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


    fPosition mypos;
    fPosition tarpos;
    My_id = pCall->GetPlayerID();
    ObjectNode* pBossNode = pCall->GetObjectByName(m_name.c_str(), 0);
    if(pBossNode == NULL)
    {
        TRACE(_T("û�ҵ�boss"));
        return;
    }

    pCall->NewSpend(4);
    pCall->Stepto(pBossNode);
    pCall->NewSpend(1);

//����ѭ��
    while(1)
    {

        //�˳�����
        //boss ��

        //pCall->KeyPress(82);
        //�����
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

        if(pCall->_GetObjectPos(pBossNode->ObjAddress, &tarpos) == FALSE)
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
        if(_event.size() > 0)
        {


            MONSTERATAACK ma;


            //������Ҫͬ��
            m_Mutex.Lock();
            std::list<MONSTERATAACK>::iterator it = _event.begin();

            ma = (*it);

            //����������¼�, �Ӷ���ɾ��
            //_event.erase(it);
            _event.clear();
            m_Mutex.Unlock();

            TRACE(_T("-----����ID:%d"), ma.dwStrikeId);


            switch(ma.dwStrikeId)
            {
            //��Ӧboss����

            //������2��
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
                    if(percent < 70)
                    {
                        if(pCall->isStrikeCd(0x5DFC) == FALSE)
                        {
                            pCall->Attack(0x5DFC);
                            pCall->TurnTo(pBossNode);
                            pCall->Attack(0x5ECE);
                            while(pCall->isStrikeCd(0x5DC1))
                            {
                                pCall->Attack(0x5ECE);
                            }
                        }
                    }
                    else
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
                    pCall->Attack(0x5E1B);
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
                    if(percent < 70)
                    {
                        if(pCall->isStrikeCd(0x5DFC) == FALSE)
                        {
                            pCall->Attack(0x5DFC);
                            pCall->TurnTo(pBossNode);
                            while(pCall->isStrikeCd(0x5DC1))
                            {
                                pCall->Attack(0x5ECE);
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
                    if(percent < 70)
                    {
                        if(pCall->isStrikeCd(0x5DFC) == FALSE)
                        {
                            pCall->Attack(0x5DFC);
                            pCall->TurnTo(pBossNode);
                            Sleep(500);
                            while(pCall->isStrikeCd(0x5DC1))
                            {
                                pCall->Attack(0x5ECE);
                            }
                        }
                    }
                    else
                    {
                        if(pCall->GetObjectTargetId(pBossNode->ObjAddress) == My_id)
                        {
                            pCall->Kill_Tab(0x5dca);
                        }
                        else
                        {
                            pCall->SteptoBack(pBossNode);
                            pCall->TurnTo(pBossNode);
                        }
                    }
                    break;
                }
            case 5902312:
                {
                    if(pCall->GetObjectTargetId(pBossNode->ObjAddress) == My_id)
                    {
                        pCall->Kill_Tab(0x5dca);
                    }
                    else
                    {
                        pCall->SteptoBack(pBossNode);
                    }
                    break;
                }
            case 5902313:
                {
                    if(pCall->GetObjectTargetId(pBossNode->ObjAddress) == My_id)
                    {
                        pCall->Kill_Tab(0x5dca);
                    }
                    else
                    {
                        pCall->SteptoBack(pBossNode);
                    }
                    break;
                }
            case 5902314:
                {
                    if(pCall->GetObjectTargetId(pBossNode->ObjAddress) == My_id)
                    {
                        pCall->Kill_Tab(0x5dca);
                    }
                    else
                    {
                        pCall->SteptoBack(pBossNode);
                    }
                    break;
                }
            case 5902315:
                {
                    pCall->Kill_Tab(0x5e60);
                    if(pCall->GetPlayerMana() > 60)
                    {
                        pCall->Kill_Tab(0x5dca);
                    }
                    pCall->Kill_Tab(0x5dc1);
                    break;
                }
            case 5902320:
                {
                    //�ٻ�С��,������.
                    break;
                }
            case 5902319:
                {
                    if(pCall->GetObjectTargetId(pBossNode->ObjAddress) == My_id)
                    {
                        pCall->Kill_Tab(0x5dca);
                    }
                    else
                    {
                        pCall->SteptoBack(pBossNode);
                    }
                    break;
                }
            case 5902318:
                {
                    TRACE("��귶Χ����");
                    pCall->TurnTo(pBossNode);
                    //pCall->Kill_Tab(0x5dc1);
                    if(pCall->isStrikeCd(0x5E1B) == FALSE)
                    {
                        Sleep(500);
                        pCall->Kill_Tab(0x5E1B);
                    }
                    else if(pCall->isStrikeCd(0x5DF2) == FALSE)
                    {
                        Sleep(500);
                        pCall->Kill_Tab(0x5DF2);
                    }
                    else
                    {
                        pCall->Kill_Tab(0x5dca);
                        pCall->sendcall(id_msg_attack, (LPVOID)0x5E1A);
                    }
                    //pCall->SteptoBack(pBossNode);
                    //pCall->TurnTo(pBossNode);
                    break;
                }
            case 5902316:
                {
                    if(pCall->GetObjectTargetId(pBossNode->ObjAddress) == My_id)
                    {
                        pCall->Kill_Tab(0x5dca);
                    }
                    else
                    {
                        pCall->SteptoBack(pBossNode);
                    }
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
            //���Ź����

            //���Źع�����
            case 5902376:
                {
                    if(pCall->GetObjectTargetId(pBossNode->ObjAddress) == My_id)
                    {
                        pCall->Kill_Tab(0x5dca);
                    }
                    else
                    {
                        pCall->SteptoBack(pBossNode);
                    }
                    break;
                }
            case 5902377:
                {
                    if(percent < 70)
                    {
                        if(pCall->isStrikeCd(0x5DFC) == FALSE)
                        {
                            pCall->Attack(0x5DFC);
                            Sleep(500);
                            pCall->TurnTo(pBossNode);
                            while(pCall->isStrikeCd(0x5DC1))
                            {
                                pCall->Attack(0x5ECE);
                            }
                        }
                    }
                    else
                    {
                        if(pCall->GetObjectTargetId(pBossNode->ObjAddress) == My_id)
                        {
                            pCall->Kill_Tab(0x5dca);
                        }
                        else
                        {
                            pCall->SteptoBack(pBossNode);
                        }
                    }
                    break;
                }
            case 5902379:
                {
                    if(pCall->GetObjectTargetId(pBossNode->ObjAddress) == My_id)
                    {
                        pCall->Kill_Tab(0x5dca);
                    }
                    else
                    {
                        pCall->SteptoBack(pBossNode);
                    }
                    break;
                }
            case 5902380:
                {
                    if(pCall->GetObjectTargetId(pBossNode->ObjAddress) == My_id)
                    {
                        pCall->Kill_Tab(0x5dca);
                    }
                    else
                    {
                        pCall->SteptoBack(pBossNode);
                    }
                    break;
                }
            case 5902381:
                {
                    if(pCall->GetObjectTargetId(pBossNode->ObjAddress) == My_id)
                    {
                        pCall->Kill_Tab(0x5dca);
                    }
                    else
                    {
                        pCall->SteptoBack(pBossNode);
                    }
                    break;
                }
            case 5902382:
                {
                    pCall->TurnTo(pBossNode);
                    //pCall->Kill_Tab(0x5dc1);
                    if(pCall->isStrikeCd(0x5E1B) == FALSE)
                    {
                        Sleep(2000);
                        pCall->Kill_Tab(0x5E1B);
                    }
                    else if(pCall->isStrikeCd(0x5DF2) == FALSE)
                    {
                        Sleep(2200);
                        pCall->Kill_Tab(0x5DF2);
                    }
                    else
                    {
                        pCall->Kill_Tab(0x5dca);
                        pCall->sendcall(id_msg_attack, (LPVOID)0x5E1A);
                    }
                    break;
                }
            //���Źع�����

            //��ħ��
            case 5902300:
                {
                    if(pCall->isStrikeCd(0x5DFC) == FALSE)
                    {
						TRACE("ִ��0x5DFC");
                        if(percent < 70)
                        {
                            pCall->Attack(0x5DFC);
                            pCall->TurnTo(pBossNode);
                            Sleep(500);
                            while(pCall->isStrikeCd(0x5DC1))
                            {
                                pCall->Attack(0x5ECE);
                            }
                        }
                    }
                    else
                    {
						TRACE("ִ��0x5dca");
						if(pCall->GetPlayerMana() < 40)
						{
							pCall->sendcall(id_msg_attack, (LPVOID)0x5dc1);
						}
						else
						{
							pCall->Kill_Tab(0x5dca);
						}
                        pCall->TurnTo(pBossNode);
                        if(pCall->isStrikeCd(0x5E1B) == FALSE)
                        {
                            TRACE("ִ��0x5E1B");
                            pCall->Kill_Tab(0x5E1B);
                            Sleep(1000);
                        }
                        else if(pCall->isStrikeCd(0x5e74) == FALSE)
                        {
                            TRACE("ִ��0x5e74");
							Sleep(1000);
                            pCall->Kill_Tab(0x5e74);
                        }
                        else if(pCall->isStrikeCd(0x5DF2) == FALSE)
                        {
                            TRACE("ִ��0x5DF2");
                            pCall->Kill_Tab(0x5DF2);
                        }
                    }
                    break;
                }
            //��ħ��


            //���Ź�����BOSS
            case 5902383:
                {
                    if(pCall->GetObjectTargetId(pBossNode->ObjAddress) == My_id)
                    {
                        pCall->Kill_Tab(0x5dca);
                    }
                    else
                    {
                        pCall->SteptoBack(pBossNode);
                    }
                    break;
                }

            case 5902384:
                {
                    if(percent < 70)
                    {
                        if(pCall->isStrikeCd(0x5DFC) == FALSE)
                        {
                            pCall->Attack(0x5DFC);
                            Sleep(500);
                            pCall->TurnTo(pBossNode);
                            while(pCall->isStrikeCd(0x5DC1))
                            {
                                pCall->Attack(0x5ECE);
                            }
                        }
                    }
                    else
                    {
                        if(pCall->GetObjectTargetId(pBossNode->ObjAddress) == My_id)
                        {
                            pCall->Kill_Tab(0x5dca);
                        }
                        else
                        {
                            pCall->SteptoBack(pBossNode);
                        }
                    }
                    break;
                }
            case 5902385:
                {
                    if(pCall->GetObjectTargetId(pBossNode->ObjAddress) == My_id)
                    {
                        pCall->Kill_Tab(0x5dca);
                    }
                    else
                    {
                        pCall->SteptoBack(pBossNode);
                    }
                    break;
                }
            case 5902386:
                {
                    if(pCall->GetObjectTargetId(pBossNode->ObjAddress) == My_id)
                    {
                        pCall->Kill_Tab(0x5dca);
                    }
                    else
                    {
                        pCall->SteptoBack(pBossNode);
                    }
                    break;
                }
            case 5902388:
                {
                    pCall->Kill_Tab(0x5dca);
                    if(pCall->GetPlayerMana() < 20)
                    {
                        pCall->sendcall(id_msg_attack, (LPVOID)0x5dc1);//r
                    }
                    pCall->Kill_Tab(0x5dca);
                    break;
                }
            case 5902389:
                {
                    pCall->Kill_Tab(0x5dca);
                    if(pCall->GetPlayerMana() < 20)
                    {
                        pCall->sendcall(id_msg_attack, (LPVOID)0x5dc1);//r
                    }
                    pCall->Kill_Tab(0x5dca);
                    break;
                }
            case 5902391:
                {
                    pCall->TurnTo(pBossNode);
                    if(pCall->GetPlayerMana() > 60)
                    {
                        if(pCall->isStrikeCd(0x5E1B) == FALSE)
                        {
                            pCall->Kill_Tab(0x5E1B);
                        }
                        else
                        {
                            pCall->Kill_Tab(0x5dca);
                        }
                    }
                    else
                    {
                        if(pCall->isStrikeCd(0x5e74) == FALSE)
                        {
                            pCall->Kill_Tab(0x5e74);
                        }
                        else if(pCall->isStrikeCd(0x5DF2) == FALSE)
                        {
                            pCall->Kill_Tab(0x5DF2);
                        }
                        else
                        {
                            pCall->Kill_Tab(0x5dca);
                        }
                    }
                    if(pCall->GetPlayerMana() < 20)
                    {
                        pCall->sendcall(id_msg_attack, (LPVOID)0x5dc1);//r
                    }
                    break;
                }
            //���Ź�����BOSS

            //ѩ�˶�ѩ��



            //ѩ�˶�ѩ��
            default:
                {
                    //ɱ��
                    TRACE(_T("attack id: %d"), ma.dwStrikeId);
                    if(wcscmp(m_name.c_str(), L"�R���_") == 0  //1��С��
                            || wcscmp(m_name.c_str(), L"��ˇ") == 0 //1��С��
                            || wcscmp(m_name.c_str(), L"�o��") == 0) //3��BOSS
                    {
                        if(percent < 70)
                        {
                            if(pCall->isStrikeCd(0x5DFC) == FALSE)
                            {
                                pCall->Attack(0x5DFC);
                                while(pCall->isStrikeCd(0x5DC1))
                                {
                                    pCall->TurnTo(pBossNode);
                                    pCall->Attack(0x5ECE);
                                }
                            }
                        }


                    }

                    if(pCall->GetRangeMonsterCount() > 1)
                    {
                        pCall->Kill_Tab(0x5dca);
                    }
                    if(pCall->GetObjectTargetId(pBossNode->ObjAddress) == My_id)
                    {
                        pCall->Kill_Tab(0x5dca);
                    }
                    else
                    {
                        pCall->SteptoBack(pBossNode);
                    }

                    break;
                }
            }
            ZeroMemory(&_event, sizeof(MONSTERATAACK));
        }
        else
        {
            //����ʱ����, һ����ͷż���


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

            pCall->TurnTo(pBossNode);

            if(percent < 90)
            {
                if(pCall->isStrikeCd(0x5E24) == FALSE)
                {
                    pCall->Attack(0x5E24);
                }
            }


            if(pCall->GetRangeMonsterCount() > 1)
            {
                if(pCall->isStrikeCd(0x5DE8) == FALSE)
                {
                    pCall->Kill_Tab(0x5DE8);
                }
            }
            if(pCall->isStrikeCd(0x5E06) == FALSE)
            {
                pCall->Attack(0x5E06);
            }

            //�¼����͹��쵼��ִ�ж�Ӧ����ʱΪʱ������ô��, �����ʱ������
            //�����û���ü������˸���������
            //Sleep(10);
            if(pCall->GetPlayerMana() > 70)
            {
                //pCall->Attack(0x5dde);
                pCall->sendcall(id_msg_attack, (LPVOID)0x5dde);
            }
            //pCall->Attack(0x5dc1);
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


    //�Ȱ�ʱ�����
    if (pAttack->dwStrikeId > 0xffff)
    {
        if(pAttack->dwStrikeId != old1.dwStrikeId)
        {

            //if (_event.size() != 0)
            //{
            //  TRACE("_event.size()");
            //}
            //�����и����ȼ�, �ŵ�����ǰ���Ƕ��к�
            //��ʵ���ȴ�����˳����.��Ҫͬ��
            m_Mutex.Lock();
            _event.push_front(*pAttack);
            m_Mutex.Unlock();

            //�����ȼ�û�����, �������һ�㶼�ǿյ����
            //�ձ�ʾ�¼����������, ������ж��еĻ�, ֻ��˵���¼��Ѿ����Ŷ���.
            //�������˶ӵ��¼���û������, �¼�Ӧ�ñ���ʱ����
            //����һ�����ż��ܱ��ŶӴ�����, ������1��. ��ʱ���ٱ������Ѿ�û������.

            old1 = *pAttack;
            dwEnd = GetTickCount(); //��¼��δ����ܵ�ʱ��
        }
        else
        {
            //������ȣ� ��Ϊȷʵ�����������ͷŵļ��ܣ� ���Ǽ��2������
            //Ҳ��ҪӦ�ԣ� �����жϣ� �����Ȳ��Һ��ϴ��ͷż��2��Ҳ����
            if((dwStart - dwEnd) > 5000)
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