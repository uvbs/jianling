#include "stdafx.h"
#include "JLkit.h"
#include "JLkitDoc.h"
#include "JLkitView.h"
#include "MainFrm.h"
#include "Settingdlg.h"
#include "ConfigMgr.h"
#include "MsgBox.h"
#include "LoginSheet.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


/////////////////////////////////////////////////////////////////////////////
// CJLkitDoc
IMPLEMENT_DYNCREATE(CJLkitDoc, CDocument)

CJLkitDoc::CJLkitDoc():
    m_LoginSheet(AfxGetApp()->m_pszAppName)
{

    m_pRegisterDlg = NULL;
    m_pLoginDlg = NULL;
    m_pKeyDlg = NULL;

    m_pStatusBox = NULL;

    m_bRegister = false;
}


BOOL CJLkitDoc::OnNewDocument()
{
    if(!CDocument::OnNewDocument())
        return FALSE;

    ShowLogin();
    return TRUE;
}

CJLkitDoc::~CJLkitDoc()
{
}


BEGIN_MESSAGE_MAP(CJLkitDoc, CDocument)
    //{{AFX_MSG_MAP(CJLkitDoc)
    ON_COMMAND(ID_SETTING, OnSetting)
    ON_UPDATE_COMMAND_UI(ID_INDICATOR_VALIDKEY, OnUpdateValidKey)
    ON_UPDATE_COMMAND_UI(ID_INDICATOR_LOGINED, OnUpdateLoginedNums)
    ON_UPDATE_COMMAND_UI(ID_INDICATOR_ALLNUMS, OnUpdateAllNums)
    ON_COMMAND(ID_LOOKKEY, OnLookkey)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CJLkitDoc diagnostics

#ifdef _DEBUG
void CJLkitDoc::AssertValid() const
{
    CDocument::AssertValid();
}

