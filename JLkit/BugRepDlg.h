#if !defined(AFX_BUGREPDLG_H__81554426_4A08_4767_943B_46AB9919CAC5__INCLUDED_)
#define AFX_BUGREPDLG_H__81554426_4A08_4767_943B_46AB9919CAC5__INCLUDED_


//bug�ύ�Ի���
class CDlgBugRep : public CDialog
{
// Construction
public:
	CDlgBugRep();   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgBugRep)
	enum { IDD = IDD_REPORTBUG };
	CString	m_strBug;
	//}}AFX_DATA

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgBugRep)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgBugRep)
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BUGREPDLG_H__81554426_4A08_4767_943B_46AB9919CAC5__INCLUDED_)
