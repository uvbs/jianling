#include "stdafx.h"
#include "RemoteLoadDll.h"

CreateRemoteThreadLoadDll::CreateRemoteThreadLoadDll(void)
{
}

CreateRemoteThreadLoadDll::~CreateRemoteThreadLoadDll(void)
{
}

typedef WCHAR WPATH[MAX_PATH];
typedef struct _UNICODE_STRING
{
    USHORT Length;
    USHORT MaximumLength;
    PWSTR  Buffer;
} UNICODE_STRING, *PUNICODE_STRING;

typedef struct _OBJECT_ATTRIBUTES
{
    ULONG           Length;
    HANDLE          RootDirectory;
    PUNICODE_STRING ObjectName;
    ULONG           Attributes;
    PVOID           SecurityDescriptor;
    PVOID           SecurityQualityOfService;
}  OBJECT_ATTRIBUTES, *POBJECT_ATTRIBUTES;


typedef struct _PROC_THREAD_ATTRIBUTE_ENTRY
{
    SIZE_T        Attribute;
    SIZE_T        Size;
    SIZE_T*        pValue;
    SIZE_T        Unknown;
} PROC_THREAD_ATTRIBUTE_ENTRY, *PPROC_THREAD_ATTRIBUTE_ENTRY;

typedef struct _PROC_THREAD_ATTRIBUTE_LIST
{
    SIZE_T                        Length;
    PROC_THREAD_ATTRIBUTE_ENTRY    Entry[2];
} PROC_THREAD_ATTRIBUTE_LIST, *PPROC_THREAD_ATTRIBUTE_LIST;

typedef DWORD (WINAPI* _NtCreateThreadEx)(OUT PHANDLE ThreadHandle,
        IN ACCESS_MASK DesiredAccess,
        IN POBJECT_ATTRIBUTES ObjectAttributes OPTIONAL,
        IN HANDLE ProcessHandle,
        IN PTHREAD_START_ROUTINE StartRoutine,
        IN PVOID StartContext,
        IN ULONG CreateThreadFlags,
        IN SIZE_T ZeroBits OPTIONAL,
        IN SIZE_T StackSize OPTIONAL,
        IN SIZE_T MaximumStackSize OPTIONAL,
        IN PPROC_THREAD_ATTRIBUTE_LIST AttributeList
                                         );
_NtCreateThreadEx ZwCreateThreadEx;

// ��Ŀ������д����̲߳�ע��dll
BOOL CreateRemoteThreadLoadDll::LoadDll(LPCWSTR lpwLibFile, HANDLE hProcess)
{

    BOOL   bRet = FALSE;
    HANDLE  hThread = NULL;
    LPVOID pszLibRemoteFile   =   NULL;
    SIZE_T dwWritten = 0;

    bRet = EnableDebugPrivilege();
    if(bRet != TRUE)
    {
        OutputDebugStringA("add privilege failed!\n");
        return -1;
    }
    __try
    {

        DWORD   cch   =   1   +   lstrlenW(lpwLibFile);
        DWORD   cb   =   cch   *   sizeof(WCHAR);
        //DbgPrint("cb:%d\n",cb);
        //DbgPrint("cb1:%d\n",sizeof(lpwLibFile));
        //2.�����㹻�Ŀռ䣬�Ա�����ǵ�dllд��Ŀ�����������ռ���
        pszLibRemoteFile   =  VirtualAllocEx(hProcess, NULL, cb, MEM_COMMIT, PAGE_READWRITE);

        if(pszLibRemoteFile   ==   NULL)
            __leave;
        //3.��ʽ�����ǵ�dllд����������Ŀռ�
        BOOL   bw   =   WriteProcessMemory(hProcess,   pszLibRemoteFile, (PVOID)lpwLibFile,   cb,   &dwWritten);
        if(dwWritten != cb)
        {
            //DbgPrint("write error!\n");
        }
        if(!bw)
            __leave;
        //4.��ùؼ�����LoadLibraryW��ַ
        PTHREAD_START_ROUTINE   pfnThreadRnt   = (LPTHREAD_START_ROUTINE)GetProcAddress(GetModuleHandleW(L"Kernel32"), "LoadLibraryW");
        if(pfnThreadRnt   ==   NULL)
            __leave;

        //5.�����̲߳���LoadLibraryW��Ϊ�߳���ʼ����������LoadLibraryW�Ĳ��������ǵ�dll
        if(MyCreateRemoteThread(hProcess, pfnThreadRnt, pszLibRemoteFile))
            __leave;

        bRet   =   TRUE;
    }
    __except(EXCEPTION_EXECUTE_HANDLER)
    {
        OutputDebugStringA("CreateRemoteThread errer\r\n");
        if(pszLibRemoteFile   !=   NULL)
            VirtualFreeEx(hProcess,   pszLibRemoteFile,   0,   MEM_RELEASE);

        if(hThread   !=   NULL)
            CloseHandle(hThread);

        if(hProcess   !=   NULL)
            CloseHandle(hProcess);
    }


    return   bRet;
}

