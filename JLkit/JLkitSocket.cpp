// ClientSocket.cpp: implementation of the CClientSocket class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "JLkitDoc.h"
#include "JLkitSocket.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////



CJLkitSocket* CJLkitSocket::_Instance = NULL;
CJLkitSocket* CJLkitSocket::GetInstance(CJLkitDoc* pDoc)
{
    if(_Instance == NULL)
    {
        _Instance = new CJLkitSocket(pDoc);
    }

    return _Instance;
}


CJLkitSocket::CJLkitSocket(CJLkitDoc* pDoc)
{
    m_pDoc = pDoc;
}

CJLkitSocket::~CJLkitSocket()
{

}


// Do not edit the following lines, which are needed by ClassWizard.
#if 0
BEGIN_MESSAGE_MAP(CJLkitSocket, CAsyncSocket)
    //{{AFX_MSG_MAP(CJLkitSocket)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif  // 0




void CJLkitSocket::OnConnect(int nErrorCode)
{

    m_pDoc->ConnectResult(nErrorCode);
}

void CJLkitSocket::OnReceive(int nErrorCode)
{
    m_pDoc->ProcessRecevice();
}

void CJLkitSocket::Heart()
{
    BYTE b;
    Send(&b, sizeof(BYTE));
}


BOOL CJLkitSocket::ConnectSrv(const CString& strHostName, int nPort)
{

    if(Connect(strHostName, nPort))
    {
        return TRUE;
    }
    else
    {
        if(GetLastError() == WSAEWOULDBLOCK)
        {
            return TRUE;
        }
    }

    return FALSE;
}


int CJLkitSocket::Send(const void* lpBuf, int nBufLen, int nFlags /* = 0 */)
{

    //备份这片数据
    BYTE* pBack = new BYTE[nBufLen];
    memcpy(pBack, lpBuf, nBufLen);

    //对数据加密
    for(int i = 0; i < nBufLen; i++)
    {
        BYTE q = (BYTE)i % 3;
        pBack[i] ^= 0x93;
        pBack[i] += q;
    }

    int nBytes = CAsyncSocket::Send(pBack, nBufLen, nFlags);
    if(nBytes == SOCKET_ERROR)
    {
        ShutDown(both);
    }

    delete []pBack;
    return nBytes;
}


int CJLkitSocket::Receive(void* lpBuf, int nBufLen, int nFlags /* = 0 */)
{
    int i;
    BYTE* temp = (BYTE*)lpBuf;

    int nBytes = CAsyncSocket::Receive(lpBuf, nBufLen, nFlags);
    if(nBytes == SOCKET_ERROR)
    {
        ShutDown(both);
    }
    else
    {
        //对数据解密
        for(i = 0; i < nBytes; i++)
        {
            BYTE q = (BYTE)i % 3;
            temp[i] -= q;
            temp[i] ^= 0x93;
        }
    }

    return nBytes;
}




void CJLkitSocket::BindKey(CString& strKey)
{

    KEY_BUF keybuf;
    keybuf.fun = fun_bindkey;
    _tcsncpy(keybuf.key, (LPCTSTR)strKey, KEYLEN);
    _tcsncpy(keybuf.name, (LPCTSTR)m_UserInfo.name, MAXLEN);
    _tcsncpy(keybuf.pw, (LPCTSTR)m_UserInfo.pw, MAXLEN);
    //  memcpy(&keybuf.pcdata, &pcinfo.stPcData, sizeof(PCDATA));

    Send(&keybuf, sizeof(KEY_BUF));
}


void CJLkitSocket::Unbindkey(CString& strKey)
{
    KEY_BUF keybuf;
    keybuf.fun = fun_unbindkey;
    _tcsncpy(keybuf.key, (LPCTSTR)strKey, KEYLEN);
    _tcsncpy(keybuf.name, (LPCTSTR)m_UserInfo.name, MAXLEN);
    _tcsncpy(keybuf.pw, (LPCTSTR)m_UserInfo.pw, MAXLEN);
    Send(&keybuf, sizeof(KEY_BUF));
}

void CJLkitSocket::Register(CString& strName, CString& strPw, CString& strIP)
{
    REGIST_BUF registbuf;
    registbuf.fun = fun_regist;

    memcpy(registbuf.ip, (LPCTSTR)strIP, MAXLEN);
    memcpy(registbuf.name, (LPCTSTR)strName, MAXLEN);
    memcpy(registbuf.pw, (LPCTSTR)strPw, MAXLEN);

    // memcpy(&registbuf.pcdata, &pcinfo.stPcData, sizeof(PCDATA));
    Send(&registbuf, sizeof(REGIST_BUF));
}

void CJLkitSocket::Querykey()
{
    LOGIN_BUF keybuf;
    keybuf.fun = fun_querykey;
    _tcsncpy(keybuf.name, (LPCTSTR)m_UserInfo.name, MAXLEN);
    _tcsncpy(keybuf.pw, (LPCTSTR)m_UserInfo.pw, MAXLEN);
    Send(&keybuf, sizeof(LOGIN_BUF));

}

void CJLkitSocket::ModifyBind(CString& strName, CString& strPw, CString& strOld, CString& strNew)
{
    //将注册数据打包
    MODIFYBIND_BUF modifybuf;
    modifybuf.fun = fun_mbind;

    memcpy(modifybuf.new_bind, (LPCTSTR)strNew, MAXLEN);
    memcpy(modifybuf.old_bind, (LPCTSTR)strOld, MAXLEN);
    memcpy(modifybuf.name, (LPCTSTR)strName, MAXLEN);
    memcpy(modifybuf.pw, (LPCTSTR)strPw, MAXLEN);

    Send(&modifybuf, sizeof(MODIFYBIND_BUF));

}


int CJLkitSocket::LoginSrv(CString& strName, CString& strPassWord)
{

    //将用户名和密码放到发包结构中
    m_UserInfo.fun = fun_login;
    _tcsncpy(m_UserInfo.name, (LPCTSTR)strName, MAXLEN);
    _tcsncpy(m_UserInfo.pw, (LPCTSTR)strPassWord, MAXLEN);

    return Send(&m_UserInfo, sizeof(LOGIN_BUF));
}

void CJLkitSocket::Reportbug(CString& strBug)
{

    BUG_BUF loginbuf;
    loginbuf.fun = fun_bugrep;
    _tcsncpy(loginbuf.name, (LPCTSTR)m_UserInfo.name, MAXLEN);
    _tcsncpy(loginbuf.pw, (LPCTSTR)m_UserInfo.pw, MAXLEN);
    _tcsncpy(loginbuf.szBug, (LPCTSTR)strBug, BUFSIZ);

    Send(&loginbuf, sizeof(BUG_BUF));
}

void CJLkitSocket::OnSend(int nErrorCode)
{
    // TODO: Add your specialized code here and/or call the base class
    TRACE0(_T("OnSend"));
    CAsyncSocket::OnSend(nErrorCode);
}
