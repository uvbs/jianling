// tester.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "tester.h"

#include "..\common\CIniFile.h"
#include "..\common\Work.h"
#include "..\common\ThreadPool.h"
#include "..\common\Lock.h"

#include <boost/regex.hpp>
using namespace boost;


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

using namespace std;

/////////////////////////////////////////////////////////////////////////////
// The one and only application object

CWinApp theApp;

class CMyWork: public CWork
{
public:
    CMyWork(int n, int y){
        times = n;
        nums = y;
    }
    void DoWork(){
        CLock lock;
        lock.lock();
        printf("Hello World %d, %d\n", times++, nums++);
        lock.unlock();

        Sleep(1000);
    }

private:
    int times;
    int nums;
};

int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
	int nRetCode = 0;

	// initialize MFC and print and error on failure
	if (!AfxWinInit(::GetModuleHandle(NULL), NULL, ::GetCommandLine(), 0))
	{
		// TODO: change error code to suit your needs
		cerr << _T("Fatal Error: MFC initialization failed") << endl;
		nRetCode = 1;
	}
	else
	{

	    CThreadPool poolt;
        poolt.SetMaxThreads(10);
        poolt.Init();

        for(int i = 0; i < 200; i++){
            poolt.AddWork(new CMyWork(10, 10));

        }


        WaitForMultipleObjects(poolt.GetThreadsCounts(), poolt.GetThreadHandle(), TRUE, INFINITE);

    }


	return nRetCode;
}
