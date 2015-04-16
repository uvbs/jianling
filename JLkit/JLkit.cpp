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


//Ψһʵ��
CJLkitApp   theApp;



//��Ϣӳ��
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
    //��֤Ψһʵ��
    //if(!MutexWnd()) return FALSE;

    //��ѹNPDLL
    //UnPackDll(MAKEINTRESOURCE(NP), _T("DLL"));


#ifndef JLTW
    if(!LoadLibrary(_T("JLnp.dll")))
    {
        AfxMessageBox(_T("����NPʧ��"));
    }
#else
    if(!LoadLibrary(_T("JLnp_tw.dll")))
    {
        AfxMessageBox(_T("����NPʧ��"));
    }
#endif

    //��ʼ���׽���
    if(!AfxSocketInit())
    {
        AfxMessageBox(IDP_SOCKETS_INIT_FAIL);
        return FALSE;
    }


    //���������ļ�
    GetModuleFileName(NULL, m_szIniPath, MAX_PATH);
    PathRemoveExtension(m_szIniPath);
    _tcscat(m_szIniPath, _T(".ini"));

    //��������
    CConfigMgr* pConfig = CConfigMgr::GetInstance();
    pConfig->LoadConfig(m_szIniPath);



    //�������ڿ��
    CSingleDocTemplate* pDocTemplate;
    pDocTemplate = new CSingleDocTemplate(
        IDR_MAINFRAME, RUNTIME_CLASS(CJLkitDoc),
        RUNTIME_CLASS(CMainFrame), RUNTIME_CLASS(CJLkitView));


    //���ڷ��
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

    //��������
    CConfigMgr* pConfig =  CConfigMgr::GetInstance();
    pConfig->SaveConfig(m_szIniPath);

    GdiplusShutdown(m_gdiplusToken);
    return CWinApp::ExitInstance();
}
