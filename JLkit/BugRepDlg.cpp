// BugRepDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Jlkit.h"
#include "JLkitDoc.h"
#include "JLkitSocket.h"
#include "BugRepDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBugRepDlg dialog


CBugRepDlg::CBugRepDlg(CJLkitDoc *pDoc)
	: CDialog(CBugRepDlg::IDD, NULL)
{
	//{{AFX_DATA_INIT(CBugRepDlg)
	m_strBug = _T("");
	//}}AFX_DATA_INIT
    m_pDoc = pDoc;
    m_pSocket = pDoc->m_pSocket;

}


void CBugRepDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBugRepDlg)
	DDX_Text(pDX, IDC_EDIT1, m_strBug);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CBugRepDlg, CDialog)
	//{{AFX_MSG_MAP(CBugRepDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBugRepDlg message handlers

void CBugRepDlg::OnOK() 
{
	// TODO: Add extra validation here
    UpdateData();
	m_pSocket->Reportbug(m_strBug);
	CDialog::OnOK();
}
