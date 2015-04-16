// StatusBox.cpp : implementation file
//

#include "stdafx.h"
#include "jlkit.h"
#include "StatusBox.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStatusBox dialog


CStatusBox::CStatusBox(CWnd* pParent /*=NULL*/)
	: CDialog(CStatusBox::IDD, pParent)
{
	//{{AFX_DATA_INIT(CStatusBox)
	//}}AFX_DATA_INIT
}


void CStatusBox::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CStatusBox)
	//}}AFX_DATA_MAP
}

void CStatusBox::SetMsg(TCHAR szMsg[])
{
    GetDlgItem(IDC_TEXT)->SetWindowText(szMsg);
}


BEGIN_MESSAGE_MAP(CStatusBox, CDialog)
	//{{AFX_MSG_MAP(CStatusBox)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStatusBox message handlers
