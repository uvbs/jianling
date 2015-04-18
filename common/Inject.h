#ifndef _INJECT_H_
#define _INJECT_H_

class CInject
{
public:
    CInject(const TCHAR* lpszName);
    ~CInject() {};

    //×¢Èë
    BOOL InjectTo(TCHAR szProcess[]);
    BOOL InjectTo(DWORD pid);

    //È¨ÏÞ
    static BOOL EnableDebugPrivilege(void);
    int AddPrivilege(LPCWSTR Name);
    BOOL IsVistaOrLater(void);

private:
    TCHAR m_szName[MAX_PATH];
};

#endif