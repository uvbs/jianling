#pragma once


#include "gamedata.h"
#include "gamestruct.h"

#include "..\common\logger.h"		
#include "..\common\common.h"
#include "..\common\CCHook.h"
#include "..\common\sharemem.h"

//��������ַ������������Ӧ�ĵ�����Ϣ

#define __L(x) ___L(x)
#define ___L(x) L##x


#if _MSC_VER > 1200
#ifdef _UNICODE
#define FUNCNAME __FUNCTIONW__
#else
#define FUNCNAME __FUNCTION__
#endif
#else 
#define FUNCNAME __L(__FILE__)
#endif


#define			RESULT_KILL_OK					0
#define			RESULT_KILL_PLAYDEAD			1
#define			RESULT_KILL_TIMEOUT				2
#define			RESULT_KILL_FAIL				3 

//ɱ��ģʽ, Ĭ��ֻNormal
//����Ӧ�ö��ɱ��ģʽ, ���� modeNormal | modeSpend | modeTask | modeAoe
#define			modeNormal						1	//����ͨ����, �����÷�Χ����
#define			modeAoe							4	//AOE
#define			modeTask						8	//����, Ӱ���˳��߼����ж�
#define			modeGoback						16	//ɱ���ԭ��
#define			modePickup						32	//ɱ���Լ���
#define			modePickupBody					64	//ɱ�����ʬ��	
#define			modePickupOnce					128 //�ɵ�һ����һ�ε���


/*״̬����*/
#define		NORTH				0		//����
#define		SOUTH				32778   //��
#define		WEST				49167   //��
#define		EAST				16389	//��

#define		VIT_STATUS_USED		1   //ʹ�����Ṧ
#define		VIT_STATUS_RENEW	2	//���ڻָ�
#define		VIT_STATUS_FULL		3	//�Ṧ����


#define     package             0x2 //����
#define     body                0x1 //����װ�� 0xFA6CE4
#define		CAN_OPERATOR		155	//���Բ����ľ���, ��Ϸ�ڴξ���Ϳ��԰�F�ȵ�



//�Զ�����Ϣ, ����ִ����Ϸ call
#define		WM_CUSTOM_GCALL		(WM_USER + 0x300)


#define     SHENXINGBAIBIANCHAZHI   0x1F35F18   //���аٱ��ֵ 



//��Ϣ
enum {
	id_msg_step					,
	id_msg_step3x               ,
		id_msg_guanshangdian		,
		id_msg_attack				,
		id_msg_clickui				,
		id_msg_vector_ui			,
		id_msg_HeChengWuQi_Po5		,
		id_msg_HeChengWuQi_Po10,
		id_msg_HeChengWuQi			,
		id_msg_WearEquipment		,
		id_msg_Fenjie				,
		id_msg_CunCangku			,
		id_msg_ChiYao				,
		id_msg_DeleteItem			,
		id_msg_DeliverQuests		,
		id_msg_DaKaiDuiHuaKuang		,
		id_msg_FaSonXianLuBao		,
		id_msg_PickupDeadbody		,
		id_msg_JingDianMoShi		,
		id_msg_PickdownBody			,
		id_msg_DunDi				,
		id_msg_GatBagGoodrName		,
		id_msg_GatTaskName			,
		id_msg_ZOULUSHUNYI			,
		id_msg_OpenQuestItem		,
		id_msg_Pickup				,
		id_msg_Pickup1,
		id_msg_Pickup2,
		id_msg_PickupTask			,
		id_msg_Fuhuo				,
		id_msg_NewBag				,
		id_msg_SellItem				,
		id_msg__KaiHeZi				,
		id_msg_HuanXian				,
		id_msg_TiaoYue				,
		id_msg_JieFengZhuangBei		,
		id_msg_JiaBaoShi			,
		id_msg_XieBaoShi			,
		id_msg_GouMaiWuPing			,
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
		id_msg_LinQuJiangLi
};





