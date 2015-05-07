// JLnp.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"


#include "..\common\RemoteLoadDll.h"
#include "..\common\inlinehook.h"
#include "..\common\HookSystemcallx86tox64.h"
#include "common.h"

HookSystemcallx86tox64 hookx64;

typedef HANDLE(WINAPI* _CreateFileW)(
    LPCWSTR lpFileName,
    DWORD dwDesiredAccess,
    DWORD dwShareMode,
    LPSECURITY_ATTRIBUTES lpSecurityAttributes,
    DWORD dwCreationDisposition,
    DWORD dwFlagsAndAttributes,
    HANDLE hTemplateFile
);

typedef HANDLE(WINAPI* _CreateMutexExW)(
    LPSECURITY_ATTRIBUTES lpMutexAttributes,
    LPCWSTR lpName,
    DWORD dwFlags,
    DWORD dwDesiredAccess);


typedef BOOL(WINAPI* _CreateProcessInternalW)(
    HANDLE hToken,
    LPCWSTR lpApplicationName,
    LPWSTR lpCommandLine,
    LPSECURITY_ATTRIBUTES lpProcessAttributes,
    LPSECURITY_ATTRIBUTES lpThreadAttributes,
    BOOL bInheritHandles,
    DWORD dwCreationFlags,
    LPVOID lpEnvironment,
    LPCWSTR lpCurrentDirectory,
    LPSTARTUPINFOW lpStartupInfo,
    LPPROCESS_INFORMATION lpProcessInformation,
    PHANDLE hNewToken);




CreateRemoteThreadLoadDll RemoteLoadDll;


//这几个硬编码的地址
#ifdef JLTW

//4月27
 //DWORD dwInitNP1 = 0x00B4c710;
 //DWORD dwInitNP2 = 0x00B4C6D0;   //dwInitNP1-40
 //DWORD CheckNP = 0x00B4C8D0;     //dwInitNP1+1c0

 //5月6
 DWORD dwInitNP1 = 0x00B4cA10;
 DWORD dwInitNP2 = 0x00B4C9D0;   //dwInitNP1-40
 DWORD CheckNP = 0x00B4CBD0;     //dwInitNP1+1c0


DWORD dwInitNP1 = 0x00B4cA10;
DWORD dwInitNP2 = 0x00B4C9D0;   //dwInitNP1-40
DWORD CheckNP = 0x00B4CBD0;     //dwInitNP1+1c0
#else

#error "no write"

#endif

DWORD dw1;
DWORD dw2;
DWORD dw3;


char szProcess[MAX_PATH];
char szModulePatch[MAX_PATH];

_CreateMutexExW Orig_CreateMutexExW;
_CreateFileW Orig_CreateFileW;
_CreateProcessInternalW Orig_CreateProcessInternalW;


VOID WINAPI c2w(wchar_t* pwstr, size_t len, const char* str)
{
    if(str)
    {
        size_t nu = strlen(str);
        size_t n = (size_t)MultiByteToWideChar(CP_ACP, 0, (const char*)str, (int)nu, NULL, 0);
        if(n >= len)
            n = len - 1;

        MultiByteToWideChar(CP_ACP, 0, (const char*)str, (int)nu, pwstr, (int)n);
        pwstr[n] = 0;
    }
}


__declspec(naked) void Fuck()
{
    __asm
    {
        mov eax, 0x755;
        retn;
    }
}


HANDLE WINAPI CreateMutexExW_hook(
    LPSECURITY_ATTRIBUTES lpMutexAttributes,
    LPCWSTR lpName,
    DWORD dwFlags,
    DWORD dwDesiredAccess
)
{

    HANDLE handle = Orig_CreateMutexExW(lpMutexAttributes, lpName, dwFlags, dwDesiredAccess);
    if(lpName && wcsstr(lpName, L"BnSGameClient"))
        CloseHandle(handle);
    return handle;
}

