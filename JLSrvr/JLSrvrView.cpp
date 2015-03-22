// JLSrvrView.cpp : implementation of the CJLSrvrView class
//

#include "stdafx.h"
#include "JLSrvr.h"

#include "JLSrvrDoc.h"
#include "JLSrvrView.h"
#include "Request.h"
#include "RequestSocket.h"
#include "DlgKeyAdd.h"

//三个属性页
#include "DlgAcInfo.h"
#include "DlgAcKey.h"
#include "DlgAcKeylog.h"

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
    ON_COMMAND(ID_SOCKETINFO, OnSocketinfo)
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

CJLSrvrDoc* CJLSrvrView::GetDocument() // non-debug version is inline
{
    ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CJLSrvrDoc)));
    return (CJLSrvrDoc*)m_pDocument;
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
            TRACE(_T("NowCount = %d"), NowCount);
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

    CListView::OnTimer(nIDEvent);
}

void CJLSrvrView::OnKeyAdd()
{
    CDlgKeyAdd dlg;
    dlg.DoModal();
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
    // TODO: Add your control notification handler code here
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
    // TODO: Add your command handler code here
    CPropertySheet sheet(_T("详细信息"));
    CDlgAcInfo page1;
    CDlgAcKey page2;
    CDlgAcKeylog page3;


    //获取选定的账号名
    POSITION pos = GetListCtrl().GetFirstSelectedItemPosition();
    if(pos == NULL)
    {
        TRACE0("No items were selected!\n");
    }
    else
    {
        int nItem = GetListCtrl().GetNextSelectedItem(pos);
        CRequest* pRequest = (CRequest*)GetListCtrl().GetItemData(nItem);
        if(pRequest == NULL)
        {
            TRACE(_T("item数据是空值, 检查这个问题"));
            return;
        }

        page1.m_strAcName = pRequest->strUserName;
        page2.m_strAcName = pRequest->strUserName;
        page3.m_strAcName = pRequest->strUserName;

        sheet.AddPage(&page1);
        sheet.AddPage(&page2);
        sheet.AddPage(&page3);

        sheet.DoModal();
    }







}


//刷新
void CJLSrvrView::OnMenuitem32775()
{
    // TODO: Add your command handler code here
    GetListCtrl().DeleteAllItems();

    POSITION ppos = GetDocument()->m_ClientList.GetHeadPosition();
    while(ppos)
    {
        CRequest* pRequest = ((CRequestSocket*)GetDocument()->m_ClientList.GetNext(ppos))->m_pRequest;
        OnUpdate(this, HINT_ACEEPT, pRequest);
    }

}

void CJLSrvrView::OnSocketinfo()
{
    // TODO: Add your command handler code here

}
