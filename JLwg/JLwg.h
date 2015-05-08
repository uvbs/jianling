#ifndef _JLWG_H_
#define _JLWG_H_

#ifndef __AFXWIN_H__
    #error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

#include "..\common\logger.h"


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


    HWND m_hGameWnd;
    WNDPROC wpOrigGameProc;
    CJLDlg* m_pWgDlg;


    //外挂线程
    static DWORD CALLBACK WgThread(LPVOID pParam);


// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CJLwgApp)
    virtual BOOL InitInstance();
    virtual int ExitInstance();
    //}}AFX_VIRTUAL

};




class GameLog : public Logger
{
public:
    GameLog(){};
    virtual ~GameLog(){};
    
    DECLARE_SINGLETON(GameLog)
};


#define LOGER   GameLog::GetInstance()->info
#define SENDLOG theApp.SendStatus

extern CJLwgApp theApp;

#endif