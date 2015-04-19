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
}

CConfigMgr::~CConfigMgr()
{

}

BOOL CConfigMgr::LoadConfig(const TCHAR szConfigPath[])
{

    VERIFY(PathFileExists(szConfigPath) == TRUE);

    if(LoadFile(szConfigPath) < 0)
    {
        AfxMessageBox(_T("加载配置文件失败"));
        return FALSE;
    }


    try
    {
        //加载值
        m_KeepPw = GetLongValue(_T("设置"), _T("记住密码"), 0);
        m_szFileName = GetValue(_T("设置"), _T("帐号文件"), _T(""));
        m_szAccountName =  GetValue(_T("设置"),  _T("用户名"), _T(""));
        m_szAccountPw = GetValue(_T("设置"), _T("密码"), _T(""));

        //取得游戏路径
        CRegKey reg; TCHAR szValue[MAX_PATH];
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
            m_szGamePath = szValue;
        }
        else
        {
            m_szGamePath = pszGamePathValue;
        }

        m_szGameConfig = GetValue(_T("设置"), _T("游戏配置"), _T("default.ini"));
        if(m_szGameConfig.empty())
        {
            m_szGameConfig = _T("default.ini");
        }

        m_szGameScript = GetValue(_T("设置"), _T("游戏脚本"), _T("default.ini"));
        if(m_szGameScript.empty())
        {
            m_szGameScript = _T("default.ini");
        }

    }
    catch(...)
    {

        return FALSE;
    }

    return TRUE;
}


void CConfigMgr::SaveConfig(const TCHAR szConfigPath[])
{
    //保存设置
    SetLongValue(_T("设置"), _T("记住密码"), m_KeepPw);
    SetValue(_T("设置"), _T("帐号文件"), m_szFileName.c_str());
    SetValue(_T("设置"), _T("用户名"), m_szAccountName.c_str());
    SetValue(_T("设置"), _T("密码"), m_szAccountPw.c_str());
    SetValue(_T("设置"), _T("游戏路径"), m_szGamePath.c_str());
    SetValue(_T("设置"), _T("游戏配置"), m_szGameConfig.c_str());
    SetValue(_T("设置"), _T("游戏脚本"), m_szGameScript.c_str());

    if(szConfigPath[0] != _T('\0'))
        SaveFile(szConfigPath);
}
