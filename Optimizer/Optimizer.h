#ifndef _OPTIMIZER_H_
#define _OPTIMIZER_H_

#ifdef JLOPTIMIZER_DLL
    #define JLOPTIMIZER_CLASS __declspec(dllexport)
#else
    #define JLOPTIMIZER_CLASS __declspec(dllimport)
#endif

class JLOPTIMIZER_CLASS JLOptimizer
{
private:
    HANDLE m_MinMemEvent;


public:
    BOOL Stop();
    BOOL Startup();


private:
    static DWORD WINAPI MinMem_ThreadProc(LPVOID lpParameter);
};

#endif