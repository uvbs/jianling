// ConfigMgr.h: interface for the CConfigMgr class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CONFIGMGR_H__C394F572_EBDE_49C2_BF9A_7295A576D6D5__INCLUDED_)
#define AFX_CONFIGMGR_H__C394F572_EBDE_49C2_BF9A_7295A576D6D5__INCLUDED_



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
    BOOL m_Update;
    std::basic_string<TCHAR> m_szFileName; //最后加载的文件名
    std::basic_string<TCHAR> m_szGamePath; //游戏路径
    std::basic_string<TCHAR> m_szAccountName; //账号名称
    std::basic_string<TCHAR> m_szAccountPw; //账号密码
    std::basic_string<TCHAR> m_szGameScript;
    std::basic_string<TCHAR> m_szGameConfig;



public:
    BOOL LoadConfig(const TCHAR szConfigPath[]);
    void SaveConfig(const TCHAR szConfigPath[]);
};

#endif // !defined(AFX_CONFIGMGR_H__C394F572_EBDE_49C2_BF9A_7295A576D6D5__INCLUDED_)
