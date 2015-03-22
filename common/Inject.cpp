

// inject.cpp: implementation of the Inject class.
//
//////////////////////////////////////////////////////////////////////
#include "StdAfx.h"
#include "Inject.h"

#include "../common/Toolhelp.h"
#include "../common/logger.h"



//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CInject::CInject(const TCHAR* lpszName)
{
    m_dwPathLen = (_tcslen(lpszName) + 1) * sizeof(TCHAR);
    m_lpszName = lpszName;
    m_hProcess = INVALID_HANDLE_VALUE;
    m_lpMem = NULL;
}


// ��������Ȩ��
BOOL CInject::EnableDebugPrivilege(void)
{
    HANDLE hToken;
    BOOL fOk = FALSE;
    if(OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES, &hToken)) {
        TOKEN_PRIVILEGES   tp;
        tp.PrivilegeCount = 1;
        if(!LookupPrivilegeValue(NULL, SE_DEBUG_NAME, &tp.Privileges[0].Luid))
            tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

        if(!AdjustTokenPrivileges(hToken, FALSE, &tp, sizeof(tp), NULL, NULL));
        else
            fOk = TRUE;

        CloseHandle(hToken);
    }
    return fOk;
}

// Ϊ��ǰ��������ָ������Ȩ
int CInject::AddPrivilege(LPCWSTR Name)
{

    HANDLE   hToken;
    TOKEN_PRIVILEGES   tp;
    LUID   Luid;

    if(!OpenProcessToken(GetCurrentProcess(),
                         TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY,
                         &hToken)) {
        #ifdef   _DEBUG
        printf("OpenProcessToken   error.\n ");
        #endif
        return   1;
    }

    if(!LookupPrivilegeValueW(NULL, Name, &Luid)) {
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
                              NULL)) {
        #ifdef   _DEBUG
        printf("AdjustTokenPrivileges   error.\n ");
        #endif
        return   1;
    }

    return   0;
}


//����ϵͳ�汾�ж�
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

    //����ȫ·��
    LPTSTR lpFilePart;
    DWORD dwPathSize = GetFullPathName(m_lpszName, MAX_PATH, m_lpszPath, &lpFilePart);
    DWORD m_dwPathLen = (dwPathSize + 1) * sizeof(TCHAR);

    __try {

        //��Ŀ�����
        m_hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_CREATE_THREAD |
                                 PROCESS_VM_OPERATION | PROCESS_VM_WRITE | PROCESS_VM_READ, TRUE, pid);
        if(m_hProcess == NULL) __leave;

        //׼���ڴ�
        m_lpMem = VirtualAllocEx(m_hProcess, NULL, m_dwPathLen,
                                 MEM_COMMIT, PAGE_READWRITE);
        if(m_lpMem == NULL) __leave;

        //д��Զ�̽���
        DWORD dwWriteBytes;
        int result = WriteProcessMemory(m_hProcess, m_lpMem, (LPVOID)m_lpszPath, m_dwPathLen, &dwWriteBytes);
        if(result == 0) __leave;
        ASSERT(dwWriteBytes == m_dwPathLen);


        //ȡԶ�̽���LoadLibrary��ַ
        #ifdef _UNICODE
        pfnLoadLibrary = (PTHREAD_START_ROUTINE)GetProcAddress(
                             GetModuleHandle(_T("kernel32")), "LoadLibraryW");
        #else
        pfnLoadLibrary = (PTHREAD_START_ROUTINE)GetProcAddress(
                             GetModuleHandle(_T("kernel32")), "LoadLibraryA");
        #endif

        if(pfnLoadLibrary == NULL) __leave;

        //Զ�߳�ִ��
        DWORD dwThreadId;
        hThread = CreateRemoteThread(m_hProcess, NULL, 0, pfnLoadLibrary, m_lpMem, 0, &dwThreadId);
        if(hThread == NULL) __leave;

        //�ȴ�����
        WaitForSingleObject(hThread, INFINITE);//�ȴ�Զ�߳�ִ����
        bRet = TRUE;
    }
    __finally {
        if(m_lpMem != NULL) {
            VirtualFreeEx(m_hProcess, m_lpMem, 0, MEM_RELEASE);
        }

        if(hThread != NULL) {
            CloseHandle(hThread);
        }

        if(m_hProcess != NULL) {
            CloseHandle(m_hProcess);
        }

    }

    return bRet;
}

BOOL CInject::InjectTo(TCHAR szProcess[])
{

    HANDLE hProcessSnap;
    PROCESSENTRY32 pe32;

    //ö�ٵ�ǰ�����б�
    hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if(hProcessSnap == INVALID_HANDLE_VALUE) {
        return TRUE;
    }

    // Set the size of the structure before using it.
    pe32.dwSize = sizeof(PROCESSENTRY32);

    // Retrieve information about the first process,
    // and exit if unsuccessful
    if(!Process32First(hProcessSnap, &pe32)) {
        CloseHandle(hProcessSnap);// clean the snapshot object
        return TRUE;
    }


    do {
        if(_tcscmp(pe32.szExeFile, szProcess) == 0)
            return InjectTo(pe32.th32ProcessID);

    }
    while(Process32Next(hProcessSnap, &pe32));

    CloseHandle(hProcessSnap);
    return FALSE;
}