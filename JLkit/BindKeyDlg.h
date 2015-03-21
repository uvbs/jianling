#if !defined(AFX_BINDKEYDLG_H__80DB6E3E_0BC5_4171_A55D_CB86A4F8B20E__INCLUDED_)
#define AFX_BINDKEYDLG_H__80DB6E3E_0BC5_4171_A55D_CB86A4F8B20E__INCLUDED_


//°ó¶¨key¶Ô»°¿ò
class CDlgBindKey : public CDialog
{
// Construction
public:
    CDlgBindKey(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
    //{{AFX_DATA(CDlgBindKey)
    enum { IDD = IDD_BINDKEY };
    CString	m_strKey;
    //}}AFX_DATA

// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CDlgBindKey)
protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL

// Implementation
protected:

    // Generated message map functions
    //{{AFX_MSG(CDlgBindKey)
    // NOTE: the ClassWizard will add member functions here
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BINDKEYDLG_H__80DB6E3E_0BC5_4171_A55D_CB86A4F8B20E__INCLUDED_)
