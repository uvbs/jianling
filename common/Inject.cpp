// inject.cpp: implementation of the Inject class.
//
//////////////////////////////////////////////////////////////////////
#include "StdAfx.h"
#include "../common/Toolhelp.h"
#include "../common/logger.h"
#include "inject.h"


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCInject::CCInject(const char* name)
{

	int len = strlen(name) + 1;

	m_pathlen = len;
	m_path = new char[len];
	ZeroMemory(m_path, len);
	strcpy(m_path, name);


	process = INVALID_HANDLE_VALUE;
	mem = NULL;
}

BOOL CCInject::Call(TCHAR szCall[], LPVOID lpParam)
{

	
	return FALSE;
}


BOOL CCInject::InjectTo(DWORD pid)
{
	//��Ŀ�����

	HANDLE thread = NULL;
	
	BOOL bRet = FALSE;

	__try
	{
		process = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_CREATE_THREAD
			| PROCESS_VM_OPERATION | PROCESS_VM_WRITE, false, pid);
		
		if(process == NULL) __leave;
		
		//ȡ��·����С
		unsigned long cb = m_pathlen;
		
		//��Զ�����������ڴ�
		mem = VirtualAllocEx(process, NULL, m_pathlen, 
			MEM_COMMIT, PAGE_READWRITE);
		if(mem == NULL) __leave;
		
		//д�뵽Զ����
		int result = WriteProcessMemory(process, mem, (void *)m_path, m_pathlen, &cb);
		if(result == 0) __leave;
		
	
		//��Զ�����д����߳�
		pfnLoadLibraryA = (PTHREAD_START_ROUTINE)GetProcAddress(GetModuleHandle(_T("kernel32")),
			"LoadLibraryA");
		if(pfnLoadLibraryA == NULL) __leave;

		
		thread = CreateRemoteThread(process, NULL, 0, pfnLoadLibraryA, mem, 0, NULL);
		if(thread == NULL) __leave;
		

		//�ȴ�Զ�߳�ִ����
		WaitForSingleObject(thread, INFINITE);

		bRet = TRUE;
	}
	__finally
	{	
		if(mem != NULL)
		{
			VirtualFreeEx(process, mem, 0, MEM_RELEASE);
		}
		
		if(thread != NULL)
		{
			CloseHandle(thread);
		}
	
		if(process != NULL)
		{
			CloseHandle(process);
		}
	
	}

	return bRet;
}

BOOL CCInject::InjectTo( TCHAR szProcess[] )
{
    //ö�ٵ�ǰ�����б�
    
    HANDLE hProcessSnap;
    PROCESSENTRY32 pe32;
    
    // Take a snapshot of all processes in the system.
    hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if(hProcessSnap == INVALID_HANDLE_VALUE){
        return TRUE;
    }
    
    // Set the size of the structure before using it.
    pe32.dwSize = sizeof(PROCESSENTRY32);
    
    // Retrieve information about the first process,
    // and exit if unsuccessful
    if(!Process32First(hProcessSnap, &pe32)){
        CloseHandle(hProcessSnap);// clean the snapshot object
        return TRUE;
    }
    
    
    do{
        if(_tcscmp(pe32.szExeFile, szProcess) == 0){
            return InjectTo(pe32.th32ProcessID);
        }
        
    } 
    while( Process32Next( hProcessSnap, &pe32 ) );
    
    CloseHandle(hProcessSnap);
    return FALSE;


}