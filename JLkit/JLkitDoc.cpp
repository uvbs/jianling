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


#ifdef _DEBUG
    #define new DEBUG_NEW
#endif


/////////////////////////////////////////////////////////////////////////////
// CJLkitDoc
IMPLEMENT_DYNCREATE(CJLkitDoc, CDocument)

CJLkitDoc::CJLkitDoc()
{
    m_lpVpnFile = NULL;
    m_lpLock = NULL;


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
    if(!CDocument::OnNewDocument()) return FALSE;


    //初始化
    if(!m_lpVpnFile)
    {
        m_lpVpnFile = new CVpnFile;
    }

    if(!m_lpLock)
    {
        m_lpLock = new CLock;
    }

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
    pCmdUI->Enable(TRUE);
    CString strTemp;
    strTemp.Format(IDS_LOGINED, m_ShraeMem.GetUsedCount());
    pCmdUI->SetText(strTemp);
}

void CJLkitDoc::OnUpdateAllNums(CCmdUI* pCmdUI)
{
    pCmdUI->Enable(TRUE);
    CString strTemp;
    strTemp.Format(IDS_ALLNUMS, m_ShraeMem.GetAllCount());
    pCmdUI->SetText(strTemp);
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


    DWORD games = m_ShraeMem.GetUsedCount();
    if(games >= key.size())
    {
        return FALSE;
    }

    return TRUE;
}


void CJLkitDoc::GetandActive()
{
    //获取vpn文本
    TCHAR szPathName[MAX_PATH];
    GetModuleFileName(NULL, szPathName, MAX_PATH);
    PathRemoveFileSpec(szPathName);

    //工作目录
    SetCurrentDirectory(szPathName);
    PathAppend(szPathName, _T("VPN.txt"));

    //打开文本
    if(m_lpVpnFile->Open(szPathName))
    {
        AfxMessageBox(_T("无法打开代理文件"));
        return;
    }

    //取得当前模块路径
    TCHAR szPath[MAX_PATH] = {0};
    GetModuleFileName(NULL, szPath, MAX_PATH);

    CTime time = CTime::GetCurrentTime();
    CString strTime = time.Format("%d日%H时%M分");
    CreateDirectory(strTime, NULL);
    PathAppend(szPath, strTime);
    SetCurrentDirectory(szPath);

    m_ErrFile.Open(_T("错误帐号.txt"), CFile::modeReadWrite | CFile::modeCreate);


    CJLkitView* pView = (CJLkitView*)m_viewList.GetHead();
    CListCtrl& listctr = pView->GetListCtrl();

    //开始
    for(int i = 0; i < listctr.GetItemCount(); i++)
    {
        CString strName = listctr.GetItemText(i, COLUMN_TEXT_ACCOUNT);
        CString strPw = listctr.GetItemText(i, COLUMN_TEXT_PASSWORD);

        CString strLine = strName + _T(", ") + strPw + _T("\n");
        Webpost poster(strName, strPw);

        int LoginTimes = 0;
        BOOL bError = FALSE;

_Again:
        listctr.SetItemText(i, COLUMN_TEXT_STATUS, _T("正在登录"));
        int nResult = poster.Login();
        pView->SetResult(nResult, i);
        if(nResult != RESULT_SUCCESS)
        {

            if(nResult == RESULT_FAIL_CAPTCHA || nResult == RESULT_FAIL_IPBLOCK)
            {
                //这两种情况直接换ip
                m_lpVpnFile->AlwaysConnect();
                LoginTimes = 0;
            }
            else if(nResult == RESULT_FAIL_PWERROR)
            {
                //这种情况直接退
                strLine.Remove(_T('\n'));
                strLine += _T(" : 密码错误");
                strLine += _T("\n");

                bError = TRUE;
                goto _WriteError;
            }
            else
            {
                //剩余情况等两次
                TRACE1("失败%d次", LoginTimes++);
                if(LoginTimes == 2)
                {
                    m_lpVpnFile->AlwaysConnect();
                    LoginTimes = 0;
                }
            }

            goto _Again;
        }

        listctr.SetItemText(i, COLUMN_TEXT_STATUS, _T("正在领取"));
        nResult = poster.Get();
        pView->SetResult(nResult, i);

        listctr.SetItemText(i, COLUMN_TEXT_STATUS, _T("正在激活"));
        nResult = poster.Active();
        pView->SetResult(nResult, i);

        if(nResult != RESULT_SUCCESS)
        {
            bError = TRUE;
        }


_WriteError:
        if(bError)
        {
            m_ErrFile.WriteString(strLine);
        }
    }

    m_ErrFile.Close();
    m_lpVpnFile->Close();

}

