#include "stdafx.h"
#include "JLwg.h"
#include "Gamecall.h"
#include "GamecallEx.h"
#include "GameConfig.h"
#include "GameSpend.h"
#include "gamehook.h"
#include "GameLog.h"
//全局变量
const double M_PI = 3.14159265358979323846;



IMPLEMENT_SINGLETON(Gamecall)


//构造函数
Gamecall::Gamecall()
{
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
        TRACE(_T("传送  error"));
    }
}




void Gamecall::Fuhuo(DWORD uiAddr)
{

    __try
    {
        TRACE(_T("进入复活call uiAddr:%d"), uiAddr);
        __asm
        {
            mov eax, uiAddr;
            push eax;
            mov ecx, 0x3;
            mov eax, fuhuo_call;
            call eax;
        }
    }
    __except(1)
    {
        TRACE(_T("复活失败"));
    }
}



//打开天赋ui
void Gamecall::OpenTalentUI()
{
    sendcall(id_msg_OpenTalentUI, 0);
}



//打开天赋ui
void Gamecall::_OpenTalentUI()
{
    DWORD dwUIAddr = 0;
    GetUIAddrByName(L"SystemMenuPanel", &dwUIAddr);

    if(dwUIAddr)
    {
        DWORD canshu2 = 0;
        canshu2 =  ReadDWORD(ReadDWORD(dwUIAddr + 0x4C) + 0x7D4);

        if(canshu2 > 0)
        {
            DaKaiJiNengMianBan(dwUIAddr, canshu2); //打开技能面板
        }
    }
}

void Gamecall::DaKaiJiNengMianBan(DWORD adress, DWORD adress1) //打开技能面板
{

    KONGJ kj;
    kj.canshu1 = QUDINGYAOJIANG_JIEGOUTOU;
    kj.canshu2 = 0x0;
    kj.canshu3 = 0x544D0EA8;
    kj.canshu4 = 0x0;
    kj.canshu5 = adress1;      //[[控件的首地址+0x4C]+0x7D4]
    kj.canshu6 = 0x1;
    kj.canshu7 = 0x2;
    kj.canshu8 = 0x0;
    kj.canshu9 = 0x0;
    kj.canshu10 = 0x0;
    kj.canshu11 = 0x0;
    kj.canshu12 = 0x4EFE0016;

    __try
    {
        _asm
        {
            mov ecx, adress; //这个是控件的首地址  "SystemMenuPanel"
            mov edx, [ecx];
            mov eax, [edx+0x4];

            lea ebx, kj;
            push ebx;
            call eax
        }
    }
    __except(1)
    {
        TRACE(_T("打开技能面板CALL错误"));
    }
}


DWORD Gamecall::call(DWORD id, LPVOID pParam)
{
    switch(id)
    {
		case id_msg_GetPlayExperienceStatusName:
			{
				KONGJIAN_JIEGOU* jiegou = (KONGJIAN_JIEGOU*)pParam;
				//TRACE1("jiegou:%08x",jiegou->adress);
				return (BOOL)GetPlayExperienceStatusName(jiegou->adress,jiegou->name);
			}
			break;
        case id_msg_XieZhuangBei:
            {
                PARAM_JIEFENGZHUANGBEI* temp = (PARAM_JIEFENGZHUANGBEI*)pParam;
                _XieZhuangBei(temp->argv1);
            }
            break;
        case id_msg_IsCanShu:
            {
                PARAM_JIEFENGZHUANGBEI* temp = (PARAM_JIEFENGZHUANGBEI*)pParam;
                return (DWORD)_IsCanShu(temp->argv1, temp->argv2);
            }
            break;
        case id_msg_NPCJieRenWu:
            {
                PARAM_JIEFENGZHUANGBEI* temp = (PARAM_JIEFENGZHUANGBEI*)pParam;
                _NPCJieRenWu(temp->argv1, temp->argv2, temp->argv3, temp->argv4, temp->argv5);
            }
            break;
        case id_msg_OpenTalentUI:
            {
                _OpenTalentUI();
            }
            break;
        case id_msg_ConfirmDeletePalentPanelShowOk:
            {
                _ConfirmDeletePalentPanelShowOk();
            }
            break;
        case id_msg_OpenDeleteTalentPanel:
            {
                _OpenDeleteTalentPanel();
            }
            break;
        case id_msg_QueRenJiNengDian:
            {
                _QueRenJiNengDian();
            }
            break;
        case id_msg_QuChuJiNengDian:
            {
                _QuChuJiNengDian((DWORD)pParam);
            }
            break;
        case id_msg_JiaJiNengDian:
            {
                _JiaJiNengDian((DWORD)pParam);
            }
            break;
        case id_msg_LinQuJiangLi:
            {
                _LinQuJiangLi();
            }
            break;
        case id_msg_GetStrikeToVector:
            {
                GetStrikeToVector(*(std::vector<STRIKEINFO>*)pParam);
            }
            break;
        case id_msg__GetUiAddrByName:
            {
                KONGJIAN_JIEGOU* jiegou = (KONGJIAN_JIEGOU*)pParam;
                _GetUiAddrByName((Tree*)jiegou->adress, jiegou->name, jiegou->ID);
            }
            break;
        case id_msg_NewSpend:
            {
                _NewSpend(*(float*)pParam);
            }
            break;
        case id_msg_GetAllBodyEquipToVector:
            {
                _GetAllBodyEquipToVector(*(std::vector<_BAGSTU>*)pParam);
            }
            break;
        case id_msg_GetAllGoodsToVector:
            {
                _GetAllGoodsToVector(*(std::vector<_BAGSTU>*)pParam);

            }
            break;
        case id_msg_GetAcceptedQuestToVector:
            {
                _GetAcceptedQuestToVector(*(std::vector<Quest>*)pParam);
            }
            break;
        case id_msg_GetRangeObjectToVector:
            {
                PARAM_GETUIADDRBYNAME* temp = (PARAM_GETUIADDRBYNAME*)pParam;
                _GetRangeObjectToVector((ObjectNode*)temp->argv1, temp->argv2, *(std::vector<ObjectNode*>*)temp->argv3);
            }
            break;

        case id_msg_GetUItoVector:
            {
                PARAM_GUANSHANGDIAN* temp = (PARAM_GUANSHANGDIAN*)pParam;
                _GetUItoVector((Tree*)temp->argv1, *(std::vector<Tree*>*)temp->argv2);
            }
            break;
        case id_msg_OverShunyi:
            {
                OverShunyi((BOOL)pParam);
            }
            break;
        case id_msg_GetObjectNameByIndex:
            {
                return (DWORD)_GetObjectNameByIndex((DWORD)pParam);
            }
            break;
        case id_msg_isYaoPingCD:
            {
                _BAGSTU* temp = (_BAGSTU*)pParam;
                return isYaoPingCD(*temp);
            }
        case id_msg_GouMaiWuPing:
            {
                PARAM_GETUIADDRBYNAME* temp = (PARAM_GETUIADDRBYNAME*)pParam;
                GouMaiWuPing(temp->argv1, temp->argv2, temp->argv3);
            }
            break;

        case id_msg_XieBaoShi:
            {
                PARAM_GETUIADDRBYNAME* temp = (PARAM_GETUIADDRBYNAME*)pParam;
                XieBaoShi(temp->argv1, temp->argv2, temp->argv3);
            }
            break;

        case id_msg_JiaBaoShi:
            {
                PARAM_JIEFENGZHUANGBEI* temp = (PARAM_JIEFENGZHUANGBEI*)pParam;
                JiaBaoShi(temp->argv1, temp->argv2, temp->argv3, temp->argv4, temp->argv5);
            }
            break;

        case id_msg_JieFengZhuangBei:
            {
                PARAM_JIEFENGZHUANGBEI* temp = (PARAM_JIEFENGZHUANGBEI*)pParam;
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
                _BAGSTU* temp = (_BAGSTU*)pParam;
                KaiHeZi(*temp);
            }
            break;

        case id_msg_SellItem:
            {
                _PARAM_GUANSHANGDIAN* temp = (_PARAM_GUANSHANGDIAN*)pParam;
                SellItem(*(_BAGSTU*)temp->argv1, temp->argv2);
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
                ObjectNode* temp = (ObjectNode*)pParam;
                _PickupTask(temp);
            }
            break;
        case id_msg_Pickup1:
            {
                ObjectNode* temp = (ObjectNode*)pParam;
                Pickup1(temp);
            }
            break;
        case id_msg_Pickup2:
            {
                ObjectNode* temp = (ObjectNode*)pParam;
                Pickup2(temp);
            }
            break;
        case id_msg_Pickup2ts:
            {
                Pickup2ts();
            }
            break;
        case id_msg_OpenQuestItem:
            {
                PARAM_GUANSHANGDIAN* temp = (PARAM_GUANSHANGDIAN*)pParam;
                OpenQuestItem(temp->argv1, temp->argv2);
            }
            break;


        case id_msg_ZOULUSHUNYI:
            {
                PARAM_GUANSHANGDIAN* temp = (PARAM_GUANSHANGDIAN*)pParam;
                ZOULUSHUNYI((DWORD*)temp->argv1, temp->argv2);
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
                UIOperator* temp = (UIOperator*)pParam;
                JingDianMoShi((DWORD)temp->pAddr, temp->c5);
            }
            break;
        case id_msg_PickupDeadbody:
            {
                PARAM_GUANSHANGDIAN* temp = (PARAM_GUANSHANGDIAN*)pParam;
                PickupDeadbody(temp->argv1, temp->argv2);
            }
            break;
        case id_msg_HeChengWuQi_Po10:
            {
                PARAM_GETUIADDRBYNAME* temp = (PARAM_GETUIADDRBYNAME*)pParam;
                HeChengWuQi_Po10(*(_BAGSTU*)temp->argv1, *(_BAGSTU*)temp->argv2, temp->argv3);
            }
            break;


        case id_msg_FaSonXianLuBao:
            {
                FaSonXianLuBao((DWORD)pParam);
            }
            break;


        case id_msg_DeliverQuests:
            {
                PARAM_DELIVERQUEST* temp = (PARAM_DELIVERQUEST*)pParam;
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
                _BAGSTU* temp = (_BAGSTU*)pParam;
                DeleteItem(*temp);
            }
            break;


        case id_msg_ChiYao:
            {

                ChiYao(*(_BAGSTU*)pParam);
            }
            break;
        case id_msg_step:
            {

                fPosition* pStepParam = (fPosition*)pParam;
                Step(pStepParam->x, pStepParam->y, pStepParam->z);
            }
            break;

        case id_msg_step3x:
            {

                fPosition* pStepParam = (fPosition*)pParam;
                Step3x(pStepParam->x, pStepParam->y, pStepParam->z);
            }
            break;
        case id_msg_vector_ui:
            {
                std::vector<Tree*>* pAllui = (std::vector<Tree*>*)pParam;
                GetUItoVector(GetUIBinTreeBaseAddr(), *pAllui);
            }
            break;

        case id_msg_guanshangdian:
            {
                UIOperator* temp = (UIOperator*)pParam;
                GuanBiDuiHuaKuangChuanKou((DWORD)temp->pAddr, temp->c5);
            }
            break;
        case id_msg_DaKaiDuiHuaKuang:
            {
                PARAM_GUANSHANGDIAN* temp = (PARAM_GUANSHANGDIAN*)pParam;
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
                UIOperator* pOpui = (UIOperator*)pParam;
                ClickUI(*pOpui);
            }
            break;

        case id_msg_HeChengWuQi_Po5:
            {
                PARAM_GUANSHANGDIAN* temp = (PARAM_GUANSHANGDIAN*)pParam;
                HeChengWuQi_Po5(*(_BAGSTU*)temp->argv1, *(_BAGSTU*)temp->argv2);
            }
            break;

        case id_msg_HeChengWuQi:
            {
                PARAM_GUANSHANGDIAN* temp = (PARAM_GUANSHANGDIAN*)pParam;
                HeChengWuQi(*(_BAGSTU*)temp->argv1, *(_BAGSTU*)temp->argv2);
            }
            break;


        case id_msg_WearEquipment:
            {
                _BAGSTU* bag = (_BAGSTU*)pParam;
                WearEquipment(*bag);
            }
            break;

        case id_msg_Fenjie:
            {
                _BAGSTU* temp = (_BAGSTU*)pParam;
                FenJie(*temp);
            }
            break;


        case id_msg_CunCangku:
            {
                PARAM_GUANSHANGDIAN* temp = (PARAM_GUANSHANGDIAN*)pParam;
                CunCangku(*(_BAGSTU*)temp->argv1);
            }
            break;
    }

    return 0;
}



//合成武器
void Gamecall::HeChengWuQi(_BAGSTU& zhu, _BAGSTU& fu)
{


    int zhu_value = zhu.m_Info;
    zhu_value <<= 16;
    zhu_value += body;

    int fu_value = fu.m_Info;
    fu_value <<= 16;
    fu_value += package;



    TRACE(_T("%s: %08x, %08x"), FUNCNAME, zhu, fu);
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
            mov eax, obj_enum_base;
            mov eax, [eax];
            mov eax, [eax+ hewuqi_offset1];
            mov eax, [eax+ hewuqi_offset2];
            mov ecx, [eax+ hewuqi_offset3];
            mov eax, hewuqi_call ;
            call eax;
        }
    }
    __except(1)
    {
        TRACE(_T("合成武器出错"));
    }
}



//根据位置取得物品信息
//1 = 武器
//2 = 衣服
//7 = 项链
//3 = 耳环
//6 = 戒指
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

//根据名字取得物品信息
BOOL Gamecall::GetGoodsFromBagByName(const wchar_t* name, std::vector<_BAGSTU>& GoodsVec)
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

//根据名字取得物品信息
//这个函数是专门找盒子名字的
//区别就是对名字的匹配上
BOOL Gamecall::GetGoodsByName_Hezi(wchar_t* name, std::vector<_BAGSTU>& GoodsVec)
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

    //根据名字过滤, 优先 8, 5, 3, 1
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

//根据名字取物品信息
BOOL Gamecall::GetGoodsFromEquipByName(wchar_t* name, _BAGSTU* goods)
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


//根据名字取得物品信息
BOOL Gamecall::GetGoodsFromBagByName(const wchar_t* name, _BAGSTU* goods,BOOL Blur)
{
    assert(name != NULL);

    std::vector<_BAGSTU> GoodsVec;
    GetAllGoodsToVector(GoodsVec);

    //背包遍历
    for(DWORD i = 0; i < GoodsVec.size(); i++)
    {
		if (Blur == TRUE)
		{
			int len = wcslen(name);
			wchar_t* fixName = new wchar_t[len];
			wcscpy(fixName, name);
			fixName[len] = L'\0';
			//MessageBox(NULL,fixName,NULL,NULL);
			if(wcsstr(GoodsVec[i].name, fixName) != NULL)
			{
				*goods = GoodsVec[i];
				return TRUE;
			}
		}else
		{
			if(wcscmp(name, GoodsVec[i].name) == 0)
			{
				*goods = GoodsVec[i];
				return TRUE;
			}
		}
    }

    return FALSE;
}



//放下尸体
void Gamecall::PickdownBody()
{
    __try
    {
        __asm
        {
            mov eax, obj_enum_base;
            mov eax, [eax];
            mov eax, [eax+ pickdown_body_offset1];
            mov eax, [eax+pickdown_body_offset2];
            mov eax, [eax+pickdown_body_offset3];
            add eax, pickdown_body_offset4;
            push eax;
            mov ecx, pickdown_body_offset5;
            mov eax, pickdown_body_call;
            call eax;
        }
    }
    __except(1)
    {
        TRACE(_T("放下尸体"));
    }
}


//登录游戏, 参数是登录的角色
BOOL Gamecall::LoginInGame(DWORD index)
{
    //先判断玩家是否已经在游戏内

    if(isLoadingMap() != 3)
    {

        ConfirmAgreement(); //确认游戏使用协议
        LoginGame(index);       //进入游戏
        WaitPlans();        //等待读条
        //CloseAttendance();    //关掉老虎机
    }

    //SetMouseMode();           //TODO: 暂时不能用


    return TRUE;
}


void Gamecall::HookQietu(BOOL bEnable)
{
    GameHook* pHooker = GameHook::GetInstance();
    if(bEnable)
    {
        pHooker->hookQietu.hook();
    }
    else
    {
        pHooker->hookQietu.unhook();
    }

}


//初始化函数
BOOL Gamecall::Init()
{
    try
    {
        //获取加载的游戏dll的地址
        m_hModuleBsEngine = GetModuleHandle(_T("bsengine_Shipping"));
        if(m_hModuleBsEngine == NULL)
        {
            TRACE(_T("获取BsEngine模块失败"));
            return FALSE;
        }
    }
    catch(...)
    {
        TRACE(_T("%s Error!"), FUNCNAME);
    }

    return TRUE;
}

//整理背包ui
BOOL Gamecall::SortBag()
{
    __try
    {
        UIOperator uiOp;
        DWORD UIAddr = 0;
        GetUIAddrByName(L"Inventory2Panel", &UIAddr);

        uiOp.pAddr = (DWORD*)UIAddr;
        uiOp.c5 = *(DWORD*)(UIAddr + bag_refresh_c5);
        sendcall(id_msg_clickui, &uiOp);

        return TRUE;
    }
    __except(1)
    {
        TRACE(FUNCNAME);
    }

    return FALSE;
}

