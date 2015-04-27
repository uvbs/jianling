#include "stdafx.h"
#include "GamecallEx.h"
#include "GameConfig.h"
#include "GameLog.h"
#include "CombatBoss.h"
#include "combatEvent.h"
#include "EventDispatcher.h"

IMPLEMENT_SINGLETON(GamecallEx)


//���캯��
GamecallEx::GamecallEx()
{
    m_bStopThread = FALSE;
    m_bCanAoe = FALSE;
}

GamecallEx::~GamecallEx()
{

    TRACE(_T("~GamecallEx"));
    m_bStopThread = TRUE;

    //�ȴ������߳��˳�
    for(int i = 0; i < sizeof(m_hThreads) ; i++)
    {
        if(m_hThreads[i] != INVALID_HANDLE_VALUE)
        {
            WaitForSingleObject(m_hThreads[i], INFINITE);
            CloseHandle(m_hThreads[i]);
        }
    }
}



BOOL GamecallEx::HeChengWuQi_Po5(EQUITMENT_POS pos, wchar_t* name)
{

    _BAGSTU zhu;
    if(GetGoodsByEquipPos(pos, &zhu) == FALSE)
    {
        TRACE(_T("װ��λ��û����Ʒ"));
        return FALSE;
    }


    //���жϲ���������û��, û������
    _BAGSTU fu;
    if(GetGoodsFromBagByName(name, &fu) == FALSE)
    {
        TRACE(_T("������û�ж�Ӧ��Ʒ"));
        return FALSE;
    }


    //������, ���жϺϳ�Ŀ����û���Ѿ���5
    BOOL isFull5_fu = TRUE;

    //��5������ò�ƶ��ĳ�����ɫ�ˣ���������ǿ��
    //if (_wcsicmp(fu.name,qianhun) == 0)
    //{
    //  isFull5_fu = TRUE;
    //}else
    //{
    //  if(fu.m_PingJi == 5 &&
    //      (fu.m_DangQianJingYanZhi == fu.m_DangQianJingYanZongZhi))
    //  {
    //      //�Ѿ���5
    //      isFull5_fu = TRUE;
    //  }
    //}


    if(isFull5_fu)
    {

        PARAM_GUANSHANGDIAN temp;
        temp.argv1 = (DWORD)&zhu;
        temp.argv2 = (DWORD)&fu;
        sendcall(id_msg_HeChengWuQi_Po5, &temp);
        Sleep(2000);
        //��5�������ǿ��
        HeChengWuQi(pos);
    }
    else
    {
        TRACE(_T("����������δ��5��"));
        TRACE(_T("��ʼʹ�����ϳ�"));
        if(HeChengWuQiByHun(pos))
        {
            return HeChengWuQi_Po5(pos, name);
        }
        TRACE(_T("�ϳ����, ��Ȼ����5"));
    }

    return TRUE;
}


//TODO:
BOOL GamecallEx::HeChengWuQiByHun(EQUITMENT_POS pos)
{
    _BAGSTU goods;
    GetGoodsByEquipPos(pos, &goods);

    BOOL bFind = FALSE;
    _BAGSTU zhu;


    if(pos == WUQI)
    {
        if(goods.m_LV <= 36)
        {
            if(GetGoodsFromBagByName(hun1, &zhu))
            {
                bFind = TRUE;
            }
        }


        if(bFind == FALSE)
        {
            if(GetGoodsFromBagByName(hun2, &zhu) == FALSE)
            {
                if(GetGoodsFromBagByName(hun3, &zhu) == FALSE)
                {
                    if(GetGoodsFromBagByName(hun4, &zhu) == FALSE)
                    {
                        TRACE(_T("û���ҵ����������"));
                        return FALSE;
                    }
                }
            }

        }
    }
    else
    {
        if(goods.m_LV <= 36)
        {
            if(GetGoodsFromBagByName(sshun1, &zhu))
            {
                bFind = TRUE;
            }
        }


        if(bFind == FALSE)
        {
            if(GetGoodsFromBagByName(sshun2, &zhu) == FALSE)
            {
                if(GetGoodsFromBagByName(sshun3, &zhu) == FALSE)
                {
                    if(GetGoodsFromBagByName(sshun4, &zhu) == FALSE)
                    {
                        TRACE(_T("û���ҵ��������������"));
                        return FALSE;
                    }
                }
            }

        }
    }


    HeChengWuQi(pos, zhu.name);
    return TRUE;
}




BOOL GamecallEx::HeChengWuQi(EQUITMENT_POS pos, wchar_t* name)
{


    _BAGSTU fu;
    _BAGSTU zhu;

    //fix
    if(GetGoodsFromBagByName(name, &fu) &&
            GetGoodsByEquipPos(pos, &zhu))
    {

        PARAM_GUANSHANGDIAN temp;
        temp.argv1 = (DWORD)&zhu;
        temp.argv2 = (DWORD)&fu;

        sendcall(id_msg_HeChengWuQi, &temp);

    }
    else
    {
        TRACE(_T("%s: û���ҵ�������Ƶ�װ��"), FUNCNAME);
        return FALSE;
    }


    return TRUE;
}


// ������������1
// ���Ե�������4
// ���ε�������5
BOOL GamecallEx::HeChengWuQi(EQUITMENT_POS pos)
{

    GameConfig* pConfig = GameConfig::GetInstance();

    DWORD qhColor;


    //������ɫȡ����Ϸ�ڶ�Ӧ������
    if(strGreen == pConfig->m_szQHColor)
    {
        qhColor = 3;
    }
    else if(strBlue == pConfig->m_szQHColor)
    {
        qhColor = 4;
    }
    else if(strPurple == pConfig->m_szQHColor)
    {
        qhColor = 5;
    }
    else
    {
        TRACE(_T("һ��δ֪����ɫ"));
        qhColor = 3;
    }

    _BAGSTU goods;
    GetGoodsByEquipPos(pos, &goods);


    //���ﴦ���ȡ���ϵ��߼�
    std::vector<_BAGSTU> Cailiao;
    std::vector<_BAGSTU> AllBagItem;
    GetAllGoodsToVector(AllBagItem);

    TRACE1("AllBagItem:%d", AllBagItem.size());
    for(DWORD i = 0; i < AllBagItem.size(); i++)
    {

        ItemVector* Items;
        if(pos == 1)
        {
            Items = &pConfig->m_QHWeapons;
        }
        else if(pos == 5)
        {
            Items = &pConfig->m_QHAccessories;
        }
        else
        {
            continue;
        }


        for(ItemIterator it = Items->begin(); it != Items->end(); it++)
        {
            if(*it == AllBagItem[i].name)
            {
                Cailiao.push_back(AllBagItem[i]);
                TRACE(_T("������һ������wcstok"));
                break;
            }
        }

        //�ж�ͬ����
        if(AllBagItem[i].m_Type == goods.m_Type)
        {
            if(AllBagItem[i].m_YanSe == qhColor) //��ɫ
            {
                //����Ե���һ������
                Cailiao.push_back(AllBagItem[i]);
                TRACE(_T("������һ������"));

            }
        }
    }

    //TRACE1("���в���:%d",Cailiao.size());
    //ʹ�����в���
    for(DWORD j = 0; j < Cailiao.size(); j++)
    {

        //����ȼ�5, ���Ҿ�����
        if(goods.m_DangQianJingYanZhi == goods.m_DangQianJingYanZongZhi)
        {
            if(goods.m_PingJi == 5 ||
                    goods.m_PingJi == 10)
            {
                TRACE(_T("��Ʒǿ���Ѿ�����"));
                return TRUE;
            }
        }

        Sleep(500);

        PARAM_GUANSHANGDIAN temp;
        temp.argv1 = (DWORD)&goods;
        temp.argv2 = (DWORD)&Cailiao[j];

        sendcall(id_msg_HeChengWuQi, &temp);
    }


    return FALSE;
}


//����״̬=1��2
void GamecallEx::FuHuo()
{
    //����, ���Ǹ�����
    if(GetPlayerDeadStatus() != 1 && GetPlayerDeadStatus() != 2)
    {
        OutputDebugString(_T("����״̬"));
        return;
    }

    DWORD uiAddr = 0;
    GetUIAddrByName(L"SkillBarPanel", &uiAddr);
    if(uiAddr == 0)
    {
        OutputDebugString(_T("����ʱû�б�����UI"));
        return;
    }

    TRACE(_T("uiAddr:%d"), uiAddr);
    uiAddr = ReadDWORD(uiAddr + fuhuo_offset1);
    TRACE(_T("uiAddr2:%d"), uiAddr);
    __try
    {

        sendcall(id_msg_Fuhuo, &uiAddr);
        //�����ȴ�10�� �ȴ������ͼ�׶� ���ɸ������ ʱ�������ױ���
        Sleep(10000);

        /*for(;;)
        {
            if(isLoadingMap() != 3)
            {
                TRACE(_T("�������"));
                break;
            }
            Sleep(500);
        }*/
        WaitPlans();
    }
    __except(1)
    {
        OutputDebugString(FUNCNAME);
    }
}


//����
//����1: ����
//����2: ��Χ
//�� ����1 ��Χ �ڵĵ���
void GamecallEx::Pickup(int pos, DWORD range)
{

//startLoot:

    //�ߵ���, ������Χ��Χ�Ŀ�ʰȡ����
    std::vector<ObjectNode*> RangeObject;
    GetRangeLootObjectToVector(range, RangeObject);

    if(RangeObject.size() == 0)
    {
        TRACE(_T("û�ж����ɼ�"));
        return;
    }

    std::sort(RangeObject.begin(), RangeObject.end(), UDgreater);
    for(DWORD i = 0; i < RangeObject.size(); i++)
    {
        ObjectNode* pNode = RangeObject[i];

        fPosition fpos;
        if(GetObjectPos(pNode, &fpos))
        {
            fPosition fmypos;
            GetPlayerPos(&fmypos);

            //����ھ����ھͲ�Ҫ�߹�ȥ��
            //������Ϸ�ڲ���165���ڻ���� f ��ť
            if(CalcC(fpos, fmypos) >= CAN_OPERATOR)
            {
                Gamecall::Stepto(fpos, 10, 50, range * 2);
                Sleep(300);
            }
        }

        if(Gamecall::Pickup(pNode))
        {
            Sleep(100);
        }
        else
        {
            KeyPress(70);
            TRACE(_T("û�гɹ�������"));
        }
    }

}


