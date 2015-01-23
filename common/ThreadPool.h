// ThreadPool.h: interface for the CThreadPool class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_THREADPOOL_H__4B5D5C10_515D_433B_85AD_4C1E45ACD20D__INCLUDED_)
#define AFX_THREADPOOL_H__4B5D5C10_515D_433B_85AD_4C1E45ACD20D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CWork;
class CLock;
class CThreadPool
{
public:
    CThreadPool(int max = 1);
    ~CThreadPool();
	
    //�̺߳���
	static UINT CALLBACK ThreadProc(void *pParam);

	void SetMaxThreads(int nMax){
		nMaxThraeds = nMax;
	};

    int GetThreadsCounts(){
        return nMaxThraeds;
    }

    HANDLE* GetThreadHandle(){
        return phThreads;
    }


	BOOL Init();	//��ʼ��
	void Close();	//�ͷ���Դ
	
	BOOL AddWork(CWork *work);	//����һ�������߳�
	CWork* DelWork();			//ɾ��һ�������߳�
	
private:
	CLock* m_lpLock;
	int nMaxThraeds;

	enum{
		ABORT_EVENT_INDEX = 0,
		SEMAPHORE_INDEX,
		NUMBER_OF_SYNC_OBJ,
	};

	HANDLE hSyncObj[NUMBER_OF_SYNC_OBJ];//ͬ������
	HANDLE *phThreads;

    typedef std::queue<CWork *>	WorkQueue, *PWorkQueue;
	WorkQueue *pQueue;
};




#endif // !defined(AFX_THREADPOOL_H__4B5D5C10_515D_433B_85AD_4C1E45ACD20D__INCLUDED_)
