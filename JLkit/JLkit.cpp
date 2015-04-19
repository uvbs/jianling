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

BOOL CJLkitApp::MutexWnd()
{
    CWnd* PrevCWnd, *ChildCWnd;

    PrevCWnd = CWnd::FindWindow(JLKITCLASSNAME, NULL);
    if(PrevCWnd != NULL)
    {

        ChildCWnd = PrevCWnd->GetLastActivePopup();
        PrevCWnd->BringWindowToTop();

        if(PrevCWnd->IsIconic())
            PrevCWnd->ShowWindow(SW_RESTORE);

        if(PrevCWnd != ChildCWnd)
            ChildCWnd->BringWindowToTop();

        return FALSE;
    }
    else
    {
        return TRUE;
    }

}

BOOL CJLkitApp::InitInstance()
{
    //保证唯一实例
    if(!MutexWnd()) return FALSE;

#ifndef JLTW
    if(!LoadLibrary(_T("JLnp.dll")))
#else
    if(!LoadLibrary(_T("JLnp_tw.dll")))
#endif
    {
        AfxMessageBox(_T("加载NP失败"));
        return FALSE;
    }


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
    if(!PathFileExists(m_szIniPath))
    {
        FILE* fp = _tfopen(m_szIniPath, _T("w+"));
        if(fp == NULL)
        {
            AfxMessageBox(_T("无法创建配置文件"));
            return FALSE;
        }

        fclose(fp);
    }

    //加载配置
    CConfigMgr* pConfig = CConfigMgr::GetInstance();
    if(!pConfig->LoadConfig(m_szIniPath))
    {
        AfxMessageBox(_T("加载配置文件失败"));
        return FALSE;
    }



    //创建窗口框架
    CSingleDocTemplate* pDocTemplate;
    pDocTemplate = new CSingleDocTemplate(
        IDR_MAINFRAME, RUNTIME_CLASS(CJLkitDoc),
        RUNTIME_CLASS(CMainFrame), RUNTIME_CLASS(CJLkitView));
    AddDocTemplate(pDocTemplate);

    //窗口风格
    GdiplusStartupInput gdiplusStartupInput;
    GdiplusStartup(&m_gdiplusToken, &gdiplusStartupInput, NULL);


    m_nCmdShow = SW_HIDE;
    OnFileNew();

    return TRUE;
}

int CJLkitApp::ExitInstance()
{

    //保存配置
    CConfigMgr* pConfig =  CConfigMgr::GetInstance();
    pConfig->SaveConfig(m_szIniPath);

    GdiplusShutdown(m_gdiplusToken);
    return CWinApp::ExitInstance();
}