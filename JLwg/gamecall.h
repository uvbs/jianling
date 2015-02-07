#pragma once


#include "gamedef.h"        //��Ϸ����
#include "gamedata.h"       //��Ϸ����
#include "gamestruct.h" //��Ϸ�ṹ

#include "..\common\logger.h"
#include "..\common\common.h"
#include "..\common\sharemem.h"
#include "..\common\CCHook.h"

class Gamecall
{
public:
    Gamecall();
    ~Gamecall();



   //����
    ObjectNode* GetObjectBinTreeBaseAddr();
    void GetAllObjectToVector(ObjectNode* pNode, std::vector<ObjectNode*>& RangeObject);
    DWORD GetRangeLootCount(DWORD range);
    void _GetRangeObjectToVector(ObjectNode* pNode, DWORD range,   std::vector <ObjectNode*>& RangeObject);
    void GetRangeMonsterToVector(DWORD range, std::vector<ObjectNode*>& MonsterVec);
    void GetRangeObjectToVector(ObjectNode* pNode, DWORD range, std::vector <ObjectNode*>& RangeObject);
    void GetRangeLootObjectToVector(DWORD range, std::vector<ObjectNode*>& LootVec);
    DWORD GetRangeMonsterCount(DWORD range = CAN_OPERATOR);             //ȡ��Χ�ڹ�������, һ�������ж��Ƿ���aoe����
    void GetRangeTaskItemToVectr(std::vector <ObjectNode*>& TastItemVector, DWORD range);
    ObjectNode* GetObjectByName(wchar_t szName[], DWORD range = 500);
    static BYTE GetObjectType(DWORD pObjAddress);                       //��������
    static BOOL _GetObjectPos(DWORD pObjAddress, fPosition* pos);       //ȡ��������
    static BOOL GetObjectPos(ObjectNode* pNode, fPosition* fpos);
    static BOOL GetObjectPos_0xb(DWORD pObjAddress, sPosition* spos);   //����short��������
    static BOOL GetObjectPos2_0x20(DWORD pObjAddress, fPosition* fpos);   //0x20����ʹ�����ȡ����
    wchar_t*  GetObjectNameByIndex(DWORD index);                        //������
    wchar_t*  GetObjectName(DWORD pObjAddress);
    DWORD GetType4HP(DWORD pObjAddress);        //��ȡ����Ϊ4�Ķ���Ѫ��
    DWORD GetObject_0x14(DWORD pObjAddress);
    DWORD GetObjectLevel(DWORD pObjAddress);    //ȡ����ȼ�
    DWORD GetObjectSY12(DWORD pObjAddress);
    DWORD GetObjectSY(DWORD pObjAddress);
    DWORD GetIndexByType(DWORD pObjAddress);    //ͨ������ȡ������

    
    
    void GetStrikeToVector(std::vector<STRIKEINFO>& RangeObject);
    void GetStrikeBarBaseAddr(Tree* pBaseAddr, DWORD* pStrikeBarBaseAddr);
    void GetStrikeName(DWORD ID, DWORD IDD, STRIKENAME* pName);
    DWORD GetStrikeStartAddr();         //��ȡ���ܿ�ʼ��ַ
    DWORD GetStrike_R_id(int index, DWORD p_R_addr);
    DWORD GetStrike_R_addr(DWORD pStrikeStartAddr);
    DWORD GetStrikeId1(int index, DWORD pStrikeStartAddr);  //ȡ����ID
    DWORD GetStrikeId2(int index, DWORD pStrikeStartAddr);  //ȡ����ID
    DWORD GetStrikeCD(int index, DWORD pAddr);
    BOOL GetStrikeByName(const wchar_t* name, STRIKEINFO* pStrikeInfo);
    DWORD GetRJianSkill(DWORD m_adress);                    //ȡ����R�����������鿪ʼ��ַ
    DWORD GetRJSkillIDDD(int i, DWORD m_adress);            //ȡR�����鼼��ID
    DWORD GetRJSkillIDDD2(int i, DWORD m_adress);           //ȡR����������ID2
    DWORD GetRJSkillIsJieSuo(int i, DWORD m_adress);        //ȡR�������Ƿ��Ѿ�����
    DWORD GetRJSkillISShiYong(int i, DWORD m_adress);       //ȡR�������Ƿ����ʹ��
    DWORD GetRJSkillCD(int i, DWORD m_adress);              //ȡR�������Ƿ���ȴ


    //����
    void ChiYao(_BAGSTU& goods);
    void ChiYao(const wchar_t* name);       //��ҩ, ҩ��
    void Attack(int id);
    void Attack(const wchar_t* name);



