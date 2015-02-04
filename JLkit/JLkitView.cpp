// JLkitView.cpp: implementation of the CJLkitView class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "JLkit.h"
#include "MainFrm.h"
#include "JLkitView.h"
#include "JLkitDoc.h"
#include "JLkitSocket.h"
#include "LaunchGameThread.h"
#include "MyWork.h"
#include "BugRepDlg.h"

#include "..\common\common.h"
#include "..\common\Inject.h"
#include "..\common\Webpost.h"
#include "..\common\ThreadPool.h"




//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

IMPLEMENT_DYNCREATE(CJLkitView, CListView)


BEGIN_MESSAGE_MAP(CJLkitView, CListView)
    //{{AFX_MSG_MAP(CJLkitView)
    ON_WM_CREATE()
    ON_COMMAND(ID_START, OnStart)
    ON_UPDATE_COMMAND_UI(ID_GETANDACTIVE, OnUpdateStart)
    ON_NOTIFY_REFLECT(NM_RCLICK, OnRclick)
    ON_COMMAND(ID_PROFILE, OnProfile)
    ON_COMMAND(ID_GETANDACTIVE, OnGetAndActive)
    ON_UPDATE_COMMAND_UI(ID_PROFILE, OnUpdateProfile)
    ON_UPDATE_COMMAND_UI(ID_SELECTALL, OnUpdateSelectall)
    ON_COMMAND(ID_REPORTBUG, OnReportbug)
    ON_WM_RBUTTONUP()
    ON_COMMAND(ID_GET, OnGet)
    ON_COMMAND(ID_ACTIVE, OnActive)
    ON_UPDATE_COMMAND_UI(ID_GET, OnUpdateStart)
    ON_UPDATE_COMMAND_UI(ID_ACTIVE, OnUpdateStart)
    ON_UPDATE_COMMAND_UI(ID_START, OnUpdateStart)
    ON_WM_TIMER()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()


CJLkitView::CJLkitView()
{
    m_lpLaunchThread = NULL;
    m_dwDefaultStyle |= LVS_REPORT;
}

CJLkitView::~CJLkitView()
{
}


BOOL CJLkitView::PreCreateWindow(CREATESTRUCT& cs)
{
    return CListView::PreCreateWindow(cs);
}



int CJLkitView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    if(CListView::OnCreate(lpCreateStruct) == -1)
        return -1;

    CString strHeading;

    for(int i = 0; i < COLUMN_TEXT_NUMS; i++)
    {
        strHeading.LoadString(IDS_STRING128 + i);
        GetListCtrl().InsertColumn(i, (LPCTSTR)strHeading, LVCFMT_LEFT);
        GetListCtrl().SetColumnWidth(i, LVSCW_AUTOSIZE_USEHEADER);
    }

    GetListCtrl().SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_CHECKBOXES);
//    CHeaderCtrl* pHeadctrl = GetListCtrl().GetHeaderCtrl();
    //   pHeadctrl->ModifyStyle(0, HDS_CHECKBOXES);
    return 0;
}



void CJLkitView::OnProfile()
{
    CJLkitDoc* pDoc = GetDocument();
    POSITION rpos = GetListCtrl().GetFirstSelectedItemPosition();

    if(rpos != NULL)
    {
        int nItem = GetListCtrl().GetNextSelectedItem(rpos);
        CString strName = GetListCtrl().GetItemText(nItem, COLUMN_TEXT_ACCOUNT);
        CString strPw = GetListCtrl().GetItemText(nItem, COLUMN_TEXT_PASSWORD);
        CString strConfig = GetListCtrl().GetItemText(nItem, COLUMN_TEXT_CONFIG);
        CString strScript = GetListCtrl().GetItemText(nItem, COLUMN_TEXT_SCRIPT);
        pDoc->LaunchGame(strName, strPw, strConfig, strScript, 1);
    }
}


// RESULT_FAIL_EXCEPTION,
// RESULT_FAIL_CAPTCHA		,
// RESULT_FAIL_IPBLOCK	,
// RESULT_FAIL_PWERROR	,
// RESULT_FAIL_AUTH		,
// RESULT_FAIL_NOACTIVEITEMS,
// RESULT_FAIL_ACTIVEITEMSERR	,
// RESULT_FAIL_TIMEOUT	,
// RESULT_SUCCESS,
// RESULT_GET_ALEADY	,
// RESULT_GET_ERROR,
// RESULT_LOGIN_NOUKEY
// };

