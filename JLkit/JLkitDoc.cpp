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
#include "configmgr.h"


#include "..\common\Job.h"
#include "..\common\Inject.h"
#include "..\common\Lock.h"
#include "..\common\ThreadPool.h"
#include "..\common\webpost.h"
#include "..\Common\common.h"


#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif


//��̬����
KeyVec CJLkitDoc::m_KeyVec;


/////////////////////////////////////////////////////////////////////////////
// CJLkitDoc
IMPLEMENT_DYNCREATE(CJLkitDoc, CDocument)
CJLkitDoc::CJLkitDoc()
{
    m_pKeyDlg = NULL;
    m_pLoginDlg = NULL;
    m_lpVpnFile = NULL;
    m_lpLock = NULL;
}

void CJLkitDoc::ConnectResult(int nErrorCode)
{
    if(m_pLoginDlg) {
        m_pLoginDlg->ConnectResult(nErrorCode);
    }
}


BOOL CJLkitDoc::OnNewDocument()
{
    if(!CDocument::OnNewDocument()) {
        return FALSE;
    }

    CConfigMgr* lpConMgr = CConfigMgr::GetInstance();
    CJLkitSocket* lpKitSocket = CJLkitSocket::GetInstance();

    //��ʼ��
    if(!m_lpVpnFile) {
        m_lpVpnFile = new CVpnFile;
    }

    if(!m_lpLock) {
        m_lpLock = new CLock;
    }

    //�����׽���
    lpKitSocket->SetDoc(this);
    lpKitSocket->Create();

    //������½�Ի���
    if(!m_pLoginDlg) {
        m_pLoginDlg = new CDlgLogin;
    }

    //���ӷ�����
    CString strServer;
    strServer.LoadString(IDS_CONNECT_SERVER);
    if(CJLkitSocket::GetInstance()->ConnectSrv(strServer, PORT_SRV) == FALSE) {
        if(AfxMessageBox(IDS_RETRY_CONNECT, MB_YESNO) == IDNO) {
            return FALSE;
        }
    }


    //��½�Ի���
    if(m_pLoginDlg->DoModal() == IDOK) return TRUE;

    return FALSE;
}

CJLkitDoc::~CJLkitDoc()
{
    TRACE(_T("CJLkitDoc Called"));
}


BEGIN_MESSAGE_MAP(CJLkitDoc, CDocument)
    //{{AFX_MSG_MAP(CJLkitDoc)
    ON_COMMAND(ID_LOOKKEY, OnLookkey)
    ON_COMMAND(ID_SETTING, OnSetting)
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
    ((CJLkitView*)m_viewList.GetHead())->SerializeText(ar);
}

/////////////////////////////////////////////////////////////////////////////
// CJLkitDoc commands



void CJLkitDoc::OnUpdateValidKey(CCmdUI* pCmdUI)
{
    pCmdUI->Enable(TRUE);
    CString strInfo;
    if(strInfo.LoadString(IDS_VALIDKEY)) {
        CString strTemp;
        strTemp.Format(IDS_VALIDKEY, m_KeyVec.size());
        pCmdUI->SetText(strTemp);
    }
}

void CJLkitDoc::OnUpdateLoginedNums(CCmdUI* pCmdUI)
{
    pCmdUI->Enable(TRUE);
    CString strTemp;
    strTemp.Format(IDS_LOGINED, JLShareMem::Instance()->GetUsedCount());
    pCmdUI->SetText(strTemp);
}

void CJLkitDoc::OnUpdateAllNums(CCmdUI* pCmdUI)
{
    pCmdUI->Enable(TRUE);
    CString strTemp;
    strTemp.Format(IDS_ALLNUMS, JLShareMem::Instance()->GetAllCount());
    pCmdUI->SetText(strTemp);
}


void CJLkitDoc::OnSetting()
{
    // TODO: Add your command handler code here
    CDlgSetting dlg;
    dlg.m_strGamePath = CConfigMgr::GetInstance()->m_szGamePath;
    if(dlg.DoModal() == IDOK) {
        //����������Ϣ
        _tcsncpy(CConfigMgr::GetInstance()->m_szGamePath, dlg.m_strGamePath, MAX_PATH);
    }
}



