// Tester.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Test.h"

#include <vector>




CWinApp theApp;

int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{

    // initialize MFC and print and error on failure
    if(!AfxWinInit(::GetModuleHandle(NULL), NULL, ::GetCommandLine(), 0))
    {
        // TODO: change error code to suit your needs
        std::cerr << _T("Fatal Error: MFC initialization failed") << std::endl;
        return 1;
    }

    std::vector<int> Vec1;
    Vec1.push_back(1);
    Vec1.push_back(2);
    Vec1.push_back(3);
    Vec1.push_back(4);
    Vec1.push_back(5);
    Vec1.push_back(6);
    Vec1.push_back(7);

    for(std::vector<int>::iterator it = Vec1.begin(); it != Vec1.end(); it++)
    {
        std::cout << *it << std::endl;
    }

    std::vector<int>::iterator it1 = Vec1.begin();

    
        std::vector<int>::iterator it2 = Vec1.erase(it1);

    std::cout << *it1 << std::endl;
    std::cout << *it2 << std::endl;

    getchar();
    return 0;
}