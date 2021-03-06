#include "stdafx.h"
#include "JLwg.h"
#include "Gamecall.h"
#include "GamecallEx.h"
#include "GameConfig.h"
#include "GameSpend.h"
#include "gamehook.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



//全局变量
const double M_PI = 3.14159265358979323846;


//单件
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
            return (BOOL)GetPlayExperienceStatusName(jiegou->adress, jiegou->name);
        }
        break;
    case id_msg_Operation:
        {
            PARAM_2* temp = (PARAM_2*)pParam;
            _Operation(temp->argv1, temp->argv2);
            break;
        }

    case id_msg_XieZhuangBei:
        {
            _XieZhuangBei((DWORD)pParam);
        }
        break;
    case id_msg_IsCanShu:
        {
            PARAM_2* temp = (PARAM_2*)pParam;
            return (DWORD)_IsCanShu(temp->argv1, temp->argv2);
        }
        break;
    case id_msg_NPCJieRenWu:
        {
            PARAM_5* temp = (PARAM_5*)pParam;
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
            GetStrikeToVector(*(StrikeVector*)pParam);
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
            _GetAllBodyEquipToVector(*(BagVector*)pParam);
        }
        break;
    case id_msg_GetAllGoodsToVector:
        {
            _GetAllGoodsToVector(*(BagVector*)pParam);

        }
        break;

    case id_msg_GetUItoVector:
        {
            PARAM_2* temp = (PARAM_2*)pParam;
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
            PARAM_3* temp = (PARAM_3*)pParam;
            GouMaiWuPing(temp->argv1, temp->argv2, temp->argv3);
        }
        break;

    case id_msg_XieBaoShi:
        {
            PARAM_3* temp = (PARAM_3*)pParam;
            XieBaoShi(temp->argv1, temp->argv2, temp->argv3);
        }
        break;

    case id_msg_JiaBaoShi:
        {
            PARAM_5* temp = (PARAM_5*)pParam;
            JiaBaoShi(temp->argv1, temp->argv2, temp->argv3, temp->argv4, temp->argv5);
        }
        break;

    case id_msg_JieFengZhuangBei:
        {
            PARAM_7* temp = (PARAM_7*)pParam;
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
            PARAM_2* temp = (PARAM_2*)pParam;
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
    case id_msg_Pickup2ts:
        {
            Pickup2ts();
        }
        break;
    case id_msg_OpenQuestItem:
        {
            PARAM_2* temp = (PARAM_2*)pParam;
            OpenQuestItem(temp->argv1, temp->argv2);
        }
        break;


    case id_msg_ZOULUSHUNYI:
        {
            PARAM_2* temp = (PARAM_2*)pParam;
            ZOULUSHUNYI((DWORD*)temp->argv1, temp->argv2);
        }
        break;

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
            PARAM_2* temp = (PARAM_2*)pParam;
            PickupDeadbody(temp->argv1, temp->argv2);
        }
        break;
    case id_msg_HeChengWuQi_Po10:
        {
            PARAM_3* temp = (PARAM_3*)pParam;
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
            PARAM_8* temp = (PARAM_8*)pParam;
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
            PARAM_2* temp = (PARAM_2*)pParam;
            DaKaiDuiHuaKuang(temp->argv1, temp->argv2);
        }
        break;

    case id_msg_attack:
        {
            return _Attack((DWORD)pParam);
        }
    case id_msg_clickui:
        {
            UIOperator* pOpui = (UIOperator*)pParam;
            ClickUI(*pOpui);
        }
        break;

    case id_msg_HeChengWuQi_Po5:
        {
            PARAM_2* temp = (PARAM_2*)pParam;
            HeChengWuQi_Po5(*(_BAGSTU*)temp->argv1, *(_BAGSTU*)temp->argv2);
        }
        break;

    case id_msg_HeChengWuQi:
        {
            PARAM_2* temp = (PARAM_2*)pParam;
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
            CunCangku(*(_BAGSTU*)pParam);
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
    BagVector EquiVec;
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
BOOL Gamecall::GetGoodsFromBagByName(std::wstring name, BagVector& GoodsVec)
{
    DWORD BagbodyAdress = 0;
    DWORD BagAdress = 0;
    int GridNum = 0;
    BOOL bFind = FALSE;
    _BAGSTU bag;

    BagbodyAdress = GetBagbodyInfoBase();                //获取背包身上装备仓库遍历Base
    if(BagbodyAdress == 0)
    {
        TRACE(_T("获取背包身上装备仓库遍历base问题"));
        return FALSE;
    }

    BagAdress = GetBagInfoBase(BagbodyAdress);           //获取背包遍历Base
    if(BagAdress == 0)
    {
        TRACE(_T("获取背包遍历base问题"));
        return FALSE;
    }
    GridNum = GetBagGridNumber();                        //当前背包的总的格子数

    for(int i = 0; i < GridNum; i++)
    {
        ZeroMemory(&bag, sizeof(_BAGSTU));
        bag.m_Base = GetGoodsBase(BagAdress, i);                 //获取物品的首地址
        if(bag.m_Base != 0)
        {
            if(FillGoods(bag))
            {
                //游戏里本来是0
                bag.m_Num = (bag.m_Num == 0 ? 1 : bag.m_Num);

                if(bag.name == name)
                {
                    GoodsVec.push_back(bag);
                    bFind = TRUE;
                }
            }
        }
    }

    return bFind;
}

//根据名字取得物品信息
//这个函数是专门找盒子名字的
//区别就是对名字的匹配上
BOOL Gamecall::GetGoodsByName_Hezi(wchar_t* name, BagVector& GoodsVec)
{

    _ASSERTE(name != NULL);


    int len = wcslen(name) + 1;
    wchar_t* fixName = new wchar_t[len];
    wcscpy(fixName, name);
    fixName[len-2] = L' ';
    fixName[len-1] = L'\0';


    BagVector AllGoods;
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

    _ASSERTE(name != NULL);



    BagVector EquiVec;
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

    //获取加载的游戏dll的地址
    m_hModuleBsEngine = GetModuleHandle(_T("bsengine_Shipping"));
    if(m_hModuleBsEngine == NULL)
    {
        TRACE(_T("获取BsEngine模块失败"));
        return FALSE;
    }


    return TRUE;
}

//整理背包ui
DWORD Gamecall::SortBag()
{
    DWORD dwRet = 0;

    __asm
    {

        mov  eax, Offset_Game_Base
        mov  eax, dword ptr ds: [eax]
        mov  eax, dword ptr ds: [eax + Offset_Game_Offset]
        mov  eax, dword ptr ds: [eax + Offset_Role_Offset]
        mov  eax, dword ptr ds: [eax + Offset_Item_Offset]
        test eax, eax
        je   fun_exit

        push 0
        push 0
        push 2
        push eax
        mov eax, FUNC_PACKAGEARRANGE
        call eax;


        fun_exit:
        mov  dwRet, eax
    }

    return FALSE;
}

//村仓库
//参数1: 背包中的格子数
void Gamecall::CunCangku(_BAGSTU& goods)
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



void Gamecall::GetAcceptedQuestToVector(TaskVector& QuestVec)
{

    //最大任务数量
    int MaxNums = 53;


    DWORD PPTR = ReadDWORD(Offset_Game_Base);
    PPTR = ReadDWORD(PPTR + Offset_Game_Offset);
    PPTR = ReadDWORD(PPTR + Offset_Role_Offset);
    PPTR = ReadDWORD(PPTR + Offset_Quest_Offset);

    _ASSERTE(PPTR != 0);

    TASK task;
    for(int i = 0; i < MaxNums; i++)
    {
        //信息指针
        DWORD PInfo = PPTR + i * 0x58 + Offset_Quest_PInfo;

        if(ReadDWORD(PInfo) > 0)
        {
            //{当前步骤}
            task.Step = ReadByte(PInfo + Offset_Quest_Step);

            //{当前步骤目标完成1}
            task.bStepTagDone1 = ReadByte(PInfo + Offset_Quest_StepTagDone1) == 1;
            //{当前步骤目标完成数1}
            task.StepTagCount1 = ReadByte(PInfo + Offset_Quest_StepTagCount1);

            //{当前步骤目标完成2}
            task.bStepTagDone2 = ReadByte(PInfo + Offset_Quest_StepTagDone2) == 1;
            //{当前步骤目标完成数2}
            task.StepTagCount2 = ReadByte(PInfo + Offset_Quest_StepTagCount2);

            //{当前步骤目标完成3}
            task.bStepTagDone3 = ReadByte(PInfo + Offset_Quest_StepTagDone3) == 1;
            //{当前步骤目标完成数3}
            task.StepTagCount3 = ReadByte(PInfo + Offset_Quest_StepTagCount3);

            //{当前步骤目标完成2}
            task.bStepTagDone4 = ReadByte(PInfo + Offset_Quest_StepTagDone4) == 1;
            //{当前步骤目标完成数2}
            task.StepTagCount4 = ReadByte(PInfo + Offset_Quest_StepTagCount4);

            //{信息指针}
            PInfo = ReadDWORD(PInfo);

            // {步骤指针}
            DWORD PStep = ReadDWORD(PInfo + (task.Step - 1) * 0x4 + Offset_Quest_PStep);
            if(PStep > 0)
            {
                //{步骤Id}
                PStep = ReadDWORD(PStep);
                task.StepNameId = ReadDWORD(PStep + Offset_Quest_StepId);
                // {步骤名}
                task.StepName = GetObjectNameByIndex(task.StepNameId);
            }


            //{信息指针}
            DWORD PPInfo = ReadDWORD(PInfo);

            if(PPInfo > 0)
            {
                // {任务Id}
                task.id = ReadDWORD(PPInfo + Offset_Quest_QuestId);
                //{名字Id}
                DWORD NameId = ReadDWORD(PPInfo + Offset_Quest_NameId);
                //{名字}
                task.nName = GetObjectNameByIndex(NameId);
            }


            QuestVec.push_back(task);
        }
    }

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
    DWORD PlayerInfo = 0;

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
BOOL Gamecall::GetPlayerPos(fPosition* fpos)
{
    _ASSERTE(fpos != NULL);

    BOOL bRet = FALSE;
    DWORD dwPlayer = GetPlayerDataAddr();

    __try
    {
        __asm
        {
            mov eax, dwPlayer;
            mov eax, [eax + player_steppos_x_offset1];
            add eax, player_steppos_x_offset2;

            mov edx, eax;
            mov eax, [edx];

            mov ebx, fpos;
            mov[ebx]fpos.x, eax;   //0x3ce4

            add edx, 4;
            mov eax, [edx];
            mov[ebx]fpos.y, eax;  //0x3ce8

            add edx, 4;
            mov eax, [edx];
            mov[ebx]fpos.z, eax; //0x3cec
        }

        bRet = TRUE;
    }
    __except(1)
    {
        TRACE(FUNCNAME);
    }

    return bRet;
}


//取得玩家坐标
BOOL Gamecall::GetPlayerPos2(sPosition* spos)
{

    _ASSERTE(spos != NULL);

    DWORD PlayerInfo = GetPlayerDataAddr();


    __try
    {
        __asm
        {
            mov edx, PlayerInfo;
            mov eax, [edx + player_pos2_x];

            mov ebx, spos;
            mov[ebx]spos.x, ax;

            mov eax, [edx + player_pos2_y + 2];
            mov[ebx]spos.y, ax;

            mov eax, [edx + player_pos2_y + 4];
            mov[ebx]spos.z, ax;
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


//走路
void Gamecall::Step(float x, float y, float z)
{

    __try
    {
        __asm
        {
            mov  edi, Offset_Game_Base
            mov  edi, [edi]
            mov  edi, [edi+ Offset_Game_Offset]
            mov  edi, [edi+ Offset_Role_Offset]
            mov  ecx, [edi+ Offset_Role_Attr]

            fld  z
            sub  esp, 0xC
            fstp [esp+ 0x8]
            fld  y
            fstp [esp+ 0x4]
            fld  x
            fstp [esp]
            mov eax, FUNC_WALK
            call eax;
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

        Stepto3x();
        Step(x, y, z);
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
//1 or 2 = 玩家 宠物
//type = 0x20 任务物品(资源)
//type = 0x4  怪物 npc
//type = 0xb0 尸体和掉落物品,
//type = 0x90 特殊任务物品
byte Gamecall::GetObjectType(DWORD pObjAddress)
{
    if(pObjAddress < 0x3000000)
    {
        return 0;
    }
    byte objtype = 0;

    __try
    {
        __asm
        {
            mov eax, pObjAddress;
            mov eax, [eax + obj_type_offset];
            mov objtype, al;
        }
    }
    __except(1)
    {
        TRACE(FUNCNAME);
    }

    return objtype;
}



BOOL Gamecall::GetObjectPos(ObjectNode* pNode, fPosition* fpos)
{

    DWORD type = (DWORD)GetObjectType(pNode->ObjAddress);
    DWORD pInfo = pNode->ObjAddress;

    if(pInfo < 0x3000000)
    {
        TRACE(_T("传入pInfo小于0x3000000..当前pInfo=%x"), pInfo);
        return FALSE;
    }
    if(pInfo == 0)
    {
        TRACE(_T("传入pInfo=0..当前pInfo=%x"), pInfo);
        return FALSE;
    }
    if(type == 0)
    {
        TRACE("未能获取类型");
        return FALSE;
    }
    __try
    {
        if(type == 0x20)
        {
            __asm
            {
                mov edx, pInfo;
                mov eax, [edx + 0x28];

				cmp eax, 0;
				jnz libJmp20;
				xor eax, eax;
				leave;
				ret;
libJmp20:
                mov ebx, fpos;
                mov[ebx]fpos.x, eax;

                mov eax, [edx + 0x2c];
                mov[ebx]fpos.y, eax;

                mov eax, [edx + 0x30];
                mov[ebx]fpos.z, eax;
            }

            //*4后和 角色坐标是相同的
            fpos->x = fpos->x * 4;
            fpos->y = fpos->y * 4;
            fpos->z = fpos->z * 4;

        }
        else if(type == 0xb0)
        {
            sPosition spos;
            __asm
            {
                mov edx, pInfo;
                mov eax, [edx +  ojb_typeb0_pos2_x];

                lea ebx, spos;
                mov [ebx]spos.x, ax;

                mov eax, [edx + ojb_typeb0_pos2_x + 2];
                mov [ebx]spos.y, ax;

                mov eax, [edx + ojb_typeb0_pos2_x + 4];
                mov [ebx]spos.z, ax;
            }

            ShortPosToFloatPos(spos, *fpos);
        }
        else if(type == 0x4)
        {

            int temp1 = obj_type4_pos_x_offset2 + 4;
            int temp2 = obj_type4_pos_x_offset2 + 8;
            __asm
            {
                mov eax, pInfo;
                mov eax, [eax + obj_type4_pos_x_offset1];
                mov ecx, eax;

                cmp ecx, 0;
                jnz libJmp4;
                xor eax, eax;
                leave;
                ret;
                libJmp4:
                mov eax, [ecx + obj_type4_pos_x_offset2];

                mov ebx, fpos;
                mov [ebx]fpos.x, eax;

                mov eax, temp1;
                mov eax, [ecx + eax];
                mov [ebx]fpos.y, eax;

                mov eax, temp2;
                mov eax, [ecx + eax];
                mov [ebx]fpos.z, eax;

            }
        }
        else if(type == 0x90)
        {
            sPosition spos;
            __asm
            {
                mov edx, pInfo;
                mov eax, [edx + 0x2A];

				cmp eax, 0;
				jnz libJmp90;
				xor eax, eax;
				leave;
				ret;
libJmp90:
                lea ebx, spos;
                mov [ebx]spos.x, ax;

                mov eax, [edx + 0x2c];
                mov [ebx]spos.y, ax;

                mov eax, [edx + 0x2e];
                mov [ebx]spos.z, ax;
            }

            ShortPosToFloatPos(spos, *fpos);
        }
        else if(type == 1 || type == 2)
        {

            __asm
            {
                mov eax, pNode;
                mov edx, [eax]ObjectNode.ObjAddress;
                mov edx, [edx+0x14]

                mov eax, [edx + 0x1A8];

				cmp eax, 0;
				jnz libJmp12;
				xor eax, eax;
				leave;
				ret;
libJmp12:
                mov ebx, fpos;
                mov [ebx]fpos.x, eax;

                mov eax, [edx + 0x1ac];
                mov [ebx]fpos.y, eax;

                mov eax, [edx + 0x1b0];
                mov [ebx]fpos.z, eax;
            }
        }

    }
    __except(1)
    {
        TRACE(_T("获取玩家坐标失败"));
        return FALSE;
    }

    return TRUE;
}

//获得对象的名字
//参数1: 对象的索引
wchar_t* Gamecall::GetObjectNameByIndex(int index)
{
    return _GetObjectNameByIndex(index);
    //return (wchar_t*)sendcall(id_msg_GetObjectNameByIndex, (LPVOID)index);
}


//获得对象的名字
//参数1: 对象的索引
wchar_t* Gamecall::_GetObjectNameByIndex(int index)
{

    if(index <= 0) return NULL;

    wchar_t* name = NULL;
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
        TRACE(_T("参数 index = %d"), index);
        TRACE(FUNCNAME);
    }

    return name;
}


//获取对象的血量
//参数1: 对象地址
int Gamecall::GetObjectTid(DWORD pObjAddress)
{
    if(pObjAddress < 0x3000000)
    {
        return 0;
    }


    int tid;

    __try
    {
        __asm
        {
            mov eax, pObjAddress;
            mov eax, [eax + Offset_Object_UK];
            mov tid, eax;
        }
    }
    __except(1)
    {
		_ASSERTE(FALSE);
        tid = 0;
    }

    return tid;
}

//获取对象的血量
//参数1: 对象地址
int Gamecall::GetObjectHP(DWORD pObjAddress)
{
    if(pObjAddress < 0x3000000)
    {
        return 0;
    }
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


//对象等级
int Gamecall::GetObjectLevel(DWORD pObjAddress)
{
    if(pObjAddress < 0x3000000)
    {
        return 0;
    }

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
    _ASSERTE(adress != NULL);
    _ASSERTE(adrewss != 0);

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
int Gamecall::_Attack(int id)  //技能攻击  传入的是技能ID
{
    _ASSERTE(id != 0);


    char bRet;
    __try
    {
        __asm
        {
            mov eax, obj_enum_base;
            mov eax, [eax];
            mov eax, [eax + attack_offset1];
            mov eax, [eax + attack_offset2];
            mov esi, [eax + attack_offset3];
            push id;
            push esi;
            mov eax, attack_call;
            call eax;
            mov bRet, al;
        }
    }
    __except(1)
    {
        TRACE(FUNCNAME);
    }
    return bRet;
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

    _ASSERTE(Addr != NULL);
    return Addr;
}

//当前线路是否有效
BOOL Gamecall::isHaveXianlu(int index)
{
    _ASSERTE(index != 0);


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
    _ASSERTE(adress != 0);
    _ASSERTE(adress1 != 0);


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
    _ASSERTE(pBarAddr != 0);

    if(pBarAddr == NULL)
    {
        return NULL;
    }

    wchar_t* name = NULL;
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
        TRACE(FUNCNAME);
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

    _ASSERTE(name != NULL);


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

            PARAM_2 temp;
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

int Gamecall::GetGoodsColor(DWORD m_Adress)  //获取物品的颜色
{
    _ASSERTE(m_Adress != 0);

    DWORD Adress = 0;
    __try
    {
        Adress = (DWORD)ReadByte(ReadDWORD(m_Adress + bag_item_color_offset1) + bag_item_color_offset2);
    }
    __except(1)
    {
        TRACE(FUNCNAME);
    }

    return Adress;
}


DWORD Gamecall::GetGoodsBiDui(DWORD m_Adress)  //获取物品的比对
{
    _ASSERTE(m_Adress != 0);

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
    _ASSERTE(m_Adress != 0);

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
    _ASSERTE(m_Adress != 0);

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
    _ASSERTE(m_Adress != 0);

    DWORD dwRet = 0;
    __try
    {
        dwRet = (DWORD)ReadWORD(m_Adress + wuqi_xp_cur_offset);
    }
    __except(1)
    {
        TRACE(FUNCNAME);
        return 0;
    }
    return dwRet;
}

char Gamecall::GetGoodsIsFengYin(DWORD m_Adress)  //获取物品是否封印
{
    _ASSERTE(m_Adress != 0);

    char Adress = 0;
    __try
    {
        Adress = ReadByte(ReadDWORD(m_Adress + 0x0C) + 0x0C);
    }
    __except(1)
    {
        TRACE(FUNCNAME);
        return -1;
    }
    return Adress;
}


DWORD Gamecall::GetBaGuaGeZiShu(DWORD m_Adress)  //获取八卦格子数
{
    _ASSERTE(m_Adress != 0);


    DWORD dwRet = 0;
    __try
    {
        dwRet = (DWORD)ReadByte(ReadDWORD(m_Adress + bag_item_bagua_pos_offset1) + bag_item_bagua_pos_offset2);
    }
    __except(1)
    {
        TRACE(FUNCNAME);
        return -1;
    }
    return dwRet;
}




//获取角色装备遍历Base
DWORD Gamecall::GetBodyInfoBase(DWORD pBase)
{
    _ASSERTE(pBase != 0);

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
    _ASSERTE(pBase != 0);

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


BOOL Gamecall::GetAllBaGuaToVector(BagVector& BaGuaVec)
{
    BagVector AllGoods;
    GetAllGoodsToVector(AllGoods);

    for(DWORD i = 0; i < AllGoods.size(); i++)
    {

        if(AllGoods[i].m_Info >= 8 && AllGoods[i].m_Info <= 16)
        {
            BaGuaVec.push_back(AllGoods[i]);
        }
    }


    return TRUE;
}



BOOL Gamecall::GetSpecBaGuaToVector(wchar_t* name, BagVector& BaGuaVec)
{
    _ASSERTE(name != 0);

    BagVector AllGoods;
    GetAllGoodsToVector(AllGoods);

    for(DWORD i = 0; i < AllGoods.size(); i++)
    {
        if(wcscmp(name, AllGoods[i].name) == 0)
            BaGuaVec.push_back(AllGoods[i]);
    }

    return TRUE;
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
    if(pAddr < 0x3000000)
    {
        TRACE(_T("GetGoodsBase问题"));
        return 0;
    }

    _ASSERTE(pAddr != 0);

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

    _ASSERTE(pAddr != 0);

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
    _ASSERTE(pAddr != 0);

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

DWORD Gamecall::GetGoodsType(DWORD pAddr)  //获取物品的类型
{

    _ASSERTE(pAddr != 0);

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
DWORD Gamecall::GetGoodsPos(DWORD pAddr)
{

    _ASSERTE(pAddr != 0);

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
        TRACE(FUNCNAME);
    }
    return nums;
}


//获取物品的数量
DWORD Gamecall::GetGoodsNum(DWORD pAddr)
{
    _ASSERTE(pAddr != 0);

    DWORD nums = 0;
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

DWORD Gamecall::GetGoodsDur(DWORD pAddr)  //获取物品的持久
{
    _ASSERTE(pAddr != 0);

    DWORD dwRet = 0;
    __try
    {
        __asm
        {
            mov eax, pAddr;
            mov eax, [eax + bag_item_durability_offset];

            movzx eax, al;
            mov dwRet, eax;
        }
    }
    __except(1)
    {
        TRACE(FUNCNAME);
    }

    return dwRet;
}

DWORD Gamecall::GetGoodsLV(DWORD pAddr)  //获取物品的等级
{
    _ASSERTE(pAddr != 0);

    DWORD dwRet;
    __try
    {
        __asm
        {
            mov eax, pAddr;
            mov eax, [eax + bag_item_level_offset1];
            mov eax, [eax + bag_item_level_offset2];

            movzx eax, al;
            mov dwRet, eax;
        }
    }
    __except(1)
    {
        TRACE(FUNCNAME);
    }

    return dwRet;
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


int Gamecall::GetObjectSY(DWORD pObjAddress)  // 环境对象的索引1
{
    if(pObjAddress < 0x3000000)
    {
        return 0;
    }

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

    _ASSERTE(m_Adress != 0);


    BYTE jd = 0;
    __try
    {
        _asm
        {
            mov eax, m_Adress;
            mov eax, [eax+obj_type4_youshan_offset1];
            mov eax, [eax+obj_type4_youshan_offset2];
            mov jd, al;
        }
    }
    __except(1)
    {
        TRACE(FUNCNAME);
    }


    return (DWORD)jd;
}


int Gamecall::GetObjectSY12(DWORD pAddr)  // 环境对象的索引12
{
    if(pAddr < 0x3000000)
    {
        return 0;
    }


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
    __except(1)
    {
        TRACE(FUNCNAME);
    }

    return Adress;
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

    if(bRet1 == -1 && bRet2 == -1 &&  bRet3 == -1)
        return false;
    else
        return TRUE;


    return TRUE;
}



//转坐标2到坐标1
void Gamecall::ShortPosToFloatPos(sPosition& spos, fPosition& fpos)
{

    fpos.x = (float)(spos.x * 4);
    fpos.y = (float)(spos.y * 4);
    fpos.z = (float)(spos.z * 4);
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
    if(theApp.m_hGameWnd != NULL)
    {
        PostMessage(theApp.m_hGameWnd, WM_KEYDOWN, vk, 0);
        //  PostMessage(theApp.m_hGameWnd, WM_KEYUP, vk, 0xc0000000);
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


//{功能操作}
//用来捡物?  类似控件操作
int Gamecall::_Operation(DWORD Param1, DWORD Param2)
{

    __try
    {

        __asm
        {
            push Param2

            mov  eax, Offset_Game_Base
            mov  eax, dword ptr ds:[eax]
            mov  eax, dword ptr ds:[eax+ Offset_ShorCutPanel_Offset1]
            mov  edi, dword ptr ds:[eax+ Offset_ShorCutPanel_Offset2+ Offset_ShorCutPanel_Offset3]
            add  edi, Offset_ShorCutPanel_Offset4
            sub  edi, Offset_ShorCutPanel_Offset5
            add  edi, Offset_ShorCutPanel_Offset6

            mov  ecx, Param1
            mov  edx, edi
            mov eax, FUNC_OPERATION;
            call eax;
        }

    }
    __except(1)
    {
        TRACE(FUNCNAME);
    }

    return 0;
}

//判断是否是尸体
BOOL Gamecall::isDeadBody(DWORD pAddr)
{
    DWORD type = GetObjectType(pAddr);
    if(type == 0xb0) return TRUE;

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


//5 表示读条 1 刚进游戏 2 选择角色界面 3游戏内
//当前读条状态
int Gamecall::isLoadingMap()
{

    char value =0;

    if(ReadDWORD(is_logingame_base) == NULL)
    {
        TRACE(_T("is_logingame_base-error"));
        return 0;
    }
    _try
    {
        __asm
        {
            mov eax, is_logingame_base;
            mov eax, [eax];
            mov eax, [eax + is_logingame_offset1];
			cmp eax, 0;
			jnz libJmpoffset1;
			xor eax, eax;
			leave;
			ret;
libJmpoffset1:

            mov eax, [eax + is_logingame_offset2];
			cmp ecx, 0;
			jnz libJmpoffset2;
			xor eax, eax;
			leave;
			ret;
libJmpoffset2:
            mov eax, [eax + is_logingame_offset3];
            mov value, al;
        }
    }
    _except(1)
    {
        TRACE(FUNCNAME);
    }

    return (int)value;
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
    _ASSERTE(uiAddr != 0);

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
        TRACE(FUNCNAME);
    }

    return value;
}

//通过类型取得索引
int Gamecall::GetIndexByType(DWORD pObjAddress)
{
    if(pObjAddress < 0x3000000)
    {
        return 0;
    }


    int index = -1;

    __try
    {
        BYTE type = GetObjectType(pObjAddress);

        if(type == 0x4)
        {
            index = GetObjectSY(pObjAddress);
        }
        else if(type == 0x20)  //资源
        {
            index = GetObjectSY12(pObjAddress);
        }
        else if(type == 0x90)   //尸体
        {
            index = GetObjectSy_90(pObjAddress);
        }

        //B0:{地面物品}
    }
    __except(1)
    {
        TRACE(FUNCNAME);
        _ASSERTE(index == -1);
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
        _asm
        {
            mov eax, m_Adress;
            mov eax, [eax+obj_type4_youshan_offset4]; //1是怪物 0是NPC
            mov jd, al;
        }
    }
    __except(1)
    {
        TRACE(FUNCNAME);
    }


    return (DWORD)jd;
}



DWORD Gamecall::m_Get110(DWORD m_Adress)  //对象的110
{
    BYTE jd = 0;
    __try
    {
        _asm
        {
            mov eax, m_Adress;
            mov eax, [eax+obj_type4_youshan_offset1];
            mov eax, [eax+obj_type4_youshan_offset3];
            mov jd, al;
        }
    }
    __except(1)
    {
        TRACE(FUNCNAME);
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

    }
    __except(1)
    {
        TRACE(FUNCNAME);
    }

    return (bLoading == 1);
}


void Gamecall::FenJie(_BAGSTU& bag)
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
    __except(1)
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
    _ASSERTE(name != NULL);

    BagVector BagVector;
    if(GetGoodsFromBagByName(name, BagVector))
    {
        sendcall(id_msg_ChiYao, &BagVector[0]);
    }
    else
    {
        TRACE(_T("%s: 没有在背包中找到这个物品: %s"), FUNCNAME, name);
    }

	
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

    DWORD addr = 0;
    GetUIAddrByName(L"OptionPanel", &addr);
    _ASSERTE(addr != 0);

    UIOperator uiop;
    uiop.c5 = *(DWORD*)(addr + mouse_mode_class_c5);
    uiop.pAddr = (DWORD*)addr;

    sendcall(id_msg_JingDianMoShi, &uiop);
}

//等待进入游戏
bool Gamecall::WaitPlans(int inMaxTime)
{

    DWORD dwCount = inMaxTime / 3;
    for(int i = 0; i < dwCount; i++)
    {
        if(isLoadingMap() == 3)
        {
            return true;
        }

        Sleep(3000);
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
    _ASSERTE(playerdata != 0);
    if(playerdata < 0x3000000)
    {
        TRACE("取死亡状态有问题");
    }

    __try
    {
        __asm
        {
            mov eax, playerdata;
            mov eax, [eax + player_dead_status_offset3];
            mov value, al;
        }

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
        BagVector item;
        if(GetGoodsFromBagByName(itemName, item))
        {
            //喝
            //if(sendcall(id_msg_isYaoPingCD, &item[0]) == 1)
            //{
            //    sendcall(id_msg_ChiYao, &item[0]);
            //    return 1;
            //}
            //else
            //{
            //    return 4;
            //}
			sendcall(id_msg_ChiYao, &item[0]);
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
    if(pObjAddress < 0x3000000)
    {
        return 0;
    }

    DWORD type = GetObjectType(pObjAddress);
    if(type == 1 || type == 2)
    {
        return (wchar_t*)ReadDWORD(pObjAddress + 0x8c);
    }
    else if(type > 2)
    {
        return GetObjectNameByIndex(GetIndexByType(pObjAddress));
    }

    return NULL;
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

    if(goods.m_Base < 0x3000000)
    {
        TRACE(_T("ChiYao有问题"));
        return;
    }
    DWORD pAddr = goods.m_Base;
    _try
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
    _except(1)
    {
        TRACE(FUNCNAME);
    }
}



void Gamecall::PickupDeadbody(DWORD id1, DWORD id2)
{
    _ASSERTE(id1 != 0);
    _ASSERTE(id2 != 0);

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
        if(status == 5) return TRUE;
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
void Gamecall::GetAllObjectToVector(ObjectNode* pNote, ObjectVector& AllObject)
{
    _ASSERTE(pNote != NULL);

    __try
    {
        if(pNote->end == 1) return;

        //加到vector中
        AllObject.push_back(pNote);



        GetAllObjectToVector(pNote->left, AllObject);
        GetAllObjectToVector(pNote->right, AllObject);
    }
    __except(1)
    {
        TRACE(FUNCNAME);
    }
}

void Gamecall::GetRangeTaskItemToVectr(ObjectVector& TastItemVector, DWORD range)
{
    //这个函数简写了,  直接从范围对象中遍历的过滤
    ObjectVector RangeObject;
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
//类型是4 并且有名字 并且xxx
BOOL Gamecall::isCanKill(ObjectNode* pNode)
{
    _ASSERTE(pNode != NULL);

    //再加一个类型是4的过滤
    if(GetObjectType(pNode->ObjAddress) != 0x4) return FALSE;

    if(GetObjectName(pNode->ObjAddress) == FALSE) return FALSE;

    //过滤
    BOOL bCanKill = FALSE;
    //if(m_Get11C(pNode->ObjAddress) == 1)
    //{
    //    bCanKill = TRUE;
    //}
    //else
    //{
    //if(m_Get110(pNode->ObjAddress) == 1)
    //{
    //    if(m_Get2E4(pNode->ObjAddress) != 0)
    //        bCanKill = TRUE;
    //}
    //}

    return bCanKill;
}

//遍历距离范围内的所有怪物到容器中
//有坐标 有名字 能杀
void Gamecall::GetRangeMonsterToVector(ObjectNode* pNode, DWORD range, ObjectVector& MonsterVec)
{
    __try
    {
        _ASSERTE(pNode != NULL);


        if(pNode->end == 1) return;

        //有坐标就比对坐标, 没有坐标就直接放进去
        if(pNode != NULL)
        {

            if(GetObjectName(pNode->ObjAddress))
            {
                if(GetObjectType(pNode->ObjAddress) == 0x4)
                {
                    static fPosition fpos;
                    if(GetObjectPos(pNode, &fpos))
                    {
                        static fPosition fmypos;
                        GetPlayerPos(&fmypos);

                        if(fpos.x != 0 && fpos.y != 0 && fpos.z != 0)
                        {
                            if((DWORD)CalcC(fmypos, fpos) <= range)
                            {
                                MonsterVec.push_back(pNode);
                            }
                        }
                    }
                }
            }
        }


        GetRangeMonsterToVector(pNode->left, range, MonsterVec);
        GetRangeMonsterToVector(pNode->right, range, MonsterVec);
    }
    __except(1)
    {
        TRACE(FUNCNAME);
    }
}

void Gamecall::GetRangeMonsterToVector(ObjectNode* pNode, DWORD range, ObjectVector& MonsterVec, fPosition& fmypos)
{
    __try
    {
        _ASSERTE(pNode != NULL);

        if(pNode->end == 1) return;

        //有坐标就比对坐标, 没有坐标就直接放进去
        if(pNode != NULL)
        {

            if(GetObjectName(pNode->ObjAddress))
            {
                if(GetObjectType(pNode->ObjAddress) == 0x4)
                {
                    static fPosition fpos;
                    if(GetObjectPos(pNode, &fpos))
                    {
                        if(fpos.x != 0 && fpos.y != 0 && fpos.z != 0)
                        {
                            if((DWORD)CalcC(fmypos, fpos) <= range)
                            {
                                MonsterVec.push_back(pNode);
                            }
                        }
                    }
                }
            }
        }


        GetRangeMonsterToVector(pNode->left, range, MonsterVec, fmypos);
        GetRangeMonsterToVector(pNode->right, range, MonsterVec, fmypos);
    }
    __except(1)
    {
        TRACE(FUNCNAME);
    }
}

//所有遍历都只会遍历到有坐标的和有名字的
//有坐标
void Gamecall::GetRangeObjectToVector(ObjectNode* pNote, DWORD range, ObjectVector& RangeObject)
{
    __try
    {
        if(pNote->end == 1) return;

        //有坐标就比对坐标, 没有坐标就直接放进去
        fPosition fpos;
        if(GetObjectPos(pNote, &fpos))
        {
            static fPosition fmypos;
            GetPlayerPos(&fmypos);

            if(fpos.x != 0 && fpos.y != 0 && fpos.z != 0)
            {
                if((DWORD)CalcC(fmypos, fpos) <= range)
                {
                    RangeObject.push_back(pNote);
                }
            }
        }


        GetRangeObjectToVector(pNote->left, range, RangeObject);
        GetRangeObjectToVector(pNote->right, range, RangeObject);
    }
    __except(1)
    {
        TRACE(FUNCNAME);
    }
}


//遍历距离范围内掉落的战利品对象到容器中
//参数1: 范围, 单位: 游戏内的 米
void Gamecall::GetRangeLootObjectToVector(DWORD range, ObjectVector& LootVec)
{

    //这个函数简写了,  直接从范围对象中遍历的过滤
    ObjectVector RangeObject;
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
                {
                    LootVec.push_back(pNode);
                }
            }
        }
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


ObjectNode* Gamecall::GetObjectByName(const wchar_t szName[], DWORD range)
{

    _ASSERTE(szName != NULL);

    ObjectVector RangeObject;
    if(range == 0)
    {
        GetAllObjectToVector(GetObjectBinTreeBaseAddr(), RangeObject);
    }
    else
    {
        GetRangeObjectToVector(GetObjectBinTreeBaseAddr(), range, RangeObject);
    }

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
        if(name == NULL) continue;

        if(wcscmp(name, szName) == 0) return RangeObject[i];
    }

    return NULL;
}

void Gamecall::_GetUItoVector(Tree* Base, std::vector<Tree*>& Allui)
{

    _ASSERTE(Base != NULL);

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
    _ASSERTE(Base != NULL);

    //PARAM_GUANSHANGDIAN temp;
    //temp.argv1 = (DWORD)Base;
    //temp.argv2 = (DWORD)&Allui;
    //sendcall(id_msg_GetUItoVector, &temp);
    _GetUItoVector(Base, Allui);
}



//通过名称取得这个ui的地址
//取得攻击面板的地址
//参数1: bar的二叉树起始节点地址
//参数2: 查找的UI名, 根据比对名返回UI的数据地址
//参数3, 传出ui的数据地址
void Gamecall::GetUIAddrByName(wchar_t* name, DWORD* pUIAddr)
{
    _ASSERTE(name != NULL);
    _ASSERTE(pUIAddr != NULL);

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
    DWORD rs;
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
            mov rs, eax;

        }
        if(rs > 0)
        {
            JingYan = ReadDWORD(rs + 0x10);
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
    _ASSERTE(Adress != 0);

    DWORD JingYan;
    DWORD rs;
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
            mov rs, eax;

        }
        if(rs > 0)
        {
            JingYan = ReadDWORD(rs + 0x24);
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
    _ASSERTE(Adress != 0);

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

    _try
    {
        BagBuff.m_ID      =   GetGoodsID(BagBuff.m_Base);                //获取物品的ID
        if(BagBuff.m_ID == UINT_MAX)
            return FALSE;

        BagBuff.m_NameID  =   GetGoodsNameID(BagBuff.m_Base);            //获取物品的名字ID


        BagBuff.name   =    GetObjectNameByIndex(BagBuff.m_NameID);
        if(BagBuff.name == NULL) return FALSE;


        BagBuff.m_Type    =   GetGoodsType(BagBuff.m_Base);              //获取物品的类型
        BagBuff.m_Info    =   GetGoodsPos(BagBuff.m_Base);              //获取物品的所在格子数
        BagBuff.m_Num     =   GetGoodsNum(BagBuff.m_Base);               //获取物品的数量
        BagBuff.CurDur =   GetGoodsDur(BagBuff.m_Base);           //获取物品的持久
        BagBuff.m_LV      =   GetGoodsLV(BagBuff.m_Base);               //获取物品的等级



        BagBuff.m_BagLeiXing = GetGoodsBagInfo(BagBuff.m_Base);  //获取物品的背包类型
        //BagBuff.m_CaoZuoType  = GetGoodsYouJianType(BagBuff.m_BagLeiXing, BagBuff.m_Info); //获取背包物品右键操作类型


        BagBuff.m_YanSe      =   GetGoodsColor(BagBuff.m_Base);  //获取物品的颜色
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
        //if(BagBuff.m_CaoZuoType == 0x0E)
        //{
        //    //TRACE("此物品是未解封的装备  总各数 %X,首地址 %X 物品右键操作类型  %X",GridNum,BagBuff.m_Base,BagBuff.m_CaoZuoType);
        //}
        //else if(BagBuff.m_CaoZuoType == 0x0F)
        //{
        //    //TRACE("此物品是未解封的盒子  总各数 %X,首地址 %X 物品右键操作类型  %X",GridNum,BagBuff.m_Base,BagBuff.m_CaoZuoType);
        //}
        else
        {
            //TRACE("总各数 %X,首地址 %X 物品右键操作类型  %X",GridNum,BagBuff.m_Base,BagBuff.m_CaoZuoType);
        }


        /*
        改个地方,需要强化时再取信息.
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
        }*/


        if(BagBuff.m_Type == 4)
        {
            BagBuff.m_BaGuaGeZiShu = GetBaGuaGeZiShu(BagBuff.m_Base);  //获取八卦格子数
        }
    }
    _except(1)
    {
        TRACE(FUNCNAME);
        return FALSE;
    }

    return TRUE;
}

void Gamecall::_GetAllGoodsToVector(BagVector& RangeObject)
{
    DWORD BagbodyAdress = 0;
    DWORD BagAdress = 0;
    int GridNum = 0;
    BAGSTU aGoods;

    BagbodyAdress = GetBagbodyInfoBase();                                 //获取背包身上装备仓库遍历Base
    BagAdress = GetBagInfoBase(BagbodyAdress);                        //获取背包遍历Base
    GridNum = GetBagGridNumber();                        //当前背包的总的格子数

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
                    aGoods.m_Num = (aGoods.m_Num == 0 ? 1 : aGoods.m_Num);

                    RangeObject.push_back(aGoods);
                }
            }

        }
        __except(1)
        {
            TRACE(FUNCNAME);
        }
    }
}


//遍历背包数据到容器
void Gamecall::GetAllGoodsToVector(BagVector& RangeObject)
{
    _GetAllGoodsToVector(RangeObject);
}


void Gamecall::_GetAllBodyEquipToVector(BagVector& RangeObject)
{
    DWORD BagbodyAdress = 0;
    DWORD BagAdress = 0;
    int Gridnum = 0;
    _BAGSTU aGoods;

    BagbodyAdress = GetBagbodyInfoBase();
    BagAdress = GetBodyInfoBase(BagbodyAdress);
    Gridnum = GetBagGridNumber();//0x10;//
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
void Gamecall::GetAllBodyEquipToVector(BagVector& RangeObject)
{
    sendcall(id_msg_GetAllBodyEquipToVector, &RangeObject);
}

void Gamecall::GetStrikeToVector(StrikeVector& RangeObject)
{

    DWORD PPTR = ReadDWORD(Offset_Game_Base);
    PPTR = ReadDWORD(PPTR + Offset_Skill_Offset1);
    PPTR = ReadDWORD(PPTR + Offset_Skill_Offset2);

    //{技能指针}
    PPTR = ReadDWORD(PPTR + Offset_Skill_Offset3 - Offset_Skill_Offset4 + Offset_Skill_Offset5 + Offset_Skill_Skill);
    _ASSERTE(PPTR != 0);


    //{技能首地址}
    DWORD PSkillBegin = ReadDWORD(PPTR + Offset_Skill_PBSkill);
    _ASSERTE(PSkillBegin != 0);


    //{技能尾地址}
    DWORD PSkillEnd = ReadDWORD(PPTR + Offset_Skill_PESkill);
    _ASSERTE(PSkillEnd != 0);

    DWORD dwCount = (PSkillEnd - PSkillBegin) / 4;

    if(dwCount < 0 || dwCount > 20)
    {
        return;
    }


    STRIKEINFO stJn;

	int i;
    for(i = 0; i < dwCount; i++)
    {

        //{信息指针}
        DWORD PInfo = ReadDWORD(PSkillBegin + i * 4);
        _ASSERTE(PInfo > 0);

        stJn.id = ReadDWORD(PInfo + Offset_Skill_Id);
        if(stJn.id > 0)
        {
            stJn.iType = ReadByte(PInfo + Offset_Skill_Type);

            if(ReadDWORD(PInfo + Offset_Skill_NameLen) >= 0xf)
            {
                stJn.name = (wchar_t*)ReadDWORD(PInfo + Offset_Skill_Name);
                _ASSERTE(stJn.name != NULL);
            }
            else
            {
                stJn.name = (wchar_t*)(PInfo + Offset_Skill_Name);
                _ASSERTE(stJn.name != NULL);
            }

            stJn.bCD = (ReadDWORD(PInfo + Offset_Skill_CD) == 0);

            stJn.bAviable = (ReadDWORD(PInfo + Offset_Skill_AState) == 0);


            stJn.iIndex = i;
            stJn.iKeyCode = 0xff; //暂时没用
            RangeObject.push_back(stJn);
        }

    }



    PPTR = ReadDWORD(Offset_Game_Base);
    PPTR = ReadDWORD(PPTR + Offset_Skill_Offset1);
    PPTR = ReadDWORD(PPTR + Offset_Skill_Offset2);

    //{技能指针}
    PPTR = ReadDWORD(PPTR + Offset_Skill_Offset3 - Offset_Skill_Offset4 + Offset_Skill_Offset5 + Offset_Skill_ASkill);
    _ASSERTE(PPTR != 0);


    //{技能首地址}
    PSkillBegin = ReadDWORD(PPTR + Offset_Skill_PBASkill);
    _ASSERTE(PSkillBegin != 0);


    //{技能尾地址}
    PSkillEnd = ReadDWORD(PPTR + Offset_Skill_PEASkill);
    _ASSERTE(PSkillEnd != 0);

    dwCount = (PSkillEnd - PSkillBegin) / 4;

    if(dwCount < 0 || dwCount > 20)
    {
        return;
    }


    for(int i = 0; i < dwCount; i++)
    {

        //{信息指针}
        DWORD PInfo = ReadDWORD(PSkillBegin + i * 4);
        _ASSERTE(PInfo > 0);

        stJn.id = ReadDWORD(PInfo + Offset_Skill_Id);
        if(stJn.id > 0)
        {
            stJn.iType = ReadByte(PInfo + Offset_Skill_Type);

            if(ReadDWORD(PInfo + Offset_Skill_NameLen) >= 0xf)
            {
                stJn.name = (wchar_t*)ReadDWORD(PInfo + Offset_Skill_Name);
                _ASSERTE(stJn.name != NULL);
            }
            else
            {
                stJn.name = (wchar_t*)(PInfo + Offset_Skill_Name);
                _ASSERTE(stJn.name != NULL);
            }

            stJn.bCD = (ReadDWORD(PInfo + Offset_Skill_CD) == 0);

            stJn.bAviable = (ReadDWORD(PInfo + Offset_Skill_AState) == 0);

            stJn.iIndex = i;
            stJn.iKeyCode = 0xff; //暂时没用
            RangeObject.push_back(stJn);
        }

    }


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
    return SendMessage(theApp.m_hGameWnd, WM_CUSTOM_GCALL, id, (LPARAM)pParam);
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


    _try
    {
        __asm
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
            mov eax, [eax+ yao_cd_offset7];
            mov eax, [eax+ yao_cd_offset8];
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
    _except(1)
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
    if(mypos.x == pos.x && mypos.y == pos.y)
    {
        TRACE(_T("转视角时, 目标和我是重叠的"));
        //这里不解决重叠， 重叠让走路解决
        RandomStep(60);
        //直接退
        //return;
    }

    //TRACE(_T("当前怪物坐标,%d,%d,%d"),(int)pos.y,(int)pos.x,(int)pos.z);


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

    //TRACE(_T("计算出角度:%d"),(int)gameangle);

    Turn((int)gameangle);
}


//捡起尸体
//范围默认500
BOOL Gamecall::PickupDeadbody(DWORD range)
{
    ObjectVector RangeObject;
    GetRangeObjectToVector(GetObjectBinTreeBaseAddr(), range, RangeObject);


    ObjectNode* pMaxNode = NULL;


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

    PARAM_2 temp;
    temp.argv1 = pMaxNode->id;
    temp.argv2 = pMaxNode->id2;
    sendcall(id_msg_PickupDeadbody, &temp);

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
        TRACE(_T("销毁物品时发生错误"));
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

    Stepto(fmypos, 5, 10, 1000, TRUE);
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
    _ASSERTE(FALSE);
}

void Gamecall::Attack(int id)
{
    int cs = 0;
    int flag = 0;
    while(flag == 0)
    {
        if(cs > 10)
        {
            break;
        }
        flag = sendcall(id_msg_attack, (LPVOID)id);
        if(flag)
        {
            //TRACE(_T("技能ID:%d,技能执行返回%d"), id, flag);
            break;
        }
        //TRACE(_T("技能ID:%d,技能执行返回%d"), id, flag);
        cs++;
        Sleep(100);
    }
}


//走向某个对象
BOOL Gamecall::Step(ObjectNode* pNode)
{
    _ASSERTE(pNode != NULL);
    fPosition fpos;
    if(GetObjectPos(pNode, &fpos))
    {
        Step(fpos.x, fpos.y, fpos.z);
        return TRUE;
    }
    else
    {
        TRACE(_T("Gamecall::Step(ObjectNode* pNode)--error"));
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
    _ASSERTE(pNode != NULL);
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
        if(wcsstr(name, L"Dummy") != NULL)
        {
            return FALSE;
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
            Adress = ReadDWORD(ReadDWORD(m_Adress + 0x14) + 0x180);
        if(Adress == 0x400 || Adress == 4 || Adress == 0x22 || Adress == 0x1 || Adress == 0xD)
            State = TRUE;
        else
            State = FALSE;
        /*
        $1:Result.nUnusual:='眩晕';
        $4:Result.nUnusual:='倒地';
        $6:Result.nUnusual:='频死';
        $B:Result.nUnusual:='眩晕';
        $D:Result.nUnusual:='倒地';
        $21:Result.nUnusual:='疗伤';
        $22:Result.nUnusual:='格挡';
        $400:Result.nUnusual:='倒地';
        */
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

wchar_t* Gamecall::GetExperienceName(DWORD ID)
{
    wchar_t* name = NULL;
    DWORD rs;
    __try
    {
        __asm
        {
            mov eax, obj_name_call_base;
            mov eax, [eax];
            mov ecx, [eax+obj_name_call_offset1]
            mov edx, [ecx]
            mov edx, [edx+obj_name_call_offset2]
            push 0;
            mov ebx, ID;
            push ebx;
            call edx;
            mov rs, eax;
        }
        if(rs>0)
        {
            rs = ReadDWORD(rs + 0x18);
            if(rs > 0)
            {
                name = ReadStr(rs);
            }
        }
    }
    __except(1)
    {
        TRACE(_T("获取经验名字错误"));
    }


    return name;
}


DWORD Gamecall::GetExperienceNameID(DWORD ID)
{
    DWORD ID1 = 0;
    DWORD rs = 0;
    __try
    {
        __asm
        {
            mov eax, obj_name_call_base;
            mov eax, [eax];
            mov ecx, [eax+Experience_status_offset2] //经验效果的二级偏移
            mov edx, [ecx]
            mov edx, [edx+obj_name_call_offset2]
            push 0;
            mov ebx, ID;
            push ebx;
            call edx;
            mov rs, eax;
        }
        if(rs > 0)
        {
            ID1 = ReadDWORD(rs + 0x14);
        }
    }
    __except(1)
    {
        TRACE(_T("获取经验名字ID错误"));
        return NULL;
    }
    return ID1;
}

DWORD Gamecall::GetExperienceNameID_SY(int i, DWORD m_adress)
{
    DWORD Adress = 0;
    __try
    {
        if(m_adress != 0)
        {
            Adress = ReadDWORD(m_adress + i * Experience_status_offset3 + Experience_status_offset4) ;   //C0是三级偏移   1C是四级偏移
        }
    }
    __except(1)
    {
        TRACE(_T("获取名字ID结构的索引错误"));
        return -1;
    }
    return Adress;
}

BOOL Gamecall::GetPlayExperienceStatusName(DWORD m_adressA, wchar_t* ExperienceName)
{
    wchar_t* name = {0};
    DWORD pos = 0;
    DWORD pos1 = 0;
    DWORD SY = 0;
    DWORD ID = 0;
    pos = ReadDWORD(m_adressA + Experience_status_offset1 + 0x4);

// TRACE1("pos===%d",pos);

    pos1 = ReadDWORD(m_adressA + Experience_status_offset1); //经验效果的一级偏移

// TRACE1("pos1===%d",pos1);

    if(pos > 0)
    {
        for(int i = 0; i < 10; i++)
        {
            SY = GetExperienceNameID_SY(i, pos1);  //获取名字ID结构的索引
            if(SY == 0)
            {
                return false;
            }
            ID = GetExperienceNameID(SY); //获取经验名字ID
            if(ID != 0)
            {
                name =  GetExperienceName(ID); //获取经验名字
                if(wcscmp(name, ExperienceName) == 0)
                {
//                  TRACE(_T("返回true"));
                    return true;
                }
            }
        }
    }
//  TRACE(_T("返回FALSE"));
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
    ZeroMemory(&jiegou, sizeof(KONGJIAN_JIEGOU));
    jiegou.adress = (DWORD)GetUIBinTreeBaseAddr();
    jiegou.name = L"00008130.UI.Normal_10";
    jiegou.ID = 0;
    GetUiAddrByName(jiegou);

    //TRACE1("ui:%x",jiegou.adress);

    wchar_t* ExperienceName = L"???";  //这个名字就是经验药品在左边的名字

    KONGJIAN_JIEGOU jiegou2;
    ZeroMemory(&jiegou2, sizeof(KONGJIAN_JIEGOU));
    jiegou2.adress = jiegou.ID;
    jiegou2.name = ExperienceName;
    BOOL pos = FALSE;
    pos = (BOOL)sendcall(id_msg_GetPlayExperienceStatusName, &jiegou2);
    //pos =  GetPlayExperienceStatusName(jiegou.adress,str1);  //获取经验名字  参数1是UI地址  参数2 是药品的名字
    if(pos == TRUE)
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
            TRACE(_T("找到UI名:%s,找到控件地址:%d"), uiname, Addr->Adress);
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
    unsigned addr2 = (unsigned)hBsengine;
    addr = addr + 0x592D8A;
    addr1 = addr1 + 0xA412B3;//0x0A410FC--
    //addr2 = addr2 + 0xA412B3;
    //A410BB
    //A410D3
    //A410C3
    DWORD pi = 0;
    DWORD pi1 = 0;
    //DWORD pi2 = 0;

    //VirtualProtect((void*)addr,4,PAGE_EXECUTE_READWRITE ,&pi);
    //*(WORD*)(addr) = 0x0EEB;
    //VirtualProtect((void*)addr,4,pi ,&pi);
    if(flag)
    {
        if(ReadByte(addr) == 0xF3)
        {
            VirtualProtect((void*)addr, 4, PAGE_EXECUTE_READWRITE , &pi);
            *(WORD*)(addr) = 0x0EEB;//0x05EB
            VirtualProtect((void*)addr, 4, pi , &pi);
        }
        if(ReadByte(addr1) == 0xD9)
        {
            VirtualProtect((void*)addr1, 4, PAGE_EXECUTE_READWRITE , &pi1);
            *(WORD*)(addr1) = 0x01EB;
            VirtualProtect((void*)addr1, 4, pi1 , &pi1);
        }
        /*if(ReadByte(addr2) == 0xD9)
        {
            VirtualProtect((void*)addr2, 4, PAGE_EXECUTE_READWRITE , &pi2);
            *(WORD*)(addr2) = 0x01EB;
            VirtualProtect((void*)addr2, 4, pi2 , &pi2);
        }*/
    }
    else
    {
        if(ReadByte(addr1) == 0xEB)
        {
            VirtualProtect((void*)addr1, 4, PAGE_EXECUTE_READWRITE , &pi1);
            *(WORD*)(addr1) = 0x5ED9;
            VirtualProtect((void*)addr1, 4, pi1 , &pi1);
        }
        if(ReadByte(addr) == 0xEB)
        {
            VirtualProtect((void*)addr, 4, PAGE_EXECUTE_READWRITE , &pi);
            *(WORD*)(addr) = 0x0FF3;
            VirtualProtect((void*)addr, 4, pi , &pi);
        }

        /*if(ReadByte(addr2) == 0xEB)
        {
            VirtualProtect((void*)addr1, 4, PAGE_EXECUTE_READWRITE , &pi2);
            *(WORD*)(addr2) = 0x5ED9;
            VirtualProtect((void*)addr2, 4, pi2 , &pi2);
        }*/
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

int Gamecall::GetObjectSy_90(DWORD pObjAddress)
{
    if(pObjAddress < 0x3000000)
    {
        return 0;
    }
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
    //TRACE("小动画状态:%d",dtzt);
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
    __try
    {
        Adress = ReadDWORD(ReadDWORD(ReadDWORD(obj_name_call_base) + Wuqi_po10_offset1) + Wuqi_po10_offset2);
    }
    __except(1)
    {
        TRACE(_T("获取开始地址错误"));
    }
    return Adress;
}

DWORD Gamecall::GetBiJiaoShu(int i, DWORD m_adress) //获取比较数值
{

    DWORD Adress = 0;
    __try
    {
        if(m_adress != 0)
            Adress = (DWORD)ReadByte(ReadDWORD(m_adress + i * 4) + 0x30);
    }
    __except(1)
    {
        TRACE(_T("获取比较数值错误"));
    }
    return Adress;
}

DWORD Gamecall::_IsCanShu(DWORD adress, DWORD adress1) //是否是这个参数
{
    BYTE is = 0;
    if(adress == 0 || adress1 == 0)
        return -1;
    __try
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
    __except(1)
    {
        TRACE(_T("是否是这个参数出错"));
        return -1;
    }
    return (DWORD)is;
}

DWORD Gamecall::IsCanShu(DWORD adress, DWORD adress1) //是否是这个参数
{
    PARAM_2 temp;
    temp.argv1 = adress;
    temp.argv2 = adress1;
    return (DWORD)sendcall(id_msg_IsCanShu, &temp);
}


DWORD Gamecall::GetBiJiaoShu1(int i, DWORD m_adress) //获取比较数值1
{

    DWORD Adress = 0;
    __try
    {
        if(m_adress != 0)
            Adress = (DWORD)ReadByte(ReadDWORD(m_adress + i * 4) + 0x8);
    }
    __except(1)
    {
        TRACE(_T("获取比较数值1错误"));
        return -1;
    }
    return Adress;
}

DWORD Gamecall::GetBiJiaoShu2(int i, DWORD m_adress) //获取比较数值2
{

    DWORD Adress = 0;
    __try
    {
        if(m_adress != 0)
            Adress = (DWORD)ReadByte(ReadDWORD(m_adress + i * 4) + Wuqi_po10_cmp2_offset);
    }
    __except(1)
    {
        TRACE(_T("获取比较数值2错误"));
        return -1;
    }
    return Adress;
}


DWORD Gamecall::GetBiJiaoShu3(DWORD m_adress)  //获取比较数值3 这里用到的2个地址都是随便弄的，还没有固定的特征码。
{

    DWORD Adress = 0;
    __try
    {
        if(m_adress != 0)
		{
            Adress = ReadDWORD(ReadDWORD(m_adress + obj_type4_id2_offset) + obj_type4_view_offset1);
		}
    }
    __except(1)
    {
        TRACE(_T("获取比较数值3错误"));
	}

    return Adress;
}

DWORD Gamecall::GetBiJiaoShu4(int i, DWORD m_adress) //获取比较数值4
{

    DWORD Adress = 0;
    __try
    {
        if(m_adress != 0)
		{
            Adress = ReadDWORD(ReadDWORD(m_adress + i * 4) + Wuqi_po10_cmp4_offset);
		}
    }
    __except(1)
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
        value = ReadDWORD(pAddr + Play_fighting_status_offset3);
        //TRACE1("战斗状态:%d",value);
    }
    __except(1)
    {
        TRACE(_T("获得战斗状态出错"));
    }

    return (value == 1);
}


DWORD Gamecall::DuiWu_EndAdress() //遍历队伍的结束地址
{
    DWORD Adress;
    __try
    {
        _asm
        {
            mov eax, obj_enum_base;
            mov eax, [eax+0];
            mov eax, [eax+enum_party_startaddr_offset1];
            mov eax, [eax+enum_party_startaddr_offset2];
            mov eax, [eax+enum_party_startaddr_offset3];
            mov eax, [eax+enum_party_startaddr_offset5 + 4];  //遍历队伍的结束地址四级偏移
            mov Adress, eax;
        }
    }
    __except(1)
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
            mov eax, leave_party_call;
            call eax;
        }
    }
    __except(1)
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
            mov eax, [eax + invite_party_call_offset1];   // 邀请组队一级偏移
            mov eax, [eax + invite_party_call_offset2];   // 邀请组队二级偏移
            mov eax, [eax + invite_party_call_offset3];  // 邀请组队三级偏移
            push eax;
            mov eax, invite_party_call;
            call eax;

        }
    }
    __except(1)
    {
        TRACE(_T("邀请组队出错"));
    }
}

int Gamecall::GetObjectView(DWORD pObjAddress)
{
    if(pObjAddress < 0x3000000)
    {
        return 0;
    }
    WORD jd = 0;
    __try
    {
        _asm
        {
            mov eax, pObjAddress;
            mov eax, [eax+0x9a];
            mov jd, ax
        }
    }
    __except(1)
    {
        TRACE(_T("对象的角度出错"));
        return 0;
    }


    return (DWORD)jd;
}

BOOL Gamecall::GetPlayerSkillStatus()
{
    DWORD pAddr = GetPlayerDataAddr();
    WORD value = 0;


    __try
    {
        value = ReadWORD(ReadDWORD(pAddr + 0x14) + 0x80);
    }
    __except(1)
    {
        TRACE(_T("获得释放技能状态出错"));
    }

    return (value != 0xFFFF);
}

BOOL Gamecall::GetPlayerBusy()
{
    DWORD pAddr = GetPlayerDataAddr();
    DWORD value_1 = 0;
    DWORD value_2 = 0;


    __try
    {
        value_1 = ReadDWORD(ReadDWORD(pAddr + 0x14) + 0x28);
        value_2 = ReadDWORD(pAddr + 0xF8);


        if(value_1 > 0 || value_2 == 5)
        {
            return TRUE;
        }
    }
    __except(1)
    {
        TRACE(_T("获得忙碌状态出错"));
    }

    return FALSE;
}

DWORD Gamecall::DuiWu_StartAdress()
{
    DWORD Adress;
    __try
    {
        __asm
        {
            mov eax, obj_enum_base;
            mov eax, [eax+0];
            mov eax, [eax+enum_party_startaddr_offset1];
            mov eax, [eax+enum_party_startaddr_offset2];
            mov eax, [eax+enum_party_startaddr_offset3];
            mov eax, [eax+enum_party_startaddr_offset4];  //遍历队伍的结束地址四级偏移
            mov Adress, eax;
        }
    }
    __except(1)
    {
        TRACE(_T("遍历队伍的结束地址出错"));
        return 0;
    }
    return Adress;
}

BOOL Gamecall::GetPartyInfo(TeamVector& TeamInfo)
{
    DWORD StartAdress  = DuiWu_StartAdress(); //遍历队伍的开始地址
    DWORD EndAdress  = DuiWu_EndAdress(); //遍历队伍的结束地址
    DWORD count;
    DWORD C_Address;
    fPosition fmypos;
    Team team;
    //ZeroMemory(&team, sizeof(Team));
    //ZeroMemory(&fmypos, sizeof(fPosition));
    C_Address = 0;

    count = (EndAdress - StartAdress) / 4;
    if(count > 0 && count <= 6)
    {
        GetPlayerPos(&fmypos);
        for(int i = 0; i < count; i++)
        {
            C_Address = GetPartyByAddress(StartAdress, i);
            team.PAddress = C_Address;
            team.name = GetPartyName(C_Address);
            team.Channel = GetPartyChannel(C_Address);
            team.CurrLife = GetPartyCurrlife(C_Address);
            team.MaxLife = GetPartyMaxlife(C_Address);
            team.ID = GetPartyId(C_Address);
            team.ID2 = GetPartyId2(C_Address);
            team.Pos = GetPartyPos(C_Address);
            team.Angle = GetPartyAngle(C_Address);
            team.Range = CalcC(team.Pos, fmypos);
            team.LV = GetPartyLv(C_Address);
            TeamInfo.push_back(team);
            //TRACE(_T("地址:%x,人名:%s,频道:%d,当前生命:%d,最大生命:%d,ID:%x,ID2%x,面向%d,距离:%d,坐标:%d,%d,%d"),team.PAddress,team.name,team.Channel,team.CurrLife,team.MaxLife,team.ID,team.ID2,team.Angle,team.Range,team.Pos.x,team.Pos.y,team.Pos.z);
        }
        return TRUE;
    }
    return FALSE;
}

wchar_t* Gamecall::GetPartyName(DWORD PartyAddress)
{
    wchar_t* name;
    name = NULL;
    __try
    {
        if(ReadDWORD(PartyAddress + 0x7c + 0x14) >= 0xF)
        {
            name = ReadStr(ReadDWORD(PartyAddress + 0x7C));
        }
        else
        {
            name = ReadStr(PartyAddress + 0x7C);
        }
    }
    __except(1)
    {
        TRACE(_T("获取角色名字出错"));
    }
    return name;
}

DWORD Gamecall::GetPartyChannel(DWORD PartyAddress)
{
    DWORD line;
    line = NULL;
    __try
    {
        line = ReadDWORD(PartyAddress + 0x44);
    }
    __except(1)
    {
        TRACE(_T("获取角色线路出错"));
        line = 0;
    }
    return line;
}

DWORD Gamecall::GetPartyCurrlife(DWORD PartyAddress)
{
    DWORD Currlife;
    Currlife = NULL;
    __try
    {
        Currlife = ReadDWORD(PartyAddress + 0x14);
    }
    __except(1)
    {
        TRACE(_T("获取角色当前血值出错"));
    }
    return Currlife;
}

DWORD Gamecall::GetPartyMaxlife(DWORD PartyAddress)
{
    DWORD Maxlife;
    Maxlife = NULL;
    __try
    {
        Maxlife = ReadDWORD(PartyAddress + 0x28);
        Maxlife = Maxlife + ReadDWORD(PartyAddress + 0x2C);
    }
    __except(1)
    {
        TRACE(_T("获取角色最大血值出错"));
    }
    return Maxlife;
}

DWORD Gamecall::GetPartyId(DWORD PartyAddress)
{
    DWORD id;
    id = NULL;
    __try
    {
        id = ReadDWORD(PartyAddress + 0x8);
    }
    __except(1)
    {
        TRACE(_T("获取角色ID出错"));
    }
    return id;
}

DWORD Gamecall::GetPartyId2(DWORD PartyAddress)
{
    DWORD id2;
    id2 = NULL;
    __try
    {
        id2 = ReadDWORD(PartyAddress + 0xC);
    }
    __except(1)
    {
        TRACE(_T("获取角色ID2出错"));
    }
    return id2;
}

fPosition Gamecall::GetPartyPos(DWORD PartyAddress)
{
    fPosition pos;
    ZeroMemory(&pos, sizeof(fPosition));
    __try
    {
        pos.x = (ReadWORD(PartyAddress + 0x1C) - 0x10000) * 4;
        pos.y = (ReadWORD(PartyAddress + 0x1E) - 0x10000) * 4;
        pos.z = (ReadWORD(PartyAddress + 0x20) - 0x10000) * 4;



        if(abs(pos.x) > 0x1FFFF)
        {
            pos.x = ReadWORD(PartyAddress + 0x1C) * 4;

        }
        if(abs(pos.y) > 0x1FFFF)
        {
            pos.y = ReadWORD(PartyAddress + 0x1E) * 4;

        }
        if(abs(pos.z) > 0x1FFFF)
        {
            pos.z = ReadWORD(PartyAddress + 0x20) * 4;
        }

        if(abs(pos.x) > 0x1FFFF)
        {
            pos.x = (0x1FFFF - ReadWORD(PartyAddress + 0x1C)) * 4 * -1;
        }
        if(abs(pos.y) > 0x1FFFF)
        {
            pos.y = (0x1FFFF - ReadWORD(PartyAddress + 0x1E)) * 4 * -1;
        }
        if(abs(pos.z) > 0x1FFFF)
        {
            pos.z = (0x1FFFF - ReadWORD(PartyAddress + 0x20)) * 4 * -1;
        }
    }
    __except(1)
    {
        TRACE(_T("获取角色坐标出错"));
    }
    return pos;
}

DWORD Gamecall::GetPartyAngle(DWORD PartyAddress)
{
    DWORD Angle;
    Angle = NULL;
    __try
    {
        Angle = ReadWORD(PartyAddress + 0x32);
    }
    __except(1)
    {
        TRACE(_T("获取面向出错"));
    }
    return Angle;
}

DWORD Gamecall::GetPartyLv(DWORD PartyAddress)
{
    DWORD Lv;
    Lv = NULL;
    __try
    {
        Lv = (DWORD)ReadByte(PartyAddress + 0x1A);
    }
    __except(1)
    {
        TRACE(_T("获取队伍等级出错"));
    }
    return Lv;
}

DWORD Gamecall::GetPartyByAddress(DWORD PartyAddress, int i)
{
    DWORD NewAddress;
    NewAddress = NULL;
    __try
    {
        NewAddress = ReadDWORD(PartyAddress + i * 0x4);
    }
    __except(1)
    {
        TRACE(_T("获取当前角色地址出错"));
    }
    return NewAddress;
}

int Gamecall::GetObjectTargetId(DWORD pObjAddress)
{
    if(pObjAddress < 0x3000000)
    {
        return 0;
    }
    DWORD TargetId;
    TargetId = NULL;
    __try
    {
        TargetId = ReadDWORD(pObjAddress + 0x108);
    }
    __except(1)
    {
        TRACE(_T("获取TargetId出错"));
    }
    return TargetId;
}


ObjectNode* Gamecall::GetObjectById(DWORD Id)
{
    ObjectVector ov;
    GetAllObjectToVector(GetObjectBinTreeBaseAddr(), ov);

    for(int i = 0 ; i < ov.size(); i++)
    {
        if(ov[i]->id == Id)
        {
            return ov[i];
        }
    }
    return NULL;
}

BOOL Gamecall::IsObjectFightStatus(DWORD pObjAddress)
{
    if(pObjAddress < 0x3000000)
    {
        return 0;
    }
    BOOL value = FALSE;
    __try
    {
        value = ReadByte(pObjAddress + Play_fighting_status_offset3);
        //TRACE1("战斗状态:%d",value);
    }
    __except(1)
    {
        TRACE(_T("获得战斗状态出错"));
    }
    return value;
}

BOOL Gamecall::IsPlayerSkillStatus(DWORD pObjAddress)
{
    if(pObjAddress < 0x3000000)
    {
        return 0;
    }
    WORD value = 0;
    __try
    {
        value = ReadWORD(ReadDWORD(pObjAddress + 0x14) + 0x80);
    }
    __except(1)
    {
        TRACE(_T("获得释放技能状态出错"));
    }
    return (value != 0xFFFF);
}

DWORD Gamecall::GetPlarerRedHeart()
{
    DWORD pAddr = GetPlayerDataAddr();
    BYTE Rh = 0;
    __try
    {
        Rh = ReadByte(pAddr + 0x1AA);
    }
    __except(1)
    {
        TRACE(_T("获得角色红心出错"));
    }
    return Rh;
}

BOOL Gamecall::IsObjectControl(DWORD pObjAddress)
{
    if(pObjAddress < 0x3000000)
    {
        return 0;
    }
    BOOL value = FALSE;
    __try
    {
        value = ReadDWORD(ReadDWORD(pObjAddress + 708) + 0x5C);
        if(value == 2)
        {
            return TRUE;
        }
    }
    __except(1)
    {
        TRACE(_T("获得控制状态出错"));
    }
    return FALSE;
}

BOOL Gamecall::isStrikeCd(DWORD id)
{
    StrikeVector JnVec;
    GetStrikeToVector(JnVec);

    for(StrikeVector::iterator it = JnVec.begin(); it != JnVec.end(); it++)
    {
        if((*it).id == id)
        {
            if((*it).bAviable)
            {
                return (*it).bCD;
            }
        }
    }
    return FALSE;
}

void Gamecall::Pickup()
{
    PARAM_2 temp;
    temp.argv1 = 0x2;
    temp.argv2 = 0x13;
    sendcall(id_msg_Operation, &temp);
}

DWORD Gamecall::GetObjectCountByName(wchar_t* Name, fPosition& pos, DWORD Range)
{
    DWORD Rs_Count = 0;
    ObjectVector RangeObject;
    if(pos.x == 0)
    {
        if(Range == 0)
        {
            GetAllObjectToVector(GetObjectBinTreeBaseAddr(), RangeObject);
        }
        else
        {
            GetRangeObjectToVector(GetObjectBinTreeBaseAddr(), Range, RangeObject);
        }
    }
    else
    {
        //TRACE(_T("进来了GetRangeMonsterToVector"));
        //TRACE(_T("%d,%d,%d\n"),(int)pos.x,(int)pos.y,(int)pos.z);
        GetRangeMonsterToVector(GetObjectBinTreeBaseAddr(), Range, RangeObject, pos);
    }
    //TRACE(_T("进来了GetRangeMonsterToVector:%d"), RangeObject.size());
    //std::sort(RangeObject.begin(), RangeObject.end(), UDgreater);
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
        if(name == NULL) continue;

        if(wcscmp(name, Name) == 0)
        {
            Rs_Count++;
        }
   /*     else
        {
            TRACE(_T("其他怪物的名字:%s"), name);
        }*/
    }

    return Rs_Count;
}

BOOL Gamecall::isStrikeCan(wchar_t* Name)
{
	StrikeVector JnVec;
	GetStrikeToVector(JnVec);

	for(StrikeVector::iterator it = JnVec.begin(); it != JnVec.end(); it++)
	{
		if(wcscmp((*it).name,Name )== 0)
		{
			return TRUE;
		}
	}
	return FALSE;
}


//邀请组队
void Gamecall::Party_Invite(DWORD sn, DWORD id)
{
	BYTE* pBuf = (BYTE *)AllocGameMemory(0x30);
	*(WORD*)pBuf = CONST_PARTYINVITE;
	*(DWORD*)(pBuf + 0x4) = PHEAD_PARTYINVITE;
	*(DWORD*)(pBuf + 0x10) = sn;
	*(DWORD*)(pBuf + 0x14) = id;

	*(pBuf + 0x25) = 4;
	*(pBuf + 0x26) = 0x1c;
	*(pBuf + 0x27) = 00;
	*(pBuf + 0x28) = 5;

	Packet_Send(pBuf);
}

//{明文发包}
void Gamecall::Packet_Send(BYTE *PBuffer, DWORD PType)
{

	EnterCriticalSection(&F_SendPacket_CS);

	if(PBuffer > 0)
	{
		__asm
		{
			push PType;
			mov  esi,PBuffer;
			mov eax, FUNC_SENDPACKET;
			call eax;
			add  esp,4;
		}
	}

	 LeaveCriticalSection(&F_SendPacket_CS);
}

//{根据名字取控件Id}
DWORD Gamecall::GetUIId(wchar_t *UIName)
{

	DWORD Result = 0;
	if(UIName == NULL) return 0;
	if(*UIName == L' ') return 0;

	__asm
	{

		call dword ptr ds:[CONST_GETUIID];
		mov  esi,eax;
		test esi,esi;
		Je   fun_exit;

		mov  edx,dword ptr ds:[esi];
		push UIName;
		mov  eax,dword ptr ds:[edx+ OFFSET_GETUIID];
		mov  ecx,esi;
		call eax;
		mov  Result,eax;
fun_exit:
	}

	return Result;
}

//{取控件指针}
bool Gamecall::GetUI(wchar_t *UIName, UI *ui, DWORD nType)
{
	bool bRet = false;


	BYTE *PTMP;
	DWORD  UIId;
	DWORD PInfo;
	DWORD vCode;
	DWORD pName;

	ZeroMemory(ui,sizeof(UI));
	if (UIName == NULL) return false;
	if(*UIName == L' ') return false;

	//{取控件Id}
	UIId = GetUIId(UIName);
	if (UIId == 0) return false;

	PTMP = new BYTE[0x10];
	__asm
	{
		mov  eax,Offset_Game_Base;
		mov  eax,dword ptr ds:[eax];
		mov  eax,dword ptr ds:[eax+ Offset_UI_Offset0];
		mov  ecx,dword ptr ds:[eax+ Offset_UI_Offset1+ Offset_UI_Offset2];
		lea  edi,dword ptr ds:[ecx+ Offset_UI_Offset3];
		lea  ecx,dword ptr ss:[UIId];
		mov  eax,PTMP;
		call dword ptr ds:[FUNC_GETPUI];
	}

	switch(nType)
	{
	case 1:
		{
			PInfo = *(DWORD *) (   (*(DWORD *)(DWORD(PTMP)+ 4)  +  0x10   ));
			break;
		}
	case 2:
		{
			PInfo = *(DWORD *)(DWORD(PTMP)+ 0x4);
			break;
		}	  

	default:
		{
			PInfo = *(DWORD *)(DWORD(*(DWORD *)(DWORD(PTMP)+ 4)) +  0x10);
			break;
		}
	}

	if (PInfo>0)
	{

		vCode= ReadDWORD(PInfo+ Offset_UI_Code);

		if (vCode<3)
		{

			//{信息指针}
			ui->PInfo = PInfo;
			
			//{Id}
			ui->Id=ReadDWORD(PInfo + 0x4);

			//{控件名}
			pName = ReadDWORD(PInfo + Offset_UI_PName);
			ui->szName= (wchar_t *)ReadDWORD(pName);
			
			//{vCode}
			ui->vCode=vCode;

			//{是否可见}
			ui->bVisable=vCode=1;
		}


		bRet = true;
	}

	delete []PTMP;
	return bRet;
}



void Gamecall::GetInvite(TInvite *pstInvite)
{

	ZeroMemory(pstInvite,sizeof(TInvite));

	UI ui;
	//'窗口_接受组队
	if(!GetUI(L"InvitedPartyConfirmPanel", &ui)) return;


	if (ui.PInfo>0)
	{
		pstInvite->PInfo = ui.PInfo;
		pstInvite->PartySn = ReadDWORD(ui.PInfo+ Offset_UI_PartySn);
		pstInvite->PartyTId = ReadDWORD(ui.PInfo+ Offset_UI_PartyTId);
		pstInvite->CaptainSn = ReadDWORD(ui.PInfo+ Offset_UI_CaptainSn);
		pstInvite->CaptainTId = ReadDWORD(ui.PInfo+ Offset_UI_CaptainTId);
	}
}

void Gamecall::Party_Accept(DWORD PartySn, DWORD PartyTId, DWORD CaptainSn, DWORD CaptainTId)
{
	if(PartySn == 0 || PartyTId==0 || CaptainSn == 0 || CaptainTId ==0)
	{
		return;
	}

	BYTE *PBuffer = AllocGameMemory(0x28);

	*(WORD*)(PBuffer+ 4) = PHEAD_PARTYACCEPT;
	*(DWORD*)PBuffer = CONST_PARTYACCEPT;

	*(DWORD*)(PBuffer+ 0x0) = PartySn;
	*(DWORD*)(PBuffer+ 0x14) = PartyTId;

	*(DWORD*)(PBuffer+ 0x18) = CaptainSn;
	*(DWORD*)(PBuffer+ 0x1C) = CaptainTId;

	*(DWORD*)(PBuffer+ 0x24) = 4;

	Packet_Send(PBuffer);
}


//申请内存
BYTE* Gamecall::AllocGameMemory(DWORD ALen)
{
	BYTE* Result;
	__asm
	{
		mov  esi,ALen;
		mov eax, FUNC_ALLOCGAMEMMORY;
		call eax;
		mov  Result,eax
	}

	if(Result > 0)
	{
		ZeroMemory(Result, ALen);
	}

	return Result;
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

wchar_t* ReadStr(DWORD addr)
{
    if(!IsBadReadPtr((void*)addr, sizeof(char)))
    {
        return (wchar_t*)addr;
    }
    return 0;
}
