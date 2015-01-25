#pragma once


#include "gamedata.h"
#include "gamestruct.h"

#include "..\common\logger.h"		
#include "..\common\common.h"
#include "..\common\CCHook.h"
#include "..\common\sharemem.h"

//方便根据字符集设置输出相应的调试信息

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

//杀怪模式, 默认只Normal
//可以应用多个杀怪模式, 比如 modeNormal | modeSpend | modeTask | modeAoe
#define			modeNormal						1	//用普通技能, 不会用范围攻击
#define			modeAoe							4	//AOE
#define			modeTask						8	//任务, 影响退出逻辑的判断
#define			modeGoback						16	//杀完回原点
#define			modePickup						32	//杀完自己捡
#define			modePickupBody					64	//杀完举起尸体	
#define			modePickupOnce					128 //干掉一个捡一次掉落


/*状态常量*/
#define		NORTH				0		//正北
#define		SOUTH				32778   //南
#define		WEST				49167   //西
#define		EAST				16389	//东

#define		VIT_STATUS_USED		1   //使用了轻功
#define		VIT_STATUS_RENEW	2	//正在恢复
#define		VIT_STATUS_FULL		3	//轻功已满


#define     package             0x2 //背包
#define     body                0x1 //身上装备 0xFA6CE4
#define		CAN_OPERATOR		155	//可以操作的距离, 游戏内次距离就可以按F等等



//自定的消息, 用来执行游戏 call
#define		WM_CUSTOM_GCALL		(WM_USER + 0x300)


#define     SHENXINGBAIBIANCHAZHI   0x1F35F18   //神行百变差值 



//消息
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

#define JINGDIANMOSHICALL_JIEGOUTOU     0x0A7CD0A4      // 经典模式CALL的结构头  
#define QUDINGYAOJIANG_JIEGOUTOU		0x0A7CD0A4      // 确定摇奖CALL的结构头  
#define ShuaXinBeiBao_JIEGOUTOU			0x0A7BD0A4      // 刷新背包CALL的结构头  
#define GUANBICHUANGKOUCALL_JIEGOUTOU   0x0AD2D0A4      // 关闭窗口CALL的结构头  


class Gamecall
{
public:
	Gamecall();
	~Gamecall();


	BOOL Init();
	void InitSpeed();
	BOOL LoginInGame(DWORD index);



	//等待
	void WaitPlans();	//等待过图 此函数返回表示过图完成
	void WaitGameCreate();


	//判断对象可杀的数据
	DWORD m_Get11C(DWORD m_Adress);   //是 ==1 红名
	DWORD m_Get110(DWORD m_Adress);	//==1 进行下面判断, ==2是npc
	DWORD m_Get2E4(DWORD m_Adress);   //==0 npc, else 黄名



	//游戏窗口
	HWND GetGamehWnd(){return m_hGameWnd;}		//获取游戏窗口
	HWND isGameWndCreated(DWORD dwPid);          //判断游戏窗口是否创建



	//工具
	void SetShuyiPath(TCHAR* szPath);
	void SetIniPath(TCHAR* szPath);
	void KeyPress(WPARAM vk);
	void HookQietu( BOOL bEnable ); //hook 切图
	static DWORD CalcC(fPosition &p1, fPosition &p2);      //计算两个坐标距离
	static fPosition ShortPosToFloatPos(sPosition &shortp);   //坐标转换
	void* GetStepCallAddr();                      //取走路call的地址
	void RandomStep(DWORD range);				//向某个方向随机走
	void JingDianMoShi(DWORD adress, DWORD adress1);  //经典模式
	TCHAR* GetLujingPath(){return m_szLujingPath;}
	TCHAR* GetConfigPath(){return m_szConfigPath;}
	TCHAR* GetLujingTest(){return m_szLujingTest;}



	
	BYTE ReadByte(DWORD addr);
	WORD ReadWORD(DWORD addr);
	DWORD ReadDWORD(DWORD addr);
	int ReadInt(DWORD addr);
	float ReadFloat(DWORD addr);
	char* ReadStr(DWORD addr);

	//封装的调用call, 通过消息
	DWORD call(DWORD id, LPVOID pParam);
	DWORD sendcall(DWORD id, LPVOID pParam);

