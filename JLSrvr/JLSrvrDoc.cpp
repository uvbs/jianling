// JLSrvrDoc.cpp : implementation of the CJLSrvrDoc class
//

#include "stdafx.h"
#include "JLSrvr.h"
#include "JLSrvrDoc.h"
#include "DlgAddKey.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//��̬����
IMPLEMENT_DYNCREATE(CJLSrvrDoc, CDocument)

//��Ϣӳ��
BEGIN_MESSAGE_MAP(CJLSrvrDoc, CDocument)
    //{{AFX_MSG_MAP(CJLSrvrDoc)
    ON_COMMAND(ID_FILE_RESTART, OnFileRestart)
    ON_UPDATE_COMMAND_UI(ID_INDICATOR_CONNECTS, OnUpdateConnects)
    ON_COMMAND(ID_KEY_ADD, OnKeyAdd)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

//���캯��
CJLSrvrDoc::CJLSrvrDoc()
{
    m_pListen = NULL;
}

//��������
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

    //��ʼ�����ݿ�
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

    //��ֹͣ��ǰ����
    StopListening();

    //�µļ����׽���
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

    //��¼����ʱ��
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
    DeleteClient(pSocket);
    return false;
}

bool CJLSrvrDoc::OnEventTCPSocketRead(CJLkitSocket* pSocket, const Tcp_Head& stTcpHead, void* pData, WORD wDataSize)
{

    _heart[pSocket] = time(NULL);

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
            PROCESS_DESCRIBE des;
            int inResult;
            int inDbRet;

            //�����û���½����
            LOGIN_BUF* pLogin = (LOGIN_BUF*)pData;
            _userdata[pSocket] = *pLogin;


            inDbRet = m_db.CheckUser(pLogin->name, pLogin->pw);
            switch(inDbRet)
            {
            case 0:
                {
                    _tcscpy(des.szDescribe, _T("Զ�˴���"));
                    break;
                }
            case 1:
                {
                    _tcscpy(des.szDescribe, _T("��½���"));
                    break;
                }
            case 2:
                {
                    _tcscpy(des.szDescribe, _T("�Ѿ���½"));
                    break;
                }
            case 3:
                {
                    _tcscpy(des.szDescribe, _T("û�����û�"));
                    break;
                }
            case 4:
                {
                    _tcscpy(des.szDescribe, _T("�������"));
                    break;
                }
            case 5:
                {
                    _tcscpy(des.szDescribe, _T("��½IP�Ͱ�IP��ͬ"));
                    break;
                }
            case 6:
                {
                    _tcscpy(des.szDescribe, _T("��½�������ʱ��������ͬ"));
                    break;
                }
            default:
                {
                    //����Ӧ���ǲ����ܷ��������
                    TRACE(_T("inDbRet: %d"), inDbRet);
                    _ASSERTE(FALSE);
                }
            }



            if(inDbRet == 1)
            {
                inResult = fun_login_ok;
            }
            else
            {
                inResult = fun_login_fail;
            }

            pSocket->Send(M_LOGIN, inResult, &des, sizeof(PROCESS_DESCRIBE));

            break;
        }


    //ע��
    case fun_regist:
        {
            PROCESS_DESCRIBE des;
            REGIST_BUF* pReg = (REGIST_BUF*)pData;


            int inRet;
            if(m_db.NewRegist(pReg->name, pReg->pw))
            {
                inRet = fun_regist_ok;
                _tcscpy(des.szDescribe, _T("ע�����"));
            }
            else
            {
                inRet = fun_regist_fail;
                _tcscpy(des.szDescribe, _T("ע��ʧ��"));
            }

            TRACE(_T("����ע����"));
            pSocket->Send(M_LOGIN, inRet, &des, sizeof(PROCESS_DESCRIBE));

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
                    pSocket->Send(M_KEY, fun_querykey_ok, it, sizeof(QUERYKEY_SUCCESS));
                }
            }
            else
            {
                PROCESS_DESCRIBE des;
                _tcscpy(des.szDescribe, _T("���˺�û�а��κο���"));
                pSocket->Send(M_KEY, fun_querykey_fail, &des, sizeof(PROCESS_DESCRIBE));
            }


            break;
        }

    case fun_bindkey:
        {
            BINDKEY_BUF* pBuf = (BINDKEY_BUF*)pData;
            PROCESS_DESCRIBE des;
            int inResult;
            int inDbRet = m_db.Bindkey(_userdata[pSocket].name, pBuf->key, _T(""));
            if(inDbRet == 1)
            {
                inResult = fun_bindkey_ok;
                _tcscpy(des.szDescribe, _T("�����"));
            }
            else if(inDbRet == 2)
            {
                inResult = fun_bindkey_fail;
                _tcscpy(des.szDescribe, _T("������Ч"));
            }
            else if(inDbRet == 3)
            {
                inResult = fun_bindkey_fail;
                _tcscpy(des.szDescribe, _T("�������ù�"));
            }
            else if(inDbRet == 0)
            {
                inResult = fun_bindkey_fail;
                _tcscpy(des.szDescribe, _T("Զ�˴���"));
            }
            else
            {
                _ASSERTE(FALSE);
            }

            pSocket->Send(M_KEY, inResult, &des, sizeof(PROCESS_DESCRIBE));
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
    _heart[pSocket] = time(NULL);
    _client.push_back(pSocket);
    return true;
}

bool CJLSrvrDoc::DeleteClient(CJLkitSocket* pSocket)
{
    _client.remove(pSocket);
    _heart.erase(pSocket);
    m_db.UserExit(_userdata[pSocket].name);

    TRACE(_T("_heart: %d"), _heart.size());
    TRACE(_T("_client: %d"), _client.size());

    pSocket->Close();
    SafeDelete(pSocket);

    return true;
}

void CJLSrvrDoc::OnUpdateConnects(CCmdUI* pCmdUI)
{
    CString strTemp;
    strTemp.Format(_T("������: %d"), _client.size());
    pCmdUI->SetText(strTemp);
}

void CJLSrvrDoc::OnKeyAdd()
{
    CDlgAddKey dlg;
    dlg.DoModal();
}

void CJLSrvrDoc::DeadSocketClear()
{

    if(_heart.empty()) return;

    std::map<CJLkitSocket*, time_t>::iterator it;
    std::map<CJLkitSocket*, time_t>::iterator it2;
    for(it = _heart.begin(); it != _heart.end();)
    {
        it2 = it++;
        if((time(NULL) - it2->second) > 20)
        {
            DeleteClient(it2->first);
        }
    }
}
