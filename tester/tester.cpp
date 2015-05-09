// Tester.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"



//��������ַ������������Ӧ�ĵ�����Ϣ
#define __L(x)  ___L(x)
#define ___L(x) L#x

#define _SRCLINE_ __FILE__ Line:__LINE__

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
    //��������
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

#define TT(x) printf("%08x", &x); printf(" %s", #x)

int L()
{

    return 0;
}


int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{

    // initialize MFC and print and error on failure
    if(!AfxWinInit(::GetModuleHandle(NULL), NULL, ::GetCommandLine(), 0))
    {
        // TODO: change error code to suit your needs
        cerr << _T("Fatal Error: MFC initialization failed") << endl;
        return 1;
    }



    printf("%08x", &L);
    printf(" %08x\r\n", *(DWORD *)&L);
    TT(L);

    getchar();
    return 0;
}