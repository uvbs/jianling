#ifndef _INJECT_H_
#define _INJECT_H_

class CInject
{
public:
    CInject(const TCHAR* lpszName);
    ~CInject() {};

    //ע��
    BOOL InjectTo(TCHAR szProcess[]);
    BOOL InjectTo(DWORD pid);

    //Ȩ��
    BOOL EnableDebugPrivilege(void);
    int AddPrivilege(LPCWSTR Name);
    BOOL IsVistaOrLater(void);


private:
    const TCHAR* m_lpszName;
};

#endif