const wchar_t nBig50[] = L"\xd070\x0020\xbc31\xb144\xc0bc\x0020\xd68c\xbcf5\xc57d";
const wchar_t nBig45[] = L"\xbc31\xb144\xc0bc\x0020\xd68c\xbcf5\xc57d";
const wchar_t nBig36[] = L"\xc218\xc815\xb09c\xd480\x0020\xd68c\xbcf5\xc57d";
const wchar_t nBig29[] = L"\xd070\x0020\xc601\xc9c0\xbc84\xc12f\x0020\xd68c\xbcf5\xc57d";
const wchar_t nBig10[] = L"\xbcf5\xbd84\xc790\x0020\xd68c\xbcf5\xc57d";
const wchar_t nLess10[] = L"\xc57d\xc218\x0020\xd68c\xbcf5\xc57d";
const wchar_t nSpec1[] = L"\xd68c\xbcf5\xc57d";
const wchar_t nSpec2[] = L"\xd589\xc6b4\xc758\x0020\xbe44\xc57d";

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

#define JINGDIANMOSHICALL_JIEGOUTOU     0x0A7CD0A4      // ����ģʽCALL�Ľṹͷ  
#define QUDINGYAOJIANG_JIEGOUTOU		0x0A7CD0A4      // ȷ��ҡ��CALL�Ľṹͷ  
#define ShuaXinBeiBao_JIEGOUTOU			0x0A7BD0A4      // ˢ�±���CALL�Ľṹͷ  
#define GUANBICHUANGKOUCALL_JIEGOUTOU   0x0AD2D0A4      // �رմ���CALL�Ľṹͷ  


class Gamecall
{
public:
	Gamecall();
	~Gamecall();


	BOOL Init();
	void InitSpeed();
	BOOL LoginInGame(DWORD index);



	//�ȴ�
	void WaitPlans();	//�ȴ���ͼ �˺������ر�ʾ��ͼ���
	void WaitGameCreate();


	//�ж϶����ɱ������
	DWORD m_Get11C(DWORD m_Adress);   //�� ==1 ����
	DWORD m_Get110(DWORD m_Adress);	//==1 ���������ж�, ==2��npc
	DWORD m_Get2E4(DWORD m_Adress);   //==0 npc, else ����



	//��Ϸ����
	HWND GetGamehWnd(){return m_hGameWnd;}		//��ȡ��Ϸ����
	HWND isGameWndCreated(DWORD dwPid);          //�ж���Ϸ�����Ƿ񴴽�



	//����
	void SetShuyiPath(TCHAR* szPath);
	void SetIniPath(TCHAR* szPath);
	void KeyPress(WPARAM vk);
	void HookQietu( BOOL bEnable ); //hook ��ͼ
	static DWORD CalcC(fPosition &p1, fPosition &p2);      //���������������
	static fPosition ShortPosToFloatPos(sPosition &shortp);   //����ת��
	void* GetStepCallAddr();                      //ȡ��·call�ĵ�ַ
	void RandomStep(DWORD range);				//��ĳ�����������
	void JingDianMoShi(DWORD adress, DWORD adress1);  //����ģʽ
	TCHAR* GetLujingPath(){return m_szLujingPath;}
	TCHAR* GetConfigPath(){return m_szConfigPath;}
	TCHAR* GetLujingTest(){return m_szLujingTest;}



	
	BYTE ReadByte(DWORD addr);
	WORD ReadWORD(DWORD addr);
	DWORD ReadDWORD(DWORD addr);
	int ReadInt(DWORD addr);
	float ReadFloat(DWORD addr);
	char* ReadStr(DWORD addr);

	//��װ�ĵ���call, ͨ����Ϣ
	DWORD call(DWORD id, LPVOID pParam);
	DWORD sendcall(DWORD id, LPVOID pParam);

