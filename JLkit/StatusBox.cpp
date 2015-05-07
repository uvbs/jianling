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
    _ASSERTE(szMsg[0] != _T('\0'));
    GetDlgItem(IDC_TEXT)->SetWindowText(szMsg);
}


BEGIN_MESSAGE_MAP(CStatusBox, CDialog)
	//{{AFX_MSG_MAP(CStatusBox)
	ON_WM_SETFOCUS()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStatusBox message handlers

BOOL CStatusBox::OnInitDialog() 
{
	CDialog::OnInitDialog();

    CenterWindow();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CStatusBox::OnCommand(WPARAM wParam, LPARAM lParam) 
{
	// TODO: Add your specialized code here and/or call the base class
	if(wParam == IDOK || wParam == IDCANCEL) return FALSE;

	return CDialog::OnCommand(wParam, lParam);
}
