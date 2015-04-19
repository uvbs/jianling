// JLSrvrDoc.cpp : implementation of the CJLSrvrDoc class
//

#include "stdafx.h"
#include "JLSrvr.h"
#include "JLSrvrDoc.h"
#include "DbMngr.h"
#include "ListenSocket.h"




#ifdef _DEBUG
    #define new DEBUG_NEW
#endif

//动态创建
IMPLEMENT_DYNCREATE(CJLSrvrDoc, CDocument)

//消息映射
BEGIN_MESSAGE_MAP(CJLSrvrDoc, CDocument)
    //{{AFX_MSG_MAP(CJLSrvrDoc)
    ON_COMMAND(ID_FILE_RESTART, OnFileRestart)
    ON_UPDATE_COMMAND_UI(ID_INDICATOR_CONNECTS, OnUpdateConnects)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

//构造函数
CJLSrvrDoc::CJLSrvrDoc()
{
    m_pListen = NULL;
}

//析构函数
CJLSrvrDoc::~CJLSrvrDoc()
{

}


void CJLSrvrDoc::OnFileRestart()
{
    // this will close the connection if it's already open
    // before starting again....
    StartListening();
}


BOOL CJLSrvrDoc::OnNewDocument()
{
    if(!CDocument::OnNewDocument()) return FALSE;



    //初始化数据库
    if(!m_db.Init())
        return FALSE;

    SetTitle(NULL);

    BOOL bRet = StartListening();
    return bRet;
}


void CJLSrvrDoc::StopListening()
{
    if(m_pListen != NULL)
    {
        m_pListen->Close();
        delete m_pListen;
        m_pListen = NULL;
    }
}


void CJLSrvrDoc::SetTitle(LPCTSTR lpszTitle)
{
    CString strTitle;
    if(lpszTitle != NULL)
    {
        m_strTitleBase = lpszTitle;
    }

    if(m_strServer.IsEmpty())
    {
        strTitle = m_strTitleBase;
    }
    else if(m_pListen == NULL)
    {
        strTitle.Format(IDS_INVALID, m_strTitleBase);
    }
    else
    {
        strTitle.Format(IDS_DOCTITLE_NOPORT, m_strTitleBase, m_strServer);
    }

    CDocument::SetTitle(strTitle);
}


BOOL CJLSrvrDoc::StartListening()
{
    BOOL bOk = FALSE;

    //先停止当前监听
    StopListening();

    //新的监听套接字
    m_pListen = new CListenSocket();


    if(m_pListen)
    {

        if(m_pListen->Create(PORT_SRV, SOCK_STREAM))
        {
            bOk = m_pListen->Listen();
        }


        if(bOk == FALSE)
        {
            CString strMsg;
            int nErr = m_pListen->GetLastError();
            if(nErr == WSAEADDRINUSE)
            {
                strMsg.Format(IDS_LISTEN_INUSE, PORT_SRV);
            }
            else
            {
                strMsg.LoadString(IDS_LISTEN_ERROR);
            }

            AfxMessageBox(strMsg, MB_OK | MB_ICONSTOP);
            StopListening();
        }
    }
    else
    {
        AfxMessageBox(IDS_CANT_LISTEN, MB_OK | MB_ICONSTOP);
    }

    //记录启动时间
    m_timeStarted = CTime::GetCurrentTime();

    return bOk;
}

/////////////////////////////////////////////////////////////////////////////
// CJLSrvrDoc serialization

void CJLSrvrDoc::Serialize(CArchive& ar)
{
    if(ar.IsStoring())
    {
        // TODO: add storing code here
    }
    else
    {
        // TODO: add loading code here
    }
}

/////////////////////////////////////////////////////////////////////////////
// CJLSrvrDoc diagnostics

#ifdef _DEBUG
void CJLSrvrDoc::AssertValid() const
{
    CDocument::AssertValid();
}