BOOL WINAPI MyCreateProcessInternalW(HANDLE hToken,
                                     LPCWSTR lpApplicationName,
                                     LPWSTR lpCommandLine,
                                     LPSECURITY_ATTRIBUTES lpProcessAttributes,
                                     LPSECURITY_ATTRIBUTES lpThreadAttributes,
                                     BOOL bInheritHandles,
                                     DWORD dwCreationFlags,
                                     LPVOID lpEnvironment,
                                     LPCWSTR lpCurrentDirectory,
                                     LPSTARTUPINFOW lpStartupInfo,
                                     LPPROCESS_INFORMATION lpProcessInformation,
                                     PHANDLE hNewToken)
{

    //剥离NP失败
    if(lpApplicationName && wcslen(lpApplicationName) && wcsstr(lpApplicationName, L".des"))
    {
        MessageBoxW(NULL, lpApplicationName, lpApplicationName, NULL);
        ExitProcess(0);
    }

    if(lpCommandLine && wcslen(lpCommandLine) && wcsstr(lpCommandLine, L".des"))
    {
        MessageBoxW(NULL, lpCommandLine, lpCommandLine, NULL);
        ExitProcess(0);
    }

    //注入
    BOOL blRet = Orig_CreateProcessInternalW(hToken,
                 lpApplicationName,
                 lpCommandLine,
                 lpProcessAttributes,
                 lpThreadAttributes,
                 bInheritHandles,
                 dwCreationFlags,
                 lpEnvironment,
                 lpCurrentDirectory,
                 lpStartupInfo,
                 lpProcessInformation,
                 hNewToken);
    if(blRet)
    {
        WCHAR wcsFile[MAXCHAR];
        c2w(wcsFile, strlen(szModulePatch) + 1, szModulePatch);
        RemoteLoadDll.LoadDll(wcsFile, lpProcessInformation->hProcess);//注入模块
    }

    return blRet;
}


typedef NTSTATUS(WINAPI* _NtQueryInformationProcess)(HANDLE ProcessHandle,
        PROCESSINFOCLASS ProcessInformationClass,
        PVOID ProcessInformation,
        ULONG ProcessInformationLength,
        PULONG ReturnLength
                                                    );

_NtQueryInformationProcess  OrigNtQueryInformationProcess;
NTSTATUS WINAPI NtQueryInformationProcess_Hook(HANDLE ProcessHandle,
        PROCESSINFOCLASS ProcessInformationClass,
        PVOID ProcessInformation,
        ULONG ProcessInformationLength,
        PULONG ReturnLength)
{
    NTSTATUS ntStatus;

    ////////////////////////////////////////////////////
    ntStatus = OrigNtQueryInformationProcess(ProcessHandle, ProcessInformationClass, ProcessInformation, ProcessInformationLength, ReturnLength);
    if(NT_SUCCESS(ntStatus))
    {
        if(ProcessInformationClass == ProcessDebugPort && NT_SUCCESS(ntStatus))
            memset(ProcessInformation, 0, ProcessInformationLength);
        if(ProcessInformationClass == ProcessDebugObjectHandle && NT_SUCCESS(ntStatus))
            memset(ProcessInformation, 0, ProcessInformationLength);
        if(ProcessInformationClass == ProcessDebugFlags && NT_SUCCESS(ntStatus))
            memset(ProcessInformation, -1, ProcessInformationLength);
    }

    return ntStatus;
}

typedef NTSTATUS(WINAPI* _NtSetInformationThread)(IN HANDLE     ThreadHandle,
        IN THREADINFOCLASS ThreadInformationClass,
        IN PVOID    ThreadInformation,
        IN ULONG    ThreadInformationLength);
_NtSetInformationThread OrigNtSetInformationThread;
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NTSTATUS    WINAPI  NtSetInformationThread_Hook(IN HANDLE               ThreadHandle,
        IN THREADINFOCLASS      ThreadInformationClass,
        IN PVOID                ThreadInformation,
        IN ULONG                ThreadInformationLength)
{

    if(ThreadInformationClass == ThreadHideFromDebugger)
        return STATUS_SUCCESS;

    return OrigNtSetInformationThread(ThreadHandle, ThreadInformationClass, ThreadInformation, ThreadInformationLength);
}

typedef NTSTATUS(WINAPI* _ZwGetContextThread)(
    IN HANDLE               ThreadHandle,
    OUT PCONTEXT            pContext);
