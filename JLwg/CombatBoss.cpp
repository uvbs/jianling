// ombatBoss.cpp: implementation of the CombatBoss class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "jlwg.h"
#include "GamecallEx.h"
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
//到达目的地的通知, 目前采用: 一直阻塞, 到达才返回. 因此到达的结果就是函数返回
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
    int inExit = 0; //测试


    //攻击循环
    while(1)
    {

        //退出条件
        //boss 死
        inExit++;
        if(inExit >= 100000) break;





        //事件列表空?
        if(_event.size() > 0)
        {

            MONSTERATAACK ma;


            //这里需要同步
            m_Mutex.Lock();
            std::list<MONSTERATAACK>::iterator it = _event.begin();

            ma = (*it);

            //处理了这个事件, 从队列删掉
            _event.erase(it);
            m_Mutex.Unlock();



            switch(ma.dwStrikeId)
            {

            //对应boss技能
            case 0x5455E1:
                {
					Sleep(800);
					TRACE("0x5455E1");
					//GamecallEx::GetInstance()->KeyPress(86);
					if (GamecallEx::GetInstance()->isStrikeCd(0x5DFC))
					{
						GamecallEx::GetInstance()->sendcall(id_msg_attack, (LPVOID)0x5DFC);//v
						//GamecallEx::GetInstance()->Attack(0x5DFC);
						Sleep(3000);
					}else
					{
						GamecallEx::GetInstance()->sendcall(id_msg_attack, (LPVOID)0x5dca);//tab
						Sleep(1000);
					}
					
					
					
					
                    break;
                }
			case 0x5455DD:
				{
					Sleep(800);
					TRACE("0x5455DD");
					//GamecallEx::GetInstance()->KeyPress(9);
					GamecallEx::GetInstance()->sendcall(id_msg_attack, (LPVOID)0x5dca);//tab
					//GamecallEx::GetInstance()->Attack(0x5dca);
					Sleep(1000);
					break;
				}
			case 0x5455DA:
				{
					Sleep(800);
					TRACE("0x5455DA");
					//GamecallEx::GetInstance()->KeyPress(82);
					//GamecallEx::GetInstance()->sendcall(id_msg_attack, (LPVOID)0x5dc1);//r
					//GamecallEx::GetInstance()->Attack(0x5dc1);
					//Sleep(500);
					//GamecallEx::GetInstance()->KeyPress(88);
					if (GamecallEx::GetInstance()->isStrikeCd(0x5E24))
					{
						GamecallEx::GetInstance()->sendcall(id_msg_attack, (LPVOID)0x5E24);//x
						//GamecallEx::GetInstance()->Attack(0x5E24);
						Sleep(500);
					}else
					{
						GamecallEx::GetInstance()->sendcall(id_msg_attack, (LPVOID)0x5dca);//tab
						Sleep(1000);
					}
					break;
				}
            default:
                {
                    //杀怪
                    TRACE(_T("attack id: %d"), ma.dwStrikeId);

                    break;
                }

            }


        }
        else
        {

            //空闲时动作, 一般的释放技能
			GamecallEx::GetInstance()->TurnToNear(300);
			Sleep(100);
			//GamecallEx::GetInstance()->KeyPress(82);
			GamecallEx::GetInstance()->sendcall(id_msg_attack, (LPVOID)0x5dc1);//r
			Sleep(100);
			//GamecallEx::GetInstance()->KeyPress(84);
			GamecallEx::GetInstance()->sendcall(id_msg_attack, (LPVOID)0x5dde);//t
			Sleep(100);
        }


        //事件发送过快导致执行对应动作时为时已晚怎么办, 这个暂时不考虑
        //计算机没来得及处理人更不可能了
        Sleep(100);
    }


    //取消回调
    GameHook::GetInstance()->SetCombatSink(NULL);
}


//这里回调不能阻塞的.
//游戏hook那里回调过来的, 所以这里也不能执行耗时的操作.
//也不能放技能. 这里只把boss攻击当作事件放到一个队列
void CombatBoss::NotifyMonsterAttack(MONSTERATAACK* pAttack)
{

    static MONSTERATAACK old1;
    static DWORD dwFirst;
    DWORD dwSec = GetTickCount();


    //先按时间过滤
    if((dwSec - dwFirst) > 500)
    {
        if(pAttack->dwStrikeId != old1.dwStrikeId)
        {


            //可以有个优先级, 放到队列前还是队列后
            //现实优先处理还是顺序处理.需要同步
            m_Mutex.Lock();
            _event.push_front(*pAttack);
            m_Mutex.Unlock();

            //这优先级没意义吧, 这个队列一般都是空的情况
            //空表示事件被处理掉了, 如果还有队列的话, 只能说明事件已经在排队了.
            //处理排了队的事件就没意义啦, 事件应该被及时处理
            //比如一个灭团技能被排队处理了, 还排了1秒. 这时候再被处理已经没意义了.

            old1 = *pAttack;
        }

        dwFirst = GetTickCount();
    }
}