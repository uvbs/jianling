#if !defined(AFX_LOGINSHEET_H__770249E6_741A_4E31_9DB5_0EF78BEED519__INCLUDED_)
#define AFX_LOGINSHEET_H__770249E6_741A_4E31_9DB5_0EF78BEED519__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LoginSheet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CLoginSheet

class CLoginSheet : public CPropertySheet
{
	DECLARE_DYNAMIC(CLoginSheet)

// Construction
public:
	CLoginSheet(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CLoginSheet(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLoginSheet)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CLoginSheet();

	// Generated message map functions
protected:
	//{{AFX_MSG(CLoginSheet)
	afx_msg void OnClose();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LOGINSHEET_H__770249E6_741A_4E31_9DB5_0EF78BEED519__INCLUDED_)
