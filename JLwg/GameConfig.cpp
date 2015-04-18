// GameConfig.cpp: implementation of the GameConfig class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "jlwg.h"
#include "GameConfig.h"
#include "gamedef.h"
#include "gamelog.h"


#ifdef _DEBUG
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
    #define new DEBUG_NEW
#endif


//x节名
//key键名
#define GOTOLIST(sec, key)  \
    {TNamesDepend items;\
    GetAllValues(str##sec, str##key, items);\
    for(TNamesDepend::const_iterator it = items.begin(); it != items.end(); it++){\
        if(it->pItem[0] != L'\0')\
            m_##key.push_back(it->pItem);\
    }}


#define GOTOLIST2(sec, key)  \
    {TNamesDepend items;\
    GetAllValues(str##sec, str##key, items);\
    for(TNamesDepend::const_iterator it = items.begin(); it != items.end(); it++){\
        if(it->pItem[0] != L'\0')\
            m_##sec.push_back(it->pItem);\
    }}

#define GOTODATA(sec, key)  \
    {for(ItemIterator it = m_##sec.begin(); it != m_##sec.end(); it++) {\
        this->SetValue(str##sec, str##key, (*it).c_str());\
    }}

#define GOTODATA2(sec, key)  \
    {for(ItemIterator it = m_##key.begin(); it != m_##key.end(); it++) {\
        this->SetValue(str##sec, str##key, (*it).c_str());\
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

    CJLwgApp* pApp = (CJLwgApp*)AfxGetApp();
    PIPEDATA& data = pApp->m_stData;
    PathAppend(szExe, data.szConfig);


    //打开配置文件
    SetUnicode();
    if(LoadFile(szExe) < 0)
    {
        return FALSE;
    }


    //清空配置
    ClearConfig();

    //喝药百分比
    m_HealthPercent = GetLongValue(strCombat, strYaoPecent, 60);


    //组队
    m_bInvite_Auto = GetLongValue(strTeam, strInvite_Auto, 0);
    m_bInvite_ALL = GetLongValue(strTeam, strInvite_All, 0);
    m_bInvite_INMAP = GetLongValue(strTeam, strInvite_InMap, 0);
    m_bInvite_Range = GetLongValue(strTeam, strInvite_Range, 0);
    m_nInvite_Range = GetLongValue(strTeam, strInvite_RangeValue, 0);

    m_bAccept_INMAP = GetLongValue(strTeam, strAcpt_InMap, 0);
    m_bAccept_Auto = GetLongValue(strTeam, strAcpt_Auto, 0);
    m_bAccept_ALL = GetLongValue(strTeam, strAcpt_All, 0);
    m_bAccept_Range = GetLongValue(strTeam, strAcpt_Range, 0);
    m_nAccept_Range = GetLongValue(strTeam, strAcpt_RangeValue, 0);


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

    //喝药百分比
    SetLongValue(strCombat, strYaoPecent, m_HealthPercent);
    SetValue(strQhColor, strQhColor, m_szQHColor);

    //组队
    SetLongValue(strTeam, strInvite_Auto, m_bInvite_Auto);
    SetLongValue(strTeam, strInvite_All, m_bInvite_ALL);
    SetLongValue(strTeam, strInvite_InMap, m_bInvite_INMAP);
    SetLongValue(strTeam, strInvite_Range, m_bInvite_Range);
    SetLongValue(strTeam, strInvite_RangeValue, m_nInvite_Range);

    SetLongValue(strTeam, strAcpt_InMap, m_bAccept_INMAP);
    SetLongValue(strTeam, strAcpt_Auto, m_bAccept_Auto);
    SetLongValue(strTeam, strAcpt_All, m_bAccept_ALL);
    SetLongValue(strTeam, strAcpt_Range, m_bAccept_Range);
    SetLongValue(strTeam, strAcpt_RangeValue, m_nAccept_Range);

    SetMultiKey();
    GOTODATA(BankItem, ItemName);
    GOTODATA(DelItem, ItemName);
    GOTODATA(SellItem, ItemName);
    GOTODATA(DisenchantItem, ItemName);
    GOTODATA(QHAccessories, ItemName);
    GOTODATA(QHWeapons, ItemName);
    GOTODATA(QHAccessories, ItemName);

    GOTODATA2(Combat, FirstKill);
    GOTODATA2(Combat, DontKill);
    GOTODATA2(Combat, AlwaysKill);
    SetMultiKey(false);

    TCHAR szExe[MAX_PATH] = {0};
    GetModuleFileName(AfxGetInstanceHandle(), szExe, MAX_PATH);
    PathRemoveFileSpec(szExe);
    PathAppend(szExe, _T("配置"));
    if(!PathFileExists(szExe))
    {
        _tmkdir(szExe);
    }

    CJLwgApp* pApp = (CJLwgApp*)AfxGetApp();
    PIPEDATA& data = pApp->m_stData;
    PathAppend(szExe, data.szConfig);

    SaveFile(szExe);
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
    _tcscpy(m_szQHColor, _T("绿色"));

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