#if !defined _MAINFRM_H_
#define _MAINFRM_H_


#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000



class CJLkitView;
class CMainFrame : public CFrameWnd
{
public:
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)


public:
	virtual ~CMainFrame();
    void RestoreWinPos();
protected:
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	public:
	//}}AFX_VIRTUAL


protected:  // control bar embedded members
    CStatusBar  m_wndStatusBar;

    // Generated message map functions
protected:
    //{{AFX_MSG(CMainFrame)
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    afx_msg void OnClose();
	//}}AFX_MSG
    DECLARE_MESSAGE_MAP()

};

#endif 
