#include "stdafx.h"
#include "Lock.h"
#include "logger.h"


Logger::Logger(TCHAR *name, UCHAR type):
fp_console(NULL), fp_file(NULL)
{
    
    if(type == 0){
        fp_console = stdout;
    }
    else if(type == 1){
        m_file = _T("asdf");
    }

	m_name = name;
	
	m_day = 0;
}

//Îö¹¹º¯Êý
Logger::~Logger()
{
	if(NULL != fp_file){
		fclose(fp_file);
		fp_file = NULL;
	}
}


void Logger::info(const TCHAR *szText, ...)
{
    va_list vp;
    
    va_start(vp,szText);
    logva(szText,vp);
    va_end(vp);
}

void Logger::logdvHex(BYTE szFormat[])
{
    TCHAR szApp[BUFSIZ] = {0};
    wsprintf(szApp, _T("[%s] "), m_name.c_str());

	TCHAR szHex[BUFSIZ] = {0};
	for(int i = 0; i < (strlen((char *)szFormat) + 10); i++){
		TCHAR temp[4] = {0};
		wsprintf(temp, _T("%02x"), szFormat[i]);
		_tcscat(szHex, temp);
		_tcscat(szHex, _T(" "));
	}



    _tcscat(szApp, szHex);
    OutputDebugString(szApp);

}


void Logger::logdv(const TCHAR szFormat[], ...)
{
    TCHAR buffer[BUFSIZ] = {0};
    
    TCHAR szApp[BUFSIZ] = {0};
    
    wsprintf(szApp, _T("[%s] "), m_name.c_str());
    
    va_list argptr;
    va_start(argptr, szFormat);
    wvsprintf(buffer, szFormat, argptr);
    va_end(argptr);
    
    _tcscat(szApp, buffer);
    OutputDebugString(szApp);

}


void Logger::logva(const TCHAR *pattern, va_list vp)
{
	TCHAR szName[MAX_PATH];

	struct tm *now;

	time_t ltime;
	time(&ltime);

	now = localtime(&ltime);
	if(NULL == now)
		return;

	SYSTEMTIME system;
	GetLocalTime(&system);

	m_lpMsgMut->lock();

	if(!m_file.empty())
	{
		if(m_day != now->tm_mday)
		{
			if(NULL != fp_file)
			{
				fclose(fp_file);
			}

			m_day = now->tm_mday;

			_sntprintf(szName, sizeof(szName)/sizeof(TCHAR), _T("%s%04d%02d%02d.log"),
				m_file.c_str(), now->tm_year + 1900, now->tm_mon + 1, now->tm_mday);

			fp_file = _tfopen(szName, _T("at"));
		}
	}

	if(NULL != fp_console)
	{
		_ftprintf(fp_console, _T("[%s] "), m_name.c_str());
		_ftprintf(fp_console, _T("%04d/%02d/%02d "), now->tm_year + 1900, now->tm_mon + 1, now->tm_mday);
		_ftprintf(fp_console, _T("%02d:%02d:%02d.%03d "), system.wHour, system.wMinute, system.wSecond, system.wMilliseconds);
		_vftprintf(fp_console, pattern, vp);
		_ftprintf(fp_console, _T("\n"));
		fflush(fp_console);
	}

	if(NULL != fp_file)
	{
		_ftprintf(fp_file, _T("[%s] "), m_name.c_str());
		_ftprintf(fp_file, _T("%04d/%02d/%02d "), now->tm_year + 1900, now->tm_mon + 1, now->tm_mday);
		_ftprintf(fp_file, _T("%02d:%02d:%02d.%03d "), system.wHour, system.wMinute, system.wSecond, system.wMilliseconds);
		_vftprintf(fp_file, pattern, vp);
		_ftprintf(fp_file, _T("\n"));
		fflush(fp_file);
	}

	m_lpMsgMut->unlock();
}