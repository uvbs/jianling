// JLkitView.cpp: implementation of the CJLkitView class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "JLkit.h"
#include "MainFrm.h"
#include "JLkitView.h"
#include "JLkitDoc.h"
#include "JLkitSocket.h"
#include "BugRepDlg.h"
#include "CVpnFile.h"
#include "ConfigMgr.h"


#include <boost/regex.hpp>
typedef boost::basic_regex<TCHAR> tregex;
typedef boost::match_results<TCHAR const*> tmatch;



#ifdef _DEBUG
    #define new DEBUG_NEW
#endif



//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

IMPLEMENT_DYNCREATE(CJLkitView, CListView)


BEGIN_MESSAGE_MAP(CJLkitView, CListView)
    //{{AFX_MSG_MAP(CJLkitView)
    ON_NOTIFY_REFLECT(NM_CUSTOMDRAW, OnNMCustomdraw)
    ON_WM_CREATE()
    ON_COMMAND(ID_START, OnStart)
    ON_NOTIFY_REFLECT(NM_RCLICK, OnRclick)
    ON_COMMAND(ID_PROFILE, OnProfile)
    ON_UPDATE_COMMAND_UI(ID_PROFILE, OnUpdateProfile)
    ON_UPDATE_COMMAND_UI(ID_SELECTALL, OnUpdateSelectall)
    ON_COMMAND(ID_REPORTBUG, OnReportbug)
    ON_WM_TIMER()
    ON_UPDATE_COMMAND_UI(ID_GET, OnUpdateStart)
    ON_COMMAND(ID_UC_START, OnUcStart)
    ON_WM_RBUTTONUP()
    ON_COMMAND(ID_GET, OnGet)
    ON_COMMAND(ID_ACTIVE, OnActive)
    ON_UPDATE_COMMAND_UI(ID_ACTIVE, OnUpdateStart)
    ON_UPDATE_COMMAND_UI(ID_START, OnUpdateStart)
    ON_UPDATE_COMMAND_UI(ID_GETANDACTIVE, OnUpdateStart)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()


