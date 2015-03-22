// Login.cpp : implementation file
//

#include "stdafx.h"
#include "JLkit.h"
#include "JLkitSocket.h"
#include "JLkitDoc.h"
#include "Logindlg.h"
#include "Registdlg.h"
#include "Modifybind.h"
#include "ConfigMgr.h"

#include "..\common\protocol.h"
#include "..\common\Webpost.h"


#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif



/////////////////////////////////////////////////////////////////////////////
// LoginDlg dialog


CDlgLogin::CDlgLogin()
    : CDialog(CDlgLogin::IDD, NULL)
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
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// LoginDlg message handlers

void CDlgLogin::OnBtnRegister()
{
    CDlgRegist dlg;

    ShowWindow(SW_HIDE);
    if(dlg.DoModal() == IDOK) {
        //ע���¼�ʺ�
    }

    ShowWindow(SW_SHOW);
}

void CDlgLogin::LoginResult(int nResult)
{
    if(nResult == result_ok) {
        CJLkitSocket::GetInstance()->Querykey();
        CDialog::OnOK();
    }
    else if(nResult == result_login_notuser)
        AfxMessageBox(_T("�����ڵ��û���"));
    else if(nResult == result_login_pwerror)
        AfxMessageBox(_T("�������"));
    else if(nResult == result_login_logined)
        AfxMessageBox(_T("�ʺ��Ѿ���¼"));

    GetDlgItem(IDOK)->EnableWindow();
}



BOOL CDlgLogin::OnInitDialog()
{
    CDialog::OnInitDialog();

    //������ù�����
    CConfigMgr* pConfigMgr = CConfigMgr::GetInstance();

    //��ʼ����½�Ի���
    m_bRemPw = pConfigMgr->m_KeepPw;
    if(m_bRemPw) {
        m_strPw = pConfigMgr->m_szAccountPw;
        m_strName = pConfigMgr->m_szAccountName;
    }

    UpdateData(FALSE);
    return TRUE;  // return TRUE unless you set the focus to a control
    // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgLogin::OnBtnModifybind()
{
    // TODO: Add your control notification handler code here
    CDlgModifyBind dlg;
    ShowWindow(SW_HIDE);
    if(dlg.DoModal() == IDOK) {
        //�޸İ���Ϣ
    }
    ShowWindow(SW_SHOW);
}

void CDlgLogin::OnOK()
{
    UpdateData();

    int nRet = CJLkitSocket::GetInstance()->LoginSrv(m_strName, m_strPw);
    if(nRet == SOCKET_ERROR)
        GetDlgItem(IDOK)->EnableWindow();

    //������ù�����
    CConfigMgr* pConfigMgr = CConfigMgr::GetInstance();

    //��������
    if(m_bRemPw) {
        _tcscpy(pConfigMgr->m_szAccountName, (LPCTSTR)m_strName);
        _tcscpy(pConfigMgr->m_szAccountPw, (LPCTSTR)m_strPw);
    }
    pConfigMgr->m_KeepPw = m_bRemPw;


}

void CDlgLogin::ConnectResult(int nErrorCode)
{
    if(nErrorCode == 0)
        GetDlgItem(IDOK)->EnableWindow();
    else
        AfxMessageBox(_T("�޷����ӵ�������"));
}