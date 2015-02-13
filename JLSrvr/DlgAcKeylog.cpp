// DlgAcKeylog.cpp : implementation file
//

#include "stdafx.h"
#include "jlsrvr.h"
#include "DlgAcKeylog.h"
#include "RecordKeyLog.h"
#include "DbMngr.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgAcKeylog property page

IMPLEMENT_DYNCREATE(CDlgAcKeylog, CPropertyPage)

CDlgAcKeylog::CDlgAcKeylog() : CPropertyPage(CDlgAcKeylog::IDD)
{
    //{{AFX_DATA_INIT(CDlgAcKeylog)

    //}}AFX_DATA_INIT
}

CDlgAcKeylog::~CDlgAcKeylog()
{
}

void CDlgAcKeylog::DoDataExchange(CDataExchange* pDX)
{
    CPropertyPage::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CDlgAcKeylog)
    DDX_Control(pDX, IDC_LIST2, m_ListLog);
    //}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgAcKeylog, CPropertyPage)
    //{{AFX_MSG_MAP(CDlgAcKeylog)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgAcKeylog message handlers

BOOL CDlgAcKeylog::OnInitDialog()
{
    CPropertyPage::OnInitDialog();

    // TODO: Add extra initialization here
    m_ListLog.InsertColumn(0, _T("卡号"));
    m_ListLog.InsertColumn(1, _T("生成时间"));
    m_ListLog.InsertColumn(2, _T("IP"));


    for(int i = 0; i < 3; i++)
        m_ListLog.SetColumnWidth(i, LVSCW_AUTOSIZE_USEHEADER);


    CRecordKeyLog keylog(CDbMngr::GetInstance());
    keylog.SetAcName(m_strAcName);
    if(keylog.Open())
    {
        int i = 0;
        while(!keylog.IsEOF())
        {
            m_ListLog.InsertItem(i, keylog.m_strKey);
            m_ListLog.SetItemText(i, 1, keylog.m_strTime);
            m_ListLog.SetItemText(i, 2, keylog.m_strIp);

            keylog.MoveNext();
            i++;
        }
    }



    return TRUE;  // return TRUE unless you set the focus to a control
    // EXCEPTION: OCX Property Pages should return FALSE
}
