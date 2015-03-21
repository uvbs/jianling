<<<<<<< HEAD
﻿#include "stdafx.h"
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
    { TEXT("904"), &TaskScript::Task_904 },//3-
    { TEXT("905"), &TaskScript::Task_905 },//3-

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



void TaskScript::Task_901(int zid, int taskid)
{
	BOOL flag_go;
	flag_go = FALSE;
	BOOL flag_43_go;
	flag_43_go = FALSE;
    switch(taskid)
    {

        case 1:
            while(true)
            {
                _BAGSTU wuqi;
                gcall.GetGoodsByEquipPos(WUQI, &wuqi);
                if(wuqi.name != NULL)
                {
                    int len = wcslen(L"진 요마도끼");//判断是不是当前拿的这个武器,如果不是这把武器，可能是已经破10后的武器,或者重新换过武器?
                    wchar_t* fixName = new wchar_t[len + 1];
                    wcscpy(fixName, L"진 요마도끼");
                    fixName[len] = L' ';
                    fixName[len + 1] = L'\0';
                    if(wcsstr(wuqi.name, fixName) != NULL)
                    {
                        if(wuqi.m_PingJi == 10 &&
                                wuqi.m_DangQianJingYanZhi == wuqi.m_DangQianJingYanZongZhi)
                        {
                            gcall.XieBaoShi(0);
                            Sleep(1000);
                            gcall.XieBaoShi(1);
                            Sleep(1000);
                            gcall.XieBaoShi(2);
                            Sleep(1000);
                            while(true)
                            {
                                Sleep(1000);
                                if(gcall.XieZhuangBei(WUQI))
                                {
                                    gcall.HeChengWuQi_Po10(L"진 요마도끼 10단계", L"염화도끼");
                                    Sleep(1000);
                                    break;//跳脱装备的循环
                                }
                            }
                            break;//跳整个破10的循环
                        }
                        else
                            gcall.HeChengWuQiByHun(WUQI);
                    }
                    else
                        break;//当前拿的不是要突破的武器，可能已经破10
                }
                else
                {
                    //name=null 有可能是已经破10 还在背包里
                    break;
                }
            }

            //MessageBox(0, L"摇奖完", L"装八卦", MB_OK);
            _BAGSTU zwuqi;
            while(true)
            {
				ZeroMemory(&zwuqi, sizeof(_BAGSTU));
				if(gcall.GetGoodsByEquipPos(WUQI, &zwuqi) == FALSE)
				{
					gcall.WearEquipment(L"각성 염화도끼 1단계", WUQI);
					Sleep(1000);
					gcall.HeChengWuQiByHun(WUQI);
					Sleep(1000);
					gcall.JiaBaoShi(0, L"빛나는 오각 자수정"); //5角紫宝石
					Sleep(1000);
					gcall.JiaBaoShi(1, L"빛나는 오각 금강석"); //加白5角宝石
					Sleep(1000);
					gcall.JiaBaoShi(2, L"빛나는 사각 홍옥"); //4角红宝石
					Sleep(1000);
				}else
				{
					if (wcsstr(zwuqi.name,L"각성 염화도끼") != NULL)
					{
						break;
					}else
					{
						MessageBox(0, L"装备武器非각성 염화도끼,手动处理。", L"装备", MB_OK);
					}
				}
				
            }

			if (gcall.GetPlayerLevel() < 39)
			{
				gcall.CityConvey(0x37);//传送到36级副本
				gcall.Stepto(71652,36676,-2691);
				gcall.Stepto(71676,36911,-2694);
				gcall.Stepto(71695,37158,-2695);
				gcall.Stepto(71695,37406,-2695);
				Sleep(1000);
				gcall.SellItemByConfig(L"나신용");
				Sleep(1000);
				gcall.SortBag();
				lianji36_go();
				while (true)
				{
					if (gcall.GetPlayerLevel() < 39)
					{
						UseExperience();
						lianji36();
					}else
					{
						break;
					}
				}
			}
			//跳出后去买卖和修理武器
			flag_go = gcall.Stepto(75872,44383,-2460,10,10,3000);
			if (flag_go)
			{
				Sleep(1000);
				gcall.Shunyi(L"Lianji36-end-mai");
				Sleep(1000);
				gcall.sendcall(id_msg_OverShunyi,(LPVOID)FALSE);
				Sleep(3000);
				gcall.Stepto(73043,38689,-2050);
			}
			gcall.WaitPlans();
			Sleep(1000);
			gcall.Stepto(73044,38638,-2050);
			gcall.Stepto(73048,38390,-2050);
			gcall.Stepto(73040,38142,-2088);
			gcall.Stepto(73031,37894,-2217);
			gcall.Stepto(73002,37650,-2344);
			gcall.Stepto(72910,37420,-2402);
			gcall.Stepto(72792,37202,-2540);
			gcall.Stepto(72673,36984,-2670);
			gcall.Stepto(72528,36789,-2694);
			gcall.Stepto(72300,36764,-2693);
			gcall.Stepto(72069,36853,-2693);
			gcall.Stepto(71858,36982,-2694);
			gcall.Stepto(71704,37176,-2694);
			gcall.Stepto(71535,37413,-2695);
			Sleep(1000);
			gcall.FixWuqi();
			Sleep(1000);
			gcall.Stepto(71695,37366,-2694);
			Sleep(1000);
			gcall.HeChengWuQi(WUQI);
			Sleep(1000);
			gcall.FenJieByConfig();
			Sleep(1000);
			gcall.SellItemByConfig(L"나신용");
			Sleep(1000);
			gcall.SortBag();
			Sleep(1000);
			gcall.AddTalent(0x12D);//加R 3-1
			gcall.AddTalent(0x12E);//加R 4-1
			gcall.AddTalent(0x13E);//加T 1-1
			if (gcall.isTalentPanelShow())
			{
				gcall.OpenTalentUI();
				Sleep(1000);
			}
			//执行3-1任务
			gcall.NewSpend(2.5);
			gcall.Stepto(73033,38537,-2050);
			gcall.Stepto(73036,38371,-2050);
			gcall.Stepto(73043,38119,-2100);
			gcall.Stepto(73036,37874,-2227);
			gcall.Stepto(73022,37624,-2358);
			gcall.Stepto(72974,37379,-2402);
			gcall.Stepto(72858,37164,-2545);
			gcall.Stepto(72741,36949,-2673);
			gcall.Stepto(72546,36803,-2694);
			gcall.Stepto(72312,36747,-2693);
			gcall.Stepto(72068,36819,-2694);
			gcall.Stepto(71839,36901,-2694);
			gcall.Stepto(71601,36986,-2694);
			gcall.Stepto(71368,37069,-2695);
			gcall.Stepto(71147,37148,-2694);
			gcall.Stepto(70912,37232,-2695);
			gcall.Stepto(70677,37316,-2700);
			gcall.Stepto(70630,37333,-2702);
			gcall.Stepto(70447,37230,-2712);
			gcall.Stepto(70232,37113,-2735);
			gcall.Stepto(70016,36995,-2765);
			gcall.Stepto(69898,36931,-2783);
			gcall.Stepto(69847,36867,-2796);
			gcall.Stepto(69694,36677,-2835);
			gcall.Stepto(69539,36483,-2862);
			gcall.Stepto(69383,36290,-2870);
			gcall.Stepto(69224,36092,-2863);
			gcall.Stepto(69072,35902,-2816);
			gcall.Stepto(68919,35713,-2767);
			gcall.Stepto(68761,35516,-2723);
			gcall.Stepto(68607,35323,-2701);
			gcall.Stepto(68415,35168,-2698);
			gcall.Stepto(68202,35046,-2693);
			gcall.Stepto(67970,34970,-2686);
			gcall.Stepto(67719,35000,-2684);
			gcall.Stepto(67481,35058,-2681);
			gcall.Stepto(67238,35118,-2669);
			gcall.Stepto(67001,35176,-2657);
			gcall.Stepto(66756,35237,-2651);
			gcall.Stepto(66519,35294,-2658);
			gcall.Stepto(66279,35247,-2668);
			gcall.Stepto(66039,35165,-2681);
			gcall.Stepto(65805,35086,-2697);
			gcall.Stepto(65575,35007,-2704);
			gcall.Stepto(65352,34931,-2719);
			gcall.Stepto(65207,34882,-2733);
			gcall.Stepto(65041,34826,-2746);
			gcall.Stepto(64857,34763,-2754);
			gcall.Stepto(64668,34699,-2771);
			gcall.Stepto(64483,34636,-2800);
			gcall.Stepto(64292,34571,-2835);
			gcall.Stepto(64103,34506,-2860);
			gcall.Stepto(63916,34443,-2873);
			gcall.Stepto(63709,34372,-2894);
			gcall.Stepto(63584,34177,-2921);
			gcall.Stepto(63566,34128,-2930);
			gcall.Stepto(63495,33933,-2959);
			gcall.Stepto(63411,33700,-2984);
			gcall.Stepto(63341,33509,-3008);
			gcall.Stepto(63275,33323,-3037);
			gcall.Stepto(63209,33136,-3065);
			gcall.Stepto(63144,32951,-3075);
			gcall.Stepto(63077,32759,-3105);
			gcall.Stepto(63012,32574,-3151);
			gcall.Stepto(62947,32386,-3201);
			gcall.Stepto(62880,32195,-3253);
			gcall.Stepto(62827,32006,-3300);
			gcall.Stepto(62780,31815,-3343);
			gcall.Stepto(62732,31617,-3385);
			gcall.Stepto(62682,31414,-3424);
			gcall.Stepto(62624,31226,-3457);
			gcall.Stepto(62510,31057,-3491);
			gcall.Stepto(62380,30910,-3521);
			gcall.Stepto(62217,30801,-3548);
			gcall.Stepto(62019,30715,-3583);
			gcall.Stepto(61784,30652,-3625);
			gcall.Stepto(61533,30622,-3664);
			gcall.Stepto(61286,30603,-3690);
			gcall.Stepto(61084,30587,-3707);
			gcall.Stepto(61019,30568,-3712);
			gcall.Stepto(60825,30510,-3719);
			gcall.Stepto(60637,30454,-3711);
			gcall.Stepto(60432,30410,-3686);
			gcall.Stepto(60198,30387,-3659);
			gcall.Stepto(60186,30387,-3657);
			gcall.Stepto(60351,30765,-3707);
			gcall.Stepto(60354,30778,-3708);
			gcall.Stepto(60421,30996,-3733);
			gcall.Stepto(60496,31218,-3753);
			gcall.Stepto(60542,31345,-3769);
			gcall.Stepto(60590,31477,-3790);
			gcall.Stepto(60636,31605,-3805);
			gcall.Stepto(60671,31736,-3821);
			gcall.Stepto(60687,31885,-3843);
			gcall.Stepto(60695,31960,-3855);
			gcall.Stepto(60704,32036,-3868);
			gcall.Stepto(60713,32111,-3880);
			gcall.Stepto(60722,32187,-3892);
			gcall.Stepto(60731,32266,-3904);
			gcall.Stepto(60743,32368,-3920);
			gcall.Stepto(60767,32570,-3948);
			gcall.Stepto(60783,32709,-3966);
			gcall.Stepto(60800,32844,-3985);
			gcall.Stepto(60817,32984,-4004);
			gcall.Stepto(60834,33118,-4018);
			gcall.Stepto(60864,33323,-4030);
			gcall.Stepto(60912,33594,-4043);
			gcall.Stepto(60962,33879,-4046);
			gcall.Stepto(61018,34200,-4026);
			gcall.Stepto(61046,34359,-4007);
			gcall.Stepto(61063,34497,-3989);
			gcall.Stepto(61057,34633,-3970);
			gcall.Stepto(61044,34888,-3934);
			gcall.Stepto(61033,35106,-3904);
			gcall.Stepto(61024,35246,-3883);
			gcall.Stepto(60981,35410,-3855);
			gcall.Stepto(60841,35644,-3816);
			gcall.Stepto(60615,35877,-3761);
			gcall.Stepto(60514,35968,-3740);
			gcall.Stepto(60399,36036,-3715);
			gcall.Stepto(60274,36102,-3693);
			gcall.Stepto(60134,36108,-3676);
			gcall.Stepto(60000,36089,-3660);
			gcall.Stepto(59843,36066,-3645);
			gcall.Stepto(59533,36023,-3619);
			gcall.Stepto(59268,35974,-3597);
			gcall.Stepto(59104,35867,-3585);
			gcall.Stepto(59017,35695,-3575);
			gcall.Stepto(58966,35506,-3557);
			gcall.Stepto(58916,35310,-3524);
			gcall.Stepto(58856,35075,-3493);
			gcall.Stepto(58794,34833,-3467);
			gcall.Stepto(58712,34591,-3439);
			gcall.Stepto(58602,34373,-3414);
			gcall.Stepto(58441,34185,-3386);
			gcall.Stepto(58284,34053,-3364);
			gcall.Stepto(58121,33948,-3342);
			gcall.Stepto(57950,33840,-3315);
			gcall.Stepto(57788,33742,-3296);
			gcall.Stepto(57602,33653,-3262);
			gcall.Stepto(57423,33564,-3225);
			gcall.Stepto(57250,33473,-3198);
			gcall.Stepto(57071,33379,-3167);
			gcall.Stepto(56898,33288,-3135);
			gcall.Stepto(56721,33195,-3105);
			gcall.Stepto(56544,33101,-3089);
			gcall.Stepto(56364,33009,-3087);
			gcall.Stepto(56173,32968,-3083);
			gcall.Stepto(55972,32958,-3056);
			gcall.Stepto(55776,32953,-2998);
			gcall.Stepto(55532,32946,-3021);
			gcall.Stepto(55290,32970,-3048);
			gcall.Stepto(55054,33064,-3039);
			gcall.Stepto(54830,33161,-3033);
			gcall.Stepto(54607,33282,-3021);
			gcall.Stepto(54396,33410,-3000);
			gcall.Stepto(54187,33538,-2974);
			gcall.Stepto(53976,33666,-2949);
			gcall.Stepto(53760,33798,-2933);
			gcall.Stepto(53544,33929,-2929);
			gcall.Stepto(53335,34056,-2931);
			gcall.Stepto(53119,34188,-2932);
			gcall.Stepto(52910,34315,-2932);
			gcall.Stepto(52694,34446,-2932);
			gcall.Stepto(52485,34573,-2932);
			gcall.Stepto(52478,34578,-2932);
			gcall.Stepto(52475,34577,-2932);
			gcall.Stepto(52238,34504,-2932);
			gcall.Stepto(52003,34438,-2924);
			gcall.Stepto(51759,34370,-2903);
			gcall.Stepto(51524,34304,-2906);
			gcall.Stepto(51475,34290,-2906);
			gcall.Stepto(51476,34133,-2900);
			gcall.Stepto(51477,33880,-2894);
			gcall.Stepto(51478,33635,-2891);
			gcall.Stepto(51479,33382,-2899);
			gcall.Stepto(51480,33148,-2906);
			gcall.Stepto(51507,33117,-2906);
			gcall.Stepto(51684,32943,-2907);
			gcall.Stepto(51863,32770,-2915);
			gcall.Stepto(52044,32594,-2937);
			gcall.Stepto(52220,32424,-2956);
			gcall.Stepto(52360,32289,-2967);
			gcall.Stepto(52340,32201,-2970);
			gcall.Stepto(52286,31954,-2989);
			gcall.Stepto(52233,31715,-3011);
			gcall.Stepto(52209,31603,-3016);
			gcall.Stepto(52163,31549,-3021);
			gcall.Stepto(51998,31357,-3042);
			gcall.Stepto(51837,31162,-3078);
			gcall.Stepto(51683,30972,-3119);
			gcall.Stepto(51524,30775,-3159);
			gcall.Stepto(51371,30584,-3193);
			gcall.Stepto(51233,30414,-3217);
			gcall.Stepto(51185,30415,-3222);
			gcall.Stepto(50932,30419,-3242);
			gcall.Stepto(50679,30423,-3267);
			gcall.Stepto(50438,30427,-3297);
			gcall.Stepto(50185,30432,-3345);
			gcall.Stepto(50067,30468,-3369);
			gcall.Stepto(49838,30577,-3413);
			gcall.Stepto(49623,30692,-3454);
			gcall.Stepto(49409,30827,-3484);
			gcall.Stepto(49245,30935,-3494);
			gcall.Stepto(49162,30991,-3475);
			gcall.Stepto(49108,31026,-3468);
			gcall.Stepto(49067,31054,-3465);
			gcall.NewSpend(1);
			gcall.Stepto(48959,31125,-3480);
			gcall.Stepto(48859,31183,-3460);
			gcall.Stepto(48630,31291,-3397);
			gcall.Stepto(48407,31392,-3301);
			gcall.Stepto(48177,31496,-3200);
			gcall.Stepto(47951,31599,-3103);
			gcall.Stepto(47706,31645,-3030);
			gcall.Stepto(47472,31616,-2994);
			gcall.Stepto(47311,31585,-2972);
			gcall.Stepto(47172,31565,-2948);
			gcall.Stepto(46929,31533,-2911);
			gcall.Stepto(46787,31516,-2896);
			gcall.Stepto(46672,31503,-2885);
			gcall.Stepto(46544,31488,-2873);
			gcall.Stepto(46303,31459,-2847);
			gcall.Stepto(46278,31456,-2844);
			gcall.NewSpend(2.5);
			gcall.Stepto(46188,31447,-2838);
			gcall.Stepto(45945,31420,-2824);
			gcall.Stepto(45702,31394,-2823);
			gcall.Stepto(45461,31349,-2830);
			gcall.Stepto(45225,31254,-2833);
			gcall.Stepto(44999,31162,-2836);
			gcall.Stepto(44770,31075,-2838);
			gcall.Stepto(44520,31075,-2841);
			gcall.Stepto(44287,31145,-2846);
			gcall.Stepto(44061,31258,-2850);
			gcall.Stepto(43851,31378,-2850);
			gcall.Stepto(43632,31505,-2859);
			gcall.Stepto(43417,31630,-2873);
			gcall.Stepto(43201,31744,-2890);
			gcall.Stepto(42964,31799,-2920);
			gcall.Stepto(42715,31843,-2946);
			gcall.Stepto(42469,31880,-2982);
			gcall.Stepto(42223,31915,-3016);
			gcall.Stepto(41981,31950,-3039);
			gcall.Stepto(41730,31987,-3069);
			gcall.Stepto(41488,32022,-3091);
			gcall.Stepto(41260,32103,-3106);
			gcall.Stepto(41043,32215,-3126);
			gcall.Stepto(40819,32333,-3159);
			gcall.Stepto(40605,32466,-3191);
			gcall.Stepto(40419,32625,-3213);
			gcall.Stepto(40230,32787,-3239);
			gcall.Stepto(40055,32956,-3250);
			gcall.Stepto(39893,33151,-3255);
			gcall.Stepto(39762,33347,-3268);
			gcall.Stepto(39652,33571,-3281);
			gcall.Stepto(39548,33802,-3283);
			gcall.Stepto(39521,33864,-3280);
			gcall.NewSpend(1);
			gcall.Stepto(39477,33970,-3275);
			gcall.Stepto(39400,34150,-3269);
			gcall.Stepto(39321,34336,-3262);
			gcall.Stepto(39245,34516,-3249);
			gcall.Stepto(39165,34702,-3226);
			gcall.Stepto(39078,34880,-3215);
			gcall.Stepto(38974,35110,-3189);
			gcall.Stepto(38872,35336,-3148);
			gcall.Stepto(38771,35559,-3095);
			gcall.Stepto(38669,35787,-3071);
			gcall.Stepto(38645,35841,-3069);
			Sleep(2000);
			gcall.Stepto(38541,36073,-3067);
			gcall.WaitPlans();
			gcall.Stepto(38441,36298,-3068);
			gcall.Stepto(38360,36482,-3069);
			gcall.Stepto(38125,36569,-3069);
			gcall.Stepto(38054,36598,-3066);
			gcall.Stepto(37913,36757,-3063);
			gcall.Stepto(37751,36939,-3042);
			gcall.Stepto(37593,37117,-2995);
			gcall.Stepto(37419,37313,-2944);
			gcall.Stepto(37253,37500,-2916);
			gcall.Stepto(37224,37532,-2910);
			gcall.Stepto(37186,37675,-2898);
			gcall.Stepto(37222,37840,-2895);
			gcall.Stepto(37179,37803,-2893);
			Sleep(1000);
			gcall.FixWuqi();
			Sleep(1000);
			gcall.Stepto(37213,37729,-2897);
			gcall.Stepto(37163,37688,-2897);
			gcall.Stepto(37152,37573,-2901);
			gcall.Stepto(37139,37578,-2900);
			gcall.Stepto(36899,37658,-2893);
			gcall.Stepto(36667,37735,-2893);
			gcall.Stepto(36547,37775,-2892);
			gcall.Stepto(36370,37702,-2892);
			gcall.Stepto(36144,37608,-2891);
			gcall.Stepto(35911,37511,-2891);
			gcall.Stepto(35694,37422,-2890);
			gcall.Stepto(35693,37421,-2890);
			gcall.Stepto(35561,37615,-2888);
			gcall.Stepto(35435,37815,-2888);
			gcall.Stepto(35386,37895,-2888);
			gcall.Stepto(35359,37939,-2888);
			gcall.Stepto(35345,38063,-2888);
			gcall.Stepto(35313,38311,-2888);
			gcall.Stepto(35312,38319,-2888);
			Sleep(1000);
			gcall.DeliverQuests(zid,taskid,L"흑풍술사 감마등");
			Sleep(1000);
            break;
        case 2:
			gcall.WaitPlans();
			Sleep(2000);
			gcall.Stepto(48340,47892,5459);
			gcall.Stepto(48541,47894,5450);
			gcall.Stepto(48780,47847,5416);
			gcall.Stepto(48856,47622,5413);
			gcall.Stepto(48790,47424,5383);
			gcall.Stepto(48546,47291,5358);
			gcall.Stepto(48302,47256,5323);
			gcall.Stepto(48054,47275,5272);
			gcall.Stepto(47816,47327,5276);
			gcall.Stepto(47573,47397,5282);
			gcall.Stepto(47455,47432,5284);
			Sleep(1000);
			gcall.DeliverQuests(zid,taskid,L"효준");
			Sleep(1000);
            break;
        case 3:
			gcall.FindThenKill(0,500,modeAoe | modeNormal);
			Sleep(1000);
            break;
        case 4:
			gcall.Stepto(47454,47432,5284);
			gcall.Stepto(47451,47296,5288);
			gcall.Stepto(47386,47057,5287);
			gcall.Stepto(47236,46861,5281);
			gcall.Stepto(47107,46730,5278);
			Sleep(1000);
			gcall.DeliverQuests(zid,taskid,L"청풍");
			Sleep(1000);
            break;
        case 5:
			gcall.NewSpend(2.5);
			gcall.Stepto(46961,46733,5279);
			gcall.Stepto(46714,46758,5280);
			gcall.Stepto(46469,46794,5282);
			gcall.Stepto(46225,46837,5283);
			gcall.Stepto(45996,46932,5291);
			gcall.Stepto(45766,47020,5294);
			gcall.Stepto(45519,47030,5302);
			gcall.Stepto(45275,46989,5311);
			gcall.Stepto(45031,46946,5311);
			gcall.NewSpend(1);
			gcall.Stepto(44809,46907,5311);
			Sleep(1000);
			gcall.sendcall(id_msg_attack, (LPVOID)0x5DE8);//z
			
			gcall.FindThenKill(0,500,modeAoe | modeNormal);
			Sleep(1000);
            break;
        case 6:
			if (gcall.GetCityID() != 4250)
			{

				gcall.Stepto(44781,46900,5311);
				gcall.Stepto(44546,46821,5311);
				gcall.Stepto(44311,46743,5311);
				gcall.Stepto(44075,46668,5311);
				gcall.Stepto(43838,46592,5311);
				gcall.Stepto(43602,46517,5311);
				gcall.Stepto(43366,46439,5311);
				gcall.Stepto(43141,46337,5308);
				gcall.Stepto(43041,46273,5304);
				gcall.Stepto(42981,46216,5301);
				Sleep(2000);
				gcall.Stepto(42863,46107,5291);
				gcall.WaitPlans();
				gcall.Stepto(42841,46087,5288);
				gcall.NewSpend(2.5);
				gcall.Stepto(42811,46060,5264);
				gcall.Stepto(42628,45892,5116);
				gcall.Stepto(42447,45721,4995);
				gcall.Stepto(42267,45550,4842);
				gcall.Stepto(42127,45350,4754);
				gcall.Stepto(42096,45108,4710);
				gcall.Stepto(42135,44859,4694);
				gcall.Stepto(42180,44724,4692);
				//去鱼人洞
				gcall.Stepto(42069,44719,4673);
				gcall.Stepto(42032,44677,4665);
				gcall.Stepto(41892,44472,4629);
				gcall.Stepto(41756,44263,4592);
				gcall.Stepto(41624,44058,4553);
				gcall.Stepto(41491,43852,4515);
				gcall.Stepto(41354,43640,4474);
				gcall.Stepto(41221,43435,4437);
				gcall.Stepto(41150,43195,4402);
				gcall.Stepto(41146,42950,4371);
				gcall.Stepto(41156,42706,4336);
				gcall.Stepto(41175,42454,4306);
				gcall.Stepto(41196,42210,4289);
				gcall.Stepto(41222,41967,4281);
				gcall.Stepto(41248,41722,4266);
				gcall.Stepto(41275,41474,4235);
				gcall.Stepto(41322,41241,4191);
				gcall.Stepto(41397,41001,4138);
				gcall.Stepto(41469,40767,4099);
				gcall.Stepto(41530,40572,4076);
				gcall.Stepto(41589,40383,4052);
				gcall.Stepto(41647,40194,4027);
				gcall.Stepto(41705,40007,4004);
				gcall.Stepto(41765,39814,3985);
				gcall.Stepto(41811,39624,3972);
				gcall.Stepto(41856,39427,3960);
				gcall.Stepto(41899,39240,3949);
				gcall.Stepto(41956,38992,3938);
				gcall.Stepto(42005,38781,3930);
				gcall.Stepto(42067,38511,3910);
				gcall.Stepto(42113,38312,3886);
				gcall.Stepto(42161,38116,3862);
				gcall.Stepto(42216,37928,3840);
				gcall.Stepto(42274,37733,3826);
				gcall.Stepto(42329,37544,3810);
				gcall.Stepto(42388,37314,3794);
				gcall.Stepto(42403,37065,3778);
				gcall.Stepto(42405,36820,3766);
				gcall.Stepto(42407,36565,3752);
				gcall.Stepto(42407,36329,3735);
				gcall.Stepto(42401,36075,3725);
				gcall.Stepto(42395,35831,3709);
				gcall.Stepto(42388,35575,3693);
				gcall.Stepto(42372,35331,3677);
				gcall.Stepto(42325,35090,3663);
				gcall.Stepto(42274,34842,3638);
				gcall.Stepto(42225,34600,3588);
				gcall.Stepto(42158,34366,3541);
				gcall.Stepto(42055,34133,3502);
				gcall.Stepto(41925,33926,3476);
				gcall.Stepto(41768,33739,3455);
				gcall.Stepto(41597,33565,3437);
				gcall.Stepto(41439,33367,3412);
				gcall.Stepto(41286,33176,3381);
				gcall.Stepto(41113,33011,3367);
				gcall.Stepto(40859,32998,3389);
				gcall.Stepto(40616,33019,3454);
				gcall.Stepto(40372,33040,3484);
				gcall.Stepto(40127,33060,3501);
				gcall.Stepto(39933,32962,3523);
				gcall.Stepto(39899,32720,3536);
				gcall.Stepto(39864,32478,3551);
				gcall.Stepto(39829,32232,3557);
				gcall.Stepto(39826,31980,3553);
				gcall.Stepto(39889,31744,3553);
				gcall.Stepto(39972,31506,3540);
				gcall.Stepto(40125,31627,3545);
				gcall.Stepto(40084,31865,3554);
				gcall.Stepto(40009,32098,3555);
				gcall.Stepto(39943,32306,3558);
				gcall.Stepto(39905,32505,3550);
				gcall.Stepto(39898,32700,3537);
				gcall.Stepto(39900,32903,3528);
				gcall.Stepto(39902,33107,3515);
				gcall.Stepto(39905,33354,3491);
				gcall.Stepto(39840,33581,3473);
				gcall.Stepto(39654,33752,3450);
				gcall.Stepto(39453,33891,3419);
				gcall.Stepto(39257,34024,3391);
				gcall.Stepto(39241,34056,3384);
				gcall.Stepto(39235,34145,3369);
				gcall.Stepto(39232,34398,3371);
				gcall.Stepto(39225,34451,3371);
				gcall.Stepto(38990,34512,3363);
				gcall.Stepto(38757,34439,3346);
				gcall.Stepto(38522,34347,3345);
				gcall.Stepto(38284,34297,3374);
				gcall.Stepto(38040,34300,3421);
				gcall.Stepto(37792,34348,3445);
				gcall.Stepto(37552,34398,3452);
				gcall.Stepto(37312,34442,3454);
				gcall.Stepto(37071,34485,3445);
				gcall.Stepto(36831,34530,3434);
				gcall.Stepto(36594,34591,3413);
				gcall.Stepto(36349,34653,3396);
				gcall.Stepto(36118,34733,3386);
				gcall.Stepto(35904,34810,3392);
				gcall.Stepto(35730,34683,3395);
				gcall.Stepto(35532,34538,3393);
				gcall.Stepto(35328,34389,3382);
				gcall.Stepto(35131,34245,3362);
				gcall.Stepto(34926,34096,3328);
				gcall.Stepto(34715,33974,3320);
				gcall.Stepto(34481,33897,3324);
				gcall.Stepto(34244,33821,3341);
				gcall.Stepto(34008,33745,3374);
				gcall.Stepto(33768,33668,3410);
				gcall.Stepto(33535,33594,3444);
				gcall.Stepto(33287,33551,3488);
				gcall.Stepto(33090,33595,3522);
				gcall.NewSpend(1);
				gcall.Stepto(33060,33604,3529);
				gcall.Stepto(32825,33671,3567);
				gcall.Stepto(32590,33738,3604);
				gcall.Stepto(32352,33794,3626);
				gcall.Stepto(32100,33807,3622);
				gcall.Stepto(31857,33777,3591);
				gcall.Stepto(31607,33741,3541);
				gcall.Stepto(31366,33705,3488);
				gcall.Stepto(31124,33670,3439);
				gcall.Stepto(30873,33634,3407);
				gcall.Stepto(30633,33589,3390);
				gcall.Stepto(30401,33489,3376);
				gcall.Stepto(30180,33384,3360);
				gcall.Stepto(29972,33246,3343);
				gcall.WaitPlans();
				gcall.Stepto(10390,21168,2234);
				//到37摇奖那张图
				gcall.NewSpend(2.5);
				gcall.Stepto(10454,20870,2124);
				gcall.Stepto(10500,20630,2030);
				gcall.Stepto(10548,20382,1943);
				gcall.Stepto(10660,20166,1854);
				gcall.Stepto(10788,19958,1766);
				gcall.Stepto(10918,19746,1691);
				gcall.Stepto(11046,19538,1604);
				gcall.Stepto(11172,19338,1526);
				gcall.Stepto(11339,19160,1455);
				gcall.Stepto(11507,18982,1394);
				gcall.Stepto(11681,18799,1338);
				gcall.Stepto(11850,18622,1279);
				gcall.Stepto(12005,18434,1237);
				gcall.Stepto(12111,18250,1225);
				gcall.Stepto(12182,18071,1220);
				gcall.Stepto(12255,17890,1226);
				gcall.Stepto(12322,17707,1236);
				gcall.Stepto(12361,17515,1270);
				gcall.Stepto(12376,17313,1308);
				gcall.Stepto(12381,17118,1345);
				gcall.Stepto(12347,16925,1380);
				gcall.Stepto(12272,16745,1438);
				gcall.Stepto(12186,16569,1487);
				gcall.Stepto(12081,16396,1536);
				gcall.Stepto(11978,16230,1572);
				gcall.Stepto(11870,16059,1604);
				gcall.Stepto(11767,15893,1635);
				gcall.Stepto(11667,15733,1667);
				gcall.Stepto(11563,15567,1698);
				gcall.Stepto(11457,15402,1730);
				gcall.NewSpend(1);
				gcall.Stepto(11308,15267,1760);
				gcall.Stepto(11138,15172,1792);
				gcall.Stepto(10956,15082,1822);
				gcall.Stepto(10781,14995,1854);
				gcall.Stepto(10733,14971,1861);
				gcall.Stepto(10678,14943,1868);
				gcall.Stepto(10503,14856,1896);
				gcall.Stepto(10322,14765,1931);
				gcall.Stepto(10148,14677,1966);
				gcall.Stepto(9991,14561,2003);
				gcall.Stepto(9872,14462,2032);
				gcall.Stepto(9820,14418,2044);
				gcall.Stepto(9633,14261,2087);
				gcall.WaitPlans();
				gcall.Stepto(9435,14103,2134);
				gcall.Stepto(9259,13959,2180);
				gcall.NewSpend(2.5);
				gcall.Stepto(9163,13880,2204);
				gcall.Stepto(8967,13722,2256);
				gcall.Stepto(8776,13570,2315);
				gcall.Stepto(8585,13417,2362);
				gcall.Stepto(8394,13264,2411);
				gcall.Stepto(8196,13106,2464);
				gcall.Stepto(8018,12940,2497);
				gcall.Stepto(7904,12724,2531);
				gcall.Stepto(7818,12489,2565);
				gcall.Stepto(7747,12255,2604);
				gcall.Stepto(7678,12025,2644);
				gcall.Stepto(7621,11835,2676);
				gcall.Stepto(7563,11641,2706);
				gcall.Stepto(7506,11454,2740);
				gcall.Stepto(7442,11272,2776);
				gcall.Stepto(7321,11107,2824);
				gcall.Stepto(7196,10948,2865);
				gcall.Stepto(7080,10800,2896);
				gcall.Stepto(6954,10641,2938);
				gcall.Stepto(6809,10455,2992);
				gcall.Stepto(6662,10272,3044);
				gcall.Stepto(6544,10193,3070);
				gcall.Stepto(6340,10059,3114);
				gcall.Stepto(6136,9924,3156);
				gcall.Stepto(5933,9788,3185);
				gcall.Stepto(5753,9607,3199);
				gcall.Stepto(5584,9431,3216);
				gcall.Stepto(5415,9254,3236);
				gcall.Stepto(5372,9211,3240);
				gcall.Stepto(5135,9173,3243);
				gcall.Stepto(4888,9118,3240);
				gcall.Stepto(4647,9060,3228);
				gcall.Stepto(4410,9000,3205);
				gcall.Stepto(4168,8939,3171);
				gcall.Stepto(3934,8880,3133);
				gcall.Stepto(3685,8831,3084);
				gcall.Stepto(3440,8838,3031);
				gcall.Stepto(3194,8859,2971);
				gcall.Stepto(2947,8876,2915);
				gcall.Stepto(2703,8876,2861);
				gcall.Stepto(2450,8871,2807);
				gcall.Stepto(2205,8867,2754);
				gcall.Stepto(1953,8862,2711);
				gcall.Stepto(1707,8858,2669);
				gcall.Stepto(1460,8854,2638);
				gcall.Stepto(1223,8927,2604);
				gcall.Stepto(1001,9030,2580);
				gcall.Stepto(769,9132,2563);
				gcall.Stepto(543,9225,2535);
				gcall.Stepto(308,9291,2510);
				gcall.Stepto(64,9358,2483);
				gcall.Stepto(-174,9325,2458);
				gcall.Stepto(-376,9243,2447);
				gcall.Stepto(-600,9144,2437);
				gcall.Stepto(-819,9036,2427);
				gcall.Stepto(-1037,8927,2419);
				gcall.Stepto(-1259,8824,2414);
				gcall.Stepto(-1486,8734,2410);
				gcall.Stepto(-1736,8692,2413);
				gcall.Stepto(-1977,8656,2396);
				gcall.Stepto(-2216,8642,2380);
				gcall.Stepto(-2456,8689,2367);
				gcall.Stepto(-2696,8740,2352);
				gcall.Stepto(-2947,8793,2331);
				gcall.Stepto(-2980,8800,2327);
				gcall.Stepto(-2963,8825,2327);
				gcall.Stepto(-2841,9038,2323);
				gcall.Stepto(-2724,9252,2323);
				gcall.Stepto(-2609,9477,2323);
				gcall.Stepto(-2498,9695,2323);
				gcall.Stepto(-2382,9920,2323);
				gcall.Stepto(-2367,9950,2323);
				gcall.Stepto(-2479,9755,2323);
				gcall.Stepto(-2602,9544,2323);
				gcall.Stepto(-2757,9356,2323);
				gcall.Stepto(-2934,9187,2323);
				gcall.Stepto(-3131,9028,2319);
				gcall.Stepto(-3324,8879,2305);
				gcall.Stepto(-3515,8726,2293);
				gcall.Stepto(-3714,8568,2281);
				gcall.Stepto(-3905,8415,2268);
				gcall.Stepto(-4081,8247,2256);
				gcall.Stepto(-4185,8065,2244);
				gcall.Stepto(-4268,7837,2227);
				gcall.Stepto(-4305,7632,2211);
				gcall.Stepto(-4348,7391,2200);
				gcall.Stepto(-4391,7151,2177);
				gcall.Stepto(-4435,6909,2125);
				gcall.Stepto(-4477,6673,2064);
				gcall.Stepto(-4525,6425,2043);
				gcall.Stepto(-4598,6191,2017);
				gcall.Stepto(-4685,5963,1988);
				gcall.Stepto(-4794,5744,1951);
				gcall.Stepto(-4922,5523,1896);
				gcall.Stepto(-5047,5307,1871);
				gcall.Stepto(-5168,5099,1860);
				gcall.Stepto(-5295,4880,1870);
				gcall.Stepto(-5417,4671,1870);
				gcall.Stepto(-5541,4451,1865);
				gcall.Stepto(-5661,4238,1860);
				gcall.Stepto(-5778,4030,1854);
				gcall.Stepto(-5902,3810,1847);
				gcall.Stepto(-6022,3596,1842);
				gcall.Stepto(-6142,3383,1845);
				gcall.Stepto(-6303,3192,1841);
				gcall.Stepto(-6528,3100,1812);
				gcall.Stepto(-6779,3070,1761);
				gcall.Stepto(-7022,3048,1707);
				gcall.Stepto(-7266,3026,1637);
				gcall.Stepto(-7518,3004,1580);
				gcall.Stepto(-7743,2983,1535);
				gcall.Stepto(-7987,2961,1484);
				gcall.Stepto(-8235,2939,1425);
				gcall.Stepto(-8480,2917,1364);
				gcall.Stepto(-8732,2894,1307);
				gcall.Stepto(-8975,2902,1267);
				gcall.Stepto(-9223,2953,1227);
				gcall.Stepto(-9455,3032,1200);
				gcall.Stepto(-9686,3111,1172);
				gcall.Stepto(-9927,3193,1153);
				gcall.Stepto(-10149,3294,1134);
				gcall.Stepto(-10372,3413,1116);
				gcall.Stepto(-10589,3527,1111);
				gcall.Stepto(-10813,3645,1100);
				gcall.Stepto(-11025,3766,1092);
				gcall.Stepto(-11238,3902,1088);
				gcall.Stepto(-11443,4032,1081);
				gcall.Stepto(-11656,4168,1068);
				gcall.Stepto(-11864,4300,1073);
				gcall.Stepto(-12078,4436,1061);
				gcall.Stepto(-12299,4524,1058);
				gcall.Stepto(-12550,4546,1056);
				gcall.Stepto(-12794,4532,1058);
				gcall.Stepto(-13047,4515,1056);
				gcall.Stepto(-13293,4498,1052);
				gcall.Stepto(-13545,4480,1050);
				gcall.Stepto(-13787,4443,1044);
				gcall.Stepto(-14036,4399,1037);
				gcall.Stepto(-14277,4357,1037);
				gcall.Stepto(-14527,4313,1041);
				gcall.Stepto(-14769,4284,1044);
				gcall.Stepto(-15021,4256,1049);
				gcall.Stepto(-15264,4229,1047);
				gcall.Stepto(-15515,4202,1040);
				gcall.Stepto(-15753,4151,1035);
				gcall.Stepto(-15966,4016,1029);
				gcall.Stepto(-16164,3871,1025);
				gcall.Stepto(-16362,3715,1022);
				gcall.Stepto(-16555,3563,1016);
				gcall.Stepto(-16754,3406,1021);
				gcall.Stepto(-16969,3292,1029);
				gcall.Stepto(-17203,3220,1034);
				gcall.Stepto(-17444,3145,1039);
				gcall.Stepto(-17686,3070,1050);
				gcall.Stepto(-17922,3007,1060);
				gcall.Stepto(-18165,2978,1063);
				gcall.Stepto(-18409,2945,1048);
				gcall.Stepto(-18659,2911,1050);
				gcall.Stepto(-18907,2877,1087);
				gcall.Stepto(-19150,2844,1124);
				gcall.Stepto(-19400,2810,1140);
				gcall.Stepto(-19641,2770,1123);
				gcall.Stepto(-19884,2719,1111);
				gcall.Stepto(-20116,2674,1110);
				gcall.Stepto(-20372,2625,1117);
				gcall.Stepto(-20620,2577,1118);
				gcall.Stepto(-20860,2531,1118);
				gcall.Stepto(-21108,2483,1111);
				gcall.Stepto(-21348,2437,1100);
				gcall.Stepto(-21597,2389,1082);
				gcall.Stepto(-21841,2342,1065);
				gcall.Stepto(-22078,2284,1046);
				gcall.Stepto(-22316,2197,1021);
				gcall.Stepto(-22543,2105,1004);
				gcall.Stepto(-22778,2011,983);
				gcall.Stepto(-23021,1945,951);
				gcall.Stepto(-23262,1902,916);
				gcall.Stepto(-23512,1866,875);
				gcall.Stepto(-23756,1850,843);
				gcall.Stepto(-24009,1832,820);
				gcall.Stepto(-24252,1810,810);
				gcall.Stepto(-24503,1779,804);
				gcall.Stepto(-24746,1750,795);
				gcall.Stepto(-24993,1696,783);
				gcall.Stepto(-25231,1637,776);
				gcall.Stepto(-25475,1606,765);
				gcall.Stepto(-25725,1633,751);
				gcall.Stepto(-25943,1742,750);
				gcall.Stepto(-26144,1895,769);
				gcall.Stepto(-26342,2052,788);
				gcall.Stepto(-26534,2204,800);
				gcall.Stepto(-26733,2360,804);
				gcall.Stepto(-26920,2518,804);
				gcall.Stepto(-27047,2628,800);
				gcall.NewSpend(1);
				gcall.Stepto(-27096,2670,799);
				gcall.Stepto(-27282,2830,796);
				gcall.Stepto(-27473,2995,801);
				gcall.Stepto(-27667,3144,809);
				gcall.Stepto(-27874,3289,817);
				gcall.Stepto(-28075,3429,834);
				gcall.Stepto(-28275,3569,847);
				gcall.Stepto(-28476,3708,853);
				gcall.Stepto(-28676,3850,851);
				gcall.Stepto(-28866,4015,851);
				gcall.Stepto(-28988,4227,845);
				gcall.Stepto(-29087,4459,831);
				gcall.Stepto(-29175,4687,813);
				gcall.Stepto(-29223,4810,795);
				gcall.Stepto(-29272,4938,776);
				gcall.Stepto(-29340,5183,740);
				gcall.WaitPlans();
				gcall.Stepto(-29389,5425,712);
				gcall.NewSpend(2.5);
				gcall.Stepto(-29438,5668,689);
				gcall.Stepto(-29486,5908,667);
				gcall.Stepto(-29504,5998,663);
				gcall.Stepto(-29509,6012,663);
				gcall.Stepto(-29626,6235,651);
				gcall.Stepto(-29755,6443,636);
				gcall.Stepto(-29884,6651,620);
				gcall.Stepto(-29969,6787,610);
				gcall.Stepto(-30090,6810,601);
				gcall.Stepto(-30339,6858,576);
				gcall.Stepto(-30579,6905,544);
				gcall.Stepto(-30819,6951,548);
				gcall.Stepto(-31067,6999,559);
				gcall.Stepto(-31308,7041,578);
				gcall.Stepto(-31551,6976,581);
				gcall.Stepto(-31780,6892,557);
				gcall.Stepto(-32010,6808,522);
				gcall.Stepto(-32247,6721,483);
				gcall.Stepto(-32477,6637,449);
				gcall.Stepto(-32707,6553,404);
				gcall.Stepto(-32944,6466,358);
				gcall.Stepto(-33181,6415,311);
				gcall.Stepto(-33430,6455,262);
				gcall.Stepto(-33669,6515,211);
				gcall.Stepto(-33906,6576,173);
				gcall.Stepto(-34105,6719,137);
				gcall.Stepto(-34198,6943,121);
				gcall.Stepto(-34241,7188,111);
				gcall.Stepto(-34283,7433,90);
				gcall.Stepto(-34325,7674,72);
				gcall.Stepto(-34369,7923,55);
				gcall.Stepto(-34411,8165,33);
				gcall.Stepto(-34453,8406,15);
				gcall.Stepto(-34498,8655,-7);
				gcall.Stepto(-34550,8894,-30);
				gcall.Stepto(-34617,9129,-55);
				gcall.Stepto(-34686,9364,-75);
				gcall.Stepto(-34754,9601,-82);
				gcall.Stepto(-34836,9834,-78);
				gcall.Stepto(-34984,10039,-86);
				gcall.Stepto(-35133,10234,-94);
				gcall.Stepto(-35287,10435,-90);
				gcall.Stepto(-35438,10631,-95);
				gcall.Stepto(-35467,10649,-99);
				gcall.Stepto(-35709,10613,-122);
				gcall.Stepto(-35944,10577,-127);
				gcall.Stepto(-36192,10540,-136);
				gcall.Stepto(-36438,10503,-134);
				gcall.Stepto(-36683,10465,-119);
				gcall.Stepto(-36925,10428,-105);
				gcall.Stepto(-37100,10402,-98);
				gcall.Stepto(-37107,10389,-98);
				gcall.Stepto(-37217,10171,-101);
				gcall.Stepto(-37331,9945,-96);
				gcall.Stepto(-37441,9726,-91);
				gcall.Stepto(-37555,9500,-85);
				gcall.Stepto(-37590,9426,-82);
				gcall.Stepto(-37614,9175,-72);
				gcall.Stepto(-37638,8932,-56);
				gcall.Stepto(-37662,8689,-48);
				gcall.Stepto(-37687,8437,-28);
				gcall.Stepto(-37711,8193,3);
				gcall.Stepto(-37754,7944,35);
				gcall.Stepto(-37834,7713,58);
				gcall.Stepto(-37922,7477,94);
				gcall.Stepto(-38009,7248,122);
				gcall.Stepto(-38098,7011,139);
				gcall.Stepto(-38185,6777,136);
				gcall.Stepto(-38271,6548,121);
				gcall.Stepto(-38295,6485,118);
				gcall.Stepto(-38390,6406,106);
				gcall.Stepto(-38580,6246,79);
				gcall.Stepto(-38771,6086,45);
				gcall.Stepto(-38957,5928,10);
				gcall.Stepto(-39150,5764,-5);
				gcall.NewSpend(1);
				gcall.Stepto(-39337,5606,-24);
				gcall.Stepto(-39530,5442,-49);
				gcall.Stepto(-39716,5285,-75);
				gcall.Stepto(-39947,5185,-95);
				gcall.Stepto(-40187,5146,-113);
				gcall.Stepto(-40339,5154,-117);
				gcall.Stepto(-40538,5170,-124);
				gcall.Stepto(-40782,5182,-134);
				gcall.Stepto(-40807,5183,-135);
				gcall.Stepto(-40884,5187,-138);
				gcall.Stepto(-41133,5199,-150);
				gcall.Stepto(-41377,5210,-149);
				gcall.Stepto(-41625,5222,-144);
				gcall.Stepto(-41868,5250,-149);
				gcall.Stepto(-42103,5315,-163);
				gcall.Stepto(-42323,5374,-183);
				gcall.Stepto(-42546,5435,-233);
				gcall.Stepto(-42547,5435,-233);
				gcall.NewSpend(2.5);
				gcall.Stepto(-42725,5525,-295);
				gcall.Stepto(-42942,5647,-376);
				gcall.Stepto(-43149,5777,-447);
				gcall.Stepto(-43362,5913,-509);
				gcall.Stepto(-43549,6064,-557);
				gcall.Stepto(-43745,6225,-605);
				gcall.Stepto(-43882,6337,-638);
				gcall.Stepto(-43809,6403,-623);
				gcall.Stepto(-43625,6569,-588);
				gcall.Stepto(-43437,6738,-559);
				gcall.Stepto(-43255,6902,-541);
				gcall.Stepto(-43074,7066,-529);
				gcall.Stepto(-43049,7301,-539);
				gcall.Stepto(-43263,7310,-554);
				gcall.Stepto(-43376,7084,-556);
				gcall.Stepto(-43470,6866,-563);
				gcall.Stepto(-43572,6644,-579);
				gcall.Stepto(-43727,6458,-606);
				gcall.Stepto(-43970,6435,-648);
				gcall.Stepto(-44207,6508,-700);
				gcall.Stepto(-44432,6603,-731);
				gcall.Stepto(-44612,6772,-763);
				gcall.Stepto(-44756,6969,-788);
				gcall.Stepto(-44909,7174,-805);
				gcall.Stepto(-45055,7370,-826);
				gcall.Stepto(-45183,7578,-847);
				gcall.Stepto(-45283,7801,-873);
				gcall.Stepto(-45332,8049,-903);
				gcall.Stepto(-45317,8293,-917);
				gcall.Stepto(-45298,8542,-935);
				gcall.Stepto(-45264,8777,-954);
				gcall.Stepto(-45210,9022,-972);
				gcall.Stepto(-45150,9259,-985);
				gcall.Stepto(-45098,9506,-1003);
				gcall.Stepto(-45052,9746,-1020);
				gcall.Stepto(-45005,9986,-1035);
				gcall.Stepto(-44967,10228,-1042);
				gcall.Stepto(-45001,10471,-1053);
				gcall.Stepto(-45110,10690,-1082);
				gcall.Stepto(-45230,10903,-1112);
				gcall.Stepto(-45356,11122,-1133);
				gcall.Stepto(-45478,11334,-1170);
				gcall.Stepto(-45600,11547,-1199);
				gcall.Stepto(-45722,11758,-1228);
				gcall.Stepto(-45848,11978,-1260);
				gcall.Stepto(-45970,12190,-1301);
				gcall.Stepto(-46092,12402,-1333);
				gcall.Stepto(-46223,12617,-1369);
				gcall.Stepto(-46364,12817,-1395);
				gcall.Stepto(-46505,13017,-1442);
				gcall.Stepto(-46645,13217,-1480);
				gcall.Stepto(-46791,13424,-1514);
				gcall.Stepto(-46932,13624,-1542);
				gcall.Stepto(-47072,13824,-1581);
				gcall.Stepto(-47213,14025,-1630);
				gcall.Stepto(-47353,14222,-1681);
				gcall.Stepto(-47494,14423,-1733);
				gcall.Stepto(-47635,14623,-1764);
				gcall.Stepto(-47780,14821,-1789);
				gcall.Stepto(-47996,14926,-1824);
				gcall.Stepto(-48240,14941,-1856);
				gcall.Stepto(-48484,14953,-1891);
				gcall.Stepto(-48737,14965,-1930);
				gcall.Stepto(-48976,15010,-1954);
				gcall.Stepto(-49187,15132,-1974);
				gcall.Stepto(-49400,15269,-2019);
				gcall.Stepto(-49606,15400,-2073);
				gcall.Stepto(-49837,15451,-2116);
				gcall.Stepto(-50078,15413,-2134);
				gcall.Stepto(-50328,15374,-2162);
				gcall.Stepto(-50570,15340,-2192);
				gcall.Stepto(-50822,15311,-2212);
				gcall.Stepto(-51065,15285,-2192);
				gcall.Stepto(-51316,15258,-2140);
				gcall.Stepto(-51559,15232,-2113);
				gcall.Stepto(-51802,15206,-2091);
				gcall.Stepto(-52054,15179,-2091);
				gcall.Stepto(-52297,15148,-2098);
				gcall.Stepto(-52547,15116,-2122);
				gcall.Stepto(-52656,15102,-2143);
				gcall.NewSpend(1);
				gcall.Stepto(-52720,15094,-2154);
				gcall.Stepto(-52963,15065,-2197);
				gcall.Stepto(-53206,15036,-2242);
				gcall.Stepto(-53455,15039,-2255);
				gcall.Stepto(-53705,15089,-2265);
				gcall.Stepto(-53941,15153,-2278);
				gcall.Stepto(-54167,15220,-2296);
				gcall.Stepto(-54390,15319,-2305);
				gcall.Stepto(-54621,15428,-2324);
				gcall.Stepto(-54659,15446,-2331);
				gcall.Stepto(-54855,15538,-2343);
				gcall.Stepto(-55041,15704,-2361);
				gcall.Stepto(-55111,15764,-2377);
				gcall.Stepto(-55235,15867,-2396);
				gcall.Stepto(-55375,15983,-2433);
				gcall.Stepto(-55562,16139,-2485);
				gcall.Stepto(-55629,16196,-2502);
				gcall.Stepto(-55652,16257,-2517);
				gcall.Stepto(-55711,16518,-2539);
				gcall.NewSpend(2.5);
				gcall.Stepto(-55764,16757,-2561);
				gcall.Stepto(-55803,16998,-2575);
				gcall.Stepto(-55753,17245,-2585);
				gcall.Stepto(-55685,17480,-2585);
				gcall.Stepto(-55616,17714,-2581);
				gcall.Stepto(-55546,17957,-2574);
				gcall.Stepto(-55478,18192,-2552);
				gcall.Stepto(-55523,18435,-2518);
				gcall.Stepto(-55617,18654,-2479);
				gcall.Stepto(-55721,18886,-2432);
				gcall.Stepto(-55842,19094,-2404);
				gcall.Stepto(-55984,19304,-2377);
				gcall.Stepto(-56120,19506,-2343);
				gcall.Stepto(-56263,19717,-2329);
				gcall.Stepto(-56415,19913,-2318);
				gcall.Stepto(-56541,20013,-2315);
				//到猪村
				
			}
			yaojiang39();
			Sleep(1000);
			gcall.CityConvey(0x26);
			Sleep(2000);
			gcall.Stepto(42368,45612,4909);
			gcall.Stepto(42361,45599,4902);
			gcall.Stepto(42252,45370,4780);
			gcall.Stepto(42154,45147,4723);
			gcall.Stepto(42156,44904,4700);
			gcall.Stepto(42165,44702,4689);
			Sleep(1000);
			gcall.DeliverQuests(zid,taskid,L"청풍");
			Sleep(1000);
            break;
        case 7:
			gcall.Stepto(42087,44715,4676);
			gcall.Stepto(41842,44679,4644);
			gcall.Stepto(41680,44581,4619);
			gcall.Stepto(41636,44465,4604);
			gcall.Stepto(41530,44242,4572);
			gcall.Stepto(41430,44015,4536);
			gcall.Stepto(41333,43787,4496);
			gcall.Stepto(41246,43555,4456);
			gcall.Stepto(41168,43339,4421);
			gcall.Stepto(41168,43338,4421);
			Sleep(1000);
			gcall.FindThenKill(0,500,modeAoe | modeNormal | modePickup);
			Sleep(1000);
			gcall.FindThenKill(0,500,modeAoe | modeNormal | modePickup);
			gcall.sendcall(id_msg_attack, (LPVOID)0x5DFC);//v
			gcall.Stepto(41164,43177,4400);
			gcall.Stepto(41169,42931,4368);
			gcall.Stepto(41175,42682,4333);
			gcall.Stepto(41184,42436,4304);
			gcall.Stepto(41192,42203,4288);
			gcall.Stepto(41192,42202,4288);
			Sleep(1000);
			gcall.FindThenKill(0,500,modeAoe | modeNormal | modePickup);
			Sleep(1000);
			gcall.FindThenKill(0,500,modeAoe | modeNormal | modePickup);
			gcall.sendcall(id_msg_attack, (LPVOID)0x5DFC);//v
			gcall.Stepto(41213,41969,4281);
			gcall.Stepto(41249,41722,4266);
			gcall.Stepto(41295,41481,4237);
			gcall.Stepto(41367,41242,4190);
			gcall.Stepto(41394,41154,4170);
			Sleep(1000);
			gcall.FindThenKill(0,500,modeAoe | modeNormal | modePickup);
			Sleep(1000);
			gcall.FindThenKill(0,500,modeAoe | modeNormal | modePickup);
			gcall.sendcall(id_msg_attack, (LPVOID)0x5DFC);//v
			gcall.Stepto(41399,41139,4167);
			gcall.Stepto(41454,40897,4121);
			gcall.Stepto(41500,40654,4086);
			gcall.Stepto(41551,40411,4056);
			gcall.Stepto(41601,40189,4028);
			gcall.Stepto(41657,39952,4001);
			gcall.Stepto(41657,39951,4001);
			gcall.sendcall(id_msg_attack, (LPVOID)0x5DE8);//z
			Sleep(1000);
			gcall.FindThenKill(0,500,modeAoe | modeNormal | modePickup);
			Sleep(1000);
			gcall.FindThenKill(0,500,modeAoe | modeNormal | modePickup);
			gcall.sendcall(id_msg_attack, (LPVOID)0x5DFC);//v
			gcall.Stepto(41669,39856,3993);
			gcall.Stepto(41747,39637,3975);
			gcall.Stepto(41833,39403,3960);
			gcall.Stepto(41916,39178,3948);
			gcall.Stepto(41917,39175,3948);
			gcall.Stepto(41923,39164,3948);
			gcall.Stepto(42031,38958,3931);
			gcall.Stepto(42032,38957,3931);
			Sleep(5000);
            break;
        case 8:
			if (gcall.GetPlayerLevel() < 43)
			{
				if (gcall.GetCityID() != 4200)
				{
					gcall.CityConvey(0x3c);
				}
			}
			lianji40_go();
			while (true)
			{
				if (gcall.GetPlayerLevel() < 43)
				{
					if (gcall.GetPlayerLevel() < 41)
					{
						UseExperience();
					}
					lianji40();
				}else
				{
					break;
				}
			}
			gcall.AddTalent(0x142);
			gcall.AddTalent(0x143);
			gcall.AddTalent(0x144);
			if (gcall.isTalentPanelShow())
			{
				gcall.OpenTalentUI();
				Sleep(1000);
			}

			//副本出来后先去修理
			flag_43_go = gcall.Stepto(-72670,-31158,-2893,10,10,3000);
			if (flag_43_go)
			{
				Sleep(1000);
				gcall.Shunyi(L"Lianji40-end-mai");
				Sleep(1000);
				gcall.sendcall(id_msg_OverShunyi,(LPVOID)FALSE);
				Sleep(3000);
				gcall.Stepto(-67468,-34934,-1525);
			}
			gcall.WaitPlans();
			Sleep(1000);
			gcall.Stepto(-67378,-34950,-1519);
			gcall.Stepto(-67152,-35021,-1511);
			gcall.Stepto(-66915,-35094,-1509);
			gcall.Stepto(-66679,-35168,-1503);
			gcall.Stepto(-66533,-35368,-1499);
			gcall.Stepto(-66421,-35589,-1481);
			gcall.Stepto(-66288,-35798,-1464);
			Sleep(1000);
			gcall.FixWuqi();
			Sleep(1000);
			

			//返回任务的地方
			gcall.CityConvey(0x26);
			gcall.NewSpend(2.5);
			gcall.Stepto(42368,45612,4909);
			gcall.Stepto(42298,45530,4846);
			gcall.Stepto(42149,45335,4758);
			gcall.Stepto(41997,45133,4702);
			gcall.Stepto(41850,44938,4669);
			gcall.Stepto(41698,44736,4637);
			gcall.Stepto(41578,44523,4607);
			gcall.Stepto(41462,44307,4576);
			gcall.Stepto(41342,44085,4544);
			gcall.Stepto(41228,43868,4506);
			gcall.Stepto(41135,43633,4464);
			gcall.Stepto(41065,43398,4429);
			gcall.Stepto(41017,43158,4398);
			gcall.Stepto(41017,42905,4365);
			gcall.Stepto(41038,42671,4332);
			gcall.Stepto(41082,42430,4304);
			gcall.Stepto(41127,42192,4288);
			gcall.Stepto(41127,42190,4288);
			gcall.Stepto(41137,42151,4287);
			gcall.Stepto(41189,41962,4281);
			gcall.Stepto(41240,41773,4272);
			gcall.Stepto(41293,41578,4251);
			gcall.Stepto(41344,41389,4221);
			gcall.Stepto(41396,41199,4180);
			gcall.Stepto(41449,41003,4138);
			gcall.Stepto(41500,40815,4107);
			gcall.Stepto(41553,40619,4082);
			gcall.Stepto(41604,40431,4058);
			gcall.Stepto(41655,40242,4031);
			gcall.Stepto(41708,40047,4008);
			gcall.Stepto(41759,39858,3989);
			gcall.Stepto(41812,39662,3974);
			gcall.Stepto(41870,39451,3960);
			gcall.Stepto(41932,39223,3947);
			gcall.Stepto(41966,39099,3942);
			gcall.Stepto(41904,39339,3953);
			gcall.Stepto(41838,39578,3968);
			gcall.Stepto(41740,39806,3986);
			gcall.Stepto(41700,39878,3993);
			Sleep(2000);
			gcall.Stepto(41743,39749,3981);
			gcall.Stepto(41821,39514,3965);
			gcall.Stepto(41883,39274,3951);
			gcall.Stepto(41922,39029,3942);
			gcall.Stepto(41945,38781,3938);
			gcall.Stepto(41898,38543,3935);
			gcall.Stepto(41777,38322,3930);
			gcall.Stepto(41760,38300,3930);
			gcall.sendcall(id_msg_attack, (LPVOID)0x5E06);//3
			Sleep(1500);
			gcall.sendcall(id_msg_attack, (LPVOID)0x5E1A);//E
			Sleep(800);
			gcall.Kill_Tab();
			gcall.sendcall(id_msg_attack, (LPVOID)0x5DE8);//z
			Sleep(800);
			gcall.Kill_Tab();
			gcall.FindThenKill(0,300,modeAoe | modeNormal | modePickup);
			Sleep(1000);
			gcall.DeliverQuests(zid,taskid,L"다원");
			Sleep(1000);
            break;
        case 9:
			gcall.NewSpend(2.5);
			gcall.Stepto(42380,45592,4904);
			gcall.Stepto(42230,45408,4781);
			gcall.Stepto(42075,45214,4727);
			gcall.Stepto(41920,45020,4682);
			gcall.Stepto(41801,44803,4652);
			gcall.Stepto(41687,44583,4620);
			gcall.Stepto(41582,44358,4589);
			gcall.Stepto(41482,44131,4556);
			gcall.Stepto(41382,43904,4517);
			gcall.Stepto(41293,43673,4476);
			gcall.Stepto(41221,43435,4437);
			gcall.Stepto(41164,43194,4402);
			gcall.Stepto(41145,42947,4370);
			gcall.Stepto(41142,42699,4336);
			gcall.Stepto(41140,42451,4306);
			gcall.Stepto(41155,42204,4288);
			gcall.Stepto(41183,41957,4281);
			gcall.Stepto(41210,41711,4265);
			gcall.Stepto(41238,41460,4233);
			gcall.Stepto(41283,41214,4185);
			gcall.Stepto(41340,40972,4133);
			gcall.Stepto(41396,40731,4096);
			gcall.Stepto(41453,40489,4068);
			gcall.Stepto(41523,40250,4037);
			gcall.Stepto(41596,40012,4009);
			gcall.Stepto(41655,39819,3991);
			gcall.Stepto(41728,39582,3973);
			gcall.Stepto(41801,39345,3958);
			gcall.Stepto(41873,39106,3950);
			gcall.Stepto(41936,38867,3941);
			gcall.Stepto(42000,38627,3923);
			gcall.Stepto(42064,38387,3899);
			//死亡后回来的路径

			gcall.Stepto(41804,38264,3917);
			gcall.Stepto(41986,38095,3871);
			gcall.Stepto(42168,37925,3841);
			gcall.Stepto(42342,37746,3826);
			gcall.Stepto(42475,37540,3810);
			gcall.Stepto(42554,37308,3794);
			gcall.Stepto(42562,37069,3778);
			gcall.Stepto(42535,36814,3764);
			gcall.Stepto(42507,36568,3749);
			gcall.Stepto(42472,36325,3736);
			gcall.Stepto(42435,36076,3726);
			gcall.Stepto(42399,35829,3709);
			gcall.Stepto(42362,35585,3692);
			gcall.Stepto(42326,35341,3674);
			gcall.Stepto(42289,35095,3661);
			gcall.Stepto(42253,34850,3637);
			gcall.Stepto(42226,34603,3588);
			gcall.Stepto(42196,34355,3539);
			gcall.Stepto(42128,34118,3499);
			gcall.Stepto(41978,33926,3476);
			gcall.Stepto(41758,33807,3462);
			gcall.Stepto(41535,33701,3452);
			gcall.Stepto(41308,33601,3431);
			gcall.Stepto(41082,33502,3412);
			gcall.Stepto(40855,33403,3413);
			gcall.Stepto(40625,33302,3433);
			gcall.Stepto(40405,33206,3462);
			gcall.Stepto(40174,33100,3495);
			gcall.Stepto(39964,32967,3521);
			gcall.Stepto(39806,32784,3534);
			gcall.Stepto(39709,32557,3545);
			gcall.Stepto(39631,32321,3556);
			gcall.Stepto(39602,32084,3557);
			gcall.Stepto(39634,31828,3556);
			gcall.Stepto(39684,31599,3553);
			gcall.NewSpend(1);
			gcall.Stepto(39684,31595,3553);
			
			gcall.sendcall(id_msg_attack, (LPVOID)0x5E06);//3
			Sleep(1500);
			gcall.Kill_Tab();
			Sleep(800);
			gcall.sendcall(id_msg_attack, (LPVOID)0x5E1A);//E
			Sleep(800);
			gcall.sendcall(id_msg_attack, (LPVOID)0x5DE8);//z
			Sleep(800);
			gcall.Kill_Tab();
			gcall.TurnToNear(500);
			Sleep(500);
			gcall.sendcall(id_msg_attack, (LPVOID)0x5e74);//1
			gcall.FindThenKill(0, 300, modeNormal | modeAoe | modePickup);
            break;
		case 10:
			gcall.Stepto(39634,32021,3557);
			gcall.Stepto(39694,31829,3553);
			gcall.Stepto(39760,31592,3552);
			gcall.Stepto(39761,31560,3550);
			gcall.Stepto(39618,31449,3547);
			gcall.Stepto(39424,31294,3537);
			gcall.Stepto(39315,31202,3535);
			gcall.Stepto(39320,31145,3543);
			Sleep(3000);
			gcall.FindThenKill(0, 300, modeNormal | modeAoe | modePickup);
			gcall.Stepto(39320,31145,3543);
			Sleep(1000);
			gcall.PickupTask();
			Sleep(1000);
			gcall.Stepto(39493,31175,3533);
			gcall.Stepto(39693,31152,3525);
			gcall.Stepto(39688,31117,3522);
			gcall.Stepto(39683,31079,3534);
			gcall.Stepto(39678,31040,3575);
			Sleep(1000);
			gcall.PickupTask();
			Sleep(1000);
			gcall.Stepto(39672,30990,3576);
			gcall.Stepto(39662,30899,3576);
			gcall.Stepto(39625,30653,3576);
			gcall.Stepto(39560,30415,3576);
			gcall.Stepto(39554,30401,3576);
			Sleep(1000);
			gcall.DeliverQuests(zid,0xA,L"구은지");
			Sleep(8000);
			break;
		case 11:
			gcall.NewSpend(1);
			gcall.Stepto(39554,30401,3576);
			gcall.Stepto(39563,30427,3576);
			gcall.Stepto(39634,30663,3576);
			gcall.Stepto(39647,30794,3576);
			gcall.Stepto(39672,31041,3574);
			gcall.Stepto(39691,31290,3536);
			gcall.Stepto(39704,31537,3552);
			gcall.Stepto(39713,31785,3553);
			gcall.Stepto(39722,32031,3554);
			gcall.Stepto(39732,32279,3556);
			gcall.Stepto(39734,32339,3556);
			Sleep(1000);
			gcall.FindThenKill(0, 500, modeNormal | modeAoe | modePickup);
			Sleep(1000);
			gcall.FindThenKill(0, 500, modeNormal | modeAoe | modePickup);

			gcall.Stepto(39736,32170,3556);
			gcall.Stepto(39734,31922,3553);
			gcall.Stepto(39733,31824,3553);
			Sleep(1000);
			gcall.FindThenKill(0, 500, modeNormal | modeAoe | modePickup);

			Sleep(1000);
			gcall.FindThenKill(0, 500, modeNormal | modeAoe | modePickup);


			gcall.Stepto(39744,31927,3553);
			gcall.Stepto(39771,32173,3556);
			gcall.Stepto(39797,32421,3554);
			gcall.Stepto(39824,32668,3538);
			gcall.Stepto(39851,32916,3529);
			gcall.Stepto(39878,33161,3513);
			gcall.Stepto(39904,33408,3489);
			gcall.Stepto(39919,33540,3469);
			gcall.Stepto(39819,33612,3467);
			gcall.Stepto(39622,33770,3451);
			gcall.Stepto(39431,33928,3412);
			gcall.Stepto(39246,34080,3381);
			gcall.Stepto(39244,34082,3380);
			gcall.Stepto(39190,34294,3363);
			gcall.Stepto(39144,34476,3367);
			gcall.Stepto(39030,34442,3354);
			gcall.Stepto(38793,34370,3332);
			gcall.Stepto(38555,34299,3338);
			gcall.Stepto(38354,34263,3360);
			Sleep(3000);
			gcall.Stepto(38464,34304,3348);
			gcall.Stepto(38554,34337,3341);
			gcall.Stepto(38927,34430,3345);
			Sleep(1000);
			gcall.sendcall(id_msg_attack, (LPVOID)0x5DE8);//z
			gcall.FindThenKill(0, 600, modeNormal | modeAoe | modePickup);
			Sleep(1000);
			gcall.FindThenKill(0, 600, modeNormal | modeAoe | modePickup);

			gcall.NewSpend(2.5);
			gcall.Stepto(38423,34191,3345);
			gcall.Stepto(38523,34255,3339);
			gcall.Stepto(38731,34390,3336);
			gcall.Stepto(38858,34473,3352);
			gcall.Stepto(38990,34468,3355);
			gcall.Stepto(39225,34466,3372);
			gcall.Stepto(39237,34451,3374);
			gcall.Stepto(39254,34424,3376);
			gcall.Stepto(39254,34246,3376);
			gcall.Stepto(39253,34000,3393);
			gcall.Stepto(39257,33952,3399);
			gcall.Stepto(39262,33950,3399);
			gcall.Stepto(39462,33896,3417);
			gcall.Stepto(39524,33879,3421);
			gcall.Stepto(39596,33805,3447);
			gcall.Stepto(39763,33623,3469);
			gcall.Stepto(39931,33439,3481);
			gcall.Stepto(40081,33275,3490);
			gcall.Stepto(40069,33240,3494);
			gcall.Stepto(39988,33006,3516);
			gcall.Stepto(39906,32772,3533);
			gcall.Stepto(39825,32537,3546);
			gcall.Stepto(39744,32303,3556);
			gcall.Stepto(39676,32105,3555);
			gcall.NewSpend(1);
			gcall.Stepto(39783,31467,3544);
			Sleep(5000);
			gcall.FindThenKill(0, 450, modeNormal | modeAoe | modePickup);
			break;
		case 12:
			/*
			if (gcall.GetCityID() != 4105)
			{
				gcall.CityConvey(0x25);
			}
			yaojiang42();*/
			if (gcall.GetCityID() != 4419)
			{
				gcall.CityConvey(0x26);
			}
			gcall.NewSpend(2.5);
			gcall.Stepto(42368,45612,4909);
			gcall.Stepto(42234,45431,4785);
			gcall.Stepto(42088,45234,4732);
			gcall.Stepto(41946,45025,4685);
			gcall.Stepto(41828,44811,4655);
			gcall.Stepto(41717,44593,4624);
			gcall.Stepto(41607,44365,4591);
			gcall.Stepto(41501,44143,4559);
			gcall.Stepto(41395,43922,4520);
			gcall.Stepto(41286,43694,4479);
			gcall.Stepto(41180,43474,4441);
			gcall.Stepto(41102,43234,4407);
			gcall.Stepto(41103,42990,4376);
			gcall.Stepto(41125,42747,4342);
			gcall.Stepto(41152,42495,4310);
			gcall.Stepto(41178,42252,4290);
			gcall.Stepto(41203,42017,4283);
			gcall.Stepto(41229,41774,4272);
			gcall.Stepto(41256,41523,4244);
			gcall.Stepto(41282,41288,4202);
			gcall.Stepto(41346,41043,4145);
			gcall.Stepto(41419,40801,4106);
			gcall.Stepto(41478,40607,4080);
			gcall.Stepto(41534,40420,4057);
			gcall.Stepto(41593,40226,4032);
			gcall.Stepto(41650,40037,4009);
			gcall.Stepto(41707,39849,3991);
			gcall.Stepto(41763,39662,3976);
			gcall.Stepto(41820,39474,3963);
			gcall.Stepto(41877,39287,3952);
			gcall.Stepto(41946,39056,3941);
			gcall.Stepto(42017,38822,3930);
			gcall.Stepto(42089,38586,3914);
			gcall.Stepto(42162,38343,3885);
			gcall.Stepto(42233,38107,3858);
			gcall.Stepto(42304,37873,3835);
			gcall.Stepto(42370,37629,3817);
			gcall.Stepto(42402,37385,3799);
			gcall.Stepto(42433,37142,3783);
			gcall.Stepto(42464,36891,3769);
			gcall.Stepto(42480,36647,3754);
			gcall.Stepto(42456,36403,3740);
			gcall.Stepto(42422,36150,3730);
			gcall.Stepto(42389,35908,3715);
			gcall.Stepto(42356,35665,3697);
			gcall.Stepto(42321,35415,3678);
			gcall.Stepto(42288,35172,3665);
			gcall.Stepto(42254,34921,3644);
			gcall.Stepto(42221,34682,3604);
			gcall.Stepto(42187,34432,3554);
			gcall.Stepto(42125,34196,3513);
			gcall.Stepto(41995,33980,3483);
			gcall.Stepto(41808,33824,3464);
			gcall.Stepto(41584,33726,3454);
			gcall.Stepto(41351,33655,3441);
			gcall.Stepto(41099,33631,3427);
			gcall.Stepto(40864,33658,3428);
			gcall.Stepto(40615,33696,3430);
			gcall.Stepto(40372,33680,3434);
			gcall.Stepto(40120,33660,3445);
			gcall.Stepto(39876,33641,3457);
			gcall.Stepto(39740,33630,3468);
			gcall.Stepto(39631,33731,3459);
			gcall.Stepto(39441,33888,3420);
			gcall.Stepto(39242,34044,3386);
			gcall.Stepto(39222,34059,3381);
			gcall.Stepto(39235,34259,3372);
			gcall.Stepto(39250,34486,3378);
			gcall.Stepto(39211,34494,3376);
			gcall.Stepto(38969,34540,3368);
			gcall.Stepto(38886,34555,3370);
			gcall.Stepto(38673,34483,3355);
			gcall.Stepto(38434,34401,3361);
			gcall.Stepto(38197,34349,3392);
			gcall.Stepto(37953,34369,3425);
			gcall.Stepto(37709,34388,3448);
			gcall.Stepto(37465,34404,3454);
			gcall.NewSpend(1);
			gcall.Stepto(37212,34422,3450);
			gcall.Stepto(37204,34423,3450);
			Sleep(1000);
			gcall.DeliverQuests(zid,0xC,L"유태월");
			Sleep(10000);
			gcall.FindThenKill(0,300,modeAoe | modeNormal);
			break;
		case 13:
//			if (gcall.GetCityID() != 4300)
//			{
//				gcall.CityConvey(0x42);
//			}
//			lianji42_go();
//			while (true)
//			{
//				if (gcall.GetPlayerLevel() < 45)
//				{
//					UseExperience();
//					lianji42();
//				}else
//				{
//					break;
//				}
//			}
//			//退出42副本 去修理
//
//			BOOL flag = gcall.Stepto(19901,-52683,-3517,10,10,3000);
//			if (flag)
//			{
//				Sleep(1000);
//				gcall.Shunyi(L"Lianji42-end-mai");
//				Sleep(1000);
//				gcall.sendcall(id_msg_OverShunyi,(LPVOID)FALSE);
//				Sleep(3000);
//				gcall.Stepto(15054,-49018,5411);
//			}
//			gcall.WaitPlans();
//			gcall.Stepto(15016,-49148,5428);
//			gcall.Stepto(14943,-49374,5440);
//			gcall.Stepto(14868,-49610,5474);
//			gcall.Stepto(14890,-49864,5488);
//			Sleep(1000);
//			gcall.FixWuqi();
//			Sleep(1000);
////MessageBox(0, L"摇奖完", L"装八卦", MB_OK);
////这里需要换45级的武器和装备一些首饰之类的,还没想好怎么换。
//			//gcall.NewBag(); 
//			gcall.XieBaoShi(0);//吸血
//			Sleep(1000);
//			gcall.XieBaoShi(1);//白色攻击
//			Sleep(1000);
//			gcall.WearEquipment(L"극마도끼 1단계",WUQI);
//			Sleep(1000);
//			gcall.JiaBaoShi(0,L"빛나는 육각 자수정");//吸血
//			Sleep(1000);
//			gcall.JiaBaoShi(1,L"빛나는 오각 금강석");//攻击
//			Sleep(1000);
//			gcall.WearEquipment(L"나류 해골반지",JIEZHI);
//			Sleep(1000);
//			gcall.WearEquipment(L"나류 해골목걸이",XIANGLIAN);
//			Sleep(1000);
//			gcall.WearEquipment(L"상승무공귀걸이",ERHUAN);
//			Sleep(1000);
//			
			gcall.CityConvey(0x26);
			gcall.NewSpend(2.5);
			gcall.Stepto(42368,45612,4909);
			gcall.Stepto(42234,45431,4785);
			gcall.Stepto(42088,45234,4732);
			gcall.Stepto(41946,45025,4685);
			gcall.Stepto(41828,44811,4655);
			gcall.Stepto(41717,44593,4624);
			gcall.Stepto(41607,44365,4591);
			gcall.Stepto(41501,44143,4559);
			gcall.Stepto(41395,43922,4520);
			gcall.Stepto(41286,43694,4479);
			gcall.Stepto(41180,43474,4441);
			gcall.Stepto(41102,43234,4407);
			gcall.Stepto(41103,42990,4376);
			gcall.Stepto(41125,42747,4342);
			gcall.Stepto(41152,42495,4310);
			gcall.Stepto(41178,42252,4290);
			gcall.Stepto(41203,42017,4283);
			gcall.Stepto(41229,41774,4272);
			gcall.Stepto(41256,41523,4244);
			gcall.Stepto(41282,41288,4202);
			gcall.Stepto(41346,41043,4145);
			gcall.Stepto(41419,40801,4106);
			gcall.Stepto(41478,40607,4080);
			gcall.Stepto(41534,40420,4057);
			gcall.Stepto(41593,40226,4032);
			gcall.Stepto(41650,40037,4009);
			gcall.Stepto(41707,39849,3991);
			gcall.Stepto(41763,39662,3976);
			gcall.Stepto(41820,39474,3963);
			gcall.Stepto(41877,39287,3952);
			gcall.Stepto(41946,39056,3941);
			gcall.Stepto(42017,38822,3930);
			gcall.Stepto(42089,38586,3914);
			gcall.Stepto(42162,38343,3885);
			gcall.Stepto(42233,38107,3858);
			gcall.Stepto(42304,37873,3835);
			gcall.Stepto(42370,37629,3817);
			gcall.Stepto(42402,37385,3799);
			gcall.Stepto(42433,37142,3783);
			gcall.Stepto(42464,36891,3769);
			gcall.Stepto(42480,36647,3754);
			gcall.Stepto(42456,36403,3740);
			gcall.Stepto(42422,36150,3730);
			gcall.Stepto(42389,35908,3715);
			gcall.Stepto(42356,35665,3697);
			gcall.Stepto(42321,35415,3678);
			gcall.Stepto(42288,35172,3665);
			gcall.Stepto(42254,34921,3644);
			gcall.Stepto(42221,34682,3604);
			gcall.Stepto(42187,34432,3554);
			gcall.Stepto(42125,34196,3513);
			gcall.Stepto(41995,33980,3483);
			gcall.Stepto(41808,33824,3464);
			gcall.Stepto(41584,33726,3454);
			gcall.Stepto(41351,33655,3441);
			gcall.Stepto(41099,33631,3427);
			gcall.Stepto(40864,33658,3428);
			gcall.Stepto(40615,33696,3430);
			gcall.Stepto(40372,33680,3434);
			gcall.Stepto(40120,33660,3445);
			gcall.Stepto(39876,33641,3457);
			gcall.Stepto(39740,33630,3468);
			gcall.Stepto(39631,33731,3459);
			gcall.Stepto(39441,33888,3420);
			gcall.Stepto(39242,34044,3386);
			gcall.Stepto(39222,34059,3381);
			gcall.Stepto(39235,34259,3372);
			gcall.Stepto(39250,34486,3378);
			gcall.Stepto(39211,34494,3376);
			gcall.Stepto(38969,34540,3368);
			gcall.Stepto(38886,34555,3370);
			gcall.Stepto(38673,34483,3355);
			gcall.Stepto(38434,34401,3361);
			gcall.Stepto(38197,34349,3392);
			gcall.Stepto(37953,34369,3425);
			gcall.Stepto(37709,34388,3448);
			gcall.Stepto(37465,34404,3454);
			gcall.NewSpend(1);
			gcall.Stepto(37212,34422,3450);
			gcall.Stepto(37204,34423,3450);
			
			Sleep(1000);
			gcall.DeliverQuests(zid,0xD,L"원웅재");
			Sleep(1000);

			break;
		case 14:
			//这里过滤掉，韩服主线已改。
			gcall.NewSpend(2.5);
			gcall.Stepto(37147,34415,3448);
			gcall.Stepto(37384,34417,3455);
			gcall.Stepto(37633,34418,3450);
			gcall.Stepto(37881,34420,3430);
			gcall.Stepto(38129,34422,3402);
			gcall.Stepto(38377,34424,3372);
			gcall.Stepto(38625,34429,3349);
			gcall.Stepto(38872,34450,3348);
			gcall.Stepto(39119,34471,3364);
			gcall.Stepto(39313,34349,3387);
			gcall.Stepto(39282,34114,3380);
			gcall.Stepto(39259,33950,3399);
			gcall.Stepto(39365,33912,3411);
			gcall.Stepto(39597,33801,3448);
			gcall.Stepto(39815,33682,3452);
			gcall.Stepto(40038,33577,3457);
			gcall.Stepto(40285,33583,3447);
			gcall.Stepto(40530,33624,3429);
			gcall.Stepto(40774,33667,3429);
			gcall.Stepto(41017,33716,3440);
			gcall.Stepto(41260,33766,3450);
			gcall.Stepto(41503,33817,3464);
			gcall.Stepto(41739,33891,3480);
			gcall.Stepto(41905,34064,3505);
			gcall.Stepto(41965,34304,3539);
			gcall.Stepto(42026,34545,3581);
			gcall.Stepto(42075,34789,3625);
			gcall.Stepto(42110,35035,3651);
			gcall.Stepto(42139,35281,3662);
			gcall.Stepto(42145,35529,3676);
			gcall.Stepto(42164,35776,3697);
			gcall.Stepto(42190,36023,3718);
			gcall.Stepto(42217,36269,3735);
			gcall.Stepto(42241,36516,3751);
			gcall.Stepto(42264,36763,3763);
			gcall.Stepto(42286,37010,3775);
			gcall.Stepto(42309,37257,3790);
			gcall.Stepto(42332,37504,3807);


			//如果死亡或者掉线或传送，应该是从这里开始跑。
			gcall.Stepto(42593,45792,5060);
			gcall.Stepto(42436,45600,4933);
			gcall.Stepto(42279,45408,4789);
			gcall.Stepto(42126,45213,4733);
			gcall.Stepto(41993,45004,4688);
			gcall.Stepto(41870,44789,4657);
			gcall.Stepto(41757,44568,4625);
			gcall.Stepto(41651,44344,4592);
			gcall.Stepto(41548,44118,4558);
			gcall.Stepto(41450,43890,4518);
			gcall.Stepto(41352,43662,4478);
			gcall.Stepto(41255,43434,4438);
			gcall.Stepto(41159,43206,4404);
			gcall.Stepto(41108,42964,4373);
			gcall.Stepto(41106,42716,4338);
			gcall.Stepto(41134,42470,4308);
			gcall.Stepto(41173,42225,4289);
			gcall.Stepto(41212,41980,4282);
			gcall.Stepto(41251,41735,4268);
			gcall.Stepto(41290,41489,4238);
			gcall.Stepto(41334,41244,4191);
			gcall.Stepto(41396,41001,4138);
			gcall.Stepto(41461,40762,4099);
			gcall.Stepto(41527,40522,4070);
			gcall.Stepto(41591,40285,4039);
			gcall.Stepto(41656,40046,4010);
			gcall.Stepto(41720,39806,3987);
			gcall.Stepto(41784,39548,3969);
			gcall.Stepto(41845,39318,3955);
			gcall.Stepto(41904,39096,3947);
			gcall.Stepto(41981,38864,3934);
			gcall.Stepto(42202,38756,3915);
			gcall.Stepto(42441,38690,3910);
			//这里到交叉口
			gcall.Stepto(42649,38639,3922,10,10,5000);
			gcall.Stepto(42876,38589,3940,10,10,5000);
			gcall.Stepto(43119,38540,3950,10,10,5000);
			gcall.Stepto(43323,38499,3957,10,10,5000);
			gcall.Stepto(43567,38455,3963,10,10,5000);
			gcall.Stepto(43813,38480,3947);
			gcall.Stepto(44055,38533,3922);
			gcall.Stepto(44297,38592,3932);
			gcall.Stepto(44532,38650,3951);
			gcall.Stepto(44772,38714,3971);
			gcall.Stepto(45011,38778,3995);
			gcall.Stepto(45250,38845,4016);
			gcall.Stepto(45489,38912,4039);
			gcall.Stepto(45721,38997,4061);
			gcall.Stepto(45940,39114,4083);
			gcall.Stepto(46156,39236,4105);
			gcall.Stepto(46370,39362,4130);
			gcall.Stepto(46583,39487,4153);
			gcall.Stepto(46798,39612,4181);
			gcall.Stepto(47013,39735,4199);
			gcall.Stepto(47232,39851,4216);
			gcall.Stepto(47451,39967,4231);
			gcall.Stepto(47667,40089,4240);
			gcall.Stepto(47883,40212,4248);
			gcall.Stepto(48103,40326,4260);
			gcall.Stepto(48326,40436,4265);
			gcall.Stepto(48548,40546,4269);
			gcall.Stepto(48770,40655,4270);
			gcall.Stepto(49003,40726,4271);
			gcall.Stepto(49251,40719,4269);
			gcall.Stepto(49499,40714,4261);
			gcall.Stepto(49747,40709,4257);
			gcall.Stepto(49995,40704,4253);
			gcall.NewSpend(1);
			gcall.Stepto(50243,40699,4232);
			Sleep(2000);
			gcall.FindThenKill(0,500,modeAoe | modeNormal | modePickup);

			gcall.Stepto(50045,40663,4244);
			gcall.Stepto(49800,40627,4252);
			gcall.Stepto(49671,40785,4260);
			gcall.Stepto(49653,41032,4278);
			gcall.Stepto(49645,41143,4275);
			Sleep(1000);
			gcall.DeliverQuests(zid,0xE,L"원서진");
			Sleep(1000);
			break;
    }
}

