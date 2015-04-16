// JLkit.cpp : Defines the class behaviors for the application.
//
#include "stdafx.h"
#include "JLkit.h"
#include "MainFrm.h"
#include "JLkitView.h"
#include "JLkitDoc.h"
#include "JLkitSocket.h"
#include "configmgr.h"


#ifdef _DEBUG
    #define new DEBUG_NEW
#endif

using namespace Gdiplus;


//唯一实例
CJLkitApp   theApp;



//消息映射
BEGIN_MESSAGE_MAP(CJLkitApp, CWinApp)
//{{AFX_MSG_MAP(CJLkitApp)
    ON_COMMAND(ID_APP_EXIT, OnAppExit)
    ON_COMMAND(ID_FILE_NEW, OnFileNew)
    ON_COMMAND(ID_FILE_OPEN, OnFileOpen)
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////

CJLkitApp::CJLkitApp()
{
    m_szIniPath[0] = 0;
}


CJLkitApp::~CJLkitApp()
{
}

BOOL CJLkitApp::UnPackResDll(LPCTSTR lpName, LPCTSTR lpType)
{
    TCHAR szTempPath[BUFSIZ] = {0};
    HGLOBAL hGlobalRes;
    DWORD dwResSize;
    DWORD dwWBytes = 0;

    HRSRC hRes = FindResource(NULL, lpName, lpType);
    if(hRes)
    {
        hGlobalRes =  LoadResource(NULL, hRes);
    }

    if(hGlobalRes)
    {
        dwResSize = SizeofResource(NULL, hRes);
        GetTempPath(sizeof(szTempPath) / sizeof(TCHAR), szTempPath);
        lstrcat(szTempPath, lpType);
        lstrcat(szTempPath, _T(".dll"));
    }

    HANDLE hFile = CreateFile(szTempPath, GENERIC_WRITE, 0, 0, 2, FILE_ATTRIBUTE_NORMAL, 0);
    if(hFile == INVALID_HANDLE_VALUE) return FALSE;


    WriteFile(hFile, (LPVOID)hGlobalRes, dwResSize, &dwWBytes, 0);
    FlushFileBuffers(hFile);
    CloseHandle(hFile);

    LoadLibrary(szTempPath);
    return TRUE;
}


BOOL CJLkitApp::MutexWnd()
{
    CWnd* PrevCWnd, *ChildCWnd;
    // Determine if another window with our class name exists.
    PrevCWnd = CWnd::FindWindow(JLKITCLASSNAME, NULL);
    if(PrevCWnd != NULL)
    {
        // If so, does it have any pop-ups?
        ChildCWnd = PrevCWnd->GetLastActivePopup();
        // Bring the main window to the top.
        PrevCWnd->BringWindowToTop();
        // If iconic, restore the main window.
        if(PrevCWnd->IsIconic())
            PrevCWnd->ShowWindow(SW_RESTORE);
        // If there are pop-ups, bring them along too!
        if(PrevCWnd != ChildCWnd)
            ChildCWnd->BringWindowToTop();
        // Return FALSE. This isn't the first instance
        // and we are done activating the previous one.
        return FALSE;
    }
    else
        // First instance. Proceed as normal.
        return TRUE;

}

BOOL CJLkitApp::InitInstance()
{
    //保证唯一实例
    //if(!MutexWnd()) return FALSE;

    //解压NPDLL
    //UnPackDll(MAKEINTRESOURCE(NP), _T("DLL"));


#ifndef JLTW
    if(!LoadLibrary(_T("JLnp.dll")))
    {
        AfxMessageBox(_T("加载NP失败"));
    }
#else
    if(!LoadLibrary(_T("JLnp_tw.dll")))
    {
        AfxMessageBox(_T("加载NP失败"));
    }
#endif

    //初始化套接字
    if(!AfxSocketInit())
    {
        AfxMessageBox(IDP_SOCKETS_INIT_FAIL);
        return FALSE;
    }


    //加载配置文件
    GetModuleFileName(NULL, m_szIniPath, MAX_PATH);
    PathRemoveExtension(m_szIniPath);
    _tcscat(m_szIniPath, _T(".ini"));

    //加载配置
    CConfigMgr* pConfig = CConfigMgr::GetInstance();
    pConfig->LoadConfig(m_szIniPath);



    //创建窗口框架
    CSingleDocTemplate* pDocTemplate;
    pDocTemplate = new CSingleDocTemplate(
        IDR_MAINFRAME, RUNTIME_CLASS(CJLkitDoc),
        RUNTIME_CLASS(CMainFrame), RUNTIME_CLASS(CJLkitView));


    //窗口风格
    GdiplusStartupInput gdiplusStartupInput;
    GdiplusStartup(&m_gdiplusToken, &gdiplusStartupInput, NULL);


    m_nCmdShow = SW_HIDE;
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

    //保存配置
    CConfigMgr* pConfig =  CConfigMgr::GetInstance();
    pConfig->SaveConfig(m_szIniPath);

    GdiplusShutdown(m_gdiplusToken);
    return CWinApp::ExitInstance();
}