void CJLkitView::SetResult(int nReslt, int i)
{
    if(nReslt == RESULT_SUCCESS)
    {
        GetListCtrl().SetItemText(i, COLUMN_TEXT_STATUS, _T("运行中.."));
        GetListCtrl().SetCheck(i);
    }
    else if(nReslt == RESULT_FAIL_CAPTCHA)
        GetListCtrl().SetItemText(i, COLUMN_TEXT_STATUS, _T("需要验证码"));
    else if(nReslt == RESULT_FAIL_IPBLOCK)
        GetListCtrl().SetItemText(i, COLUMN_TEXT_STATUS, _T("IP BLOCK"));
    else if(nReslt == RESULT_FAIL_GETUKEY)
        GetListCtrl().SetItemText(i, COLUMN_TEXT_STATUS, _T("无法获取UKEY"));
    else if(nReslt == RESULT_NOKEY)
        GetListCtrl().SetItemText(i, COLUMN_TEXT_STATUS, _T("没有有效KEY"));
    else if(nReslt == RESULT_ALREADY_RUNNING)
        GetListCtrl().SetItemText(i, COLUMN_TEXT_STATUS, _T("已经在运行.."));
    else if(nReslt == RESULT_GET_ALEADY)
        GetListCtrl().SetItemText(i, COLUMN_TEXT_STATUS, _T("已经领取过"));
    else if(nReslt == RESULT_GET_ERROR)
        GetListCtrl().SetItemText(i, COLUMN_TEXT_STATUS, _T("领取失败"));
    else if(nReslt == RESULT_FAIL_TIMEOUT)
        GetListCtrl().SetItemText(i, COLUMN_TEXT_STATUS, _T("超时"));
    else if(nReslt == RESULT_FAIL_NOACTIVEITEMS)
        GetListCtrl().SetItemText(i, COLUMN_TEXT_STATUS, _T("无需激活"));
    else if(nReslt == RESULT_FAIL_PWERROR)
        GetListCtrl().SetItemText(i, COLUMN_TEXT_STATUS, _T("密码错误"));
    else if(nReslt == RESULT_FAIL_CREATEGAMEPROCESS)
        GetListCtrl().SetItemText(i, COLUMN_TEXT_STATUS, _T("创建进程错误"));
}


void CJLkitView::OnStart()
{
    if(m_lpLaunchThread == NULL)
    {
        m_lpLaunchThread = (CLaunchThread*)
                           AfxBeginThread(RUNTIME_CLASS(CLaunchThread), THREAD_PRIORITY_NORMAL,
                                          0, CREATE_SUSPENDED);
        m_lpLaunchThread->SetOwner(this);
        m_lpLaunchThread->ResumeThread();
    }
}


void CJLkitView::LaunchGame()
{
    Webpost::InitCom();
    CJLkitDoc* pDoc = GetDocument();
    CListCtrl& list = GetListCtrl();

    //当前选中的条目
    for(int i = 0; i < list.GetItemCount(); i++)
    {
        if(list.GetCheck(i))
        {
            CString strName = list.GetItemText(i, COLUMN_TEXT_ACCOUNT);
            CString strPw = list.GetItemText(i, COLUMN_TEXT_PASSWORD);
            CString strConfig = list.GetItemText(i, COLUMN_TEXT_CONFIG);
            CString strScript = list.GetItemText(i, COLUMN_TEXT_SCRIPT);
            list.SetItemText(i, COLUMN_TEXT_STATUS, _T("开始运行.."));
            int nReslt = pDoc->LaunchGame(strName, strPw, strConfig, strScript);
            SetResult(nReslt, i);
        }
    }

    Webpost::UnInitCom();
}


void CJLkitView::OnUpdateStart(CCmdUI* pCmdUI)
{
    // TODO: Add your command update UI handler code here
    pCmdUI->Enable(FALSE);
    int count = GetListCtrl().GetItemCount();

    for(int i = 0; i < count; i++)
    {
        if(GetListCtrl().GetCheck(i))
        {
            pCmdUI->Enable();
            break;
        }
    }

    if(GetListCtrl().GetSelectedCount() != 0)
        pCmdUI->Enable();

    if(m_lpLaunchThread)
    {
        DWORD dwExitCode = 0;
        GetExitCodeThread(m_lpLaunchThread->m_hThread, &dwExitCode);

        if(dwExitCode == STILL_ACTIVE)
            pCmdUI->Enable(FALSE);
    }
}


void CJLkitView::OnGet()
{
    // TODO: Add your command handler code here
    int count = GetListCtrl().GetItemCount();
    CJLkitDoc* pDoc = GetDocument();

    for(int i = 0; i < count; i++)
    {
        if(GetListCtrl().GetCheck(i))
        {
            CString strName = GetListCtrl().GetItemText(i, COLUMN_TEXT_ACCOUNT);
            CString strPw = GetListCtrl().GetItemText(i, COLUMN_TEXT_PASSWORD);
            int nRet = pDoc->Get(strName, strPw);
            SetResult(nRet, i);
        }
    }
}

