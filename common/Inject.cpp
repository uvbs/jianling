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

CInject::CInject(TCHAR* lpszName)
{
    m_dwPathLen = (_tcslen(lpszName) + 1) * sizeof(TCHAR);
    m_lpszPath = new TCHAR[m_dwPathLen];
    ZeroMemory(m_lpszPath, sizeof(TCHAR)*m_dwPathLen);
    _tcscpy(m_lpszPath, lpszName);

    m_hProcess = INVALID_HANDLE_VALUE;
    m_lpMem = NULL;
}

BOOL CInject::InjectTo(DWORD pid)
{
    //打开目标进程

    HANDLE thread = NULL;
    BOOL bRet = FALSE;

    __try
    {
        m_hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_CREATE_THREAD |
                                 PROCESS_VM_OPERATION | PROCESS_VM_WRITE, false, pid);

        if(m_hProcess == NULL)
        {
            __leave;
        }

        m_lpMem = VirtualAllocEx(m_hProcess, NULL, m_dwPathLen,
                                 MEM_COMMIT, PAGE_READWRITE);//在远进程中申请内存
        if(m_lpMem == NULL)
        {
            __leave;
        }

        DWORD dwWriteBytes;
        int result = WriteProcessMemory(m_hProcess, m_lpMem, (LPVOID)m_lpszPath, m_dwPathLen, &dwWriteBytes);//写入到远进程
        if(result == 0)
        {
            __leave;
        }


#ifdef UNICODE
        pfnLoadLibrary = (PTHREAD_START_ROUTINE)GetProcAddress(GetModuleHandle(_T("kernel32")),
                          "LoadLibraryW");//在远进程中创建线程
#else
        pfnLoadLibrary = (PTHREAD_START_ROUTINE)GetProcAddress(GetModuleHandle(_T("kernel32")),
                          "LoadLibraryA");//在远进程中创建线程
#endif

        if(pfnLoadLibrary == NULL)
        {
            __leave;
        }

        thread = CreateRemoteThread(m_hProcess, NULL, 0, pfnLoadLibrary, m_lpMem, 0, NULL);
        if(thread == NULL)
        {
            __leave;
        }

        WaitForSingleObject(thread, INFINITE);//等待远线程执行完
        bRet = TRUE;
    }
    __finally
    {
        if(m_lpMem != NULL)
        {
            VirtualFreeEx(m_hProcess, m_lpMem, 0, MEM_RELEASE);
        }

        if(thread != NULL)
        {
            CloseHandle(thread);
        }

        if(m_hProcess != NULL)
        {
            CloseHandle(m_hProcess);
        }

    }

    return bRet;
}

BOOL CInject::InjectTo(TCHAR szProcess[])
{
    //枚举当前进程列表

    HANDLE hProcessSnap;
    PROCESSENTRY32 pe32;

    // Take a snapshot of all processes in the system.
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
        {
            return InjectTo(pe32.th32ProcessID);
        }

    }
    while(Process32Next(hProcessSnap, &pe32));

    CloseHandle(hProcessSnap);
    return FALSE;
}

CInject::~CInject()
{
    delete m_lpszPath;
}