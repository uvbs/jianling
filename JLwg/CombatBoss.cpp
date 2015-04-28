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


    //遍历到boss的地址
    //获得坐标

    std::vector<ObjectNode*> RangeObject;
    GamecallEx::GetInstance()->GetRangeMonsterToVector(200, RangeObject);



    //走过去



    //攻击循环
    while(1)
    {

        //退出条件
        //boss 死
        



        //事件列表空表示当前可以普通攻击
        if(_event.size() > 0)
        {
            std::list<MONSTERATAACK>::iterator it = _event.begin();
            switch((*it).dwStrikeId)
            {

            //对应boss技能
            case 3333:
                {

                    break;
                }

            default:
                {
                    //杀怪
                    TRACE(_T("attack id:%d"), (*it).dwStrikeId);
                    break;
                }

            }

            //处理了这个事件, 从队列删掉
            _event.erase(it);
        }
        else
        {
            //空闲时动作

            //普通释放技能



        }


        //事件发送过快导致执行对应动作时为时已晚怎么办
        Sleep(250);
    }

}

void CombatBoss::NotifyMonsterAttack(MONSTERATAACK* pAttack)
{

    static MONSTERATAACK old1;

    static DWORD dwFirst;
    DWORD dwSec = GetTickCount();

    TRACE(_T("技能ID:%x"), pAttack->dwStrikeId);



    //先按时间过滤
    if((dwSec - dwFirst) > 1000)
    {
        if(pAttack->dwStrikeId != old1.dwStrikeId)
        {


            //可以有个优先级, 放到队列前还是队列后
            //现实优先处理还是顺序处理.
            _event.push_back(*pAttack);



//             if(pAttack->dwStrikeId == 0x5527005)
//             {
//                 sendcall(id_msg_attack, (LPVOID)0x5dca);//tab
//             }
//             else if(pAttack->dwStrikeId == 0x5527009)
//             {
//                 //c-5E1B
//                 sendcall(id_msg_attack, (LPVOID)0x5E1B);//tab
//
//             }

            //这里写对应boss的技能




            old1 = *pAttack;
        }

        dwFirst = GetTickCount();
    }


}