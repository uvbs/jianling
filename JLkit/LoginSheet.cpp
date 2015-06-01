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
// arrays of IDs used to initialize control bars

static UINT BASED_CODE indicators[] =
{
    ID_SEPARATOR,           // status line indicator
    ID_INDICATOR_LOGINED,
    ID_INDICATOR_ALLNUMS,
    ID_INDICATOR_VALIDKEY
};

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
    ON_WM_SIZE()
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

    return 0;
}

void CLoginSheet::OnSize(UINT nType, int cx, int cy)
{
    CPropertySheet::OnSize(nType, cx, cy);


}

BOOL CLoginSheet::OnInitDialog()
{
    CPropertySheet::OnInitDialog();

    
    SetIcon(AfxGetApp()->LoadIcon(IDR_MAINFRAME), FALSE);

    // Create the status bar..and set the indicators..
    if(!m_wndStatusBar.Create(this) ||
            !m_wndStatusBar.SetIndicators(indicators,
                                          sizeof(indicators) / sizeof(UINT)))
    {
        TRACE0("Failed to create status bar\n");
        return -1;      // fail to create
    }

    // Make a sunken or recessed border around the first pane
    m_wndStatusBar.SetPaneInfo(0, m_wndStatusBar.GetItemID(0),
                               SBPS_STRETCH, NULL);

    CRect sheetRect;
    CRect barRect;

    // Get the client coordinates of the propertysheet.
    GetClientRect(&sheetRect);

    // Query for the rectangle coordinates when the status bar will be placed. This
    // will help in determining the height of staus bar.
    RepositionBars(AFX_IDW_CONTROLBAR_FIRST, AFX_IDW_CONTROLBAR_LAST,
                   0, reposQuery, barRect);


    CenterWindow();


    return TRUE;  // return TRUE unless you set the focus to a control
    // EXCEPTION: OCX Property Pages should return FALSE
}
