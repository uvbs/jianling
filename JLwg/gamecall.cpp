#include "stdafx.h"
#include "Gamecall.h"
#include "GamecallEx.h"

#include "..\common\CIniFile.h"

BYTE Gamecall::ReadByte(DWORD addr)
{
	if(!IsBadReadPtr((void*)addr, sizeof(BYTE)))
		return *(BYTE*)addr;
	return 0;
}

WORD Gamecall::ReadWORD(DWORD addr)
{
	if(!IsBadReadPtr((void*)addr, sizeof(WORD)))
		return *(WORD*)addr;
	return 0;
}

DWORD Gamecall::ReadDWORD(DWORD addr)
{
	if(!IsBadReadPtr((void*)addr, sizeof(DWORD)))
		return *(DWORD*)addr;
	return 0;
}

int Gamecall::ReadInt(DWORD addr)
{
	if(!IsBadReadPtr((void*)addr, sizeof(int)))
		return *(int*)addr;
	return 0;
}

float Gamecall::ReadFloat(DWORD addr)
{
	if(!IsBadReadPtr((void*)addr, sizeof(float)))
		return *(float*)addr;
	return 0;
}

char* Gamecall::ReadStr(DWORD addr)
{
	if(!IsBadReadPtr((void*)addr, sizeof(char)))
		return (char*)addr;
	return 0;
}

Gamecall::Gamecall(): log(_T("gcall"))
{
	m_pfnInitSpeed = NULL;
	m_pShareMem = NULL;

	ZeroMemory(m_szLujingPath, MAX_PATH);
	ZeroMemory(m_szConfigPath, MAX_PATH);
	ZeroMemory(m_szLujingTest, MAX_PATH);

}

Gamecall::~Gamecall()
{
}


void Gamecall::DunDi(DWORD cityid)
{
	__try
	{
		__asm
		{
			mov eax, obj_enum_base;
			mov eax, [eax];
			mov eax, [eax + dundi_offset1];
			mov eax, [eax + dundi_offset2];
			mov esi, [eax + dundi_offset3];
			mov eax, cityid;
			mov ebx, dundi_call;
			call ebx;
		}
	}
	__except(1)
	{
		log.logdv(_T("����  error"));
	}
}




void Gamecall::Fuhuo(DWORD uiAddr)
{
	
	__try
	{
		log.logdv(_T("���븴��call uiAddr:%d"),uiAddr);
		__asm
		{
			mov eax,uiAddr;
			push eax;
			mov ecx,0x3;
			mov eax,fuhuo_call;
			call eax;
		}
	}
	__except(1)
	{
		OutputDebugString(_T("����ʧ��"));
	}
}
//���츳ui
void Gamecall::OpenTalentUI()
{
	DWORD dwUIAddr = 0;
	GetUIAddrByName(L"SystemMenuPanel", &dwUIAddr);

	if(dwUIAddr){
		DWORD canshu2 = 0;
		canshu2 =  ReadDWORD(ReadDWORD(dwUIAddr+0x4C) + 0x7D4);
	
		if ( canshu2 > 0 )
		{
			DaKaiJiNengMianBan(dwUIAddr,canshu2); //�򿪼������
		}
	}
}

void Gamecall::DaKaiJiNengMianBan(DWORD adress,DWORD adress1) //�򿪼������
{

	KONGJ kj;
	kj.canshu1 = QUDINGYAOJIANG_JIEGOUTOU;
	kj.canshu2 = 0x0;
	kj.canshu3 = 0x544D0EA8;
	kj.canshu4 = 0x0;
	kj.canshu5 = adress1;      //[[�ؼ����׵�ַ+0x4C]+0x7D4]
	kj.canshu6 = 0x1;
	kj.canshu7 = 0x2;
	kj.canshu8 = 0x0;
	kj.canshu9 = 0x0;
	kj.canshu10= 0x0;
	kj.canshu11= 0x0;
	kj.canshu12= 0x4EFE0016;

	_try
	{
		_asm
		{
			mov ecx,adress; //����ǿؼ����׵�ַ  "SystemMenuPanel"
			mov edx,[ecx];
			mov eax,[edx+0x4];

			lea ebx,kj;
			push ebx;
			call eax  
		}
	}

	_except(1)
	{
		TRACE(_T("�򿪼������CALL����"));
	}
}


DWORD Gamecall::call(DWORD id, LPVOID pParam)
{
	switch(id)
	{
	case id_msg_GetStrikeToVector:
		{
			GetStrikeToVector(*(std::vector<STRIKEINFO>*)pParam);
		}
		break;
	case id_msg__GetUiAddrByName:
		{
			KONGJIAN_JIEGOU* jiegou = (KONGJIAN_JIEGOU*)pParam;
			_GetUiAddrByName((Tree*)jiegou->adress,jiegou->name,jiegou->ID);
		}
		break;
	case id_msg_NewSpend:
		{
			_NewSpend(*(float*)pParam);
		}
		break;
    case id_msg_GetAllBodyEquipToVector:
        {
            _GetAllBodyEquipToVector(*(std::vector<_BAGSTU> *)pParam);
        }
        break;
    case id_msg_GetAllGoodsToVector:
        {
            _GetAllGoodsToVector(*(std::vector<_BAGSTU> *)pParam);
            
        }
        break;
    case id_msg_GetAcceptedQuestToVector:
        {
            _GetAcceptedQuestToVector(*(std::vector<Quest> *)pParam);
        }
        break;
 	case id_msg_GetRangeObjectToVector:
        {
            PARAM_GETUIADDRBYNAME* temp = (PARAM_GETUIADDRBYNAME *)pParam;
            _GetRangeObjectToVector((ObjectNode *)temp->argv1, temp->argv2, *(std::vector<ObjectNode *> *)temp->argv3);
 		}
 		break;

    case id_msg_GetUItoVector:
        {
            PARAM_GUANSHANGDIAN* temp = (PARAM_GUANSHANGDIAN *)pParam;
            _GetUItoVector((Tree *)temp->argv1, *(std::vector<Tree *> *)temp->argv2);
        }
        break;
	case id_msg_OverShunyi:
		{
			OverShunyi((BOOL)pParam);
		}
		break;

	case id_msg_isYaoPingCD:
		{
			_BAGSTU* temp = (_BAGSTU *)pParam;
			return isYaoPingCD(*temp);
		}
	case id_msg_GouMaiWuPing:
		{
			PARAM_GETUIADDRBYNAME* temp = (PARAM_GETUIADDRBYNAME *)pParam;
			GouMaiWuPing(temp->argv1, temp->argv2, temp->argv3);
		}
        break;

	case id_msg_XieBaoShi:
		{
			PARAM_GETUIADDRBYNAME* temp = (PARAM_GETUIADDRBYNAME *)pParam;
			XieBaoShi(temp->argv1, temp->argv2, temp->argv3);
		}
		break;
		
	case id_msg_JiaBaoShi:
		{
			PARAM_JIEFENGZHUANGBEI* temp = (PARAM_JIEFENGZHUANGBEI *)pParam;
			JiaBaoShi(temp->argv1, temp->argv2, temp->argv3, temp->argv4, temp->argv5);
		}
		break;
		
	case id_msg_JieFengZhuangBei:
		{
			PARAM_JIEFENGZHUANGBEI* temp = (PARAM_JIEFENGZHUANGBEI *)pParam;
			JieFengZhuangBei(
				temp->argv1,
				temp->argv2,
				temp->argv3,
				temp->argv4,
				temp->argv5,
				temp->argv6,
				temp->argv7);
		}
		break;

	case id_msg_TiaoYue:
		{
			TiaoYue();
		}
		break;
		
		
	case id_msg_HuanXian:
		{
			HuanXian((DWORD)pParam);
		}
		break;
		
	case id_msg__KaiHeZi:
		{
			_BAGSTU* temp = (_BAGSTU *)pParam;
			KaiHeZi(*temp);
		}
		break;
		
	case id_msg_SellItem:
		{
			_PARAM_GUANSHANGDIAN* temp = (_PARAM_GUANSHANGDIAN *)pParam;
			SellItem(*(_BAGSTU *)temp->argv1, temp->argv2);
		}
		break;
		
	case id_msg_NewBag:
		{
			NewBag();
		}
		break;
		
	case id_msg_Fuhuo:
		{
			Fuhuo(*(DWORD*)pParam);
		}
		break;
		
	case id_msg_PickupTask:
		{
			ObjectNode* temp = (ObjectNode *)pParam;
			_PickupTask(temp);
		}
		break;
	case id_msg_Pickup1:
		{
			ObjectNode* temp = (ObjectNode *)pParam;
			Pickup1(temp);
		}
		break;
	case id_msg_Pickup2:
		{
			ObjectNode* temp = (ObjectNode *)pParam;
			Pickup2(temp);
		}
		break;
		
	case id_msg_OpenQuestItem:
		{
			PARAM_GUANSHANGDIAN* temp = (PARAM_GUANSHANGDIAN *)pParam;
			OpenQuestItem(temp->argv1, temp->argv2);
		}
		break;
		
		
	case id_msg_ZOULUSHUNYI:
		{
			PARAM_GUANSHANGDIAN* temp = (PARAM_GUANSHANGDIAN *)pParam;
			ZOULUSHUNYI((DWORD *)temp->argv1, temp->argv2);
		}
		break;
		
		
	case id_msg_GatTaskName:
		{
			return (DWORD)GatTaskName((DWORD)pParam);
		}
		
	case id_msg_GatBagGoodrName:
		{
			return (DWORD)GatBagGoodrName((DWORD)pParam);
		}
		
	case id_msg_DunDi:
		{
			DunDi((DWORD)pParam);
		}
		break;
	case id_msg_PickdownBody:
		{
			PickdownBody();
		}
		break;
		
		
	case id_msg_JingDianMoShi:
		{
			UIOperator* temp = (UIOperator *)pParam;
			JingDianMoShi((DWORD)temp->pAddr, temp->c5);
		}
		break;
	case id_msg_PickupDeadbody:
		{
			PARAM_GUANSHANGDIAN* temp = (PARAM_GUANSHANGDIAN *)pParam;
			PickupDeadbody(temp->argv1, temp->argv2);
		}
		break;
	case id_msg_HeChengWuQi_Po10:
		{
			PARAM_HECHENGWUQI* temp = (PARAM_HECHENGWUQI *)pParam;
			HeChengWuQi_Po10(temp->zhu, temp->fu, temp->adress);
		}
		break;
		
		
	case id_msg_FaSonXianLuBao:
		{
			FaSonXianLuBao((DWORD)pParam);
		}
		break;
		
		
	case id_msg_DeliverQuests:
		{
			PARAM_DELIVERQUEST* temp = (PARAM_DELIVERQUEST *)pParam;
			DeliverQuests(
				temp->id,
				temp->step,
				temp->questtype,
				temp->ff,
				temp->npcid1,
				temp->npcid2,
				temp->unknow,
				temp->mianban);
		}
		break;
		
		
	case id_msg_DeleteItem:
		{
			_BAGSTU* temp = (_BAGSTU *)pParam;
			DeleteItem(*temp);
		}
		break;
		
		
	case id_msg_ChiYao:
		{

			ChiYao(*(_BAGSTU *)pParam);
		}
		break;
	case id_msg_step:
		{
			
			fPosition* pStepParam = (fPosition *)pParam;
			Step(pStepParam->x, pStepParam->y, pStepParam->z);
		}
		break;
		
	case id_msg_step3x:
		{

			fPosition* pStepParam = (fPosition *)pParam;
			Step3x(pStepParam->x, pStepParam->y, pStepParam->z);
		}
		break;
	case id_msg_vector_ui:
		{
			std::vector<Tree *>* pAllui = (std::vector<Tree *> *)pParam;
			GetUItoVector(GetUIBinTreeBaseAddr(), *pAllui);
		}
		break;
		
	case id_msg_guanshangdian:
		{
			UIOperator* temp = (UIOperator *)pParam;
			GuanBiDuiHuaKuangChuanKou((DWORD)temp->pAddr, temp->c5);
		}
		break;
	case id_msg_DaKaiDuiHuaKuang:
		{
			PARAM_GUANSHANGDIAN* temp = (PARAM_GUANSHANGDIAN *)pParam;
			DaKaiDuiHuaKuang(temp->argv1, temp->argv2);
		}
		break;
		
	case id_msg_attack:
		{
			Attack((DWORD)pParam);
		}
		break;
		
		
	case id_msg_clickui:
		{
			UIOperator* pOpui = (UIOperator *)pParam;
			ClickUI(*pOpui);
		}
		break;
		
	case id_msg_HeChengWuQi_Po5:
		{
			PARAM_GUANSHANGDIAN* temp = (PARAM_GUANSHANGDIAN *)pParam;
			HeChengWuQi_Po5(*(_BAGSTU *)temp->argv1, *(_BAGSTU *)temp->argv2);
		}
		break;
		
	case id_msg_HeChengWuQi:
		{
			PARAM_GUANSHANGDIAN* temp = (PARAM_GUANSHANGDIAN *)pParam;	
			HeChengWuQi(*(_BAGSTU *)temp->argv1, *(_BAGSTU *)temp->argv2);
		}
		break;
		
		
	case id_msg_WearEquipment:
		{
			_BAGSTU* bag = (_BAGSTU *)pParam;
			WearEquipment(*bag);
		}
		break;
		
	case id_msg_Fenjie:
		{
			_BAGSTU* temp = (_BAGSTU *)pParam;
			FenJie(*temp);
		}
		break;
		
		
	case id_msg_CunCangku:
		{
			CunCangku(*(_BAGSTU *)pParam);
		}
		break;
	}
	
	return 0;
}



//�ϳ�����
void Gamecall::HeChengWuQi(_BAGSTU &zhu, _BAGSTU &fu) 
{
	
	
	int zhu_value = zhu.m_Info;
	zhu_value <<= 16;
	zhu_value += body;
	
	int fu_value = fu.m_Info;
	fu_value <<= 16;
	fu_value += package;
	
	
	
	log.logdv(_T("%s: %08x, %08x"), FUNCNAME, zhu, fu);
	__try
	{
		_asm
		{
			push 0;
			push 0;
			push 0;
			mov eax, fu_value;
			push eax;
			push 0;
			mov ecx, zhu_value;
			push ecx;
			mov eax,obj_enum_base;
			mov eax,[eax];
			mov eax,[eax+ hewuqi_offset1];
			mov eax,[eax+ hewuqi_offset2];
			mov ecx,[eax+ hewuqi_offset3];
			mov eax,hewuqi_call ;
			call eax;
		}
	}
	__except(1)
	{
		OutputDebugString(_T("�ϳ���������"));
	}
}



//����λ��ȡ����Ʒ��Ϣ
//1 = ����
//2 = �·�
//7 = ����
//3 = ����
//6 = ��ָ
BOOL Gamecall::GetGoodsByEquipPos(DWORD pos, _BAGSTU* goods)
{
	std::vector<_BAGSTU> EquiVec;
	GetAllBodyEquipToVector(EquiVec);
	
	for(unsigned i = 0; i < EquiVec.size(); i++)
	{
		if(EquiVec[i].m_Info == pos)
		{
			*goods = EquiVec[i];
			return TRUE;
		}
	}
	
	return FALSE;
}

//��������ȡ����Ʒ��Ϣ
BOOL Gamecall::GetGoodsFromBagByName(const wchar_t *name, std::vector<_BAGSTU> &GoodsVec) 
{
	assert(name != NULL);
	
	std::vector<_BAGSTU> AllGoods;
	GetAllGoodsToVector(AllGoods);
	
	BOOL isHave = FALSE;
	for(unsigned i = 0; i < AllGoods.size(); i++)
	{
		if(wcscmp(name, AllGoods[i].name) == 0)
		{
			isHave = TRUE;
			GoodsVec.push_back(AllGoods[i]);
		}
	}
	
	
	return isHave;
}

//��������ȡ����Ʒ��Ϣ
//���������ר���Һ������ֵ�
//������Ƕ����ֵ�ƥ����
BOOL Gamecall::GetGoodsByName_Hezi(wchar_t *name, std::vector<_BAGSTU> &GoodsVec) 
{
	
	assert(name != NULL);
	
	
	int len = wcslen(name);
	wchar_t* fixName = new wchar_t[len + 1];
	wcscpy(fixName, name);
	fixName[len] = L' ';
	fixName[len + 1] = L'\0';
	
	
	std::vector<_BAGSTU> AllGoods;
	GetAllGoodsToVector(AllGoods);
	BOOL isHave = FALSE;
	for(DWORD i = 0; i < AllGoods.size(); i++)
	{
		if(wcsstr(AllGoods[i].name, fixName) != NULL)
		{
			
			isHave = TRUE;
			GoodsVec.push_back(AllGoods[i]);
		}
	}
	
	//�������ֹ���, ���� 8, 5, 3, 1
	if(isHave)
	{
		
		for(DWORD i = 0; i < GoodsVec.size(); i++)
		{
			
			if(wcschr(GoodsVec[i].name, L'3') != NULL)
			{
				_BAGSTU temp = GoodsVec[i];
				GoodsVec.erase(GoodsVec.begin() + i);
				GoodsVec.insert(GoodsVec.begin(), temp);
			}
			else if(wcschr(GoodsVec[i].name, L'5') != NULL)
			{
				_BAGSTU temp = GoodsVec[i];
				GoodsVec.erase(GoodsVec.begin() + i);
				GoodsVec.insert(GoodsVec.begin(), temp);
			}
			else if(wcschr(GoodsVec[i].name, L'8') != NULL)
			{
				_BAGSTU temp = GoodsVec[i];
				GoodsVec.erase(GoodsVec.begin() + i);
				GoodsVec.insert(GoodsVec.begin(), temp);
			}
		}
		
	}
	
	
	return isHave;
}

//��������ȡ��Ʒ��Ϣ
BOOL Gamecall::GetGoodsFromEquipByName(wchar_t *name, _BAGSTU *goods)
{
	
	assert(name != NULL);
	
	
	
	std::vector<_BAGSTU> EquiVec;
	GetAllBodyEquipToVector(EquiVec);
	
	for(DWORD i = 0; i < EquiVec.size(); i++)
	{
		if(wcscmp(name, EquiVec[i].name) == 0)
		{
			*goods = EquiVec[i];
			return TRUE;
		}
		
	}
	
	
	return FALSE;
}


//��������ȡ����Ʒ��Ϣ
BOOL Gamecall::GetGoodsFromBagByName(const wchar_t *name, _BAGSTU *goods)      
{
	assert(name != NULL);
	
	std::vector<_BAGSTU> GoodsVec;
	GetAllGoodsToVector(GoodsVec);
	
	//��������
	for(DWORD i = 0; i < GoodsVec.size(); i++)
	{
		if(wcscmp(name, GoodsVec[i].name) == 0)
		{
			*goods = GoodsVec[i];
			return TRUE;
		}
	}
	
	return FALSE;
}

//��ʼ�����
//�������Ӧ�ô���ֱ�ע�뿪ʼ�͵���
//�ȴ���Ϸ���ڽ���
//�ȴ�Э��˵��, ���ȥ
//�ȴ���ɫѡ�����, ���ȥ
//�ȴ�����
//ҡ��
//�ص�ҡ��
//����1: ʹ�õڼ�����ɫ������Ϸ
void Gamecall::SetIniPath(TCHAR* szPath)
{
	_tcscpy(m_szConfigPath, szPath);
}


//����ʬ��
void Gamecall::PickdownBody() 
{
	__try
	{
		__asm
		{
			mov eax,obj_enum_base;
			mov eax,[eax];
			mov eax,[eax+ pickdown_body_offset1];
			mov eax,[eax+pickdown_body_offset2];
			mov eax,[eax+pickdown_body_offset3];
			add eax, pickdown_body_offset4;
			push eax;
			mov ecx, pickdown_body_offset5;
			mov eax,pickdown_body_call;
			call eax;
		}
	}
	__except(1)
	{
		TRACE(_T("����ʬ��"));
	}
}


void Gamecall::InitSpeed()
{
	//�ȼ������DLL
	m_hack = GetModuleHandle(_T("speedhack-i386"));
	if(m_hack == NULL)
	{
		log.logdv(_T("load speedhack-i386 err: %d"), GetLastError());
		return;
	}
	
	
	HMODULE hWinmm = GetModuleHandle(_T("Winmm"));
	BYTE* pfntimeGetTime = (BYTE *)GetProcAddress(hWinmm, "timeGetTime");
	
	
	m_pfnInitSpeed = (_InitializeSpeedhack)GetProcAddress(m_hack, "InitializeSpeedhack");
	int *realGetTickCount = (int *)GetProcAddress(m_hack, "realGetTickCount");
	int *realQueryPerformance = (int *)GetProcAddress(m_hack, "realQueryPerformanceCounter");
	
	int *ce_gettickcount = (int *)GetProcAddress(m_hack, "speedhackversion_GetTickCount");
	int *ce_querytime = (int *)GetProcAddress(m_hack, "speedhackversion_QueryPerformanceCounter");
	
	
	HMODULE hKernel = GetModuleHandle(_T("Kernel32"));
	DWORD GetTickCount_addr = (DWORD)GetProcAddress(hKernel, "GetTickCount");
	DWORD Query_addr = (DWORD)GetProcAddress(hKernel, "QueryPerformanceCounter"); 
	
	
	ce_hooktimeGetTime.Init((void *)pfntimeGetTime, ce_gettickcount, FALSE);
	ce_hookGetTickCount.Init((void *)GetTickCount_addr, ce_gettickcount, FALSE);
	ce_hookQueryPerformanceCounter.Init((void *)Query_addr, ce_querytime, FALSE);
	
	
	if(*realGetTickCount == 0)
	{
		ce_hooktimeGetTime.hook();
		void *result1 = ce_hookGetTickCount.hook();
		*realGetTickCount = (DWORD)result1;
		
		
	}
	
	if(*realQueryPerformance == 0)
	{
		void *result2 = ce_hookQueryPerformanceCounter.hook();
		*realQueryPerformance = (DWORD)result2;
	}
	
}


//��¼��Ϸ, �����ǵ�¼�Ľ�ɫ
BOOL Gamecall::LoginInGame(DWORD index)
{
	//���ж�����Ƿ��Ѿ�����Ϸ��
	
	if(isLoadingMap() != 3)
	{
		
		ConfirmAgreement();	//ȷ����Ϸʹ��Э��
		LoginGame(index);		//������Ϸ
		WaitPlans();		//�ȴ�����
		//CloseAttendance();	//�ص��ϻ���
	}
	
	//SetMouseMode();			//TODO: ��ʱ������
	
	
	return TRUE;
}



void __stdcall ShunyiQietu()
{
	

	__asm
	{
		leave;
		retn 12;
	}
}