_ZwGetContextThread ZwGetContextThread;
NTSTATUS WINAPI ZwGetContextThread_Hook(
    IN HANDLE               ThreadHandle,
    OUT PCONTEXT            pContext)
{
    NTSTATUS ntStatus = ZwGetContextThread(ThreadHandle, pContext);
    if(NT_SUCCESS(ntStatus))
        pContext->Dr0 = pContext->Dr1 = pContext->Dr2 = pContext->Dr3 = pContext->Dr6 = pContext->Dr7 = 0;
    return ntStatus;
}
HANDLE WINAPI CreateFileW_Hook(
    LPCWSTR lpFileName,
    DWORD dwDesiredAccess,
    DWORD dwShareMode,
    LPSECURITY_ATTRIBUTES lpSecurityAttributes,
    DWORD dwCreationDisposition,
    DWORD dwFlagsAndAttributes,
    HANDLE hTemplateFile
)
{

    //这里方便调试
    //if(wcsstr(lpFileName, L"rsaenh"))
    //{
    //  MessageBoxW(NULL, lpFileName, NULL, NULL);
    //}

    //处理文件独占
    if(dwShareMode == NULL)
        dwShareMode = FILE_SHARE_READ | FILE_SHARE_WRITE;
    return Orig_CreateFileW(lpFileName, dwDesiredAccess, dwShareMode, lpSecurityAttributes, dwCreationDisposition, dwFlagsAndAttributes, hTemplateFile);
}


//剥离操作的线程
DWORD WINAPI nPthread(PVOID lpParam)
{
    for(;;)
    {
        //设置 dwInitNP1 地址处的内存属性为 可读可写可执行
        //返回的 dwProtect 存储原本属性
        DWORD dwProtect;
        VirtualProtect((VOID*)dwInitNP1, 5, PAGE_EXECUTE_READWRITE, &dwProtect);

        //取此地址 0x0af7460 处的第一个字节 是否 == 0xa1
        if(*(BYTE*)dwInitNP1 == 0xA1)
        {
            //钩住这几个地址处的函数
            //钩到这里  Fuck
            InlineHook((VOID*)dwInitNP1, (VOID*)Fuck, (VOID**)&dw1);//适当的时候还原HOOK 避免被扒
            InlineHook((VOID*)dwInitNP2, (VOID*)Fuck, (VOID**)&dw2);//适当的时候还原HOOK 避免被扒
            InlineHook((VOID*)CheckNP, (VOID*)Fuck, (VOID**)&dw3);//这个不能还原
            break;
        }

        //TODO: 偶尔np启动
        Sleep(10);
    }

    return 0;
}

//清NP保护的线程
void ClearNP(HMODULE hModule)
{

    GetModuleFileNameA(NULL, szProcess, MAXCHAR);
    GetModuleFileNameA(hModule, szModulePatch, MAXCHAR);
    _strupr(szProcess);

    if(strstr(szProcess, "CLIENT.EXE"))
    {
        //创建线程执行
        CreateThread(0, 0, nPthread, 0, 0, 0);

        //处理调试器  多开不需要这些玩意
        hookx64.Initialization();
        hookx64.InstallHook("ZwSetInformationThread", (DWORD)NtSetInformationThread_Hook, (PDWORD)&OrigNtSetInformationThread);
        hookx64.InstallHook("ZwQueryInformationProcess", (DWORD)NtQueryInformationProcess_Hook, (PDWORD)&OrigNtQueryInformationProcess);
        hookx64.InstallHook("ZwGetContextThread", (DWORD)ZwGetContextThread_Hook, (PDWORD)&ZwGetContextThread);

        //多开.互斥,文件独占
        InlineHook((VOID*)(DWORD)GetProcAddress(LoadLibraryA("kernelBase.dll"), "CreateMutexExW"), (VOID*)CreateMutexExW_hook, (VOID**)&Orig_CreateMutexExW);
        InlineHook((VOID*)(DWORD)GetProcAddress(LoadLibraryA("kernelBase.dll"), "CreateFileW"), (VOID*)CreateFileW_Hook, (VOID**)&Orig_CreateFileW);
        InlineHook((VOID*)(DWORD)GetProcAddress(LoadLibraryA("kernel32.dll"), "CreateProcessInternalW"), (VOID*)MyCreateProcessInternalW, (VOID**)&Orig_CreateProcessInternalW);
    }
    else
    {


        HMODULE hKer32 = GetModuleHandle(_T("kernel32.dll"));
        if(hKer32 == NULL) return;

        DWORD dwCreateProcessInternalW = (DWORD)GetProcAddress(hKer32, "CreateProcessInternalW");
        if(dwCreateProcessInternalW == NULL) return;

        //硬编码
        InlineHook((VOID*)dwCreateProcessInternalW, (VOID*)MyCreateProcessInternalW, (VOID**)&Orig_CreateProcessInternalW);
    }


}


BOOL APIENTRY DllMain(HANDLE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
    switch(ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        {
            ClearNP((HMODULE)hModule);
            break;
        }

    case DLL_PROCESS_DETACH:
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
        break;

    }
    return TRUE;
}

