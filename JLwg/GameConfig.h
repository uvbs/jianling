// GameConfig.h: interface for the GameConfig class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GAMECONFIG_H__F88A8AE2_C451_47B0_A88C_A933A4EAE5E1__INCLUDED_)
#define AFX_GAMECONFIG_H__F88A8AE2_C451_47B0_A88C_A933A4EAE5E1__INCLUDED_

#if _MSC_VER > 1000
    #pragma once
#endif // _MSC_VER > 1000

typedef std::vector<std::wstring> ItemVector;
typedef std::vector<std::wstring>::iterator ItemIterator;

//游戏配置
class GameConfig: public CSimpleIniW
{
protected:
    GameConfig();
    virtual ~GameConfig();

    DECLARE_SINGLETON(GameConfig)

public:
    bool isHave(ItemVector& vec, wchar_t* pszItem);

    //配置文件路径
public:
    TCHAR m_szLujingPath[MAX_PATH];
    TCHAR m_szConfigPath[MAX_PATH];
    TCHAR m_szLujingTest[MAX_PATH];


    //出售
    ItemVector m_SellItem;

    //存仓
    ItemVector m_BankItem;

    //分解
    ItemVector m_DisenchantItem;

    //交易
    ItemVector m_TradeItem;

    //删除
    ItemVector m_DelItem;

    //强化饰品
    ItemVector m_QHAccessories;

    //强化武器
    ItemVector m_QHWeapons;

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




    // 自动发起组队
    BOOL m_bInvite_Auto;

    //发起所有组队
    BOOL m_bInvite_ALL;

    //只对同地图发起组队
    BOOL m_bInvite_INMAP;

    //发起范围
    BOOL m_bInvite_Range;

    // 发起组队范围
    int m_nInvite_Range;



    // 只接受同地图内组队
    BOOL m_bAccept_INMAP;

    // 自动接受组队
    BOOL m_bAccept_Auto;

    // 接受所有组队
    BOOL m_bAccept_ALL;

    // 接受范围内组队
    BOOL m_bAccept_Range;

    //接受范围
    int m_nAccept_Range;



    SHAREINFO* m_pMyData;


    //共享内存
private:
    JLShareMem m_SMem;

    //初始化
public:
    BOOL Init();

    //加载配置
    void LoadConfig();

    //保存配置
    void SaveConfig();

    //清空配置
    void ClearConfig();
};

#endif // !defined(AFX_GAMECONFIG_H__F88A8AE2_C451_47B0_A88C_A933A4EAE5E1__INCLUDED_)
