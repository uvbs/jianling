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
    static MONSTERATAACK old1;
    static DWORD dwFirst = 0;
    DWORD dwSec = GetTickCount();

    TRACE(_T("����ID:%x"), pAttack->dwStrikeId);


    //�Ȱ�ʱ�����
    if((dwSec - dwFirst) > 1000)
    {
        if(pAttack->dwStrikeId != old1.dwStrikeId)
        {

            //����¼�, ������ȼ� == 1
            EventDispatcher::GetInstance()->AddEvent(new EventArg);

            //����д��Ӧboss�ļ���
            old1 = *pAttack;
        }

        dwFirst = GetTickCount();
    }

}

void CombatEvent::AddEvent(MONSTERATAACK* pAttack)
{
    _events.push_back(*pAttack);
}