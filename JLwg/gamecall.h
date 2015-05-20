#ifndef _GAMECALL_H_
#define _GAMECALL_H_


#ifdef JLTW
#include "gamedata-tw.h"
#include "gamedata-tw_new.h"
#else
#include "gamedata.h"
#endif


#include "gamedef.h"
#include "gamestruct.h"


typedef std::vector<CUSTOMKILL> CustKillVector;
typedef std::vector<ObjectNode*> ObjectVector;
typedef std::vector<BAGSTU> BagVector;
typedef std::vector<Team> TeamVector;


class Gamecall
{
protected:
    Gamecall();
    ~Gamecall();

    DECLARE_SINGLETON(Gamecall)

public:
    BOOL Init();


    //�ȴ�
    bool WaitPlans(int inMaxTime = 30);   //�ȴ���ͼ �˺������ر�ʾ��ͼ���
    BOOL LoginInGame(DWORD index);

    //�ж϶����ɱ������
    DWORD m_Get11C(DWORD m_Adress);   //�� ==1 ����
    DWORD m_Get110(DWORD m_Adress); //==1 ���������ж�, ==2��npc
    DWORD m_Get2E4(DWORD m_Adress);   //==0 npc, else ����


    //����
    void HookQietu(BOOL bEnable);   //hook ��ͼ
    void KeyPress(WPARAM vk);
    DWORD CalcC(fPosition& p1, fPosition& p2);      //���������������
    void ShortPosToFloatPos(sPosition& spos, fPosition& fpos);   //����ת��
    void RandomStep(DWORD range);               //��ĳ�����������
    void JingDianMoShi(DWORD adress, DWORD adress1);  //����ģʽ
    void CloseXiaoDongHua();



    void ChangeZ_Status(BOOL flag);//��״̬
    void ChangeHeight(float how);


    //��װ�ĵ���call, ͨ����Ϣ
    DWORD call(DWORD id, LPVOID pParam);
    DWORD sendcall(DWORD id, LPVOID pParam);

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
    UCHAR GetPlayerLevel();             //��ҵȼ�
    DWORD GetPlayerMaxHealth();         //������Ѫ��
    DWORD GetPlayerDataAddr();          //������ݻ�ַ
    DWORD GetPlayerID();                //id
    wchar_t* GetPlayerName();           //��
    UCHAR GetPlayerMana();              //����ֵ
    float GetPlayerMaxVit();            //�Ṧ
    float GetPlayerVit();               //��ǰ�Ṥֵ
    int GetPlayerVitStatus();           //�Ṧ״̬
    BOOL GetPlayerPos(fPosition* fpos);   //float����
    BOOL GetPlayerPos2(sPosition* spos);            //short������
    float GetPlayerViewPoint();         //��ɫ����
    DWORD GetPlayerQuestUIStatus();     //�жϽ�ɫ�������ui״̬�Ƿ񵯳�
    DWORD GetPlayerQuestUIStatusts();   //�жϽ�ɫ�������ui״̬�Ƿ񵯳�
    BYTE GetPlayerDeadStatus();         //����״̬
    DWORD GetCityID();
    BOOL GetPlayExperienceStatus();     //��þ���ҩ״̬
    BOOL GetPlayExperienceStatusName(DWORD m_adressA, wchar_t* ExperienceName);  //��ȡ��������  ����1��UI��ַ  ����2 ��ҩƷ������
    DWORD GetExperienceNameID_SY(int i, DWORD m_adress); //��ȡ����ҩ����ID�ṹ������
    DWORD GetExperienceNameID(DWORD ID);        //��ȡ��������ID
    wchar_t* GetExperienceName(DWORD ID);       //��ȡ��������
    BOOL GetPlayerFightingStatus();             //���ս��״̬
    BOOL GetPlayerSkillStatus();                //����Ƿ�����ʹ�ü���״̬
    BOOL GetPlayerBusy();                       //��ɫ��ǰ�Ƿ�����æµ
    DWORD GetPlarerRedHeart();                  //��ȡ����ɫ��������



    void _LinQuJiangLi();



