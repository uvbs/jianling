// JLkitView.cpp: implementation of the CJLkitView class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "JLkit.h"
#include "MainFrm.h"
#include "JLkitView.h"
#include "JLkitDoc.h"
#include "JLkitSocket.h"
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


enum WORKTHREADMSGID
{
    WM_WORKTHREAD_GET = WM_USER + 555,
    WM_WORKTHREAD_ACTIVE,
    WM_WORKTHREAD_GETANDACTIVE,
    WM_WORKTHREAD_RUN_ALL_GAME,
    WM_WORKTHREAD_RUN_SINGLE_GAME
};



//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

IMPLEMENT_DYNCREATE(CJLkitView, CListView)


BEGIN_MESSAGE_MAP(CJLkitView, CListView)
    //{{AFX_MSG_MAP(CJLkitView)
    ON_NOTIFY_REFLECT(NM_CUSTOMDRAW, OnNMCustomdraw)
    ON_WM_CREATE()
    ON_NOTIFY_REFLECT(NM_RCLICK, OnRclick)
    ON_COMMAND(ID_START, OnStart)
    ON_COMMAND(ID_UC_START, OnUcStart)
    ON_COMMAND(ID_GET, OnGet)
    ON_COMMAND(ID_ACTIVE, OnActive)
    ON_UPDATE_COMMAND_UI(ID_GET, OnUpdateStart)
    ON_COMMAND(ID_GETANDACTIVE, OnGetAndActive)
    ON_UPDATE_COMMAND_UI(ID_UC_START, OnUpdateUcStart)
    ON_COMMAND(ID_UC_LOG, OnUcLog)
    ON_COMMAND(ID_STOPOP, OnStopOp)
    ON_UPDATE_COMMAND_UI(ID_STOPOP, OnUpdateStopOp)
    ON_WM_RBUTTONUP()
    ON_UPDATE_COMMAND_UI(ID_ACTIVE, OnUpdateStart)
    ON_UPDATE_COMMAND_UI(ID_START, OnUpdateStart)
    ON_UPDATE_COMMAND_UI(ID_GETANDACTIVE, OnUpdateStart)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()


CJLkitView::CJLkitView()
{
    m_dwDefaultStyle |= LVS_REPORT;
    m_LineNums = 0;
    m_lpVpnFile = NULL;
}

CJLkitView::~CJLkitView()
{
    //�ͷ��߳�
    if(m_pWorkThread)
    {
        m_bWorking = false;
        m_pWorkThread->PostThreadMessage(WM_QUIT, 0, 0);
        WaitForSingleObject(m_pWorkThread->m_hThread, INFINITE);
    }

    SafeDelete(m_lpVpnFile);
}


BOOL CJLkitView::PreCreateWindow(CREATESTRUCT& cs)
{
    if(!CListView::PreCreateWindow(cs))
        return FALSE;


    return TRUE;
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


void CJLkitView::SetResult(int nReslt, int i)
{
    switch(nReslt)
    {
    case RESULT_FAIL_INJECT:
        {
            GetListCtrl().SetItemText(i, COLUMN_TEXT_STATUS, _T("ע��ʧ��"));
            break;
        }
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
            GetListCtrl().SetItemText(i, COLUMN_TEXT_STATUS, _T("IP������, ʹ�ô�������"));
            SetItemColor(i, RGB(255, 0, 0));
            break;
        }
    case  RESULT_FAIL_EXCEPTION:
        {
            GetListCtrl().SetItemText(i, COLUMN_TEXT_STATUS, _T("�쳣, ����"));
            break;
        }
    case  RESULT_FAIL_GETUKEY:
        {
            GetListCtrl().SetItemText(i, COLUMN_TEXT_STATUS, _T("�޷���ȡUKEY"));
            break;
        }
    case  RESULT_NOKEY:
        {
            GetListCtrl().SetItemText(i, COLUMN_TEXT_STATUS, _T("û����Ч����"));
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
            DWORD dwLastErr = GetLastError();
            TCHAR szBuf[BUFSIZ/2];
            wsprintf(szBuf, _T("�������̳���, %d"), dwLastErr);
            GetListCtrl().SetItemText(i, COLUMN_TEXT_STATUS, szBuf);
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
            GetListCtrl().SetItemText(i, COLUMN_TEXT_STATUS, _T("������.."));
            break;
        }
    }
}


void CJLkitView::OnStart()
{
    m_pWorkThread->PostThreadMessage(WM_WORKTHREAD_RUN_ALL_GAME, 0, 0);
}

