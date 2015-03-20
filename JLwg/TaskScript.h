#pragma once

class TaskScript
{
public:
	TaskScript(void);
	~TaskScript(void);
	void BeginTask();
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
	void Task_318(int zid,int taskid);//24장. 거짓 서신
	void Task_495(int zid,int taskid);//25장. 결전을 위한 준비
	void Task_319(int zid,int taskid);//26장. 남소유 구출작전
	void Task_320(int zid,int taskid);//27장. 불타는 대나무 마을
	void Task_501(int zid,int taskid);//1장. 수상한 마을
	void Task_540(int zid,int taskid);//2장. 원군 요청
	void Task_502(int zid,int taskid);//3장. 거만한 수비대장
	void Task_503(int zid,int taskid);//4장. 의문의 마교집단
	void Task_504(int zid,int taskid);//5장. 원수의 흔적
	void Task_505(int zid,int taskid);//6장. 위기의 무녀들
	void Task_506(int zid,int taskid);//7장. 어둠의 구멍
	void Task_507(int zid,int taskid);//8장. 운국의 감찰관
	void Task_508(int zid,int taskid);//9장. 낭인무사의 정체
	void Task_509(int zid,int taskid);//10장. 불타는 환영초 밭
	void Task_510(int zid,int taskid);//11장. 절사명의
	void Task_511(int zid,int taskid);//12장. 배신자의 집
	void Task_512(int zid,int taskid);//13장. 끌려간 미령
	void Task_513(int zid,int taskid);//14장. 심마
	void Task_514(int zid,int taskid);//15장. 무신의 비보를 노리는 장군
	void Task_515(int zid,int taskid);//16장. 보물사냥꾼
	void Task_516(int zid,int taskid);//17장. 연꽃의 도적
	void Task_517(int zid,int taskid);//18장. 도적의 행방
	void Task_518(int zid,int taskid);//19장. 동업
	void Task_519(int zid,int taskid);//20장. 무신삼원로
	void Task_520(int zid,int taskid);//21장. 고대의 살수
	void Task_521(int zid,int taskid);//22장. 무신릉의 단서
	void Task_522(int zid,int taskid);//23장. 번갯불을 찾는 도공
	void Task_523(int zid,int taskid);//24장. 가마의 제
	void Task_524(int zid,int taskid);//25장. 주정뱅이 기인
	void Task_525(int zid,int taskid);//26장. 천씨 성을 지닌 자
	void Task_526(int zid,int taskid);//27장. 죽음 위의 연꽃
	void Task_527(int zid,int taskid);//28장. 명장의 석상
	void Task_528(int zid,int taskid);//29장. 은조패
	void Task_541(int zid,int taskid);//30장. 배신한 사형과 만남
	void Task_529(int zid,int taskid);//31장. 애꾸눈의 사연
	void Task_530(int zid,int taskid);//32장. 무신을 가리키는 나침반
	void Task_531(int zid,int taskid);//33장. 춤추는 바늘
	void Task_532(int zid,int taskid);//34장. 이이제이
	void Task_533(int zid,int taskid);//35장. 무신의 후예
	void Task_542(int zid,int taskid);//36장. 다시 만난 거지 노인
	void Task_534(int zid,int taskid);//37장. 뼈가면의 전사들
	void Task_535(int zid,int taskid);//38장. 앙숙
	void Task_536(int zid,int taskid);//39장. 무신의 날개
	void Task_537(int zid,int taskid);//40장. 복수의 길, 홍문의 길
	void Task_538(int zid,int taskid);//41장. 다시 만난 팔부기재
	void Task_901(int zid,int taskid);//1장. 뒤틀린 용맥
	void Task_902(int zid,int taskid);//2장. 과거와 현재의 인연
	void Task_903(int zid,int taskid);//3장. 동맹을 위한 탈출
	void Task_904(int zid,int taskid);//
	void Task_905(int zid,int taskid);//

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
	void lianji36();//36级副本
	void lianji36_go();//36级副本 进
	void lianji40();//40级副本
	void lianji40_go();//40级副本 进
	void lianji42();//42级副本
	void lianji42_go();//42级副本 进
	void lianji45();//45级副本
	void lianji45_go();//45级副本 进
	void yaojiang39();
	void yaojiang42();
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
