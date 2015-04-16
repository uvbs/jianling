#if !defined _KEYVIEWDLG_H_
#define _KEYVIEWDLG_H_


// CDlgKeyView dialog
class CDlgKeyView : public CDialog
{
    DECLARE_DYNAMIC(CDlgKeyView)
    DECLARE_MESSAGE_MAP()

public:
    CDlgKeyView();   // standard constructor
    virtual ~CDlgKeyView();
    

public:
    CListCtrl m_ListCtrl;


// Dialog Data
    //{{AFX_DATA(CDlgKeyView)
    enum { IDD = IDD_KEY };
    //}}AFX_DATA

protected:
    //{{AFX_VIRTUAL(CDlgKeyView)
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    virtual BOOL OnInitDialog();
    //}}AFX_VIRTUAL

public:
    //{{AFX_MSG(CDlgKeyView)
    afx_msg void OnQuerykey();
    afx_msg void OnBinkey();
    afx_msg void OnUnbindkey();
    afx_msg void OnNMRClickListkey(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
};


#endif
