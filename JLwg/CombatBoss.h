// ombatBoss.h: interface for the CombatBoss class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_OMBATBOSS_H__4807637C_C4C2_4752_9D02_052934507027__INCLUDED_)
#define AFX_OMBATBOSS_H__4807637C_C4C2_4752_9D02_052934507027__INCLUDED_

#include "GameHook.h"

class CombatBoss: public ICombatHookSink
{
public:
    CombatBoss();
    virtual ~CombatBoss();

    void NotifyMonsterAttack(MONSTERATAACK* pAttack);

    void SetName(const wchar_t *name);
    void run();

private:
    CMutex m_Mutex;
    std::list<MONSTERATAACK> _event;
    std::wstring m_name;
};

#endif // !defined(AFX_OMBATBOSS_H__4807637C_C4C2_4752_9D02_052934507027__INCLUDED_)
