#if !defined _MODIFYBIND_H
#define _MODIFYBIND_H


//修改绑定对话框
class CDlgModifyBind : public CDialog
{
public:
    CDlgModifyBind(CWnd* pParent = NULL);   // standard constructor
    virtual ~CDlgModifyBind();

// Dialog Data
    //{{AFX_DATA(CDlgModifyBind)
    enum { IDD = IDD_MODIFYBIND };
    CString m_strPw;
    CString m_strName;
    CString m_strOldbind;
    CString m_strNewbind;
    //}}AFX_DATA

    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CDlgModifyBind)
protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL


    // Generated message map functions

public:
    //{{AFX_MSG(CDlgModifyBind)
    virtual void OnOK();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()

private:

};

#endif
