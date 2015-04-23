// ombatBoss.cpp: implementation of the CombatBoss class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "jlwg.h"
#include "CombatBoss.h"



#ifdef _DEBUG
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
    #define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CombatBoss::CombatBoss()
{

}

CombatBoss::~CombatBoss()
{

}


//问题: 耗时的操作时, 如果此时正好有事件通知怎么办
//其实目前耗时的操作, 比如走路的问题, 在于如果不是同步调用, 需要一种方式获得
//到达目的地的通知
//目前采用: 一直阻塞, 到达才返回. 因此到达的结果就是函数返回
//需要一种异步调用, 在执行完获得通知
void CombatBoss::run()
{
    //hook怪物技能, 设置回调
    GameHook::GetInstance()->SetCombatSink(this);

    while(1)
    {
        if(_event.size() > 0)
        {
            std::list<MONSTERATAACK>::iterator it = _event.begin();
            switch((*it).dwStrikeId)
            {
            case 3333:
                {

                    break;
                }

            default:
                {
                    //杀怪

                }

            }

            _event.erase(it);
        }
        else
        {
            //空闲时动作
        }


        Sleep(1000);
    }

}

void CombatBoss::NotifyMonsterAttack(MONSTERATAACK* pAttack)
{
    _event.push_back(*pAttack);
}