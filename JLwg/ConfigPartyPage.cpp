// ConfigPartyPage.cpp : implementation file
//

#include "stdafx.h"
#include "JLwg.h"
#include "ConfigPartyPage.h"
#include "GameConfig.h"
#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CConfigPartyPage property page

IMPLEMENT_DYNCREATE(CConfigPartyPage, CPropertyPage)

CConfigPartyPage::CConfigPartyPage() : CPropertyPage(CConfigPartyPage::IDD)
{
    //{{AFX_DATA_INIT(CConfigPartyPage)

    m_bInvite_Auto = 0;
    m_bInvite_ALL = 0;
    m_bInvite_INMAP = 0;
    m_bInvite_Range = 0;
    m_nInvite_Range = 0;


    m_bAccept_INMAP = 0;
    m_bAccept_Auto = 0;
    m_bAccept_ALL = 0;
    m_bAccept_Range = 0;
    m_nAccept_Range = 0;
    //}}AFX_DATA_INIT
}

CConfigPartyPage::~CConfigPartyPage()
{
}

void CConfigPartyPage::DoDataExchange(CDataExchange* pDX)
{

    CPropertyPage::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CConfigPartyPage)
    DDX_Check(pDX, IDC_ACCEPT_ALL, m_bAccept_ALL);
    DDX_Check(pDX, IDC_ACCEPT_AUTO, m_bAccept_Auto);
    DDX_Check(pDX, IDC_ACCEPT_RANGE, m_bAccept_Range);
    DDX_Check(pDX, IDC_ACCEPT_INMAP, m_bAccept_INMAP);
    DDX_Text(pDX, IDC_ACCEPT_RANGE_VALUE, m_nAccept_Range);

    DDX_Check(pDX, IDC_INVITE_ALL, m_bInvite_ALL);
    DDX_Check(pDX, IDC_INVITE_AUTO, m_bInvite_Auto);
    DDX_Check(pDX, IDC_INVITE_RANGE, m_bInvite_Range);
    DDX_Check(pDX, IDC_INVITE_INMAP, m_bInvite_INMAP);
    DDX_Text(pDX, IDC_INVITE_RANGE_VALUE, m_nInvite_Range);
    //}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CConfigPartyPage, CPropertyPage)
    //{{AFX_MSG_MAP(CConfigPartyPage)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CConfigPartyPage message handlers

BOOL CConfigPartyPage::OnInitDialog()
{
    CPropertyPage::OnInitDialog();

    GameConfig* pConfig = GameConfig::GetInstance();

    m_bInvite_Auto  = pConfig->m_bInvite_Auto;
    m_bInvite_ALL   = pConfig->m_bInvite_ALL;
    m_bInvite_INMAP = pConfig->m_bAccept_INMAP;
    m_bInvite_Range = pConfig->m_bInvite_Range;
    m_nInvite_Range = pConfig->m_nInvite_Range;


    m_bAccept_Auto = pConfig->m_bAccept_Auto;
    m_bAccept_ALL = pConfig->m_bAccept_ALL;
    m_bAccept_INMAP = pConfig->m_bAccept_INMAP;
    m_bAccept_Range = pConfig->m_bAccept_Range;
    m_nAccept_Range = pConfig->m_nAccept_Range;

    UpdateData(FALSE);
    return TRUE;
}

BOOL CConfigPartyPage::OnApply()
{
    TRACE(_T("OnApply"));
    //获得控件值
    UpdateData(TRUE);

    GameConfig* pConfig = GameConfig::GetInstance();

    pConfig->m_bInvite_Auto = m_bInvite_Auto ;
    pConfig->m_bInvite_ALL = m_bInvite_ALL   ;
    pConfig->m_bInvite_INMAP = m_bInvite_INMAP ;
    pConfig->m_bInvite_Range = m_bInvite_Range;
    pConfig->m_nInvite_Range =  m_nInvite_Range ;


    pConfig->m_bAccept_Auto = m_bAccept_Auto ;
    pConfig->m_bAccept_ALL = m_bAccept_ALL;
    pConfig->m_bAccept_INMAP =  m_bAccept_INMAP ;
    pConfig->m_bAccept_Range = m_bAccept_Range ;
    pConfig->m_nAccept_Range = m_nAccept_Range ;

    return CPropertyPage::OnApply();
}

BOOL CConfigPartyPage::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{


    return CPropertyPage::OnNotify(wParam, lParam, pResult);
}

BOOL CConfigPartyPage::OnCommand(WPARAM wParam, LPARAM lParam)
{
   
    int Notifyid = HIWORD(wParam);
    if(Notifyid == EN_CHANGE) {
        SetModified();
    }


    return CPropertyPage::OnCommand(wParam, lParam);
}
