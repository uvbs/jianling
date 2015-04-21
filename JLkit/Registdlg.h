#if !defined _CREGISTDLG_H_
#define _CREGISTDLG_H_



class CDlgRegist : public CPropertyPage
{
// Construction
public:
    CDlgRegist(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
    //{{AFX_DATA(CDlgRegist)
    enum { IDD = IDD_REGISTER };
    CString m_strName;
    CString m_strPw;
    //}}AFX_DATA

    WORD ConstructRegisterPacket(BYTE cbBuffer[], WORD wBufferSize);

// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CDlgRegist)
protected:
    virtual void OnOK();
    virtual BOOL OnInitDialog();
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL

// Implementation
protected:

    // Generated message map functions
    //{{AFX_MSG(CDlgRegist)
    // NOTE: the ClassWizard will add member functions here
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()

public:

};


#endif
