// GameConfig.cpp: implementation of the GameConfig class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "jlwg.h"
#include "GameConfig.h"
#include "gamedef.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif


//x节名
//key键名
#define GOTOLIST(sec, key)  \
    {CSimpleIni::TNamesDepend items;\
    ini.GetAllValues(str##sec, str##key, items);\
    for(CSimpleIniW::TNamesDepend::const_iterator it = items.begin(); it != items.end(); it++){\
        if(it->pItem[0] != L'\0')\
            m_##key.push_back(it->pItem);\
    }}


#define GOTOLIST2(sec, key)  \
    {CSimpleIni::TNamesDepend items;\
    ini.GetAllValues(str##sec, str##key, items);\
    for(CSimpleIni::TNamesDepend::const_iterator it = items.begin(); it != items.end(); it++){\
        if(it->pItem[0] != L'\0')\
            m_##sec.push_back(it->pItem);\
    }}

#define GOTODATA(sec, key)  \
    {for(ItemIterator it = m_##sec.begin(); it != m_##sec.end(); it++) {\
        ini.SetValue(str##sec, str##key, (*it).c_str());\
    }}

#define GOTODATA2(sec, key)  \
    {for(ItemIterator it = m_##key.begin(); it != m_##key.end(); it++) {\
        ini.SetValue(str##sec, str##key, (*it).c_str());\
    }}



IMPLEMENT_SINGLETON(GameConfig)

//构造函数
GameConfig::GameConfig()
{
}

GameConfig::~GameConfig()
{

}


BOOL GameConfig::LoadConfig()
{

    TCHAR szExe[MAX_PATH] = {0};
    GetModuleFileName(AfxGetInstanceHandle(), szExe, MAX_PATH);
    PathRemoveFileSpec(szExe);
    PathAppend(szExe, _T("配置"));
    if(!PathFileExists(szExe))
    {
        _tmkdir(szExe);
    }


    PathAppend(szExe, theApp.m_stData.szConfig);


    //不存在, 新建
    if(!PathFileExists(szExe))
    {
        FILE* newfile = _tfopen(szExe, _T("w"));
        if(newfile == NULL) return FALSE;

        fclose(newfile);
    }


    //打开配置文件
    CSimpleIni ini;
    ini.SetUnicode();
    ini.SetMultiKey();
    if(ini.LoadFile(szExe) < 0) return FALSE;

    //清空配置
    ClearConfig();

    
    ini.SetMultiKey(false);
    //喝药百分比
    m_HealthPercent = ini.GetLongValue(strCombat, strYaoPecent, 60);
    m_szQHColor = ini.GetValue(strCombat, strQhColor, _T("绿色"));

    //组队
    m_bInvite_Auto = ini.GetLongValue(strTeam, strInvite_Auto, 0);
    m_bInvite_ALL = ini.GetLongValue(strTeam, strInvite_All, 0);
    m_bInvite_INMAP = ini.GetLongValue(strTeam, strInvite_InMap, 0);
    m_bInvite_Range = ini.GetLongValue(strTeam, strInvite_Range, 0);
    m_nInvite_Range = ini.GetLongValue(strTeam, strInvite_RangeValue, 0);

    m_bAccept_INMAP = ini.GetLongValue(strTeam, strAcpt_InMap, 0);
    m_bAccept_Auto = ini.GetLongValue(strTeam, strAcpt_Auto, 0);
    m_bAccept_ALL = ini.GetLongValue(strTeam, strAcpt_All, 0);
    m_bAccept_Range = ini.GetLongValue(strTeam, strAcpt_Range, 0);
    m_nAccept_Range = ini.GetLongValue(strTeam, strAcpt_RangeValue, 0);


    ini.SetMultiKey();
    GOTOLIST(Combat, DontKill);
    GOTOLIST(Combat, AlwaysKill);
    GOTOLIST(Combat, FirstKill);


    GOTOLIST2(SellItem, ItemName);
    GOTOLIST2(DelItem, ItemName);
    GOTOLIST2(BankItem, ItemName);
    GOTOLIST2(TradeItem, ItemName);
    GOTOLIST2(DisenchantItem, ItemName);
    GOTOLIST2(QHAccessories, ItemName);
    GOTOLIST2(QHWeapons, ItemName);

    return TRUE;
}

void GameConfig::SaveConfig()
{

    CSimpleIni ini;
    ini.SetUnicode();
    ini.SetMultiKey(false);


    //喝药百分比
    ini.SetLongValue(strCombat, strYaoPecent, m_HealthPercent);
    ini.SetValue(strQhColor, strQhColor, m_szQHColor.c_str());

    //组队
    ini.SetLongValue(strTeam, strInvite_Auto, m_bInvite_Auto);
    ini.SetLongValue(strTeam, strInvite_All, m_bInvite_ALL);
    ini.SetLongValue(strTeam, strInvite_InMap, m_bInvite_INMAP);
    ini.SetLongValue(strTeam, strInvite_Range, m_bInvite_Range);
    ini.SetLongValue(strTeam, strInvite_RangeValue, m_nInvite_Range);

    ini.SetLongValue(strTeam, strAcpt_InMap, m_bAccept_INMAP);
    ini.SetLongValue(strTeam, strAcpt_Auto, m_bAccept_Auto);
    ini.SetLongValue(strTeam, strAcpt_All, m_bAccept_ALL);
    ini.SetLongValue(strTeam, strAcpt_Range, m_bAccept_Range);
    ini.SetLongValue(strTeam, strAcpt_RangeValue, m_nAccept_Range);

    ini.SetMultiKey(true);
    GOTODATA(TradeItem, ItemName);
    GOTODATA(BankItem, ItemName);
    GOTODATA(DelItem, ItemName);
    GOTODATA(SellItem, ItemName);
    GOTODATA(DisenchantItem, ItemName);
    GOTODATA(QHAccessories, ItemName);
    GOTODATA(QHWeapons, ItemName);

    GOTODATA2(Combat, FirstKill);
    GOTODATA2(Combat, DontKill);
    GOTODATA2(Combat, AlwaysKill);


    TCHAR szExe[MAX_PATH] = {0};
    GetModuleFileName(AfxGetInstanceHandle(), szExe, MAX_PATH);
    PathRemoveFileSpec(szExe);
    PathAppend(szExe, _T("配置"));
    if(!PathFileExists(szExe))
    {
        _tmkdir(szExe);
    }


    ini.SetMultiKey();
    PathAppend(szExe, theApp.m_stData.szConfig);
    ini.SaveFile(szExe);
}

void GameConfig::ClearConfig()
{

    m_SellItem.clear();
    m_BankItem.clear();
    m_DisenchantItem.clear();
    m_TradeItem.clear();
    m_DelItem.clear();
    m_FirstKill.clear();
    m_DontKill.clear();
    m_AlwaysKill.clear();
    m_QHAccessories.clear();
    m_QHWeapons.clear();

    m_HealthPercent = 60;
    m_szQHColor = _T("绿色");

    m_bInvite_Auto = 0;
    m_bInvite_ALL = 0;
    m_bInvite_INMAP = 0;
    m_bInvite_Range = 0;
    m_nInvite_Range = 0;
    m_bAccept_INMAP = 0;
    m_bAccept_Auto = 0;
    m_bAccept_ALL = 0;
    m_bAccept_Range = 0;
    m_nAccept_Range = 0;
}


bool GameConfig::isHave(ItemVector& vec, wchar_t* pszItem)
{
    for(ItemIterator it = vec.begin(); it != vec.end(); it++)
    {
        if(*it == pszItem)
        {
            return true;
        }
    }

    return false;
}