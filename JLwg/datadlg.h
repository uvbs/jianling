#if !defined(AFX_DATADLG1_H__2800A9AC_001C_43E1_8873_9016C0DF9B34__INCLUDED_)
#define AFX_DATADLG1_H__2800A9AC_001C_43E1_8873_9016C0DF9B34__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DataDlg1.h : header file
//

#include "GameHook.h"

/////////////////////////////////////////////////////////////////////////////
// CDataDlg dialog

class CDataDlg : public CDialog, public GameHook
{
// Construction
public:
	CDataDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDataDlg)
	enum { IDD = IDD_WGDATA };
	CListCtrl	m_ListCtrl;
	CEdit	m_hEdit;
	CComboBox	m_ComBox;
	UINT	m_nRange;
	BOOL	m_bHook_step;
	BOOL	m_bHook_Dundi;
	BOOL	m_bHook_Pickup1;
	BOOL	m_bHook_quest;
	BOOL	m_bHook_Weaquit;
	BOOL	m_bHook_Accquest;
	BOOL	m_bHook_Combat;
	//}}AFX_DATA

	void CheckHook();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDataDlg)
public:
	virtual BOOL DestroyWindow();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	virtual BOOL OnInitDialog();
	//}}AFX_VIRTUAL


	// Implementation
public:	
	void PrintfAllObject();
	void PrintfPlayerEquip();
	void PrintfRangeTaskItem();
	void PrintfAllUI();
	void PrintfQuest();
	void PrintfBag();
	void InertBagItem(DWORD index, _BAGSTU &BagBuff);
	void PrintfRangeLoot();
	void PrintfStrike();
	void PrintfRangeMonster(BOOL bApplyConfig = FALSE);
	void PrintfRangeObject();
    void AddInfo(TCHAR szFormat[], ...);

private:
	void InsertColumnHelper(TCHAR* column[], int count);


protected:

	// Generated message map functions
	//{{AFX_MSG(CDataDlg)
	afx_msg void OnGetpalyerinfo();
	afx_msg void OnSpeedx();
	afx_msg void OnSelchangeComboDatatype();
	afx_msg void OnBtnConfig();
	afx_msg void OnRefresh();
	afx_msg void OnHookSendstep();
	afx_msg void OnHookYicijianwu();
	afx_msg void OnHookDequest();
	afx_msg void OnHookChuanzhuangbei();
	afx_msg void OnHookDundi();
	afx_msg void OnClr();
	afx_msg void OnTurnto();
	afx_msg void OnSteptoobjet();
	afx_msg void OnRclickList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnScriptwriter();
	afx_msg void OnFindthenkill();
	afx_msg void OnHookAcceptquest();
	afx_msg void OnHookstrike();
	afx_msg void OnHookCombat();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
 
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DATADLG1_H__2800A9AC_001C_43E1_8873_9016C0DF9B34__INCLUDED_)
