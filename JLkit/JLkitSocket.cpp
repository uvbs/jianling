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
    //�Ͽ��׽���
    Close();

    //����״̬
    m_bConnectState = NOCONNECT;

}

//����֪ͨ
void CJLkitSocket::OnConnect(int nErrorCode)
{
    if(nErrorCode == 0)
    {
        //��������״̬
        m_bConnectState = CONNECTED;
    }
    else
    {
        CloseSocket();
    }

    //���ϲ�֪ͨ
    m_Sink->OnEventTCPSocketLink(this, nErrorCode);
}


void CJLkitSocket::OnReceive(int nErrorCode)
{
    TRACE(_T("------------#һ���հ�#------------"));
    int nRecvSize = CAsyncSocket::Receive(m_cbRecvBuf + m_nRecvWriterPointer, sizeof(m_cbRecvBuf) - m_nRecvWriterPointer, 0);
    ASSERT(nRecvSize != 0);
    if((nRecvSize == SOCKET_ERROR) || (nRecvSize == 0))
    {
        m_Sink->OnEventTCPSocketShut(this, 0);
        CloseSocket();
        return;
    }

    TRACE(_T("����: %d"), nRecvSize);

    try
    {


        //���������еȴ������ֽ�
        int nBufSize = m_nRecvWriterPointer + nRecvSize;
        int nProcSize = 0;  //������ĳ���
        int nLeftSize;      //ʣ�೤��
        while(1)
        {

            //����ʣ�೤��
            nLeftSize = nBufSize - nProcSize;

            //Ч��, ���Ȳ���һ����ͷ��С
            if(nLeftSize < sizeof(Tcp_Head))
            {
                TRACE(_T("������һ��������, ʣ�� %d bytes\n"), nLeftSize);
                break;
            }

            //��ȡ��ͷ
            Tcp_Head* pTcpHead = (Tcp_Head*)(m_cbRecvBuf + nProcSize);

            //��ȡ�û����ݴ�С
            int nDataSize = pTcpHead->wPacketSize;
            TRACE(_T("�û����ݳ���: %d"), nDataSize);

            //����û����ݴ���ʣ�ദ������
            if(nDataSize >= nLeftSize)
            {
                TRACE(_T("�û����ݻ�δ��ȡ����"));
                break;
            }

            //��ȡ�û�����
            void* pData = pTcpHead + 1;

            //����״̬Ϊ����
            m_bConnectState = MESPROCESS;

            // �����������������������Ϣ
            if(m_Sink)
            {
                m_Sink->OnEventTCPSocketRead(this, *pTcpHead, pData, nDataSize);
            }

            //�Ѿ�����ĳ���
            nProcSize += sizeof(Tcp_Head) + nDataSize;
        }

        //ʣ�������ƶ�����������ʼ
        if(nLeftSize > 0)
        {
            memmove(m_cbRecvBuf, m_cbRecvBuf + nProcSize, nLeftSize);
        }

        //ͬʱ���û�������д��ƫ��
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

    //Ч�����
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
        TRACE(_T("���������쳣"));
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

    //�е�������û�����ݵ�.
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
