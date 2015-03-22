// JLSrvr.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "JLSrvr.h"
#include "MainFrm.h"
#include "JLSrvrDoc.h"
#include "JLSrvrView.h"
#include "DbMngr.h"
#include "sockinfo.h"


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


void CJLSrvrApp::ShowFrame(LPCTSTR szText, PVOID pParam)
{
    OutputDebugString(szText);
}


//异常处理
LONG CALLBACK CJLSrvrApp::myUnhandledExceptionFilter(EXCEPTION_POINTERS* lpExceptionInfo)
{
    CCallTracer tracer;
    tracer.WalkStack(ShowFrame, 0, 20, lpExceptionInfo->ContextRecord);
    return 0;
}


/////////////////////////////////////////////////////////////////////////////
// CJLSrvrApp initialization

BOOL CJLSrvrApp::InitInstance()
{
    AfxEnableControlContainer();

    SetUnhandledExceptionFilter(myUnhandledExceptionFilter);

    if(!AfxSocketInit())
    {
        AfxMessageBox(IDS_SOCKET_INITFAIL);
        return FALSE;
    }

    // try to get the default host name....
    char szhostName[BUFSIZ] = {0};
    int nOk =  gethostname(szhostName, BUFSIZ);
    if(nOk != 0)
    {
        // get the computer server name....
        DWORD dwLen = MAX_COMPUTERNAME_LENGTH + 1;
        GetComputerName(m_strDefSvr.GetBuffer(dwLen), &dwLen);
        m_strDefSvr.ReleaseBuffer();
        // all lower-case....
        m_strDefSvr.MakeLower();
    }

    m_strDefSvr = szhostName;

    // Standard initialization
    // If you are not using these features and wish to reduce the size
    //  of your final executable, you should remove from the following
    //  the specific initialization routines you do not need.

#ifdef _AFXDLL
    Enable3dControls();         // Call this when using MFC in a shared DLL
#else
    Enable3dControlsStatic();   // Call this when linking to MFC statically
#endif


    //初始化数据库
    if(!CDbMngr::GetInstance()->Init())
        return FALSE;


    // Change the registry key under which our settings are stored.
    // TODO: You should modify this string to be something appropriate
    // such as the name of your company or organization.
    SetRegistryKey(_T("Local AppWizard-Generated Applications"));

    LoadStdProfileSettings();  // Load standard INI file options (including MRU)

    // Register the application's document templates.  Document templates
    //  serve as the connection between documents, frame windows and views.

    CSingleDocTemplate* pDocTemplate;
    pDocTemplate = new CSingleDocTemplate(
        IDR_MAINFRAME,
        RUNTIME_CLASS(CJLSrvrDoc),
        RUNTIME_CLASS(CMainFrame),       // main SDI frame window
        RUNTIME_CLASS(CJLSrvrView));
    AddDocTemplate(pDocTemplate);


    // Parse command line for standard shell commands, DDE, file open
    CCommandLineInfo cmdInfo;
    ParseCommandLine(cmdInfo);

    // Dispatch commands specified on the command line
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

    //操作
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

void CAboutDlg::sock_opt_print(int type, union opt_val* value, int len)
{
    BOOL b_val;
    int i_val;
    unsigned char c_val;
    struct linger lng;
    CString strValue;

    //printf("len = %d, ", len);
    switch(type)
    {

        case VBOOL:
            b_val = value->b_value;

            strValue.Format(_T("%s"), b_val ? _T("on") : _T("off"));
            break;

        case VCHAR:
            c_val = value->c_value;
            strValue.Format(_T("%s"), c_val ? _T("on") : _T("off"));
            break;

        case VINTG:
            i_val = value->i_value;
            strValue.Format(_T("%d"), i_val);
            break;

        case VLGER:
            lng = value->linger;
            strValue.Format(_T("l_onoff = %d, l_linger = %d"), lng.l_onoff, lng.l_linger);
            break;

        default:
            break;
    }

    m_sockinfo += strValue;
    m_sockinfo += _T("\r\n");
}

BOOL CAboutDlg::OnInitDialog()
{
    CDialog::OnInitDialog();

    SOCKET	udp_soc, tcp_soc, soc; /* socket 句柄 */
    union opt_val value;
    int i, result, val_len;
    int opt_cnt = sizeof(sock_opt_g) / sizeof(sock_opt_g[0]);
    struct sock_opt* popt;

    udp_soc = socket(AF_INET, SOCK_DGRAM, 0);
    tcp_soc = socket(AF_INET, SOCK_STREAM, 0);

    m_sockinfo += ("[GetOpt] Get socket default option:\r\n");
    for(i = 0; i < opt_cnt; i++)
    {
        popt = &sock_opt_g[i];
        CString strName;
        strName.Format(_T("%-20s : "), popt->name);
        m_sockinfo += strName;
        val_len = sizeof(value);

        soc = (popt->protocol ? tcp_soc : udp_soc);
        result = getsockopt(soc, popt->level, popt->option,
                            (char*)&value, &val_len);
        if(result == SOCKET_ERROR)
        {
            printf("fails to getsockopt\n");
        }
        else
        {
            sock_opt_print(popt->type, &value, val_len);
        }
    }

    UpdateData(FALSE);

    return TRUE;  // return TRUE unless you set the focus to a control
    // EXCEPTION: OCX Property Pages should return FALSE
}
