#if !defined _LOGGER_H
#define _LOGGER_H

#if _MSC_VER > 1000
    #pragma once
#endif // _MSC_VER > 1000

#include <string>
#include "Lock.h"


#include <stdexcept>
using std::runtime_error;

class Logger
{
public:
    Logger();
    Logger(TCHAR* pFileName, TCHAR* pMode = _T("at"));
    ~Logger();
    void InitValue();


    BOOL open(TCHAR* pFileName, TCHAR* pMode = _T("at"));

    void info(const TCHAR* szText, ...);

protected:
    void logva(const TCHAR* pattern, va_list vp);


#ifdef _UNICODE
    typedef std::wstring tstring;
#else
    typedef std::string tstring
#endif

private:
    CLock* m_lpMsgMut;
    FILE* fp_file;
    tstring m_strFileName;
};

#endif
