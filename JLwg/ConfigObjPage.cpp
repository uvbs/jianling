// ConfigObjPage.cpp : implementation file
//

#include "stdafx.h"
#include "JLwg.h"
#include "ConfigObjPage.h"

#include "GamecallEx.h"
#include "GameConfig.h"
#include "..\common\cinifile.h"


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
    ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_OBJECTFILTER, OnItemchangedListObjectfilter)
    ON_NOTIFY(LVN_DELETEITEM, IDC_LIST_OBJECTFILTER, OnDeleteitemListObjectfilter)
    ON_NOTIFY(LVN_INSERTITEM, IDC_LIST_OBJECTFILTER, OnInsertitemListObjectfilter)
    ON_COMMAND(ID_CONFIG_ALWAYSKILL, OnConfigAlwayskill)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CConfigObjPage message handlers

void CConfigObjPage::RefreshObj()
{

    //获取游戏外挂功能
    GamecallEx& gcall = *GamecallEx::Instance();

    m_ObjList.DeleteAllItems();
    ObjectVector RangeObject;
    TRACE(_T("GetRangeMonsterToVector"));
    gcall.GetRangeMonsterToVector(10000, RangeObject);

    fPosition fmypos;
    gcall.GetPlayerPos(&fmypos);
    TRACE1("GetRangeMonsterToVector:%d", RangeObject.size());
    for(unsigned i = 0; i < RangeObject.size(); i++) {
        ObjectNode* pNode = RangeObject[i];

        wchar_t* pName = gcall.GetObjectName(pNode->ObjAddress);
        m_ObjList.InsertItem(i, pName);

        fPosition tarpos;
        if(gcall.GetObjectPos(pNode, &tarpos)) {
            DWORD dis = gcall.CalcC(fmypos, tarpos);
            CString strDis;
            strDis.Format(_T("%d"), dis);
            m_ObjList.SetItemText(i, 1, strDis);
        }
    }
}
BOOL CConfigObjPage::OnInitDialog()
{
    CDialog::OnInitDialog();

    // TODO: Add extra initialization here
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

    GameConfig* pConfig = GameConfig::Instance();

    //TODO: 

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
    if(pos == NULL) {
        TRACE0("No items were selected!\n");
    }
    else {
        while(pos) {
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

void CConfigObjPage::OnItemchangedListObjectfilter(NMHDR* pNMHDR, LRESULT* pResult)
{
    NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
    // TODO: Add your control notification handler code here
    *pResult = 0;
}

void CConfigObjPage::OnDeleteitemListObjectfilter(NMHDR* pNMHDR, LRESULT* pResult)
{
    NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
    // TODO: Add your control notification handler code here
    SetModified();
    *pResult = 0;
}

void CConfigObjPage::OnInsertitemListObjectfilter(NMHDR* pNMHDR, LRESULT* pResult)
{
    NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
    // TODO: Add your control notification handler code here
    SetModified();
    *pResult = 0;
}

void CConfigObjPage::OnConfigAlwayskill()
{
    // TODO: Add your command handler code here
    GetSelToFilterList(strAlwaysKill);
}