void TaskScript::Task_902(int zid, int taskid)
{
    switch(taskid)
    {
        case 1:
			gcall.NewSpend(2.5);
			gcall.Stepto(42237,45441,4786);
			gcall.Stepto(42209,45406,4778);
			gcall.Stepto(42058,45209,4724);
			gcall.Stepto(41913,45011,4681);
			gcall.Stepto(41787,44798,4651);
			gcall.Stepto(41664,44582,4619);
			gcall.Stepto(41553,44379,4589);
			gcall.Stepto(41429,44146,4555);
			gcall.Stepto(41334,43912,4517);
			gcall.Stepto(41254,43678,4476);
			gcall.Stepto(41180,43443,4436);
			gcall.Stepto(41118,43201,4403);
			gcall.Stepto(41089,42956,4372);
			gcall.Stepto(41090,42710,4337);
			gcall.Stepto(41127,42462,4307);
			gcall.Stepto(41170,42219,4289);
			gcall.Stepto(41214,41974,4282);
			gcall.Stepto(41258,41726,4267);
			gcall.Stepto(41301,41485,4237);
			gcall.Stepto(41343,41248,4192);
			gcall.Stepto(41389,40995,4137);
			gcall.Stepto(41435,40755,4098);
			gcall.Stepto(41483,40563,4075);
			gcall.Stepto(41532,40370,4052);
			gcall.Stepto(41582,40181,4028);
			gcall.Stepto(41634,39989,4005);
			gcall.Stepto(41690,39797,3988);
			gcall.Stepto(41749,39607,3973);
			gcall.Stepto(41817,39420,3961);
			gcall.Stepto(41891,39248,3950);
			gcall.Stepto(42032,39047,3936);
			gcall.Stepto(42216,38896,3923);
			gcall.Stepto(42456,38812,3919);
			gcall.Stepto(42699,38755,3935);
			gcall.Stepto(42943,38728,3942);
			gcall.Stepto(43194,38731,3944);
			gcall.Stepto(43442,38735,3952);
			gcall.Stepto(43692,38738,3952);
			gcall.Stepto(43938,38741,3943);
			gcall.Stepto(44188,38744,3937);
			gcall.Stepto(44436,38748,3950);
			gcall.Stepto(44688,38751,3967);
			gcall.Stepto(44933,38759,3987);
			gcall.Stepto(45179,38791,4008);
			gcall.Stepto(45419,38855,4032);
			gcall.Stepto(45656,38926,4053);
			gcall.Stepto(45878,39007,4074);
			gcall.Stepto(46103,39108,4096);
			gcall.Stepto(46315,39237,4116);
			gcall.Stepto(46515,39369,4140);
			gcall.Stepto(46730,39510,4166);
			gcall.Stepto(46941,39648,4188);
			gcall.Stepto(47148,39786,4208);
			gcall.Stepto(47352,39927,4226);
			gcall.Stepto(47554,40071,4238);
			gcall.Stepto(47755,40215,4245);
			gcall.Stepto(47962,40351,4254);
			gcall.Stepto(48183,40464,4263);
			gcall.Stepto(48405,40575,4268);
			gcall.Stepto(48626,40686,4270);
			gcall.Stepto(48848,40798,4270);
			gcall.Stepto(49079,40894,4270);
			gcall.Stepto(49087,40896,4270);
			gcall.NewSpend(1);
			gcall.Stepto(49359,40671,4265);
			gcall.Stepto(49145,40553,4271);
			gcall.Stepto(48932,40435,4271);
			gcall.Stepto(48704,40324,4268);
			gcall.Stepto(48492,40191,4264);
			gcall.Stepto(48455,40167,4262);
			//过滤怪物(영린촌 주민,1);
			gcall.AddCustomKill(L"영린촌 주민",DONTKILL);
			gcall.FindThenKill(0,600,modeAoe | modeNormal);
			Sleep(1000);
			gcall.FindThenKill(0,600,modeAoe | modeNormal);
			gcall.Stepto(48378,39996,4258);
			gcall.Stepto(L"영린촌 주민");
			Sleep(1000);
			gcall.PickupSpecTypeTask(200,0x4,L"영린촌 주민");
			Sleep(1000);

			gcall.NewSpend(2.5);
			gcall.Stepto(47733,40150,4242);
			gcall.Stepto(47563,40117,4240);
			gcall.Stepto(47507,40105,4238);
			gcall.Stepto(47265,40047,4232);
			gcall.Stepto(47023,39990,4227);
			gcall.Stepto(46783,39931,4214);
			gcall.NewSpend(1);
			gcall.Stepto(46609,39888,4201);
			
			gcall.FindThenKill(0,600,modeAoe | modeNormal);
			Sleep(1000);
			gcall.FindThenKill(0,600,modeAoe | modeNormal);
			gcall.Stepto(46659,39974,4215);
			gcall.Stepto(L"영린촌 주민");
			Sleep(1000);
			gcall.PickupSpecTypeTask(200,0x4,L"영린촌 주민");
			Sleep(1000);

			gcall.NewSpend(2.5);
			gcall.Stepto(46408,39767,4172);
			gcall.Stepto(46381,39715,4164);
			gcall.Stepto(46269,39496,4135);
			gcall.Stepto(46143,39283,4108);
			gcall.Stepto(46005,39074,4087);
			gcall.NewSpend(1);
			gcall.Stepto(45952,38995,4080);
			
			gcall.FindThenKill(0,600,modeAoe | modeNormal);
			Sleep(1000);
			gcall.FindThenKill(0,600,modeAoe | modeNormal);
			gcall.Stepto(46054,38913,4088);
			gcall.Stepto(L"영린촌 주민");
			Sleep(1000);
			gcall.PickupSpecTypeTask(200,0x4,L"영린촌 주민");
			Sleep(1000);

			gcall.NewSpend(2.5);
			gcall.Stepto(45887,38895,4073);
			gcall.Stepto(45963,38964,4080);
			gcall.Stepto(46110,39098,4096);
			gcall.Stepto(46257,39232,4112);
			gcall.Stepto(46403,39365,4132);
			gcall.Stepto(46550,39499,4152);
			gcall.Stepto(46704,39639,4177);
			gcall.Stepto(46898,39790,4202);
			gcall.Stepto(47130,39877,4216);
			gcall.Stepto(47363,39962,4229);
			gcall.Stepto(47597,40046,4238);
			gcall.Stepto(47831,40130,4244);
			gcall.Stepto(48064,40214,4256);
			gcall.Stepto(48297,40303,4263);
			gcall.Stepto(48520,40408,4267);
			gcall.Stepto(48733,40535,4270);
			gcall.Stepto(48935,40679,4271);
			gcall.Stepto(49111,40853,4271);
			gcall.NewSpend(1);
			gcall.Stepto(49219,40998,4271);
			gcall.ClearCustom();
            break;
        case 2:
			gcall.NewSpend(2.5);
			gcall.Stepto(48239,40063,4256,30,10,3000);
			gcall.Stepto(48233,40065,4256,20,10,3000);
			gcall.Stepto(48040,40020,4249,10,10,3000);
			gcall.Stepto(47863,39929,4240);
			gcall.Stepto(47687,39839,4234);
			gcall.Stepto(47508,39752,4225);
			gcall.Stepto(47322,39685,4209);
			gcall.Stepto(47095,39601,4191);
			gcall.Stepto(46871,39503,4173);
			gcall.Stepto(46650,39387,4151);
			gcall.Stepto(46431,39272,4127);
			gcall.Stepto(46212,39156,4106);
			gcall.Stepto(45993,39041,4085);
			gcall.Stepto(45769,38942,4063);
			gcall.Stepto(45531,38852,4042);
			gcall.Stepto(45296,38776,4018);
			gcall.Stepto(45060,38699,3995);
			gcall.Stepto(44826,38624,3973);
			gcall.Stepto(44590,38545,3950);
			gcall.Stepto(44358,38459,3930);
			gcall.Stepto(44117,38392,3916);
			gcall.Stepto(43876,38425,3935);
			gcall.Stepto(43632,38483,3959);
			gcall.Stepto(43390,38541,3958);
			gcall.Stepto(43152,38597,3948);
			gcall.Stepto(42909,38655,3941);
			gcall.Stepto(42670,38712,3930);
			gcall.Stepto(42426,38770,3916);
			gcall.Stepto(42186,38832,3921);
			gcall.Stepto(41970,38947,3937);
			gcall.Stepto(41872,39173,3950);
			gcall.Stepto(41810,39409,3961);
			gcall.Stepto(41748,39652,3976);
			gcall.Stepto(41689,39882,3994);
			gcall.Stepto(41625,40130,4021);
			gcall.Stepto(41563,40373,4052);
			gcall.Stepto(41498,40609,4080);
			gcall.Stepto(41430,40848,4113);
			gcall.Stepto(41362,41087,4155);
			gcall.Stepto(41293,41326,4209);
			gcall.Stepto(41236,41529,4244);
			gcall.Stepto(41198,41723,4266);
			gcall.Stepto(41177,41921,4279);
			gcall.Stepto(41156,42118,4286);
			gcall.Stepto(41136,42317,4292);
			gcall.Stepto(41116,42512,4312);
			gcall.Stepto(41097,42711,4337);
			gcall.Stepto(41091,42910,4365);
			gcall.Stepto(41105,43143,4396);
			gcall.Stepto(41126,43390,4428);
			gcall.Stepto(41196,43627,4465);
			gcall.Stepto(41301,43852,4506);
			gcall.Stepto(41421,44070,4545);
			gcall.Stepto(41544,44288,4578);
			gcall.Stepto(41667,44506,4610);
			gcall.Stepto(41789,44722,4643);
			gcall.Stepto(41912,44938,4674);
			gcall.Stepto(42034,45154,4710);
			gcall.Stepto(42161,45366,4763);
			gcall.NewSpend(1);
			gcall.Stepto(42312,45563,4865);
			gcall.Stepto(42477,45748,5013);
			gcall.Stepto(42669,45915,5143);
			gcall.Stepto(42858,46076,5291);
			gcall.Stepto(42892,46104,5291);
			gcall.Stepto(42898,46109,5291);
			gcall.Stepto(43087,46269,5304);
			Sleep(2000);
			gcall.Stepto(43106,46285,5304);
			gcall.Stepto(43319,46463,5310);
			gcall.WaitPlans();
			gcall.Stepto(43387,46511,5310);
			gcall.NewSpend(2.5);
			gcall.Stepto(43591,46589,5310);
			gcall.Stepto(43826,46669,5310);
			gcall.Stepto(44062,46747,5310);
			gcall.Stepto(44298,46821,5310);
			gcall.Stepto(44535,46895,5311);
			gcall.Stepto(44772,46969,5311);
			gcall.Stepto(45010,47039,5311);
			gcall.Stepto(45249,47106,5311);
			gcall.Stepto(45488,47170,5303);
			gcall.Stepto(45728,47235,5295);
			gcall.Stepto(45968,47300,5288);
			gcall.Stepto(46207,47366,5284);
			gcall.Stepto(46446,47432,5285);
			gcall.Stepto(46687,47499,5292);
			gcall.Stepto(46927,47565,5295);
			gcall.NewSpend(1);
			gcall.Stepto(46993,47583,5294);
			
			Sleep(1000);
			gcall.DeliverQuests(zid,taskid,L"원웅재");
			Sleep(12000);
            break;
        case 3:
			gcall.Stepto(46909,47540,5296);
			gcall.Stepto(46677,47449,5292);
			gcall.Stepto(46441,47377,5284);
			gcall.Stepto(46203,47318,5284);
			gcall.Stepto(45987,47257,5288);
			gcall.AddCustomKill(L"영린촌 주민",DONTKILL);
			gcall.sendcall(id_msg_attack, (LPVOID)0x5E06);//3
			Sleep(1500);
			gcall.sendcall(id_msg_attack, (LPVOID)0x5E1A);//E
			Sleep(800);
			gcall.sendcall(id_msg_attack, (LPVOID)0x5DE8);//z
			Sleep(800);
			gcall.Kill_Tab();
			Sleep(500);
			gcall.FindThenKill(0,600,modeAoe | modeNormal,3);
			Sleep(1000);
            break;
        case 4:
			gcall.ClearCustom();
			gcall.Stepto(46141,47308,5284);
			gcall.Stepto(46374,47391,5283);
			gcall.Stepto(46609,47471,5289);
			gcall.Stepto(46845,47547,5297);
			gcall.Stepto(46942,47578,5295);
			Sleep(1000);
			gcall.DeliverQuests(zid,taskid,L"원웅재");
			Sleep(15000);
            break;
        case 5:
			gcall.Stepto(46954,47579,5295);
			gcall.Stepto(47039,47585,5294);
			gcall.Stepto(47256,47606,5294);
			gcall.Stepto(47500,47643,5285);
			gcall.Stepto(47677,47666,5281);
			Sleep(1000);
			gcall.PickupTask();
			Sleep(80000);
			gcall.Stepto(47256,47606,5294);
			gcall.Stepto(47500,47643,5285);
			gcall.Stepto(47677,47666,5281);
			Sleep(1000);
			gcall.PickupTask();
			Sleep(6000);
            break;
        case 6:
			gcall.WaitPlans();
			gcall.KeyPress(27);
			Sleep(1000);
			gcall.KeyPress(27);
			Sleep(1000);
			gcall.DeliverQuests(zid,taskid,L"유태월");
			Sleep(1000);
            break;
        case 7:
			gcall.WaitPlans();
			gcall.KeyPress(27);
			Sleep(1000);
			gcall.KeyPress(27);
			Sleep(1000);
			gcall.NewSpend(2.5);
			gcall.Stepto(39628,30630,3576);
			gcall.Stepto(39629,30677,3576);
			gcall.Stepto(39635,30730,3576);
			gcall.Stepto(39667,30956,3576);
			gcall.Stepto(39670,30975,3576);
			gcall.Stepto(39707,31215,3530);
			gcall.Stepto(39742,31445,3544);
			gcall.Stepto(39779,31689,3553);
			gcall.Stepto(39812,31937,3553);
			gcall.Stepto(39843,32184,3556);
			gcall.Stepto(39869,32432,3554);
			gcall.Stepto(39888,32678,3538);
			gcall.Stepto(39907,32926,3526);
			gcall.Stepto(39926,33172,3509);
			gcall.Stepto(39945,33421,3481);
			gcall.Stepto(39947,33488,3471);
			gcall.Stepto(39744,33617,3471);
			gcall.Stepto(39650,33678,3468);
			gcall.Stepto(39539,33783,3457);
			gcall.Stepto(39362,33950,3406);
			gcall.Stepto(39272,34036,3391);
			gcall.Stepto(39267,34163,3373);
			gcall.Stepto(39264,34411,3378);
			gcall.Stepto(39264,34443,3379);
			gcall.Stepto(39133,34464,3365);
			gcall.Stepto(38889,34509,3360);
			gcall.Stepto(38837,34496,3357);
			gcall.Stepto(38655,34334,3330);
			gcall.Stepto(38539,34230,3336);
			gcall.Stepto(38404,34245,3351);
			gcall.Stepto(38157,34273,3393);
			gcall.Stepto(37913,34316,3434);
			gcall.Stepto(37667,34362,3454);
			gcall.Stepto(37424,34412,3454);
			gcall.Stepto(37182,34468,3449);
			gcall.Stepto(36941,34527,3442);
			gcall.Stepto(36702,34593,3422);
			gcall.Stepto(36466,34668,3402);
			gcall.Stepto(36230,34745,3393);
			gcall.Stepto(35993,34821,3389);
			gcall.Stepto(35758,34897,3410);
			gcall.Stepto(35531,34970,3444);
			gcall.Stepto(35342,35030,3486);
			gcall.Stepto(35148,35077,3545);
			gcall.Stepto(34957,35119,3617);
			gcall.Stepto(34774,35145,3699);
			gcall.Stepto(34563,35158,3797);
			gcall.Stepto(34290,35165,3928);
			gcall.Stepto(34039,35168,4039);
			gcall.Stepto(33791,35175,4137);
			gcall.Stepto(33543,35210,4211);
			gcall.Stepto(33311,35294,4265);
			gcall.Stepto(33110,35431,4295);
			gcall.NewSpend(1);
			gcall.Stepto(33050,35674,4311);
			gcall.Stepto(33051,35922,4317);
			gcall.Stepto(33066,36169,4326);
			gcall.Stepto(33080,36417,4330);
			gcall.Stepto(33084,36666,4327);
			gcall.Stepto(33084,36722,4327);
			Sleep(5000);
			gcall.Stepto(33084,36858,4327);
			gcall.Stepto(33085,36887,4327);
			gcall.WaitPlans();
			gcall.Stepto(33089,36995,4327);
			//进洞
			gcall.Stepto(33089,36996,4327);
			gcall.Stepto(33063,37230,4328);
			gcall.Stepto(33229,37428,4328);
			gcall.Stepto(33483,37464,4326);
			gcall.Stepto(33731,37482,4328);
			gcall.Stepto(33978,37501,4327);
			gcall.Stepto(34225,37519,4327);
			gcall.Stepto(34473,37522,4307);
			gcall.Stepto(34721,37522,4278);
			gcall.Stepto(34969,37523,4203);
			gcall.Stepto(35194,37587,4192);
			gcall.Stepto(35365,37718,4225);
			gcall.Stepto(35470,37935,4290);
			gcall.Stepto(35522,38175,4357);
			gcall.Stepto(35535,38423,4425);
			gcall.Stepto(35547,38670,4508);
			gcall.Stepto(35557,38918,4608);
			gcall.Stepto(35549,39166,4703);
			gcall.Stepto(35536,39394,4711);
			Sleep(5000);
			gcall.FindThenKill(0,450,modeAoe | modeNormal);
			Sleep(2000);
			gcall.FindThenKill(0,450,modeAoe | modeNormal);
			gcall.Stepto(35488,39619,4713);
			gcall.Stepto(35419,39857,4682);
			gcall.Stepto(35342,40093,4646);
			gcall.Stepto(35261,40327,4611);
			//第1只怪不可采集
			Sleep(3000);
			gcall.FindThenKill(0,450,modeAoe | modeNormal);
			
			//gcall.PickupSpecTypeTask(200,0x4,L"동굴석괴");
			//Sleep(1000);
			//gcall.FindThenKill(0,450,modeAoe | modeNormal);
			//Sleep(1000);



			//能采集的怪物是固定的。
			/*
			打怪超时以后，对话。打怪。
			打怪超时以后，对话，等待，跑过去采集。
			
			*/
			gcall.Stepto(35178,40518,4571);
			gcall.Stepto(35019,40708,4545);
			gcall.Stepto(34860,40899,4547);
			gcall.Stepto(34705,41093,4549);
			Sleep(1000);
			gcall.FindThenKill(0,450,modeAoe | modeNormal);
			Sleep(1000);
			gcall.PickupSpecTypeTask(300,0x4,L"동굴석괴");
			Sleep(20000);
			gcall.Stepto(34917,41133,4551);
			gcall.Stepto(35158,41073,4552);
			gcall.Stepto(35395,41012,4555);
			gcall.Stepto(35423,41005,4555);
			Sleep(2000);
			gcall.PickupTask();
			Sleep(2000);



			//不可采
			gcall.Stepto(35200,41084,4553);
			gcall.Stepto(34966,41167,4552);
			gcall.Stepto(34769,41321,4532);
			gcall.Stepto(34662,41544,4525);
			gcall.Stepto(34574,41727,4544);
			gcall.Stepto(34477,41932,4554);
			gcall.Stepto(34460,42170,4561);
			gcall.Stepto(34442,42417,4552);
			gcall.Stepto(34452,42664,4550);
			Sleep(3000);
			gcall.FindThenKill(0,450,modeAoe | modeNormal);


			//可采
			gcall.Stepto(34520,42896,4555);
			gcall.Stepto(34607,43128,4553);
			gcall.Stepto(34755,43309,4551);
			gcall.Stepto(34973,43425,4551);
			Sleep(1000);
			gcall.FindThenKill(0,450,modeAoe | modeNormal);
			Sleep(1000);
			gcall.PickupSpecTypeTask(300,0x4,L"동굴석괴");
			Sleep(20000);
			gcall.Stepto(34742,43351,4549);
			gcall.Stepto(34514,43255,4548);
			gcall.Stepto(34396,43194,4561);
			Sleep(2000);
			gcall.PickupTask();
			Sleep(2000);


			//不可采
			gcall.Stepto(34736,43315,4550);
			gcall.Stepto(34970,43398,4553);
			gcall.Stepto(35204,43481,4548);
			gcall.Stepto(35442,43544,4549);
			gcall.Stepto(35690,43548,4540);
			gcall.Stepto(35938,43552,4545);
			gcall.Stepto(36186,43557,4529);
			Sleep(3000);
			gcall.FindThenKill(0,450,modeAoe | modeNormal);


			//可采
			gcall.Stepto(36413,43542,4516);
			gcall.Stepto(36660,43523,4502);
			gcall.Stepto(36908,43519,4478);
			gcall.Stepto(37156,43523,4473);
			Sleep(2000);
			gcall.FindThenKill(0,450,modeAoe | modeNormal);
			Sleep(1000);
			gcall.PickupSpecTypeTask(300,0x4,L"동굴석괴");
			Sleep(20000);
			gcall.Stepto(37058,43344,4474);
			gcall.Stepto(36884,43189,4498);
			gcall.Stepto(36695,43040,4529);
			gcall.Stepto(36636,42995,4534);
			Sleep(2000);
			gcall.PickupTask();
			Sleep(2000);


			//出洞
			gcall.NewSpend(2.5);
			gcall.Stepto(36489,43182,4522);
			gcall.Stepto(36336,43377,4529);
			gcall.Stepto(36182,43571,4529);
			gcall.Stepto(35959,43661,4528);
			gcall.Stepto(35751,43574,4536);
			gcall.Stepto(35518,43489,4547);
			gcall.Stepto(35285,43405,4552);
			gcall.Stepto(35051,43322,4557);
			gcall.Stepto(34818,43239,4554);
			gcall.Stepto(34630,43085,4556);
			gcall.Stepto(34548,42852,4556);
			gcall.Stepto(34514,42606,4553);
			gcall.Stepto(34502,42359,4555);
			gcall.Stepto(34539,42113,4559);
			gcall.Stepto(34586,41869,4562);
			gcall.Stepto(34656,41632,4529);
			gcall.Stepto(34746,41400,4524);
			gcall.Stepto(34850,41175,4551);
			gcall.Stepto(34955,40950,4549);
			gcall.Stepto(35052,40733,4545);
			gcall.Stepto(35151,40506,4569);
			gcall.Stepto(35251,40278,4619);
			gcall.Stepto(35350,40051,4652);
			gcall.Stepto(35449,39823,4687);
			gcall.Stepto(35517,39585,4718);
			gcall.Stepto(35579,39345,4708);
			gcall.Stepto(35598,39098,4690);
			gcall.Stepto(35591,38850,4584);
			gcall.Stepto(35583,38602,4480);
			gcall.Stepto(35575,38352,4410);
			gcall.Stepto(35554,38103,4338);
			gcall.NewSpend(1);
			gcall.Stepto(35465,37871,4272);
			gcall.Stepto(35306,37682,4216);
			gcall.Stepto(35116,37525,4182);
			gcall.Stepto(34873,37485,4231);
			gcall.Stepto(34625,37480,4300);
			gcall.Stepto(34377,37475,4318);
			gcall.Stepto(34129,37470,4327);
			gcall.Stepto(33882,37465,4327);
			gcall.Stepto(33634,37460,4326);
			gcall.Stepto(33386,37455,4326);
			gcall.Stepto(33157,37364,4328);
			gcall.Stepto(33019,37208,4329);
			gcall.Stepto(33077,36925,4327);
			Sleep(2000);

			gcall.Stepto(33068,36727,4327);
			gcall.WaitPlans();

            break;
        case 8:
			gcall.NewSpend(2.5);
			gcall.Stepto(33072,36816,4327);
			gcall.Stepto(33066,36579,4323);
			gcall.Stepto(33059,36331,4329);
			gcall.Stepto(33078,36084,4323);
			gcall.Stepto(33134,35843,4315);
			gcall.Stepto(33232,35615,4309);
			gcall.Stepto(33378,35416,4271);
			gcall.Stepto(33578,35271,4211);
			gcall.Stepto(33801,35163,4132);
			gcall.Stepto(34046,35132,4032);
			gcall.Stepto(34294,35118,3925);
			gcall.Stepto(34541,35102,3805);
			gcall.Stepto(34789,35087,3691);
			gcall.Stepto(35036,35072,3582);
			gcall.Stepto(35284,35056,3507);
			gcall.Stepto(35526,35003,3448);
			gcall.Stepto(35766,34941,3415);
			gcall.Stepto(36006,34880,3393);
			gcall.Stepto(36240,34814,3396);
			gcall.Stepto(36476,34737,3407);
			gcall.Stepto(36711,34658,3419);
			gcall.Stepto(36946,34579,3440);
			gcall.Stepto(37182,34500,3448);
			gcall.Stepto(37417,34421,3454);
			gcall.Stepto(37658,34367,3455);
			gcall.Stepto(37907,34377,3430);
			gcall.Stepto(38164,34398,3399);
			gcall.Stepto(38411,34417,3366);
			gcall.Stepto(38658,34437,3347);
			gcall.Stepto(38906,34457,3350);
			gcall.Stepto(39153,34477,3368);
			gcall.Stepto(39312,34317,3387);
			gcall.Stepto(39273,34077,3385);
			gcall.Stepto(39410,33886,3421);
			gcall.Stepto(39601,33793,3449);
			gcall.Stepto(39823,33684,3451);
			gcall.Stepto(39886,33456,3486);
			gcall.NewSpend(1);
			gcall.Stepto(39885,33216,3507);
			gcall.Stepto(39884,32968,3525);
			gcall.Stepto(39883,32720,3536);
			gcall.Stepto(39880,32473,3551);
			gcall.Stepto(39847,32227,3557);
			gcall.Stepto(39822,32013,3553);
			gcall.Stepto(39790,31768,3553);
			gcall.Stepto(39756,31522,3548);
			gcall.Stepto(39720,31265,3534);
			gcall.Stepto(39681,31021,3576);
			gcall.Stepto(39676,30984,3576);
			Sleep(2000);
			gcall.Stepto(39657,30833,3576);
			gcall.WaitPlans();
			gcall.Stepto(39654,30783,3576);
			gcall.Stepto(39638,30535,3576);
			Sleep(1000);
			gcall.DeliverQuests(zid,taskid,L"일심");
			Sleep(1000);
            break;
        case 9:
			gcall.NewSpend(2.5);
			gcall.Stepto(39623,30616,3576);
			gcall.Stepto(39625,30624,3576);
			gcall.Stepto(39656,30870,3576);
			gcall.Stepto(39666,30960,3576);
			gcall.Stepto(39684,31112,3522);
			gcall.Stepto(39737,31368,3539);
			gcall.Stepto(39792,31615,3551);
			gcall.Stepto(39939,31770,3552);
			gcall.Stepto(40168,31865,3554);
			gcall.Stepto(40369,32012,3532);
			gcall.Stepto(40565,32166,3454);
			gcall.Stepto(40761,32316,3348);
			gcall.Stepto(40998,32358,3324);
			gcall.Stepto(41199,32220,3315);
			gcall.Stepto(41361,32034,3312);
			gcall.Stepto(41487,31829,3309);
			gcall.Stepto(41595,31597,3294);
			gcall.Stepto(41690,31367,3283);
			gcall.Stepto(41819,31158,3266);
			gcall.Stepto(42040,31049,3264);
			gcall.Stepto(42282,30998,3259);
			gcall.Stepto(42518,30953,3253);
			gcall.Stepto(42771,30909,3250);
			gcall.Stepto(43016,30882,3239);
			gcall.Stepto(43235,30859,3227);
			gcall.Stepto(43431,30821,3215);
			gcall.Stepto(43597,30730,3196);
			gcall.Stepto(43715,30565,3175);
			gcall.Stepto(43775,30378,3160);
			gcall.Stepto(43807,30177,3148);
			gcall.Stepto(43818,29980,3140);
			gcall.Stepto(43822,29782,3139);
			gcall.Stepto(43824,29581,3181);
			gcall.Stepto(43825,29343,3181);
			gcall.Stepto(43822,29093,3181);
			gcall.Stepto(43818,28849,3089);
			gcall.Stepto(43815,28626,3010);
			gcall.Stepto(43831,28429,3004);
			gcall.Stepto(43852,28261,2991);
			gcall.NewSpend(1);
			gcall.Stepto(43857,28175,2987);
			gcall.Stepto(43841,27927,2985);
			gcall.Stepto(43833,27732,2985);
			Sleep(2000);
			gcall.FindThenKill(0,600,modeAoe | modeNormal | modePickup);
			gcall.sendcall(id_msg_attack, (LPVOID)0x5DFC);//v
			gcall.Stepto(43845,27743,2985);
			gcall.Stepto(43869,27736,2985);
			gcall.Stepto(44059,27677,2985);
			gcall.Stepto(44256,27646,2985);
			gcall.Stepto(44447,27692,2985);
			gcall.Stepto(44625,27777,2985);
			gcall.Stepto(44808,27858,2985);
			gcall.Stepto(44992,27925,2985);
			gcall.Stepto(45224,28001,2986);
			gcall.Stepto(45463,28052,2985);
			gcall.Stepto(45469,28052,2985);
			Sleep(2000);
			gcall.FindThenKill(0,600,modeAoe | modeNormal | modePickup);
			gcall.sendcall(id_msg_attack, (LPVOID)0x5DFC);//v
			gcall.Stepto(45292,28031,2987);
			gcall.Stepto(45195,28019,2986);
			gcall.Stepto(45166,27828,2985);
			gcall.Stepto(45144,27580,2985);
			gcall.Stepto(45154,27338,2985);
			gcall.Stepto(45155,27326,2985);
			Sleep(2000);
			gcall.FindThenKill(0,600,modeAoe | modeNormal | modePickup);
			gcall.sendcall(id_msg_attack, (LPVOID)0x5DFC);//v
			gcall.Stepto(45159,27166,2985);
			gcall.Stepto(45162,26995,2985);
			gcall.Stepto(45142,26906,2985);
			gcall.Stepto(45070,26668,2985);
			gcall.Stepto(44976,26441,2984);
			gcall.Stepto(44813,26262,2982);
			gcall.Stepto(44664,26262,2979);
			gcall.Stepto(44661,26263,2979);
			Sleep(2000);
			gcall.FindThenKill(0,600,modeAoe | modeNormal | modePickup);
			gcall.sendcall(id_msg_attack, (LPVOID)0x5DFC);//v
			gcall.Stepto(44607,26253,2978);
			gcall.Stepto(44415,26209,2975);
			gcall.Stepto(44220,26164,2973);
			gcall.Stepto(44029,26119,2973);
			gcall.Stepto(43832,26130,2973);
			gcall.Stepto(43643,26188,2974);
			gcall.Stepto(43408,26259,2977);
			gcall.Stepto(43195,26293,2979);
			gcall.Stepto(43067,26282,2982);
			Sleep(2000);
			gcall.FindThenKill(0,600,modeAoe | modeNormal | modePickup);
			gcall.sendcall(id_msg_attack, (LPVOID)0x5DFC);//v
			gcall.Stepto(42943,26224,2985);
			gcall.Stepto(42763,26141,2993);
			gcall.Stepto(42589,26051,3002);
			gcall.Stepto(42410,25965,3006);
			gcall.Stepto(42224,25890,3000);
			gcall.Stepto(42040,25816,2990);
			gcall.Stepto(41874,25690,2988);
			gcall.Stepto(41785,25468,2990);
			gcall.Stepto(41784,25465,2990);
			Sleep(2000);
			gcall.FindThenKill(0,600,modeAoe | modeNormal | modePickup);
			gcall.sendcall(id_msg_attack, (LPVOID)0x5DFC);//v
			gcall.Stepto(41793,25468,2990);
			gcall.Stepto(41925,25546,2995);
			gcall.Stepto(42054,25630,3002);
			gcall.Stepto(42183,25715,3009);
			gcall.Stepto(42332,25812,3012);
			gcall.Stepto(42498,25921,3013);
			gcall.Stepto(42640,26055,3001);
			gcall.Stepto(42664,26247,2988);
			gcall.Stepto(42654,26445,2985);
			gcall.Stepto(42643,26675,2985);
			gcall.Stepto(42631,26922,2985);
			gcall.Stepto(42623,27168,2985);
			gcall.Stepto(42620,27410,2985);
			gcall.Stepto(42552,27644,2989);
			gcall.Stepto(42316,27726,2993);
			gcall.Stepto(42088,27766,2991);
			gcall.Stepto(42087,27766,2991);
			Sleep(2000);
			gcall.FindThenKill(0,600,modeAoe | modeNormal | modePickup);
			gcall.sendcall(id_msg_attack, (LPVOID)0x5DFC);//v
			gcall.Stepto(42189,27760,2993);
			gcall.Stepto(42388,27749,2994);
			gcall.Stepto(42584,27738,2991);
			gcall.Stepto(42782,27727,2986);
			gcall.Stepto(42981,27712,2985);
			gcall.Stepto(43180,27696,2985);
			gcall.Stepto(43379,27681,2985);
			gcall.Stepto(43628,27669,2985);
			gcall.Stepto(43811,27680,2985);
			gcall.FindThenKill(0,600,modeAoe | modeNormal | modePickup);
			gcall.sendcall(id_msg_attack, (LPVOID)0x5DFC);//v
			Sleep(2000);
            break;
		case 10:
			gcall.Stepto(43840,27915,2985);
			gcall.Stepto(43838,27992,2985);
			gcall.Stepto(43832,28243,2989);
			gcall.Stepto(43828,28493,3007);
			gcall.Stepto(43825,28738,3024);
			gcall.Stepto(43822,28984,3168);
			gcall.Stepto(43819,29184,3181);
			Sleep(1000);
			gcall.GoodsQuests(zid,0xA,L"제국군 지령서");
			Sleep(1000);
			break;
		case 11:
			gcall.NewSpend(2.5);
			gcall.Stepto(43840,27915,2985);
			gcall.Stepto(43838,27992,2985);
			gcall.Stepto(43832,28243,2989);
			gcall.Stepto(43828,28493,3007);
			gcall.Stepto(43825,28738,3024);
			gcall.Stepto(43822,28984,3168);
			gcall.Stepto(43819,29184,3181);
			gcall.Stepto(43817,29383,3181);
			gcall.Stepto(43814,29581,3181);
			gcall.Stepto(43811,29778,3139);
			gcall.Stepto(43809,29982,3140);
			gcall.Stepto(43806,30114,3145);
			gcall.Stepto(43797,30362,3158);
			gcall.Stepto(43722,30590,3177);
			gcall.Stepto(43517,30729,3200);
			gcall.Stepto(43283,30772,3217);
			gcall.Stepto(43085,30794,3229);
			gcall.Stepto(42888,30819,3239);
			gcall.Stepto(42691,30853,3245);
			gcall.Stepto(42501,30907,3247);
			gcall.Stepto(42309,30977,3257);
			gcall.Stepto(42086,31091,3268);
			gcall.Stepto(41873,31216,3273);
			gcall.Stepto(41705,31372,3284);
			gcall.Stepto(41576,31526,3290);
			gcall.Stepto(41467,31689,3297);
			gcall.Stepto(41382,31868,3305);
			gcall.Stepto(41318,32056,3310);
			gcall.Stepto(41250,32261,3322);
			gcall.Stepto(41174,32496,3329);
			gcall.Stepto(41098,32733,3352);
			gcall.Stepto(41024,32969,3371);
			gcall.Stepto(40921,33197,3393);
			gcall.Stepto(40725,33337,3418);
			gcall.Stepto(40481,33324,3448);
			gcall.Stepto(40248,33235,3478);
			gcall.Stepto(40031,33117,3505);
			gcall.Stepto(39895,32913,3528);
			gcall.Stepto(39839,32672,3538);
			gcall.Stepto(39797,32426,3553);
			gcall.Stepto(39769,32177,3557);
			gcall.Stepto(39751,31933,3553);
			gcall.Stepto(39733,31684,3553);
			gcall.Stepto(39715,31436,3545);
			gcall.NewSpend(1);
			gcall.Stepto(39697,31190,3528);
			gcall.Stepto(39665,30940,3576);
			gcall.Stepto(39665,30935,3576);
			gcall.Stepto(39626,30667,3576);
			gcall.Stepto(39620,30545,3576);
			Sleep(1000);
			gcall.DeliverQuests(zid,0xB,L"일심");
			Sleep(1000);
			break;
    }
}

