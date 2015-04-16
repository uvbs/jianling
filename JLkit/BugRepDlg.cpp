// BugRepDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Jlkit.h"
#include "JLkitDoc.h"
#include "JLkitSocket.h"
#include "BugRepDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgBugRep dialog


CDlgBugRep::CDlgBugRep()
	: CDialog(CDlgBugRep::IDD, NULL)
{
	//{{AFX_DATA_INIT(CDlgBugRep)
	m_strBug = _T("");
	//}}AFX_DATA_INIT
}


void CDlgBugRep::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgBugRep)
	DDX_Text(pDX, IDC_EDIT1, m_strBug);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgBugRep, CDialog)
	//{{AFX_MSG_MAP(CDlgBugRep)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgBugRep message handlers

void CDlgBugRep::OnOK() 
{
	// TODO: Add extra validation here
    UpdateData();

	CDialog::OnOK();
}
