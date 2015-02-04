// JLkit.cpp : Defines the class behaviors for the application.
//
#include "stdafx.h"
#include "JLkit.h"
#include "MainFrm.h"
#include "JLkitView.h"
#include "JLkitDoc.h"
#include "JLkitSocket.h"

#include "../common/logger.h"
#include "../common/protocol.h"
#include "../common/ShareMem.h"
#include "../common/common.h"

#ifdef _DEBUG
	#define new DEBUG_NEW
#endif

/////////////////////////////////////////////////////////////////////////////
// CJLkitApp
BEGIN_MESSAGE_MAP(CJLkitApp, CWinApp)
//{{AFX_MSG_MAP(CJLkitApp)
	ON_COMMAND(ID_APP_EXIT, OnAppExit)
	ON_COMMAND(ID_FILE_NEW, OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, OnFileOpen)
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////

// CJLkitApp construction
CJLkitApp::CJLkitApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/* */
CJLkitApp::~CJLkitApp()
{
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CJLkitApp object
CJLkitApp	theApp;

/////////////////////////////////////////////////////////////////////////////

// CJLkitApp initialization
BOOL CJLkitApp::InitInstance()
{
	// 	::CreateMutex(NULL, FALSE, _T("JLkit_Mutex"));
	// 	if(GetLastError() == ERROR_ALREADY_EXISTS){
	// 		AfxMessageBox(_T("这个程序已经在执行"));
	// 		return FALSE;	
	// 	}
	if(LoadLibrary(_T("JLnp")) == NULL)
	{
		AfxMessageBox(_T("没有找到 JLNP.DLL"));
		return FALSE;
	}

	if(!AfxSocketInit())
	{
		AfxMessageBox(IDP_SOCKETS_INIT_FAIL);
		return FALSE;
	}

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.
	LoadStdProfileSettings();

	CSingleDocTemplate*		pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(IDR_MAINFRAME, RUNTIME_CLASS(CJLkitDoc), RUNTIME_CLASS(CMainFrame), // main SDI frame window
	RUNTIME_CLASS(CJLkitView));
	AddDocTemplate(pDocTemplate);

	OnFileNew();

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////

// CJLkitApp message handlers
BOOL CJLkitApp::OnIdle(LONG lCount)
{
	BOOL	bMore = CWinApp::OnIdle(lCount);

	// if we still need more processing time, ask for it...
	return bMore;

}
