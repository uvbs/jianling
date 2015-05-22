#pragma once


#include "gamecall.h"
#include "GameHook.h"
#include "..\JLkit\JLkitSocket.h"

class GamecallEx: public Gamecall, public ITCPSocketSink
{
protected:
    GamecallEx();
    ~GamecallEx();
    DECLARE_SINGLETON(GamecallEx)


public:
    BOOL Init();
    void UnLoad();


    //网络回调
private:
    virtual bool OnEventTCPSocketLink(CJLkitSocket* pSocket, INT nErrorCode) ;
    virtual bool OnEventTCPSocketShut(CJLkitSocket* pSocket, INT nErrorCode);
    virtual bool OnEventTCPSocketRead(CJLkitSocket* pSocket, const Tcp_Head& stTcpHead, void* pData, WORD wDataSize);

    CJLkitSocket sock;


public:
    DWORD GetRangeLootCount(DWORD range);
    DWORD GetRangeMonsterCount(DWORD range = CAN_OPERATOR); //取范围内怪物数量, 一般用来判断是否用aoe攻击


    //拾取, UI
    void Pickup(int pos, DWORD range);        //捡起范围内掉落
    BOOL PickupTask(DWORD range = CAN_OPERATOR);    //打开任务物品, 这个范围取值是游戏内能看到f键亮的距离
    BOOL PickupTaskts(DWORD range = CAN_OPERATOR);  //打开任务物品, 这个范围取值是游戏内能看到f键亮的距离
    BOOL PickupSpecTypeTask(DWORD range, DWORD type, wchar_t* name = NULL, BOOL flag = FALSE);
    BOOL PickupSpecTypeTaskts(DWORD range, DWORD type, wchar_t* name = NULL);
    void PickupTask(DWORD range, DWORD taskid, DWORD taskstep);
    void Pickdown();    //这个当前用来一个任务中放尸体到火堆中, 暂时不知能不能通用
    void LinQuJiangLi();


    //任务
    void DeliverQuests(DWORD id, DWORD step, wchar_t* name, DWORD questtype = 0, DWORD ff = 0xff, DWORD unknow = 0);
    void DeliverQuests(DWORD id, DWORD step, DWORD npcid1, DWORD npcid2, DWORD questtype , DWORD ff, DWORD unknow);
    void GoodsQuests(DWORD id, DWORD step, wchar_t* name, DWORD questtype = 0, DWORD ff = 0xff, DWORD unknow = 0);
    void NPCJieRenWu(DWORD canshu1, DWORD canshu2, DWORD canshu3, DWORD canshu4, DWORD canshu5);
    void NPCJieRenWu(wchar_t* name, DWORD canshu3, DWORD canshu4, DWORD canshu5);
    void Yaojiang(wchar_t* ZenName, wchar_t* BaGuaName);



	
    //打怪
    void KillBoss(const wchar_t* name);
    int FindThenKill(int pos, DWORD range, DWORD mode, DWORD MyQuestStep = 0, DWORD MyQuestID = 0, DWORD canKillRange = CAN_OPERATOR);    //找到杀掉
    BOOL kill_PickupBody();
    BOOL kill_Task(int MyQuestID, int MyQuestStep);
    void Kill_Tab(int id);//tab释放等待

    //自定义杀怪过滤
    BOOL isCustomKill_DontKill(wchar_t* name);
    BOOL isCustomKill_AlwaysKill(wchar_t* name);
    BOOL isCustomKill_HaveName(wchar_t* name);

    //应用杀怪策略
    BOOL Kill_ApplyConfig(ObjectVector& ObjectVec);


    //辅助线程
    static UINT CALLBACK KeepAliveThread(LPVOID pParam);

    //杀怪
    int KillObject(DWORD range, ObjectNode* pNode, DWORD mode, DWORD canKillRange = CAN_OPERATOR,BOOL Rush = FALSE); //杀死这个对象
    void AddCustomKill(wchar_t* name, CUSTOMTYPE type);
	void Party_KillObject();


    //控制
    BOOL Stepto(float y, float x, float z, double timeout = 10, DWORD OkRange = CAN_OPERATOR, DWORD toolong = 1000, BOOL sp3x = FALSE);
    void Stepto(wchar_t* name);
    void Stepto(ObjectNode* pNode);
    void SteptoBack(ObjectNode *pObj);
	wchar_t* SteptoParty();//跟随组队玩家

    void FollowNpc(wchar_t* name, DWORD range = 1000);
    void FuHuo();
    BOOL _CityConvey(DWORD cityid);     //传送
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
    void CuncangkuByConfig();//配置文件存仓库
    void DeleteItem(std::wstring name);   //删除一个物品
    void DeleteItemByConfig();      //删除配置文件中所有物品
    void SellItem(wchar_t* name, wchar_t* npcName, BOOL bClose = TRUE);     //卖掉一个物品
    void SellItemByConfig(wchar_t* name);           //卖掉配置文件中所有物品
    void FenJie(wchar_t* name);     //分解指定物品, 所有数量
    void FenJieByConfig();    //分解配置文件中的所有物品

    void JieFengHezi(wchar_t* HeZiname, UCHAR keytype, wchar_t* Keyname, DWORD keyCount); //分解盒子
    void JieFengZhuangBei(wchar_t* name, wchar_t* cailiao_name, UINT count); //分解装备
    void FixWuqi();                     //修理武器

    BOOL XieZhuangBei(EQUITMENT_POS pos);           //卸装备
    void WearEquipment(wchar_t* name, int pos, BOOL Blur = FALSE); //穿装备


    //合成武器
    BOOL HeChengWuQi(EQUITMENT_POS type);
    BOOL HeChengWuQi_Po5(EQUITMENT_POS pos, wchar_t* name);
    BOOL HeChengWuQi_Po10(wchar_t* zname, wchar_t* name);
    BOOL HeChengWuQiByHun(EQUITMENT_POS pos);
    BOOL HeChengWuQi(EQUITMENT_POS pos, wchar_t* name);
    DWORD HuoQuWuQiPo10CanShu(DWORD m_adressA);  //参数是主武器的首地址;

    void XieBaoShi(DWORD pos);
    void JiaBaoShi(DWORD pos, wchar_t* name);
    BOOL BuqiBaGua(wchar_t* name);
    BOOL BuqiBaGua();
    BOOL TihuanBaGua(wchar_t* name);


    //天赋
    void AddTalent(DWORD id);   //添加一个技能点
    void DelAllTalent();    //删除所有技能点
    void DelTalent(DWORD id);
    void _NewSpend(float x);
    int ClearCustom();


    //任务
    int GetPresentTaskStep();    //获取当前任务步骤
    int GetPresentTaskID();     //当前任务ID;
    int GetTaskStepById(int id);
    //组队
    void AddToPary();


    //自定义的要杀的怪物名称
private:
    HANDLE m_hTHelper;
    CustKillVector CustomName;
};
