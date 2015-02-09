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

CCVPNFile::CCVPNFile(): CStdioFile()
{
    dwMaxLine = 0;
}

CCVPNFile::~CCVPNFile()
{

}


BOOL CCVPNFile::Open(TCHAR szFilePath[])
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


void CCVPNFile::DisConnectVPN()
{
    CString strLine;
    strLine.Format(_T("cmd /c rasdial \"VPN ����\" /disconnect >NUL"));
    ::WinExec((LPCTSTR)strLine, SW_HIDE);
}

//һֱ����, ֱ���ҵ�һ�����õ�
void CCVPNFile::AlwaysConnect()
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
            TRACE1(_T("����һ��vpn����, %d"), nRet);
        }
    }
}


int CCVPNFile::ConnectVPN()
{
    //Ҫ�ǵ�ĩβ�ľ����¿�ʼ
    if(curLine == NULL)
    {
        curLine = cStrList.GetHeadPosition();
    }

    CString strLine = cStrList.GetNext(curLine);

    TCHAR szPw[BUFSIZ];
    TCHAR szAc[BUFSIZ];
    TCHAR szIp[BUFSIZ];
    _stscanf((LPCTSTR)strLine, _T("%s %s %s"), szAc, szPw, szIp);

    strLine.Format(_T("rasdial \"VPN ����\" %s %s /PHONE:%s"),
                   szAc, szPw, szIp);
    int nRet = ::_tsystem(strLine);
    strLine.Format(_T("ipconfig /flushdns"));
    ::_tsystem(strLine);

    return nRet;
}
