// DlgKeyAdd.cpp : implementation file
//

#include "stdafx.h"
#include "JLSrvr.h"
#include "DlgKeyAdd.h"
#include "DbMngr.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgKeyAdd dialog


CDlgKeyAdd::CDlgKeyAdd(CWnd* pParent /*=NULL*/)
    : CDialog(CDlgKeyAdd::IDD, pParent)
{
    //{{AFX_DATA_INIT(CDlgKeyAdd)
    m_strKey = _T("");
    m_nTime = 0;
    m_nNums = 5;
    //}}AFX_DATA_INIT
}


void CDlgKeyAdd::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CDlgKeyAdd)
    DDX_Text(pDX, IDC_EDIT_KEY, m_strKey);
    DDX_Text(pDX, IDC_EDIT_TIME, m_nTime);
    DDX_Text(pDX, IDC_EDIT2nums, m_nNums);
    //}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgKeyAdd, CDialog)
    //{{AFX_MSG_MAP(CDlgKeyAdd)
    ON_WM_CTLCOLOR()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgKeyAdd message handlers

void CDlgKeyAdd::OnOK()
{
    // TODO: Add extra validation here
    UpdateData();


    
    srand(GetTickCount());
    for(int i = 0; i < m_nNums; i++)
    {
       
        CString strKey(_T(""));
        if(CDbMngr::GetInstance()->AddKey(strKey, m_nTime, 1))
            m_strKey += strKey;
        else
            m_strKey += _T("Ê§°Ü");

        m_strKey += _T("\r\n");

    }


    UpdateData(FALSE);


}

HBRUSH CDlgKeyAdd::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
    HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

    // TODO: Change any attributes of the DC here
    if(pWnd->GetDlgCtrlID() == IDC_EDIT_KEY)
    {
        // Set the text color to red
        pDC->SetTextColor(RGB(0, 0, 255));
    }



    // TODO: Return a different brush if the default is not desired
    return hbr;
}

BOOL CDlgKeyAdd::OnInitDialog()
{
    CDialog::OnInitDialog();

    // TODO: Add extra initialization here


    m_font.CreatePointFont(200, "ËÎÌå");
    GetDlgItem(IDC_EDIT_KEY)->SetFont(&m_font, FALSE);


    return TRUE;  // return TRUE unless you set the focus to a control
    // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CDlgKeyAdd::DestroyWindow()
{
    // TODO: Add your specialized code here and/or call the base class
    m_font.DeleteObject();
    return CDialog::DestroyWindow();
}
