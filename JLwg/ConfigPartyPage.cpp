// ConfigPartyPage.cpp : implementation file
//

#include "stdafx.h"
#include "jlwg.h"
#include "ConfigPartyPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CConfigPartyPage property page

IMPLEMENT_DYNCREATE(CConfigPartyPage, CPropertyPage)

CConfigPartyPage::CConfigPartyPage() : CPropertyPage(CConfigPartyPage::IDD)
{
	//{{AFX_DATA_INIT(CConfigPartyPage)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CConfigPartyPage::~CConfigPartyPage()
{
}

void CConfigPartyPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CConfigPartyPage)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CConfigPartyPage, CPropertyPage)
	//{{AFX_MSG_MAP(CConfigPartyPage)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CConfigPartyPage message handlers
