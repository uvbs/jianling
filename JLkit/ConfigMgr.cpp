// ConfigMgr.cpp: implementation of the CConfigMgr class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "JLkit.h"
#include "ConfigMgr.h"

#ifdef _DEBUG
    #define new DEBUG_NEW
#endif


IMPLEMENT_SINGLETON(CConfigMgr)

//���캯��
CConfigMgr::CConfigMgr()
{
    m_szAccountName[0] = NULL;
    m_szAccountPw[0] = NULL;
    m_szGamePath[0] = NULL;
    m_szFileName[0] = NULL;
    m_szWindowPos[0] = NULL;
    m_szGameScript[0] = NULL;
    m_szGameConfig[0] = NULL;

    m_szGameScriptPath[0] = 0;
    m_szGameConfigPath[0] = 0;

}

CConfigMgr::~CConfigMgr()
{

}

void CConfigMgr::LoadConfig(const TCHAR szConfigPath[])
{

    //��ȡ����Ŀ¼
    if(GetModuleFileName(NULL, m_szGameScriptPath, MAX_PATH) == 0) return;
    _tcscpy(m_szGameConfigPath, m_szGameScriptPath);

    PathRemoveFileSpec(m_szGameConfigPath);
    PathRemoveFileSpec(m_szGameScriptPath);

    PathAppend(m_szGameScriptPath, _T("�ű�"));
    PathAppend(m_szGameConfigPath, _T("����"));

    if(!PathFileExists(m_szGameConfigPath))
        _tmkdir(m_szGameConfigPath);

    if(!PathFileExists(m_szGameScriptPath))
        _tmkdir(m_szGameScriptPath);


    if(LoadFile(szConfigPath) < 0) return;


    try
    {
        //����ֵ
        m_KeepPw = GetLongValue(_T("����"), _T("��ס����"), 0);
        _tcscpy(m_szFileName, GetValue(_T("����"), _T("�ʺ��ļ�")));
        _tcscpy(m_szAccountName, GetValue(_T("����"),  _T("�û���")));
        _tcscpy(m_szAccountPw, GetValue(_T("����"), _T("����")));
        _tcscpy(m_szWindowPos, GetValue(_T("����"), _T("����λ��")));

        //ȡ����Ϸ·��
        CRegKey reg;
        TCHAR szValue[MAX_PATH];
        if(reg.Open(HKEY_LOCAL_MACHINE, _T("SOFTWARE\\Wow6432Node\\plaync\\BNS_KOR")) == ERROR_SUCCESS)
        {
            DWORD sizeValue = MAX_PATH;
            if(reg.QueryValue(szValue, _T("BaseDir"), &sizeValue) == ERROR_SUCCESS)
            {
                _tcscat(szValue, _T("\\bin\\Client.exe"));
            }
        }

        //
        const TCHAR* pszGamePathValue = GetValue(_T("����"), _T("��Ϸ·��"), szValue);


        if(pszGamePathValue[0] == '\0')
        {
            _tcscpy(m_szGamePath, szValue);
        }
        else
        {
            _tcscpy(m_szGamePath, pszGamePathValue);
        }

        _tcscpy(m_szGameConfig, GetValue(_T("����"), _T("��Ϸ����")));
        _tcscpy(m_szGameScript, GetValue(_T("����"), _T("��Ϸ�ű�")));

    }
    catch(...)
    {

    }
}


void CConfigMgr::SaveConfig(const TCHAR szConfigPath[])
{
    //��������
    SetLongValue(_T("����"), _T("��ס����"), m_KeepPw);
    SetValue(_T("����"), _T("�ʺ��ļ�"), m_szFileName);
    SetValue(_T("����"), _T("�û���"), m_szAccountName);
    SetValue(_T("����"), _T("����"), m_szAccountPw);
    SetValue(_T("����"), _T("����λ��"), m_szWindowPos);
    SetValue(_T("����"), _T("��Ϸ·��"), m_szGamePath);
    SetValue(_T("����"), _T("��Ϸ����"), m_szGameConfig);
    SetValue(_T("����"), _T("��Ϸ�ű�"), m_szGameScript);

    SaveFile(szConfigPath);
}