	//ǿ��
	DWORD GetMuQianJingYanZongZhi(DWORD Adress);
	DWORD GetMuQianJingYanZongZhi_A(DWORD Adress);
	void  XieBaoShi(DWORD canshu1, DWORD canshu2, DWORD canshu3);
	void  JiaBaoShi(DWORD canshu1, DWORD canshu2, DWORD canshu3, DWORD canshu4, DWORD canshu5);


	//��·
	void HuanXian(int xianlu);	//����
	DWORD GetXianluNums();		//��ȡ��·yun
	UCHAR GetPlayerXianlu();
	void DunDi(DWORD cityid);

	//���
	DWORD GetPlayerHealth();			//���Ѫ��
	UCHAR GetPlayerLevel();			//��ҵȼ�
	DWORD GetPlayerMaxHealth();		//������Ѫ��
	static DWORD GetPlayerDataAddr();		//������ݻ�ַ
	DWORD GetPlayerID();              //id
	wchar_t* GetPlayerName();            //��
	UCHAR GetPlayerMana();		    //����ֵ
	float GetPlayerMaxVit();			//�Ṧ
	float GetPlayerVit();				//��ǰ�Ṥֵ
	int	GetPlayerVitStatus();		//�Ṧ״̬
	static BOOL GetPlayerPos(fPosition* PlayerPosition);				//float����
	BOOL GetPlayerPos2(sPosition* spos);			//short������
	float GetPlayerViewPoint();		//��ɫ����
	DWORD GetPlayerQuestUIStatus();	//�жϽ�ɫ�������ui״̬�Ƿ񵯳�
	BYTE GetPlayerDeadStatus();	//����״̬
	DWORD GetCityID();
	BOOL GetPlayExperienceStatus();//��þ���ҩ״̬
	void _LinQuJiangLi();
	//����
  
	ObjectNode* GetObjectBinTreeBaseAddr();
	void GetAllObjectToVector(ObjectNode *pNode, std::vector<ObjectNode *> &RangeObject);
	DWORD GetRangeLootCount(DWORD range);
    void _GetRangeObjectToVector(ObjectNode *pNode, DWORD range, std::vector<ObjectNode *> &RangeObject);
	void GetRangeMonsterToVector(DWORD range, std::vector<ObjectNode *> &MonsterVec);
	void GetRangeObjectToVector(ObjectNode *pNode, DWORD range, std::vector<ObjectNode *> &RangeObject);
	void GetRangeLootObjectToVector(DWORD range, std::vector<ObjectNode *> &LootVec);
	DWORD GetRangeMonsterCount(DWORD range = CAN_OPERATOR);	//ȡ��Χ�ڹ�������, һ�������ж��Ƿ���aoe����
	void GetRangeTaskItemToVectr(std::vector<ObjectNode *> &TastItemVector, DWORD range);
	ObjectNode* GetObjectByName(wchar_t szName[], DWORD range = 500);
	static BYTE GetObjectType(DWORD pObjAddress);		//��������
	static BOOL _GetObjectPos(DWORD pObjAddress, fPosition* pos);		//ȡ��������
	static BOOL	GetObjectPos(ObjectNode* pNode, fPosition* fpos);
	static BOOL GetObjectPos_0xb(DWORD pObjAddress, sPosition* spos);      //����short��������
	static BOOL GetObjectPos2_0x20(DWORD pObjAddress, fPosition* fpos);//0x20����ʹ�����ȡ����
	wchar_t* GetObjectNameByIndex(DWORD index);                   //������
	wchar_t* GetObjectName(DWORD pObjAddress);
	DWORD GetType4HP(DWORD pObjAddress);  		//��ȡ����Ϊ4�Ķ���Ѫ��
	DWORD GetObject_0x14(DWORD pObjAddress);
	DWORD GetObjectLevel(DWORD pObjAddress);		//ȡ����ȼ�
	DWORD GetObjectSY12(DWORD pObjAddress);
	DWORD GetObjectSY(DWORD pObjAddress);
	DWORD GetIndexByType(DWORD pObjAddress); //ͨ������ȡ������



