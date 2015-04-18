#if !defined(AFX_WORKTHREAD_H__6D674540_5009_461C_A473_A848E5AE5BE9__INCLUDED_)
#define AFX_WORKTHREAD_H__6D674540_5009_461C_A473_A848E5AE5BE9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// WorkThread.h : header file
//



/////////////////////////////////////////////////////////////////////////////
// CWorkThread thread

class CWorkThread : public CWinThread
{
	DECLARE_DYNCREATE(CWorkThread)
protected:
	CWorkThread();           // protected constructor used by dynamic creation

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWorkThread)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CWorkThread();

	// Generated message map functions
	//{{AFX_MSG(CWorkThread)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WORKTHREAD_H__6D674540_5009_461C_A473_A848E5AE5BE9__INCLUDED_)
