// BindKeyDlg.cpp : implementation file
//

#include "stdafx.h"
#include "JLkit.h"
#include "JLkitDoc.h"
#include "MainFrm.h"
#include "JLkitSocket.h"
#include "BindKeyDlg.h"

#ifdef _DEBUG
    #define new DEBUG_NEW
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
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgBindKey message handlers

void CDlgBindKey::OnOK() 
{
    UpdateData();

    CMainFrame* pFrame =  (CMainFrame*)AfxGetMainWnd();
    CJLkitDoc* pDoc = (CJLkitDoc*)pFrame->GetActiveDocument();
    CJLkitSocket& sock = pDoc->m_socket;
    
    BINDKEY_BUF key;
    _tcscpy(key.key, (LPCTSTR)m_strKey);

    sock.Send(M_KEY, fun_bindkey, &key, sizeof(BINDKEY_BUF));
}