    //����
    void _GetAllGoodsToVector(std::vector<_BAGSTU>& RangeObject);
    void GetAllGoodsToVector(std::vector<_BAGSTU>& RangeObject);    // ��������
    void GetAllBodyEquipToVector(std::vector<_BAGSTU>& RangeObject);
    void _GetAllBodyEquipToVector(std::vector<_BAGSTU>& RangeObject);

    DWORD GetBagbodyInfoBase();                 //��ȡ��������װ���ֿ����Base
    DWORD GetBagInfoBase(DWORD pAddr);          //��ȡ��������Base
    DWORD GetBodyInfoBase(DWORD pBase);
    DWORD GetBagGridNumber();                   //��ǰ�������ܵĸ�����
    DWORD GetBagGridNumberLast();


    DWORD GetGoodsBase(DWORD pAddr, int index);   //��ȡ��Ʒ���׵�ַ
    DWORD GetGoodsID(DWORD pAddr);              //��ȡ��Ʒ��ID
    DWORD GetGoodsNameID(DWORD pAddr);          //��ȡ��Ʒ������ID
    wchar_t*  GatBagGoodrName(DWORD ID);        //��ȡ������Ʒ����
    DWORD GetGoodsBagInfo(DWORD m_Adress);
    DWORD GetGoodsType(DWORD pAddr);            //��ȡ��Ʒ������
    DWORD GetGoodsInfo(DWORD pAddr);            //��ȡ��Ʒ�����ڸ�����
    DWORD GetGoodsNum(DWORD pAddr);             //��ȡ��Ʒ������
    DWORD GetGoodsLasting(DWORD pAddr);         //��ȡ��Ʒ�ĳ־�
    DWORD GetGoodsLLV(DWORD pAddr);             //��ȡ��Ʒ�ĵȼ�


    BOOL FillGoods(_BAGSTU& goods);

    DWORD GetCanshu_a(DWORD pAddr);             //��ҩ�ʹ�װ����Ҫ��һ������
    DWORD Getcanshu4(DWORD pAddr);              //����4
    DWORD Getcanshu3(DWORD pAddr);              //����3
    DWORD Getcanshu2(DWORD pAddr);              //����2
    DWORD Getcanshu1(DWORD pAddr);              //����1

    int GetGoodsYanSe(DWORD m_Adress);                      //��ȡ��Ʒ����ɫ
    DWORD GetGoodsIsFengYin(DWORD m_Adress);                //��ȡ��Ʒ�Ƿ��ӡ
    DWORD GetBagYouJianCaoZuoType(DWORD Adress, DWORD AAA);   // ��ȡ������Ʒ�Ҽ���������
    DWORD GetGoodsYouJianType(DWORD m_BagLeiXing, DWORD m_Info);    //��ȡ������Ʒ�Ҽ���������
    DWORD GetGoodsWuQiPingJi(DWORD m_Adress);                       //��ȡ����������
    DWORD GetGoodsWuQiDangQianJingYan(DWORD m_Adress);              //��ȡ������ǰ�ľ���
    DWORD GetGoodsBiDui(DWORD m_Adress);    //��ȡ��Ʒ�ıȶ�
    DWORD GetGoodsBiDui_A(DWORD m_Adress);  //��ȡ��Ʒ�ıȶ�A
    DWORD GetBaGuaGeZiShu(DWORD m_Adress);  //��ȡ���Ը�����
    BOOL GetGoodsByName_Hezi(wchar_t* name, std::vector<_BAGSTU>& GoodsVec);    //����ö�ٺ���
    void KaiHeZi(_BAGSTU& bag);
    BOOL SortBag();
    BOOL NewBag();


    DWORD GetMuQianJingYanZongZhi(DWORD Adress);
    DWORD GetMuQianJingYanZongZhi_A(DWORD Adress);


    
    BYTE ReadByte(DWORD addr);
    WORD ReadWORD(DWORD addr);
    DWORD ReadDWORD(DWORD addr);
    int ReadInt(DWORD addr);
    float ReadFloat(DWORD addr);
    char*  ReadStr(DWORD addr);


    BOOL ClickUI(UIOperator uiOp);      //���ui

    wchar_t*  GetUIName(DWORD pBarAddr);
    wchar_t*  GetUiNewName(DWORD pBarAddr);




    Tree*  GetUIBinTreeBaseAddr();