//��ʼ������
//�ӹ����ڴ��������ļ��ű�·��
//��ʼ������, �ȴ���Ϸ���ڴ���
//��ʼ��һ�����Ӻ�һ����Ϸģ�������
BOOL Gamecall::Init()
{
	try
	{
		
		BOOL bGetShareMem = FALSE;
		if(g_share.Create(0, SHAREOBJNAME)){
			//Sleep(2000);
			m_pShareMem = g_share.Get(GetCurrentProcessId());
			if(m_pShareMem){
				bGetShareMem = TRUE;
			}
			
		}
		
		if(bGetShareMem == FALSE){
			TRACE(_T("û�ܳ�ʼ���������"));
			return FALSE;
		}


		//�����ļ�·��
		GetModuleFileName(GetModuleHandle(_T("JLwg")), m_szConfigPath, MAX_PATH);
		PathRemoveFileSpec(m_szConfigPath);
		
		//ģ���·��
		TCHAR szExePath[MAX_PATH] = {0};
		_tcscpy(szExePath, m_szConfigPath);


		//�����ļ�·��
		PathAppend(m_szConfigPath, _T("����"));
		if(PathFileExists(m_szConfigPath) == FALSE){
			_wmkdir(m_szConfigPath);
		}
		
		//˳���·��
		_tcscpy(m_szLujingPath, szExePath);
		PathAppend(m_szLujingPath, _T("·��"));
		if(PathFileExists(m_szLujingPath) == FALSE){
			_wmkdir(m_szLujingPath);
		}
		
		//¼��˲�Ƶ�Ĭ��·��
		_tcscpy(m_szLujingTest, m_szLujingPath);
		PathAppend(m_szLujingTest, _T("test.bin"));
		

		//Ĭ�������ļ���·��
		TCHAR szConfigTemp[MAX_PATH] = {0};
		CString strConfig = m_pShareMem->szConfig;
		_tcscpy(szConfigTemp, (LPCTSTR)strConfig);
		_tcscat(szConfigTemp, _T(".ini"));
		PathAppend(m_szConfigPath, szConfigTemp);
		
		//��������ļ�������
		if(PathFileExists(m_szConfigPath) == FALSE){
			FILE* configFile = _tfopen(_T("default.ini"), _T("w+"));
			if(configFile == NULL){
				TRACE(_T("���������ļ�ʧ��"));
				return FALSE;
			}
			
			WORD hdr = 0xfeff;
			if(fwrite(&hdr, 1, sizeof(WORD), configFile) != sizeof(WORD)){
				return FALSE;
			}

			fclose(configFile);

		}
		
		
		log.logdv(_T("%s"), m_szConfigPath);
		log.logdv(_T("%s"), m_szLujingTest);
		
		
		WaitGameCreate();	//�ȴ���Ϸ����
		InitSpeed();		//��ʼ������
		hookQietu.Init((void *)hook_dont_leave_dungeons, ShunyiQietu);
		//��ȡ���ص���Ϸdll�ĵ�ַ
		m_hModuleBsEngine = GetModuleHandle(_T("bsengine_Shipping"));
		
		
		return TRUE;
	}
	catch(...){
		log.logdv(_T("%s Error!"), FUNCNAME);
	}
	
	return FALSE;
}


//������ui
BOOL Gamecall::SortBag()
{
	__try
	{
        UIOperator uiOp;
	    DWORD UIAddr = 0;
		GetUIAddrByName(L"Inventory2Panel", &UIAddr);
		
		uiOp.pAddr = (DWORD *)UIAddr;
		uiOp.c5 = *(DWORD *)(UIAddr + bag_refresh_c5);
		sendcall(id_msg_clickui, &uiOp);

        return TRUE;
	}
	__except(1)
	{
		TRACE(FUNCNAME);
	}
	
	return FALSE;
}

//��ֿ�
//����1: �����еĸ�����
void Gamecall::CunCangku(_BAGSTU &goods)
{
	
	int value = goods.m_Info;
	value <<= 16;
	value += package;
	
	__try
	{
		__asm
		{
			push -1;
			push 0;
			mov eax, value;
			push eax;
			mov eax, bag_cuncang_call;
			call eax;
			
		}
		
	}
	__except(1)
	{
		OutputDebugString(FUNCNAME);
	}
	
}


//�ϳ�������10
void Gamecall::HeChengWuQi_Po10(DWORD zhu,DWORD fu,DWORD adress) 
{
	
	log.logdv(_T("%s: %08x, %08x"), FUNCNAME, zhu, fu);
	
	
	YouJianLeiXing LeiXing;
	LeiXing.canshu1 = fu;
	LeiXing.canshu2 = 0;
	LeiXing.canshu3 = 0;
	LeiXing.canshu4 = 0;
	
	_try
	{
		_asm
		{
			push 0;
			push 0;
			push 1;
			lea eax,LeiXing;
			push eax;
			push 0;
			mov eax,zhu;
			push eax;
			push 0;
			mov eax,adress;
			push eax;
			
			mov eax,obj_enum_base;
			mov eax,[eax];
			mov eax,[eax+hewuqi_po10_offset1];
			mov eax,[eax+hewuqi_po10_offset2];
			mov ecx,[eax+hewuqi_po10_offset3];
			push ecx;
			mov eax,hewuqi_po10_call;
			call eax;
		}
	}
	_except(1)
	{
		TRACE(_T("�ϳ�������10����"));
	}
}



void Gamecall::HeChengWuQi_Po5(_BAGSTU &zhu, _BAGSTU &fu) //�ϳ�������5
{
	
	int zhu_value = zhu.m_Info;
	zhu_value <<= 16;
	zhu_value += body;
	
	int fu_value = fu.m_Info;
	fu_value <<= 16;
	fu_value += package;
	
	
	
	log.logdv(_T("%s: %08x, %08x"), FUNCNAME, zhu, fu);
	
	
	__try
	{
		__asm
		{
			push 0;
			push 0;
			push 0;
			mov eax,fu_value;
			push eax;
			push 0;
			mov ecx,zhu_value;
			push ecx;
			mov eax,obj_enum_base;
			mov eax,[eax];
			mov eax,[eax+hewuqi_po5_offset1];
			mov eax,[eax+hewuqi_po5_offset2];
			mov ecx,[eax+hewuqi_po5_offset3];
			mov eax,hewuqi_po5_call;
			call eax;
		}
	}
	__except(1)
	{
		OutputDebugString(_T("�ϳ�������5����"));
	}
}


//�ж���Ϸ�����Ƿ񴴽�
HWND Gamecall::isGameWndCreated(DWORD dwPid)
{
	HWND hGameWnd = FindWindowEx(NULL, NULL, _T("LaunchUnrealUWindowsClient"), NULL);
	
	if(hGameWnd == NULL)
	{
		//û���ҵ�
		return NULL;
	}
	
	//�ж���Ϸ���ڴ������
	for(;;)
	{
		DWORD dwWndOfPid;
		GetWindowThreadProcessId(hGameWnd, &dwWndOfPid);
		
		if(dwPid == dwWndOfPid)
		{
			//�ҵ���, ����
			m_hGameWnd = hGameWnd;
			return hGameWnd;
		}
		
		hGameWnd = FindWindowEx(NULL, hGameWnd, _T("LaunchUnrealUWindowsClient"), NULL);
		if(hGameWnd == NULL)
		{
			return NULL;
		}
	}
}


void Gamecall::_GetAcceptedQuestToVector(std::vector<Quest> &QuestVec)
{
    int TaskNum = 53;
    
    DWORD pStartAddr = GetTaskStartAddr();  //��ȡ����ʼ��ַ
    Quest qst;
    
    for(int i = 0; i < TaskNum; i++)
    {
        //DWORD *pAddr        =     gcall.GetTaskPresentAddr(i, pStartAddr);  //��õ�ǰ�����ַ
        qst.id = GetTaskID(i, pStartAddr);  //��õ�ǰ����ID
        qst.name_id = GetTaskNameID(i, pStartAddr);  //��õ�ǰ��������ID
        qst.step = GetPresentTaskIndexes(i, pStartAddr);  //��õ�ǰ�����ڼ���С����
        qst.endflag = GetPresentTaskEndFlag(i, pStartAddr, qst.step);  //��õ�ǰС���������־
        qst.num = GetPresentTaskNum(i, pStartAddr, qst.step);  //��õ�ǰС�����Ѿ���Ĺ�����
        qst.name = GatTaskName(qst.name_id);//��ȡ��ǰ�ѽ���������
        
        if(qst.name)
        {
            QuestVec.push_back(qst);
        }
        else
        {
            //�������
            break;
        }
	}
}

void Gamecall::GetAcceptedQuestToVector(std::vector<Quest> &QuestVec)
{
    sendcall(id_msg_GetAcceptedQuestToVector, &QuestVec);
}


/*��Χ��������������Ļ���ַ*/
ObjectNode* Gamecall::GetObjectBinTreeBaseAddr()
{
	ObjectNode *Note = NULL;
	__try
	{
		
		int temp2 = obj_enum_offset2 + 4;
		
		__asm
		{
			mov eax, obj_enum_base;
			mov eax, [eax];
			mov eax, [eax + obj_enum_offset1];
			mov ebx, temp2;
			mov eax, [eax + ebx];
			mov eax, [eax + obj_enum_offset3];
			
			mov Note, eax;
		}
	}
	__except(1)
	{
		OutputDebugString(FUNCNAME);
	}
	
	/*ȡ����, ������*/
	return Note;
}



wchar_t* Gamecall::GetPlayerName()
{
	DWORD PlayerInfo = GetPlayerDataAddr();
	wchar_t *PlayerName = NULL;
	
	__try
	{
		__asm
		{
			mov eax, PlayerInfo;
			mov eax, [eax + player_name_offset];
			
			mov PlayerName, eax;
		}
	}
	__except(1)
	{
		OutputDebugString(FUNCNAME);
	}
	return PlayerName;
}


//��ɫID
DWORD Gamecall::GetPlayerID()
{
	DWORD PlayerInfo = GetPlayerDataAddr();
	DWORD PlayerID = UINT_MAX;
	
	__try
	{
		__asm
		{
			mov eax, PlayerInfo;
			mov eax, [eax + player_id1];
			
			mov PlayerID, eax;
		}
	}
	__except(1)
	{
		OutputDebugString(FUNCNAME);
	}
	return PlayerID;
}

//ȡ��������ݵ�ַ�ĸ�������
DWORD Gamecall::GetPlayerDataAddr()
{
	DWORD PlayerInfo = UINT_MAX;
	
	__try
	{
		__asm
		{
			mov eax, player_base;
			mov eax, [eax];
			mov eax, [eax + player_offset1];
			mov eax, [eax + player_offset2];
			
			mov PlayerInfo, eax
		}
	}
	__except(1)
	{
		OutputDebugString(FUNCNAME);
	}
	
	return PlayerInfo;
}


//ȡ���������
BOOL Gamecall::GetPlayerPos(fPosition* PlayerPosition)
{
	DWORD PlayerInfo = GetPlayerDataAddr();
	
	__try
	{
		__asm
		{
			mov eax, PlayerInfo;
			mov eax, [eax + player_steppos_x_offset1];
			add eax, player_steppos_x_offset2;
			
			mov edx, eax; /*����һ��*/
			mov eax, [edx];
				
			mov ebx, PlayerPosition;
			mov[ebx]PlayerPosition.x, eax;   //0x3ce4
			
			add edx, 4;
			mov eax, [edx];
			mov[ebx]PlayerPosition.y, eax;  //0x3ce8
			
			add edx, 4;
			mov eax, [edx];
			mov[ebx]PlayerPosition.z, eax; //0x3cec
		}
		
		return TRUE;
	}
	__except(1)
	{
		OutputDebugString(FUNCNAME);
	}
	
	
	
	return FALSE;
}


//ȡ���������
BOOL Gamecall::GetPlayerPos2(sPosition* PlayerPosition)
{
	DWORD PlayerInfo = GetPlayerDataAddr();
	
	
	__try
	{
		__asm
		{
			mov edx, PlayerInfo;
			mov eax, [edx + player_pos2_x];
			
			mov ebx, PlayerPosition;
			mov[ebx]PlayerPosition.x, ax;
			
			mov eax, [edx + player_pos2_y + 2];
			mov[ebx]PlayerPosition.y, ax;
			
			mov eax, [edx + player_pos2_y + 4];
			mov[ebx]PlayerPosition.z, ax;
		}
		
		return TRUE;
	}
	__except(1)
	{
		OutputDebugString(FUNCNAME);
	}
	
	return FALSE;
}



//�������Ṧ
float Gamecall::GetPlayerMaxVit()
{
	DWORD PlayerInfo = GetPlayerDataAddr();
	float PlayerVit;
	
	__try
	{
		__asm
		{
			mov eax, PlayerInfo;
			mov eax, [eax + player_name_qinggong_offset1];
			mov eax, [eax + player_name_qinggong_offset2 + 4];
			
			mov PlayerVit, eax;
		}
	}
	__except(1)
	{
		OutputDebugString(FUNCNAME);
	}
	return PlayerVit;
}

//����Ṧ
float Gamecall::GetPlayerVit()
{
	DWORD PlayerInfo = GetPlayerDataAddr();
	float PlayerVit;
	
	__try
	{
		__asm
		{
			mov eax, PlayerInfo;
			mov eax, [eax + player_name_qinggong_offset1];
			mov eax, [eax + player_name_qinggong_offset2+0x8];
			
			mov PlayerVit, eax;
		}
	}
	__except(1)
	{
		OutputDebugString(FUNCNAME);
	}
	return PlayerVit;
}


//ȡ���������
UCHAR Gamecall::GetPlayerMana()
{
	DWORD PlayerInfo = GetPlayerDataAddr();
	UCHAR Vit = UCHAR_MAX;
	
	__try
	{
		__asm
		{
			mov eax, PlayerInfo;
			mov eax, [eax + 0xf4];
			
			mov Vit, al;
		}
	}
	__except(1)
	{
		OutputDebugString(FUNCNAME);
	}
	
	return Vit;
}

/*����Ṧ״̬
1, ʹ�����Ṧ
2, �Ṧ���ڻָ�
3, �Ṧ�Ѿ���*/
int Gamecall::GetPlayerVitStatus()
{
	int status = INT_MAX;
	
	DWORD PlayerInfo = GetPlayerDataAddr();
	
	__try
	{
		__asm
		{
			mov eax, PlayerInfo;
			mov eax, [eax + 0x14];
			
			add eax, 0x24c;
			mov status, eax;
		}
	}
	__except(1)
	{
		OutputDebugString(FUNCNAME);
	}
	return status;
}


//��ȡ��ɫ���Ѫֵ
DWORD Gamecall::GetPlayerMaxHealth() 
{	
	DWORD wMaxBlood;
	DWORD wMaxBlood1;
	
	DWORD m_Adress = GetPlayerDataAddr();
	wMaxBlood = 0;
	wMaxBlood1 = 0;
	__try
	{
		if ( m_Adress )
		{
			wMaxBlood = ReadDWORD(m_Adress + player_max_health);
			wMaxBlood1 = ReadDWORD(m_Adress + player_bagua_health);
			wMaxBlood = wMaxBlood + wMaxBlood1;
		}	
	}
	__except(1)
	{
		OutputDebugString(FUNCNAME);
	}
	
	return wMaxBlood;
}


//��ҵ�ǰѪ��
DWORD Gamecall::GetPlayerHealth()
{
	DWORD Health = UINT_MAX;
	DWORD PlayInfo;
	
	PlayInfo = GetPlayerDataAddr();
	
	__try
	{
		__asm
		{
			mov eax, PlayInfo;
			mov eax, [eax + player_cur_health];
			
			mov Health, eax;
		}
	}
	__except(1)
	{
		OutputDebugString(FUNCNAME);
	}
	
	return Health;
}

void* Gamecall::GetStepCallAddr()
{
	void *pCall = NULL;
	
	__try
	{
		__asm
		{
			mov eax, step_call_base;
			mov eax, [eax];
			call eax;  //�߲�
			
			mov edx, [eax];
			mov ecx, eax;
			mov eax, [edx + step_call_offset1];
			mov pCall, eax;
		}
	}
	__except(1)
	{
		OutputDebugString(FUNCNAME);
	}
	
	return pCall;
}

//��·
void Gamecall::Step(float x, float y, float z)
{
	
	__try
	{
		void *pCall = GetStepCallAddr();
		__asm
		{
			push z;
			push y;
			push x;
			call pCall;
		}
	}
	__except(1)
	{
		OutputDebugString(FUNCNAME);
	}
	
}

//��·3��
void Gamecall::Step3x(float x, float y, float z)
{

	__try
	{
		void *pCall = GetStepCallAddr();
		__asm
		{
			push z;
			push y;
			push x;
			call pCall;
		}
		Stepto3x();
	}
	__except(1)
	{
		OutputDebugString(FUNCNAME);
	}

}


//ת��
void Gamecall::Turn(int angle)
{
	
	
	DWORD addr = (DWORD)m_hModuleBsEngine + SHENXINGBAIBIANCHAZHI;
	
	
	__try
	{
		__asm
		{
			mov eax, addr;
			mov eax, [eax];
			mov eax, [eax + viewpoint_offset1];
			mov eax, [eax];
			mov eax, [eax + viewpoint_offset3];
			mov eax, [eax + viewpoint_offset4];
			add eax, viewpoint_offset5;
			
			mov ebx, angle;
			mov[eax], ebx;
		}
	}
	__except(1)
	{
		OutputDebugString(FUNCNAME);
	}
}

//��ö�������
//type = 0x20 ������Ʒ
//type = 0x4  ���� npc
//type = 0xb0 ʬ��͵�����Ʒ,
BYTE Gamecall::GetObjectType(DWORD pObjAddress)
{
	DWORD Objtype = 0;
	
	__try
	{
		//Objtype = ReadDWORD(pObjAddress+obj_type_offset);
		if(!IsBadReadPtr((void*)pObjAddress, sizeof(DWORD)))
		{
			__asm
			{
				mov eax, pObjAddress;
				mov eax, [eax + obj_type_offset];
				mov Objtype, eax;
			}
		}
	}
	__except(1)
	{
		//log.logdv(_T("GetObjectType-error:%d"),pObjAddress);
		OutputDebugString(FUNCNAME);
		return 0;
	}
	
	return (BYTE)Objtype;
}



BOOL Gamecall::GetObjectPos(ObjectNode* pNode, fPosition* fpos)
{
	
	DWORD type = (DWORD)GetObjectType(pNode->ObjAddress);
	if(type == 0x20){
		GetObjectPos2_0x20(pNode->ObjAddress, fpos);
	}
	else if(type == 0xb0){
		sPosition spos;
		GetObjectPos_0xb(pNode->ObjAddress, &spos);
		*fpos = ShortPosToFloatPos(spos);
	}
	else if(type == 0x4){
		_GetObjectPos(pNode->ObjAddress, fpos);
	}
	else{
		return FALSE;
	}
	
	return TRUE;
}


//��������
//����1: ����ַ
//����4���ƶ�����
BOOL Gamecall::_GetObjectPos(DWORD pObjAddress, fPosition* pos)
{

	BOOL bRet = FALSE;	
	__try
	{
		
		int temp1 = obj_type4_pos_x_offset2 + 4;
		int temp2 = obj_type4_pos_x_offset2 + 8;
		
		
		__asm
		{
			mov eax, pObjAddress;
			mov eax, [eax + obj_type4_pos_x_offset1];
			mov ecx, eax;
			
			mov eax, [ecx + obj_type4_pos_x_offset2];
			
			
			mov ebx, pos;
			mov [ebx]pos.x, eax;
			
			mov eax, temp1;
			mov eax, [ecx + eax];
			mov [ebx]pos.y, eax;
			
			mov eax, temp2;
			mov eax, [ecx + eax];
			mov [ebx]pos.z, eax;
		}

		bRet = TRUE;
	}
	__except(1)
	{
		pos->x = -1;
		pos->y = -1;
		pos->z = -1;
	}
	
	return bRet;
}



//��������2, ���Ǹ�������
//����������0x20�������ȡ����
//ȡ�������Ǹ�������
//����1: ����ַ
BOOL Gamecall::GetObjectPos2_0x20(DWORD pObjAddress, fPosition* pos)
{
	BOOL bRet = FALSE;	
	__try
	{
		__asm
		{
			mov edx, pObjAddress;
			mov eax, [edx + 0x28];
			
			mov ebx, pos;
			mov[ebx]pos.x, eax;
			
			mov eax, [edx + 0x2c];
			mov[ebx]pos.y, eax;
			
			mov eax, [edx + 0x30];
			mov[ebx]pos.z, eax;
		}
		
		//*4��� ��ɫ��������ͬ��
		pos->x = pos->x * 4;
		pos->y = pos->y * 4;
		pos->z = pos->z * 4;

		bRet = TRUE;
	}
	__except(1)
	{
		pos->x = -1;
		pos->y = -1;
		pos->z = -1;
	}
	
	return bRet;
}

//��������2, ������������
//����1: ����ַ
BOOL Gamecall::GetObjectPos_0xb(DWORD pObjAddress, sPosition* spos)
{
	BOOL bRet = FALSE;	
	__try
	{
		__asm
		{
			mov edx, pObjAddress;
			mov eax, [edx +  ojb_typeb0_pos2_x];
			
			mov ebx, spos;
			mov[ebx]spos.x, ax;
			
			mov eax, [edx + ojb_typeb0_pos2_x + 2];
			mov[ebx]spos.y, ax;
			
			mov eax, [edx + ojb_typeb0_pos2_x + 4];
			mov[ebx]spos.z, ax;
		}

		bRet = TRUE;
	}
	__except(1)
	{
		spos->x = -1;
		spos->y = -1;
		spos->z = -1;
	}
	
	return bRet;
}

/*
��ö��������
����1: ���������
*/
wchar_t* Gamecall::GetObjectNameByIndex(DWORD index)
{
	
	if(index == UINT_MAX)
	{
		return NULL;
	}
	
	wchar_t *name;
	
	__try
	{
		__asm
		{
			mov eax, obj_name_call_base;
			mov eax, [eax];
			mov ecx, [eax + obj_name_call_offset1];  // 0x26FC
			mov edx, [ecx];
			mov edx, [edx + obj_name_call_offset2];
			
			push 0;
			push index;
			call edx;
			mov eax, [eax + 0x18]; //TODO: 
			mov name, eax;
		}
	}
	__except(1)
	{
		name = NULL;
	}
	
	return name;
}

//��ȡ�����Ѫ��
//����1: �����ַ
DWORD Gamecall::GetType4HP(DWORD pObjAddress)
{
	DWORD hp;
	
	__try
	{
		__asm
		{
			mov eax, pObjAddress;
			mov eax, [eax + obj_type4_health];
			mov hp, eax;
		}
	}
	__except(1)
	{
		hp = ULONG_MAX;
	}
	
	return hp;
}


//�̶�ƫ��
DWORD Gamecall::GetObject_0x14(DWORD pObjAddress)
{
	DWORD temp;
	temp = 0;

	__try
	{
		temp = ReadByte(pObjAddress+0x14);
	}
	__except(1)
	{
		temp = ULONG_MAX;
	}

	return temp;
}

