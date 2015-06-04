#include "stdafx.h"
#include "JLkit.h"
#include "JLkitDoc.h"
#include "JLkitView.h"
#include "MainFrm.h"
#include "Settingdlg.h"
#include "ConfigMgr.h"
#include "LoginSheet.h"
#include "Registdlg.h"
#include "Logindlg.h"
#include "Keyviewdlg.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#endif


/////////////////////////////////////////////////////////////////////////////
// CJLkitDoc
IMPLEMENT_DYNCREATE(CJLkitDoc, CDocument)

CJLkitDoc::CJLkitDoc()
{

    m_pRegisterDlg = NULL;
    m_pLoginDlg = NULL;
    m_pKeyDlg = NULL;
    m_pLoginSheet = NULL;

    m_bRegister = false;
	
    //���ûص�
    m_socket.SetSink(this);

	m_loginStatus = nologin;
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
        //����������Ϣ
        CConfigMgr::GetInstance()->m_szGamePath = dlg.m_strGamePath;
    }
}


//����Ƿ�����Ч��KEY����һ����Ϸ����
//������һ��KEY��Ӧһ����Ϸ����
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

    SafeDelete(m_pRegisterDlg);
    SafeDelete(m_pLoginDlg);
    SafeDelete(m_pLoginSheet);


    CDocument::OnCloseDocument();
}



void CJLkitDoc::ShowLogin()
{
    //������½�Ի���
    if(!m_pLoginSheet)
    {
        m_pLoginSheet = new CLoginSheet(_T(""));
    }

    if(!m_pLoginDlg)
    {
        m_pLoginDlg = new CDlgLogin();
    }

    if(!m_pRegisterDlg)
    {
        m_pRegisterDlg = new CDlgRegist();
    }

    m_bRegister = false;

    if(m_pLoginSheet->m_hWnd == NULL)
    {
        m_pLoginSheet->AddPage(m_pLoginDlg);
        m_pLoginSheet->AddPage(m_pRegisterDlg);
        m_pLoginSheet->Create(NULL, WS_OVERLAPPED | WS_SYSMENU);
    }

    m_pLoginSheet->ShowWindow(SW_SHOW);

}

bool CJLkitDoc::PerformLogonMission()
{
    TRACE(_T("�������ӷ�����.."));


    if(!m_socket.ConnectSrv(NAME_SRV, PORT_SRV))
    {
        AfxMessageBox(_T("���ӷ�����ʧ��"));
        ShowLogin();
        return false;
    }

    return true;
}


VOID CALLBACK TimeoutLogin(PTP_CALLBACK_INSTANCE pInstance, PVOID pvContext, PTP_CALLBACK_ENVIRON pcbe)
{
	CJLkitDoc *pDoc = (CJLkitDoc *)pvContext;

	if(pDoc->m_loginStatus == logining)
	{
		AfxMessageBox(_T("��¼ʧ��"));
		pDoc->m_socket.Close();
		pDoc->ShowLogin();
	}

}

//�����¼�
bool CJLkitDoc::OnEventTCPSocketLink(CJLkitSocket* pSocket, INT nErrorCode)
{

    if(nErrorCode != 0)
    {
		m_loginStatus = nologin;
        AfxMessageBox(_T("���ӷ�����ʧ��"));
        m_socket.Close();
        ShowLogin();
    }
    else
    {

		int funid;

		if(m_bRegister)
		{
			funid = fun_regist;
		}
		else
		{
			funid = fun_login;
		}

		m_socket.Send(M_LOGIN, funid, 0, 0);

		m_loginStatus = logining;
	}

    return true;
}


//�ر��¼�
bool CJLkitDoc::OnEventTCPSocketShut(CJLkitSocket* pSocket, INT nErrorCode)
{
	m_loginStatus = nologin;
    pSocket->Close();
    return true;
}

