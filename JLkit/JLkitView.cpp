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
#include "BugRepDlg.h"
#include "CVPNFile.h"


#include "..\common\ShareMem.h"
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
    ON_COMMAND(ID_LOOKSHAREMEM, OnLookShareMem)
    ON_WM_CREATE()
    ON_COMMAND(ID_START, OnStart)
    ON_NOTIFY_REFLECT(NM_RCLICK, OnRclick)
    ON_COMMAND(ID_PROFILE, OnProfile)
    ON_COMMAND(ID_GETANDACTIVE, OnGetAndActive)
    ON_UPDATE_COMMAND_UI(ID_PROFILE, OnUpdateProfile)
    ON_UPDATE_COMMAND_UI(ID_SELECTALL, OnUpdateSelectall)
    ON_COMMAND(ID_REPORTBUG, OnReportbug)
    ON_WM_TIMER()
    ON_UPDATE_COMMAND_UI(ID_GET, OnUpdateStart)
    ON_WM_RBUTTONUP()
    ON_COMMAND(ID_GET, OnGet)
    ON_COMMAND(ID_ACTIVE, OnActive)
    ON_UPDATE_COMMAND_UI(ID_ACTIVE, OnUpdateStart)
    ON_UPDATE_COMMAND_UI(ID_START, OnUpdateStart)
    ON_UPDATE_COMMAND_UI(ID_GETANDACTIVE, OnUpdateStart)
    ON_COMMAND(ID_SOCKINFO, OnSockinfo)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()


CJLkitView::CJLkitView()
{
    m_lpLaunchThread = NULL;
    m_dwDefaultStyle |= LVS_REPORT;
    m_LineNums = 0;
}

CJLkitView::~CJLkitView()
{

}

CJLkitDoc*  CJLkitView::GetDocument()
{
    return (CJLkitDoc*)m_pDocument;
}


BOOL CJLkitView::PreCreateWindow(CREATESTRUCT& cs)
{
    return CListView::PreCreateWindow(cs);
}



int CJLkitView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    if(CListView::OnCreate(lpCreateStruct) == -1) {
        return -1;
    }

    CString strHeading;

    for(int i = 0; i < COLUMN_TEXT_NUMS; i++) {
        strHeading.LoadString(IDS_STRING128 + i);
        GetListCtrl().InsertColumn(i, (LPCTSTR)strHeading, LVCFMT_LEFT);
        GetListCtrl().SetColumnWidth(i, LVSCW_AUTOSIZE_USEHEADER);
    }

    GetListCtrl().SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_CHECKBOXES);
    //CHeaderCtrl* pHeadctrl = GetListCtrl().GetHeaderCtrl();
    //pHeadctrl->ModifyStyle(0, HDS_CHECKBOXES);
    return 0;
}



void CJLkitView::OnProfile()
{
    CJLkitDoc* pDoc = GetDocument();
    POSITION rpos = GetListCtrl().GetFirstSelectedItemPosition();

    if(rpos != NULL) {
        int nItem = GetListCtrl().GetNextSelectedItem(rpos);
        CString strName = GetListCtrl().GetItemText(nItem, COLUMN_TEXT_ACCOUNT);
        CString strPw = GetListCtrl().GetItemText(nItem, COLUMN_TEXT_PASSWORD);
        CString strConfig = GetListCtrl().GetItemText(nItem, COLUMN_TEXT_CONFIG);
        CString strScript = GetListCtrl().GetItemText(nItem, COLUMN_TEXT_SCRIPT);
        pDoc->LaunchGame(strName, strPw, strConfig, strScript, 1);
    }
}