//����Ƿ�����Ч��KEY����һ����Ϸ����
//������һ��KEY��Ӧһ����Ϸ����
BOOL CJLkitDoc::IsHaveValidKey()
{

    DWORD games = JLShareMem::Instance()->GetUsedCount();
    if(games >= m_KeyVec.size()) {
        return FALSE;
    }

    return TRUE;
}


void CJLkitDoc::ProcessRecevice()
{
    CByteArray m_buf;
    m_buf.SetSize(2048);
    int nBytes = CJLkitSocket::GetInstance()->Receive(m_buf.GetData(), m_buf.GetSize());
    if(nBytes == SOCKET_ERROR) {
        TRACE(_T("recevice: SOCKET_ERROR"));
    }
    else {
        //�������
        QUERYKEY_RET_BUF* retbuf = (QUERYKEY_RET_BUF*)m_buf.GetData();
        if(retbuf->fun == fun_login) {
            m_pLoginDlg->LoginResult(retbuf->result);
        }
        else if(retbuf->fun == fun_regist) {

        }
        else if(retbuf->fun == fun_querykey) {
            m_KeyVec.clear();
            if(retbuf->result == result_ok) {
                for(int i = 0; i < nBytes / sizeof(QUERYKEY_RET_BUF); i++) {
                    m_KeyVec.push_back(*retbuf);
                    retbuf++;
                }

                if(m_pKeyDlg) {
                    m_pKeyDlg->QueryKeyResult();
                }
            }
        }
        else if(retbuf->fun == fun_unbindkey) {
            if(m_pKeyDlg) {
                m_pKeyDlg->UnBindResult(retbuf->result);
            }
        }
        else if(retbuf->fun == fun_bindkey) {
            if(m_pKeyDlg) {
                m_pKeyDlg->BindResult(retbuf->result);
            }
        }
        else if(retbuf->fun == fun_regist) {
            if(retbuf->result = TRUE) {
                AfxMessageBox(_T("ע�����"));
            }
            else {
                AfxMessageBox(_T("ע��ʧ��"));
            }
        }
    }
}


void CJLkitDoc::OnCloseDocument()
{
    TRACE(_T("OnCloseDocument Called"));
    m_KeyVec.clear();

    if(m_lpVpnFile) {
        delete m_lpVpnFile;
        m_lpVpnFile = NULL;
    }
    if(m_lpLock) {
        delete m_lpLock;
        m_lpLock = NULL;
    }

    if(CJLkitSocket::GetInstance()) {
        CJLkitSocket::GetInstance()->Delete();
    }

    if(m_pLoginDlg) {
        delete m_pLoginDlg;
        m_pLoginDlg = NULL;
    }




    CDocument::OnCloseDocument();
}


void CJLkitDoc::GetandActive()
{
    //�����ǰû������vpn
    TCHAR szPathName[MAX_PATH];
    GetModuleFileName(NULL, szPathName, MAX_PATH);
    PathRemoveFileSpec(szPathName);
    PathAppend(szPathName, _T("VPN.txt"));

    //����һ��vpn
    m_lpVpnFile->Open(szPathName);

    //ȡ�õ�ǰģ��·��
    TCHAR szPath[MAX_PATH] = {0};
    GetModuleFileName(NULL, szPath, MAX_PATH);

    //������·������Ϊģ��·��
    PathRemoveFileSpec(szPath);
    SetCurrentDirectory(szPath);

    CTime time = CTime::GetCurrentTime();
    CString strTime = time.Format("%d��%Hʱ%M��");
    CreateDirectory(strTime, NULL);
    PathAppend(szPath, strTime);
    SetCurrentDirectory(szPath);

    errfile.Open(_T("�����ʺ�.txt"), CFile::modeReadWrite | CFile::modeCreate);

}