void CJLkitDoc::ProcessLogin(CJLkitSocket* pSocket, const Tcp_Head& stTcpHead, void* pData, WORD wDataSize)
{

	switch(stTcpHead.wSubCmdID)
	{
		//����������Ӧ��
	case fun_login_reply:
		{
			TZ *pLoginBuf = (TZ*)pData;
			DWORD dwnValue = pLoginBuf->dwNvalue;
			DWORD repyN = calcNvalue(dwnValue);


			TRACE(_T("���ڵ�½.."));

			//�������, ��ʼ���͵�½����
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

				LOGIN_BUF *pLoginBuf = (LOGIN_BUF *)cbBuffer;
				pLoginBuf->tz = repyN;

				funid = fun_login_reply;
			}

			m_socket.Send(M_LOGIN, funid, cbBuffer, wPacketSize);

			PTP_TIMER hTimerOut = CreateThreadpoolTimer((PTP_TIMER_CALLBACK)TimeoutLogin, this, NULL);
			ULARGE_INTEGER ulRelativeStartTime;
			ulRelativeStartTime.QuadPart = -50000000;
			FILETIME ftRelativeStartTime;
			ftRelativeStartTime.dwHighDateTime = ulRelativeStartTime.HighPart;
			ftRelativeStartTime.dwLowDateTime = ulRelativeStartTime.LowPart;

			SetThreadpoolTimer(hTimerOut, &ftRelativeStartTime, 0, 0);

			m_loginStatus = logining;
			break;
		}

    //��¼ʧ��
    case fun_login_fail:
        {
            //�ر�����
			m_loginStatus = nologin;
            m_socket.Close();

            PROCESS_DESCRIBE* pDes = (PROCESS_DESCRIBE*)pData;
            AfxMessageBox(pDes->szDescribe);

            //��¼�Ի���
            ShowLogin();
            break;
        }

    //��¼���
    case fun_login_ok:
        {
			m_loginStatus = logined;
            SafeDelete(m_pLoginSheet);

            //�Զ������ϴδ򿪵��ļ�
            if(CConfigMgr::GetInstance()->m_szFileName[0] != _T('\0'))
            {
                AfxGetApp()->OpenDocumentFile(CConfigMgr::GetInstance()->m_szFileName.c_str());
            }

            //��ʾ������
            ((CMainFrame*)AfxGetMainWnd())->ActivateFrame();
			//��������
			AfxGetMainWnd()->SetTimer(IDT_HEART, 15000, NULL);

            //��ѯ��ǰ����
            PROCESS_DESCRIBE* pLoginSucess = (PROCESS_DESCRIBE*)pData;
            m_socket.Send(M_KEY, fun_querykey, NULL, 0);

            break;
        }


    //ע��
    case fun_regist_ok:
    case fun_regist_fail:
        {
            PROCESS_DESCRIBE* pDes = (PROCESS_DESCRIBE*)pData;
            AfxMessageBox(pDes->szDescribe);

            //�ر��׽���
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
            //ˢ�¶Ի����б�
            if(m_pKeyDlg)
            {

            }
            break;
        }

    case fun_querykey_ok:
        {

            QUERYKEY_SUCCESS* pKey = (QUERYKEY_SUCCESS*)pData;

            //�ŵ��û�ȫ��������
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
        {
            _ASSERTE(FALSE);
            break;
        }
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


#pragma optimize("g", off)

//����������Ϣ
bool CJLkitDoc::OnEventTCPSocketRead(CJLkitSocket* pSocket, const Tcp_Head& stTcpHead, VOID* pData, WORD wDataSize)
{
	VMProtectBegin("process key");

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
	
    VMProtectEnd();
    return true;
}

#pragma optimize("g", on)


void CJLkitDoc::OnLookkey()
{

    if(m_pKeyDlg == NULL)
    {
        m_pKeyDlg = new CDlgKey(AfxGetMainWnd());
    }

    m_pKeyDlg->DoModal();
    SafeDelete(m_pKeyDlg);
}