	//强化
	DWORD GetMuQianJingYanZongZhi(DWORD Adress);
	DWORD GetMuQianJingYanZongZhi_A(DWORD Adress);
	void  XieBaoShi(DWORD canshu1, DWORD canshu2, DWORD canshu3);
	void  JiaBaoShi(DWORD canshu1, DWORD canshu2, DWORD canshu3, DWORD canshu4, DWORD canshu5);


	//线路
	void HuanXian(int xianlu);	//换线
	DWORD GetXianluNums();		//获取线路yun
	UCHAR GetPlayerXianlu();
	void DunDi(DWORD cityid);

	//玩家
	DWORD GetPlayerHealth();			//玩家血量
	UCHAR GetPlayerLevel();			//玩家等级
	DWORD GetPlayerMaxHealth();		//玩家最大血量
	static DWORD GetPlayerDataAddr();		//玩家数据基址
	DWORD GetPlayerID();              //id
	wchar_t* GetPlayerName();            //名
	UCHAR GetPlayerMana();		    //法力值
	float GetPlayerMaxVit();			//轻功
	float GetPlayerVit();				//当前轻工值
	int	GetPlayerVitStatus();		//轻功状态
	static BOOL GetPlayerPos(fPosition* PlayerPosition);				//float坐标
	BOOL GetPlayerPos2(sPosition* spos);			//short型坐标
	float GetPlayerViewPoint();		//角色面向
	DWORD GetPlayerQuestUIStatus();	//判断角色任务相关ui状态是否弹出
	BYTE GetPlayerDeadStatus();	//死亡状态
	DWORD GetCityID();
	BOOL GetPlayExperienceStatus();//获得经验药状态
	void _LinQuJiangLi();
	//对象
  
	ObjectNode* GetObjectBinTreeBaseAddr();
	void GetAllObjectToVector(ObjectNode *pNode, std::vector<ObjectNode *> &RangeObject);
	DWORD GetRangeLootCount(DWORD range);
    void _GetRangeObjectToVector(ObjectNode *pNode, DWORD range, std::vector<ObjectNode *> &RangeObject);
	void GetRangeMonsterToVector(DWORD range, std::vector<ObjectNode *> &MonsterVec);
	void GetRangeObjectToVector(ObjectNode *pNode, DWORD range, std::vector<ObjectNode *> &RangeObject);
	void GetRangeLootObjectToVector(DWORD range, std::vector<ObjectNode *> &LootVec);
	DWORD GetRangeMonsterCount(DWORD range = CAN_OPERATOR);	//取范围内怪物数量, 一般用来判断是否用aoe攻击
	void GetRangeTaskItemToVectr(std::vector<ObjectNode *> &TastItemVector, DWORD range);
	ObjectNode* GetObjectByName(wchar_t szName[], DWORD range = 500);
	static BYTE GetObjectType(DWORD pObjAddress);		//对象类型
	static BOOL _GetObjectPos(DWORD pObjAddress, fPosition* pos);		//取对象坐标
	static BOOL	GetObjectPos(ObjectNode* pNode, fPosition* fpos);
	static BOOL GetObjectPos_0xb(DWORD pObjAddress, sPosition* spos);      //对象short类型坐标
	static BOOL GetObjectPos2_0x20(DWORD pObjAddress, fPosition* fpos);//0x20对象使用这个取坐标
	wchar_t* GetObjectNameByIndex(DWORD index);                   //对象名
	wchar_t* GetObjectName(DWORD pObjAddress);
	DWORD GetType4HP(DWORD pObjAddress);  		//获取类型为4的对象血量
	DWORD GetObject_0x14(DWORD pObjAddress);
	DWORD GetObjectLevel(DWORD pObjAddress);		//取对象等级
	DWORD GetObjectSY12(DWORD pObjAddress);
	DWORD GetObjectSY(DWORD pObjAddress);
	DWORD GetIndexByType(DWORD pObjAddress); //通过类型取得索引



