// DbgPage.cpp : implementation file
//

#include "stdafx.h"
#include "jlwg.h"
#include "DbgPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDbgPage dialog


CDbgPage::CDbgPage(CWnd* pParent /*=NULL*/)
	: CPropertyPage(CDbgPage::IDD)
{
	//{{AFX_DATA_INIT(CDbgPage)
	m_strInfo = _T("");
	//}}AFX_DATA_INIT
}


void CDbgPage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDbgPage)
	DDX_Text(pDX, IDC_EDITINFO, m_strInfo);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDbgPage, CDialog)
	//{{AFX_MSG_MAP(CDbgPage)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDbgPage message handlers
