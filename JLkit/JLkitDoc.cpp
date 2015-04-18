#include "stdafx.h"
#include "JLkit.h"
#include "JLkitDoc.h"
#include "JLkitView.h"
#include "MainFrm.h"
#include "Settingdlg.h"
#include "BugRepDlg.h"
#include "ConfigMgr.h"
#include "MsgBox.h"
#include "GlobalUserInfo.h"
#include "WorkThread.h"



#ifdef _DEBUG
    #define new DEBUG_NEW
#endif


/////////////////////////////////////////////////////////////////////////////
// CJLkitDoc
IMPLEMENT_DYNCREATE(CJLkitDoc, CDocument)

CJLkitDoc::CJLkitDoc()
{

    m_pModiBind = NULL;
    m_pRegisterDlg = NULL;
    m_pLoginDlg = NULL;
    m_pKeyDlg = NULL;
    m_pBindDlg = NULL;

    m_pMsgBox = NULL;
    m_pStatusBox = NULL;

    //设置回调
    m_socket.SetSink(this);


    m_bModiBind = false;
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
    pCmdUI->Enable(TRUE);


    CGlobalUserInfo* pGlobalUserInfo = CGlobalUserInfo::GetInstance();
    KeyVec& key = pGlobalUserInfo->m_KeyVec;


    CString strInfo;
    if(strInfo.LoadString(IDS_VALIDKEY))
    {
        CString strTemp;
        strTemp.Format(IDS_VALIDKEY, key.size());
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
    CConfigMgr* pConfig =  CConfigMgr::GetInstance();
    dlg.m_strGamePath = pConfig->m_szGamePath;
    if(dlg.DoModal() == IDOK)
    {
        //保存配置信息
        _tcscpy(pConfig->m_szGamePath, (LPCTSTR)dlg.m_strGamePath);
    }
}


//检查是否还有有效的KEY供打开一个游戏进程
//这里是一个KEY对应一个游戏进程
BOOL CJLkitDoc::IsHaveValidKey()
{
    CGlobalUserInfo* pGlobalUserInfo = CGlobalUserInfo::GetInstance();
    KeyVec& key = pGlobalUserInfo->m_KeyVec;
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

    CConfigMgr* pConfig = CConfigMgr::GetInstance();
    _tcscpy(pConfig->m_szFileName, lpszPathName);

    return TRUE;
}

void CJLkitDoc::OnCloseDocument()
{

    SafeDelete(m_pStatusBox);
    SafeDelete(m_pMsgBox);
    SafeDelete(m_pBindDlg);
    SafeDelete(m_pRegisterDlg);
    SafeDelete(m_pLoginDlg);
    SafeDelete(m_pModiBind);

    CDocument::OnCloseDocument();
}



void CJLkitDoc::ShowLogin()
{
    //创建登陆对话框
    if(!m_pLoginDlg)
    {
        m_pLoginDlg = new CDlgLogin();
    }


    m_bRegister = false;


    //获得配置
    CConfigMgr* pConfigMgr = CConfigMgr::GetInstance();

    //初始化登陆对话框
    m_pLoginDlg->m_bRemPw = pConfigMgr->m_KeepPw;
    if(m_pLoginDlg->m_bRemPw)
    {
        m_pLoginDlg->m_strPw = pConfigMgr->m_szAccountPw;
        m_pLoginDlg->m_strName = pConfigMgr->m_szAccountName;
    }

    if(m_pLoginDlg->m_hWnd == NULL)
    {
        //登陆对话框
        m_pLoginDlg->Create(CDlgLogin::IDD, AfxGetMainWnd());
    }

    m_pLoginDlg->ShowWindow(SW_SHOW);
}

void CJLkitDoc::ShowRegister()
{
    if(!m_pRegisterDlg)
    {
        m_pRegisterDlg = new CDlgRegist();
    }

    m_bRegister = true;
    m_pRegisterDlg->DoModal();
}


void CJLkitDoc::ShowModiBind()
{
    if(!m_pModiBind)
    {
        m_pModiBind = new CDlgModifyBind();
    }

    m_bModiBind = true;
    m_pModiBind->DoModal();
}

bool CJLkitDoc::PerformLogonMission()
{

    ShowStatus(_T("连接服务器中..."));

    CString strSrvIp;
    _ASSERTE(strSrvIp.LoadString(IDS_CONNECT_SERVER) == TRUE);

    if(!m_socket.ConnectSrv(strSrvIp, PORT_SRV))
    {
        ShowMsg(_T("连接服务器失败"));
        return false;
    }

    Sleep(100);
    return true;
}


//连接事件
bool CJLkitDoc::OnEventTCPSocketLink(CJLkitSocket* pSocket, INT nErrorCode)
{

    if(nErrorCode != 0)
    {
        ShowMsg(_T("连接服务器失败"));
        ShowLogin();
    }
    else
    {
        ShowStatus(NULL);

        //完成链接, 开始发送登陆数据
        BYTE cbBuffer[SOCKET_TCP_PACKET];
        WORD wPacketSize;
        int funid;
        if(m_bModiBind)
        {
            wPacketSize = m_pModiBind->ConstructModifyBindPacket(cbBuffer, sizeof(cbBuffer));
            funid = fun_bindkey;
        }
        else if(m_bRegister)
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
bool CJLkitDoc::OnEventTCPSocketShut(CJLkitSocket* pSocket, BYTE cbShutReason)
{


    return true;
}

void CJLkitDoc::ProcessLogin(CJLkitSocket* pSocket, const Tcp_Head& stTcpHead, void* pData, WORD wDataSize)
{
    switch(stTcpHead.wSubCmdID)
    {

        case fun_login_fail:
        {
            PROCESS_DESCRIBE* pLoginFail = (PROCESS_DESCRIBE*)pData;

            m_socket.CloseSocket();

            AfxMessageBox(pLoginFail->szDescribe);

            if(m_bRegister == false)
            {
                ShowLogin();
            }
            else if(m_bModiBind == true)
            {
                ShowModiBind();
            }
            else
            {
                ShowRegister();
            }

            break;
        }

        case fun_login_ok:
        {
            LOGIN_SUCCESS* pLoginSucess = (LOGIN_SUCCESS*)pData;
            m_socket.Send(M_KEY, fun_querykey, NULL, 0);

            //自动加载上次打开的文件
            CConfigMgr* pConfig = CConfigMgr::GetInstance();

            if(pConfig->m_szFileName[0] != _T('\0'))
            {
                AfxGetApp()->m_nCmdShow = SW_HIDE;
                AfxGetApp()->OpenDocumentFile(pConfig->m_szFileName);
            }

            //显示主窗口
            ((CMainFrame*)AfxGetMainWnd())->ActivateFrame();
            break;
        }

    }
}

void CJLkitDoc::ProcessKey(CJLkitSocket* pSocket, const Tcp_Head& stTcpHead, void* pData, WORD wDataSize)
{
    switch(stTcpHead.wSubCmdID)
    {
        case fun_bindkey_fail:
        {
            PROCESS_DESCRIBE* pDesc = (PROCESS_DESCRIBE*)pData;
            AfxMessageBox(pDesc->szDescribe);
            break;
        }

        case fun_bindkey_ok:
        {
            if(m_pBindDlg)
            {
                m_pBindDlg->EndDialog(IDOK);
            }

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

            //获取用户KEY
            CGlobalUserInfo* pUserInfo = CGlobalUserInfo::GetInstance();
            KeyVec& key =  pUserInfo->m_KeyVec;;

            QUERYKEY_SUCCESS* pKey = (QUERYKEY_SUCCESS*)pData;

            //用户层的Recv应该保证收到的都是完整的数据
            //下面判断小于包的语句可以省略吧

            key.clear();
            for(int i = 0; ; i++, pKey++)
            {

                //此处可以省略?
                if(wDataSize < sizeof(QUERYKEY_SUCCESS))
                    break;

                //放到用户全局数据中
                key.push_back(*pKey);

                wDataSize -= sizeof(QUERYKEY_SUCCESS);
            }

            break;
        }

        case fun_querykey_fail:
        {
            if(m_pKeyDlg)
            {
                CListCtrl& listctr = m_pKeyDlg->m_ListCtrl;
                listctr.DeleteAllItems();

                listctr.InsertItem(0, _T("查询失败"));

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
        m_pKeyDlg = new CDlgKeyView();


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

    if(m_pMsgBox == NULL)
        m_pMsgBox = new CMsgBox;

    m_pMsgBox->SetMsg(szText);
    m_pMsgBox->DoModal();
}