//����ȼ�
DWORD Gamecall::GetObjectLevel(DWORD pObjAddress)
{
	DWORD level;
	
	__asm
	{
		mov eax, pObjAddress;
		mov eax, [eax + 0x09c];
		mov level, eax;
	}
	
	return level;
}


//��Ծ
void Gamecall::TiaoYue() 
{
	
	DWORD addr = (DWORD)m_hModuleBsEngine + SHENXINGBAIBIANCHAZHI;
	
	__try
	{
		__asm
		{
			mov eax, addr;
			mov eax, [eax];
			mov eax, [eax + tiaoyue_offset1];
			mov eax, [eax];
			mov eax, [eax + tiaoyue_offset3];
			mov esi, [eax + tiaoyue_offset4];
			mov eax, [esi];
			mov edx, [eax + 0x3FC]; //TODO: ��Ծ��5��ƫ��
			mov ecx,esi;
			call edx;
			
		}
	}
	_except(1)
	{
		TRACE(_T("��Ծ����"));
	}
}


//˲��
void Gamecall::ZOULUSHUNYI(DWORD *adress,DWORD adrewss)
{
	__try
	{
		_asm
		{
			
            push shunyi_offset1;
			push shunyi_offset1;
			
			mov eax,obj_enum_base;
			mov eax,[eax];
			mov eax,[eax+shunyi_offset3 ];
			mov eax,[eax+shunyi_offset4];
			mov eax,[eax+shunyi_offset5];
			add eax,  shunyi_offset6 ;
			mov ecx,[eax+ shunyi_offset7];
			
			
			mov eax,adress;
			mov [eax+ shunyi_offset7],cx;
			
			push eax;
			
			
			mov eax,  shunyi_call;
			call eax;
		}
	}
	__except(1)
	{
		TRACE(_T("˲�Ƴ���"));
	}
}



//����
//����1: ����id
void Gamecall::Attack(int id)  //���ܹ���  ������Ǽ���ID
{
	__try
	{
		__asm
		{
			mov eax, id;
			push eax;
			mov eax, obj_enum_base;
			mov eax, [eax];
			mov eax, [eax + attack_offset1];
			mov eax, [eax + attack_offset2];
			mov eax, [eax + attack_offset3];
			push eax;
			mov eax, attack_call;
			call eax;
		}
		
	}
	__except(1)
	{
		OutputDebugString(FUNCNAME);
	}
}

//ȡ�ü��ܻ���ַ
Tree* Gamecall::GetUIBinTreeBaseAddr()
{
	Tree* Addr = NULL;
	__try
	{
		
		__asm
		{
			mov eax, ui_enum_base;
			mov eax, [eax];
			mov eax, [eax + ui_enum_offset1];
			mov eax, [eax + ui_enum_offset2 + 4];
			mov eax, [eax + ui_enum_offset3 + 4];
			mov eax, [eax + ui_enum_offset4];
			
			mov Addr, eax;
			mov eax, [eax];
		}
	}
	__except(1)
	{
		OutputDebugString(FUNCNAME);
	}
	
	return Addr;
}

//��ǰ��·�Ƿ���Ч
BOOL Gamecall::isHaveXianlu(int index)
{
	int value = index * xianlu_count_array_size;
	int result = 0xffffffff;
	
	
	DWORD uiAddr = 0;
	GetUIAddrByName(L"AreaInfoPanel", &uiAddr);
	
	if(uiAddr == 0){
		log.logdv(_T("isHaveXianlu ��ȡui��ַʧ��"));
		return FALSE;
	}
	
	__try
	{
		__asm
		{
			mov eax, uiAddr;
			add eax, xianlu_count_offset1;
			mov ebx, value;
			mov eax, [eax + ebx];
			mov result, eax;
		}
	}
	__except(1)
	{
		OutputDebugString(FUNCNAME);
	}
	
	return (result != 0xffffffff);
}

//�رնԻ��򴰿�CALL
//����1: ui��ַ
//����2: c5����

void Gamecall::GuanBiDuiHuaKuangChuanKou(DWORD adress, DWORD adress1)
{

	KONGJ kj;
	kj.canshu1 = GUANBICHUANGKOUCALL_JIEGOUTOU;
	kj.canshu2 = 0x0;
	kj.canshu3 = 0x5468B3C2;
	kj.canshu4 = 0x0;
	kj.canshu5 = adress1;      //�ؼ����׵�ַ+0x40
	kj.canshu6 = 0x1;
	kj.canshu7 = 0x2;
	kj.canshu8 = 0x0;
	kj.canshu9 = 0x0;
	kj.canshu10 = 0x0;
	kj.canshu11 = 0x0;
	kj.canshu12 = 0x4EFE0016;
	
	
	__try
	{
		__asm
		{
			mov ecx, adress; //����ǿؼ����׵�ַ "TalkControlPanel"
			mov edx, [ecx];
			mov eax, [edx + 0x4];
			
			lea ebx, kj;
			push ebx;
			
			call eax;
	
		}
	}
	__except(1)
	{
		OutputDebugString(FUNCNAME);
	}
}





//��ȡ��·����
DWORD Gamecall::GetXianluNums()
{
	
	OpenXianluUI();
	Sleep(2000);
	
	
	int count = 0;
	for(int i = 0; i < 30; i++)
	{
		if(isHaveXianlu(i))
		{
			count++;
		}
		else
		{
			break;
		}
	}
	
	return count;
}

//ȡ��һ����������
//����1: ���ĵ�ַ
wchar_t* Gamecall::GetUIName(DWORD pBarAddr)
{
	if(pBarAddr == NULL){
        log.logdv(_T("GetUIName: ���� = NULL"));
        return NULL;
    }
	
	wchar_t *name;
	__try{
		__asm{
			mov eax, pBarAddr;
			mov eax, [eax + 0x0c];
			
			mov name, eax;
			mov eax, [eax];  //��������Ƿ�ɶ�
		}
	}
	__except(1){
		name = NULL;
	}
	
	return name;
}

//�жϽ�ɫ�Ƿ���·��
// == 1 ������·��
// == 0 ������·��
BOOL Gamecall::isPlayerSteping()
{
	DWORD playerdata = GetPlayerDataAddr();
	
	UCHAR state = false;
	__try{
		__asm{
			mov eax, playerdata;
			mov eax, [eax + player_status_step_offset1];
			mov eax, [eax + player_status_step_offset2];
			mov state, al;
		}
	}
	__except(1){
		OutputDebugString(FUNCNAME);
	}
	
	return (state == 1);
}

//[[[[0x0F9E11C]+0x34]+0x80]+744] == ��ɫ������·
UCHAR Gamecall::GetPlayerXianlu()
{
	
	UCHAR result = UCHAR_MAX;
	DWORD playerdata = GetPlayerDataAddr();
	__try{
		__asm{
			mov eax, playerdata;
			mov eax, [eax + player_xianlu_offset3];
			
			mov result, al;
		}
	}
	__except(1){
		OutputDebugString(FUNCNAME);
	}
	
	return result;
	
}


//����Ʒ�Ի��� 
//����1: npc����
//����ֵ: ItemStorePanel ui��ַ
BOOL Gamecall::OpenShangDian(wchar_t* name, DWORD* pUiAddr)
{
	
	//���жϴ�û��
	BOOL bOpen = FALSE;
	
	GetUIAddrByName(L"ItemStorePanel", pUiAddr);
	if(*pUiAddr == 0)
        return FALSE;
	
	
	//�ȴ������ж��̵��Ƿ��Ѿ���
	for(DWORD i = 0; i < 4; i++){
		
		if(*(DWORD *)(*pUiAddr + 0x88) == 0){
			
			ObjectNode *pNode = GetObjectByName(name);
			if(pNode == NULL){
				log.logdv(_T("%s: û���ҵ����NPC"), name);
				return FALSE;
			}
			
			PARAM_GUANSHANGDIAN temp;
			temp.argv1 = pNode->id;
			temp.argv2 = pNode->id2;
			
			sendcall(id_msg_DaKaiDuiHuaKuang, &temp);
			Sleep(1000);
			
		}
		else{
			bOpen = TRUE;
			break;
		}
		
		Sleep(500);
	}
	
	
	return bOpen;
}




//�ر��̵�
void Gamecall::CloseShangDian()
{
	UIOperator uiop;
	ZeroMemory(&uiop, sizeof(UIOperator));

	GetUIAddrByName(L"TalkControlPanel", (DWORD *)&uiop.pAddr);
	if(uiop.pAddr){
		uiop.c5 = *(DWORD *)((DWORD)uiop.pAddr + close_npc_c5);
		sendcall(id_msg_guanshangdian, &uiop);
		
		Sleep(2000);
	}
	else{
		log.logdv(_T("%s: ��ȡ�̵�UI��ַʧ��"), FUNCNAME);
	}
	
	return;
}



void Gamecall::SellItem(_BAGSTU &bag, DWORD adress)
{
	
	int value = bag.m_Info;
	value <<= 16;
	value += package;
	
	int nums = bag.m_Num;
	if(nums == 0)
		nums += 1;
	
	_try{
		_asm{
			mov eax, nums;
			push eax;
			push 0;
			mov eax, value;
			push eax;
			mov eax,adress;
			mov ebx,sell_call;
			call ebx;
		}
		
	}
	_except(1){
		TRACE(_T("����������"));
	}
}


//���ĳ��ui
//����1: ����ui�ṹ
BOOL Gamecall::ClickUI(UIOperator uiOp)
{
	
	DWORD *pAddr = uiOp.pAddr;
	DWORD c5 = uiOp.c5;
	
	BOOL bRet = false;
	
	KONGJ kj;
	kj.canshu1 = 0x0A010954;
	kj.canshu2 = 0x0;
	kj.canshu3 = 0x543CE1EB;
	kj.canshu4 = 0x0;
	kj.canshu5 = c5;
	kj.canshu6 = 0x1;
	kj.canshu7 = 0x2;
	kj.canshu8 = 0x0;
	kj.canshu9 = 0x0;
	kj.canshu10 = 0x0;
	kj.canshu11 = 0x0;
	kj.canshu12 = 0x4EFE0016;
	
	__try{
		__asm{
			mov ecx, pAddr; //����ǿؼ����׵�ַ
			mov edx, [ecx];
			mov eax, [edx + 0x4];
			
			lea ebx, kj;
			push ebx;
			
			/*mov eax,0x7BF600*/
			call eax
		}
		
		bRet = TRUE;
	}
	__except(1){
		OutputDebugString(FUNCNAME);
	}
	
	return bRet;
}

/*
ȡ�ù������ĵ�ַ
����1: bar�Ķ�������ʼ�ڵ��ַ
����2, ���� ������ �ĵ�ַ
*/
void Gamecall::GetStrikeBarBaseAddr(Tree *pBaseAddr, DWORD *pStrikeBarBaseAddr)
{
	if(pBaseAddr->p2 == 1)
	{
		return;
	}
	
	__try
	{
		wchar_t *name = GetUIName(pBaseAddr->Adress);
		if(name != NULL)
		{
			if(wcscmp(name, L"SkillBarPanel") == 0)
			{
				*pStrikeBarBaseAddr = (DWORD)pBaseAddr->Adress;
				return;
			}
		}
		
		
		
	}
	__except(EXCEPTION_EXECUTE_HANDLER)
	{
		
	}
	
	
	GetStrikeBarBaseAddr(pBaseAddr->Right, pStrikeBarBaseAddr);
	GetStrikeBarBaseAddr(pBaseAddr->Left, pStrikeBarBaseAddr);
}

//��ȡ��������
//����1: ����id
//����2: δ֪
void Gamecall::GetStrikeName(DWORD ID, DWORD IDD, STRIKENAME *pName)
{
	pName->canshu7 = 0x07;
	
	__try
	{
		__asm
		{
			mov ecx, obj_name_call_base;
			mov ecx, [ecx];
			mov ecx, [ecx + nums_strike_call_offset1];
			mov edx, [ecx];
			mov edx, [edx + nums_strike_call_offset2];
			mov eax, IDD;
			push eax;
			mov eax, ID;
			push eax;
			call edx;
			
			mov edi, eax;
			mov edx, [edi + 0x18];   //TODO �̶�
			mov ecx, [edi + 0x1C];	//TODO �̶�
			mov eax, IDD;
			push eax;
			
			mov eax, ID;
			push ID;
			push ecx;
			push edx;
			mov eax, pName;
			push eax;
			mov eax, nums_strike_call;
			call eax;
			add esp, 0x14;
		}
	}
	__except(1)
	{
		OutputDebugString(FUNCNAME);
	}
}



//ȡ�����Ƿ���ȴ  ����2 ˵������ȴ�� ����˵����һ�����������ڷ���
DWORD Gamecall::GetStrikeCD(int index, DWORD pAddr)
{
	DWORD value = UINT_MAX;
	__try
	{
		int temp = index * nums_strike_strcut_size;
		int temp2 = nums_strike_cd + 0x10;
		__asm
		{
			mov eax, pAddr;
			add eax, temp;
			add eax, temp2;
			
			mov eax, [eax];
			mov value, eax;
		}
	}
	__except(1)
	{
		OutputDebugString(FUNCNAME);
	}
	return value;
}

//ȡ�����Ƿ��Ѿ�����  �����0˵����û�н����ļ���  1 ˵�����Ѿ�������
DWORD Gamecall::isStrikeLocked(int index, DWORD pAddr)
{
	DWORD value = UINT_MAX;
	__try
	{
		int temp = index * nums_strike_strcut_size;
		int temp2 = nums_strike_islock + 0x10;
		__asm
		{
			mov eax, pAddr;
			add eax, temp;
			add eax, temp2;
			
			mov eax, [eax];
			mov value, eax;
		}
	}
	__except(1)
	{
		OutputDebugString(FUNCNAME);
	}
	return value;
}

//ȡ�����Ƿ����ʹ�� �����0˵����������ǿ���ʹ�õ�  2 ˵�����������Ȼ�Ѿ����� �����ǻ�����
DWORD Gamecall::isStrikeCanUse(int index, DWORD pAddr)
{
	DWORD value = UINT_MAX;
	__try
	{
		if ( pAddr != 0 )
		{
			value = ReadDWORD( pAddr + index*nums_strike_strcut_size + (nums_strike_canuse + 0x10) );
		}
		/*int temp = index * nums_strike_strcut_size;
		int temp2 = (nums_strike_canuse + 0x10);
		__asm
		{
		mov eax, pAddr;
		add eax, temp;
		add eax, temp2;

		mov eax, [eax];
		mov value, eax;
		}*/
	}
	__except(1)
	{
		OutputDebugString(FUNCNAME);
	}
	return value;
}

//���ݹ������ĵ�ַȡ�ü������ݵĿ�ʼ��ַ
DWORD Gamecall::GetStrikeStartAddr()
{
	DWORD StartAddr = 0;
	
	__try
	{
		DWORD StrikeStartAddr = 0;
		GetStrikeBarBaseAddr(GetUIBinTreeBaseAddr(), &StrikeStartAddr);
		
		assert(StrikeStartAddr != 0);
		
		__asm
		{
			mov eax, StrikeStartAddr;
			//add eax, 0x44;
			//mov eax, [eax];
			//mov eax, [eax + 0x24];
			add eax, 0x40;
			
			mov StartAddr, eax;
		}
		
	}
	
	__except(1)
	{
		OutputDebugString(FUNCNAME);
	}
	
	return StartAddr;
}

//ȡ����id1
//����1: ���ܵ�����, Ӧ������Ϸ�����е�����˳��
//����2: �������ݿ�ʼ��ַ
//
DWORD Gamecall::GetStrikeId1(int index, DWORD pStrikeStartAddr)
{
	DWORD id = UINT_MAX;
	int temp = index *nums_strike_strcut_size;
	
	__try
	{
		__asm
		{
			mov eax, pStrikeStartAddr;
			add eax, temp;
			add eax, nums_strike_strcut_id;
			mov eax, [eax];
			
			mov id, eax;
		}
	}
	__except(1)
	{
		OutputDebugString(FUNCNAME);
	}
	
	return id;
}

/*ȥ����id2
����1: ���ܵ�����, Ӧ������Ϸ�����е�����˳��
����2: �������ݿ�ʼ��ַ
*/
DWORD Gamecall::GetStrikeId2(int index, DWORD pStrikeStartAddr)  //ȡ����ID2
{
	DWORD id = UINT_MAX;
	int temp = index * nums_strike_strcut_size;
	
	__try
	{
		__asm
		{
			mov eax, pStrikeStartAddr;
			add eax, temp;
			add eax, nums_strike_id2;
			mov eax, [eax];
			
			mov id, eax;
		}
	}
	__except(1)
	{
		OutputDebugString(FUNCNAME);
	}
	
	return id;
}

DWORD Gamecall::GetStrike_R_id(int index, DWORD p_R_addr)
{
	DWORD addr = 0;
	int temp = index * 0xb88;
	
	__asm
	{
		mov eax, p_R_addr;
		add eax, temp;
		add eax, 0x4;
		mov eax, [eax];
		mov addr, eax;
	}
	
	return addr;
}

DWORD Gamecall::GetStrike_R_addr(DWORD pStrikeStartAddr)
{
	DWORD addr;
	__asm
	{
		mov eax, pStrikeStartAddr;
		mov eax, [eax + 0x4];
		mov eax, [eax + 0x20];
		add eax, 0x68;
		
		mov addr, eax;
	}
	
	return addr;
}

//��ȡ��������װ���ֿ����Base
DWORD Gamecall::GetBagbodyInfoBase()
{
	DWORD addr = NULL;
	
	__try{
		__asm{
			mov eax, bag_enum_base;
			mov eax, [eax];
			mov eax, [eax + bag_enum_offset1];
			mov eax, [eax + bag_enum_offset2];
			mov eax, [eax + bag_enum_offset3];
			
			mov addr, eax;
		}
	}
	__except(1)
	{
		OutputDebugString(FUNCNAME);
	}
	return addr;
}

int Gamecall::GetGoodsYanSe(DWORD m_Adress)  //��ȡ��Ʒ����ɫ
{
	DWORD Adress = 0;
	_try
	{
		Adress =(DWORD)ReadByte(ReadDWORD( m_Adress + bag_item_color_offset1 ) + bag_item_color_offset2);
	}
	_except(1)
	{
		TRACE(_T("��ȡ��Ʒ�ĵȼ�����"));
		return -1;
	}
	return Adress;
}


DWORD Gamecall::GetGoodsBiDui(DWORD m_Adress)  //��ȡ��Ʒ�ıȶ�
{
	DWORD Adress = 0;
	_try
	{
		Adress =(DWORD)ReadByte(ReadDWORD( m_Adress + bag_item_bidui_offset1 ) + bag_item_bidui_offset2);
	}
	_except(1)
	{
		TRACE(_T("��ȡ��Ʒ�ıȶԴ���"));
		return -1;
	}
	return Adress;
}

DWORD Gamecall::GetGoodsBiDui_A(DWORD m_Adress)  //��ȡ��Ʒ�ıȶ�A
{
	DWORD Adress = 0;
	_try
	{
		Adress =(DWORD)ReadByte(ReadDWORD( m_Adress + bag_item_bidui1_offset1 ) + bag_item_bidui1_offset2);
	}
	_except(1)
	{
		TRACE(_T("��ȡ��Ʒ�ıȶ�A����"));
		return -1;
	}
	return Adress;
}


DWORD Gamecall::GetGoodsWuQiPingJi(DWORD m_Adress)  //��ȡ����������
{
	DWORD Adress = 0;
	_try
	{
		Adress =(DWORD)ReadByte( m_Adress + wuqi_pj_offset );
	}
	_except(1)
	{
		TRACE(_T("��ȡ��������������"));
		return -1;
	}
	return Adress;
}


DWORD Gamecall::GetGoodsWuQiDangQianJingYan(DWORD m_Adress)  //��ȡ������ǰ�ľ���
{
	DWORD Adress = 0;
	_try
	{
		Adress =(DWORD)ReadWORD( m_Adress + wuqi_xp_cur_offset );
	}
	_except(1)
	{
		TRACE(_T("��ȡ������ǰ�ľ������"));
		return -1;
	}
	return Adress;
}

DWORD Gamecall::GetGoodsIsFengYin(DWORD m_Adress)  //��ȡ��Ʒ�Ƿ��ӡ
{
	DWORD Adress = 0;
	_try
	{
		Adress =(DWORD)ReadByte(ReadDWORD( m_Adress + 0x0C)+0x0C ); 
	}
	_except(1)
	{
		TRACE(_T("��ȡ��Ʒ�Ƿ��ӡ����"));
		return -1;
	}
	return Adress;
}


DWORD Gamecall::GetBaGuaGeZiShu(DWORD m_Adress)  //��ȡ���Ը�����
{
	DWORD Adress = 0;
	_try
	{
		Adress =(DWORD)ReadByte(ReadDWORD( m_Adress + bag_item_bagua_pos_offset1)+ bag_item_bagua_pos_offset2 ); 
	}
	_except(1)
	{
		TRACE(_T("��ȡ���Ը���������"));
		return -1;
	}
	return Adress;
}




//��ȡ��ɫװ������Base
DWORD Gamecall::GetBodyInfoBase(DWORD pBase) 
{
	DWORD addr = NULL;
	
	DWORD temp = body * 0x10;
	__try
	{
		__asm
		{
			mov eax, pBase;
			add eax, temp;
			add eax, 0x0c;
			mov eax, [eax];
			
			mov addr, eax;
		}
	}
	__except(1)
	{
		OutputDebugString(FUNCNAME);
	}
	
	return addr;
}


DWORD Gamecall::GetBagInfoBase(DWORD pBase)  //��ȡ��������Base
{
	DWORD addr = NULL;
	
	DWORD temp = package * 0x10;
	__try
	{
		__asm
		{
			mov eax, pBase;
			add eax, temp;
			add eax, 0x0c;
			mov eax, [eax];
			
			mov addr, eax;
		}
	}
	__except(1)
	{
		OutputDebugString(FUNCNAME);
	}
	
	return addr;
}


BOOL Gamecall::GetAllBaGuaToVector(std::vector<_BAGSTU> &BaGuaVec)
{
	std::vector<_BAGSTU> AllGoods;
	GetAllGoodsToVector(AllGoods);
	
	for(DWORD i = 0; i < AllGoods.size(); i++)
	{
		
		if(AllGoods[i].m_Info >= 8 &&
			AllGoods[i].m_Info <= 16)
		{
			BaGuaVec.push_back(AllGoods[i]);
		}
	}
	
	
	return TRUE;
}



