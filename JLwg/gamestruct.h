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

//��Щ�ṹ���巽�㴫��
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
    char        CanSell; //�Ƿ���Գ���
    char        UFaction; //ʹ��ְҵ
    char        UseLevel;    //ʹ�õȼ�
    char        EquipIndex; //����λ��
    DWORD       m_Base;                     //��Ʒ���׵�ַ
    DWORD       m_Info;                     //��Ʒ���ڵĸ�����
    DWORD       m_ID;                       //��Ʒ��ID
    DWORD       m_NameID;                   //��Ʒ���ֵ�ID
    int         m_Type;                     //��Ʒ������
    int         m_Num;                      //��Ʒ������
    int         m_LV;                       //��Ʒ�ĵȼ�

    DWORD       MaxDur;   //����;�
    DWORD       CurDur;   //��ǰ�;�

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

} BAGSTU, *PBAGSTU;



typedef struct _YouJianLeiXing
{
    DWORD   canshu1;
    DWORD   canshu2;
    DWORD   canshu3;
    DWORD   canshu4;
} YouJianLeiXing;


//�������ݽṹ
typedef struct _STRIKEINFO
{
    wchar_t* name;
    int id;
    int iIndex;
    char iType;
    int iKeyCode;
    bool bCD;
    bool bAviable;  //����
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
    DWORD       PAddress;   //�����ָ��
    wchar_t*    name;       //���������
    DWORD       Channel;    //�������·
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
