// Login.cpp : implementation file
//

#include "stdafx.h"
#include "JLkit.h"
#include "JLkitSocket.h"
#include "JLkitDoc.h"
#include "MainFrm.h"
#include "Logindlg.h"
#include "Registdlg.h"
#include "Modifybind.h"
#include "ConfigMgr.h"


#ifdef _DEBUG
    #define new DEBUG_NEW
#endif


/////////////////////////////////////////////////////////////////////////////
// LoginDlg dialog


CDlgLogin::CDlgLogin(CWnd* pParent)
    : CDialog(CDlgLogin::IDD, pParent)
{
    //{{AFX_DATA_INIT(LoginDlg)
    m_strName = _T("");
    m_strPw = _T("");
    m_bRemPw = TRUE;
    //}}AFX_DATA_INIT
}


void CDlgLogin::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CDlgLogin)
    DDX_Text(pDX, IDC_EDITNAME, m_strName);
    DDX_Text(pDX, IDC_EDITPASSWORD, m_strPw);
    DDX_Check(pDX, IDC_REMPASSWORD, m_bRemPw);
    //}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgLogin, CDialog)
    //{{AFX_MSG_MAP(CDlgLogin)
    ON_BN_CLICKED(IDC_BUTTONREGISTER, OnBtnRegister)
    ON_BN_CLICKED(IDC_BTNMODIFYBIND, OnBtnModifybind)
    ON_WM_CREATE()
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// LoginDlg message handlers

void CDlgLogin::OnBtnRegister()
{
    CMainFrame *pFrame = (CMainFrame *)AfxGetMainWnd();
    CJLkitDoc* pDoc = (CJLkitDoc *)pFrame->GetActiveDocument();
    pDoc->ShowRegister();
}


BOOL CDlgLogin::OnInitDialog()
{
    CDialog::OnInitDialog();

    
    //¼ÓÔØÍ¼±ê
    SetIcon(AfxGetApp()->LoadIcon(IDR_MAINFRAME), FALSE);
    

    //½¹µã
    if(m_strName.IsEmpty())
    {
        GetDlgItem(IDC_EDITNAME)->SetFocus();
    }
    else
    {
        GetDlgItem(IDOK)->SetFocus();
    }


    return FALSE;  // return TRUE unless you set the focus to a control
    // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgLogin::OnBtnModifybind()
{
    CMainFrame *pFrame = (CMainFrame *)AfxGetMainWnd();
    CJLkitDoc* pDoc = (CJLkitDoc *)pFrame->GetActiveDocument();
    pDoc->ShowModiBind();
}

void CDlgLogin::OnOK()
{
    ShowWindow(SW_HIDE);

    CMainFrame *pFrame = (CMainFrame *)AfxGetMainWnd();
    CJLkitDoc* pDoc = (CJLkitDoc *)pFrame->GetActiveDocument();
    pDoc->PerformLogonMission();
}


WORD CDlgLogin::ConstructLoginPacket( BYTE cbBuffer[], WORD wBufferSize )
{
    ASSERT(this != NULL);


    LOGIN_BUF* pLoginBuf = (LOGIN_BUF*)cbBuffer;


    CWHService::GetMachineID(pLoginBuf->szMachineID);
    _tcsncpy(pLoginBuf->name, (LPCTSTR)m_strName, MAXLEN);
    _tcsncpy(pLoginBuf->pw, (LPCTSTR)m_strPw, MAXLEN);


    return sizeof(LOGIN_BUF);
}

void CDlgLogin::OnClose() 
{
    AfxGetMainWnd()->DestroyWindow();
	CDialog::OnClose();
}