BOOL Gamecall::GetSpecBaGuaToVector(wchar_t* name, std::vector<_BAGSTU> &BaGuaVec)
{
	std::vector<_BAGSTU> AllGoods;
	GetAllGoodsToVector(AllGoods);
	
	for(DWORD i = 0; i < AllGoods.size(); i++)
	{
		if(wcscmp(name, AllGoods[i].name) == 0)
		{
			BaGuaVec.push_back(AllGoods[i]);
		}
	}
	
	return TRUE;
}



DWORD Gamecall::GetBagGridNumberLast()
{
	std::vector<_BAGSTU> AllGoods;
	GetAllGoodsToVector(AllGoods);
	
	return (GetBagGridNumber() - AllGoods.size());
}


//��ǰ�������ܵĸ�����
DWORD Gamecall::GetBagGridNumber() 
{
	DWORD nums = 0;
	
	__try
	{
		__asm
		{
			mov eax, bag_grid_nums_base;
			mov eax, [eax];
			mov eax, [eax + bag_grid_nums_offset1];
			mov eax, [eax + bag_grid_nums_offset2];
			mov eax, [eax + bag_grid_nums_offset3];
			
			movzx eax, al;
			mov nums, eax;
		}
	}
	__except(1)
	{
		OutputDebugString(FUNCNAME);		
	}
	
	return nums;
}

DWORD Gamecall::GetGoodsBase(DWORD pAddr, int index)  //��ȡ��Ʒ���׵�ַ
{
	DWORD addr = 0;
	
	int temp = index * 4;
	
	__try
	{
		__asm
		{
			mov eax, pAddr;
			mov ebx, temp;
			mov eax, [eax + ebx];
			
			mov addr, eax;
		}
	}
	__except(1)
	{
		OutputDebugString(FUNCNAME);
	}
	
	return addr;
}

DWORD Gamecall::GetGoodsID(DWORD pAddr)  //��ȡ��Ʒ��ID
{
	DWORD id = UINT_MAX;
	
	__try
	{
		__asm
		{
			mov eax, pAddr;
			mov eax, [eax + bag_item_id_offset1];
			mov eax, [eax + bag_item_id_offset2];
			
			mov id, eax;
		}
	}
	__except(1)
	{
		
	}
	
	return id;
}

DWORD Gamecall::GetGoodsNameID(DWORD pAddr)  //��ȡ��Ʒ������ID
{
	DWORD id = UINT_MAX;
	
	__try
	{
		__asm
		{
			mov eax, pAddr;
			mov eax, [eax + bag_item_nameid_offset1];
			mov eax, [eax + bag_item_nameid_offset2];
			
			mov id, eax;
		}
	}
	__except(1)
	{
		OutputDebugString(FUNCNAME);
	}
	
	return id;
}


//��ȡ������Ʒ����
wchar_t* Gamecall::GatBagGoodrName(DWORD ID) 
{
	wchar_t *name = NULL;
	
	__try
	{
		__asm
		{
			mov eax, bag_item_name_call_base;
			mov eax, [eax];
			mov ecx, [eax +  bag_item_name_call_offset1];
			mov edx, [ecx];
			mov edx, [edx + bag_item_name_call_offset2];
			push 0;
			mov ebx, ID;
			push ebx;
			call edx;
			mov eax, [eax + 0x18];
			mov name, eax;
		}
	}
	__except(1)
	{
		OutputDebugString(FUNCNAME);
	}
	
	return name;
}

DWORD Gamecall::GetGoodsType(DWORD pAddr)  //��ȡ��Ʒ������
{
	DWORD goodstype = UINT_MAX;
	
	__try
	{
		__asm
		{
			mov eax, pAddr;
			mov eax, [eax + bag_item_type_offset];
			
			mov goodstype, eax;
		}
	}
	__except(1)
	{
		OutputDebugString(FUNCNAME);
	}
	
	return goodstype;
}


//��ȡ��Ʒ�����ڸ�����
DWORD Gamecall::GetGoodsInfo(DWORD pAddr) 
{
	DWORD nums = UINT_MAX;
	
	__try
	{
		__asm
		{
			mov eax, pAddr;
			mov eax, [eax + bag_item_pos_offset];
			
			movzx eax, al;
			mov nums, eax;
		}
	}
	__except(1)
	{
		TCHAR szBuf[MAX_PATH];wsprintf(szBuf, _T("%S: %d"), __FILE__, __LINE__);log.logdv(szBuf);
	}
	return nums;
}


//��ȡ��Ʒ������
DWORD Gamecall::GetGoodsNum(DWORD pAddr)  
{
	DWORD nums = UINT_MAX;
	
	__try
	{
		__asm
		{
			mov eax, pAddr;
			mov eax, [eax + bag_item_nums_offset];
			
			movzx eax, al;
			mov nums, eax;
		}
	}
	__except(1)
	{
		OutputDebugString(FUNCNAME);
	}
	return nums;
}

DWORD Gamecall::GetGoodsLasting(DWORD pAddr)  //��ȡ��Ʒ�ĳ־�
{
	DWORD naijiu;
	
	__try
	{
		__asm
		{
			mov eax, pAddr;
			mov eax, [eax + bag_item_durability_offset];
			
			movzx eax, al;
			mov naijiu, eax;
		}
	}
	__except(1)
	{
		TCHAR szBuf[MAX_PATH];wsprintf(szBuf, _T("%S: %d"), __FILE__, __LINE__);log.logdv(szBuf);
		naijiu = UINT_MAX;
	}
	
	return naijiu;
}

DWORD Gamecall::GetGoodsLLV(DWORD pAddr)  //��ȡ��Ʒ�ĵȼ�
{
	int lv;
	__try
	{
		__asm
		{
			mov eax, pAddr;
			mov eax, [eax + bag_item_level_offset1];
			mov eax, [eax + bag_item_level_offset2];
			
			movzx eax, al;
			mov lv, eax;
		}
	}
	__except(1)
	{
		OutputDebugString(FUNCNAME);
		lv = UINT_MAX;
	}
	
	return lv;
}

DWORD Gamecall::GetCanshu_a(DWORD pAddr)  //��ҩ�ʹ�װ����Ҫ��һ������
{
	DWORD Adress = 0;
	
	__try
	{
		__asm
		{
			mov eax, pAddr;
			mov eax, [eax + 0x1c];
			
			mov Adress, eax;
		}
	}
	__except(1)
	{
		OutputDebugString(FUNCNAME);
	}
	return Adress;
}

DWORD Gamecall::Getcanshu1(DWORD pAddr)  //����1
{
	DWORD Adress = 0;
	
	__try
	{
		__asm
		{
			mov eax, pAddr;
			mov eax, [eax + 0x0c];
			mov eax, [eax + 0x938];
			
			mov Adress, eax;
		}
	}
	__except(1)
	{
		OutputDebugString(FUNCNAME);
	}
	return Adress;
}

DWORD Gamecall::Getcanshu2(DWORD pAddr)  //����2
{
	DWORD Adress = UINT_MAX;
	
	__try
	{
		__asm
		{
			mov eax, pAddr;
			mov eax, [eax + 0x0c];
			mov eax, [eax + 0x838];
			
			mov Adress, eax;
		}
	}
	__except(1)
	{
		OutputDebugString(FUNCNAME);
	}
	return Adress;
}

DWORD Gamecall::Getcanshu3(DWORD pAddr)  //����3
{
	DWORD Adress = UINT_MAX;
	
	__try
	{
		__asm
		{
			mov eax, pAddr;
			mov eax, [eax + 0x0c];
			mov eax, [eax + 0x838];
			
			add eax, -0x3;
			mov Adress, eax;
		}
	}
	__except(1)
	{
		OutputDebugString(FUNCNAME);
	}
	return Adress;
}

DWORD Gamecall::Getcanshu4(DWORD pAddr)  //����4
{
	DWORD Adress = 0;
	
	__try
	{
		__asm
		{
			mov eax, pAddr;
			mov eax, [eax + 0x0c];
			mov eax, [eax + 0x87e];
			
			mov Adress, eax;
		}
	}
	__except(1)
	{
		OutputDebugString(FUNCNAME);
	}
	
	return Adress;
}


//�������
DWORD Gamecall::CalcC(fPosition &p1, fPosition &p2)
{
	//power of   ƽ��
	//���ݹ��ȶ���
	double x = abs((double)(p1.x - p2.x));
	double y = abs((double)(p1.y - p2.y));
	
	double x2 = pow(x, 2);
	double y2 = pow(y, 2);
	
	//��߳�
	return (DWORD)sqrt(x2 + y2);
}


DWORD Gamecall::GetObjectSY(DWORD pObjAddress)  // �������������1
{
	DWORD Adress = UINT_MAX;
	
	__try
	{
		__asm
		{
			mov eax, pObjAddress;
			mov eax, [eax + obj_type4_name_offset1];
			mov eax, [eax + 0x1c];
			mov Adress, eax;
		}
	}
	__except(1)
	{
		OutputDebugString(FUNCNAME);
	}
	return Adress;
}


//�����Ǻ���
//��������  objadress
DWORD Gamecall::m_Get11C(DWORD m_Adress)  
{
	BYTE jd = 0;
	__try
	{
		_asm
		{
			mov eax,m_Adress;
			mov eax,[eax+obj_type4_youshan_offset1];
			mov eax,[eax+obj_type4_youshan_offset2];
			mov jd,al;
		}
	}
	__except(1)
	{
	}
	
	
	return (DWORD)jd;
}


//ojb_type20_nameid_offset1 
DWORD Gamecall::GetObjectSY12(DWORD pAddr)  // �������������12
{
	DWORD Adress;
	__try
	{
		_asm
		{
			mov eax, pAddr;
			mov eax, [eax + ojb_type20_nameid_offset1 ];
			mov eax, [eax + 0x1c];
			mov Adress, eax;
		}
	}
	_except(1)
	{
		OutputDebugString(FUNCNAME);
		Adress = UINT_MAX;
	}
	
	return Adress;
}


//��ȡ����ʼ��ַ
DWORD Gamecall::GetTaskStartAddr()
{
	DWORD value;
	__try
	{
		__asm
		{
			mov eax, quest_base;
			mov eax, [eax];
			mov eax, [eax + quest_offset1];
			mov eax, [eax + quest_offset2];
			mov eax, [eax + quest_offset3];
			add eax, quest_offset4;
			
			mov value, eax;
		}
	}
	__except(1)
	{
		OutputDebugString(FUNCNAME);
		value = NULL;
	}
	
	return value;
}

//��õ�ǰ����ID
DWORD Gamecall::GetTaskID(int i, DWORD pAddr)
{
	DWORD id = UINT_MAX;
	__try
	{
		int temp = i * quest_struct_size;
		__asm
		{
			mov eax, pAddr;
			mov ebx, temp;
			mov eax, [eax + ebx];
			mov eax, [eax];
			mov eax, [eax + quest_id_offset3];
			
			mov id, eax;
		}
	}
	__except(1)
	{
		log.logdv(_T("%s"), FUNCNAME);
	}
	
	return id;
}

//��õ�ǰ��������ID
DWORD Gamecall::GetTaskNameID(int i, DWORD pAddr)
{
	DWORD id = UINT_MAX;
	
	__try
	{
		int temp = i * quest_struct_size;
		__asm
		{
			mov eax, pAddr;
			mov ebx, temp;
			mov eax, [eax + ebx];
			mov eax, [eax];
			mov eax, [eax + quest_nameid_offset3];
			
			mov id, eax;
		}
	}
	__except(1)
	{
		log.logdv(_T("%s"), FUNCNAME);
	}
	
	return id;
}

//��õ�ǰ�����ַ
DWORD Gamecall::GetTaskPresentAddr(int i, DWORD pAddr)
{
	DWORD value;
	_try
	{
		int temp = i * 0x58;
		__asm
		{
			mov eax, pAddr;
			mov ebx, temp;
			
			add eax, ebx;
			
			mov value, eax
		}
	}
	_except(1)
	{
		OutputDebugString(FUNCNAME);
		value = NULL;
	}
	return value;
}

//��õ�ǰ�����ڼ���С����
DWORD Gamecall::GetPresentTaskIndexes(int i, DWORD pAddr)
{
	DWORD value;
	_try
	{
		int temp = i * 0x58;
		__asm
		{
			mov eax, pAddr;
			mov ebx, temp;
			add eax, ebx;
			add eax, 0x8;
			mov eax, [eax];
			
			movzx eax, al;
			mov value, eax;
		}
	}
	_except(1)
	{
		OutputDebugString(FUNCNAME);
		value = UINT_MAX;
	}
	
	return value;
}

//��õ�ǰС���������־
DWORD Gamecall::GetPresentTaskEndFlag(int i, DWORD pAddr, DWORD info)
{
	DWORD value;
	_try
	{
		int temp = i * 0x58 + 0x9 + (info - 1) * 1 * 2;
		__asm
		{
			mov eax, pAddr;
			mov ebx, temp;
			add eax, ebx;
			
			mov eax, [eax];
			movzx eax, al;
			
			mov value, eax;
		}
	}
	_except(1)
	{
		OutputDebugString(FUNCNAME);
		value = UINT_MAX;
	}
	return value;
}

//��õ�ǰС�����Ѿ���Ĺ�����
DWORD Gamecall::GetPresentTaskNum(int i, DWORD pAddr, DWORD info)
{
	DWORD value = UINT_MAX;
	__try
	{
		int temp = i * 0x58 + 0x9 + (info - 1) * 1 * 2 + 0x1;
		
		__asm
		{
			mov eax, pAddr;
			mov ebx, temp;
			add eax, ebx;
			
			mov eax, [eax];
			movzx eax, al;
			
			mov value, eax;
		}
	}
	__except(1)
	{
		log.logdv(_T("%s"), FUNCNAME);
	}
	return value;
}

//��ȡ��ǰ�ѽ���������
wchar_t* Gamecall::GatTaskName(DWORD ID)
{
	wchar_t *name = NULL;
	__try
	{
		__asm
		{
			mov eax, quest_name_call_base;
			mov eax, [eax];
            mov ecx, [eax + quest_name_call_offset1];
            mov edx, [ecx];
            mov edx, [edx + quest_name_call_offset2];
            push 0;
            mov ebx, ID;
            push ebx;
			call edx;
			mov eax, [eax + 0x18];  //TODO: 
			mov name, eax;
		}
	}
	__except(1)
	{
		log.logdv(_T("%s"), FUNCNAME);
	}
	
	return name;
}


DWORD Gamecall::GetTaskStepById(DWORD id)
{
	std::vector<Quest> QuestVec;
	GetAcceptedQuestToVector(QuestVec);
	
	for(DWORD i = 0; i < QuestVec.size(); i++)
	{
		if(QuestVec[i].id == id)
		{
			return QuestVec[i].step;
		}
	}
	
	return UINT_MAX;
}



//��������Ʒ
void Gamecall::OpenQuestItem(DWORD ID, DWORD ID2)
{
	_try
	{
		_asm
		{
			push 0;
			push 0;
			mov eax, ID2;
			push eax;
			mov eax, ID;
			push eax;
			
			
			mov eax, obj_enum_base;
			mov eax, [eax];
			mov eax, [eax + pickup1_offset1];
			mov eax, [eax + pickup1_offset2];
			mov eax, [eax + pickup1_offset3];
			mov ecx, eax;
			push eax;
			
			
			mov eax, pickup1_call;
			call eax;
		}
	}
	_except(1)
	{
		log.logdv(_T("%s"), FUNCNAME);
	}
}


void Gamecall::Pickup1(ObjectNode *pObj) //һ�μ���
{
	
	int ID2 = pObj->id2;
	int ID = pObj->id;
	__try
	{
		_asm
		{
			push 0;
			push 0;
			mov eax,ID2;
			push eax;
			mov eax,ID;
			push eax;
			
			mov eax,obj_enum_base;
			mov eax,[eax];
			mov eax,[eax+pickup1_offset1];
			mov eax,[eax+pickup1_offset2];
			mov eax,[eax+pickup1_offset3];
			mov ecx,eax;
			push eax;
			
			mov eax,pickup1_call;
			call eax;
			
			
			
		}
	}
	_except(1)
	{
		TRACE(_T("һ�μ������"));
	}
	
}


//���μ���
void Gamecall::Pickup2(ObjectNode *pObj)
{
	
	int ID2 = pObj->id2;
	int ID = pObj->id;
	
	
	__try
	{
		__asm
		{
			push 0;
			mov eax, ID2;
			push eax;
			mov eax, ID;
			push eax;
			
			mov eax, obj_enum_base;
			mov eax, [eax];
			mov eax, [eax + pickup2_offset1];
			mov eax, [eax + pickup2_offset2];
			mov eax, [eax + pickup2_offset3];
			mov ecx, eax;
			push eax;
			
			mov eax, pickup2_call;
			call eax;
		}
	}
	__except(1)
	{
		log.logdv(_T("%s"), FUNCNAME);
	}
}


//��������
BOOL Gamecall::isBagFull()
{
	//���жϱ�����û����
	std::vector<_BAGSTU> GoodsVec;
	GetAllGoodsToVector(GoodsVec);
	
	if(GoodsVec.size() == GetBagGridNumber())
	{
		return TRUE;
	}
	
	
	return FALSE;
}



//����
BOOL Gamecall::Pickup(ObjectNode *pObj)
{
	
	DWORD i = 0;
	__try
	{
		int times = 0;
		
pickup_one:
		
		sendcall(id_msg_Pickup1, pObj);
		
		
		
		if(isPlayerHasPickupQuestItemUI())
		{
			sendcall(id_msg_Pickup2, pObj);
		}
		else
		{	
			times++;
			if(times >= 3)
			{
				return FALSE;
			}
			goto pickup_one;
		}
		
		
		for(int i = 0; i < 6; i++)
		{
			if(GetPlayerQuestUIStatus() != 2)
			{
				break;
			}
			
			KeyPress('Y');
			Sleep(200);
		}
		
		
		return TRUE;
	}
	__except(1)
	{
		log.logdv(_T("%s"), FUNCNAME);
	}
	
	
	return FALSE;
}

//�ж϶����Ƿ�Ϊ����
BOOL Gamecall::isLoots(DWORD pAddr)  //TODO
{
	int bRet1;
	int bRet2;
	int bRet3;
	
	__try
	{
		__asm
		{
			mov eax, pAddr;
			mov eax, [eax + 0x14];
			mov ebx, eax;
			mov eax, [ebx + 0x14];
			mov bRet1, eax;
			
			mov eax, [ebx + 0x18];
			mov bRet2, eax;
			
			mov eax, [ebx + 0x1c];
			mov bRet3, eax;
		}
	}
	__except(1)
	{
		
		bRet1 = -1;
		bRet2 = -1;
		bRet3 = -1;
		
		log.logdv(_T("%s"), FUNCNAME);
		
	}
	
	if(bRet1 == -1 &&
		bRet2 == -1 &&
		bRet3 == -1)
		return false;
	else
		return TRUE;
	
	
	return TRUE;
}

//ת����2������1
fPosition Gamecall::ShortPosToFloatPos(sPosition &spos)
{
	fPosition fpos;
	
	fpos.x = (float)(spos.x * 4);
	fpos.y = (float)(spos.y * 4);
	fpos.z = (float)(spos.z * 4);
	
	return fpos;
}


// ���Էֽ�Ķ���
// 
// ������������1
// ���Ե�������4
// ���ε�������5
BOOL Gamecall::isCanFenjie(DWORD pAddr)
{
	
	DWORD type = GetGoodsType(pAddr);
	
	if(type == 1 ||
		type == 4 ||
		type == 5)
	{
		return TRUE;
	}
	
	return false;
}

//����
void Gamecall::HuanXian(int xianlu)
{
	DWORD playeraddr = GetPlayerDataAddr();
	
	__try
	{
		__asm
		{
			
			mov ebx, xianlu;
			push ebx;
			mov eax, playeraddr;
			mov ebx, huanxian_call;
			call ebx;
		}
	}
	__except(1)
	{
		log.logdv(_T("%s"), FUNCNAME);
	}
}



//������
void Gamecall::DeliverQuests(DWORD id, DWORD step, DWORD questtype, DWORD ff, DWORD npcid1, DWORD npcid2, DWORD unknow, DWORD mianban)
{
	__try
	{
		__asm
		{
			push unknow;
			mov eax, npcid2;
			push eax;
			mov eax, npcid1;
			push eax;
			mov eax, ff;
			push eax;
			mov eax, questtype;
			push eax;
			mov eax, step;
			push eax;
			mov eax, id;
			push eax;
			
			mov eax, obj_enum_base;
			mov eax, [eax];
			mov eax, [eax + deliver_quest_offset1];
			mov eax, [eax +  deliver_quest_offset2];
			mov esi, eax;
			mov eax, [eax +  deliver_quest_offset3];
			
			mov edx, eax;
			mov ecx, step;
			mov ebx, id;
			//mov edi, mianban;
			
			mov eax, deliver_quest_call ;
			call eax;
		}
	}
	__except(1)
	{
		log.logdv(_T("%s"), FUNCNAME);
	}
}

void Gamecall::KeyPress(WPARAM vk)
{
	if(m_hGameWnd != NULL)
	{
		PostMessage(m_hGameWnd, WM_KEYDOWN, vk, 0);
	}
	else
	{
		log.logdv(_T("���û�л�ȡ��Ϸ���ھ��"));
	}
}


//��װ����ԭʼ����, �һ���߶�дһ��
//����1: <<16 + pickage
//����2: װ����λ��
void Gamecall::WearEquipment(_BAGSTU &bag)
{
	
	int value = bag.m_Info;
	value <<= 16;
	value += package;
				
	
	//TODO: ���λ�ð���ʹ�� .BaguaGeziShu
	//��ͨ��Ʒ�õ���  m_Info
	
	int pos = 0;;
	if(8 <= bag.m_BaGuaGeZiShu &&
		bag.m_BaGuaGeZiShu <= 15)
	{
		pos = bag.m_BaGuaGeZiShu;
	}
	else
	{
		pos = bag.m_ID;
	}
	
	__try
	{
		
		DWORD addr = GetPlayerDataAddr();
		
		_asm
		{
			mov eax, addr;
			mov edx, [eax];
			mov ecx, eax;
			mov eax, [edx + chuanzhuangbei_offset3];
			
			call eax;
			
			push pos;
			push 0;
			mov ebx, value;
			push ebx;
			push eax;
			mov ecx, value;
			
			mov eax,  chuanzhuangbei_call;
			call eax;
		}
		
	}
	__except(1)
	{
		log.logdv(_T("%s"), FUNCNAME);
	}
}


//���װ�� ���������ҷֱ���  
//��Ҫ���װ����λ�� ��80002  
//������ID ��C5C9E   
//��������
void Gamecall::JieFengZhuangBei(DWORD zhuangbei,DWORD jiefengfu_ID,DWORD num)
{
	_try
	{
		_asm
		{
			mov eax,num;
			push eax;
			push 1;
			mov eax,jiefengfu_ID;
			push eax;
			push 0;
			push 0;
			mov eax,zhuangbei;
			push eax;
			
			
			
			mov eax,obj_enum_base;
			mov eax,[eax];
			mov eax,[eax+jiefeng_offset1];
			mov eax,[eax+jiefeng_offset2];
			mov ecx,[eax+jiefeng_offset3];
			
			mov eax,jiefeng_call;
			call eax;
		}
	}
	_except(1)
	{
		TRACE(_T("���װ������"));
	}
}


