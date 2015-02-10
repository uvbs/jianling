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
        log.logdv(_T("装备位置没有物品"));
        return FALSE;
    }


    //先判断参数传的有没有, 没有算逑
    _BAGSTU fu;
    if(GetGoodsFromBagByName(name, &fu) == FALSE)
    {
        log.logdv(_T("背包里没有对应物品"));
        return FALSE;
    }


    //参数有, 再判断合成目标有没有已经满5
	BOOL isFull5_fu = TRUE;

	//破5的武器貌似都改成蓝颜色了，并且无需强化
	//if (_wcsicmp(fu.name,qianhun) == 0)
	//{
	//	isFull5_fu = TRUE;
	//}else
	//{
	//	if(fu.m_PingJi == 5 &&
	//		(fu.m_DangQianJingYanZhi == fu.m_DangQianJingYanZongZhi))
	//	{
	//		//已经满5
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
        //破5级后继续强化
        HeChengWuQi(pos);
    }
    else
    {
        log.logdv(_T("材料武器还未满5级"));
        log.logdv(_T("开始使用武魂合成"));
        if(HeChengWuQiByHun(pos))
        {
            return HeChengWuQi_Po5(pos, name);
        }
        log.logdv(_T("合成完毕, 依然不满5"));
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
                        log.logdv(_T("没有找到这个武魂材料"));
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
                        log.logdv(_T("没有找到这个首饰武魂材料"));
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
        log.logdv(_T("%s: 没有找到这个名称的装备"), FUNCNAME);
        return FALSE;
    }


    return TRUE;
}