	//�ж�
	BOOL isConfirmDeleteTalnetPanelShow();
	BOOL isTalentPanelShow();
	BOOL isStrikeCd(DWORD id);	//�жϼ���cd
	BOOL isPlayerDaodi();	//����״̬
	BOOL isLoots(DWORD pAddr);
	BOOL isLoading(); //�жϽ�ɫ�Ƿ��ڴ�������Ʒ�Ķ���״̬
	BOOL isSelectedSlotHavePlayer(DWORD index);	//��ɫѡ����浱ǰ��ѡ����һ����ɫ����
	BOOL isQuestItem(DWORD pAddr); //�ж��Ƿ���������Ʒ
	BOOL isPlayerHasPickupQuestItemUI(); //�и�ʰȡUi������
	BOOL isPlayerChanneling();	//���ڶ���
	BOOL isPlayerSteping();		//���������·
	BOOL isLoginInSelectPlayer();	//�ж��Ƿ�����˽�ɫѡ����
	int	isLoadingMap();		//��ͼ״̬
	BOOL isHaveXianlu(int index);
	BOOL isCityConveyLoadingMap();
	BOOL isCityConveying();
	BOOL isPickupDeadBody();
	BOOL isDeadBody(DWORD pAddr);
	BOOL isCanFenjie(DWORD pAddr); //���Էֽ�
	BOOL isFuhuoing();
	DWORD isYaoPingCD(_BAGSTU &goods); //ҩƿcd
	DWORD isStrikeLocked(int index, DWORD pAddr);
	DWORD isStrikeCanUse(int index, DWORD pAddr);
	BOOL isBagFull();
	BOOL isCanKill(ObjectNode* pNode);
	BOOL isCanLook(DWORD pAddr);	//���Կ�����


	//����
    void        _GetAcceptedQuestToVector(std::vector<Quest> &QuestVec);
	void		GetAcceptedQuestToVector(std::vector<Quest> &QuestVec);
	void        DeliverQuests(DWORD id, DWORD step, DWORD questtype, DWORD ff, DWORD npcid1, DWORD npcid2, DWORD unknow, DWORD mianban);     //������
	DWORD		GetTaskStartAddr();  //��ȡ����ʼ��ַ
	DWORD		GetTaskID(int i, DWORD pAddr);  //��õ�ǰ����ID
	wchar_t*	GatTaskName(DWORD ID); //��ȡ��ǰ�ѽ���������
	DWORD		GetTaskNameID(int i, DWORD pAddr);  //��õ�ǰ��������ID
	DWORD		GetTaskPresentAddr(int i, DWORD pAddr);  //��õ�ǰ�����ַ
	DWORD		GetPresentTaskIndexes(int i, DWORD pAddr);  //��õ�ǰ�����ڼ���С����
	DWORD		GetPresentTaskEndFlag(int i, DWORD pAddr ,DWORD info);  //��õ�ǰС���������־
	DWORD		GetPresentTaskNum(int i, DWORD pAddr ,DWORD info );  //��õ�ǰС�����Ѿ���Ĺ�����
	void        OpenQuestItem(DWORD ID,DWORD ID2);    //��������Ʒ
	DWORD		GetTaskStepById(DWORD id);



	//ui �ͼ���
	BOOL        CloseAttendance();		//�رտ�ʼ��ҡ��
	void		SetMouseMode();			//������: ���ģʽ
	BOOL		ConfirmAgreement();		//ȷ�ϵ�¼��Ϸʱ��ʾ��Э��
	void		FaSonXianLuBao(DWORD adress1);
	void		OpenXianluUI();
	void		LoginGame(int index);	//������Ϸ
	PCHARACTER  GetCharacter(int index);    //��ɫѡ�� ui

