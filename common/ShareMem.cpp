// ShareMem.cpp: implementation of the ShareMem class.
//
//////////////////////////////////////////////////////////////////////

#include "StdAfx.h"
#include "..\common\logger.h"
#include "ShareMem.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ShareMem::ShareMem(HANDLE hFileMap)
{
    m_hFileMap = hFileMap;
    m_lpMem = NULL;
    m_dwMaxCount = 0;
}


SHAREINFO* ShareMem::IsLogined(DWORD pid)
{
	SHAREINFO *share = GetMemAddr();

    for(unsigned i = 0; i < m_dwMaxCount; i++){
        if(share->pid == pid){
            return share;
        }
    }

	return NULL;

}



//判断一个名称是否已经存在
SHAREINFO* ShareMem::IsLogined(const char *name)
{
    
    SHAREINFO *share = GetMemAddr();

    for(unsigned i = 0; i < m_dwMaxCount; i++){
        if(strcmp(share->szName, name) == 0){
            return share;
        }
    }

    return NULL;
}


//创建和打开通用, 0是打开, > 0是创建
//当打开时, 对象大小不是指定的大小
BOOL ShareMem::Create(DWORD dwCount, TCHAR szObjName[])
{

	BOOL bRet = FALSE;

    __try
    {
        
        DWORD MemSize = dwCount * sizeof(SHAREINFO) + sizeof(DWORD);
        
        
        //创建共享对象
        m_hFileMap = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, MemSize, szObjName);
        if(m_hFileMap == NULL) __leave;
        
        m_lpMem = (SHAREINFO *)MapViewOfFile(m_hFileMap, FILE_MAP_ALL_ACCESS, 0, 0, 0);
        if(m_lpMem == NULL) __leave;
        
        
        ZeroMemory(m_lpMem, MemSize);
        *(DWORD *)m_lpMem = MemSize;
        m_lpMem = (SHAREINFO *)((DWORD)m_lpMem + sizeof(DWORD));
        m_dwMaxCount = dwCount;
        
        bRet = TRUE;
        
    }
	__finally
	{
		if(bRet == FALSE){
			if(m_hFileMap != NULL){
				CloseHandle(m_hFileMap);
				m_hFileMap = NULL;
			}
			
			if(m_lpMem){
				UnmapViewOfFile(m_lpMem);
				m_lpMem = NULL;
			}
		}
		
	}


	return bRet;
}

void ShareMem::Close()
{
	if(m_lpMem != NULL){
		m_lpMem = (SHAREINFO *)((DWORD)m_lpMem - sizeof(DWORD));
		UnmapViewOfFile(m_lpMem);
		m_lpMem = NULL;
	}
	
	
	if(m_hFileMap != NULL){
		CloseHandle(m_hFileMap);
		m_hFileMap = NULL;
	}

    m_dwMaxCount = 0;
}


ShareMem::~ShareMem()
{
	Close();
}


SHAREINFO* ShareMem::Add(SHAREINFO *pShareInfo)
{

    SHAREINFO *pItor = m_lpMem;

    for(DWORD i = 0; i < m_dwMaxCount; i++){
        if(pItor->pid == 0){
			memcpy((void *)pItor, (void *)pShareInfo, sizeof(SHAREINFO));
            break;
        }
    
        pItor++;
    }

	return pItor;
}


void ShareMem::Del(const char *name)
{
    
    SHAREINFO *pItor = IsLogined(name);
    if(pItor != NULL){
        ZeroMemory(pItor, sizeof(SHAREINFO));
    }

}


void ShareMem::Del(DWORD dwPid)
{
    
    SHAREINFO *pItor = m_lpMem;

    for(DWORD i = 0; i < m_dwMaxCount; i++){
        if(pItor->pid == dwPid){
            ZeroMemory(pItor, sizeof(SHAREINFO));
            break;
        }

        pItor++;
    
    }
}



//获取已经登录的个数
DWORD ShareMem::GetLoginedCount()
{

    if(m_lpMem == NULL)
        return 0;

	DWORD count = 0;
	SHAREINFO *pItor = m_lpMem;
	for(DWORD i = 0; i < m_dwMaxCount; i++){
		if(pItor->pid != 0){
			count++;
		}

		pItor++;
	}
	
	return count;
}





//获取指定的共享数据
SHAREINFO* ShareMem::Get(DWORD dwPid)
{
	if(m_lpMem == NULL ||
		m_hFileMap == NULL){
		return NULL;
	}


	SHAREINFO *pItor = m_lpMem;
	for(DWORD i = 0; i < m_dwMaxCount; i++){
		if(pItor->pid == dwPid){
			return pItor;
		}

		pItor++;
	}

	return NULL;
}

BOOL ShareMem::Open(TCHAR szObjName[])
{
    BOOL bRet = FALSE;
    __try{
        m_hFileMap = OpenFileMapping(FILE_MAP_ALL_ACCESS, FALSE, szObjName);
        if(m_hFileMap == NULL) __leave;
        
        m_lpMem = (SHAREINFO *)MapViewOfFile(m_hFileMap, FILE_MAP_ALL_ACCESS, 0, 0, 0);
        if(m_lpMem == NULL) __leave;
        
        int MemSize = *(DWORD *)m_lpMem;
        m_lpMem = (SHAREINFO *)((DWORD)m_lpMem + sizeof(DWORD));
        m_dwMaxCount = (MemSize - sizeof(DWORD))/sizeof(SHAREINFO);   
        bRet = TRUE;
    }
    __finally{
        if(bRet == FALSE){
            if(m_hFileMap != NULL){
                CloseHandle(m_hFileMap);
                m_hFileMap = NULL;
            }
            
            if(m_lpMem){
                UnmapViewOfFile(m_lpMem);
                m_lpMem = NULL;
            }
        }
        
    }
    
    return bRet;
}

//判断给定名字的pid是否有效, 用来判断是否进程退出了
DWORD ShareMem::IsPidValid( const char* name )
{
    SHAREINFO* lpsa = IsLogined(name);
    if(lpsa == NULL)
        return 0;


    HANDLE hProcessSnap;
    PROCESSENTRY32 pe32;
    
    // Take a snapshot of all processes in the system.
    hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if(hProcessSnap == INVALID_HANDLE_VALUE){
        return TRUE;
    }
    
    // Set the size of the structure before using it.
    pe32.dwSize = sizeof( PROCESSENTRY32 );
    
    // Retrieve information about the first process,
    // and exit if unsuccessful
    if(!Process32First(hProcessSnap, &pe32)){
        CloseHandle(hProcessSnap);          // clean the snapshot object
        return TRUE;
    }
    
    
    do{
        if(pe32.th32ProcessID == lpsa->pid){
            return TRUE;
        }
        
    } 
    while(Process32Next(hProcessSnap, &pe32));
    CloseHandle(hProcessSnap);
    return FALSE;
    
    
}