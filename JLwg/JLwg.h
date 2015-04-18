#pragma once

#if _MSC_VER > 1000
    #pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
    #error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols
#include "JLDlg.h"


class CJLwgApp: public CWinApp
{
public:
    CJLwgApp();
    ~CJLwgApp();


    //外挂线程
    static DWORD CALLBACK WgThread(LPVOID pParam);
    static LRESULT CALLBACK GameMsgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

    //等待游戏窗口创建
    HWND isGameWndCreated(DWORD dwPid);
    BOOL WaitGameCreate(int inMaxTime);

    PIPEDATA m_stData;
    static HWND m_hGameWnd;

// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CJLwgApp)
    virtual BOOL InitInstance();
    virtual int ExitInstance();
    //}}AFX_VIRTUAL


private:
    static WNDPROC wpOrigGameProc;
    static CJLDlg* m_pWgDlg;
};
