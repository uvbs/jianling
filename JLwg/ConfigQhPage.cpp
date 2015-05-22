// ConfigQhPage.cpp : implementation file
//

#include "stdafx.h"
#include "JLwg.h"
#include "ConfigQhPage.h"
#include "GameConfig.h"
#include "gamedef.h"
#include "GamecallEx.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CConfigQhPage dialog


CConfigQhPage::CConfigQhPage(CWnd* pParent /*=NULL*/)
    : CPropertyPage(CConfigQhPage::IDD)
{
    //{{AFX_DATA_INIT(CConfigQhPage)
    m_HealthPercent = 0;
    //}}AFX_DATA_INIT
}


void CConfigQhPage::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CConfigQhPage)
    DDX_Control(pDX, IDC_COMBO_ITEMCOLOR, m_ComBox);
    DDX_Text(pDX, IDC_CHIYAOPERCENT, m_HealthPercent);
    DDV_MinMaxInt(pDX, m_HealthPercent, 1, 100);
    //}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CConfigQhPage, CDialog)
    //{{AFX_MSG_MAP(CConfigQhPage)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CConfigQhPage message handlers

BOOL CConfigQhPage::OnInitDialog()
{
    CDialog::OnInitDialog();

    //获取配置对象
    GameConfig* pConfig = GameConfig::GetInstance();

    m_ComBox.AddString(strGreen);
    m_ComBox.AddString(strBlue);
    m_ComBox.AddString(strPurple);
    m_ComBox.AddString(strOrange);
    m_ComBox.SetCurSel(-1);

    //获取颜色
    _ASSERTE(!pConfig->m_szQHColor.empty());
    int nIndex = m_ComBox.SelectString(-1, pConfig->m_szQHColor.c_str());
    _ASSERTE(nIndex != LB_ERR);

    m_HealthPercent = pConfig->m_HealthPercent;

    UpdateData(FALSE);
    return TRUE;  // return TRUE unless you set the focus to a control
    // EXCEPTION: OCX Property Pages should return FALSE
}


BOOL CConfigQhPage::OnApply()
{
    UpdateData();

    GameConfig* pConfig = GameConfig::GetInstance();

    pConfig->m_HealthPercent = m_HealthPercent;

    TCHAR szQHColor[BUFSIZ] = {0};
    int inSel = m_ComBox.GetCurSel();
    m_ComBox.GetLBText(inSel, szQHColor);
    pConfig->m_szQHColor = szQHColor;


    return CPropertyPage::OnApply();
}

BOOL CConfigQhPage::OnCommand(WPARAM wParam, LPARAM lParam)
{

    int Notifyid = HIWORD(wParam);
    if(Notifyid == EN_CHANGE || Notifyid == BM_CLICK)
    {
        SetModified();
    }


    return CDialog::OnCommand(wParam, lParam);
}


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
    BagVector BagVec;
    gcall.GetAllGoodsToVector(BagVec);
    for(i = 0; i < BagVec.size(); i++)
    {
    
        m_BagList.InsertItem(i, BagVec[i].name);

        CString strPos;
        strPos.Format(_T("%d"), BagVec[i].m_Info);
        m_BagList.SetItemText(i, 1, strPos);

    }

    ItemVector& SellItem = pConfig->m_SellItem;
    ItemVector& BankItem = pConfig->m_BankItem;
    ItemVector& DisenchantItem = pConfig->m_DisenchantItem;
    ItemVector& TradeItem = pConfig->m_TradeItem;
    ItemVector& DelItem = pConfig->m_DelItem;
    ItemVector& QHAccessories = pConfig->m_QHAccessories;    //强化饰品
    ItemVector& QHWeapons = pConfig->m_QHWeapons;    //强化武器

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

    //摧毁
    for(i = 0; i < QHAccessories.size(); i++)
    {
        m_FilterList.InsertItem(i, QHAccessories[i].c_str());
        m_FilterList.SetItemText(i, 1, strQHAccessories);
    }

    //摧毁
    for(i = 0; i < QHWeapons.size(); i++)
    {
        m_FilterList.InsertItem(i, QHWeapons[i].c_str());
        m_FilterList.SetItemText(i, 1, strQHWeapons);
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
    GetSelToFilterList(strBankItem);
}

void CConfigItemPage::OnConfigFenjie()
{
    GetSelToFilterList(strDisenchantItem);
}

void CConfigItemPage::OnConfigJiaoyi()
{
    GetSelToFilterList(strTradeItem);
}

