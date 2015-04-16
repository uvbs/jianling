#if !defined(AFX_TEST_H__93341652_9CF8_49EA_829F_5934C44F7F07__INCLUDED_)
#define AFX_TEST_H__93341652_9CF8_49EA_829F_5934C44F7F07__INCLUDED_

#if _MSC_VER > 1000
    #pragma once
#endif // _MSC_VER > 1000
// Test.h : header file
//

#include "resource.h"

#include "..\JLkit\JLkitSocket.h"


/////////////////////////////////////////////////////////////////////////////
// Test dialog

class Test : public CDialog, public ITCPSocketSink
{
// Construction
public:
    Test(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
    //{{AFX_DATA(Test)
    enum { IDD = IDD_DIALOG1 };
    // NOTE: the ClassWizard will add data members here
    //}}AFX_DATA

private:
    CJLkitSocket sock ;


    bool OnEventTCPSocketLink(CJLkitSocket* pSocket, INT nErrorCode)
    {

        if(nErrorCode == 0)
        {

            PartyPlayer player;
            player.flag = ONLY_MAP;
            player.mid = 123;
            player.pid = 234;
            player.pos.x = 100;
            player.pos.y = 200;
            player.pos.z = 300;


            sock.Send(M_ADDPARTY, fun_group_find, &player, sizeof(PartyPlayer));
        }
        else
        {
            TRACE(_T("连接服务器失败"));
        }


        return true;
    }
    bool OnEventTCPSocketShut(CJLkitSocket* pSocket, BYTE cbShutReason)
    {
        return true;
    }

    bool OnEventTCPSocketRead(CJLkitSocket* pSocket, const Tcp_Head& stTcpHead, void* pData, WORD wDataSize)
    {
        if(stTcpHead.wMainCmdID == M_ADDPARTY)
        {
            if(stTcpHead.wSubCmdID != fun_group_fail)
            {
                if(stTcpHead.wSubCmdID == fun_group_caption)
                {
                    TRACE(_T("你是队长!\n"));
                }

                PartyRequest* pRequest = (PartyRequest*)pData;
                TRACE(_T("收到组队列表"));
                TRACE(_T("%d, %d, %d, %d, %d"),
                      pRequest->pid1,
                      pRequest->pid2,
                      pRequest->pid3,
                      pRequest->pid4,
                      pRequest->pid5);

                //调用组队
                for(int i = 0; i < 5; i++)
                {
                    //InvitePlayer(i);
                }

            }
        }
        return true;
    }


// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(Test)
protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL

// Implementation
protected:

    // Generated message map functions
    //{{AFX_MSG(Test)
    virtual void OnOK();
    virtual BOOL OnInitDialog();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TEST_H__93341652_9CF8_49EA_829F_5934C44F7F07__INCLUDED_)
