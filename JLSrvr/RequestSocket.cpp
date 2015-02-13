// RequestSocket.cpp : implementation file
//

#include "stdafx.h"
#include "JLSrvr.h"
#include "RequestSocket.h"
#include "Request.h"
#include "JLSrvrDoc.h"
#include "DbMngr.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRequestSocket

CRequestSocket::CRequestSocket(CJLSrvrDoc* pDoc)
{
    m_pDoc = pDoc;
    m_pRequest = NULL;
    m_buf.SetSize(2048);
    NoRecvTimes = 0; //����û��Ӧ
}

CRequestSocket::~CRequestSocket()
{
    if(m_pRequest)
    {
        delete m_pRequest;
    }
}


// Do not edit the following lines, which are needed by ClassWizard.
#if 0
BEGIN_MESSAGE_MAP(CRequestSocket, CAsyncSocket)
    //{{AFX_MSG_MAP(CRequestSocket)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif  // 0

/////////////////////////////////////////////////////////////////////////////
// CRequestSocket member functions


BOOL CRequestSocket::ProcessRequest(BYTE* pRequestBuf)
{
    int fun = ((LOGIN_BUF*)pRequestBuf)->fun;

    //��¼�������������Ϣ
    m_pRequest->m_reqNums += 1;
    m_pRequest->strTime = GetNowTime();
    m_pRequest->strIp.Format(_T("%s:%d"), inet_ntoa(m_soaddr.sin_addr), m_soaddr.sin_port);

    //ȡ�������ͷֱ���
    switch(fun)
    {

        case fun_bugrep:
        {
            BUG_BUF* LoginBuf = (BUG_BUF*)pRequestBuf;
            m_pRequest->strType = _T("bug����");
            m_pRequest->strOther = LoginBuf->szBug;
            break;
        }

        case fun_login:
        {
            LOGIN_BUF* pLoginBuf = (LOGIN_BUF*)pRequestBuf;
            int nResult = CDbMngr::GetInstance()->GetPwRight(pLoginBuf->name, pLoginBuf->pw);

            m_pRequest->strUserName = pLoginBuf->name;
            m_pRequest->strType = _T("��¼");
            m_pRequest->strOther = pLoginBuf->pw;

            if(nResult == result_login_ok)
            {

                //����Ƿ��Ѿ���¼
                CRequestSocket* lpsock = m_pDoc->isLogined(pLoginBuf->name);
                if(lpsock)
                {
                    m_pRequest->strResult = _T("�Ѿ���½, �ߵ���ǰ����");
                    m_pDoc->ClientClose(lpsock);

                    nResult = result_login_ok;
                }
                else
                {
                    m_pRequest->strResult = _T("��֤���");
                }

                memcpy(m_szName, pLoginBuf->name, MAXLEN * sizeof(TCHAR));
                memcpy(m_szPw, pLoginBuf->pw, MAXLEN * sizeof(TCHAR));

            }
            else if(nResult == result_login_pwerror)
            {
                m_pRequest->strResult = _T("�������");
            }
            else if(nResult == result_login_notuser)
            {
                m_pRequest->strResult = _T("�û�������");
            }


            RET_BUF retbuf;
            retbuf.fun = fun;
            retbuf.result = nResult;

            m_cbOut = sizeof(RET_BUF);
            memcpy(m_buf.GetData(), &retbuf, m_cbOut);

            AsyncSelect(FD_WRITE | FD_CLOSE);
            break;
        }

        case fun_querykey:
        {
            LOGIN_BUF* pLoginBuf = (LOGIN_BUF*)pRequestBuf;

            std::vector<QUERYKEY_RET_BUF> querybuf;
            m_pRequest->strType = _T("��ѯ����");
            m_pRequest->strOther = _T("");
            if(CDbMngr::GetInstance()->Querykey(querybuf, pLoginBuf->name, pLoginBuf->pw))
            {
                m_pRequest->strResult = _T("���");

                //����������?
                m_buf.SetSize(sizeof(QUERYKEY_RET_BUF) * querybuf.size());
                TRACE1(_T("��ǰ��С: %d"), m_buf.GetSize());
                TRACE1(_T("�����ṹ: %d"), sizeof(QUERYKEY_RET_BUF));
                TRACE1(_T("��ǰcnSent: %d"), m_cbOut);

                for(int i = 0; i < querybuf.size(); i++)
                {
                    querybuf[i].fun = fun_querykey;
                    querybuf[i].result = result_ok;

                    m_cbOut += sizeof(QUERYKEY_RET_BUF);
                    memcpy((m_buf.GetData() + sizeof(QUERYKEY_RET_BUF) * i), &querybuf[i], sizeof(QUERYKEY_RET_BUF));
                }

            }
            else
            {
                m_pRequest->strResult = _T("ʧ��");

                RET_BUF retbuf;
                retbuf.fun = fun_querykey;
                retbuf.result = result_fail;

                m_cbOut = sizeof(RET_BUF);
                memcpy(m_buf.GetData(), &retbuf, m_cbOut);
            }

            AsyncSelect(FD_WRITE | FD_CLOSE);
            break;
        }

        case fun_unbindkey:
        {
            KEY_BUF* keybuf = (KEY_BUF*)pRequestBuf;

            m_pRequest->strType = _T("���");
            m_pRequest->strOther = keybuf->key;

            int nResult = CDbMngr::GetInstance()->Unbindkey(keybuf, &m_soaddr);

            RET_BUF retbuf;
            retbuf.fun = fun_unbindkey;
            retbuf.result = nResult;

            m_cbOut = sizeof(RET_BUF);
            memcpy(m_buf.GetData(), &retbuf, m_cbOut);
            switch(nResult)
            {
                case result_unbind_ok:
                {
                    m_pRequest->strResult = _T("���");
                    break;
                }
                case result_unbind_fail:
                {
                    m_pRequest->strResult = _T("ʧ��");
                    break;
                }
                case result_unbind_errtime:
                {
                    m_pRequest->strResult = _T("24����");
                    break;
                }
                case result_unbind_notuser:
                {
                    m_pRequest->strResult = _T("�������ʺ�");
                    break;
                }
                default:
                {
                    m_pRequest->strResult = _T("δ֪����");
                }
            }

            AsyncSelect(FD_WRITE | FD_CLOSE);
            break;
        }


        case fun_bindkey:
        {
            KEY_BUF* keybuf = (KEY_BUF*)pRequestBuf;

            m_pRequest->strType = _T("��");
            m_pRequest->strOther = keybuf->key;

            int nResult = CDbMngr::GetInstance()->Bindkey(keybuf, inet_ntoa(m_soaddr.sin_addr));

            RET_BUF retbuf;
            retbuf.fun = fun_bindkey;
            retbuf.result = nResult;

            switch(nResult)
            {
                case result_bind_ok:
                {
                    m_pRequest->strResult = _T("���");
                    break;
                }
                case result_bind_fail:
                {
                    m_pRequest->strResult = _T("ʧ��");
                    break;
                }
                case result_bind_errkey:
                {
                    m_pRequest->strResult = _T("���Ŵ���");
                    break;
                }
                case result_bind_used:
                {
                    m_pRequest->strResult = _T("��ʹ��");
                    break;
                }
                default:
                {
                    m_pRequest->strResult = _T("δ֪����");
                }
            }

            m_cbOut = sizeof(RET_BUF);
            memcpy(m_buf.GetData(), &retbuf, m_cbOut);
            AsyncSelect(FD_WRITE | FD_CLOSE);

            break;
        }

        case fun_regist:
        {
            REGIST_BUF* lpBuf = (REGIST_BUF*)pRequestBuf;

            m_pRequest->strType = _T("ע��");
            m_pRequest->strOther = lpBuf->name;

            int nResult = CDbMngr::GetInstance()->NewRegist(lpBuf->name,
                          lpBuf->pw, lpBuf->ip, _T(""), _T(""));

            if(nResult == FALSE)
            {
                m_pRequest->strResult = _T("ʧ��");
            }
            else
            {
                m_pRequest->strResult = _T("���");
            }

            RET_BUF retbuf;
            retbuf.fun = fun_regist;
            retbuf.result = nResult;

            m_cbOut = sizeof(RET_BUF);
            memcpy(m_buf.GetData(), &retbuf, m_cbOut);

            AsyncSelect(FD_WRITE | FD_CLOSE);
            break;
        }

        default:
        {
            m_pRequest->strType = _T("����");
            break;
        }

    }


    return TRUE;
}


