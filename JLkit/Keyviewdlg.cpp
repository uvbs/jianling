// CDlgKeyView.cpp : implementation file
//

#include "stdafx.h"
#include "JLkit.h"
#include "JLkitDoc.h"
#include "MainFrm.h"
#include "JLkitSocket.h"
#include "Keyviewdlg.h"
#include "BindkeyDlg.h"
#include "GlobalUserInfo.h"


#ifdef _DEBUG
    #define new DEBUG_NEW
#endif


// CDlgKeyView dialog

IMPLEMENT_DYNAMIC(CDlgKeyView, CDialog)
CDlgKeyView::CDlgKeyView()
    : CDialog(CDlgKeyView::IDD, NULL)
{
}

CDlgKeyView::~CDlgKeyView()
{

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
    ON_COMMAND(ID_QUERY, OnQuerykey)
    ON_COMMAND(ID_BINDKEY, OnBinkey)
    ON_COMMAND(ID_UNBIND, OnUnbindkey)
    ON_NOTIFY(NM_RCLICK, IDC_LISTKEY, OnNMRClickListkey)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()


// CDlgKeyView message handlers

BOOL CDlgKeyView::OnInitDialog()
{
    CDialog::OnInitDialog();


    m_ListCtrl.InsertColumn(0, _T("卡号"));
    m_ListCtrl.InsertColumn(1, _T("充值时间"));
    m_ListCtrl.InsertColumn(2, _T("充值卡类型"));
    m_ListCtrl.InsertColumn(3, _T("剩余时间"));

    for(int i = 0; i < 4; i++)
    {
        m_ListCtrl.SetColumnWidth(i, LVSCW_AUTOSIZE_USEHEADER);
    }

    m_ListCtrl.SetExtendedStyle(LVS_EX_FULLROWSELECT);


    CRect rect;
    GetClientRect(&rect);

    m_ListCtrl.MoveWindow(&rect, FALSE);

    OnQuerykey();

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
    CMainFrame* pFrame =  (CMainFrame*)AfxGetMainWnd();
    CJLkitDoc* pDoc = (CJLkitDoc*)pFrame->GetActiveDocument();
    CDlgBindKey* pBindDlg = pDoc->m_pBindDlg;

    if(pBindDlg == NULL)
        pBindDlg = new CDlgBindKey;

    pBindDlg->DoModal();
}

void CDlgKeyView::OnQuerykey()
{

    //获取用户KEY
    CGlobalUserInfo* pUserInfo = CGlobalUserInfo::GetInstance();
    KeyVec& key =  pUserInfo->m_KeyVec;;

    CMainFrame* pFrame =  (CMainFrame*)AfxGetMainWnd();
    CJLkitDoc* pDoc = (CJLkitDoc*)pFrame->GetActiveDocument();
    CJLkitSocket& sock = pDoc->m_socket;

    m_ListCtrl.DeleteAllItems();
    for(int i = 0; i < key.size(); i++)
    {
        m_ListCtrl.InsertItem(i, key[i].type);
        m_ListCtrl.SetItemText(i, 1, key[i].key);
        // listctr.SetItemText(i, 2, pKey->remaintime);
        // listctr.SetItemText(i, 3, pKey->buildtime);
    }

    sock.Send(M_KEY, fun_querykey, NULL, 0);
}


void CDlgKeyView::OnUnbindkey()
{

    CMainFrame* pFrame =  (CMainFrame*)AfxGetMainWnd();
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

