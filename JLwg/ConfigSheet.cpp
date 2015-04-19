// ConfigSheet.cpp : implementation file
//

#include "stdafx.h"
#include "JLwg.h"
#include "ConfigSheet.h"
#include "GameConfig.h"
#include "gamedef.h"

#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif



/////////////////////////////////////////////////////////////////////////////
// CConfigSheet

IMPLEMENT_DYNAMIC(CConfigSheet, CPropertySheet)


CConfigSheet::CConfigSheet(CWnd* pWndParent)
    : CPropertySheet(_T("≈‰÷√Œƒº˛"), pWndParent)
{
    AddPage(&m_itempage);
    AddPage(&m_objpage);
    AddPage(&m_qhpage);
    AddPage(&m_partypage);
}

CConfigSheet::~CConfigSheet()
{
}


BEGIN_MESSAGE_MAP(CConfigSheet, CPropertySheet)
    //{{AFX_MSG_MAP(CConfigSheet)
    ON_COMMAND(ID_APPLY_NOW, OnApplyNow)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CConfigSheet message handlers
void CConfigSheet::OnApplyNow()
{


    Default();

}

BOOL CConfigSheet::OnInitDialog()
{
    CPropertySheet::OnInitDialog();


    return TRUE;  // return TRUE unless you set the focus to a control
    // EXCEPTION: OCX Property Pages should return FALSE
}
