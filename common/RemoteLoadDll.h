#pragma once

#include <Windows.h>
#include <Tlhelp32.h>
#include <stdio.h>

class CreateRemoteThreadLoadDll
{
public:
    CreateRemoteThreadLoadDll(void);
    ~CreateRemoteThreadLoadDll(void);

    // 在目标进程中创建线程并注入dll
    BOOL LoadDll(LPCWSTR lpwLibFile, HANDLE hProcess);
    // 卸载dll
    BOOL UnloadDll(LPCWSTR lpwLibFile, DWORD dwProcessId);
    // 提升程序权限
    BOOL EnableDebugPrivilege(void);
    // 为当前进程增加指定的特权
    int AddPrivilege(LPCWSTR Name);
    // 操作系统版本判断
    BOOL IsVistaOrLater(void);
    // 调用NtCreateThreadEx创建远程线程
    HANDLE MyCreateRemoteThread(HANDLE hProcess, LPTHREAD_START_ROUTINE pThreadProc, LPVOID pRemoteBuf);
};

