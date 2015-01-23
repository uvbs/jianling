#if !defined(AFX_CONFIGSHEET_H__42253DC2_B620_4862_B5F9_A6B9042794BA__INCLUDED_)
#define AFX_CONFIGSHEET_H__42253DC2_B620_4862_B5F9_A6B9042794BA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ConfigSheet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CConfigSheet

class CConfigSheet : public CPropertySheet
{
	DECLARE_DYNAMIC(CConfigSheet)

// Construction
public:
	CConfigSheet(CWnd* pParentWnd = NULL);

// Attributes
public:
	CConfigItemPage itempage;
	CConfigQhPage qhpage;
	CConfigObjPage objpage;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CConfigSheet)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CConfigSheet();

	// Generated message map functions
protected:
	//{{AFX_MSG(CConfigSheet)
	afx_msg void OnApplyNow();
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CONFIGSHEET_H__42253DC2_B620_4862_B5F9_A6B9042794BA__INCLUDED_)
