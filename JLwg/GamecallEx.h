#pragma once
#include "gamecall.h"
#include "..\JLkit\JLkitSocket.h"

class GamecallEx: public Gamecall, public ITCPSocketSink
{
protected:
    GamecallEx();
    ~GamecallEx();
    DECLARE_SINGLETON(GamecallEx)


public:
    BOOL Init();

    //����ص�
private:
    virtual bool OnEventTCPSocketLink(CJLkitSocket* pSocket, INT nErrorCode) ;
    virtual bool OnEventTCPSocketShut(CJLkitSocket* pSocket, BYTE cbShutReason);
    virtual bool OnEventTCPSocketRead(CJLkitSocket* pSocket, const Tcp_Head& stTcpHead, void* pData, WORD wDataSize);

    CJLkitSocket sock;

public:
    DWORD GetRangeLootCount(DWORD range);
    DWORD GetRangeMonsterCount(DWORD range = CAN_OPERATOR); //ȡ��Χ�ڹ�������, һ�������ж��Ƿ���aoe����


    //ʰȡ, UI
    void Pickup(int pos, DWORD range);        //����Χ�ڵ���
    BOOL PickupTask(DWORD range = CAN_OPERATOR);    //��������Ʒ, �����Χȡֵ����Ϸ���ܿ���f�����ľ���
    BOOL PickupTaskts(DWORD range = CAN_OPERATOR);  //��������Ʒ, �����Χȡֵ����Ϸ���ܿ���f�����ľ���
    BOOL PickupSpecTypeTask(DWORD range, DWORD type, wchar_t* name = NULL, BOOL flag = FALSE);
    BOOL PickupSpecTypeTaskts(DWORD range, DWORD type, wchar_t* name = NULL);
    void PickupTask(DWORD range, DWORD taskid, DWORD taskstep);
    void Pickdown();    //�����ǰ����һ�������з�ʬ�嵽�����, ��ʱ��֪�ܲ���ͨ��
    void LinQuJiangLi();


    //����
    void DeliverQuests(DWORD id, DWORD step, wchar_t* name, DWORD questtype = 0, DWORD ff = 0xff, DWORD unknow = 0);
    void DeliverQuests(DWORD id, DWORD step, DWORD npcid1, DWORD npcid2, DWORD questtype , DWORD ff, DWORD unknow);
    void GoodsQuests(DWORD id, DWORD step, wchar_t* name, DWORD questtype = 0, DWORD ff = 0xff, DWORD unknow = 0);
    void NPCJieRenWu(DWORD canshu1, DWORD canshu2, DWORD canshu3, DWORD canshu4, DWORD canshu5);
    void NPCJieRenWu(wchar_t* name, DWORD canshu3, DWORD canshu4, DWORD canshu5);
    void Yaojiang(wchar_t* Zen_name, wchar_t* BaGuaname);




    //���
    int FindThenKill(int pos, DWORD range, DWORD mode, DWORD MyQuestStep = 0, DWORD MyQuestID = 0, DWORD canKillRange = CAN_OPERATOR);    //�ҵ�ɱ��
    void kill_PickupOnce();
    BOOL kill_PickupBody();
    BOOL kill_Task(int MyQuestID, int MyQuestStep);
    void Kill_Tab();//tab�ͷŵȴ�
    void AttackNormal();    //��ͨ���� , rt ѭ����, ��Ҫ������ʹ�ӽ����������������
    void AttackAOE();                       //AOE����

    //�Զ���ɱ�ֹ���
    BOOL isCustomKill_DontKill(wchar_t* name);
    BOOL isCustomKill_AlwaysKill(wchar_t* name);
    BOOL isCustomKill_HaveName(wchar_t* name);

    //Ӧ��ɱ�ֲ���
    BOOL Kill_ApplyConfig(ObjectVector& ObjectVec);


    //�����߳�
    static UINT CALLBACK KeepAliveThread(LPVOID pParam);
    static UINT CALLBACK AttackHelperThread(LPVOID pParam);

    //ɱ��
    int KillObject(DWORD range, ObjectNode* pNode, DWORD mode, DWORD canKillRange = CAN_OPERATOR); //ɱ���������
    void AddCustomKill(WCHAR* name, DWORD type);



    //����
    BOOL Stepto(float y, float x, float z, double timeout = 10, DWORD OkRange = CAN_OPERATOR, DWORD toolong = 1000, BOOL sp3x = FALSE);
    void Stepto(wchar_t* name);
    void FollowNpc(wchar_t* name, DWORD range = 1000);
    void FuHuo();
    BOOL _CityConvey(DWORD cityid);     //����
    void CityConvey(DWORD cityid);//���� �߼� �ж�
    void Shunyi(TCHAR* szLujing);
    void NewSpend(float x);
    void TurnTo(ObjectNode* pNode);
    void TurnToNear(DWORD range);


    //��·
    void randXianlu(DWORD MaxXianlu);


    //��Ʒ, ����
    void NewBag();
    void BuyItem(DWORD nums, DWORD index, wchar_t* npcname, BOOL bClose = TRUE);  //������Ʒ
    void CunCangku(wchar_t* name, wchar_t* npcname);   //�Ųֿ�
    void CuncangkuByConfig(wchar_t* name);//�����ļ���ֿ�
    void DeleteItem(wchar_t* name);   //ɾ��һ����Ʒ
    void DeleteItemByConfig();      //ɾ�������ļ���������Ʒ
    void SellItem(wchar_t* name, wchar_t* npcName, BOOL bClose = TRUE);     //����һ����Ʒ
    void SellItemByConfig(wchar_t* name);           //���������ļ���������Ʒ
    void FenJie(wchar_t* name);     //�ֽ�ָ����Ʒ, ��������
    void FenJieByConfig();    //�ֽ������ļ��е�������Ʒ

    void JieFengHezi(wchar_t* HeZiname, UCHAR keytype, wchar_t* Keyname, DWORD keyCount); //�ֽ����
    void JieFengZhuangBei(wchar_t* name, wchar_t* cailiao_name, UINT count); //�ֽ�װ��
    void FixWuqi();                     //��������

    BOOL XieZhuangBei(EQUITMENT_POS pos);           //жװ��
    void WearEquipment(wchar_t* name, int pos, BOOL Blur = FALSE); //��װ��


    //�ϳ�����
    BOOL HeChengWuQi(EQUITMENT_POS type);
    BOOL HeChengWuQi_Po5(EQUITMENT_POS pos, wchar_t* name);
    BOOL HeChengWuQi_Po10(wchar_t* zname, wchar_t* name);
    BOOL HeChengWuQiByHun(EQUITMENT_POS pos);
    BOOL HeChengWuQi(EQUITMENT_POS pos, wchar_t* name);
    DWORD HuoQuWuQiPo10CanShu(DWORD m_adressA);  //���������������׵�ַ;

    void XieBaoShi(DWORD pos);
    void JiaBaoShi(DWORD pos, wchar_t* name);
    BOOL BuqiBaGua(wchar_t* name);
    BOOL BuqiBaGua();
    BOOL TihuanBaGua(wchar_t* name);


    //�츳
    void AddTalent(DWORD id);   //���һ�����ܵ�
    void DelAllTalent();    //ɾ�����м��ܵ�
    void DelTalent(DWORD id);
    void _NewSpend(float x);
    int ClearCustom();


    //���
    void AddToPary();




    //�Զ����Ҫɱ�Ĺ�������
private:
    Logger log;
    HANDLE m_hThreads[2];
    BOOL m_bStopThread;
    BOOL m_bCanAoe;
    CustKillVector CustomName;
};
