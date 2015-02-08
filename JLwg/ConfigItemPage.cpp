// ConfigItemPage.cpp : implementation file
//

#include "stdafx.h"
#include "JLwg.h"
#include "ConfigItemPage.h"
#include "GamecallEx.h"
#include "..\common\common.h"
#include "..\common\CIniFile.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CConfigItemPage dialog


CConfigItemPage::CConfigItemPage(CWnd* pParent /*=NULL*/)
	: CPropertyPage(CConfigItemPage::IDD)
{
	//{{AFX_DATA_INIT(CConfigItemPage)
	//}}AFX_DATA_INIT
}


void CConfigItemPage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CConfigItemPage)
	DDX_Control(pDX, IDC_LIST_BAGSFILTER, m_FilterList);
	DDX_Control(pDX, IDC_LIST_BAGS, m_BagList);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CConfigItemPage, CDialog)
	//{{AFX_MSG_MAP(CConfigItemPage)
	ON_NOTIFY(NM_RCLICK, IDC_LIST_BAGS, OnRclickListBags)
	ON_COMMAND(ID_CONFIG_CUNCANG, OnConfigCuncang)
	ON_COMMAND(ID_CONFIG_FENJIE, OnConfigFenjie)
	ON_COMMAND(ID_CONFIG_JIAOYI, OnConfigJiaoyi)
	ON_COMMAND(ID_CONFIG_QHSP, OnConfigQhsp)
	ON_COMMAND(ID_CONFIG_QHWQ, OnConfigQhwq)
	ON_COMMAND(ID_CONFIG_SELL, OnConfigSell)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_BAGSFILTER, OnDblclkListBagsfilter)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_BAGSFILTER, OnItemchangedListBagsfilter)
	ON_NOTIFY(LVN_INSERTITEM, IDC_LIST_BAGSFILTER, OnInsertitemListBagsfilter)
	ON_NOTIFY(LVN_DELETEITEM, IDC_LIST_BAGSFILTER, OnDeleteitemListBagsfilter)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CConfigItemPage message handlers

BOOL CConfigItemPage::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_BagList.InsertColumn(0, _T("名称"));
	m_BagList.InsertColumn(1, _T("位置"));
	m_BagList.SetColumnWidth(0, 150);
	m_BagList.SetColumnWidth(1, LVSCW_AUTOSIZE_USEHEADER);

	m_FilterList.InsertColumn(0, _T("名称"));
	m_FilterList.InsertColumn(1, _T("位置"));
	m_FilterList.SetColumnWidth(0, 150);
	m_FilterList.SetColumnWidth(1, LVSCW_AUTOSIZE_USEHEADER);

	m_BagList.SetExtendedStyle(LVS_EX_FULLROWSELECT);
	m_FilterList.SetExtendedStyle(LVS_EX_FULLROWSELECT);

	int i = 0;
	
	//填充背包
	std::vector<_BAGSTU> GoodsVec;
	gcall.GetAllGoodsToVector(GoodsVec);
	for(i = 0; i < GoodsVec.size(); i++)
	{
		m_BagList.InsertItem(i, GoodsVec[i].name);

		CString strPos;
		strPos.Format(_T("%d"), GoodsVec[i].m_Info);
		m_BagList.SetItemText(i, 1, strPos);
		
	}

	CCIniFile ConfigFile;
	ConfigFile.Open(gcall.GetConfigPath());

	//填充已经存在的过滤到控件中
	wchar_t *szSell = NULL;
	wchar_t *szCunCang  = NULL;
	wchar_t *szJioayi = NULL;
	wchar_t *szFenjie = NULL;
	wchar_t *szQhWuqi = NULL;
	wchar_t *szQhShipin  = NULL;


	szSell = ConfigFile.GetProfileString(strSell, strItemName);
	szJioayi = ConfigFile.GetProfileString(strJiaoyi, strItemName);
	szCunCang = ConfigFile.GetProfileString(strCunCang, strItemName);
	szQhShipin = ConfigFile.GetProfileString(strQhShipin, strItemName);
	szQhWuqi = ConfigFile.GetProfileString(strQhWuqi, strItemName);
	szFenjie = ConfigFile.GetProfileString(strFenjie, strItemName);

	
	i = m_FilterList.GetItemCount();

	wchar_t *token = wcstok(szCunCang, L";"); // C4996
	while( token != NULL )
	{
		m_FilterList.InsertItem(i, token);
		m_FilterList.SetItemText(i, 1, strCunCang);
		i++;

		// Get next token: 
		token = wcstok(NULL, L";"); // C4996
	}




	token = wcstok(szSell, L";"); // C4996
	while( token != NULL )
	{
		m_FilterList.InsertItem(i, token);
		m_FilterList.SetItemText(i, 1, strSell);
		i++;

		// Get next token: 
		token = wcstok(NULL, L";"); // C4996
	}



	token = wcstok(szFenjie, L";"); // C4996
	while( token != NULL )
	{
		m_FilterList.InsertItem(i, token);
		m_FilterList.SetItemText(i, 1, strFenjie);
		i++;

		// Get next token: 
		token = wcstok(NULL, L";"); // C4996
	}


	
	token = wcstok(szJioayi, L";"); // C4996
	while( token != NULL )
	{
		m_FilterList.InsertItem(i, token);
		m_FilterList.SetItemText(i, 1, strJiaoyi);
		i++;

		// Get next token: 
		token = wcstok(NULL, L";"); // C4996
	}



	token = wcstok(szQhWuqi, L";"); // C4996
	while( token != NULL )
	{
		m_FilterList.InsertItem(i, token);
		m_FilterList.SetItemText(i, 1, strQhWuqi);
		i++;

		// Get next token: 
		token = wcstok(NULL, L";"); // C4996
	}




	token = wcstok(szQhShipin, L";"); // C4996
	while( token != NULL )
	{
		m_FilterList.InsertItem(i, token);
		m_FilterList.SetItemText(i, 1, strQhShipin);
		i++;

		// Get next token: 
		token = wcstok(NULL, L";"); // C4996
	}



	delete []szQhShipin;
	delete []szQhWuqi;
	delete []szFenjie;
	delete []szJioayi;
	delete []szCunCang;
	delete []szSell;
	

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CConfigItemPage::OnRclickListBags(NMHDR* pNMHDR, LRESULT* pResult) 
{
	POINT point;
	GetCursorPos(&point);
	
	CMenu menu;
	menu.LoadMenu(IDR_FILTER);
	menu.GetSubMenu(0)->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);
	*pResult = 0;
}

