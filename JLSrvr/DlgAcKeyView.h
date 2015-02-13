#if !defined(AFX_DLGACKEYVIEW_H__1DADA5F8_41ED_4AB5_85C4_76C38B5A17A3__INCLUDED_)
#define AFX_DLGACKEYVIEW_H__1DADA5F8_41ED_4AB5_85C4_76C38B5A17A3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgAcKeyView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgAcKeyView record view

#include "RecordKeyLog.h"

class CDlgAcKeyView : public CRecordView
{
protected:
	CDlgAcKeyView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CDlgAcKeyView)

// Form Data
public:
	//{{AFX_DATA(CDlgAcKeyView)
	enum { IDD = IDD_DIALOG3 };
	CRecordKeyLog* m_pSet;
	//}}AFX_DATA

// Attributes
public:

// Operations
public:
	CRecordKeyLog* GetRecordset();


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgAcKeyView)
		// NOTE - the ClassWizard will add and remove member functions here.
	public:
	virtual CRecordset* OnGetRecordset();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnInitialUpdate();
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CDlgAcKeyView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CDlgAcKeyView)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGACKEYVIEW_H__1DADA5F8_41ED_4AB5_85C4_76C38B5A17A3__INCLUDED_)
