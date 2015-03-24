// GameConfig.cpp: implementation of the GameConfig class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "jlwg.h"
#include "GameConfig.h"
#include "gamedef.h"

#include "..\common\ShareMem.h"


#ifdef _DEBUG
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
    #define new DEBUG_NEW
#endif


//��̬����
GameConfig* GameConfig::_inst = NULL;





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

    //��ȡ�������
    JLShareMem* pSMem = JLShareMem::Instance();

    //��ȡ��������
    SHAREINFO* pMyData = pSMem->Get(GetCurrentProcessId());
    if(!pMyData) return FALSE;

    //ģ��·��
    TCHAR szExePath[MAX_PATH] = {0};
    GetModuleFileName(GetModuleHandle(_T("JLwg")), szExePath, MAX_PATH);
    PathRemoveFileSpec(szExePath);



    //�����ļ�·��
    _tcscpy(m_szConfigPath, szExePath);
    PathAppend(m_szConfigPath, _T("����"));
    if(PathFileExists(m_szConfigPath) == FALSE) {
        _wmkdir(m_szConfigPath);
    }


    //˲�Ƶ�·��
    _tcscpy(m_szLujingPath, szExePath);
    PathAppend(m_szLujingPath, _T("·��"));
    if(PathFileExists(m_szLujingPath) == FALSE) {
        _wmkdir(m_szLujingPath);
    }


    //¼��˲���ļ�·��
    _tcscpy(m_szLujingTest, m_szLujingPath);
    PathAppend(m_szLujingTest, _T("˲������.bin"));



    //Ĭ�������ļ���·��
    PathAppend(m_szConfigPath, pMyData->szConfig);
    _tcscat(m_szConfigPath, _T(".ini"));


    //��������ļ�������
    if(PathFileExists(m_szConfigPath) == FALSE) {
        FILE* configFile = _tfopen(_T("default.ini"), _T("w+"));
        if(configFile == NULL) {
            TRACE(_T("���������ļ�ʧ��"));
            return FALSE;
        }

        //UNICODE
        WORD hdr = 0xfeff;
        if(fwrite(&hdr, 1, sizeof(WORD), configFile) != sizeof(WORD)) {
            return FALSE;
        }

        fclose(configFile);
    }

    return Open(m_szConfigPath);
}

void GameConfig::LoadConfig()
{
    //�������ļ�
    Open(m_szConfigPath);

    //׼��ָ��
    wchar_t* szSell = NULL;
    wchar_t* szCunCang  = NULL;
    wchar_t* szJioayi = NULL;
    wchar_t* szFenjie = NULL;
    wchar_t* szQhWuqi = NULL;
    wchar_t* szQhShipin  = NULL;
    wchar_t* szCombatFirst = NULL;
    wchar_t* szCombatDont = NULL;
    wchar_t* szCombatAlways = NULL;
    wchar_t* szQHColor = NULL;

    //��ҩ�ٷֱ�
    m_HealthPercent = ReadInt(strCombat, strYaoPecent, 60);


    //���
    m_bInvite_Auto = ReadInt(strTeam, strInvite_Auto, 0);
    m_bInvite_ALL = ReadInt(strTeam, strInvite_All, 0);
    m_bInvite_INMAP = ReadInt(strTeam, strInvite_InMap, 0);
    m_bInvite_Range = ReadInt(strTeam, strInvite_Range, 0);
    m_nInvite_Range = ReadInt(strTeam, strInvite_RangeValue, 0);

    m_bAccept_INMAP = ReadInt(strTeam, strAcpt_InMap, 0);
    m_bAccept_Auto = ReadInt(strTeam, strAcpt_Auto, 0);
    m_bAccept_ALL = ReadInt(strTeam, strAcpt_All, 0);
    m_bAccept_Range = ReadInt(strTeam, strAcpt_Range, 0);
    m_nAccept_Range = ReadInt(strTeam, strAcpt_RangeValue, 0);


    szSell = ReadString(strSell, strItemName);
    szJioayi = ReadString(strJiaoyi, strItemName);
    szCunCang = ReadString(strCunCang, strItemName);
    szQhShipin = ReadString(strQhShipin, strItemName);
    szQhWuqi = ReadString(strQhWuqi, strItemName);
    szFenjie = ReadString(strFenjie, strItemName);
    szCombatFirst = ReadString(strCombat, strFirstKill);
    szCombatDont = ReadString(strCombat, strDontKill);
    szCombatAlways = ReadString(strCombat, strAlwaysKill);

    wchar_t* token;
    token = wcstok(szCombatFirst, L";");
    while( token != NULL ) {
        m_FirstKill.push_back(token);

        // Get next token:
        token = wcstok(NULL, L";");
    }

    token = wcstok(szCombatDont, L";");
    while( token != NULL ) {
        m_DontKill.push_back(token);

        // Get next token:
        token = wcstok(NULL, L";");
    }

    token = wcstok(szCombatAlways, L";");
    while( token != NULL ) {
        m_AlwaysKill.push_back(token);

        // Get next token:
        token = wcstok(NULL, L";");
    }


    token = wcstok(szCunCang, L";");
    while( token != NULL ) {
        m_Bank.push_back(token);

        // Get next token:
        token = wcstok(NULL, L";");
    }


    token = wcstok(szSell, L";");
    while( token != NULL ) {
        m_SellItem.push_back(token);

        // Get next token:
        token = wcstok(NULL, L";");
    }

    token = wcstok(szFenjie, L";");
    while( token != NULL ) {
        m_Disenchant.push_back(token);

        // Get next token:
        token = wcstok(NULL, L";");
    }

    token = wcstok(szJioayi, L";");
    while( token != NULL ) {
        m_Trade.push_back(token);

        // Get next token:
        token = wcstok(NULL, L";");
    }

    token = wcstok(szQhWuqi, L";");
    while( token != NULL ) {
        m_QHWeapons.push_back(token);

        // Get next token:
        token = wcstok(NULL, L";");
    }

    token = wcstok(szQhShipin, L";");
    while( token != NULL ) {
        m_QHAccessories.push_back(token);

        // Get next token:
        token = wcstok(NULL, L";");
    }


    delete []szQhShipin;
    delete []szQhWuqi;
    delete []szFenjie;
    delete []szJioayi;
    delete []szCunCang;
    delete []szSell;
    delete []szCombatFirst;
    delete []szCombatDont;
    delete []szCombatAlways;
    delete []szQHColor;

}

void GameConfig::SaveConfig()
{

    //��ҩ�ٷֱ�
    m_HealthPercent = WriteInt(strCombat, strYaoPecent, 60);


    //���
    WriteInt(strTeam, strInvite_Auto, m_bInvite_Auto);
    WriteInt(strTeam, strInvite_All, m_bInvite_ALL);
    WriteInt(strTeam, strInvite_InMap, m_bInvite_INMAP);
    WriteInt(strTeam, strInvite_Range, m_bInvite_Range);
    WriteInt(strTeam, strInvite_RangeValue, m_nInvite_Range);

    WriteInt(strTeam, strAcpt_InMap, m_bAccept_INMAP);
    WriteInt(strTeam, strAcpt_Auto, m_bAccept_Auto);
    WriteInt(strTeam, strAcpt_All, m_bAccept_ALL);
    WriteInt(strTeam, strAcpt_Range, m_bAccept_Range);
    WriteInt(strTeam, strAcpt_RangeValue, m_nAccept_Range);
}