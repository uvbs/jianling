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

    //�����ļ�
public:
    CStdioFile errfile;

    //��ǰ����
    static KeyVec m_KeyVec;

    //��Ϸ����
    int LaunchGame(CString& strName, CString& strPw, CString& strConfig,
                   CString& strScript, BOOL bProfile = FALSE);  //������Ϸ
    //������Ϸ����
    int CreateGameProcess(CString& strName, CString& strPw, BOOL bProfile,
                          PROCESS_INFORMATION* lppi);

    //�Ի���
    CDlgLogin* m_pLoginDlg;
    CDlgKeyView* m_pKeyDlg;

    //�ؼ�����
    CLock* m_lpLock;

    //����vpn
    CVpnFile* m_lpVpnFile;

    //��ȡ����
    int Active(CString& strName, CString& strPw);  //����
    int Get(CString& strName, CString& strPw);  //��ȡ
    void GetandActive();                        //��ȡ�ټ���

    //�����׽���
    void ProcessRecevice();

    //���ӽ��
    void ConnectResult(int nErrorCode);

    //�Ƿ�ʣ����ЧKEY
    BOOL IsHaveValidKey();



    //��д
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
