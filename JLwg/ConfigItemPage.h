#if !defined(AFX_CONFIGITEMPAGE_H__CAB5627F_935A_4483_8472_C1DB1260A37E__INCLUDED_)
#define AFX_CONFIGITEMPAGE_H__CAB5627F_935A_4483_8472_C1DB1260A37E__INCLUDED_

#if _MSC_VER > 1000
    #pragma once
#endif // _MSC_VER > 1000
// ConfigItemPage.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CConfigItemPage dialog

class CConfigItemPage : public CPropertyPage
{
// Construction
public:
    CConfigItemPage(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
    //{{AFX_DATA(CConfigItemPage)
    enum { IDD = IDD_SETINI_ITEMFILTER };
    CListCtrl   m_FilterList;
    CListCtrl   m_BagList;
    //}}AFX_DATA


    void GetSelToFilterList(TCHAR szName[]);


// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CConfigItemPage)
	protected:
    virtual BOOL OnApply();
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
protected:

    // Generated message map functions
    //{{AFX_MSG(CConfigItemPage)
    virtual BOOL OnInitDialog();
    afx_msg void OnRclickListBags(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg void OnConfigCuncang();
    afx_msg void OnConfigFenjie();
    afx_msg void OnConfigJiaoyi();
    afx_msg void OnConfigQhsp();
    afx_msg void OnConfigQhwq();
    afx_msg void OnConfigSell();
    afx_msg void OnDblclkListBagsfilter(NMHDR* pNMHDR, LRESULT* pResult);
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CONFIGITEMPAGE_H__CAB5627F_935A_4483_8472_C1DB1260A37E__INCLUDED_)
