#include "stdafx.h"
#include "TaskScript.h"
#include "JLwg.h"
#include <string>
#include <tchar.h>



FunTask ft[0x400] =
{
    { TEXT("221"), &TaskScript::Task_221 },//新手任务1
    { TEXT("222"), &TaskScript::Task_222 },//新手任务2
    { TEXT("223"), &TaskScript::Task_223 },//新手任务3
    { TEXT("224"), &TaskScript::Task_224 },//新手任务4
    { TEXT("231"), &TaskScript::Task_231 },//新手任务5
    { TEXT("232"), &TaskScript::Task_232 },//新手任务6
    { TEXT("227"), &TaskScript::Task_227 },//新手任务7
    { TEXT("243"), &TaskScript::Task_243 },//新手任务8
    { TEXT("301"), &TaskScript::Task_301 },//1-1
    { TEXT("302"), &TaskScript::Task_302 },//1-2
    { TEXT("303"), &TaskScript::Task_303 },//1-3
    { TEXT("497"), &TaskScript::Task_497 },//1-4
    { TEXT("304"), &TaskScript::Task_304 },//1-5
    { TEXT("305"), &TaskScript::Task_305 },//1-6
    { TEXT("306"), &TaskScript::Task_306 },//1-7
    { TEXT("307"), &TaskScript::Task_307 },//1-8
    { TEXT("308"), &TaskScript::Task_308 },//1-9
    { TEXT("309"), &TaskScript::Task_309 },//1-10
    { TEXT("310"), &TaskScript::Task_310 },//1-11
    { TEXT("311"), &TaskScript::Task_311 },//1-12  到了这个任务要去打到12级才行，上然后面有的装备穿上上。
    { TEXT("312"), &TaskScript::Task_312 },//1-13
    { TEXT("491"), &TaskScript::Task_491 },//1-14
    { TEXT("492"), &TaskScript::Task_492 },//1-15
    { TEXT("313"), &TaskScript::Task_313 },//1-16
    { TEXT("494"), &TaskScript::Task_494 },//1-17
    { TEXT("314"), &TaskScript::Task_314 },//1-18
    { TEXT("496"), &TaskScript::Task_496 },//1-19
    { TEXT("315"), &TaskScript::Task_315 },//1-20
    { TEXT("316"), &TaskScript::Task_316 },//1-21
    { TEXT("493"), &TaskScript::Task_493 },//1-22
    { TEXT("317"), &TaskScript::Task_317 },//1-23
    { TEXT("318"), &TaskScript::Task_318 },//1-24
    { TEXT("495"), &TaskScript::Task_495 },//1-25
    { TEXT("319"), &TaskScript::Task_319 },//1-26
    { TEXT("320"), &TaskScript::Task_320 },//1-27
    { TEXT("501"), &TaskScript::Task_501 },//2-1
    { TEXT("540"), &TaskScript::Task_540 },//2-2
    { TEXT("502"), &TaskScript::Task_502 },//2-3
    { TEXT("503"), &TaskScript::Task_503 },//2-4
    { TEXT("504"), &TaskScript::Task_504 },//2-5
    { TEXT("505"), &TaskScript::Task_505 },//2-6
    { TEXT("506"), &TaskScript::Task_506 },//2-7
    { TEXT("507"), &TaskScript::Task_507 },//2-8
    { TEXT("508"), &TaskScript::Task_508 },//2-9
    { TEXT("509"), &TaskScript::Task_509 },//2-10
    { TEXT("510"), &TaskScript::Task_510 },//2-11
    { TEXT("511"), &TaskScript::Task_511 },//2-12
    { TEXT("512"), &TaskScript::Task_512 },//2-13
    { TEXT("513"), &TaskScript::Task_513 },//2-14
    { TEXT("514"), &TaskScript::Task_514 },//2-15
    { TEXT("515"), &TaskScript::Task_515 },//2-16
    { TEXT("516"), &TaskScript::Task_516 },//2-17
    { TEXT("517"), &TaskScript::Task_517 },//2-18
    { TEXT("518"), &TaskScript::Task_518 },//2-19
    { TEXT("519"), &TaskScript::Task_519 },//2-20
    { TEXT("520"), &TaskScript::Task_520 },//2-21
    { TEXT("521"), &TaskScript::Task_521 },//2-22
    { TEXT("522"), &TaskScript::Task_522 },//2-23
    { TEXT("523"), &TaskScript::Task_523 },//2-24
    { TEXT("524"), &TaskScript::Task_524 },//2-25
    { TEXT("525"), &TaskScript::Task_525 },//2-26
    { TEXT("526"), &TaskScript::Task_526 },//2-27
    { TEXT("527"), &TaskScript::Task_527 },//2-28
    { TEXT("528"), &TaskScript::Task_528 },//2-29
    { TEXT("541"), &TaskScript::Task_541 },//2-30
    { TEXT("529"), &TaskScript::Task_529 },//2-31
    { TEXT("530"), &TaskScript::Task_530 },//2-32
    { TEXT("531"), &TaskScript::Task_531 },//2-33
    { TEXT("532"), &TaskScript::Task_532 },//2-34
    { TEXT("533"), &TaskScript::Task_533 },//2-35
    { TEXT("542"), &TaskScript::Task_542 },//2-36
    { TEXT("534"), &TaskScript::Task_534 },//2-37
    { TEXT("535"), &TaskScript::Task_535 },//2-38
    { TEXT("536"), &TaskScript::Task_536 },//2-39
    { TEXT("537"), &TaskScript::Task_537 },//2-40
    { TEXT("538"), &TaskScript::Task_538 },//2-41
    { TEXT("901"), &TaskScript::Task_901 },//3-1
    { TEXT("902"), &TaskScript::Task_902 },//3-2
    { TEXT("903"), &TaskScript::Task_903 },//3-3
    { TEXT("904"), &TaskScript::Task_904 },//3-4
    { TEXT("905"), &TaskScript::Task_905 },//3-5
	{ TEXT("906"), &TaskScript::Task_906 },//3-6
	{ TEXT("907"), &TaskScript::Task_907 },//3-7
	{ TEXT("908"), &TaskScript::Task_908 },//3-8
	{ TEXT("931"), &TaskScript::Task_931 },//3-9
	{ TEXT("909"), &TaskScript::Task_909 },//3-10
	{ TEXT("910"), &TaskScript::Task_910 },//3-11
	{ TEXT("911"), &TaskScript::Task_911 },//3-12
	{ TEXT("912"), &TaskScript::Task_912 },//3-13
	{ TEXT("913"), &TaskScript::Task_913 },//3-14
	{ TEXT("914"), &TaskScript::Task_914 },//3-15
	{ TEXT("915"), &TaskScript::Task_915 },//3-16
	{ TEXT("916"), &TaskScript::Task_916 },//3-17
	{ TEXT("917"), &TaskScript::Task_917 },//3-18
	{ TEXT("918"), &TaskScript::Task_918 },//3-19
	{ TEXT("919"), &TaskScript::Task_919 },//3-20
	{ TEXT("921"), &TaskScript::Task_921 },//3-21
	{ TEXT("922"), &TaskScript::Task_922 },//3-22
	{ TEXT("923"), &TaskScript::Task_923 },//3-23
	{ TEXT("924"), &TaskScript::Task_924 },//3-
	{ TEXT("925"), &TaskScript::Task_925 },//3-
	{ TEXT("926"), &TaskScript::Task_926 },//3-24
	{ TEXT("927"), &TaskScript::Task_927 },//3-
	{ TEXT("928"), &TaskScript::Task_928 },//3-
	{ TEXT("929"), &TaskScript::Task_929 },//3-
    { TEXT("294"), &TaskScript::Task_294 },//4-19
};



