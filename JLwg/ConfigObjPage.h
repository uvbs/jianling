#if !defined(AFX_CONFIGOBJPAGE_H__2416A326_4E09_4F0C_A0C0_946A5B1FC4CD__INCLUDED_)
#define AFX_CONFIGOBJPAGE_H__2416A326_4E09_4F0C_A0C0_946A5B1FC4CD__INCLUDED_

#if _MSC_VER > 1000
    #pragma once
#endif // _MSC_VER > 1000
// ConfigObjPage.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CConfigObjPage dialog

class CConfigObjPage : public CPropertyPage
{
// Construction
public:
    CConfigObjPage(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
    //{{AFX_DATA(CConfigObjPage)
    enum { IDD = IDD_SETINI_OBJFILTER };
    CListCtrl   m_FilterList;
    CListCtrl   m_ObjList;
    //}}AFX_DATA

    void GetSelToFilterList(TCHAR szName[]);
    void RefreshObj();


// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CConfigObjPage)
protected:
    virtual BOOL OnApply();
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL

// Implementation
protected:

    // Generated message map functions
    //{{AFX_MSG(CConfigObjPage)
    virtual BOOL OnInitDialog();
    afx_msg void OnConfigRefresh();
    afx_msg void OnRclickListObjects(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg void OnConfigFirst();
    afx_msg void OnConfigDontkill();
    afx_msg void OnDblclkListObjectfilter(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg void OnItemchangedListObjectfilter(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg void OnDeleteitemListObjectfilter(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg void OnInsertitemListObjectfilter(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg void OnConfigAlwayskill();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CONFIGOBJPAGE_H__2416A326_4E09_4F0C_A0C0_946A5B1FC4CD__INCLUDED_)
