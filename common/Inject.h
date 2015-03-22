#if !defined _INJECT_H_
#define _INJECT_H_

class CInject
{
public:
    CInject(const TCHAR* lpszName);
    ~CInject(){};

    //×¢Èë
    BOOL InjectTo(TCHAR szProcess[]);
    BOOL InjectTo(DWORD pid);

    //È¨ÏÞ
    BOOL EnableDebugPrivilege(void);
    int AddPrivilege(LPCWSTR Name);
    BOOL IsVistaOrLater(void);


private:
    TCHAR m_lpszPath[MAX_PATH];
    const TCHAR* m_lpszName;
    DWORD m_dwPathLen;
    PTHREAD_START_ROUTINE pfnLoadLibrary;
    LPVOID m_lpMem;
    HANDLE m_hProcess;
};

#endif