// ClientSocket.cpp: implementation of the CClientSocket class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "JLkitDoc.h"
#include "JLkitSocket.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

IMPLEMENT_DYNAMIC(CJLkitSocket, CSocket)

CJLkitSocket::CJLkitSocket(CJLkitDoc* pDoc)
{
    m_pDoc = pDoc;
}

CJLkitSocket::~CJLkitSocket()
{

}


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




BOOL CJLkitSocket::BindKey(CString& strKey)
{

    KEY_BUF keybuf;
    keybuf.fun = fun_bindkey;
    _tcsncpy(keybuf.key, (LPCTSTR)strKey, KEYLEN);
    _tcsncpy(keybuf.name, (LPCTSTR)m_UserInfo.name, MAXLEN);
    _tcsncpy(keybuf.pw, (LPCTSTR)m_UserInfo.pw, MAXLEN);
    //	memcpy(&keybuf.pcdata, &pcinfo.stPcData, sizeof(PCDATA));

    Send(&keybuf, sizeof(KEY_BUF));
    return TRUE;
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


BOOL CJLkitSocket::Querykey()
{
    LOGIN_BUF keybuf;
    keybuf.fun = fun_querykey;
    _tcsncpy(keybuf.name, (LPCTSTR)m_UserInfo.name, MAXLEN);
    _tcsncpy(keybuf.pw, (LPCTSTR)m_UserInfo.pw, MAXLEN);
    Send(&keybuf, sizeof(LOGIN_BUF));
    return TRUE;
}


BOOL CJLkitSocket::LoginSrv(CString& strName, CString& strPassWord)
{

    //将用户名和密码放到发包结构中
    m_UserInfo.fun = fun_login;
    _tcsncpy(m_UserInfo.name, (LPCTSTR)strName, MAXLEN);
    _tcsncpy(m_UserInfo.pw, (LPCTSTR)strPassWord, MAXLEN);

    int nBytes = Send(&m_UserInfo, sizeof(LOGIN_BUF));

    return (nBytes != SOCKET_ERROR);
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