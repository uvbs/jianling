#if !defined(AFX_JLDLG_H__9B29DC05_CA02_4C53_B0F2_D4D00809E70B__INCLUDED_)
#define AFX_JLDLG_H__9B29DC05_CA02_4C53_B0F2_D4D00809E70B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// JLDlg.h : header file
//


/////////////////////////////////////////////////////////////////////////////

// CJLDlg dialog
class CJLDlg : public CDialog
{
// Construction
public:
    CJLDlg(CWnd* pParent = NULL);						// standard constructor

    // Dialog Data
    //{{AFX_DATA(CJLDlg)
    enum { IDD = IDD_WGDLG };
    //}}AFX_DATA


    CWinThread* m_pTaskThread;


    // Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CJLDlg)
protected:
    virtual void	DoDataExchange(CDataExchange* pDX); // DDX/DDV support
    virtual BOOL	OnInitDialog();
    virtual void	PostNcDestroy();
    //}}AFX_VIRTUAL


// Implementation
public:
    // Generated message map functions
    //{{AFX_MSG(CJLDlg)
    afx_msg void	OnGotask();
    afx_msg void	OnWgdata();
    afx_msg void	OnStopTask();
    afx_msg void	OnClose();
    afx_msg void	OnShowWindow(BOOL bShow, UINT nStatus);
    afx_msg void	OnUnloadwg();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.
#endif // !defined(AFX_JLDLG_H__9B29DC05_CA02_4C53_B0F2_D4D00809E70B__INCLUDED_)
