#pragma once


#include "gamedata.h"
#include "gamestruct.h"
#include "gamedef.h"
#include "gamespend.h"
#include "GameInit.h"
#include "GameHepler.h"

#include "..\common\logger.h"
#include "..\common\common.h"
#include "..\common\CCHook.h"
#include "..\common\sharemem.h"


class Gamecall: public GameSpend, public GameInit, public GameHepler
{
public:
    Gamecall();
    ~Gamecall();

    void UnInit();
    BOOL Init();

    //�ȴ�
    void WaitPlans();   //�ȴ���ͼ �˺������ر�ʾ��ͼ���
    BOOL LoginInGame(DWORD index);


    //�ж϶����ɱ������
    static DWORD m_Get11C(DWORD m_Adress);   //�� ==1 ����
    static DWORD m_Get110(DWORD m_Adress); //==1 ���������ж�, ==2��npc
    static DWORD m_Get2E4(DWORD m_Adress);   //==0 npc, else ����





    //����
    void HookQietu(BOOL bEnable);   //hook ��ͼ
    void SetShuyiPath(TCHAR* szPath);
    void SetIniPath(TCHAR* szPath);
    void KeyPress(WPARAM vk);
    static DWORD CalcC(fPosition& p1, fPosition& p2);      //���������������
    static fPosition ShortPosToFloatPos(sPosition& shortp);   //����ת��
    void* GetStepCallAddr();                      //ȡ��·call�ĵ�ַ
    void RandomStep(DWORD range);               //��ĳ�����������
    void JingDianMoShi(DWORD adress, DWORD adress1);  //����ģʽ
    void CloseXiaoDongHua();



    void ChangeZ_Status(BOOL flag);//��״̬
    void ChangeHeight(float how);


    //��װ�ĵ���call, ͨ����Ϣ
    DWORD call(DWORD id, LPVOID pParam);
    static DWORD sendcall(DWORD id, LPVOID pParam);

    //ǿ��
    DWORD GetMuQianJingYanZongZhi(DWORD Adress);
    DWORD GetMuQianJingYanZongZhi_A(DWORD Adress);
    void  XieBaoShi(DWORD canshu1, DWORD canshu2, DWORD canshu3);
    void  JiaBaoShi(DWORD canshu1, DWORD canshu2, DWORD canshu3, DWORD canshu4, DWORD canshu5);


    //��·
    void HuanXian(int xianlu);  //����
    DWORD GetXianluNums();      //��ȡ��·yun
    UCHAR GetPlayerXianlu();
    void DunDi(DWORD cityid);

    //���
    DWORD GetPlayerHealth();            //���Ѫ��
    UCHAR GetPlayerLevel();         //��ҵȼ�
    DWORD GetPlayerMaxHealth();     //������Ѫ��
    static DWORD GetPlayerDataAddr();       //������ݻ�ַ
    DWORD GetPlayerID();              //id
    wchar_t* GetPlayerName();            //��
    UCHAR GetPlayerMana();          //����ֵ
    float GetPlayerMaxVit();            //�Ṧ
    float GetPlayerVit();               //��ǰ�Ṥֵ
    int GetPlayerVitStatus();       //�Ṧ״̬
    static BOOL GetPlayerPos(fPosition* PlayerPosition);                //float����
    BOOL GetPlayerPos2(sPosition* spos);            //short������
    float GetPlayerViewPoint();     //��ɫ����
    DWORD GetPlayerQuestUIStatus(); //�жϽ�ɫ�������ui״̬�Ƿ񵯳�
    DWORD GetPlayerQuestUIStatusts();   //�жϽ�ɫ�������ui״̬�Ƿ񵯳�
    static BYTE GetPlayerDeadStatus(); //����״̬
    DWORD GetCityID();
    BOOL GetPlayExperienceStatus();//��þ���ҩ״̬
	BOOL GetPlayExperienceStatusName(DWORD m_adressA,wchar_t * ExperienceName);  //��ȡ��������  ����1��UI��ַ  ����2 ��ҩƷ������
	DWORD GetExperienceNameID_SY(int i,DWORD m_adress);//��ȡ����ҩ����ID�ṹ������
	DWORD GetExperienceNameID(DWORD ID); //��ȡ��������ID
	wchar_t* GetExperienceName(DWORD ID); //��ȡ��������
	static BOOL GetPlayerFightingStatus();//���ս��״̬

