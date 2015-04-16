// Tester.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"



CWinApp theApp;

using namespace std;


#include "Test.h"

int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{

    // initialize MFC and print and error on failure
    if (!AfxWinInit(::GetModuleHandle(NULL), NULL, ::GetCommandLine(), 0))
    {
        // TODO: change error code to suit your needs
        cerr << _T("Fatal Error: MFC initialization failed") << endl;
        return 1;
    }


    if(!AfxSocketInit())
    {
        cerr << _T("Ì×½Ó×Ö³õÊ¼»¯Ê§°Ü") << endl;
        return 1;
    }

    
    Test dlg;
    dlg.DoModal();
        
    return 0;
}