void CJLkitView::SetResult(int nReslt, int i)
{
    switch(nReslt) {
        case  RESULT_SUCCESS: {
            GetListCtrl().SetItemText(i, COLUMN_TEXT_STATUS, _T("完成"));
            GetListCtrl().SetCheck(i);
            break;
        }
        case  RESULT_FAIL_CAPTCHA: {
            GetListCtrl().SetItemText(i, COLUMN_TEXT_STATUS, _T("需要验证码"));
            break;
        }
        case  RESULT_FAIL_IPBLOCK: {
            GetListCtrl().SetItemText(i, COLUMN_TEXT_STATUS, _T("此IP被封锁, 使用代理重试"));
            break;
        }
        case  RESULT_FAIL_EXCEPTION: {
            GetListCtrl().SetItemText(i, COLUMN_TEXT_STATUS, _T("异常, 请重试一次"));
            break;
        }
        case  RESULT_FAIL_GETUKEY: {
            GetListCtrl().SetItemText(i, COLUMN_TEXT_STATUS, _T("无法获取UKEY"));
            break;
        }
        case  RESULT_NOKEY: {
            GetListCtrl().SetItemText(i, COLUMN_TEXT_STATUS, _T("没有有效KEY"));
            break;
        }
        case  RESULT_ALREADY_RUNNING: {
            GetListCtrl().SetItemText(i, COLUMN_TEXT_STATUS, _T("已经在运行.."));
            break;
        }
        case  RESULT_GET_ALEADY: {
            GetListCtrl().SetItemText(i, COLUMN_TEXT_STATUS, _T("已经领取过"));
            break;
        }
        case  RESULT_GET_ERROR: {
            GetListCtrl().SetItemText(i, COLUMN_TEXT_STATUS, _T("领取失败"));
            break;
        }
        case  RESULT_FAIL_TIMEOUT: {
            GetListCtrl().SetItemText(i, COLUMN_TEXT_STATUS, _T("超时"));
            break;
        }
        case  RESULT_FAIL_NOACTIVEITEMS: {
            GetListCtrl().SetItemText(i, COLUMN_TEXT_STATUS, _T("无需激活"));
            break;
        }
        case  RESULT_FAIL_PWERROR: {
            GetListCtrl().SetItemText(i, COLUMN_TEXT_STATUS, _T("密码错误"));
            break;
        }
        case  RESULT_FAIL_CREATEGAMEPROCESS: {
            GetListCtrl().SetItemText(i, COLUMN_TEXT_STATUS, _T("创建进程错误"));
            break;
        }
        case  RESULT_FAIL_AUTH: {
            GetListCtrl().SetItemText(i, COLUMN_TEXT_STATUS, _T("验证失败, 请重试一次"));
            break;
        }
        case RESULT_LOGIN_SUCCESS: {
            GetListCtrl().SetItemText(i, COLUMN_TEXT_STATUS, _T("完成登陆"));
            break;
        }
    }
}


void CJLkitView::OnStart()
{
    m_lpLaunchThread->AddWork(CLaunchThread::LAUNCHGAME);
}


void CJLkitView::LaunchGame()
{

    CJLkitDoc* pDoc = GetDocument();
    CListCtrl& list = GetListCtrl();

    //当前选中的条目
    for(int i = 0; i < list.GetItemCount(); i++) {
        if(list.GetCheck(i)) {
            CString strName = list.GetItemText(i, COLUMN_TEXT_ACCOUNT);
            CString strPw = list.GetItemText(i, COLUMN_TEXT_PASSWORD);
            CString strConfig = list.GetItemText(i, COLUMN_TEXT_CONFIG);
            CString strScript = list.GetItemText(i, COLUMN_TEXT_SCRIPT);
            list.SetItemText(i, COLUMN_TEXT_STATUS, _T("开始运行.."));
            int nReslt = pDoc->LaunchGame(strName, strPw, strConfig, strScript);
            SetResult(nReslt, i);
        }
    }

}