//村仓库
//参数1: 背包中的格子数
void Gamecall::CunCangku(_BAGSTU& goods)
{
    TRACE1("格子:%d", goods.m_Info);
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
        TRACE(FUNCNAME);
    }

}

//合成武器破10
void Gamecall::HeChengWuQi_Po10(_BAGSTU& zhu, _BAGSTU& fu, DWORD adress)
{

    int zhu_value = zhu.m_Info;
    zhu_value <<= 16;
    zhu_value += package;

    int fu_value = fu.m_Info;
    fu_value <<= 16;
    fu_value += package;


    TRACE(_T("%s: %08x, %08x,%08x"), FUNCNAME, zhu_value, fu_value, adress);


    YouJianLeiXing LeiXing;
    LeiXing.canshu1 = fu_value;
    LeiXing.canshu2 = 0;
    LeiXing.canshu3 = 0;
    LeiXing.canshu4 = 0;

    __try
    {
        _asm
        {
            push 0;
            push 0;
            push 1;
            
            //push eax;
            push 0;
            mov eax, zhu_value;
            push eax;
            push 0;
			mov eax, adress;
			push eax;

            mov eax, obj_enum_base;
            mov eax, [eax];
            mov eax, [eax+hewuqi_po10_offset1];
            mov eax, [eax+hewuqi_po10_offset2];
            mov ecx, [eax+hewuqi_po10_offset3];
            push ecx;
			lea ecx, LeiXing;
            mov eax, hewuqi_po10_call;
            call eax;
        }
    }
    __except(1)
    {
        TRACE(_T("合成武器破10出错"));
    }
}



void Gamecall::HeChengWuQi_Po5(_BAGSTU& zhu, _BAGSTU& fu) //合成武器破5
{

    int zhu_value = zhu.m_Info;
    zhu_value <<= 16;
    zhu_value += body;

    int fu_value = fu.m_Info;
    fu_value <<= 16;
    fu_value += package;



    //TRACE(_T("%s: %08x, %08x"), FUNCNAME, zhu, fu);


    __try
    {
        __asm
        {
            push 0;
            push 0;
            push 0;
            mov eax, fu_value;
            push eax;
            push 0;
            mov ecx, zhu_value;
            push ecx;
            mov eax, obj_enum_base;
            mov eax, [eax];
            mov eax, [eax+hewuqi_po5_offset1];
            mov eax, [eax+hewuqi_po5_offset2];
            mov ecx, [eax+hewuqi_po5_offset3];
            mov eax, hewuqi_po5_call;
            call eax;
        }
    }
    __except(1)
    {
        TRACE(_T("合成武器破5出错"));
    }
}



void Gamecall::_GetAcceptedQuestToVector(std::vector<Quest>& QuestVec)
{
    int TaskNum = 53;

    DWORD pStartAddr = GetTaskStartAddr();  //获取任务开始地址
    Quest qst;

    for(int i = 0; i < TaskNum; i++)
    {
        //DWORD *pAddr        =     gcall.GetTaskPresentAddr(i, pStartAddr);  //获得当前任务地址
        qst.id = GetTaskID(i, pStartAddr);  //获得当前任务ID
        qst.name_id = GetTaskNameID(i, pStartAddr);  //获得当前任务名字ID
        qst.step = GetPresentTaskIndexes(i, pStartAddr);  //获得当前做到第几个小任务
        qst.endflag = GetPresentTaskEndFlag(i, pStartAddr, qst.step);  //获得当前小任务结束标志
        qst.num = GetPresentTaskNum(i, pStartAddr, qst.step);  //获得当前小任务已经打的怪数量
        qst.name = GatTaskName(qst.name_id);//获取当前已接任务名字

        if(qst.name)
        {
            QuestVec.push_back(qst);
        }
        else
        {
            //遍历完成
            break;
        }
    }
}

void Gamecall::GetAcceptedQuestToVector(std::vector<Quest>& QuestVec)
{
    sendcall(id_msg_GetAcceptedQuestToVector, &QuestVec);
}


/*周围环境对象二叉树的基地址*/
ObjectNode* Gamecall::GetObjectBinTreeBaseAddr()
{
    ObjectNode* Note = NULL;
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
        TRACE(FUNCNAME);
    }

    /*取得了, 遍历到*/
    return Note;
}



wchar_t* Gamecall::GetPlayerName()
{
    DWORD PlayerInfo = GetPlayerDataAddr();
    wchar_t* PlayerName = NULL;

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
        TRACE(FUNCNAME);
    }
    return PlayerName;
}


//角色ID
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
        TRACE(FUNCNAME);
    }
    return PlayerID;
}

//取得玩家数据地址的辅助函数
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
        TRACE(FUNCNAME);
    }

    return PlayerInfo;
}


//取得玩家坐标
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

            mov edx, eax; /*保存一下*/
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
        TRACE(FUNCNAME);
    }



    return FALSE;
}


//取得玩家坐标
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
        TRACE(FUNCNAME);
    }

    return FALSE;
}



//玩家最大轻功
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
        TRACE(FUNCNAME);
    }
    return PlayerVit;
}

//玩家轻功
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
        TRACE(FUNCNAME);
    }
    return PlayerVit;
}


//取得玩家内力
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
        TRACE(FUNCNAME);
    }

    return Vit;
}

/*玩家轻功状态
1, 使用了轻功
2, 轻功正在恢复
3, 轻功已经满*/
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
        TRACE(FUNCNAME);
    }
    return status;
}


//获取角色最大血值
DWORD Gamecall::GetPlayerMaxHealth()
{
    DWORD wMaxBlood;
    DWORD wMaxBlood1;

    DWORD m_Adress = GetPlayerDataAddr();
    wMaxBlood = 0;
    wMaxBlood1 = 0;
    __try
    {
        if(m_Adress)
        {
            wMaxBlood = ReadDWORD(m_Adress + player_max_health);
            wMaxBlood1 = ReadDWORD(m_Adress + player_bagua_health);
            wMaxBlood = wMaxBlood + wMaxBlood1;
        }
    }
    __except(1)
    {
        TRACE(FUNCNAME);
    }

    return wMaxBlood;
}


//玩家当前血量
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
        TRACE(FUNCNAME);
    }

    return Health;
}

void* Gamecall::GetStepCallAddr()
{
    void* pCall = NULL;

    __try
    {
        __asm
        {
            mov eax, step_call_base;
            mov eax, [eax];
            call eax;  //走步

            mov edx, [eax];
            mov ecx, eax;
            mov eax, [edx + step_call_offset1];
            mov pCall, eax;
        }
    }
    __except(1)
    {
        TRACE(FUNCNAME);
    }

    return pCall;
}

//走路
void Gamecall::Step(float x, float y, float z)
{

    __try
    {
        void* pCall = GetStepCallAddr();
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
        TRACE(FUNCNAME);
    }

}

//走路3倍
void Gamecall::Step3x(float x, float y, float z)
{

    __try
    {
        void* pCall = GetStepCallAddr();
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
        TRACE(FUNCNAME);
    }

}


//转向
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
        TRACE(FUNCNAME);
		//TRACE1("bs=%d",m_hModuleBsEngine);
    }
}

//获得对象类型
//type = 0x20 任务物品
//type = 0x4  怪物 npc
//type = 0xb0 尸体和掉落物品,
//type = 0x90 特殊任务物品
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
        //TRACE(_T("GetObjectType-error:%d"),pObjAddress);
        TRACE(FUNCNAME);
        return 0;
    }

    return (BYTE)Objtype;
}



BOOL Gamecall::GetObjectPos(ObjectNode* pNode, fPosition* fpos)
{

    DWORD type = (DWORD)GetObjectType(pNode->ObjAddress);
    if(type == 0x20)
        GetObjectPos2_0x20(pNode->ObjAddress, fpos);
    else if(type == 0xb0)
    {
        sPosition spos;
        GetObjectPos_0xb(pNode->ObjAddress, &spos);
        *fpos = ShortPosToFloatPos(spos);
    }
    else if(type == 0x4)
        _GetObjectPos(pNode->ObjAddress, fpos);
    else if(type == 0x90)
    {
        sPosition spos;
        GetObjectPos2_0x90(pNode->ObjAddress, &spos);
        *fpos = ShortPosToFloatPos(spos);
    }
    else
        return FALSE;

    return TRUE;
}


//对象坐标
//参数1: 基地址
//类型4的移动坐标
BOOL Gamecall::_GetObjectPos(DWORD pObjAddress, fPosition* pos)
{

    BOOL bRet = FALSE;
    __try
    {

        int temp1 = obj_type4_pos_x_offset2 + 4;
        int temp2 = obj_type4_pos_x_offset2 + 8;

        if(!IsBadReadPtr((void*)pObjAddress, sizeof(DWORD)))
        {
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



//对象坐标2, 这是浮点坐标
//对象类型是0x20的用这个取坐标
//取出来的是浮点类型
//参数1: 基地址
BOOL Gamecall::GetObjectPos2_0x20(DWORD pObjAddress, fPosition* pos)
{
    BOOL bRet = FALSE;
    __try
    {
        if(!IsBadReadPtr((void*)pObjAddress, sizeof(DWORD)))
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
        }
        //*4后和 角色坐标是相同的
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

//对象坐标2, 这是浮点坐标
//对象类型是0x20的用这个取坐标
//取出来的是浮点类型
//参数1: 基地址
BOOL Gamecall::GetObjectPos2_0x90(DWORD pObjAddress, sPosition* pos)
{
    BOOL bRet = FALSE;
    __try
    {
        if(!IsBadReadPtr((void*)pObjAddress, sizeof(DWORD)))
        {
            //pos->x = ReadWORD(pObjAddress + 0x2a) * 4;
            //pos->y = ReadWORD(pObjAddress + 0x2c) * 4;
            //pos->z = ReadWORD(pObjAddress + 0x2e) * 4;
            __asm
            {
                mov edx, pObjAddress;
                mov eax, [edx + 0x2A];

                mov ebx, pos;
                mov [ebx]pos.x, ax;

                mov eax, [edx + 0x2c];
                mov [ebx]pos.y, ax;

                mov eax, [edx + 0x2e];
                mov [ebx]pos.z, ax;
            }
        }
        //TRACE3("x:%d,y:%d,z:%d",pos->x,pos->y,pos->z);
        //  *4后和 角色坐标是相同的
        //pos->x = pos->x * 4;
        //pos->y = pos->y * 4;
        //pos->z = pos->z * 4;

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

//对象坐标2, 这是整数坐标
//参数1: 基地址
BOOL Gamecall::GetObjectPos_0xb(DWORD pObjAddress, sPosition* spos)
{
    BOOL bRet = FALSE;
    __try
    {
        if(!IsBadReadPtr((void*)pObjAddress, sizeof(DWORD)))
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
获得对象的名字
参数1: 对象的索引
*/
wchar_t* Gamecall::GetObjectNameByIndex(DWORD index)
{
    //return (wchar_t*)sendcall(id_msg_GetObjectNameByIndex, (LPVOID)index);
    return _GetObjectNameByIndex(index);
}

/*
获得对象的名字
参数1: 对象的索引
*/
wchar_t* Gamecall::_GetObjectNameByIndex(DWORD index)
{

    if(index == UINT_MAX)
        return NULL;

    wchar_t* name;

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

//获取对象的血量
//参数1: 对象地址
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


//固定偏移
DWORD Gamecall::GetObject_0x14(DWORD pObjAddress)
{
    DWORD temp;
    temp = 0;

    __try
    {
        temp = ReadByte(pObjAddress + 0x14);
    }
    __except(1)
    {
        temp = ULONG_MAX;
    }

    return temp;
}

//对象等级
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


//跳跃
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
            mov edx, [eax + 0x3FC]; //TODO: 跳跃的5级偏移
            mov ecx, esi;
            call edx;

        }
    }
    __except(1)
    {
        TRACE(_T("跳跃出错"));
    }
}


//瞬移
void Gamecall::ZOULUSHUNYI(DWORD* adress, DWORD adrewss)
{
    __try
    {
        _asm
        {

            push shunyi_offset1;
            push shunyi_offset2;

            mov eax, obj_enum_base;
            mov eax, [eax];
            mov eax, [eax+shunyi_offset3 ];
            mov eax, [eax+shunyi_offset4];
            mov eax, [eax+shunyi_offset5];
            add eax,  shunyi_offset6 ;
            mov ecx, [eax+ shunyi_offset7];


            mov eax, adress;
            mov [eax+ shunyi_offset7], cx;

            push eax;


            mov eax,  shunyi_call;
            call eax;
        }
    }
    __except(1)
    {
        TRACE(_T("瞬移出错"));
    }
}



//攻击
//参数1: 技能id
void Gamecall::Attack(int id)  //技能攻击  传入的是技能ID
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
        TRACE(FUNCNAME);
    }
}

//取得技能基地址
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
        TRACE(FUNCNAME);
    }

    return Addr;
}

//当前线路是否有效
BOOL Gamecall::isHaveXianlu(int index)
{
    int value = index * xianlu_count_array_size;
    int result = -1;


    DWORD uiAddr = 0;
    GetUIAddrByName(L"AreaInfoPanel", &uiAddr);

    if(uiAddr == 0)
    {
        TRACE(_T("isHaveXianlu 获取ui地址失败"));
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
        //TRACE1("result:%d",result);
    }
    __except(1)
    {
        TRACE(FUNCNAME);
    }

    return (result != -1);
}

//关闭对话框窗口CALL
//参数1: ui地址
//参数2: c5参数

void Gamecall::GuanBiDuiHuaKuangChuanKou(DWORD adress, DWORD adress1)
{

    KONGJ kj;
    kj.canshu1 = GUANBICHUANGKOUCALL_JIEGOUTOU;
    kj.canshu2 = 0x0;
    kj.canshu3 = 0x5468B3C2;
    kj.canshu4 = 0x0;
    kj.canshu5 = adress1;      //控件的首地址+0x40
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
            mov ecx, adress; //这个是控件的首地址 "TalkControlPanel"
            mov edx, [ecx];
            mov eax, [edx + 0x4];

            lea ebx, kj;
            push ebx;

            call eax;

        }
    }
    __except(1)
    {
        TRACE(FUNCNAME);
    }
}





//获取线路数量
DWORD Gamecall::GetXianluNums()
{

    OpenXianluUI();
    Sleep(2000);


    int count = 0;
    for(int i = 0; i < 30; i++)
    {
        if(isHaveXianlu(i))
            count++;
        else
            break;
    }

    return count;
}

//取得一个面板的名字
//参数1: 面板的地址
wchar_t* Gamecall::GetUIName(DWORD pBarAddr)
{
    if(pBarAddr == NULL)
    {
        TRACE(_T("GetUIName: 参数 = NULL"));
        return NULL;
    }

    wchar_t* name;
    __try
    {
        __asm
        {
            mov eax, pBarAddr;
            mov eax, [eax + 0x0c];

            mov name, eax;
            mov eax, [eax];  //用来检测是否可读
        }
    }
    __except(1)
    {
        name = NULL;
    }

    return name;
}

//判断角色是否走路中
// == 1 是在走路中
// == 0 不再走路中
BOOL Gamecall::isPlayerSteping()
{
    DWORD playerdata = GetPlayerDataAddr();

    UCHAR state = false;
    __try
    {
        __asm
        {
            mov eax, playerdata;
            mov eax, [eax + player_status_step_offset1];
            mov eax, [eax + player_status_step_offset2];
            mov state, al;
        }
    }
    __except(1)
    {
        TRACE(FUNCNAME);
    }

    return (state == 1);
}

//[[[[0x0F9E11C]+0x34]+0x80]+744] == 角色所在线路
UCHAR Gamecall::GetPlayerXianlu()
{

    UCHAR result = UCHAR_MAX;
    DWORD playerdata = GetPlayerDataAddr();
    __try
    {
        __asm
        {
            mov eax, playerdata;
            mov eax, [eax + player_xianlu_offset3];

            mov result, al;
        }
    }
    __except(1)
    {
        TRACE(FUNCNAME);
    }

    return result;

}


//打开商品对话框
//参数1: npc名字
//返回值: ItemStorePanel ui地址
BOOL Gamecall::OpenShangDian(wchar_t* name, DWORD* pUiAddr)
{

    //先判断打开没有
    BOOL bOpen = FALSE;

    GetUIAddrByName(L"TalkControlPanel", pUiAddr);//old-ItemStorePanel
    if(*pUiAddr == 0)
        return FALSE;


    //等待四秒判断商店是否已经打开
    for(DWORD i = 0; i < 4; i++)
    {

        //TRACE1("123:%d",*(DWORD *)(*pUiAddr + 0x38));
        if(*(DWORD*)(*pUiAddr + 0x38) == 2)
        {

            ObjectNode* pNode = GetObjectByName(name);
            if(pNode == NULL)
            {
                TRACE(_T("%s: 没有找到这个NPC"), name);
                return FALSE;
            }

            PARAM_GUANSHANGDIAN temp;
            temp.argv1 = pNode->id;
            temp.argv2 = pNode->id2;

            sendcall(id_msg_DaKaiDuiHuaKuang, &temp);
            Sleep(1000);

        }
        else
        {
            bOpen = TRUE;
            break;
        }

        Sleep(500);
    }


    return bOpen;
}




