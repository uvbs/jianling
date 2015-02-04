// JLkitDoc.cpp : implementation file
//

#include "stdafx.h"
#include "JLkit.h"
#include "JLkitDoc.h"
#include "JLkitView.h"
#include "MainFrm.h"
#include "JLkitSocket.h"
#include "Keyviewdlg.h"
#include "Logindlg.h"
#include "Settingdlg.h"
#include "BugRepDlg.h"
#include "LaunchGameThread.h"
#include "CVPNFile.h"

#include "..\common\Job.h"
#include "..\common\Inject.h"
#include "..\common\Lock.h"
#include "..\common\ThreadPool.h"
#include "..\common\webpost.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif





/////////////////////////////////////////////////////////////////////////////
// CJLkitDoc

IMPLEMENT_DYNCREATE(CJLkitDoc, CDocument)

CJLkitDoc::CJLkitDoc()
{

    m_szAccountName[0] = _T('\0');
    m_szAccountPw[0] = _T('\0');
    m_szGamePath[0] = _T('\0');
    m_szFileName[0] = _T('\0');

    m_pSocket = NULL;
    m_pKeyDlg = NULL;
    m_pLoginDlg = NULL;
    m_pJob = NULL;
    m_lpVpnFile = NULL;
    m_lpTPool = NULL;
    m_lpLock = NULL;
}

void CJLkitDoc::ConnectResult(int nErrorCode)
{
    if(nErrorCode == 0)
    {

    }
    else
    {
        AfxMessageBox(_T("连接失败"));
    }
}


BOOL CJLkitDoc::OnNewDocument()
{
    if(!CDocument::OnNewDocument())
    {
        return FALSE;
    }


    m_KeepPw =	AfxGetApp()->GetProfileInt(_T("设置"), _T("记住密码"), 0);
    _tcsncpy(m_szFileName, (LPCTSTR)AfxGetApp()->GetProfileString(_T("设置"), _T("帐号文件")), MAX_PATH);
    _tcsncpy(m_szAccountName, (LPCTSTR)AfxGetApp()->GetProfileString(_T("设置"), _T("用户名")), MAX_PATH);
    _tcsncpy(m_szAccountPw, (LPCTSTR)AfxGetApp()->GetProfileString(_T("设置"), _T("密码")), MAX_PATH);
    _tcsncpy(m_szGamePath, (LPCTSTR)AfxGetApp()->GetProfileString(_T("设置"), _T("游戏路径")), MAX_PATH);


    GetGamePath();


    if(!m_lpVpnFile)
    {
        m_lpVpnFile = new CCVPNFile;
    }
    if(!m_lpTPool)
    {
        m_lpTPool = new CThreadPool;
    }
    if(!m_lpLock)
    {
        m_lpLock = new CLock;
    }
    if(!m_pSocket)
    {
        m_pSocket = new CJLkitSocket(this);
        m_pSocket->Create();
    }
    if(!m_pLoginDlg)
    {
        m_pLoginDlg = new CDlgLogin(this);
    }
    if(!m_pJob)
    {
        m_pJob = new CJob;
    }



    CString strServer;
    strServer.LoadString(IDS_CONNECT_SERVER);

    if(m_pSocket->ConnectSrv(strServer, PORT_SRV) == FALSE)
    {
        if(AfxMessageBox(IDS_RETRY_CONNECT, MB_YESNO) == IDNO)
        {
            return FALSE;
        }
    }


    m_pJob->Create(NULL, _T("JLkit_Job"));


    m_pLoginDlg->m_bRemPw = m_KeepPw;
    if(m_KeepPw)
    {
        m_pLoginDlg->m_strPw = m_szAccountPw;
        m_pLoginDlg->m_strName = m_szAccountName;
    }

    if(m_pLoginDlg->DoModal() == IDOK)
    {
        //保存配置
        if(m_pLoginDlg->m_bRemPw)
        {
            _tcscpy(m_szAccountName, (LPCTSTR)m_pLoginDlg->m_strName);
            _tcscpy(m_szAccountPw, (LPCTSTR)m_pLoginDlg->m_strPw);

        }
        m_KeepPw = m_pLoginDlg->m_bRemPw;

        return TRUE;
    }

    return FALSE;
}

