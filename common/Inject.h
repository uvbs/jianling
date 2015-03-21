#if !defined _INJECT_H_
#define _INJECT_H_

class CInject
{
public:
    CInject(TCHAR* lpszName);
    ~CInject();

    BOOL InjectTo(TCHAR szProcess[]);
    BOOL InjectTo(DWORD pid);

private:
    TCHAR* m_lpszPath;
    DWORD m_dwPathLen;
    PTHREAD_START_ROUTINE pfnLoadLibrary;
    LPVOID m_lpMem;
    HANDLE m_hProcess;
    HMODULE m_hModule;
};

#endif