// JLSrvr.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "JLSrvr.h"
#include "MainFrm.h"
#include "JLSrvrDoc.h"
#include "JLSrvrView.h"
#include "DbMngr.h"


#include "..\common\common.h"
#include "..\common\CallTracer.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CJLSrvrApp

BEGIN_MESSAGE_MAP(CJLSrvrApp, CWinApp)
    //{{AFX_MSG_MAP(CJLSrvrApp)
    ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
    // NOTE - the ClassWizard will add and remove mapping macros here.
    //    DO NOT EDIT what you see in these blocks of generated code!
    //}}AFX_MSG_MAP
    // Standard file based document commands
    ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
    ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CJLSrvrApp construction

CJLSrvrApp::CJLSrvrApp()
{
    // TODO: add construction code here,
    // Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CJLSrvrApp object

CJLSrvrApp theApp;


/////////////////////////////////////////////////////////////////////////////
// CJLSrvrApp initialization

BOOL CJLSrvrApp::InitInstance()
{

    AfxEnableControlContainer();
    if(!AfxSocketInit())
    {
        AfxMessageBox(IDS_SOCKET_INITFAIL);
        return FALSE;
    }

    char szhostName[BUFSIZ] = {0};
    int nOk =  gethostname(szhostName, BUFSIZ);
    if(nOk != 0)
    {
        DWORD dwLen = MAX_COMPUTERNAME_LENGTH + 1;
        GetComputerName(m_strDefSvr.GetBuffer(dwLen), &dwLen);
        m_strDefSvr.ReleaseBuffer();
        m_strDefSvr.MakeLower();
    }

    m_strDefSvr = szhostName;


    CSingleDocTemplate* pDocTemplate;
    pDocTemplate = new CSingleDocTemplate(
        IDR_MAINFRAME,
        RUNTIME_CLASS(CJLSrvrDoc),
        RUNTIME_CLASS(CMainFrame),
        RUNTIME_CLASS(CJLSrvrView));
    AddDocTemplate(pDocTemplate);
 
    CCommandLineInfo cmdInfo;
    ParseCommandLine(cmdInfo);

    if(!ProcessShellCommand(cmdInfo))
    {
        return FALSE;
    }

    return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
    CAboutDlg();

// Dialog Data
    //{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	CString	m_sockinfo;
	//}}AFX_DATA

    //²Ù×÷
    void sock_opt_print(int type, union opt_val* value, int len);

    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CAboutDlg)
protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL

// Implementation
protected:
    //{{AFX_MSG(CAboutDlg)
    virtual BOOL OnInitDialog();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
    //{{AFX_DATA_INIT(CAboutDlg)
	m_sockinfo = _T("");
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CAboutDlg)
	DDX_Text(pDX, IDC_STATIC_SOCKET, m_sockinfo);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
    //{{AFX_MSG_MAP(CAboutDlg)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

// App command to run the dialog
void CJLSrvrApp::OnAppAbout()
{
    CAboutDlg aboutDlg;
    aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CJLSrvrApp message handlers


BOOL CJLSrvrApp::OnIdle(LONG lCount)
{
    return CWinApp::OnIdle(lCount);
}

BOOL CAboutDlg::OnInitDialog()
{
    CDialog::OnInitDialog();

    return TRUE;  // return TRUE unless you set the focus to a control
    // EXCEPTION: OCX Property Pages should return FALSE
}
