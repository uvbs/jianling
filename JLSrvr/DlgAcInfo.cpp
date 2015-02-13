// DlgAcInfo.cpp : implementation file
//

#include "stdafx.h"
#include "jlsrvr.h"
#include "DlgAcInfo.h"
#include "RecordAc.h"
#include "DbMngr.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgAcInfo dialog


CDlgAcInfo::CDlgAcInfo(CWnd* pParent /*=NULL*/)
    : CPropertyPage(CDlgAcInfo::IDD)
{
    //{{AFX_DATA_INIT(CDlgAcInfo)
    // NOTE: the ClassWizard will add member initialization here
    //}}AFX_DATA_INIT
}


void CDlgAcInfo::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CDlgAcInfo)
    DDX_Text(pDX, IDC_EDIT1name , m_strName);
    DDX_Text(pDX, IDC_EDIT4ac,  m_strAc);
    DDX_Text(pDX, IDC_EDIT10cpuid, m_strCpuip);
    DDX_Text(pDX, IDC_EDIT8hid, m_strHid);
    DDX_Text(pDX, IDC_EDIT10bios, m_strBios);
    DDX_Text(pDX, IDC_EDIT7mb, m_strMB);
    DDX_Text(pDX, IDC_EDIT5rgtime, m_strRegTime);

    //}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgAcInfo, CDialog)
    //{{AFX_MSG_MAP(CDlgAcInfo)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgAcInfo message handlers

BOOL CDlgAcInfo::OnInitDialog()
{
    CDialog::OnInitDialog();

    // TODO: Add extra initialization here

    CRecordAc ac(CDbMngr::GetInstance());
    ac.SetAcName(m_strAcName);
    if(ac.Open())
    {

        m_strAc = ac.m_strAc;
        m_strName = ac.m_strName;
        m_strRegTime = ac.m_strRegTime;
        m_strBios = ac.m_strBios;
        m_strCpuip = ac.m_strCpuip;
        m_strMB = ac.m_strMB;

    }


    UpdateData(FALSE);
    return TRUE;  // return TRUE unless you set the focus to a control
    // EXCEPTION: OCX Property Pages should return FALSE
}
