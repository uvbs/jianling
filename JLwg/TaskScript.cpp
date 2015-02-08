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
	{ TEXT("525"), &TaskScript::Task_525 },//2-
	{ TEXT("526"), &TaskScript::Task_526 },//2-
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
		while (1)
		{
			DWORD pStartAddr = gcall.GetTaskStartAddr();//获取任务开始地址

			//log(TEXT("%08x"),pStartAddr);
			DWORD ID = gcall.GetTaskID(0, pStartAddr);//获得当前任务ID
			DWORD info = gcall.GetPresentTaskIndexes(0, pStartAddr);//获得当前做到第几个小任务

			DWORD nameid = gcall.GetTaskNameID(0, pStartAddr);//获取当前任务吊id
			//wchar_t* taskname = gcall.GatTaskName(nameid);//获得当前任务吊

			//if (ID == 227)
			//{
			//	break;
			//}
			if (ID == -1 || info == -1)
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
			TCHAR szbu[20] = { 0 };
			for (int i = 0; i < 0x400; i++)
			{
				if (lstrcmp(ft[i].taskname, szBu_id) == 0)
				{
					wsprintf(szbu, TEXT("任务函数开始执行.id:%s,task_id:%d,数组下标:%d"), ft[i].taskname, info, i);
					log(szbu);
					(ts.*(ft[i].fp))(ID,info);
					log(TEXT("任务函数执行完成"));
					break;
				}
				else
				{
					log(_T("当前任务:%d,函数ID:%s,数组id:%s"),ID,szBu_id,ft[i].taskname);
				}
			}
		}


		//Task_221_2();
	}
	catch (...)
	{
		log(TEXT("获取任务异常"));
	}
}

void TaskScript::Task_221(int zid,int taskid)
{
	switch (taskid)
	{
	case 1:
		//gcall.SetMouseMode();

	
		






		Sleep(1000);
		gcall.KeyPress(27);
		Sleep(500);
		gcall.KeyPress(27);
		Sleep(500);
		gcall.DeliverQuests(zid, taskid, L"진영");
		Sleep(500);
		break;
	case 2:
		log(TEXT("开始走路"));
		gcall.Stepto(36942, -12657, 2336);
		Sleep(500);
		log(TEXT("捡物"));
		gcall.PickupTask();
		/*Sleep(3000);
		log(TEXT("按F"));
		gcall.KeyPress(70);*/
		Sleep(1000);
		break;
	case 3:
		gcall.WearEquipment(L"홍문파 도복", 2);//穿装备

		Sleep(1000);
		break;
	case 4:
		gcall.DeliverQuests(zid, taskid, L"진영");
		Sleep(5000);
		break;
	case 5:
		gcall.Stepto(37084, -12695, 2336);
		gcall.Stepto(37200, -12506, 2336);
		gcall.Stepto(37274, -12252, 2336);
		gcall.Stepto(37012, -12103, 2336);
		Sleep(2000);
		break;
	case 6:
		gcall.Stepto(36859, -12302, 2336);
		gcall.Stepto(36745, -12502, 2336);
		gcall.Stepto(36712, -12601, 2336);
		Sleep(1000);
		gcall.PickupTask(180);
		Sleep(1000);
		break;
	case 7:
		gcall.DeliverQuests(zid, taskid, L"길홍");
		Sleep(1000);
		break;
	}
}

void TaskScript::Task_222(int zid,int taskid)
{
	switch (taskid)
	{
	case 1:
		gcall.Stepto(36725, -12478, 2334);
		gcall.Stepto(36810, -12389, 2334);
		gcall.Stepto(36874, -12289, 2334);
		gcall.Stepto(36949, -12218, 2334);
		Sleep(1000);
		break;
	case 2:
		break;
	case 3:
		break;
	case 4:
		gcall.DeliverQuests(zid, taskid, L"진영");
		Sleep(1000);
		break;
	}

}


void TaskScript::Task_223(int zid,int taskid)
{
	switch (taskid)
	{
	case 1:
		//log(_T("执行2231"));
		gcall.Stepto(36981, -12151, 2334);
		gcall.Stepto(37066, -12060, 2333);
		gcall.Stepto(37158, -11956, 2333);
		gcall.Stepto(37262, -11847, 2331);
		gcall.Stepto(37374, -11725, 2316);
		gcall.Stepto(37552, -11527, 2216);
		gcall.Stepto(37786, -11331, 2171);
		gcall.Stepto(37980, -11222, 2172);
		gcall.Stepto(38158, -11134, 2178);
		gcall.Stepto(38380, -11019, 2163);
		gcall.Stepto(38600, -10887, 2148);
		gcall.Stepto(38852, -10762, 2139);
		gcall.Stepto(39091, -10683, 2142);
		gcall.Stepto(39273, -10627, 2151);
		gcall.Stepto(39462, -10564, 2152);
		Sleep(500);
		break;
	case 2:
		gcall.Stepto(39475, -10586, 2156);
		Sleep(500);
		gcall.DeliverQuests(zid, taskid, L"영묵");
		Sleep(1000);
		break;
	case 3:
		gcall.NewSpend(2.5);
		gcall.Stepto(38949, -10508, 2153);
		gcall.Stepto(38313, -10305, 2204);
		gcall.Stepto(37900, -10167, 2241);
		gcall.Stepto(37281, -9861, 2222);
		gcall.Stepto(36726, -9581, 2195);
		gcall.Stepto(35960, -9459, 2268);
		gcall.Stepto(35217, -9310, 2183);
		gcall.Stepto(34561, -8948, 2209);
		gcall.Stepto(33961, -8841, 2257);
		gcall.Stepto(33285, -9068, 2535);
		gcall.Stepto(32961, -8874, 2596);
		gcall.Stepto(32993, -8704, 2601);
		gcall.Stepto(33045, -8681, 2602);
		gcall.NewSpend(1);
		Sleep(1000);
		gcall.KeyPress(27);
		Sleep(500);
		gcall.Stepto(33712, -8121, 2636);
		Sleep(1000);
		gcall.KeyPress(27);
		Sleep(500);
		gcall.KeyPress(27);
		Sleep(500);
		gcall.Stepto(33712, -8121, 2636);
		Sleep(1000);
		break;
	case 4:
		gcall.Stepto(33823, -8043, 2636);
		Sleep(1000);
		gcall.DeliverQuests(zid, taskid, L"무성");
		break;

	}


}


void TaskScript::Task_224(int zid,int taskid)
{
	switch (taskid)
	{
	case 1:
		gcall.NewSpend(2.5);
		gcall.Stepto(33976, -8212, 2652);
		gcall.Stepto(34123, -8347, 2620);
		gcall.Stepto(34316, -8508, 2225);
		gcall.Stepto(34511, -8662, 2216);
		gcall.Stepto(34668, -8779, 2214);
		gcall.Stepto(34790, -8870, 2211);
		gcall.Stepto(34913, -9068, 2206);
		gcall.Stepto(35091, -9228, 2201);
		gcall.Stepto(35294, -9340, 2184);
		gcall.Stepto(35451, -9387, 2186);
		gcall.Stepto(35698, -9408, 2241);
		gcall.Stepto(35942, -9448, 2268);
		gcall.Stepto(36187, -9488, 2267);
		gcall.Stepto(36434, -9529, 2235);
		gcall.Stepto(36678, -9570, 2194);
		gcall.Stepto(36692, -9572, 2193);
		gcall.Stepto(36778, -9669, 2202);
		gcall.Stepto(36921, -9863, 2217);
		gcall.Stepto(37155, -9942, 2211);
		gcall.Stepto(37391, -10021, 2220);
		gcall.Stepto(37623, -10098, 2234);
		gcall.Stepto(37697, -10042, 2243);
		gcall.Stepto(37878, -9864, 2266);
		gcall.Stepto(38059, -9696, 2288);
		gcall.Stepto(38242, -9521, 2301);
		gcall.Stepto(38421, -9349, 2324);
		gcall.Stepto(38600, -9183, 2353);
		gcall.Stepto(38787, -9020, 2360);
		gcall.Stepto(38882, -8924, 2360);
		gcall.Stepto(38897, -8908, 2360);
		gcall.Stepto(38922, -8879, 2360);
		gcall.NewSpend(1);
		Sleep(1000);
		break;
	case 2:
		gcall.DeliverQuests(zid, taskid, L"홍석근", 0);
		Sleep(1000);
		break;
	case 3:
		gcall.Stepto(38945, -8763, 2360);
		gcall.Stepto(38618, -8439, 2508);
		gcall.Stepto(38244, -8048, 2705);
		gcall.Stepto(38047, -7771, 2739);
		gcall.Stepto(37904, -7456, 2739);
		gcall.Stepto(37771, -7355, 2743);
		gcall.Stepto(37619, -7377, 2743);
		Sleep(1000);
		break;
	case 4:
		Sleep(1000);
		gcall.Stepto(37619, -7377, 2743);
		Sleep(1000);
		gcall.PickupTask();
		//Sleep(4000);
		//gcall.KeyPress(70);
		Sleep(2000);
		break;
	case 5:
		gcall.DeliverQuests(zid, 5, NULL,1,0,1);
		Sleep(3000);
		break;
	case 6:
		gcall.Stepto(37685, -7270, 2743);
		Sleep(500);
		gcall.DeliverQuests(zid, taskid, L"홍석근");
		Sleep(1000);
		break;
	}
}


void TaskScript::Task_231(int zid,int taskid)
{
	switch (taskid)
	{
	case 1:
		gcall.NewSpend(2.5);
		gcall.Stepto(37796, -7362, 2743);
		gcall.Stepto(37908, -7463, 2739);
		gcall.Stepto(38061, -7857, 2739);
		gcall.Stepto(38165, -7999, 2732);
		gcall.Stepto(38297, -8122, 2672);
		gcall.Stepto(38402, -8237, 2616);
		gcall.Stepto(38575, -8415, 2525);
		gcall.Stepto(38747, -8593, 2435);
		gcall.Stepto(38918, -8770, 2360);
		gcall.Stepto(39010, -8862, 2360);
		gcall.Stepto(39133, -8906, 2360);
		gcall.Stepto(39290, -8961, 2357);
		gcall.Stepto(39527, -9032, 2277);
		gcall.Stepto(39766, -9099, 2189);
		gcall.Stepto(39874, -9140, 2157);
		gcall.Stepto(39935, -9252, 2148);
		gcall.Stepto(40026, -9422, 2145);
		gcall.Stepto(40158, -9439, 2145);
		gcall.Stepto(40402, -9480, 2072);
		gcall.Stepto(40562, -9511, 2045);
		gcall.Stepto(40773, -9582, 2016);
		gcall.Stepto(40836, -9562, 2012);
		gcall.Stepto(41019, -9506, 1992);
		gcall.Stepto(41185, -9441, 2039);
		gcall.Stepto(41418, -9367, 2127);
		gcall.Stepto(41621, -9306, 2202);
		gcall.Stepto(41901, -9220, 2226);
		gcall.Stepto(42135, -9147, 2226);
		gcall.Stepto(42373, -9073, 2232);
		gcall.Stepto(42489, -9037, 2232);
		gcall.Stepto(42523, -9026, 2232);
		gcall.NewSpend(1);
		Sleep(1000);
		gcall.DeliverQuests(zid, taskid, L"영묵");
		Sleep(1000);
		break;
	case 2:
		gcall.WearEquipment(L"수련용 도끼", 1);
		Sleep(1000);
		break;
	case 3:
		gcall.Stepto(42894, -8913, 2226);
		gcall.Stepto(43123, -8821, 2226);
		gcall.Stepto(43508, -8667, 2226);
		gcall.Stepto(43894, -8569, 2226);
		gcall.Stepto(44196, -8470, 2226);
		Sleep(5000);
		break;
	}
}


void TaskScript::Task_232(int zid,int taskid)
{
	switch (taskid)
	{
	case 1:
		gcall.DeliverQuests(zid, taskid, L"영묵");
		Sleep(1000);
		break;
	case 2:
		gcall.DeliverQuests(zid, taskid, NULL);
		Sleep(500);
		gcall.DeliverQuests(zid, taskid, NULL);
		Sleep(500);
		gcall.DeliverQuests(zid, taskid, NULL);
		Sleep(1000);
		break;
	case 3:
		gcall.DeliverQuests(zid, 4, NULL);
		Sleep(500);
		gcall.DeliverQuests(zid, 4, NULL);
		Sleep(500);
		gcall.DeliverQuests(zid, 4, NULL);
		Sleep(1000);
		break;
	}
}

void TaskScript::Task_227(int zid,int taskid)
{
	switch (taskid)
	{
	case 1:
		gcall.DeliverQuests(zid, 1, L"영묵");
		Sleep(1000);
		gcall.DeliverQuests(zid, 1, NULL);
		Sleep(1000);
		break;
	case 2:
		//log(_T("227-2"));
		gcall.DeliverQuests(zid, 2, L"영묵", 1,0,0);
		Sleep(1000);
		break;
	case 3:
		gcall.NewSpend(2.5);
		gcall.Stepto(44185, -8432, 2226);
		gcall.Stepto(44135, -8450, 2226);
		gcall.Stepto(43900, -8532, 2226);
		gcall.Stepto(43666, -8614, 2226);
		gcall.Stepto(43433, -8695, 2226);
		gcall.Stepto(43199, -8778, 2226);
		gcall.Stepto(42965, -8860, 2226);
		gcall.Stepto(42731, -8942, 2232);
		gcall.Stepto(42497, -9024, 2232);
		gcall.Stepto(42263, -9105, 2226);
		gcall.Stepto(42027, -9180, 2226);
		gcall.Stepto(41910, -9215, 2226);
		gcall.Stepto(41855, -9232, 2226);
		gcall.Stepto(41616, -9303, 2201);
		gcall.Stepto(41376, -9377, 2111);
		gcall.Stepto(41139, -9450, 2023);
		gcall.Stepto(40902, -9524, 2008);
		gcall.Stepto(40665, -9597, 2028);
		gcall.Stepto(40631, -9608, 2032);
		gcall.Stepto(40626, -9835, 2052);
		gcall.Stepto(40615, -10082, 2067);
		gcall.Stepto(40604, -10330, 2062);
		gcall.Stepto(40594, -10578, 2059);
		gcall.Stepto(40583, -10826, 2051);
		gcall.Stepto(40580, -11074, 2030);
		gcall.Stepto(40688, -11295, 1999);
		gcall.Stepto(40795, -11452, 1990);
		gcall.Stepto(40926, -11662, 1957);
		gcall.Stepto(41058, -11873, 1888);
		gcall.Stepto(41189, -12083, 1831);
		gcall.Stepto(41321, -12294, 1770);
		gcall.Stepto(41448, -12494, 1722);
		gcall.Stepto(41549, -12581, 1709);
		gcall.Stepto(41732, -12748, 1693);
		gcall.Stepto(41918, -12911, 1692);
		gcall.Stepto(42108, -13078, 1630);
		gcall.Stepto(42293, -13242, 1504);
		gcall.Stepto(42473, -13414, 1446);
		gcall.Stepto(42658, -13583, 1326);
		gcall.Stepto(42847, -13743, 1246);
		gcall.Stepto(43043, -13901, 1208);
		gcall.Stepto(43236, -14057, 1211);
		gcall.Stepto(43429, -14212, 1222);
		gcall.Stepto(43451, -14230, 1223);
		gcall.Stepto(43450, -14410, 1230);
		gcall.Stepto(43456, -14658, 1239);
		gcall.Stepto(43462, -14906, 1249);
		gcall.Stepto(43468, -15158, 1256);
		gcall.Stepto(43468, -15403, 1269);
		gcall.Stepto(43491, -15551, 1270);
		gcall.Stepto(43542, -15796, 1270);
		gcall.Stepto(43594, -16038, 1271);
		gcall.Stepto(43646, -16285, 1270);
		gcall.Stepto(43697, -16528, 1279);
		gcall.Stepto(43749, -16771, 1281);
		gcall.Stepto(43800, -17014, 1283);
		gcall.Stepto(43852, -17259, 1284);
		gcall.Stepto(43877, -17379, 1284);
		gcall.NewSpend(1);
		Sleep(2000);
		break;
	case 4:
		gcall.Stepto(43964, -17699, 1291);
		gcall.Stepto(44041, -17994, 1313);
		gcall.Stepto(44417, -18314, 1316);
		gcall.Stepto(44741, -18653, 1277);
		gcall.Stepto(44822, -19080, 1214);
		gcall.Stepto(44752, -19269, 1185);
		gcall.Stepto(44500, -19680, 1106);
		gcall.Stepto(44091, -20182, 993);
		gcall.Stepto(44127, -20791, 1018);
		gcall.Stepto(44149, -21160, 1018);
		Sleep(500);
		gcall.FindThenKill(0, 600, modeNormal | modeAoe | modeGoback);
		Sleep(1000);
		break;
	case 5:
		Sleep(1000);
		gcall.Stepto(44149, -21306, 1018);
		Sleep(10000);
		break;
	case 6:
		Sleep(1000);
		gcall.KeyPress(49);
		//gcall.DeliverQuests(227, taskid, 0, 0, 0, 1);
		Sleep(25000);
		break;
	case 7:
		//gcall.UseItem(L"작은 야채 만두");
		gcall.ChiYao(L"약수 회복약");
		Sleep(2000);
		break;
	case 8:
		gcall.Stepto(44193, -21271, 1018);
		gcall.Stepto(44143, -21255, 1018);
		Sleep(1000);
		gcall.DeliverQuests(227, taskid, L"무성");
		Sleep(2000);
		break;
	case 9:
		gcall.Stepto(43833, -21202, 1018);
		Sleep(1000);
		gcall.KeyPress(70);
		Sleep(15000);
		break;
	case 10:
		Sleep(1000);
		gcall.Stepto(44133, -21241, 1018);
		Sleep(1000);
		gcall.DeliverQuests(227, 0xa, L"무성",1);
		Sleep(2000);
		break;
	}
}
void TaskScript::Task_243(int zid,int taskid)
{
	switch (taskid)
	{
	case 1:
		Sleep(1000);
		gcall.NewSpend(2.5);
		gcall.Stepto(44133, -21241, 1018);
		gcall.Stepto(44124, -21109, 1018);
		gcall.Stepto(44117, -20863, 1018);
		gcall.Stepto(44112, -20615, 1016);
		gcall.Stepto(44145, -20370, 1002);
		gcall.Stepto(44206, -20129, 1000);
		gcall.Stepto(44327, -19914, 1048);
		gcall.Stepto(44468, -19709, 1098);
		gcall.Stepto(44607, -19504, 1145);
		gcall.Stepto(44669, -19398, 1166);
		gcall.Stepto(44680, -19376, 1170);
		gcall.Stepto(44748, -19138, 1212);
		gcall.Stepto(44806, -18904, 1248);
		gcall.Stepto(44810, -18656, 1280);
		gcall.Stepto(44810, -18638, 1283);
		gcall.Stepto(44746, -18441, 1305);
		gcall.Stepto(44555, -18298, 1315);
		gcall.Stepto(44404, -18151, 1319);
		gcall.Stepto(44241, -17988, 1313);
		gcall.Stepto(44055, -17770, 1303);
		gcall.Stepto(44021, -17666, 1288);
		gcall.Stepto(43967, -17424, 1283);
		gcall.Stepto(43915, -17182, 1284);
		gcall.Stepto(43912, -17171, 1284);
		Sleep(2000);
		break;
	case 2:
		gcall.Stepto(43845, -16877, 1282);
		gcall.Stepto(43635, -16038, 1271);
		gcall.Stepto(43569, -15636, 1270);
		gcall.Stepto(43507, -15214, 1259);
		gcall.Stepto(43486, -14762, 1244);
		gcall.Stepto(43455, -14186, 1222);
		gcall.Stepto(43324, -14095, 1216);
		gcall.Stepto(43215, -14015, 1208);
		gcall.Stepto(43098, -13929, 1202);
		gcall.Stepto(42998, -13855, 1241);
		gcall.Stepto(42636, -13557, 1343);

		gcall.NewSpend(1);
		//对准角度(42848, -13754, 1246);
		Sleep(3000);
		//跑();
		//Sleep(2000);
		//gcall.KeyPress(27);
		//Sleep(1000);
		//gcall.KeyPress(27);
		break;
	case 3:
		/*gcall.Stepto(42992, -13866, 1240);
		gcall.Stepto(42943, -13823, 1246);
		gcall.Stepto(42752, -13658, 1264);
		gcall.Stepto(42567, -13497, 1389);
		gcall.Stepto(42376, -13332, 1446);
		gcall.Stepto(42191, -13171, 1566);
		gcall.Stepto(42006, -13011, 1683);
		gcall.Stepto(41832, -12829, 1692);
		gcall.Stepto(41686, -12633, 1699);
		gcall.Stepto(41535, -12430, 1720);
		gcall.Stepto(41396, -12229, 1769);
		gcall.Stepto(41265, -12023, 1830);
		gcall.Stepto(41126, -11811, 1888);
		gcall.Stepto(40987, -11610, 1952);
		gcall.Stepto(40846, -11400, 1991);*/
		gcall.Stepto(40717, -11192, 2005);
		gcall.Stepto(40584, -10977, 2036);
		gcall.Stepto(40454, -10770, 2055);
		gcall.Stepto(40307, -10575, 2110);
		gcall.Stepto(40132, -10393, 2155);
		gcall.Stepto(39961, -10217, 2158);
		gcall.Stepto(39938, -10193, 2157);
		gcall.Stepto(39520, -9973, 2156);
		Sleep(1000);
		//gcall.FindThenKill(0, 1000, modeNormal | modeAoe | modeGoback | modeTask,3,243);
		gcall.FindThenKill(0, 1000, modeNormal | modeAoe);
		Sleep(10000);
		gcall.KeyPress(27);
		//Sleep(1000);
		//gcall.KeyPress(27);
		//Sleep(10000);
		//gcall.KeyPress(27);
		//Sleep(1000);
		//gcall.WaitPlans();
		break;

	}
}

void TaskScript::Task_301(int zid,int taskid)
{
	switch (taskid)
	{
	case 1:
		gcall.WaitPlans();
		Sleep(1000);
		gcall.KeyPress(27);
		Sleep(1000);
		gcall.Stepto(-51145, -54519, -3042, 10, 20, 200);
		gcall.Stepto(-51066, -54428, -3033, 10, 20, 200);
		gcall.Stepto(-50982, -54346, -3012, 10, 20, 200);
		gcall.Stepto(-50894, -54264, -3012, 10, 20, 200);
		gcall.Stepto(-50829, -54178, -3012, 10, 20, 200);
		Sleep(500);
		gcall.KeyPress(27);
		Sleep(1000);
		gcall.DeliverQuests(301, taskid, L"남소유");
		Sleep(1000);
		break;
	case 2:
		Sleep(1000);
		gcall.KeyPress(27);
		Sleep(1000);
		gcall.KeyPress(27);
		Sleep(1000);
		gcall.Stepto(-50971, -54328, -3012);
		gcall.Stepto(-51195, -54484, -3035);
		gcall.Stepto(-51497, -54694, -3056);
		Sleep(1000);
		gcall.DeliverQuests(301, taskid, L"고설준");
		Sleep(3000);
		break;
	case 3:
		gcall.Stepto(-51624, -54693, -3057);
		gcall.Stepto(-51916, -54627, -3052);
		gcall.Stepto(-52231, -54719, -3041);
		gcall.Stepto(-52301, -55332, -3067);
		gcall.Stepto(-52511, -55976, -3131);
		gcall.Stepto(-52555, -56457, -3138);
		gcall.Stepto(-52434, -56425, -3136);
		Sleep(3000);
		break;
	case 4:
		gcall.Stepto(-52355, -56369, -3136);
		Sleep(1000);
		gcall.DeliverQuests(301, taskid, L"옥경원");
		Sleep(2000);
		break;
	}
}

void TaskScript::Task_302(int zid,int taskid)
{
	switch (taskid)
	{
	case 1:
		gcall.randXianlu(0);
		gcall.NewSpend(2.5);
		gcall.Stepto(-52156, -56474, -3142);
		gcall.Stepto(-52358, -57077, -3217);
		gcall.Stepto(-52471, -57595, -3227);
		gcall.Stepto(-52786, -57978, -3248);
		gcall.Stepto(-53102, -58250, -3231);
		gcall.Stepto(-53218, -58374, -3225);
		gcall.Stepto(-53313, -58433, -3221);
		gcall.NewSpend(1);
		Sleep(2000);
		
		break;
	case 2:
		gcall.FindThenKill(0, 250, modeNormal | modeAoe | modePickupOnce | modeTask,2,302);
		Sleep(1000);
		break;
	case 3:
		gcall.Stepto(-53112, -59050, -3240);
		gcall.Stepto(-52977, -59632, -3289);
		Sleep(1000);
		gcall.PickupTask(200);
		//Sleep(1000);
		gcall.NewSpend(2.5);
		gcall.Stepto(-52783, -58944, -3256);
		gcall.Stepto(-52641, -58438, -3262);
		gcall.Stepto(-52361, -57723, -3230);
		gcall.Stepto(-52014, -57282, -3210);
		gcall.Stepto(-51725, -57318, -3204);
		gcall.Stepto(-51118, -57476, -3193);
		gcall.Stepto(-50746, -57281, -3159);
		gcall.Stepto(-50809, -56938, -3137);
		gcall.Stepto(-50861, -56564, -3117);
		gcall.Stepto(-50826, -56371, -3114);
		gcall.NewSpend(1);
		Sleep(1000);
		//gcall.DeliverQuests(302, 3, L"곽준", 11,255,0);
		gcall.DeliverQuests(302, 3, L"곽준", 0x0000000b);
		Sleep(1000);
		gcall.NewSpend(2.5);
		gcall.Stepto(-50863, -56554, -3116);
		gcall.Stepto(-50895, -56661, -3120);
		gcall.Stepto(-50927, -56780, -3129);
		gcall.Stepto(-50920, -56904, -3138);
		gcall.Stepto(-50901, -57027, -3143);
		gcall.Stepto(-50852, -57155, -3151);
		gcall.Stepto(-50805, -57270, -3160);
		gcall.Stepto(-50763, -57387, -3165);
		gcall.Stepto(-50720, -57503, -3176);
		gcall.Stepto(-50679, -57620, -3190);
		gcall.Stepto(-50640, -57738, -3193);
		gcall.Stepto(-50611, -57858, -3197);
		gcall.Stepto(-50605, -57982, -3199);
		gcall.Stepto(-50617, -58106, -3204);
		gcall.Stepto(-50650, -58225, -3209);
		gcall.Stepto(-50716, -58330, -3222);
		gcall.Stepto(-50795, -58425, -3234);
		gcall.Stepto(-50875, -58521, -3241);
		gcall.Stepto(-50954, -58616, -3245);
		gcall.Stepto(-51018, -58721, -3248);
		gcall.Stepto(-51067, -58833, -3253);
		gcall.Stepto(-51119, -58946, -3262);
		gcall.Stepto(-51171, -59058, -3271);
		gcall.Stepto(-51223, -59171, -3277);
		gcall.Stepto(-51275, -59284, -3279);
		gcall.Stepto(-51328, -59398, -3282);
		gcall.Stepto(-51379, -59511, -3284);
		gcall.Stepto(-52165, -59457, -3270);
		gcall.Stepto(-52287, -59434, -3271);
		gcall.Stepto(-52405, -59397, -3276);
		gcall.Stepto(-52518, -59344, -3281);
		gcall.Stepto(-52630, -59292, -3285);
		gcall.Stepto(-52743, -59239, -3281);
		gcall.Stepto(-52854, -59185, -3267);
		gcall.NewSpend(1);
		gcall.Stepto(-52965, -59130, -3251);
		break;
	case 4:
		gcall.NewSpend(2.5);
		/*gcall.Stepto(-51338, -59411, -3283);
		gcall.Stepto(-51274, -59277, -3279);
		gcall.Stepto(-51210, -59142, -3276);
		gcall.Stepto(-51145, -59008, -3267);
		gcall.Stepto(-51081, -58874, -3256);
		gcall.Stepto(-51017, -58739, -3248);
		gcall.Stepto(-50953, -58605, -3246);
		gcall.Stepto(-50902, -58498, -3244);
		gcall.Stepto(-50848, -58386, -3235);
		gcall.Stepto(-50795, -58274, -3220);
		gcall.Stepto(-50741, -58162, -3213);
		gcall.Stepto(-50686, -58051, -3206);
		gcall.Stepto(-50632, -57939, -3199);
		gcall.Stepto(-50606, -57820, -3195);
		gcall.Stepto(-50641, -57701, -3192);
		gcall.Stepto(-50682, -57584, -3185);
		gcall.Stepto(-50723, -57467, -3174);
		gcall.Stepto(-50765, -57350, -3161);
		gcall.Stepto(-50806, -57233, -3158);
		gcall.Stepto(-50846, -57116, -3148);
		gcall.Stepto(-50866, -56994, -3141);
		gcall.Stepto(-50867, -56870, -3136);
		gcall.Stepto(-50864, -56746, -3123);
		gcall.Stepto(-50854, -56622, -3118);
		gcall.Stepto(-50839, -56499, -3115);
		gcall.Stepto(-50936, -56668, -3121);
		gcall.Stepto(-51585, -56626, -3141);
		gcall.Stepto(-52244, -56176, -3137);
		gcall.Stepto(-52231, -55402, -3065);
		gcall.Stepto(-52117, -54672, -3045);
		gcall.Stepto(-51326, -54488, -3039);
		gcall.Stepto(-50968, -54356, -3012);
		gcall.Stepto(-50751, -54242, -3012);*/
		gcall.Stepto(-52915, -58987, -3241);
		gcall.Stepto(-52878, -58882, -3243);
		gcall.Stepto(-52837, -58765, -3246);
		gcall.Stepto(-52795, -58648, -3247);
		gcall.Stepto(-52757, -58530, -3250);
		gcall.Stepto(-52719, -58412, -3252);
		gcall.Stepto(-52682, -58294, -3256);
		gcall.Stepto(-52644, -58176, -3258);
		gcall.Stepto(-52607, -58057, -3257);
		gcall.Stepto(-52569, -57939, -3255);
		gcall.Stepto(-52532, -57821, -3247);
		gcall.Stepto(-52494, -57703, -3236);
		gcall.Stepto(-52458, -57584, -3227);
		gcall.Stepto(-52426, -57464, -3225);
		gcall.Stepto(-52397, -57344, -3222);
		gcall.Stepto(-52368, -57223, -3220);
		gcall.Stepto(-52338, -57103, -3218);
		gcall.Stepto(-52309, -56982, -3216);
		gcall.Stepto(-52280, -56862, -3203);
		gcall.Stepto(-52252, -56741, -3186);
		gcall.Stepto(-52239, -56617, -3163);
		gcall.Stepto(-52234, -56494, -3146);
		gcall.Stepto(-52232, -56370, -3138);
		gcall.Stepto(-52236, -56246, -3137);
		gcall.Stepto(-52240, -56122, -3137);
		gcall.Stepto(-52244, -55998, -3137);
		gcall.Stepto(-52249, -55874, -3140);
		gcall.Stepto(-52253, -55750, -3144);
		gcall.Stepto(-52257, -55626, -3145);
		gcall.Stepto(-52260, -55502, -3100);
		gcall.Stepto(-52260, -55378, -3062);
		gcall.Stepto(-52258, -55254, -3058);
		gcall.Stepto(-52257, -55130, -3053);
		gcall.Stepto(-52256, -55006, -3048);
		gcall.Stepto(-52254, -54882, -3043);
		gcall.Stepto(-52253, -54758, -3040);
		gcall.Stepto(-52148, -54705, -3043);
		gcall.Stepto(-52029, -54669, -3047);
		gcall.Stepto(-51910, -54634, -3051);
		gcall.Stepto(-51788, -54611, -3055);
		gcall.Stepto(-51666, -54591, -3054);
		gcall.Stepto(-51544, -54567, -3047);
		gcall.Stepto(-51425, -54533, -3043);
		gcall.Stepto(-51309, -54490, -3039);
		gcall.Stepto(-51194, -54444, -3031);
		gcall.Stepto(-51078, -54400, -3030);
		gcall.Stepto(-50968, -54352, -3012);
		gcall.Stepto(-50867, -54293, -3012);
		gcall.Stepto(-50759, -54231, -3012);
		gcall.NewSpend(1);
		Sleep(15000);
		gcall.DeliverQuests(302,taskid,L"도천풍");
		Sleep(2000);
		break;
	}

}

void TaskScript::Task_303(int zid,int taskid)
{
	switch (taskid)
	{
	case 1:
		Sleep(1000);
		gcall.Stepto(-50948, -54337, -3012);
		gcall.Stepto(-51138, -54438, -3030);
		gcall.Stepto(-51340, -54544, -3042);
		gcall.Stepto(-51552, -54663, -3056);
		Sleep(1000);
		gcall.DeliverQuests(303,taskid, L"고설준");
		Sleep(2000);
		break;
	case 2:
		
		gcall.NewSpend(2.5);
		gcall.Stepto(-51652,-54557,-3052);
		gcall.Stepto(-51889,-54587,-3053);
		gcall.Stepto(-52126,-54653,-3046);
		gcall.Stepto(-52289,-54834,-3040);
		gcall.Stepto(-52316,-55079,-3052);
		gcall.Stepto(-52325,-55327,-3066);
		gcall.Stepto(-52335,-55576,-3131);
		gcall.Stepto(-52344,-55824,-3138);
		gcall.Stepto(-52350,-56049,-3134);
		gcall.Stepto(-52346,-56297,-3136);
		gcall.Stepto(-52336,-56544,-3151);
		gcall.Stepto(-52325,-56797,-3196);
		gcall.Stepto(-52332,-57045,-3217);
		gcall.Stepto(-52375,-57289,-3221);
		gcall.Stepto(-52419,-57533,-3227);
		gcall.Stepto(-52477,-57774,-3242);
		gcall.Stepto(-52632,-57944,-3252);
		gcall.Stepto(-52867,-58026,-3243);
		gcall.Stepto(-53096,-58119,-3232);
		gcall.Stepto(-53319,-58227,-3226);
		gcall.Stepto(-53542,-58337,-3224);
		gcall.Stepto(-53763,-58449,-3226);
		gcall.Stepto(-53983,-58565,-3225);
		gcall.Stepto(-54202,-58681,-3227);
		gcall.Stepto(-54422,-58797,-3229);
		gcall.Stepto(-54641,-58913,-3235);
		gcall.Stepto(-54861,-59028,-3232);
		gcall.Stepto(-55097,-59089,-3251);
		gcall.Stepto(-55340,-59042,-3258);
		gcall.Stepto(-55570,-58949,-3258);
		gcall.Stepto(-55787,-58829,-3257);
		gcall.Stepto(-56000,-58702,-3269);
		gcall.Stepto(-56206,-58564,-3282);
		gcall.Stepto(-56407,-58419,-3275);
		gcall.Stepto(-56608,-58274,-3272);
		gcall.Stepto(-56810,-58129,-3290);
		gcall.Stepto(-57011,-57984,-3299);
		gcall.Stepto(-57212,-57838,-3286);
		gcall.Stepto(-57413,-57693,-3249);
		gcall.Stepto(-57614,-57548,-3226);
		gcall.Stepto(-57820,-57409,-3200);
		gcall.Stepto(-58036,-57287,-3201);
		gcall.Stepto(-58252,-57164,-3214);
		gcall.Stepto(-58458,-57025,-3226);
		gcall.Stepto(-58656,-56877,-3227);
		gcall.Stepto(-58856,-56730,-3225);
		gcall.NewSpend(1);
		gcall.Stepto(-58140, -57880, -3215);
		Sleep(1000);
		gcall.FindThenKill(0, 1000, modeNormal | modeAoe | modePickupOnce | modeTask | modePickup,2,303);
		//gcall.FindThenKill(0, 1000, modeNormal | modeAoe ,2,303);
		Sleep(1000);
		break;
	case 3:
		gcall.NewSpend(2.5);
		gcall.Stepto(-58493, -58224, -3216,10,20,10000);
		gcall.Stepto(-59020, -57931, -3191,10,20,10000);
		gcall.Stepto(-59360, -57612, -3214);
		gcall.Stepto(-59388, -57548, -3216);
		gcall.Stepto(-59487, -57320, -3221);
		gcall.Stepto(-59583, -57093, -3220);
		gcall.Stepto(-59701, -56876, -3209);
		gcall.Stepto(-59812, -56692, -3190);
		gcall.Stepto(-59984, -56412, -3170);
		gcall.Stepto(-60208, -56044, -3171);
		gcall.Stepto(-60425, -55672, -3189);
		gcall.Stepto(-60629, -55286, -3202);
		gcall.Stepto(-60815, -54886, -3175);
		gcall.Stepto(-60988, -54488, -3155);
		gcall.Stepto(-61159, -54094, -3166);
		gcall.Stepto(-61328, -53696, -3175);
		gcall.Stepto(-61414, -53265, -3177);
		gcall.Stepto(-61469, -52835, -3162);
		gcall.Stepto(-61517, -52406, -3151);
		gcall.Stepto(-61486, -51988, -3137);
		gcall.Stepto(-61423, -51688, -3129);
		gcall.Stepto(-61424, -51440, -3122);
		gcall.Stepto(-61448, -51194, -3114);
		gcall.Stepto(-61521, -50959, -3105);
		gcall.Stepto(-61674, -50764, -3101);
		gcall.Stepto(-61886, -50639, -3097);
		gcall.Stepto(-62115, -50536, -3082);
		gcall.Stepto(-62347, -50449, -3066);
		gcall.Stepto(-62584, -50378, -3047);
		gcall.Stepto(-62835, -50350, -3038);
		gcall.Stepto(-63082, -50331, -3040);
		gcall.Stepto(-63330, -50316, -3058);
		gcall.Stepto(-63412, -50314, -3058);
		gcall.Stepto(-63538, -50290, -3055);
		gcall.Stepto(-63643, -50291, -3050);
		gcall.Stepto(-63966, -50297, -3042);
		gcall.Stepto(-64581, -50376, -3113);
		gcall.Stepto(-65079, -50534, -3169);
		gcall.Stepto(-65385, -50856, -3256);
		gcall.Stepto(-65469, -50906, -3256);
		gcall.NewSpend(1);
		Sleep(1000);
		gcall.DeliverQuests(303,taskid, L"고봉");
		Sleep(2000);
		break;
	case 4:
		gcall.Stepto(-63248, -50353, -3052);
		gcall.Stepto(-63420, -50368, -3053, 10, 10, 200);
		gcall.Stepto(-63595, -50384, -3048, 10, 10, 200);
		gcall.Stepto(-63781, -50401, -3052, 10, 10, 200);
		gcall.Stepto(-63966, -50418, -3061, 10, 10, 200);
		gcall.Stepto(-64151, -50434, -3084, 10, 10, 200);
		gcall.Stepto(-64336, -50451, -3116, 10, 10, 200);
		gcall.Stepto(-64521, -50471, -3146, 10, 10, 200);
		gcall.Stepto(-64702, -50512, -3161, 10, 10, 200);
		gcall.Stepto(-64861, -50608, -3183, 10, 10, 200);
		gcall.Stepto(-64994, -50736, -3210, 10, 10, 200);
		gcall.Stepto(-65159, -50792, -3229, 10, 10, 200);
		gcall.Stepto(-65340, -50833, -3251, 10, 10, 200);
		//从NPC走到打怪点

		gcall.Stepto(-65188, -50866, -3239);
		gcall.Stepto(-65035, -50944, -3236);
		gcall.Stepto(-64874, -51037, -3229);
		gcall.Stepto(-64711, -51127, -3236);

		Sleep(1000);
		gcall.FindThenKill(0, 500, modeNormal | modeAoe | modeTask,4);
		Sleep(1000);
		break;
	case 5:
		gcall.Stepto(-63285, -50357, -3053);
		gcall.Stepto(-63484, -50370, -3051, 10, 10, 200);
		gcall.Stepto(-63670, -50383, -3050, 10, 10, 200);
		gcall.Stepto(-63855, -50395, -3053, 10, 10, 200);
		gcall.Stepto(-64041, -50408, -3067, 10, 10, 200);
		gcall.Stepto(-64227, -50420, -3092, 10, 10, 200);
		gcall.Stepto(-64412, -50438, -3126, 10, 10, 200);
		gcall.Stepto(-64596, -50464, -3148, 10, 10, 200);
		gcall.Stepto(-64741, -50570, -3171, 10, 10, 200);
		gcall.Stepto(-64840, -50727, -3187, 10, 10, 200);
		gcall.Stepto(-64895, -50904, -3214, 10, 10, 200);
		gcall.Stepto(-64826, -51045, -3226, 10, 10, 200);


		//从打怪点走到门前

		gcall.Stepto(-64550, -51188, -3246);
		gcall.Stepto(-64656, -51336, -3248);
		gcall.Stepto(-64807, -51444, -3248);
		gcall.Stepto(-64937, -51578, -3252);
		gcall.Stepto(-65047, -51727, -3253);

		gcall.FindThenKill(0, 500, modeNormal | modeAoe | modeTask,5);
		Sleep(1000);
		break;
	case 6:
		
		gcall.Stepto(-63421, -50368, -3053);
		gcall.Stepto(-63580, -50378, -3049, 10, 10, 200);
		gcall.Stepto(-63765, -50397, -3052, 10, 10, 200);
		gcall.Stepto(-63949, -50419, -3060, 10, 10, 200);
		gcall.Stepto(-64133, -50450, -3084, 10, 10, 200);
		gcall.Stepto(-64315, -50487, -3114, 10, 10, 200);
		gcall.Stepto(-64496, -50530, -3141, 10, 10, 200);
		gcall.Stepto(-64677, -50574, -3163, 10, 10, 200);
		gcall.Stepto(-64834, -50670, -3184, 10, 10, 200);
		gcall.Stepto(-64943, -50819, -3213, 10, 10, 200);
		gcall.Stepto(-65021, -50988, -3238, 10, 10, 200);
		gcall.Stepto(-65064, -51169, -3253, 10, 10, 200);
		gcall.Stepto(-65076, -51354, -3259, 10, 10, 200);
		gcall.Stepto(-65071, -51540, -3253, 10, 10, 200);

		
		//从门前打怪点走到门前开门

		gcall.Stepto(-65055, -51726, -3253);
		Sleep(1000);
		gcall.Stepto(-64932, -51707, -3254);
		Sleep(1000);
		gcall.PickupTask(150);
		Sleep(1000);
		break;
	case 7:
		gcall.Stepto(-63344, -50355, -3055);
		gcall.Stepto(-63548, -50365, -3050, 10, 10, 200);
		gcall.Stepto(-63733, -50374, -3051, 10, 10, 200);
		gcall.Stepto(-63919, -50386, -3058, 10, 10, 200);
		gcall.Stepto(-64104, -50404, -3073, 10, 10, 200);
		gcall.Stepto(-64289, -50424, -3103, 10, 10, 200);
		gcall.Stepto(-64472, -50456, -3139, 10, 10, 200);
		gcall.Stepto(-64650, -50509, -3156, 10, 10, 200);
		gcall.Stepto(-64814, -50596, -3179, 10, 10, 200);
		gcall.Stepto(-64943, -50729, -3203, 10, 10, 200);
		gcall.Stepto(-65027, -50894, -3232, 10, 10, 200);
		gcall.Stepto(-65037, -51078, -3248, 10, 10, 200);
		gcall.Stepto(-65010, -51262, -3257, 10, 10, 200);
		gcall.Stepto(-64978, -51445, -3252, 10, 10, 100);
		gcall.Stepto(-64949, -51629, -3254, 10, 10, 50);
		//开门口走到NPC
		Sleep(1000);
		gcall.Stepto(-64858, -51740, -3253);
		Sleep(1000);
		gcall.DeliverQuests(303,taskid,L"도단하");
		Sleep(1000);
		break;
	case 8:
		//NPC走出来

		gcall.Stepto(-63344, -50355, -3055);
		gcall.Stepto(-63548, -50365, -3050, 10, 10, 200);
		gcall.Stepto(-63733, -50374, -3051, 10, 10, 200);
		gcall.Stepto(-63919, -50386, -3058, 10, 10, 200);
		gcall.Stepto(-64104, -50404, -3073, 10, 10, 200);
		gcall.Stepto(-64289, -50424, -3103, 10, 10, 200);
		gcall.Stepto(-64472, -50456, -3139, 10, 10, 200);
		gcall.Stepto(-64650, -50509, -3156, 10, 10, 200);
		gcall.Stepto(-64814, -50596, -3179, 10, 10, 200);
		gcall.Stepto(-64943, -50729, -3203, 10, 10, 200);
		gcall.Stepto(-65027, -50894, -3232, 10, 10, 200);
		gcall.Stepto(-65037, -51078, -3248, 10, 10, 200);
		gcall.Stepto(-65010, -51262, -3257, 10, 10, 200);
		gcall.Stepto(-64978, -51445, -3252, 10, 10, 200);
		gcall.Stepto(-64949, -51629, -3254, 10, 10, 200);
		gcall.Stepto(-65125, -51619, -3252);
		gcall.Stepto(-65070, -51781, -3252);
		gcall.Stepto(-65020, -51960, -3251);
		gcall.Stepto(-65169, -52070, -3247);
		gcall.Stepto(-65349, -52118, -3244);
		Sleep(1000);
		gcall.PickupTask(150);
		Sleep(15000);
		break;
	case 9:
		//NPC走出来

		gcall.Stepto(-63344, -50355, -3055);
		gcall.Stepto(-63263, -50339, -3053, 10, 10, 200);
		gcall.Stepto(-63423, -50344, -3055, 10, 10, 200);
		gcall.Stepto(-63609, -50354, -3051, 10, 10, 200);
		gcall.Stepto(-63794, -50372, -3053, 10, 10, 200);
		gcall.Stepto(-63978, -50398, -3059, 10, 10, 200);
		gcall.Stepto(-64162, -50425, -3084, 10, 10, 200);
		gcall.Stepto(-64344, -50464, -3118, 10, 10, 200);
		gcall.Stepto(-64525, -50506, -3145, 10, 10, 200);
		gcall.Stepto(-64706, -50549, -3165, 10, 10, 200);
		gcall.Stepto(-64862, -50648, -3186, 10, 10, 200);
		gcall.Stepto(-64972, -50795, -3216, 10, 10, 200);
		gcall.Stepto(-65000, -50978, -3236, 10, 10, 200);
		gcall.Stepto(-64999, -51164, -3252, 10, 10, 200);
		gcall.Stepto(-65001, -51350, -3257, 10, 10, 200);
		gcall.Stepto(-65005, -51536, -3253, 10, 10, 200);
		gcall.Stepto(-65015, -51722, -3253, 10, 10, 200);
		gcall.Stepto(-65033, -51907, -3252, 10, 10, 200);
		gcall.Stepto(-65053, -52092, -3244, 10, 10, 200);

		gcall.Stepto(-65172, -52244, -3238);
		gcall.Stepto(-65335, -52334, -3252);
		Sleep(2000);
		gcall.FindThenKill(0, 1000, modeNormal | modeAoe | modePickup);
		Sleep(1000);
		gcall.Stepto(-65437, -52250, -3262);
		Sleep(1000);
		gcall.Stepto(L"도단하");
		Sleep(500);
		gcall.DeliverQuests(303,taskid,L"도단하");
		
		break;
	case 10:
		Sleep(2000);
		gcall.CityConvey(1);
		Sleep(5000);
		gcall.WaitPlans();
		Sleep(2000);
		break;
	case 11:

		gcall.Stepto(-48903, -49643, -2378);
		gcall.Stepto(-48890, -49928, -2378);
		Sleep(1000);
		gcall.DeliverQuests(303, 0xb, L"고봉");
		Sleep(1000);
		break;
	case 12:
		gcall.NewSpend(2.5);
		Sleep(1000);
		gcall.Stepto(-49130, -49655, -2382);
		gcall.Stepto(-49673, -49564, -2386);
		gcall.Stepto(-50484, -49319, -2376);
		gcall.Stepto(-50873, -49109, -2346);
		gcall.Stepto(-50969, -48379, -2361);
		gcall.Stepto(-51551, -48169, -2362);
		gcall.Stepto(-52114, -48476, -2423);
		gcall.Stepto(-52467, -48808, -2610);
		gcall.Stepto(-52717, -48997, -2685);
		gcall.Stepto(-53149, -49092, -2665);
		gcall.Stepto(-53653, -49252, -2657);
		gcall.Stepto(-54233, -49620, -2702);
		gcall.Stepto(-54864, -50075, -2686);
		gcall.Stepto(-55346, -50354, -2646);
		gcall.Stepto(-55637, -50286, -2576);
		gcall.Stepto(-55891, -50194, -2539);
		gcall.Stepto(-56115, -50123, -2539);
		gcall.Stepto(-56089, -49929, -2539);
		gcall.NewSpend(1);
		Sleep(500);
		gcall.DeliverQuests(303, 0xc, L"도천풍");
		Sleep(10000);
		break;
	}
}

void TaskScript::Task_497(int zid,int taskid)
{
	switch (taskid)
	{
	case 1:
		gcall.DeliverQuests(497, taskid, L"남소유");
		Sleep(1000);
		break;
	case 2:
		gcall.DeliverQuests(497, 2, 0,1,0,1);
		Sleep(1000);
		gcall.NewBag();
		Sleep(6000);
		break;
	case 3:
		gcall.DeliverQuests(497, taskid, L"남소유");
		Sleep(1000);
		break;
	}
}
void TaskScript::Task_304(int zid,int taskid)
{
	switch (taskid)
	{
	case 1:
		gcall.NewSpend(2.5);
		Sleep(1000);
		gcall.Stepto(-56082, -50123, -2539);
		gcall.Stepto(-55741, -50245, -2576);
		gcall.Stepto(-55498, -50317, -2588);
		gcall.Stepto(-55043, -50360, -2687);
		gcall.Stepto(-54542, -50446, -2650);
		gcall.Stepto(-54321, -50467, -2611);
		gcall.Stepto(-53996, -50461, -2525);
		gcall.Stepto(-53781, -50473, -2525);
		gcall.NewSpend(1);
		Sleep(1000);
		gcall.DeliverQuests(304,taskid, L"곽대규");
		Sleep(1000);
		
		break;
	case 2:
		gcall.NewSpend(2.5);
		Sleep(1000);
		gcall.Stepto(-54066, -50475, -2541);
		gcall.Stepto(-54336, -50473, -2610);
		gcall.Stepto(-54513, -50472, -2641);
		gcall.Stepto(-54940, -50471, -2689);
		gcall.Stepto(-55396, -51015, -2681);
		gcall.Stepto(-55498, -51218, -2668);
		gcall.NewSpend(1);
		Sleep(1000);
		/*支线任务*/
		gcall.NPCJieRenWu(6, 0x40070, 0x551, 0, 0);
		Sleep(1000);
		gcall.NPCJieRenWu(6, 0x40070, 0x141, 0, 0);
		Sleep(1000);
		gcall.DeliverQuests(0x141, 1, 0, 0, 0, 1);
		Sleep(1000);
		gcall.DeliverQuests(0x141, 2, 0, 0, 0, 1);
		Sleep(1000);
		gcall.DeliverQuests(0x141, 3, 0, 0, 0, 1);
		Sleep(1000);
		gcall.DeliverQuests(0x141, 4, 0, 0, 0, 1);
		Sleep(1000);
		gcall.DeliverQuests(0x551, 1, 0, 0, 0, 1);
		Sleep(1000);
		gcall.DeliverQuests(0x551, 2, 0, 1);
		Sleep(1000);
		/*支线任务结束*/

		gcall.Stepto(-55027, -51563, -2696);
		gcall.Stepto(-54728, -51878, -2663);
		Sleep(1000);
		gcall.NPCJieRenWu(3, 0x40070, 0x142, 0, 0);
		Sleep(1000);
		gcall.Stepto(-54493, -51651, -2699,10,20,2000);
		gcall.Stepto(-54314, -51487, -2691,10,20,2000);
		//Sleep(500);
		//gcall.NPCJieRenWu(4, 0x40070, 0x145, 0, 0);//这个任务没了。

		//Sleep(1000);
		gcall.NewSpend(2.5);
		gcall.Stepto(-53906, -51759, -2696,10,20,2000);
		gcall.Stepto(-53194, -51861, -2713,10,20,2000);
		gcall.Stepto(-52313, -52215, -2683,10,20,2000);
		gcall.Stepto(-52254, -52698, -2695,10,20,2000);
		gcall.Stepto(-52230, -53469, -2939,10,20,2000);
		gcall.Stepto(-52127, -54449, -3051,10,20,2000);
		gcall.Stepto(-51541, -54664, -3056,10,20,2000);
		gcall.Stepto(-51074, -54863, -3051,10,20,2000);
		gcall.Stepto(-50549, -55032, -3022,10,20,2000);
		gcall.NewSpend(1);
		gcall.Stepto(-50451, -54997, -3022,10,20,2000);
		Sleep(2000);
		gcall.DeliverQuests(0x141, 5, L"장호엄");
		Sleep(1000);
		gcall.NewSpend(2.5);
		gcall.Stepto(-50801, -54914, -3041,10,20,2000);
		gcall.Stepto(-51127, -54696, -3049,10,20,2000);
		gcall.Stepto(-51180, -54431, -3030,10,20,2000);
		gcall.Stepto(-50962, -54353, -3012,10,20,2000);
		gcall.Stepto(-50762, -54238, -3012,10,20,2000);
		gcall.Stepto(-50534, -54127, -2988,10,20,2000);
		gcall.NewSpend(1);
		Sleep(1000);
		gcall.DeliverQuests(304,taskid, L"곽준");
		Sleep(1000);
		
		break;
	case 3:
		Sleep(1000);
		gcall.Stepto(-50720, -54076, -3012);
		gcall.Stepto(-50788, -53991, -2980);
		Sleep(1000);
		gcall.DeliverQuests(304,taskid, L"곽칠");
		Sleep(1000);
		break;
	case 4:
		gcall.Stepto(-50643, -54114, -3012);
		gcall.Stepto(-50509, -54148, -2988);
		Sleep(1000);
		gcall.DeliverQuests(304,taskid, L"곽준");
		Sleep(1000);
		

		//可能会卡顿，穿装备时需要判断下是否装备上。最多执行3次

		while(true)
		{
			int flag;
			flag = 0;
			std::vector<_BAGSTU> EquiVec;
			gcall.GetAllBodyEquipToVector(EquiVec);

			for (int i=0; i < EquiVec.size();i++)
			{
				if (EquiVec[i].m_Type == 1)
				{
					if (wcscmp(EquiVec[i].name, L"홍문도끼 1단계") == 0)
					{
						flag = 1;
					}
					break;
				}
			}
			
			if (flag == 1)
			{
				break;
			}else
			{
				gcall.WearEquipment(L"홍문도끼 1단계", 1);
				Sleep(1000);
			}
			Sleep(100);
		}
		
		Sleep(1000);
		gcall.HeChengWuQiByHun(EQUITMENT_POS::WUQI);
		Sleep(1000);
		break;
	case 5:
		gcall.NewSpend(2.5);
		gcall.Stepto(-50631, -54188, -3012);
		gcall.Stepto(-50706, -54222, -3012);
		gcall.Stepto(-50928, -54332, -3012);
		gcall.Stepto(-51009, -54372, -3021);
		gcall.Stepto(-51139, -54438, -3030);
		gcall.Stepto(-51362, -54550, -3043);
		gcall.Stepto(-51591, -54633, -3054);
		gcall.Stepto(-51833, -54694, -3053);
		gcall.Stepto(-52070, -54767, -3043);
		gcall.Stepto(-52206, -54968, -3045);
		gcall.Stepto(-52207, -55211, -3054);
		gcall.Stepto(-52181, -55459, -3082);
		gcall.Stepto(-52155, -55705, -3144);
		gcall.Stepto(-52129, -55952, -3139);
		gcall.Stepto(-52124, -56202, -3137);
		gcall.Stepto(-52145, -56449, -3140);
		gcall.Stepto(-52167, -56696, -3172);
		gcall.Stepto(-52190, -56939, -3207);
		gcall.Stepto(-52213, -57187, -3219);
		gcall.randXianlu(0);
		gcall.Stepto(-52236, -57435, -3226);
		gcall.Stepto(-52253, -57682, -3225);
		gcall.Stepto(-52234, -57930, -3247);
		gcall.Stepto(-52223, -58179, -3250);
		gcall.Stepto(-52213, -58427, -3258);
		gcall.Stepto(-52209, -58516, -3263);
		gcall.NewSpend(1);
		Sleep(1000);
		gcall.FindThenKill(0, 400, modeNormal | modeAoe | modePickup);
		gcall.NewSpend(2.5);
		gcall.Stepto(-52208, -58519, -3263);
		gcall.Stepto(-52027, -58674, -3259);
		gcall.Stepto(-51804, -58784, -3273);
		gcall.Stepto(-51581, -58895, -3283);
		gcall.Stepto(-51360, -59004, -3275);
		gcall.Stepto(-51139, -59119, -3274);
		gcall.Stepto(-50919, -59234, -3274);
		gcall.Stepto(-50717, -59342, -3273);
		gcall.Stepto(-50717, -59343, -3273);
		gcall.NewSpend(1);
		gcall.FindThenKill(0, 400, modeNormal | modeAoe | modePickup);
		gcall.NewSpend(2.5);
		gcall.Stepto(-50657, -59441, -3276);
		gcall.Stepto(-50547, -59663, -3271);
		gcall.Stepto(-50396, -59859, -3267);
		gcall.Stepto(-50193, -60004, -3268);
		gcall.Stepto(-49998, -60157, -3286);
		gcall.Stepto(-49803, -60310, -3301);
		gcall.Stepto(-49781, -60327, -3302);
		gcall.NewSpend(1);
		gcall.FindThenKill(0, 400, modeNormal | modeAoe | modePickup);
		gcall.NewSpend(2.5);
		gcall.Stepto(-49819, -60343, -3301);
		gcall.Stepto(-50007, -60502, -3299);
		gcall.Stepto(-50182, -60677, -3304);
		gcall.Stepto(-50360, -60849, -3312);
		gcall.Stepto(-50539, -61021, -3317);
		gcall.Stepto(-50651, -61129, -3319);
		gcall.NewSpend(1);
		gcall.FindThenKill(0, 400, modeNormal | modeAoe | modePickup);
		gcall.NewSpend(2.5);
		gcall.Stepto(-50714, -61065, -3311);
		gcall.Stepto(-50923, -60936, -3305);
		gcall.Stepto(-51138, -60811, -3300);
		gcall.Stepto(-51352, -60686, -3319);
		gcall.Stepto(-51507, -60595, -3332);
		gcall.NewSpend(1);
		gcall.FindThenKill(0, 400, modeNormal | modeAoe | modePickup);
		gcall.NewSpend(2.5);
		gcall.Stepto(-51516, -60689, -3324);
		gcall.Stepto(-51541, -60934, -3325);
		gcall.Stepto(-51572, -61180, -3331);
		gcall.Stepto(-51590, -61322, -3337);
		gcall.NewSpend(1);
		gcall.FindThenKill(0, 400, modeNormal | modeAoe | modePickup);
		gcall.NewSpend(2.5);
		gcall.Stepto(-51620, -61275, -3335);
		gcall.Stepto(-51626, -61285, -3336);
		gcall.Stepto(-51694, -61396, -3343);
		gcall.NewSpend(1);
		Sleep(1000);
		gcall.PickupTask();
		gcall.NewSpend(2.5);
		gcall.Stepto(-51692, -61392, -3343);
		gcall.Stepto(-51720, -61375, -3341);
		gcall.Stepto(-51920, -61229, -3339);
		gcall.Stepto(-52107, -61067, -3336);
		gcall.Stepto(-52294, -60904, -3328);
		gcall.Stepto(-52442, -60774, -3324);
		gcall.NewSpend(1);
		gcall.FindThenKill(0, 400, modeNormal | modeAoe | modePickup);
		gcall.NewSpend(2.5);
		gcall.Stepto(-52467, -60848, -3325);
		gcall.Stepto(-52546, -61083, -3332);
		gcall.Stepto(-52625, -61318, -3342);
		gcall.Stepto(-52642, -61368, -3345);
		gcall.NewSpend(1);
		Sleep(1000);
		gcall.PickupTask();

		gcall.Stepto(-52711, -61365, -3346);
		gcall.Stepto(-52792, -61166, -3336);
		gcall.Stepto(-52890, -60939, -3330);
		gcall.Stepto(-52945, -60812, -3318);
		Sleep(1000);
		gcall.PickupTask();
		gcall.Stepto(-53065, -60747, -3315);
		gcall.Stepto(-53292, -60647, -3314);
		gcall.Stepto(-53525, -60562, -3319);
		gcall.Stepto(-53755, -60479, -3324);
		gcall.Stepto(-53989, -60395, -3323);
		gcall.Stepto(-54225, -60326, -3321);
		gcall.Stepto(-54433, -60246, -3321);
		gcall.Stepto(-54458, -60180, -3316);

		gcall.NewSpend(1);
		Sleep(1000);
		gcall.FindThenKill(0, 1000, modeNormal | modeAoe | modeGoback | modePickupOnce | modeTask |modePickup,5);
		Sleep(1000);
		
		break;
	case 6:
		gcall.Stepto(-53830, -60057, -3298,10,20,5000);
		gcall.NewSpend(2.5);
		gcall.Stepto(-54066, -60133, -3308,10,20,5000);
		gcall.Stepto(-54303, -60205, -3316,10,20,5000);
		gcall.Stepto(-54545, -60262, -3324,10,20,5000);
		gcall.Stepto(-54787, -60313, -3328,10,20,5000);
		gcall.Stepto(-55027, -60322, -3328,10,20,5000);
		gcall.Stepto(-55284, -60317, -3329,10,20,5000);
		gcall.Stepto(-55532, -60319, -3329,10,20,5000);
		gcall.Stepto(-55776, -60297, -3329,10,20,5000);
		gcall.Stepto(-55844, -60291, -3329,10,20,5000);
		gcall.NewSpend(1);
		Sleep(1000);
		gcall.PickupTask(1500,322,1);
		gcall.Stepto(-56004, -60166, -3323,20,20,5000);
		gcall.Stepto(-55996, -59942, -3317,20,20,5000);
		gcall.NewSpend(2.5);
		gcall.Stepto(-55782, -59810, -3320);
		gcall.Stepto(-55570, -59682, -3319);
		gcall.Stepto(-55358, -59553, -3312);
		gcall.Stepto(-55123, -59551, -3310);
		gcall.Stepto(-54887, -59618, -3311);
		gcall.Stepto(-54649, -59687, -3308);
		gcall.Stepto(-54414, -59765, -3299);
		gcall.Stepto(-54180, -59846, -3287);
		gcall.Stepto(-53944, -59928, -3291);
		gcall.Stepto(-53710, -60009, -3295);
		gcall.Stepto(-53465, -60040, -3293);
		gcall.Stepto(-53231, -59966, -3293);
		gcall.Stepto(-53070, -59782, -3292);
		gcall.Stepto(-52962, -59558, -3287);
		gcall.Stepto(-52869, -59329, -3278);
		gcall.Stepto(-52793, -59092, -3264);
		gcall.Stepto(-52718, -58855, -3263);
		gcall.Stepto(-52645, -58624, -3268);
		gcall.Stepto(-52573, -58382, -3265);
		gcall.Stepto(-52516, -58140, -3262);
		gcall.Stepto(-52468, -57937, -3251);
		gcall.Stepto(-52455, -57869, -3246);
		gcall.Stepto(-52407, -57625, -3230);
		gcall.Stepto(-52361, -57390, -3224);
		gcall.Stepto(-52314, -57146, -3220);
		gcall.Stepto(-52266, -56903, -3207);
		gcall.Stepto(-52236, -56746, -3185);
		gcall.Stepto(-52215, -56506, -3147);
		gcall.Stepto(-52196, -56263, -3137);
		gcall.Stepto(-52177, -56013, -3138);
		gcall.Stepto(-52162, -55765, -3143);
		gcall.Stepto(-52147, -55517, -3107);
		gcall.Stepto(-52133, -55269, -3060);
		gcall.Stepto(-52129, -55023, -3047);
		gcall.Stepto(-52130, -54773, -3042);
		gcall.Stepto(-52119, -54713, -3043);
		gcall.Stepto(-51883, -54637, -3052);
		gcall.Stepto(-51642, -54576, -3052);
		gcall.Stepto(-51396, -54531, -3042);
		gcall.Stepto(-51283, -54497, -3038);
		gcall.Stepto(-51057, -54399, -3031);
		gcall.Stepto(-50964, -54354, -3012);
		gcall.Stepto(-50844, -54294, -3012);
		gcall.Stepto(-50624, -54180, -3012);
		gcall.NewSpend(1);
		gcall.Stepto(-50567, -54150, -3012);
		Sleep(1000);
		gcall.DeliverQuests(304,taskid, L"곽준");
		Sleep(1000);
		break;
	case 7:
		gcall.NewSpend(2.5);
		gcall.Stepto(-51003, -54389, -3022,10,20,2000);
		gcall.Stepto(-51338, -54526, -3041,10,20,2000);
		gcall.Stepto(-51873, -54531, -3054,10,20,2000);
		gcall.Stepto(-52178, -54011, -3037,10,20,2000);
		gcall.Stepto(-52194, -53110, -2826,10,20,2000);
		gcall.Stepto(-52272, -52330, -2677,10,20,2000);
		gcall.Stepto(-52383, -51933, -2710,10,20,2000);
		gcall.Stepto(-53169, -51828, -2723,10,20,2000);
		gcall.Stepto(-53767, -51724, -2693,10,20,2000);
		gcall.Stepto(-54154, -51761, -2698,10,20,2000);
		gcall.Stepto(-54620, -51806, -2684,10,20,2000);
		gcall.Stepto(-54747, -51886, -2661,10,20,2000);
		gcall.NewSpend(1);
		Sleep(1000);
		gcall.DeliverQuests(0x142,2, L"한미백");
		Sleep(1000);
		gcall.DeliverQuests(322,3,NULL,0,0,1);
		Sleep(1000);
		gcall.DeliverQuests(322,4,L"한미백");
		Sleep(1000);
		gcall.NewSpend(2.5);
		Sleep(1000);
		gcall.Stepto(-54802, -51763, -2676);
		gcall.Stepto(-54850, -51665, -2688);
		gcall.Stepto(-54903, -51553, -2703);
		gcall.Stepto(-54956, -51441, -2707);
		gcall.Stepto(-55009, -51329, -2706);
		gcall.Stepto(-55062, -51217, -2705);
		gcall.Stepto(-55115, -51105, -2705);
		gcall.Stepto(-55168, -50993, -2702);
		gcall.Stepto(-55221, -50881, -2699);
		gcall.Stepto(-55275, -50769, -2689);
		gcall.Stepto(-55328, -50657, -2675);
		gcall.Stepto(-55381, -50545, -2655);
		gcall.Stepto(-55434, -50432, -2629);
		gcall.Stepto(-55485, -50325, -2593);
		gcall.Stepto(-55592, -50289, -2576);
		gcall.Stepto(-55711, -50252, -2576);
		gcall.Stepto(-55830, -50214, -2540);
		gcall.Stepto(-55961, -50173, -2539);
		gcall.Stepto(-56081, -50137, -2539);
		gcall.Stepto(-56130, -50006, -2539);
		gcall.Stepto(-56104, -49893, -2539);
		gcall.NewSpend(1);
		gcall.DeliverQuests(304, taskid, L"도천풍");
		Sleep(1000);
		break;
	case 8:
		gcall.DeliverQuests(304,taskid, NULL, 1,0, 1);
		Sleep(1000);
		break;
	case 9:
		gcall.DeliverQuests(304, taskid, L"도천풍");
		gcall.NewBag();
		Sleep(5000);
		break;
	case 10:
		gcall.NewSpend(2.5);
		gcall.Stepto(-56089, -50109, -2539);
		gcall.Stepto(-55886, -50178, -2539);
		gcall.Stepto(-55677, -50242, -2576);
		gcall.Stepto(-55625, -50257, -2576);
		gcall.Stepto(-55392, -50324, -2635);
		gcall.Stepto(-55349, -50336, -2644);
		gcall.Stepto(-55157, -50230, -2669);
		gcall.Stepto(-54956, -50084, -2683);
		gcall.Stepto(-54764, -49953, -2688);
		gcall.Stepto(-54569, -49819, -2693);
		gcall.Stepto(-54277, -49623, -2700);
		gcall.Stepto(-53913, -49381, -2672);
		gcall.Stepto(-53666, -49230, -2653);
		gcall.Stepto(-53632, -49221, -2655);
		gcall.Stepto(-53218, -49103, -2671);
		gcall.Stepto(-52791, -48998, -2674);
		gcall.Stepto(-52593, -48949, -2680);
		gcall.Stepto(-52520, -48887, -2646);
		gcall.Stepto(-52197, -48597, -2455);
		gcall.Stepto(-51885, -48317, -2390);
		gcall.Stepto(-51715, -48178, -2369);
		gcall.Stepto(-51535, -47979, -2342);
		gcall.Stepto(-51448, -47693, -2301);
		gcall.Stepto(-51393, -47441, -2268);
		gcall.NewSpend(1);
		Sleep(5000);
		gcall.Stepto(-51339, -47216, -2258);
		gcall.WaitPlans();
		gcall.Stepto(-51271, -47025, -2249);
		gcall.WaitPlans();
		gcall.Stepto(-51127, -46616, -2211);
		gcall.NewSpend(2.5);
		gcall.Stepto(-51064, -46385, -2214);
		gcall.Stepto(-51006, -46144, -2222);
		gcall.Stepto(-50869, -45903, -2234);
		gcall.Stepto(-50544, -45614, -2237);
		gcall.Stepto(-50361, -45563, -2236);
		gcall.Stepto(-49949, -45437, -2239);
		gcall.Stepto(-49657, -45281, -2243);
		gcall.Stepto(-49490, -45027, -2250);
		gcall.Stepto(-49323, -44679, -2247);
		gcall.Stepto(-49324, -44626, -2247);
		gcall.Stepto(-49334, -44184, -2239);
		gcall.Stepto(-49441, -43850, -2231);
		gcall.Stepto(-49632, -43664, -2222);
		gcall.Stepto(-49807, -43599, -2200);
		gcall.Stepto(-50158, -43505, -2196);
		gcall.Stepto(-50396, -43442, -2187);
		gcall.Stepto(-50550, -43400, -2191);
		gcall.Stepto(-50664, -43363, -2195);
		gcall.Stepto(-50898, -43289, -2191);
		gcall.Stepto(-51136, -43207, -2187);
		gcall.Stepto(-51364, -43121, -2184);
		gcall.Stepto(-51597, -43016, -2173);
		gcall.Stepto(-51751, -42844, -2182);
		gcall.Stepto(-51831, -42625, -2189);
		gcall.Stepto(-51814, -42359, -2196);
		gcall.Stepto(-51748, -42114, -2202);
		gcall.Stepto(-51649, -41884, -2218);
		gcall.Stepto(-51538, -41662, -2223);
		gcall.Stepto(-51418, -41443, -2237);
		gcall.NewSpend(1);
		Sleep(5000);
		gcall.Stepto(-51371, -41358, -2243);
		gcall.WaitPlans();
		gcall.Stepto(-51346, -41321, -2241);
		gcall.WaitPlans();
		gcall.Stepto(-51093, -40956, -2234);
		gcall.NewSpend(2.5);
		gcall.Stepto(-50856, -40596, -2238);
		gcall.Stepto(-50731, -40391, -2237);
		gcall.Stepto(-50527, -40001, -2242);
		gcall.Stepto(-50421, -39723, -2247);
		gcall.Stepto(-50329, -39349, -2266);
		gcall.Stepto(-50223, -38922, -2275);
		gcall.Stepto(-50117, -38501, -2264);
		gcall.Stepto(-50011, -38077, -2253);
		gcall.Stepto(-49956, -37856, -2247);
		gcall.Stepto(-50034, -37509, -2235);
		gcall.Stepto(-50124, -37088, -2183);
		gcall.Stepto(-50210, -36658, -2129);
		gcall.Stepto(-50237, -36435, -2150);
		gcall.Stepto(-50274, -36099, -2159);
		gcall.Stepto(-50302, -35849, -2174);
		gcall.Stepto(-50330, -35600, -2181);
		gcall.Stepto(-50358, -35350, -2207);
		gcall.Stepto(-50385, -35103, -2238);
		gcall.Stepto(-50413, -34857, -2271);
		gcall.Stepto(-50441, -34607, -2297);
		gcall.Stepto(-50469, -34358, -2285);
		gcall.Stepto(-50497, -34108, -2276);
		gcall.Stepto(-50525, -33861, -2267);
		gcall.Stepto(-50552, -33611, -2241);
		gcall.Stepto(-50586, -33363, -2230);
		gcall.Stepto(-50653, -32930, -2212);
		gcall.Stepto(-50721, -32502, -2155);
		gcall.Stepto(-50760, -32255, -2094);
		gcall.Stepto(-50846, -31931, -1976);
		gcall.Stepto(-50828, -31617, -1943);
		gcall.Stepto(-50640, -31379, -1944);
		gcall.Stepto(-50319, -31450, -1963);
		gcall.NewSpend(1);
		Sleep(1000);
		gcall.DeliverQuests(304,0xA,L"공삼식");
		Sleep(1000);
		break;
	}

}

void TaskScript::Task_305(int zid,int taskid)
{
	switch (taskid)
	{
	case 1:
		gcall.NewSpend(2.5);
		gcall.Stepto(-50772, -31235, -1944);
		gcall.Stepto(-50766, -31313, -1944);
		gcall.Stepto(-50747, -31560, -1944);
		gcall.Stepto(-50728, -31807, -1966);
		gcall.Stepto(-50710, -32056, -2031);
		gcall.Stepto(-50690, -32304, -2121);
		gcall.Stepto(-50672, -32550, -2169);
		gcall.Stepto(-50652, -32797, -2199);
		gcall.Stepto(-50633, -33044, -2223);
		gcall.Stepto(-50618, -33292, -2230);
		gcall.Stepto(-50610, -33536, -2234);
		gcall.Stepto(-50658, -33784, -2240);
		gcall.Stepto(-50721, -34022, -2255);
		gcall.Stepto(-50783, -34262, -2265);
		gcall.Stepto(-50910, -34473, -2266);
		gcall.Stepto(-51056, -34674, -2274);
		gcall.Stepto(-51192, -34881, -2284);
		gcall.Stepto(-51326, -35086, -2290);
		gcall.Stepto(-51508, -35254, -2300);
		gcall.Stepto(-51742, -35329, -2308);
		gcall.Stepto(-51989, -35344, -2318);
		gcall.Stepto(-52236, -35327, -2316);
		gcall.Stepto(-52484, -35310, -2302);
		gcall.Stepto(-52734, -35293, -2283);
		gcall.Stepto(-52981, -35276, -2260);
		gcall.Stepto(-53229, -35277, -2235);
		gcall.Stepto(-53477, -35285, -2201);
		gcall.Stepto(-53725, -35287, -2168);
		gcall.Stepto(-53974, -35295, -2171);
		gcall.Stepto(-54218, -35295, -2332);
		gcall.Stepto(-54470, -35293, -2508);
		gcall.Stepto(-54714, -35339, -2629);
		gcall.Stepto(-54954, -35392, -2692);
		gcall.Stepto(-55184, -35307, -2784);
		gcall.Stepto(-55357, -35131, -2838);
		gcall.Stepto(-55479, -34918, -2855);
		gcall.Stepto(-55528, -34675, -2900);
		gcall.Stepto(-55470, -34436, -2926);
		gcall.Stepto(-55319, -34239, -2931);
		gcall.Stepto(-55134, -34075, -2925);
		gcall.Stepto(-54905, -34023, -2964);
		gcall.Stepto(-54699, -34160, -3063);
		gcall.Stepto(-54525, -34338, -3161);
		gcall.Stepto(-54413, -34558, -3207);
		gcall.Stepto(-54355, -34799, -3270);
		gcall.Stepto(-54357, -35044, -3347);
		gcall.Stepto(-54490, -35252, -3419);
		gcall.Stepto(-54678, -35414, -3470);
		gcall.Stepto(-54908, -35382, -3501);
		gcall.Stepto(-55126, -35263, -3593);
		gcall.Stepto(-55304, -35098, -3674);
		gcall.Stepto(-55369, -34859, -3801);
		gcall.Stepto(-55358, -34611, -3861);
		gcall.Stepto(-55225, -34407, -3863);
		gcall.Stepto(-55044, -34238, -3861);
		gcall.Stepto(-54852, -34081, -3853);
		gcall.Stepto(-54680, -33904, -3857);
		gcall.Stepto(-54580, -33681, -3864);
		gcall.Stepto(-54555, -33625, -3864);
		gcall.Stepto(-54430, -33408, -3863);
		gcall.Stepto(-54246, -33254, -3863);
		gcall.Stepto(-54004, -33185, -3864);
		gcall.Stepto(-53757, -33155, -3865);
		gcall.Stepto(-53511, -33137, -3870);
		gcall.Stepto(-53479, -33135, -3871);
		gcall.NewSpend(1);
		Sleep(1000);
		gcall.DeliverQuests(305,taskid, L"곽대규");
		Sleep(1000);
		break;
	case 2:
		//gcall.NewSpend(2.5);
		//gcall.Stepto(-53473, -33136, -3871);
		//gcall.Stepto(-53583, -33119, -3869);
		//gcall.Stepto(-53833, -33083, -3869);
		//gcall.Stepto(-54076, -33085, -3870);
		//gcall.Stepto(-54312, -33157, -3868);
		//gcall.Stepto(-54493, -33324, -3867);
		//gcall.Stepto(-54605, -33543, -3866);
		//gcall.Stepto(-54645, -33712, -3862);
		//gcall.Stepto(-54672, -33832, -3859);
		//gcall.Stepto(-54710, -33996, -3857);
		//gcall.Stepto(-54880, -34143, -3858);
		//gcall.Stepto(-55062, -34307, -3861);
		//gcall.Stepto(-55235, -34488, -3863);
		//gcall.Stepto(-55381, -34686, -3854);
		//gcall.Stepto(-55394, -34770, -3831);
		//gcall.Stepto(-55408, -34986, -3737);
		//gcall.Stepto(-55386, -35009, -3727);
		//gcall.Stepto(-55211, -35189, -3624);
		//gcall.Stepto(-55044, -35360, -3528);
		//gcall.Stepto(-54897, -35512, -3464);
		//gcall.Stepto(-54800, -35475, -3474);
		//gcall.Stepto(-54675, -35428, -3468);
		//gcall.Stepto(-54585, -35329, -3452);
		//gcall.Stepto(-54418, -35142, -3378);
		//gcall.Stepto(-54273, -34980, -3310);
		//gcall.Stepto(-54290, -34920, -3297);
		//gcall.Stepto(-54363, -34682, -3240);
		//gcall.Stepto(-54436, -34446, -3179);
		//gcall.Stepto(-54479, -34307, -3157);
		//gcall.Stepto(-54560, -34254, -3145);
		//gcall.Stepto(-54776, -34114, -3006);
		//gcall.Stepto(-54882, -34045, -2974);
		//gcall.Stepto(-54901, -34049, -2971);
		//gcall.Stepto(-55142, -34108, -2925);
		//gcall.Stepto(-55199, -34122, -2918);
		//gcall.Stepto(-55262, -34199, -2916);
		//gcall.Stepto(-55416, -34394, -2938);
		//gcall.Stepto(-55555, -34572, -2908);
		//gcall.NewSpend(1);
		//gcall.Stepto(-55547, -34635, -2906);
		//gcall.Stepto(-55533, -34741, -2896);
		//gcall.Stepto(-55493, -34984, -2834);
		//gcall.Stepto(-55490, -34991, -2832);
		//gcall.Stepto(-55321, -35169, -2833);
		//gcall.Stepto(-55150, -35348, -2766);
		//gcall.Stepto(-55071, -35431, -2729);
		//gcall.Stepto(-55011, -35417, -2713);
		//gcall.Stepto(-54786, -35363, -2655);
		//gcall.Stepto(-54785, -35363, -2655);
		//gcall.Stepto(-54570, -35266, -2562);
		//gcall.Stepto(-54471, -35221, -2509);
		//gcall.Stepto(-54361, -35216, -2441);
		//gcall.Stepto(-54259, -35212, -2377);
		//gcall.Stepto(-54180, -35283, -2307);
		//gcall.Stepto(-54145, -35312, -2274);
		//gcall.Stepto(-54129, -35325, -2254);
		//gcall.Stepto(-54020, -35319, -2191);
		//gcall.Stepto(-53772, -35305, -2166);
		//gcall.Stepto(-53525, -35291, -2194);
		//gcall.Stepto(-53277, -35277, -2229);
		//gcall.Stepto(-53034, -35268, -2256);
		//gcall.Stepto(-52963, -35263, -2263);
		//gcall.NewSpend(2.5);
		//gcall.Stepto(-52815, -35252, -2279);
		//gcall.Stepto(-52571, -35234, -2295);
		//gcall.Stepto(-52323, -35219, -2311);
		//gcall.Stepto(-52075, -35205, -2328);
		//gcall.Stepto(-51829, -35163, -2314);
		//gcall.Stepto(-51600, -35076, -2304);
		//gcall.Stepto(-51370, -34980, -2298);
		//gcall.Stepto(-51169, -34837, -2282);
		//gcall.Stepto(-51019, -34639, -2273);
		//gcall.Stepto(-50886, -34434, -2264);
		//gcall.Stepto(-50750, -34221, -2266);
		//gcall.Stepto(-50697, -33979, -2252);
		//gcall.Stepto(-50658, -33735, -2237);
		//gcall.Stepto(-50635, -33488, -2234);
		//gcall.Stepto(-50632, -33240, -2230);
		//gcall.Stepto(-50637, -32993, -2218);
		//gcall.Stepto(-50661, -32746, -2193);
		//gcall.Stepto(-50700, -32501, -2159);
		//gcall.Stepto(-50739, -32256, -2096);
		//gcall.Stepto(-50778, -32011, -2006);
		//gcall.Stepto(-50812, -31766, -1953);
		//gcall.Stepto(-50745, -31532, -1944);
		//gcall.Stepto(-50656, -31398, -1944);
		//gcall.Stepto(-50445, -31446, -1954);
		//gcall.Stepto(-50349, -31507, -1961);
		//gcall.NewSpend(1);
		gcall.CityConvey(0x45);//传送过来

		Sleep(1000);
		gcall.WaitPlans();
		Sleep(2000);
		gcall.DeliverQuests(305,taskid, L"공삼식");
		Sleep(1000);
		break;
	case 3:
		gcall.NewSpend(2.5);
		gcall.Stepto(-50337, -31504, -1961);
		gcall.Stepto(-50425, -31444, -1955);
		gcall.Stepto(-50631, -31306, -1944);
		gcall.Stepto(-50837, -31167, -1943);
		gcall.Stepto(-51043, -31029, -1936);
		gcall.Stepto(-51242, -30882, -1912);
		gcall.Stepto(-51316, -30815, -1904);
		gcall.Stepto(-51379, -30753, -1905);
		gcall.Stepto(-51334, -30523, -1905);
		gcall.Stepto(-51328, -30430, -1905);
		gcall.NewSpend(1);
		Sleep(1000);
		gcall.DeliverQuests(305,taskid, L"도단하");
		Sleep(1000);
		break;
	case 4:
		gcall.DeliverQuests(305,taskid, L"남소유");
		Sleep(1000);
		break;
	}

}

void TaskScript::Task_306(int zid,int taskid)
{
	switch (taskid)
	{
	case 1:
		gcall.Stepto(-51392, -30549, -1905 ,10,20,200);
		gcall.Stepto(-51454, -30650, -1905, 10, 20, 200);
		gcall.Stepto(-51374, -30747, -1905, 10, 20, 200);
		gcall.Stepto(-51285, -30837, -1904, 10, 20, 200);
		gcall.Stepto(-51206, -30919, -1928, 10, 20, 200);
		gcall.Stepto(-51128, -31026, -1931, 10, 20, 200);
		gcall.Stepto(-51077, -31139, -1937, 10, 20, 200);
		gcall.Stepto(-51023, -31251, -1939, 10, 20, 200);
		gcall.Stepto(-50975, -31366, -1939, 10, 20, 200);
		Sleep(500);
		gcall.NPCJieRenWu(0xAF, 0x4006d, 0x150,0,0);
		Sleep(500);
		gcall.Stepto(-50813, -31294, -1944);
		gcall.Stepto(-50782, -31174, -1944);
		gcall.Stepto(-50749, -31055, -1944);
		gcall.Stepto(-50717, -30935, -1950);
		gcall.Stepto(-50688, -30814, -1945);
		Sleep(1000);
		gcall.BuyItem(8, 0, L"모팔모");
		gcall.KeyPress(27);
		Sleep(300);
		gcall.KeyPress(27);
		Sleep(1000);
		gcall.NewSpend(2.5);
		gcall.Stepto(-50657, -31212, -1944);
		gcall.Stepto(-50416, -31179, -1958);
		gcall.Stepto(-50165, -31144, -1993);
		gcall.Stepto(-49921, -31110, -2047);
		gcall.Stepto(-49677, -31137, -2116);
		gcall.Stepto(-49464, -31258, -2208);
		gcall.Stepto(-49306, -31449, -2278);
		gcall.Stepto(-49166, -31653, -2323);
		gcall.Stepto(-49025, -31857, -2338);
		gcall.Stepto(-48885, -32061, -2335);
		gcall.Stepto(-48745, -32266, -2332);
		gcall.Stepto(-48603, -32472, -2327);
		gcall.Stepto(-48463, -32676, -2326);
		gcall.Stepto(-48323, -32880, -2326);
		gcall.Stepto(-48182, -33086, -2338);
		gcall.Stepto(-48043, -33287, -2352);
		gcall.Stepto(-47848, -33443, -2375);
		gcall.Stepto(-47649, -33587, -2396);
		gcall.Stepto(-47447, -33734, -2399);
		gcall.Stepto(-47247, -33879, -2384);
		gcall.Stepto(-47045, -34025, -2371);
		gcall.Stepto(-46843, -34171, -2368);
		gcall.Stepto(-46644, -34316, -2378);
		gcall.Stepto(-46443, -34461, -2379);
		gcall.Stepto(-46243, -34607, -2361);
		gcall.Stepto(-46042, -34752, -2338);
		gcall.Stepto(-45829, -34883, -2315);
		gcall.Stepto(-45614, -35007, -2297);
		gcall.Stepto(-45403, -35132, -2261);
		gcall.Stepto(-45232, -35313, -2277);
		gcall.Stepto(-45075, -35505, -2295);
		gcall.Stepto(-44918, -35698, -2267);
		gcall.Stepto(-44731, -35854, -2237);
		gcall.Stepto(-44502, -35952, -2212);
		gcall.Stepto(-44263, -35983, -2174);
		gcall.Stepto(-44021, -35917, -2124);
		gcall.Stepto(-43782, -35849, -2092);
		gcall.Stepto(-43544, -35781, -2054);
		gcall.Stepto(-43305, -35713, -2005);
		gcall.Stepto(-43089, -35651, -1980);
		gcall.Stepto(-42827, -35576, -1925);
		gcall.Stepto(-42587, -35513, -1886);
		gcall.Stepto(-42339, -35495, -1832);
		gcall.Stepto(-42096, -35547, -1763);
		gcall.Stepto(-41871, -35652, -1711);
		gcall.Stepto(-41651, -35761, -1686);
		gcall.Stepto(-41422, -35865, -1643);
		gcall.Stepto(-41185, -35938, -1601);
		gcall.Stepto(-40946, -36005, -1560);
		gcall.Stepto(-40708, -36073, -1531);
		gcall.Stepto(-40469, -36141, -1521);
		gcall.Stepto(-40231, -36209, -1529);
		gcall.Stepto(-39993, -36277, -1513);
		gcall.Stepto(-39750, -36330, -1480);
		gcall.Stepto(-39505, -36363, -1459);
		gcall.Stepto(-39258, -36390, -1447);
		gcall.Stepto(-39010, -36415, -1429);
		gcall.Stepto(-38764, -36439, -1374);
		gcall.Stepto(-38515, -36463, -1229);
		gcall.Stepto(-38270, -36487, -1162);
		gcall.Stepto(-38021, -36511, -1113);
		gcall.Stepto(-37777, -36521, -974);
		gcall.Stepto(-37558, -36405, -935);
		gcall.Stepto(-37344, -36279, -884);
		gcall.Stepto(-37127, -36152, -817);
		gcall.Stepto(-36914, -36030, -750);
		gcall.Stepto(-36679, -36063, -653);
		gcall.Stepto(-36502, -36234, -553);
		gcall.Stepto(-36339, -36424, -462);
		gcall.Stepto(-36218, -36635, -426);
		gcall.Stepto(-36135, -36872, -403);
		gcall.Stepto(-36097, -37110, -391);
		gcall.Stepto(-36217, -37330, -381);
		gcall.Stepto(-36347, -37541, -379);
		gcall.Stepto(-36492, -37742, -376);
		gcall.Stepto(-36672, -37912, -372);
		gcall.Stepto(-36862, -38072, -378);
		gcall.Stepto(-36868, -38077, -378);
		gcall.NewSpend(1);
		Sleep(1000);
		gcall.DeliverQuests(306,taskid, L"역기산");
		Sleep(1000);
		gcall.Stepto(-36802, -38187, -379);
		gcall.Stepto(-36544, -38475, -379);
		gcall.Stepto(-36561, -38668, -378);
		gcall.DeliverQuests(0x150, 1, L"소붕");
		Sleep(1000);
		break;
	case 2:
		gcall.NewSpend(2.5);
		gcall.Stepto(-36656, -38045, -365);
		gcall.Stepto(-36411, -38007, -363);
		gcall.Stepto(-36166, -37971, -374);
		gcall.Stepto(-35928, -38029, -374);
		gcall.Stepto(-35717, -38159, -374);
		gcall.Stepto(-35520, -38311, -374);
		gcall.Stepto(-35333, -38474, -374);
		gcall.Stepto(-35303, -38500, -374);
		gcall.NewSpend(1);
		Sleep(1000);
		gcall.DeliverQuests(306,taskid,L"음소지");
		Sleep(1000);
		break;
	case 3:
		
		gcall.NewSpend(2.5);
		gcall.Stepto(-35353, -38308, -374, 10, 20);
		gcall.Stepto(-35416, -38201, -374, 10, 20);
		gcall.Stepto(-35480, -38094, -374, 10, 20);
		gcall.Stepto(-35544, -37987, -374, 10, 20);
		gcall.Stepto(-35607, -37881, -374, 10, 20);
		gcall.Stepto(-35671, -37775, -374, 10, 20);
		gcall.Stepto(-35735, -37668, -371, 10, 20);
		gcall.Stepto(-35799, -37562, -366, 10, 20);
		gcall.Stepto(-35862, -37455, -378, 10, 20);
		gcall.Stepto(-35926, -37349, -379, 10, 20);
		gcall.Stepto(-35990, -37243, -385, 10, 20);
		gcall.Stepto(-36054, -37136, -388, 10, 20);
		gcall.Stepto(-36119, -37027, -395, 10, 20);
		gcall.Stepto(-36180, -36919, -404, 10, 20);
		gcall.Stepto(-36220, -36802, -412, 10, 20);
		gcall.Stepto(-36249, -36682, -425, 10, 20);
		gcall.Stepto(-36278, -36561, -438, 10, 20);
		gcall.Stepto(-36307, -36440, -455, 10, 20);
		gcall.Stepto(-36336, -36320, -490, 10, 20);
		gcall.Stepto(-36370, -36201, -539, 10, 20);
		gcall.Stepto(-36433, -36095, -584, 10, 20);
		gcall.Stepto(-36535, -36024, -624, 10, 20);
		gcall.Stepto(-36656, -36001, -665, 10, 20);
		gcall.Stepto(-37016, -36081, -778, 10, 20);
		gcall.Stepto(-37241, -36193, -851, 10, 20);
		gcall.Stepto(-37428, -36355, -909, 10, 20);
		gcall.Stepto(-37520, -36438, -932, 10, 20);
		gcall.Stepto(-37612, -36522, -955, 10, 20);
		gcall.Stepto(-37704, -36605, -980, 10, 20);
		gcall.Stepto(-37796, -36688, -1008, 10, 20);
		gcall.Stepto(-37892, -36768, -1027, 10, 20);
		gcall.Stepto(-38007, -36810, -1044, 10, 20);
		gcall.Stepto(-38104, -36743, -1079, 10, 20);
		gcall.Stepto(-38150, -36628, -1126, 10, 20);
		gcall.Stepto(-38177, -36507, -1160, 10, 20);
		gcall.Stepto(-38180, -36383, -1186, 10, 20);
		gcall.Stepto(-38168, -36260, -1211, 10, 20);
		gcall.Stepto(-38156, -36136, -1241, 10, 20);
		gcall.Stepto(-38143, -36013, -1277, 10, 20);
		gcall.Stepto(-38131, -35890, -1315, 10, 20);
		gcall.Stepto(-38132, -35766, -1366, 10, 20);
		gcall.Stepto(-38188, -35525, -1450, 10, 20);
		gcall.Stepto(-38317, -35313, -1505, 10, 20);
		gcall.Stepto(-38450, -35104, -1538, 10, 20);
		gcall.Stepto(-38582, -34894, -1532, 10, 20);
		gcall.Stepto(-38713, -34684, -1524, 10, 20);
		gcall.Stepto(-38780, -34578, -1523, 10, 20, 10000);
		gcall.Stepto(-38918, -34369, -1532, 10, 20, 10000);
		gcall.Stepto(-39063, -34156, -1548, 10, 20, 10000);
		gcall.Stepto(-39192, -33967, -1565, 10, 20, 10000);
		gcall.NewSpend(1);
		gcall.FindThenKill(0, 1000, modeNormal | modeAoe | modePickup | modePickupBody);
		gcall.Stepto(-38753, -34051, -1519, 10, 20, 5000);
		gcall.Stepto(-38629, -34041, -1507, 10, 20, 5000);
		gcall.Stepto(-38506, -34026, -1497);
		gcall.Stepto(-38385, -34003, -1489);
		gcall.Stepto(-38263, -33978, -1486);
		gcall.Stepto(-38142, -33953, -1487);
		gcall.Stepto(-38020, -33928, -1490);
		gcall.Stepto(-37898, -33902, -1489);
		gcall.Stepto(-37776, -33877, -1486);
		gcall.Stepto(-37655, -33852, -1480);
		gcall.Stepto(-37533, -33826, -1473);
		gcall.Stepto(-37416, -33785, -1465);
		gcall.Stepto(-37228, -33628, -1452);
		gcall.Stepto(-37169, -33519, -1451);
		gcall.Stepto(-37085, -33286, -1452);
		gcall.Stepto(-37044, -33169, -1439);
		gcall.Stepto(-36962, -32935, -1395);
		gcall.Stepto(-36871, -32704, -1378);
		gcall.Stepto(-36746, -32491, -1325);
		gcall.Stepto(-36580, -32323, -1280);

		Sleep(1000);
		//丢火炉

		//MessageBox(0, 0, 0, MB_OK);
		gcall.Pickdown();
		Sleep(1000);
		gcall.randXianlu(0);
		Sleep(1000);

		gcall.Stepto(-36570, -32328, -1280);
		gcall.Stepto(-36744, -32507, -1331);
		gcall.Stepto(-36916, -32686, -1379);
		gcall.Stepto(-37081, -32871, -1417);
		gcall.Stepto(-37165, -32962, -1461);
		gcall.Stepto(-37334, -33144, -1500);
		gcall.Stepto(-37511, -33320, -1501);
		gcall.Stepto(-37605, -33401, -1508);
		gcall.Stepto(-37798, -33556, -1516);
		gcall.Stepto(-37896, -33632, -1515);
		gcall.Stepto(-38101, -33771, -1508);
		gcall.Stepto(-38228, -33794, -1504);
		gcall.Stepto(-38474, -33825, -1508);
		gcall.Stepto(-38715, -33881, -1521);
		break;
	case 4:
		gcall.NewSpend(2.5);
		gcall.Stepto(-38632, -34032, -1508,10,20,3000);
		gcall.Stepto(-38514, -34251, -1490);
		gcall.Stepto(-38397, -34469, -1478);
		gcall.Stepto(-38281, -34689, -1468);
		gcall.Stepto(-38189, -34918, -1478);
		gcall.Stepto(-38176, -35167, -1501);
		gcall.Stepto(-38172, -35415, -1465);
		gcall.Stepto(-38168, -35664, -1405);
		gcall.Stepto(-38164, -35912, -1310);
		gcall.Stepto(-38160, -36160, -1234);
		gcall.Stepto(-38156, -36408, -1178);
		gcall.Stepto(-38126, -36655, -1111);
		gcall.Stepto(-38076, -36768, -1067);
		gcall.Stepto(-37856, -36780, -1022);
		gcall.Stepto(-37682, -36603, -977);
		gcall.Stepto(-37501, -36434, -928);
		gcall.Stepto(-37317, -36268, -877);
		gcall.Stepto(-37128, -36107, -814);
		gcall.Stepto(-37024, -36040, -786);
		gcall.Stepto(-36784, -36004, -701);
		gcall.Stepto(-36665, -36039, -660);
		gcall.Stepto(-36463, -36178, -572);
		gcall.Stepto(-36344, -36398, -469);
		gcall.Stepto(-36253, -36629, -430);
		gcall.Stepto(-36163, -36860, -404);
		gcall.Stepto(-36074, -37091, -391);
		gcall.Stepto(-35984, -37323, -379);
		gcall.Stepto(-35876, -37545, -366);
		gcall.Stepto(-35742, -37754, -369);
		gcall.Stepto(-35604, -37960, -374);
		gcall.Stepto(-35471, -38169, -374);
		gcall.Stepto(-35337, -38379, -374);
		gcall.Stepto(-35279, -38471, -374);
		gcall.NewSpend(1);
		Sleep(1000);
		gcall.DeliverQuests(306,taskid, L"음소지");
		Sleep(1000);
		break;
	case 5:
		gcall.NewSpend(2.5);
		gcall.Stepto(-35437, -38439, -374);
		gcall.Stepto(-35656, -38323, -374);
		gcall.Stepto(-35875, -38206, -374);
		gcall.Stepto(-36095, -38089, -374);
		gcall.Stepto(-36329, -38016, -374);
		gcall.Stepto(-36564, -38044, -358);
		gcall.Stepto(-36814, -38106, -379);
		gcall.Stepto(-36853, -38116, -379);
		gcall.NewSpend(1);
		Sleep(1000);
		gcall.DeliverQuests(306,taskid, L"역기산");
		Sleep(1500);
		
		break;
	}

}

void TaskScript::Task_307(int zid,int taskid)
{
	switch (taskid)
	{
	case 1:
		gcall.Stepto(-36844, -38003, -377);
		Sleep(500);
		gcall.NPCJieRenWu(0xB9, 0x4006B, 0x15A, 0, 0);
		Sleep(1000);
		gcall.NewSpend(2.5);
		gcall.Stepto(-36497, -37940, -357);
		gcall.Stepto(-36142, -37939, -374);
		gcall.Stepto(-35819, -38065, -374);
		gcall.Stepto(-35561, -38264, -374);
		gcall.Stepto(-35308, -38470, -374);
		Sleep(1000);
		gcall.DeliverQuests(346, 1, L"음소지");
		Sleep(1000);
		gcall.NewSpend(2.5);
		gcall.Stepto(-3460, -6188, 627);
		gcall.Stepto(-3543, -6151, 626);
		gcall.Stepto(-3766, -6051, 605);
		gcall.Stepto(-4003, -6033, 576);
		gcall.Stepto(-4238, -6127, 556);
		gcall.Stepto(-4309, -6156, 560);
		gcall.Stepto(-4466, -5729, 559);
		gcall.Stepto(-4682, -5613, 557);
		gcall.Stepto(-4907, -5492, 551);
		gcall.Stepto(-5122, -5377, 550);
		gcall.Stepto(-5338, -5260, 554);
		gcall.Stepto(-5565, -5149, 559);
		gcall.Stepto(-5786, -5045, 563);
		gcall.Stepto(-6014, -4937, 566);
		gcall.Stepto(-6235, -4833, 559);
		gcall.Stepto(-6459, -4718, 541);
		gcall.Stepto(-6652, -4614, 551);
		gcall.Stepto(-6891, -4486, 560);
		gcall.Stepto(-7112, -4367, 584);
		gcall.Stepto(-7327, -4251, 598);
		gcall.Stepto(-7551, -4138, 599);
		gcall.Stepto(-7781, -4033, 601);
		gcall.Stepto(-8014, -3944, 601);
		gcall.Stepto(-8247, -3882, 595);
		gcall.Stepto(-8493, -3815, 570);
		gcall.Stepto(-8731, -3751, 583);
		gcall.Stepto(-8968, -3760, 602);
		gcall.Stepto(-9160, -3918, 602);
		gcall.Stepto(-9351, -4082, 602);
		gcall.Stepto(-9539, -4246, 602);
		gcall.Stepto(-9724, -4413, 602);
		gcall.Stepto(-9907, -4578, 602);
		gcall.Stepto(-10095, -4747, 602);
		gcall.Stepto(-10275, -4910, 602);
		gcall.Stepto(-10462, -5078, 602);
		gcall.Stepto(-10646, -5244, 602);
		gcall.Stepto(-10845, -5394, 603);
		gcall.Stepto(-11050, -5529, 621);
		gcall.Stepto(-11278, -5616, 641);
		gcall.Stepto(-11529, -5621, 657);
		gcall.Stepto(-11766, -5564, 656);
		gcall.Stepto(-12012, -5493, 665);
		gcall.Stepto(-12247, -5426, 646);
		gcall.Stepto(-12491, -5382, 635);
		gcall.Stepto(-12737, -5433, 605);
		gcall.Stepto(-12964, -5525, 596);
		gcall.Stepto(-13195, -5628, 579);
		gcall.Stepto(-13398, -5763, 590);
		gcall.Stepto(-13589, -5929, 562);
		gcall.Stepto(-13775, -6089, 532);
		gcall.Stepto(-13959, -6242, 455);
		gcall.Stepto(-14179, -6392, 354);
		gcall.Stepto(-14401, -6493, 231);
		gcall.Stepto(-14450, -6515, 206);
		gcall.Stepto(-14556, -6561, 157);
		gcall.Stepto(-14805, -6596, 20);
		gcall.Stepto(-15050, -6604, -39);
		gcall.Stepto(-15303, -6612, -66);
		gcall.Stepto(-15548, -6619, -83);
		gcall.Stepto(-15801, -6628, -112);
		gcall.Stepto(-16046, -6637, -141);
		gcall.Stepto(-16291, -6703, -170);
		gcall.Stepto(-16506, -6819, -183);
		gcall.Stepto(-16710, -6967, -187);
		gcall.Stepto(-16896, -7127, -190);
		gcall.Stepto(-17061, -7317, -191);
		gcall.Stepto(-17125, -7552, -186);
		gcall.Stepto(-17119, -7805, -207);
		gcall.Stepto(-17055, -8042, -235);
		gcall.Stepto(-16950, -8263, -255);
		gcall.Stepto(-16817, -8476, -283);
		gcall.Stepto(-16649, -8654, -330);
		gcall.Stepto(-16475, -8838, -374);
		gcall.Stepto(-16304, -9020, -413);
		gcall.Stepto(-16140, -9202, -452);
		gcall.Stepto(-15971, -9387, -491);
		gcall.Stepto(-15791, -9553, -520);
		gcall.Stepto(-15605, -9724, -538);
		gcall.Stepto(-15424, -9889, -567);
		gcall.Stepto(-15238, -10060, -605);
		gcall.Stepto(-15057, -10225, -639);
		gcall.Stepto(-14871, -10396, -677);
		gcall.Stepto(-14684, -10567, -719);
		gcall.Stepto(-14499, -10726, -748);
		gcall.Stepto(-14310, -10881, -774);
		gcall.Stepto(-14107, -11038, -807);
		gcall.Stepto(-13905, -11189, -848);
		gcall.Stepto(-13707, -11332, -889);
		gcall.Stepto(-13481, -11447, -919);
		gcall.Stepto(-13258, -11546, -942);
		gcall.Stepto(-13027, -11649, -993);
		gcall.Stepto(-12803, -11748, -1051);
		gcall.Stepto(-12572, -11851, -1098);
		gcall.Stepto(-12348, -11950, -1115);
		gcall.Stepto(-12271, -11984, -1127);
		gcall.Stepto(-12243, -11997, -1130);
		gcall.Stepto(-12012, -12099, -1168);
		gcall.Stepto(-11786, -12200, -1212);
		gcall.Stepto(-11562, -12299, -1265);
		gcall.Stepto(-11328, -12403, -1334);
		gcall.Stepto(-11104, -12502, -1384);
		gcall.Stepto(-10878, -12603, -1409);
		gcall.Stepto(-10651, -12704, -1454);
		gcall.Stepto(-10420, -12806, -1498);
		gcall.Stepto(-10194, -12907, -1540);
		gcall.Stepto(-9964, -13009, -1589);
		gcall.Stepto(-9742, -13110, -1617);
		gcall.Stepto(-9524, -13238, -1639);
		gcall.Stepto(-9325, -13381, -1650);
		gcall.Stepto(-9155, -13562, -1665);
		gcall.Stepto(-8997, -13759, -1679);
		gcall.Stepto(-8855, -13968, -1699);
		gcall.Stepto(-8748, -14186, -1714);
		gcall.Stepto(-8660, -14426, -1718);
		gcall.Stepto(-8586, -14660, -1722);
		gcall.Stepto(-8515, -14901, -1730);
		gcall.Stepto(-8446, -15137, -1743);
		gcall.Stepto(-8376, -15378, -1762);
		gcall.Stepto(-8305, -15621, -1782);
		gcall.Stepto(-8254, -15860, -1792);
		gcall.Stepto(-8228, -16109, -1791);
		gcall.Stepto(-8208, -16354, -1784);
		gcall.Stepto(-8189, -16592, -1775);
		gcall.Stepto(-8167, -16854, -1759);
		gcall.Stepto(-8147, -17104, -1744);
		gcall.Stepto(-8127, -17348, -1732);
		gcall.Stepto(-8076, -17593, -1723);
		gcall.Stepto(-7977, -17826, -1716);
		gcall.Stepto(-7856, -18036, -1713);
		gcall.Stepto(-7698, -18234, -1719);
		gcall.Stepto(-7499, -18386, -1730);
		gcall.Stepto(-7278, -18472, -1730);
		gcall.Stepto(-7031, -18555, -1749);
		gcall.Stepto(-6800, -18633, -1770);
		gcall.Stepto(-6563, -18723, -1802);
		gcall.Stepto(-6352, -18850, -1846);
		gcall.Stepto(-6155, -19008, -1867);
		gcall.Stepto(-6010, -19203, -1870);
		gcall.Stepto(-5903, -19431, -1897);
		gcall.Stepto(-5823, -19671, -1902);
		gcall.Stepto(-5746, -19903, -1895);
		gcall.Stepto(-5696, -20151, -1889);
		gcall.Stepto(-5663, -20393, -1886);
		gcall.Stepto(-5661, -20646, -1870);
		gcall.Stepto(-5696, -20888, -1868);
		gcall.Stepto(-5768, -21130, -1869);
		gcall.Stepto(-5849, -21365, -1873);
		gcall.Stepto(-5930, -21597, -1874);
		gcall.Stepto(-6012, -21836, -1876);
		gcall.Stepto(-6095, -22075, -1889);
		gcall.Stepto(-6161, -22310, -1906);
		gcall.Stepto(-6126, -22559, -1926);
		gcall.Stepto(-6019, -22778, -1937);
		gcall.Stepto(-5896, -22999, -1961);
		gcall.Stepto(-5772, -23220, -1972);
		gcall.Stepto(-5653, -23434, -1997);
		gcall.Stepto(-5533, -23656, -2016);
		gcall.Stepto(-5429, -23877, -2059);
		gcall.Stepto(-5390, -24109, -2114);
		gcall.Stepto(-5390, -24110, -2114);
		gcall.Stepto(-5370, -24253, -2149);
		gcall.Stepto(-5359, -24502, -2204);
		gcall.Stepto(-5354, -24628, -2227);
		gcall.Stepto(-5341, -24840, -2282);
		gcall.Stepto(-5276, -25084, -2331);
		gcall.Stepto(-5198, -25310, -2374);
		gcall.Stepto(-5103, -25549, -2421);
		gcall.Stepto(-5010, -25776, -2452);
		gcall.Stepto(-4913, -26010, -2467);
		gcall.Stepto(-4803, -26238, -2467);
		gcall.Stepto(-4695, -26459, -2458);
		gcall.Stepto(-4587, -26679, -2451);
		gcall.Stepto(-4473, -26904, -2459);
		gcall.Stepto(-4349, -27120, -2471);
		gcall.Stepto(-4212, -27332, -2483);
		gcall.Stepto(-4070, -27531, -2499);
		gcall.Stepto(-3918, -27734, -2510);
		gcall.Stepto(-3758, -27930, -2515);
		gcall.Stepto(-3604, -28119, -2535);
		gcall.Stepto(-3541, -28197, -2539);
		gcall.Stepto(-3399, -28371, -2545);
		gcall.Stepto(-3244, -28561, -2554);
		gcall.Stepto(-3085, -28757, -2580);
		gcall.Stepto(-2930, -28947, -2612);
		gcall.Stepto(-2771, -29143, -2628);
		gcall.Stepto(-2611, -29340, -2651);
		gcall.Stepto(-2457, -29530, -2662);
		gcall.Stepto(-2299, -29723, -2684);
		gcall.Stepto(-2140, -29919, -2710);
		gcall.Stepto(-1986, -30108, -2732);
		gcall.Stepto(-1970, -30128, -2734);
		gcall.Stepto(-1913, -30198, -2741);
		gcall.Stepto(-1753, -30394, -2761);
		gcall.Stepto(-1598, -30584, -2771);
		gcall.Stepto(-1439, -30780, -2772);
		gcall.Stepto(-1280, -30975, -2800);
		gcall.Stepto(-1127, -31164, -2814);
		gcall.Stepto(-968, -31359, -2818);
		gcall.Stepto(-808, -31555, -2827);
		gcall.Stepto(-654, -31745, -2844);
		gcall.Stepto(-494, -31941, -2866);
		gcall.Stepto(-339, -32133, -2874);
		gcall.Stepto(-206, -32342, -2882);
		gcall.Stepto(-203, -32596, -2882);
		gcall.Stepto(-280, -32832, -2886);
		gcall.Stepto(-419, -33033, -2876);
		gcall.Stepto(-598, -33212, -2849);
		gcall.Stepto(-818, -33317, -2827);
		gcall.Stepto(-1055, -33404, -2810);
		gcall.Stepto(-1289, -33491, -2807);
		gcall.Stepto(-1526, -33578, -2807);
		gcall.Stepto(-1756, -33663, -2807);
		gcall.Stepto(-1993, -33750, -2812);
		gcall.Stepto(-2231, -33838, -2822);
		gcall.Stepto(-2460, -33922, -2839);
		gcall.Stepto(-2707, -33979, -2859);
		gcall.Stepto(-2944, -33951, -2874);
		gcall.Stepto(-3163, -33824, -2886);
		gcall.Stepto(-3374, -33685, -2902);
		gcall.Stepto(-3578, -33551, -2907);
		gcall.Stepto(-3790, -33411, -2927);
		gcall.Stepto(-4002, -33272, -2923);
		gcall.Stepto(-4206, -33138, -2914);
		gcall.Stepto(-4405, -32982, -2912);
		gcall.Stepto(-4597, -32831, -2906);
		gcall.Stepto(-4800, -32683, -2906);
		gcall.Stepto(-5005, -32535, -2905);
		gcall.Stepto(-5209, -32384, -2901);
		gcall.Stepto(-5398, -32230, -2907);
		gcall.Stepto(-5594, -32070, -2905);
		gcall.Stepto(-5792, -31908, -2911);
		gcall.Stepto(-5988, -31748, -2885);
		gcall.Stepto(-6184, -31588, -2845);
		gcall.Stepto(-6367, -31439, -2840);
		gcall.Stepto(-6569, -31273, -2836);
		gcall.Stepto(-6765, -31113, -2812);
		gcall.Stepto(-6955, -30958, -2766);
		gcall.Stepto(-7151, -30798, -2723);
		gcall.Stepto(-7347, -30638, -2706);
		gcall.Stepto(-7538, -30481, -2696);
		gcall.Stepto(-7734, -30321, -2696);
		gcall.Stepto(-7932, -30159, -2704);
		gcall.Stepto(-8133, -29996, -2691);
		gcall.Stepto(-8328, -29836, -2674);
		gcall.Stepto(-8518, -29681, -2616);
		gcall.Stepto(-8723, -29535, -2539);
		gcall.Stepto(-8962, -29453, -2453);
		gcall.Stepto(-9212, -29399, -2354);
		gcall.Stepto(-9453, -29357, -2281);
		gcall.Stepto(-9703, -29320, -2197);
		gcall.Stepto(-9953, -29282, -2111);
		gcall.Stepto(-10195, -29246, -2031);
		gcall.Stepto(-10445, -29209, -1963);
		gcall.Stepto(-10695, -29169, -1895);
		gcall.Stepto(-10795, -29148, -1874);
		gcall.Stepto(-11044, -29097, -1829);
		gcall.Stepto(-11292, -29046, -1773);
		gcall.Stepto(-11531, -28980, -1730);
		gcall.Stepto(-11733, -28833, -1694);
		gcall.Stepto(-11888, -28644, -1670);
		gcall.Stepto(-12047, -28447, -1654);
		gcall.Stepto(-12206, -28250, -1634);
		gcall.Stepto(-12369, -28057, -1611);
		gcall.Stepto(-12561, -27907, -1585);
		gcall.Stepto(-12803, -27843, -1546);
		gcall.Stepto(-13053, -27873, -1512);
		gcall.Stepto(-13297, -27924, -1481);
		gcall.Stepto(-13541, -27976, -1450);
		gcall.Stepto(-13779, -28045, -1413);
		gcall.Stepto(-14017, -28139, -1377);
		gcall.Stepto(-14242, -28235, -1374);
		gcall.Stepto(-14471, -28342, -1345);
		gcall.Stepto(-14697, -28456, -1332);
		gcall.Stepto(-14916, -28567, -1338);
		gcall.Stepto(-15136, -28694, -1302);
		gcall.Stepto(-15280, -28891, -1280);
		gcall.Stepto(-15404, -29121, -1259);
		gcall.Stepto(-15531, -29328, -1233);
		gcall.Stepto(-15716, -29501, -1203);
		gcall.Stepto(-15929, -29639, -1192);
		gcall.Stepto(-16076, -29711, -1180);
		gcall.Stepto(-16256, -29800, -1175);
		gcall.Stepto(-16484, -29911, -1177);
		gcall.Stepto(-16703, -30019, -1177);
		gcall.Stepto(-16930, -30130, -1178);
		gcall.Stepto(-17159, -30242, -1182);
		gcall.Stepto(-17381, -30351, -1181);
		gcall.Stepto(-17608, -30463, -1172);
		gcall.Stepto(-17835, -30574, -1165);
		gcall.Stepto(-18065, -30687, -1155);
		gcall.Stepto(-18292, -30798, -1141);
		gcall.Stepto(-18511, -30906, -1115);
		gcall.Stepto(-18737, -31020, -1087);
		gcall.Stepto(-18976, -31116, -1061);
		gcall.Stepto(-19213, -31196, -1079);
		gcall.Stepto(-19454, -31273, -1126);
		gcall.Stepto(-19688, -31345, -1168);
		gcall.Stepto(-19916, -31402, -1163);
		gcall.Stepto(-20181, -31432, -1147);
		gcall.Stepto(-20434, -31435, -1126);
		gcall.Stepto(-20689, -31417, -1140);
		gcall.Stepto(-20941, -31393, -1162);
		gcall.Stepto(-21182, -31351, -1161);
		gcall.Stepto(-21428, -31293, -1138);
		gcall.Stepto(-21671, -31222, -1128);
		gcall.Stepto(-21913, -31147, -1154);
		gcall.Stepto(-22147, -31071, -1192);
		gcall.Stepto(-22388, -30994, -1188);
		gcall.Stepto(-22629, -30916, -1174);
		gcall.Stepto(-22863, -30841, -1186);
		gcall.Stepto(-23104, -30764, -1175);
		gcall.Stepto(-23344, -30686, -1125);
		gcall.Stepto(-23586, -30610, -1075);
		gcall.Stepto(-23828, -30535, -1050);
		gcall.Stepto(-24062, -30463, -1046);
		gcall.Stepto(-24303, -30389, -1046);
		gcall.Stepto(-24545, -30314, -1044);
		gcall.Stepto(-24786, -30240, -1056);
		gcall.Stepto(-25028, -30166, -1056);
		gcall.Stepto(-25272, -30098, -1048);
		gcall.Stepto(-25513, -30036, -1032);
		gcall.Stepto(-25760, -29986, -1034);
		gcall.Stepto(-26015, -29965, -1050);
		gcall.Stepto(-26261, -29951, -1065);
		gcall.Stepto(-26514, -29951, -1078);
		gcall.Stepto(-26758, -29951, -1074);
		gcall.Stepto(-27006, -29997, -1070);
		gcall.Stepto(-27243, -30086, -1075);
		gcall.Stepto(-27485, -30158, -1080);
		gcall.Stepto(-27733, -30207, -1078);
		gcall.Stepto(-27983, -30247, -1076);
		gcall.Stepto(-28227, -30269, -1074);
		gcall.Stepto(-28479, -30290, -1076);
		gcall.Stepto(-28727, -30311, -1080);
		gcall.Stepto(-28979, -30353, -1074);
		gcall.Stepto(-29230, -30402, -1070);
		gcall.Stepto(-29477, -30449, -1081);
		gcall.Stepto(-29721, -30515, -1098);
		gcall.Stepto(-29953, -30613, -1105);
		gcall.Stepto(-30111, -30806, -1088);
		gcall.Stepto(-30187, -31050, -1045);
		gcall.Stepto(-30253, -31288, -964);
		gcall.Stepto(-30313, -31533, -897);
		gcall.Stepto(-30354, -31784, -828);
		gcall.Stepto(-30394, -32033, -756);
		gcall.Stepto(-30450, -32271, -714);
		gcall.Stepto(-30543, -32506, -691);
		gcall.Stepto(-30662, -32729, -703);
		gcall.Stepto(-30775, -32955, -704);
		gcall.Stepto(-30885, -33179, -724);
		gcall.Stepto(-30998, -33405, -720);
		gcall.Stepto(-31120, -33626, -762);
		gcall.Stepto(-31261, -33837, -819);
		gcall.Stepto(-31406, -34024, -871);
		gcall.Stepto(-31594, -34210, -902);
		gcall.Stepto(-31788, -34360, -935);
		gcall.Stepto(-32002, -34504, -954);
		gcall.Stepto(-32214, -34626, -973);
		gcall.Stepto(-32431, -34748, -1000);
		gcall.Stepto(-32651, -34872, -1027);
		gcall.Stepto(-32868, -34993, -1056);
		gcall.Stepto(-33091, -35117, -1090);
		gcall.Stepto(-33318, -35226, -1130);
		gcall.Stepto(-33558, -35304, -1154);
		gcall.Stepto(-33805, -35364, -1148);
		gcall.Stepto(-34039, -35396, -1122);
		gcall.Stepto(-34300, -35411, -1085);
		gcall.Stepto(-34556, -35422, -1052);
		gcall.Stepto(-34809, -35433, -1032);
		gcall.Stepto(-35053, -35445, -1000);
		gcall.Stepto(-35308, -35475, -949);
		gcall.Stepto(-35486, -35628, -899);
		gcall.Stepto(-35426, -35862, -797);
		gcall.Stepto(-35280, -36073, -688);
		gcall.Stepto(-35137, -36282, -604);
		gcall.Stepto(-35044, -36513, -514);
		gcall.Stepto(-35062, -36759, -451);
		gcall.Stepto(-35181, -36981, -394);
		gcall.Stepto(-35355, -37162, -379);
		gcall.Stepto(-35547, -37324, -379);
		gcall.Stepto(-35746, -37469, -376);
		gcall.Stepto(-35952, -37602, -366);
		gcall.Stepto(-36182, -37732, -375);
		gcall.Stepto(-36405, -37848, -372);
		gcall.Stepto(-36627, -37964, -363);
		gcall.Stepto(-36834, -38073, -378);
		gcall.Stepto(-36836, -38074, -378);
		gcall.Stepto(-36853, -38116, -379);
		gcall.Stepto(-36865, -38093, -378);
		gcall.Stepto(-36773, -38058, -378);
		gcall.Stepto(-36534, -38005, -356);
		gcall.Stepto(-36291, -37959, -374);
		gcall.Stepto(-36040, -37928, -374);
		gcall.Stepto(-35797, -37898, -374);
		gcall.Stepto(-35544, -37894, -374);
		gcall.Stepto(-35300, -37896, -374);
		gcall.Stepto(-35140, -37905, -375);
		gcall.Stepto(-35140, -37905, -375);
		gcall.Stepto(-35144, -37689, -378);
		gcall.Stepto(-35143, -37436, -379);
		gcall.Stepto(-35056, -37211, -393);
		gcall.Stepto(-34861, -37052, -417);
		gcall.Stepto(-34672, -36959, -433);
		gcall.Stepto(-34629, -36939, -436);
		gcall.Stepto(-34460, -36861, -441);
		gcall.Stepto(-34454, -36858, -441);
		gcall.Stepto(-34233, -36756, -514);
		gcall.Stepto(-34005, -36645, -823);
		gcall.Stepto(-33797, -36516, -1138);
		gcall.Stepto(-33620, -36349, -1177);
		gcall.Stepto(-33430, -36181, -1167);
		gcall.Stepto(-33244, -36036, -1110);
		gcall.Stepto(-33060, -35852, -1045);
		gcall.Stepto(-32887, -35663, -1010);
		gcall.Stepto(-32722, -35483, -988);
		gcall.Stepto(-32551, -35296, -975);
		gcall.Stepto(-32386, -35115, -961);
		gcall.Stepto(-32220, -34934, -954);
		gcall.Stepto(-32051, -34750, -950);
		gcall.Stepto(-31881, -34563, -943);
		gcall.Stepto(-31714, -34381, -923);
		gcall.Stepto(-31547, -34199, -896);
		gcall.Stepto(-31390, -33997, -865);
		gcall.Stepto(-31246, -33800, -810);
		gcall.Stepto(-31107, -33599, -756);
		gcall.Stepto(-30972, -33389, -720);
		gcall.Stepto(-30929, -33307, -724);
		gcall.Stepto(-30895, -33242, -727);
		gcall.Stepto(-30789, -33016, -705);
		gcall.Stepto(-30690, -32792, -705);
		gcall.Stepto(-30606, -32553, -698);
		gcall.Stepto(-30517, -32326, -705);
		gcall.Stepto(-30425, -32090, -744);
		gcall.Stepto(-30369, -31848, -810);
		gcall.Stepto(-30335, -31606, -877);
		gcall.Stepto(-30335, -31376, -939);
		gcall.Stepto(-30335, -31362, -942);
		gcall.Stepto(-30355, -31110, -1007);
		gcall.Stepto(-30383, -30867, -1065);
		gcall.Stepto(-30412, -30615, -1122);
		gcall.Stepto(-30440, -30372, -1158);
		gcall.Stepto(-30469, -30121, -1181);
		gcall.Stepto(-30497, -29878, -1194);
		gcall.Stepto(-30524, -29638, -1194);
		gcall.Stepto(-30553, -29383, -1186);
		gcall.Stepto(-30582, -29135, -1180);
		gcall.Stepto(-30610, -28890, -1176);
		gcall.Stepto(-30638, -28644, -1174);
		gcall.Stepto(-30667, -28396, -1172);
		gcall.Stepto(-30695, -28144, -1172);
		gcall.Stepto(-30720, -27900, -1175);
		gcall.Stepto(-30744, -27648, -1177);
		gcall.Stepto(-30767, -27405, -1177);
		gcall.Stepto(-30791, -27157, -1171);
		gcall.Stepto(-30823, -26907, -1157);
		gcall.Stepto(-30902, -26678, -1111);
		gcall.Stepto(-30985, -26439, -1118);
		gcall.Stepto(-31019, -26198, -1067);
		gcall.Stepto(-30882, -26007, -996);
		gcall.Stepto(-30664, -25897, -992);
		gcall.Stepto(-30521, -25823, -990);
		gcall.Stepto(-30533, -25690, -993);
		gcall.Stepto(-30538, -25625, -991);
		gcall.NewSpend(1);
		Sleep(1000);
		gcall.DeliverQuests(346, 2, L"육지평");
		Sleep(1000);
		gcall.DeliverQuests(307,taskid, L"기봉사");
		Sleep(1000);
		gcall.HeChengWuQi(EQUITMENT_POS::WUQI);
		Sleep(1000);
		gcall.SellItemByConfig(L"이화상");
		Sleep(1000);
		gcall.SortBag();
		Sleep(1000);
		break;
	case 2:
		gcall.NewSpend(2.5);
		gcall.Stepto(-30622, -25847, -991);
		gcall.Stepto(-30862, -25909, -994);
		gcall.Stepto(-31109, -25920, -1004);
		gcall.Stepto(-31353, -25886, -1051);
		gcall.Stepto(-31598, -25839, -1052);
		gcall.Stepto(-31834, -25763, -1052);
		gcall.Stepto(-32070, -25686, -1049);
		gcall.Stepto(-32306, -25610, -1049);
		gcall.Stepto(-32538, -25535, -1046);
		gcall.Stepto(-32779, -25457, -1056);
		gcall.Stepto(-33015, -25381, -1078);
		gcall.Stepto(-33251, -25304, -1103);
		gcall.Stepto(-33485, -25228, -1126);
		gcall.Stepto(-33715, -25137, -1140);
		gcall.Stepto(-33940, -25025, -1162);
		gcall.Stepto(-34159, -24916, -1186);
		gcall.Stepto(-34383, -24805, -1185);
		gcall.Stepto(-34622, -24758, -1191);
		gcall.Stepto(-34868, -24801, -1202);
		gcall.Stepto(-35103, -24876, -1207);
		gcall.Stepto(-35338, -24956, -1249);
		gcall.Stepto(-35572, -25038, -1278);
		gcall.Stepto(-35802, -25118, -1309);
		gcall.Stepto(-36040, -25201, -1344);
		gcall.Stepto(-36274, -25283, -1387);
		gcall.Stepto(-36511, -25352, -1424);
		gcall.Stepto(-36760, -25347, -1462);
		gcall.Stepto(-36994, -25269, -1478);
		gcall.Stepto(-37208, -25143, -1482);
		gcall.Stepto(-37418, -25011, -1500);
		gcall.Stepto(-37628, -24880, -1513);
		gcall.Stepto(-37839, -24748, -1522);
		gcall.Stepto(-38047, -24617, -1543);
		gcall.Stepto(-38258, -24485, -1553);
		gcall.Stepto(-38470, -24352, -1532);
		gcall.Stepto(-38680, -24220, -1482);
		gcall.Stepto(-38887, -24085, -1428);
		gcall.Stepto(-39040, -23891, -1394);
		gcall.Stepto(-39111, -23655, -1400);
		gcall.Stepto(-39118, -23410, -1365);
		gcall.Stepto(-39062, -23165, -1377);
		gcall.Stepto(-38976, -22932, -1331);
		gcall.NewSpend(1);
		Sleep(5000);
		gcall.Stepto(-38916, -22807, -1340);
		gcall.WaitPlans();
		gcall.Stepto(-38687, -22259, -1467);
		gcall.WaitPlans();
		gcall.Stepto(-38636, -22019, -1460);
		gcall.NewSpend(2.5);
		gcall.Stepto(-38681, -21780, -1417);
		gcall.Stepto(-38827, -21580, -1361);
		gcall.Stepto(-39002, -21398, -1298);
		gcall.Stepto(-39176, -21222, -1210);
		gcall.Stepto(-39348, -21048, -1117);
		gcall.Stepto(-39551, -20899, -1014);
		gcall.Stepto(-39760, -20766, -959);
		gcall.Stepto(-39967, -20634, -932);
		gcall.Stepto(-40174, -20498, -932);
		gcall.Stepto(-40378, -20356, -935);
		gcall.Stepto(-40577, -20216, -934);
		gcall.Stepto(-40783, -20066, -932);
		gcall.NewSpend(1);
		gcall.Stepto(-40984, -19921, -929);
		gcall.Stepto(-41182, -19771, -929);
		gcall.Stepto(-41356, -19637, -934);
		gcall.Stepto(-41513, -19515, -931);
		gcall.Stepto(-41671, -19393, -928);
		gcall.Stepto(-41829, -19271, -930);
		gcall.Stepto(-41986, -19149, -935);
		gcall.Stepto(-42144, -19027, -929);
		gcall.Stepto(-42300, -18907, -936);
		gcall.Stepto(-42458, -18785, -936);
		gcall.Stepto(-42615, -18663, -937);
		gcall.Stepto(-42771, -18543, -931);
		gcall.Stepto(-42928, -18421, -936);
		gcall.Stepto(-43086, -18299, -936);
		gcall.Stepto(-43243, -18178, -936);
		gcall.Stepto(-43400, -18057, -933);
		gcall.Stepto(-43560, -17941, -934);
		gcall.Stepto(-43733, -17839, -935);
		gcall.FindThenKill(0, 900, modeNormal | modeAoe | modePickup | modeGoback);
		gcall.Stepto(-44228, -17506, -1033,10,20,1500);
		gcall.Stepto(-44385, -17385, -1116);
		gcall.Stepto(-44539, -17260, -1198);
		gcall.Stepto(-44693, -17135, -1288);
		gcall.Stepto(-44844, -17012, -1365);
		gcall.Stepto(-45002, -16884, -1439);
		gcall.Stepto(-45164, -16770, -1447);
		gcall.Stepto(-45336, -16667, -1438);
		gcall.Stepto(-45510, -16573, -1461);
		gcall.Stepto(-45689, -16490, -1490);
		gcall.Stepto(-45873, -16416, -1519);
		gcall.Stepto(-46060, -16344, -1548);
		gcall.Stepto(-46246, -16274, -1576);
		gcall.Stepto(-46433, -16208, -1598);
		gcall.Stepto(-46629, -16189, -1603);
		gcall.Stepto(-46827, -16208, -1601);
		gcall.Stepto(-47024, -16228, -1603);
		gcall.Stepto(-47222, -16247, -1628);
		gcall.Stepto(-47419, -16264, -1626);
		gcall.Stepto(-47618, -16232, -1614);
		gcall.Stepto(-47810, -16183, -1615);
		gcall.Stepto(-48002, -16132, -1615);
		gcall.Stepto(-48195, -16081, -1611);
		gcall.Stepto(-48392, -16056, -1608);
		gcall.Stepto(-48590, -16061, -1612);
		gcall.Stepto(-48785, -16097, -1615);
		gcall.Stepto(-48972, -16162, -1610);
		gcall.FindThenKill(0, 900, modeNormal | modeAoe | modePickup | modeGoback);
		gcall.Stepto(-48713, -16085, -1615,10,20,2000);
		gcall.Stepto(-48509, -15996, -1601);
		gcall.Stepto(-48364, -15929, -1604);
		gcall.Stepto(-48219, -15986, -1607);
		gcall.Stepto(-47987, -16076, -1615);
		gcall.Stepto(-47748, -16133, -1614);
		gcall.Stepto(-47581, -16310, -1617);
		gcall.Stepto(-47550, -16376, -1624);
		gcall.Stepto(-47367, -16489, -1625);
		gcall.Stepto(-47145, -16599, -1615);
		gcall.Stepto(-46911, -16680, -1607);
		gcall.Stepto(-46668, -16729, -1619);
		gcall.Stepto(-46424, -16768, -1619);
		gcall.Stepto(-46177, -16763, -1576);
		gcall.Stepto(-45931, -16730, -1497);
		gcall.Stepto(-45681, -16728, -1463);
		gcall.Stepto(-45435, -16734, -1443);
		gcall.Stepto(-45363, -16736, -1438);
		gcall.Stepto(-45345, -16607, -1439);
		gcall.Stepto(-45479, -16479, -1456);
		gcall.Stepto(-45659, -16308, -1502);
		gcall.Stepto(-45838, -16136, -1549);
		gcall.Stepto(-45986, -15994, -1580);
		gcall.Stepto(-46087, -15975, -1591);
		gcall.Stepto(-46330, -15927, -1599);
		gcall.Stepto(-46574, -15879, -1597);
		gcall.Stepto(-46666, -15901, -1597);
		gcall.Stepto(-46876, -16033, -1598);
		gcall.Stepto(-47087, -16164, -1610);
		gcall.Stepto(-47297, -16295, -1630);
		gcall.Stepto(-47352, -16330, -1631);
		gcall.FindThenKill(0, 900, modeNormal | modeAoe | modePickup | modeGoback);
		gcall.Stepto(-46691, -15764, -1608);
		Sleep(5000);
		gcall.FindThenKill(0, 300, modeNormal | modeAoe | modePickup);
		gcall.Stepto(-46691, -15764, -1608);
		Sleep(1000);
		gcall.PickupTask();
		Sleep(1000);
		gcall.Stepto(-46691, -15764, -1608);
		gcall.Stepto(-46535, -15908, -1597);
		gcall.Stepto(-46328, -16030, -1600);
		gcall.Stepto(-46082, -16067, -1581);
		gcall.Stepto(-45837, -16111, -1522);
		gcall.Stepto(-45671, -16154, -1482);
		Sleep(2000);
		gcall.FindThenKill(0, 300, modeNormal | modeAoe | modePickup);
		gcall.Stepto(-45837, -16111, -1522);
		gcall.Stepto(-45671, -16154, -1482);
		Sleep(1000);
		gcall.PickupTask();
		Sleep(1000);
		gcall.Stepto(-45671, -16154, -1509);
		gcall.Stepto(-45757, -16340, -1513);
		gcall.Stepto(-45844, -16574, -1503);
		gcall.Stepto(-45902, -16745, -1489);
		//Sleep(2000);
		//gcall.FindThenKill(0, 300, modeNormal | modeAoe | modePickup);
		//gcall.Stepto(-45844, -16574, -1503);
		//gcall.Stepto(-45902, -16745, -1489);
		Sleep(1000);
		gcall.PickupTask();
		Sleep(1000);
		gcall.Stepto(-46070, -16733, -1548);
		gcall.Stepto(-46260, -16719, -1592);
		gcall.Stepto(-46336, -16842, -1610);
		gcall.Stepto(-46337, -16844, -1610);
		//Sleep(2000);
		//gcall.FindThenKill(0, 300, modeNormal | modeAoe | modePickup);
		//gcall.Stepto(-46260, -16719, -1592);
		//gcall.Stepto(-46337, -16844, -1610);
		Sleep(1000);
		gcall.PickupTask();
		Sleep(1000);
		gcall.Stepto(-46441, -16769, -1619);
		gcall.Stepto(-46650, -16636, -1616);
		gcall.Stepto(-46873, -16692, -1608);
		gcall.Stepto(-46906, -16755, -1609);
		gcall.Stepto(-46906, -16777, -1611);
		//Sleep(2000);
		//gcall.FindThenKill(0, 300, modeNormal | modeAoe | modePickup);
		//gcall.Stepto(-46906, -16755, -1609);
		//gcall.Stepto(-46906, -16777, -1611);
		Sleep(1000);
		gcall.PickupTask();
		Sleep(1000);
		gcall.Stepto(-46995, -16618, -1606);
		gcall.Stepto(-47007, -16598, -1606);
		gcall.Stepto(-47095, -16586, -1616);
		gcall.Stepto(-47137, -16641, -1614);
		//Sleep(2000);
		//gcall.FindThenKill(0, 300, modeNormal | modeAoe | modePickup);
		//gcall.Stepto(-47095, -16586, -1616);
		//gcall.Stepto(-47137, -16641, -1614);
		Sleep(1000);
		gcall.PickupTask();
		gcall.NewSpend(2.5);
		gcall.Stepto(-47184, -16592, -1616);
		gcall.Stepto(-47357, -16416, -1630);
		gcall.Stepto(-47531, -16238, -1619);
		gcall.Stepto(-47751, -16131, -1613);
		gcall.Stepto(-47988, -16060, -1615);
		gcall.Stepto(-48226, -15989, -1607);
		gcall.Stepto(-48468, -15943, -1603);
		gcall.Stepto(-48713, -15983, -1609);
		gcall.Stepto(-48947, -16064, -1612);
		gcall.Stepto(-49039, -16139, -1608);
		gcall.Stepto(-49115, -16297, -1609);
		gcall.Stepto(-49224, -16463, -1607);
		gcall.Stepto(-49318, -16637, -1607);
		gcall.Stepto(-49411, -16812, -1609);
		gcall.NewSpend(1);
		gcall.Stepto(-49506, -16991, -1586);
		gcall.Stepto(-49599, -17166, -1520);
		gcall.Stepto(-49692, -17341, -1485);
		gcall.Stepto(-49785, -17517, -1492);
		gcall.Stepto(-49878, -17692, -1495);
		gcall.Stepto(-49971, -17867, -1496);
		gcall.Stepto(-50064, -18043, -1496);
		gcall.Stepto(-50167, -18212, -1496);
		gcall.Stepto(-50293, -18366, -1494);
		gcall.Stepto(-50428, -18516, -1494);
		gcall.Stepto(-50561, -18663, -1494);
		gcall.Stepto(-50694, -18811, -1494);
		gcall.Stepto(-50746, -18869, -1494);
		gcall.FindThenKill(0, 900, modeNormal | modeAoe | modeGoback | modePickup | modeTask,2);
		Sleep(2000);
		gcall.HeChengWuQi(EQUITMENT_POS::WUQI);
		Sleep(1000);
		gcall.FenJieByConfig();
		Sleep(1000);
		gcall.SortBag();
		break;
	case 3:
		gcall.NewSpend(2.5);
		gcall.Stepto(-50746, -18869, -1494);
		gcall.Stepto(-50640, -18726, -1494);
		gcall.Stepto(-50522, -18567, -1494);
		gcall.Stepto(-50405, -18407, -1494);
		gcall.Stepto(-50291, -18244, -1494);
		gcall.Stepto(-50182, -18079, -1496);
		gcall.Stepto(-50072, -17913, -1496);
		gcall.Stepto(-49971, -17743, -1496);
		gcall.Stepto(-49874, -17569, -1493);
		gcall.Stepto(-49846, -17519, -1493);
		gcall.Stepto(-49806, -17452, -1492);
		gcall.Stepto(-49675, -17241, -1489);
		gcall.Stepto(-49544, -17031, -1568);
		gcall.Stepto(-49414, -16822, -1610);
		gcall.Stepto(-49283, -16611, -1607);
		gcall.Stepto(-49184, -16451, -1608);
		gcall.Stepto(-49161, -16413, -1609);
		gcall.Stepto(-48984, -16243, -1609);
		gcall.Stepto(-48772, -16114, -1615);
		gcall.Stepto(-48539, -16030, -1604);
		gcall.Stepto(-48296, -16006, -1607);
		gcall.Stepto(-48055, -16061, -1615);
		gcall.Stepto(-47816, -16129, -1615);
		gcall.Stepto(-47578, -16197, -1614);
		gcall.Stepto(-47335, -16243, -1627);
		gcall.Stepto(-47087, -16243, -1611);
		gcall.Stepto(-46839, -16243, -1602);
		gcall.Stepto(-46591, -16242, -1604);
		gcall.Stepto(-46343, -16242, -1588);
		gcall.Stepto(-46096, -16260, -1563);
		gcall.Stepto(-45864, -16346, -1524);
		gcall.Stepto(-45649, -16470, -1487);
		gcall.Stepto(-45443, -16610, -1450);
		gcall.Stepto(-45238, -16751, -1437);
		gcall.Stepto(-45033, -16891, -1443);
		gcall.Stepto(-44830, -17034, -1355);
		gcall.Stepto(-44656, -17165, -1269);
		gcall.Stepto(-44498, -17286, -1174);
		gcall.Stepto(-44341, -17407, -1097);
		gcall.Stepto(-44184, -17528, -1011);
		gcall.Stepto(-44024, -17645, -941);
		gcall.Stepto(-43858, -17755, -934);
		gcall.Stepto(-43693, -17864, -935);
		gcall.Stepto(-43527, -17973, -934);
		gcall.Stepto(-43361, -18082, -935);
		gcall.Stepto(-43193, -18193, -935);
		gcall.Stepto(-43027, -18302, -935);
		gcall.Stepto(-42861, -18412, -936);
		gcall.Stepto(-42696, -18521, -933);
		gcall.Stepto(-42530, -18630, -937);
		gcall.Stepto(-42364, -18739, -935);
		gcall.Stepto(-42202, -18853, -933);
		gcall.Stepto(-42053, -18985, -933);
		gcall.Stepto(-41905, -19116, -933);
		gcall.Stepto(-41756, -19248, -929);
		gcall.Stepto(-41608, -19380, -928);
		gcall.Stepto(-41460, -19512, -930);
		gcall.Stepto(-41311, -19644, -933);
		gcall.Stepto(-41158, -19769, -928);
		gcall.Stepto(-41003, -19893, -929);
		gcall.Stepto(-40848, -20017, -931);
		gcall.Stepto(-40690, -20143, -933);
		gcall.Stepto(-40537, -20265, -935);
		gcall.Stepto(-40382, -20389, -935);
		gcall.Stepto(-40227, -20513, -933);
		gcall.Stepto(-40065, -20632, -933);
		gcall.Stepto(-39903, -20747, -939);
		gcall.Stepto(-39743, -20865, -963);
		gcall.Stepto(-39582, -20980, -1018);
		gcall.Stepto(-39421, -21096, -1105);
		gcall.Stepto(-39259, -21211, -1191);
		gcall.Stepto(-39098, -21327, -1258);
		gcall.Stepto(-38937, -21442, -1326);
		gcall.Stepto(-38777, -21560, -1374);
		gcall.Stepto(-38665, -21722, -1411);
		gcall.Stepto(-38602, -21909, -1445);
		gcall.Stepto(-38599, -22106, -1475);
		gcall.Stepto(-38655, -22293, -1463);
		gcall.Stepto(-38742, -22475, -1423);
		gcall.Stepto(-38830, -22653, -1365);
		gcall.Stepto(-38917, -22831, -1338);
		gcall.NewSpend(1);
		Sleep(5000);
		gcall.Stepto(-38935, -22867, -1331);
		gcall.WaitPlans();
		gcall.Stepto(-39042, -23085, -1375);
		gcall.Stepto(-39137, -23316, -1371);
		gcall.NewSpend(2.5);
		gcall.Stepto(-39173, -23563, -1389);
		gcall.Stepto(-39104, -23799, -1395);
		gcall.Stepto(-38970, -24007, -1410);
		gcall.Stepto(-38781, -24164, -1457);
		gcall.Stepto(-38574, -24303, -1511);
		gcall.Stepto(-38368, -24441, -1546);
		gcall.Stepto(-38161, -24580, -1553);
		gcall.Stepto(-37958, -24724, -1537);
		gcall.Stepto(-37781, -24901, -1532);
		gcall.Stepto(-37607, -25078, -1526);
		gcall.Stepto(-37434, -25255, -1512);
		gcall.Stepto(-37260, -25432, -1504);
		gcall.Stepto(-37088, -25612, -1496);
		gcall.Stepto(-36944, -25814, -1477);
		gcall.Stepto(-36792, -26011, -1442);
		gcall.Stepto(-36629, -26198, -1400);
		gcall.Stepto(-36490, -26403, -1368);
		gcall.Stepto(-36351, -26607, -1360);
		gcall.Stepto(-36212, -26813, -1369);
		gcall.Stepto(-36073, -27019, -1402);
		gcall.Stepto(-35923, -27217, -1393);
		gcall.Stepto(-35744, -27390, -1377);
		gcall.Stepto(-35544, -27535, -1354);
		gcall.Stepto(-35327, -27636, -1341);
		gcall.Stepto(-35076, -27692, -1331);
		gcall.Stepto(-34826, -27708, -1313);
		gcall.Stepto(-34582, -27692, -1294);
		gcall.Stepto(-34335, -27657, -1284);
		gcall.Stepto(-34096, -27586, -1269);
		gcall.Stepto(-33859, -27507, -1230);
		gcall.Stepto(-33626, -27428, -1191);
		gcall.Stepto(-33390, -27348, -1176);
		gcall.Stepto(-33158, -27262, -1169);
		gcall.Stepto(-32929, -27166, -1161);
		gcall.Stepto(-32696, -27068, -1160);
		gcall.Stepto(-32471, -26965, -1162);
		gcall.Stepto(-32247, -26858, -1155);
		gcall.Stepto(-32036, -26736, -1148);
		gcall.Stepto(-31824, -26603, -1144);
		gcall.Stepto(-31618, -26457, -1123);
		gcall.Stepto(-31418, -26315, -1100);
		gcall.Stepto(-31213, -26171, -1084);
		gcall.Stepto(-31000, -26045, -1008);
		gcall.Stepto(-30777, -25936, -994);
		gcall.Stepto(-30584, -25845, -990);
		gcall.Stepto(-30678, -25728, -991);
		gcall.NewSpend(1);
		Sleep(1000);
		gcall.DeliverQuests(346, 5,L"육지평");
		Sleep(1000);
		gcall.DeliverQuests(307,taskid,L"기봉사");
		Sleep(2000);
		break;
	case 4:
		gcall.LinQuJiangLi();
		Sleep(1000);
		gcall.JiaBaoShi(0, L"거와의 삼각 자수정");
		Sleep(1000);
		//Lianji6_go();
		//while (true)
		//{
			//_BAGSTU goods;
			//gcall.GetGoodsByEquipPos(EQUITMENT_POS::WUQI, &goods);

			////如果等级5, 而且经验满

			//if (goods.m_DangQianJingYanZhi == goods.m_DangQianJingYanZongZhi)
			//{
			//	if (goods.m_PingJi == 5 ||
			//		goods.m_PingJi == 10)
			//	{
			//		log(_T("洪门已经满级,准备突破5"));//洪门武器已满

			//		//gcall.WearEquipment(L"천령도끼 1단계", EQUITMENT_POS::WUQI);
			//		//Sleep(500);
			//		//gcall.WearEquipment(L"천령도끼 2단계", EQUITMENT_POS::WUQI);
			//		//Sleep(500);
			//		//gcall.WearEquipment(L"천령도끼 3단계", EQUITMENT_POS::WUQI);
			//		//Sleep(500);
			//		//gcall.WearEquipment(L"천령도끼 4단계", EQUITMENT_POS::WUQI);
			//		//Sleep(500);
			//		//gcall.WearEquipment(L"천령도끼 5단계", EQUITMENT_POS::WUQI);
			//		//Sleep(500);
			//		//gcall.HeChengWuQi(EQUITMENT_POS::WUQI);
			//		//Sleep(2000);
			//		//gcall.HeChengWuQiByHun(EQUITMENT_POS::WUQI);
			//		//Sleep(2000);
			//		gcall.HeChengWuQi_Po5(EQUITMENT_POS::WUQI, L"천령도끼");
			//		Sleep(2000);
			//		/*				gcall.LinQuJiangLi();
			//						Sleep(2000);
			//						gcall.JiaBaoShi(0, L"삼각 자수정");
			//						Sleep(2000);*/
			//		//break;
			//		Lianji6();
			//	}
			//	else
			//	{
			//		Lianji6();
			//	}
			//}else
			//{
			//	Lianji6();
			//}
			//if (gcall.GetPlayerLevel()>5)
			//{
				//break;
			//}
			//else
			//{
				//Lianji6();
			//}
			//Sleep(100);
		//}
		//MessageBox(0, L"6级完", 0, MB_OK);
		//while (true)
		//{
			//DWORD pStartAddr = gcall.GetTaskStartAddr();//获取任务开始地址

			//DWORD info = gcall.GetPresentTaskIndexes(0, pStartAddr);//获得当前做到第几个小任务

			//if (info > 4)
			//{
			//	break;
			//}
			gcall.NewSpend(2.5);
			gcall.Stepto(-39093, -23304, -1370);
			gcall.Stepto(-39158, -23480, -1363);
			gcall.Stepto(-39210, -23658, -1403);
			gcall.Stepto(-39166, -23838, -1395);
			gcall.Stepto(-39101, -24012, -1396);
			gcall.Stepto(-38953, -24124, -1422);
			gcall.Stepto(-38787, -24210, -1463);
			gcall.Stepto(-38618, -24289, -1501);
			gcall.Stepto(-38447, -24363, -1536);
			gcall.Stepto(-38273, -24429, -1550);
			gcall.Stepto(-38096, -24488, -1545);
			gcall.Stepto(-37925, -24545, -1519);
			gcall.Stepto(-37757, -24601, -1496);
			gcall.Stepto(-37577, -24649, -1480);
			gcall.Stepto(-37397, -24695, -1469);
			gcall.Stepto(-37215, -24735, -1459);
			gcall.Stepto(-37032, -24772, -1450);
			gcall.Stepto(-36849, -24808, -1457);
			gcall.Stepto(-36665, -24844, -1448);
			gcall.Stepto(-36483, -24881, -1421);
			gcall.Stepto(-36300, -24917, -1381);
			gcall.Stepto(-36116, -24952, -1341);
			gcall.Stepto(-35932, -24978, -1309);
			gcall.Stepto(-35743, -24990, -1283);
			gcall.Stepto(-35560, -24956, -1255);
			gcall.Stepto(-35378, -24917, -1250);
			gcall.Stepto(-35197, -24877, -1231);
			gcall.Stepto(-35019, -24822, -1210);
			gcall.Stepto(-34839, -24762, -1201);
			gcall.Stepto(-34660, -24701, -1191);
			gcall.Stepto(-34474, -24688, -1183);
			gcall.Stepto(-34291, -24723, -1181);
			gcall.Stepto(-34111, -24769, -1178);
			gcall.Stepto(-33929, -24815, -1164);
			gcall.Stepto(-33748, -24857, -1148);
			gcall.Stepto(-33566, -24897, -1136);
			gcall.Stepto(-33385, -24940, -1124);
			gcall.Stepto(-33203, -24983, -1103);
			gcall.Stepto(-33021, -25026, -1084);
			gcall.Stepto(-32840, -25068, -1068);
			gcall.Stepto(-32658, -25111, -1055);
			gcall.Stepto(-32475, -25154, -1045);
			gcall.Stepto(-32294, -25196, -1042);
			gcall.Stepto(-32111, -25234, -1035);
			gcall.Stepto(-31927, -25267, -1028);
			gcall.Stepto(-31744, -25301, -1021);
			gcall.Stepto(-31559, -25334, -1014);
			gcall.Stepto(-31376, -25367, -1004);
			gcall.Stepto(-31192, -25401, -997);
			gcall.Stepto(-31008, -25434, -990);
			gcall.Stepto(-30825, -25471, -986);
			gcall.Stepto(-30645, -25522, -991);
			gcall.Stepto(-30514, -25604, -991);
			gcall.NewSpend(1);
			Sleep(1000);
			gcall.SellItemByConfig(L"이화상");
			Sleep(1000);
			gcall.NewSpend(2.5);
			gcall.Stepto(-30461,-25703,-991);
			gcall.Stepto(-30577,-25290,-972);
			gcall.Stepto(-30620,-25042,-957);
			gcall.Stepto(-30661,-24794,-972);
			gcall.Stepto(-30671,-24542,-990);
			gcall.Stepto(-30629,-24295,-997);
			gcall.Stepto(-30584,-24048,-989);
			gcall.Stepto(-30539,-23801,-983);
			gcall.Stepto(-30493,-23552,-989);
			gcall.Stepto(-30448,-23304,-1004);
			gcall.Stepto(-30400,-23056,-1021);
			gcall.Stepto(-30348,-22811,-1031);
			gcall.Stepto(-30281,-22569,-1032);
			gcall.Stepto(-30189,-22335,-1030);
			gcall.Stepto(-30053,-22124,-1002);
			gcall.Stepto(-29903,-21920,-962);
			gcall.Stepto(-29747,-21722,-935);
			gcall.Stepto(-29592,-21524,-922);
			gcall.NewSpend(1);
			gcall.Stepto(-29437,-21328,-911);
			gcall.Stepto(-29271,-21141,-901);
			gcall.Stepto(-29068,-20994,-883);
			//gcall.NewSpend(1);
			/*过滤怪物(야생곰, 1);
			过滤怪物(흑룡채 보초병, 2);*/ //现在没有过滤怪物先上用

			gcall.FindThenKill(0, 1000, modeNormal | modeAoe | modePickup);
			//gcall.NewSpend(2.5);
			gcall.Stepto(-28851,-20901,-851);
			gcall.Stepto(-28651,-20872,-831);
			gcall.Stepto(-28450,-20858,-819);
			gcall.Stepto(-28249,-20845,-805);
			gcall.Stepto(-28050,-20824,-779);
			gcall.Stepto(-27849,-20803,-756);
			gcall.Stepto(-27648,-20781,-733);
			gcall.Stepto(-27449,-20759,-728);
			gcall.Stepto(-27249,-20684,-734);
			gcall.Stepto(-27103,-20529,-726);
			gcall.Stepto(-26976,-20374,-733);
			gcall.Stepto(-26804,-20202,-735);
			gcall.Stepto(-26633,-20095,-735);
			gcall.Stepto(-26654,-19884,-735);
			//gcall.NewSpend(1);
			gcall.FindThenKill(0, 450, modeNormal | modeAoe | modePickup);
			gcall.Stepto(-26845,-20027,-735);
			gcall.Stepto(-27045,-20177,-735);
			gcall.Stepto(-27247,-20328,-732);
			gcall.Stepto(-27449,-20480,-735);
			gcall.Stepto(-27692,-20392,-759);
			gcall.Stepto(-27906,-20262,-794);
			gcall.Stepto(-28118,-20128,-820);
			gcall.Stepto(-28331,-19994,-834);
			gcall.Stepto(-28544,-19859,-841);
			gcall.Stepto(-28756,-19724,-861);
			gcall.Stepto(-28958,-19579,-901);
			gcall.Stepto(-29147,-19414,-915);
			gcall.Stepto(-29336,-19248,-909);
			gcall.Stepto(-29527,-19081,-901);
			gcall.Stepto(-29716,-18916,-896);
			gcall.Stepto(-29906,-18750,-902);
			gcall.Stepto(-30100,-18580,-920);
			gcall.Stepto(-30289,-18415,-940);
			gcall.Stepto(-30496,-18466,-950);
			gcall.Stepto(-30558,-18710,-932);
			gcall.Stepto(-30658,-18938,-906);
			gcall.Stepto(-30812,-19136,-899);
			gcall.Stepto(-30954,-19341,-914);

			gcall.FindThenKill(0, 450, modeNormal | modeAoe | modePickup);
			//gcall.NewSpend(2.5);
			gcall.Stepto(-31068,-19132,-873);
			gcall.Stepto(-31164,-18956,-853);
			gcall.Stepto(-31260,-18779,-851);
			gcall.Stepto(-31390,-18614,-832);
			gcall.Stepto(-31534,-18440,-825);
			gcall.Stepto(-31666,-18288,-825);
			gcall.Stepto(-31800,-18138,-825);

			//gcall.NewSpend(1);
			gcall.FindThenKill(0, 450, modeNormal | modeAoe | modePickup);
			gcall.Stepto(-31722,-18325,-825);
			gcall.Stepto(-31635,-18560,-825);
			gcall.Stepto(-31547,-18796,-826);
			gcall.Stepto(-31460,-19032,-828);
			gcall.Stepto(-31578,-19210,-827);
			gcall.Stepto(-31804,-19315,-843);
			gcall.Stepto(-32028,-19429,-861);
			gcall.Stepto(-32242,-19563,-839);
			gcall.Stepto(-32349,-19733,-842);
			gcall.Stepto(-32379,-19984,-856);
			gcall.Stepto(-32409,-20184,-864);
			gcall.Stepto(-32435,-20404,-875);
			gcall.Stepto(-32454,-20640,-875);
			gcall.Stepto(-32460,-20892,-883);
			gcall.Stepto(-32454,-21142,-913);
			Sleep(2000);
			gcall.FindThenKill(0, 300, modeNormal | modeAoe | modePickup);
			gcall.NewSpend(2.5);
			gcall.Stepto(-32398,-21364,-933);
			gcall.Stepto(-32284,-21529,-954);
			gcall.Stepto(-32173,-21698,-986);
			gcall.Stepto(-32043,-21911,-1024);
			gcall.Stepto(-31948,-22090,-1022);
			gcall.Stepto(-31851,-22277,-1015);
			gcall.Stepto(-31733,-22501,-1008);
			gcall.Stepto(-31617,-22724,-1004);
			gcall.Stepto(-31500,-22946,-1009);
			gcall.Stepto(-31383,-23170,-1025);
			gcall.Stepto(-31267,-23392,-1010);
			gcall.Stepto(-31151,-23615,-977);
			gcall.Stepto(-31034,-23836,-955);
			gcall.NewSpend(1);
			gcall.randXianlu(0);
			Sleep(1000);
			//任务需改，暂时没想好逻辑怎么写。

		//}
		break;
	case 5:
		gcall.NewSpend(2.5);
		gcall.Stepto(-31579, -22062, -1028,10,20,3000);
		gcall.Stepto(-31537, -21821, -1041);
		gcall.Stepto(-31480, -21586, -1025);
		gcall.Stepto(-31365, -21366, -1000);
		gcall.Stepto(-31254, -21143, -974);
		gcall.Stepto(-31259, -20895, -956);
		gcall.Stepto(-31292, -20648, -941);
		gcall.Stepto(-31327, -20402, -926);
		gcall.Stepto(-31362, -20156, -912);
		gcall.Stepto(-31385, -19910, -904);
		gcall.Stepto(-31259, -19697, -914);
		gcall.Stepto(-31134, -19482, -917);
		gcall.Stepto(-31011, -19273, -902);
		gcall.Stepto(-30903, -19104, -890);
		gcall.Stepto(-30796, -18932, -900);
		gcall.Stepto(-30690, -18761, -924);
		gcall.Stepto(-30559, -18550, -944);
		gcall.Stepto(-30433, -18345, -954);
		gcall.Stepto(-30303, -18131, -960);
		gcall.Stepto(-30182, -17914, -950);
		gcall.Stepto(-30071, -17724, -921);
		gcall.Stepto(-29944, -17510, -865);
		gcall.Stepto(-29817, -17296, -821);
		gcall.Stepto(-29690, -17081, -782);
		gcall.Stepto(-29594, -16890, -733);
		gcall.Stepto(-29561, -16643, -685);
		gcall.Stepto(-29562, -16395, -689);
		gcall.NewSpend(1);
		Sleep(5000);
		gcall.Stepto(-29576, -16167, -704);
		gcall.WaitPlans();
		gcall.Stepto(-29592, -15967, -717);
		gcall.WaitPlans();
		gcall.NewSpend(2.5);
		gcall.Stepto(-29610, -15759, -738);
		gcall.Stepto(-29641, -15513, -813);
		gcall.Stepto(-29668, -15266, -927);
		gcall.Stepto(-29695, -15018, -1070);
		gcall.Stepto(-29722, -14772, -1215);
		gcall.Stepto(-29748, -14525, -1258);
		gcall.Stepto(-29772, -14277, -1308);
		gcall.Stepto(-29795, -14030, -1389);
		gcall.Stepto(-29819, -13783, -1499);
		gcall.Stepto(-29843, -13536, -1588);
		gcall.Stepto(-29868, -13289, -1666);
		gcall.Stepto(-29952, -13103, -1709);
		gcall.NewSpend(1);
		Sleep(1000);
		gcall.DeliverQuests(307, taskid, L"기봉사");
		Sleep(1000);
		break;
	}

}

void TaskScript::Task_308(int zid,int taskid)
{
	switch (taskid)
	{
	case 1:
		/*gcall.JieFengHezi(L"잠긴 천령무기",0,L"제룡림 열쇠",1);
		MessageBox(0, L"摇奖完", L"装八卦", MB_OK);*/
		//这里应该摇奖，但是只执行一次，先判断背包里是否还有 L"천령강시의 정수" 如果已经没有了，就上执行这里了。

		_BAGSTU jingqi;
		while (gcall.GetGoodsFromBagByName(L"천령강시의 정수", &jingqi))
		{
			gcall.CityConvey(2);
			Sleep(2000);
			gcall.Stepto(-35888, -38107, -374);
			gcall.Stepto(-35639, -38093, -374);
			gcall.Stepto(-35389, -38080, -374);
			gcall.Stepto(-35141, -38098, -374);
			Sleep(1000);
			gcall.HeChengWuQi(EQUITMENT_POS::WUQI);
			Sleep(1000);
			gcall.SellItemByConfig(L"무료한");
			Sleep(1000);
			gcall.Stepto(-35021, -38264, -374);
			gcall.Stepto(-34927, -38496, -374);
			gcall.Stepto(-34788, -38701, -374);
			Sleep(1000);
			gcall.Yaojiang(L"천령강시의 정수", L"천령보패");
			Sleep(1000);
			gcall.Stepto(-34787, -38701, -374);
			gcall.Stepto(-34903, -38493, -374);
			gcall.Stepto(-35032, -38280, -374);
			gcall.Stepto(-35120, -38097, -374);
			Sleep(1000);
			gcall.SellItemByConfig(L"무료한");
			Sleep(1000);
		}
		gcall.NewSpend(2.5);
		gcall.Stepto(-35275, -37916, -374);
		gcall.Stepto(-35327, -37677, -373);
		gcall.Stepto(-35249, -37443, -379);
		gcall.Stepto(-35140, -37220, -386);
		gcall.Stepto(-35040, -36993, -413);
		gcall.Stepto(-34966, -36757, -462);
		gcall.Stepto(-34956, -36510, -515);
		gcall.Stepto(-35029, -36275, -593);
		gcall.Stepto(-35201, -36097, -662);
		gcall.Stepto(-35390, -35936, -760);
		gcall.Stepto(-35545, -35744, -863);
		gcall.Stepto(-35507, -35529, -923);
		gcall.Stepto(-35275, -35447, -960);
		gcall.Stepto(-35030, -35410, -1011);
		gcall.Stepto(-34782, -35397, -1044);
		gcall.Stepto(-34536, -35372, -1061);
		gcall.Stepto(-34296, -35311, -1090);
		gcall.Stepto(-34093, -35173, -1123);
		gcall.Stepto(-34052, -34932, -1153);
		gcall.Stepto(-34138, -34698, -1169);
		gcall.Stepto(-34214, -34462, -1164);
		gcall.Stepto(-34239, -34215, -1169);
		gcall.Stepto(-34232, -33967, -1214);
		gcall.Stepto(-34203, -33721, -1293);
		gcall.Stepto(-34165, -33476, -1350);
		gcall.Stepto(-34107, -33235, -1375);
		gcall.Stepto(-34043, -32995, -1391);
		gcall.Stepto(-33979, -32752, -1389);
		gcall.Stepto(-33913, -32503, -1414);
		gcall.Stepto(-33850, -32264, -1441);
		gcall.Stepto(-33783, -32025, -1441);
		gcall.Stepto(-33715, -31786, -1420);
		gcall.Stepto(-33647, -31548, -1378);
		gcall.Stepto(-33578, -31309, -1360);
		gcall.Stepto(-33510, -31071, -1373);
		gcall.Stepto(-33441, -30833, -1387);
		gcall.Stepto(-33373, -30594, -1401);
		gcall.Stepto(-33304, -30356, -1396);
		gcall.Stepto(-33236, -30118, -1365);
		gcall.Stepto(-33167, -29879, -1302);
		gcall.Stepto(-33098, -29640, -1274);
		gcall.Stepto(-33029, -29401, -1267);
		gcall.Stepto(-32961, -29163, -1262);
		gcall.Stepto(-32892, -28924, -1256);
		gcall.Stepto(-32823, -28686, -1254);
		gcall.Stepto(-32739, -28451, -1255);
		gcall.Stepto(-32594, -28248, -1259);
		gcall.Stepto(-32473, -28031, -1251);
		gcall.Stepto(-32356, -27810, -1238);
		gcall.Stepto(-32240, -27590, -1228);
		gcall.Stepto(-32130, -27367, -1216);
		gcall.Stepto(-32022, -27144, -1203);
		gcall.Stepto(-31915, -26920, -1182);
		gcall.Stepto(-31810, -26696, -1156);
		gcall.Stepto(-31722, -26464, -1122);
		gcall.Stepto(-31641, -26229, -1095);
		gcall.Stepto(-31562, -25994, -1073);
		gcall.Stepto(-31479, -25760, -1041);
		gcall.Stepto(-31395, -25527, -1015);
		gcall.Stepto(-31311, -25293, -998);
		gcall.Stepto(-31227, -25060, -987);
		gcall.Stepto(-31143, -24826, -976);
		gcall.Stepto(-31059, -24593, -969);
		gcall.Stepto(-30975, -24357, -964);
		gcall.Stepto(-30891, -24123, -960);
		gcall.Stepto(-30807, -23890, -961);
		gcall.Stepto(-30723, -23656, -973);
		gcall.Stepto(-30639, -23423, -995);
		gcall.Stepto(-30555, -23189, -1013);
		gcall.Stepto(-30471, -22955, -1022);
		gcall.Stepto(-30391, -22721, -1030);
		gcall.Stepto(-30310, -22486, -1037);
		gcall.Stepto(-30230, -22252, -1030);
		gcall.Stepto(-30148, -22016, -1006);
		gcall.Stepto(-30056, -21785, -979);
		gcall.Stepto(-29964, -21555, -958);
		gcall.Stepto(-29873, -21324, -940);
		gcall.Stepto(-29782, -21094, -929);
		gcall.Stepto(-29690, -20863, -912);
		gcall.Stepto(-29599, -20631, -903);
		gcall.Stepto(-29507, -20400, -898);
		gcall.Stepto(-29440, -20162, -897);
		gcall.Stepto(-29426, -19914, -904);
		gcall.Stepto(-29436, -19667, -907);
		gcall.Stepto(-29456, -19419, -906);
		gcall.Stepto(-29478, -19172, -901);
		gcall.Stepto(-29511, -18927, -911);
		gcall.Stepto(-29539, -18680, -921);
		gcall.Stepto(-29565, -18433, -920);
		gcall.Stepto(-29597, -18182, -897);
		gcall.Stepto(-29631, -17936, -869);
		gcall.Stepto(-29664, -17689, -830);
		gcall.Stepto(-29669, -17442, -800);
		gcall.Stepto(-29658, -17194, -788);
		gcall.Stepto(-29633, -16947, -749);
		gcall.Stepto(-29607, -16700, -711);
		gcall.Stepto(-29581, -16454, -685);
		gcall.Stepto(-29579,-16269, -697);
		gcall.NewSpend(1);
		Sleep(6000);
		gcall.Stepto(-29579,-16229,-700);
		gcall.WaitPlans();
		gcall.Stepto(-29596,-16126,-706);
		gcall.WaitPlans();
		gcall.Stepto(-29588,-15927,-725);
		

		/*
		gcall.Stepto(-29611,-15857,-732);
		gcall.Stepto(-29626,-15608,-775);
		gcall.Stepto(-29640,-15360,-882);
		gcall.Stepto(-29661,-15113,-1009);
		gcall.Stepto(-29683,-14866,-1167);
		gcall.Stepto(-29703,-14618,-1244);
		gcall.Stepto(-29723,-14371,-1293);
		gcall.Stepto(-29744,-14124,-1353);
		gcall.Stepto(-29764,-13876,-1456);
		gcall.Stepto(-29784,-13627,-1548);
		gcall.Stepto(-29805,-13380,-1633);
		gcall.Stepto(-29825,-13131,-1706);
		gcall.Stepto(-29845,-12884,-1750);
		gcall.Stepto(-30001,-12720,-1789);
		gcall.Stepto(-30216,-12591,-1819);
		gcall.Stepto(-30460,-12519,-1788);
		gcall.Stepto(-30708,-12543,-1728);
		gcall.Stepto(-30955,-12569,-1676);
		gcall.Stepto(-31202,-12597,-1676);
		gcall.Stepto(-31451,-12624,-1685);
		gcall.Stepto(-31655,-12679,-1682);
		gcall.Stepto(-31823,-12862,-1676);
		gcall.Stepto(-31983,-13051,-1676);
		gcall.Stepto(-32038,-13291,-1677);
		gcall.Stepto(-32055,-13539,-1676);
		gcall.Stepto(-32061,-13787,-1675);
		gcall.Stepto(-32089,-14032,-1675);
		gcall.Stepto(-32223,-14240,-1675);
		gcall.Stepto(-32444,-14343,-1675);
		gcall.Stepto(-32693,-14353,-1679);
		gcall.Stepto(-32945,-14346,-1650);
		gcall.Stepto(-33194,-14345,-1704);
		gcall.Stepto(-33442,-14342,-1704);
		gcall.Stepto(-33690,-14343,-1704);
		gcall.Stepto(-33938,-14343,-1704);
		gcall.Stepto(-34187,-14345,-1704);
		gcall.Stepto(-34435,-14349,-1704);
		gcall.Stepto(-34686,-14354,-1704);
		gcall.Stepto(-34934,-14357,-1704);
		gcall.Stepto(-35182,-14363,-1704);
		gcall.Stepto(-35429,-14353,-1704);
		gcall.Stepto(-35647,-14238,-1709);
		gcall.Stepto(-35725,-14008,-1716);
		gcall.Stepto(-35730,-13758,-1716);
		gcall.Stepto(-35728,-13510,-1716);
		gcall.Stepto(-35726,-13258,-1709);
		gcall.Stepto(-35726,-13009,-1713);
		gcall.Stepto(-35802,-12775,-1713);
		gcall.Stepto(-35973,-12598,-1713);
		gcall.Stepto(-36188,-12469,-1713);
		gcall.Stepto(-36429,-12412,-1713);
		gcall.Stepto(-36679,-12412,-1707);
		gcall.Stepto(-36928,-12416,-1582);
		gcall.Stepto(-37177,-12417,-1430);
		gcall.Stepto(-37426,-12418,-1416);
		gcall.Stepto(-37676,-12419,-1416);
		gcall.Stepto(-37925,-12420,-1411);
		gcall.Stepto(-38176,-12419,-1411);
		gcall.Stepto(-38424,-12418,-1409);
		gcall.Stepto(-38673,-12417,-1409);
		gcall.Stepto(-38921,-12415,-1409);
		*/
		
		Sleep(1000);
		gcall.Shunyi(L"1-9-1");
		Sleep(1000);
		gcall.sendcall(id_msg_OverShunyi,(LPVOID)0);//unhook
		Sleep(2000);
		gcall.Stepto(-38305, -12425, -1411);
		gcall.Stepto(-38509, -12426, -1409);
		gcall.Stepto(-38710, -12423, -1409);
		gcall.Stepto(-38947, -12418, -1409);
		gcall.FindThenKill(0, 600, modeNormal | modeAoe | modePickup);
		gcall.Stepto(-38947, -12418, -1409);
		Sleep(1000);
		break;
	case 2:
		gcall.Stepto(-38947, -12418, -1409);
		Sleep(1000);
		gcall.PickupSpecTypeTask(200,0x4,L"약탈 의뢰서");
		Sleep(1000);
		gcall.Stepto(-39052, -12237, -1409);
		gcall.Stepto(-39249, -12029, -1409);
		gcall.Stepto(-39506, -11897, -1416);
		Sleep(1000);
		gcall.PickupTask();
		Sleep(1000);
		gcall.Stepto(-39308, -11900, -1416,10,20,2500);
		Sleep(1000);
		gcall.Shunyi(L"1-9-2");
		Sleep(1000);
		gcall.sendcall(id_msg_OverShunyi,(LPVOID)0);//unhook
		Sleep(8000);
		gcall.Stepto(-29590, -16033, -713);
		gcall.Stepto(-29566, -16394, -689);
		gcall.WaitPlans();
		break;
	case 3:
		/*gcall.NewSpend(2);
		gcall.Stepto(-38879, -12426, -1409);
		gcall.Stepto(-38631, -12434, -1409);
		gcall.Stepto(-38383, -12442, -1411);
		gcall.Stepto(-38335, -12444, -1411);
		gcall.Stepto(-38253, -12449, -1411);
		gcall.Stepto(-38005, -12452, -1411);
		gcall.Stepto(-37757, -12454, -1414);
		gcall.Stepto(-37509, -12456, -1416);
		gcall.Stepto(-37261, -12458, -1416);
		gcall.Stepto(-37014, -12461, -1529);
		gcall.Stepto(-36766, -12460, -1680);
		gcall.Stepto(-36518, -12445, -1707);
		gcall.Stepto(-36271, -12430, -1713);
		gcall.Stepto(-36040, -12508, -1713);
		gcall.Stepto(-35857, -12668, -1713);
		gcall.Stepto(-35744, -12888, -1713);
		gcall.Stepto(-35704, -13130, -1706);
		gcall.Stepto(-35692, -13377, -1712);
		gcall.Stepto(-35690, -13625, -1716);
		gcall.Stepto(-35689, -13874, -1716);
		gcall.Stepto(-35677, -14121, -1709);
		gcall.Stepto(-35517, -14297, -1709);
		gcall.Stepto(-35287, -14387, -1704);
		gcall.Stepto(-35040, -14402, -1704);
		gcall.Stepto(-34792, -14405, -1704);
		gcall.Stepto(-34544, -14406, -1704);
		gcall.Stepto(-34296, -14407, -1704);
		gcall.Stepto(-34048, -14408, -1704);
		gcall.Stepto(-33800, -14398, -1704);
		gcall.Stepto(-33553, -14379, -1704);
		gcall.Stepto(-33306, -14361, -1704);
		gcall.Stepto(-33059, -14342, -1650);
		gcall.Stepto(-32811, -14324, -1650);
		gcall.Stepto(-32564, -14305, -1675);
		gcall.Stepto(-32327, -14230, -1675);
		gcall.Stepto(-32157, -14054, -1675);
		gcall.Stepto(-32071, -13821, -1673);
		gcall.Stepto(-31997, -13585, -1679);
		gcall.Stepto(-31941, -13343, -1678);
		gcall.Stepto(-31882, -13102, -1676);
		gcall.Stepto(-31769, -12881, -1676);
		gcall.Stepto(-31589, -12711, -1687);
		gcall.Stepto(-31389, -12564, -1680);
		gcall.Stepto(-31160, -12470, -1676);
		gcall.Stepto(-30914, -12469, -1684);
		gcall.Stepto(-30667, -12492, -1740);
		gcall.Stepto(-30421, -12514, -1792);
		gcall.Stepto(-30177, -12564, -1819);
		gcall.Stepto(-29972, -12694, -1792);
		gcall.Stepto(-29865, -12914, -1747);
		gcall.Stepto(-29806, -13154, -1698);
		gcall.Stepto(-29770, -13400, -1621);
		gcall.Stepto(-29745, -13646, -1536);
		gcall.Stepto(-29759, -13898, -1447);
		gcall.Stepto(-29774, -14146, -1344);
		gcall.Stepto(-29755, -14393, -1290);
		gcall.Stepto(-29732, -14640, -1242);
		gcall.Stepto(-29709, -14884, -1159);
		gcall.Stepto(-29685, -15135, -999);
		gcall.Stepto(-29661, -15382, -874);
		gcall.Stepto(-29638, -15628, -768);
		gcall.Stepto(-29614, -15875, -731);
		gcall.Stepto(-29591, -16120, -707);
		gcall.NewSpend(1);
		gcall.Stepto(-29575, -16292, -696);
		gcall.WaitPlans();
		gcall.Stepto(-29565, -16407, -688);
		gcall.WaitPlans();
		gcall.Stepto(-29562, -16655, -691);
		gcall.NewSpeed(1);
		*/
		lianji8_go();

		//打到9级，之后再继续任务。

		while (true)
		{
			if (gcall.GetPlayerLevel()<10)
			{
				UseExperience();
				lianji8();
			}else
			{
				//出副本

				BOOL steprs;
				steprs = FALSE;
				steprs = gcall.Stepto(-35566, -12217, -1713,10,20,2500);
				if (steprs == TRUE)
				{
					//gcall.Stepto(-39308, -11900, -1416,10,20,2500);old
					ShunYiResult(2000,L"Lianji8-end",TRUE);
					Sleep(5000);
					//Sleep(1000);
					//gcall.Shunyi(L"Lianji8-mai-men");
					//Sleep(3000);
					//gcall.sendcall(id_msg_OverShunyi,(LPVOID)0);//hook
					//Sleep(3000);
					ShunYiResult(2000,L"Lianji8-mai-men",FALSE);
					gcall.WaitPlans();
					gcall.HeChengWuQi(EQUITMENT_POS::WUQI);
					Sleep(1000);
					gcall.BuqiBaGua(L"충각 치명보패");
					Sleep(1000);
					gcall.FenJieByConfig();
				}
				//走向能瞬移的坐标才操作瞬移，如果掉线，肯定就在门口了。

				break;
			}
			//if (gcall.GetPlayerLevel()>9)
			//{
			//	
			//	i++;
			//	if (i > 3)
			//	{
			//		//貌似韩朊改了，没这些了。

			//		gcall.JieFengZhuangBei(L"봉인된 제룡목걸이", L"제룡 봉인해제 부적", 1);
			//		Sleep(1000);
			//		gcall.WearEquipment(L"제룡목걸이 1단계", 7);
			//		Sleep(1000);
			//		gcall.JieFengZhuangBei(L"봉인된 제룡반지", L"제룡 봉인해제 부적", 1);
			//		Sleep(1000);
			//		gcall.WearEquipment(L"제룡반지 1단계", 6);
			//		Sleep(1000);
			//		gcall.JieFengZhuangBei(L"봉인된 제룡귀걸이", L"제룡 봉인해제 부적", 1);
			//		Sleep(1000);
			//		gcall.WearEquipment(L"제룡귀걸이 1단계", 3);
			//		Sleep(1000);
			//		break;
			//	}
			//	else
			//	{
			//		lianji8();
			//	}
			//}
			//else
			//{
			//	lianji8();
			//}
		}
		gcall.sendcall(id_msg_OverShunyi,(LPVOID)0);//hook
		Sleep(3000);
		gcall.Stepto(-29571, -16902, -734);
		gcall.Stepto(-29582, -17151, -771);
		gcall.NewSpend(2.5);
		gcall.Stepto(-29583, -17397, -776);
		gcall.Stepto(-29569, -17645, -798);
		gcall.Stepto(-29554, -17891, -841);
		gcall.Stepto(-29539, -18142, -882);
		gcall.Stepto(-29524, -18391, -912);
		gcall.Stepto(-29509, -18635, -924);
		gcall.Stepto(-29493, -18887, -915);
		gcall.Stepto(-29478, -19134, -902);
		gcall.Stepto(-29463, -19382, -904);
		gcall.Stepto(-29448, -19626, -909);
		gcall.Stepto(-29432, -19875, -904);
		gcall.Stepto(-29428, -19945, -903);
		gcall.Stepto(-29425, -20035, -900);
		gcall.Stepto(-29464, -20280, -897);
		gcall.Stepto(-29571, -20499, -899);
		gcall.Stepto(-29782, -20628, -914);
		gcall.Stepto(-29999, -20750, -931);
		gcall.Stepto(-30202, -20890, -948);
		gcall.Stepto(-30369, -21077, -964);
		gcall.Stepto(-30510, -21276, -979);
		gcall.Stepto(-30628, -21495, -998);
		gcall.Stepto(-30697, -21737, -1028);
		gcall.Stepto(-30753, -21977, -1051);
		gcall.Stepto(-30807, -22209, -1058);
		gcall.Stepto(-30808, -22211, -1058);
		gcall.Stepto(-30833, -22315, -1053);
		gcall.Stepto(-30914, -22551, -1048);
		gcall.Stepto(-30996, -22785, -1055);
		gcall.Stepto(-31077, -23017, -1050);
		gcall.Stepto(-31139, -23258, -1024);
		gcall.Stepto(-31144, -23508, -990);
		gcall.Stepto(-31146, -23753, -963);
		gcall.Stepto(-31149, -24005, -946);
		gcall.Stepto(-31152, -24250, -942);
		gcall.Stepto(-31151, -24499, -961);
		gcall.Stepto(-31136, -24747, -974);
		gcall.Stepto(-31120, -24994, -979);
		gcall.Stepto(-31074, -25239, -984);
		gcall.Stepto(-30991, -25474, -991);
		gcall.Stepto(-30835, -25662, -991);
		gcall.Stepto(-30606, -25765, -991);
		gcall.Stepto(-30522, -25796, -990);
		gcall.NewSpend(1);
		Sleep(1000);
		gcall.DeliverQuests(308,taskid,L"기봉사");
		Sleep(1000);
		gcall.SellItemByConfig(L"이화상");
		Sleep(1000);
		gcall.SortBag();
		Sleep(1000);
		break;
	case 4:
		gcall.NewSpend(2.5);
		gcall.Stepto(-29582, -16456, -684);
		gcall.Stepto(-29587, -16512, -680);
		gcall.Stepto(-29662, -16746, -715);
		gcall.Stepto(-29764, -16974, -779);
		gcall.Stepto(-29851, -17205, -817);
		gcall.Stepto(-29940, -17438, -857);
		gcall.Stepto(-30028, -17671, -907);
		gcall.Stepto(-30116, -17904, -944);
		gcall.Stepto(-30199, -18136, -960);
		gcall.Stepto(-30127, -18351, -943);
		gcall.Stepto(-30010, -18571, -923);
		gcall.Stepto(-29915, -18799, -895);
		gcall.Stepto(-29836, -19035, -882);
		gcall.Stepto(-29766, -19271, -890);
		gcall.Stepto(-29695, -19508, -905);
		gcall.Stepto(-29622, -19745, -909);
		gcall.Stepto(-29546, -19981, -906);
		gcall.Stepto(-29471, -20218, -898);
		gcall.Stepto(-29542, -20445, -899);
		gcall.Stepto(-29712, -20627, -909);
		gcall.Stepto(-29808, -20849, -922);
		gcall.Stepto(-29861, -21092, -939);
		gcall.Stepto(-29910, -21338, -943);
		gcall.Stepto(-29958, -21584, -959);
		gcall.Stepto(-30005, -21825, -976);
		gcall.Stepto(-30052, -22070, -998);
		gcall.Stepto(-30100, -22315, -1021);
		gcall.Stepto(-30147, -22557, -1033);
		gcall.Stepto(-30195, -22802, -1033);
		gcall.Stepto(-30243, -23046, -1023);
		gcall.Stepto(-30290, -23290, -1005);
		gcall.Stepto(-30337, -23530, -994);
		gcall.Stepto(-30385, -23775, -989);
		gcall.Stepto(-30431, -24011, -996);
		gcall.Stepto(-30480, -24261, -1004);
		gcall.Stepto(-30527, -24506, -993);
		gcall.Stepto(-30574, -24750, -973);
		gcall.Stepto(-30611, -24996, -958);
		gcall.Stepto(-30615, -25244, -971);
		gcall.Stepto(-30621, -25493, -991);
		gcall.Stepto(-30621, -25570, -991);
		gcall.NewSpend(1);
		Sleep(2000);
		gcall.FixWuqi();
		Sleep(1000);
		gcall.NewSpend(2.5);
		gcall.Stepto(-30621, -25570, -991);
		gcall.Stepto(-30622, -25571, -991);
		gcall.Stepto(-30823, -25702, -991);
		gcall.Stepto(-30987, -25886, -997);
		gcall.Stepto(-31070, -26122, -1046);
		gcall.Stepto(-31088, -26366, -1117);
		gcall.Stepto(-31074, -26614, -1149);
		gcall.Stepto(-31036, -26859, -1161);
		gcall.Stepto(-30995, -27103, -1189);
		gcall.Stepto(-30977, -27216, -1191);
		gcall.Stepto(-30967, -27273, -1192);
		gcall.Stepto(-30927, -27516, -1199);
		gcall.Stepto(-30886, -27761, -1198);
		gcall.Stepto(-30846, -28004, -1194);
		gcall.Stepto(-30805, -28252, -1186);
		gcall.Stepto(-30764, -28497, -1183);
		gcall.Stepto(-30723, -28740, -1182);
		gcall.Stepto(-30814, -28941, -1195);
		gcall.Stepto(-30992, -29106, -1216);
		gcall.Stepto(-31173, -29276, -1234);
		gcall.Stepto(-31355, -29447, -1234);
		gcall.Stepto(-31535, -29615, -1268);
		gcall.Stepto(-31716, -29785, -1279);
		gcall.Stepto(-31899, -29955, -1288);
		gcall.Stepto(-32084, -30121, -1294);
		gcall.Stepto(-32276, -30275, -1304);
		gcall.Stepto(-32469, -30432, -1313);
		gcall.Stepto(-32661, -30586, -1324);
		gcall.Stepto(-32855, -30742, -1335);
		gcall.Stepto(-33049, -30899, -1344);
		gcall.Stepto(-33243, -31055, -1350);
		gcall.Stepto(-33435, -31210, -1353);
		gcall.Stepto(-33630, -31364, -1369);
		gcall.Stepto(-33823, -31513, -1427);
		gcall.Stepto(-33947, -31609, -1439);
		gcall.Stepto(-33955, -31691, -1433);
		gcall.Stepto(-33976, -31934, -1439);
		gcall.Stepto(-33999, -32187, -1442);
		gcall.Stepto(-34021, -32433, -1437);
		gcall.Stepto(-34043, -32680, -1403);
		gcall.Stepto(-34065, -32928, -1399);
		gcall.Stepto(-34087, -33176, -1378);
		gcall.Stepto(-34109, -33424, -1345);
		gcall.Stepto(-34131, -33670, -1288);
		gcall.Stepto(-34153, -33917, -1204);
		gcall.Stepto(-34204, -34161, -1168);
		gcall.Stepto(-34268, -34402, -1168);
		gcall.Stepto(-34331, -34640, -1201);
		gcall.Stepto(-34389, -34882, -1159);
		gcall.Stepto(-34441, -35126, -1086);
		gcall.Stepto(-34598, -35297, -1061);
		gcall.Stepto(-34836, -35367, -1039);
		gcall.Stepto(-35081, -35414, -1002);
		gcall.Stepto(-35301, -35521, -943);
		gcall.Stepto(-35401, -35728, -839);
		gcall.Stepto(-35329, -35951, -742);
		gcall.Stepto(-35232, -36209, -616);
		gcall.Stepto(-35159, -36444, -505);
		gcall.Stepto(-35137, -36690, -437);
		gcall.Stepto(-35182, -36936, -394);
		gcall.Stepto(-35320, -37136, -379);
		gcall.Stepto(-35500, -37311, -379);
		gcall.Stepto(-35692, -37470, -379);
		gcall.Stepto(-35900, -37600, -362);
		gcall.Stepto(-36120, -37721, -373);
		gcall.Stepto(-36337, -37836, -376);
		gcall.Stepto(-36562, -37952, -358);
		gcall.Stepto(-36784, -38059, -379);
		gcall.Stepto(-36859, -38095, -378);
		gcall.NewSpend(1);
		Sleep(1000);
		gcall.DeliverQuests(308,taskid,L"역기산");
		Sleep(2000);
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

void TaskScript::Task_309(int zid,int taskid)
{
	switch (taskid)
	{
	case 1:
		gcall.NewSpend(2.5);
		gcall.Stepto(-36861,-38091,-378);
		gcall.Stepto(-36823,-38076,-378);
		gcall.Stepto(-36591,-37987,-360);
		gcall.Stepto(-36357,-37897,-374);
		gcall.Stepto(-36126,-37807,-373);
		gcall.Stepto(-35896,-37719,-359);
		gcall.Stepto(-35665,-37629,-376);
		gcall.Stepto(-35446,-37513,-379);
		gcall.Stepto(-35255,-37355,-379);
		gcall.Stepto(-35065,-37196,-394);
		gcall.Stepto(-34865,-37050,-417);
		gcall.Stepto(-34645,-36936,-437);
		gcall.Stepto(-34420,-36833,-445);
		gcall.Stepto(-34183,-36761,-555);
		gcall.Stepto(-33941,-36712,-913);
		gcall.Stepto(-33710,-36746,-1120);
		gcall.Stepto(-33535,-36921,-1174);
		gcall.Stepto(-33402,-37130,-1202);
		gcall.Stepto(-33285,-37349,-1233);
		gcall.Stepto(-33173,-37570,-1247);
		gcall.Stepto(-33061,-37791,-1264);
		gcall.Stepto(-32949,-38013,-1295);
		gcall.Stepto(-32802,-38209,-1332);
		gcall.Stepto(-32619,-38376,-1348);
		gcall.Stepto(-32433,-38539,-1351);
		gcall.Stepto(-32231,-38680,-1365);
		gcall.Stepto(-32015,-38800,-1382);
		gcall.Stepto(-31773,-38851,-1407);
		gcall.Stepto(-31527,-38887,-1414);
		gcall.Stepto(-31280,-38910,-1432);
		gcall.Stepto(-31034,-38932,-1456);
		gcall.Stepto(-30786,-38954,-1500);
		gcall.Stepto(-30539,-38976,-1527);
		gcall.Stepto(-30292,-38987,-1539);
		gcall.Stepto(-30049,-38937,-1530);
		gcall.Stepto(-29806,-38885,-1516);
		gcall.Stepto(-29562,-38855,-1505);
		gcall.Stepto(-29329,-38937,-1499);
		gcall.Stepto(-29109,-39039,-1502);
		gcall.Stepto(-28880,-39146,-1513);
		gcall.Stepto(-28653,-39252,-1536);
		gcall.Stepto(-28428,-39357,-1547);
		gcall.Stepto(-28204,-39462,-1540);
		gcall.Stepto(-27979,-39567,-1522);
		gcall.Stepto(-27755,-39672,-1509);
		gcall.Stepto(-27530,-39777,-1531);
		gcall.Stepto(-27311,-39893,-1536);
		gcall.Stepto(-27104,-40030,-1552);
		gcall.Stepto(-26899,-40174,-1573);
		gcall.Stepto(-26698,-40319,-1616);
		gcall.Stepto(-26500,-40469,-1648);
		gcall.Stepto(-26303,-40620,-1664);
		gcall.NewSpend(1);
		gcall.Stepto(-26112,-40777,-1704);
		gcall.Stepto(-25921,-40940,-1748);
		Sleep(5000);
		gcall.Stepto(-25838,-41011,-1764);
		gcall.WaitPlans();
		gcall.Stepto(-25680,-41146,-1800);
		gcall.Stepto(-25491,-41308,-1869);
		gcall.NewSpend(2.5);
		gcall.Stepto(-25271,-41422,-1922);
		gcall.Stepto(-25038,-41507,-1978);
		gcall.Stepto(-24796,-41540,-2039);
		gcall.Stepto(-24544,-41550,-2101);
		gcall.Stepto(-24296,-41560,-2142);
		gcall.Stepto(-24050,-41570,-2189);
		gcall.Stepto(-23802,-41580,-2222);
		gcall.Stepto(-23554,-41589,-2244);
		gcall.Stepto(-23305,-41599,-2269);
		gcall.Stepto(-23057,-41609,-2273);
		gcall.Stepto(-22808,-41618,-2268);
		gcall.Stepto(-22559,-41628,-2296);
		gcall.Stepto(-22316,-41657,-2320);
		gcall.Stepto(-22089,-41760,-2327);
		gcall.Stepto(-21870,-41876,-2341);
		gcall.Stepto(-21670,-42025,-2342);
		gcall.Stepto(-21484,-42186,-2345);
		gcall.Stepto(-21306,-42361,-2351);
		gcall.Stepto(-21131,-42536,-2368);
		gcall.Stepto(-20959,-42717,-2411);
		gcall.Stepto(-20801,-42909,-2463);
		gcall.Stepto(-20645,-43100,-2524);
		gcall.Stepto(-20485,-43293,-2590);
		gcall.Stepto(-20309,-43464,-2643);
		gcall.Stepto(-20148,-43620,-2677);
		gcall.Stepto(-20005,-43757,-2703);
		gcall.Stepto(-19868,-43901,-2730);
		gcall.Stepto(-19740,-44054,-2752);
		gcall.Stepto(-19617,-44210,-2763);
		gcall.Stepto(-19494,-44365,-2782);
		gcall.Stepto(-19334,-44479,-2798);
		gcall.Stepto(-19140,-44514,-2820);
		gcall.Stepto(-18942,-44481,-2834);
		gcall.Stepto(-18753,-44419,-2817);
		gcall.Stepto(-18748,-44417,-2816);
		gcall.NewSpend(1);
		Sleep(1000);
		break;
	case 2:
		gcall.FindThenKill(0,300,modeNormal | modeAoe | modeTask,2);
		Sleep(1000);
		break;
	case 3:
		gcall.Stepto(-18748,-44417,-2816);
		gcall.DeliverQuests(309,taskid,L"고봉");
		Sleep(1000);
		break;
	case 4:
		gcall.NewSpend(2.5);
		gcall.Stepto(-18791,-44556,-2826);
		gcall.Stepto(-18889,-44589,-2832);
		gcall.Stepto(-19124,-44667,-2824);
		gcall.Stepto(-19359,-44745,-2823);
		gcall.Stepto(-19595,-44823,-2819);
		gcall.Stepto(-19830,-44902,-2813);
		gcall.Stepto(-20065,-44980,-2789);
		gcall.Stepto(-20128,-45001,-2785);
		gcall.Stepto(-20343,-44917,-2783);
		gcall.Stepto(-20570,-44962,-2795);
		gcall.Stepto(-20750,-45046,-2806);
		gcall.Stepto(-20924,-45140,-2812);
		gcall.Stepto(-21097,-45238,-2812);
		gcall.Stepto(-21266,-45334,-2819);
		gcall.Stepto(-21451,-45439,-2826);
		gcall.Stepto(-21671,-45508,-2826);
		gcall.Stepto(-21868,-45534,-2821);
		gcall.Stepto(-22065,-45560,-2810);
		gcall.Stepto(-22261,-45586,-2803);
		gcall.Stepto(-22458,-45612,-2793);
		gcall.Stepto(-22671,-45639,-2782);
		gcall.Stepto(-22917,-45671,-2776);
		gcall.Stepto(-23142,-45769,-2759);
		gcall.Stepto(-23351,-45898,-2750);
		gcall.Stepto(-23541,-46055,-2795);
		gcall.Stepto(-23705,-46242,-2828);
		gcall.Stepto(-23837,-46452,-2857);
		gcall.Stepto(-23958,-46669,-2889);
		gcall.NewSpend(1);
		gcall.Stepto(-24064,-46893,-2900);
		gcall.Stepto(-24105,-46981,-2902);
		Sleep(1000);
		gcall.PickupTask();
		Sleep(1000);
		break;
	case 5:
		gcall.Stepto(-24105,-46981,-2902);
		gcall.Stepto(-24255,-46903,-2896);
		gcall.Stepto(-24474,-46787,-2882);
		gcall.Stepto(-24532,-46757,-2881);
		gcall.Stepto(-24638,-46567,-2884);
		gcall.Stepto(-24702,-46329,-2888);
		gcall.Stepto(-24705,-46262,-2890);
		Sleep(3000);
		gcall.KeyPress(27);
		Sleep(3000);
		break;
	case 6:
		gcall.Stepto(-24681,-46255,-2889);
		Sleep(1000);
		gcall.DeliverQuests(309,taskid,L"범박",1);
		break;
	case 7:
		gcall.Stepto(-24708,-46264,-2889);
		gcall.Stepto(-24622,-46442,-2885);
		gcall.Stepto(-24479,-46643,-2881);
		gcall.Stepto(-24304,-46819,-2890);
		gcall.Stepto(-24200,-46923,-2897);
		gcall.Stepto(-24180,-46931,-2899);
		Sleep(1000);
		gcall.PickupSpecTypeTask(200,0x4,L"부지부장 은광삼");
		Sleep(2000);
		break;
	case 8:
		//可能掉出副本

		gcall.Stepto(-25694,-41184,-1806);
		gcall.NewSpend(2.5);
		gcall.Stepto(-25756,-41224,-1803);
		gcall.Stepto(-25542,-41323,-1863);
		gcall.Stepto(-25342,-41406,-1910);
		gcall.Stepto(-25112,-41497,-1965);
		gcall.Stepto(-24875,-41571,-2030);
		gcall.Stepto(-24628,-41596,-2097);
		gcall.Stepto(-24381,-41604,-2145);
		gcall.Stepto(-24133,-41601,-2180);
		gcall.Stepto(-23885,-41598,-2224);
		gcall.Stepto(-23637,-41595,-2232);
		gcall.Stepto(-23389,-41594,-2262);
		gcall.Stepto(-23141,-41594,-2275);
		gcall.Stepto(-22893,-41595,-2269);
		gcall.Stepto(-22645,-41597,-2289);
		gcall.Stepto(-22398,-41623,-2315);
		gcall.Stepto(-22167,-41719,-2322);
		gcall.Stepto(-21970,-41868,-2338);
		gcall.Stepto(-21773,-42019,-2343);
		gcall.Stepto(-21576,-42170,-2341);
		gcall.Stepto(-21377,-42325,-2348);
		gcall.Stepto(-21203,-42501,-2364);
		gcall.Stepto(-21033,-42682,-2397);
		gcall.Stepto(-20866,-42864,-2449);
		gcall.Stepto(-20709,-43056,-2507);
		gcall.Stepto(-20554,-43250,-2573);
		gcall.Stepto(-20421,-43459,-2634);
		gcall.Stepto(-20318,-43685,-2683);
		gcall.Stepto(-20220,-43912,-2722);
		gcall.Stepto(-20128,-44143,-2760);
		gcall.Stepto(-20077,-44384,-2789);
		gcall.Stepto(-20155,-44615,-2783);
		gcall.Stepto(-20349,-44766,-2779);
		gcall.Stepto(-20567,-44884,-2799);
		gcall.Stepto(-20785,-45002,-2806);
		gcall.Stepto(-21004,-45119,-2805);
		gcall.Stepto(-21222,-45237,-2811);
		gcall.Stepto(-21448,-45337,-2819);
		gcall.Stepto(-21689,-45396,-2823);
		gcall.Stepto(-21933,-45441,-2821);
		gcall.Stepto(-22177,-45487,-2815);
		gcall.Stepto(-22420,-45533,-2798);
		gcall.Stepto(-22662,-45586,-2783);
		gcall.Stepto(-22899,-45660,-2777);
		gcall.Stepto(-23129,-45751,-2761);
		gcall.Stepto(-23354,-45856,-2750);
		gcall.Stepto(-23545,-46013,-2794);
		gcall.Stepto(-23719,-46190,-2826);
		gcall.Stepto(-23883,-46375,-2856);
		gcall.Stepto(-24048,-46561,-2888);
		gcall.Stepto(-24215,-46747,-2890);
		gcall.Stepto(-24382,-46929,-2892);
		gcall.Stepto(-24579,-47081,-2895);
		gcall.NewSpend(1);
		//可能掉出副本

		gcall.Stepto(-24200,-46923,-2897);
		gcall.Stepto(-24142,-46854,-2897);
		gcall.Stepto(-23981,-46664,-2891);
		gcall.Stepto(-23821,-46475,-2857);
		gcall.Stepto(-23660,-46285,-2827);
		gcall.Stepto(-23500,-46095,-2788);
		gcall.Stepto(-23319,-45928,-2751);
		gcall.Stepto(-23116,-45783,-2761);
		gcall.Stepto(-22915,-45638,-2777);
		gcall.Stepto(-22713,-45494,-2781);
		gcall.Stepto(-22513,-45350,-2799);
		gcall.Stepto(-22320,-45194,-2821);
		gcall.Stepto(-22252,-44965,-2821);
		gcall.FindThenKill(0,450,modeNormal | modeAoe | modePickup);
		gcall.Stepto(-22191,-44948,-2823);
		gcall.Stepto(-22241,-44924,-2821);
		Sleep(1000);
		log(_T("准备开第一个门"));
		gcall.PickupTask();
		Sleep(1000);
		gcall.FindThenKill(0,450,modeNormal | modeAoe | modePickup);
		gcall.Stepto(-22191,-44948,-2823);
		gcall.Stepto(-22241,-44924,-2821);
		Sleep(1000);
		log(_T("准备开第一个门"));
		gcall.PickupTask();
		Sleep(1000);
		//gcall.Stepto(-22375,-44806,-2789);
		gcall.DeliverQuests(309,taskid,L"하준광");
		Sleep(6000);
		//gcall.Stepto(-22230 ,-44953 ,-2822); 
		break;
	case 9:
		fPosition mypos;
		fPosition movepos1;
		movepos1.x = -47126;
		movepos1.y = -18847;
		movepos1.z = -2846;
		fPosition movepos2;
		movepos2.x = -46541;
		movepos2.y = -17737;
		movepos2.z = -2846;
		fPosition movepos3;
		movepos3.x = -47513;
		movepos3.y = -16227;
		movepos3.z = -2863;
		fPosition movepos4;
		movepos4.x = -46048;
		movepos4.y = -15698;
		movepos4.z = -2876;
		fPosition movepos4_1;
		movepos4_1.x = -46001;
		movepos4_1.y = -16407;
		movepos4_1.z = -2857;
		fPosition movepos5;
		movepos5.x = -46268;
		movepos5.y = -13856;
		movepos5.z = -2876;
		fPosition movepos6;
		movepos6.x = -46635;
		movepos6.y = -15107;
		movepos6.z = -2877;
		while (1)
		{

			//gcall.GetPlayerPos(&mypos);
			ObjectNode *pNode = NULL;

			pNode = gcall.GetObjectByName(L"하준광", 0);
			gcall.GetObjectPos(pNode, &mypos);
			if (gcall.CalcC(mypos,movepos1)<200)
			{
				gcall.Stepto(L"하준광");
				gcall.FindThenKill(0,400,modeNormal | modeAoe | modePickup );
				gcall.Stepto(-18960,-47184,-2846);
				gcall.Stepto(-18978,-47374,-2852);
				Sleep(1000);
				gcall.PickupSpecTypeTask(200,0x20,L"폭탄 부품상자");
				Sleep(2000);
				gcall.Stepto(-18978,-47374,-2852);
				gcall.Stepto(-18960,-47184,-2846);
			}else if (gcall.CalcC(mypos,movepos2)<150)
			{
				gcall.Stepto(L"하준광");
				gcall.FindThenKill(0,400,modeNormal | modeAoe | modePickup );
				gcall.Stepto(-17701,-46701,-2845);
				gcall.Stepto(-17737,-46541,-2846);
				Sleep(1000);
				gcall.PickupSpecTypeTask(200,0x20,L"폭탄 부품상자");
				Sleep(2000);
			}else if (gcall.CalcC(mypos,movepos3)<150)
			{
				gcall.Stepto(L"하준광");
				gcall.FindThenKill(0,400,modeNormal | modeAoe | modePickup );
				gcall.Stepto(-16227,-47513,-2863);
				Sleep(1000);
				gcall.PickupSpecTypeTask(200,0x20,L"폭탄 부품상자");
				Sleep(2000);
			}/*else if (gcall.CalcC(mypos,movepos4)<200)
			 {
			 gcall.Stepto(L"하준광");
			 gcall.FindThenKill(0,200,modeNormal | modeAoe | modePickup );
			 gcall.Stepto(-15437,-46112,-2877);
			 gcall.Stepto(-15591,-45918,-2877);
			 gcall.Stepto(-15965,-45849,-2860);
			 gcall.Stepto(-16189,-45987,-2857);
			 gcall.Stepto(-15652,-45785,-2877);
			 Sleep(1000);
			 gcall.PickupSpecTypeTask(200,0x20,L"폭약통");
			 Sleep(2000);
			 }*/else if (gcall.CalcC(mypos,movepos4_1)<150)
			{
				//gcall.Stepto(L"하준광");
				gcall.Stepto(-15293,-45806,-2877,10,20,5000);
				gcall.Stepto(-15807,-45823,-2871);
				gcall.Stepto(-16052,-45906,-2857);
				gcall.Stepto(-16393,-46016,-2857);
				gcall.FindThenKill(0,200,modeNormal | modeAoe | modePickup );
				gcall.Stepto(-16393,-46016,-2857);
				Sleep(1000);
				gcall.PickupSpecTypeTask(200,0x20,L"폭약통");
				Sleep(2000);
				gcall.Stepto(-16066,-45902,-2857);
				gcall.Stepto(-15741,-45861,-2875);
				gcall.Stepto(-15598,-46152,-2877);
				gcall.Stepto(-15298,-46725,-2877);
				Sleep(2000);
			}
			else if (gcall.CalcC(mypos,movepos5)<150)
			{
				gcall.Stepto(L"하준광");
				gcall.FindThenKill(0,50,modeNormal | modeAoe | modePickup );
				gcall.Stepto(-14097,-46238 ,-2865);
				gcall.Stepto(-13800,-46253,-2877);
				Sleep(1000);
				gcall.PickupSpecTypeTask(200,0x20,L"폭약통");
				Sleep(1000);
				gcall.Stepto(-14097,-46238 ,-2865);
				gcall.Stepto(-14234,-46139 ,-2862);
				
			}else if(gcall.CalcC(mypos,movepos6)<200)
			{
				DWORD pStartAddr = gcall.GetTaskStartAddr();//获取任务开始地址

				DWORD info = gcall.GetPresentTaskIndexes(0, pStartAddr);//获得当前做到第几个小任务

				if (info != 9)
				{
					break;
				}
			}
			gcall.Stepto(L"하준광");
			if(gcall.GetRangeMonsterCount(200) >= 1){
				gcall.FindThenKill(0,200,modeNormal | modeAoe | modePickup );
			}
			
		}
		break;
	case 10:
		gcall.Stepto(-14571,-46260,-2877);
		gcall.Stepto(-14912,-46840,-2877);
		gcall.Stepto(-15085,-46590,-2877);

		gcall.Stepto(L"하준광");
		gcall.FindThenKill(0,900,modeNormal | modeAoe | modePickup );
		Sleep(1000);
		gcall.Stepto(-15129,-46716,-2877);
		gcall.Stepto(-15079,-46579,-2877);
		Sleep(1000);
		log(_T("准备捡第六个物品"));
		gcall.PickupSpecTypeTask(200,0x20,L"기폭장치");
		Sleep(5000);
		gcall.FindThenKill(0,600,modeNormal | modeAoe | modePickup);
		gcall.Stepto(-15129,-46716,-2877);
		gcall.Stepto(-15079,-46579,-2877);
		Sleep(1000);
		gcall.PickupSpecTypeTask(200,0x20,L"기폭장치");
		Sleep(5000);
		gcall.FindThenKill(0,600,modeNormal | modeAoe | modePickup);
		gcall.Stepto(-15129,-46716,-2877);
		gcall.Stepto(-15079,-46579,-2877);
		Sleep(1000);
		gcall.PickupSpecTypeTask(200,0x20,L"기폭장치");
		Sleep(2000);

		gcall.Stepto(-15077,-46574,-2877);
		gcall.Stepto(-14971,-46728,-2877);
		gcall.Stepto(-14737,-46692,-2877);
		gcall.Stepto(-14615,-46488,-2877);
		gcall.Stepto(-14597,-46236,-2877);
		gcall.Stepto(-14594,-45988,-2877);
		gcall.Stepto(-14601,-45735,-2876);
		gcall.Stepto(-14601,-45727,-2876);
		Sleep(5000);
		gcall.FindThenKill(0,600,modeNormal | modeAoe | modePickup | modeTask,10,0);
		Sleep(3000);
		break;
	case 11:
		gcall.NewSpend(2.5);
		gcall.Stepto(-14661,-45805,-2877);
		gcall.Stepto(-14685,-45826,-2877);
		gcall.Stepto(-14841,-45947,-2877);
		gcall.Stepto(-15014,-46044,-2877);
		gcall.Stepto(-15187,-46140,-2877);
		gcall.Stepto(-15392,-46270,-2877);
		gcall.Stepto(-15580,-46433,-2877);
		gcall.Stepto(-15762,-46601,-2871);
		gcall.Stepto(-15944,-46770,-2860);
		gcall.Stepto(-16126,-46938,-2860);
		gcall.Stepto(-16341,-47059,-2863);
		gcall.Stepto(-16584,-47109,-2863);
		gcall.NewSpend(1);
		Sleep(1000);
		gcall.CityConvey(2);
		Sleep(3000);
		gcall.Stepto(-36188,-38116,-376);
		gcall.Stepto(-36324,-37991,-374);
		gcall.Stepto(-36459,-38020,-357);
		gcall.Stepto(-36688,-38075,-369);
		gcall.Stepto(-36866,-38110,-379);
		Sleep(1000);
		gcall.DeliverQuests(309,taskid,L"역기산");
		Sleep(3000);
		break;
	}
}

void TaskScript::Task_310(int zid,int taskid)
{
	switch (taskid)
	{
	case 1:
		gcall.NewSpend(2.5);
		gcall.Stepto(-36892,-38111,-378);
		gcall.Stepto(-36831,-38078,-378);
		gcall.Stepto(-36612,-37960,-362);
		gcall.Stepto(-36397,-37835,-375);
		gcall.Stepto(-36183,-37709,-376);
		gcall.Stepto(-35971,-37584,-369);
		gcall.Stepto(-35757,-37458,-377);
		gcall.Stepto(-35544,-37332,-379);
		gcall.Stepto(-35330,-37207,-379);
		gcall.Stepto(-35115,-37080,-397);
		gcall.Stepto(-34901,-36954,-429);
		gcall.Stepto(-34695,-36816,-449);
		gcall.Stepto(-34497,-36667,-475);
		gcall.Stepto(-34308,-36506,-546);
		gcall.Stepto(-34130,-36333,-834);
		gcall.Stepto(-33954,-36162,-1123);
		gcall.Stepto(-33775,-35987,-1147);
		gcall.Stepto(-33598,-35814,-1145);
		gcall.Stepto(-33421,-35643,-1140);
		gcall.Stepto(-33236,-35476,-1108);
		gcall.Stepto(-33043,-35320,-1066);
		gcall.Stepto(-32848,-35167,-1035);
		gcall.Stepto(-32651,-35016,-1012);
		gcall.Stepto(-32454,-34865,-993);
		gcall.Stepto(-32249,-34727,-973);
		gcall.Stepto(-32017,-34640,-951);
		gcall.Stepto(-31780,-34568,-934);
		gcall.Stepto(-31542,-34496,-907);
		gcall.Stepto(-31305,-34424,-879);
		gcall.Stepto(-31078,-34328,-844);
		gcall.Stepto(-30934,-34128,-815);
		gcall.Stepto(-30824,-33908,-790);
		gcall.Stepto(-30773,-33665,-760);
		gcall.Stepto(-30734,-33423,-743);
		gcall.Stepto(-30674,-33177,-728);
		gcall.Stepto(-30612,-32937,-707);
		gcall.Stepto(-30550,-32697,-683);
		gcall.Stepto(-30488,-32457,-685);
		gcall.Stepto(-30432,-32215,-719);
		gcall.Stepto(-30385,-31972,-772);
		gcall.Stepto(-30338,-31730,-839);
		gcall.Stepto(-30291,-31486,-910);
		gcall.Stepto(-30244,-31240,-983);
		gcall.Stepto(-30198,-30999,-1053);
		gcall.Stepto(-30151,-30755,-1093);
		gcall.Stepto(-30076,-30519,-1120);
		gcall.Stepto(-29897,-30346,-1126);
		gcall.Stepto(-29681,-30229,-1122);
		gcall.Stepto(-29439,-30176,-1111);
		gcall.Stepto(-29194,-30161,-1096);
		gcall.Stepto(-28945,-30146,-1090);
		gcall.Stepto(-28698,-30132,-1090);
		gcall.Stepto(-28450,-30117,-1088);
		gcall.Stepto(-28200,-30103,-1085);
		gcall.Stepto(-27952,-30088,-1084);
		gcall.Stepto(-27706,-30074,-1085);
		gcall.Stepto(-27460,-30060,-1083);
		gcall.Stepto(-27212,-30045,-1075);
		gcall.Stepto(-26961,-30031,-1070);
		gcall.Stepto(-26713,-30016,-1073);
		gcall.Stepto(-26465,-30002,-1075);
		gcall.Stepto(-26217,-29987,-1063);
		gcall.Stepto(-25970,-29973,-1049);
		gcall.Stepto(-25722,-29959,-1033);
		gcall.Stepto(-25479,-29944,-1029);
		gcall.Stepto(-25236,-29982,-1037);
		gcall.Stepto(-24992,-30044,-1055);
		gcall.Stepto(-24749,-30094,-1056);
		gcall.Stepto(-24506,-30143,-1045);
		gcall.Stepto(-24263,-30192,-1040);
		gcall.Stepto(-24017,-30220,-1029);
		gcall.Stepto(-23770,-30244,-1038);
		gcall.Stepto(-23523,-30269,-1072);
		gcall.Stepto(-23276,-30293,-1117);
		gcall.Stepto(-23030,-30317,-1166);
		gcall.Stepto(-22783,-30342,-1203);
		gcall.Stepto(-22536,-30366,-1223);
		gcall.Stepto(-22287,-30390,-1241);
		gcall.Stepto(-22039,-30415,-1259);
		gcall.Stepto(-21795,-30439,-1280);
		gcall.Stepto(-21548,-30463,-1305);
		gcall.Stepto(-21297,-30487,-1326);
		gcall.Stepto(-21050,-30511,-1326);
		gcall.Stepto(-20808,-30558,-1316);
		gcall.Stepto(-20581,-30658,-1294);
		gcall.Stepto(-20366,-30780,-1254);
		gcall.Stepto(-20154,-30909,-1224);
		gcall.Stepto(-19942,-31038,-1178);
		gcall.Stepto(-19730,-31167,-1139);
		gcall.Stepto(-19515,-31298,-1147);
		gcall.Stepto(-19303,-31427,-1165);
		gcall.Stepto(-19062,-31462,-1155);
		gcall.Stepto(-18823,-31398,-1147);
		gcall.Stepto(-18603,-31284,-1142);
		gcall.Stepto(-18392,-31152,-1141);
		gcall.Stepto(-18183,-31020,-1150);
		gcall.Stepto(-17973,-30887,-1168);
		gcall.Stepto(-17760,-30753,-1183);
		gcall.Stepto(-17550,-30620,-1187);
		gcall.Stepto(-17340,-30487,-1186);
		gcall.Stepto(-17131,-30355,-1182);
		gcall.Stepto(-16921,-30222,-1177);
		gcall.Stepto(-16711,-30090,-1176);
		gcall.NewSpend(1);
		gcall.Stepto(-16502,-29957,-1176);
		gcall.Stepto(-16292,-29825,-1175);
		gcall.Stepto(-16083,-29692,-1180);
		Sleep(3000);
		gcall.Stepto(-16013,-29648,-1186);
		gcall.WaitPlans();
		gcall.Stepto(-15805,-29516,-1202);
		gcall.Stepto(-15595,-29384,-1221);
		gcall.NewSpend(2.5);
		gcall.Stepto(-15429,-29279,-1249);
		gcall.Stepto(-15397,-29176,-1257);
		gcall.Stepto(-15323,-28935,-1273);
		gcall.Stepto(-15209,-28719,-1294);
		gcall.Stepto(-15026,-28555,-1325);
		gcall.Stepto(-14796,-28467,-1333);
		gcall.Stepto(-14564,-28380,-1334);
		gcall.Stepto(-14327,-28293,-1360);
		gcall.Stepto(-14100,-28199,-1373);
		gcall.Stepto(-13870,-28104,-1397);
		gcall.Stepto(-13643,-28011,-1436);
		gcall.Stepto(-13402,-27942,-1468);
		gcall.Stepto(-13158,-27915,-1498);
		gcall.Stepto(-12907,-27886,-1532);
		gcall.Stepto(-12660,-27886,-1570);
		gcall.Stepto(-12451,-28016,-1600);
		gcall.Stepto(-12279,-28195,-1624);
		gcall.Stepto(-12114,-28380,-1648);
		gcall.Stepto(-11948,-28565,-1659);
		gcall.NewSpend(1);
		gcall.Stepto(-11783,-28750,-1690);
		gcall.Stepto(-11613,-28935,-1715);
		gcall.Stepto(-11393,-29043,-1754);
		gcall.Stepto(-11152,-29101,-1808);
		gcall.Stepto(-10911,-29158,-1856);
		Sleep(5000);
		gcall.Stepto(-10665,-29191,-1904);
		gcall.WaitPlans();
		gcall.Stepto(-10532,-29207,-1939);
		gcall.Stepto(-10252,-29241,-2016);
		gcall.NewSpend(2.5);
		gcall.Stepto(-10002,-29272,-2093);
		gcall.Stepto(-9756,-29302,-2179);
		gcall.Stepto(-9510,-29332,-2258);
		gcall.Stepto(-9263,-29362,-2339);
		gcall.Stepto(-9018,-29399,-2417);
		gcall.Stepto(-8789,-29481,-2511);
		gcall.Stepto(-8569,-29612,-2595);
		gcall.Stepto(-8367,-29754,-2661);
		gcall.Stepto(-8172,-29907,-2688);
		gcall.Stepto(-7992,-30083,-2700);
		gcall.Stepto(-7840,-30275,-2694);
		gcall.Stepto(-7710,-30489,-2691);
		gcall.Stepto(-7620,-30718,-2688);
		gcall.Stepto(-7568,-30961,-2688);
		gcall.Stepto(-7561,-31017,-2688);
		gcall.NewSpend(1);
		Sleep(1000);
		gcall.DeliverQuests(310,taskid,L"쓰러진 어촌주민");
		Sleep(2000);
		break;
	case 2:
		gcall.randXianlu(0);
		Sleep(2000);
		gcall.Stepto(-7561,-31017,-2688);
		gcall.Stepto(-7537,-31021,-2688);
		gcall.NewSpend(2.5);
		gcall.Stepto(-7303,-31105,-2690);
		gcall.Stepto(-7079,-31213,-2710);
		gcall.Stepto(-6852,-31307,-2767);
		gcall.Stepto(-6619,-31396,-2834);
		gcall.Stepto(-6395,-31504,-2840);
		gcall.Stepto(-6184,-31634,-2845);
		gcall.Stepto(-5974,-31766,-2889);
		gcall.Stepto(-5774,-31909,-2911);
		gcall.Stepto(-5573,-32054,-2902);
		gcall.Stepto(-5369,-32200,-2904);
		gcall.Stepto(-5170,-32344,-2906);
		gcall.Stepto(-4969,-32489,-2911);
		gcall.Stepto(-4767,-32636,-2907);
		gcall.Stepto(-4568,-32783,-2902);
		gcall.Stepto(-4370,-32929,-2911);
		gcall.Stepto(-4168,-33078,-2909);
		gcall.Stepto(-3970,-33225,-2921);
		gcall.Stepto(-3770,-33373,-2928);
		gcall.Stepto(-3565,-33506,-2910);
		gcall.Stepto(-3322,-33560,-2902);
		gcall.Stepto(-3071,-33565,-2880);
		gcall.Stepto(-2824,-33550,-2858);
		gcall.Stepto(-2579,-33528,-2850);
		gcall.Stepto(-2339,-33504,-2837);
		gcall.Stepto(-2085,-33468,-2821);
		gcall.Stepto(-1847,-33405,-2814);
		gcall.Stepto(-1611,-33329,-2807);
		gcall.Stepto(-1373,-33249,-2807);
		gcall.Stepto(-1137,-33170,-2807);
		gcall.Stepto(-903,-33091,-2815);
		gcall.Stepto(-667,-33011,-2854);
		gcall.Stepto(-455,-32884,-2880);
		gcall.Stepto(-318,-32678,-2885);
		gcall.Stepto(-245,-32446,-2884);
		gcall.Stepto(-272,-32205,-2879);
		gcall.Stepto(-403,-31985,-2871);
		gcall.Stepto(-550,-31787,-2853);
		gcall.Stepto(-695,-31593,-2836);
		gcall.Stepto(-837,-31402,-2819);
		gcall.Stepto(-990,-31196,-2814);
		gcall.Stepto(-1145,-30988,-2805);
		gcall.Stepto(-1290,-30793,-2787);
		gcall.Stepto(-1438,-30595,-2769);
		gcall.Stepto(-1585,-30395,-2759);
		gcall.Stepto(-1715,-30183,-2750);
		gcall.Stepto(-1817,-29949,-2741,10,20,3000);
		gcall.Stepto(-1869,-29708,-2713,10,20,3000);
		gcall.Stepto(-1913,-29471,-2693,10,20,3000);
		gcall.Stepto(-1923,-29218,-2674,10,20,3000);
		gcall.Stepto(-1879,-28971,-2665,10,20,3000);
		gcall.Stepto(-1796,-28742,-2648,10,20,3000);
		gcall.Stepto(-1699,-28514,-2630,10,20,3000);
		gcall.Stepto(-1600,-28282,-2618,10,20,3000);
		gcall.Stepto(-1525,-28046,-2594,10,20,3000);
		gcall.Stepto(-1553,-27797,-2547,10,20,3000);
		gcall.Stepto(-1653,-27570,-2455,10,20,3000);
		gcall.Stepto(-1784,-27382,-2363,10,20,3000);
		gcall.Stepto(-1784,-27382,-2362,10,20,3000);
		gcall.Stepto(-1743,-27517,-2408,10,20,3000);
		gcall.Stepto(-1676,-27756,-2522,10,20,3000);
		gcall.Stepto(-1614,-28000,-2584);
		gcall.Stepto(-1596,-28245,-2614);
		gcall.Stepto(-1676,-28479,-2630);
		gcall.Stepto(-1763,-28713,-2646);
		gcall.Stepto(-1849,-28943,-2664);
		gcall.Stepto(-1905,-29179,-2672);
		gcall.Stepto(-1856,-29425,-2692);
		gcall.Stepto(-1799,-29668,-2715);
		gcall.Stepto(-1722,-29907,-2744);
		gcall.Stepto(-1629,-30136,-2745);
		gcall.Stepto(-1519,-30360,-2754);
		gcall.Stepto(-1382,-30567,-2769);
		gcall.Stepto(-1216,-30747,-2788);
		gcall.Stepto(-1030,-30915,-2800);
		gcall.Stepto(-828,-31066,-2801);
		gcall.Stepto(-616,-31192,-2816);
		gcall.Stepto(-394,-31305,-2831);
		gcall.Stepto(-172,-31418,-2845);
		gcall.Stepto(48,-31531,-2850);
		gcall.Stepto(268,-31644,-2853);
		gcall.Stepto(476,-31784,-2865);
		gcall.Stepto(627,-31978,-2869);
		gcall.Stepto(709,-32198,-2864);
		gcall.Stepto(709,-32199,-2864);
		gcall.Stepto(610,-32384,-2874);
		gcall.Stepto(600,-32404,-2874);
		gcall.NewSpend(1);
		//过滤怪物(선준,1);
		gcall.FindThenKill(0,900,modeNormal | modeAoe | modePickup | modeTask,2);
		//过滤怪物(선준,3);
		Sleep(3000);
		break;
	case 3:
		gcall.NewSpend(2.5);
		gcall.Stepto(-2545,-26781,-2226);
		gcall.Stepto(-2409,-26979,-2230);
		gcall.Stepto(-2313,-27203,-2230);
		gcall.Stepto(-2122,-27375,-2270);
		gcall.Stepto(-1930,-27555,-2376);
		gcall.Stepto(-1754,-27735,-2496);
		gcall.Stepto(-1638,-27961,-2573);
		gcall.Stepto(-1651,-28216,-2609);
		gcall.Stepto(-1669,-28473,-2630);
		gcall.Stepto(-1688,-28736,-2650);
		gcall.Stepto(-1706,-28995,-2667);
		gcall.Stepto(-1724,-29248,-2681);
		gcall.Stepto(-1743,-29507,-2706);
		gcall.Stepto(-1761,-29762,-2725);
		gcall.Stepto(-1776,-30020,-2746);
		gcall.Stepto(-1678,-30255,-2752);
		gcall.Stepto(-1496,-30441,-2763);
		gcall.Stepto(-1318,-30621,-2774);
		gcall.Stepto(-1140,-30803,-2794);
		gcall.Stepto(-961,-30984,-2802);
		gcall.Stepto(-781,-31167,-2809);
		gcall.Stepto(-600,-31351,-2826);
		gcall.NewSpend(1);
		gcall.Stepto(268,-31644,-2853,10,20,3000);
		gcall.Stepto(L"도천풍");
		Sleep(3000);
		break;
	case 4:
		gcall.NewSpend(2.5);
		gcall.Stepto(-2545,-26781,-2226);
		gcall.Stepto(-2409,-26979,-2230);
		gcall.Stepto(-2313,-27203,-2230);
		gcall.Stepto(-2122,-27375,-2270);
		gcall.Stepto(-1930,-27555,-2376);
		gcall.Stepto(-1754,-27735,-2496);
		gcall.Stepto(-1638,-27961,-2573);
		gcall.Stepto(-1651,-28216,-2609);
		gcall.Stepto(-1669,-28473,-2630);
		gcall.Stepto(-1688,-28736,-2650);
		gcall.Stepto(-1706,-28995,-2667);
		gcall.Stepto(-1724,-29248,-2681);
		gcall.Stepto(-1743,-29507,-2706);
		gcall.Stepto(-1761,-29762,-2725);
		gcall.Stepto(-1776,-30020,-2746);
		gcall.Stepto(-1678,-30255,-2752);
		gcall.Stepto(-1496,-30441,-2763);
		gcall.Stepto(-1318,-30621,-2774);
		gcall.Stepto(-1140,-30803,-2794);
		gcall.Stepto(-961,-30984,-2802);
		gcall.Stepto(-781,-31167,-2809);
		gcall.Stepto(-600,-31351,-2826);
		gcall.NewSpend(1);
		gcall.Stepto(745,-32120,-2861);
		gcall.Stepto(725,-32112,-2862);
		gcall.Stepto(535,-32050,-2873);
		gcall.Stepto(344,-31997,-2877);
		gcall.Stepto(114,-32011,-2878);
		gcall.Stepto(-131,-32027,-2879);
		gcall.Stepto(-378,-32043,-2872);
		gcall.Stepto(-627,-32060,-2849);
		gcall.Stepto(-874,-32076,-2816);
		gcall.Stepto(-1124,-32100,-2787);
		gcall.Stepto(-1363,-32150,-2761);
		gcall.Stepto(-1607,-32201,-2764);
		gcall.Stepto(-1658,-32210,-2764);
		Sleep(2000);
		gcall.FindThenKill(0,300,modeNormal | modeAoe | modePickup);
		gcall.Stepto(-1134,-32156,-2780);
		gcall.Stepto(-1682,-32191,-2764);
		Sleep(2000);
		gcall.PickupSpecTypeTask(200,0x4,L"고립된 어촌주민");
		Sleep(2000);
		gcall.Stepto(-1727,-32107,-2764);
		gcall.Stepto(-1830,-31884,-2764);
		gcall.Stepto(-1932,-31663,-2761);
		gcall.Stepto(-2041,-31429,-2737);
		gcall.Stepto(-2240,-31326,-2699);
		gcall.Stepto(-2475,-31402,-2668);
		gcall.Stepto(-2637,-31591,-2647);
		gcall.Stepto(-2726,-31811,-2663);
		gcall.Stepto(-2737,-31838,-2664);
		Sleep(2000);
		gcall.FindThenKill(0,300,modeNormal | modeAoe | modePickup);
		gcall.Stepto(-2703,-31655,-2657);
		gcall.Stepto(-2718,-31814,-2664);
		Sleep(2000);
		gcall.PickupSpecTypeTask(200,0x4,L"고립된 어촌주민");
		Sleep(2000);
		gcall.Stepto(-2769,-31667,-2658);
		gcall.Stepto(-2821,-31426,-2647);
		gcall.Stepto(-2876,-31186,-2650);
		gcall.Stepto(-2886,-31150,-2650);
		Sleep(1000);
		gcall.FindThenKill(0,300,modeNormal | modeAoe | modePickup);
		gcall.Stepto(-2818,-31411,-2647);
		gcall.Stepto(-2872,-31271,-2648);
		Sleep(2000);
		gcall.PickupSpecTypeTask(200,0x4,L"고립된 어촌주민");
		Sleep(2000);
		gcall.Stepto(-2896,-31128,-2651);
		gcall.Stepto(-2996,-30898,-2645);
		gcall.Stepto(-3082,-30666,-2618);
		gcall.Stepto(-3184,-30440,-2582);
		gcall.Stepto(-3404,-30411,-2566);
		gcall.Stepto(-3452,-30427,-2566);
		Sleep(1000);
		gcall.FindThenKill(0,300,modeNormal | modeAoe | modePickup);
		gcall.Stepto(-3276,-30443,-2574);
		gcall.Stepto(-3440,-30439,-2566);
		Sleep(2000);
		gcall.PickupSpecTypeTask(200,0x4,L"고립된 어촌주민");
		Sleep(2000);
		gcall.Stepto(-3368,-30425,-2568);
		gcall.Stepto(-3125,-30458,-2587);
		gcall.Stepto(-2881,-30497,-2619);
		gcall.Stepto(-2650,-30582,-2665);
		gcall.Stepto(-2438,-30718,-2684);
		gcall.Stepto(-2267,-30892,-2694);
		gcall.Stepto(-2113,-31087,-2725);
		gcall.Stepto(-1965,-31286,-2743);
		gcall.Stepto(-1853,-31505,-2753);
		gcall.Stepto(-1799,-31746,-2764);
		gcall.Stepto(-1772,-31995,-2764);
		gcall.Stepto(-1742,-32160,-2764);
		gcall.randXianlu(0);
		Sleep(2000);
		break;
	case 5:
		gcall.NewSpend(2.5);
		gcall.Stepto(-1658,-32210,-2764);
		gcall.Stepto(-1740,-32045,-2764);
		gcall.Stepto(-1844,-31820,-2764);
		gcall.Stepto(-1905,-31581,-2758);
		gcall.Stepto(-1965,-31340,-2743);
		gcall.Stepto(-2027,-31099,-2740);
		gcall.Stepto(-2088,-30861,-2727);
		gcall.Stepto(-2149,-30619,-2713);
		gcall.Stepto(-2211,-30377,-2717);
		gcall.Stepto(-2226,-30135,-2716);
		gcall.Stepto(-2184,-29890,-2706);
		gcall.Stepto(-2141,-29646,-2693);
		gcall.Stepto(-2098,-29399,-2681);
		gcall.Stepto(-2055,-29155,-2665);
		gcall.Stepto(-2013,-28911,-2653);
		gcall.Stepto(-1970,-28666,-2638);
		gcall.Stepto(-1927,-28424,-2610);
		gcall.Stepto(-1885,-28179,-2589);
		gcall.Stepto(-1891,-27932,-2549);
		gcall.Stepto(-1924,-27686,-2443);
		gcall.Stepto(-1966,-27442,-2319);
		gcall.Stepto(-2022,-27201,-2255);
		gcall.Stepto(-2096,-26965,-2231);
		gcall.Stepto(-2212,-26744,-2231);
		gcall.Stepto(-2324,-26548,-2231);
		gcall.NewSpend(1);
		Sleep(1000);
		gcall.DeliverQuests(310,taskid,L"옥경원");
		Sleep(2000);
		break;
	case 6:
		gcall.NewSpend(2.5);
		gcall.Stepto(-2212,-26716,-2231);
		gcall.Stepto(-2199,-26735,-2231);
		gcall.Stepto(-2172,-26785,-2231);
		gcall.Stepto(-2076,-27014,-2232);
		gcall.Stepto(-1981,-27245,-2266);
		gcall.Stepto(-1900,-27478,-2348);
		gcall.Stepto(-1858,-27719,-2472);
		gcall.Stepto(-1865,-27969,-2563);
		gcall.Stepto(-1940,-28203,-2587);
		gcall.Stepto(-2053,-28418,-2606);
		gcall.Stepto(-2242,-28585,-2621);
		gcall.Stepto(-2425,-28747,-2626);
		gcall.Stepto(-2612,-28911,-2628);
		gcall.Stepto(-2798,-29075,-2627);
		gcall.Stepto(-2985,-29240,-2610);
		gcall.Stepto(-3172,-29405,-2569);
		gcall.Stepto(-3358,-29568,-2556);
		gcall.Stepto(-3551,-29724,-2548);
		gcall.Stepto(-3756,-29863,-2548);
		gcall.Stepto(-3852,-29831,-2548);
		gcall.Stepto(-4071,-29721,-2537);
		gcall.Stepto(-4312,-29664,-2540);
		gcall.Stepto(-4546,-29584,-2577);
		gcall.Stepto(-4647,-29363,-2597);
		gcall.WaitPlans();
		gcall.Stepto(-4673,-29278,-2627);
		gcall.WaitPlans();
		gcall.Stepto(-4707,-29169,-2686,30);
		gcall.WaitPlans();
		gcall.Stepto(-4782,-28931,-2841,30);
		gcall.Stepto(-4860,-28699,-2996,30);
		gcall.Stepto(-4940,-28463,-3147);
		gcall.Stepto(-5019,-28228,-3293);
		gcall.Stepto(-5104,-27994,-3324);
		gcall.Stepto(-5235,-27783,-3341);
		gcall.Stepto(-5372,-27576,-3371);
		gcall.Stepto(-5509,-27368,-3454);
		gcall.Stepto(-5646,-27161,-3551);
		gcall.Stepto(-5786,-26959,-3631);
		gcall.Stepto(-5982,-26805,-3719);
		gcall.Stepto(-6207,-26706,-3784);
		gcall.Stepto(-6451,-26655,-3825);
		gcall.Stepto(-6698,-26665,-3822);
		gcall.Stepto(-6937,-26721,-3816);
		gcall.Stepto(-7172,-26809,-3798);
		gcall.Stepto(-7369,-26941,-3749);
		gcall.Stepto(-7530,-27057,-3723);
		gcall.Stepto(-7690,-27172,-3722);
		gcall.Stepto(-7854,-27290,-3722);
		gcall.Stepto(-8013,-27406,-3721);
		gcall.Stepto(-8167,-27528,-3721);
		gcall.Stepto(-8325,-27654,-3722);
		gcall.Stepto(-8481,-27777,-3723);
		gcall.Stepto(-8636,-27901,-3714);
		gcall.Stepto(-8791,-28024,-3723);
		gcall.Stepto(-8946,-28148,-3713);
		gcall.Stepto(-9103,-28270,-3713);
		gcall.Stepto(-9262,-28388,-3713);
		gcall.Stepto(-9422,-28506,-3725);
		gcall.Stepto(-9581,-28625,-3728);
		gcall.Stepto(-9740,-28743,-3732);
		gcall.Stepto(-9899,-28861,-3738);
		gcall.Stepto(-10059,-28979,-3741);
		gcall.Stepto(-10218,-29098,-3732);
		gcall.Stepto(-10377,-29216,-3726);
		gcall.Stepto(-10537,-29334,-3719);
		gcall.Stepto(-10696,-29452,-3708);
		gcall.Stepto(-10856,-29571,-3697);
		gcall.Stepto(-11015,-29689,-3682);
		gcall.Stepto(-11175,-29808,-3664);
		gcall.Stepto(-11335,-29926,-3643);
		gcall.Stepto(-11380,-29960,-3638);
		gcall.NewSpend(1);
		Sleep(35000);
		break;
	case 7:
		gcall.NewSpend(2.5);
		gcall.Stepto(-4598,-29405,-2588);
		gcall.Stepto(-4713,-29181,-2681);
		gcall.Stepto(-4793,-28946,-2835);
		gcall.Stepto(-4858,-28707,-2991);
		gcall.Stepto(-4935,-28467,-3144);
		gcall.Stepto(-5020,-28234,-3290);
		gcall.Stepto(-5114,-28005,-3324);
		gcall.Stepto(-5230,-27785,-3341);
		gcall.Stepto(-5361,-27575,-3369);
		gcall.Stepto(-5510,-27377,-3452);
		gcall.Stepto(-5684,-27200,-3557);
		gcall.Stepto(-5860,-27026,-3645);
		gcall.Stepto(-6037,-26851,-3730);
		gcall.Stepto(-6215,-26679,-3787);
		gcall.Stepto(-6434,-26622,-3826);
		gcall.Stepto(-6682,-26614,-3821);
		gcall.Stepto(-6918,-26682,-3815);
		gcall.Stepto(-7124,-26818,-3807);
		gcall.Stepto(-7321,-26969,-3748);
		gcall.Stepto(-7518,-27120,-3722);
		gcall.Stepto(-7715,-27271,-3721);
		gcall.Stepto(-7912,-27421,-3721);
		gcall.Stepto(-8112,-27568,-3721);
		gcall.Stepto(-8312,-27714,-3722);
		gcall.Stepto(-8514,-27858,-3718);
		gcall.Stepto(-8716,-28002,-3723);
		gcall.Stepto(-8919,-28145,-3713);
		gcall.Stepto(-9124,-28290,-3713);
		gcall.Stepto(-9326,-28434,-3716);
		gcall.Stepto(-9527,-28579,-3727);
		gcall.Stepto(-9719,-28736,-3732);
		gcall.Stepto(-9908,-28897,-3741);
		gcall.Stepto(-10097,-29056,-3738);
		gcall.Stepto(-10294,-29208,-3729);
		gcall.Stepto(-10537,-29394,-3717);
		gcall.Stepto(-10708,-29527,-3706);
		gcall.Stepto(-10877,-29663,-3694);
		gcall.Stepto(-11048,-29797,-3672);
		gcall.Stepto(-11220,-29930,-3651);
		gcall.NewSpend(1);
		gcall.Stepto(-11380,-29960,-3638);
		gcall.Stepto(-11432,-29992,-3633);
		gcall.Stepto(-11644,-30122,-3613);
		gcall.Stepto(-11842,-30271,-3591);
		gcall.Stepto(-11980,-30379,-3572);
		gcall.FindThenKill(0,500,modeNormal | modeAoe | modePickup);
		Sleep(3000);
		break;
	case 8:
		gcall.NewSpend(2.5);
		gcall.Stepto(-4598,-29405,-2588);
		gcall.Stepto(-4713,-29181,-2681);
		gcall.Stepto(-4793,-28946,-2835);
		gcall.Stepto(-4858,-28707,-2991);
		gcall.Stepto(-4935,-28467,-3144);
		gcall.Stepto(-5020,-28234,-3290);
		gcall.Stepto(-5114,-28005,-3324);
		gcall.Stepto(-5230,-27785,-3341);
		gcall.Stepto(-5361,-27575,-3369);
		gcall.Stepto(-5510,-27377,-3452);
		gcall.Stepto(-5684,-27200,-3557);
		gcall.Stepto(-5860,-27026,-3645);
		gcall.Stepto(-6037,-26851,-3730);
		gcall.Stepto(-6215,-26679,-3787);
		gcall.Stepto(-6434,-26622,-3826);
		gcall.Stepto(-6682,-26614,-3821);
		gcall.Stepto(-6918,-26682,-3815);
		gcall.Stepto(-7124,-26818,-3807);
		gcall.Stepto(-7321,-26969,-3748);
		gcall.Stepto(-7518,-27120,-3722);
		gcall.Stepto(-7715,-27271,-3721);
		gcall.Stepto(-7912,-27421,-3721);
		gcall.Stepto(-8112,-27568,-3721);
		gcall.Stepto(-8312,-27714,-3722);
		gcall.Stepto(-8514,-27858,-3718);
		gcall.Stepto(-8716,-28002,-3723);
		gcall.Stepto(-8919,-28145,-3713);
		gcall.Stepto(-9124,-28290,-3713);
		gcall.Stepto(-9326,-28434,-3716);
		gcall.Stepto(-9527,-28579,-3727);
		gcall.Stepto(-9719,-28736,-3732);
		gcall.Stepto(-9908,-28897,-3741);
		gcall.Stepto(-10097,-29056,-3738);
		gcall.Stepto(-10294,-29208,-3729);
		gcall.Stepto(-10537,-29394,-3717);
		gcall.Stepto(-10708,-29527,-3706);
		gcall.Stepto(-10877,-29663,-3694);
		gcall.Stepto(-11048,-29797,-3672);
		gcall.Stepto(-11220,-29930,-3651);
		gcall.NewSpend(1);
		gcall.Stepto(L"도천풍");
		gcall.FindThenKill(0,500,modeNormal | modeAoe | modePickup);
		Sleep(5000);
		gcall.FindThenKill(0,500,modeNormal | modeAoe | modePickup);
		gcall.Stepto(-11678,-30308,-3604);
		Sleep(1000);
		gcall.DeliverQuests(310,taskid,L"도천풍");
		Sleep(17000);
		gcall.KeyPress(52);//按4
		break;
	case 9:
		gcall.Stepto(L"도천풍");
		gcall.FindThenKill(0,500,modeNormal | modeAoe);
		break;
	case 10:
		gcall.NewSpend(2.5);
		gcall.Stepto(-6706,-26665,-3821);
		gcall.Stepto(-6619,-26641,-3824);
		gcall.Stepto(-6378,-26600,-3820);
		gcall.Stepto(-6150,-26694,-3775);
		gcall.Stepto(-5987,-26875,-3712);
		gcall.Stepto(-5825,-27069,-3599);
		gcall.Stepto(-5665,-27256,-3539);
		gcall.Stepto(-5503,-27445,-3428);
		gcall.Stepto(-5346,-27637,-3359);
		gcall.Stepto(-5217,-27845,-3337);
		gcall.Stepto(-5127,-28028,-3324);
		gcall.Stepto(-5044,-28281,-3245);
		gcall.Stepto(-4958,-28501,-3132);
		gcall.Stepto(-4867,-28732,-2980);
		gcall.Stepto(-4776,-28965,-2820);
		gcall.Stepto(-4693,-29197,-2667);
		Sleep(3000);
		gcall.Stepto(-4649,-29331,-2608);
		gcall.WaitPlans();
		gcall.Stepto(-4582,-29432,-2586);
		gcall.WaitPlans();
		gcall.Stepto(-4445,-29639,-2560);
		gcall.Stepto(-4240,-29758,-2537);
		gcall.Stepto(-3990,-29772,-2545);
		gcall.Stepto(-3742,-29799,-2548);
		gcall.Stepto(-3511,-29719,-2548);
		gcall.Stepto(-3302,-29584,-2555);
		gcall.Stepto(-3098,-29445,-2581);
		gcall.Stepto(-2896,-29299,-2617);
		gcall.Stepto(-2701,-29147,-2637);
		gcall.Stepto(-2510,-28986,-2637);
		gcall.Stepto(-2329,-28815,-2637);
		gcall.Stepto(-2155,-28640,-2630);
		gcall.Stepto(-1986,-28469,-2615);
		gcall.Stepto(-1807,-28287,-2601);
		gcall.Stepto(-1637,-28107,-2597);
		gcall.Stepto(-1513,-27893,-2573);
		gcall.Stepto(-1504,-27867,-2570);
		gcall.Stepto(-1599,-27731,-2524);
		gcall.Stepto(-1743,-27527,-2413);
		gcall.Stepto(-1897,-27333,-2301);
		gcall.Stepto(-2055,-27144,-2245);
		gcall.Stepto(-2133,-27053,-2233);
		Sleep(1000);
		gcall.DeliverQuests(310,0xA,L"도천풍");
		Sleep(3000);
		gcall.Stepto(-2214,-27051,-2230);
		gcall.Stepto(-2608,-26840,-2227);
		gcall.Stepto(-2946,-26540,-2230);
		Sleep(1000);
		gcall.FenJieByConfig();
		Sleep(1000);
		gcall.BuyItem(8,0,L"한망치");
		Sleep(1000);
		gcall.SellItemByConfig(L"한망치");
		Sleep(1000);
		gcall.JiaBaoShi(1,L"거와의 삼각 황옥");
		Sleep(1000);
		gcall.SortBag();
		Sleep(1000);
		break;
	}
}


void TaskScript::Task_311(int zid,int taskid)
{
	switch (taskid)
	{
	case 1:
		//gcall.ChiYao(L"자경단의 한방 용봉탕");//使用的是%60的经验药 제룡림 특제 용봉탕 小经验药

		//在副本中加检测经验药的状态，如何判断各种经验药状态？

		lianji10_go();
		while (1)
		{
			if (gcall.GetPlayerLevel()<13)
			{
				UseExperience();
				lianji10();
			}else
			{
				Sleep(5000);
				gcall.FindThenKill(0,300,modeNormal|modeAoe|modePickup);
				gcall.CityConvey(3);
				gcall.Stepto(-2548 ,-26632 ,-2230);
				gcall.Stepto(-2339 ,-27023 ,-2230);
				gcall.Stepto(-1938 ,-27481 ,-2339);
				gcall.Stepto(-2530 ,-27967 ,-2570);
				Sleep(1000);
				gcall.FixWuqi();
				//BOOL flagrs = gcall.Stepto(5864,-10502,-3265,10,20,1500);
				//if (flagrs)
				//{
				//	Sleep(1000);
				//	gcall.Shunyi(L"Lianji10-end");
				//	Sleep(1000);
				//	gcall.sendcall(id_msg_OverShunyi,(LPVOID)1);//hook
				//	Sleep(1000);
				//	gcall.Shunyi(L"Lianji10-mai-men");
				//	Sleep(1000);
				//	gcall.sendcall(id_msg_OverShunyi,(LPVOID)0);//hook
				//	Sleep(5000);
				//	gcall.WaitPlans();
				//	gcall.HeChengWuQi(EQUITMENT_POS::WUQI);
				//	Sleep(1000);
				//	gcall.FenJieByConfig();
				//}
				
				break;
			}
		}
		
		//10级战斗的地方出副本门

		//BOOL flaggo = gcall.Stepto(5629,-10419,-3271,10,20,1500);
		//if (flaggo)
		//{
		//	gcall.Stepto(5417,-10524,-3271);
		//	gcall.Stepto(5202,-10648,-3266);
		//	gcall.Stepto(4985,-10767,-3265);
		//	gcall.Stepto(4766,-10887,-3267);
		//	gcall.Stepto(4549,-11006,-3275);
		//	gcall.Stepto(4324,-11111,-3279);
		//	gcall.Stepto(4096,-11209,-3293);
		//	gcall.Stepto(3868,-11305,-3317);
		//	gcall.Stepto(3639,-11401,-3305);
		//	gcall.Stepto(3410,-11497,-3273);
		//	gcall.Stepto(3182,-11593,-3241);
		//	gcall.Stepto(2954,-11692,-3171);
		//	gcall.Stepto(2747,-11824,-3080);
		//	gcall.Stepto(2578,-12006,-2968);
		//	gcall.Stepto(2463,-12229,-2851);
		//	gcall.Stepto(2390,-12466,-2729);
		//	gcall.Stepto(2320,-12704,-2607);
		//	gcall.Stepto(2250,-12942,-2465);
		//	gcall.Stepto(2180,-13180,-2344);
		//	gcall.Stepto(2109,-13418,-2230);
		//	gcall.Stepto(2007,-13644,-2103);
		//	gcall.Stepto(1867,-13847,-1969);
		//	gcall.Stepto(1683,-14013,-1819);
		//	gcall.Stepto(1490,-14169,-1682);
		//	gcall.Stepto(1264,-14269,-1538);
		//	gcall.Stepto(1027,-14360,-1403);
		//	gcall.Stepto(787,-14452,-1292);
		//	gcall.Stepto(550,-14543,-1191);
		//	gcall.Stepto(312,-14648,-1148);
		//	gcall.Stepto(89,-14758,-1133);
		//	gcall.Stepto(-131,-14871,-1145);
		//	gcall.Stepto(-343,-15000,-1178);
		//	gcall.Stepto(-552,-15133,-1237);
		//	gcall.Stepto(-762,-15264,-1289);
		//	gcall.Stepto(-974,-15392,-1299);
		//	gcall.Stepto(-1203,-15487,-1314);
		//	gcall.Stepto(-1392,-15563,-1310);
		//	gcall.Stepto(-1573,-15669,-1338);
		//	//出10级副本门。

		//}
		
		
		////这里执行10级副本 先上管他

		////执行脚本(10级地下坑-上捡.inf,11);
		//gcall.NewSpend(2.5);
		//gcall.Stepto(-1499,-15595,-1314);
		//gcall.Stepto(-1617,-15671,-1346);
		//gcall.Stepto(-1829,-15806,-1405);
		//gcall.Stepto(-2034,-15936,-1451);
		//gcall.Stepto(-2240,-16071,-1488);
		//gcall.Stepto(-2451,-16205,-1506);
		//gcall.Stepto(-2485,-16225,-1510);
		//gcall.Stepto(-2524,-16248,-1513);
		//gcall.Stepto(-2531,-16253,-1514);
		//Sleep(1000);
		//gcall.FindThenKill(0,300,modeNormal|modeAoe|modePickup);
		//gcall.Stepto(-2531,-16253,-1514);
		//Sleep(1000);
		//gcall.FixWuqi();
		//Sleep(1000);
		//gcall.FindThenKill(0,300,modeNormal|modeAoe|modePickup);
		
		Sleep(2000);
		gcall.NewSpend(2.5);
		//gcall.Stepto(-2159,-27038,-2232);
		//gcall.Stepto(-2161,-27038,-2232);
		//gcall.Stepto(-2396,-26981,-2230);
		//gcall.Stepto(-2637,-26922,-2224);
		//gcall.Stepto(-2878,-26863,-2227);
		//gcall.Stepto(-3119,-26806,-2226);
		//gcall.Stepto(-3363,-26842,-2230);
		//gcall.Stepto(-3594,-26931,-2279);
		//gcall.Stepto(-3824,-27024,-2369);
		//gcall.Stepto(-4054,-27116,-2464);
		//gcall.Stepto(-4286,-27045,-2466);
		//gcall.Stepto(-4425,-26841,-2454);
		//gcall.Stepto(-4557,-26635,-2450);
		//gcall.Stepto(-4690,-26426,-2458);
		//gcall.Stepto(-4824,-26217,-2468);
		//gcall.Stepto(-4958,-26007,-2464);
		//gcall.Stepto(-5062,-25783,-2449);
		//gcall.Stepto(-5156,-25554,-2417);
		//gcall.Stepto(-5251,-25324,-2375);
		//gcall.Stepto(-5319,-25087,-2330);
		gcall.Stepto(-2868,-28433,-2570);
		gcall.Stepto(-3105,-28417,-2554);
		gcall.Stepto(-3349,-28373,-2546);
		gcall.Stepto(-3555,-28235,-2541);
		gcall.Stepto(-3732,-28062,-2528);
		gcall.Stepto(-3882,-27867,-2515);
		gcall.Stepto(-4003,-27650,-2507);
		gcall.Stepto(-4123,-27433,-2491);
		gcall.Stepto(-4240,-27214,-2476);
		gcall.Stepto(-4355,-26994,-2463);
		gcall.Stepto(-4470,-26775,-2451);
		gcall.Stepto(-4585,-26555,-2450);
		gcall.Stepto(-4700,-26335,-2459);
		gcall.Stepto(-4808,-26112,-2469);
		gcall.Stepto(-4912,-25887,-2461);
		gcall.Stepto(-5020,-25664,-2440);
		gcall.Stepto(-5128,-25441,-2400);
		gcall.Stepto(-5234,-25216,-2358);
		gcall.Stepto(-5313,-24981,-2310);
		gcall.Stepto(-5345,-24841,-2282);
		gcall.Stepto(-5361,-24593,-2220);
		gcall.Stepto(-5365,-24490,-2202);
		gcall.Stepto(-5375,-24240,-2147);
		gcall.Stepto(-5385,-23993,-2090);
		gcall.Stepto(-5418,-23748,-2039);
		gcall.Stepto(-5508,-23518,-1996);
		gcall.Stepto(-5606,-23291,-1971);
		gcall.Stepto(-5710,-23064,-1944);
		gcall.Stepto(-5812,-22838,-1931);
		gcall.Stepto(-5915,-22613,-1928);
		gcall.Stepto(-6018,-22387,-1925);
		gcall.Stepto(-6107,-22156,-1896);
		gcall.Stepto(-6162,-21914,-1869);
		gcall.Stepto(-6217,-21671,-1864);
		gcall.Stepto(-6272,-21429,-1866);
		gcall.Stepto(-6332,-21188,-1870);
		gcall.Stepto(-6430,-20962,-1874);
		gcall.Stepto(-6530,-20735,-1874);
		gcall.Stepto(-6631,-20506,-1877);
		gcall.Stepto(-6730,-20280,-1862);
		gcall.Stepto(-6830,-20055,-1831);
		gcall.Stepto(-6931,-19825,-1803);
		gcall.Stepto(-7031,-19598,-1780);
		gcall.Stepto(-7130,-19374,-1774);
		gcall.Stepto(-7231,-19146,-1759);
		gcall.Stepto(-7328,-18926,-1749);
		gcall.Stepto(-7430,-18694,-1743);
		gcall.Stepto(-7529,-18470,-1735);
		gcall.Stepto(-7629,-18242,-1718);
		gcall.Stepto(-7730,-18015,-1705);
		gcall.Stepto(-7830,-17787,-1704);
		gcall.Stepto(-7930,-17560,-1713);
		gcall.Stepto(-8031,-17332,-1729);
		gcall.Stepto(-8127,-17110,-1744);
		gcall.Stepto(-8169,-16860,-1758);
		gcall.Stepto(-8203,-16614,-1774);
		gcall.Stepto(-8237,-16371,-1784);
		gcall.Stepto(-8271,-16125,-1792);
		gcall.Stepto(-8305,-15875,-1793);
		gcall.Stepto(-8342,-15630,-1782);
		gcall.Stepto(-8414,-15393,-1762);
		gcall.Stepto(-8488,-15156,-1743);
		gcall.Stepto(-8562,-14919,-1730);
		gcall.Stepto(-8664,-14693,-1721);
		gcall.Stepto(-8768,-14469,-1718);
		gcall.Stepto(-8873,-14242,-1714);
		gcall.Stepto(-8987,-14022,-1698);
		gcall.Stepto(-9120,-13812,-1677);
		gcall.Stepto(-9271,-13615,-1664);
		gcall.Stepto(-9428,-13427,-1643);
		gcall.Stepto(-9613,-13261,-1634);
		gcall.Stepto(-9832,-13146,-1615);
		gcall.Stepto(-10054,-13034,-1578);
		gcall.Stepto(-10278,-12923,-1525);
		gcall.Stepto(-10505,-12821,-1486);
		gcall.Stepto(-10732,-12722,-1441);
		gcall.Stepto(-10959,-12623,-1407);
		gcall.Stepto(-11187,-12524,-1379);
		gcall.Stepto(-11414,-12425,-1324);
		gcall.Stepto(-11642,-12327,-1253);
		gcall.Stepto(-11869,-12228,-1208);
		gcall.Stepto(-12096,-12129,-1162);
		gcall.Stepto(-12324,-12030,-1127);
		gcall.Stepto(-12555,-11929,-1104);
		gcall.Stepto(-12783,-11830,-1066);
		gcall.Stepto(-13008,-11732,-1013);
		gcall.Stepto(-13239,-11631,-958);
		gcall.Stepto(-13466,-11533,-927);
		gcall.Stepto(-13682,-11413,-898);
		gcall.Stepto(-13876,-11258,-862);
		gcall.Stepto(-13987,-11053,-817);
		gcall.Stepto(-13832,-10863,-789);
		gcall.Stepto(-13662,-10682,-742);
		gcall.Stepto(-13492,-10500,-661);
		gcall.Stepto(-13339,-10307,-581);
		gcall.Stepto(-13287,-10066,-478);
		gcall.Stepto(-13264,-9817,-351);
		gcall.Stepto(-13257,-9569,-230);
		gcall.Stepto(-13249,-9321,-81);
		gcall.Stepto(-13241,-9072,49);
		gcall.Stepto(-13234,-8824,161);
		gcall.Stepto(-13202,-8585,259);
		gcall.Stepto(-13134,-8337,357);
		gcall.Stepto(-13037,-8112,433);
		gcall.Stepto(-12938,-7882,512);
		gcall.Stepto(-12839,-7655,566);
		gcall.Stepto(-12741,-7427,590);
		gcall.Stepto(-12641,-7198,602);
		gcall.Stepto(-12541,-6969,609);
		gcall.Stepto(-12427,-6751,619);
		gcall.Stepto(-12304,-6536,616);
		gcall.Stepto(-12166,-6327,609);
		gcall.Stepto(-12013,-6133,626);
		gcall.Stepto(-11849,-5944,647);
		gcall.Stepto(-11651,-5796,652);
		gcall.Stepto(-11426,-5699,650);
		gcall.Stepto(-11179,-5678,626);
		gcall.Stepto(-10946,-5760,606);
		gcall.Stepto(-10797,-5952,602);
		gcall.Stepto(-10725,-6188,602);
		gcall.Stepto(-10699,-6439,602);
		gcall.Stepto(-10700,-6683,593);
		gcall.Stepto(-10751,-6929,583);
		gcall.Stepto(-10848,-7155,585);
		gcall.Stepto(-10916,-7260,597);
		gcall.Stepto(-10944,-7300,596);
		gcall.Stepto(-11003,-7390,595);
		gcall.Stepto(-11076,-7585,594);
		Sleep(1000);
		gcall.DeliverQuests(311,taskid,L"도천풍");
		Sleep(1000);
		break;
	case 2:
		gcall.DeliverQuests(311,taskid,L"위원홍");
		Sleep(1000);
		break;
	case 3:
		gcall.NewSpend(2.5);
		gcall.Stepto(-11001,-7442,594);
		gcall.Stepto(-10898,-7249,597);
		gcall.Stepto(-10850,-7161,585);
		gcall.Stepto(-10745,-6965,583);
		gcall.Stepto(-10744,-6964,583);
		gcall.Stepto(-10633,-6756,586);
		gcall.Stepto(-10643,-6507,602);
		gcall.Stepto(-10691,-6261,602);
		gcall.Stepto(-10776,-6032,602);
		gcall.Stepto(-10977,-5896,603);
		gcall.Stepto(-11209,-5808,622);
		gcall.Stepto(-11433,-5707,650);
		gcall.Stepto(-11659,-5605,654);
		gcall.Stepto(-11886,-5502,661);
		gcall.Stepto(-12112,-5400,660);
		gcall.Stepto(-12338,-5298,652);
		gcall.Stepto(-12579,-5228,641);
		gcall.Stepto(-12819,-5165,623);
		gcall.Stepto(-13054,-5107,631);
		gcall.Stepto(-13298,-5058,607);
		gcall.Stepto(-13548,-5022,588);
		gcall.Stepto(-13794,-4989,541);
		gcall.Stepto(-14040,-4956,451);
		gcall.Stepto(-14286,-4925,192);
		gcall.Stepto(-14533,-4909,-47);
		gcall.Stepto(-14777,-4936,-174);
		gcall.Stepto(-15019,-4981,-203);
		gcall.Stepto(-15253,-5071,-204);
		gcall.Stepto(-15466,-5196,-203);
		gcall.Stepto(-15664,-5345,-200);
		gcall.Stepto(-15863,-5493,-197);
		gcall.Stepto(-16062,-5641,-197);
		gcall.Stepto(-16263,-5790,-195);
		gcall.Stepto(-16462,-5937,-193);
		gcall.Stepto(-16661,-6084,-201);
		gcall.Stepto(-16841,-6250,-213);
		gcall.Stepto(-16996,-6447,-205);
		gcall.Stepto(-17148,-6640,-194);
		gcall.Stepto(-17306,-6834,-178);
		gcall.Stepto(-17488,-7000,-172);
		gcall.Stepto(-17689,-7144,-167);
		gcall.Stepto(-17902,-7271,-181);
		gcall.Stepto(-18143,-7335,-190);
		gcall.Stepto(-18390,-7356,-191);
		gcall.Stepto(-18631,-7319,-189);
		gcall.Stepto(-18875,-7258,-186);
		gcall.Stepto(-19116,-7197,-181);
		gcall.Stepto(-19358,-7143,-170);
		gcall.Stepto(-19600,-7088,-179);
		gcall.Stepto(-19846,-7033,-190);
		gcall.Stepto(-20088,-6979,-193);
		gcall.Stepto(-20330,-6924,-193);
		gcall.Stepto(-20572,-6870,-193);
		gcall.Stepto(-20814,-6816,-193);
		gcall.Stepto(-21056,-6761,-183);
		gcall.Stepto(-21298,-6707,-174);
		gcall.Stepto(-21540,-6653,-179);
		gcall.Stepto(-21766,-6559,-184);
		gcall.Stepto(-21968,-6415,-179);
		gcall.Stepto(-22170,-6270,-193);
		gcall.Stepto(-22371,-6126,-200);
		gcall.Stepto(-22573,-5982,-208);
		gcall.Stepto(-22775,-5837,-214);
		gcall.Stepto(-22977,-5693,-225);
		gcall.Stepto(-23178,-5549,-225);
		gcall.Stepto(-23380,-5404,-230);
		gcall.Stepto(-23582,-5260,-221);
		gcall.Stepto(-23787,-5113,-193);
		gcall.Stepto(-23987,-4970,-175);
		gcall.Stepto(-24188,-4826,-172);
		gcall.Stepto(-24390,-4681,-149);
		gcall.Stepto(-24595,-4541,-130);
		gcall.Stepto(-24771,-4426,-113);
		gcall.Stepto(-24820,-4394,-103);
		gcall.Stepto(-25026,-4260,-72);
		gcall.Stepto(-25234,-4124,-37);
		gcall.Stepto(-25442,-3989,8);
		gcall.NewSpend(1);
		gcall.Stepto(-25650,-3853,59);
		gcall.Stepto(-25858,-3718,105);
		gcall.Stepto(-26067,-3581,134);
		gcall.Stepto(-26275,-3446,147);
		gcall.Stepto(-26483,-3310,189);
		gcall.Stepto(-26690,-3175,246);
		gcall.Stepto(-26898,-3040,302);
		gcall.Stepto(-27105,-2903,355);
		gcall.Stepto(-27250,-2766,388);
		gcall.Stepto(-27267,-2743,393);
		Sleep(3000);
		gcall.FindThenKill(0,400,modeNormal | modeAoe | modePickup);
		gcall.Stepto(-27200,-3011,356);
		gcall.Stepto(-27229,-2784,382);
		Sleep(1000);
		gcall.FindThenKill(0,400,modeNormal | modeAoe | modePickup);
		gcall.Stepto(-27200,-3011,356);
		gcall.Stepto(-27229,-2784,382);
		Sleep(1000);
		gcall.PickupTask();//可能问题

		Sleep(6000);
		gcall.FindThenKill(0,400,modeNormal | modeAoe | modePickup);
		Sleep(3000);
		break;
	case 4:
		gcall.NewSpend(2.5);
		gcall.Stepto(-27282,-2749,396);
		gcall.Stepto(-27280,-2750,395);
		gcall.Stepto(-27090,-2899,353);
		gcall.Stepto(-26884,-3036,299);
		gcall.Stepto(-26677,-3173,244);
		gcall.Stepto(-26470,-3310,187);
		gcall.Stepto(-26264,-3448,146);
		gcall.Stepto(-26057,-3585,134);
		gcall.Stepto(-25851,-3722,104);
		gcall.Stepto(-25644,-3859,57);
		gcall.Stepto(-25437,-3996,6);
		gcall.Stepto(-25231,-4134,-39);
		gcall.Stepto(-25024,-4271,-74);
		gcall.Stepto(-24818,-4408,-106);
		gcall.Stepto(-24621,-4538,-132);
		gcall.Stepto(-24559,-4580,-135);
		gcall.Stepto(-24348,-4720,-152);
		gcall.Stepto(-24140,-4858,-172);
		gcall.Stepto(-23934,-4995,-177);
		gcall.Stepto(-23727,-5132,-200);
		gcall.Stepto(-23522,-5268,-221);
		gcall.Stepto(-23311,-5408,-222);
		gcall.Stepto(-23105,-5545,-219);
		gcall.Stepto(-22883,-5657,-215);
		gcall.Stepto(-22664,-5768,-206);
		gcall.Stepto(-22443,-5881,-187);
		gcall.Stepto(-22222,-5994,-179);
		gcall.Stepto(-22003,-6106,-178);
		gcall.Stepto(-21780,-6220,-176);
		gcall.Stepto(-21560,-6333,-174);
		gcall.Stepto(-21341,-6445,-171);
		gcall.Stepto(-21120,-6558,-172);
		gcall.Stepto(-20899,-6672,-185);
		gcall.Stepto(-20678,-6785,-194);
		gcall.Stepto(-20457,-6898,-193);
		gcall.Stepto(-20236,-7011,-193);
		gcall.Stepto(-20007,-7103,-193);
		gcall.Stepto(-19766,-7161,-190);
		gcall.Stepto(-19525,-7220,-174);
		gcall.Stepto(-19282,-7279,-161);
		gcall.Stepto(-19041,-7337,-169);
		gcall.Stepto(-18800,-7396,-169);
		gcall.Stepto(-18559,-7455,-190);
		gcall.Stepto(-18317,-7513,-216);
		gcall.Stepto(-18076,-7572,-228);
		gcall.Stepto(-17832,-7631,-235);
		gcall.Stepto(-17590,-7685,-243);
		gcall.Stepto(-17564,-7690,-240);
		gcall.Stepto(-17371,-7587,-215);
		gcall.Stepto(-17158,-7460,-199);
		gcall.Stepto(-17134,-7446,-195);
		gcall.Stepto(-16993,-7362,-162);
		gcall.Stepto(-16779,-7234,-111);
		gcall.Stepto(-16566,-7107,-110);
		gcall.Stepto(-16353,-6980,-119);
		gcall.Stepto(-16140,-6853,-123);
		gcall.Stepto(-15927,-6725,-117);
		gcall.Stepto(-15713,-6599,-102);
		gcall.Stepto(-15467,-6587,-79);
		gcall.Stepto(-15217,-6598,-60);
		gcall.Stepto(-14972,-6601,-26);
		gcall.Stepto(-14724,-6595,62);
		gcall.Stepto(-14474,-6588,213);
		gcall.Stepto(-14232,-6581,341);
		gcall.Stepto(-13980,-6574,425);
		gcall.Stepto(-13730,-6567,501);
		gcall.Stepto(-13481,-6560,545);
		gcall.Stepto(-13235,-6553,604);
		gcall.Stepto(-12986,-6547,652);
		gcall.Stepto(-12738,-6540,614);
		gcall.Stepto(-12497,-6492,621);
		gcall.Stepto(-12285,-6361,612);
		gcall.Stepto(-12102,-6193,618);
		gcall.Stepto(-11920,-6027,639);
		gcall.Stepto(-11735,-5857,651);
		gcall.Stepto(-11525,-5731,652);
		gcall.Stepto(-11300,-5627,643);
		gcall.Stepto(-11061,-5659,617);
		gcall.Stepto(-10845,-5779,602);
		gcall.Stepto(-10632,-5913,602);
		gcall.Stepto(-10424,-6044,602);
		gcall.Stepto(-10212,-6178,602);
		gcall.Stepto(-10017,-6328,602);
		gcall.Stepto(-9867,-6525,602);
		gcall.Stepto(-9735,-6740,602);
		gcall.Stepto(-9620,-6956,602);
		gcall.Stepto(-9514,-7184,603);
		gcall.Stepto(-9476,-7282,603);
		gcall.NewSpend(1);
		Sleep(1000);
		gcall.DeliverQuests(311,taskid,L"을파소");
		Sleep(2000);
		break;
	case 5:
		gcall.NewSpend(2.5);
		gcall.Stepto(-9429,-7179,602);
		gcall.Stepto(-9505,-7033,602);
		gcall.Stepto(-9620,-6810,603);
		gcall.Stepto(-9814,-6707,602);
		gcall.Stepto(-10061,-6726,602);
		gcall.Stepto(-10312,-6745,592);
		gcall.Stepto(-10534,-6841,585);
		gcall.Stepto(-10722,-7001,583);
		gcall.Stepto(-10872,-7202,591);
		gcall.Stepto(-10916,-7261,597);
		gcall.Stepto(-10987,-7371,595);
		gcall.Stepto(-11118,-7576,595);
		gcall.Stepto(-11120,-7579,595);
		gcall.NewSpend(1);
		Sleep(1000);
		gcall.DeliverQuests(311,taskid,L"위원홍");
		Sleep(2000);
		break;
	case 6:
		gcall.NewSpend(2.5);
		gcall.Stepto(-11151,-7605,595);
		gcall.Stepto(-11194,-7639,595);
		gcall.Stepto(-11265,-7646,596);
		gcall.Stepto(-11266,-7646,596);
		gcall.Stepto(-11282,-7632,596);
		gcall.Stepto(-11287,-7608,597);
		gcall.Stepto(-11287,-7592,597);
		gcall.NewSpend(1);
		Sleep(1000);
		gcall.DeliverQuests(311,taskid,L"하준광");
		Sleep(2000);
		break;
	case 7:
		gcall.NewSpend(2.5);
		gcall.Stepto(-11297,-7523,598);
		gcall.Stepto(-11307,-7453,599);
		gcall.Stepto(-11262,-7414,599);
		gcall.Stepto(-11140,-7361,598);
		gcall.Stepto(-10912,-7262,597);
		gcall.Stepto(-10890,-7252,597);
		gcall.Stepto(-10873,-7215,595);
		gcall.Stepto(-10770,-6991,583);
		gcall.Stepto(-10670,-7033,582);
		gcall.Stepto(-10666,-6766,586);
		gcall.Stepto(-10603,-6527,602);
		gcall.Stepto(-10559,-6287,602);
		gcall.Stepto(-10513,-6037,602);
		gcall.Stepto(-10470,-5795,602);
		gcall.Stepto(-10426,-5552,602);
		gcall.Stepto(-10381,-5307,602);
		gcall.Stepto(-10337,-5062,602);
		gcall.Stepto(-10293,-4820,602);
		gcall.Stepto(-10248,-4573,602);
		gcall.Stepto(-10205,-4331,602);
		gcall.Stepto(-10160,-4087,602);
		gcall.Stepto(-10127,-3839,602);
		gcall.Stepto(-10132,-3591,602);
		gcall.Stepto(-10138,-3346,602);
		gcall.Stepto(-10165,-3097,597);
		gcall.Stepto(-10201,-2852,568);
		gcall.Stepto(-10254,-2610,460);
		gcall.Stepto(-10307,-2373,373);
		gcall.Stepto(-10335,-2352,367);
		gcall.Stepto(-10547,-2223,264);
		gcall.Stepto(-10761,-2093,150);
		gcall.Stepto(-10983,-1983,69);
		gcall.Stepto(-11206,-1877,45);
		gcall.Stepto(-11429,-1770,18);
		gcall.NewSpend(1);
		gcall.Stepto(-11429,-1770,18);
		gcall.Stepto(-11528,-1716,1);
		gcall.Stepto(-11745,-1595,-22);
		gcall.Stepto(-11956,-1468,-22);
		gcall.Stepto(-12169,-1336,-48);
		gcall.Stepto(-12386,-1226,-125);
		gcall.Stepto(-12465,-1195,-150);
		gcall.FindThenKill(0,300,modeNormal | modeAoe | modePickup);
		gcall.Stepto(-12465,-1195,-150);
		Sleep(1000);
		gcall.PickupTask();
		gcall.Stepto(-12589,-1021,-175);
		gcall.Stepto(-12738,-823,-189);
		gcall.Stepto(-12894,-628,-195);
		gcall.Stepto(-13042,-448,-181);
		gcall.Stepto(-13043,-447,-181);
		Sleep(1000);
		gcall.FindThenKill(0,450,modeNormal | modeAoe | modePickup);
		Sleep(1000);
		gcall.Stepto(-13006,-566,-189);
		gcall.Stepto(-13049,-459,-181);
		Sleep(1000);
		gcall.PickupTask();
		Sleep(1000);
		gcall.NewSpend(2.5);
		gcall.Stepto(-13049,-459,-181);
		gcall.Stepto(-13059,-554,-186);
		gcall.Stepto(-13080,-805,-199);
		gcall.Stepto(-13102,-1050,-194);
		gcall.Stepto(-13167,-1288,-189);
		gcall.Stepto(-13283,-1509,-171);
		gcall.Stepto(-13402,-1727,-152);
		gcall.Stepto(-13520,-1945,-141);
		gcall.Stepto(-13639,-2164,-148);
		gcall.Stepto(-13757,-2381,-144);
		gcall.Stepto(-13876,-2600,-150);
		gcall.Stepto(-13980,-2770,-165);
		gcall.Stepto(-14145,-2884,-173);
		gcall.Stepto(-14308,-2999,-178);
		gcall.Stepto(-14465,-3118,-193);
		gcall.Stepto(-14620,-3241,-215);
		gcall.Stepto(-14806,-3389,-236);
		gcall.Stepto(-15003,-3545,-233);
		gcall.Stepto(-15196,-3699,-219);
		gcall.Stepto(-15391,-3853,-208);
		gcall.Stepto(-15585,-4007,-204);
		gcall.Stepto(-15779,-4161,-198);
		gcall.Stepto(-15974,-4316,-196);
		gcall.Stepto(-16186,-4380,-199);
		gcall.Stepto(-16427,-4325,-218);
		gcall.Stepto(-16628,-4194,-211);
		gcall.Stepto(-16781,-3998,-202);
		gcall.Stepto(-16936,-3804,-202);
		gcall.Stepto(-16990,-3741,-203);
		gcall.Stepto(-16970,-3722,-203);
		gcall.Stepto(-16968,-3720,-203);
		gcall.NewSpend(1);
		Sleep(1000);
		gcall.FindThenKill(0,300,modeNormal | modeAoe | modePickup);
		Sleep(1000);
		gcall.Stepto(-17088,-3857,-203);
		gcall.Stepto(-16956,-3709,-203);
		Sleep(1000);
		gcall.PickupTask();
		Sleep(1000);
		gcall.Stepto(-16956,-3709,-203);
		gcall.Stepto(-17041,-3817,-203);
		gcall.Stepto(-17201,-4012,-211);
		gcall.Stepto(-17354,-4200,-207);
		gcall.Stepto(-17367,-4216,-206);
		Sleep(1000);
		gcall.FindThenKill(0,300,modeNormal | modeAoe | modePickup);
		Sleep(1000);
		gcall.Stepto(-17242,-4052,-212);
		gcall.Stepto(-17348,-4197,-207);
		Sleep(1000);
		gcall.PickupTask();
		Sleep(1000);
		gcall.NewSpend(2.5);
		gcall.Stepto(-17348,-4197,-207);
		gcall.Stepto(-17241,-4196,-221);
		gcall.Stepto(-16993,-4181,-217);
		gcall.Stepto(-16744,-4166,-208);
		gcall.Stepto(-16500,-4151,-203);
		gcall.Stepto(-16250,-4136,-185);
		gcall.Stepto(-16003,-4121,-189);
		gcall.Stepto(-15754,-4105,-196);
		gcall.Stepto(-15528,-4017,-204);
		gcall.Stepto(-15328,-3869,-209);
		gcall.Stepto(-15135,-3724,-219);
		gcall.Stepto(-14936,-3568,-232);
		gcall.Stepto(-14743,-3416,-232);
		gcall.Stepto(-14545,-3259,-210);
		gcall.Stepto(-14350,-3104,-190);
		gcall.Stepto(-14155,-2950,-179);
		gcall.Stepto(-13963,-2798,-168);
		gcall.Stepto(-13767,-2642,-158);
		gcall.Stepto(-13573,-2486,-161);
		gcall.Stepto(-13380,-2330,-158);
		gcall.Stepto(-13190,-2176,-147);
		gcall.Stepto(-13093,-1951,-143);
		gcall.Stepto(-13035,-1713,-158);
		gcall.Stepto(-12976,-1467,-175);
		gcall.Stepto(-12964,-1422,-178);
		gcall.randXianlu(0);
		Sleep(1000);
		break;
	case 8:
		gcall.NewSpend(2.5);
		gcall.Stepto(-17053,-4058,-211);
		gcall.Stepto(-16817,-4081,-203);
		gcall.Stepto(-16573,-4112,-210);
		gcall.Stepto(-16327,-4143,-189);
		gcall.Stepto(-16078,-4175,-189);
		gcall.Stepto(-15833,-4199,-200);
		gcall.Stepto(-15595,-4142,-204);
		gcall.Stepto(-15395,-4000,-206);
		gcall.Stepto(-15193,-3857,-212);
		gcall.Stepto(-14988,-3712,-223);
		gcall.Stepto(-14786,-3568,-230);
		gcall.Stepto(-14590,-3429,-219);
		gcall.Stepto(-14383,-3283,-197);
		gcall.Stepto(-14181,-3139,-183);
		gcall.Stepto(-13985,-3000,-174);
		gcall.Stepto(-13777,-2853,-160);
		gcall.Stepto(-13572,-2708,-155);
		gcall.Stepto(-13369,-2563,-159);
		gcall.Stepto(-13169,-2422,-149);
		gcall.Stepto(-12967,-2279,-132);
		gcall.Stepto(-12762,-2134,-118);
		gcall.Stepto(-12562,-1992,-104);
		gcall.Stepto(-12359,-1847,-85);
		gcall.Stepto(-12157,-1705,-50);
		gcall.Stepto(-12091,-1658,-40);
		gcall.Stepto(-12388,-1264,-133);
		gcall.Stepto(-12217,-1391,-49);
		gcall.Stepto(-12018,-1541,-26);
		gcall.Stepto(-11818,-1687,-37);
		gcall.Stepto(-11593,-1792,-2);
		gcall.Stepto(-11367,-1894,32);
		gcall.Stepto(-11142,-1995,44);
		gcall.Stepto(-10914,-2098,99);
		gcall.Stepto(-10687,-2200,207);
		gcall.Stepto(-10461,-2301,325);
		gcall.Stepto(-10244,-2420,379);
		gcall.Stepto(-10087,-2604,476);
		gcall.Stepto(-10058,-2849,559);
		gcall.Stepto(-10070,-3095,596);
		gcall.Stepto(-10076,-3143,598);
		gcall.Stepto(-10077,-3149,598);
		gcall.Stepto(-10107,-3393,602);
		gcall.Stepto(-10137,-3635,602);
		gcall.Stepto(-10167,-3885,602);
		gcall.Stepto(-10119,-4119,602);
		gcall.Stepto(-10031,-4358,602);
		gcall.Stepto(-9946,-4589,602);
		gcall.Stepto(-9860,-4823,602);
		gcall.Stepto(-9774,-5056,602);
		gcall.Stepto(-9689,-5289,602);
		gcall.Stepto(-9603,-5521,602);
		gcall.Stepto(-9518,-5754,602);
		gcall.Stepto(-9464,-5995,602);
		gcall.Stepto(-9451,-6091,602);
		gcall.Stepto(-9448,-6115,602);
		gcall.Stepto(-9414,-6362,601);
		gcall.Stepto(-9420,-6612,601);
		gcall.Stepto(-9431,-6859,602);
		gcall.Stepto(-9444,-7106,601);
		gcall.Stepto(-9452,-7229,603);
		gcall.NewSpend(1);
		gcall.Stepto(-9457,-7279,602);
		Sleep(1000);
		gcall.DeliverQuests(311,taskid,L"을파소");
		Sleep(1000);
		gcall.WearEquipment(L"홍문반지 1단계",EQUITMENT_POS::JIEZHI);
		Sleep(1000);
		
		IsGoonHecheng(EQUITMENT_POS::JIEZHI);
		
		break;
	}
}

void TaskScript::Task_312(int zid,int taskid)
{
	BOOL flaglj = FALSE ;
	switch (taskid)
	{
	case 1:
		gcall.NPCJieRenWu(0x3c6,0,0x3c6,0,0);

		//while (1)
		//{
		//	gcall.FenJieByConfig();
		//}
		lianji14_go();
		
		while (1)
		{
			if (flaglj == FALSE)
			{
				if (gcall.GetPlayerLevel() == 14)
				{
					Sleep(1000);
					gcall.LinQuJiangLi();
					Sleep(1000);
					flaglj = TRUE;
				}
			}
			
			if (gcall.GetPlayerLevel()<15)
			{
				UseExperience();
				lianji14();
			}else
			{
				BOOL flagrs = gcall.Stepto(1417,-5129,13,10,20,1500);
				if (flagrs)
				{
					//Sleep(1000);
					//gcall.Shunyi(L"Lianji14-end");
					//Sleep(1000);
					//gcall.sendcall(id_msg_OverShunyi,(LPVOID)1);//hook
					//Sleep(1000);
					//gcall.Shunyi(L"Lianji14-mai-men");
					//Sleep(1000);
					//gcall.sendcall(id_msg_OverShunyi,(LPVOID)0);//hook
					//Sleep(5000);
					ShunYiResult(2203,L"Lianji14-end",TRUE);
					Sleep(2000);
					ShunYiResult(2203,L"Lianji14-mai-men",FALSE);
					Sleep(2000);
					gcall.hookQietu.unhook();
					gcall.WaitPlans();
					gcall.HeChengWuQi(EQUITMENT_POS::WUQI);
					Sleep(1000);
					gcall.FenJieByConfig();
				}
				break;
			}
		
		}
		gcall.sendcall(id_msg_OverShunyi,(LPVOID)0);//hook
		Sleep(3000);
		/*Sleep(3000);
		执行脚本(13级秘密加工厂-my-上捡.inf,13);
		领取礼包(14);
		Sleep(2000);
		使用物品(자경단의 한방 용봉탕);
		Sleep(3000);
		使用物品(제룡림 약선 용봉탕);
		Sleep(2000);
		武器强化();
		Sleep(1000);
		执行脚本(13级秘密加工厂-my-上捡.inf,14);
		//执行练到14级，上知道还用上用练。

		*/
		gcall.Stepto(-3612,-6133,621);
		gcall.Stepto(-3698,-6103,616);
		gcall.NewSpend(2.5);
		gcall.Stepto(-3934,-6022,579);
		gcall.Stepto(-4170,-5942,549);
		gcall.Stepto(-4412,-5918,567);
		gcall.Stepto(-4663,-5943,574);
		gcall.Stepto(-4907,-5975,573);
		gcall.Stepto(-5152,-6006,568);
		gcall.Stepto(-5399,-6034,594);
		gcall.Stepto(-5649,-6055,608);
		gcall.Stepto(-5896,-6068,592);
		gcall.Stepto(-6141,-6081,548);
		gcall.Stepto(-6393,-6088,509);
		gcall.Stepto(-6639,-6079,521);
		gcall.Stepto(-6885,-6068,557);
		gcall.Stepto(-7137,-6057,581);
		gcall.Stepto(-7387,-6052,597);
		gcall.Stepto(-7623,-6075,596);
		gcall.Stepto(-7880,-6103,586);
		gcall.Stepto(-8123,-6161,576);
		gcall.Stepto(-8355,-6240,575);
		gcall.Stepto(-8593,-6310,575);
		gcall.Stepto(-8832,-6378,571);
		gcall.Stepto(-9071,-6446,571);
		gcall.Stepto(-9311,-6514,595);
		gcall.Stepto(-9554,-6583,602);
		gcall.Stepto(-9791,-6652,602);
		gcall.Stepto(-10036,-6715,602);
		gcall.Stepto(-10271,-6793,592);
		gcall.Stepto(-10504,-6876,585);
		gcall.Stepto(-10552,-6893,584);
		gcall.NewSpend(1);
		Sleep(1000);
		gcall.FixWuqi();
		Sleep(1000);
		gcall.NewSpend(2.5);
		gcall.Stepto(-10552,-6893,584);
		gcall.Stepto(-10412,-6844,587);
		gcall.Stepto(-10181,-6764,596);
		gcall.Stepto(-9943,-6683,602);
		gcall.Stepto(-9704,-6676,602);
		gcall.Stepto(-9511,-6825,603);
		gcall.Stepto(-9485,-7069,602);
		gcall.Stepto(-9478,-7173,602);
		gcall.Stepto(-9529,-7132,603);
		gcall.Stepto(-9649,-6917,603);
		gcall.Stepto(-9647,-6678,602);
		gcall.Stepto(-9579,-6439,602);
		gcall.Stepto(-9512,-6201,602);
		gcall.Stepto(-9444,-5963,602);
		gcall.Stepto(-9377,-5725,602);
		gcall.Stepto(-9309,-5486,602);
		gcall.Stepto(-9241,-5247,602);
		gcall.Stepto(-9174,-5008,602);
		gcall.Stepto(-9106,-4770,602);
		gcall.Stepto(-9038,-4531,602);
		gcall.Stepto(-8921,-4313,602);
		gcall.Stepto(-8778,-4111,593);
		gcall.Stepto(-8636,-3912,584);
		gcall.Stepto(-8491,-3709,566);
		gcall.Stepto(-8346,-3504,568);
		gcall.Stepto(-8201,-3301,551);
		gcall.Stepto(-8057,-3100,543);
		gcall.Stepto(-7915,-2900,527);
		gcall.Stepto(-7771,-2698,506);
		gcall.Stepto(-7626,-2494,482);
		gcall.Stepto(-7482,-2292,458);
		gcall.Stepto(-7338,-2090,432);
		gcall.Stepto(-7196,-1890,407);
		gcall.Stepto(-7052,-1688,385);
		gcall.Stepto(-6907,-1484,376);
		gcall.Stepto(-6764,-1284,363);
		gcall.Stepto(-6618,-1080,356);
		gcall.Stepto(-6466,-885,339);
		gcall.Stepto(-6262,-745,330);
		gcall.Stepto(-6032,-653,327);
		gcall.Stepto(-5810,-596,321);
		gcall.Stepto(-5569,-541,315);
		gcall.Stepto(-5327,-486,316);
		gcall.Stepto(-5085,-431,325);
		gcall.Stepto(-4845,-369,338);
		gcall.Stepto(-4607,-301,353);
		gcall.Stepto(-4368,-230,383);
		gcall.Stepto(-4130,-160,422);
		gcall.Stepto(-3900,-92,465);
		gcall.Stepto(-3654,-18,524);
		gcall.Stepto(-3418,52,574);
		gcall.Stepto(-3180,124,603);
		gcall.Stepto(-2940,191,606);
		gcall.Stepto(-2703,257,610);
		gcall.Stepto(-2463,323,628);
		gcall.Stepto(-2222,385,655);
		gcall.Stepto(-1980,449,675);
		gcall.Stepto(-1743,512,716);
		gcall.Stepto(-1501,575,780);
		gcall.Stepto(-1261,638,831);
		gcall.Stepto(-1019,664,879);
		gcall.Stepto(-819,635,934);
		gcall.Stepto(-809,634,935);
		gcall.Stepto(-724,652,954);
		gcall.Stepto(-482,704,996);
		gcall.Stepto(-236,758,1029);
		gcall.Stepto(-6,844,1058);
		gcall.Stepto(200,981,1069);
		gcall.Stepto(379,1153,1112);
		gcall.Stepto(547,1334,1161);
		gcall.Stepto(675,1546,1221);
		gcall.Stepto(738,1785,1207);
		gcall.Stepto(744,2032,1222);
		gcall.Stepto(685,2271,1244);
		gcall.Stepto(541,2470,1247);
		gcall.Stepto(354,2633,1287);
		gcall.Stepto(163,2791,1295);
		gcall.Stepto(-25,2950,1298);
		gcall.Stepto(-171,3150,1314);
		gcall.Stepto(-220,3363,1308);
		gcall.Stepto(-233,3610,1301);
		gcall.Stepto(-150,3842,1294);
		gcall.Stepto(27,4009,1273);
		gcall.Stepto(252,4113,1266);
		gcall.Stepto(498,4122,1276);
		gcall.Stepto(734,4046,1271);
		gcall.Stepto(970,3970,1274);
		gcall.Stepto(1206,3894,1276);
		gcall.Stepto(1442,3818,1274);
		gcall.Stepto(1678,3742,1254);
		gcall.NewSpend(1);
		gcall.Stepto(1916,3665,1228);
		gcall.Stepto(2159,3616,1205);
		gcall.Stepto(2403,3572,1196);
		gcall.Stepto(2648,3531,1182);
		Sleep(2000);
		gcall.Stepto(2891,3497,1174);
		gcall.WaitPlans();
		gcall.Stepto(2973,3486,1174);
		gcall.Stepto(3210,3454,1133);
		gcall.Stepto(3456,3420,1088);
		gcall.Stepto(3702,3386,1039);
		gcall.Stepto(3947,3352,986);
		gcall.Stepto(4193,3319,943);
		gcall.NewSpend(2.5);
		gcall.Stepto(4439,3285,907);
		gcall.Stepto(4684,3251,879);
		gcall.Stepto(4930,3217,863);
		gcall.Stepto(5175,3184,851);
		gcall.Stepto(5425,3149,827);
		gcall.Stepto(5669,3144,790);
		gcall.Stepto(5896,3245,759);
		gcall.Stepto(6098,3388,731);
		gcall.Stepto(6296,3538,712);
		gcall.Stepto(6487,3699,684);
		gcall.Stepto(6667,3870,646);
		gcall.Stepto(6844,4039,603);
		gcall.Stepto(7026,4211,546);
		gcall.Stepto(7206,4382,489);
		gcall.Stepto(7385,4553,436);
		gcall.Stepto(7510,4768,387);
		gcall.Stepto(7556,5011,362);
		gcall.Stepto(7598,5253,351);
		gcall.Stepto(7640,5498,292);
		gcall.Stepto(7683,5746,218);
		gcall.Stepto(7725,5991,117);
		gcall.Stepto(7767,6233,40);
		gcall.Stepto(7809,6479,-9);
		gcall.Stepto(7852,6724,-43);
		gcall.Stepto(7893,6964,-63);
		gcall.Stepto(7936,7215,-73);
		gcall.Stepto(7978,7458,-60);
		gcall.Stepto(8057,7692,-20);
		gcall.Stepto(8165,7917,-29);
		gcall.Stepto(8272,8139,-55);
		gcall.Stepto(8380,8364,-116);
		gcall.Stepto(8488,8588,-167);
		gcall.Stepto(8616,8798,-182);
		gcall.Stepto(8770,8995,-166);
		gcall.Stepto(8923,9191,-168);
		gcall.Stepto(9075,9386,-185);
		gcall.Stepto(9228,9583,-199);
		gcall.Stepto(9382,9780,-225);
		gcall.Stepto(9535,9976,-253);
		gcall.Stepto(9686,10169,-276);
		gcall.Stepto(9840,10367,-288);
		gcall.Stepto(9992,10562,-304);
		gcall.Stepto(10144,10758,-317);
		gcall.Stepto(10297,10954,-333);
		gcall.Stepto(10450,11150,-371);
		gcall.Stepto(10605,11348,-408);
		gcall.Stepto(10761,11542,-432);
		gcall.Stepto(10917,11733,-436);
		gcall.Stepto(11072,11924,-436);
		gcall.Stepto(11230,12120,-435);
		gcall.Stepto(11379,12320,-432);
		gcall.Stepto(11526,12521,-426);
		gcall.Stepto(11664,12726,-424);
		gcall.Stepto(11798,12938,-414);
		gcall.Stepto(11930,13147,-410);
		gcall.Stepto(12064,13358,-409);
		gcall.Stepto(12196,13567,-409);
		gcall.Stepto(12346,13766,-409);
		gcall.Stepto(12588,13814,-408);
		gcall.Stepto(12746,13825,-401);
		gcall.Stepto(12778,13824,-399);
		gcall.Stepto(13028,13823,-398);
		gcall.Stepto(13248,13919,-398);
		gcall.Stepto(13372,14025,-398);
		gcall.Stepto(13578,14357,-398);
		gcall.Stepto(13597,14393,-398);
		gcall.Stepto(13638,14469,-398);
		gcall.Stepto(13671,14545,-398);
		gcall.Stepto(13680,14601,-398);
		gcall.Stepto(13623,14646,-398);
		gcall.Stepto(13612,14645,-398);
		gcall.NewSpend(1);
		Sleep(1000);
		gcall.DeliverQuests(312,taskid,L"풍대혜");
		Sleep(3000);
		break;
	case 2:
		gcall.NewSpend(2.5);
		gcall.Stepto(13612,14645,-398);
		gcall.Stepto(13632,14636,-398);
		gcall.Stepto(13672,14617,-398);
		gcall.Stepto(13672,14565,-398);
		gcall.Stepto(13643,14494,-398);
		gcall.Stepto(13604,14448,-398);
		gcall.Stepto(13561,14410,-398);
		gcall.Stepto(13559,14405,-398);
		gcall.Stepto(13514,14228,-398);
		gcall.Stepto(13412,14001,-398);
		gcall.Stepto(13203,13877,-398);
		gcall.Stepto(12959,13834,-398);
		gcall.Stepto(12747,13812,-401);
		gcall.Stepto(12440,14015,-409);
		gcall.Stepto(12366,14246,-409);
		gcall.Stepto(12416,14488,-409);
		gcall.Stepto(12491,14723,-407);
		gcall.Stepto(12604,14946,-392);
		gcall.Stepto(12726,15161,-387);
		gcall.Stepto(12774,15247,-387);
		gcall.Stepto(12863,15404,-386);
		gcall.Stepto(12986,15621,-383);
		gcall.Stepto(13108,15835,-381);
		gcall.Stepto(13231,16053,-369);
		gcall.Stepto(13356,16268,-363);
		gcall.Stepto(13559,16405,-361);
		gcall.Stepto(13778,16520,-332);
		gcall.Stepto(13996,16634,-357);
		gcall.Stepto(14216,16750,-382);
		gcall.Stepto(14421,16889,-399);
		gcall.Stepto(14623,17034,-415);
		gcall.Stepto(14826,17180,-427);
		gcall.Stepto(15026,17324,-439);
		gcall.Stepto(15228,17469,-446);
		gcall.Stepto(15429,17614,-469);
		gcall.Stepto(15631,17754,-526);
		gcall.Stepto(15865,17833,-553);
		gcall.Stepto(16115,17831,-546);
		gcall.Stepto(16361,17824,-474);
		gcall.Stepto(16609,17792,-425);
		gcall.Stepto(16848,17734,-388);
		gcall.Stepto(17089,17674,-364);
		gcall.Stepto(17330,17613,-361);
		gcall.Stepto(17572,17552,-362);
		gcall.Stepto(17808,17493,-374);
		gcall.Stepto(18051,17432,-415);
		gcall.Stepto(18294,17371,-457);
		gcall.Stepto(18534,17310,-527);
		gcall.Stepto(18775,17250,-547);
		gcall.Stepto(19012,17179,-524);
		gcall.Stepto(19244,17090,-494);
		gcall.Stepto(19476,17002,-456);
		gcall.Stepto(19707,16914,-457);
		gcall.Stepto(19939,16826,-443);
		gcall.Stepto(20171,16738,-421);
		gcall.Stepto(20403,16649,-402);
		gcall.Stepto(20635,16561,-411);
		gcall.Stepto(20867,16473,-468);
		gcall.Stepto(21100,16386,-490);
		gcall.Stepto(21340,16310,-509);
		gcall.Stepto(21577,16236,-514);
		gcall.Stepto(21813,16161,-508);
		gcall.Stepto(22050,16087,-518);
		gcall.Stepto(22286,16013,-535);
		gcall.Stepto(22523,15938,-535);
		gcall.Stepto(22759,15862,-516);
		gcall.Stepto(22977,15745,-493);
		gcall.Stepto(23194,15625,-463);
		gcall.Stepto(23401,15490,-435);
		gcall.Stepto(23569,15308,-413);
		gcall.Stepto(23722,15112,-389);
		gcall.Stepto(23850,14900,-351);
		gcall.Stepto(23968,14683,-309);
		gcall.Stepto(24081,14462,-245);
		gcall.Stepto(24177,14233,-161);
		gcall.Stepto(24245,13995,-77);
		gcall.Stepto(24302,13749,-30);
		gcall.Stepto(24333,13503,-17);
		gcall.Stepto(24342,13414,-16);
		gcall.NewSpend(1);
		Sleep(1000);
		gcall.DeliverQuests(312,taskid,L"독초거사");
		Sleep(1000);
		break;
	case 3:
		gcall.NewSpend(2.5);
		gcall.Stepto(24286,13431,-16);
		gcall.Stepto(24270,13545,-18);
		gcall.Stepto(24231,13790,-40);
		gcall.Stepto(24198,14036,-93);
		gcall.Stepto(24168,14282,-179);
		gcall.Stepto(24144,14529,-257);
		gcall.Stepto(24165,14775,-303);
		gcall.Stepto(24205,15020,-315);
		gcall.Stepto(24269,15260,-307);
		gcall.Stepto(24329,15388,-290);
		gcall.Stepto(24340,15391,-287);
		gcall.NewSpend(1);
		gcall.Stepto(20730,18454,-33);
		Sleep(1500);
		gcall.PickupTask();
		Sleep(1500);
		gcall.Stepto(24345,15417,-274);
		gcall.Stepto(24351,15182,-292);
		gcall.Stepto(24357,14934,-289);
		gcall.Stepto(24363,14686,-267);
		gcall.Stepto(24369,14438,-214);
		gcall.Stepto(24375,14190,-116);
		gcall.Stepto(24392,13943,-56);
		gcall.Stepto(24512,13732,-18);
		gcall.Stepto(24625,13688,-16);
		gcall.Stepto(24652,13722,-16);
		Sleep(1500);
		gcall.Pickdown();
		Sleep(1500);
		break;
	case 4:
		gcall.NewSpend(2.5);
		gcall.Stepto(24344,13475,-16);
		gcall.Stepto(24323,13675,-23);
		gcall.Stepto(24267,13917,-59);
		gcall.Stepto(24208,14158,-132);
		gcall.Stepto(24086,14369,-217);
		gcall.Stepto(23856,14451,-290);
		gcall.Stepto(23625,14376,-336);
		gcall.Stepto(23433,14219,-367);
		gcall.Stepto(23268,14035,-391);
		gcall.Stepto(23181,13804,-365);
		gcall.Stepto(23129,13561,-352);
		gcall.Stepto(23082,13317,-379);
		gcall.Stepto(23036,13074,-419);
		gcall.Stepto(22987,12831,-468);
		gcall.Stepto(22933,12587,-513);
		gcall.Stepto(22877,12345,-539);
		gcall.Stepto(22815,12108,-552);
		gcall.Stepto(22755,11868,-531);
		gcall.Stepto(22699,11626,-525);
		gcall.Stepto(22653,11382,-505);
		gcall.NewSpend(1);
		gcall.Stepto(22642,11331,-473);
		Sleep(2500);
		gcall.PickupTask();
		Sleep(1500);
		gcall.NewSpend(2.5);
		gcall.Stepto(22642,11331,-473);
		gcall.Stepto(22665,11413,-506);
		gcall.Stepto(22732,11651,-521);
		gcall.Stepto(22800,11889,-526);
		gcall.Stepto(22867,12128,-536);
		gcall.Stepto(22935,12367,-510);
		gcall.Stepto(23002,12605,-473);
		gcall.Stepto(23063,12845,-426);
		gcall.Stepto(23114,13088,-389);
		gcall.Stepto(23161,13332,-345);
		gcall.Stepto(23209,13576,-324);
		gcall.Stepto(23276,13813,-341);
		gcall.Stepto(23430,14006,-328);
		gcall.Stepto(23606,14181,-309);
		gcall.Stepto(23798,14337,-283);
		gcall.Stepto(24027,14389,-231);
		gcall.Stepto(24188,14210,-152);
		gcall.Stepto(24223,13965,-72);
		gcall.Stepto(24183,13721,-32);
		gcall.Stepto(24122,13481,-17);
		gcall.Stepto(24057,13242,-16);
		gcall.Stepto(23991,13003,-15);
		gcall.Stepto(23923,12764,-15);
		gcall.NewSpend(1);
		gcall.Stepto(23890,12646,-15);
		Sleep(1500);
		gcall.Pickdown();
		Sleep(2000);
		break;
	case 5:
		gcall.Stepto(23950,12758,-15);
		gcall.Stepto(24071,12975,-16);
		gcall.Stepto(24212,13178,-16);
		gcall.Stepto(24310,13304,-16);
		Sleep(1000);
		gcall.DeliverQuests(312,taskid,L"독초거사");
		Sleep(2000);
		break;
	}
}

void TaskScript::Task_491(int zid,int taskid)
{
	switch (taskid)
	{
	case 1:
		gcall.NewSpend(2.5);
		gcall.Stepto(-3532,-6204,626);
		gcall.Stepto(-3591,-6170,621);
		gcall.Stepto(-3803,-6048,601);
		gcall.Stepto(-3973,-5871,550);
		gcall.Stepto(-4071,-5642,543);
		gcall.Stepto(-4168,-5410,543);
		gcall.Stepto(-4234,-5171,545);
		gcall.Stepto(-4286,-4933,574);
		gcall.Stepto(-4328,-4685,616);
		gcall.Stepto(-4356,-4439,631);
		gcall.Stepto(-4383,-4195,637);
		gcall.Stepto(-4404,-3945,644);
		gcall.Stepto(-4421,-3698,636);
		gcall.Stepto(-4438,-3451,607);
		gcall.Stepto(-4456,-3203,604);
		gcall.Stepto(-4473,-2957,601);
		gcall.Stepto(-4474,-2709,587);
		gcall.Stepto(-4469,-2459,571);
		gcall.Stepto(-4465,-2211,559);
		gcall.Stepto(-4461,-1964,516);
		gcall.Stepto(-4457,-1716,466);
		gcall.Stepto(-4444,-1468,428);
		gcall.Stepto(-4374,-1228,428);
		gcall.Stepto(-4269,-1005,415);
		gcall.Stepto(-4117,-809,426);
		gcall.Stepto(-3964,-613,440);
		gcall.Stepto(-3806,-423,461);
		gcall.Stepto(-3614,-267,511);
		gcall.Stepto(-3407,-130,557);
		gcall.Stepto(-3200,5,590);
		gcall.Stepto(-2993,142,606);
		gcall.Stepto(-2781,282,606);
		gcall.Stepto(-2553,378,618);
		gcall.Stepto(-2318,440,641);
		gcall.Stepto(-2072,504,663);
		gcall.Stepto(-1831,560,690);
		gcall.Stepto(-1586,605,756);
		gcall.Stepto(-1343,633,815);
		gcall.Stepto(-1095,630,861);
		gcall.Stepto(-847,622,926);
		gcall.Stepto(-815,621,930);
		gcall.Stepto(-539,613,965);
		gcall.Stepto(-285,608,1012);
		gcall.Stepto(-40,639,1026);
		gcall.Stepto(169,770,1048);
		gcall.Stepto(335,952,1076);
		gcall.Stepto(455,1169,1120);
		gcall.Stepto(549,1398,1168);
		gcall.Stepto(638,1630,1220);
		gcall.Stepto(711,1867,1214);
		gcall.Stepto(747,2118,1231);
		gcall.Stepto(700,2344,1245);
		gcall.Stepto(493,2481,1259);
		gcall.Stepto(294,2629,1288);
		gcall.Stepto(97,2778,1290);
		gcall.Stepto(-100,2926,1298);
		gcall.Stepto(-300,3076,1295);
		gcall.Stepto(-366,3129,1300);
		gcall.Stepto(-319,3371,1299);
		gcall.Stepto(-271,3613,1292);
		gcall.Stepto(-223,3856,1286);
		gcall.Stepto(-192,4015,1271);
		gcall.Stepto(-30,4021,1272);
		gcall.Stepto(221,4045,1270);
		gcall.Stepto(469,4068,1275);
		gcall.Stepto(715,4090,1270);
		gcall.Stepto(835,4054,1270);
		gcall.Stepto(1052,3937,1270);
		gcall.Stepto(1281,3823,1277);
		gcall.Stepto(1501,3713,1265);
		gcall.Stepto(1728,3607,1233);
		gcall.Stepto(1976,3575,1217);
		gcall.Stepto(2223,3554,1208);
		gcall.Stepto(2470,3525,1199);
		gcall.Stepto(2718,3505,1181);
		gcall.Stepto(2965,3495,1173);
		gcall.Stepto(3011,3497,1171);
		gcall.Stepto(3268,3500,1124);
		gcall.Stepto(3511,3469,1077);
		gcall.Stepto(3753,3419,1028);
		gcall.Stepto(3997,3368,977);
		gcall.Stepto(4241,3317,936);
		gcall.Stepto(4489,3265,899);
		gcall.Stepto(4732,3215,872);
		gcall.NewSpend(2.5);
		gcall.Stepto(4975,3164,859);
		gcall.Stepto(5219,3113,845);
		gcall.Stepto(5461,3063,818);
		gcall.Stepto(5711,3046,788);
		gcall.Stepto(5933,3153,761);
		gcall.Stepto(6122,3314,734);
		gcall.Stepto(6305,3481,717);
		gcall.Stepto(6492,3652,689);
		gcall.Stepto(6668,3826,653);
		gcall.Stepto(6843,4002,610);
		gcall.Stepto(7018,4177,554);
		gcall.Stepto(7193,4353,496);
		gcall.Stepto(7368,4530,443);
		gcall.Stepto(7540,4708,392);
		gcall.Stepto(7712,4887,342);
		gcall.Stepto(7886,5068,283);
		gcall.Stepto(8048,5257,217);
		gcall.Stepto(8093,5498,155);
		gcall.Stepto(8086,5752,102);
		gcall.Stepto(8078,6000,58);
		gcall.Stepto(8067,6246,18);
		gcall.Stepto(8044,6497,-10);
		gcall.Stepto(7981,6740,-39);
		gcall.Stepto(7917,6978,-62);
		gcall.Stepto(7852,7220,-82);
		gcall.Stepto(7790,7453,-110);
		gcall.Stepto(7724,7699,-133);
		gcall.Stepto(7710,7943,-156);
		gcall.Stepto(7808,8176,-169);
		gcall.Stepto(7965,8360,-169);
		gcall.Stepto(8167,8507,-176);
		gcall.Stepto(8382,8643,-179);
		gcall.Stepto(8582,8789,-182);
		gcall.Stepto(8778,8934,-174);
		gcall.Stepto(8984,9088,-182);
		gcall.Stepto(9182,9237,-199);
		gcall.Stepto(9384,9388,-213);
		gcall.Stepto(9575,9546,-235);
		gcall.Stepto(9767,9705,-255);
		gcall.Stepto(9959,9864,-277);
		gcall.Stepto(10161,10021,-292);
		gcall.Stepto(10385,10121,-327);
		gcall.Stepto(10618,10203,-368);
		gcall.Stepto(10856,10288,-397);
		gcall.Stepto(11092,10372,-423);
		gcall.Stepto(11336,10432,-445);
		gcall.Stepto(11584,10455,-457);
		gcall.Stepto(11829,10500,-470);
		gcall.Stepto(12073,10542,-490);
		gcall.Stepto(12324,10583,-521);
		gcall.Stepto(12569,10622,-547);
		gcall.Stepto(12819,10622,-568);
		gcall.Stepto(13063,10631,-587);
		gcall.Stepto(13307,10683,-611);
		gcall.Stepto(13554,10734,-623);
		gcall.Stepto(13753,10777,-626);
		gcall.Stepto(13859,10800,-596);
		gcall.Stepto(13957,10821,-584);
		gcall.Stepto(14057,10843,-580);
		gcall.Stepto(14155,10864,-578);
		gcall.Stepto(14253,10885,-578);
		gcall.Stepto(14352,10906,-578);
		gcall.Stepto(14450,10927,-578);
		gcall.Stepto(14550,10949,-578);
		gcall.Stepto(14649,10970,-578);
		gcall.Stepto(14725,10987,-578);
		gcall.Stepto(14839,11011,-578);
		gcall.Stepto(14937,11032,-578);
		gcall.Stepto(15035,11053,-578);
		gcall.Stepto(15134,11075,-578);
		gcall.Stepto(15232,11096,-578);
		gcall.Stepto(15332,11117,-578);
		gcall.Stepto(15431,11139,-578);
		gcall.Stepto(15528,11160,-578);
		gcall.Stepto(15629,11181,-578);
		gcall.Stepto(15725,11202,-578);
		gcall.Stepto(15867,11232,-605);
		gcall.Stepto(16109,11285,-572);
		gcall.Stepto(16361,11286,-549);
		gcall.Stepto(16605,11242,-538);
		gcall.Stepto(16849,11198,-528);
		gcall.Stepto(17099,11153,-522);
		gcall.Stepto(17345,11096,-512);
		gcall.Stepto(17585,11026,-501);
		gcall.Stepto(17818,10936,-493);
		gcall.Stepto(18050,10845,-493);
		gcall.Stepto(18280,10754,-501);
		gcall.Stepto(18516,10661,-544);
		gcall.Stepto(18751,10569,-548);
		gcall.Stepto(18991,10499,-545);
		gcall.Stepto(19225,10567,-543);
		gcall.Stepto(19401,10749,-531);
		gcall.Stepto(19560,10940,-513);
		gcall.Stepto(19723,11135,-521);
		gcall.Stepto(19956,11182,-513);
		gcall.Stepto(20204,11191,-518);
		gcall.Stepto(20455,11160,-528);
		gcall.Stepto(20696,11102,-542);
		gcall.Stepto(20943,11040,-523);
		gcall.Stepto(21180,10969,-525);
		gcall.Stepto(21422,10891,-496);
		gcall.Stepto(21658,10814,-477);
		gcall.Stepto(21894,10737,-463);
		gcall.Stepto(22135,10658,-451);
		gcall.Stepto(22282,10848,-478);
		gcall.Stepto(22418,11063,-500);
		gcall.Stepto(22526,11285,-515);
		gcall.Stepto(22609,11526,-531);
		gcall.Stepto(22689,11760,-533);
		gcall.Stepto(22772,12001,-550);
		gcall.Stepto(22853,12235,-547);
		gcall.Stepto(22935,12476,-509);
		gcall.Stepto(23016,12710,-464);
		gcall.Stepto(23097,12948,-398);
		gcall.Stepto(23168,13189,-360);
		gcall.Stepto(23236,13433,-302);
		gcall.Stepto(23306,13671,-295);
		gcall.Stepto(23393,13910,-319);
		gcall.Stepto(23486,14140,-337);
		gcall.Stepto(23690,14284,-306);
		gcall.Stepto(23926,14356,-240);
		gcall.Stepto(24147,14253,-171);
		gcall.Stepto(24229,14022,-86);
		gcall.Stepto(24263,13770,-35);
		gcall.Stepto(24296,13524,-18);
		gcall.Stepto(24303,13472,-16);
		gcall.NewSpend(2.5);
		gcall.Stepto(24300,13426,-16);
		gcall.Stepto(24243,13616,-21);
		gcall.Stepto(24218,13699,-28);
		gcall.Stepto(24160,13895,-61);
		gcall.Stepto(24033,13798,-49);
		gcall.Stepto(23836,13647,-22);
		gcall.Stepto(23639,13496,-29);
		gcall.Stepto(23448,13337,-107);
		gcall.Stepto(23262,13173,-306);
		gcall.Stepto(23082,13015,-406);
		gcall.Stepto(22943,12804,-494);
		gcall.Stepto(22826,12582,-558);
		gcall.Stepto(22722,12357,-585);
		gcall.Stepto(22621,12131,-591);
		gcall.Stepto(22520,11904,-574);
		gcall.Stepto(22419,11679,-574);
		gcall.Stepto(22305,11459,-580);
		gcall.Stepto(22112,11308,-583);
		gcall.Stepto(21874,11239,-587);
		gcall.Stepto(21629,11202,-587);
		gcall.Stepto(21382,11166,-592);
		gcall.Stepto(21139,11130,-573);
		gcall.Stepto(20890,11094,-543);
		gcall.Stepto(20645,11059,-522);
		gcall.Stepto(20400,11023,-446);
		gcall.Stepto(20154,10988,-427);
		gcall.Stepto(19914,10944,-434);
		gcall.Stepto(19695,10827,-464);
		gcall.Stepto(19572,10614,-487);
		gcall.Stepto(19501,10378,-484);
		gcall.Stepto(19503,10131,-437);
		gcall.Stepto(19514,9895,-393);
		gcall.Stepto(19535,9632,-375);
		gcall.Stepto(19555,9385,-414);
		gcall.Stepto(19568,9137,-471);
		gcall.Stepto(19563,8890,-484);
		gcall.Stepto(19533,8644,-485);
		gcall.NewSpend(1);
		Sleep(6000);
		gcall.Stepto(19506,8532,-486);
		gcall.WaitPlans();
		gcall.Stepto(19474,8487,-486);
		gcall.Stepto(19271,8297,-484);
		gcall.Stepto(19054,8176,-486);
		gcall.Stepto(18820,8087,-490);
		gcall.NewSpend(2.5);
		gcall.Stepto(18584,8009,-516);
		gcall.Stepto(18349,7932,-570);
		gcall.Stepto(18113,7855,-653);
		gcall.Stepto(17920,7765,-743);
		gcall.Stepto(17712,7633,-830);
		gcall.Stepto(17517,7478,-875);
		gcall.Stepto(17323,7324,-875);
		gcall.Stepto(17205,7126,-875);
		gcall.Stepto(17214,6879,-875);
		gcall.Stepto(17240,6652,-875);
		gcall.Stepto(17263,6454,-875);
		gcall.Stepto(17286,6254,-875);
		gcall.Stepto(17309,6057,-868);
		gcall.Stepto(17320,5859,-863);
		gcall.Stepto(17266,5669,-860);
		gcall.Stepto(17164,5499,-855);
		gcall.Stepto(17057,5332,-859);
		gcall.Stepto(16949,5165,-860);
		gcall.Stepto(16796,5042,-863);
		gcall.Stepto(16619,4953,-868);
		gcall.Stepto(16423,4923,-870);
		gcall.Stepto(16225,4925,-874);
		gcall.Stepto(16027,4925,-882);
		gcall.Stepto(15828,4919,-869);
		gcall.Stepto(15630,4914,-850);
		gcall.Stepto(15433,4894,-836);
		gcall.Stepto(15238,4857,-831);
		gcall.Stepto(15045,4813,-825);
		gcall.Stepto(14850,4783,-799);
		gcall.Stepto(14654,4814,-792);
		gcall.Stepto(14457,4841,-788);
		gcall.Stepto(14256,4843,-799);
		gcall.Stepto(14058,4823,-806);
		gcall.Stepto(13861,4801,-799);
		gcall.Stepto(13665,4769,-810);
		gcall.Stepto(13470,4733,-826);
		gcall.Stepto(13276,4691,-831);
		gcall.Stepto(13083,4646,-836);
		gcall.Stepto(12890,4601,-848);
		gcall.Stepto(12696,4556,-866);
		gcall.Stepto(12503,4511,-883);
		gcall.Stepto(12317,4443,-910);
		gcall.Stepto(12136,4362,-921);
		gcall.Stepto(11956,4273,-924);
		gcall.Stepto(11779,4184,-967);
		gcall.Stepto(11602,4094,-972);
		gcall.Stepto(11426,4004,-997);
		gcall.Stepto(11256,3902,-1027);
		gcall.Stepto(11087,3798,-1056);
		gcall.Stepto(11094,3930,-1048);
		gcall.Stepto(10683,3374,-1132);
		gcall.Stepto(10612,3188,-1132);
		gcall.Stepto(10553,2999,-1132);
		gcall.NewSpend(1);
		gcall.Stepto(10540,2801,-1143);
		gcall.Stepto(10546,2738,-1147);
		gcall.Stepto(10718,2830,-1134);
		gcall.Stepto(10732,2829,-1134);
		gcall.Stepto(10777,2685,-1135);
		Sleep(1000);
		gcall.sendcall(id_msg_attack, (LPVOID)0x5dca);
		Sleep(1000);
		gcall.sendcall(id_msg_attack, (LPVOID)0x5dca);
		gcall.FindThenKill(0,300,modeNormal | modeAoe | modePickup);
		Sleep(1000);
		gcall.DeliverQuests(491,taskid,L"무명인");
		Sleep(2000);
		break;
	case 2:
		gcall.NewSpend(2.5);
		gcall.Stepto(10717,2793,-1134);
		gcall.Stepto(10498,2895,-1135);
		gcall.Stepto(10445,3128,-1130);
		gcall.Stepto(10460,3380,-1130);
		gcall.Stepto(10620,3563,-1128);
		gcall.Stepto(10811,3722,-1100);
		gcall.Stepto(11023,3849,-1062);
		gcall.Stepto(11241,3968,-1025);
		gcall.Stepto(11455,4086,-988);
		gcall.Stepto(11673,4205,-963);
		gcall.Stepto(11891,4324,-927);
		gcall.Stepto(12110,4443,-922);
		gcall.Stepto(12344,4519,-904);
		gcall.Stepto(12587,4571,-873);
		gcall.Stepto(12829,4624,-851);
		gcall.Stepto(13072,4676,-836);
		gcall.Stepto(13314,4729,-828);
		gcall.Stepto(13559,4764,-817);
		gcall.Stepto(13806,4786,-801);
		gcall.Stepto(14053,4809,-809);
		gcall.Stepto(14300,4816,-798);
		gcall.Stepto(14548,4804,-789);
		gcall.Stepto(14786,4793,-799);
		gcall.Stepto(14984,4789,-823);
		gcall.Stepto(15182,4800,-828);
		gcall.Stepto(15380,4815,-842);
		gcall.Stepto(15577,4838,-845);
		gcall.Stepto(15774,4860,-865);
		gcall.Stepto(15972,4883,-879);
		gcall.Stepto(16169,4906,-878);
		gcall.Stepto(16366,4929,-869);
		gcall.Stepto(16555,4975,-867);
		gcall.Stepto(16717,5091,-861);
		gcall.Stepto(16868,5219,-857);
		gcall.Stepto(17014,5353,-847);
		gcall.Stepto(17139,5505,-848);
		gcall.Stepto(17231,5681,-859);
		gcall.Stepto(17259,5876,-861);
		gcall.Stepto(17250,6074,-865);
		gcall.Stepto(17236,6272,-875);
		gcall.Stepto(17221,6470,-875);
		gcall.Stepto(17207,6668,-875);
		gcall.Stepto(17192,6869,-875);
		gcall.Stepto(17225,7060,-875);
		gcall.Stepto(17346,7214,-875);
		gcall.Stepto(17469,7369,-875);
		gcall.Stepto(17575,7503,-875);
		gcall.Stepto(17727,7645,-823);
		gcall.Stepto(17892,7754,-752);
		gcall.Stepto(18073,7844,-671);
		gcall.Stepto(18251,7932,-596);
		gcall.Stepto(18429,8020,-535);
		gcall.Stepto(18607,8107,-513);
		gcall.Stepto(18785,8195,-484);
		gcall.Stepto(18963,8282,-479);
		gcall.Stepto(19141,8370,-479);
		gcall.Stepto(19318,8460,-483);
		gcall.NewSpend(1);
		gcall.FenJieByConfig();
		Sleep(8000);
		gcall.Stepto(19458,8598,-483);
		gcall.WaitPlans();
		gcall.Stepto(19514,8692,-482);
		gcall.WaitPlans();
		gcall.Stepto(19586,8930,-484);
		gcall.Stepto(19569,9173,-463);
		gcall.Stepto(19559,9856,-371);
		gcall.Stepto(19429,10022,-413);
		gcall.NewSpend(2.5);
		gcall.Stepto(19276,10217,-473);
		gcall.Stepto(19122,10410,-520);
		gcall.Stepto(18957,10596,-558);
		gcall.Stepto(18733,10695,-546);
		gcall.Stepto(18495,10764,-545);
		gcall.Stepto(18254,10811,-501);
		gcall.Stepto(18008,10845,-492);
		gcall.Stepto(17765,10892,-491);
		gcall.Stepto(17520,10939,-500);
		gcall.Stepto(17276,10987,-513);
		gcall.Stepto(17031,11034,-528);
		gcall.Stepto(16788,11081,-536);
		gcall.Stepto(16544,11128,-541);
		gcall.Stepto(16303,11174,-567);
		gcall.Stepto(16057,11203,-585);
		gcall.Stepto(15829,11115,-615);
		gcall.Stepto(15725,11068,-595);
		gcall.Stepto(15633,11026,-584);
		gcall.Stepto(15541,10984,-580);
		gcall.Stepto(15450,10942,-578);
		gcall.Stepto(15360,10900,-578);
		gcall.Stepto(15269,10859,-578);
		gcall.Stepto(15178,10817,-578);
		gcall.Stepto(15087,10775,-578);
		gcall.Stepto(14996,10734,-578);
		gcall.Stepto(14904,10691,-578);
		gcall.Stepto(14814,10650,-578);
		gcall.Stepto(14677,10587,-612);
		gcall.Stepto(14452,10484,-589);
		gcall.Stepto(14226,10380,-569);
		gcall.Stepto(14000,10276,-554);
		gcall.Stepto(13906,10290,-557);
		gcall.Stepto(13665,10351,-580);
		gcall.Stepto(13421,10408,-587);
		gcall.Stepto(13179,10464,-574);
		gcall.Stepto(12942,10520,-563);
		gcall.Stepto(12696,10577,-554);
		gcall.Stepto(12473,10676,-544);
		gcall.Stepto(12257,10805,-528);
		gcall.Stepto(12045,10931,-472);
		gcall.Stepto(11833,11058,-435);
		gcall.Stepto(11619,11186,-426);
		gcall.Stepto(11462,11354,-408);
		gcall.Stepto(11432,11601,-416);
		gcall.Stepto(11401,11847,-435);
		gcall.Stepto(11371,12092,-431);
		gcall.Stepto(11345,12335,-431);
		gcall.Stepto(11442,12570,-425);
		gcall.Stepto(11539,12802,-419);
		gcall.Stepto(11670,13012,-413);
		gcall.Stepto(11819,13214,-410);
		gcall.Stepto(11967,13400,-409);
		gcall.Stepto(12130,13599,-409);
		gcall.Stepto(12294,13785,-409);
		gcall.Stepto(12488,13938,-409);
		gcall.Stepto(12596,13988,-408);
		gcall.Stepto(12675,14019,-407);
		Sleep(1000);
		gcall.DeliverQuests(zid,taskid,L"독초거사");
		Sleep(2000);
		gcall.Stepto(12633,14045,-408);
		gcall.Stepto(12485,14091,-409);
		gcall.Stepto(12246,14161,-409);
		gcall.Stepto(12010,14226,-409);
		gcall.Stepto(11767,14292,-409);
		gcall.Stepto(11531,14356,-409);
		gcall.Stepto(11489,14344,-409);
		gcall.Stepto(11378,14248,-409);
		gcall.SellItemByConfig(L"마을처녀");
		gcall.Stepto(11457,14317,-409);
		gcall.Stepto(11591,14329,-409);
		gcall.Stepto(11792,14327,-409);
		gcall.Stepto(12040,14324,-409);
		gcall.Stepto(12280,14322,-409);
		gcall.Stepto(12348,14278,-409);
		gcall.Stepto(12554,14144,-409);
		gcall.Stepto(12625,14099,-409);
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


void TaskScript::Task_492(int zid,int taskid)
{
	switch (taskid)
	{
	case 1:
		gcall.NewSpend(2.5);
		gcall.Stepto(12632,14029,-408);
		gcall.Stepto(12638,14163,-409);
		gcall.Stepto(12666,14783,-405);
		gcall.Stepto(12681,15146,-386);
		gcall.Stepto(13077,15692,-384);
		gcall.Stepto(13505,16294,-358);
		gcall.Stepto(13925,16884,-393);
		gcall.Stepto(14353,17486,-420);
		gcall.Stepto(14584,17810,-476);
		gcall.Stepto(14993,17829,-502);
		gcall.Stepto(15720,17870,-550);
		gcall.Stepto(16157,17849,-535);
		gcall.Stepto(16853,17638,-382);
		gcall.Stepto(17563,17460,-362);
		gcall.Stepto(18263,17288,-456);
		gcall.Stepto(18984,17110,-530);
		gcall.Stepto(19684,16938,-455);
		gcall.Stepto(19828,16930,-448);
		gcall.Stepto(20485,17213,-318);
		gcall.Stepto(21161,17496,-198);
		gcall.Stepto(21829,17773,-82);
		gcall.Stepto(22483,18043,25);
		gcall.Stepto(23135,18302,108);
		gcall.Stepto(23797,18554,183);
		gcall.Stepto(24476,18781,246);
		gcall.Stepto(25009,18956,298);
		gcall.NewSpend(1);
		Sleep(1000);
		gcall.DeliverQuests(zid,taskid,L"주노인");
		Sleep(1000);
		break;
	case 2:
		gcall.NewSpend(2.5);
		gcall.Stepto(24996,18955,297);
		gcall.Stepto(25614,18699,352);
		gcall.Stepto(25859,18612,396);
		gcall.Stepto(26293,18907,526);
		gcall.Stepto(26899,19318,684);
		gcall.Stepto(27126,19472,749);
		gcall.Stepto(27133,20019,909);
		gcall.Stepto(27161,20747,1143);
		gcall.Stepto(27167,20919,1189);
		gcall.Stepto(27193,21583,1392);
		gcall.Stepto(27221,22319,1603);
		gcall.Stepto(27222,22351,1603);
		gcall.Stepto(27058,22902,1615);
		gcall.Stepto(27038,22969,1620);
		gcall.Stepto(26991,22991,1620);
		gcall.Stepto(26790,23681,1690);
		gcall.NewSpend(1);
		gcall.Stepto(26587,24380,1757);
		gcall.Stepto(26358,25079,1808);
		gcall.Stepto(26222,25490,1845);
		gcall.Stepto(25999,25605,1857);
		gcall.Stepto(25360,25961,1940);
		gcall.Stepto(24746,26336,1982);
		gcall.Stepto(24227,26686,1983);
		gcall.Stepto(23220,26878,1944,10,2,3000);
		gcall.Stepto(23249,26956,1947);
		gcall.Stepto(23336,27188,1959);
		gcall.Stepto(23423,27421,1975);
		gcall.Stepto(23496,27604,2008);
		//过滤怪物(그늘버섯,1);
		//过滤怪物(야생곰,2);2是优先

		Sleep(1000);
		gcall.FindThenKill(0,450,modeNormal | modeAoe | modePickup);
		gcall.Stepto(23496,27604,2008);
		gcall.Stepto(23430,27627,1999);
		gcall.Stepto(23196,27710,1989);
		gcall.Stepto(22966,27802,1982);
		gcall.Stepto(22736,27895,1976);
		gcall.Stepto(22506,27988,1974);
		gcall.Stepto(22276,28081,1975);
		gcall.Stepto(22047,28174,1980);
		gcall.Stepto(22040,28177,1980);
		gcall.Stepto(22086,28027,1971);
		gcall.Stepto(22176,27795,1962);
		gcall.Stepto(22236,27642,1972);
		gcall.Stepto(22249,27622,1972);
		gcall.Stepto(22350,27444,1965);
		Sleep(1000);
		gcall.FindThenKill(0,450,modeNormal | modeAoe | modePickup);
		gcall.Stepto(22353,27428,1965);
		gcall.Stepto(22365,27364,1963);
		gcall.Stepto(22394,27169,1946);
		gcall.Stepto(22429,26923,1930);
		gcall.Stepto(22471,26679,1922);
		gcall.Stepto(22515,26435,1922);
		gcall.Stepto(22558,26191,1915);
		gcall.Stepto(22593,25945,1918);
		gcall.Stepto(22619,25700,1923);
		gcall.Stepto(22628,25615,1924);
		Sleep(1000);
		gcall.FindThenKill(0,450,modeNormal | modeAoe | modePickup);
		gcall.Stepto(22659,25622,1923);
		gcall.Stepto(22897,25682,1925);
		gcall.Stepto(23130,25762,1926);
		gcall.Stepto(23348,25880,1929);
		gcall.Stepto(23561,26008,1946);
		gcall.Stepto(23754,26161,1961);
		gcall.Stepto(23765,26176,1962);
		Sleep(1000);
		gcall.FindThenKill(0,450,modeNormal | modeAoe | modePickup);
		gcall.Stepto(23765,26176,1962);
		gcall.Stepto(23838,26289,1970);
		gcall.Stepto(23948,26433,1974);
		gcall.Stepto(23950,26435,1974);
		gcall.Stepto(24070,26595,1972);
		gcall.Stepto(24141,26693,1983);
		gcall.Stepto(24247,26668,1981);
		gcall.Stepto(24433,26610,1981);
		gcall.Stepto(24615,26539,1983);
		gcall.Stepto(24705,26492,1984);
		Sleep(1000);
		gcall.FindThenKill(0,450,modeNormal | modeAoe | modePickup);
		gcall.randXianlu(0);
		Sleep(1000);
		//过滤怪物(그늘버섯,3);
		//过滤怪物(야생곰,3);3是正常

		break;
	case 3:
		gcall.NewSpend(2.5);
		gcall.Stepto(23157,26828,1939,10,5,3000);
		gcall.Stepto(23377,26955,1958,10,5,3000);
		gcall.Stepto(23989,27369,2044);
		gcall.Stepto(24530,27769,2162);
		gcall.Stepto(25077,28183,2345);
		gcall.Stepto(25641,28609,2528);
		gcall.Stepto(26169,29008,2686);
		gcall.Stepto(26753,29459,2866);
		gcall.Stepto(26951,30152,2988);
		gcall.Stepto(26750,30368,3023);
		gcall.Stepto(26147,30749,3051);
		gcall.Stepto(25550,31124,3176);
		gcall.Stepto(24932,31491,3318);
		gcall.Stepto(24298,31830,3534);
		gcall.Stepto(23796,32323,3618);
		gcall.Stepto(23797,33013,3603);
		gcall.Stepto(24241,33563,3501);
		gcall.Stepto(24695,34111,3335);
		gcall.Stepto(25044,34733,3237);
		gcall.Stepto(25317,35394,3258);
		gcall.Stepto(25577,36050,3202);
		gcall.Stepto(25841,36716,3094);
		gcall.Stepto(25986,37412,3010);
		gcall.Stepto(25809,38101,2846);
		gcall.Stepto(25227,38500,2615);
		gcall.Stepto(24517,38655,2304);
		gcall.Stepto(23798,38752,1979);
		gcall.Stepto(23079,38728,1679);
		gcall.Stepto(22366,38605,1381);
		gcall.Stepto(21761,38179,1116);
		gcall.Stepto(21148,37777,979);
		gcall.Stepto(20511,37402,956);
		gcall.Stepto(19931,36938,956);
		gcall.Stepto(19415,36422,975);
		gcall.Stepto(19107,36189,988);
		gcall.Stepto(19066,36173,990);
		gcall.Stepto(19100,36128,988);
		gcall.Stepto(18618,35953,1038);
		gcall.Stepto(18296,35835,1096);
		gcall.Stepto(18211,35713,1127);
		gcall.Stepto(18196,35692,1131);
		gcall.NewSpend(1);
		Sleep(1000);
		gcall.DeliverQuests(zid,taskid,L"독초거사");
		Sleep(1000);
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

void TaskScript::Task_313(int zid,int taskid)
{
	switch (taskid)
	{
	case 1:
		gcall.NewSpend(2.5);
		gcall.Stepto(18180,35537,1150);
		gcall.Stepto(18160,35650,1140);
		gcall.Stepto(18194,35899,1098);
		gcall.Stepto(18329,36089,1051);
		gcall.Stepto(18566,36175,1019);
		gcall.Stepto(18810,36162,1004);
		gcall.Stepto(19063,36160,990);
		gcall.Stepto(19286,36251,983);
		gcall.Stepto(19481,36400,972);
		gcall.Stepto(19678,36558,956);
		gcall.Stepto(19867,36713,956);
		gcall.Stepto(20063,36873,956);
		gcall.Stepto(20253,37027,956);
		gcall.Stepto(20453,37186,956);
		gcall.Stepto(20646,37338,956);
		gcall.Stepto(20838,37489,957);
		gcall.Stepto(21032,37642,964);
		gcall.Stepto(21224,37793,981);
		gcall.Stepto(21423,37950,1012);
		gcall.Stepto(21611,38118,1078);
		gcall.Stepto(21708,38338,1141);
		gcall.Stepto(21680,38581,1170);
		gcall.Stepto(21586,38816,1183);
		gcall.Stepto(21438,39009,1197);
		gcall.Stepto(21269,39197,1200);
		gcall.Stepto(21105,39379,1219);
		gcall.Stepto(20946,39569,1220);
		gcall.Stepto(20880,39804,1213);
		gcall.Stepto(20859,39960,1225);
		gcall.Stepto(20859,39960,1225);
		gcall.Stepto(20857,40050,1232);
		gcall.NewSpend(1);
		gcall.Stepto(20854,40168,1237);
		gcall.WaitPlans();
		gcall.Stepto(20985,40361,1242);
		gcall.Stepto(21195,40492,1238);
		gcall.Stepto(21419,40605,1220);
		gcall.Stepto(21637,40714,1205);
		gcall.NewSpend(2.5);
		gcall.Stepto(21865,40827,1184);
		gcall.Stepto(22081,40941,1161);
		gcall.Stepto(22238,41135,1136);
		gcall.Stepto(22326,41363,1113);
		gcall.Stepto(22340,41614,1091);
		gcall.Stepto(22264,41846,1072);
		gcall.Stepto(22081,42002,1066);
		gcall.Stepto(21840,42042,1046);
		gcall.Stepto(21588,42083,1021);
		gcall.Stepto(21347,42123,1007);
		gcall.Stepto(21097,42163,988);
		gcall.Stepto(20859,42217,958);
		gcall.Stepto(20670,42382,936);
		gcall.Stepto(20543,42591,913);
		gcall.Stepto(20486,42731,900);
		gcall.Stepto(20477,42851,886);
		gcall.Stepto(20478,43096,858);
		gcall.Stepto(20479,43205,855);
		gcall.Stepto(20919,43540,843);
		gcall.NewSpend(1);
		Sleep(1000);
		gcall.FindThenKill(0,600,modeNormal | modeAoe | modePickup);
		Sleep(2000);
		gcall.Stepto(L"홍삼");
		Sleep(1000);
		gcall.FindThenKill(0,300,modeNormal | modeAoe | modePickup);
		gcall.Stepto(L"홍삼");
		Sleep(1000);
		gcall.FindThenKill(0,300,modeNormal | modeAoe | modePickup);
		break;
	case 2:
		gcall.Stepto(L"홍삼");
		Sleep(1000);
		gcall.DeliverQuests(zid,taskid,L"홍삼");
		Sleep(1000);
		break;
	case 3:
		gcall.Stepto(20901,43579,843);
		gcall.Stepto(21009,43802,844);
		gcall.Stepto(21090,44036,816);
		gcall.Stepto(21142,44213,786);
		gcall.Stepto(21156,44228,783);
		gcall.FindThenKill(0,1000,modeNormal | modeAoe | modePickup);
		Sleep(15000);
		gcall.Stepto(21061,44239,780);
		gcall.Stepto(21060,44312,768);
		gcall.Stepto(21055,44556,701);
		gcall.Stepto(21050,44809,619);
		gcall.Stepto(21045,45054,560);
		gcall.Stepto(21040,45298,510);
		gcall.Stepto(21018,45491,500);
		gcall.FindThenKill(0,1000,modeNormal | modeAoe | modePickup);
		Sleep(20000);
		gcall.Stepto(21023,45715,521);
		gcall.Stepto(21060,45961,555);
		gcall.Stepto(21097,46206,566);
		gcall.Stepto(21135,46451,580);
		gcall.Stepto(21201,46687,612);
		gcall.Stepto(21276,46923,594);
		gcall.Stepto(21356,47158,561);
		gcall.Stepto(21435,47393,580);
		gcall.Stepto(21515,47627,588);
		gcall.Stepto(21605,47838,578);
		gcall.Stepto(21605,47839,578);
		gcall.Stepto(21663,47883,577);
		gcall.Stepto(21858,48036,577);
		gcall.Stepto(21876,48051,577);
		gcall.Stepto(21901,48071,576);
		gcall.Stepto(22096,48225,546);
		gcall.Stepto(22290,48380,540);
		gcall.Stepto(22448,48505,544);
		Sleep(12000);
		break;
	case 4:
		gcall.Stepto(21023,45715,521);
		gcall.Stepto(21060,45961,555);
		gcall.Stepto(21097,46206,566);
		gcall.Stepto(21135,46451,580);
		gcall.Stepto(21201,46687,612);
		gcall.Stepto(21276,46923,594);
		gcall.Stepto(21356,47158,561);
		gcall.Stepto(21435,47393,580);
		gcall.Stepto(21515,47627,588);
		gcall.Stepto(21605,47838,578);
		gcall.Stepto(21605,47839,578);
		gcall.Stepto(21663,47883,577);
		gcall.Stepto(21858,48036,577);
		gcall.Stepto(21876,48051,577);
		gcall.Stepto(21901,48071,576);
		gcall.Stepto(22096,48225,546);
		gcall.Stepto(22290,48380,540);
		gcall.Stepto(22448,48505,544,30,10,5000);
		Sleep(1000);
		gcall.DeliverQuests(zid,taskid,L"홍삼");
		Sleep(1000);
		break;
	case 5:
		gcall.NewSpend(2.5);
		gcall.Stepto(22468,48541,542);
		gcall.Stepto(22604,48747,523);
		gcall.Stepto(22748,48945,382);
		gcall.Stepto(22885,49150,26);
		gcall.Stepto(22957,49391,41);
		gcall.Stepto(22969,49475,45);
		gcall.Stepto(22968,49630,51);
		gcall.Stepto(22936,49874,69);
		gcall.Stepto(22902,50119,79);
		gcall.Stepto(22872,50365,113);
		gcall.Stepto(22854,50612,147);
		gcall.Stepto(22816,50857,246);
		gcall.Stepto(22763,51103,315);
		gcall.Stepto(22711,51345,366);
		gcall.Stepto(22681,51589,391);
		gcall.Stepto(22774,51819,434);
		gcall.Stepto(22867,52046,475);
		gcall.Stepto(22897,52290,476);
		gcall.Stepto(22888,52538,474);
		gcall.Stepto(22870,52785,475);
		gcall.Stepto(22886,53032,476);
		gcall.Stepto(22943,53273,477);
		gcall.Stepto(22996,53515,493);
		gcall.Stepto(22990,53762,536);
		gcall.Stepto(22876,53981,576);
		gcall.Stepto(22728,54179,632);
		gcall.Stepto(22552,54354,689);
		gcall.Stepto(22367,54518,740);
		gcall.Stepto(22181,54683,831);
		gcall.Stepto(21996,54848,907);
		gcall.Stepto(21811,55013,960);
		gcall.Stepto(21614,55161,975);
		gcall.Stepto(21374,55202,1007);
		gcall.Stepto(21124,55182,1029);
		gcall.Stepto(20887,55113,1036);
		gcall.Stepto(20699,54953,1058);
		gcall.Stepto(20541,54763,1072);
		gcall.Stepto(20407,54554,1103);
		gcall.Stepto(20271,54342,1129);
		gcall.Stepto(20128,54141,1136);
		gcall.Stepto(19919,54009,1143);
		gcall.Stepto(19678,53956,1190);
		gcall.Stepto(19309,54052,1292);
		gcall.NewSpend(1);
		break;
	case 6:
		gcall.KeyPress(27);
		gcall.WaitPlans();
		Sleep(3000);
		break;
	case 7:
		gcall.Stepto(32444,23116,1896);
		gcall.Stepto(32444,23116,1895);
		gcall.Stepto(32444,23116,1901);
		gcall.Stepto(32444,23116,1903);
		gcall.Stepto(32439,22969,1916);
		Sleep(1000);
		gcall.DeliverQuests(zid,taskid,L"독초거사");
		Sleep(2000);
		break;
	case 8:
		gcall.Stepto(32547,22966,1906);
		gcall.Stepto(32903,22967,1888);
		gcall.Stepto(33448,23235,1837);
		gcall.Stepto(33800,23145,1919);
		gcall.Stepto(34123,23013,1913);
		gcall.Stepto(34282,22744,1856);
		gcall.Stepto(34242,22670,1859);
		Sleep(1000);
		gcall.PickupSpecTypeTask(200,0x20,L"기연절벽 용맥");
		Sleep(15000);
		break;
	case 9:
		gcall.Stepto(43934,19257,1713);
		gcall.Stepto(44021,19332,1714);
		gcall.Stepto(44207,19492,1717);
		gcall.Stepto(44394,19654,1716);
		gcall.Stepto(44583,19817,1714);
		gcall.Stepto(44678,19899,1722);
		Sleep(1000);
		gcall.PickupSpecTypeTask(200,0x20,L"절벽기지 용맥");
		Sleep(20000);
		break;
	case 10:
		gcall.Stepto(53462,22126,1473);
		gcall.Stepto(53346,22154,1477);
		gcall.Stepto(53106,22227,1479);
		gcall.Stepto(53056,22242,1479);
		Sleep(1000);
		gcall.PickupSpecTypeTask(200,0x20,L"부유석 용맥");
		Sleep(20000);
		break;
	case 11:
		gcall.Stepto(40495,28547,574);
		gcall.Stepto(40527,28574,574);
		gcall.Stepto(40723,28741,574);
		gcall.Stepto(40724,28742,574);
		Sleep(1000);
		gcall.DeliverQuests(zid,0xB,L"번아");
		Sleep(2000);
		break;
	}
}

void TaskScript::Task_494(int zid,int taskid)
{
	switch (taskid)
	{
	case 1:
		gcall.NewSpend(2.5);
		gcall.Stepto(40812,28810,574);
		gcall.Stepto(41008,28962,573);
		gcall.Stepto(41205,29114,579);
		gcall.Stepto(41394,29269,581);
		gcall.Stepto(41472,29499,566);
		gcall.Stepto(41507,29744,531);
		gcall.Stepto(41512,30606,293);
		Sleep(2000);
		break;
	case 2:
		gcall.NewSpend(2.5);
		gcall.Stepto(41541,29990,488);
		gcall.Stepto(41558,30237,432);
		gcall.Stepto(41566,30431,352);
		gcall.Stepto(41572,30572,293);
		gcall.Stepto(41582,30820,209);
		gcall.Stepto(41594,31072,128);
		gcall.Stepto(41674,31301,62);
		gcall.Stepto(41793,31521,16);
		gcall.Stepto(41986,31671,-24);
		gcall.Stepto(42211,31755,-24);
		gcall.Stepto(42462,31770,12);
		gcall.Stepto(42709,31747,82);
		gcall.Stepto(42956,31724,104);
		gcall.Stepto(43203,31701,55);
		gcall.Stepto(43450,31678,-9);
		gcall.Stepto(43693,31697,-38);
		gcall.Stepto(43878,31862,0);
		gcall.Stepto(44056,32035,43);
		gcall.Stepto(44163,32256,102);
		gcall.Stepto(44218,32497,177);
		gcall.Stepto(44252,32742,262);
		gcall.Stepto(44287,32989,369);
		gcall.Stepto(44321,33235,459);
		gcall.Stepto(44356,33480,494);
		gcall.Stepto(44402,33724,506);
		gcall.Stepto(44435,33885,497);
		gcall.NewSpend(1);
		Sleep(1000);
		gcall.DeliverQuests(zid,taskid,L"독초거사");
		Sleep(1000);
		break;
	case 3:
		gcall.Stepto(44426,33867,497);
		gcall.Stepto(44358,33989,495);
		gcall.Stepto(44237,34207,489);
		gcall.Stepto(44145,34366,501);
		Sleep(1000);
		gcall.DeliverQuests(zid,taskid,L"파륜성 진웅",4);
		Sleep(2000);
		break;
	case 4:
		gcall.Stepto(41383,29622,548);
		gcall.Stepto(41408,29763,529);
		gcall.Stepto(41450,30004,486);
		gcall.Stepto(41493,30253,427);
		gcall.Stepto(41524,30428,357);
		gcall.Stepto(41532,30476,335);
		gcall.Stepto(41730,31611,11);
		gcall.Stepto(41975,31643,-18);
		gcall.Stepto(42221,31683,-27);
		gcall.Stepto(42459,31721,12);
		gcall.Stepto(42710,31743,82);
		gcall.Stepto(42960,31740,104);
		gcall.Stepto(43199,31735,57);
		gcall.Stepto(43459,31730,-12);
		gcall.Stepto(43704,31735,-34);
		gcall.Stepto(43921,31857,4);
		gcall.Stepto(44076,32047,47);
		gcall.Stepto(44199,32264,108);
		gcall.Stepto(44249,32509,216);
		gcall.Stepto(44288,32749,270);
		gcall.Stepto(44327,32996,374);
		gcall.Stepto(44360,33243,463);
		gcall.Stepto(44381,33489,498);
		gcall.Stepto(44348,33732,509);
		gcall.Stepto(44171,33903,506);
		gcall.Stepto(43955,34024,494);
		gcall.Stepto(43733,34136,510);
		gcall.Stepto(43502,34226,515);
		gcall.Stepto(43281,34337,531);
		gcall.Stepto(43119,34525,553);
		gcall.Stepto(42973,34727,542);
		gcall.Stepto(42828,34929,542);
		gcall.Stepto(42712,35147,541);
		gcall.Stepto(42643,35387,535);
		gcall.Stepto(42595,35630,534);
		gcall.Stepto(42553,35875,556);
		gcall.Stepto(42508,36119,553);
		gcall.Stepto(42493,36186,550);
		Sleep(10000);
		gcall.Stepto(L"홍삼");
		Sleep(1000);
		gcall.FindThenKill(0,800,modeNormal | modeAoe | modeGoback | modePickup);
		Sleep(1000);
		gcall.FindThenKill(0,800,modeNormal | modeAoe | modeGoback | modePickup);
		gcall.Stepto(L"홍삼");
		Sleep(1000);
		gcall.DeliverQuests(zid,taskid,L"홍삼");
		Sleep(2000);
		break;
	case 5:
		gcall.NewSpend(2.5);
		gcall.Stepto(41383,29622,548);
		gcall.Stepto(41408,29763,529);
		gcall.Stepto(41450,30004,486);
		gcall.Stepto(41493,30253,427);
		gcall.Stepto(41524,30428,357);
		gcall.Stepto(41532,30476,335);
		gcall.Stepto(41730,31611,11);
		gcall.Stepto(41975,31643,-18);
		gcall.Stepto(42221,31683,-27);
		gcall.Stepto(42459,31721,12);
		gcall.Stepto(42710,31743,82);
		gcall.Stepto(42960,31740,104);
		gcall.Stepto(43199,31735,57);
		gcall.Stepto(43459,31730,-12);
		gcall.Stepto(43704,31735,-34);
		gcall.Stepto(43921,31857,4);
		gcall.Stepto(44076,32047,47);
		gcall.Stepto(44199,32264,108);
		gcall.Stepto(44249,32509,216);
		gcall.Stepto(44288,32749,270);
		gcall.Stepto(44327,32996,374);
		gcall.Stepto(44360,33243,463);
		gcall.Stepto(44381,33489,498);
		gcall.Stepto(44348,33732,509);
		gcall.Stepto(44171,33903,506);
		gcall.Stepto(43955,34024,494);
		gcall.Stepto(43733,34136,510);
		gcall.Stepto(43502,34226,515);
		gcall.Stepto(43281,34337,531);
		gcall.Stepto(43119,34525,553);
		gcall.Stepto(42973,34727,542);
		gcall.Stepto(42828,34929,542);
		gcall.Stepto(42712,35147,541);
		gcall.Stepto(42643,35387,535);
		gcall.Stepto(42595,35630,534);
		gcall.Stepto(42553,35875,556);
		gcall.Stepto(42508,36119,553);
		gcall.Stepto(42493,36186,550);
		gcall.Stepto(42526,36014,555);
		gcall.NewSpend(1);
		gcall.Stepto(42526,36014,555);
		gcall.Stepto(42515,36035,555);
		gcall.Stepto(42397,36253,548);
		gcall.Stepto(42279,36471,561);
		gcall.Stepto(42161,36691,615);
		gcall.Stepto(42043,36909,655);
		gcall.Stepto(41927,37129,688);
		gcall.Stepto(41841,37361,719);
		gcall.Stepto(41810,37488,725);
		gcall.Stepto(41809,37448,725);
		Sleep(20000);
		gcall.Stepto(41786,38065,706);
		gcall.Stepto(41814,38342,704);
		gcall.Stepto(41932,38539,708);
		gcall.Stepto(42053,38781,707);
		gcall.Stepto(42151,38975,704);
		gcall.Stepto(42275,39038,700);
		Sleep(1000);
		gcall.FindThenKill(0,300,modeNormal | modeAoe | modePickup);
		gcall.Stepto(42126,39083,698);
		gcall.Stepto(41848,39167,703);
		gcall.Stepto(41773,39251,700);
		Sleep(1000);
		gcall.FindThenKill(0,300,modeNormal | modeAoe | modePickup);
		gcall.Stepto(41796,39350,693);
		gcall.Stepto(41837,39526,671);
		gcall.Stepto(41894,39768,642);
		gcall.Stepto(41952,40009,629);
		gcall.Stepto(41967,40072,625);
		Sleep(1000);
		gcall.FindThenKill(0,300,modeNormal | modeAoe | modePickup);
		gcall.Stepto(42075,40046,628);
		gcall.Stepto(42316,39988,640);
		gcall.Stepto(42557,39930,663);
		gcall.Stepto(42790,39854,675);
		gcall.Stepto(43013,39747,688);
		gcall.Stepto(43062,39719,691);
		Sleep(1000);
		gcall.FindThenKill(0,300,modeNormal | modeAoe | modePickup);
		gcall.Stepto(42520,39687,647);
		gcall.FenJieByConfig();
		break;
	case 6:
		gcall.NewSpend(2.5);
		gcall.Stepto(41383,29622,548);
		gcall.Stepto(41408,29763,529);
		gcall.Stepto(41450,30004,486);
		gcall.Stepto(41493,30253,427);
		gcall.Stepto(41524,30428,357);
		gcall.Stepto(41532,30476,335,10,20,3000);
		gcall.Stepto(41730,31611,11,10,20,3000);
		gcall.Stepto(41975,31643,-18,10,20,3000);
		gcall.Stepto(42221,31683,-27);
		gcall.Stepto(42459,31721,12);
		gcall.Stepto(42710,31743,82);
		gcall.Stepto(42960,31740,104);
		gcall.Stepto(43199,31735,57);
		gcall.Stepto(43459,31730,-12);
		gcall.Stepto(43704,31735,-34);
		gcall.Stepto(43921,31857,4);
		gcall.Stepto(44076,32047,47);
		gcall.Stepto(44199,32264,108);
		gcall.Stepto(44249,32509,216);
		gcall.Stepto(44288,32749,270);
		gcall.Stepto(44327,32996,374);
		gcall.Stepto(44360,33243,463);
		gcall.Stepto(44381,33489,498);
		gcall.Stepto(44348,33732,509);
		gcall.Stepto(44171,33903,506);
		gcall.Stepto(43955,34024,494);
		gcall.Stepto(43733,34136,510);
		gcall.Stepto(43502,34226,515);
		gcall.Stepto(43281,34337,531);
		gcall.Stepto(43119,34525,553);
		gcall.Stepto(42973,34727,542);
		gcall.Stepto(42828,34929,542);
		gcall.Stepto(42712,35147,541);
		gcall.Stepto(42643,35387,535);
		gcall.Stepto(42595,35630,534);
		gcall.Stepto(42553,35875,556);
		gcall.Stepto(42508,36119,553);
		gcall.Stepto(42493,36186,550);
		gcall.Stepto(42464,36250,545);
		gcall.Stepto(42339,36465,552);
		gcall.Stepto(42210,36679,605);
		gcall.Stepto(42080,36891,653);
		gcall.Stepto(41954,37105,685);
		gcall.Stepto(41864,37335,715);
		gcall.Stepto(41823,37579,715);
		gcall.Stepto(41810,37829,712);
		gcall.Stepto(41804,38076,705);
		gcall.Stepto(41807,38325,703);
		gcall.Stepto(41834,38572,712);
		gcall.Stepto(41892,38811,710);
		gcall.Stepto(41958,39051,706);
		gcall.Stepto(41977,39117,701);
		gcall.Stepto(42065,39280,682);
		gcall.Stepto(42242,39454,663);
		gcall.Stepto(42465,39555,655);
		gcall.Stepto(42709,39596,661);
		gcall.Stepto(42961,39626,681);
		gcall.Stepto(43208,39656,692);
		gcall.Stepto(43456,39687,697);
		gcall.Stepto(43702,39716,708);
		gcall.Stepto(43951,39744,715);
		gcall.Stepto(44199,39771,719);
		gcall.Stepto(44445,39801,744);
		gcall.Stepto(44577,39818,744);
		gcall.NewSpend(1);
		Sleep(10000);
		gcall.Stepto(L"수삼");
		Sleep(1000);
		gcall.sendcall(id_msg_attack, (LPVOID)0x5dc1);//r
		Sleep(100);
		gcall.sendcall(id_msg_attack, (LPVOID)0x5dca);//tab
		Sleep(1000);
		gcall.sendcall(id_msg_attack, (LPVOID)0x5dca);//tab
		Sleep(1000);
		gcall.Stepto(L"수삼");
		Sleep(1000);
		gcall.sendcall(id_msg_attack, (LPVOID)0x5dc1);//r
		Sleep(100);
		gcall.sendcall(id_msg_attack, (LPVOID)0x5dca);//tab
		Sleep(1000);
		gcall.sendcall(id_msg_attack, (LPVOID)0x5dca);//tab
		Sleep(1000);
		gcall.Stepto(L"수삼");
		Sleep(1000);
		gcall.sendcall(id_msg_attack, (LPVOID)0x5dc1);//r
		Sleep(100);
		gcall.sendcall(id_msg_attack, (LPVOID)0x5dca);//tab
		Sleep(1000);
		gcall.sendcall(id_msg_attack, (LPVOID)0x5dca);//tab
		Sleep(1000);
		//gcall.FindThenKill(0,1000,modeNormal | modeAoe | modePickup);//以后可增加必杀

		//Sleep(1500);
		gcall.Stepto(L"수삼");
		gcall.DeliverQuests(zid,taskid,L"수삼");
		Sleep(1500);
		break;
	case 7:
		gcall.NewSpend(2.5);
		gcall.Stepto(41383,29622,548);
		gcall.Stepto(41408,29763,529);
		gcall.Stepto(41450,30004,486);
		gcall.Stepto(41493,30253,427);
		gcall.Stepto(41524,30428,357);
		gcall.Stepto(41532,30476,335);
		gcall.Stepto(41730,31611,11);
		gcall.Stepto(41975,31643,-18);
		gcall.Stepto(42221,31683,-27);
		gcall.Stepto(42459,31721,12);
		gcall.Stepto(42710,31743,82);
		gcall.Stepto(42960,31740,104);
		gcall.Stepto(43199,31735,57);
		gcall.Stepto(43459,31730,-12);
		gcall.Stepto(43704,31735,-34);
		gcall.Stepto(43921,31857,4);
		gcall.Stepto(44076,32047,47);
		gcall.Stepto(44199,32264,108);
		gcall.Stepto(44249,32509,216);
		gcall.Stepto(44288,32749,270);
		gcall.Stepto(44327,32996,374);
		gcall.Stepto(44360,33243,463);
		gcall.Stepto(44381,33489,498);
		gcall.Stepto(44348,33732,509);
		gcall.Stepto(44171,33903,506);
		gcall.Stepto(43955,34024,494);
		gcall.Stepto(43733,34136,510);
		gcall.Stepto(43502,34226,515);
		gcall.Stepto(43281,34337,531);
		gcall.Stepto(43119,34525,553);
		gcall.Stepto(42973,34727,542);
		gcall.Stepto(42828,34929,542);
		gcall.Stepto(42712,35147,541);
		gcall.Stepto(42643,35387,535);
		gcall.Stepto(42595,35630,534);
		gcall.Stepto(42553,35875,556);
		gcall.Stepto(42508,36119,553);
		gcall.Stepto(42493,36186,550);
		gcall.Stepto(42464,36250,545);
		gcall.Stepto(42339,36465,552);
		gcall.Stepto(42210,36679,605);
		gcall.Stepto(42080,36891,653);
		gcall.Stepto(41954,37105,685);
		gcall.Stepto(41864,37335,715);
		gcall.Stepto(41823,37579,715);
		gcall.Stepto(41810,37829,712);
		gcall.Stepto(41804,38076,705);
		gcall.Stepto(41807,38325,703);
		gcall.Stepto(41834,38572,712);
		gcall.Stepto(41892,38811,710);
		gcall.Stepto(41958,39051,706);
		gcall.Stepto(41977,39117,701);
		gcall.Stepto(42065,39280,682);
		gcall.Stepto(42242,39454,663);
		gcall.Stepto(42465,39555,655);
		gcall.Stepto(42709,39596,661);
		gcall.Stepto(42961,39626,681);
		gcall.Stepto(43208,39656,692);
		gcall.Stepto(43456,39687,697);
		gcall.Stepto(43702,39716,708);
		gcall.Stepto(43951,39744,715);
		gcall.Stepto(44199,39771,719);
		gcall.Stepto(44445,39801,744);
		gcall.Stepto(44577,39818,744);
		gcall.NewSpend(1);
		gcall.Stepto(44743,39933,745);
		gcall.Stepto(44945,40076,756);
		gcall.Stepto(45168,40184,788);
		gcall.Stepto(45410,40229,825);
		gcall.Stepto(45658,40227,863);
		gcall.Stepto(45906,40202,903);
		gcall.Stepto(46151,40164,930);
		gcall.Stepto(46260,40144,930);
		gcall.Stepto(46503,40099,863);
		gcall.Stepto(46530,40094,852);
		Sleep(20000);
		gcall.Stepto(46662,40073,796);
		gcall.Stepto(46682,40070,787);
		gcall.Stepto(46925,40019,727);
		gcall.Stepto(47163,39950,702);
		gcall.Stepto(47381,39835,711);
		gcall.Stepto(47501,39750,721);
		gcall.Stepto(47500,39601,725);
		gcall.Stepto(47488,39354,762);
		gcall.Stepto(47475,39106,819);
		gcall.Stepto(47461,38858,880);
		gcall.Stepto(47448,38610,953);
		gcall.Stepto(47442,38484,994);
		Sleep(2000);
		gcall.FindThenKill(0,300,modeNormal | modeAoe | modePickup);
		gcall.Stepto(47430,38364,1024);
		gcall.Stepto(47432,38303,1034);
		gcall.Stepto(47428,38104,1040);
		gcall.Stepto(47423,37906,1040);
		gcall.Stepto(47421,37792,1033);
		Sleep(1000);
		gcall.FindThenKill(0,300,modeNormal | modeAoe | modePickup);
		gcall.Stepto(47413,37708,1022);
		gcall.Stepto(47366,37567,1012);
		gcall.Stepto(47287,37332,985);
		gcall.Stepto(47220,37093,993);
		gcall.Stepto(47272,37019,991);
		gcall.Stepto(47389,36983,993);
		Sleep(1000);
		gcall.FindThenKill(0,300,modeNormal | modeAoe | modePickup);
		gcall.Stepto(47387,36868,996);
		gcall.Stepto(47377,36620,1000);
		gcall.Stepto(47367,36372,988);
		gcall.Stepto(47366,36345,986);
		Sleep(1000);
		gcall.FindThenKill(0,300,modeNormal | modeAoe | modePickup);
		gcall.Stepto(47345,36219,976);
		gcall.Stepto(47319,36082,963);
		gcall.Stepto(47279,35888,945);
		gcall.Stepto(47233,35695,935);
		gcall.Stepto(47212,35609,930);
		Sleep(1000);
		gcall.FindThenKill(0,600,modeNormal | modeAoe | modePickup);
		Sleep(1000);
		gcall.FindThenKill(0,300,modeNormal | modeAoe | modePickup);
		gcall.Stepto(47131,35609,929);
		gcall.Stepto(47119,35612,929);
		gcall.Stepto(46881,35681,929);
		gcall.Stepto(46646,35758,938);
		gcall.Stepto(46498,35808,949);
		gcall.Stepto(46556,35870,942);
		gcall.Stepto(46595,35892,942);
		gcall.Stepto(46810,36015,945);
		gcall.Stepto(47026,36136,955);
		gcall.Stepto(47223,36286,974);
		gcall.Stepto(47231,36293,975);
		Sleep(1000);
		gcall.FindThenKill(0,1500,modeNormal | modeAoe | modePickup);
		Sleep(1000);
		gcall.FenJieByConfig();
		Sleep(1000);
		gcall.Stepto(46936,35948,944,20,20,3000);
		Sleep(1000);
		gcall.PickupTask();
		Sleep(1000);
		break;
	case 8:
		gcall.NewSpend(2.5);
		gcall.Stepto(46722,35685,936,20,20,1500);
		gcall.Stepto(46474,35684,955);
		gcall.Stepto(46227,35697,972);
		gcall.Stepto(45979,35710,990);
		gcall.Stepto(45731,35704,987);
		gcall.Stepto(45483,35697,992);
		gcall.Stepto(45236,35679,1011);
		gcall.Stepto(45071,35650,1010);
		gcall.Stepto(45020,35570,1000);
		gcall.Stepto(44888,35360,632);
		gcall.Stepto(44788,35135,491);
		gcall.Stepto(44731,34894,496);
		gcall.Stepto(44678,34652,508);
		gcall.Stepto(44592,34420,509);
		gcall.Stepto(44380,34316,481);
		gcall.Stepto(44154,34379,501);
		gcall.Stepto(44153,34380,501);
		gcall.Stepto(44153,34380,501);
		gcall.Stepto(44179,34320,497);
		gcall.Stepto(44259,34080,490);
		gcall.Stepto(44318,33843,504);
		gcall.Stepto(44351,33695,510);
		gcall.NewSpend(1);
		Sleep(1000);
		gcall.DeliverQuests(zid,taskid,L"홍삼");
		Sleep(2000);
		break;
	case 9:
		gcall.Stepto(44351,33695,510);
		gcall.Stepto(44431,33677,509);
		gcall.Stepto(44447,33674,510);
		Sleep(1000);
		gcall.DeliverQuests(zid,taskid,L"수삼");
		Sleep(2000);
		break;
	case 10:
		gcall.NewSpend(2.5);
		gcall.Stepto(47035,35941,944);
		gcall.Stepto(46829,36002,945);
		gcall.Stepto(46601,35904,942);
		gcall.Stepto(46370,35814,961);
		gcall.Stepto(46126,35770,979);
		gcall.Stepto(45881,35736,981);
		gcall.Stepto(45635,35701,988);
		gcall.Stepto(45389,35667,1010);
		gcall.Stepto(45189,35639,1013);
		gcall.Stepto(45022,35471,982);
		gcall.Stepto(44856,35287,583);
		gcall.Stepto(44762,35060,487);
		gcall.Stepto(44712,34817,499);
		gcall.Stepto(44655,34576,510);
		gcall.Stepto(44548,34353,497);
		gcall.Stepto(44433,34133,483);
		gcall.Stepto(44370,33895,499);
		gcall.Stepto(44426,33721,507);
		gcall.NewSpend(1);
		Sleep(1000);
		gcall.NPCJieRenWu(0x3c6,0,0x3c6,0,0);
		Sleep(2000);
		gcall.DeliverQuests(966, 2, L"수삼");
		Sleep(1000);
		gcall.DeliverQuests(966, 1, L"수삼");
		Sleep(1000);
		/*gcall.NewSpend(2.5);
		gcall.Stepto(46722,35685,936,20,20,1500);
		gcall.Stepto(46474,35684,955);
		gcall.Stepto(46227,35697,972);
		gcall.Stepto(45979,35710,990);
		gcall.Stepto(45731,35704,987);
		gcall.Stepto(45483,35697,992);
		gcall.Stepto(45236,35679,1011);
		gcall.Stepto(45071,35650,1010);
		gcall.Stepto(45020,35570,1000);
		gcall.Stepto(44888,35360,632);
		gcall.Stepto(44788,35135,491);
		gcall.Stepto(44731,34894,496);
		gcall.Stepto(44678,34652,508);
		gcall.Stepto(44592,34420,509);
		gcall.Stepto(44380,34316,481);
		gcall.Stepto(44154,34379,501);
		gcall.Stepto(44153,34380,501);
		gcall.Stepto(44153,34380,501);
		gcall.Stepto(44179,34320,497);
		gcall.Stepto(44259,34080,490);
		gcall.Stepto(44318,33843,504);
		gcall.Stepto(44351,33695,510);
		gcall.NewSpend(1);
		gcall.Stepto(44447,33674,510);
		gcall.Stepto(44457,33873,500);
		gcall.Stepto(44457,33881,499);*/
		gcall.Stepto(44444,33890,497);
		Sleep(1000);
		gcall.DeliverQuests(zid,0xA,L"독초거사");
		Sleep(1000);
		
		break;
	case 11:
		gcall.Stepto(44470,33730,511);
		Sleep(1000);
		gcall.DeliverQuests(zid,0xB,L"수삼");//优先进入浑天

		Sleep(1000);
		gcall.DeliverQuests(zid,0xC,L"수삼");
		Sleep(1000);
		gcall.NewBag();
		Sleep(1000);
		break;
	case 12:
		gcall.Stepto(44435,33793,503);
		gcall.Stepto(44349,33943,498);
		gcall.Stepto(44231,34162,487);
		gcall.Stepto(44148,34323,500);
		Sleep(1000);
		gcall.NewBag();
		Sleep(1000);
		gcall.DeliverQuests(zid,0xD,L"파륜성 진웅",4,0);
		Sleep(1000);
		break;
	case 13:
		gcall.Stepto(44148,34323,500);
		gcall.Stepto(44162,34303,498);
		gcall.Stepto(44322,34111,487);
		gcall.Stepto(44425,33995,490);
		Sleep(1000);
		gcall.DeliverQuests(zid,0xE,L"독초거사");
		Sleep(1000);
		break;
	}
}

void TaskScript::Task_314(int zid,int taskid)
{
	switch (taskid)
	{
	case 1:
		gcall.HeChengWuQi_Po5(EQUITMENT_POS::WUQI,L"천령도끼");
		Sleep(1000);
		gcall.HeChengWuQi(EQUITMENT_POS::WUQI);
		Sleep(1000);
		IsGoonHecheng(EQUITMENT_POS::WUQI);
		//执行3次合成武魂，保证到10.
		gcall.WearEquipment(L"홍문목걸이 1단계",EQUITMENT_POS::XIANGLIAN);
		Sleep(1000);
		IsGoonHecheng(EQUITMENT_POS::XIANGLIAN);
		Sleep(1000);
		gcall.DeliverQuests(zid, 1, NULL,0,0,1);
		
		/*while (1)
		{
		if (gcall.isTalentPanelShow())
		{
		Sleep(1000);
		break;
		}else
		{
		gcall.OpenTalentUI();
		}
		Sleep(1000);
		}
		gcall.JiaJiNengDian(0x135);
		Sleep(1000);
		gcall.QueRenJiNengDian();
		Sleep(1000);*/
		gcall.AddTalent(0x135);
		if (gcall.isTalentPanelShow())
		{
			gcall.OpenTalentUI();
			Sleep(1000);
		}
		break;
	case 2:
		gcall.NewSpend(2.5);
		gcall.Stepto(41324,29216,581);
		gcall.Stepto(41324,29216,581);
		gcall.Stepto(41361,29449,572);
		gcall.Stepto(41396,29695,539);
		gcall.Stepto(41429,29941,497);
		gcall.Stepto(41468,30185,450);
		gcall.Stepto(41503,30390,374);
		gcall.WaitPlans();
		gcall.Stepto(41525,30493,330);
		gcall.Stepto(41547,30604,287);
		gcall.Stepto(41600,30846,198);
		gcall.Stepto(41655,31088,112);
		gcall.Stepto(41719,31327,53);
		gcall.Stepto(41808,31531,13);
		gcall.Stepto(42020,31658,-25);
		gcall.Stepto(42259,31726,-20);
		gcall.Stepto(42501,31775,23);
		gcall.Stepto(42749,31794,84);
		gcall.Stepto(43000,31781,102);
		gcall.Stepto(43248,31763,45);
		gcall.Stepto(43495,31745,-17);
		gcall.Stepto(43739,31765,-28);
		gcall.Stepto(43956,31886,12);
		gcall.Stepto(44129,32062,55);
		gcall.Stepto(44227,32286,117);
		gcall.Stepto(44272,32530,198);
		gcall.Stepto(44303,32776,282);
		gcall.Stepto(44331,33023,386);
		gcall.Stepto(44359,33269,470);
		gcall.Stepto(44383,33516,504);
		gcall.Stepto(44408,33762,503);
		gcall.Stepto(44436,34009,489);
		gcall.NewSpend(1);
		gcall.Stepto(44393,33983,493);
		gcall.DeliverQuests(zid,taskid,L"독초거사");
		Sleep(2000);
		break;
	case 3:
		gcall.NewSpend(2.5);
		gcall.Stepto(44358,33762,506);
		gcall.Stepto(44352,33706,509);
		gcall.Stepto(44349,33653,511);
		gcall.Stepto(44334,33405,487);
		gcall.Stepto(44320,33158,440);
		gcall.Stepto(44306,32910,336);
		gcall.Stepto(44280,32664,239);
		gcall.Stepto(44237,32420,158);
		gcall.Stepto(44191,32176,83);
		gcall.Stepto(44057,31971,33);
		gcall.Stepto(43882,31790,-9);
		gcall.Stepto(43662,31738,-36);
		gcall.Stepto(43414,31746,-5);
		gcall.Stepto(43166,31744,68);
		gcall.Stepto(42914,31743,106);
		gcall.Stepto(42752,31742,89);
		gcall.Stepto(42595,31741,52);
		gcall.Stepto(42341,31739,-10);
		gcall.Stepto(42161,31738,-31);
		gcall.Stepto(42039,31647,-24);
		gcall.Stepto(41840,31498,16);
		gcall.Stepto(41651,31357,56);
		gcall.Stepto(41638,31291,68);
		gcall.Stepto(41593,31047,135);
		gcall.Stepto(41550,30799,222);
		gcall.Stepto(41511,30554,311);
		gcall.Stepto(41497,30470,343);
		gcall.NewSpend(1);
		Sleep(6000);
		gcall.Stepto(41492,30392,374);
		gcall.WaitPlans();
		gcall.Stepto(41483,30283,416);
		gcall.Stepto(41483,30283,417);
		gcall.Stepto(41540,30103,471);
		gcall.Stepto(41532,29902,504);
		gcall.Stepto(41493,29657,537);
		gcall.Stepto(41438,29415,574);
		gcall.Stepto(41378,29174,583);
		gcall.Stepto(41310,28934,570);
		gcall.Stepto(41306,28919,570);
		Sleep(1000);
		gcall.PickupSpecTypeTask(300,0x20,L"용맥동굴 용맥");
		Sleep(20000);
		gcall.NewSpend(2.5);
		gcall.Stepto(33264,26240,2143);
		gcall.Stepto(33035,26215,2143);
		gcall.Stepto(32779,26185,2133);
		gcall.Stepto(32532,26152,2111);
		gcall.Stepto(32305,26066,2076);
		gcall.Stepto(32108,25918,2026);
		gcall.Stepto(31932,25754,1990);
		gcall.Stepto(31751,25569,1978);
		gcall.Stepto(31581,25388,1980);
		gcall.Stepto(31451,25177,1978);
		gcall.Stepto(31399,24937,1976);
		gcall.Stepto(31441,24693,1960);
		gcall.Stepto(31543,24467,1955);
		gcall.Stepto(31652,24245,1940);
		gcall.Stepto(31761,24022,1939);
		gcall.Stepto(31837,23867,1938);
		gcall.Stepto(31952,23755,1938);
		gcall.Stepto(32129,23582,1946);
		gcall.Stepto(32306,23409,1925);
		gcall.Stepto(32484,23236,1897);
		gcall.Stepto(32681,23087,1890);
		gcall.Stepto(32897,22961,1889);
		gcall.Stepto(33111,22837,1875);
		gcall.Stepto(33312,22696,1850);
		gcall.Stepto(33455,22489,1808);
		gcall.Stepto(33576,22272,1753);
		gcall.Stepto(33697,22056,1691);
		gcall.Stepto(33753,21957,1668);
		gcall.Stepto(33895,22001,1622);
		gcall.Stepto(34129,22072,1529);
		gcall.Stepto(34372,22142,1383);
		gcall.Stepto(34605,22215,1309);
		gcall.Stepto(34616,22218,1307);
		gcall.Stepto(34749,22019,1190);
		gcall.Stepto(34887,21813,1087);
		gcall.Stepto(35010,21625,1011);
		gcall.Stepto(35015,21538,994);
		gcall.Stepto(35027,21337,949);
		gcall.Stepto(35072,21279,932);
		gcall.Stepto(35223,21082,820);
		gcall.Stepto(35376,20887,688);
		gcall.Stepto(35531,20692,575);
		gcall.Stepto(35685,20497,499);
		gcall.Stepto(35766,20395,482);
		gcall.Stepto(35820,20478,478);
		gcall.Stepto(35955,20686,454);
		gcall.Stepto(36089,20891,389);
		gcall.Stepto(36092,20896,387);
		gcall.Stepto(36015,21116,311);
		gcall.Stepto(35933,21350,234);
		gcall.Stepto(35851,21584,135);
		gcall.Stepto(35769,21818,66);
		gcall.Stepto(35687,22052,-29);
		gcall.Stepto(35663,22121,-57);
		gcall.Stepto(35596,22215,-108);
		gcall.Stepto(35454,22418,-216);
		gcall.Stepto(35311,22622,-299);
		gcall.Stepto(35217,22756,-344);
		gcall.Stepto(35171,22853,-383);
		gcall.Stepto(35063,23076,-489);
		gcall.Stepto(34955,23299,-587);
		gcall.Stepto(34937,23329,-601);
		gcall.Stepto(34760,23502,-661);
		gcall.Stepto(34580,23679,-716);
		gcall.Stepto(34403,23852,-743);
		gcall.Stepto(34225,24026,-774);
		gcall.Stepto(34153,24097,-779);
		gcall.Stepto(34155,24102,-781);
		gcall.Stepto(34260,24325,-831);
		gcall.Stepto(34366,24551,-876);
		gcall.Stepto(34465,24762,-913);
		gcall.Stepto(34465,24763,-914);
		gcall.Stepto(34493,24757,-920);
		gcall.Stepto(34740,24706,-981);
		gcall.Stepto(34983,24654,-1049);
		gcall.Stepto(35224,24602,-1113);
		gcall.Stepto(35349,24572,-1143);
		gcall.Stepto(35593,24519,-1198);
		gcall.Stepto(35835,24467,-1254);
		gcall.Stepto(36077,24415,-1303);
		gcall.Stepto(36324,24362,-1361);
		gcall.Stepto(36566,24310,-1435);
		gcall.Stepto(36808,24258,-1519);
		gcall.Stepto(37051,24206,-1590);
		gcall.Stepto(37294,24153,-1648);
		gcall.Stepto(37536,24101,-1714);
		gcall.Stepto(37783,24048,-1731);
		gcall.Stepto(38025,23996,-1735);
		gcall.Stepto(38267,23944,-1732);
		gcall.Stepto(38371,23922,-1725);
		gcall.Stepto(38572,23996,-1740);
		gcall.Stepto(38801,24099,-1730);
		gcall.Stepto(39027,24201,-1733);
		gcall.Stepto(39252,24303,-1741);
		gcall.Stepto(39444,24390,-1743);
		gcall.Stepto(39625,24472,-1745);
		gcall.Stepto(39803,24553,-1742);
		gcall.Stepto(39985,24635,-1742);
		gcall.Stepto(40169,24719,-1744);
		gcall.Stepto(40387,24818,-1768);
		gcall.Stepto(40592,24911,-1783);
		gcall.Stepto(40860,24942,-1785);
		gcall.Stepto(41108,24955,-1771);
		gcall.Stepto(41358,24968,-1753);
		gcall.Stepto(41608,24981,-1731);
		gcall.Stepto(41854,24994,-1721);
		gcall.Stepto(42107,25007,-1722);
		gcall.Stepto(42348,25020,-1730);
		gcall.Stepto(42596,25032,-1738);
		gcall.Stepto(42847,25045,-1744);
		gcall.Stepto(43094,25058,-1745);
		gcall.Stepto(43345,25071,-1764);
		gcall.Stepto(43593,25084,-1747);
		gcall.Stepto(43845,25097,-1737);
		gcall.Stepto(44042,25107,-1748);
		gcall.Stepto(44126,25168,-1727);
		gcall.Stepto(44329,25314,-1636);
		gcall.Stepto(44531,25459,-1550);
		gcall.Stepto(44581,25496,-1511);
		gcall.Stepto(44779,25475,-1455);
		gcall.Stepto(45022,25451,-1435);
		gcall.Stepto(45276,25425,-1435);
		gcall.Stepto(45525,25399,-1435);
		gcall.Stepto(45582,25393,-1435);
		gcall.NewSpend(1);
		Sleep(1000);
		gcall.DeliverQuests(zid,taskid,L"오국춘");
		Sleep(1000);
		gcall.Stepto(45328,25488,-1436);
		gcall.SortBag();
		Sleep(1000);
		gcall.SellItemByConfig(L"이호리");
		Sleep(1000);
		break;
	case 4:
		gcall.randXianlu(0);
		//gcall.NewSpend(2.5);
		gcall.Stepto(45509,25321,-1437);
		gcall.Stepto(44839,25526,-1425);
		gcall.Stepto(44416,25357,-1610);
		gcall.Stepto(44057,25114,-1747);
		gcall.Stepto(43866,24973,-1776);
		//gcall.NewSpend(1);
		Sleep(1000);
		gcall.PickupTask();
		Sleep(1000);
		gcall.Stepto(43537,24521,-1826);
		gcall.Stepto(43078,23873,-1714);
		gcall.Stepto(42799,23857,-1760);
		Sleep(1000);
		gcall.PickupTask();
		Sleep(1000);
		gcall.Stepto(42741,23162,-1688);
		Sleep(1000);
		gcall.PickupTask();
		Sleep(1000);
		gcall.Stepto(42316,23088,-1735);
		gcall.Stepto(42049,22827,-1667);
		Sleep(1000);
		gcall.PickupTask();
		Sleep(1000);
		gcall.Stepto(42653,23667,-1772);
		gcall.Stepto(43304,24540,-1838);
		
		break;
	case 5:
		gcall.NewSpend(2.5);
		gcall.Stepto(43409,24936,-1789,10,20,3000);
		gcall.Stepto(43713,25052,-1752,10,20,3000);
		gcall.Stepto(43992,25147,-1728);
		gcall.Stepto(44346,25355,-1611);
		gcall.Stepto(44582,25470,-1532);
		gcall.Stepto(44851,25486,-1448);
		gcall.Stepto(45006,25520,-1433);
		gcall.Stepto(45255,25376,-1435);
		gcall.Stepto(45487,25308,-1439);
		gcall.NewSpend(1);
		Sleep(1000);
		gcall.DeliverQuests(zid,taskid,L"오국춘");
		Sleep(1000);
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

void TaskScript::Task_496(int zid,int taskid)
{
	switch (taskid)
	{
	case 1:
		gcall.CityConvey(0x5);
		Sleep(1000);
		break;
	case 2:
		gcall.NewSpend(2.5);
		gcall.Stepto(9831,15821,87);
		gcall.Stepto(9590,15888,87);
		gcall.Stepto(9354,15958,88);
		gcall.Stepto(9174,16009,90);
		gcall.Stepto(9174,16009,90);
		gcall.Stepto(8972,16019,90);
		gcall.Stepto(8911,15755,91);
		gcall.NewSpend(1);
		Sleep(1000);
		gcall.DeliverQuests(zid,taskid,L"풍대혜");
		Sleep(1000);
		break;
	case 3:
		gcall.NewSpend(2.5);
		gcall.Stepto(8979,16030,90);
		gcall.Stepto(9182,16009,90);
		gcall.Stepto(9365,15954,87);
		gcall.Stepto(9697,15875,87);
		gcall.Stepto(9686,15342,87);
		gcall.Stepto(9699,14768,70);
		gcall.NewSpend(1);
		gcall.randXianlu(0);
		Sleep(1000);
		gcall.Stepto(9738,14263,-18);
		gcall.Stepto(9779,13869,-121);
		gcall.Stepto(9835,13428,-172);
		gcall.Stepto(9893,12949,-201);
		gcall.Stepto(9997,12624,-232);
		gcall.Stepto(10248,12608,-257);
		gcall.Stepto(10494,12218,-345);
		gcall.Stepto(10657,11795,-426);
		gcall.Stepto(10702,11323,-423);
		gcall.FindThenKill(0,400,modeNormal | modeAoe | modePickup | modeGoback);
		gcall.NewSpend(2.5);
		gcall.Stepto(11046,11564,-422);
		gcall.Stepto(11111,11531,-415);
		gcall.Stepto(11327,11417,-404);
		gcall.NewSpend(1);
		gcall.Stepto(11538,11285,-418);
		gcall.Stepto(11567,11267,-421);
		gcall.FindThenKill(0,400,modeNormal | modeAoe | modePickup | modeGoback);
		gcall.NewSpend(2.5);
		gcall.Stepto(11693,11163,-429);
		gcall.Stepto(11710,11147,-430);
		gcall.Stepto(11761,11073,-433);
		gcall.Stepto(11955,10929,-454);
		gcall.Stepto(12170,10803,-516);
		gcall.NewSpend(1);
		gcall.Stepto(12372,10657,-532);
		gcall.Stepto(12526,10542,-535);
		gcall.FindThenKill(0,400,modeNormal | modeAoe | modePickup | modeGoback);
		gcall.NewSpend(2.5);
		gcall.Stepto(12526,10542,-537);
		gcall.Stepto(12355,10550,-522);
		gcall.Stepto(12107,10524,-492);
		gcall.Stepto(11863,10493,-472);
		gcall.Stepto(11618,10463,-458);
		gcall.Stepto(11367,10431,-447);
		gcall.Stepto(11124,10401,-428);
		gcall.NewSpend(1);
		gcall.Stepto(10876,10385,-405);
		gcall.Stepto(10747,10381,-395);
		gcall.FindThenKill(0,400,modeNormal | modeAoe | modePickup | modeGoback);
		gcall.Stepto(10589,10433,-385);
		gcall.Stepto(10398,10491,-372);
		gcall.Stepto(10205,10520,-347);
		gcall.Stepto(10061,10527,-319);
		gcall.FindThenKill(0,400,modeNormal | modeAoe | modePickup | modeGoback);
		gcall.NewSpend(2.5);
		gcall.Stepto(10043,10621,-308);
		gcall.Stepto(9998,10864,-286);
		gcall.Stepto(9960,11108,-254);
		gcall.Stepto(9946,11357,-253);
		gcall.NewSpend(1);
		gcall.Stepto(9949,11607,-267);
		gcall.Stepto(9950,11808,-273);
		gcall.FindThenKill(0,400,modeNormal | modeAoe | modePickup | modeGoback);
		gcall.NewSpend(2.5);
		gcall.Stepto(9951,11843,-273);
		gcall.Stepto(9973,12091,-268);
		gcall.Stepto(9982,12331,-254);
		gcall.Stepto(9998,12587,-236);
		gcall.NewSpend(1);
		gcall.Stepto(10027,12834,-219);
		gcall.Stepto(10033,12880,-215);
		gcall.FindThenKill(0,400,modeNormal | modeAoe | modePickup | modeGoback);
		gcall.NewSpend(2.5);
		gcall.Stepto(10165,12855,-228);
		gcall.Stepto(10409,12802,-261);
		gcall.Stepto(10653,12749,-300);
		gcall.Stepto(10895,12695,-360);
		gcall.Stepto(11137,12642,-405);
		gcall.Stepto(11361,12593,-424);
		gcall.Stepto(11515,12559,-426);
		gcall.Stepto(11535,12608,-426);
		gcall.Stepto(11628,12782,-422);
		gcall.NewSpend(1);
		gcall.Stepto(11728,12954,-415);
		gcall.Stepto(11812,13099,-411);
		gcall.FindThenKill(0,400,modeNormal | modeAoe | modePickup | modeGoback);
		gcall.NewSpend(2.5);
		gcall.Stepto(11835,13192,-410);
		gcall.Stepto(11902,13378,-409);
		gcall.Stepto(11974,13564,-409);
		gcall.Stepto(12046,13750,-409);
		gcall.Stepto(12117,13933,-409);
		gcall.NewSpend(1);
		gcall.Stepto(12192,14127,-409);
		gcall.Stepto(12252,14283,-409);
		gcall.FindThenKill(0,400,modeNormal | modeAoe | modePickup | modeGoback);
		gcall.NewSpend(2.5);
		gcall.Stepto(12256,14293,-409);
		gcall.Stepto(12327,14478,-409);
		gcall.Stepto(12400,14666,-408);
		gcall.Stepto(12471,14850,-402);
		gcall.Stepto(12554,15041,-387);
		gcall.Stepto(12659,15266,-380);
		gcall.NewSpend(1);
		gcall.Stepto(12828,15445,-383);
		gcall.Stepto(12998,15576,-384);
		gcall.FindThenKill(0,600,modeNormal | modeAoe | modePickup | modeGoback);
		gcall.NewSpend(2.5);
		gcall.Stepto(12998,15581,-384);
		gcall.Stepto(13038,15826,-377);
		gcall.Stepto(13124,16050,-367);
		gcall.Stepto(13289,16238,-364);
		gcall.Stepto(13455,16420,-364);
		gcall.Stepto(13588,16631,-373);
		gcall.NewSpend(1);
		gcall.Stepto(13712,16843,-389);
		gcall.Stepto(13722,16860,-391);
		gcall.FindThenKill(0,600,modeNormal | modeAoe | modePickup | modeGoback);
		gcall.NewSpend(2.5);
		gcall.Stepto(13549,16807,-385);
		gcall.Stepto(13362,16750,-372);
		gcall.Stepto(13172,16692,-353);
		gcall.Stepto(12979,16637,-323);
		gcall.Stepto(12787,16593,-283);
		gcall.Stepto(12595,16549,-237);
		gcall.Stepto(12399,16514,-190);
		gcall.Stepto(12203,16484,-152);
		gcall.Stepto(12004,16454,-121);
		gcall.Stepto(11810,16424,-90);
		gcall.Stepto(11615,16399,-60);
		gcall.Stepto(11372,16380,-23);
		gcall.Stepto(11126,16361,21);
		gcall.Stepto(10879,16342,55);
		gcall.Stepto(10633,16305,74);
		gcall.Stepto(10402,16211,87);
		gcall.Stepto(10260,16013,87);
		gcall.Stepto(10148,15790,87);
		gcall.Stepto(10046,15565,87);
		gcall.Stepto(9949,15337,87);
		gcall.Stepto(9851,15109,87);
		gcall.Stepto(9761,14878,78);
		gcall.Stepto(9728,14635,54);
		gcall.Stepto(9776,14390,11);
		gcall.Stepto(9829,14147,-51);
		gcall.Stepto(9881,13907,-114);
		gcall.Stepto(9933,13663,-161);
		gcall.Stepto(9984,13419,-174);
		gcall.Stepto(10028,13214,-189);
		gcall.Stepto(10048,13039,-206);
		gcall.NewSpend(1);
		gcall.Stepto(10023,12791,-222);
		gcall.Stepto(10009,12675,-230);
		gcall.FindThenKill(0,400,modeNormal | modeAoe | modePickup | modeGoback);
		break;
	case 4:
		gcall.NewSpend(2.5);
		gcall.Stepto(12334,14985,-377);
		gcall.Stepto(12277,14779,-405);
		gcall.Stepto(12170,14367,-409);
		gcall.Stepto(12089,13940,-409);
		gcall.Stepto(11972,13535,-409);
		gcall.Stepto(11855,13305,-409);
		gcall.Stepto(11714,13103,-410);
		gcall.Stepto(11560,12908,-416);
		gcall.Stepto(11434,12698,-422);
		gcall.Stepto(11299,12626,-417);
		gcall.Stepto(10908,12496,-383);
		gcall.Stepto(10498,12585,-284);
		gcall.Stepto(10158,12718,-240);
		gcall.Stepto(10565,12049,-391);
		gcall.Stepto(10353,12386,-294);
		gcall.Stepto(10194,12832,-233);
		gcall.Stepto(10076,13242,-189);
		gcall.Stepto(9987,13603,-167);
		gcall.Stepto(9894,13957,-102);
		gcall.Stepto(9787,14332,-2);
		gcall.Stepto(9730,14647,56);
		gcall.Stepto(9713,15033,85);
		gcall.Stepto(9753,15392,87);
		gcall.Stepto(9826,15806,87);
		gcall.Stepto(9602,15884,87);
		gcall.Stepto(9327,15970,88);
		gcall.Stepto(9200,16003,90);
		gcall.Stepto(9200,16003,90);
		gcall.Stepto(9016,16036,90);
		gcall.Stepto(9016,16036,90);
		gcall.NewSpend(1);
		gcall.Stepto(8964,15931,90);
		gcall.Stepto(8895,15710,90);
		Sleep(1000);
		gcall.DeliverQuests(zid,taskid+1,L"풍대혜");
		Sleep(1000);
		break;
	case 5:
		gcall.NewSpend(2.5);
		gcall.Stepto(8965,16059,90);
		gcall.Stepto(9186,16014,90);
		gcall.Stepto(9553,15922,87);
		gcall.Stepto(9884,15843,87);
		gcall.Stepto(10079,16099,87);
		gcall.Stepto(10454,16328,85);
		gcall.Stepto(10937,16380,48);
		gcall.Stepto(11448,16387,-35);
		gcall.Stepto(11869,16426,-100);
		gcall.Stepto(12360,16529,-183);
		gcall.Stepto(12803,16705,-290);
		gcall.Stepto(13288,16947,-374);
		gcall.Stepto(13365,17353,-424);
		gcall.Stepto(13296,17792,-491);
		gcall.Stepto(13225,18218,-549);
		gcall.Stepto(13157,18644,-601);
		gcall.Stepto(13092,19076,-603);
		gcall.Stepto(13038,19493,-603);
		gcall.Stepto(12988,19880,-603);
		gcall.Stepto(12945,20198,-603);
		gcall.Stepto(12889,20559,-603);
		gcall.Stepto(12987,20834,-603);
		gcall.Stepto(13139,21234,-603);
		gcall.Stepto(13295,21571,-603);
		gcall.Stepto(13463,21927,-603);
		gcall.Stepto(13568,22230,-587);
		gcall.Stepto(13646,22570,-567);
		gcall.Stepto(13709,22880,-565);
		gcall.Stepto(13567,23096,-566);
		gcall.NewSpend(1);
		gcall.Stepto(13108,23394,-563);
		gcall.Stepto(13108,23394,-563);
		Sleep(2000);
		break;
	case 6:
		gcall.NewSpend(2.5);
		gcall.Stepto(12798,23456,-567);
		gcall.Stepto(12516,23511,-614);
		gcall.Stepto(12212,23611,-697);
		gcall.Stepto(11894,23817,-699);
		gcall.Stepto(11678,24060,-646);
		gcall.Stepto(11637,24392,-568);
		gcall.Stepto(11632,24806,-424);
		gcall.Stepto(11663,25148,-284);
		gcall.Stepto(11704,25457,-202);
		gcall.Stepto(11752,25872,-196);
		gcall.Stepto(11740,26113,-204);
		gcall.Stepto(11732,26302,-204);
		gcall.Stepto(11701,26548,-221);
		gcall.Stepto(11679,26795,-239);
		gcall.Stepto(11630,27036,-241);
		gcall.Stepto(11476,27228,-227);
		gcall.Stepto(11267,27361,-205);
		gcall.Stepto(11051,27482,-195);
		gcall.Stepto(10833,27601,-191);
		gcall.Stepto(10603,27692,-193);
		gcall.Stepto(10365,27760,-198);
		gcall.Stepto(10118,27810,-189);
		gcall.Stepto(9873,27851,-190);
		gcall.Stepto(9628,27888,-179);
		gcall.Stepto(9384,27930,-207);
		gcall.NewSpend(1);
		gcall.Stepto(9142,27985,-244);
		gcall.Stepto(8906,28060,-282);
		gcall.Stepto(8577,28387,-333);
		//过滤怪物(제자군,1);
		gcall.FindThenKill(0,1500,modeNormal | modeAoe | modeTask | modeGoback,6);
		//任务清怪1(1000,6,1);
		Sleep(2000);
		gcall.Stepto(8580,28393,-334);
		gcall.Stepto(8410,28508,-347);
		gcall.Stepto(8236,28625,-346);
		gcall.Stepto(8149,28695,-346);
		Sleep(1000);
		gcall.PickupTask();
		Sleep(1000);
		//过滤怪物(제자군,3);
		break;
	case 7:
		gcall.NewSpend(2.5);
		gcall.Stepto(8853,28231,-293,10,20,3000);
		gcall.Stepto(8856,28229,-293,10,20,3000);
		gcall.Stepto(9060,28096,-259);
		gcall.Stepto(9285,27992,-223);
		gcall.Stepto(9516,27919,-191);
		gcall.Stepto(9759,27867,-189);
		gcall.Stepto(10004,27828,-188);
		gcall.Stepto(10247,27783,-192);
		gcall.Stepto(10479,27695,-194);
		gcall.Stepto(10704,27592,-191);
		gcall.Stepto(10931,27492,-193);
		gcall.Stepto(11143,27364,-196);
		gcall.Stepto(11341,27214,-214);
		gcall.Stepto(11543,27071,-233);
		gcall.Stepto(11725,26898,-249);
		gcall.Stepto(11798,26664,-229);
		gcall.Stepto(11799,26416,-211);
		gcall.Stepto(11780,26169,-196);
		gcall.Stepto(11758,25922,-197);
		gcall.Stepto(11737,25675,-184);
		gcall.Stepto(11717,25439,-203);
		gcall.Stepto(11690,25178,-270);
		gcall.Stepto(11664,24931,-379);
		gcall.Stepto(11642,24732,-451);
		gcall.Stepto(11598,24300,-590);
		gcall.NewSpend(1);
		gcall.Stepto(11611,23954,-658);
		gcall.Stepto(11815,23834,-691);
		gcall.Stepto(12193,23615,-699);
		gcall.Stepto(12604,23476,-600);
		gcall.Stepto(13023,23362,-560);
		Sleep(6000);
		gcall.Stepto(13338,23251,-558);
		gcall.WaitPlans();
		gcall.Stepto(13470,23154,-563);
		gcall.Stepto(13594,22943,-565);
		gcall.NewSpend(2.5);
		gcall.Stepto(13604,22695,-566);
		gcall.Stepto(13590,22910,-564);
		gcall.Stepto(13591,22824,-564);
		gcall.Stepto(13599,22596,-564);
		gcall.Stepto(13591,22345,-569);
		gcall.Stepto(13571,22110,-597);
		gcall.Stepto(13527,21854,-603);
		gcall.Stepto(13483,21610,-603);
		gcall.Stepto(13440,21368,-603);
		gcall.Stepto(13396,21125,-603);
		gcall.Stepto(13352,20878,-603);
		gcall.Stepto(13309,20635,-603);
		gcall.Stepto(13265,20391,-603);
		gcall.Stepto(13234,20144,-603);
		gcall.Stepto(13220,19898,-603);
		gcall.Stepto(13211,19647,-603);
		gcall.Stepto(13203,19400,-603);
		gcall.Stepto(13196,19152,-603);
		gcall.Stepto(13191,18902,-603);
		gcall.Stepto(13191,18658,-602);
		gcall.Stepto(13191,18408,-572);
		gcall.Stepto(13194,18160,-542);
		gcall.Stepto(13201,17911,-516);
		gcall.Stepto(13209,17662,-470);
		gcall.Stepto(13217,17415,-416);
		gcall.Stepto(13222,17167,-378);
		gcall.Stepto(13213,16929,-364);
		gcall.Stepto(13146,16692,-349);
		gcall.Stepto(12931,16562,-310);
		gcall.Stepto(12693,16514,-256);
		gcall.Stepto(12440,16482,-195);
		gcall.Stepto(12195,16451,-150);
		gcall.Stepto(11948,16419,-112);
		gcall.Stepto(11701,16388,-75);
		gcall.Stepto(11454,16357,-36);
		gcall.Stepto(11211,16326,9);
		gcall.Stepto(10962,16294,50);
		gcall.Stepto(10734,16220,73);
		gcall.Stepto(10537,16077,85);
		gcall.Stepto(10384,15884,87);
		gcall.Stepto(10248,15682,87);
		gcall.Stepto(10106,15466,87);
		gcall.Stepto(9986,15256,87);
		gcall.Stepto(9921,15017,86);
		gcall.Stepto(9865,14773,73);
		gcall.Stepto(9816,14523,38);
		gcall.Stepto(9786,14281,-14);
		gcall.Stepto(9766,14043,-78);
		gcall.Stepto(9743,13785,-139);
		gcall.Stepto(9722,13536,-170);
		gcall.Stepto(9696,13291,-172);
		gcall.Stepto(9687,13221,-174);
		gcall.Stepto(9529,13218,-172);
		gcall.Stepto(9277,13214,-169);
		gcall.Stepto(9029,13214,-162);
		gcall.Stepto(8780,13234,-162);
		gcall.Stepto(8534,13256,-162);
		gcall.NewSpend(1);
		Sleep(1000);
		gcall.FixWuqi();
		Sleep(1000);
		gcall.SortBag();
		Sleep(1000);
		gcall.SellItemByConfig(L"병기창");
		/*对准角度(8428,13254,-162);
		Sleep(1000);
		按键(F);
		Sleep(15000);
		卖(병기창);*/
		Sleep(1000);
		gcall.NewSpend(2.5);
		gcall.Stepto(8428,13254,-162);
		gcall.Stepto(8623,13233,-162);
		gcall.Stepto(8873,13209,-162);
		gcall.Stepto(9117,13186,-161);
		gcall.Stepto(9365,13162,-172);
		gcall.Stepto(9613,13138,-175);
		gcall.Stepto(9858,13115,-185);
		gcall.Stepto(10105,13091,-205);
		gcall.Stepto(10344,13023,-241);
		gcall.Stepto(10577,12944,-283);
		gcall.Stepto(10811,12863,-329);
		gcall.Stepto(11049,12782,-387);
		gcall.Stepto(11282,12703,-413);
		gcall.Stepto(11510,12763,-420);
		gcall.Stepto(11662,12959,-415);
		gcall.Stepto(11807,13159,-410);
		gcall.Stepto(11962,13356,-409);
		gcall.Stepto(12118,13540,-409);
		gcall.Stepto(12336,13666,-409);
		gcall.Stepto(12570,13745,-409);
		gcall.Stepto(12799,13814,-398);
		gcall.Stepto(13048,13859,-398);
		gcall.Stepto(13289,13926,-398);
		gcall.Stepto(13481,14077,-398);
		gcall.Stepto(13526,14317,-398);
		gcall.Stepto(13545,14453,-398);
		gcall.NewSpend(1);
		Sleep(1000);
		gcall.DeliverQuests(zid,taskid+1,L"풍대혜");
		Sleep(1000);
		break;
	case 8:
		break;
	case 9:
		break;

	}
}


void TaskScript::Task_315(int zid,int taskid)
{
	switch (taskid)
	{
	case 1:
		gcall.WearEquipment(L"홍문귀걸이 1단계",EQUITMENT_POS::ERHUAN);
		Sleep(1000);
		IsGoonHecheng(EQUITMENT_POS::ERHUAN);
		Sleep(1000);
		gcall.NewSpend(2.5);
		gcall.Stepto(13535,14426,-398);
		gcall.Stepto(13535,14414,-398);
		gcall.Stepto(13510,14166,-398);
		gcall.Stepto(13387,13953,-398);
		gcall.Stepto(13201,13818,-398);
		gcall.Stepto(12950,13809,-398);
		gcall.Stepto(12743,13815,-401);
		gcall.Stepto(12530,13826,-409);
		gcall.Stepto(12472,13784,-409);
		gcall.Stepto(12302,13603,-409);
		gcall.Stepto(12143,13415,-409);
		gcall.Stepto(11989,13231,-409);
		gcall.Stepto(11826,13037,-411);
		gcall.Stepto(11666,12844,-420);
		gcall.Stepto(11509,12648,-425);
		gcall.Stepto(11393,12503,-426);
		gcall.Stepto(11153,12150,-434);
		gcall.Stepto(10953,11768,-435);
		gcall.Stepto(10782,11372,-430);
		gcall.Stepto(10561,10993,-416);
		gcall.Stepto(10305,10643,-370);
		gcall.Stepto(10033,10305,-303);
		gcall.Stepto(9751,9975,-273);
		gcall.Stepto(9467,9647,-233);
		gcall.Stepto(9169,9325,-200);
		gcall.Stepto(8869,9018,-177);
		gcall.Stepto(8557,8706,-180);
		gcall.Stepto(8267,8417,-148);
		gcall.Stepto(8092,8242,-88);
		gcall.Stepto(7919,8058,-123);
		gcall.Stepto(7785,7851,-131);
		gcall.Stepto(7739,7609,-128);
		gcall.Stepto(7762,7363,-104);
		gcall.Stepto(7809,7121,-79);
		gcall.Stepto(7867,6881,-57);
		gcall.Stepto(7939,6658,-32);
		gcall.Stepto(8154,6286,9);
		gcall.Stepto(8410,5932,63);
		gcall.Stepto(8765,5694,116);
		gcall.Stepto(9072,5640,124);
		gcall.Stepto(9320,5641,124);
		gcall.Stepto(9490,5641,122);
		gcall.Stepto(9731,5641,117);
		gcall.Stepto(9950,5642,102);
		gcall.Stepto(10384,5654,94);
		gcall.Stepto(10755,5672,93);
		gcall.Stepto(11016,5694,115);
		gcall.Stepto(11263,5677,128);
		gcall.Stepto(11507,5636,156);
		gcall.Stepto(11752,5586,196);
		gcall.Stepto(11995,5535,238);
		gcall.Stepto(12238,5484,292);
		gcall.Stepto(12480,5434,350);
		gcall.Stepto(12726,5443,403);
		gcall.Stepto(12913,5493,440);
		gcall.Stepto(13330,5615,503);
		gcall.Stepto(13753,5741,558);
		gcall.Stepto(14169,5865,622);
		gcall.Stepto(14571,6026,654);
		gcall.Stepto(14860,6156,669);
		gcall.Stepto(15088,6251,683);
		gcall.Stepto(15334,6241,716);
		gcall.Stepto(15562,6147,763);
		gcall.Stepto(15784,6028,810);
		gcall.Stepto(15998,5903,849);
		gcall.Stepto(16168,5799,893);
		gcall.Stepto(16517,5584,985);
		gcall.Stepto(16886,5356,1010);
		gcall.Stepto(16996,5288,1014);
		gcall.Stepto(17147,5195,1019);
		gcall.Stepto(17501,4976,1024);
		gcall.Stepto(17872,4752,1039);
		gcall.Stepto(18043,4627,1045);
		gcall.Stepto(18212,4447,1043);
		gcall.Stepto(18238,4207,1065);
		gcall.Stepto(18203,3961,1079);
		gcall.Stepto(18152,3719,1097);
		gcall.Stepto(18146,3469,1111);
		gcall.Stepto(18252,3246,1122);
		gcall.Stepto(18392,3043,1136);
		gcall.Stepto(18563,2863,1127);
		gcall.Stepto(18714,2670,1134);
		gcall.Stepto(18809,2500,1145);
		gcall.Stepto(19016,2377,1162);
		gcall.Stepto(19265,2342,1181);
		gcall.Stepto(19513,2341,1203);
		gcall.Stepto(19753,2392,1229);
		gcall.Stepto(19988,2480,1250);
		gcall.Stepto(20208,2579,1269);
		gcall.Stepto(20436,2695,1280);
		gcall.Stepto(20659,2802,1313);
		gcall.Stepto(20906,2800,1308);
		gcall.Stepto(21140,2710,1298);
		gcall.Stepto(21365,2611,1309);
		gcall.Stepto(21551,2529,1314);
		gcall.Stepto(21813,2401,1319);
		gcall.NewSpend(1);
		gcall.Stepto(22033,2279,1327);
		gcall.Stepto(22247,2153,1332);
		gcall.Stepto(22459,2024,1326);
		gcall.Stepto(22670,1895,1344);
		gcall.Stepto(22882,1762,1326);
		gcall.Stepto(22928,1729,1323);
		gcall.Stepto(22960,1706,1323);
		Sleep(2000);
		gcall.PickupSpecTypeTask(300,0x20,L"녹명촌 용맥");
		Sleep(8000);
		gcall.WaitPlans();
		gcall.Stepto(29524,-2512,1042);
		gcall.Stepto(29563,-2558,1042);
		gcall.Stepto(29708,-2760,1042);
		gcall.Stepto(29837,-2943,1042);
		gcall.NewSpend(2.5);
		gcall.Stepto(30029,-3214,1042);
		gcall.Stepto(30287,-3563,1042);
		gcall.Stepto(30483,-3946,1062);
		gcall.Stepto(30516,-4377,1042);
		gcall.Stepto(30495,-4811,989);
		gcall.Stepto(30496,-5245,915);
		gcall.Stepto(30533,-5677,849);
		gcall.Stepto(30590,-6103,807);
		gcall.Stepto(30670,-6537,776);
		gcall.Stepto(30785,-6956,735);
		gcall.Stepto(30920,-7349,690);
		gcall.Stepto(31134,-7746,671);
		gcall.Stepto(31314,-7974,658);
		gcall.Stepto(31496,-8142,638);
		gcall.Stepto(31604,-8230,625);
		gcall.Stepto(31800,-8383,598);
		gcall.Stepto(31993,-8537,571);
		gcall.Stepto(32207,-8660,557);
		gcall.Stepto(32454,-8706,551);
		gcall.Stepto(32700,-8719,547);
		gcall.Stepto(32948,-8706,544);
		gcall.Stepto(33196,-8688,539);
		gcall.Stepto(33446,-8669,528);
		gcall.Stepto(33640,-8602,522);
		gcall.Stepto(34011,-8384,517);
		gcall.Stepto(34289,-8057,516);
		gcall.Stepto(34534,-7697,500);
		gcall.Stepto(34803,-7359,437);
		gcall.Stepto(35195,-7179,375);
		gcall.Stepto(35504,-7130,327);
		gcall.Stepto(35754,-7141,295);
		gcall.Stepto(36000,-7179,281);
		gcall.Stepto(36243,-7232,271);
		gcall.Stepto(36484,-7290,266);
		gcall.Stepto(36620,-7328,264);
		gcall.Stepto(36985,-7384,258);
		gcall.Stepto(37423,-7425,254);
		gcall.Stepto(37835,-7455,243);
		gcall.Stepto(38081,-7472,234);
		gcall.Stepto(38331,-7478,223);
		gcall.Stepto(38578,-7466,214);
		gcall.Stepto(38826,-7453,209);
		gcall.Stepto(39076,-7440,208);
		gcall.Stepto(39321,-7428,209);
		gcall.Stepto(39566,-7460,210);
		gcall.Stepto(39813,-7530,216);
		gcall.Stepto(40223,-7652,226);
		gcall.Stepto(40642,-7778,233);
		gcall.Stepto(41051,-7924,235);
		gcall.Stepto(41344,-8059,225);
		gcall.Stepto(41571,-8164,220);
		gcall.Stepto(41795,-8268,214);
		gcall.Stepto(42021,-8373,191);
		gcall.Stepto(42247,-8473,165);
		gcall.Stepto(42482,-8564,150);
		gcall.Stepto(42703,-8650,133);
		gcall.Stepto(42886,-8721,118);
		gcall.Stepto(43287,-8877,80);
		gcall.Stepto(43693,-9035,35);
		gcall.Stepto(44093,-9219,-20);
		gcall.Stepto(44344,-9392,-53);
		gcall.Stepto(44451,-9614,-73);
		gcall.Stepto(44525,-9597,-73);
		gcall.Stepto(44774,-9586,-77);
		gcall.Stepto(45023,-9595,-77);
		gcall.Stepto(45272,-9608,-83);
		gcall.Stepto(45518,-9620,-92);
		gcall.Stepto(45824,-9636,-106);
		gcall.Stepto(46259,-9654,-113);
		gcall.Stepto(46692,-9661,-106);
		gcall.Stepto(47083,-9614,-101);
		gcall.Stepto(47326,-9565,-106);
		gcall.Stepto(47564,-9497,-117);
		gcall.Stepto(47796,-9400,-131);
		gcall.Stepto(48010,-9305,-134);
		gcall.Stepto(48262,-9148,-123);
		gcall.Stepto(48580,-8848,-84);
		gcall.Stepto(48817,-8588,-33);
		gcall.Stepto(48988,-8403,16);
		gcall.Stepto(49157,-8223,90);
		gcall.Stepto(49287,-8015,173);
		gcall.Stepto(49422,-7979,202);
		gcall.Stepto(49669,-8014,232);
		gcall.Stepto(49909,-8057,230);
		gcall.Stepto(49912,-8058,230);
		gcall.Stepto(49932,-8062,228);
		gcall.Stepto(49948,-8065,226);
		gcall.NewSpend(1);
		Sleep(1000);
		gcall.DeliverQuests(zid,taskid,L"부용");
		Sleep(2000);
		break;
	case 2:
		gcall.NewSpend(2.5);
		gcall.Stepto(49952,-8274,231);
		gcall.Stepto(50080,-8485,186);
		gcall.Stepto(50201,-8670,71);
		gcall.Stepto(50328,-8781,-51);
		gcall.Stepto(50559,-8850,-133);
		gcall.Stepto(50793,-8771,-187);
		gcall.Stepto(51020,-8669,-241);
		gcall.Stepto(51218,-8524,-287);
		gcall.Stepto(51378,-8334,-333);
		gcall.Stepto(51514,-8123,-389);
		gcall.Stepto(51667,-7928,-453);
		gcall.Stepto(51736,-7692,-527);
		gcall.Stepto(51764,-7449,-596);
		gcall.Stepto(51793,-7202,-637);
		gcall.Stepto(51807,-6952,-679);
		gcall.Stepto(51762,-6710,-715);
		gcall.Stepto(51742,-6465,-737);
		gcall.Stepto(51685,-6229,-747);
		gcall.Stepto(51605,-6129,-746);
		gcall.Stepto(51489,-6239,-714);
		gcall.Stepto(51306,-6406,-651);
		gcall.NewSpend(1);
		gcall.Stepto(51122,-6573,-618);
		gcall.Stepto(50934,-6734,-629);
		gcall.Stepto(50910,-6754,-629);
		gcall.Stepto(50828,-6824,-631);
		Sleep(2000);
		gcall.Stepto(50734,-6902,-634);
		gcall.WaitPlans();
		gcall.Stepto(50697,-6933,-646);
		gcall.Stepto(50648,-6970,-656);
		gcall.NewSpend(2.5);
		gcall.Stepto(50449,-7114,-752);
		gcall.Stepto(50247,-7261,-887);
		gcall.Stepto(50046,-7410,-999);
		gcall.Stepto(49848,-7559,-1145);
		gcall.Stepto(49647,-7699,-1190);
		gcall.Stepto(49435,-7837,-1272);
		gcall.Stepto(49227,-7971,-1280);
		gcall.Stepto(48999,-8056,-1284);
		gcall.Stepto(48926,-8057,-1294);
		gcall.Stepto(48923,-8038,-1294);
		gcall.Stepto(48790,-7837,-1304);
		gcall.Stepto(48568,-7732,-1294);
		gcall.Stepto(48323,-7739,-1329);
		gcall.Stepto(48114,-7872,-1397);
		gcall.Stepto(47973,-8076,-1517);
		gcall.Stepto(47872,-8296,-1590);
		gcall.Stepto(47824,-8524,-1649);
		gcall.Stepto(47917,-8752,-1717);
		gcall.Stepto(48072,-8947,-1793);
		gcall.Stepto(48293,-9056,-1847);
		gcall.Stepto(48532,-9006,-1888);
		gcall.Stepto(48709,-8834,-1976);
		gcall.Stepto(48812,-8610,-2078);
		gcall.Stepto(48836,-8366,-2187);
		gcall.Stepto(48755,-8164,-2243);
		gcall.Stepto(48565,-8167,-2259);
		gcall.Stepto(48383,-8158,-2259);
		gcall.Stepto(48195,-8027,-2258);
		gcall.Stepto(48073,-7813,-2259);
		gcall.Stepto(47947,-7595,-2247);
		gcall.Stepto(47818,-7383,-2250);
		gcall.Stepto(47687,-7173,-2232);
		gcall.Stepto(47557,-6961,-2226);
		gcall.Stepto(47440,-6744,-2227);
		gcall.Stepto(47337,-6515,-2224);
		gcall.NewSpend(1);
		gcall.Stepto(47348,-6291,-2217);
		gcall.Stepto(47348,-6290,-2217);
		Sleep(1000);
		gcall.DeliverQuests(zid,taskid,L"고봉");
		Sleep(1000);
		break;
	case 3:
		gcall.Stepto(47338,-6392,-2219);
		gcall.Stepto(47311,-6520,-2224);
		gcall.Stepto(47278,-6588,-2227);
		gcall.Stepto(47054,-6595,-2217);
		gcall.Stepto(46820,-6521,-2204);
		gcall.Stepto(46578,-6471,-2205);
		gcall.Stepto(46400,-6464,-2204);
		gcall.FindThenKill(0,600,modeNormal | modeAoe | modeTask | modeGoback , taskid);
		Sleep(1000);
		break;
	case 4:
		gcall.Stepto(46230,-6397,-2201);
		gcall.Stepto(46152,-6421,-2202);
		Sleep(1000);
		gcall.PickupSpecTypeTask(200,0x20,L"흑룡채 감옥문");
		Sleep(1000);
		break;
	case 5:
		gcall.NewSpend(2.5);
		gcall.Stepto(50621,-7035,-659);
		gcall.Stepto(50603,-7044,-660);
		gcall.Stepto(50384,-7159,-795);
		gcall.Stepto(50172,-7289,-914);
		gcall.Stepto(49969,-7432,-1043);
		gcall.Stepto(49767,-7575,-1144);
		gcall.Stepto(49563,-7716,-1216);
		gcall.Stepto(49358,-7856,-1281);
		gcall.Stepto(49134,-7961,-1278);
		gcall.Stepto(48894,-7944,-1295);
		gcall.Stepto(48696,-7796,-1304);
		gcall.Stepto(48472,-7691,-1307);
		gcall.Stepto(48232,-7686,-1330);
		gcall.Stepto(48063,-7865,-1409);
		gcall.Stepto(47960,-8091,-1526);
		gcall.Stepto(47867,-8321,-1597);
		gcall.Stepto(47816,-8563,-1662);
		gcall.Stepto(47845,-8804,-1711);
		gcall.Stepto(48022,-8982,-1785);
		gcall.Stepto(48254,-9068,-1839);
		gcall.Stepto(48496,-9035,-1877);
		gcall.Stepto(48700,-8895,-1949);
		gcall.Stepto(48826,-8685,-2030);
		gcall.Stepto(48828,-8439,-2157);
		gcall.Stepto(48714,-8227,-2247);
		gcall.Stepto(48474,-8193,-2259);
		gcall.Stepto(48270,-8138,-2259);
		gcall.Stepto(48255,-8114,-2259);
		gcall.Stepto(48119,-7906,-2261);
		gcall.Stepto(47978,-7702,-2255);
		gcall.Stepto(47838,-7498,-2249);
		gcall.Stepto(47698,-7293,-2239);
		gcall.Stepto(47557,-7088,-2227);
		gcall.Stepto(47414,-6883,-2226);
		gcall.Stepto(47248,-6702,-2234);
		gcall.Stepto(47035,-6573,-2213);
		gcall.Stepto(46807,-6479,-2205);
		gcall.Stepto(46579,-6389,-2206);
		gcall.Stepto(46364,-6305,-2193);
		gcall.Stepto(46312,-6332,-2195);
		gcall.Stepto(46139,-6413,-2200);
		gcall.Stepto(46137,-6413,-2200);
		gcall.NewSpend(1);
		gcall.Stepto(46061,-6449,-2201);
		Sleep(1000);
		gcall.DeliverQuests(zid,taskid,L"도단하");
		Sleep(1000);
		break;
	case 6:
		gcall.Stepto(46143,-6436,-2202);
		gcall.Stepto(46146,-6433,-2202);
		gcall.Stepto(46328,-6274,-2188);
		gcall.Stepto(46379,-6229,-2185);
		gcall.Stepto(46314,-6158,-2176);
		gcall.Stepto(46203,-6040,-2151);
		gcall.Stepto(46096,-5924,-2129);
		gcall.Stepto(45992,-5808,-2107);
		gcall.Stepto(45861,-5662,-2078);
		gcall.Stepto(45767,-5555,-2056);
		gcall.Stepto(45715,-5494,-2048);
		gcall.FindThenKill(0,600,modeNormal | modeAoe | modeGoback | modePickup);
		gcall.Stepto(45674,-5420,-2039);
		gcall.Stepto(45554,-5202,-2049);
		gcall.Stepto(45433,-4986,-2048);
		gcall.Stepto(45312,-4769,-2047);
		gcall.Stepto(45275,-4702,-2048);
		gcall.FindThenKill(0,500,modeNormal | modeAoe | modeGoback | modePickup);

		gcall.Stepto(45285,-4792,-2048);
		gcall.Stepto(45277,-4769,-2048);
		gcall.Stepto(45206,-4531,-2049);
		gcall.Stepto(45134,-4294,-2049);
		gcall.Stepto(45054,-4059,-2046);
		gcall.Stepto(44954,-3833,-2048);
		gcall.Stepto(44853,-3606,-2046);
		gcall.Stepto(44753,-3379,-2042);
		gcall.Stepto(44638,-3161,-2043);
		gcall.Stepto(44461,-2987,-2045);
		gcall.Stepto(44352,-2934,-2047);
		gcall.Stepto(44117,-2953,-2041);
		gcall.Stepto(43876,-3001,-2042);
		gcall.Stepto(43655,-3114,-2040);
		gcall.Stepto(43455,-3201,-2039);
		gcall.FindThenKill(0,500,modeNormal | modeAoe | modeGoback | modePickup);

		gcall.Stepto(43455,-3201,-2039);
		gcall.Stepto(43342,-3265,-2038);
		gcall.Stepto(43149,-3376,-2038);
		gcall.Stepto(42924,-3479,-2039);
		gcall.Stepto(42866,-3496,-2039);
		gcall.FindThenKill(0,500,modeNormal | modeAoe | modeGoback | modePickup);

		gcall.Stepto(42866,-3496,-2039);
		gcall.Stepto(42852,-3505,-2039);
		gcall.Stepto(42642,-3636,-2040);
		gcall.Stepto(42424,-3753,-2039);
		gcall.Stepto(42197,-3853,-2032);
		gcall.Stepto(41976,-3966,-2029);
		gcall.Stepto(41746,-4060,-2028);
		gcall.Stepto(41613,-4123,-2031);
		gcall.Stepto(41501,-4182,-2030);
		gcall.Stepto(41477,-4233,-2030);
		gcall.Stepto(41406,-4471,-2026);
		gcall.Stepto(41392,-4525,-2028);
		gcall.Stepto(41480,-4703,-2027);
		gcall.Stepto(41574,-4894,-2028);
		gcall.Stepto(41647,-5047,-2030);
		gcall.Stepto(41754,-5270,-2020);
		gcall.Stepto(41796,-5358,-2021);
		gcall.FindThenKill(0,500,modeNormal | modeAoe | modeGoback | modePickup);

		gcall.Stepto(41796,-5358,-2021);
		gcall.Stepto(41844,-5462,-2029);
		gcall.Stepto(41927,-5642,-2038);
		gcall.Stepto(42009,-5823,-1999);
		gcall.Stepto(42091,-6003,-1999);
		gcall.Stepto(42176,-6183,-2062);
		gcall.Stepto(42263,-6361,-2064);
		gcall.Stepto(42346,-6541,-2064);
		gcall.Stepto(42392,-6653,-2064);
		gcall.FindThenKill(0,500,modeNormal | modeAoe | modeGoback | modePickup);

		gcall.Stepto(L"도단하");
		gcall.FindThenKill(0,300,modeNormal | modeAoe | modeGoback | modePickup);
		Sleep(2000);
		gcall.Stepto(L"도단하");
		gcall.FindThenKill(0,300,modeNormal | modeAoe | modeGoback | modePickup);
		break;
	case 7:
		gcall.NewSpend(2.5);
		gcall.Stepto(50232,-7312,-909);
		gcall.Stepto(50227,-7314,-911);
		gcall.Stepto(50017,-7443,-1025);
		gcall.Stepto(49807,-7575,-1144);
		gcall.Stepto(49597,-7707,-1205);
		gcall.Stepto(49387,-7839,-1279);
		gcall.Stepto(49233,-7935,-1280);
		gcall.Stepto(49135,-7932,-1277);
		gcall.Stepto(48970,-7928,-1277);
		gcall.Stepto(48818,-7859,-1304);
		gcall.Stepto(48591,-7757,-1299);
		gcall.Stepto(48366,-7670,-1326);
		gcall.Stepto(48272,-7648,-1321);
		gcall.Stepto(48222,-7685,-1331);
		gcall.Stepto(48159,-7736,-1345);
		gcall.Stepto(48043,-7907,-1435);
		gcall.Stepto(47928,-8127,-1548);
		gcall.Stepto(47816,-8349,-1601);
		gcall.Stepto(47787,-8407,-1614);
		gcall.Stepto(47809,-8595,-1670);
		gcall.Stepto(47838,-8843,-1721);
		gcall.Stepto(47840,-8864,-1726);
		gcall.Stepto(47962,-8923,-1766);
		gcall.Stepto(48187,-9027,-1824);
		gcall.Stepto(48412,-9131,-1860);
		gcall.Stepto(48464,-9155,-1857);
		gcall.Stepto(48536,-9065,-1876);
		gcall.Stepto(48692,-8872,-1957);
		gcall.Stepto(48850,-8678,-2030);
		gcall.Stepto(48901,-8615,-2074);
		gcall.Stepto(48892,-8573,-2098);
		gcall.Stepto(48830,-8333,-2200);
		gcall.Stepto(48795,-8202,-2237);
		gcall.Stepto(48742,-8208,-2244);
		gcall.Stepto(48495,-8223,-2259);
		gcall.Stepto(48340,-8228,-2258);
		gcall.Stepto(48285,-8145,-2259);
		gcall.Stepto(48141,-7941,-2261);
		gcall.Stepto(47998,-7738,-2256);
		gcall.Stepto(47854,-7535,-2249);
		gcall.Stepto(47709,-7330,-2242);
		gcall.Stepto(47568,-7130,-2229);
		gcall.Stepto(47423,-6926,-2227);
		gcall.Stepto(47280,-6723,-2232);
		gcall.Stepto(47191,-6598,-2228);
		gcall.Stepto(47142,-6566,-2225);
		gcall.Stepto(46933,-6431,-2205);
		gcall.Stepto(46722,-6295,-2208);
		gcall.Stepto(46516,-6161,-2205);
		gcall.Stepto(46301,-6022,-2163);
		gcall.Stepto(46092,-5888,-2124);
		gcall.Stepto(45884,-5753,-2092);
		gcall.Stepto(45685,-5625,-2051);
		gcall.Stepto(45683,-5624,-2051);
		gcall.Stepto(45628,-5478,-2038);
		gcall.Stepto(45541,-5241,-2049);
		gcall.Stepto(45453,-5009,-2048);
		gcall.Stepto(45361,-4779,-2046);
		gcall.Stepto(45261,-4552,-2048);
		gcall.Stepto(45159,-4325,-2049);
		gcall.Stepto(45058,-4099,-2047);
		gcall.Stepto(44956,-3872,-2048);
		gcall.Stepto(44855,-3646,-2046);
		gcall.Stepto(44754,-3422,-2042);
		gcall.Stepto(44652,-3194,-2042);
		gcall.Stepto(44583,-3040,-2047);
		gcall.Stepto(44385,-3038,-2042);
		gcall.Stepto(44133,-3035,-2039);
		gcall.Stepto(43885,-3032,-2043);
		gcall.Stepto(43771,-3031,-2044);
		gcall.Stepto(43649,-3097,-2040);
		gcall.Stepto(43428,-3215,-2039);
		gcall.Stepto(43209,-3331,-2036);
		gcall.Stepto(42990,-3447,-2039);
		gcall.Stepto(42770,-3563,-2039);
		gcall.Stepto(42551,-3679,-2037);
		gcall.Stepto(42332,-3794,-2039);
		gcall.Stepto(42110,-3911,-2030);
		gcall.Stepto(41890,-4027,-2027);
		gcall.Stepto(41672,-4142,-2030);
		gcall.Stepto(41483,-4242,-2030);
		gcall.Stepto(41526,-4456,-2026);
		gcall.Stepto(41575,-4700,-2025);
		gcall.Stepto(41623,-4943,-2028);
		gcall.Stepto(41671,-5185,-2022);
		gcall.Stepto(41716,-5407,-2021);
		gcall.Stepto(41750,-5468,-2030);
		gcall.Stepto(41865,-5687,-2038);
		gcall.Stepto(41981,-5907,-1999);
		gcall.Stepto(42091,-6115,-2036);
		gcall.Stepto(42206,-6334,-2064);
		gcall.Stepto(42316,-6542,-2064);
		gcall.Stepto(42430,-6757,-2064);
		gcall.Stepto(42542,-6969,-2064);
		gcall.Stepto(42507,-7123,-2064);
		gcall.Stepto(42519,-7367,-2064);
		gcall.NewSpend(1);
		gcall.Stepto(42389,-6836,-2064);
		gcall.Stepto(42447,-7078,-2064);
		gcall.Stepto(42502,-7319,-2064);
		gcall.Stepto(42546,-7563,-2064);
		gcall.Stepto(42599,-7806,-2064);
		gcall.Stepto(42655,-8048,-2064);
		gcall.Stepto(42711,-8288,-2051);
		gcall.Stepto(42742,-8424,-2051);
		Sleep(1000);
		gcall.FindThenKill(0,300,modeNormal | modeAoe | modeGoback | modePickup);
		Sleep(2000);
		gcall.FindThenKill(0,300,modeNormal | modeAoe | modeGoback | modePickup);
		Sleep(2000);
		gcall.FindThenKill(0,300,modeNormal | modeAoe | modeGoback | modePickup);
		break;
	case 8:
		gcall.Stepto(L"도단하");
		Sleep(1000);
		gcall.DeliverQuests(zid,taskid,L"도단하");
		Sleep(1000);
		gcall.FenJieByConfig();
		Sleep(1000);
		gcall.SortBag();
		break;
	case 9:
		gcall.NewSpend(2.5);
		gcall.Stepto(42494,-7355,-2064,10,20,3000);
		gcall.Stepto(42432,-7178,-2064,10,20,3000);
		gcall.Stepto(42305,-6756,-2064,10,20,3000);
		gcall.Stepto(42181,-6348,-2064);
		gcall.Stepto(42027,-5935,-1999);
		gcall.Stepto(41851,-5538,-2029);
		gcall.Stepto(41676,-5141,-2024);
		gcall.Stepto(41557,-4726,-2026);
		gcall.Stepto(41604,-4297,-2028);
		gcall.Stepto(41861,-3961,-2027);
		gcall.Stepto(42249,-3769,-2028);
		gcall.Stepto(42651,-3605,-2040);
		gcall.Stepto(43055,-3447,-2039);
		gcall.Stepto(43407,-3308,-2038);
		gcall.Stepto(43638,-3217,-2040);
		gcall.Stepto(43866,-3121,-2039);
		gcall.Stepto(44093,-3020,-2039);
		gcall.Stepto(44327,-3056,-2041);
		gcall.Stepto(44524,-3217,-2040);
		gcall.Stepto(44643,-3409,-2037);
		gcall.Stepto(44825,-3699,-2044);
		gcall.Stepto(45045,-4072,-2046);
		gcall.Stepto(45237,-4462,-2048);
		gcall.Stepto(45368,-4763,-2046);
		gcall.Stepto(45462,-4993,-2047);
		gcall.Stepto(45558,-5221,-2049);
		gcall.Stepto(45699,-5424,-2042);
		gcall.Stepto(45873,-5601,-2071);
		gcall.Stepto(46041,-5784,-2107);
		gcall.Stepto(46200,-5973,-2143);
		gcall.Stepto(46389,-6133,-2187);
		gcall.Stepto(46544,-6252,-2208);
		gcall.Stepto(46852,-6491,-2205);
		gcall.Stepto(47202,-6761,-2231);
		gcall.Stepto(47521,-7053,-2226);
		gcall.Stepto(47769,-7408,-2249);
		gcall.Stepto(47950,-7651,-2247);
		gcall.Stepto(48124,-7802,-2260);
		gcall.Stepto(48190,-7917,-2260);
		gcall.Stepto(48315,-8100,-2258);
		gcall.Stepto(48547,-8184,-2259);
		gcall.Stepto(48781,-8266,-2230);
		gcall.Stepto(48897,-8443,-2157);
		gcall.Stepto(48955,-8658,-2044);
		gcall.Stepto(48844,-8736,-2005);
		gcall.Stepto(48671,-8915,-1938);
		gcall.Stepto(48477,-9069,-1872);
		gcall.Stepto(48289,-9103,-1848);
		gcall.Stepto(48062,-9013,-1798);
		gcall.Stepto(47866,-8870,-1734);
		gcall.Stepto(47835,-8624,-1680);
		gcall.Stepto(47863,-8379,-1611);
		gcall.Stepto(47936,-8138,-1550);
		gcall.Stepto(48044,-7915,-1438);
		gcall.Stepto(48093,-7843,-1395);
		gcall.Stepto(48048,-7784,-1390);
		gcall.Stepto(48102,-7856,-1397);
		gcall.Stepto(48250,-7754,-1339);
		gcall.Stepto(48239,-7643,-1320);
		gcall.Stepto(48485,-7709,-1307);
		gcall.Stepto(48708,-7809,-1304);
		gcall.Stepto(48914,-7938,-1290);
		gcall.Stepto(49165,-7910,-1277);
		gcall.Stepto(49400,-7839,-1280);
		gcall.Stepto(49610,-7707,-1202);
		gcall.Stepto(49821,-7576,-1144);
		gcall.Stepto(50029,-7442,-1019);
		gcall.Stepto(50231,-7298,-905);
		gcall.NewSpend(1);
		gcall.Stepto(50418,-7159,-779);
		gcall.Stepto(50419,-7158,-779);
		gcall.Stepto(50435,-7146,-768);
		gcall.Stepto(50632,-6996,-658);
		gcall.Stepto(50812,-6825,-632);
		Sleep(2000);
		gcall.Stepto(50843,-6795,-631);
		gcall.WaitPlans();
		gcall.Stepto(51052,-6624,-618);
		gcall.Stepto(51133,-6594,-621);
		gcall.NewSpend(2.5);
		gcall.Stepto(51206,-6587,-623);
		gcall.Stepto(51454,-6590,-654);
		gcall.Stepto(51697,-6627,-712);
		gcall.Stepto(51840,-6821,-710);
		gcall.Stepto(51845,-7004,-685);
		gcall.Stepto(51840,-7252,-644);
		gcall.Stepto(51788,-7496,-588);
		gcall.Stepto(51710,-7731,-515);
		gcall.Stepto(51616,-7962,-439);
		gcall.Stepto(51489,-8175,-375);
		gcall.Stepto(51340,-8374,-323);
		gcall.Stepto(51162,-8543,-278);
		gcall.Stepto(50940,-8659,-226);
		gcall.Stepto(50714,-8758,-165);
		gcall.Stepto(50566,-8782,-125);
		gcall.Stepto(50380,-8940,-105);
		gcall.Stepto(50188,-9096,-107);
		gcall.Stepto(49953,-9163,-102);
		gcall.Stepto(49727,-9234,-93);
		gcall.Stepto(49480,-9262,-85);
		gcall.Stepto(49306,-9115,-69);
		gcall.Stepto(49233,-8883,-36);
		gcall.Stepto(49259,-8670,16);
		gcall.Stepto(49288,-8474,80);
		gcall.Stepto(49356,-8284,148);
		gcall.Stepto(49410,-8096,188);
		gcall.Stepto(49546,-7980,220);
		gcall.Stepto(49775,-8023,236);
		gcall.Stepto(49960,-8062,225);
		gcall.NewSpend(1);
		Sleep(1000);
		gcall.DeliverQuests(zid,taskid,L"부용");
		Sleep(2000);
		break;

	}
}

void TaskScript::Task_316(int zid,int taskid)
{
	switch (taskid)
	{
	case 1:
		gcall.NewSpend(2.5);
		gcall.Stepto(49929,-8073,229);
		gcall.Stepto(49724,-8004,233);
		gcall.Stepto(49490,-8073,207);
		gcall.Stepto(49272,-8191,133);
		gcall.Stepto(49073,-8338,43);
		gcall.Stepto(48928,-8462,0);
		gcall.Stepto(48631,-8758,-74);
		gcall.Stepto(48322,-9059,-116);
		gcall.Stepto(47958,-9293,-136);
		gcall.Stepto(47545,-9421,-123);
		gcall.Stepto(47116,-9468,-113);
		gcall.Stepto(46709,-9490,-113);
		gcall.Stepto(46460,-9504,-112);
		gcall.Stepto(46215,-9525,-110);
		gcall.Stepto(45964,-9551,-106);
		gcall.Stepto(45720,-9579,-100);
		gcall.Stepto(45571,-9598,-94);
		gcall.Stepto(45323,-9639,-86);
		gcall.Stepto(45082,-9598,-78);
		gcall.Stepto(44860,-9706,-80);
		gcall.Stepto(44675,-9871,-83);
		gcall.Stepto(44586,-10084,-104);
		gcall.Stepto(44688,-10314,-122);
		gcall.Stepto(44794,-10539,-150);
		gcall.Stepto(44912,-10757,-187);
		gcall.Stepto(45046,-10965,-226);
		gcall.Stepto(45147,-11114,-248);
		gcall.Stepto(45303,-11344,-279);
		gcall.Stepto(45545,-11700,-361);
		gcall.Stepto(45771,-12076,-428);
		gcall.Stepto(45953,-12469,-491);
		gcall.Stepto(46088,-12878,-579);
		gcall.Stepto(46214,-13294,-703);
		gcall.Stepto(46339,-13717,-826);
		gcall.Stepto(46456,-14128,-932);
		gcall.Stepto(46524,-14377,-992);
		gcall.Stepto(46586,-14618,-1041);
		gcall.Stepto(46646,-14858,-1085);
		gcall.Stepto(46694,-15102,-1126);
		gcall.Stepto(46736,-15346,-1158);
		gcall.Stepto(46758,-15593,-1197);
		gcall.Stepto(46784,-15840,-1238);
		gcall.Stepto(46814,-16086,-1280);
		gcall.Stepto(46829,-16196,-1301);
		gcall.Stepto(46888,-16436,-1350);
		gcall.Stepto(46954,-16675,-1408);
		gcall.Stepto(46973,-16919,-1464);
		gcall.Stepto(47008,-17161,-1523);
		gcall.Stepto(47120,-17385,-1575);
		gcall.Stepto(47286,-17540,-1617);
		gcall.Stepto(47448,-17720,-1656);
		gcall.Stepto(47611,-17912,-1683);
		gcall.Stepto(47858,-17936,-1682);
		gcall.Stepto(48103,-17953,-1678);
		gcall.Stepto(48355,-17967,-1676);
		gcall.Stepto(48602,-17979,-1679);
		gcall.Stepto(48849,-17989,-1680);
		gcall.Stepto(49097,-17993,-1681);
		gcall.Stepto(49348,-17994,-1679);
		gcall.Stepto(49596,-17994,-1671);
		gcall.Stepto(49844,-17994,-1655);
		gcall.Stepto(50092,-17994,-1628);
		gcall.Stepto(50340,-17994,-1591);
		gcall.Stepto(50588,-17994,-1547);
		gcall.Stepto(50836,-17994,-1499);
		gcall.Stepto(51085,-17994,-1433);
		gcall.Stepto(51250,-17994,-1433);
		gcall.Stepto(51643,-17993,-1458);
		gcall.Stepto(52084,-17992,-1280);
		gcall.NewSpend(1);
		gcall.Stepto(52505,-17982,-1093);
		gcall.Stepto(52950,-17961,-895);
		gcall.Stepto(53384,-17957,-696);
		gcall.Stepto(53818,-17945,-619);
		Sleep(2000);
		gcall.Stepto(53971,-17939,-619);
		gcall.WaitPlans();
		gcall.Stepto(54170,-17930,-651);
		gcall.Stepto(54591,-17909,-631);
		gcall.Stepto(55021,-17880,-637);
		gcall.NewSpend(2.5);
		gcall.Stepto(55449,-17838,-416);
		gcall.Stepto(55873,-17752,-341);
		gcall.Stepto(56309,-17654,-343);
		gcall.Stepto(56722,-17520,-343);
		gcall.Stepto(57076,-17267,-325);
		gcall.Stepto(57329,-16920,-305);
		gcall.Stepto(57417,-16501,-304);
		gcall.Stepto(57256,-16101,-304);
		gcall.Stepto(56921,-15824,-333);
		gcall.Stepto(56545,-15652,-347);
		gcall.Stepto(56315,-15557,-342);
		gcall.Stepto(56088,-15456,-327);
		gcall.Stepto(56035,-15439,-324);
		gcall.Stepto(55807,-15283,-302);
		gcall.Stepto(55835,-15107,-294);
		gcall.Stepto(55883,-14872,-287);
		gcall.Stepto(55884,-14869,-287);
		gcall.NewSpend(1);
		Sleep(1000);
		gcall.DeliverQuests(zid,taskid,L"성진하");
		Sleep(1000);
		break;
	case 2:
		gcall.NewSpend(2.5);
		gcall.Stepto(55884,-14869,-287);
		gcall.Stepto(55883,-15030,-291);
		gcall.Stepto(55911,-15212,-302);
		gcall.Stepto(56009,-15433,-322);
		gcall.Stepto(56224,-15558,-339);
		gcall.Stepto(56453,-15653,-347);
		gcall.Stepto(56705,-15759,-342);
		gcall.Stepto(57113,-15888,-322);
		gcall.Stepto(57385,-16188,-297);
		gcall.Stepto(57407,-16622,-309);
		gcall.Stepto(57356,-17054,-302);
		gcall.Stepto(57128,-17412,-324);
		gcall.Stepto(56724,-17560,-342);
		gcall.Stepto(56634,-17506,-346);
		gcall.Stepto(56639,-17321,-339);
		gcall.Stepto(56441,-17180,-334);
		gcall.Stepto(56195,-17175,-351);
		gcall.Stepto(55949,-17193,-370);
		gcall.Stepto(55712,-17128,-452);
		gcall.Stepto(55462,-17109,-640);
		gcall.Stepto(55223,-17161,-681);
		gcall.Stepto(54986,-17239,-608);
		gcall.NewSpend(1);
		gcall.Stepto(54767,-17355,-602);
		gcall.Stepto(54637,-17424,-604);
		Sleep(1000);
		gcall.DeliverQuests(zid,taskid,L"동동");
		Sleep(1000);
		break;
	case 3:
		gcall.NewSpend(2.5);
		gcall.Stepto(54637,-17424,-604);
		gcall.Stepto(54563,-17578,-614);
		gcall.Stepto(54392,-17756,-637);
		gcall.Stepto(54174,-17869,-654);
		gcall.Stepto(53934,-17932,-619);
		gcall.Stepto(53717,-17962,-619);
		gcall.WaitPlans();
		gcall.Stepto(53571,-17969,-619);
		gcall.Stepto(53313,-17981,-730);
		gcall.Stepto(52876,-17989,-928);
		gcall.Stepto(52442,-17993,-1121);
		gcall.Stepto(52012,-17996,-1311);
		gcall.Stepto(51574,-17972,-1433);
		gcall.Stepto(51140,-17952,-1433);
		gcall.Stepto(50706,-17951,-1525);
		gcall.Stepto(50319,-18103,-1596);
		gcall.Stepto(49975,-18383,-1643);
		gcall.Stepto(49648,-18668,-1669);
		gcall.Stepto(49376,-19002,-1731);
		gcall.Stepto(49200,-19397,-1736);
		gcall.Stepto(49124,-19700,-1734);
		gcall.Stepto(49093,-19948,-1731);
		gcall.Stepto(49070,-20193,-1737);
		gcall.Stepto(49008,-20418,-1724);
		gcall.Stepto(48922,-20655,-1704);
		gcall.Stepto(48838,-20886,-1683);
		gcall.Stepto(48757,-21120,-1660);
		gcall.Stepto(48684,-21357,-1634);
		gcall.Stepto(48603,-21585,-1608);
		gcall.Stepto(48508,-21734,-1586);
		gcall.Stepto(48463,-21752,-1579);
		gcall.Stepto(48248,-21876,-1537);
		gcall.Stepto(48046,-22022,-1490);
		gcall.Stepto(47964,-22084,-1468);
		gcall.Stepto(47920,-22428,-1448);
		gcall.Stepto(47819,-23047,-1412);
		gcall.Stepto(47502,-23656,-1356);
		gcall.NewSpend(1);
		//过滤怪物(흑룡채 순찰조장 우마애,2);
		gcall.FindThenKill(0,600,modeNormal | modeAoe | modePickup | modeGoback);
		//过滤怪物(흑룡채 순찰조장 우마애,3);
		gcall.randXianlu(0);
		Sleep(1000);
		break;
	case 4:
		gcall.NewSpend(2.5);
		gcall.Stepto(47743,-23376,-1388);
		gcall.Stepto(47760,-23348,-1392);
		gcall.Stepto(47856,-23210,-1410);
		gcall.Stepto(48048,-22914,-1452);
		gcall.Stepto(48265,-22538,-1504);
		gcall.Stepto(48481,-22164,-1554);
		gcall.Stepto(48652,-21767,-1600);
		gcall.Stepto(48689,-21335,-1637);
		gcall.Stepto(48665,-20902,-1673);
		gcall.Stepto(48644,-20468,-1706);
		gcall.Stepto(48702,-20041,-1735);
		gcall.Stepto(48875,-19645,-1744);
		gcall.Stepto(49108,-19278,-1735);
		gcall.Stepto(49384,-18939,-1723);
		gcall.Stepto(49665,-18609,-1659);
		gcall.Stepto(49865,-18411,-1643);
		gcall.Stepto(50076,-18282,-1633);
		gcall.Stepto(50305,-18187,-1601);
		gcall.Stepto(50496,-18111,-1566);
		gcall.Stepto(50733,-18037,-1520);
		gcall.Stepto(50975,-17992,-1474);
		gcall.Stepto(51226,-17975,-1433);
		gcall.Stepto(51474,-17969,-1433);
		gcall.Stepto(51722,-17974,-1440);
		gcall.Stepto(51970,-17975,-1330);
		gcall.Stepto(52218,-17975,-1220);
		gcall.Stepto(52463,-17975,-1112);
		gcall.NewSpend(1);
		gcall.Stepto(52716,-17975,-999);
		gcall.Stepto(52964,-17974,-889);
		gcall.Stepto(53212,-17972,-779);
		gcall.Stepto(53460,-17959,-664);
		Sleep(2000);
		gcall.Stepto(53707,-17947,-619);
		gcall.WaitPlans();
		gcall.Stepto(53905,-17940,-619);
		gcall.Stepto(54029,-17935,-619);
		gcall.Stepto(54280,-17925,-650);
		gcall.Stepto(54499,-17832,-634);
		gcall.Stepto(54590,-17605,-615);
		gcall.Stepto(54600,-17476,-607);
		gcall.NewSpend(1);
		Sleep(1000);
		gcall.DeliverQuests(zid,taskid,L"동동");
		Sleep(1000);
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

void TaskScript::Task_493(int zid,int taskid)
{
	switch (taskid)
	{
	case 1:
		gcall.FenJieByConfig();
		Sleep(1000);
		gcall.SortBag();
		Sleep(1000);
		gcall.NewSpend(2.5);
		gcall.Stepto(54600,-17476,-607);
		gcall.Stepto(54575,-17519,-610);
		gcall.Stepto(54465,-17707,-630);
		gcall.Stepto(54142,-17862,-640);
		gcall.Stepto(53717,-17947,-619);
		gcall.Stepto(53597,-17952,-619);
		gcall.WaitPlans();
		gcall.Stepto(53445,-17958,-670);
		gcall.Stepto(53245,-17966,-765);
		gcall.Stepto(53069,-17973,-842);
		gcall.Stepto(52761,-17978,-979);
		gcall.Stepto(52327,-17984,-1172);
		gcall.Stepto(51893,-17988,-1364);
		gcall.Stepto(51459,-17975,-1433);
		gcall.Stepto(51028,-17953,-1455);
		gcall.Stepto(50591,-17932,-1546);
		gcall.Stepto(50158,-17911,-1620);
		gcall.Stepto(49724,-17889,-1667);
		gcall.Stepto(49289,-17874,-1682);
		gcall.Stepto(48857,-17918,-1683);
		gcall.Stepto(48438,-18027,-1678);
		gcall.Stepto(48044,-18201,-1701);
		gcall.Stepto(47754,-18349,-1728);
		gcall.Stepto(47538,-18471,-1746);
		gcall.Stepto(47355,-18637,-1763);
		gcall.Stepto(47185,-18815,-1775);
		gcall.Stepto(47002,-18980,-1777);
		gcall.Stepto(46774,-19085,-1773);
		gcall.Stepto(46542,-19170,-1771);
		gcall.Stepto(46390,-19226,-1772);
		gcall.Stepto(46180,-19263,-1775);
		gcall.Stepto(45980,-19238,-1778);
		gcall.Stepto(45741,-19212,-1787);
		gcall.Stepto(45591,-19199,-1796);
		gcall.Stepto(45442,-19189,-1811);
		gcall.Stepto(45205,-19232,-1840);
		gcall.Stepto(44973,-19179,-1863);
		gcall.Stepto(44739,-19165,-1896);
		gcall.Stepto(44505,-19180,-1939);
		gcall.Stepto(44284,-19258,-1989);
		gcall.Stepto(44038,-19354,-2049);
		gcall.Stepto(43802,-19346,-2102);
		gcall.Stepto(43574,-19368,-2161);
		gcall.Stepto(43332,-19395,-2224);
		gcall.Stepto(43124,-19486,-2285);
		gcall.Stepto(42878,-19518,-2347);
		gcall.Stepto(42643,-19588,-2417);
		gcall.Stepto(42405,-19654,-2486);
		gcall.Stepto(42167,-19703,-2545);
		gcall.Stepto(41923,-19682,-2589);
		gcall.Stepto(41672,-19655,-2622);
		gcall.Stepto(41428,-19628,-2636);
		gcall.Stepto(41417,-19627,-2636);
		gcall.Stepto(41313,-19416,-2600);
		gcall.Stepto(41205,-19252,-2566);
		gcall.Stepto(41185,-19253,-2563);
		gcall.Stepto(40980,-19151,-2514);
		gcall.Stepto(40769,-19022,-2446);
		gcall.Stepto(40700,-18806,-2403);
		gcall.Stepto(40742,-18585,-2393);
		gcall.Stepto(40833,-18254,-2364);
		gcall.Stepto(40948,-17834,-2297);
		gcall.Stepto(41040,-17417,-2217);
		gcall.Stepto(40902,-17008,-2153);
		gcall.Stepto(40662,-16640,-2089);
		gcall.Stepto(40397,-16296,-2033);
		gcall.Stepto(40072,-16008,-1989);
		gcall.Stepto(39858,-15889,-1960);
		gcall.Stepto(39639,-15772,-1931);
		gcall.Stepto(39419,-15654,-1910);
		gcall.Stepto(39348,-15616,-1905);
		gcall.Stepto(39173,-15708,-1906);
		gcall.Stepto(38965,-15839,-1900);
		gcall.Stepto(38843,-15904,-1899);
		gcall.Stepto(38657,-15992,-1895);
		gcall.Stepto(38539,-16206,-1895);
		gcall.Stepto(38478,-16345,-1896);
		gcall.Stepto(38331,-16306,-1891);
		gcall.Stepto(38091,-16388,-1894);
		gcall.NewSpend(1);
		
		gcall.Stepto(37916,-16209,-1871);
		gcall.Stepto(37783,-16074,-1798);
		//过滤怪物(도끼파 날강도,2);
		//过滤怪物(도끼파 사기꾼,2);
		//过滤怪物(우산 광대버섯,1);
		Sleep(1000);
		gcall.PickupTask();
		Sleep(1000);
		gcall.Stepto(37854,-16123,-1838);
		gcall.Stepto(38059,-16263,-1891);
		gcall.Stepto(38264,-16403,-1894);
		gcall.Stepto(38437,-16522,-1902);
		gcall.Stepto(38637,-16660,-1914);
		gcall.Stepto(38846,-16793,-1930);
		gcall.Stepto(39026,-16907,-1954);
		Sleep(1000);
		gcall.FindThenKill(0,500,modeNormal | modeAoe | modePickup);
		Sleep(2000);
		gcall.FindThenKill(0,500,modeNormal | modeAoe | modePickup);
		gcall.Stepto(38824,-16783,-1928);
		gcall.Stepto(39109,-16962,-1971);
		Sleep(1000);
		gcall.PickupTask();
		Sleep(1000);
		gcall.NewSpend(2.5);
		gcall.Stepto(38954,-16885,-1943);
		gcall.Stepto(38897,-16882,-1940);
		gcall.Stepto(38654,-16921,-1933);
		gcall.Stepto(38415,-16990,-1933);
		gcall.Stepto(38175,-17060,-1933);
		gcall.Stepto(37938,-17134,-1932);
		gcall.Stepto(37702,-17208,-1933);
		gcall.Stepto(37465,-17286,-1931);
		gcall.Stepto(37237,-17381,-1927);
		gcall.Stepto(37006,-17455,-1925);
		gcall.Stepto(36778,-17556,-1925);
		gcall.Stepto(36658,-17609,-1924);
		gcall.Stepto(36463,-17648,-1925);
		gcall.Stepto(36221,-17695,-1926);
		gcall.Stepto(36191,-17701,-1925);
		gcall.Stepto(36042,-17714,-1917);
		gcall.Stepto(35984,-17719,-1911);
		gcall.Stepto(35850,-17898,-1803);
		gcall.Stepto(35735,-18050,-1742);
		gcall.NewSpend(1);
		Sleep(1000);
		gcall.PickupTask();
		Sleep(1000);
		gcall.Stepto(35734,-17997,-1754);
		gcall.Stepto(35721,-17755,-1888);
		gcall.Stepto(35678,-17511,-1957);
		gcall.Stepto(35599,-17280,-1971);
		gcall.Stepto(35507,-17044,-1985);
		gcall.Stepto(35416,-16817,-1985);
		gcall.Stepto(35376,-16716,-1984);
		Sleep(1000);
		gcall.FindThenKill(0,300,modeNormal | modeAoe | modePickup);
		gcall.Stepto(35553,-16693,-1972);
		Sleep(1000);
		gcall.PickupTask();
		Sleep(1000);
		gcall.NewSpend(2.5);
		gcall.Stepto(35275,-16857,-1994);
		gcall.Stepto(35172,-16756,-1994);
		gcall.Stepto(35030,-16618,-2007);
		gcall.Stepto(34887,-16479,-2030);
		gcall.Stepto(34746,-16340,-2059);
		gcall.Stepto(34605,-16200,-2083);
		gcall.Stepto(34464,-16060,-2100);
		gcall.Stepto(34324,-15920,-2116);
		gcall.Stepto(34183,-15780,-2132);
		gcall.Stepto(34043,-15640,-2137);
		gcall.Stepto(33900,-15498,-2129);
		gcall.Stepto(33724,-15323,-2114);
		gcall.Stepto(33548,-15148,-2102);
		gcall.Stepto(33372,-14973,-2100);
		gcall.Stepto(33160,-14843,-2084);
		gcall.Stepto(33038,-14767,-2073);
		gcall.NewSpend(1);
		Sleep(1000);
		gcall.FindThenKill(0,300,modeNormal | modeAoe | modePickup);
		gcall.Stepto(33038,-14767,-2073);
		Sleep(1000);
		gcall.PickupTask();
		Sleep(1000);

		gcall.Stepto(32991,-14696,-2076);
		gcall.Stepto(33000,-14483,-2106);
		gcall.Stepto(33033,-14237,-2098);
		gcall.Stepto(33077,-13993,-2075);
		gcall.Stepto(33115,-13782,-2047);
		Sleep(1000);
		gcall.PickupTask();
		Sleep(1000);

		gcall.Stepto(33301,-13927,-2053);
		gcall.Stepto(33506,-14067,-2062);
		gcall.Stepto(33716,-14198,-2071);
		Sleep(1000);
		gcall.FindThenKill(0,300,modeNormal | modeAoe | modePickup);
		Sleep(1000);

		gcall.Stepto(33891,-14329,-2067);
		gcall.Stepto(34080,-14488,-2049);
		gcall.Stepto(34293,-14538,-1998);
		Sleep(1000);
		gcall.PickupTask();
		Sleep(1000);

		gcall.NewSpend(2.5);
		gcall.Stepto(34202,-14757,-2058,10,20,3000);
		gcall.Stepto(34088,-14977,-2093,10,20,3000);
		gcall.Stepto(33970,-15195,-2112,10,20,3000);
		gcall.Stepto(33866,-15420,-2123);
		gcall.Stepto(33771,-15652,-2126);
		gcall.Stepto(33781,-15896,-2123);
		gcall.Stepto(33883,-16122,-2125);
		gcall.Stepto(33997,-16342,-2121);
		gcall.Stepto(34126,-16554,-2121);
		gcall.Stepto(34257,-16765,-2092);
		gcall.Stepto(34383,-16967,-2072);
		gcall.Stepto(34515,-17177,-2046);
		gcall.Stepto(34680,-17346,-2018);
		gcall.Stepto(34920,-17410,-1999);
		gcall.Stepto(35159,-17474,-1982);
		gcall.Stepto(35399,-17537,-1970);
		gcall.Stepto(35642,-17585,-1956);
		gcall.Stepto(35849,-17623,-1935);
		gcall.Stepto(36094,-17659,-1927);
		gcall.Stepto(36341,-17651,-1927);
		gcall.Stepto(36582,-17590,-1926);
		gcall.Stepto(36821,-17526,-1925);
		gcall.Stepto(37061,-17462,-1925);
		gcall.Stepto(37300,-17398,-1928);
		gcall.Stepto(37540,-17334,-1931);
		gcall.Stepto(37736,-17192,-1933);
		gcall.Stepto(37908,-17013,-1929);
		gcall.Stepto(38041,-16856,-1921);
		gcall.Stepto(38009,-16912,-1924);
		gcall.NewSpend(1);
		gcall.randXianlu(0);
		Sleep(2000);
		break;
	case 2:
		gcall.NewSpend(2.5);
		gcall.Stepto(38166,-16162,-1887,10,20,3000);
		gcall.Stepto(38226,-16149,-1888,10,20,3000);
		gcall.Stepto(38414,-16084,-1890,10,20,3000);
		gcall.Stepto(38792,-15942,-1898);
		gcall.Stepto(39055,-15879,-1906);
		gcall.Stepto(39298,-15845,-1916);
		gcall.Stepto(39544,-15816,-1929);
		gcall.Stepto(39775,-15889,-1954);
		gcall.Stepto(39971,-16042,-1989);
		gcall.Stepto(40120,-16177,-2018);
		gcall.Stepto(40438,-16473,-2059);
		gcall.Stepto(40755,-16769,-2113);
		gcall.Stepto(41067,-17071,-2161);
		gcall.Stepto(41417,-17325,-2198);
		gcall.Stepto(41831,-17450,-2202);
		gcall.Stepto(42263,-17488,-2158);
		gcall.Stepto(42701,-17458,-2088);
		gcall.Stepto(43133,-17402,-1970);
		gcall.Stepto(43543,-17267,-1802);
		gcall.Stepto(43931,-17071,-1637);
		gcall.Stepto(44297,-16841,-1488);
		gcall.Stepto(44609,-16627,-1365);
		gcall.Stepto(44802,-16468,-1298);
		gcall.Stepto(44982,-16298,-1243);
		gcall.Stepto(45096,-16180,-1211);
		gcall.Stepto(45271,-15999,-1171);
		gcall.Stepto(45440,-15818,-1144);
		gcall.Stepto(45583,-15666,-1131);
		gcall.Stepto(45758,-15488,-1120);
		gcall.Stepto(45992,-15456,-1117);
		gcall.Stepto(46200,-15534,-1135);
		gcall.Stepto(46359,-15724,-1172);
		gcall.Stepto(46511,-15920,-1222);
		gcall.Stepto(46630,-16137,-1272);
		gcall.Stepto(46740,-16360,-1323);
		gcall.Stepto(46851,-16586,-1379);
		gcall.Stepto(46959,-16807,-1438);
		gcall.Stepto(47091,-17015,-1491);
		gcall.Stepto(47239,-17217,-1543);
		gcall.Stepto(47378,-17422,-1593);
		gcall.Stepto(47536,-17611,-1638);
		gcall.Stepto(47762,-17702,-1654);
		gcall.Stepto(47987,-17728,-1659);
		gcall.Stepto(48329,-17770,-1666);
		gcall.Stepto(48758,-17840,-1682);
		gcall.Stepto(49190,-17880,-1683);
		gcall.Stepto(49622,-17919,-1671);
		gcall.Stepto(50055,-17944,-1634);
		gcall.Stepto(50496,-17950,-1563);
		gcall.Stepto(50930,-17957,-1478);
		gcall.Stepto(51364,-17962,-1433);
		gcall.Stepto(51799,-17968,-1406);
		gcall.Stepto(52233,-17973,-1214);
		gcall.Stepto(52660,-17971,-1024);
		gcall.NewSpend(1);
		gcall.Stepto(52908,-17972,-914);
		gcall.Stepto(53156,-17967,-804);
		gcall.Stepto(53408,-17961,-691);
		gcall.Stepto(53656,-17962,-619);
		Sleep(2000);
		gcall.Stepto(53904,-17956,-619);
		gcall.WaitPlans();
		gcall.Stepto(54042,-17951,-619);
		gcall.Stepto(54282,-17902,-649);
		gcall.Stepto(54460,-17730,-632);
		gcall.Stepto(54559,-17506,-609);
		gcall.Stepto(54564,-17492,-608);
		gcall.NewSpend(1);
		Sleep(1000);
		gcall.DeliverQuests(zid,taskid,L"동동");
		Sleep(1000);
		break;
	case 3:
		gcall.NewSpend(2.5);
		gcall.Stepto(54623,-17466,-606);
		gcall.Stepto(54662,-17505,-608);
		gcall.Stepto(55035,-17711,-634);
		gcall.Stepto(55467,-17733,-397);
		gcall.Stepto(55898,-17679,-341);
		gcall.Stepto(56328,-17621,-352);
		gcall.Stepto(56734,-17464,-344);
		gcall.Stepto(57057,-17176,-326);
		gcall.Stepto(57314,-16827,-308);
		gcall.Stepto(57398,-16409,-299);
		gcall.Stepto(57183,-16042,-312);
		gcall.Stepto(56805,-15833,-337);
		gcall.Stepto(56403,-15670,-346);
		gcall.Stepto(56066,-15462,-327);
		gcall.Stepto(55983,-15231,-306);
		gcall.NewSpend(1);
		gcall.Stepto(55926,-14988,-290);
		gcall.Stepto(55910,-14917,-288);
		Sleep(1000);
		gcall.DeliverQuests(zid,taskid,L"성진하");
		Sleep(1000);
		break;
	case 4:
		gcall.NewSpend(2.5);
		gcall.Stepto(55908,-14917,-288);
		gcall.Stepto(55684,-15001,-289);
		gcall.Stepto(55455,-15096,-289);
		gcall.Stepto(55330,-15042,-273);
		gcall.Stepto(55149,-14898,-243);
		gcall.Stepto(55144,-14895,-243,30);
		gcall.Stepto(55063,-14819,-247,30);
		gcall.Stepto(55068,-14753,-247,30);
		gcall.Stepto(55074,-14565,-247);
		gcall.NewSpend(1);
		Sleep(1000);
		gcall.DeliverQuests(zid,taskid,L"도천풍");
		Sleep(1000);
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


void TaskScript::Task_317(int zid,int taskid)
{
	switch (taskid)
	{
	case 1:
		gcall.NewSpend(2.5);
		gcall.Stepto(55074,-14565,-247);
		gcall.Stepto(55116,-14762,-247);
		gcall.Stepto(55171,-14905,-243);
		gcall.Stepto(55220,-14991,-257);
		gcall.Stepto(55403,-15146,-289);
		gcall.Stepto(55592,-15240,-293);
		gcall.Stepto(55931,-15408,-317);
		gcall.Stepto(56322,-15605,-344);
		gcall.Stepto(56708,-15799,-340);
		gcall.Stepto(57028,-16080,-319);
		gcall.Stepto(57164,-16490,-305);
		gcall.Stepto(57079,-16912,-317);
		gcall.Stepto(56828,-17255,-333);
		gcall.Stepto(56444,-17477,-352);
		gcall.Stepto(56042,-17633,-341);
		gcall.Stepto(55625,-17740,-378);
		gcall.NewSpend(1);
		gcall.Stepto(55194,-17823,-556);
		gcall.Stepto(54761,-17867,-623);
		gcall.Stepto(54507,-17887,-636);
		gcall.Stepto(54259,-17914,-651);
		gcall.Stepto(54019,-17940,-619);
		Sleep(2000);
		gcall.Stepto(53718,-17972,-619);
		gcall.WaitPlans();
		gcall.Stepto(53647,-17979,-619);
		gcall.Stepto(53268,-18005,-754);
		gcall.Stepto(52838,-17978,-945);
		gcall.NewSpend(2.5);
		gcall.Stepto(52405,-17945,-1137);
		gcall.Stepto(51972,-17969,-1329);
		gcall.Stepto(51532,-17999,-1433);
		gcall.Stepto(51103,-18004,-1433);
		gcall.Stepto(50669,-17989,-1532);
		gcall.Stepto(50234,-17979,-1608);
		gcall.Stepto(49798,-17980,-1659);
		gcall.Stepto(49364,-17975,-1679);
		gcall.Stepto(48927,-17988,-1680);
		gcall.Stepto(48522,-18115,-1678);
		gcall.Stepto(48364,-18314,-1690);
		gcall.Stepto(48274,-18548,-1726);
		gcall.Stepto(48243,-18791,-1751);
		gcall.Stepto(48281,-19033,-1763);
		gcall.Stepto(48345,-19273,-1767);
		gcall.Stepto(48381,-19446,-1765);
		gcall.Stepto(48135,-19460,-1776);
		gcall.Stepto(47887,-19446,-1784);
		gcall.Stepto(47639,-19435,-1790);
		gcall.Stepto(47510,-19418,-1791);
		gcall.Stepto(47304,-19284,-1791);
		gcall.Stepto(47067,-19291,-1788);
		gcall.Stepto(46846,-19299,-1783);
		gcall.Stepto(46577,-19300,-1778);
		gcall.Stepto(46146,-19297,-1777);
		gcall.Stepto(45713,-19282,-1791);
		gcall.Stepto(45273,-19269,-1834);
		gcall.Stepto(44840,-19291,-1883);
		gcall.Stepto(44411,-19357,-1968);
		gcall.Stepto(43982,-19431,-2068);
		gcall.Stepto(43741,-19472,-2131);
		gcall.Stepto(43493,-19515,-2203);
		gcall.Stepto(43247,-19558,-2271);
		gcall.Stepto(43003,-19601,-2334);
		gcall.Stepto(42762,-19660,-2403);
		gcall.Stepto(42522,-19721,-2473);
		gcall.Stepto(42281,-19781,-2536);
		gcall.Stepto(42043,-19851,-2592);
		gcall.Stepto(41836,-19986,-2647);
		gcall.Stepto(41622,-20179,-2708);
		gcall.Stepto(41296,-20466,-2793);
		gcall.Stepto(40968,-20751,-2825);
		gcall.Stepto(40703,-21094,-2845);
		gcall.Stepto(40463,-21457,-2920);
		gcall.Stepto(40316,-21687,-2968);
		gcall.Stepto(40186,-21900,-2984);
		gcall.Stepto(40082,-22125,-3012);
		gcall.Stepto(39966,-22345,-3058);
		gcall.Stepto(39806,-22532,-3095);
		gcall.Stepto(39596,-22633,-3106);
		gcall.Stepto(39276,-22742,-3095);
		gcall.Stepto(38865,-22882,-3105);
		gcall.Stepto(38452,-23024,-3138);
		gcall.Stepto(38176,-23118,-3149);
		gcall.Stepto(37933,-23201,-3151);
		gcall.Stepto(37688,-23235,-3130);
		gcall.Stepto(37502,-23286,-3117);
		gcall.Stepto(37092,-23358,-3127);
		gcall.Stepto(36699,-23323,-3138);
		gcall.Stepto(36532,-23237,-3139);
		gcall.Stepto(36378,-23062,-3123);
		gcall.Stepto(36238,-22859,-3077);
		gcall.NewSpend(1);
		gcall.Stepto(36106,-22649,-3038);
		gcall.Stepto(36049,-22407,-3004);
		gcall.Stepto(36008,-22162,-2993);
		gcall.Stepto(36005,-22140,-2993);
		gcall.Stepto(35981,-22033,-2995);
		Sleep(2000);
		gcall.Stepto(35950,-21892,-2992);
		gcall.WaitPlans();
		gcall.Stepto(35868,-21672,-3000);
		gcall.Stepto(35802,-21433,-3090);
		gcall.NewSpend(2.5);
		gcall.Stepto(35744,-21192,-3217);
		gcall.Stepto(35690,-20950,-3344);
		gcall.Stepto(35636,-20708,-3466);
		gcall.Stepto(35583,-20466,-3584);
		gcall.Stepto(35561,-20218,-3638);
		gcall.Stepto(35536,-19971,-3641);
		gcall.Stepto(35496,-19726,-3611);
		gcall.Stepto(35450,-19483,-3612);
		gcall.Stepto(35411,-19238,-3589);
		gcall.Stepto(35395,-18990,-3572);
		gcall.Stepto(35389,-18865,-3566);
		gcall.Stepto(35392,-18617,-3556);
		gcall.Stepto(35473,-18384,-3558);
		gcall.Stepto(35647,-18213,-3561);
		gcall.Stepto(35858,-18086,-3548);
		gcall.Stepto(36084,-17984,-3547);
		gcall.Stepto(36317,-17898,-3561);
		gcall.Stepto(36558,-17844,-3584);
		gcall.Stepto(36804,-17810,-3594);
		gcall.Stepto(37050,-17776,-3609);
		gcall.Stepto(37295,-17742,-3620);
		gcall.Stepto(37542,-17720,-3621);
		gcall.Stepto(37788,-17742,-3634);
		gcall.Stepto(38030,-17797,-3670);
		gcall.Stepto(38271,-17858,-3731);
		gcall.Stepto(38455,-18016,-3787);
		gcall.NewSpend(1);
		gcall.Stepto(38471,-18065,-3793,10,100,1000,TRUE);
		gcall.Stepto(38428,-18199,-3799,10,100,1000,TRUE);
		gcall.Stepto(38399,-18287,-3802,10,100,1000,TRUE);
		gcall.Stepto(38384,-18333,-3804,10,100,1000,TRUE);
		gcall.Stepto(38298,-18330,-3785,10,100,1000,TRUE);
		gcall.Stepto(38209,-18325,-3774,10,100,1000,TRUE);
		Sleep(4000);
		gcall.sendcall(id_msg_attack, (LPVOID)0x5dca);//tab
		Sleep(1800);
		gcall.sendcall(id_msg_attack, (LPVOID)0x5dca);//tab
		Sleep(1800);
		gcall.TurnToNear(3000);
		gcall.sendcall(id_msg_attack, (LPVOID)0x5e74);//1
		Sleep(500);
		gcall.FindThenKill(0,500,modeAoe | modeNormal | modePickup);
		gcall.Stepto(38316,-18328,-3794);
		gcall.Stepto(38563,-18347,-3810);
		gcall.Stepto(38578,-18348,-3809);
		gcall.Stepto(38754,-18193,-3804);
		gcall.Stepto(38939,-18028,-3789);
		gcall.Stepto(39126,-17865,-3787);
		gcall.Stepto(39161,-17838,-3787);
		gcall.FindThenKill(0,500,modeAoe | modeNormal | modePickup);
		Sleep(1000);
		gcall.DeliverQuests(zid,taskid,L"범박");
		Sleep(1000);
		break;
	case 2:
		gcall.NewSpend(2.5);
		gcall.Stepto(39051,-17831,-3787);
		gcall.Stepto(38791,-17766,-3790);
		gcall.Stepto(38370,-17660,-3730);
		gcall.Stepto(37949,-17555,-3671);
		gcall.Stepto(37534,-17529,-3617);
		gcall.Stepto(37111,-17627,-3618);
		gcall.Stepto(36688,-17722,-3594);
		gcall.Stepto(36269,-17834,-3557);
		gcall.Stepto(35869,-18003,-3544);
		gcall.Stepto(35565,-18306,-3561);
		gcall.Stepto(35380,-18695,-3559);
		gcall.Stepto(35330,-19125,-3582);
		gcall.Stepto(35404,-19552,-3614);
		gcall.Stepto(35474,-19855,-3620);
		gcall.NewSpend(1);
		gcall.Stepto(35528,-20092,-3640);
		gcall.Stepto(35564,-20337,-3636);
		gcall.Stepto(35597,-20583,-3529);
		gcall.Stepto(35646,-20826,-3409);
		gcall.Stepto(35701,-21057,-3291);
		gcall.Stepto(35805,-21478,-3069);
		gcall.Stepto(35928,-21894,-2992);
		Sleep(2000);
		gcall.Stepto(35938,-21929,-2991);
		gcall.WaitPlans();
		gcall.Stepto(36040,-22209,-2992);
		gcall.Stepto(36196,-22617,-3030);
		gcall.Stepto(36378,-23011,-3112);
		gcall.NewSpend(2.5);
		gcall.Stepto(36686,-23309,-3138);
		gcall.Stepto(37103,-23415,-3130);
		gcall.Stepto(37535,-23401,-3129);
		gcall.Stepto(37966,-23351,-3149);
		gcall.Stepto(38396,-23294,-3145);
		gcall.Stepto(38808,-23159,-3135);
		gcall.Stepto(39184,-22936,-3114);
		gcall.Stepto(39538,-22683,-3106);
		gcall.Stepto(39856,-22391,-3068);
		gcall.Stepto(40054,-22166,-3019);
		gcall.Stepto(40197,-21963,-2992);
		gcall.Stepto(40306,-21809,-2983);
		gcall.Stepto(40450,-21605,-2955);
		gcall.Stepto(40593,-21401,-2901);
		gcall.Stepto(40736,-21198,-2854);
		gcall.Stepto(40879,-20995,-2837);
		gcall.Stepto(41022,-20792,-2829);
		gcall.Stepto(41171,-20595,-2818);
		gcall.Stepto(41350,-20422,-2780);
		gcall.Stepto(41540,-20264,-2731);
		gcall.Stepto(41756,-20138,-2683);
		gcall.Stepto(41975,-20020,-2626);
		gcall.Stepto(42194,-19904,-2573);
		gcall.Stepto(42413,-19789,-2510);
		gcall.Stepto(42644,-19698,-2440);
		gcall.Stepto(42885,-19641,-2369);
		gcall.Stepto(43130,-19603,-2305);
		gcall.Stepto(43375,-19564,-2242);
		gcall.Stepto(43623,-19525,-2170);
		gcall.Stepto(43865,-19487,-2100);
		gcall.Stepto(44114,-19448,-2040);
		gcall.Stepto(44360,-19410,-1983);
		gcall.Stepto(44604,-19370,-1926);
		gcall.Stepto(44850,-19334,-1880);
		gcall.Stepto(45095,-19308,-1851);
		gcall.Stepto(45262,-19291,-1834);
		gcall.Stepto(45692,-19262,-1792);
		gcall.Stepto(46127,-19266,-1776);
		gcall.Stepto(46565,-19265,-1776);
		gcall.Stepto(46999,-19261,-1786);
		gcall.Stepto(47423,-19194,-1787);
		gcall.Stepto(47772,-18934,-1773);
		gcall.Stepto(47985,-18557,-1742);
		gcall.Stepto(48196,-18178,-1691);
		gcall.Stepto(48552,-17946,-1677);
		gcall.Stepto(48983,-17906,-1684);
		gcall.Stepto(49417,-17905,-1679);
		gcall.Stepto(49768,-17909,-1664);
		gcall.Stepto(49960,-17911,-1645);
		gcall.Stepto(50212,-17913,-1611);
		gcall.Stepto(50461,-17916,-1569);
		gcall.Stepto(50707,-17919,-1524);
		gcall.Stepto(50955,-17921,-1475);
		gcall.Stepto(51207,-17927,-1433);
		gcall.Stepto(51451,-17938,-1433);
		gcall.Stepto(51681,-17948,-1459);
		gcall.Stepto(52118,-17967,-1265);
		gcall.NewSpend(1);
		gcall.Stepto(52547,-17986,-1074);
		gcall.Stepto(52985,-18005,-880);
		gcall.Stepto(53382,-17999,-700);
		gcall.Stepto(53630,-17987,-619);
		gcall.Stepto(53878,-17974,-619);
		gcall.Stepto(53993,-17968,-619);
		Sleep(2000);
		gcall.Stepto(54282,-17952,-650);
		gcall.Stepto(54729,-17917,-626);
		gcall.WaitPlans();
		gcall.Stepto(55156,-17848,-578);
		gcall.Stepto(55586,-17779,-378);
		gcall.Stepto(56011,-17710,-341);
		gcall.Stepto(56441,-17602,-351);
		gcall.Stepto(56820,-17396,-343);
		gcall.Stepto(57105,-17070,-321);
		gcall.Stepto(57366,-16720,-309);
		gcall.Stepto(57334,-16303,-297);
		gcall.Stepto(57019,-16010,-322);
		gcall.Stepto(56652,-15783,-341);
		gcall.Stepto(56388,-15645,-346);
		gcall.Stepto(56198,-15552,-338);
		gcall.Stepto(55866,-15392,-313);
		gcall.Stepto(55634,-15280,-297);
		gcall.Stepto(55411,-15172,-289);
		gcall.Stepto(55224,-15013,-271);
		gcall.Stepto(55133,-14899,-243);
		gcall.Stepto(54985,-14702,-247);
		gcall.NewSpend(1);
		gcall.Stepto(54967,-14651,-247);
		gcall.Stepto(55077,-14553,-247);
		Sleep(1000);
		gcall.DeliverQuests(zid,taskid,L"도천풍");
		Sleep(1000);
		break;
	case 3:
		gcall.NewSpend(2.5);
		gcall.Stepto(54420,-20195,-607);
		gcall.Stepto(54437,-19966,-609);
		gcall.Stepto(54461,-19718,-609);
		gcall.Stepto(54498,-19472,-609);
		gcall.Stepto(54536,-19227,-609);
		gcall.Stepto(54573,-18983,-609);
		gcall.Stepto(54612,-18737,-609);
		gcall.Stepto(54650,-18488,-613);
		gcall.Stepto(54688,-18248,-622);
		gcall.Stepto(54785,-18024,-628);
		gcall.Stepto(54975,-17867,-636);
		gcall.Stepto(55216,-17805,-542);
		gcall.Stepto(55454,-17749,-406);
		gcall.Stepto(55696,-17692,-378);
		gcall.Stepto(55941,-17634,-341);
		gcall.Stepto(56183,-17578,-341);
		gcall.Stepto(56425,-17521,-353);
		gcall.Stepto(56649,-17468,-345);
		gcall.Stepto(56661,-17247,-332);
		gcall.Stepto(56673,-16996,-320);
		gcall.Stepto(56675,-16849,-326);
		gcall.Stepto(56557,-16677,-331);
		gcall.Stepto(56409,-16475,-339);
		gcall.Stepto(56257,-16279,-350);
		gcall.Stepto(56103,-16081,-355);
		gcall.Stepto(55951,-15886,-354);
		gcall.Stepto(55798,-15689,-339);
		gcall.Stepto(55648,-15496,-315);
		gcall.Stepto(55491,-15302,-294);
		gcall.Stepto(55332,-15113,-279);
		gcall.Stepto(55167,-14926,-243);
		gcall.Stepto(55145,-14903,-243);
		gcall.Stepto(54973,-14728,-247);
		gcall.Stepto(54950,-14705,-247);
		gcall.Stepto(54989,-14588,-247);
		gcall.NewSpend(1);
		Sleep(1000);
		gcall.DeliverQuests(zid,taskid,L"목방형",2);
		Sleep(1000);
		gcall.DeliverQuests(zid,taskid,L"목방형");
		Sleep(1000);
		gcall.NewSpend(2.5);
		gcall.Stepto(55050,-14769,-247);
		gcall.Stepto(55115,-14848,-247);
		gcall.Stepto(55165,-14908,-243);
		gcall.Stepto(55317,-15050,-273);
		gcall.Stepto(55517,-15209,-290);
		gcall.Stepto(55721,-15343,-303);
		gcall.Stepto(55935,-15476,-322);
		gcall.Stepto(56153,-15597,-339);
		gcall.Stepto(56368,-15717,-344);
		gcall.Stepto(56587,-15839,-339);
		gcall.Stepto(56787,-15950,-332);
		gcall.Stepto(56998,-16078,-321);
		gcall.Stepto(57141,-16281,-308);
		gcall.Stepto(57225,-16514,-304);
		gcall.Stepto(57285,-16753,-310);
		gcall.Stepto(57265,-17001,-309);
		gcall.Stepto(57203,-17238,-313);
		gcall.Stepto(57017,-17402,-331);
		gcall.Stepto(56789,-17499,-342);
		gcall.Stepto(56557,-17579,-348);
		gcall.Stepto(56318,-17640,-348);
		gcall.Stepto(56078,-17701,-341);
		gcall.Stepto(55833,-17748,-341);
		gcall.Stepto(55587,-17786,-378);
		gcall.Stepto(55341,-17824,-475);
		gcall.Stepto(55101,-17886,-612);
		gcall.Stepto(54945,-18055,-629);
		gcall.Stepto(54896,-18300,-612);
		gcall.Stepto(54856,-18544,-607);
		gcall.Stepto(54818,-18790,-607);
		gcall.Stepto(54780,-19034,-609);
		gcall.Stepto(54741,-19274,-609);
		gcall.Stepto(54694,-19524,-609);
		gcall.Stepto(54614,-19756,-609);
		gcall.Stepto(54496,-19974,-609);
		gcall.Stepto(54372,-20189,-607);
		gcall.Stepto(54319,-20276,-607);
		gcall.NewSpend(1);
		gcall.SellItemByConfig(L"노점방");
		Sleep(1000);
		//买(80,1,노점방);//应该是上用买了。现在都是加%50的药。

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

void TaskScript::Task_318(int zid,int taskid)
{
	BOOL flagout = FALSE;
	switch (taskid)
	{
	case 1:
		//gcall.ChangeZ_Status(FALSE);
		//Sleep(5000);
		//gcall.ChangeZ_Status(TRUE);
		//Sleep(1000);
		//fPosition mypos;
		//gcall.GetPlayerPos(&mypos);
		//gcall.ChangeHeight(mypos.z + 800);
		//gcall.CityConvey(0x8);
		//gcall.ChangeZ_Status(FALSE);
		//MessageBox(0, L"摇奖完", L"装八卦", MB_OK);
		//gcall.CuncangkuByConfig(L"팔휘연");
		//MessageBox(0, L"摇奖完", L"装八卦", MB_OK);
		gcall.AddTalent(0x135);
		gcall.AddTalent(0x139);
		if (gcall.isTalentPanelShow())
		{
			gcall.OpenTalentUI();
			Sleep(1000);
		}
		
		//执行18级副本

		lianji18_go();
		while (true)
		{
			if (flagout == FALSE)
			{
				if (gcall.GetPlayerLevel() == 17)
				{
					gcall.AddTalent(0x13A);
					if (gcall.isTalentPanelShow())
					{
						gcall.OpenTalentUI();
						Sleep(1000);
					}
					flagout = TRUE;
				}
			}
			if (gcall.GetPlayerLevel()<20)
			{
				UseExperience();
				lianji18();
			}else
			{
				gcall.CityConvey(0x8);
				break;
			}
		}
		gcall.AddTalent(0x148);
		gcall.AddTalent(0x14D);
		gcall.AddTalent(0x14F);
		if (gcall.isTalentPanelShow())
		{
			gcall.OpenTalentUI();
			Sleep(1000);
		}
		gcall.LinQuJiangLi();
		Sleep(1000);
		//gcall.Yaojiang(L"천령강시의 정수",L"남해함대지부 보패함");
		//Sleep(1000);
		gcall.NewSpend(2.5);
		gcall.Stepto(57692,-16839,-290);
		gcall.Stepto(57489,-16962,-295);
		gcall.Stepto(57278,-17092,-306);
		gcall.Stepto(57076,-17235,-325);
		gcall.Stepto(56873,-17378,-341);
		gcall.Stepto(56669,-17519,-344);
		gcall.Stepto(56436,-17599,-351);
		gcall.Stepto(56194,-17652,-341);
		gcall.Stepto(55951,-17703,-341);
		gcall.Stepto(55707,-17748,-378);
		gcall.Stepto(55463,-17792,-404);
		gcall.Stepto(55219,-17836,-543);
		gcall.Stepto(54975,-17880,-636);
		gcall.NewSpend(1);
		gcall.Stepto(54731,-17924,-626);
		gcall.Stepto(54486,-17963,-640);
		gcall.Stepto(54239,-17984,-654);
		gcall.Stepto(54001,-17983,-619);
		Sleep(2000);
		gcall.Stepto(53772,-17981,-619);
		gcall.Stepto(53541,-17980,-631);
		gcall.WaitPlans();
		gcall.NewSpend(2.5);
		gcall.Stepto(53287,-17979,-745);
		gcall.Stepto(53039,-17978,-856);
		gcall.Stepto(52791,-17977,-966);
		gcall.Stepto(52543,-17976,-1076);
		gcall.Stepto(52295,-17975,-1186);
		gcall.Stepto(52047,-17974,-1296);
		gcall.Stepto(51799,-17973,-1406);
		gcall.Stepto(51551,-17972,-1433);
		gcall.Stepto(51303,-17971,-1433);
		gcall.Stepto(51056,-17970,-1441);
		gcall.Stepto(50808,-17969,-1505);
		gcall.Stepto(50560,-17968,-1552);
		gcall.Stepto(50418,-18111,-1580);
		gcall.Stepto(50367,-18355,-1601);
		gcall.Stepto(50316,-18598,-1647);
		gcall.Stepto(50237,-18832,-1689);
		gcall.Stepto(50140,-19060,-1719);
		gcall.Stepto(50042,-19288,-1728);
		gcall.Stepto(49943,-19515,-1743);
		gcall.Stepto(49844,-19743,-1768);
		gcall.Stepto(49751,-19973,-1795);
		gcall.Stepto(49661,-20204,-1784);
		gcall.Stepto(49571,-20435,-1753);
		gcall.Stepto(49530,-20679,-1736);
		gcall.Stepto(49526,-20927,-1711);
		gcall.Stepto(49559,-21173,-1689);
		gcall.Stepto(49609,-21416,-1673);
		gcall.Stepto(49660,-21658,-1661);
		gcall.Stepto(49712,-21901,-1649);
		gcall.Stepto(49763,-22144,-1643);
		gcall.Stepto(49815,-22386,-1638);
		gcall.Stepto(49867,-22629,-1630);
		gcall.Stepto(49919,-22871,-1622);
		gcall.Stepto(49994,-23107,-1615);
		gcall.Stepto(50077,-23341,-1610);
		gcall.Stepto(50163,-23574,-1609);
		gcall.Stepto(50260,-23802,-1610);
		gcall.Stepto(50357,-24030,-1614);
		gcall.Stepto(50455,-24258,-1617);
		gcall.Stepto(50552,-24486,-1616);
		gcall.Stepto(50650,-24714,-1612);
		gcall.Stepto(50747,-24942,-1606);
		gcall.Stepto(50848,-25169,-1589);
		gcall.Stepto(50991,-25372,-1563);
		gcall.Stepto(51149,-25564,-1536);
		gcall.Stepto(51310,-25759,-1503);
		gcall.Stepto(51469,-25952,-1465);
		gcall.Stepto(51625,-26145,-1426);
		gcall.Stepto(51785,-26335,-1389);
		gcall.Stepto(51960,-26510,-1350);
		gcall.Stepto(52138,-26682,-1310);
		gcall.Stepto(52317,-26854,-1282);
		gcall.Stepto(52496,-27026,-1265);
		gcall.Stepto(52675,-27198,-1253);
		gcall.Stepto(52854,-27370,-1236);
		gcall.Stepto(53025,-27549,-1216);
		gcall.Stepto(53180,-27743,-1205);
		gcall.Stepto(53334,-27942,-1203);
		gcall.Stepto(53480,-28143,-1201);
		gcall.Stepto(53627,-28343,-1197);
		gcall.Stepto(53789,-28529,-1195);
		gcall.Stepto(53970,-28699,-1198);
		gcall.Stepto(54149,-28871,-1208);
		gcall.NewSpend(1);
		gcall.Stepto(54328,-29043,-1228);
		gcall.Stepto(54506,-29215,-1263);
		gcall.Stepto(54691,-29381,-1321);
		gcall.Stepto(54901,-29513,-1390);
		gcall.Stepto(55110,-29645,-1462);
		gcall.Stepto(55287,-29767,-1510);
		Sleep(2000);
		gcall.Stepto(55453,-29883,-1539);
		gcall.WaitPlans();
		gcall.NewSpend(2.5);
		gcall.Stepto(55623,-30003,-1548);
		gcall.Stepto(55826,-30144,-1561);
		gcall.Stepto(56037,-30275,-1580);
		gcall.Stepto(56249,-30405,-1600);
		gcall.Stepto(56460,-30534,-1618);
		gcall.Stepto(56672,-30663,-1642);
		gcall.Stepto(56883,-30792,-1667);
		gcall.Stepto(57095,-30922,-1700);
		gcall.Stepto(57304,-31055,-1729);
		gcall.Stepto(57516,-31189,-1755);
		gcall.Stepto(57725,-31322,-1777);
		gcall.Stepto(57934,-31456,-1799);
		gcall.Stepto(58149,-31578,-1815);
		gcall.Stepto(58370,-31692,-1833);
		gcall.Stepto(58598,-31790,-1851);
		gcall.Stepto(58831,-31873,-1873);
		gcall.NewSpend(1);
		gcall.Stepto(59070,-31945,-1901);
		gcall.Stepto(59305,-32025,-1928);
		gcall.DeliverQuests(zid,taskid,L"서문범");
		Sleep(2000);
		gcall.Stepto(59260,-32080,-1922);
		gcall.Stepto(59165,-32192,-1913);
		gcall.Stepto(59015,-32388,-1908);
		gcall.Stepto(58994,-32418,-1904);
		gcall.Stepto(59004,-32448,-1903);
		gcall.Stepto(59043,-32529,-1910);
		gcall.Stepto(59106,-32647,-1908);
		gcall.Stepto(59154,-32736,-1908);
		gcall.Stepto(59170,-32763,-1909);
		gcall.Stepto(59171,-32764,-1909);
		Sleep(1000);
		gcall.FixWuqi();
		Sleep(1000);
		gcall.Stepto(59171,-32765,-1909);
		gcall.Stepto(58949,-32775,-1887);
		gcall.Stepto(58701,-32787,-1851);
		gcall.CuncangkuByConfig(L"석두");
		break;
	case 2:
		gcall.randXianlu(0);
		Sleep(1000);
		gcall.NewSpend(2.5);
		gcall.Stepto(59689,-32007,-1990,10,20,3000);
		gcall.Stepto(59916,-31991,-2034,10,20,3000);
		gcall.Stepto(60163,-31981,-2073);
		gcall.Stepto(60410,-32017,-2125);
		gcall.Stepto(60652,-32061,-2171);
		gcall.Stepto(60887,-32109,-2213);
		gcall.Stepto(61140,-32162,-2257);
		gcall.Stepto(61383,-32213,-2298);
		gcall.Stepto(61627,-32249,-2344);
		gcall.Stepto(61872,-32280,-2385);
		gcall.Stepto(62120,-32312,-2423);
		gcall.Stepto(62366,-32344,-2462);
		gcall.Stepto(62605,-32374,-2501);
		gcall.Stepto(62860,-32407,-2513);
		gcall.Stepto(63105,-32438,-2541);
		gcall.Stepto(63350,-32455,-2557);
		gcall.Stepto(63600,-32450,-2572);
		gcall.Stepto(63848,-32442,-2583);
		gcall.Stepto(64098,-32434,-2594);
		gcall.Stepto(64345,-32425,-2608);
		gcall.Stepto(64593,-32420,-2625);
		gcall.Stepto(64842,-32430,-2657);
		gcall.Stepto(65088,-32454,-2675);
		gcall.Stepto(65331,-32482,-2701);
		gcall.Stepto(65580,-32510,-2728);
		gcall.Stepto(65826,-32547,-2746);
		gcall.Stepto(66028,-32601,-2761);
		gcall.Stepto(66221,-32653,-2772);
		gcall.Stepto(66413,-32705,-2781);
		gcall.Stepto(66602,-32756,-2789);
		gcall.Stepto(66794,-32808,-2796);
		gcall.Stepto(67022,-32873,-2804);
		gcall.Stepto(67249,-32976,-2815);
		gcall.Stepto(67472,-33081,-2834);
		gcall.Stepto(67698,-33190,-2853);
		gcall.Stepto(67907,-33318,-2875);
		gcall.Stepto(68118,-33452,-2894);
		gcall.Stepto(68328,-33586,-2901);
		gcall.Stepto(68538,-33720,-2897);
		gcall.Stepto(68748,-33853,-2882);
		gcall.Stepto(68962,-33975,-2853);
		gcall.Stepto(69197,-34040,-2813);
		gcall.Stepto(69443,-33996,-2788);
		gcall.Stepto(69675,-33914,-2785);
		gcall.Stepto(69877,-33839,-2783);
		gcall.Stepto(70065,-33772,-2777);
		gcall.Stepto(70257,-33732,-2779);
		gcall.Stepto(70454,-33756,-2758);
		gcall.Stepto(70605,-33850,-2726);
		gcall.Stepto(70606,-33851,-2725);
		gcall.NewSpend(1);
		gcall.sendcall(id_msg_attack, (LPVOID)0x5E06);//3
		gcall.FindThenKill(0,300,modeAoe | modeNormal | modePickup);
		gcall.Stepto(70452,-33724,-2758);
		gcall.Stepto(70620,-33868,-2723);
		Sleep(1000);
		gcall.PickupTask();
		Sleep(1000);
		/*gcall.Stepto(70452,-33724,-2758);
		gcall.Stepto(70620,-33868,-2723);
		对准角度(70707,-33921,-2723);
		Sleep(1000);
		按键(F);
		Sleep(3000);
		按键(F);*/
		Sleep(1000);
		gcall.Stepto(70589,-33824,-2733);
		gcall.Stepto(70511,-33815,-2757);
		gcall.Stepto(70282,-33894,-2789);
		gcall.Stepto(70341,-34079,-2807);
		gcall.Stepto(70564,-34171,-2842);
		gcall.Stepto(70788,-34263,-2907);
		gcall.Stepto(71034,-34265,-3107);
		gcall.Stepto(71262,-34175,-3099);
		gcall.Stepto(71477,-34052,-3098);
		gcall.Stepto(71679,-33908,-3100);
		gcall.Stepto(71879,-33761,-3062);
		gcall.Stepto(72053,-33713,-3049);
		gcall.Stepto(72229,-33806,-3044);
		gcall.Stepto(72304,-33877,-3038);
		//过滤怪物(풍암괴,1);
		//过滤怪物(중갑게,1);
		Sleep(1000);
		gcall.Kill_Tab();
		gcall.Kill_Tab();
		gcall.sendcall(id_msg_attack, (LPVOID)0x5e74);//1
		gcall.FindThenKill(0,900,modeAoe| modeNormal | modeGoback | modePickup);
		gcall.NewSpend(2.5);
		gcall.Stepto(72256,-33888,-3040);
		gcall.Stepto(72148,-33787,-3046);
		gcall.Stepto(72001,-33653,-3050);
		gcall.Stepto(71855,-33517,-3053);
		gcall.Stepto(71710,-33381,-3063);
		gcall.Stepto(71565,-33246,-3050);
		gcall.Stepto(71419,-33113,-3035);
		gcall.Stepto(71258,-32996,-3022);
		gcall.Stepto(71096,-32881,-3003);
		gcall.Stepto(70935,-32766,-2989);
		gcall.Stepto(70777,-32653,-2998);
		gcall.Stepto(70597,-32565,-3019);
		gcall.Stepto(70401,-32543,-3014);
		gcall.Stepto(70200,-32553,-3001);
		gcall.Stepto(70016,-32626,-2994);
		gcall.Stepto(69820,-32714,-2982);
		gcall.Stepto(69593,-32823,-2964);
		gcall.Stepto(69370,-32929,-2949);
		gcall.Stepto(69146,-33036,-2933);
		gcall.Stepto(68964,-33112,-2924);
		gcall.Stepto(68771,-33155,-2923);
		gcall.Stepto(68571,-33165,-2917);
		gcall.Stepto(68375,-33155,-2910);
		gcall.Stepto(68175,-33130,-2891);
		gcall.Stepto(67942,-33086,-2864);
		gcall.Stepto(67697,-33030,-2845);
		gcall.Stepto(67459,-32967,-2827);
		gcall.Stepto(67218,-32902,-2811);
		gcall.Stepto(66981,-32838,-2801);
		gcall.Stepto(66908,-32818,-2798);
		
		break;
	case 3:
		gcall.NewSpend(2.5);
		gcall.Stepto(71804,-32583,-3092);
		gcall.Stepto(71371,-32557,-3063);
		gcall.Stepto(70938,-32572,-3014);
		gcall.Stepto(70602,-32600,-3011);
		gcall.Stepto(70384,-32637,-3001);
		gcall.Stepto(69959,-32721,-2980);
		gcall.Stepto(69623,-32822,-2964);
		gcall.Stepto(69424,-32912,-2952);
		gcall.Stepto(69030,-33097,-2926);
		gcall.Stepto(68617,-33199,-2916);
		gcall.Stepto(68186,-33121,-2892);
		gcall.Stepto(67766,-33028,-2848);
		gcall.Stepto(67356,-32874,-2815);
		gcall.Stepto(66953,-32717,-2793);
		gcall.Stepto(66535,-32614,-2776);
		gcall.Stepto(66244,-32548,-2765);
		gcall.Stepto(66015,-32497,-2751);
		gcall.Stepto(65761,-32439,-2733);
		gcall.Stepto(65520,-32384,-2714);
		gcall.Stepto(65273,-32353,-2689);
		gcall.Stepto(65126,-32350,-2674);
		gcall.Stepto(64952,-32344,-2661);
		gcall.Stepto(64531,-32329,-2619);
		gcall.Stepto(64096,-32330,-2593);
		gcall.Stepto(63658,-32352,-2575);
		gcall.Stepto(63367,-32366,-2560);
		gcall.Stepto(63121,-32368,-2545);
		gcall.Stepto(62879,-32362,-2516);
		gcall.Stepto(62624,-32350,-2502);
		gcall.Stepto(62375,-32338,-2463);
		gcall.Stepto(62127,-32326,-2425);
		gcall.Stepto(61861,-32304,-2384);
		gcall.Stepto(61442,-32201,-2309);
		gcall.Stepto(61016,-32095,-2237);
		gcall.Stepto(60664,-32009,-2175);
		gcall.Stepto(60416,-31950,-2131);
		gcall.Stepto(60183,-31922,-2084);
		gcall.Stepto(59887,-31904,-2031);
		gcall.NewSpend(1);
		gcall.Stepto(59520,-31971,-1962);
		gcall.Stepto(59317,-32054,-1928);
		Sleep(1000);
		gcall.DeliverQuests(zid,5,L"서문범");
		Sleep(3000);
		gcall.Stepto(59331,-32020,-1932);
		gcall.Stepto(59236,-32166,-1918);
		gcall.Stepto(59092,-32370,-1912);
		gcall.Stepto(58950,-32573,-1891);
		gcall.Stepto(58815,-32777,-1860);
		gcall.Stepto(58713,-32932,-1850);
		gcall.Stepto(58798,-33007,-1850);
		gcall.Stepto(58800,-33008,-1850);
		gcall.FenJieByConfig();
		Sleep(1000);
		gcall.SellItemByConfig(L"마전표");

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

void TaskScript::Task_495(int zid,int taskid)
{
	switch (taskid)
	{
	case 1:
		gcall.NewSpend(2.5);
		gcall.Stepto(59352,-32021,-1935,20,20,3000);
		gcall.Stepto(59506,-31967,-1960,20,20,3000);
		gcall.Stepto(59806,-31929,-2015);
		gcall.Stepto(60238,-31897,-2095);
		gcall.Stepto(60666,-31971,-2175);
		gcall.Stepto(60893,-32022,-2216);
		gcall.Stepto(61124,-32097,-2255);
		gcall.Stepto(61267,-32262,-2277);
		gcall.Stepto(61344,-32487,-2289);
		gcall.Stepto(61439,-32693,-2309);
		gcall.Stepto(61689,-32704,-2354);
		gcall.Stepto(61931,-32674,-2398);
		gcall.Stepto(62108,-32650,-2428);
		gcall.Stepto(62388,-32613,-2487);
		gcall.Stepto(62787,-32734,-2515);
		gcall.Stepto(62851,-33142,-2529);
		gcall.Stepto(62780,-33570,-2759);
		gcall.Stepto(62594,-33961,-2974);
		gcall.Stepto(62271,-34248,-2996);
		gcall.Stepto(61939,-34451,-2989);
		gcall.Stepto(61716,-34568,-2977);
		gcall.Stepto(61492,-34674,-2961);
		gcall.Stepto(61271,-34775,-2934);
		gcall.Stepto(61044,-34875,-2896);
		gcall.Stepto(60828,-34991,-2868);
		gcall.Stepto(60616,-35119,-2835);
		gcall.Stepto(60414,-35266,-2802);
		gcall.Stepto(60263,-35459,-2779);
		gcall.Stepto(60095,-35637,-2739);
		gcall.Stepto(59887,-35773,-2717);
		gcall.Stepto(59721,-35879,-2698);
		gcall.Stepto(59369,-36131,-2659);
		gcall.Stepto(59036,-36408,-2616);
		gcall.Stepto(58732,-36708,-2581);
		gcall.Stepto(58528,-37006,-2537);
		gcall.NewSpend(1);
		Sleep(1000);
		gcall.DeliverQuests(zid,taskid,L"복진무");
		Sleep(1000);
		gcall.FindThenKill(0,500,modeAoe | modeNormal | modePickup);
		break;
	case 2:
		gcall.randXianlu(0);
		Sleep(1000);
		gcall.NewSpend(2.5);
		gcall.Stepto(59000,-32455,-1902,20,20,3000);
		gcall.Stepto(59263,-31900,-1927,20,20,3000);
		gcall.Stepto(59646,-32241,-1969);
		gcall.Stepto(60468,-32070,-2136);
		gcall.Stepto(61836,-32326,-2380);
		gcall.Stepto(62796,-32835,-2517);
		gcall.Stepto(63889,-32946,-2574);
		gcall.Stepto(64700,-33276,-2825);
		gcall.Stepto(63922,-33867,-2970);
		gcall.Stepto(62803,-34130,-2993);
		gcall.Stepto(61487,-34495,-2960);
		gcall.Stepto(60472,-35121,-2809);
		gcall.Stepto(59642,-35832,-2694);
		gcall.Stepto(58671,-36561,-2588);
		gcall.Stepto(58619,-36947,-2555);
		//过滤怪物(풍암괴,2);
		//过滤怪物(삿갓 녹포검귀,1);
		gcall.NewSpend(1);
		gcall.Stepto(59379,-36181,-2659);
		Sleep(500);
		gcall.FindThenKill(0,500,modeAoe | modeNormal | modePickup | modeGoback);
		gcall.sendcall(id_msg_attack, (LPVOID)0x5DFC);
		gcall.NewSpend(2.5);
		gcall.Stepto(59604,-35913,-2684,20,20,3000);
		gcall.Stepto(59669,-35862,-2695,20,20,3000);
		gcall.Stepto(59865,-35710,-2718);
		gcall.Stepto(60068,-35568,-2741);
		gcall.Stepto(60271,-35426,-2781);
		gcall.Stepto(60475,-35285,-2805);
		gcall.Stepto(60686,-35155,-2841);
		gcall.Stepto(60801,-35087,-2862);
		gcall.NewSpend(1);
		Sleep(1000);
		gcall.FindThenKill(0,500,modeAoe | modeNormal | modePickup | modeGoback);
		gcall.sendcall(id_msg_attack, (LPVOID)0x5DFC);
		gcall.NewSpend(2.5);
		gcall.Stepto(60812,-35083,-2863,20,20,3000);
		gcall.Stepto(61054,-35023,-2882,20,20,3000);
		gcall.Stepto(61294,-34971,-2925);
		gcall.Stepto(61536,-34919,-2954);
		gcall.Stepto(61780,-34869,-2981);
		gcall.Stepto(62025,-34819,-2998);
		gcall.Stepto(62268,-34843,-3016);
		gcall.Stepto(62325,-34864,-3019);
		gcall.NewSpend(1);
		Sleep(1000);
		gcall.FindThenKill(0,500,modeAoe | modeNormal | modePickup | modeGoback);
		gcall.sendcall(id_msg_attack, (LPVOID)0x5DFC);
		gcall.NewSpend(2.5);
		gcall.Stepto(62499,-34832,-3018,20,20,3000);
		gcall.Stepto(62740,-34788,-3015,20,20,3000);
		gcall.Stepto(62984,-34745,-3013);
		gcall.Stepto(63231,-34724,-3029);
		gcall.Stepto(63446,-34843,-3085);
		gcall.Stepto(63654,-34984,-3140);
		gcall.Stepto(63857,-35123,-3172);
		gcall.Stepto(64025,-35237,-3172);
		gcall.NewSpend(1);
		Sleep(1000);
		gcall.FindThenKill(0,500,modeAoe | modeNormal | modePickup | modeGoback);
		gcall.sendcall(id_msg_attack, (LPVOID)0x5DFC);
		gcall.NewSpend(2.5);
		gcall.Stepto(62499,-34832,-3018,20,20,3000);
		gcall.Stepto(62740,-34788,-3015,20,20,3000);
		gcall.Stepto(62984,-34745,-3013);
		gcall.Stepto(63231,-34724,-3029);
		gcall.Stepto(63446,-34843,-3085);
		gcall.Stepto(63654,-34984,-3140);
		gcall.Stepto(63857,-35123,-3172);
		gcall.Stepto(64025,-35237,-3172);
		gcall.NewSpend(1);
		Sleep(1000);
		gcall.FindThenKill(0,500,modeAoe | modeNormal | modePickup | modeGoback);
		gcall.sendcall(id_msg_attack, (LPVOID)0x5DFC);
		gcall.NewSpend(2.5);
		gcall.Stepto(64245,-35273,-3172,20,20,3000);
		gcall.Stepto(64491,-35306,-3172,20,20,3000);
		gcall.Stepto(64737,-35339,-3172);
		gcall.Stepto(64984,-35372,-3172);
		gcall.Stepto(65225,-35425,-3172);
		gcall.Stepto(65451,-35524,-3172);
		gcall.Stepto(65671,-35639,-3172);
		gcall.Stepto(65721,-35666,-3173);
		gcall.NewSpend(1);
		Sleep(1000);
		gcall.FindThenKill(0,500,modeAoe | modeNormal | modePickup | modeGoback);
		gcall.sendcall(id_msg_attack, (LPVOID)0x5DFC);
		gcall.Stepto(65740,-35429,-3172,20,20,3000);
		gcall.Stepto(65759,-35182,-3172,20,20,3000);
		gcall.Stepto(65779,-34936,-3172);
		gcall.Stepto(65808,-34689,-3172);
		gcall.Stepto(65825,-34578,-3172);
		Sleep(500);
		gcall.FindThenKill(0,500,modeAoe | modeNormal | modePickup | modeGoback);
		gcall.sendcall(id_msg_attack, (LPVOID)0x5DFC);
		gcall.NewSpend(2.5);
		gcall.Stepto(65856,-34520,-3172,20,20,3000);
		gcall.Stepto(65976,-34303,-3174,20,20,3000);
		gcall.Stepto(66045,-34178,-3174);
		gcall.Stepto(66062,-34161,-3174);
		gcall.Stepto(66075,-34146,-3174);
		gcall.Stepto(66218,-34117,-3172);
		gcall.Stepto(66460,-34072,-3133);
		gcall.Stepto(66707,-34032,-3056);
		gcall.Stepto(66951,-33993,-2949);
		gcall.Stepto(67195,-33954,-2892);
		gcall.Stepto(67441,-33915,-2887);
		gcall.Stepto(67685,-33876,-2893);
		gcall.Stepto(67918,-33903,-2900);
		gcall.Stepto(68089,-34059,-2908);
		gcall.Stepto(68234,-34195,-2915);
		gcall.Stepto(68377,-34328,-2924);
		gcall.Stepto(68524,-34466,-2935);
		gcall.Stepto(68668,-34601,-2952);
		gcall.Stepto(68825,-34748,-2976);
		gcall.Stepto(69006,-34917,-3009);
		gcall.Stepto(69084,-35138,-3044);
		gcall.Stepto(69070,-35386,-3080);
		gcall.Stepto(69013,-35624,-3112);
		gcall.Stepto(69011,-35630,-3113);
		gcall.NewSpend(1);
		Sleep(1000);
		gcall.FindThenKill(0,500,modeAoe | modeNormal | modePickup | modeGoback);
		gcall.sendcall(id_msg_attack, (LPVOID)0x5DFC);
		gcall.NewSpend(2.5);
		gcall.Stepto(69131,-35627,-3106,20,20,3000);
		gcall.Stepto(69376,-35609,-3102,20,20,3000);
		gcall.Stepto(69623,-35588,-3106);
		gcall.Stepto(69869,-35556,-3104);
		gcall.Stepto(70113,-35508,-3101);
		gcall.Stepto(70354,-35454,-3117);
		gcall.Stepto(70458,-35431,-3117);
		gcall.NewSpend(1);
		Sleep(1000);
		gcall.FindThenKill(0,500,modeAoe | modeNormal | modePickup | modeGoback);
		gcall.sendcall(id_msg_attack, (LPVOID)0x5DFC);
		gcall.NewSpend(2.5);
		gcall.Stepto(70514,-35450,-3121,20,20,3000);
		gcall.Stepto(70590,-35507,-3132,20,20,3000);
		gcall.Stepto(70694,-35598,-3139);
		gcall.Stepto(70864,-35649,-3171);
		gcall.Stepto(71057,-35707,-3169);
		gcall.Stepto(71157,-35910,-3169);
		gcall.Stepto(71263,-36135,-3168);
		gcall.Stepto(71369,-36359,-3170);
		gcall.Stepto(71396,-36418,-3172);
		gcall.NewSpend(1);
		Sleep(1000);
		gcall.FindThenKill(0,500,modeAoe | modeNormal | modePickup | modeGoback);
		gcall.sendcall(id_msg_attack, (LPVOID)0x5DFC);
		gcall.Stepto(71243,-36579,-3175,20,20,3000);
		gcall.Stepto(71072,-36759,-3177,20,20,3000);
		gcall.Stepto(70903,-36938,-3172);
		gcall.Stepto(70851,-36992,-3172);
		Sleep(500);
		gcall.FindThenKill(0,500,modeAoe | modeNormal | modePickup | modeGoback);
		gcall.sendcall(id_msg_attack, (LPVOID)0x5DFC);
		gcall.NewSpend(2.5);
		gcall.Stepto(70958,-37023,-3176,20,20,3000);
		gcall.Stepto(71186,-37118,-3183,20,20,3000);
		gcall.Stepto(71411,-37225,-3182);
		gcall.Stepto(71635,-37331,-3177);
		gcall.Stepto(71859,-37438,-3175);
		gcall.Stepto(71995,-37618,-3178);
		gcall.Stepto(72051,-37863,-3178);
		gcall.Stepto(72105,-38101,-3177);
		gcall.Stepto(72160,-38346,-3178);
		gcall.Stepto(72193,-38489,-3178);
		gcall.NewSpend(1);
		Sleep(1000);
		gcall.FindThenKill(0,500,modeAoe | modeNormal | modePickup | modeGoback);
		gcall.sendcall(id_msg_attack, (LPVOID)0x5DFC);
		gcall.NewSpend(2.5);
		gcall.Stepto(72048,-38459,-3176,20,20,3000);
		gcall.Stepto(72025,-38454,-3176,20,20,3000);
		gcall.Stepto(71848,-38421,-3175);
		gcall.Stepto(71604,-38366,-3176);
		gcall.Stepto(71363,-38307,-3181);
		gcall.Stepto(71123,-38245,-3188);
		gcall.Stepto(70893,-38157,-3190);
		gcall.Stepto(70821,-38129,-3187);
		gcall.NewSpend(1);
		Sleep(1000);
		gcall.FindThenKill(0,500,modeAoe | modeNormal | modePickup | modeGoback);
		gcall.sendcall(id_msg_attack, (LPVOID)0x5DFC);
		gcall.NewSpend(2.5);
		gcall.Stepto(70745,-38098,-3181,20,20,3000);
		gcall.Stepto(70504,-38040,-3171,20,20,3000);
		gcall.Stepto(70265,-37968,-3161);
		gcall.Stepto(70029,-37898,-3154);
		gcall.Stepto(69791,-37829,-3168);
		gcall.Stepto(69542,-37804,-3172);
		gcall.Stepto(69307,-37768,-3172);
		gcall.Stepto(69304,-37767,-3172);
		gcall.NewSpend(1);
		Sleep(1000);
		gcall.FindThenKill(0,500,modeAoe | modeNormal | modePickup | modeGoback);
		gcall.sendcall(id_msg_attack, (LPVOID)0x5DFC);
		gcall.NewSpend(2.5);
		gcall.Stepto(69303,-37768,-3172,20,20,3000);
		gcall.Stepto(69086,-37867,-3175,20,20,3000);
		gcall.Stepto(68861,-37970,-3179);
		gcall.Stepto(68633,-38074,-3164);
		gcall.Stepto(68410,-38176,-3170);
		gcall.Stepto(68171,-38117,-3172);
		gcall.Stepto(67938,-38039,-3169);
		gcall.Stepto(67745,-37891,-3169);
		gcall.Stepto(67556,-37728,-3172);
		gcall.Stepto(67359,-37577,-3172);
		gcall.Stepto(67157,-37433,-3172);
		gcall.Stepto(67022,-37338,-3172);
		gcall.NewSpend(1);
		Sleep(1000);
		gcall.FindThenKill(0,500,modeAoe | modeNormal | modePickup | modeGoback);
		gcall.sendcall(id_msg_attack, (LPVOID)0x5DFC);
		gcall.NewSpend(2.5);
		gcall.Stepto(66897,-37167,-3172,20,20,3000);
		gcall.Stepto(66755,-36963,-3172,20,20,3000);
		gcall.Stepto(66613,-36758,-3172);
		gcall.Stepto(66479,-36552,-3172);
		gcall.Stepto(66342,-36342,-3174);
		gcall.Stepto(66207,-36135,-3174);
		gcall.Stepto(66073,-35927,-3174);
		gcall.Stepto(65936,-35717,-3173);
		gcall.Stepto(65846,-35578,-3172);
		gcall.Stepto(65816,-35586,-3172);
		gcall.Stepto(65512,-35655,-3172);
		gcall.Stepto(65314,-35689,-3172);
		gcall.Stepto(65118,-35717,-3174);
		gcall.Stepto(64923,-35743,-3172);
		gcall.Stepto(64724,-35769,-3172);
		gcall.Stepto(64504,-35798,-3172);
		gcall.Stepto(64293,-35735,-3172);
		gcall.Stepto(64154,-35532,-3172);
		gcall.Stepto(64032,-35354,-3172);
		gcall.NewSpend(1);
		Sleep(1000);
		gcall.FindThenKill(0,500,modeAoe | modeNormal | modePickup | modeGoback);
		gcall.sendcall(id_msg_attack, (LPVOID)0x5DFC);
		gcall.NewSpend(2.5);
		gcall.Stepto(64061,-35469,-3172,20,20,3000);
		gcall.Stepto(64126,-35709,-3172,20,20,3000);
		gcall.Stepto(64195,-35947,-3172);
		gcall.Stepto(64263,-36185,-3152);
		gcall.Stepto(64302,-36318,-3128);
		gcall.Stepto(64406,-36393,-3107);
		gcall.Stepto(64605,-36536,-3070);
		gcall.Stepto(64807,-36681,-3075);
		gcall.Stepto(64822,-36692,-3076);
		gcall.Stepto(64802,-36842,-3067);
		gcall.Stepto(64768,-37086,-3058);
		gcall.Stepto(64767,-37094,-3058);
		gcall.NewSpend(1);
		Sleep(1000);
		gcall.FindThenKill(0,500,modeAoe | modeNormal | modePickup | modeGoback);
		gcall.sendcall(id_msg_attack, (LPVOID)0x5DFC);
		gcall.NewSpend(2.5);
		gcall.Stepto(64776,-36868,-3063,20,20,3000);
		gcall.Stepto(64786,-36620,-3074,20,20,3000);
		gcall.Stepto(64789,-36547,-3078);
		gcall.Stepto(64784,-36545,-3077);
		gcall.Stepto(64693,-36514,-3071);
		gcall.Stepto(64458,-36435,-3096);
		gcall.Stepto(64405,-36417,-3104);
		gcall.Stepto(64387,-36397,-3108);
		gcall.Stepto(64291,-36225,-3142);
		gcall.Stepto(64159,-36014,-3172);
		gcall.Stepto(64029,-35817,-3172);
		gcall.Stepto(63969,-35844,-3172);
		gcall.Stepto(63745,-35951,-3172);
		gcall.Stepto(63522,-36059,-3172);
		gcall.Stepto(63420,-36108,-3172);
		gcall.Stepto(63309,-36213,-3172);
		gcall.Stepto(63164,-36415,-3172);
		gcall.Stepto(63003,-36603,-3172);
		gcall.Stepto(62823,-36774,-3172);
		gcall.Stepto(62643,-36944,-3172);
		gcall.Stepto(62463,-37113,-3172);
		gcall.Stepto(62401,-37172,-3172);
		gcall.Stepto(62363,-37129,-3172);
		gcall.Stepto(62345,-37108,-3172);
		gcall.NewSpend(1);
		Sleep(1000);
		gcall.FindThenKill(0,500,modeAoe | modeNormal | modePickup | modeGoback);
		gcall.sendcall(id_msg_attack, (LPVOID)0x5DFC);
		gcall.Stepto(62378,-37150,-3172,20,20,3000);
		gcall.Stepto(62534,-37343,-3172);
		gcall.Stepto(62667,-37548,-3172);
		gcall.Stepto(62800,-37743,-3172);
		Sleep(500);
		gcall.FindThenKill(0,500,modeAoe | modeNormal | modePickup | modeGoback);
		gcall.sendcall(id_msg_attack, (LPVOID)0x5DFC);
		gcall.NewSpend(2.5);
		gcall.Stepto(62785,-37715,-3172,20,20,3000);
		gcall.Stepto(62669,-37496,-3172,20,20,3000);
		gcall.Stepto(62553,-37276,-3172);
		gcall.Stepto(62436,-37057,-3172);
		gcall.Stepto(62310,-36841,-3172);
		gcall.Stepto(62166,-36642,-3172);
		gcall.Stepto(62022,-36443,-3167);
		gcall.Stepto(61878,-36238,-3108);
		gcall.Stepto(61734,-36034,-3094);
		gcall.Stepto(61592,-35832,-3076);
		gcall.Stepto(61496,-35879,-3074);
		gcall.Stepto(61322,-36055,-3066);
		gcall.Stepto(61163,-36243,-3058);
		gcall.Stepto(61110,-36306,-3055);
		gcall.Stepto(61139,-36541,-3068);
		gcall.Stepto(61154,-36786,-3077);
		gcall.Stepto(61148,-36913,-3081);
		gcall.Stepto(61149,-37161,-3072);
		gcall.Stepto(61149,-37409,-3073);
		gcall.Stepto(61149,-37552,-3080);
		gcall.NewSpend(1);
		Sleep(1000);
		gcall.FindThenKill(0,500,modeAoe | modeNormal | modePickup | modeGoback);
		gcall.sendcall(id_msg_attack, (LPVOID)0x5DFC);
		gcall.NewSpend(2.5);
		gcall.Stepto(61080,-37550,-3081,20,20,3000);
		gcall.Stepto(60835,-37587,-3076,20,20,3000);
		gcall.Stepto(60591,-37626,-3066);
		gcall.Stepto(60347,-37669,-3035);
		gcall.Stepto(60103,-37711,-3033);
		gcall.Stepto(59859,-37754,-3044);
		gcall.Stepto(59617,-37796,-3040);
		gcall.Stepto(59612,-37797,-3040);
		gcall.NewSpend(1);
		Sleep(1000);
		gcall.FindThenKill(0,500,modeAoe | modeNormal | modePickup | modeGoback);
		gcall.sendcall(id_msg_attack, (LPVOID)0x5DFC);
		gcall.Stepto(59612,-37703,-3027,20,20,3000);
		gcall.Stepto(59609,-37455,-3001,20,20,3000);
		gcall.Stepto(59605,-37207,-2962);
		gcall.Stepto(59621,-36960,-2905);
		gcall.Stepto(59698,-36722,-2803);
		gcall.Stepto(59760,-36494,-2754);
		//过滤怪物(풍암괴,3);
		//过滤怪物(삿갓 녹포검귀,3);
		gcall.FenJieByConfig();
		break;
	case 3:
		gcall.NewSpend(2.5);
		gcall.Stepto(62443,-37032,-3172,20,20,3000);
		gcall.Stepto(62301,-36836,-3172,20,20,3000);
		gcall.Stepto(62152,-36638,-3172,20,20,3000);
		gcall.Stepto(62000,-36441,-3166);
		gcall.Stepto(61864,-36235,-3108);
		gcall.Stepto(61742,-36018,-3092);
		gcall.Stepto(61560,-35936,-3081);
		gcall.Stepto(61312,-35936,-3057);
		gcall.Stepto(61068,-35977,-3017);
		gcall.Stepto(60827,-36036,-2951);
		gcall.Stepto(60587,-36096,-2892);
		gcall.Stepto(60346,-36155,-2835);
		gcall.Stepto(60112,-36236,-2785);
		gcall.Stepto(59889,-36345,-2755);
		gcall.Stepto(59669,-36459,-2721);
		gcall.Stepto(59448,-36573,-2682);
		gcall.Stepto(59225,-36680,-2647);
		gcall.Stepto(59000,-36784,-2591);
		gcall.Stepto(58772,-36882,-2571);
		gcall.Stepto(58552,-36996,-2540);
		gcall.NewSpend(1);
		Sleep(1000);
		gcall.DeliverQuests(zid,taskid,L"복진무");
		Sleep(1000);
		break;
	case 4:
		gcall.NewSpend(2.5);
		gcall.Stepto(58593,-36903,-2561,20,20,3000);
		gcall.Stepto(58602,-36898,-2563,20,20,3000);
		gcall.Stepto(58903,-36690,-2585);
		gcall.Stepto(59258,-36453,-2644);
		gcall.Stepto(59623,-36210,-2681);
		gcall.Stepto(59983,-35969,-2709);
		gcall.Stepto(60350,-35724,-2764);
		gcall.Stepto(60720,-35501,-2820);
		gcall.Stepto(61079,-35264,-2877);
		gcall.Stepto(61375,-34940,-2937);
		gcall.Stepto(61679,-34635,-2974);
		gcall.Stepto(62077,-34471,-2994);
		gcall.Stepto(62496,-34350,-2999);
		gcall.Stepto(62821,-34073,-2990);
		gcall.Stepto(62969,-33857,-2964);
		gcall.Stepto(63104,-33651,-2860);
		gcall.Stepto(63260,-33457,-2777);
		gcall.Stepto(63419,-33265,-2683);
		gcall.Stepto(63576,-33071,-2575);
		gcall.Stepto(63703,-32860,-2563);
		gcall.Stepto(63622,-32648,-2572);
		gcall.Stepto(63402,-32588,-2561);
		gcall.Stepto(63059,-32526,-2532);
		gcall.Stepto(62631,-32447,-2503);
		gcall.Stepto(62207,-32371,-2438);
		gcall.Stepto(61785,-32294,-2372);
		gcall.Stepto(61488,-32241,-2317);
		gcall.Stepto(61243,-32197,-2273);
		gcall.Stepto(61009,-32155,-2235);
		gcall.Stepto(60756,-32109,-2190);
		gcall.Stepto(60509,-32076,-2144);
		gcall.Stepto(60306,-32060,-2096);
		gcall.Stepto(59934,-32035,-2036);
		gcall.Stepto(59501,-32011,-1957);
		gcall.Stepto(59397,-32013,-1942);
		gcall.Stepto(59373,-32030,-1937);
		gcall.NewSpend(1);
		Sleep(1000);
		gcall.DeliverQuests(zid,taskid,L"서문범");
		Sleep(1000);
		gcall.Stepto(59370,-32030,-1937);
		gcall.Stepto(59241,-32227,-1917);
		gcall.Stepto(59122,-32444,-1914);
		gcall.Stepto(59011,-32666,-1898);
		gcall.Stepto(58910,-32892,-1881);
		gcall.Stepto(58846,-33109,-1850);
		Sleep(1000);
		gcall.FenJieByConfig();
		Sleep(1000);
		gcall.SellItemByConfig(L"마전표");
		Sleep(1000);
		gcall.SortBag();
		Sleep(1000);
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

void TaskScript::Task_319(int zid,int taskid)
{
	switch (taskid)
	{
	case 1:
		//突破觉醒 需要下回重新做。
		//gcall.XieBaoShi(0);
		//Sleep(1000);
		//gcall.XieBaoShi(1);
		//Sleep(1000);
		///*gcall.XieZhuangBei(EQUITMENT_POS::WUQI);
		//Sleep(1000);*/
		//_BAGSTU zhu;
		//while (true)
		//{
		//	ZeroMemory(&zhu,sizeof(_BAGSTU));
		//	gcall.GetGoodsByEquipPos(EQUITMENT_POS::WUQI, &zhu);
		//	
		//	if (zhu.name != NULL)
		//	{
		//		if(_wcsicmp(zhu.name,L"홍문도끼 10단계") == 0)
		//		{
		//			if (zhu.m_PingJi == 10 && 
		//				(zhu.m_DangQianJingYanZhi == zhu.m_DangQianJingYanZongZhi))
		//			{
		//				gcall.HeChengWuQi_Po10(EQUITMENT_POS::WUQI,L"요마도끼");
		//				Sleep(1000);
		//				gcall.WearEquipment(L"갓겅 요마도끼 1단계",EQUITMENT_POS::WUQI);
		//			}else
		//			{
		//				IsGoonHecheng(EQUITMENT_POS::WUQI);
		//			}
		//		}else if (_wcsicmp(zhu.name,L"갓겅 요마도끼 1단계") == 0)
		//		{
		//			TRACE("破10完毕");
		//			IsGoonHecheng(EQUITMENT_POS::WUQI);
		//			break;
		//		}else
		//		{
		//			gcall.WearEquipment(L"갓겅 요마도끼 1단계",EQUITMENT_POS::WUQI);
		//		}
		//	}
		//}
		//_BAGSTU goods;
		//if(GetGoodsFromBagByName(L"오각 자수정", &goods))
		//{
		//	gcall.JiaBaoShi(0,L"오각 자수정");
		//}else
		//{
		//	gcall.JiaBaoShi(0,L"거와의 삼각 자수정");
		//}
		//Sleep(1000);
		//gcall.JiaBaoShi(1,L"거와의 삼각 황옥");
		//Sleep(1000);
		//装备完

		gcall.NewSpend(2.5);
		gcall.Stepto(59433,-32016,-1946,20,20,3000);
		gcall.Stepto(59676,-31965,-1990,20,20,3000);
		gcall.Stepto(59922,-31944,-2037,20,20,3000);
		gcall.Stepto(60180,-31942,-2080);
		gcall.Stepto(60614,-31948,-2166);
		gcall.Stepto(61049,-31988,-2244);
		gcall.Stepto(61476,-32032,-2317);
		gcall.Stepto(61912,-32085,-2384);
		gcall.Stepto(62331,-32187,-2451);
		gcall.Stepto(62751,-32291,-2509);
		gcall.Stepto(63181,-32330,-2549);
		gcall.Stepto(63620,-32333,-2573);
		gcall.Stepto(64052,-32334,-2591);
		gcall.Stepto(64488,-32335,-2616);
		gcall.Stepto(64922,-32336,-2659);
		gcall.Stepto(65238,-32341,-2684);
		gcall.Stepto(65482,-32388,-2711);
		gcall.Stepto(65712,-32469,-2733);
		gcall.Stepto(65948,-32555,-2753);
		gcall.Stepto(66182,-32641,-2770);
		gcall.Stepto(66412,-32726,-2783);
		gcall.Stepto(66650,-32813,-2794);
		gcall.Stepto(66879,-32897,-2803);
		gcall.Stepto(67115,-32985,-2811);
		gcall.Stepto(67342,-33086,-2826);
		gcall.Stepto(67561,-33204,-2846);
		gcall.Stepto(67759,-33357,-2868);
		gcall.Stepto(67938,-33525,-2888);
		gcall.Stepto(68109,-33703,-2900);
		gcall.Stepto(68276,-33886,-2906);
		gcall.Stepto(68438,-34077,-2909);
		gcall.Stepto(68609,-34278,-2917);
		gcall.Stepto(68893,-34613,-2953);
		gcall.Stepto(69166,-34942,-3010);
		gcall.Stepto(69405,-35304,-3068);
		gcall.Stepto(69548,-35714,-3112);
		gcall.Stepto(69678,-36129,-3131);
		gcall.Stepto(69808,-36547,-3123);
		gcall.Stepto(69918,-36968,-3142);
		gcall.Stepto(69987,-37291,-3161);
		gcall.Stepto(70035,-37534,-3162);
		gcall.Stepto(70065,-37782,-3153);
		gcall.Stepto(70088,-38030,-3158);
		gcall.Stepto(70111,-38277,-3153);
		gcall.Stepto(70134,-38524,-3150);
		gcall.Stepto(70157,-38771,-3142);
		gcall.Stepto(70180,-39019,-3126);
		gcall.Stepto(70203,-39266,-3098);
		gcall.Stepto(70226,-39511,-3055);
		gcall.Stepto(70220,-39763,-3009);
		gcall.Stepto(70137,-39994,-2958);
		gcall.Stepto(69955,-40153,-2895);
		gcall.Stepto(69721,-40215,-2826);
		gcall.Stepto(69423,-40303,-2752);
		gcall.Stepto(69007,-40443,-2633);
		gcall.Stepto(68591,-40565,-2491);
		gcall.Stepto(68309,-40669,-2391);
		gcall.Stepto(68084,-40774,-2331);
		gcall.Stepto(67793,-40912,-2263);
		gcall.Stepto(67396,-41087,-2214);
		gcall.Stepto(67043,-41329,-2199);
		gcall.Stepto(66747,-41646,-2199);
		gcall.Stepto(66504,-42001,-2206);
		gcall.Stepto(66468,-42248,-2209);
		gcall.Stepto(66521,-42487,-2206);
		gcall.Stepto(66661,-42697,-2211);
		gcall.Stepto(66801,-42902,-2218);
		gcall.Stepto(66942,-43106,-2220);
		gcall.Stepto(67088,-43307,-2220);
		gcall.Stepto(67244,-43499,-2222);
		gcall.Stepto(67393,-43697,-2221);
		gcall.Stepto(67493,-43922,-2214);
		gcall.Stepto(67536,-44166,-2216);
		gcall.Stepto(67553,-44279,-2205);
		gcall.Stepto(67556,-44305,-2203);
		gcall.Stepto(67556,-44306,-2203);
		gcall.NewSpend(1);
		Sleep(1000);
		gcall.PickupSpecTypeTask(200,0x20,L"거암골 용맥");
		Sleep(10000);
		gcall.NewSpend(2.5);
		gcall.Stepto(71432,-50681,-1558);
		gcall.Stepto(71496,-50919,-1558);
		gcall.Stepto(71567,-51157,-1558);
		gcall.Stepto(71637,-51379,-1558);
		gcall.Stepto(71713,-51616,-1558);
		gcall.Stepto(71788,-51852,-1558);
		gcall.Stepto(71861,-52089,-1558);
		gcall.Stepto(71937,-52325,-1558);
		gcall.Stepto(72035,-52553,-1558);
		gcall.Stepto(72140,-52781,-1558);
		gcall.Stepto(72251,-53003,-1558);
		gcall.Stepto(72359,-53223,-1558);
		gcall.Stepto(72449,-53414,-1558);
		gcall.Stepto(72625,-53808,-1676);
		gcall.Stepto(72748,-54224,-1661);
		gcall.Stepto(72879,-54645,-1534);
		gcall.Stepto(73063,-55037,-1530);
		gcall.Stepto(73253,-55428,-1526);
		gcall.Stepto(73405,-55740,-1522);
		gcall.Stepto(73501,-55914,-1522);
		gcall.Stepto(73606,-56082,-1524);
		gcall.Stepto(73718,-56246,-1525);
		gcall.Stepto(73832,-56408,-1527);
		gcall.Stepto(73954,-56565,-1529);
		gcall.Stepto(74085,-56713,-1522);
		gcall.Stepto(74227,-56870,-1525);
		gcall.Stepto(74393,-57054,-1528);
		gcall.Stepto(74571,-57226,-1531);
		gcall.Stepto(74759,-57389,-1528);
		gcall.Stepto(74928,-57535,-1525);
		gcall.NewSpend(1);
		gcall.Stepto(75257,-57818,-1523);
		gcall.Stepto(75589,-58108,-1523);
		gcall.Stepto(75882,-58428,-1523);
		gcall.Stepto(76162,-58759,-1523);
		gcall.Stepto(76422,-59107,-1523);
		gcall.Stepto(76641,-59481,-1523);
		Sleep(2000);
		gcall.Stepto(76796,-59855,-1523);
		gcall.Stepto(76833,-59954,-1523);
		gcall.WaitPlans();
		gcall.Stepto(76903,-60138,-1523);
		gcall.Stepto(76997,-60383,-1523);
		gcall.Stepto(77146,-60796,-1418);
		gcall.NewSpend(2.5);
		gcall.Stepto(77293,-61202,-1276);
		gcall.Stepto(77473,-61601,-1143);
		gcall.Stepto(77665,-61986,-1146);
		gcall.Stepto(77794,-62404,-1118);
		gcall.Stepto(77808,-62716,-1092);
		gcall.Stepto(77794,-62915,-1076);
		gcall.Stepto(77765,-63111,-1063);
		gcall.Stepto(77701,-63299,-1052);
		gcall.Stepto(77608,-63475,-1028);
		gcall.Stepto(77493,-63665,-1027);
		gcall.Stepto(77362,-63842,-1028);
		gcall.Stepto(77238,-63969,-1030);
		gcall.Stepto(77100,-64111,-1033);
		gcall.Stepto(76964,-64260,-1042);
		gcall.Stepto(76843,-64417,-1038);
		gcall.Stepto(76721,-64592,-1038);
		gcall.Stepto(76581,-64797,-1037);
		gcall.Stepto(76440,-65001,-1036);
		gcall.Stepto(76307,-65203,-1035);
		gcall.Stepto(75996,-65502,-1043);
		gcall.Stepto(75573,-65604,-1043);
		gcall.Stepto(75148,-65660,-979);
		gcall.Stepto(74734,-65809,-840);
		gcall.Stepto(74337,-65975,-829);
		gcall.Stepto(74122,-65997,-829);
		gcall.Stepto(74161,-65782,-829);
		gcall.Stepto(74279,-65566,-829);
		gcall.Stepto(74217,-65362,-829);
		gcall.Stepto(74130,-65419,-808);
		gcall.Stepto(73902,-65509,-667);
		gcall.Stepto(73681,-65623,-526);
		gcall.Stepto(73457,-65733,-384);
		gcall.Stepto(73291,-65823,-329);
		gcall.Stepto(73193,-65826,-329);
		gcall.Stepto(73337,-66016,-329);
		gcall.Stepto(73434,-66250,-329);
		gcall.Stepto(73462,-66326,-329);
		gcall.Stepto(73243,-66429,-322);
		gcall.Stepto(73009,-66522,-313);
		gcall.Stepto(72788,-66453,-313);
		gcall.Stepto(72665,-66239,-313);
		gcall.Stepto(72496,-66065,-313);
		gcall.Stepto(72251,-66041,-293);
		gcall.Stepto(72066,-66103,-353);
		gcall.Stepto(71730,-66251,-500);
		gcall.Stepto(71328,-66243,-571);
		gcall.Stepto(71317,-66227,-571);
		gcall.Stepto(71220,-66050,-571);
		gcall.Stepto(71216,-66042,-571);
		gcall.Stepto(71146,-66041,-571);
		gcall.Stepto(70906,-66067,-575);
		gcall.Stepto(70811,-66089,-575);
		gcall.Stepto(70492,-66253,-575);
		gcall.Stepto(70079,-66386,-575);
		gcall.Stepto(69893,-66471,-575);
		gcall.Stepto(69764,-66564,-575);
		gcall.Stepto(69563,-66640,-575);
		gcall.Stepto(69267,-66760,-575);
		gcall.Stepto(68862,-66916,-575);
		gcall.Stepto(68612,-67031,-575);
		gcall.Stepto(68793,-66963,-575);
		gcall.Stepto(68862,-66938,-575);
		gcall.Stepto(68846,-66938,-575);
		gcall.Stepto(68620,-67025,-575);
		gcall.Stepto(68578,-67063,-575);
		gcall.Stepto(68650,-67040,-575);
		gcall.Stepto(69041,-66852,-575);
		gcall.Stepto(69441,-66667,-575);
		gcall.Stepto(69850,-66519,-575);
		gcall.Stepto(70263,-66380,-575);
		gcall.Stepto(70670,-66229,-575);
		gcall.Stepto(71084,-66125,-571);
		gcall.Stepto(71208,-66172,-571);
		gcall.Stepto(71427,-66115,-571);
		gcall.Stepto(71559,-66012,-571);
		gcall.Stepto(71733,-65911,-648);
		gcall.Stepto(71915,-65830,-782);
		gcall.Stepto(72098,-65754,-844);
		gcall.Stepto(72269,-65654,-944);
		gcall.Stepto(72500,-65574,-1043);
		gcall.Stepto(72791,-65572,-1133);
		gcall.Stepto(73055,-65896,-1391);
		gcall.Stepto(73099,-66026,-1456);
		gcall.Stepto(73099,-66085,-1497);
		gcall.Stepto(73097,-66138,-1508);
		gcall.Stepto(72783,-66341,-1496);
		gcall.Stepto(72406,-66556,-1488);
		gcall.Stepto(72029,-66771,-1488);
		gcall.Stepto(71617,-66919,-1488);
		gcall.Stepto(71186,-66976,-1488);
		gcall.Stepto(70755,-67004,-1488);
		gcall.Stepto(70321,-67045,-1488);
		gcall.Stepto(70035,-67148,-1604);
		gcall.Stepto(69805,-67252,-1739);
		gcall.Stepto(69581,-67358,-1871);
		gcall.Stepto(69367,-67480,-1952);
		gcall.Stepto(69212,-67667,-1952);
		gcall.Stepto(69269,-67870,-1952);
		gcall.Stepto(69077,-67978,-1952);
		gcall.Stepto(68832,-68009,-1952);
		gcall.Stepto(68614,-68107,-1952);
		gcall.Stepto(68433,-68195,-1952);
		gcall.Stepto(68250,-68272,-1952);
		gcall.Stepto(68062,-68336,-1952);
		gcall.Stepto(67872,-68393,-1952);
		gcall.Stepto(67708,-68287,-1952);
		gcall.Stepto(67572,-68192,-1952);
		gcall.Stepto(67814,-68096,-1968);
		gcall.Stepto(68028,-67990,-2069);
		gcall.Stepto(68328,-67837,-2211);
		gcall.Stepto(68506,-67749,-2295);
		gcall.Stepto(68690,-67674,-2379);
		gcall.Stepto(68883,-67615,-2464);
		gcall.Stepto(69077,-67579,-2546);
		gcall.Stepto(69277,-67570,-2571);
		gcall.Stepto(69523,-67625,-2571);
		gcall.Stepto(69765,-67680,-2571);
		gcall.Stepto(69954,-67774,-2571);
		gcall.Stepto(70006,-67629,-2571);
		gcall.Stepto(70074,-67462,-2571);
		gcall.NewSpend(1);
		Sleep(1000);
		gcall.DeliverQuests(zid,taskid,L"고봉");
		Sleep(2000);
		break;
	case 2:
		gcall.NewSpend(2.5);
		gcall.Stepto(70110,-67424,-2571);
		gcall.Stepto(70063,-67515,-2571);
		gcall.Stepto(69933,-67682,-2571);
		gcall.Stepto(69879,-67852,-2571);
		gcall.Stepto(69712,-67972,-2571);
		gcall.Stepto(69498,-68097,-2571);
		gcall.Stepto(69280,-68216,-2571);
		gcall.Stepto(69064,-68337,-2571);
		gcall.Stepto(68860,-68479,-2571);
		gcall.NewSpend(1);
		gcall.Stepto(68733,-68683,-2571);
		gcall.Stepto(68786,-68923,-2571);
		gcall.Stepto(68870,-69125,-2609);
		gcall.Stepto(68970,-69368,-2657);
		Sleep(2000);
		gcall.Stepto(69009,-69466,-2670);
		
		gcall.Stepto(69011,-69495,-2670);
		gcall.WaitPlans();
		gcall.Stepto(69061,-69737,-2670);
		gcall.Stepto(69111,-69980,-2670);
		gcall.NewSpend(2.5);
		gcall.Stepto(69106,-70015,-2670);
		gcall.Stepto(69077,-69956,-2670);
		gcall.Stepto(69082,-69828,-2670);
		gcall.Stepto(69297,-69707,-2670);
		gcall.Stepto(69524,-69608,-2775);
		gcall.Stepto(69753,-69512,-2903);
		gcall.Stepto(69993,-69191,-3053);
		gcall.Stepto(69024,-69764,-3137);
		gcall.NewSpend(1);
		gcall.Stepto(69024,-69764,-3137);
		Sleep(5000);
		break;
	case 3:
		gcall.NewSpend(2.5);
		gcall.Stepto(71572,-51161,-1558);
		gcall.Stepto(71975,-52233,-1558);
		gcall.Stepto(72313,-53140,-1558);
		gcall.Stepto(72749,-54152,-1677);
		gcall.Stepto(73061,-54967,-1530);
		gcall.Stepto(73609,-56044,-1524);
		gcall.Stepto(74055,-56744,-1522);
		gcall.Stepto(74817,-57387,-1527);
		gcall.Stepto(75460,-57981,-1523);
		gcall.Stepto(76127,-58686,-1523);
		gcall.Stepto(76546,-59365,-1523);
		gcall.Stepto(76681,-59633,-1523);
		gcall.NewSpend(1);
		gcall.Stepto(76908,-60068,-1523);
		gcall.NewSpend(2.5);
		gcall.Stepto(77066,-60429,-1523);
		gcall.Stepto(77308,-61151,-1289);
		gcall.Stepto(77675,-61836,-1144);
		gcall.Stepto(77818,-62553,-1104);
		gcall.Stepto(77688,-63249,-1057);
		gcall.Stepto(77433,-63721,-1027);
		gcall.Stepto(77097,-63964,-1033);
		gcall.Stepto(76500,-64156,-1066);
		gcall.Stepto(75880,-65245,-1543);
		gcall.Stepto(75677,-65594,-1543);
		gcall.Stepto(74544,-65977,-1543);
		gcall.Stepto(73442,-66342,-1509);
		gcall.Stepto(72299,-66643,-1488);
		gcall.Stepto(70877,-67047,-1488);
		gcall.Stepto(70348,-67063,-1488);
		gcall.Stepto(69206,-67548,-1952);
		gcall.Stepto(68841,-68127,-1952);
		gcall.Stepto(67676,-68618,-1952);
		gcall.Stepto(67596,-68150,-1952);
		gcall.Stepto(68361,-67741,-2240);
		gcall.Stepto(69483,-67425,-2571);
		gcall.Stepto(69693,-68028,-2571);
		gcall.Stepto(68506,-68337,-2571);
		gcall.Stepto(68873,-69135,-2611);
		gcall.Stepto(68964,-69802,-2670);
		gcall.Stepto(69390,-69643,-2704);
		gcall.Stepto(70151,-69323,-3052);
		gcall.Stepto(70022,-69045,-3052);
		gcall.NewSpend(1);
		gcall.Stepto(69484,-69313,-3136);
		gcall.Stepto(68927,-69958,-3137);
		Sleep(1000);
		gcall.sendcall(id_msg_attack, (LPVOID)0x5DE8);//z
		gcall.Kill_Tab();
		gcall.Kill_Tab();
		gcall.TurnToNear(500);
		Sleep(300);
		gcall.sendcall(id_msg_attack, (LPVOID)0x5e74);//1
		Sleep(500);
		gcall.Kill_Tab();
		gcall.TurnToNear(500);
		Sleep(300);
		gcall.sendcall(id_msg_attack, (LPVOID)0x5DF2);//2
		gcall.FindThenKill(0,300,modeAoe | modeNormal | modePickup);
		Sleep(2000);
		break;
	case 4:
		gcall.Stepto(69008,-70114,-3137);
		Sleep(1000);
		gcall.DeliverQuests(zid,taskid,L"남소유");
		Sleep(7000);
		break;
	case 5:
		gcall.NewSpend(2.5);
		gcall.Stepto(69122,-69885,-3137);
		gcall.Stepto(69219,-69863,-3137);
		gcall.Stepto(69461,-69810,-3137);
		gcall.Stepto(69702,-69756,-3137);
		gcall.Stepto(69946,-69711,-3096);
		gcall.Stepto(70160,-69588,-3052);
		gcall.Stepto(70220,-69385,-3052);
		gcall.Stepto(69996,-69408,-3039);
		gcall.Stepto(69770,-69510,-2911);
		gcall.Stepto(69536,-69605,-2781);
		gcall.Stepto(69310,-69706,-2670);
		gcall.Stepto(69151,-69862,-2670);
		gcall.Stepto(69151,-69863,-2670);
		gcall.Stepto(69119,-69832,-2670);
		gcall.Stepto(69001,-69619,-2670);
		gcall.Stepto(68953,-69401,-2662);
		gcall.Stepto(68947,-69365,-2655);
		gcall.Stepto(68908,-69189,-2623);
		gcall.Stepto(68755,-68806,-2571);
		gcall.Stepto(68661,-68570,-2571);
		gcall.Stepto(68943,-68354,-2571);
		gcall.Stepto(69322,-68142,-2571);
		gcall.Stepto(69684,-67911,-2571);
		gcall.Stepto(69935,-67682,-2571);
		gcall.Stepto(70010,-67584,-2571);
		gcall.Stepto(70038,-67543,-2571);
		gcall.NewSpend(1);
		gcall.Stepto(70091,-67438,-2571);
		gcall.Stepto(70092,-67438,-2571);
		Sleep(1000);
		gcall.DeliverQuests(zid,taskid,L"고봉");
		Sleep(5000);
		gcall.FindThenKill(0,300,modeAoe | modeNormal | modePickup);
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

void TaskScript::Task_320(int zid,int taskid)
{
	switch (taskid)
	{
	case 1:
		gcall.CityConvey(1);
		gcall.NewSpend(2.5);
		gcall.Stepto(-48892,-49408,-2383,20,20,3000);
		gcall.Stepto(-48909,-49420,-2381);
		gcall.Stepto(-48942,-49442,-2382);
		gcall.Stepto(-49021,-49576,-2382);
		gcall.Stepto(-49092,-49738,-2384);
		gcall.Stepto(-49225,-50098,-2340);
		gcall.Stepto(-49352,-50510,-2317);
		gcall.Stepto(-49453,-50849,-2383);
		gcall.Stepto(-49602,-51003,-2377);
		gcall.Stepto(-49804,-51054,-2382);
		gcall.Stepto(-50171,-51139,-2381);
		gcall.Stepto(-50593,-51244,-2388);
		gcall.Stepto(-51017,-51349,-2387);
		gcall.Stepto(-51440,-51446,-2400);
		gcall.Stepto(-51853,-51578,-2531);
		gcall.Stepto(-52104,-51622,-2596);
		gcall.Stepto(-52118,-51654,-2605);
		gcall.Stepto(-52186,-52028,-2657);
		gcall.Stepto(-52216,-52460,-2681);
		gcall.Stepto(-52197,-52895,-2751);
		gcall.Stepto(-52166,-53322,-2895);
		gcall.Stepto(-52151,-53519,-2962);
		gcall.Stepto(-52144,-53839,-3021);
		gcall.Stepto(-52136,-54178,-3045);
		gcall.Stepto(-52106,-54374,-3049);
		gcall.Stepto(-51923,-54452,-3050);
		gcall.Stepto(-51695,-54546,-3055);
		gcall.Stepto(-51488,-54631,-3052);
		gcall.Stepto(-51391,-54585,-3046);
		gcall.Stepto(-51174,-54466,-3033);
		gcall.Stepto(-50970,-54348,-3012);
		gcall.Stepto(-50977,-54370,-3023);
		gcall.Stepto(-50972,-54352,-3012);
		gcall.Stepto(-50941,-54332,-3012);
		gcall.NewSpend(1);
		gcall.Stepto(-50764,-54220,-3012);
		Sleep(2000);
		break;
	case 2:
		gcall.DeliverQuests(zid,taskid,L"곽대규");
		Sleep(2000);
		break;
	case 3:
		gcall.Stepto(-50865,-54298,-3012);
		gcall.Stepto(-51098,-54774,-3422);
		gcall.Stepto(-51201,-54492,-3040);
		gcall.Stepto(-51264,-54644,-3050);
		gcall.Stepto(-51120,-54451,-3033);
		Sleep(2000);
		gcall.Stepto(-51461,-54695,-3055);
		Sleep(1000);
		gcall.DeliverQuests(zid,taskid,L"장호엄");
		Sleep(1000);
		break;
	case 4:
		gcall.NewSpend(2.5);
		gcall.Stepto(-51681,-54575,-3055);
		gcall.Stepto(-51852,-54574,-3053);
		gcall.Stepto(-52074,-54676,-3046);
		gcall.Stepto(-52226,-54871,-3042);
		gcall.Stepto(-52299,-55105,-3053);
		gcall.Stepto(-52333,-55350,-3070);
		gcall.Stepto(-52351,-55597,-3140);
		gcall.Stepto(-52349,-55847,-3138);
		gcall.Stepto(-52328,-56094,-3134);
		gcall.Stepto(-52307,-56339,-3136);
		gcall.Stepto(-52286,-56587,-3158);
		gcall.Stepto(-52271,-56834,-3199);
		gcall.Stepto(-52292,-57078,-3218);
		gcall.Stepto(-52339,-57509,-3227);
		gcall.NewSpend(1);
		gcall.randXianlu(0);
		Sleep(1000);
		gcall.NewSpend(2.5);
		gcall.Stepto(-52395,-57794,-3236);
		gcall.Stepto(-52446,-58039,-3256);
		gcall.Stepto(-52497,-58283,-3264);
		gcall.Stepto(-52569,-58504,-3268);
		gcall.Stepto(-52673,-58729,-3268);
		gcall.Stepto(-52801,-58941,-3253);
		gcall.Stepto(-52948,-59141,-3254);
		gcall.Stepto(-53094,-59342,-3263);
		gcall.Stepto(-53239,-59543,-3273);
		gcall.Stepto(-53362,-59759,-3289);
		gcall.Stepto(-53481,-59976,-3293);
		gcall.Stepto(-53583,-60202,-3300);
		gcall.Stepto(-53677,-60435,-3319);
		gcall.Stepto(-53692,-60472,-3321);
		gcall.NewSpend(1);
		gcall.Stepto(-53633,-59601,-3266);
		Sleep(500);
		gcall.FindThenKill(0,300,modeAoe | modePickup);
		//gcall.sendcall(id_msg_attack, (LPVOID)0x5DFC);//v
		gcall.Stepto(-53648,-59596,-3266);
		gcall.Stepto(-53882,-59514,-3288);
		gcall.Stepto(-54117,-59433,-3265);
		gcall.Stepto(-54357,-59376,-3275);
		gcall.Stepto(-54604,-59390,-3303);
		gcall.Stepto(-54815,-59434,-3299);
		gcall.Stepto(-54907,-59454,-3302);
		Sleep(500);
		gcall.FindThenKill(0,300,modeAoe | modePickup);
		//gcall.sendcall(id_msg_attack, (LPVOID)0x5DFC);//v
		gcall.Stepto(-54982,-59549,-3309);
		gcall.Stepto(-54939,-59793,-3316);
		gcall.Stepto(-54887,-60036,-3326);
		gcall.Stepto(-54864,-60143,-3326);
		Sleep(500);
		gcall.FindThenKill(0,300,modeAoe | modePickup);
		//gcall.sendcall(id_msg_attack, (LPVOID)0x5DFC);//v
		gcall.Stepto(-54827,-60209,-3328);
		gcall.Stepto(-54604,-60319,-3328);
		gcall.Stepto(-54380,-60428,-3325);
		gcall.Stepto(-54164,-60542,-3323);
		gcall.Stepto(-54111,-60570,-3323);
		Sleep(500);
		gcall.FindThenKill(0,300,modeAoe | modePickup);
		gcall.sendcall(id_msg_attack, (LPVOID)0x5DFC);//v
		gcall.Stepto(-53949,-60687,-3327);
		gcall.Stepto(-53714,-60768,-3330);
		gcall.Stepto(-53478,-60841,-3331);
		gcall.Stepto(-53253,-60901,-3331);
		gcall.Stepto(-53252,-60901,-3331);
		Sleep(500);
		gcall.FindThenKill(0,300,modeNormal | modeAoe | modePickup);
		//gcall.sendcall(id_msg_attack, (LPVOID)0x5DFC);//v
		gcall.NewSpend(2.5);
		gcall.Stepto(-53090,-60915,-3327);
		gcall.Stepto(-52844,-60949,-3330);
		gcall.Stepto(-52690,-60971,-3329);
		gcall.Stepto(-52670,-60974,-3329);
		gcall.Stepto(-52576,-60987,-3329);
		gcall.Stepto(-52333,-61022,-3330);
		gcall.Stepto(-52221,-61041,-3331);
		gcall.Stepto(-51974,-61072,-3342);
		gcall.Stepto(-51727,-61087,-3331);
		gcall.Stepto(-51480,-61105,-3328);
		gcall.Stepto(-51240,-61123,-3323);
		gcall.Stepto(-51238,-61123,-3324);
		gcall.NewSpend(1);
		Sleep(500);
		gcall.FindThenKill(0,300,modeNormal | modeAoe | modePickup);
		//gcall.sendcall(id_msg_attack, (LPVOID)0x5DFC);//v
		gcall.Stepto(-51245,-61061,-3318);
		gcall.Stepto(-51047,-61067,-3326);
		gcall.Stepto(-50819,-61063,-3313);
		gcall.Stepto(-50583,-60993,-3314);
		gcall.Stepto(-50371,-60864,-3313);
		gcall.Stepto(-50345,-60847,-3312);
		Sleep(500);
		gcall.FindThenKill(0,300,modeNormal | modeAoe | modePickup);
		//gcall.sendcall(id_msg_attack, (LPVOID)0x5DFC);//v
		gcall.Stepto(-50222,-60814,-3310);
		gcall.Stepto(-50025,-60663,-3301);
		gcall.Stepto(-49861,-60477,-3299);
		gcall.Stepto(-49832,-60444,-3300);
		Sleep(500);
		gcall.FindThenKill(0,300,modeNormal | modeAoe | modePickup);
		//gcall.sendcall(id_msg_attack, (LPVOID)0x5DFC);//v
		gcall.Stepto(-49910,-60449,-3299);
		gcall.Stepto(-49781,-60300,-3302);
		gcall.Stepto(-49657,-60145,-3300);
		gcall.Stepto(-49558,-59971,-3279);
		gcall.Stepto(-49479,-59823,-3253);
		Sleep(1000);
		gcall.FindThenKill(0,300,modeNormal | modeAoe | modePickup);
		//gcall.sendcall(id_msg_attack, (LPVOID)0x5DFC);//v
		gcall.Stepto(-49509,-59697,-3227);
		gcall.Stepto(-49661,-59568,-3211);
		gcall.Stepto(-49831,-59463,-3224);
		gcall.Stepto(-50003,-59364,-3234);
		gcall.Stepto(-50174,-59267,-3242);
		gcall.Stepto(-50376,-59150,-3251);
		gcall.Stepto(-50590,-59024,-3252);
		gcall.Stepto(-50726,-58943,-3248);
		Sleep(1000);
		gcall.FindThenKill(0,300,modeNormal | modeAoe | modePickup);
		//gcall.sendcall(id_msg_attack, (LPVOID)0x5DFC);//v
		gcall.Stepto(-50764,-58920,-3247);
		gcall.Stepto(-50896,-58855,-3249);
		gcall.Stepto(-51071,-58759,-3250);
		gcall.Stepto(-51241,-58658,-3259);
		gcall.Stepto(-51412,-58555,-3264);
		gcall.Stepto(-51480,-58515,-3264);
		Sleep(1000);
		gcall.FindThenKill(0,300,modeNormal | modeAoe | modePickup);
		gcall.sendcall(id_msg_attack, (LPVOID)0x5DFC);//v
		gcall.Stepto(-51535,-58576,-3267);
		gcall.Stepto(-51721,-58747,-3274);
		gcall.Stepto(-51918,-58892,-3274);
		gcall.Stepto(-52129,-59028,-3265);
		gcall.Stepto(-52323,-59164,-3264);
		gcall.Stepto(-52325,-59165,-3264);
		Sleep(1000);
		gcall.FindThenKill(0,300,modeNormal | modeAoe | modePickup,4);
		gcall.sendcall(id_msg_attack, (LPVOID)0x5DFC);//v
		break;
	case 5:
		gcall.NewSpend(2.5);
		gcall.Stepto(-51873,-60742,-3321);
		gcall.Stepto(-51856,-60520,-3307);
		gcall.Stepto(-51815,-60343,-3299);
		gcall.Stepto(-51749,-59922,-3292);
		gcall.Stepto(-51669,-59492,-3293);
		gcall.Stepto(-51563,-59072,-3292);
		gcall.Stepto(-51443,-58659,-3269);
		gcall.Stepto(-51332,-58233,-3245);
		gcall.Stepto(-51205,-57818,-3216);
		gcall.Stepto(-51170,-57715,-3212);
		gcall.Stepto(-51000,-57317,-3161);
		gcall.Stepto(-50945,-57191,-3151);
		gcall.Stepto(-51072,-57012,-3143);
		gcall.Stepto(-51278,-56883,-3137);
		gcall.Stepto(-51634,-56641,-3141);
		gcall.Stepto(-51994,-56390,-3138);
		gcall.Stepto(-52239,-56209,-3137);
		gcall.Stepto(-52269,-55942,-3138);
		gcall.Stepto(-52305,-55510,-3103);
		gcall.Stepto(-52313,-55151,-3055);
		gcall.Stepto(-52276,-54910,-3043);
		gcall.Stepto(-52106,-54749,-3042);
		gcall.Stepto(-51866,-54649,-3053);
		gcall.Stepto(-51623,-54612,-3052);
		gcall.Stepto(-51506,-54673,-3056);
		gcall.NewSpend(1);
		Sleep(1000);
		gcall.DeliverQuests(zid,6,L"장호엄");
		Sleep(1000);
		break;
	case 6:
		gcall.NewSpend(2.5);
		gcall.Stepto(-51621,-54610,-3052);
		gcall.Stepto(-51839,-54491,-3052);
		gcall.Stepto(-52014,-54322,-3047);
		gcall.Stepto(-52090,-54089,-3042);
		gcall.Stepto(-52131,-53819,-3019);
		gcall.Stepto(-52187,-53385,-2917);
		gcall.Stepto(-52223,-52954,-2776);
		gcall.Stepto(-52258,-52528,-2686);
		gcall.Stepto(-52281,-52191,-2677);
		gcall.Stepto(-52281,-51991,-2681);
		gcall.Stepto(-52271,-51798,-2675);
		gcall.Stepto(-52325,-51612,-2701);
		gcall.Stepto(-52276,-51561,-2674);
		gcall.Stepto(-52057,-51531,-2565);
		gcall.Stepto(-51817,-51469,-2498);
		gcall.Stepto(-51579,-51397,-2413);
		gcall.Stepto(-51363,-51326,-2396);
		gcall.Stepto(-50966,-51148,-2387);
		gcall.Stepto(-50707,-50927,-2382);
		gcall.Stepto(-50474,-50934,-2380);
		gcall.Stepto(-50293,-50941,-2382);
		gcall.Stepto(-50335,-50851,-2376);
		gcall.Stepto(-50399,-50664,-2375);
		gcall.Stepto(-50528,-50250,-2375);
		gcall.Stepto(-50650,-49833,-2356);
		gcall.Stepto(-50672,-49757,-2353);
		gcall.Stepto(-50721,-49751,-2347);
		gcall.Stepto(-50950,-49682,-2314);
		gcall.Stepto(-51192,-49638,-2260);
		gcall.Stepto(-51439,-49618,-2131);
		gcall.Stepto(-51456,-49617,-2122);
		gcall.NewSpend(1);
		gcall.Stepto(-51559,-49617,-2106);
		gcall.Stepto(-51597,-49597,-2106);
		gcall.Stepto(-51606,-49589,-2106);

		gcall.WaitPlans();
		gcall.DeliverQuests(zid,7,L"용숙");
		Sleep(1000);
		break;
	case 7:
		gcall.Stepto(-51608,-49552,-2106);
		gcall.Stepto(-51625,-49303,-2111);
		gcall.Stepto(-51631,-49243,-2137);
		gcall.Stepto(-51631,-49238,-2139);
		gcall.Stepto(-51633,-49223,-2146);
		gcall.Kill_Tab();
		gcall.Kill_Tab();
		gcall.Stepto(-51643,-49156,-2182);
		gcall.Stepto(-51666,-49006,-2216);
		gcall.Stepto(-51768,-48948,-2216);
		gcall.Stepto(-51806,-48918,-2216);
		gcall.Stepto(-51822,-48905,-2216);
		Sleep(2000);
		gcall.Kill_Tab();
		gcall.Kill_Tab();
		gcall.FindThenKill(0,500,modeAoe | modeNormal | modePickup);
		Sleep(1000);
		gcall.PickupTask();
		Sleep(1000);
		gcall.Stepto(-51817,-48908,-2216);
		gcall.Stepto(-51676,-49028,-2216);
		gcall.Stepto(-51630,-49201,-2156);
		gcall.Stepto(-51603,-49425,-2106);
		Sleep(1000);
		gcall.DeliverQuests(zid,8,L"용숙");
		Sleep(2000);
		break;
	case 8:
		gcall.NewSpend(2.5);
		gcall.Stepto(-51431,-49483,-2142);
		gcall.Stepto(-51385,-49497,-2165);
		gcall.Stepto(-51145,-49558,-2282);
		gcall.Stepto(-51102,-49566,-2289);
		gcall.Stepto(-50942,-49578,-2317);
		gcall.Stepto(-50696,-49608,-2350);
		gcall.Stepto(-50450,-49637,-2369);
		gcall.Stepto(-50340,-49649,-2372);
		gcall.NewSpend(1);
		gcall.Stepto(-50329,-49650,-2372);
		Sleep(1000);
		gcall.DeliverQuests(zid,9,L"고봉");
		Sleep(1000);
		break;
	case 9:
		gcall.NewSpend(2.5);
		gcall.Stepto(-50334,-49782,-2376);
		gcall.Stepto(-50341,-50029,-2375);
		gcall.Stepto(-50347,-50276,-2375);
		gcall.Stepto(-50327,-50526,-2375);
		gcall.Stepto(-50223,-50750,-2376);
		gcall.Stepto(-50233,-50823,-2376);
		gcall.Stepto(-50454,-50933,-2379);
		gcall.Stepto(-50678,-51036,-2386);
		gcall.Stepto(-50910,-51144,-2387);
		gcall.Stepto(-51281,-51325,-2393);
		gcall.Stepto(-51682,-51540,-2452);
		gcall.Stepto(-52099,-51654,-2597);
		gcall.Stepto(-52534,-51625,-2683);
		gcall.Stepto(-52964,-51572,-2678);
		gcall.Stepto(-53396,-51535,-2695);
		gcall.Stepto(-53823,-51608,-2692);
		gcall.Stepto(-54251,-51682,-2700);
		gcall.Stepto(-54675,-51615,-2699);
		gcall.Stepto(-54973,-51310,-2707);
		gcall.Stepto(-55111,-50899,-2703);
		gcall.Stepto(-55117,-50579,-2693);
		gcall.Stepto(-55230,-50383,-2667);
		gcall.Stepto(-55467,-50311,-2598);
		gcall.Stepto(-55707,-50248,-2576);
		gcall.Stepto(-55769,-50233,-2576);
		gcall.Stepto(-55889,-50202,-2539);
		gcall.Stepto(-56092,-50148,-2539);
		gcall.Stepto(-56097,-49909,-2539);
		gcall.Stepto(-56098,-49861,-2539);
		gcall.NewSpend(1);
		Sleep(1000);
		gcall.DeliverQuests(zid,0xB,L"도천풍");
		Sleep(1000);
		break;
	case 10:
		Sleep(1000);
		break;
	case 11:
		gcall.NewSpend(2.5);
		gcall.Stepto(-56100,-49984,-2539);
		gcall.Stepto(-56098,-50103,-2539);
		gcall.Stepto(-55869,-50181,-2539);
		gcall.Stepto(-55678,-50247,-2576);
		gcall.Stepto(-55628,-50264,-2576);
		gcall.Stepto(-55395,-50335,-2635);
		gcall.Stepto(-55331,-50349,-2648);
		gcall.Stepto(-55331,-50357,-2648);
		gcall.Stepto(-55300,-50691,-2681);
		gcall.Stepto(-55098,-51076,-2706);
		gcall.Stepto(-54838,-51424,-2705);
		gcall.Stepto(-54487,-51674,-2698);
		gcall.Stepto(-54066,-51782,-2696);
		gcall.Stepto(-53640,-51709,-2691);
		gcall.Stepto(-53237,-51551,-2719);
		gcall.Stepto(-52805,-51563,-2670);
		gcall.Stepto(-52377,-51648,-2716);
		gcall.Stepto(-52181,-51995,-2655);
		gcall.Stepto(-52213,-52430,-2678);
		gcall.Stepto(-52192,-52855,-2734);
		gcall.Stepto(-52167,-53144,-2835);
		gcall.Stepto(-52145,-53390,-2918);
		gcall.Stepto(-52133,-53641,-2994);
		gcall.Stepto(-52132,-53887,-3028);
		gcall.Stepto(-52116,-54135,-3044);
		gcall.Stepto(-51990,-54345,-3047);
		gcall.Stepto(-51802,-54510,-3052);
		gcall.Stepto(-51583,-54620,-3052);
		gcall.Stepto(-51348,-54704,-3052);
		gcall.Stepto(-51110,-54779,-3051);
		gcall.Stepto(-50874,-54845,-3047);
		gcall.Stepto(-50682,-54843,-3037);
		gcall.Stepto(-50276,-54788,-3001);
		gcall.Stepto(-49841,-54725,-2885);
		gcall.Stepto(-49439,-54822,-2697);
		gcall.Stepto(-49368,-55038,-2593);
		gcall.Stepto(-49332,-55399,-2504);
		gcall.Stepto(-49263,-55588,-2479);
		gcall.Stepto(-49223,-55637,-2477);
		gcall.Stepto(-49082,-55572,-2469);
		gcall.Stepto(-48925,-55467,-2458);
		gcall.Stepto(-48607,-55253,-2390);
		gcall.Stepto(-48409,-55200,-2294);
		gcall.Stepto(-48165,-55225,-2148);
		gcall.Stepto(-47955,-55352,-2024);
		gcall.Stepto(-47848,-55573,-1920);
		gcall.Stepto(-47765,-55807,-1838);
		gcall.Stepto(-47692,-56001,-1805);
		gcall.Stepto(-49256,-59386,-3186);
		gcall.NewSpend(1);
		gcall.Stepto(-46456,-56068,-1808,20,20,3000);
		Sleep(2000);
		break;
	case 12:
		Sleep(1000);
		gcall.Stepto(-46352,-56159,-1808);
		gcall.sendcall(id_msg_attack, (LPVOID)0x5DE8);//z
		Sleep(600);
		gcall.sendcall(id_msg_attack, (LPVOID)0x5E06);//3
		gcall.Kill_Tab();
		gcall.TurnToNear(300);
		gcall.sendcall(id_msg_attack, (LPVOID)0x5e74);//1
		gcall.Kill_Tab();
		gcall.TurnToNear(300);
		gcall.sendcall(id_msg_attack, (LPVOID)0x5DF2);//2
		gcall.FindThenKill(0,500,modeNormal | modeAoe | modePickup,0xc);
		Sleep(2000);
		break;
	case 13:
		gcall.WaitPlans();
		Sleep(1000);
		gcall.Stepto(-56106,-50070,-2539);
		gcall.Stepto(-56078,-50090,-2539);
		gcall.Stepto(-55857,-50201,-2539);
		gcall.Stepto(-55832,-50213,-2539);
		gcall.Stepto(-55760,-50336,-2576);
		Sleep(1000);
		gcall.DeliverQuests(zid,0xE,L"고봉");
		Sleep(3000);
		break;
	}
}

void TaskScript::Task_501(int zid,int taskid)
{
	switch (taskid)
	{
	case 1:
		gcall.NewSpend(2.5);
		gcall.Stepto(-55767,-50336,-2576);
		gcall.Stepto(-55754,-50244,-2576);
		gcall.Stepto(-55753,-50240,-2576);
		gcall.Stepto(-55678,-50262,-2576);
		gcall.Stepto(-55614,-50281,-2576);
		gcall.Stepto(-55546,-50301,-2576);
		gcall.Stepto(-55538,-50300,-2576);
		gcall.Stepto(-55286,-50263,-2652);
		gcall.Stepto(-55039,-50217,-2681);
		gcall.Stepto(-54795,-50173,-2684);
		gcall.Stepto(-54593,-50146,-2667);
		gcall.NewSpend(1);
		Sleep(1000);
		gcall.DeliverQuests(zid,taskid,L"안두매");
		Sleep(1000);
		break;
	case 2:
		gcall.Stepto(-54541,-50089,-2670);
		gcall.Stepto(-54773,-50172,-2682);
		gcall.Stepto(-54960,-50332,-2689);
		gcall.Stepto(-55078,-50548,-2694);
		gcall.Stepto(-55201,-50762,-2695);
		gcall.Stepto(-55347,-50962,-2687);
		gcall.Stepto(-55456,-51098,-2675);
		Sleep(1000);
		gcall.DeliverQuests(zid,taskid,L"오백언");
		Sleep(1000);
		gcall.Stepto(-55317,-51208,-2687);
		gcall.Stepto(-55148,-51389,-2697);
		gcall.Stepto(-54990,-51584,-2696);
		gcall.Stepto(-54842,-51780,-2671);
		gcall.Stepto(-54782,-51863,-2664);
		Sleep(1000);
		gcall.DeliverQuests(zid,3,L"한미백");
		Sleep(1000);
		gcall.Stepto(-54747,-51843,-2669);
		gcall.Stepto(-54539,-51757,-2691);
		gcall.Stepto(-54390,-51584,-2701);
		gcall.Stepto(-54265,-51401,-2673);
		Sleep(1000);
		gcall.DeliverQuests(zid,4,L"관철수");
		Sleep(1000);
		break;
	case 3:
		gcall.NewSpend(2.5);
		gcall.Stepto(-54447,-51457,-2693);
		gcall.Stepto(-54688,-51411,-2699);
		gcall.Stepto(-54902,-51288,-2705);
		gcall.Stepto(-55014,-51085,-2705);
		gcall.Stepto(-55014,-51083,-2705);
		gcall.Stepto(-55027,-50888,-2702);
		gcall.Stepto(-54987,-50644,-2692);
		gcall.Stepto(-54910,-50409,-2688);
		gcall.Stepto(-54787,-50195,-2683);
		gcall.Stepto(-54762,-50164,-2682);
		gcall.Stepto(-54623,-50012,-2683);
		gcall.Stepto(-54504,-49911,-2684);
		gcall.Stepto(-54505,-49913,-2684);
		gcall.Stepto(-54519,-50097,-2669);
		gcall.NewSpend(1);
		Sleep(1000);
		gcall.DeliverQuests(zid,5,L"안두매");
		gcall.WaitPlans();
		gcall.Stepto(-62440,-43804,-1741);
		break;
	case 4:
		gcall.Stepto(-62573,-43786,-1741);
		Sleep(1000);
		gcall.DeliverQuests(zid,6,L"백무");
		Sleep(1000);
		break;
	case 5:
		gcall.NewSpend(2.5);
		gcall.Stepto(-62457,-43889,-1741);
		gcall.Stepto(-62383,-44036,-1741);
		gcall.Stepto(-62381,-44219,-1769);
		gcall.WaitPlans();
		gcall.Stepto(-62381,-44245,-1773);
		gcall.Stepto(-62466,-44423,-1790);
		gcall.Stepto(-62553,-44653,-1812);
		gcall.Stepto(-62635,-44888,-1873);
		gcall.Stepto(-62717,-45124,-1923);
		gcall.Stepto(-62792,-45358,-1934);
		gcall.Stepto(-62847,-45603,-1944);
		gcall.Stepto(-62878,-45827,-1954);
		gcall.Stepto(-62827,-45853,-1954);
		gcall.Stepto(-62730,-45980,-1957);
		gcall.Stepto(-62726,-46052,-1959);
		gcall.NewSpend(1);
		Sleep(1000);
		gcall.FindThenKill(0,1000,modeAoe | modeNormal | modePickup,5);
		Sleep(2000);
		break;
	case 6:
		gcall.NewSpend(2.5);
		gcall.Stepto(-62754,-46094,-1961);
		gcall.Stepto(-62731,-45951,-1956);
		gcall.Stepto(-62694,-45706,-1945);
		gcall.Stepto(-62657,-45460,-1934);
		gcall.Stepto(-62621,-45215,-1924);
		gcall.Stepto(-62584,-44971,-1892);
		gcall.Stepto(-62545,-44724,-1819);
		gcall.Stepto(-62478,-44486,-1793);
		gcall.Stepto(-62411,-44255,-1775);
		gcall.Stepto(-62385,-44002,-1741);
		gcall.Stepto(-62389,-43874,-1741);
		gcall.Stepto(-62417,-43713,-1741);
		gcall.WaitPlans();
		gcall.Stepto(-62438,-43725,-1741);
		gcall.Stepto(-62590,-43822,-1741);
		gcall.Stepto(-62600,-43828,-1741);
		gcall.NewSpend(1);
		Sleep(1000);
		gcall.PickupSpecTypeTask(200,0x4,L"한시랑");
		Sleep(1000);
		break;
	case 7:
		gcall.NewSpend(2.5);
		gcall.Stepto(-62403,-43820,-1741);
		gcall.Stepto(-62359,-44214,-1769);
		gcall.WaitPlans();
		gcall.Stepto(-62521,-44708,-1810);
		gcall.Stepto(-62732,-45493,-1937);
		gcall.NewSpend(1);
		Sleep(1000);
		gcall.FindThenKill(0,1000,modeAoe | modeNormal | modePickup | modeGoback,7);
		gcall.WaitPlans();
		break;
	case 8:
		gcall.Stepto(-62444,-43826,-1741);
		gcall.Stepto(-62594,-43866,-1741);
		Sleep(1000);
		gcall.DeliverQuests(zid,0xA,L"한시랑");
		Sleep(2000);
		gcall.Stepto(-62571,-43818,-1741);
		gcall.Stepto(-62467,-43843,-1741);
		gcall.Stepto(-62377,-43864,-1741);
		gcall.Stepto(-62376,-43903,-1741);
		gcall.Stepto(-62375,-44001,-1741);
		gcall.Stepto(-62377,-44086,-1741);
		gcall.Stepto(-62381,-44339,-1781);
		gcall.Stepto(-62401,-44388,-1785);
		gcall.Stepto(-62552,-44587,-1805);
		gcall.Stepto(-62701,-44785,-1854);
		gcall.Stepto(-62770,-44896,-1883);
		gcall.Stepto(-62771,-45140,-1926);
		gcall.Stepto(-62773,-45384,-1934);
		gcall.Stepto(-62774,-45640,-1944);
		gcall.Stepto(-62776,-45886,-1954);
		gcall.Stepto(-62751,-45922,-1955);
		gcall.Stepto(-62564,-46065,-1955);
		gcall.Stepto(-62359,-46225,-1951);
		gcall.Stepto(-62160,-46362,-1937);
		gcall.Stepto(-61946,-46450,-1935);
		Sleep(1000);
		gcall.FenJieByConfig();
		Sleep(1000);
		gcall.SellItemByConfig(L"한냥해");
		Sleep(1000);
		gcall.SortBag();
		Sleep(1000);
		/*买(200,1,한냥해);
		Sleep(1000);
		卖(한냥해);
		Sleep(1000);
		整理背包();
		Sleep(1000);
		按键(ESC);
		按键(ESC);
		gcall.Stepto(-61949,-46506,-1938);
		gcall.Stepto(-61934,-46452,-1935);
		gcall.Stepto(-61932,-46443,-1934);
		gcall.Stepto(-62033,-46291,-1930);
		gcall.Stepto(-62107,-46178,-1929);
		gcall.Stepto(-62007,-46057,-1926);
		gcall.Stepto(-61985,-46031,-1926);
		gcall.Stepto(-61793,-45977,-1926);
		gcall.Stepto(-61551,-45904,-1923);
		gcall.Stepto(-61381,-45854,-1923);
		gcall.Stepto(-61291,-45854,-1923);
		gcall.Stepto(-61182,-45861,-1923);
		Sleep(1000);
		买(60,0,무승휴);
		Sleep(1000);*/
		break;
	case 9:
		break;

	}
}

void TaskScript::Task_540(int zid,int taskid)
{
	BOOL flag21 = FALSE;
	BOOL flag22 = FALSE;
	BOOL flag23 = FALSE;
	switch (taskid)
	{
	case 1:
		gcall.NewSpend(2.5);
		gcall.Stepto(-61969,-46359,-1929,20,20,3000);
		gcall.Stepto(-62041,-46292,-1931,20,20,3000);
		gcall.Stepto(-62227,-46134,-1938,20,20,3000);
		gcall.Stepto(-62443,-46002,-1948);
		gcall.Stepto(-62641,-45868,-1950);
		gcall.Stepto(-62640,-45750,-1945);
		gcall.Stepto(-62645,-45505,-1935);
		gcall.Stepto(-62654,-45261,-1926);
		gcall.Stepto(-62656,-45008,-1903);
		gcall.Stepto(-62657,-44797,-1853);
		gcall.Stepto(-62669,-44384,-1791);
		gcall.Stepto(-63005,-44337,-1801);
		gcall.Stepto(-63431,-44304,-1813);
		gcall.Stepto(-63854,-44388,-1823);
		gcall.Stepto(-64237,-44593,-1859);
		gcall.Stepto(-64584,-44855,-1909);
		gcall.Stepto(-64882,-45162,-1957);
		gcall.Stepto(-65156,-45509,-2003);
		gcall.Stepto(-65405,-45836,-2004);
		gcall.Stepto(-65677,-46201,-1932);
		gcall.Stepto(-65893,-46578,-1889);
		gcall.Stepto(-66092,-46971,-1877);
		gcall.Stepto(-66228,-47229,-1877);
		gcall.Stepto(-66304,-47337,-1879);
		gcall.Stepto(-66522,-47444,-1868);
		gcall.Stepto(-66754,-47494,-1854);
		gcall.Stepto(-67018,-47570,-1834);
		gcall.Stepto(-67435,-47690,-1796);
		gcall.Stepto(-67745,-47780,-1760);
		gcall.Stepto(-67984,-47848,-1736);
		gcall.Stepto(-68222,-47917,-1722);
		gcall.Stepto(-68451,-47984,-1713);
		gcall.Stepto(-68481,-47996,-1712);
		gcall.Stepto(-68703,-48103,-1710);
		gcall.Stepto(-68927,-48210,-1713);
		gcall.Stepto(-69144,-48338,-1720);
		gcall.Stepto(-69335,-48494,-1735);
		gcall.Stepto(-69527,-48654,-1750);
		gcall.Stepto(-69716,-48811,-1765);
		gcall.Stepto(-69909,-48971,-1782);
		gcall.Stepto(-70100,-49129,-1800);
		gcall.Stepto(-70237,-49244,-1812);
		gcall.Stepto(-70541,-49496,-1835);
		gcall.Stepto(-70878,-49776,-1846);
		gcall.Stepto(-71211,-50052,-1848);
		gcall.Stepto(-71544,-50329,-1842);
		gcall.Stepto(-71878,-50607,-1841);
		gcall.Stepto(-72235,-50861,-1861);
		gcall.Stepto(-72562,-51014,-1885);
		gcall.Stepto(-72798,-51088,-1898);
		gcall.Stepto(-73036,-51167,-1906);
		gcall.Stepto(-73269,-51248,-1904);
		gcall.Stepto(-73505,-51330,-1898);
		gcall.Stepto(-73739,-51411,-1890);
		gcall.Stepto(-73977,-51480,-1878);
		gcall.Stepto(-74225,-51518,-1863);
		gcall.Stepto(-74469,-51554,-1841);
		gcall.Stepto(-74714,-51591,-1820);
		gcall.Stepto(-74960,-51642,-1802);
		gcall.Stepto(-75162,-51706,-1793);
		gcall.Stepto(-75473,-51811,-1778);
		gcall.Stepto(-75884,-51954,-1757);
		gcall.Stepto(-76294,-52102,-1729);
		gcall.Stepto(-76698,-52251,-1698);
		gcall.Stepto(-77105,-52412,-1683);
		gcall.Stepto(-77505,-52577,-1666);
		gcall.Stepto(-77721,-52695,-1659);
		gcall.Stepto(-77906,-52865,-1671);
		gcall.Stepto(-78085,-53033,-1657);
		gcall.Stepto(-78262,-53206,-1643);
		gcall.Stepto(-78430,-53393,-1642);
		gcall.Stepto(-78596,-53578,-1645);
		gcall.Stepto(-78763,-53765,-1648);
		gcall.Stepto(-78927,-53948,-1646);
		gcall.Stepto(-79094,-54135,-1650);
		gcall.Stepto(-79259,-54320,-1652);
		gcall.Stepto(-79415,-54494,-1653);
		gcall.Stepto(-79730,-54799,-1651);
		gcall.Stepto(-80077,-55056,-1640);
		gcall.Stepto(-80402,-55348,-1640);
		gcall.Stepto(-80711,-55653,-1637);
		gcall.Stepto(-81012,-55950,-1638);
		gcall.Stepto(-81190,-56126,-1642);
		gcall.Stepto(-81366,-56301,-1652);
		gcall.Stepto(-81543,-56475,-1665);
		gcall.Stepto(-81724,-56644,-1668);
		gcall.Stepto(-81924,-56791,-1683);
		gcall.Stepto(-82123,-56938,-1696);
		gcall.Stepto(-82333,-57076,-1704);
		gcall.Stepto(-82498,-57152,-1710);
		gcall.Stepto(-82869,-57317,-1734);
		gcall.Stepto(-83269,-57496,-1761);
		gcall.Stepto(-83669,-57674,-1789);
		gcall.Stepto(-84063,-57850,-1829);
		gcall.Stepto(-84284,-57962,-1854);
		gcall.Stepto(-84492,-58096,-1878);
		gcall.Stepto(-84673,-58265,-1902);
		gcall.Stepto(-84829,-58439,-1935);
		gcall.Stepto(-84998,-58693,-1983);
		gcall.Stepto(-85216,-59068,-2048);
		gcall.Stepto(-85377,-59348,-2086);
		gcall.Stepto(-85500,-59563,-2108);
		gcall.Stepto(-85586,-59794,-2125);
		gcall.Stepto(-85530,-60033,-2128);
		gcall.Stepto(-85372,-60224,-2114);
		gcall.Stepto(-85169,-60365,-2091);
		gcall.Stepto(-84938,-60450,-2067);
		gcall.Stepto(-84743,-60520,-2048);
		gcall.Stepto(-84397,-60646,-2007);
		gcall.Stepto(-83991,-60799,-1954);
		gcall.Stepto(-83570,-60911,-1909);
		gcall.Stepto(-83155,-60956,-1884);
		gcall.Stepto(-82907,-60971,-1881);
		gcall.Stepto(-82657,-60986,-1883);
		gcall.Stepto(-82411,-61001,-1877);
		gcall.Stepto(-82160,-61016,-1863);
		gcall.Stepto(-81913,-61030,-1852);
		gcall.Stepto(-81665,-61045,-1821);
		gcall.Stepto(-81414,-61059,-1789);
		gcall.Stepto(-81167,-61071,-1738);
		gcall.Stepto(-80923,-61025,-1700);
		gcall.Stepto(-80678,-60971,-1659);
		gcall.Stepto(-80545,-60934,-1636);
		gcall.Stepto(-80554,-60935,-1637);
		gcall.Stepto(-80899,-60956,-1702);
		gcall.Stepto(-81333,-60973,-1775);
		gcall.Stepto(-81774,-60962,-1835);
		gcall.Stepto(-82204,-60904,-1862);
		gcall.Stepto(-82632,-60833,-1882);
		gcall.Stepto(-82975,-60778,-1874);
		gcall.Stepto(-83148,-60936,-1885);
		gcall.Stepto(-83335,-61100,-1876);
		gcall.Stepto(-83426,-61328,-1835);
		gcall.Stepto(-83476,-61571,-1756);
		gcall.Stepto(-83454,-61820,-1664);
		gcall.Stepto(-83408,-62029,-1610);
		gcall.Stepto(-83337,-62217,-1578);
		gcall.Stepto(-83244,-62355,-1553);
		gcall.Stepto(-83186,-62505,-1529);
		gcall.Stepto(-83104,-62739,-1492);
		gcall.Stepto(-83021,-62976,-1448);
		gcall.Stepto(-82940,-63208,-1402);
		gcall.Stepto(-82856,-63446,-1362);
		gcall.Stepto(-82767,-63677,-1323);
		gcall.Stepto(-82684,-63854,-1304);
		gcall.Stepto(-82454,-64197,-1210);
		gcall.Stepto(-82107,-64452,-1117);
		gcall.Stepto(-81690,-64570,-1045);
		gcall.Stepto(-81261,-64581,-941);
		gcall.Stepto(-80896,-64338,-861);
		gcall.Stepto(-80570,-64051,-768);
		gcall.Stepto(-80263,-63746,-704);
		gcall.Stepto(-79920,-63475,-581);
		gcall.Stepto(-79747,-63470,-522);
		gcall.Stepto(-79498,-63474,-405);
		gcall.Stepto(-79384,-63476,-353);
		gcall.Stepto(-79271,-63455,-316);
		gcall.Stepto(-79060,-63519,-274);
		gcall.Stepto(-79062,-63675,-265);
		gcall.Stepto(-79260,-64050,-240);
		gcall.Stepto(-79463,-64434,-199);
		gcall.Stepto(-79665,-64818,-120);
		gcall.Stepto(-79850,-65168,-2);
		gcall.Stepto(-79966,-65388,65);
		gcall.Stepto(-80092,-65602,131);
		gcall.Stepto(-80202,-65749,177);
		gcall.Stepto(-80368,-65898,217);
		gcall.Stepto(-80563,-66058,256);
		gcall.Stepto(-80763,-66204,286);
		gcall.Stepto(-80973,-66336,317);
		gcall.Stepto(-81189,-66466,333);
		gcall.Stepto(-81408,-66582,347);
		gcall.Stepto(-81626,-66694,347);
		gcall.Stepto(-81816,-66791,338);
		gcall.Stepto(-81849,-66809,338);
		gcall.NewSpend(1);
		Sleep(1000);
		
		lianji22_go();
		while (true)
		{
			if (gcall.GetPlayerLevel() == 21)
			{
				if (flag21 == FALSE)
				{
					gcall.AddTalent(0x167);
					if (gcall.isTalentPanelShow())
					{
						gcall.OpenTalentUI();
						Sleep(1000);
					}
					flag21 = TRUE;
				}
				
			}else if (gcall.GetPlayerLevel() == 22)
			{
				if (flag22 == FALSE)
				{
					gcall.AddTalent(0x16E);
					if (gcall.isTalentPanelShow())
					{
						gcall.OpenTalentUI();
						Sleep(1000);
					}
					flag22 = TRUE;
				}

			}else if (gcall.GetPlayerLevel() == 23)
			{
				if (flag23 == FALSE)
				{
					gcall.LinQuJiangLi();
					gcall.AddTalent(0x16F);
					if (gcall.isTalentPanelShow())
					{
						gcall.OpenTalentUI();
						Sleep(1000);
					}
					flag23 = TRUE;
				}

			}
			
			if (gcall.GetPlayerLevel() < 25)
			{
				UseExperience();
				lianji22();
			}else
			{
				gcall.CityConvey(0xa);
				break;
			}
		}
		gcall.AddTalent(0x1C7);
		gcall.AddTalent(0x1C8);
		if (gcall.isTalentPanelShow())
		{
			gcall.OpenTalentUI();
			Sleep(1000);
		}
		gcall.Stepto(-81333,-67080,380);
		gcall.Stepto(-81324,-66843,363);
		gcall.Stepto(-81305,-66596,349);
		gcall.Stepto(-81279,-66350,331);
		Sleep(1000);
		gcall.SellItemByConfig(L"초유랑");
		Sleep(1000);
		gcall.SortBag();
		Sleep(1000);
		gcall.NewBag();
		Sleep(5000);
		gcall.Stepto(-81247,-66297,329);
		gcall.Stepto(-81368,-66501,337);
		gcall.Stepto(-81499,-66712,361);
		gcall.Stepto(-81647,-66910,355);
		Sleep(1000);
		gcall.FixWuqi();
		Sleep(1000);
		

		/*领取礼包(19);
		Sleep(1000);
		整理背包();
		Sleep(1000);
		执行脚本(22级练级2.inf,22);
		Sleep(1000);
		领取礼包(23);
		Sleep(1000);
		使用物品(대사막 약선 용봉탕);
		Sleep(1000);
		执行脚本(22级练级2.inf,24);*/
		/*Sleep(1000);
		gcall.Stepto(-74852,-64520,-959);
		gcall.Stepto(-74842,-64309,-952);
		gcall.Stepto(-74830,-64061,-886);
		gcall.Stepto(-74828,-63813,-837);
		gcall.Stepto(-74870,-63566,-792);
		gcall.Stepto(-74958,-63348,-778);
		gcall.Stepto(-75067,-63124,-782);
		gcall.Stepto(-75180,-62904,-805);
		gcall.Stepto(-75295,-62684,-815);
		gcall.Stepto(-75415,-62467,-818);
		gcall.Stepto(-75449,-62417,-819);
		gcall.Stepto(-75530,-62474,-819);
		gcall.Stepto(-75532,-62476,-819);
		gcall.NewSpend(1);
		Sleep(1000);
		gcall.FixWuqi();
		Sleep(1000);
		gcall.NewSpend(2.5);
		gcall.Stepto(-75632,-62187,-816);
		gcall.Stepto(-75847,-62062,-823);
		gcall.Stepto(-76065,-61954,-836);
		gcall.Stepto(-76300,-61863,-859);
		gcall.Stepto(-76535,-61780,-890);
		gcall.Stepto(-76769,-61698,-938);
		gcall.Stepto(-77005,-61620,-989);
		gcall.Stepto(-77241,-61549,-1041);
		gcall.Stepto(-77480,-61478,-1094);
		gcall.Stepto(-77718,-61408,-1145);
		gcall.Stepto(-77956,-61338,-1198);
		gcall.Stepto(-78192,-61268,-1250);
		gcall.Stepto(-78432,-61198,-1303);
		gcall.Stepto(-78577,-61155,-1335);
		gcall.Stepto(-78705,-61221,-1350);
		gcall.Stepto(-78925,-61335,-1363);
		gcall.Stepto(-79142,-61449,-1356);
		gcall.Stepto(-79362,-61566,-1342);
		gcall.Stepto(-79581,-61684,-1348);
		gcall.Stepto(-79793,-61809,-1370);
		gcall.Stepto(-79995,-61954,-1376);
		gcall.Stepto(-80219,-62052,-1367);
		gcall.Stepto(-80466,-62091,-1381);
		gcall.Stepto(-80713,-62105,-1415);
		gcall.Stepto(-80960,-62116,-1433);
		gcall.Stepto(-81208,-62126,-1445);
		gcall.Stepto(-81456,-62137,-1455);
		gcall.Stepto(-81705,-62148,-1457);
		gcall.Stepto(-81952,-62180,-1456);
		gcall.Stepto(-82186,-62255,-1460);
		gcall.Stepto(-82414,-62361,-1479);
		gcall.Stepto(-82650,-62437,-1506);
		gcall.Stepto(-82889,-62492,-1517);
		gcall.Stepto(-82993,-62521,-1517);
		gcall.Stepto(-83022,-62610,-1506);
		gcall.Stepto(-83024,-62704,-1493);
		gcall.Stepto(-82994,-62951,-1451);
		gcall.Stepto(-82924,-63187,-1405);
		gcall.Stepto(-82846,-63423,-1363);
		gcall.Stepto(-82766,-63657,-1325);
		gcall.Stepto(-82672,-63887,-1298);
		gcall.Stepto(-82586,-64078,-1266);
		gcall.Stepto(-82501,-64182,-1224);
		gcall.Stepto(-82379,-64296,-1190);
		gcall.Stepto(-82183,-64360,-1149);
		gcall.Stepto(-81946,-64432,-1095);
		gcall.Stepto(-81707,-64497,-1056);
		gcall.Stepto(-81467,-64562,-984);
		gcall.Stepto(-81228,-64627,-931);
		gcall.Stepto(-81085,-64646,-903);
		gcall.Stepto(-80974,-64589,-884);
		gcall.Stepto(-80812,-64402,-848);
		gcall.Stepto(-80665,-64202,-795);
		gcall.Stepto(-80517,-64003,-757);
		gcall.Stepto(-80369,-63801,-726);
		gcall.Stepto(-80209,-63611,-679);
		gcall.Stepto(-80020,-63451,-612);
		gcall.Stepto(-79878,-63333,-561);
		gcall.Stepto(-79687,-63324,-492);
		gcall.Stepto(-79558,-63344,-442);
		gcall.Stepto(-79406,-63390,-371);
		gcall.Stepto(-79225,-63473,-301);
		gcall.Stepto(-79141,-63525,-281);
		gcall.Stepto(-79043,-63604,-269);
		gcall.Stepto(-79035,-63727,-257);
		gcall.Stepto(-79134,-63898,-247);
		gcall.Stepto(-79258,-64114,-229);
		gcall.Stepto(-79383,-64329,-211);
		gcall.Stepto(-79506,-64541,-185);
		gcall.Stepto(-79628,-64753,-141);
		gcall.Stepto(-79754,-64969,-69);
		gcall.Stepto(-79881,-65189,5);
		gcall.Stepto(-80005,-65403,72);
		gcall.Stepto(-80129,-65618,139);
		gcall.Stepto(-80253,-65833,198);
		gcall.Stepto(-80377,-66047,246);
		gcall.Stepto(-80502,-66262,285);
		gcall.Stepto(-80600,-66381,309);
		gcall.Stepto(-80820,-66490,325);
		gcall.Stepto(-81046,-66594,336);
		gcall.Stepto(-81280,-66680,361);
		gcall.Stepto(-81521,-66738,360);
		gcall.Stepto(-81764,-66789,339);
		gcall.Stepto(-81831,-66803,338);
		Sleep(1000);
		gcall.Stepto(-81800,-66808,339);
		gcall.Stepto(-81773,-66778,338);
		gcall.Stepto(-81602,-66598,340);
		gcall.Stepto(-81423,-66426,333);
		gcall.Stepto(-81321,-66332,331);
		gcall.Stepto(-81292,-66306,330);
		gcall.FenJieByConfig();
		Sleep(1000);
		gcall.SellItemByConfig(L"초유랑");
		Sleep(1000);
		gcall.Stepto(-81334,-66367,331);
		gcall.Stepto(-81476,-66569,345);
		gcall.Stepto(-81679,-66709,338);*/
		gcall.Stepto(-81834,-66793,338,10,10,3000);
		Sleep(1000);
		gcall.DeliverQuests(zid,taskid,L"거만하");
		Sleep(1000);
		
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

void TaskScript::Task_502(int zid,int taskid)
{
	switch (taskid)
	{
	case 1:
		gcall.NewSpend(2.5);
		gcall.Stepto(-81819,-66788,338);
		gcall.Stepto(-81673,-66752,340);
		gcall.Stepto(-81431,-66698,361);
		gcall.Stepto(-81189,-66644,353);
		gcall.Stepto(-80947,-66590,335);
		gcall.Stepto(-80707,-66528,329);
		gcall.Stepto(-80497,-66399,307);
		gcall.Stepto(-80318,-66228,282);
		gcall.Stepto(-80172,-66028,242);
		gcall.Stepto(-80065,-65804,184);
		gcall.Stepto(-79960,-65580,116);
		gcall.Stepto(-79855,-65355,49);
		gcall.Stepto(-79750,-65130,-24);
		gcall.Stepto(-79644,-64904,-105);
		gcall.Stepto(-79540,-64679,-161);
		gcall.Stepto(-79437,-64457,-193);
		gcall.Stepto(-79331,-64230,-219);
		gcall.Stepto(-79230,-64012,-242);
		gcall.Stepto(-79136,-63777,-263);
		gcall.Stepto(-79185,-63542,-285);
		gcall.Stepto(-79398,-63420,-365);
		gcall.Stepto(-79641,-63375,-477);
		gcall.Stepto(-79889,-63352,-566);
		gcall.Stepto(-80128,-63408,-640);
		gcall.Stepto(-80298,-63586,-697);
		gcall.Stepto(-80428,-63797,-735);
		gcall.Stepto(-80560,-64007,-764);
		gcall.Stepto(-80718,-64197,-806);
		gcall.Stepto(-80899,-64367,-864);
		gcall.Stepto(-81111,-64493,-911);
		gcall.Stepto(-81350,-64560,-956);
		gcall.Stepto(-81597,-64568,-1022);
		gcall.Stepto(-81837,-64513,-1075);
		gcall.Stepto(-82063,-64408,-1112);
		gcall.Stepto(-82279,-64284,-1177);
		gcall.Stepto(-82486,-64164,-1227);
		gcall.Stepto(-82574,-64099,-1262);
		gcall.Stepto(-82663,-64014,-1283);
		gcall.Stepto(-82746,-63901,-1303);
		gcall.Stepto(-82793,-63736,-1319);
		gcall.Stepto(-82825,-63585,-1344);
		gcall.Stepto(-82852,-63421,-1364);
		gcall.Stepto(-82874,-63246,-1393);
		gcall.Stepto(-82901,-63039,-1431);
		gcall.Stepto(-82956,-62838,-1469);
		gcall.Stepto(-83052,-62701,-1495);
		gcall.Stepto(-83197,-62646,-1511);
		gcall.Stepto(-83349,-62610,-1528);
		gcall.Stepto(-83462,-62591,-1542);
		gcall.Stepto(-83542,-62659,-1547);
		gcall.Stepto(-83468,-62783,-1526);
		gcall.Stepto(-83408,-62889,-1503);
		gcall.NewSpend(1);
		gcall.Stepto(-83360,-62979,-1481);
		gcall.Stepto(-83355,-63039,-1472);
		Sleep(2000);
		gcall.FindThenKill(0,300,modeAoe | modeNormal | modePickup);
		gcall.Stepto(-83408,-62889,-1503);
		gcall.Stepto(-83360,-62979,-1481);
		gcall.Stepto(-83355,-63039,-1472);
		Sleep(1000);
		gcall.PickupTask();
		Sleep(1000);
		gcall.FindThenKill(0,200,modeAoe | modeNormal | modePickup);
		gcall.NewSpend(2.5);
		gcall.Stepto(-83416,-62728,-1524,10,10,3000);
		gcall.Stepto(-83045,-62631,-1504);
		gcall.Stepto(-82539,-62509,-1490);
		gcall.Stepto(-82343,-63047,-1448);
		gcall.NewSpend(1);
		Sleep(1000);
		gcall.PickupTask();
		Sleep(1000);
		gcall.FindThenKill(0,200,modeAoe | modeNormal | modePickup);
		gcall.NewSpend(2.5);
		gcall.Stepto(-82180,-62916,-1457,10,10,3000);
		gcall.Stepto(-81731,-62712,-1468);
		gcall.Stepto(-81193,-62433,-1453);
		gcall.Stepto(-80789,-62211,-1418);
		gcall.Stepto(-80480,-62049,-1392);
		gcall.NewSpend(1);
		Sleep(1000);
		gcall.PickupTask();
		Sleep(1000);
		gcall.FindThenKill(0,200,modeAoe | modeNormal | modePickup);
		gcall.NewSpend(2.5);
		gcall.Stepto(-80668,-61670,-1485,10,10,3000);
		gcall.Stepto(-81138,-61026,-1740);
		gcall.Stepto(-81794,-61018,-1838);
		gcall.Stepto(-82656,-61018,-1881);
		gcall.Stepto(-83274,-60875,-1890);
		gcall.Stepto(-83938,-60722,-1953);
		gcall.Stepto(-84770,-60639,-2052);
		gcall.Stepto(-85283,-60404,-2104);
		gcall.Stepto(-85794,-60236,-2148);
		gcall.Stepto(-86351,-60033,-2098);
		gcall.NewSpend(1);
		Sleep(1000);
		gcall.PickupTask();
		Sleep(1000);
		gcall.FindThenKill(0,200,modeAoe | modeNormal | modePickup);
		gcall.NewSpend(2.5);
		gcall.Stepto(-86371,-60448,-2142,10,10,3000);
		gcall.Stepto(-86496,-60914,-2160);
		gcall.Stepto(-86604,-61405,-2143);
		gcall.Stepto(-86729,-62010,-2127);
		gcall.Stepto(-86828,-62517,-2161);
		gcall.Stepto(-86884,-62802,-2172);
		gcall.NewSpend(1);
		Sleep(1000);
		gcall.PickupTask();
		Sleep(1000);
		gcall.FindThenKill(0,200,modeAoe | modeNormal | modePickup);
		gcall.NewSpend(2.5);
		gcall.Stepto(-87465,-62670,-2242,10,10,3000);
		gcall.Stepto(-87910,-62604,-2219);
		gcall.Stepto(-88229,-62550,-2171);
		gcall.Stepto(-88419,-62862,-2157);
		gcall.Stepto(-88557,-63116,-2148);
		gcall.NewSpend(1);
		Sleep(1000);
		gcall.PickupTask();
		Sleep(1000);
		gcall.FindThenKill(0,200,modeAoe | modeNormal | modePickup);
		gcall.NewSpend(2.5);
		gcall.Stepto(-88513,-63048,-2152,10,10,3000);
		gcall.Stepto(-88383,-62927,-2167);
		gcall.Stepto(-88198,-62756,-2188);
		gcall.Stepto(-88017,-62587,-2207);
		gcall.Stepto(-87836,-62420,-2215);
		gcall.Stepto(-87654,-62251,-2218);
		gcall.Stepto(-87475,-62085,-2214);
		gcall.Stepto(-87291,-61915,-2203);
		gcall.Stepto(-87106,-61743,-2196);
		gcall.Stepto(-86939,-61560,-2186);
		gcall.Stepto(-86780,-61373,-2172);
		gcall.Stepto(-86618,-61183,-2162);
		gcall.Stepto(-86458,-60995,-2156);
		gcall.Stepto(-86296,-60805,-2150);
		gcall.Stepto(-86130,-60621,-2148);
		gcall.Stepto(-85927,-60483,-2146);
		gcall.Stepto(-85701,-60379,-2141);
		gcall.Stepto(-85456,-60356,-2122);
		gcall.Stepto(-85221,-60435,-2097);
		gcall.Stepto(-84990,-60527,-2073);
		gcall.Stepto(-84760,-60619,-2051);
		gcall.Stepto(-84535,-60709,-2021);
		gcall.Stepto(-84299,-60798,-1987);
		gcall.Stepto(-84063,-60877,-1955);
		gcall.Stepto(-83830,-60956,-1926);
		gcall.Stepto(-83601,-61033,-1898);
		gcall.Stepto(-83492,-61070,-1887);
		gcall.Stepto(-83456,-61283,-1847);
		gcall.Stepto(-83375,-61517,-1781);
		gcall.Stepto(-83279,-61746,-1712);
		gcall.Stepto(-83183,-61973,-1647);
		gcall.Stepto(-83100,-62208,-1573);
		gcall.Stepto(-83065,-62366,-1543);
		gcall.randXianlu(0);
		break;
	case 2:
		gcall.NewSpend(2.5);
		gcall.Stepto(-86929,-62820,-2178);
		gcall.Stepto(-87072,-62546,-2209);
		gcall.Stepto(-87139,-62122,-2213);
		gcall.Stepto(-87040,-61795,-2196);
		gcall.Stepto(-86939,-61633,-2187);
		gcall.Stepto(-86710,-61264,-2168);
		gcall.Stepto(-86452,-60916,-2158);
		gcall.Stepto(-86146,-60618,-2149);
		gcall.Stepto(-85756,-60453,-2141);
		gcall.Stepto(-85327,-60513,-2109);
		gcall.Stepto(-84900,-60608,-2065);
		gcall.Stepto(-84477,-60702,-2014);
		gcall.Stepto(-84054,-60792,-1961);
		gcall.Stepto(-83623,-60852,-1916);
		gcall.Stepto(-83233,-60881,-1888);
		gcall.Stepto(-82981,-60898,-1883);
		gcall.Stepto(-82734,-60916,-1885);
		gcall.Stepto(-82487,-60951,-1881);
		gcall.Stepto(-82244,-60990,-1867);
		gcall.Stepto(-81994,-61013,-1857);
		gcall.Stepto(-81746,-61024,-1832);
		gcall.Stepto(-81607,-61028,-1813);
		gcall.Stepto(-81359,-61032,-1782);
		gcall.Stepto(-81113,-61025,-1736);
		gcall.Stepto(-80865,-60993,-1693);
		gcall.Stepto(-80769,-60977,-1677);
		gcall.Stepto(-80842,-60964,-1692);
		gcall.Stepto(-81275,-60976,-1766);
		gcall.Stepto(-81708,-60974,-1826);
		gcall.Stepto(-82141,-60950,-1861);
		gcall.Stepto(-82344,-60928,-1873);
		gcall.Stepto(-82591,-60902,-1884);
		gcall.Stepto(-82834,-60933,-1884);
		gcall.Stepto(-83028,-61083,-1872);
		gcall.Stepto(-83166,-61289,-1840);
		gcall.Stepto(-83298,-61499,-1786);
		gcall.Stepto(-83383,-61735,-1705);
		gcall.Stepto(-83381,-61980,-1627);
		gcall.Stepto(-83389,-62221,-1574);
		gcall.Stepto(-83317,-62451,-1543);
		gcall.Stepto(-83188,-62662,-1508);
		gcall.Stepto(-83072,-62881,-1467);
		gcall.Stepto(-82988,-63112,-1422);
		gcall.Stepto(-82913,-63353,-1346);
		gcall.Stepto(-82838,-63586,-1344);
		gcall.Stepto(-82724,-63808,-1311);
		gcall.Stepto(-82593,-64018,-1273);
		gcall.Stepto(-82423,-64199,-1203);
		gcall.Stepto(-82213,-64329,-1159);
		gcall.Stepto(-81980,-64414,-1100);
		gcall.Stepto(-81740,-64484,-1063);
		gcall.Stepto(-81497,-64536,-995);
		gcall.Stepto(-81253,-64522,-940);
		gcall.Stepto(-81045,-64388,-894);
		gcall.Stepto(-80854,-64231,-842);
		gcall.Stepto(-80668,-64066,-786);
		gcall.Stepto(-80555,-63955,-761);
		gcall.Stepto(-80379,-63780,-727);
		gcall.Stepto(-80201,-63608,-676);
		gcall.Stepto(-79977,-63503,-600);
		gcall.Stepto(-79731,-63475,-515);
		gcall.Stepto(-79484,-63448,-401);
		gcall.Stepto(-79236,-63424,-306);
		gcall.Stepto(-79144,-63475,-284);
		gcall.Stepto(-79186,-63719,-274);
		gcall.Stepto(-79261,-63954,-253);
		gcall.Stepto(-79372,-64175,-231);
		gcall.Stepto(-79487,-64400,-207);
		gcall.Stepto(-79601,-64620,-174);
		gcall.Stepto(-79717,-64839,-110);
		gcall.Stepto(-79834,-65061,-34);
		gcall.Stepto(-79945,-65282,36);
		gcall.Stepto(-80053,-65506,103);
		gcall.Stepto(-80179,-65719,168);
		gcall.Stepto(-80331,-65915,219);
		gcall.Stepto(-80530,-66061,255);
		gcall.Stepto(-80740,-66194,282);
		gcall.Stepto(-80955,-66318,314);
		gcall.Stepto(-81175,-66441,331);
		gcall.Stepto(-81392,-66560,344);
		gcall.Stepto(-81615,-66674,349);
		gcall.Stepto(-81820,-66776,338);
		gcall.Stepto(-81854,-66793,337);
		gcall.NewSpend(1);
		Sleep(1000);
		gcall.DeliverQuests(zid,taskid,L"거만하");
		Sleep(1000);
		break;
	case 3:
		gcall.NewSpend(2.5);
		gcall.Stepto(-81642,-66717,345);
		gcall.Stepto(-81411,-66624,355);
		gcall.Stepto(-81184,-66525,335);
		gcall.Stepto(-80964,-66411,324);
		gcall.Stepto(-80762,-66268,295);
		gcall.Stepto(-80564,-66118,264);
		gcall.Stepto(-80367,-65967,231);
		gcall.Stepto(-80175,-65810,190);
		gcall.Stepto(-80040,-65604,128);
		gcall.Stepto(-79936,-65379,61);
		gcall.Stepto(-79832,-65153,-8);
		gcall.Stepto(-79729,-64928,-84);
		gcall.Stepto(-79625,-64701,-154);
		gcall.Stepto(-79520,-64476,-197);
		gcall.Stepto(-79409,-64257,-223);
		gcall.Stepto(-79297,-64035,-245);
		gcall.Stepto(-79184,-63812,-263);
		gcall.Stepto(-79072,-63591,-271);
		gcall.Stepto(-79045,-63538,-272);
		gcall.Stepto(-79101,-63512,-278);
		gcall.Stepto(-79327,-63410,-337);
		gcall.Stepto(-79550,-63308,-440);
		gcall.Stepto(-79723,-63229,-499);
		gcall.Stepto(-79767,-63265,-519);
		gcall.Stepto(-79958,-63423,-591);
		gcall.Stepto(-80149,-63582,-661);
		gcall.Stepto(-80314,-63767,-715);
		gcall.Stepto(-80461,-63966,-747);
		gcall.Stepto(-80608,-64166,-781);
		gcall.Stepto(-80755,-64366,-832);
		gcall.Stepto(-80901,-64563,-869);
		gcall.Stepto(-80904,-64567,-870);
		gcall.Stepto(-80994,-64560,-889);
		gcall.Stepto(-81241,-64540,-938);
		gcall.Stepto(-81488,-64521,-994);
		gcall.Stepto(-81736,-64504,-1060);
		gcall.Stepto(-81982,-64476,-1095);
		gcall.Stepto(-82090,-64441,-1114);
		gcall.Stepto(-82258,-64257,-1180);
		gcall.Stepto(-82424,-64075,-1236);
		gcall.Stepto(-82590,-63893,-1285);
		gcall.Stepto(-82759,-63707,-1320);
		gcall.Stepto(-82857,-63600,-1343);
		gcall.Stepto(-82898,-63439,-1364);
		gcall.Stepto(-82957,-63198,-1405);
		gcall.Stepto(-83015,-62959,-1451);
		gcall.Stepto(-83074,-62715,-1494);
		gcall.Stepto(-83118,-62538,-1521);
		gcall.Stepto(-83182,-62548,-1523);
		gcall.Stepto(-83379,-62581,-1535);
		gcall.Stepto(-83575,-62613,-1553);
		gcall.Stepto(-83769,-62645,-1571);
		gcall.Stepto(-83967,-62678,-1586);
		gcall.Stepto(-84162,-62709,-1600);
		gcall.Stepto(-84360,-62742,-1613);
		gcall.Stepto(-84554,-62774,-1605);
		gcall.Stepto(-84745,-62805,-1568);
		gcall.Stepto(-84937,-62744,-1567);
		gcall.Stepto(-85121,-62671,-1604);
		gcall.Stepto(-85306,-62599,-1638);
		gcall.Stepto(-85333,-62517,-1663);
		gcall.Stepto(-85480,-62744,-1565);
		gcall.Stepto(-85436,-62937,-1380);
		gcall.Stepto(-85386,-63130,-1276);
		gcall.Stepto(-85315,-63316,-1237);
		gcall.Stepto(-85240,-63498,-1175);
		gcall.Stepto(-85135,-63665,-1124);
		gcall.Stepto(-85090,-63692,-1117);
		gcall.Stepto(-84914,-63787,-1097);
		gcall.Stepto(-84738,-63878,-1079);
		gcall.Stepto(-84568,-63936,-1044);
		gcall.Stepto(-84509,-63952,-1023);
		gcall.Stepto(-84314,-64007,-955);
		gcall.Stepto(-84123,-64060,-879);
		gcall.Stepto(-84009,-64091,-824);
		gcall.Stepto(-83901,-64246,-761);
		gcall.Stepto(-83765,-64453,-703);
		gcall.Stepto(-83627,-64660,-611);
		gcall.Stepto(-83486,-64864,-471);
		gcall.Stepto(-83345,-65067,-376);
		gcall.Stepto(-83275,-65168,-321);
		gcall.NewSpend(1);
		gcall.Stepto(-83112,-65182,-294);
		gcall.Stepto(-83068,-65240,-245);
		Sleep(1000);
		//MessageBox(0, L"摇奖完", L"装八卦", MB_OK);
		gcall.Shunyi(L"2-3-3");
		Sleep(2000);
		gcall.sendcall(id_msg_OverShunyi,(LPVOID)0);
		Sleep(2000);
		//按键(Jump);
		//信息框(手动用轻功飞上前面的高台后点确定,任务不用你交~);
		gcall.DeliverQuests(zid,taskid,L"길동");
		Sleep(1000);
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

void TaskScript::Task_503(int zid,int taskid)
{
	switch (taskid)
	{
	case 1:
		gcall.NewSpend(2.5);
		gcall.Stepto(-84452,-63665,-434);
		gcall.Stepto(-84416,-63684,-434);
		gcall.Stepto(-84194,-63791,-781);
		gcall.Stepto(-84143,-63813,-944);
		gcall.Stepto(-84126,-63576,-1103);
		gcall.Stepto(-84141,-63341,-1366);
		gcall.Stepto(-84126,-63083,-1537);
		gcall.Stepto(-84005,-62867,-1576);
		gcall.Stepto(-83886,-62650,-1581);
		gcall.Stepto(-83811,-62548,-1576);
		gcall.Stepto(-83722,-62440,-1570);
		gcall.Stepto(-83595,-62228,-1565);
		gcall.Stepto(-83536,-62022,-1589);
		gcall.Stepto(-83526,-61824,-1649);
		gcall.Stepto(-83526,-61624,-1729);
		gcall.Stepto(-83528,-61425,-1810);
		gcall.Stepto(-83520,-61231,-1860);
		gcall.Stepto(-83451,-61042,-1888);
		gcall.Stepto(-83339,-60884,-1894);
		gcall.Stepto(-83143,-60856,-1884);
		gcall.Stepto(-83057,-60864,-1882);
		gcall.Stepto(-82839,-60885,-1883);
		gcall.Stepto(-82600,-60907,-1885);
		gcall.Stepto(-82353,-60930,-1874);
		gcall.Stepto(-82106,-60953,-1860);
		gcall.Stepto(-81909,-60972,-1850);
		gcall.Stepto(-81711,-60990,-1827);
		gcall.Stepto(-81514,-61009,-1801);
		gcall.Stepto(-81316,-61027,-1774);
		gcall.Stepto(-81107,-61047,-1731);
		gcall.Stepto(-80859,-61056,-1683);
		gcall.Stepto(-80612,-61036,-1642);
		gcall.Stepto(-80367,-61015,-1605);
		gcall.Stepto(-80118,-60993,-1572);
		gcall.Stepto(-79874,-60998,-1539);
		gcall.Stepto(-79642,-61058,-1503);
		gcall.Stepto(-79399,-61121,-1469);
		gcall.Stepto(-79159,-61183,-1429);
		gcall.Stepto(-78919,-61246,-1381);
		gcall.Stepto(-78679,-61308,-1333);
		gcall.Stepto(-78427,-61373,-1276);
		gcall.Stepto(-78187,-61435,-1228);
		gcall.Stepto(-77947,-61498,-1176);
		gcall.Stepto(-77707,-61560,-1124);
		gcall.Stepto(-77467,-61622,-1076);
		gcall.Stepto(-77227,-61685,-1023);
		gcall.Stepto(-77165,-61701,-1009);
		gcall.Stepto(-76927,-61765,-955);
		gcall.Stepto(-76688,-61825,-909);
		gcall.Stepto(-76460,-61894,-868);
		gcall.Stepto(-76216,-61980,-841);
		gcall.Stepto(-75981,-62073,-827);
		gcall.Stepto(-75757,-62180,-818);
		gcall.Stepto(-75537,-62295,-816);
		gcall.Stepto(-75319,-62413,-814);
		gcall.Stepto(-75208,-62473,-813);
		gcall.Stepto(-75158,-62539,-812);
		gcall.Stepto(-75006,-62734,-795);
		gcall.Stepto(-74890,-62849,-776);
		gcall.Stepto(-74889,-63022,-774);
		gcall.Stepto(-74882,-63270,-770);
		gcall.Stepto(-74868,-63522,-791);
		gcall.Stepto(-74848,-63769,-826);
		gcall.Stepto(-74829,-64016,-874);
		gcall.Stepto(-74820,-64264,-942);
		gcall.Stepto(-74836,-64511,-959);
		gcall.Stepto(-74858,-64659,-986);
		gcall.Stepto(-74872,-64751,-1008);
		gcall.Stepto(-74898,-64916,-1062);
		gcall.Stepto(-74871,-65166,-1138);
		gcall.Stepto(-74827,-65405,-1206);
		gcall.Stepto(-74858,-65647,-1248);
		gcall.Stepto(-74821,-65894,-1286);
		gcall.Stepto(-74628,-66049,-1327);
		gcall.Stepto(-74615,-66056,-1330);
		gcall.Stepto(-74428,-66186,-1345);
		gcall.Stepto(-74201,-66288,-1298);
		gcall.Stepto(-73963,-66369,-1262);
		gcall.Stepto(-73721,-66422,-1292);
		gcall.Stepto(-73487,-66479,-1317);
		gcall.Stepto(-73298,-66638,-1281);
		gcall.Stepto(-73202,-66873,-1225);
		gcall.Stepto(-73167,-67119,-1172);
		gcall.Stepto(-73182,-67367,-1100);
		gcall.Stepto(-73207,-67613,-991);
		gcall.Stepto(-73232,-67859,-911);
		gcall.Stepto(-73263,-68107,-818);
		gcall.Stepto(-73316,-68352,-775);
		gcall.NewSpend(1);
		gcall.Stepto(-73386,-68588,-778);
		gcall.Stepto(-73465,-68793,-779);
		Sleep(1000);
		gcall.DeliverQuests(zid,taskid,L"최진아");
		Sleep(1000);
		break;
	case 2:
		gcall.Stepto(-73531,-68764,-776);
		gcall.Stepto(-73575,-68747,-777);
		Sleep(1000);
		gcall.PickupTask();
		Sleep(1000);
		break;
	case 3:
		//过滤怪物(제물용 돼지,1);
		//过滤怪物(해탈이,1);
		gcall.Stepto(-73448,-68853,-779);
		gcall.Stepto(-73454,-68921,-779);
		gcall.Stepto(-73477,-69166,-779);
		gcall.Stepto(-73515,-69413,-778);
		gcall.Stepto(-73559,-69658,-778);
		gcall.Stepto(-73604,-69897,-779);
		gcall.Stepto(-73649,-70144,-779);
		gcall.Stepto(-73694,-70386,-779);
		gcall.Stepto(-73734,-70631,-779);
		gcall.Stepto(-73768,-70837,-779);
		gcall.sendcall(id_msg_attack, (LPVOID)0x5E06);//3
		Sleep(1500);
		gcall.sendcall(id_msg_attack, (LPVOID)0x5DE8);//z
		Sleep(500);
		gcall.Kill_Tab();
		gcall.TurnToNear(500);
		Sleep(300);
		gcall.sendcall(id_msg_attack, (LPVOID)0x5e74);//1
		gcall.FindThenKill(0,300,modeAoe | modeNormal | modePickup);
		gcall.Stepto(-73709,-70861,-779);
		gcall.Stepto(-73488,-70973,-779);
		gcall.Stepto(-73396,-71017,-779);
		gcall.Stepto(-73372,-71028,-779);
		gcall.Stepto(-73351,-71038,-779);
		Sleep(1000);
		gcall.PickupSpecTypeTask(200,0x4,L"비밀장부");
		Sleep(1000);
		break;
	case 4:
		//过滤怪物(제물용 돼지,3);
		//过滤怪物(해탈이,3);
		gcall.DeliverQuests(zid,taskid,L"최진아");
		//MessageBox(0, L"摇奖完", L"装八卦", MB_OK);
		Sleep(2000);
		break;
	case 5:
		gcall.NewSpend(2.5);
		gcall.Stepto(-73733,-71083,-779);
		gcall.Stepto(-73945,-71062,-779);
		gcall.Stepto(-74285,-71008,-779);
		gcall.Stepto(-74715,-70947,-779);
		gcall.Stepto(-75145,-70890,-778);
		gcall.Stepto(-75577,-70845,-776);
		gcall.Stepto(-75689,-70836,-776);
		gcall.Stepto(-75936,-70813,-775);
		gcall.Stepto(-76183,-70793,-773);
		gcall.Stepto(-76430,-70775,-775);
		gcall.Stepto(-76677,-70777,-776);
		gcall.NewSpend(1);
		gcall.Stepto(-76862,-70917,-776);
		gcall.Stepto(-76874,-70942,-777);
		Sleep(1000);
		gcall.sendcall(id_msg_attack, (LPVOID)0x5E06);//3
		Sleep(1500);
		gcall.sendcall(id_msg_attack, (LPVOID)0x5DE8);//z
		Sleep(500);
		gcall.Kill_Tab();
		gcall.TurnToNear(500);
		Sleep(300);
		gcall.sendcall(id_msg_attack, (LPVOID)0x5e74);//1
		gcall.FindThenKill(0,500,modeAoe | modeNormal | modePickup );
		gcall.Stepto(-76677,-70777,-776);
		gcall.Stepto(-76862,-70917,-776);
		gcall.Stepto(-76874,-70942,-777);
		Sleep(1000);
		gcall.PickupTask();
		Sleep(1000);

		gcall.Stepto(-76860,-70918,-777);
		gcall.Stepto(-76738,-70702,-774);
		gcall.Stepto(-76656,-70560,-771);
		Sleep(1000);
		gcall.PickupTask();
		Sleep(1000);

		gcall.NewSpend(2.5);
		gcall.Stepto(-76629,-70750,-775);
		gcall.Stepto(-76430,-70782,-775);
		gcall.Stepto(-76184,-70817,-772);
		gcall.Stepto(-75939,-70852,-775);
		gcall.Stepto(-75693,-70887,-777);
		gcall.Stepto(-75447,-70922,-777);
		gcall.Stepto(-75202,-70957,-777);
		gcall.Stepto(-74956,-70992,-779);
		gcall.Stepto(-74712,-71032,-779);
		gcall.Stepto(-74632,-71266,-779);
		gcall.Stepto(-74558,-71503,-779);
		gcall.Stepto(-74484,-71740,-779);
		gcall.Stepto(-74410,-71977,-779);
		gcall.Stepto(-74417,-72219,-779);
		gcall.Stepto(-74460,-72464,-779);
		gcall.Stepto(-74503,-72708,-778);
		gcall.Stepto(-74547,-72952,-783);
		gcall.Stepto(-74587,-73196,-780);
		gcall.Stepto(-74572,-73442,-783);
		gcall.Stepto(-74565,-73468,-783);
		gcall.NewSpend(1);
		Sleep(1000);
		gcall.sendcall(id_msg_attack, (LPVOID)0x5E06);//3
		Sleep(1500);
		gcall.sendcall(id_msg_attack, (LPVOID)0x5DE8);//z
		Sleep(500);
		gcall.Kill_Tab();
		gcall.TurnToNear(500);
		Sleep(300);
		gcall.sendcall(id_msg_attack, (LPVOID)0x5e74);//1
		gcall.FindThenKill(0,500,modeAoe | modeNormal | modePickup );
		gcall.Stepto(-74656,-73433,-781);
		gcall.Stepto(-74441,-73462,-782);
		Sleep(1000);
		gcall.PickupTask();
		Sleep(1000);
		gcall.Stepto(-74266,-73504,-782);
		gcall.Stepto(-74196,-73521,-782);
		Sleep(1000);
		gcall.DeliverQuests(zid,6,L"길동의 딸 소연화");
		Sleep(1000);
		break;
	case 6:
		gcall.CityConvey(0xB);
		gcall.WaitPlans();
		gcall.NewSpend(2.5);
		gcall.Stepto(-59775,-44554,-1840);
		gcall.Stepto(-60005,-44483,-1827);
		gcall.Stepto(-60244,-44527,-1821);
		gcall.Stepto(-60418,-44560,-1816);
		gcall.Stepto(-60826,-44677,-1827);
		gcall.Stepto(-61226,-44845,-1865);
		gcall.Stepto(-61624,-45019,-1911);
		gcall.Stepto(-62031,-45168,-1911);
		gcall.Stepto(-62377,-45276,-1918);
		gcall.Stepto(-62460,-45172,-1914);
		gcall.Stepto(-62574,-44762,-1833);
		gcall.Stepto(-62468,-44342,-1785);
		gcall.Stepto(-62412,-43967,-1741);
		gcall.Stepto(-62419,-43850,-1741);
		gcall.NewSpend(1);
		gcall.Stepto(-62455,-43847,-1741);
		gcall.Stepto(-62597,-43855,-1741);
		gcall.WaitPlans();
		gcall.DeliverQuests(zid,7,L"한시랑");
		Sleep(1000);
		break;
	case 7:
		break;
	case 8:
		break;
	case 9:
		break;

	}
}


void TaskScript::Task_504(int zid,int taskid)
{
	switch (taskid)
	{
	case 1:
		if (gcall.GetCityID() != 3002)
		{
			gcall.Stepto(-62376,-44058,-1741);
			gcall.Stepto(-62375,-43873,-1741);
			gcall.WaitPlans();
			gcall.Stepto(-62550,-43836,-1741);
		}
		gcall.DeliverQuests(zid,taskid,L"홍삼");
		Sleep(1000);
		break;
	case 2:
		if (gcall.GetCityID() != 3002)
		{
			gcall.Stepto(-62376,-44058,-1741);
			gcall.Stepto(-62375,-43873,-1741);
			gcall.WaitPlans();
			gcall.Stepto(-62550,-43836,-1741);
		}
		gcall.DeliverQuests(zid,taskid,L"수삼");
		Sleep(1000);
		break;
	case 3:
		gcall.NewSpend(2.5);
		gcall.Stepto(-62470,-43882,-1741);
		gcall.Stepto(-62374,-44036,-1741);
		gcall.Stepto(-62368,-44076,-1741);
		gcall.Stepto(-62391,-44255,-1775);
		gcall.WaitPlans();
		gcall.Stepto(-62444,-44482,-1792);
		gcall.Stepto(-62583,-44897,-1870);
		gcall.Stepto(-62697,-45312,-1930);
		gcall.Stepto(-62710,-45745,-1947);
		gcall.Stepto(-62713,-46183,-1963);
		gcall.Stepto(-62753,-46611,-1967);
		gcall.Stepto(-62811,-46978,-1963);
		gcall.Stepto(-62846,-47149,-1960);
		gcall.Stepto(-62913,-47572,-1959);
		gcall.Stepto(-62979,-47999,-1977);
		gcall.Stepto(-63045,-48434,-1983);
		gcall.Stepto(-63102,-48864,-1984);
		gcall.Stepto(-63144,-49297,-1995);
		gcall.Stepto(-63134,-49730,-2004);
		gcall.Stepto(-63087,-49989,-2007);
		gcall.Stepto(-63036,-50234,-2008);
		gcall.Stepto(-62986,-50477,-2007);
		gcall.Stepto(-62937,-50718,-2002);
		gcall.Stepto(-62889,-50964,-1994);
		gcall.Stepto(-62845,-51207,-1981);
		gcall.Stepto(-62788,-51431,-1961);
		gcall.Stepto(-62699,-51743,-1924);
		gcall.Stepto(-62581,-52159,-1872);
		gcall.Stepto(-62462,-52576,-1816);
		gcall.Stepto(-62348,-52966,-1755);
		gcall.Stepto(-62275,-53206,-1722);
		gcall.Stepto(-62207,-53436,-1698);
		gcall.Stepto(-62164,-53792,-1673);
		gcall.Stepto(-62151,-54018,-1664);
		gcall.Stepto(-62130,-54366,-1658);
		gcall.Stepto(-62116,-54609,-1659);
		gcall.Stepto(-62101,-54859,-1660);
		gcall.Stepto(-62082,-55106,-1663);
		gcall.Stepto(-62073,-55356,-1672);
		gcall.Stepto(-62053,-55627,-1684);
		gcall.Stepto(-62019,-56064,-1712);
		gcall.Stepto(-61993,-56417,-1742);
		gcall.Stepto(-61982,-56630,-1763);
		gcall.Stepto(-61975,-56976,-1807);
		gcall.Stepto(-61971,-57224,-1843);
		gcall.Stepto(-61968,-57472,-1878);
		gcall.Stepto(-61971,-57720,-1904);
		gcall.Stepto(-61935,-58023,-1925);
		gcall.Stepto(-61879,-58454,-1939);
		gcall.Stepto(-61850,-58669,-1945);
		gcall.Stepto(-61821,-58891,-1943);
		gcall.Stepto(-61786,-59138,-1943);
		gcall.NewSpend(1);
		gcall.Stepto(-61765,-59284,-1943);
		gcall.Stepto(-61756,-59326,-1943);
		Sleep(1000);
		gcall.DeliverQuests(zid,taskid,L"봉찬");
		Sleep(1000);
		break;
	case 4:
		gcall.NewSpend(2.5);
		gcall.Stepto(-61790,-59285,-1944);
		gcall.Stepto(-61879,-59208,-1944);
		gcall.Stepto(-62071,-59050,-1944);
		gcall.Stepto(-62292,-58941,-1950);
		gcall.Stepto(-62536,-58940,-1954);
		gcall.Stepto(-62760,-59040,-1952);
		gcall.Stepto(-62885,-59092,-1948);
		gcall.Stepto(-63060,-58961,-1945);
		gcall.Stepto(-63256,-58808,-1935);
		gcall.Stepto(-63453,-58658,-1904);
		gcall.Stepto(-63645,-58616,-1877);
		gcall.Stepto(-63892,-58600,-1855);
		gcall.Stepto(-64140,-58583,-1841);
		gcall.Stepto(-64362,-58509,-1830);
		gcall.Stepto(-64484,-58293,-1814);
		gcall.Stepto(-64608,-58078,-1797);
		gcall.Stepto(-64767,-57901,-1785);
		gcall.Stepto(-64896,-57690,-1770);
		gcall.Stepto(-65022,-57476,-1764);
		gcall.NewSpend(1);
		gcall.Stepto(-65057,-57394,-1762);
		gcall.Stepto(-65058,-57383,-1762);
		Sleep(1000);
		gcall.PickupTask();
		Sleep(1000);
		gcall.randXianlu(0);
		break;
	case 5:
		gcall.GoodsQuests(zid,taskid,L"정찰병의 보고서");
		Sleep(1000);
		break;
	case 6:
		gcall.NewSpend(2.5);
		gcall.Stepto(-65047,-57381,-1761);
		gcall.Stepto(-64801,-57346,-1743);
		gcall.Stepto(-64564,-57275,-1735);
		gcall.Stepto(-64363,-57158,-1733);
		gcall.Stepto(-64106,-56933,-1732);
		gcall.Stepto(-63775,-56655,-1718);
		gcall.Stepto(-63415,-56408,-1691);
		gcall.Stepto(-63033,-56202,-1680);
		gcall.Stepto(-62647,-55998,-1685);
		gcall.Stepto(-62276,-55778,-1700);
		gcall.Stepto(-62096,-55401,-1676);
		gcall.Stepto(-62092,-55286,-1670);
		gcall.Stepto(-62091,-55196,-1666);
		gcall.Stepto(-62089,-54948,-1661);
		gcall.Stepto(-62087,-54700,-1659);
		gcall.Stepto(-62085,-54452,-1659);
		gcall.Stepto(-62083,-54204,-1660);
		gcall.Stepto(-62081,-53956,-1665);
		gcall.Stepto(-62128,-53709,-1677);
		gcall.Stepto(-62180,-53466,-1695);
		gcall.Stepto(-62232,-53224,-1719);
		gcall.Stepto(-62284,-52981,-1752);
		gcall.Stepto(-62336,-52738,-1792);
		gcall.Stepto(-62388,-52496,-1828);
		gcall.Stepto(-62441,-52254,-1859);
		gcall.Stepto(-62493,-52013,-1887);
		gcall.Stepto(-62545,-51769,-1912);
		gcall.Stepto(-62598,-51526,-1939);
		gcall.Stepto(-62648,-51294,-1964);
		gcall.Stepto(-62702,-51041,-1982);
		gcall.Stepto(-62754,-50799,-1994);
		gcall.Stepto(-62807,-50555,-2003);
		gcall.Stepto(-62859,-50312,-2007);
		gcall.Stepto(-62911,-50071,-2009);
		gcall.Stepto(-62964,-49826,-2010);
		gcall.Stepto(-63016,-49586,-2006);
		gcall.Stepto(-63068,-49344,-1999);
		gcall.Stepto(-63120,-49101,-1990);
		gcall.Stepto(-63092,-48855,-1985);
		gcall.Stepto(-63028,-48615,-1983);
		gcall.Stepto(-62965,-48377,-1983);
		gcall.Stepto(-62901,-48136,-1982);
		gcall.Stepto(-62837,-47895,-1976);
		gcall.Stepto(-62778,-47656,-1968);
		gcall.Stepto(-62758,-47406,-1959);
		gcall.Stepto(-62743,-47160,-1958);
		gcall.Stepto(-62728,-46912,-1963);
		gcall.Stepto(-62714,-46665,-1967);
		gcall.Stepto(-62699,-46415,-1967);
		gcall.Stepto(-62684,-46167,-1962);
		gcall.Stepto(-62669,-45920,-1953);
		gcall.Stepto(-62655,-45672,-1942);
		gcall.Stepto(-62640,-45425,-1932);
		gcall.Stepto(-62638,-45177,-1922);
		gcall.Stepto(-62626,-44925,-1883);
		gcall.Stepto(-62565,-44685,-1815);
		gcall.Stepto(-62552,-44639,-1812);
		gcall.Stepto(-62485,-44414,-1790);
		gcall.Stepto(-62418,-44176,-1763);
		gcall.Stepto(-62377,-43970,-1741);
		gcall.NewSpend(1);
		gcall.Stepto(-62393,-43886,-1741);
		gcall.Stepto(-62489,-43873,-1741);
		gcall.WaitPlans();
		gcall.Stepto(-62633,-43846,-1741);
		Sleep(1000);
		gcall.DeliverQuests(zid,taskid,L"한시랑");
		Sleep(1000);
		break;
	case 7:
		break;
	case 8:
		break;
	case 9:
		break;

	}
}

void TaskScript::Task_505(int zid,int taskid)
{
	switch (taskid)
	{
	case 1:
		gcall.NewSpend(2.5);
		gcall.Stepto(-62387,-43914,-1741);
		gcall.Stepto(-62379,-44224,-1770);
		gcall.WaitPlans();
		gcall.Stepto(-62656,-44770,-1846,10,10,5000);
		gcall.Stepto(-62580,-45223,-1922,10,10,5000);
		gcall.Stepto(-62418,-45857,-1940,10,10,5000);
		gcall.NewSpend(1);
		Sleep(1000);
		gcall.DeliverQuests(zid,2,L"홍일");
		Sleep(1000);
		gcall.NewSpend(2.5);
		gcall.Stepto(-62937,-45918,-1957);
		gcall.Stepto(-63529,-46151,-1973);
		gcall.Stepto(-64252,-46212,-2008);
		gcall.NewSpend(1);
		Sleep(1000);
		gcall.DeliverQuests(zid,taskid,L"청월");
		Sleep(1000);
		break;
	case 2:
		gcall.NewSpend(2.5);
		gcall.Stepto(-64214,-46218,-2003);
		gcall.Stepto(-64131,-46216,-1997);
		gcall.Stepto(-63882,-46211,-1990);
		gcall.Stepto(-63635,-46203,-1983);
		gcall.Stepto(-63397,-46142,-1967);
		gcall.Stepto(-63183,-46008,-1958);
		gcall.Stepto(-63032,-45817,-1951);
		gcall.Stepto(-62920,-45594,-1944);
		gcall.Stepto(-62829,-45366,-1935);
		gcall.Stepto(-62774,-45123,-1925);
		gcall.Stepto(-62735,-44877,-1878);
		gcall.Stepto(-62711,-44630,-1827);
		gcall.Stepto(-62698,-44536,-1813);
		gcall.Stepto(-62347,-44293,-1776);
		gcall.Stepto(-62481,-44299,-1778);
		gcall.Stepto(-62608,-44293,-1774);
		gcall.Stepto(-62855,-44283,-1773);
		gcall.Stepto(-63104,-44302,-1800);
		gcall.Stepto(-63352,-44333,-1812);
		gcall.Stepto(-63597,-44364,-1819);
		gcall.Stepto(-63832,-44438,-1828);
		gcall.Stepto(-64055,-44549,-1848);
		gcall.Stepto(-64266,-44676,-1872);
		gcall.Stepto(-64475,-44811,-1900);
		gcall.Stepto(-64681,-44952,-1924);
		gcall.Stepto(-64880,-45102,-1944);
		gcall.Stepto(-65068,-45259,-1963);
		gcall.Stepto(-65181,-45480,-1996);
		gcall.Stepto(-65290,-45704,-2012);
		gcall.Stepto(-65403,-45928,-2010);
		gcall.Stepto(-65534,-46133,-1984);
		gcall.Stepto(-65668,-46345,-1940);
		gcall.Stepto(-65802,-46554,-1916);
		gcall.Stepto(-65935,-46763,-1897);
		gcall.Stepto(-66068,-46973,-1881);
		gcall.Stepto(-66202,-47183,-1876);
		gcall.Stepto(-66336,-47391,-1881);
		gcall.Stepto(-66518,-47556,-1872);
		gcall.Stepto(-66757,-47620,-1856);
		gcall.Stepto(-66999,-47672,-1837);
		gcall.Stepto(-67246,-47725,-1815);
		gcall.Stepto(-67488,-47777,-1790);
		gcall.Stepto(-67730,-47829,-1761);
		gcall.Stepto(-67973,-47880,-1737);
		gcall.Stepto(-68214,-47936,-1722);
		gcall.Stepto(-68443,-48032,-1712);
		gcall.Stepto(-68668,-48135,-1710);
		gcall.Stepto(-68890,-48245,-1712);
		gcall.Stepto(-69097,-48382,-1719);
		gcall.Stepto(-69300,-48524,-1733);
		gcall.Stepto(-69503,-48667,-1748);
		gcall.Stepto(-69707,-48811,-1764);
		gcall.Stepto(-69900,-48969,-1782);
		gcall.Stepto(-70085,-49134,-1799);
		gcall.Stepto(-70269,-49298,-1816);
		gcall.Stepto(-70457,-49465,-1830);
		gcall.Stepto(-70642,-49630,-1838);
		gcall.Stepto(-70835,-49784,-1844);
		gcall.Stepto(-71038,-49926,-1848);
		gcall.Stepto(-71244,-50071,-1848);
		gcall.Stepto(-71447,-50214,-1847);
		gcall.Stepto(-71650,-50357,-1844);
		gcall.Stepto(-71854,-50500,-1843);
		gcall.Stepto(-72057,-50642,-1846);
		gcall.Stepto(-72260,-50785,-1860);
		gcall.Stepto(-72463,-50928,-1877);
		gcall.Stepto(-72666,-51071,-1893);
		gcall.Stepto(-72872,-51208,-1909);
		gcall.Stepto(-73117,-51256,-1911);
		gcall.Stepto(-73363,-51300,-1903);
		gcall.Stepto(-73606,-51344,-1894);
		gcall.Stepto(-73851,-51388,-1884);
		gcall.Stepto(-74097,-51433,-1869);
		gcall.Stepto(-74342,-51477,-1851);
		gcall.Stepto(-74585,-51521,-1828);
		gcall.Stepto(-74829,-51565,-1808);
		gcall.Stepto(-75074,-51609,-1792);
		gcall.Stepto(-75322,-51654,-1775);
		gcall.Stepto(-75566,-51698,-1757);
		gcall.Stepto(-75812,-51729,-1738);
		gcall.Stepto(-76053,-51683,-1706);
		gcall.Stepto(-76293,-51614,-1672);
		gcall.Stepto(-76526,-51531,-1645);
		gcall.Stepto(-76763,-51446,-1607);
		gcall.Stepto(-76972,-51322,-1547);
		gcall.Stepto(-77104,-51112,-1491);
		gcall.Stepto(-77241,-50906,-1436);
		gcall.Stepto(-77380,-50700,-1378);
		gcall.Stepto(-77515,-50489,-1322);
		gcall.NewSpend(1);
		gcall.Stepto(-77609,-50261,-1272);
		gcall.Stepto(-77727,-50042,-1226);
		gcall.Stepto(-77847,-49821,-1177);
		gcall.Stepto(-77963,-49601,-1133);
		gcall.Stepto(-78072,-49385,-1112);
		gcall.Stepto(-78133,-49144,-1106);
		Sleep(2000);
		gcall.Stepto(-78148,-49023,-1107);
		gcall.WaitPlans();
		gcall.Stepto(-78180,-48761,-1109);
		gcall.Stepto(-78198,-48517,-1111);
		gcall.NewSpend(2.5);
		gcall.Stepto(-78195,-48267,-1114);
		gcall.Stepto(-78293,-48040,-1108);
		gcall.Stepto(-78371,-47894,-1066);
		gcall.Stepto(-78322,-48021,-1107);
		gcall.Stepto(-78273,-48049,-1108);
		gcall.Stepto(-78040,-48033,-1104);
		gcall.Stepto(-77821,-47910,-1082);
		gcall.Stepto(-77596,-47797,-1060);
		gcall.Stepto(-77383,-47690,-1016);
		gcall.Stepto(-77228,-47612,-994);
		gcall.Stepto(-76998,-47521,-960);
		gcall.Stepto(-76761,-47449,-921);
		gcall.Stepto(-76519,-47386,-883);
		gcall.Stepto(-76277,-47330,-870);
		gcall.Stepto(-76048,-47253,-858);
		gcall.Stepto(-76045,-47252,-858);
		gcall.Stepto(-75865,-47128,-855);
		gcall.Stepto(-75640,-47025,-849);
		gcall.Stepto(-75507,-47004,-848);
		gcall.Stepto(-75261,-46976,-827);
		gcall.Stepto(-75223,-46999,-824);
		gcall.Stepto(-75112,-47031,-824);
		gcall.NewSpend(1);
		gcall.Stepto(-75141,-47118,-824);
		gcall.Stepto(-75169,-47203,-824);
		gcall.WaitPlans();
		gcall.Stepto(-75199,-47255,-824);
		Sleep(1000);
		gcall.DeliverQuests(zid,3,L"백무");
		Sleep(1000);
		break;
	case 3:
		gcall.DeliverQuests(zid,4,L"한시랑");
		Sleep(1000);
		break;
	case 4:
		gcall.DeliverQuests(zid,5,L"백무");
		Sleep(1000);
		break;
	case 5:
		gcall.NewSpend(2.5);
		gcall.Stepto(-75133,-47087,-824);
		gcall.Stepto(-75161,-47060,-824);
		gcall.Stepto(-75240,-46986,-824);
		gcall.Stepto(-75402,-46890,-848);
		gcall.Stepto(-75484,-46835,-849);
		gcall.Stepto(-75584,-46766,-852);
		gcall.Stepto(-75660,-46919,-851);
		gcall.Stepto(-75818,-47102,-853);
		gcall.Stepto(-75895,-47147,-856);
		gcall.Stepto(-75934,-47161,-857);
		gcall.Stepto(-76168,-47242,-863);
		gcall.Stepto(-76403,-47323,-876);
		gcall.Stepto(-76637,-47405,-904);
		gcall.Stepto(-76874,-47487,-938);
		gcall.Stepto(-77109,-47568,-982);
		gcall.Stepto(-77343,-47652,-1003);
		gcall.Stepto(-77569,-47754,-1053);
		gcall.Stepto(-77780,-47883,-1079);
		gcall.Stepto(-77975,-48036,-1102);
		gcall.Stepto(-78187,-48161,-1113);
		gcall.Stepto(-78406,-48058,-1109);
		gcall.Stepto(-78478,-47873,-1106);
		gcall.Stepto(-78521,-47501,-1114);
		gcall.Stepto(-78566,-47069,-1140);
		gcall.Stepto(-78606,-46637,-1171);
		gcall.Stepto(-78646,-46205,-1237);
		gcall.Stepto(-78691,-45905,-1273);
		gcall.Stepto(-78959,-45754,-1297);
		gcall.Stepto(-79350,-45561,-1321);
		gcall.Stepto(-79755,-45416,-1345);
		gcall.Stepto(-80187,-45357,-1423);
		gcall.Stepto(-80621,-45324,-1492);
		gcall.Stepto(-81055,-45303,-1576);
		gcall.Stepto(-81492,-45292,-1636);
		gcall.Stepto(-81891,-45312,-1670);
		gcall.Stepto(-82120,-45400,-1688);
		gcall.Stepto(-82303,-45568,-1703);
		gcall.Stepto(-82482,-45740,-1719);
		gcall.Stepto(-82663,-45909,-1731);
		gcall.Stepto(-82844,-46079,-1733);
		gcall.Stepto(-83010,-46263,-1736);
		gcall.Stepto(-83195,-46426,-1739);
		gcall.Stepto(-83423,-46522,-1741);
		gcall.Stepto(-83645,-46563,-1742);
		gcall.Stepto(-83982,-46582,-1745);
		gcall.Stepto(-84248,-46584,-1747);
		gcall.Stepto(-84446,-46585,-1748);
		gcall.Stepto(-84645,-46587,-1750);
		gcall.Stepto(-84822,-46591,-1756);
		gcall.Stepto(-85005,-46609,-1766);
		gcall.Stepto(-85216,-46647,-1785);
		gcall.Stepto(-85541,-46764,-1832);
		gcall.Stepto(-85929,-46959,-1918);
		gcall.Stepto(-86297,-47188,-2022);
		gcall.Stepto(-86627,-47469,-2111);
		gcall.NewSpend(1);
		gcall.Stepto(-86980,-47722,-2200);
		gcall.Stepto(-87348,-47953,-2300);
		gcall.Stepto(-87668,-48142,-2379);
		gcall.Stepto(-87891,-48273,-2429);
		gcall.Stepto(-88105,-48398,-2465);
		gcall.Stepto(-88320,-48522,-2506);
		Sleep(2000);
		gcall.Stepto(-88377,-48556,-2538);
		gcall.WaitPlans();
		gcall.Stepto(-88624,-48706,-2684);
		gcall.Stepto(-88822,-48856,-2811);
		gcall.NewSpend(2.5);
		gcall.Stepto(-89016,-49011,-2936);
		gcall.Stepto(-89168,-49121,-3027);
		gcall.Stepto(-89495,-49383,-3110);
		gcall.Stepto(-89453,-49776,-3109);
		gcall.Stepto(-89180,-50113,-3108);
		gcall.Stepto(-88937,-50473,-3094);
		gcall.Stepto(-88710,-50842,-3085);
		gcall.Stepto(-88481,-51216,-3082);
		gcall.Stepto(-88258,-51589,-3084);
		gcall.Stepto(-88163,-52007,-3074);
		gcall.Stepto(-88310,-52410,-3080);
		gcall.Stepto(-88602,-52728,-3087);
		gcall.Stepto(-88927,-53016,-3086);
		gcall.Stepto(-89242,-53302,-3087);
		gcall.Stepto(-89426,-53465,-3087);
		gcall.Stepto(-89389,-53375,-3087);
		gcall.NewSpend(1);
		gcall.Stepto(-89312,-53286,-3086);
		gcall.Stepto(-89449,-53444,-3087);
		gcall.Stepto(-89549,-53617,-3087);
		gcall.Stepto(-89623,-53801,-3087);
		gcall.Stepto(-89675,-53993,-3087);
		gcall.Stepto(-89704,-54103,-3087);
		gcall.Stepto(-89617,-53934,-3087);
		gcall.Stepto(-89546,-53749,-3087);
		gcall.Stepto(-89475,-53564,-3087);
		gcall.Stepto(-89405,-53377,-3087);
		gcall.Stepto(-89337,-53191,-3087);
		gcall.Stepto(-89322,-53005,-3087);
		gcall.Stepto(-89414,-52957,-3087);
		Sleep(5000);
		gcall.sendcall(id_msg_attack, (LPVOID)0x5E06);//3
		Sleep(1500);
		gcall.sendcall(id_msg_attack, (LPVOID)0x5DE8);//z
		Sleep(500);
		gcall.Kill_Tab();
		gcall.TurnToNear(500);
		Sleep(300);
		gcall.sendcall(id_msg_attack, (LPVOID)0x5e74);//1
		//任务捡物5(300,서낭당 천둥귀);
		gcall.FindThenKill(0,300,modeAoe | modeNormal | modePickup);
		gcall.PickupSpecTypeTask(200,0x90,L"천둥귀의 북");
		gcall.Stepto(-89242,-53012,-3087);
		gcall.Stepto(-89120,-53132,-3087);
		gcall.Stepto(-89413,-53364,-3087);
		gcall.Stepto(-90003,-53689,-3087);
		Sleep(1000);
		gcall.PickupSpecTypeTask(200,0x20,L"봉인석");
		Sleep(1000);
		
		//2
		gcall.Stepto(-90259,-53355,-3087);
		//任务捡物5(400,서낭당 천둥귀);
		gcall.FindThenKill(0,300,modeAoe | modeNormal | modePickup);
		gcall.PickupSpecTypeTask(200,0x90,L"천둥귀의 북");
		gcall.Stepto(-90395,-53460,-3087);
		Sleep(1000);
		gcall.PickupSpecTypeTask(200,0x20,L"봉인석");
		Sleep(1000);

		//3
		gcall.Stepto(-90810,-53465,-3087);
		//任务捡物5(400,서낭당 천둥귀);
		gcall.FindThenKill(0,300,modeAoe | modeNormal | modePickup);
		gcall.PickupSpecTypeTask(200,0x90,L"천둥귀의 북");
		gcall.Stepto(-90710,-53695,-3087);
		Sleep(1000);
		gcall.PickupSpecTypeTask(200,0x20,L"봉인석");
		Sleep(1000);

		//4
		gcall.Stepto(-90998,-53908,-3087);
		//任务捡物5(400,서낭당 천둥귀);
		gcall.FindThenKill(0,300,modeAoe | modeNormal | modePickup);
		gcall.PickupSpecTypeTask(200,0x90,L"천둥귀의 북");
		gcall.Stepto(-90581,-54097,-3087);
		Sleep(1000);
		gcall.PickupSpecTypeTask(200,0x20,L"봉인석");
		Sleep(1000);

		//清
		gcall.Stepto(-90720,-54301,-3086);
		gcall.FindThenKill(0,300,modeAoe | modeNormal | modePickup);

		//5
		gcall.Stepto(-90300,-54518,-3086);
		//任务捡物5(200,서낭당 천둥귀);
		gcall.FindThenKill(0,300,modeAoe | modeNormal | modePickup);
		gcall.PickupSpecTypeTask(200,0x90,L"천둥귀의 북");
		gcall.Stepto(-90124,-54114,-3054);
		Sleep(1000);
		gcall.PickupSpecTypeTask(200,0x20,L"봉인석");
		gcall.sendcall(id_msg_attack, (LPVOID)0x5DFC);//v


		//BOSS？
		gcall.Stepto(-90346,-53846,-3087);
		gcall.FindThenKill(0,300,modeAoe | modeNormal | modePickup);
		Sleep(2000);
		break;
	case 6:
		gcall.CityConvey(0xC);
		gcall.WaitPlans();
		gcall.Stepto(-75628,-46784,-855);
		gcall.Stepto(-75628,-46784,-855);
		gcall.Stepto(-75627,-46784,-853);
		gcall.Stepto(-75412,-46887,-848);
		gcall.Stepto(-75227,-47004,-824);
		gcall.Stepto(-75217,-47010,-824);
		gcall.Stepto(-75113,-47057,-824);
		gcall.Stepto(-75186,-47222,-824);
		gcall.WaitPlans();
		gcall.Stepto(-75189,-47229,-824);
		Sleep(1000);
		gcall.DeliverQuests(zid,7,L"백무");
		Sleep(1000);
		break;
	case 7:
		gcall.Stepto(-75182,-47210,-824);
		gcall.Stepto(-75134,-47102,-824);
		gcall.Stepto(-75239,-46986,-824);
		gcall.Stepto(-75381,-46883,-847);
		gcall.Stepto(-75403,-46868,-848);
		gcall.Stepto(-75492,-46720,-850);
		gcall.Stepto(-75523,-46538,-854);
		gcall.Stepto(-75491,-46311,-849);
		Sleep(1000);
		gcall.FindThenKill(0,300,modeAoe | modeNormal | modePickup);
		Sleep(1000);
		gcall.PickupTask();
		Sleep(1000);
		gcall.FindThenKill(0,300,modeAoe | modeNormal | modePickup);
		gcall.randXianlu(0);
		gcall.sendcall(id_msg_attack, (LPVOID)0x5DFC);//v
		break;
	case 8:
		gcall.Stepto(-75515,-46461,-853);
		gcall.Stepto(-75554,-46691,-852);
		gcall.Stepto(-75473,-46774,-849);
		gcall.Stepto(-75293,-46945,-831);
		gcall.Stepto(-75224,-47003,-824);
		gcall.Stepto(-75125,-47070,-824);
		gcall.Stepto(-75187,-47225,-824);
		gcall.WaitPlans();
		gcall.Stepto(-75188,-47226,-824);
		Sleep(1000);
		gcall.DeliverQuests(zid,9,L"백무");
		Sleep(1000);
		break;
	case 9:
		break;

	}
}

void TaskScript::Task_506(int zid,int taskid)
{
	switch (taskid)
	{
	case 1:
		gcall.NewSpend(2.5);
		gcall.Stepto(-75139,-47049,-824,30);
		gcall.Stepto(-75240,-46988,-824,30);
		gcall.Stepto(-75414,-46920,-848,30);
		gcall.Stepto(-75507,-46957,-848,30);
		gcall.Stepto(-75512,-46959,-848,30);
		gcall.Stepto(-75724,-47083,-850);
		gcall.Stepto(-75950,-47188,-857);
		gcall.Stepto(-76175,-47293,-862);
		gcall.Stepto(-76405,-47359,-877);
		gcall.Stepto(-76412,-47363,-878);
		gcall.Stepto(-76629,-47418,-904);
		gcall.Stepto(-77041,-47555,-967);
		gcall.Stepto(-77436,-47733,-1032);
		gcall.Stepto(-77817,-47940,-1085);
		gcall.Stepto(-78226,-48067,-1108);
		gcall.Stepto(-78537,-47807,-1107);
		gcall.Stepto(-78606,-47380,-1124);
		gcall.Stepto(-78638,-46947,-1144);
		gcall.Stepto(-78671,-46514,-1186);
		gcall.Stepto(-78641,-46084,-1252);
		gcall.Stepto(-78506,-45671,-1273);
		gcall.Stepto(-78315,-45280,-1270);
		gcall.Stepto(-78113,-45024,-1252);
		gcall.Stepto(-77905,-44890,-1236);
		gcall.Stepto(-77695,-44758,-1227);
		gcall.Stepto(-77483,-44634,-1218);
		gcall.Stepto(-77237,-44606,-1199);
		gcall.Stepto(-77014,-44606,-1172);
		gcall.Stepto(-77013,-44606,-1172);
		gcall.Stepto(-76803,-44606,-1138);
		gcall.Stepto(-76556,-44606,-1102);
		gcall.Stepto(-76306,-44606,-1068);
		gcall.Stepto(-76058,-44605,-1041);
		gcall.Stepto(-75827,-44605,-1017);
		gcall.Stepto(-75564,-44605,-981);
		gcall.Stepto(-75315,-44604,-949);
		gcall.Stepto(-75067,-44611,-923);
		gcall.Stepto(-74816,-44617,-894);
		gcall.Stepto(-74568,-44622,-857);
		gcall.Stepto(-74328,-44574,-816);
		gcall.Stepto(-74100,-44477,-775);
		gcall.Stepto(-73872,-44379,-746);
		gcall.Stepto(-73644,-44281,-728);
		gcall.Stepto(-73416,-44183,-706);
		gcall.Stepto(-73202,-44063,-684);
		gcall.Stepto(-73054,-43864,-664);
		gcall.Stepto(-72921,-43655,-636);
		gcall.Stepto(-72844,-43418,-619);
		gcall.Stepto(-72775,-43177,-608);
		gcall.Stepto(-72721,-42935,-603);
		gcall.Stepto(-72693,-42689,-602);
		gcall.Stepto(-72666,-42442,-608);
		gcall.Stepto(-72641,-42195,-618);
		gcall.Stepto(-72641,-41948,-618);
		gcall.Stepto(-72636,-41697,-614);
		gcall.Stepto(-72630,-41449,-610);
		gcall.Stepto(-72624,-41201,-603);
		gcall.Stepto(-72626,-40953,-596);
		gcall.Stepto(-72647,-40706,-590);
		gcall.Stepto(-72682,-40460,-584);
		gcall.Stepto(-72732,-40247,-579);
		gcall.Stepto(-72771,-40054,-572);
		gcall.Stepto(-72768,-39856,-566);
		gcall.Stepto(-72756,-39656,-556);
		gcall.Stepto(-72710,-39463,-554);
		gcall.Stepto(-72639,-39241,-558);
		gcall.Stepto(-72564,-39005,-568);
		gcall.Stepto(-72470,-38777,-582);
		gcall.Stepto(-72336,-38569,-598);
		gcall.Stepto(-72186,-38372,-614);
		gcall.Stepto(-72034,-38174,-633);
		gcall.Stepto(-71883,-37977,-651);
		gcall.Stepto(-71731,-37778,-657);
		gcall.Stepto(-71588,-37592,-653);
		gcall.Stepto(-71475,-37429,-649);
		gcall.Stepto(-71397,-37245,-644);
		gcall.Stepto(-71345,-37053,-641);
		gcall.Stepto(-71302,-36860,-640);
		gcall.Stepto(-71263,-36651,-639);
		gcall.Stepto(-71235,-36405,-638);
		gcall.Stepto(-71251,-36154,-639);
		gcall.Stepto(-71254,-36131,-639);
		gcall.Stepto(-71271,-35909,-641);
		gcall.NewSpend(1);
		gcall.Stepto(-71283,-35758,-642);
		gcall.Stepto(-71377,-35657,-639);
		Sleep(1000);
		gcall.DeliverQuests(zid,taskid,L"지혜");
		Sleep(1000);
		break;
	case 2:
		gcall.NewSpend(2.5);
		gcall.Stepto(-71188,-35585,-647);
		gcall.Stepto(-71150,-35483,-648);
		gcall.Stepto(-71142,-35237,-652);
		gcall.Stepto(-71153,-34987,-657);
		gcall.Stepto(-71136,-34754,-658);
		gcall.Stepto(-71114,-34505,-661);
		gcall.Stepto(-71104,-34245,-661);
		gcall.Stepto(-71106,-33997,-661);
		gcall.Stepto(-71120,-33756,-660);
		gcall.Stepto(-71200,-33523,-660);
		gcall.Stepto(-71321,-33311,-659);
		gcall.Stepto(-71459,-33105,-657);
		gcall.Stepto(-71630,-32926,-652);
		gcall.Stepto(-71817,-32782,-643);
		gcall.Stepto(-72035,-32661,-634);
		gcall.Stepto(-72274,-32555,-628);
		gcall.Stepto(-72500,-32459,-624);
		gcall.Stepto(-72735,-32366,-624);
		gcall.Stepto(-72973,-32298,-626);
		gcall.Stepto(-73218,-32245,-596);
		gcall.Stepto(-73458,-32192,-556);
		gcall.Stepto(-73467,-32190,-556);
		gcall.Stepto(-73677,-32137,-614);
		gcall.Stepto(-74043,-32111,-767);
		gcall.Stepto(-74091,-32110,-788);
		gcall.WaitPlans();
		gcall.Stepto(-74336,-32088,-876);
		gcall.NewSpend(2.5);
		gcall.Stepto(-74588,-32076,-960);
		gcall.Stepto(-74832,-32096,-1034);
		gcall.Stepto(-75064,-32168,-1081);
		gcall.Stepto(-75232,-32348,-1120);
		gcall.Stepto(-75329,-32576,-1142);
		gcall.Stepto(-75413,-32810,-1101);
		gcall.Stepto(-75476,-33047,-1032);
		gcall.Stepto(-75516,-33295,-939);
		gcall.Stepto(-75536,-33431,-930);
		gcall.Stepto(-75552,-33538,-930);
		gcall.Stepto(-75587,-33781,-980);
		gcall.Stepto(-75624,-34031,-977);
		gcall.Stepto(-75659,-34271,-977);
		gcall.Stepto(-75696,-34522,-978);
		gcall.Stepto(-75778,-34758,-983);
		gcall.Stepto(-75875,-34827,-984);
		gcall.Stepto(-76103,-34930,-978);
		gcall.Stepto(-76326,-35030,-979);
		gcall.Stepto(-76566,-35095,-984);
		gcall.Stepto(-76813,-35129,-983);
		gcall.Stepto(-77062,-35163,-989);
		gcall.Stepto(-77308,-35200,-991);
		gcall.Stepto(-77547,-35243,-991);
		gcall.Stepto(-77782,-35333,-992);
		gcall.Stepto(-77882,-35555,-990);
		gcall.Stepto(-77989,-35782,-995);
		gcall.Stepto(-78093,-36002,-995);
		gcall.Stepto(-78201,-36230,-991);
		gcall.Stepto(-78308,-36455,-997);
		gcall.Stepto(-78335,-36511,-998);
		gcall.Stepto(-78304,-36555,-1001);
		gcall.NewSpend(1);
		Sleep(1000);
		gcall.FindThenKill(0,300,modeAoe | modeNormal | modePickup );
		Sleep(4000);
		gcall.Stepto(L"장금봉");
		gcall.DeliverQuests(zid,taskid,L"장금봉");
		Sleep(1000);
		break;
	case 3:
		gcall.NewSpend(2.5);
		gcall.Stepto(-78553,-36536,-995);
		gcall.Stepto(-78757,-36567,-997);
		gcall.Stepto(-79001,-36600,-999);
		gcall.Stepto(-79243,-36632,-1006);
		gcall.Stepto(-79494,-36660,-1007);
		gcall.Stepto(-79740,-36688,-1007);
		gcall.Stepto(-79849,-36700,-1007);
		gcall.Stepto(-80030,-36722,-1007);
		gcall.Stepto(-80265,-36802,-1007);
		gcall.Stepto(-80487,-36862,-1007);
		gcall.Stepto(-80696,-36999,-1007);
		gcall.Stepto(-80884,-37156,-1007);
		gcall.Stepto(-80908,-37395,-1007);
		gcall.Stepto(-80835,-37634,-1005);
		gcall.Stepto(-80824,-37886,-1005);
		gcall.Stepto(-80809,-38131,-1001);
		gcall.Stepto(-80795,-38380,-997);
		gcall.Stepto(-80784,-38624,-994);
		gcall.Stepto(-80806,-38877,-995);
		gcall.Stepto(-80831,-39120,-996);
		gcall.Stepto(-80841,-39370,-998);
		gcall.Stepto(-80840,-39511,-1000);
		gcall.NewSpend(1);
		gcall.Stepto(-80840,-39515,-1000);
		gcall.Stepto(-80844,-39512,-1000);
		Sleep(2000);
		break;
	case 4:
		gcall.NewSpend(2.5);
		gcall.Stepto(-80839,-39231,-998);
		gcall.Stepto(-80837,-39206,-998);
		gcall.Stepto(-80807,-38796,-995);
		gcall.Stepto(-80808,-38359,-997);
		gcall.Stepto(-80826,-37924,-1005);
		gcall.Stepto(-80819,-37497,-1007);
		gcall.Stepto(-80733,-37110,-1007);
		gcall.Stepto(-80579,-37006,-1007);
		gcall.Stepto(-80358,-36888,-1007);
		gcall.Stepto(-80124,-36803,-1007);
		gcall.Stepto(-79882,-36751,-1007);
		gcall.Stepto(-79637,-36703,-1007);
		gcall.Stepto(-79392,-36664,-1007);
		gcall.Stepto(-79149,-36627,-1003);
		gcall.Stepto(-78901,-36590,-997);
		gcall.Stepto(-78656,-36554,-996);
		gcall.Stepto(-78419,-36490,-996);
		gcall.Stepto(-78229,-36333,-994);
		gcall.Stepto(-78109,-36114,-994);
		gcall.Stepto(-77992,-35896,-996);
		gcall.Stepto(-77877,-35680,-989);
		gcall.Stepto(-77758,-35458,-987);
		gcall.Stepto(-77601,-35269,-991);
		gcall.Stepto(-77369,-35193,-991);
		gcall.Stepto(-77124,-35150,-993);
		gcall.Stepto(-76877,-35110,-983);
		gcall.Stepto(-76632,-35071,-985);
		gcall.Stepto(-76392,-35029,-981);
		gcall.Stepto(-76159,-34947,-975);
		gcall.Stepto(-75940,-34826,-984);
		gcall.Stepto(-75794,-34700,-981);
		gcall.Stepto(-75743,-34407,-981);
		gcall.Stepto(-75683,-33971,-977);
		gcall.Stepto(-75592,-33549,-939);
		gcall.Stepto(-75565,-33431,-930);
		gcall.Stepto(-75495,-33198,-978);
		gcall.Stepto(-75439,-33005,-1041);
		gcall.Stepto(-75366,-32737,-1122);
		gcall.NewSpend(1);
		gcall.Stepto(-75268,-32459,-1134);
		gcall.Stepto(-75032,-32104,-1070);
		gcall.Stepto(-74628,-31966,-959);
		gcall.Stepto(-74204,-32034,-822);
		gcall.Stepto(-73777,-32109,-660);
		gcall.Stepto(-73619,-32129,-591);
		gcall.Stepto(-73394,-32203,-556);
		gcall.WaitPlans();
		gcall.Stepto(-73087,-32304,-627);
		gcall.Stepto(-72671,-32435,-622);
		gcall.NewSpend(2.5);
		gcall.Stepto(-72251,-32572,-628);
		gcall.Stepto(-71855,-32708,-641);
		gcall.Stepto(-71436,-32853,-654);
		gcall.Stepto(-71412,-32871,-655);
		gcall.Stepto(-71287,-33230,-658);
		gcall.Stepto(-71146,-33630,-660);
		gcall.Stepto(-71114,-33719,-660);
		gcall.Stepto(-71089,-34036,-661);
		gcall.Stepto(-71067,-34456,-661);
		gcall.Stepto(-71060,-34581,-660);
		gcall.Stepto(-71038,-35013,-656);
		gcall.Stepto(-71031,-35140,-655);
		gcall.Stepto(-71061,-35345,-652);
		gcall.Stepto(-71086,-35507,-650);
		gcall.Stepto(-71144,-35649,-648);
		gcall.Stepto(-71156,-35673,-647);
		gcall.Stepto(-71367,-35684,-639);
		Sleep(1000);
		gcall.DeliverQuests(zid,taskid,L"지혜");
		Sleep(1000);
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

void TaskScript::Task_507(int zid,int taskid)
{
	switch (taskid)
	{
	case 1:
		gcall.FenJieByConfig();
		Sleep(1000);
		gcall.SortBag();
		gcall.NewSpend(2.5);
		gcall.Stepto(-71041,-36075,-646);
		gcall.Stepto(-70989,-36189,-647);
		gcall.Stepto(-70856,-36406,-651);
		gcall.Stepto(-70725,-36616,-657);
		gcall.Stepto(-70562,-36794,-654);
		gcall.Stepto(-70446,-36843,-645);
		gcall.Stepto(-70196,-36867,-628);
		gcall.Stepto(-69949,-36834,-612);
		gcall.Stepto(-69707,-36802,-588);
		gcall.Stepto(-69462,-36768,-560);
		gcall.Stepto(-69207,-36771,-530);
		gcall.Stepto(-68964,-36800,-499);
		gcall.Stepto(-68718,-36852,-473);
		gcall.Stepto(-68480,-36915,-435);
		gcall.Stepto(-68239,-36978,-403);
		gcall.Stepto(-68016,-37075,-382);
		gcall.Stepto(-67779,-37166,-365);
		gcall.Stepto(-67548,-37252,-351);
		gcall.Stepto(-67319,-37338,-336);
		gcall.Stepto(-67086,-37425,-323);
		gcall.Stepto(-66859,-37509,-317);
		gcall.Stepto(-66615,-37597,-313);
		gcall.NewSpend(1);
		gcall.Stepto(-66386,-37682,-306);
		gcall.Stepto(-66205,-37753,-304);
		gcall.Stepto(-65813,-37937,-280);
		gcall.Stepto(-65429,-38138,-263);
		gcall.Stepto(-65052,-38340,-263);
		gcall.Stepto(-64822,-38484,-280);
		Sleep(2000);
		gcall.Stepto(-64608,-38641,-302);
		gcall.WaitPlans();
		gcall.Stepto(-64443,-38803,-326);
		gcall.NewSpend(2.5);
		gcall.Stepto(-64285,-38976,-346);
		gcall.Stepto(-64119,-39114,-364);
		gcall.Stepto(-63725,-39306,-384);
		gcall.Stepto(-63307,-39409,-393);
		gcall.Stepto(-62868,-39367,-411);
		gcall.Stepto(-62492,-39186,-417);
		gcall.Stepto(-62220,-38846,-400);
		gcall.Stepto(-62054,-38635,-380);
		gcall.Stepto(-61899,-38435,-362);
		gcall.Stepto(-61740,-38250,-339);
		gcall.Stepto(-61564,-38074,-315);
		gcall.Stepto(-61386,-37899,-301);
		gcall.Stepto(-61201,-37737,-284);
		gcall.Stepto(-60994,-37600,-265);
		gcall.Stepto(-60779,-37472,-249);
		gcall.Stepto(-60564,-37346,-238);
		gcall.Stepto(-60359,-37225,-224);
		gcall.Stepto(-60138,-37098,-218);
		gcall.Stepto(-59922,-36977,-211);
		gcall.Stepto(-59709,-36848,-208);
		gcall.Stepto(-59502,-36706,-206);
		gcall.Stepto(-59295,-36569,-203);
		gcall.Stepto(-59098,-36423,-187);
		gcall.Stepto(-58899,-36265,-161);
		gcall.Stepto(-58708,-36113,-129);
		gcall.Stepto(-58524,-35963,-93);
		gcall.Stepto(-58391,-35926,-75);
		gcall.Stepto(-58146,-35914,-42);
		gcall.Stepto(-57896,-35912,-11);
		gcall.Stepto(-57653,-35937,4);
		gcall.Stepto(-57404,-35974,10);
		gcall.Stepto(-57162,-36019,11);
		gcall.Stepto(-56924,-36098,15);
		gcall.Stepto(-56704,-36190,7);
		gcall.Stepto(-56469,-36291,-5);
		gcall.Stepto(-56252,-36415,-10);
		gcall.Stepto(-56055,-36555,-18);
		gcall.Stepto(-55870,-36731,-24);
		gcall.Stepto(-55693,-36901,-28);
		gcall.Stepto(-55515,-37079,-28);
		gcall.Stepto(-55341,-37254,-31);
		gcall.Stepto(-55143,-37401,-34);
		gcall.Stepto(-54939,-37538,-40);
		gcall.Stepto(-54715,-37654,-57);
		gcall.Stepto(-54491,-37763,-77);
		gcall.Stepto(-54267,-37870,-90);
		gcall.Stepto(-54043,-37976,-96);
		gcall.Stepto(-53835,-38094,-107);
		gcall.Stepto(-53616,-38228,-127);
		gcall.Stepto(-53421,-38352,-142);
		gcall.Stepto(-53420,-38352,-142);
		gcall.Stepto(-53274,-38496,-170);
		gcall.Stepto(-53097,-38679,-201);
		gcall.NewSpend(1);
		gcall.Stepto(-52941,-38866,-239);
		gcall.Stepto(-52785,-39056,-248);
		gcall.Stepto(-52639,-39251,-241);
		gcall.Stepto(-52488,-39455,-163);
		gcall.Stepto(-52282,-39589,-164);
		gcall.Stepto(-52163,-39641,-145);
		gcall.Stepto(-52124,-39750,-140);
		gcall.WaitPlans();
		gcall.Stepto(-52082,-39849,-142);
		gcall.Stepto(-52150,-39950,-142);
		gcall.Stepto(-52204,-39997,-142);
		Sleep(1000);
		gcall.DeliverQuests(zid,taskid,L"박범진");
		Sleep(1000);
		break;
	case 2:
		gcall.Stepto(-52185,-39931,-142);
		gcall.DeliverQuests(zid,taskid,L"한시랑");
		Sleep(1000);
		break;
	case 3:
		gcall.NewSpend(2.5);
		gcall.Stepto(-51773,-38790,-159);
		gcall.Stepto(-51961,-38952,-151);
		gcall.Stepto(-52144,-39116,-151);
		gcall.Stepto(-52327,-39283,-155);
		gcall.Stepto(-52463,-39406,-168);
		gcall.Stepto(-52461,-39403,-168);
		gcall.Stepto(-52710,-39238,-247);
		gcall.Stepto(-52925,-39110,-242);
		gcall.Stepto(-53147,-39009,-210);
		gcall.Stepto(-53391,-38954,-166);
		gcall.Stepto(-53637,-38926,-150);
		gcall.Stepto(-53770,-38862,-130);
		gcall.Stepto(-53825,-38723,-108);
		gcall.Stepto(-54054,-38350,-68);
		gcall.Stepto(-54366,-38046,-88);
		gcall.Stepto(-54708,-37779,-57);
		gcall.Stepto(-55054,-37512,-36);
		gcall.Stepto(-55374,-37228,-31);
		gcall.Stepto(-55598,-37016,-29);
		gcall.Stepto(-55757,-36874,-27);
		gcall.Stepto(-55949,-36715,-22);
		gcall.Stepto(-56139,-36558,-17);
		gcall.Stepto(-56343,-36409,-12);
		gcall.Stepto(-56554,-36275,-3);
		gcall.Stepto(-56637,-36224,3);
		gcall.Stepto(-56754,-36154,10);
		gcall.Stepto(-56964,-36027,16);
		gcall.Stepto(-57236,-36071,13);
		gcall.Stepto(-57201,-36006,11);
		gcall.Stepto(-57054,-35806,44);
		gcall.Stepto(-56887,-35624,120);
		gcall.Stepto(-56700,-35457,153);
		gcall.Stepto(-56499,-35312,168);
		gcall.Stepto(-56291,-35177,207);
		gcall.Stepto(-56085,-35039,300);
		gcall.Stepto(-55881,-34897,394);
		gcall.Stepto(-55795,-34749,432);
		gcall.Stepto(-55834,-34632,460);
		gcall.Stepto(-55850,-34587,474);
		gcall.NewSpend(1);
		gcall.Stepto(-55844,-34628,463);
		gcall.Stepto(-55853,-34601,471);
		gcall.Stepto(-55920,-34414,519);
		gcall.Stepto(-55987,-34229,560);
		gcall.Stepto(-56025,-34035,587);
		gcall.Stepto(-56025,-33837,607);
		gcall.Stepto(-56024,-33638,630);
		gcall.Stepto(-56028,-33552,640);
		gcall.sendcall(id_msg_attack, (LPVOID)0x5E06);//3
		Sleep(1500);
		gcall.sendcall(id_msg_attack, (LPVOID)0x5DE8);//z
		Sleep(800);
		gcall.Kill_Tab();
		gcall.TurnToNear(500);
		gcall.sendcall(id_msg_attack, (LPVOID)0x5e74);//1
		gcall.FindThenKill(0,400,modeAoe | modeNormal | modePickup);


		//2
		gcall.Stepto(-56280,-32811,724);
		gcall.Stepto(-56282,-32808,724);
		gcall.Stepto(-56360,-32627,734);
		gcall.Stepto(-56431,-32442,743);
		gcall.Stepto(-56504,-32252,755);
		gcall.Stepto(-56592,-32020,785);
		gcall.Stepto(-56681,-31789,825);
		gcall.Stepto(-56770,-31556,871);
		gcall.Stepto(-56937,-31406,906);
		gcall.Stepto(-57020,-31397,910);
		gcall.FindThenKill(0,300,modeAoe | modeNormal | modePickup);

		//3
		gcall.NewSpend(2.5);
		gcall.Stepto(-57158,-31519,905);
		gcall.Stepto(-57161,-31603,900);
		gcall.Stepto(-57169,-31801,873);
		gcall.Stepto(-57178,-32000,842);
		gcall.Stepto(-57279,-32169,789);
		gcall.Stepto(-57394,-32343,666);
		gcall.Stepto(-57521,-32554,542);
		gcall.Stepto(-57650,-32765,502);
		gcall.Stepto(-57780,-32976,483);
		gcall.Stepto(-57923,-33180,476);
		gcall.Stepto(-58072,-33381,479);
		gcall.Stepto(-58233,-33564,498);
		gcall.Stepto(-58417,-33734,493);
		gcall.Stepto(-58633,-33824,484);
		gcall.NewSpend(1);
		gcall.Stepto(-58724,-33822,482);
		
		gcall.sendcall(id_msg_attack, (LPVOID)0x5E06);//3
		Sleep(1500);
		gcall.sendcall(id_msg_attack, (LPVOID)0x5DE8);//z
		Sleep(800);
		gcall.Kill_Tab();
		gcall.TurnToNear(500);
		gcall.sendcall(id_msg_attack, (LPVOID)0x5e74);//1
		gcall.FindThenKill(0,400,modeAoe | modeNormal | modePickup);

		//4
		gcall.Stepto(-58784,-34187,480);
		gcall.Stepto(-58847,-34204,480);
		gcall.Stepto(-59078,-34293,465);
		gcall.Stepto(-59302,-34400,405);
		gcall.Stepto(-59523,-34513,352);
		gcall.Stepto(-59749,-34616,314);
		gcall.Stepto(-59977,-34713,295);
		gcall.Stepto(-60206,-34811,292);
		gcall.Stepto(-60239,-34825,291);
		gcall.FindThenKill(0,400,modeAoe | modeNormal | modePickup);


		//5
		gcall.NewSpend(2.5);
		gcall.Stepto(-60204,-34600,317);
		gcall.Stepto(-60171,-34543,325);
		gcall.Stepto(-60046,-34328,365);
		gcall.Stepto(-59923,-34115,429);
		gcall.Stepto(-59798,-33901,486);
		gcall.Stepto(-59680,-33697,526);
		gcall.Stepto(-59570,-33475,575);
		gcall.Stepto(-59485,-33241,640);
		gcall.Stepto(-59398,-33009,684);
		gcall.Stepto(-59266,-32803,688);
		gcall.Stepto(-59123,-32602,704);
		gcall.Stepto(-59158,-32369,743);
		gcall.Stepto(-59305,-32169,776);
		gcall.Stepto(-59404,-31940,814);
		gcall.Stepto(-59492,-31712,841);
		gcall.Stepto(-59581,-31478,855);
		gcall.NewSpend(1);
		gcall.Stepto(-59582,-31271,872);
		gcall.Stepto(-59556,-31173,876);
		
		gcall.sendcall(id_msg_attack, (LPVOID)0x5E06);//3
		Sleep(1500);
		gcall.sendcall(id_msg_attack, (LPVOID)0x5DE8);//z
		Sleep(800);
		gcall.Kill_Tab();
		gcall.TurnToNear(500);
		gcall.sendcall(id_msg_attack, (LPVOID)0x5e74);//1
		gcall.FindThenKill(0,400,modeAoe | modeNormal | modePickup);



		//6
		gcall.Stepto(-59807,-31182,884);
		gcall.Stepto(-59856,-31131,894);
		gcall.Stepto(-59993,-30987,920);
		gcall.Stepto(-60145,-30858,951);
		gcall.Stepto(-60292,-30726,980);
		gcall.Stepto(-60330,-30692,987);
		gcall.FindThenKill(0,400,modeAoe | modeNormal | modePickup);


		//7
		gcall.Stepto(-60232,-30352,1015);
		gcall.Stepto(-60216,-30319,1015);
		gcall.Stepto(-60114,-30093,1013);
		gcall.Stepto(-60018,-29864,999);
		gcall.Stepto(-59913,-29640,993);
		gcall.Stepto(-59785,-29428,1000);
		gcall.Stepto(-59699,-29298,1010);
		gcall.FindThenKill(0,400,modeAoe | modeNormal | modePickup);



		//8 不加速
		gcall.Stepto(-59903,-29092,1051);
		gcall.Stepto(-60068,-28907,1080);
		gcall.Stepto(-60180,-28782,1093);
		gcall.Stepto(-60161,-28755,1096);
		gcall.Stepto(-60018,-28553,1117);
		gcall.Stepto(-59875,-28350,1139);
		gcall.Stepto(-59732,-28147,1145);
		gcall.Stepto(-59589,-27945,1147);
		gcall.Stepto(-59451,-27749,1151);
		gcall.Stepto(-59338,-27588,1157);
		gcall.Stepto(-59267,-27488,1169);
		gcall.sendcall(id_msg_attack, (LPVOID)0x5E06);//3
		Sleep(1500);
		gcall.sendcall(id_msg_attack, (LPVOID)0x5DE8);//z
		Sleep(800);
		gcall.Kill_Tab();
		gcall.TurnToNear(500);
		gcall.sendcall(id_msg_attack, (LPVOID)0x5e74);//1
		gcall.FindThenKill(0,400,modeAoe | modeNormal | modePickup);


		//9
		gcall.NewSpend(2.5);
		gcall.Stepto(-59064,-27516,1149);
		gcall.Stepto(-58871,-27672,1100);
		gcall.Stepto(-58679,-27827,1053);
		gcall.Stepto(-58486,-27983,1005);
		gcall.Stepto(-58293,-28139,952);
		gcall.Stepto(-58100,-28295,897);
		gcall.Stepto(-58066,-28520,867);
		gcall.Stepto(-58093,-28766,858);
		gcall.Stepto(-58119,-29013,852);
		gcall.Stepto(-58144,-29260,844);
		gcall.Stepto(-58169,-29505,836);
		gcall.Stepto(-58194,-29752,829);
		gcall.Stepto(-58219,-29999,812);
		gcall.Stepto(-58244,-30246,777);
		gcall.Stepto(-58267,-30490,740);
		gcall.NewSpend(1);
		gcall.Stepto(-58100,-30675,728);
		gcall.Stepto(-58074,-30701,729);
		gcall.FindThenKill(0,400,modeAoe | modeNormal | modePickup);



		gcall.NewSpend(2.5);
		gcall.Stepto(-58080,-31257,634);
		gcall.Stepto(-58085,-31401,623);
		gcall.Stepto(-58074,-31599,603);
		gcall.Stepto(-58060,-31797,589);
		gcall.Stepto(-58030,-31993,571);
		gcall.Stepto(-57973,-32182,551);
		gcall.Stepto(-57908,-32381,533);
		gcall.Stepto(-57831,-32619,519);
		gcall.Stepto(-57755,-32852,497);
		gcall.Stepto(-57678,-33088,453);
		gcall.Stepto(-57615,-33330,404);
		gcall.Stepto(-57571,-33573,357);
		gcall.Stepto(-57527,-33819,309);
		gcall.Stepto(-57478,-34061,260);
		gcall.Stepto(-57438,-34305,209);
		gcall.Stepto(-57413,-34546,167);
		gcall.Stepto(-57412,-34550,166);
		gcall.randXianlu(0);
		break;
	case 4:
		gcall.NewSpend(2.5);
		gcall.Stepto(-55942,-34267,548,20,20,3000);
		gcall.Stepto(-55955,-34479,513,20,20,3000);
		gcall.Stepto(-55982,-34720,463,20,20,3000);
		gcall.Stepto(-55995,-34967,358,20,20,3000);
		gcall.Stepto(-55943,-35209,243);
		gcall.Stepto(-55891,-35457,203);
		gcall.Stepto(-55843,-35695,226);
		gcall.Stepto(-55791,-35941,185);
		gcall.Stepto(-55735,-36184,88);
		gcall.Stepto(-55679,-36426,18);
		gcall.Stepto(-55624,-36666,-9);
		gcall.Stepto(-55545,-36900,-21);
		gcall.Stepto(-55412,-37105,-26);
		gcall.Stepto(-55242,-37289,-30);
		gcall.Stepto(-55056,-37457,-35);
		gcall.Stepto(-54866,-37617,-46);
		gcall.Stepto(-54681,-37773,-60);
		gcall.Stepto(-54480,-37924,-80);
		gcall.Stepto(-54348,-38021,-90);
		gcall.Stepto(-54000,-38274,-76);
		gcall.Stepto(-53638,-38504,-130);
		gcall.Stepto(-53264,-38729,-175);
		gcall.Stepto(-52985,-38897,-235);
		gcall.Stepto(-52867,-38968,-247);
		gcall.NewSpend(1);
		gcall.Stepto(-52663,-39100,-248);
		gcall.Stepto(-52484,-39276,-163);
		gcall.Stepto(-52306,-39455,-165);
		gcall.Stepto(-52172,-39653,-141);
		gcall.Stepto(-52160,-39677,-140);
		Sleep(2000);
		gcall.Stepto(-52138,-39697,-140);
		gcall.WaitPlans();
		gcall.Stepto(-52115,-39745,-140);
		gcall.Stepto(-52097,-39779,-140);
		gcall.Stepto(-52099,-39917,-142);
		gcall.Stepto(-52135,-39941,-142);
		gcall.Stepto(-52283,-39971,-142);
		Sleep(1000);
		gcall.PickupSpecTypeTask(200,0x4,L"소현");
		Sleep(1000);
		break;
	case 5:
		Sleep(1000);
		gcall.DeliverQuests(zid,taskid,L"소현");
		Sleep(1000);
		break;
	case 6:
		if (gcall.GetCityID() != 3009)
		{
			gcall.Stepto(-52306,-39455,-165);
			gcall.Stepto(-52172,-39653,-141);
			gcall.Stepto(-52160,-39677,-140);
		}
		gcall.Stepto(-52191,-39941,-142);
		Sleep(1000);
		gcall.DeliverQuests(zid,taskid,L"한시랑");
		Sleep(1000);
		break;
	case 7:
		break;
	case 8:
		break;
	case 9:
		break;

	}
}

void TaskScript::Task_508(int zid,int taskid)
{
	switch (taskid)
	{
	case 1:
		gcall.NewSpend(2.5);
		gcall.Stepto(-52075,-39827,-142);
		gcall.Stepto(-52126,-39719,-140,30);
		gcall.Stepto(-52289,-39451,-163,30);
		gcall.Stepto(-52537,-39267,-178,30);
		gcall.Stepto(-52811,-39060,-248,30);
		gcall.Stepto(-52994,-38887,-233,30);
		gcall.Stepto(-53163,-38702,-187);
		gcall.Stepto(-53358,-38550,-161);
		gcall.Stepto(-53527,-38435,-138);
		gcall.Stepto(-53887,-38191,-94);
		gcall.Stepto(-54247,-37946,-92);
		gcall.Stepto(-54609,-37701,-65);
		gcall.Stepto(-54969,-37462,-33);
		gcall.Stepto(-55326,-37226,-30);
		gcall.Stepto(-55695,-36981,-27);
		gcall.Stepto(-56047,-36736,-16);
		gcall.Stepto(-56410,-36484,-11);
		gcall.Stepto(-56766,-36251,10);
		gcall.Stepto(-57141,-36028,12);
		gcall.Stepto(-57519,-35804,13);
		gcall.Stepto(-57717,-35571,23);
		gcall.Stepto(-57694,-35391,49);
		gcall.Stepto(-57684,-35137,81);
		gcall.Stepto(-57655,-34894,109);
		gcall.Stepto(-57613,-34649,148);
		gcall.Stepto(-57581,-34404,195);
		gcall.Stepto(-57571,-34153,248);
		gcall.Stepto(-57578,-33907,296);
		gcall.Stepto(-57607,-33656,345);
		gcall.Stepto(-57646,-33412,394);
		gcall.Stepto(-57699,-33175,441);
		gcall.Stepto(-57765,-32929,488);
		gcall.Stepto(-57834,-32693,515);
		gcall.Stepto(-57903,-32458,529);
		gcall.Stepto(-57973,-32215,548);
		gcall.Stepto(-58044,-31977,573);
		gcall.Stepto(-58113,-31741,594);
		gcall.Stepto(-58161,-31498,612);
		gcall.Stepto(-58192,-31248,632);
		gcall.Stepto(-58214,-31066,656);
		gcall.Stepto(-58243,-30639,714);
		gcall.Stepto(-58264,-30201,783);
		gcall.Stepto(-58253,-29762,824);
		gcall.Stepto(-58209,-29342,838);
		gcall.NewSpend(1);
		gcall.Stepto(-58120,-28914,855);
		gcall.Stepto(-57864,-28365,874);
		Sleep(2000);
		gcall.Shunyi(L"2-9-1");
		Sleep(2000);
		gcall.sendcall(id_msg_OverShunyi,(LPVOID)0);
		Sleep(4000);
		gcall.Stepto(-57239,-26978,1682);
		gcall.Stepto(-57159,-26756,1703);
		Sleep(2000);
		gcall.Stepto(-57045,-26626,1723);
		gcall.WaitPlans();
		
		gcall.Stepto(-56913,-26486,1733,30,30,3000);
		gcall.Stepto(-56194,-25326,1758,30,30,3000);
		gcall.NewSpend(2.5);
		gcall.Stepto(-56104,-25037,1766,30,30,3000);
		gcall.Stepto(-56110,-24850,1771,30,30,3000);
		gcall.Stepto(-56126,-24622,1781,30,30,3000);
		gcall.Stepto(-56126,-24622,1781,30,30,3000);
		gcall.Stepto(-56126,-24618,1781);
		gcall.Stepto(-56157,-24290,1792);
		gcall.Stepto(-56217,-23841,1809);
		gcall.Stepto(-56268,-23407,1829);
		gcall.Stepto(-56301,-22977,1861);
		gcall.Stepto(-56355,-22554,1903);
		gcall.Stepto(-56422,-22181,1951);
		gcall.Stepto(-56470,-21991,1976);
		gcall.Stepto(-56536,-21803,2000);
		gcall.Stepto(-56637,-21631,2026);
		gcall.Stepto(-56767,-21496,2052);
		gcall.Stepto(-56929,-21341,2096);
		gcall.Stepto(-57117,-21187,2150);
		gcall.Stepto(-57321,-21047,2208);
		gcall.Stepto(-57520,-20911,2267);
		gcall.Stepto(-57728,-20756,2320);
		gcall.Stepto(-57921,-20604,2364);
		gcall.Stepto(-58108,-20456,2405);
		gcall.Stepto(-58316,-20295,2458);
		gcall.Stepto(-58513,-20147,2495);
		gcall.Stepto(-58702,-19992,2526);
		gcall.Stepto(-58856,-19837,2563);
		gcall.Stepto(-58984,-19686,2608);
		gcall.Stepto(-59104,-19527,2657);
		gcall.Stepto(-59199,-19355,2701);
		gcall.Stepto(-59270,-19169,2755);
		gcall.Stepto(-59340,-18945,2819);
		gcall.Stepto(-59375,-18703,2907);
		gcall.Stepto(-59374,-18449,2965);
		gcall.Stepto(-59368,-18203,3035);
		gcall.Stepto(-59403,-17958,3088);
		gcall.Stepto(-59511,-17741,3132);
		gcall.Stepto(-59706,-17581,3186);
		gcall.Stepto(-59921,-17466,3240);
		gcall.Stepto(-60145,-17354,3286);
		gcall.Stepto(-60379,-17276,3313);
		gcall.Stepto(-60577,-17256,3324);
		gcall.Stepto(-61021,-17247,3333);
		gcall.Stepto(-61454,-17273,3334);
		gcall.Stepto(-61870,-17391,3338);
		gcall.Stepto(-62291,-17492,3350);
		gcall.Stepto(-62713,-17573,3365);
		gcall.Stepto(-63131,-17651,3364);
		gcall.Stepto(-63575,-17732,3363);
		gcall.Stepto(-63994,-17798,3364);
		gcall.Stepto(-64437,-17846,3358);
		gcall.Stepto(-64863,-17896,3352);
		gcall.Stepto(-65044,-17956,3350);
		gcall.Stepto(-65191,-17927,3350);
		gcall.Stepto(-65382,-17882,3351);
		gcall.Stepto(-65572,-17823,3352);
		gcall.Stepto(-65763,-17755,3353);
		gcall.Stepto(-65981,-17677,3353);
		gcall.Stepto(-66198,-17598,3351);
		gcall.NewSpend(1);
		gcall.Stepto(-66445,-17495,3341);
		gcall.Stepto(-66671,-17401,3368);
		gcall.Stepto(-66856,-17316,3405);
		
		break;
	case 2:
		gcall.Stepto(-66856,-17316,3405);
		Sleep(3000);
		gcall.Stepto(-67003,-17240,3378);
		gcall.Stepto(-67303,-17140,3307);
		gcall.WaitPlans();
		gcall.Stepto(-67313,-17137,3301);
		gcall.Stepto(-67550,-17064,3178);
		gcall.Stepto(-67788,-16982,3047);
		gcall.Stepto(-68014,-16904,2930);
		gcall.Stepto(-68245,-16836,2814);
		gcall.Stepto(-68489,-16768,2705);
		gcall.NewSpend(1);
		gcall.Stepto(-68727,-16715,2699);
		gcall.Stepto(-68784,-16703,2699);
		Sleep(15000);
		gcall.Stepto(-69305,-16544,2678);
		gcall.FindThenKill(0,300,modeAoe | modeNormal);
		gcall.Stepto(-68949,-16640,2698);
		gcall.Stepto(-69180,-16555,2677);
		gcall.Stepto(-69430,-16540,2678);
		gcall.Stepto(-69677,-16524,2685);
		gcall.Stepto(-69925,-16530,2685);
		gcall.Stepto(-70162,-16612,2679);
		gcall.Stepto(-70227,-16702,2683);
		gcall.Stepto(-70259,-16781,2684);
		gcall.Stepto(-70347,-17011,2683);
		gcall.Stepto(-70415,-17231,2686);
		gcall.Stepto(-70489,-17477,2683);
		gcall.Stepto(-70575,-17718,2681);
		gcall.Stepto(-70731,-17915,2677);
		gcall.Stepto(-70893,-18097,2659);
		gcall.Stepto(-71031,-18257,2658);
		Sleep(1000);
		gcall.FindThenKill(0,300,modeAoe | modeNormal);
		gcall.Stepto(-71305,-18420,2654);
		gcall.Stepto(-71349,-18413,2654);
		gcall.Stepto(-71589,-18384,2655);
		gcall.Stepto(-71833,-18354,2651);
		gcall.Stepto(-72073,-18282,2646);
		gcall.Stepto(-72329,-18220,2648);
		gcall.Stepto(-72564,-18176,2650);
		gcall.Stepto(-72693,-18140,2648);
		Sleep(1000);
		gcall.FindThenKill(0,300,modeAoe | modeNormal);
		gcall.Stepto(-73065,-18181,2651);
		gcall.Stepto(-73099,-18224,2653);
		gcall.Stepto(-73249,-18422,2650);
		gcall.Stepto(-73399,-18616,2654);
		gcall.Stepto(-73552,-18810,2668);
		gcall.Stepto(-73707,-19006,2657);
		gcall.Stepto(-73846,-19182,2651);
		gcall.Stepto(-73995,-19373,2654);
		gcall.Stepto(-74059,-19468,2657);
		gcall.Stepto(-74192,-19664,2666);
		gcall.Stepto(-74193,-19666,2666);
		Sleep(1000);
		gcall.Stepto(L"최진아");
		Sleep(1000);
		gcall.sendcall(id_msg_attack, (LPVOID)0x5E06);//3
		Sleep(1500);
		gcall.sendcall(id_msg_attack, (LPVOID)0x5DE8);//z
		Sleep(800);
		gcall.Kill_Tab();
		gcall.TurnToNear(500);
		gcall.sendcall(id_msg_attack, (LPVOID)0x5e74);//1
		gcall.FindThenKill(0,500,modeAoe | modeNormal | modePickup);
		gcall.Stepto(L"최진아");
		Sleep(1000);
		gcall.DeliverQuests(zid,taskid,L"최진아");
		Sleep(1000);
		gcall.Stepto(-74193,-19666,2666);
		Sleep(1000);
		gcall.DeliverQuests(zid,taskid,L"최진아");
		Sleep(1000);
		break;
	case 3:
		//过滤怪物(최진아,1);
		Sleep(1000);
		gcall.Stepto(-74246,-19708,2667);
		gcall.Stepto(-74368,-19724,2664);
		gcall.Stepto(-74615,-19750,2653);
		gcall.Stepto(-74862,-19770,2655);
		gcall.Stepto(-75107,-19825,2679);
		gcall.Stepto(-75290,-19981,2777);
		gcall.Stepto(-75362,-20217,2881);
		gcall.Stepto(-75381,-20464,2958);
		gcall.Stepto(-75346,-20710,2997);
		gcall.Stepto(-75308,-20957,3039);
		gcall.Stepto(-75270,-21201,3059);
		gcall.FindThenKill(0,600,modeAoe | modeNormal | modePickup);
		gcall.Stepto(-75235,-21444,3067);
		gcall.Stepto(-75297,-21683,3081);
		gcall.Stepto(-75436,-21893,3071);
		gcall.Stepto(-75460,-21927,3068);
		gcall.sendcall(id_msg_attack, (LPVOID)0x5E06);//3
		Sleep(1500);
		gcall.sendcall(id_msg_attack, (LPVOID)0x5DE8);//z
		Sleep(800);
		gcall.Kill_Tab();
		gcall.TurnToNear(500);
		gcall.sendcall(id_msg_attack, (LPVOID)0x5e74);//1
		gcall.FindThenKill(0,500,modeAoe | modeNormal | modePickup);
		Sleep(2000);
		gcall.FindThenKill(0,500,modeAoe | modeNormal | modePickup);
		Sleep(1000);
		gcall.sendcall(id_msg_attack, (LPVOID)0x5DFC);//v
		gcall.Stepto(-75643,-22100,3058);
		gcall.Stepto(-75668,-22122,3058);
		gcall.Stepto(-75850,-22295,3058);
		gcall.Stepto(-76036,-22457,3059);
		gcall.Stepto(-76238,-22601,3055);
		gcall.Stepto(-76311,-22632,3053);
		gcall.Stepto(-76535,-22568,3055);
		gcall.Stepto(-76769,-22490,3054);
		gcall.Stepto(-77000,-22385,3056);
		gcall.Stepto(-77103,-22336,3058);
		Sleep(2000);
		gcall.FindThenKill(0,500,modeAoe | modeNormal | modePickup);
		Sleep(2000);
		gcall.FindThenKill(0,500,modeAoe | modeNormal | modePickup);
		Sleep(1000);
		gcall.sendcall(id_msg_attack, (LPVOID)0x5DFC);//v
		gcall.Stepto(-77207,-22269,3059);
		gcall.Stepto(-77416,-22133,3060);
		gcall.Stepto(-77614,-22005,3059);
		gcall.Stepto(-77628,-21995,3059);
		Sleep(2000);
		gcall.FindThenKill(0,500,modeAoe | modeNormal | modePickup);
		Sleep(2000);
		gcall.FindThenKill(0,500,modeAoe | modeNormal | modePickup);
		Sleep(1000);
		gcall.sendcall(id_msg_attack, (LPVOID)0x5DFC);//v
		gcall.Stepto(-77738,-21933,3058);
		gcall.Stepto(-77959,-21811,3059);
		gcall.Stepto(-78170,-21688,3062);
		gcall.Stepto(-78380,-21553,3063);
		gcall.Stepto(-78583,-21419,3055);
		gcall.Stepto(-78748,-21292,3061);
		gcall.Stepto(-78804,-21253,3064);
		gcall.Stepto(-79007,-21109,3070);
		gcall.Stepto(-79020,-21099,3071);
		Sleep(2000);
		break;
	case 4:
		gcall.NewSpend(2.5);
		gcall.Stepto(-67144,-17210,3346);
		gcall.Stepto(-67364,-17129,3276);
		gcall.Stepto(-67599,-17049,3152);
		gcall.Stepto(-67834,-16969,3024);
		gcall.Stepto(-68068,-16889,2903);
		gcall.Stepto(-68303,-16809,2783);
		gcall.Stepto(-68538,-16730,2702);
		gcall.Stepto(-68772,-16647,2698);
		gcall.Stepto(-69007,-16566,2698);
		gcall.Stepto(-69243,-16491,2677);
		gcall.Stepto(-69483,-16431,2686);
		gcall.Stepto(-69724,-16373,2691);
		gcall.Stepto(-69735,-16370,2691);
		gcall.Stepto(-69744,-16378,2691);
		gcall.Stepto(-69937,-16534,2684);
		gcall.Stepto(-70131,-16689,2680);
		gcall.Stepto(-70324,-16845,2684);
		gcall.Stepto(-70384,-16893,2685);
		gcall.Stepto(-70400,-17045,2685);
		gcall.Stepto(-70429,-17291,2686);
		gcall.Stepto(-70456,-17529,2683);
		gcall.Stepto(-70502,-17615,2682);
		gcall.Stepto(-70622,-17832,2678);
		gcall.Stepto(-70716,-18004,2673);
		gcall.Stepto(-70821,-18126,2658);
		gcall.Stepto(-70982,-18314,2654);
		gcall.Stepto(-71147,-18505,2650);
		gcall.Stepto(-71198,-18563,2648);
		gcall.Stepto(-71436,-18552,2648);
		gcall.Stepto(-71676,-18494,2650);
		gcall.Stepto(-71906,-18400,2647);
		gcall.Stepto(-72135,-18306,2644);
		gcall.Stepto(-72370,-18226,2650);
		gcall.Stepto(-72605,-18148,2649);
		gcall.Stepto(-72833,-18073,2646);
		gcall.Stepto(-72835,-18072,2646);
		gcall.Stepto(-72861,-18091,2647);
		gcall.Stepto(-73059,-18240,2653);
		gcall.Stepto(-73258,-18389,2649);
		gcall.Stepto(-73456,-18538,2653);
		gcall.Stepto(-73623,-18664,2664);
		gcall.Stepto(-73685,-18756,2669);
		gcall.Stepto(-73823,-18962,2668);
		gcall.Stepto(-73964,-19171,2654);
		gcall.Stepto(-74102,-19377,2655);
		gcall.Stepto(-74241,-19583,2665);
		gcall.Stepto(-74338,-19617,2666);
		gcall.Stepto(-74577,-19682,2658);
		gcall.Stepto(-74815,-19746,2655);
		gcall.Stepto(-75057,-19812,2663);
		gcall.Stepto(-75296,-19877,2735);
		gcall.Stepto(-75309,-19895,2747);
		gcall.Stepto(-75354,-20143,2845);
		gcall.Stepto(-75399,-20387,2933);
		gcall.Stepto(-75428,-20548,2980);
		gcall.Stepto(-75355,-20691,2992);
		gcall.Stepto(-75243,-20912,3035);
		gcall.Stepto(-75130,-21133,3066);
		gcall.Stepto(-75049,-21294,3068);
		gcall.Stepto(-75058,-21307,3068);
		gcall.Stepto(-75197,-21513,3071);
		gcall.Stepto(-75336,-21718,3081);
		gcall.Stepto(-75475,-21923,3068);
		gcall.Stepto(-75614,-22129,3057);
		gcall.Stepto(-75756,-22337,3053);
		gcall.Stepto(-75895,-22543,3054);
		gcall.Stepto(-75971,-22654,3054);
		gcall.Stepto(-76069,-22662,3053);
		gcall.Stepto(-76317,-22680,3051);
		gcall.Stepto(-76564,-22699,3053);
		gcall.Stepto(-76645,-22705,3057);
		gcall.Stepto(-76739,-22639,3056);
		gcall.Stepto(-76947,-22496,3056);
		gcall.Stepto(-77154,-22360,3058);
		gcall.Stepto(-77362,-22224,3060);
		gcall.Stepto(-77569,-22088,3057);
		gcall.Stepto(-77766,-21960,3057);
		gcall.Stepto(-77974,-21824,3058);
		gcall.Stepto(-78182,-21689,3062);
		gcall.Stepto(-78298,-21606,3065);
		gcall.Stepto(-78491,-21443,3059);
		gcall.Stepto(-78678,-21285,3058);
		gcall.Stepto(-78868,-21124,3067);
		gcall.NewSpend(1);
		gcall.Stepto(-79161,-20878,3086);
		gcall.Stepto(-79335,-20650,3103);
		gcall.Stepto(-79679,-20507,3140);
		Sleep(2000);
		//过滤怪物(최진아,1);
		gcall.FindThenKill(0,1000,modeAoe | modeNormal | modePickup );
		gcall.Stepto(-79871,-20751,3130);
		gcall.Stepto(-79792,-20657,3132);
		gcall.Stepto(-79730,-20589,3135);
		gcall.Stepto(-79709,-20559,3137);
		Sleep(1000);
		gcall.PickupSpecTypeTask(200,0x4,L"거래장부");
		Sleep(1000);
		break;
	case 5:
		gcall.Stepto(L"최진아");
		Sleep(1000);
		gcall.DeliverQuests(zid,taskid,L"최진아");
		Sleep(1000);
		break;
	case 6:
		Sleep(1000);
		break;
	case 7:
		break;
	case 8:
		break;
	case 9:
		break;

	}
}

void TaskScript::Task_509(int zid,int taskid)
{
	switch (taskid)
	{
	case 1:
		gcall.NewSpend(2.5);
		gcall.Stepto(-79423,-20572,3114);
		gcall.Stepto(-79399,-20572,3112);
		gcall.Stepto(-79113,-20860,3085);
		gcall.Stepto(-78920,-21218,3066);
		gcall.Stepto(-78545,-21456,3057);
		gcall.Stepto(-78184,-21686,3063);
		gcall.Stepto(-77817,-21920,3057);
		gcall.Stepto(-77447,-22155,3059);
		gcall.Stepto(-77083,-22377,3057);
		gcall.Stepto(-76678,-22536,3055);
		gcall.Stepto(-76250,-22580,3055);
		gcall.Stepto(-75849,-22448,3054);
		gcall.Stepto(-75569,-22132,3057);
		gcall.Stepto(-75303,-21773,3078);
		gcall.Stepto(-75166,-21579,3074);
		gcall.Stepto(-75020,-21365,3066);
		gcall.Stepto(-74885,-21160,3069);
		gcall.Stepto(-74749,-20949,3066);
		gcall.Stepto(-74624,-20741,3062);
		gcall.Stepto(-74505,-20519,2755);
		gcall.Stepto(-74389,-20302,2644);
		gcall.Stepto(-74272,-20082,2659);
		gcall.Stepto(-74156,-19860,2662);
		gcall.Stepto(-74042,-19641,2663);
		gcall.Stepto(-73925,-19418,2656);
		gcall.Stepto(-73814,-19202,2650);
		gcall.Stepto(-73694,-18978,2659);
		gcall.Stepto(-73565,-18767,2655);
		gcall.Stepto(-73419,-18568,2654);
		gcall.Stepto(-73264,-18376,2649);
		gcall.Stepto(-73083,-18213,2652);
		gcall.Stepto(-72839,-18205,2651);
		gcall.Stepto(-72590,-18203,2651);
		gcall.Stepto(-72378,-18262,2652);
		gcall.Stepto(-72193,-18322,2646);
		gcall.Stepto(-71992,-18380,2644);
		gcall.Stepto(-71817,-18423,2649);
		gcall.Stepto(-71612,-18458,2652);
		gcall.Stepto(-71383,-18479,2651);
		gcall.Stepto(-71174,-18358,2656);
		gcall.Stepto(-70998,-18171,2666);
		gcall.Stepto(-70861,-18038,2665);
		gcall.Stepto(-70736,-17881,2676);
		gcall.Stepto(-70637,-17714,2679);
		gcall.Stepto(-70560,-17532,2682);
		gcall.Stepto(-70486,-17356,2685);
		gcall.Stepto(-70403,-17161,2686);
		gcall.Stepto(-70292,-16907,2683);
		gcall.Stepto(-70129,-16720,2680);
		gcall.Stepto(-69953,-16584,2678);
		gcall.Stepto(-69690,-16458,2687);
		gcall.Stepto(-69451,-16519,2680);
		gcall.Stepto(-69210,-16552,2677);
		gcall.Stepto(-69031,-16585,2693);
		gcall.Stepto(-68839,-16635,2698);
		gcall.Stepto(-68654,-16691,2699);
		gcall.Stepto(-68468,-16747,2704);
		gcall.Stepto(-68282,-16810,2791);
		gcall.Stepto(-68113,-16862,2875);
		gcall.Stepto(-67862,-16921,3003);
		gcall.Stepto(-67599,-16998,3144);
		gcall.Stepto(-67380,-17120,3267);
		gcall.Stepto(-67202,-17191,3336);
		gcall.Stepto(-66965,-17262,3404);
		gcall.Stepto(-66932,-17272,3405);
		gcall.Stepto(-66523,-17406,3336);
		gcall.Stepto(-66521,-17408,3336);
		gcall.Stepto(-66519,-17409,3335);
		gcall.Stepto(-66518,-17411,3335);
		gcall.NewSpend(1);
		gcall.Stepto(-66516,-17413,3335);
		gcall.Stepto(-66513,-17415,3335);
		gcall.WaitPlans();
		break;
	case 2:
		gcall.Stepto(-66781,-17316,3405);
		gcall.Stepto(-66566,-17382,3336);
		gcall.Stepto(-66325,-17450,3344);
		gcall.Stepto(-66082,-17512,3355);
		gcall.Stepto(-65840,-17558,3358);
		gcall.Stepto(-65592,-17583,3360);
		gcall.Stepto(-65491,-17589,3360);
		Sleep(1000);
		gcall.DeliverQuests(zid,taskid,L"최진아");
		Sleep(1000);
		break;
	case 3:
		//过滤怪物(소현,1);
		//过滤怪物(최진아,1);
		
		gcall.Stepto(-65491,-17589,3360,30,30,5000);
		gcall.NewSpend(1);
		gcall.FindThenKill(0,600,modeAoe | modeNormal);
		gcall.sendcall(id_msg_attack, (LPVOID)0x5DFC);//v
		gcall.Stepto(-65299,-17775,3355);
		gcall.Stepto(-65123,-17924,3351);
		gcall.Stepto(-64921,-18072,3349);
		gcall.Stepto(-64733,-18229,3353);
		gcall.Stepto(-64725,-18235,3353);
		Sleep(1000);
		//gcall.FindThenKill(0,200,modeAoe | modeNormal);
		//Sleep(1000);
		//gcall.FindThenKill(0,200,modeAoe | modeNormal);

		//gcall.Stepto(-64620,-18148,3355);
		//gcall.Stepto(-64758,-18250,3353);
		//Sleep(1000);
		gcall.PickupTask();
		//Sleep(1000);
		gcall.NewSpend(2.5);
		gcall.Stepto(-64628,-18120,3355);
		gcall.Stepto(-64174,-18063,3364);
		Sleep(1000);
		gcall.PickupTask();
		//Sleep(1000);

		gcall.Stepto(-64036,-18099,3367);
		gcall.Stepto(-63969,-18107,3367);
		gcall.Stepto(-63866,-18133,3367);
		gcall.Stepto(-63667,-18123,3364);
		gcall.Stepto(-63472,-18100,3360);
		gcall.Stepto(-63274,-18077,3356);
		gcall.Stepto(-63078,-18055,3354);
		gcall.Stepto(-62961,-18045,3355);
		gcall.Stepto(-62906,-18039,3356);
		gcall.Stepto(-64794,-17762,3354);
		gcall.Stepto(-65491,-17589,3360);
		Sleep(1000);
		gcall.PickupTask();
		gcall.randXianlu(0);
		gcall.NewSpend(2.5);
		//过滤怪物(소현,3);
		break;
	case 4:
		gcall.NewSpend(2.5);
		gcall.Stepto(-65361,-17722,3356,30,30,5000);
		gcall.Stepto(-65418,-17777,3354,30,30,5000);
		gcall.Stepto(-65465,-17971,3347);
		gcall.Stepto(-65512,-18164,3340);
		gcall.Stepto(-65558,-18355,3336);
		gcall.Stepto(-65606,-18550,3327);
		gcall.Stepto(-65653,-18741,3304);
		gcall.Stepto(-65727,-18926,3275);
		gcall.Stepto(-65819,-19099,3261);
		gcall.Stepto(-65906,-19280,3246);
		gcall.Stepto(-65985,-19462,3233);
		gcall.Stepto(-66060,-19646,3224);
		gcall.Stepto(-66132,-19831,3232);
		gcall.Stepto(-66206,-20013,3228);
		gcall.Stepto(-66284,-20204,3223);
		gcall.Stepto(-66381,-20431,3262);
		gcall.Stepto(-66526,-20630,3348);
		gcall.Stepto(-66687,-20819,3456);
		gcall.Stepto(-66830,-21021,3564);
		gcall.Stepto(-66947,-21240,3674);
		gcall.Stepto(-67062,-21459,3801);
		gcall.Stepto(-67181,-21677,3885);
		gcall.Stepto(-67339,-21870,3971);
		gcall.Stepto(-67514,-22046,4024);
		gcall.Stepto(-67688,-22222,4053);
		gcall.Stepto(-67864,-22398,4067);
		gcall.Stepto(-68038,-22574,4087);
		gcall.Stepto(-68191,-22734,4103);
		gcall.Stepto(-68326,-22876,4117);
		gcall.Stepto(-68464,-23021,4131);
		gcall.Stepto(-68602,-23166,4135);
		gcall.Stepto(-68738,-23306,4137);
		gcall.Stepto(-68899,-23464,4137);
		gcall.NewSpend(1);
		gcall.Stepto(-69003,-23484,4138);
		gcall.Stepto(-69014,-23494,4138);
		
		Sleep(1000);
		gcall.DeliverQuests(zid,5,L"한시랑");
		Sleep(1000);
		break;
	case 5:
		gcall.NewSpend(2.5);
		gcall.Stepto(-65646,-17656,3357);
		gcall.Stepto(-65536,-17861,3351);
		gcall.Stepto(-65455,-18094,3343);
		gcall.Stepto(-65489,-18338,3337);
		gcall.Stepto(-65578,-18566,3328);
		gcall.Stepto(-65667,-18794,3293);
		gcall.Stepto(-65767,-19026,3266);
		gcall.Stepto(-65891,-19236,3249);
		gcall.Stepto(-66016,-19447,3239);
		gcall.Stepto(-66139,-19657,3242);
		gcall.Stepto(-66220,-19896,3235);
		gcall.Stepto(-66276,-20135,3225);
		gcall.Stepto(-66335,-20372,3244);
		gcall.Stepto(-66428,-20607,3312);
		gcall.Stepto(-66564,-20809,3418);
		gcall.Stepto(-66718,-21009,3519);
		gcall.Stepto(-66845,-21218,3638);
		gcall.Stepto(-66964,-21432,3763);
		gcall.Stepto(-67083,-21646,3853);
		gcall.Stepto(-67206,-21867,3943);
		gcall.Stepto(-67367,-22049,4003);
		gcall.Stepto(-67545,-22217,4039);
		gcall.Stepto(-67726,-22394,4058);
		gcall.Stepto(-67900,-22566,4077);
		gcall.Stepto(-68081,-22743,4097);
		gcall.Stepto(-68251,-22913,4114);
		gcall.Stepto(-68421,-23089,4131);
		gcall.Stepto(-68598,-23271,4136);
		gcall.Stepto(-68768,-23446,4137);
		gcall.Stepto(-68938,-23622,4137);
		gcall.Stepto(-69114,-23803,4139);
		gcall.Stepto(-69284,-23979,4141);
		gcall.Stepto(-69296,-23991,4141);
		gcall.Stepto(-69227,-23899,4139);
		gcall.Stepto(-69360,-24025,4149);
		gcall.Stepto(-69532,-24201,4225);
		gcall.Stepto(-69703,-24385,4284);
		gcall.Stepto(-69875,-24557,4330);
		gcall.Stepto(-70052,-24731,4364);
		gcall.Stepto(-70229,-24903,4380);
		gcall.Stepto(-70403,-25073,4387);
		gcall.Stepto(-70586,-25251,4386);
		gcall.Stepto(-70765,-25425,4373);
		gcall.Stepto(-70931,-25592,4362);
		gcall.Stepto(-70963,-25625,4362);
		gcall.Stepto(-71079,-25767,4408);
		gcall.Stepto(-71269,-25935,4456);
		gcall.Stepto(-71449,-26104,4456);
		gcall.Stepto(-71628,-26272,4456);
		gcall.Stepto(-71640,-26281,4456);
		gcall.Stepto(-71647,-26291,4456);
		gcall.Stepto(-71815,-26471,4456);
		gcall.Stepto(-71997,-26642,4489);
		gcall.Stepto(-72111,-26741,4485);
		gcall.Stepto(-72215,-26832,4439);
		gcall.Stepto(-72300,-26904,4439);
		gcall.Stepto(-72611,-26807,4439);
		gcall.Stepto(-72645,-26823,4439);
		gcall.Stepto(-72871,-26911,4439);
		gcall.WaitPlans();
		gcall.Stepto(-73106,-26987,4439);
		gcall.Stepto(-73352,-27039,4439);
		gcall.Stepto(-73466,-26987,4445);
		gcall.Stepto(-73435,-26884,4444);
		gcall.Stepto(-73267,-26700,4307);
		gcall.Stepto(-73088,-26524,4231);
		gcall.Stepto(-72912,-26349,4088);
		gcall.Stepto(-72787,-26171,4026);
		gcall.Stepto(-72958,-26113,4026);
		gcall.Stepto(-73143,-26258,3946);
		gcall.Stepto(-73331,-26423,3818);
		gcall.Stepto(-73504,-26602,3729);
		gcall.Stepto(-73676,-26781,3621);
		gcall.Stepto(-73712,-26822,3621);
		gcall.Stepto(-73605,-27003,3621);
		gcall.Stepto(-73427,-27175,3621);
		gcall.Stepto(-73246,-27229,3611);
		gcall.Stepto(-73204,-27239,3611);
		gcall.Stepto(-72969,-27314,3611);
		gcall.Stepto(-72723,-27363,3611);
		gcall.NewSpend(1);
		gcall.Stepto(-72491,-27389,3611);
		Sleep(1000);
		gcall.sendcall(id_msg_attack, (LPVOID)0x5E06);//3
		Sleep(1500);
		gcall.sendcall(id_msg_attack, (LPVOID)0x5DE8);//z
		Sleep(800);
		gcall.Kill_Tab();
		gcall.TurnToNear(500);
		gcall.sendcall(id_msg_attack, (LPVOID)0x5e74);//1
		gcall.FindThenKill(0,500,modeAoe | modeNormal);
		Sleep(15000);
		break;
	case 6:
		gcall.Stepto(-72550,-27397,3611);
		Sleep(1000);
		gcall.DeliverQuests(zid,7,L"한시랑");
		Sleep(1000);
		break;
	case 7:
		gcall.NewSpend(2.5);
		gcall.Stepto(-72421,-27532,3611);
		gcall.Stepto(-72390,-27572,3621);
		gcall.Stepto(-72223,-27747,3611);
		gcall.Stepto(-71981,-27820,3611);
		gcall.Stepto(-71739,-27868,3611);
		gcall.Stepto(-71495,-27911,3611);
		gcall.Stepto(-71258,-27967,3621);
		gcall.Stepto(-71079,-28088,3619);
		gcall.Stepto(-71113,-28143,3619);
		gcall.Stepto(-71288,-28317,3530);
		gcall.Stepto(-71462,-28495,3405);
		gcall.Stepto(-71628,-28678,3313);
		gcall.Stepto(-71795,-28864,3198);
		gcall.Stepto(-71750,-28958,3198);
		gcall.Stepto(-71597,-28998,3198);
		gcall.Stepto(-71426,-28816,3098);
		gcall.Stepto(-71254,-28641,2991);
		gcall.Stepto(-71066,-28479,2885);
		gcall.Stepto(-70886,-28306,2793);
		gcall.Stepto(-70845,-28240,2793);
		gcall.Stepto(-71020,-28079,2793);
		gcall.Stepto(-71215,-27919,2793);
		gcall.Stepto(-71448,-27834,2784);
		gcall.Stepto(-71687,-27787,2784);
		gcall.Stepto(-71906,-27706,2784);
		gcall.Stepto(-72065,-27589,2784);
		gcall.Stepto(-72226,-27474,2793);
		gcall.Stepto(-72384,-27354,2784);
		gcall.Stepto(-72542,-27232,2784);
		gcall.Stepto(-72698,-27111,2784);
		gcall.Stepto(-72852,-26987,2784);
		gcall.Stepto(-73000,-26848,2792);
		gcall.Stepto(-73132,-26703,2798);
		gcall.Stepto(-73265,-26553,2784);
		gcall.Stepto(-73394,-26405,2763);
		gcall.Stepto(-73527,-26259,2707);
		gcall.Stepto(-73667,-26111,2624);
		gcall.Stepto(-73801,-25973,2551);
		gcall.Stepto(-73944,-25832,2482);
		gcall.NewSpend(1);
		gcall.Stepto(-74091,-25695,2412);
		break;
	case 8:
		gcall.WaitPlans();
		gcall.NewSpend(2.5);
		gcall.Stepto(-62405,-43907,-1741);
		gcall.Stepto(-62381,-44043,-1741);
		gcall.Stepto(-62380,-44047,-1741);
		gcall.Stepto(-62374,-44165,-1764,30);
		gcall.Stepto(-62367,-44454,-1788,30);
		gcall.Stepto(-62364,-44454,-1788,30);
		gcall.Stepto(-61994,-44422,-1785);
		gcall.Stepto(-61562,-44372,-1783);
		gcall.Stepto(-61131,-44329,-1777);
		gcall.Stepto(-60690,-44352,-1786);
		gcall.Stepto(-60267,-44345,-1806);
		gcall.NewSpend(1);
		gcall.Stepto(-59876,-44149,-1802);
		gcall.Stepto(-59756,-44017,-1799);
		
		Sleep(1000);
		gcall.DeliverQuests(zid,9,L"한시랑");
		Sleep(2000);
		break;
	case 9:
		gcall.Stepto(-59567,-44097,-1805);
		gcall.Stepto(-59517,-44121,-1806);
		Sleep(1000);
		gcall.DeliverQuests(zid,0xA,L"거지노인 청운");
		Sleep(1000);
		break;
	case 10:
		gcall.Stepto(-59649,-44034,-1801);
		gcall.Stepto(-59579,-43940,-1799);
		gcall.Stepto(-59497,-43826,-1780);
		gcall.Stepto(-59469,-43785,-1781);
		Sleep(1000);
		gcall.PickupTask();
		Sleep(1000);
		break;
	case 11:
		gcall.Stepto(-59578,-43873,-1780);
		gcall.Stepto(-59557,-44035,-1802);
		Sleep(1000);
		gcall.DeliverQuests(zid,0xC,L"거지노인 청운");
		Sleep(1000);
		break;
	}
}
void TaskScript::Task_510(int zid,int taskid)
{
	switch (taskid)
	{
	case 1:
		gcall.FenJieByConfig();
		Sleep(1000);
		gcall.NewSpend(2.5);
		gcall.Stepto(-59558,-44038,-1802);
		gcall.Stepto(-59777,-44120,-1802);
		gcall.Stepto(-60003,-44222,-1803);
		gcall.Stepto(-60227,-44336,-1807);
		gcall.Stepto(-60448,-44449,-1804);
		gcall.Stepto(-60669,-44562,-1811);
		gcall.Stepto(-60889,-44675,-1828);
		gcall.Stepto(-61112,-44785,-1851);
		gcall.Stepto(-61335,-44893,-1879);
		gcall.Stepto(-61560,-44996,-1908);
		gcall.Stepto(-61786,-45100,-1914);
		gcall.Stepto(-62012,-45203,-1913);
		gcall.Stepto(-62237,-45306,-1917);
		gcall.Stepto(-62463,-45410,-1926);
		gcall.Stepto(-62558,-45592,-1936);
		gcall.Stepto(-62640,-45826,-1948);
		gcall.Stepto(-62721,-46060,-1959);
		gcall.Stepto(-62802,-46295,-1966);
		gcall.NewSpend(1);
		gcall.Stepto(-62883,-46529,-1961);
		gcall.Stepto(-62964,-46764,-1968);
		Sleep(1000);
		gcall.CuncangkuByConfig(L"오늘준");
		Sleep(1000);
		gcall.Stepto(-62758,-46671,-1968);
		gcall.Stepto(-62563,-46518,-1965);
		gcall.Stepto(-62368,-46365,-1954);
		gcall.Stepto(-62128,-46366,-1936);
		gcall.Stepto(-61956,-46521,-1938);
		Sleep(1000);
		gcall.SellItemByConfig(L"한냥해");
		Sleep(1000);
		gcall.SortBag();
		Sleep(1000);
		gcall.NewSpend(2.5);
		gcall.Stepto(-61978,-46310,-1929);
		gcall.Stepto(-62148,-46180,-1932);
		gcall.Stepto(-62379,-46088,-1948);
		gcall.Stepto(-62609,-45996,-1954);
		gcall.Stepto(-62689,-45790,-1948);
		gcall.Stepto(-62593,-45591,-1937);
		gcall.Stepto(-62386,-45454,-1926);
		gcall.Stepto(-62179,-45317,-1918);
		gcall.Stepto(-61968,-45187,-1913);
		gcall.Stepto(-61754,-45062,-1913);
		gcall.Stepto(-61537,-44941,-1901);
		gcall.Stepto(-61319,-44823,-1866);
		gcall.Stepto(-61097,-44713,-1838);
		gcall.Stepto(-60872,-44608,-1819);
		gcall.Stepto(-60645,-44508,-1804);
		gcall.Stepto(-60417,-44409,-1801);
		gcall.Stepto(-60190,-44310,-1806);
		gcall.Stepto(-59962,-44211,-1803);
		gcall.NewSpend(1);
		gcall.Stepto(-59735,-44112,-1802);
		//买卖，存完

		gcall.NewSpend(2.5);
		gcall.Stepto(-59354,-44554,-1833);
		gcall.Stepto(-59358,-44564,-1834);
		gcall.Stepto(-59418,-44800,-1862);
		gcall.Stepto(-59449,-45048,-1879);
		gcall.Stepto(-59474,-45295,-1886);
		gcall.Stepto(-59479,-45542,-1887);
		gcall.Stepto(-59494,-45781,-1897);
		gcall.Stepto(-59551,-46218,-1927);
		gcall.Stepto(-59517,-46488,-1926);
		gcall.Stepto(-59502,-46497,-1925);
		gcall.Stepto(-59317,-46604,-1910);
		gcall.Stepto(-59038,-46692,-1877);
		gcall.Stepto(-58634,-46868,-1811);
		gcall.Stepto(-58257,-47059,-1755);
		gcall.Stepto(-58234,-47071,-1753);
		gcall.Stepto(-58194,-47095,-1748);
		gcall.Stepto(-57864,-47335,-1716);
		gcall.Stepto(-57523,-47638,-1676);
		gcall.Stepto(-57196,-47921,-1663);
		gcall.Stepto(-56849,-48188,-1657);
		gcall.Stepto(-56513,-48459,-1656);
		gcall.Stepto(-56178,-48742,-1660);
		gcall.Stepto(-55786,-48910,-1644);
		gcall.Stepto(-55364,-49026,-1569);
		gcall.Stepto(-54930,-49046,-1455);
		gcall.Stepto(-54507,-49003,-1333);
		gcall.Stepto(-54070,-48940,-1208);
		gcall.Stepto(-53671,-48862,-1095);
		gcall.Stepto(-53435,-48773,-1029);
		gcall.Stepto(-53224,-48642,-959);
		gcall.Stepto(-53034,-48485,-885);
		gcall.Stepto(-52842,-48326,-817);
		gcall.Stepto(-52651,-48167,-755);
		gcall.Stepto(-52484,-47988,-691);
		gcall.Stepto(-52354,-47776,-636);
		gcall.Stepto(-52242,-47555,-583);
		gcall.Stepto(-52148,-47326,-537);
		gcall.Stepto(-52054,-47095,-492);
		gcall.Stepto(-51940,-46878,-442);
		gcall.Stepto(-51771,-46694,-391);
		gcall.Stepto(-51573,-46545,-344);
		gcall.Stepto(-51370,-46410,-293);
		gcall.Stepto(-51149,-46287,-238);
		gcall.Stepto(-50927,-46169,-183);
		gcall.Stepto(-50706,-46052,-136);
		gcall.Stepto(-50487,-45937,-99);
		gcall.Stepto(-50265,-45821,-63);
		gcall.Stepto(-50052,-45697,-28);
		gcall.Stepto(-49836,-45567,10);
		gcall.Stepto(-49625,-45440,50);
		gcall.Stepto(-49412,-45312,93);
		gcall.Stepto(-49200,-45184,134);
		gcall.Stepto(-48979,-45062,169);
		gcall.Stepto(-48747,-44975,196);
		gcall.Stepto(-48530,-44932,213);
		gcall.Stepto(-48098,-44851,242);
		gcall.Stepto(-47668,-44780,267);
		gcall.NewSpend(1);
		gcall.Stepto(-47235,-44718,281);
		gcall.Stepto(-46808,-44656,298);
		gcall.Stepto(-46381,-44587,327);
		gcall.Stepto(-45945,-44516,350);
		gcall.Stepto(-45521,-44445,358);
		gcall.Stepto(-45089,-44373,363);
		Sleep(2000);
		gcall.Stepto(-44909,-44341,364);
		gcall.Stepto(-44772,-44315,364);
		gcall.Stepto(-44729,-44307,365);
		gcall.WaitPlans();
		gcall.NewSpend(2.5);
		gcall.Stepto(-44483,-44297,360);
		gcall.Stepto(-44236,-44272,353);
		gcall.Stepto(-43987,-44233,353);
		gcall.Stepto(-43749,-44177,353);
		gcall.Stepto(-43519,-44086,353);
		gcall.Stepto(-43326,-43925,353);
		gcall.Stepto(-43163,-43739,353);
		gcall.Stepto(-43075,-43513,353);
		gcall.Stepto(-43081,-43268,353);
		gcall.Stepto(-43088,-43085,353);
		gcall.Stepto(-43077,-42656,353);
		gcall.Stepto(-42913,-42254,353);
		gcall.Stepto(-42587,-41982,353);
		gcall.Stepto(-42159,-41975,355);
		gcall.Stepto(-41802,-42215,353);
		gcall.Stepto(-41544,-42567,353);
		gcall.Stepto(-41472,-42984,353);
		gcall.Stepto(-41445,-43360,353);
		gcall.Stepto(-41387,-43798,353);
		gcall.Stepto(-41281,-44005,353);
		gcall.Stepto(-41173,-44113,353);
		gcall.Stepto(-40962,-44236,353);
		gcall.Stepto(-40724,-44266,353);
		gcall.Stepto(-40492,-44184,353);
		gcall.NewSpend(1);
		gcall.Stepto(-40292,-44041,353);
		gcall.Stepto(-40091,-43889,353);
		gcall.Stepto(-39893,-43740,353);
		gcall.Stepto(-39690,-43599,353);
		gcall.Stepto(-39468,-43490,353);
		gcall.Stepto(-39236,-43397,353);
		gcall.Stepto(-39004,-43303,353);
		Sleep(6000);
		gcall.Stepto(-38955,-43286,353);
		gcall.Stepto(-38881,-43294,353);
		gcall.WaitPlans();
		gcall.Stepto(-38844,-43289,353);
		gcall.Stepto(-38590,-43272,360);
		gcall.NewSpend(2.5);
		gcall.Stepto(-38347,-43262,348);
		gcall.Stepto(-38181,-43256,346);
		gcall.Stepto(-38072,-43289,345);
		gcall.Stepto(-37856,-43409,343);
		gcall.Stepto(-37711,-43523,340);
		gcall.Stepto(-37472,-43875,332);
		gcall.Stepto(-37267,-44261,327);
		gcall.Stepto(-37075,-44654,323);
		gcall.Stepto(-36774,-44963,312);
		gcall.Stepto(-36369,-45097,287);
		gcall.Stepto(-35935,-45082,244);
		gcall.Stepto(-35509,-44994,198);
		gcall.Stepto(-35089,-44893,189);
		gcall.Stepto(-34665,-44790,189);
		gcall.Stepto(-34251,-44692,181);
		gcall.Stepto(-33823,-44591,140);
		gcall.Stepto(-33414,-44494,67);
		gcall.Stepto(-33180,-44439,11);
		gcall.Stepto(-32937,-44381,-51);
		gcall.Stepto(-32690,-44323,-119);
		gcall.Stepto(-32459,-44268,-178);
		gcall.Stepto(-32210,-44209,-238);
		gcall.Stepto(-31968,-44172,-303);
		gcall.Stepto(-31722,-44121,-375);
		gcall.Stepto(-31477,-44115,-449);
		gcall.Stepto(-31229,-44111,-531);
		gcall.Stepto(-30979,-44107,-614);
		gcall.Stepto(-30732,-44103,-687);
		gcall.Stepto(-30484,-44103,-746);
		gcall.Stepto(-30233,-44110,-795);
		gcall.Stepto(-29989,-44122,-844);
		gcall.Stepto(-29740,-44129,-921);
		gcall.Stepto(-29489,-44126,-1017);
		gcall.Stepto(-29244,-44135,-1101);
		gcall.Stepto(-28996,-44148,-1168);
		gcall.Stepto(-28743,-44160,-1215);
		gcall.Stepto(-28497,-44172,-1239);
		gcall.Stepto(-28250,-44184,-1253);
		gcall.Stepto(-28001,-44201,-1283);
		gcall.Stepto(-27764,-44220,-1343);
		gcall.Stepto(-27505,-44240,-1404);
		gcall.Stepto(-27261,-44259,-1436);
		gcall.Stepto(-27020,-44277,-1460);
		gcall.Stepto(-26767,-44307,-1484);
		gcall.Stepto(-26521,-44351,-1507);
		gcall.Stepto(-26286,-44426,-1530);
		gcall.Stepto(-26139,-44539,-1545);
		gcall.Stepto(-25835,-44852,-1580);
		gcall.Stepto(-25553,-45180,-1614);
		gcall.Stepto(-25275,-45511,-1637);
		gcall.Stepto(-25012,-45859,-1651);
		gcall.Stepto(-24750,-46206,-1656);
		gcall.Stepto(-24495,-46556,-1649);
		gcall.Stepto(-24239,-46909,-1632);
		gcall.Stepto(-23978,-47265,-1647);
		gcall.Stepto(-23721,-47613,-1651);
		gcall.Stepto(-23459,-47952,-1638);
		gcall.Stepto(-23180,-48298,-1650);
		gcall.Stepto(-22938,-48599,-1653);
		gcall.Stepto(-22779,-48794,-1652);
		gcall.Stepto(-22624,-48986,-1655);
		gcall.Stepto(-22466,-49180,-1660);
		gcall.Stepto(-22311,-49371,-1668);
		gcall.Stepto(-22152,-49567,-1675);
		gcall.Stepto(-21998,-49756,-1670);
		gcall.Stepto(-21830,-49941,-1657);
		gcall.Stepto(-21651,-50115,-1643);
		gcall.Stepto(-21462,-50278,-1619);
		gcall.Stepto(-21357,-50368,-1608);
		gcall.Stepto(-21247,-50545,-1573);
		gcall.Stepto(-21125,-50762,-1539);
		gcall.Stepto(-21018,-50985,-1506);
		gcall.Stepto(-20952,-51221,-1476);
		gcall.Stepto(-20906,-51467,-1473);
		gcall.Stepto(-20882,-51689,-1475);
		gcall.Stepto(-20861,-52128,-1472);
		gcall.Stepto(-20869,-52562,-1410);
		gcall.Stepto(-20882,-52999,-1340);
		gcall.Stepto(-20908,-53435,-1251);
		gcall.Stepto(-20958,-53870,-1236);
		gcall.Stepto(-21003,-54300,-1232);
		gcall.Stepto(-21048,-54735,-1229);
		gcall.Stepto(-21128,-55057,-1216);
		gcall.Stepto(-21262,-55262,-1208);
		gcall.Stepto(-21398,-55471,-1190);
		gcall.Stepto(-21530,-55684,-1157);
		gcall.Stepto(-21655,-55898,-1112);
		gcall.Stepto(-21781,-56113,-1054);
		gcall.Stepto(-21905,-56326,-1004);
		gcall.Stepto(-22030,-56542,-979);
		gcall.Stepto(-22155,-56757,-992);
		gcall.Stepto(-22279,-56972,-1012);
		gcall.Stepto(-22404,-57189,-1010);
		gcall.NewSpend(1);
		gcall.Stepto(-22530,-57406,-1004);
		gcall.Stepto(-22622,-57565,-1000);
		gcall.Stepto(-22778,-57832,-1000);
		gcall.Stepto(-23027,-58191,-1003);
		gcall.Stepto(-23297,-58533,-1031);
		gcall.Stepto(-23578,-58861,-1033);
		gcall.Stepto(-23672,-58965,-1027);
		gcall.Stepto(-24123,-59287,-987);
		Sleep(6000);
		gcall.Stepto(-24506,-59571,-1003);
		gcall.Stepto(-24785,-59748,-1075);
		gcall.WaitPlans();
		gcall.Stepto(-25157,-59970,-1218);
		gcall.Stepto(-25536,-60194,-1354);
		gcall.NewSpend(2.5);
		gcall.Stepto(-25698,-60310,-1414);
		gcall.Stepto(-25829,-60511,-1482);
		gcall.Stepto(-25951,-60700,-1533);
		gcall.Stepto(-25891,-60934,-1574);
		gcall.Stepto(-25765,-61195,-1653);
		gcall.Stepto(-25550,-61564,-1745);
		gcall.Stepto(-25331,-61938,-1795);
		gcall.Stepto(-25109,-62316,-1843);
		gcall.Stepto(-24887,-62688,-1869);
		gcall.Stepto(-24662,-63058,-1896);
		gcall.Stepto(-24419,-63422,-1904);
		gcall.Stepto(-24172,-63765,-1931);
		gcall.Stepto(-23890,-64117,-1967);
		gcall.Stepto(-23568,-64404,-2128);
		gcall.Stepto(-23248,-64652,-2240);
		gcall.Stepto(-23034,-64786,-2256);
		gcall.Stepto(-22833,-64930,-2256);
		gcall.Stepto(-22591,-64977,-2256);
		gcall.Stepto(-22347,-64957,-2256);
		gcall.Stepto(-22155,-64939,-2257);
		gcall.Stepto(-21723,-64896,-2258);
		gcall.Stepto(-21298,-64854,-2246);
		gcall.Stepto(-21051,-64830,-2231);
		gcall.Stepto(-20801,-64830,-2213);
		gcall.Stepto(-20555,-64844,-2192);
		gcall.Stepto(-20317,-64915,-2175);
		gcall.Stepto(-20093,-65012,-2150);
		gcall.Stepto(-19930,-65049,-2130);
		gcall.Stepto(-19837,-64650,-2127);
		gcall.Stepto(-19589,-64559,-2114);
		gcall.Stepto(-19472,-64507,-2114);
		gcall.WaitPlans();
		gcall.Stepto(-19554,-64253,-2114);
		gcall.Stepto(-19556,-64057,-2114);
		gcall.NewSpend(1);
		Sleep(1000);
		gcall.DeliverQuests(zid,taskid,L"절사명의 백운");
		Sleep(2000);
		break;
	case 2:
		gcall.NewSpend(2.5);
		gcall.Stepto(-19538,-64255,-2114);
		gcall.Stepto(-19532,-64280,-2114);
		gcall.Stepto(-19473,-64504,-2114);
		gcall.Stepto(-19493,-64518,-2114);
		gcall.Stepto(-19591,-64571,-2114);
		gcall.Stepto(-19603,-64576,-2114);
		gcall.Stepto(-19690,-64612,-2126);
		gcall.Stepto(-19905,-64700,-2128);
		gcall.WaitPlans();
		gcall.Stepto(-20023,-64708,-2129);
		gcall.Stepto(-20457,-64760,-2166);
		gcall.Stepto(-20885,-64841,-2222);
		gcall.Stepto(-21303,-64936,-2254);
		gcall.Stepto(-21732,-65018,-2258);
		gcall.Stepto(-22175,-65047,-2255);
		gcall.Stepto(-22601,-64980,-2256);
		gcall.Stepto(-23017,-64846,-2258);
		gcall.Stepto(-23404,-64650,-2213);
		gcall.Stepto(-23716,-64359,-2067);
		gcall.Stepto(-24023,-64043,-1939);
		gcall.Stepto(-24305,-63720,-1927);
		gcall.Stepto(-24536,-63429,-1919);
		gcall.Stepto(-24692,-63227,-1912);
		gcall.Stepto(-24840,-63027,-1889);
		gcall.Stepto(-24984,-62830,-1861);
		gcall.Stepto(-25133,-62628,-1831);
		gcall.Stepto(-25276,-62426,-1830);
		gcall.Stepto(-25399,-62211,-1828);
		gcall.Stepto(-25512,-61993,-1798);
		gcall.Stepto(-25622,-61769,-1765);
		gcall.Stepto(-25695,-61563,-1730);
		gcall.Stepto(-25772,-61303,-1675);
		gcall.Stepto(-25834,-61063,-1612);
		gcall.Stepto(-25887,-60812,-1547);
		gcall.Stepto(-25894,-60564,-1504);
		gcall.NewSpend(1);
		gcall.Stepto(-25817,-60330,-1449);
		gcall.Stepto(-25636,-60166,-1375);
		gcall.Stepto(-25481,-60068,-1325);
		gcall.Stepto(-25112,-59864,-1188);
		gcall.Stepto(-24727,-59653,-1045);
		gcall.Stepto(-24362,-59406,-989);
		gcall.Stepto(-24313,-59367,-984);
		Sleep(2000);
		gcall.Stepto(-24193,-59274,-981);
		gcall.Stepto(-23846,-59006,-985);
		gcall.WaitPlans();
		gcall.Stepto(-23511,-58745,-1031);
		gcall.NewSpend(2.5);
		gcall.Stepto(-23172,-58457,-1023);
		gcall.Stepto(-22925,-58099,-1003);
		gcall.Stepto(-22765,-57704,-998);
		gcall.Stepto(-22595,-57298,-990);
		gcall.Stepto(-22408,-56907,-991);
		gcall.Stepto(-22194,-56543,-981);
		gcall.Stepto(-21927,-56184,-1030);
		gcall.Stepto(-21665,-55837,-1128);
		gcall.Stepto(-21403,-55490,-1188);
		gcall.Stepto(-21218,-55175,-1212);
		gcall.Stepto(-21122,-54950,-1223);
		gcall.Stepto(-21042,-54710,-1229);
		gcall.Stepto(-20978,-54472,-1229);
		gcall.Stepto(-20952,-54226,-1229);
		gcall.Stepto(-20928,-53980,-1233);
		gcall.Stepto(-20903,-53732,-1239);
		gcall.Stepto(-20877,-53485,-1245);
		gcall.Stepto(-20849,-53248,-1286);
		gcall.Stepto(-20817,-52995,-1350);
		gcall.Stepto(-20775,-52744,-1388);
		gcall.Stepto(-20723,-52505,-1431);
		gcall.Stepto(-20666,-52265,-1480);
		gcall.Stepto(-20618,-52021,-1516);
		gcall.Stepto(-20601,-51774,-1538);
		gcall.Stepto(-20566,-51531,-1551);
		gcall.Stepto(-20664,-51306,-1540);
		gcall.Stepto(-20794,-51091,-1527);
		gcall.Stepto(-20866,-50998,-1529);
		gcall.Stepto(-21095,-50741,-1551);
		gcall.Stepto(-21383,-50415,-1604);
		gcall.Stepto(-21665,-50085,-1644);
		gcall.Stepto(-21940,-49746,-1663);
		gcall.Stepto(-22206,-49394,-1671);
		gcall.Stepto(-22455,-49035,-1661);
		gcall.Stepto(-22641,-48663,-1659);
		gcall.Stepto(-22631,-48600,-1662);
		gcall.Stepto(-22545,-48180,-1673);
		gcall.Stepto(-22414,-47760,-1676);
		gcall.Stepto(-22317,-47455,-1681);
		gcall.Stepto(-22270,-47309,-1684);
		gcall.Stepto(-22075,-47100,-1671);
		gcall.Stepto(-22020,-47022,-1666);
		gcall.Stepto(-21881,-46815,-1654);
		gcall.Stepto(-21744,-46610,-1640);
		gcall.Stepto(-21604,-46400,-1624);
		gcall.Stepto(-21466,-46197,-1605);
		gcall.Stepto(-21355,-46001,-1582);
		gcall.Stepto(-21287,-45741,-1547);
		gcall.Stepto(-21244,-45570,-1521);
		gcall.Stepto(-21206,-45385,-1491);
		gcall.Stepto(-21207,-45384,-1491);
		gcall.Stepto(-21410,-45076,-1454);
		gcall.Stepto(-21530,-44806,-1467);
		gcall.Stepto(-21592,-44608,-1446);
		gcall.Stepto(-21629,-44369,-1442);
		gcall.Stepto(-21781,-44167,-1454);
		gcall.Stepto(-21889,-43950,-1469);
		gcall.Stepto(-21813,-43723,-1452);
		gcall.Stepto(-21619,-43565,-1413);
		gcall.NewSpend(1);
		gcall.Stepto(-21607,-43556,-1411);
		Sleep(1000);
		gcall.PickupTask();

		gcall.NewSpend(2.5);
		gcall.Stepto(-21217,-43731,-1328);
		gcall.Stepto(-20832,-44230,-1369);
		gcall.Stepto(-20264,-44372,-1384);
		gcall.Stepto(-19798,-44491,-1370);
		gcall.NewSpend(1);
		gcall.Stepto(-19692,-44411,-1363);
		Sleep(1000);
		gcall.PickupTask();

		gcall.NewSpend(2.5);
		gcall.Stepto(-20150,-44570,-1365);
		gcall.Stepto(-20923,-44258,-1371);
		gcall.Stepto(-21564,-44442,-1440);
		gcall.Stepto(-21903,-43921,-1471);
		gcall.Stepto(-21592,-42968,-1417);
		gcall.Stepto(-21423,-42102,-1370,10,20,3000);
		gcall.Stepto(-21494,-41378,-1353,10,20,3000);
		gcall.Stepto(-21821,-40817,-1481,10,20,3000);
		gcall.NewSpend(1);
		gcall.Stepto(-22195,-40261,-1580,10,20,3000);
		Sleep(1000);
		gcall.PickupTask();

		gcall.NewSpend(2.5);
		gcall.Stepto(-21874,-40847,-1491);
		gcall.Stepto(-21535,-41650,-1363);
		gcall.Stepto(-21531,-42576,-1389);
		gcall.Stepto(-21712,-43318,-1435,10,20,3000);
		gcall.Stepto(-21931,-44093,-1481,10,20,3000);
		gcall.Stepto(-22094,-44673,-1543,10,20,3000);
		gcall.NewSpend(1);
		gcall.Stepto(-22681,-45017,-1656,10,20,3000);
		Sleep(1000);
		gcall.PickupTask();
		Sleep(1000);
		gcall.randXianlu(0);
		Sleep(1000);
		break;
	case 3:
		gcall.NewSpend(2.5);
		gcall.Stepto(-21679,-43666,-1423,10,20,3000);
		gcall.Stepto(-21680,-43667,-1423,10,20,3000);
		gcall.Stepto(-21881,-43927,-1466);
		gcall.Stepto(-22141,-44265,-1524);
		gcall.Stepto(-22410,-44618,-1592);
		gcall.Stepto(-22663,-44964,-1651);
		gcall.Stepto(-22918,-45317,-1676);
		gcall.Stepto(-23132,-45702,-1672);
		gcall.Stepto(-23251,-46115,-1666);
		gcall.Stepto(-23288,-46545,-1674);
		gcall.Stepto(-23283,-46976,-1687);
		gcall.Stepto(-23199,-47407,-1685);
		gcall.Stepto(-23105,-47823,-1663);
		gcall.Stepto(-23009,-48243,-1658);
		gcall.Stepto(-22873,-48471,-1657);
		gcall.Stepto(-22779,-48692,-1653);
		gcall.Stepto(-22604,-48851,-1657);
		gcall.Stepto(-22454,-49029,-1661);
		gcall.Stepto(-22398,-49272,-1662);
		gcall.Stepto(-22334,-49513,-1663);
		gcall.Stepto(-22163,-49696,-1673);
		gcall.Stepto(-21991,-49870,-1670);
		gcall.Stepto(-21816,-50047,-1660);
		gcall.Stepto(-21640,-50225,-1641);
		gcall.Stepto(-21464,-50403,-1611);
		gcall.Stepto(-21314,-50554,-1563);
		gcall.Stepto(-21130,-50741,-1541);
		gcall.Stepto(-21070,-50978,-1497);
		gcall.Stepto(-21053,-51229,-1473);
		gcall.Stepto(-21037,-51471,-1471);
		gcall.Stepto(-21020,-51719,-1470);
		gcall.Stepto(-21003,-51968,-1469);
		gcall.Stepto(-20986,-52215,-1451);
		gcall.Stepto(-20993,-52459,-1415);
		gcall.Stepto(-20977,-52706,-1376);
		gcall.Stepto(-20960,-52958,-1336);
		gcall.Stepto(-20943,-53207,-1289);
		gcall.Stepto(-21006,-53430,-1252);
		gcall.Stepto(-20990,-53677,-1240);
		gcall.Stepto(-20973,-53922,-1236);
		gcall.Stepto(-20956,-54173,-1231);
		gcall.Stepto(-21013,-54402,-1232);
		gcall.Stepto(-20998,-54648,-1230);
		gcall.Stepto(-20981,-54893,-1220);
		gcall.Stepto(-21028,-55122,-1208);
		gcall.Stepto(-21110,-55205,-1205);
		gcall.Stepto(-21241,-55382,-1196);
		gcall.Stepto(-21412,-55636,-1163);
		gcall.Stepto(-21654,-55993,-1087);
		gcall.Stepto(-21899,-56357,-998);
		gcall.Stepto(-22143,-56719,-988);
		gcall.Stepto(-22383,-57074,-1007);
		gcall.Stepto(-22631,-57442,-992);
		gcall.Stepto(-22847,-57812,-991);
		gcall.NewSpend(1);
		gcall.Stepto(-23090,-58173,-995);
		gcall.Stepto(-23333,-58532,-1026);
		gcall.Stepto(-23571,-58885,-1035);
		gcall.Stepto(-23819,-59252,-1003);
		gcall.Stepto(-23825,-59262,-1001);
		gcall.Stepto(-23942,-59302,-988);
		gcall.Stepto(-24164,-59416,-983);
		gcall.Stepto(-24360,-59528,-991);
		gcall.Stepto(-24379,-59541,-993);
		Sleep(6000);
		gcall.Stepto(-24426,-59572,-996);
		gcall.Stepto(-24527,-59640,-1009);
		gcall.Stepto(-24888,-59885,-1125);
		gcall.Stepto(-25247,-60146,-1270);
		gcall.WaitPlans();
		gcall.Stepto(-25454,-60503,-1367);
		gcall.NewSpend(2.5);
		gcall.Stepto(-25509,-60927,-1560);
		gcall.Stepto(-25453,-61362,-1702);
		gcall.Stepto(-25341,-61782,-1774);
		gcall.Stepto(-25168,-62181,-1823);
		gcall.Stepto(-24961,-62559,-1860);
		gcall.Stepto(-24740,-62941,-1892);
		gcall.Stepto(-24508,-63304,-1908);
		gcall.Stepto(-24240,-63645,-1920);
		gcall.Stepto(-23991,-63919,-1937);
		gcall.Stepto(-23809,-64094,-1983);
		gcall.Stepto(-23625,-64263,-2078);
		gcall.Stepto(-23465,-64398,-2159);
		gcall.Stepto(-23263,-64526,-2224);
		gcall.Stepto(-23034,-64643,-2246);
		gcall.Stepto(-22808,-64745,-2254);
		gcall.Stepto(-22581,-64813,-2257);
		gcall.Stepto(-22330,-64866,-2258);
		gcall.Stepto(-22080,-64922,-2258);
		gcall.Stepto(-21840,-64938,-2258);
		gcall.Stepto(-21589,-64933,-2258);
		gcall.Stepto(-21398,-64917,-2257);
		gcall.Stepto(-21029,-64877,-2239);
		gcall.Stepto(-20594,-64812,-2190);
		gcall.Stepto(-20158,-64743,-2136);
		gcall.Stepto(-19924,-64699,-2128);
		gcall.Stepto(-19755,-64618,-2128);
		gcall.Stepto(-19585,-64560,-2114);
		gcall.Stepto(-19476,-64474,-2114);
		gcall.WaitPlans();
		gcall.Stepto(-19512,-64389,-2114);
		gcall.NewSpend(1);
		Sleep(1000);
		gcall.DeliverQuests(zid,taskid,L"고아 친친");
		Sleep(1000);
		break;
	case 4:
		gcall.Stepto(-19548,-64264,-2114);
		gcall.Stepto(-19561,-64145,-2114);
		gcall.Stepto(-19570,-64025,-2114);
		Sleep(1000);
		gcall.DeliverQuests(zid,taskid,L"절사명의 백운");
		Sleep(1000);
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

void TaskScript::Task_511(int zid,int taskid)
{
	switch (taskid)
	{
	case 1:
		gcall.NewSpend(2.5);
		gcall.Stepto(-19570,-64025,-2114);
		gcall.Stepto(-19565,-64063,-2114);
		gcall.Stepto(-19511,-64301,-2114);
		gcall.Stepto(-19454,-64510,-2114);
		gcall.Stepto(-19459,-64514,-2114);
		gcall.Stepto(-19603,-64582,-2114);
		gcall.Stepto(-19663,-64599,-2126);
		gcall.Stepto(-19900,-64661,-2128);
		gcall.WaitPlans();
		gcall.Stepto(-19970,-64680,-2128);
		gcall.Stepto(-20191,-64736,-2140);
		gcall.Stepto(-20434,-64779,-2166);
		gcall.Stepto(-20682,-64841,-2204);
		gcall.Stepto(-20917,-64908,-2237);
		gcall.Stepto(-21154,-64986,-2253);
		gcall.Stepto(-21371,-65099,-2259);
		gcall.Stepto(-21557,-65242,-2259);
		gcall.Stepto(-21707,-65438,-2258);
		gcall.Stepto(-21901,-65594,-2249);
		gcall.Stepto(-22082,-65764,-2224);
		gcall.Stepto(-22201,-65981,-2134);
		gcall.Stepto(-22257,-66191,-2065);
		gcall.Stepto(-22274,-66501,-2040);
		gcall.Stepto(-22285,-66936,-1992);
		gcall.Stepto(-22294,-67367,-1932);
		gcall.Stepto(-22307,-67802,-1862);
		gcall.Stepto(-22303,-68221,-1793);
		gcall.Stepto(-22229,-68367,-1802);
		gcall.Stepto(-22479,-68528,-1745);
		gcall.Stepto(-22888,-68562,-1543);
		gcall.Stepto(-23287,-68369,-1367);
		gcall.Stepto(-23654,-68129,-1354);
		gcall.Stepto(-23969,-67825,-1354);
		gcall.Stepto(-24139,-67440,-1354);
		gcall.Stepto(-24130,-67456,-1354);
		gcall.Stepto(-24057,-67450,-1354);
		gcall.Stepto(-23840,-67428,-1354);
		gcall.Stepto(-23795,-67395,-1347);
		gcall.NewSpend(1);
		gcall.Stepto(-23750,-67363,-1347);
		gcall.Stepto(-23673,-67309,-1349);
		Sleep(4000);
		break;
	case 2:
		gcall.Stepto(-23673,-67309,-1349);
		Sleep(1000);
		gcall.DeliverQuests(zid,taskid,L"미령");
		Sleep(1000);
		break;
	case 3:
		gcall.NewSpend(2.5);
		gcall.Stepto(-23753,-67367,-1347);
		gcall.Stepto(-23755,-67368,-1347);
		gcall.Stepto(-23762,-67374,-1347);
		gcall.Stepto(-23970,-67554,-1354);
		gcall.Stepto(-24017,-67795,-1354);
		gcall.Stepto(-23882,-67991,-1354);
		gcall.Stepto(-23673,-68134,-1354);
		gcall.Stepto(-23513,-68233,-1354);
		gcall.Stepto(-23273,-68405,-1372);
		gcall.Stepto(-22894,-68591,-1545);
		gcall.Stepto(-22487,-68477,-1743);
		gcall.Stepto(-22300,-68328,-1793);
		gcall.Stepto(-22283,-68270,-1794);
		gcall.Stepto(-22221,-67844,-1862);
		gcall.Stepto(-22188,-67429,-1946);
		gcall.Stepto(-22162,-66980,-1990);
		gcall.Stepto(-22177,-66560,-2035);
		gcall.Stepto(-22258,-66127,-2072);
		gcall.Stepto(-22356,-65691,-2153);
		gcall.Stepto(-22443,-65274,-2233);
		gcall.Stepto(-22497,-64841,-2258);
		gcall.Stepto(-22474,-64410,-2184);
		gcall.Stepto(-22474,-64410,-2182);
		gcall.NewSpend(1);
		gcall.Stepto(-22518,-64296,-2165);
		gcall.Stepto(-22542,-64212,-2159);
		Sleep(1000);
		gcall.PickupTaskts();
		Sleep(2000);
		break;
	case 4:
		gcall.NewSpend(2.5);
		gcall.Stepto(-22526,-64510,-2226);
		gcall.Stepto(-22526,-64534,-2236);
		gcall.Stepto(-22532,-64954,-2257);
		gcall.Stepto(-22538,-65390,-2208);
		gcall.Stepto(-22484,-65823,-2119);
		gcall.Stepto(-22444,-66259,-2062);
		gcall.Stepto(-22417,-66692,-2020);
		gcall.Stepto(-22390,-67127,-1970);
		gcall.Stepto(-22364,-67557,-1895);
		gcall.Stepto(-22341,-67990,-1821);
		gcall.Stepto(-22414,-68406,-1766);
		gcall.Stepto(-22745,-68669,-1637);
		gcall.Stepto(-23143,-68558,-1423);
		gcall.Stepto(-23484,-68302,-1354);
		gcall.Stepto(-23658,-68127,-1354);
		gcall.Stepto(-23821,-67937,-1354);
		gcall.Stepto(-23976,-67749,-1354);
		gcall.Stepto(-24108,-67535,-1354);
		gcall.Stepto(-23958,-67481,-1354);
		gcall.Stepto(-23761,-67369,-1347);
		gcall.NewSpend(1);
		gcall.Stepto(-23709,-67343,-1349);
		gcall.Stepto(-23536,-67258,-1345);
		gcall.WaitPlans();
		gcall.PickupTask();
		Sleep(2000);
		break;
	case 5:
		gcall.Stepto(-23679,-67294,-1349);
		Sleep(1000);
		gcall.DeliverQuests(zid,taskid,L"고아 친친");
		Sleep(1000);
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

void TaskScript::Task_512(int zid,int taskid)
{
	switch (taskid)
	{
	case 1:
		gcall.NewSpend(2.5);
		gcall.Stepto(-23760,-67380,-1347);
		gcall.Stepto(-23773,-67389,-1347);
		gcall.Stepto(-23968,-67539,-1354);
		gcall.Stepto(-24107,-67692,-1354);
		gcall.WaitPlans();
		gcall.Stepto(-23920,-67967,-1354);
		gcall.Stepto(-23620,-68282,-1354);
		gcall.Stepto(-23246,-68502,-1386);
		gcall.Stepto(-22852,-68360,-1531);
		gcall.Stepto(-22639,-67984,-1745);
		gcall.Stepto(-22494,-67575,-1886);
		gcall.Stepto(-22430,-67143,-1967);
		gcall.Stepto(-22428,-66721,-2017);
		gcall.Stepto(-22532,-66288,-2062);
		gcall.Stepto(-22703,-65900,-2113);
		gcall.Stepto(-22896,-65500,-2193);
		gcall.Stepto(-23109,-65124,-2249);
		gcall.Stepto(-23267,-64890,-2251);
		gcall.Stepto(-23415,-64694,-2214);
		gcall.Stepto(-23567,-64493,-2144);
		gcall.Stepto(-23609,-64437,-2120);
		gcall.Stepto(-23712,-64301,-2060);
		gcall.Stepto(-23860,-64100,-1971);
		gcall.Stepto(-24003,-63898,-1937);
		gcall.Stepto(-24144,-63700,-1917);
		gcall.Stepto(-24289,-63496,-1896);
		gcall.Stepto(-24433,-63292,-1890);
		gcall.Stepto(-24579,-63088,-1888);
		gcall.Stepto(-24716,-62885,-1884);
		gcall.Stepto(-24861,-62681,-1869);
		gcall.Stepto(-25004,-62479,-1857);
		gcall.Stepto(-25105,-62338,-1846);
		gcall.NewSpend(1);
		gcall.Stepto(-25349,-61993,-1806);
		gcall.Stepto(-25571,-61623,-1753);
		gcall.Stepto(-25772,-61239,-1662);
		gcall.Stepto(-25868,-60824,-1549);
		gcall.Stepto(-25730,-60413,-1441);
		gcall.Stepto(-25402,-60124,-1310);
		gcall.Stepto(-25049,-59886,-1175);
		gcall.Stepto(-24693,-59691,-1043);
		gcall.Stepto(-24479,-59576,-999);
		gcall.Stepto(-24268,-59447,-986);
		Sleep(6000);
		gcall.Stepto(-24201,-59403,-984);
		gcall.WaitPlans();
		gcall.Stepto(-24051,-59295,-986);
		gcall.Stepto(-23745,-58988,-1011);
		gcall.NewSpend(2.5);
		gcall.Stepto(-23465,-58650,-1023);
		gcall.Stepto(-23199,-58309,-1006);
		gcall.Stepto(-22942,-57949,-989);
		gcall.Stepto(-22704,-57596,-998);
		gcall.Stepto(-22471,-57227,-1009);
		gcall.Stepto(-22235,-56866,-1005);
		gcall.Stepto(-21979,-56501,-980);
		gcall.Stepto(-21728,-56152,-1045);
		gcall.Stepto(-21470,-55798,-1132);
		gcall.Stepto(-21214,-55445,-1187);
		gcall.Stepto(-20982,-55128,-1208);
		gcall.Stepto(-20826,-54938,-1209);
		gcall.Stepto(-20639,-54767,-1186);
		gcall.Stepto(-20423,-54640,-1173);
		gcall.Stepto(-20195,-54549,-1293);
		gcall.Stepto(-19955,-54482,-1339);
		gcall.Stepto(-19714,-54414,-1358);
		gcall.Stepto(-19634,-54403,-1362);
		gcall.Stepto(-19462,-54253,-1385);
		gcall.Stepto(-19262,-54104,-1411);
		gcall.Stepto(-19060,-53959,-1433);
		gcall.Stepto(-18874,-53795,-1434);
		gcall.Stepto(-18706,-53617,-1434);
		gcall.Stepto(-18539,-53454,-1434);
		gcall.Stepto(-18539,-53453,-1434);
		gcall.Stepto(-18422,-53375,-1434);
		gcall.Stepto(-18334,-53375,-1435);
		gcall.Stepto(-18085,-53381,-1434);
		gcall.Stepto(-17919,-53387,-1434);
		gcall.Stepto(-17525,-53437,-1434);
		gcall.Stepto(-17454,-53457,-1434);
		gcall.Stepto(-17166,-53497,-1438);
		gcall.Stepto(-16756,-53636,-1436);
		gcall.Stepto(-16351,-53780,-1471);
		gcall.Stepto(-15947,-53947,-1393);
		gcall.Stepto(-15564,-54157,-1303);
		gcall.Stepto(-15215,-54422,-1260);
		gcall.Stepto(-14915,-54736,-1272);
		gcall.Stepto(-14733,-55133,-1250);
		gcall.Stepto(-14613,-55455,-1202);
		gcall.Stepto(-14455,-55645,-1185);
		gcall.Stepto(-14279,-55823,-1178);
		gcall.Stepto(-14097,-55996,-1188);
		gcall.Stepto(-13910,-56156,-1210);
		gcall.Stepto(-13715,-56304,-1227);
		gcall.Stepto(-13514,-56453,-1232);
		gcall.Stepto(-13315,-56610,-1231);
		gcall.Stepto(-13125,-56760,-1228);
		gcall.Stepto(-12929,-56917,-1226);
		gcall.Stepto(-12868,-56965,-1226);
		gcall.Stepto(-12611,-57152,-1225);
		gcall.Stepto(-12262,-57398,-1228);
		gcall.Stepto(-11904,-57650,-1237);
		gcall.Stepto(-11538,-57887,-1246);
		gcall.Stepto(-11163,-58107,-1244);
		gcall.Stepto(-10782,-58315,-1211);
		gcall.Stepto(-10455,-58474,-1186);
		gcall.Stepto(-10226,-58571,-1185);
		gcall.Stepto(-9991,-58659,-1189);
		gcall.Stepto(-9755,-58740,-1191);
		gcall.Stepto(-9521,-58816,-1188);
		gcall.Stepto(-9284,-58893,-1181);
		gcall.Stepto(-9046,-58969,-1167);
		gcall.Stepto(-8808,-59049,-1143);
		gcall.Stepto(-8579,-59133,-1127);
		gcall.Stepto(-8349,-59221,-1120);
		gcall.Stepto(-8117,-59329,-1120);
		gcall.Stepto(-7907,-59447,-1124);
		gcall.Stepto(-7810,-59475,-1127);
		gcall.Stepto(-7301,-60133,-1117);
		gcall.Stepto(-7163,-60215,-1127);
		gcall.Stepto(-6844,-60489,-1170);
		gcall.Stepto(-6547,-60801,-1178);
		gcall.Stepto(-6246,-61123,-1158);
		gcall.NewSpend(1);
		gcall.Stepto(-5954,-61436,-1142);
		gcall.Stepto(-5704,-61791,-1154);
		gcall.Stepto(-5555,-62193,-1209);
		gcall.Stepto(-5552,-62633,-1246);
		gcall.Stepto(-5533,-62921,-1273);
		gcall.Stepto(-5535,-62957,-1279);
		Sleep(2000);
		gcall.Stepto(-5601,-63337,-1402);
		gcall.WaitPlans();
		gcall.Stepto(-5593,-63766,-1624);
		gcall.Stepto(-5633,-64176,-1798);
		gcall.Stepto(-5638,-64620,-1925);
		gcall.Stepto(-5575,-64754,-1923);
		gcall.Stepto(-5420,-64793,-1925);
		gcall.Stepto(-5157,-64806,-1925);
		gcall.Stepto(-4924,-64795,-1922);
		gcall.Stepto(-4666,-64810,-1923);
		gcall.Stepto(-4411,-64826,-1886);
		gcall.Stepto(-4170,-64814,-1859);
		gcall.Stepto(-3917,-64782,-1816);
		gcall.Stepto(-3674,-64750,-1793);
		gcall.Stepto(-3427,-64716,-1754);
		gcall.Stepto(-3180,-64673,-1728);
		gcall.Stepto(-2993,-64524,-1708);
		gcall.Stepto(-2785,-64380,-1685);
		gcall.Stepto(-2590,-64234,-1653);
		gcall.Stepto(-2415,-64053,-1615);
		gcall.Stepto(-2251,-63862,-1567);
		gcall.Stepto(-2091,-63672,-1527);
		gcall.Stepto(-1927,-63502,-1489);
		gcall.Stepto(-1537,-63085,-1421);
		gcall.Stepto(-1255,-63051,-1345);
		gcall.Stepto(-1290,-63139,-1359);
		gcall.Stepto(-1054,-63053,-1295);
		gcall.NewSpend(1);
		gcall.Stepto(-848,-62996,-1252);
		gcall.Stepto(-847,-62996,-1252);
		gcall.Stepto(-697,-62950,-1238);
		gcall.Stepto(-515,-62893,-1241);
		gcall.Stepto(-315,-62837,-1258);
		gcall.Stepto(-133,-62765,-1294);
		gcall.Stepto(-120,-62733,-1296);
		gcall.Stepto(104,-62939,-1328);
		gcall.sendcall(id_msg_attack, (LPVOID)0x5E06);//3
		Sleep(1500);
		gcall.sendcall(id_msg_attack, (LPVOID)0x5DE8);//z
		Sleep(800);
		gcall.Kill_Tab();
		gcall.TurnToNear(500);
		gcall.sendcall(id_msg_attack, (LPVOID)0x5e74);//1
		Sleep(500);
		gcall.Kill_Tab();
		gcall.sendcall(id_msg_attack, (LPVOID)0x5E10);//4
		gcall.FindThenKill(0,500,modeAoe | modeNormal | modePickup,1);
		break;
	case 2:
		gcall.NewSpend(2.5);
		gcall.Stepto(163,-62234,-1386);
		gcall.Stepto(153,-62241,-1384);
		gcall.Stepto(-149,-62481,-1288);
		gcall.Stepto(-502,-62746,-1240);
		gcall.Stepto(-895,-62925,-1268);
		gcall.Stepto(-1305,-63067,-1358);
		gcall.Stepto(-1697,-63252,-1452);
		gcall.Stepto(-2034,-63518,-1504);
		gcall.Stepto(-2306,-63855,-1572);
		gcall.Stepto(-2579,-64197,-1645);
		gcall.Stepto(-2691,-64292,-1666);
		gcall.Stepto(-2862,-64458,-1704);
		gcall.Stepto(-3092,-64540,-1721);
		gcall.Stepto(-3328,-64611,-1743);
		gcall.Stepto(-3504,-64656,-1770);
		gcall.Stepto(-3928,-64736,-1819);
		gcall.Stepto(-4348,-64780,-1877);
		gcall.Stepto(-4788,-64805,-1923);
		gcall.Stepto(-5213,-64775,-1925);
		gcall.Stepto(-5625,-64633,-1925);
		gcall.Stepto(-5677,-64568,-1925);
		gcall.Stepto(-5625,-64209,-1814);
		gcall.Stepto(-5604,-63899,-1688);
		gcall.Stepto(-5596,-63800,-1640);
		gcall.Stepto(-5595,-63781,-1631);
		gcall.NewSpend(1);
		gcall.Stepto(-5576,-63657,-1567);
		gcall.Stepto(-5563,-63410,-1439);
		gcall.Stepto(-5561,-63167,-1319);
		gcall.Stepto(-5527,-62915,-1272);
		Sleep(6000);
		gcall.Stepto(-5519,-62803,-1257);
		gcall.WaitPlans();
		gcall.Stepto(-5519,-62796,-1256);
		gcall.Stepto(-5517,-62764,-1253);
		gcall.NewSpend(2.5);
		gcall.Stepto(-5508,-62352,-1233);
		gcall.Stepto(-5568,-61919,-1178);
		gcall.Stepto(-5710,-61518,-1157);
		gcall.Stepto(-5949,-61141,-1165);
		gcall.Stepto(-6259,-60857,-1175);
		gcall.Stepto(-6608,-60571,-1186);
		gcall.Stepto(-6714,-60487,-1183);
		gcall.Stepto(-6764,-60448,-1178);
		gcall.Stepto(-7110,-60186,-1133);
		gcall.Stepto(-7405,-59863,-1122);
		gcall.Stepto(-7657,-59518,-1131);
		gcall.Stepto(-7922,-59161,-1134);
		gcall.Stepto(-8227,-58864,-1148);
		gcall.Stepto(-8551,-58568,-1180);
		gcall.Stepto(-8747,-58395,-1206);
		gcall.Stepto(-8931,-58225,-1233);
		gcall.Stepto(-9121,-58067,-1260);
		gcall.Stepto(-9329,-57922,-1286);
		gcall.Stepto(-9533,-57780,-1311);
		gcall.Stepto(-9732,-57641,-1334);
		gcall.Stepto(-9944,-57509,-1354);
		gcall.Stepto(-10175,-57408,-1367);
		gcall.Stepto(-10408,-57327,-1372);
		gcall.Stepto(-10641,-57247,-1374);
		gcall.Stepto(-10876,-57166,-1375);
		gcall.Stepto(-11115,-57080,-1376);
		gcall.Stepto(-11346,-56990,-1377);
		gcall.Stepto(-11564,-56882,-1380);
		gcall.Stepto(-11778,-56749,-1387);
		gcall.Stepto(-11989,-56620,-1398);
		gcall.Stepto(-12199,-56491,-1415);
		gcall.Stepto(-12411,-56364,-1441);
		gcall.Stepto(-12633,-56243,-1466);
		gcall.Stepto(-12804,-56158,-1479);
		gcall.Stepto(-13147,-55987,-1486);
		gcall.Stepto(-13525,-55786,-1432);
		gcall.Stepto(-13889,-55539,-1366);
		gcall.Stepto(-14250,-55289,-1369);
		gcall.Stepto(-14578,-55020,-1360);
		gcall.Stepto(-14913,-54730,-1274);
		gcall.Stepto(-15231,-54429,-1254);
		gcall.Stepto(-15546,-54139,-1309);
		gcall.Stepto(-15902,-53890,-1409);
		gcall.Stepto(-16291,-53678,-1501);
		gcall.Stepto(-16526,-53567,-1488);
		gcall.Stepto(-16756,-53479,-1444);
		gcall.Stepto(-16993,-53409,-1434);
		gcall.Stepto(-17239,-53350,-1435);
		gcall.Stepto(-17481,-53309,-1435);
		gcall.Stepto(-17730,-53293,-1435);
		gcall.Stepto(-17976,-53301,-1435);
		gcall.Stepto(-18227,-53327,-1435);
		gcall.Stepto(-18465,-53382,-1434);
		gcall.Stepto(-18693,-53486,-1434);
		gcall.Stepto(-18853,-53679,-1434);
		gcall.Stepto(-19001,-53837,-1434);
		gcall.Stepto(-19004,-53953,-1431);
		gcall.Stepto(-18995,-54173,-1401);
		gcall.Stepto(-19012,-54181,-1399);
		gcall.Stepto(-19400,-54336,-1367);
		gcall.Stepto(-19815,-54492,-1338);
		gcall.Stepto(-20208,-54649,-1278);
		gcall.Stepto(-20605,-54826,-1181);
		gcall.Stepto(-20965,-55083,-1210);
		gcall.Stepto(-21262,-55403,-1194);
		gcall.Stepto(-21435,-55619,-1167);
		gcall.Stepto(-21574,-55825,-1127);
		gcall.Stepto(-21684,-56052,-1072);
		gcall.Stepto(-21800,-56271,-1013);
		gcall.Stepto(-21924,-56484,-977);
		gcall.Stepto(-22037,-56709,-975);
		gcall.Stepto(-22134,-56933,-995);
		gcall.Stepto(-22221,-57171,-1014);
		gcall.Stepto(-22301,-57402,-1014);
		gcall.Stepto(-22374,-57612,-1015);
		gcall.Stepto(-22545,-57879,-1010);
		gcall.NewSpend(1);
		gcall.Stepto(-22837,-58206,-1013);
		gcall.Stepto(-23145,-58519,-1027);
		gcall.Stepto(-23445,-58818,-1044);
		gcall.Stepto(-23783,-59102,-1013);
		gcall.Stepto(-24023,-59276,-988);
		gcall.Stepto(-24227,-59420,-984);
		gcall.Stepto(-24358,-59501,-991);
		Sleep(6000);
		gcall.Stepto(-24423,-59540,-995);
		gcall.Stepto(-24461,-59563,-998);
		gcall.WaitPlans();
		gcall.Stepto(-24805,-59836,-1094);
		gcall.Stepto(-25133,-60118,-1232);
		gcall.NewSpend(2.5);
		gcall.Stepto(-25359,-60486,-1333);
		gcall.Stepto(-25560,-60874,-1541);
		gcall.Stepto(-25533,-61289,-1692);
		gcall.Stepto(-25484,-61409,-1716);
		gcall.Stepto(-25440,-61495,-1726);
		gcall.Stepto(-25214,-61871,-1770);
		gcall.Stepto(-25022,-62258,-1819);
		gcall.Stepto(-24850,-62650,-1866);
		gcall.Stepto(-24637,-63043,-1893);
		gcall.Stepto(-24381,-63381,-1893);
		gcall.Stepto(-24100,-63711,-1917);
		gcall.Stepto(-23799,-64010,-1965);
		gcall.Stepto(-23459,-64300,-2138);
		gcall.Stepto(-23118,-64582,-2236);
		gcall.Stepto(-22888,-64936,-2256);
		gcall.Stepto(-22711,-65343,-2213);
		gcall.Stepto(-22590,-65702,-2141);
		gcall.Stepto(-22514,-65936,-2102);
		gcall.Stepto(-22468,-66183,-2071);
		gcall.Stepto(-22429,-66426,-2049);
		gcall.Stepto(-22393,-66670,-2021);
		gcall.Stepto(-22373,-66918,-1994);
		gcall.Stepto(-22367,-67169,-1963);
		gcall.Stepto(-22365,-67405,-1916);
		gcall.Stepto(-22368,-67665,-1875);
		gcall.Stepto(-22380,-67910,-1837);
		gcall.Stepto(-22416,-68157,-1785);
		gcall.Stepto(-22495,-68392,-1744);
		gcall.Stepto(-22645,-68587,-1674);
		gcall.Stepto(-22875,-68669,-1572);
		gcall.Stepto(-23116,-68635,-1445);
		gcall.Stepto(-23320,-68504,-1373);
		gcall.Stepto(-23493,-68347,-1354);
		gcall.Stepto(-23801,-68041,-1354);
		gcall.Stepto(-24038,-67674,-1354);
		gcall.Stepto(-24081,-67579,-1354);
		gcall.Stepto(-23968,-67504,-1354);
		gcall.Stepto(-23819,-67404,-1354);
		gcall.Stepto(-23753,-67360,-1347);
		gcall.NewSpend(1);
		gcall.Stepto(-23704,-67332,-1349);
		gcall.Stepto(-23657,-67289,-1349);
		gcall.WaitPlans();
		break;
	case 3:
		gcall.Stepto(-23620,-67286,-1349);
		Sleep(1000);
		gcall.DeliverQuests(zid,taskid,L"고아 친친");
		Sleep(1000);
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

void TaskScript::Task_513(int zid,int taskid)
{
	switch (taskid)
	{
	case 1:
		gcall.Stepto(-23701,-67354,-1349);
		gcall.Stepto(-23760,-67381,-1347);
		gcall.WaitPlans();
		gcall.NewSpend(2.5);
		gcall.Stepto(-23977,-67536,-1354);
		gcall.Stepto(-24055,-67603,-1354);
		gcall.Stepto(-24002,-67886,-1354);
		gcall.Stepto(-23782,-68261,-1354);
		gcall.Stepto(-23495,-68588,-1356);
		gcall.Stepto(-23111,-68736,-1465);
		gcall.Stepto(-22668,-68693,-1673);
		gcall.Stepto(-22329,-68625,-1783);
		gcall.Stepto(-22294,-68564,-1789);
		gcall.Stepto(-22097,-68177,-1816);
		gcall.Stepto(-21870,-67805,-1976);
		gcall.Stepto(-21552,-67521,-2105);
		gcall.Stepto(-21271,-67431,-2143);
		gcall.Stepto(-21214,-67404,-2147);
		gcall.NewSpend(1);
		Sleep(1000);
		gcall.DeliverQuests(zid,taskid,L"유가촌 주민");
		Sleep(1000);
		break;
	case 2:
		gcall.NewSpend(2.5);
		gcall.Stepto(-21425,-67378,-2126);
		gcall.Stepto(-21394,-67225,-2131);
		gcall.Stepto(-21360,-66983,-2146);
		gcall.Stepto(-21333,-66793,-2155);
		gcall.Stepto(-21331,-66777,-2155);
		gcall.Stepto(-21134,-66640,-2155);
		gcall.Stepto(-20751,-66430,-2158);
		gcall.Stepto(-20372,-66232,-2197);
		gcall.Stepto(-20032,-65954,-2132);
		gcall.Stepto(-20008,-65914,-2125);
		gcall.Stepto(-19959,-65745,-2119);
		gcall.Stepto(-19930,-65614,-2118);
		gcall.Stepto(-19877,-65318,-2118);
		gcall.Stepto(-19877,-65316,-2118);
		gcall.Stepto(-19872,-64966,-2131);
		gcall.Stepto(-19832,-64720,-2129);
		gcall.Stepto(-19830,-64718,-2129);
		gcall.Stepto(-19697,-64622,-2127);
		gcall.Stepto(-19583,-64567,-2114);
		gcall.NewSpend(1);
		gcall.Stepto(-19459,-64480,-2114);
		gcall.Stepto(-19452,-64475,-2114);
		gcall.WaitPlans();
		gcall.Stepto(-19462,-64453,-2114);
		gcall.Stepto(-19474,-64426,-2114);
		Sleep(5000);
		break;
	case 3:
		gcall.Stepto(-19541,-64354,-2114);
		gcall.Stepto(-19558,-64300,-2114);
		Sleep(1000);
		gcall.PickupSpecTypeTaskts(200,0x4,L"유가촌 주민");
		Sleep(1000);
		break;
	case 4:
		gcall.Stepto(-19608,-64231,-2114);
		Sleep(1000);
		gcall.DeliverQuests(zid,taskid,L"절사명의 백운");
		Sleep(1000);
		break;
	case 5:
		gcall.Stepto(-19520,-64354,-2114);
		gcall.Stepto(-19546,-64528,-2114);
		gcall.Stepto(-19600,-64592,-2114);
		gcall.Stepto(-19604,-64594,-2114);
		gcall.Stepto(-19758,-64661,-2128);
		gcall.Stepto(-19823,-64687,-2128);
		Sleep(4000);
		break;
	case 6:
		//这里加过滤，强制杀某个怪物。 问题
		gcall.Kill_Tab();
		gcall.FindThenKill(0,500,modeAoe | modeNormal);
		gcall.Stepto(-20029,-64767,-2130);
		gcall.Stepto(-20037,-64771,-2130);
		gcall.Stepto(-20365,-64944,-2189);
		gcall.Stepto(-20739,-65145,-2254);
		gcall.Stepto(-21010,-65347,-2259);
		while (true)
		{
			ObjectNode * pNode = gcall.GetObjectByName(L"",500);
			if (gcall.m_Get11C(pNode->ObjAddress) == 1)
			{
				Sleep(1000);
				break;
			}
		}
		
		gcall.Kill_Tab();
		gcall.Kill_Tab();
		gcall.FindThenKill(0,500,modeAoe | modeNormal);
		gcall.Stepto(-21288,-65036,-2259);
		Sleep(1000);
		gcall.Kill_Tab();
		gcall.Kill_Tab();
		gcall.FindThenKill(0,500,modeAoe | modeNormal);
		gcall.Stepto(-21288,-65036,-2259);
		gcall.Stepto(-21249,-64872,-2246);
		Sleep(1000);
		gcall.Kill_Tab();
		gcall.Kill_Tab();
		gcall.FindThenKill(0,500,modeAoe | modeNormal);
		Sleep(1000);
		gcall.Kill_Tab();
		gcall.Kill_Tab();
		gcall.FindThenKill(0,500,modeAoe | modeNormal,6);
		Sleep(1000);
		gcall.WaitPlans();
		break;
	case 7:
		gcall.KeyPress(87);
		Sleep(1000);
		gcall.DeliverQuests(zid,taskid,L"절사명의 백운");
		Sleep(1000);
		break;
	case 8:
		gcall.WaitPlans();
		gcall.KeyPress(87);
		Sleep(1000);
		gcall.Stepto(-19580,-64124,-2114);
		gcall.Stepto(-19597,-64259,-2114);
		gcall.Stepto(-19554,-64333,-2114);
		Sleep(1000);
		gcall.DeliverQuests(zid,taskid,L"고아 친친");
		Sleep(1000);
		break;
	case 9:
		gcall.KeyPress(87);
		Sleep(1000);
		gcall.NewSpend(2.5);
		gcall.Stepto(-19584,-64095,-2114,30,30,3000);
		gcall.Stepto(-19532,-63952,-2112);
		gcall.Stepto(-19500,-63937,-2112);
		gcall.Stepto(-19452,-63935,-2108);
		gcall.Stepto(-19278,-63964,-2096);
		gcall.WaitPlans();
		gcall.Stepto(-18972,-64160,-2005);
		gcall.Stepto(-18916,-64196,-2001);
		gcall.Stepto(-18971,-64544,-2040);
		gcall.Stepto(-19005,-64764,-2024);
		gcall.Stepto(-19278,-64802,-2103);
		gcall.Stepto(-19490,-64842,-2130);
		gcall.Stepto(-19836,-64939,-2132);
		gcall.Stepto(-20277,-64926,-2172);
		gcall.Stepto(-20708,-64994,-2235);
		gcall.Stepto(-21110,-65148,-2258);
		gcall.Stepto(-21535,-65188,-2259);
		gcall.Stepto(-21977,-65134,-2257);
		gcall.Stepto(-22385,-65020,-2254);
		gcall.Stepto(-22787,-64839,-2258);
		gcall.Stepto(-23174,-64631,-2242);
		gcall.Stepto(-23507,-64387,-2144);
		gcall.Stepto(-23812,-64132,-1992);
		gcall.Stepto(-23982,-63946,-1937);
		gcall.Stepto(-24138,-63755,-1928);
		gcall.Stepto(-24295,-63557,-1908);
		gcall.Stepto(-24440,-63356,-1899);
		gcall.Stepto(-24580,-63150,-1897);
		gcall.Stepto(-24719,-62945,-1889);
		gcall.Stepto(-24859,-62738,-1875);
		gcall.Stepto(-24994,-62533,-1856);
		gcall.Stepto(-25130,-62326,-1845);
		gcall.Stepto(-25266,-62114,-1821);
		gcall.Stepto(-25396,-61905,-1795);
		gcall.Stepto(-25513,-61693,-1765);
		gcall.Stepto(-25589,-61549,-1740);
		gcall.NewSpend(1);
		gcall.Stepto(-25768,-61180,-1648);
		gcall.Stepto(-25835,-60769,-1531);
		gcall.Stepto(-25621,-60375,-1402);
		gcall.Stepto(-25294,-60090,-1276);
		gcall.Stepto(-24938,-59861,-1139);
		gcall.Stepto(-24543,-59658,-1012);
		gcall.Stepto(-24430,-59572,-997);
		Sleep(6000);
		gcall.Stepto(-24266,-59427,-987);
		gcall.WaitPlans();
		gcall.Stepto(-24254,-59417,-987);
		gcall.Stepto(-23938,-59161,-993);
		gcall.NewSpend(2.5);
		gcall.Stepto(-23609,-58865,-1030);
		gcall.Stepto(-23334,-58539,-1027);
		gcall.Stepto(-23079,-58192,-1000);
		gcall.Stepto(-22865,-57806,-988);
		gcall.Stepto(-22679,-57462,-989);
		gcall.Stepto(-22572,-57299,-996);
		gcall.Stepto(-22332,-56946,-1008);
		gcall.Stepto(-22086,-56594,-982);
		gcall.Stepto(-21834,-56236,-1023);
		gcall.Stepto(-21571,-55880,-1115);
		gcall.Stepto(-21310,-55549,-1175);
		gcall.Stepto(-21033,-55218,-1202);
		gcall.Stepto(-20744,-54882,-1201);
		gcall.Stepto(-20402,-54606,-1178);
		gcall.Stepto(-20014,-54426,-1342);
		gcall.Stepto(-19613,-54257,-1388);
		gcall.Stepto(-19204,-54095,-1414);
		gcall.Stepto(-18882,-53985,-1428);
		gcall.Stepto(-18649,-53897,-1434);
		gcall.Stepto(-18428,-53813,-1434);
		gcall.Stepto(-18331,-53774,-1434);
		gcall.Stepto(-18273,-53724,-1434);
		gcall.Stepto(-18226,-53683,-1434);
		gcall.Stepto(-18129,-53538,-1434);
		gcall.Stepto(-18128,-53538,-1434);
		gcall.Stepto(-17939,-53432,-1434);
		gcall.Stepto(-17520,-53366,-1434);
		gcall.Stepto(-17097,-53473,-1436);
		gcall.Stepto(-16680,-53592,-1449);
		gcall.Stepto(-16291,-53729,-1492);
		gcall.Stepto(-16063,-53822,-1448);
		gcall.Stepto(-15843,-53932,-1387);
		gcall.Stepto(-15619,-54046,-1333);
		gcall.Stepto(-15403,-54169,-1307);
		gcall.Stepto(-15187,-54294,-1294);
		gcall.Stepto(-14973,-54416,-1295);
		gcall.Stepto(-14758,-54537,-1359);
		gcall.Stepto(-14541,-54660,-1454);
		gcall.Stepto(-14324,-54783,-1528);
		gcall.Stepto(-14106,-54904,-1582);
		gcall.Stepto(-13890,-55023,-1608);
		gcall.Stepto(-13672,-55143,-1622);
		gcall.Stepto(-13460,-55261,-1657);
		gcall.Stepto(-13261,-55371,-1683);
		gcall.Stepto(-12886,-55575,-1701);
		gcall.Stepto(-12501,-55784,-1603);
		gcall.Stepto(-12117,-56003,-1508);
		gcall.Stepto(-11873,-56350,-1440);
		gcall.Stepto(-11680,-56739,-1392);
		gcall.Stepto(-11421,-57073,-1364);
		gcall.Stepto(-11143,-57259,-1357);
		gcall.Stepto(-10938,-57389,-1353);
		gcall.Stepto(-10724,-57518,-1350);
		gcall.Stepto(-10510,-57645,-1340);
		gcall.Stepto(-10293,-57773,-1325);
		gcall.Stepto(-10077,-57897,-1305);
		gcall.Stepto(-9862,-58014,-1287);
		gcall.Stepto(-9646,-58131,-1272);
		gcall.Stepto(-9425,-58251,-1257);
		gcall.Stepto(-9208,-58369,-1240);
		gcall.Stepto(-8987,-58489,-1219);
		gcall.Stepto(-8768,-58608,-1193);
		gcall.Stepto(-8563,-58714,-1172);
		gcall.Stepto(-8330,-58829,-1154);
		gcall.Stepto(-8101,-58938,-1143);
		gcall.Stepto(-7880,-59043,-1141);
		gcall.Stepto(-7815,-59073,-1142);
		gcall.Stepto(-7566,-59178,-1151);
		gcall.Stepto(-7412,-59185,-1150);
		gcall.Stepto(-6972,-59218,-1148);
		gcall.Stepto(-6862,-59278,-1147);
		gcall.Stepto(-6754,-59332,-1151);
		gcall.Stepto(-6396,-59576,-1159);
		gcall.Stepto(-6363,-59615,-1160);
		gcall.Stepto(-6143,-59253,-1159);
		gcall.Stepto(-5996,-59246,-1173);
		gcall.Stepto(-5781,-59181,-1188);
		gcall.Stepto(-5536,-59229,-1193);
		gcall.Stepto(-5302,-59293,-1193);
		gcall.NewSpend(1);
		gcall.Stepto(-5253,-59389,-1191);
		gcall.Stepto(-5241,-59439,-1183);
		gcall.randXianlu(3);
		Sleep(1000);
		gcall.DeliverQuests(zid,taskid,L"마영강");
		Sleep(1000);
		gcall.LinQuJiangLi();
		Sleep(1000);
		gcall.FenJieByConfig();
		Sleep(1000);
		gcall.AddTalent(0x1BA);
		if (gcall.isTalentPanelShow())
		{
			gcall.OpenTalentUI();
			Sleep(1000);
		}
		break;

	}
}

void TaskScript::Task_514(int zid,int taskid)
{
	BOOL flag27 = FALSE;
	BOOL flag = FALSE;
	switch (taskid)
	{
	case 1:
		lianji28_go();
		while (true)
		{
			if (gcall.GetPlayerLevel() == 27)
			{
				if (flag27 == FALSE)
				{
					gcall.AddTalent(0x1C1);
					if (gcall.isTalentPanelShow())
					{
						gcall.OpenTalentUI();
						Sleep(1000);
					}
					flag27 = TRUE;
				}
			}
			if (gcall.GetPlayerLevel() < 29)
			{
				UseExperience();
				lianji28();
			}else
			{
				gcall.AddTalent(0x15A);
				gcall.AddTalent(0x15B);
				if (gcall.isTalentPanelShow())
				{
					gcall.OpenTalentUI();
					Sleep(1000);
				}
				break;
			}
		}
		
		//出28级副本
		flag = gcall.Stepto(29903,-41454,-2275,10,10,3000);
		if (flag)
		{
			Sleep(1000);
			gcall.Shunyi(L"Lianji28-end-mai");
			Sleep(1000);
			gcall.sendcall(id_msg_OverShunyi,(LPVOID)FALSE);
			Sleep(3000);
			gcall.Stepto(27309,-43292,-1619);
			gcall.Stepto(27315,-43510,-1587,40);
		}
		gcall.WaitPlans();
		if (gcall.GetPlayerXianlu() >3)
		{
			gcall.randXianlu(3);
			Sleep(2000);
		}
		gcall.Stepto(27328,-43725,-1587,30,30,3000);
		Sleep(1000);
		gcall.Shunyi(L"Lianji28-mai");
		Sleep(1000);
		gcall.sendcall(id_msg_OverShunyi,(LPVOID)FALSE);
		gcall.WaitPlans();
		gcall.LinQuJiangLi();
		Sleep(1000);
		gcall.SellItemByConfig(L"한정가");
		Sleep(1000);
		gcall.KeyPress(27);
		//走到转盘去
		gcall.Stepto(8567,-38900,-2318);
		gcall.Stepto(8652,-39076,-2322);
		gcall.Stepto(8754,-39288,-2326);
		gcall.Stepto(8755,-39290,-2326);
		gcall.Stepto(8588,-39297,-2318);
		gcall.Stepto(8453,-39299,-2307);
		Sleep(2000);
		
		_BAGSTU jingqi;
		while (gcall.GetGoodsFromBagByName(L"금강역사의 정수", &jingqi))
		{
			gcall.Yaojiang(L"금강역사의 정수",L"금강보패");
		}
		gcall.Stepto(8549,-39129,-2318);
		gcall.Stepto(8633,-38847,-2320);
		Sleep(1000);
		gcall.SellItemByConfig(L"한정가");
		Sleep(1000);
		gcall.KeyPress(27);
		Sleep(1000);
		gcall.XieBaoShi(0);
		Sleep(1000);
		gcall.XieBaoShi(1);
		Sleep(1000);
		gcall.JiaBaoShi(0,L"빛나는 오각 자수정");//5角紫宝石
		Sleep(1000);
		gcall.JiaBaoShi(1,L"빛나는 사각 홍옥");//4角红宝石
		Sleep(1000);

		//任务的传送
		gcall.CityConvey(0x12);
		//gcall.randXianlu(3);
		//gcall.Stepto(8650,-39021,-2321);
		//Sleep(1000);
		//gcall.Shunyi(L"2-15-1");
		//Sleep(1000);
		//gcall.sendcall(id_msg_OverShunyi,(LPVOID)FALSE);
		//Sleep(3000);

		gcall.Stepto(-5095,-59346,-1191,30,30,3000);

		if (gcall.GetPlayerXianlu() >3)
		{
			gcall.randXianlu(3);
			Sleep(2000);
		}
		gcall.DeliverQuests(zid,taskid,L"종리추");
		Sleep(1000);
		break;
	case 2:
		//过滤怪物(황풍사막 준오,2);
		//过滤怪物(황풍사막 목괴,1);
		//过滤怪物(적룡채 약탈꾼,1);
		//过滤怪物(유적사암괴,1);
		//过滤怪物(굶주린 준오,1);
		//过滤怪物(수호대,1);

		gcall.NewSpend(2.5);
		gcall.Stepto(-5095,-58933,-1238);
		gcall.Stepto(-5115,-58686,-1287);
		gcall.Stepto(-5132,-58436,-1332);
		gcall.Stepto(-5134,-58409,-1336);
		gcall.Stepto(-5159,-58213,-1361);
		gcall.Stepto(-5178,-58011,-1380);
		gcall.Stepto(-5180,-57854,-1392);
		gcall.Stepto(-5186,-57604,-1410);
		gcall.Stepto(-5194,-57356,-1431);
		gcall.NewSpend(1);
		gcall.Stepto(-5201,-57213,-1443);
		gcall.FindThenKill(0,500,modeAoe | modeNormal | modePickup);

		gcall.NewSpend(2.5);
		gcall.Stepto(-5496,-57180,-1458);
		gcall.Stepto(-5561,-57175,-1460);
		gcall.Stepto(-5809,-57175,-1458);
		gcall.Stepto(-6057,-57171,-1448);
		gcall.Stepto(-6305,-57164,-1446);
		gcall.Stepto(-6550,-57124,-1453);
		gcall.Stepto(-6787,-57066,-1466);
		gcall.NewSpend(1);
		gcall.Stepto(-6901,-56939,-1475);
		gcall.FindThenKill(0,800,modeAoe | modeNormal | modePickup);

		gcall.NewSpend(2.5);
		gcall.Stepto(-5198,-57148,-1449,30,30,3000);
		gcall.Stepto(-5189,-56952,-1466,30,30,3000);
		gcall.Stepto(-5181,-56761,-1489);
		gcall.Stepto(-5171,-56556,-1523);
		gcall.Stepto(-5162,-56357,-1556);
		gcall.Stepto(-5154,-56158,-1585);
		gcall.Stepto(-5145,-55958,-1609);
		gcall.Stepto(-5135,-55745,-1629);
		gcall.Stepto(-5107,-55500,-1644);
		gcall.NewSpend(1);
		gcall.Stepto(-5079,-55407,-1647);
		gcall.FindThenKill(0,500,modeAoe | modeNormal | modePickup);


		gcall.NewSpend(2.5);
		gcall.Stepto(-5071,-55383,-1648);
		gcall.Stepto(-5002,-55194,-1652);
		gcall.Stepto(-4937,-55017,-1654);
		gcall.Stepto(-4867,-54827,-1654);
		gcall.Stepto(-4799,-54642,-1653);
		gcall.Stepto(-4759,-54448,-1653);
		gcall.Stepto(-4721,-54253,-1652);
		gcall.Stepto(-4718,-54242,-1652);
		gcall.Stepto(-4711,-54211,-1652);
		gcall.Stepto(-4643,-54025,-1648);
		gcall.Stepto(-4568,-53841,-1644);
		gcall.Stepto(-4492,-53658,-1642);
		gcall.Stepto(-4416,-53474,-1641);
		gcall.Stepto(-4333,-53275,-1642);
		gcall.Stepto(-4238,-53045,-1650);
		gcall.Stepto(-4144,-52816,-1659);
		gcall.Stepto(-4113,-52741,-1661);
		gcall.Stepto(-4069,-52531,-1658);
		gcall.Stepto(-4003,-52292,-1653);
		gcall.Stepto(-3932,-52055,-1655);
		gcall.NewSpend(1);
		gcall.Stepto(-3861,-51817,-1664);
		gcall.Stepto(-3836,-51731,-1668);
		gcall.FindThenKill(0,500,modeAoe | modeNormal | modePickup);


		gcall.NewSpend(2.5);
		gcall.Stepto(-3805,-51628,-1672);
		gcall.Stepto(-3864,-51446,-1668);
		gcall.Stepto(-3960,-51276,-1658);
		gcall.Stepto(-4058,-51103,-1645);
		gcall.Stepto(-4157,-50928,-1628);
		gcall.Stepto(-4255,-50756,-1622);
		gcall.Stepto(-4353,-50583,-1634);
		gcall.Stepto(-4468,-50380,-1646);
		gcall.Stepto(-4670,-50322,-1648);
		gcall.Stepto(-4882,-50339,-1653);
		gcall.Stepto(-5128,-50306,-1670);
		gcall.Stepto(-5374,-50265,-1689);
		gcall.Stepto(-5616,-50211,-1710);
		gcall.Stepto(-5855,-50152,-1731);
		gcall.Stepto(-6067,-50100,-1743);
		gcall.NewSpend(1);
		gcall.Stepto(-6239,-50057,-1751);
		gcall.FindThenKill(0,800,modeAoe | modeNormal | modePickup);


		gcall.NewSpend(2.5);
		gcall.Stepto(-6018,-50177,-1737);
		gcall.Stepto(-5778,-50114,-1727);
		gcall.Stepto(-5539,-50051,-1707);
		gcall.Stepto(-5295,-50009,-1685);
		gcall.Stepto(-5047,-50001,-1668);
		gcall.Stepto(-4798,-49993,-1660);
		gcall.Stepto(-4550,-49985,-1663);
		gcall.Stepto(-4302,-49974,-1667);
		gcall.Stepto(-4120,-49888,-1670);
		gcall.Stepto(-3989,-49744,-1672);
		gcall.NewSpend(1);
		gcall.Stepto(-3943,-49693,-1672);
		gcall.FindThenKill(0,500,modeAoe | modeNormal | modePickup);


		gcall.NewSpend(2.5);
		gcall.Stepto(-3818,-49654,-1670);
		gcall.Stepto(-3625,-49611,-1665);
		gcall.Stepto(-3449,-49520,-1657);
		gcall.Stepto(-3287,-49406,-1648);
		gcall.Stepto(-3094,-49309,-1634);
		gcall.Stepto(-2863,-49222,-1613);
		gcall.Stepto(-2617,-49196,-1614);
		gcall.Stepto(-2370,-49187,-1624);
		gcall.Stepto(-2121,-49178,-1630);
		gcall.Stepto(-1873,-49169,-1646);
		gcall.Stepto(-1622,-49160,-1662);
		gcall.Stepto(-1385,-49207,-1674);
		gcall.Stepto(-1156,-49302,-1678);
		gcall.Stepto(-939,-49423,-1676);
		gcall.Stepto(-749,-49583,-1669);
		gcall.Stepto(-599,-49775,-1667);
		gcall.Stepto(-444,-49972,-1660);
		gcall.Stepto(-372,-50210,-1650);
		gcall.Stepto(-377,-50458,-1642);
		gcall.Stepto(-389,-50705,-1637);
		gcall.Stepto(-401,-50953,-1631);
		gcall.Stepto(-412,-51198,-1624);
		gcall.Stepto(-424,-51447,-1615);
		gcall.Stepto(-436,-51695,-1603);
		gcall.Stepto(-448,-51944,-1590);
		gcall.Stepto(-460,-52190,-1580);
		gcall.Stepto(-589,-52402,-1584);
		gcall.Stepto(-694,-52624,-1594);
		gcall.Stepto(-798,-52843,-1614);
		gcall.Stepto(-907,-53073,-1638);
		gcall.Stepto(-1013,-53297,-1659);
		gcall.Stepto(-1034,-53537,-1674);
		gcall.Stepto(-1018,-53790,-1686);
		gcall.Stepto(-924,-54016,-1690);
		gcall.Stepto(-778,-54212,-1687);
		gcall.Stepto(-626,-54408,-1678);
		gcall.Stepto(-463,-54595,-1666);
		gcall.Stepto(-291,-54780,-1651);
		gcall.Stepto(-124,-54963,-1635);
		gcall.Stepto(-3,-55179,-1612);
		gcall.NewSpend(1);
		gcall.Stepto(129,-55389,-1576);
		gcall.Stepto(215,-55523,-1552);
		
		gcall.FindThenKill(0,500,modeAoe | modeNormal | modePickup);

		gcall.NewSpend(2.5);
		gcall.Stepto(174,-55564,-1546);
		gcall.Stepto(34,-55705,-1525);
		gcall.Stepto(-118,-55857,-1493);
		gcall.Stepto(-320,-55999,-1454);
		gcall.Stepto(-521,-56141,-1418);
		gcall.Stepto(-714,-56293,-1385);
		gcall.Stepto(-860,-56425,-1363);
		gcall.Stepto(-904,-56610,-1355);
		gcall.NewSpend(1);
		gcall.Stepto(-909,-56672,-1353);
		
		gcall.FindThenKill(0,500,modeAoe | modeNormal | modePickup);


		gcall.NewSpend(2.5);
		gcall.Stepto(174,-55564,-1546);
		gcall.Stepto(34,-55705,-1525);
		gcall.Stepto(-118,-55857,-1493);
		gcall.Stepto(-320,-55999,-1454);
		gcall.Stepto(-521,-56141,-1418);
		gcall.Stepto(-714,-56293,-1385);
		gcall.Stepto(-860,-56425,-1363);
		gcall.Stepto(-904,-56610,-1355);
		gcall.Stepto(-909,-56672,-1353);
		gcall.Stepto(-1045,-56796,-1348);
		gcall.Stepto(-1154,-56950,-1346);
		gcall.Stepto(-1153,-57148,-1347);
		gcall.Stepto(-1191,-57343,-1348);
		gcall.Stepto(-1283,-57534,-1333);
		gcall.Stepto(-1399,-57754,-1282);
		gcall.Stepto(-1514,-57973,-1220);
		gcall.Stepto(-1634,-58190,-1157);
		gcall.Stepto(-1834,-58327,-1126);
		gcall.Stepto(-2060,-58430,-1116);
		gcall.Stepto(-2286,-58533,-1117);
		gcall.Stepto(-2514,-58631,-1132);
		gcall.Stepto(-2755,-58567,-1183);
		gcall.Stepto(-2993,-58498,-1232);
		gcall.Stepto(-3230,-58426,-1272);
		gcall.Stepto(-3438,-58295,-1303);
		gcall.Stepto(-3627,-58136,-1319);
		gcall.Stepto(-3819,-57973,-1329);
		gcall.Stepto(-4001,-57815,-1341);
		gcall.Stepto(-4020,-57799,-1343);
		gcall.NewSpend(1);
		gcall.Stepto(-4038,-57822,-1344);
		gcall.FindThenKill(0,500,modeAoe | modeNormal | modePickup);


		gcall.NewSpend(2.5);
		gcall.Stepto(-3796,-57876,-1328);
		gcall.Stepto(-3859,-57940,-1331);
		gcall.Stepto(-4031,-58113,-1342);
		gcall.Stepto(-4203,-58287,-1344);
		gcall.Stepto(-4382,-58465,-1333);
		gcall.Stepto(-4576,-58615,-1317);
		gcall.Stepto(-4766,-58781,-1289);
		gcall.Stepto(-4950,-58942,-1244);
		gcall.Stepto(-5146,-59086,-1210);
		gcall.Stepto(-5386,-59165,-1197);
		gcall.Stepto(-5626,-59228,-1191);
		gcall.Stepto(-5863,-59290,-1182);
		gcall.Stepto(-6107,-59355,-1163);
		gcall.Stepto(-6342,-59424,-1156);
		gcall.Stepto(-6573,-59508,-1153);
		gcall.Stepto(-6597,-59517,-1153);
		gcall.NewSpend(1);
		gcall.randXianlu(3);
		break;
	case 3:
		gcall.NewSpend(2.5);
		gcall.Stepto(27349,-43564,-1587,30,30,3000);
		gcall.Stepto(27348,-43570,-1587,30,30,3000);
		gcall.Stepto(27319,-43812,-1589,30,30,3000);
		gcall.Stepto(27299,-43979,-1590);
		gcall.Stepto(27292,-44044,-1591);
		gcall.Stepto(27254,-44285,-1606);
		gcall.Stepto(27164,-44521,-1619);
		gcall.Stepto(27024,-44721,-1618);
		gcall.Stepto(26846,-44888,-1602);
		gcall.Stepto(26638,-45031,-1572);
		gcall.Stepto(26434,-45166,-1551);
		gcall.Stepto(26233,-45306,-1543);
		gcall.Stepto(26028,-45454,-1546);
		gcall.Stepto(25830,-45597,-1552);
		gcall.Stepto(25624,-45745,-1576);
		gcall.Stepto(25424,-45889,-1606);
		gcall.Stepto(25226,-46032,-1625);
		gcall.Stepto(25030,-46193,-1638);
		gcall.Stepto(24872,-46384,-1647);
		gcall.Stepto(24717,-46578,-1654);
		gcall.Stepto(24562,-46771,-1663);
		gcall.Stepto(24433,-46930,-1668);
		gcall.Stepto(24310,-47082,-1673);
		gcall.Stepto(24180,-47237,-1677);
		gcall.Stepto(24050,-47386,-1682);
		gcall.Stepto(23921,-47533,-1686);
		gcall.Stepto(23787,-47685,-1690);
		gcall.Stepto(23657,-47831,-1693);
		gcall.Stepto(23525,-47978,-1694);
		gcall.Stepto(23377,-48138,-1690);
		gcall.Stepto(23206,-48314,-1680);
		gcall.Stepto(23033,-48493,-1669);
		gcall.Stepto(22863,-48668,-1657);
		gcall.Stepto(22687,-48850,-1643);
		gcall.Stepto(22517,-49026,-1626);
		gcall.Stepto(22347,-49201,-1609);
		gcall.Stepto(22171,-49383,-1589);
		gcall.Stepto(21997,-49555,-1571);
		gcall.Stepto(21820,-49725,-1557);
		gcall.Stepto(21641,-49892,-1549);
		gcall.Stepto(21461,-50060,-1548);
		gcall.Stepto(21273,-50229,-1550);
		gcall.Stepto(21086,-50386,-1556);
		gcall.Stepto(20892,-50548,-1559);
		gcall.Stepto(20705,-50706,-1554);
		gcall.Stepto(20518,-50863,-1546);
		gcall.Stepto(20324,-51025,-1535);
		gcall.Stepto(20137,-51183,-1523);
		gcall.Stepto(19949,-51340,-1509);
		gcall.Stepto(19762,-51497,-1493);
		gcall.Stepto(19575,-51654,-1473);
		gcall.Stepto(19383,-51816,-1448);
		gcall.Stepto(19189,-51978,-1419);
		gcall.Stepto(19002,-52136,-1386);
		gcall.Stepto(18814,-52293,-1352);
		gcall.Stepto(18620,-52456,-1319);
		gcall.Stepto(18433,-52613,-1290);
		gcall.Stepto(18239,-52776,-1262);
		gcall.Stepto(18051,-52933,-1239);
		gcall.Stepto(17858,-53096,-1219);
		gcall.Stepto(17672,-53252,-1202);
		gcall.Stepto(17452,-53371,-1176);
		gcall.Stepto(17215,-53433,-1146);
		gcall.Stepto(16978,-53494,-1118);
		gcall.Stepto(16741,-53555,-1093);
		gcall.Stepto(16504,-53616,-1066);
		gcall.Stepto(16259,-53680,-1022);
		gcall.Stepto(16022,-53739,-988);
		gcall.Stepto(15772,-53780,-959);
		gcall.Stepto(15530,-53815,-959);
		gcall.Stepto(15288,-53850,-957);
		gcall.Stepto(15046,-53885,-952);
		gcall.Stepto(14796,-53922,-947);
		gcall.Stepto(14554,-53957,-944);
		gcall.Stepto(14304,-53993,-941);
		gcall.Stepto(14062,-54029,-940);
		gcall.Stepto(13811,-54066,-941);
		gcall.Stepto(13576,-54117,-940);
		gcall.Stepto(13385,-54183,-936);
		gcall.Stepto(13207,-54264,-928);
		gcall.Stepto(13032,-54352,-933);
		gcall.Stepto(12846,-54435,-978);
		gcall.Stepto(12663,-54506,-1045);
		gcall.Stepto(12473,-54576,-1102);
		gcall.Stepto(12289,-54640,-1137);
		gcall.Stepto(12059,-54720,-1159);
		gcall.Stepto(11828,-54800,-1176);
		gcall.Stepto(11597,-54880,-1202);
		gcall.Stepto(11357,-54963,-1235);
		gcall.Stepto(11126,-55044,-1259);
		gcall.Stepto(10894,-55122,-1272);
		gcall.Stepto(10652,-55197,-1286);
		gcall.Stepto(10426,-55266,-1301);
		gcall.Stepto(10178,-55342,-1317);
		gcall.Stepto(9945,-55414,-1328);
		gcall.Stepto(9703,-55488,-1338);
		gcall.Stepto(9463,-55562,-1344);
		gcall.Stepto(9229,-55631,-1336);
		gcall.Stepto(8989,-55700,-1317);
		gcall.Stepto(8753,-55765,-1306);
		gcall.Stepto(8510,-55832,-1305);
		gcall.Stepto(8266,-55899,-1311);
		gcall.Stepto(8030,-55963,-1329);
		gcall.Stepto(7794,-56028,-1349);
		gcall.Stepto(7558,-56092,-1369);
		gcall.Stepto(7314,-56159,-1393);
		gcall.Stepto(7078,-56224,-1415);
		gcall.Stepto(6835,-56290,-1435);
		gcall.Stepto(6599,-56355,-1450);
		gcall.Stepto(6356,-56421,-1458);
		gcall.Stepto(6120,-56486,-1460);
		gcall.Stepto(5876,-56553,-1458);
		gcall.Stepto(5634,-56619,-1443);
		gcall.Stepto(5398,-56684,-1423);
		gcall.Stepto(5151,-56678,-1414);
		gcall.Stepto(4919,-56597,-1420);
		gcall.Stepto(4688,-56517,-1425);
		gcall.Stepto(4448,-56433,-1429);
		gcall.Stepto(4218,-56353,-1432);
		gcall.Stepto(3979,-56270,-1439);
		gcall.Stepto(3748,-56190,-1445);
		gcall.Stepto(3500,-56152,-1440);
		gcall.Stepto(3261,-56226,-1410);
		gcall.Stepto(3030,-56306,-1382);
		gcall.Stepto(2787,-56376,-1359);
		gcall.Stepto(2554,-56450,-1341);
		gcall.Stepto(2314,-56532,-1329);
		gcall.Stepto(2083,-56611,-1329);
		gcall.Stepto(1843,-56693,-1337);
		gcall.Stepto(1613,-56774,-1342);
		gcall.Stepto(1377,-56859,-1337);
		gcall.Stepto(1146,-56942,-1322);
		gcall.Stepto(910,-57026,-1305);
		gcall.Stepto(672,-57111,-1296);
		gcall.Stepto(441,-57194,-1299);
		gcall.Stepto(203,-57279,-1315);
		gcall.Stepto(-26,-57362,-1329);
		gcall.Stepto(-264,-57447,-1332);
		gcall.Stepto(-494,-57529,-1330);
		gcall.Stepto(-724,-57612,-1321);
		gcall.Stepto(-961,-57696,-1303);
		gcall.Stepto(-1199,-57782,-1278);
		gcall.Stepto(-1426,-57863,-1252);
		gcall.Stepto(-1665,-57948,-1229);
		gcall.Stepto(-1887,-58028,-1214);
		gcall.Stepto(-2128,-58114,-1204);
		gcall.Stepto(-2361,-58198,-1204);
		gcall.Stepto(-2599,-58283,-1212);
		gcall.Stepto(-2829,-58365,-1227);
		gcall.Stepto(-3067,-58451,-1249);
		gcall.Stepto(-3303,-58535,-1273);
		gcall.Stepto(-3533,-58617,-1295);
		gcall.Stepto(-3770,-58702,-1313);
		gcall.Stepto(-4000,-58785,-1313);
		gcall.Stepto(-4231,-58867,-1296);
		gcall.Stepto(-4461,-58950,-1271);
		gcall.Stepto(-4699,-59035,-1246);
		gcall.Stepto(-4937,-59120,-1216);
		gcall.Stepto(-5156,-59199,-1198);
		gcall.Stepto(-5317,-59256,-1193);

		//过滤怪物(황풍사막 준오,3);
		//过滤怪物(황풍사막 목괴,3);
		//过滤怪物(적룡채 약탈꾼,3);
		//过滤怪物(유적사암괴,3);
		//过滤怪物(굶주린 준오,3);
		//过滤怪物(수호대,3);


		gcall.NewSpend(2.5);
		gcall.Stepto(-3839,-57584,-1335,30,30,3000);
		gcall.Stepto(-3869,-57573,-1337,30,30,3000);
		gcall.Stepto(-4055,-57503,-1357,30,30,3000);
		gcall.Stepto(-4235,-57421,-1377);
		gcall.Stepto(-4415,-57337,-1397);
		gcall.Stepto(-4595,-57253,-1414);
		gcall.Stepto(-4774,-57169,-1429);
		gcall.Stepto(-4956,-57089,-1443);
		gcall.Stepto(-5144,-57026,-1457);
		gcall.Stepto(-5376,-56950,-1477);
		gcall.Stepto(-5612,-56872,-1494);
		gcall.Stepto(-5847,-56794,-1483);
		gcall.Stepto(-6084,-56716,-1484);
		gcall.Stepto(-6318,-56639,-1530);
		gcall.Stepto(-6556,-56560,-1551);
		gcall.Stepto(-6790,-56483,-1549);
		gcall.Stepto(-6921,-56617,-1521);
		gcall.Stepto(-6988,-56856,-1481);
		gcall.Stepto(-7054,-57095,-1438);
		gcall.Stepto(-7121,-57334,-1395);
		gcall.Stepto(-7187,-57573,-1352);
		gcall.Stepto(-7254,-57812,-1312);
		gcall.Stepto(-7320,-58050,-1275);
		gcall.Stepto(-7270,-58272,-1245);
		gcall.Stepto(-7074,-58425,-1226);
		gcall.Stepto(-6876,-58574,-1191);
		gcall.Stepto(-6678,-58724,-1165);
		gcall.Stepto(-6508,-58894,-1153);
		gcall.Stepto(-6572,-59133,-1154);
		gcall.Stepto(-6641,-59368,-1153);
		gcall.Stepto(-6689,-59529,-1143);
		gcall.NewSpend(1);
		Sleep(1000);
		gcall.DeliverQuests(zid,taskid,L"반찬통");
		Sleep(1000);
		break;
	case 4:
		gcall.NewSpend(2.5);
		gcall.Stepto(-6675,-59345,-1152);
		gcall.Stepto(-6662,-59293,-1153);
		gcall.Stepto(-6464,-59165,-1152);
		gcall.Stepto(-6259,-59056,-1149);
		gcall.Stepto(-6022,-59035,-1171);
		gcall.Stepto(-5781,-59026,-1190);
		gcall.Stepto(-5535,-59067,-1199);
		gcall.Stepto(-5306,-59152,-1199);
		gcall.Stepto(-5080,-59254,-1196);
		gcall.NewSpend(1);
		gcall.Stepto(-5015,-59297,-1197);
		
		Sleep(1000);
		gcall.DeliverQuests(zid,taskid,L"종리추");
		Sleep(1000);
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

void TaskScript::Task_515(int zid,int taskid)
{
	switch (taskid)
	{
	case 1:
		gcall.NewSpend(2.5);
		gcall.Stepto(-4956,-59291,-1199);
		gcall.Stepto(-4935,-59289,-1200);
		gcall.Stepto(-4531,-59317,-1207);
		gcall.Stepto(-4105,-59274,-1242);
		gcall.Stepto(-3665,-59223,-1273);
		gcall.Stepto(-3239,-59172,-1223);
		gcall.Stepto(-2810,-59122,-1138);
		gcall.Stepto(-2378,-59071,-1058);
		gcall.Stepto(-1946,-59042,-994);
		gcall.Stepto(-1515,-59064,-940);
		gcall.Stepto(-1075,-59059,-907);
		gcall.Stepto(-640,-59053,-855);
		gcall.Stepto(-204,-59049,-801);
		gcall.Stepto(222,-59049,-792);
		gcall.Stepto(473,-59049,-793);
		gcall.Stepto(718,-59050,-793);
		gcall.Stepto(966,-59072,-787);
		gcall.Stepto(1212,-59104,-780);
		gcall.Stepto(1461,-59115,-780);
		gcall.Stepto(1709,-59126,-788);
		gcall.Stepto(1958,-59136,-803);
		gcall.Stepto(2208,-59146,-818);
		gcall.Stepto(2454,-59157,-827);
		gcall.Stepto(2698,-59167,-828);
		gcall.Stepto(2947,-59177,-831);
		gcall.Stepto(3196,-59187,-838);
		gcall.Stepto(3444,-59198,-846);
		gcall.Stepto(3698,-59209,-855);
		gcall.Stepto(3943,-59220,-868);
		gcall.Stepto(4192,-59231,-884);
		gcall.Stepto(4425,-59241,-902);
		gcall.Stepto(4685,-59249,-924);
		gcall.Stepto(4935,-59245,-947);
		gcall.Stepto(5183,-59233,-973);
		gcall.Stepto(5430,-59229,-1003);
		gcall.Stepto(5678,-59228,-1032);
		gcall.Stepto(5929,-59211,-1051);
		gcall.Stepto(6172,-59157,-1059);
		gcall.Stepto(6405,-59085,-1061);
		gcall.Stepto(6641,-59000,-1061);
		gcall.Stepto(6873,-58915,-1061);
		gcall.Stepto(7095,-58809,-1059);
		gcall.Stepto(7326,-58724,-1057);
		gcall.Stepto(7573,-58685,-1056);
		gcall.Stepto(7613,-58683,-1056);
		gcall.Stepto(7664,-58679,-1056);
		gcall.NewSpend(1);
		Sleep(1000);
		gcall.DeliverQuests(zid,taskid,L"인절미");
		Sleep(1000);
		break;
	case 2:
		gcall.Stepto(7664,-58679,-1056);
		Sleep(1000);
		gcall.Shunyi(L"2-16-2");
		Sleep(1000);
		gcall.sendcall(id_msg_OverShunyi,(LPVOID)FALSE);
		Sleep(3000);
		gcall.DeliverQuests(zid,taskid,L"진소아");
		Sleep(1000);
		break;
	case 3:
		gcall.NewSpend(2.5);
		gcall.Stepto(8962,-58583,-717);
		gcall.Stepto(8961,-58567,-717);
		gcall.Stepto(8968,-58319,-854);
		gcall.Stepto(8982,-58072,-1053);
		gcall.Stepto(9001,-57905,-1068);
		gcall.Stepto(9618,-58039,-1102);
		gcall.Stepto(9804,-57876,-1164);
		gcall.Stepto(9926,-57663,-1248);
		gcall.Stepto(9971,-57416,-1339);
		gcall.Stepto(10005,-57171,-1384);
		gcall.Stepto(10047,-56928,-1392);
		gcall.Stepto(10095,-56685,-1384);
		gcall.Stepto(10142,-56439,-1372);
		gcall.Stepto(10176,-56191,-1359);
		gcall.Stepto(10188,-55948,-1349);
		gcall.Stepto(10169,-55701,-1339);
		gcall.Stepto(10126,-55456,-1326);
		gcall.Stepto(10058,-55215,-1309);
		gcall.Stepto(10015,-55093,-1300);
		gcall.NewSpend(1);
		Sleep(1000);
		gcall.PickupTask();
		Sleep(1000);

		gcall.NewSpend(2.5);
		gcall.Stepto(10504,-55548,-1319,30,30,3000);
		gcall.Stepto(11453,-56037,-1357,30,30,3000);
		gcall.Stepto(12337,-56184,-1272);
		gcall.Stepto(13267,-56306,-1237);
		gcall.Stepto(13465,-56430,-1272);
		gcall.NewSpend(1);
		gcall.FindThenKill(0,500,modeAoe | modeNormal | modePickup);
		gcall.Stepto(13345,-56362,-1267);
		Sleep(1000);
		gcall.PickupTask();
		Sleep(1000);

		gcall.NewSpend(2.5);
		gcall.Stepto(12554,-56070,-1244,30,30,3000);
		gcall.Stepto(12746,-55449,-1083,30,30,3000);
		gcall.Stepto(13117,-54646,-902);
		gcall.Stepto(13229,-54353,-927);
		gcall.NewSpend(1);
		gcall.FindThenKill(0,500,modeAoe | modeNormal | modePickup);
		gcall.Stepto(13176,-54615,-924);
		Sleep(1000);
		gcall.PickupTask();
		Sleep(1000);

		gcall.NewSpend(2.5);
		gcall.Stepto(13180,-53784,-953,30,30,3000);
		gcall.Stepto(13336,-53026,-971);
		gcall.Stepto(13541,-52283,-1011);
		gcall.NewSpend(1);
		gcall.FindThenKill(0,500,modeAoe | modeNormal | modePickup);
		Sleep(1000);
		gcall.PickupTask();
		Sleep(1000);

		gcall.NewSpend(2.5);
		gcall.Stepto(12996,-52710,-999,30,30,3000);
		gcall.Stepto(12402,-53202,-995,30,30,3000);
		gcall.Stepto(11816,-53675,-1118);
		gcall.Stepto(11186,-54170,-1232);
		gcall.NewSpend(1);
		gcall.Stepto(10661,-54675,-1266);
		
		if (gcall.GetPlayerXianlu()>3)
		{
			gcall.randXianlu(3);
		}
		
		Sleep(1000);
		break;
	case 4:
		gcall.NewSpend(2.5);
		gcall.Stepto(10112,-55425,-1324);
		gcall.Stepto(10109,-55470,-1327);
		gcall.Stepto(10130,-55879,-1348);
		gcall.Stepto(10195,-56290,-1363);
		gcall.Stepto(10089,-56708,-1385);
		gcall.Stepto(10008,-57127,-1387);
		gcall.Stepto(9869,-57543,-1279);
		gcall.Stepto(9511,-57757,-1124);
		gcall.Stepto(9095,-57858,-1075);
		gcall.Stepto(8686,-58002,-1049);
		gcall.Stepto(8297,-58196,-1050);
		gcall.NewSpend(1);
		gcall.Stepto(8064,-58432,-1053);
		gcall.Stepto(8038,-58462,-1054);
		gcall.Stepto(8000,-58505,-1054);
		
		if (gcall.GetPlayerXianlu()>3)
		{
			gcall.randXianlu(3);
		}
		Sleep(1000);
		gcall.DeliverQuests(zid,taskid,L"진소아");
		Sleep(1000);
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

void TaskScript::Task_516(int zid,int taskid)
{
	switch (taskid)
	{
	case 1:
		gcall.NewSpend(2.5);
		gcall.Stepto(8015,-57843,-1043);
		gcall.Stepto(8030,-57830,-1043);
		gcall.Stepto(8356,-57592,-1031);
		gcall.Stepto(8510,-57472,-1044);
		gcall.Stepto(8696,-57313,-1131);
		gcall.Stepto(8882,-57151,-1239);
		gcall.Stepto(9022,-57024,-1311);
		gcall.Stepto(9314,-56750,-1386);
		gcall.Stepto(9627,-56448,-1384);
		gcall.Stepto(9937,-56150,-1364);
		gcall.Stepto(10247,-55852,-1344);
		gcall.Stepto(10571,-55565,-1319);
		gcall.Stepto(10899,-55281,-1282);
		gcall.Stepto(11238,-54994,-1249);
		gcall.Stepto(11568,-54726,-1198);
		gcall.Stepto(11915,-54459,-1156);
		gcall.Stepto(12274,-54201,-1096);
		gcall.Stepto(12604,-53919,-1021);
		gcall.Stepto(12898,-53609,-977);
		gcall.Stepto(13042,-53397,-972);
		gcall.Stepto(13174,-53190,-972);
		gcall.Stepto(13310,-52978,-975);
		gcall.Stepto(13442,-52774,-977);
		gcall.Stepto(13627,-52608,-975);
		gcall.Stepto(13838,-52479,-973);
		gcall.Stepto(14055,-52350,-982);
		gcall.Stepto(14273,-52230,-1000);
		gcall.Stepto(14500,-52128,-1010);
		gcall.Stepto(14724,-52030,-1010);
		gcall.Stepto(14954,-51930,-1011);
		gcall.Stepto(15181,-51831,-1016);
		gcall.Stepto(15410,-51731,-1024);
		gcall.Stepto(15632,-51635,-1034);
		gcall.Stepto(15862,-51534,-1048);
		gcall.Stepto(16089,-51435,-1065);
		gcall.Stepto(16320,-51335,-1084);
		gcall.Stepto(16547,-51236,-1105);
		gcall.Stepto(16769,-51137,-1128);
		gcall.Stepto(17000,-51032,-1156);
		gcall.Stepto(17222,-50931,-1191);
		gcall.Stepto(17450,-50827,-1235);
		gcall.Stepto(17675,-50725,-1275);
		gcall.Stepto(17900,-50617,-1309);
		gcall.Stepto(18126,-50509,-1334);
		gcall.Stepto(18348,-50405,-1351);
		gcall.Stepto(18573,-50299,-1365);
		gcall.Stepto(18798,-50190,-1378);
		gcall.Stepto(19012,-50078,-1392);
		gcall.Stepto(19240,-49960,-1409);
		gcall.Stepto(19460,-49846,-1427);
		gcall.Stepto(19679,-49733,-1447);
		gcall.Stepto(19897,-49620,-1465);
		gcall.Stepto(20113,-49499,-1478);
		gcall.Stepto(20325,-49364,-1485);
		gcall.Stepto(20498,-49256,-1485);
		gcall.Stepto(20816,-49055,-1473);
		gcall.Stepto(21183,-48819,-1452);
		gcall.Stepto(21546,-48588,-1456);
		gcall.Stepto(21920,-48355,-1457);
		gcall.Stepto(22291,-48128,-1480);
		gcall.Stepto(22659,-47905,-1531);
		gcall.Stepto(23005,-47690,-1581);
		gcall.Stepto(23387,-47414,-1623);
		gcall.Stepto(23728,-47160,-1673);
		gcall.Stepto(24072,-46896,-1660);
		gcall.Stepto(24376,-46578,-1639);
		gcall.Stepto(24659,-46248,-1632);
		gcall.Stepto(24830,-46062,-1628);
		gcall.Stepto(25006,-45887,-1615);
		gcall.Stepto(25186,-45714,-1598);
		gcall.Stepto(25368,-45541,-1579);
		gcall.Stepto(25549,-45374,-1558);
		gcall.Stepto(25743,-45214,-1531);
		gcall.Stepto(25962,-45100,-1536);
		gcall.Stepto(26193,-45007,-1559);
		gcall.Stepto(26423,-44927,-1576);
		gcall.Stepto(26654,-44835,-1598);
		gcall.Stepto(26878,-44725,-1614);
		gcall.Stepto(27068,-44562,-1620);
		gcall.Stepto(27204,-44382,-1613);
		gcall.Stepto(27291,-44204,-1600);
		gcall.Stepto(27341,-44012,-1586);
		gcall.NewSpend(1);
		gcall.Stepto(27355,-43811,-1586);
		gcall.Stepto(27352,-43755,-1588);
		gcall.Stepto(27343,-43604,-1584);
		gcall.Stepto(27331,-43399,-1599);
		Sleep(5000);
		gcall.Stepto(27322,-43233,-1620);
		gcall.Stepto(27314,-43151,-1623);
		gcall.WaitPlans();
		gcall.Stepto(27314,-43146,-1623);
		gcall.NewSpend(2.5);
		gcall.Stepto(27305,-42895,-1715);
		gcall.Stepto(27299,-42649,-1859);
		gcall.Stepto(27294,-42398,-2001);
		gcall.Stepto(27281,-42154,-2104);
		gcall.Stepto(27266,-41903,-2212);
		gcall.Stepto(27265,-41681,-2266);
		gcall.Stepto(27337,-41653,-2266);
		gcall.Stepto(27564,-41554,-2266);
		gcall.Stepto(27717,-41553,-2266);
		gcall.Stepto(27963,-41526,-2264);
		gcall.Stepto(28129,-41508,-2264);
		gcall.Stepto(28256,-41518,-2264);
		gcall.Stepto(28516,-41541,-2281);
		gcall.Stepto(28767,-41560,-2282);
		gcall.Stepto(29012,-41578,-2279);
		gcall.Stepto(29262,-41595,-2280);
		gcall.Stepto(29505,-41612,-2282);
		gcall.Stepto(29752,-41628,-2282);
		gcall.Stepto(30009,-41644,-2278);
		gcall.Stepto(30247,-41648,-2279);
		gcall.Stepto(30501,-41651,-2274);
		gcall.Stepto(30749,-41655,-2275);
		gcall.Stepto(30998,-41658,-2279);
		gcall.Stepto(31234,-41664,-2274);
		gcall.Stepto(31436,-41671,-2275);
		gcall.Stepto(31632,-41679,-2278);
		gcall.Stepto(31831,-41687,-2280);
		gcall.Stepto(32031,-41695,-2282);
		gcall.Stepto(32228,-41703,-2280);
		gcall.Stepto(32425,-41705,-2280);
		gcall.Stepto(32626,-41706,-2272);
		gcall.Stepto(32827,-41706,-2257);
		gcall.Stepto(33024,-41705,-2259);
		gcall.Stepto(33225,-41705,-2266);
		gcall.Stepto(33419,-41730,-2260);
		gcall.Stepto(33610,-41783,-2258);
		gcall.Stepto(33800,-41842,-2260);
		gcall.Stepto(33991,-41902,-2262);
		gcall.Stepto(34178,-41962,-2273);
		gcall.Stepto(34347,-42055,-2290);
		gcall.Stepto(34495,-42198,-2302);
		gcall.Stepto(34589,-42370,-2307);
		gcall.Stepto(34673,-42551,-2301);
		gcall.Stepto(34745,-42737,-2285);
		gcall.Stepto(34796,-42930,-2269);
		gcall.Stepto(34838,-43120,-2259);
		gcall.Stepto(34861,-43321,-2257);
		gcall.Stepto(34858,-43518,-2249);
		gcall.Stepto(34841,-43717,-2236);
		gcall.Stepto(34823,-43911,-2237);
		gcall.Stepto(34797,-44109,-2236);
		gcall.Stepto(34769,-44310,-2234);
		gcall.Stepto(34746,-44504,-2232);
		gcall.Stepto(34733,-44706,-2238);
		gcall.Stepto(34808,-44811,-2236);
		gcall.Stepto(34800,-44892,-2237);
		gcall.Stepto(34780,-45146,-2233);
		gcall.Stepto(34765,-45394,-2236);
		gcall.Stepto(34746,-45640,-2233);
		gcall.Stepto(34728,-45873,-2229);
		gcall.Stepto(34728,-45874,-2229);
		gcall.NewSpend(1);
		gcall.sendcall(id_msg_attack, (LPVOID)0x5E06);//3
		Sleep(1500);
		gcall.sendcall(id_msg_attack, (LPVOID)0x5DE8);//z
		Sleep(800);
		gcall.Kill_Tab();
		gcall.Kill_Tab();
		gcall.Kill_Tab();
		gcall.TurnToNear(500);
		Sleep(300);
		gcall.sendcall(id_msg_attack, (LPVOID)0x5e74);//1
		gcall.FindThenKill(0,600,modeAoe | modeNormal | modePickup);

		gcall.NewSpend(2.5);
		gcall.Stepto(34833,-44900,-2236);
		gcall.Stepto(34924,-44957,-2236);
		gcall.Stepto(35133,-45085,-2235);
		gcall.Stepto(35183,-45212,-2233);
		gcall.Stepto(35250,-45449,-2234);
		gcall.Stepto(35321,-45687,-2229);
		gcall.Stepto(35355,-45817,-2228);
		gcall.NewSpend(1);
		gcall.FindThenKill(0,300,modeAoe | modeNormal | modePickup);
		Sleep(1000);
		gcall.Stepto(35355,-45817,-2228);
		Sleep(1000);
		gcall.PickupTask();
		Sleep(1000);

		gcall.NewSpend(2.5);
		gcall.Stepto(35347,-45834,-2203);
		gcall.Stepto(35333,-45875,-2203);
		gcall.Stepto(35287,-46084,-2226);
		gcall.Stepto(35234,-46326,-2224);
		gcall.Stepto(35148,-46558,-2215);
		gcall.Stepto(34981,-46738,-2225);
		gcall.Stepto(34754,-46829,-2228);
		gcall.Stepto(34507,-46798,-2231);
		gcall.Stepto(34276,-46714,-2234);
		gcall.Stepto(34073,-46570,-2231);
		gcall.Stepto(34005,-46339,-2229);
		gcall.Stepto(34025,-46169,-2231);
		gcall.NewSpend(1);
		gcall.FindThenKill(0,300,modeAoe | modeNormal | modePickup);
		Sleep(1000);
		gcall.Stepto(34005,-46339,-2229);
		gcall.Stepto(34025,-46169,-2231);
		Sleep(1000);
		gcall.PickupTask();
		Sleep(1000);
		break;
	case 2:
		gcall.NewSpend(2.5);
		gcall.Stepto(34572,-46515,-2233);
		gcall.Stepto(34572,-46526,-2232);
		gcall.Stepto(34572,-46634,-2230);
		gcall.Stepto(34534,-47044,-2233);
		gcall.Stepto(34531,-47487,-2238);
		gcall.Stepto(34538,-47583,-2225);
		gcall.Stepto(34548,-47832,-2154);
		gcall.Stepto(34557,-48081,-2103);
		gcall.Stepto(34564,-48326,-2131);
		gcall.Stepto(34549,-48576,-2137);
		gcall.Stepto(34502,-48817,-2139);
		gcall.Stepto(34442,-49007,-2156);
		gcall.Stepto(34361,-49187,-2166);
		gcall.Stepto(34255,-49358,-2166);
		gcall.Stepto(34132,-49513,-2160);
		gcall.Stepto(33987,-49641,-2147);
		gcall.Stepto(33815,-49744,-2131);
		gcall.Stepto(33635,-49834,-2129);
		gcall.Stepto(33456,-49917,-2127);
		gcall.Stepto(33270,-49980,-2127);
		gcall.Stepto(33071,-50001,-2128);
		gcall.Stepto(32878,-50026,-2089);
		gcall.Stepto(32676,-50054,-2023);
		gcall.Stepto(32481,-50082,-2021);
		gcall.Stepto(32285,-50110,-2016);
		gcall.Stepto(32088,-50138,-2016);
		gcall.Stepto(31892,-50165,-2009);
		gcall.Stepto(31692,-50186,-2016);
		gcall.Stepto(31493,-50189,-2015);
		gcall.Stepto(31296,-50193,-2013);
		gcall.Stepto(31098,-50200,-2011);
		gcall.Stepto(30900,-50198,-2010);
		gcall.Stepto(30696,-50192,-2015);
		gcall.Stepto(30502,-50186,-2013);
		gcall.Stepto(30307,-50180,-2011);
		gcall.Stepto(30107,-50177,-2014);
		gcall.Stepto(29909,-50176,-2018);
		gcall.Stepto(29787,-50179,-2020);
		gcall.Stepto(29590,-50178,-2012);
		gcall.Stepto(29392,-50177,-2020);
		gcall.Stepto(29190,-50176,-2019);
		gcall.Stepto(28992,-50175,-2018);
		gcall.Stepto(28792,-50174,-2017);
		gcall.Stepto(28596,-50177,-2019);
		gcall.Stepto(28400,-50181,-1976);
		gcall.Stepto(28195,-50186,-1925);
		gcall.Stepto(28001,-50190,-1938);
		gcall.Stepto(27799,-50194,-1938);
		gcall.Stepto(27603,-50198,-1939);
		gcall.Stepto(27401,-50200,-1940);
		gcall.Stepto(27227,-50174,-1939);
		gcall.Stepto(27072,-50054,-1940);
		gcall.Stepto(27010,-49874,-1941);
		gcall.Stepto(27024,-49677,-1852);
		gcall.Stepto(27044,-49474,-1743);
		gcall.NewSpend(1);
		gcall.Stepto(27058,-49280,-1636);
		gcall.Stepto(27058,-49083,-1523);
		gcall.Stepto(27049,-48882,-1408);
		gcall.Stepto(27050,-48684,-1315);
		Sleep(5000);
		gcall.Stepto(27065,-48482,-1294);
		gcall.Stepto(27069,-48387,-1266);
		gcall.WaitPlans();
		gcall.Stepto(27066,-48281,-1222);
		gcall.Stepto(27065,-48243,-1207);
		if (gcall.GetPlayerXianlu()>3)
		{
			gcall.randXianlu(3);
		}
		Sleep(1000);
		gcall.Stepto(27051,-48053,-1188);
		gcall.Stepto(27017,-47908,-1181);
		gcall.NewSpend(2.5);
		gcall.Stepto(26838,-47713,-1194);
		gcall.Stepto(26572,-47613,-1225);
		gcall.Stepto(26160,-47532,-1337);
		gcall.Stepto(25725,-47550,-1546);
		gcall.Stepto(25315,-47669,-1633);
		gcall.Stepto(24928,-47859,-1649);
		gcall.Stepto(24576,-48061,-1646);
		gcall.Stepto(24408,-48165,-1641);
		gcall.Stepto(24238,-48269,-1644);
		gcall.Stepto(24072,-48371,-1647);
		gcall.Stepto(23897,-48471,-1650);
		gcall.Stepto(23719,-48570,-1641);
		gcall.Stepto(23550,-48664,-1634);
		gcall.Stepto(23195,-48862,-1633);
		gcall.Stepto(22817,-49072,-1634);
		gcall.Stepto(22434,-49293,-1607);
		gcall.Stepto(22106,-49574,-1575);
		gcall.Stepto(21794,-49866,-1553);
		gcall.Stepto(21433,-50116,-1548);
		gcall.Stepto(21062,-50339,-1553);
		gcall.Stepto(20673,-50543,-1546);
		gcall.Stepto(20291,-50743,-1524);
		gcall.Stepto(19985,-50903,-1501);
		gcall.Stepto(19769,-51021,-1482);
		gcall.Stepto(19552,-51144,-1460);
		gcall.Stepto(19334,-51267,-1434);
		gcall.Stepto(19120,-51388,-1404);
		gcall.Stepto(18904,-51511,-1369);
		gcall.Stepto(18702,-51660,-1333);
		gcall.Stepto(18519,-51830,-1297);
		gcall.Stepto(18344,-52004,-1263);
		gcall.Stepto(18167,-52180,-1232);
		gcall.Stepto(17996,-52360,-1209);
		gcall.Stepto(17829,-52541,-1188);
		gcall.Stepto(17662,-52721,-1172);
		gcall.Stepto(17492,-52905,-1159);
		gcall.Stepto(17321,-53090,-1145);
		gcall.Stepto(17153,-53271,-1131);
		gcall.Stepto(16985,-53453,-1117);
		gcall.Stepto(16818,-53634,-1104);
		gcall.Stepto(16647,-53818,-1090);
		gcall.Stepto(16503,-53980,-1068);
		gcall.Stepto(16224,-54321,-1049);
		gcall.Stepto(15963,-54666,-1054);
		gcall.Stepto(15713,-55018,-1019);
		gcall.Stepto(15476,-55387,-938);
		gcall.Stepto(15243,-55749,-902);
		gcall.Stepto(15010,-56124,-895);
		gcall.Stepto(14942,-56545,-881);
		gcall.Stepto(14857,-56964,-897);
		gcall.Stepto(14618,-57328,-935);
		gcall.Stepto(14383,-57506,-1017);
		gcall.Stepto(14147,-57576,-1092);
		gcall.Stepto(13903,-57621,-1140);
		gcall.Stepto(13662,-57672,-1143);
		gcall.Stepto(13416,-57724,-1136);
		gcall.Stepto(13177,-57772,-1138);
		gcall.Stepto(12929,-57814,-1147);
		gcall.Stepto(12681,-57855,-1158);
		gcall.Stepto(12437,-57896,-1171);
		gcall.Stepto(12192,-57937,-1186);
		gcall.Stepto(11947,-57981,-1205);
		gcall.Stepto(11702,-58025,-1228);
		gcall.Stepto(11458,-58053,-1258);
		gcall.Stepto(11245,-58072,-1287);
		gcall.Stepto(10812,-58098,-1335);
		gcall.Stepto(10378,-58094,-1297);
		gcall.Stepto(9944,-58080,-1178);
		gcall.Stepto(9511,-58048,-1086);
		gcall.Stepto(9072,-58004,-1062);
		gcall.Stepto(8681,-58020,-1049);
		gcall.Stepto(8633,-58048,-1049);
		gcall.Stepto(8401,-58142,-1049);
		gcall.Stepto(8183,-58256,-1051);
		gcall.Stepto(8133,-58316,-1052);
		gcall.NewSpend(1);
		gcall.Stepto(8014,-58510,-1054);
		gcall.Stepto(8013,-58512,-1054);
		
		Sleep(1000);
		gcall.DeliverQuests(zid,3,L"진소아");
		Sleep(1000);
		gcall.Stepto(8185,-58402,-1047);
		gcall.FenJieByConfig();
		gcall.SellItemByConfig(L"백화정");
		gcall.SortBag();
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

void TaskScript::Task_517(int zid,int taskid)
{
	switch (taskid)
	{
	case 1:
		gcall.NewSpend(2.5);
		gcall.Stepto(7807,-57857,-1055);
		gcall.Stepto(7808,-57857,-1055);
		gcall.Stepto(8099,-57681,-1042);
		gcall.Stepto(8484,-57478,-1039);
		gcall.Stepto(8828,-57211,-1202);
		gcall.Stepto(9136,-56907,-1361);
		gcall.Stepto(9258,-56503,-1381);
		gcall.Stepto(9218,-56071,-1360);
		gcall.Stepto(9092,-55652,-1323);
		gcall.Stepto(8956,-55240,-1251);
		gcall.Stepto(8839,-54819,-1175);
		gcall.Stepto(8727,-54405,-1130);
		gcall.Stepto(8615,-53979,-1110);
		gcall.Stepto(8513,-53563,-1104);
		gcall.Stepto(8457,-53275,-1099);
		gcall.Stepto(8416,-53035,-1091);
		gcall.Stepto(8389,-52790,-1076);
		gcall.Stepto(8380,-52540,-1056);
		gcall.Stepto(8361,-52294,-1048);
		gcall.Stepto(8341,-52045,-1059);
		gcall.Stepto(8321,-51794,-1103);
		gcall.Stepto(8302,-51550,-1169);
		gcall.Stepto(8283,-51301,-1252);
		gcall.Stepto(8264,-51051,-1343);
		gcall.Stepto(8246,-50809,-1427);
		gcall.Stepto(8227,-50561,-1500);
		gcall.Stepto(8208,-50310,-1543);
		gcall.Stepto(8198,-50065,-1567);
		gcall.Stepto(8191,-49815,-1586);
		gcall.Stepto(8184,-49569,-1600);
		gcall.Stepto(8177,-49320,-1612);
		gcall.Stepto(8178,-49071,-1623);
		gcall.Stepto(8189,-48822,-1632);
		gcall.Stepto(8201,-48571,-1642);
		gcall.Stepto(8219,-48316,-1651);
		gcall.Stepto(8253,-47880,-1660);
		gcall.Stepto(8297,-47448,-1661);
		gcall.Stepto(8349,-47021,-1648);
		gcall.Stepto(8411,-46593,-1638);
		gcall.Stepto(8605,-46200,-1635);
		gcall.Stepto(8796,-45818,-1656);
		gcall.Stepto(8987,-45435,-1647);
		gcall.Stepto(9092,-45225,-1638);
		gcall.Stepto(9183,-45053,-1628);
		gcall.Stepto(9275,-44870,-1615);
		gcall.Stepto(9328,-44681,-1600);
		gcall.Stepto(9375,-44489,-1581);
		gcall.Stepto(9433,-44267,-1558);
		gcall.Stepto(9502,-44030,-1528);
		gcall.Stepto(9585,-43796,-1489);
		gcall.Stepto(9659,-43559,-1461);
		gcall.Stepto(9709,-43310,-1447);
		gcall.Stepto(9746,-43084,-1457);
		gcall.Stepto(9798,-42831,-1521);
		gcall.Stepto(9802,-42593,-1586);
		gcall.Stepto(9782,-42573,-1595);
		gcall.Stepto(9607,-42391,-1652);
		gcall.Stepto(9427,-42218,-1695);
		gcall.Stepto(9225,-42075,-1800);
		gcall.Stepto(9036,-41915,-1840);
		gcall.Stepto(8855,-41744,-1829);
		gcall.Stepto(8677,-41579,-1810);
		gcall.Stepto(8658,-41564,-1818);
		gcall.Stepto(8442,-41479,-1882);
		gcall.Stepto(8316,-41358,-2136);
		gcall.Stepto(8233,-41235,-2255);
		gcall.Stepto(8051,-41065,-2263);
		gcall.Stepto(7874,-40893,-2221);
		gcall.Stepto(7883,-40665,-2228);
		gcall.Stepto(8022,-40461,-2256);
		gcall.Stepto(8176,-40268,-2274);
		gcall.Stepto(8324,-40078,-2287);
		gcall.Stepto(8480,-39874,-2301);
		gcall.Stepto(8628,-39682,-2317);
		gcall.Stepto(8771,-39478,-2327);
		gcall.Stepto(8896,-39257,-2329);
		gcall.Stepto(8927,-39014,-2329);
		gcall.Stepto(8947,-38769,-2330);
		gcall.Stepto(9000,-38520,-2330);
		gcall.Stepto(9190,-38368,-2329);
		gcall.Stepto(9427,-38286,-2335);
		gcall.Stepto(9656,-38241,-2348);
		gcall.Stepto(9657,-38240,-2348);
		gcall.NewSpend(1);
		
		if (gcall.GetPlayerXianlu() > 3)
		{
			gcall.randXianlu(3);
		}
		Sleep(1000);
		gcall.DeliverQuests(zid,taskid,L"길동");
		Sleep(1000);
		break;
	case 2:
		gcall.NewSpend(2.5);
		gcall.Stepto(9540,-38444,-2348);
		gcall.Stepto(9502,-38513,-2348);
		gcall.Stepto(9381,-38731,-2331);
		gcall.Stepto(9260,-38948,-2330);
		gcall.Stepto(9232,-38993,-2330);
		gcall.Stepto(9050,-39150,-2330);
		gcall.Stepto(8875,-39330,-2329);
		gcall.Stepto(8705,-39510,-2325);
		gcall.Stepto(8539,-39692,-2309);
		gcall.Stepto(8381,-39879,-2292);
		gcall.Stepto(8230,-40077,-2280);
		gcall.Stepto(8110,-40296,-2268);
		gcall.Stepto(8081,-40539,-2267);
		gcall.Stepto(8115,-40788,-2289);
		gcall.Stepto(8163,-41030,-2311);
		gcall.Stepto(8167,-41058,-2296);
		gcall.NewSpend(1);
		Sleep(1000);
		gcall.PickupTask();
		Sleep(1000);
		if (gcall.GetPlayerXianlu() > 3)
		{
			gcall.randXianlu(3);
		}
		break;
	case 3:
		gcall.NewSpend(2.5);
		gcall.Stepto(8209,-40841,-2339);
		gcall.Stepto(8215,-40818,-2335);
		gcall.Stepto(8376,-40425,-2306);
		gcall.Stepto(8536,-40033,-2308);
		gcall.Stepto(8686,-39621,-2322);
		gcall.Stepto(8824,-39215,-2328);
		gcall.Stepto(8893,-39006,-2329);
		gcall.Stepto(8952,-38777,-2329);
		gcall.Stepto(9070,-38560,-2330);
		gcall.Stepto(9269,-38407,-2329);
		gcall.NewSpend(1);
		gcall.Stepto(9486,-38296,-2341);
		gcall.Stepto(9647,-38223,-2348);
		Sleep(1000);
		if (gcall.GetPlayerXianlu() > 3)
		{
			gcall.randXianlu(3);
		}
		gcall.DeliverQuests(zid,taskid,L"길동");
		Sleep(1000);
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

void TaskScript::Task_518(int zid,int taskid)
{
	switch (taskid)
	{
	case 1:
		gcall.NewSpend(2.5);
		gcall.Stepto(9334,-38056,-2330);
		gcall.Stepto(9334,-38054,-2330);
		gcall.Stepto(9328,-37810,-2334);
		gcall.Stepto(9293,-37564,-2333);
		gcall.Stepto(9146,-37360,-2318);
		gcall.Stepto(9049,-37234,-2308);
		gcall.Stepto(8782,-36893,-2276);
		gcall.Stepto(8515,-36551,-2230);
		gcall.Stepto(8250,-36198,-2169);
		gcall.Stepto(8001,-35850,-2101);
		gcall.Stepto(7746,-35493,-2041);
		gcall.Stepto(7495,-35142,-1960);
		gcall.Stepto(7244,-34790,-1913);
		gcall.Stepto(6992,-34439,-1851);
		gcall.Stepto(6741,-34079,-1787);
		gcall.Stepto(6498,-33713,-1763);
		gcall.Stepto(6259,-33351,-1740);
		gcall.Stepto(6044,-33018,-1702);
		gcall.Stepto(5917,-32804,-1661);
		gcall.Stepto(5800,-32591,-1611);
		gcall.Stepto(5682,-32377,-1554);
		gcall.Stepto(5557,-32151,-1497);
		gcall.Stepto(5439,-31936,-1462);
		gcall.Stepto(5319,-31719,-1435);
		gcall.Stepto(5200,-31503,-1410);
		gcall.Stepto(5092,-31278,-1378);
		gcall.Stepto(4997,-31045,-1343);
		gcall.Stepto(4930,-30809,-1310);
		gcall.Stepto(4876,-30567,-1287);
		gcall.Stepto(4832,-30325,-1272);
		gcall.Stepto(4796,-30077,-1266);
		gcall.Stepto(4760,-29828,-1285);
		gcall.Stepto(4724,-29583,-1323);
		gcall.Stepto(4689,-29340,-1363);
		gcall.Stepto(4653,-29095,-1400);
		gcall.Stepto(4617,-28846,-1419);
		gcall.Stepto(4583,-28609,-1419);
		gcall.Stepto(4552,-28357,-1409);
		gcall.Stepto(4522,-28106,-1395);
		gcall.Stepto(4494,-27863,-1380);
		gcall.Stepto(4466,-27618,-1364);
		gcall.Stepto(4437,-27369,-1351);
		gcall.Stepto(4406,-27098,-1342);
		gcall.Stepto(4356,-26674,-1340);
		gcall.Stepto(4312,-26239,-1357);
		gcall.Stepto(4268,-25800,-1385);
		gcall.Stepto(4226,-25376,-1388);
		gcall.Stepto(4183,-24940,-1370);
		gcall.Stepto(4140,-24503,-1355);
		gcall.Stepto(4097,-24073,-1341);
		gcall.Stepto(4054,-23639,-1338);
		gcall.Stepto(4012,-23208,-1319);
		gcall.Stepto(3969,-22777,-1298);
		gcall.Stepto(3926,-22339,-1260);
		gcall.Stepto(3894,-22019,-1232);
		gcall.Stepto(3870,-21776,-1213);
		gcall.Stepto(3846,-21528,-1192);
		gcall.Stepto(3821,-21275,-1171);
		gcall.Stepto(3797,-21034,-1153);
		gcall.Stepto(3772,-20783,-1133);
		gcall.NewSpend(1);
		gcall.Stepto(3750,-20536,-1108);
		gcall.Stepto(3781,-20291,-1068);
		gcall.Stepto(3817,-20046,-1061);
		Sleep(2000);
		gcall.Stepto(3828,-19936,-1064);
		gcall.Stepto(3838,-19707,-1062);
		gcall.WaitPlans();
		gcall.Stepto(3859,-19466,-1063);
		gcall.Stepto(3875,-19214,-1075);
		gcall.NewSpend(2.5);
		gcall.Stepto(3871,-18968,-1076);
		gcall.Stepto(3867,-18719,-1076);
		gcall.Stepto(3867,-18473,-1069);
		gcall.Stepto(3875,-18224,-1067);
		gcall.Stepto(3888,-17973,-1076);
		gcall.Stepto(3905,-17728,-1082);
		gcall.Stepto(3920,-17479,-1084);
		gcall.Stepto(3920,-17231,-1071);
		gcall.Stepto(3916,-16980,-1054);
		gcall.Stepto(3912,-16728,-1051);
		gcall.Stepto(3910,-16485,-1051);
		gcall.Stepto(3919,-16233,-965);
		gcall.Stepto(3899,-15590,-1031);
		gcall.Stepto(3920,-16144,-926);
		gcall.Stepto(3932,-15895,-822);
		gcall.Stepto(3934,-15849,-822);
		gcall.Stepto(3874,-15769,-822);
		Sleep(5000);
		break;
	case 2:
		Sleep(1000);
		gcall.DeliverQuests(zid,taskid,L"마궁상");
		Sleep(1000);
		break;
	case 3:
		gcall.NewSpend(2.5);
		gcall.Stepto(3936,-15715,-822);
		gcall.Stepto(3894,-15652,-826);
		gcall.Stepto(3707,-15489,-828);
		gcall.Stepto(3481,-15395,-828);
		gcall.Stepto(3349,-15307,-828);
		gcall.Stepto(3182,-15147,-828);
		gcall.Stepto(3056,-14993,-828);
		gcall.Stepto(3026,-14953,-828);
		gcall.Stepto(2985,-14883,-828);
		gcall.Stepto(2922,-14735,-828);
		gcall.Stepto(2861,-14501,-790);
		gcall.Stepto(2871,-14252,-660);
		gcall.Stepto(2902,-14013,-547);
		gcall.Stepto(2957,-13871,-528);
		gcall.Stepto(3105,-13661,-401);
		gcall.Stepto(3204,-13537,-322);
		gcall.Stepto(3322,-13415,-285);
		gcall.Stepto(3444,-13320,-285);
		gcall.Stepto(3596,-13276,-285);
		gcall.Stepto(3757,-13234,-285);
		gcall.Stepto(3950,-13196,-285);
		gcall.Stepto(4075,-13183,-285);
		gcall.Stepto(4080,-13180,-285);
		gcall.Stepto(4107,-13158,-285);
		gcall.Stepto(4195,-12927,-286);
		gcall.Stepto(4216,-12739,-286);
		gcall.Stepto(4216,-12738,-286);
		gcall.Stepto(4208,-12543,-286);
		gcall.Stepto(4193,-12420,-286);
		gcall.Stepto(4168,-12295,-286);
		gcall.Stepto(4008,-12229,-286);
		gcall.Stepto(3871,-12217,-268);
		gcall.Stepto(3763,-12219,-273);
		gcall.Stepto(3669,-12220,-272);
		gcall.Stepto(3665,-12220,-272);
		gcall.Stepto(3618,-12217,-272);
		gcall.Stepto(3609,-12216,-272);
		gcall.Stepto(3547,-12212,-272);
		gcall.Stepto(3546,-12216,-272);
		gcall.NewSpend(1);
		Sleep(1000);
		gcall.PickupTask();
		Sleep(1000);
		gcall.Stepto(3385,-12189,-272);
		gcall.Stepto(3271,-12149,-272);
		gcall.Stepto(3082,-12061,-272);
		gcall.Stepto(2900,-11985,-271);
		gcall.Stepto(2836,-11965,-272);
		Sleep(1000);
		gcall.DeliverQuests(zid,taskid,L"진소아");
		Sleep(1000);
		break;
	case 4:
		gcall.NewSpend(2.5);
		gcall.Stepto(2906,-12058,-271);
		gcall.Stepto(2950,-12074,-271);
		gcall.Stepto(3154,-12157,-272);
		gcall.Stepto(3342,-12198,-272);
		gcall.Stepto(3477,-12210,-272);
		gcall.Stepto(3719,-12238,-272);
		gcall.Stepto(3893,-12258,-286);
		gcall.Stepto(4132,-12285,-286);
		gcall.Stepto(4378,-12303,-286);
		gcall.Stepto(4613,-12317,-268);
		gcall.Stepto(4792,-12326,-272);
		gcall.Stepto(4927,-12332,-272);
		gcall.NewSpend(1);
		Sleep(1000);
		gcall.PickupTask();
		Sleep(1000);
		gcall.Stepto(5138,-12344,-272);
		gcall.Stepto(5158,-12345,-272);
		gcall.Stepto(5265,-12348,-272);
		gcall.Stepto(5426,-12335,-272);
		gcall.Stepto(5627,-12292,-272);
		gcall.Stepto(5643,-12289,-272);
		Sleep(1000);
		gcall.sendcall(id_msg_attack, (LPVOID)0x5E06);//3
		Sleep(1500);
		gcall.sendcall(id_msg_attack, (LPVOID)0x5DE8);//z
		Sleep(800);
		gcall.Kill_Tab();
		gcall.Kill_Tab();
		gcall.Kill_Tab();
		gcall.Kill_Tab();
		gcall.TurnToNear(500);
		gcall.sendcall(id_msg_attack, (LPVOID)0x5e74);//1
		//必杀 소연화
		gcall.FindThenKill(0,500,modeNormal);
		Sleep(1000);
		gcall.Stepto(5643,-12289,-272);
		Sleep(1000);
		gcall.DeliverQuests(zid,taskid,L"소연화");
		Sleep(1000);
		break;
	case 5:
		gcall.NewSpend(2.5);
		gcall.Stepto(5416,-12317,-272);
		gcall.Stepto(5370,-12323,-272);
		gcall.Stepto(5122,-12357,-272);
		gcall.Stepto(4978,-12352,-272);
		gcall.Stepto(4731,-12321,-272);
		gcall.Stepto(4489,-12289,-286);
		gcall.Stepto(4339,-12281,-286);
		gcall.Stepto(4275,-12378,-286);
		gcall.Stepto(4234,-12625,-286);
		gcall.Stepto(4194,-12804,-286);
		gcall.Stepto(4189,-12832,-286);
		gcall.Stepto(4163,-12945,-286);
		gcall.Stepto(4147,-13102,-285);
		gcall.Stepto(4141,-13121,-285);
		gcall.Stepto(3897,-13171,-285);
		gcall.Stepto(3660,-13240,-285);
		gcall.Stepto(3447,-13330,-285);
		gcall.Stepto(3229,-13471,-290);
		gcall.Stepto(3123,-13590,-367);
		gcall.Stepto(2981,-13796,-491);
		gcall.Stepto(2922,-13896,-542);
		gcall.Stepto(2872,-14117,-597);
		gcall.Stepto(2842,-14367,-717);
		gcall.Stepto(2853,-14616,-828);
		gcall.Stepto(2949,-14846,-828);
		gcall.Stepto(3081,-15052,-828);
		gcall.Stepto(3239,-15237,-828);
		gcall.Stepto(3452,-15380,-828);
		gcall.Stepto(3670,-15491,-828);
		gcall.Stepto(3809,-15537,-828);
		gcall.Stepto(3884,-15680,-822);
		gcall.Stepto(3928,-15915,-824);
		gcall.Stepto(3891,-16157,-933);
		gcall.Stepto(3861,-16413,-1047);
		gcall.Stepto(3845,-16657,-1051);
		gcall.Stepto(3835,-16905,-1052);
		gcall.Stepto(3826,-17155,-1066);
		gcall.Stepto(3816,-17402,-1081);
		gcall.Stepto(3809,-17652,-1084);
		gcall.Stepto(3812,-17890,-1079);
		gcall.Stepto(3816,-18150,-1071);
		gcall.Stepto(3818,-18394,-1071);
		gcall.Stepto(3820,-18633,-1076);
		gcall.Stepto(3818,-18894,-1076);
		gcall.Stepto(3815,-19139,-1076);
		gcall.NewSpend(1);
		gcall.Stepto(3814,-19387,-1067);
		gcall.Stepto(3813,-19637,-1062);
		gcall.Stepto(3812,-19885,-1062);
		Sleep(2000);
		gcall.Stepto(3812,-19983,-1062);
		gcall.Stepto(3811,-20218,-1061);
		gcall.WaitPlans();
		gcall.Stepto(3811,-20472,-1099);
		gcall.Stepto(3808,-20719,-1126);
		gcall.Stepto(3724,-20854,-1140);
		gcall.Stepto(3673,-20899,-1144);
		if (gcall.GetPlayerXianlu()>3)
		{
			gcall.randXianlu(3);

		}
		Sleep(1000);
		gcall.Stepto(3484,-21056,-1162);
		gcall.Stepto(3288,-21207,-1182);
		gcall.NewSpend(2.5);
		gcall.Stepto(3092,-21346,-1197);
		gcall.Stepto(2875,-21487,-1225);
		gcall.Stepto(2666,-21617,-1304);
		gcall.Stepto(2446,-21733,-1364);
		gcall.Stepto(2206,-21684,-1368);
		gcall.Stepto(1973,-21591,-1371);
		gcall.Stepto(1747,-21496,-1376);
		gcall.Stepto(1519,-21400,-1380);
		gcall.Stepto(1289,-21297,-1383);
		gcall.Stepto(1063,-21194,-1381);
		gcall.Stepto(842,-21089,-1374);
		gcall.Stepto(619,-20973,-1363);
		gcall.Stepto(397,-20860,-1349);
		gcall.Stepto(196,-20756,-1336);
		gcall.Stepto(195,-20755,-1336);
		gcall.Stepto(72,-20662,-1327);
		gcall.Stepto(52,-20638,-1325);
		gcall.Stepto(-229,-20314,-1301);
		gcall.Stepto(-513,-19985,-1279);
		gcall.Stepto(-791,-19663,-1257);
		gcall.Stepto(-1113,-19356,-1233);
		gcall.Stepto(-1449,-19100,-1212);
		gcall.Stepto(-1834,-18891,-1195);
		gcall.Stepto(-2216,-18698,-1184);
		gcall.Stepto(-2649,-18613,-1186);
		gcall.Stepto(-3086,-18594,-1177);
		gcall.Stepto(-3516,-18634,-1140);
		gcall.Stepto(-3933,-18699,-1081);
		gcall.Stepto(-4348,-18775,-988);
		gcall.Stepto(-4600,-18824,-941);
		gcall.Stepto(-4845,-18863,-928);
		gcall.Stepto(-5093,-18885,-937);
		gcall.Stepto(-5344,-18901,-961);
		gcall.Stepto(-5585,-18926,-1000);
		gcall.Stepto(-5829,-18978,-1053);
		gcall.NewSpend(1);
		gcall.Stepto(-6070,-19049,-1114);
		gcall.Stepto(-6170,-19079,-1141);
		//gcall.NewSpend(1);
		//过滤怪物(그늘사암괴,2);
		//过滤怪物(흙먼지전갈,1);
		//过滤怪物(덕후파,1);
		//过滤怪物(유덕후,1);
		//过滤怪物(인간사냥꾼,1);
		//过滤怪物(유덕후의 졸개,1);
		gcall.FindThenKill(0,900,modeAoe | modeNormal | modePickup );
		gcall.sendcall(id_msg_attack, (LPVOID)0x5DFC);//v

		gcall.Stepto(-6898,-18801,-1242,10,30,5000,TRUE);
		gcall.Stepto(-7619,-18379,-1283,10,30,5000,TRUE);
		gcall.Stepto(-8769,-17855,-1243,10,30,5000,TRUE);
		gcall.FindThenKill(0,900,modeAoe | modeNormal | modePickup );
		gcall.sendcall(id_msg_attack, (LPVOID)0x5DFC);//v

		gcall.Stepto(-8919,-16798,-1231,10,30,5000,TRUE);
		gcall.Stepto(-9411,-15683,-1243,10,30,5000,TRUE);
		gcall.FindThenKill(0,900,modeAoe | modeNormal | modePickup );
		gcall.sendcall(id_msg_attack, (LPVOID)0x5DFC);//v

		gcall.Stepto(-9977,-16129,-1099,10,30,5000,TRUE);
		gcall.Stepto(-10445,-16686,-1008,10,30,5000,TRUE);
		gcall.Stepto(-10961,-17388,-963,10,30,5000,TRUE);
		gcall.FindThenKill(0,900,modeAoe | modeNormal | modePickup );
		gcall.sendcall(id_msg_attack, (LPVOID)0x5DFC);//v

		gcall.Stepto(-11222,-17975,-961,10,30,5000,TRUE);
		gcall.Stepto(-11781,-18524,-974,10,30,5000,TRUE);
		gcall.FindThenKill(0,900,modeAoe | modeNormal | modePickup );
		gcall.sendcall(id_msg_attack, (LPVOID)0x5DFC);//v

		gcall.Stepto(-11117,-19470,-895,10,30,5000,TRUE);
		gcall.FindThenKill(0,900,modeAoe | modeNormal | modePickup );
		gcall.sendcall(id_msg_attack, (LPVOID)0x5DFC);//v

		gcall.Stepto(-10722,-19989,-984,10,30,5000,TRUE);
		gcall.FindThenKill(0,900,modeAoe | modeNormal | modePickup );
		gcall.sendcall(id_msg_attack, (LPVOID)0x5DFC);//v

		gcall.Stepto(-9507,-19646,-1310,10,30,5000,TRUE);
		gcall.FindThenKill(0,900,modeAoe | modeNormal | modePickup );
		gcall.sendcall(id_msg_attack, (LPVOID)0x5DFC);//v

		gcall.Stepto(-9169,-21620,-1346,10,30,5000,TRUE);
		gcall.Stepto(-8933,-21611,-1366,10,30,5000,TRUE);
		gcall.Stepto(-8682,-21601,-1376,10,30,5000,TRUE);
		gcall.Stepto(-8434,-21579,-1383,10,30,5000,TRUE);
		gcall.Stepto(-8189,-21541,-1386,10,30,5000,TRUE);
		gcall.Stepto(-7948,-21484,-1387,10,30,5000,TRUE);
		gcall.Stepto(-7709,-21410,-1386,10,30,5000,TRUE);
		gcall.Stepto(-7477,-21314,-1380,10,30,5000,TRUE);
		gcall.Stepto(-7254,-21206,-1376,10,30,5000,TRUE);
		gcall.Stepto(-7031,-21099,-1368,10,30,5000,TRUE);
		gcall.Stepto(-6807,-20991,-1360,10,30,5000,TRUE);
		gcall.Stepto(-6581,-20882,-1349,10,30,5000,TRUE);
		gcall.Stepto(-6348,-20797,-1334,10,30,5000,TRUE);
		gcall.Stepto(-6114,-20716,-1313,10,30,5000,TRUE);
		gcall.Stepto(-5881,-20629,-1288,10,30,5000,TRUE);
		gcall.Stepto(-5655,-20527,-1258,10,30,5000,TRUE);
		gcall.Stepto(-5451,-20427,-1230,10,30,5000,TRUE);
		gcall.FindThenKill(0,300,modeAoe | modeNormal | modePickup );
		gcall.sendcall(id_msg_attack, (LPVOID)0x5DFC);//v
		gcall.randXianlu(3);
		gcall.FindThenKill(0,900,modeAoe | modeNormal | modePickup );
		gcall.sendcall(id_msg_attack, (LPVOID)0x5DFC);//v
		break;
	case 6:
		//过滤怪物(그늘사암괴,3);
		//过滤怪物(흙먼지전갈,3);
		//过滤怪物(덕후파,3);
		//过滤怪物(유덕후,3);
		//过滤怪物(인간사냥꾼,3);
		//过滤怪物(유덕후의 졸개,3);
		gcall.NewSpend(2.5);
		gcall.Stepto(-5911,-19019,-1076,10,30,5000);
		gcall.Stepto(-5861,-19011,-1065,10,30,5000);
		gcall.Stepto(-5431,-18946,-980,10,30,5000);
		gcall.Stepto(-5027,-18812,-921);
		gcall.Stepto(-4614,-18656,-914);
		gcall.Stepto(-4200,-18526,-1003);
		gcall.Stepto(-3787,-18406,-1077);
		gcall.Stepto(-3372,-18288,-1128);
		gcall.Stepto(-2952,-18173,-1157);
		gcall.Stepto(-2528,-18086,-1152);
		gcall.Stepto(-2095,-18103,-1149);
		gcall.Stepto(-1667,-18173,-1156);
		gcall.Stepto(-1232,-18246,-1148);
		gcall.Stepto(-829,-18331,-1128);
		gcall.Stepto(-591,-18393,-1093);
		gcall.Stepto(-349,-18463,-1076);
		gcall.Stepto(-121,-18553,-1073);
		gcall.Stepto(93,-18678,-1076);
		gcall.Stepto(304,-18812,-1082);
		gcall.Stepto(333,-18830,-1081);
		gcall.Stepto(437,-18928,-1086);
		gcall.Stepto(741,-19245,-1102);
		gcall.Stepto(969,-19609,-1110);
		gcall.Stepto(1193,-19988,-1096);
		gcall.Stepto(1330,-20186,-1113);
		gcall.Stepto(1499,-20376,-1133);
		gcall.Stepto(1720,-20487,-1130);
		gcall.Stepto(1966,-20517,-1129);
		gcall.Stepto(2206,-20539,-1125);
		gcall.Stepto(2459,-20553,-1118);
		gcall.Stepto(2706,-20585,-1123);
		gcall.Stepto(2948,-20630,-1132);
		gcall.Stepto(3190,-20679,-1139);
		gcall.Stepto(3436,-20729,-1138);
		gcall.Stepto(3682,-20770,-1133);
		gcall.Stepto(3704,-20766,-1132);
		gcall.Stepto(3748,-20563,-1111);
		gcall.NewSpend(1);
		gcall.Stepto(3787,-20318,-1073);
		gcall.Stepto(3814,-20073,-1061);
		Sleep(6000);
		gcall.Stepto(3828,-19926,-1062);
		gcall.WaitPlans();
		gcall.Stepto(3837,-19772,-1062);
		gcall.Stepto(3837,-19744,-1062);
		gcall.NewSpend(2.5);
		gcall.Stepto(3822,-19331,-1071);
		gcall.Stepto(3827,-18900,-1076);
		gcall.Stepto(3832,-18460,-1073);
		gcall.Stepto(3836,-18049,-1074);
		gcall.Stepto(3840,-17592,-1084);
		gcall.Stepto(3851,-17159,-1066);
		gcall.Stepto(3876,-16724,-1051);
		gcall.Stepto(3899,-16290,-991);
		gcall.Stepto(3915,-16002,-863);
		gcall.Stepto(3930,-15779,-822);
		gcall.Stepto(3950,-15531,-828);
		gcall.Stepto(3959,-15405,-828);
		gcall.Stepto(3826,-15520,-828);
		gcall.Stepto(3667,-15493,-828);
		gcall.Stepto(3440,-15383,-828);
		gcall.Stepto(3241,-15246,-828);
		gcall.Stepto(3075,-15060,-828);
		gcall.Stepto(2954,-14844,-828);
		gcall.Stepto(2866,-14610,-828);
		gcall.Stepto(2850,-14365,-716);
		gcall.Stepto(2870,-14116,-597);
		gcall.Stepto(2916,-13873,-542);
		gcall.Stepto(2950,-13785,-497);
		gcall.Stepto(3067,-13567,-375);
		gcall.Stepto(3191,-13471,-297);
		gcall.Stepto(3399,-13347,-285);
		gcall.Stepto(3630,-13245,-285);
		gcall.Stepto(3865,-13171,-285);
		gcall.Stepto(4001,-13166,-285);
		gcall.Stepto(4250,-13208,-285);
		gcall.Stepto(4491,-13265,-285);
		gcall.Stepto(4708,-13380,-285);
		gcall.Stepto(4909,-13527,-285);
		gcall.Stepto(5074,-13708,-285);
		gcall.Stepto(5188,-13928,-285);
		gcall.Stepto(5259,-14166,-285);
		gcall.Stepto(5281,-14418,-285);
		gcall.Stepto(5259,-14565,-285);
		gcall.Stepto(5195,-14806,-285);
		gcall.Stepto(5165,-14879,-285);
		gcall.Stepto(5119,-14948,-285);
		gcall.Stepto(4971,-15148,-285);
		gcall.Stepto(4798,-15329,-280);
		gcall.Stepto(4594,-15462,-280);
		gcall.Stepto(4464,-15460,-276);
		gcall.Stepto(4218,-15432,-276);
		gcall.Stepto(4085,-15416,-276);
		gcall.Stepto(4018,-15406,-276);
		gcall.Stepto(4003,-15509,-276);
		gcall.NewSpend(1);
		gcall.Stepto(3949,-15747,-276);
		gcall.Stepto(3930,-15886,-276);
		
		Sleep(1000);
		gcall.DeliverQuests(zid,taskid,L"예하랑");
		Sleep(1000);
		break;
	case 7:
		gcall.NewSpend(2.5);
		gcall.Stepto(3957,-15755,-276);
		gcall.Stepto(3965,-15702,-276);
		gcall.Stepto(4004,-15517,-276);
		gcall.Stepto(4057,-15494,-276);
		gcall.Stepto(4305,-15462,-276);
		gcall.Stepto(4553,-15436,-280);
		gcall.Stepto(4762,-15313,-280);
		gcall.Stepto(4943,-15140,-285);
		gcall.Stepto(5095,-14945,-285);
		gcall.Stepto(5175,-14815,-285);
		gcall.Stepto(5224,-14708,-285);
		gcall.Stepto(5235,-14476,-285);
		gcall.Stepto(5212,-14218,-285);
		gcall.Stepto(5162,-13975,-285);
		gcall.Stepto(5060,-13758,-285);
		gcall.Stepto(4916,-13546,-285);
		gcall.Stepto(4749,-13389,-285);
		gcall.Stepto(4531,-13265,-285);
		gcall.Stepto(4304,-13171,-285);
		gcall.Stepto(4191,-13135,-285);
		gcall.Stepto(4174,-13075,-285);
		gcall.Stepto(4154,-12927,-286);
		gcall.Stepto(4180,-12734,-286);
		gcall.Stepto(4202,-12630,-286);
		gcall.Stepto(4279,-12387,-286);
		gcall.Stepto(4336,-12258,-286);
		gcall.NewSpend(1);
		gcall.Stepto(4505,-12272,-286);
		gcall.Stepto(4753,-12312,-273);
		gcall.Stepto(4927,-12328,-272);
		
		Sleep(1000);
		gcall.PickupTask();
		Sleep(1000);
		gcall.Stepto(5040,-12335,-272);
		gcall.Stepto(5127,-12346,-272);
		gcall.Stepto(5295,-12359,-272);
		gcall.Stepto(5477,-12344,-272);
		gcall.Stepto(5675,-12330,-272);
		Sleep(1000);
		gcall.DeliverQuests(zid,taskid,L"소연화");
		Sleep(1000);
		break;
	case 8:
		break;
	case 9:
		break;

	}
}

void TaskScript::Task_519(int zid,int taskid)
{
	switch (taskid)
	{
	case 1:
		while (true)
		{
			_BAGSTU wuqi;
			gcall.GetGoodsByEquipPos(EQUITMENT_POS::WUQI, &wuqi);
			if(wuqi.name != NULL)
			{
				int len = wcslen(L"각성 요마도끼");//判断是不是当前拿的这个武器
				wchar_t* fixName = new wchar_t[len + 1];
				wcscpy(fixName, L"각성 요마도끼");
				fixName[len] = L' ';
				fixName[len + 1] = L'\0';
				if(wcsstr(wuqi.name, fixName) != NULL)
				{
					if (wuqi.m_PingJi == 5 &&
						wuqi.m_DangQianJingYanZhi == wuqi.m_DangQianJingYanZongZhi)
					{
						gcall.HeChengWuQi_Po5(EQUITMENT_POS::WUQI,L"제룡도끼");
						Sleep(1000);
						/*gcall.XieBaoShi(0);
						Sleep(1000);
						gcall.XieBaoShi(1);
						Sleep(1000);*/
					}else if (wuqi.m_PingJi == 10 &&
						wuqi.m_DangQianJingYanZhi == wuqi.m_DangQianJingYanZongZhi)
					{
						gcall.HeChengWuQi_Po10(EQUITMENT_POS::WUQI,L"금강도끼");
						Sleep(1000);
						//gcall.JiaBaoShi(0,L"");//蓝色5角紫
						//Sleep(1000);
						//gcall.JiaBaoShi(1,L"");//蓝色4角红
						//Sleep(1000);
						break;
					}else
					{
						gcall.HeChengWuQiByHun(EQUITMENT_POS::WUQI);
					}
				}else
				{
					break;
				}
			}else
			{
				//可能出错
				break;
			}
		}
		//这里跳出时应该是破5了。


		_BAGSTU wuqi;
		ZeroMemory(&wuqi,sizeof(_BAGSTU));
		while (true)
		{
			if (gcall.GetGoodsByEquipPos(EQUITMENT_POS::WUQI, &wuqi) == FALSE)
			{
				gcall.WearEquipment(L"진 요마도끼 1단계",EQUITMENT_POS::WUQI);
				Sleep(1000);
			}
			if (wuqi.m_DangQianJingYanZhi != wuqi.m_DangQianJingYanZongZhi )
			{
				gcall.HeChengWuQiByHun(EQUITMENT_POS::WUQI);
				Sleep(1000);
			}else
			{
				break;
			}
		}
		
		gcall.NewSpend(2.5);
		gcall.Stepto(5492,-12352,-272);
		gcall.Stepto(5434,-12351,-272);
		gcall.Stepto(5236,-12352,-272);
		gcall.Stepto(5022,-12354,-272);
		gcall.Stepto(4864,-12334,-272);
		gcall.Stepto(4614,-12320,-268);
		gcall.Stepto(4372,-12303,-286);
		gcall.Stepto(4294,-12298,-286);
		gcall.Stepto(4251,-12497,-286);
		gcall.Stepto(4199,-12741,-286);
		gcall.Stepto(4184,-12836,-286);
		gcall.Stepto(4171,-12950,-286);
		gcall.Stepto(4131,-13170,-285);
		gcall.Stepto(4021,-13178,-285);
		gcall.Stepto(3772,-13226,-285);
		gcall.Stepto(3545,-13300,-285);
		gcall.Stepto(3321,-13420,-285);
		gcall.Stepto(3135,-13577,-358);
		gcall.Stepto(3011,-13794,-481);
		gcall.Stepto(2933,-14033,-554);
		gcall.Stepto(2887,-14276,-670);
		gcall.Stepto(2906,-14424,-750);
		gcall.Stepto(2902,-14477,-778);
		gcall.Stepto(2928,-14722,-828);
		gcall.Stepto(3043,-14940,-828);
		gcall.Stepto(3190,-15140,-828);
		gcall.Stepto(3385,-15299,-828);
		gcall.Stepto(3594,-15433,-828);
		gcall.Stepto(3809,-15539,-828);
		gcall.Stepto(3852,-15592,-828);
		gcall.Stepto(3854,-15721,-822);
		gcall.NewSpend(1);
		Sleep(1000);
		gcall.DeliverQuests(zid,taskid,L"마궁상");
		Sleep(1000);
		
		break;
	case 2:
		gcall.NewSpend(2.5);
		gcall.Stepto(3877,-15867,-822);
		gcall.Stepto(3877,-16127,-920);
		gcall.Stepto(3867,-16557,-1051);
		gcall.Stepto(3858,-16991,-1055);
		gcall.Stepto(3858,-17427,-1083);
		gcall.Stepto(3860,-17855,-1080);
		gcall.Stepto(3863,-18293,-1065);
		gcall.Stepto(3867,-18724,-1076);
		gcall.Stepto(3866,-19160,-1075);
		gcall.Stepto(3850,-19594,-1062);
		gcall.NewSpend(1);
		gcall.Stepto(3838,-19895,-1062);
		gcall.Stepto(3837,-19906,-1062);
		Sleep(2000);
		gcall.Stepto(3833,-19986,-1061);
		gcall.WaitPlans();
		gcall.Stepto(3811,-20206,-1061);
		gcall.Stepto(3770,-20571,-1112);
		gcall.NewSpend(2.5);
		gcall.Stepto(3774,-21006,-1151);
		gcall.Stepto(3792,-21440,-1186);
		gcall.Stepto(3789,-21678,-1206);
		gcall.Stepto(3787,-21682,-1206);
		gcall.Stepto(3609,-22003,-1233);
		gcall.Stepto(3409,-22385,-1267);
		gcall.Stepto(3192,-22764,-1306);
		gcall.Stepto(2868,-23051,-1329);
		gcall.Stepto(2514,-23308,-1330);
		gcall.Stepto(2155,-23544,-1318);
		gcall.Stepto(1784,-23773,-1308);
		gcall.Stepto(1416,-23984,-1282);
		gcall.Stepto(1015,-24148,-1261);
		gcall.Stepto(749,-24350,-1238);
		gcall.Stepto(585,-24534,-1243);
		gcall.Stepto(419,-24719,-1267);
		gcall.Stepto(250,-24904,-1296);
		gcall.Stepto(76,-25076,-1321);
		gcall.Stepto(-100,-25250,-1343);
		gcall.Stepto(-281,-25426,-1353);
		gcall.Stepto(-462,-25595,-1352);
		gcall.Stepto(-650,-25751,-1348);
		gcall.Stepto(-855,-25893,-1343);
		gcall.Stepto(-1064,-26029,-1335);
		gcall.Stepto(-1274,-26165,-1321);
		gcall.Stepto(-1493,-26273,-1309);
		gcall.Stepto(-1738,-26303,-1299);
		gcall.Stepto(-1986,-26332,-1294);
		gcall.Stepto(-2234,-26360,-1295);
		gcall.Stepto(-2481,-26387,-1305);
		gcall.Stepto(-2724,-26414,-1311);
		gcall.Stepto(-2971,-26442,-1313);
		gcall.Stepto(-3220,-26462,-1313);
		gcall.Stepto(-3419,-26468,-1313);
		gcall.Stepto(-3603,-26474,-1312);
		gcall.Stepto(-4032,-26487,-1314);
		gcall.Stepto(-4469,-26500,-1304);
		gcall.Stepto(-4898,-26513,-1252);
		gcall.Stepto(-5342,-26526,-1186);
		gcall.Stepto(-5757,-26539,-1110);
		gcall.Stepto(-6209,-26553,-1036);
		gcall.Stepto(-6635,-26565,-1052);
		gcall.Stepto(-7078,-26579,-1115);
		gcall.Stepto(-7505,-26597,-1102);
		gcall.Stepto(-7945,-26624,-1047);
		gcall.Stepto(-8286,-26647,-1094);
		gcall.Stepto(-8535,-26659,-1133);
		gcall.Stepto(-8785,-26662,-1169);
		gcall.Stepto(-9033,-26659,-1197);
		gcall.Stepto(-9279,-26643,-1216);
		gcall.Stepto(-9520,-26580,-1223);
		gcall.Stepto(-9762,-26508,-1222);
		gcall.Stepto(-9997,-26437,-1219);
		gcall.Stepto(-10233,-26367,-1219);
		gcall.Stepto(-10469,-26296,-1222);
		gcall.Stepto(-10709,-26224,-1213);
		gcall.Stepto(-10951,-26151,-1190);
		gcall.Stepto(-11186,-26073,-1173);
		gcall.Stepto(-11419,-25994,-1166);
		gcall.Stepto(-11656,-25914,-1184);
		gcall.Stepto(-11888,-25829,-1213);
		gcall.Stepto(-12118,-25737,-1235);
		gcall.Stepto(-12351,-25653,-1273);
		gcall.Stepto(-12590,-25577,-1367);
		gcall.Stepto(-12830,-25509,-1517);
		gcall.Stepto(-13070,-25449,-1639);
		gcall.Stepto(-13311,-25393,-1733);
		gcall.Stepto(-13553,-25339,-1784);
		gcall.Stepto(-13796,-25282,-1815);
		gcall.Stepto(-14036,-25220,-1859);
		gcall.Stepto(-14281,-25155,-1903);
		gcall.Stepto(-14468,-25105,-1934);
		gcall.Stepto(-14854,-24997,-1949);
		gcall.Stepto(-15273,-24877,-2019);
		gcall.Stepto(-15693,-24812,-2094);
		gcall.Stepto(-16122,-24886,-2097);
		gcall.Stepto(-16519,-25065,-2074);
		gcall.Stepto(-16736,-25175,-2048);
		gcall.Stepto(-16935,-24932,-1949);
		gcall.Stepto(-17193,-24579,-1913);
		gcall.Stepto(-17423,-24215,-1901);
		gcall.Stepto(-17646,-23836,-1901);
		gcall.Stepto(-17869,-23460,-1901);
		gcall.Stepto(-18132,-23128,-1901);
		gcall.Stepto(-18496,-22878,-1892);
		gcall.Stepto(-18881,-22729,-1843);
		gcall.Stepto(-19123,-22658,-1778);
		gcall.Stepto(-19364,-22591,-1694);
		gcall.Stepto(-19601,-22533,-1619);
		gcall.Stepto(-19848,-22496,-1531);
		gcall.Stepto(-20099,-22497,-1462);
		gcall.Stepto(-20310,-22552,-1420);
		gcall.Stepto(-20319,-22598,-1419);
		gcall.Stepto(-20229,-22824,-1406);
		gcall.Stepto(-20086,-23032,-1375);
		gcall.Stepto(-19981,-23257,-1336);
		gcall.Stepto(-19934,-23502,-1308);
		gcall.Stepto(-19946,-23746,-1270);
		gcall.Stepto(-19992,-23909,-1237);
		gcall.Stepto(-20033,-24028,-1210);
		gcall.Stepto(-20132,-24254,-1201);
		gcall.Stepto(-20248,-24449,-1224);
		gcall.Stepto(-20398,-24632,-1254);
		gcall.Stepto(-20445,-24683,-1259);
		gcall.Stepto(-20612,-24861,-1275);
		gcall.Stepto(-20785,-25042,-1288);
		gcall.Stepto(-20960,-25218,-1289);
		gcall.Stepto(-21139,-25389,-1292);
		gcall.Stepto(-21330,-25549,-1291);
		gcall.NewSpend(1);
		gcall.Stepto(-21523,-25704,-1285);
		gcall.Stepto(-21726,-25840,-1268);
		gcall.Stepto(-21938,-25971,-1243);
		gcall.Stepto(-22165,-26076,-1217);
		gcall.Stepto(-22413,-26112,-1202);
		Sleep(2000);
		gcall.Stepto(-22614,-26129,-1192);
		gcall.WaitPlans();
		gcall.Stepto(-22797,-26169,-1178);
		gcall.Stepto(-23040,-26222,-1152);
		gcall.NewSpend(2.5);
		gcall.Stepto(-23282,-26274,-1124);
		gcall.Stepto(-23523,-26324,-1096);
		gcall.Stepto(-23771,-26340,-1093);
		gcall.Stepto(-24022,-26318,-1084);
		gcall.Stepto(-24232,-26268,-1063);
		gcall.Stepto(-24405,-26216,-1039);
		gcall.Stepto(-24642,-26147,-1007);
		gcall.Stepto(-24874,-26052,-949);
		gcall.Stepto(-25063,-25891,-859);
		gcall.Stepto(-25247,-25724,-738);
		gcall.Stepto(-25341,-25577,-685);
		gcall.Stepto(-25243,-25394,-679);
		gcall.Stepto(-25185,-25266,-679);
		gcall.NewSpend(1);
		Sleep(1000);
		gcall.DeliverQuests(zid,taskid,L"진소아");
		Sleep(1000);
		break;
	case 3:
		gcall.NewSpend(2.5);
		gcall.Stepto(-25745,-25546,-679);
		gcall.Stepto(-25777,-25524,-679);
		gcall.Stepto(-25978,-25374,-679);
		gcall.Stepto(-26178,-25230,-679);
		gcall.Stepto(-26389,-25107,-679);
		gcall.Stepto(-26608,-24987,-685);
		gcall.Stepto(-26825,-24866,-753);
		gcall.Stepto(-27038,-24732,-852);
		gcall.Stepto(-27222,-24602,-878);
		gcall.Stepto(-27440,-24448,-888);
		gcall.Stepto(-27639,-24305,-942);
		gcall.Stepto(-27841,-24155,-1005);
		gcall.Stepto(-28028,-23994,-1052);
		gcall.Stepto(-28195,-23813,-1076);
		gcall.Stepto(-28344,-23609,-1081);
		gcall.Stepto(-28481,-23401,-1081);
		gcall.Stepto(-28608,-23188,-1081);
		gcall.Stepto(-28734,-22977,-1074);
		gcall.Stepto(-28857,-22764,-1060);
		gcall.Stepto(-28988,-22553,-1056);
		gcall.Stepto(-29132,-22348,-1085);
		gcall.Stepto(-29279,-22147,-1217);
		gcall.Stepto(-29431,-21950,-1358);
		gcall.Stepto(-29608,-21780,-1401);
		gcall.Stepto(-29798,-21614,-1438);
		gcall.Stepto(-29986,-21452,-1450);
		gcall.Stepto(-30174,-21293,-1468);
		gcall.Stepto(-30368,-21139,-1480);
		gcall.Stepto(-30565,-20989,-1480);
		gcall.Stepto(-30760,-20834,-1480);
		gcall.Stepto(-30924,-20646,-1480);
		gcall.Stepto(-30966,-20570,-1480);
		gcall.Stepto(-31019,-20378,-1480);
		gcall.Stepto(-31067,-20132,-1480);
		gcall.Stepto(-31104,-19889,-1477);
		gcall.Stepto(-31133,-19688,-1479);
		gcall.NewSpend(1);
		gcall.Stepto(-31165,-19517,-1486);
		gcall.Stepto(-31136,-19692,-1479);
		Sleep(2000);
		gcall.Stepto(-31157,-19532,-1480);
		gcall.WaitPlans();
		gcall.Stepto(-31160,-19504,-1480);
		Sleep(5000);
		break;
	case 4:
		gcall.NewSpend(2.5);
		gcall.Stepto(-31210,-19173,-1479);
		gcall.Stepto(-31196,-19099,-1480);
		gcall.Stepto(-31158,-18857,-1480);
		gcall.Stepto(-31107,-18616,-1480);
		gcall.Stepto(-30962,-18413,-1480);
		gcall.Stepto(-30787,-18244,-1480);
		gcall.Stepto(-30597,-18075,-1480);
		gcall.Stepto(-30424,-17908,-1480);
		gcall.Stepto(-30271,-17717,-1480);
		gcall.Stepto(-30128,-17503,-1480);
		gcall.Stepto(-29992,-17297,-1480);
		gcall.Stepto(-29857,-17092,-1480);
		gcall.Stepto(-29709,-16891,-1480);
		gcall.Stepto(-29541,-16708,-1480);
		gcall.Stepto(-29382,-16520,-1480);
		gcall.Stepto(-29242,-16344,-1479);
		gcall.Stepto(-29217,-16304,-1478);
		gcall.Stepto(-29207,-16286,-1477);
		gcall.NewSpend(1);
		Sleep(1000);
		gcall.DeliverQuests(zid,taskid,L"소연화");
		Sleep(1000);
		break;
	case 5:
		//过滤怪物(해골 대장,2);
		//过滤怪物(해골 주술사,2);
		//过滤怪物(당여월 친위대,1);
		Sleep(1000);
		gcall.Stepto(-29884,-16122,-1480,10,10,3000);
		Sleep(2000);
		gcall.FindThenKill(0,500,modeAoe | modeNormal);
		gcall.Stepto(L"소연화");
		gcall.FindThenKill(0,500,modeAoe | modeNormal);

		gcall.Stepto(-30387,-15980,-1480,10,10,3000);
		Sleep(2000);
		gcall.FindThenKill(0,600,modeAoe | modeNormal);
		gcall.Stepto(L"소연화");
		gcall.FindThenKill(0,500,modeAoe | modeNormal);

		gcall.Stepto(-31025,-15511,-1475,10,10,3000);
		Sleep(2000);
		gcall.FindThenKill(0,600,modeAoe | modeNormal);
		gcall.Stepto(L"소연화");
		gcall.FindThenKill(0,500,modeAoe | modeNormal);

		gcall.Stepto(-31048,-15403,-1472,10,10,3000);
		gcall.Stepto(-31114,-15164,-1439,10,10,3000);
		gcall.Stepto(-31180,-14925,-1373,10,10,3000);
		gcall.Stepto(-31209,-14819,-1373);
		gcall.Stepto(-31207,-14737,-1373);
		gcall.Stepto(-31186,-14491,-1373);
		gcall.Stepto(-31185,-14483,-1373);
		Sleep(2000);
		gcall.FindThenKill(0,500,modeAoe | modeNormal);
		gcall.Stepto(L"소연화");
		gcall.FindThenKill(0,500,modeAoe | modeNormal);

		gcall.Stepto(-31175,-14372,-1373,10,10,3000);
		gcall.Stepto(-31154,-14125,-1373,10,10,3000);
		gcall.Stepto(-31132,-13878,-1373,10,10,3000);
		gcall.Stepto(-31110,-13631,-1373,10,10,3000);
		gcall.Stepto(-31089,-13384,-1373);
		gcall.Stepto(-31078,-13136,-1373);
		gcall.Stepto(-31071,-12888,-1373);
		gcall.Stepto(-31063,-12641,-1373);
		gcall.Stepto(-31059,-12514,-1373);
		gcall.Stepto(-31133,-12334,-1373);
		gcall.Stepto(-31194,-12979,-1373);
		Sleep(2000);
		
		gcall.FindThenKill(0,500,modeAoe | modeNormal);
		gcall.Stepto(L"소연화");
		gcall.FindThenKill(0,500,modeAoe | modeNormal);


		gcall.Stepto(-31011,-12396,-1373,10,10,3000);
		gcall.Stepto(-30928,-12199,-1373,10,10,3000);
		gcall.Stepto(-30966,-12026,-1373,10,10,3000);
		gcall.Stepto(-31016,-11783,-1373);
		gcall.Stepto(-31074,-11542,-1314);
		gcall.Stepto(-31132,-11301,-1205);
		gcall.Stepto(-31183,-11085,-1162);
		Sleep(2000);
		gcall.FindThenKill(0,600,modeAoe | modeNormal);
		gcall.Stepto(L"소연화");
		gcall.FindThenKill(0,500,modeAoe | modeNormal);


		gcall.Stepto(-31180,-10867,-1146,10,10,3000);
		gcall.Stepto(-31176,-10619,-1144,10,10,3000);
		gcall.Stepto(-31172,-10371,-1144,10,10,3000);
		gcall.Stepto(-31169,-10123,-1144);
		gcall.Stepto(-31165,-9875,-1144);
		gcall.Stepto(-31161,-9627,-1144);
		gcall.Stepto(-31157,-9379,-1144);
		gcall.Stepto(-31151,-9130,-1133);
		gcall.Stepto(-31136,-8882,-1133);
		gcall.Stepto(-31120,-8635,-1133);
		gcall.Stepto(-31101,-8388,-1133);
		gcall.Stepto(-31080,-8141,-1125);
		gcall.Stepto(-31057,-7894,-1125);
		gcall.Stepto(-31035,-7649,-1125);
		gcall.Stepto(-31016,-7485,-1125);
		Sleep(3000);
		gcall.FindThenKill(0,500,modeAoe | modeNormal);
		gcall.Stepto(L"소연화");
		gcall.FindThenKill(0,500,modeAoe | modeNormal);

		gcall.NewSpend(2.5);
		gcall.Stepto(-31162,-9145,-1133,10,10,3000);
		gcall.Stepto(-31163,-9310,-1133,10,10,3000);
		gcall.Stepto(-31161,-9558,-1144,10,10,3000);
		gcall.Stepto(-31158,-9806,-1144);
		gcall.Stepto(-31155,-10054,-1144);
		gcall.Stepto(-31153,-10302,-1144);
		gcall.Stepto(-31150,-10550,-1144);
		gcall.Stepto(-31147,-10798,-1144);
		gcall.Stepto(-31144,-11046,-1161);
		gcall.Stepto(-31141,-11294,-1203);
		gcall.Stepto(-31137,-11539,-1313);
		gcall.Stepto(-31143,-11787,-1373);
		gcall.Stepto(-31185,-12035,-1373);
		gcall.Stepto(-31201,-12282,-1373);
		gcall.Stepto(-31204,-12530,-1373);
		gcall.Stepto(-31205,-12778,-1373);
		gcall.Stepto(-31200,-13026,-1373);
		gcall.Stepto(-31193,-13273,-1373);
		gcall.Stepto(-31185,-13521,-1373);
		gcall.Stepto(-31183,-13769,-1373);
		gcall.Stepto(-31181,-14017,-1373);
		gcall.Stepto(-31180,-14265,-1373);
		gcall.Stepto(-31178,-14513,-1373);
		gcall.Stepto(-31176,-14762,-1373);
		gcall.Stepto(-31174,-15010,-1383);
		gcall.Stepto(-31126,-15252,-1464);
		gcall.Stepto(-31048,-15480,-1474);
		gcall.Stepto(-30936,-15700,-1475);
		gcall.Stepto(-30784,-15900,-1480);
		gcall.Stepto(-30580,-16044,-1480);
		gcall.Stepto(-30377,-16184,-1480);
		gcall.Stepto(-30181,-16341,-1480);
		gcall.Stepto(-29988,-16496,-1480);
		gcall.Stepto(-29880,-16583,-1480);
		gcall.NewSpend(1);
		gcall.Stepto(L"소연화");
		gcall.FindThenKill(0,300,modeAoe | modeNormal);
		
		break;
	case 6:
		//过滤怪物(해골 대장,3);
		//过滤怪物(해골 주술사,3);
		//过滤怪物(당여월 친위대,3);
		gcall.NewSpend(2.5);
		gcall.Stepto(-30119,-16996,-1480);
		gcall.Stepto(-30146,-16950,-1480);
		gcall.Stepto(-30280,-16742,-1480);
		gcall.Stepto(-30422,-16538,-1480);
		gcall.Stepto(-30564,-16335,-1480);
		gcall.Stepto(-30706,-16132,-1480);
		gcall.Stepto(-30848,-15928,-1480);
		gcall.Stepto(-30990,-15725,-1475);
		gcall.Stepto(-31131,-15521,-1474);
		gcall.Stepto(-31155,-15391,-1471);
		gcall.Stepto(-31179,-15144,-1431);
		gcall.Stepto(-31202,-14897,-1373);
		gcall.Stepto(-31224,-14650,-1373);
		gcall.Stepto(-31221,-14402,-1373);
		gcall.Stepto(-31220,-14154,-1373);
		gcall.Stepto(-31219,-13906,-1373);
		gcall.Stepto(-31220,-13658,-1373);
		gcall.Stepto(-31221,-13410,-1373);
		gcall.Stepto(-31222,-13162,-1373);
		gcall.Stepto(-31223,-12913,-1373);
		gcall.Stepto(-31223,-12667,-1373);
		gcall.Stepto(-31223,-12422,-1373);
		gcall.Stepto(-31223,-12168,-1373);
		gcall.Stepto(-31222,-11922,-1373);
		gcall.Stepto(-31222,-11674,-1372);
		gcall.Stepto(-31220,-11426,-1261);
		gcall.Stepto(-31209,-11178,-1162);
		gcall.Stepto(-31213,-10930,-1147);
		gcall.Stepto(-31217,-10682,-1144);
		gcall.Stepto(-31220,-10434,-1144);
		gcall.Stepto(-31224,-10186,-1144);
		gcall.Stepto(-31227,-9934,-1144);
		gcall.Stepto(-31221,-9686,-1144);
		gcall.Stepto(-31212,-9438,-1144);
		gcall.Stepto(-31203,-9190,-1133);
		gcall.Stepto(-31189,-8942,-1133);
		gcall.Stepto(-31173,-8695,-1133);
		gcall.Stepto(-31156,-8448,-1133);
		gcall.Stepto(-31136,-8200,-1125);
		gcall.Stepto(-31110,-7954,-1125);
		gcall.NewSpend(1);
		gcall.Stepto(-31083,-7707,-1125);
		gcall.Stepto(-31067,-7557,-1125);
		Sleep(1000);
		gcall.DeliverQuests(zid,taskid,L"백운선사");
		Sleep(1000);
		break;
	case 7:
		gcall.Stepto(-31007,-7656,-1125);
		Sleep(1000);
		gcall.DeliverQuests(zid,taskid,L"소연화");
		Sleep(1000);
		break;
	case 8:
		gcall.NewSpend(2.5);
		gcall.Stepto(-31020,-7810,-1125);
		gcall.Stepto(-31020,-7857,-1125);
		gcall.Stepto(-31058,-8293,-1125);
		gcall.Stepto(-31137,-8706,-1133);
		gcall.Stepto(-31210,-9137,-1133);
		gcall.Stepto(-31243,-9566,-1144);
		gcall.Stepto(-31198,-10000,-1144);
		gcall.Stepto(-31160,-10441,-1144);
		gcall.Stepto(-31155,-10680,-1144);
		gcall.Stepto(-31159,-10931,-1148);
		gcall.Stepto(-31162,-11185,-1162);
		gcall.Stepto(-31152,-11427,-1261);
		gcall.Stepto(-31145,-11674,-1372);
		gcall.Stepto(-31149,-11920,-1373);
		gcall.Stepto(-31151,-12151,-1373);
		gcall.Stepto(-31149,-12394,-1373);
		gcall.Stepto(-31146,-12640,-1373);
		gcall.Stepto(-31147,-12889,-1373);
		gcall.Stepto(-31155,-13138,-1373);
		gcall.Stepto(-31168,-13393,-1373);
		gcall.Stepto(-31181,-13635,-1373);
		gcall.Stepto(-31190,-13869,-1373);
		gcall.Stepto(-31197,-14175,-1373);
		gcall.Stepto(-31198,-14606,-1373);
		gcall.Stepto(-31194,-15049,-1392);
		gcall.Stepto(-31190,-15484,-1474);
		gcall.Stepto(-31186,-15911,-1480);
		gcall.Stepto(-31161,-16355,-1480);
		gcall.Stepto(-31121,-16785,-1480);
		gcall.Stepto(-31079,-17214,-1480);
		gcall.Stepto(-31047,-17653,-1480);
		gcall.Stepto(-31043,-18092,-1480);
		gcall.Stepto(-31073,-18518,-1480);
		gcall.Stepto(-31114,-18952,-1480);
		gcall.Stepto(-31142,-19249,-1480);
		gcall.Stepto(-31157,-19443,-1480);
		gcall.Stepto(-31155,-19690,-1479);
		gcall.Stepto(-31155,-19693,-1479);
		gcall.Stepto(-31156,-19716,-1479);
		gcall.Stepto(-31154,-19774,-1479);
		gcall.Stepto(-31150,-20022,-1480);
		gcall.Stepto(-31146,-20272,-1480);
		gcall.WaitPlans();
		gcall.Stepto(-31143,-20438,-1480);
		gcall.NewSpend(2.5);
		gcall.Stepto(-30537,-20676,-1480);
		gcall.Stepto(-30528,-20680,-1480);
		gcall.Stepto(-30324,-20761,-1480);
		gcall.Stepto(-29992,-20920,-1458);
		gcall.Stepto(-29589,-21076,-1433);
		gcall.Stepto(-29181,-21223,-1379);
		gcall.Stepto(-29092,-21274,-1374);
		gcall.Stepto(-28983,-21424,-1363);
		gcall.Stepto(-28720,-21772,-1151);
		gcall.Stepto(-28476,-22126,-1056);
		gcall.Stepto(-28397,-22311,-1056);
		gcall.Stepto(-28381,-22749,-1073);
		gcall.Stepto(-28378,-23168,-1081);
		gcall.Stepto(-28329,-23610,-1081);
		gcall.Stepto(-28128,-23989,-1065);
		gcall.Stepto(-27840,-24317,-981);
		gcall.Stepto(-27490,-24552,-885);
		gcall.Stepto(-27155,-24743,-867);
		gcall.Stepto(-26932,-24860,-793);
		gcall.Stepto(-26711,-24968,-691);
		gcall.Stepto(-26486,-25071,-679);
		gcall.Stepto(-26256,-25166,-679);
		gcall.Stepto(-26026,-25256,-679);
		gcall.Stepto(-25790,-25339,-679);
		gcall.Stepto(-25546,-25370,-679);
		gcall.NewSpend(1);
		gcall.Stepto(-25295,-25360,-679);
		gcall.Stepto(-25095,-25358,-679);
		Sleep(1000);
		gcall.DeliverQuests(zid,taskid,L"진소아");
		Sleep(1000);
		break;
	case 9:
		break;

	}
}

void TaskScript::Task_520(int zid,int taskid)
{
	BOOL flag30 = FALSE;
	BOOL flag = FALSE;
	switch (taskid)
	{
	case 1:
		gcall.NewSpend(2.5);
		gcall.Stepto(-25285,-25294,-679);
		gcall.Stepto(-25361,-25266,-679);
		gcall.Stepto(-25594,-25176,-679);
		gcall.Stepto(-25863,-25142,-679);
		gcall.Stepto(-26288,-25067,-679);
		gcall.Stepto(-26697,-24913,-698);
		gcall.Stepto(-27066,-24720,-856);
		gcall.Stepto(-27445,-24489,-886);
		gcall.Stepto(-27789,-24221,-988);
		gcall.Stepto(-28074,-23891,-1062);
		gcall.Stepto(-28320,-23539,-1081);
		gcall.Stepto(-28560,-23166,-1081);
		gcall.Stepto(-28773,-22799,-1063);
		gcall.Stepto(-29021,-22464,-1058);
		gcall.Stepto(-29122,-22341,-1084);
		gcall.Stepto(-29296,-22165,-1216);
		gcall.Stepto(-29486,-22007,-1358);
		gcall.Stepto(-29660,-21877,-1411);
		gcall.Stepto(-29902,-21622,-1452);
		gcall.Stepto(-30202,-21311,-1474);
		gcall.Stepto(-30504,-20998,-1480);
		gcall.Stepto(-30644,-20862,-1480);
		gcall.Stepto(-30815,-20805,-1480);
		gcall.Stepto(-31217,-20653,-1480);
		gcall.Stepto(-31491,-20520,-1480);
		gcall.Stepto(-31653,-20421,-1480);
		gcall.Stepto(-31831,-20283,-1480);
		gcall.Stepto(-32027,-20128,-1480);
		gcall.Stepto(-32040,-20120,-1480);
		gcall.Stepto(-32049,-20118,-1480);
		gcall.Stepto(-32291,-20090,-1416);
		gcall.Stepto(-32358,-20095,-1414);
		gcall.Stepto(-32417,-20100,-1410);
		gcall.Stepto(-32608,-20109,-1410);
		gcall.Stepto(-32653,-20110,-1410);
		gcall.Stepto(-32878,-20112,-1410);
		gcall.Stepto(-33011,-20111,-1410);
		gcall.NewSpend(2.5);
		gcall.Stepto(-33262,-20109,-1419);
		gcall.Stepto(-33509,-20108,-1419);
		gcall.Stepto(-33757,-20106,-1419);
		gcall.Stepto(-34006,-20104,-1419);
		gcall.Stepto(-34249,-20102,-1419);
		gcall.Stepto(-34422,-20101,-1419);
		gcall.Stepto(-34445,-19956,-1419);
		gcall.Stepto(-34455,-19708,-1419);
		gcall.Stepto(-34456,-19523,-1419);
		gcall.Stepto(-34460,-19449,-1419);
		gcall.Stepto(-34505,-19448,-1419);
		gcall.Stepto(-34748,-19459,-1450);
		gcall.Stepto(-34998,-19462,-1493);
		gcall.Stepto(-35249,-19465,-1510);
		gcall.Stepto(-35498,-19467,-1538);
		gcall.Stepto(-35723,-19469,-1640);
		gcall.Stepto(-35995,-19472,-1780);
		gcall.Stepto(-36243,-19475,-1903);
		gcall.Stepto(-36486,-19476,-2015);
		gcall.Stepto(-36737,-19466,-2110);
		gcall.Stepto(-36942,-19460,-2157);
		gcall.Stepto(-37142,-19450,-2159);
		gcall.Stepto(-37341,-19438,-2155);
		gcall.Stepto(-37541,-19422,-2148);
		gcall.Stepto(-37735,-19404,-2171);
		gcall.Stepto(-37929,-19378,-2203);
		gcall.Stepto(-38125,-19338,-2233);
		gcall.Stepto(-38317,-19272,-2265);
		gcall.Stepto(-38493,-19186,-2289);
		gcall.Stepto(-38675,-19102,-2311);
		gcall.Stepto(-38839,-19052,-2310);
		
		Sleep(1000);
		gcall.FindThenKill(0,500,modeAoe | modeNormal | modePickup);
		Sleep(1000);
		gcall.NewSpend(2.5);
		gcall.Stepto(-38839,-19052,-2310);
		gcall.Stepto(-38675,-19102,-2311);
		gcall.Stepto(-38493,-19186,-2289);
		gcall.Stepto(-38317,-19272,-2265);
		gcall.Stepto(-38125,-19338,-2233);
		gcall.Stepto(-37929,-19378,-2203);
		gcall.Stepto(-37735,-19404,-2171);
		gcall.Stepto(-37541,-19422,-2148);
		gcall.Stepto(-37341,-19438,-2155);
		gcall.Stepto(-37142,-19450,-2159);
		gcall.Stepto(-36942,-19460,-2157);
		gcall.Stepto(-36737,-19466,-2110);
		gcall.Stepto(-36486,-19476,-2015);
		gcall.Stepto(-36243,-19475,-1903);
		gcall.Stepto(-35995,-19472,-1780);
		gcall.Stepto(-35723,-19469,-1640);
		gcall.Stepto(-35498,-19467,-1538);
		gcall.Stepto(-35249,-19465,-1510);
		gcall.Stepto(-34998,-19462,-1493);
		gcall.Stepto(-34748,-19459,-1450);
		gcall.Stepto(-34505,-19448,-1419);
		gcall.Stepto(-34460,-19449,-1419);
		gcall.Stepto(-34456,-19523,-1419);
		gcall.Stepto(-34455,-19708,-1419);
		gcall.Stepto(-34445,-19956,-1419);
		gcall.Stepto(-34422,-20101,-1419);
		gcall.Stepto(-34249,-20102,-1419);
		gcall.Stepto(-34006,-20104,-1419);
		gcall.Stepto(-33757,-20106,-1419);
		gcall.Stepto(-33509,-20108,-1419);
		gcall.Stepto(-33262,-20109,-1419);
		Sleep(1000);
		break;
	case 2:
		lianji30_go();
		while (true)
		{
			if (flag30 == FALSE)
			{
				if (gcall.GetPlayerLevel() == 30)
				{
					gcall.AddTalent(0x15C);
					if (gcall.isTalentPanelShow())
					{
						gcall.OpenTalentUI();
						Sleep(1000);
					}
					flag30 = TRUE;
				}
			}
			
			if (gcall.GetPlayerLevel() < 33)
			{
				UseExperience();
				lianji30();
			}
			else
			{
				gcall.AddTalent(0x12B);
				gcall.AddTalent(0x12C);
				gcall.AddTalent(0x12D);
				if (gcall.isTalentPanelShow())
				{
					gcall.OpenTalentUI();
					Sleep(1000);
				}

				break;
			}
		}
		flag = gcall.Stepto(-39259,-18338,-2340,10,5,3000);
		if (flag)
		{
			Sleep(1000);
			gcall.Shunyi(L"Lianji30-end-mai");
			Sleep(1000);
			gcall.sendcall(id_msg_OverShunyi,(LPVOID)FALSE);
			Sleep(3000);
			gcall.Stepto(-32453,-20092,-1410);
		}
		gcall.WaitPlans();
		Sleep(1000);
		gcall.Stepto(-32112,-20110,-1480);
		Sleep(1000);
		gcall.Shunyi(L"Lianji30-mai");
		Sleep(1000);
		gcall.sendcall(id_msg_OverShunyi,(LPVOID)FALSE);
		Sleep(3000);
		gcall.Stepto(-23932,-24614,-679);
		Sleep(1000);
		gcall.FenJieByConfig();
		Sleep(1000);
		gcall.SellItemByConfig(L"한정가");
		Sleep(1000);
		gcall.SortBag();
		/*gcall.NewSpend(2.5);
		gcall.Stepto(-32022,-20102,-1480);
		gcall.Stepto(-31804,-20187,-1480);
		gcall.Stepto(-31573,-20277,-1480);
		gcall.Stepto(-31338,-20369,-1480);
		gcall.Stepto(-31110,-20458,-1480);
		gcall.Stepto(-30877,-20548,-1480);
		gcall.Stepto(-30646,-20639,-1480);
		gcall.Stepto(-30416,-20728,-1480);
		gcall.Stepto(-30186,-20818,-1478);
		gcall.Stepto(-29955,-20908,-1457);
		gcall.Stepto(-29723,-20999,-1445);
		gcall.Stepto(-29496,-21102,-1419);
		gcall.Stepto(-29291,-21244,-1384);
		gcall.Stepto(-29109,-21412,-1367);
		gcall.Stepto(-28955,-21605,-1295);
		gcall.Stepto(-28810,-21795,-1168);
		gcall.Stepto(-28661,-21997,-1054);
		gcall.Stepto(-28548,-22223,-1056);
		gcall.Stepto(-28486,-22462,-1057);
		gcall.Stepto(-28443,-22705,-1069);
		gcall.Stepto(-28405,-22955,-1079);
		gcall.Stepto(-28369,-23198,-1081);
		gcall.Stepto(-28332,-23446,-1081);
		gcall.Stepto(-28295,-23688,-1079);
		gcall.Stepto(-28209,-23917,-1076);
		gcall.Stepto(-28030,-24088,-1043);
		gcall.Stepto(-27833,-24221,-994);
		gcall.Stepto(-27614,-24363,-923);
		gcall.Stepto(-27403,-24489,-886);
		gcall.Stepto(-27185,-24608,-874);
		gcall.Stepto(-26965,-24725,-833);
		gcall.Stepto(-26745,-24842,-730);
		gcall.Stepto(-26529,-24957,-681);
		gcall.Stepto(-26295,-25036,-679);
		gcall.Stepto(-26048,-25067,-679);
		gcall.Stepto(-25801,-25092,-679);
		gcall.Stepto(-25560,-25114,-679);
		gcall.Stepto(-25304,-25126,-679);
		gcall.Stepto(-25067,-25061,-679);
		gcall.Stepto(-24841,-24958,-679);
		gcall.Stepto(-24620,-24851,-679);
		gcall.Stepto(-24393,-24742,-679);
		gcall.Stepto(-24258,-24680,-679);
		gcall.Stepto(-24200,-24686,-679);
		gcall.Stepto(-24097,-24697,-679);
		gcall.Stepto(-24055,-24701,-679);
		gcall.NewSpend(2.5);
		Sleep(1000);
		gcall.FixWuqi();
		Sleep(1000);
		gcall.SellItemByConfig(L"내하리");
		Sleep(1000);*/
		gcall.CityConvey(0x16);
		Sleep(3000);
		gcall.NewSpend(2.5);
		gcall.Stepto(3838,-19048,-1076);
		gcall.Stepto(3833,-18611,-1076);
		gcall.Stepto(3826,-18179,-1070);
		gcall.Stepto(3818,-17744,-1082);
		gcall.Stepto(3812,-17308,-1077);
		gcall.Stepto(3831,-16879,-1052);
		gcall.Stepto(3870,-16439,-1051);
		gcall.Stepto(3912,-16016,-870);
		gcall.Stepto(3956,-15570,-828);
		gcall.Stepto(3966,-15470,-828);
		gcall.Stepto(3875,-15461,-828);
		gcall.Stepto(3629,-15436,-828);
		gcall.Stepto(3397,-15343,-828);
		gcall.Stepto(3204,-15187,-828);
		gcall.Stepto(3039,-15004,-828);
		gcall.Stepto(2915,-14791,-828);
		gcall.Stepto(2837,-14556,-819);
		gcall.Stepto(2811,-14309,-690);
		gcall.Stepto(2842,-14065,-576);
		gcall.Stepto(2950,-13847,-521);
		gcall.Stepto(3091,-13640,-396);
		gcall.Stepto(3243,-13443,-286);
		gcall.Stepto(3448,-13301,-285);
		gcall.Stepto(3684,-13223,-285);
		gcall.Stepto(3918,-13156,-285);
		gcall.Stepto(4162,-13163,-285);
		gcall.Stepto(4177,-13166,-285);
		gcall.Stepto(4177,-13079,-285);
		gcall.Stepto(4184,-12833,-286);
		gcall.Stepto(4187,-12741,-286);
		gcall.Stepto(4190,-12663,-286);
		gcall.Stepto(4177,-12553,-286);
		gcall.Stepto(4153,-12421,-286);
		gcall.Stepto(4106,-12209,-286);
		gcall.Stepto(4012,-12209,-286);
		gcall.Stepto(3813,-12216,-268);
		gcall.NewSpend(1);
		gcall.Stepto(3565,-12207,-272);
		gcall.Stepto(3547,-12215,-272);
		Sleep(2000);
		gcall.PickupTask();
		Sleep(2000);
		gcall.Stepto(3365,-12191,-272);
		gcall.Stepto(3288,-12177,-272);
		gcall.Stepto(3125,-12143,-272);
		gcall.Stepto(3090,-11966,-272);
		gcall.Stepto(3065,-11828,-272);
		gcall.Stepto(3030,-11616,-272);
		Sleep(1000);
		gcall.DeliverQuests(zid,taskid,L"진소아");
		Sleep(1000);
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

void TaskScript::Task_521(int zid,int taskid)
{
	switch (taskid)
	{
	case 1:
		gcall.Stepto(3052,-11999,-272);
		gcall.Stepto(3055,-11747,-272);
		gcall.Stepto(3062,-11653,-272);
		Sleep(1000);
		gcall.PickupTask();
		Sleep(1000);
		break;
	case 2:
		gcall.GoodsQuests(zid,taskid,L"술값 계산서");
		Sleep(2000);
		break;
	case 3:
		gcall.NewSpend(2.5);
		gcall.Stepto(3547,-12206,-272);
		gcall.Stepto(3693,-12211,-272);
		gcall.Stepto(3835,-12216,-268);
		gcall.Stepto(3936,-12248,-286);
		gcall.Stepto(4058,-12356,-286);
		gcall.Stepto(4172,-12565,-286);
		gcall.Stepto(4189,-12733,-286);
		gcall.Stepto(4185,-12836,-286);
		gcall.Stepto(4176,-13065,-285);
		gcall.Stepto(4175,-13110,-285);
		gcall.Stepto(4360,-13187,-285);
		gcall.Stepto(4577,-13298,-285);
		gcall.Stepto(4784,-13429,-285);
		gcall.Stepto(4970,-13596,-285);
		gcall.Stepto(5097,-13807,-285);
		gcall.Stepto(5208,-14033,-285);
		gcall.Stepto(5258,-14269,-285);
		gcall.NewSpend(1);
		gcall.Stepto(5256,-14518,-285);
		gcall.Stepto(5212,-14763,-285);
		Sleep(5000);
		gcall.Stepto(5158,-14882,-285);
		gcall.WaitPlans();
		gcall.Stepto(5120,-14940,-285);
		gcall.Stepto(4960,-15141,-285);
		gcall.NewSpend(2.5);
		gcall.Stepto(4778,-15303,-280);
		gcall.Stepto(4565,-15424,-280);
		gcall.Stepto(4450,-15434,-276);
		gcall.Stepto(4195,-15428,-276);
		gcall.Stepto(4037,-15427,-276);
		gcall.Stepto(4006,-15573,-276);
		gcall.NewSpend(1);
		gcall.Stepto(3948,-15809,-276);
		gcall.Stepto(3927,-15900,-276);
		
		Sleep(1000);
		gcall.DeliverQuests(zid,taskid,L"예하랑");
		Sleep(1000);
		break;
	case 4:
		gcall.NewSpend(2.5);
		gcall.Stepto(3961,-15783,-276);
		gcall.Stepto(3986,-15695,-276);
		gcall.Stepto(4059,-15458,-276);
		gcall.Stepto(4188,-15433,-276);
		gcall.Stepto(4441,-15440,-276);
		gcall.Stepto(4676,-15390,-280);
		gcall.Stepto(4893,-15268,-285);
		gcall.Stepto(4995,-15196,-285);
		gcall.Stepto(5061,-15079,-285);
		gcall.Stepto(5162,-14853,-285);
		gcall.Stepto(5175,-14816,-285);
		gcall.Stepto(5217,-14684,-285);
		gcall.Stepto(5218,-14674,-285);
		gcall.Stepto(5238,-14425,-285);
		gcall.Stepto(5234,-14181,-285);
		gcall.Stepto(5176,-13949,-285);
		gcall.Stepto(5045,-13729,-285);
		gcall.Stepto(4906,-13527,-285);
		gcall.Stepto(4712,-13367,-285);
		gcall.Stepto(4496,-13242,-285);
		gcall.Stepto(4271,-13169,-285);
		gcall.Stepto(4147,-13135,-285);
		gcall.Stepto(4160,-12971,-286);
		gcall.Stepto(4182,-12740,-286);
		gcall.Stepto(4182,-12738,-286);
		gcall.Stepto(4206,-12497,-286);
		gcall.Stepto(4224,-12312,-286);
		gcall.Stepto(4235,-12307,-286);
		gcall.Stepto(4478,-12260,-286);
		gcall.Stepto(4703,-12302,-273);
		gcall.NewSpend(1);
		gcall.Stepto(4927,-12328,-272);
		gcall.Stepto(4927,-12329,-272);
		Sleep(2000);
		gcall.PickupTask();
		Sleep(2000);
		gcall.Stepto(5048,-12342,-272);
		gcall.Stepto(5107,-12347,-272);
		gcall.Stepto(5356,-12356,-272);
		gcall.Stepto(5607,-12372,-272);
		gcall.Stepto(5695,-12381,-272);
		Sleep(1000);
		gcall.DeliverQuests(zid,taskid,L"소연화");
		Sleep(1000);
		break;
	case 5:
		gcall.Stepto(5666,-12248,-272);
		Sleep(1000);
		gcall.DeliverQuests(zid,taskid,L"길동");
		Sleep(1000);
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

void TaskScript::Task_522(int zid,int taskid)
{
	switch (taskid)
	{
	case 1:
		gcall.NewSpend(2.5);
		gcall.Stepto(5463,-12340,-272);
		gcall.Stepto(5395,-12347,-272);
		gcall.Stepto(5151,-12372,-272);
		gcall.Stepto(5036,-12366,-272);
		gcall.Stepto(4792,-12346,-272);
		gcall.Stepto(4541,-12319,-286);
		gcall.Stepto(4330,-12303,-286);
		gcall.Stepto(4326,-12310,-286);
		gcall.Stepto(4242,-12539,-286);
		gcall.Stepto(4199,-12784,-286);
		gcall.Stepto(4195,-12832,-286);
		gcall.Stepto(4161,-13077,-285);
		gcall.Stepto(4132,-13181,-285);
		gcall.Stepto(3895,-13188,-285);
		gcall.Stepto(3666,-13267,-285);
		gcall.Stepto(3437,-13365,-285);
		gcall.Stepto(3231,-13506,-297);
		gcall.Stepto(3102,-13721,-424);
		gcall.Stepto(2985,-13935,-542);
		gcall.Stepto(2972,-14164,-612);
		gcall.Stepto(2936,-14398,-737);
		gcall.Stepto(2900,-14632,-828);
		gcall.Stepto(3000,-14840,-828);
		gcall.Stepto(3100,-15072,-828);
		gcall.Stepto(3265,-15248,-828);
		gcall.Stepto(3459,-15403,-828);
		gcall.Stepto(3679,-15527,-828);
		gcall.Stepto(3895,-15651,-826);
		gcall.Stepto(3940,-15734,-822);
		gcall.Stepto(3909,-16166,-936);
		gcall.Stepto(3890,-16604,-1051);
		gcall.Stepto(3879,-17043,-1056);
		gcall.Stepto(3869,-17459,-1083);
		gcall.Stepto(3858,-17885,-1079);
		gcall.Stepto(3848,-18315,-1065);
		gcall.Stepto(3836,-18781,-1076);
		gcall.Stepto(3830,-19207,-1075);
		gcall.NewSpend(1);
		gcall.Stepto(3826,-19649,-1062);
		gcall.Stepto(3828,-19900,-1062);
		Sleep(2000);
		gcall.Stepto(3764,-20478,-1101);
		gcall.WaitPlans();
		gcall.NewSpend(2.5);
		gcall.Stepto(3850,-20274,-1065,10,10,3000);
		gcall.Stepto(3903,-20312,-1071);
		gcall.Stepto(4088,-20477,-1097);
		gcall.Stepto(4276,-20638,-1110);
		gcall.Stepto(4511,-20700,-1101);
		gcall.Stepto(4757,-20667,-1090);
		gcall.Stepto(5003,-20631,-1090);
		gcall.Stepto(5248,-20594,-1072);
		gcall.Stepto(5494,-20557,-1071);
		gcall.Stepto(5740,-20523,-1079);
		gcall.Stepto(5986,-20514,-1096);
		gcall.Stepto(6206,-20625,-1203);
		gcall.Stepto(6419,-20753,-1318);
		gcall.Stepto(6633,-20879,-1417);
		gcall.Stepto(6857,-20988,-1483);
		gcall.Stepto(7100,-21014,-1517);
		gcall.Stepto(7327,-20918,-1535);
		gcall.Stepto(7520,-20763,-1527);
		gcall.Stepto(7693,-20586,-1505);
		gcall.Stepto(7848,-20395,-1474);
		gcall.Stepto(7987,-20192,-1442);
		gcall.Stepto(8085,-19990,-1418);
		gcall.Stepto(8189,-19733,-1412);
		gcall.Stepto(8283,-19503,-1444);
		gcall.Stepto(8377,-19273,-1501);
		gcall.Stepto(8470,-19043,-1563);
		gcall.Stepto(8564,-18813,-1599);
		gcall.Stepto(8668,-18589,-1628);
		gcall.Stepto(8829,-18400,-1648);
		gcall.Stepto(8996,-18217,-1628);
		gcall.Stepto(9163,-18033,-1614);
		gcall.Stepto(9328,-17848,-1634);
		gcall.Stepto(9461,-17639,-1673);
		gcall.Stepto(9527,-17400,-1692);
		gcall.Stepto(9539,-17166,-1704);
		gcall.Stepto(9529,-16926,-1709);
		gcall.Stepto(9513,-16669,-1708);
		gcall.Stepto(9492,-16422,-1701);
		gcall.Stepto(9471,-16176,-1692);
		gcall.Stepto(9447,-15925,-1675);
		gcall.Stepto(9422,-15678,-1636);
		gcall.Stepto(9399,-15431,-1570);
		gcall.Stepto(9376,-15184,-1513);
		gcall.Stepto(9354,-14935,-1490);
		gcall.Stepto(9352,-14687,-1489);
		gcall.Stepto(9352,-14439,-1474);
		gcall.Stepto(9352,-14191,-1459);
		gcall.Stepto(9354,-13943,-1453);
		gcall.Stepto(9360,-13695,-1451);
		gcall.Stepto(9364,-13446,-1453);
		gcall.Stepto(9365,-13209,-1460);
		gcall.Stepto(9365,-12947,-1471);
		gcall.Stepto(9366,-12698,-1489);
		gcall.Stepto(9367,-12493,-1509);
		gcall.Stepto(9339,-12509,-1509);
		gcall.NewSpend(1);
		gcall.Stepto(9127,-12635,-1508);
		gcall.Stepto(9093,-12656,-1509);
		Sleep(1000);
		gcall.LinQuJiangLi();
		Sleep(1000);
		if (gcall.GetPlayerXianlu() > 3)
		{
			gcall.randXianlu(3);
		}
		Sleep(1000);
		gcall.Yaojiang(L"귀염집게의 정수",L"전갈보패");
		Sleep(1000);
		gcall.FenJieByConfig();
		Sleep(1000);
		gcall.FenJieByConfig();
		Sleep(1000);
		gcall.XieBaoShi(1);
		Sleep(1000);
		gcall.JiaBaoShi(1,L"빛나는 오각 금강석");//加白5角宝石
		Sleep(1000);
		gcall.JiaBaoShi(2,L"빛나는 사각 홍옥");//加红4角宝石
		Sleep(1000);
		gcall.SortBag();
		Sleep(1000);
		gcall.NewSpend(2.5);
		gcall.Stepto(9199,-12614,-1506);
		gcall.Stepto(9211,-12644,-1502);
		gcall.Stepto(9305,-12872,-1478);
		gcall.Stepto(9400,-13105,-1463);
		gcall.Stepto(9453,-13234,-1459);
		gcall.Stepto(9461,-13282,-1458);
		gcall.Stepto(9520,-13524,-1457);
		gcall.Stepto(9578,-13766,-1462);
		gcall.Stepto(9630,-14010,-1474);
		gcall.Stepto(9682,-14253,-1493);
		gcall.Stepto(9734,-14495,-1514);
		gcall.Stepto(9778,-14739,-1528);
		gcall.Stepto(9822,-14983,-1543);
		gcall.Stepto(9865,-15229,-1583);
		gcall.Stepto(9908,-15470,-1640);
		gcall.Stepto(9951,-15714,-1690);
		gcall.Stepto(9994,-15960,-1717);
		gcall.Stepto(10037,-16201,-1720);
		gcall.Stepto(10027,-16248,-1720);
		gcall.Stepto(9968,-16485,-1717);
		gcall.Stepto(9908,-16726,-1717);
		gcall.Stepto(9848,-16967,-1716);
		gcall.Stepto(9788,-17207,-1709);
		gcall.Stepto(9727,-17449,-1698);
		gcall.Stepto(9667,-17692,-1681);
		gcall.Stepto(9607,-17933,-1649);
		gcall.Stepto(9533,-18166,-1605);
		gcall.Stepto(9427,-18391,-1600);
		gcall.Stepto(9305,-18607,-1607);
		gcall.Stepto(9180,-18825,-1607);
		gcall.Stepto(9058,-19038,-1597);
		gcall.Stepto(8936,-19249,-1566);
		gcall.Stepto(8809,-19470,-1502);
		gcall.Stepto(8758,-19559,-1479);
		gcall.Stepto(8687,-19660,-1453);
		gcall.Stepto(8545,-19864,-1416);
		gcall.Stepto(8403,-20068,-1406);
		gcall.Stepto(8260,-20274,-1417);
		gcall.Stepto(8119,-20475,-1438);
		gcall.Stepto(7976,-20680,-1465);
		gcall.Stepto(7835,-20883,-1491);
		gcall.Stepto(7681,-21076,-1513);
		gcall.Stepto(7486,-21232,-1531);
		gcall.Stepto(7281,-21373,-1509);
		gcall.Stepto(7077,-21510,-1477);
		gcall.Stepto(6871,-21647,-1448);
		gcall.Stepto(6664,-21785,-1432);
		gcall.Stepto(6455,-21925,-1435);
		gcall.Stepto(6250,-22061,-1447);
		gcall.Stepto(6042,-22200,-1452);
		gcall.Stepto(5836,-22337,-1450);
		gcall.Stepto(5628,-22476,-1443);
		gcall.Stepto(5421,-22614,-1431);
		gcall.Stepto(5196,-22712,-1418);
		gcall.Stepto(4956,-22773,-1400);
		gcall.Stepto(4713,-22833,-1366);
		gcall.Stepto(4473,-22888,-1328);
		gcall.Stepto(4222,-22908,-1316);
		gcall.Stepto(3974,-22891,-1305);
		gcall.Stepto(3937,-22877,-1304);
		gcall.Stepto(3886,-22632,-1285);
		gcall.Stepto(3853,-22390,-1264);
		gcall.Stepto(3831,-22138,-1242);
		gcall.Stepto(3813,-21889,-1222);
		gcall.Stepto(3796,-21642,-1203);
		gcall.Stepto(3778,-21393,-1182);
		gcall.Stepto(3760,-21144,-1163);
		gcall.Stepto(3753,-21011,-1152);
		gcall.Stepto(2537,-20528,-1112);
		gcall.Stepto(2100,-20550,-1138,10,10,3000);
		gcall.Stepto(1674,-20578,-1193,10,10,3000);
		gcall.Stepto(1246,-20610,-1325,10,10,3000);
		gcall.Stepto(807,-20651,-1373,10,10,3000);
		gcall.Stepto(374,-20681,-1345,10,10,3000);
		gcall.Stepto(-54,-20686,-1320,10,10,3000);
		gcall.Stepto(-491,-20727,-1303,10,10,3000);
		gcall.Stepto(-917,-20768,-1293,10,10,3000);
		gcall.Stepto(-1361,-20791,-1287,10,10,3000);
		gcall.Stepto(-1629,-20747,-1282,10,10,3000);
		gcall.Stepto(-1864,-20674,-1278);
		gcall.Stepto(-2104,-20600,-1274);
		gcall.Stepto(-2342,-20523,-1272);
		gcall.Stepto(-2575,-20439,-1272);
		gcall.Stepto(-2809,-20353,-1269);
		gcall.Stepto(-3041,-20269,-1260);
		gcall.Stepto(-3274,-20179,-1243);
		gcall.Stepto(-3504,-20089,-1218);
		gcall.Stepto(-3736,-19998,-1189);
		gcall.Stepto(-3959,-19911,-1158);
		gcall.Stepto(-4141,-19840,-1131);
		gcall.Stepto(-4327,-19766,-1103);
		gcall.Stepto(-4508,-19691,-1078);
		gcall.Stepto(-4693,-19612,-1057);
		gcall.Stepto(-4886,-19529,-1042);
		gcall.Stepto(-5115,-19430,-1035);
		gcall.Stepto(-5288,-19355,-1037);
		gcall.Stepto(-5668,-19191,-1061);
		gcall.Stepto(-6055,-19024,-1107);
		gcall.Stepto(-6477,-18841,-1165);
		gcall.Stepto(-6867,-18673,-1217);
		gcall.Stepto(-7275,-18496,-1260);
		gcall.Stepto(-7675,-18325,-1282);
		gcall.Stepto(-8068,-18157,-1275);
		gcall.Stepto(-8468,-17987,-1257);
		gcall.Stepto(-8823,-17791,-1239);
		gcall.Stepto(-8989,-17604,-1228);
		gcall.Stepto(-9142,-17408,-1216);
		gcall.Stepto(-9294,-17214,-1202);
		gcall.Stepto(-9445,-17020,-1183);
		gcall.Stepto(-9599,-16823,-1159);
		gcall.Stepto(-9748,-16622,-1129);
		gcall.Stepto(-9869,-16410,-1107);
		gcall.Stepto(-9990,-16192,-1092);
		gcall.Stepto(-10111,-15974,-1085);
		gcall.Stepto(-10231,-15754,-1082);
		gcall.Stepto(-10350,-15538,-1082);
		gcall.Stepto(-10467,-15322,-1085);
		gcall.Stepto(-10583,-15097,-1095);
		gcall.Stepto(-10694,-14875,-1115);
		gcall.Stepto(-10763,-14640,-1153);
		gcall.Stepto(-10827,-14398,-1211);
		gcall.Stepto(-10891,-14159,-1286);
		gcall.Stepto(-10954,-13919,-1356);
		gcall.Stepto(-11008,-13678,-1406);
		gcall.Stepto(-11063,-13432,-1489);
		gcall.Stepto(-11121,-13194,-1603);
		gcall.Stepto(-11189,-12951,-1740);
		gcall.Stepto(-11262,-12714,-1861);
		gcall.Stepto(-11337,-12479,-1896);
		gcall.Stepto(-11412,-12244,-1899);
		gcall.Stepto(-11493,-12008,-1900);
		gcall.Stepto(-11614,-11788,-1893);
		gcall.Stepto(-11749,-11578,-1861);
		gcall.Stepto(-11886,-11372,-1825);
		gcall.Stepto(-11978,-11237,-1826);
		gcall.Stepto(-12223,-10875,-1856);
		gcall.Stepto(-12466,-10516,-1873);
		gcall.Stepto(-12707,-10159,-1877);
		gcall.Stepto(-12951,-9799,-1877);
		gcall.Stepto(-13200,-9431,-1876);
		gcall.Stepto(-13442,-9077,-1855);
		gcall.Stepto(-13689,-8716,-1846);
		gcall.Stepto(-13926,-8349,-1874);
		gcall.Stepto(-14133,-7968,-1885);
		gcall.Stepto(-14263,-7549,-1876);
		gcall.Stepto(-14354,-7126,-1873);
		gcall.Stepto(-14419,-6734,-1866);
		gcall.Stepto(-14445,-6488,-1853);
		gcall.Stepto(-14454,-6237,-1842);
		gcall.Stepto(-14463,-5991,-1839);
		gcall.Stepto(-14474,-5742,-1841);
		gcall.Stepto(-14486,-5494,-1842);
		gcall.Stepto(-14497,-5248,-1848);
		gcall.Stepto(-14507,-4998,-1839);
		gcall.Stepto(-14514,-4746,-1825);
		gcall.Stepto(-14521,-4502,-1793);
		gcall.Stepto(-14527,-4303,-1754);
		gcall.Stepto(-14536,-3893,-1701);
		gcall.Stepto(-14538,-3450,-1675);
		gcall.Stepto(-14539,-3023,-1611);
		gcall.Stepto(-14539,-2584,-1510);
		gcall.Stepto(-14529,-2146,-1484);
		gcall.Stepto(-14529,-2130,-1482);
		gcall.Stepto(-14558,-1964,-1467);
		gcall.Stepto(-14565,-1928,-1463);
		gcall.Stepto(-14605,-1503,-1413);
		gcall.Stepto(-14557,-1069,-1328);
		gcall.Stepto(-14415,-807,-1255);
		gcall.WaitPlans();
		gcall.Stepto(-14207,-716,-1209);
		gcall.Stepto(-13961,-691,-1171);
		gcall.Stepto(-13714,-708,-1149);
		gcall.Stepto(-13464,-736,-1146);
		gcall.Stepto(-13222,-738,-1143);
		gcall.Stepto(-12990,-658,-1160);
		gcall.Stepto(-12834,-473,-1158);
		gcall.Stepto(-12746,-238,-1139);
		gcall.Stepto(-12695,7,-1125);
		gcall.Stepto(-12673,251,-1121);
		gcall.Stepto(-12665,504,-1107);
		gcall.Stepto(-12666,751,-1088);
		gcall.Stepto(-12676,998,-1057);
		gcall.Stepto(-12709,1242,-1017);
		gcall.Stepto(-12763,1483,-1002);
		gcall.Stepto(-12846,1716,-975);
		gcall.Stepto(-12977,1930,-943);
		gcall.Stepto(-13063,2053,-903);
		gcall.Stepto(-13165,2141,-871);
		gcall.Stepto(-13370,2327,-846);
		gcall.Stepto(-13593,2433,-824);
		gcall.Stepto(-13840,2491,-794);
		gcall.Stepto(-14079,2444,-800);
		gcall.Stepto(-14308,2357,-784);
		gcall.Stepto(-14542,2263,-770);
		gcall.Stepto(-14772,2171,-748);
		gcall.Stepto(-15005,2089,-718);
		gcall.Stepto(-15245,2060,-685);
		gcall.Stepto(-15402,2188,-659);
		gcall.NewSpend(1);
		gcall.Stepto(-15673,2454,-585);
		gcall.Stepto(-15717,2710,-536);
		gcall.Stepto(-15785,3148,-419);
		gcall.Stepto(-15838,3488,-340);
		gcall.Stepto(-15846,3645,-321);
		Sleep(2000);
		gcall.Stepto(-15848,3640,-324);
		gcall.WaitPlans();
		gcall.Stepto(-15857,3888,-286);
		gcall.Stepto(-15855,3926,-286);
		gcall.NewSpend(2.5);
		gcall.Stepto(-15811,4341,-372);
		gcall.Stepto(-15762,4774,-394);
		gcall.Stepto(-15712,5205,-386);
		gcall.Stepto(-15659,5638,-364);
		gcall.Stepto(-15604,6070,-348);
		gcall.Stepto(-15573,6494,-309);
		gcall.Stepto(-15653,6931,-272);
		gcall.Stepto(-15768,7348,-272);
		gcall.Stepto(-15896,7765,-267);
		gcall.Stepto(-15948,7906,-264);
		gcall.Stepto(-16062,8136,-258);
		gcall.Stepto(-16165,8308,-243);
		gcall.Stepto(-16309,8510,-213);
		gcall.Stepto(-16448,8658,-181);
		gcall.Stepto(-16620,8838,-150);
		gcall.Stepto(-16745,9037,-124);
		gcall.Stepto(-16835,9279,-107);
		gcall.Stepto(-16868,9522,-94);
		gcall.Stepto(-16883,9769,-87);
		gcall.NewSpend(1);
		gcall.Stepto(-16920,10011,-85);
		gcall.Stepto(-16941,10061,-87);
		Sleep(1000);
		gcall.DeliverQuests(zid,taskid,L"춘삼");
		Sleep(1000);
		break;
	case 2:
		//过滤怪物( 땅땅이;물물이;불불이;
		gcall.NewSpend(2.5);
		gcall.Stepto(-17103,10001,-86);
		gcall.Stepto(-17150,9955,-88);
		gcall.Stepto(-17330,9765,-108);
		gcall.Stepto(-17514,9602,-139);
		gcall.Stepto(-17641,9564,-156);
		gcall.Stepto(-18069,9543,-224);
		gcall.Stepto(-18500,9551,-277);
		gcall.Stepto(-18910,9674,-304);
		gcall.Stepto(-19278,9907,-346);
		gcall.Stepto(-19315,10195,-344);
		gcall.Stepto(-19399,10617,-287);
		gcall.Stepto(-19495,11034,-256);
		gcall.Stepto(-19531,11466,-212);
		gcall.Stepto(-19379,11852,-193);
		gcall.Stepto(-19102,12203,-176);
		gcall.Stepto(-18758,12455,-142);
		gcall.Stepto(-18364,12660,-81);
		gcall.Stepto(-18008,12776,-19);
		gcall.Stepto(-17844,12732,27);
		gcall.Stepto(-17613,12823,86);
		gcall.Stepto(-17421,12973,138);
		gcall.Stepto(-17226,13133,193);
		gcall.Stepto(-17037,13286,253);
		gcall.Stepto(-16843,13443,320);
		gcall.Stepto(-16659,13608,387);
		gcall.Stepto(-16507,13807,446);
		gcall.Stepto(-16409,14029,499);
		gcall.Stepto(-16371,14276,552);
		gcall.Stepto(-16373,14522,601);
		gcall.Stepto(-16431,14765,650);
		gcall.Stepto(-16507,15002,707);
		gcall.Stepto(-16596,15232,775);
		gcall.Stepto(-16695,15462,870);
		gcall.Stepto(-16782,15695,971);
		gcall.Stepto(-16783,15939,1092);
		gcall.Stepto(-16618,16108,1230);
		gcall.Stepto(-16382,16150,1330);
		gcall.Stepto(-16137,16103,1403);
		gcall.Stepto(-15894,16035,1470);
		gcall.Stepto(-15668,15933,1511);
		gcall.Stepto(-15449,15816,1541);
		gcall.Stepto(-15240,15690,1568);
		gcall.Stepto(-15035,15553,1589);
		gcall.Stepto(-14833,15398,1604);
		gcall.Stepto(-14639,15245,1626);
		gcall.Stepto(-14454,15085,1658);
		gcall.Stepto(-14305,14885,1680);
		gcall.Stepto(-14214,14759,1690);
		gcall.Stepto(-14167,14689,1695);
		gcall.Stepto(-14020,14492,1717);
		gcall.Stepto(-13872,14294,1765);
		gcall.NewSpend(1);
		gcall.Stepto(-13692,14122,1768);
		gcall.Stepto(-13477,13995,1868);
		gcall.Stepto(-13248,13900,1879);
		gcall.Stepto(-13017,13812,1877);
		Sleep(6000);
		gcall.Stepto(-12911,13782,1867);
		gcall.WaitPlans();
		gcall.Stepto(-12905,13806,1867);
		gcall.Stepto(-12751,13768,1864);
		gcall.NewSpend(2.5);
		gcall.Stepto(-12515,13699,1791);
		gcall.Stepto(-12272,13620,1664);
		gcall.Stepto(-12041,13549,1540);
		gcall.Stepto(-11800,13473,1415);
		gcall.Stepto(-11565,13396,1294);
		gcall.Stepto(-11330,13318,1221);
		gcall.Stepto(-11191,13272,1217);
		gcall.Stepto(-11169,13265,1217);
		gcall.Stepto(-10933,13186,1216);
		gcall.Stepto(-10699,13109,1217);
		gcall.Stepto(-10467,13032,1217);
		gcall.Stepto(-10223,12958,1217);
		gcall.Stepto(-10025,12894,1217);
		gcall.NewSpend(1);
		gcall.Stepto(-10024,12898,1217);
		gcall.Stepto(-9993,13055,1217);
		
		gcall.FindThenKill(0,500,modeAoe | modeNormal | modePickup );
		gcall.Stepto(-9814,12688,1217);
		gcall.FindThenKill(0,500,modeAoe | modeNormal | modePickup );
		gcall.Stepto(-9992,12543,1218);
		gcall.Stepto(-10174,12377,1219);
		gcall.Stepto(-10196,12356,1219);
		gcall.FindThenKill(0,500,modeAoe | modeNormal | modePickup );
		gcall.Stepto(-9902,12444,1219);
		gcall.Stepto(-9405,12609,1233);
		gcall.FindThenKill(0,500,modeAoe | modeNormal | modePickup );
		gcall.Stepto(-9433,12888,1217);
		gcall.Stepto(-9395,13216,1217);
		gcall.Stepto(-9052,13506,1217);
		gcall.FindThenKill(0,500,modeAoe | modeNormal | modePickup );
		gcall.Stepto(-9052,13506,1217);
		Sleep(1000);
		gcall.PickupTask();
		Sleep(1000);
		gcall.Stepto(-8942,13399,1217);
		gcall.Stepto(-8749,13180,1217);
		gcall.Stepto(-8501,12939,1221);
		gcall.FindThenKill(0,300,modeAoe | modeNormal | modePickup );
		Sleep(1000);
		gcall.Stepto(-8501,12939,1221);
		Sleep(1000);
		gcall.PickupTask();
		Sleep(1000);
		gcall.Stepto(-8519,12587,1221);
		gcall.Stepto(-8603,12248,1217);
		gcall.Stepto(-8683,11874,1217);
		gcall.Stepto(-8737,11618,1217);
		gcall.FindThenKill(0,300,modeAoe | modeNormal | modePickup );
		Sleep(1000);
		gcall.Stepto(-8711 ,11590,1218);
		Sleep(1000);
		gcall.PickupTask();
		Sleep(1000);
		gcall.Stepto(-8902,11822,1217);
		gcall.Stepto(-9355,11753,1217);
		gcall.FindThenKill(0,300,modeAoe | modeNormal | modePickup );
		Sleep(1000);
		gcall.Stepto(-9578,12013,1217);
		gcall.Stepto(-9737,12242,1217);
		gcall.Stepto(-9773,12517,1218);
		gcall.Stepto(-9501,12513,1224);
		gcall.Stepto(-9223,12540,1233);
		Sleep(10000);
		gcall.PickupTask();
		Sleep(1000);
		gcall.PickupTask();
		Sleep(1000);
		gcall.PickupTask();
		Sleep(1000);
		break;
	case 3:
		gcall.NewSpend(2.5);
		Sleep(1000);
		gcall.Stepto(-9525,12674,1217);
		gcall.Stepto(-9586,12700,1217);
		gcall.Stepto(-9997,12848,1217);
		gcall.Stepto(-10217,12924,1217);
		gcall.Stepto(-10624,13065,1217);
		gcall.Stepto(-11030,13207,1217);
		gcall.Stepto(-11199,13266,1218);
		gcall.Stepto(-11418,13351,1223);
		gcall.Stepto(-11642,13428,1335);
		gcall.NewSpend(1);
		gcall.Stepto(-11878,13487,1452);
		gcall.Stepto(-12110,13551,1571);
		gcall.Stepto(-12345,13633,1701);
		gcall.Stepto(-12579,13714,1823);
		gcall.Stepto(-12823,13770,1865);
		gcall.Stepto(-12874,13780,1866);
		Sleep(4000);
		gcall.Stepto(-12974,13809,1876);
		gcall.WaitPlans();
		gcall.Stepto(-13080,13843,1878);
		gcall.NewSpend(2.5);
		gcall.Stepto(-13314,13929,1879);
		gcall.Stepto(-13537,14032,1839);
		gcall.Stepto(-13726,14193,1768);
		gcall.Stepto(-13898,14380,1753);
		gcall.Stepto(-14069,14559,1706);
		gcall.Stepto(-14358,14878,1675);
		gcall.Stepto(-14651,15201,1631);
		gcall.Stepto(-14958,15503,1595);
		gcall.Stepto(-15134,15622,1580);
		gcall.Stepto(-15486,15684,1544);
		gcall.Stepto(-15764,15682,1487);
		gcall.Stepto(-16014,15635,1380);
		gcall.Stepto(-16259,15591,1234);
		gcall.Stepto(-16435,15428,969);
		gcall.Stepto(-16441,15185,782);
		gcall.Stepto(-16440,14931,690);
		gcall.Stepto(-16465,14687,634);
		gcall.Stepto(-16466,14682,633);
		gcall.Stepto(-16492,14485,595);
		gcall.Stepto(-16538,14240,522);
		gcall.Stepto(-16599,14013,464);
		gcall.Stepto(-16694,13774,403);
		gcall.Stepto(-16871,13596,331);
		gcall.Stepto(-17068,13445,254);
		gcall.Stepto(-17080,13436,250);
		gcall.Stepto(-17257,13269,186);
		gcall.Stepto(-17603,12992,81);
		gcall.Stepto(-17950,12749,-2);
		gcall.Stepto(-18309,12499,-53);
		gcall.Stepto(-18672,12250,-121);
		gcall.Stepto(-19017,12017,-150);
		gcall.Stepto(-19373,11733,-195);
		gcall.Stepto(-19622,11404,-211);
		gcall.Stepto(-19708,10987,-251);
		gcall.Stepto(-19631,10561,-308);
		gcall.Stepto(-19470,10147,-354);
		gcall.Stepto(-19154,9844,-338);
		gcall.Stepto(-18879,9698,-298);
		gcall.Stepto(-18637,9632,-279);
		gcall.Stepto(-18396,9579,-264);
		gcall.Stepto(-18152,9524,-235);
		gcall.Stepto(-17908,9486,-196);
		gcall.Stepto(-17657,9466,-156);
		gcall.Stepto(-17412,9453,-135);
		gcall.Stepto(-17161,9439,-116);
		gcall.Stepto(-16911,9437,-100);
		gcall.Stepto(-16677,9498,-89);
		gcall.Stepto(-16647,9516,-88);
		gcall.Stepto(-16706,9695,-85);
		gcall.NewSpend(1);
		gcall.Stepto(-16760,9935,-85);
		gcall.Stepto(-16787,10060,-82);
		Sleep(1000);
		gcall.DeliverQuests(zid,taskid,L"춘삼");
		Sleep(1000);
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


void TaskScript::Task_523(int zid,int taskid)
{
	switch (taskid)
	{
	case 1:
		gcall.NewSpend(2.5);
		gcall.Stepto(-16975,9340,-108);
		gcall.Stepto(-17165,9357,-117);
		gcall.Stepto(-17451,9384,-144);
		gcall.Stepto(-17694,9414,-157);
		gcall.Stepto(-17939,9451,-200);
		gcall.Stepto(-18104,9488,-231);
		gcall.Stepto(-18280,9471,-250);
		gcall.Stepto(-18712,9490,-291);
		gcall.Stepto(-19136,9616,-325);
		gcall.Stepto(-19530,9781,-333);
		gcall.Stepto(-19934,9959,-386);
		gcall.Stepto(-20324,10127,-443);
		gcall.Stepto(-20706,10341,-503);
		gcall.Stepto(-20961,10683,-521);
		gcall.Stepto(-21218,11044,-544);
		gcall.Stepto(-21569,11284,-579);
		gcall.Stepto(-21984,11400,-602);
		gcall.Stepto(-22422,11413,-629);
		gcall.Stepto(-22784,11417,-650);
		gcall.Stepto(-23020,11394,-649);
		gcall.Stepto(-23214,11456,-624);
		gcall.Stepto(-23412,11609,-577);
		gcall.Stepto(-23612,11760,-534);
		gcall.Stepto(-23815,11908,-502);
		gcall.Stepto(-24006,12062,-457);
		gcall.Stepto(-24080,12118,-444);
		gcall.Stepto(-24182,12269,-425);
		gcall.Stepto(-24290,12478,-405);
		gcall.Stepto(-24408,12736,-380);
		gcall.Stepto(-24587,13129,-338);
		gcall.Stepto(-24810,13502,-271);
		gcall.Stepto(-25081,13842,-214);
		gcall.Stepto(-25399,14138,-142);
		gcall.Stepto(-25619,14313,-66);
		gcall.Stepto(-25824,14463,-5);
		gcall.Stepto(-25938,14546,16);
		gcall.Stepto(-26156,14657,31);
		gcall.Stepto(-26323,14826,31);
		gcall.Stepto(-26508,15007,18);
		gcall.Stepto(-26703,15154,-4);
		gcall.Stepto(-26908,15293,-36);
		gcall.Stepto(-27117,15429,-54);
		gcall.Stepto(-27342,15516,-70);
		gcall.Stepto(-27590,15595,-87);
		gcall.Stepto(-27833,15642,-82);
		gcall.Stepto(-28076,15679,-68);
		gcall.Stepto(-28323,15701,-53);
		gcall.Stepto(-28564,15706,-19);
		gcall.Stepto(-28761,15709,5);
		gcall.Stepto(-28961,15711,31);
		gcall.Stepto(-29161,15710,54);
		gcall.Stepto(-29358,15708,69);
		gcall.Stepto(-29569,15704,75);
		gcall.Stepto(-29815,15698,85);
		gcall.Stepto(-30066,15692,95);
		gcall.Stepto(-30315,15684,99);
		gcall.Stepto(-30548,15677,111);
		gcall.Stepto(-30805,15679,112);
		gcall.NewSpend(1);
		gcall.Stepto(-31059,15692,106);
		gcall.Stepto(-31064,15691,106);
		
		Sleep(1000);
		gcall.PickupTask();
		Sleep(1000);
		break;
	case 2:
		gcall.NewSpend(2.5);
		gcall.Stepto(-31220,15456,44);
		gcall.Stepto(-31239,15431,38);
		gcall.Stepto(-31406,15230,-2);
		gcall.Stepto(-31578,15051,-37);
		gcall.Stepto(-31750,14874,-73);
		gcall.Stepto(-31919,14691,-109);
		gcall.Stepto(-32082,14511,-139);
		gcall.Stepto(-32250,14322,-166);
		gcall.Stepto(-32419,14135,-185);
		gcall.Stepto(-32588,13956,-192);
		gcall.Stepto(-32764,13780,-194);
		gcall.Stepto(-32947,13614,-203);
		gcall.Stepto(-33141,13459,-219);
		gcall.Stepto(-33347,13326,-240);
		gcall.Stepto(-33561,13199,-256);
		gcall.Stepto(-33785,13081,-280);
		gcall.Stepto(-34008,12971,-293);
		gcall.Stepto(-34225,12857,-303);
		gcall.Stepto(-34437,12744,-330);
		gcall.Stepto(-34652,12604,-348);
		gcall.Stepto(-34845,12443,-354);
		gcall.Stepto(-35026,12281,-373);
		gcall.Stepto(-35210,12112,-395);
		gcall.Stepto(-35394,11942,-398);
		gcall.Stepto(-35568,11794,-407);
		gcall.Stepto(-35823,11726,-431);
		gcall.Stepto(-36067,11770,-438);
		gcall.Stepto(-36288,11886,-440);
		gcall.Stepto(-36462,12055,-431);
		gcall.Stepto(-36519,12158,-430);
		gcall.Stepto(-36622,12382,-410);
		gcall.Stepto(-36707,12614,-373);
		gcall.Stepto(-36761,12857,-334);
		gcall.Stepto(-36799,13103,-286);
		gcall.Stepto(-36818,13349,-243);
		gcall.NewSpend(1);
		gcall.Stepto(-36825,13599,-211);
		gcall.Stepto(-36834,13680,-201);
		
		Sleep(1000);
		gcall.PickupTask();
		Sleep(1000);
		break;
	case 3:
		gcall.Stepto(-36929,13628,-208);
		gcall.Stepto(-37049,13617,-212);
		Sleep(1000);
		gcall.DeliverQuests(zid,taskid,L"포청");
		Sleep(1000);
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

void TaskScript::Task_524(int zid,int taskid)
{
	switch (taskid)
	{
	case 1:
		gcall.NewSpend(2.5);
		gcall.Stepto(-36955,13215,-258);
		gcall.Stepto(-36787,13093,-290);
		gcall.Stepto(-36542,13005,-351);
		gcall.Stepto(-36112,13056,-335);
		gcall.Stepto(-35671,13110,-278);
		gcall.Stepto(-35244,13139,-232);
		gcall.Stepto(-34816,13157,-275);
		gcall.Stepto(-34376,13171,-317);
		gcall.Stepto(-33940,13200,-296);
		gcall.Stepto(-33512,13232,-252);
		gcall.Stepto(-33211,13361,-224);
		gcall.Stepto(-33054,13491,-209);
		gcall.Stepto(-32859,13645,-194);
		gcall.Stepto(-32666,13799,-187);
		gcall.Stepto(-32470,13951,-185);
		gcall.Stepto(-32278,14107,-172);
		gcall.Stepto(-32086,14266,-154);
		gcall.Stepto(-31895,14426,-128);
		gcall.Stepto(-31707,14582,-100);
		gcall.Stepto(-31519,14749,-66);
		gcall.Stepto(-31333,14916,-36);
		gcall.Stepto(-31135,15094,1);
		gcall.Stepto(-30796,15361,59);
		gcall.Stepto(-30408,15569,84);
		gcall.Stepto(-30004,15704,99);
		gcall.Stepto(-29936,15715,96);
		gcall.Stepto(-29689,15739,82);
		gcall.Stepto(-29439,15735,71);
		gcall.Stepto(-29191,15742,56);
		gcall.Stepto(-28940,15758,24);
		gcall.Stepto(-28703,15805,-8);
		gcall.Stepto(-28464,15898,-46);
		gcall.Stepto(-28258,15996,-62);
		gcall.Stepto(-28023,16123,-67);
		gcall.Stepto(-27811,16254,-57);
		gcall.Stepto(-27624,16413,-26);
		gcall.Stepto(-27442,16585,7);
		gcall.Stepto(-27336,16796,45);
		gcall.Stepto(-27347,17044,92);
		gcall.Stepto(-27353,17292,164);
		gcall.Stepto(-27423,17528,242);
		gcall.Stepto(-27544,17745,305);
		gcall.Stepto(-27690,17940,360);
		gcall.Stepto(-27881,18099,407);
		gcall.Stepto(-28087,18237,441);
		gcall.Stepto(-28304,18363,483);
		gcall.Stepto(-28526,18479,525);
		gcall.Stepto(-28750,18588,549);
		gcall.Stepto(-28969,18695,579);
		gcall.Stepto(-29192,18803,625);
		gcall.Stepto(-29418,18914,675);
		gcall.Stepto(-29638,19031,732);
		gcall.Stepto(-29847,19165,800);
		gcall.Stepto(-30051,19304,840);
		gcall.Stepto(-30239,19429,860);
		gcall.Stepto(-30408,19536,870);
		gcall.Stepto(-30578,19639,877);
		gcall.Stepto(-30767,19692,879);
		gcall.Stepto(-30963,19677,865);
		gcall.Stepto(-31168,19577,832);
		gcall.Stepto(-31366,19428,762);
		gcall.Stepto(-31555,19277,680);
		gcall.Stepto(-31745,19117,591);
		gcall.Stepto(-31933,18952,499);
		gcall.Stepto(-32124,18785,437);
		gcall.Stepto(-32306,18619,395);
		gcall.Stepto(-32435,18507,394);
		gcall.Stepto(-32517,18364,391);
		gcall.Stepto(-32676,18175,386);
		gcall.Stepto(-32814,18099,388);
		gcall.Stepto(-32998,18008,381);
		gcall.Stepto(-32956,18169,386);
		gcall.Stepto(-32925,18420,419);
		gcall.Stepto(-32966,18607,448);
		gcall.Stepto(-32980,18626,448);
		gcall.Stepto(-33105,18782,446);
		gcall.NewSpend(1);
		gcall.Stepto(-33091,18805,446);
		gcall.Stepto(-33006,18947,446);
		Sleep(1000);
		gcall.DeliverQuests(zid,taskid,L"괴인 적운");
		Sleep(1000);
		break;
	case 2:
		
		gcall.NewSpend(2.5);
		gcall.Stepto(-33120,18789,446);
		gcall.Stepto(-33116,18784,446);
		gcall.Stepto(-33038,18691,448);
		gcall.Stepto(-32941,18581,439);
		gcall.Stepto(-32847,18463,417);
		gcall.Stepto(-32815,18295,396);
		gcall.Stepto(-32919,18186,389);
		gcall.Stepto(-33111,18101,370);
		gcall.Stepto(-33162,18097,367);
		gcall.Stepto(-33385,18130,356);
		gcall.NewSpend(1);
		gcall.Stepto(-33522,18211,346);
		gcall.Stepto(-33700,18376,330);
		gcall.Stepto(-33804,18516,328);
		gcall.Stepto(-33932,18701,328);
		gcall.Stepto(-34095,18922,300);
		gcall.Stepto(-34226,19111,269);
		Sleep(6000);
		gcall.Stepto(-34431,19282,139);
		gcall.WaitPlans();
		gcall.Stepto(-34443,19290,132);
		gcall.Stepto(-34572,19504,3);
		gcall.NewSpend(2.5);
		gcall.Stepto(-34708,19715,-119);
		gcall.Stepto(-34865,19906,-240);
		gcall.Stepto(-35021,20091,-344);
		gcall.Stepto(-35221,20233,-343);
		gcall.Stepto(-35458,20206,-343);
		gcall.Stepto(-35666,20069,-342);
		gcall.Stepto(-35839,19892,-342);
		gcall.Stepto(-36026,19733,-343);
		gcall.Stepto(-36230,19579,-343);
		gcall.Stepto(-36424,19433,-342);
		gcall.Stepto(-36616,19290,-316);
		gcall.Stepto(-36787,19190,-298);
		gcall.Stepto(-36964,19097,-281);
		gcall.Stepto(-37138,19006,-271);
		gcall.Stepto(-37323,18925,-268);
		gcall.Stepto(-37501,18848,-273);
		gcall.Stepto(-37688,18767,-270);
		gcall.Stepto(-37866,18689,-258);
		gcall.Stepto(-38050,18608,-261);
		gcall.Stepto(-38233,18528,-256);
		gcall.Stepto(-38415,18449,-252);
		gcall.Stepto(-38594,18371,-261);
		gcall.Stepto(-38781,18289,-278);
		gcall.Stepto(-38960,18205,-286);
		gcall.Stepto(-39136,18114,-296);
		gcall.Stepto(-39307,18019,-308);
		gcall.Stepto(-39477,17917,-328);
		gcall.Stepto(-39647,17813,-350);
		gcall.Stepto(-39813,17705,-369);
		gcall.Stepto(-39981,17593,-372);
		gcall.Stepto(-40142,17480,-362);
		gcall.Stepto(-40302,17367,-356);
		gcall.Stepto(-40468,17248,-352);
		gcall.Stepto(-40626,17127,-350);
		gcall.Stepto(-40781,17008,-348);
		gcall.Stepto(-40940,16886,-350);
		gcall.Stepto(-41093,16765,-351);
		gcall.Stepto(-41245,16635,-351);
		gcall.Stepto(-41350,16472,-355);
		gcall.Stepto(-41365,16270,-350);
		gcall.Stepto(-41329,16082,-349);
		gcall.Stepto(-41275,15884,-355);
		gcall.Stepto(-41216,15697,-355);
		gcall.Stepto(-41150,15510,-354);
		gcall.Stepto(-41082,15319,-355);
		gcall.Stepto(-41013,15135,-389);
		gcall.Stepto(-40936,14959,-417);
		gcall.Stepto(-40834,14785,-447);
		gcall.Stepto(-40700,14647,-460);
		gcall.Stepto(-40511,14588,-475);
		gcall.Stepto(-40404,14560,-447);
		gcall.Stepto(-40195,14175,-459);
		gcall.Stepto(-40218,13940,-460);
		gcall.Stepto(-40308,13811,-471);
		gcall.Stepto(-40454,13818,-483);
		gcall.NewSpend(1);
		Sleep(2000);
		//过滤怪物(영아령,1);
		gcall.AddCustomKill(L"영아령",DONTKILL);
		gcall.FindThenKill(0,300,modeAoe | modeNormal);
		gcall.ClearCustom();
		gcall.Stepto(-40318,13781,-475);
		gcall.Stepto(-40188,13926,-458);
		gcall.Stepto(-40182,14078,-460);
		gcall.Stepto(-40289,14390,-456);
		gcall.Stepto(-40570,14437,-481);
		gcall.Stepto(-40662,14469,-486);
		gcall.Stepto(-40678,14410,-490);
		Sleep(1000);
		gcall.PickupTask();
		Sleep(1000);
		//过滤怪物(영아령,3);
		gcall.Stepto(-40357,14439,-453);
		Sleep(1000);
		/*对准怪物();
		Sleep(1000);
		按键(R);
		对准怪物();
		Sleep(1000);
		按键(R);
		Sleep(4000);*/
		//gcall.FindThenKill(0,300,modeAoe | modeNormal);
		gcall.TurnToNear(500);
		Sleep(500);
		gcall.KeyPress(82);
		Sleep(1000);
		gcall.TurnToNear(500);
		Sleep(500);
		gcall.KeyPress(82);
		Sleep(2000);
		gcall.PickupSpecTypeTask(200,0x4,L"영아초");
		Sleep(1000);
		gcall.Stepto(-40291,14448,-453);
		Sleep(1000);
		gcall.PickupSpecTypeTask(200,0x4,L"영아초");
		Sleep(1000);


		gcall.Stepto(-40681,14434,-488);
		Sleep(1000);
		gcall.PickupTask();
		Sleep(1000);
		gcall.Stepto(-40745,14653,-463);
		gcall.Stepto(-40927,14826,-435);
		Sleep(1000);
		/*	对准怪物();
		Sleep(1000);
		按键(R);
		对准怪物();
		Sleep(1000);
		按键(R);
		Sleep(4000);*/
		gcall.TurnToNear(500);
		Sleep(500);
		gcall.KeyPress(82);
		Sleep(1000);
		gcall.TurnToNear(500);
		Sleep(500);
		gcall.KeyPress(82);
		Sleep(2000);
		gcall.PickupSpecTypeTask(200,0x4,L"영아초");
		Sleep(1000);
		gcall.Stepto(-41019,14893,-420);
		Sleep(1000);
		gcall.PickupSpecTypeTask(200,0x4,L"영아초");
		Sleep(1000);

		gcall.Stepto(-40681,14434,-488);
		Sleep(1000);
		gcall.PickupTask();
		Sleep(1000);
		gcall.Stepto(-41148,14495,-471);
		gcall.Stepto(-41235,14218,-490);
		Sleep(1000);
		/*对准怪物();
		Sleep(1000);
		按键(R);
		对准怪物();
		Sleep(1000);
		按键(R);
		Sleep(4000);*/
		gcall.TurnToNear(500);
		Sleep(500);
		gcall.KeyPress(82);
		Sleep(1000);
		gcall.TurnToNear(500);
		Sleep(500);
		gcall.KeyPress(82);
		Sleep(2000);
		gcall.PickupSpecTypeTask(200,0x4,L"영아초");
		Sleep(1000);
		gcall.Stepto(-41309,14339,-480);
		Sleep(1000);
		gcall.PickupSpecTypeTask(200,0x4,L"영아초");
		Sleep(1000);
		break;
	case 3:
		gcall.NewSpend(2.5);
		gcall.Stepto(-40846,14577,-466);
		gcall.Stepto(-40850,14599,-464);
		gcall.Stepto(-41001,14990,-409);
		gcall.Stepto(-41165,15404,-353);
		gcall.Stepto(-41308,15798,-355);
		gcall.Stepto(-41394,16135,-346);
		gcall.Stepto(-41373,16339,-354);
		gcall.Stepto(-41299,16569,-354);
		gcall.Stepto(-41169,16786,-349);
		gcall.Stepto(-40979,16939,-348);
		gcall.Stepto(-40771,17079,-348);
		gcall.Stepto(-40561,17213,-351);
		gcall.Stepto(-40354,17345,-354);
		gcall.Stepto(-40143,17480,-361);
		gcall.Stepto(-39931,17616,-373);
		gcall.Stepto(-39727,17747,-361);
		gcall.Stepto(-39538,17865,-340);
		gcall.Stepto(-39165,18075,-300);
		gcall.Stepto(-38778,18281,-277);
		gcall.Stepto(-38521,18413,-253);
		gcall.Stepto(-38340,18488,-253);
		gcall.Stepto(-38156,18565,-258);
		gcall.Stepto(-37975,18640,-263);
		gcall.Stepto(-37790,18718,-261);
		gcall.Stepto(-37608,18794,-273);
		gcall.Stepto(-37427,18878,-271);
		gcall.Stepto(-37258,18983,-269);
		gcall.Stepto(-37089,19092,-276);
		gcall.Stepto(-36924,19198,-287);
		gcall.Stepto(-36756,19306,-303);
		gcall.Stepto(-36589,19413,-322);
		gcall.Stepto(-36423,19520,-339);
		gcall.Stepto(-36256,19627,-340);
		gcall.Stepto(-36088,19734,-343);
		gcall.Stepto(-35918,19840,-342);
		gcall.Stepto(-35761,19942,-342);
		gcall.Stepto(-35602,20045,-343);
		gcall.Stepto(-35433,20146,-340);
		gcall.Stepto(-35251,20229,-343);
		gcall.Stepto(-35064,20202,-343);
		gcall.Stepto(-34929,20051,-319);
		gcall.Stepto(-34810,19893,-215);
		gcall.Stepto(-34691,19735,-120);
		gcall.NewSpend(1);
		gcall.Stepto(-34578,19571,-23);
		gcall.Stepto(-34467,19405,79);
		gcall.Stepto(-34348,19245,181);
		gcall.Stepto(-34244,19131,256);
		gcall.Stepto(-34236,19123,262);
		Sleep(5000);
		gcall.Stepto(-34220,19102,272);
		gcall.WaitPlans();
		gcall.Stepto(-34086,18901,300);
		gcall.Stepto(-33944,18687,328);
		gcall.NewSpend(2.5);
		gcall.Stepto(-33801,18485,328);
		gcall.Stepto(-33645,18298,335);
		gcall.Stepto(-33444,18145,353);
		gcall.Stepto(-33209,18082,366);
		gcall.Stepto(-32958,18097,383);
		gcall.Stepto(-32731,18189,388);
		gcall.Stepto(-32711,18198,388);
		gcall.Stepto(-32710,18199,388);
		gcall.Stepto(-32466,18427,390);
		gcall.Stepto(-32146,18739,425);
		gcall.Stepto(-31844,19054,549);
		gcall.Stepto(-31541,19357,702);
		gcall.Stepto(-31190,19597,835);
		gcall.Stepto(-30968,19660,861);
		gcall.Stepto(-30715,19612,867);
		gcall.Stepto(-30489,19513,865);
		gcall.Stepto(-30272,19387,858);
		gcall.Stepto(-30059,19267,837);
		gcall.Stepto(-29840,19150,794);
		gcall.Stepto(-29620,19034,730);
		gcall.Stepto(-29403,18920,675);
		gcall.Stepto(-29177,18799,622);
		gcall.Stepto(-28963,18683,576);
		gcall.Stepto(-28748,18566,546);
		gcall.Stepto(-28522,18443,521);
		gcall.Stepto(-28316,18314,478);
		gcall.Stepto(-28120,18155,445);
		gcall.Stepto(-27936,17987,403);
		gcall.Stepto(-27756,17817,346);
		gcall.Stepto(-27594,17633,282);
		gcall.Stepto(-27527,17393,206);
		gcall.Stepto(-27587,17153,114);
		gcall.Stepto(-27629,16911,52);
		gcall.Stepto(-27688,16668,12);
		gcall.Stepto(-27773,16431,-28);
		gcall.Stepto(-27894,16218,-62);
		gcall.Stepto(-28088,16092,-67);
		gcall.Stepto(-28327,16051,-54);
		gcall.Stepto(-28764,15984,-1);
		gcall.Stepto(-29186,15891,58);
		gcall.Stepto(-29605,15761,81);
		gcall.Stepto(-30009,15616,98);
		gcall.Stepto(-30416,15444,84);
		gcall.Stepto(-30814,15266,50);
		gcall.Stepto(-31194,15064,-6);
		gcall.Stepto(-31538,14802,-66);
		gcall.Stepto(-31863,14511,-119);
		gcall.Stepto(-32180,14211,-165);
		gcall.Stepto(-32496,13911,-184);
		gcall.Stepto(-32743,13685,-184);
		gcall.Stepto(-32933,13531,-194);
		gcall.Stepto(-33135,13367,-213);
		gcall.Stepto(-33328,13213,-236);
		gcall.Stepto(-33544,13090,-263);
		gcall.Stepto(-33777,13005,-279);
		gcall.Stepto(-34023,12989,-295);
		gcall.Stepto(-34274,13002,-313);
		gcall.Stepto(-34521,13011,-330);
		gcall.Stepto(-34772,13021,-308);
		gcall.Stepto(-34947,13029,-285);
		gcall.Stepto(-35313,13047,-245);
		gcall.Stepto(-35754,13061,-293);
		gcall.Stepto(-36186,13035,-341);
		gcall.Stepto(-36618,13001,-333);
		gcall.Stepto(-36832,13044,-293);
		gcall.Stepto(-36966,13254,-254);
		gcall.Stepto(-37074,13476,-225);
		gcall.Stepto(-37122,13581,-215);
		gcall.NewSpend(1);
		Sleep(1000);
		gcall.DeliverQuests(zid,taskid,L"포청");
		Sleep(1000);
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

void TaskScript::Task_525(int zid,int taskid)
{
	switch (taskid)
	{
	case 1:
		MessageBox(0, L"525", L"装八卦", MB_OK);
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

void TaskScript::Task_526(int zid,int taskid)
{
	switch (taskid)
	{
	case 1:
		MessageBox(0, L"526", L"装八卦", MB_OK);
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

void TaskScript::Task_294(int zid,int taskid)
{
	switch (taskid)
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
BOOL TaskScript::ShunYiResult(DWORD CityId,wchar_t* FileName,BOOL Hook_flag)
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
	while (1)
	{
		if (shunyics >= 2)
		{
			break;
		}
		if (gcall.GetCityID() == CityId)
		{
			log(L"当前地图ID:%d,与传入ID:%d,相同break",gcall.GetCityID(),CityId);
			if (returnflag)
			{
				Sleep(1000);
			}else
			{
				Sleep(5000);
			}
			
			break;
		}else
		{
			if (resultsy == FALSE)
			{
				gcall.Shunyi(FileName);
				Sleep(1000);
				gcall.sendcall(id_msg_OverShunyi,(LPVOID)Hook_flag);//hook
				Sleep(1000);
				resultsy = TRUE;
				shunyics++;
			}
			log(L"当前地图ID:%d,与传入ID:%d,执行瞬移文件吊:%s",gcall.GetCityID(),CityId,FileName);
			Sleep(1000);
			if (shunyirs > 30)
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
				gcall.sendcall(id_msg_TiaoYue,0);
				Sleep(1000);
			}
		}
		shunyirs++;
	}
	return returnflag;
}

void TaskScript::UseExperience()
{
	if (gcall.GetPlayExperienceStatus()==FALSE)
	{
		gcall.SortBag();
		Sleep(1000);
		std::vector<_BAGSTU> GoodsVec;
		gcall.GetAllGoodsToVector(GoodsVec);
		for (int i=0;i<GoodsVec.size();i++)
		{
			if (_wcsicmp(GoodsVec[i].name,L"자경단의 한방 용봉탕") == 0)//%60
			{
				gcall.ChiYao(L"자경단의 한방 용봉탕");
				Sleep(1000);
				gcall.sendcall(id_msg_attack, (LPVOID)0x5dc1);
				return;
			}
		}

		for (int i=0;i<GoodsVec.size();i++)
		{
			if(_wcsicmp(GoodsVec[i].name,L"대사막 약선 용봉탕") == 0)//%40
			{
				gcall.ChiYao(L"대사막 약선 용봉탕");
				Sleep(1000);
				gcall.sendcall(id_msg_attack, (LPVOID)0x5dc1);
				return;
			}
		}

		for (int i=0;i<GoodsVec.size();i++)
		{
			if(_wcsicmp(GoodsVec[i].name,L"제룡림 약선 용봉탕") == 0)//%30
			{
				gcall.ChiYao(L"제룡림 약선 용봉탕");
				Sleep(1000);
				gcall.sendcall(id_msg_attack, (LPVOID)0x5dc1);
				return;
			}
		}

		for (int i=0;i<GoodsVec.size();i++)
		{
			if(_wcsicmp(GoodsVec[i].name,L"제룡림 특제 용봉탕") == 0)//%20
			{
				gcall.ChiYao(L"제룡림 특제 용봉탕");
				Sleep(1000);
				gcall.sendcall(id_msg_attack, (LPVOID)0x5dc1);
				return;
			}
		}
	}
}

void TaskScript::IsGoonHecheng(DWORD pos)
{
	//可能出问题

	for (int i = 0;i < 10;i++)
	{
		_BAGSTU zhu;
		if(gcall.GetGoodsByEquipPos(pos, &zhu) == FALSE)
		{
			log(_T("装备位置没有物品:%d"),pos);
			return;
		}else
		{
			if((zhu.m_PingJi == 5 &&
				(zhu.m_DangQianJingYanZhi == zhu.m_DangQianJingYanZongZhi))
				||
				(zhu.m_PingJi == 10 &&
				zhu.m_DangQianJingYanZhi == zhu.m_DangQianJingYanZongZhi))
			{
				log(_T("要强化的物品已满级:%d"),pos);
				Sleep(1000);
				return;
			}else
			{
				gcall.HeChengWuQiByHun((EQUITMENT_POS)pos);//수련보옥36级首饰魂

				Sleep(1000);
			}
		}
	}
}
////////////////////Task函数线///////////////////////////////


/////////////////////副本分界线///////////////////////////////
void TaskScript::Lianji6_go()
{
	//进副本

	gcall.NewSpend(2.5);
	gcall.Stepto(-36188, -38116, -376,10,20,3000,TRUE);
	gcall.Stepto(-36021, -37957, -374);
	gcall.Stepto(-35842, -37786, -362);
	gcall.Stepto(-35663, -37616, -376);
	gcall.Stepto(-35485, -37445, -379);
	gcall.Stepto(-35307, -37267, -379);
	gcall.Stepto(-35141, -37083, -394);
	gcall.Stepto(-35003, -36877, -434);
	gcall.Stepto(-34873, -36666, -477);
	gcall.Stepto(-34745, -36453, -521);
	gcall.Stepto(-34637, -36230, -574);
	gcall.Stepto(-34550, -35998, -650);
	gcall.Stepto(-34494, -35756, -886);
	gcall.Stepto(-34443, -35514, -1059);
	gcall.Stepto(-34409, -35275, -1081);
	gcall.Stepto(-34413, -35022, -1126);
	gcall.Stepto(-34360, -34785, -1179);
	gcall.Stepto(-34313, -34538, -1195);
	gcall.Stepto(-34267, -34294, -1170);
	gcall.Stepto(-34222, -34050, -1187);
	gcall.Stepto(-34187, -33808, -1256);
	gcall.Stepto(-34153, -33562, -1328);
	gcall.Stepto(-34097, -33320, -1359);
	gcall.Stepto(-34038, -33079, -1380);
	gcall.Stepto(-33962, -32843, -1387);
	gcall.Stepto(-33885, -32607, -1393);
	gcall.Stepto(-33808, -32369, -1428);
	gcall.Stepto(-33732, -32134, -1440);
	gcall.Stepto(-33655, -31898, -1421);
	gcall.Stepto(-33580, -31666, -1364);
	gcall.Stepto(-33502, -31425, -1342);
	gcall.Stepto(-33426, -31190, -1355);
	gcall.Stepto(-33349, -30953, -1365);
	gcall.Stepto(-33257, -30723, -1381);
	gcall.Stepto(-33161, -30495, -1379);
	gcall.Stepto(-33069, -30265, -1365);
	gcall.Stepto(-32976, -30034, -1335);
	gcall.Stepto(-32883, -29802, -1310);
	gcall.Stepto(-32791, -29576, -1292);
	gcall.Stepto(-32698, -29343, -1285);
	gcall.Stepto(-32605, -29114, -1281);
	gcall.Stepto(-32518, -28897, -1279);
	gcall.Stepto(-32420, -28652, -1283);
	gcall.Stepto(-32327, -28422, -1289);
	gcall.Stepto(-32233, -28193, -1284);
	gcall.Stepto(-32143, -27974, -1272);
	gcall.Stepto(-32044, -27733, -1261);
	gcall.Stepto(-31949, -27504, -1239);
	gcall.Stepto(-31852, -27273, -1214);
	gcall.Stepto(-31756, -27044, -1196);
	gcall.Stepto(-31660, -26815, -1172);
	gcall.Stepto(-31563, -26586, -1146);
	gcall.Stepto(-31461, -26359, -1105);
	gcall.Stepto(-31360, -26132, -1083);
	gcall.Stepto(-31260, -25908, -1046);
	gcall.Stepto(-31157, -25678, -1004);
	gcall.Stepto(-31063, -25468, -994);
	gcall.Stepto(-31063, -25467, -994);
	gcall.Stepto(-31094, -25448, -994);
	gcall.Stepto(-31304, -25319, -999);
	gcall.Stepto(-31517, -25189, -1006);
	gcall.Stepto(-31730, -25059, -1015);
	gcall.Stepto(-31940, -24930, -1024);
	gcall.Stepto(-32152, -24801, -1032);
	gcall.Stepto(-32364, -24689, -1029);
	gcall.Stepto(-32622, -24667, -1043);
	gcall.Stepto(-32868, -24692, -1070);
	gcall.Stepto(-33116, -24712, -1097);
	gcall.Stepto(-33364, -24714, -1123);
	gcall.Stepto(-33612, -24715, -1142);
	gcall.Stepto(-33860, -24717, -1158);
	gcall.Stepto(-34108, -24718, -1176);
	gcall.Stepto(-34360, -24719, -1181);
	gcall.Stepto(-34609, -24721, -1188);
	gcall.Stepto(-34857, -24722, -1202);
	gcall.Stepto(-35104, -24735, -1221);
	gcall.Stepto(-35343, -24800, -1237);
	gcall.Stepto(-35576, -24883, -1239);
	gcall.Stepto(-35809, -24971, -1289);
	gcall.Stepto(-36043, -25065, -1338);
	gcall.Stepto(-36270, -25157, -1392);
	gcall.Stepto(-36504, -25251, -1431);
	gcall.Stepto(-36734, -25344, -1459);
	gcall.Stepto(-36965, -25438, -1479);
	gcall.Stepto(-37196, -25531, -1504);
	gcall.Stepto(-37383, -25429, -1515);
	gcall.Stepto(-37552, -25247, -1524);
	gcall.Stepto(-37732, -25077, -1541);
	gcall.Stepto(-37913, -24907, -1548);
	gcall.Stepto(-38093, -24737, -1557);
	gcall.Stepto(-38277, -24565, -1554);
	gcall.Stepto(-38458, -24395, -1536);
	gcall.Stepto(-38639, -24225, -1491);
	gcall.Stepto(-38821, -24057, -1431);
	gcall.Stepto(-39004, -23890, -1394);
	gcall.Stepto(-39190, -23719, -1397);
	gcall.Stepto(-39164, -23492, -1364);
	gcall.Stepto(-39078, -23261, -1372);
	gcall.Stepto(-39007, -23055, -1362);
	gcall.NewSpend(1);
	Sleep(2000);
	//进副本结束


}
void TaskScript::Lianji6()
{
	//死亡

	if (gcall.GetPlayerDeadStatus() == 1 ||
		gcall.GetPlayerDeadStatus() == 2)
	{
		Sleep(5000);
		gcall.FuHuo();
		Sleep(3000);
		gcall.Stepto(-38753, -22648, -1377);
		gcall.Stepto(-38879, -22851, -1341);
		gcall.Stepto(-38939, -22910, -1329);
	}
	_BAGSTU stu;
	gcall.GetGoodsByEquipPos(EQUITMENT_POS::WUQI, &stu);
	if (stu.m_Lasting < 10)
	{
		gcall.NewSpend(2.5);
		gcall.Stepto(-38983, -22977, -1342);
		gcall.Stepto(-39017, -23073, -1367);
		gcall.Stepto(-39098, -23304, -1370);
		gcall.Stepto(-39135, -23549, -1368);
		gcall.Stepto(-39075, -23789, -1395);
		gcall.Stepto(-38936, -23985, -1411);
		gcall.Stepto(-38743, -24117, -1452);
		gcall.Stepto(-38394, -24371, -1542);
		gcall.Stepto(-38020, -24593, -1537);
		gcall.Stepto(-37642, -24806, -1507);
		gcall.Stepto(-37262, -25013, -1477);
		gcall.Stepto(-36874, -25212, -1475);
		gcall.Stepto(-36479, -25388, -1414);
		gcall.Stepto(-36083, -25562, -1315);
		gcall.Stepto(-35684, -25739, -1235);
		gcall.Stepto(-35292, -25911, -1220);
		gcall.Stepto(-34889, -26087, -1231);
		gcall.Stepto(-34479, -26227, -1231);
		gcall.Stepto(-34057, -26326, -1207);
		gcall.Stepto(-33626, -26378, -1162);
		gcall.Stepto(-33193, -26352, -1115);
		gcall.Stepto(-32865, -26314, -1101);
		gcall.Stepto(-32625, -26255, -1094);
		gcall.Stepto(-32385, -26193, -1084);
		gcall.Stepto(-32145, -26131, -1073);
		gcall.Stepto(-31905, -26065, -1069);
		gcall.Stepto(-31667, -25998, -1072);
		gcall.Stepto(-31428, -25931, -1063);
		gcall.Stepto(-31194, -25849, -1017);
		gcall.Stepto(-31057, -25757, -996);
		gcall.Stepto(-30888, -25573, -990);
		gcall.Stepto(-30712, -25399, -986);
		gcall.Stepto(-30639, -25438, -988);
		gcall.Stepto(-30550, -25517, -990);
		gcall.Stepto(-30571, -25434, -987);
		gcall.Stepto(-30594, -25575, -991);
		gcall.NewSpend(1);
		Sleep(1000);
		gcall.FixWuqi();
		Sleep(1000);
		gcall.NewSpend(2.5);
		gcall.Stepto(-30580, -25474, -990);
		gcall.Stepto(-30681, -25449, -989);
		gcall.Stepto(-30917, -25372, -981);
		gcall.Stepto(-31054, -25325, -987);
		gcall.Stepto(-31435, -25219, -1002);
		gcall.Stepto(-31857, -25112, -1023);
		gcall.Stepto(-32280, -25007, -1042);
		gcall.Stepto(-32687, -24906, -1058);
		gcall.Stepto(-33122, -24798, -1097);
		gcall.Stepto(-33539, -24695, -1137);
		gcall.Stepto(-33964, -24592, -1162);
		gcall.Stepto(-34397, -24556, -1178);
		gcall.Stepto(-34830, -24576, -1203);
		gcall.Stepto(-35253, -24662, -1229);
		gcall.Stepto(-35674, -24766, -1242);
		gcall.Stepto(-36100, -24845, -1324);
		gcall.Stepto(-36536, -24841, -1429);
		gcall.Stepto(-36961, -24763, -1453);
		gcall.Stepto(-37385, -24667, -1464);
		gcall.Stepto(-37626, -24606, -1480);
		gcall.Stepto(-37859, -24521, -1505);
		gcall.Stepto(-38087, -24427, -1542);
		gcall.Stepto(-38317, -24333, -1544);
		gcall.Stepto(-38546, -24238, -1504);
		gcall.Stepto(-38775, -24144, -1454);
		gcall.Stepto(-38981, -24006, -1409);
		gcall.Stepto(-39116, -23801, -1396);
		gcall.Stepto(-39182, -23565, -1393);
		gcall.Stepto(-39128, -23330, -1370);
		gcall.Stepto(-39015, -23141, -1377);
		gcall.Stepto(-38939, -22910, -1329);
		gcall.NewSpend(1);
		Sleep(1500);
	}

	if (gcall.GetBagGridNumberLast() < 5)
	{
		gcall.NewSpend(2.5);
		gcall.Stepto(-38983, -22977, -1342);
		gcall.Stepto(-39017, -23073, -1367);
		gcall.Stepto(-39098, -23304, -1370);
		gcall.Stepto(-39135, -23549, -1368);
		gcall.Stepto(-39075, -23789, -1395);
		gcall.Stepto(-38936, -23985, -1411);
		gcall.Stepto(-38743, -24117, -1452);
		gcall.Stepto(-38394, -24371, -1542);
		gcall.Stepto(-38020, -24593, -1537);
		gcall.Stepto(-37642, -24806, -1507);
		gcall.Stepto(-37262, -25013, -1477);
		gcall.Stepto(-36874, -25212, -1475);
		gcall.Stepto(-36479, -25388, -1414);
		gcall.Stepto(-36083, -25562, -1315);
		gcall.Stepto(-35684, -25739, -1235);
		gcall.Stepto(-35292, -25911, -1220);
		gcall.Stepto(-34889, -26087, -1231);
		gcall.Stepto(-34479, -26227, -1231);
		gcall.Stepto(-34057, -26326, -1207);
		gcall.Stepto(-33626, -26378, -1162);
		gcall.Stepto(-33193, -26352, -1115);
		gcall.Stepto(-32865, -26314, -1101);
		gcall.Stepto(-32625, -26255, -1094);
		gcall.Stepto(-32385, -26193, -1084);
		gcall.Stepto(-32145, -26131, -1073);
		gcall.Stepto(-31905, -26065, -1069);
		gcall.Stepto(-31667, -25998, -1072);
		gcall.Stepto(-31428, -25931, -1063);
		gcall.Stepto(-31194, -25849, -1017);
		gcall.Stepto(-31057, -25757, -996);
		gcall.Stepto(-30888, -25573, -990);
		gcall.Stepto(-30712, -25399, -986);
		gcall.Stepto(-30639, -25438, -988);
		gcall.Stepto(-30550, -25517, -990);
		gcall.Stepto(-30550, -25517, -990);
		gcall.Stepto(-30475, -25619, -991);
		gcall.NewSpend(1);
		Sleep(1000);
		gcall.SellItemByConfig(L"이화상");
		Sleep(1000);
		gcall.NewSpend(2.5);
		gcall.Stepto(-30580, -25474, -990);
		gcall.Stepto(-30681, -25449, -989);
		gcall.Stepto(-30917, -25372, -981);
		gcall.Stepto(-31054, -25325, -987);
		gcall.Stepto(-31435, -25219, -1002);
		gcall.Stepto(-31857, -25112, -1023);
		gcall.Stepto(-32280, -25007, -1042);
		gcall.Stepto(-32687, -24906, -1058);
		gcall.Stepto(-33122, -24798, -1097);
		gcall.Stepto(-33539, -24695, -1137);
		gcall.Stepto(-33964, -24592, -1162);
		gcall.Stepto(-34397, -24556, -1178);
		gcall.Stepto(-34830, -24576, -1203);
		gcall.Stepto(-35253, -24662, -1229);
		gcall.Stepto(-35674, -24766, -1242);
		gcall.Stepto(-36100, -24845, -1324);
		gcall.Stepto(-36536, -24841, -1429);
		gcall.Stepto(-36961, -24763, -1453);
		gcall.Stepto(-37385, -24667, -1464);
		gcall.Stepto(-37626, -24606, -1480);
		gcall.Stepto(-37859, -24521, -1505);
		gcall.Stepto(-38087, -24427, -1542);
		gcall.Stepto(-38317, -24333, -1544);
		gcall.Stepto(-38546, -24238, -1504);
		gcall.Stepto(-38775, -24144, -1454);
		gcall.Stepto(-38981, -24006, -1409);
		gcall.Stepto(-39116, -23801, -1396);
		gcall.Stepto(-39182, -23565, -1393);
		gcall.Stepto(-39128, -23330, -1370);
		gcall.Stepto(-39015, -23141, -1377);
		gcall.Stepto(-38939, -22910, -1329);
		gcall.NewSpend(1);
		Sleep(1500);
	}
	gcall.Stepto(-38858, -22737, -1353,120);
	gcall.Stepto(-38797, -22584, -1386,120);
	//MessageBox(0, 0, 0, MB_OK);
	//gcall.Stepto(-38705, -22354, -1455);
	/*
	gcall.Stepto(-38615, -22123, -1476);
	gcall.Stepto(-38573, -21881, -1444);
	gcall.Stepto(-38639, -21643, -1401);
	gcall.Stepto(-38759, -21427, -1348);
	gcall.Stepto(-38957, -21281, -1270);
	gcall.Stepto(-39173, -21151, -1190);
	gcall.Stepto(-39386, -21024, -1098);
	gcall.Stepto(-39600, -20899, -999);
	gcall.Stepto(-39820, -20786, -954);
	gcall.Stepto(-40042, -20675, -933);
	gcall.Stepto(-40263, -20564, -934);
	gcall.Stepto(-40475, -20435, -935);*/
	//MessageBox(0, L"摇奖完", L"装八卦", MB_OK);
	Sleep(1000);
	gcall.Shunyi(L"Lianji6");
	Sleep(2000);
	gcall.Stepto(-40539, -20262, -935);
	gcall.Stepto(-40684, -20145, -933);
	gcall.Stepto(-40806, -20005, -931);
	gcall.Stepto(-40906, -19848, -928);
	gcall.Stepto(-41005, -19689, -926);
	gcall.Stepto(-41105, -19532, -926);
	gcall.Stepto(-41204, -19374, -929);
	gcall.Stepto(-41310, -19221, -928);
	gcall.Stepto(-41436, -19082, -927);
	gcall.Stepto(-41603, -19008, -928);
	gcall.Stepto(-41787, -19026, -932);
	gcall.Stepto(-41917, -19152, -933);
	gcall.Stepto(-41929, -19335, -932);
	gcall.Stepto(-41885, -19516, -930);

	//gcall.FindThenKill(0, 1000, modeNormal | modeAoe | modeGoback | modePickup);
	

	

	if (gcall.FindThenKill(0, 1000, modeNormal | modeAoe | modePickup) == RESULT_KILL_PLAYDEAD)
	{
		Sleep(5000);
		gcall.FuHuo();
		Sleep(3000);
		gcall.Stepto(-38753, -22648, -1377);
		gcall.Stepto(-38879, -22851, -1341);
		gcall.Stepto(-38939, -22910, -1329);
	}
	else
	{
		gcall.Stepto(-41612, -19432, -932);
		Sleep(1000);
		/*
		MessageBox(0, 0, 0, MB_OK);
		gcall.Stepto(-41084, -19810, -928);
		gcall.Stepto(-40888, -19961, -930);
		gcall.Stepto(-40686, -20106, -932);
		gcall.Stepto(-40490, -20248, -935);
		gcall.Stepto(-40286, -20395, -934);
		gcall.Stepto(-40079, -20544, -932);
		gcall.Stepto(-39879, -20687, -937);
		gcall.Stepto(-39678, -20832, -971);
		gcall.Stepto(-39478, -20978, -1053);
		gcall.Stepto(-39278, -21125, -1158);
		gcall.Stepto(-39078, -21272, -1245);
		gcall.Stepto(-38879, -21419, -1328);
		gcall.Stepto(-38696, -21586, -1387);
		gcall.Stepto(-38613, -21817, -1430);
		gcall.Stepto(-38603, -22064, -1470);
		gcall.Stepto(-38662, -22305, -1461);
		gcall.Stepto(-38742, -22539, -1406);
		gcall.Stepto(-38861, -22756, -1351);
		gcall.Stepto(-38885, -22798, -1345);*/
		gcall.Shunyi(L"Lianji6-end");
		Sleep(2000);
	}

	//打怪完

	//延时(5000);
	gcall.HeChengWuQi(EQUITMENT_POS::WUQI);
	Sleep(500);
	gcall.BuqiBaGua(L"충각 치명보패");
	Sleep(500);
	//gcall.TihuanBaGua(L"");
	gcall.FenJieByConfig();
	Sleep(4000);
	gcall.Stepto(-38939, -22910, -1329,120);
	//整理背包();
	Sleep(4000);

}

void TaskScript::lianji8_go()
{
	gcall.NewSpend(2.5);
	gcall.Stepto(-36781, -38069, -379,10,20,3000,TRUE);
	gcall.Stepto(-36586, -37994, -360);
	gcall.Stepto(-36352, -37901, -374);
	gcall.Stepto(-36122, -37809, -373);
	gcall.Stepto(-35892, -37717, -359);
	gcall.Stepto(-35668, -37611, -376);
	gcall.Stepto(-35456, -37481, -379);
	gcall.Stepto(-35254, -37345, -379);
	gcall.Stepto(-35065, -37178, -395);
	gcall.Stepto(-34943, -36966, -426);
	gcall.Stepto(-34883, -36730, -465);
	gcall.Stepto(-34905, -36481, -524);
	gcall.Stepto(-34975, -36247, -591);
	gcall.Stepto(-35160, -36075, -660);
	gcall.Stepto(-35348, -35914, -761);
	gcall.Stepto(-35486, -35710, -866);
	gcall.Stepto(-35414, -35491, -936);
	gcall.Stepto(-35178, -35440, -978);
	gcall.Stepto(-34930, -35451, -1012);
	gcall.Stepto(-34692, -35458, -1032);
	gcall.Stepto(-34433, -35448, -1069);
	gcall.Stepto(-34191, -35407, -1102);
	gcall.Stepto(-33986, -35273, -1131);
	gcall.Stepto(-33767, -35151, -1154);
	gcall.Stepto(-33541, -35044, -1156);
	gcall.Stepto(-33318, -34938, -1141);
	gcall.Stepto(-33093, -34832, -1115);
	gcall.Stepto(-32868, -34725, -1082);
	gcall.Stepto(-32645, -34620, -1051);
	gcall.Stepto(-32419, -34513, -1012);
	gcall.Stepto(-32193, -34406, -973);
	gcall.Stepto(-31969, -34300, -955);
	gcall.Stepto(-31747, -34196, -926);
	gcall.Stepto(-31536, -34068, -889);
	gcall.Stepto(-31337, -33918, -846);
	gcall.Stepto(-31140, -33766, -790);
	gcall.Stepto(-30953, -33600, -756);
	gcall.Stepto(-30849, -33396, -736);
	gcall.Stepto(-30750, -33157, -728);
	gcall.Stepto(-30657, -32918, -708);
	gcall.Stepto(-30567, -32685, -688);
	gcall.Stepto(-30480, -32458, -684);
	gcall.Stepto(-30397, -32221, -716);
	gcall.Stepto(-30365, -31977, -769);
	gcall.Stepto(-30353, -31727, -841);
	gcall.Stepto(-30350, -31474, -916);
	gcall.Stepto(-30351, -31229, -978);
	gcall.Stepto(-30352, -30981, -1039);
	gcall.Stepto(-30353, -30731, -1096);
	gcall.Stepto(-30361, -30481, -1139);
	gcall.Stepto(-30369, -30233, -1167);
	gcall.Stepto(-30390, -29984, -1184);
	gcall.Stepto(-30423, -29737, -1192);
	gcall.Stepto(-30462, -29492, -1186);
	gcall.Stepto(-30511, -29252, -1179);
	gcall.Stepto(-30562, -29004, -1176);
	gcall.Stepto(-30610, -28765, -1173);
	gcall.Stepto(-30657, -28516, -1173);
	gcall.Stepto(-30702, -28279, -1174);
	gcall.Stepto(-30751, -28029, -1180);
	gcall.Stepto(-30815, -27789, -1189);
	gcall.Stepto(-30882, -27551, -1194);
	gcall.Stepto(-30950, -27309, -1192);
	gcall.Stepto(-31016, -27072, -1186);
	gcall.Stepto(-31084, -26830, -1160);
	gcall.Stepto(-31150, -26593, -1152);
	gcall.Stepto(-31217, -26354, -1110);
	gcall.Stepto(-31271, -26109, -1077);
	gcall.Stepto(-31285, -25861, -1043);
	gcall.Stepto(-31250, -25616, -1008);
	gcall.Stepto(-31194, -25374, -996);
	gcall.Stepto(-31138, -25131, -985);
	gcall.Stepto(-31079, -24889, -977);
	gcall.Stepto(-31021, -24647, -974);
	gcall.Stepto(-30962, -24403, -968);
	gcall.Stepto(-30904, -24163, -961);
	gcall.Stepto(-30846, -23923, -957);
	gcall.Stepto(-30803, -23678, -965);
	gcall.Stepto(-30771, -23429, -992);
	gcall.Stepto(-30740, -23184, -1024);
	gcall.Stepto(-30708, -22936, -1039);
	gcall.Stepto(-30676, -22691, -1036);
	gcall.Stepto(-30644, -22443, -1040);
	gcall.Stepto(-30613, -22197, -1051);
	gcall.Stepto(-30582, -21959, -1040);
	gcall.Stepto(-30552, -21718, -1017);
	gcall.Stepto(-30477, -21479, -991);
	gcall.Stepto(-30371, -21252, -976);
	gcall.Stepto(-30230, -21050, -964);
	gcall.Stepto(-30073, -20857, -941);
	gcall.Stepto(-29912, -20673, -924);
	gcall.Stepto(-29740, -20483, -905);
	gcall.Stepto(-29575, -20302, -900);
	gcall.Stepto(-29412, -20111, -896);
	gcall.Stepto(-29306, -19889, -897);
	gcall.Stepto(-29297, -19639, -899);
	gcall.Stepto(-29327, -19393, -909);
	gcall.Stepto(-29375, -19149, -908);
	gcall.Stepto(-29428, -18905, -918);
	gcall.Stepto(-29484, -18664, -924);
	gcall.Stepto(-29540, -18422, -917);
	gcall.Stepto(-29605, -18183, -898);
	gcall.Stepto(-29670, -17949, -879);
	gcall.Stepto(-29714, -17698, -846);
	gcall.Stepto(-29715, -17446, -810);
	gcall.Stepto(-29699, -17199, -795);
	gcall.Stepto(-29660, -16954, -756);
	gcall.Stepto(-29623, -16711, -712);
	gcall.NewSpend(1);
	gcall.Stepto(-29619, -16682, -711);
	gcall.Stepto(-29580, -16292, -697);
	Sleep(2000);
}

void TaskScript::lianji8()
{
	//副本里A2A 副本外 2000
	//死亡

	if (gcall.GetPlayerDeadStatus() == 1 ||
		gcall.GetPlayerDeadStatus() == 2)
	{
		Sleep(5000);
		gcall.FuHuo();
		Sleep(3000);
		gcall.Stepto(-29719, -14670, -1237);
		gcall.Stepto(-29689, -15176, -975);
		gcall.Stepto(-29633, -15683, -748);
		gcall.Stepto(-29580, -16292, -697);
	}

	//修理

	_BAGSTU stu;
	gcall.GetGoodsByEquipPos(EQUITMENT_POS::WUQI, &stu);
	//MessageBox(0, L"摇奖完", L"装八卦", MB_OK);
	if (stu.m_Lasting < 10)
	{
		//这里首先要保证能走到瞬移的点上，如果有自动寻路的话就可以很精准。

		BOOL flagrs = gcall.Stepto(-35566, -12217, -1713,10,20,2500);
		if (flagrs)
		{
			ShunYiResult(2000,L"Lianji8-end",TRUE);//这里是保证已经瞬移到8级副本外了。地图ID：2000
			gcall.Shunyi(L"Lianji8-mai-men");
			Sleep(3000);
			gcall.sendcall(id_msg_OverShunyi,(LPVOID)0);//hook
			Sleep(3000);
			gcall.WaitPlans();
			gcall.HeChengWuQi(EQUITMENT_POS::WUQI);
			Sleep(1000);
			gcall.BuqiBaGua(L"충각 치명보패");
			Sleep(1000);
			gcall.FenJieByConfig();
		}
		gcall.Stepto(-29603, -16562, -677);
		Sleep(1000);
		gcall.Shunyi(L"Lianji8-mai");
		Sleep(1000);
		gcall.sendcall(id_msg_OverShunyi,(LPVOID)0);//hook
		Sleep(1000);
		gcall.Stepto(-30513, -25672, -991);
		Sleep(1000);
		gcall.FixWuqi();
		Sleep(1000);
		gcall.Stepto(-30578, -25431, -987);
		Sleep(1000);
		gcall.Shunyi(L"Lianji8-mai-hui");
		Sleep(1000);
		gcall.sendcall(id_msg_OverShunyi,(LPVOID)0);//hook
		Sleep(5000);
		gcall.Stepto(-29680,-16865,-745);
		gcall.Stepto(-29580, -16292, -697);
		Sleep(3000);
	}

	//卖

	if (gcall.GetBagGridNumberLast() < 5)
	{
		BOOL flagrs = gcall.Stepto(-35566, -12217, -1713,10,20,2500);
		if (flagrs)
		{
			ShunYiResult(2000,L"Lianji8-end",TRUE);//这里是保证已经瞬移到8级副本外了。地图ID：2000
			Sleep(1000);
			gcall.Shunyi(L"Lianji8-mai-men");
			Sleep(3000);
			gcall.sendcall(id_msg_OverShunyi,(LPVOID)0);//hook
			Sleep(3000);
			gcall.WaitPlans();
			gcall.HeChengWuQi(EQUITMENT_POS::WUQI);
			Sleep(1000);
			gcall.BuqiBaGua(L"충각 치명보패");
			Sleep(1000);
			gcall.FenJieByConfig();
		}
		gcall.Stepto(-29603, -16562, -677);
		Sleep(1000);
		gcall.Shunyi(L"Lianji8-mai");
		Sleep(1000);
		gcall.sendcall(id_msg_OverShunyi,(LPVOID)0);//hook
		Sleep(1000);
		gcall.Stepto(-30513, -25672, -991);
		Sleep(1000);
		gcall.SellItemByConfig(L"이화상");
		Sleep(1000);
		gcall.Stepto(-30578, -25431, -987);
		Sleep(1000);
		gcall.Shunyi(L"Lianji8-mai-hui");
		Sleep(1000);
		gcall.sendcall(id_msg_OverShunyi,(LPVOID)0);//hook
		Sleep(5000);
		gcall.Stepto(-29680,-16865,-745);
		gcall.Stepto(-29580, -16292, -697);
		Sleep(3000);
	}


	//BOOL flag = gcall.Stepto(-39308, -11900, -1416,10,20,2500);
	BOOL flag = gcall.Stepto(-35566, -12217, -1713,10,20,2500);
	if (flag == TRUE)
	{
		

		//Sleep(1000);
		//gcall.Shunyi(L"Lianji8-end");
		//Sleep(1000);
		//gcall.sendcall(id_msg_OverShunyi,(LPVOID)1);//hook
		//Sleep(1000);
		ShunYiResult(2000,L"Lianji8-end",TRUE);//这里是保证已经瞬移到8级副本外了。地图ID：2000
		gcall.HeChengWuQi(EQUITMENT_POS::WUQI);
		Sleep(1000);
		gcall.BuqiBaGua(L"충각 치명보패");
		Sleep(1000);
		gcall.FenJieByConfig();
		Sleep(1000);

		ShunYiResult(2602,L"Lianji8-go",TRUE);//这里是保证已经瞬移到8级副本里了。地图ID：2602
		//gcall.Shunyi(L"Lianji8-go");
		//Sleep(1000);
		//gcall.sendcall(id_msg_OverShunyi,(LPVOID)1);//hook
		//Sleep(2000);

		gcall.Shunyi(L"Lianji8");
		Sleep(1000);
		gcall.sendcall(id_msg_OverShunyi,(LPVOID)0);//hook
	}else
	{
		while (1)
		{
			gcall.Stepto(-29580, -16292, -697);
			BOOL flag = ShunYiResult(2602,L"Lianji8-go",FALSE);//这里是保证已经瞬移到8级副本里了。地图ID：2602
			if (flag)
			{
				Sleep(3000);
				break;
			}
		}
		
		//Sleep(1000);
		//gcall.Shunyi(L"Lianji8-go");
		//Sleep(1000);
		//gcall.sendcall(id_msg_OverShunyi,(LPVOID)0);//hook
		//Sleep(2000);
		gcall.Shunyi(L"Lianji8");
		Sleep(1000);
		gcall.sendcall(id_msg_OverShunyi,(LPVOID)0);//hook
	}
	
	


	Sleep(2000);
	gcall.Stepto(-32935, -14344, -1650);
	//引怪

	gcall.Stepto(-33182, -14357, -1697);
	gcall.Stepto(-33433, -14355, -1704);
	gcall.Stepto(-33635, -14358, -1704);
	gcall.Stepto(-33837, -14360, -1704);
	gcall.Stepto(-34040, -14363, -1704);
	gcall.Stepto(-34243, -14365, -1704);
	gcall.Stepto(-34492, -14368, -1704);
	gcall.Stepto(-34696, -14371, -1704);
	gcall.Stepto(-34898, -14373, -1704);
	gcall.Stepto(-35100, -14374, -1704);
	gcall.Stepto(-35302, -14370, -1704);
	gcall.Stepto(-35536, -14284, -1709);
	gcall.Stepto(-35698, -14099, -1709);
	gcall.Stepto(-35724, -13853, -1716);
	gcall.Stepto(-35711, -13651, -1716);
	gcall.Stepto(-35700, -13450, -1716);
	gcall.Stepto(-35687, -13246, -1709);
	gcall.Stepto(-35673, -13044, -1713);
	gcall.Stepto(-35613, -12850, -1713);
	gcall.Stepto(-35549, -12658, -1713);
	gcall.Stepto(-35489, -12463, -1713);
	gcall.Stepto(-35430, -12270, -1713);
	gcall.sendcall(id_msg_attack, (LPVOID)0x5dca);
	gcall.Stepto(-35331, -11989, -1713);
	/*gcall.sendcall(id_msg_attack, (LPVOID)0x5dca);
	Sleep(500);
	gcall.Stepto(-35541, -12104, -1713);
	gcall.sendcall(id_msg_attack, (LPVOID)0x5dca);
	Sleep(500);
	gcall.Stepto(-35713, -12207, -1713);
	gcall.Stepto(-35898, -12295, -1713);
	gcall.Stepto(-36081, -12376, -1713);
	gcall.Stepto(-36272, -12441, -1713);
	gcall.Stepto(-36475, -12447, -1707);
	gcall.Stepto(-36678, -12446, -1707);
	gcall.Stepto(-36879, -12442, -1612);
	gcall.Stepto(-37083, -12436, -1487);
	gcall.Stepto(-37287, -12431, -1416);
	gcall.Stepto(-37491, -12426, -1416);
	gcall.Stepto(-37695, -12424, -1416);
	gcall.Stepto(-37897, -12424, -1411);
	gcall.Stepto(-38101, -12425, -1411);
	gcall.Stepto(-38305, -12425, -1411,10,20,1500,TRUE);
	gcall.Stepto(-38509, -12426, -1409);
	gcall.Stepto(-38710, -12423, -1409);
	gcall.Stepto(-38910, -12421, -1409,10,20,1500,TRUE);
	gcall.Stepto(-38038, -11722, -1416,10,20,1500,TRUE);
	gcall.sendcall(id_msg_attack, (LPVOID)0x5dca);
	Sleep(1000);
	gcall.sendcall(id_msg_attack, (LPVOID)0x5dca);
	Sleep(1000);
	gcall.sendcall(id_msg_attack, (LPVOID)0x5dca);
	Sleep(1000);

	gcall.Stepto(-38252, -11894, -1416);
	gcall.sendcall(id_msg_attack, (LPVOID)0x5dca);
	gcall.Stepto(-38294, -12096, -1416);
	gcall.sendcall(id_msg_attack, (LPVOID)0x5dca);*/
	if (gcall.FindThenKill(0, 500, modeNormal | modeAoe | modePickup) == RESULT_KILL_PLAYDEAD)
	{
		Sleep(5000);
		gcall.FuHuo();
		Sleep(3000);
		gcall.Stepto(-29719, -14670, -1237);
		gcall.Stepto(-29689, -15176, -975);
		gcall.Stepto(-29633, -15683, -748);
		gcall.Stepto(-29580, -16292, -697);
	}
	else
	{
		BOOL zlflag = gcall.Stepto(-35540 , -12119 , -1713);
		if (zlflag)
		{
			Sleep(1000);
			_BAGSTU yaoshi;
			if (gcall.GetGoodsFromBagByName(L"제룡림 열쇠",&yaoshi))
			{
				gcall.Stepto(-35540 , -12119 , -1713);
				Sleep(1000);
				gcall.Shunyi(L"Lianji8-hz");
				Sleep(1000);
				gcall.sendcall(id_msg_OverShunyi,(LPVOID)0);
				Sleep(3000);
				gcall.Stepto(-39593 , -11839 , -1416);
				Sleep(3000);
				if (gcall.FindThenKill(0, 500, modeNormal | modeAoe | modePickup) == RESULT_KILL_PLAYDEAD)
				{
					Sleep(5000);
					gcall.FuHuo();
					Sleep(3000);
					gcall.Stepto(-29719, -14670, -1237);
					gcall.Stepto(-29689, -15176, -975);
					gcall.Stepto(-29633, -15683, -748);
					gcall.Stepto(-29580, -16292, -697);
				}
				gcall.Stepto(-39593 , -11839 , -1416);
				Sleep(1000);
				gcall.PickupTask();
				Sleep(1000);
				gcall.Stepto(-39528 , -11701 , -1416);
				Sleep(1000);
				gcall.Shunyi(L"Lianji8-hz-end");
				Sleep(1000);
				gcall.sendcall(id_msg_OverShunyi,(LPVOID)0);
				Sleep(2000);
			}
		}
	}
	//打怪完

	//延时(5000);
	/*gcall.HeChengWuQi(EQUITMENT_POS::WUQI);
	Sleep(1000);
	gcall.BuqiBaGua(L"충각 치명보패");
	Sleep(1000);
	gcall.FenJieByConfig();
	Sleep(1000);*/
	//Sleep(4000);
	////走到门口的坐标

	//gcall.Stepto(-29590, -16033, -713,120);
	//gcall.Stepto(-29561, -16406, -689,120);
	//Sleep(4000);
	
	

}


void TaskScript::lianji10_go()
{
	gcall.Stepto(-2387,-26858,-2230,10,20,3000,TRUE);
	gcall.Stepto(-2343,-26916,-2230);
	gcall.NewSpend(2.5);
	gcall.Stepto(-2169,-27096,-2235);
	gcall.Stepto(-2028,-27297,-2268);
	gcall.Stepto(-1912,-27518,-2359);
	gcall.Stepto(-1877,-27752,-2482);
	gcall.Stepto(-1909,-28009,-2567);
	gcall.Stepto(-1970,-28245,-2588);
	gcall.Stepto(-2099,-28455,-2610);
	gcall.Stepto(-2273,-28629,-2624);
	gcall.Stepto(-2491,-28741,-2622);
	gcall.Stepto(-2728,-28680,-2605);
	gcall.Stepto(-2935,-28549,-2576);
	gcall.Stepto(-3145,-28415,-2553);
	gcall.Stepto(-3352,-28277,-2543);
	gcall.Stepto(-3546,-28124,-2535);
	gcall.Stepto(-3736,-27962,-2518);
	gcall.Stepto(-3886,-27765,-2510);
	gcall.Stepto(-4007,-27560,-2500);
	gcall.Stepto(-4139,-27338,-2484);
	gcall.Stepto(-4268,-27124,-2472);
	gcall.Stepto(-4397,-26912,-2458);
	gcall.Stepto(-4526,-26700,-2450);
	gcall.Stepto(-4641,-26483,-2454);
	gcall.Stepto(-4742,-26257,-2464);
	gcall.Stepto(-4842,-26031,-2470);
	gcall.Stepto(-4945,-25800,-2455);
	gcall.Stepto(-5046,-25574,-2428);
	gcall.Stepto(-5145,-25350,-2383);
	gcall.Stepto(-5246,-25122,-2340);
	gcall.Stepto(-5343,-24892,-2290);
	gcall.Stepto(-5393,-24649,-2232);
	gcall.Stepto(-5405,-24579,-2215);
	gcall.Stepto(-5441,-24373,-2169);
	gcall.Stepto(-5460,-24124,-2093);
	gcall.Stepto(-5478,-23877,-2058);
	gcall.Stepto(-5497,-23631,-2013);
	gcall.Stepto(-5518,-23382,-1975);
	gcall.Stepto(-5540,-23134,-1939);
	gcall.Stepto(-5564,-22886,-1912);
	gcall.Stepto(-5587,-22639,-1909);
	gcall.Stepto(-5611,-22392,-1907);
	gcall.Stepto(-5634,-22145,-1901);
	gcall.Stepto(-5657,-21904,-1892);
	gcall.Stepto(-5674,-21673,-1882);
	gcall.Stepto(-5670,-21474,-1876);
	gcall.Stepto(-5662,-21274,-1871);
	gcall.Stepto(-5648,-21074,-1870);
	gcall.Stepto(-5637,-20882,-1870);
	gcall.Stepto(-5631,-20638,-1872);
	gcall.Stepto(-5625,-20392,-1884);
	gcall.Stepto(-5620,-20143,-1884);
	gcall.Stepto(-5613,-19899,-1884);
	gcall.Stepto(-5596,-19646,-1888);
	gcall.Stepto(-5557,-19401,-1894);
	gcall.Stepto(-5502,-19157,-1889);
	gcall.Stepto(-5447,-18917,-1885);
	gcall.Stepto(-5309,-18709,-1876);
	gcall.Stepto(-5167,-18505,-1834);
	gcall.Stepto(-5030,-18308,-1782);
	gcall.Stepto(-4869,-18110,-1739);
	gcall.Stepto(-4712,-17939,-1705);
	gcall.Stepto(-4539,-17759,-1676);
	gcall.Stepto(-4361,-17580,-1684);
	gcall.Stepto(-4186,-17407,-1731);
	gcall.Stepto(-4010,-17233,-1748);
	gcall.Stepto(-3840,-17063,-1746);
	gcall.Stepto(-3656,-16881,-1698);
	gcall.Stepto(-3478,-16705,-1621);
	gcall.Stepto(-3301,-16536,-1589);
	gcall.Stepto(-3090,-16400,-1563);
	gcall.Stepto(-2875,-16277,-1552);
	gcall.Stepto(-2660,-16156,-1538);
	gcall.Stepto(-2449,-16040,-1523);
	gcall.Stepto(-2218,-15921,-1494);
	gcall.Stepto(-2005,-15814,-1437);
	gcall.Stepto(-1778,-15708,-1385);
	gcall.Stepto(-1540,-15609,-1326);
	gcall.NewSpend(1);
	gcall.Stepto(-1423,-15563,-1310);
	Sleep(2000);
}

void TaskScript::lianji10()
{
	//副本里是A2C 外是89B
	//死亡

	if (gcall.GetPlayerDeadStatus() == 1 ||
		gcall.GetPlayerDeadStatus() == 2)
	{
		Sleep(5000);
		gcall.FuHuo();
		Sleep(3000);
		gcall.Stepto(-224,-14788,-1166);
		gcall.Stepto(-606,-15197,-1254);
		gcall.Stepto(-977,-15424,-1296);
		gcall.Stepto(-1555,-15642,-1332);
		gcall.Stepto(-1423,-15563,-1310);
	}

	//修理

	_BAGSTU stu;
	gcall.GetGoodsByEquipPos(EQUITMENT_POS::WUQI, &stu);
	if (stu.m_Lasting < 10)
	{
		BOOL flagrs = gcall.Stepto(5864,-10502,-3265,10,20,1500);
		if (flagrs)
		{
			//Sleep(1000);
			//gcall.Shunyi(L"Lianji10-end");
			//Sleep(1000);
			//gcall.sendcall(id_msg_OverShunyi,(LPVOID)1);//hook
			//Sleep(3000);
			ShunYiResult(0x89b,L"Lianji10-end",TRUE);
			Sleep(1000);
			gcall.Shunyi(L"Lianji10-mai-men");
			Sleep(3000);
			gcall.sendcall(id_msg_OverShunyi,(LPVOID)0);//hook
			Sleep(3000);
			gcall.WaitPlans();
			gcall.HeChengWuQi(EQUITMENT_POS::WUQI);
			Sleep(1000);
			gcall.FenJieByConfig();
		}

		gcall.Stepto(-1499,-15595,-1314);
		gcall.Stepto(-1617,-15671,-1346);
		gcall.Stepto(-1829,-15806,-1405);
		gcall.Stepto(-2034,-15936,-1451);
		gcall.Stepto(-2240,-16071,-1488);
		gcall.Stepto(-2451,-16205,-1506);
		gcall.Stepto(-2485,-16225,-1510);
		gcall.Stepto(-2524,-16248,-1513);
		gcall.Stepto(-2531,-16253,-1514);
		Sleep(2000);
		gcall.FixWuqi();
		Sleep(2000);
		gcall.Stepto(-2531,-16253,-1514);
		gcall.Stepto(-2391,-16147,-1503);
		gcall.Stepto(-2196,-16000,-1484);
		gcall.Stepto(-1990,-15862,-1438);
		gcall.Stepto(-1772,-15735,-1386);
		gcall.Stepto(-1554,-15616,-1329);
		gcall.Stepto(-1423,-15563,-1310);
		Sleep(2000);
	}

	//卖

	if (gcall.GetBagGridNumberLast() < 5)
	{
		BOOL flagrs = gcall.Stepto(5864,-10502,-3265,10,20,1500);
		if (flagrs)
		{
			//Sleep(1000);
			//gcall.Shunyi(L"Lianji10-end");
			//Sleep(1000);
			//gcall.sendcall(id_msg_OverShunyi,(LPVOID)1);//hook
			//Sleep(3000);
			ShunYiResult(0x89b,L"Lianji10-end",TRUE);
			Sleep(1000);
			gcall.Shunyi(L"Lianji10-mai-men");
			Sleep(3000);
			gcall.sendcall(id_msg_OverShunyi,(LPVOID)0);//hook
			Sleep(3000);
			gcall.WaitPlans();
			gcall.HeChengWuQi(EQUITMENT_POS::WUQI);
			Sleep(1000);
			gcall.FenJieByConfig();
		}
		gcall.Stepto(-1478,-15579,-1312);
		gcall.Stepto(-1511,-15594,-1317);
		gcall.NewSpend(2.5);
		gcall.Stepto(-1740,-15693,-1375);
		gcall.Stepto(-1978,-15770,-1427);
		gcall.Stepto(-2218,-15806,-1501);
		gcall.Stepto(-2459,-15838,-1563);
		gcall.Stepto(-2705,-15842,-1610);
		gcall.Stepto(-2959,-15836,-1637);
		gcall.Stepto(-3211,-15831,-1657);
		gcall.Stepto(-3456,-15826,-1666);
		gcall.Stepto(-3701,-15820,-1672);
		gcall.Stepto(-3951,-15780,-1696);
		gcall.Stepto(-4186,-15708,-1698);
		gcall.Stepto(-4424,-15634,-1687);
		gcall.Stepto(-4662,-15561,-1669);
		gcall.Stepto(-4898,-15494,-1657);
		gcall.Stepto(-5140,-15430,-1655);
		gcall.Stepto(-5372,-15371,-1671);
		gcall.Stepto(-5621,-15308,-1694);
		gcall.Stepto(-5863,-15247,-1715);
		gcall.Stepto(-6100,-15188,-1721);
		gcall.Stepto(-6343,-15127,-1717);
		gcall.Stepto(-6578,-15049,-1719);
		gcall.Stepto(-6802,-14946,-1722);
		gcall.Stepto(-7007,-14808,-1721);
		gcall.Stepto(-7130,-14710,-1719);
		gcall.Stepto(-7165,-14626,-1714);
		gcall.Stepto(-7211,-14406,-1703);
		gcall.Stepto(-7167,-14389,-1703);
		gcall.Stepto(-7165,-14388,-1703);
		gcall.NewSpend(1);
		Sleep(2000);
		gcall.SellItemByConfig(L"이진상");
		Sleep(2000);
		gcall.Stepto(-7165,-14388,-1703);
		gcall.NewSpend(2.5);
		gcall.Stepto(-7164,-14392,-1703);
		gcall.Stepto(-7108,-14640,-1713);
		gcall.Stepto(-7030,-14873,-1725);
		gcall.Stepto(-6816,-14989,-1725);
		gcall.Stepto(-6580,-15035,-1718);
		gcall.Stepto(-6329,-15074,-1715);
		gcall.Stepto(-6082,-15113,-1714);
		gcall.Stepto(-5851,-15150,-1703);
		gcall.Stepto(-5595,-15190,-1682);
		gcall.Stepto(-5353,-15228,-1659);
		gcall.Stepto(-5113,-15266,-1642);
		gcall.Stepto(-4861,-15305,-1640);
		gcall.Stepto(-4624,-15343,-1645);
		gcall.Stepto(-4373,-15382,-1656);
		gcall.Stepto(-4127,-15421,-1664);
		gcall.Stepto(-3891,-15458,-1672);
		gcall.Stepto(-3647,-15496,-1669);
		gcall.Stepto(-3395,-15536,-1668);
		gcall.Stepto(-3147,-15575,-1667);
		gcall.Stepto(-2905,-15613,-1649);
		gcall.Stepto(-2655,-15653,-1615);
		gcall.Stepto(-2414,-15691,-1560);
		gcall.Stepto(-2174,-15728,-1486);
		gcall.Stepto(-1926,-15750,-1416);
		gcall.Stepto(-1706,-15666,-1365);
		gcall.Stepto(-1488,-15560,-1313);
		gcall.NewSpend(1);
		gcall.Stepto(-1423,-15563,-1310);
		Sleep(2000);
	}


	BOOL flag = gcall.Stepto(5864,-10502,-3265,10,20,1500);
	if (flag == TRUE)
	{
		//Sleep(1000);
		//gcall.Shunyi(L"Lianji10-end");
		//Sleep(1000);
		//gcall.sendcall(id_msg_OverShunyi,(LPVOID)1);//hook
		//Sleep(1000);
		ShunYiResult(0x89b,L"Lianji10-end",TRUE);
		Sleep(1000);
		gcall.HeChengWuQi(EQUITMENT_POS::WUQI);
		Sleep(1000);
		gcall.BuqiBaGua(L"충각 치명보패");
		Sleep(1000);
		gcall.FenJieByConfig();
		Sleep(2000);
		//gcall.Shunyi(L"Lianji10-go");
		//Sleep(1000);
		//gcall.sendcall(id_msg_OverShunyi,(LPVOID)1);//hook
		//Sleep(2000);
		ShunYiResult(0xa2c,L"Lianji10-go",TRUE);
		Sleep(1000);
		gcall.Shunyi(L"Lianji10");
		Sleep(1000);
		gcall.sendcall(id_msg_OverShunyi,(LPVOID)0);//hook
	}else
	{
		while (1)
		{
			gcall.Stepto(-1423,-15563,-1310);
			BOOL flag = ShunYiResult(0xa2c,L"Lianji10-go",FALSE);
			if (flag)
			{
				Sleep(3000);
				break;
			}
		}
		//gcall.Stepto(-1423,-15563,-1310);
		//Sleep(1000);
		//gcall.Shunyi(L"Lianji10-go");
		//Sleep(1000);
		//gcall.sendcall(id_msg_OverShunyi,(LPVOID)0);//hook
		//Sleep(2000);
		gcall.Shunyi(L"Lianji10");
		Sleep(1000);
		gcall.sendcall(id_msg_OverShunyi,(LPVOID)0);//hook
	}
	
	


	Sleep(2000);
	gcall.Stepto(4288,-11479,-3287);
	gcall.Stepto(4512,-11399,-3278);
	gcall.Stepto(4665,-11202,-3276);
	gcall.Stepto(4780,-10985,-3281);
	gcall.Stepto(4920,-10816,-3267);
	gcall.Stepto(5055,-10671,-3265);
	gcall.Stepto(5130,-10628,-3265);
	gcall.Stepto(5330,-10630,-3268);
	gcall.Stepto(5522,-10682,-3272);
	gcall.Stepto(5710,-10745,-3268);
	gcall.Stepto(5897,-10804,-3265);
	gcall.Stepto(6096,-10828,-3264);
	gcall.Stepto(6291,-10820,-3264);
	gcall.Stepto(6380,-10658,-3263);
	gcall.Stepto(6319,-10476,-3263);
	gcall.Stepto(6150,-10375,-3267);
	gcall.Stepto(6029,-10308,-3269);
	if (gcall.FindThenKill(0, 500, modeNormal | modeAoe | modePickup) == RESULT_KILL_PLAYDEAD)
	{
		Sleep(5000);
		gcall.FuHuo();
		Sleep(3000);
		gcall.Stepto(-224,-14788,-1166);
		gcall.Stepto(-606,-15197,-1254);
		gcall.Stepto(-977,-15424,-1296);
		gcall.Stepto(-1555,-15642,-1332);
		gcall.Stepto(-1423,-15563,-1310);
	}
}

void TaskScript::lianji14_go()
{
	gcall.Stepto(-9460,-7284,601,10,20,3000,TRUE);
	gcall.Stepto(-9460,-7284,601);
	gcall.NewSpend(2.5);
	gcall.Stepto(-9372,-7065,599);
	gcall.Stepto(-9262,-6843,593);
	gcall.Stepto(-9148,-6623,573);
	gcall.Stepto(-9033,-6403,572);
	gcall.Stepto(-8908,-6189,586);
	gcall.Stepto(-8859,-5947,599);
	gcall.Stepto(-8826,-5702,604);
	gcall.Stepto(-8790,-5456,604);
	gcall.Stepto(-8740,-5213,603);
	gcall.Stepto(-8682,-4972,602);
	gcall.Stepto(-8576,-4749,602);
	gcall.Stepto(-8398,-4579,609);
	gcall.Stepto(-8172,-4479,603);
	gcall.Stepto(-7928,-4507,600);
	gcall.Stepto(-7690,-4577,601);
	gcall.Stepto(-7459,-4667,601);
	gcall.Stepto(-7225,-4754,601);
	gcall.Stepto(-6992,-4840,595);
	gcall.Stepto(-6760,-4927,578);
	gcall.Stepto(-6527,-5013,548);
	gcall.Stepto(-6295,-5099,562);
	gcall.Stepto(-6062,-5186,562);
	gcall.Stepto(-5830,-5272,569);
	gcall.Stepto(-5597,-5359,568);
	gcall.Stepto(-5365,-5445,557);
	gcall.Stepto(-5132,-5532,551);
	gcall.Stepto(-4900,-5618,559);
	gcall.Stepto(-4668,-5704,565);
	gcall.Stepto(-4435,-5791,563);
	gcall.Stepto(-4205,-5884,550);
	gcall.Stepto(-3980,-5989,568);
	gcall.NewSpend(1);
	gcall.Stepto(-3852,-5988,585);
	gcall.Stepto(-3689,-6084,615);
	gcall.Stepto(-3385,-6251,623);
	Sleep(4000);

	
}

void TaskScript::lianji14()
{
	//副本里A3C 副本外89B
	//死亡

	if (gcall.GetPlayerDeadStatus() == 1 ||
		gcall.GetPlayerDeadStatus() == 2)
	{
		Sleep(5000);
		gcall.FuHuo();
		Sleep(3000);
		gcall.Stepto(-3207,-6410,599);
		gcall.Stepto(-3615,-6159,621);
		gcall.Stepto(-3385,-6251,623);
	}

	//修理

	_BAGSTU stu;
	gcall.GetGoodsByEquipPos(EQUITMENT_POS::WUQI, &stu);
	if (stu.m_Lasting < 10)
	{
		BOOL flagrs = gcall.Stepto(1417,-5129,13,10,20,1500);
		if (flagrs)
		{
			//Sleep(1000);
			//gcall.Shunyi(L"Lianji14-end");
			//Sleep(1000);
			//gcall.sendcall(id_msg_OverShunyi,(LPVOID)1);//hook
			ShunYiResult(0x89b,L"Lianji14-end",TRUE);
			Sleep(1000);
			gcall.Shunyi(L"Lianji14-mai-men");
			Sleep(1000);
			gcall.sendcall(id_msg_OverShunyi,(LPVOID)0);//hook
			Sleep(5000);
			gcall.WaitPlans();
			gcall.HeChengWuQi(EQUITMENT_POS::WUQI);
			Sleep(1000);
			gcall.FenJieByConfig();
		}
		Sleep(2000);
		gcall.Stepto(-3417,-6255,624);
		gcall.Stepto(-3630,-6155,621);
		gcall.Stepto(-3855,-6051,594);
		gcall.Stepto(-4091,-6039,566);
		gcall.Stepto(-4325,-6139,562);
		Sleep(2000);
		gcall.FixWuqi();
		Sleep(2000);
		gcall.Stepto(-4091,-6039,566);
		gcall.Stepto(-3855,-6051,594);
		gcall.Stepto(-3630,-6155,621);
		gcall.Stepto(-3417,-6255,624);
		gcall.Stepto(-3385,-6251,623);
		Sleep(2000);
	}

	//卖

	if (gcall.GetBagGridNumberLast() < 5)
	{
		BOOL flagrs = gcall.Stepto(1417,-5129,13,10,20,1500);
		if (flagrs)
		{
			//Sleep(1000);
			//gcall.Shunyi(L"Lianji14-end");
			//Sleep(1000);
			//gcall.sendcall(id_msg_OverShunyi,(LPVOID)1);//hook
			//Sleep(1000);
			ShunYiResult(0x89b,L"Lianji14-end",TRUE);
			Sleep(1000);
			gcall.Shunyi(L"Lianji14-mai-men");
			Sleep(1000);
			gcall.sendcall(id_msg_OverShunyi,(LPVOID)0);//hook
			Sleep(5000);
			gcall.WaitPlans();
			gcall.HeChengWuQi(EQUITMENT_POS::WUQI);
			Sleep(1000);
			gcall.FenJieByConfig();
		}
		gcall.Stepto(-3538,-6191,626);
		gcall.Stepto(-3661,-6108,617);
		gcall.NewSpend(2.5);
		gcall.Stepto(-3867,-5970,579);
		gcall.Stepto(-4073,-5831,545);
		gcall.Stepto(-4280,-5692,548);
		gcall.Stepto(-4485,-5554,546);
		gcall.Stepto(-4691,-5415,545);
		gcall.Stepto(-4895,-5277,548);
		gcall.Stepto(-5102,-5138,548);
		gcall.Stepto(-5307,-5000,549);
		gcall.Stepto(-5537,-4909,555);
		gcall.Stepto(-5775,-4835,570);
		gcall.Stepto(-6011,-4762,572);
		gcall.Stepto(-6248,-4689,559);
		gcall.Stepto(-6484,-4616,542);
		gcall.Stepto(-6722,-4542,556);
		gcall.Stepto(-6959,-4469,563);
		gcall.Stepto(-7197,-4397,595);
		gcall.Stepto(-7435,-4326,600);
		gcall.Stepto(-7671,-4255,601);
		gcall.Stepto(-7910,-4184,601);
		gcall.Stepto(-8049,-4142,602);
		gcall.Stepto(-8449,-4023,599);
		gcall.Stepto(-8864,-3899,590);
		gcall.Stepto(-9122,-3817,602);
		gcall.Stepto(-9346,-3737,602);
		gcall.Stepto(-9572,-3633,602);
		gcall.Stepto(-9586,-3626,602);
		gcall.NewSpend(1);
		gcall.Stepto(-9592,-3448,601);
		Sleep(2000);
		gcall.SellItemByConfig(L"이쇠돌");
		Sleep(2000);
		gcall.Stepto(-9592,-3448,601);
		gcall.Stepto(-9586,-3626,602);
		gcall.NewSpend(2.5);
		gcall.Stepto(-9488,-3748,602);
		gcall.Stepto(-9311,-3924,602);
		gcall.Stepto(-9271,-3960,602);
		gcall.Stepto(-8850,-3895,589);
		gcall.Stepto(-8807,-3825,587);
		gcall.Stepto(-8625,-3669,570);
		gcall.Stepto(-8479,-3656,566);
		gcall.Stepto(-8066,-3763,599);
		gcall.Stepto(-7658,-3914,596);
		gcall.Stepto(-7265,-4097,587);
		gcall.Stepto(-6871,-4280,559);
		gcall.Stepto(-6477,-4464,544);
		gcall.Stepto(-6089,-4657,571);
		gcall.Stepto(-5712,-4872,566);
		gcall.Stepto(-5344,-5095,551);
		gcall.Stepto(-4970,-5317,549);
		gcall.Stepto(-4842,-5393,548);
		gcall.Stepto(-4661,-5501,547);
		gcall.NewSpend(1);
		gcall.Stepto(-4290,-5725,550);
		gcall.Stepto(-3919,-5948,564);
		gcall.Stepto(-3547,-6172,626);
		gcall.Stepto(-3385,-6251,623);
		Sleep(2000);
	}


	BOOL flag = gcall.Stepto(1417,-5129,13,10,20,1500);
	if (flag == TRUE)
	{
		//Sleep(1000);
		//gcall.Shunyi(L"Lianji14-end");
		//Sleep(1000);
		//gcall.sendcall(id_msg_OverShunyi,(LPVOID)1);//hook
		//Sleep(1000);
		ShunYiResult(0x89b,L"Lianji14-end",TRUE);
		Sleep(1000);
		gcall.HeChengWuQi(EQUITMENT_POS::WUQI);
		Sleep(1000);
		//gcall.BuqiBaGua(L"충각 치명보패");
		//Sleep(1000);
		gcall.FenJieByConfig();
		Sleep(2000);
		//gcall.Shunyi(L"Lianji14-go");
		//Sleep(1000);
		//gcall.sendcall(id_msg_OverShunyi,(LPVOID)1);//hook
		//Sleep(2000);
		ShunYiResult(0xa3c,L"Lianji14-go",TRUE);
		gcall.Shunyi(L"Lianji14");
		Sleep(1000);
		gcall.sendcall(id_msg_OverShunyi,(LPVOID)0);//hook
	}else
	{
		while (1)
		{
			gcall.Stepto(-3385,-6251,623);

			BOOL flag = ShunYiResult(0xa3c,L"Lianji14-go",FALSE);
			if (flag)
			{
				Sleep(3000);
				break;
			}
		}
		
		//Sleep(1000);
		//gcall.Shunyi(L"Lianji14-go");
		//Sleep(1000);
		//gcall.sendcall(id_msg_OverShunyi,(LPVOID)0);//unhook
		//Sleep(2000);
		gcall.Shunyi(L"Lianji14");
		Sleep(1000);
		gcall.sendcall(id_msg_OverShunyi,(LPVOID)0);//unhook
	}




	Sleep(2000);
	gcall.Stepto(-575,-5134,24);
	gcall.Stepto(-447,-4937,25);
	gcall.Stepto(-257,-4778,19);
	gcall.Stepto(-35,-4677,30);
	gcall.Stepto(210,-4651,28);
	gcall.Stepto(447,-4717,22);
	gcall.Stepto(675,-4816,18);
	gcall.Stepto(902,-4918,20);
	gcall.Stepto(1126,-5024,12);
	gcall.Stepto(1349,-5131,13);
	gcall.Stepto(1569,-5246,13);
	gcall.sendcall(id_msg_attack, (LPVOID)0x5dca);//tab
	gcall.Stepto(1680,-5304,10);
	gcall.Kill_Tab();
	gcall.Kill_Tab();
	gcall.TurnToNear(500);
	Sleep(500);
	gcall.sendcall(id_msg_attack, (LPVOID)0x5e74);//1
	Sleep(1000);
	if (gcall.FindThenKill(0, 500, modeNormal | modeAoe | modePickup) == RESULT_KILL_PLAYDEAD)
	{
		Sleep(5000);
		gcall.FuHuo();
		Sleep(3000);
		gcall.Stepto(-3207,-6410,599);
		gcall.Stepto(-3615,-6159,621);
		gcall.Stepto(-3385,-6251,623);
	}
}

void TaskScript::lianji18_go()
{
	gcall.NewSpend(2.5);
	gcall.Stepto(55050,-14769,-247,10,20,3000,TRUE);
	gcall.Stepto(55115,-14848,-247);
	gcall.Stepto(55165,-14908,-243);
	gcall.Stepto(55317,-15050,-273);
	gcall.Stepto(55517,-15209,-290);
	gcall.Stepto(55721,-15343,-303);
	gcall.Stepto(55935,-15476,-322);
	gcall.Stepto(56153,-15597,-339);
	gcall.Stepto(56368,-15717,-344);
	gcall.Stepto(56587,-15839,-339);
	gcall.Stepto(56787,-15950,-332);
	gcall.Stepto(56998,-16078,-321);
	gcall.Stepto(57141,-16281,-308);
	gcall.Stepto(57225,-16514,-304);
	gcall.Stepto(57285,-16753,-310);
	gcall.Stepto(57265,-17001,-309);
	gcall.Stepto(57203,-17238,-313);
	gcall.Stepto(57017,-17402,-331);
	gcall.Stepto(56789,-17499,-342);
	gcall.Stepto(56557,-17579,-348);
	gcall.Stepto(56318,-17640,-348);
	gcall.Stepto(56078,-17701,-341);
	gcall.Stepto(55833,-17748,-341);
	gcall.Stepto(55587,-17786,-378);
	gcall.Stepto(55341,-17824,-475);
	gcall.Stepto(55101,-17886,-612);
	gcall.Stepto(54945,-18055,-629);
	gcall.Stepto(54896,-18300,-612);
	gcall.Stepto(54856,-18544,-607);
	gcall.Stepto(54818,-18790,-607);
	gcall.Stepto(54780,-19034,-609);
	gcall.Stepto(54741,-19274,-609);
	gcall.Stepto(54694,-19524,-609);
	gcall.Stepto(54614,-19756,-609);
	gcall.Stepto(54496,-19974,-609);
	gcall.Stepto(54372,-20189,-607);
	gcall.Stepto(54319,-20276,-607);
	gcall.Stepto(54478,-20195,-607);
	gcall.Stepto(54565,-19469,-609);
	gcall.Stepto(54565,-19468,-609);
	gcall.Stepto(54579,-19242,-609);
	gcall.Stepto(54573,-19005,-609);
	gcall.Stepto(54567,-18757,-610);
	gcall.NewSpend(1);
	gcall.Stepto(54561,-18509,-618);
	gcall.Stepto(54556,-18261,-629);
	gcall.Stepto(54516,-18034,-639);
	gcall.Stepto(54277,-17966,-650);
	gcall.Stepto(54029,-17969,-619);
	gcall.Stepto(53810,-17971,-619);
	Sleep(2000);
	gcall.Stepto(53600,-17970,-619);
	gcall.WaitPlans();
	gcall.Stepto(53339,-17967,-715);
	gcall.NewSpend(2.5);
	gcall.Stepto(53091,-17964,-833);
	gcall.Stepto(52843,-17964,-943);
	gcall.Stepto(52595,-17965,-1053);
	gcall.Stepto(52347,-17965,-1163);
	gcall.Stepto(52099,-17965,-1273);
	gcall.Stepto(51851,-17966,-1383);
	gcall.Stepto(51603,-17966,-1438);
	gcall.Stepto(51355,-17967,-1433);
	gcall.Stepto(51107,-17967,-1433);
	gcall.Stepto(50859,-17967,-1494);
	gcall.Stepto(50611,-17968,-1542);
	gcall.Stepto(50363,-17968,-1586);
	gcall.Stepto(50114,-17968,-1625);
	gcall.Stepto(49866,-17969,-1654);
	gcall.Stepto(49618,-17969,-1670);
	gcall.Stepto(49370,-17969,-1679);
	gcall.Stepto(49122,-17970,-1682);
	gcall.Stepto(48875,-17974,-1681);
	gcall.Stepto(48640,-18049,-1678);
	gcall.Stepto(48413,-18149,-1680);
	gcall.Stepto(48200,-18276,-1699);
	gcall.Stepto(47988,-18405,-1725);
	gcall.Stepto(47779,-18539,-1745);
	gcall.Stepto(47579,-18685,-1762);
	gcall.Stepto(47378,-18831,-1777);
	gcall.Stepto(47177,-18976,-1785);
	gcall.Stepto(46967,-19108,-1782);
	gcall.Stepto(46737,-19200,-1778);
	gcall.Stepto(46494,-19250,-1775);
	gcall.Stepto(46249,-19285,-1775);
	gcall.Stepto(46001,-19302,-1781);
	gcall.Stepto(45754,-19309,-1789);
	gcall.Stepto(45504,-19306,-1806);
	gcall.Stepto(45256,-19302,-1835);
	gcall.Stepto(45008,-19299,-1859);
	gcall.Stepto(44760,-19296,-1895);
	gcall.Stepto(44512,-19293,-1944);
	gcall.Stepto(44264,-19289,-1995);
	gcall.Stepto(44018,-19315,-2050);
	gcall.Stepto(43776,-19368,-2111);
	gcall.Stepto(43534,-19423,-2180);
	gcall.Stepto(43292,-19478,-2247);
	gcall.Stepto(43051,-19538,-2311);
	gcall.Stepto(42813,-19608,-2380);
	gcall.Stepto(42575,-19677,-2451);
	gcall.Stepto(42337,-19747,-2519);
	gcall.Stepto(42099,-19817,-2577);
	gcall.Stepto(41861,-19886,-2628);
	gcall.Stepto(41643,-20002,-2678);
	gcall.Stepto(41453,-20167,-2729);
	gcall.Stepto(41269,-20333,-2776);
	gcall.Stepto(41094,-20509,-2808);
	gcall.Stepto(40930,-20695,-2819);
	gcall.Stepto(40781,-20893,-2829);
	gcall.Stepto(40653,-21105,-2846);
	gcall.Stepto(40532,-21326,-2886);
	gcall.Stepto(40413,-21544,-2944);
	gcall.Stepto(40295,-21762,-2975);
	gcall.Stepto(40165,-21974,-2991);
	gcall.Stepto(40010,-22167,-3019);
	gcall.Stepto(39847,-22354,-3061);
	gcall.Stepto(39672,-22533,-3095);
	gcall.Stepto(39480,-22690,-3103);
	gcall.Stepto(39276,-22831,-3106);
	gcall.Stepto(39054,-22941,-3113);
	gcall.Stepto(38824,-23033,-3125);
	gcall.Stepto(38593,-23123,-3140);
	gcall.Stepto(38356,-23197,-3146);
	gcall.Stepto(38110,-23233,-3148);
	gcall.Stepto(37863,-23256,-3148);
	gcall.Stepto(37616,-23278,-3126);
	gcall.Stepto(37369,-23301,-3114);
	gcall.Stepto(37121,-23314,-3122);
	gcall.Stepto(36873,-23309,-3131);
	gcall.NewSpend(1);
	gcall.Stepto(36625,-23301,-3140);
	gcall.Stepto(36392,-23243,-3143);
	gcall.Stepto(36230,-23058,-3116);
	gcall.Stepto(36160,-22821,-3069);
	gcall.Stepto(36072,-22589,-3028);
	gcall.Stepto(36009,-22349,-3000);
	gcall.Stepto(35946,-21921,-2991);
	Sleep(2000);
}

void TaskScript::lianji18()
{
	//副本里2615 副本外2440
	//死亡

	if (gcall.GetPlayerDeadStatus() == 1 ||
		gcall.GetPlayerDeadStatus() == 2)
	{
		Sleep(5000);
		gcall.FuHuo();
		Sleep(3000);
		gcall.Stepto(35822,-21520,-3047,10,20,3000);
		gcall.Stepto(35883,-21732,-2995,10,20,3000);
		gcall.Stepto(35955,-22018,-2991);
		gcall.Stepto(36000,-22208,-2994);
		gcall.Stepto(35946,-21921,-2991);
	}

	//修理

	_BAGSTU stu;
	gcall.GetGoodsByEquipPos(EQUITMENT_POS::WUQI, &stu);
	if (stu.m_Lasting < 10)
	{
		gcall.CityConvey(0x8);
		gcall.NewSpend(2.5);
		gcall.Stepto(57680,-16824,-295);
		gcall.Stepto(57473,-16939,-295);
		gcall.Stepto(57256,-17060,-309);
		gcall.Stepto(57040,-17181,-327);
		gcall.Stepto(56823,-17302,-338);
		gcall.Stepto(56606,-17423,-344);
		gcall.Stepto(56390,-17544,-354);
		gcall.Stepto(56168,-17654,-341);
		gcall.Stepto(55927,-17712,-341);
		gcall.Stepto(55682,-17751,-378);
		gcall.Stepto(55438,-17791,-418);
		gcall.Stepto(55193,-17831,-557);
		gcall.Stepto(54948,-17871,-635);
		gcall.Stepto(54866,-18108,-625);
		gcall.Stepto(54814,-18350,-613);
		gcall.Stepto(54763,-18593,-608);
		gcall.Stepto(54711,-18835,-608);
		gcall.Stepto(54631,-19070,-609);
		gcall.Stepto(54520,-19291,-609);
		gcall.NewSpend(1);
		gcall.Stepto(54402,-19509,-609);
		gcall.Stepto(54287,-19729,-611);
		Sleep(2000);
		gcall.FixWuqi();
		Sleep(2000);
		lianji18_go();
	}

	//卖

	if (gcall.GetBagGridNumberLast() < 5)
	{
		gcall.CityConvey(0x8);
		gcall.NewSpend(2.5);
		gcall.Stepto(57680,-16824,-295);
		gcall.Stepto(57473,-16939,-295);
		gcall.Stepto(57256,-17060,-309);
		gcall.Stepto(57040,-17181,-327);
		gcall.Stepto(56823,-17302,-338);
		gcall.Stepto(56606,-17423,-344);
		gcall.Stepto(56390,-17544,-354);
		gcall.Stepto(56168,-17654,-341);
		gcall.Stepto(55927,-17712,-341);
		gcall.Stepto(55682,-17751,-378);
		gcall.Stepto(55438,-17791,-418);
		gcall.Stepto(55193,-17831,-557);
		gcall.Stepto(54948,-17871,-635);
		gcall.Stepto(54866,-18108,-625);
		gcall.Stepto(54814,-18350,-613);
		gcall.Stepto(54763,-18593,-608);
		gcall.Stepto(54711,-18835,-608);
		gcall.Stepto(54631,-19070,-609);
		gcall.Stepto(54520,-19291,-609);
		gcall.Stepto(54402,-19509,-609);
		gcall.Stepto(54287,-19729,-611);
		gcall.NewSpend(1);
		gcall.Stepto(54214,-19968,-612);
		gcall.Stepto(54191,-20170,-608);
		Sleep(2000);
		gcall.SellItemByConfig(L"이무기");
		Sleep(2000);
		lianji18_go();
	}


	BOOL flag = gcall.Stepto(35353,-17880,-3548,10,20,1500);
	if (flag == TRUE)
	{
		ShunYiResult(2440,L"Lianji18-end",TRUE);
		Sleep(1000);
		gcall.HeChengWuQi(EQUITMENT_POS::WUQI);
		Sleep(1000);
		gcall.FenJieByConfig();
		Sleep(2000);
		ShunYiResult(2615,L"Lianji18-go",TRUE);
		gcall.Shunyi(L"Lianji18");
		Sleep(1000);
		gcall.sendcall(id_msg_OverShunyi,(LPVOID)0);//hook
	}else
	{
		while (1)
		{
			BOOL flag = ShunYiResult(2615,L"Lianji18-go",FALSE);
			Sleep(1000);
			if (flag)
			{
				break;
			}else
			{
				gcall.Stepto(35946,-21921,-2991);
			}
		}
		Sleep(1000);
		gcall.Shunyi(L"Lianji18");
		Sleep(1000);
		gcall.sendcall(id_msg_OverShunyi,(LPVOID)0);//unhook
	}




	Sleep(2000);
	gcall.Stepto(35320,-18444,-3555);
	gcall.Stepto(35708,-18039,-3547,10,20,3000,TRUE);
	gcall.Stepto(36129,-17609,-3543);
	gcall.Stepto(35945,-17380,-3542);
	gcall.Stepto(35622,-16938,-3548,10,20,3000,TRUE);
	gcall.Stepto(35200,-17289,-3536);
	gcall.Stepto(35437,-17731,-3549);
	gcall.Stepto(35536,-17750,-3545);

	gcall.Kill_Tab();
	gcall.Kill_Tab();
	gcall.Kill_Tab();
	gcall.TurnToNear(500);
	Sleep(300);
	gcall.sendcall(id_msg_attack, (LPVOID)0x5e74);//1
	Sleep(500);
	if (gcall.FindThenKill(0, 500, modeNormal | modeAoe | modePickup) == RESULT_KILL_PLAYDEAD)
	{
		Sleep(5000);
		gcall.FuHuo();
		Sleep(3000);
		gcall.Stepto(35822,-21520,-3047,10,20,3000);
		gcall.Stepto(35883,-21732,-2995,10,20,3000);
		gcall.Stepto(35955,-22018,-2991);
		gcall.Stepto(36000,-22208,-2994);
		gcall.Stepto(35946,-21921,-2991);
	}
}

void TaskScript::lianji22_go()
{
	gcall.NewSpend(2.5);
	gcall.Stepto(-81243,-66572,344,20,20,3000);
	gcall.Stepto(-81242,-66572,344);
	gcall.Stepto(-81019,-66524,332);
	gcall.Stepto(-80836,-66358,312);
	gcall.Stepto(-80628,-66222,281);
	gcall.Stepto(-80421,-66086,254);
	gcall.Stepto(-80231,-65927,219);
	gcall.Stepto(-80064,-65745,168);
	gcall.Stepto(-79946,-65528,101);
	gcall.Stepto(-79842,-65303,33);
	gcall.Stepto(-79739,-65077,-40);
	gcall.Stepto(-79635,-64852,-119);
	gcall.Stepto(-79531,-64626,-172);
	gcall.Stepto(-79427,-64401,-202);
	gcall.Stepto(-79325,-64177,-227);
	gcall.Stepto(-79221,-63951,-251);
	gcall.Stepto(-79117,-63725,-266);
	gcall.Stepto(-79017,-63498,-272);
	gcall.Stepto(-78964,-63365,-272);
	gcall.Stepto(-79155,-63386,-290);
	gcall.Stepto(-79403,-63399,-369);
	gcall.Stepto(-79652,-63410,-482);
	gcall.Stepto(-79898,-63438,-571);
	gcall.Stepto(-80139,-63497,-650);
	gcall.Stepto(-80378,-63563,-712);
	gcall.Stepto(-80585,-63695,-756);
	gcall.Stepto(-80769,-63861,-790);
	gcall.Stepto(-80962,-64015,-853);
	gcall.Stepto(-81170,-64149,-949);
	gcall.Stepto(-81398,-64247,-1025);
	gcall.Stepto(-81644,-64249,-1077);
	gcall.Stepto(-81892,-64246,-1114);
	gcall.Stepto(-82141,-64240,-1165);
	gcall.Stepto(-82374,-64159,-1205);
	gcall.Stepto(-82525,-63969,-1267);
	gcall.Stepto(-82660,-63758,-1309);
	gcall.Stepto(-82763,-63530,-1344);
	gcall.Stepto(-82817,-63291,-1378);
	gcall.Stepto(-82865,-63048,-1428);
	gcall.Stepto(-82911,-62804,-1474);
	gcall.Stepto(-82928,-62558,-1509);
	gcall.Stepto(-82798,-62359,-1529);
	gcall.Stepto(-82580,-62244,-1505);
	gcall.Stepto(-82354,-62142,-1465);
	gcall.Stepto(-82120,-62060,-1456);
	gcall.Stepto(-81875,-62034,-1463);
	gcall.Stepto(-81627,-62031,-1462);
	gcall.Stepto(-81379,-62028,-1456);
	gcall.Stepto(-81131,-62025,-1445);
	gcall.Stepto(-80883,-62021,-1433);
	gcall.Stepto(-80634,-62018,-1415);
	gcall.Stepto(-80386,-62015,-1389);
	gcall.Stepto(-80138,-62012,-1372);
	gcall.Stepto(-79887,-61998,-1340);
	gcall.Stepto(-79641,-61973,-1277);
	gcall.Stepto(-79398,-61946,-1213);
	gcall.Stepto(-79151,-61918,-1169);
	gcall.Stepto(-78902,-61889,-1152);
	gcall.Stepto(-78654,-61861,-1151);
	gcall.Stepto(-78409,-61834,-1144);
	gcall.Stepto(-78160,-61806,-1131);
	gcall.Stepto(-77914,-61778,-1108);
	gcall.Stepto(-77667,-61755,-1082);
	gcall.Stepto(-77418,-61769,-1045);
	gcall.Stepto(-77172,-61797,-996);
	gcall.Stepto(-76928,-61839,-937);
	gcall.Stepto(-76684,-61883,-894);
	gcall.Stepto(-76441,-61928,-863);
	gcall.Stepto(-76199,-61994,-839);
	gcall.Stepto(-75967,-62088,-825);
	gcall.Stepto(-75755,-62211,-818);
	gcall.Stepto(-75547,-62348,-818);
	gcall.Stepto(-75351,-62500,-817);
	gcall.Stepto(-75224,-62711,-813);
	gcall.Stepto(-75160,-62950,-801);
	gcall.Stepto(-75096,-63194,-785);
	gcall.Stepto(-75024,-63432,-785);
	gcall.Stepto(-74940,-63665,-794);
	gcall.Stepto(-74877,-63904,-849);
	gcall.Stepto(-74867,-64150,-910);
	gcall.NewSpend(1);
	gcall.Stepto(-74882,-64401,-952);
	gcall.Stepto(-74901,-64637,-979);
	Sleep(2000);
}

void TaskScript::lianji22()
{
	//副本里3060 副本外3000
	//死亡

	if (gcall.GetPlayerDeadStatus() == 1 ||
		gcall.GetPlayerDeadStatus() == 2)
	{
		Sleep(5000);
		gcall.FuHuo();
		Sleep(3000);
		gcall.Stepto(-74888,-65116,-1123);
		gcall.Stepto(-74887,-64879,-1050);
		gcall.Stepto(-74887,-64641,-981);
		gcall.WaitPlans();
		gcall.Stepto(-74875,-64407,-952);
		gcall.Stepto(-74901,-64637,-979);
	}

	//修理

	_BAGSTU stu;
	gcall.GetGoodsByEquipPos(EQUITMENT_POS::WUQI, &stu);
	if (stu.m_Lasting < 10)
	{
		BOOL flag = gcall.Stepto(-73796,-70971,-779,10,10,3000);
		if (flag == TRUE)
		{
			ShunYiResult(3000,L"Lianji22-end",TRUE);
			gcall.Shunyi(L"Lianji22-mai-men");
			Sleep(3000);
			gcall.sendcall(id_msg_OverShunyi,(LPVOID)0);//hook
			Sleep(3000);
		}
		gcall.Stepto(-74801,-64005,-874);
		gcall.Stepto(-74868,-63775,-824);
		gcall.Stepto(-74965,-63548,-790);
		gcall.Stepto(-75080,-63327,-783);
		gcall.Stepto(-75197,-63109,-793);
		gcall.Stepto(-75317,-62892,-811);
		gcall.Stepto(-75437,-62675,-818);
		gcall.Stepto(-75505,-62578,-812);
		Sleep(1000);
		gcall.FixWuqi();
		Sleep(1000);
		gcall.Stepto(-75287,-62865,-811);
		gcall.Stepto(-75137,-63063,-785);
		gcall.Stepto(-74987,-63260,-777);
		gcall.Stepto(-74892,-63487,-788);
		gcall.Stepto(-74848,-63731,-816);
		gcall.Stepto(-74836,-63979,-867);
		gcall.Stepto(-74852,-64228,-932);
		gcall.Stepto(-74901,-64637,-979);
	}

	//卖

	if (gcall.GetBagGridNumberLast() < 5)
	{
		gcall.CityConvey(0xa);
		gcall.Stepto(-81333,-67080,380);
		gcall.Stepto(-81324,-66843,363);
		gcall.Stepto(-81305,-66596,349);
		gcall.Stepto(-81279,-66350,331);
		Sleep(2000);
		gcall.SellItemByConfig(L"초유랑");
		Sleep(2000);
		lianji22_go();
	}


	BOOL flag = gcall.Stepto(-73796,-70971,-779,10,10,3000);
	if (flag == TRUE)
	{
		while (1)
		{
			BOOL flagsy = ShunYiResult(3000,L"Lianji22-end",TRUE);
			
			if (flagsy)
			{
				break;
			}else
			{
				gcall.Stepto(-73796,-70971,-779,10,5,3000);
			}
		}
		Sleep(1000);
		gcall.FenJieByConfig();
		Sleep(1000);
		ShunYiResult(3060,L"Lianji22-go",TRUE);
		gcall.Shunyi(L"Lianji22");
		Sleep(1000);
		gcall.sendcall(id_msg_OverShunyi,(LPVOID)0);//hook
	}else
	{
		while (1)
		{
			BOOL flag = ShunYiResult(3060,L"Lianji22-go",FALSE);
			Sleep(1000);
			if (flag)
			{
				break;
			}else
			{
				gcall.Stepto(-74901,-64637,-979);
			}
		}
		Sleep(1000);
		gcall.Shunyi(L"Lianji22");
		Sleep(1000);
		gcall.sendcall(id_msg_OverShunyi,(LPVOID)0);//unhook
	}




	Sleep(2000);
	gcall.Stepto(-73647,-70509,-779,10,20,3000,TRUE);
	gcall.Stepto(-73890,-70560,-777,10,20,3000,TRUE);
	gcall.Stepto(-74073,-70667,-779,10,20,3000,TRUE);
	gcall.Stepto(-74206,-70876,-779,10,20,3000,TRUE);
	gcall.Stepto(-74338,-71086,-779,10,20,3000,TRUE);
	gcall.Stepto(-74443,-71310,-779,10,20,3000,TRUE);
	gcall.Stepto(-74502,-71516,-779,10,20,3000,TRUE);
	gcall.Stepto(-74566,-71755,-779);
	gcall.Stepto(-74405,-71930,-779);
	gcall.Stepto(-74163,-71961,-779,10,20,3000,TRUE);
	gcall.Stepto(-73947,-71840,-778);
	gcall.Stepto(-73746,-71698,-778);
	gcall.Stepto(-73695,-71457,-779);
	gcall.Stepto(-73787,-71233,-779);
	gcall.sendcall(id_msg_attack, (LPVOID)0x5E06);//3
	Sleep(1500);
	gcall.sendcall(id_msg_attack, (LPVOID)0x5DE8);//z
	/*Sleep(1000);
	gcall.Kill_Tab();
	gcall.TurnToNear(500);
	Sleep(300);
	gcall.sendcall(id_msg_attack, (LPVOID)0x5e74);//1
	*/
	if (gcall.FindThenKill(0, 500, modeNormal | modeAoe | modePickup) == RESULT_KILL_PLAYDEAD)
	{
		Sleep(5000);
		gcall.FuHuo();
		Sleep(3000);
		gcall.Stepto(-74888,-65116,-1123);
		gcall.Stepto(-74887,-64879,-1050);
		gcall.Stepto(-74887,-64641,-981);
		gcall.WaitPlans();
		gcall.Stepto(-74875,-64407,-952);
		gcall.Stepto(-74901,-64637,-979);
	}
}

void TaskScript::lianji28_go()
{
	gcall.NewSpend(2.5);
	gcall.Stepto(-5755,-59296,-1187);
	gcall.Stepto(-5638,-59178,-1192);
	gcall.Stepto(-5485,-58988,-1210);
	gcall.Stepto(-5337,-58784,-1260);
	gcall.Stepto(-5194,-58585,-1305);
	gcall.Stepto(-5046,-58380,-1340);
	gcall.Stepto(-4904,-58182,-1361);
	gcall.Stepto(-4761,-57983,-1374);
	gcall.Stepto(-4618,-57785,-1380);
	gcall.Stepto(-4479,-57592,-1384);
	gcall.Stepto(-4336,-57394,-1387);
	gcall.Stepto(-4193,-57195,-1388);
	gcall.Stepto(-4048,-56991,-1388);
	gcall.Stepto(-3902,-56784,-1385);
	gcall.Stepto(-3763,-56586,-1378);
	gcall.Stepto(-3623,-56386,-1376);
	gcall.Stepto(-3479,-56182,-1373);
	gcall.Stepto(-3368,-56024,-1373);
	gcall.Stepto(-3248,-55853,-1376);
	gcall.Stepto(-3135,-55693,-1382);
	gcall.Stepto(-3019,-55527,-1396);
	gcall.Stepto(-2906,-55367,-1419);
	gcall.Stepto(-2767,-55168,-1458);
	gcall.Stepto(-2626,-54967,-1507);
	gcall.Stepto(-2499,-54786,-1552);
	gcall.Stepto(-2339,-54559,-1608);
	gcall.Stepto(-2194,-54352,-1652);
	gcall.Stepto(-2053,-54152,-1680);
	gcall.Stepto(-1910,-53948,-1693);
	gcall.Stepto(-1769,-53747,-1694);
	gcall.Stepto(-1623,-53540,-1687);
	gcall.Stepto(-1483,-53341,-1674);
	gcall.Stepto(-1343,-53141,-1659);
	gcall.Stepto(-1206,-52946,-1643);
	gcall.Stepto(-1089,-52781,-1628);
	gcall.Stepto(-977,-52621,-1616);
	gcall.Stepto(-863,-52458,-1605);
	gcall.Stepto(-750,-52298,-1598);
	gcall.Stepto(-626,-52121,-1594);
	gcall.Stepto(-486,-51921,-1594);
	gcall.Stepto(-341,-51715,-1597);
	gcall.Stepto(-200,-51514,-1599);
	gcall.Stepto(-59,-51314,-1599);
	gcall.Stepto(86,-51107,-1600);
	gcall.Stepto(224,-50910,-1603);
	gcall.Stepto(369,-50703,-1609);
	gcall.Stepto(509,-50505,-1615);
	gcall.Stepto(650,-50304,-1623);
	gcall.Stepto(726,-50066,-1635);
	gcall.Stepto(775,-49826,-1648);
	gcall.Stepto(824,-49586,-1661);
	gcall.Stepto(875,-49339,-1675);
	gcall.Stepto(925,-49099,-1683);
	gcall.Stepto(985,-48853,-1686);
	gcall.Stepto(1044,-48616,-1684);
	gcall.Stepto(1105,-48373,-1678);
	gcall.Stepto(1165,-48136,-1668);
	gcall.Stepto(1227,-47891,-1653);
	gcall.Stepto(1287,-47654,-1635);
	gcall.Stepto(1349,-47408,-1624);
	gcall.Stepto(1409,-47171,-1625);
	gcall.Stepto(1472,-46926,-1639);
	gcall.Stepto(1532,-46689,-1663);
	gcall.Stepto(1592,-46452,-1688);
	gcall.Stepto(1652,-46215,-1714);
	gcall.Stepto(1714,-45970,-1746);
	gcall.Stepto(1774,-45733,-1779);
	gcall.Stepto(1836,-45488,-1818);
	gcall.Stepto(1897,-45248,-1860);
	gcall.Stepto(1969,-45015,-1876);
	gcall.Stepto(2107,-44804,-1884);
	gcall.Stepto(2314,-44677,-1900);
	gcall.Stepto(2542,-44569,-1919);
	gcall.Stepto(2763,-44464,-1929);
	gcall.Stepto(2992,-44356,-1934);
	gcall.Stepto(3215,-44250,-1938);
	gcall.Stepto(3436,-44145,-1944);
	gcall.Stepto(3664,-44037,-1942);
	gcall.Stepto(3885,-43932,-1939);
	gcall.Stepto(4114,-43823,-1930);
	gcall.Stepto(4328,-43705,-1921);
	gcall.Stepto(4536,-43562,-1916);
	gcall.Stepto(4728,-43424,-1915);
	gcall.Stepto(4940,-43271,-1914);
	gcall.Stepto(5136,-43125,-1915);
	gcall.Stepto(5331,-42976,-1911);
	gcall.Stepto(5528,-42817,-1880);
	gcall.Stepto(5709,-42644,-1846);
	gcall.Stepto(5884,-42473,-1832);
	gcall.Stepto(6061,-42299,-1831);
	gcall.Stepto(6242,-42122,-1858);
	gcall.Stepto(6414,-41952,-1893);
	gcall.Stepto(6594,-41775,-1934);
	gcall.Stepto(6766,-41605,-1976);
	gcall.Stepto(6943,-41430,-2015);
	gcall.Stepto(7124,-41252,-2059);
	gcall.Stepto(7298,-41080,-2109);
	gcall.Stepto(7472,-40908,-2149);
	gcall.Stepto(7653,-40730,-2184);
	gcall.Stepto(7826,-40559,-2219);
	gcall.Stepto(7981,-40363,-2250);
	gcall.Stepto(8111,-40146,-2268);
	gcall.Stepto(8231,-39933,-2279);
	gcall.Stepto(8343,-39725,-2290);
	gcall.Stepto(8462,-39491,-2307);
	gcall.Stepto(8566,-39266,-2316);
	gcall.Stepto(8666,-39034,-2322);
	gcall.Stepto(8763,-38808,-2328);
	gcall.Stepto(8872,-38783,-2330);
	gcall.Stepto(9047,-38928,-2329);
	gcall.Stepto(8967,-39157,-2329);
	gcall.Stepto(8826,-39358,-2328);
	gcall.Stepto(8686,-39558,-2322);
	gcall.Stepto(8567,-39728,-2310);
	gcall.Stepto(8427,-39928,-2296);
	gcall.Stepto(8282,-40135,-2284);
	gcall.Stepto(8141,-40336,-2271);
	gcall.Stepto(7996,-40543,-2251);
	gcall.Stepto(7856,-40743,-2220);
	gcall.Stepto(7709,-40936,-2186);
	gcall.Stepto(7553,-41105,-2152);
	gcall.Stepto(7407,-41312,-2104);
	gcall.Stepto(7300,-41530,-2052);
	gcall.Stepto(7224,-41771,-2009);
	gcall.Stepto(7151,-42005,-1964);
	gcall.Stepto(7076,-42246,-1900);
	gcall.Stepto(7031,-42486,-1802);
	gcall.Stepto(7145,-42704,-1719);
	gcall.Stepto(7348,-42836,-1685);
	gcall.Stepto(7569,-42950,-1663);
	gcall.Stepto(7763,-43099,-1642);
	gcall.Stepto(7962,-43256,-1570);
	gcall.Stepto(8174,-43379,-1475);
	gcall.Stepto(8395,-43502,-1444);
	gcall.Stepto(8613,-43613,-1468);
	gcall.Stepto(8846,-43713,-1496);
	gcall.Stepto(9071,-43808,-1518);
	gcall.Stepto(9309,-43895,-1525);
	gcall.Stepto(9540,-43977,-1518);
	gcall.Stepto(9778,-44062,-1506);
	gcall.Stepto(10009,-44145,-1490);
	gcall.Stepto(10247,-44230,-1469);
	gcall.Stepto(10477,-44312,-1441);
	gcall.Stepto(10715,-44397,-1411);
	gcall.Stepto(10946,-44479,-1388);
	gcall.Stepto(11184,-44565,-1370);
	gcall.Stepto(11422,-44650,-1364);
	gcall.Stepto(11652,-44732,-1366);
	gcall.Stepto(11891,-44817,-1372);
	gcall.Stepto(12121,-44899,-1383);
	gcall.Stepto(12358,-44984,-1398);
	gcall.Stepto(12588,-45066,-1417);
	gcall.Stepto(12827,-45151,-1445);
	gcall.Stepto(13057,-45234,-1476);
	gcall.Stepto(13295,-45319,-1507);
	gcall.Stepto(13529,-45403,-1532);
	gcall.Stepto(13767,-45488,-1539);
	gcall.Stepto(13998,-45570,-1523);
	gcall.Stepto(14232,-45654,-1492);
	gcall.Stepto(14467,-45737,-1471);
	gcall.Stepto(14705,-45823,-1491);
	gcall.Stepto(14938,-45906,-1539);
	gcall.Stepto(15168,-45988,-1587);
	gcall.Stepto(15406,-46073,-1622);
	gcall.Stepto(15637,-46155,-1635);
	gcall.Stepto(15875,-46240,-1637);
	gcall.Stepto(16113,-46326,-1638);
	gcall.Stepto(16343,-46408,-1639);
	gcall.Stepto(16582,-46493,-1633);
	gcall.Stepto(16813,-46575,-1596);
	gcall.Stepto(17051,-46661,-1523);
	gcall.Stepto(17281,-46743,-1435);
	gcall.Stepto(17514,-46841,-1347);
	gcall.Stepto(17711,-46985,-1291);
	gcall.Stepto(17900,-47126,-1261);
	gcall.Stepto(18093,-47271,-1251);
	gcall.Stepto(18250,-47388,-1258);
	gcall.Stepto(18412,-47509,-1278);
	gcall.Stepto(18569,-47627,-1308);
	gcall.Stepto(18732,-47749,-1343);
	gcall.Stepto(18910,-47883,-1368);
	gcall.Stepto(19107,-48028,-1382);
	gcall.Stepto(19317,-48169,-1389);
	gcall.Stepto(19528,-48299,-1393);
	gcall.Stepto(19743,-48420,-1403);
	gcall.Stepto(19968,-48523,-1419);
	gcall.Stepto(20209,-48602,-1439);
	gcall.Stepto(20447,-48675,-1420);
	gcall.Stepto(20682,-48747,-1417);
	gcall.Stepto(20929,-48800,-1430);
	gcall.Stepto(21181,-48823,-1453);
	gcall.Stepto(21429,-48807,-1482);
	gcall.Stepto(21659,-48745,-1509);
	gcall.Stepto(21894,-48649,-1530);
	gcall.Stepto(22120,-48536,-1548);
	gcall.Stepto(22332,-48415,-1571);
	gcall.Stepto(22551,-48288,-1602);
	gcall.Stepto(22760,-48160,-1635);
	gcall.Stepto(22969,-48033,-1650);
	gcall.Stepto(23184,-47901,-1666);
	gcall.Stepto(23400,-47769,-1679);
	gcall.Stepto(23606,-47638,-1686);
	gcall.Stepto(23811,-47488,-1687);
	gcall.Stepto(24003,-47345,-1684);
	gcall.Stepto(24179,-47168,-1677);
	gcall.Stepto(24324,-46961,-1672);
	gcall.Stepto(24431,-46741,-1658);
	gcall.Stepto(24539,-46512,-1645);
	gcall.Stepto(24648,-46284,-1634);
	gcall.Stepto(24754,-46064,-1625);
	gcall.Stepto(24904,-45860,-1609);
	gcall.Stepto(25056,-45669,-1587);
	gcall.Stepto(25230,-45497,-1567);
	gcall.Stepto(25432,-45345,-1549);
	gcall.Stepto(25645,-45210,-1526);
	gcall.Stepto(25869,-45111,-1526);
	gcall.Stepto(26094,-45016,-1549);
	gcall.Stepto(26286,-44943,-1570);
	gcall.Stepto(26475,-44871,-1584);
	gcall.Stepto(26650,-44818,-1599);
	gcall.Stepto(26854,-44759,-1613);
	gcall.Stepto(27043,-44706,-1618);
	gcall.Stepto(27275,-44613,-1619);
	gcall.Stepto(27326,-44380,-1607);
	gcall.Stepto(27326,-44135,-1593);
	gcall.Stepto(27330,-43880,-1586);
	gcall.NewSpend(1);
	gcall.Stepto(27332,-43646,-1584);
	gcall.Stepto(27333,-43490,-1587);
	gcall.Stepto(27315,-43375,-1609);
	Sleep(6000);
}

void TaskScript::lianji28()
{
	//副本里3072 副本外3010
	//死亡

	if (gcall.GetPlayerDeadStatus() == 1 ||
		gcall.GetPlayerDeadStatus() == 2)
	{
		Sleep(5000);
		gcall.FuHuo();
		Sleep(3000);
		gcall.Stepto(27286,-42822,-1760);
		gcall.Stepto(27298,-43190,-1622);
		gcall.Stepto(27324,-43459,-1587);
		gcall.Stepto(27329,-43663,-1584);


		gcall.Stepto(27315,-43375,-1609);
	}

	//修理

	_BAGSTU stu;
	gcall.GetGoodsByEquipPos(EQUITMENT_POS::WUQI, &stu);
	if (stu.m_Lasting < 10)
	{
		BOOL flag = gcall.Stepto(29903,-41454,-2275,10,10,3000);
		if (flag)
		{
			Sleep(1000);
			gcall.Shunyi(L"Lianji28-end-mai");
			Sleep(1000);
			gcall.sendcall(id_msg_OverShunyi,(LPVOID)FALSE);
			Sleep(3000);
			gcall.Stepto(27309,-43292,-1619);
			gcall.Stepto(27315,-43510,-1587,40);
		}
		gcall.WaitPlans();
		gcall.randXianlu(3);
		Sleep(1000);
		gcall.Stepto(27328,-43725,-1587);
		Sleep(1000);
		gcall.Shunyi(L"Lianji28-mai");
		Sleep(1000);
		gcall.sendcall(id_msg_OverShunyi,(LPVOID)FALSE);
		Sleep(3000);
		gcall.Stepto(8868,-38555,-2328);
		gcall.Stepto(8988,-38067,-2325);
		Sleep(1000);
		gcall.FixWuqi();
		Sleep(1000);
		gcall.Stepto(8947,-38366,-2326);
		gcall.Stepto(8863,-38969,-2329);
		Sleep(1000);
		gcall.Shunyi(L"Lianji28-mai-hui");
		Sleep(1000);
		gcall.sendcall(id_msg_OverShunyi,(LPVOID)FALSE);
		Sleep(3000);
		gcall.Stepto(27315,-43375,-1609);
	}

	//卖

	if (gcall.GetBagGridNumberLast() < 5)
	{
		BOOL flag = gcall.Stepto(29903,-41454,-2275,10,10,3000);
		if (flag)
		{
			Sleep(1000);
			gcall.Shunyi(L"Lianji28-end-mai");
			Sleep(1000);
			gcall.sendcall(id_msg_OverShunyi,(LPVOID)FALSE);
			Sleep(3000);
			gcall.Stepto(27309,-43292,-1619);
			gcall.Stepto(27315,-43510,-1587,40);
		}
		gcall.WaitPlans();
		gcall.randXianlu(3);
		Sleep(1000);
		gcall.Stepto(27328,-43725,-1587);
		Sleep(1000);
		gcall.Shunyi(L"Lianji28-mai");
		Sleep(1000);
		gcall.sendcall(id_msg_OverShunyi,(LPVOID)FALSE);
		Sleep(3000);
		gcall.SellItemByConfig(L"한정가");
		Sleep(1000);
		gcall.Stepto(8863,-38969,-2329);
		Sleep(1000);
		gcall.Shunyi(L"Lianji28-mai-hui");
		Sleep(1000);
		gcall.sendcall(id_msg_OverShunyi,(LPVOID)FALSE);
		Sleep(3000);
		gcall.Stepto(27315,-43375,-1609);
	}


	BOOL flag = gcall.Stepto(29903,-41454,-2275,10,10,3000);
	if (flag == TRUE)
	{
		while (1)
		{
			BOOL flagsy = ShunYiResult(3010,L"Lianji28-end",TRUE);
			
			if (flagsy)
			{
				break;
			}else
			{
				gcall.Stepto(29903,-41454,-2275,10,10,3000);
			}
		}
		Sleep(1000);
		gcall.FenJieByConfig();
		Sleep(1000);
		ShunYiResult(3072,L"Lianji28-go",TRUE);
		gcall.Shunyi(L"Lianji28");
		Sleep(1000);
		gcall.sendcall(id_msg_OverShunyi,(LPVOID)0);//hook
	}else
	{
		//gcall.Stepto(27315,-43375,-1609);
		gcall.Stepto(27302,-43092,-1635,30);
		gcall.Stepto(27300,-42845,-1748,30);
		gcall.Stepto(27294,-42597,-1890,30);
		gcall.Stepto(27286,-42346,-2029,10,10,3000,TRUE);
		gcall.Stepto(27275,-42099,-2127,10,10,3000,TRUE);
		gcall.Stepto(27263,-41851,-2235,10,10,3000,TRUE);
		gcall.Stepto(27300,-41650,-2264,10,10,3000,TRUE);
		gcall.Stepto(27520,-41535,-2265,10,10,3000,TRUE);
		gcall.Stepto(27768,-41535,-2265,10,10,3000,TRUE);
		gcall.Stepto(28016,-41532,-2264,10,10,3000,TRUE);
		gcall.Stepto(28264,-41522,-2264,10,10,3000,TRUE);
		gcall.Stepto(28512,-41516,-2281,10,10,3000,TRUE);
		gcall.Stepto(28760,-41511,-2282,10,10,3000,TRUE);

		//while (1)
		//{
		//	BOOL flag = ShunYiResult(3060,L"Lianji22-go",FALSE);
		//	Sleep(1000);
		//	if (flag)
		//	{
		//		break;
		//	}else
		//	{
		//		//加双S
		//		gcall.Stepto(27312,-43336,-1618);
		//	}
		//}
		//Sleep(1000);
		//gcall.Shunyi(L"Lianji28");
		//Sleep(1000);
		//gcall.sendcall(id_msg_OverShunyi,(LPVOID)0);//unhook
	}




	Sleep(2000);
	
	gcall.Stepto(28956,-41577,-2281,10,10,3000,TRUE);
	gcall.Stepto(29190,-41650,-2276,10,10,3000,TRUE);
	gcall.Stepto(29421,-41719,-2282,10,10,3000,TRUE);
	gcall.Stepto(29664,-41764,-2283,10,10,3000,TRUE);
	gcall.Stepto(29912,-41784,-2271,10,10,3000,TRUE);
	gcall.Stepto(30160,-41792,-2281,10,10,3000,TRUE);
	gcall.sendcall(id_msg_attack, (LPVOID)0x5DFC);//v
	gcall.Stepto(30408,-41796,-2276,10,10,3000,TRUE);
	gcall.Stepto(30655,-41772,-2276,10,10,3000,TRUE);
	gcall.Stepto(30895,-41709,-2282,10,10,3000,TRUE);
	gcall.Stepto(30993,-41510,-2276,10,10,3000,TRUE);
	gcall.Stepto(30843,-41336,-2275,10,10,3000,TRUE);
	gcall.Stepto(30599,-41295,-2273,10,10,3000,TRUE);
	gcall.Stepto(30352,-41318,-2275);
	gcall.Stepto(30109,-41366,-2280);
	gcall.Stepto(30012,-41400,-2282);






	gcall.sendcall(id_msg_attack, (LPVOID)0x5E06);//3
	Sleep(1500);
	gcall.sendcall(id_msg_attack, (LPVOID)0x5DE8);//z
	Sleep(800);
	gcall.Kill_Tab();
	Sleep(500);
	gcall.Kill_Tab();
	Sleep(500);
	gcall.Kill_Tab();
	gcall.TurnToNear(500);
	Sleep(500);
	gcall.sendcall(id_msg_attack, (LPVOID)0x5e74);//1
	
	//gcall.TurnToNear(500);
	//gcall.sendcall(id_msg_attack, (LPVOID)0x5E10);//4
	//Sleep(500);
	//gcall.Kill_Tab();
	//Sleep(500);
	//gcall.Kill_Tab();
	if (gcall.FindThenKill(0, 500, modeNormal | modeAoe | modePickup) == RESULT_KILL_PLAYDEAD)
	{
		Sleep(5000);
		gcall.FuHuo();
		Sleep(3000);
		gcall.Stepto(27286,-42822,-1760);
		gcall.Stepto(27298,-43190,-1622);
		gcall.Stepto(27324,-43459,-1587);
		gcall.Stepto(27329,-43663,-1584);

		gcall.Stepto(27315,-43375,-1609);
	}
}

void TaskScript::lianji30_go()
{
	gcall.NewSpend(2.5);
	gcall.Stepto(-24636,-25256,-679);
	gcall.Stepto(-24668,-25243,-679);
	gcall.Stepto(-25039,-25041,-679);
	gcall.Stepto(-25473,-25003,-679);
	gcall.Stepto(-25904,-24981,-679);
	gcall.Stepto(-26344,-24979,-679);
	gcall.Stepto(-26762,-24884,-727);
	gcall.Stepto(-27143,-24685,-868);
	gcall.Stepto(-27502,-24434,-896);
	gcall.Stepto(-27837,-24163,-1003);
	gcall.Stepto(-28166,-23887,-1073);
	gcall.Stepto(-28392,-23512,-1081);
	gcall.Stepto(-28541,-23109,-1080);
	gcall.Stepto(-28468,-22701,-1067);
	gcall.Stepto(-28442,-22455,-1058);
	gcall.Stepto(-28474,-22211,-1056);
	gcall.Stepto(-28595,-21995,-1049);
	gcall.Stepto(-28738,-21792,-1148);
	gcall.Stepto(-28884,-21592,-1278);
	gcall.Stepto(-29034,-21394,-1366);
	gcall.Stepto(-29215,-21225,-1380);
	gcall.Stepto(-29410,-21072,-1412);
	gcall.Stepto(-29623,-20945,-1442);
	gcall.Stepto(-29852,-20851,-1456);
	gcall.Stepto(-30004,-20800,-1463);
	gcall.Stepto(-30416,-20663,-1478);
	gcall.Stepto(-30828,-20526,-1479);
	gcall.Stepto(-31239,-20389,-1480);
	gcall.Stepto(-31648,-20243,-1480);
	gcall.NewSpend(1);
	gcall.Stepto(-31719,-20221,-1480);
	gcall.Stepto(-31952,-20133,-1480);
	gcall.Stepto(-32024,-20106,-1480);
	gcall.Stepto(-32493,-20109,-1410);
	Sleep(2000);
}

void TaskScript::lianji30()
{
	//副本里3080 副本外3047
	//死亡

	if (gcall.GetPlayerDeadStatus() == 1 ||
		gcall.GetPlayerDeadStatus() == 2)
	{
		Sleep(5000);
		gcall.FuHuo();
		Sleep(3000);
		gcall.Stepto(-35324,-19460,-1514);
		gcall.Stepto(-35087,-19462,-1507);
		gcall.Stepto(-34839,-19462,-1466);
		gcall.Stepto(-34610,-19462,-1426);
		gcall.Stepto(-34382,-19465,-1419);
		gcall.Stepto(-34382,-19465,-1419);
		gcall.Stepto(-34395,-19702,-1419);
		gcall.Stepto(-34395,-19950,-1419);
		gcall.Stepto(-34241,-20121,-1419);
		gcall.Stepto(-34003,-20110,-1419);
		gcall.Stepto(-33755,-20100,-1419);
		gcall.Stepto(-33504,-20097,-1419);
		gcall.Stepto(-33254,-20098,-1419);
		gcall.Stepto(-33006,-20099,-1410);
		gcall.Stepto(-32758,-20098,-1410);
		gcall.Stepto(-32459,-20102,-1410);
		gcall.Stepto(-32288,-20107,-1410);

		gcall.Stepto(-32493,-20109,-1410);
	}

	//修理

	_BAGSTU stu;
	gcall.GetGoodsByEquipPos(EQUITMENT_POS::WUQI, &stu);
	if (stu.m_Lasting < 10)
	{
		BOOL flag = gcall.Stepto(-39259,-18338,-2340,10,5,3000);
		if (flag)
		{
			Sleep(1000);
			gcall.Shunyi(L"Lianji30-end-mai");
			Sleep(1000);
			gcall.sendcall(id_msg_OverShunyi,(LPVOID)FALSE);
			Sleep(3000);
			gcall.Stepto(-32453,-20092,-1410);
		}
		gcall.WaitPlans();
		Sleep(1000);
		gcall.Stepto(-32112,-20110,-1480);
		gcall.Stepto(-31877,-20143,-1480);
		gcall.Stepto(-31631,-20175,-1480);
		gcall.Stepto(-31385,-20208,-1480);
		gcall.Stepto(-31140,-20241,-1480);
		gcall.Stepto(-30893,-20274,-1460);
		gcall.Stepto(-30645,-20299,-1439);
		gcall.Stepto(-30395,-20307,-1445);
		Sleep(1000);
		gcall.FixWuqi();
		Sleep(1000);
		gcall.Stepto(-30395,-20307,-1445);
		gcall.Stepto(-30645,-20299,-1439);
		gcall.Stepto(-30893,-20274,-1460);
		gcall.Stepto(-31140,-20241,-1480);
		gcall.Stepto(-31385,-20208,-1480);
		gcall.Stepto(-31631,-20175,-1480);
		gcall.Stepto(-31877,-20143,-1480);
		gcall.Stepto(-32493,-20109,-1410);
	}

	//卖

	if (gcall.GetBagGridNumberLast() < 5)
	{
		BOOL flag = gcall.Stepto(-39259,-18338,-2340,10,5,3000);
		if (flag)
		{
			Sleep(1000);
			gcall.Shunyi(L"Lianji30-end-mai");
			Sleep(1000);
			gcall.sendcall(id_msg_OverShunyi,(LPVOID)FALSE);
			Sleep(3000);
			gcall.Stepto(-32453,-20092,-1410);
		}
		gcall.WaitPlans();
		Sleep(1000);
		gcall.Stepto(-32112,-20110,-1480);
		Sleep(1000);
		gcall.Shunyi(L"Lianji30-mai");
		Sleep(1000);
		gcall.sendcall(id_msg_OverShunyi,(LPVOID)FALSE);
		Sleep(3000);
		gcall.Stepto(-23932,-24614,-679);
		Sleep(1000);
		gcall.SellItemByConfig(L"한정가");
		Sleep(1000);
		gcall.Stepto(-24082,-24648,-679);
		Sleep(1000);
		gcall.Shunyi(L"Lianji30-mai-hui");
		Sleep(1000);
		gcall.sendcall(id_msg_OverShunyi,(LPVOID)FALSE);
		Sleep(3000);
		

		gcall.Stepto(-32493,-20109,-1410);
	}


	BOOL flag = gcall.Stepto(-39259,-18338,-2340,10,10,3000);
	if (flag == TRUE)
	{
		while (1)
		{
			BOOL flagsy = ShunYiResult(3047,L"Lianji30-end",TRUE);

			if (flagsy)
			{
				break;
			}else
			{
				gcall.Stepto(-39259,-18338,-2340,10,5,3000);
			}
		}
		Sleep(1000);
		gcall.FenJieByConfig();
		Sleep(1000);
		ShunYiResult(3080,L"Lianji30-go",TRUE);
		gcall.Shunyi(L"Lianji30");
		Sleep(1000);
		gcall.sendcall(id_msg_OverShunyi,(LPVOID)0);//hook
	}else
	{

		//gcall.Stepto(27315,-43375,-1609);
		gcall.Stepto(-32552,-20109,-1410);
		gcall.WaitPlans();
		gcall.Stepto(-32727,-20104,-1410,10,10,1000,TRUE);
		gcall.Stepto(-32975,-20101,-1410,10,10,1000,TRUE);
		gcall.Stepto(-33226,-20096,-1419,10,10,1000,TRUE);
		gcall.Stepto(-33474,-20091,-1419,10,10,1000,TRUE);
		gcall.Stepto(-33722,-20088,-1419,10,10,1000,TRUE);
		gcall.Stepto(-33970,-20084,-1419,10,10,1000,TRUE);
		gcall.Stepto(-34218,-20084,-1419,10,10,1000,TRUE);
		gcall.Stepto(-34412,-20085,-1419,10,10,1000,TRUE);
		gcall.Stepto(-34415,-20034,-1419,10,10,1000,TRUE);
		gcall.Stepto(-34422,-19786,-1419,10,10,1000,TRUE);
		gcall.Stepto(-34424,-19538,-1419,10,10,1000,TRUE);
		gcall.Stepto(-34663,-19457,-1435,10,10,1000,TRUE);
		gcall.Stepto(-34911,-19459,-1478,10,10,1000,TRUE);
		gcall.Stepto(-35159,-19461,-1508,10,10,1000,TRUE);
		gcall.Stepto(-35407,-19463,-1515,10,10,1000,TRUE);
		gcall.Stepto(-35657,-19467,-1606,10,10,1000,TRUE);
		gcall.Stepto(-35905,-19471,-1734,10,10,1000,TRUE);
		gcall.Stepto(-36156,-19475,-1860,10,10,1000,TRUE);
		gcall.Stepto(-36404,-19478,-1983,10,10,1000,TRUE);
		gcall.Stepto(-36652,-19482,-2079,10,10,1000,TRUE);
		gcall.Stepto(-36875,-19474,-2155,10,10,1000,TRUE);

		//while (1)
		//{
		//	BOOL flag = ShunYiResult(3060,L"Lianji22-go",FALSE);
		//	Sleep(1000);
		//	if (flag)
		//	{
		//		break;
		//	}else
		//	{
		//		//加双S
		//		gcall.Stepto(27312,-43336,-1618);
		//	}
		//}
		//Sleep(1000);
		//gcall.Shunyi(L"Lianji28");
		//Sleep(1000);
		//gcall.sendcall(id_msg_OverShunyi,(LPVOID)0);//unhook
	}




	Sleep(2000);

	gcall.Stepto(-37056,-19443,-2160);
	gcall.Stepto(-37295,-19470,-2160);
	gcall.Stepto(-37541,-19498,-2143);
	gcall.Stepto(-37787,-19491,-2168);
	gcall.Stepto(-38026,-19428,-2218);
	gcall.Stepto(-38264,-19356,-2258);

	gcall.Stepto(-38337,-19109,-2268,10,10,3000,TRUE);
	gcall.Stepto(-38384,-18862,-2311,10,10,3000,TRUE);
	gcall.Stepto(-38529,-18716,-2322,10,10,3000,TRUE);
	gcall.Stepto(-38770,-18777,-2314,10,10,3000,TRUE);
	gcall.Stepto(-39011,-18838,-2310,10,10,3000,TRUE);
	gcall.Stepto(-39152,-18625,-2321,10,10,3000,TRUE);
	gcall.Stepto(-39209,-18383,-2338,10,10,3000,TRUE);




	gcall.sendcall(id_msg_attack, (LPVOID)0x5DFC);//v

	gcall.Stepto(-39420,-18263,-2322,10,10,3000,TRUE);
	gcall.Stepto(-39630,-18150,-2315,10,10,3000,TRUE);
	gcall.Stepto(-39842,-18024,-2321,10,10,3000,TRUE);
	gcall.Stepto(-39993,-17826,-2323,10,10,3000,TRUE);
	gcall.Stepto(-40154,-17637,-2315,10,10,3000,TRUE);
	gcall.Stepto(-40298,-17480,-2315,10,10,3000,TRUE);
	gcall.sendcall(id_msg_attack, (LPVOID)0x5dca);//tab
	gcall.Stepto(-40044,-17406,-2315,10,5);
	gcall.Stepto(-40542,-17487,-2314,10,10,3000);
	gcall.Stepto(-40751,-17590,-2320,10,10,3000,TRUE);
	gcall.Stepto(-40758,-17837,-2326);
	gcall.Stepto(-40645,-18053,-2325);
	gcall.Stepto(-40455,-18213,-2328);
	gcall.Stepto(-40296,-18346,-2330,10,10,3000,TRUE);
	gcall.Stepto(-40061,-18285,-2324);
	gcall.Stepto(-39822,-18219,-2318);
	gcall.Stepto(-39580,-18185,-2315);

	
	
	gcall.sendcall(id_msg_attack, (LPVOID)0x5E06);//3
	Sleep(1500);
	gcall.sendcall(id_msg_attack, (LPVOID)0x5DE8);//z
	Sleep(800);
	gcall.Kill_Tab();
	Sleep(500);
	gcall.Kill_Tab();
	Sleep(500);
	gcall.Kill_Tab();
	gcall.TurnToNear(500);
	Sleep(500);
	gcall.sendcall(id_msg_attack, (LPVOID)0x5e74);//1

	//gcall.TurnToNear(500);
	//gcall.sendcall(id_msg_attack, (LPVOID)0x5E10);//4
	//Sleep(500);
	//gcall.Kill_Tab();
	//Sleep(500);
	//gcall.Kill_Tab();
	if (gcall.FindThenKill(0, 500, modeNormal | modeAoe | modePickup) == RESULT_KILL_PLAYDEAD)
	{
		Sleep(5000);
		gcall.FuHuo();
		Sleep(3000);
		gcall.Stepto(-35324,-19460,-1514);
		gcall.Stepto(-35087,-19462,-1507);
		gcall.Stepto(-34839,-19462,-1466);
		gcall.Stepto(-34610,-19462,-1426);
		gcall.Stepto(-34382,-19465,-1419);
		gcall.Stepto(-34382,-19465,-1419);
		gcall.Stepto(-34395,-19702,-1419);
		gcall.Stepto(-34395,-19950,-1419);
		gcall.Stepto(-34241,-20121,-1419);
		gcall.Stepto(-34003,-20110,-1419);
		gcall.Stepto(-33755,-20100,-1419);
		gcall.Stepto(-33504,-20097,-1419);
		gcall.Stepto(-33254,-20098,-1419);
		gcall.Stepto(-33006,-20099,-1410);
		gcall.Stepto(-32758,-20098,-1410);
		gcall.Stepto(-32459,-20102,-1410);
		gcall.Stepto(-32288,-20107,-1410);

		gcall.Stepto(-32493,-20109,-1410);
	}
}