// 武器的类型是1
// 八卦的类型是4
// 首饰的类型是5
BOOL GamecallEx::HeChengWuQi(EQUITMENT_POS pos)
{

    DWORD qhColor = UINT_MAX;
    CCIniFile fileConfig;
    fileConfig.Open(m_szConfigPath);
    TCHAR* szColor = fileConfig.GetProfileString(strNormal, strQhColor, strGreen);
    BOOL bFindColor = TRUE;
    //根据颜色取得游戏内对应的数据
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
        TRACE(_T("一个未知的颜色"));
        bFindColor = FALSE;
    }

    if(bFindColor == FALSE)
    {
        return FALSE;
    }

    _BAGSTU goods;
    GetGoodsByEquipPos(pos, &goods);


    //这里处理获取材料的逻辑
    std::vector<_BAGSTU> Cailiao;
    std::vector<_BAGSTU> AllBagItem;
    GetAllGoodsToVector(AllBagItem);


    for(DWORD i = 0; i < AllBagItem.size(); i++)
    {

        //判断同类型
        if(AllBagItem[i].m_Type == goods.m_Type)
        {
            if(AllBagItem[i].m_YanSe == qhColor) //绿色
            {
                //这可以当作一个材料
                Cailiao.push_back(AllBagItem[i]);
                log.logdv(_T("遍历到一个材料"));

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


    //使用所有材料
    for(DWORD j = 0; j < Cailiao.size(); j++)
    {

        //如果等级5, 而且经验满
        if(goods.m_DangQianJingYanZhi == goods.m_DangQianJingYanZongZhi)
        {
            if(goods.m_PingJi == 5 ||
                    goods.m_PingJi == 10)
            {
                log.logdv(_T("物品强化已经满级"));
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


//死亡状态=1或2
void GamecallEx::FuHuo()
{
    //首先, 得是个死人
    if(GetPlayerDeadStatus() != 1 && GetPlayerDeadStatus() != 2)
    {
        OutputDebugString(_T("复活状态"));
        return;
    }

    DWORD uiAddr = 0;
    GetUIAddrByName(L"SkillBarPanel", &uiAddr);
    if(uiAddr == 0)
    {
        OutputDebugString(_T("复活时没有遍历到UI"));
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
                log.logdv(_T("进入读条"));
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


//捡东西
//参数1: 坐标
//参数2: 范围
//捡 参数1 范围 内的掉落
void GamecallEx::Pickup(int pos, DWORD range)
{

//startLoot:

    //走到了, 遍历周围范围的可拾取对象
    ObjectVector RangeObject;
    GetRangeLootObjectToVector(range, RangeObject);

    if(RangeObject.size() == 0)
    {
        log.logdv(_T("没有东西可捡"));
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

            //如果在距离内就不要走过去捡
            //距离游戏内测试165以内会出现 f 按钮
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
            log.logdv(_T("没有成功捡起来"));
        }
    }

}


//火化尸体
void GamecallEx::Pickdown()
{
    // TODO: 在此添加控件通知处理程序代码
    DWORD Pos;
    DWORD info;
    DWORD info1;
    Pos = ReadDWORD(ReadDWORD(ReadDWORD(ReadDWORD(obj_enum_base) + huohua_offset1)  + huohua_offset2) + 0x14);
    info  = ReadDWORD(Pos + huohua_offset4); //火化尸体4级偏移
    info1 = ReadDWORD(Pos + huohua_offset5); //火化尸体5级偏移

    ObjectNode Node;
    Node.id = info;
    Node.id2 = info1;

    sendcall(id_msg_Pickup1, &Node);
}



//买东西
//参数1: 数量
//参数2: 索引, 物品在ui里的位置  0 开始
//参数3: 名字
void GamecallEx::BuyItem(DWORD nums, DWORD index, wchar_t* npcname, BOOL bClose)
{

    assert(npcname != NULL);

    DWORD dwUiAddr = 0;
    BOOL bOpen = OpenShangDian(npcname, &dwUiAddr);
    if(bOpen == FALSE)
    {
        log.logdv(_T("%s: 没能打开对话框"), FUNCNAME);
        return;
    }


    GouMaiWuPing(nums, index, dwUiAddr);


    if(bClose)
    {
        CloseShangDian();
    }
}


//卸装备
//参数是身上的格子数
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
        TRACE(_T("卸装备出错"));
    }
}

//瞬间移动
//参数1: 文件数据路径
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
        log.logdv(_T("读取瞬移文件,准备瞬移"));
    }

    //取文件大小
    fseek(file, 0L, SEEK_END);
    int filesize = ftell(file);
    fseek(file, 0L, SEEK_SET);

    //根据文件大小计算需要发送多少次
    for(int i = 0; i < filesize / 17408; i++)
    {
        //每次发送16384字节
        BYTE* buff = new BYTE[17408];
        BYTE* Oribuff = buff;


        for(int i = 0; i < 34; i++)
        {
            //用循环总共读出来16386字节
            BYTE temp[512];
            //TODO: 这里还有问题, 得保证512全部读出来了.
            //TODO: 钩子那里同样的问题, 但是能用
            size_t count = fread(temp, 1, 512, file);
            if(count == 0)
            {
                TRACE(_T("读取出错"));
            }
            else
            {
                //TRACE1("读取:%d",count);
            }

            memcpy(buff, temp, 512);
            buff += 512;
        }

        //发送这16384字节
        PARAM_GUANSHANGDIAN temp;
        temp.argv1 = (DWORD)Oribuff;
        temp.argv2 = 0xee;
        sendcall(id_msg_ZOULUSHUNYI, &temp);
        Sleep(10);
    }

    log.logdv(_T("结束瞬移"));
    fclose(file);
    log.logdv(_T("关闭瞬移文件,退出瞬移"));
}


void GamecallEx::kill_PickupOnce()
{
    //杀完捡起掉落, 此时的范围为了更可靠写改成x2
    //if(GetRangeMonsterCount(200) == 0){
    //log.logdv(_T("范围无人, 开始捡东西"));
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
        log.logdv(_T("杀怪时举起了一个尸体"));
        return TRUE;
    }

    return FALSE;
}


//id相同, 步骤不同返回TRUE, 表示任务步骤变了
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
            OutputDebugString(_T("没有找到对应的任务ID"));
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

//添加自定义杀怪规则
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

//清空自定义杀怪规则
int GamecallEx::ClearCustom()
{
    //释放掉new的内存
    for(int i = 0; i < CustomName.size(); i++)
    {
        delete []CustomName[i].name;
    }

    CustomName.clear();
    return 0;
}


//杀怪
//参数1: 坐标
//参数2: 以参数1计算的范围
//参数3: 模式
int GamecallEx::FindThenKill(int pos, DWORD range, DWORD mode, DWORD MyQuestStep, DWORD MyQuestID, DWORD canKillRange)
{
    


    fPosition fmypos;
    GetPlayerPos(&fmypos);

startKiLL:
    //log.logdv(_T("遍历怪物"));
    ObjectVector RangeObject;
    GetRangeMonsterToVector(range, RangeObject);


    //排序
    //log.logdv(_T("怪物排序"));
    std::sort(RangeObject.begin(), RangeObject.end(), UDgreater);

    //log.logdv(_T("根据配置配需"));
    //应用杀怪配置, 包括自定义的
    Kill_ApplyConfig(RangeObject);

    DWORD count = RangeObject.size();
    log.logdv(_T("总共: %d 个目标怪物"), count);


    //杀怪
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
            log.logdv(_T("执行modePickupBody"));
            if(kill_PickupBody())
            {
                break;
            }
        }
        if(mode & modePickupOnce)
        {
            log.logdv(_T("执行modePickupOnce"));
            kill_PickupOnce();
        }


        //判断任务步骤
        if(mode & modeTask)
        {
            log.logdv(_T("执行modeTask"));
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
    //打完所有怪小等片刻再遍历。
    Sleep(500);

    //如果有一次超时, 那可能是一个隐藏的但是存在的怪物
    //没办法杀的, 就不继续找剩余怪, 避免死循环
    if(bTimeOut == FALSE)
    {
        //整个杀怪逻辑执行完后再遍历一次周围怪物, 如果有杀掉再返回
        log.logdv(_T("执行GetRangeMonsterCount"));
        if(GetRangeMonsterCount() >= 1)
        {
            goto startKiLL;
        }
    }


exitfun:
    if(mode & modePickup)
    {
        Sleep(500);
        log.logdv(_T("执行modePickup"));
        //杀完捡起掉落, 此时的范围为了更可靠写改成x2
        Pickup(0, range);
    }

    if(mode & modeGoback)
    {
        log.logdv(_T("执行modeGoback"));
        Gamecall::Stepto(fmypos, 10, CAN_OPERATOR, range * 2);
    }

    log.logdv(_T("%s done!"), FUNCNAME);
    return RESULT_KILL_OK;
}


//交任务, 最后参数默认0
//参数1: 任务id
//参数2: 任务步骤
//参数3: 任务名字
//参数4: 任务的类型, 通常是 0 1 2 3 这几个值
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
            log.logdv(_T("%s: 没有找到这个NPC"), FUNCNAME);
            return;
        }

        npcid1 = Node->id;
        npcid2 = Node->id2;
    }

    //取任务面板地址, 测试不用这个地址
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


