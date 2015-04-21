// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "JLSrvr.h"
#include "JLSrvrDoc.h"
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
    ON_WM_TIMER()
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

static UINT indicators[] =
{
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


int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    if(CFrameWnd::OnCreate(lpCreateStruct) == -1)
    {
        return -1;
    }


    if(!m_wndToolBar.Create(this))
    {
        TRACE0("Failed to create status bar\n");
        return -1;      // fail to create
    }

    //平面风格
    m_wndToolBar.ModifyStyle(0, TBSTYLE_FLAT);


    m_wndToolBar.LoadToolBar(IDR_MAINFRAME);


    if(!m_wndStatusBar.Create(this) ||
            !m_wndStatusBar.SetIndicators(indicators, sizeof(indicators) / sizeof(UINT)))
    {
        TRACE0("Failed to create status bar\n");
        return -1;      // fail to create
    }

    SetTimer(IDT_CLEAR, 20000, NULL);
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


void CMainFrame::OnTimer(UINT nIDEvent)
{
    if(nIDEvent == IDT_CLEAR)
    {
        CJLSrvrDoc* pDoc = (CJLSrvrDoc*)GetActiveDocument();
        pDoc->DeadSocketClear();
    }

    CFrameWnd::OnTimer(nIDEvent);
}

void CMainFrame::OnClose() 
{
	KillTimer(IDT_CLEAR);
	CFrameWnd::OnClose();
}
