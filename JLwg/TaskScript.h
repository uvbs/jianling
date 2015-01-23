#pragma once

class TaskScript
{
public:
	TaskScript(void);
	~TaskScript(void);
	void BeginTask();
	void log(TCHAR szFormat[], ...);
	void Task_221(int taskid);//新手任务1
	void Task_222(int taskid);//新手任务2
	void Task_223(int taskid);//新手任务3
	void Task_224(int taskid);//新手任务4
	void Task_231(int taskid);//新手任务5
	void Task_232(int taskid);//新手任务6
	void Task_227(int taskid);//新手任务7
	void Task_243(int taskid);//新手任务8
	void Task_301(int taskid);//1장. 구사일생 1-1
	void Task_302(int taskid);//1장. 대사형 도천풍  1-2
	void Task_303(int taskid);//1장. 자경단장의 아들  1-3
	void Task_497(int taskid);//4장. 남소유라는 이름의 여인 1-4
	void Task_304(int taskid);//5장. 생명의 은인  1-5
	void Task_305(int taskid);//6장. 수상한 촌장.  1-6
	void Task_306(int taskid);//7장. 도적들의 정체.  1-7
	void Task_307(int taskid);//8장. 해적과 손잡은 산적.  1-8
	void Task_308(int taskid);//9장. 어두운 등잔 밑 1-9
	void Task_309(int taskid);//10장. 해적의 소굴
	void Task_310(int taskid);//
	void Lianji6();//6级副本
	void Lianji6_go();//6级副本 进
	void lianji8();//8级副本
	void lianji8_go();//8级副本 进
	void lianji10();//10级副本
	void lianji10_go();//10级副本 进
	void lianji14();//14级副本
	void lianji14_go();//14级副本 进
private:
};

typedef void (TaskScript::*FunPointer)(int taskid);

typedef struct _FunTask
{
	TCHAR *taskname;//大任务ID+小任务ID
	FunPointer fp;//函数指针

} FunTask;