//打开任务物品, 带有走路逻辑
//参数1: 范围
//参数2: 任务id;
//参数3: 任务步骤
//遍历参数1范围内的所有任务物品
//如果遍历到走过去捡他
//捡起后判断任务step变化
//变大退出逻辑, 如果捡完依然没变, 也是退出逻辑, 没有返回值
//如果没有在范围内遍历到切换线路
void GamecallEx::PickupTask(DWORD range, DWORD taskid, DWORD taskstep)
{
    //先判断参数正确性
    BOOL bFined = FALSE;


    //备份当前角色坐标待最后回到原点用
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
        log.logdv(_T("没有找到你传的任务id"));
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
            //走过去
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
    //走回去
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



//打开任务物品
//参数1: 距离
//当调用此函数时, 函数枚举参数1范围内的任务物品
//然后走过去拾取
//读条后不需捡的任务没法判断, 用超时来判断
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





//随机换线
//参数1: 给随机值一个最大值
//比如你传5, 那么随机的数值最大只会是5
//传0表示不限制, 最大值将使用遍历到的线路数量
void GamecallEx::randXianlu(DWORD MaxXianlu)
{
    //获取当前线路数量
    while(isLoadingMap() != 3)
    {
        TRACE(_T("等待读图完成"));
        Sleep(1000);
    }

    DWORD allXianluNums = GetXianluNums();
    log.logdv(_T("所有线路数量: %d"), allXianluNums);

    if(allXianluNums == 0)
    {
        TRACE(_T("所有线路数量=0，返回"));
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

            randnum += 1; //线路下标从1开始
            //log.logdv(_T("11随机获取的线路: %d"), randnum);
            if(randnum != GetPlayerXianlu())
            {

                //if(isHaveXianlu(randnum)){
                {
                    log.logdv(_T("随机获取的线路: %d"), randnum);
                    sendcall(id_msg_HuanXian, (LPVOID)randnum);
                    return;
                    //}
                }
                Sleep(100);
            }
            log.logdv(_T("换线未成功，可能很多灰色线路"));
        }
    }


}



