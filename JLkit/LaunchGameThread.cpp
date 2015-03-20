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
}

CLaunchThread::~CLaunchThread()
{
    StopThread();

    for(int i = 0; i < sizeof(m_phEvents) / sizeof(HANDLE); i++)
    {
        CloseHandle(m_phEvents[i]);
    }
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
    SetEvent(m_phEvents[work]);
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

    Webpost::InitCom();
    while(1)
    {
        //这里同时等待多个对象
        //其中一个停止事件, 用来通知现成退出.
        //解决程序无法正常关闭的问题

        DWORD dwRet = WaitForMultipleObjects(sizeof(m_phEvents) / sizeof(HANDLE),
                                             m_phEvents, FALSE, INFINITE);
        if(dwRet == WAIT_OBJECT_0)
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
                m_pView->GetAndActive();
            }


            m_bIsWorking = FALSE;
        }
        else if(dwRet == WAIT_OBJECT_0 + 1)
        {
            break;
        }
    }

    Webpost::InitCom();
    return 0;
}

BOOL CLaunchThread::InitInstance()
{
    // TODO: Add your specialized code here and/or call the base class

    //初始化事件对象
    m_phEvents[work] = CreateEvent(NULL, FALSE, FALSE, NULL);
    m_phEvents[stop] = CreateEvent(NULL, FALSE, FALSE, NULL);

    CWinThread::InitInstance();
    return TRUE;
}

void CLaunchThread::StopThread()
{
    SetEvent(m_phEvents[stop]);
}

void CLaunchThread::SetOwner(CJLkitView* pOwner)
{
    m_pView = pOwner;
}