TaskScript::TaskScript(void)
{

}

TaskScript::~TaskScript(void)
{

}


//功能函数区

/*
70=f
27=esc
87=w
32=space
*/



/************************************************************************/
/*新手村任务开始 */
/************************************************************************/
/*写日志*/
void TaskScript::log(TCHAR szFormat[], ...)
{
    TCHAR buffer[BUFSIZ] = { 0 };

    va_list argptr;
    va_start(argptr, szFormat);
    wvsprintf(buffer, szFormat, argptr);
    va_end(argptr);
    OutputDebugString(buffer);
}

void TaskScript::BeginTask()
{
    TaskScript ts;
    try
    {
        while(1)
        {
            DWORD pStartAddr = gcall.GetTaskStartAddr();//获取任务开始地址

            //log(TEXT("%08x"),pStartAddr);
            DWORD ID = gcall.GetTaskID(0, pStartAddr);//获得当前任务ID
            //TRACE1("当前任务ID:%d",ID);

            DWORD info = gcall.GetPresentTaskIndexes(0, pStartAddr);//获得当前做到第几个小任务

            DWORD nameid = gcall.GetTaskNameID(0, pStartAddr);//获取当前任务吊id
            //wchar_t* taskname = gcall.GatTaskName(nameid);//获得当前任务吊

            //if (ID == 227)
            //{
            //	break;
            //}
            if(ID == -1 || info == -1)
            {
                log(TEXT("获取任务失败..address:%x,id:%d,info:%d"), pStartAddr, ID, info);
                Sleep(2000);
            }
            //else
            //{
            //	log(TEXT("address:%x,id:%d,info:%d,任务吊:%s"), pStartAddr, ID, info, taskname);
            //}
            //TCHAR szbuffer[20];
            //wsprintf(szbuffer,TEXT("%d%d"),ID,info);
            //log(szbuffer);
            TCHAR szBu_id[20] = { 0 };
            wsprintf(szBu_id, TEXT("%d"), ID);
            TCHAR szbu[BUFSIZ] = { 0 };
            for(int i = 0; i < 0x400; i++)
            {
                if(lstrcmp(ft[i].taskname, szBu_id) == 0)
                {
                    wsprintf(szbu, TEXT("任务函数开始执行.id:%s,task_id:%d,数组下标:%d"), ft[i].taskname, info, i);
                    log(szbu);
                    //TRACE1("ID--:%d",ID);
                    (ts.*(ft[i].fp))(ID, info);
                    log(TEXT("任务函数执行完成"));
                    break;
                }
                else
                    log(_T("当前任务:%d,函数ID:%s,数组id:%s"), ID, szBu_id, ft[i].taskname);
            }
        }


        //Task_221_2();
    }
    catch(...)
    {
        log(TEXT("获取任务异常"));
    }
}