void TaskScript::Task_903(int zid, int taskid)
{
    switch(taskid)
    {
        case 1:
			gcall.NewSpend(2.5);
			gcall.Stepto(39622,30553,3576);
			gcall.Stepto(39634,30637,3576);
			gcall.Stepto(39658,30841,3576);
			gcall.Stepto(39669,30961,3576);
			gcall.Stepto(39680,31099,3521);
			gcall.Stepto(39700,31347,3540);
			gcall.Stepto(39720,31599,3552);
			gcall.Stepto(39750,31846,3552);
			gcall.Stepto(39781,32094,3555);
			gcall.Stepto(39812,32337,3557);
			gcall.Stepto(39844,32587,3543);
			gcall.Stepto(39925,32816,3531);
			gcall.Stepto(40100,32988,3512);
			gcall.Stepto(40297,33145,3478);
			gcall.Stepto(40504,33273,3447);
			gcall.Stepto(40736,33359,3419);
			gcall.Stepto(40971,33446,3408);
			gcall.Stepto(41203,33531,3415);
			gcall.Stepto(41436,33617,3443);
			gcall.Stepto(41670,33703,3451);
			gcall.Stepto(41884,33819,3463);
			gcall.Stepto(42031,34019,3487);
			gcall.Stepto(42126,34247,3521);
			gcall.Stepto(42186,34489,3565);
			gcall.Stepto(42234,34730,3614);
			gcall.Stepto(42244,34776,3623);
			gcall.Stepto(42246,34788,3625);
			gcall.Stepto(42294,35031,3656);
			gcall.Stepto(42342,35275,3672);
			gcall.Stepto(42390,35518,3689);
			gcall.Stepto(42438,35762,3708);
			gcall.Stepto(42512,35998,3722);
			gcall.Stepto(42608,36228,3735);
			gcall.Stepto(42703,36458,3748);
			gcall.Stepto(42819,36666,3754);
			gcall.Stepto(42977,36866,3762);
			gcall.Stepto(43132,37063,3781);
			gcall.Stepto(43284,37256,3805);
			gcall.Stepto(43440,37449,3831);
			gcall.Stepto(43604,37638,3854);
			gcall.Stepto(43769,37821,3874);
			gcall.Stepto(43939,38004,3893);
			gcall.Stepto(44109,38184,3907);
			gcall.Stepto(44287,38358,3921);
			gcall.Stepto(44497,38492,3941);
			gcall.Stepto(44718,38602,3964);
			gcall.Stepto(44938,38711,3984);
			gcall.Stepto(45169,38810,4008);
			gcall.Stepto(45400,38903,4031);
			gcall.Stepto(45631,38995,4054);
			gcall.Stepto(45861,39087,4076);
			gcall.Stepto(46076,39209,4098);
			gcall.Stepto(46281,39350,4124);
			gcall.Stepto(46487,39488,4147);
			gcall.Stepto(46696,39623,4175);
			gcall.Stepto(46907,39754,4198);
			gcall.Stepto(47118,39884,4217);
			gcall.Stepto(47329,40015,4231);
			gcall.Stepto(47540,40145,4240);
			gcall.Stepto(47752,40274,4247);
			gcall.Stepto(47978,40372,4255);
			gcall.Stepto(48229,40389,4263);
			gcall.Stepto(48477,40388,4266);
			gcall.Stepto(48725,40386,4268);
			gcall.Stepto(48973,40384,4271);
			gcall.Stepto(49221,40382,4268);
			gcall.Stepto(49469,40380,4257);
			gcall.Stepto(49717,40380,4236);
			gcall.Stepto(49968,40392,4218);
			gcall.NewSpend(1);
			gcall.Stepto(50216,40407,4206);
			gcall.Stepto(50463,40422,4179);
			gcall.Stepto(50710,40419,4187);
			gcall.Stepto(50876,40400,4190);
			
			Sleep(2000);
			gcall.Stepto(50963,40390,4192);
			gcall.WaitPlans();
			gcall.Stepto(51064,40378,4193);
			gcall.Stepto(51206,40362,4203);
			gcall.NewSpend(2.5);
			gcall.Stepto(51267,40355,4216);
			gcall.Stepto(51516,40325,4280);
			gcall.Stepto(51762,40297,4343);
			gcall.Stepto(52006,40268,4353);
			gcall.Stepto(52252,40239,4361);
			gcall.Stepto(52498,40209,4343);
			gcall.Stepto(52739,40152,4307);
			gcall.Stepto(52934,40004,4254);
			gcall.Stepto(53113,39834,4170);
			gcall.Stepto(53324,39707,4060);
			gcall.Stepto(53560,39631,3920);
			gcall.Stepto(53798,39560,3777);
			gcall.Stepto(54037,39493,3633);
			gcall.Stepto(54284,39488,3496);
			gcall.Stepto(54522,39540,3359);
			gcall.Stepto(54754,39635,3217);
			gcall.Stepto(54767,39642,3209);
			gcall.Stepto(54931,39746,3109);
			gcall.Stepto(55125,39896,3002);
			gcall.Stepto(55303,40058,2901);
			gcall.Stepto(55484,40235,2794);
			gcall.Stepto(55663,40413,2679);
			gcall.Stepto(55836,40588,2576);
			gcall.Stepto(56008,40763,2472);
			gcall.Stepto(56197,40917,2366);
			gcall.Stepto(56436,40997,2247);
			gcall.Stepto(56679,41049,2143);
			gcall.Stepto(56920,41082,2040);
			gcall.Stepto(57168,41038,2000);
			gcall.Stepto(57395,40968,1988);
			gcall.Stepto(57633,40871,1972);
			gcall.Stepto(57863,40778,1969);
			gcall.Stepto(58082,40656,1981);
			gcall.Stepto(58290,40525,1984);
			gcall.Stepto(58304,40517,1984);
			gcall.Stepto(58448,40624,2011);
			gcall.Stepto(58449,40624,2011);
			gcall.NewSpend(1);
			Sleep(1000);
			gcall.DeliverQuests(zid,taskid,L"일심");
			Sleep(1000);
            break;
        case 2:
			gcall.Stepto(L"일심");
			gcall.FindThenKill(0,700,modeAoe | modeNormal);
            break;
        case 3:
			gcall.NewSpend(2.5);
			gcall.Stepto(62580,43832,2097);
			gcall.Stepto(62593,43946,2091);
			gcall.Stepto(62548,44185,2073);
			gcall.Stepto(62487,44375,2048);
			gcall.Stepto(62422,44377,2048);
			gcall.Stepto(62167,44384,2047);
			gcall.Stepto(61918,44397,2048);
			gcall.NewSpend(1);
			gcall.FindThenKill(0,300,modeAoe | modeNormal);
			gcall.NewSpend(2.5);
			gcall.Stepto(61681,44472,2043);
			gcall.Stepto(61470,44592,2041);
			gcall.Stepto(61278,44752,2037);
			gcall.Stepto(61146,44959,2032);
			gcall.Stepto(61049,45187,2023);
			gcall.NewSpend(1);
			gcall.FindThenKill(0,300,modeAoe | modeNormal);
			gcall.NewSpend(2.5);
			gcall.Stepto(60987,45425,2008);
			gcall.Stepto(60962,45675,1991);
			gcall.Stepto(60941,45920,1992);
			gcall.Stepto(60948,46165,1989);
			gcall.Stepto(61036,46397,1979);
			gcall.Stepto(61162,46611,1993);
			gcall.NewSpend(1);
			gcall.FindThenKill(0,300,modeAoe | modeNormal);
			gcall.NewSpend(2.5);
			gcall.Stepto(61333,46790,2014);
			gcall.Stepto(61527,46943,2025);
			gcall.Stepto(61735,47082,2028);
			gcall.Stepto(61948,47205,2020);
			gcall.Stepto(62169,47319,2021);
			gcall.NewSpend(1);
			gcall.FindThenKill(0,600,modeAoe | modeNormal);
			gcall.Stepto(62397,47416,2023);
			gcall.Stepto(62629,47507,2021);
			gcall.Stepto(62860,47597,2034);
			gcall.Stepto(63092,47685,2024);
			gcall.Stepto(63299,47756,2012);
			gcall.Stepto(63490,47809,1985);
			gcall.Stepto(63683,47853,1956);
			gcall.Stepto(63878,47893,1915);
			gcall.Stepto(64074,47917,1862);
			gcall.Stepto(64302,47896,1789);
			gcall.Stepto(64545,47847,1703);
			gcall.Stepto(64772,47760,1628);
			gcall.Stepto(64947,47666,1574);
			gcall.NewSpend(1);
			gcall.FindThenKill(0,800,modeAoe | modeNormal);
			gcall.Stepto(65095,47536,1514);
			gcall.Stepto(65234,47394,1449);
			gcall.Stepto(65372,47252,1390);
			gcall.Stepto(65515,47105,1339);
			gcall.Stepto(65686,46928,1277);
			gcall.Stepto(65887,46786,1255);
			gcall.Stepto(66137,46784,1275);
			gcall.Stepto(66378,46848,1275);
			gcall.NewSpend(1);
			gcall.Stepto(66604,46916,1275);
			
			gcall.FindThenKill(0,500,modeAoe | modeNormal);
			Sleep(10000);
			gcall.DeliverQuests(zid,taskid,L"일심");
			Sleep(1000);
            break;
        case 4:
			gcall.NewSpend(2.5);
			gcall.Stepto(49832,40440,4226);
			gcall.Stepto(50054,40424,4213);
			gcall.Stepto(50302,40413,4196);
			gcall.Stepto(50554,40404,4180);
			gcall.Stepto(50802,40405,4188);
			gcall.Stepto(51013,40407,4196);
			gcall.Stepto(51239,40408,4218);
			gcall.Stepto(51278,40408,4227);
			gcall.Stepto(51267,40355,4216);
			gcall.Stepto(51516,40325,4280);
			gcall.Stepto(51762,40297,4343);
			gcall.Stepto(52006,40268,4353);
			gcall.Stepto(52252,40239,4361);
			gcall.Stepto(52498,40209,4343);
			gcall.Stepto(52739,40152,4307);
			gcall.Stepto(52934,40004,4254);
			gcall.Stepto(53113,39834,4170);
			gcall.Stepto(53324,39707,4060);
			gcall.Stepto(53560,39631,3920);
			gcall.Stepto(53798,39560,3777);
			gcall.Stepto(54037,39493,3633);
			gcall.Stepto(54284,39488,3496);
			gcall.Stepto(54522,39540,3359);
			gcall.Stepto(54754,39635,3217);
			gcall.Stepto(54767,39642,3209);
			gcall.Stepto(54931,39746,3109);
			gcall.Stepto(55125,39896,3002);
			gcall.Stepto(55303,40058,2901);
			gcall.Stepto(55484,40235,2794);
			gcall.Stepto(55663,40413,2679);
			gcall.Stepto(55836,40588,2576);
			gcall.Stepto(56008,40763,2472);
			gcall.Stepto(56197,40917,2366);
			gcall.Stepto(56436,40997,2247);
			gcall.Stepto(56679,41049,2143);
			gcall.Stepto(56920,41082,2040);
			gcall.Stepto(57168,41038,2000);
			gcall.Stepto(57395,40968,1988);
			gcall.Stepto(57633,40871,1972);
			gcall.Stepto(57863,40778,1969);
			gcall.Stepto(58082,40656,1981);
			gcall.Stepto(58290,40525,1984);
			gcall.Stepto(58304,40517,1984);
			gcall.Stepto(58448,40624,2011);
			gcall.Stepto(58449,40624,2011);
			gcall.Stepto(58429,40529,1993);
			gcall.Stepto(58441,40527,1993);
			gcall.Stepto(58684,40475,1998);
			gcall.Stepto(58926,40424,2050);
			gcall.Stepto(59169,40372,2080);
			gcall.Stepto(59416,40351,2099);
			gcall.Stepto(59663,40364,2102);
			gcall.Stepto(59911,40371,2100);
			gcall.Stepto(60159,40370,2098);
			gcall.Stepto(60407,40369,2098);
			gcall.Stepto(60655,40367,2101);
			gcall.Stepto(60902,40369,2092);
			gcall.Stepto(61149,40377,2093);
			gcall.Stepto(61397,40393,2096);
			gcall.Stepto(61643,40419,2101);
			gcall.Stepto(61894,40446,2099);
			gcall.Stepto(62129,40519,2102);
			gcall.Stepto(62323,40672,2107);
			gcall.Stepto(62470,40866,2109);
			gcall.Stepto(62569,41088,2104);
			gcall.Stepto(62627,41338,2099);
			gcall.Stepto(62652,41579,2094);
			gcall.Stepto(62669,41832,2098);
			gcall.Stepto(62677,42077,2106);
			gcall.Stepto(62684,42328,2106);
			gcall.Stepto(62684,42576,2107);
			gcall.Stepto(62683,42826,2109);
			gcall.Stepto(62682,43071,2106);
			gcall.Stepto(62550,44205,2068);
			gcall.Stepto(62491,44239,2061);
			gcall.Stepto(62268,44347,2050);
			gcall.Stepto(62025,44394,2045);
			gcall.Stepto(61778,44436,2045);
			gcall.Stepto(61552,44540,2041);
			gcall.Stepto(61366,44702,2036);
			gcall.Stepto(61216,44903,2032);
			gcall.Stepto(61107,45121,2024);
			gcall.Stepto(61018,45352,2013);
			gcall.Stepto(60959,45595,1995);
			gcall.Stepto(60967,45840,1991);
			gcall.Stepto(60991,46088,1988);
			gcall.Stepto(61060,46326,1982);
			gcall.Stepto(61191,46537,1988);
			gcall.Stepto(61348,46728,2006);
			gcall.Stepto(61537,46889,2017);
			gcall.Stepto(61735,47039,2022);
			gcall.Stepto(61942,47169,2019);
			gcall.Stepto(62165,47292,2015);
			gcall.Stepto(62384,47407,2023);
			gcall.Stepto(62613,47492,2021);
			gcall.Stepto(62847,47574,2033);
			gcall.Stepto(63081,47656,2025);
			gcall.Stepto(63315,47735,2011);
			gcall.Stepto(63550,47814,1977);
			gcall.Stepto(63790,47875,1935);
			gcall.Stepto(64036,47909,1873);
			gcall.Stepto(64284,47913,1796);
			gcall.Stepto(64531,47900,1713);
			gcall.Stepto(64765,47842,1638);
			gcall.Stepto(64994,47732,1571);
			gcall.Stepto(65176,47564,1502);
			gcall.Stepto(65356,47389,1425);
			gcall.Stepto(65532,47219,1363);
			gcall.Stepto(65717,47050,1301);
			gcall.Stepto(65922,46925,1267);
			gcall.Stepto(66045,46883,1273);
			gcall.Stepto(66287,46894,1275);
			gcall.Stepto(66296,46895,1275);
			gcall.Stepto(66140,46832,1275);
			gcall.Stepto(65910,46740,1252);
			gcall.Stepto(65680,46647,1230);
			gcall.Stepto(65491,46490,1199);
			gcall.Stepto(65325,46306,1200);
			gcall.Stepto(65164,46117,1203);
			gcall.Stepto(64973,45963,1205);
			gcall.Stepto(64767,45914,1210);
			gcall.Stepto(64765,45913,1210);
			gcall.Stepto(64527,45876,1201);
			gcall.Stepto(64285,45823,1201);
			gcall.Stepto(64156,45792,1201);
			gcall.Stepto(64347,45771,1204);
			gcall.Stepto(64139,45706,1211);
			gcall.NewSpend(1);
			Sleep(1000);
			gcall.FindThenKill(0,300,modeAoe | modeNormal | modePickup);
			gcall.Stepto(64089,45683,1213);
			gcall.Stepto(63911,45603,1210);
			gcall.Stepto(63730,45522,1214);
			gcall.Stepto(63541,45442,1203);
			gcall.Stepto(63312,45348,1199);
			gcall.Stepto(63119,45289,1214);
			gcall.Stepto(62929,45232,1227);
			gcall.Stepto(62886,45220,1228);
			gcall.FindThenKill(0,600,modeAoe | modeNormal | modePickup);
			gcall.sendcall(id_msg_attack, (LPVOID)0x5DFC);//v
			gcall.Stepto(62896,45350,1213);
			gcall.Stepto(62915,45548,1194);
			gcall.Stepto(62934,45742,1194);
			gcall.Stepto(62953,45940,1194);
			gcall.Stepto(62973,46139,1212);
			gcall.Stepto(62978,46194,1223);
			gcall.Stepto(62851,46411,1289);
			gcall.FindThenKill(0,600,modeAoe | modeNormal | modePickup);
			gcall.sendcall(id_msg_attack, (LPVOID)0x5DFC);//v
			gcall.Stepto(62828,46092,1202);
			gcall.Stepto(62661,45985,1197);
			gcall.Stepto(62494,45876,1194);
			gcall.Stepto(62330,45769,1198);
			gcall.Stepto(62163,45661,1218);
			gcall.Stepto(62023,45570,1232);
			gcall.FindThenKill(0,300,modeAoe | modeNormal | modePickup);
			gcall.sendcall(id_msg_attack, (LPVOID)0x5DFC);//v
			gcall.Stepto(61985,45725,1220);
			gcall.Stepto(62058,45906,1210);
			gcall.Stepto(62160,46077,1204);
			gcall.Stepto(62226,46260,1212);
			gcall.Stepto(62102,46397,1212);
			gcall.Stepto(61912,46450,1229);
			gcall.Stepto(61829,46449,1242);
			gcall.FindThenKill(0,300,modeAoe | modeNormal | modePickup);
			gcall.sendcall(id_msg_attack, (LPVOID)0x5DFC);//v
			gcall.Stepto(61957,46424,1220);
			gcall.Stepto(62175,46336,1216);
			gcall.Stepto(62344,46270,1216);
			gcall.Stepto(62678,46141,1213);
			gcall.Stepto(63085,45993,1195);
			gcall.Stepto(63500,45863,1194);
			gcall.Stepto(63926,45785,1196);
			gcall.Stepto(64170,45751,1204);
			gcall.FindThenKill(0,300,modeAoe | modeNormal | modePickup);
			gcall.sendcall(id_msg_attack, (LPVOID)0x5DFC);//v
            break;
        case 5:
			gcall.NewSpend(2.5);
			gcall.Stepto(64170,45751,1204);
			gcall.Stepto(64096,45757,1201);
			gcall.Stepto(63850,45784,1196);
			gcall.Stepto(63603,45812,1194);
			gcall.Stepto(63356,45839,1194);
			gcall.Stepto(63110,45866,1194);
			gcall.Stepto(62863,45893,1194);
			gcall.Stepto(62620,45939,1194);
			gcall.Stepto(62406,46062,1198);
			gcall.Stepto(62231,46237,1208);
			gcall.Stepto(62073,46428,1212);
			gcall.Stepto(61925,46630,1239);
			gcall.Stepto(61797,46839,1232);
			gcall.Stepto(61795,46844,1232);
			gcall.Stepto(61715,46974,1228);
			gcall.Stepto(61660,47065,1228);
			gcall.NewSpend(1);
			gcall.Stepto(61605,47100,1221);
			gcall.Stepto(61397,47236,1232);
			gcall.Stepto(61221,47360,1240);
			gcall.FindThenKill(0,600,modeAoe | modeNormal );
			Sleep(1000);
			gcall.FindThenKill(0,600,modeAoe | modeNormal );
			gcall.Stepto(61162,47331,1250);
			Sleep(1000);
			gcall.PickupTask();
			Sleep(1000);
			gcall.Stepto(61239,47352,1237);
			gcall.Stepto(61350,47444,1235);
			gcall.Stepto(61495,47580,1220);
			gcall.Stepto(61546,47767,1222);
			gcall.Stepto(61548,47832,1224);
			gcall.FindThenKill(0,500,modeAoe | modeNormal );
			Sleep(1000);
			gcall.FindThenKill(0,500,modeAoe | modeNormal );
			gcall.Stepto(61769,47852,1240);
			gcall.Stepto(61772,47852,1241);
			Sleep(1000);
			gcall.PickupTask();
			Sleep(1000);
			gcall.Stepto(61770,47853,1241);
			gcall.Stepto(61538,47917,1224);
			gcall.Stepto(61300,47989,1231);
			gcall.Stepto(61183,48025,1235);
			gcall.FindThenKill(0,500,modeAoe | modeNormal );
			Sleep(1000);
			gcall.FindThenKill(0,500,modeAoe | modeNormal );
			gcall.Stepto(61268,48003,1233);
			gcall.Stepto(61082,48022,1252);
			Sleep(1000);
			gcall.PickupTask();
			Sleep(1000);
			gcall.Stepto(61153,48053,1235);
			gcall.Stepto(61375,48163,1231);
			gcall.Stepto(61593,48281,1230);
			gcall.Stepto(61664,48320,1233);
			gcall.Stepto(61709,48345,1235);
			gcall.Stepto(61789,48382,1238);
			gcall.Stepto(61794,48384,1238);
			Sleep(1000);
			gcall.PickupTask();
			Sleep(1000);
			gcall.Stepto(61670,48431,1234);
			gcall.Stepto(61436,48512,1229);
			gcall.Stepto(61239,48584,1234);
			gcall.FindThenKill(0,600,modeAoe | modeNormal );
			Sleep(1000);
			gcall.FindThenKill(0,600,modeAoe | modeNormal );
			gcall.Stepto(61198,48599,1234);
			gcall.Stepto(61141,48617,1234);
			gcall.Stepto(61094,48633,1245);
			gcall.Stepto(61088,48635,1247);
			gcall.Stepto(61059,48644,1257);
			Sleep(1000);
			gcall.PickupTask();
			Sleep(1000);
			gcall.Stepto(61136,48657,1235);
			gcall.Stepto(61380,48699,1225);
			gcall.Stepto(61623,48751,1230);
			gcall.Stepto(61700,48776,1234);
			gcall.FindThenKill(0,800,modeAoe | modeNormal );
			Sleep(1000);
			gcall.FindThenKill(0,800,modeAoe | modeNormal );
			gcall.Stepto(61612,48798,1224);
			gcall.Stepto(61820,48933,1236);
			gcall.Stepto(61904,48983,1267);
			Sleep(1000);
			gcall.PickupTask();
			Sleep(1000);
			gcall.Stepto(61675,49052,1231);
			gcall.Stepto(61432,49099,1230);
			gcall.Stepto(61301,49132,1234);
			gcall.FindThenKill(0,600,modeAoe | modeNormal );
			Sleep(1000);
			gcall.FindThenKill(0,600,modeAoe | modeNormal );
			gcall.Stepto(61178,49168,1242);
			gcall.Stepto(61172,49170,1243);
			Sleep(1000);
			gcall.PickupTask();
			Sleep(1000);
			gcall.Stepto(61211,49217,1239);
			gcall.Stepto(61361,49409,1235);
			gcall.Stepto(61519,49601,1232);
			gcall.Stepto(61604,49700,1228);
			gcall.FindThenKill(0,800,modeAoe | modeNormal );
			Sleep(1000);
			gcall.FindThenKill(0,800,modeAoe | modeNormal );
			gcall.Stepto(61838,49649,1235);
			gcall.Stepto(62010,49614,1258);
			gcall.Stepto(62036,49609,1272);
			gcall.Stepto(62036,49608,1272);
			Sleep(1000);
			gcall.PickupTask();
			Sleep(1000);
			gcall.Stepto(61956,49691,1235);
			gcall.Stepto(61817,49894,1230);
			gcall.Stepto(61702,50083,1232);
			gcall.Stepto(61701,50084,1232);
			gcall.FindThenKill(0,800,modeAoe | modeNormal );
			Sleep(1000);
			gcall.FindThenKill(0,800,modeAoe | modeNormal );
			gcall.Stepto(61670,50036,1232);
			gcall.Stepto(61522,49841,1234);
			gcall.Stepto(61353,49826,1241);
			gcall.Stepto(61329,49837,1244);
			Sleep(1000);
			gcall.PickupTask();
			Sleep(1000);
			gcall.Stepto(61376,49872,1235);
			gcall.Stepto(61567,50029,1235);
			gcall.Stepto(61737,50210,1232);
			gcall.Stepto(61899,50396,1224);
			gcall.Stepto(61904,50402,1224);
			gcall.FindThenKill(0,500,modeAoe | modeNormal );
			Sleep(1000);
			gcall.FindThenKill(0,500,modeAoe | modeNormal );
			gcall.Stepto(61902,50402,1224);
			gcall.Stepto(61653,50384,1236);
			gcall.Stepto(61582,50387,1247);
			Sleep(1000);
			gcall.PickupTask();
			Sleep(1000);
			
			gcall.Stepto(61582,50387,1247);
			gcall.NewSpend(2.5);
			gcall.Stepto(61588,50212,1235);
			gcall.Stepto(61565,49778,1231);
			gcall.Stepto(61536,49345,1222);
			gcall.Stepto(61507,48912,1218);
			gcall.Stepto(61479,48479,1227);
			gcall.Stepto(61451,48046,1221);
			gcall.Stepto(61479,47613,1219);
			gcall.Stepto(61585,47194,1222);
			gcall.Stepto(61770,46801,1233);
			gcall.Stepto(61731,46821,1238);
			gcall.Stepto(61769,46746,1235);
			gcall.Stepto(61800,46685,1236);
			gcall.Stepto(61928,46473,1231);
			gcall.Stepto(62093,46288,1211);
			gcall.Stepto(62260,46105,1201);
			gcall.Stepto(62367,45989,1195);
            break;
        case 6:
			gcall.NewSpend(2.5);
			gcall.Stepto(61793,46769,1233);
			gcall.Stepto(61776,46823,1233);
			gcall.Stepto(61740,46933,1233);
			gcall.Stepto(61700,47056,1227);
			gcall.Stepto(61681,47092,1230);
			gcall.Stepto(61567,47313,1221);
			gcall.Stepto(61454,47533,1225);
			gcall.Stepto(61419,47606,1228);
			gcall.Stepto(61452,47852,1222);
			gcall.Stepto(61484,48098,1222);
			gcall.Stepto(61513,48322,1225);
			gcall.Stepto(61529,48534,1228);
			gcall.Stepto(61546,48749,1221);
			gcall.Stepto(61567,49024,1216);
			gcall.Stepto(61586,49271,1220);
			gcall.Stepto(61604,49499,1230);
			gcall.Stepto(61625,49544,1233);
			gcall.Stepto(61730,49769,1231);
			gcall.Stepto(61836,49993,1228);
			gcall.Stepto(61941,50217,1229);
			gcall.Stepto(62047,50442,1223);
			gcall.Stepto(62066,50483,1220);
			gcall.Stepto(62144,50545,1218);
			gcall.Stepto(62338,50702,1234);
			gcall.Stepto(62532,50857,1236);
			gcall.Stepto(62722,51009,1242);
			gcall.Stepto(62779,51019,1243);
			gcall.Stepto(63023,51061,1255);
			gcall.Stepto(63269,51104,1267);
			gcall.NewSpend(1);
			Sleep(5000);
			gcall.Stepto(63335,51115,1271);
			gcall.Stepto(63520,51095,1273);
			gcall.Stepto(63766,51069,1273);
			gcall.Stepto(64013,51043,1273);
			gcall.Stepto(64260,51017,1273);
			gcall.Stepto(64397,51003,1273);
			gcall.Stepto(64433,50995,1273);
			gcall.Stepto(64676,50946,1273);
			gcall.Stepto(64923,50895,1270);
			gcall.Stepto(65055,50868,1270);
			gcall.Stepto(65083,50863,1270);
			gcall.Stepto(65327,50817,1270);
			gcall.Stepto(65571,50771,1270);
			gcall.Stepto(65795,50729,1270);
			gcall.Stepto(65913,50684,1270);
			gcall.Stepto(66146,50594,1270);
			gcall.Stepto(66378,50505,1270);
			gcall.Stepto(66609,50416,1270);
			gcall.Stepto(66843,50326,1270);
			gcall.Stepto(67074,50237,1270);
			gcall.Stepto(67119,50219,1270);
			gcall.Stepto(67325,50150,1270);
			gcall.Stepto(67514,50069,1270);
			gcall.Stepto(67693,49986,1270);
			gcall.Stepto(67871,49897,1270);
			gcall.Stepto(68047,49806,1270);
			gcall.Stepto(68223,49716,1270);
			gcall.Stepto(68401,49624,1276);
			gcall.Stepto(68580,49537,1265);
			gcall.Stepto(68759,49457,1259);
			gcall.Stepto(68943,49375,1250);
			gcall.Stepto(69155,49297,1236);
			gcall.Stepto(69390,49222,1174);
			gcall.Stepto(69628,49150,1113);
			gcall.Stepto(69866,49077,1084);
			gcall.Stepto(70098,48991,1087);
			gcall.Stepto(70285,48874,1087);
			gcall.Stepto(70286,48874,1087);
			gcall.sendcall(id_msg_attack, (LPVOID)0x5E06);//3
			Sleep(1500);
			gcall.sendcall(id_msg_attack, (LPVOID)0x5E1A);//E
			Sleep(800);
			gcall.Kill_Tab();
			gcall.sendcall(id_msg_attack, (LPVOID)0x5DE8);//z
			Sleep(800);
			gcall.Kill_Tab();
			Sleep(500);
			gcall.sendcall(id_msg_attack, (LPVOID)0x5dc1);//r
			Sleep(500);
			gcall.Kill_Tab();
			gcall.TurnToNear(500);
			Sleep(500);
			gcall.sendcall(id_msg_attack, (LPVOID)0x5e74);//1
			gcall.Kill_Tab();
			Sleep(500);
			gcall.sendcall(id_msg_attack, (LPVOID)0x5dc1);//r
			Sleep(500);
			gcall.Kill_Tab();
			gcall.TurnToNear(500);
			Sleep(500);
			gcall.sendcall(id_msg_attack, (LPVOID)0x5E10);//4
			gcall.FindThenKill(0,600,modeAoe | modeNormal);
			gcall.Stepto(70670,48770,1087);
			gcall.Stepto(70674,48755,1087);
			gcall.Stepto(70699,48681,1087);
			Sleep(1000);
			gcall.DeliverQuests(zid,taskid,L"유태월");
			Sleep(12000);
            break;
        case 7:
			gcall.Stepto(70579,48732,1087);
			gcall.Stepto(70405,48749,1087);
			gcall.Stepto(70167,48877,1087);
			gcall.sendcall(id_msg_attack, (LPVOID)0x5E06);//3
			Sleep(1500);
			gcall.sendcall(id_msg_attack, (LPVOID)0x5E1A);//E
			Sleep(800);
			gcall.Kill_Tab();
			gcall.sendcall(id_msg_attack, (LPVOID)0x5DE8);//z
			Sleep(800);
			gcall.Kill_Tab();
			Sleep(500);
			gcall.sendcall(id_msg_attack, (LPVOID)0x5dc1);//r
			Sleep(500);
			gcall.Kill_Tab();
			gcall.TurnToNear(500);
			Sleep(500);
			gcall.sendcall(id_msg_attack, (LPVOID)0x5e74);//1
			gcall.Kill_Tab();
			Sleep(500);
			gcall.sendcall(id_msg_attack, (LPVOID)0x5dc1);//r
			Sleep(500);
			gcall.Kill_Tab();
			gcall.TurnToNear(500);
			Sleep(500);
			gcall.sendcall(id_msg_attack, (LPVOID)0x5E10);//4
			gcall.FindThenKill(0,1200,modeAoe | modeNormal);
			gcall.AddCustomKill(L"월광회 회원",DONTKILL);
			gcall.Kill_Tab();
			gcall.Kill_Tab();
			gcall.Kill_Tab();
			gcall.FindThenKill(0,700,modeAoe | modeNormal);
			Sleep(2000);
            break;
        case 8:
			gcall.Stepto(70643,48679,1087);
			gcall.Stepto(70675,48662,1087);
			Sleep(1000);
			gcall.DeliverQuests(zid,taskid,L"유태월");
			Sleep(1000);
            break;
        case 9:
			gcall.CityConvey(0x26);
			Sleep(2000);
			gcall.Stepto(39904,31630,3547);
			gcall.Stepto(39768,31596,3551);
			gcall.Stepto(39747,31457,3545);
			gcall.Stepto(39707,31213,3530);
			gcall.Stepto(39669,30970,3576);
			gcall.Stepto(39660,30903,3576);
			gcall.Stepto(39636,30658,3576);
			gcall.Stepto(39634,30610,3576);
			Sleep(1000);
			gcall.DeliverQuests(zid,taskid,L"유태월");
			Sleep(1000);
            break;
		case 10:
			gcall.NewSpend(2.5);
			gcall.Stepto(39657,30794,3576);
			gcall.Stepto(39670,30955,3576);
			gcall.Stepto(39682,31073,3540);
			gcall.Stepto(39708,31315,3537);
			gcall.Stepto(39734,31565,3552);
			gcall.Stepto(39759,31807,3553);
			gcall.Stepto(39783,32037,3554);
			gcall.Stepto(39802,32217,3557);
			gcall.Stepto(39818,32375,3557);
			gcall.Stepto(39844,32622,3541);
			gcall.Stepto(39871,32865,3531);
			gcall.Stepto(40034,33047,3510);
			gcall.Stepto(40234,33197,3482);
			gcall.Stepto(40453,33311,3451);
			gcall.Stepto(40682,33406,3424);
			gcall.Stepto(40924,33462,3414);
			gcall.Stepto(41166,33508,3412);
			gcall.Stepto(41412,33555,3434);
			gcall.Stepto(41644,33635,3444);
			gcall.Stepto(41860,33761,3458);
			gcall.Stepto(42052,33912,3474);
			gcall.Stepto(42179,34118,3499);
			gcall.Stepto(42201,34366,3541);
			gcall.Stepto(42219,34610,3589);
			gcall.Stepto(42237,34859,3637);
			gcall.Stepto(42255,35106,3659);
			gcall.Stepto(42273,35353,3671);
			gcall.Stepto(42291,35600,3689);
			gcall.Stepto(42309,35848,3708);
			gcall.Stepto(42314,36096,3725);
			gcall.Stepto(42298,36344,3740);
			gcall.Stepto(42275,36591,3755);
			gcall.Stepto(42252,36837,3766);
			gcall.Stepto(42226,37084,3780);
			gcall.Stepto(42198,37330,3797);
			gcall.Stepto(42163,37576,3813);
			gcall.Stepto(42109,37819,3832);
			gcall.Stepto(42062,38062,3861);
			gcall.Stepto(42031,38310,3893);
			gcall.Stepto(41999,38556,3919);
			gcall.Stepto(41968,38802,3935);
			gcall.Stepto(41930,39050,3942);
			gcall.Stepto(41873,39291,3953);
			gcall.Stepto(41814,39532,3967);
			gcall.Stepto(41754,39773,3983);
			gcall.Stepto(41695,40012,4005);
			gcall.Stepto(41633,40252,4033);
			gcall.Stepto(41559,40491,4065);
			gcall.Stepto(41485,40727,4094);
			gcall.Stepto(41420,40936,4128);
			gcall.Stepto(41360,41126,4164);
			gcall.Stepto(41301,41315,4207);
			gcall.Stepto(41251,41507,4241);
			gcall.Stepto(41218,41703,4264);
			gcall.Stepto(41195,41900,4278);
			gcall.Stepto(41177,42097,4286);
			gcall.Stepto(41158,42295,4291);
			gcall.Stepto(41138,42511,4312);
			gcall.Stepto(41116,42758,4344);
			gcall.Stepto(41109,42957,4372);
			gcall.Stepto(41128,43155,4397);
			gcall.Stepto(41163,43350,4422);
			gcall.Stepto(41225,43539,4453);
			gcall.Stepto(41302,43722,4485);
			gcall.Stepto(41398,43951,4525);
			gcall.Stepto(41494,44179,4563);
			gcall.Stepto(41591,44408,4595);
			gcall.Stepto(41689,44639,4626);
			gcall.Stepto(41801,44860,4658);
			gcall.Stepto(41941,45065,4688);
			gcall.Stepto(42097,45258,4738);
			gcall.Stepto(42253,45450,4792);
			gcall.Stepto(42410,45641,4940);
			gcall.Stepto(42585,45816,5066);
			gcall.Stepto(42771,45987,5216);
			gcall.Stepto(42916,46120,5291);
			gcall.NewSpend(1);
			gcall.Stepto(42941,46147,5291);
			gcall.Stepto(42962,46170,5297);
			gcall.Stepto(42990,46200,5300);
			gcall.Stepto(43078,46288,5305);
			
			gcall.Stepto(43704,46516,5304);
			gcall.WaitPlans();
			gcall.Stepto(43704,46516,5304);
			gcall.Stepto(43704,46516,5310);
			gcall.Stepto(43704,46516,5308);
			gcall.Stepto(43826,46529,5311);
			gcall.Stepto(44065,46466,5311);
			gcall.Stepto(44205,46353,5311);
			
			Sleep(1000);
			gcall.DeliverQuests(zid,0xA,L"일심");
			Sleep(1000);
			break;
		case 11:
			gcall.Stepto(44744,46577,5310);
			gcall.Stepto(44673,46542,5310);
			gcall.Stepto(44752,46609,5310);
			gcall.Stepto(44913,46725,5310);
			gcall.Stepto(45075,46840,5310);
			gcall.Stepto(45237,46955,5310);
			Sleep(1000);
			gcall.FindThenKill(0,700,modeAoe | modeNormal);
			Sleep(1000);
			gcall.FindThenKill(0,700,modeAoe | modeNormal);
			gcall.Stepto(45399,47069,5307);
			gcall.Stepto(45559,47187,5300);
			gcall.Stepto(45706,47320,5296);
			gcall.Stepto(45857,47487,5293);
			gcall.Stepto(45994,47694,5291);
			Sleep(1000);
			gcall.FindThenKill(0,1000,modeAoe | modeNormal);
			Sleep(1000);
			gcall.FindThenKill(0,1000,modeAoe | modeNormal);
			gcall.Stepto(46034,47765,5289);
			gcall.Stepto(46047,47790,5288);
			gcall.Stepto(46159,48011,5282);
			gcall.Stepto(46259,48208,5276);
			Sleep(3000);
			gcall.PickupTask();
			Sleep(2500);
			gcall.Stepto(46266,48198,5276);
			gcall.Stepto(46410,47996,5287);
			gcall.Stepto(46558,47798,5292);
			gcall.Stepto(46768,47667,5296);
			gcall.Stepto(46985,47554,5295);
			gcall.Stepto(47214,47458,5293);
			gcall.Stepto(47266,47435,5290);
			Sleep(1000);
			gcall.FindThenKill(0,700,modeAoe | modeNormal);
			Sleep(1000);
			gcall.FindThenKill(0,700,modeAoe | modeNormal);
			gcall.Stepto(47383,47365,5288);
			gcall.Stepto(47556,47267,5282);
			gcall.Stepto(47668,47203,5277);
			Sleep(1000);
			gcall.FindThenKill(0,700,modeAoe | modeNormal);
			gcall.Stepto(47746,47164,5275);
			gcall.Stepto(47967,47052,5270);
			gcall.Stepto(48154,46919,5273);
			gcall.Stepto(48191,46893,5272);
			Sleep(1000);
			gcall.FindThenKill(0,700,modeAoe | modeNormal);
			Sleep(10000);
			gcall.sendcall(id_msg_attack, (LPVOID)0x5E06);//3
			Sleep(1500);
			gcall.sendcall(id_msg_attack, (LPVOID)0x5E1A);//E
			Sleep(800);
			gcall.Kill_Tab();
			gcall.sendcall(id_msg_attack, (LPVOID)0x5DE8);//z
			Sleep(800);
			gcall.Kill_Tab();
			Sleep(500);
			gcall.sendcall(id_msg_attack, (LPVOID)0x5dc1);//r
			Sleep(500);
			gcall.Kill_Tab();
			gcall.TurnToNear(500);
			Sleep(500);
			gcall.sendcall(id_msg_attack, (LPVOID)0x5e74);//1
			gcall.Kill_Tab();
			Sleep(500);
			gcall.sendcall(id_msg_attack, (LPVOID)0x5dc1);//r
			Sleep(500);
			gcall.Kill_Tab();
			gcall.TurnToNear(500);
			Sleep(500);
			gcall.sendcall(id_msg_attack, (LPVOID)0x5E10);//4
			gcall.FindThenKill(0,800,modeAoe | modeNormal);
			gcall.Stepto(48061,46912,5272);
			gcall.Kill_Tab();
			gcall.Kill_Tab();
			gcall.Kill_Tab();
			gcall.FindThenKill(0,600,modeAoe | modeNormal);
			Sleep(1200);
			gcall.Stepto(48355,46896,5269);
			gcall.Stepto(48466,46898,5267);
			Sleep(1000);
			gcall.PickupTask();
			Sleep(10000);
			gcall.WaitPlans();
			break;
		case 12:
			Sleep(10000);
			gcall.Stepto(12060,-3449,6510);
			Sleep(1000);
			gcall.DeliverQuests(zid,0xC,L"일심");
			Sleep(1000);
			break;
    }
}

void TaskScript::Task_904(int zid, int taskid)
{
    switch(taskid)
    {
        case 1:
            MessageBox(0, L"904", L"装八卦", MB_OK);
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

void TaskScript::Task_905(int zid, int taskid)
{
    switch(taskid)
    {
        case 1:
            MessageBox(0, L"905", L"装八卦", MB_OK);
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



=======
#include "stdafx.h"
>>>>>>> ec82f68341aec048924c2ea5f64172867a97816d
