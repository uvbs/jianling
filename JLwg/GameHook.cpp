// GameHook.cpp: implementation of the GameHook class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "GameHook.h"
#include "GamecallEx.h"
#include "gamestruct.h"



//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


DWORD* GameHook::backupSendStep = NULL;
DWORD* GameHook::backupWearEquipment = NULL;
DWORD* GameHook::backupYiciJianWu = NULL;
DWORD* GameHook::backupDunDi = NULL;
DWORD* GameHook::backupQuest = NULL;
DWORD* GameHook::backupCombat = NULL;

GameHook* GameHook::_Instance = NULL;

LPVOID GameHook::m_lpParam = NULL;
SHOWHOOKRESULT GameHook::m_showHookRet = NULL;
std::vector<DWORD> GameHook::m_ObjAddrVec;

static DWORD g_RecordStepRange = 200;
static fPosition g_fmypos;

static DWORD* jmpTo;
GameHook::GameHook():
    stepHook((void*)shunyi_call, mySendStep),
    deQuestHook((void*)deliver_quest_call, myDeliveQuest),
    aeQuestHook((void*)npc_quest_call, myAcceptQuest),
    WearHook((void*)chuanzhuangbei_call, myWearEquipment),
    DundiHook((void*)dundi_call, myDunDi),
    Yicjw((void*)pickup1_call, myYiCiJianWu),
    CombatHook((void*)0x0047B948, myCombatFilter)
{

}

GameHook::~GameHook()
{

}


void GameHook::showHookRet(LPTSTR szFormat, ...)
{
    TCHAR szBuf[BUFSIZ] = {0};

    va_list argptr;
    va_start(argptr, szFormat);
    wvsprintf(szBuf, szFormat, argptr);
    va_end(argptr);

    _tcscat(szBuf, _T("\r\n"));

    m_showHookRet(m_lpParam, szBuf);

}




void __stdcall GameHook::mySendStep(SENDSTEP* ftarpos)
{

    fPosition tarpos = {ftarpos->x, ftarpos->y, ftarpos->z};

    BYTE* backup = (BYTE*)ftarpos;

    //多长距离输出一次
    if(Gamecall::CalcC(g_fmypos, tarpos) >= g_RecordStepRange)
    {
        showHookRet(_T("gcall.Stepto(%d,%d,%d);"), (int)ftarpos->y, (int)ftarpos->x, (int)ftarpos->z);
        g_fmypos.x = ftarpos->x;
        g_fmypos.y = ftarpos->y;
        g_fmypos.z = ftarpos->z;
    }


    //追加
    FILE* file = _tfopen(Gamecall::GetLujingTest(), _T("a+b"));
    if(file == NULL)
        OutputDebugString(_T("打开文件失败"));
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

    BOOL bFind = FALSE;
    //根据value的高16位 是背包物品的id;
    //通过各自数获取名字
    std::vector<_BAGSTU> GoodsVector;
    Gamecall::GetAllGoodsToVector(GoodsVector);

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
        showHookRet(_T("gcall.WearEquipment(L%s, %d);"), name, itemtype);
    else
        showHookRet(_T("穿装备失败"));

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
    }
    __asm
    {
        mov eax, [esi+0x10];
        mov id, eax;
    }

    for(int i = 0; i < m_ObjAddrVec.size(); i++)
    {
        if(objAddr == m_ObjAddrVec[i])
            showHookRet(_T("%08x, 技能: %d"), objAddr, id);
    }

    jmpTo = backupCombat;
    __asm
    {
        leave;
        jmp jmpTo;
    }

}

//交任务钩子函数
void __stdcall GameHook::myYiCiJianWu(DWORD argv1,
                                      DWORD argv2,
                                      DWORD argv3,
                                      DWORD argv4,
                                      DWORD argv5)
{

    DWORD* pEsp = & argv1;
    showHookRet(_T("dump stack"));

    for(int i = 0; i < 5; i++)
        showHookRet(_T("esp+%d %08x"), i, *(pEsp + i));

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

    showHookRet(_T("eax = %08x"), eax_value);

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


    showHookRet(_T("dump stack"));
    for(i = 0; i < 8; i++)
        showHookRet(_T("esp+%d %08x"), i, *(pEsp + i));

    showHookRet(_T("mianban: %08x"), edi_value);
    BOOL bFined;
    bFined = FALSE;
    wchar_t* name = NULL;
    std::vector<ObjectNode*> RangeObject;

    Gamecall::GetAllObjectToVector(Gamecall::GetObjectBinTreeBaseAddr(), RangeObject);
    for(i = 0; i < RangeObject.size(); i++)
    {
        ObjectNode* pNode = RangeObject[i];

        if((pNode->id == npcid1) && (pNode->id2 == npcid2))
        {
            //只要对比到NPCID就跳出去
            name = Gamecall::GetObjectName(pNode->ObjAddress);
            bFined = TRUE;

            //此处break逻辑无误
            break;
        }
    }

    if(bFined != TRUE)
        showHookRet(_T("没有遍历到这个\nNPCID: %d, NPCID2: %d"), npcid1, npcid2);

    //NPC有没有名字
    if(name == NULL)
        name = L"NULL";

    showHookRet(_T("gcall.DeliverQuests(%d, %x, %s);"), questID, questStep, name);

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

    showHookRet(_T("dump stack"));
    for(int i = 0; i < 7; i++)
        showHookRet(_T("esp+%d %08x"), i, *(pEsp + i));

    __asm
    {
        leave;
        retn 28;
    }
}


