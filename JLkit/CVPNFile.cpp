// CVPNFile.cpp: implementation of the CCVPNFile class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "jlkit.h"
#include "CVPNFile.h"


#ifdef _DEBUG
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
    #define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CVpnFile::CVpnFile(): CStdioFile()
{
    dwMaxLine = 0;
}

CVpnFile::~CVpnFile()
{

}


BOOL CVpnFile::Open(TCHAR szFilePath[])
{
    if(CStdioFile::Open(szFilePath, CFile::modeRead))
    {
        CString strLine;
        while(ReadString(strLine))
        {
            cStrList.AddTail(strLine);
        }

        curLine = cStrList.GetHeadPosition();
        return TRUE;
    }

    return FALSE;
}


void CVpnFile::DisConnectVPN()
{
    CString strLine;
    strLine.Format(_T("cmd /c rasdial \"VPN 连接\" /disconnect >NUL"));

    LPCSTR lpszLine;
#ifdef UNICODE
    USES_CONVERSION;
    lpszLine = W2CA((LPCTSTR)strLine);
#else
    lpszLine = (LPCTSTR)strLine;
#endif

    ::WinExec(lpszLine, SW_HIDE);
}

//一直连接, 直到找到一个能用的
void CVpnFile::AlwaysConnect()
{
    DisConnectVPN();
    Sleep(4000);
    while(1)
    {
        int nRet = ConnectVPN();
        if(nRet == 0 || nRet == 1)
        {
            Sleep(4000);
            break;

        }
        else
        {
            TRACE1("连接一个vpn出错, %d", nRet);
        }
    }
}


int CVpnFile::ConnectVPN()
{
    //要是到末尾的就重新开始
    if(curLine == NULL)
    {
        curLine = cStrList.GetHeadPosition();
    }

    CString strLine = cStrList.GetNext(curLine);

    TCHAR szPw[BUFSIZ];
    TCHAR szAc[BUFSIZ];
    TCHAR szIp[BUFSIZ];
    _stscanf((LPCTSTR)strLine, _T("%s %s %s"), szAc, szPw, szIp);

    strLine.Format(_T("rasdial \"VPN 连接\" %s %s /PHONE:%s"),
                   szAc, szPw, szIp);
    int nRet = ::_tsystem(strLine);
    strLine.Format(_T("ipconfig /flushdns"));
    ::_tsystem(strLine);

    return nRet;
}
