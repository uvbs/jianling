// ThreadPool.cpp: implementation of the CThreadPool class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ThreadPool.h"
#include "Lock.h"

#include <process.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif




//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CThreadPool::CThreadPool(int max)
{
    nMaxThraeds = max;
    phThreads = NULL;
    pQueue = NULL;
    m_lpLock = new CLock();
}
CThreadPool::~CThreadPool()
{
    Close();
};
	

BOOL CThreadPool::Init()
{
	phThreads = new HANDLE[nMaxThraeds];
	pQueue = new WorkQueue;


	//创建信号量 
	hSyncObj[SEMAPHORE_INDEX] = CreateSemaphore(NULL, 0, LONG_MAX, NULL);
	if(hSyncObj[SEMAPHORE_INDEX] == NULL)     
		return FALSE;

	hSyncObj[ABORT_EVENT_INDEX] = CreateEvent(NULL, TRUE, FALSE, NULL);	//同步对象
	if(hSyncObj[ABORT_EVENT_INDEX] == NULL)
		return FALSE;

	for(unsigned i = 0; i < nMaxThraeds; i++){
        phThreads[i] = (HANDLE)_beginthreadex(0, 0, ThreadProc, this, 0, 0);
		if(phThreads[i] == NULL){
			nMaxThraeds = i;
			break;
		}
	}

	return TRUE;
}

UINT CThreadPool::ThreadProc(void *pParam)
{
	CThreadPool *pool = (CThreadPool *)pParam;
	DWORD dwWaitRet;
	for(;;){

		dwWaitRet = WaitForMultipleObjects(NUMBER_OF_SYNC_OBJ, pool->hSyncObj, FALSE, INFINITE);
		switch(dwWaitRet - WAIT_OBJECT_0){
		case ABORT_EVENT_INDEX:
			return 0;

		case SEMAPHORE_INDEX:
			CWork *work = pool->DelWork();
			work->DoWork();
		}

	}

	return 0;
}

BOOL CThreadPool::AddWork(CWork *work) //开始一个工作线程
{
    pQueue->push(work);
	if (!ReleaseSemaphore(hSyncObj[SEMAPHORE_INDEX], 1, NULL)) 
		return FALSE;    

	return TRUE;
}

CWork* CThreadPool::DelWork()
{
	CWork *work;

	m_lpLock->lock();
	work = pQueue->front();
	pQueue->pop();
	m_lpLock->unlock();
	
	return work;
}

void CThreadPool::Close()
{
    delete m_lpLock;
	delete pQueue;

	if(!SetEvent(hSyncObj[ABORT_EVENT_INDEX]))
		return;//失败
	
	WaitForMultipleObjects(nMaxThraeds, phThreads, TRUE, 5000);


	while(!pQueue->empty()){
		CWork *pWork = pQueue->front();
		pQueue->pop();
		delete pWork;
	}
	delete []phThreads;

	for(unsigned i = 0; i< NUMBER_OF_SYNC_OBJ; i++){
		CloseHandle(hSyncObj[i]);
	}
}