//�����ֱ��� ����λ��:220002  0    1    0(������)    Կ��ID    1     1(������)
void Gamecall::JieFengZhuangBei(DWORD adress1,DWORD adress2,DWORD adress3,DWORD adress4,DWORD adress5,DWORD adress6,DWORD adress7) //������
{
	__try
	{
		_asm
		{
			
			mov eax,adress7;
			push eax;
			mov eax,adress6;
			push eax;
			mov eax,adress5;
			push eax;
			mov eax,adress4;
			push eax;
			mov eax,adress3;
			push eax;
			mov eax,adress2;
			push eax;
			mov eax,adress1;
			push eax;
			
			
			mov eax,obj_enum_base;
			mov eax,[eax];
			mov eax,[eax+jiefeng_hezi_offset1];
			mov eax,[eax+jiefeng_hezi_offset2];
			mov ecx,[eax+ jiefeng_hezi_offset3];
            push ecx;
			mov ecx,0;
			mov eax,jiefeng_hezi_call;
			call eax;
		}
	}
	__except(1)
	{
		TRACE(_T("�����ӳ���"));
	}
}




//�ж��Ƿ���ʬ��
BOOL Gamecall::isDeadBody(DWORD pAddr)
{
	DWORD type = GetObjectType(pAddr);
	if(type == 0xb0)
	{
		return TRUE;
	}
	
	return FALSE;
}


//ReadByte(ReadDWORD(ReadDWORD(ReadDWORD(Environmental_Adress) + 0x34) + 0x80) + 0x158);
//�Ƿ����ʬ����
BOOL Gamecall::isPickupDeadBody()
{
	
	UCHAR result = 0;
	DWORD playerdata = GetPlayerDataAddr();
	
	__try
	{
		__asm
		{
			mov eax, playerdata;
			mov eax, [eax +  player_status_ispickupbody_offset3];
			mov result, al;
		}
		
		
	}
	__except(1)
	{
		log.logdv(_T("%s"), FUNCNAME);
	}
	
	return (result != 0);
}



void Gamecall::_PickupTask(ObjectNode* pObj)
{
	
	int id2 = pObj->id2;
	int id1 = pObj->id;
	
	log.logdv(_T("%s: id: %d, id2: %d"), FUNCNAME, id1, id2);
	__try
	{
		__asm
		{
			push 0;
			push 0;
			mov eax, id2;
			push eax;
			mov eax, id1;
			push eax;
			
			
			mov eax, obj_enum_base;
			mov eax, [eax];
			mov eax, [eax + pickup1_offset1];
			mov eax, [eax + pickup1_offset2];
			mov eax, [eax + pickup1_offset3];
			mov ecx, eax;
			push eax;
			
			
			mov eax, pickup1_call;
			call eax;
		}
		
	}
	__except(1)
	{
		log.logdv(_T("%s"), FUNCNAME);
	}
}


//ȡ��ɫ��Ϣ
PCHARACTER Gamecall::GetCharacter(int index)
{
	int temp = index * 4;
	PCHARACTER lpret = NULL;
	
	__try
	{
		__asm
		{
			mov eax, eax;
			mov eax, [eax];
			mov eax, [eax + 0x30];
			mov eax, [eax + 0x10];
			mov ebx, temp;
			mov eax, [eax + ebx];
			mov lpret, eax;
		}
	}
	__except(1)
	{
		log.logdv(_T("%s"), FUNCNAME);
	}
	return lpret;
}


//5 ��ʾ���� 1 �ս���Ϸ 2 ѡ���ɫ���� 3��Ϸ��
//��ǰ����״̬
int Gamecall::isLoadingMap()
{
	
	DWORD value = UINT_MAX;
	
	__try
	{
		__asm
		{
			mov eax, is_logingame_base;
			mov eax, [eax];
			mov eax, [eax + is_logingame_offset1];
			mov eax, [eax + is_logingame_offset2];
			mov eax, [eax + is_logingame_offset3];
			
			mov value, eax;
		}
	}
	__except(1)
	{
		log.logdv(_T("%s"), FUNCNAME);
	}
	
	return value;
}


//�жϽ�ɫ�Ƿ��ڴ�������Ʒ�Ķ���״̬
BOOL Gamecall::isLoading()
{
	DWORD value = 0;
	DWORD addr = GetPlayerDataAddr();
	
	__try
	{
		__asm
		{
			mov eax, addr;
			mov eax, [eax + 0x110];
			movzx eax, al;
			mov value, eax;
		}
	}
	__except(1)
	{
		log.logdv(_T("%s"), FUNCNAME);
	}
	
	//����Ӧ����Ū����
	//==5˵�����ٶ���״̬
	return (value == 5);
}


//
//wchar_t *NAME = L"AreaInfoPanel";
//	canshu2 = ReadDWORD(JIEGOU.adress+0x58);
void Gamecall::OpenXianluUI()
{
	DWORD uiAddr = 0; 
	GetUIAddrByName(L"AreaInfoPanel", &uiAddr);
	assert(uiAddr != 0);
	
	UIOperator uiop;
	uiop.pAddr = (DWORD *)uiAddr;
	uiop.c5 = *(DWORD *)(uiAddr +  post_xianlu_c5);
	
	sendcall(id_msg_FaSonXianLuBao, (LPVOID)uiop.c5);
	
}

//������·��CALL
void Gamecall::FaSonXianLuBao(DWORD adress1) 
{
	KONGJ kj;
	kj.canshu1 = 0x0A78D0A4;
	kj.canshu2 = 0x0;
	kj.canshu3 = 0x544D0EA8;
	kj.canshu4 = 0x0;
	kj.canshu5 = adress1;      //"AreaInfoPanel"+0x58
	kj.canshu6 = 0x1;
	kj.canshu7 = 0x2;
	kj.canshu8 = 0x0;
	kj.canshu9 = 0x0;
	kj.canshu10 = 0x0;
	kj.canshu11 = 0x0;
	kj.canshu12 = 0x4EFE0016;
	
	__try
	{
		__asm
		{
			mov eax, obj_enum_base;
			mov eax, [eax];
			mov eax, [eax + post_xianlu_offset1];
			mov ecx, [eax + 0x8];    //dd [[[0x0FAC688]+2C]+8]
			
			
			mov edx, [ecx];
			mov eax, [edx + post_xianlu_offset2];
			
			lea ebx, kj;
			push ebx;
			call eax
		}
	}
	__except(1)
	{
		log.logdv(_T("%s"), FUNCNAME);
	}
}

//������Ϸ
void Gamecall::LoginGame(int index)
{
	DWORD uiAddr = 0;
	int i = 0;
	
	
	BOOL bFind = FALSE;
	for(i = 0; i < 5; i++){
		GetUIAddrByName(L"SelectCharacterPanel", &uiAddr);
		if(uiAddr != 0)
		{
			bFind = TRUE;
			break;
		}
		
		Sleep(1000);
	}
	
	
	if(bFind == FALSE)
	{
		log.logdv(_T("û���ҵ���ɫѡ��UI"));
		return;
	}
	
	
	BOOL bIn =FALSE;
	for(i = 0; i < 10; i++)
	{
		//�жϽ�ɫѡ�����
		if(isLoginInSelectPlayer())
		{
			bIn = TRUE;
			break;
		}
		
		Sleep(1000);
	}
	
	
	if(bIn == FALSE)
	{
		log.logdv(_T("���ٽ�ɫѡ�����"));
		return;
	}
	
	
	
	for(;;)
	{
		if(isLoadingMap() == 2)
		{
			break;
		}
		
		
		Sleep(1000);
	}
	
	
	
	//��̫�ɿ�
	Sleep(1000);
	__try
	{
		__asm
		{
			mov eax, uiAddr;
			mov ebx, index;
			mov dword ptr ds:[eax+0x1A8], ebx;
			mov ecx,eax;
			mov edi,eax;
			mov eax, login_call;
			call eax;
		}
		
	}
	__except(1)
	{
		log.logdv(_T("%s"), FUNCNAME);
	}
}


BOOL Gamecall::isQuestItem(DWORD pAddr)
{
	
	int value;
	
	
	__try
	{
		__asm
		{
			mov eax, pAddr;
			mov eax, [eax + 0x1c];
			movzx eax, al;
			mov value, eax;
		}
		
		//==2���ǿ���, ���ÿ��Զ϶�Ϊ��������Ʒ
		if(value == 2)
			return TRUE;
	}
	__except(1)
	{
		OutputDebugString(FUNCNAME);
	}
	
	return false;
}

//[[[player_base]+0x34]+0x78]+0x110] == ��ȡһ���ֽڣ�
//5		˵���ڿ���������Ʒ״̬
//2		��ʾ�Ǹ�ʰȡ��ui��������, ���Զ��μ���Ʒ
DWORD Gamecall::GetPlayerQuestUIStatus()
{
	DWORD pAddr = GetPlayerDataAddr();
	int value = UINT_MAX;
	
	
	__try
	{
		__asm
		{
			mov eax, pAddr;
			mov eax, [eax + player_status_openblock];
			movzx eax, al;
			mov value, eax;
		}
	}
	__except(1)
	{
		log.logdv(_T("%s"), FUNCNAME);
	}
	
	return value;
}

//ͨ������ȡ������
DWORD Gamecall::GetIndexByType(DWORD pObjAddress)
{
	DWORD index = UINT_MAX;
	TCHAR type = GetObjectType(pObjAddress);
	__try
	{
		if(type == 0x4)
		{
			index = GetObjectSY(pObjAddress);
		}
		else if(type == 0x20)
		{
			index = GetObjectSY12(pObjAddress);
		}
	}
	__except(1)
	{
		OutputDebugString(FUNCNAME);
	}
	
	return index;
}


//npc == 0
//else  == ����
DWORD Gamecall::m_Get2E4(DWORD m_Adress) 
{
	BYTE jd = 0;
	_try
	{
		_asm
		{
			mov eax,m_Adress;
			mov eax,[eax+obj_type4_youshan_offset4]; //1�ǹ��� 0��NPC
			mov jd,al;
		}
	}
	_except(1)
	{
		OutputDebugString(FUNCNAME);
		return 0;
	}
	
	
	return (DWORD)jd;
}



DWORD Gamecall::m_Get110(DWORD m_Adress)  //�����110
{
	BYTE jd = 0;
	__try
	{
		_asm
		{
			mov eax,m_Adress;
			mov eax,[eax+obj_type4_youshan_offset1];
			mov eax,[eax+obj_type4_youshan_offset3];
			mov jd,al;
		}
	}
	__except(1)
	{
		
	}
	
	
	return (DWORD)jd;
}


//����
//����1: ����id;
//�ж��Ƿ��ͺ�Ķ�����״̬
BOOL Gamecall::isCityConveyLoadingMap()
{
	
	UCHAR bLoading = 0;
	DWORD addr = GetPlayerDataAddr();
	__try
	{
		__asm
		{
			mov eax, addr
			mov eax, [eax + 0x14];
			mov eax, [eax + 0x16C];
			mov bLoading, al;
			
		}
		
		
	}
	__except(1)
	{
		
		OutputDebugString(FUNCNAME);
	}
	
	return (bLoading == 1);
}



//�ж��Ƿ��Ͷ���״̬
BOOL Gamecall::isCityConveying()
{
	
	UCHAR bLoading = 0;
	DWORD addr = GetPlayerDataAddr();
	__try
	{
		__asm
		{
			mov eax, addr;
			mov eax, [eax + 0x14];
			mov eax, [eax + dundi_chuning_status_offset4];
			
			mov bLoading, al;
			
		}
		
		log.logdv(_T("%d"), bLoading);
	}
	__except(1)
	{
		OutputDebugString(FUNCNAME);
	}
	
	return (bLoading == 1);
}


void Gamecall::FenJie(_BAGSTU &bag)
{
	//log.logdv(_T("������:%d"),bag.m_Info);
	int value = bag.m_Info;
	value <<= 16;
	value += package;
	
	//log.logdv(_T("fenjie.value:%d"),value);
    try
    {
        __asm
        {
            push 0;
            push 0;
            push 0;
            push 0;
            push 0;
            push 0;
            mov ebx, value;
            push ebx;
            
            mov eax, obj_enum_base;
            mov eax, [eax];
            mov eax, [eax+fenjie_offset1];
            mov eax, [eax+fenjie_offset2];
            mov eax, [eax+fenjie_offset3];
            push eax;
            
            mov ecx,0x0FF;
            
            mov eax,fenjie_call;
            call eax;
        }
		
    }
    catch(...)
    {
		OutputDebugString(FUNCNAME);
    }
}


//��չ����
//���� 5��
BOOL Gamecall::NewBag()
{
	DWORD addr = 0;
	DWORD addr1 = 0;
	

	GetUIAddrByName(L"Inventory2Panel", &addr);
    GetUIAddrByName(L"ExpandInvenSlotConfirmPanel", &addr1);
	
	BOOL result = FALSE;
	__try{
		
		__asm{
			mov edi, addr;  //EDI ���� Inventory2Panel ���׵�ַ
			lea ecx, [edi + bag_newslot_offset1];
			push 0;
			push 0;
			push ecx;
			push 0x2;
			push edi;
			mov eax, bag_newslot_call;
			call eax;
			
			mov edi, addr1;  //EDI= ExpandInvenSlotConfirmPanel�׵�ַ
			mov ecx, [edi + bag_newslot_offset2];
			mov eax, [ecx];
			push bag_newslot_offset3;
			push edi;
			mov edx, [eax + bag_newslot_offset4];
			call edx;
		}
		
		result = TRUE;
	}
	__except(1)
	{
		OutputDebugString(FUNCNAME);
	}
	
	return result;
}

//��ҩ
void Gamecall::ChiYao(const wchar_t *name)
{
	std::vector<_BAGSTU> AllGoods;
	GetAllGoodsToVector(AllGoods);
	
	_BAGSTU goods;
	if(GetGoodsFromBagByName(name, &goods))
	{
		sendcall(id_msg_ChiYao, &goods);
	}
	else
	{
		log.logdv(_T("%s: û���ڱ������ҵ������Ʒ: %s"), FUNCNAME, name);
	}
	
	return;
}

void Gamecall::TurnTo(float x, float y, float z)
{
	fPosition fpos;
	fpos.x = x;
	fpos.y = y;
	fpos.z = z;
	
	TurnTo(fpos);
}


//����״̬�ж�
//[����UI�׵�ַ + 44]
BOOL Gamecall::isFuhuoing()
{
	
	BYTE value = UCHAR_MAX;
	DWORD addr = GetPlayerDataAddr();
	__try
	{
		__asm
		{
			mov eax, addr;
			mov eax, [eax + 0x4fe];   //TODO:
			
			mov value, al;
		}
		
	}
	__except(1)
	{
		OutputDebugString(FUNCNAME);
		
	}
	
	return (value == 6);
	
}




//ȷ�Ͻ�����Ϸ��Э��
BOOL Gamecall::ConfirmAgreement()
{
	DWORD uiAddr = 0;
	BOOL bUiok = FALSE;
	BOOL bRet = FALSE;
    int i;
	//�ȴ�Э��ui
	for(i = 0; i < 10; i++)
	{
		
		//���ж�ui��������ַ��û������
		if(GetUIBinTreeBaseAddr() != NULL){
			GetUIAddrByName(L"ClausePanel", &uiAddr);
			if(uiAddr != 0){
				//�ҵ�ȷ��Э���ui��
				bUiok = TRUE;
				break;
			}
			
		}
		
		Sleep(1000);
	}
	
	
	if(bUiok == FALSE){
		log.logdv(_T("û�������õ�ʱ�����ҵ���¼Э���UI"));
		return FALSE;
	}
	
	BOOL uiValid = FALSE;
	
	//�ȴ�ui����
	for(i = 0; i < 5; i++){
		if(*(BYTE *)(uiAddr + 0x38) == 1){
			uiValid = TRUE;
			break;
		}
		
		Sleep(1000);
	}
	
	if(uiValid == FALSE){
		log.logdv(_T("��¼Э��UI������"));
		return FALSE;
	}
	
	
	//Э��ui���ú�������ui�ᵼ�½���Ľ�ɫui����.
	//�����Ǹ�ui��Ҫ������ʼ����Ϣ, ���������ټӸ�Sleep
	//��̫�ɿ�
	Sleep(2000);
	__try{
		UIOperator uiop;
		ZeroMemory(&uiop, sizeof(UIOperator));
		
		uiop.pAddr = (DWORD *)uiAddr;
		uiop.c5 = *(DWORD *)(uiAddr + 0x48);
		
		sendcall(id_msg_clickui, &uiop);
		
		bRet = TRUE;
	}
	__except(1){
		log.logdv(_T("���Э��UIʱ�쳣"));
	}
	
	
	return bRet;
	
}



//�رս�����Ϸ���ҡ��ui
BOOL Gamecall::CloseAttendance()
{
	
	UIOperator uiOp;
	ZeroMemory(&uiOp, sizeof(UIOperator));
	DWORD UIAddr = 0;
    int i;
	BOOL buiFined = FALSE;
	//�ȴ�ui����
	for(i = 0; i < 5; i++){
		GetUIAddrByName(L"AttendancePanel", &UIAddr);
		if(UIAddr != NULL){
			buiFined = TRUE;
			break;
		}
		
		
		Sleep(1000);
	}
	
	
	if(buiFined == FALSE){
		log.logdv(_T("û�����õ�ʱ���ڵȴ���UI����"));
		return FALSE;
	}
	
	
	BOOL buiOpen = FALSE;
	//�ȴ�ui����
	for(i = 0; i < 10; i++){
		//�����ж�һ��
		if(*(BYTE *)(UIAddr + 0x38) == 1)
		{
			buiOpen = TRUE;
			break;
		}
		
		Sleep(2000);
	}
	
	if(buiOpen == FALSE)
	{
		log.logdv(_T("û�������õ�ʱ���ڵȴ���ҡ��UI��ʾ"));
		return FALSE;
	}
	
	
	__try{
		
		uiOp.pAddr = (DWORD *)UIAddr;
		uiOp.c5 = *(DWORD *)(UIAddr + 0x1CBD8);
		sendcall(id_msg_clickui, &uiOp);
		
		
		UIAddr = 0;
		//ֱ��ȷ�ϵ�ui�������ټ���
		for(int i = 0; i < 3; i++){
			GetUIAddrByName(L"WindowConfirmPanel_Main", &UIAddr);
	
			if(UIAddr != 0){
				int IsShow = *(DWORD *)(UIAddr + 0x4c);
				if(IsShow != 0){
					//��������
					uiOp.pAddr = (DWORD *)UIAddr;
					uiOp.c5 = *(DWORD *)(UIAddr + 0x1c8);
					
					sendcall(id_msg_clickui, &uiOp);
					return TRUE;
				}
			}
			
			Sleep(1000);
		}
	}
	__except(1)
	{
		OutputDebugString(FUNCNAME);
	}
	
	return false;
}


//���õ�ǰ������ģʽ
//Ĭ�Ͼ���ģʽ. ��ǰ�Ѿ��Ǿ���Ͳ��л���
void Gamecall::SetMouseMode()
{
	//"OptionPanel" ������ֵĿؼ�
	//	1:������Ϸ���ж��Ǿ���ģʽ���Ǽ���ģʽ[["OptionPanel" �׵�ַ + 0x36D1C] + 0x1C]  ���� 1  �Ǿ���ģʽ  ����0�Ǽ���ģʽ
	//	2 : [0xFE3280] ���� 1  �Ǿ���ģʽ  ����0�Ǽ���ģʽ
	//	���ַ����жϾ���ģʽ��״̬������
	//	����5�� �ؼ����׵�ַ + 0x36F28
	
	//�жϵ�ǰģʽ
	//UCHAR isClass = *(UCHAR *)0xfe3280;
	//if(isClass == 0)
	//{
	DWORD addr = 0;
	GetUIAddrByName(L"OptionPanel", &addr);
	assert(addr != 0);
	
	UIOperator uiop;
	uiop.c5 = *(DWORD *)(addr + mouse_mode_class_c5);
	uiop.pAddr = (DWORD *)addr;
	
	sendcall(id_msg_JingDianMoShi, &uiop);
}

//�ȴ���Ϸ���ڴ���
//�ȴ�ʱ��25��
void Gamecall::WaitGameCreate()
{
	bool bIsCreate = false;
	
	//�жϵ�ǰ��Ϸ�Ĵ����Ƿ񴴽�
	//25����û����Ϸ���ڲ�����ʹ��Ҳ�����
	for(int i = 0; i < 20; i++)
	{
		if(isGameWndCreated(GetCurrentProcessId()) != NULL)
		{
			bIsCreate = true;
			break;
		}
		
		Sleep(2000);
	}
	
	log.logdv(_T("��Ϸ�����Ѿ�����"));
	return;
}


//�жϹ�����
//dd [[[[�����ַ]+2C]+0C]+4] = 5 ��ʾ���� 1 �ս���Ϸ 2 ѡ���ɫ���� 3��Ϸ��
void Gamecall::WaitPlans()
{
	for(;;)
	{
		if(isLoadingMap() == 3)
			break;
		
		
		log.logdv(_T("�ȴ�����"));
		Sleep(2000);
	}
}


//
//[[[[0x0FAC688]+34]+80]+1B4] һ�ֽ�  
//0��ʾ����  1��2����ʾ����   2��ʾ�����˻�����ԭ�ظ���
//
BYTE Gamecall::GetPlayerDeadStatus()
{
	
	BYTE value = UCHAR_MAX;
	DWORD playerdata = GetPlayerDataAddr();
	__try
	{
		__asm
		{
			mov eax, playerdata;
			mov eax, [eax + player_dead_status_offset3];
			
			mov value, al;
			
		}
		//log.logdv(_T("����״̬:%d"),value);
	}
	__except(1)
	{
		OutputDebugString(FUNCNAME);
		
	}
	
	return value;
}


