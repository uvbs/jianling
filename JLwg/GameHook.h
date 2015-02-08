// GameHook.h: interface for the GameHook class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GAMEHOOK_H__E712D73C_7E44_4074_8CE5_C484C0DE297F__INCLUDED_)
#define AFX_GAMEHOOK_H__E712D73C_7E44_4074_8CE5_C484C0DE297F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\common\CCHook.h"



typedef void (*SHOWHOOKRESULT)(LPVOID lpParam, TCHAR szFormat[]);


//����Hook, �������ڼ̳��������
class GameHook
{
public:
    GameHook();
    virtual ~GameHook();



    //��·�����Ľṹ
    typedef struct _SENDSTEP
    {
        DWORD unknow;
        float x;
        float y;
        float z;
    } SENDSTEP, PSENDSTEP;


    static LPVOID m_lpParam;
    static SHOWHOOKRESULT m_showHookRet;




    static void showHookRet(LPTSTR lpText, ...);



protected:

    static std::vector<DWORD> m_ObjAddrVec;


    CCHook stepHook;
    CCHook deQuestHook;
    CCHook aeQuestHook;
    CCHook WearHook;
    CCHook DundiHook;
    CCHook Yicjw;
    CCHook CombatHook;


    static DWORD* backupSendStep;
    static DWORD* backupWearEquipment;
    static DWORD* backupYiciJianWu;
    static DWORD* backupDunDi;
    static DWORD* backupQuest;
    static DWORD* backupCombat;


    //������
    static void __stdcall myAcceptQuest(DWORD questID, UCHAR questStep, DWORD argv3, DWORD argv4,
                                        DWORD npcid1, DWORD npcid2, DWORD argv7);

    //������
    static void __stdcall myDeliveQuest(DWORD unknow, DWORD questID, UCHAR questStep,
                                        DWORD argv3, DWORD argv4, DWORD npcid1, DWORD npcid2);

    //���д���
    static void __stdcall myDunDi();
    static void __stdcall myYiCiJianWu(DWORD argv1, DWORD argv2, DWORD argv3, DWORD argv4, DWORD argv5);
    static void __stdcall myCombatFilter();//ս����־
    static void __stdcall myWearEquipment(DWORD argv1, DWORD value, DWORD argv3, DWORD itemtype);//��װ��
    
    static void __stdcall mySendStep(SENDSTEP* ftarpos);//��·
};

#endif // !defined(AFX_GAMEHOOK_H__E712D73C_7E44_4074_8CE5_C484C0DE297F__INCLUDED_)