//装备物品
//参数1: 装备名字
//参数2: 装备类型
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

    log.logdv(_T("穿装备: 没有找到匹配的名字"));
}


BOOL Gamecall::Stepto(fPosition& tarpos, double timeOut, DWORD okRange, DWORD tooLong, BOOL sp3x)
{

    //首先, 人得是活的
    if(GetPlayerDeadStatus() == 1 ||
            GetPlayerDeadStatus() == 2)
    {
        return FALSE;
    }

    DWORD tc1 = GetTickCount();

    //判断距离太远
    fPosition fmypos;
    if(GetPlayerPos(&fmypos) == FALSE)
    {
        log.logdv(_T("没能获取自身坐标"));
        return FALSE;
    }


    DWORD dis = (DWORD)CalcC(fmypos, tarpos);
    if(dis >= tooLong)
    {
        log.logdv(_T("%s: 目的距离太远"), FUNCNAME);
        return FALSE;
    }

    //走路在外边导致走的时候碰一下就停止了
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
        //等200微妙再判断, 否则调用Step时游戏内并没有立刻走
        //导致下面的走路状态判断失败又调用一次
        Sleep(100);


        //判断距离太远
        fmypos;
        if(GetPlayerPos(&fmypos) == FALSE)
        {
            log.logdv(_T("没能获取自身坐标"));
            return FALSE;
        }

        dis = (DWORD)CalcC(fmypos, tarpos);
        //走到
        if(dis <= okRange)
        {
            return TRUE;
        }


        if((GetTickCount() - tc1) >= (timeOut * 1000))
        {
            log.logdv(_T("超时"));
            sendcall(id_msg_attack, (LPVOID)0x5e6a);
            return FALSE;
        }


        //走路状态判定, 避免频繁调用
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

//走路
//参数0: 目的坐标
//参数1: 时间单位是 秒, 只能 <= 60秒, 用来做超时返回, 避免死循环
//参数2: 距离模糊, 比如当a和b距离, 参数2 时就停下. 如果要距离=0, 就是重叠再停下传0
//参数3: 超过这个距离就不执行函数了
//补充:
//参数4: 到达距离模糊参数之后的行为, TRUE停止, FALSE不停止只返回
BOOL GamecallEx::Stepto(float y, float x, float z, double timeOut, DWORD okRange, DWORD tooLong, BOOL sp3x)
{
    fPosition tarpos;
    tarpos.x = x;
    tarpos.y = y;
    tarpos.z = z;
    TRACE3("走路:%d,%d,%d", (int)y, (int)x, (int)z);
    return Gamecall::Stepto(tarpos, timeOut, okRange, tooLong, sp3x);
}



//走路的外层封装函数
void GamecallEx::Stepto(wchar_t* name)
{
    ObjectNode* pNode = NULL;

    pNode = GetObjectByName(name, 0);
    if(pNode == NULL)
    {
        log.logdv(_T("%s: 没有找到这个NPC"), FUNCNAME);
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
    //	log.logdv(_T("相同的城市ID取消传送"));
    //	return FALSE;
    //}


    __try
    {

        sendcall(id_msg_DunDi, (LPVOID)cityid);

        Sleep(2000);
        if(isCityConveying() == FALSE)
        {
            log.logdv(_T("城市传送读条失败"));
            return FALSE;
        }
        else
        {
            for(;;)
            {
                //读条完毕或被打断
                if(isCityConveying() == FALSE)
                {
                    break;
                }

                Sleep(2000);
            }
        }

        //判断是否打断根据有没有进入读黄条, 限时6秒
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
            //等待蓝条完成
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
            log.logdv(_T("读条被打断"));
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



//NPC接任务
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
    //装备上几个缺
    std::vector<int> NoEquit;

    int i;
    for(i = 8; i < 16; i++)
    {
        _BAGSTU goods;
        if(GetGoodsByEquipPos(i, &goods) == FALSE)
        {
            log.logdv(_T("%s: %d 处没有装备"), FUNCNAME, i);
            NoEquit.push_back(i);
        }

    }


    //取得背包里所有八卦
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



//补齐八卦
//参数1: 八卦名字
//TODO:
BOOL GamecallEx::BuqiBaGua(wchar_t* name)
{
    //装备上几个缺

    std::vector<_BAGSTU> EquiVec;
    GetAllBodyEquipToVector(EquiVec);

    log.logdv(_T("遍历数量:%d"), EquiVec.size());
    std::vector<int> NoEquit;


    int i;
    int j;
    int k;

    for(i = 8; i < 16; i++)
    {
        k = 0;
        for(j = 0; j < EquiVec.size(); j++)
        {
            //log.logdv(_T("当前对比装备type=%d,info=%d,i=%d"),EquiVec[j].m_Type,EquiVec[j].m_Info,i);
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

    log.logdv(_T("当前未装备数量:%d"), NoEquit.size());
    for(i = 0; i < NoEquit.size(); i++)
    {
        log.logdv(_T("%d位置没有装备八卦"), NoEquit[i]);
    }

    if(NoEquit.size() == 0)
    {
        return FALSE;
    }

    //取得背包里所有八卦
    std::vector<_BAGSTU> BaGuaVec;
    GetSpecBaGuaToVector(name, BaGuaVec);


    for(i = 0; i < BaGuaVec.size(); i++)
    {
        for(DWORD j = 0; j < NoEquit.size(); j++)
        {
            //log.logdv(_T("当前对比八卦位置:%d"),NoEquit[j]);
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

//参数1是盒子在背包中的位置 + 0002
//参数2是固定0
//参数3是股东1
//参数4是选普通的钥匙是0  特殊的钥匙就是1
//参数5是钥匙ID
//参数6是固定1
//参数7是解封符的数量
void GamecallEx::JieFengHezi(wchar_t* HeZiname, UCHAR keytype, wchar_t* Keyname, DWORD keyCount)
{
    _BAGSTU HeziGoods;
    _BAGSTU KeyGoods;
    if(GetGoodsFromBagByName(HeZiname, &HeziGoods) == FALSE ||
            GetGoodsFromBagByName(Keyname, &KeyGoods) == FALSE)
    {
        log.logdv(_T("%s: 没有找到这个盒子"), FUNCNAME);
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

//解封装备
//装备名字
//材料名字
//材料数量
void GamecallEx::JieFengZhuangBei(wchar_t* name, wchar_t* cailiao_name, UINT count)
{
    _BAGSTU goods;
    _BAGSTU cailiao;
    if(GetGoodsFromBagByName(name, &goods) == FALSE ||
            GetGoodsFromBagByName(cailiao_name, &cailiao) == FALSE)
    {
        log.logdv(_T("%d: 没有这个物品"), FUNCNAME);
        return;
    }

    int value = goods.m_Info;
    value <<= 16;
    value += package;

    Gamecall::JieFengZhuangBei(value, cailiao.m_ID, count);

}



//替换八卦
//参数1: 八卦名字
BOOL GamecallEx::TihuanBaGua(wchar_t* name)
{

    //取得背包里所有八卦
    std::vector<_BAGSTU> BaGuaVec;
    GetSpecBaGuaToVector(name, BaGuaVec);

    for(DWORD i = 0; i < BaGuaVec.size(); i++)
    {
        //这是一个可以装备的
        BaGuaVec[i].m_BaGuaGeZiShu += 1;
        sendcall(id_msg_WearEquipment, &BaGuaVec[i]);
        Sleep(500);
    }


    return TRUE;
}


//领取奖励
void GamecallEx::LinQuJiangLi()
{
    sendcall(id_msg_LinQuJiangLi, (LPVOID)0);
}


//跟随一个npc直到这个npc4秒内没有变化坐标
void GamecallEx::FollowNpc(wchar_t* name, DWORD range)
{

    ObjectNode* pNode = GetObjectByName(name, range);
    if(pNode == NULL)
    {
        log.logdv(_T("%s: 没有找到这个NPC"), FUNCNAME);
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

        //判断走路or停止跟随
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
        log.logdv(_T("没有找到这个宝石"));
    }

}


void GamecallEx::NewBag()
{
    sendcall(id_msg_NewBag, 0);
}


//存到仓库
void GamecallEx::CunCangku(wchar_t* name, wchar_t* npcname)
{

    if(name == NULL || npcname == NULL)
    {
        return;
    }

    DWORD dwUiAddr = 0;
    if(OpenShangDian(npcname, &dwUiAddr) == FALSE)
    {
        log.logdv(_T("%s: 没能打开对话框"), FUNCNAME);
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


// 0086BBB8  |.  50            push eax                             ;  物品数量
// 0086BBB9  |.  53            push ebx                             ;  0
// 0086BBBA  |.  56            push esi                             ;  背包中的格子数 如30002
// 0086BBBB  |.  8BC5          mov eax,ebp                          ;  "ItemStorePanel"首地址
// 0086BBBD  |.  E8 8E030000   call Client.0086BF50                 ;  卖东西1


//卖东西
//参数1: 物品名称
//参数2: 数量  == 0, 表示卖掉全部数量
void GamecallEx::SellItem(wchar_t* name, wchar_t* npcName, BOOL bClose)
{

    assert(name != NULL);
    assert(npcName != NULL);


    DWORD dwUiAddr = 0;
    if(OpenShangDian(name, &dwUiAddr) == FALSE)
    {
        log.logdv(_T("%s: 没能打开对话框"), FUNCNAME);
        return;
    }


    //通过这个名字取其它信息
    _BAGSTU goods;
    if(GetGoodsFromBagByName(name, &goods) == FALSE)
    {
        log.logdv(_T("%s: 没找到这个物品"), FUNCNAME);
        return;
    }


    __try
    {
        //这个数量数据目前测试武器八卦是0, 表示有一个
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


//丢弃物品
//参数1: 物品名字
//参数2: 数量
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
        log.logdv(_T("%s: 没有找到这个物品"), FUNCNAME);
        return;
    }

    for(unsigned i = 0; i < GoodsVec.size(); i++)
    {
        sendcall(id_msg_Fenjie, &GoodsVec[i]);
    }
}


void GamecallEx::Yaojiang(wchar_t* Zen_name, wchar_t* BaGuaname)
{

    //摇奖
    DWORD i = 0;
    _BAGSTU ZenGoods;
    ZeroMemory(&ZenGoods, sizeof(_BAGSTU));
    GetGoodsFromBagByName(Zen_name, &ZenGoods);
    log.logdv(_T("精气数量:%d"), ZenGoods.m_Num);
    for(i = 0; i < ZenGoods.m_Num; i++)
    {
        log.logdv(_T("摇精气当前进度:%d"), i);
        PickupTask();
        Sleep(5000);
    }


    //完, 开盒子装八卦
    std::vector<_BAGSTU> HeZiVec;
    GetGoodsByName_Hezi(BaGuaname, HeZiVec);
    log.logdv(_T("盒子的数量:%d"), HeZiVec.size());
    for(i = 0; i < HeZiVec.size(); i++)
    {

        log.logdv(_T("单个盒子的数量:%d"), HeZiVec[i].m_Num);
        for(int j = 0; j < HeZiVec[i].m_Num; j++)
        {
            log.logdv(_T("开盒子"));
            sendcall(id_msg__KaiHeZi, &HeZiVec[i]);
            Sleep(1000);

            log.logdv(_T("替换八卦"));
            TihuanBaGua(BaGuaname);
            Sleep(1000);

            //剩余还在背包里的分解掉
            std::vector<_BAGSTU> LastBaga;
            GetSpecBaGuaToVector(BaGuaname, LastBaga);
            log.logdv(_T("替换完八卦后，剩余八卦数量:%d"), LastBaga.size());
            for(DWORD k = 0; k < LastBaga.size(); k++)
            {
                log.logdv(_T("分解中，当前分解:%d"), LastBaga[k].m_Info);
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


    //TODO: 看看能不能用
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

//卖掉配置文件中所有物品
void GamecallEx::SellItemByConfig(wchar_t* name)
{

    CCIniFile configFile;
    configFile.Open(m_szConfigPath);
    TCHAR* szFilter = configFile.GetProfileString(strSell, strItemName);


    //遍历一次当前所有物品
    std::vector<_BAGSTU> AllBag;
    GetAllGoodsToVector(AllBag);


    DWORD dwUiAddr = 0;
    if(OpenShangDian(name, &dwUiAddr) == FALSE)
    {
        return;
    }
    GetUIAddrByName(L"ItemStorePanel", &dwUiAddr);//卖的地址

    wchar_t* token = wcstok(szFilter, L";"); // C4996
    while(token != NULL)
    {
        //每次从vector中判断出名字
        for(int i = 0; i < AllBag.size(); i++)
        {
            if(wcscmp(token, AllBag[i].name) == 0)
            {
                PARAM_GUANSHANGDIAN temp;
                temp.argv1 = (DWORD)&AllBag[i];
                temp.argv2 = dwUiAddr;
                //TRACE(_T("执行卖"));
                sendcall(id_msg_SellItem, &temp);

                Sleep(1000);
            }
        }

        //Get next token:
        token = wcstok(NULL, L";"); // C4996
    }

    CloseShangDian();
}


// 007F6025  |.  66:8B4E 70    mov cx,word ptr ds:[esi+0x70]        ;  这个是数量
// 007F6029  |.  52            push edx                             ;  00080002
// 007F602A  |.  50            push eax                             ;  [[[[0x0FAC688]+34]+80]+788]
// 007F602B  |.  E8 905ECCFF   call Client.004BBEC0                 ;  丢弃物品1
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
        //判断能删的
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
//添加一个天赋技能
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

//删除一个天赋技能
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
    //排序
    //log.logdv(_T("怪物排序"));
    std::sort(RangeObject.begin(), RangeObject.end(), UDgreater);
    //log.logdv(_T("根据配置配需"));
    Kill_ApplyConfig(RangeObject);
    if(RangeObject.size() > 0)
    {
        TRACE2("找到最近怪,面向它.ID:%d,ID2:%d", RangeObject[0]->id, RangeObject[0]->id2);
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
            TRACE(_T("TAB释放时倒地跳出"));
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
//普通攻击, rt 循环按, 具体逻辑看里面, 需要参数来使视角总是面向这个对象
void GamecallEx::AttackNormal()
{

    //放技能, 加对魔法值的判断
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


//AOE攻击
//TODO: 可以通过判断公共cd来优化
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

//杀死对象, 逻辑中带有走路
//循环出口: 怪死, 超时, 角色死, 出范围
//参数1: 对象地址
//参数2: 超时
//补充:参数2, 这个模式影响杀怪的整个过程
//canKillRange 设定多远距离可直接攻击
int GamecallEx::KillObject(DWORD range, ObjectNode* pNode, DWORD mode, DWORD canKillRange)
{
	//记录当下状态来判断目标是否死亡或者杀怪超时
	DWORD oriTime = GetTickCount();
	DWORD tarHealth = GetType4HP(pNode->ObjAddress);;

	fPosition mypos;
	fPosition targetpos;
	for(;;)
	{
 
		//TRACE(_T("判断人物死亡"));
		if(GetPlayerHealth() <= 0)
		{
			log.logdv(_T("%s: 人物死亡了"), FUNCNAME);
			return RESULT_KILL_PLAYDEAD;
		}

		//整个逻辑根据距离来作为输入数据来做判断
		//TRACE(_T("执行血量判断"));
		if(GetType4HP(pNode->ObjAddress) == -1 || GetType4HP(pNode->ObjAddress) == 0)
		{
			log.logdv(_T("%s: 血量判断怪死了"), FUNCNAME);
			return RESULT_KILL_OK;
		}


		ZeroMemory(&mypos, sizeof(fPosition));
		GetPlayerPos(&mypos);

		//通过距离判断目标死亡
		//TRACE(_T("执行类型判断"));
		ZeroMemory(&targetpos, sizeof(fPosition));

		if(GetObjectType(pNode->ObjAddress) != 0x4)
		{
			log.logdv(_T("%s: 类型判断怪死了"), FUNCNAME);
			return RESULT_KILL_OK;
		}

		//TRACE(_T("执行坐标判断"));
		if(_GetObjectPos(pNode->ObjAddress, &targetpos) == FALSE)
		{
			log.logdv(_T("%s: 坐标判断怪死了"), FUNCNAME);
			return RESULT_KILL_OK;
		}
		DWORD dis = (DWORD)CalcC(targetpos, mypos);
		//TRACE(_T("执行距离判断"));
		if(dis >= range)
		{
			log.logdv(_T("%s: 距离判断怪死了"), FUNCNAME);
			return RESULT_KILL_OK;
		}



		/*
		不可用
		if(GetObject_0x14(pNode->ObjAddress) == 0){
		log.logdv(_T("%s: 0x14判断怪死了"), FUNCNAME);
		return RESULT_KILL_OK;
		}*/


		//可继续走
		if(dis > canKillRange)
		{
			targetpos.x = targetpos.x - 10;
			targetpos.y = targetpos.y - 10;
			Gamecall::Stepto(targetpos, 10, CAN_OPERATOR, range);
			/*}else if(dis <= 2){
			log.logdv(_T("自己的坐标X:%d,y:%d,怪物的坐标X:%d,Y:%d"),(int)mypos.x,(int)mypos.y,(int)targetpos.x,(int)targetpos.y);
			log.logdv(_T("%s: 重叠怪物"), FUNCNAME);
			RandomStep(30);*/
		}
		else if(dis <= canKillRange)
		{
			//判断倒地状态
			if(isPlayerDaodi())
			{
				//5E60->5EA6->5EB0->5E9C
				TRACE(_T("进入倒地状态"));
				Sleep(500);
				if(isStrikeCd(0x5e60) == TRUE)
				{
					TRACE(_T("进入倒地状态:0x5e60"));
					sendcall(id_msg_attack, (LPVOID)0x5e60);
					Sleep(1000);
				}
				else if(isStrikeCd(0x5EA6) == TRUE)
				{
					TRACE(_T("进入倒地状态:0x5EA6"));
					sendcall(id_msg_attack, (LPVOID)0x5EA6);
				}
				else if(isStrikeCd(0x5E9C) == TRUE)
				{
					TRACE(_T("进入倒地状态:0x5E9C"));
					sendcall(id_msg_attack, (LPVOID)0x5E9C);
				}
				else if(isStrikeCd(0x5EB0) == TRUE)
				{
					TRACE(_T("进入倒地状态:0x5EB0"));
					sendcall(id_msg_attack, (LPVOID)0x5EB0);
				}

			}
			//杀怪时才需要转向
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
						//TRACE("执行AEO");
						AttackAOE();
					}else
					{
						//TRACE("执行RT");
						//TRACE(_T("执行RT"));
						AttackNormal();
					}
				}
				else{
					//TRACE("执行AOE外的RT");
					//TRACE(_T("执行AOE外的RT"));
					AttackNormal();
				}
			}
			//5秒没能打掉血就退
			DWORD curTime = GetTickCount();
			if((curTime - oriTime) >= 5000)
			{
				DWORD curHealth = GetType4HP(pNode->ObjAddress);
				if(curHealth == tarHealth)
				{
					log.logdv(_T("%s: 超时退出"), FUNCNAME);
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
                /*log.logdv(_T("传送期间有怪，执行杀怪。"));
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


    //遍历一次当前所有物品
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
        //每次从vector中判断出名字
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


//[物品首地址 + 0x6C] == 0x78 adress
BOOL GamecallEx::HeChengWuQi_Po10(EQUITMENT_POS pos, wchar_t* name)
{
    _BAGSTU zhu;
    if(GetGoodsByEquipPos(pos, &zhu) == FALSE)
    {
        log.logdv(_T("装备位置没有物品"));
        return FALSE;
    }


    //先判断参数传的有没有, 没有算逑
    _BAGSTU fu;
    if(GetGoodsFromBagByName(name, &fu) == FALSE)
    {
        log.logdv(_T("背包里没有对应物品"));
        return FALSE;
    }


    //参数有, 再判断合成目标有没有已经满5
    BOOL isFull5_fu = TRUE;
    //if (_wcsicmp(fu.name,qianhun) == 0)
    //{
    //	isFull5_fu = TRUE;
    //}else
    //{
    //	if(fu.m_PingJi == 5 &&
    //		(fu.m_DangQianJingYanZhi == fu.m_DangQianJingYanZongZhi))
    //	{
    //		//已经满5
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
        //破5级后继续强化
		//HeChengWuQi(pos);
    }
    else
    {
        log.logdv(_T("材料武器还未满5级"));
        log.logdv(_T("开始使用武魂合成"));
        if(HeChengWuQiByHun(pos))
        {
            return HeChengWuQi_Po10(pos, name);
        }
        log.logdv(_T("合成完毕, 依然不满5"));
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
        log.logdv(_T("没有输入任务物品名称"));
        return;
    }
    else
    {

        if(GetGoodsFromBagByName(name, &bag) == FALSE)
        {
            log.logdv(_T("没有获取到任务道具信息"));
            return;
        }
    }
    if(bag.m_Info == NULL)
    {
        log.logdv(_T("没有获取道具的格子数"));
        return;
    }
    gezi = bag.m_Info;
    gezi <<= 16;
    gezi += package;
    //取任务面板地址, 测试不用这个地址
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
