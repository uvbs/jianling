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
    //构造函数
protected:
    CJLkitSocket(CJLkitDoc* pDoc);

public:
    static CJLkitSocket* GetInstance(CJLkitDoc* pDoc = NULL);
    virtual ~CJLkitSocket();
private:
    static CJLkitSocket* _Instance;

    //属性
public:
    int LoginSrv(CString& strName, CString& strPassWord);
    BOOL ConnectSrv(const CString& strHostName, int nPort);
    void Querykey();
    void BindKey(CString& strKey);
    void Unbindkey(CString& strKey);
    void Reportbug(CString& strBug);
    void Register(CString& strName, CString& strPw, CString& strIP);
    void ModifyBind(CString& strName, CString& strPw, CString& strOld, CString& strNew);
    void Heart();

    CJLkitDoc* m_pDoc;
    LOGIN_BUF m_UserInfo;

    //覆盖
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CJLkitSocket)
	public:
    virtual void OnReceive(int nErrorCode);
    virtual void OnConnect(int nErrorCode);
    virtual int Send(const void* lpBuf, int nBufLen, int nFlags = 0);
    virtual int Receive(void* lpBuf, int nBufLen, int nFlags = 0);
	virtual void OnSend(int nErrorCode);
	virtual void OnClose(int nErrorCode);
	//}}AFX_VIRTUAL

    // Generated message map functions
    //{{AFX_MSG(CJLkitSocket)
    // NOTE - the ClassWizard will add and remove member functions here.
    //}}AFX_MSG

};

#endif // !defined(AFX_CLIENTSOCKET_H__BF7469B0_F694_47D1_ABD7_C858631751B9__INCLUDED_)