	//判断
	BOOL isConfirmDeleteTalnetPanelShow();
	BOOL isTalentPanelShow();
	BOOL isStrikeCd(DWORD id);	//判断技能cd
	BOOL isPlayerDaodi();	//倒地状态
	BOOL isLoots(DWORD pAddr);
	BOOL isLoading(); //判断角色是否在打开任务物品的读条状态
	BOOL isSelectedSlotHavePlayer(DWORD index);	//角色选择界面当前的选择有一个角色存在
	BOOL isQuestItem(DWORD pAddr); //判断是否是任务物品
	BOOL isPlayerHasPickupQuestItemUI(); //有个拾取Ui弹出来
	BOOL isPlayerChanneling();	//正在读条
	BOOL isPlayerSteping();		//玩家正在走路
	BOOL isLoginInSelectPlayer();	//判断是否进入了角色选择画面
	int	isLoadingMap();		//过图状态
	BOOL isHaveXianlu(int index);
	BOOL isCityConveyLoadingMap();
	BOOL isCityConveying();
	BOOL isPickupDeadBody();
	BOOL isDeadBody(DWORD pAddr);
	BOOL isCanFenjie(DWORD pAddr); //可以分解
	BOOL isFuhuoing();
	DWORD isYaoPingCD(_BAGSTU &goods); //药瓶cd
	DWORD isStrikeLocked(int index, DWORD pAddr);
	DWORD isStrikeCanUse(int index, DWORD pAddr);
	BOOL isBagFull();
	BOOL isCanKill(ObjectNode* pNode);
	BOOL isCanLook(DWORD pAddr);	//可以看到的


	//任务
    void        _GetAcceptedQuestToVector(std::vector<Quest> &QuestVec);
	void		GetAcceptedQuestToVector(std::vector<Quest> &QuestVec);
	void        DeliverQuests(DWORD id, DWORD step, DWORD questtype, DWORD ff, DWORD npcid1, DWORD npcid2, DWORD unknow, DWORD mianban);     //交任务
	DWORD		GetTaskStartAddr();  //获取任务开始地址
	DWORD		GetTaskID(int i, DWORD pAddr);  //获得当前任务ID
	wchar_t*	GatTaskName(DWORD ID); //获取当前已接任务名字
	DWORD		GetTaskNameID(int i, DWORD pAddr);  //获得当前任务名字ID
	DWORD		GetTaskPresentAddr(int i, DWORD pAddr);  //获得当前任务地址
	DWORD		GetPresentTaskIndexes(int i, DWORD pAddr);  //获得当前做到第几个小任务
	DWORD		GetPresentTaskEndFlag(int i, DWORD pAddr ,DWORD info);  //获得当前小任务结束标志
	DWORD		GetPresentTaskNum(int i, DWORD pAddr ,DWORD info );  //获得当前小任务已经打的怪数量
	void        OpenQuestItem(DWORD ID,DWORD ID2);    //打开任务物品
	DWORD		GetTaskStepById(DWORD id);



	//ui 和技能
	BOOL        CloseAttendance();		//关闭开始的摇奖
	void		SetMouseMode();			//鼠标操作: 点击模式
	BOOL		ConfirmAgreement();		//确认登录游戏时显示的协议
	void		FaSonXianLuBao(DWORD adress1);
	void		OpenXianluUI();
	void		LoginGame(int index);	//进入游戏
	PCHARACTER  GetCharacter(int index);    //角色选择 ui

	BOOL		ClickUI(UIOperator uiOp);   //点击ui
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
	DWORD		GetStrikeStartAddr();                               //获取技能开始地址
	DWORD		GetStrike_R_id(int index, DWORD p_R_addr);
	DWORD		GetStrike_R_addr(DWORD pStrikeStartAddr);
	DWORD		GetStrikeId1(int index, DWORD pStrikeStartAddr);  //取技能ID
	DWORD		GetStrikeId2(int index, DWORD pStrikeStartAddr);  //取技能ID
	DWORD		GetStrikeCD(int index, DWORD pAddr);
	BOOL		GetStrikeByName(const wchar_t *name, STRIKEINFO* pStrikeInfo);
	DWORD		GetRJianSkill(DWORD m_adress);  //取技能R键攻击的数组开始地址
	DWORD		GetRJSkillIDDD(int i, DWORD m_adress);  //取R键数组技能ID
	DWORD		GetRJSkillIDDD2(int i, DWORD m_adress);  //取R键技能数组ID2
	DWORD		GetRJSkillIsJieSuo(int i, DWORD m_adress);  //取R键技能是否已经解锁
	DWORD		GetRJSkillISShiYong(int i, DWORD m_adress);  //取R键技能是否可以使用
	DWORD		GetRJSkillCD(int i, DWORD m_adress);  //取R键技能是否冷却
	void Fuhuo(DWORD uiAddr);
	void DaKaiJiNengMianBan(DWORD adress,DWORD adress1); //打开技能面板