void CJLkitDoc::Dump(CDumpContext& dc) const
{
    CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CJLkitDoc serialization

void CJLkitDoc::Serialize(CArchive& ar)
{
    ((CJLkitView*)m_viewList.GetHead())->SerializeText(ar);
}

/////////////////////////////////////////////////////////////////////////////
// CJLkitDoc commands



void CJLkitDoc::OnUpdateValidKey(CCmdUI* pCmdUI)
{

    CString strInfo;
    if(strInfo.LoadString(IDS_VALIDKEY))
    {
        CString strTemp;
        strTemp.Format(IDS_VALIDKEY, m_KeyVec.size());
        pCmdUI->SetText(strTemp);
    }
}

void CJLkitDoc::OnUpdateLoginedNums(CCmdUI* pCmdUI)
{
}

void CJLkitDoc::OnUpdateAllNums(CCmdUI* pCmdUI)
{
}


void CJLkitDoc::OnSetting()
{
    CDlgSetting dlg;

    dlg.m_strGamePath = CConfigMgr::GetInstance()->m_szGamePath.c_str();
    if(dlg.DoModal() == IDOK)
    {
        //保存配置信息
        CConfigMgr::GetInstance()->m_szGamePath = dlg.m_strGamePath;
    }
}


//检查是否还有有效的KEY供打开一个游戏进程
//这里是一个KEY对应一个游戏进程
BOOL CJLkitDoc::IsHaveValidKey()
{

    return TRUE;
}



int CJLkitDoc::Get(CString& strName, CString& strPw)
{
    Webpost poster(strName, strPw);
    int nRet = poster.Login();
    if(nRet == RESULT_SUCCESS)
    {
        nRet = poster.Get();
        return nRet;
    }
    else
    {
        return nRet;
    }
}


int CJLkitDoc::Active(CString& strName, CString& strPw)
{
    Webpost poster(strName, strPw);
    int nRet = poster.Login();
    if(nRet == RESULT_SUCCESS)
    {
        nRet = poster.Active();
    }

    return nRet;
}

void CJLkitDoc::OnIdle()
{
}

BOOL CJLkitDoc::OnOpenDocument(LPCTSTR lpszPathName)
{
    if(!CDocument::OnOpenDocument(lpszPathName)) return FALSE;

    CConfigMgr::GetInstance()->m_szFileName = lpszPathName;
    return TRUE;
}

void CJLkitDoc::OnCloseDocument()
{

    SafeDelete(m_pStatusBox);
    SafeDelete(m_pRegisterDlg);
    SafeDelete(m_pLoginDlg);

    CDocument::OnCloseDocument();
}



void CJLkitDoc::ShowLogin()
{
    //创建登陆对话框
    if(!m_pLoginDlg)
    {
        m_pLoginDlg = new CDlgLogin();
    }

    if(!m_pRegisterDlg)
    {
        m_pRegisterDlg = new CDlgRegist();
    }

    m_bRegister = false;

    if(m_LoginSheet.m_hWnd == NULL)
    {
        m_LoginSheet.AddPage(m_pLoginDlg);
        m_LoginSheet.AddPage(m_pRegisterDlg);
        m_LoginSheet.Create(NULL, WS_OVERLAPPED | WS_SYSMENU);
    }

    m_LoginSheet.ShowWindow(SW_SHOW);
}

bool CJLkitDoc::PerformLogonMission()
{
    ShowStatus(_T("正在连接服务器.."));

    CString strSrvIp;
    VERIFY(strSrvIp.LoadString(IDS_CONNECT_SERVER) == TRUE);

    //设置回调
    m_socket.SetSink(this);

    if(!m_socket.ConnectSrv(strSrvIp, PORT_SRV))
    {
        ShowMsg(_T("连接服务器失败"));
        ShowLogin();
        return false;
    }


    AfxGetMainWnd()->SetTimer(IDT_HEART, 15000, NULL);

    return true;
}


//连接事件
bool CJLkitDoc::OnEventTCPSocketLink(CJLkitSocket* pSocket, INT nErrorCode)
{

    if(nErrorCode != 0)
    {
        ShowMsg(_T("连接服务器失败"));
        m_socket.Close();
        ShowLogin();
    }
    else
    {
        ShowStatus(_T("正在登陆.."));

        //完成链接, 开始发送登陆数据
        BYTE cbBuffer[SOCKET_TCP_PACKET];
        WORD wPacketSize;
        int funid;

        if(m_bRegister)
        {
            wPacketSize = m_pRegisterDlg->ConstructRegisterPacket(cbBuffer, sizeof(cbBuffer));
            funid = fun_regist;
        }
        else
        {
            wPacketSize = m_pLoginDlg->ConstructLoginPacket(cbBuffer, sizeof(cbBuffer));
            funid = fun_login;
        }

        m_socket.Send(M_LOGIN, funid, cbBuffer, wPacketSize);
    }

    return true;
}


//关闭事件
bool CJLkitDoc::OnEventTCPSocketShut(CJLkitSocket* pSocket, INT nErrorCode)
{

    pSocket->Close();
    return true;
}

void CJLkitDoc::ProcessLogin(CJLkitSocket* pSocket, const Tcp_Head& stTcpHead, void* pData, WORD wDataSize)
{
    switch(stTcpHead.wSubCmdID)
    {

    case fun_login_fail:
        {
            PROCESS_DESCRIBE* pDes = (PROCESS_DESCRIBE*)pData;
            m_socket.Close();
            ShowLogin();
            AfxMessageBox(pDes->szDescribe);
            break;
        }

    case fun_login_ok:
        {
            
            ShowStatus(NULL);

            //自动加载上次打开的文件
            if(CConfigMgr::GetInstance()->m_szFileName[0] != _T('\0'))
            {
                AfxGetApp()->OpenDocumentFile(CConfigMgr::GetInstance()->m_szFileName.c_str());
            }

            //显示主窗口
            ((CMainFrame*)AfxGetMainWnd())->ActivateFrame();

            PROCESS_DESCRIBE* pLoginSucess = (PROCESS_DESCRIBE*)pData;
            m_socket.Send(M_KEY, fun_querykey, NULL, 0);

            break;
        }


    case fun_regist_ok:
    case fun_regist_fail:
        {
            PROCESS_DESCRIBE* pDes = (PROCESS_DESCRIBE*)pData;
            AfxMessageBox(pDes->szDescribe);
            m_socket.Close();
            break;
        }


    default:
        break;
    }
}

void CJLkitDoc::ProcessKey(CJLkitSocket* pSocket, const Tcp_Head& stTcpHead, void* pData, WORD wDataSize)
{
    switch(stTcpHead.wSubCmdID)
    {
    case fun_bindkey_fail:
    case fun_bindkey_ok:
        {
            PROCESS_DESCRIBE* pDesc = (PROCESS_DESCRIBE*)pData;
            AfxMessageBox(pDesc->szDescribe);
            break;
        }

    case fun_unbindkey_fail:
        {
            PROCESS_DESCRIBE* pDesc = (PROCESS_DESCRIBE*)pData;
            AfxMessageBox(pDesc->szDescribe);
            break;
        }

    case fun_unbindkey_ok:
        {
            //刷新对话框列表
            if(m_pKeyDlg)
            {

            }
            break;
        }

    case fun_querykey_ok:
        {

            QUERYKEY_SUCCESS* pKey = (QUERYKEY_SUCCESS*)pData;

            //放到用户全局数据中
            m_KeyVec.push_back(*pKey);
            break;
        }


    case fun_querykey_fail:
        {
            if(m_pKeyDlg)
            {
                CListCtrl& listctr = m_pKeyDlg->m_ListCtrl;
                listctr.DeleteAllItems();

            }
            break;
        }


    default:
        break;
    }
}

void CJLkitDoc::ProcessHelp(CJLkitSocket* pSocket, const Tcp_Head& stTcpHead, void* pData, WORD wDataSize)
{
    switch(stTcpHead.wSubCmdID)
    {
    case fun_bugrep_ok:
        {
            break;
        }

    case fun_bugrep_fail:
        {
            break;
        }
    }
}



//处理网络消息
bool CJLkitDoc::OnEventTCPSocketRead(CJLkitSocket* pSocket, const Tcp_Head& stTcpHead, VOID* pData, WORD wDataSize)
{

    switch(stTcpHead.wMainCmdID)
    {
    case M_LOGIN:
        ProcessLogin(pSocket, stTcpHead, pData, wDataSize);
        break;

    case M_KEY:
        ProcessKey(pSocket, stTcpHead, pData, wDataSize);
        break;

    case M_HELP:
        ProcessHelp(pSocket, stTcpHead, pData, wDataSize);
        break;

    default:
        break;
    }

    return true;
}


void CJLkitDoc::OnLookkey()
{

    if(m_pKeyDlg == NULL)
        m_pKeyDlg = new CDlgKey(AfxGetMainWnd());

    m_pKeyDlg->DoModal();
    SafeDelete(m_pKeyDlg);
}

void CJLkitDoc::ShowStatus(TCHAR szText[])
{

    if(m_pStatusBox == NULL)
        m_pStatusBox = new CStatusBox;

    if(m_pStatusBox->m_hWnd == NULL)
        m_pStatusBox->Create(CStatusBox::IDD);

    if(szText == NULL)
    {
        m_pStatusBox->ShowWindow(SW_HIDE);
        return;
    }

    m_pStatusBox->SetMsg(szText);
    m_pStatusBox->ShowWindow(SW_SHOW);
    m_pStatusBox->SetForegroundWindow();
}

void CJLkitDoc::ShowMsg(TCHAR szText[])
{
    _ASSERTE(szText != NULL);

    //隐藏状态提示
    m_pStatusBox->ShowWindow(SW_HIDE);

    CMsgBox dlg;
    dlg.SetMsg(szText);
    dlg.DoModal();
}