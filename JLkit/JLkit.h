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

    //Ω‚—πDLL
    BOOL UnPackResDll(LPCTSTR lpName, LPCTSTR lpType);

    //≥Ã–ÚŒ®“ª
    BOOL MutexWnd();

private:
    CMutex m_mutex;


// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CJLkitApp)
public:
    virtual BOOL InitInstance();
    virtual BOOL OnIdle(LONG lCount);
    virtual int ExitInstance();
    //}}AFX_VIRTUAL
// Implementation

    //{{AFX_MSG(CJLkitApp)
    //}}AFX_MSG
private:
    HANDLE m_Mutex;
};

#endif



