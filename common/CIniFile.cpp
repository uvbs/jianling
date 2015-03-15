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

#define UNICODE_HEADER	0xfeff

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
    if(CStdioFile::Open(lpszFileName, CFile::modeReadWrite | CFile::shareDenyNone) == FALSE)
    {
        return FALSE;
    }

    //判断是不是unicode文件
    WORD hdr = 0;
    Read(&hdr, sizeof(WORD));

    if(hdr == UNICODE_HEADER)
    {
        m_bIsUnicode = TRUE;
    }

    return TRUE;
}


TCHAR* CIniFile::GetProfileString(TCHAR* strSec, TCHAR* strKey, TCHAR* strDefault)
{
    DWORD dwLen = BUFSIZ;
    TCHAR*	lpszBuf = new TCHAR[dwLen];
    DWORD dwReads = ::GetPrivateProfileString(strSec, strKey, strDefault, lpszBuf, dwLen,
                    (LPCTSTR) GetFilePath());

    while((dwReads + 1) >= dwLen)
    {
        dwLen += BUFSIZ;
        delete lpszBuf;
        lpszBuf = new TCHAR[dwLen];
        dwReads = ::GetPrivateProfileString(strSec, strKey, strDefault, lpszBuf, dwLen,
                                            (LPCTSTR) GetFilePath());
    }

    return lpszBuf;
}


BOOL CIniFile::isHave(TCHAR szSec[], TCHAR szKey[], TCHAR* name)
{
    TCHAR*	lpszTemp = GetProfileString(szSec, szKey);
    BOOL bFind = FALSE;
    TCHAR*	token = _tcstok(lpszTemp, _T(";"));

    while(token != NULL)
    {
        if(_tcscmp(token, name) == 0)
        {
            bFind = TRUE;
            break;
        }
        else
        {
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
    for(std::list<TCHAR*>::iterator it = m_data.begin(); it != m_data.end(); it++)
    {
        _fputts(*it, m_lpfile);
    }
}

void CIniFile::Close()
{
    if(m_lpfile)
    {
        fclose(m_lpfile);
    }
}