    //����
    ObjectNode* GetObjectBinTreeBaseAddr();
    void GetAllObjectToVector(ObjectNode* pNode, ObjectVector& RangeObject);
    void _GetRangeObjectToVector(ObjectNode* pNode, DWORD range, ObjectVector& RangeObject);
    void GetRangeMonsterToVector(DWORD range, ObjectVector& MonsterVec);
    void GetRangeObjectToVector(ObjectNode* pNode, DWORD range, ObjectVector& RangeObject);
    void GetRangeLootObjectToVector(DWORD range, ObjectVector& LootVec);
    void GetRangeTaskItemToVectr(ObjectVector& TastItemVector, DWORD range);
    ObjectNode* GetObjectByName(const wchar_t szName[], DWORD range = 500);
    BYTE GetObjectType(DWORD pObjAddress);                          //��������
    BOOL _GetObjectPos(DWORD pObjAddress, fPosition* pos);          //ȡ��������
    BOOL GetObjectPos(ObjectNode* pNode, fPosition* fpos);
    BOOL GetObjectPos_0xb(DWORD pObjAddress, sPosition* spos);      //����short��������
    BOOL GetObjectPos2_0x20(DWORD pObjAddress, fPosition* fpos);    //0x20����ʹ�����ȡ����
    BOOL GetObjectPos2_0x90(DWORD pObjAddress, sPosition* spos);    //0x90����ʹ�����ȡ����
    wchar_t* GetObjectNameByIndex(DWORD index);                     //������
    wchar_t* _GetObjectNameByIndex(DWORD index);
    wchar_t* GetObjectName(DWORD pObjAddress);
    DWORD GetObjectHP(DWORD pObjAddress);            //��ȡ����Ϊ4�Ķ���Ѫ��
    DWORD GetObject_0x14(DWORD pObjAddress);
    DWORD GetObjectLevel(DWORD pObjAddress);        //ȡ����ȼ�
    DWORD GetObjectSY12(DWORD pObjAddress);
    DWORD GetObjectSY(DWORD pObjAddress);
    DWORD GetObjectSy_90(DWORD pObjAddress);        //ȡ90������
    DWORD GetIndexByType(DWORD pObjAddress);        //ͨ������ȡ������
    DWORD GetObjectView(DWORD pObjAddress);         //��ȡ����Ƕ�
	DWORD GetObjectTargetId(DWORD pObjAddress);     //��ȡ����Ŀ��
	ObjectNode* GetObjectById(DWORD Id);            //����ID��ȡ�����ַ
	BOOL IsObjectFightStatus(DWORD pObjAddress);   //��ȡ����ս��״̬
	BOOL IsPlayerSkillStatus(DWORD pObjAddress);    //��ö����Ƿ�����ʹ�ü���״̬
	BOOL IsObjectControl(DWORD pObjAddress);        //��ö����Ƿ����˫��




    //�ж�
    BOOL        isConfirmDeleteTalnetPanelShow();
    BOOL        isTalentPanelShow();
    BOOL        isStrikeCd(DWORD id);  //�жϼ���cd
	BOOL        isStrkeId(DWORD id);   //�ж��Ƿ�������˼���
    BOOL        isPlayerDaodi();   //����״̬
    BOOL        isLoots(DWORD pAddr);
    BOOL        isLoading(); //�жϽ�ɫ�Ƿ��ڴ�������Ʒ�Ķ���״̬
    BOOL        isSelectedSlotHavePlayer(DWORD index); //��ɫѡ����浱ǰ��ѡ����һ����ɫ����
    BOOL        isQuestItem(DWORD pAddr); //�ж��Ƿ���������Ʒ
    BOOL        isPlayerHasPickupQuestItemUI(); //�и�ʰȡUi������
    BOOL        isPlayPickupUiStatus();//�����2�μ����ж�
    BOOL        isPlayerChanneling();  //���ڶ���
    BOOL        isPlayerSteping();     //���������·
    BOOL        isLoginInSelectPlayer();   //�ж��Ƿ�����˽�ɫѡ����
    int         isLoadingMap();     //��ͼ״̬
    BOOL        isHaveXianlu(int index);
    BOOL        isCityConveyLoadingMap();
    BOOL        isCityConveying();
    BOOL        isPickupDeadBody();
    BOOL        isDeadBody(DWORD pAddr);
    BOOL        isCanFenjie(DWORD pAddr); //���Էֽ�
    BOOL        isFuhuoing();
    DWORD       isYaoPingCD(_BAGSTU& goods); //ҩƿcd
    DWORD       isStrikeLocked(int index, DWORD pAddr);
    DWORD       isStrikeCanUse(int index, DWORD pAddr);
    BOOL        isBagFull();
    BOOL        isCanKill(ObjectNode* pNode);
    BOOL        isCanLook(DWORD pAddr);    //���Կ�����


