// ClientSocket.cpp: implementation of the CClientSocket class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "JLkitSocket.h"

#ifdef _DEBUG
    #define new DEBUG_NEW
#endif

CJLkitSocket::CJLkitSocket()
{
    m_Sink = NULL;
    m_nRecvWriterPointer = 0;
}

CJLkitSocket::~CJLkitSocket()
{

}

// Do not edit the following lines, which are needed by ClassWizard.
#if 0
    BEGIN_MESSAGE_MAP(CJLkitSocket, CAsyncSocket)
        //{{AFX_MSG_MAP(CJLkitSocket)
        //}}AFX_MSG_MAP
    END_MESSAGE_MAP()
#endif  // 0


//链接通知
void CJLkitSocket::OnConnect(int nErrorCode)
{
    //给上层通知
    m_Sink->OnEventTCPSocketLink(this, nErrorCode);
}


void CJLkitSocket::OnReceive(int nErrorCode)
{
    TRACE(_T("------------#一次收包#------------"));
    int nRecvSize = CAsyncSocket::Receive(m_cbRecvBuf + m_nRecvWriterPointer, sizeof(m_cbRecvBuf) - m_nRecvWriterPointer, 0);
    ASSERT(nRecvSize != 0);
    if((nRecvSize == SOCKET_ERROR) || (nRecvSize == 0))
    {
        m_Sink->OnEventTCPSocketShut(this, 0);
        return;
    }

    TRACE(_T("长度: %d"), nRecvSize);

    try
    {


        //缓冲区所有等待处理字节
        int nBufSize = m_nRecvWriterPointer + nRecvSize;
        int nProcSize = 0;  //处理过的长度
        int nLeftSize = 0;      //剩余长度
        while(1)
        {

            //calc buf left noprocess size;
            nLeftSize = nBufSize - nProcSize;

            //check , size not complete
            if(nLeftSize < sizeof(Tcp_Head))
            {
                TRACE(_T("完成处理, 剩余长度 %d bytes\n"), nLeftSize);
                break;
            }

            //get data head
            Tcp_Head* pTcpHead = (Tcp_Head*)(m_cbRecvBuf + nProcSize);

            //get user data len
            int nDataSize = pTcpHead->wPacketSize;
            TRACE(_T("用户数据长度: %d"), nDataSize);

            //if user data big than left size
            if(nDataSize > (nLeftSize - sizeof(Tcp_Head)))
            {
                TRACE(_T("用户数据还没完整"));
                break;
            }

            //get user data
            void* pData;
            if(nDataSize == 0)
            {
                pData = NULL;
            }
            else
            {
                pData = pTcpHead + 1;
            }


            //call back
            if(m_Sink)
            {
                m_Sink->OnEventTCPSocketRead(this, *pTcpHead, pData, nDataSize);
            }

            //processed len
            nProcSize += sizeof(Tcp_Head) + nDataSize;
        }

        //剩余数据移动到缓冲区开始
        if(nLeftSize > 0)
        {
            memmove(m_cbRecvBuf, m_cbRecvBuf + nProcSize, nLeftSize);
        }

        //同时设置缓冲区的写入偏移
        m_nRecvWriterPointer = nLeftSize;
        _ASSERTE(m_nRecvWriterPointer < SOCKET_TCP_BUFFER);
    }
    catch(...)
    {
        TRACE(_T("Revice Err!"));
    }
}


BOOL CJLkitSocket::ConnectSrv(LPCTSTR pSrv, long port)
{
    _ASSERTE(m_hSocket == INVALID_SOCKET);

    try
    {
        if(!Create()) return FALSE;


        int iErrorCode = Connect(pSrv, PORT_SRV);
        if(iErrorCode == 0)
        {
            if(WSAGetLastError() != WSAEWOULDBLOCK)
            {
                Close();
                return FALSE;
            }
        }


        return TRUE;
    }
    catch(...)
    {
        TRACE(_T("Connect Err!"));
    }

    return FALSE;
}

int CJLkitSocket::Send(const void* lpBuf, int nBufLen, int nFlags /* = 0 */)
{
    ASSERT(nBufLen != 0);
    ASSERT(lpBuf != NULL);

    WORD wSended = 0;
    try
    {


        do
        {
            int iErrorCode = CAsyncSocket::Send((char*)lpBuf + wSended, nBufLen - wSended, nFlags);
            if(iErrorCode == SOCKET_ERROR || iErrorCode == 0)
            {
                if(WSAGetLastError() == WSAEWOULDBLOCK)
                {
                    Sleep(20);
                    continue;
                }
                else
                {
                    return SOCKET_ERROR;
                }
            }

            wSended += iErrorCode;
        }
        while(wSended < nBufLen);

    }
    catch(...)
    {
        TRACE(_T("发送数据异常"));
        wSended = SOCKET_ERROR;
    }

    return wSended;
}

int CJLkitSocket::Send(int cmd_main, int cmd_sub, void* pData, WORD wDataSize)
{

    Tcp_Head* pTcpHead = (Tcp_Head*)m_cbBuffer;
    pTcpHead->wVersion = 100;
    pTcpHead->wPacketSize = wDataSize;
    pTcpHead->wSubCmdID = cmd_sub;
    pTcpHead->wMainCmdID = cmd_main;

    //有的请求是没有数据的.
    if(pData != NULL && wDataSize > 0)
    {
        memcpy(pTcpHead + 1, pData, wDataSize);
    }

    int nPacketSize = wDataSize + sizeof(Tcp_Head);
    return Send(pTcpHead, nPacketSize);
}

void CJLkitSocket::OnClose(int nErrorCode)
{
    m_Sink->OnEventTCPSocketShut(this, nErrorCode);
}
