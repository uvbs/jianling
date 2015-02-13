// tester.cpp : Defines the entry point for the console application.
#include "stdafx.h"
#include "tester.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


#include "Logic.h"
#include "UILogic.h"
#include "ontrolLogic.h"
#include "AttackLogic.h"
#include "TaskDispter.h"


void Attack()
{
    printf("����\n");
}

void OpenBag()
{
    printf("�򿪱����\n");
}

void AcceptQuest()
{
    printf("�������\n");
}

void DelivrQuest()
{
    printf("�������\n");
}


int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{

    TaskDispter dispter;

    AttackLogic alogc;
    UILogic uilogc;
    ControLogic ctloc;

    alogc.Init();
    uilogc.Init();
    ctloc.Init();


    dispter.AddLogic(&alogc);
    dispter.AddLogic(&uilogc);
    dispter.AddLogic(&ctloc);



    dispter.AddWork(Attack);
    dispter.AddWork(DelivrQuest);


    return 0;
}