//关闭商店
void Gamecall::CloseShangDian()
{
    UIOperator uiop;
    ZeroMemory(&uiop, sizeof(UIOperator));

    GetUIAddrByName(L"TalkControlPanel", (DWORD*)&uiop.pAddr);
    if(uiop.pAddr)
    {
        uiop.c5 = *(DWORD*)((DWORD)uiop.pAddr + close_npc_c5);
        sendcall(id_msg_guanshangdian, &uiop);

        Sleep(2000);
    }
    else
        TRACE(_T("%s: 获取商店UI地址失败"), FUNCNAME);

    return;
}



void Gamecall::SellItem(_BAGSTU& bag, DWORD adress)
{

    int value = bag.m_Info;
    value <<= 16;
    value += package;

    int nums = bag.m_Num;
    //if(nums == 0)
    //  nums += 1;

    __try
    {
        _asm
        {
            mov eax, nums;
            push eax;
            push 0;
            mov eax, value;
            push eax;
            mov eax, adress;
            mov ebx, sell_call;
            call ebx;
        }

    }
    __except(1)
    {
        TRACE(_T("卖东西出错"));
    }
}


//点击某个ui
//参数1: 操作ui结构
BOOL Gamecall::ClickUI(UIOperator uiOp)
{

    DWORD* pAddr = uiOp.pAddr;
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

    __try
    {
        __asm
        {
            mov ecx, pAddr; //这个是控件的首地址
            mov edx, [ecx];
            mov eax, [edx + 0x4];

            lea ebx, kj;
            push ebx;

            /*mov eax,0x7BF600*/
            call eax
        }

        bRet = TRUE;
    }
    __except(1)
    {
        TRACE(FUNCNAME);
    }

    return bRet;
}

/*
取得攻击面板的地址
参数1: bar的二叉树起始节点地址
参数2, 传出 攻击栏 的地址
*/
void Gamecall::GetStrikeBarBaseAddr(Tree* pBaseAddr, DWORD* pStrikeBarBaseAddr)
{
    if(pBaseAddr->p2 == 1)
        return;

    __try
    {
        wchar_t* name = GetUIName(pBaseAddr->Adress);
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

//获取技能名字
//参数1: 技能id
//参数2: 未知
void Gamecall::GetStrikeName(DWORD ID, DWORD IDD, STRIKENAME* pName)
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
            mov edx, [edi + 0x18];   //TODO 固定
            mov ecx, [edi + 0x1C];  //TODO 固定
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
        TRACE(FUNCNAME);
    }
}



//取技能是否冷却  等于2 说明在冷却中 或者说明是一个持续技能在发招
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
        TRACE(FUNCNAME);
    }
    return value;
}

//取技能是否已经解锁  这个是0说明是没有解锁的技能  1 说明是已经解锁了
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
        TRACE(FUNCNAME);
    }
    return value;
}

//取技能是否可以使用 这个是0说明这个技能是可以使用的  2 说明这个技能虽然已经解锁 但是是灰名的
DWORD Gamecall::isStrikeCanUse(int index, DWORD pAddr)
{
    DWORD value = UINT_MAX;
    __try
    {
        if(pAddr != 0)
            value = ReadDWORD(pAddr + index * nums_strike_strcut_size + (nums_strike_canuse + 0x10));
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
        TRACE(FUNCNAME);
    }
    return value;
}

//根据攻击栏的地址取得技能数据的开始地址
DWORD Gamecall::GetStrikeStartAddr()
{
    DWORD StartAddr = 0;

    __try
    {
        DWORD StrikeStartAddr = 0;
        GetStrikeBarBaseAddr(GetUIBinTreeBaseAddr(), &StrikeStartAddr);

        //assert(StrikeStartAddr != 0);
		if (StrikeStartAddr == NULL)
		{
			return 0;
		}

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
        TRACE(FUNCNAME);
    }

    return StartAddr;
}

//取技能id1
//参数1: 技能的索引, 应该是游戏界面中的排列顺序
//参数2: 技能数据开始地址
//
DWORD Gamecall::GetStrikeId1(int index, DWORD pStrikeStartAddr)
{
    DWORD id = UINT_MAX;
    int temp = index * nums_strike_strcut_size;

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
        TRACE(FUNCNAME);
    }

    return id;
}

/*去技能id2
参数1: 技能的索引, 应该是游戏界面中的排列顺序
参数2: 技能数据开始地址
*/
DWORD Gamecall::GetStrikeId2(int index, DWORD pStrikeStartAddr)  //取技能ID2
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
        TRACE(FUNCNAME);
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

//获取背包身上装备仓库遍历Base
DWORD Gamecall::GetBagbodyInfoBase()
{
    DWORD addr = NULL;

    __try
    {
        __asm
        {
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
        TRACE(FUNCNAME);
    }
    return addr;
}

int Gamecall::GetGoodsYanSe(DWORD m_Adress)  //获取物品的颜色
{
    DWORD Adress = 0;
    __try
    {
        Adress = (DWORD)ReadByte(ReadDWORD(m_Adress + bag_item_color_offset1) + bag_item_color_offset2);
    }
    __except(1)
    {
        TRACE(_T("获取物品的等级错误"));
        return -1;
    }
    return Adress;
}


DWORD Gamecall::GetGoodsBiDui(DWORD m_Adress)  //获取物品的比对
{
    DWORD Adress = 0;
    __try
    {
        Adress = (DWORD)ReadByte(ReadDWORD(m_Adress + bag_item_bidui_offset1) + bag_item_bidui_offset2);
    }
    __except(1)
    {
        TRACE(_T("获取物品的比对错误"));
        return -1;
    }
    return Adress;
}

DWORD Gamecall::GetGoodsBiDui_A(DWORD m_Adress)  //获取物品的比对A
{
    DWORD Adress = 0;
    __try
    {
        Adress = (DWORD)ReadByte(ReadDWORD(m_Adress + bag_item_bidui1_offset1) + bag_item_bidui1_offset2);
    }
    __except(1)
    {
        TRACE(_T("获取物品的比对A错误"));
        return -1;
    }
    return Adress;
}


DWORD Gamecall::GetGoodsWuQiPingJi(DWORD m_Adress)  //获取武器的评级
{
    DWORD Adress = 0;
    __try
    {
        Adress = (DWORD)ReadByte(m_Adress + wuqi_pj_offset);
    }
    __except(1)
    {
        TRACE(_T("获取武器的评级错误"));
        return -1;
    }
    return Adress;
}


DWORD Gamecall::GetGoodsWuQiDangQianJingYan(DWORD m_Adress)  //获取武器当前的经验
{
    DWORD Adress = 0;
    __try
    {
        Adress = (DWORD)ReadWORD(m_Adress + wuqi_xp_cur_offset);
    }
    __except(1)
    {
        TRACE(_T("获取武器当前的经验错误"));
        return -1;
    }
    return Adress;
}

DWORD Gamecall::GetGoodsIsFengYin(DWORD m_Adress)  //获取物品是否封印
{
    DWORD Adress = 0;
    __try
    {
        Adress = (DWORD)ReadByte(ReadDWORD(m_Adress + 0x0C) + 0x0C);
    }
    __except(1)
    {
        TRACE(_T("获取物品是否封印错误"));
        return -1;
    }
    return Adress;
}


DWORD Gamecall::GetBaGuaGeZiShu(DWORD m_Adress)  //获取八卦格子数
{
    DWORD Adress = 0;
    __try
    {
        Adress = (DWORD)ReadByte(ReadDWORD(m_Adress + bag_item_bagua_pos_offset1) + bag_item_bagua_pos_offset2);
    }
    __except(1)
    {
        TRACE(_T("获取八卦格子数错误"));
        return -1;
    }
    return Adress;
}




//获取角色装备遍历Base
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
        TRACE(FUNCNAME);
    }

    return addr;
}


DWORD Gamecall::GetBagInfoBase(DWORD pBase)  //获取背包遍历Base
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
        TRACE(FUNCNAME);
    }

    return addr;
}


BOOL Gamecall::GetAllBaGuaToVector(std::vector<_BAGSTU>& BaGuaVec)
{
    std::vector<_BAGSTU> AllGoods;
    GetAllGoodsToVector(AllGoods);

    for(DWORD i = 0; i < AllGoods.size(); i++)
    {

        if(AllGoods[i].m_Info >= 8 &&
                AllGoods[i].m_Info <= 16)
            BaGuaVec.push_back(AllGoods[i]);
    }


    return TRUE;
}



BOOL Gamecall::GetSpecBaGuaToVector(wchar_t* name, std::vector<_BAGSTU>& BaGuaVec)
{
    std::vector<_BAGSTU> AllGoods;
    GetAllGoodsToVector(AllGoods);

    for(DWORD i = 0; i < AllGoods.size(); i++)
    {
        if(wcscmp(name, AllGoods[i].name) == 0)
            BaGuaVec.push_back(AllGoods[i]);
    }

    return TRUE;
}



DWORD Gamecall::GetBagGridNumberLast()
{
    std::vector<_BAGSTU> AllGoods;
    GetAllGoodsToVector(AllGoods);

    return (GetBagGridNumber() - AllGoods.size());
}


//当前背包的总的格子数
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
        TRACE(FUNCNAME);
    }

    return nums;
}

DWORD Gamecall::GetGoodsBase(DWORD pAddr, int index)  //获取物品的首地址
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
        TRACE(FUNCNAME);
    }

    return addr;
}

DWORD Gamecall::GetGoodsID(DWORD pAddr)  //获取物品的ID
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

DWORD Gamecall::GetGoodsNameID(DWORD pAddr)  //获取物品的名字ID
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
        TRACE(FUNCNAME);
    }

    return id;
}


//获取背包物品名字
wchar_t* Gamecall::GatBagGoodrName(DWORD ID)
{
    wchar_t* name = NULL;

    __try
    {
        __asm
        {
            mov eax, bag_item_name_call_base;
            mov eax, [eax];
            mov ecx, [eax + bag_item_name_call_offset1];
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
        TRACE(FUNCNAME);
    }

    return name;
}

DWORD Gamecall::GetGoodsType(DWORD pAddr)  //获取物品的类型
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
        TRACE(FUNCNAME);
    }

    return goodstype;
}


//获取物品的所在格子数
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
        TCHAR szBuf[MAX_PATH];
        wsprintf(szBuf, _T("%S: %d"), __FILE__, __LINE__);
        TRACE(szBuf);
    }
    return nums;
}


//获取物品的数量
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
        TRACE(FUNCNAME);
    }
    return nums;
}

DWORD Gamecall::GetGoodsLasting(DWORD pAddr)  //获取物品的持久
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
        TCHAR szBuf[MAX_PATH];
        wsprintf(szBuf, _T("%S: %d"), __FILE__, __LINE__);
        TRACE(szBuf);
        naijiu = UINT_MAX;
    }

    return naijiu;
}

DWORD Gamecall::GetGoodsLLV(DWORD pAddr)  //获取物品的等级
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
        TRACE(FUNCNAME);
        lv = UINT_MAX;
    }

    return lv;
}

DWORD Gamecall::GetCanshu_a(DWORD pAddr)  //吃药和穿装备需要的一个参数
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
        TRACE(FUNCNAME);
    }
    return Adress;
}

DWORD Gamecall::Getcanshu1(DWORD pAddr)  //参数1
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
        TRACE(FUNCNAME);
    }
    return Adress;
}

DWORD Gamecall::Getcanshu2(DWORD pAddr)  //参数2
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
        TRACE(FUNCNAME);
    }
    return Adress;
}

DWORD Gamecall::Getcanshu3(DWORD pAddr)  //参数3
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
        TRACE(FUNCNAME);
    }
    return Adress;
}

DWORD Gamecall::Getcanshu4(DWORD pAddr)  //参数4
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
        TRACE(FUNCNAME);
    }

    return Adress;
}


//计算距离
DWORD Gamecall::CalcC(fPosition& p1, fPosition& p2)
{
    //power of   平方
    //根据沟谷定理
    double x = abs((double)(p1.x - p2.x));
    double y = abs((double)(p1.y - p2.y));

    double x2 = pow(x, 2);
    double y2 = pow(y, 2);

    //求边长
    return (DWORD)sqrt(x2 + y2);
}


DWORD Gamecall::GetObjectSY(DWORD pObjAddress)  // 环境对象的索引1
{
    DWORD Adress = UINT_MAX;

    __try
    {
        if(!IsBadReadPtr((void*)pObjAddress, sizeof(DWORD)))
        {
            __asm
            {
                mov eax, pObjAddress;
                mov eax, [eax + obj_type4_name_offset1];
                mov eax, [eax + 0x1c];
                mov Adress, eax;
            }
        }
    }
    __except(1)
    {
        TRACE(FUNCNAME);
    }
    return Adress;
}


//对象是红名
//参数对象  objadress
DWORD Gamecall::m_Get11C(DWORD m_Adress)
{
    BYTE jd = 0;
    __try
    {
        if(!IsBadReadPtr((void*)m_Adress, sizeof(DWORD)))
        {
            _asm
            {
                mov eax, m_Adress;
                mov eax, [eax+obj_type4_youshan_offset1];
                mov eax, [eax+obj_type4_youshan_offset2];
                mov jd, al;
            }
        }
    }
    __except(1)
    {
    }


    return (DWORD)jd;
}


//ojb_type20_nameid_offset1
DWORD Gamecall::GetObjectSY12(DWORD pAddr)  // 环境对象的索引12
{
    DWORD Adress;
    __try
    {
        if(!IsBadReadPtr((void*)pAddr, sizeof(DWORD)))
        {
            _asm
            {
                mov eax, pAddr;
                mov eax, [eax + ojb_type20_nameid_offset1 ];
                mov eax, [eax + 0x1c];
                mov Adress, eax;
            }
        }
    }
    __except(1)
    {
        TRACE(FUNCNAME);
        Adress = UINT_MAX;
    }

    return Adress;
}


//获取任务开始地址
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
        TRACE(FUNCNAME);
        value = NULL;
    }

    return value;
}

//获得当前任务ID
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
        TRACE(_T("%s"), FUNCNAME);
    }

    return id;
}

//获得当前任务名字ID
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
        TRACE(_T("%s"), FUNCNAME);
    }

    return id;
}

//获得当前任务地址
DWORD Gamecall::GetTaskPresentAddr(int i, DWORD pAddr)
{
    DWORD value;
    __try
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
    __except(1)
    {
        TRACE(FUNCNAME);
        value = NULL;
    }
    return value;
}

//获得当前做到第几个小任务
DWORD Gamecall::GetPresentTaskIndexes(int i, DWORD pAddr)
{
    DWORD value;
    __try
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
    __except(1)
    {
        TRACE(FUNCNAME);
        value = UINT_MAX;
    }

    return value;
}

//获得当前小任务结束标志
DWORD Gamecall::GetPresentTaskEndFlag(int i, DWORD pAddr, DWORD info)
{
    DWORD value;
    __try
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
    __except(1)
    {
        TRACE(FUNCNAME);
        value = UINT_MAX;
    }
    return value;
}

//获得当前小任务已经打的怪数量
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
        TRACE(_T("%s"), FUNCNAME);
    }
    return value;
}

//获取当前已接任务名字
wchar_t* Gamecall::GatTaskName(DWORD ID)
{
    wchar_t* name = NULL;
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
        TRACE(_T("%s"), FUNCNAME);
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
            return QuestVec[i].step;
    }

    return UINT_MAX;
}



//打开任务物品
void Gamecall::OpenQuestItem(DWORD ID, DWORD ID2)
{
    __try
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
    __except(1)
    {
        TRACE(_T("%s"), FUNCNAME);
    }
}


void Gamecall::Pickup1(ObjectNode* pObj) //一次捡物
{

    int ID2 = pObj->id2;
    int ID = pObj->id;
    __try
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
            mov eax, [eax+pickup1_offset1];
            mov eax, [eax+pickup1_offset2];
            mov eax, [eax+pickup1_offset3];
            mov ecx, eax;
            push eax;

            mov eax, pickup1_call;
            call eax;



        }
    }
    __except(1)
    {
        TRACE(_T("一次捡物出错"));
    }

}


//二次捡物
void Gamecall::Pickup2(ObjectNode* pObj)
{

    TRACE2("id:%d,id2:%d", pObj->id, pObj->id2);
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
        TRACE(_T("%s"), FUNCNAME);
    }
}


//背包满了
BOOL Gamecall::isBagFull()
{
    //先判断背包有没有满
    std::vector<_BAGSTU> GoodsVec;
    GetAllGoodsToVector(GoodsVec);

    if(GoodsVec.size() == GetBagGridNumber())
        return TRUE;


    return FALSE;
}



//捡东西
BOOL Gamecall::Pickup(ObjectNode* pObj)
{

    DWORD i = 0;
    __try
    {
        int times = 0;

pickup_one:

        sendcall(id_msg_Pickup1, pObj);



        if(isPlayerHasPickupQuestItemUI())
            sendcall(id_msg_Pickup2, pObj);
        else
        {
            times++;
            if(times >= 3)
                return FALSE;
            goto pickup_one;
        }


        for(int i = 0; i < 6; i++)
        {
            Sleep(200);
            if(GetPlayerQuestUIStatus() != 2)
            {
                Sleep(200);
                break;
            }
            KeyPress(89);
        }


        return TRUE;
    }
    __except(1)
    {
        TRACE(_T("%s"), FUNCNAME);
    }


    return FALSE;
}

//判断对象是否为掉落
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

        TRACE(_T("%s"), FUNCNAME);

    }

    if(bRet1 == -1 &&
            bRet2 == -1 &&
            bRet3 == -1)
        return false;
    else
        return TRUE;


    return TRUE;
}

