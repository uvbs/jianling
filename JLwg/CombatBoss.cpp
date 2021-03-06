// ombatBoss.cpp: implementation of the CombatBoss class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "jlwg.h"
#include "GamecallEx.h"
#include "CombatBoss.h"

#include <iostream>
#include <fstream>
#include <direct.h>
#include <algorithm>
#include <map>

using namespace std;


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
//1 杀怪完
//2 没找到怪
//3 死亡
int CombatBoss::run()
{

	DWORD dwRet = 0;
    DWORD MaxHealth = 0;//GetPlayerMaxHealth();
    DWORD Health = 0;//GetPlayerHealth();
    DWORD percent = 0;//Health * 100 / MaxHealth;
    DWORD My_id = 0;
    TRACE(_T("准备打BOSS"));
    //hook怪物技能, 设置回调
    GameHook::GetInstance()->SetCombatSink(this);


    //获得call
    GamecallEx* pCall = GamecallEx::GetInstance();


    DWORD Cs_86 = 0;
    BOOL Xiezi_flag = FALSE;
    //ObjectNode* pNode;
    fPosition mypos;
    fPosition tarpos;
    My_id = pCall->GetPlayerID();
    TRACE("要打的BOSS名:%s", m_name.c_str());
    ObjectNode* pBossNode = pCall->GetObjectByName(m_name.c_str(), 0);
    if(pBossNode == NULL)
    {
        TRACE(_T("没找到boss"));
        return 2;
    }

    pCall->NewSpend(3);
    pCall->Stepto(pBossNode);
    pCall->NewSpend(1);

    //攻击循环
    while(1)
    {

        if(pCall->GetPlayerHealth() <= 0)
        {
            TRACE(_T("%s: 人物死亡了"), FUNCNAME);
			dwRet = 3;
			break;
        }


        if(pCall->GetObjectHP(pBossNode->ObjAddress) == -1 || pCall->GetObjectHP(pBossNode->ObjAddress) == 0)
        {
            TRACE(_T("%s: 血量判断怪死了"), FUNCNAME);
			dwRet = 1;
			break;
            return 1;
        }

        if(pCall->GetObjectPos(pBossNode, &tarpos) == FALSE)
        {
            TRACE(_T("%s: 坐标判断怪死了"), FUNCNAME);
			dwRet = 1;
			break;
        }

		if(pCall->GetObjectPos(pBossNode, &tarpos) == 1000)
		{
			TRACE(_T("%s: 坐标判断怪死了"), FUNCNAME);
			dwRet = 1;
			break;
		}


        //这个距离判断不太通用, 假设怪物第血量会快速逃脱
        //此时正好判断到距离, 判断成死了
        pCall->GetPlayerPos(&mypos);
        DWORD dis = (DWORD)pCall->CalcC(tarpos, mypos);
        if(dis > CAN_OPERATOR)
        {
            pCall->NewSpend(4);
            pCall->Stepto(tarpos.y - 50, tarpos.x - 50, tarpos.z, 10, CAN_OPERATOR, 5000, FALSE);
            pCall->NewSpend(1);
        }

        MaxHealth = pCall->GetPlayerMaxHealth();
        Health = pCall->GetPlayerHealth();
        percent = Health * 100 / MaxHealth;



        //事件列表空?


        //这里需要同步
        if(m_event.dwStrikeId != 0)
        {

            TRACE(_T("-----技能ID:%d"), m_event.dwStrikeId);

            switch(m_event.dwStrikeId)
            {
            //对应boss技能

            //武神塔2层
            case 5190087:
                {
                    pCall->TurnTo(pBossNode);
                    TRACE(_T("5190087"));
                    pCall->Kill_Tab(0x5dc1);
                    pCall->Kill_Tab(0x5dca, 15);
                    pCall->Kill_Tab(0x5dc1);
                    pCall->Attack(0x5dca);
                    break;
                }
            case 5190071:
                {
                    TRACE(_T("5190071"));
                    if(percent < 70)
                    {
                        if(pCall->isStrikeCd(0x5DFC))
                        {
                            pCall->Attack(0x5DFC);
                            pCall->TurnTo(pBossNode);
                            Sleep(800);
                            while(pCall->isStrikeCd(0x1F5))
                            {
                                pCall->sendcall(id_msg_attack, (LPVOID)0x5ECE);
                            }
                        }
                    }
                    else
                    {
                        pCall->Kill_Tab(0x5dca, 15);
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
                    pCall->sendcall(id_msg_attack, (LPVOID)0x5dc1);
                    pCall->Attack(0x5dca);
                    break;
                }
            case 5511314:
                {
                    pCall->sendcall(id_msg_attack, (LPVOID)0x5dc1);
                    pCall->Kill_Tab(0x5E1B, 25);
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
                    pCall->Kill_Tab(0x5dca, 15);
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
                    if(percent < 70)
                    {
                        if(pCall->isStrikeCd(0x5DFC))
                        {
                            pCall->Attack(0x5DFC);
                            pCall->TurnTo(pBossNode);
                            Sleep(800);
                            while(pCall->isStrikeCd(0x1F5))
                            {
                                pCall->sendcall(id_msg_attack, (LPVOID)0x5ECE);
                            }
                        }
                    }
                    else
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


            //鬼门关万魂
            case 5902311:
                {
                    if(pCall->GetObjectTargetId(pBossNode->ObjAddress) == My_id)
                    {
                        TRACE(_T("2311-0x5dc1"));
                        pCall->sendcall(id_msg_attack, (LPVOID)0x5dc1);
                        TRACE(_T("2311-0x5dca"));
                        pCall->Kill_Tab(0x5dca, 11);
                        //}
                    }
                    else
                    {
                        pCall->SteptoBack(pBossNode);
                        pCall->TurnTo(pBossNode);
                    }
                    //}
                    break;
                }
            case 5902312:
                {
                    if(pCall->GetObjectTargetId(pBossNode->ObjAddress) == My_id)
                    {
                        pCall->sendcall(id_msg_attack, (LPVOID)0x5dc1);
                        pCall->Kill_Tab(0x5dca, 11);
                    }
                    else
                    {
                        pCall->SteptoBack(pBossNode);
                        pCall->TurnTo(pBossNode);
                    }

                    break;
                }
            case 5902313:
                {

                    if(pCall->GetObjectTargetId(pBossNode->ObjAddress) == My_id)
                    {
                        pCall->sendcall(id_msg_attack, (LPVOID)0x5dc1);
                        pCall->Kill_Tab(0x5dca, 11);
                    }
                    else
                    {
                        pCall->SteptoBack(pBossNode);
                        pCall->TurnTo(pBossNode);
                    }

                    break;
                }
            case 5902314:
                {
                    if(percent < 70)
                    {
                        if(pCall->isStrikeCd(0x5DFC))
                        {
                            pCall->Attack(0x5DFC);
                            pCall->TurnTo(pBossNode);
                            Sleep(800);
                            while(pCall->isStrikeCd(0x1F5))
                            {
                                pCall->sendcall(id_msg_attack, (LPVOID)0x5ECE);
                            }
                        }
                    }
                    else
                    {
                        if(pCall->GetObjectTargetId(pBossNode->ObjAddress) == My_id)
                        {
                            pCall->sendcall(id_msg_attack, (LPVOID)0x5dc1);
                            pCall->Kill_Tab(0x5dca, 11);
                        }
                        else
                        {
                            pCall->SteptoBack(pBossNode);
                            pCall->TurnTo(pBossNode);
                        }
                    }
                    break;
                }
            case 5902315:
                {
                    if(pCall->isStrikeCd(0x5e60))
                    {
                        pCall->Kill_Tab(0x5e60);
                    }
                    break;
                }
            case 5902320:
                {
                    //召唤小怪,不管他.
                    break;
                }
            case 5902319:
                {
                    pCall->TurnTo(pBossNode);
                    pCall->sendcall(id_msg_attack, (LPVOID)0x5dc1);
                    if(percent < 70)
                    {
                        if(pCall->isStrikeCd(0x5DFC))
                        {
                            pCall->Attack(0x5DFC);
                            pCall->TurnTo(pBossNode);
                            Sleep(800);
                            while(pCall->isStrikeCd(0x1F5))
                            {
                                pCall->sendcall(id_msg_attack, (LPVOID)0x5ECE);
                            }
                        }
                    }
                    else
                    {
                        if(pCall->GetObjectTargetId(pBossNode->ObjAddress) == My_id)
                        {
                            if(pCall->GetPlayerMana() > 60)
                            {
                                pCall->Kill_Tab(0x5dca, 11);
                            }
                            else
                            {
                                pCall->sendcall(id_msg_attack, (LPVOID)0x5dc1);
                                pCall->Kill_Tab(0x5dca, 11);
                            }
                        }
                        else
                        {
                            pCall->SteptoBack(pBossNode);
                        }
                    }
                    break;
                }
            case 5902318:
                {
                    if(percent < 70)
                    {
                        if(pCall->isStrikeCd(0x5DFC))
                        {
                            pCall->Attack(0x5DFC);
                            pCall->TurnTo(pBossNode);
                            Sleep(800);
                            while(pCall->isStrikeCd(0x1F5))
                            {
                                pCall->sendcall(id_msg_attack, (LPVOID)0x5ECE);
                            }
                        }
                    }
                    else
                    {
                        TRACE(_T("万魂范围攻击"));
                        pCall->TurnTo(pBossNode);
						Sleep(300);
                        //pCall->sendcall(id_msg_attack, (LPVOID)0x5DC1);
                        if(pCall->isStrikeCd(0x5DF2))
                        {
                            pCall->Kill_Tab(0x5DF2, 5);
                            pCall->sendcall(id_msg_attack, (LPVOID)0x5E1A);
                        }
                        else if(pCall->isStrikeCd(0x5e74))
                        {
                            pCall->Kill_Tab(0x5e74, 5);
                        }
                        else if(pCall->isStrikeCd(0x5E1B))
                        {
                            pCall->Kill_Tab(0x5E1B, 20);
                        }

                        else
                        {
                            pCall->Kill_Tab(0x5dca, 11);
                            pCall->sendcall(id_msg_attack, (LPVOID)0x5dc1);
                        }
                    }
                    break;
                }
            case 5902316:
                {
                    //if(percent < 70)
                    //{
                    //    if(pCall->isStrikeCd(0x5DFC))
                    //    {
                    //        pCall->Attack(0x5DFC);
                    //        pCall->TurnTo(pBossNode);
                    //        Sleep(800);
                    //        while(pCall->isStrikeCd(0x1F5))
                    //        {
                    //            pCall->sendcall(id_msg_attack, (LPVOID)0x5ECE);
                    //        }
                    //    }
                    //}
                    //else
                    //{
                    if(pCall->GetObjectTargetId(pBossNode->ObjAddress) == My_id)
                    {
                        if(pCall->GetPlayerMana() > 60)
                        {
                            pCall->Kill_Tab(0x5dca, 11);
                        }
                        else
                        {
                            pCall->Kill_Tab(0x5dca, 11);
                            pCall->sendcall(id_msg_attack, (LPVOID)0x5dc1);
                        }
                    }
                    else
                    {
                        pCall->SteptoBack(pBossNode);
                    }
                    //}
                    break;
                }
            case 5902392:
                {
                    //这不是万魂的ID了退
                    return 1;
                }
            case 5902398:
                {
                    //这不是万魂的ID了退
                    return 1;
                }
            case 5100600:
                {
                    //这不是万魂的ID了退
                    return 1;
                }
            case 5100601:
                {
                    //这不是万魂的ID了退
                    return 1;
                }

            //鬼门关万魂

            //鬼门关鬼神泣
            case 5902376:
                {
                    if(pCall->GetObjectTargetId(pBossNode->ObjAddress) == My_id)
                    {
                        if(pCall->GetPlayerMana() > 60)
                        {
                            pCall->Kill_Tab(0x5dca, 11);
                        }
                        else
                        {
                            pCall->sendcall(id_msg_attack, (LPVOID)0x5dc1);
                            pCall->Kill_Tab(0x5dca, 11);
                        }
                    }
                    else
                    {
                        pCall->SteptoBack(pBossNode);
                    }
                    break;
                }
            case 5902377:
                {
                    pCall->SteptoBack(pBossNode);
                    break;
                }
            case 5902379:
                {
                    pCall->Attack(0x5dc1);
                    pCall->Kill_Tab(0x5dca, 11);
                    pCall->Kill_Tab(0x5dca, 11);
                    break;
                }
            case 5902380:
                {
                    if(pCall->GetObjectTargetId(pBossNode->ObjAddress) == My_id)
                    {
                        if(pCall->GetPlayerMana() > 60)
                        {
                            pCall->Kill_Tab(0x5dca, 11);
                        }
                        else
                        {
                            pCall->Kill_Tab(0x5dca, 11);
                            pCall->sendcall(id_msg_attack, (LPVOID)0x5dc1);
                        }
                    }
                    else
                    {
                        pCall->SteptoBack(pBossNode);
                    }
                    break;
                }
            case 5902381:
                {
                    TRACE(_T("进81，退"));
                    break;
                }
            case 5902382:
                {
                    pCall->TurnTo(pBossNode);
                    pCall->Attack(0x5dc1);
                    pCall->Attack(0x5dc1);
                    pCall->Attack(0x5dc1);
                    if(pCall->isStrikeCd(0x5E1B))
                    {
                        pCall->TurnTo(pBossNode);
                        pCall->Kill_Tab(0x5E1B, 25);
                    }
                    else if(pCall->isStrikeCd(0x5DF2))
                    {
                        pCall->TurnTo(pBossNode);
                        pCall->Attack(0x5e6a);
                        pCall->Kill_Tab(0x5DF2, 10);
                        pCall->Kill_Tab(0x5E1A, 5);
                    }
                    else
                    {
                        pCall->Kill_Tab(0x5dca, 11);
                        pCall->Kill_Tab(0x5dca, 11);
                    }
                    break;
                }
            //鬼门关鬼神泣

            //爆魔人
            case 5902300:
                {
                    //pCall->TurnTo(pBossNode);
                    //pCall->Attack(0x5dc1);
                    //if(pCall->GetRangeMonsterCount() > 1)
                    //{
                    //    pCall->Kill_Tab(0x5dca, 15);
                    //    pCall->Kill_Tab(0x5dca, 15);
                    //}
                    //else
                    //{
                    if(percent < 70)
                    {
                        if(pCall->isStrikeCd(0x5DFC))
                        {
                            pCall->Attack(0x5DFC);
                            pCall->TurnTo(pBossNode);
                            Sleep(800);
                            while(pCall->isStrikeCd(0x1F5))
                            {
                                pCall->sendcall(id_msg_attack, (LPVOID)0x5ECE);
                            }
                        }
                    }
                    else
                    {
                        pCall->TurnTo(pBossNode);
                        pCall->Attack(0x5dc1);
                        pCall->Attack(0x5dc1);
                        pCall->Attack(0x5dc1);
                        pCall->TurnTo(pBossNode);
                        if(pCall->isStrikeCd(0x5E1B))
                        {
                            pCall->Kill_Tab(0x5E1B, 20);
                        }
                        else if(pCall->isStrikeCd(0x5DF2))
                        {
                            pCall->Kill_Tab(0x5DF2, 5);
                            pCall->Attack(0x5E1A);
                        }
                        else
                        {
                            pCall->Kill_Tab(0x5dca, 11);
                            pCall->Kill_Tab(0x5dca, 11);
                        }
                    }
                    //}
                    break;
                }
            case 5902301:
                {
                    if(pCall->GetObjectTargetId(pBossNode->ObjAddress) == My_id)
                    {
                        pCall->Kill_Tab(0x5dca, 11);
                        pCall->sendcall(id_msg_attack, (LPVOID)0x5dc1);
                    }
                    else
                    {
                        pCall->SteptoBack(pBossNode);
                    }
                    break;
                }
            case 5902303:
                {
                    if(pCall->GetRangeMonsterCount() > 1)
                    {
                        pCall->Kill_Tab(0x5dca, 11);
                        pCall->sendcall(id_msg_attack, (LPVOID)0x5dc1);
                    }
                    break;
                }
            case 5902397:
                {
                    if(pCall->GetObjectTargetId(pBossNode->ObjAddress) == My_id)
                    {
                        pCall->Kill_Tab(0x5dca, 11);
                        pCall->sendcall(id_msg_attack, (LPVOID)0x5dc1);
                    }
                    else
                    {
                        pCall->SteptoBack(pBossNode);
                    }
                    break;
                }
            case 5902304:
                {
                    if(pCall->isStrikeCd(0x5e60))
                    {
                        pCall->Kill_Tab(0x5e60);
                    }
                    else
                    {
                        pCall->Attack(0x5e6a);
                    }
                    pCall->Kill_Tab(0x5dca, 11);
                    break;
                }
            //爆魔人


            //鬼门关最终BOSS
            case 5902383:
                {
                    if(percent < 70)
                    {
                        if(pCall->isStrikeCd(0x5DFC))
                        {
                            pCall->Attack(0x5DFC);
                            pCall->TurnTo(pBossNode);
                            Sleep(800);

                            while(pCall->isStrikeCd(0x1F5))
                            {
                                pCall->sendcall(id_msg_attack, (LPVOID)0x5ECE);
                            }
                        }
                    }
                    else
                    {
                        pCall->Kill_Tab(0x5dca, 1);
                        //pCall->sendcall(id_msg_attack, (LPVOID)0x5dca);
                    }
                    break;
                }

            case 5902384:
                {
                    pCall->SteptoBack(pBossNode);
                    break;
                }
            case 5902385:
                {
                    pCall->SteptoBack(pBossNode);
                    break;
                }
            case 5902386:
                {
                    pCall->SteptoBack(pBossNode);
                    break;
                }
            case 5902388:
                {
                    if(pCall->GetObjectTargetId(pBossNode->ObjAddress) == My_id)
                    {
                        pCall->Kill_Tab(0x5dca, 11);
                    }
                    else
                    {
                        pCall->SteptoBack(pBossNode);
                    }
                    break;
                }
            case 5902389:
                {
                    pCall->Kill_Tab(0x5dca);
                    break;
                }
            case 5902391:
                {
                    //pCall->Attack(0x5dc1);
                    pCall->Stepto(pBossNode);
                    //pCall->Attack(0x5dc1);
                    pCall->ChangeZ_Status(TRUE);
                    pCall->ChangeHeight(0);
                    Sleep(6400);
                    pCall->ChangeZ_Status(FALSE);
                    pCall->ChangeHeight(-1071);
                    pCall->Kill_Tab(0x5dca, 10);

                    //              pCall->Stepto(pBossNode);
                    //              if(Xiezi_flag == FALSE)
                    //              {
                    //TRACE(_T("沒打小蠍子,準備飛天"));
                    //                  pCall->ChangeZ_Status(TRUE);
                    //                  pCall->ChangeHeight(-500);
                    //                  //MessageBox(L"摇奖完", L"装八卦", MB_OK);
                    //Sleep(9500);
                    //                  pCall->ChangeZ_Status(FALSE);
                    //              }
                    //              else
                    //              {
                    //pCall->Attack(0x5dc1);
                    //pCall->Attack(0x5dc1);
                    //pCall->Attack(0x5dc1);
                    //                  Xiezi_flag = FALSE;
                    //                  if(pCall->isStrikeCd(0x5E1B))
                    //                  {
                    //                      TRACE("准备使用C");
                    //                      pCall->Kill_Tab(0x5E1B);
                    //                  }
                    //                  if(pCall->isStrikeCd(0x5DF2))
                    //                  {
                    //                      TRACE("准备使用2");
                    //                      Sleep(500);
                    //                      pCall->Kill_Tab(0x5DF2, 10);
                    //                      Sleep(500);
                    //                      TRACE("准备使用SS");
                    //                      pCall->Kill_Tab(0x5e6a, 10);
                    //                      /*Sleep(1000);
                    //                      TRACE("准备使用e");
                    //                      pCall->Kill_Tab(0x5E1A, 8);*/
                    //                  }
                    //                  else
                    //                  {
                    //                      TRACE("没其他技能可用，准备使用tab");
                    //                      if(pCall->isStrikeCd(0x5e60))
                    //                      {
                    //                          pCall->Kill_Tab(0x5e60);
                    //                      }
                    //                      TRACE("tab1");
                    //                      pCall->Kill_Tab(0x5dca, 15);
                    //                      if(pCall->isStrikeCd(0x5e60))
                    //                      {
                    //                          pCall->Kill_Tab(0x5e60);
                    //                      }
                    //                      TRACE("tab2");
                    //                      pCall->Kill_Tab(0x5dca, 15);
                    //                      if(pCall->isStrikeCd(0x5e60))
                    //                      {
                    //                          pCall->Kill_Tab(0x5e60);
                    //                      }
                    //                      TRACE("tab3");
                    //                      pCall->Kill_Tab(0x5dca, 15);
                    //                  }
                    //              }
                    break;
                }
            //鬼门关最终BOSS

            //雪人洞雪人

            //雪人洞雪人



            default:
                {
                    //杀怪
                    TRACE(_T("attack id: %d"), m_event.dwStrikeId);
                    if(wcscmp(m_name.c_str(), L"馬柴達") == 0  //1层小怪
                            || wcscmp(m_name.c_str(), L"舒藝") == 0 //1层小怪
                            || wcscmp(m_name.c_str(), L"無名") == 0) //3层BOSS
                    {
                        if(percent < 70)
                        {
                            if(pCall->isStrikeCd(0x5DFC))
                            {
                                pCall->Attack(0x5DFC);
                                pCall->TurnTo(pBossNode);
                                Sleep(800);
                                while(pCall->isStrikeCd(0x1F5))
                                {
                                    pCall->sendcall(id_msg_attack, (LPVOID)0x5ECE);
                                }
                            }
                        }
                    }

                    if(pCall->GetObjectTargetId(pBossNode->ObjAddress) == My_id)
                    {
                        pCall->sendcall(id_msg_attack, (LPVOID)0x5dc1);
                        pCall->Kill_Tab(0x5dca, 15);
                    }
                    else
                    {
                        pCall->SteptoBack(pBossNode);
                    }

                    break;
                }
            }
            TRACE("处理完毕");
            m_event.dwStrikeId = 0;
        }
        else
        {
            //空闲时动作, 一般的释放技能

            //5E60->5EA6->5EB0->5E9C
            if(pCall->isStrikeCd(0x5e60))
            {
                pCall->sendcall(id_msg_attack, (LPVOID)0x5e60);
            }
            if(pCall->isStrikeCd(0x5ea6))
            {
                pCall->sendcall(id_msg_attack, (LPVOID)0x5ea6);
            }

            pCall->TurnTo(pBossNode);

            if(percent < 90)
            {
                if(pCall->isStrikeCd(0x5E24))
                {
                    pCall->sendcall(id_msg_attack, (LPVOID)0x5E24);
                }
            }

            pCall->GetHealth(60);

            if(pCall->GetRangeMonsterCount() > 1)
            {
                if(pCall->isStrikeCd(0x5DE8))
                {
                    pCall->sendcall(id_msg_attack, (LPVOID)0x5DE8);
                }
                else if(pCall->isStrikeCd(0x5E06))
                {
                    pCall->sendcall(id_msg_attack, (LPVOID)0x5E06);
                }
            }
            //事件发送过快导致执行对应动作时为时已晚怎么办, 这个暂时不考虑
            //计算机没来得及处理人更不可能了
            //Sleep(10);
            if(pCall->GetPlayerMana() > 70)
            {
                pCall->sendcall(id_msg_attack, (LPVOID)0x5dde);
            }
            pCall->sendcall(id_msg_attack, (LPVOID)0x5dc1);
        }


    }

	//取消回调
    GameHook::GetInstance()->SetCombatSink(NULL);

	return dwRet;
}


//这里回调不能阻塞的.
//游戏hook那里回调过来的, 所以这里也不能执行耗时的操作.
//也不能放技能. 这里只把boss攻击当作事件放到一个队列
void CombatBoss::NotifyMonsterAttack(MONSTERATAACK* pAttack)
{

    static MONSTERATAACK old1;
    static DWORD dwEnd = GetTickCount();
    DWORD dwStart = GetTickCount();
	static MONSTERATAACK attackid;
	attackid = *pAttack;
    static int notProcess = 0; //不处理次数
    try
    {
        //先按时间过滤
        if(pAttack->dwStrikeId <= 65535)return;
        if(pAttack->dwStrikeId >= 268435456) return;

        if(pAttack->dwStrikeId != old1.dwStrikeId)
        {
            m_event.dwObj = pAttack->dwObj;
            m_event.dwStrikeId = pAttack->dwStrikeId;

            old1 = *pAttack;
            notProcess = 0;
        }
        else
        {
            //上个id
            notProcess++;


			TRACE(_T("pAttack->dwStrikeId:%d"),attackid.dwStrikeId);
            //没找到
			if (m_JnCounts.find(attackid.dwStrikeId) == m_JnCounts.end())
			{
				//TRACE("没有记录的技能ID,%d",pAttack->dwStrikeId);
			}else
			{
				    m_event.dwObj = attackid.dwObj;
				    m_event.dwStrikeId = attackid.dwStrikeId;
			}
            //if(m_JnCounts.find(pAttack->dwStrikeId) == m_JnCounts.end())
            //{
            //    //这是没有记录的id
            //    //TRACE("没有记录的技能ID,%d",pAttack->dwStrikeId);
            //}
            //else if(m_JnCounts[pAttack->dwStrikeId] == notProcess)
            //{
            //    //TRACE("ID已勾:%d",pAttack->dwStrikeId);
            //    m_event.dwObj = pAttack->dwObj;
            //    m_event.dwStrikeId = pAttack->dwStrikeId;
            //}
            //else
            //{	
            //    //TRACE("notProcess,%d",notProcess);
            //}
        }

    }
	catch(exception ex)
    {
        TRACE(_T("m_JnCounts.find-error"));
		return;
    }
}

void CombatBoss::LoadCountsData()
{
    try
    {

        char szExe[MAX_PATH] = {0};
        GetModuleFileNameA(AfxGetInstanceHandle(), szExe, MAX_PATH);
        PathRemoveFileSpecA(szExe);
        PathAppendA(szExe, "配置");
        if(!PathFileExistsA(szExe))
        {
            TRACE(_T("没有%s"), szExe);
            return;
        }


        PathAppendA(szExe, "jnCount.txt");


        //不存在, 新建
        if(!PathFileExistsA(szExe))
        {
            TRACE(_T("没有%s"), szExe);
            return;
        }


        fstream file1;
        file1.open(szExe);

        int i;
        int i1;
        while(!file1.eof())
        {
            file1 >> i;
            file1 >> i1;
			TRACE(_T("技能i: %d"), i);
			TRACE(_T("技能i1: %d"), i1);
            //m_JnCounts[i] = i1;
			m_JnCounts.insert(pair<int,int>(i,i1));
        }
        TRACE(_T("技能数量: %d"), m_JnCounts.size());
    }
    catch(...)
    {
		TRACE(_T("读文件报错"));
    }

}


void CombatBoss::SetName(const wchar_t* name)
{
    TRACE(_T("SetName: %s"), name);
    m_name = name;
}