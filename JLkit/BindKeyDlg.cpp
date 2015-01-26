// BindKeyDlg.cpp : implementation file
//

#include "stdafx.h"
#include "jlkit.h"
#include "BindKeyDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBindKeyDlg dialog


CBindKeyDlg::CBindKeyDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CBindKeyDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CBindKeyDlg)
	m_strKey = _T("");
	//}}AFX_DATA_INIT
}


void CBindKeyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBindKeyDlg)
	DDX_Text(pDX, IDC_BINDKEY, m_strKey);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CBindKeyDlg, CDialog)
	//{{AFX_MSG_MAP(CBindKeyDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBindKeyDlg message handlers