//��Ѫ
//����1:���Ǹ��ٷֱ�, ���紫 50, ��ʾѪֵһ��ʱ
//���ȳԶ�Ӧ�ȼ���ҩ, û�еĻ��Ե͵ȼ�ҩ, ����û�гԲ��޵ȼ�, ����û����
//����ֵ1 = ��ҩ  2 = ��������ȷ 3 = ��ҩ�ɳ� 4 = CD�� 5 = ����
int Gamecall::GetHealth(DWORD theValue)
{
	if(theValue > 100 || theValue <= 0){
		log.logdv(_T("��������ȷ"));
		return 2;
	}
	
	
	try{	
		DWORD MaxHealth = GetPlayerMaxHealth();
		DWORD Health = GetPlayerHealth();
		DWORD percent = Health * 100 / MaxHealth;
		int leave = GetPlayerLevel();
		
		const wchar_t *itemName = NULL;
		
		
		//��������ҩ�ı�־
		BOOL test_1 = FALSE;
		BOOL test_2 = FALSE;
		
		
		//���Գ�ҩ��
MoreTimes:
		if(percent < theValue)
		{
			
			if(test_1 == FALSE){
				itemName = nSpec1;
				goto letsDrike;
			}
			
			if(test_2 == FALSE){
				itemName = nSpec2;
				goto letsDrike;
			}
			
			if(leave >= 50){
				itemName = nBig50;
			}
			else if(leave >= 45){
				itemName = nBig45;
			}
			else if(leave >= 36){
				itemName = nBig36;
			}
			else if(leave >= 29){
				itemName = nBig29;
			}
			else if(leave >= 10){
				itemName = nBig10;
			}
			else if(leave < 10 && leave >= 0){
				itemName = nLess10;
			}
			else{
				log.logdv(_T("û���ҵ������ܺȵ�ҩ"));
				return 3;
			}
			
letsDrike:
			_BAGSTU goods;
			if(GetGoodsFromBagByName(itemName, &goods)){
				//��
				if(sendcall(id_msg_isYaoPingCD, &goods) == 1){
					sendcall(id_msg_ChiYao, &goods);
					return 1;
				}
				else{
					return 4;
				}
				
				
			}
			else{
				if(test_1 == FALSE){
					test_1 = TRUE;
					goto MoreTimes;
				}
				
				if(test_1 == FALSE){
					test_2 = TRUE;
					goto MoreTimes;
				}
				
				//û���ҵ������Ʒ
				leave -= 5;
				goto MoreTimes;
			}
		}
	}
	catch(...){
		TRACE(FUNCNAME);
	}
	return 5;
}



//��ҵȼ�
UCHAR Gamecall::GetPlayerLevel() //��ý�ɫ�ȼ�
{
	UCHAR LV = 0;
	DWORD PlayerInfo = GetPlayerDataAddr();
	__try{
		__asm{
			mov eax, PlayerInfo;
			mov eax, [eax + player_cur_level];
			mov LV, al;
		}
	}
	__except(1){
		OutputDebugString(FUNCNAME);
	}
	
	return LV;
}

//Ӧ�������ļ���ɱ������
//һЩ�Ƿ������жϷŵ�������Ҫ�ñ�����Χ���ﾡ���ܶ�ı�������, Ȼ��
//�������ļ�ȥ����, ��Ȼ����Ҫ��дһ����Χ����Ŀ�����. ��Ϊ�������ļ�
//�д��ڵ���ԭ����Χ�����в����ڵ����.
BOOL Gamecall::Kill_ApplyConfig(std::vector<ObjectNode *> &ObjectVec)
{
    try{ 
        CCIniFile fileConfig;
        fileConfig.Open(m_szConfigPath);
        std::vector<ObjectNode *>::iterator it;
        
        for(it = ObjectVec.begin(); it != ObjectVec.end();){
            //���������ͬ, �ŵ�������ʼ
            ObjectNode *pNode = *it;
            wchar_t* objName = GetObjectName(pNode->ObjAddress);
            
            //Ҫ�Ǽ�����ɱ�����ļ���û��ָ��Ҫɱ��ɾ�����Ԫ��
            if(isCanKill(pNode) == FALSE &&
                fileConfig.isHave(strCombat, strAlwaysKill, objName) == FALSE)
            {
                it = ObjectVec.erase(it);
            }
            else{
                it++;
            }
        }
	
	
        for(it = ObjectVec.begin(); it != ObjectVec.end();){
            
            ObjectNode *pNode = *it;
            wchar_t* objName = GetObjectName(pNode->ObjAddress);
            
            if(fileConfig.isHave(strCombat, strFirst, objName)){
                ObjectNode *pBack = pNode;
                it = ObjectVec.erase(it);
                ObjectVec.insert(ObjectVec.begin(), pBack);	
            }
            else
                it++;
        }
        
        
        for(it = ObjectVec.begin(); it != ObjectVec.end();){
            ObjectNode *pNode = *it;
            wchar_t* objName = GetObjectName(pNode->ObjAddress);
            
            if(fileConfig.isHave(strCombat, strDontKill, objName)){
                //ɾ�����Ԫ��
                it = ObjectVec.erase(it);
            }
            else
                it++;
        }
        
	}
	catch(...){
		TRACE(_T("Ӧ�������ļ�����"));
	}
	return TRUE;
}


//ȡ�ö�������
wchar_t* Gamecall::GetObjectName(DWORD pObjAddress)
{
	return GetObjectNameByIndex(GetIndexByType(pObjAddress));
}



// Return whether first element is greater than the second
BOOL Gamecall::UDgreater(ObjectNode *elem1, ObjectNode *elem2)
{
	fPosition fpos1;
	fPosition fpos2;
	
	double dis1 = 0;
	double dis2 = 0;
	if(Gamecall::GetObjectPos(elem1, &fpos1) && Gamecall::GetObjectPos(elem2, &fpos2))
	{
		fPosition mypos;
		Gamecall::GetPlayerPos(&mypos);
		dis1 = Gamecall::CalcC(mypos, fpos1);
		dis2 = Gamecall::CalcC(mypos, fpos2);
	}
	
	return dis1 < dis2;
}



//��������Ʒ���׵�ַ, �����Ǳ������������Ķ����ַ
void Gamecall::ChiYao(_BAGSTU &goods)  //��ҩ
{

	DWORD pAddr = goods.m_Base;
	__try
	{
		__asm
		{
			mov ecx, 0;
			mov eax, pAddr;
			mov edx, [eax + 0x1c];
			mov eax, obj_enum_base;
			mov eax, [eax];
			mov eax, [eax + chiyao_offset1];
			mov eax, [eax + chiyao_offset2];
			mov eax, [eax + chiyao_offset3];
			push ecx;
			push edx;
			push eax;
			mov eax,  chiyao_call;
			call eax;
		}
	}
	__except(1)
	{
		OutputDebugString(FUNCNAME);
	}
}



void Gamecall::PickupDeadbody(DWORD id1, DWORD id2)
{
	__try{
		__asm{
			mov eax, id2;
			push eax;
			mov eax, id1;
			push eax;
			
			mov eax, obj_enum_base;
			mov eax, [eax];
			mov eax, [eax + pickup_body_offset1];
			mov eax, [eax + pickup_body_offset2 ];
			mov eax, [eax + pickup_body_offset3];
			mov edi, eax;
			
			mov eax, pickup_body_call;
			call eax;
		}
	}
	__except(1){
		TRACE(FUNCNAME);
	}
}

//[[[player_base]+0x34]+0x78]+0x110] == ��ȡһ���ֽڣ�
//5		˵���ڿ���������Ʒ״̬
//2		��ʾ�Ǹ�ʰȡ��ui��������, ���Զ��μ���Ʒ
BOOL Gamecall::isPlayerHasPickupQuestItemUI()
{
	DWORD status = 0;
	
	for(int i = 0; i < 7; i++){
		Sleep(200);
		status = GetPlayerQuestUIStatus();
		
		if(status == 2)
			return TRUE;
	}
	
	return FALSE;
}

//�жϽ�ɫ����״̬
BOOL Gamecall::isPlayerChanneling()
{
	DWORD status = 0;
	
	for(int i = 0; i < 7; i++){
		Sleep(200);
		status = GetPlayerQuestUIStatus();
		if(status == 5)
			return TRUE;
	}
	
	return FALSE;
}

float Gamecall::GetPlayerViewPoint()
{
	DWORD value = UINT_MAX;
	
	DWORD playerdata = GetPlayerDataAddr();
	
	__try{
		__asm{
			mov eax, playerdata;
			mov eax, [eax + 0x14];
			mov eax, [eax + player_steppos_x_offset2 + 0xc];
			mov value, eax;
		}
	}
	__except(1){
		OutputDebugString(FUNCNAME);
	}
	
	return (float)value;
}

//������Χ���еĶ�������
void Gamecall::GetAllObjectToVector(ObjectNode *pNote, std::vector<ObjectNode *> &RangeObject)
{
	__try{
		if(pNote->end == 1){
			return;
		}
		
		//�ӵ�vector��
		RangeObject.push_back(pNote);
		
		GetAllObjectToVector(pNote->left, RangeObject);
		GetAllObjectToVector(pNote->right, RangeObject);
	}
    __except(1){
		log.logdv(_T("%s: �����쳣"), FUNCNAME);
	}
}

void Gamecall::GetRangeTaskItemToVectr(std::vector<ObjectNode *> &TastItemVector, DWORD range)
{
	//���������д��,  ֱ�Ӵӷ�Χ�����б����Ĺ���
	std::vector<ObjectNode *> RangeObject;
	GetRangeObjectToVector(GetObjectBinTreeBaseAddr(), range, RangeObject);
	
	fPosition fmypos;
	GetPlayerPos(&fmypos);
	for(DWORD i = 0; i < RangeObject.size(); i++){
		ObjectNode *pNode = RangeObject[i];
		
		fPosition fpos;
		//���˵�����Զ�ĺ�û�����
		if(GetObjectPos(RangeObject[i], &fpos) == FALSE)
			continue;
		
		if(fpos.x == 0 || fpos.y == 0 || fpos.z == 0){
			continue;
		}

		DWORD dis = (DWORD)CalcC(fpos, fmypos);
		if(dis <= range){
			//�ж��Ƿ�Ϊ������Ʒ
			if(isQuestItem(pNode->ObjAddress))
			{
				TastItemVector.push_back(pNode);
			}
		}
	}
}

//�ж��Ƿ����ɱ
BOOL Gamecall::isCanKill(ObjectNode* pNode)
{
    
    //�ټ�һ��������4�Ĺ���
    if(GetObjectType(pNode->ObjAddress) != 0x4){
        return FALSE;
    }
    
    //����
    BOOL bCanKill = FALSE;
    if(m_Get11C(pNode->ObjAddress) == 1){
        bCanKill = TRUE;
        
    }
    else{
        if(m_Get110(pNode->ObjAddress) == 1){
            if(m_Get2E4(pNode->ObjAddress) != 0){
                bCanKill = TRUE;
            }
        }
        
    }
    
    return bCanKill;
}

//�������뷶Χ�ڵ����й��ﵽ������
//����1: ��Χ, ��λ: ��Ϸ�ڵ� ��
void Gamecall::GetRangeMonsterToVector(DWORD range, std::vector<ObjectNode *> &MonsterVec)
{
    try
    {
		//���������д��,  ֱ�Ӵӷ�Χ�����б����Ĺ���
		std::vector<ObjectNode *> RangeObject;
		GetRangeObjectToVector(GetObjectBinTreeBaseAddr(), range, RangeObject);
		
		fPosition fmypos;
		GetPlayerPos(&fmypos);
		for(DWORD i = 0; i < RangeObject.size(); i++)
		{
			ObjectNode *pNode = RangeObject[i];
			wchar_t* objName = GetObjectName(pNode->ObjAddress);
			if(objName == NULL)
				continue;

			fPosition fpos;
			//���˵�����Զ�ĺ�û�����
			if(GetObjectPos(RangeObject[i], &fpos) == FALSE)
				continue;
			
			if(fpos.x == 0 || fpos.y == 0 || fpos.z == 0)
				continue;
			
			if(CalcC(fpos, fmypos) > range)
				continue;

			if(isCanLook(pNode->ObjAddress) == FALSE)
				continue;

			//���漸��������ǿ�Ƶ�, ���������ļ���û��
			//����: ��������ļ�ǿ��ɱһ������, �����������
			//��û�������, ��϶����޷�ɱ��
			MonsterVec.push_back(pNode);
		}
    }
    catch(...)
    {
        TRACE(FUNCNAME);
    }
}


void Gamecall::_GetRangeObjectToVector(ObjectNode *pNote, DWORD range, std::vector<ObjectNode *> &RangeObject)
{
    if(pNote->end == 1)
    {
        return;
    }
    
    try
    {
        //������ͱȶ�����, û�������ֱ�ӷŽ�ȥ
        fPosition fpos;
        if(GetObjectPos(pNote, &fpos)){
            fPosition fmypos;
            GetPlayerPos(&fmypos);
            if(fpos.x == 0 || fpos.y == 0 || fpos.z	 == 0){
                RangeObject.push_back(pNote);
            }
            else if((DWORD)CalcC(fmypos, fpos) <= range){
                RangeObject.push_back(pNote);
            }
        }
        else
        {
            RangeObject.push_back(pNote);
        }
        
        
        GetRangeObjectToVector(pNote->left, range, RangeObject);
        GetRangeObjectToVector(pNote->right, range, RangeObject);
    }
    catch(...)
    {
        OutputDebugString(FUNCNAME);
    }
}
//�������뷶Χ�ڵ����ж���������
//����1: ��Χ, ��λ: ��Ϸ�ڵ� ��
//����������ڻὫû�������������0�Ķ�������ȥ
//��֤���������, ����Ĺ����ڵ����ĺ������
//�������������Ʒ���Ǹ�����
void Gamecall::GetRangeObjectToVector(ObjectNode *pNode, DWORD range, std::vector<ObjectNode *> &RangeObject)
{
    PARAM_GETUIADDRBYNAME temp;
    temp.argv1 = (DWORD)pNode;
    temp.argv2 = range;
    temp.argv3 = (DWORD)&RangeObject;
    sendcall(id_msg_GetRangeObjectToVector, &temp);
}

//�������뷶Χ�ڵ����ս��Ʒ����������
//����1: ��Χ, ��λ: ��Ϸ�ڵ� ��
void Gamecall::GetRangeLootObjectToVector(DWORD range, std::vector<ObjectNode *> &LootVec)
{

	try{
		//���������д��,  ֱ�Ӵӷ�Χ�����б����Ĺ���
		std::vector<ObjectNode *> RangeObject;
		GetRangeObjectToVector(GetObjectBinTreeBaseAddr(), range, RangeObject);
		
		fPosition fmypos;
		GetPlayerPos(&fmypos);
		for(DWORD i = 0; i < RangeObject.size(); i++)
		{
			ObjectNode *pNode = RangeObject[i];
			
			fPosition fpos;
			//���˵�����Զ�ĺ�û�����
			if(GetObjectPos(RangeObject[i], &fpos) == FALSE)
				continue;
			
			if(fpos.x == 0 || fpos.y == 0 || fpos.z == 0)
				continue;
			
			if(GetObjectType(pNode->ObjAddress) == 0xb0)
			{
				if(isLoots(pNode->ObjAddress))
				{
					DWORD dis = (DWORD)CalcC(fpos, fmypos);
					if(dis <= range){
						LootVec.push_back(pNode);
					}
				}
			}
		}
    }
    catch(...)
    {
        OutputDebugString(FUNCNAME);
    }
}

DWORD Gamecall::GetRangeMonsterCount(DWORD range)
{
	//�ж��Ƿ���aoe
	std::vector<ObjectNode *> RangeObject;
	GetRangeMonsterToVector(range, RangeObject);
    Kill_ApplyConfig(RangeObject);
	return RangeObject.size();
}


DWORD Gamecall::GetRangeLootCount(DWORD range)
{
	//�ж��Ƿ���aoe
	std::vector<ObjectNode *> RangeObject;
	GetRangeLootObjectToVector(range, RangeObject);
	return RangeObject.size();
}


void Gamecall::HookQietu( BOOL bEnable )
{
	if(bEnable)
	{
		hookQietu.hook();
	
	}else{
		hookQietu.unhook();
	}
	
}

void Gamecall::OverShunyi(BOOL bEnable) //��ͼ
{
	
	HookQietu(bEnable);
	__try
	{
		__asm
		{
			mov eax, obj_enum_base;
			mov eax, [eax];
			mov eax, [eax+shunyi_offset3];    
			mov eax, [eax+shunyi_offset4];     
			mov eax, [eax+shunyi_offset5];     
			add eax, shunyi_offset6;


			mov edi,eax;

			mov eax, over_shunyi_call;
			call eax;
		}
	}
	_except(1)
	{
		TRACE(_T("��ͼ����"));
	}
}


ObjectNode* Gamecall::GetObjectByName(wchar_t szName[], DWORD range)
{
	try
	{
		std::vector<ObjectNode *> RangeObject;
		if(range == 0){
			GetAllObjectToVector(GetObjectBinTreeBaseAddr(), RangeObject);
		}
		else{
			GetRangeObjectToVector(GetObjectBinTreeBaseAddr(), range, RangeObject);
		}
		
		fPosition tarpos;
		for(DWORD i = 0; i < RangeObject.size(); i++)
		{
			
			//���˵�û�����
			if(GetObjectPos(RangeObject[i], &tarpos) == FALSE){
				continue;
			}

			//���˵�������0��
			if(tarpos.x == 0 || tarpos.y == 0 || tarpos.z == 0){
				continue;
			}

			//���˵�û���ֵ�
			wchar_t *name = GetObjectName(RangeObject[i]->ObjAddress);
			if(name == NULL){
				continue;
			}
			
			if(wcscmp(name, szName) == 0){
				return RangeObject[i];
			}
		}
	}
	catch(...)
	{
		TRACE(FUNCNAME);
	}
	
	return NULL;
}

void Gamecall::_GetUItoVector(Tree *Base, std::vector<Tree *> &Allui)
{
	//�������Ż�һ��, �ҿ������ݱ��������ܶ��ַ��ͬ����id��ͬ������
	//����˵���Щ��ַ��ͬ��
	__try
	{
		if (Base->p2 == 1){
			return;
		}

		//��������5�����ظ���
		static DWORD ____old = 0;
		static DWORD ___old = 0;
		static DWORD __old = 0;
		static DWORD _old = 0;
		static DWORD old = 0;
		wchar_t* curName = GetUIName(Base->Adress);

		if(curName != NULL){
			if(curName[0] == 0x20 || (curName[0] >= 0x41 && //���˵���ͷ����A~Z�����
				curName[0] <= 0x7a ) ){
					if(Base->Adress != old &&
						Base->Adress != _old &&
						Base->Adress != __old &&
						Base->Adress != ___old &&
						Base->Adress != ____old
						){

							Allui.push_back(Base);

							____old = ___old;
							___old = __old;
							__old = _old;
							_old = old;
							old = Base->Adress;
					}
			}
		}



		_GetUItoVector(Base->Right, Allui);
		_GetUItoVector(Base->Left, Allui);

	}
	__except(1)
	{

	}

}

//ȡ������ui��������
void Gamecall::GetUItoVector(Tree *Base, std::vector<Tree *> &Allui)
{
    PARAM_GUANSHANGDIAN temp;
    temp.argv1 = (DWORD)Base;
    temp.argv2 = (DWORD)&Allui;
    sendcall(id_msg_GetUItoVector, &temp);
}



//ͨ������ȡ�����ui�ĵ�ַ
//ȡ�ù������ĵ�ַ
//����1: bar�Ķ�������ʼ�ڵ��ַ
//����2: ���ҵ�UI��, ���ݱȶ�������UI�����ݵ�ַ
//����3, ����ui�����ݵ�ַ
void Gamecall::GetUIAddrByName(wchar_t *name, DWORD *pUIAddr)
{
    assert(name != NULL);
    std::vector<Tree *> AllUI;
    GetUItoVector(GetUIBinTreeBaseAddr(), AllUI);
    

    for(int i = 0; i < AllUI.size(); i++){
        wchar_t* uiname = GetUIName(AllUI[i]->Adress);
        if(uiname != NULL){
            if(_wcsicmp(name, uiname) == 0){
                *pUIAddr = AllUI[i]->Adress;
                return;
            }
        }
    }

}


//��ȡ��Ʒ�ı�������
DWORD Gamecall::GetGoodsBagInfo(DWORD m_Adress) 
{
	DWORD Adress = 0;
	_try
	{
		Adress = (DWORD)ReadByte( m_Adress + 0x1C );
	}
	_except(1)
	{
		TRACE(_T("��ȡ��Ʒ�ı������ʹ���"));
		return -1;
	}
	return Adress;
}

// ��ȡ��ǰ����������ֵ
DWORD Gamecall::GetMuQianJingYanZongZhi(DWORD Adress) 
{
	DWORD JingYan;
	_try
	{
		_asm
		{
			
			mov eax,Adress;
			mov eax,[eax+wuqi_xp_all1_offset1];
			mov eax,[eax+wuqi_xp_all1_offset2];
			add eax,1;
			push eax;
			
			mov esi,Adress;
			mov eax,[esi+wuqi_xp_all1_offset3];
			mov eax,[eax+wuqi_xp_all1_offset4];
			push eax;
			
			mov eax,obj_name_call_base;
			mov edx,[eax];
			mov ecx,[edx+wuqi_xp_all1_offset5];
			mov edx,[ecx];
			mov eax,[edx+wuqi_xp_all1_offset6];
			call eax;
			mov eax,[eax+0x10];
			mov JingYan,eax;
		}
	}
	_except(1)
	{
		TRACE(_T("��ȡ��ǰ����������ֵ����"));
		return 0;
	}
	
	JingYan = JingYan - 1;
	return JingYan;
}

// ��ȡ��ǰ����������ֵA
DWORD Gamecall::GetMuQianJingYanZongZhi_A(DWORD Adress)
{
	DWORD JingYan;
	_try
	{
		_asm
		{
			
			mov eax,Adress;
			mov eax,[eax+ wuqi_xp_all2_offset1];
			mov eax,[eax+ wuqi_xp_all2_offset2];
			sub eax,1;
			push eax;
			
			mov esi,Adress;
			mov eax,[esi+ wuqi_xp_all2_offset3];
			mov eax,[eax+ wuqi_xp_all2_offset4];
			push eax;
			
			mov eax, obj_name_call_base;
			mov edx,[eax];
			mov ecx,[edx+ wuqi_xp_all2_offset5];
			mov edx,[ecx];
			mov eax,[edx+ wuqi_xp_all2_offset6];
			call eax;
			mov eax,[eax+ 0x24];
			mov JingYan,eax;
		}
	}
	_except(1)
	{
		TRACE(_T("��ȡ��ǰ����������ֵA����"));
		return 0;
	}
	
	return JingYan;
}


// ��ȡ������Ʒ�Ҽ��������� 
DWORD Gamecall::GetBagYouJianCaoZuoType(DWORD Adress,DWORD argv2)
{
	
	YouJianLeiXing LeiXing;
	LeiXing.canshu1 = Adress;
	LeiXing.canshu2 = 0;
	LeiXing.canshu3 = 0;
	LeiXing.canshu4 = 0;
	DWORD BBB;
	_try
	{
		_asm
		{
			push 0;
			lea eax,LeiXing;
			push eax;
			push 0;
			mov eax,Adress;
			push eax;
			mov eax,argv2;
			mov ebx,rbt_type_call;
			call ebx;
			add esp,0x8;
			mov BBB,eax;
			
		}
	}
	_except(1)
	{
		TRACE(_T("��ȡ������Ʒ�Ҽ���������"));
	}
	return BBB;
}


