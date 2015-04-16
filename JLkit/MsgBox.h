#if !defined(AFX_MSGBOX_H__6AF06716_1A88_404A_B974_1F611B757436__INCLUDED_)
#define AFX_MSGBOX_H__6AF06716_1A88_404A_B974_1F611B757436__INCLUDED_

#if _MSC_VER > 1000
    #pragma once
#endif // _MSC_VER > 1000
// MsgBox.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMsgBox dialog

class CMsgBox : public CDialog
{
// Construction
public:
    CMsgBox(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
    //{{AFX_DATA(CMsgBox)
    enum { IDD = IDD_MSGBOX };
    CString m_strText;
    //}}AFX_DATA

public:
    void SetMsg(TCHAR szMsg[]);
    void AutoClose(int nTimes);


private:
    DWORD m_closeCount; //¹Ø±Õ¼ÆÊ±

// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CMsgBox)
protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL

// Implementation
protected:

    // Generated message map functions
    //{{AFX_MSG(CMsgBox)
    virtual BOOL OnInitDialog();
    afx_msg void OnTimer(UINT nIDEvent);
	virtual void OnOK();
	//}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MSGBOX_H__6AF06716_1A88_404A_B974_1F611B757436__INCLUDED_)
