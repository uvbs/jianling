// LaunchGameThread.cpp : implementation file
//

#include "stdafx.h"
#include "jlkit.h"
#include "LaunchGameThread.h"
#include "JLkitView.h"
#include "JLkitDoc.h"


#include "..\common\webpost.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLaunchGameThread

IMPLEMENT_DYNCREATE(CLaunchThread, CWinThread)

CLaunchThread::CLaunchThread()
{
    m_bIsWorking = FALSE;
    m_bStop = FALSE;
}

CLaunchThread::~CLaunchThread()
{
    m_bStop = TRUE;
    
    CloseHandle(hEventObj);
}


BEGIN_MESSAGE_MAP(CLaunchThread, CWinThread)
    //{{AFX_MSG_MAP(CLaunchThread)
    // NOTE - the ClassWizard will add and remove mapping macros here.
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()



/////////////////////////////////////////////////////////////////////////////
// CLaunchGameThread message handlers

BOOL CLaunchThread::AddWork(FUNCID id)
{

    //先判断当前是否工作
    if(isWorking())
    {
        return FALSE;
    }

    //激活等待的事件
    m_nFuncid = id;
    SetEvent(hEventObj);
    TRACE(_T("AddWork Done."));
    return TRUE;
}

BOOL CLaunchThread::isWorking()
{
    return m_bIsWorking;
};


int CLaunchThread::Run()
{
    // TODO: Add your specialized code here and/or call the base class
    if(m_pView == NULL)
    {
        return -1;
    }


    while(m_bStop == FALSE)
    {
        TRACE(_T("waiting..."));
        if(WaitForSingleObject(hEventObj, INFINITE) == WAIT_OBJECT_0)
        {
            m_bIsWorking = TRUE;

            if(m_nFuncid == LAUNCHGAME)
            {
                m_pView->LaunchGame();
            }
            else if(m_nFuncid == GET)
            {
                m_pView->OnGet();
            }
            else if(m_nFuncid == ACTIVE)
            {
                m_pView->OnActive();
            }
            else if(m_nFuncid == GETANDACTIVE)
            {
                m_pView->OnGetAndActive();
            }


            m_bIsWorking = FALSE;
        }
    }

    return 0;
}

BOOL CLaunchThread::InitInstance()
{
    // TODO: Add your specialized code here and/or call the base class

    //初始化事件对象
    hEventObj = CreateEvent(NULL, FALSE, FALSE, NULL);


    CWinThread::InitInstance();
    return TRUE;
}