CJLkitDoc::~CJLkitDoc()
{
}


BEGIN_MESSAGE_MAP(CJLkitDoc, CDocument)
    //{{AFX_MSG_MAP(CJLkitDoc)
    ON_COMMAND(ID_LOOKKEY, OnLookkey)
    ON_COMMAND(ID_SETTING, OnSetting)
    ON_COMMAND(ID_LOOKSHAREMEM, OnLookShareMem)
    ON_UPDATE_COMMAND_UI(ID_INDICATOR_VALIDKEY, OnUpdateValidKey)
    ON_UPDATE_COMMAND_UI(ID_INDICATOR_LOGINED, OnUpdateLoginedNums)
    ON_UPDATE_COMMAND_UI(ID_INDICATOR_ALLNUMS, OnUpdateAllNums)
    // NOTE - the ClassWizard will add and remove mapping macros here.
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
    if(ar.IsStoring())
    {
        // TODO: add storing code here
    }
    else
    {
        // TODO: add loading code here
    }

    ((CJLkitView*)m_viewList.GetHead())->SerializeText(ar);
}

/////////////////////////////////////////////////////////////////////////////
// CJLkitDoc commands



void CJLkitDoc::OnUpdateValidKey(CCmdUI* pCmdUI)
{
    pCmdUI->Enable(TRUE);
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
    pCmdUI->Enable(TRUE);
    CString strTemp;
    strTemp.Format(IDS_LOGINED, m_share.GetLoginedCount());
    pCmdUI->SetText(strTemp);
}

void CJLkitDoc::OnUpdateAllNums(CCmdUI* pCmdUI)
{
    pCmdUI->Enable(TRUE);
    CString strTemp;
    strTemp.Format(IDS_ALLNUMS, m_share.GetMaxCount());
    pCmdUI->SetText(strTemp);
}

void CJLkitDoc::OnLookShareMem()
{
    SHAREINFO* pShareInfo = m_share.GetMemAddr();
    if(pShareInfo != NULL)
    {
        for(unsigned i = 0; i < m_share.GetMaxCount(); i++, pShareInfo++)
        {
            TCHAR szTemp[BUFSIZ] = {0};
            wsprintf(szTemp, _T("帐号:%s PID:%d 配置:%s 脚本:%s\n"),
                     pShareInfo->szName,
                     pShareInfo->pid,
                     pShareInfo->szConfig,
                     pShareInfo->szSript);

            TRACE(szTemp);
        }
    }
}

void CJLkitDoc::OnLookkey()
{
    m_pKeyDlg = new CDlgKeyView(this);
    m_pKeyDlg->DoModal();

    delete m_pKeyDlg;
    m_pKeyDlg = NULL;
}

void CJLkitDoc::OnSetting()
{
    // TODO: Add your command handler code here
    CDlgSetting dlg;
    dlg.m_strGamePath = m_szGamePath;
    if(dlg.DoModal() == IDOK)
    {
        //保存配置信息
        _tcsncpy(m_szGamePath, dlg.m_strGamePath, MAX_PATH);
    }
}



void CJLkitDoc::GetGamePath()
{

    if(m_szGamePath[0] == '\0')
    {
        //取得游戏路径
        CRegKey reg;
        if(reg.Open(HKEY_LOCAL_MACHINE, _T("SOFTWARE\\Wow6432Node\\plaync\\BNS_KOR")) == ERROR_SUCCESS)
        {
            TCHAR szValue[MAX_PATH];
            ULONG sizeValue = MAX_PATH;
            if(reg.QueryValue(szValue, _T("BaseDir"), &sizeValue) == ERROR_SUCCESS)
            {
                _tcscat(szValue, _T("\\bin\\Client.exe"));
                _tcsncpy(m_szGamePath, szValue, MAX_PATH);
            }

        }
        else
        {
            AfxMessageBox(IDS_NOTFIND_GAME);
        }
    }

}




