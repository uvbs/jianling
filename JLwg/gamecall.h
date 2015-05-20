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


    //等待
    bool WaitPlans(int inMaxTime = 30);   //等待过图 此函数返回表示过图完成
    BOOL LoginInGame(DWORD index);

    //判断对象可杀的数据
    DWORD m_Get11C(DWORD m_Adress);   //是 ==1 红名
    DWORD m_Get110(DWORD m_Adress); //==1 进行下面判断, ==2是npc
    DWORD m_Get2E4(DWORD m_Adress);   //==0 npc, else 黄名


    //工具
    void HookQietu(BOOL bEnable);   //hook 切图
    void KeyPress(WPARAM vk);
    DWORD CalcC(fPosition& p1, fPosition& p2);      //计算两个坐标距离
    void ShortPosToFloatPos(sPosition& spos, fPosition& fpos);   //坐标转换
    void RandomStep(DWORD range);               //向某个方向随机走
    void JingDianMoShi(DWORD adress, DWORD adress1);  //经典模式
    void CloseXiaoDongHua();



    void ChangeZ_Status(BOOL flag);//改状态
    void ChangeHeight(float how);


    //封装的调用call, 通过消息
    DWORD call(DWORD id, LPVOID pParam);
    DWORD sendcall(DWORD id, LPVOID pParam);

    //强化
    DWORD GetMuQianJingYanZongZhi(DWORD Adress);
    DWORD GetMuQianJingYanZongZhi_A(DWORD Adress);
    void  XieBaoShi(DWORD canshu1, DWORD canshu2, DWORD canshu3);
    void  JiaBaoShi(DWORD canshu1, DWORD canshu2, DWORD canshu3, DWORD canshu4, DWORD canshu5);


    //线路
    void HuanXian(int xianlu);  //换线
    DWORD GetXianluNums();      //获取线路yun
    UCHAR GetPlayerXianlu();
    void DunDi(DWORD cityid);

    //玩家
    DWORD GetPlayerHealth();            //玩家血量
    UCHAR GetPlayerLevel();             //玩家等级
    DWORD GetPlayerMaxHealth();         //玩家最大血量
    DWORD GetPlayerDataAddr();          //玩家数据基址
    DWORD GetPlayerID();                //id
    wchar_t* GetPlayerName();           //名
    UCHAR GetPlayerMana();              //法力值
    float GetPlayerMaxVit();            //轻功
    float GetPlayerVit();               //当前轻工值
    int GetPlayerVitStatus();           //轻功状态
    BOOL GetPlayerPos(fPosition* fpos);   //float坐标
    BOOL GetPlayerPos2(sPosition* spos);            //short型坐标
    float GetPlayerViewPoint();         //角色面向
    DWORD GetPlayerQuestUIStatus();     //判断角色任务相关ui状态是否弹出
    DWORD GetPlayerQuestUIStatusts();   //判断角色任务相关ui状态是否弹出
    BYTE GetPlayerDeadStatus();         //死亡状态
    DWORD GetCityID();
    BOOL GetPlayExperienceStatus();     //获得经验药状态
    BOOL GetPlayExperienceStatusName(DWORD m_adressA, wchar_t* ExperienceName);  //获取经验名字  参数1是UI地址  参数2 是药品的名字
    DWORD GetExperienceNameID_SY(int i, DWORD m_adress); //获取经验药名字ID结构的索引
    DWORD GetExperienceNameID(DWORD ID);        //获取经验名字ID
    wchar_t* GetExperienceName(DWORD ID);       //获取经验名字
    BOOL GetPlayerFightingStatus();             //获得战斗状态
    BOOL GetPlayerSkillStatus();                //获得是否正在使用技能状态
    BOOL GetPlayerBusy();                       //角色当前是否正在忙碌
    DWORD GetPlarerRedHeart();                  //获取本角色红心数量



    void _LinQuJiangLi();



    //对象
    ObjectNode* GetObjectBinTreeBaseAddr();
    void GetAllObjectToVector(ObjectNode* pNode, ObjectVector& RangeObject);
    void _GetRangeObjectToVector(ObjectNode* pNode, DWORD range, ObjectVector& RangeObject);
    void GetRangeMonsterToVector(DWORD range, ObjectVector& MonsterVec);
    void GetRangeObjectToVector(ObjectNode* pNode, DWORD range, ObjectVector& RangeObject);
    void GetRangeLootObjectToVector(DWORD range, ObjectVector& LootVec);
    void GetRangeTaskItemToVectr(ObjectVector& TastItemVector, DWORD range);
    ObjectNode* GetObjectByName(const wchar_t szName[], DWORD range = 500);
    BYTE GetObjectType(DWORD pObjAddress);                          //对象类型
    BOOL _GetObjectPos(DWORD pObjAddress, fPosition* pos);          //取对象坐标
    BOOL GetObjectPos(ObjectNode* pNode, fPosition* fpos);
    BOOL GetObjectPos_0xb(DWORD pObjAddress, sPosition* spos);      //对象short类型坐标
    BOOL GetObjectPos2_0x20(DWORD pObjAddress, fPosition* fpos);    //0x20对象使用这个取坐标
    BOOL GetObjectPos2_0x90(DWORD pObjAddress, sPosition* spos);    //0x90对象使用这个取坐标
    wchar_t* GetObjectNameByIndex(DWORD index);                     //对象名
    wchar_t* _GetObjectNameByIndex(DWORD index);
    wchar_t* GetObjectName(DWORD pObjAddress);
    DWORD GetObjectHP(DWORD pObjAddress);            //获取类型为4的对象血量
    DWORD GetObject_0x14(DWORD pObjAddress);
    DWORD GetObjectLevel(DWORD pObjAddress);        //取对象等级
    DWORD GetObjectSY12(DWORD pObjAddress);
    DWORD GetObjectSY(DWORD pObjAddress);
    DWORD GetObjectSy_90(DWORD pObjAddress);        //取90的索引
    DWORD GetIndexByType(DWORD pObjAddress);        //通过类型取得索引
    DWORD GetObjectView(DWORD pObjAddress);         //获取对象角度
	DWORD GetObjectTargetId(DWORD pObjAddress);     //获取对象目标
	ObjectNode* GetObjectById(DWORD Id);            //根据ID获取二叉地址
	BOOL IsObjectFightStatus(DWORD pObjAddress);   //获取对象战斗状态
	BOOL IsPlayerSkillStatus(DWORD pObjAddress);    //获得对象是否正在使用技能状态
	BOOL IsObjectControl(DWORD pObjAddress);        //获得对象是否可以双控




    //判断
    BOOL        isConfirmDeleteTalnetPanelShow();
    BOOL        isTalentPanelShow();
    BOOL        isStrikeCd(DWORD id);  //判断技能cd
	BOOL        isStrkeId(DWORD id);   //判断是否遍历出此技能
    BOOL        isPlayerDaodi();   //倒地状态
    BOOL        isLoots(DWORD pAddr);
    BOOL        isLoading(); //判断角色是否在打开任务物品的读条状态
    BOOL        isSelectedSlotHavePlayer(DWORD index); //角色选择界面当前的选择有一个角色存在
    BOOL        isQuestItem(DWORD pAddr); //判断是否是任务物品
    BOOL        isPlayerHasPickupQuestItemUI(); //有个拾取Ui弹出来
    BOOL        isPlayPickupUiStatus();//特殊的2次捡物判断
    BOOL        isPlayerChanneling();  //正在读条
    BOOL        isPlayerSteping();     //玩家正在走路
    BOOL        isLoginInSelectPlayer();   //判断是否进入了角色选择画面
    int         isLoadingMap();     //过图状态
    BOOL        isHaveXianlu(int index);
    BOOL        isCityConveyLoadingMap();
    BOOL        isCityConveying();
    BOOL        isPickupDeadBody();
    BOOL        isDeadBody(DWORD pAddr);
    BOOL        isCanFenjie(DWORD pAddr); //可以分解
    BOOL        isFuhuoing();
    DWORD       isYaoPingCD(_BAGSTU& goods); //药瓶cd
    DWORD       isStrikeLocked(int index, DWORD pAddr);
    DWORD       isStrikeCanUse(int index, DWORD pAddr);
    BOOL        isBagFull();
    BOOL        isCanKill(ObjectNode* pNode);
    BOOL        isCanLook(DWORD pAddr);    //可以看到的


    //任务
    void        _GetAcceptedQuestToVector(std::vector<Quest>& QuestVec);
    void        GetAcceptedQuestToVector(std::vector<Quest>& QuestVec);
    void        DeliverQuests(DWORD id, DWORD step, DWORD questtype, DWORD ff, DWORD npcid1, DWORD npcid2, DWORD unknow, DWORD mianban);     //交任务
    DWORD       GetTaskStartAddr();  //获取任务开始地址
    DWORD       GetTaskID(int i, DWORD pAddr);  //获得当前任务ID
    wchar_t*    GatTaskName(DWORD ID); //获取当前已接任务名字
    DWORD       GetTaskNameID(int i, DWORD pAddr);  //获得当前任务名字ID
    DWORD       GetTaskPresentAddr(int i, DWORD pAddr);  //获得当前任务地址
    DWORD       GetPresentTaskIndexes(int i, DWORD pAddr);  //获得当前做到第几个小任务
    DWORD       GetPresentTaskEndFlag(int i, DWORD pAddr , DWORD info); //获得当前小任务结束标志
    DWORD       GetPresentTaskNum(int i, DWORD pAddr , DWORD info);  //获得当前小任务已经打的怪数量
    void        OpenQuestItem(DWORD ID, DWORD ID2);   //打开任务物品
    DWORD       GetTaskStepById(DWORD id);
    void        _NPCJieRenWu(DWORD canshu1, DWORD canshu2, DWORD canshu3, DWORD canshu4, DWORD canshu5);//NPC接任务


    //ui 和技能
    BOOL        CloseAttendance();      //关闭开始的摇奖
    void        SetMouseMode();         //鼠标操作: 点击模式
    BOOL        ConfirmAgreement();     //确认登录游戏时显示的协议
    void        FaSonXianLuBao(DWORD adress1);
    void        OpenXianluUI();
    void        LoginGame(int index);   //进入游戏


    BOOL        ClickUI(UIOperator uiOp);   //点击ui
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
    DWORD       GetStrikeStartAddr();                               //获取技能开始地址
    DWORD       GetStrike_R_id(int index, DWORD p_R_addr);
    DWORD       GetStrike_R_addr(DWORD pStrikeStartAddr);
    DWORD       GetStrikeId1(int index, DWORD pStrikeStartAddr);  //取技能ID
    DWORD       GetStrikeId2(int index, DWORD pStrikeStartAddr);  //取技能ID
    DWORD       GetStrikeCD(int index, DWORD pAddr);
    BOOL        GetStrikeByName(const wchar_t* name, STRIKEINFO* pStrikeInfo);
    DWORD       GetRJianSkill(DWORD m_adress);  //取技能R键攻击的数组开始地址
    DWORD       GetRJSkillIDDD(int i, DWORD m_adress);  //取R键数组技能ID
    DWORD       GetRJSkillIDDD2(int i, DWORD m_adress);  //取R键技能数组ID2
    DWORD       GetRJSkillIsJieSuo(int i, DWORD m_adress);  //取R键技能是否已经解锁
    DWORD       GetRJSkillISShiYong(int i, DWORD m_adress);  //取R键技能是否可以使用
    DWORD       GetRJSkillCD(int i, DWORD m_adress);  //取R键技能是否冷却
    void        Fuhuo(DWORD uiAddr);
    void        DaKaiJiNengMianBan(DWORD adress, DWORD adress1); //打开技能面板


    //加点
    void    JiaJiNengDian(DWORD ID); //加技能点
    void    _JiaJiNengDian(DWORD ID); //加技能点
    void    QuChuJiNengDian(DWORD ID); //去除技能点
    void    _QuChuJiNengDian(DWORD ID); //去除技能点
    void    QueRenJiNengDian(); //确认技能点
    void    _QueRenJiNengDian(); //确认技能点
    void    OpenDeleteTalentPanel();
    void    _OpenDeleteTalentPanel();
    void    DaKaiQingChuQuanBuJiNengJieMian(DWORD adress, DWORD adress1);
    void    ConfirmDeletePalentPanelShowOk();
    void    _ConfirmDeletePalentPanelShowOk();
    void    QueRenQingChuQuanBuJiNengJieMian(DWORD adress, DWORD adress1);
    void    OpenTalentUI();
    void    _OpenTalentUI();


    //商品
    void        DaKaiDuiHuaKuang(DWORD ID, DWORD ID2);
    void        GuanBiDuiHuaKuangChuanKou(DWORD adress, DWORD adress1);
    void        GouMaiWuPing(DWORD Num, DWORD Ind, DWORD Adress);
    void        CunCangku(_BAGSTU& goods);              //放仓库
    void        SellItem(_BAGSTU& bag, DWORD adress);
    BOOL        OpenShangDian(wchar_t* name, DWORD* pUiAddr); //打开商品对话框
    void        CloseShangDian();
    void        DeleteItem(_BAGSTU* bag);   //摧毁一个物品

    //背包
    void        _GetAllGoodsToVector(BagVector& RangeObject);
    void        GetAllGoodsToVector(BagVector& RangeObject);                // 遍历背包
    void        GetAllBodyEquipToVector(BagVector& RangeObject);
    void        _GetAllBodyEquipToVector(BagVector& RangeObject);

    BOOL        GetAllBaGuaToVector(BagVector& BaGuaVec);
    BOOL        GetSpecBaGuaToVector(wchar_t* name, BagVector& BaGuaVec);
    DWORD       GetBagbodyInfoBase();                   //获取背包身上装备仓库遍历Base
    DWORD       GetBagInfoBase(DWORD pAddr);            //获取背包遍历Base
    DWORD       GetBodyInfoBase(DWORD pBase);
    DWORD       GetBagGridNumber();                     //当前背包的总的格子数
    DWORD       GetGoodsBase(DWORD pAddr, int index);   //获取物品的首地址
    DWORD       GetGoodsID(DWORD pAddr);                //获取物品的ID
    DWORD       GetGoodsNameID(DWORD pAddr);            //获取物品的名字ID
    DWORD       GetGoodsBagInfo(DWORD m_Adress);
    DWORD       GetGoodsType(DWORD pAddr);          //获取物品的类型
    DWORD       GetGoodsPos(DWORD pAddr);           //获取物品的所在格子数
    DWORD       GetGoodsNum(DWORD pAddr);           //获取物品的数量
    DWORD       GetGoodsDur(DWORD pAddr);           //获取物品的持久
    DWORD       GetGoodsLV(DWORD pAddr);            //获取物品的等级


    BOOL        GetGoodsFromBagByName(std::wstring name, BagVector& GoodsVec);
    BOOL        GetGoodsFromEquipByName(wchar_t* name, _BAGSTU* goods);
    BOOL        GetGoodsByEquipPos(DWORD pos, _BAGSTU* goods);      //根据位置取得物品信息


    BOOL        FillGoods(_BAGSTU& goods);
    int         GetGoodsColor(DWORD m_Adress);  //获取物品的颜色
    char        GetGoodsIsFengYin(DWORD m_Adress);  //获取物品是否封印
    DWORD       GetBagYouJianCaoZuoType(DWORD Adress, DWORD AAA); // 获取背包物品右键操作类型
    DWORD       GetGoodsYouJianType(DWORD m_BagLeiXing, DWORD m_Info); //获取背包物品右键操作类型
    DWORD       GetGoodsWuQiPingJi(DWORD m_Adress);  //获取武器的评级
    DWORD       GetGoodsWuQiDangQianJingYan(DWORD m_Adress);  //获取武器当前的经验
    DWORD       GetGoodsBiDui(DWORD m_Adress);  //获取物品的比对
    DWORD       GetGoodsBiDui_A(DWORD m_Adress);  //获取物品的比对A
    DWORD       GetBaGuaGeZiShu(DWORD m_Adress);  //获取八卦格子数
    BOOL        GetGoodsByName_Hezi(wchar_t* name, BagVector& GoodsVec); //用来枚举盒子
    void        KaiHeZi(_BAGSTU& bag);
    DWORD       SortBag();  //整理背包
    BOOL        NewBag();


    //武器强化
    void  HeChengWuQi(_BAGSTU& zhu, _BAGSTU& fu);
    void  HeChengWuQi_Po5(_BAGSTU& zhu, _BAGSTU& fu); //合成武器破5
    void  HeChengWuQi_Po10(_BAGSTU& zhu, _BAGSTU& fu, DWORD adress); //合成武器破10
    void  JieFengZhuangBei(DWORD zhuangbei, DWORD jiefengfu_ID, DWORD num);
    void  JieFengZhuangBei(DWORD adress1, DWORD adress2, DWORD adress3, DWORD adress4, DWORD adress5, DWORD adress6, DWORD adress7); //解封盒子
    void  FenJie(_BAGSTU& bag);
    DWORD GetKaiShiAdress();//获取开始地址
    DWORD GetBiJiaoShu(int i, DWORD m_adress); //获取比较数值
    DWORD _IsCanShu(DWORD adress, DWORD adress1); ////是否是这个参数
    DWORD IsCanShu(DWORD adress, DWORD adress1); ////是否是这个参数
    DWORD GetBiJiaoShu1(int i, DWORD m_adress); // //获取比较数值1
    DWORD GetBiJiaoShu2(int i, DWORD m_adress); //获取比较数值2
    DWORD GetBiJiaoShu3(DWORD m_adress);  //获取比较数值3
    DWORD GetBiJiaoShu4(int i, DWORD m_adress); //获取比较数值4



    //穿装备
    void        WearEquipment(_BAGSTU& bag);
    void        _XieZhuangBei(DWORD pos);



    //捡东西
    void        Pickup1(ObjectNode* pObj);    //第一次捡
    void        Pickup2(ObjectNode* pObj);   //第二次捡起来
    void        Pickup2ts();   //特殊的2次捡物
    BOOL        Pickup(ObjectNode* pObj);     //捡东西
    void        _PickupTask(ObjectNode* pObj);  //

    BOOL        PickupTask(ObjectNode* pNode);
    BOOL        PickupTaskts(ObjectNode* pNode);
    void        PickupDeadbody(DWORD id1, DWORD id2);
    BOOL        PickupDeadbody(DWORD range = 500);  //捡起尸体, 有逻辑的, 自动遍历范围内
    void        PickdownBody(); //这个用来一个任务捡起尸体又放下来完成任务



    //走路
    BOOL Stepto(fPosition& tarpos, double timeOut = 10, DWORD okRange = CAN_OPERATOR, DWORD tooLong = 1000, BOOL sp3x = FALSE);
    void Step(float x, float y, float z);
    void Step3x(float x, float y, float z);
    BOOL Step(ObjectNode* pNode);
    void Stepto3x();
    void ZOULUSHUNYI(DWORD* adress, DWORD adrewss);
    void OverShunyi(BOOL bEnable); //过图
    void _NewSpend(float x);
    void TiaoYue();




    //攻击
    int GetHealth(DWORD theValue);
    void ChiYao(_BAGSTU& goods);
    void ChiYao(const wchar_t* name);       //吃药, 药名
    void Attack(int id);
    int _Attack(int id);
    void Attack(const wchar_t* name);


    //转向
    void Turn(int angle);
    void TurnTo(fPosition& pos);
    void TurnTo(float x, float y, float z);     //视角



    //排序, 配置文件的优先级过滤
    static BOOL UDgreater(ObjectNode* elem1, ObjectNode* elem2);

    //组队
    void TuiChuDuiWu(); //退出队伍
    void YaoQingZuDui(DWORD ID, DWORD Info); /*邀请组队 参数1是对象ID 参数2 就是10000数值 */;
    DWORD DuiWu_EndAdress() /*遍历队伍的结束地址 */;
	DWORD DuiWu_StartAdress();//队伍开始地址
	BOOL GetPartyInfo(TeamVector& TeamInfo);//获取队伍信息
	DWORD GetPartyByAddress(DWORD PartyAddress,int i);//获取当前角色地址
	wchar_t* GetPartyName(DWORD PartyAddress);//获取队伍角色名
	DWORD GetPartyChannel(DWORD PartyAddress);//获取角色当前频道
	DWORD GetPartyCurrlife(DWORD PartyAddress);//获取角色当前血值
	DWORD GetPartyMaxlife(DWORD PartyAddress);//获取角色最大血值
	DWORD GetPartyId(DWORD PartyAddress);//获取角色id
	DWORD GetPartyId2(DWORD PartyAddress);//获取角色id2
	fPosition GetPartyPos(DWORD PartyAddress);//获取角色x坐标
	DWORD GetPartyAngle(DWORD PartyAddress);//获取角色面向
	DWORD GetPartyLv(DWORD PartyAddress);//获取角色等级
private:
    HANDLE m_hModuleBsEngine;
};


//辅助函数
BYTE ReadByte(DWORD addr);
WORD ReadWORD(DWORD addr);
DWORD ReadDWORD(DWORD addr);
int ReadInt(DWORD addr);
float ReadFloat(DWORD addr);
wchar_t* ReadStr(DWORD addr);


#endif