    void _LinQuJiangLi();
    //����

    static ObjectNode* GetObjectBinTreeBaseAddr();
    static void GetAllObjectToVector(ObjectNode* pNode, std::vector<ObjectNode*>& RangeObject);
    DWORD GetRangeLootCount(DWORD range);
    void _GetRangeObjectToVector(ObjectNode* pNode, DWORD range, std::vector<ObjectNode*>& RangeObject);
    static void GetRangeMonsterToVector(DWORD range, std::vector<ObjectNode*>& MonsterVec);
    static void GetRangeObjectToVector(ObjectNode* pNode, DWORD range, std::vector<ObjectNode*>& RangeObject);
    void GetRangeLootObjectToVector(DWORD range, std::vector<ObjectNode*>& LootVec);
    static DWORD GetRangeMonsterCount(DWORD range = CAN_OPERATOR); //ȡ��Χ�ڹ�������, һ�������ж��Ƿ���aoe����
    void GetRangeTaskItemToVectr(std::vector<ObjectNode*>& TastItemVector, DWORD range);
    ObjectNode* GetObjectByName(wchar_t szName[], DWORD range = 500);
    static BYTE GetObjectType(DWORD pObjAddress);       //��������
    static BOOL _GetObjectPos(DWORD pObjAddress, fPosition* pos);       //ȡ��������
    static BOOL GetObjectPos(ObjectNode* pNode, fPosition* fpos);
    static BOOL GetObjectPos_0xb(DWORD pObjAddress, sPosition* spos);      //����short��������
    static BOOL GetObjectPos2_0x20(DWORD pObjAddress, fPosition* fpos);//0x20����ʹ�����ȡ����
    static BOOL GetObjectPos2_0x90(DWORD pObjAddress, sPosition* spos);//0x90����ʹ�����ȡ����
    static wchar_t* GetObjectNameByIndex(DWORD index);                   //������
    wchar_t* _GetObjectNameByIndex(DWORD index);
    static wchar_t* GetObjectName(DWORD pObjAddress);
    static DWORD GetType4HP(DWORD pObjAddress);         //��ȡ����Ϊ4�Ķ���Ѫ��
    static DWORD GetObject_0x14(DWORD pObjAddress);
    static DWORD GetObjectLevel(DWORD pObjAddress);     //ȡ����ȼ�
    static DWORD GetObjectSY12(DWORD pObjAddress);
    static DWORD GetObjectSY(DWORD pObjAddress);
    static DWORD GetObjectSy_90(DWORD pObjAddress);//ȡ90������
    static DWORD GetIndexByType(DWORD pObjAddress); //ͨ������ȡ������



    //�ж�
    BOOL isConfirmDeleteTalnetPanelShow();
    BOOL isTalentPanelShow();
    BOOL isStrikeCd(DWORD id);  //�жϼ���cd
    BOOL isPlayerDaodi();   //����״̬
    BOOL isLoots(DWORD pAddr);
    BOOL isLoading(); //�жϽ�ɫ�Ƿ��ڴ�������Ʒ�Ķ���״̬
    BOOL isSelectedSlotHavePlayer(DWORD index); //��ɫѡ����浱ǰ��ѡ����һ����ɫ����
    BOOL isQuestItem(DWORD pAddr); //�ж��Ƿ���������Ʒ
    BOOL isPlayerHasPickupQuestItemUI(); //�и�ʰȡUi������
    BOOL isPlayPickupUiStatus();//�����2�μ����ж�
    BOOL isPlayerChanneling();  //���ڶ���
    BOOL isPlayerSteping();     //���������·
    BOOL isLoginInSelectPlayer();   //�ж��Ƿ�����˽�ɫѡ����
   static int isLoadingMap();     //��ͼ״̬
    BOOL isHaveXianlu(int index);
    BOOL isCityConveyLoadingMap();
    BOOL isCityConveying();
    BOOL isPickupDeadBody();
    BOOL isDeadBody(DWORD pAddr);
    BOOL isCanFenjie(DWORD pAddr); //���Էֽ�
    BOOL isFuhuoing();
    DWORD isYaoPingCD(_BAGSTU& goods); //ҩƿcd
    DWORD isStrikeLocked(int index, DWORD pAddr);
    DWORD isStrikeCanUse(int index, DWORD pAddr);
    BOOL isBagFull();
    static BOOL isCanKill(ObjectNode* pNode);
    static BOOL isCanLook(DWORD pAddr);    //���Կ�����


