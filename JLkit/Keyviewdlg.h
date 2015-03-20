#if !defined _KEYVIEWDLG_H_
#define _KEYVIEWDLG_H_



#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


// CDlgKeyView dialog
class CJLkitSocket;
class CDlgKeyView : public CDialog
{
    DECLARE_DYNAMIC(CDlgKeyView)
    DECLARE_MESSAGE_MAP()

public:
    CDlgKeyView(CJLkitDoc* pDoc);   // standard constructor
    virtual ~CDlgKeyView();
    void BindResult(int nResult);
    void UnBindResult(int nResult);
    void QueryKeyResult();

public:
    CJLkitDoc* m_pDoc;
    CJLkitSocket* m_pSocket;


// Dialog Data
    //{{AFX_DATA(CDlgKeyView)
    enum { IDD = IDD_KEY };
    //}}AFX_DATA

protected:
    //{{AFX_VIRTUAL(CDlgKeyView)
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    virtual BOOL OnInitDialog();
    //}}AFX_VIRTUAL

public:
    //{{AFX_MSG(CDlgKeyView)
    afx_msg void OnQuerykey();
    afx_msg void OnBinkey();
    afx_msg void OnUnbindkey();
    afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
    afx_msg void OnNMRClickListkey(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG

private:
    CListCtrl m_ListCtrl;

};


#endif  //