	BOOL		ClickUI(UIOperator uiOp);   //���ui
	Tree*		GetUIBinTreeBaseAddr();
	wchar_t*	GetUIName(DWORD pBarAddr);
	wchar_t*GetUiNewName(DWORD pBarAddr);
    void        _GetUItoVector(Tree *Base, std::vector<Tree *> &Allui);
	void		GetUItoVector(Tree* pBaseAddr, std::vector<Tree *> &Allui);
	void		GetUIAddrByName(wchar_t* name, DWORD *pUIAddr);
	void    GetUiAddrByName(KONGJIAN_JIEGOU &jiegou);
	void    _GetUiAddrByName(Tree* Addr,wchar_t* name,DWORD &reAddr);
	void		GetStrikeToVector(std::vector<STRIKEINFO> &RangeObject);
	void		GetStrikeBarBaseAddr(Tree *pBaseAddr, DWORD *pStrikeBarBaseAddr);
	void		GetStrikeName(DWORD ID,DWORD IDD, STRIKENAME *pName);
	DWORD		GetStrikeStartAddr();                               //��ȡ���ܿ�ʼ��ַ
	DWORD		GetStrike_R_id(int index, DWORD p_R_addr);
	DWORD		GetStrike_R_addr(DWORD pStrikeStartAddr);
	DWORD		GetStrikeId1(int index, DWORD pStrikeStartAddr);  //ȡ����ID
	DWORD		GetStrikeId2(int index, DWORD pStrikeStartAddr);  //ȡ����ID
	DWORD		GetStrikeCD(int index, DWORD pAddr);
	BOOL		GetStrikeByName(const wchar_t *name, STRIKEINFO* pStrikeInfo);
	DWORD		GetRJianSkill(DWORD m_adress);  //ȡ����R�����������鿪ʼ��ַ
	DWORD		GetRJSkillIDDD(int i, DWORD m_adress);  //ȡR�����鼼��ID
	DWORD		GetRJSkillIDDD2(int i, DWORD m_adress);  //ȡR����������ID2
	DWORD		GetRJSkillIsJieSuo(int i, DWORD m_adress);  //ȡR�������Ƿ��Ѿ�����
	DWORD		GetRJSkillISShiYong(int i, DWORD m_adress);  //ȡR�������Ƿ����ʹ��
	DWORD		GetRJSkillCD(int i, DWORD m_adress);  //ȡR�������Ƿ���ȴ
	void Fuhuo(DWORD uiAddr);
	void DaKaiJiNengMianBan(DWORD adress,DWORD adress1); //�򿪼������


	//�ӵ�
	void JiaJiNengDian(DWORD ID); //�Ӽ��ܵ�
	void QuChuJiNengDian(DWORD ID); //ȥ�����ܵ�
	void QueRenJiNengDian(); //ȷ�ϼ��ܵ�
	void OpenDeleteTalentPanel();
	void DaKaiQingChuQuanBuJiNengJieMian(DWORD adress,DWORD adress1);
	void ConfirmDeletePalentPanelShowOk();
	void QueRenQingChuQuanBuJiNengJieMian(DWORD adress,DWORD adress1);
	void OpenTalentUI();


	//��Ʒ
	void		DaKaiDuiHuaKuang(DWORD ID, DWORD ID2);
	void		GuanBiDuiHuaKuangChuanKou(DWORD adress, DWORD adress1);
	void		GouMaiWuPing(DWORD Num, DWORD Ind, DWORD Adress);
	void        CunCangku(_BAGSTU &goods);              //�Ųֿ�
	void		SellItem(_BAGSTU &bag, DWORD adress);
	BOOL		OpenShangDian(wchar_t* name, DWORD* pUiAddr); //����Ʒ�Ի���
	void		CloseShangDian();
	void		DeleteItem(_BAGSTU &bag);	//�ݻ�һ����Ʒ

	//����
    void _GetAllGoodsToVector(std::vector<_BAGSTU> &RangeObject);
	void GetAllGoodsToVector(std::vector<_BAGSTU> &RangeObject);                // ��������
	void GetAllBodyEquipToVector(std::vector<_BAGSTU> &RangeObject);	
    void _GetAllBodyEquipToVector(std::vector<_BAGSTU> &RangeObject);
 
