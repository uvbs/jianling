#if !defined(AFX_LISTENSOCKET_H__30176901_8C78_4537_BB76_0A11E8CB9DED__INCLUDED_)
#define AFX_LISTENSOCKET_H__30176901_8C78_4537_BB76_0A11E8CB9DED__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ListenSocket.h : header file
//



/////////////////////////////////////////////////////////////////////////////
// CListenSocket command target
class CJLSrvrDoc;
class CListenSocket : public CAsyncSocket
{
// Attributes
public:
    CJLSrvrDoc* m_pDoc;

// Operations
public:
	CListenSocket(CJLSrvrDoc *pDoc);
	virtual ~CListenSocket();


// Overrides
public:
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CListenSocket)
    virtual void OnAccept( int nErrorCode );
	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(CListenSocket)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

// Implementation
protected:
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LISTENSOCKET_H__30176901_8C78_4537_BB76_0A11E8CB9DED__INCLUDED_)