    //����
    void        _GetAcceptedQuestToVector(std::vector<Quest>& QuestVec);
    void            GetAcceptedQuestToVector(std::vector<Quest>& QuestVec);
    void        DeliverQuests(DWORD id, DWORD step, DWORD questtype, DWORD ff, DWORD npcid1, DWORD npcid2, DWORD unknow, DWORD mianban);     //������
    DWORD       GetTaskStartAddr();  //��ȡ����ʼ��ַ
    DWORD       GetTaskID(int i, DWORD pAddr);  //��õ�ǰ����ID
    wchar_t*        GatTaskName(DWORD ID); //��ȡ��ǰ�ѽ���������
    DWORD       GetTaskNameID(int i, DWORD pAddr);  //��õ�ǰ��������ID
    DWORD       GetTaskPresentAddr(int i, DWORD pAddr);  //��õ�ǰ�����ַ
    DWORD       GetPresentTaskIndexes(int i, DWORD pAddr);  //��õ�ǰ�����ڼ���С����
    DWORD       GetPresentTaskEndFlag(int i, DWORD pAddr , DWORD info); //��õ�ǰС���������־
    DWORD       GetPresentTaskNum(int i, DWORD pAddr , DWORD info);  //��õ�ǰС�����Ѿ���Ĺ�����
    void        OpenQuestItem(DWORD ID, DWORD ID2);   //��������Ʒ
    DWORD       GetTaskStepById(DWORD id);
    void            _NPCJieRenWu(DWORD canshu1, DWORD canshu2, DWORD canshu3, DWORD canshu4, DWORD canshu5);//NPC������


    //ui �ͼ���
    BOOL        CloseAttendance();      //�رտ�ʼ��ҡ��
    void        SetMouseMode();         //������: ���ģʽ
    BOOL        ConfirmAgreement();     //ȷ�ϵ�¼��Ϸʱ��ʾ��Э��
    void        FaSonXianLuBao(DWORD adress1);
    void        OpenXianluUI();
    void        LoginGame(int index);   //������Ϸ
    PCHARACTER  GetCharacter(int index);    //��ɫѡ�� ui

