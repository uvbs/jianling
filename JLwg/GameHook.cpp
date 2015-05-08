// GameHook.cpp: implementation of the GameHook class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "JLwg.h"
#include "GameHook.h"
#include "GamecallEx.h"
#include "GameConfig.h"




//单例
IMPLEMENT_SINGLETON(GameHook)

DWORD* GameHook::backupSendStep = NULL;
DWORD* GameHook::backupWearEquipment = NULL;
DWORD* GameHook::backupYiciJianWu = NULL;
DWORD* GameHook::backupDunDi = NULL;
DWORD* GameHook::backupQuest = NULL;
DWORD* GameHook::backupCombat = NULL;


std::vector<ObjectNode*> GameHook::m_ObjAddrVec;


DWORD* jmpTo;
DWORD g_RecordStepRange = 200;
fPosition g_fmypos;


//构造函数
GameHook::GameHook():
    stepHook((void*)shunyi_call, mySendStep),
    deQuestHook((void*)deliver_quest_call, myDeliveQuest),
    aeQuestHook((void*)npc_quest_call, myAcceptQuest),
    WearHook((void*)chuanzhuangbei_call, myWearEquipment),
    DundiHook((void*)dundi_call, myDunDi),
    Yicjw((void*)pickup1_call, myYiCiJianWu),
    CombatHook((void*)hook_combat_call, myCombatFilter),
    hookQietu((void*)hook_dont_leave_dungeons, ShunyiQietu)

{
    m_sink = NULL;
    m_pCombatSink = NULL;
}

GameHook::~GameHook()
{

}


void __stdcall GameHook::ShunyiQietu()
{


    __asm
    {
        leave;
        retn 12;
    }
}

void __stdcall GameHook::mySendStep(SENDSTEP* ftarpos)
{
    Gamecall* pCall = Gamecall::GetInstance();


    fPosition tarpos = {ftarpos->x, ftarpos->y, ftarpos->z};

    BYTE* backup = (BYTE*)ftarpos;

    //多长距离输出一次
    if(pCall->CalcC(g_fmypos, tarpos) >= g_RecordStepRange)
    {
        GameHook::GetInstance()->m_sink->ShowHook(_T("gcall.Stepto(%d,%d,%d);"), (int)ftarpos->y, (int)ftarpos->x, (int)ftarpos->z);
        g_fmypos.x = ftarpos->x;
        g_fmypos.y = ftarpos->y;
        g_fmypos.z = ftarpos->z;
    }


    GameConfig* pConfig = GameConfig::GetInstance();


    TCHAR szExe[MAX_PATH] = {0};
    GetModuleFileName(AfxGetInstanceHandle(), szExe, MAX_PATH);
    PathRemoveFileSpec(szExe);
    PathAppend(szExe, _T("路径"));
    if(!PathFileExists(szExe))
    {
        _tmkdir(szExe);
    }

    PathAppend(szExe, _T("new.bin"));

    //追加
    FILE* file = _tfopen(szExe, _T("a+b"));
    if(file == NULL)
    {
        TRACE(_T("打开文件失败"));
    }
    else
    {

        for(int i = 0; i < 34; i++)
        {

            BYTE buff[512];
            //从参数中复制512字节到缓冲区
            memcpy(buff, backup, 512);

            //把这512字节写到文件中
            size_t count = fwrite(buff, 512, 1, file);
            if(count == 0)
            {
                OutputDebugString(_T("写入失败"));
                break;
            }

            fflush(file);
            backup += 512;
        }

        fclose(file);

    }

    jmpTo = backupSendStep;
    __asm
    {
        leave;
        jmp jmpTo;
    }
}


//穿装备
void __stdcall GameHook::myWearEquipment(DWORD argv1, DWORD value, DWORD argv3, DWORD itemtype)
{

    Gamecall* pCall = Gamecall::GetInstance();

    BOOL bFind = FALSE;

    //根据value的高16位 是背包物品的id;
    //通过各自数获取名字
    std::vector<_BAGSTU> GoodsVector;
    pCall->GetAllGoodsToVector(GoodsVector);

    wchar_t* name = NULL;
    DWORD GridPos = value >> 16;

    for(DWORD i = 0; i < GoodsVector.size(); i++)
    {
        if(GoodsVector[i].m_Info == GridPos)
        {
            bFind = TRUE;
            name = GoodsVector[i].name;
        }
    }

    if(bFind)
    {
        GameHook::GetInstance()->m_sink->ShowHook(_T("gcall.WearEquipment(L%s, %d);"), name, itemtype);
    }
    else
    {
        GameHook::GetInstance()->m_sink->ShowHook(_T("穿装备失败"));
    }

    jmpTo = backupWearEquipment;
    __asm
    {
        leave;
        jmp jmpTo;
    }
}

