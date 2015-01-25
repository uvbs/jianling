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

         char CpuId[200];
	     char szCPUID[129] = {NULL}; 
         char szTmp[33] = {NULL}; 
         unsigned long s1 = 0, s2 = 0; 
         _asm { 
             mov eax,01h 
                 xor edx,edx
                 cpuid 
                 mov s1,edx 
                 mov s2,eax 
         } 

  

         _asm { 
             mov eax,03h 
                 xor ecx,ecx 
                 xor edx,edx
                 cpuid 
                 mov s1,edx 
                 mov s2,ecx
         } 



             
           PCHAR bname, bcopy, bdate, bserial; 
           bname=(char*)(0xFE061); // Bios name 
           bcopy=(char*)(0xFE091); // Bios copyright 
           bdate=(char*)(0xFFFF5); // Bios date 
           bserial=(char*)(0x000FEC71); // Bios serial number 
    }



	return nRetCode;
}
