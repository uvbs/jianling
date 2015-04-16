// ConfigMgr.h: interface for the CConfigMgr class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CONFIGMGR_H__C394F572_EBDE_49C2_BF9A_7295A576D6D5__INCLUDED_)
#define AFX_CONFIGMGR_H__C394F572_EBDE_49C2_BF9A_7295A576D6D5__INCLUDED_

#if _MSC_VER > 1000
    #pragma once
#endif // _MSC_VER > 1000


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
    TCHAR m_szFileName[MAX_PATH]; //�����ص��ļ���
    TCHAR m_szGamePath[MAX_PATH]; //��Ϸ·��
    TCHAR m_szAccountName[MAX_PATH]; //�˺�����
    TCHAR m_szAccountPw[MAX_PATH]; //�˺�����
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
