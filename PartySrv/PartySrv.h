// PartySrv.h : main header file for the PARTYSRV application
//

#if !defined(AFX_PARTYSRV_H__E6950AAB_12DA_486B_BFF7_F4AB6D987478__INCLUDED_)
#define AFX_PARTYSRV_H__E6950AAB_12DA_486B_BFF7_F4AB6D987478__INCLUDED_

#if _MSC_VER > 1000
    #pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
    #error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CPartySrvApp:
// See PartySrv.cpp for the implementation of this class
//

class CPartySrvApp : public CWinApp
{
public:
    CPartySrvApp();

// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CPartySrvApp)
public:
    virtual BOOL InitInstance();
    //}}AFX_VIRTUAL

// Implementation

    //{{AFX_MSG(CPartySrvApp)
    // NOTE - the ClassWizard will add and remove member functions here.
    //    DO NOT EDIT what you see in these blocks of generated code !
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PARTYSRV_H__E6950AAB_12DA_486B_BFF7_F4AB6D987478__INCLUDED_)