//��ȡ������Ʒ�Ҽ���������
DWORD Gamecall::GetGoodsYouJianType(DWORD m_BagLeiXing,DWORD m_Info)  
{
	DWORD m_Adress;
	DWORD UIaddr = 0;
	GetUIAddrByName(L"Inventory2Panel", &UIaddr);
	int value = m_Info;
	value <<= 16;
	value += m_BagLeiXing;
	
	if(UIaddr){
		m_Adress = GetBagYouJianCaoZuoType(value,UIaddr);
	}
	
	return m_Adress;
}

//������ �����Ǻ����ڱ����еĸ�����
void Gamecall::KaiHeZi(_BAGSTU &bag) 
{
	
	int value = bag.m_Info;
	value <<= 16;
	value += package;
	
	
	__try
	{
		__asm
		{
			push 0;
			push 0;
			push 0;
			push 0;
			push 1;
			push 0;
			mov ebx,value;
			push ebx;
			mov eax,obj_enum_base;
			mov eax,[eax];
			mov eax,[eax+kaihezi_offset1];
			mov eax,[eax+kaihezi_offset2];
			mov eax,[eax+kaihezi_offset3];
			push eax;
			mov ecx,0xFF;
			mov eax,kaihezi_call;
			call eax;
			
		}
	}
	_except(1)
	{
		TRACE(_T("�����ӳ���"));
	}
}



BOOL Gamecall::FillGoods(_BAGSTU &BagBuff)
{
	
	BagBuff.m_ID      =   GetGoodsID(BagBuff.m_Base);                //��ȡ��Ʒ��ID
	if(BagBuff.m_ID == UINT_MAX)
	{
		return FALSE;
	}
	
	BagBuff.m_NameID  =   GetGoodsNameID(BagBuff.m_Base);            //��ȡ��Ʒ������ID
	
	
	//BagBuff.name   =	  (wchar_t *)sendcall(id_msg_GatBagGoodrName, (LPVOID)BagBuff.m_NameID);
	BagBuff.name   =	  GatBagGoodrName(BagBuff.m_NameID);
	if(BagBuff.name == NULL)
	{
		return FALSE;
	}
	
	BagBuff.m_Type    =   GetGoodsType(BagBuff.m_Base);              //��ȡ��Ʒ������
	BagBuff.m_Info    =   GetGoodsInfo(BagBuff.m_Base);              //��ȡ��Ʒ�����ڸ�����
	BagBuff.m_Num	  =   GetGoodsNum(BagBuff.m_Base);               //��ȡ��Ʒ������
	BagBuff.m_Lasting =	  GetGoodsLasting(BagBuff.m_Base);           //��ȡ��Ʒ�ĳ־�
	BagBuff.m_LV      =   GetGoodsLLV(BagBuff.m_Base);               //��ȡ��Ʒ�ĵȼ�
	//BagBuff.m_Site	  =   GetCanshu_a(BagBuff.m_Base);               //��ҩ�ʹ�װ����Ҫ��һ������
	
	
	
	BagBuff.canshu1 = Getcanshu1(BagBuff.m_Base);  //����1
	BagBuff.canshu2 = Getcanshu2(BagBuff.m_Base);  //����2
	BagBuff.canshu3 = Getcanshu3(BagBuff.m_Base);  //����3
	BagBuff.canshu4 = Getcanshu4(BagBuff.m_Base);  //����4
	
	BagBuff.m_BagLeiXing = GetGoodsBagInfo(BagBuff.m_Base);  //��ȡ��Ʒ�ı�������
	
	
	
	
	
	BagBuff.m_CaoZuoType  = GetGoodsYouJianType(BagBuff.m_BagLeiXing,BagBuff.m_Info);  //��ȡ������Ʒ�Ҽ���������
	
	
	BagBuff.m_YanSe      =   GetGoodsYanSe(BagBuff.m_Base);  //��ȡ��Ʒ����ɫ
	BagBuff.m_IsFengYin  =   GetGoodsIsFengYin(BagBuff.m_Base);  //��ȡ��Ʒ�Ƿ��ӡ
	if ( BagBuff.m_YanSe == 5 )
	{
		//TRACE(_T("����Ʒ����ɫ   %X",BagBuff.m_CaoZuoType);
	}
	if ( BagBuff.m_YanSe == 4 )
	{
		//TRACE(_T("����Ʒ����ɫ   %X",BagBuff.m_CaoZuoType);
	}
	if ( BagBuff.m_YanSe == 3 )
	{
		//TRACE(_T("����Ʒ����ɫ   %X",BagBuff.m_CaoZuoType);
	}
	if ( BagBuff.m_YanSe == 2 )
	{
		//TRACE(_T("����Ʒ�ǰ�ɫ   %X",BagBuff.m_CaoZuoType);
	}
	if ( BagBuff.m_CaoZuoType == 0x0E )
	{
		//TRACE(_T("����Ʒ��δ����װ��  �ܸ��� %X,�׵�ַ %X ��Ʒ�Ҽ���������  %X",GridNum,BagBuff.m_Base,BagBuff.m_CaoZuoType);
	}
	else if ( BagBuff.m_CaoZuoType == 0x0F )
	{
		//TRACE(_T("����Ʒ��δ���ĺ���  �ܸ��� %X,�׵�ַ %X ��Ʒ�Ҽ���������  %X",GridNum,BagBuff.m_Base,BagBuff.m_CaoZuoType);
	}
	else
	{
		//TRACE(_T("�ܸ��� %X,�׵�ַ %X ��Ʒ�Ҽ���������  %X",GridNum,BagBuff.m_Base,BagBuff.m_CaoZuoType);
	}
	
	
	
	if ( BagBuff.m_Type == 1 || BagBuff.m_Type == 5 )
	{
		if ( BagBuff.m_YanSe == 4 || BagBuff.m_YanSe == 5  )
		{
			BagBuff.m_BiDui1 =  GetGoodsBiDui(BagBuff.m_Base);  //��ȡ��Ʒ�ıȶ�
			BagBuff.m_BiDui2 =  GetGoodsBiDui_A(BagBuff.m_Base);  //��ȡ��Ʒ�ıȶ�1
			if ( BagBuff.m_BiDui1 < BagBuff.m_BiDui2 )
			{
				BagBuff.m_DangQianJingYanZongZhi = GetMuQianJingYanZongZhi(BagBuff.m_Base); // ��ȡ��ǰ����������ֵ
			}
			if ( BagBuff.m_BiDui1 >= BagBuff.m_BiDui2 )
			{
				BagBuff.m_DangQianJingYanZongZhi = GetMuQianJingYanZongZhi_A(BagBuff.m_Base); // ��ȡ��ǰ����������ֵ
			}
			
			BagBuff.m_DangQianJingYanZhi  = GetGoodsWuQiDangQianJingYan(BagBuff.m_Base);  //��ȡ������ǰ�ľ���
			BagBuff.m_PingJi = GetGoodsWuQiPingJi(BagBuff.m_Base);  //��ȡ����������
			
		}
	}
	
	
	if (  BagBuff.m_Type == 4 )
	{
		BagBuff.m_BaGuaGeZiShu = GetBaGuaGeZiShu(BagBuff.m_Base);  //��ȡ���Ը�����
		
	}
	
	
	return TRUE;
}

void Gamecall::_GetAllGoodsToVector(std::vector<_BAGSTU> &RangeObject)
{
    DWORD BagbodyAdress = 0;
    DWORD BagAdress = 0;
    int GridNum = 0;
    _BAGSTU aGoods;
    
    BagbodyAdress = GetBagbodyInfoBase();                                 //��ȡ��������װ���ֿ����Base
    BagAdress = GetBagInfoBase(BagbodyAdress);                        //��ȡ��������Base
    GridNum = GetBagGridNumber();                        //��ǰ�������ܵĸ�����

    //������һ�±���
    for(int i = 0; i < GridNum; i++){
        ZeroMemory(&aGoods, sizeof(aGoods));
        __try{
            aGoods.m_Base = GetGoodsBase(BagAdress, i);                 //��ȡ��Ʒ���׵�ַ
            if(aGoods.m_Base != 0){
                if(FillGoods(aGoods)){
                    RangeObject.push_back(aGoods);
                }
            }
			//Sleep(10);
        }
        __except(1){
            TRACE(FUNCNAME);
        }
	}
}

//�����������ݵ�����
void Gamecall::GetAllGoodsToVector(std::vector<_BAGSTU> &RangeObject)
{
	sendcall(id_msg_GetAllGoodsToVector, &RangeObject);
}

void Gamecall::_GetAllBodyEquipToVector(std::vector<_BAGSTU> &RangeObject)
{
    DWORD BagbodyAdress = 0;
    DWORD BagAdress = 0;
    
    _BAGSTU aGoods;
    
    BagbodyAdress = GetBagbodyInfoBase();
    BagAdress = GetBodyInfoBase(BagbodyAdress);
    
    //��ǰ�������ܵĸ�����
    for(int i = 0; i < 0x10; i++){
        ZeroMemory(&aGoods, sizeof(_BAGSTU));
        __try{
            aGoods.m_Base = GetGoodsBase(BagAdress, i);   
            
            if(aGoods.m_Base != 0){
                if(FillGoods(aGoods)){
                    RangeObject.push_back(aGoods);
                }
            }
        }
        __except(1){
            TRACE(FUNCNAME);
        }
    }
}

//����װ�����ݵ�����
void Gamecall::GetAllBodyEquipToVector(std::vector<_BAGSTU> &RangeObject)
{
    sendcall(id_msg_GetAllBodyEquipToVector, &RangeObject);
}

//ͨ������ȡid
BOOL Gamecall::GetStrikeByName(const wchar_t *name, STRIKEINFO* pStrikeInfo)
{
	
	assert(name != NULL);
	
	std::vector<STRIKEINFO> StrikeVec;
	GetStrikeToVector(StrikeVec);
	
	try
	{
		for(DWORD i = 0; i < StrikeVec.size(); i++)
		{
			if(wcscmp(StrikeVec[i].stName.name, name) == 0)
			{
				*pStrikeInfo = StrikeVec[i];
				return TRUE;
			}
		}
	}
	catch(...)
	{
		OutputDebugString(FUNCNAME);
	}
	
	log.logdv(_T("%s: û���ҵ���Ӧ����"), FUNCNAME);
	return FALSE;
}

void Gamecall::GetStrikeToVector(std::vector<STRIKEINFO> &RangeObject)
{
	int count = 9;
	int count2 = 6;
	int index;
	
	
	DWORD pStrikeStart = GetStrikeStartAddr();
	DWORD adress = GetRJianSkill(pStrikeStart);

	STRIKEINFO strike;
	
	
	for(index = 0; index < count; index++){
		ZeroMemory(&strike, sizeof(STRIKEINFO));
		__try
		{
			strike.id1 = GetStrikeId1(index, pStrikeStart);
			if (strike.id1 != 0)
			{
				strike.id2 = GetStrikeId2(index, pStrikeStart);
				GetStrikeName(strike.id1, strike.id2, &strike.stName);
				strike.cd = GetStrikeCD(index, pStrikeStart);
				strike.canUse = isStrikeCanUse(index, pStrikeStart);
				strike.isBlock = isStrikeLocked(index, pStrikeStart);
				RangeObject.push_back(strike);
			}else
			{
				continue;
			}
		}
		__except(1){
			OutputDebugString(FUNCNAME);
		}
	}
	
	for(index = 0; index < count2; index++){
		ZeroMemory(&strike, sizeof(STRIKEINFO));
		__try{
			strike.id1 = GetRJSkillIDDD(index, adress);
			if (strike.id1 != 0)
			{
				strike.id2 = GetRJSkillIDDD2(index, adress);
				GetStrikeName(strike.id1, strike.id2, &strike.stName);
				strike.cd = GetRJSkillCD(index, adress);
				strike.canUse = GetRJSkillISShiYong(index, adress);
				strike.isBlock = GetRJSkillIsJieSuo(index, adress);
				RangeObject.push_back(strike);
			}else
			{
				continue;
			}
		}
		__except(1){
			OutputDebugString(FUNCNAME);
		}
	}
}

//ȡR�������Ƿ���ȴ  ����1 ˵������ȴ�� ����˵����һ�����������ڷ���
DWORD Gamecall::GetRJSkillCD(int i, DWORD m_adress)
{
	DWORD Adress = UINT_MAX;
	int temp = i * letter_strike_id + (letter_strike_cd-0x10) + m_adress;
	
	__try
	{
		if(m_adress != 0)
		{
			__asm
			{
				mov eax, temp;
				mov eax, [eax];
				mov Adress, eax;
			}
		}
	}
	__except(1)
	{
		OutputDebugString(FUNCNAME);
	}
	return Adress;
}

//ȡR�������Ƿ��Ѿ�����  
//0 ˵����û�н����ļ��� 
//1 ˵�����Ѿ�������
DWORD Gamecall::GetRJSkillIsJieSuo(int i, DWORD m_adress)
{
	DWORD Adress = UINT_MAX;
	int temp = i * letter_strike_id + (letter_strike_islock - 0x10) + m_adress;
	
	__try
	{
		if(m_adress != 0)
		{
			__asm
			{
				mov eax, temp;
				mov eax, [eax];
				mov Adress, eax;
			}
		}
	}
	__except(1)
	{
		OutputDebugString(FUNCNAME);
	}
	return Adress;
}

//ȡR�������Ƿ����ʹ�� �����0˵����������ǿ���ʹ�õ�  2 ˵�����������Ȼ�Ѿ����� �����ǻ�����
DWORD Gamecall::GetRJSkillISShiYong(int i, DWORD m_adress)
{
	DWORD Adress = UINT_MAX;
	int temp = i * letter_strike_id + (letter_strike_canuse-0x10) + m_adress;
	
	__try
	{
		if(m_adress != 0)
		{
			__asm
			{
				mov eax, temp;
				mov eax, [eax];
				mov Adress, eax;
			}
		}
	}
	__except(1)
	{
		OutputDebugString(FUNCNAME);
	}
	return Adress;
}

DWORD Gamecall::GetRJSkillIDDD2(int i, DWORD m_adress)  //ȡR����������ID2
{
	DWORD Adress = UINT_MAX;
	int temp = i * letter_strike_i2 + 0x4 + m_adress;  //TODO: 
	
	__try
	{
		if(m_adress != 0)
		{
			__asm
			{
				mov eax, temp;
				mov eax, [eax];
				mov Adress, eax;
			}
		}
	}
	__except(1)
	{
		OutputDebugString(FUNCNAME);
	}
	return Adress;
}

//ȡ����R�����������鿪ʼ��ַ
DWORD Gamecall::GetRJianSkill(DWORD m_adress)
{
	DWORD Adress = 0;
	__try
	{
		if(m_adress != 0)
		{
			__asm
			{
				mov eax, m_adress;
				mov eax, [eax + 0x4];
				mov eax, [eax + letter_strike_start_offset2];
				add eax, letter_strike_start_offset3;
				mov Adress, eax;
			}
		}
	}
	__except(1)
	{
		OutputDebugString(FUNCNAME);
	}
	return Adress;
}

//ȡR�����鼼��ID
DWORD Gamecall::GetRJSkillIDDD(int i, DWORD m_adress)
{
	DWORD Adress = 0;
	int temp = m_adress + i * letter_strike_id;
	__try
	{
		if(m_adress != 0)
		{
			__asm
			{
				mov eax, temp;
				mov eax, [eax];
				mov Adress, eax;
			}
		}
	}
	__except(1)
	{
		OutputDebugString(FUNCNAME);
	}
	return Adress;
}

//�ж��Ƿ�����ɫѡ�����
BOOL Gamecall::isLoginInSelectPlayer()
{
	DWORD dwUIAddr = 0;
	DWORD value = UINT_MAX;
	__try{
		GetUIAddrByName(L"SelectCharacterPanel", &dwUIAddr);
		__asm{
			mov eax, dwUIAddr;
			mov eax, [eax + select_character_offset];
			mov value, eax;
		}
		
	}
	__except(1)
	{
		OutputDebugString(FUNCNAME);
	}
	
	return (value != 0xff);
}


//ж��ʯ
void Gamecall::XieBaoShi(DWORD canshu1, DWORD canshu2, DWORD canshu3)
{
	__try
	{
		__asm
		{
			mov ebx, canshu1;
			push ebx;
			mov ebx, canshu2;
			push ebx;
			mov ebx, canshu3;
			push ebx;
			
			mov eax, obj_enum_base;
			mov eax, [eax];
			mov eax, [eax + xiebaoshi_offset1];
			mov eax, [eax + xiebaoshi_offset2];
			mov ecx, [eax + xiebaoshi_offset3];
			push ecx;
			
			mov ebx, xiebaoshi_call;
			call ebx;
		}
	}
	__except(1)
	{
		OutputDebugString(FUNCNAME);
	}
}


//�ӱ�ʯ
void Gamecall::JiaBaoShi(DWORD canshu1, DWORD canshu2, DWORD canshu3, DWORD canshu4, DWORD canshu5)
{
	__try
	{
		__asm
		{
			mov ebx, canshu1;
			push ebx;
			mov ebx, canshu2;
			push ebx;
			mov ebx, canshu3;
			push ebx;
			mov ecx, canshu4;
			push ecx;
			mov edx, canshu5;
			push edx;
			
			mov eax, obj_enum_base;
			mov eax, [eax];
			mov eax, [eax +  jiabaoshi_offset1];
			mov eax, [eax +  jiabaoshi_offset2];
			mov eax, [eax +  jiabaoshi_offset3];
			push eax;
			
			mov ebx,  jiabaoshi_call;
			call ebx;
		}
	}
	__except(1)
	{
		OutputDebugString(FUNCNAME);
	}
}


DWORD Gamecall::sendcall(DWORD id, LPVOID pParam)
{
	
	
	return SendMessage(GetGamehWnd(), WM_CUSTOM_GCALL, id, (LPARAM)pParam);
}


void Gamecall::Stepto3x()
{
	
	DWORD Adress = (DWORD)m_hModuleBsEngine + SHENXINGBAIBIANCHAZHI;
	
	__try
	{
		__asm
		{
			mov eax, Adress;
			mov eax, [eax];
			mov eax, [eax + x3step_offset1];
			mov eax, [eax + 0x0];
			mov eax, [eax + x3step_offset3];
			mov eax, [eax + x3step_offset4];
			mov ebx, 0x44610000;
			
			mov dword ptr [eax + x3step_offset5], ebx;
		}
		
		
	}
	__except(1)
	{
		OutputDebugString(FUNCNAME);
	}
}

//�򿪶Ի���, ���� npcid, npcid2
void Gamecall::DaKaiDuiHuaKuang(DWORD ID, DWORD ID2)
{
	__try
	{
		__asm
		{
			push 0;
			push 0;
			mov eax, ID2;
			push eax;
			mov eax, ID;
			push eax;
			mov eax, obj_enum_base;
			mov eax, [eax];
			mov eax, [eax + open_npc_offset1];
			mov eax, [eax + open_npc_offset2];
			mov ecx, [eax + open_npc_offset3];
			push ecx;
			
			mov eax, open_npc_call;
			call eax;
		}
	}
	__except(1)
	{
		OutputDebugString(FUNCNAME);
	}
}


//����
//����1: ����
//����2: ����
//����3: ��ַ ItemStorePanel ui
void Gamecall::GouMaiWuPing(DWORD Num, DWORD Ind, DWORD Adress)
{
	__try
	{
		__asm
		{
			push 0;
			push 0;
			mov eax, Num;
			push eax;
			mov eax, Ind;
			push eax;
			mov ecx, Adress;
			mov eax, buy_call;
			call eax;
		}
	}
	__except(1)
	{
		OutputDebugString(FUNCNAME);
	}
}


//ҩƷCD_CALL
// 1 == û��cd
// 0 == cd��
DWORD Gamecall::isYaoPingCD(_BAGSTU &goods) 
{
	BYTE m_Adress = 0;
	YaoPingCD_JG CD;
	
	int value = goods.m_Info;
	value <<= 16;
	value += package;
	
	int adress = goods.m_Base;


	_try
	{
		_asm
		{
			mov ecx,yao_cd_base;
			mov ecx,[ecx];
			mov ecx,[ecx+ yao_cd_offset1];
			mov edx,[ecx];
			mov edx,[edx+yao_cd_offset2];
			
			mov eax,adress;
			mov eax,[eax+yao_cd_offset3];
			mov ebx,[eax+yao_cd_offset4];
			push ebx;
			mov ebx,[eax+ yao_cd_offset5];
			push ebx;
			call edx;
			mov CD.canshu1,eax;
			mov CD.canshu2,-1;
			
			mov eax,obj_enum_base;
			mov eax,[eax];
			mov eax,[eax+ yao_cd_offset6];
			mov eax,[eax+yao_cd_offset7];
			mov eax,[eax+yao_cd_offset8];
			mov CD.canshu3,eax;
			
			lea eax,CD;
			push eax;
			push 0;
			mov ecx,value;
			push ecx;
			
			mov eax,obj_enum_base;
			mov eax,[eax];
			mov eax,[eax+yao_cd_offset9];
			mov ebx,[eax+yao_cd_offset10];
			
			mov esi,ebx;
			mov eax,yao_cd_call ;
			call eax;
			
			
			mov m_Adress,al;
		}
	}
	_except(1)
	{
		OutputDebugString(_T("ҩƷCD_CALL����"));
		return -1;
	}
	
	return (DWORD)m_Adress;
}


//��ͨ����, rt ѭ����, �����߼�������, ��Ҫ������ʹ�ӽ����������������
void Gamecall::AttackNormal()
{

	//�ż���, �Ӷ�ħ��ֵ���ж�
	if(GetPlayerMana() >= 50){
		//T
		sendcall(id_msg_attack, (LPVOID)0x5dde);
	}
	else{	
		//Attack(ATTACK_R);
		sendcall(id_msg_attack, (LPVOID)0x5dc1);
	}

}


//AOE����
//TODO: ����ͨ���жϹ���cd���Ż�
void Gamecall::AttackAOE()
{
	
	int mana = GetPlayerMana();
	if(mana >= 60){
		sendcall(id_msg_attack, (LPVOID)0x5dca);
		Sleep(1000);
	}
	else{
		sendcall(id_msg_attack, (LPVOID)0x5dc1);
	}
	
	
}

