// GameHook.h: interface for the GameHook class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GAMEHOOK_H__E712D73C_7E44_4074_8CE5_C484C0DE297F__INCLUDED_)
#define AFX_GAMEHOOK_H__E712D73C_7E44_4074_8CE5_C484C0DE297F__INCLUDED_


#include "gamestruct.h"


typedef struct _MONSTERATAACK
{
    DWORD dwObj;
    DWORD dwStrikeId;
} MONSTERATAACK, *PMONSTERATAACK;

struct IHookRetSink
{
    virtual void ShowHook(TCHAR * pszFormat, ...) = 0;
};

struct ICombatHookSink
{
    virtual void NotifyMonsterAttack(MONSTERATAACK * pAttack) = 0;
};


//负责Hook
class GameHook
{
protected:
    GameHook();
    virtual ~GameHook();

    DECLARE_SINGLETON(GameHook)


private:
    IHookRetSink* m_sink;
    ICombatHookSink* m_pCombatSink;

public:
    void SetSink(IHookRetSink* pSink)
    {
        m_sink = pSink;
    }

    void DelCombatSink()
    {
        m_pCombatSink = NULL;
    }

    void SetCombatSink(ICombatHookSink* pSink)
    {
        m_pCombatSink = pSink;
    }


    DWORD* backupSendStep;
    DWORD* backupWearEquipment;
    DWORD* backupYiciJianWu;
    DWORD* backupDunDi;
    DWORD* backupQuest;
    DWORD* backupCombat;


    std::vector<ObjectNode*> m_ObjAddrVec;




    CHook hookQietu;
    CHook deQuestHook;
    CHook aeQuestHook;
    CHook WearHook;
    CHook DundiHook;
    CHook Yicjw;
    CHook CombatHook;
    CHook stepHook;



    //走路发包的结构
    typedef struct _STEPPACKET
    {
        DWORD unknow;
        float x;
        float y;
        float z;
    } STEPPACKET, PSTEPPACKET;

    //Hooked Functions!
    static void __stdcall ShunyiQietu();
    static void __stdcall myAcceptQuest(DWORD questID, UCHAR questStep, DWORD argv3, DWORD argv4, DWORD npcid1, DWORD npcid2, DWORD argv7);
    static void __stdcall myDeliveQuest(DWORD unknow, DWORD questID, UCHAR questStep, DWORD argv3, DWORD argv4, DWORD npcid1, DWORD npcid2);
    static void __stdcall myDunDi();
    static void __stdcall myYiCiJianWu(DWORD argv1, DWORD argv2, DWORD argv3, DWORD argv4, DWORD argv5);
    static void __stdcall myCombatFilter();//战斗日志
    static void __stdcall myWearEquipment(DWORD argv1, DWORD value, DWORD argv3, DWORD itemtype);//穿装备
    static void __stdcall mySendStep(float x, float y, float z);//走路
    static void __stdcall RecordStepPacket(STEPPACKET *pBuf);
};

#endif // !defined(AFX_GAMEHOOK_H__E712D73C_7E44_4074_8CE5_C484C0DE297F__INCLUDED_)
