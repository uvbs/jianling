// ConfigQhPage.cpp : implementation file
//

#include "stdafx.h"
#include "jlwg.h"
#include "ConfigQhPage.h"

#include "..\common\CIniFile.h"
#include "..\common\common.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CConfigQhPage dialog


CConfigQhPage::CConfigQhPage(CWnd* pParent /*=NULL*/)
    : CPropertyPage(CConfigQhPage::IDD)
{
    //{{AFX_DATA_INIT(CConfigQhPage)
    //}}AFX_DATA_INIT
}


void CConfigQhPage::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CConfigQhPage)
    DDX_Control(pDX, IDC_COMBO_ITEMCOLOR, m_ComBox);
    //}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CConfigQhPage, CDialog)
    //{{AFX_MSG_MAP(CConfigQhPage)
    ON_CBN_EDITCHANGE(IDC_COMBO_ITEMCOLOR, OnEditchangeComboItemcolor)
    ON_EN_CHANGE(IDC_CHIYAOPERCENT, OnChangeChiyaopercent)
    ON_CBN_SELCHANGE(IDC_COMBO_ITEMCOLOR, OnSelchangeComboItemcolor)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CConfigQhPage message handlers

BOOL CConfigQhPage::OnInitDialog()
{
    CDialog::OnInitDialog();

    // TODO: Add extra initialization here
    m_ComBox.AddString(strGreen);
    m_ComBox.AddString(strBlue);
    m_ComBox.AddString(strPurple);
    m_ComBox.AddString(strOrange);
    m_ComBox.SetCurSel(-1);

    CIniFile configFile;
    configFile.Open(GameInit::Instance()->GetConfigPath());

    TCHAR* lpszColor = configFile.GetProfileString(strNormal, strQhColor, strGreen);
    if(lpszColor[0] == _T(''))
    {
        m_ComBox.SelectString(0, strGreen);
    }
    else
    {
        m_ComBox.SelectString(0, lpszColor);
    }

    TCHAR* lpszHeYaoPercent = configFile.GetProfileString(strCombat, strYaoPecent);
    SetDlgItemText(IDC_CHIYAOPERCENT, lpszHeYaoPercent);

    delete []lpszColor;
    delete []lpszHeYaoPercent;
    return TRUE;  // return TRUE unless you set the focus to a control
    // EXCEPTION: OCX Property Pages should return FALSE
}

void CConfigQhPage::OnEditchangeComboItemcolor()
{
    // TODO: Add your control notification handler code here

}

void CConfigQhPage::OnChangeChiyaopercent()
{
    // TODO: If this is a RICHEDIT control, the control will not
    // send this notification unless you override the CDialog::OnInitDialog()
    // function and call CRichEditCtrl().SetEventMask()
    // with the ENM_CHANGE flag ORed into the mask.

    // TODO: Add your control notification handler code here
    SetModified();
}

void CConfigQhPage::OnSelchangeComboItemcolor()
{
    // TODO: Add your control notification handler code here
    SetModified();
}
