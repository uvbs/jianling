#pragma once

#include <Windows.h>
#include <Tlhelp32.h>
#include <stdio.h>

class CreateRemoteThreadLoadDll
{
public:
    CreateRemoteThreadLoadDll(void);
    ~CreateRemoteThreadLoadDll(void);

    // ��Ŀ������д����̲߳�ע��dll
    BOOL LoadDll(LPCWSTR lpwLibFile, HANDLE hProcess);
    // ж��dll
    BOOL UnloadDll(LPCWSTR lpwLibFile, DWORD dwProcessId);
    // ��������Ȩ��
    BOOL EnableDebugPrivilege(void);
    // Ϊ��ǰ��������ָ������Ȩ
    int AddPrivilege(LPCWSTR Name);
    // ����ϵͳ�汾�ж�
    BOOL IsVistaOrLater(void);
    // ����NtCreateThreadEx����Զ���߳�
    HANDLE MyCreateRemoteThread(HANDLE hProcess, LPTHREAD_START_ROUTINE pThreadProc, LPVOID pRemoteBuf);
};

