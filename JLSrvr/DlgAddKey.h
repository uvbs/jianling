#if !defined(AFX_DLGADDKEY_H__03D6A230_C2C0_4DA5_9445_75C9173BDCB0__INCLUDED_)
#define AFX_DLGADDKEY_H__03D6A230_C2C0_4DA5_9445_75C9173BDCB0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgAddKey.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgAddKey dialog

class CDlgAddKey : public CDialog
{
// Construction
public:
	CDlgAddKey(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgAddKey)
	enum { IDD = IDD_DLG_ADDKEY };
	UINT	m_unCounts;
	CString	m_strKeyOut;
	UINT	m_unTime;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgAddKey)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgAddKey)
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGADDKEY_H__03D6A230_C2C0_4DA5_9445_75C9173BDCB0__INCLUDED_)