//转坐标2到坐标1
fPosition Gamecall::ShortPosToFloatPos(sPosition& spos)
{
    fPosition fpos;

    fpos.x = (float)(spos.x * 4);
    fpos.y = (float)(spos.y * 4);
    fpos.z = (float)(spos.z * 4);

    return fpos;
}


// 可以分解的东西
//
// 武器的类型是1
// 八卦的类型是4
// 首饰的类型是5
BOOL Gamecall::isCanFenjie(DWORD pAddr)
{

    DWORD type = GetGoodsType(pAddr);

    if(type == 1 ||
            type == 4 ||
            type == 5)
        return TRUE;

    return false;
}

//换线
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
        TRACE(_T("%s"), FUNCNAME);
    }
}



//交任务
void Gamecall::DeliverQuests(DWORD id, DWORD step, DWORD questtype, DWORD ff, DWORD npcid1, DWORD npcid2, DWORD unknow, DWORD mianban)
{
    TRACE(_T("id:%d,step:%d,questtype:%d,ff:%d,npcid1:%d,npcid2:%d,unknow:%d"), id, step, questtype, ff, npcid1, npcid2, unknow);
    //TRACE(_T("DeliverQuests执行"));
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
            push eax;
            mov ecx, 0x0;
            mov ecx, step;
            mov ebx, id;
            //mov edi, mianban;

            mov eax, deliver_quest_call;
            call eax;
        }
    }
    __except(1)
    {
        TRACE(_T("%s"), FUNCNAME);
    }
}

void Gamecall::KeyPress(WPARAM vk)
{
    if(CJLwgApp::m_hGameWnd != NULL)
    {
        PostMessage(CJLwgApp::m_hGameWnd, WM_KEYDOWN, vk, 0);
    }
    else
    {
        TRACE(_T("外挂没有获取游戏窗口句柄"));
    }
}


//穿装备的原始函数, 我会外边多写一层
//参数1: <<16 + pickage
//参数2: 装备的位置
void Gamecall::WearEquipment(_BAGSTU& bag)
{

    int value = bag.m_Info;
    value <<= 16;
    value += package;


    //TODO: 这个位置八卦使用 .BaguaGeziShu
    //普通物品用的是  m_Info

    int pos = 0;;
    if(8 <= bag.m_BaGuaGeZiShu &&
            bag.m_BaGuaGeZiShu <= 15)
        pos = bag.m_BaGuaGeZiShu;
    else
        pos = bag.m_ID;

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
        TRACE(_T("%s"), FUNCNAME);
    }
}


//解封装备 参数从左到右分别是
//需要解封装备的位置 ：80002
//解封符的ID ：C5C9E
//解封符数量
void Gamecall::JieFengZhuangBei(DWORD zhuangbei, DWORD jiefengfu_ID, DWORD num)
{
    __try
    {
        _asm
        {
            mov eax, num;
            push eax;
            push 1;
            mov eax, jiefengfu_ID;
            push eax;
            push 0;
            push 0;
            mov eax, zhuangbei;
            push eax;



            mov eax, obj_enum_base;
            mov eax, [eax];
            mov eax, [eax+jiefeng_offset1];
            mov eax, [eax+jiefeng_offset2];
            mov ecx, [eax+jiefeng_offset3];

            mov eax, jiefeng_call;
            call eax;
        }
    }
    __except(1)
    {
        TRACE(_T("解封装备出错"));
    }
}


//参数分别是 盒子位置:220002  0    1    0(这个会变)    钥匙ID    1     1(这个会变)
void Gamecall::JieFengZhuangBei(DWORD adress1, DWORD adress2, DWORD adress3, DWORD adress4, DWORD adress5, DWORD adress6, DWORD adress7) //解封盒子
{
    __try
    {
        _asm
        {

            mov eax, adress7;
            push eax;
            mov eax, adress6;
            push eax;
            mov eax, adress5;
            push eax;
            mov eax, adress4;
            push eax;
            mov eax, adress3;
            push eax;
            mov eax, adress2;
            push eax;
            mov eax, adress1;
            push eax;


            mov eax, obj_enum_base;
            mov eax, [eax];
            mov eax, [eax+jiefeng_hezi_offset1];
            mov eax, [eax+jiefeng_hezi_offset2];
            mov ecx, [eax+ jiefeng_hezi_offset3];
            push ecx;
            mov ecx, 0;
            mov eax, jiefeng_hezi_call;
            call eax;
        }
    }
    __except(1)
    {
        TRACE(_T("解封盒子出错"));
    }
}




//判断是否是尸体
BOOL Gamecall::isDeadBody(DWORD pAddr)
{
    DWORD type = GetObjectType(pAddr);
    if(type == 0xb0)
        return TRUE;

    return FALSE;
}


//ReadByte(ReadDWORD(ReadDWORD(ReadDWORD(Environmental_Adress) + 0x34) + 0x80) + 0x158);
//是否举起尸体了
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
        TRACE(_T("%s"), FUNCNAME);
    }

    return (result != 0);
}



void Gamecall::_PickupTask(ObjectNode* pObj)
{

    int id2 = pObj->id2;
    int id1 = pObj->id;

    TRACE(_T("%s: id: %d, id2: %d"), FUNCNAME, id1, id2);
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
        TRACE(_T("%s"), FUNCNAME);
    }
}


//取角色信息
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
        TRACE(_T("%s"), FUNCNAME);
    }
    return lpret;
}


//5 表示读条 1 刚进游戏 2 选择角色界面 3游戏内
//当前读条状态
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
        TRACE(_T("%s"), FUNCNAME);
    }

    return value;
}


//判断角色是否在打开任务物品的读条状态
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
        TRACE(_T("%s"), FUNCNAME);
    }

    //这里应该是弄反了
    //==5说明不再读条状态
    return (value == 5);
}


//
//wchar_t *NAME = L"AreaInfoPanel";
//  canshu2 = ReadDWORD(JIEGOU.adress+0x58);
void Gamecall::OpenXianluUI()
{
    DWORD uiAddr = 0;
    GetUIAddrByName(L"AreaInfoPanel", &uiAddr);
    assert(uiAddr != 0);

    UIOperator uiop;
    uiop.pAddr = (DWORD*)uiAddr;
    uiop.c5 = *(DWORD*)(uiAddr +  post_xianlu_c5);

    sendcall(id_msg_FaSonXianLuBao, (LPVOID)uiop.c5);

}

//发送线路包CALL
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
        TRACE(_T("%s"), FUNCNAME);
    }
}

//进入游戏
void Gamecall::LoginGame(int index)
{
    DWORD uiAddr = 0;
    int i = 0;


    BOOL bFind = FALSE;
    for(i = 0; i < 5; i++)
    {
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
        TRACE(_T("没能找到角色选择UI"));
        return;
    }


    BOOL bIn = FALSE;
    for(i = 0; i < 10; i++)
    {
        //判断角色选择界面
        if(isLoginInSelectPlayer())
        {
            bIn = TRUE;
            break;
        }

        Sleep(1000);
    }


    if(bIn == FALSE)
    {
        TRACE(_T("不再角色选择界面"));
        return;
    }



    for(;;)
    {
        if(isLoadingMap() == 2)
            break;


        Sleep(1000);
    }



    //不太可靠
    Sleep(1000);
    __try
    {
        __asm
        {
            mov eax, uiAddr;
            mov ebx, index;
            mov dword ptr ds:[eax+0x1A8], ebx;
            mov ecx, eax;
            mov edi, eax;
            mov eax, login_call;
            call eax;
        }

    }
    __except(1)
    {
        TRACE(_T("%s"), FUNCNAME);
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

        //==2就是可用, 可用可以断定为是任务物品
        if(value == 2)
            return TRUE;
    }
    __except(1)
    {
        TRACE(FUNCNAME);
    }

    return false;
}

//[[[player_base]+0x34]+0x78]+0x110] == （取一个字节）
//5     说明在开启任务物品状态
//2     表示那个拾取的ui弹出来了, 可以二次捡物品
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
        TRACE(_T("%s"), FUNCNAME);
    }

    return value;
}

//通过类型取得索引
DWORD Gamecall::GetIndexByType(DWORD pObjAddress)
{
    DWORD index = UINT_MAX;
    TCHAR type = GetObjectType(pObjAddress);
    __try
    {
        if(type == 0x4)
            index = GetObjectSY(pObjAddress);
        else if(type == 0x20)
            index = GetObjectSY12(pObjAddress);
        else if(type == 0x90)
            index = GetObjectSy_90(pObjAddress);

    }
    __except(1)
    {
        TRACE(FUNCNAME);
    }

    return index;
}


//npc == 0
//else  == 黄名
DWORD Gamecall::m_Get2E4(DWORD m_Adress)
{
    BYTE jd = 0;
    __try
    {
        if(!IsBadReadPtr((void*)m_Adress, sizeof(DWORD)))
        {
            _asm
            {
                mov eax, m_Adress;
                mov eax, [eax+obj_type4_youshan_offset4]; //1是怪物 0是NPC
                mov jd, al;
            }
        }
    }
    __except(1)
    {
        TRACE(FUNCNAME);
        return 0;
    }


    return (DWORD)jd;
}



DWORD Gamecall::m_Get110(DWORD m_Adress)  //对象的110
{
    BYTE jd = 0;
    __try
    {
        if(!IsBadReadPtr((void*)m_Adress, sizeof(DWORD)))
        {
            _asm
            {
                mov eax, m_Adress;
                mov eax, [eax+obj_type4_youshan_offset1];
                mov eax, [eax+obj_type4_youshan_offset3];
                mov jd, al;
            }
        }
    }
    __except(1)
    {

    }


    return (DWORD)jd;
}


//传送
//参数1: 城市id;
//判断是否传送后的读蓝条状态
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
            mov eax, [eax + dundi_chuning_status_offset4];
            mov bLoading, al;

        }


    }
    __except(1)
    {

        TRACE(FUNCNAME);
    }

    return (bLoading == 1);
}



//判断是否传送读条状态
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

        TRACE(_T("%d"), bLoading);
    }
    __except(1)
    {
        TRACE(FUNCNAME);
    }

    return (bLoading == 1);
}


void Gamecall::FenJie(_BAGSTU& bag)
{
    //TRACE(_T("格子数:%d"),bag.m_Info);
    int value = bag.m_Info;
    value <<= 16;
    value += package;

    //TRACE(_T("fenjie.value:%d"),value);
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

            mov ecx, 0x0FF;

            mov eax, fenjie_call;
            call eax;
        }

    }
    catch(...)
    {
        TRACE(FUNCNAME);
    }
}


//拓展背包
//读条 5秒
BOOL Gamecall::NewBag()
{
    DWORD addr = 0;
    DWORD addr1 = 0;


    GetUIAddrByName(L"Inventory2Panel", &addr);
    GetUIAddrByName(L"ExpandInvenSlotConfirmPanel", &addr1);

    BOOL result = FALSE;
    __try
    {

        __asm
        {
            mov edi, addr;  //EDI 就是 Inventory2Panel 的首地址
            lea ecx, [edi + bag_newslot_offset1];
            push 0;
            push 0;
            push ecx;
            push 0x2;
            push edi;
            mov eax, bag_newslot_call;
            call eax;

            mov edi, addr1;  //EDI= ExpandInvenSlotConfirmPanel首地址
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
        TRACE(FUNCNAME);
    }

    return result;
}

//吃药
void Gamecall::ChiYao(const wchar_t* name)
{
    std::vector<_BAGSTU> AllGoods;
    GetAllGoodsToVector(AllGoods);

    _BAGSTU goods;
    if(GetGoodsFromBagByName(name, &goods))
        sendcall(id_msg_ChiYao, &goods);
    else
        TRACE(_T("%s: 没有在背包中找到这个物品: %s"), FUNCNAME, name);

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


//复活状态判断
//[技能UI首地址 + 44]
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
        TRACE(FUNCNAME);

    }

    return (value == 6);

}




//确认进入游戏的协议
BOOL Gamecall::ConfirmAgreement()
{
    DWORD uiAddr = 0;
    BOOL bUiok = FALSE;
    BOOL bRet = FALSE;
    int i;
    //等待协议ui
    for(i = 0; i < 10; i++)
    {

        //先判断ui二叉树基址有没有数据
        if(GetUIBinTreeBaseAddr() != NULL)
        {
            GetUIAddrByName(L"ClausePanel", &uiAddr);
            if(uiAddr != 0)
            {
                //找到确认协议的ui了
                bUiok = TRUE;
                break;
            }

        }

        Sleep(1000);
    }


    if(bUiok == FALSE)
    {
        TRACE(_T("没有在设置的时间内找到登录协议的UI"));
        return FALSE;
    }

    BOOL uiValid = FALSE;

    //等待ui可用
    for(i = 0; i < 5; i++)
    {
        if(*(BYTE*)(uiAddr + 0x38) == 1)
        {
            uiValid = TRUE;
            break;
        }

        Sleep(1000);
    }

    if(uiValid == FALSE)
    {
        TRACE(_T("登录协议UI不可用"));
        return FALSE;
    }


    //协议ui可用后立即点ui会导致进入的角色ui错乱.
    //可能那个ui需要其他初始化信息, 所以这里再加个Sleep
    //不太可靠
    Sleep(2000);
    __try
    {
        UIOperator uiop;
        ZeroMemory(&uiop, sizeof(UIOperator));

        uiop.pAddr = (DWORD*)uiAddr;
        uiop.c5 = *(DWORD*)(uiAddr + 0x48);

        sendcall(id_msg_clickui, &uiop);

        bRet = TRUE;
    }
    __except(1)
    {
        TRACE(_T("点击协议UI时异常"));
    }


    return bRet;

}



//关闭进入游戏后的摇奖ui
BOOL Gamecall::CloseAttendance()
{

    UIOperator uiOp;
    ZeroMemory(&uiOp, sizeof(UIOperator));
    DWORD UIAddr = 0;
    int i;
    BOOL buiFined = FALSE;
    //等待ui产生
    for(i = 0; i < 5; i++)
    {
        GetUIAddrByName(L"AttendancePanel", &UIAddr);
        if(UIAddr != NULL)
        {
            buiFined = TRUE;
            break;
        }


        Sleep(1000);
    }


    if(buiFined == FALSE)
    {
        TRACE(_T("没有设置的时间内等待到UI产生"));
        return FALSE;
    }


    BOOL buiOpen = FALSE;
    //等待ui可用
    for(i = 0; i < 10; i++)
    {
        //两秒判断一次
        if(*(BYTE*)(UIAddr + 0x38) == 1)
        {
            buiOpen = TRUE;
            break;
        }

        Sleep(2000);
    }

    if(buiOpen == FALSE)
    {
        TRACE(_T("没有在设置的时间内等待到摇奖UI显示"));
        return FALSE;
    }


    __try
    {

        uiOp.pAddr = (DWORD*)UIAddr;
        uiOp.c5 = *(DWORD*)(UIAddr + 0x1CBD8);
        sendcall(id_msg_clickui, &uiOp);


        UIAddr = 0;
        //直到确认的ui弹出来再继续
        for(int i = 0; i < 3; i++)
        {
            GetUIAddrByName(L"WindowConfirmPanel_Main", &UIAddr);

            if(UIAddr != 0)
            {
                int IsShow = *(DWORD*)(UIAddr + 0x4c);
                if(IsShow != 0)
                {
                    //弹出来了
                    uiOp.pAddr = (DWORD*)UIAddr;
                    uiOp.c5 = *(DWORD*)(UIAddr + 0x1c8);

                    sendcall(id_msg_clickui, &uiOp);
                    return TRUE;
                }
            }

            Sleep(1000);
        }
    }
    __except(1)
    {
        TRACE(FUNCNAME);
    }

    return false;
}


//设置当前鼠标操作模式
//默认经典模式. 当前已经是经典就不切换了
void Gamecall::SetMouseMode()
{
    //"OptionPanel" 这个名字的控件
    //  1:进入游戏后判断是经典模式还是键盘模式[["OptionPanel" 首地址 + 0x36D1C] + 0x1C]  等于 1  是经典模式  等于0是键盘模式
    //  2 : [0xFE3280] 等于 1  是经典模式  等于0是键盘模式
    //  二种方法判断经典模式的状态都可以
    //  参数5是 控件的首地址 + 0x36F28

    //判断当前模式
    //UCHAR isClass = *(UCHAR *)0xfe3280;
    //if(isClass == 0)
    //{
    DWORD addr = 0;
    GetUIAddrByName(L"OptionPanel", &addr);
    assert(addr != 0);

    UIOperator uiop;
    uiop.c5 = *(DWORD*)(addr + mouse_mode_class_c5);
    uiop.pAddr = (DWORD*)addr;

    sendcall(id_msg_JingDianMoShi, &uiop);
}

//等待进入游戏
bool Gamecall::WaitPlans(int inMaxTime)
{

    for(int i = 0; i < inMaxTime; i++)
    {
        if(isLoadingMap() == 3) 
        {
            
            return true;
        }

        Sleep(1000);
    }

    return false;
}


//
//[[[[0x0FAC688]+34]+80]+1B4] 一字节
//0表示活着  1和2都表示死亡   2表示死亡了还能在原地复活
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
        //TRACE(_T("死亡状态:%d"),value);
    }
    __except(1)
    {
        TRACE(FUNCNAME);

    }

    return value;
}


