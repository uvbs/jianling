// JLSrvrView.cpp : implementation of the CJLSrvrView class
//

#include "stdafx.h"
#include "JLSrvr.h"
#include "JLSrvrDoc.h"
#include "JLSrvrView.h"


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
    ON_COMMAND(ID_KEY_ADD, OnKeyAdd)
    ON_NOTIFY_REFLECT(NM_RCLICK, OnRclick)
    ON_COMMAND(ID_MENUITEM32774, OnMenuitem32774)
    ON_COMMAND(ID_MENUITEM32775, OnMenuitem32775)
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

    //插入列
    GetListCtrl().InsertColumn(0, _T("帐号"));
    GetListCtrl().InsertColumn(1, _T("在线时长"));
    GetListCtrl().InsertColumn(2, _T("请求数"));
    GetListCtrl().InsertColumn(3, _T("地址"));

    //自动列宽度
    AutoColumnWidth();

    //全行风格
    GetListCtrl().SetExtendedStyle(LVS_EX_FULLROWSELECT);
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

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CJLSrvrView message handlers

BOOL CJLSrvrView::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName,
                         DWORD dwStyle, const RECT& rect, CWnd* pParentWnd,
                         UINT nID, CCreateContext* pContext)
{

    return CWnd::Create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext);
}

void CJLSrvrView::AutoColumnWidth()
{
    for(;;)
    {
        if(!GetListCtrl().SetColumnWidth(i, LVSCW_AUTOSIZE_USEHEADER))
            break;
    }
}

void CJLSrvrView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint)
{

}

void CJLSrvrView::OnTimer(UINT nIDEvent)
{

    CListView::OnTimer(nIDEvent);
}

void CJLSrvrView::OnKeyAdd()
{
}

void CJLSrvrView::DoPopupMenu(int type)
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


void CJLSrvrView::OnRclick(NMHDR* pNMHDR, LRESULT* pResult)
{
    switch(pNMHDR->code)
    {
        case NM_RCLICK:
        {
            if(GetListCtrl().GetSelectedCount() == 0)
            {
                DoPopupMenu(1);
            }
            else
            {
                DoPopupMenu(0);
            }
        }
        break;

    }
    *pResult = 0;
}


//帐号详细信息
void CJLSrvrView::OnMenuitem32774()
{

}


//刷新
void CJLSrvrView::OnMenuitem32775()
{


}