void CRequestSocket::OnReceive(int nErrorCode)
{

    m_buf.SetSize(1024);
    int nBytes = Receive(m_buf.GetData(), m_buf.GetSize());

    switch(nBytes)
    {
        case SOCKET_ERROR:
        {
            if(GetLastError() == WSAEWOULDBLOCK)
            {
                AsyncSelect(FD_WRITE | FD_CLOSE);
            }
            else
            {
                ShutDown(both);
                m_pDoc->ClientClose(this);

            }
            break;
        }

        case 0:
        {
            //�����Ѿ����ر�
            ShutDown(both);
            m_pDoc->ClientClose(this);
            break;
        }

        default:
        {
            ProcessRequest(m_buf.GetData());
            m_pDoc->DocHit(HINT_REQUEST, m_pRequest);
        }
    }
}

int CRequestSocket::Send(const void* lpBuf, int nBufLen, int nFlags)
{
    //������Ƭ����
    BYTE* pBack = new BYTE[nBufLen];
    memcpy(pBack, lpBuf, nBufLen);

    //�����ݼ���
    for(int i = 0; i < nBufLen; i++)
    {
        BYTE q = (BYTE)i % 3;
        pBack[i] ^= 0x93;
        pBack[i] += q;
    }

    int nBytes = CAsyncSocket::Send(pBack, nBufLen, nFlags);


    delete []pBack;
    return nBytes;
}

