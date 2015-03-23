// GameSpend.cpp: implementation of the GameSpend class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "jlwg.h"
#include "GameSpend.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
    #define new DEBUG_NEW
#endif


//静态成员
GameSpend* GameSpend::_inst = NULL;


//构造函数
GameSpend::GameSpend()
{
    m_pfnInitSpeed = NULL;
}

GameSpend::~GameSpend()
{

}


BOOL GameSpend::Init()
{
    //先加载这个DLL
    m_hack = GetModuleHandle(_T("speedhack-i386"));
    if(m_hack == NULL) return FALSE;

    HMODULE hWinmm = GetModuleHandle(_T("Winmm"));
    BYTE* pfntimeGetTime = (BYTE*)GetProcAddress(hWinmm, "timeGetTime");


    m_pfnInitSpeed = (_InitializeSpeedhack)GetProcAddress(m_hack, "InitializeSpeedhack");
    int* realGetTickCount = (int*)GetProcAddress(m_hack, "realGetTickCount");
    int* realQueryPerformance = (int*)GetProcAddress(m_hack, "realQueryPerformanceCounter");

    int* ce_gettickcount = (int*)GetProcAddress(m_hack, "speedhackversion_GetTickCount");
    int* ce_querytime = (int*)GetProcAddress(m_hack, "speedhackversion_QueryPerformanceCounter");


    HMODULE hKernel = GetModuleHandle(_T("Kernel32"));
    DWORD GetTickCount_addr = (DWORD)GetProcAddress(hKernel, "GetTickCount");
    DWORD Query_addr = (DWORD)GetProcAddress(hKernel, "QueryPerformanceCounter");


    ce_hooktimeGetTime.Init((void*)pfntimeGetTime, ce_gettickcount, FALSE);
    ce_hookGetTickCount.Init((void*)GetTickCount_addr, ce_gettickcount, FALSE);
    ce_hookQueryPerformanceCounter.Init((void*)Query_addr, ce_querytime, FALSE);


    if(*realGetTickCount == 0) {
        ce_hooktimeGetTime.hook();
        void* result1 = ce_hookGetTickCount.hook();
        *realGetTickCount = (DWORD)result1;
    }

    if(*realQueryPerformance == 0) {
        void* result2 = ce_hookQueryPerformanceCounter.hook();
        *realQueryPerformance = (DWORD)result2;
    }

    return TRUE;
}
