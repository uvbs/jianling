#include "stdafx.h"
#include "logger.h"


Logger::Logger()
{

}

//析构函数
Logger::~Logger()
{
    if(NULL != fp_file)
    {
        fclose(fp_file);
        fp_file = NULL;
    }

}


void Logger::info(const TCHAR* szText, ...)
{
    va_list vp;

    va_start(vp, szText);
    logva(szText, vp);
    va_end(vp);
}



void Logger::logva(const TCHAR* pattern, va_list vp)
{

    struct tm* now;

    time_t ltime;
    time(&ltime);

    now = localtime(&ltime);
    if(NULL == now) return;

    SYSTEMTIME system;
    GetLocalTime(&system);

    //临界区
    m_MsgMut.Lock();

    if(NULL != fp_file)
    {
        _ftprintf(fp_file, _T("%04d/%02d/%02d "), now->tm_year + 1900, now->tm_mon + 1, now->tm_mday);
        _ftprintf(fp_file, _T("%02d:%02d:%02d  "), system.wHour, system.wMinute, system.wSecond);
        _vftprintf(fp_file, pattern, vp);
        _ftprintf(fp_file, _T("\n"));
        fflush(fp_file);
    }

    m_MsgMut.Unlock();
}

BOOL Logger::open(const TCHAR* pFileName, TCHAR *pMode)
{

    fp_file = _tfopen(pFileName, pMode);
    return (fp_file != NULL);
}