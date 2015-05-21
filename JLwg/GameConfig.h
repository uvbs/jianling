// GameConfig.h: interface for the GameConfig class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GAMECONFIG_H__F88A8AE2_C451_47B0_A88C_A933A4EAE5E1__INCLUDED_)
#define AFX_GAMECONFIG_H__F88A8AE2_C451_47B0_A88C_A933A4EAE5E1__INCLUDED_


typedef std::vector<std::wstring> ItemVector;
typedef std::vector<std::wstring>::iterator ItemIterator;



//游戏配置
class GameConfig
{
protected:
    GameConfig();
    virtual ~GameConfig();

    DECLARE_SINGLETON(GameConfig)

public:
    bool isHave(ItemVector& vec, wchar_t* pszItem);

    //配置文件路径
public:

    ItemVector m_SellItem;    //出售
    ItemVector m_BankItem;    //存仓
    ItemVector m_DisenchantItem;    //分解
    ItemVector m_TradeItem;    //交易
    ItemVector m_DelItem;    //删除
    ItemVector m_QHAccessories;    //强化饰品
    ItemVector m_QHWeapons;    //强化武器

    //战斗
    ItemVector m_FirstKill;
    ItemVector m_DontKill;
    ItemVector m_AlwaysKill;


    //喝药百分比
    int m_HealthPercent;

    //强化材料最低颜色
    std::basic_string<TCHAR> m_szQHColor;




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



public:
    //加载配置
    BOOL LoadConfig();

    //保存配置
    void SaveConfig();

    //清空配置
    void ClearConfig();

};

#endif // !defined(AFX_GAMECONFIG_H__F88A8AE2_C451_47B0_A88C_A933A4EAE5E1__INCLUDED_)
