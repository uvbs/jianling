#ifndef _GAMESTRUCT_H
#define _GAMESTRUCT_H


typedef struct _PARAM_7
{
    DWORD   argv1;
    DWORD   argv2;
    DWORD   argv3;
    DWORD   argv4;
    DWORD   argv5;
    DWORD   argv6;
    DWORD   argv7;
} PARAM_7, *PPARAM_7;

typedef struct _PARAM_5
{
    DWORD   argv1;
    DWORD   argv2;
    DWORD   argv3;
    DWORD   argv4;
    DWORD   argv5;
    DWORD   argv6;
    DWORD   argv7;
} PARAM_5, *PPARAM_5;

typedef struct _PARAM_3
{
    DWORD   argv1;
    DWORD   argv2;
    DWORD   argv3;
} PARAM_3, *PPARAM_3;

//这些结构定义方便传参
typedef struct _PARAM_2
{
    DWORD   argv1;
    DWORD   argv2;
} PARAM_2, *PPARAM_2;


typedef struct _PARAM_8
{
    DWORD   id;
    DWORD   step;
    DWORD   questtype;
    DWORD   ff;
    DWORD   npcid1;
    DWORD   npcid2;
    DWORD   unknow;
    DWORD   mianban;
} PARAM_8, *PPARAM_8;

typedef struct _TInvite
{
	DWORD PInfo;
    DWORD PartySn;
	DWORD PartyTId;
	DWORD CaptainSn;
	DWORD CaptainTId;
} TInvite, *PTInvite;

typedef struct _UI
{
    wchar_t* szName;
	DWORD PInfo;
    DWORD Id;
	DWORD vCode;
	DWORD bVisable;
}UI, *PUI;

typedef struct _YaoPingCD_JG
{
    DWORD   canshu1;
    DWORD   canshu2;
    DWORD   canshu3;
} YaoPingCD_JG, *PYaoPingCD_JG;


typedef struct _BAGSTU
{
    char        CanSell; //是否可以出售
    char        UFaction; //使用职业
    char        UseLevel;    //使用等级
    char        EquipIndex; //身上位置
    DWORD       m_Base;                     //物品的首地址
    DWORD       m_Info;                     //物品所在的格子数
    DWORD       m_ID;                       //物品的ID
    DWORD       m_NameID;                   //物品名字的ID
    int         m_Type;                     //物品的类型
    int         m_Num;                      //物品的数量
    int         m_LV;                       //物品的等级

    DWORD       MaxDur;   //最大耐久
    DWORD       CurDur;   //当前耐久

    DWORD       m_YanSe;                    //物品的颜色
    DWORD       m_IsFengYin;                //物品是否封印
    DWORD       m_BagLeiXing;               //物品的背包类型
    DWORD       m_CaoZuoType;               //右键操作物品的类型
    DWORD       m_DangQianJingYanZhi;       //武器的当前经验值
    DWORD       m_DangQianJingYanZongZhi;   //武器的当前经验总值
    DWORD       m_HeChengWuQiLeiXing;       //合成武器类型 1表示是合成武器类型
    BOOL        m_IsHeChengWuQiLeiXing;     //合成武器类型 1表示是合成武器类型
    DWORD       m_BaGuaGeZiShu;             //八卦格子数
    DWORD       m_BiDui1;                   //比对1
    DWORD       m_BiDui2;                   //比对2
    DWORD       m_PingJi;                   //武器的评级
    wchar_t*    name;                       //物品的名字
    DWORD       canshu1;
    DWORD       canshu2;
    DWORD       canshu3;
    DWORD       canshu4;

} BAGSTU, *PBAGSTU;



typedef struct _YouJianLeiXing
{
    DWORD   canshu1;
    DWORD   canshu2;
    DWORD   canshu3;
    DWORD   canshu4;
} YouJianLeiXing;


//技能数据结构
typedef struct _STRIKEINFO
{
    wchar_t* name;
    int id;
    int iIndex;
    char iType;
    int iKeyCode;
    bool bCD;
    bool bAviable;  //能用
} STRIKEINFO, PSTRIKEINFO;

#pragma pack(push)
#pragma pack(1)
typedef struct _Tree
{
    _Tree*  Right;
    _Tree*  Last;
    _Tree*  Left;
    DWORD   ID;
    DWORD   Adress;
    BYTE    p1;
    BYTE    p2;
} Tree, *PTree;
#pragma pack(pop)

//坐标
typedef struct _fPosition
{
    float   x;
    float   y;
    float   z;
} fPosition;

typedef struct _sPosition
{
    short   x;
    short   y;
    short   z;
} sPosition;

typedef struct _TASK
{
    wchar_t *nName;
    wchar_t *StepName;
    int PInfo;
    int id;
    int Step;
    int StepNameId;
    int StepTagCount1;
    int StepTagCount2;
    int StepTagCount3;
    int StepTagCount4;
    bool bStepTagDone1;
    bool bStepTagDone2;
    bool bStepTagDone3;
    bool bStepTagDone4;
}TASK, *PTASK;


//任务节点
typedef struct _QuestNode
{
    _QuestNode*     left;
    _QuestNode*     last;
    _QuestNode*     right;

    UCHAR           unknow[0x204];
    USHORT          id;
    UCHAR           end;    /* ==  1 结束*/
} QuestNode, *PQuestNode;

//对象结构
typedef struct _ObjectNode
{
    _ObjectNode*    left;
    _ObjectNode*    last;//4
    _ObjectNode*    right;//8
    DWORD           unknow;//c
    DWORD           id;//10
    DWORD           id2;//14
    DWORD           ObjAddress;//18
    DWORD           unknow2;//1c
    bool            unknow3;//20
    bool            end;//21
} ObjectNode, *PObjectNode;


typedef struct _KONGJIAN_JIEGOU
{
    DWORD       ID;
    DWORD       adress;
    wchar_t*    name;
    wchar_t*    nm;
    DWORD       ISSHOW;
} KONGJIAN_JIEGOU, *PKONGJIAN_JIEGOU;

//控件
typedef struct _KONGJ   //控件
{
    DWORD   canshu1;
    DWORD   canshu2;
    DWORD   canshu3;
    DWORD   canshu4;
    DWORD   canshu5;
    DWORD   canshu6;
    DWORD   canshu7;
    DWORD   canshu8;
    DWORD   canshu9;
    DWORD   canshu10;
    DWORD   canshu11;
    DWORD   canshu12;
} KONGJ, *PKONGJ;

//操作ui用的结构
typedef struct _UIOperator
{
    DWORD*  pAddr;
    DWORD   c5;
} UIOperator, *PUIOperator;



typedef struct _Team
{
    DWORD       PAddress;   //对象的指针
    wchar_t*    name;       //对象的名字
    DWORD       Channel;    //对象的线路
    DWORD       CurrLife;   //当前生命
    DWORD       MaxLife;    //最大生命
    DWORD       ID;         //对象的ID
    DWORD       ID2;        //对象的ID2
    fPosition   Pos;        //坐标
    DWORD       Angle;      //面向
    DWORD       Range;      //距离
    DWORD       LV;         //等级;
    DWORD       TeamNum;    //队伍人数
} Team, *PTeam;


#endif
