// ListenSocket.cpp : implementation file
//

#include "stdafx.h"
#include "JLSrvr.h"
#include "ListenSocket.h"
#include "RequestSocket.h"
#include "JLSrvrDoc.h"

#include <MSTcpIP.h>


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


// Do not edit the following lines, which are needed by ClassWizard.
#if 0
BEGIN_MESSAGE_MAP(CListenSocket, CAsyncSocket)
    //{{AFX_MSG_MAP(CListenSocket)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif  // 0



/////////////////////////////////////////////////////////////////////////////
// CListenSocket

CListenSocket::CListenSocket(CJLSrvrDoc* pDoc)
{
    m_pDoc = pDoc;
}

CListenSocket::~CListenSocket()
{
}



/////////////////////////////////////////////////////////////////////////////
// CListenSocket member functions

void CListenSocket::OnAccept(int nErrorCode)
{
    if(nErrorCode == 0)
        m_pDoc->ClientAccept();

}
