#if !defined(AFX_DBLOGINDLG_H__9A9F09BF_0881_45DB_83D4_E115A2C90942__INCLUDED_)
#define AFX_DBLOGINDLG_H__9A9F09BF_0881_45DB_83D4_E115A2C90942__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DBLoginDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDBLoginDlg dialog

class CDBLoginDlg : public CDialog
{
// Construction
public:
	CDBLoginDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDBLoginDlg)
	enum { IDD = IDD_DLG_LOGIN };
	CComboBox	m_ComBox;
	CString	m_strDBName;
	CString	m_strIP;
	CString	m_strPassW;
	CString	m_strUserName;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDBLoginDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDBLoginDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DBLOGINDLG_H__9A9F09BF_0881_45DB_83D4_E115A2C90942__INCLUDED_)
