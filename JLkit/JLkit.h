#if !defined _JLKIT_H_
#define _JLKIT_H_


#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//
// This is a part of the Microsoft Foundation Classes C++ library.
// Copyright (C) 1992-1998 Microsoft Corporation
// All rights reserved.
//
// This source code is only intended as a supplement to the
// Microsoft Foundation Classes Reference and related
// electronic documentation provided with the library.
// See these sources for detailed information regarding the
// Microsoft Foundation Classes product.

#ifndef __AFXWIN_H__
#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols



class CJLkitApp : public CWinApp
{

    DECLARE_MESSAGE_MAP()

public:
    CJLkitApp();
    ~CJLkitApp();

// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CJLkitApp)
public:
    virtual BOOL InitInstance();
    virtual BOOL OnIdle(LONG lCount);
    //}}AFX_VIRTUAL
// Implementation

    //{{AFX_MSG(CJLkitApp)
    //}}AFX_MSG
};


#endif
