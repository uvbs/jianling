#if !defined(AFX_REQUESTSOCKET_H__5949C235_7F55_457B_9E1B_074BE2B5F111__INCLUDED_)
#define AFX_REQUESTSOCKET_H__5949C235_7F55_457B_9E1B_074BE2B5F111__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RequestSocket.h : header file
//


#include "..\common\protocol.h"

/////////////////////////////////////////////////////////////////////////////
// CRequestSocket command target
class CJLSrvrDoc;
class CRequest;
class CRequestSocket : public CAsyncSocket
{
// Attributes
public:
    CJLSrvrDoc* m_pDoc;
    CRequest* m_pRequest;
    SOCKADDR_IN m_soaddr;
    CByteArray  m_buf;
    TCHAR m_szName[MAXLEN];
    TCHAR m_szPw[MAXLEN];

    int NoRecvTimes;
// Operations
public:
    CRequestSocket(CJLSrvrDoc* pDoc);
    virtual ~CRequestSocket();
    BOOL ProcessRequest(BYTE* pRequestBuf);
    void InitAccept(SOCKADDR_IN& cltsock);



    //数据库处理
    int GetPwRight(TCHAR szUsername[], TCHAR szPassw[]);
    BOOL ModifyBind(TCHAR szUserName[], TCHAR szPassword[], TCHAR szOldBind[], TCHAR szNewBind[]);
    int Unbindkey(KEY_BUF* pKeyBuf,  sockaddr_in* pSocketAddr);
    BOOL NewRegist(TCHAR szUserName[], TCHAR szPassword[], TCHAR szBindIP[], TCHAR szMac[], TCHAR szClientIp[]);
    BOOL Querykey(std::vector<QUERYKEY_RET_BUF>& vecKeyInfo, TCHAR szUserName[], TCHAR szPassWord[]);
    BOOL Bindkey(KEY_BUF* pKeyBuf);


// Overrides
public:
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CRequestSocket)
public:
    virtual void OnReceive(int nErrorCode);
    virtual int Send(const void* lpBuf, int nBufLen, int nFlags = 0);
    virtual int Receive(void* lpBuf, int nBufLen, int nFlags = 0);
    virtual void OnClose(int nErrorCode);
    //}}AFX_VIRTUAL

    // Generated message map functions
    //{{AFX_MSG(CRequestSocket)
    // NOTE - the ClassWizard will add and remove member functions here.
    //}}AFX_MSG

// Implementation
protected:
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_REQUESTSOCKET_H__5949C235_7F55_457B_9E1B_074BE2B5F111__INCLUDED_)
