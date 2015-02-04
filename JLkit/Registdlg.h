#if !defined _CREGISTDLG_H_
#define _CREGISTDLG_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CJLkitSocket;
class CDlgRegist : public CDialog
{
// Construction
public:
	CDlgRegist(CJLkitSocket* pSock, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgRegist)
	enum { IDD = IDD_REGISTER };
	CString m_strName;
	CString m_strPw;
	CString m_strIp;
	//}}AFX_DATA


    CJLkitSocket* m_pSock;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgRegist)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgRegist)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	virtual void OnOK();
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT nIDEvent);
};


#endif
