#if !defined(AFX_REQUESTVIEW_H__C6086DF4_B2D0_430F_BBB6_41A22FC0467E__INCLUDED_)
#define AFX_REQUESTVIEW_H__C6086DF4_B2D0_430F_BBB6_41A22FC0467E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RequestView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRequestView view

class CRequestView : public CListView
{
protected:
    CRequestView();           // protected constructor used by dynamic creation
    DECLARE_DYNCREATE(CRequestView)


// Attributes
public:
    void AutoColumnWidth();

    void DoPopupMenu(int type);

// Operations
public:

// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CRequestView)
public:
    virtual void OnInitialUpdate();
protected:
    virtual void OnDraw(CDC* pDC);      // overridden to draw this view
    virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
    //}}AFX_VIRTUAL

// Implementation
protected:
    virtual ~CRequestView();
#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump(CDumpContext& dc) const;
#endif

    // Generated message map functions
protected:
    //{{AFX_MSG(CRequestView)
    afx_msg void OnRclick(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnMenuitem32776();
	//}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_REQUESTVIEW_H__C6086DF4_B2D0_430F_BBB6_41A22FC0467E__INCLUDED_)
