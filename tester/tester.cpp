// Tester.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Test.h"

#include <vector>
#include <fstream>


CWinApp theApp;

using namespace std;

int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{

    // initialize MFC and print and error on failure
    if(!AfxWinInit(::GetModuleHandle(NULL), NULL, ::GetCommandLine(), 0))
    {
        // TODO: change error code to suit your needs
        std::cerr << _T("Fatal Error: MFC initialization failed") << std::endl;
        return 1;
    }

    try
    {

        fstream file1;
        file1.open("test.txt");

        int i;
        int i1;
        while(!file1.eof())
        {
            file1 >> i;
            file1 >> i1;

            cout << i << endl;
            cout << i1 << endl;
        }

    }
    catch(...)
    {
        cout << "unknow excpetion" << endl;
    }


    getchar();
    return 0;
}