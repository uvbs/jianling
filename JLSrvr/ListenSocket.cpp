// ListenSocket.cpp : implementation file
//

#include "stdafx.h"
#include "JLSrvr.h"
#include "ListenSocket.h"
#include "RequestSocket.h"
#include "JLSrvrDoc.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

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

void CListenSocket::OnAccept( int nErrorCode )
{
    if(nErrorCode == 0){
        m_pDoc->ClientAccept();
    }

}