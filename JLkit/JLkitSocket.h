// ClientSocket.h: interface for the CClientSocket class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CLIENTSOCKET_H__BF7469B0_F694_47D1_ABD7_C858631751B9__INCLUDED_)
#define AFX_CLIENTSOCKET_H__BF7469B0_F694_47D1_ABD7_C858631751B9__INCLUDED_


//socket������״̬
enum ConnectState
{
    NOCONNECT = 0,     // û������
    CONNECTTING,       // ������
    CONNECTED,         // ������
    MESPROCESS         // ������Ϣ����
};


class CJLkitSocket;



//����ӿ�
struct ITCPSocketSink
{
    virtual bool OnEventTCPSocketLink(CJLkitSocket* pSocket, INT nErrorCode) = 0;
    virtual bool OnEventTCPSocketShut(CJLkitSocket* pSocket, INT nErrorCode) = 0;
    virtual bool OnEventTCPSocketRead(CJLkitSocket* pSocket, const Tcp_Head &stTcpHead, void* pData, WORD wDataSize) = 0;
};



class CJLkitSocket : public CAsyncSocket
{
    //���캯��
public:
    CJLkitSocket();
    virtual ~CJLkitSocket();


    //�ص�
public:
    void SetSink(ITCPSocketSink* pSink)
    {
        m_Sink = pSink;
    }

private:
    ITCPSocketSink* m_Sink;
    
	char m_cbBuffer[SOCKET_TCP_BUFFER];
    char m_cbRecvBuf[SOCKET_TCP_BUFFER];
    int m_nRecvWriterPointer;   //������д��ָ��


public:
    BOOL ConnectSrv(LPCTSTR pSrv, long port);

    int Send(int cmd_main, int cmd_sub, void* pData, WORD size);

    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CJLkitSocket)
public:
    virtual void OnReceive(int nErrorCode);
    virtual void OnConnect(int nErrorCode);
    virtual void OnClose(int nErrorCode);
    virtual int Send(const void* lpBuf, int nBufLen, int nFlags = 0);
    //}}AFX_VIRTUAL

    // Generated message map functions
    //{{AFX_MSG(CJLkitSocket)
    // NOTE - the ClassWizard will add and remove member functions here.
    //}}AFX_MSG
};





#endif // !defined(AFX_CLIENTSOCKET_H__BF7469B0_F694_47D1_ABD7_C858631751B9__INCLUDED_)
