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

//构造函数
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

    //获取各个目录
    if(GetModuleFileName(NULL, m_szGameScriptPath, MAX_PATH) == 0) return;
    _tcscpy(m_szGameConfigPath, m_szGameScriptPath);

    PathRemoveFileSpec(m_szGameConfigPath);
    PathRemoveFileSpec(m_szGameScriptPath);

    PathAppend(m_szGameScriptPath, _T("脚本"));
    PathAppend(m_szGameConfigPath, _T("配置"));

    if(!PathFileExists(m_szGameConfigPath))
        _tmkdir(m_szGameConfigPath);

    if(!PathFileExists(m_szGameScriptPath))
        _tmkdir(m_szGameScriptPath);


    if(LoadFile(szConfigPath) < 0) return;


    try
    {
        //加载值
        m_KeepPw = GetLongValue(_T("设置"), _T("记住密码"), 0);
        _tcscpy(m_szFileName, GetValue(_T("设置"), _T("帐号文件")));
        _tcscpy(m_szAccountName, GetValue(_T("设置"),  _T("用户名")));
        _tcscpy(m_szAccountPw, GetValue(_T("设置"), _T("密码")));
        _tcscpy(m_szWindowPos, GetValue(_T("设置"), _T("窗口位置")));

        //取得游戏路径
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
        const TCHAR* pszGamePathValue = GetValue(_T("设置"), _T("游戏路径"), szValue);


        if(pszGamePathValue[0] == '\0')
        {
            _tcscpy(m_szGamePath, szValue);
        }
        else
        {
            _tcscpy(m_szGamePath, pszGamePathValue);
        }

        _tcscpy(m_szGameConfig, GetValue(_T("设置"), _T("游戏配置")));
        _tcscpy(m_szGameScript, GetValue(_T("设置"), _T("游戏脚本")));

    }
    catch(...)
    {

    }
}


void CConfigMgr::SaveConfig(const TCHAR szConfigPath[])
{
    //保存设置
    SetLongValue(_T("设置"), _T("记住密码"), m_KeepPw);
    SetValue(_T("设置"), _T("帐号文件"), m_szFileName);
    SetValue(_T("设置"), _T("用户名"), m_szAccountName);
    SetValue(_T("设置"), _T("密码"), m_szAccountPw);
    SetValue(_T("设置"), _T("窗口位置"), m_szWindowPos);
    SetValue(_T("设置"), _T("游戏路径"), m_szGamePath);
    SetValue(_T("设置"), _T("游戏配置"), m_szGameConfig);
    SetValue(_T("设置"), _T("游戏脚本"), m_szGameScript);

    SaveFile(szConfigPath);
}
