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

        GamecallEx::GetInstance()->KeyPress('R');
        //�����



        if(pCall->GetType4HP(pBossNode->ObjAddress) == -1 || pCall->GetType4HP(pBossNode->ObjAddress) == 0)
        {
            TRACE(_T("%s: Ѫ���жϹ�����"), FUNCNAME);
            break;
        }


        if(pCall->GetObjectType(pBossNode->ObjAddress) != 0x4)
        {
            TRACE(_T("%s: �����жϹ�����"), FUNCNAME);
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
        if(dis >= CAN_OPERATOR*2)
        {
            TRACE(_T("%s: �����жϹ�����"), FUNCNAME);
            break;
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
                    Sleep(800);
                    TRACE(_T("0x5455E1"));
                    //GamecallEx::GetInstance()->KeyPress(86);
                    if(GamecallEx::GetInstance()->isStrikeCd(0x5DFC))
                    {
                        GamecallEx::GetInstance()->sendcall(id_msg_attack, (LPVOID)0x5DFC);//v
                        //GamecallEx::GetInstance()->Attack(0x5DFC);
                        Sleep(3000);
                    }
                    else
                    {
                        GamecallEx::GetInstance()->sendcall(id_msg_attack, (LPVOID)0x5dca);//tab
                        Sleep(1000);
                    }




                    break;
                }
            case 0x5455DD:
                {
                    Sleep(800);
                    TRACE(_T("0x5455DD"));
                    //GamecallEx::GetInstance()->KeyPress(9);
                    GamecallEx::GetInstance()->sendcall(id_msg_attack, (LPVOID)0x5dca);//tab
                    //GamecallEx::GetInstance()->Attack(0x5dca);
                    Sleep(1000);
                    break;
                }
            case 0x5455DA:
                {
                    Sleep(800);
                    TRACE(_T("0x5455DA"));
                    //GamecallEx::GetInstance()->KeyPress(82);
                    //GamecallEx::GetInstance()->sendcall(id_msg_attack, (LPVOID)0x5dc1);//r
                    //GamecallEx::GetInstance()->Attack(0x5dc1);
                    //Sleep(500);
                    //GamecallEx::GetInstance()->KeyPress(88);
                    if(GamecallEx::GetInstance()->isStrikeCd(0x5E24))
                    {
                        GamecallEx::GetInstance()->sendcall(id_msg_attack, (LPVOID)0x5E24);//x
                        //GamecallEx::GetInstance()->Attack(0x5E24);
                        Sleep(500);
                    }
                    else
                    {
                        GamecallEx::GetInstance()->sendcall(id_msg_attack, (LPVOID)0x5dca);//tab
                        Sleep(1000);
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


        }
        else
        {

            //����ʱ����, һ����ͷż���
            pCall->TurnToNear(300);
            Sleep(100);
            //GamecallEx::GetInstance()->KeyPress(82);
            //GamecallEx::GetInstance()->sendcall(id_msg_attack, (LPVOID)0x5dc1);//r
            Sleep(100);
            pCall->KeyPress('R');
            //GamecallEx::GetInstance()->sendcall(id_msg_attack, (LPVOID)0x5dde);//t
            Sleep(100);
        }


        //�¼����͹��쵼��ִ�ж�Ӧ����ʱΪʱ������ô��, �����ʱ������
        //�����û���ü������˸���������
        Sleep(100);
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
    static DWORD dwFirst;
    DWORD dwSec = GetTickCount();


    //�Ȱ�ʱ�����
    if((dwSec - dwFirst) > 500)
    {
        if(pAttack->dwStrikeId != old1.dwStrikeId)
        {


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
        }

        dwFirst = GetTickCount();
    }
}

void CombatBoss::SetName(const wchar_t* name)
{
    m_name = name;
}