#if !defined(AFX_BINDKEYDLG_H__80DB6E3E_0BC5_4171_A55D_CB86A4F8B20E__INCLUDED_)
#define AFX_BINDKEYDLG_H__80DB6E3E_0BC5_4171_A55D_CB86A4F8B20E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BindKeyDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CBindKeyDlg dialog

class CBindKeyDlg : public CDialog
{
// Construction
public:
	CBindKeyDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CBindKeyDlg)
	enum { IDD = IDD_BINDKEY };
	CString	m_strKey;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBindKeyDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CBindKeyDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BINDKEYDLG_H__80DB6E3E_0BC5_4171_A55D_CB86A4F8B20E__INCLUDED_)
