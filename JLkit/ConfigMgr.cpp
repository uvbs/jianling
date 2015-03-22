// ConfigMgr.cpp: implementation of the CConfigMgr class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "jlkit.h"
#include "ConfigMgr.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
    #define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CConfigMgr* CConfigMgr::_inst = NULL;
CConfigMgr::CConfigMgr()
{
    m_szAccountName[0] = _T('\0');
    m_szAccountPw[0] = _T('\0');
    m_szGamePath[0] = _T('\0');
    m_szFileName[0] = _T('\0');
}

CConfigMgr::~CConfigMgr()
{

}

void CConfigMgr::LoadConfig()
{
    m_KeepPw =  AfxGetApp()->GetProfileInt(_T("设置"), _T("记住密码"), 0);
    _tcsncpy(m_szFileName, (LPCTSTR)AfxGetApp()->GetProfileString(_T("设置"), _T("帐号文件")), MAX_PATH);
    _tcsncpy(m_szAccountName, (LPCTSTR)AfxGetApp()->GetProfileString(_T("设置"), _T("用户名")), MAX_PATH);
    _tcsncpy(m_szAccountPw, (LPCTSTR)AfxGetApp()->GetProfileString(_T("设置"), _T("密码")), MAX_PATH);
    _tcsncpy(m_szGamePath, (LPCTSTR)AfxGetApp()->GetProfileString(_T("设置"), _T("游戏路径")), MAX_PATH);


    if(m_szGamePath[0] == '\0') {
        //取得游戏路径
        CRegKey reg;
        if(reg.Open(HKEY_LOCAL_MACHINE,
                    _T("SOFTWARE\\Wow6432Node\\plaync\\BNS_KOR")) == ERROR_SUCCESS) {
            TCHAR szValue[MAX_PATH];
            ULONG sizeValue = MAX_PATH;
            if(reg.QueryValue(szValue, _T("BaseDir"), &sizeValue) == ERROR_SUCCESS) {
                _tcscat(szValue, _T("\\bin\\Client.exe"));
                _tcsncpy(m_szGamePath, szValue, MAX_PATH);
            }
        }
    }

}

CConfigMgr* CConfigMgr::GetInstance()
{
    if(_inst == NULL)
        _inst = new CConfigMgr;

    return _inst;
}

void CConfigMgr::SaveConfig()
{
    //保存设置
    AfxGetApp()->WriteProfileInt(_T("设置"), _T("记住密码"), m_KeepPw);
    AfxGetApp()->WriteProfileString(_T("设置"), _T("帐号文件"), m_szFileName);
    AfxGetApp()->WriteProfileString(_T("设置"), _T("用户名"), m_szAccountName);
    AfxGetApp()->WriteProfileString(_T("设置"), _T("密码"), m_szAccountPw);
    AfxGetApp()->WriteProfileString(_T("设置"), _T("游戏路径"), m_szGamePath);
}

void CConfigMgr::Delete()
{
    if(_inst) delete _inst;
}