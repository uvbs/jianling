#pragma once

class TaskScript
{
public:
	TaskScript(void){};
	~TaskScript(void){};
    void BeginTask(){};
	void log(TCHAR szFormat[], ...);
	void Task_221(int zid,int taskid);//新手任务1
	void Task_222(int zid,int taskid);//新手任务2
	void Task_223(int zid,int taskid);//新手任务3
	void Task_224(int zid,int taskid);//新手任务4
	void Task_231(int zid,int taskid);//新手任务5
	void Task_232(int zid,int taskid);//新手任务6
	void Task_227(int zid,int taskid);//新手任务7
	void Task_243(int zid,int taskid);//新手任务8
	void Task_301(int zid,int taskid);//1?. ???? 1-1
	void Task_302(int zid,int taskid);//1?. ??? ???  1-2
	void Task_303(int zid,int taskid);//1?. ????? ??  1-3
	void Task_497(int zid,int taskid);//4?. ????? ??? ?? 1-4
	void Task_304(int zid,int taskid);//5?. ??? ??  1-5
	void Task_305(int zid,int taskid);//6?. ??? ??.  1-6
	void Task_306(int zid,int taskid);//7?. ???? ??.  1-7
	void Task_307(int zid,int taskid);//8?. ??? ??? ??.  1-8
	void Task_308(int zid,int taskid);//9?. ??? ?? ? 1-9
	void Task_309(int zid,int taskid);//10?. ??? ??
	void Task_310(int zid,int taskid);//11?. ?? ??
	void Task_311(int zid,int taskid);//12?. ??? ??
	void Task_312(int zid,int taskid);//13?. ??? ????
	void Task_491(int zid,int taskid);//14?. ?? ? ??
	void Task_492(int zid,int taskid);//15?. ? ?? 
	void Task_313(int zid,int taskid);//16?. ??? ??
	void Task_494(int zid,int taskid);//17?. ????? ??
	void Task_314(int zid,int taskid);//18?. ????
	void Task_496(int zid,int taskid);//19?. ??? ??
	void Task_315(int zid,int taskid);//20?. ???? ??
	void Task_316(int zid,int taskid);//21?. ??? ??
	void Task_493(int zid,int taskid);//22?. ??? ??
	void Task_317(int zid,int taskid);//23?. ????
	void Task_318(int zid,int taskid);//24?. ?? ??
	void Task_495(int zid,int taskid);//25?. ??? ?? ??
	void Task_319(int zid,int taskid);//26?. ??? ????
	void Task_320(int zid,int taskid);//27?. ??? ??? ??
	void Task_501(int zid,int taskid);//1?. ??? ??
	void Task_540(int zid,int taskid);//2?. ?? ??
	void Task_502(int zid,int taskid);//3?. ??? ????
	void Task_503(int zid,int taskid);//4?. ??? ????
	void Task_504(int zid,int taskid);//5?. ??? ??
	void Task_505(int zid,int taskid);//6?. ??? ???
	void Task_506(int zid,int taskid);//7?. ??? ??
	void Task_507(int zid,int taskid);//8?. ??? ???
	void Task_508(int zid,int taskid);//9?. ????? ??
	void Task_509(int zid,int taskid);//10?. ??? ??? ?
	void Task_510(int zid,int taskid);//11?. ????
	void Task_511(int zid,int taskid);//12?. ???? ?
	void Task_512(int zid,int taskid);//13?. ??? ??
	void Task_513(int zid,int taskid);//14?. ??
	void Task_514(int zid,int taskid);//15?. ??? ??? ??? ??
	void Task_515(int zid,int taskid);//16?. ?????
	void Task_516(int zid,int taskid);//17?. ??? ??
	void Task_517(int zid,int taskid);//18?. ??? ??
	void Task_518(int zid,int taskid);//19?. ??
	void Task_519(int zid,int taskid);//20?. ?????
	void Task_520(int zid,int taskid);//21?. ??? ??
	void Task_521(int zid,int taskid);//22?. ???? ??
	void Task_522(int zid,int taskid);//23?. ???? ?? ??
	void Task_523(int zid,int taskid);//24?. ??? ?
	void Task_524(int zid,int taskid);//25?. ???? ??
	void Task_525(int zid,int taskid);//
	void Task_526(int zid,int taskid);//
	void Task_294(int zid,int taskid);//魔道4-19
	void Lianji6();//6级副本
	void Lianji6_go();//6级副本 进
	void lianji8();//8级副本
	void lianji8_go();//8级副本 进
	void lianji10();//10级副本
	void lianji10_go();//10级副本 进
	void lianji14();//14级副本
	void lianji14_go();//14级副本 进
	void lianji18();//18级副本
	void lianji18_go();//18级副本 进
	void lianji22();//22级副本
	void lianji22_go();//22级副本 进
	void lianji28();//28级副本
	void lianji28_go();//28级副本 进
	void lianji30();//30级副本
	void lianji30_go();//30级副本 进
	BOOL ShunYiResult(DWORD CityId,wchar_t* FileName,BOOL Hook_flag);//瞬移等待逻辑的封装函数
	void UseExperience();//使用经验药
	void IsGoonHecheng(DWORD pos);//逻辑循环强化物品
private:
};

typedef void (TaskScript::*FunPointer)(int zid,int taskid);

typedef struct _FunTask
{
	TCHAR *taskname;//大任务ID+小任务ID
	FunPointer fp;//函数指针

} FunTask;
