#if !defined(AFX_TOOLDLG_H__BA162CCC_8831_4E5E_B68D_46EF3F15F752__INCLUDED_)
#define AFX_TOOLDLG_H__BA162CCC_8831_4E5E_B68D_46EF3F15F752__INCLUDED_



/////////////////////////////////////////////////////////////////////////////
// CToolDlg dialog

class CToolDlg : public CDialog
{
// Construction
public:
	CToolDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CToolDlg)
	enum { IDD = IDD_TOOL };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


    CHook m_dbgprint;
    CHook m_bsEGetInstance;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CToolDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CToolDlg)
	afx_msg void OnCheck1();
	afx_msg void OnCheck2();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TOOLDLG_H__BA162CCC_8831_4E5E_B68D_46EF3F15F752__INCLUDED_)
