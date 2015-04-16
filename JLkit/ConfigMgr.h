// ConfigMgr.h: interface for the CConfigMgr class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CONFIGMGR_H__C394F572_EBDE_49C2_BF9A_7295A576D6D5__INCLUDED_)
#define AFX_CONFIGMGR_H__C394F572_EBDE_49C2_BF9A_7295A576D6D5__INCLUDED_

#if _MSC_VER > 1000
    #pragma once
#endif // _MSC_VER > 1000


//配置管理器
class CConfigMgr: public CSimpleIni
{
public:
    CConfigMgr();
    virtual ~CConfigMgr();

    DECLARE_SINGLETON(CConfigMgr);

    //用户配置
public:
    BOOL m_KeepPw; //记住密码
    TCHAR m_szFileName[MAX_PATH]; //最后加载的文件名
    TCHAR m_szGamePath[MAX_PATH]; //游戏路径
    TCHAR m_szAccountName[MAX_PATH]; //账号名称
    TCHAR m_szAccountPw[MAX_PATH]; //账号密码
    TCHAR m_szWindowPos[MAX_PATH];
    TCHAR m_szGameScript[MAX_PATH];
    TCHAR m_szGameConfig[MAX_PATH];


    TCHAR m_szGameScriptPath[MAX_PATH];
    TCHAR m_szGameConfigPath[MAX_PATH];

public:
    void LoadConfig(const TCHAR szConfigPath[]);
    void SaveConfig(const TCHAR szConfigPath[]);
};

#endif // !defined(AFX_CONFIGMGR_H__C394F572_EBDE_49C2_BF9A_7295A576D6D5__INCLUDED_)
