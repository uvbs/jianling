// ClientSocket.h: interface for the CClientSocket class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CLIENTSOCKET_H__BF7469B0_F694_47D1_ABD7_C858631751B9__INCLUDED_)
#define AFX_CLIENTSOCKET_H__BF7469B0_F694_47D1_ABD7_C858631751B9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include "..\common\protocol.h"

//这应该是需要个单例模式
//为了是能在程序全局内可以访问到这个类
//并且使用单例来提供避免多次声明此类

class CJLkitDoc;
class CJLkitSocket : public CAsyncSocket
{

protected:
    CJLkitSocket(CJLkitDoc* pDoc);

public:
    static CJLkitSocket* GetInstance(CJLkitDoc* pDoc = NULL)
    {
        if(_Instance == NULL)
        {
            _Instance = new CJLkitSocket(pDoc);
            assert(pDoc != NULL);
        }

        return _Instance;
    }

    virtual ~CJLkitSocket();


    BOOL LoginSrv(CString& strName, CString& strPassWord);
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

public:
    virtual void OnReceive(int nErrorCode);
    virtual void OnConnect(int nErrorCode);
    virtual int Send(const void* lpBuf, int nBufLen, int nFlags = 0);
    virtual int Receive(void* lpBuf, int nBufLen, int nFlags = 0);

private:
    static CJLkitSocket* _Instance;
};

#endif // !defined(AFX_CLIENTSOCKET_H__BF7469B0_F694_47D1_ABD7_C858631751B9__INCLUDED_)
