#pragma once

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols


#include "GamecallEx.h"




class CJLDlg;
class CJLwgApp: public CWinApp
{
public:
	CJLwgApp();
	~CJLwgApp();
    
    static DWORD CALLBACK WgThread(LPVOID pParam);
    static LRESULT CALLBACK GameMsgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

    static WNDPROC wpOrigGameProc;
    static CJLDlg* m_pWgDlg;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CJLwgApp)
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

};


extern GamecallEx gcall;