//ת��
void Gamecall::TurnTo(fPosition &pos)
{
	fPosition mypos;
	GetPlayerPos(&mypos);
	
	double angle;
	
	double M_PI = 3.14159265359;
	double value1;
	double value2;
	
	value1 = mypos.y - pos.y;
	value2 = mypos.x - pos.x;
	
	angle = atan2(abs(value1), abs(value2)) * 180 / M_PI;
	
	//�����Ϸ�ڽǶ�
	double gameangle = angle * 182;
	//logdv(_T("gameangle = %d"), (int)gameangle);
	
	//ȡ��ǰ��ɫ�Ƕ�
	int playerangle = (int)GetPlayerViewPoint();
	playerangle = playerangle % 65536;
	//logdv(_T("��ɫ����: %d"), playerangle);
	
	//�жϵ�ǰ��ɫ���ӽ��ڵڼ�����
	if((pos.x > mypos.x) &&
		(pos.y > mypos.y))
	{
		//����, ���ǵ�ǰ��ɫ�������ϵ�����
		//logdv(_T("Ŀ�굱ǰ����"));
	}
	else if((pos.x > mypos.x) &&
		(pos.y < mypos.y))
	{
		//���ǽ�ɫ���µ�����
		//logdv(_T("Ŀ���ڵ�ǰ����"));
		gameangle = 65536 - gameangle;
	}
	else if((pos.x < mypos.x) &&
		(pos.y < mypos.y))
	{
		//������������
		//logdv(_T("Ŀ�굱ǰ����"));
		gameangle += SOUTH;
	}
	else if((pos.x < mypos.x) &&
		(pos.y > mypos.y))
	{
		//logdv(_T("Ŀ�굱ǰ����"));
		gameangle = SOUTH - gameangle;
		//gameangle += EAST;
	}
	else
	{
		log.logdv(_T("ת�ӽ�ʱ, δ֪�ķ�λ"));
		RandomStep(60);
	}
	
	Turn((int)gameangle);
}


//����ʬ��
//��ΧĬ��500
BOOL Gamecall::PickupDeadbody(DWORD range)
{
	std::vector<ObjectNode *> RangeObject;
	GetRangeObjectToVector(GetObjectBinTreeBaseAddr(), range, RangeObject);
	
	
	ObjectNode *pMaxNode = NULL;
	try{
		for(DWORD i = 0; i < RangeObject.size(); i++){
			
			ObjectNode *pNode = RangeObject[i];
			
			
			//�ж϶����Ƿ��ǿɾ����ʬ��
			if(isDeadBody(pNode->ObjAddress)){
				pMaxNode = pNode;
				
				if(pNode->id > pMaxNode->id){
					pMaxNode = pNode;
				}
				
			}
		}
		
		if(pMaxNode == NULL){
			log.logdv(_T("û�б�����ʬ��"));
			return false;
		}
			
		PARAM_GUANSHANGDIAN temp;
		temp.argv1 = pMaxNode->id;
		temp.argv2 = pMaxNode->id2;
		sendcall(id_msg_PickupDeadbody, &temp);
	}
	catch(...){
		TRACE(FUNCNAME);
	}
	
	return TRUE;
}




//ɱ������, �߼��д�����·
//ѭ������: ����, ��ʱ, ��ɫ��, ����Χ
//����1: �����ַ
//����2: ��ʱ
//����:����2, ���ģʽӰ��ɱ�ֵ���������
//canKillRange �趨��Զ�����ֱ�ӹ���
int Gamecall::KillObject(DWORD range, ObjectNode *pNode, DWORD mode, DWORD canKillRange)
{
	//��¼����״̬���ж�Ŀ���Ƿ���������ɱ�ֳ�ʱ
	DWORD oriTime = GetTickCount();
	DWORD tarHealth = GetType4HP(pNode->ObjAddress);;
	int chiyaojs;
	chiyaojs = 0;
	for(;;){
		if (chiyaojs == 0)
		{
			if (GetHealth(50) == 1)
			{
				chiyaojs = 100*12;//100��*12 1��=50����
			}else if (GetHealth(50) == 2 || GetHealth(50) == 3 || GetHealth(50) == 5)
			{
				chiyaojs = 50000;//����2��3��4�Ͳ�׼����ѭ��
			}else if(GetHealth(50) == 4)
			{
				chiyaojs = 20;//CD�У���1��ʱ���ٽ����жϡ�
			}
		}else
		{
			chiyaojs--;
		}
		
		
		if(GetPlayerHealth() <= 0){
			log.logdv(_T("%s: ����������"), FUNCNAME);
			return RESULT_KILL_PLAYDEAD;
		}
		
		//�����߼����ݾ�������Ϊ�������������ж�

		if(GetType4HP(pNode->ObjAddress) == -1 || GetType4HP(pNode->ObjAddress) == 0){
			log.logdv(_T("%s: Ѫ���жϹ�����"), FUNCNAME);
			return RESULT_KILL_OK;
		}

		//if (GetObjectType(pNode->ObjAddress)==0xb0)
		//{
		//	log.logdv(_T("%s: �����жϹ�����"), FUNCNAME);
		//	return RESULT_KILL_OK;
		//}

		fPosition mypos;
		GetPlayerPos(&mypos);
		
		//ͨ�������ж�Ŀ������
		fPosition targetpos;
		if(_GetObjectPos(pNode->ObjAddress, &targetpos) == FALSE){
			log.logdv(_T("%s: �����жϹ�����"), FUNCNAME);
			return RESULT_KILL_OK;
		}
		DWORD dis = (DWORD)CalcC(targetpos, mypos);
		if(CalcC(targetpos, mypos) >= range){
			log.logdv(_T("%s: �����жϹ�����"), FUNCNAME);
			return RESULT_KILL_OK;
		}
		
		
		
		/*
		������
		if(GetObject_0x14(pNode->ObjAddress) == 0){
		log.logdv(_T("%s: 0x14�жϹ�����"), FUNCNAME);
		return RESULT_KILL_OK;
		}*/

		
		//�ɼ�����
		if(dis > canKillRange){
			targetpos.x = targetpos.x-10;
			targetpos.y = targetpos.y-10;
			Stepto(targetpos, 10, CAN_OPERATOR, range);
		}else if(dis <= 2){
			log.logdv(_T("%s: �ص�����"), FUNCNAME);
			RandomStep(30);
		}else if(dis <= canKillRange){
			//�жϵ���״̬
			if(isPlayerDaodi()){
				//5E60->5EA6->5EB0->5E9C
				if(isStrikeCd(0x5e60) == FALSE){
					sendcall(id_msg_attack, (LPVOID)0x5e60);
				}
				else if(isStrikeCd(0x5EA6) == FALSE){
					sendcall(id_msg_attack, (LPVOID)0x5EA6);
				}
				else if(isStrikeCd(0x5EB0) == FALSE){
					sendcall(id_msg_attack, (LPVOID)0x5EB0);
				}
				else if(isStrikeCd(0x5E9C) == FALSE){
					sendcall(id_msg_attack, (LPVOID)0x5E9C);
				}
			}
			//ɱ��ʱ����Ҫת��
			TurnTo(targetpos);
			if(mode & modeAoe){
				if(GetRangeMonsterCount() >= 2){
					AttackAOE();
				}else{
					AttackNormal();
				}
			}
			else{
				AttackNormal();
			}

			//5��û�ܴ��Ѫ����
			DWORD curTime = GetTickCount();
			if((curTime - oriTime) >= 5000){
				DWORD curHealth = GetType4HP(pNode->ObjAddress);
				if(curHealth == tarHealth){
					log.logdv(_T("%s: ��ʱ�˳�"), FUNCNAME);
					return RESULT_KILL_TIMEOUT;
				}
				else{
					oriTime = GetTickCount();
					tarHealth = GetType4HP(pNode->ObjAddress);
				}
			}
		}
		Sleep(50);
	}//for
}


void Gamecall::DeleteItem(_BAGSTU &bag)
{
	int pos = bag.m_Info;
    int value = pos;
    value <<= 16;
    value += package;
    
	int nums = bag.m_Num;
	
	__try{
		__asm{
			mov eax, nums;
			push eax;
			mov eax, value;
			push eax;
			mov eax, obj_enum_base;
			mov eax, [eax];
			mov eax, [eax + bag_delete_offset1];
			mov eax, [eax + bag_delete_offset2];
			mov eax, [eax + bag_delete_offset3];
			push eax;
			
			mov eax, bag_delete_call;
			call eax;
		}
		
	}
	__except(1){
		
	}
	
	
}
//���������
void Gamecall::RandomStep(DWORD range)
{
	fPosition fmypos;
	GetPlayerPos(&fmypos);
	
	if((rand()%2) == 1){
		fmypos.x += range;
		fmypos.y += range;
	}
	else{
		fmypos.x -= range;
		fmypos.y -= range;
	}
	
	Stepto(fmypos, 10, 10);
}

void Gamecall::QuChuJiNengDian(DWORD ID) //ȥ�����ܵ�
{
	_try{
		_asm{
			push 0;
			mov eax,ID;
			push eax;
			mov eax,obj_enum_base;
			mov eax,[eax];
			mov eax,[eax+delete_strike_call_offset1];        //ȥ�����ܵ�һ��ƫ��
			mov eax,[eax+delete_strike_call_offset2];        //ȥ�����ܵ����ƫ��
			mov eax,[eax+delete_strike_call_offset3];       //ȥ�����ܵ�����ƫ��
			push eax;
			mov ebx,delete_strike_call;
			call ebx;
		}
	}
	_except(1){
		TRACE(_T("ȥ�����ܵ�"));
	}

}



void Gamecall::DaKaiQingChuQuanBuJiNengJieMian(DWORD adress,DWORD adress1) //�����ȫ�����ܽ���
{


	KONGJ kj;
	kj.canshu1 = QUDINGYAOJIANG_JIEGOUTOU;
	kj.canshu2 = 0x0;
	kj.canshu3 = 0x544D0EA8;
	kj.canshu4 = 0x0;
	kj.canshu5 = adress1;      
	kj.canshu6 = 0x1;
	kj.canshu7 = 0x2;
	kj.canshu8 = 0x0;
	kj.canshu9 = 0x0;
	kj.canshu10= 0x0;
	kj.canshu11= 0x0;
	kj.canshu12= 0x4EFE0016;

	_try{
		_asm{
			mov ecx,adress; //����ǿؼ����׵�ַ  "SkillTrainPanel"
			mov edx,[ecx];
			mov eax,[edx+0x4];

			lea ebx,kj;
			push ebx;
			call eax  
		}
	}

	_except(1){
		TRACE(_T("�����ȫ�����ܽ���CALL����"));
	}
}


//����ռ��ܵ��ui
void Gamecall::OpenDeleteTalentPanel()
{
	DWORD dwUIAddr = 0;
	PARAM_GETUIADDRBYNAME temp;
	temp.argv1 = (DWORD)GetUIBinTreeBaseAddr();
	temp.argv2 = (DWORD)L"SkillTrainPanel";
	temp.argv3 = (DWORD)&dwUIAddr;
	DWORD canshu2 = 0;
	canshu2 =  ReadDWORD(dwUIAddr+0x58);

	if(canshu2 > 0){
		DaKaiQingChuQuanBuJiNengJieMian(dwUIAddr,canshu2); //�����ȫ�����ܽ���
	}
}

//ȷ�����ȫ�����ܽ���
void Gamecall::QueRenQingChuQuanBuJiNengJieMian(DWORD adress,DWORD adress1) 
{


	KONGJ kj;
	kj.canshu1 = QUDINGYAOJIANG_JIEGOUTOU;
	kj.canshu2 = 0x0;
	kj.canshu3 = 0x544D0EA8;
	kj.canshu4 = 0x0;
	kj.canshu5 = adress1;      //�ؼ����׵�ַ+0x70
	kj.canshu6 = 0x1;
	kj.canshu7 = 0x2;
	kj.canshu8 = 0x0;
	kj.canshu9 = 0x0;
	kj.canshu10= 0x0;
	kj.canshu11= 0x0;
	kj.canshu12= 0x4EFE0016;

	__try{
		__asm{
			mov ecx,adress; //����ǿؼ����׵�ַ  "SkillTrainInitConfirmPanel"
			mov edx,[ecx];
			mov eax,[edx+0x4];

			lea ebx,kj;
			push ebx;
			call eax  
		}
	}

	__except(1)
	{
		TRACE(_T("ȷ�����ȫ�����ܽ���CALL����"));
	}
}

//ȷ��ɾ���츳��ui
void Gamecall::ConfirmDeletePalentPanelShowOk()
{
	DWORD dwUIAddr = 0;
    GetUIAddrByName(L"SkillTrainInitConfirmPanel", &dwUIAddr);
	if(dwUIAddr){
		DWORD canshu2 = 0;
		canshu2 =  ReadDWORD(dwUIAddr+0x70);
		
		if (canshu2 > 0){
			QueRenQingChuQuanBuJiNengJieMian(dwUIAddr,canshu2); //ȷ�����ȫ�����ܽ���
		}
	}
	
}

//ȷ������츳��ui��û����ʾ
BOOL Gamecall::isConfirmDeleteTalnetPanelShow()
{
	DWORD dwUIAddr = 0;
    GetUIAddrByName(L"SkillTrainInitConfirmPanel", &dwUIAddr);
	if(dwUIAddr != 0){
		DWORD canshu2 = 0;
		canshu2 =  ReadDWORD(dwUIAddr+clearstrike_isopen);
		if (canshu2){
			return TRUE;
		}
		if(canshu2 == 0){
			TRACE(_T("������ܽ���û�д�"));
		}
	}

	return FALSE;

}

void Gamecall::QueRenJiNengDian() //ȷ�ϼ��ܵ�
{
	_try{
		_asm{
			mov eax, obj_enum_base;
			mov eax, [eax];
			mov eax, [eax+confrim_add_strike_offset1];   //ȷ�ϼ��ܵ�һ��ƫ��
			mov eax, [eax+confrim_add_strike_offset2];   //ȷ�ϼ��ܵ����ƫ��
			mov eax, [eax+confrim_add_strike_offset3];  //ȷ�ϼ��ܵ�����ƫ��
			push eax;
			mov eax, confrim_call;
			call eax;
	

		}
	}
	_except(1){
		TRACE(_T("ȷ�ϼ��ܵ����"));
	}

}

void Gamecall::JiaJiNengDian(DWORD ID) //�Ӽ��ܵ�
{
	_try{
		_asm{


			push 0;
			mov eax,ID;
			push eax;
			mov eax,obj_enum_base;
			mov eax,[eax];
			mov eax,[eax+add_strike_offset1];   //�Ӽ��ܵ�һ��ƫ��
			mov eax,[eax+add_strike_offset2];   //�Ӽ��ܵ����ƫ��
			mov eax,[eax+add_strike_offset3];  //�Ӽ��ܵ�����ƫ��
			push eax; 
			mov ebx,add_strike_call;
			call ebx;


		}
	}
	_except(1){
		TRACE(_T("�Ӽ��ܵ����"));
	}

}

//�츳����Ƿ���ʾ
BOOL Gamecall::isTalentPanelShow()
{

	DWORD dwUIAddr = 0;
    GetUIAddrByName(L"SkillTrainPanel", &dwUIAddr);

	DWORD canshu2 = 0;
	canshu2 =  ReadDWORD(dwUIAddr+skillpanel_isshow);

	if ( canshu2 == 1 ){
		return TRUE;
	}
	if ( canshu2 == 2 ){
		TRACE(_T("�������û�д�"));
	}

	return FALSE;
}

//����ģʽCALL
void Gamecall::JingDianMoShi(DWORD adress, DWORD c5)
{
	KONGJ kj;
	kj.canshu1 = JINGDIANMOSHICALL_JIEGOUTOU;
	kj.canshu2 = 0x0;
	kj.canshu3 = 0x544D0EA8;
	kj.canshu4 = 0x0;
	kj.canshu5 = c5;      //�ؼ����׵�ַ+0x36FB0
	kj.canshu6 = 0x1;
	kj.canshu7 = 0x2;
	kj.canshu8 = 0x0;
	kj.canshu9 = 0x0;
	kj.canshu10 = 0x0;
	kj.canshu11 = 0x0;
	kj.canshu12 = 0x4EFE0016;
	
	__try
	{
		__asm
		{
			mov ebx, adress;  //����ǿؼ����׵�ַ  "OptionPanel"
			mov ebx, [ebx + mouse_mode_class_offset1 + mouse_mode_class_offset11];
			mov eax, 0x1;
			mov dword ptr ds : [ebx + mouse_mode_class_offset2], eax;
			
			mov ecx, adress; //����ǿؼ����׵�ַ  "OptionPanel"
			mov edx, [ecx];
			mov eax, [edx + 0x4];
			
			lea ebx, kj;
			push ebx;
			
			call eax
		}
	}
	
	__except(1)
	{
		OutputDebugString(FUNCNAME);
	}
}


//���ܹ���
//����1: ��������
void Gamecall::Attack(const wchar_t *name)
{
	STRIKEINFO sinfo;
	if(GetStrikeByName(name, &sinfo))
	{
		sendcall(id_msg_attack, (LPVOID)sinfo.id1);
	}
}


//����ĳ������
BOOL Gamecall::Step(ObjectNode* pNode)
{
	
	fPosition fpos;
	if(GetObjectPos(pNode, &fpos))
	{
		Step(fpos.x, fpos.y, fpos.z);
		return TRUE;
	}
	
	return FALSE;
}


//��ȡ��ͼid
DWORD Gamecall::GetCityID()
{
	DWORD PlayerInfo = GetPlayerDataAddr();
	DWORD cityid = UINT_MAX;
	
	__try
	{
		__asm
		{
			mov eax, PlayerInfo;
			mov eax, [eax + player_mapid];
			mov cityid, eax;
		}
	}
	__except(1)
	{
		OutputDebugString(FUNCNAME);
	}
	
	return cityid;
}

//һ���װ, ����ȴ�, ������ŷ���
BOOL Gamecall::PickupTask(ObjectNode* pNode)
{
	
	sendcall(id_msg_PickupTask, pNode);
	
	
	//�ж϶���
	//��������, һ����ʱ, һ���������
	if(isPlayerChanneling() == FALSE)
		return FALSE;
	
	
	for(;;)
	{
		if(isPlayerChanneling() == FALSE)
			break;
		Sleep(10);
	}
	
	
	if(isPlayerHasPickupQuestItemUI())
	{
		sendcall(id_msg_Pickup2, pNode);
		return TRUE;
	}
	
	
	return FALSE;
	
}


//�Ƿ��ܿ���
BOOL Gamecall::isCanLook(DWORD pAddr)
{
   //BYTE temp;
    wchar_t* name = (wchar_t *)ReadDWORD(ReadDWORD(pAddr + obj_type4_name_offset1)+0x10);

    __try{
		//temp = ReadByte(pAddr +0x9C);
        __asm{
            lea eax, name;
            mov ebx, [eax]; //�����Ƿ�ɶ��ĵ�ַ
        }
		//log.logdv(_T("name:%s"),name);
		if(IsBadStringPtr(name, MAX_PATH) == FALSE)
		{
			if (wcsstr(name, L"Dummy") != NULL)
			{
				return FALSE;
			}
		}
		/*if (temp == 9)
		{
			return TRUE;
		}*/
    }
    __except(1){
        log.logdvHex((BYTE*)name);
    }
	//log.logdv(_T("temp:%d"),temp);
    return TRUE;
}

BOOL Gamecall::isPlayerDaodi()
{
	DWORD m_Adress = GetPlayerDataAddr();
	DWORD Adress = 0;
	bool State = FALSE;
	_try
	{
		if(m_Adress)
		{
			Adress =ReadWORD(m_Adress + player_status_down);
		}	
		if(Adress == 0)
		{
			State = FALSE;
		}
		else
		{
			State = TRUE;
		}
	}
	_except(1)
	{
		TRACE(_T("��ȡ��ɫ����״̬����"));
	}

	return State;	
}

void Gamecall::_NewSpend(float x)
{
	//DWORD dwThreadId;

	if(m_pfnInitSpeed != NULL){
		m_pfnInitSpeed(x);
	}
}

BOOL Gamecall::isStrikeCd(DWORD id)
{
	std::vector<STRIKEINFO> StrikeVec;
	GetStrikeToVector(StrikeVec);

	for(int i = 0; i < StrikeVec.size(); i++){
		if(StrikeVec[i].id1 == id){
			if (StrikeVec[i].isBlock == 1 && StrikeVec[i].canUse == 0)
			{
				return (StrikeVec[i].cd == 0);
			}else
			{
				break;
			}
			
		}
	}
	return FALSE;
}

BOOL Gamecall::GetPlayExperienceStatus()
{
	//KONGJIAN_JIEGOU JIEGOU = {NULL};
	//DWORD *pUiAddr = 0;
	//wchar_t *str = L"";  //ItemGrowth2Panel
	//GetUIAddrByName(L"", pUiAddr);
	//if(*pUiAddr == 0)
	//	return FALSE;
	KONGJIAN_JIEGOU jiegou = {NULL};
	jiegou.adress = (DWORD)GetUIBinTreeBaseAddr();
	jiegou.name = L"Normal";
	jiegou.ID = 0;
	GetUiAddrByName(jiegou);
	DWORD pos = -1;
	pos = ReadDWORD(ReadDWORD(jiegou.ID+0x83F8)+0x1C);
	TRACE(_T("����Ч����ID %X"),pos);
	if ( pos!=0 )
	{
		TRACE(_T("����ҩ���Ѿ�����,����Ҫ�ٳ���"));
		return TRUE;
	}
	if ( pos == 0 )
	{
		TRACE(_T("û�гԾ���ҩ��,��Ծ���ҩ��"));
	}
	return FALSE;
}

void Gamecall::GetUiAddrByName(KONGJIAN_JIEGOU &jiegou)
{
	log.logdv(_T("add:%x,name:%s,fanhui:%x"),jiegou.adress,jiegou.name,jiegou.ID);
	sendcall(id_msg__GetUiAddrByName,&jiegou);
}

void Gamecall::_GetUiAddrByName(Tree* Addr,wchar_t* name,DWORD &reAddr)
{
	if (Addr->p2 == 1)		
	{
		//TRACE("�Ƴ���");
		return ;
	}
	if ( reAddr > 0) //
	{
		//TRACE("������");
		return;
	}
	wchar_t* uiname  = {0};
	if(!IsBadReadPtr((void*)GetUiNewName(Addr->Adress), sizeof(DWORD)))
	{
		uiname = GetUiNewName(Addr->Adress);//��ȡ�����������
		if (wcsstr(uiname,name) != NULL)
		{
			//TRACE("�ҵ���Ҫ�Ŀؼ���");
			//log.logdv(_T("�ҵ�UI��:%s,�ҵ��ؼ���ַ:%d"),uiname,Addr->Adress);
			reAddr = Addr->Adress;
			return ;
		}
	}
	_GetUiAddrByName(Addr->Right,name,reAddr);
	_GetUiAddrByName(Addr->Left,name,reAddr);
}

wchar_t* Gamecall::GetUiNewName(DWORD pBarAddr)
{
	wchar_t *name = {0};
	__try
	{
		name = (wchar_t *)ReadDWORD(pBarAddr +0x94);
	}
	__except(1)
	{
		OutputDebugString(L"��ȡ����������ִ���");
	}
	return name;

}