//检查是否还有有效的KEY供打开一个游戏进程
//这里是一个KEY对应一个游戏进程
BOOL CJLkitDoc::IsHaveValidKey()
{

    DWORD games = m_share.GetLoginedCount();
    if(games >= m_KeyVec.size())
    {
        return FALSE;
    }

    return TRUE;
}


void CJLkitDoc::ProcessRecevice()
{
    CByteArray m_buf;
    m_buf.SetSize(2048);
    int nBytes = m_pSocket->Receive(m_buf.GetData(), m_buf.GetSize());
    if(nBytes == SOCKET_ERROR)
    {
        TRACE(_T("recevice: SOCKET_ERROR"));
    }
    else
    {
        //接收完成
        QUERYKEY_RET_BUF* retbuf = (QUERYKEY_RET_BUF*)m_buf.GetData();
        if(retbuf->fun == fun_login)
        {
            m_pLoginDlg->LoginResult(retbuf->result);
        }

        else if(retbuf->fun == fun_querykey)
        {
            m_KeyVec.clear();
            if(retbuf->result == result_ok)
            {
                for(int i = 0; i < nBytes / sizeof(QUERYKEY_RET_BUF); i++)
                {
                    m_KeyVec.push_back(*retbuf);
                    retbuf++;
                }

                if(m_pKeyDlg)
                {
                    m_pKeyDlg->QueryKeyResult();
                }
            }
        }
        else if(retbuf->fun == fun_unbindkey)
        {
            if(m_pKeyDlg)
            {
                m_pKeyDlg->UnBindResult(retbuf->result);
            }
        }
        else if(retbuf->fun == fun_bindkey)
        {
            if(m_pKeyDlg)
            {
                m_pKeyDlg->BindResult(retbuf->result);
            }
        }
    }
}


void CJLkitDoc::OnCloseDocument()
{

    m_share.Close();
    m_KeyVec.clear();

    if(m_lpVpnFile)
    {
        delete m_lpVpnFile;
        m_lpVpnFile = NULL;
    }
    if(m_lpTPool)
    {
        delete m_lpTPool;
        m_lpTPool = NULL;
    }
    if(m_lpLock)
    {
        delete m_lpLock;
        m_lpLock = NULL;
    }


    if(m_pJob)
    {
        delete m_pJob;
        m_pJob = NULL;
    }

    if(m_pSocket)
    {
        delete m_pSocket;
        m_pSocket = NULL;
    }

    if(m_pLoginDlg)
    {
        delete m_pLoginDlg;
        m_pLoginDlg = NULL;
    }



    //保存设置
    AfxGetApp()->WriteProfileInt(_T("设置"), _T("记住密码"), m_KeepPw);
    AfxGetApp()->WriteProfileString(_T("设置"), _T("帐号文件"), m_szFileName);
    AfxGetApp()->WriteProfileString(_T("设置"), _T("用户名"), m_szAccountName);
    AfxGetApp()->WriteProfileString(_T("设置"), _T("密码"), m_szAccountPw);
    AfxGetApp()->WriteProfileString(_T("设置"), _T("游戏路径"), m_szGamePath);

    CDocument::OnCloseDocument();
}

BOOL CJLkitDoc::OnOpenDocument(LPCTSTR lpszPathName)
{
    if(!CDocument::OnOpenDocument(lpszPathName))
    {
        return FALSE;
    }

    // TODO: Add your specialized creation code here
    AfxGetApp()->WriteProfileString(_T("设置"), _T("帐号文件"), lpszPathName);
    return TRUE;
}


