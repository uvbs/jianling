#if !defined(AFX_JLKITDOC_H__9C9AD6C5_69D3_45CF_A1E2_27114BFE567F__INCLUDED_)
#define AFX_JLKITDOC_H__9C9AD6C5_69D3_45CF_A1E2_27114BFE567F__INCLUDED_

#if _MSC_VER > 1000
    #pragma once
#endif // _MSC_VER > 1000



#include "Logindlg.h"
#include "Registdlg.h"
#include "Modifybind.h"
#include "Keyviewdlg.h"
#include "JLkitSocket.h"
#include "BindKeyDlg.h"
#include "MsgBox.h"
#include "StatusBox.h"



class CJLkitDoc : public CDocument, public ITCPSocketSink
{
protected:
    CJLkitDoc();           // protected constructor used by dynamic creation
    virtual ~CJLkitDoc();
    DECLARE_DYNCREATE(CJLkitDoc)

public:

    //领取激活
    int Active(CString& strName, CString& strPw);   //激活
    int Get(CString& strName, CString& strPw);      //领取


    //是否剩余有效KEY
    BOOL IsHaveValidKey();


    //登陆部分
    void ShowLogin();
    void ShowRegister();
    void ShowModiBind();
    bool PerformLogonMission();

    void ShowStatus(TCHAR szText[]);
    void ShowMsg(TCHAR szText[]);


    //对话框
    CDlgKeyView* m_pKeyDlg;
    CDlgLogin* m_pLoginDlg;
    CDlgRegist* m_pRegisterDlg;
    CDlgModifyBind* m_pModiBind;
    CDlgBindKey* m_pBindDlg;

    CMsgBox* m_pMsgBox;
    CStatusBox* m_pStatusBox;

    //网络套接字
    CJLkitSocket m_socket;


    bool m_bModiBind;
    bool m_bRegister;

    //网络回调
public:
    virtual bool OnEventTCPSocketLink(CJLkitSocket* pSocket, INT nErrorCode);
    virtual bool OnEventTCPSocketShut(CJLkitSocket* pSocket, BYTE cbShutReason);
    virtual bool OnEventTCPSocketRead(CJLkitSocket* pSocket, const Tcp_Head& stTcpHead, VOID* pData, WORD wDataSize);


    //处理网络数据
    void ProcessLogin(CJLkitSocket* pSocket, const Tcp_Head& stTcpHead, void* pData, WORD wDataSize);
    void ProcessKey(CJLkitSocket* pSocket, const Tcp_Head& stTcpHead, void* pData, WORD wDataSize);
    void ProcessHelp(CJLkitSocket* pSocket, const Tcp_Head& stTcpHead, void* pData, WORD wDataSize);


    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CJLkitDoc)
public:
    virtual void Serialize(CArchive& ar);   // overridden for document i/o
    virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
    virtual void OnCloseDocument();
    virtual BOOL OnNewDocument();
    virtual void OnIdle();
    //}}AFX_VIRTUAL


#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump(CDumpContext& dc) const;
#endif

    // Generated message map functions
protected:
    //{{AFX_MSG(CJLkitDoc)
    afx_msg void OnSetting();
    afx_msg void OnUpdateValidKey(CCmdUI* pCmdUI);
    afx_msg void OnUpdateLoginedNums(CCmdUI* pCmdUI);
    afx_msg void OnUpdateAllNums(CCmdUI* pCmdUI);
    afx_msg void OnLookkey();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_JLKITDOC_H__9C9AD6C5_69D3_45CF_A1E2_27114BFE567F__INCLUDED_)
