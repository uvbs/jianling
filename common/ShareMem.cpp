#include "stdafx.h"
#include "ShareMem.h"


ShareMem* ShareMem::Instance()
{
    if(_inst == NULL) {
        _inst = new ShareMem;
    }

    return _inst;
}
ShareMem* ShareMem::_inst = NULL;



ShareMem::ShareMem()
{
    m_hFileMap = INVALID_HANDLE_VALUE;
    m_lpMem = NULL;
    m_dwCount = 0;
}



BOOL ShareMem::Create(DWORD dwCount, TCHAR szObjName[])
{

    BOOL bRet = FALSE;

    __try {

        DWORD MemSize = dwCount * sizeof(SHAREINFO) + sizeof(DWORD);


        //创建共享对象
        m_hFileMap = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, MemSize, szObjName);
        if(m_hFileMap == NULL) {
            __leave;
        }

        m_lpMem = (SHAREINFO*)MapViewOfFile(m_hFileMap, FILE_MAP_ALL_ACCESS, 0, 0, 0);
        if(m_lpMem == NULL) {
            __leave;
        }


        ZeroMemory(m_lpMem, MemSize);
        *(DWORD*)m_lpMem = MemSize;
        m_lpMem = (SHAREINFO*)((DWORD)m_lpMem + sizeof(DWORD));
        m_dwCount = dwCount;

        bRet = TRUE;

    }
    __finally {
        if(bRet == FALSE) {
            if(m_hFileMap != NULL) {
                CloseHandle(m_hFileMap);
                m_hFileMap = NULL;
            }

            if(m_lpMem) {
                UnmapViewOfFile(m_lpMem);
                m_lpMem = NULL;
            }
        }

    }


    return bRet;
}



void ShareMem::Close()
{
    if(m_lpMem != NULL) {
        m_lpMem = (SHAREINFO*)((DWORD)m_lpMem - sizeof(DWORD));
        UnmapViewOfFile(m_lpMem);
        m_lpMem = NULL;
    }


    if(m_hFileMap != NULL) {
        CloseHandle(m_hFileMap);
        m_hFileMap = NULL;
    }

    m_dwCount = 0;
}


ShareMem::~ShareMem()
{
    Close();
}


BOOL ShareMem::Add(SHAREINFO* pShareInfo)
{

    SHAREINFO* pItor = m_lpMem;
    for(DWORD i = 0; i < m_dwCount; i++) {
        if(pItor->pid == 0) {
            memcpy(pItor, pShareInfo, sizeof(SHAREINFO));
            break;
        }

        pItor++;
    }

    return TRUE;
}


//获取已经登录的个数
DWORD ShareMem::GetUsedCount()
{

    if(m_lpMem == NULL) {
        return 0;
    }

    DWORD count = 0;
    SHAREINFO* pItor = m_lpMem;
    for(DWORD i = 0; i < m_dwCount; i++) {
        if(pItor->pid != 0) {
            count++;
        }

        pItor++;
    }

    return count;
}


BOOL ShareMem::Open(TCHAR szObjName[])
{
    BOOL bRet = FALSE;
    __try {
        m_hFileMap = OpenFileMapping(FILE_MAP_ALL_ACCESS, FALSE, szObjName);
        if(m_hFileMap == NULL) __leave;

        m_lpMem = (SHAREINFO*)MapViewOfFile(m_hFileMap, FILE_MAP_ALL_ACCESS, 0, 0, 0);
        if(m_lpMem == NULL) __leave;

        int MemSize = *(DWORD*)m_lpMem;
        m_lpMem = (SHAREINFO*)((DWORD)m_lpMem + sizeof(DWORD));
        m_dwCount = (MemSize - sizeof(DWORD)) / sizeof(SHAREINFO);
        bRet = TRUE;
    }
    __finally {
        if(bRet == FALSE) {
            if(m_hFileMap != NULL) {
                CloseHandle(m_hFileMap);
                m_hFileMap = NULL;
            }

            if(m_lpMem) {
                UnmapViewOfFile(m_lpMem);
                m_lpMem = NULL;
            }
        }

    }

    if(bRet == FALSE) {
        TRACE(_T("没能打开共享内存"));
    }


    return bRet;
}


void ShareMem::Del(LPCTSTR lpszName)
{

    SHAREINFO* pItor = m_lpMem;
    for(DWORD i = 0; i < m_dwCount; i++) {
        if(_tcscmp(pItor->szName, lpszName) == 0) {
            ZeroMemory(pItor, sizeof(SHAREINFO));
            break;
        }

        pItor++;
    }

}


void ShareMem::Del(DWORD dwPid)
{

    SHAREINFO* pItor = m_lpMem;
    for(DWORD i = 0; i < m_dwCount; i++) {
        if(pItor->pid == dwPid) {
            ZeroMemory(pItor, sizeof(SHAREINFO));
            break;
        }

        pItor++;
    }
}



//获取指定的共享数据
SHAREINFO* ShareMem::Get(LPCTSTR lpszName)
{
    if(m_lpMem == NULL || m_hFileMap == NULL) return NULL;

    SHAREINFO* pItor = m_lpMem;
    for(DWORD i = 0; i < m_dwCount; i++) {
        if(_tcscmp(pItor->szName, lpszName) == 0) {
            return pItor;
        }

        pItor++;
    }

    TRACE(_T("没能获取相关数据"));
    return NULL;
}


//获取指定的共享数据
SHAREINFO* ShareMem::Get(DWORD dwPid)
{
    if(m_lpMem == NULL ||
            m_hFileMap == NULL) {
        return FALSE;
    }


    SHAREINFO* pItor = m_lpMem;
    for(DWORD i = 0; i < m_dwCount; i++) {
        if(pItor->pid == dwPid) {
            return pItor;
        }

        pItor++;
    }

    TRACE(_T("没能获取相关数据"));
    return NULL;
}

//判断给定名字的pid是否有效, 用来判断是否进程退出了
DWORD ShareMem::IsPidValid(LPCTSTR lpszName)
{

    SHAREINFO* lpsa = Get(lpszName);
    if(lpsa == NULL) {
        return FALSE;
    }

    HANDLE hProcessSnap;
    PROCESSENTRY32 pe32;

    // Take a snapshot of all processes in the system.
    hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if(hProcessSnap == INVALID_HANDLE_VALUE) {
        return TRUE;
    }

    // Set the size of the structure before using it.
    pe32.dwSize = sizeof(PROCESSENTRY32);

    // Retrieve information about the first process,
    // and exit if unsuccessful
    if(!Process32First(hProcessSnap, &pe32)) {
        CloseHandle(hProcessSnap);          // clean the snapshot object
        return TRUE;
    }


    do {
        if(pe32.th32ProcessID == lpsa->pid) {
            return TRUE;
        }

    }
    while(Process32Next(hProcessSnap, &pe32));
    CloseHandle(hProcessSnap);
    return FALSE;
}

void ShareMem::Dump(DWORD dwPid)
{
    SHAREINFO* pSMem = Get(dwPid);
    if(pSMem) {
        TRACE(_T("进程: %d"), pSMem->pid);
        TRACE(_T("配置: %s"), pSMem->szConfig);
        TRACE(_T("账号: %s"), pSMem->szName);
        TRACE(_T("脚本: %s"), pSMem->szSript);
    }
}