    void _GetUItoVector(Tree* Base, std::vector<Tree*>& Allui);
    void GetUItoVector(Tree* pBaseAddr, std::vector<Tree*>& Allui);
    void GetUIAddrByName(wchar_t* name, DWORD* pUIAddr);
    void GetUiAddrByName(KONGJIAN_JIEGOU& jiegou);
    void _GetUiAddrByName(Tree* Addr, wchar_t* name, DWORD& reAddr);




      //���
    DWORD GetPlayerHealth();                                //���Ѫ��
    UCHAR GetPlayerLevel();                                 //��ҵȼ�
    DWORD GetPlayerMaxHealth();                             //������Ѫ��
    static DWORD GetPlayerDataAddr();                       //������ݻ�ַ
    DWORD GetPlayerID();                                    //id
    wchar_t*  GetPlayerName();                              //��
    UCHAR GetPlayerMana();                                  //����ֵ
    float GetPlayerMaxVit();                                //�Ṧ
    float GetPlayerVit();                                   //��ǰ�Ṥֵ
    int GetPlayerVitStatus();                               //�Ṧ״̬
    static BOOL GetPlayerPos(fPosition* PlayerPosition);    //float����
    BOOL GetPlayerPos2(sPosition* spos);                    //short������
    float GetPlayerViewPoint();     //��ɫ����
    DWORD GetPlayerQuestUIStatus(); //�жϽ�ɫ�������ui״̬�Ƿ񵯳�
    BYTE GetPlayerDeadStatus();     //����״̬
    DWORD GetCityID();
    BOOL GetPlayExperienceStatus(); //��þ���ҩ״̬





    BOOL Init();
    BOOL LoginInGame(DWORD index);


    //�ȴ�
    void WaitPlans();               //�ȴ���ͼ �˺������ر�ʾ��ͼ���
    void WaitGameCreate();


    //��Ϸ����
    HWND GetGamehWnd()
    {
        return m_hGameWnd;
    }



    void InitSpeed();

    void KeyPress(WPARAM vk);

    //��ȡ��Ϸ����
    HWND isGameWndCreated(DWORD dwPid);   //�ж���Ϸ�����Ƿ񴴽�


    //��װ�ĵ���call, ͨ����Ϣ
    DWORD call(DWORD id, LPVOID pParam);
    DWORD sendcall(DWORD id, LPVOID pParam);




    //�ж϶����ɱ������
    DWORD m_Get11C(DWORD m_Adress);   //�� ==1 ����
    DWORD m_Get110(DWORD m_Adress);   //==1 ���������ж�, ==2��npc
    DWORD m_Get2E4(DWORD m_Adress);   //==0 npc, else ����



    //����
    void SetShuyiPath(TCHAR* szPath);
    void SetIniPath(TCHAR* szPath);



    void HookQietu(BOOL bEnable);       //hook ��ͼ
    static DWORD CalcC(fPosition& p1, fPosition& p2);       //���������������
    static fPosition ShortPosToFloatPos(sPosition& shortp);   //����ת��
    void* GetStepCallAddr();        //ȡ��·call�ĵ�ַ
    void RandomStep(DWORD range);   //��ĳ�����������
    void JingDianMoShi(DWORD adress, DWORD adress1);    //����ģʽ
    void ChangeZ_Status(BOOL flag);//��״̬
    void ChangeHeight(float how);

    TCHAR* GetLujingPath()
    {
        return m_szLujingPath;
    }
    TCHAR* GetConfigPath()
    {
        return m_szConfigPath;
    }
    TCHAR* GetLujingTest()
    {
        return m_szLujingTest;
    }




    //ǿ��
    void XieBaoShi(DWORD canshu1, DWORD canshu2, DWORD canshu3);
    void JiaBaoShi(DWORD canshu1, DWORD canshu2, DWORD canshu3, DWORD canshu4, DWORD canshu5);



    //��·
    void HuanXian(int xianlu);                              //����
    DWORD GetXianluNums();                                  //��ȡ��·yun
    UCHAR GetPlayerXianlu();
    void DunDi(DWORD cityid);



    void _LinQuJiangLi();


