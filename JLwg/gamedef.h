// gamedef.h: interface for the gamedef class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GAMEDEF_H__240B533F_368F_42BD_90E6_7F364A93AF17__INCLUDED_)
#define AFX_GAMEDEF_H__240B533F_368F_42BD_90E6_7F364A93AF17__INCLUDED_

#if _MSC_VER > 1000
    #pragma once
#endif // _MSC_VER > 1000



//��������ַ������������Ӧ�ĵ�����Ϣ
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

//ɱ��ģʽ, Ĭ��ֻNormal
//����Ӧ�ö��ɱ��ģʽ, ���� modeNormal | modeSpend | modeTask | modeAoe
#define modeNormal      1                   //����ͨ����, �����÷�Χ����
#define modeAoe         4                   //AOE
#define modeTask        8                   //����, Ӱ���˳��߼����ж�
#define modeGoback      16                  //ɱ���ԭ��
#define modePickup      32                  //ɱ���Լ���
#define modePickupBody  64                  //ɱ�����ʬ��  
#define modePickupOnce  128                 //�ɵ�һ����һ�ε���
#define modeOnlyAoe     256                 //ֻ��Aoe


/*״̬����*/
#define NORTH               0               //����
#define SOUTH               32778           //��
#define WEST                49167           //��
#define EAST                16389           //��
#define VIT_STATUS_USED     1               //ʹ�����Ṧ
#define VIT_STATUS_RENEW    2               //���ڻָ�
#define VIT_STATUS_FULL     3               //�Ṧ����
#define package             0x2             //����
#define body                0x1             //����װ�� 0xFA6CE4
#define CAN_OPERATOR        155             //���Բ����ľ���, ��Ϸ�ڴξ���Ϳ��԰�F�ȵ�



//�Զ�����Ϣ, ����ִ����Ϸ call
#define WM_CUSTOM_GCALL         (WM_USER + 0x300)

//
#define JINGDIANMOSHICALL_JIEGOUTOU     0x0A7CD0A4      // ����ģʽCALL�Ľṹͷ  
#define QUDINGYAOJIANG_JIEGOUTOU        0x0A7CD0A4      // ȷ��ҡ��CALL�Ľṹͷ  
#define ShuaXinBeiBao_JIEGOUTOU         0x0A7BD0A4      // ˢ�±���CALL�Ľṹͷ  
#define GUANBICHUANGKOUCALL_JIEGOUTOU   0x0AD2D0A4      // �رմ���CALL�Ľṹͷ  
#define SHENXINGBAIBIANCHAZHI           0x1EF26C8       //���аٱ��ֵ     ����Ļ�ַ - bsengine_Shipping.dll��base 


//��ÿ��������һ�������ļ��еĽ���
#define strNormal       _T("��ͨ")
#define strTeam         _T("���")
#define strCombat       _T("ս��")

#define strSellItem         _T("����")
#define strDisenchantItem   _T("�ֽ�")
#define strBankItem         _T("���")
#define strTradeItem        _T("����")
#define strQHWeapons        _T("ǿ������")
#define strQHAccessories    _T("ǿ����Ʒ")
#define strDelItem          _T("�ݻ�")


//���Ǽ���
#define strInvite_Auto  _T("�Զ�����")
#define strInvite_All   _T("��������")
#define strInvite_InMap _T("�����ͼ��")
#define strInvite_Range _T("���뷶Χ��")
#define strInvite_RangeValue _T("���뷶Χֵ")


#define strAcpt_Auto    _T("�Զ�����")
#define strAcpt_All     _T("��������")
#define strAcpt_InMap   _T("���ܵ�ͼ��")
#define strAcpt_Range   _T("���ܷ�Χ��")
#define strAcpt_RangeValue _T("���ܷ�Χֵ")
#define strQhColor      _T("�ϳ���ɫ")
#define strItemName     _T("��Ʒ��")
#define strFirstKill    _T("����")
#define strDontKill     _T("��ɱ")
#define strAlwaysKill   _T("��ɱ")
#define strYaoPecent    _T("��ҩ�ٷֱ�")


//����ֵ
#define strGreen        _T("��ɫ")
#define strBlue         _T("��ɫ")
#define strPurple       _T("��ɫ")
#define strOrange       _T("��ɫ")

//װ��λ��ö��
enum EQUITMENT_POS {
    WUQI = 1,
    YIFU = 2,
    YAODAI,
    XIANGLIAN = 7,
    JIEZHI = 6,
    ERHUAN = 3
};


//��ϢID
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
    DONTKILL,   //��ɱ
    ALWAYSKILL, //����
    KILLFIRST   //����
};


typedef struct _CUSTOMTYPE {
    wchar_t* name;
    int type;
} CUSTOMKILL, *PCUSTOMKILL;


//ҩˮ, ��������ʶ�ȼ�
const wchar_t nBig50[] = L"\xd070\x0020\xbc31\xb144\xc0bc\x0020\xd68c\xbcf5\xc57d";
const wchar_t nBig45[] = L"\xbc31\xb144\xc0bc\x0020\xd68c\xbcf5\xc57d";
const wchar_t nBig36[] = L"\xc218\xc815\xb09c\xd480\x0020\xd68c\xbcf5\xc57d";
const wchar_t nBig29[] = L"\xd070\x0020\xc601\xc9c0\xbc84\xc12f\x0020\xd68c\xbcf5\xc57d";
const wchar_t nBig10[] = L"\xbcf5\xbd84\xc790\x0020\xd68c\xbcf5\xc57d";
const wchar_t nLess10[] = L"\xc57d\xc218\x0020\xd68c\xbcf5\xc57d";
const wchar_t nSpec1[] = L"\xd68c\xbcf5\xc57d";
const wchar_t nSpec2[] = L"\xd589\xc6b4\xc758\x0020\xbe44\xc57d";

//��ħ
const wchar_t fTo20[] = L"\xc81c\xb8e1\x0020\xc218\xb9ac\xb3c4\xad6c";
const wchar_t fTo36[] = L"\xc0ac\xb9c9\x0020\xc218\xb9ac\xb3c4\xad6c";
const wchar_t fTo45[] = L"\xc218\xc6d4\x0020\xc218\xb9ac\xb3c4\xad6c";
const wchar_t fTo50[] = L"\xbc31\xccad\x0020\xc218\xb9ac\xb3c4\xad6c";


//�ĸ����εĻ�����
//1~36
//1~50
//ss == ����
const wchar_t sshun1[] = L"\xc218\xb828\xbcf4\xc625";
const wchar_t sshun2[] = L"\xbcf4\xc625";
const wchar_t sshun3[] = L"\xd64d\xbb38\xbcf4\xc625";
const wchar_t sshun4[] = L"\xd589\xc6b4\xbcf4\xc625";


//�ĸ��������
const wchar_t hun1[] = L"\xc218\xb828\xbb34\xd63c";
const wchar_t hun2[] = L"\xbb34\xd63c";
const wchar_t hun3[] = L"\xd589\xc6b4\xbb34\xd63c";
const wchar_t hun4[] = L"\xd64d\xbb38\xbb34\xd63c";



//ǧ������
const wchar_t qianhun[] = L"\xcc9c\xb839\xb3c4\xb07c";



#endif // !defined(AFX_GAMEDEF_H__240B533F_368F_42BD_90E6_7F364A93AF17__INCLUDED_)
