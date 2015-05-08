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

    //�ȴ���Ϸ���ڴ���
    BOOL WaitGameCreate(int inMaxTime);

    //ͨ��
    PIPEDATA m_stData;
    HANDLE m_hPipe;
    void SendStatus(TCHAR szText[]);

    //����ʱ�ص�
    BOOL InitPipe();
    BOOL InitLog();


    HWND m_hGameWnd;
    WNDPROC wpOrigGameProc;
    CJLDlg* m_pWgDlg;


    //����߳�
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