#if !defined(AFX_CONFIGQHPAGE_H__DF6BA6C9_4AF4_4190_BB09_A8D021D73DAF__INCLUDED_)
#define AFX_CONFIGQHPAGE_H__DF6BA6C9_4AF4_4190_BB09_A8D021D73DAF__INCLUDED_



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
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
protected:

    // Generated message map functions
    //{{AFX_MSG(CConfigQhPage)
    virtual BOOL OnInitDialog();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};


class CConfigPartyPage : public CPropertyPage
{
    DECLARE_DYNCREATE(CConfigPartyPage)
        
        // Construction
public:
    CConfigPartyPage();
    ~CConfigPartyPage();
    
    // Dialog Data
    //{{AFX_DATA(CConfigPartyPage)
    enum { IDD = IDD_SETINI_PARTY };
    
    //ÑûÇë
    BOOL m_bInvite_Auto;
    BOOL m_bInvite_ALL;
    BOOL m_bInvite_INMAP;
    BOOL m_bInvite_Range;
    int m_nInvite_Range;
    
    //½ÓÊÜÑûÇë
    BOOL m_bAccept_INMAP;
    BOOL m_bAccept_Auto;
    BOOL m_bAccept_ALL;
    BOOL m_bAccept_Range;
    int m_nAccept_Range;
    //}}AFX_DATA
    
    
    // Overrides
    // ClassWizard generate virtual function overrides
    //{{AFX_VIRTUAL(CConfigPartyPage)
public:
    virtual BOOL OnApply();
protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
    //}}AFX_VIRTUAL
    
    // Implementation
protected:
    // Generated message map functions
    //{{AFX_MSG(CConfigPartyPage)
    virtual BOOL OnInitDialog();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
        
};



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
    virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
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
    afx_msg void OnConfigAlwayskill();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};



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

#endif // !defined(AFX_CONFIGQHPAGE_H__DF6BA6C9_4AF4_4190_BB09_A8D021D73DAF__INCLUDED_)
