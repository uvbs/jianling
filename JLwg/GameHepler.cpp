// GameHepler.cpp: implementation of the GameHepler class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "jlwg.h"
#include "GameHepler.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

GameHepler::GameHepler()
{

}

GameHepler::~GameHepler()
{

}






BYTE GameHepler::ReadByte(DWORD addr)
{
    if(!IsBadReadPtr((void*)addr, sizeof(BYTE)))
    {
        return *(BYTE*)addr;
    }
    return 0;
}

WORD GameHepler::ReadWORD(DWORD addr)
{
    if(!IsBadReadPtr((void*)addr, sizeof(WORD)))
    {
        return *(WORD*)addr;
    }
    return 0;
}

DWORD GameHepler::ReadDWORD(DWORD addr)
{
    if(!IsBadReadPtr((void*)addr, sizeof(DWORD)))
    {
        return *(DWORD*)addr;
    }
    return 0;
}

int GameHepler::ReadInt(DWORD addr)
{
    if(!IsBadReadPtr((void*)addr, sizeof(int)))
    {
        return *(int*)addr;
    }
    return 0;
}

float GameHepler::ReadFloat(DWORD addr)
{
    if(!IsBadReadPtr((void*)addr, sizeof(float)))
    {
        return *(float*)addr;
    }
    return 0;
}

char* GameHepler::ReadStr(DWORD addr)
{
    if(!IsBadReadPtr((void*)addr, sizeof(char)))
    {
        return (char*)addr;
    }
    return 0;
}