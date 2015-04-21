// CDlgKeyView.cpp : implementation file
//

#include "stdafx.h"
#include "JLkit.h"
#include "JLkitDoc.h"
#include "MainFrm.h"
#include "JLkitSocket.h"
#include "Keyviewdlg.h"


#ifdef _DEBUG
    #define new DEBUG_NEW
#endif


// CDlgKeyView dialog

IMPLEMENT_DYNAMIC(CDlgKeyView, CDialog)
CDlgKeyView::CDlgKeyView(CWnd* pParent)
    : CDialog(CDlgKeyView::IDD, pParent)
{
    m_pBindDlg = NULL;
}

CDlgKeyView::~CDlgKeyView()
{
    SafeDelete(m_pBindDlg);
}



void CDlgKeyView::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);

    //{{AFX_DATA_MAP(CDlgKeyView)
    DDX_Control(pDX, IDC_LISTKEY, m_ListCtrl);
    //}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgKeyView, CDialog)
    //{{AFX_MSG_MAP(CDlgKeyView)
    ON_COMMAND(ID_BINDKEY, OnBinkey)
    ON_COMMAND(ID_UNBIND, OnUnbindkey)
    ON_NOTIFY(NM_RCLICK, IDC_LISTKEY, OnNMRClickListkey)
    ON_COMMAND(ID_QUERY, OnQuery)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()


// CDlgKeyView message handlers

BOOL CDlgKeyView::OnInitDialog()
{
    CDialog::OnInitDialog();


    m_ListCtrl.InsertColumn(0, _T("卡号"));
    m_ListCtrl.InsertColumn(1, _T("剩余时间"));

    for(int i = 0; i < 2; i++)
    {
        m_ListCtrl.SetColumnWidth(i, LVSCW_AUTOSIZE_USEHEADER);
    }

    m_ListCtrl.SetExtendedStyle(LVS_EX_FULLROWSELECT);


    CRect rect;
    GetClientRect(&rect);

    m_ListCtrl.MoveWindow(&rect, FALSE);



    Querykey();

    return TRUE;  // return TRUE unless you set the focus to a control
    // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgKeyView::OnNMRClickListkey(NMHDR* pNMHDR, LRESULT* pResult)
{

    POINT point;
    GetCursorPos(&point);

    CMenu menu;
    menu.LoadMenu(IDR_KEY);
    menu.GetSubMenu(0)->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);

    *pResult = 0;
}

void CDlgKeyView::OnBinkey()
{

    if(m_pBindDlg == NULL)
        m_pBindDlg = new CDlgBindKey;

    m_pBindDlg->DoModal();
}

void CDlgKeyView::Querykey()
{
    CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
    CJLkitDoc* pDoc = (CJLkitDoc*)pFrame->GetActiveDocument();

    m_ListCtrl.DeleteAllItems();
    for(int i = 0; i < pDoc->m_KeyVec.size(); i++)
    {
        m_ListCtrl.InsertItem(i, pDoc->m_KeyVec[i].key);
        CString strLeft;
        strLeft.Format(_T("%d小时"), pDoc->m_KeyVec[i].remaintime);
        m_ListCtrl.SetItemText(i, 1, strLeft);
    }
    
    for(int t = 0;;)
    {
        if(!m_ListCtrl.SetColumnWidth(t++, LVSCW_AUTOSIZE_USEHEADER))
            break;
    }
}


void CDlgKeyView::OnUnbindkey()
{

    CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
    CJLkitDoc* pDoc = (CJLkitDoc*)pFrame->GetActiveDocument();
    CJLkitSocket& sock = pDoc->m_socket;

    //解绑key
    POSITION rpos = m_ListCtrl.GetFirstSelectedItemPosition();

    while(rpos)
    {
        int nItem = m_ListCtrl.GetNextSelectedItem(rpos);
        CString strKey = m_ListCtrl.GetItemText(nItem, 0);

        BINDKEY_BUF key;
        _tcscpy(key.key, (LPCTSTR)strKey);

        sock.Send(M_KEY, fun_unbindkey, &key, sizeof(BINDKEY_BUF));
    }
}


void CDlgKeyView::OnQuery()
{

    Querykey();

    CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
    CJLkitDoc* pDoc = (CJLkitDoc*)pFrame->GetActiveDocument();

    pDoc->m_KeyVec.clear();
    pDoc->m_socket.Send(M_KEY, fun_querykey, NULL, 0);


}
