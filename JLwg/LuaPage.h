#if !defined(AFX_LUAPAGE_H__92F36B6E_7161_40F1_AEC1_B994DC996F91__INCLUDED_)
#define AFX_LUAPAGE_H__92F36B6E_7161_40F1_AEC1_B994DC996F91__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LuaPage.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CLuaPage dialog

class CLuaPage : public CPropertyPage
{
// Construction
public:
	CLuaPage(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CLuaPage)
	enum { IDD = IDD_LUA };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLuaPage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CLuaPage)
	afx_msg void OnTestLua();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////
// CDbgPage dialog

class CDbgPage : public CPropertyPage
{
    // Construction
public:
    CDbgPage(CWnd* pParent = NULL);   // standard constructor
    
    // Dialog Data
    //{{AFX_DATA(CDbgPage)
    enum { IDD = IDD_DEBUG };
    //}}AFX_DATA
    
    
    // Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CDbgPage)
protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL
    
    // Implementation
protected:
    
    // Generated message map functions
    //{{AFX_MSG(CDbgPage)
    // NOTE: the ClassWizard will add member functions here
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};



//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LUAPAGE_H__92F36B6E_7161_40F1_AEC1_B994DC996F91__INCLUDED_)
