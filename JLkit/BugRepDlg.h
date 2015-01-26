#if !defined(AFX_BUGREPDLG_H__81554426_4A08_4767_943B_46AB9919CAC5__INCLUDED_)
#define AFX_BUGREPDLG_H__81554426_4A08_4767_943B_46AB9919CAC5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BugRepDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CBugRepDlg dialog
class CJLkitSocket;
class CJLkitDoc;
class CBugRepDlg : public CDialog
{
// Construction
public:
	CBugRepDlg(CJLkitDoc *pDoc);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CBugRepDlg)
	enum { IDD = IDD_REPORTBUG };
	CString	m_strBug;
	//}}AFX_DATA

    CJLkitDoc *m_pDoc;
    CJLkitSocket* m_pSocket;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBugRepDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CBugRepDlg)
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BUGREPDLG_H__81554426_4A08_4767_943B_46AB9919CAC5__INCLUDED_)
