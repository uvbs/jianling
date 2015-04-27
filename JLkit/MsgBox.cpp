// MsgBox.cpp : implementation file
//

#include "stdafx.h"
#include "jlkit.h"
#include "MsgBox.h"

#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMsgBox dialog


CMsgBox::CMsgBox(CWnd* pParent /*=NULL*/)
    : CDialog(CMsgBox::IDD, pParent)
{
    //{{AFX_DATA_INIT(CMsgBox)
    //}}AFX_DATA_INIT
    m_closeCount = 10;
}


void CMsgBox::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CMsgBox)
    DDX_Text(pDX, IDC_TEXT, m_strText);
    //}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMsgBox, CDialog)
    //{{AFX_MSG_MAP(CMsgBox)
    ON_WM_TIMER()
    ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


void CMsgBox::SetMsg(TCHAR szMsg[])
{
    _ASSERTE(szMsg[0] != _T('\0'));
    m_strText = szMsg;
}


void CMsgBox::AutoClose(int nTimes)
{
    m_closeCount = nTimes;
}


/////////////////////////////////////////////////////////////////////////////
// CMsgBox message handlers

BOOL CMsgBox::OnInitDialog()
{
    CDialog::OnInitDialog();

    SetWindowText(_T("提示"));
    SetTimer(IDT_TIMER_CLOSE, 1000, NULL);

    return TRUE;  // return TRUE unless you set the focus to a control
    // EXCEPTION: OCX Property Pages should return FALSE
}

void CMsgBox::OnTimer(UINT nIDEvent)
{
    if(IDT_TIMER_CLOSE == nIDEvent)
    {
        if(m_closeCount <= 1)
        {
            KillTimer(IDT_TIMER_CLOSE);
            m_closeCount = 10;
            OnCancel();
        }

        m_closeCount -= 1;

        CString strTimer;
        strTimer.Format(_T("%d 秒后关闭"), m_closeCount);
        SetDlgItemText(IDC_LEFTTIMES, strTimer);
    }

    CDialog::OnTimer(nIDEvent);
}

void CMsgBox::OnOK() 
{

    KillTimer(IDT_TIMER_CLOSE);
	CDialog::OnOK();
}
