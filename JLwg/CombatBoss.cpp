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
    TRACE(_T("׼����BOSS"));
    //hook���＼��, ���ûص�
    GameHook::GetInstance()->SetCombatSink(this);

    //���call
    GamecallEx* pCall = GamecallEx::GetInstance();


    fPosition mypos;
    fPosition tarpos;

    ObjectNode* pBossNode = pCall->GetObjectByName(m_name.c_str(), 0);
    if(pBossNode == NULL)
    {
        TRACE(_T("û�ҵ�boss"));
        return;
    }

    pCall->Stepto(pBossNode);

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


        if(pCall->GetType4HP(pBossNode->ObjAddress) == -1 || pCall->GetType4HP(pBossNode->ObjAddress) == 0)
        {
            TRACE(_T("%s: Ѫ���жϹ�����"), FUNCNAME);
            break;
        }


        //if(pCall->GetObjectType(pBossNode->ObjAddress) != 0x4)
        //{
        //    TRACE(_T("%s: �����жϹ�����"), FUNCNAME);
        //    break;
        //}


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
            pCall->Stepto(tarpos.y, tarpos.x, tarpos.z, 10, CAN_OPERATOR, 3000, TRUE);
            //TRACE(_T("%s: �����жϹ�����"), FUNCNAME);
            //break;
        }





        //�¼��б��?
        if(_event.size() > 0)
        {


            MONSTERATAACK ma;


            //������Ҫͬ��
            m_Mutex.Lock();
            std::list<MONSTERATAACK>::iterator it = _event.begin();

            ma = (*it);

            //����������¼�, �Ӷ���ɾ��
            _event.erase(it);
            m_Mutex.Unlock();



            switch(ma.dwStrikeId)
            {

            //��Ӧboss����
            case 0x5455E1:
                {
                    pCall->TurnToNear(300);
                    Sleep(300);
                    TRACE(_T("0x5455E1"));
                    //pCall->KeyPress(86);
                    if(pCall->isStrikeCd(0x5DFC))
                    {
                        //pCall->sendcall(id_msg_attack, (LPVOID)0x5DFC);//v
                        //Sleep(600);
                        //pCall->sendcall(id_msg_attack, (LPVOID)0x5ECE);//v-r
                        //Sleep(400);
                        //pCall->sendcall(id_msg_attack, (LPVOID)0x5ECE);//v-r
                        //Sleep(400);
                        //pCall->sendcall(id_msg_attack, (LPVOID)0x5ECE);//v-r
                        //pCall->Attack(0x5DFC);
                        pCall->Attack(0x5DFC);
                        pCall->TurnToNear(300);
                        Sleep(300);
                        pCall->Attack(0x5ECE);
                        pCall->Attack(0x5ECE);
                        pCall->Attack(0x5ECE);
                        pCall->Attack(0x5ECE);
                        pCall->Attack(0x5ECE);
                    }
                    else
                    {
                        //pCall->sendcall(id_msg_attack, (LPVOID)0x5E1A);//E
                        pCall->Attack(0x5E1A);
                        //pCall->sendcall(id_msg_attack, (LPVOID)0x5dca);//tab
                        //Sleep(500);
                    }
                    break;
                }
            //case 0x5455DD:
            //    {
            //        pCall->TurnToNear(300);
            //        Sleep(500);
            //        TRACE(_T("0x5455DD"));
            //        //pCall->KeyPress(9);

            //        pCall->sendcall(id_msg_attack, (LPVOID)0x5dc1);//r
            //        Sleep(500);
            //        pCall->sendcall(id_msg_attack, (LPVOID)0x5dca);//tab
            //        //pCall->Attack(0x5dca);
            //        Sleep(500);
            //        break;
            //    }
            case 0x5455DA:
                {
                    pCall->TurnToNear(300);
                    Sleep(600);
                    TRACE(_T("0x5455DA"));
                    //pCall->KeyPress(82);
                    //pCall->sendcall(id_msg_attack, (LPVOID)0x5dc1);//r
                    //pCall->Attack(0x5dc1);
                    //Sleep(500);
                    //pCall->KeyPress(88);
                    //              if(pCall->isStrikeCd(0x5E24))
                    //              {
                    //pCall->Attack(0x5E24);//x
                    //pCall->Attack(0x5dc1);
                    //pCall->Attack(0x5dc1);
                    //pCall->Attack(0x5dca);
                    //pCall->Attack(0x5E1B);

                    ////                  pCall->sendcall(id_msg_attack, (LPVOID)0x5E24);//x
                    ////                  //pCall->Attack(0x5E24);
                    ////                  Sleep(800);
                    ////pCall->sendcall(id_msg_attack, (LPVOID)0x5dc1);//r
                    ////Sleep(500);
                    ////pCall->sendcall(id_msg_attack, (LPVOID)0x5dca);//tab
                    ////Sleep(1000);
                    ////pCall->sendcall(id_msg_attack, (LPVOID)0x5E1B);//C
                    ////Sleep(800);
                    ////pCall->Attack(0);
                    //              }
                    //              else
                    if(pCall->isStrikeCd(0x5e74))
                    {
                        pCall->Attack(0x5e74);//1
                        pCall->Attack(0x5dc1);
                        pCall->Attack(0x5dc1);
                        pCall->Attack(0x5dca);
                        pCall->Attack(0x5E1B);
                        //                  pCall->sendcall(id_msg_attack, (LPVOID)0x5dca);//tab
                        //                  Sleep(1000);
                        //pCall->sendcall(id_msg_attack, (LPVOID)0x5dc1);//r
                        //Sleep(500);
                        //pCall->sendcall(id_msg_attack, (LPVOID)0x5dc1);//r
                        //Sleep(500);
                        //pCall->sendcall(id_msg_attack, (LPVOID)0x5E1B);//C
                        //Sleep(800);
                    }
                    else if(pCall->isStrikeCd(0x5DF2))
                    {
                        pCall->Attack(0x5DF2);//1
                        pCall->Attack(0x5dc1);
                        pCall->Attack(0x5dc1);
                        pCall->Attack(0x5dca);
                        pCall->Attack(0x5E1B);
                    }
                    break;
                }
            case 5190087:
                {
                    pCall->TurnToNear(300);
                    Sleep(300);
                    TRACE(_T("5190087"));
                    //pCall->sendcall(id_msg_attack, (LPVOID)0x5dc1);//r
                    pCall->Attack(0x5dc1);
                    pCall->Kill_Tab();
                    //pCall->sendcall(id_msg_attack, (LPVOID)0x5dca);//tab
                    //Sleep(1000);
                    //pCall->sendcall(id_msg_attack, (LPVOID)0x5dc1);//r
                    pCall->Attack(0x5dc1);
                    pCall->Kill_Tab();
                    break;
                }
            case 5190074:
                {
                    pCall->TurnToNear(300);
                    Sleep(600);
                    TRACE(_T("5190074"));
                    //pCall->sendcall(id_msg_attack, (LPVOID)0x5dca);//tab
                    //Sleep(1000);
                    pCall->Kill_Tab();
                    //pCall->sendcall(id_msg_attack, (LPVOID)0x5dc1);//r
                    pCall->KeyPress(82);
                    break;
                }
            case 5190070:
                {
                    pCall->TurnToNear(300);
                    Sleep(300);
                    TRACE(_T("5190074"));
                    //pCall->sendcall(id_msg_attack, (LPVOID)0x5dca);//tab
                    //Sleep(1000);
                    pCall->Kill_Tab();
                    //pCall->sendcall(id_msg_attack, (LPVOID)0x5dc1);//r
                    //pCall->KeyPress(82);
                    break;
                }
            case 5190071:
                {
                    pCall->TurnToNear(300);
                    Sleep(300);
                    TRACE(_T("5190071"));
                    //pCall->sendcall(id_msg_attack, (LPVOID)0x5dca);//tab
                    //Sleep(1000);
                    pCall->Kill_Tab();
                    //pCall->sendcall(id_msg_attack, (LPVOID)0x5dc1);//r
                    //pCall->KeyPress(82);
                    break;
                }
            case 5190088:
                {
                    //pCall->TurnToNear(300);
                    Sleep(300);
                    pCall->SteptoBack(pBossNode);
                    TRACE(_T("��������"));
                    break;
                }
            case 5190089:
                {
                    //pCall->TurnToNear(300);
                    Sleep(300);
                    pCall->SteptoBack(pBossNode);
                    TRACE(_T("��������"));
                    //if (pCall->isStrikeCd(0x5e6a))
                    //{
                    //  pCall->sendcall(id_msg_attack, (LPVOID)0x5e6a);//ss
                    //  Sleep(2500);
                    //  pCall->sendcall(id_msg_attack, (LPVOID)0x5e74);//1
                    //}else
                    if(pCall->isStrikeCd(0x5E1B))
                    {
                        Sleep(500);
                        //pCall->sendcall(id_msg_attack, (LPVOID)0x5E1B);//C
                        pCall->KeyPress(67);
                        Sleep(800);
                    }
                    else if(pCall->isStrikeCd(0x5DF2))
                    {
                        Sleep(500);
                        //pCall->sendcall(id_msg_attack, (LPVOID)0x5DF2);//2
                        pCall->KeyPress(50);
                        Sleep(500);
                    }
                    else if(pCall->isStrikeCd(0x5DFC))
                    {
                        pCall->Attack(0x5DFC);
                        pCall->TurnToNear(300);
                        Sleep(300);
                        pCall->Attack(0x5ECE);
                        pCall->Attack(0x5ECE);
                        pCall->Attack(0x5ECE);
                        pCall->Attack(0x5ECE);
                        pCall->Attack(0x5ECE);
                    }
                    break;
                }
            default:
                {
                    //ɱ��
                    TRACE(_T("attack id: %d"), ma.dwStrikeId);
                    break;
                }
            }
            ZeroMemory(&_event, sizeof(MONSTERATAACK));
        }
        else
        {
            //����ʱ����, һ����ͷż���
            if(pCall->isPlayerDaodi())
            {
                //5E60->5EA6->5EB0->5E9C
                Sleep(500);
                if(pCall->isStrikeCd(0x5e60))
                {
                    //pCall->sendcall(id_msg_attack, (LPVOID)0x5e60);
                    pCall->Attack(0x5e60);
                    //Sleep(1000);
                }
                else if(pCall->isStrikeCd(0x5EA6))
                {
                    //pCall->sendcall(id_msg_attack, (LPVOID)0x5EA6);
                    pCall->Attack(0x5EA6);
                }
                else if(pCall->isStrikeCd(0x5E9C))
                {
                    //pCall->sendcall(id_msg_attack, (LPVOID)0x5E9C);
                    pCall->Attack(0x5E9C);
                }
            }
            pCall->TurnToNear(300);
            Sleep(50);
            //pCall->KeyPress(82);
            //if (wcscmp(m_name.c_str() ,L"�y����ʿ") == 0)
            //{
            //  if(pCall->GetPlayerMana() >= 60)
            //  {
            //      if (pCall->isStrikeCd(0x5dde))
            //      {
            //          pCall->Attack(0x5dde);
            //      }
            //  }
            //  pCall->Attack(0x5dc1);
            //}else
            //{
            if(pCall->isStrikeCd(0x5E24))
            {
                pCall->Attack(0x5E24);
            }
            if(pCall->GetPlayerMana() > 70)
            {
                //pCall->sendcall(id_msg_attack, (LPVOID)0x5dde);//t
                //if (pCall->isStrikeCd(0x5dde))
                //{
                pCall->Attack(0x5dde);
                //}
            }
            else
            {
                pCall->Attack(0x5dc1);
            }
            //pCall->sendcall(id_msg_attack, (LPVOID)0x5dc1);//r
            //}

        }
        //�¼����͹��쵼��ִ�ж�Ӧ����ʱΪʱ������ô��, �����ʱ������
        //�����û���ü������˸���������
        Sleep(10);
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
    if(pAttack->dwStrikeId > 0xffff)
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
            if((dwStart - dwEnd) > 1000)
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