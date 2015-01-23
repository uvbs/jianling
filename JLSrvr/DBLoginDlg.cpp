// DBLoginDlg.cpp : implementation file
//

#include "stdafx.h"
#include "JLSrvr.h"
#include "DBLoginDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDBLoginDlg dialog


CDBLoginDlg::CDBLoginDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDBLoginDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDBLoginDlg)
	m_strDBName = _T("bns");
	m_strPassW = _T("Zy@7!3)9");
	m_strUserName = _T("sa");
	//}}AFX_DATA_INIT
}


void CDBLoginDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDBLoginDlg)
	DDX_Control(pDX, IDC_COMBO1, m_ComBox);
	DDX_Text(pDX, IDC_DBNAME, m_strDBName);
	DDX_Text(pDX, IDC_PASSW, m_strPassW);
	DDX_Text(pDX, IDC_USERNAME, m_strUserName);
	DDX_Text(pDX, IDC_COMBO1, m_strIP);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDBLoginDlg, CDialog)
	//{{AFX_MSG_MAP(CDBLoginDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDBLoginDlg message handlers

BOOL CDBLoginDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_ComBox.AddString(_T("127.0.0.1"));
	m_ComBox.AddString(_T("218.74.227.242"));

	m_ComBox.SetCurSel(1);


	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDBLoginDlg::OnOK() 
{
	// TODO: Add extra validation here
	m_ComBox.GetLBText(m_ComBox.GetCurSel(), m_strIP);
	CDialog::OnOK();
}
