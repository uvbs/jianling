#if !defined(AFX_LISTENSOCK_H__441CEA5A_369C_45AB_9AE8_016CE416A7E1__INCLUDED_)
#define AFX_LISTENSOCK_H__441CEA5A_369C_45AB_9AE8_016CE416A7E1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ListenSock.h : header file
//



/////////////////////////////////////////////////////////////////////////////
// CListenSock command target

class CListenSock : public CAsyncSocket
{
// Attributes
public:

// Operations
public:
	CListenSock();
	virtual ~CListenSock();

// Overrides
public:
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CListenSock)
	public:
	virtual void OnAccept(int nErrorCode);
	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(CListenSock)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

// Implementation
protected:
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LISTENSOCK_H__441CEA5A_369C_45AB_9AE8_016CE416A7E1__INCLUDED_)