void CJLkitView::OnUpdateStart(CCmdUI* pCmdUI)
{


    if(m_bWorking == false)
    {
        int count = GetListCtrl().GetItemCount();
        for(int i = 0; i < count; i++)
        {
            if(GetListCtrl().GetCheck(i))
            {
                pCmdUI->Enable();
                return;
            }
        }

    }

    pCmdUI->Enable(FALSE);
}


void CJLkitView::OnGet()
{
    m_pWorkThread->PostThreadMessage(WM_WORKTHREAD_GET, 0, 0);
}

void CJLkitView::OnActive()
{
    m_pWorkThread->PostThreadMessage(WM_WORKTHREAD_ACTIVE, 0, 0);
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

    //��ʼ�������߳�
    m_pWorkThread = AfxBeginThread(WorkThread, this);
    if(!m_pWorkThread) return;

    //��ʼ��
    if(!m_lpVpnFile)
    {
        m_lpVpnFile = new CVpnFile;
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
            {
                if(strLine.empty())
                {
                    return false;
                }
                else
                {
                    return true;
                }
            }


            if(cbChar == 0x0d || cbChar == 0x0a)
            {
                if(cbChar == 0x0a)
                {
                    break;
                }

                continue;
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

        //��ȡ���
        CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
        CComboBox& cbScript = pFrame->m_cbScript;
        CComboBox& cbConfig = pFrame->m_cbConfig;

        //��ȡ����ָ��
        CFile* pFile = ar.GetFile();

        std::basic_string<TCHAR> strLine;
        std::basic_string<TCHAR> strName;
        std::basic_string<TCHAR> strPw;

        TCHAR szConfig[MAX_PATH];
        TCHAR szScript[MAX_PATH];
        cbScript.GetLBText(cbScript.GetCurSel(), szScript);
        cbConfig.GetLBText(cbConfig.GetCurSel(), szConfig);

        _ASSERTE(szConfig[0] != _T('\0'));
        _ASSERTE(szScript[0] != _T('\0'));


        while(ReadLine(strLine, pFile))
        {
            tregex line(_T("([^,; ]+)[,; ]+([^,; ]+)"));
            tmatch matches;

            if(boost::regex_search(strLine, matches, line))
            {
                strName = matches.str(1);
                strPw = matches.str(2);

                InsertLine(m_LineNums++, strName.c_str(), strPw.c_str(), szConfig, szScript);
            }

        }


        //�����п�
        for(int i = 0; i < COLUMN_TEXT_NUMS; i++)
        {
            GetListCtrl().SetColumnWidth(i, LVSCW_AUTOSIZE_USEHEADER);
        }
    }
}



#define PIPE_TIMEOUT 4000
UINT AFX_CDECL CJLkitView::IPCThread(LPVOID lpParam)
{

    PIPEDATA stPipeData = *(PPIPEDATA)lpParam;

    CMainFrame* pFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd;
    CJLkitView* pView = (CJLkitView*)pFrame->GetActiveView();
    CListCtrl& list = pView->GetListCtrl();

    int inItem = stPipeData.dwItem;
    HANDLE hPipe = INVALID_HANDLE_VALUE;
    DWORD dwBytesRead;
    BOOL bRetCode;
    DWORD dwBytesWrited = 0;

    TCHAR szPipi[MAX_PATH];
    wsprintf(szPipi, _T("\\\\.\\Pipe\\JLwg_%d"), stPipeData.dwPid);

    hPipe = CreateNamedPipe(szPipi, PIPE_ACCESS_DUPLEX, PIPE_TYPE_MESSAGE | PIPE_WAIT, 1, BUFSIZ, BUFSIZ, PIPE_TIMEOUT, NULL);
    if(hPipe == INVALID_HANDLE_VALUE)
    {
        TRACE(_T("�����ܵ�ʧ��"));
        goto fun_exit;
    }

    if(!ConnectNamedPipe(hPipe, NULL))
    {
        if(ERROR_PIPE_CONNECTED != GetLastError())
        {
            goto fun_exit;
        }
    }


    //д��һ������
    if(!WriteFile(hPipe, &stPipeData, sizeof(PIPEDATA), &dwBytesWrited, NULL))
    {
        goto fun_exit;
    }


    PIPESTATUS status;
    while(1)
    {

        // Read client requests from the pipe.
        bRetCode = ReadFile(hPipe, &status, sizeof(PIPESTATUS),  &dwBytesRead, NULL);
        if(!bRetCode || (dwBytesRead == 0))
        {
            list.SetItemText(inItem, COLUMN_TEXT_STATUS, _T("�����˳���"));

            DisconnectNamedPipe(hPipe);
            break;
        }

        //����״̬
        list.SetItemText(inItem, COLUMN_TEXT_STATUS, status.szStatus);
    }

fun_exit:
    if(hPipe != INVALID_HANDLE_VALUE)
    {
        CloseHandle(hPipe);
    }

    return 0;
}



//������Ϸ����
int CJLkitView::CreateGameProcess(int inItem, bool bInject)
{
    int RetCode;
    CJLkitDoc* pDoc = (CJLkitDoc*)GetDocument();


    std::basic_string<TCHAR> strName = GetListCtrl().GetItemText(inItem, COLUMN_TEXT_ACCOUNT);
    std::basic_string<TCHAR> strPw = GetListCtrl().GetItemText(inItem, COLUMN_TEXT_PASSWORD);
    std::basic_string<TCHAR> strConfig = GetListCtrl().GetItemText(inItem, COLUMN_TEXT_CONFIG);
    std::basic_string<TCHAR> strScript = GetListCtrl().GetItemText(inItem, COLUMN_TEXT_SCRIPT);



    //�Ƿ��Ѿ���¼
    //if(m_ShraeMem.Get((LPCTSTR)strName)) return RESULT_ALREADY_RUNNING;


    //�Ƿ�����Ч����
    if(pDoc->IsHaveValidKey() == FALSE) return RESULT_NOKEY;


    PROCESS_INFORMATION pi;
    ZeroMemory(&pi, sizeof(PROCESS_INFORMATION));

    STARTUPINFO si;
    ZeroMemory(&si, sizeof(STARTUPINFO));
    si.cb = sizeof(si);

    Webpost poster(strName.c_str(), strPw.c_str());
    GetListCtrl().SetItemText(inItem, COLUMN_TEXT_STATUS, _T("��½.."));

#ifdef JLTW
    //̨�����õ�½
#else
    RetCode = poster.Login();
    if(RetCode != RESULT_SUCCESS) return RetCode;
#endif


    //��ȡ����KEY
    std::basic_string<TCHAR> strkey;
    if(!poster.GetStartKey(strkey)) return RESULT_FAIL_GETUKEY;
    GetListCtrl().SetItemText(inItem, COLUMN_TEXT_STATUS, _T("��ȡ��������.."));

    //��ȡ����
    CConfigMgr* pConfig = CConfigMgr::GetInstance();

    //������Ϸ
    TCHAR szCmdLine[MAX_PATH];
    wsprintf(szCmdLine, _T("%s /LaunchByLauncher /SessKey:\"%s\" /CompanyID:\"0\" /ChannelGroupIndex:\"-1\""),
             pConfig->m_szGamePath.c_str(), strkey.c_str());

    GetListCtrl().SetItemText(inItem, COLUMN_TEXT_STATUS, _T("��������.."));
    if(!CreateProcess(NULL, szCmdLine, NULL, NULL, FALSE, CREATE_SUSPENDED, NULL, NULL, &si, &pi))
    {
        TRACE(_T("LastErr: %d"), GetLastError());
        RetCode = RESULT_FAIL_CREATEGAMEPROCESS;
    }
    else
    {

        GetListCtrl().SetItemText(inItem, COLUMN_TEXT_STATUS, _T("����ͨ��.."));

        PIPEDATA stData;
        stData.dwPid = pi.dwProcessId;
        stData.dwItem = inItem;
        _tcscpy(stData.szConfig, strConfig.c_str());
        _tcscpy(stData.szScript, strScript.c_str());
        _tcscpy(stData.szAccount, strName.c_str());

        //�������̺߳����ͨ��
        AfxBeginThread(IPCThread, &stData);


        //ע��
        TCHAR szLibFile[MAX_PATH] = {0};
        GetModuleFileName(NULL, szLibFile, MAX_PATH);

#ifdef JLTW
        _tcscpy(_tcsrchr(szLibFile, TEXT('\\')) + 1, TEXT("JLwg_tw.dll"));
        CInject wgdll(szLibFile);
#else
        _tcscpy(_tcsrchr(szLibFile, TEXT('\\')) + 1, TEXT("JLwg.dll"));
        CInject wgdll(szLibFile);
#endif

        _tcscpy(_tcsrchr(szLibFile, TEXT('\\')) + 1, TEXT("speedhack-i386.dll"));
        CInject spdll(szLibFile);

        if(wgdll.InjectTo(pi.dwProcessId) && spdll.InjectTo(pi.dwProcessId))
        {

            if(ResumeThread(pi.hThread) == 0)
            {
                RetCode = RESULT_NOUSE;
            }
            else
            {
                RetCode = RESULT_LOGIN_SUCCESS;
            }

        }
        else
        {
            RetCode = RESULT_FAIL_INJECT;
            TerminateProcess(pi.hProcess, 0);
            return RetCode;
        }
    }


    return RetCode;
}



UINT AFX_CDECL CJLkitView::WorkThread(LPVOID pVoid)
{
    CJLkitView* pView = (CJLkitView*)pVoid;

    CListCtrl& listctr = pView->GetListCtrl();
    CJLkitDoc* pDoc = (CJLkitDoc*)pView->GetDocument();


    //�����߳���Ϣ����
    MSG msg;
    PeekMessage(&msg, NULL, WM_USER, WM_USER, PM_NOREMOVE);

    while(1)
    {

        //״̬
        pView->m_bWorking = false;

        GetMessage(&msg, NULL, 0, 0);
        pView->m_bWorking = true;

        switch(msg.message)
        {
        case WM_QUIT:
            return 1;

        //�Զ�����Ϣ1����
        case WM_WORKTHREAD_GET:
            {

                int count = listctr.GetItemCount();
                for(int i = 0; i < count; i++)
                {
                    if(listctr.GetCheck(i) && pView->m_bWorking == true)
                    {
                        CString strName = listctr.GetItemText(i, COLUMN_TEXT_ACCOUNT);
                        CString strPw = listctr.GetItemText(i, COLUMN_TEXT_PASSWORD);
                        int nRet = pDoc->Get(strName, strPw);
                        pView->SetResult(nRet, i);
                    }
                }

                break;
            }

        //�Զ�����Ϣ2����
        case WM_WORKTHREAD_ACTIVE:
            {
                int count = listctr.GetItemCount();
                for(int i = 0; i < count; i++)
                {
                    if(listctr.GetCheck(i) && pView->m_bWorking == true)
                    {
                        CString strName = listctr.GetItemText(i, COLUMN_TEXT_ACCOUNT);
                        CString strPw = listctr.GetItemText(i, COLUMN_TEXT_PASSWORD);
                        listctr.SetItemText(i, COLUMN_TEXT_STATUS, _T("���ڵ�¼"));
                        int nRet = pDoc->Active(strName, strPw);
                        pView->SetResult(nRet, i);
                    }
                }
                break;
            }


        case WM_WORKTHREAD_GETANDACTIVE:
            {

                CVpnFile* lpVpnFile = pView->m_lpVpnFile;
                std::basic_fstream<TCHAR>& err = pView->m_errfile;


                //��ȡvpn�ı�
                TCHAR szPathName[MAX_PATH];
                GetModuleFileName(NULL, szPathName, MAX_PATH);
                PathRemoveFileSpec(szPathName);

                //����Ŀ¼
                PathAppend(szPathName, _T("VPN.txt"));

                //���ı�
                if(lpVpnFile->Open(szPathName))
                {
                    AfxMessageBox(_T("�޷��򿪴����ļ�"));
                    return 0;
                }

                //ȡ�õ�ǰģ��·��
                ZeroMemory(szPathName, sizeof(szPathName));
                GetModuleFileName(NULL, szPathName, MAX_PATH);
                PathRemoveFileSpec(szPathName);

                CTime time = CTime::GetCurrentTime();
                PathAppend(szPathName, (LPCTSTR)time.Format("%d��%Hʱ%M��"));
                if(!PathFileExists(szPathName))
                {
                    _tmkdir(szPathName);
                }

                USES_CONVERSION;
                err.open(T2A((LPCTSTR)szPathName));


                //��ʼ
                for(int i = 0; i < listctr.GetItemCount(), pView->m_bWorking == true; i++)
                {

                    CString strName = listctr.GetItemText(i, COLUMN_TEXT_ACCOUNT);
                    CString strPw = listctr.GetItemText(i, COLUMN_TEXT_PASSWORD);

                    CString strLine = strName + _T(", ") + strPw + _T("\n");
                    Webpost poster(strName, strPw);

                    int LoginTimes = 0;
                    BOOL bError = FALSE;

_Again:
                    listctr.SetItemText(i, COLUMN_TEXT_STATUS, _T("���ڵ�¼"));
                    int nResult = poster.Login();
                    pView->SetResult(nResult, i);
                    if(nResult != RESULT_SUCCESS)
                    {

                        if(nResult == RESULT_FAIL_CAPTCHA || nResult == RESULT_FAIL_IPBLOCK)
                        {
                            //���������ֱ�ӻ�ip
                            lpVpnFile->AlwaysConnect();
                            LoginTimes = 0;
                        }
                        else if(nResult == RESULT_FAIL_PWERROR)
                        {
                            //�������ֱ����
                            strLine.Remove(_T('\n'));
                            strLine += _T(" : �������");
                            strLine += _T("\n");

                            bError = TRUE;
                            goto _WriteError;
                        }
                        else
                        {
                            //ʣ�����������
                            TRACE1("ʧ��%d��", LoginTimes++);
                            if(LoginTimes == 2)
                            {
                                lpVpnFile->AlwaysConnect();
                                LoginTimes = 0;
                            }
                        }

                        goto _Again;
                    }

                    listctr.SetItemText(i, COLUMN_TEXT_STATUS, _T("������ȡ"));
                    nResult = poster.Get();
                    pView->SetResult(nResult, i);

                    listctr.SetItemText(i, COLUMN_TEXT_STATUS, _T("���ڼ���"));
                    nResult = poster.Active();
                    pView->SetResult(nResult, i);

                    if(nResult != RESULT_SUCCESS)
                    {
                        bError = TRUE;
                    }


_WriteError:
                    if(bError)
                    {
                        err << (LPCTSTR)strLine;
                    }
                }

                lpVpnFile->Close();

                break;
            }

        case WM_WORKTHREAD_RUN_ALL_GAME:
            {

                //��ǰѡ�е���Ŀ
                for(int i = 0; i < listctr.GetItemCount(); i++)
                {
                    if(listctr.GetCheck(i) && pView->m_bWorking == true)
                    {
                        listctr.SetItemText(i, COLUMN_TEXT_STATUS, _T("��ʼ����.."));
                        int nReslt = pView->CreateGameProcess(i);
                        pView->SetResult(nReslt, i);
                    }
                }

                break;
            }


        case WM_WORKTHREAD_RUN_SINGLE_GAME:
            {

                //��ǰѡ�е���Ŀ
                POSITION pos = listctr.GetFirstSelectedItemPosition();

                while(pos && (pView->m_bWorking == true))
                {
                    int i = listctr.GetNextSelectedItem(pos);
                    listctr.SetItemText(i, COLUMN_TEXT_STATUS, _T("��ʼ����.."));
                    int nReslt = pView->CreateGameProcess(i);
                    pView->SetResult(nReslt, i);
                }

                break;
            }

        default:
            break;

        }

    }


    return 0;
}


void CJLkitView::OnUcStart()
{
    m_pWorkThread->PostThreadMessage(WM_WORKTHREAD_RUN_SINGLE_GAME, 0, 0);
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

void CJLkitView::OnGetAndActive()
{
    m_pWorkThread->PostThreadMessage(WM_WORKTHREAD_GETANDACTIVE, 0, 0);
}

void CJLkitView::OnUpdateUcStart(CCmdUI* pCmdUI)
{
    pCmdUI->Enable(m_bWorking == false);
}

void CJLkitView::OnUcLog()
{
    POSITION rpos = GetListCtrl().GetFirstSelectedItemPosition();
    if(rpos)
    {
        int inItem = GetListCtrl().GetNextSelectedItem(rpos);
        std::basic_string<TCHAR> strName = GetListCtrl().GetItemText(inItem, COLUMN_TEXT_ACCOUNT);

        TCHAR szExePath[MAX_PATH];
        GetModuleFileName(NULL, szExePath, MAX_PATH);
        PathRemoveFileSpec(szExePath);
        PathAppend(szExePath, _T("��־"));
        PathAppend(szExePath, strName.c_str());
        _tcscat(szExePath, _T(".txt"));


        ShellExecute(0, _T("open"), _T("notepad.exe"), szExePath, NULL, SW_SHOWNORMAL);
    }
}

void CJLkitView::OnStopOp()
{
    if(IDOK == AfxMessageBox(_T("ȷ��ȡ����ǰ����?")))
    {
        m_bWorking = false;
    }
}

void CJLkitView::OnUpdateStopOp(CCmdUI* pCmdUI)
{
    pCmdUI->Enable(m_bWorking == true);
}