    BOOL        ClickUI(UIOperator uiOp);   //���ui
    Tree*       GetUIBinTreeBaseAddr();
    wchar_t*    GetUIName(DWORD pBarAddr);
    wchar_t* GetUiNewName(DWORD pBarAddr);
    void        _GetUItoVector(Tree* Base, std::vector<Tree*>& Allui);
    void        GetUItoVector(Tree* pBaseAddr, std::vector<Tree*>& Allui);
    void        GetUIAddrByName(wchar_t* name, DWORD* pUIAddr);
    void    GetUiAddrByName(KONGJIAN_JIEGOU& jiegou);
    void    _GetUiAddrByName(Tree* Addr, wchar_t* name, DWORD& reAddr);
    void        GetStrikeToVector(std::vector<STRIKEINFO>& RangeObject);
    void        GetStrikeBarBaseAddr(Tree* pBaseAddr, DWORD* pStrikeBarBaseAddr);
    void        GetStrikeName(DWORD ID, DWORD IDD, STRIKENAME* pName);
    DWORD       GetStrikeStartAddr();                               //��ȡ���ܿ�ʼ��ַ
    DWORD       GetStrike_R_id(int index, DWORD p_R_addr);
    DWORD       GetStrike_R_addr(DWORD pStrikeStartAddr);
    DWORD       GetStrikeId1(int index, DWORD pStrikeStartAddr);  //ȡ����ID
    DWORD       GetStrikeId2(int index, DWORD pStrikeStartAddr);  //ȡ����ID
    DWORD       GetStrikeCD(int index, DWORD pAddr);
    BOOL        GetStrikeByName(const wchar_t* name, STRIKEINFO* pStrikeInfo);
    DWORD       GetRJianSkill(DWORD m_adress);  //ȡ����R�����������鿪ʼ��ַ
    DWORD       GetRJSkillIDDD(int i, DWORD m_adress);  //ȡR�����鼼��ID
    DWORD       GetRJSkillIDDD2(int i, DWORD m_adress);  //ȡR����������ID2
    DWORD       GetRJSkillIsJieSuo(int i, DWORD m_adress);  //ȡR�������Ƿ��Ѿ�����
    DWORD       GetRJSkillISShiYong(int i, DWORD m_adress);  //ȡR�������Ƿ����ʹ��
    DWORD       GetRJSkillCD(int i, DWORD m_adress);  //ȡR�������Ƿ���ȴ
    void Fuhuo(DWORD uiAddr);
    void DaKaiJiNengMianBan(DWORD adress, DWORD adress1); //�򿪼������


    //�ӵ�
    void JiaJiNengDian(DWORD ID); //�Ӽ��ܵ�
    void _JiaJiNengDian(DWORD ID); //�Ӽ��ܵ�
    void QuChuJiNengDian(DWORD ID); //ȥ�����ܵ�
    void _QuChuJiNengDian(DWORD ID); //ȥ�����ܵ�
    void QueRenJiNengDian(); //ȷ�ϼ��ܵ�
    void _QueRenJiNengDian(); //ȷ�ϼ��ܵ�
    void OpenDeleteTalentPanel();
    void _OpenDeleteTalentPanel();
    void DaKaiQingChuQuanBuJiNengJieMian(DWORD adress, DWORD adress1);
    void ConfirmDeletePalentPanelShowOk();
    void _ConfirmDeletePalentPanelShowOk();
    void QueRenQingChuQuanBuJiNengJieMian(DWORD adress, DWORD adress1);
    void OpenTalentUI();
    void _OpenTalentUI();


    //��Ʒ
    void        DaKaiDuiHuaKuang(DWORD ID, DWORD ID2);
    void        GuanBiDuiHuaKuangChuanKou(DWORD adress, DWORD adress1);
    void        GouMaiWuPing(DWORD Num, DWORD Ind, DWORD Adress);
    void        CunCangku(_BAGSTU& goods);              //�Ųֿ�
    void        SellItem(_BAGSTU& bag, DWORD adress);
    BOOL        OpenShangDian(wchar_t* name, DWORD* pUiAddr); //����Ʒ�Ի���
    void        CloseShangDian();
    void        DeleteItem(_BAGSTU& bag);   //�ݻ�һ����Ʒ

    //����
    void _GetAllGoodsToVector(std::vector<_BAGSTU>& RangeObject);
    static void GetAllGoodsToVector(std::vector<_BAGSTU>& RangeObject);                // ��������
    static void GetAllBodyEquipToVector(std::vector<_BAGSTU>& RangeObject);
    void _GetAllBodyEquipToVector(std::vector<_BAGSTU>& RangeObject);

