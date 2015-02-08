#if !defined _INJECT_H_
#define _INJECT_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000



class CCInject
{
public:
    CCInject(const char* name);
    ~CCInject()
    {
        delete m_path;
    }

    BOOL InjectTo(TCHAR szProcess[]);
    BOOL InjectTo(DWORD pid);
    BOOL Call(TCHAR szCall[], LPVOID lpParam = NULL);


private:

    char* m_path;
    DWORD m_pathlen;
    PTHREAD_START_ROUTINE pfnLoadLibraryA;

    void* mem;
    HANDLE process;
    HMODULE hModule;
};

#endif