void CConfigItemPage::OnConfigQhsp()
{
    GetSelToFilterList(strQHAccessories);
}

void CConfigItemPage::OnConfigQhwq()
{
    GetSelToFilterList(strQHWeapons);
}

void CConfigItemPage::OnConfigSell()
{
    GetSelToFilterList(strSellItem);
}

void CConfigItemPage::OnDblclkListBagsfilter(NMHDR* pNMHDR, LRESULT* pResult)
{
    NMLISTVIEW* pItem = (NMLISTVIEW*)pNMHDR;
    m_FilterList.DeleteItem(pItem->iItem);
    *pResult = 0;
}


BOOL CConfigItemPage::OnApply()
{
    UpdateData();

    GameConfig* pConfig = GameConfig::GetInstance();

    ItemVector& sell = pConfig-> m_SellItem;    //出售
    ItemVector& bank = pConfig-> m_BankItem;    //存仓
    ItemVector& disenchant = pConfig-> m_DisenchantItem;    //分解
    ItemVector& trade = pConfig-> m_TradeItem;    //交易
    ItemVector& dell = pConfig-> m_DelItem;    //删除
    ItemVector& qhacce = pConfig-> m_QHAccessories;    //强化饰品
    ItemVector& qhweapon = pConfig-> m_QHWeapons;    //强化武器

    sell.clear();
    bank.clear();
    disenchant.clear();
    trade.clear();
    dell.clear();
    qhacce.clear();
    qhweapon.clear();


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


    return TRUE;
}

BOOL CConfigItemPage::OnCommand(WPARAM wParam, LPARAM lParam)
{

    int Notifyid = HIWORD(wParam);
    if(Notifyid == NM_DBLCLK)
    {
        SetModified();
    }

    return CDialog::OnCommand(wParam, lParam);
}



/////////////////////////////////////////////////////////////////////////////
// CConfigObjPage dialog


CConfigObjPage::CConfigObjPage(CWnd* pParent /*=NULL*/)
    : CPropertyPage(CConfigObjPage::IDD)
{
    //{{AFX_DATA_INIT(CConfigObjPage)
    //}}AFX_DATA_INIT
}


void CConfigObjPage::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CConfigObjPage)
    DDX_Control(pDX, IDC_LIST_OBJECTFILTER, m_FilterList);
    DDX_Control(pDX, IDC_LIST_OBJECTS, m_ObjList);
    //}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CConfigObjPage, CDialog)
    //{{AFX_MSG_MAP(CConfigObjPage)
    ON_COMMAND(ID_CONFIG_REFRESH, OnConfigRefresh)
    ON_NOTIFY(NM_RCLICK, IDC_LIST_OBJECTS, OnRclickListObjects)
    ON_COMMAND(ID_CONFIG_FIRST, OnConfigFirst)
    ON_COMMAND(ID_CONFIG_DONTKILL, OnConfigDontkill)
    ON_NOTIFY(NM_DBLCLK, IDC_LIST_OBJECTFILTER, OnDblclkListObjectfilter)
    ON_COMMAND(ID_CONFIG_ALWAYSKILL, OnConfigAlwayskill)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CConfigObjPage message handlers