void CJLSrvrDoc::Dump(CDumpContext& dc) const
{
    CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CJLSrvrDoc commands

void CJLSrvrDoc::OnCloseDocument()
{
    StopListening();
    CDocument::OnCloseDocument();
}


bool CJLSrvrDoc::OnEventTCPSocketLink(CJLkitSocket* pSocket, INT nErrorCode)
{

    return false;
}

bool CJLSrvrDoc::OnEventTCPSocketShut(CJLkitSocket* pSocket, BYTE cbShutReason)
{
    //删除这个客户
    DeleteClient(pSocket);
    return false;
}

bool CJLSrvrDoc::OnEventTCPSocketRead(CJLkitSocket* pSocket, const Tcp_Head& stTcpHead, void* pData, WORD wDataSize)
{
    switch(stTcpHead.wMainCmdID)
    {
        case M_LOGIN:
        {
            ProcessLogin(pSocket, stTcpHead, pData, wDataSize);
            break;
        }

        case M_KEY:
        {

            ProcessKey(pSocket, stTcpHead, pData, wDataSize);
            break;
        }


        default:
            break;
    }


    return true;
}

bool CJLSrvrDoc::ProcessLogin(CJLkitSocket* pSocket, const Tcp_Head& stTcpHead, void* pData, WORD wDataSize)
{
    _ASSERTE(pSocket != NULL);

    switch(stTcpHead.wSubCmdID)
    {
        case fun_login:
        {
            PROCESS_DESCRIBE LoginBuf;
            LOGIN_BUF* pLogin = (LOGIN_BUF*)pData;


            //保存用户登陆数据
            _userdata[pSocket] = *pLogin;


            int inResult;
            int inDbRet = m_db.CheckUser(pLogin->name, pLogin->pw);
            if(inDbRet == 0)
            {
                inResult = fun_login_ok;
                _tcscpy(LoginBuf.szDescribe, _T("北京欢迎你."));
            }
            else if(inDbRet == 2)
            {
                inResult = fun_login_fail;
                _tcscpy(LoginBuf.szDescribe, _T("已经登陆"));
            }
            else
            {
                inResult = fun_login_fail;
                _tcscpy(LoginBuf.szDescribe, _T("密码错误"));
            }


            pSocket->Send(M_LOGIN, inResult, &LoginBuf, sizeof(PROCESS_DESCRIBE));

            break;
        }


        //注册
        case fun_regist:
        {
            break;
        }


        //修改绑定
        case fun_mbind:
        {
            break;
        }


        default:
            break;
    }


    return true;
}

bool CJLSrvrDoc::ProcessKey(CJLkitSocket* pSocket, const Tcp_Head& stTcpHead, void* pData, WORD wDataSize)
{
    switch(stTcpHead.wSubCmdID)
    {

        case fun_querykey:
        {

            std::vector<QUERYKEY_SUCCESS> KeyVec;
            BOOL bDbRet = m_db.Querykey(KeyVec, _userdata[pSocket].name, _userdata[pSocket].pw);
            if(KeyVec.size())
            {
                for(std::vector<QUERYKEY_SUCCESS>::iterator it = KeyVec.begin(); it != KeyVec.end(); it++)
                {
                    pSocket->Send(M_KEY, fun_querykey_ok, &it, sizeof(QUERYKEY_SUCCESS));
                }
            }
            else
            {
                PROCESS_DESCRIBE des;
                _tcscpy(des.szDescribe, _T("此账号没有绑定任何卡号"));
                pSocket->Send(M_KEY, fun_querykey_fail, &des, sizeof(PROCESS_DESCRIBE));
            }


            break;
        }

        case fun_bindkey:
            {
                BINDKEY_BUF *pBuf = (BINDKEY_BUF *)pData;
                if(m_db.Bindkey(_userdata[pSocket].name, pBuf->key, _T("")))
                {
                    pSocket->Send(M_KEY, fun_bindkey_ok, NULL, 0);
                }
                else
                {
                    PROCESS_DESCRIBE des;
                    _tcscpy(des.szDescribe, _T("绑定失败"));
                    pSocket->Send(M_KEY, fun_bindkey_fail, &des, sizeof(PROCESS_DESCRIBE));
                }
                break;
            }

   
        default:
            break;
    }
    return true;
}

bool CJLSrvrDoc::ProcessHelp(CJLkitSocket* pSocket, const Tcp_Head& stTcpHead, void* pData, WORD wDataSize)
{

    return false;
}

bool CJLSrvrDoc::AddClient(CJLkitSocket* pSocket)
{
    _client.push_back(pSocket);
    return true;
}

bool CJLSrvrDoc::DeleteClient(CJLkitSocket* pSocket)
{
    _client.remove(pSocket);
    _userdata.erase(pSocket);
    SafeDelete(pSocket);

    return true;
}

void CJLSrvrDoc::OnUpdateConnects(CCmdUI* pCmdUI)
{
    CString strTemp;
    strTemp.Format(_T("连接数: %d"), _client.size());
    pCmdUI->SetText(strTemp);
}
