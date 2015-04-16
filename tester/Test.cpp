// Test.cpp : implementation file
//

#include "stdafx.h"
#include "tester.h"
#include "Test.h"

#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Test dialog


Test::Test(CWnd* pParent /*=NULL*/)
    : CDialog(Test::IDD, pParent)
{
    //{{AFX_DATA_INIT(Test)
    // NOTE: the ClassWizard will add member initialization here
    //}}AFX_DATA_INIT
}


void Test::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(Test)
    // NOTE: the ClassWizard will add DDX and DDV calls here
    //}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(Test, CDialog)
    //{{AFX_MSG_MAP(Test)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Test message handlers

void Test::OnOK()
{
    // TODO: Add extra validation here

    CDialog::OnOK();
}

BOOL Test::OnInitDialog()
{
    CDialog::OnInitDialog();

    sock.SetSink(this);

    if(!sock.Create())
    {
        TRACE(_T("创建套接字失败."));
        return 1;
    }


    if(!sock.Connect(_T("liyhtning.xicp.net"), 4567))
    {
        if(WSAGetLastError() != WSAEWOULDBLOCK)
        {
            TRACE(_T("连接服务器失败"));
            return 1;
        }
    }




    return TRUE;  // return TRUE unless you set the focus to a control
    // EXCEPTION: OCX Property Pages should return FALSE
}