//��ʬ��
void GamecallEx::Pickdown()
{
    // TODO: �ڴ���ӿؼ�֪ͨ����������
    DWORD Pos;
    DWORD info;
    DWORD info1;
    Pos = ReadDWORD(ReadDWORD(ReadDWORD(ReadDWORD(obj_enum_base) + huohua_offset1)  + huohua_offset2) + 0x14);
    info  = ReadDWORD(Pos + huohua_offset4); //��ʬ��4��ƫ��
    info1 = ReadDWORD(Pos + huohua_offset5); //��ʬ��5��ƫ��

    ObjectNode Node;
    Node.id = info;
    Node.id2 = info1;

    sendcall(id_msg_Pickup1, &Node);
}



//����
//����1: ����
//����2: ����, ��Ʒ��ui���λ��  0 ��ʼ
//����3: ����
void GamecallEx::BuyItem(DWORD nums, DWORD index, wchar_t* npcname, BOOL bClose)
{

    _ASSERTE(npcname != NULL);

    DWORD dwUiAddr = 0;
    BOOL bOpen = OpenShangDian(npcname, &dwUiAddr);
    if(bOpen == FALSE)
    {
        TRACE(_T("%s: û�ܴ򿪶Ի���"), FUNCNAME);
        return;
    }


    GouMaiWuPing(nums, index, dwUiAddr);


    if(bClose)
    {
        CloseShangDian();
    }
}