void CJLkitDoc::GetandActive()
{
    m_lpTPool->SetMaxThreads(1);
    m_lpTPool->Init();

    //如果当前没有连接vpn
    TCHAR szPathName[MAX_PATH];
    GetModuleFileName(NULL, szPathName, MAX_PATH);
    PathRemoveFileSpec(szPathName);
    PathAppend(szPathName, _T("VPN.txt"));

    //连接一次vpn
    m_lpVpnFile->Open(szPathName);

    //取得当前模块路径
    TCHAR szPath[MAX_PATH] = {0};
    GetModuleFileName(NULL, szPath, MAX_PATH);
    //将工作路径设置为模块路径
    PathRemoveFileSpec(szPath);
    SetCurrentDirectory(szPath);

    CTime time = CTime::GetCurrentTime();
    CString strTime = time.Format("%d-%H-%M");
    CreateDirectory(strTime, NULL);
    PathAppend(szPath, strTime);
    SetCurrentDirectory(szPath);

    errfile.Open(_T("错误帐号.txt"), CFile::modeReadWrite | CFile::modeCreate);

}


//加载游戏, 返回值为进程pid
int CJLkitDoc::LaunchGame(const CString& strName,
                          const CString& strPw,
                          const CString& strConfig,
                          const CString& strScript,
                          BOOL bProfile)
{

    if(m_share.IsLogined((LPCTSTR)strName))
    {
        return RESULT_ALREADY_RUNNING;
    }

    PROCESS_INFORMATION pi;
    STARTUPINFO si;

    ZeroMemory(&pi, sizeof(pi));
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);


    Webpost poster(strName, strPw);
    int LoginRet = poster.Login();
    if(LoginRet != RESULT_SUCCESS)
    {
        return LoginRet;
    }

    //登录
    CString strSKey;
    strSKey = poster.GetGameStartKey();
    if(strSKey == _T(""))
    {
        return RESULT_FAIL_GETUKEY;
    }


    //启动游戏
    CString strGameStart;
    CString strCmdLine;
    strCmdLine.Format(_T("/LaunchByLauncher /SessKey:\"%s\" ")
                      _T("/CompanyID:\"0\" /ChannelGroupIndex:\"-1\""), (LPCTSTR)strSKey);
    strGameStart.Format(_T("%s /LaunchByLauncher /SessKey:\"%s\" ")
                        _T("/CompanyID:\"0\" /ChannelGroupIndex:\"-1\""),
                        m_szGamePath, (LPCTSTR)strSKey);


    TCHAR szGameCmdLine[BUFSIZ] = {0};
    _tcsncpy(szGameCmdLine, (LPCTSTR)strGameStart, strGameStart.GetLength());


    CCInject dllwg("JLwg.dll");
    CCInject dllspeed("speedhack-i386.dll");
    if(bProfile)
    {
        //执行批处理
        CString strTemp;
        strTemp.Format(_T("cmd /k profileJL.bat JLwg %s \"%s\"\""), m_szGamePath, strCmdLine);
        WinExec((LPCTSTR)strTemp, SW_SHOW);

        return RESULT_SUCCESS;
    }
    else
    {
        if(CreateProcess(NULL, szGameCmdLine, NULL,  NULL, FALSE,
                         CREATE_SUSPENDED, NULL, NULL, &si, &pi) == FALSE)
        {
            return RESULT_FAIL_CREATEGAMEPROCESS;
        }

        SHAREINFO sai;
        sai.pid = pi.dwProcessId;
        strcpy(sai.szConfig, (LPCTSTR)strConfig);
        strcpy(sai.szSript, (LPCTSTR)strScript);
        strcpy(sai.szName, (LPCTSTR)strName);
        m_share.Add(&sai);

        ResumeThread(pi.hThread);
        if(dllwg.InjectTo(pi.dwProcessId) &&
                dllspeed.InjectTo(pi.dwProcessId))
        {
            return RESULT_SUCCESS;
        }
    }


    return RESULT_FAIL_INJECT;
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
        return nRet;

    }

    return nRet;
}

void CJLkitDoc::DeleteContents()
{
    // TODO: Add your specialized code here and/or call the base class


    CDocument::DeleteContents();
}
