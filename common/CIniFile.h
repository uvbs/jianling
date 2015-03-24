// CIniFile.h: interface for the CIniFile class.
//
//////////////////////////////////////////////////////////////////////
#if !defined(AFX_CIniFile_H__13B64092_70AB_41ED_9279_55D409F1C176__INCLUDED_)
#define AFX_CIniFile_H__13B64092_70AB_41ED_9279_55D409F1C176__INCLUDED_

#if _MSC_VER > 1000
    #pragma once
#endif // _MSC_VER > 1000


#include <list>


typedef std::list<LPVOID> LineVector;
typedef std::list<LPVOID>::iterator LineIterator;

class CIniFile : public CStdioFile
{
    //构造
public:
    CIniFile();
    virtual ~CIniFile();
    BOOL Open(LPCTSTR lpszFileName);

    //保存到文件
    void SaveToFile();


    //某键是否有某值
    BOOL isHave(LPCTSTR lpAppName, LPCTSTR lpKeyName, LPCTSTR lpValue);

    //写字符
    BOOL WriteString(LPCTSTR lpAppName, LPCTSTR lpKeyName, LPCTSTR lpString);

    //读字符
    TCHAR* ReadString(LPCTSTR lpAppName, LPCTSTR lpKeyName, LPCTSTR szDefault = NULL);

    //读整型
    UINT ReadInt(LPCTSTR lpAppName, LPCTSTR lpKeyName, INT nValue);
    
    //写整型
    BOOL WriteInt(LPCTSTR lpAppName, LPCTSTR lpKeyName, INT nValue);
    
private:
    BOOL m_bIsUnicode;
    LineVector m_data;
};

#endif // !defined(AFX_CIniFile_H__13B64092_70AB_41ED_9279_55D409F1C176__INCLUDED_)
