#if !defined(AFX_CONFIGQHPAGE_H__DF6BA6C9_4AF4_4190_BB09_A8D021D73DAF__INCLUDED_)
#define AFX_CONFIGQHPAGE_H__DF6BA6C9_4AF4_4190_BB09_A8D021D73DAF__INCLUDED_

#if _MSC_VER > 1000
    #pragma once
#endif

class CConfigQhPage : public CPropertyPage
{
// Construction
public:
    CConfigQhPage(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
    //{{AFX_DATA(CConfigQhPage)
    enum { IDD = IDD_SETINI_QIANGHUA };
    CComboBox   m_ComBox;
    int     m_HealthPercent;
    //}}AFX_DATA


// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CConfigQhPage)
protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    virtual BOOL OnApply();
    //}}AFX_VIRTUAL

// Implementation
protected:

    // Generated message map functions
    //{{AFX_MSG(CConfigQhPage)
    virtual BOOL OnInitDialog();
    afx_msg void OnEditchangeComboItemcolor();
    afx_msg void OnChangeChiyaopercent();
    afx_msg void OnSelchangeComboItemcolor();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CONFIGQHPAGE_H__DF6BA6C9_4AF4_4190_BB09_A8D021D73DAF__INCLUDED_)
