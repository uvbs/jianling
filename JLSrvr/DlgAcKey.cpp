// DlgAcKey.cpp : implementation file
//

#include "stdafx.h"
#include "JLsrvr.h"

#include "DlgAcKey.h"
#include "RecordKey.h"
#include "DbMngr.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgAcKey property page

IMPLEMENT_DYNCREATE(CDlgAcKey, CPropertyPage)

CDlgAcKey::CDlgAcKey() : CPropertyPage(CDlgAcKey::IDD)
{
    //{{AFX_DATA_INIT(CDlgAcKey)
    // NOTE: the ClassWizard will add member initialization here
    //}}AFX_DATA_INIT
}

CDlgAcKey::~CDlgAcKey()
{
}

void CDlgAcKey::DoDataExchange(CDataExchange* pDX)
{
    CPropertyPage::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CDlgAcKey)
    DDX_Control(pDX, IDC_LIST1, m_ListHaveKey);
    //}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgAcKey, CPropertyPage)
    //{{AFX_MSG_MAP(CDlgAcKey)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgAcKey message handlers

BOOL CDlgAcKey::OnInitDialog()
{
    CPropertyPage::OnInitDialog();

    // TODO: Add extra initialization here
    m_ListHaveKey.InsertColumn(0, _T("卡号"));
    m_ListHaveKey.InsertColumn(1, _T("生成时间"));
    m_ListHaveKey.InsertColumn(2, _T("使用时间"));
    m_ListHaveKey.InsertColumn(3, _T("剩余时间"));

    for(int i = 0; i < 4; i++)
        m_ListHaveKey.SetColumnWidth(i, LVSCW_AUTOSIZE_USEHEADER);

    CRecordKey key(CDbMngr::GetInstance());
    key.SetAcName(m_strAcName);
    if(key.Open())
    {
        int i = 0;
        while(!key.IsEOF())
        {
            m_ListHaveKey.InsertItem(i, key.m_strKey);
            m_ListHaveKey.SetItemText(i, 1, key.m_strTime);
            m_ListHaveKey.SetItemText(i, 2, key.m_strUse);
            m_ListHaveKey.SetItemText(i, 3, key.m_strLeft);

            key.MoveNext();
            i++;
        }
    }



    return TRUE;  // return TRUE unless you set the focus to a control
    // EXCEPTION: OCX Property Pages should return FALSE
}
