// CDlgRegist.cpp : implementation file
//

#include "stdafx.h"
#include "Jlkit.h"
#include "JLkitSocket.h"
#include "RegistDlg.h"

#include "..\common\protocol.h"

#ifdef _DEBUG
    #define new DEBUG_NEW
#endif



CDlgRegist::CDlgRegist(CWnd* pParent /*=NULL*/)
    : CDialog(CDlgRegist::IDD, pParent)
{
    //{{AFX_DATA_INIT(CDlgRegist)
    // NOTE: the ClassWizard will add member initialization here
    //}}AFX_DATA_INIT

}


void CDlgRegist::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CDlgRegist)
    DDX_Text(pDX, IDC_EDITPASSWORD, m_strPw);
    DDX_Text(pDX, IDC_EDITUSERNAME, m_strName);
    DDX_Text(pDX, IDC_IPADDRESS, m_strIp);
    //}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgRegist, CDialog)
    //{{AFX_MSG_MAP(CDlgRegist)
    // NOTE: the ClassWizard will add message map macros here
    //}}AFX_MSG_MAP
    ON_WM_TIMER()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgRegist message handlers

void CDlgRegist::OnOK()
{
    // TODO: Add your specialized code here and/or call the base class
    UpdateData();

    if(m_strName.GetLength() > 10 || m_strPw.GetLength() > 10)
    {
        AfxMessageBox(_T("最长10个字符"));
        UpdateData(0);
        return;
    }

    if(m_strIp == _T("0.0.0.0") || m_strName.IsEmpty() || m_strPw.IsEmpty())
    {
        AfxMessageBox(_T("不能为空"));
    }
    else
    {
//        CJLkitSocket::GetInstance()->Register(m_strName, m_strPw, m_strIp);
    }


}


WORD CDlgRegist::ConstructRegisterPacket(BYTE cbBuffer[], WORD wBufferSize)
{

    REGIST_BUF* pBuffer = (REGIST_BUF*)cbBuffer;
    _tcsncpy(pBuffer->name, (LPCTSTR)m_strName, MAXLEN);
    _tcsncpy(pBuffer->pw, (LPCTSTR)m_strPw, MAXLEN);

    return sizeof(REGIST_BUF);
}


BOOL CDlgRegist::OnInitDialog()
{
    CDialog::OnInitDialog();

    // TODO:  Add extra initialization here


    return TRUE;  // return TRUE unless you set the focus to a control
    // EXCEPTION: OCX Property Pages should return FALSE
}