void CJLkitView::OnUpdateStart(CCmdUI* pCmdUI)
{
    // TODO: Add your command update UI handler code here
    pCmdUI->Enable(FALSE);
    int count = GetListCtrl().GetItemCount();

    for(int i = 0; i < count; i++) {
        if(GetListCtrl().GetCheck(i)) {
            pCmdUI->Enable();
            break;
        }
    }


    if(m_lpLaunchThread) {
        if(m_lpLaunchThread->isWorking()) {
            pCmdUI->Enable(FALSE);
        }
    }
}


void CJLkitView::OnGet()
{

    int count = GetListCtrl().GetItemCount();
    CJLkitDoc* pDoc = GetDocument();

    for(int i = 0; i < count; i++) {
        if(GetListCtrl().GetCheck(i)) {
            CString strName = GetListCtrl().GetItemText(i, COLUMN_TEXT_ACCOUNT);
            CString strPw = GetListCtrl().GetItemText(i, COLUMN_TEXT_PASSWORD);
            int nRet = pDoc->Get(strName, strPw);
            SetResult(nRet, i);
        }
    }
}

void CJLkitView::OnActive()
{
    int count = GetListCtrl().GetItemCount();
    CJLkitDoc* pDoc = GetDocument();

    for(int i = 0; i < count; i++) {
        if(GetListCtrl().GetCheck(i)) {
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
    m_lpLaunchThread = (CLaunchThread*)AfxBeginThread(RUNTIME_CLASS(CLaunchThread), THREAD_PRIORITY_NORMAL,
                       0, CREATE_SUSPENDED);

    m_lpLaunchThread->SetOwner(this);
    m_lpLaunchThread->ResumeThread();


    //创建一个定时器
    SetTimer(IDT_HEART, 5000, NULL);
    SetTimer(IDT_TIMERGAMEEXIT, 2000, NULL);
    SetTimer(IDT_TIMERPOSTKEYQUERY, 30000, NULL);
}

void CJLkitView::GetAndActive()
{
    //准备
    GetDocument()->GetandActive();

    //开始
    for(int i = 0; i < GetListCtrl().GetItemCount(); i++) {
        CString strName = GetListCtrl().GetItemText(i, COLUMN_TEXT_ACCOUNT);
        CString strPw = GetListCtrl().GetItemText(i, COLUMN_TEXT_PASSWORD);

        CString strLine = strName + _T(", ") + strPw + _T("\n");
        Webpost poster(strName, strPw);

        int LoginTimes = 0;
        BOOL bError = FALSE;

_Again:
        GetListCtrl().SetItemText(i, COLUMN_TEXT_STATUS, _T("正在登录"));
        int nResult = poster.Login();
        SetResult(nResult, i);
        if(nResult != RESULT_SUCCESS) {

            if(nResult == RESULT_FAIL_CAPTCHA ||
                    nResult == RESULT_FAIL_IPBLOCK) {
                //这两种情况直接换ip
                GetDocument()->m_lpVpnFile->AlwaysConnect();
                LoginTimes = 0;
            }
            else if(nResult == RESULT_FAIL_PWERROR) {
                //这种情况直接退
                strLine.Remove(_T('\n'));
                strLine += _T(" : 密码错误");
                strLine += _T("\n");

                bError = TRUE;
                goto _WriteError;
            }
            else {
                //剩余情况等两次
                TRACE1("失败%d次", LoginTimes++);
                if(LoginTimes == 2) {
                    GetDocument()->m_lpVpnFile->AlwaysConnect();
                    LoginTimes = 0;
                }
            }

            goto _Again;
        }

        GetListCtrl().SetItemText(i, COLUMN_TEXT_STATUS, _T("正在领取"));
        nResult = poster.Get();
        SetResult(nResult, i);
        //if(nResult != RESULT_SUCCESS)
        //{
        //    bError = TRUE;
        //}

        GetListCtrl().SetItemText(i, COLUMN_TEXT_STATUS, _T("正在激活"));
        nResult = poster.Active();
        SetResult(nResult, i);
        if(nResult != RESULT_SUCCESS) {
            bError = TRUE;
        }


_WriteError:
        if(bError) {
            GetDocument()->errfile.WriteString(strLine);
        }
    }
    GetDocument()->errfile.Close();
    GetDocument()->m_lpVpnFile->Close();
}



void CJLkitView::OnGetAndActive()
{
    m_lpLaunchThread->AddWork(CLaunchThread::GETANDACTIVE);
}


void CJLkitView::InsertLine(int index, CString& strName,
                            CString& strPw, CString& strConfig,
                            CString& strScript)
{
    GetListCtrl().InsertItem(index, _T(""));
    GetListCtrl().SetItemText(index, COLUMN_TEXT_ACCOUNT, strName);
    GetListCtrl().SetItemText(index, COLUMN_TEXT_PASSWORD, strPw);
    GetListCtrl().SetItemText(index, COLUMN_TEXT_SCRIPT, strScript);
    GetListCtrl().SetItemText(index, COLUMN_TEXT_CONFIG, strConfig);
}


BOOL CJLkitView::ReadLine(CFile* pFile, TCHAR szLine[], BOOL bUnicode)
{
    BOOL bRet = FALSE;
    if(bUnicode) {

        //准备内存
        wchar_t* pLiner = new wchar_t[BUFSIZ];
        ZeroMemory(pLiner, BUFSIZ * sizeof(wchar_t));

        TRY {
            //开始读取文本
            wchar_t bChar = 0;
            int i = 0;
            for(;;)
            {

                if(pFile->Read(&bChar, sizeof(bChar)) == 0)
                    CFileException::ThrowOsError(CFileException::endOfFile);

                if(bChar == 0x0d || bChar == 0x0a) {
                    if(bChar == '\r')
                        pFile->Read(&bChar, sizeof(bChar));

                    break;
                }

                //过滤一些字符
                //if(bChar == ' ') continue;
                if(bChar == 0xfeff) continue;

                memcpy(&pLiner[i++], &bChar, sizeof(bChar));
            }

            pLiner[i] = '\0';

            //根据工程转换
            #ifdef _UNICODE
            wcscpy(szLine, pLiner);
            #else
            //UNICODE -> MBCS
            wcstombs(szLine, pLiner, sizeof(BUFSIZ)*sizeof(wchar_t));
            #endif


            bRet = TRUE;
        }
        CATCH(CFileException, pEx) {
            pEx->Delete();

        }
        END_CATCH


        delete pLiner;

    }
    else {
        //准备内存
        char* pLiner = new char[BUFSIZ];
        ZeroMemory(pLiner, BUFSIZ);

        try {
            //开始读取文本
            char bChar = 0;
            int i = 0;
            for(;;) {

                if(pFile->Read(&bChar, sizeof(bChar)) == 0)
                    CFileException::ThrowOsError(CFileException::endOfFile);

                if(bChar == 0x0d || bChar == 0x0a) {
                    if(bChar == '\r')
                        pFile->Read(&bChar, sizeof(bChar));

                    break;
                }

                //
                //if(bChar == ' ') continue;

                memcpy(&pLiner[i++], &bChar, sizeof(bChar));
            }

            pLiner[i] = '\0';

            //转换字符串
            #ifdef _UNICODE
            //MBCS -> UNICODE
            mbstowcs(szLine, pLiner, strlen(pLiner));
            #else
            strcpy(szLine, pLiner);
            #endif


            bRet = TRUE;
        }
        catch(CFileException* pEx) {
            pEx->Delete();

        }

        delete pLiner;
    }

    return bRet;
}


//串行
void CJLkitView::SerializeText(CArchive& ar)
{
    if(ar.IsStoring()) {

    }
    else {

        //获取对象指针
        CFile* pFile = ar.GetFile();

        //读取一部分判断编码
        TCHAR szIsUnicode[BUFSIZ];
        pFile->Read(szIsUnicode, sizeof(szIsUnicode));
        pFile->SeekToBegin();

        //判断编码
        TCHAR szLine[BUFSIZ] = {0};

        INT nTestMode = IS_TEXT_UNICODE_STATISTICS;
        BOOL bIsUnicode = ::IsTextUnicode(szIsUnicode, sizeof(szIsUnicode), &nTestMode);


        //插入行
        while(ReadLine(pFile, szLine, bIsUnicode)) {

            CString strName;
            CString strPw;
            Webpost::GetPwName(CString(szLine), strName, strPw);

            InsertLine(m_LineNums++, strName, strPw, CString(_T("Default")), CString(_T("Default")));

            ZeroMemory(szLine, BUFSIZ * sizeof(TCHAR));
        }

        //设置列宽
        for(int i = 0; i < COLUMN_TEXT_NUMS; i++) {
            GetListCtrl().SetColumnWidth(i, LVSCW_AUTOSIZE_USEHEADER);
        }

        JLShareMem::Instance()->Close();
        JLShareMem::Instance()->Create(m_LineNums, SHAREOBJNAME);
    }
}

void CJLkitView::OnUpdateProfile(CCmdUI* pCmdUI)
{
    // TODO: Add your command update UI handler code here
    pCmdUI->Enable(FALSE);
    int count = GetListCtrl().GetItemCount();

    for(int i = 0; i < count; i++) {
        if(GetListCtrl().GetCheck(i)) {
            pCmdUI->Enable();
            break;
        }
    }

    if(GetListCtrl().GetSelectedCount() != 0) {
        pCmdUI->Enable();
    }
}

void CJLkitView::OnUpdateSelectall(CCmdUI* pCmdUI)
{
}

void CJLkitView::OnReportbug()
{
    CJLkitDoc* pDoc = GetDocument();
    CDlgBugRep dlg(pDoc);
    dlg.DoModal();
}


void CJLkitView::OnLookShareMem()
{

    SHAREINFO* pShareInfo = JLShareMem::Instance()->GetMem();
    if(pShareInfo != NULL) {
        for(unsigned i = 0; i < JLShareMem::Instance()->GetAllCount(); i++, pShareInfo++) {
            TCHAR szTemp[BUFSIZ] = {0};
            wsprintf(szTemp, _T("帐号:%s PID:%d 配置:%s 脚本:%s\n"),
                     pShareInfo->szName,
                     pShareInfo->pid,
                     pShareInfo->szConfig,
                     pShareInfo->szSript);

            TRACE(szTemp);
        }
    }
}


void CJLkitView::OnTimer(UINT nIDEvent)
{
    if(nIDEvent == IDT_TIMERGAMEEXIT) {
        //共享内存
        JLShareMem* pShareMem = JLShareMem::Instance();

        //每次遍历所有item, 判断item的pid存不存在, 不存在就是游戏退出了
        for(int i = 0; i < GetListCtrl().GetItemCount(); i++) {
            CString strName = GetListCtrl().GetItemText(i, COLUMN_TEXT_ACCOUNT);

            if(pShareMem->Get((LPCTSTR)strName)) {
                if(pShareMem->IsPidValid((LPCTSTR)strName) == FALSE) {
                    pShareMem->Del((LPCTSTR)strName);
                    GetListCtrl().SetItemText(i, COLUMN_TEXT_STATUS, _T("进程退出了"));
                }
            }

        }
    }

    //CListView::OnTimer(nIDEvent);
}

void CJLkitView::OnUpdateGetandactive(CCmdUI* pCmdUI)
{
    if(m_lpLaunchThread) {
        if(m_lpLaunchThread->isWorking()) {
            pCmdUI->Enable(FALSE);
        }
    }
}

void CJLkitView::PostNcDestroy()
{
    TRACE(_T("PostNcDestroy Called"));
    CListView::PostNcDestroy();
}

void CJLkitView::OnSockinfo()
{

}
