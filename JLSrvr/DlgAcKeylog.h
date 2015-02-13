#if !defined(AFX_DLGACKEYLOG_H__D65635C7_DEB6_4148_A4E9_59FCF30897B6__INCLUDED_)
#define AFX_DLGACKEYLOG_H__D65635C7_DEB6_4148_A4E9_59FCF30897B6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgAcKeylog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgAcKeylog dialog

class CDlgAcKeylog : public CPropertyPage
{
	DECLARE_DYNCREATE(CDlgAcKeylog)

// Construction
public:
	CDlgAcKeylog();
	~CDlgAcKeylog();

// Dialog Data
	//{{AFX_DATA(CDlgAcKeylog)
	enum { IDD = IDD_DIALOG3log };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	CListCtrl	m_ListLog;
	//}}AFX_DATA

    // Ù–‘
    CString m_strAcName;

// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CDlgAcKeylog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CDlgAcKeylog)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGACKEYLOG_H__D65635C7_DEB6_4148_A4E9_59FCF30897B6__INCLUDED_)
