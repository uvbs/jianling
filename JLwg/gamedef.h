// gamedef.h: interface for the gamedef class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GAMEDEF_H__240B533F_368F_42BD_90E6_7F364A93AF17__INCLUDED_)
#define AFX_GAMEDEF_H__240B533F_368F_42BD_90E6_7F364A93AF17__INCLUDED_

#if _MSC_VER > 1000
    #pragma once
#endif // _MSC_VER > 1000



//方便根据字符集设置输出相应的调试信息
#define __L(x)  ___L(x)
#define ___L(x) L##x

#if _MSC_VER > 1200
    #ifdef _UNICODE
        #define FUNCNAME    __FUNCTIONW__
    #else
        #define FUNCNAME    __FUNCTION__
    #endif
#else
    #define FUNCNAME    __L(__FILE__)
#endif



#define RESULT_KILL_OK          0
#define RESULT_KILL_PLAYDEAD    1
#define RESULT_KILL_TIMEOUT     2
#define RESULT_KILL_FAIL        3

//杀怪模式, 默认只Normal
//可以应用多个杀怪模式, 比如 modeNormal | modeSpend | modeTask | modeAoe
#define modeNormal      1                   //用普通技能, 不会用范围攻击
#define modeAoe         4                   //AOE
#define modeTask        8                   //任务, 影响退出逻辑的判断
#define modeGoback      16                  //杀完回原点
#define modePickup      32                  //杀完自己捡
#define modePickupBody  64                  //杀完举起尸体  
#define modePickupOnce  128                 //干掉一个捡一次掉落
#define modeOnlyAoe     256                 //只用Aoe


/*状态常量*/
#define NORTH               0               //正北
#define SOUTH               32778           //南
#define WEST                49167           //西
#define EAST                16389           //东
#define VIT_STATUS_USED     1               //使用了轻功
#define VIT_STATUS_RENEW    2               //正在恢复
#define VIT_STATUS_FULL     3               //轻功已满
#define package             0x2             //背包
#define body                0x1             //身上装备 0xFA6CE4
#define CAN_OPERATOR        155             //可以操作的距离, 游戏内次距离就可以按F等等



//自定的消息, 用来执行游戏 call
#define WM_CUSTOM_GCALL         (WM_USER + 0x300)

//
#define JINGDIANMOSHICALL_JIEGOUTOU     0x0A7CD0A4      // 经典模式CALL的结构头  
#define QUDINGYAOJIANG_JIEGOUTOU        0x0A7CD0A4      // 确定摇奖CALL的结构头  
#define ShuaXinBeiBao_JIEGOUTOU         0x0A7BD0A4      // 刷新背包CALL的结构头  
#define GUANBICHUANGKOUCALL_JIEGOUTOU   0x0AD2D0A4      // 关闭窗口CALL的结构头  
#define SHENXINGBAIBIANCHAZHI           0x1EF26C8       //神行百变差值     面向的基址 - bsengine_Shipping.dll的base 


//这每个定义是一种配置文件中的节名
#define strNormal       _T("普通")
#define strTeam         _T("组队")
#define strCombat       _T("战斗")

#define strSellItem         _T("出售")
#define strDisenchantItem   _T("分解")
#define strBankItem         _T("存仓")
#define strTradeItem        _T("交易")
#define strQHWeapons        _T("强化武器")
#define strQHAccessories    _T("强化饰品")
#define strDelItem          _T("摧毁")


//这是键名
#define strInvite_Auto  _T("自动邀请")
#define strInvite_All   _T("邀请所有")
#define strInvite_InMap _T("邀请地图内")
#define strInvite_Range _T("邀请范围内")
#define strInvite_RangeValue _T("邀请范围值")


#define strAcpt_Auto    _T("自动接受")
#define strAcpt_All     _T("接受所有")
#define strAcpt_InMap   _T("接受地图内")
#define strAcpt_Range   _T("接受范围内")
#define strAcpt_RangeValue _T("接受范围值")
#define strQhColor      _T("合成颜色")
#define strItemName     _T("物品名")
#define strFirstKill    _T("优先")
#define strDontKill     _T("不杀")
#define strAlwaysKill   _T("必杀")
#define strYaoPecent    _T("喝药百分比")


//这是值
#define strGreen        _T("绿色")
#define strBlue         _T("蓝色")
#define strPurple       _T("紫色")
#define strOrange       _T("橙色")

//装备位置枚举
enum EQUITMENT_POS {
    WUQI = 1,
    YIFU = 2,
    YAODAI,
    XIANGLIAN = 7,
    JIEZHI = 6,
    ERHUAN = 3
};