void CConfigItemPage::GetSelToFilterList(TCHAR szName[])
{
	POSITION pos = m_BagList.GetFirstSelectedItemPosition();
	if (pos == NULL)
		TRACE0("No items were selected!\n");
	else
	{
		while(pos)
		{
			int nItem = m_BagList.GetNextSelectedItem(pos);
			TRACE1("Item %d was selected!\n", nItem);
			// you could do your own processing on nItem here
			CString strItem = m_BagList.GetItemText(nItem, 0);

			//添加到过滤控件
			DWORD dwCount = m_FilterList.GetItemCount();
			m_FilterList.InsertItem(dwCount, strItem);
			m_FilterList.SetItemText(dwCount, 1, szName);
		}
	}
}
void CConfigItemPage::OnConfigCuncang() 
{
	// TODO: Add your command handler code here
	GetSelToFilterList(strCunCang);
}

void CConfigItemPage::OnConfigFenjie() 
{
	// TODO: Add your command handler code here
	GetSelToFilterList(strFenjie);
}

void CConfigItemPage::OnConfigJiaoyi() 
{
	// TODO: Add your command handler code here
	GetSelToFilterList(strJiaoyi);
}

void CConfigItemPage::OnConfigQhsp() 
{
	// TODO: Add your command handler code here
	GetSelToFilterList(strQhShipin);
}

void CConfigItemPage::OnConfigQhwq() 
{
	// TODO: Add your command handler code here
	GetSelToFilterList(strQhWuqi);
}

void CConfigItemPage::OnConfigSell() 
{
	// TODO: Add your command handler code here
	GetSelToFilterList(strSell);
}

void CConfigItemPage::OnDblclkListBagsfilter(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NMLISTVIEW *pItem = (NMLISTVIEW*)pNMHDR;
	m_FilterList.DeleteItem(pItem->iItem);
	*pResult = 0;
}

void CConfigItemPage::OnItemchangedListBagsfilter(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here

	*pResult = 0;
}

void CConfigItemPage::OnInsertitemListBagsfilter(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
	SetModified();
	*pResult = 0;
}

void CConfigItemPage::OnDeleteitemListBagsfilter(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
	SetModified();
	*pResult = 0;
}
