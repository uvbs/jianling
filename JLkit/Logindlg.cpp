// Login.cpp : implementation file
//

#include "stdafx.h"
#include "JLkit.h"
#include "JLkitSocket.h"
#include "JLkitDoc.h"
#include "Logindlg.h"
#include "Registdlg.h"
#include "Modifybind.h"


#include "..\common\Userinfo.h"
#include "..\common\protocol.h"
#include "..\common\Webpost.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



/////////////////////////////////////////////////////////////////////////////
// LoginDlg dialog


CDlgLogin::CDlgLogin(CJLkitDoc* pDoc)
    : CDialog(CDlgLogin::IDD, NULL)
{
    //{{AFX_DATA_INIT(LoginDlg)
    m_strName = _T("");
    m_strPw = _T("");
    //}}AFX_DATA_INIT

    m_pDoc = pDoc;
    m_pSocket = pDoc->m_pSocket;
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
    if(dlg.DoModal() == IDOK)
    {
        //ע���¼�ʺ�
    }

}



void CDlgLogin::LoginResult(int nResult)
{

    if(nResult == result_ok)
    {
        m_pSocket->Querykey();
        CDialog::OnOK();
    }
    else if(nResult == result_login_notuser)
    {
        AfxMessageBox(_T("�����ڵ��û���"));
    }
    else if(nResult == result_login_pwerror)
    {
        AfxMessageBox(_T("�������"));
    }
    else if(nResult == result_login_logined)
    {
        AfxMessageBox(_T("�ʺ��Ѿ���¼"));
    }

}



BOOL CDlgLogin::OnInitDialog()
{
    CDialog::OnInitDialog();
    UpdateData(FALSE);


    return TRUE;  // return TRUE unless you set the focus to a control
    // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgLogin::OnBtnModifybind()
{
    // TODO: Add your control notification handler code here
    CDlgModifyBind dlg;
    if(dlg.DoModal() == IDOK)
    {
        //�޸İ���Ϣ
    }


}

void CDlgLogin::OnOK()
{
    // TODO: Add extra validation here
    UpdateData(TRUE);
    m_pSocket->LoginSrv(m_strName, m_strPw);

}
