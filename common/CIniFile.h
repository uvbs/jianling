// CIniFile.h: interface for the CCIniFile class.
//
//////////////////////////////////////////////////////////////////////
#if !defined(AFX_CINIFILE_H__13B64092_70AB_41ED_9279_55D409F1C176__INCLUDED_)
	#define AFX_CINIFILE_H__13B64092_70AB_41ED_9279_55D409F1C176__INCLUDED_

	#if _MSC_VER > 1000
		#pragma once
	#endif // _MSC_VER > 1000
class CCIniFile :
	public CStdioFile
{
public:
	CCIniFile();
	virtual ~CCIniFile();

	BOOL Open(LPCTSTR lpszFileName);

	//
	//BOOL ReadStr(TCHAR szSection[], TCHAR szKey[], std::vector<tstring> *strVec);
	BOOL ReadInt(TCHAR szSection[], TCHAR szKey[], int *lpnValue);
	BOOL WriteStr(TCHAR szSection[], TCHAR szKey[], CString);
	BOOL WriteStr(TCHAR szSection[], TCHAR szKey[], int nValue);
	TCHAR *GetProfileString(TCHAR strSec[], TCHAR strKey[], TCHAR szDefault[] = NULL);
	BOOL isHave(TCHAR szSec[], TCHAR szKey[], TCHAR *name);

private:
	BOOL m_bIsUnicode;
};

#endif // !defined(AFX_CINIFILE_H__13B64092_70AB_41ED_9279_55D409F1C176__INCLUDED_)
