// ConfigItemPage.cpp : implementation file
//

#include "stdafx.h"
#include "JLwg.h"
#include "ConfigItemPage.h"
#include "GamecallEx.h"
#include "GameConfig.h"

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

    //获取对象
    GamecallEx& gcall = *GamecallEx::GetInstance();
    GameConfig* pConfig = GameConfig::GetInstance();

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

    ItemVector& SellItem = pConfig->m_SellItem;
    ItemVector& BankItem = pConfig->m_BankItem;
    ItemVector& DisenchantItem = pConfig->m_DisenchantItem;
    ItemVector& TradeItem = pConfig->m_TradeItem;
    ItemVector& DelItem = pConfig->m_DelItem;


    //出售
    for(i = 0; i < SellItem.size(); i++)
    {
        m_FilterList.InsertItem(i, SellItem[i].c_str());
        m_FilterList.SetItemText(i, 1, strSellItem);
    }

    //存仓
    for(i = 0; i < BankItem.size(); i++)
    {
        m_FilterList.InsertItem(i, BankItem[i].c_str());
        m_FilterList.SetItemText(i, 1, strBankItem);
    }
    //分解
    for(i = 0; i < DisenchantItem.size(); i++)
    {
        m_FilterList.InsertItem(i, DisenchantItem[i].c_str());
        m_FilterList.SetItemText(i, 1, strDisenchantItem);
    }
    //交易
    for(i = 0; i < TradeItem.size(); i++)
    {
        m_FilterList.InsertItem(i, TradeItem[i].c_str());
        m_FilterList.SetItemText(i, 1, strTradeItem);
    }
    //摧毁
    for(i = 0; i < DelItem.size(); i++)
    {
        m_FilterList.InsertItem(i, DelItem[i].c_str());
        m_FilterList.SetItemText(i, 1, strDelItem);
    }

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
    while(pos)
    {
        int nItem = m_BagList.GetNextSelectedItem(pos);

        // you could do your own processing on nItem here
        CString strItem = m_BagList.GetItemText(nItem, 0);

        //添加到过滤控件
        DWORD dwCount = m_FilterList.GetItemCount();
        m_FilterList.InsertItem(dwCount, strItem);
        m_FilterList.SetItemText(dwCount, 1, szName);
    }
}
void CConfigItemPage::OnConfigCuncang()
{
    // TODO: Add your command handler code here
    GetSelToFilterList(strBankItem);
}

void CConfigItemPage::OnConfigFenjie()
{
    // TODO: Add your command handler code here
    GetSelToFilterList(strDisenchantItem);
}

void CConfigItemPage::OnConfigJiaoyi()
{
    // TODO: Add your command handler code here
    GetSelToFilterList(strTradeItem);
}

void CConfigItemPage::OnConfigQhsp()
{
    // TODO: Add your command handler code here
    GetSelToFilterList(strQHAccessories);
}

void CConfigItemPage::OnConfigQhwq()
{
    // TODO: Add your command handler code here
    GetSelToFilterList(strQHWeapons);
}

void CConfigItemPage::OnConfigSell()
{
    // TODO: Add your command handler code here
    GetSelToFilterList(strSellItem);
}

void CConfigItemPage::OnDblclkListBagsfilter(NMHDR* pNMHDR, LRESULT* pResult)
{
    NMLISTVIEW* pItem = (NMLISTVIEW*)pNMHDR;
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

BOOL CConfigItemPage::OnApply()
{
    GameConfig* pConfig = GameConfig::GetInstance();

    ItemVector& sell = pConfig-> m_SellItem;    //出售
    ItemVector& bank = pConfig-> m_BankItem;    //存仓
    ItemVector& disenchant = pConfig-> m_DisenchantItem;    //分解
    ItemVector& trade = pConfig-> m_TradeItem;    //交易
    ItemVector& dell = pConfig-> m_DelItem;    //删除
    ItemVector& qhacce = pConfig-> m_QHAccessories;    //强化饰品
    ItemVector& qhweapon = pConfig-> m_QHWeapons;    //强化武器


    for(int i = 0; i < m_FilterList.GetItemCount(); i++)
    {
        TCHAR szName[MAX_PATH];
        m_FilterList.GetItemText(i, 0, szName, MAX_PATH);
        CString strAttri = m_FilterList.GetItemText(i, 1);
        if(strAttri == strSellItem)
        {
            sell.push_back(szName);
        }
        else if(strAttri == strDelItem)
        {
            dell.push_back(szName);
        }
        else if(strAttri == strTradeItem)
        {
            trade.push_back(szName);
        }
        else if(strAttri == strDisenchantItem)
        {
            disenchant.push_back(szName);
        }
        else if(strAttri == strQHAccessories)
        {
            qhacce.push_back(szName);
        }
        else if(strAttri == strQHWeapons)
        {
            qhweapon.push_back(szName);
        }
        else if(strAttri == strBankItem)
        {
            bank.push_back(szName);
        }

    }

    pConfig->SaveConfig();

    return TRUE;
}