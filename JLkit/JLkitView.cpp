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

#ifdef _UNICODE
    typedef boost::wregex tregex;
    typedef boost::wsmatch tmatch;
#else
    typedef boost::regex tregex;
    typedef boost::smatch tmatch;
#endif

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
            GetListCtrl().SetItemText(i, COLUMN_TEXT_STATUS, _T("���"));
            GetListCtrl().SetCheck(i);
            SetItemColor(i, RGB(255, 255, 255));
            break;
        }
        case  RESULT_FAIL_CAPTCHA:
        {
            GetListCtrl().SetItemText(i, COLUMN_TEXT_STATUS, _T("��Ҫ��֤��"));
            break;
        }
        case  RESULT_FAIL_IPBLOCK:
        {
            GetListCtrl().SetItemText(i, COLUMN_TEXT_STATUS, _T("��IP������, ʹ�ô�������"));
            SetItemColor(i, RGB(255, 0, 0));
            break;
        }
        case  RESULT_FAIL_EXCEPTION:
        {
            GetListCtrl().SetItemText(i, COLUMN_TEXT_STATUS, _T("�쳣, ������һ��"));
            break;
        }
        case  RESULT_FAIL_GETUKEY:
        {
            GetListCtrl().SetItemText(i, COLUMN_TEXT_STATUS, _T("�޷���ȡUKEY"));
            break;
        }
        case  RESULT_NOKEY:
        {
            GetListCtrl().SetItemText(i, COLUMN_TEXT_STATUS, _T("û����ЧKEY"));
            break;
        }
        case  RESULT_ALREADY_RUNNING:
        {
            GetListCtrl().SetItemText(i, COLUMN_TEXT_STATUS, _T("�Ѿ�������.."));
            break;
        }
        case  RESULT_GET_ALEADY:
        {
            GetListCtrl().SetItemText(i, COLUMN_TEXT_STATUS, _T("�Ѿ���ȡ��"));
            break;
        }
        case  RESULT_GET_ERROR:
        {
            GetListCtrl().SetItemText(i, COLUMN_TEXT_STATUS, _T("��ȡʧ��"));
            break;
        }
        case  RESULT_FAIL_TIMEOUT:
        {
            GetListCtrl().SetItemText(i, COLUMN_TEXT_STATUS, _T("��ʱ"));
            break;
        }
        case  RESULT_FAIL_NOACTIVEITEMS:
        {
            GetListCtrl().SetItemText(i, COLUMN_TEXT_STATUS, _T("���輤��"));
            break;
        }
        case  RESULT_FAIL_PWERROR:
        {
            GetListCtrl().SetItemText(i, COLUMN_TEXT_STATUS, _T("�������"));
            SetItemColor(i, RGB(255, 0, 0));
            break;
        }
        case  RESULT_FAIL_CREATEGAMEPROCESS:
        {
            GetListCtrl().SetItemText(i, COLUMN_TEXT_STATUS, _T("�������̴���"));
            break;
        }
        case  RESULT_FAIL_AUTH:
        {
            GetListCtrl().SetItemText(i, COLUMN_TEXT_STATUS, _T("��֤ʧ��, ������һ��"));
            SetItemColor(i, RGB(255, 0, 0));
            break;
        }
        case RESULT_LOGIN_SUCCESS:
        {
            GetListCtrl().SetItemText(i, COLUMN_TEXT_STATUS, _T("�������"));
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

    //��ǰѡ�е���Ŀ
    for(int i = 0; i < list.GetItemCount(); i++)
    {
        if(list.GetCheck(i))
        {
            CString strName = list.GetItemText(i, COLUMN_TEXT_ACCOUNT);
            CString strPw = list.GetItemText(i, COLUMN_TEXT_PASSWORD);
            CString strConfig = list.GetItemText(i, COLUMN_TEXT_CONFIG);
            CString strScript = list.GetItemText(i, COLUMN_TEXT_SCRIPT);
            list.SetItemText(i, COLUMN_TEXT_STATUS, _T("��ʼ����.."));
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

            GetListCtrl().SetItemText(i, COLUMN_TEXT_STATUS, _T("���ڵ�¼"));
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
    MapItemColor.SetAt(iItem, color);//����ĳ�е���ɫ��
    GetListCtrl().RedrawItems(iItem, iItem);//����Ⱦɫ
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

    //�Զ������˺��ĵ�
    CConfigMgr* lpConfig = CConfigMgr::GetInstance();
    if(lpConfig->m_szFileName[0] != 0)
    {
        GetDocument()->OnOpenDocument(lpConfig->m_szFileName);
    }

    //�����п�
    for(int i = 0; i < COLUMN_TEXT_NUMS; i++)
    {
        GetListCtrl().SetColumnWidth(i, LVSCW_AUTOSIZE_USEHEADER);
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


bool CJLkitView::ReadLine(std::basic_string<TCHAR>& strLine, CFile* pFile)
{
    char cbChar = 0;
    strLine = _T("");
    try
    {

        for(;;)
        {
            if(pFile->Read(&cbChar, sizeof(cbChar)) == 0)
                return false;


            if(cbChar == 0x0d || cbChar == 0x0a)
            {
                break;
            }

            strLine += cbChar;

        }

        return true;

    }
    catch(CFileException* pEx)
    {
        pEx->Delete();
    }

    return false;
}

//����
void CJLkitView::SerializeText(CArchive& ar)
{
    if(ar.IsStoring())
    {

    }
    else
    {
        //����б��
        GetListCtrl().DeleteAllItems();

        //׼������
        CConfigMgr* pConfig = CConfigMgr::GetInstance();

        //��ȡ���
        CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
        CComboBox& cbScript = pFrame->m_cbScript;
        CComboBox& cbConfig = pFrame->m_cbConfig;

        //��ȡ����ָ��
        CFile* pFile = ar.GetFile();

        std::basic_string<TCHAR> strLine;
        std::basic_string<TCHAR> strName;
        std::basic_string<TCHAR> strPw;
        std::basic_string<TCHAR> strConfig;
        std::basic_string<TCHAR> strScript;

        while(ReadLine(strLine, pFile))
        {
            tregex line(_T("([^,; ]+)[,; ]+([^,; ]+)"));
            tmatch matches;

            if(boost::regex_search(strLine, matches, line))
            {
                strName = matches.str(1);
                strPw = matches.str(2);

                InsertLine(m_LineNums++, strName.c_str(), strPw.c_str(), strConfig.c_str(), strScript.c_str());
            }

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
    CJLkitDoc* pDoc = (CJLkitDoc*)GetDocument();
    CListCtrl& list = GetListCtrl();

    //��ǰѡ�е���Ŀ
    POSITION pos = list.GetFirstSelectedItemPosition();

    while(pos)
    {
        int i = list.GetNextSelectedItem(pos);
        CString strName = list.GetItemText(i, COLUMN_TEXT_ACCOUNT);
        CString strPw = list.GetItemText(i, COLUMN_TEXT_PASSWORD);
        CString strConfig = list.GetItemText(i, COLUMN_TEXT_CONFIG);
        CString strScript = list.GetItemText(i, COLUMN_TEXT_SCRIPT);
        list.SetItemText(i, COLUMN_TEXT_STATUS, _T("��ʼ����.."));
        int nReslt = pDoc->LaunchGame(strName, strPw, strConfig, strScript);
        SetResult(nReslt, i);
    }

}

void CJLkitView::OnNMCustomdraw(NMHDR* pNMHDR, LRESULT* pResult)
{
    *pResult = CDRF_DODEFAULT;
    NMLVCUSTOMDRAW* lplvdr = (NMLVCUSTOMDRAW*)pNMHDR;
    NMCUSTOMDRAW& nmcd = lplvdr->nmcd;
    switch(lplvdr->nmcd.dwDrawStage)   //�ж�״̬
    {
        case CDDS_PREPAINT:
        {
            *pResult = CDRF_NOTIFYITEMDRAW;
            break;
        }
        case CDDS_ITEMPREPAINT:   //���Ϊ��ITEM֮ǰ��Ҫ������ɫ�ĸı�
        {
            COLORREF ItemColor;
            if(MapItemColor.Lookup(nmcd.dwItemSpec, ItemColor))
                // ������ SetItemColor(DWORD iItem, COLORREF color) ���õ�
                // ITEM�ź�COLORREF �������в��ң�Ȼ�������ɫ��ֵ��
            {
                //lplvdr->clrText = RGB(0,0,0);//ItemColor;
                lplvdr->clrTextBk = ItemColor;
                *pResult = CDRF_DODEFAULT;
            }
        }
        break;
    }
}