//加血
//参数1:这是个百分比, 比如传 50, 表示血值一半时
//优先吃对应等级的药, 没有的话吃低等级药, 还是没有吃不限等级, 还是没有退
//返回值1 = 吃药  2 = 参数不正确 3 = 无药可吃 4 = CD中 5 = 报错
int Gamecall::GetHealth(DWORD theValue)
{
    if(theValue > 100 || theValue <= 0)
    {
        TRACE(_T("参数不正确"));
        return 2;
    }


    try
    {
        DWORD MaxHealth = GetPlayerMaxHealth();
        DWORD Health = GetPlayerHealth();
        DWORD percent = Health * 100 / MaxHealth;
        int leave = GetPlayerLevel();

        const wchar_t* itemName = NULL;


        //两个特殊药的标志
        BOOL test_1 = FALSE;
        BOOL test_2 = FALSE;


        //可以吃药了
MoreTimes:
        if(percent < theValue)
        {

            if(test_1 == FALSE)
            {
                itemName = nSpec1;
                goto letsDrike;
            }

            if(test_2 == FALSE)
            {
                itemName = nSpec2;
                goto letsDrike;
            }

            if(leave >= 50)
            {
                itemName = nBig50;
            }
            else if(leave >= 45)
            {
                itemName = nBig45;
            }
            else if(leave >= 36)
            {
                itemName = nBig36;
            }
            else if(leave >= 29)
            {
                itemName = nBig29;
            }
            else if(leave >= 10)
            {
                itemName = nBig10;
            }
            else if(leave < 10 && leave >= 0)
            {
                itemName = nLess10;
            }
            else
            {
                TRACE(_T("没有找到所有能喝的药"));
                return 3;
            }

letsDrike:
            _BAGSTU goods;
            if(GetGoodsFromBagByName(itemName, &goods))
            {
                //喝
                if(sendcall(id_msg_isYaoPingCD, &goods) == 1)
                {
                    sendcall(id_msg_ChiYao, &goods);
                    return 1;
                }
                else
                    return 4;


            }
            else
            {
                if(test_1 == FALSE)
                {
                    test_1 = TRUE;
                    goto MoreTimes;
                }

                if(test_1 == FALSE)
                {
                    test_2 = TRUE;
                    goto MoreTimes;
                }

                //没有找到这个物品
                leave -= 5;
                goto MoreTimes;
            }
        }
    }
    catch(...)
    {
        TRACE(FUNCNAME);
    }
    return 5;
}



//玩家等级
UCHAR Gamecall::GetPlayerLevel() //获得角色等级
{
    UCHAR LV = 0;
    DWORD PlayerInfo = GetPlayerDataAddr();
    __try
    {
        __asm
        {
            mov eax, PlayerInfo;
            mov eax, [eax + player_cur_level];
            mov LV, al;
        }
    }
    __except(1)
    {
        TRACE(FUNCNAME);
    }

    return LV;
}


//取得对象名字
wchar_t* Gamecall::GetObjectName(DWORD pObjAddress)
{
    return GetObjectNameByIndex(GetIndexByType(pObjAddress));
}



// Return whether first element is greater than the second
BOOL Gamecall::UDgreater(ObjectNode* elem1, ObjectNode* elem2)
{
    Gamecall* pCall = Gamecall::GetInstance();
    fPosition fpos1;
    fPosition fpos2;

    double dis1 = 0;
    double dis2 = 0;
    if(pCall->GetObjectPos(elem1, &fpos1) && pCall->GetObjectPos(elem2, &fpos2))
    {
        fPosition mypos;
        pCall->GetPlayerPos(&mypos);

        dis1 = pCall->CalcC(mypos, fpos1);
        dis2 = pCall->CalcC(mypos, fpos2);
    }

    return dis1 < dis2;
}



//参数是物品的首地址, 参数是背包遍历出来的对象地址
void Gamecall::ChiYao(_BAGSTU& goods)  //吃药
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
        TRACE(FUNCNAME);
    }
}



void Gamecall::PickupDeadbody(DWORD id1, DWORD id2)
{
    __try
    {
        __asm
        {
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
    __except(1)
    {
        TRACE(FUNCNAME);
    }
}

//[[[player_base]+0x34]+0x78]+0x110] == （取一个字节）
//5     说明在开启任务物品状态
//2     表示那个拾取的ui弹出来了, 可以二次捡物品
BOOL Gamecall::isPlayerHasPickupQuestItemUI()
{
    DWORD status = 0;

    for(int i = 0; i < 7; i++)
    {
        Sleep(200);
        status = GetPlayerQuestUIStatus();

        if(status == 2)
            return TRUE;
    }

    return FALSE;
}

//判断角色读条状态
BOOL Gamecall::isPlayerChanneling()
{
    DWORD status = 0;

    for(int i = 0; i < 7; i++)
    {
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

    __try
    {
        __asm
        {
            mov eax, playerdata;
            mov eax, [eax + 0x14];
            mov eax, [eax + player_steppos_x_offset2 + 0xc];
            mov value, eax;
        }
    }
    __except(1)
    {
        TRACE(FUNCNAME);
    }

    return (float)value;
}


//遍历周围所有的对象到容器
void Gamecall::GetAllObjectToVector(ObjectNode* pNote, std::vector<ObjectNode*>& RangeObject)
{
    __try
    {
        if(pNote->end == 1)
            return;

        //加到vector中
        RangeObject.push_back(pNote);
        GetAllObjectToVector(pNote->left, RangeObject);
        GetAllObjectToVector(pNote->right, RangeObject);
    }
    __except(1)
    {
        TRACE1("%s: 遍历异常", FUNCNAME);
    }
}

void Gamecall::GetRangeTaskItemToVectr(std::vector<ObjectNode*>& TastItemVector, DWORD range)
{
    //这个函数简写了,  直接从范围对象中遍历的过滤
    std::vector<ObjectNode*> RangeObject;
    GetRangeObjectToVector(GetObjectBinTreeBaseAddr(), range, RangeObject);

    fPosition fmypos;
    GetPlayerPos(&fmypos);
    for(DWORD i = 0; i < RangeObject.size(); i++)
    {
        ObjectNode* pNode = RangeObject[i];

        fPosition fpos;
        //过滤掉距离远的和没距离的
        if(GetObjectPos(RangeObject[i], &fpos) == FALSE) continue;

        if(fpos.x == 0 || fpos.y == 0 || fpos.z == 0) continue;

        DWORD dis = (DWORD)CalcC(fpos, fmypos);
        if(dis <= range)
        {
            //判断是否为任务物品
            if(isQuestItem(pNode->ObjAddress))
            {
                TastItemVector.push_back(pNode);
            }
        }
    }
}

//判断是否可以杀
BOOL Gamecall::isCanKill(ObjectNode* pNode)
{

    //再加一个类型是4的过滤
    if(GetObjectType(pNode->ObjAddress) != 0x4) return FALSE;

    //过滤
    BOOL bCanKill = FALSE;
    if(m_Get11C(pNode->ObjAddress) == 1)
    {
        bCanKill = TRUE;
    }
    else
    {
        if(m_Get110(pNode->ObjAddress) == 1)
        {
            if(m_Get2E4(pNode->ObjAddress) != 0)
                bCanKill = TRUE;
        }

    }

    return bCanKill;
}

//遍历距离范围内的所有怪物到容器中
//参数1: 范围, 单位: 游戏内的 米
void Gamecall::GetRangeMonsterToVector(DWORD range, std::vector<ObjectNode*>& MonsterVec)
{
    try
    {
        //这个函数简写了,  直接从范围对象中遍历的过滤
        std::vector<ObjectNode*> RangeObject;
        GetRangeObjectToVector(GetObjectBinTreeBaseAddr(), range, RangeObject);

        fPosition fmypos;
        GetPlayerPos(&fmypos);
        //TRACE1("RangeObject.size():%d",RangeObject.size());
        for(DWORD i = 0; i < RangeObject.size(); i++)
        {
            ObjectNode* pNode = RangeObject[i];
            //TRACE(_T("执行GetObjectName"));


            fPosition fpos;
            //过滤掉距离远的和没距离的
            //TRACE(_T("执行GetObjectPos"));
            if(GetObjectPos(RangeObject[i], &fpos) == FALSE)
                continue;

            if(fpos.x == 0 || fpos.y == 0 || fpos.z == 0)
                continue;

            if(CalcC(fpos, fmypos) > range)
                continue;
            wchar_t* objName = GetObjectName(pNode->ObjAddress);
            if(objName == NULL)
                continue;
            //TRACE(_T("执行isCanLook"));
            if(isCanLook(pNode->ObjAddress) == FALSE)
                continue;

            //上面几个过滤是强制的, 不管配置文件有没有
            //比如: 如果配置文件强制杀一个怪物, 但是这个怪物
            //是没有坐标的, 这肯定是无法杀的
            //TRACE(_T("push_back"));
            MonsterVec.push_back(pNode);
            //TRACE1("当前循环:%d",i);
        }
        //TRACE1("MonsterVec:%d",MonsterVec.size());
    }
    catch(...)
    {
        TRACE(FUNCNAME);
    }
}


void Gamecall::_GetRangeObjectToVector(ObjectNode* pNote, DWORD range, std::vector<ObjectNode*>& RangeObject)
{
    if(pNote->end == 1)
        return;

    try
    {
        //有坐标就比对坐标, 没有坐标就直接放进去
        fPosition fpos;
        if(GetObjectPos(pNote, &fpos))
        {
            fPosition fmypos;
            GetPlayerPos(&fmypos);
            if(fpos.x == 0 || fpos.y == 0 || fpos.z  == 0)
                RangeObject.push_back(pNote);
            else if((DWORD)CalcC(fmypos, fpos) <= range)
                RangeObject.push_back(pNote);
        }
        else
            RangeObject.push_back(pNote);


        GetRangeObjectToVector(pNote->left, range, RangeObject);
        GetRangeObjectToVector(pNote->right, range, RangeObject);
    }
    catch(...)
    {
        TRACE(FUNCNAME);
    }
}
//遍历距离范围内的所有对象到容器中
//参数1: 范围, 单位: 游戏内的 米
//这个函数现在会将没有坐标和坐标是0的都遍历进去
//保证都会遍历到, 更多的过滤在单独的函数里加
//比如遍历任务物品的那个过滤
void Gamecall::GetRangeObjectToVector(ObjectNode* pNode, DWORD range, std::vector<ObjectNode*>& RangeObject)
{
//     PARAM_GETUIADDRBYNAME temp;
//     temp.argv1 = (DWORD)pNode;
//     temp.argv2 = range;
//     temp.argv3 = (DWORD)&RangeObject;
//     sendcall(id_msg_GetRangeObjectToVector, &temp);
    _GetRangeObjectToVector(pNode, range, RangeObject);
}

//遍历距离范围内掉落的战利品对象到容器中
//参数1: 范围, 单位: 游戏内的 米
void Gamecall::GetRangeLootObjectToVector(DWORD range, std::vector<ObjectNode*>& LootVec)
{

    try
    {
        //这个函数简写了,  直接从范围对象中遍历的过滤
        std::vector<ObjectNode*> RangeObject;
        GetRangeObjectToVector(GetObjectBinTreeBaseAddr(), range, RangeObject);

        fPosition fmypos;
        GetPlayerPos(&fmypos);
        for(DWORD i = 0; i < RangeObject.size(); i++)
        {
            ObjectNode* pNode = RangeObject[i];

            
            //过滤掉距离远的和没距离的
            fPosition fpos;
            if(GetObjectPos(RangeObject[i], &fpos) == FALSE)
                continue;

            if(fpos.x == 0 || fpos.y == 0 || fpos.z == 0)
                continue;

            if(GetObjectType(pNode->ObjAddress) == 0xb0)
            {
                if(isLoots(pNode->ObjAddress))
                {
                    DWORD dis = (DWORD)CalcC(fpos, fmypos);
                    if(dis <= range)
                        LootVec.push_back(pNode);
                }
            }
        }
    }
    catch(...)
    {
        TRACE(FUNCNAME);
    }
}

void Gamecall::OverShunyi(BOOL bEnable) //过图
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


            mov edi, eax;

            mov eax, over_shunyi_call;
            call eax;
        }
    }
    __except(1)
    {
        TRACE(_T("过图出错"));
    }
    TRACE1("执行瞬移HOOK完毕,参数:%d", bEnable);
}


ObjectNode* Gamecall::GetObjectByName(wchar_t szName[], DWORD range)
{
    try
    {
        std::vector<ObjectNode*> RangeObject;
        if(range == 0)
            GetAllObjectToVector(GetObjectBinTreeBaseAddr(), RangeObject);
        else
            GetRangeObjectToVector(GetObjectBinTreeBaseAddr(), range, RangeObject);

        std::sort(RangeObject.begin(), RangeObject.end(), UDgreater);

        fPosition tarpos;
        for(DWORD i = 0; i < RangeObject.size(); i++)
        {

            //过滤掉没坐标的
            if(GetObjectPos(RangeObject[i], &tarpos) == FALSE)
                continue;

            //过滤掉坐标是0的
            if(tarpos.x == 0 || tarpos.y == 0 || tarpos.z == 0)
                continue;

            //过滤掉没名字的
            wchar_t* name = GetObjectName(RangeObject[i]->ObjAddress);
            if(name == NULL)
                continue;

            if(wcscmp(name, szName) == 0)
                return RangeObject[i];
        }
    }
    catch(...)
    {
        TRACE(FUNCNAME);
    }

    return NULL;
}

void Gamecall::_GetUItoVector(Tree* Base, std::vector<Tree*>& Allui)
{
    //这里我优化一下, 我看到数据遍历出来很多地址相同但是id不同的数据
    //因此滤掉那些地址相同的
    __try
    {
        if(Base->p2 == 1)
            return;

        //查找连续5个内重复的
        static DWORD ____old = 0;
        static DWORD ___old = 0;
        static DWORD __old = 0;
        static DWORD _old = 0;
        static DWORD old = 0;
        wchar_t* curName = GetUIName(Base->Adress);

        if(curName != NULL)
        {
            if(curName[0] == 0x20 || (curName[0] >= 0x41 && //过滤掉开头不是A~Z区间的
                                      curName[0] <= 0x7a))
            {
                if(Base->Adress != old &&
                        Base->Adress != _old &&
                        Base->Adress != __old &&
                        Base->Adress != ___old &&
                        Base->Adress != ____old
                  )
                {

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
        TRACE(FUNCNAME);
    }

}

//取得所有ui对象到容器
void Gamecall::GetUItoVector(Tree* Base, std::vector<Tree*>& Allui)
{
    PARAM_GUANSHANGDIAN temp;
    temp.argv1 = (DWORD)Base;
    temp.argv2 = (DWORD)&Allui;
    sendcall(id_msg_GetUItoVector, &temp);
}



//通过名称取得这个ui的地址
//取得攻击面板的地址
//参数1: bar的二叉树起始节点地址
//参数2: 查找的UI名, 根据比对名返回UI的数据地址
//参数3, 传出ui的数据地址
void Gamecall::GetUIAddrByName(wchar_t* name, DWORD* pUIAddr)
{
    assert(name != NULL);

    std::vector<Tree*> AllUI;
    GetUItoVector(GetUIBinTreeBaseAddr(), AllUI);
    for(int i = 0; i < AllUI.size(); i++)
    {
        wchar_t* uiname = GetUIName(AllUI[i]->Adress);
        if(uiname != NULL)
        {
            if(_wcsicmp(name, uiname) == 0)
            {
                *pUIAddr = AllUI[i]->Adress;
                return;
            }
        }
    }



}


//获取物品的背包类型
DWORD Gamecall::GetGoodsBagInfo(DWORD m_Adress)
{
    DWORD Adress = 0;
    __try
    {
        Adress = (DWORD)ReadByte(m_Adress + item_bag_type_offset);
    }
    __except(1)
    {
        TRACE(_T("获取物品的背包类型错误"));
        return -1;
    }
    return Adress;
}

// 获取当前武器经验总值
DWORD Gamecall::GetMuQianJingYanZongZhi(DWORD Adress)
{
    DWORD JingYan;
    __try
    {
        _asm
        {

            mov eax, Adress;
            mov eax, [eax+wuqi_xp_all1_offset1];
            mov eax, [eax+wuqi_xp_all1_offset2];
            add eax, 1;
            push eax;

            mov esi, Adress;
            mov eax, [esi+wuqi_xp_all1_offset3];
            mov eax, [eax+wuqi_xp_all1_offset4];
            push eax;

            mov eax, obj_name_call_base;
            mov edx, [eax];
            mov ecx, [edx+wuqi_xp_all1_offset5];
            mov edx, [ecx];
            mov eax, [edx+wuqi_xp_all1_offset6];
            call eax;
            mov eax, [eax+0x10];
            mov JingYan, eax;
        }
    }
    __except(1)
    {
        TRACE(_T("获取当前武器经验总值出错"));
        return 0;
    }

    JingYan = JingYan - 1;
    return JingYan;
}

// 获取当前武器经验总值A
DWORD Gamecall::GetMuQianJingYanZongZhi_A(DWORD Adress)
{
    DWORD JingYan;
    __try
    {
        _asm
        {

            mov eax, Adress;
            mov eax, [eax+ wuqi_xp_all2_offset1];
            mov eax, [eax+ wuqi_xp_all2_offset2];
            sub eax, 1;
            push eax;

            mov esi, Adress;
            mov eax, [esi+ wuqi_xp_all2_offset3];
            mov eax, [eax+ wuqi_xp_all2_offset4];
            push eax;

            mov eax, obj_name_call_base;
            mov edx, [eax];
            mov ecx, [edx+ wuqi_xp_all2_offset5];
            mov edx, [ecx];
            mov eax, [edx+ wuqi_xp_all2_offset6];
            call eax;
            mov eax, [eax+ 0x24];
            mov JingYan, eax;
        }
    }
    __except(1)
    {
        TRACE(_T("获取当前武器经验总值A出错"));
        return 0;
    }

    return JingYan;
}


// 获取背包物品右键操作类型
DWORD Gamecall::GetBagYouJianCaoZuoType(DWORD Adress, DWORD argv2)
{

    YouJianLeiXing LeiXing;
    LeiXing.canshu1 = Adress;
    LeiXing.canshu2 = 0;
    LeiXing.canshu3 = 0;
    LeiXing.canshu4 = 0;
    DWORD BBB;
    __try
    {
        _asm
        {
            push 0;
            lea eax, LeiXing;
            push eax;
            push 0;
            mov eax, Adress;
            push eax;
            mov eax, argv2;
            mov ebx, rbt_type_call;
            call ebx;
            add esp, 0x8;
            mov BBB, eax;

        }
    }
    __except(1)
    {
        TRACE(_T("获取背包物品右键操作类型"));
    }
    return BBB;
}


//获取背包物品右键操作类型
DWORD Gamecall::GetGoodsYouJianType(DWORD m_BagLeiXing, DWORD m_Info)
{
    DWORD m_Adress = 0;
    DWORD UIaddr = 0;

    __try
    {
        GetUIAddrByName(L"Inventory2Panel", &UIaddr);
        int value = m_Info;
        value <<= 16;
        value += m_BagLeiXing;

        if(UIaddr)
            m_Adress = GetBagYouJianCaoZuoType(value, UIaddr);
    }
    __except(1)
    {
        TRACE(FUNCNAME);
    }
    return m_Adress;
}

//开盒子 参数是盒子在背包中的格子数
void Gamecall::KaiHeZi(_BAGSTU& bag)
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
            mov ebx, value;
            push ebx;
            mov eax, obj_enum_base;
            mov eax, [eax];
            mov eax, [eax+kaihezi_offset1];
            mov eax, [eax+kaihezi_offset2];
            mov eax, [eax+kaihezi_offset3];
            push eax;
            mov ecx, 0xFF;
            mov eax, kaihezi_call;
            call eax;

        }
    }
    __except(1)
    {
        TRACE(_T("开盒子出错"));
    }
}



