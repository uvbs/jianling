// RequestView.cpp : implementation file
//

#include "stdafx.h"
#include "JLSrvr.h"
#include "Request.h"
#include "RequestSocket.h"
#include "RequestView.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRequestView

IMPLEMENT_DYNCREATE(CRequestView, CListView)

CRequestView::CRequestView()
{
    m_dwDefaultStyle |= LVS_REPORT;
}

CRequestView::~CRequestView()
{
}


BEGIN_MESSAGE_MAP(CRequestView, CListView)
    //{{AFX_MSG_MAP(CRequestView)
    ON_NOTIFY_REFLECT(NM_RCLICK, OnRclick)
    ON_COMMAND(ID_MENUITEM32776, OnMenuitem32776)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRequestView drawing

void CRequestView::OnDraw(CDC* pDC)
{
    CDocument* pDoc = GetDocument();
    // TODO: add draw code here
}

/////////////////////////////////////////////////////////////////////////////
// CRequestView diagnostics

#ifdef _DEBUG
void CRequestView::AssertValid() const
{
    CListView::AssertValid();
}

void CRequestView::Dump(CDumpContext& dc) const
{
    CListView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CRequestView message handlers


void CRequestView::AutoColumnWidth()
{
    for(int i = 0; i < 5; i++)
    {
        GetListCtrl().SetColumnWidth(i, LVSCW_AUTOSIZE_USEHEADER);
    }
}
void CRequestView::OnInitialUpdate()
{
    CListView::OnInitialUpdate();

    // TODO: Add your specialized code here and/or call the base class

    int i = 0;
    GetListCtrl().InsertColumn(i++, _T("帐号"));
    GetListCtrl().InsertColumn(i++, _T("请求"));
    GetListCtrl().InsertColumn(i++, _T("时间"));
    GetListCtrl().InsertColumn(i++, _T("请求结果"));
    GetListCtrl().InsertColumn(i++, _T("其他"));


    AutoColumnWidth();



    GetListCtrl().SetExtendedStyle(LVS_EX_FULLROWSELECT);
}

void CRequestView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint)
{
    // TODO: Add your specialized code here and/or call the base class
    int NowCount = GetListCtrl().GetItemCount();
    if(lHint == HINT_OFFLINE ||
            lHint == HINT_REQUEST)
    {
        CRequest* pRequest = (CRequest*)pHint;
        GetListCtrl().InsertItem(NowCount, pRequest->strUserName);
        GetListCtrl().SetItemText(NowCount, 1, pRequest->strType);
        GetListCtrl().SetItemText(NowCount, 2, pRequest->strTime);
        GetListCtrl().SetItemText(NowCount, 3, pRequest->strResult);
        GetListCtrl().SetItemText(NowCount, 4, pRequest->strOther);
    }

    AutoColumnWidth();
    GetListCtrl().EnsureVisible(NowCount, FALSE);
}



void CRequestView::DoPopupMenu(int type)
{
    POINT point;
    if(GetCursorPos(&point))
    {
        CMenu menu;
        menu.LoadMenu(IDR_MENU1);
        CMenu* subMenu = menu.GetSubMenu(type);
        subMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);
    }

}

void CRequestView::OnRclick(NMHDR* pNMHDR, LRESULT* pResult)
{
    // TODO: Add your control notification handler code here

    DoPopupMenu(2);


    *pResult = 0;
}

void CRequestView::OnMenuitem32776()
{
    // TODO: Add your command handler code here
    GetListCtrl().DeleteAllItems();
}
