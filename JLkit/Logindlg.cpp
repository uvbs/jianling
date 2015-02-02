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
    DDX_Check(pDX, IDC_REMPASSWORD, bRemPw);
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
	if (dlg.DoModal() == IDOK)
	{
		//注册登录帐号
	}

}



void CDlgLogin::LoginResult(int nResult)
{

    if(nResult == result_ok){
        m_pSocket->Querykey();
        CDialog::OnOK();
    }
    else if(nResult == result_login_notuser){
        AfxMessageBox(_T("不存在的用户名"));
    }
    else if(nResult == result_login_pwerror){
        AfxMessageBox(_T("密码错误"));
    }
    else if(nResult == result_login_logined){
        AfxMessageBox(_T("帐号已经登录"));
    }
    
}



BOOL CDlgLogin::OnInitDialog()
{
	CDialog::OnInitDialog();

    //判断是否记住密码
    if(bRemPw){
        UpdateData(FALSE);
    }



	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgLogin::OnBtnModifybind()
{
	// TODO: Add your control notification handler code here
	CDlgModifyBind dlg;
	if(dlg.DoModal() == IDOK){
		//修改绑定信息
	}


}

void CDlgLogin::OnOK() 
{
    // TODO: Add extra validation here
    UpdateData();

    m_pDoc->m_bRememberPassWord = bRemPw;
    if(bRemPw){
        _tcscpy(m_pDoc->m_szAccountName, (LPCTSTR)m_strName);
        _tcscpy(m_pDoc->m_szAccountPw, (LPCTSTR)m_strPw);
        
    }
    
    CString strServer;
    strServer.LoadString(IDS_CONNECT_SERVER);
    while(1){
        m_pSocket->Close();
        if(m_pSocket->ConnectSrv(strServer, PORT_SRV) == FALSE){
            if(AfxMessageBox(IDS_RETRY_CONNECT, MB_YESNO) == IDNO)
                CDialog::OnCancel();
        }


        break;
 
    }

}


void CDlgLogin::ConnectResult(int nErrorCode)
{
    if(nErrorCode == 0){ 
        m_pSocket->LoginSrv(m_strName, m_strPw);
    }
    else{
        AfxMessageBox(_T("连接失败.."));
    }
    
}