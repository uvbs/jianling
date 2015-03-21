// JLSrvrDoc.h : interface of the CJLSrvrDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_JLSRVRDOC_H__4ABA5256_27E0_427F_87E1_2E441B5CA64B__INCLUDED_)
#define AFX_JLSRVRDOC_H__4ABA5256_27E0_427F_87E1_2E441B5CA64B__INCLUDED_

#if _MSC_VER > 1000
    #pragma once
#endif // _MSC_VER > 1000

class CRequestSocket;
class CListenSocket;
class CRequest;
class CJLSrvrDoc : public CDocument
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

    //请求列表
    CObList m_reqList;

    //客户列表
    CObList m_ClientList;


    CListenSocket* m_pListen;
    CTime m_timeStarted;


// Operations
public:
    BOOL StartListening();
    void StopListening();
    void ClientAccept();
    void ClientClose(CRequestSocket* pSock);

    //是否已经登陆
    CRequestSocket* isLogined(TCHAR* szUserName);

    //闲置处理
    BOOL OnIdle(LONG lCount);

    //
    void DocHit(LPARAM lHint, CRequest* pObject);


    //重写
    // ClassWizard generated virtual function overrides
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

// Generated message map functions
protected:
    //{{AFX_MSG(CJLSrvrDoc)
    afx_msg void OnUpdateCalcUpTime(CCmdUI* pCmdUI);
    afx_msg void OnUpdateConnects(CCmdUI* pCmdUI);
    afx_msg void OnFileRestart();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_JLSRVRDOC_H__4ABA5256_27E0_427F_87E1_2E441B5CA64B__INCLUDED_)
