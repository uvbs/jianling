#if !defined _KEYVIEWDLG_H_
#define _KEYVIEWDLG_H_


class CDlgBindKey;

// CDlgKey dialog
class CDlgKey : public CDialog
{
    DECLARE_DYNAMIC(CDlgKey)
    DECLARE_MESSAGE_MAP()

public:
    CDlgKey(CWnd* pParent = NULL);   // standard constructor
    virtual ~CDlgKey();


    void Querykey();

public:
    CListCtrl m_ListCtrl;
    CDlgBindKey* m_pBindDlg;

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
    afx_msg void OnBinkey();
    afx_msg void OnUnbindkey();
    afx_msg void OnNMRClickListkey(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnQuery();
	//}}AFX_MSG
};


#endif
