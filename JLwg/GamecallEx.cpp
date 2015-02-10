#include "stdafx.h"
#include "GamecallEx.h"


#include "..\common\common.h"
#include "..\common\CIniFile.h"



GamecallEx::GamecallEx()
{

}

GamecallEx::~GamecallEx()
{

}



BOOL GamecallEx::HeChengWuQi_Po5(EQUITMENT_POS pos, wchar_t* name)
{

    _BAGSTU zhu;
    if(GetGoodsByEquipPos(pos, &zhu) == FALSE)
    {
        log.logdv(_T("װ��λ��û����Ʒ"));
        return FALSE;
    }


    //���жϲ���������û��, û������
    _BAGSTU fu;
    if(GetGoodsFromBagByName(name, &fu) == FALSE)
    {
        log.logdv(_T("������û�ж�Ӧ��Ʒ"));
        return FALSE;
    }


    //������, ���жϺϳ�Ŀ����û���Ѿ���5
	BOOL isFull5_fu = TRUE;

	//��5������ò�ƶ��ĳ�����ɫ�ˣ���������ǿ��
	//if (_wcsicmp(fu.name,qianhun) == 0)
	//{
	//	isFull5_fu = TRUE;
	//}else
	//{
	//	if(fu.m_PingJi == 5 &&
	//		(fu.m_DangQianJingYanZhi == fu.m_DangQianJingYanZongZhi))
	//	{
	//		//�Ѿ���5
	//		isFull5_fu = TRUE;
	//	}
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
        log.logdv(_T("����������δ��5��"));
        log.logdv(_T("��ʼʹ�����ϳ�"));
        if(HeChengWuQiByHun(pos))
        {
            return HeChengWuQi_Po5(pos, name);
        }
        log.logdv(_T("�ϳ����, ��Ȼ����5"));
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
                        log.logdv(_T("û���ҵ����������"));
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
                        log.logdv(_T("û���ҵ��������������"));
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
        log.logdv(_T("%s: û���ҵ�������Ƶ�װ��"), FUNCNAME);
        return FALSE;
    }


    return TRUE;
}


