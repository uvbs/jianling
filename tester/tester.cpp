// Tester.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"



CWinApp theApp;

using namespace std;


#include "Test.h"


void thread1()
{
    static int i = 0;
    printf("thread1: %d\r\n", i++);
}

void thread2()
{
    static int i = 0;
    printf("thread2: %d\r\n", i++);
}

void threadmgr()
{
    //ÂÖÁ÷µ÷¶È
    static bool b = true;
    if(b)
    {
        thread2();
    }
    else 
    {
        thread1();
    }

    b = !b;
}
int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{

    // initialize MFC and print and error on failure
    if (!AfxWinInit(::GetModuleHandle(NULL), NULL, ::GetCommandLine(), 0))
    {
        // TODO: change error code to suit your needs
        cerr << _T("Fatal Error: MFC initialization failed") << endl;
        return 1;
    }

    for(int i = 0; i < 20; i++)
    {
        threadmgr();
        Sleep(100);
    }
        
    return 0;
}