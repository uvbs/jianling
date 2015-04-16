// JLSrvr.h : main header file for the JLSRVR application
//

#if !defined(AFX_JLSRVR_H__CA15C3AE_7D20_4FDC_8DA8_B01E2C37FF5C__INCLUDED_)
#define AFX_JLSRVR_H__CA15C3AE_7D20_4FDC_8DA8_B01E2C37FF5C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CJLSrvrApp:
// See JLSrvr.cpp for the implementation of this class
//


class CJLSrvrApp : public CWinApp
{
    //构造函数
public:
    CJLSrvrApp();


    //计算机名
    CString m_strDefSvr;

// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CJLSrvrApp)
public:
    virtual BOOL InitInstance();
    virtual BOOL OnIdle(LONG lCount);
    //}}AFX_VIRTUAL

// Implementation
    //{{AFX_MSG(CJLSrvrApp)
    afx_msg void OnAppAbout();
    // NOTE - the ClassWizard will add and remove member functions here.
    //    DO NOT EDIT what you see in these blocks of generated code !
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_JLSRVR_H__CA15C3AE_7D20_4FDC_8DA8_B01E2C37FF5C__INCLUDED_)