void CConfigObjPage::RefreshObj()
{

    //获取游戏外挂功能
    GamecallEx& gcall = *GamecallEx::GetInstance();

    m_ObjList.DeleteAllItems();
    ObjectVector RangeObject;

    gcall.GetRangeMonsterToVector(gcall.GetObjectBinTreeBaseAddr(), 10000, RangeObject);

    fPosition fmypos;
    gcall.GetPlayerPos(&fmypos);
    for(unsigned i = 0; i < RangeObject.size(); i++)
    {
        ObjectNode* pNode = RangeObject[i];
		_ASSERTE(pNode!=NULL);
        wchar_t* pName = gcall.GetObjectName(pNode->ObjAddress);
		_ASSERTE(pName!=NULL);
        m_ObjList.InsertItem(i, pName);

        fPosition tarpos;
        if(gcall.GetObjectPos(pNode, &tarpos))
        {
            CString strDis;
            strDis.Format(_T("%d"), gcall.CalcC(fmypos, tarpos));
            m_ObjList.SetItemText(i, 1, strDis);
        }
    }

}
BOOL CConfigObjPage::OnInitDialog()
{
    CDialog::OnInitDialog();

    m_ObjList.InsertColumn(0, _T("名称"));
    m_ObjList.InsertColumn(1, _T("距离"));
    m_ObjList.SetColumnWidth(0, 120);
    m_ObjList.SetColumnWidth(1, LVSCW_AUTOSIZE_USEHEADER);

    m_FilterList.InsertColumn(0, _T("名称"));
    m_FilterList.InsertColumn(1, _T("优先"));
    m_FilterList.SetColumnWidth(0, 120);
    m_FilterList.SetColumnWidth(1, LVSCW_AUTOSIZE_USEHEADER);


    m_ObjList.SetExtendedStyle(LVS_EX_FULLROWSELECT);
    m_FilterList.SetExtendedStyle(LVS_EX_FULLROWSELECT);

    GameConfig* pConfig = GameConfig::GetInstance();

    //优先
    ItemVector& FirstKill = pConfig->m_FirstKill;

    //不杀
    ItemVector& DontKill = pConfig->m_DontKill;

    //必杀
    ItemVector& AlwaysKill = pConfig->m_AlwaysKill;

    int i;
    for(i = 0; i < FirstKill.size(); i++)
    {
        m_FilterList.InsertItem(i, FirstKill[i].c_str());
        m_FilterList.SetItemText(i, 1, strFirstKill);
    }

    for(i = 0; i < DontKill.size(); i++)
    {
        m_FilterList.InsertItem(i, DontKill[i].c_str());
        m_FilterList.SetItemText(i, 1, strDontKill);

    }

    for(i = 0; i < AlwaysKill.size(); i++)
    {
        m_FilterList.InsertItem(i, AlwaysKill[i].c_str());
        m_FilterList.SetItemText(i, 1, strAlwaysKill);
    }

    //填充周围对象列表
    RefreshObj();
    return TRUE;  // return TRUE unless you set the focus to a control
    // EXCEPTION: OCX Property Pages should return FALSE
}


void CConfigObjPage::OnConfigRefresh()
{
    RefreshObj();
}

void CConfigObjPage::OnRclickListObjects(NMHDR* pNMHDR, LRESULT* pResult)
{
    POINT point;
    GetCursorPos(&point);

    CMenu menu;
    menu.LoadMenu(IDR_FILTER);
    menu.GetSubMenu(1)->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);

    *pResult = 0;
}

void CConfigObjPage::GetSelToFilterList(TCHAR szName[])
{
    POSITION pos = m_ObjList.GetFirstSelectedItemPosition();

    while(pos)
    {
        int nItem = m_ObjList.GetNextSelectedItem(pos);

        // you could do your own processing on nItem here
        CString strItem = m_ObjList.GetItemText(nItem, 0);

        //添加到过滤控件
        DWORD dwCount = m_FilterList.GetItemCount();
        m_FilterList.InsertItem(dwCount, strItem);
        m_FilterList.SetItemText(dwCount, 1, szName);
    }
}


void CConfigObjPage::OnConfigFirst()
{
    GetSelToFilterList(strFirstKill);
}

void CConfigObjPage::OnConfigDontkill()
{
    GetSelToFilterList(strDontKill);
}

void CConfigObjPage::OnDblclkListObjectfilter(NMHDR* pNMHDR, LRESULT* pResult)
{
    NMLISTVIEW* pItem = (NMLISTVIEW*)pNMHDR;
    m_FilterList.DeleteItem(pItem->iItem);
    *pResult = 0;
}


void CConfigObjPage::OnConfigAlwayskill()
{
    GetSelToFilterList(strAlwaysKill);
}

BOOL CConfigObjPage::OnApply()
{
    UpdateData();

    GameConfig* pConfig = GameConfig::GetInstance();

    ItemVector& dontkill = pConfig->m_DontKill;
    ItemVector& alwayskill = pConfig->m_AlwaysKill;
    ItemVector& firstkill = pConfig->m_FirstKill;

    dontkill.clear();
    alwayskill.clear();
    firstkill.clear();


    for(int i = 0; i < m_FilterList.GetItemCount(); i++)
    {
        CString strName = m_FilterList.GetItemText(i, 0);
        CString strAttri = m_FilterList.GetItemText(i, 1);
        if(strAttri == strDontKill)
        {
            dontkill.push_back((LPCTSTR)strName);
        }
        else if(strAttri == strFirstKill)
        {
            firstkill.push_back((LPCTSTR)strName);
        }
        else if(strAttri == strAlwaysKill)
        {
            alwayskill.push_back((LPCTSTR)strName);
        }
    }


    return TRUE;
}

BOOL CConfigObjPage::OnCommand(WPARAM wParam, LPARAM lParam)
{
    int Notifyid = HIWORD(wParam);
    if(Notifyid == NM_DBLCLK)
    {
        SetModified();
    }

    return CDialog::OnCommand(wParam, lParam);
}



