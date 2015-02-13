#if !defined(AFX_DLGACKEY_H__07D3B68B_0273_464C_9CB8_AFF8ECD6B337__INCLUDED_)
#define AFX_DLGACKEY_H__07D3B68B_0273_464C_9CB8_AFF8ECD6B337__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgAcKey.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgAcKey dialog

class CDlgAcKey : public CPropertyPage
{
	DECLARE_DYNCREATE(CDlgAcKey)

// Construction
public:
	CDlgAcKey();
	~CDlgAcKey();

// Dialog Data
	//{{AFX_DATA(CDlgAcKey)
	enum { IDD = IDD_DIALOG1key };
	CListCtrl	m_ListHaveKey;
	//}}AFX_DATA

    // Ù–‘
    CString m_strAcName;

// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CDlgAcKey)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CDlgAcKey)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGACKEY_H__07D3B68B_0273_464C_9CB8_AFF8ECD6B337__INCLUDED_)
