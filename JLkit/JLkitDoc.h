#if !defined(AFX_JLKITDOC_H__9C9AD6C5_69D3_45CF_A1E2_27114BFE567F__INCLUDED_)
#define AFX_JLKITDOC_H__9C9AD6C5_69D3_45CF_A1E2_27114BFE567F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// JLkitDoc.h : header file
//


#include "..\common\common.h"
#include "..\common\protocol.h"
#include "..\common\ShareMem.h"

/////////////////////////////////////////////////////////////////////////////
// CJLkitDoc document

class CWaitDlg;
class CDlgKeyView;
class CDlgLogin;
class CJLkitSocket;
class CThreadPool;
class CLock;
class CCVPNFile;
class CJob;
class CJLkitDoc : public CDocument
{
protected:
    CJLkitDoc();           // protected constructor used by dynamic creation
    DECLARE_DYNCREATE(CJLkitDoc)

// Attributes
public:
    //设置
    BOOL m_KeepPw;  //保存密码
    TCHAR m_szFileName[MAX_PATH];
    TCHAR m_szGamePath[MAX_PATH];
    TCHAR m_szAccountName[MAX_PATH];
    TCHAR m_szAccountPw[MAX_PATH];

    //对话框
    CStdioFile errfile;
    ShareMem m_share;
    std::vector<QUERYKEY_RET_BUF> m_KeyVec;

    int LaunchGame(const CString& strName, const CString& strPw,
                   const CString& strConfig, const CString& strScript, BOOL bProfile = FALSE);

    CDlgKeyView* m_pKeyDlg;
    CDlgLogin* m_pLoginDlg;
    CJLkitSocket* m_pSocket;
    CLock* m_lpLock;
    CThreadPool* m_lpTPool;
    CCVPNFile* m_lpVpnFile;
    CJob* m_pJob;


    int Active(CString& strName, CString& strPw);
    int Get(CString& strName, CString& strPw);
    void GetandActive();

// Operations
public:
    void GetGamePath();
    void ProcessRecevice();
    void ConnectResult(int nErrorCode);
    BOOL IsHaveValidKey();


// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CJLkitDoc)
public:
    virtual void Serialize(CArchive& ar);   // overridden for document i/o
    virtual void OnCloseDocument();
    virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
    virtual void DeleteContents();
protected:
    virtual BOOL OnNewDocument();
    //}}AFX_VIRTUAL

// Implementation
public:
    virtual ~CJLkitDoc();
#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump(CDumpContext& dc) const;
#endif

    // Generated message map functions
protected:
    //{{AFX_MSG(CJLkitDoc)
    // NOTE - the ClassWizard will add and remove member functions here.
    afx_msg void OnLookkey();
    afx_msg void OnLookShareMem();
    afx_msg void OnSetting();
    afx_msg void OnUpdateValidKey(CCmdUI* pCmdUI);
    afx_msg void OnUpdateLoginedNums(CCmdUI* pCmdUI);
    afx_msg void OnUpdateAllNums(CCmdUI* pCmdUI);
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_JLKITDOC_H__9C9AD6C5_69D3_45CF_A1E2_27114BFE567F__INCLUDED_)
