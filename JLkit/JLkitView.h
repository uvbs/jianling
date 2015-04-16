// JLkitView.h: interface for the CJLkitView class.
//
//////////////////////////////////////////////////////////////////////
#if !defined(AFX_JLKITVIEW_H__2A3B3EDF_5BC0_49E0_8991_A0C7672EA797__INCLUDED_)
#define AFX_JLKITVIEW_H__2A3B3EDF_5BC0_49E0_8991_A0C7672EA797__INCLUDED_

#if _MSC_VER > 1000
    #pragma once
#endif // _MSC_VER > 1000


enum
{
    COLUMN_TEXT_CHECKBOX = 0,
    COLUMN_TEXT_ACCOUNT,
    COLUMN_TEXT_PASSWORD,
    COLUMN_TEXT_CONFIG,
    COLUMN_TEXT_SCRIPT,
    COLUMN_TEXT_STATUS,
    COLUMN_TEXT_NUMS
};


enum
{
    RESULT_FAIL_INJECT = 100,
    RESULT_NOKEY,
    RESULT_ALREADY_RUNNING,
    RESULT_FAIL_CREATEGAMEPROCESS,
    RESULT_LOGIN_SUCCESS
};


class CJLkitView : public CListView
{
protected:
    CJLkitView();
    virtual ~CJLkitView();
    DECLARE_DYNCREATE(CJLkitView)

public:
    //串行文本
    void SerializeText(CArchive& ar);

    //加载游戏
    void LaunchGame();

    //领取和激活
    void OnGet();
    void OnActive();

    //账号数量
    int m_LineNums;

    //插入行
    void InsertLine(int index, const TCHAR szName[], const TCHAR szPw[], const TCHAR szConfig[], const TCHAR szScript[]);

    //显示结果
    void SetResult(int nResult, int i);

    //设置行颜色
    void SetItemColor(DWORD iItem, COLORREF color);

private:
    CMap<DWORD, DWORD&, COLORREF, COLORREF&> MapItemColor;

    bool ReadLine(std::basic_string<TCHAR>& strLine, CFile *pFile);

// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CJLkitView)
protected:
    virtual void    OnInitialUpdate();
    virtual BOOL    PreCreateWindow(CREATESTRUCT& cs);
    virtual void    OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
    virtual void    PostNcDestroy();
    //}}AFX_VIRTUAL
// Generated message map functions


public:
    //{{AFX_MSG(CJLkitView)
    afx_msg void OnNMCustomdraw(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg int  OnCreate(LPCREATESTRUCT lpCreateStruct);
    afx_msg void OnStart();
    afx_msg void OnRclick(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg void OnProfile();
    afx_msg void OnReportbug();
    afx_msg void OnTimer(UINT nIDEvent);
    afx_msg void OnUpdateProfile(CCmdUI* pCmdUI);
    afx_msg void OnUpdateSelectall(CCmdUI* pCmdUI);
    afx_msg void OnUpdateStart(CCmdUI* pCmdUI);
    afx_msg void OnUpdateGetandactive(CCmdUI* pCmdUI);
    afx_msg void OnUcStart();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

#endif // !defined(AFX_JLKITVIEW_H__2A3B3EDF_5BC0_49E0_8991_A0C7672EA797__INCLUDED_)
