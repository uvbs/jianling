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
    ~Logger();

    BOOL open(const TCHAR* pFileName, TCHAR* pMode = _T("at"));
    void info(const TCHAR* szText, ...);

protected:
    void logva(const TCHAR* pattern, va_list vp);

private:
    std::basic_string<TCHAR> m_strFileName;
    CLock* m_lpMsgMut;
    FILE* fp_file;
};

#endif
