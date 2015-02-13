#if !defined(AFX_DLGKEYADD_H__D5B13FC1_D5D2_4C5C_8FBE_5E8B75CBFF34__INCLUDED_)
#define AFX_DLGKEYADD_H__D5B13FC1_D5D2_4C5C_8FBE_5E8B75CBFF34__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgKeyAdd.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgKeyAdd dialog

class CDlgKeyAdd : public CDialog
{
// Construction
public:
    CDlgKeyAdd(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
    //{{AFX_DATA(CDlgKeyAdd)
    enum { IDD = IDD_DLG_ADDKEY };
    CString m_strKey;
    UINT    m_nTime;
    UINT    m_nNums;
    //}}AFX_DATA

// Ù–‘
    CFont m_font;

// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CDlgKeyAdd)
public:
    virtual BOOL DestroyWindow();
protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL

// Implementation
protected:

    // Generated message map functions
    //{{AFX_MSG(CDlgKeyAdd)
    virtual void OnOK();
    afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
    virtual BOOL OnInitDialog();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGKEYADD_H__D5B13FC1_D5D2_4C5C_8FBE_5E8B75CBFF34__INCLUDED_)
