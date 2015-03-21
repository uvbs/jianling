// ConfigMgr.h: interface for the CConfigMgr class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CONFIGMGR_H__C394F572_EBDE_49C2_BF9A_7295A576D6D5__INCLUDED_)
#define AFX_CONFIGMGR_H__C394F572_EBDE_49C2_BF9A_7295A576D6D5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


//配置管理器
class CConfigMgr
{
public:
    CConfigMgr();
    virtual ~CConfigMgr();


    //用户配置
public:
    BOOL m_KeepPw; //记住密码
    TCHAR m_szFileName[MAX_PATH];//最后加载的文件名
    TCHAR m_szGamePath[MAX_PATH]; //游戏路径
    TCHAR m_szAccountName[MAX_PATH]; //账号名称
    TCHAR m_szAccountPw[MAX_PATH]; //账号密码


public:
    void LoadConfig();
    void SaveConfig();

    //单件
private:
    static CConfigMgr* _inst;
public:
    static CConfigMgr* GetInstance();
};

#endif // !defined(AFX_CONFIGMGR_H__C394F572_EBDE_49C2_BF9A_7295A576D6D5__INCLUDED_)