// ������������1
// ���Ե�������4
// ���ε�������5
BOOL GamecallEx::HeChengWuQi(EQUITMENT_POS pos)
{

    DWORD qhColor = UINT_MAX;
    CCIniFile fileConfig;
    fileConfig.Open(m_szConfigPath);
    TCHAR* szColor = fileConfig.GetProfileString(strNormal, strQhColor, strGreen);
    BOOL bFindColor = TRUE;
    //������ɫȡ����Ϸ�ڶ�Ӧ������
    if(wcscmp(strGreen, szColor) == 0)
    {
        qhColor = 3;
    }
    else if(wcscmp(strBlue, szColor) == 0)
    {
        qhColor = 4;
    }
    else if(wcscmp(strPurple, szColor) == 0)
    {
        qhColor = 5;
    }
    else
    {
        TRACE(_T("һ��δ֪����ɫ"));
        bFindColor = FALSE;
    }

    if(bFindColor == FALSE)
    {
        return FALSE;
    }

    _BAGSTU goods;
    GetGoodsByEquipPos(pos, &goods);


    //���ﴦ���ȡ���ϵ��߼�
    std::vector<_BAGSTU> Cailiao;
    std::vector<_BAGSTU> AllBagItem;
    GetAllGoodsToVector(AllBagItem);


    for(DWORD i = 0; i < AllBagItem.size(); i++)
    {

        //�ж�ͬ����
        if(AllBagItem[i].m_Type == goods.m_Type)
        {
            if(AllBagItem[i].m_YanSe == qhColor) //��ɫ
            {
                //����Ե���һ������
                Cailiao.push_back(AllBagItem[i]);
                log.logdv(_T("������һ������"));

            }
        }


        TCHAR* szFilter = NULL;
        if(AllBagItem[i].m_Type == 1)
        {
            szFilter = fileConfig.GetProfileString(strQhWuqi, strItemName);
        }
        else if(AllBagItem[i].m_Type == 5)
        {
            szFilter = fileConfig.GetProfileString(strQhShipin, strItemName);
        }
        else
        {
            continue;
        }


        wchar_t* token = wcstok(szFilter, L";"); // C4996
        while(token != NULL)
        {

            if(wcscmp(token, AllBagItem[i].name) == 0)
            {
                Cailiao.push_back(AllBagItem[i]);
            }

            // Get next token:
            token = wcstok(NULL, L";"); // C4996
        }


    }


    //ʹ�����в���
    for(DWORD j = 0; j < Cailiao.size(); j++)
    {

        //����ȼ�5, ���Ҿ�����
        if(goods.m_DangQianJingYanZhi == goods.m_DangQianJingYanZongZhi)
        {
            if(goods.m_PingJi == 5 ||
                    goods.m_PingJi == 10)
            {
                log.logdv(_T("��Ʒǿ���Ѿ�����"));
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

    log.logdv(_T("uiAddr:%d"), uiAddr);
    uiAddr = ReadDWORD(uiAddr + fuhuo_offset1);
    log.logdv(_T("uiAddr2:%d"), uiAddr);
    __try
    {

        sendcall(id_msg_Fuhuo, &uiAddr);
        for(;;)
        {
            if(isLoadingMap() != 3)
            {
                log.logdv(_T("�������"));
                break;
            }
            Sleep(500);
        }
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
    ObjectVector RangeObject;
    GetRangeLootObjectToVector(range, RangeObject);

    if(RangeObject.size() == 0)
    {
        log.logdv(_T("û�ж����ɼ�"));
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
            log.logdv(_T("û�гɹ�������"));
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

    assert(npcname != NULL);

    DWORD dwUiAddr = 0;
    BOOL bOpen = OpenShangDian(npcname, &dwUiAddr);
    if(bOpen == FALSE)
    {
        log.logdv(_T("%s: û�ܴ򿪶Ի���"), FUNCNAME);
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
void GamecallEx::XieZhuangBei(EQUITMENT_POS pos)
{
    __try
    {
        __asm
        {
            mov eax, pos;
            push eax;
            mov eax, obj_enum_base;
            mov eax, [eax];
            mov eax, [eax+xiezhuangbei_offset1];
            mov eax, [eax+xiezhuangbei_offset2];
            mov eax, [eax+xiezhuangbei_offset3];
            push eax;
            mov eax, xiezhuangbei_call;
            call eax;
        }
    }
    __except(1)
    {
        TRACE(_T("жװ������"));
    }
}

//˲���ƶ�
//����1: �ļ�����·��
void GamecallEx::Shunyi(TCHAR* szLujing)
{
    TCHAR szFull[MAX_PATH] = {0};
    _tcscat(szFull, m_szLujingPath);
    PathAppend(szFull, szLujing);
    _tcscat(szFull, _T(".bin"));


    FILE* file = _tfopen(szFull, _T("rb"));
    if(file == NULL)
    {
        log.logdv(_T("%s: open fail"), FUNCNAME);
        return;
    }
    else
    {
        log.logdv(_T("��ȡ˲���ļ�,׼��˲��"));
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

    log.logdv(_T("����˲��"));
    fclose(file);
    log.logdv(_T("�ر�˲���ļ�,�˳�˲��"));
}


void GamecallEx::kill_PickupOnce()
{
    //ɱ��������, ��ʱ�ķ�ΧΪ�˸��ɿ�д�ĳ�x2
    //if(GetRangeMonsterCount(200) == 0){
    //log.logdv(_T("��Χ����, ��ʼ����"));
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
        log.logdv(_T("ɱ��ʱ������һ��ʬ��"));
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
    //�ͷŵ�new���ڴ�
    for(int i = 0; i < CustomName.size(); i++)
    {
        delete []CustomName[i].name;
    }

    CustomName.clear();
    return 0;
}


//ɱ��
//����1: ����
//����2: �Բ���1����ķ�Χ
//����3: ģʽ
int GamecallEx::FindThenKill(int pos, DWORD range, DWORD mode, DWORD MyQuestStep, DWORD MyQuestID, DWORD canKillRange)
{
    


    fPosition fmypos;
    GetPlayerPos(&fmypos);

startKiLL:
    //log.logdv(_T("��������"));
    ObjectVector RangeObject;
    GetRangeMonsterToVector(range, RangeObject);


    //����
    //log.logdv(_T("��������"));
    std::sort(RangeObject.begin(), RangeObject.end(), UDgreater);

    //log.logdv(_T("������������"));
    //Ӧ��ɱ������, �����Զ����
    Kill_ApplyConfig(RangeObject);

    DWORD count = RangeObject.size();
    log.logdv(_T("�ܹ�: %d ��Ŀ�����"), count);


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
            log.logdv(_T("ִ��modePickupBody"));
            if(kill_PickupBody())
            {
                break;
            }
        }
        if(mode & modePickupOnce)
        {
            log.logdv(_T("ִ��modePickupOnce"));
            kill_PickupOnce();
        }


        //�ж�������
        if(mode & modeTask)
        {
            log.logdv(_T("ִ��modeTask"));
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
        log.logdv(_T("ִ��GetRangeMonsterCount"));
        if(GetRangeMonsterCount() >= 1)
        {
            goto startKiLL;
        }
    }


exitfun:
    if(mode & modePickup)
    {
        Sleep(500);
        log.logdv(_T("ִ��modePickup"));
        //ɱ��������, ��ʱ�ķ�ΧΪ�˸��ɿ�д�ĳ�x2
        Pickup(0, range);
    }

    if(mode & modeGoback)
    {
        log.logdv(_T("ִ��modeGoback"));
        Gamecall::Stepto(fmypos, 10, CAN_OPERATOR, range * 2);
    }

    log.logdv(_T("%s done!"), FUNCNAME);
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
            log.logdv(_T("%s: û���ҵ����NPC"), FUNCNAME);
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
        log.logdv(_T("û���ҵ��㴫������id"));
        return;
    }



    for(;;)
    {
        ObjectVector RangeObject;
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
            assert(curStep != UINT_MAX);

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



BOOL GamecallEx::PickupSpecTypeTask(DWORD range, DWORD type, wchar_t* name)
{

    try
    {
        ObjectVector RangeObject;
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
        ObjectVector RangeObject;
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
        ObjectVector RangeObject;
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
    log.logdv(_T("������·����: %d"), allXianluNums);

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
            //log.logdv(_T("11�����ȡ����·: %d"), randnum);
            if(randnum != GetPlayerXianlu())
            {

                //if(isHaveXianlu(randnum)){
                {
                    log.logdv(_T("�����ȡ����·: %d"), randnum);
                    sendcall(id_msg_HuanXian, (LPVOID)randnum);
                    return;
                    //}
                }
                Sleep(100);
            }
            log.logdv(_T("����δ�ɹ������ܺܶ��ɫ��·"));
        }
    }


}



//װ����Ʒ
//����1: װ������
//����2: װ������
void GamecallEx::WearEquipment(wchar_t* name, int pos)
{

    std::vector<_BAGSTU> RangeObject;
    GetAllGoodsToVector(RangeObject);

    try
    {
        DWORD i;
        for(i = 0; i < RangeObject.size(); i++)
        {
            if(wcscmp(RangeObject[i].name, name) == 0)
            {
                RangeObject[i].m_ID = pos;
                sendcall(id_msg_WearEquipment, (LPVOID)&RangeObject[i]);
                return;
            }
        }
    }
    catch(...)
    {

    }

    log.logdv(_T("��װ��: û���ҵ�ƥ�������"));
}


BOOL Gamecall::Stepto(fPosition& tarpos, double timeOut, DWORD okRange, DWORD tooLong, BOOL sp3x)
{

    //����, �˵��ǻ��
    if(GetPlayerDeadStatus() == 1 ||
            GetPlayerDeadStatus() == 2)
    {
        return FALSE;
    }

    DWORD tc1 = GetTickCount();

    //�жϾ���̫Զ
    fPosition fmypos;
    if(GetPlayerPos(&fmypos) == FALSE)
    {
        log.logdv(_T("û�ܻ�ȡ��������"));
        return FALSE;
    }


    DWORD dis = (DWORD)CalcC(fmypos, tarpos);
    if(dis >= tooLong)
    {
        log.logdv(_T("%s: Ŀ�ľ���̫Զ"), FUNCNAME);
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
            log.logdv(_T("û�ܻ�ȡ��������"));
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
            log.logdv(_T("��ʱ"));
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
        log.logdv(_T("%s: û���ҵ����NPC"), FUNCNAME);
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
    //	log.logdv(_T("��ͬ�ĳ���IDȡ������"));
    //	return FALSE;
    //}


    __try
    {

        sendcall(id_msg_DunDi, (LPVOID)cityid);

        Sleep(2000);
        if(isCityConveying() == FALSE)
        {
            log.logdv(_T("���д��Ͷ���ʧ��"));
            return FALSE;
        }
        else
        {
            for(;;)
            {
                //������ϻ򱻴��
                if(isCityConveying() == FALSE)
                {
                    break;
                }

                Sleep(2000);
            }
        }

        //�ж��Ƿ��ϸ�����û�н��������, ��ʱ6��
        bool isInMapLoading = false;
        for(int i = 0; i < 3; i++)
        {
            if(isCityConveyLoadingMap() == TRUE)
            {
                isInMapLoading = TRUE;
                break;
            }

            Sleep(2000);
        }

        if(isInMapLoading)
        {
            //�ȴ��������
            for(;;)
            {

                if(isCityConveyLoadingMap() == FALSE)
                {
                    WaitPlans();
                    break;
                }



                Sleep(2000);
            }
        }
        else
        {
            log.logdv(_T("���������"));
            return FALSE;
        }


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
            log.logdv(_T("%s: %d ��û��װ��"), FUNCNAME, i);
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

    log.logdv(_T("��������:%d"), EquiVec.size());
    std::vector<int> NoEquit;


    int i;
    int j;
    int k;

    for(i = 8; i < 16; i++)
    {
        k = 0;
        for(j = 0; j < EquiVec.size(); j++)
        {
            //log.logdv(_T("��ǰ�Ա�װ��type=%d,info=%d,i=%d"),EquiVec[j].m_Type,EquiVec[j].m_Info,i);
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

    log.logdv(_T("��ǰδװ������:%d"), NoEquit.size());
    for(i = 0; i < NoEquit.size(); i++)
    {
        log.logdv(_T("%dλ��û��װ������"), NoEquit[i]);
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
            //log.logdv(_T("��ǰ�ԱȰ���λ��:%d"),NoEquit[j]);
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
        log.logdv(_T("%s: û���ҵ��������"), FUNCNAME);
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
        log.logdv(_T("%d: û�������Ʒ"), FUNCNAME);
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
        log.logdv(_T("%s: û���ҵ����NPC"), FUNCNAME);
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
        log.logdv(_T("û���ҵ������ʯ"));
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
        log.logdv(_T("%s: û�ܴ򿪶Ի���"), FUNCNAME);
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

    assert(name != NULL);
    assert(npcName != NULL);


    DWORD dwUiAddr = 0;
    if(OpenShangDian(name, &dwUiAddr) == FALSE)
    {
        log.logdv(_T("%s: û�ܴ򿪶Ի���"), FUNCNAME);
        return;
    }


    //ͨ���������ȡ������Ϣ
    _BAGSTU goods;
    if(GetGoodsFromBagByName(name, &goods) == FALSE)
    {
        log.logdv(_T("%s: û�ҵ������Ʒ"), FUNCNAME);
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

    assert(bFind == true);

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
        log.logdv(_T("%s: û���ҵ������Ʒ"), FUNCNAME);
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
    log.logdv(_T("��������:%d"), ZenGoods.m_Num);
    for(i = 0; i < ZenGoods.m_Num; i++)
    {
        log.logdv(_T("ҡ������ǰ����:%d"), i);
        PickupTask();
        Sleep(5000);
    }


    //��, ������װ����
    std::vector<_BAGSTU> HeZiVec;
    GetGoodsByName_Hezi(BaGuaname, HeZiVec);
    log.logdv(_T("���ӵ�����:%d"), HeZiVec.size());
    for(i = 0; i < HeZiVec.size(); i++)
    {

        log.logdv(_T("�������ӵ�����:%d"), HeZiVec[i].m_Num);
        for(int j = 0; j < HeZiVec[i].m_Num; j++)
        {
            log.logdv(_T("������"));
            sendcall(id_msg__KaiHeZi, &HeZiVec[i]);
            Sleep(1000);

            log.logdv(_T("�滻����"));
            TihuanBaGua(BaGuaname);
            Sleep(1000);

            //ʣ�໹�ڱ�����ķֽ��
            std::vector<_BAGSTU> LastBaga;
            GetSpecBaGuaToVector(BaGuaname, LastBaga);
            log.logdv(_T("�滻����Ժ�ʣ���������:%d"), LastBaga.size());
            for(DWORD k = 0; k < LastBaga.size(); k++)
            {
                log.logdv(_T("�ֽ��У���ǰ�ֽ�:%d"), LastBaga[k].m_Info);
                //FenJie(LastBaga[i].name);
                sendcall(id_msg_Fenjie, &LastBaga[k]);
                Sleep(500);
            }
        }

    }
}


void GamecallEx::FixWuqi()
{
    _BAGSTU goods;
    GetGoodsByEquipPos(1, &goods);


    if(goods.m_LV  <= 20)
    {
        ChiYao(fTo20);
    }
    else if(goods.m_LV <= 36)
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
    CCIniFile configFile;
    configFile.Open(m_szConfigPath);
    TCHAR* szFilter = configFile.GetProfileString(strFenjie, strItemName);
    //AfxMessageBox(szFilter);
    std::vector<_BAGSTU> AllBag;
    GetAllGoodsToVector(AllBag);

    wchar_t* token = wcstok(szFilter, L";");
    while(token != NULL)
    {
        for(int i = 0; i < AllBag.size(); i++)
            for(int j = 0; j < AllBag[i].m_Num ; j++)
            {
                {
                    sendcall(id_msg_Fenjie, &AllBag[i]);
                    Sleep(500);
                }
            }
    }

    // Get next token:
    token = wcstok(NULL, L";");
}

//���������ļ���������Ʒ
void GamecallEx::SellItemByConfig(wchar_t* name)
{

    CCIniFile configFile;
    configFile.Open(m_szConfigPath);
    TCHAR* szFilter = configFile.GetProfileString(strSell, strItemName);


    //����һ�ε�ǰ������Ʒ
    std::vector<_BAGSTU> AllBag;
    GetAllGoodsToVector(AllBag);


    DWORD dwUiAddr = 0;
    if(OpenShangDian(name, &dwUiAddr) == FALSE)
    {
        return;
    }
    GetUIAddrByName(L"ItemStorePanel", &dwUiAddr);//���ĵ�ַ

    wchar_t* token = wcstok(szFilter, L";"); // C4996
    while(token != NULL)
    {
        //ÿ�δ�vector���жϳ�����
        for(int i = 0; i < AllBag.size(); i++)
        {
            if(wcscmp(token, AllBag[i].name) == 0)
            {
                PARAM_GUANSHANGDIAN temp;
                temp.argv1 = (DWORD)&AllBag[i];
                temp.argv2 = dwUiAddr;
                //TRACE(_T("ִ����"));
                sendcall(id_msg_SellItem, &temp);

                Sleep(1000);
            }
        }

        //Get next token:
        token = wcstok(NULL, L";"); // C4996
    }

    CloseShangDian();
}


// 007F6025  |.  66:8B4E 70    mov cx,word ptr ds:[esi+0x70]        ;  ���������
// 007F6029  |.  52            push edx                             ;  00080002
// 007F602A  |.  50            push eax                             ;  [[[[0x0FAC688]+34]+80]+788]
// 007F602B  |.  E8 905ECCFF   call Client.004BBEC0                 ;  ������Ʒ1
void GamecallEx::DeleteItemByConfig()
{
    CCIniFile configFile;
    configFile.Open(m_szConfigPath);
    TCHAR* szFilter = configFile.GetProfileString(strCuihui, strItemName);


    std::vector<_BAGSTU> GoodsVec;
    GetAllGoodsToVector(GoodsVec);


    wchar_t* token = wcstok(szFilter, L";"); // C4996
    while(token != NULL)
    {
        //�ж���ɾ��
        for(int i = 0; i < GoodsVec.size(); i++)
        {
            if(wcscmp(GoodsVec[i].name, token) == 0)
            {
                sendcall(id_msg_DeleteItem, &GoodsVec[i]);
            }
        }

        // Get next token:
        token = wcstok(NULL, L";"); // C4996
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
    ObjectVector RangeObject;
    GetRangeMonsterToVector(range, RangeObject);
    //����
    //log.logdv(_T("��������"));
    std::sort(RangeObject.begin(), RangeObject.end(), UDgreater);
    //log.logdv(_T("������������"));
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
        if(isStrikeCd(0x5dca) == TRUE)
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
    if(GetPlayerMana() >= 50)
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
			log.logdv(_T("%s: ����������"), FUNCNAME);
			return RESULT_KILL_PLAYDEAD;
		}

		//�����߼����ݾ�������Ϊ�������������ж�
		//TRACE(_T("ִ��Ѫ���ж�"));
		if(GetType4HP(pNode->ObjAddress) == -1 || GetType4HP(pNode->ObjAddress) == 0)
		{
			log.logdv(_T("%s: Ѫ���жϹ�����"), FUNCNAME);
			return RESULT_KILL_OK;
		}


		ZeroMemory(&mypos, sizeof(fPosition));
		GetPlayerPos(&mypos);

		//ͨ�������ж�Ŀ������
		//TRACE(_T("ִ�������ж�"));
		ZeroMemory(&targetpos, sizeof(fPosition));

		if(GetObjectType(pNode->ObjAddress) != 0x4)
		{
			log.logdv(_T("%s: �����жϹ�����"), FUNCNAME);
			return RESULT_KILL_OK;
		}

		//TRACE(_T("ִ�������ж�"));
		if(_GetObjectPos(pNode->ObjAddress, &targetpos) == FALSE)
		{
			log.logdv(_T("%s: �����жϹ�����"), FUNCNAME);
			return RESULT_KILL_OK;
		}
		DWORD dis = (DWORD)CalcC(targetpos, mypos);
		//TRACE(_T("ִ�о����ж�"));
		if(dis >= range)
		{
			log.logdv(_T("%s: �����жϹ�����"), FUNCNAME);
			return RESULT_KILL_OK;
		}



		/*
		������
		if(GetObject_0x14(pNode->ObjAddress) == 0){
		log.logdv(_T("%s: 0x14�жϹ�����"), FUNCNAME);
		return RESULT_KILL_OK;
		}*/


		//�ɼ�����
		if(dis > canKillRange)
		{
			targetpos.x = targetpos.x - 10;
			targetpos.y = targetpos.y - 10;
			Gamecall::Stepto(targetpos, 10, CAN_OPERATOR, range);
			/*}else if(dis <= 2){
			log.logdv(_T("�Լ�������X:%d,y:%d,���������X:%d,Y:%d"),(int)mypos.x,(int)mypos.y,(int)targetpos.x,(int)targetpos.y);
			log.logdv(_T("%s: �ص�����"), FUNCNAME);
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
				else if(isStrikeCd(0x5EB0) == TRUE)
				{
					TRACE(_T("���뵹��״̬:0x5EB0"));
					sendcall(id_msg_attack, (LPVOID)0x5EB0);
				}

			}
			//ɱ��ʱ����Ҫת��
			Gamecall::TurnTo(targetpos);
			if (mode & modeOnlyAoe)
			{
				AttackAOE();
			}else
			{
				if(mode & modeAoe)
				{
                if(Gamecall::m_bCanAoe)
					{
						//TRACE("ִ��AEO");
						AttackAOE();
					}else
					{
						//TRACE("ִ��RT");
						//TRACE(_T("ִ��RT"));
						AttackNormal();
					}
				}
				else{
					//TRACE("ִ��AOE���RT");
					//TRACE(_T("ִ��AOE���RT"));
					AttackNormal();
				}
			}
			//5��û�ܴ��Ѫ����
			DWORD curTime = GetTickCount();
			if((curTime - oriTime) >= 5000)
			{
				DWORD curHealth = GetType4HP(pNode->ObjAddress);
				if(curHealth == tarHealth)
				{
					log.logdv(_T("%s: ��ʱ�˳�"), FUNCNAME);
					return RESULT_KILL_TIMEOUT;
				}
				else
				{
					oriTime = GetTickCount();
					tarHealth = GetType4HP(pNode->ObjAddress);
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
                /*log.logdv(_T("�����ڼ��й֣�ִ��ɱ�֡�"));
                FindThenKill(0,300,modeAoe | modeNormal | modePickup | modeGoback);
                Sleep(1000);*/
                fPosition mypos;
                GetPlayerPos(&mypos);
                ChangeZ_Status(TRUE);
                ChangeHeight(mypos.z + 600);
                rs = TRUE;
            }
        }
    }
}

void GamecallEx::CuncangkuByConfig(wchar_t* name)
{
    CCIniFile configFile;
    configFile.Open(m_szConfigPath);
    TCHAR* szFilter = configFile.GetProfileString(strCunCang, strItemName);


    //����һ�ε�ǰ������Ʒ
    std::vector<_BAGSTU> AllBag;
    GetAllGoodsToVector(AllBag);


    DWORD dwUiAddr = 0;
    if(OpenShangDian(name, &dwUiAddr) == FALSE)
    {
        return;
    }


    wchar_t* token = wcstok(szFilter, L";"); // C4996
    while(token != NULL)
    {
        //ÿ�δ�vector���жϳ�����
        for(int i = 0; i < AllBag.size(); i++)
        {
            if(wcscmp(token, AllBag[i].name) == 0)
            {
                PARAM_GUANSHANGDIAN temp;
                temp.argv1 = (DWORD)&AllBag[i];
                temp.argv2 = dwUiAddr;
                sendcall(id_msg_CunCangku, &temp);

                Sleep(1000);
            }
        }

        //Get next token:
        token = wcstok(NULL, L";"); // C4996
    }

    CloseShangDian();
}


//[��Ʒ�׵�ַ + 0x6C] == 0x78 adress
BOOL GamecallEx::HeChengWuQi_Po10(EQUITMENT_POS pos, wchar_t* name)
{
    _BAGSTU zhu;
    if(GetGoodsByEquipPos(pos, &zhu) == FALSE)
    {
        log.logdv(_T("װ��λ��û����Ʒ"));
        return FALSE;
    }


    //���жϲ���������û��, û������
    _BAGSTU fu;
    if(GetGoodsFromBagByName(name, &fu) == FALSE)
    {
        log.logdv(_T("������û�ж�Ӧ��Ʒ"));
        return FALSE;
    }


    //������, ���жϺϳ�Ŀ����û���Ѿ���5
    BOOL isFull5_fu = TRUE;
    //if (_wcsicmp(fu.name,qianhun) == 0)
    //{
    //	isFull5_fu = TRUE;
    //}else
    //{
    //	if(fu.m_PingJi == 5 &&
    //		(fu.m_DangQianJingYanZhi == fu.m_DangQianJingYanZongZhi))
    //	{
    //		//�Ѿ���5
    //		isFull5_fu = TRUE;
    //	}
    //}
    TRACE2("zhu:%x,fu:%x", zhu.m_Info, fu.m_Info);

    if(isFull5_fu)
    {

        PARAM_GUANSHANGDIAN temp;
        temp.argv1 = (DWORD)&zhu;
        temp.argv2 = (DWORD)&fu;
        sendcall(id_msg_HeChengWuQi_Po10, &temp);
        Sleep(2000);
        //��5�������ǿ��
		//HeChengWuQi(pos);
    }
    else
    {
        log.logdv(_T("����������δ��5��"));
        log.logdv(_T("��ʼʹ�����ϳ�"));
        if(HeChengWuQiByHun(pos))
        {
            return HeChengWuQi_Po10(pos, name);
        }
        log.logdv(_T("�ϳ����, ��Ȼ����5"));
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
        log.logdv(_T("û������������Ʒ����"));
        return;
    }
    else
    {

        if(GetGoodsFromBagByName(name, &bag) == FALSE)
        {
            log.logdv(_T("û�л�ȡ�����������Ϣ"));
            return;
        }
    }
    if(bag.m_Info == NULL)
    {
        log.logdv(_T("û�л�ȡ���ߵĸ�����"));
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
        ObjectVector RangeObject;
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
