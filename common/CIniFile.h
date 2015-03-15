// CIniFile.h: interface for the CIniFile class.
//
//////////////////////////////////////////////////////////////////////
#if !defined(AFX_CIniFile_H__13B64092_70AB_41ED_9279_55D409F1C176__INCLUDED_)
#define AFX_CIniFile_H__13B64092_70AB_41ED_9279_55D409F1C176__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include <list>

class CIniFile : public CStdioFile
{
public:
    CIniFile();
    virtual ~CIniFile();
    BOOL Open(LPCTSTR lpszFileName);

    void SaveToFile();


    //BOOL ReadStr(TCHAR szSection[], TCHAR szKey[], std::vector<tstring> *strVec);
    BOOL ReadInt(TCHAR szSection[], TCHAR szKey[], int* lpnValue);
    BOOL WriteStr(TCHAR szSection[], TCHAR szKey[], CString);
    BOOL WriteStr(TCHAR szSection[], TCHAR szKey[], int nValue);
    TCHAR* GetProfileString(TCHAR strSec[], TCHAR strKey[], TCHAR szDefault[] = NULL);
    BOOL isHave(TCHAR szSec[], TCHAR szKey[], TCHAR* name);
    void Close();

private:
    BOOL m_bIsUnicode;
    std::list<TCHAR*> m_data;
    FILE* m_lpfile;

};

#endif // !defined(AFX_CIniFile_H__13B64092_70AB_41ED_9279_55D409F1C176__INCLUDED_)