BOOL Gamecall::FillGoods(_BAGSTU& BagBuff)
{

    BagBuff.m_ID      =   GetGoodsID(BagBuff.m_Base);                //获取物品的ID
    if(BagBuff.m_ID == UINT_MAX)
        return FALSE;

    BagBuff.m_NameID  =   GetGoodsNameID(BagBuff.m_Base);            //获取物品的名字ID


    //BagBuff.name   =	  (wchar_t *)sendcall(id_msg_GatBagGoodrName, (LPVOID)BagBuff.m_NameID);
    BagBuff.name   =	  GatBagGoodrName(BagBuff.m_NameID);
    if(BagBuff.name == NULL)
        return FALSE;

    BagBuff.m_Type    =   GetGoodsType(BagBuff.m_Base);              //获取物品的类型
    BagBuff.m_Info    =   GetGoodsInfo(BagBuff.m_Base);              //获取物品的所在格子数
    BagBuff.m_Num	  =   GetGoodsNum(BagBuff.m_Base);               //获取物品的数量
    BagBuff.m_Lasting =	  GetGoodsLasting(BagBuff.m_Base);           //获取物品的持久
    BagBuff.m_LV      =   GetGoodsLLV(BagBuff.m_Base);               //获取物品的等级
    //BagBuff.m_Site	  =   GetCanshu_a(BagBuff.m_Base);               //吃药和穿装备需要的一个参数



    BagBuff.canshu1 = Getcanshu1(BagBuff.m_Base);  //参数1
    BagBuff.canshu2 = Getcanshu2(BagBuff.m_Base);  //参数2
    BagBuff.canshu3 = Getcanshu3(BagBuff.m_Base);  //参数3
    BagBuff.canshu4 = Getcanshu4(BagBuff.m_Base);  //参数4

    BagBuff.m_BagLeiXing = GetGoodsBagInfo(BagBuff.m_Base);  //获取物品的背包类型





    BagBuff.m_CaoZuoType  = GetGoodsYouJianType(BagBuff.m_BagLeiXing, BagBuff.m_Info); //获取背包物品右键操作类型


    BagBuff.m_YanSe      =   GetGoodsYanSe(BagBuff.m_Base);  //获取物品的颜色
    BagBuff.m_IsFengYin  =   0;//GetGoodsIsFengYin(BagBuff.m_Base);  //获取物品是否封印
    if(BagBuff.m_YanSe == 5)
    {
        //TRACE("此物品是紫色   %X",BagBuff.m_CaoZuoType);
    }
    if(BagBuff.m_YanSe == 4)
    {
        //TRACE("此物品是蓝色   %X",BagBuff.m_CaoZuoType);
    }
    if(BagBuff.m_YanSe == 3)
    {
        //TRACE("此物品是绿色   %X",BagBuff.m_CaoZuoType);
    }
    if(BagBuff.m_YanSe == 2)
    {
        //TRACE("此物品是白色   %X",BagBuff.m_CaoZuoType);
    }
    if(BagBuff.m_CaoZuoType == 0x0E)
    {
        //TRACE("此物品是未解封的装备  总各数 %X,首地址 %X 物品右键操作类型  %X",GridNum,BagBuff.m_Base,BagBuff.m_CaoZuoType);
    }
    else if(BagBuff.m_CaoZuoType == 0x0F)
    {
        //TRACE("此物品是未解封的盒子  总各数 %X,首地址 %X 物品右键操作类型  %X",GridNum,BagBuff.m_Base,BagBuff.m_CaoZuoType);
    }
    else
    {
        //TRACE("总各数 %X,首地址 %X 物品右键操作类型  %X",GridNum,BagBuff.m_Base,BagBuff.m_CaoZuoType);
    }



    if(BagBuff.m_Type == 1 || BagBuff.m_Type == 5)
    {
        if(BagBuff.m_YanSe == 4 || BagBuff.m_YanSe == 5)
        {
            BagBuff.m_BiDui1 =  GetGoodsBiDui(BagBuff.m_Base);  //获取物品的比对
            BagBuff.m_BiDui2 =  GetGoodsBiDui_A(BagBuff.m_Base);  //获取物品的比对1
            if(BagBuff.m_BiDui1 < BagBuff.m_BiDui2)
            {
                BagBuff.m_DangQianJingYanZongZhi = GetMuQianJingYanZongZhi(BagBuff.m_Base); // 获取当前武器经验总值
            }
            if(BagBuff.m_BiDui1 >= BagBuff.m_BiDui2)
            {
                BagBuff.m_DangQianJingYanZongZhi = GetMuQianJingYanZongZhi_A(BagBuff.m_Base); // 获取当前武器经验总值
            }

            BagBuff.m_DangQianJingYanZhi  = GetGoodsWuQiDangQianJingYan(BagBuff.m_Base);  //获取武器当前的经验
            BagBuff.m_PingJi = GetGoodsWuQiPingJi(BagBuff.m_Base);  //获取武器的评级

        }
    }


    if(BagBuff.m_Type == 4)
    {
        BagBuff.m_BaGuaGeZiShu = GetBaGuaGeZiShu(BagBuff.m_Base);  //获取八卦格子数
    }


    return TRUE;
}

void Gamecall::_GetAllGoodsToVector(std::vector<_BAGSTU>& RangeObject)
{
    DWORD BagbodyAdress = 0;
    DWORD BagAdress = 0;
    int GridNum = 0;
    _BAGSTU aGoods;

    BagbodyAdress = GetBagbodyInfoBase();                                 //获取背包身上装备仓库遍历Base
    BagAdress = GetBagInfoBase(BagbodyAdress);                        //获取背包遍历Base
    GridNum = GetBagGridNumber();                        //当前背包的总的格子数

	//TRACE1("背包格子总数:%d",GridNum);
    //先整理一下背包
    for(int i = 0; i < GridNum; i++)
    {
        ZeroMemory(&aGoods, sizeof(aGoods));
        __try
        {
            aGoods.m_Base = GetGoodsBase(BagAdress, i);                 //获取物品的首地址
            if(aGoods.m_Base != 0)
            {
                if(FillGoods(aGoods))
                {
                    //游戏里本来是0
                    if(aGoods.m_Num == 0)
                        aGoods.m_Num = 1;
                    RangeObject.push_back(aGoods);
                }
            }
            //Sleep(10);
        }
        __except(1)
        {
            TRACE(FUNCNAME);
        }
    }
}


//遍历背包数据到容器
void Gamecall::GetAllGoodsToVector(std::vector<_BAGSTU>& RangeObject)
{
    sendcall(id_msg_GetAllGoodsToVector, &RangeObject);
}


void Gamecall::_GetAllBodyEquipToVector(std::vector<_BAGSTU>& RangeObject)
{
    DWORD BagbodyAdress = 0;
    DWORD BagAdress = 0;
	int Gridnum = 0;
    _BAGSTU aGoods;

    BagbodyAdress = GetBagbodyInfoBase();
    BagAdress = GetBodyInfoBase(BagbodyAdress);
	Gridnum = 0x10;//GetBagGridNumber();
    //当前背包的总的格子数
    for(int i = 0; i < Gridnum; i++)
    {
        ZeroMemory(&aGoods, sizeof(_BAGSTU));
        __try
        {
            aGoods.m_Base = GetGoodsBase(BagAdress, i);

            if(aGoods.m_Base != 0)
            {
				//TRACE1("base:%x",)
                if(FillGoods(aGoods))
                    RangeObject.push_back(aGoods);
            }
        }
        __except(1)
        {
            TRACE(FUNCNAME);
        }
    }
}

//遍历装备数据到容器
void Gamecall::GetAllBodyEquipToVector(std::vector<_BAGSTU>& RangeObject)
{
    sendcall(id_msg_GetAllBodyEquipToVector, &RangeObject);
}

//通过名字取id
BOOL Gamecall::GetStrikeByName(const wchar_t* name, STRIKEINFO* pStrikeInfo)
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
        TRACE(FUNCNAME);
    }

    TRACE(_T("%s: 没有找到对应技能"), FUNCNAME);
    return FALSE;
}

void Gamecall::GetStrikeToVector(std::vector<STRIKEINFO>& RangeObject)
{
    int count = 9;
    int count2 = 6;
    int index;


    DWORD pStrikeStart = GetStrikeStartAddr();

	if (pStrikeStart == NULL)
	{
		TRACE(_T("未查到技能基址"));
		return;
	}

    DWORD adress = GetRJianSkill(pStrikeStart);

    STRIKEINFO strike;


    for(index = 0; index < count; index++)
    {
        ZeroMemory(&strike, sizeof(STRIKEINFO));
        __try
        {
            strike.id1 = GetStrikeId1(index, pStrikeStart);
            if(strike.id1 != 0)
            {
                strike.id2 = GetStrikeId2(index, pStrikeStart);
                GetStrikeName(strike.id1, strike.id2, &strike.stName);
                strike.cd = GetStrikeCD(index, pStrikeStart);
                strike.canUse = isStrikeCanUse(index, pStrikeStart);
                strike.isBlock = isStrikeLocked(index, pStrikeStart);
                RangeObject.push_back(strike);
            }
            else
                continue;
        }
        __except(1)
        {
            TRACE(FUNCNAME);
        }
    }

    for(index = 0; index < count2; index++)
    {
        ZeroMemory(&strike, sizeof(STRIKEINFO));
        __try
        {
            strike.id1 = GetRJSkillIDDD(index, adress);
            if(strike.id1 != 0)
            {
                strike.id2 = GetRJSkillIDDD2(index, adress);
                GetStrikeName(strike.id1, strike.id2, &strike.stName);
                strike.cd = GetRJSkillCD(index, adress);
                strike.canUse = GetRJSkillISShiYong(index, adress);
                strike.isBlock = GetRJSkillIsJieSuo(index, adress);
                RangeObject.push_back(strike);
            }
            else
                continue;
        }
        __except(1)
        {
            TRACE(FUNCNAME);
        }
    }
}

//取R键技能是否冷却  等于1 说明在冷却中 或者说明是一个持续技能在发招
DWORD Gamecall::GetRJSkillCD(int i, DWORD m_adress)
{
    DWORD Adress = UINT_MAX;
    int temp = i * letter_strike_id + (letter_strike_cd - 0x10) + m_adress;

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
        TRACE(FUNCNAME);
    }
    return Adress;
}

//取R键技能是否已经解锁
//0 说明是没有解锁的技能
//1 说明是已经解锁了
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
        TRACE(FUNCNAME);
    }
    return Adress;
}

//取R键技能是否可以使用 这个是0说明这个技能是可以使用的  2 说明这个技能虽然已经解锁 但是是灰名的
DWORD Gamecall::GetRJSkillISShiYong(int i, DWORD m_adress)
{
    DWORD Adress = UINT_MAX;
    int temp = i * letter_strike_id + (letter_strike_canuse - 0x10) + m_adress;

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
        TRACE(FUNCNAME);
    }
    return Adress;
}

DWORD Gamecall::GetRJSkillIDDD2(int i, DWORD m_adress)  //取R键技能数组ID2
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
        TRACE(FUNCNAME);
    }
    return Adress;
}

//取技能R键攻击的数组开始地址
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
        TRACE(FUNCNAME);
    }
    return Adress;
}

//取R键数组技能ID
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
        TRACE(FUNCNAME);
    }
    return Adress;
}

//判断是否进入角色选择界面
BOOL Gamecall::isLoginInSelectPlayer()
{
    DWORD dwUIAddr = 0;
    DWORD value = UINT_MAX;
    __try
    {
        GetUIAddrByName(L"SelectCharacterPanel", &dwUIAddr);
        __asm
        {
            mov eax, dwUIAddr;
            mov eax, [eax + select_character_offset];
            mov value, eax;
        }

    }
    __except(1)
    {
        TRACE(FUNCNAME);
    }

    return (value != 0xff);
}


//卸宝石
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
        TRACE(FUNCNAME);
    }
}


//加宝石
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
        TRACE(FUNCNAME);
    }
}


DWORD Gamecall::sendcall(DWORD id, LPVOID pParam)
{
    return SendMessage(CJLwgApp::m_hGameWnd, WM_CUSTOM_GCALL, id, (LPARAM)pParam);
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
        TRACE(FUNCNAME);
    }
}

//打开对话框, 参数 npcid, npcid2
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
        TRACE(FUNCNAME);
    }
}


//购买
//参数1: 数量
//参数2: 索引
//参数3: 地址 ItemStorePanel ui
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
        TRACE(FUNCNAME);
    }
}


//药品CD_CALL
// 1 == 没有cd
// 0 == cd中
DWORD Gamecall::isYaoPingCD(_BAGSTU& goods)
{
    BYTE m_Adress = 0;
    YaoPingCD_JG CD;

    int value = goods.m_Info;
    value <<= 16;
    value += package;

    int adress = goods.m_Base;


    __try
    {
        _asm
        {
            mov ecx, yao_cd_base;
            mov ecx, [ecx];
            mov ecx, [ecx+ yao_cd_offset1];
            mov edx, [ecx];
            mov edx, [edx+yao_cd_offset2];

            mov eax, adress;
            mov eax, [eax+yao_cd_offset3];
            mov ebx, [eax+yao_cd_offset4];
            push ebx;
            mov ebx, [eax+ yao_cd_offset5];
            push ebx;
            call edx;
            mov CD.canshu1, eax;
            mov CD.canshu2, -1;

            mov eax, obj_enum_base;
            mov eax, [eax];
            mov eax, [eax+ yao_cd_offset6];
            mov eax, [eax+yao_cd_offset7];
            mov eax, [eax+yao_cd_offset8];
            mov CD.canshu3, eax;

            lea eax, CD;
            push eax;
            push 0;
            mov ecx, value;
            push ecx;

            mov eax, obj_enum_base;
            mov eax, [eax];
            mov eax, [eax+yao_cd_offset9];
            mov ebx, [eax+yao_cd_offset10];

            mov esi, ebx;
            mov eax, yao_cd_call ;
            call eax;


            mov m_Adress, al;
        }
    }
    __except(1)
    {
        TRACE(_T("药品CD_CALL出错"));
        return -1;
    }

    return (DWORD)m_Adress;
}




