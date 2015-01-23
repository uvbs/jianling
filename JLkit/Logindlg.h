#if !defined _LOGINDLG_H_
#define _LOGINDLG_H_


#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000





class CJLkitDoc;
class CJLkitSocket;
class CWaitDlg;
class CLoginDlg : public CDialog
{
// Construction
public:
	CLoginDlg(CJLkitDoc* pDoc);   // standard constructor


// Dialog Data
public:
	//{{AFX_DATA(CLoginDlg)
    enum {IDD = IDD_LOGIN};
	CComboBox m_ComBox;
	CString	m_strName;
	CString	m_strPw;
    BOOL bRemPw;
	//}}AFX_DATA

    CJLkitSocket* m_pSocket;
    CJLkitDoc* m_pDoc;

    void LoginResult(int nResult);
    void ConnectResult(int nErrorCode);


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLoginDlg)
	protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    virtual void OnOK();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CLoginDlg)
	afx_msg void OnBtnRegister();
	afx_msg void OnBtnModifybind();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
        void DisableCtrl(BOOL bTrue);
  
};

#endif