//创建游戏进程
int CJLkitDoc::CreateGameProcess(CString& strName, CString& strPw, BOOL bProfile, PROCESS_INFORMATION* lppi)
{
    int RetCode;

    CString strGameStart;
    CString strCmdLine;
    CString strSKey;

    STARTUPINFO si;
    ZeroMemory(&si, sizeof(STARTUPINFO));
    si.cb = sizeof(si);

    Webpost poster(strName, strPw);
#ifdef JLTW
    //台服不用登陆
#else
    RetCode = poster.Login();
    if(RetCode != RESULT_SUCCESS) return RetCode;
#endif

    //获取启动KEY
    strSKey = poster.GetStartKey();
    if(strSKey == _T("")) return RESULT_FAIL_GETUKEY;

    //获取配置
    CConfigMgr* pConfig = CConfigMgr::GetInstance();

    //启动游戏
    strCmdLine.Format(
        _T("/LaunchByLauncher /SessKey:\"%s\" /CompanyID:\"0\" /ChannelGroupIndex:\"-1\""), (LPCTSTR)strSKey);

    strGameStart.Format(
        _T("%s /LaunchByLauncher /SessKey:\"%s\" /CompanyID:\"0\" /ChannelGroupIndex:\"-1\""),
        pConfig->m_szGamePath, (LPCTSTR)strSKey);


    if(bProfile)
    {
        //执行批处理
        CString strTemp;
        strTemp.Format(
            _T("cmd /k profileJL.bat JLwg %s \"%s\"\""), pConfig->m_szGamePath, strCmdLine);


        LPCSTR lpszLine;
#ifdef UNICODE
        USES_CONVERSION;
        lpszLine = W2A((LPCTSTR)strTemp);
#else
        lpszLine = (LPCTSTR)strTemp;
#endif

        WinExec(lpszLine, SW_SHOW);
    }
    else
    {
        if(!CreateProcess(NULL, strGameStart.GetBuffer(MAX_PATH), NULL, NULL, FALSE, CREATE_SUSPENDED, NULL, NULL, &si, lppi))
            RetCode = RESULT_FAIL_CREATEGAMEPROCESS;
    }

    strGameStart.ReleaseBuffer();
    return RetCode;
}

//加载游戏
int CJLkitDoc::LaunchGame(CString& strName, CString& strPw, CString& strConfig, CString& strScript, BOOL bProfile)
{

    //是否已经登录
    if(m_ShraeMem.Get((LPCTSTR)strName)) return RESULT_ALREADY_RUNNING;


    //是否有有效卡号
    if(IsHaveValidKey() == FALSE) return RESULT_NOKEY;


    PROCESS_INFORMATION pi;
    ZeroMemory(&pi, sizeof(PROCESS_INFORMATION));

    //创建进程
    int nResult = CreateGameProcess(strName, strPw, bProfile, &pi);
    if(nResult == RESULT_SUCCESS)
    {

        //添加到共享内存
        SHAREINFO sai;
        sai.pid = pi.dwProcessId;
        _tcscpy(sai.szConfig, (LPCTSTR)strConfig);
        _tcscpy(sai.szSript, (LPCTSTR)strScript);
        _tcscpy(sai.szName, (LPCTSTR)strName);
        m_ShraeMem.Add(&sai);

        //注入

#ifndef JLTW
        CInject dllwg(_T("JLwg.dll"));
#else
        CInject dllwg(_T("JLwg_tw.dll"));
#endif
        CInject dllspeed(_T("speedhack-i386.dll"));



#ifdef JLTW

        if(dllspeed.InjectTo(pi.dwProcessId) &&
            dllwg.InjectTo(pi.dwProcessId))
        {
            nResult = RESULT_LOGIN_SUCCESS;

#else
        if(dllwg.InjectTo(pi.dwProcessId) &&
                dllspeed.InjectTo(pi.dwProcessId))
        {
            nResult = RESULT_LOGIN_SUCCESS;

#endif
            //唤起游戏进程
            Sleep(500);
            ResumeThread(pi.hThread);
        }
        else
        {
            nResult = RESULT_FAIL_INJECT;
            TerminateProcess(pi.hProcess, 0);
        }
    }


    return nResult;
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

    SafeDelete(m_lpLock);
    SafeDelete(m_pStatusBox);
    SafeDelete(m_pMsgBox);
    SafeDelete(m_pBindDlg);
    SafeDelete(m_pRegisterDlg);
    SafeDelete(m_pLoginDlg);
    SafeDelete(m_lpVpnFile);
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

    Sleep(250);
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

            ((CMainFrame*)AfxGetMainWnd())->ShowWindow(SW_SHOW);
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