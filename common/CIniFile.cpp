// CIniFile.cpp: implementation of the CIniFile class.
//
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "CIniFile.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
    #define new DEBUG_NEW
#endif

#define UNICODE_HEADER  0xfeff

//////////////////////////////////////////////////////////////////////

// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CIniFile::CIniFile() :
    CStdioFile()
{
    m_bIsUnicode = FALSE;
}


CIniFile::~CIniFile()
{
    Close();
}


BOOL CIniFile::Open(LPCTSTR lpszFileName)
{
    if(CStdioFile::Open(lpszFileName, CFile::modeReadWrite | CFile::shareDenyNone) == FALSE) {
        return FALSE;
    }

    //判断是不是unicode文件
    WORD hdr = 0;
    Read(&hdr, sizeof(WORD));

    if(hdr == UNICODE_HEADER) {
        m_bIsUnicode = TRUE;
    }
    else {
        SeekToBegin();
    }

    return TRUE;
}


TCHAR* CIniFile::ReadString(LPCTSTR lpAppName, LPCTSTR lpKeyName, LPCTSTR szDefault)
{
    DWORD dwLen = BUFSIZ;
    TCHAR*  lpszBuf = new TCHAR[dwLen];
    DWORD dwReads = ::GetPrivateProfileString(lpAppName, lpKeyName, szDefault, lpszBuf, dwLen,
                    (LPCTSTR) GetFilePath());

    while((dwReads + 1) >= dwLen) {
        dwLen += BUFSIZ;
        delete lpszBuf;
        lpszBuf = new TCHAR[dwLen];
        dwReads = ::GetPrivateProfileString(lpAppName, lpKeyName, szDefault, lpszBuf, dwLen,
                                            (LPCTSTR)m_strFileName);
    }


    return lpszBuf;
}


BOOL CIniFile::isHave(LPCTSTR lpAppName, LPCTSTR lpKeyName, LPCTSTR lpValue)
{
    TCHAR*  lpszTemp = ReadString(lpAppName, lpKeyName);
    BOOL bFind = FALSE;

    TCHAR*  token = _tcstok(lpszTemp, _T(";"));
    while(token != NULL) {
        if(_tcscmp(token, lpValue) == 0) {
            bFind = TRUE;
            break;
        }

        // Get next token:
        token = _tcstok(NULL, _T(";"));
    }

    delete[] lpszTemp;
    return bFind;
}

void CIniFile::SaveToFile()
{
    //遍历所有行到文件中
    for(LineIterator it = m_data.begin(); it != m_data.end(); it++) {

    }
}

BOOL CIniFile::WriteString(LPCTSTR lpAppName, LPCTSTR lpKeyName, LPCTSTR lpString)
{
    return ::WritePrivateProfileString(lpAppName, lpKeyName, lpString, (LPCTSTR)m_strFileName);
}

UINT CIniFile::ReadInt(LPCTSTR lpAppName, LPCTSTR lpKeyName, INT nDefault)
{
    return ::GetPrivateProfileInt(lpAppName, lpKeyName, nDefault, (LPCTSTR)m_strFileName);
}

BOOL CIniFile::WriteInt(LPCTSTR lpAppName, LPCTSTR lpKeyName, INT nValue)
{
    //准备变量
    TCHAR szInt[BUFSIZ / 4] = {0};

    _itot(nValue, szInt, 10);
    TRACE(_T("%s"), szInt);
        TRACE(_T("%s"), (LPCTSTR)m_strFileName);
    return ::WritePrivateProfileString(lpAppName, lpKeyName, szInt, (LPCTSTR)m_strFileName);
}