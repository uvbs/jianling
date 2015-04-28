#if !defined _LOGINDLG_H_
#define _LOGINDLG_H_


class CDlgLogin : public CPropertyPage
{
// Construction
public:
    CDlgLogin(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
public:
    //{{AFX_DATA(CDlgLogin)
    enum {IDD = IDD_LOGIN};
    CString m_strName;
    CString m_strPw;
    BOOL m_bRemPw;
    CComboBox m_ComBox;
    //}}AFX_DATA


    WORD ConstructLoginPacket(BYTE cbBuffer[], WORD wBufferSize);

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
	//}}AFX_MSG
    DECLARE_MESSAGE_MAP()


};

#endif