void TaskScript::Task_929(int zid, int taskid)
{
	switch(taskid)
	{
	case 1:
		MessageBox(0, L"929", L"装八卦", MB_OK);
		break;
	case 2:
		break;
	case 3:
		break;
	case 4:
		break;
	case 5:
		break;
	case 6:
		break;
	case 7:
		break;
	case 8:
		break;
	case 9:
		break;

	}
}


void TaskScript::Task_294(int zid, int taskid)
{
    switch(taskid)
    {
        case 1:
            MessageBox(0, L"摇奖完", L"装八卦", MB_OK);
            break;
        case 2:
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            break;
        case 6:
            break;
        case 7:
            break;
        case 8:
            break;
        case 9:
            break;

    }
}
/////////////////////主线结束线///////////////////////////////

////////////////////Task函数线///////////////////////////////
/************************************************************************/
/* 出现30秒以上的可能就是卡门了，卡门后必须要退出游戏重新进才能解决。

具体出现的原因:大概是VPN的问题，但还上能确定。*/
/************************************************************************/
BOOL TaskScript::ShunYiResult(DWORD CityId, wchar_t* FileName, BOOL Hook_flag)
{
    Sleep(1000);//先休息1秒后再瞬移,否则太快可能还没走到点就执行瞬移了。

    int shunyirs = 0;
    BOOL resultsy = FALSE;
    BOOL returnflag = TRUE;
    log(_T("执行ShunYiResult"));
    //先执行一次
    int shunyics = 0;
    //gcall.Shunyi(FileName);
    //Sleep(1000);
    //gcall.sendcall(id_msg_OverShunyi,(LPVOID)Hook_flag);//hook
    //Sleep(1000);
    //////////////////////////////////////////////////////////////////////////
    while(1)
    {
        if(shunyics >= 2)
            break;
        if(gcall.GetCityID() == CityId)
        {
            log(L"当前地图ID:%d,与传入ID:%d,相同break", gcall.GetCityID(), CityId);
            if(returnflag)
                Sleep(1000);
            else
                Sleep(5000);

            break;
        }
        else
        {
            if(resultsy == FALSE)
            {
                gcall.Shunyi(FileName);
                Sleep(1000);
                gcall.sendcall(id_msg_OverShunyi, (LPVOID)Hook_flag); //hook
                Sleep(1000);
                resultsy = TRUE;
                shunyics++;
            }
            log(L"当前地图ID:%d,与传入ID:%d,执行瞬移文件吊:%s", gcall.GetCityID(), CityId, FileName);
            Sleep(1000);
            if(shunyirs > 30)
            {
                //MessageBox(NULL,L"这里修改全局变量通知控制台退出",NULL,NULL);
                log(L"这里修改全局变量通知控制台退出");//等待时间N分钟或退出。

                resultsy = FALSE;
                returnflag = FALSE;
                shunyirs = 0;
                gcall.KeyPress(87);
                gcall.KeyPress(87);
                Sleep(500);
                gcall.KeyPress(83);
                gcall.KeyPress(83);
                Sleep(1000);
                gcall.sendcall(id_msg_TiaoYue, 0);
                Sleep(1000);
            }
        }
        shunyirs++;
    }
    return returnflag;
}



