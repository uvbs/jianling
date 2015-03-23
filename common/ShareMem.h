// ShareMem.h: interface for the ShareMem class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SHAREMEM_H__EA35F58D_574C_4783_BF68_B196F54257E6__INCLUDED_)
#define AFX_SHAREMEM_H__EA35F58D_574C_4783_BF68_B196F54257E6__INCLUDED_

#if _MSC_VER > 1000
    #pragma once
#endif // _MSC_VER > 1000



#define SHAREMAXLEN 32
typedef struct _SHAREINFO {
    TCHAR szName[SHAREMAXLEN];
    TCHAR szConfig[SHAREMAXLEN];
    TCHAR szSript[SHAREMAXLEN];
    DWORD pid;
} SHAREINFO, *PSHAREINFO;

class ShareMem;
typedef ShareMem JLShareMem;

class ShareMem
{
protected:
    ShareMem();

public:
    virtual ~ShareMem();
    static ShareMem* Instance();
private:
    static ShareMem* _inst;

public:
    BOOL Open(TCHAR szObjName[]);
    BOOL Create(DWORD dwCount, TCHAR szObjName[] = _T(""));
    void Close();

    //²Ù×÷
    BOOL Add(SHAREINFO* pInfo);

    SHAREINFO* Get(DWORD dwPid);
    SHAREINFO* Get(LPCTSTR lpszName);

    void Del(LPCTSTR lpszName);
    void Del(DWORD dwPid);

    DWORD IsPidValid(LPCTSTR lpszName);

    DWORD GetUsedCount();
    DWORD GetAllCount() {return m_dwCount;}
    SHAREINFO* GetMem() {return m_lpMem;}

    void Dump(DWORD dwPid);

protected:
    HANDLE m_hFileMap;
    DWORD m_dwCount;
    SHAREINFO* m_lpMem;
};



#endif // !defined(AFX_SHAREMEM_H__EA35F58D_574C_4783_BF68_B196F54257E6__INCLUDED_)
