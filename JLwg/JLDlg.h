#ifndef AFX_JLDLG_H__9B29DC05_CA02_4C53_B0F2_D4D00809E70B__INCLUDED_
#define AFX_JLDLG_H__9B29DC05_CA02_4C53_B0F2_D4D00809E70B__INCLUDED_


enum WORKTHREADMSGID
{
    WM_WORKTHREAD_EXCULUA = WM_USER + 555,
    WM_WORKTHREAD_EXCUTASK,
    WM_WORKTHREAD_TESTCOMBATBOSS
};


// CJLDlg dialog
class CJLDlg : public CDialog
{
// Construction
public:
    CJLDlg(CWnd* pParent = NULL);                       // standard constructor
    ~CJLDlg();

    // Dialog Data
    //{{AFX_DATA(CJLDlg)
    enum { IDD = IDD_WGDLG };
    //}}AFX_DATA

    static UINT WorkThread(LPVOID pParam);
    CWinThread* m_pWorkThread;
    bool m_bWorking;


    // Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CJLDlg)
protected:
    virtual void DoDataExchange(CDataExchange* pDX); // DDX/DDV support
    virtual BOOL OnInitDialog();
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
    afx_msg void OnGotask2();
    afx_msg void OnUpdateGoTask(CCmdUI* pCmdUI);
    afx_msg LRESULT OnKickIdle(WPARAM, LPARAM);
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.
#endif // !defined(AFX_JLDLG_H__9B29DC05_CA02_4C53_B0F2_D4D00809E70B__INCLUDED_)
