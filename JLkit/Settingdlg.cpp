// SettingDlg.cpp : implementation file
//

#include "stdafx.h"
#include "jlkit.h"
#include "Settingdlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

/////////////////////////////////////////////////////////////////////////////
// SettingDlg dialog

SettingDlg::SettingDlg(CWnd* pParent /*=NULL*/)
	: CDialog(SettingDlg::IDD, pParent)
{
    m_strGamePath = _T("");
}

void SettingDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);

    //{{AFX_DATA_MAP(SettingDlg)
    DDX_Text(pDX, IDC_GAMEPATH, m_strGamePath);
    //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(SettingDlg, CDialog)
	//{{AFX_MSG_MAP(SettingDlg)
	ON_BN_CLICKED(IDC_SETTING_BROWSE, OnSettingBrowse)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// SettingDlg message handlers

BOOL SettingDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void SettingDlg::OnSettingBrowse() 
{
	// TODO: Add your control notification handler code here
	CFileDialog* lpCfd = new CFileDialog(TRUE);
    if(lpCfd->DoModal() == IDOK)
    {
        m_strGamePath = lpCfd->GetPathName();
        UpdateData(FALSE);
    }
}
