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
	
	DWORD MaxHealth = 0;//GetPlayerMaxHealth();
	DWORD Health = 0;//GetPlayerHealth();
	DWORD percent = 0;//Health * 100 / MaxHealth;
	TRACE(_T("准备打BOSS"));
    //hook怪物技能, 设置回调
    GameHook::GetInstance()->SetCombatSink(this);

    //获得call
    GamecallEx* pCall = GamecallEx::GetInstance();


    fPosition mypos;
    fPosition tarpos;

    ObjectNode* pBossNode = pCall->GetObjectByName(m_name.c_str(), 0);
    if(pBossNode == NULL)
    {
        TRACE(_T("没找到boss"));
        return;
    }

    pCall->Stepto(pBossNode);

//攻击循环
    while(1)
    {

        //退出条件
        //boss 死

        //pCall->KeyPress(82);
        //玩家死
        if(pCall->GetPlayerHealth() <= 0)
        {
            TRACE(_T("%s: 人物死亡了"), FUNCNAME);
            break;
        }


        if(pCall->GetObjectHP(pBossNode->ObjAddress) == -1 || pCall->GetObjectHP(pBossNode->ObjAddress) == 0)
        {
            TRACE(_T("%s: 血量判断怪死了"), FUNCNAME);
            break;
        }


        //if(pCall->GetObjectType(pBossNode->ObjAddress) != 0x4)
        //{
        //    TRACE(_T("%s: 类型判断怪死了"), FUNCNAME);
        //    break;
        //}


        if(pCall->_GetObjectPos(pBossNode->ObjAddress, &tarpos) == FALSE)
        {
            TRACE(_T("%s: 坐标判断怪死了"), FUNCNAME);
            break;
        }


        //这个距离判断不太通用, 假设怪物第血量会快速逃脱
        //此时正好判断到距离, 判断成死了
        pCall->GetPlayerPos(&mypos);
        DWORD dis = (DWORD)pCall->CalcC(tarpos, mypos);
        if(dis > CAN_OPERATOR)
        {
            pCall->Stepto(tarpos.y, tarpos.x-15, tarpos.z, 10, CAN_OPERATOR, 3000, TRUE);
            //TRACE(_T("%s: 距离判断怪死了"), FUNCNAME);
            //break;
        }

		MaxHealth = pCall->GetPlayerMaxHealth();
		Health = pCall->GetPlayerHealth();
		percent = Health * 100 / MaxHealth;



        //事件列表空?
        if(_event.size() > 0)
        {


            MONSTERATAACK ma;


            //这里需要同步
            m_Mutex.Lock();
            std::list<MONSTERATAACK>::iterator it = _event.begin();

            ma = (*it);

            //处理了这个事件, 从队列删掉
            //_event.erase(it);
			_event.clear();
            m_Mutex.Unlock();



            switch(ma.dwStrikeId)
            {

            //对应boss技能

			//武神塔2层
            case 5190087:
                {
                    pCall->TurnTo(pBossNode);
                    TRACE(_T("5190087"));
                    pCall->Kill_Tab(0x5dc1);
                    pCall->Kill_Tab(0x5dca);
                    pCall->Kill_Tab(0x5dc1);
                    pCall->Attack(0x5dca);
                    break;
                }
            case 5190071:
                {
					TRACE(_T("5190071"));
					if (percent < 70)
					{
						if (pCall->isStrikeCd(0x5DFC) == FALSE)
						{
							pCall->Attack(0x5DFC);
							pCall->TurnTo(pBossNode);
							pCall->Attack(0x5ECE);
							while (pCall->isStrikeCd(0x5DC1))
							{
								pCall->Attack(0x5ECE);
							}
						}
					}else
					{
						pCall->Kill_Tab(0x5dca);
						pCall->TurnTo(pBossNode);
						pCall->Attack(0x5dc1);
					}
                    break;
                }
            case 5190088:
                {
                    pCall->SteptoBack(pBossNode);
                    TRACE(_T("锤子来了88"));
					pCall->TurnTo(pBossNode);
                    break;
                }
            case 5190089:
                {
                    pCall->SteptoBack(pBossNode);
                    TRACE(_T("锤子来了89"));
					pCall->TurnTo(pBossNode);
                    break;
                }
			//武神塔2层结束


			//武神塔3层
			case 5511103:
				{
					pCall->SteptoBack(pBossNode);
					TRACE(_T("5511103"));
					pCall->TurnTo(pBossNode);
					break;
				}
			case 5511106:
				{
					pCall->sendcall(id_msg_attack,(LPVOID)0x5dc1);
					pCall->Attack(0x5dca);
					break;
				}
			case 5511314:
				{
					pCall->sendcall(id_msg_attack,(LPVOID)0x5dc1);
					pCall->Attack(0x5E1B);
					break;
				}

			//武神塔3层结束

			//武神塔4层
			case 5100618:
				{
					pCall->Attack(0x5dc1);
					pCall->Attack(0x5dc1);
					pCall->Attack(0x5dc1);
					pCall->Attack(0x5e6a);
					break;
				}
			case 5100614:
				{
					TRACE(_T("5100614"));
					pCall->Kill_Tab(0x5dc1);
					pCall->Kill_Tab(0x5dca);
					pCall->Kill_Tab(0x5dc1);
					pCall->Attack(0x5dca);
					break;
				}
			case 5100610:
				{
					pCall->SteptoBack(pBossNode);
					pCall->TurnTo(pBossNode);
					break;
				}
			case 5100611:
				{
					if (percent < 70)
					{
						if (pCall->isStrikeCd(0x5DFC) == FALSE)
						{
							pCall->Attack(0x5DFC);
							pCall->TurnTo(pBossNode);
							while (pCall->isStrikeCd(0x5DC1))
							{
								pCall->Attack(0x5ECE);
							}
						}
					}else
					{
						pCall->SteptoBack(pBossNode);
						pCall->TurnTo(pBossNode);
					}
					break;
				}
			case 5100613:
				{

					break;
				}
			//武神塔4层结束
            default:
                {
                    //杀怪
                    TRACE(_T("attack id: %d"), ma.dwStrikeId);
					if (wcscmp(m_name.c_str(),L"馬柴達") == 0  //1层小怪
						|| wcscmp(m_name.c_str(),L"舒藝") == 0 //1层小怪
						|| wcscmp(m_name.c_str(),L"無名") == 0 ) //3层BOSS
					{
						if (percent < 70)
						{
							if (pCall->isStrikeCd(0x5DFC) == FALSE)
							{
								pCall->Attack(0x5DFC);
								while (pCall->isStrikeCd(0x5DC1))
								{
									pCall->TurnTo(pBossNode);
									pCall->Attack(0x5ECE);
								}
							}
						}
						if (pCall->isStrikeCd(0x5DE8) == FALSE)
						{
							pCall->Attack(0x5DE8);
						}else if (pCall->isStrikeCd(0x5E10) == FALSE)
						{
							pCall->Attack(0x5E10);
						}else if (pCall->isStrikeCd(0x5DF2) == FALSE)
						{
							pCall->Attack(0x5DF2);
						}else if (pCall->isStrikeCd(0x5E06) == FALSE)
						{
							pCall->Attack(0x5E06);
						}else if (pCall->isStrikeCd(0x5e74) == FALSE)
						{
							pCall->Attack(0x5e74);
						}

					}

                    break;
                }
            }
            ZeroMemory(&_event, sizeof(MONSTERATAACK));
        }
        else
        {
            //空闲时动作, 一般的释放技能
            if(pCall->isPlayerDaodi())
            {
                //5E60->5EA6->5EB0->5E9C
                if(pCall->isStrikeCd(0x5e60) == FALSE)
                {
					pCall->Attack(0x5e60);
                    //Sleep(1000);
                }
                else if(pCall->isStrikeCd(0x5EA6) == FALSE)
                {
					pCall->Attack(0x5EA6);
                }
                else if(pCall->isStrikeCd(0x5E9C) == FALSE)
                {
					pCall->Attack(0x5E9C);
                }
            }
			
			pCall->TurnTo(pBossNode);

			if (percent < 90)
			{
				if (pCall->isStrikeCd(0x5E24) == FALSE)
				{
					pCall->Attack(0x5E24);
				}
			}

			
			if(pCall->GetPlayerMana() > 70)
			{
				//pCall->Attack(0x5dde);
				pCall->sendcall(id_msg_attack,(LPVOID)0x5dde);
			}else
			{
				//pCall->Attack(0x5dc1);
				pCall->sendcall(id_msg_attack,(LPVOID)0x5dc1);
			}
        }
        //事件发送过快导致执行对应动作时为时已晚怎么办, 这个暂时不考虑
        //计算机没来得及处理人更不可能了
        //Sleep(10);
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
    static DWORD dwEnd = GetTickCount();
    DWORD dwStart = GetTickCount();


    //先按时间过滤
    if(pAttack->dwStrikeId > 0xffff)
    {
        if(pAttack->dwStrikeId != old1.dwStrikeId)
        {

            //if (_event.size() != 0)
    //{
            //  TRACE("_event.size()");
            //}
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
            dwEnd = GetTickCount(); //记录这次处理技能的时间
        }
        else
        {
            //技能相等， 因为确实有两个连续释放的技能， 但是间隔2秒左右
            //也需要应对， 所以判断， 如果相等并且和上次释放间隔2秒也处理
            if((dwStart - dwEnd) > 2000)
            {
                m_Mutex.Lock();
                _event.push_front(*pAttack);
                m_Mutex.Unlock();
            }
        }
    }
}

void CombatBoss::SetName(const wchar_t* name)
{
    m_name = name;
}