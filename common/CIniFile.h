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
    //构造
public:
    CIniFile();
    virtual ~CIniFile();
    BOOL Open(LPCTSTR lpszFileName);

    //保存到文件
    void SaveToFile();


    BOOL ReadStr(LPCTSTR lpAppName, LPCTSTR lpKeyName, LPCTSTR lpDefault);
    UINT ReadInt(LPCTSTR lpAppName, LPCTSTR lpKeyName, INT nDefault);
    

    
    BOOL isHave(TCHAR szSec[], TCHAR szKey[], TCHAR* name);

    //写入INI
    BOOL WriteString(LPCTSTR lpAppName, LPCTSTR lpKeyName, LPCTSTR lpString);

    //读取INI
    TCHAR* ReadString(LPCTSTR lpAppName, LPCTSTR lpKeyName, LPCTSTR szDefault = NULL);

private:
    BOOL m_bIsUnicode;
    std::list<TCHAR*> m_data;
};

#endif // !defined(AFX_CIniFile_H__13B64092_70AB_41ED_9279_55D409F1C176__INCLUDED_)
