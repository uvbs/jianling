// GameLog.cpp: implementation of the GameLog class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "jlwg.h"
#include "GameLog.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif



IMPLEMENT_SINGLETON(GameLog)

//���캯��
GameLog::GameLog()
{
    OutputDebugString(_T("GameLog"));
}

//��������
GameLog::~GameLog()
{

}
