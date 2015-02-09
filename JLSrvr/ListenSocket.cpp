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
    {
        m_pDoc->ClientAccept();
    }

}

void CListenSocket::OnConnect(int nErrorCode)
{
    // TODO: Add your specialized code here and/or call the base class

    CAsyncSocket::OnConnect(nErrorCode);
}


BOOL CListenSocket::EnableKeepAlive()
{
    tcp_keepalive    inKeepAlive   =   {0};   //输入参数
    unsigned   long   ulInLen   =   sizeof(tcp_keepalive);

    tcp_keepalive    outKeepAlive   =   {0};   //输出参数
    unsigned   long   ulOutLen   =   sizeof(tcp_keepalive);
    unsigned   long   ulBytesReturn   =   0;

    //设置socket的keep   alive为10秒，并且发送次数为3次
    inKeepAlive.onoff   =   1;
    inKeepAlive.keepaliveinterval   =   4000;   //两次KeepAlive探测间的时间间隔
    inKeepAlive.keepalivetime   =   1000;   //开始首次KeepAlive探测前的TCP空闭时间

    int nRet = WSAIoctl(m_hSocket, SIO_KEEPALIVE_VALS, (LPVOID)&inKeepAlive,
                        ulInLen, (LPVOID)&outKeepAlive, ulOutLen, &ulBytesReturn, NULL, NULL);
    if(SOCKET_ERROR == nRet)
    {
        return FALSE;
    }

    return TRUE;
}