// CDlgModifyBind.cpp : implementation file
//

#include "stdafx.h"
#include "JLkit.h"
#include "Modifybind.h"
#include "JLkitSocket.h"

#include "..\common\protocol.h"


// CDlgModifyBind dialog

CDlgModifyBind::CDlgModifyBind(CWnd* pParent /*=NULL*/)
    : CDialog(CDlgModifyBind::IDD, pParent)
{
    //{{AFX_DATA_INIT(CDlgModifyBind)
    m_strPw = _T("");
    m_strName = _T("");
    m_strOldbind = _T("");
    m_strNewbind = _T("");
    //}}AFX_DATA_INIT

}

CDlgModifyBind::~CDlgModifyBind()
{
}

void CDlgModifyBind::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CDlgModifyBind)
    DDX_Text(pDX, IDC_EDITPASSWORD, m_strPw);
    DDX_Text(pDX, IDC_EDITUSERNAME, m_strName);
    DDX_Text(pDX, IDC_OLDBIND, m_strOldbind);
    DDX_Text(pDX, IDC_NEWBIND, m_strNewbind);
    //}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgModifyBind, CDialog)
//{{AFX_MSG_MAP(CDlgModifyBind)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()


// CDlgModifyBind message handlers

void CDlgModifyBind::OnOK()
{
    // TODO: Add extra validation here
    UpdateData();

    if(m_strName.GetLength() > 10 || m_strPw.GetLength() > 10)
    {
        AfxMessageBox(_T("最长10个字符"));
        UpdateData(0);
        return;
    }



    if(m_strOldbind == _T("0.0.0.0") || m_strNewbind == _T("0.0.0.0") || m_strName.IsEmpty() ||
            m_strPw.IsEmpty())
        AfxMessageBox(_T("不能为空"));
    else
        CJLkitSocket::GetInstance()->ModifyBind(m_strName, m_strPw, m_strOldbind, m_strNewbind);

    CDialog::OnOK();
}
