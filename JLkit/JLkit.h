#if !defined _JLKIT_H_
#define _JLKIT_H_

#ifndef __AFXWIN_H__
    #error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"


class CJLkitApp : public CWinApp
{
    DECLARE_MESSAGE_MAP()
public:
    CJLkitApp();
    ~CJLkitApp();

    //³ÌÐòÎ¨Ò»
    BOOL MutexWnd();
    static BOOL CALLBACK EnumChildProc(HWND hWnd,LPARAM lParam);


// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CJLkitApp)
	public:
    virtual BOOL InitInstance();
    virtual int ExitInstance();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL
// Implementation

public:
    //{{AFX_MSG(CJLkitApp)
    //}}AFX_MSG
};

#endif



