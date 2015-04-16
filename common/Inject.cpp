#include "StdAfx.h"
#include "Inject.h"


CInject::CInject(const TCHAR* lpszName)
{
    m_lpszName = lpszName;
}


// 提升程序权限
BOOL CInject::EnableDebugPrivilege(void)
{
    HANDLE hToken;
    BOOL fOk = FALSE;
    if(OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES, &hToken))
    {
        TOKEN_PRIVILEGES   tp;
        tp.PrivilegeCount = 1;
        if(!LookupPrivilegeValue(NULL, SE_DEBUG_NAME, &tp.Privileges[0].Luid))
            tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

        if(AdjustTokenPrivileges(hToken, FALSE, &tp, sizeof(tp), NULL, NULL))
            fOk = TRUE;

        CloseHandle(hToken);
    }
    return fOk;
}

// 为当前进程增加指定的特权
int CInject::AddPrivilege(LPCWSTR Name)
{

    HANDLE   hToken;
    TOKEN_PRIVILEGES   tp;
    LUID   Luid;

    if(!OpenProcessToken(GetCurrentProcess(),
                         TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY,
                         &hToken))
    {
#ifdef   _DEBUG
#endif
        return   1;
    }

    if(!LookupPrivilegeValueW(NULL, Name, &Luid))
    {
#ifdef   _DEBUG
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
#endif
        return   1;
    }

    return   0;
}


//操作系统版本判断
BOOL CInject::IsVistaOrLater(void)
{
    OSVERSIONINFO osvi;
    ZeroMemory(&osvi, sizeof(OSVERSIONINFO));
    osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);

    GetVersionEx(&osvi);
    if(osvi.dwMajorVersion >= 6)
        return TRUE;

    return FALSE;
}

BOOL CInject::InjectTo(DWORD pid)
{
    BOOL bRet = FALSE;
    HANDLE hThread = NULL;
    HANDLE hProcess = INVALID_HANDLE_VALUE;
    LPVOID lpMem = NULL;

    EnableDebugPrivilege();

    //计算全路径
    LPTSTR lpFilePart;
    TCHAR szFullPath[MAX_PATH] = {0};
    DWORD dwPathSize = GetFullPathName(m_lpszName, MAX_PATH, szFullPath, &lpFilePart);
    _ASSERTE(dwPathSize != 0);
    DWORD dwPathLen = (dwPathSize + 1) * sizeof(TCHAR);

    __try
    {

        //打开目标进程
        hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_CREATE_THREAD |
                               PROCESS_VM_OPERATION | PROCESS_VM_WRITE | PROCESS_VM_READ, TRUE, pid);
        if(hProcess == NULL) __leave;

        //准备内存
        lpMem = VirtualAllocEx(hProcess, NULL, dwPathLen, MEM_COMMIT, PAGE_READWRITE);
        if(lpMem == NULL) __leave;

        //写入远程进程
        DWORD dwWriteBytes;
        int result = WriteProcessMemory(hProcess, lpMem, (LPVOID)szFullPath, dwPathLen, &dwWriteBytes);
        if(result == 0) __leave;
        ASSERT(dwWriteBytes == dwPathLen);


        //取远程进程LoadLibrary地址
#ifdef _UNICODE
        PTHREAD_START_ROUTINE pfnLoadLibrary = (PTHREAD_START_ROUTINE)GetProcAddress(
                GetModuleHandle(_T("kernel32")), "LoadLibraryW");
#else
        PTHREAD_START_ROUTINE pfnLoadLibrary = (PTHREAD_START_ROUTINE)GetProcAddress(
                GetModuleHandle(_T("kernel32")), "LoadLibraryA");
#endif

        if(pfnLoadLibrary == NULL) __leave;

        //远线程执行
        DWORD dwThreadId;
        hThread = CreateRemoteThread(hProcess, NULL, 0, pfnLoadLibrary, lpMem, 0, &dwThreadId);
        if(hThread == NULL) __leave;

        //等待结束
        WaitForSingleObject(hThread, INFINITE);//等待远线程执行完
        bRet = TRUE;
    }
    __finally
    {
        if(lpMem != NULL)
        {
            VirtualFreeEx(hProcess, lpMem, 0, MEM_RELEASE);
        }

        if(hThread != NULL)
        {
            CloseHandle(hThread);
        }

        if(hProcess != NULL)
        {
            CloseHandle(hProcess);
        }

    }

    return bRet;
}

BOOL CInject::InjectTo(TCHAR szProcess[])
{

    HANDLE hProcessSnap;
    PROCESSENTRY32 pe32;

    //枚举当前进程列表
    hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if(hProcessSnap == INVALID_HANDLE_VALUE)
    {
        return TRUE;
    }

    // Set the size of the structure before using it.
    pe32.dwSize = sizeof(PROCESSENTRY32);

    // Retrieve information about the first process,
    // and exit if unsuccessful
    if(!Process32First(hProcessSnap, &pe32))
    {
        CloseHandle(hProcessSnap);// clean the snapshot object
        return TRUE;
    }

    do
    {
        if(_tcscmp(pe32.szExeFile, szProcess) == 0)
            return InjectTo(pe32.th32ProcessID);

    }
    while(Process32Next(hProcessSnap, &pe32));

    CloseHandle(hProcessSnap);
    return FALSE;
}