//转向
void Gamecall::TurnTo(fPosition& pos)
{
    fPosition mypos;
    GetPlayerPos(&mypos);

	//重叠的情况
	if(mypos.x == pos.x &&
		mypos.y == pos.y)
	{
		TRACE(_T("转视角时, 目标和我是重叠的"));
		//这里不解决重叠， 重叠让走路解决
		//RandomStep(60);
		//直接退
		return;
	}


    
    double value1;
    double value2;

    value1 = mypos.y - pos.y;
    value2 = mypos.x - pos.x;

    double angle = atan2(abs(value1), abs(value2)) * 180 / M_PI;

    //算成游戏内角度
    double gameangle = angle * 182;
    //logdv(_T("gameangle = %d"), (int)gameangle);

    //取当前角色角度
    int playerangle = (int)GetPlayerViewPoint();
    playerangle = playerangle % 65536;
    //logdv(_T("角色面向: %d"), playerangle);

    //判断当前角色的视角在第几象限
    if((pos.x > mypos.x) &&
            (pos.y > mypos.y))
    {
        //logdv(_T("目标当前东北"));
    }
    else if((pos.x > mypos.x) &&
            (pos.y < mypos.y))
    {
        //logdv(_T("目标在当前西北"));
        gameangle = 65536 - gameangle;
    }
    else if((pos.x < mypos.x) &&
            (pos.y < mypos.y))
    {
        //logdv(_T("目标当前西南"));
        gameangle += SOUTH;
    }
    else if((pos.x < mypos.x) &&
            (pos.y > mypos.y))
    {
        gameangle = SOUTH - gameangle;
        //gameangle += EAST;
    }
	else if((pos.x == mypos.x) &&
		(pos.y > mypos.y))  //x轴相同
	{
		//正东
		gameangle = EAST;
	}
	else if((pos.x == mypos.x) &&
		(pos.y < mypos.y))  //x轴相同
	{
		//正西面
		gameangle = WEST;
	}
	else if((pos.x > mypos.x) &&
		(pos.y = mypos.y))  //y轴相同
	{
		//正北
		gameangle = NORTH;
	}
	else if((pos.x < mypos.x) &&
		(pos.y = mypos.y))  //y轴相同
	{
		//正南
		gameangle = SOUTH;
	}

    Turn((int)gameangle);
}


//捡起尸体
//范围默认500
BOOL Gamecall::PickupDeadbody(DWORD range)
{
    std::vector<ObjectNode*> RangeObject;
    GetRangeObjectToVector(GetObjectBinTreeBaseAddr(), range, RangeObject);


    ObjectNode* pMaxNode = NULL;
    try
    {
        for(DWORD i = 0; i < RangeObject.size(); i++)
        {

            ObjectNode* pNode = RangeObject[i];


            //判断对象是否是可举起的尸体
            if(isDeadBody(pNode->ObjAddress))
            {
                pMaxNode = pNode;

                if(pNode->id > pMaxNode->id)
                    pMaxNode = pNode;

            }
        }

        if(pMaxNode == NULL)
        {
            TRACE(_T("没有遍历到尸体"));
            return false;
        }

        PARAM_GUANSHANGDIAN temp;
        temp.argv1 = pMaxNode->id;
        temp.argv2 = pMaxNode->id2;
        sendcall(id_msg_PickupDeadbody, &temp);
    }
    catch(...)
    {
        TRACE(FUNCNAME);
    }

    return TRUE;
}







void Gamecall::DeleteItem(_BAGSTU& bag)
{
    int pos = bag.m_Info;
    int value = pos;
    value <<= 16;
    value += package;

    int nums = bag.m_Num;

    __try
    {
        __asm
        {
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
    __except(1)
    {

    }


}
//随机方向走
void Gamecall::RandomStep(DWORD range)
{
    fPosition fmypos;
    GetPlayerPos(&fmypos);

    if((rand() % 2) == 1)
    {
        fmypos.x += range;
        fmypos.y += range;
    }
    else
    {
        fmypos.x -= range;
        fmypos.y -= range;
    }

    Stepto(fmypos, 10, 10);
}


void Gamecall::QuChuJiNengDian(DWORD ID) //去除技能点
{
    sendcall(id_msg_QuChuJiNengDian, (LPVOID)ID);
}


void Gamecall::_QuChuJiNengDian(DWORD ID) //去除技能点
{
    __try
    {
        _asm
        {
            push 0;
            mov eax, ID;
            push eax;
            mov eax, obj_enum_base;
            mov eax, [eax];
            mov eax, [eax+delete_strike_call_offset1];       //去除技能点一级偏移
            mov eax, [eax+delete_strike_call_offset2];       //去除技能点二级偏移
            mov eax, [eax+delete_strike_call_offset3];      //去除技能点三级偏移
            push eax;
            mov ebx, delete_strike_call;
            call ebx;
        }
    }
    __except(1)
    {
        TRACE(_T("去除技能点"));
    }

}



void Gamecall::DaKaiQingChuQuanBuJiNengJieMian(DWORD adress, DWORD adress1) //打开清除全部技能界面
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
    kj.canshu10 = 0x0;
    kj.canshu11 = 0x0;
    kj.canshu12 = 0x4EFE0016;

    __try
    {
        _asm
        {
            mov ecx, adress; //这个是控件的首地址  "SkillTrainPanel"
            mov edx, [ecx];
            mov eax, [edx+0x4];

            lea ebx, kj;
            push ebx;
            call eax
        }
    }
    __except(1)
    {
        TRACE(_T("打开清除全部技能界面CALL错误"));
    }
}

//打开清空技能点的ui
void Gamecall::OpenDeleteTalentPanel()
{
    sendcall(id_msg_OpenDeleteTalentPanel, 0);
}
//打开清空技能点的ui
void Gamecall::_OpenDeleteTalentPanel()
{
    DWORD dwUIAddr = 0;
    //PARAM_GETUIADDRBYNAME temp;
    //temp.argv1 = (DWORD)GetUIBinTreeBaseAddr();
    //temp.argv2 = (DWORD);
    //temp.argv3 = (DWORD);
    GetUIAddrByName(L"SkillTrainPanel", &dwUIAddr);
    DWORD canshu2 = 0;
    canshu2 =  ReadDWORD(dwUIAddr + clearstrike_isopen);

    if(canshu2 > 0)
    {
        DaKaiQingChuQuanBuJiNengJieMian(dwUIAddr, canshu2); //打开清除全部技能界面
    }
}

//确认清除全部技能界面
void Gamecall::QueRenQingChuQuanBuJiNengJieMian(DWORD adress, DWORD adress1)
{


    KONGJ kj;
    kj.canshu1 = QUDINGYAOJIANG_JIEGOUTOU;
    kj.canshu2 = 0x0;
    kj.canshu3 = 0x544D0EA8;
    kj.canshu4 = 0x0;
    kj.canshu5 = adress1;      //控件的首地址+0x70
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
            mov ecx, adress; //这个是控件的首地址  "SkillTrainInitConfirmPanel"
            mov edx, [ecx];
            mov eax, [edx+0x4];

            lea ebx, kj;
            push ebx;
            call eax
        }
    }
    __except(1)
    {
        TRACE(_T("确认清除全部技能界面CALL错误"));
    }
}

//确认删除天赋的ui
void Gamecall::ConfirmDeletePalentPanelShowOk()
{
    sendcall(id_msg_ConfirmDeletePalentPanelShowOk, 0);
}

//确认删除天赋的ui
void Gamecall::_ConfirmDeletePalentPanelShowOk()
{
    DWORD dwUIAddr = 0;
    GetUIAddrByName(L"SkillTrainInitConfirmPanel", &dwUIAddr);
    if(dwUIAddr)
    {
        DWORD canshu2 = 0;
        canshu2 =  ReadDWORD(dwUIAddr + 0x70);

        if(canshu2 > 0)
        {
            QueRenQingChuQuanBuJiNengJieMian(dwUIAddr, canshu2); //确认清除全部技能界面
        }
    }

}

//确认清除天赋的ui有没有显示
BOOL Gamecall::isConfirmDeleteTalnetPanelShow()
{
    DWORD dwUIAddr = 0;
    GetUIAddrByName(L"SkillTrainInitConfirmPanel", &dwUIAddr);
    if(dwUIAddr != 0)
    {
        DWORD canshu2 = 0;
        canshu2 =  ReadDWORD(dwUIAddr + clearstrike_isopen);
        if(canshu2)
            return TRUE;
        if(canshu2 == 0)
            TRACE(_T("清除技能界面没有打开"));
    }

    return FALSE;

}

void Gamecall::QueRenJiNengDian() //确认技能点
{
    sendcall(id_msg_QueRenJiNengDian, 0);
}

void Gamecall::_QueRenJiNengDian() //确认技能点
{
    __try
    {
        _asm
        {
            mov eax, obj_enum_base;
            mov eax, [eax];
            mov eax, [eax+confrim_add_strike_offset1];   //确认技能点一级偏移
            mov eax, [eax+confrim_add_strike_offset2];   //确认技能点二级偏移
            mov eax, [eax+confrim_add_strike_offset3];  //确认技能点三级偏移
            push eax;
            mov eax, confrim_call;
            call eax;


        }
    }
    __except(1)
    {
        TRACE(_T("确认技能点错误"));
    }

}

void Gamecall::JiaJiNengDian(DWORD ID) //加技能点
{
    sendcall(id_msg_JiaJiNengDian, (LPVOID)ID);
}
void Gamecall::_JiaJiNengDian(DWORD ID) //加技能点
{
    __try
    {
        _asm
        {


            push 0;
            mov eax, ID;
            push eax;
            mov eax, obj_enum_base;
            mov eax, [eax];
            mov eax, [eax+add_strike_offset1];  //加技能点一级偏移
            mov eax, [eax+add_strike_offset2];  //加技能点二级偏移
            mov eax, [eax+add_strike_offset3]; //加技能点三级偏移
            push eax;
            mov ebx, add_strike_call;
            call ebx;
        }
    }
    __except(1)
    {
        TRACE(_T("加技能点错误"));
    }

}

//天赋面板是否显示
BOOL Gamecall::isTalentPanelShow()
{

    DWORD dwUIAddr = 0;
    GetUIAddrByName(L"SkillTrainPanel", &dwUIAddr);

    DWORD canshu2 = 0;
    canshu2 =  ReadDWORD(dwUIAddr + skillpanel_isshow);

    if(canshu2 == 1)
        return TRUE;
    if(canshu2 == 2)
        TRACE(_T("技能面板没有打开"));

    return FALSE;
}

//经典模式CALL
void Gamecall::JingDianMoShi(DWORD adress, DWORD c5)
{
    KONGJ kj;
    kj.canshu1 = JINGDIANMOSHICALL_JIEGOUTOU;
    kj.canshu2 = 0x0;
    kj.canshu3 = 0x544D0EA8;
    kj.canshu4 = 0x0;
    kj.canshu5 = c5;      //控件的首地址+0x36FB0
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
            mov ebx, adress;  //这个是控件的首地址  "OptionPanel"
            mov ebx, [ebx + mouse_mode_class_offset1 + mouse_mode_class_offset11];
            mov eax, 0x1;
            mov dword ptr ds : [ebx + mouse_mode_class_offset2], eax;

            mov ecx, adress; //这个是控件的首地址  "OptionPanel"
            mov edx, [ecx];
            mov eax, [edx + 0x4];

            lea ebx, kj;
            push ebx;

            call eax
        }
    }

    __except(1)
    {
        TRACE(FUNCNAME);
    }
}


//技能攻击
//参数1: 技能名字
void Gamecall::Attack(const wchar_t* name)
{
    STRIKEINFO sinfo;
    if(GetStrikeByName(name, &sinfo))
        sendcall(id_msg_attack, (LPVOID)sinfo.id1);
}


//走向某个对象
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


//获取地图id
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
        TRACE(FUNCNAME);
    }

    return cityid;
}

