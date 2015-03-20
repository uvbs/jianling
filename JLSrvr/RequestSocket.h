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
//¹¹Ôìº¯Êý
public:
    CRequestSocket(CJLSrvrDoc* pDoc);
    virtual ~CRequestSocket();


// Attributes
public:
    CJLSrvrDoc* m_pDoc;

    SOCKADDR_IN m_soaddr;

    CByteArray  m_buf;
    int         m_cbOut;


    TCHAR m_szName[MAXLEN];
    TCHAR m_szPw[MAXLEN];


    int NoRecvTimes;

    CPtrList m_reqList;
    CRequest* m_pRequest;


// Operations
public:

    BOOL ProcessRequest(BYTE* pRequestBuf);
    void InitAccept();
    CString GetNowTime();

// Overrides
public:
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CRequestSocket)
public:
    virtual void OnReceive(int nErrorCode);
    virtual int Send(const void* lpBuf, int nBufLen, int nFlags = 0);
    virtual int Receive(void* lpBuf, int nBufLen, int nFlags = 0);
    virtual void OnClose(int nErrorCode);
    virtual void OnSend(int nErrorCode);
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