void __stdcall GameHook::myCombatFilter()
{

    DWORD objAddr;
    DWORD id;


    __asm
    {
        mov objAddr, ebx;
        mov eax, [esi+0x10];
        mov id, eax;
    }

    for(int i = 0; i < m_ObjAddrVec.size(); i++)
    {
        if(objAddr == m_ObjAddrVec[i]->ObjAddress)
        {

            if(GameHook::GetInstance()->m_sink != NULL)
            {
                GameHook::GetInstance()->m_sink->ShowHook(_T("怪物: %08x, 技能: %d"), objAddr, id);
            }


            if(GameHook::GetInstance()->m_pCombatSink != NULL)
            {
                MONSTERATAACK ma;
                ma.dwObj = objAddr;
                ma.dwStrikeId = id;

                GameHook::GetInstance()->m_pCombatSink->NotifyMonsterAttack(&ma);
            }
        }
    }

    jmpTo = backupCombat;
    __asm
    {
        leave;
        jmp jmpTo;
    }

}

//交任务钩子函数
void __stdcall GameHook::myYiCiJianWu(
    DWORD argv1,
    DWORD argv2,
    DWORD argv3,
    DWORD argv4,
    DWORD argv5)
{

    DWORD* pEsp = & argv1;
    GameHook::GetInstance()->m_sink->ShowHook(_T("dump stack"));

    for(int i = 0; i < 5; i++)
    {
        GameHook::GetInstance()->m_sink->ShowHook(_T("esp+%d %08x"), i, *(pEsp + i));
    }

    jmpTo = backupYiciJianWu;
    __asm
    {
        leave;
        jmp jmpTo;
    }
}



//交任务钩子函数
void __stdcall GameHook::myDunDi()
{
    DWORD eax_value;
    __asm
    {
        mov eax_value, eax;
    }

    GameHook::GetInstance()->m_sink->ShowHook(_T("eax = %08x"), eax_value);

    jmpTo = backupDunDi;
    __asm
    {
        leave;
        jmp jmpTo;
    }
}



//交任务钩子函数
void __stdcall GameHook::myDeliveQuest(DWORD unknow, DWORD questID, UCHAR questStep,
                                       DWORD argv3, DWORD argv4, DWORD npcid1, DWORD npcid2)
{

    Gamecall* pCall = Gamecall::GetInstance();
    int edi_value;
    int i;


    __asm
    {
        __asm
        {
            mov edi_value, edi;
        }
        pushad;
    }

    //过掉返回值
    DWORD* pEsp = &questID;
    pEsp += 1;


    GameHook::GetInstance()->m_sink->ShowHook(_T("dump stack"));
    for(i = 0; i < 8; i++)
    {
        GameHook::GetInstance()->m_sink->ShowHook(_T("esp+%d %08x"), i, *(pEsp + i));
    }

    GameHook::GetInstance()->m_sink->ShowHook(_T("mianban: %08x"), edi_value);
    BOOL bFined;
    bFined = FALSE;
    wchar_t* name = NULL;
    std::vector<ObjectNode*> RangeObject;

    pCall->GetAllObjectToVector(pCall->GetObjectBinTreeBaseAddr(), RangeObject);
    for(i = 0; i < RangeObject.size(); i++)
    {
        ObjectNode* pNode = RangeObject[i];

        if((pNode->id == npcid1) && (pNode->id2 == npcid2))
        {
            //只要对比到NPCID就跳出去
            name = pCall->GetObjectName(pNode->ObjAddress);
            bFined = TRUE;

            //此处break逻辑无误
            break;
        }
    }

    if(bFined != TRUE)
    {
        GameHook::GetInstance()->m_sink->ShowHook(_T("没有遍历到这个\nNPCID: %d, NPCID2: %d"), npcid1, npcid2);
    }

    //NPC有没有名字
    if(name == NULL)
    {
        name = L"NULL";
    }

    GameHook::GetInstance()->m_sink->ShowHook(_T("gcall.DeliverQuests(%d, %x, %s);"), questID, questStep, name);

    int result = MessageBox(NULL, _T("一次交任务CALL执行\n\n确定: 交了它\n取消: 停止交"),
                            NULL, MB_OKCANCEL);


    jmpTo = backupQuest;
    if(result == IDOK)
    {
        __asm
        {
            popad;
            leave;
            jmp jmpTo;
        }
    }
    else
    {
        __asm
        {
            popad;
            leave;
            retn 32;
        }
    }
}


//交任务钩子函数
void __stdcall GameHook::myAcceptQuest(DWORD questID, UCHAR questStep, DWORD argv3,
                                       DWORD argv4, DWORD npcid1, DWORD npcid2, DWORD argv7)
{
    DWORD* pEsp = &questID;

    GameHook::GetInstance()->m_sink->ShowHook(_T("dump stack"));
    for(int i = 0; i < 7; i++)
    {
        GameHook::GetInstance()->m_sink->ShowHook(_T("esp+%d %08x"), i, *(pEsp + i));
    }

    __asm
    {
        leave;
        retn 28;
    }
}