    BOOL        GetAllBaGuaToVector(std::vector<_BAGSTU>& BaGuaVec);
    BOOL        GetSpecBaGuaToVector(wchar_t* name, std::vector<_BAGSTU>& BaGuaVec);
    DWORD       GetBagbodyInfoBase();               //��ȡ��������װ���ֿ����Base
    DWORD       GetBagInfoBase(DWORD pAddr);    //��ȡ��������Base
    DWORD       GetBodyInfoBase(DWORD pBase);
    DWORD       GetBagGridNumber();     //��ǰ�������ܵĸ�����
    DWORD       GetBagGridNumberLast();
    DWORD       GetGoodsBase(DWORD pAddr, int index);   //��ȡ��Ʒ���׵�ַ
    DWORD       GetGoodsID(DWORD pAddr);                //��ȡ��Ʒ��ID
    DWORD       GetGoodsNameID(DWORD pAddr);            //��ȡ��Ʒ������ID
    wchar_t*    GatBagGoodrName(DWORD ID);       //��ȡ������Ʒ����
    DWORD       GetGoodsBagInfo(DWORD m_Adress);
    DWORD       GetGoodsType(DWORD pAddr);          //��ȡ��Ʒ������
    DWORD       GetGoodsInfo(DWORD pAddr);          //��ȡ��Ʒ�����ڸ�����
    DWORD       GetGoodsNum(DWORD pAddr);           //��ȡ��Ʒ������
    DWORD       GetGoodsLasting(DWORD pAddr);       //��ȡ��Ʒ�ĳ־�
    DWORD       GetGoodsLLV(DWORD pAddr);            //��ȡ��Ʒ�ĵȼ�
    DWORD       GetCanshu_a(DWORD pAddr);       //��ҩ�ʹ�װ����Ҫ��һ������
    DWORD       Getcanshu4(DWORD pAddr);        //����4
    DWORD       Getcanshu3(DWORD pAddr);        //����3
    DWORD       Getcanshu2(DWORD pAddr);        //����2
    DWORD       Getcanshu1(DWORD pAddr);        //����1

    BOOL        GetGoodsFromBagByName(const wchar_t* name, _BAGSTU* goods);      //��������ȡ��Ʒ��Ϣ
    BOOL        GetGoodsFromBagByName(const wchar_t* name, std::vector<_BAGSTU>& GoodsVec);
    BOOL        GetGoodsFromEquipByName(wchar_t* name, _BAGSTU* goods);
    BOOL        GetGoodsByEquipPos(DWORD pos, _BAGSTU* goods);      //����λ��ȡ����Ʒ��Ϣ

    BOOL        FillGoods(_BAGSTU& goods);
    int         GetGoodsYanSe(DWORD m_Adress);  //��ȡ��Ʒ����ɫ
    DWORD       GetGoodsIsFengYin(DWORD m_Adress);  //��ȡ��Ʒ�Ƿ��ӡ
    DWORD       GetBagYouJianCaoZuoType(DWORD Adress, DWORD AAA); // ��ȡ������Ʒ�Ҽ���������
    DWORD       GetGoodsYouJianType(DWORD m_BagLeiXing, DWORD m_Info); //��ȡ������Ʒ�Ҽ���������
    DWORD       GetGoodsWuQiPingJi(DWORD m_Adress);  //��ȡ����������
    DWORD       GetGoodsWuQiDangQianJingYan(DWORD m_Adress);  //��ȡ������ǰ�ľ���
    DWORD       GetGoodsBiDui(DWORD m_Adress);  //��ȡ��Ʒ�ıȶ�
    DWORD       GetGoodsBiDui_A(DWORD m_Adress);  //��ȡ��Ʒ�ıȶ�A
    DWORD       GetBaGuaGeZiShu(DWORD m_Adress);  //��ȡ���Ը�����
    BOOL        GetGoodsByName_Hezi(wchar_t* name, std::vector<_BAGSTU>& GoodsVec); //����ö�ٺ���
    void        KaiHeZi(_BAGSTU& bag);
    BOOL        SortBag();
    BOOL        NewBag();


