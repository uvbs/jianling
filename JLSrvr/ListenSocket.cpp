// ListenSocket.cpp : implementation file
//

#include "stdafx.h"
#include "JLSrvr.h"
#include "ListenSocket.h"
#include "JLSrvrDoc.h"
#include "MainFrm.h"

#include "..\JLkit\JLkitSocket.h"



#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif


// Do not edit the following lines, which are needed by ClassWizard.
#if 0
    BEGIN_MESSAGE_MAP(CListenSocket, CSocket)
        //{{AFX_MSG_MAP(CListenSocket)
        //}}AFX_MSG_MAP
    END_MESSAGE_MAP()
#endif  // 0



/////////////////////////////////////////////////////////////////////////////
// CListenSocket

CListenSocket::CListenSocket()
{

}

CListenSocket::~CListenSocket()
{
}



/////////////////////////////////////////////////////////////////////////////
// CListenSocket member functions

void CListenSocket::OnAccept(int nErrorCode)
{
    TRACE(_T("OnAccept: %d"), nErrorCode);

    //文档
    CMainFrame* pFrame =  (CMainFrame*)AfxGetMainWnd();
    CJLSrvrDoc* pDoc = (CJLSrvrDoc*)pFrame->GetActiveDocument();

    //接受这个套接字
    CJLkitSocket* pNewSock = new CJLkitSocket;
    _ASSERTE(pNewSock != NULL);



    if(Accept(*pNewSock))
    {
        pNewSock->SetSink(pDoc);
        pDoc->AddClient(pNewSock);
    }


}
