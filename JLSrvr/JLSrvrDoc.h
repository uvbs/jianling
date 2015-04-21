// JLSrvrDoc.h : interface of the CJLSrvrDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_JLSRVRDOC_H__4ABA5256_27E0_427F_87E1_2E441B5CA64B__INCLUDED_)
#define AFX_JLSRVRDOC_H__4ABA5256_27E0_427F_87E1_2E441B5CA64B__INCLUDED_

#if _MSC_VER > 1000
    #pragma once
#endif // _MSC_VER > 1000

#include "DbMngr.h"
#include "ListenSocket.h"
#include "../JLkit/JLkitSocket.h"

class CJLSrvrDoc : public CDocument, public ITCPSocketSink
{
protected:
    CJLSrvrDoc();
    DECLARE_DYNCREATE(CJLSrvrDoc)

// Attributes
public:
    CString m_strDbName;
    CString m_strDbUser;
    CString m_strDbPw;
    CString m_strIp;
    CString m_strServer;
    CString m_strTitleBase;


    CListenSocket* m_pListen;
    CTime m_timeStarted;

    //加入一个客户端
    bool AddClient(CJLkitSocket* pSocket);

    //删除一个客户端
    bool DeleteClient(CJLkitSocket* pSocket);

    void DeadSocketClear();

    //客户端列表
private:
    std::list<CJLkitSocket*> _client;
    std::map<CJLkitSocket*, LOGIN_BUF> _userdata;
    std::map<CJLkitSocket*, time_t> _heart;


// Operations
public:
    BOOL StartListening();
    void StopListening();


    //网络事件
public:
    virtual bool OnEventTCPSocketLink(CJLkitSocket* pSocket, INT nErrorCode);
    virtual bool OnEventTCPSocketShut(CJLkitSocket* pSocket, BYTE cbShutReason);
    virtual bool OnEventTCPSocketRead(CJLkitSocket* pSocket, const Tcp_Head& stTcpHead, void* pData, WORD wDataSize);


    //处理登陆
    bool ProcessLogin(CJLkitSocket* pSocket, const Tcp_Head& stTcpHead, void* pData, WORD wDataSize);
    bool ProcessKey(CJLkitSocket* pSocket, const Tcp_Head& stTcpHead, void* pData, WORD wDataSize);
    bool ProcessHelp(CJLkitSocket* pSocket, const Tcp_Head& stTcpHead, void* pData, WORD wDataSize);


    //数据库
    CDbMngr m_db;

    //{{AFX_VIRTUAL(CJLSrvrDoc)
public:
    virtual BOOL OnNewDocument();
    virtual void Serialize(CArchive& ar);
    virtual void SetTitle(LPCTSTR lpszTitle);
    virtual void OnCloseDocument();
    //}}AFX_VIRTUAL

// Implementation
public:
    virtual ~CJLSrvrDoc();
#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump(CDumpContext& dc) const;
#endif

protected:
    //{{AFX_MSG(CJLSrvrDoc)
    afx_msg void OnFileRestart();
    afx_msg void OnUpdateConnects(CCmdUI* pCmdUI);
    afx_msg void OnKeyAdd();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};


#endif
