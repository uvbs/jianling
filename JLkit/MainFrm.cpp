// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "JLkit.h"
#include "MainFrm.h"
#include "JLkitView.h"
#include "JLkitDoc.h"
#include "JLkitSocket.h"
#include "settingdlg.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#endif


/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_WM_CLOSE()
	ON_WM_ACTIVATE()
    ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


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
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{

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
	if (strBuffer.IsEmpty())
		return FALSE;
	
	WINDOWPLACEMENT wp;
	int nRead = _stscanf(strBuffer, szFormat,
		&wp.flags, &wp.showCmd,
		&wp.ptMinPosition.x, &wp.ptMinPosition.y,
		&wp.ptMaxPosition.x, &wp.ptMaxPosition.y,
		&wp.rcNormalPosition.left, &wp.rcNormalPosition.top,
		&wp.rcNormalPosition.right, &wp.rcNormalPosition.bottom);
	
	if (nRead != 10)
		return FALSE;
	
	wp.length = sizeof wp;
	*pwp = wp;
	return TRUE;
}

static void PASCAL NEAR WriteWindowPlacement(LPWINDOWPLACEMENT pwp)
// write a window placement to settings section of app's ini file
{
	TCHAR szBuffer[sizeof("-32767")*8 + sizeof("65535")*2];
	
	wsprintf(szBuffer, szFormat,
		pwp->flags, pwp->showCmd,
		pwp->ptMinPosition.x, pwp->ptMinPosition.y,
		pwp->ptMaxPosition.x, pwp->ptMaxPosition.y,
		pwp->rcNormalPosition.left, pwp->rcNormalPosition.top,
		pwp->rcNormalPosition.right, pwp->rcNormalPosition.bottom);
	AfxGetApp()->WriteProfileString(szSection, szWindowPos, szBuffer);
}

void CMainFrame::RestoreWinPos()
{
    WINDOWPLACEMENT wp;
    if (ReadWindowPlacement(&wp)){
        wp.showCmd = SW_HIDE;
		SetWindowPlacement(&wp);
    }
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if(CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT))){
		TRACE0("Failed to create status bar\n");
        return -1;      // fail to create
	}
    
    RestoreWinPos();

    SetTimer(IDT_HEART, 5000, NULL);
    SetTimer(IDT_TIMERGAMEEXIT, 2000, NULL);
    SetTimer(IDT_TIMERPOSTKEYQUERY, 30000, NULL);
    return 0;
}


/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers

void CMainFrame::OnClose() 
{

	WINDOWPLACEMENT wp;
	wp.length = sizeof wp;
	if (GetWindowPlacement(&wp))
	{
		wp.flags = 0;
		if (IsZoomed())
			wp.flags |= WPF_RESTORETOMAXIMIZED;
		// and write it to the .INI file
		WriteWindowPlacement(&wp);
	}


	CFrameWnd::OnClose();
}


void CMainFrame::OnTimer(UINT nIDEvent) 
{
    CJLkitDoc* pDoc = (CJLkitDoc *)GetActiveDocument();
    CJLkitView* pView = (CJLkitView *)GetActiveView();
    if(pDoc == NULL)
        return;


    CJLkitSocket* pSocket = pDoc->m_pSocket;
    CListCtrl &list = pView->GetListCtrl();
    
    if(nIDEvent == IDT_TIMERGAMEEXIT){
        for(int i = 0; i < list.GetItemCount(); i++){
            CString strName = list.GetItemText(i, 0);
            if(pDoc->m_share.IsPidValid((LPCTSTR)strName) == FALSE){
                pDoc->m_share.Del((LPCTSTR)strName);
                list.SetItemText(i, COLUMN_TEXT_STATUS, _T("进程退出了"));
            }
        }
    }
}
