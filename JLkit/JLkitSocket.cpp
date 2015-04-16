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
    m_bConnectState = NOCONNECT;
    m_nRecvWriterPointer = 0;
    m_wSocketID = 0;
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



void CJLkitSocket::CloseSocket()
{
    //断开套接字
    Close();

    //连接状态
    m_bConnectState = NOCONNECT;

}

//链接通知
void CJLkitSocket::OnConnect(int nErrorCode)
{
    if(nErrorCode == 0)
    {
        //更改链接状态
        m_bConnectState = CONNECTED;
    }
    else
    {
        CloseSocket();
    }

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
        CloseSocket();
        return;
    }

    TRACE(_T("长度: %d"), nRecvSize);

    try
    {


        //缓冲区所有等待处理字节
        int nBufSize = m_nRecvWriterPointer + nRecvSize;
        int nProcSize = 0;  //处理过的长度
        int nLeftSize;      //剩余长度
        while(1)
        {

            //计算剩余长度
            nLeftSize = nBufSize - nProcSize;

            //效验, 长度不及一个包头大小
            if(nLeftSize < sizeof(Tcp_Head))
            {
                TRACE(_T("处理完一个缓冲区, 剩余 %d bytes\n"), nLeftSize);
                break;
            }

            //获取包头
            Tcp_Head* pTcpHead = (Tcp_Head*)(m_cbRecvBuf + nProcSize);

            //获取用户数据大小
            int nDataSize = pTcpHead->wPacketSize;
            TRACE(_T("用户数据长度: %d"), nDataSize);

            //如果用户数据大于剩余处理数据
            if(nDataSize >= nLeftSize)
            {
                TRACE(_T("用户数据还未收取完整"));
                break;
            }

            //获取用户数据
            void* pData = pTcpHead + 1;

            //更改状态为处理
            m_bConnectState = MESPROCESS;

            // 让主窗体来处理这个网络消息
            if(m_Sink)
            {
                m_Sink->OnEventTCPSocketRead(this, *pTcpHead, pData, nDataSize);
            }

            //已经处理的长度
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
        CloseSocket();
    }
}


BOOL CJLkitSocket::ConnectSrv(LPCTSTR pSrv, long port)
{

    //效验参数
    ASSERT(m_bConnectState == NOCONNECT);
    ASSERT(m_hSocket == INVALID_SOCKET);


    try
    {
        if(Create() == FALSE) return FALSE;

#ifndef TEST_NETWORK
        int iErrorCode = Connect(pSrv, PORT_SRV);
#else
        int iErrorCode = Connect(_T("127.0.0.1"), PORT_SRV);
#endif
        if(iErrorCode == 0)
        {
            if(WSAGetLastError() != WSAEWOULDBLOCK) FALSE;
        }

        m_bConnectState = CONNECTTING;;
        return TRUE;
    }
    catch(...)
    {
        CloseSocket();
        return FALSE;
    }
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
            if(iErrorCode == SOCKET_ERROR)
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
    char cbBuffer[SOCKET_TCP_BUFFER];

    Tcp_Head* pTcpHead = (Tcp_Head*)cbBuffer;
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
    CloseSocket();
}