int CRequestSocket::Receive(void* lpBuf, int nBufLen, int nFlags)
{

    int result = CAsyncSocket::Receive(lpBuf, nBufLen, nFlags);
    if(result == SOCKET_ERROR)
    {
        return result;
    }


    //�����ݽ���
    BYTE* temp = (BYTE*)lpBuf;
    for(int i = 0; i < nBufLen; i++)
    {
        BYTE q = (BYTE)i % 3;
        temp[i] -= q;
        temp[i] ^= 0x93;
    }

    return result;

}

CString CRequestSocket::GetNowTime()
{
    return CTime::GetCurrentTime().Format(_T("%y/%m/%d %H:%M:%S"));
}

void CRequestSocket::OnClose(int nErrorCode)
{
    if(nErrorCode != 0)
    {
        return;
    }

    m_pRequest->strType = _T("����");
    m_pRequest->strTime = GetNowTime();
    m_pRequest->strOther = _T("");
    m_pRequest->strResult = _T("���");
    m_pDoc->ClientClose(this);
}

void CRequestSocket::InitAccept()
{

    if(m_pRequest == NULL)
    {
        m_pRequest = new CRequest;
    }


    if(m_pRequest)
    {
        m_pRequest->m_reqNums = 0;
        m_pRequest->strUserName = _T("");
        m_pRequest->strType = _T("����");
        m_pRequest->strTime = GetNowTime();
        m_pRequest->strOther = _T("");
        m_pRequest->strResult = _T("���");
        m_pRequest->strIp.Format(_T("%s:%d"), inet_ntoa(m_soaddr.sin_addr), m_soaddr.sin_port);
        m_pDoc->DocHit(HINT_ACEEPT, m_pRequest);
    }
    else
    {
        delete this;
    }

}

void CRequestSocket::OnSend(int nErrorCode)
{
    int nBytes = Send(m_buf.GetData(), m_cbOut);
    if(nBytes == SOCKET_ERROR)
    {
        if(GetLastError() != WSAEWOULDBLOCK)
        {
            ShutDown(both);
            m_pDoc->ClientClose(this);
        }
        else
        {
            AsyncSelect(FD_WRITE | FD_CLOSE);
        }
    }
    else if(nBytes < m_cbOut)
    {
        // ����ʣ����ֽ�
        m_buf.RemoveAt(0, nBytes);
        m_cbOut -= nBytes;

        // ׼����һ��д��
        AsyncSelect(FD_WRITE | FD_CLOSE);
    }
    else
    {
        //�������, �����ȴ�����
        m_cbOut = 0;
        AsyncSelect(FD_READ | FD_CLOSE);
    }
}
