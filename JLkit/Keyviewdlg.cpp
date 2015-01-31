// CDlgKeyView.cpp : implementation file
//

#include "stdafx.h"
#include "JLkit.h"
#include "JLkitDoc.h"
#include "JLkitSocket.h"
#include "Keyviewdlg.h"
#include "BindkeyDlg.h"


// CDlgKeyView dialog

IMPLEMENT_DYNAMIC(CDlgKeyView, CDialog)
CDlgKeyView::CDlgKeyView(CJLkitDoc* pDoc)
	: CDialog(CDlgKeyView::IDD, NULL)
{
    m_pSocket = pDoc->m_pSocket;
    m_pDoc = pDoc;

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
	ON_WM_RBUTTONUP()
	ON_NOTIFY(NM_RCLICK, IDC_LISTKEY, OnNMRClickListkey)
	ON_COMMAND(ID_QUERY, OnQuerykey)
	ON_COMMAND(ID_BINDKEY, OnBinkey)
	ON_COMMAND(ID_UNBIND, OnUnbindkey)
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


// CDlgKeyView message handlers
void CDlgKeyView::OnRButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default


	CDialog::OnRButtonUp(nFlags, point);
}

BOOL CDlgKeyView::OnInitDialog()
{
	CDialog::OnInitDialog();



	m_ListCtrl.InsertColumn(0, _T("卡号"));
	m_ListCtrl.InsertColumn(1, _T("充值时间"));
	m_ListCtrl.InsertColumn(2, _T("充值卡类型"));
	m_ListCtrl.InsertColumn(3, _T("剩余时间"));

    for(int i = 0; i < 4; i++){
	    m_ListCtrl.SetColumnWidth(i, LVSCW_AUTOSIZE_USEHEADER);
    }

	m_ListCtrl.SetExtendedStyle(LVS_EX_FULLROWSELECT);

	OnQuerykey();

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgKeyView::OnNMRClickListkey(NMHDR *pNMHDR, LRESULT *pResult)
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
	CDlgBindKey dlg;
	if(dlg.DoModal() == IDOK)
	{
		m_pSocket->BindKey(dlg.m_strKey);
	}
	
}

void CDlgKeyView::OnQuerykey()
{
	m_pSocket->Querykey();
}

void CDlgKeyView::UnBindResult(int nResult)
{
    if(nResult == result_ok){
        AfxMessageBox(_T("解绑完成"));
    }
    else if(nResult == result_unbind_errtime){
        AfxMessageBox(_T("24小时内只能解绑一次"));
    }
    else{
        AfxMessageBox(_T("解绑失败"));
    }
            
}

void CDlgKeyView::BindResult(int nResult)
{
    if(nResult == result_bind_used){
        AfxMessageBox(_T("这个卡号已经被使用"));
    }
    else if(nResult == result_ok){
        AfxMessageBox(_T("完成"));
    }
    else if(nResult == result_bind_errkey){
        AfxMessageBox(_T("不存在的卡号"));
    }
    else{
        AfxMessageBox(_T("未知的错误"));
    }
            
}
void CDlgKeyView::QueryKeyResult()
{
	m_ListCtrl.DeleteAllItems();
    int i;
	for(i = 0; i < m_pDoc->m_KeyVec.size(); i++){
		QUERYKEY_RET_BUF &retkey = m_pDoc->m_KeyVec[i];
		m_ListCtrl.InsertItem(i, retkey.key);
		m_ListCtrl.SetItemText(i, 1, retkey.buildtime);
		m_ListCtrl.SetItemText(i, 2, retkey.type);
		CString LeftTime;
		LeftTime.Format(_T("%d小时"), retkey.remaintime);
		m_ListCtrl.SetItemText(i, 3, LeftTime);
	}
    
    for(i = 0; i < 4; i++){
        m_ListCtrl.SetColumnWidth(i, LVSCW_AUTOSIZE_USEHEADER);
    }
}

void CDlgKeyView::OnUnbindkey()
{
	UINT i, uSelectedCount = m_ListCtrl.GetSelectedCount();
	int  nItem = -1;
	
	// Update all of the selected items.
	if (uSelectedCount > 0)
	{
		for (i=0;i < uSelectedCount;i++)
		{
			nItem = m_ListCtrl.GetNextItem(nItem, LVNI_SELECTED);
			ASSERT(nItem != -1);
			CString strKey = m_ListCtrl.GetItemText(nItem, 0);
			m_pSocket->Unbindkey(strKey);
		}
	}
}
