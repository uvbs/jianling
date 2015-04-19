// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "JLkit.h"
#include "MainFrm.h"
#include "JLkitView.h"
#include "JLkitDoc.h"
#include "JLkitSocket.h"
#include "settingdlg.h"
#include "ConfigMgr.h"



using namespace Gdiplus;


#ifdef _DEBUG
    #define new DEBUG_NEW
#endif



/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
    //{{AFX_MSG_MAP(CMainFrame)
    ON_WM_CREATE()
    ON_WM_CLOSE()
    ON_WM_DROPFILES()
    ON_WM_ACTIVATE()
    ON_WM_PAINT()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// arrays of IDs used to initialize control bars

static UINT BASED_CODE indicators[] =
{
    ID_SEPARATOR,           // status line indicator
    ID_INDICATOR_LOGINED,
    ID_INDICATOR_ALLNUMS,
    ID_INDICATOR_VALIDKEY
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
}


CMainFrame::~CMainFrame()
{

}


void CMainFrame::InitComBox()
{

    //获取配置
    CConfigMgr* pConfig  = CConfigMgr::GetInstance();


    //设置工作目录
    TCHAR szExe[MAX_PATH];
    GetModuleFileName(NULL, szExe, MAX_PATH);
    PathRemoveFileSpec(szExe);

    std::basic_string<TCHAR> strCurPath = szExe;
    strCurPath += _T("脚本");
    strCurPath += _T("*.ini");

    WIN32_FIND_DATA FindData;
    HANDLE hFinder = FindFirstFile(strCurPath.c_str(), &FindData);
    if(hFinder != INVALID_HANDLE_VALUE)
    {
        do
        {
            m_cbScript.AddString(FindData.cFileName);
        }
        while(FindNextFile(hFinder, &FindData));
    }
    else
    {
        m_cbScript.AddString(_T("default.ini"));
    }

    strCurPath = szExe;
    strCurPath += _T("配置");
    strCurPath += _T("*.ini");
    hFinder = FindFirstFile(strCurPath.c_str(), &FindData);
    if(hFinder != INVALID_HANDLE_VALUE)
    {
        do
        {
            m_cbConfig.AddString(FindData.cFileName);
        }
        while(FindNextFile(hFinder, &FindData));
    }
    else
    {
        m_cbConfig.AddString(_T("default.ini"));
    }


    //选中配置
    m_cbConfig.SelectString(-1, pConfig->m_szGameConfig.c_str());
    m_cbScript.SelectString(-1, pConfig->m_szGameScript.c_str());

}


int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    if(CFrameWnd::OnCreate(lpCreateStruct) == -1) return -1;


    //创建状态栏
    if(!m_wndStatusBar.Create(this) || !m_wndStatusBar.SetIndicators(indicators, sizeof(indicators) / sizeof(UINT)))
        return -1;

    //创建工具栏
    if(!m_wndToolBar.Create(this)) return -1;

    //平面风格
    m_wndToolBar.ModifyStyle(0, TBSTYLE_FLAT);

    //加载工具栏
    m_wndToolBar.LoadToolBar(IDR_MAINFRAME);


    int nIndex1 = m_wndToolBar.GetToolBarCtrl().CommandToIndex(ID_COMBO1);
    int nIndex2 = m_wndToolBar.GetToolBarCtrl().CommandToIndex(ID_COMBO2);
    m_wndToolBar.SetButtonInfo(nIndex1, ID_COMBO1, TBBS_SEPARATOR, 100);
    m_wndToolBar.SetButtonInfo(nIndex2, ID_COMBO2, TBBS_SEPARATOR, 150);


    //获取工具栏大小
    CRect rect;
    CRect rect2;
    m_wndToolBar.GetToolBarCtrl().GetItemRect(nIndex1, &rect);
    m_wndToolBar.GetToolBarCtrl().GetItemRect(nIndex2, &rect2);


    //创建列表框
    if(!m_cbConfig.Create(
                WS_VISIBLE | WS_CHILD | CBS_DROPDOWNLIST | CBS_AUTOHSCROLL | WS_VSCROLL | CBS_HASSTRINGS, rect, &m_wndToolBar, ID_COMBO1))
        return FALSE;

    if(!m_cbScript.Create(
                WS_VISIBLE | WS_CHILD | CBS_DROPDOWNLIST | CBS_AUTOHSCROLL | WS_VSCROLL | CBS_HASSTRINGS, rect2, &m_wndToolBar, ID_COMBO2))
        return FALSE;


    //列表框字体
    HFONT hFont = (HFONT)GetStockObject(DEFAULT_GUI_FONT);
    if(hFont == NULL) hFont = (HFONT)GetStockObject(ANSI_VAR_FONT);
    m_cbScript.SendMessage(WM_SETFONT, (WPARAM)hFont);
    m_cbConfig.SendMessage(WM_SETFONT, (WPARAM)hFont);

    //列表框
    InitComBox();

    return 0;
}


/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers

void CMainFrame::OnClose()
{

    //获取配置对象
    CConfigMgr* pConfig = CConfigMgr::GetInstance();
    TCHAR szStr[MAX_PATH];

    int inSel = m_cbConfig.GetCurSel();
    m_cbConfig.GetLBText(inSel, szStr);
    pConfig->m_szGameConfig = szStr;

    inSel = m_cbScript.GetCurSel();
    m_cbScript.GetLBText(inSel, szStr);
    pConfig->m_szGameScript = szStr;

    CFrameWnd::OnClose();
}


BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{

    if(!CFrameWnd::PreCreateWindow(cs)) return FALSE;

    static TCHAR szClassName[] = JLKITCLASSNAME;
    WNDCLASS wndc;

    if(::GetClassInfo(AfxGetInstanceHandle(), cs.lpszClass, &wndc))
    {
        wndc.hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
        wndc.lpszClassName = szClassName;
        VERIFY(AfxRegisterClass(&wndc));

        cs.lpszClass = szClassName;
    }

    cs.cx=600;
    cs.cy=400;
    return TRUE;
}
