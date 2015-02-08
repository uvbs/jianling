// GameHepler.h: interface for the GameHepler class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GAMEHEPLER_H__C5E39275_71A5_4307_8D63_54E7E3CB21E0__INCLUDED_)
#define AFX_GAMEHEPLER_H__C5E39275_71A5_4307_8D63_54E7E3CB21E0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class GameHepler  
{
public:
	GameHepler();
	virtual ~GameHepler();


    
    static BYTE ReadByte(DWORD addr);
    static WORD ReadWORD(DWORD addr);
    static DWORD ReadDWORD(DWORD addr);
    static int ReadInt(DWORD addr);
    static float ReadFloat(DWORD addr);
    static char* ReadStr(DWORD addr);

};

#endif // !defined(AFX_GAMEHEPLER_H__C5E39275_71A5_4307_8D63_54E7E3CB21E0__INCLUDED_)
