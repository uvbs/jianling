// ConfigMgr.h: interface for the CConfigMgr class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CONFIGMGR_H__C394F572_EBDE_49C2_BF9A_7295A576D6D5__INCLUDED_)
#define AFX_CONFIGMGR_H__C394F572_EBDE_49C2_BF9A_7295A576D6D5__INCLUDED_



//���ù�����
class CConfigMgr: public CSimpleIni
{
public:
    CConfigMgr();
    virtual ~CConfigMgr();

    DECLARE_SINGLETON(CConfigMgr);

    //�û�����
public:
    BOOL m_KeepPw; //��ס����
    BOOL m_Update;
    std::basic_string<TCHAR> m_szFileName; //�����ص��ļ���
    std::basic_string<TCHAR> m_szGamePath; //��Ϸ·��
    std::basic_string<TCHAR> m_szAccountName; //�˺�����
    std::basic_string<TCHAR> m_szAccountPw; //�˺�����
    std::basic_string<TCHAR> m_szGameScript;
    std::basic_string<TCHAR> m_szGameConfig;



public:
    BOOL LoadConfig(const TCHAR szConfigPath[]);
    void SaveConfig(const TCHAR szConfigPath[]);
};

#endif // !defined(AFX_CONFIGMGR_H__C394F572_EBDE_49C2_BF9A_7295A576D6D5__INCLUDED_)