void CJLkitView::OnActive()
{
    // TODO: Add your command handler code here
    int count = GetListCtrl().GetItemCount();
    CJLkitDoc* pDoc = GetDocument();

    for(int i = 0; i < count; i++)
    {
        if(GetListCtrl().GetCheck(i))
        {
            CString strName = GetListCtrl().GetItemText(i, COLUMN_TEXT_ACCOUNT);
            CString strPw = GetListCtrl().GetItemText(i, COLUMN_TEXT_PASSWORD);
            GetListCtrl().SetItemText(i, COLUMN_TEXT_STATUS, _T("正在登录"));
            int nRet = pDoc->Active(strName, strPw);
            SetResult(nRet, i);
        }
    }
}


void CJLkitView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint)
{
}

void CJLkitView::OnRclick(NMHDR* pNMHDR, LRESULT* pResult)
{
    POINT point;
    GetCursorPos(&point);
    CMenu menu;
    menu.LoadMenu(IDR_MAINFRAME);
    menu.GetSubMenu(1)->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, (CMainFrame*)AfxGetMainWnd());
    *pResult = 0;
}

void CJLkitView::OnInitialUpdate()
{
    CListView::OnInitialUpdate();
    //创建一个定时器
    SetTimer(IDT_HEART, 5000, NULL);
    SetTimer(IDT_TIMERGAMEEXIT, 2000, NULL);
    SetTimer(IDT_TIMERPOSTKEYQUERY, 30000, NULL);
}


void CJLkitView::OnGetAndActive()
{
    CJLkitDoc* pDoc = GetDocument();
    CThreadPool* lpTpool = pDoc->m_lpTPool;
    pDoc->GetandActive();
    int count = GetListCtrl().GetItemCount();

    for(int i = 0; i < count; i++)
    {
        if(GetListCtrl().GetCheck(i))
            lpTpool->AddWork(new MyCWork(i, this));
    }
}


void CJLkitView::SerializeText(CArchive& ar)
{
    // TODO: Add your command handler code here
    if(ar.IsStoring())
    {
    }
    else
    {
        CJLkitDoc* pDoc = GetDocument();
        GetListCtrl().DeleteAllItems();
        CString strDefault(_T("Default"));
        CString strLine;
        int count = 0;

        while(ar.ReadString(strLine))
        {
            CString strName;
            CString strPw;
            Webpost::GetPwName(strLine, strName, strPw);

            if(strName != _T("") && strPw != _T(""))
            {
                GetListCtrl().InsertItem(count, _T(""));
                GetListCtrl().SetItemText(count, COLUMN_TEXT_ACCOUNT, strName);
                GetListCtrl().SetItemText(count, COLUMN_TEXT_PASSWORD, strPw);
                GetListCtrl().SetItemText(count, COLUMN_TEXT_SCRIPT, strDefault);
                GetListCtrl().SetItemText(count, COLUMN_TEXT_CONFIG, strDefault);
                count++;
            }
        }

        for(int i = 0; i < COLUMN_TEXT_NUMS; i++)
            GetListCtrl().SetColumnWidth(i, LVSCW_AUTOSIZE_USEHEADER);

        pDoc->m_share.Close();
        pDoc->m_share.Create(count, SHAREOBJNAME);
    }
}

void CJLkitView::OnUpdateProfile(CCmdUI* pCmdUI)
{
    // TODO: Add your command update UI handler code here
    pCmdUI->Enable(FALSE);
    int count = GetListCtrl().GetItemCount();

    for(int i = 0; i < count; i++)
    {
        if(GetListCtrl().GetCheck(i))
        {
            pCmdUI->Enable();
            break;
        }
    }

    if(GetListCtrl().GetSelectedCount() != 0)
        pCmdUI->Enable();
}

void CJLkitView::OnUpdateSelectall(CCmdUI* pCmdUI)
{
}

void CJLkitView::OnReportbug()
{
    // TODO: Add your command handler code here
    CJLkitDoc* pDoc = GetDocument();
    CDlgBugRep dlg(pDoc);
    dlg.DoModal();
}

void CJLkitView::OnTimer(UINT nIDEvent)
{
    // TODO: Add your message handler code here and/or call default
    if(nIDEvent == IDT_TIMERGAMEEXIT)
    {
        //每次遍历所有item, 判断item的pid存不存在, 不存在就是游戏退出了
        for(int i = 0; i < GetListCtrl().GetItemCount(); i++)
        {
            CString strName = GetListCtrl().GetItemText(i, COLUMN_TEXT_ACCOUNT);

            if(GetDocument()->m_share.IsPidValid((LPCTSTR)strName) == FALSE)
            {
                GetDocument()->m_share.Del((LPCTSTR)strName);
                GetListCtrl().SetItemText(i, COLUMN_TEXT_STATUS, _T("进程退出了"));
            }
        }
    }

    CListView::OnTimer(nIDEvent);
}
