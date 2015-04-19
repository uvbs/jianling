// DbMngr.h: interface for the CDbMngr class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DBMNGR_H__D4825D1E_CB90_4703_8099_4269409660BC__INCLUDED_)
#define AFX_DBMNGR_H__D4825D1E_CB90_4703_8099_4269409660BC__INCLUDED_

#if _MSC_VER > 1000
    #pragma once
#endif // _MSC_VER > 1000


class CDbMngr: public CDatabase
{
public:
    CDbMngr();
    virtual ~CDbMngr();


    //����
public:
    BOOL Init();
    int CheckUser(TCHAR szUsername[], TCHAR szPassw[]);
    BOOL ModifyBind(TCHAR szUserName[], TCHAR szPassword[], TCHAR szOldBind[], TCHAR szNewBind[]);
    int Unbindkey(TCHAR* pszName, TCHAR* pszKey, sockaddr_in* pSocketAddr);
    BOOL NewRegist(TCHAR szUserName[], TCHAR szPassword[], TCHAR szBindIP[], TCHAR szMac[], TCHAR szClientIp[]);
    BOOL Querykey(std::vector<QUERYKEY_SUCCESS>& vecKeyInfo, TCHAR szUserName[], TCHAR szPassWord[]);
    BOOL Bindkey(TCHAR* pszName, TCHAR* pszKey, const TCHAR szIp[]);
    BOOL AddKey(CString& strKey, UINT nTimes, int type);

};

#endif // !defined(AFX_DBMNGR_H__D4825D1E_CB90_4703_8099_4269409660BC__INCLUDED_)