//一层封装, 加入等待, 读条后才返回
BOOL Gamecall::PickupTask(ObjectNode* pNode)
{

    sendcall(id_msg_PickupTask, pNode);

	Sleep(1000);
    //判断读条
    //两个出口, 一个超时, 一个读条完成
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


//是否能看到
BOOL Gamecall::isCanLook(DWORD pAddr)
{
    //BYTE temp;
    wchar_t* name = (wchar_t*)ReadDWORD(ReadDWORD(pAddr + obj_type4_name_offset1) + 0x10);

    __try
    {

        if(IsBadStringPtr(name, MAX_PATH) == FALSE)
        {
            if(wcsstr(name, L"Dummy") != NULL)
            {
                return FALSE;
            }
        }
    }
    __except(1)
    {

    }
    return TRUE;
}

BOOL Gamecall::isPlayerDaodi()
{
    DWORD m_Adress = GetPlayerDataAddr();
    DWORD Adress = 0;
    bool State = FALSE;
    __try
    {
        if(m_Adress)
            Adress = ReadWORD(m_Adress + player_status_down);
        if(Adress == 0)
            State = FALSE;
        else
            State = TRUE;
    }
    __except(1)
    {
        TRACE(_T("获取角色倒地状态错误"));
    }

    return State;
}

void Gamecall::_NewSpend(float x)
{
    //DWORD dwThreadId;
    GameSpend* pSpender = GameSpend::GetInstance();

    if(pSpender->m_pfnInitSpeed != NULL)
    {
        pSpender->m_pfnInitSpeed(x);
    }
}

BOOL Gamecall::isStrikeCd(DWORD id)
{
	if (GetPlayerDeadStatus() == 0)
	{
		std::vector<STRIKEINFO> StrikeVec;
		sendcall(id_msg_GetStrikeToVector, &StrikeVec);
		//GetStrikeToVector();

		for(int i = 0; i < StrikeVec.size(); i++)
		{
			if(StrikeVec[i].id1 == id)
			{
				if(StrikeVec[i].isBlock == 1 && StrikeVec[i].canUse == 0)
				{
					//CD= 2是冷却 =1 是释放中
					if(StrikeVec[i].cd == 0)
						return TRUE;
					else
						return FALSE;
				}
				else
					break;
			}
		}
	}else
	{
		TRACE(_T("人物死亡，不遍历。"));
	}
    
    return FALSE;
}

wchar_t* Gamecall::GetExperienceName(DWORD ID)
{
	wchar_t *name = {0};
	_try
	{
		__asm
		{
			mov eax,obj_name_call_base;
			mov eax,[eax];
			mov ecx,[eax+obj_name_call_offset1]
			mov edx,[ecx]
			mov edx,[edx+obj_name_call_offset2]
			push 0;
			mov ebx,ID;
			push ebx;
			call edx;
			mov eax,[eax+0x18];
			mov name,eax;
		}
	}
	_except(1)
	{
		TRACE(_T("获取经验名字错误"));
		return NULL;
	}
	return name;
}


DWORD Gamecall::GetExperienceNameID(DWORD ID)
{
	DWORD ID1 = 0;
	_try
	{
		__asm
		{
			mov eax,obj_name_call_base;
			mov eax,[eax];
			mov ecx,[eax+Experience_status_offset2] //经验效果的二级偏移
			mov edx,[ecx]
			mov edx,[edx+obj_name_call_offset2]
			push 0;
			mov ebx,ID;
			push ebx;
			call edx;
			mov eax,[eax+0x14];
			mov ID1,eax;
		}
	}
	_except(1)
	{
		TRACE(_T("获取经验名字ID错误"));
		return NULL;
	}
	return ID1;
}

DWORD Gamecall::GetExperienceNameID_SY(int i,DWORD m_adress)
{
	DWORD Adress = 0;
	_try
	{
		if ( m_adress != 0 )
		{
			Adress = ReadDWORD( m_adress + i*Experience_status_offset3 + Experience_status_offset4 ) ;   //C0是三级偏移   1C是四级偏移
		}
	}
	_except(1)
	{
		TRACE(_T("获取名字ID结构的索引错误"));
		return -1;
	}
	return Adress;
}

BOOL Gamecall::GetPlayExperienceStatusName(DWORD m_adressA,wchar_t * ExperienceName)
{
	wchar_t *name = {0};
	DWORD pos = 0;
	DWORD pos1 = 0;
	DWORD SY = 0;
	DWORD ID = 0;
	pos = ReadDWORD(m_adressA+Experience_status_offset1+0x4);

// TRACE1("pos===%d",pos);

	pos1 = ReadDWORD(m_adressA+Experience_status_offset1);  //经验效果的一级偏移

// TRACE1("pos1===%d",pos1);
	
	if ( pos > 0 )
	{
		for ( int i = 0; i < 10; i++  )
		{
			SY = GetExperienceNameID_SY( i,pos1);  //获取名字ID结构的索引
			if ( SY == 0 )
			{
				return false;
			}
			ID = GetExperienceNameID(SY); //获取经验名字ID
			if ( ID != 0 )
			{
				name =  GetExperienceName(ID); //获取经验名字
				if ( wcscmp(name,ExperienceName) == 0 )
				{
// 					TRACE(_T("返回true"));
					return true;
				}
			}
		}
	}
// 	TRACE(_T("返回FALSE"));
	return FALSE;
}


BOOL Gamecall::GetPlayExperienceStatus()
{
    //KONGJIAN_JIEGOU JIEGOU = {NULL};
    //DWORD *pUiAddr = 0;
    //wchar_t *str = L"";  //ItemGrowth2Panel
    //GetUIAddrByName(L"", pUiAddr);
    //if(*pUiAddr == 0)
    //  return FALSE;
    KONGJIAN_JIEGOU jiegou;
	ZeroMemory(&jiegou,sizeof(KONGJIAN_JIEGOU));
    jiegou.adress = (DWORD)GetUIBinTreeBaseAddr();
    jiegou.name = L"00008130.UI.Normal_10";
    jiegou.ID = 0;
    GetUiAddrByName(jiegou);

	//TRACE1("ui:%x",jiegou.adress);

	wchar_t * ExperienceName = L"???"; //这个名字就是经验药品在左边的名字

	KONGJIAN_JIEGOU jiegou2;
	ZeroMemory(&jiegou2,sizeof(KONGJIAN_JIEGOU));
	jiegou2.adress = jiegou.ID;
	jiegou2.name = ExperienceName;
	BOOL pos = FALSE;
	pos = (BOOL)sendcall(id_msg_GetPlayExperienceStatusName,&jiegou2);
	//pos =  GetPlayExperienceStatusName(jiegou.adress,str1);  //获取经验名字  参数1是UI地址  参数2 是药品的名字
	if ( pos == TRUE )
	{
		TRACE(_T("经验药已经吃了"));
		 return TRUE;
	}
	else
	{
		TRACE(_T("没有吃经验药"));
		return FALSE;
	}

   /* DWORD pos = -1;
    pos = ReadDWORD(ReadDWORD(jiegou.ID + 0x83F8) + 0x1C);
    TRACE1("经验效果的ID %X", pos);
    if(pos != 0)
    {
        TRACE(_T("经验药物已经吃了,不需要再吃了"));
        return TRUE;
    }
    if(pos == 0)
        TRACE(_T("没有吃经验药物,请吃经验药物"));
    return FALSE;*/
}

void Gamecall::GetUiAddrByName(KONGJIAN_JIEGOU& jiegou)
{
    TRACE(_T("add:%x,name:%s,fanhui:%x"), jiegou.adress, jiegou.name, jiegou.ID);
    sendcall(id_msg__GetUiAddrByName, &jiegou);
}

void Gamecall::_GetUiAddrByName(Tree* Addr, wchar_t* name, DWORD& reAddr)
{
    if(Addr->p2 == 1)
    {
        //TRACE(_T("推出了"));
        return ;
    }
    if(reAddr > 0)   //
    {
        //TRACE(_T("返回了"));
        return;
    }
    wchar_t* uiname  = {0};

    if(!IsBadReadPtr((void*)GetUiNewName(Addr->Adress), sizeof(DWORD)))
    {
        uiname = GetUiNewName(Addr->Adress);//获取技能面板名字
        if(wcsstr(uiname, name) != NULL)
        {
            //TRACE(_T("找到需要的控件了"));
            TRACE(_T("找到UI名:%s,找到控件地址:%d"),uiname,Addr->Adress);
            reAddr = Addr->Adress;
            return ;
        }
    }
    _GetUiAddrByName(Addr->Right, name, reAddr);
    _GetUiAddrByName(Addr->Left, name, reAddr);
}

wchar_t* Gamecall::GetUiNewName(DWORD pBarAddr)
{
    wchar_t* name = {0};
    __try
    {
        name = (wchar_t*)ReadDWORD(pBarAddr + 0x94);
    }
    __except(1)
    {
        TRACE(L"获取技能面板名字错误");
    }
    return name;

}

void Gamecall::_LinQuJiangLi()
{
    DWORD uiAddr = 0;

    GetUIAddrByName(L"SurveyRewardPanel", &uiAddr);
    if(uiAddr == 0)
        return;

    __try
    {
        __asm
        {

            mov eax, obj_enum_base;
            mov eax, [eax];
            mov eax, [eax + get_jiangli_offset1];
            mov eax, [eax + get_jiangli_offset2];
            mov ecx, [eax + get_jiangli_offset3];
            mov edi, uiAddr;
            mov edx, [edi + get_jiangli_offset4];
            push edx;
            mov eax, get_jiangli_call;
            call eax;
        }
    }
    __except(1)
    {
        TRACE(FUNCNAME);
    }
}

void Gamecall::_NPCJieRenWu(DWORD canshu1, DWORD canshu2, DWORD canshu3, DWORD canshu4, DWORD canshu5)
{
    __try
    {
        __asm
        {
            mov ebx, canshu5;
            push ebx;
            mov ebx, canshu4;
            push ebx;
            mov ebx, canshu3;
            push ebx;
            mov ebx, canshu2;
            push ebx;
            mov ebx, canshu1;
            push ebx;

            mov eax, obj_enum_base;
            mov eax, [eax];
            mov eax, [eax + npc_quest_offset1];
            mov eax, [eax + npc_quest_offset2];
            mov ecx, [eax + npc_quest_offset3];
            mov edx, [eax + npc_quest_offset4];
            push edx;
            mov eax, [eax + npc_quest_offset5];
            push eax;

            mov ebx, npc_quest_call;
            call ebx;
        }
    }
    __except(1)
    {
        TRACE(FUNCNAME);
    }
}

void Gamecall::ChangeZ_Status(BOOL flag)
{
    HMODULE hBsengine = ::GetModuleHandle(_T("bsengine_Shipping"));
    unsigned addr = (unsigned)hBsengine;
    unsigned addr1 = (unsigned)hBsengine;
	addr = addr + 0x0597455;
    addr1 = addr1 + 0x0A410C3;//0x0A410FC--
	//A410BB
	//A410D3
	//A410C3
    DWORD pi = 0;
    DWORD pi1 = 0;

    //VirtualProtect((void*)addr,4,PAGE_EXECUTE_READWRITE ,&pi);
    //*(WORD*)(addr) = 0x0EEB;
    //VirtualProtect((void*)addr,4,pi ,&pi);
    if(flag)
    {
        if(ReadByte(addr) == 0xF3)
        {
            VirtualProtect((void*)addr, 4, PAGE_EXECUTE_READWRITE , &pi);
            *(WORD*)(addr) = 0x05EB;//0x05EB
            VirtualProtect((void*)addr, 4, pi , &pi);
        }
        if(ReadByte(addr1) == 0xD9)
        {
            VirtualProtect((void*)addr1, 4, PAGE_EXECUTE_READWRITE , &pi1);
            *(WORD*)(addr1) = 0x01EB;
            VirtualProtect((void*)addr1, 4, pi1 , &pi1);
        }
    }
    else
    {
        if(ReadByte(addr) == 0xEB)
        {
            VirtualProtect((void*)addr, 4, PAGE_EXECUTE_READWRITE , &pi);
            *(WORD*)(addr) = 0x0FF3;
            VirtualProtect((void*)addr, 4, pi , &pi);
        }
        if(ReadByte(addr1) == 0xEB)
        {
            VirtualProtect((void*)addr1, 4, PAGE_EXECUTE_READWRITE , &pi1);
            *(WORD*)(addr1) = 0x5ED9;
            VirtualProtect((void*)addr1, 4, pi1 , &pi1);
        }
    }

}

void Gamecall::ChangeHeight(float how)
{
    HMODULE hBsengine = ::GetModuleHandle(_T("bsengine_Shipping"));
    unsigned addr = (unsigned)hBsengine;
    addr = addr + SHENXINGBAIBIANCHAZHI;

	//TRACE1("addr:%x",addr);
    //int gg = 43480000;
    __try
    {
        __asm
        {
            mov eax, addr;
            mov eax, [eax];
            mov eax, [eax + 0x3bc];
            mov eax, [eax];
            mov eax, [eax + 0x40];
            mov eax, [eax + 0x214];
            //add eax, 0x5C;
            mov ebx, how;
            mov dword ptr ds:[eax+0x5C], ebx;


        }
    }
    __except(1)
    {
        TRACE(_T("飞起错误"));
    }
}

DWORD Gamecall::GetObjectSy_90(DWORD pObjAddress)
{
    DWORD result;
    result = 0;
    __try
    {
        result = ReadDWORD(ReadDWORD(pObjAddress + 0x3c) + 0x194);
    }
    __except(1)
    {
        TRACE(FUNCNAME);
    }
    return result;
}

DWORD Gamecall::GetPlayerQuestUIStatusts()
{
    DWORD pAddr = GetPlayerDataAddr();
    int value = 0;


    __try
    {
        value = ReadDWORD(ReadDWORD(pAddr + 0x14) + 0x218);
        /*__asm
        {
        mov eax, pAddr;
        mov eax, [eax + player_status_openblock];
        movzx eax, al;
        mov value, eax;
        }*/
    }
    __except(1)
    {
        TRACE(_T("%s"), FUNCNAME);
    }

    return value;
}

BOOL Gamecall::PickupTaskts(ObjectNode* pNode)
{
    TRACE(_T("执行ts"));
    sendcall(id_msg_PickupTask, pNode);

    DWORD uiaddr;
    uiaddr = 0;
    DWORD ui_status;
    ui_status = 0;

    for(int i = 0; i < 10; i++)
    {
        GetUIAddrByName(L"PickupItemPanel", &uiaddr);
        TRACE1("ui地址:%x", uiaddr);
        if(uiaddr != NULL)
            ui_status = ReadDWORD(uiaddr + 0x38);

        TRACE1("ui_status:%d", ui_status);
        if(ui_status == 1)
        {
            if(isPlayPickupUiStatus())
            {
                TRACE(_T("执行upckup2"));
                sendcall(id_msg_Pickup2ts, (LPVOID)0);
                return TRUE;
            }
        }
        Sleep(1000);
    }
    TRACE(_T("未找到UI,跳出"));

    return FALSE;
}

BOOL Gamecall::isPlayPickupUiStatus()
{
    DWORD pAddr = GetPlayerDataAddr();
    int value = 0;


    __try
    {
        value = ReadDWORD(ReadDWORD(pAddr + 0x704) + 0x8);
        if(value != NULL)
            return TRUE;

        /*__asm
        {
        mov eax, pAddr;
        mov eax, [eax + player_status_openblock];
        movzx eax, al;
        mov value, eax;
        }*/
    }
    __except(1)
    {
        TRACE(_T("%s"), FUNCNAME);
    }

    return FALSE;
}

void Gamecall::Pickup2ts()
{
    DWORD addr = GetPlayerDataAddr();
    __try
    {
        _asm
        {
            mov eax, addr;
            mov ecx, [eax+pickup2_offset3]; //二次捡物三级偏移
            push ecx;

            mov eax, Pickup2_call_ts;
            call eax;
        }
    }
    __except(1)
    {
        TRACE(_T("特殊二次捡物出错"));
    }

}


void Gamecall::CloseXiaoDongHua()
{
    DWORD dtzt;
    dtzt = (DWORD)ReadByte(ReadDWORD(ReadDWORD(ReadDWORD(move_status_base) + move_status_offset1) + move_status_offset2) + move_status_offset3 + move_status_offset31); //是否有小动画 0是有 1是没有
    //TRACE1("小动画状态:%d",dtzt);
    if(dtzt == 1)
    {
        //TRACE(_T("动画状态中"));
        //KeyPress(VK_ESCAPE);
        Sleep(500);
        KeyPress(27);
        Sleep(500);
    }

}

DWORD Gamecall::GetKaiShiAdress()  //获取开始地址
{
    DWORD Adress;
    Adress = 0;
    _try
    {
        Adress = ReadDWORD(ReadDWORD(ReadDWORD(obj_name_call_base) + Wuqi_po10_offset1) + Wuqi_po10_offset2);
    }
    _except(1)
    {
        TRACE(_T("获取开始地址错误"));
    }
    return Adress;
}

DWORD Gamecall::GetBiJiaoShu(int i, DWORD m_adress) //获取比较数值
{

    DWORD Adress = 0;
    _try
    {
        if(m_adress != 0)
            Adress = (DWORD)ReadByte(ReadDWORD(m_adress + i * 4) + 0x30);
    }
    _except(1)
    {
        TRACE(_T("获取比较数值错误"));
    }
    return Adress;
}

DWORD Gamecall::_IsCanShu(DWORD adress, DWORD adress1) //是否是这个参数
{
    byte is = 0;
    if(adress == 0 || adress1 == 0)
        return -1;
    _try
    {
        _asm
        {
            mov ecx, adress;
            push ecx;
            mov eax, adress1;
            movzx eax, byte ptr ds:[eax+Iscs_po10_cmp_offset1];
            push eax;
            mov eax, adress1;
            mov eax, dword ptr ds:[eax+Iscs_po10_cmp_offset2];
            push eax;
            mov eax, Iscs_po10_cmp_Call;
            call eax;
            add esp, 0xC;
            mov is, al;

        }
    }
    _except(1)
    {
        TRACE(_T("是否是这个参数出错"));
        return -1;
    }
    return (DWORD)is;
}

DWORD Gamecall::IsCanShu(DWORD adress, DWORD adress1) //是否是这个参数
{
    PARAM_JIEFENGZHUANGBEI temp;
    temp.argv1 = adress;
    temp.argv2 = adress1;
    return (DWORD)sendcall(id_msg_IsCanShu, &temp);
}


DWORD Gamecall::GetBiJiaoShu1(int i, DWORD m_adress) //获取比较数值1
{

    DWORD Adress = 0;
    _try
    {
        if(m_adress != 0)
            Adress = (DWORD)ReadByte(ReadDWORD(m_adress + i * 4) + 0x8);
    }
    _except(1)
    {
        TRACE(_T("获取比较数值1错误"));
        return -1;
    }
    return Adress;
}

DWORD Gamecall::GetBiJiaoShu2(int i, DWORD m_adress) //获取比较数值2
{

    DWORD Adress = 0;
    _try
    {
        if(m_adress != 0)
            Adress = (DWORD)ReadByte(ReadDWORD(m_adress + i * 4) + Wuqi_po10_cmp2_offset);
    }
    _except(1)
    {
        TRACE(_T("获取比较数值2错误"));
        return -1;
    }
    return Adress;
}


DWORD Gamecall::GetBiJiaoShu3(DWORD m_adress)  //获取比较数值3 这里用到的2个地址都是随便弄的，还没有固定的特征码。
{

    DWORD Adress = 0;
    _try
    {
        if(m_adress != 0)
            Adress = ReadDWORD(ReadDWORD(m_adress + obj_type4_id2_offset) + obj_type4_view_offset1);
    }
    _except(1)
    {
        TRACE(_T("获取比较数值3错误"));
    }
    return Adress;
}

DWORD Gamecall::GetBiJiaoShu4(int i, DWORD m_adress) //获取比较数值4
{

    DWORD Adress = 0;
    _try
    {
        if(m_adress != 0)
            Adress = ReadDWORD(ReadDWORD(m_adress + i * 4) + Wuqi_po10_cmp4_offset);
    }
    _except(1)
    {
        TRACE(_T("获取比较数值4错误"));
        return -1;
    }
    return Adress;
}

//卸装备
//参数是身上的格子数
//TODO:
void Gamecall::_XieZhuangBei(DWORD pos)
{
    __try
    {
        __asm
        {
            mov eax, pos;
            push eax;
            mov eax, obj_enum_base;
            mov eax, [eax];
            mov eax, [eax+xiezhuangbei_offset1];
            mov eax, [eax+xiezhuangbei_offset2];
            mov eax, [eax+xiezhuangbei_offset3];
            push eax;
            mov eax, xiezhuangbei_call;
            call eax;
        }
    }
    __except(1)
    {
        TRACE(_T("卸装备出错"));
    }
}

BOOL Gamecall::GetPlayerFightingStatus()
{
	DWORD pAddr = GetPlayerDataAddr();
	int value = 0;


	__try
	{
		value =ReadDWORD(pAddr + Play_fighting_status_offset3);
		//TRACE1("战斗状态:%d",value);
	}__except(1)
	{
		TRACE(_T("获得战斗状态出错"));
	}

	return (value==1);
}


DWORD Gamecall::DuiWu_EndAdress() //遍历队伍的结束地址
{
    DWORD Adress;
    _try
    {
        _asm
        {
            mov eax, obj_enum_base;
            mov eax, [eax+0];
            mov eax, [eax+0x34];
            mov eax, [eax+0x80];
            mov eax, [eax+0x79C];
            mov eax, [eax+0x18];  //遍历队伍的结束地址四级偏移
            mov Adress, eax;


        }

    }
    _except(1)
    {
        TRACE(_T("遍历队伍的结束地址出错"));
        return 0;
    }
    return Adress;
}

void Gamecall::TuiChuDuiWu() //退出队伍
{
    __try
    {
        __asm
        {
            mov eax, 0x004EA9A0;
            call eax;
        }
    }
    _except(1)
    {
        TRACE(_T("退出队伍出错"));
    }
}

void Gamecall::YaoQingZuDui(DWORD ID, DWORD Info) //邀请组队 参数1是对象ID  参数2 就是10000数值
{
    __try
    {
        __asm
        {
            push 0;
            push 0;
            mov eax, Info;
            push eax;
            mov eax, ID;
            push eax;
            mov eax, obj_enum_base;
            mov eax, [eax];
            mov eax, [eax+invite_party_call_offset1];   // 邀请组队一级偏移
            mov eax, [eax+invite_party_call_offset2];   // 邀请组队二级偏移
            mov eax, [eax+invite_party_call_offset3];  // 邀请组队三级偏移
            push eax;
            mov eax, invite_party_call;
            call eax;

        }
    }
    _except(1)
    {
        TRACE(_T("邀请组队出错"));
    }
}

BYTE ReadByte(DWORD addr)
{
    if(!IsBadReadPtr((void*)addr, sizeof(BYTE)))
    {
        return *(BYTE*)addr;
    }
    return 0;
}

WORD ReadWORD(DWORD addr)
{
    if(!IsBadReadPtr((void*)addr, sizeof(WORD)))
    {
        return *(WORD*)addr;
    }
    return 0;
}

DWORD ReadDWORD(DWORD addr)
{
    if(!IsBadReadPtr((void*)addr, sizeof(DWORD)))
    {
        return *(DWORD*)addr;
    }
    return 0;
}

int ReadInt(DWORD addr)
{
    if(!IsBadReadPtr((void*)addr, sizeof(int)))
    {
        return *(int*)addr;
    }
    return 0;
}

float ReadFloat(DWORD addr)
{
    if(!IsBadReadPtr((void*)addr, sizeof(float)))
    {
        return *(float*)addr;
    }
    return 0;
}

char* ReadStr(DWORD addr)
{
    if(!IsBadReadPtr((void*)addr, sizeof(char)))
    {
        return (char*)addr;
    }
    return 0;
}

