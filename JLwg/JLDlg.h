#if !defined(AFX_JLDLG_H__9B29DC05_CA02_4C53_B0F2_D4D00809E70B__INCLUDED_)
#define AFX_JLDLG_H__9B29DC05_CA02_4C53_B0F2_D4D00809E70B__INCLUDED_


// CJLDlg dialog
class CJLDlg : public CDialog
{
// Construction
public:
    CJLDlg(CWnd* pParent = NULL);                       // standard constructor

    // Dialog Data
    //{{AFX_DATA(CJLDlg)
    enum { IDD = IDD_WGDLG };
    //}}AFX_DATA


    CWinThread* m_pTaskThread;
    static UINT TaskThread(LPVOID pParam);

    // Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CJLDlg)
	protected:
    virtual void    DoDataExchange(CDataExchange* pDX); // DDX/DDV support
    virtual BOOL    OnInitDialog();
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL


// Implementation
public:
    // Generated message map functions
    //{{AFX_MSG(CJLDlg)
    afx_msg void OnGotask();
    afx_msg void OnWgdata();
    afx_msg void OnClose();
    afx_msg void OnUnloadwg();
    afx_msg void OnStopTask();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.
#endif // !defined(AFX_JLDLG_H__9B29DC05_CA02_4C53_B0F2_D4D00809E70B__INCLUDED_)
