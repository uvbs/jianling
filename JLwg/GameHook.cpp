// GameHook.cpp: implementation of the GameHook class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "GameHook.h"
#include "GamecallEx.h"
#include "gamestruct.h"




extern GamecallEx gcall;


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


DWORD* GameHook::backupSendStep = NULL;
DWORD* GameHook::backupWearEquipment = NULL;
DWORD* GameHook::backupYiciJianWu = NULL;
DWORD* GameHook::backupDunDi = NULL;
DWORD* GameHook::backupQuest = NULL;
DWORD* GameHook::backupCombat = NULL;

std::vector<DWORD> GameHook::m_ObjAddrVec;
SHOWHOOKRESULT GameHook::showHookRet = NULL;


DWORD g_RecordStepRange = 200;
fPosition g_fmypos;


GameHook::GameHook():
stepHook((void *)shunyi_call, mySendStep),
deQuestHook((void *)deliver_quest_call, myDeliveQuest),
aeQuestHook((void *)npc_quest_call, myAcceptQuest),
WearHook((void *)chuanzhuangbei_call, myWearEquipment), 
DundiHook((void *)dundi_call, myDunDi),
Yicjw((void *)pickup1_call, myYiCiJianWu),
CombatHook((void *)0x0047B948, myCombatFilter)
{
    
}

GameHook::~GameHook()
{

}

void __stdcall GameHook::mySendStep(SENDSTEP *ftarpos)
{
    
    static BOOL bFirst = TRUE;
    if(bFirst)
    {
        GameHook::showHookRet(_T("gcall.Stepto(%d,%d,%d);"), (int)ftarpos->y, (int)ftarpos->x, (int)ftarpos->z);
        bFirst = !bFirst;
    }
    
    
    fPosition tarpos = {ftarpos->x, ftarpos->y, ftarpos->z};
    
    BYTE* backup = (BYTE*)ftarpos;
    
    //�೤�������һ��
    if(Gamecall::CalcC(g_fmypos, tarpos) >= g_RecordStepRange)
    {
        GameHook::showHookRet(_T("gcall.Stepto(%d,%d,%d);"), (int)ftarpos->y, (int)ftarpos->x, (int)ftarpos->z);
        g_fmypos.x = ftarpos->x;
        g_fmypos.y = ftarpos->y;
        g_fmypos.z = ftarpos->z;
    }
    
    
    //׷��
    FILE* file = _tfopen(gcall.GetLujingTest(), _T("a+b"));
    if(file == NULL)
    {
        OutputDebugString(_T("���ļ�ʧ��"));
        goto exitf;
    }
    
    int i;
    for(i = 0; i < 34; i++)
    {
        
        BYTE buff[512];
        //�Ӳ����и���512�ֽڵ�������
        memcpy(buff, backup, 512);
        
        //����512�ֽ�д���ļ���
        size_t count = fwrite(buff, 512, 1, file);
        if(count == 0){
            TRACE(_T("д��ʧ��"));
            break;
        }
        
        fflush(file);
        backup += 512;
    }
    
    fclose(file);
    
    
exitf:
    
    void *jmpTo = GameHook::backupSendStep;
    __asm
    {
        leave;
        jmp jmpTo;
    }
}


//��װ��
void __stdcall GameHook::myWearEquipment(DWORD argv1, DWORD value, DWORD argv3, DWORD itemtype)
{
    
    BOOL bFind = FALSE;
    //����value�ĸ�16λ �Ǳ�����Ʒ��id;
    //ͨ����������ȡ����
    std::vector<_BAGSTU> GoodsVector;
    gcall.GetAllGoodsToVector(GoodsVector);
    
    wchar_t *name = NULL;
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
    {
        showHookRet(_T("��װ��ʧ��"));
    }
    
    void* jmpTo = GameHook::backupWearEquipment;
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
		mov eax,[esi+0x10];
		mov id,eax;
	}
	
	for(int i = 0; i < m_ObjAddrVec.size(); i++){
		if(objAddr == m_ObjAddrVec[i]){
			showHookRet(_T("%08x, ����: %d"), objAddr, id);
		}
	}

    void* jmpTo = GameHook::backupCombat;
    __asm{
        leave;
        jmp jmpTo;
    }
    
}

//�������Ӻ���
void __stdcall GameHook::myYiCiJianWu(DWORD argv1, 
                            DWORD argv2, 
                            DWORD argv3, 
                            DWORD argv4, 
                            DWORD argv5)
{

    DWORD* pEsp = & argv1;
    showHookRet(_T("dump stack"));
    
    for(int i = 0; i < 5; i++)
    {
        showHookRet(_T("esp+%d %08x"), i, *(pEsp + i));
    }
    
    void* jmpTo = GameHook::backupYiciJianWu;
    __asm
    {
        leave;
        jmp jmpTo;
    }
}



//�������Ӻ���
void __stdcall GameHook::myDunDi()
{
    DWORD eax_value;
    __asm
    {
        mov eax_value, eax;
    }
    
    showHookRet(_T("eax = %08x"), eax_value);
    
    void* jmpTo = GameHook::backupDunDi;
    __asm
    {
        leave;
        jmp jmpTo;
    }
}



//�������Ӻ���
void __stdcall GameHook::myDeliveQuest(DWORD unknow,
									DWORD questID, 
                             UCHAR questStep,
                             DWORD argv3,
                             DWORD argv4, 
                             DWORD npcid1,
                             DWORD npcid2)
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
    
    //��������ֵ
    DWORD* pEsp = &questID;  
    pEsp += 1;
    
    
    showHookRet(_T("dump stack"));
    for(i = 0; i < 8; i++)
    {
        showHookRet(_T("esp+%d %08x"), i, *(pEsp + i));
    }
    
    showHookRet(_T("mianban: %08x"), edi_value);
    BOOL bFined;
    bFined = FALSE;
    wchar_t* name = NULL;
    std::vector<ObjectNode *> RangeObject;
    
    gcall.GetAllObjectToVector(gcall.GetObjectBinTreeBaseAddr(), RangeObject);
    for(i = 0; i < RangeObject.size(); i++)
    {
        ObjectNode *pNode = RangeObject[i];
        
        if((pNode->id == npcid1) && (pNode->id2 == npcid2))
        {
            //ֻҪ�Աȵ�NPCID������ȥ
            name = gcall.GetObjectName(pNode->ObjAddress);
            bFined = TRUE;
            
            //�˴�break�߼�����
            break;
        }
    }
    
    if(bFined != TRUE)
    {
        showHookRet(_T("û�б��������\nNPCID: %d, NPCID2: %d"), npcid1, npcid2);
    }
    
    //NPC��û������
    if(name == NULL)
    {
        name = L"NULL";
    }
    
    showHookRet(_T("gcall.DeliverQuests(%d, %x, %s);"), questID, questStep, name);
    
    int result = MessageBox(NULL, _T("һ�ν�����CALLִ��\n\nȷ��: ������\nȡ��: ֹͣ��"),
        NULL, MB_OKCANCEL);
    

    void* jmpTo = GameHook::backupQuest;
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


//�������Ӻ���
void __stdcall GameHook::myAcceptQuest(DWORD questID, 
                             UCHAR questStep, 
                             DWORD argv3, 
                             DWORD argv4, 
                             DWORD npcid1,
                             DWORD npcid2, 
                             DWORD argv7)
{
    DWORD* pEsp = &questID;
   
    showHookRet(_T("dump stack"));
    for(int i = 0; i < 7; i++)
    {
        showHookRet(_T("esp+%d %08x"), i, *(pEsp + i));
    }
    
    __asm
    {
        leave;
        retn 28;
    }
}