CJLkitView::CJLkitView()
{
    m_dwDefaultStyle |= LVS_REPORT;
    m_LineNums = 0;
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
    if(CListView::OnCreate(lpCreateStruct) == -1) return -1;

    CString strHeading;
    for(int i = 0; i < COLUMN_TEXT_NUMS; i++)
    {
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
    CJLkitDoc* pDoc = (CJLkitDoc*)GetDocument();
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


void CJLkitView::SetResult(int nReslt, int i)
{
    switch(nReslt)
    {
        case  RESULT_SUCCESS:
        {
            GetListCtrl().SetItemText(i, COLUMN_TEXT_STATUS, _T("完成"));
            GetListCtrl().SetCheck(i);
            SetItemColor(i, RGB(255, 255, 255));
            break;
        }
        case  RESULT_FAIL_CAPTCHA:
        {
            GetListCtrl().SetItemText(i, COLUMN_TEXT_STATUS, _T("需要验证码"));
            break;
        }
        case  RESULT_FAIL_IPBLOCK:
        {
            GetListCtrl().SetItemText(i, COLUMN_TEXT_STATUS, _T("此IP被封锁, 使用代理重试"));
            SetItemColor(i, RGB(255, 0, 0));
            break;
        }
        case  RESULT_FAIL_EXCEPTION:
        {
            GetListCtrl().SetItemText(i, COLUMN_TEXT_STATUS, _T("异常, 请重试一次"));
            break;
        }
        case  RESULT_FAIL_GETUKEY:
        {
            GetListCtrl().SetItemText(i, COLUMN_TEXT_STATUS, _T("无法获取UKEY"));
            break;
        }
        case  RESULT_NOKEY:
        {
            GetListCtrl().SetItemText(i, COLUMN_TEXT_STATUS, _T("没有有效KEY"));
            break;
        }
        case  RESULT_ALREADY_RUNNING:
        {
            GetListCtrl().SetItemText(i, COLUMN_TEXT_STATUS, _T("已经在运行.."));
            break;
        }
        case  RESULT_GET_ALEADY:
        {
            GetListCtrl().SetItemText(i, COLUMN_TEXT_STATUS, _T("已经领取过"));
            break;
        }
        case  RESULT_GET_ERROR:
        {
            GetListCtrl().SetItemText(i, COLUMN_TEXT_STATUS, _T("领取失败"));
            break;
        }
        case  RESULT_FAIL_TIMEOUT:
        {
            GetListCtrl().SetItemText(i, COLUMN_TEXT_STATUS, _T("超时"));
            break;
        }
        case  RESULT_FAIL_NOACTIVEITEMS:
        {
            GetListCtrl().SetItemText(i, COLUMN_TEXT_STATUS, _T("无需激活"));
            break;
        }
        case  RESULT_FAIL_PWERROR:
        {
            GetListCtrl().SetItemText(i, COLUMN_TEXT_STATUS, _T("密码错误"));
            SetItemColor(i, RGB(255, 0, 0));
            break;
        }
        case  RESULT_FAIL_CREATEGAMEPROCESS:
        {
            GetListCtrl().SetItemText(i, COLUMN_TEXT_STATUS, _T("创建进程错误"));
            break;
        }
        case  RESULT_FAIL_AUTH:
        {
            GetListCtrl().SetItemText(i, COLUMN_TEXT_STATUS, _T("验证失败, 请重试一次"));
            SetItemColor(i, RGB(255, 0, 0));
            break;
        }
        case RESULT_LOGIN_SUCCESS:
        {
            GetListCtrl().SetItemText(i, COLUMN_TEXT_STATUS, _T("完成运行"));
            break;
        }
    }
}


void CJLkitView::OnStart()
{
    LaunchGame();
}


void CJLkitView::LaunchGame()
{

    CJLkitDoc* pDoc = (CJLkitDoc*)GetDocument();
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

}


void CJLkitView::OnUpdateStart(CCmdUI* pCmdUI)
{
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
}


void CJLkitView::OnGet()
{

    int count = GetListCtrl().GetItemCount();
    CJLkitDoc* pDoc = (CJLkitDoc*)GetDocument();

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
    int count = GetListCtrl().GetItemCount();
    CJLkitDoc* pDoc = (CJLkitDoc*)GetDocument();

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


void CJLkitView::SetItemColor(DWORD iItem, COLORREF color)
{
    MapItemColor.SetAt(iItem, color);//设置某行的颜色。
    GetListCtrl().RedrawItems(iItem, iItem);//重新染色
    UpdateWindow();
}


void CJLkitView::OnRclick(NMHDR* pNMHDR, LRESULT* pResult)
{
    switch(pNMHDR->code)
    {
        case NM_RCLICK:
        {
            POINT point;
            GetCursorPos(&point);
            CMenu menu;

            if(GetListCtrl().GetSelectedCount() == 0)
            {
                menu.LoadMenu(IDR_MAINFRAME);
                menu.GetSubMenu(1)->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, (CMainFrame*)AfxGetMainWnd());

            }
            else
            {
                menu.LoadMenu(IDR_KEY);
                menu.GetSubMenu(1)->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, (CMainFrame*)AfxGetMainWnd());

            }

        }
        break;

    }
    *pResult = 0;
}

void CJLkitView::OnInitialUpdate()
{
    //自动加载账号文档
    CConfigMgr* lpConfig = CConfigMgr::GetInstance();
    if(lpConfig->m_szFileName[0] != 0)
    {
        GetDocument()->OnOpenDocument(lpConfig->m_szFileName);
    }

    CListView::OnInitialUpdate();
}


void CJLkitView::InsertLine(int index, const TCHAR szName[], const TCHAR szPw[], const TCHAR szConfig[], const TCHAR szScript[])
{
    GetListCtrl().InsertItem(index, _T(""));
    GetListCtrl().SetItemText(index, COLUMN_TEXT_ACCOUNT, szName);
    GetListCtrl().SetItemText(index, COLUMN_TEXT_PASSWORD, szPw);
    GetListCtrl().SetItemText(index, COLUMN_TEXT_SCRIPT, szScript);
    GetListCtrl().SetItemText(index, COLUMN_TEXT_CONFIG, szConfig);
}

void CJLkitView::Trim(std::basic_string<TCHAR>* str)
{

    _ASSERTE(NULL != str);
    if(str->empty()) return;

    // Trim begin chars.
    std::basic_string<TCHAR>::iterator it = str->begin();
    while(it != str->end())
    {
        if(*it == 0xfeff) it++;
        if(!_istspace(*it)) break;
        ++it;
    }

    str->erase(str->begin(), it);

    // Trim end chars;
    std::basic_string<TCHAR>::iterator it2 = str->end();
    if(it2 == it)
    {
        str->erase();
        return;
    }

    while(it2 != it)
    {
        if(*it2 == 0) it2--;

        if(!_istspace(*it2)) break;
        it2--;
    }

    str->erase(++it2, str->end());
}

//串行
void CJLkitView::SerializeText(CArchive& ar)
{
    if(ar.IsStoring())
    {

    }
    else
    {

        //准备对象
        CConfigMgr* pConfig = CConfigMgr::GetInstance();

        //获取框架
        CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
        CComboBox& cbScript = pFrame->m_cbScript;
        CComboBox& cbConfig = pFrame->m_cbConfig;

        //获取对象指针
        CFile* pFile = ar.GetFile();

        //文件大小
        DWORD dwFileSize = pFile->GetLength();
        if(dwFileSize < 3) return;

        char* pCastBuf = new char[dwFileSize + 2];
        ZeroMemory(pCastBuf, dwFileSize + 2);

        //完整读取
        pFile->Read(pCastBuf, dwFileSize);

        //探测编码
        INT nTestMode = IS_TEXT_UNICODE_UNICODE_MASK;
        BOOL bIsUnicode = ::IsTextUnicode(pCastBuf, dwFileSize, &nTestMode);


        TCHAR* pTbuf = NULL;
        //根据编码转换为TCHAR
        if(bIsUnicode)
        {
#ifndef _UNICODE

            pTbuf = new char[dwFileSize / sizeof(TCHAR)];
            ZeroMemory(pTbuf, dwFileSize);

            //转换成ANSI
            AtlW2AHelper(pTbuf, (LPWSTR)pCastBuf, dwFileSize, CP_ACP);
#else
            pTbuf = (TCHAR*)pCastBuf;
#endif
        }
        else
        {
#ifdef _UNICODE

            pTbuf = new wchar_t[dwFileSize + 1];
            ZeroMemory(pTbuf, (dwFileSize + 1)*sizeof(wchar_t));

            //转换成UNICODE
            mbstowcs((LPWSTR)pTbuf, (LPSTR)pCastBuf, strlen(pCastBuf));
#else
            pTbuf = (TCHAR*)pCastBuf;
#endif
        }

        //字符串流
        std::basic_stringstream<wchar_t> fmt(pTbuf);
        std::basic_string<TCHAR> strLine;


        //清空列表框
        GetListCtrl().DeleteAllItems();

        CString strConfig;
        CString strScript;

        //插入行
        while(std::getline(fmt, strLine))
        {
            std::basic_string<TCHAR> strName;
            std::basic_string<TCHAR> strPw;

            Trim(&strLine);

            if(strLine.length() <= 0) continue;

            tregex line(_T("([^,;]*)[,; ]*([^,;]*)"));
            tmatch matches;

            if(boost::regex_search(strLine, matches, line))
            {
                strName = matches.str(1);
                strPw = matches.str(2);
            }

            if(cbConfig.GetLBTextLen(cbConfig.GetCurSel()) == -1)
            {
                strConfig = _T("");
            }
            else
            {
                cbConfig.GetLBText(cbConfig.GetCurSel(), strConfig);
            }

            if(cbScript.GetLBTextLen(cbScript.GetCurSel()) == -1)
            {
                strScript = _T("");
            }
            else
            {

                cbScript.GetLBText(cbScript.GetCurSel(), strScript);
            }

            InsertLine(m_LineNums++, strName.c_str(), strPw.c_str(), (LPCTSTR)strConfig, (LPCTSTR)strScript);
        }


        //设置列宽
        for(int i = 0; i < COLUMN_TEXT_NUMS; i++)
        {
            GetListCtrl().SetColumnWidth(i, LVSCW_AUTOSIZE_USEHEADER);
        }

        if(pTbuf == (TCHAR*)pCastBuf)
        {
            SafeDelete(pTbuf);
        }
        else
        {
            SafeDelete(pTbuf);
            SafeDelete(pCastBuf);
        }

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
    {
        pCmdUI->Enable();
    }
}

void CJLkitView::OnUpdateSelectall(CCmdUI* pCmdUI)
{
}

void CJLkitView::OnReportbug()
{
    CDlgBugRep dlg;
    dlg.DoModal();
}

void CJLkitView::OnTimer(UINT nIDEvent)
{
    if(nIDEvent == ID_TESTSOCKET)
    {

    }
}

void CJLkitView::OnUpdateGetandactive(CCmdUI* pCmdUI)
{
}

void CJLkitView::PostNcDestroy()
{
    CListView::PostNcDestroy();
}

void CJLkitView::OnUcStart()
{
    CJLkitDoc* pDoc = (CJLkitDoc *)GetDocument();
    CListCtrl& list = GetListCtrl();

    //当前选中的条目
    POSITION pos = list.GetFirstSelectedItemPosition();

    while(pos)
    {
        int i = list.GetNextSelectedItem(pos);
        CString strName = list.GetItemText(i, COLUMN_TEXT_ACCOUNT);
        CString strPw = list.GetItemText(i, COLUMN_TEXT_PASSWORD);
        CString strConfig = list.GetItemText(i, COLUMN_TEXT_CONFIG);
        CString strScript = list.GetItemText(i, COLUMN_TEXT_SCRIPT);
        list.SetItemText(i, COLUMN_TEXT_STATUS, _T("开始运行.."));
        int nReslt = pDoc->LaunchGame(strName, strPw, strConfig, strScript);
        SetResult(nReslt, i);
    }

}

void CJLkitView::OnNMCustomdraw(NMHDR* pNMHDR, LRESULT* pResult)
{
    *pResult = CDRF_DODEFAULT;
    NMLVCUSTOMDRAW* lplvdr = (NMLVCUSTOMDRAW*)pNMHDR;
    NMCUSTOMDRAW& nmcd = lplvdr->nmcd;
    switch(lplvdr->nmcd.dwDrawStage)   //判断状态
    {
        case CDDS_PREPAINT:
        {
            *pResult = CDRF_NOTIFYITEMDRAW;
            break;
        }
        case CDDS_ITEMPREPAINT:   //如果为画ITEM之前就要进行颜色的改变
        {
            COLORREF ItemColor;
            if(MapItemColor.Lookup(nmcd.dwItemSpec, ItemColor))
                // 根据在 SetItemColor(DWORD iItem, COLORREF color) 设置的
                // ITEM号和COLORREF 在摸板中查找，然后进行颜色赋值。
            {
                //lplvdr->clrText = RGB(0,0,0);//ItemColor;
                lplvdr->clrTextBk = ItemColor;
                *pResult = CDRF_DODEFAULT;
            }
        }
        break;
    }
}