void TaskScript::UseExperience()
{
	if (gcall.GetPlayerDeadStatus() == 0)
	{


		if(gcall.GetPlayExperienceStatus() == FALSE)
		{
			gcall.SortBag();
			Sleep(1000);
			std::vector<_BAGSTU> GoodsVec;
			gcall.GetAllGoodsToVector(GoodsVec);
			for(int i = 0; i < GoodsVec.size(); i++)
			{
				if(_wcsicmp(GoodsVec[i].name, L"자경단의 한방 용봉탕") == 0)//%60
				{
					gcall.ChiYao(L"자경단의 한방 용봉탕");
					Sleep(1000);
					gcall.sendcall(id_msg_attack, (LPVOID)0x5dc1);
					return;
				}
			}

			if(gcall.GetPlayerLevel() >= 37)
			{
				for(int i = 0; i < GoodsVec.size(); i++)
				{
					if(_wcsicmp(GoodsVec[i].name, L"수월평원 약선 용봉탕") == 0)//%50
					{
						gcall.ChiYao(L"수월평원 약선 용봉탕");
						Sleep(1000);
						gcall.sendcall(id_msg_attack, (LPVOID)0x5dc1);
						return;
					}
				}
			}

			if(gcall.GetPlayerLevel() >= 45)
			{
				for(int i = 0; i < GoodsVec.size(); i++)
				{
					if(_wcsicmp(GoodsVec[i].name, L"백청산맥 약선 용봉탕") == 0)//%50
					{
						gcall.ChiYao(L"백청산맥 약선 용봉탕");
						Sleep(1000);
						gcall.sendcall(id_msg_attack, (LPVOID)0x5dc1);
						return;
					}
				}
			}

			for(int i = 0; i < GoodsVec.size(); i++)
			{
				if(_wcsicmp(GoodsVec[i].name, L"대사막 약선 용봉탕") == 0) //%40
				{
					gcall.ChiYao(L"대사막 약선 용봉탕");
					Sleep(1000);
					gcall.sendcall(id_msg_attack, (LPVOID)0x5dc1);
					return;
				}
			}

			for(int i = 0; i < GoodsVec.size(); i++)
			{
				if(_wcsicmp(GoodsVec[i].name, L"제룡림 약선 용봉탕") == 0) //%30
				{
					gcall.ChiYao(L"제룡림 약선 용봉탕");
					Sleep(1000);
					gcall.sendcall(id_msg_attack, (LPVOID)0x5dc1);
					return;
				}
			}

			for(int i = 0; i < GoodsVec.size(); i++)
			{
				if(_wcsicmp(GoodsVec[i].name, L"제룡림 특제 용봉탕") == 0) //%20
				{
					gcall.ChiYao(L"제룡림 특제 용봉탕");
					Sleep(1000);
					gcall.sendcall(id_msg_attack, (LPVOID)0x5dc1);
					return;
				}
			}
		}
	}
}

void TaskScript::IsGoonHecheng(DWORD pos)
{
    //可能出问题

    for(int i = 0; i < 10; i++)
    {
        _BAGSTU zhu;
        if(gcall.GetGoodsByEquipPos(pos, &zhu) == FALSE)
        {
            log(_T("装备位置没有物品:%d"), pos);
            return;
        }
        else
        {
            if((zhu.m_PingJi == 5 &&
                    (zhu.m_DangQianJingYanZhi == zhu.m_DangQianJingYanZongZhi))
                    ||
                    (zhu.m_PingJi == 10 &&
                     zhu.m_DangQianJingYanZhi == zhu.m_DangQianJingYanZongZhi))
            {
                log(_T("要强化的物品已满级:%d"), pos);
                Sleep(1000);
                return;
            }
            else
            {
                gcall.HeChengWuQiByHun((EQUITMENT_POS)pos);//수련보옥36级首饰魂

                Sleep(1000);
            }
        }
    }
}




////////////////////Task函数线///////////////////////////////

