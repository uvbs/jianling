// ClientSocket.h: interface for the CClientSocket class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CLIENTSOCKET_H__BF7469B0_F694_47D1_ABD7_C858631751B9__INCLUDED_)
#define AFX_CLIENTSOCKET_H__BF7469B0_F694_47D1_ABD7_C858631751B9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include "..\common\protocol.h"

class CJLkitDoc;
class CJLkitSocket : public CAsyncSocket  
{
public:
	CJLkitSocket(CJLkitDoc* pDoc);
    DECLARE_DYNAMIC(CJLkitSocket)

	virtual ~CJLkitSocket();


    BOOL LoginSrv(CString &strName, CString &strPassWord);
	BOOL ConnectSrv(const CString &strHostName, int nPort);
    BOOL Querykey();
    BOOL BindKey(CString &strKey);
    void Unbindkey(CString &strKey);
    void Reportbug(CString &strBug);
    void Heart();
    CJLkitDoc* m_pDoc;
    LOGIN_BUF m_UserInfo;

public:
    virtual void OnReceive(int nErrorCode);
	virtual void OnConnect(int nErrorCode);
    virtual int Send(const void* lpBuf, int nBufLen, int nFlags = 0);
    virtual int Receive(void* lpBuf, int nBufLen, int nFlags = 0);

};

#endif // !defined(AFX_CLIENTSOCKET_H__BF7469B0_F694_47D1_ABD7_C858631751B9__INCLUDED_)
