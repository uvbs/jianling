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


//x����
//key����
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

//���캯��
GameConfig::GameConfig()
{
    m_szConfigPath[0] = _T('\0');
    m_szLujingPath[0] = _T('\0');
    m_szLujingTest[0] = _T('\0');
}

GameConfig::~GameConfig()
{

}


BOOL GameConfig::Init()
{

#ifndef TEST_CONFIG

    //�򿪹����ڴ�
    if(!m_SMem.Open(SHAREOBJNAME)) return FALSE;

    //��ȡ��������
    m_pMyData = m_SMem.Get(GetCurrentProcessId());
    if(m_pMyData == NULL) return FALSE;

#endif //TEST_CONFIG


    //ģ��·��
    TCHAR szExePath[MAX_PATH] = {0};
    GetModuleFileName(GetModuleHandle(_T("JLwg")), szExePath, MAX_PATH);
    PathRemoveFileSpec(szExePath);



    //�����ļ�·��
    _tcscpy(m_szConfigPath, szExePath);
    PathAppend(m_szConfigPath, _T("����"));
    if(PathFileExists(m_szConfigPath) == FALSE)
    {
        _wmkdir(m_szConfigPath);
    }


    //˲�Ƶ�·��
    _tcscpy(m_szLujingPath, szExePath);
    PathAppend(m_szLujingPath, _T("·��"));
    if(PathFileExists(m_szLujingPath) == FALSE)
    {
        _wmkdir(m_szLujingPath);
    }


    //¼��˲���ļ�·��
    _tcscpy(m_szLujingTest, m_szLujingPath);
    PathAppend(m_szLujingTest, _T("˲������.bin"));


#ifndef TEST_CONFIG
    //Ĭ�������ļ���·��
    PathAppend(m_szConfigPath, m_pMyData->szConfig);
    _tcscat(m_szConfigPath, _T(".ini"));
#else
    PathAppend(m_szConfigPath, _T("test"));
    _tcscat(m_szConfigPath, _T(".ini"));
#endif

    //��������ļ�������
    if(PathFileExists(m_szConfigPath) == FALSE)
    {
#ifndef TEST_CONFIG
        FILE* configFile = _tfopen(_T("default.ini"), _T("w+"));
#else
        FILE* configFile = _tfopen(_T("test.ini"), _T("w+"));
#endif
        if(configFile == NULL)
        {
            TRACE(_T("���������ļ�ʧ��"));
            return FALSE;
        }

        //UNICODE
        WORD hdr = 0xfeff;
        if(fwrite(&hdr, 1, sizeof(WORD), configFile) != sizeof(WORD))
        {
            return FALSE;
        }

        fclose(configFile);
    }

    return TRUE;
}

void GameConfig::LoadConfig()
{
    _ASSERTE(m_szConfigPath[0] != '\0');


    //�������ļ�
    SetMultiKey();
    SetUnicode();
    if(LoadFile(m_szConfigPath) < 0) return;

    TRACE(_T("�����ļ��������.."));


    //�������
    ClearConfig();

    //��ҩ�ٷֱ�
    m_HealthPercent = GetLongValue(strCombat, strYaoPecent, 60);


    //���
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
}

void GameConfig::SaveConfig()
{

    //��ҩ�ٷֱ�
    SetLongValue(strCombat, strYaoPecent, m_HealthPercent);

    //���
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


    this->SaveFile(m_szConfigPath);
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
    _tcscpy(m_szQHColor, _T("��ɫ"));

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