//������Ϸ����
int CJLkitDoc::CreateGameProcess(CString& strName, CString& strPw, BOOL bProfile, PROCESS_INFORMATION* lppi)
{

    STARTUPINFO si;
    ZeroMemory(&si, sizeof(STARTUPINFO));
    si.cb = sizeof(si);

    Webpost poster(strName, strPw);
    int LoginRet = poster.Login();
    if(LoginRet != RESULT_SUCCESS) return LoginRet;

    //��¼
    CString strSKey;
    strSKey = poster.GetGameStartKey();
    if(strSKey == _T("")) return RESULT_FAIL_GETUKEY;


    //������Ϸ
    CString strGameStart;
    CString strCmdLine;
    strCmdLine.Format(_T("/LaunchByLauncher /SessKey:\"%s\" ")
                      _T("/CompanyID:\"0\" /ChannelGroupIndex:\"-1\""), (LPCTSTR)strSKey);
    strGameStart.Format(_T("%s /LaunchByLauncher /SessKey:\"%s\" ")
                        _T("/CompanyID:\"0\" /ChannelGroupIndex:\"-1\""),
                        CConfigMgr::GetInstance()->m_szGamePath, (LPCTSTR)strSKey);


    TCHAR szGameCmdLine[BUFSIZ] = {0};
    _tcsncpy(szGameCmdLine, (LPCTSTR)strGameStart, strGameStart.GetLength());

    if(bProfile) {
        //ִ��������
        CString strTemp;
        strTemp.Format(_T("cmd /k profileJL.bat JLwg %s \"%s\"\""),
                       CConfigMgr::GetInstance()->m_szGamePath,
                       strCmdLine);


        LPCSTR lpszLine;
        #ifdef UNICODE
        USES_CONVERSION;
        lpszLine = W2A((LPCTSTR)strTemp);
        #else
        lpszLine = (LPCTSTR)strLine;
        #endif

        WinExec(lpszLine, SW_SHOW);
    }
    else {
        if(!CreateProcess(NULL, szGameCmdLine, NULL, NULL, FALSE, CREATE_SUSPENDED, NULL, NULL, &si, lppi))
            return RESULT_FAIL_CREATEGAMEPROCESS;
    }

    return RESULT_SUCCESS;
}

//������Ϸ
int CJLkitDoc::LaunchGame(CString& strName, CString& strPw, CString& strConfig, CString& strScript, BOOL bProfile)
{

    //�Ƿ��Ѿ���¼
    if(JLShareMem::Instance()->Get((LPCTSTR)strName))
        return RESULT_ALREADY_RUNNING;


    //�Ƿ�����Ч����
    if(IsHaveValidKey() == FALSE) return RESULT_NOKEY;


    PROCESS_INFORMATION pi;
    ZeroMemory(&pi, sizeof(PROCESS_INFORMATION));

    //��������
    int nResult = CreateGameProcess(strName, strPw, bProfile, &pi);
    if(nResult == RESULT_SUCCESS) {

        SHAREINFO sai;
        sai.pid = pi.dwProcessId;
        _tcscpy(sai.szConfig, (LPCTSTR)strConfig);
        _tcscpy(sai.szSript, (LPCTSTR)strScript);
        _tcscpy(sai.szName, (LPCTSTR)strName);
        JLShareMem::Instance()->Add(&sai);


        CInject dllwg(_T("JLwg.dll"));
        CInject dllspeed(_T("speedhack-i386.dll"));
        //������Ϸ����
        ResumeThread(pi.hThread);
        Sleep(3000);

        //ע��
        if(dllwg.InjectTo(pi.dwProcessId) && dllspeed.InjectTo(pi.dwProcessId)) {
            nResult = RESULT_LOGIN_SUCCESS;
        }
        else {
            nResult = RESULT_FAIL_INJECT;
            TerminateProcess(pi.hProcess, 0);
        }
    }


    return nResult;;
}

int CJLkitDoc::Get(CString& strName, CString& strPw)
{
    Webpost poster(strName, strPw);
    int nRet = poster.Login();
    if(nRet == RESULT_SUCCESS) {
        nRet = poster.Get();
        return nRet;
    }
    else {
        return nRet;
    }
}


void CJLkitDoc::OnLookkey()
{
    m_pKeyDlg = new CDlgKeyView();
    m_pKeyDlg->DoModal();

    delete m_pKeyDlg;
    m_pKeyDlg = NULL;
}


int CJLkitDoc::Active(CString& strName, CString& strPw)
{
    Webpost poster(strName, strPw);
    int nRet = poster.Login();
    if(nRet == RESULT_SUCCESS) {
        nRet = poster.Active();
        return nRet;

    }

    return nRet;
}

void CJLkitDoc::OnIdle()
{

}

BOOL CJLkitDoc::OnOpenDocument(LPCTSTR lpszPathName)
{
    if(!CDocument::OnOpenDocument(lpszPathName))
        return FALSE;


    return TRUE;
}