    //�ж�
    BOOL isConfirmDeleteTalnetPanelShow();
    BOOL isTalentPanelShow();
    BOOL isStrikeCd(DWORD id);                  //�жϼ���cd
    BOOL isPlayerDaodi();                       //����״̬
    BOOL isLoots(DWORD pAddr);
    BOOL isLoading();   //�жϽ�ɫ�Ƿ��ڴ�������Ʒ�Ķ���״̬
    BOOL isSelectedSlotHavePlayer(DWORD index);   //��ɫѡ����浱ǰ��ѡ����һ����ɫ����
    BOOL isQuestItem(DWORD pAddr);              //�ж��Ƿ���������Ʒ
    BOOL isPlayerHasPickupQuestItemUI();        //�и�ʰȡUi������
    BOOL isPlayerChanneling();                  //���ڶ���
    BOOL isPlayerSteping();                     //���������·
    BOOL isLoginInSelectPlayer();               //�ж��Ƿ�����˽�ɫѡ����
    int isLoadingMap();                 //��ͼ״̬
    BOOL isHaveXianlu(int index);
    BOOL isCityConveyLoadingMap();
    BOOL isCityConveying();
    BOOL isPickupDeadBody();
    BOOL isDeadBody(DWORD pAddr);
    BOOL isCanFenjie(DWORD pAddr);      //���Էֽ�
    BOOL isFuhuoing();
    DWORD isYaoPingCD(_BAGSTU& goods);  //ҩƿcd
    DWORD isStrikeLocked(int index, DWORD pAddr);
    DWORD isStrikeCanUse(int index, DWORD pAddr);
    BOOL isBagFull();
    BOOL isCanKill(ObjectNode* pNode);
    BOOL isCanLook(DWORD pAddr);        //���Կ�����



    //����
    void _GetAcceptedQuestToVector(std::vector<Quest>& QuestVec);
    void GetAcceptedQuestToVector(std::vector<Quest>& QuestVec);
    void DeliverQuests(DWORD id, DWORD step, DWORD questtype, DWORD ff, DWORD npcid1, DWORD npcid2, DWORD unknow, DWORD mianban);   //������
    DWORD GetTaskStartAddr();                       //��ȡ����ʼ��ַ
    DWORD GetTaskID(int i, DWORD pAddr);            //��õ�ǰ����ID
    wchar_t*  GatTaskName(DWORD ID);                //��ȡ��ǰ�ѽ���������
    DWORD GetTaskNameID(int i, DWORD pAddr);        //��õ�ǰ��������ID
    DWORD GetTaskPresentAddr(int i, DWORD pAddr);   //��õ�ǰ�����ַ
    DWORD GetPresentTaskIndexes(int i, DWORD pAddr);                //��õ�ǰ�����ڼ���С����
    DWORD GetPresentTaskEndFlag(int i, DWORD pAddr, DWORD info);    //��õ�ǰС���������־
    DWORD GetPresentTaskNum(int i, DWORD pAddr, DWORD info);        //��õ�ǰС�����Ѿ���Ĺ�����
    void OpenQuestItem(DWORD ID, DWORD ID2);                        //��������Ʒ
    DWORD GetTaskStepById(DWORD id);
    void _NPCJieRenWu(DWORD canshu1, DWORD canshu2, DWORD canshu3, DWORD canshu4, DWORD canshu5);   //NPC������



    //ui �ͼ���
    BOOL CloseAttendance();             //�رտ�ʼ��ҡ��
    void SetMouseMode();                //������: ���ģʽ
    BOOL ConfirmAgreement();            //ȷ�ϵ�¼��Ϸʱ��ʾ��Э��
    void FaSonXianLuBao(DWORD adress1);
    void OpenXianluUI();



    //�ӵ�
        void DaKaiJiNengMianBan(DWORD adress, DWORD adress1);   //�򿪼������
    void JiaJiNengDian(DWORD ID);                                   //�Ӽ��ܵ�
    void _JiaJiNengDian(DWORD ID);                                  //�Ӽ��ܵ�
    void QuChuJiNengDian(DWORD ID);                                 //ȥ�����ܵ�
    void _QuChuJiNengDian(DWORD ID);                                //ȥ�����ܵ�
    void QueRenJiNengDian();                                        //ȷ�ϼ��ܵ�
    void _QueRenJiNengDian();                                       //ȷ�ϼ��ܵ�
    void OpenDeleteTalentPanel();
    void _OpenDeleteTalentPanel();
    void DaKaiQingChuQuanBuJiNengJieMian(DWORD adress, DWORD adress1);
    void ConfirmDeletePalentPanelShowOk();
    void _ConfirmDeletePalentPanelShowOk();
    void QueRenQingChuQuanBuJiNengJieMian(DWORD adress, DWORD adress1);
    void OpenTalentUI();
    void _OpenTalentUI();



    //��Ʒ
    void DaKaiDuiHuaKuang(DWORD ID, DWORD ID2);
    void GuanBiDuiHuaKuangChuanKou(DWORD adress, DWORD adress1);
    void GouMaiWuPing(DWORD Num, DWORD Ind, DWORD Adress);
    void CunCangku(_BAGSTU& goods);                                 //�Ųֿ�
    void SellItem(_BAGSTU& bag, DWORD adress);
    BOOL OpenShangDian(wchar_t* name, DWORD* pUiAddr);              //����Ʒ�Ի���
    void CloseShangDian();
    void DeleteItem(_BAGSTU& bag);                                  //�ݻ�һ����Ʒ



