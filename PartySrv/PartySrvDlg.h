// PartySrvDlg.h : header file
//

#if !defined(AFX_PARTYSRVDLG_H__C2B3CDDB_4DEB_46B0_9027_D6DE27345959__INCLUDED_)
#define AFX_PARTYSRVDLG_H__C2B3CDDB_4DEB_46B0_9027_D6DE27345959__INCLUDED_

#if _MSC_VER > 1000
    #pragma once
#endif // _MSC_VER > 1000

#include "ListenSock.h"
#include "..\JLkit\JLkitSocket.h"

/////////////////////////////////////////////////////////////////////////////
// CPartySrvDlg dialog

class CPartySrvDlg : public CDialog, public ITCPSocketSink
{
// Construction
public:
    CPartySrvDlg(CWnd* pParent = NULL); // standard constructor

// Dialog Data
    //{{AFX_DATA(CPartySrvDlg)
    enum { IDD = IDD_PARTYSRV_DIALOG };
    CListCtrl   m_ListCtrl;
    //}}AFX_DATA

    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CPartySrvDlg)
protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL


    //当前等待排队玩家
private:


    //所有等待组队的列表
    typedef std::map<CJLkitSocket*, PartyPlayer> RequestMap;
    RequestMap m_PlayerReq;

    typedef std::vector<CJLkitSocket*> GroupVec;

private:
    CListenSock m_listen;

    //加入一个组队玩家到列表框
    void AddPalyerToList(CJLkitSocket* pPlayer);
    void DelPalyerFromList(CJLkitSocket* pSocket);


    //向队伍中的某个玩家发送组队
    void NotifyGroupComplete(GroupVec& VecIt);

    //从当前所有请求列表匹配队伍
    void SearchGroup();

    //按照一个玩家的请求匹配队伍
    BOOL MatchGroup(RequestMap::iterator& tarit, GroupVec& ItVec);

    BOOL AddRequest(CJLkitSocket* pSocket, PartyPlayer &stParty);
    BOOL DelRequest(CJLkitSocket* pSocket);

    //网络消息回调
    //网络事件
public:
    virtual bool OnEventTCPSocketLink(CJLkitSocket* pSocket, INT nErrorCode);
    virtual bool OnEventTCPSocketShut(CJLkitSocket* pSocket, BYTE cbShutReason);
    virtual bool OnEventTCPSocketRead(CJLkitSocket* pSocket, const Tcp_Head& stTcpHead, void* pData, WORD wDataSize);


// Implementation
protected:
    HICON m_hIcon;

    // Generated message map functions
    //{{AFX_MSG(CPartySrvDlg)
    virtual BOOL OnInitDialog();
    afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
    afx_msg void OnPaint();
    afx_msg HCURSOR OnQueryDragIcon();
    afx_msg void OnTimer(UINT nIDEvent);
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PARTYSRVDLG_H__C2B3CDDB_4DEB_46B0_9027_D6DE27345959__INCLUDED_)