// ж��dll
BOOL CreateRemoteThreadLoadDll::UnloadDll(LPCWSTR lpwLibFile, DWORD dwProcessId)
{

    BOOL   bRet   =   FALSE;
    HANDLE   hProcess   =   NULL,   hThread   =   NULL;
    HANDLE   hSnapshot   =   NULL;

    __try
    {
        hSnapshot   =   CreateToolhelp32Snapshot(TH32CS_SNAPMODULE,   dwProcessId);
        if(hSnapshot   ==   NULL)
            __leave;
        MODULEENTRY32W   me   =   {sizeof(MODULEENTRY32W)};
        BOOL   bFound   =   FALSE;
        BOOL   bMoreMods   =   Module32FirstW(hSnapshot,   &me);
        for(;   bMoreMods;   bMoreMods   =   Module32NextW(hSnapshot,   &me))
        {
            bFound   = (lstrcmpiW(me.szModule,   lpwLibFile)   ==   0)   ||
                       (lstrcmpiW(me.szExePath,   lpwLibFile)   ==   0);
            if(bFound)
                break;
        }

        if(!bFound)
            __leave;
        hProcess   =   OpenProcess(
                           PROCESS_CREATE_THREAD   |
                           PROCESS_VM_OPERATION,
                           FALSE,   dwProcessId);

        if(hProcess   ==   NULL)
            __leave;

        PTHREAD_START_ROUTINE   pfnThreadRnt   = (PTHREAD_START_ROUTINE)
                GetProcAddress(GetModuleHandle(TEXT("Kernel32 ")),   "FreeLibrary ");
        if(pfnThreadRnt   ==   NULL)
            __leave;

        if(MyCreateRemoteThread(hProcess, pfnThreadRnt, me.modBaseAddr))
            __leave;

        bRet   =   TRUE;
    }
    __except(EXCEPTION_EXECUTE_HANDLER)
    {
        OutputDebugStringA("CreateRemoteThread errer\r\n");
        if(hSnapshot   !=   NULL)
            CloseHandle(hSnapshot);

        if(hThread   !=   NULL)
            CloseHandle(hThread);

        if(hProcess   !=   NULL)
            CloseHandle(hProcess);
    }

    return   bRet;
}

// ��������Ȩ��
BOOL CreateRemoteThreadLoadDll::EnableDebugPrivilege(void)
{
    HANDLE   hToken;
    BOOL   fOk = FALSE;
    if(OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES, &hToken))
    {
        TOKEN_PRIVILEGES   tp;
        tp.PrivilegeCount = 1;
        if(!LookupPrivilegeValue(NULL, SE_DEBUG_NAME, &tp.Privileges[0].Luid))
            tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
        if(!AdjustTokenPrivileges(hToken, FALSE, &tp, sizeof(tp), NULL, NULL));
        else
            fOk = TRUE;
        CloseHandle(hToken);
    }
    return   fOk;
}

// Ϊ��ǰ��������ָ������Ȩ
int CreateRemoteThreadLoadDll::AddPrivilege(LPCWSTR Name)
{

    HANDLE   hToken;
    TOKEN_PRIVILEGES   tp;
    LUID   Luid;

    if(!OpenProcessToken(GetCurrentProcess(),
                         TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY,
                         &hToken))
    {
#ifdef   _DEBUG
        printf("OpenProcessToken   error.\n ");
#endif
        return   1;
    }

    if(!LookupPrivilegeValueW(NULL, Name, &Luid))
    {
#ifdef   _DEBUG
        printf("LookupPrivilegeValue   error.\n ");
#endif
        return   1;
    }

    tp.PrivilegeCount   =   1;
    tp.Privileges[0].Attributes   =   SE_PRIVILEGE_ENABLED;
    tp.Privileges[0].Luid   =   Luid;

    if(!AdjustTokenPrivileges(hToken,
                              0,
                              &tp,
                              sizeof(TOKEN_PRIVILEGES),
                              NULL,
                              NULL))
    {
#ifdef   _DEBUG
        printf("AdjustTokenPrivileges   error.\n ");
#endif
        return   1;
    }

    return   0;
}


//����ϵͳ�汾�ж�
BOOL CreateRemoteThreadLoadDll::IsVistaOrLater(void)
{
    OSVERSIONINFO osvi;
    ZeroMemory(&osvi, sizeof(OSVERSIONINFO));
    osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
    GetVersionEx(&osvi);
    if(osvi.dwMajorVersion >= 6)
        return TRUE;
    return FALSE;
}

// ����NtCreateThreadEx����Զ���߳�
HANDLE CreateRemoteThreadLoadDll::MyCreateRemoteThread(HANDLE hProcess, LPTHREAD_START_ROUTINE pThreadProc, LPVOID pRemoteBuf)
{

    HANDLE      hThread = NULL;

    if(IsVistaOrLater())      // Vista, 7, Server2008
    {
        ZwCreateThreadEx = (_NtCreateThreadEx)GetProcAddress(GetModuleHandleW(L"ntdll.dll"), "NtCreateThreadEx");
        if(ZwCreateThreadEx == NULL)
        {
            //DbgPrint("MyCreateRemoteThread() : GetProcAddress(\"NtCreateThreadEx\") ����ʧ�ܣ��������: [%d]/n",GetLastError());
            return FALSE;
        }
        ZwCreateThreadEx(
            &hThread,
            0x1FFFFF,
            NULL,
            hProcess,
            pThreadProc,
            pRemoteBuf,
            FALSE,
            NULL,
            NULL,
            NULL,
            NULL);
    }
    else                    // 2000, XP, Server2003
    {
        hThread = CreateRemoteThread(hProcess,
                                     NULL,
                                     0,
                                     pThreadProc,
                                     pRemoteBuf,
                                     0,
                                     NULL);
    }
    return hThread ;
}
