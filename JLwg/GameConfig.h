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

//游戏配置
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



    //配置文件路径
public:
    TCHAR m_szLujingPath[MAX_PATH];
    TCHAR m_szConfigPath[MAX_PATH];
    TCHAR m_szLujingTest[MAX_PATH];


    //出售
    ItemVector m_SellItem;

    //存仓
    ItemVector m_Bank;

    //分解
    ItemVector m_Disenchant;

    //交易
    ItemVector m_Trade;

    //删除
    ItemVector m_DelItem;

    //战斗优先
    ItemVector m_FirstKill;

    //战斗不杀
    ItemVector m_DontKill;

    //战斗必杀
    ItemVector m_AlwaysKill;

    //喝药百分比
    int m_HealthPercent;

    //强化材料最低颜色
    TCHAR m_szQHColor[BUFSIZ / 4];

    //强化饰品
    ItemVector m_QHAccessories;

    //强化武器
    ItemVector m_QHWeapons;


    //初始化
public:
    BOOL Init();

    //加载配置
    void LoadConfig();

    //保存配置
    void SaveConfig();
};

#endif // !defined(AFX_GAMECONFIG_H__F88A8AE2_C451_47B0_A88C_A933A4EAE5E1__INCLUDED_)
