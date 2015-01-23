#if !defined(AFX_CFILEDIALOG_H__FB13E42C_DFA8_4ECD_A141_D15D067FB882__INCLUDED_)
#define AFX_CFILEDIALOG_H__FB13E42C_DFA8_4ECD_A141_D15D067FB882__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CFileDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCFileDialog dialog

class CCFileDialog : public CFileDialog
{
	DECLARE_DYNAMIC(CCFileDialog)

public:
	CCFileDialog(BOOL bOpenFileDialog, // TRUE for FileOpen, FALSE for FileSaveAs
		LPCTSTR lpszDefExt = NULL,
		LPCTSTR lpszFileName = NULL,
		DWORD dwFlags = OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		LPCTSTR lpszFilter = NULL,
		CWnd* pParentWnd = NULL);

    virtual ~CCFileDialog();
protected:
	//{{AFX_MSG(CCFileDialog)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CFILEDIALOG_H__FB13E42C_DFA8_4ECD_A141_D15D067FB882__INCLUDED_)