    //����ǿ��
    void        HeChengWuQi(_BAGSTU& zhu, _BAGSTU& fu);
    void    HeChengWuQi_Po5(_BAGSTU& zhu, _BAGSTU& fu); //�ϳ�������5
    void        HeChengWuQi_Po10(_BAGSTU& zhu, _BAGSTU& fu,DWORD adress); //�ϳ�������10
    void        JieFengZhuangBei(DWORD zhuangbei, DWORD jiefengfu_ID, DWORD num);
    void        JieFengZhuangBei(DWORD adress1, DWORD adress2, DWORD adress3, DWORD adress4, DWORD adress5, DWORD adress6, DWORD adress7); //������
    void        FenJie(_BAGSTU& bag);
	DWORD GetKaiShiAdress();//��ȡ��ʼ��ַ
	DWORD GetBiJiaoShu(int i,DWORD m_adress);//��ȡ�Ƚ���ֵ
	DWORD _IsCanShu(DWORD adress,DWORD adress1);////�Ƿ���������� 
	DWORD IsCanShu(DWORD adress,DWORD adress1);////�Ƿ���������� 
	DWORD GetBiJiaoShu1(int i,DWORD m_adress);// //��ȡ�Ƚ���ֵ1
	DWORD GetBiJiaoShu2(int i,DWORD m_adress);  //��ȡ�Ƚ���ֵ2
	DWORD GetBiJiaoShu3(DWORD m_adress);  //��ȡ�Ƚ���ֵ3
	DWORD GetBiJiaoShu4(int i,DWORD m_adress);  //��ȡ�Ƚ���ֵ4
	


    //��װ��
    void        WearEquipment(_BAGSTU& bag);
	void        _XieZhuangBei(DWORD pos);

    //����
    void        Pickup1(ObjectNode* pObj);    //��һ�μ�
    void        Pickup2(ObjectNode* pObj);   //�ڶ��μ�����
    void        Pickup2ts();   //�����2�μ���
    BOOL        Pickup(ObjectNode* pObj);     //����
    void        _PickupTask(ObjectNode* pObj);  //
    BOOL        PickupTask(ObjectNode* pNode);
    BOOL        PickupTaskts(ObjectNode* pNode);
    void        PickupDeadbody(DWORD id1, DWORD id2);
    BOOL        PickupDeadbody(DWORD range = 500);  //����ʬ��, ���߼���, �Զ�������Χ��
    void        PickdownBody(); //�������һ���������ʬ���ַ������������



    //��·
    BOOL Stepto(fPosition& tarpos, double timeOut = 10, DWORD okRange = CAN_OPERATOR, DWORD tooLong = 1000, BOOL sp3x = FALSE);
    void Step(float x, float y, float z);
    void Step3x(float x, float y, float z);
    BOOL Step(ObjectNode* pNode);
    void Stepto3x();
    void ZOULUSHUNYI(DWORD* adress, DWORD adrewss);
    void OverShunyi(BOOL bEnable); //��ͼ
    void _NewSpend(float x);
    void TiaoYue();




    //����
    int GetHealth(DWORD theValue);
    void ChiYao(_BAGSTU& goods);
    void ChiYao(const wchar_t* name);       //��ҩ, ҩ��
    void Attack(int id);
    void Attack(const wchar_t* name);



    //ת��
    void Turn(int angle);
    void TurnTo(fPosition& pos);
    void TurnTo(float x, float y, float z);     //�ӽ�



    //����, �����ļ������ȼ�����
    static BOOL UDgreater(ObjectNode* elem1, ObjectNode* elem2);
    static BOOL Kill_ApplyConfig(std::vector<ObjectNode*>& ObjectVec);


    static UINT CALLBACK KeepAliveThread(LPVOID pParam);
    static UINT CALLBACK AttackHelperThread(LPVOID pParam);


    BOOL isCustomKill_DontKill(wchar_t *name);
    BOOL isCustomKill_AlwaysKill(wchar_t *name);
    static BOOL isCustomKill_HaveName(wchar_t *name);


protected:
    HANDLE hThreads[2];
    static BOOL m_bStopThread;
    static BOOL m_bCanAoe;
    static void __stdcall ShunyiQietu();
    CCHook hookQietu;
    static Logger log;
    HANDLE m_hModuleBsEngine;
    static CustKillVector CustomName;
};