    //����
    void        _GetAcceptedQuestToVector(std::vector<Quest>& QuestVec);
    void        GetAcceptedQuestToVector(std::vector<Quest>& QuestVec);
    void        DeliverQuests(DWORD id, DWORD step, DWORD questtype, DWORD ff, DWORD npcid1, DWORD npcid2, DWORD unknow, DWORD mianban);     //������
    DWORD       GetTaskStartAddr();  //��ȡ����ʼ��ַ
    DWORD       GetTaskID(int i, DWORD pAddr);  //��õ�ǰ����ID
    wchar_t*    GatTaskName(DWORD ID); //��ȡ��ǰ�ѽ���������
    DWORD       GetTaskNameID(int i, DWORD pAddr);  //��õ�ǰ��������ID
    DWORD       GetTaskPresentAddr(int i, DWORD pAddr);  //��õ�ǰ�����ַ
    DWORD       GetPresentTaskIndexes(int i, DWORD pAddr);  //��õ�ǰ�����ڼ���С����
    DWORD       GetPresentTaskEndFlag(int i, DWORD pAddr , DWORD info); //��õ�ǰС���������־
    DWORD       GetPresentTaskNum(int i, DWORD pAddr , DWORD info);  //��õ�ǰС�����Ѿ���Ĺ�����
    void        OpenQuestItem(DWORD ID, DWORD ID2);   //��������Ʒ
    DWORD       GetTaskStepById(DWORD id);
    void        _NPCJieRenWu(DWORD canshu1, DWORD canshu2, DWORD canshu3, DWORD canshu4, DWORD canshu5);//NPC������


    //ui �ͼ���
    BOOL        CloseAttendance();      //�رտ�ʼ��ҡ��
    void        SetMouseMode();         //������: ���ģʽ
    BOOL        ConfirmAgreement();     //ȷ�ϵ�¼��Ϸʱ��ʾ��Э��
    void        FaSonXianLuBao(DWORD adress1);
    void        OpenXianluUI();
    void        LoginGame(int index);   //������Ϸ


    BOOL        ClickUI(UIOperator uiOp);   //���ui
    Tree*       GetUIBinTreeBaseAddr();
    wchar_t*    GetUIName(DWORD pBarAddr);
    wchar_t*    GetUiNewName(DWORD pBarAddr);
    void        _GetUItoVector(Tree* Base, std::vector<Tree*>& Allui);
    void        GetUItoVector(Tree* pBaseAddr, std::vector<Tree*>& Allui);
    void        GetUIAddrByName(wchar_t* name, DWORD* pUIAddr);
    void        GetUiAddrByName(KONGJIAN_JIEGOU& jiegou);
    void        _GetUiAddrByName(Tree* Addr, wchar_t* name, DWORD& reAddr);
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
    void        Fuhuo(DWORD uiAddr);
    void        DaKaiJiNengMianBan(DWORD adress, DWORD adress1); //�򿪼������


    //�ӵ�
    void    JiaJiNengDian(DWORD ID); //�Ӽ��ܵ�
    void    _JiaJiNengDian(DWORD ID); //�Ӽ��ܵ�
    void    QuChuJiNengDian(DWORD ID); //ȥ�����ܵ�
    void    _QuChuJiNengDian(DWORD ID); //ȥ�����ܵ�
    void    QueRenJiNengDian(); //ȷ�ϼ��ܵ�
    void    _QueRenJiNengDian(); //ȷ�ϼ��ܵ�
    void    OpenDeleteTalentPanel();
    void    _OpenDeleteTalentPanel();
    void    DaKaiQingChuQuanBuJiNengJieMian(DWORD adress, DWORD adress1);
    void    ConfirmDeletePalentPanelShowOk();
    void    _ConfirmDeletePalentPanelShowOk();
    void    QueRenQingChuQuanBuJiNengJieMian(DWORD adress, DWORD adress1);
    void    OpenTalentUI();
    void    _OpenTalentUI();


