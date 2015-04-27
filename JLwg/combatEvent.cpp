// combatEvent.cpp: implementation of the CombatEvent class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "jlwg.h"
#include "combatEvent.h"
#include "EventDispatcher.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
    #define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CombatEvent::CombatEvent()
{

}

CombatEvent::~CombatEvent()
{

}

void CombatEvent::NotifyMonsterAttack(MONSTERATAACK* pAttack)
{
    static MONSTERATAACK old = {0};

    //这个信息钩出来是有多次重复的, 此处过滤!
    if(pAttack->dwObj != old.dwObj)
    {
        TRACE(_T("怪物id: %d, 技能id: %d"), pAttack->dwObj, pAttack->dwStrikeId);

        //添加事件, 这个优先级 == 1
        EventDispatcher::GetInstance()->AddEvent(new EventArg);

        old = *pAttack;
    }

}
