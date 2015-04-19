// ConfigObjPage.cpp : implementation file
//

#include "stdafx.h"
#include "JLwg.h"
#include "ConfigObjPage.h"
#include "GamecallEx.h"
#include "GameConfig.h"

#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

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

    gcall.GetRangeMonsterToVector(10000, RangeObject);

    fPosition fmypos;
    gcall.GetPlayerPos(&fmypos);
    TRACE1("GetRangeMonsterToVector:%d", RangeObject.size());
    for(unsigned i = 0; i < RangeObject.size(); i++)
    {
        ObjectNode* pNode = RangeObject[i];

        wchar_t* pName = gcall.GetObjectName(pNode->ObjAddress);
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

    //战斗优先
    ItemVector& FirstKill = pConfig->m_FirstKill;

    //战斗不杀
    ItemVector& DontKill = pConfig->m_DontKill;

    //战斗必杀
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
    // TODO: Add your control notification handler code here
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
    if(pos == NULL)
    {
        TRACE0("No items were selected!\n");
    }
    else
    {
        while(pos)
        {
            int nItem = m_ObjList.GetNextSelectedItem(pos);
            TRACE1("Item %d was selected!\n", nItem);
            // you could do your own processing on nItem here
            CString strItem = m_ObjList.GetItemText(nItem, 0);

            //添加到过滤控件
            DWORD dwCount = m_FilterList.GetItemCount();
            m_FilterList.InsertItem(dwCount, strItem);
            m_FilterList.SetItemText(dwCount, 1, szName);
        }
    }
}


void CConfigObjPage::OnConfigFirst()
{
    // TODO: Add your command handler code here
    GetSelToFilterList(strFirstKill);
}

void CConfigObjPage::OnConfigDontkill()
{
    // TODO: Add your command handler code here
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
    // TODO: Add your command handler code here
    GetSelToFilterList(strAlwaysKill);
}

BOOL CConfigObjPage::OnApply()
{
    UpdateData();

    GameConfig *pConfig = GameConfig::GetInstance();

    ItemVector& dontkill = pConfig->m_DontKill;
    ItemVector& alwayskill = pConfig->m_AlwaysKill;
    ItemVector& firstkill = pConfig->m_FirstKill;
    
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