    //��Ʒ
    void        DaKaiDuiHuaKuang(DWORD ID, DWORD ID2);
    void        GuanBiDuiHuaKuangChuanKou(DWORD adress, DWORD adress1);
    void        GouMaiWuPing(DWORD Num, DWORD Ind, DWORD Adress);
    void        CunCangku(_BAGSTU& goods);              //�Ųֿ�
    void        SellItem(_BAGSTU& bag, DWORD adress);
    BOOL        OpenShangDian(wchar_t* name, DWORD* pUiAddr); //����Ʒ�Ի���
    void        CloseShangDian();
    void        DeleteItem(_BAGSTU* bag);   //�ݻ�һ����Ʒ

    //����
    void        _GetAllGoodsToVector(BagVector& RangeObject);
    void        GetAllGoodsToVector(BagVector& RangeObject);                // ��������
    void        GetAllBodyEquipToVector(BagVector& RangeObject);
    void        _GetAllBodyEquipToVector(BagVector& RangeObject);

    BOOL        GetAllBaGuaToVector(BagVector& BaGuaVec);
    BOOL        GetSpecBaGuaToVector(wchar_t* name, BagVector& BaGuaVec);
    DWORD       GetBagbodyInfoBase();                   //��ȡ��������װ���ֿ����Base
    DWORD       GetBagInfoBase(DWORD pAddr);            //��ȡ��������Base
    DWORD       GetBodyInfoBase(DWORD pBase);
    DWORD       GetBagGridNumber();                     //��ǰ�������ܵĸ�����
    DWORD       GetGoodsBase(DWORD pAddr, int index);   //��ȡ��Ʒ���׵�ַ
    DWORD       GetGoodsID(DWORD pAddr);                //��ȡ��Ʒ��ID
    DWORD       GetGoodsNameID(DWORD pAddr);            //��ȡ��Ʒ������ID
    DWORD       GetGoodsBagInfo(DWORD m_Adress);
    DWORD       GetGoodsType(DWORD pAddr);          //��ȡ��Ʒ������
    DWORD       GetGoodsPos(DWORD pAddr);           //��ȡ��Ʒ�����ڸ�����
    DWORD       GetGoodsNum(DWORD pAddr);           //��ȡ��Ʒ������
    DWORD       GetGoodsDur(DWORD pAddr);           //��ȡ��Ʒ�ĳ־�
    DWORD       GetGoodsLV(DWORD pAddr);            //��ȡ��Ʒ�ĵȼ�


    BOOL        GetGoodsFromBagByName(std::wstring name, BagVector& GoodsVec);
    BOOL        GetGoodsFromEquipByName(wchar_t* name, _BAGSTU* goods);
    BOOL        GetGoodsByEquipPos(DWORD pos, _BAGSTU* goods);      //����λ��ȡ����Ʒ��Ϣ


    BOOL        FillGoods(_BAGSTU& goods);
    int         GetGoodsColor(DWORD m_Adress);  //��ȡ��Ʒ����ɫ
    char        GetGoodsIsFengYin(DWORD m_Adress);  //��ȡ��Ʒ�Ƿ��ӡ
    DWORD       GetBagYouJianCaoZuoType(DWORD Adress, DWORD AAA); // ��ȡ������Ʒ�Ҽ���������
    DWORD       GetGoodsYouJianType(DWORD m_BagLeiXing, DWORD m_Info); //��ȡ������Ʒ�Ҽ���������
    DWORD       GetGoodsWuQiPingJi(DWORD m_Adress);  //��ȡ����������
    DWORD       GetGoodsWuQiDangQianJingYan(DWORD m_Adress);  //��ȡ������ǰ�ľ���
    DWORD       GetGoodsBiDui(DWORD m_Adress);  //��ȡ��Ʒ�ıȶ�
    DWORD       GetGoodsBiDui_A(DWORD m_Adress);  //��ȡ��Ʒ�ıȶ�A
    DWORD       GetBaGuaGeZiShu(DWORD m_Adress);  //��ȡ���Ը�����
    BOOL        GetGoodsByName_Hezi(wchar_t* name, BagVector& GoodsVec); //����ö�ٺ���
    void        KaiHeZi(_BAGSTU& bag);
    DWORD       SortBag();  //������
    BOOL        NewBag();