//жװ��
//���������ϵĸ�����
//TODO:
BOOL GamecallEx::XieZhuangBei(EQUITMENT_POS pos)
{
    _PARAM_JIEFENGZHUANGBEI temp;
    temp.argv1 = (DWORD)pos;
    sendcall(id_msg_XieZhuangBei, &temp);
    //����
    _BAGSTU stu;
    if(GetGoodsByEquipPos(WUQI, &stu) == FALSE)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

//˲���ƶ�
//����1: �ļ�����·��
void GamecallEx::Shunyi(TCHAR* szLujing)
{
    GameConfig* pConfig = GameConfig::GetInstance();

    TCHAR szExe[MAX_PATH] = {0};
    GetModuleFileName(AfxGetInstanceHandle(), szExe, MAX_PATH);
    PathRemoveFileSpec(szExe);
    PathAppend(szExe, _T("·��"));
    if(!PathFileExists(szExe))
    {
        _tmkdir(szExe);
    }

    PathAppend(szExe, szLujing);
    _tcscat(szExe, _T(".bin"));


    FILE* file = _tfopen(szExe, _T("rb"));
    if(file == NULL)
    {
        LOGER(_T("%s: open fail"), FUNCNAME);
        return;
    }
    else
    {
        TRACE(_T("��ȡ˲���ļ�,׼��˲��"));
    }

    //ȡ�ļ���С
    fseek(file, 0L, SEEK_END);
    int filesize = ftell(file);
    fseek(file, 0L, SEEK_SET);

    //�����ļ���С������Ҫ���Ͷ��ٴ�
    for(int i = 0; i < filesize / 17408; i++)
    {
        //ÿ�η���16384�ֽ�
        BYTE* buff = new BYTE[17408];
        BYTE* Oribuff = buff;


        for(int i = 0; i < 34; i++)
        {
            //��ѭ���ܹ�������16386�ֽ�
            BYTE temp[512];
            //TODO: ���ﻹ������, �ñ�֤512ȫ����������.
            //TODO: ��������ͬ��������, ��������
            size_t count = fread(temp, 1, 512, file);
            if(count == 0)
            {
                TRACE(_T("��ȡ����"));
            }
            else
            {
                //TRACE1("��ȡ:%d",count);
            }

            memcpy(buff, temp, 512);
            buff += 512;
        }

        //������16384�ֽ�
        PARAM_GUANSHANGDIAN temp;
        temp.argv1 = (DWORD)Oribuff;
        temp.argv2 = 0xee;
        sendcall(id_msg_ZOULUSHUNYI, &temp);
        Sleep(10);
    }

    TRACE(_T("����˲��"));
    fclose(file);
    TRACE(_T("�ر�˲���ļ�,�˳�˲��"));
}


void GamecallEx::kill_PickupOnce()
{
    //ɱ��������, ��ʱ�ķ�ΧΪ�˸��ɿ�д�ĳ�x2
    //if(GetRangeMonsterCount(200) == 0){
    //TRACE(_T("��Χ����, ��ʼ����"));
    Pickup(0, 170);
    //}
}

BOOL GamecallEx::kill_PickupBody()
{
    Sleep(1000);
    PickupDeadbody();
    Sleep(1000);
    if(isPickupDeadBody())
    {
        TRACE(_T("ɱ��ʱ������һ��ʬ��"));
        return TRUE;
    }

    return FALSE;
}


//id��ͬ, ���費ͬ����TRUE, ��ʾ���������
BOOL GamecallEx::kill_Task(int MyQuestID, int MyQuestStep)
{
    std::vector<Quest> QuestVec;
    GetAcceptedQuestToVector(QuestVec);


    DWORD step;
    Quest mainCurQuest;
    if(MyQuestID == 0)
    {
        mainCurQuest = QuestVec[0];
        step = mainCurQuest.step;
    }
    else
    {

        BOOL bFind = FALSE;
        for(DWORD i = 0; i < QuestVec.size(); i++)
        {
            if(MyQuestID == QuestVec[i].id)
            {
                bFind = TRUE;
                mainCurQuest = QuestVec[i];
                step = mainCurQuest.step;

            }
        }

        if(bFind == FALSE)
        {
            OutputDebugString(_T("û���ҵ���Ӧ������ID"));
            return FALSE;
        }
    }


    if(step != MyQuestStep)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

//����Զ���ɱ�ֹ���
void GamecallEx::AddCustomKill(WCHAR* name, DWORD type)
{

    CUSTOMKILL cust;

    int len = wcslen(name);
    WCHAR* lpName = new WCHAR[len];
    wcscpy(lpName, name);

    cust.name = lpName;
    cust.type = type;

    CustomName.push_back(cust);
}

//����Զ���ɱ�ֹ���
int GamecallEx::ClearCustom()
{
    CustomName.clear();
    //�ͷŵ�new���ڴ�
    for(int i = 0; i < CustomName.size(); i++)
    {
        delete []CustomName[i].name;
    }


    return 0;
}


//ɱ��
//����1: ����
//����2: �Բ���1����ķ�Χ
//����3: ģʽ
//���������ȫ����, ֱ�����
int GamecallEx::FindThenKill(int pos, DWORD range, DWORD mode, DWORD MyQuestStep, DWORD MyQuestID, DWORD canKillRange)
{



    fPosition fmypos;
    GetPlayerPos(&fmypos);

startKiLL:
    //TRACE(_T("��������"));
    std::vector<ObjectNode*> RangeObject;
    GetRangeMonsterToVector(range, RangeObject);


    //����
    //TRACE(_T("��������"));
    std::sort(RangeObject.begin(), RangeObject.end(), UDgreater);

    //TRACE(_T("������������"));
    //Ӧ��ɱ������, �����Զ����
    Kill_ApplyConfig(RangeObject);

    DWORD count = RangeObject.size();
    TRACE(_T("�ܹ�: %d ��Ŀ�����"), count);


    //ɱ��
    BOOL bTimeOut = FALSE;
    for(DWORD i = 0; i < count; i++)
    {
        if(isPickupDeadBody())
        {
            sendcall(id_msg_PickdownBody, 0);
            continue;
        }
        int killresult = KillObject(range, RangeObject[i], mode, canKillRange);
        if(killresult == RESULT_KILL_PLAYDEAD)
        {
            return RESULT_KILL_PLAYDEAD;
        }

        if(killresult == RESULT_KILL_TIMEOUT)
        {
            bTimeOut = TRUE;
        }
        if(mode & modePickupBody)
        {

            if(kill_PickupBody())
            {
                break;
            }
            /*else
            {
                TRACE(_T("û�о����û��ʰ��"));
                goto startKiLL;
            }*/
        }
        if(mode & modePickupOnce)
        {
            TRACE(_T("ִ��modePickupOnce"));
            kill_PickupOnce();
        }


        //�ж�������
        if(mode & modeTask)
        {
            TRACE(_T("ִ��modeTask"));
            if(kill_Task(MyQuestID, MyQuestStep))
            {
                goto exitfun;
            }
            else
            {
                goto startKiLL;
            }

        }

    }//for
    //�������й�С��Ƭ���ٱ�����
    Sleep(500);

    //�����һ�γ�ʱ, �ǿ�����һ�����صĵ��Ǵ��ڵĹ���
    //û�취ɱ��, �Ͳ�������ʣ���, ������ѭ��
    if(bTimeOut == FALSE)
    {
        //����ɱ���߼�ִ������ٱ���һ����Χ����, �����ɱ���ٷ���
        TRACE(_T("ִ��GetRangeMonsterCount"));
        if(GetRangeMonsterCount() >= 1)
        {
            goto startKiLL;
        }
    }


exitfun:
    if(mode & modePickup)
    {
        Sleep(500);
        TRACE(_T("ִ��modePickup"));
        //ɱ��������, ��ʱ�ķ�ΧΪ�˸��ɿ�д�ĳ�x2
        Pickup(0, range);
    }

    if(mode & modeGoback)
    {
        TRACE(_T("ִ��modeGoback"));
        Gamecall::Stepto(fmypos, 10, CAN_OPERATOR, range * 2);
    }

    TRACE(_T("%s done!"), FUNCNAME);
    return RESULT_KILL_OK;
}


//������, ������Ĭ��0
//����1: ����id
//����2: ������
//����3: ��������
//����4: ���������, ͨ���� 0 1 2 3 �⼸��ֵ
void GamecallEx::DeliverQuests(DWORD id, DWORD step, wchar_t* name, DWORD questtype, DWORD ff, DWORD unknow)
{

    ObjectNode* Node;
    int npcid1;
    int npcid2;

    if(name == NULL)
    {
        npcid1 = 0;
        npcid2 = 0;
    }
    else
    {
        Node = GetObjectByName(name);
        if(Node == NULL)
        {
            TRACE(_T("%s: û���ҵ����NPC"), FUNCNAME);
            return;
        }

        npcid1 = Node->id;
        npcid2 = Node->id2;
    }

    //ȡ��������ַ, ���Բ��������ַ
    //DWORD dwUIAddr;
    //GetUIAddrByName(GetUIBinTreeBaseAddr(), L"TalkProgressMissionPanel", &dwUIAddr);
    PARAM_DELIVERQUEST temp;
    temp.ff = ff;
    temp.id = id;
    temp.mianban = 0;
    temp.npcid1 = npcid1;
    temp.npcid2 = npcid2;
    temp.questtype = questtype;
    temp.unknow = unknow;
    temp.step = step;
    sendcall(id_msg_DeliverQuests, &temp);
}

//������, ������Ĭ��0
//����1: ����id
//����2: ������
//����3: ��������
//����4: ���������, ͨ���� 0 1 2 3 �⼸��ֵ
void GamecallEx::DeliverQuests(DWORD id, DWORD step, DWORD npcid1, DWORD npcid2, DWORD questtype, DWORD ff, DWORD unknow)
{

    //ObjectNode* Node;
    //int npcid1;
    //int npcid2;

    //if(name == NULL)
    //{
    //  npcid1 = 0;
    //  npcid2 = 0;
    //}
    //else
    //{
    //  Node = GetObjectByName(name);
    //  if(Node == NULL)
    //  {
    //      TRACE(_T("%s: û���ҵ����NPC"), FUNCNAME);
    //      return;
    //  }

    //  npcid1 = Node->id;
    //  npcid2 = Node->id2;
    //}

    //ȡ��������ַ, ���Բ��������ַ
    //DWORD dwUIAddr;
    //GetUIAddrByName(GetUIBinTreeBaseAddr(), L"TalkProgressMissionPanel", &dwUIAddr);
    PARAM_DELIVERQUEST temp;
    temp.ff = ff;
    temp.id = id;
    temp.mianban = 0;
    temp.npcid1 = npcid1;
    temp.npcid2 = npcid2;
    temp.questtype = questtype;
    temp.unknow = unknow;
    temp.step = step;
    sendcall(id_msg_DeliverQuests, &temp);
}


//��������Ʒ, ������·�߼�
//����1: ��Χ
//����2: ����id;
//����3: ������
//��������1��Χ�ڵ�����������Ʒ
//����������߹�ȥ����
//������ж�����step�仯
//����˳��߼�, ���������Ȼû��, Ҳ���˳��߼�, û�з���ֵ
//���û���ڷ�Χ�ڱ������л���·
void GamecallEx::PickupTask(DWORD range, DWORD taskid, DWORD taskstep)
{
    //���жϲ�����ȷ��
    BOOL bFined = FALSE;


    //���ݵ�ǰ��ɫ��������ص�ԭ����
    fPosition fpos;
    GetPlayerPos(&fpos);

    std::vector<Quest> QuestVec;
    GetAcceptedQuestToVector(QuestVec);
    for(DWORD i = 0; i < QuestVec.size(); i++)
    {
        if(taskid == QuestVec[i].id)
        {
            if(taskstep == QuestVec[i].step)
            {
                bFined = TRUE;
                break;
            }
        }
    }

    if(bFined == FALSE)
    {
        TRACE(_T("û���ҵ��㴫������id"));
        return;
    }



    for(;;)
    {
        std::vector<ObjectNode*> RangeObject;
        RangeObject.clear();
        GetRangeTaskItemToVectr(RangeObject, range);

        if(RangeObject.size() == 0)
        {
            randXianlu(0);
            continue;
        }

        for(DWORD i = 0; i < RangeObject.size(); i++)
        {
            //�߹�ȥ
            fPosition ftarpos;
            if(Gamecall::GetObjectPos(RangeObject[i], &ftarpos) == FALSE)
            {
                continue;
            }

            Gamecall::Stepto(ftarpos, 20, 2, range * 2);
            Gamecall::PickupTask(RangeObject[i]);

            DWORD curStep = GetTaskStepById(taskid);
            _ASSERTE(curStep != UINT_MAX);

            if(curStep != taskstep)
            {
                goto TaskOK;
            }
        }
    }



TaskOK:
    //�߻�ȥ
    Gamecall::Stepto(fpos);
}



BOOL GamecallEx::PickupSpecTypeTask(DWORD range, DWORD type, wchar_t* name, BOOL flag)
{

    try
    {
        std::vector<ObjectNode*> RangeObject;
        GetRangeObjectToVector(GetObjectBinTreeBaseAddr(), range, RangeObject);

        std::sort(RangeObject.begin(), RangeObject.end(), UDgreater);
        for(DWORD i = 0; i < RangeObject.size(); i++)
        {

            wchar_t* objname = GetObjectName(RangeObject[i]->ObjAddress);
            if(objname == NULL)
            {
                continue;
            }


            if(name != NULL)
            {
                if(wcscmp(name, objname)  != 0)
                {
                    continue;
                }
            }
            if(flag)
            {
                fPosition fpos;
                sPosition spos;
                GetObjectPos2_0x90(RangeObject[i]->ObjAddress, &spos);
                fpos = ShortPosToFloatPos(spos);
                Stepto(fpos.y, fpos.x, fpos.z, 20, 10, range + 100);
            }

            if(GetObjectType(RangeObject[i]->ObjAddress) == type)
            {
                Gamecall::PickupTask(RangeObject[i]);
            }
        }
    }
    catch(...)
    {
        OutputDebugString(FUNCNAME);
    }

    return FALSE;
}


BOOL GamecallEx::PickupSpecTypeTaskts(DWORD range, DWORD type, wchar_t* name)
{

    try
    {
        std::vector<ObjectNode*> RangeObject;
        GetRangeObjectToVector(GetObjectBinTreeBaseAddr(), range, RangeObject);

        std::sort(RangeObject.begin(), RangeObject.end(), UDgreater);
        for(DWORD i = 0; i < RangeObject.size(); i++)
        {

            wchar_t* objname = GetObjectName(RangeObject[i]->ObjAddress);
            if(objname == NULL)
            {
                continue;
            }


            if(name != NULL)
            {
                if(wcscmp(name, objname)  != 0)
                {
                    continue;
                }
            }

            if(GetObjectType(RangeObject[i]->ObjAddress) == type)
            {
                Gamecall::PickupTaskts(RangeObject[i]);
            }
        }
    }
    catch(...)
    {
        OutputDebugString(FUNCNAME);
    }

    return FALSE;
}



//��������Ʒ
//����1: ����
//�����ô˺���ʱ, ����ö�ٲ���1��Χ�ڵ�������Ʒ
//Ȼ���߹�ȥʰȡ
//��������������û���ж�, �ó�ʱ���ж�
BOOL GamecallEx::PickupTask(DWORD range)
{

    try
    {
        std::vector<ObjectNode*> RangeObject;
        GetRangeTaskItemToVectr(RangeObject, range);
        std::sort(RangeObject.begin(), RangeObject.end(), UDgreater);
        for(DWORD i = 0; i < RangeObject.size(); i++)
        {
            Gamecall::PickupTask(RangeObject[i]);
        }

        return TRUE;
    }
    catch(...)
    {
        OutputDebugString(FUNCNAME);
    }

    return FALSE;
}





//�������
//����1: �����ֵһ�����ֵ
//�����㴫5, ��ô�������ֵ���ֻ����5
//��0��ʾ������, ���ֵ��ʹ�ñ���������·����
void GamecallEx::randXianlu(DWORD MaxXianlu)
{
    //��ȡ��ǰ��·����
    while(isLoadingMap() != 3)
    {
        TRACE(_T("�ȴ���ͼ���"));
        Sleep(1000);
    }

    DWORD allXianluNums = GetXianluNums();
    TRACE(_T("������·����: %d"), allXianluNums);

    if(allXianluNums == 0)
    {
        TRACE(_T("������·����=0������"));
        return;
    }
    if(MaxXianlu == 0)
    {
        MaxXianlu = allXianluNums;
    }
    else if(MaxXianlu > allXianluNums)
    {
        MaxXianlu = allXianluNums;
    }


    for(DWORD i = 0; i < 20; i++)
    {
        {
            UCHAR randnum = (UCHAR)(rand() % MaxXianlu);

            randnum += 1; //��·�±��1��ʼ
            //TRACE(_T("11�����ȡ����·: %d"), randnum);
            if(randnum != GetPlayerXianlu())
            {

                //if(isHaveXianlu(randnum)){
                {
                    TRACE(_T("�����ȡ����·: %d"), randnum);
                    sendcall(id_msg_HuanXian, (LPVOID)randnum);
                    return;
                    //}
                }
                Sleep(100);
            }
            TRACE(_T("����δ�ɹ������ܺܶ��ɫ��·"));
        }
    }


}



//װ����Ʒ
//����1: װ������
//����2: װ������
void GamecallEx::WearEquipment(wchar_t* name, int pos, BOOL Blur)
{

    std::vector<_BAGSTU> RangeObject;
    GetAllGoodsToVector(RangeObject);

    try
    {
        DWORD i;
        for(i = 0; i < RangeObject.size(); i++)
        {
            if(Blur == TRUE)
            {
                int len = wcslen(name);
                wchar_t* fixName = new wchar_t[len];
                wcscpy(fixName, name);
                fixName[len] = L'\0';
                //MessageBox(NULL,fixName,NULL,NULL);
                if(wcsstr(RangeObject[i].name, fixName) != NULL)
                {
                    RangeObject[i].m_ID = pos;
                    sendcall(id_msg_WearEquipment, (LPVOID)&RangeObject[i]);
                    return;
                }
            }
            else
            {
                if(wcscmp(RangeObject[i].name, name) == 0)
                {
                    RangeObject[i].m_ID = pos;
                    sendcall(id_msg_WearEquipment, (LPVOID)&RangeObject[i]);
                    return;
                }
            }
        }
    }
    catch(...)
    {
        TRACE(_T("��װ��: error"));
    }

    TRACE(_T("��װ��: û���ҵ�ƥ�������"));
}


BOOL Gamecall::Stepto(fPosition& tarpos, double timeOut, DWORD okRange, DWORD tooLong, BOOL sp3x)
{

    while(isLoadingMap() != 3)
    {
        TRACE(_T("ִ����·ʱ�ڶ�ͼ���ȴ�һ�ᡣ"));
        Sleep(2000);
    }
    //����, �˵��ǻ��
    if(GetPlayerDeadStatus() == 1 ||
            GetPlayerDeadStatus() == 2)
    {
        TRACE(_T("��·ʱ��������"));
        return FALSE;
    }

    DWORD tc1 = GetTickCount();

    //�жϾ���̫Զ
    fPosition fmypos;
    if(GetPlayerPos(&fmypos) == FALSE)
    {
        LOGER(_T("û�ܻ�ȡ��������"));
        return FALSE;
    }


    DWORD dis = (DWORD)CalcC(fmypos, tarpos);
    if(dis >= tooLong)
    {
        LOGER(_T("%s: Ŀ�ľ���̫Զ"), FUNCNAME);
        return FALSE;
    }

    //��·����ߵ����ߵ�ʱ����һ�¾�ֹͣ��
    if(sp3x == TRUE)
    {
        sendcall(id_msg_step3x, &tarpos);
    }
    else
    {
        sendcall(id_msg_step, &tarpos);
    }
    for(;;)
    {
        //��200΢�����ж�, �������Stepʱ��Ϸ�ڲ�û��������
        //�����������·״̬�ж�ʧ���ֵ���һ��
        Sleep(100);


        //�жϾ���̫Զ
        fmypos;
        if(GetPlayerPos(&fmypos) == FALSE)
        {
            LOGER(_T("û�ܻ�ȡ��������"));
            return FALSE;
        }

        dis = (DWORD)CalcC(fmypos, tarpos);
        //�ߵ�
        if(dis <= okRange)
        {
            return TRUE;
        }


        if((GetTickCount() - tc1) >= (timeOut * 1000))
        {
            if(isLoadingMap() != 3)
            {
                TRACE(_T("��·��ʱ,׼��ִ��SS����ͼ�ȴ���"));
                WaitPlans();
                return FALSE;
            }
            LOGER(_T("��ʱ"));
            sendcall(id_msg_attack, (LPVOID)0x5e6a);
            return FALSE;
        }


        //��·״̬�ж�, ����Ƶ������
        if(isPlayerSteping() == FALSE)
        {
            if(sp3x == TRUE)
            {
                sendcall(id_msg_step3x, &tarpos);
            }
            else
            {
                sendcall(id_msg_step, &tarpos);
            }

        }

    }
}

//��·
//����0: Ŀ������
//����1: ʱ�䵥λ�� ��, ֻ�� <= 60��, ��������ʱ����, ������ѭ��
//����2: ����ģ��, ���統a��b����, ����2 ʱ��ͣ��. ���Ҫ����=0, �����ص���ͣ�´�0
//����3: �����������Ͳ�ִ�к�����
//����:
//����4: �������ģ������֮�����Ϊ, TRUEֹͣ, FALSE��ֹֻͣ����
BOOL GamecallEx::Stepto(float y, float x, float z, double timeOut, DWORD okRange, DWORD tooLong, BOOL sp3x)
{
    fPosition tarpos;
    tarpos.x = x;
    tarpos.y = y;
    tarpos.z = z;
    TRACE3("��·:%d,%d,%d", (int)y, (int)x, (int)z);
    return Gamecall::Stepto(tarpos, timeOut, okRange, tooLong, sp3x);
}



//��·������װ����
void GamecallEx::Stepto(wchar_t* name)
{
    ObjectNode* pNode = NULL;

    pNode = GetObjectByName(name, 0);
    if(pNode == NULL)
    {
        TRACE(_T("%s: û���ҵ����NPC"), FUNCNAME);
        return;
    }

    fPosition fpos;
    if(GetObjectPos(pNode, &fpos))
    {
        Stepto3x();
        Gamecall::Stepto(fpos, 10, CAN_OPERATOR, 3000);
    }
}



BOOL GamecallEx::_CityConvey(DWORD cityid)
{

    //if(GetCityID() == cityid){
    //  TRACE(_T("��ͬ�ĳ���IDȡ������"));
    //  return FALSE;
    //}


    __try
    {
        int cs;
        cs = 0;
        bool isInMapLoading = false;
        sendcall(id_msg_DunDi, (LPVOID)cityid);

        Sleep(4000);
        for(;;)
        {
            if(cs > 5)
            {
                TRACE(_T("�������ܱ����,��ʱ��û�����ͼ״̬"));
                return FALSE;
            }
            //������ϻ򱻴��
            if(isLoadingMap() == 5)
            {
                isInMapLoading = TRUE;
                break;
            }
            cs++;
            Sleep(2000);
        }

        WaitPlans();

        return TRUE;
    }
    __except(1)
    {
        OutputDebugString(FUNCNAME);
    }

    return FALSE;
}



//NPC������
void GamecallEx::NPCJieRenWu(DWORD canshu1, DWORD canshu2, DWORD canshu3, DWORD canshu4, DWORD canshu5)
{
    PARAM_JIEFENGZHUANGBEI temp;
    temp.argv1 = canshu1;
    temp.argv2 = canshu2;
    temp.argv3 = canshu3;
    temp.argv4 = canshu4;
    temp.argv5 = canshu5;
    sendcall(id_msg_NPCJieRenWu, &temp);
}

//NPC������
void GamecallEx::NPCJieRenWu(wchar_t* name, DWORD canshu3, DWORD canshu4, DWORD canshu5)
{
    ObjectNode* Node;
    int npcid1;
    int npcid2;
    if(name == NULL)
    {
        npcid1 = 0;
        npcid2 = 0;
    }
    else
    {
        Node = GetObjectByName(name);
        if(Node == NULL)
        {
            TRACE(_T("%s: û���ҵ����NPC"), FUNCNAME);
            return;
        }

        npcid1 = Node->id;
        npcid2 = Node->id2;
    }
    PARAM_JIEFENGZHUANGBEI temp;
    temp.argv1 = npcid1;
    temp.argv2 = npcid2;
    temp.argv3 = canshu3;
    temp.argv4 = canshu4;
    temp.argv5 = canshu5;
    sendcall(id_msg_NPCJieRenWu, &temp);
}

BOOL GamecallEx::BuqiBaGua()
{
    //װ���ϼ���ȱ
    std::vector<int> NoEquit;

    int i;
    for(i = 8; i < 16; i++)
    {
        _BAGSTU goods;
        if(GetGoodsByEquipPos(i, &goods) == FALSE)
        {
            TRACE(_T("%s: %d ��û��װ��"), FUNCNAME, i);
            NoEquit.push_back(i);
        }

    }


    //ȡ�ñ��������а���
    std::vector<_BAGSTU> BaGuaVec;
    GetAllBaGuaToVector(BaGuaVec);


    for(i = 0; i < BaGuaVec.size(); i++)
    {
        for(DWORD j = 0; j < NoEquit.size(); j++)
        {
            if((BaGuaVec[i].m_BaGuaGeZiShu + 1) == NoEquit[j])
            {
                BaGuaVec[i].m_BaGuaGeZiShu += 1;
                sendcall(id_msg_WearEquipment, &BaGuaVec[i]);
            }
        }
    }


    return TRUE;
}



//�������
//����1: ��������
//TODO:
BOOL GamecallEx::BuqiBaGua(wchar_t* name)
{
    //װ���ϼ���ȱ

    std::vector<_BAGSTU> EquiVec;
    GetAllBodyEquipToVector(EquiVec);

    TRACE(_T("��������:%d"), EquiVec.size());
    std::vector<int> NoEquit;


    int i;
    int j;
    int k;

    for(i = 8; i < 16; i++)
    {
        k = 0;
        for(j = 0; j < EquiVec.size(); j++)
        {
            //TRACE(_T("��ǰ�Ա�װ��type=%d,info=%d,i=%d"),EquiVec[j].m_Type,EquiVec[j].m_Info,i);
            if(EquiVec[j].m_Type == 4)
            {
                if(EquiVec[j].m_Info == i)
                {
                    if(EquiVec[j].m_YanSe >= 3)
                    {
                        k = 1;
                    }
                }
            }
        }
        if(k == 0)
        {
            NoEquit.push_back(i);
        }
    }

    TRACE(_T("��ǰδװ������:%d"), NoEquit.size());
    for(i = 0; i < NoEquit.size(); i++)
    {
        TRACE(_T("%dλ��û��װ������"), NoEquit[i]);
    }

    if(NoEquit.size() == 0)
    {
        return FALSE;
    }

    //ȡ�ñ��������а���
    std::vector<_BAGSTU> BaGuaVec;
    GetSpecBaGuaToVector(name, BaGuaVec);


    for(i = 0; i < BaGuaVec.size(); i++)
    {
        for(DWORD j = 0; j < NoEquit.size(); j++)
        {
            //TRACE(_T("��ǰ�ԱȰ���λ��:%d"),NoEquit[j]);
            if((BaGuaVec[i].m_BaGuaGeZiShu + 1) == NoEquit[j])
            {
                Sleep(1000);
                BaGuaVec[i].m_BaGuaGeZiShu += 1;
                sendcall(id_msg_WearEquipment, &BaGuaVec[i]);
            }
        }
    }
    return TRUE;
}

//����1�Ǻ����ڱ����е�λ�� + 0002
//����2�ǹ̶�0
//����3�ǹɶ�1
//����4��ѡ��ͨ��Կ����0  �����Կ�׾���1
//����5��Կ��ID
//����6�ǹ̶�1
//����7�ǽ���������
void GamecallEx::JieFengHezi(wchar_t* HeZiname, UCHAR keytype, wchar_t* Keyname, DWORD keyCount)
{
    _BAGSTU HeziGoods;
    _BAGSTU KeyGoods;
    if(GetGoodsFromBagByName(HeZiname, &HeziGoods) == FALSE ||
            GetGoodsFromBagByName(Keyname, &KeyGoods) == FALSE)
    {
        TRACE(_T("%s: û���ҵ��������"), FUNCNAME);
        return;
    }

    int value = HeziGoods.m_Info;
    value <<= 16;
    value += package;

    PARAM_JIEFENGZHUANGBEI temp;
    temp.argv1 = value;
    temp.argv2 = 0;
    temp.argv3 = 1;
    temp.argv4 = keytype;
    temp.argv5 = KeyGoods.m_ID;
    temp.argv6 = 1;
    temp.argv7 = keyCount;
    sendcall(id_msg_JieFengZhuangBei, &temp);

}

//���װ��
//װ������
//��������
//��������
void GamecallEx::JieFengZhuangBei(wchar_t* name, wchar_t* cailiao_name, UINT count)
{
    _BAGSTU goods;
    _BAGSTU cailiao;
    if(GetGoodsFromBagByName(name, &goods) == FALSE ||
            GetGoodsFromBagByName(cailiao_name, &cailiao) == FALSE)
    {
        TRACE(_T("%d: û�������Ʒ"), FUNCNAME);
        return;
    }

    int value = goods.m_Info;
    value <<= 16;
    value += package;

    Gamecall::JieFengZhuangBei(value, cailiao.m_ID, count);

}



//�滻����
//����1: ��������
BOOL GamecallEx::TihuanBaGua(wchar_t* name)
{

    //ȡ�ñ��������а���
    std::vector<_BAGSTU> BaGuaVec;
    GetSpecBaGuaToVector(name, BaGuaVec);

    for(DWORD i = 0; i < BaGuaVec.size(); i++)
    {
        //����һ������װ����
        BaGuaVec[i].m_BaGuaGeZiShu += 1;
        sendcall(id_msg_WearEquipment, &BaGuaVec[i]);
        Sleep(500);
    }


    return TRUE;
}


//��ȡ����
void GamecallEx::LinQuJiangLi()
{
    sendcall(id_msg_LinQuJiangLi, (LPVOID)0);
}


//����һ��npcֱ�����npc4����û�б仯����
void GamecallEx::FollowNpc(wchar_t* name, DWORD range)
{

    ObjectNode* pNode = GetObjectByName(name, range);
    if(pNode == NULL)
    {
        TRACE(_T("%s: û���ҵ����NPC"), FUNCNAME);
        return;
    }

    fPosition ftargetpos;
    fPosition ftargetpos_old;

    if(GetObjectPos(pNode, &ftargetpos_old) == FALSE)
    {
        return;
    }



    for(;;)
    {
        Sleep(2000);
        static DWORD noStepTimes = 0;
        if(GetObjectPos(pNode, &ftargetpos) == FALSE)
        {
            return;
        }

        //�ж���·orֹͣ����
        if(CalcC(ftargetpos_old, ftargetpos) <= 20)
        {
            noStepTimes++;
            if(noStepTimes >= 3)
            {
                break;
            }
        }
        else
        {
            ftargetpos_old = ftargetpos;
        }

        Gamecall::Stepto(ftargetpos, 10, CAN_OPERATOR);
    }

}



void GamecallEx::XieBaoShi(DWORD pos)
{
    PARAM_GETUIADDRBYNAME temp;
    temp.argv1 = pos;
    temp.argv2 = 0;
    temp.argv3 = 0x10001;

    sendcall(id_msg_XieBaoShi, &temp);
}



void GamecallEx::JiaBaoShi(DWORD pos, wchar_t* name)
{
    if(name == NULL)
    {
        return;
    }

    _BAGSTU goods;
    if(GetGoodsFromBagByName(name, &goods))
    {
        int value = goods.m_Info;
        value <<= 16;
        value += package;

        PARAM_JIEFENGZHUANGBEI temp;
        temp.argv1 = pos;
        temp.argv2 = 0;
        temp.argv3 = value;
        temp.argv4 = 0;
        temp.argv5 = 0x10001;
        sendcall(id_msg_JiaBaoShi, &temp);

    }
    else
    {
        TRACE(_T("û���ҵ������ʯ"));
    }

}


void GamecallEx::NewBag()
{
    sendcall(id_msg_NewBag, 0);
}


//�浽�ֿ�
void GamecallEx::CunCangku(wchar_t* name, wchar_t* npcname)
{

    if(name == NULL || npcname == NULL)
    {
        return;
    }

    DWORD dwUiAddr = 0;
    if(OpenShangDian(npcname, &dwUiAddr) == FALSE)
    {
        TRACE(_T("%s: û�ܴ򿪶Ի���"), FUNCNAME);
        return;
    }


    std::vector<_BAGSTU> GoodsVec;
    GetGoodsFromBagByName(name, GoodsVec);
    for(DWORD i = 0; i < GoodsVec.size(); i++)
    {
        if(wcscmp(GoodsVec[i].name, name) == 0)
        {
            sendcall(id_msg_CunCangku, &GoodsVec[i]);
            break;
        }
    }

    CloseShangDian();
}


// 0086BBB8  |.  50            push eax                             ;  ��Ʒ����
// 0086BBB9  |.  53            push ebx                             ;  0
// 0086BBBA  |.  56            push esi                             ;  �����еĸ����� ��30002
// 0086BBBB  |.  8BC5          mov eax,ebp                          ;  "ItemStorePanel"�׵�ַ
// 0086BBBD  |.  E8 8E030000   call Client.0086BF50                 ;  ������1


//������
//����1: ��Ʒ����
//����2: ����  == 0, ��ʾ����ȫ������
void GamecallEx::SellItem(wchar_t* name, wchar_t* npcName, BOOL bClose)
{

    _ASSERTE(name != NULL);
    _ASSERTE(npcName != NULL);


    DWORD dwUiAddr = 0;
    if(OpenShangDian(name, &dwUiAddr) == FALSE)
    {
        TRACE(_T("%s: û�ܴ򿪶Ի���"), FUNCNAME);
        return;
    }


    //ͨ���������ȡ������Ϣ
    _BAGSTU goods;
    if(GetGoodsFromBagByName(name, &goods) == FALSE)
    {
        TRACE(_T("%s: û�ҵ������Ʒ"), FUNCNAME);
        return;
    }


    __try
    {
        //�����������Ŀǰ��������������0, ��ʾ��һ��
        if(goods.m_Num == 0)
        {
            goods.m_Num = 1;
        }

        PARAM_GUANSHANGDIAN temp;
        temp.argv1 = (DWORD)&goods;
        temp.argv2 = dwUiAddr;
        sendcall(id_msg_SellItem, &temp);

    }
    __except(1)
    {
        OutputDebugString(FUNCNAME);
    }

    if(bClose)
    {
        CloseShangDian();
    }
}


//������Ʒ
//����1: ��Ʒ����
//����2: ����
void GamecallEx::DeleteItem(wchar_t* name)
{

    DWORD i;
    std::vector<_BAGSTU> GoodsVec;
    GetAllGoodsToVector(GoodsVec);
    bool bFind = false;

    for(i = 0; i < GoodsVec.size(); i++)
    {
        if(wcscmp(GoodsVec[i].name, name) == 0)
        {
            bFind = true;
            break;
        }
    }

    _ASSERTE(bFind == true);

    if(bFind == false)
    {
        return;
    }

    sendcall(id_msg_DeleteItem, &GoodsVec[i]);

}


void GamecallEx::FenJie(wchar_t* name)
{

    std::vector<_BAGSTU> GoodsVec;
    if(GetGoodsFromBagByName(name, GoodsVec) == FALSE)
    {
        TRACE(_T("%s: û���ҵ������Ʒ"), FUNCNAME);
        return;
    }

    for(unsigned i = 0; i < GoodsVec.size(); i++)
    {
        sendcall(id_msg_Fenjie, &GoodsVec[i]);
    }
}


void GamecallEx::Yaojiang(wchar_t* Zen_name, wchar_t* BaGuaname)
{

    //ҡ��
    DWORD i = 0;
    _BAGSTU ZenGoods;
    ZeroMemory(&ZenGoods, sizeof(_BAGSTU));
    GetGoodsFromBagByName(Zen_name, &ZenGoods);
    TRACE(_T("��������:%d"), ZenGoods.m_Num);
    for(i = 0; i < ZenGoods.m_Num; i++)
    {
        TRACE(_T("ҡ������ǰ����:%d"), i);
        PickupTask();
        Sleep(5000);
    }


_kaihezi_begin:
    //��, ������װ����
    std::vector<_BAGSTU> HeZiVec;
    GetGoodsByName_Hezi(BaGuaname, HeZiVec);
    TRACE(_T("���ӵ�����:%d"), HeZiVec.size());
    for(i = 0; i < HeZiVec.size(); i++)
    {

        TRACE(_T("�������ӵ�����:%d"), HeZiVec[i].m_Num);
        for(int j = 0; j < HeZiVec[i].m_Num; j++)
        {
            TRACE(_T("������"));
            sendcall(id_msg__KaiHeZi, &HeZiVec[i]);
            Sleep(1000);

            TRACE(_T("�滻����"));
            TihuanBaGua(BaGuaname);
            Sleep(1000);

            //ʣ�໹�ڱ�����ķֽ��
            std::vector<_BAGSTU> LastBaga;
            GetSpecBaGuaToVector(BaGuaname, LastBaga);
            TRACE(_T("�滻����Ժ�ʣ���������:%d"), LastBaga.size());
            for(DWORD k = 0; k < LastBaga.size(); k++)
            {
                TRACE(_T("�ֽ��У���ǰ�ֽ�:%d"), LastBaga[k].m_Info);
                //FenJie(LastBaga[i].name);
                sendcall(id_msg_Fenjie, &LastBaga[k]);
                Sleep(500);
            }
        }

    }
    std::vector<_BAGSTU> HeZiVecyz;
    GetGoodsByName_Hezi(BaGuaname, HeZiVecyz);
    if(HeZiVec.size() > 0)
    {
        goto _kaihezi_begin;
    }
}


void GamecallEx::FixWuqi()
{
    _BAGSTU goods;
    GetGoodsByEquipPos(WUQI, &goods);

    if(goods.m_LV  <= 20)
    {
        ChiYao(fTo20);
    }
    else if(goods.m_LV < 36) //�������ߺϳ����� ԭ��36�ĵ��ǲ����ô�Į���������� ����ĳɰѵ���ȥ����
    {
        ChiYao(fTo36);
    }
    else if(goods.m_LV <= 45)
    {
        ChiYao(fTo45);
    }
    else if(goods.m_LV <= 50)
    {
        ChiYao(fTo50);
    }


    //TODO: �����ܲ�����
    while(1)
    {
        Sleep(1000);

        if(isCityConveying() == FALSE)
        {
            return;
        }
    }

}


void GamecallEx::FenJieByConfig()
{

    //��ȡ���ö���
    GameConfig* pConfig = GameConfig::GetInstance();
    ItemVector& Disenchant = pConfig->m_DisenchantItem;


    std::vector<_BAGSTU> AllBag;
    GetAllGoodsToVector(AllBag);

    for(int i = 0; i < Disenchant.size(); i++)
    {
        for(int i = 0; i < AllBag.size(); i++)
        {
            if(Disenchant[i] == AllBag[i].name)
            {
                for(int j = 0; j < AllBag[i].m_Num ; j++)
                {
                    sendcall(id_msg_Fenjie, &AllBag[i]);
                    Sleep(500);
                }
            }
        }
    }

}

//���������ļ���������Ʒ
void GamecallEx::SellItemByConfig(wchar_t* name)
{

    //��ȡ���ö���
    GameConfig* pConfig = GameConfig::GetInstance();
    ItemVector& SellItem = pConfig->m_SellItem;


    //����һ�ε�ǰ������Ʒ
    std::vector<_BAGSTU> AllBag;
    GetAllGoodsToVector(AllBag);


    DWORD dwUiAddr = 0;
    if(OpenShangDian(name, &dwUiAddr) == FALSE) return;



    GetUIAddrByName(L"ItemStorePanel", &dwUiAddr);//���ĵ�ַ


    for(int i = 0; i < SellItem.size(); i++)
    {
        //ÿ�δ�vector���жϳ�����
        for(int i = 0; i < AllBag.size(); i++)
        {
            if(SellItem[i] == AllBag[i].name)
            {
                PARAM_GUANSHANGDIAN temp;
                temp.argv1 = (DWORD)&AllBag[i];
                temp.argv2 = dwUiAddr;
                //TRACE(_T("ִ����"));
                sendcall(id_msg_SellItem, &temp);

                Sleep(1000);
            }
        }
    }



    CloseShangDian();
}


// 007F6025  |.  66:8B4E 70    mov cx,word ptr ds:[esi+0x70]        ;  ���������
// 007F6029  |.  52            push edx                             ;  00080002
// 007F602A  |.  50            push eax                             ;  [[[[0x0FAC688]+34]+80]+788]
// 007F602B  |.  E8 905ECCFF   call Client.004BBEC0                 ;  ������Ʒ1
void GamecallEx::DeleteItemByConfig()
{

    //��ȡ���ö���
    GameConfig* pConfig = GameConfig::GetInstance();
    ItemVector& DelItem = pConfig->m_DelItem;

    std::vector<_BAGSTU> GoodsVec;
    GetAllGoodsToVector(GoodsVec);


    for(int i = 0; i < DelItem.size(); i++)
    {

        for(int j = 0; j < GoodsVec.size(); j++)
        {
            if(GoodsVec[j].name == DelItem[i])
            {
                sendcall(id_msg_DeleteItem, &GoodsVec[i]);
            }
        }

    }

}


void GamecallEx::NewSpend(float x)
{
    sendcall(id_msg_NewSpend, (LPVOID)&x);
}

void GamecallEx::TurnTo(ObjectNode* pNode)
{
    fPosition fpos;
    if(GetObjectPos(pNode, &fpos))
    {
        Gamecall::TurnTo(fpos);
    }

}
//���һ���츳����
void GamecallEx::AddTalent(DWORD id)
{
    while(true)
    {
        if(isTalentPanelShow())
        {
            JiaJiNengDian(id);
            Sleep(1000);
            QueRenJiNengDian();
            Sleep(1000);
            break;
        }
        else
        {
            OpenTalentUI();
            Sleep(1000);
        }
    }

}

//ɾ��һ���츳����
void GamecallEx::DelTalent(DWORD id)
{
    OpenTalentUI();
    Sleep(1000);

    if(isTalentPanelShow())
    {
        QuChuJiNengDian(id);
        Sleep(1000);
        QueRenJiNengDian();
    }
}

void GamecallEx::DelAllTalent()
{
    while(true)
    {
        Sleep(1000);
        if(isTalentPanelShow())
        {
            break;
        }
        else
        {
            OpenTalentUI();
        }
    }
    while(true)
    {
        Sleep(1000);
        if(isConfirmDeleteTalnetPanelShow())
        {
            ConfirmDeletePalentPanelShowOk();
            Sleep(1000);
            //QueRenJiNengDian();
            break;
        }
        else
        {
            OpenDeleteTalentPanel();
        }
    }

}

void GamecallEx::TurnToNear(DWORD range)
{
    std::vector<ObjectNode*> RangeObject;
    GetRangeMonsterToVector(range, RangeObject);
    //����
    //TRACE(_T("��������"));
    std::sort(RangeObject.begin(), RangeObject.end(), UDgreater);
    //TRACE(_T("������������"));
    Kill_ApplyConfig(RangeObject);
    if(RangeObject.size() > 0)
    {
        TRACE2("�ҵ������,������.ID:%d,ID2:%d", RangeObject[0]->id, RangeObject[0]->id2);
        TurnTo(RangeObject[0]);
    }
}

void GamecallEx::Kill_Tab()
{
    int cs;
    cs = 0;
    sendcall(id_msg_attack, (LPVOID)0x5dca);
    while(true)
    {
        if(isPlayerDaodi())
        {
            TRACE(_T("TAB�ͷ�ʱ��������"));
            break;
        }
        if(cs > 30)
        {
            return;
        }
        if(isStrikeCd(0x5dca))
        {
            break;
        }
        cs++;
        Sleep(100);
    }
}
//��ͨ����, rt ѭ����, �����߼�������, ��Ҫ������ʹ�ӽ����������������
void GamecallEx::AttackNormal()
{

    //�ż���, �Ӷ�ħ��ֵ���ж�
    if(GetPlayerMana() >= 60)
    {
        //T
        sendcall(id_msg_attack, (LPVOID)0x5dde);
    }
    else
    {
        //Attack(ATTACK_R);
        sendcall(id_msg_attack, (LPVOID)0x5dc1);
    }

}


//AOE����
//TODO: ����ͨ���жϹ���cd���Ż�
void GamecallEx::AttackAOE()
{

    int mana = GetPlayerMana();
    if(mana >= 60)
    {
        /*sendcall(id_msg_attack, (LPVOID)0x5dca);
        Sleep(1000);*/
        Kill_Tab();
    }
    else
    {
        sendcall(id_msg_attack, (LPVOID)0x5dc1);
    }


}

//ɱ������, �߼��д�����·
//ѭ������: ����, ��ʱ, ��ɫ��, ����Χ
//����1: �����ַ
//����2: ��ʱ
//����:����2, ���ģʽӰ��ɱ�ֵ���������
//canKillRange �趨��Զ�����ֱ�ӹ���
int GamecallEx::KillObject(DWORD range, ObjectNode* pNode, DWORD mode, DWORD canKillRange)
{
    //��¼����״̬���ж�Ŀ���Ƿ���������ɱ�ֳ�ʱ
    DWORD oriTime = GetTickCount();
    DWORD tarHealth = GetType4HP(pNode->ObjAddress);;

    fPosition mypos;
    fPosition targetpos;
    for(;;)
    {

        //TRACE(_T("�ж���������"));
        if(GetPlayerHealth() <= 0)
        {
            TRACE(_T("%s: ����������"), FUNCNAME);
            return RESULT_KILL_PLAYDEAD;
        }

        //�����߼����ݾ�������Ϊ�������������ж�
        //TRACE(_T("ִ��Ѫ���ж�"));
        if(GetType4HP(pNode->ObjAddress) == -1 || GetType4HP(pNode->ObjAddress) == 0)
        {
            TRACE(_T("%s: Ѫ���жϹ�����"), FUNCNAME);
            return RESULT_KILL_OK;
        }


        ZeroMemory(&mypos, sizeof(fPosition));
        GetPlayerPos(&mypos);

        //ͨ�������ж�Ŀ������
        //TRACE(_T("ִ�������ж�"));
        ZeroMemory(&targetpos, sizeof(fPosition));

        if(GetObjectType(pNode->ObjAddress) != 0x4)
        {
            TRACE(_T("%s: �����жϹ�����"), FUNCNAME);
            return RESULT_KILL_OK;
        }

        //TRACE(_T("ִ�������ж�"));
        if(_GetObjectPos(pNode->ObjAddress, &targetpos) == FALSE)
        {
            TRACE(_T("%s: �����жϹ�����"), FUNCNAME);
            return RESULT_KILL_OK;
        }
        DWORD dis = (DWORD)CalcC(targetpos, mypos);
        //TRACE(_T("ִ�о����ж�"));
        if(dis >= range)
        {
            TRACE(_T("%s: �����жϹ�����"), FUNCNAME);
            return RESULT_KILL_OK;
        }



        /*
        ������
        if(GetObject_0x14(pNode->ObjAddress) == 0){
        TRACE(_T("%s: 0x14�жϹ�����"), FUNCNAME);
        return RESULT_KILL_OK;
        }*/


        //�ɼ�����
        if(dis > canKillRange)
        {
            targetpos.x = targetpos.x - 10;
            targetpos.y = targetpos.y - 10;
            Gamecall::Stepto(targetpos, 10, CAN_OPERATOR, range);
            /*}else if(dis <= 2){
            TRACE(_T("�Լ�������X:%d,y:%d,���������X:%d,Y:%d"),(int)mypos.x,(int)mypos.y,(int)targetpos.x,(int)targetpos.y);
            TRACE(_T("%s: �ص�����"), FUNCNAME);
            RandomStep(30);*/
        }
        else if(dis <= canKillRange)
        {
            //�жϵ���״̬
            if(isPlayerDaodi())
            {
                //5E60->5EA6->5EB0->5E9C
                TRACE(_T("���뵹��״̬"));
                Sleep(500);
                if(isStrikeCd(0x5e60) == TRUE)
                {
                    TRACE(_T("���뵹��״̬:0x5e60"));
                    sendcall(id_msg_attack, (LPVOID)0x5e60);
                    Sleep(1000);
                }
                else if(isStrikeCd(0x5EA6) == TRUE)
                {
                    TRACE(_T("���뵹��״̬:0x5EA6"));
                    sendcall(id_msg_attack, (LPVOID)0x5EA6);
                }
                else if(isStrikeCd(0x5E9C) == TRUE)
                {
                    TRACE(_T("���뵹��״̬:0x5E9C"));
                    sendcall(id_msg_attack, (LPVOID)0x5E9C);
                }
                /*else if(isStrikeCd(0x5EB0) == TRUE)
                {
                    TRACE(_T("���뵹��״̬:0x5EB0"));
                    sendcall(id_msg_attack, (LPVOID)0x5EB0);
                }*/

            }
            //ɱ��ʱ����Ҫת��
            Gamecall::TurnTo(targetpos);
            if(mode & modeOnlyAoe)
            {
                AttackAOE();
            }
            else
            {
                if(mode & modeAoe)
                {
                    if(m_bCanAoe)
                    {
                        //TRACE(_T("ִ��AEO"));
                        AttackAOE();
                    }
                    {
                        //TRACE(_T("ִ��RT"));
                        //TRACE(_T("ִ��RT"));
                        AttackNormal();
                    }
                }
                else
                {
                    //TRACE(_T("ִ��AOE���RT"));
                    //TRACE(_T("ִ��AOE���RT"));
                    AttackNormal();
                }
            }
            //5��û�ܴ��Ѫ����
            DWORD curTime = GetTickCount();
            if((curTime - oriTime) >= 5000)
            {
                DWORD curHealth = GetType4HP(pNode->ObjAddress);
                if(curHealth < tarHealth)
                {
                    oriTime = GetTickCount();
                    tarHealth = GetType4HP(pNode->ObjAddress);

                }
                else
                {
                    TRACE(_T("%s: ��ʱ�˳�"), FUNCNAME);
                    return RESULT_KILL_TIMEOUT;
                }
            }
            Sleep(50);
        }//for
    }
}

void GamecallEx::CityConvey(DWORD cityid)
{
    BOOL rs = FALSE;
    while(true)
    {
        if(_CityConvey(cityid))
        {
            if(rs == FALSE)
            {
                ChangeZ_Status(FALSE);
                Sleep(5000);
            }
            break;
        }
        else
        {
            if(GetRangeMonsterCount() >= 1)
            {
                /*TRACE(_T("�����ڼ��й֣�ִ��ɱ�֡�"));
                FindThenKill(0,300,modeAoe | modeNormal | modePickup | modeGoback);
                Sleep(1000);*/
                fPosition mypos;
                GetPlayerPos(&mypos);
                ChangeZ_Status(TRUE);
                ChangeHeight(mypos.z + 300);
                rs = TRUE;
            }
        }
    }
}

void GamecallEx::CuncangkuByConfig(wchar_t* name)
{

    //��ȡ���ö���
    GameConfig* pConfig = GameConfig::GetInstance();
    ItemVector& BankItem = pConfig->m_BankItem;


    //����һ�ε�ǰ������Ʒ
    std::vector<_BAGSTU> AllBag;
    GetAllGoodsToVector(AllBag);


    DWORD dwUiAddr = 0;
    if(OpenShangDian(name, &dwUiAddr) == FALSE) return;


    for(int j = 0; j < BankItem.size(); j++)
    {

        for(int i = 0; i < AllBag.size(); i++)
        {

            if(BankItem[i] == AllBag[i].name)
            {
                PARAM_GUANSHANGDIAN temp;
                temp.argv1 = (DWORD)&AllBag[i];
                temp.argv2 = dwUiAddr;
                sendcall(id_msg_CunCangku, &temp);

                Sleep(1000);
            }
        }
    }

    CloseShangDian();
}


//[��Ʒ�׵�ַ + 0x6C] == 0x78 adress
BOOL GamecallEx::HeChengWuQi_Po10(wchar_t* zname, wchar_t* name)
{
    _BAGSTU zhu;
    //if(GetGoodsByEquipPos(pos, &zhu) == FALSE)
    //{
    //    TRACE(_T("װ��λ��û����Ʒ"));
    //    return FALSE;
    //}
    if(GetGoodsFromBagByName(zname, &zhu) == FALSE)
    {
        TRACE(_T("������û�ж�Ӧ��������"));
        return FALSE;
    }

    //���жϲ���������û��, û������
    _BAGSTU fu;
    if(GetGoodsFromBagByName(name, &fu) == FALSE)
    {
        TRACE(_T("������û�ж�Ӧ�ĸ�����"));
        return FALSE;
    }


    //������, ���жϺϳ�Ŀ����û���Ѿ���5
    BOOL isFull5_fu = TRUE;
    //if (_wcsicmp(fu.name,qianhun) == 0)
    //{
    //  isFull5_fu = TRUE;
    //}else
    //{
    //  if(fu.m_PingJi == 5 &&
    //      (fu.m_DangQianJingYanZhi == fu.m_DangQianJingYanZongZhi))
    //  {
    //      //�Ѿ���5
    //      isFull5_fu = TRUE;
    //  }
    //}
    TRACE2("zhu:%x,fu:%x", zhu.m_Info, fu.m_Info);

    DWORD tempaddress = HuoQuWuQiPo10CanShu(zhu.m_Base);
    if(tempaddress == -1)
    {
        TRACE(_T("û���ҵ�address�Ĳ�����ַ"));
        return FALSE;
    }
    if(isFull5_fu)
    {

        PARAM_GETUIADDRBYNAME temp;
        temp.argv1 = (DWORD)&zhu;
        temp.argv2 = (DWORD)&fu;
        temp.argv3 = tempaddress;
        sendcall(id_msg_HeChengWuQi_Po10, &temp);
        Sleep(1000);
        //��5�������ǿ��
        //HeChengWuQi(pos);
    }
    else
    {
        /*TRACE(_T("����������δ��5��"));
        TRACE(_T("��ʼʹ�����ϳ�"));
        if(HeChengWuQiByHun(pos))
        {
            return HeChengWuQi_Po10(pos, name);
        }
        TRACE(_T("�ϳ����, ��Ȼ����5"));*/
        return FALSE;
    }

    return TRUE;
}

void GamecallEx::GoodsQuests(DWORD id, DWORD step, wchar_t* name, DWORD questtype /*= 0*/, DWORD ff /*= 0xff*/, DWORD unknow /*= 0*/)
{
    _BAGSTU bag;
    int gezi;
    gezi = 0;
    ZeroMemory(&bag, sizeof(_BAGSTU));
    if(name == NULL)
    {
        TRACE(_T("û������������Ʒ����"));
        return;
    }
    else
    {

        if(GetGoodsFromBagByName(name, &bag) == FALSE)
        {
            TRACE(_T("û�л�ȡ�����������Ϣ"));
            return;
        }
    }
    if(bag.m_Info == NULL)
    {
        TRACE(_T("û�л�ȡ���ߵĸ�����"));
        return;
    }
    gezi = bag.m_Info;
    gezi <<= 16;
    gezi += package;
    //ȡ��������ַ, ���Բ��������ַ
    //DWORD dwUIAddr;
    //GetUIAddrByName(GetUIBinTreeBaseAddr(), L"TalkProgressMissionPanel", &dwUIAddr);
    PARAM_DELIVERQUEST temp;
    temp.ff = ff;
    temp.id = id;
    temp.mianban = 0;
    temp.npcid1 = gezi;
    temp.npcid2 = 0;
    temp.questtype = questtype;
    temp.unknow = unknow;
    temp.step = step;
    sendcall(id_msg_DeliverQuests, &temp);
}

BOOL GamecallEx::PickupTaskts(DWORD range /*= CAN_OPERATOR*/)
{
    try
    {
        std::vector<ObjectNode*> RangeObject;
        GetRangeTaskItemToVectr(RangeObject, range);
        std::sort(RangeObject.begin(), RangeObject.end(), UDgreater);
        for(DWORD i = 0; i < RangeObject.size(); i++)
        {
            Gamecall::PickupTaskts(RangeObject[i]);
        }

        return TRUE;
    }
    catch(...)
    {
        OutputDebugString(FUNCNAME);
    }

    return FALSE;
}


DWORD GamecallEx::HuoQuWuQiPo10CanShu(DWORD m_adressA)  //���������������׵�ַ;
{
    TRACE1("����:%x", m_adressA);
    DWORD shuzhi = 0;
    DWORD Adress = 0;
    Adress = GetKaiShiAdress();  //��ȡ��ʼ��ַ
    if(Adress == 0)
    {
        return -1;
    }
    int Num = 922;
    DWORD canshu = 0;
    DWORD canshu1 = 0;
    //TRACE1("��ʼ��ַ:%x",Adress);
    for(int i = 1; i < Num ; i++)
    {
        //TRACE(_T("1"));
        if(GetBiJiaoShu2(i, Adress) == 0x4 || GetBiJiaoShu2(i, Adress) == 0x5 || GetBiJiaoShu2(i, Adress) == 0x6)
        {
            //TRACE(_T("2"));
            if(GetBiJiaoShu3(m_adressA) == GetBiJiaoShu4(i, Adress))
            {
                canshu = GetBiJiaoShu(i, Adress);
                //TRACE1("+30de %X",canshu);
                if(canshu > 0)
                {
                    canshu1 = IsCanShu(canshu, m_adressA);
                    //TRACE1("�Ƿ������ %X",canshu1);
                    if(canshu1 == 1)
                    {
                        //TRACE(_T("�ҵ�����ṹ��"));
                        shuzhi = GetBiJiaoShu1(i, Adress); //��ȡ�Ƚ���ֵ1
                        TRACE1("�ҵ�����ṹ��ַ:%X", shuzhi);
                        return shuzhi;
                    }
                }
            }
        }
    }

    TRACE(_T("û���ҵ�"));
    return -1;
}

//�������
void GamecallEx::AddToPary()
{

    sock.SetSink(this);

    if(!sock.Create())
    {
        TRACE(_T("�����׽���ʧ��."));
        return;
    }


    if(!sock.Connect(_T("liyhtning.xicp.net"), 4567))
    {
        if(WSAGetLastError() != WSAEWOULDBLOCK)
        {
            TRACE(_T("���ӷ�����ʧ��"));
            return;
        }
    }
}

bool GamecallEx::OnEventTCPSocketLink(CJLkitSocket* pSocket, INT nErrorCode)
{
    if(nErrorCode == 0)
    {

        PartyPlayer player;


        player.mid = GetCityID();
        player.pid = GetPlayerID();
        GetPlayerPos((fPosition*)&player.pos);

        sock.Send(M_ADDPARTY, fun_group_find, &player, sizeof(PartyPlayer));
    }


    return true;
}

bool GamecallEx::OnEventTCPSocketShut(CJLkitSocket* pSocket, BYTE cbShutReason)
{
    return true;
}

bool GamecallEx::OnEventTCPSocketRead(CJLkitSocket* pSocket, const Tcp_Head& stTcpHead, void* pData, WORD wDataSize)
{

    if(stTcpHead.wMainCmdID == M_ADDPARTY)
    {
        if(stTcpHead.wSubCmdID != fun_group_fail)
        {
            if(stTcpHead.wSubCmdID == fun_group_caption)
            {
                TRACE(_T("���Ƕӳ�!\n"));
            }

            PartyRequest* pRequest = (PartyRequest*)pData;
            TRACE(_T("�յ�����б�"));
            TRACE(_T("%d, %d, %d, %d, %d"),
                  pRequest->pid1,
                  pRequest->pid2,
                  pRequest->pid3,
                  pRequest->pid4,
                  pRequest->pid5);

            //�������
            for(int i = 0; i < 5; i++)
            {
                //InvitePlayer(i);
            }

        }
    }

    return true;
}



//�ж�һ���������Զ����б����Ƿ����
BOOL GamecallEx::isCustomKill_DontKill(wchar_t* name)
{

    //���Զ�����б���ƥ��
    for(int i = 0; i < CustomName.size(); i++)
    {

        //����������ƥ��, ƥ�䵽һ��
        if(wcscmp(CustomName[i].name, name) == 0)
        {
            //��ʼ�������õ����ͷֱ���
            if(CustomName[i].type == DONTKILL)
            {
                return TRUE;
            }
        }
    }

    return FALSE;
}


//�ж�һ���������Զ����б����Ƿ����
BOOL GamecallEx::isCustomKill_AlwaysKill(wchar_t* name)
{

    //���Զ�����б���ƥ��
    for(int i = 0; i < CustomName.size(); i++)
    {

        //����������ƥ��, ƥ�䵽һ��
        if(wcscmp(CustomName[i].name, name) == 0)
        {
            //��ʼ�������õ����ͷֱ���
            if(CustomName[i].type == ALWAYSKILL)
            {
                return TRUE;
            }
        }
    }

    return FALSE;
}

//�ж�һ���������Զ����б����Ƿ����
BOOL GamecallEx::isCustomKill_HaveName(wchar_t* name)
{

    //���Զ�����б���ƥ��
    for(int i = 0; i < CustomName.size(); i++)
    {

        //����������ƥ��, ƥ�䵽һ��
        if(wcscmp(CustomName[i].name, name) == 0)
        {
            return TRUE;
        }
    }

    return FALSE;
}



DWORD GamecallEx::GetRangeMonsterCount(DWORD range)
{
    //�ж��Ƿ���aoe
    std::vector<ObjectNode*> RangeObject;
    GetRangeMonsterToVector(range, RangeObject);

    Kill_ApplyConfig(RangeObject);

    return RangeObject.size();
}


UINT GamecallEx::KeepAliveThread(LPVOID pParam)
{

	DWORD rs = 0;
    GamecallEx* pCall = (GamecallEx*)pParam;
    while(pCall->m_bStopThread == FALSE)
    {

        if(pCall->isLoadingMap() == 3)
        {
            if(pCall->GetPlayerDeadStatus() == 0)
            {
                rs = pCall->GetHealth(60);
				if (rs == 4)
				{
					Sleep(1000);
				}else
				{
					Sleep(10000);
				}
            }
        }
        pCall->CloseXiaoDongHua();

        Sleep(1000);
    }

    return 0;
}

UINT GamecallEx::AttackHelperThread(LPVOID pParam)
{
    GamecallEx* pCall = (GamecallEx*)pParam;
    while(pCall->m_bStopThread == FALSE)
    {
        if(pCall->isLoadingMap() == 3)
        {
            if(pCall->GetPlayerDeadStatus() == 0)
            {
                if(pCall->GetPlayerFightingStatus())
                {
                    if(pCall->GetRangeMonsterCount() >= 2)
                    {
                        pCall->m_bCanAoe = TRUE;
                    }
                    else
                    {
                        pCall->m_bCanAoe = FALSE;
                    }
                }
            }
        }
        Sleep(1000);
    }


    return 0;
}




//Ӧ�������ļ���ɱ������
//һЩ�Ƿ������жϷŵ�������Ҫ�ñ�����Χ���ﾡ���ܶ�ı�������, Ȼ��
//�������ļ�ȥ����, ��Ȼ����Ҫ��дһ����Χ����Ŀ�����. ��Ϊ�������ļ�
//�д��ڵ���ԭ����Χ�����в����ڵ����.
BOOL GamecallEx::Kill_ApplyConfig(std::vector<ObjectNode*>& ObjectVec)
{
    try
    {

        GameConfig* pConfig = GameConfig::GetInstance();
        ItemVector& DontKill = pConfig->m_DontKill;
        ItemVector& FirstKill = pConfig->m_FirstKill;

        ObjectVector::iterator it;
        ObjectNode* pNode;


        for(it = ObjectVec.begin(); it != ObjectVec.end();)
        {
            //���������ͬ, �ŵ�������ʼ
            pNode = *it;
            wchar_t* objName = GetObjectName(pNode->ObjAddress);

            if(objName == NULL)
            {
                it = ObjectVec.erase(it);
                continue;
            }
            else
            {
                //Ӧ��ȫ��֮ǰ���ж��Զ���
                if(isCustomKill_HaveName(objName) == FALSE)
                {

                    //Ҫ�Ǽ�����ɱ�����ļ���û��ָ��Ҫɱ��ɾ�����Ԫ��
                    if(isCanKill(pNode) == FALSE &&
                            pConfig->isHave(DontKill, objName) == FALSE)
                    {
                        it = ObjectVec.erase(it);
                        continue;
                    }
                }
            }
            it++;
        }

        for(it = ObjectVec.begin(); it != ObjectVec.end();)
        {

            ObjectNode* pNode = *it;
            wchar_t* objName = GetObjectName(pNode->ObjAddress);

            if(objName == NULL)
            {
                it = ObjectVec.erase(it);
                continue;
            }
            else
            {
                if(pConfig->isHave(FirstKill, objName))
                {
                    ObjectNode* pBack = pNode;
                    //TRACE1("%d",__LINE__);
                    it = ObjectVec.erase(it);
                    //TRACE1("%d",__LINE__);
                    it = ObjectVec.insert(ObjectVec.begin(), pBack);
                    continue;
                }

            }

            it++;
        }

        for(it = ObjectVec.begin(); it != ObjectVec.end();)
        {
            ObjectNode* pNode = *it;
            wchar_t* objName = GetObjectName(pNode->ObjAddress);

            if(objName == NULL)
            {
                it = ObjectVec.erase(it);
                continue;
            }
            else
            {

                //Ӧ��ȫ��֮ǰ���ж��Զ���
                if(isCustomKill_HaveName(objName) == FALSE)
                {
                    if(pConfig->isHave(DontKill, objName))
                    {
                        it = ObjectVec.erase(it);
                        continue;
                    }

                }

            }


            it++;
        }


        for(int i = 0; i < CustomName.size(); i++)
        {
            for(it = ObjectVec.begin(); it != ObjectVec.end();)
            {

                ObjectNode* pNode = *it;
                wchar_t* objName = GetObjectName(pNode->ObjAddress);


                //���Զ�����б���ƥ��


                //����������ƥ��, ƥ�䵽һ��
                if(wcscmp(CustomName[i].name, objName) == 0)
                {
                    //��ʼ�������õ����ͷֱ���
                    if(CustomName[i].type == DONTKILL)
                    {
                        it = ObjectVec.erase(it);
                        continue;
                    }
                    /*else if(CustomName[i].type == ALWAYSKILL)
                    {

                    }*/
                    else if(CustomName[i].type == KILLFIRST)
                    {
                        ObjectNode* pBack = pNode;

                        it = ObjectVec.erase(it);
                        it = ObjectVec.insert(ObjectVec.begin(), pBack);
                        continue;
                    }
                }
                it++;
            }
        }

    }
    catch(...)
    {
        TRACE(_T("Ӧ�������ļ�����"));
    }


    return TRUE;
}

//��Χ�ڵ�������
DWORD GamecallEx::GetRangeLootCount(DWORD range)
{
    std::vector<ObjectNode*> RangeObject;
    GetRangeLootObjectToVector(range, RangeObject);
    return RangeObject.size();
}

BOOL GamecallEx::Init()
{

    //�ȴ�������Ϸ
    if(WaitPlans(540))
    {
        LOGER(_T("������Ϸ���"));
    }
    else
    {
        LOGER(_T("û�ܽ�����Ϸ"));
        return FALSE;
    }



    //���������߳�
    m_hThreads[0] = (HANDLE)_beginthreadex(0, 0, KeepAliveThread, this, 0, 0);
    m_hThreads[1] = (HANDLE)_beginthreadex(0, 0, AttackHelperThread, this, 0, 0);
    SetThreadPriority(m_hThreads[0], THREAD_PRIORITY_LOWEST);
    SetThreadPriority(m_hThreads[1], THREAD_PRIORITY_LOWEST);

    //��ս����Ϣ
    GameHook::GetInstance()->SetCombatSink(this);


    if(!Gamecall::Init()) return FALSE;

    return TRUE;
}

void GamecallEx::NotifyMonsterAttack(MONSTERATAACK* pAttack)
{
    static MONSTERATAACK old1;

    static DWORD dwFirst;
    DWORD dwSec = GetTickCount();

	TRACE("����ID:%x",pAttack->dwStrikeId);
    //�Ȱ�ʱ�����
    if((dwSec - dwFirst) > 1000)
    {
        if(pAttack->dwStrikeId != old1.dwStrikeId)
        {
			if (pAttack->dwStrikeId == 0x5527005)
			{
				sendcall(id_msg_attack, (LPVOID)0x5dca);//tab
			}else if (pAttack->dwStrikeId == 0x5527009)
			{
				//c-5E1B
				sendcall(id_msg_attack, (LPVOID)0x5E1B);//tab

			}

            //����д��Ӧboss�ļ���
            

            old1 = *pAttack;
        }

        dwFirst = GetTickCount();
    }




}