	BOOL		GetAllBaGuaToVector(std::vector<_BAGSTU> &BaGuaVec);
	BOOL		GetSpecBaGuaToVector(wchar_t* name, std::vector<_BAGSTU> &BaGuaVec);
	DWORD		GetBagbodyInfoBase();               //��ȡ��������װ���ֿ����Base
	DWORD		GetBagInfoBase(DWORD pAddr);    //��ȡ��������Base
	DWORD		GetBodyInfoBase(DWORD pBase);
	DWORD		GetBagGridNumber();     //��ǰ�������ܵĸ�����
	DWORD		GetBagGridNumberLast();
	DWORD		GetGoodsBase(DWORD pAddr,int index);    //��ȡ��Ʒ���׵�ַ
	DWORD		GetGoodsID(DWORD pAddr);                //��ȡ��Ʒ��ID
	DWORD		GetGoodsNameID(DWORD pAddr);            //��ȡ��Ʒ������ID
	wchar_t*	GatBagGoodrName(DWORD ID);       //��ȡ������Ʒ����
	DWORD		GetGoodsBagInfo(DWORD m_Adress);
	DWORD		GetGoodsType(DWORD pAddr);          //��ȡ��Ʒ������
	DWORD		GetGoodsInfo(DWORD pAddr);          //��ȡ��Ʒ�����ڸ�����
	DWORD		GetGoodsNum(DWORD pAddr);           //��ȡ��Ʒ������
	DWORD		GetGoodsLasting(DWORD pAddr);       //��ȡ��Ʒ�ĳ־�
	DWORD		GetGoodsLLV(DWORD pAddr);            //��ȡ��Ʒ�ĵȼ�
	DWORD		GetCanshu_a(DWORD pAddr);       //��ҩ�ʹ�װ����Ҫ��һ������
	DWORD		Getcanshu4(DWORD pAddr);        //����4
	DWORD		Getcanshu3(DWORD pAddr);        //����3
	DWORD		Getcanshu2(DWORD pAddr);        //����2
	DWORD		Getcanshu1(DWORD pAddr);        //����1

	BOOL		GetGoodsFromBagByName(const wchar_t *name, _BAGSTU *goods);      //��������ȡ��Ʒ��Ϣ
	BOOL		GetGoodsFromBagByName(const wchar_t *name, std::vector<_BAGSTU> &GoodsVec);
	BOOL		GetGoodsFromEquipByName(wchar_t *name, _BAGSTU *goods);
	BOOL		GetGoodsByEquipPos(DWORD pos, _BAGSTU* goods);		//����λ��ȡ����Ʒ��Ϣ

	BOOL		FillGoods(_BAGSTU &goods);
	int			GetGoodsYanSe(DWORD m_Adress);  //��ȡ��Ʒ����ɫ
	DWORD		GetGoodsIsFengYin(DWORD m_Adress);  //��ȡ��Ʒ�Ƿ��ӡ
	DWORD		GetBagYouJianCaoZuoType(DWORD Adress,DWORD AAA); // ��ȡ������Ʒ�Ҽ��������� 
	DWORD		GetGoodsYouJianType(DWORD m_BagLeiXing,DWORD m_Info);  //��ȡ������Ʒ�Ҽ���������
	DWORD		GetGoodsWuQiPingJi(DWORD m_Adress);  //��ȡ����������
	DWORD		GetGoodsWuQiDangQianJingYan(DWORD m_Adress);  //��ȡ������ǰ�ľ���
	DWORD		GetGoodsBiDui(DWORD m_Adress);  //��ȡ��Ʒ�ıȶ�
	DWORD		GetGoodsBiDui_A(DWORD m_Adress);  //��ȡ��Ʒ�ıȶ�A
	DWORD		GetBaGuaGeZiShu(DWORD m_Adress);  //��ȡ���Ը�����
	BOOL		GetGoodsByName_Hezi(wchar_t *name, std::vector<_BAGSTU> &GoodsVec); //����ö�ٺ���
	void		KaiHeZi(_BAGSTU &bag);
	BOOL		SortBag();
	BOOL		NewBag();