/////////////////////////////////////////////////////////////////////////////
// CConfigPartyPage property page

IMPLEMENT_DYNCREATE(CConfigPartyPage, CPropertyPage)

CConfigPartyPage::CConfigPartyPage() : CPropertyPage(CConfigPartyPage::IDD)
{
    //{{AFX_DATA_INIT(CConfigPartyPage)

    m_bInvite_Auto = 0;
    m_bInvite_ALL = 0;
    m_bInvite_INMAP = 0;
    m_bInvite_Range = 0;
    m_nInvite_Range = 0;


    m_bAccept_INMAP = 0;
    m_bAccept_Auto = 0;
    m_bAccept_ALL = 0;
    m_bAccept_Range = 0;
    m_nAccept_Range = 0;
    //}}AFX_DATA_INIT
}

CConfigPartyPage::~CConfigPartyPage()
{
}

void CConfigPartyPage::DoDataExchange(CDataExchange* pDX)
{

    CPropertyPage::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CConfigPartyPage)
    DDX_Check(pDX, IDC_ACCEPT_ALL, m_bAccept_ALL);
    DDX_Check(pDX, IDC_ACCEPT_AUTO, m_bAccept_Auto);
    DDX_Check(pDX, IDC_ACCEPT_RANGE, m_bAccept_Range);
    DDX_Check(pDX, IDC_ACCEPT_INMAP, m_bAccept_INMAP);
    DDX_Text(pDX, IDC_ACCEPT_RANGE_VALUE, m_nAccept_Range);

    DDX_Check(pDX, IDC_INVITE_ALL, m_bInvite_ALL);
    DDX_Check(pDX, IDC_INVITE_AUTO, m_bInvite_Auto);
    DDX_Check(pDX, IDC_INVITE_RANGE, m_bInvite_Range);
    DDX_Check(pDX, IDC_INVITE_INMAP, m_bInvite_INMAP);
    DDX_Text(pDX, IDC_INVITE_RANGE_VALUE, m_nInvite_Range);
    //}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CConfigPartyPage, CPropertyPage)
    //{{AFX_MSG_MAP(CConfigPartyPage)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CConfigPartyPage message handlers

BOOL CConfigPartyPage::OnInitDialog()
{
    CPropertyPage::OnInitDialog();

    GameConfig* pConfig = GameConfig::GetInstance();

    m_bInvite_Auto  = pConfig->m_bInvite_Auto;
    m_bInvite_ALL   = pConfig->m_bInvite_ALL;
    m_bInvite_INMAP = pConfig->m_bAccept_INMAP;
    m_bInvite_Range = pConfig->m_bInvite_Range;
    m_nInvite_Range = pConfig->m_nInvite_Range;


    m_bAccept_Auto = pConfig->m_bAccept_Auto;
    m_bAccept_ALL = pConfig->m_bAccept_ALL;
    m_bAccept_INMAP = pConfig->m_bAccept_INMAP;
    m_bAccept_Range = pConfig->m_bAccept_Range;
    m_nAccept_Range = pConfig->m_nAccept_Range;

    UpdateData(FALSE);
    return TRUE;
}

BOOL CConfigPartyPage::OnApply()
{
    UpdateData();

    GameConfig* pConfig = GameConfig::GetInstance();
    pConfig->m_bInvite_Auto = m_bInvite_Auto ;
    pConfig->m_bInvite_ALL = m_bInvite_ALL   ;
    pConfig->m_bInvite_INMAP = m_bInvite_INMAP ;
    pConfig->m_bInvite_Range = m_bInvite_Range;
    pConfig->m_nInvite_Range =  m_nInvite_Range ;


    pConfig->m_bAccept_Auto = m_bAccept_Auto ;
    pConfig->m_bAccept_ALL = m_bAccept_ALL;
    pConfig->m_bAccept_INMAP =  m_bAccept_INMAP ;
    pConfig->m_bAccept_Range = m_bAccept_Range ;
    pConfig->m_nAccept_Range = m_nAccept_Range ;


    return CPropertyPage::OnApply();
}



BOOL CConfigPartyPage::OnCommand(WPARAM wParam, LPARAM lParam)
{

    int Notifyid = HIWORD(wParam);
    if(Notifyid == EN_CHANGE ||
            Notifyid == BM_SETCHECK)
    {
        SetModified();
    }

    return CPropertyPage::OnCommand(wParam, lParam);
}
