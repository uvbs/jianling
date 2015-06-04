// Login.cpp : implementation file
//

#include "stdafx.h"
#include "JLkit.h"
#include "JLkitSocket.h"
#include "JLkitDoc.h"
#include "MainFrm.h"
#include "Logindlg.h"
#include "Registdlg.h"
#include "ConfigMgr.h"
#include "LoginSheet.h"

#ifdef _DEBUG
    #define new DEBUG_NEW
#endif


/////////////////////////////////////////////////////////////////////////////
// LoginDlg dialog


CDlgLogin::CDlgLogin(CWnd* pParent)
    : CPropertyPage(CDlgLogin::IDD)
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
    ON_WM_CREATE()
    ON_WM_CLOSE()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// LoginDlg message handlers

BOOL CDlgLogin::OnInitDialog()
{
    CDialog::OnInitDialog();


    //初始化登陆对话框
    m_bRemPw = CConfigMgr::GetInstance()->m_KeepPw;
    if(m_bRemPw)
    {
        m_strPw = CConfigMgr::GetInstance()->m_szAccountPw.c_str();
        m_strName = CConfigMgr::GetInstance()->m_szAccountName.c_str();
        UpdateData(FALSE);
    }

    return TRUE;
}

void CDlgLogin::OnOK()
{
    CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
    CJLkitDoc* pDoc = (CJLkitDoc*)pFrame->GetActiveDocument();

    UpdateData();
    if(m_bRemPw)
    {
        CConfigMgr::GetInstance()->m_szAccountName = m_strName;
        CConfigMgr::GetInstance()->m_szAccountPw = m_strPw;
        CConfigMgr::GetInstance()->m_KeepPw = m_bRemPw;
    }


    if(m_strName.GetLength() > 10 || m_strPw.GetLength() > 10)
    {
        AfxMessageBox(_T("用户名和密码最长十个字符"));
        return;
    }

    if(m_strName.IsEmpty() || m_strPw.IsEmpty())
    {
        AfxMessageBox(_T("用户名和密码不能空"));
        return;
    }
    else
    {
        pDoc->m_bRegister = false;
        pDoc->PerformLogonMission();
    }
}


WORD CDlgLogin::ConstructLoginPacket(BYTE cbBuffer[], WORD wBufferSize)
{

    LOGIN_BUF* pLoginBuf = (LOGIN_BUF*)cbBuffer;


    CWHService::GetMachineID(pLoginBuf->szMachineID);
    _tcsncpy(pLoginBuf->name, (LPCTSTR)m_strName, MAXLEN);
    _tcsncpy(pLoginBuf->pw, (LPCTSTR)m_strPw, MAXLEN);


    return sizeof(LOGIN_BUF);
}