	//����ǿ��
	void		HeChengWuQi(_BAGSTU &zhu, _BAGSTU &fu);
	void        HeChengWuQi_Po5(_BAGSTU &zhu, _BAGSTU &fu); //�ϳ�������5
	void		HeChengWuQi_Po10(DWORD zhu,DWORD fu,DWORD adress);
	void		JieFengZhuangBei(DWORD zhuangbei,DWORD jiefengfu_ID,DWORD num);
	void		JieFengZhuangBei(DWORD adress1,DWORD adress2,DWORD adress3,DWORD adress4,DWORD adress5,DWORD adress6,DWORD adress7); //������
	void		FenJie(_BAGSTU &bag);






	//��װ��
	void        WearEquipment(_BAGSTU &bag);


	//����
	void        Pickup1(ObjectNode *pObj);    //��һ�μ�
	void        Pickup2(ObjectNode *pObj);   //�ڶ��μ�����
	BOOL		Pickup(ObjectNode *pObj);     //����
	void        _PickupTask(ObjectNode* pObj);  //
	BOOL		PickupTask(ObjectNode* pNode);
	void		PickupDeadbody(DWORD id1, DWORD id2);
	BOOL		PickupDeadbody(DWORD range = 500);  //����ʬ��, ���߼���, �Զ�������Χ��
	void		PickdownBody(); //�������һ���������ʬ���ַ������������


	//ɱ��
	int			KillObject(DWORD range, ObjectNode *pNode, DWORD mode, DWORD canKillRange = CAN_OPERATOR); //ɱ���������

	//��·
	BOOL Stepto(fPosition &tarpos, double timeOut = 10, DWORD okRange = CAN_OPERATOR, DWORD tooLong = 1000,BOOL sp3x = FALSE);
	void Step(float x, float y, float z);
	void Step3x(float x, float y, float z);
	BOOL Step(ObjectNode* pNode);
	void Stepto3x();
	void ZOULUSHUNYI(DWORD *adress,DWORD adrewss);
	void OverShunyi(BOOL bEnable); //��ͼ
	void _NewSpend(float x);

	void TiaoYue();
	//����
	int GetHealth(DWORD theValue);
	void ChiYao(_BAGSTU &goods);
	void ChiYao(const wchar_t *name);		//��ҩ, ҩ��
	void Attack(int id);
	void Attack(const wchar_t *name);
	void AttackNormal();	//��ͨ���� , rt ѭ����, ��Ҫ������ʹ�ӽ����������������
	void AttackAOE();						//AOE����


	//ת��
	void Turn(int angle);
	void TurnTo(fPosition &pos);
	void TurnTo(float x, float y, float z);		//�ӽ�


	//����, �����ļ������ȼ�����
	static BOOL UDgreater(ObjectNode *elem1, ObjectNode *elem2);
	BOOL Kill_ApplyConfig(std::vector<ObjectNode *> &ObjectVec);
	

public:
	Logger log;
	HWND m_hGameWnd;
	HANDLE m_hModuleBsEngine;
	HMODULE	m_hack;	//����ģ����


    //�����ļ�
	TCHAR m_szLujingPath[MAX_PATH];
    TCHAR m_szConfigPath[MAX_PATH];
	TCHAR m_szLujingTest[MAX_PATH];

	CCHook ce_hookGetTickCount;
	CCHook ce_hookQueryPerformanceCounter;
	CCHook ce_hooktimeGetTime;
	CCHook hookQietu; 

	ShareMem g_share;
	SHAREINFO* m_pShareMem;
	typedef int ( *_InitializeSpeedhack)(float);
  
	_InitializeSpeedhack m_pfnInitSpeed;
};



