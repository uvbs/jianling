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


//����֪ͨ
void CJLkitSocket::OnConnect(int nErrorCode)
{
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
        return;
    }

    TRACE(_T("����: %d"), nRecvSize);

    try
    {


        //���������еȴ������ֽ�
        int nBufSize = m_nRecvWriterPointer + nRecvSize;
        int nProcSize = 0;  //������ĳ���
        int nLeftSize = 0;      //ʣ�೤��
        while(1)
        {

            //calc buf left noprocess size;
            nLeftSize = nBufSize - nProcSize;

            //check , size not complete
            if(nLeftSize < sizeof(Tcp_Head))
            {
                TRACE(_T("��ɴ���, ʣ�೤�� %d bytes\n"), nLeftSize);
                break;
            }

            //get data head
            Tcp_Head* pTcpHead = (Tcp_Head*)(m_cbRecvBuf + nProcSize);

            //get user data len
            int nDataSize = pTcpHead->wPacketSize;
            TRACE(_T("�û����ݳ���: %d"), nDataSize);

            //if user data big than left size
            if(nDataSize > (nLeftSize - sizeof(Tcp_Head)))
            {
                TRACE(_T("�û����ݻ�û����"));
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
        TRACE(_T("���������쳣"));
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
}
