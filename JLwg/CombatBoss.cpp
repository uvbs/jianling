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


//����: ��ʱ�Ĳ���ʱ, �����ʱ�������¼�֪ͨ��ô��
//��ʵĿǰ��ʱ�Ĳ���, ������·������, �����������ͬ������, ��Ҫһ�ַ�ʽ���
//����Ŀ�ĵص�֪ͨ
//Ŀǰ����: һֱ����, ����ŷ���. ��˵���Ľ�����Ǻ�������
//��Ҫһ���첽����, ��ִ������֪ͨ
void CombatBoss::run()
{
    //hook���＼��, ���ûص�
    GameHook::GetInstance()->SetCombatSink(this);


    //������boss�ĵ�ַ
    //�������

    std::vector<ObjectNode*> RangeObject;
    GamecallEx::GetInstance()->GetRangeMonsterToVector(200, RangeObject);



    //�߹�ȥ



    //����ѭ��
    while(1)
    {

        //�˳�����
        //boss ��
        



        //�¼��б�ձ�ʾ��ǰ������ͨ����
        if(_event.size() > 0)
        {
            std::list<MONSTERATAACK>::iterator it = _event.begin();
            switch((*it).dwStrikeId)
            {

            //��Ӧboss����
            case 3333:
                {

                    break;
                }

            default:
                {
                    //ɱ��
                    TRACE(_T("attack id:%d"), (*it).dwStrikeId);
                    break;
                }

            }

            //����������¼�, �Ӷ���ɾ��
            _event.erase(it);
        }
        else
        {
            //����ʱ����

            //��ͨ�ͷż���



        }


        //�¼����͹��쵼��ִ�ж�Ӧ����ʱΪʱ������ô��
        Sleep(250);
    }

}

void CombatBoss::NotifyMonsterAttack(MONSTERATAACK* pAttack)
{

    static MONSTERATAACK old1;

    static DWORD dwFirst;
    DWORD dwSec = GetTickCount();

    TRACE(_T("����ID:%x"), pAttack->dwStrikeId);



    //�Ȱ�ʱ�����
    if((dwSec - dwFirst) > 1000)
    {
        if(pAttack->dwStrikeId != old1.dwStrikeId)
        {


            //�����и����ȼ�, �ŵ�����ǰ���Ƕ��к�
            //��ʵ���ȴ�����˳����.
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

            //����д��Ӧboss�ļ���




            old1 = *pAttack;
        }

        dwFirst = GetTickCount();
    }


}