// DlgAddKey.cpp : implementation file
//

#include "stdafx.h"
#include "jlsrvr.h"
#include "JLSrvrDoc.h"
#include "DlgAddKey.h"
#include "MainFrm.h"


#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgAddKey dialog


CDlgAddKey::CDlgAddKey(CWnd* pParent /*=NULL*/)
    : CDialog(CDlgAddKey::IDD, pParent)
{
    //{{AFX_DATA_INIT(CDlgAddKey)
    m_unCounts = 0;
    m_strKeyOut = _T("");
    m_unTime = 0;
    //}}AFX_DATA_INIT
}


void CDlgAddKey::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CDlgAddKey)
    DDX_Text(pDX, IDC_EDIT_COUNTS, m_unCounts);
    DDX_Text(pDX, IDC_EDIT_KEY, m_strKeyOut);
    DDX_Text(pDX, IDC_EDIT_TIME, m_unTime);
    //}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgAddKey, CDialog)
    //{{AFX_MSG_MAP(CDlgAddKey)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgAddKey message handlers

void CDlgAddKey::OnOK()
{
    UpdateData();

    CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
    CJLSrvrDoc* pDoc = (CJLSrvrDoc*)pFrame->GetActiveDocument();

    CString strNew;
    for(int i = 0; i < m_unCounts; i++)
    {
        pDoc->m_db.AddKey(strNew, m_unTime, 1);
        m_strKeyOut += strNew;
        m_strKeyOut += _T("\r\n");
    }

    UpdateData(FALSE);
}
