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
    //����
public:
    CIniFile();
    virtual ~CIniFile();
    BOOL Open(LPCTSTR lpszFileName);

    //���浽�ļ�
    void SaveToFile();


    //ĳ���Ƿ���ĳֵ
    BOOL isHave(LPCTSTR lpAppName, LPCTSTR lpKeyName, LPCTSTR lpValue);

    //д�ַ�
    BOOL WriteString(LPCTSTR lpAppName, LPCTSTR lpKeyName, LPCTSTR lpString);

    //���ַ�
    TCHAR* ReadString(LPCTSTR lpAppName, LPCTSTR lpKeyName, LPCTSTR szDefault = NULL);

    //������
    UINT ReadInt(LPCTSTR lpAppName, LPCTSTR lpKeyName, INT nValue);
    
    //д����
    BOOL WriteInt(LPCTSTR lpAppName, LPCTSTR lpKeyName, INT nValue);
    
private:
    BOOL m_bIsUnicode;
    LineVector m_data;
};

#endif // !defined(AFX_CIniFile_H__13B64092_70AB_41ED_9279_55D409F1C176__INCLUDED_)
