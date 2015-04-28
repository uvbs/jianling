// combatEvent.h: interface for the CombatEvent class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_COMBATEVENT_H__C72242F3_049D_4095_84A4_6EB98CF741D8__INCLUDED_)
#define AFX_COMBATEVENT_H__C72242F3_049D_4095_84A4_6EB98CF741D8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "GameHook.h"


class CombatEvent: public ICombatHookSink
{
protected:
	CombatEvent();
	virtual ~CombatEvent();

    DECLARE_SINGLETON(CombatEvent)
public:

    
    void AddEvent(MONSTERATAACK *pAttack);

    virtual void NotifyMonsterAttack(MONSTERATAACK *pAttack);


private:
    std::list<MONSTERATAACK> _events;
};

#endif // !defined(AFX_COMBATEVENT_H__C72242F3_049D_4095_84A4_6EB98CF741D8__INCLUDED_)
