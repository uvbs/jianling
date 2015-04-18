// ConfigQhPage.cpp : implementation file
//

#include "stdafx.h"
#include "jlwg.h"
#include "ConfigQhPage.h"
#include "GameConfig.h"
#include "gamedef.h"


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
    m_HealthPercent = 0;
    //}}AFX_DATA_INIT
}


void CConfigQhPage::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CConfigQhPage)
    DDX_Control(pDX, IDC_COMBO_ITEMCOLOR, m_ComBox);
    DDX_Text(pDX, IDC_CHIYAOPERCENT, m_HealthPercent);
    DDV_MinMaxInt(pDX, m_HealthPercent, 1, 100);
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

    //获取配置对象
    GameConfig* pConfig = GameConfig::GetInstance();

    m_ComBox.AddString(strGreen);
    m_ComBox.AddString(strBlue);
    m_ComBox.AddString(strPurple);
    m_ComBox.AddString(strOrange);
    m_ComBox.SetCurSel(-1);

    //获取颜色
    //TODO:
    int nIndex = m_ComBox.SelectString(0, pConfig->m_szQHColor);
    ASSERT(nIndex != LB_ERR);

    m_HealthPercent = pConfig->m_HealthPercent;

    UpdateData(FALSE);

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

BOOL CConfigQhPage::OnApply()
{
    UpdateData();

    GameConfig* pConfig = GameConfig::GetInstance();

    pConfig->m_HealthPercent = m_HealthPercent;

    TCHAR szQHColor[BUFSIZ] = {0};
    m_ComBox.GetLBText(m_ComBox.GetCurSel(), szQHColor);
    wcscpy(pConfig->m_szQHColor, szQHColor);

    return CPropertyPage::OnApply();
}