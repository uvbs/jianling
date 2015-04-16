// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "JLSrvr.h"
#include "MainFrm.h"
#include "JLSrvrView.h"


#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
    //{{AFX_MSG_MAP(CMainFrame)
    ON_WM_CREATE()
    ON_WM_CLOSE()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

static UINT indicators[] = {
    ID_SEPARATOR,           // status line indicator
    ID_INDICATOR_UPTIME,
    ID_INDICATOR_CONNECTS   //总连接数
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
    // TODO: add member initialization code here

}

CMainFrame::~CMainFrame()
{
}


static TCHAR BASED_CODE szSection[] = _T("设置");
static TCHAR BASED_CODE szWindowPos[] = _T("WindowPos");
static TCHAR szFormat[] = _T("%u,%u,%d,%d,%d,%d,%d,%d,%d,%d");

static BOOL PASCAL NEAR ReadWindowPlacement(LPWINDOWPLACEMENT pwp)
{
    CString strBuffer = AfxGetApp()->GetProfileString(szSection, szWindowPos);
    if(strBuffer.IsEmpty()) {
        return FALSE;
    }

    WINDOWPLACEMENT wp;
    int nRead = _stscanf(strBuffer, szFormat,
                         &wp.flags, &wp.showCmd,
                         &wp.ptMinPosition.x, &wp.ptMinPosition.y,
                         &wp.ptMaxPosition.x, &wp.ptMaxPosition.y,
                         &wp.rcNormalPosition.left, &wp.rcNormalPosition.top,
                         &wp.rcNormalPosition.right, &wp.rcNormalPosition.bottom);

    if(nRead != 10) {
        return FALSE;
    }

    wp.length = sizeof wp;
    *pwp = wp;
    return TRUE;
}

static void PASCAL NEAR WriteWindowPlacement(LPWINDOWPLACEMENT pwp)
// write a window placement to settings section of app's ini file
{
    TCHAR szBuffer[sizeof("-32767") * 8 + sizeof("65535") * 2];

    wsprintf(szBuffer, szFormat,
             pwp->flags, pwp->showCmd,
             pwp->ptMinPosition.x, pwp->ptMinPosition.y,
             pwp->ptMaxPosition.x, pwp->ptMaxPosition.y,
             pwp->rcNormalPosition.left, pwp->rcNormalPosition.top,
             pwp->rcNormalPosition.right, pwp->rcNormalPosition.bottom);
    AfxGetApp()->WriteProfileString(szSection, szWindowPos, szBuffer);
}



 int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    if(CFrameWnd::OnCreate(lpCreateStruct) == -1) {
        return -1;
    }

    WINDOWPLACEMENT wp;
    if(ReadWindowPlacement(&wp)) {
        SetWindowPlacement(&wp);
    }
    
    if(!m_wndToolBar.Create(this)) {
        TRACE0("Failed to create status bar\n");
        return -1;      // fail to create
    }

    //平面风格
    m_wndToolBar.ModifyStyle(0, TBSTYLE_FLAT);


    m_wndToolBar.LoadToolBar(IDR_MAINFRAME);


    if(!m_wndStatusBar.Create(this) ||
            !m_wndStatusBar.SetIndicators(indicators, sizeof(indicators) / sizeof(UINT))) {
        TRACE0("Failed to create status bar\n");
        return -1;      // fail to create
    }

    return 0;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
    CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
    CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers


void CMainFrame::OnClose()
{
    // TODO: Add your message handler code here and/or call default
    WINDOWPLACEMENT wp;
    wp.length = sizeof wp;
    if(GetWindowPlacement(&wp)) {
        wp.flags = 0;
        if(IsZoomed()) {
            wp.flags |= WPF_RESTORETOMAXIMIZED;
        }
        // and write it to the .INI file
        WriteWindowPlacement(&wp);
    }


    CFrameWnd::OnClose();
}