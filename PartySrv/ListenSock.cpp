// ListenSock.cpp : implementation file
//

#include "stdafx.h"
#include "PartySrv.h"
#include "ListenSock.h"
#include "PartySrvDlg.h"

#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

#include "..\JLkit\JLkitSocket.h"


/////////////////////////////////////////////////////////////////////////////
// CListenSock

CListenSock::CListenSock()
{
}

CListenSock::~CListenSock()
{
}


// Do not edit the following lines, which are needed by ClassWizard.
#if 0
    BEGIN_MESSAGE_MAP(CListenSock, CAsyncSocket)
        //{{AFX_MSG_MAP(CListenSock)
        //}}AFX_MSG_MAP
    END_MESSAGE_MAP()
#endif  // 0

/////////////////////////////////////////////////////////////////////////////
// CListenSock member functions

void CListenSock::OnAccept(int nErrorCode)
{
    //框架指针
    CPartySrvDlg* pFrame = (CPartySrvDlg*)AfxGetMainWnd();
    

    //设置回调
    CJLkitSocket* pNewSock = new CJLkitSocket;
    pNewSock->SetSink(pFrame);
    
    //接收一个连接
    if(Accept(*pNewSock) == FALSE)
    {
        TRACE(_T("Accept Fail!"));
        delete pFrame;
    }

    CAsyncSocket::OnAccept(nErrorCode);
}