//消息ID
enum CUSTOMMSGID {
    id_msg_step = 0,
    id_msg_step3x,
    id_msg_guanshangdian,
    id_msg_attack,
    id_msg_clickui,
    id_msg_vector_ui,
    id_msg_HeChengWuQi_Po5,
    id_msg_HeChengWuQi_Po10,
    id_msg_HeChengWuQi,
    id_msg_WearEquipment,
    id_msg_Fenjie,
    id_msg_CunCangku,
    id_msg_ChiYao,
    id_msg_DeleteItem,
    id_msg_DeliverQuests,
    id_msg_DaKaiDuiHuaKuang,
    id_msg_FaSonXianLuBao,
    id_msg_PickupDeadbody,
    id_msg_JingDianMoShi,
    id_msg_PickdownBody,
    id_msg_DunDi,
    id_msg_GatBagGoodrName,
    id_msg_GatTaskName,
    id_msg_ZOULUSHUNYI,
    id_msg_OpenQuestItem,
    id_msg_Pickup,
    id_msg_Pickup1,
    id_msg_Pickup2,
    id_msg_PickupTask,
    id_msg_Fuhuo,
    id_msg_NewBag,
    id_msg_SellItem,
    id_msg__KaiHeZi,
    id_msg_HuanXian,
    id_msg_TiaoYue,
    id_msg_JieFengZhuangBei,
    id_msg_JiaBaoShi,
    id_msg_XieBaoShi,
    id_msg_GouMaiWuPing,
    id_msg_isYaoPingCD,
    id_msg_OverShunyi,
    id_msg_GetRangeObjectToVector,
    id_msg_GetUItoVector,
    id_msg_GetAcceptedQuestToVector,
    id_msg_GetAllGoodsToVector,
    id_msg_GetAllBodyEquipToVector,
    id_msg_NewSpend,
    id_msg__GetUiAddrByName,
    id_msg_GetStrikeToVector,
    id_msg_LinQuJiangLi,
    id_msg_QueRenJiNengDian,
    id_msg_QuChuJiNengDian,
    id_msg_JiaJiNengDian,
    id_msg_OpenTalentUI,
    id_msg_ConfirmDeletePalentPanelShowOk,
    id_msg_OpenDeleteTalentPanel,
    id_msg_NPCJieRenWu,
    id_msg_GetObjectNameByIndex,
    id_msg_Pickup2ts,
    id_msg_DaKaiHeChengJieMian,
    id_msg_IsCanShu,
    id_msg_XieZhuangBei,
    id_msg_GetPlayExperienceStatusName
};


enum CUSTOMTYPE {
    DONTKILL,   //不杀
    ALWAYSKILL, //总是
    KILLFIRST   //优先
};


typedef struct _CUSTOMTYPE {
    wchar_t* name;
    int type;
} CUSTOMKILL, *PCUSTOMKILL;


//药水, 变量名标识等级
const wchar_t nBig50[] = L"\xd070\x0020\xbc31\xb144\xc0bc\x0020\xd68c\xbcf5\xc57d";
const wchar_t nBig45[] = L"\xbc31\xb144\xc0bc\x0020\xd68c\xbcf5\xc57d";
const wchar_t nBig36[] = L"\xc218\xc815\xb09c\xd480\x0020\xd68c\xbcf5\xc57d";
const wchar_t nBig29[] = L"\xd070\x0020\xc601\xc9c0\xbc84\xc12f\x0020\xd68c\xbcf5\xc57d";
const wchar_t nBig10[] = L"\xbcf5\xbd84\xc790\x0020\xd68c\xbcf5\xc57d";
const wchar_t nLess10[] = L"\xc57d\xc218\x0020\xd68c\xbcf5\xc57d";
const wchar_t nSpec1[] = L"\xd68c\xbcf5\xc57d";
const wchar_t nSpec2[] = L"\xd589\xc6b4\xc758\x0020\xbe44\xc57d";

//附魔
const wchar_t fTo20[] = L"\xc81c\xb8e1\x0020\xc218\xb9ac\xb3c4\xad6c";
const wchar_t fTo36[] = L"\xc0ac\xb9c9\x0020\xc218\xb9ac\xb3c4\xad6c";
const wchar_t fTo45[] = L"\xc218\xc6d4\x0020\xc218\xb9ac\xb3c4\xad6c";
const wchar_t fTo50[] = L"\xbc31\xccad\x0020\xc218\xb9ac\xb3c4\xad6c";


//四个首饰的魂名字
//1~36
//1~50
//ss == 首饰
const wchar_t sshun1[] = L"\xc218\xb828\xbcf4\xc625";
const wchar_t sshun2[] = L"\xbcf4\xc625";
const wchar_t sshun3[] = L"\xd64d\xbb38\xbcf4\xc625";
const wchar_t sshun4[] = L"\xd589\xc6b4\xbcf4\xc625";


//四个魂的名字
const wchar_t hun1[] = L"\xc218\xb828\xbb34\xd63c";
const wchar_t hun2[] = L"\xbb34\xd63c";
const wchar_t hun3[] = L"\xd589\xc6b4\xbb34\xd63c";
const wchar_t hun4[] = L"\xd64d\xbb38\xbb34\xd63c";



//千魂武器
const wchar_t qianhun[] = L"\xcc9c\xb839\xb3c4\xb07c";



#endif // !defined(AFX_GAMEDEF_H__240B533F_368F_42BD_90E6_7F364A93AF17__INCLUDED_)
