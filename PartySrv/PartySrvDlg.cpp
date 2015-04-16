// PartySrvDlg.cpp : implementation file
//

#include "stdafx.h"
#include "PartySrv.h"
#include "PartySrvDlg.h"

#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
    CAboutDlg();

// Dialog Data
    //{{AFX_DATA(CAboutDlg)
    enum { IDD = IDD_ABOUTBOX };
    //}}AFX_DATA

    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CAboutDlg)
protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL

// Implementation
protected:
    //{{AFX_MSG(CAboutDlg)
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
    //{{AFX_DATA_INIT(CAboutDlg)
    //}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CAboutDlg)
    //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
    //{{AFX_MSG_MAP(CAboutDlg)
    // No message handlers
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPartySrvDlg dialog

CPartySrvDlg::CPartySrvDlg(CWnd* pParent /*=NULL*/)
    : CDialog(CPartySrvDlg::IDD, pParent)
{
    //{{AFX_DATA_INIT(CPartySrvDlg)
    // NOTE: the ClassWizard will add member initialization here
    //}}AFX_DATA_INIT
    // Note that LoadIcon does not require a subsequent DestroyIcon in Win32
    m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CPartySrvDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CPartySrvDlg)
    DDX_Control(pDX, IDC_LIST1, m_ListCtrl);
    //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CPartySrvDlg, CDialog)
    //{{AFX_MSG_MAP(CPartySrvDlg)
    ON_WM_SYSCOMMAND()
    ON_WM_PAINT()
    ON_WM_QUERYDRAGICON()
    ON_WM_TIMER()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPartySrvDlg message handlers

BOOL CPartySrvDlg::OnInitDialog()
{
    CDialog::OnInitDialog();

    // Add "About..." menu item to system menu.

    // IDM_ABOUTBOX must be in the system command range.
    ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
    ASSERT(IDM_ABOUTBOX < 0xF000);

    CMenu* pSysMenu = GetSystemMenu(FALSE);
    if(pSysMenu != NULL)
    {
        CString strAboutMenu;
        strAboutMenu.LoadString(IDS_ABOUTBOX);
        if(!strAboutMenu.IsEmpty())
        {
            pSysMenu->AppendMenu(MF_SEPARATOR);
            pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
        }
    }

    // Set the icon for this dialog.  The framework does this automatically
    //  when the application's main window is not a dialog
    SetIcon(m_hIcon, TRUE);         // Set big icon
    SetIcon(m_hIcon, FALSE);        // Set small icon

    //进入监听
    if(!m_listen.Create(4567))
    {
        AfxMessageBox(_T("创建套接字失败\n"));
    }

    if(!m_listen.Listen())
    {
        AfxMessageBox(_T("监听失败!\n"));
    }

    m_ListCtrl.InsertColumn(0, _T("玩家ID"));
    m_ListCtrl.InsertColumn(1, _T("地图ID"));
    m_ListCtrl.InsertColumn(2, _T("坐标"));

    for(int i = 0; i < 3; i++)
    {
        m_ListCtrl.SetColumnWidth(i, LVSCW_AUTOSIZE_USEHEADER);
    }


    m_ListCtrl.SetExtendedStyle(LVS_EX_FULLROWSELECT);

    //设置定时器, 驱动服务器没段时间匹配一次队伍
    SetTimer(IDT_PIPEI, 5000, NULL);


    return TRUE;  // return TRUE  unless you set the focus to a control
}

void CPartySrvDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
    if((nID & 0xFFF0) == IDM_ABOUTBOX)
    {
        CAboutDlg dlgAbout;
        dlgAbout.DoModal();
    }
    else
    {
        CDialog::OnSysCommand(nID, lParam);
    }
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CPartySrvDlg::OnPaint()
{
    if(IsIconic())
    {
        CPaintDC dc(this); // device context for painting

        SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

        // Center icon in client rectangle
        int cxIcon = GetSystemMetrics(SM_CXICON);
        int cyIcon = GetSystemMetrics(SM_CYICON);
        CRect rect;
        GetClientRect(&rect);
        int x = (rect.Width() - cxIcon + 1) / 2;
        int y = (rect.Height() - cyIcon + 1) / 2;

        // Draw the icon
        dc.DrawIcon(x, y, m_hIcon);
    }
    else
    {
        CDialog::OnPaint();
    }
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CPartySrvDlg::OnQueryDragIcon()
{
    return (HCURSOR) m_hIcon;
}

bool CPartySrvDlg::OnEventTCPSocketLink(CJLkitSocket* pSocket, INT nErrorCode)
{
    return true;
}

bool CPartySrvDlg::OnEventTCPSocketShut(CJLkitSocket* pSocket, BYTE cbShutReason)
{
    TRACE(_T("处理消息"));
    DelRequest(pSocket);
    TRACE(_T("处理完成"));
    return true;
}

void CPartySrvDlg::AddPalyerToList(CJLkitSocket* pSocket)
{
    PartyPlayer& pPlayer = m_PlayerReq[pSocket];

    CString strTemp;
    strTemp.Format(_T("%d"), pPlayer.pid);
    m_ListCtrl.InsertItem(0, strTemp);

    strTemp.Format(_T("%d"), pPlayer.mid);
    m_ListCtrl.SetItemText(0, 1, strTemp);

    strTemp.Format(_T("%d-%d-%d"), (int)pPlayer.pos.x, (int)pPlayer.pos.y, (int)pPlayer.pos.z);
    m_ListCtrl.SetItemText(0, 2, strTemp);

    m_ListCtrl.SetItemData(0, (DWORD)pSocket);

}

bool CPartySrvDlg::OnEventTCPSocketRead(CJLkitSocket* pSocket, const Tcp_Head& stTcpHead, void* pData, WORD wDataSize)
{

    if(stTcpHead.wMainCmdID == M_ADDPARTY)
    {

        switch(stTcpHead.wSubCmdID)
        {
            case fun_group_find:
            {
                PartyPlayer* pParty = (PartyPlayer*)pData;
                AddRequest(pSocket, *pParty);
                SearchGroup();
                break;
            }

            default:
                break;
        }


    }

    return true;
}

void CPartySrvDlg::DelPalyerFromList(CJLkitSocket* pSocket)
{
    for(int i = 0; i < m_ListCtrl.GetItemCount(); i++)
    {
        if(m_ListCtrl.GetItemData(i) == (DWORD)pSocket)
        {
            m_ListCtrl.DeleteItem(i);
            break;
        }
    }

}

//匹配一个player的组队
BOOL CPartySrvDlg::MatchGroup(RequestMap::iterator& tarit, GroupVec& ItVec)
{

    ItVec.clear();

    for(RequestMap::iterator it = m_PlayerReq.begin(); it != m_PlayerReq.end(); it++)
    {
        //仅仅地图内组队
        if(tarit->second.flag == ONLY_MAP)
        {
            if(it->second.mid == tarit->second.mid)
            {
                ItVec.push_back(it->first);
                if(ItVec.size() >= 6) return TRUE;
            }
        }
        else if(tarit->second.flag == ONLY_RANGE)
        {
            //范围内组队
        }
        else if(tarit->second.flag == SAME_TASKID)
        {
            if(it->second.taskid == tarit->second.taskid)
            {
                ItVec.push_back(it->first);
                if(ItVec.size() >= 6) return TRUE;
            }
        }
    }

    return FALSE;
}

//通知完成组队
void CPartySrvDlg::NotifyGroupComplete(GroupVec& VecIt)
{

    PartyRequest req;

    req.pid1 = m_PlayerReq[VecIt[0]].pid;
    req.pid2 = m_PlayerReq[VecIt[1]].pid;
    req.pid3 = m_PlayerReq[VecIt[2]].pid;
    req.pid4 = m_PlayerReq[VecIt[3]].pid;
    req.pid5 = m_PlayerReq[VecIt[4]].pid;
    req.pid6 = m_PlayerReq[VecIt[5]].pid;

    CJLkitSocket* pSocket = (CJLkitSocket*)VecIt[0];
    _ASSERTE(pSocket != NULL);

    pSocket->Send(M_ADDPARTY, fun_group_caption, &req, sizeof(PartyRequest));


    //控件
    for(int i = 0; i < VecIt.size(); i++)
    {
        DelRequest(VecIt[i]);
    }
}


//匹配队伍, 用计时器驱动
void CPartySrvDlg::SearchGroup()
{
    GroupVec ItVec;

    //从当前请求列表匹配
    for(RequestMap::iterator it = m_PlayerReq.begin(); it != m_PlayerReq.end(); it++)
    {
        if(MatchGroup(it, ItVec))
        {
            NotifyGroupComplete(ItVec);
            break;
        }
    }

}


void CPartySrvDlg::OnTimer(UINT nIDEvent)
{
    if(nIDEvent == IDT_PIPEI)
    {
        //SearchGroup();
    }

    CDialog::OnTimer(nIDEvent);
}

BOOL CPartySrvDlg::DelRequest(CJLkitSocket* pSocket)
{
    DelPalyerFromList(pSocket);

    int size = m_PlayerReq.size();
    m_PlayerReq.erase(pSocket);
    _ASSERTE(size > m_PlayerReq.size());

    SafeDelete(pSocket);

    return TRUE;
}

BOOL CPartySrvDlg::AddRequest(CJLkitSocket* pSocket, PartyPlayer& stParty)
{

    m_PlayerReq[pSocket] = stParty;

    AddPalyerToList(pSocket);

    return TRUE;
}