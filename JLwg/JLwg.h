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

    //�ȴ���Ϸ���ڴ���
    BOOL WaitGameCreate(int inMaxTime);

    //ͨ��
    PIPEDATA m_stData;
    HANDLE m_hPipe;
    void SendStatus(TCHAR szText[]);

    //����ʱ�ص�
    BOOL InitPipe();
    BOOL InitLog();


    //��Ϸ���ڹ���
    static LRESULT CALLBACK GameWndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
    HWND m_hGameWnd;
    WNDPROC wpOrigGameProc;

    //��Ҵ���
    CJLDlg* m_pWgDlg;


    //����߳�
    static DWORD CALLBACK WorkThread(LPVOID pParam);

    //lua�ű�
    void RegGameLib(lua_State* L);
    lua_State* m_pstate;
    bool InitLua();

    //��־
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