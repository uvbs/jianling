// ShareMem.h: interface for the ShareMem class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SHAREMEM_H__EA35F58D_574C_4783_BF68_B196F54257E6__INCLUDED_)
#define AFX_SHAREMEM_H__EA35F58D_574C_4783_BF68_B196F54257E6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define SHAREMAXLEN 32


typedef struct _SHAREINFO
{
	char szName[SHAREMAXLEN];
	DWORD pid;
	char szConfig[SHAREMAXLEN];
	char szSript[SHAREMAXLEN];
}SHAREINFO, *PSHAREINFO;


class ShareMem
{
public:
	ShareMem(HANDLE hFileMap = NULL);
	virtual ~ShareMem();

	BOOL Open(TCHAR szObjName[]);
	BOOL Create(DWORD dwCount, TCHAR szObjName[] = _T(""));
	SHAREINFO* Add(SHAREINFO *pInfo);
	SHAREINFO* Get(DWORD dwPid);
    void Del(DWORD dwPid);
    void Del(const char *name);
    SHAREINFO* IsLogined(const char* name); //判断一个帐号是否已经存在
	SHAREINFO* IsLogined(DWORD pid);
    DWORD IsPidValid(const char* name);
	inline DWORD GetMaxCount(){return m_dwMaxCount;}
	inline SHAREINFO* GetMemAddr(){return m_lpMem;}
	void Close();
	DWORD GetLoginedCount();


private:
	HANDLE m_hFileMap;
	SHAREINFO* m_lpMem;
	DWORD m_dwMaxCount;
};

#endif // !defined(AFX_SHAREMEM_H__EA35F58D_574C_4783_BF68_B196F54257E6__INCLUDED_)
