// CFileDialog.cpp : implementation file
//

#include "stdafx.h"
#include "jlkit.h"
#include "CFileDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCFileDialog

IMPLEMENT_DYNAMIC(CCFileDialog, CFileDialog)

CCFileDialog::CCFileDialog(BOOL bOpenFileDialog, LPCTSTR lpszDefExt, LPCTSTR lpszFileName,
		DWORD dwFlags, LPCTSTR lpszFilter, CWnd* pParentWnd) :
		CFileDialog(bOpenFileDialog, lpszDefExt, lpszFileName, dwFlags, lpszFilter, pParentWnd)
{
}

CCFileDialog::~CCFileDialog()
{
    

}

BEGIN_MESSAGE_MAP(CCFileDialog, CFileDialog)
	//{{AFX_MSG_MAP(CCFileDialog)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

