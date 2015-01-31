#if !defined _MODIFYBIND_H
#define _MODIFYBIND_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// CDlgModifyBind dialog

class CDlgModifyBind : public CDialog
{
	DECLARE_DYNAMIC(CDlgModifyBind)

public:
	CDlgModifyBind(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgModifyBind();

// Dialog Data
	enum { IDD = IDD_MODIFYBIND };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();

private:
	CString m_strPw;
	CString m_strName;
	CString m_strOldbind;
	CString m_strNewbind;

};

#endif