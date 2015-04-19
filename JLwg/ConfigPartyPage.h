#if !defined(AFX_CONFIGPARTYPAGE_H__E79E57E9_E4F0_4946_B68B_BF4F1D678A8F__INCLUDED_)
#define AFX_CONFIGPARTYPAGE_H__E79E57E9_E4F0_4946_B68B_BF4F1D678A8F__INCLUDED_

#if _MSC_VER > 1000
    #pragma once
#endif // _MSC_VER > 1000
// ConfigPartyPage.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CConfigPartyPage dialog

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

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CONFIGPARTYPAGE_H__E79E57E9_E4F0_4946_B68B_BF4F1D678A8F__INCLUDED_)