	//加点
	void JiaJiNengDian(DWORD ID); //加技能点
	void QuChuJiNengDian(DWORD ID); //去除技能点
	void QueRenJiNengDian(); //确认技能点
	void OpenDeleteTalentPanel();
	void DaKaiQingChuQuanBuJiNengJieMian(DWORD adress,DWORD adress1);
	void ConfirmDeletePalentPanelShowOk();
	void QueRenQingChuQuanBuJiNengJieMian(DWORD adress,DWORD adress1);
	void OpenTalentUI();


	//商品
	void		DaKaiDuiHuaKuang(DWORD ID, DWORD ID2);
	void		GuanBiDuiHuaKuangChuanKou(DWORD adress, DWORD adress1);
	void		GouMaiWuPing(DWORD Num, DWORD Ind, DWORD Adress);
	void        CunCangku(_BAGSTU &goods);              //放仓库
	void		SellItem(_BAGSTU &bag, DWORD adress);
	BOOL		OpenShangDian(wchar_t* name, DWORD* pUiAddr); //打开商品对话框
	void		CloseShangDian();
	void		DeleteItem(_BAGSTU &bag);	//摧毁一个物品

	//背包
    void _GetAllGoodsToVector(std::vector<_BAGSTU> &RangeObject);
	void GetAllGoodsToVector(std::vector<_BAGSTU> &RangeObject);                // 遍历背包
	void GetAllBodyEquipToVector(std::vector<_BAGSTU> &RangeObject);	
    void _GetAllBodyEquipToVector(std::vector<_BAGSTU> &RangeObject);
 
	BOOL		GetAllBaGuaToVector(std::vector<_BAGSTU> &BaGuaVec);
	BOOL		GetSpecBaGuaToVector(wchar_t* name, std::vector<_BAGSTU> &BaGuaVec);
	DWORD		GetBagbodyInfoBase();               //获取背包身上装备仓库遍历Base
	DWORD		GetBagInfoBase(DWORD pAddr);    //获取背包遍历Base
	DWORD		GetBodyInfoBase(DWORD pBase);
	DWORD		GetBagGridNumber();     //当前背包的总的格子数
	DWORD		GetBagGridNumberLast();
	DWORD		GetGoodsBase(DWORD pAddr,int index);    //获取物品的首地址
	DWORD		GetGoodsID(DWORD pAddr);                //获取物品的ID
	DWORD		GetGoodsNameID(DWORD pAddr);            //获取物品的名字ID
	wchar_t*	GatBagGoodrName(DWORD ID);       //获取背包物品名字
	DWORD		GetGoodsBagInfo(DWORD m_Adress);
	DWORD		GetGoodsType(DWORD pAddr);          //获取物品的类型
	DWORD		GetGoodsInfo(DWORD pAddr);          //获取物品的所在格子数
	DWORD		GetGoodsNum(DWORD pAddr);           //获取物品的数量
	DWORD		GetGoodsLasting(DWORD pAddr);       //获取物品的持久
	DWORD		GetGoodsLLV(DWORD pAddr);            //获取物品的等级
	DWORD		GetCanshu_a(DWORD pAddr);       //吃药和穿装备需要的一个参数
	DWORD		Getcanshu4(DWORD pAddr);        //参数4
	DWORD		Getcanshu3(DWORD pAddr);        //参数3
	DWORD		Getcanshu2(DWORD pAddr);        //参数2
	DWORD		Getcanshu1(DWORD pAddr);        //参数1

	BOOL		GetGoodsFromBagByName(const wchar_t *name, _BAGSTU *goods);      //根据名字取物品信息
	BOOL		GetGoodsFromBagByName(const wchar_t *name, std::vector<_BAGSTU> &GoodsVec);
	BOOL		GetGoodsFromEquipByName(wchar_t *name, _BAGSTU *goods);
	BOOL		GetGoodsByEquipPos(DWORD pos, _BAGSTU* goods);		//根据位置取得物品信息

