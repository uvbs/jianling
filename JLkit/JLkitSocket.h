// ClientSocket.h: interface for the CClientSocket class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CLIENTSOCKET_H__BF7469B0_F694_47D1_ABD7_C858631751B9__INCLUDED_)
#define AFX_CLIENTSOCKET_H__BF7469B0_F694_47D1_ABD7_C858631751B9__INCLUDED_



#include "..\common\protocol.h"


class CJLkitDoc;
class CJLkitSocket : public CAsyncSocket
{
    //¹¹Ôìº¯Êý
protected:
    CJLkitSocket();
public:
    static CJLkitSocket* GetInstance();
    virtual ~CJLkitSocket();
    void SetDoc(CJLkitDoc* pDoc);
    void Delete();
private:
    static CJLkitSocket* _Instance;
    CJLkitDoc* m_pDoc;
    LOGIN_BUF m_UserInfo;



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
