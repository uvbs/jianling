#include "stdafx.h"
#include "Lock.h"
#include "logger.h"




Logger::Logger(TCHAR* pFileName, TCHAR *pMode)
{
//     InitValue();
//     if(!open(pFileName, pMode))
//     {
//         throw runtime_error("File Open Error");
//     }
}

Logger::Logger()
{
    InitValue();
}

void Logger::InitValue()
{
    m_lpMsgMut = NULL;
}

//析构函数
Logger::~Logger()
{
    if(NULL != fp_file)
    {
        fclose(fp_file);
        fp_file = NULL;
    }

    if(m_lpMsgMut != NULL)
    {
        delete m_lpMsgMut;
        m_lpMsgMut = NULL;
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
    m_lpMsgMut->lock();

    if(NULL != fp_file)
    {
        _ftprintf(fp_file, _T("%04d/%02d/%02d "), now->tm_year + 1900, now->tm_mon + 1, now->tm_mday);
        _ftprintf(fp_file, _T("%02d:%02d:%02d.%03d "), system.wHour, system.wMinute, system.wSecond, system.wMilliseconds);
        _vftprintf(fp_file, pattern, vp);
        _ftprintf(fp_file, _T("\n"));
        fflush(fp_file);
    }

    m_lpMsgMut->unlock();
}

BOOL Logger::open(TCHAR* pFileName, TCHAR *pMode)
{
    if(m_lpMsgMut == NULL)
        m_lpMsgMut = new CLock;

    fp_file = _tfopen(pFileName, pMode);
    return (fp_file != NULL);
}