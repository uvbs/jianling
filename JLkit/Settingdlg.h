#if !defined _SETTINGDLG_H_
#define _SETTINGDLG_H_


class CDlgSetting : public CDialog
{
// Construction
public:
    CDlgSetting(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
    //{{AFX_DATA(CDlgSetting)
	enum { IDD = IDD_SETTING };
    CString m_strGamePath;
	BOOL	m_bChkUpdate;
	//}}AFX_DATA


// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CDlgSetting)
protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL

// Implementation
protected:

    // Generated message map functions
    //{{AFX_MSG(CDlgSetting)
    virtual BOOL OnInitDialog();
    afx_msg void OnSettingBrowse();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

#endif
