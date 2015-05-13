#ifndef _GAMESTRUCT_H
#define _GAMESTRUCT_H


typedef struct _PARAM_JIEFENGZHUANGBEI
{
    DWORD   argv1;
    DWORD   argv2;
    DWORD   argv3;
    DWORD   argv4;
    DWORD   argv5;
    DWORD   argv6;
    DWORD   argv7;
} PARAM_JIEFENGZHUANGBEI, *PPARAM_JIEFENGZHUANGBEI;

typedef struct _PARAM_GETUIADDRBYNAME
{
    DWORD   argv1;
    DWORD   argv2;
    DWORD   argv3;
} PARAM_GETUIADDRBYNAME, *PPARAM_GETUIADDRBYNAME;

//��Щ�ṹ���巽�㴫��
typedef struct _PARAM_GUANSHANGDIAN
{
    DWORD   argv1;
    DWORD   argv2;
} PARAM_GUANSHANGDIAN, *PPARAM_GUANSHANGDIAN;

typedef struct _PARAM_DELIVERQUEST
{
    DWORD   id;
    DWORD   step;
    DWORD   questtype;
    DWORD   ff;
    DWORD   npcid1;
    DWORD   npcid2;
    DWORD   unknow;
    DWORD   mianban;
} PARAM_DELIVERQUEST, *PPARAM_DELIVERQUEST;

typedef struct _PARAM_HECHENGWUQI
{
    DWORD   zhu;
    DWORD   fu;
    DWORD   adress;
} PARAM_HECHENGWUQI, *PPARAM_HECHENGWUQI;



typedef struct _CHARACTER
{
    char            unknow[2];
    unsigned char   _clsss;
    char            unknow1[0x5e];
    wchar_t*        name;
    char            unknow2[0xce];
    unsigned char   level;

} CHARACTER, *PCHARACTER;

typedef struct _YaoPingCD_JG
{
    DWORD   canshu1;
    DWORD   canshu2;
    DWORD   canshu3;
} YaoPingCD_JG, *PYaoPingCD_JG;

struct _BAGSTU
{
    DWORD       m_Base;                     //��Ʒ���׵�ַ
    DWORD       m_Info;                     //��Ʒ���ڵĸ�����
    DWORD       m_ID;                       //��Ʒ��ID
    DWORD       m_NameID;                   //��Ʒ���ֵ�ID
    int         m_Type;                     //��Ʒ������
    int         m_Site;                     //��ҩ��װ����Ҫ��һ������
    int         m_Num;                      //��Ʒ������
    int         m_LV;                       //��Ʒ�ĵȼ�
    DWORD       m_Lasting;                  //��Ʒ�ĳ־�
    DWORD       m_YanSe;                    //��Ʒ����ɫ
    DWORD       m_IsFengYin;                //��Ʒ�Ƿ��ӡ
    DWORD       m_BagLeiXing;               //��Ʒ�ı�������
    DWORD       m_CaoZuoType;               //�Ҽ�������Ʒ������
    DWORD       m_DangQianJingYanZhi;       //�����ĵ�ǰ����ֵ
    DWORD       m_DangQianJingYanZongZhi;   //�����ĵ�ǰ������ֵ
    DWORD       m_HeChengWuQiLeiXing;       //�ϳ��������� 1��ʾ�Ǻϳ���������
    BOOL        m_IsHeChengWuQiLeiXing;     //�ϳ��������� 1��ʾ�Ǻϳ���������
    DWORD       m_BaGuaGeZiShu;             //���Ը�����
    DWORD       m_BiDui1;                   //�ȶ�1
    DWORD       m_BiDui2;                   //�ȶ�2
    DWORD       m_PingJi;                   //����������
    wchar_t*    name;                       //��Ʒ������
    DWORD       canshu1;
    DWORD       canshu2;
    DWORD       canshu3;
    DWORD       canshu4;
};

typedef struct _YouJianLeiXing
{
    DWORD   canshu1;
    DWORD   canshu2;
    DWORD   canshu3;
    DWORD   canshu4;
} YouJianLeiXing;

typedef struct _STRIKENAME
{
    unsigned    canshu1;
    wchar_t     name[10];
    unsigned    canshu7;
} STRIKENAME, PSTRIKENAME;

//�������ݽṹ
typedef struct _STRIKEINFO
{
    int         id1;
    int         id2;
    STRIKENAME  stName;
    DWORD       cd;
    DWORD       canUse;
    DWORD       isBlock;
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

//����
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

//����
typedef struct _CurrQuest
{
    char    killed;     //�Ѵ�
    char    complete;   //��ɱ�־  = 1���
    char    queststep;  //����ڼ��� 1 ��ʼ
} CurrQuest, *PCurrQuest;

//����ڵ�
typedef struct _Quest
{
    DWORD       id;
    DWORD       name_id;
    DWORD       step;
    DWORD       endflag;
    DWORD       num;
    wchar_t*    name;
} Quest, *PQuest;

//����ڵ�
typedef struct _QuestNode
{
    _QuestNode*     left;
    _QuestNode*     last;
    _QuestNode*     right;

    UCHAR           unknow[0x204];
    USHORT          id;
    UCHAR           end;    /* ==  1 ����*/
} QuestNode, *PQuestNode;

//����ṹ
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

typedef struct _SkillNameCANSHUQ
{
    DWORD   canshu1;
    DWORD   canshu2;
    DWORD   canshu3;
    DWORD   canshu4;
    DWORD   canshu5;
    DWORD   canshu6;
    DWORD   canshu7;
} SkillNameCANSHUQ, *PSkillNameCANSHUQ;

typedef struct _SkillM
{
    DWORD   ID;
    DWORD   ID2;
    DWORD   ISShiYong;
    DWORD   IsJieSuo;
    DWORD   CD;
    wchar_t name[80];
    char*   nameA;
} SkillM, *PSkillM;

typedef struct _KONGJIAN_JIEGOU
{
    DWORD       ID;
    DWORD       adress;
    wchar_t*    name;
    wchar_t*    nm;
    DWORD       ISSHOW;

} KONGJIAN_JIEGOU, *PKONGJIAN_JIEGOU;

//�ؼ�
typedef struct _KONGJ   //�ؼ�
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

//����ui�õĽṹ
typedef struct _UIOperator
{
    DWORD*  pAddr;
    DWORD   c5;
} UIOperator, *PUIOperator;



typedef struct _Team
{
    DWORD       PAddress; //�����ָ��
    wchar_t*     name;   //���������
    DWORD       Channel;       //�������·
    DWORD       CurrLife;   //��ǰ����
    DWORD       MaxLife;    //�������
    DWORD       ID;         //�����ID
    DWORD       ID2;        //�����ID2
    fPosition   Pos;        //����
    DWORD       Angle;      //����
    DWORD       Range;      //����
    DWORD       LV;         //�ȼ�;
    DWORD       TeamNum;    //��������
} Team, *PTeam;

#endif
