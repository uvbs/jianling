// GameConfig.h: interface for the GameConfig class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GAMECONFIG_H__F88A8AE2_C451_47B0_A88C_A933A4EAE5E1__INCLUDED_)
#define AFX_GAMECONFIG_H__F88A8AE2_C451_47B0_A88C_A933A4EAE5E1__INCLUDED_

#if _MSC_VER > 1000
    #pragma once
#endif // _MSC_VER > 1000

#include "..\common\CIniFile.h"

typedef std::vector<wchar_t*> ItemVector;

//��Ϸ����
class GameConfig: public CIniFile
{
protected:
    GameConfig();
    virtual ~GameConfig();

public:
    static GameConfig* Instance() {
        if(_inst == NULL) {
            _inst = new GameConfig;
        }
        return _inst;
    }
private:
    static GameConfig* _inst;



    //�����ļ�·��
public:
    TCHAR m_szLujingPath[MAX_PATH];
    TCHAR m_szConfigPath[MAX_PATH];
    TCHAR m_szLujingTest[MAX_PATH];


    //����
    ItemVector m_SellItem;

    //���
    ItemVector m_Bank;

    //�ֽ�
    ItemVector m_Disenchant;

    //����
    ItemVector m_Trade;

    //ɾ��
    ItemVector m_DelItem;

    //ս������
    ItemVector m_FirstKill;

    //ս����ɱ
    ItemVector m_DontKill;

    //ս����ɱ
    ItemVector m_AlwaysKill;

    //��ҩ�ٷֱ�
    int m_HealthPercent;

    //ǿ�����������ɫ
    TCHAR m_szQHColor[BUFSIZ / 4];

    //ǿ����Ʒ
    ItemVector m_QHAccessories;

    //ǿ������
    ItemVector m_QHWeapons;


    //��ʼ��
public:
    BOOL Init();

    //��������
    void LoadConfig();

    //��������
    void SaveConfig();
};

#endif // !defined(AFX_GAMECONFIG_H__F88A8AE2_C451_47B0_A88C_A933A4EAE5E1__INCLUDED_)
