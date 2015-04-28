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




IMPLEMENT_SINGLETON(CombatEvent)

//构造函数
CombatEvent::CombatEvent()
{

}

//析构函数
CombatEvent::~CombatEvent()
{

}

void CombatEvent::NotifyMonsterAttack(MONSTERATAACK* pAttack)
{
    static MONSTERATAACK old1;
    static DWORD dwFirst = 0;
    DWORD dwSec = GetTickCount();

    TRACE(_T("技能ID:%x"), pAttack->dwStrikeId);


    //先按时间过滤
    if((dwSec - dwFirst) > 1000)
    {
        if(pAttack->dwStrikeId != old1.dwStrikeId)
        {

            //添加事件, 这个优先级 == 1
            EventDispatcher::GetInstance()->AddEvent(new EventArg);

            //这里写对应boss的技能
            old1 = *pAttack;
        }

        dwFirst = GetTickCount();
    }

}

void CombatEvent::AddEvent(MONSTERATAACK* pAttack)
{
    _events.push_back(*pAttack);
}