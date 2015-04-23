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
                    //ɱ��

                }

            }

            _event.erase(it);
        }
        else
        {
            //����ʱ����
        }


        Sleep(1000);
    }

}

void CombatBoss::NotifyMonsterAttack(MONSTERATAACK* pAttack)
{
    _event.push_back(*pAttack);
}