	BOOL		FillGoods(_BAGSTU &goods);
	int			GetGoodsYanSe(DWORD m_Adress);  //获取物品的颜色
	DWORD		GetGoodsIsFengYin(DWORD m_Adress);  //获取物品是否封印
	DWORD		GetBagYouJianCaoZuoType(DWORD Adress,DWORD AAA); // 获取背包物品右键操作类型 
	DWORD		GetGoodsYouJianType(DWORD m_BagLeiXing,DWORD m_Info);  //获取背包物品右键操作类型
	DWORD		GetGoodsWuQiPingJi(DWORD m_Adress);  //获取武器的评级
	DWORD		GetGoodsWuQiDangQianJingYan(DWORD m_Adress);  //获取武器当前的经验
	DWORD		GetGoodsBiDui(DWORD m_Adress);  //获取物品的比对
	DWORD		GetGoodsBiDui_A(DWORD m_Adress);  //获取物品的比对A
	DWORD		GetBaGuaGeZiShu(DWORD m_Adress);  //获取八卦格子数
	BOOL		GetGoodsByName_Hezi(wchar_t *name, std::vector<_BAGSTU> &GoodsVec); //用来枚举盒子
	void		KaiHeZi(_BAGSTU &bag);
	BOOL		SortBag();
	BOOL		NewBag();


	//武器强化
	void		HeChengWuQi(_BAGSTU &zhu, _BAGSTU &fu);
	void        HeChengWuQi_Po5(_BAGSTU &zhu, _BAGSTU &fu); //合成武器破5
	void		HeChengWuQi_Po10(DWORD zhu,DWORD fu,DWORD adress);
	void		JieFengZhuangBei(DWORD zhuangbei,DWORD jiefengfu_ID,DWORD num);
	void		JieFengZhuangBei(DWORD adress1,DWORD adress2,DWORD adress3,DWORD adress4,DWORD adress5,DWORD adress6,DWORD adress7); //解封盒子
	void		FenJie(_BAGSTU &bag);






	//穿装备
	void        WearEquipment(_BAGSTU &bag);


	//捡东西
	void        Pickup1(ObjectNode *pObj);    //第一次捡
	void        Pickup2(ObjectNode *pObj);   //第二次捡起来
	BOOL		Pickup(ObjectNode *pObj);     //捡东西
	void        _PickupTask(ObjectNode* pObj);  //
	BOOL		PickupTask(ObjectNode* pNode);
	void		PickupDeadbody(DWORD id1, DWORD id2);
	BOOL		PickupDeadbody(DWORD range = 500);  //捡起尸体, 有逻辑的, 自动遍历范围内
	void		PickdownBody(); //这个用来一个任务捡起尸体又放下来完成任务


	//杀怪
	int			KillObject(DWORD range, ObjectNode *pNode, DWORD mode, DWORD canKillRange = CAN_OPERATOR); //杀死这个对象

	//走路
	BOOL Stepto(fPosition &tarpos, double timeOut = 10, DWORD okRange = CAN_OPERATOR, DWORD tooLong = 1000,BOOL sp3x = FALSE);
	void Step(float x, float y, float z);
	void Step3x(float x, float y, float z);
	BOOL Step(ObjectNode* pNode);
	void Stepto3x();
	void ZOULUSHUNYI(DWORD *adress,DWORD adrewss);
	void OverShunyi(BOOL bEnable); //过图
	void _NewSpend(float x);

	void TiaoYue();
	//攻击
	int GetHealth(DWORD theValue);
	void ChiYao(_BAGSTU &goods);
	void ChiYao(const wchar_t *name);		//吃药, 药名
	void Attack(int id);
	void Attack(const wchar_t *name);
	void AttackNormal();	//普通攻击 , rt 循环按, 需要参数来使视角总是面向这个对象
	void AttackAOE();						//AOE攻击


	//转向
	void Turn(int angle);
	void TurnTo(fPosition &pos);
	void TurnTo(float x, float y, float z);		//视角


	//排序, 配置文件的优先级过滤
	static BOOL UDgreater(ObjectNode *elem1, ObjectNode *elem2);
	BOOL Kill_ApplyConfig(std::vector<ObjectNode *> &ObjectVec);
	

public:
	Logger log;
	HWND m_hGameWnd;
	HANDLE m_hModuleBsEngine;
	HMODULE	m_hack;	//加速模块句柄


    //配置文件
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



