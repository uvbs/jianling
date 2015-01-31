// CDlgSetting.cpp : implementation file
//

#include "stdafx.h"
#include "Jlkit.h"
#include "Settingdlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgSetting dialog

CDlgSetting::CDlgSetting(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgSetting::IDD, pParent)
{
    m_strGamePath = _T("");
}

void CDlgSetting::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);

    //{{AFX_DATA_MAP(CDlgSetting)
    DDX_Text(pDX, IDC_GAMEPATH, m_strGamePath);
    //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDlgSetting, CDialog)
	//{{AFX_MSG_MAP(CDlgSetting)
	ON_BN_CLICKED(IDC_SETTING_BROWSE, OnSettingBrowse)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgSetting message handlers

BOOL CDlgSetting::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void CDlgSetting::OnSettingBrowse() 
{
	// TODO: Add your control notification handler code here
	CFileDialog* lpCfd = new CFileDialog(TRUE);
    if(lpCfd->DoModal() == IDOK)
    {
        m_strGamePath = lpCfd->GetPathName();
        UpdateData(FALSE);
    }
}
