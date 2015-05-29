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


//����: ��ʱ�Ĳ���ʱ, �����ʱ�������¼�֪ͨ��ô��
//��ʵĿǰ��ʱ�Ĳ���, ������·������, �����������ͬ������, ��Ҫһ�ַ�ʽ���
//����Ŀ�ĵص�֪ͨ, Ŀǰ����: һֱ����, ����ŷ���. ��˵���Ľ�����Ǻ�������
//��Ҫһ���첽����, ��ִ������֪ͨ
void CombatBoss::run()
{

    DWORD MaxHealth = 0;//GetPlayerMaxHealth();
    DWORD Health = 0;//GetPlayerHealth();
    DWORD percent = 0;//Health * 100 / MaxHealth;
    DWORD My_id = 0;
    TRACE(_T("׼����BOSS"));
    //hook���＼��, ���ûص�
    GameHook::GetInstance()->SetCombatSink(this);


    //���call
    GamecallEx* pCall = GamecallEx::GetInstance();


    DWORD Cs_86 = 0;
    BOOL Xiezi_flag = FALSE;
    //ObjectNode* pNode;
    fPosition mypos;
    fPosition tarpos;
    My_id = pCall->GetPlayerID();
    TRACE("Ҫ���BOSS��:%s", m_name.c_str());
    ObjectNode* pBossNode = pCall->GetObjectByName(m_name.c_str(), 0);
    if(pBossNode == NULL)
    {
        TRACE(_T("û�ҵ�boss"));
        return;
    }

    pCall->NewSpend(3);
    pCall->Stepto(pBossNode);
    pCall->NewSpend(1);

    //����ѭ��
    while(1)
    {

        if(pCall->GetPlayerHealth() <= 0)
        {
            TRACE(_T("%s: ����������"), FUNCNAME);
            break;
        }


        if(pCall->GetObjectHP(pBossNode->ObjAddress) == -1 || pCall->GetObjectHP(pBossNode->ObjAddress) == 0)
        {
            TRACE(_T("%s: Ѫ���жϹ�����"), FUNCNAME);
            break;
        }

        if(pCall->GetObjectPos(pBossNode, &tarpos) == FALSE)
        {
            TRACE(_T("%s: �����жϹ�����"), FUNCNAME);
            break;
        }


        //��������жϲ�̫ͨ��, ��������Ѫ�����������
        //��ʱ�����жϵ�����, �жϳ�����
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



        //�¼��б��?


        //������Ҫͬ��
        if(m_event.dwStrikeId != 0)
        {

            TRACE(_T("-----����ID:%d"), m_event.dwStrikeId);

            switch(m_event.dwStrikeId)
            {
            //��Ӧboss����

            //������2��
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
                    TRACE(_T("��������88"));
                    pCall->TurnTo(pBossNode);
                    break;
                }
            case 5190089:
                {
                    pCall->SteptoBack(pBossNode);
                    TRACE(_T("��������89"));
                    pCall->TurnTo(pBossNode);
                    break;
                }
            //������2�����


            //������3��
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

            //������3�����

            //������4��
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
            //������4�����


            //���Ź����
            case 5902311:
                {
                    if(pCall->GetObjectTargetId(pBossNode->ObjAddress) == My_id)
                    {
                        TRACE(_T("2311-0x5dc1"));
                        pCall->sendcall(id_msg_attack, (LPVOID)0x5dc1);
                        TRACE(_T("2311-0x5dca"));
                        pCall->Kill_Tab(0x5dca, 15);
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
                        pCall->Kill_Tab(0x5dca, 15);
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
                        pCall->Kill_Tab(0x5dca, 15);
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
                            pCall->Kill_Tab(0x5dca, 15);
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
                    //�ٻ�С��,������.
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
                                pCall->Kill_Tab(0x5dca, 15);
                            }
                            else
                            {
                                pCall->sendcall(id_msg_attack, (LPVOID)0x5dc1);
                                pCall->Kill_Tab(0x5dca, 15);
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
                        TRACE(_T("��귶Χ����"));
                        pCall->TurnTo(pBossNode);
                        //pCall->sendcall(id_msg_attack, (LPVOID)0x5DC1);
                        if(pCall->isStrikeCd(0x5E1B))
                        {
                            TRACE(_T("0x5E1B"));
                            pCall->Kill_Tab(0x5E1B, 25);
                        }
                        else if(pCall->isStrikeCd(0x5DF2))
                        {
                            pCall->Kill_Tab(0x5DF2, 10);
                            pCall->sendcall(id_msg_attack, (LPVOID)0x5E1A);
                        }
                        else
                        {
                            pCall->Kill_Tab(0x5dca, 15);
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
                            pCall->Kill_Tab(0x5dca, 15);
                        }
                        else
                        {
                            pCall->Kill_Tab(0x5dca, 15);
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
                    //�ⲻ������ID����
                    return;
                }
            case 5902398:
                {
                    //�ⲻ������ID����
                    return;
                }
            case 5100600:
                {
                    //�ⲻ������ID����
                    return;
                }
            case 5100601:
                {
                    //�ⲻ������ID����
                    return;
                }

            //���Ź����

            //���Źع�����
            case 5902376:
                {
                    if(pCall->GetObjectTargetId(pBossNode->ObjAddress) == My_id)
                    {
                        if(pCall->GetPlayerMana() > 60)
                        {
                            pCall->Kill_Tab(0x5dca, 15);
                        }
                        else
                        {
                            pCall->sendcall(id_msg_attack, (LPVOID)0x5dc1);
                            pCall->Kill_Tab(0x5dca, 15);
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
					pCall->Attack(0x5dc1);
                    if(pCall->GetObjectTargetId(pBossNode->ObjAddress) == My_id)
                    {
                        //if(pCall->GetPlayerMana() > 60)
                        //{
                        //    pCall->Kill_Tab(0x5dca, 15);
                        //}
                        //else
                        //{
                        pCall->sendcall(id_msg_attack, (LPVOID)0x5dc1);
                        pCall->Kill_Tab(0x5dca, 14);
                        pCall->Kill_Tab(0x5dca, 15);
                        //}
                    }
                    else
                    {
                        pCall->SteptoBack(pBossNode);
                    }
                    //}
                    break;
                }
            case 5902379:
                {
                    pCall->Attack(0x5dc1);
                    pCall->Attack(0x5dc1);
                    if(pCall->GetObjectTargetId(pBossNode->ObjAddress) == My_id)
                    {
                        pCall->Kill_Tab(0x5dca, 15);
                        pCall->Kill_Tab(0x5dca, 15);
                    }
                    break;
                }
            case 5902380:
                {
                    if(pCall->GetObjectTargetId(pBossNode->ObjAddress) == My_id)
                    {
                        if(pCall->GetPlayerMana() > 60)
                        {
                            pCall->Kill_Tab(0x5dca, 15);
                        }
                        else
                        {
                            pCall->sendcall(id_msg_attack, (LPVOID)0x5dc1);
                            pCall->Kill_Tab(0x5dca, 15);
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
                    TRACE(_T("��81����"));
                    break;
                }
            case 5902382:
                {
                    pCall->TurnTo(pBossNode);
                    pCall->Attack(0x5dc1);
                    pCall->Attack(0x5dc1);
                    pCall->Attack(0x5dc1);
					pCall->Attack(0x5dc1);
                    if(pCall->isStrikeCd(0x5E1B))
                    {
                        pCall->Kill_Tab(0x5E1B, 25);
                    }
                    else if(pCall->isStrikeCd(0x5DF2))
                    {
                        pCall->Attack(0x5e6a);
                        pCall->Kill_Tab(0x5DF2, 10);
                        pCall->Kill_Tab(0x5E1A, 5);
                    }
                    else
                    {
                        pCall->Kill_Tab(0x5dca, 15);
                        pCall->Kill_Tab(0x5dca, 15);
                    }
                    break;
                }
            //���Źع�����

            //��ħ��
            case 5902300:
                {
                    pCall->TurnTo(pBossNode);
                    pCall->Attack(0x5dc1);
                    if(pCall->GetRangeMonsterCount() > 1)
                    {
                        pCall->Kill_Tab(0x5dca, 15);
                        pCall->Kill_Tab(0x5dca, 15);
                    }
                    else
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
                            pCall->TurnTo(pBossNode);
                            if(pCall->isStrikeCd(0x5E1B))
                            {
                                pCall->Attack(0x5dc1);
                                pCall->Attack(0x5dc1);
								pCall->Attack(0x5dc1);
                                pCall->Kill_Tab(0x5E1B, 25);
                            }
                            else if(pCall->isStrikeCd(0x5DF2))
                            {
                                pCall->Attack(0x5dc1);
                                pCall->Attack(0x5dc1);
								pCall->Attack(0x5dc1);
                                pCall->Kill_Tab(0x5DF2, 8);
                                pCall->Attack(0x5E1A);
                            }
                            else
                            {
                                pCall->Kill_Tab(0x5dca, 15);
                                pCall->Kill_Tab(0x5dca, 15);
                            }
                        }
                    }
                    break;
                }
            case 5902301:
                {
                    if(pCall->GetObjectTargetId(pBossNode->ObjAddress) == My_id)
                    {
                        pCall->Kill_Tab(0x5dca, 15);
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
                        pCall->Kill_Tab(0x5dca, 15);
                        pCall->sendcall(id_msg_attack, (LPVOID)0x5dc1);
                    }
                    break;
                }
            case 5902397:
                {
                    if(pCall->GetObjectTargetId(pBossNode->ObjAddress) == My_id)
                    {
                        pCall->Kill_Tab(0x5dca, 15);
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
                    pCall->Kill_Tab(0x5dca, 15);
                    break;
                }
            //��ħ��


            //���Ź�����BOSS
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
						pCall->Kill_Tab(0x5dca, 5);
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
					pCall->Attack(0x5dc1);
					if(pCall->GetObjectTargetId(pBossNode->ObjAddress) == My_id)
					{
						pCall->Kill_Tab(0x5dca, 15);
					}else
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
					pCall->Attack(0x5dc1);
					pCall->ChangeZ_Status(TRUE);
					pCall->ChangeHeight(0);
					Sleep(6700);
					pCall->ChangeZ_Status(FALSE);
					pCall->ChangeHeight(-1071);
					pCall->Kill_Tab(0x5dca,15);

      //              pCall->Stepto(pBossNode);
      //              if(Xiezi_flag == FALSE)
      //              {
						//TRACE(_T("�]��Сϐ��,�ʂ��w��"));
      //                  pCall->ChangeZ_Status(TRUE);
      //                  pCall->ChangeHeight(-500);
      //                  //MessageBox(L"ҡ����", L"װ����", MB_OK);
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
      //                      TRACE("׼��ʹ��C");
      //                      pCall->Kill_Tab(0x5E1B);
      //                  }
      //                  if(pCall->isStrikeCd(0x5DF2))
      //                  {
      //                      TRACE("׼��ʹ��2");
      //                      Sleep(500);
      //                      pCall->Kill_Tab(0x5DF2, 10);
      //                      Sleep(500);
      //                      TRACE("׼��ʹ��SS");
      //                      pCall->Kill_Tab(0x5e6a, 10);
      //                      /*Sleep(1000);
      //                      TRACE("׼��ʹ��e");
      //                      pCall->Kill_Tab(0x5E1A, 8);*/
      //                  }
      //                  else
      //                  {
      //                      TRACE("û�������ܿ��ã�׼��ʹ��tab");
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
            //���Ź�����BOSS

            //ѩ�˶�ѩ��

            //ѩ�˶�ѩ��



            default:
                {
                    //ɱ��
                    TRACE(_T("attack id: %d"), m_event.dwStrikeId);
                    if(wcscmp(m_name.c_str(), L"�R���_") == 0  //1��С��
                            || wcscmp(m_name.c_str(), L"��ˇ") == 0 //1��С��
                            || wcscmp(m_name.c_str(), L"�o��") == 0) //3��BOSS
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
            TRACE("�������");
            m_event.dwStrikeId = 0;
        }
        else
        {
            //����ʱ����, һ����ͷż���

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
            //�¼����͹��쵼��ִ�ж�Ӧ����ʱΪʱ������ô��, �����ʱ������
            //�����û���ü������˸���������
            //Sleep(10);
            if(pCall->GetPlayerMana() > 70)
            {
                pCall->sendcall(id_msg_attack, (LPVOID)0x5dde);
            }
            pCall->sendcall(id_msg_attack, (LPVOID)0x5dc1);
        }


    }

//ȡ���ص�
    GameHook::GetInstance()->SetCombatSink(NULL);
}


//����ص�����������.
//��Ϸhook����ص�������, ��������Ҳ����ִ�к�ʱ�Ĳ���.
//Ҳ���ܷż���. ����ֻ��boss���������¼��ŵ�һ������
void CombatBoss::NotifyMonsterAttack(MONSTERATAACK* pAttack)
{

    static MONSTERATAACK old1;
    static DWORD dwEnd = GetTickCount();
    DWORD dwStart = GetTickCount();

    static int notProcess = 0; //���������

    //�Ȱ�ʱ�����
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
        //�ϸ�id
        notProcess++;


        //û�ҵ�
        if(m_JnCounts.find(pAttack->dwStrikeId) == m_JnCounts.end())
        {
            //����û�м�¼��id
            //TRACE("û�м�¼�ļ���ID,%d",pAttack->dwStrikeId);
        }
        else if(m_JnCounts[pAttack->dwStrikeId] == notProcess)
        {
            //TRACE("ID�ѹ�:%d",pAttack->dwStrikeId);
            m_event.dwObj = pAttack->dwObj;
            m_event.dwStrikeId = pAttack->dwStrikeId;
        }
        else
        {
            //TRACE("notProcess,%d",notProcess);
        }

    }

}

void CombatBoss::LoadCountsData()
{
    try
    {

        char szExe[MAX_PATH] = {0};
        GetModuleFileNameA(AfxGetInstanceHandle(), szExe, MAX_PATH);
        PathRemoveFileSpecA(szExe);
        PathAppendA(szExe, "����");
        if(!PathFileExistsA(szExe))
        {
            TRACE(_T("û��%s"), szExe);
            return;
        }


        PathAppendA(szExe, "jnCount.txt");


        //������, �½�
        if(!PathFileExistsA(szExe))
        {
            TRACE(_T("û��%s"), szExe);
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

            m_JnCounts[i] = i1;

            TRACE(_T("����i: %d"), i);
            TRACE(_T("����i1: %d"), i1);

        }

        TRACE(_T("��������: %d"), m_JnCounts.size());
    }
    catch(...)
    {

    }

}


void CombatBoss::SetName(const wchar_t* name)
{
    TRACE(_T("SetName: %s"), name);
    m_name = name;
}