// Tester.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Test.h"


//方便根据字符集设置输出相应的调试信息
#define __L(x)  ___L(x)
#define ___L(x) L#x

#define _SRCLINE_ __FILE__ Line:__LINE__

CWinApp theApp;



UINT WorkThread1(LPVOID lParam)
{

    Sleep(100000);

    return 0;
}

UINT WorkThread(LPVOID lParam)
{

    HANDLE tThread = AfxBeginThread(WorkThread1, 0);
    CloseHandle(tThread);
    Sleep(100000);

    return 0;
}

using namespace std;
int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{

    // initialize MFC and print and error on failure
    if(!AfxWinInit(::GetModuleHandle(NULL), NULL, ::GetCommandLine(), 0))
    {
        // TODO: change error code to suit your needs
        cerr << _T("Fatal Error: MFC initialization failed") << endl;
        return 1;
    }


    getchar();
    return 0;
}