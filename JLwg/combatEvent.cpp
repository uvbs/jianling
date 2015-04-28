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

//���캯��
CombatEvent::CombatEvent()
{

}

//��������
CombatEvent::~CombatEvent()
{

}

void CombatEvent::NotifyMonsterAttack(MONSTERATAACK* pAttack)
{
    static MONSTERATAACK old = {0};

    //�����Ϣ���������ж���ظ���, �˴�����!
    if(pAttack->dwObj != old.dwObj)
    {
        TRACE(_T("����id: %d, ����id: %d"), pAttack->dwObj, pAttack->dwStrikeId);

        //����¼�, ������ȼ� == 1
        EventDispatcher::GetInstance()->AddEvent(new EventArg);

        old = *pAttack;
    }

}

void CombatEvent::AddEvent(MONSTERATAACK* pAttack)
{
    _events.push_back(*pAttack);
}