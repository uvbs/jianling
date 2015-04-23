// ombatBoss.h: interface for the CombatBoss class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_OMBATBOSS_H__4807637C_C4C2_4752_9D02_052934507027__INCLUDED_)
#define AFX_OMBATBOSS_H__4807637C_C4C2_4752_9D02_052934507027__INCLUDED_

#if _MSC_VER > 1000
    #pragma once
#endif // _MSC_VER > 1000

#include "GameHook.h"

class CombatBoss: public ICombatHookSink
{
public:
    CombatBoss();
    virtual ~CombatBoss();

    void NotifyMonsterAttack(MONSTERATAACK* pAttack);


    void run();

private:
    std::list<MONSTERATAACK> _event;
};

#endif // !defined(AFX_OMBATBOSS_H__4807637C_C4C2_4752_9D02_052934507027__INCLUDED_)
