#pragma once
#include "gamecall.h"


 class GamecallEx: public Gamecall
{
public:
    GamecallEx();
    ~GamecallEx();


    //拾取, UI
    void Pickup(int pos, DWORD range);        //捡起范围内掉落
    BOOL PickupTask(DWORD range = CAN_OPERATOR);	//打开任务物品, 这个范围取值是游戏内能看到f键亮的距离
	BOOL PickupTaskts(DWORD range = CAN_OPERATOR);	//打开任务物品, 这个范围取值是游戏内能看到f键亮的距离
    BOOL PickupSpecTypeTask(DWORD range, DWORD type, wchar_t* name = NULL);
	BOOL PickupSpecTypeTaskts(DWORD range, DWORD type, wchar_t* name = NULL);
    void PickupTask(DWORD range, DWORD taskid, DWORD taskstep);
    void Pickdown();    //这个当前用来一个任务中放尸体到火堆中, 暂时不知能不能通用
    void LinQuJiangLi();


    //任务
    void DeliverQuests(DWORD id, DWORD step, wchar_t* name, DWORD questtype = 0, DWORD ff = 0xff, DWORD unknow = 0);
	void GoodsQuests(DWORD id, DWORD step, wchar_t *name, DWORD questtype = 0, DWORD ff = 0xff, DWORD unknow = 0);
    void NPCJieRenWu(DWORD canshu1, DWORD canshu2, DWORD canshu3, DWORD canshu4, DWORD canshu5);
    void Yaojiang(wchar_t* Zen_name, wchar_t* BaGuaname);




    //打怪
    int	FindThenKill(int pos, DWORD range, DWORD mode, DWORD MyQuestStep = 0, DWORD MyQuestID = 0, DWORD canKillRange = CAN_OPERATOR);    //找到杀掉
    void kill_PickupOnce();
    BOOL kill_PickupBody();
    BOOL kill_Task(int MyQuestID, int MyQuestStep);
    void Kill_Tab();//tab释放等待
    void AttackNormal();	//普通攻击 , rt 循环按, 需要参数来使视角总是面向这个对象
    void AttackAOE();						//AOE攻击



    //杀怪
    int	KillObject(DWORD range, ObjectNode* pNode, DWORD mode, DWORD canKillRange = CAN_OPERATOR); //杀死这个对象
    void AddCustomKill(WCHAR* name, DWORD type);



    //控制
    BOOL Stepto(float y, float x, float z, double timeout = 10, DWORD OkRange = CAN_OPERATOR, DWORD toolong = 1000, BOOL sp3x = FALSE);
    void Stepto(wchar_t* name);
    void FollowNpc(wchar_t* name, DWORD range = 1000);
    void FuHuo();
    BOOL _CityConvey(DWORD cityid);		//传送
    void CityConvey(DWORD cityid);//传送 逻辑 判断
    void Shunyi(TCHAR* szLujing);
    void NewSpend(float x);
    void TurnTo(ObjectNode* pNode);
    void TurnToNear(DWORD range);
	

    //线路
    void randXianlu(DWORD MaxXianlu);


    //商品, 背包
    void NewBag();
    void BuyItem(DWORD nums, DWORD index, wchar_t* npcname, BOOL bClose = TRUE);  //购买物品
    void CunCangku(wchar_t* name, wchar_t* npcname);   //放仓库
    void CuncangkuByConfig(wchar_t* name);//配置文件存仓库
    void DeleteItem(wchar_t* name);   //删除一个物品
    void DeleteItemByConfig();		//删除配置文件中所有物品
    void SellItem(wchar_t* name, wchar_t* npcName, BOOL bClose = TRUE);     //卖掉一个物品
    void SellItemByConfig(wchar_t* name);			//卖掉配置文件中所有物品
    void FenJie(wchar_t* name);		//分解指定物品, 所有数量
    void FenJieByConfig();    //分解配置文件中的所有物品

    void JieFengHezi(wchar_t* HeZiname, UCHAR keytype, wchar_t* Keyname, DWORD keyCount); //分解盒子
    void JieFengZhuangBei(wchar_t* name, wchar_t* cailiao_name, UINT count); //分解装备
    void FixWuqi();						//修理武器

    BOOL XieZhuangBei(EQUITMENT_POS pos);			//卸装备
    void WearEquipment(wchar_t* name, int pos);  //穿装备


    //合成武器
    BOOL HeChengWuQi(EQUITMENT_POS type);
    BOOL HeChengWuQi_Po5(EQUITMENT_POS pos, wchar_t* name);
	BOOL HeChengWuQi_Po10(wchar_t* zname, wchar_t *name);
    BOOL HeChengWuQiByHun(EQUITMENT_POS pos);
    BOOL HeChengWuQi(EQUITMENT_POS pos, wchar_t* name);
	DWORD HuoQuWuQiPo10CanShu(DWORD m_adressA);  //参数是主武器的首地址;

    void XieBaoShi(DWORD pos);
    void JiaBaoShi(DWORD pos, wchar_t* name);
    BOOL BuqiBaGua(wchar_t* name);
    BOOL BuqiBaGua();
    BOOL TihuanBaGua(wchar_t* name);
	

    //天赋
    void AddTalent(DWORD id);	//添加一个技能点
    void DelAllTalent();	//删除所有技能点
    void DelTalent(DWORD id);
    void _NewSpend(float x);
    int ClearCustom();

private:
    //自定义的要杀的怪物名称
    Logger log;
};
