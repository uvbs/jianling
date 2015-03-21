// DbMngr.h: interface for the CDbMngr class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DBMNGR_H__D4825D1E_CB90_4703_8099_4269409660BC__INCLUDED_)
#define AFX_DBMNGR_H__D4825D1E_CB90_4703_8099_4269409660BC__INCLUDED_

#if _MSC_VER > 1000
    #pragma once
#endif // _MSC_VER > 1000


#include <string>
#include <vector>
#include "..\common\protocol.h"


class CDbMngr: public CDatabase
{
    //构造
protected:
    CDbMngr();

public:
    virtual ~CDbMngr();

    //单件
public:
    static CDbMngr* GetInstance();
    BOOL Init();

private:
    static CDbMngr* _Instance;

    //属性
public:
    int GetPwRight(TCHAR szUsername[], TCHAR szPassw[]);
    BOOL ModifyBind(TCHAR szUserName[], TCHAR szPassword[], TCHAR szOldBind[], TCHAR szNewBind[]);
    int Unbindkey(KEY_BUF* pKeyBuf,  sockaddr_in* pSocketAddr);
    BOOL NewRegist(TCHAR szUserName[], TCHAR szPassword[], TCHAR szBindIP[], TCHAR szMac[], TCHAR szClientIp[]);
    BOOL Querykey(std::vector<QUERYKEY_RET_BUF>& vecKeyInfo, TCHAR szUserName[], TCHAR szPassWord[]);
    BOOL Bindkey(KEY_BUF* pKeyBuf, TCHAR szIp[]);
    BOOL AddKey(CString& strKey, UINT nTimes, int type);
};

#endif // !defined(AFX_DBMNGR_H__D4825D1E_CB90_4703_8099_4269409660BC__INCLUDED_)
