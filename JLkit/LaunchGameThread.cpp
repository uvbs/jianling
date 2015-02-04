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
    m_bAutoDelete = FALSE;
    m_bIsWorking = FALSE;
}

CLaunchThread::~CLaunchThread()
{
}


BEGIN_MESSAGE_MAP(CLaunchThread, CWinThread)
	//{{AFX_MSG_MAP(CLaunchThread)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()



/////////////////////////////////////////////////////////////////////////////
// CLaunchGameThread message handlers


int CLaunchThread::Run() 
{
    // TODO: Add your specialized code here and/or call the base class
    if(m_pView == NULL)
        return -1;


    while(1)
    {
        m_bIsWorking = TRUE;
        m_pView->LaunchGame();

    }

    return 0;
}

BOOL CLaunchThread::InitInstance() 
{
	// TODO: Add your specialized code here and/or call the base class
	
	CWinThread::InitInstance();
    return TRUE;
}
