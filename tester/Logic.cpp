// Logic.cpp: implementation of the Logic class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Logic.h"


#include <process.h>
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


UINT CALLBACK Logic::Run(LPVOID pParam)
{
    Logic* pLogc = (Logic*)pParam;
    while(!pLogc->m_bExit)
    {
        printf("%08x: 我在干活\n", pParam);
        Sleep(1000);
    }

    printf("%08x: 退出\n", pParam);
    return 0;
}


void Logic::Init()
{
    m_hThread = (HANDLE)_beginthreadex(0, 0, Run, this, 0, 0);
}

void Logic::UnInit()
{
    m_bExit = TRUE;
    WaitForSingleObject(m_hThread, INFINITE);
    CloseHandle(m_hThread);
}
