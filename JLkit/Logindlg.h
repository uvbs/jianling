#if !defined _LOGINDLG_H_
#define _LOGINDLG_H_


#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000





class CJLkitDoc;
class CJLkitSocket;
class CDlgLogin : public CDialog
{
// Construction
public:
    CDlgLogin();   // standard constructor


// Dialog Data
public:
    //{{AFX_DATA(CDlgLogin)
    enum {IDD = IDD_LOGIN};
    CComboBox m_ComBox;
    CString m_strName;
    CString m_strPw;
    BOOL m_bRemPw;
    //}}AFX_DATA

    void LoginResult(int nResult);
    void ConnectResult(int nErrorCode);

// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CDlgLogin)
protected:
    virtual BOOL OnInitDialog();
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    virtual void OnOK();
    //}}AFX_VIRTUAL

// Implementation
protected:

    // Generated message map functions
    //{{AFX_MSG(CDlgLogin)
    afx_msg void OnBtnRegister();
    afx_msg void OnBtnModifybind();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()


};

#endif
