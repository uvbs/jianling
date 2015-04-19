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
    _ASSERTE(!pConfig->m_szQHColor.empty());
    int nIndex = m_ComBox.SelectString(-1, pConfig->m_szQHColor.c_str());
    _ASSERTE(nIndex != LB_ERR);

    m_HealthPercent = pConfig->m_HealthPercent;

    UpdateData(FALSE);
    return TRUE;  // return TRUE unless you set the focus to a control
    // EXCEPTION: OCX Property Pages should return FALSE
}


BOOL CConfigQhPage::OnApply()
{
    UpdateData();

    GameConfig* pConfig = GameConfig::GetInstance();

    pConfig->m_HealthPercent = m_HealthPercent;

    TCHAR szQHColor[BUFSIZ] = {0};
    int inSel = m_ComBox.GetCurSel();
    m_ComBox.GetLBText(inSel, szQHColor);
    pConfig->m_szQHColor = szQHColor;


    return CPropertyPage::OnApply();
}

BOOL CConfigQhPage::OnCommand(WPARAM wParam, LPARAM lParam)
{

    int Notifyid = HIWORD(wParam);
    if(Notifyid == EN_CHANGE ||
            Notifyid == BM_CLICK)
    {
        SetModified();
    }


    return CDialog::OnCommand(wParam, lParam);
}
