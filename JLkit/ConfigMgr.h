// ConfigMgr.h: interface for the CConfigMgr class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CONFIGMGR_H__C394F572_EBDE_49C2_BF9A_7295A576D6D5__INCLUDED_)
#define AFX_CONFIGMGR_H__C394F572_EBDE_49C2_BF9A_7295A576D6D5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


//���ù�����
class CConfigMgr
{
public:
    CConfigMgr();
    virtual ~CConfigMgr();


    //�û�����
public:
    BOOL m_KeepPw; //��ס����
    TCHAR m_szFileName[MAX_PATH];//�����ص��ļ���
    TCHAR m_szGamePath[MAX_PATH]; //��Ϸ·��
    TCHAR m_szAccountName[MAX_PATH]; //�˺�����
    TCHAR m_szAccountPw[MAX_PATH]; //�˺�����


public:
    void LoadConfig();
    void SaveConfig();

    //����
private:
    static CConfigMgr* _inst;
public:
    static CConfigMgr* GetInstance();
};

#endif // !defined(AFX_CONFIGMGR_H__C394F572_EBDE_49C2_BF9A_7295A576D6D5__INCLUDED_)
