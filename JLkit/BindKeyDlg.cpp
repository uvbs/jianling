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
// CDlgBindKey dialog


CDlgBindKey::CDlgBindKey(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgBindKey::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgBindKey)
	m_strKey = _T("");
	//}}AFX_DATA_INIT
}


void CDlgBindKey::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgBindKey)
	DDX_Text(pDX, IDC_BINDKEY, m_strKey);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgBindKey, CDialog)
	//{{AFX_MSG_MAP(CDlgBindKey)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgBindKey message handlers
