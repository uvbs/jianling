// JLSrvrView.cpp : implementation of the CJLSrvrView class
//

#include "stdafx.h"
#include "JLSrvr.h"

#include "JLSrvrDoc.h"
#include "JLSrvrView.h"
#include "Request.h"
#include "RequestSocket.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CJLSrvrView

IMPLEMENT_DYNCREATE(CJLSrvrView, CListView)

BEGIN_MESSAGE_MAP(CJLSrvrView, CListView)
    //{{AFX_MSG_MAP(CJLSrvrView)
    ON_WM_TIMER()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CJLSrvrView construction/destruction

CJLSrvrView::CJLSrvrView()
{
    // TODO: add construction code here
    m_dwDefaultStyle |= LVS_REPORT;
}

CJLSrvrView::~CJLSrvrView()
{
}

BOOL CJLSrvrView::PreCreateWindow(CREATESTRUCT& cs)
{
    // TODO: Modify the Window class or styles here by modifying

    return CListView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CJLSrvrView drawing

void CJLSrvrView::OnDraw(CDC* pDC)
{
    CJLSrvrDoc* pDoc = GetDocument();
    ASSERT_VALID(pDoc);
    // TODO: add draw code for native data here
}

void CJLSrvrView::OnInitialUpdate()
{
    CListView::OnInitialUpdate();


    GetListCtrl().InsertColumn(0, _T("帐号"));
    GetListCtrl().InsertColumn(1, _T("在线时长"));
    GetListCtrl().InsertColumn(2, _T("请求数"));
    GetListCtrl().InsertColumn(3, _T("地址"));


    AutoColumnWidth();


    //全行风格
    GetListCtrl().SetExtendedStyle(LVS_EX_FULLROWSELECT);



    SetTimer(IDT_TIMERCALCTIME, 2000, NULL);
    // TODO: You may populate your ListView with items by directly accessing
    //  its list control through a call to GetListCtrl().
}

/////////////////////////////////////////////////////////////////////////////
// CJLSrvrView diagnostics

#ifdef _DEBUG
void CJLSrvrView::AssertValid() const
{
    CListView::AssertValid();
}

void CJLSrvrView::Dump(CDumpContext& dc) const
{
    CListView::Dump(dc);
}

CJLSrvrDoc* CJLSrvrView::GetDocument() // non-debug version is inline
{
    ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CJLSrvrDoc)));
    return (CJLSrvrDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CJLSrvrView message handlers

BOOL CJLSrvrView::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext)
{
    // TODO: Add your specialized code here and/or call the base class
    return CWnd::Create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext);
}

void CJLSrvrView::AutoColumnWidth()
{
    for(int i = 0; i < 4; i++)
    {
        GetListCtrl().SetColumnWidth(i, LVSCW_AUTOSIZE_USEHEADER);
    }
}



void CJLSrvrView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint)
{
    CRequest* pRequest = (CRequest*)pHint;
    int NowCount = GetListCtrl().GetItemCount();
    if(lHint == HINT_ACEEPT)
    {
        GetListCtrl().InsertItem(NowCount, pRequest->strUserName);
        GetListCtrl().SetItemText(NowCount, 1, pRequest->strTime);
        CString strReqNums;
        strReqNums.Format(_T("%d"), pRequest->m_reqNums);
        GetListCtrl().SetItemText(NowCount, 2, strReqNums);
        GetListCtrl().SetItemText(NowCount, 3, pRequest->strIp);
        GetListCtrl().SetItemData(NowCount, (DWORD)pHint);
    }
    else if(lHint == HINT_OFFLINE)
    {
        //删掉自己的列
        for(int i = 0; i < NowCount; i++)
        {
            TRACE1(_T("NowCount = %d"), NowCount);
            if(GetListCtrl().GetItemData(i) == (DWORD)pHint)
            {
                GetListCtrl().DeleteItem(i);
                break;
            }
        }
    }
    else if(lHint == HINT_REQUEST)
    {
        for(int i = 0; i < NowCount; i++)
        {
            if(GetListCtrl().GetItemData(i) == (DWORD)pHint)
            {
                GetListCtrl().SetItemText(i, 0, pRequest->strUserName);
                CString strReqNums;
                strReqNums.Format(_T("%d"), pRequest->m_reqNums);
                GetListCtrl().SetItemText(i, 2, strReqNums);
            }
        }
    }

    AutoColumnWidth();

}

void CJLSrvrView::OnTimer(UINT nIDEvent)
{
    // TODO: Add your message handler code here and/or call default
    if(nIDEvent == IDT_TIMERCALCTIME)
    {

    }
    CListView::OnTimer(nIDEvent);
}
