#if !defined(AFX_JLKITDOC_H__9C9AD6C5_69D3_45CF_A1E2_27114BFE567F__INCLUDED_)
#define AFX_JLKITDOC_H__9C9AD6C5_69D3_45CF_A1E2_27114BFE567F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000



#include "..\common\common.h"
#include "..\common\protocol.h"
#include "..\common\ShareMem.h"



class CDlgKeyView;
class CWaitDlg;
class CDlgLogin;
class CLock;
class CVpnFile;
class CJob;
class CJLkitDoc : public CDocument
{
protected:
    CJLkitDoc();           // protected constructor used by dynamic creation
    virtual ~CJLkitDoc();
    DECLARE_DYNCREATE(CJLkitDoc)

    //错误文件
public:
    CStdioFile errfile;

    //当前卡号
    static KeyVec m_KeyVec;

    //游戏控制
    int LaunchGame(CString& strName, CString& strPw, CString& strConfig,
                   CString& strScript, BOOL bProfile = FALSE);  //加载游戏
    //创建游戏进程
    int CreateGameProcess(CString& strName, CString& strPw, BOOL bProfile,
                          PROCESS_INFORMATION* lppi);

    //对话框
    CDlgLogin* m_pLoginDlg;
    CDlgKeyView* m_pKeyDlg;

    //关键段锁
    CLock* m_lpLock;

    //拨号vpn
    CVpnFile* m_lpVpnFile;

    //领取激活
    int Active(CString& strName, CString& strPw);  //激活
    int Get(CString& strName, CString& strPw);  //领取
    void GetandActive();                        //领取再激活

    //处理套接字
    void ProcessRecevice();

    //连接结果
    void ConnectResult(int nErrorCode);

    //是否剩余有效KEY
    BOOL IsHaveValidKey();



    //重写
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CJLkitDoc)
	public:
    virtual void Serialize(CArchive& ar);   // overridden for document i/o
    virtual void OnCloseDocument();
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	protected:
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
    // NOTE - the ClassWizard will add and remove member functions here.
    afx_msg void OnLookkey();
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
