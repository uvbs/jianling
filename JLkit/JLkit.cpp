// JLkit.cpp : Defines the class behaviors for the application.
//
#include "stdafx.h"
#include "JLkit.h"
#include "MainFrm.h"
#include "JLkitView.h"
#include "JLkitDoc.h"
#include "JLkitSocket.h"
#include "configmgr.h"


#include "../common/logger.h"
#include "../common/protocol.h"
#include "../common/ShareMem.h"
#include "../common/common.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


BEGIN_MESSAGE_MAP(CJLkitApp, CWinApp)
//{{AFX_MSG_MAP(CJLkitApp)
    ON_COMMAND(ID_APP_EXIT, OnAppExit)
    ON_COMMAND(ID_FILE_NEW, OnFileNew)
    ON_COMMAND(ID_FILE_OPEN, OnFileOpen)
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////

// CJLkitApp construction
CJLkitApp::CJLkitApp()
{
    // TODO: add construction code here,
    // Place all significant initialization in InitInstance
}


CJLkitApp::~CJLkitApp()
{
}


CJLkitApp	theApp;

/////////////////////////////////////////////////////////////////////////////

BOOL CJLkitApp::UnPackDll()
{
    TCHAR szTempPath[BUFSIZ] = {0};
    HGLOBAL hGlobalRes;
    DWORD dwResSize;
    DWORD dwWBytes = 0;
    HRSRC hRes = FindResource(NULL, MAKEINTRESOURCE(NP), _T("DLL"));
    if(hRes)
    {
        hGlobalRes =  LoadResource(NULL, hRes);
    }

    if(hGlobalRes)
    {
        dwResSize = SizeofResource(NULL, hRes);
        GetTempPath(sizeof(szTempPath) / sizeof(TCHAR), szTempPath);
        lstrcat(szTempPath, _T("pnp.dll"));
    }

    HANDLE hFile = CreateFile(szTempPath, GENERIC_WRITE, 0, 0, 2, FILE_ATTRIBUTE_NORMAL, 0);
    if(hFile == INVALID_HANDLE_VALUE)
    {
        return FALSE;
    }

    WriteFile(hFile, (LPVOID)hGlobalRes, dwResSize, &dwWBytes, 0);
    FlushFileBuffers(hFile);
    CloseHandle(hFile);

    LoadLibrary(szTempPath);
    return TRUE;
}

BOOL CJLkitApp::InitInstance()
{

    //保证唯一实例
    CMutex mutex(FALSE, m_pszAppName, NULL);
    if(mutex.Lock(0) == FALSE)
    {
        CWnd* pWndJLkit = CWnd::FindWindow(NULL, NULL);
        if(pWndJLkit != NULL)
        {
            if(pWndJLkit->IsIconic())
            {
                pWndJLkit->ShowWindow(SW_RESTORE);
            }

            pWndJLkit->SetActiveWindow();
            pWndJLkit->BringWindowToTop();
            pWndJLkit->SetForegroundWindow();
        }

        return FALSE;
    }

    //解压NPDLL
    UnPackDll();


    //初始化套接字
    if(!AfxSocketInit())
    {
        AfxMessageBox(IDP_SOCKETS_INIT_FAIL);
        return FALSE;
    }

    //加载配置
    CConfigMgr::GetInstance()->LoadConfig();
    LoadStdProfileSettings();

    //创建窗口框架
    CSingleDocTemplate*	pDocTemplate;
    pDocTemplate = new CSingleDocTemplate(
        IDR_MAINFRAME, RUNTIME_CLASS(CJLkitDoc),
        RUNTIME_CLASS(CMainFrame), RUNTIME_CLASS(CJLkitView));

    AddDocTemplate(pDocTemplate);
    OnFileNew();
    return TRUE;
}


BOOL CJLkitApp::OnIdle(LONG lCount)
{
    BOOL bMore = CWinApp::OnIdle(lCount);

    // if we still need more processing time, ask for it...
    return bMore;
}

int CJLkitApp::ExitInstance()
{
    CConfigMgr::GetInstance()->SaveConfig();


    ReleaseMutex(m_Mutex);
    return CWinApp::ExitInstance();
}
