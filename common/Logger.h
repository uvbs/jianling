#if !defined _LOGGER_H
	#define _LOGGER_H

	#if _MSC_VER > 1000
		#pragma once
	#endif // _MSC_VER > 1000
class CLock;
class Logger
{
public:
	Logger(TCHAR *name = _T("Logger"), UCHAR type = 0);
	~ Logger();

	void logva(const TCHAR *pattern, va_list vp);
	void info(const TCHAR *szText, ...);

	/*–¥»’÷æ*/
	void logdv(const TCHAR szFormat[], ...);
	void logdvHex(BYTE szFormat[]);

private:
	CLock *m_lpMsgMut;

	FILE *fp_console;
	FILE *fp_file;
	FILE *fp_dbview;
	int m_day;

	#ifdef _UNICODE
	std::wstring m_name;
	std::wstring m_file;
	#else
	std::string m_name;
	std::string m_file;
	#endif

};

#endif
