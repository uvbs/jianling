#ifndef _JLWG_H_
#define _JLWG_H_

#ifndef __AFXWIN_H__
#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols



class CJLDlg;
class CJLwgApp: public CWinApp
{
public:
    CJLwgApp();
    ~CJLwgApp();

    //等待游戏窗口创建
    BOOL WaitGameCreate(int inMaxTime);

    //通信
    PIPEDATA m_stData;
    HANDLE m_hPipe;
    void SendStatus(TCHAR szText[]);

    //调试时关掉
    BOOL InitPipe();
    BOOL InitLog();


    //游戏窗口过程
    static LRESULT CALLBACK GameWndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
    HWND m_hGameWnd;
    WNDPROC wpOrigGameProc;

    //外挂窗口
    CJLDlg* m_pWgDlg;


    //外挂线程
    static DWORD CALLBACK WorkThread(LPVOID pParam);

    //lua脚本
    void RegGameLib(lua_State* L);
    lua_State* m_pstate;
    bool InitLua();

    //日志
    Logger m_GameLog;

// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CJLwgApp)
    virtual BOOL InitInstance();
    virtual int ExitInstance();
    //}}AFX_VIRTUAL

};


extern CJLwgApp theApp;



#define LOGER   theApp.m_GameLog.info
#define SENDLOG theApp.SendStatus





#endif