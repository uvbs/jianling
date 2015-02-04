#ifndef _TASKSCRIPT_H
#define _TASKSCRIPT_H

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
	void Task_301(int zid,int taskid);//1장. 구사일생 1-1
	void Task_302(int zid,int taskid);//1장. 대사형 도천풍  1-2
	void Task_303(int zid,int taskid);//1장. 자경단장의 아들  1-3
	void Task_497(int zid,int taskid);//4장. 남소유라는 이름의 여인 1-4
	void Task_304(int zid,int taskid);//5장. 생명의 은인  1-5
	void Task_305(int zid,int taskid);//6장. 수상한 촌장.  1-6
	void Task_306(int zid,int taskid);//7장. 도적들의 정체.  1-7
	void Task_307(int zid,int taskid);//8장. 해적과 손잡은 산적.  1-8
	void Task_308(int zid,int taskid);//9장. 어두운 등잔 밑 1-9
	void Task_309(int zid,int taskid);//10장. 해적의 소굴
	void Task_310(int zid,int taskid);//11장. 검은 기운
	void Task_311(int zid,int taskid);//12장. 탁기의 시체
	void Task_312(int zid,int taskid);//13장. 괴팍한 독초거사
	void Task_491(int zid,int taskid);//14장. 어둠 속 출수
	void Task_492(int zid,int taskid);//15장. 곰 사냥 
	void Task_313(int zid,int taskid);//16장. 예정된 기연
	void Task_494(int zid,int taskid);//17장. 팔부기재의 시험
	void Task_314(int zid,int taskid);//18장. 이독치독
	void Task_496(int zid,int taskid);//19장. 망자의 역습
	void Task_315(int zid,int taskid);//20장. 잃어버린 봇짐
	void Task_316(int zid,int taskid);//21장. 겁먹은 아이
	void Task_493(int zid,int taskid);//22장. 첩자의 정체
	void Task_317(int zid,int taskid);//23장. 경국지색
	void Task_318(int zid,int taskid);//
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
	BOOL ShunYiResult(DWORD CityId,wchar_t* FileName,BOOL Hook_flag);//瞬移等待逻辑的封装函数
	void UseExperience();//使用经验药
	void IsGoonHecheng(DWORD pos);//逻辑循环强化物品
private:


    typedef void (TaskScript::*FunPointer)(int zid,int taskid);

typedef struct _FunTask
{
	TCHAR *taskname;//大任务ID+小任务ID
	FunPointer fp;//函数指针

} FunTask;



};


#endif