    //����ǿ��
    void  HeChengWuQi(_BAGSTU& zhu, _BAGSTU& fu);
    void  HeChengWuQi_Po5(_BAGSTU& zhu, _BAGSTU& fu); //�ϳ�������5
    void  HeChengWuQi_Po10(_BAGSTU& zhu, _BAGSTU& fu, DWORD adress); //�ϳ�������10
    void  JieFengZhuangBei(DWORD zhuangbei, DWORD jiefengfu_ID, DWORD num);
    void  JieFengZhuangBei(DWORD adress1, DWORD adress2, DWORD adress3, DWORD adress4, DWORD adress5, DWORD adress6, DWORD adress7); //������
    void  FenJie(_BAGSTU& bag);
    DWORD GetKaiShiAdress();//��ȡ��ʼ��ַ
    DWORD GetBiJiaoShu(int i, DWORD m_adress); //��ȡ�Ƚ���ֵ
    DWORD _IsCanShu(DWORD adress, DWORD adress1); ////�Ƿ����������
    DWORD IsCanShu(DWORD adress, DWORD adress1); ////�Ƿ����������
    DWORD GetBiJiaoShu1(int i, DWORD m_adress); // //��ȡ�Ƚ���ֵ1
    DWORD GetBiJiaoShu2(int i, DWORD m_adress); //��ȡ�Ƚ���ֵ2
    DWORD GetBiJiaoShu3(DWORD m_adress);  //��ȡ�Ƚ���ֵ3
    DWORD GetBiJiaoShu4(int i, DWORD m_adress); //��ȡ�Ƚ���ֵ4



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
    int _Attack(int id);
    void Attack(const wchar_t* name);


    //ת��
    void Turn(int angle);
    void TurnTo(fPosition& pos);
    void TurnTo(float x, float y, float z);     //�ӽ�



    //����, �����ļ������ȼ�����
    static BOOL UDgreater(ObjectNode* elem1, ObjectNode* elem2);

    //���
    void TuiChuDuiWu(); //�˳�����
    void YaoQingZuDui(DWORD ID, DWORD Info); /*������� ����1�Ƕ���ID ����2 ����10000��ֵ */;
    DWORD DuiWu_EndAdress() /*��������Ľ�����ַ */;
	DWORD DuiWu_StartAdress();//���鿪ʼ��ַ
	BOOL GetPartyInfo(TeamVector& TeamInfo);//��ȡ������Ϣ
	DWORD GetPartyByAddress(DWORD PartyAddress,int i);//��ȡ��ǰ��ɫ��ַ
	wchar_t* GetPartyName(DWORD PartyAddress);//��ȡ�����ɫ��
	DWORD GetPartyChannel(DWORD PartyAddress);//��ȡ��ɫ��ǰƵ��
	DWORD GetPartyCurrlife(DWORD PartyAddress);//��ȡ��ɫ��ǰѪֵ
	DWORD GetPartyMaxlife(DWORD PartyAddress);//��ȡ��ɫ���Ѫֵ
	DWORD GetPartyId(DWORD PartyAddress);//��ȡ��ɫid
	DWORD GetPartyId2(DWORD PartyAddress);//��ȡ��ɫid2
	fPosition GetPartyPos(DWORD PartyAddress);//��ȡ��ɫx����
	DWORD GetPartyAngle(DWORD PartyAddress);//��ȡ��ɫ����
	DWORD GetPartyLv(DWORD PartyAddress);//��ȡ��ɫ�ȼ�
private:
    HANDLE m_hModuleBsEngine;
};


//��������
BYTE ReadByte(DWORD addr);
WORD ReadWORD(DWORD addr);
DWORD ReadDWORD(DWORD addr);
int ReadInt(DWORD addr);
float ReadFloat(DWORD addr);
wchar_t* ReadStr(DWORD addr);


#endif