    BOOL GetAllBaGuaToVector(std::vector<_BAGSTU>& BaGuaVec);
    BOOL GetSpecBaGuaToVector(wchar_t* name, std::vector<_BAGSTU>& BaGuaVec);



    BOOL GetGoodsFromBagByName(const wchar_t* name, _BAGSTU* goods);    //��������ȡ��Ʒ��Ϣ
    BOOL GetGoodsFromBagByName(const wchar_t* name, std::vector<_BAGSTU>& GoodsVec);
    BOOL GetGoodsFromEquipByName(wchar_t* name, _BAGSTU* goods);
    BOOL GetGoodsByEquipPos(DWORD pos, _BAGSTU* goods);                 //����λ��ȡ����Ʒ��Ϣ




    //����ǿ��
    void HeChengWuQi(_BAGSTU& zhu, _BAGSTU& fu);
    void HeChengWuQi_Po5(_BAGSTU& zhu, _BAGSTU& fu);    //�ϳ�������5
    void HeChengWuQi_Po10(DWORD zhu, DWORD fu, DWORD adress);
    void JieFengZhuangBei(DWORD zhuangbei, DWORD jiefengfu_ID, DWORD num);
    void JieFengZhuangBei(DWORD adress1, DWORD adress2, DWORD adress3, DWORD adress4, DWORD adress5, DWORD adress6, DWORD adress7);   //������
    void FenJie(_BAGSTU& bag);


    void WearEquipment(_BAGSTU& bag);
    void LoginGame(int index);          //������Ϸ
    PCHARACTER GetCharacter(int index);   //��ɫѡ�� ui

    //����
    void Pickup1(ObjectNode* pObj);         //��һ�μ�
    void Pickup2(ObjectNode* pObj);         //�ڶ��μ�����
    BOOL Pickup(ObjectNode* pObj);          //����
    void _PickupTask(ObjectNode* pObj);     //
    BOOL PickupTask(ObjectNode* pNode);
    void PickupDeadbody(DWORD id1, DWORD id2);
    BOOL PickupDeadbody(DWORD range = 500); //����ʬ��, ���߼���, �Զ�������Χ��
    void PickdownBody();                    //�������һ���������ʬ���ַ������������



    //��·
    BOOL Stepto(fPosition& tarpos, double timeOut = 10, DWORD okRange = CAN_OPERATOR, DWORD tooLong = 1000, BOOL sp3x = FALSE);
    void Step(float x, float y, float z);
    void Step3x(float x, float y, float z);
    BOOL Step(ObjectNode* pNode);
    void Stepto3x();
    void ZOULUSHUNYI(DWORD* adress, DWORD adrewss);
    void OverShunyi(BOOL bEnable);          //��ͼ
    void _NewSpend(float x);
    void TiaoYue();

    int GetHealth(DWORD theValue);
    void Fuhuo(DWORD uiAddr);

    //ת��
    void Turn(int angle);
    void TurnTo(fPosition& pos);
    void TurnTo(float x, float y, float z);   //�ӽ�



    //����, �����ļ������ȼ�����
    static BOOL UDgreater(ObjectNode* elem1, ObjectNode* elem2);
    BOOL Kill_ApplyConfig(std::vector <ObjectNode*>& ObjectVec);



    //�����߳�, ��Ѫ, ��С����
    static unsigned CALLBACK KeepAliveThread(PVOID pParam);

    //ɱ���߼�
    static unsigned CALLBACK AttackThread(PVOID pParam);
    



    SHAREINFO* GetAccountInfo()
    {
        return m_ShareMem.GetMemAddr();
    };



protected:

    typedef int (*_InitializeSpeedhack)(float);
    _InitializeSpeedhack m_pfnInitSpeed;


    CCHook ce_hookGetTickCount;
    CCHook ce_hookQueryPerformanceCounter;
    CCHook ce_hooktimeGetTime;
    CCHook hookQietu;


    HMODULE m_hack; //����ģ����
    HWND m_hGameWnd;
    Logger log;

    HANDLE m_hModuleBsEngine;

    BOOL m_bAliveStop;
    HANDLE hEvenStop;


    //�����ļ�
    TCHAR m_szLujingPath[MAX_PATH];
    TCHAR m_szConfigPath[MAX_PATH];
    TCHAR m_szLujingTest[MAX_PATH];

    ShareMem m_ShareMem;

};
