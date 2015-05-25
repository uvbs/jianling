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

static UINT indicators[] =
{
    ID_SEPARATOR,           // status line indicator
    ID_INDICATOR_UPTIME,
    ID_INDICATOR_CONNECTS   //总连接数
};

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
    //{{AFX_MSG_MAP(CMainFrame)
    ON_WM_CREATE()
    ON_WM_TIMER()
    ON_WM_CLOSE()
    ON_UPDATE_COMMAND_UI(ID_INDICATOR_CONNECTS, OnUpdateConnects)
    ON_UPDATE_COMMAND_UI(ID_INDICATOR_UPTIME, OnUpdateRunTime)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()



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

    m_wndStatusBar.SetPaneInfo(ID_SEPARATOR, ID_SEPARATOR, SBPS_STRETCH, 10);

    //处理心跳
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

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
    // TODO: Add your specialized code here and/or call the base class

    if(!CFrameWnd::PreCreateWindow(cs))
        return FALSE;


    cs.cx = 600;
    cs.cy = 400;
    cs.dwExStyle &= ~WS_EX_CLIENTEDGE;

    return TRUE;
}

void CMainFrame::OnUpdateConnects(CCmdUI* pCmdUI)
{
    CString strNums;
    strNums.Format(_T("%d"), ((CJLSrvrDoc*)GetActiveDocument())->_client.size());
    pCmdUI->SetText(strNums);
}

//运行时间
void CMainFrame::OnUpdateRunTime(CCmdUI* pCmdUI)
{
    CString strNums;
    strNums.Format(_T("%d"), ((CJLSrvrDoc*)GetActiveDocument())->_client.size());
    pCmdUI->SetText(strNums);
}


void CMainFrame::CalcUpTime()
{
    CString strUpTime;
    CJLSrvrDoc* pDoc = (CJLSrvrDoc*)GetActiveDocument();


    // only canculate if we have a doc and it's listening....
    if(pDoc && pDoc->m_pListen)
    {
        CTime timeNow = CTime::GetCurrentTime();


        // calculate uptime and set the status bar....
        CTimeSpan upTime = timeNow - pDoc->m_timeStarted;
        UINT uFmt = upTime.GetDays() > 0 ? IDS_UPTIME_DAYS : IDS_UPTIME_DAY;
        strUpTime = upTime.Format(uFmt);
    }
    else
    {
        strUpTime.Format(ID_INDICATOR_UPTIME);
    }

    m_wndStatusBar.SetPaneText(1, strUpTime, TRUE);
}