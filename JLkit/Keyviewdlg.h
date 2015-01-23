#if !defined _KEYVIEWDLG_H_
#define _KEYVIEWDLG_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// KeyViewDlg dialog
class CJLkitSocket;
class KeyViewDlg : public CDialog
{
	DECLARE_DYNAMIC(KeyViewDlg)
    DECLARE_MESSAGE_MAP()

public:
	KeyViewDlg(CJLkitDoc* pDoc);   // standard constructor
	virtual ~KeyViewDlg();
    void BindResult(int nResult);
    void UnBindResult(int nResult);
    void QueryKeyResult();

public:
    CJLkitDoc* m_pDoc;
    CJLkitSocket* m_pSocket;


// Dialog Data
	//{{AFX_DATA(KeyViewDlg)
	enum { IDD = IDD_KEY };
	//}}AFX_DATA

protected:
	//{{AFX_VIRTUAL(KeyViewDlg)
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	//}}AFX_VIRTUAL

public:
    //{{AFX_MSG(KeyViewDlg)
	afx_msg void OnQuerykey();
    afx_msg void OnBinkey();
    afx_msg void OnUnbindkey();
    afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
    afx_msg void OnNMRClickListkey(NMHDR *pNMHDR, LRESULT *pResult);
    //}}AFX_MSG

private:
	CListCtrl m_ListCtrl;

};


#endif  //
