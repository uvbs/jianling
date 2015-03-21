// GameHook.h: interface for the GameHook class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GAMEHOOK_H__E712D73C_7E44_4074_8CE5_C484C0DE297F__INCLUDED_)
#define AFX_GAMEHOOK_H__E712D73C_7E44_4074_8CE5_C484C0DE297F__INCLUDED_

#if _MSC_VER > 1000
    #pragma once
#endif // _MSC_VER > 1000

#include "..\common\CHook.h"



typedef void (*SHOWHOOKRESULT)(LPVOID lpParam, TCHAR szFormat[]);


//负责Hook
class GameHook
{

public:
    static GameHook* GetInstance() {
        if(_Instance == NULL)
        {
            _Instance =    new GameHook();
        }
        return _Instance;
    }

private:
    static GameHook* _Instance;

protected:
    GameHook();
    virtual ~GameHook();

    //走路发包的结构
    typedef struct _SENDSTEP {
        DWORD unknow;
        float x;
        float y;
        float z;
    } SENDSTEP, PSENDSTEP;

public:
    static LPVOID m_lpParam;
    static SHOWHOOKRESULT m_showHookRet;

    static void showHookRet(LPTSTR lpText, ...);

    static DWORD* backupSendStep;
    static DWORD* backupWearEquipment;
    static DWORD* backupYiciJianWu;
    static DWORD* backupDunDi;
    static DWORD* backupQuest;
    static DWORD* backupCombat;

    static std::vector<DWORD> m_ObjAddrVec;

    CHook deQuestHook;
    CHook aeQuestHook;
    CHook WearHook;
    CHook DundiHook;
    CHook Yicjw;
    CHook CombatHook;

    CHook stepHook;

    //接任务
    static void __stdcall myAcceptQuest(DWORD questID, UCHAR questStep, DWORD argv3, DWORD argv4,
                                        DWORD npcid1, DWORD npcid2, DWORD argv7);

    //交任务
    static void __stdcall myDeliveQuest(DWORD unknow, DWORD questID, UCHAR questStep,
                                        DWORD argv3, DWORD argv4, DWORD npcid1, DWORD npcid2);

    //城市传送
    static void __stdcall myDunDi();
    static void __stdcall myYiCiJianWu(DWORD argv1, DWORD argv2, DWORD argv3, DWORD argv4, DWORD argv5);
    static void __stdcall myCombatFilter();//战斗日志
    static void __stdcall myWearEquipment(DWORD argv1, DWORD value, DWORD argv3, DWORD itemtype);//穿装备

    static void __stdcall mySendStep(SENDSTEP* ftarpos);//走路
};

#endif // !defined(AFX_GAMEHOOK_H__E712D73C_7E44_4074_8CE5_C484C0DE297F__INCLUDED_)
