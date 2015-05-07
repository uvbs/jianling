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


    HWND m_hGameWnd;
    WNDPROC wpOrigGameProc;
    CJLDlg* m_pWgDlg;


// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CJLwgApp)
    virtual BOOL InitInstance();
    virtual int ExitInstance();
    //}}AFX_VIRTUAL

};

extern CJLwgApp theApp;

#define SENDLOG theApp.SendStatus

#endif