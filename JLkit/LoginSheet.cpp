// LoginSheet.cpp : implementation file
//

#include "stdafx.h"
#include "jlkit.h"
#include "LoginSheet.h"

#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLoginSheet

IMPLEMENT_DYNAMIC(CLoginSheet, CPropertySheet)

CLoginSheet::CLoginSheet(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
    : CPropertySheet(nIDCaption, pParentWnd, iSelectPage)
{
}

CLoginSheet::CLoginSheet(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
    : CPropertySheet(pszCaption, pParentWnd, iSelectPage)
{
}

CLoginSheet::~CLoginSheet()
{
}


BEGIN_MESSAGE_MAP(CLoginSheet, CPropertySheet)
    //{{AFX_MSG_MAP(CLoginSheet)
    ON_WM_CLOSE()
    ON_WM_CREATE()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLoginSheet message handlers

void CLoginSheet::OnClose()
{
    //Í¨Öª¿ò¼ÜÍË³ö
    CPropertySheet::OnClose();
    AfxGetMainWnd()->DestroyWindow();
}

int CLoginSheet::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    if(CPropertySheet::OnCreate(lpCreateStruct) == -1)
        return -1;

    SetIcon(AfxGetApp()->LoadIcon(IDR_MAINFRAME), FALSE);
    return 0;
}
