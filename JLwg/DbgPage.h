#if !defined(AFX_DBGPAGE_H__69F6BD6F_9373_4727_A1A2_A5CC2064154B__INCLUDED_)
#define AFX_DBGPAGE_H__69F6BD6F_9373_4727_A1A2_A5CC2064154B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DbgPage.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDbgPage dialog

class CDbgPage : public CPropertyPage
{
// Construction
public:
	CDbgPage(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDbgPage)
	enum { IDD = IDD_DEBUG };
	CString	m_strInfo;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDbgPage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDbgPage)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DBGPAGE_H__69F6BD6F_9373_4727_A1A2_A5CC2064154B__INCLUDED_)
