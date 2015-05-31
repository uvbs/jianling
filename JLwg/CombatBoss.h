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
    void LoadCountsData(); //加载技能次数数据
    int run();

private:
    CMutex m_Mutex;
	MONSTERATAACK m_event;
    std::wstring m_name;
    std::map<int, int> m_JnCounts;  //技能次数映射
};

#endif // !defined(AFX_OMBATBOSS_H__4807637C_C4C2_4752_9D02_052934507027__INCLUDED_)
