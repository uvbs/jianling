// DataDlg1.cpp : implementation file
//

#include "stdafx.h"
#include "Jlwg.h"
#include "JLDlg.h"
#include "DataDlg.h"
#include "GameHook.h"
#include "GameConfig.h"
#include "ConfigQhPage.h"
#include "ConfigSheet.h"
#include "LuaPage.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



TCHAR* cli_AllObject[] =
{
    {_T("地址")},
    {_T("名字")},
    {_T("ID")},
    {_T("ID2")},
    {_T("类型")},
    {_T("血量")},
    {_T("索引")},
    {_T("坐标")}
};

TCHAR* cli_RangeObject[] =
{
    {_T("地址")},
    {_T("名字")},
    {_T("ID")},
    {_T("ID2")},
    {_T("类型")},
    {_T("血量")},
    {_T("距离")},
    {_T("坐标")},
    {_T("是否怪物")},
    {_T("索引")},
    {_T("面向")}
};

//技能 需要的控件列
TCHAR* cli_Bar[] =
{
    {_T("名称")},
    {_T("地址")},
    {_T("id")}
};

TCHAR* cli_Strike[] =
{
    {_T("技能名")},
    {_T("冷却")},
    {_T("可用")},
    {_T("解锁")},
    {_T("ID_1")},
    {_T("ID_2")}
};

TCHAR* cli_Quest[] =
{
    {_T("任务名称")},
    {_T("步骤")},
    {_T("结束标志")},
    {_T("任务数量")},
    {_T("任务ID")},
};



TCHAR* cli_TaskItem[] =
{
    {_T("名称")},
    {_T("距离")},
    {_T("坐标")},
    {_T("类型")}
};


TCHAR* cli_Bag[] =
{
    {_T("名称")},
    {_T("耐久")},
    {_T("等级")},
    {_T("数量")},
    {_T("类型")},
    {_T("位置")},
    {_T("地址")},
    {_T("封印")},
    {_T("经验")},
    {_T("颜色")},
    {_T("总经验")},
    {_T("评级")},
    {_T("八卦")},
    {_T("类型")}

};

TCHAR* cli_Loots[] =
{
    {_T("地址")},
    {_T("名称")},
    {_T("坐标")},
    {_T("距离")}
};


//构造函数
CDataDlg::CDataDlg(CWnd* pParent /*=NULL*/)
    : CDialog(CDataDlg::IDD, pParent)
{
    //{{AFX_DATA_INIT(CDataDlg)
    m_nRange = 0;
    m_bHook_step = FALSE;
    m_bHook_Dundi = FALSE;
    m_bHook_Pickup1 = FALSE;
    m_bHook_quest = FALSE;
    m_bHook_Weaquit = FALSE;
    m_bHook_Accquest = FALSE;
    m_bHook_Combat = FALSE;
    //}}AFX_DATA_INIT

    m_pLuaPage = NULL;
    m_pDbgPage = NULL;
}

CDataDlg::~CDataDlg()
{
    SafeDelete(m_pDbgPage);
    SafeDelete(m_pLuaPage);
}

void CDataDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CDataDlg)
    DDX_Control(pDX, IDC_TAB1, m_TabCtrl);
    DDX_Control(pDX, IDC_LIST, m_ListCtrl);
    DDX_Control(pDX, IDC_COMBO_DATATYPE, m_ComBox);
    DDX_Text(pDX, IDC_EDITMEMINPUT, m_nRange);
    DDX_Check(pDX, IDC_HOOK_SENDSTEP, m_bHook_step);
    DDX_Check(pDX, IDC_HOOK_DUNDI, m_bHook_Dundi);
    DDX_Check(pDX, IDC_HOOK_YICIJIANWU, m_bHook_Pickup1);
    DDX_Check(pDX, IDC_HOOK_DEQUEST, m_bHook_quest);
    DDX_Check(pDX, IDC_HOOK_CHUANZHUANGBEI, m_bHook_Weaquit);
    DDX_Check(pDX, IDC_HOOK_ACCEPTQUEST, m_bHook_Accquest);
    DDX_Check(pDX, IDC_HOOK_COMBAT, m_bHook_Combat);
    //}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDataDlg, CDialog)
    //{{AFX_MSG_MAP(CDataDlg)
    ON_BN_CLICKED(ID_GETPALYERINFO, OnGetpalyerinfo)
    ON_BN_CLICKED(IDC_SPEEDX, OnSpeedx)
    ON_CBN_SELCHANGE(IDC_COMBO_DATATYPE, OnSelchangeComboDatatype)
    ON_BN_CLICKED(IDC_BTNCONFIG, OnBtnConfig)
    ON_BN_CLICKED(IDC_REFRESH, OnRefresh)
    ON_BN_CLICKED(IDC_HOOK_SENDSTEP, OnHookSendstep)
    ON_BN_CLICKED(IDC_HOOK_YICIJIANWU, OnHookYicijianwu)
    ON_BN_CLICKED(IDC_HOOK_DEQUEST, OnHookDequest)
    ON_BN_CLICKED(IDC_HOOK_CHUANZHUANGBEI, OnHookChuanzhuangbei)
    ON_BN_CLICKED(IDC_HOOK_DUNDI, OnHookDundi)
    ON_BN_CLICKED(ID_CLR, OnClr)
    ON_COMMAND(IDC_TURNTO, OnTurnto)
    ON_COMMAND(ID_STEPTOOBJET, OnSteptoobjet)
    ON_NOTIFY(NM_RCLICK, IDC_LIST, OnRclickList)
    ON_BN_CLICKED(ID_FINDTHENKILL, OnFindthenkill)
    ON_BN_CLICKED(IDC_HOOK_ACCEPTQUEST, OnHookAcceptquest)
    ON_COMMAND(ID_HOOKSTRIKE, OnHookstrike)
    ON_BN_CLICKED(IDC_HOOK_COMBAT, OnHookCombat)
    ON_BN_CLICKED(IDC_BOSSCOMBAT, OnBossBombat)
    ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, OnSelchangeTab1)
	ON_COMMAND(ID_GOTOBACK, OnGotoback)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CDataDlg message handlers

void CDataDlg::CheckHook()
{

    if(m_bHook_Combat)
        GameHook::GetInstance()->CombatHook.unhook();

    if(m_bHook_Accquest)
        GameHook::GetInstance()->aeQuestHook.unhook();

    if(m_bHook_Dundi)
        GameHook::GetInstance()->DundiHook.unhook();

    if(m_bHook_Pickup1)
        GameHook::GetInstance()->Yicjw.unhook();

    if(m_bHook_quest)
        GameHook::GetInstance()->deQuestHook.unhook();

    if(m_bHook_Weaquit)
        GameHook::GetInstance()->WearHook.unhook();

    if(m_bHook_step)
        GameHook::GetInstance()->stepHook.unhook();

}

void CDataDlg::AddInfo(const TCHAR szFormat[], ...)
{
    TCHAR buffer[BUFSIZ] = {0};

    va_list argptr;
    va_start(argptr, szFormat);
    wvsprintf(buffer, szFormat, argptr);
    va_end(argptr);

    _tcscat(buffer, _T("\r\n"));

    m_pDbgPage->m_strInfo += buffer;
    m_pDbgPage->UpdateData(FALSE);
}



BOOL CDataDlg::OnInitDialog()
{
    CDialog::OnInitDialog();


    m_ComBox.AddString(_T("所有对象"));
    m_ComBox.AddString(_T("未接任务"));
    m_ComBox.AddString(_T("技能"));
    m_ComBox.AddString(_T("范围对象"));
    m_ComBox.AddString(_T("任务"));
    m_ComBox.AddString(_T("背包"));
    m_ComBox.AddString(_T("界面"));
    m_ComBox.AddString(_T("范围怪物"));
    m_ComBox.AddString(_T("任务物品"));
    m_ComBox.AddString(_T("装备"));
    m_ComBox.AddString(_T("周围掉落"));
    m_ComBox.AddString(_T("范围怪物(配置文件)"));

    m_ListCtrl.SetExtendedStyle(LVS_EX_FULLROWSELECT);

    //配置lua和调试信息两个页面
    if(m_pDbgPage == NULL)
    {
        m_pDbgPage = new CDbgPage;
    }

    if(m_pLuaPage == NULL)
    {
        m_pLuaPage = new CLuaPage;
    }

    CRect rect;
    m_TabCtrl.GetWindowRect((LPRECT)rect);
    ScreenToClient((LPRECT)rect);

    m_TabCtrl.InsertItem(0, _T("调试"));
    m_TabCtrl.InsertItem(1, _T("脚本"));

    m_pLuaPage->Create(CLuaPage::IDD, this);
    m_pDbgPage->Create(CDbgPage::IDD, this);

    m_pLuaPage->SetWindowPos(NULL, rect.left + 5, rect.top + 20, 0, 0, SWP_NOSIZE);
    m_pDbgPage->SetWindowPos(NULL, rect.left + 5, rect.top + 20, 0, 0, SWP_NOSIZE);
    m_pDbgPage->ShowWindow(SW_SHOW);

    CheckHook();

    //初始化钩子
    GameHook::GetInstance()->SetSink(this);


    return TRUE;  // return TRUE unless you set the focus to a control
    // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CDataDlg::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{

    NMHDR* pNMHdr = (NMHDR*)lParam;
    switch(pNMHdr->code)
    {
    case NM_CLICK:
        {
            //显示点击的名字到编辑控件方便复制
            NMLISTVIEW* pItem = (NMLISTVIEW*)pNMHdr;
            CString strClick = m_ListCtrl.GetItemText(pItem->iItem, pItem->iSubItem);
            if(strClick.IsEmpty() == FALSE)
            {
                AddInfo((LPCTSTR)strClick);
            }
        }
        break;

    }

    return CDialog::OnNotify(wParam, lParam, pResult);
}

void CDataDlg::OnGetpalyerinfo()
{
    //获取游戏外挂功能
    GamecallEx& gcall = *GamecallEx::GetInstance();

    fPosition PlayerPos;
    gcall.GetPlayerPos(&PlayerPos);

    sPosition PlayerPos2;
    gcall.GetPlayerPos2(&PlayerPos2);

    AddInfo(_T("角色名: %s"), gcall.GetPlayerName());
    AddInfo(_T("角色地图ID: %d"), gcall.GetCityID());
    AddInfo(_T("角色魔法: %d"), gcall.GetPlayerMana());
    AddInfo(_T("角色等级: %d"), gcall.GetPlayerLevel());
    AddInfo(_T("角色血量: %d"), gcall.GetPlayerHealth());
    AddInfo(_T("角色最大血量: %d"), gcall.GetPlayerMaxHealth());
    AddInfo(_T("角色内力: %d"), gcall.GetPlayerMana());
    AddInfo(_T("角色ID: %d"), gcall.GetPlayerID());
    AddInfo(_T("角色最大体力: %d"), (int)gcall.GetPlayerMaxVit());
    AddInfo(_T("角色体力: %d"), (int) gcall.GetPlayerVit());
    AddInfo(_T("角色视角: %d"), (int)gcall.GetPlayerViewPoint());
    AddInfo(_T("人物UI状态: %d"), gcall.GetPlayerQuestUIStatus());
    AddInfo(_T("人物UI状态2: %d"), gcall.GetPlayerQuestUIStatusts());
    AddInfo(_T("LoadingMap: %d"), gcall.isLoadingMap());

    AddInfo(_T("角色坐标: x:%d y:%d z:%d"), (int)PlayerPos.x, (int)PlayerPos.y, (int)PlayerPos.z);
    AddInfo(_T("角色坐标2: x:%d y:%d z:%d"), (int)PlayerPos2.x, (int)PlayerPos2.y, (int)PlayerPos2.z);

}


//遍历全部对象
void CDataDlg::PrintfAllObject()
{
    //获取游戏外挂功能
    GamecallEx& gcall = *GamecallEx::GetInstance();


    ObjectVector RangeObject;
    gcall.GetAllObjectToVector(gcall.GetObjectBinTreeBaseAddr(), RangeObject);

    m_ListCtrl.SetRedraw(FALSE);
    for(DWORD i = 0; i < RangeObject.size(); i++)
    {

        ObjectNode* pNode = RangeObject[i];


        //地址
        CString strAddr;
        strAddr.Format(_T("%08x"), pNode->ObjAddress);
        m_ListCtrl.InsertItem(i, strAddr);



        DWORD type = gcall.GetObjectType(pNode->ObjAddress);


        //名称
        wchar_t* pText = gcall.GetObjectName(pNode->ObjAddress);
        m_ListCtrl.SetItemText(i, 1, pText);

        CString strTemp;
        strTemp.Format(_T("%d"), pNode->id);
        m_ListCtrl.SetItemText(i, 2, strTemp);

        strTemp.Format(_T("%d"), pNode->id2);
        m_ListCtrl.SetItemText(i, 3, strTemp);


        strTemp.Format(_T("%d"), type);
        m_ListCtrl.SetItemText(i, 4, strTemp);


        if(type == 0x4)
        {
            strTemp.Format(_T("%d"), gcall.GetType4HP(pNode->ObjAddress));
            m_ListCtrl.SetItemText(i, 5, strTemp);
        }


        int suoyin = gcall.GetIndexByType(pNode->ObjAddress);
        if(suoyin != -1)
        {
            strTemp.Format(_T("%d"), suoyin);
            m_ListCtrl.SetItemText(i, 6, strTemp);
        }


        //显示对象的坐标
        fPosition fpos;
        if(gcall.GetObjectPos(pNode, &fpos))
        {
            strTemp.Format(_T("x:%d y:%d z:%d"), (int)fpos.x, (int)fpos.y, (int)fpos.z);
            m_ListCtrl.SetItemText(i, 7, strTemp);
        }


        m_ListCtrl.SetItemData(i, (DWORD)pNode);
    }
    m_ListCtrl.SetRedraw(TRUE);
}

void CDataDlg::InertBagItem(DWORD i, _BAGSTU& BagBuff)
{
    //物品名称
    m_ListCtrl.InsertItem(i, BagBuff.name);

    CString strLast;
    strLast.Format(_T("%d"), BagBuff.m_Lasting);
    m_ListCtrl.SetItemText(i, 1, strLast);

    strLast.Format(_T("%d"), BagBuff.m_LV);
    m_ListCtrl.SetItemText(i, 2, strLast);

    strLast.Format(_T("%d"), BagBuff.m_Num);
    m_ListCtrl.SetItemText(i, 3, strLast);

    strLast.Format(_T("%d"), BagBuff.m_Type);
    m_ListCtrl.SetItemText(i, 4, strLast);

    strLast.Format(_T("%d"), BagBuff.m_Info);
    m_ListCtrl.SetItemText(i, 5, strLast);

    strLast.Format(_T("%08x"), BagBuff.m_Base);
    m_ListCtrl.SetItemText(i, 6, strLast);

    strLast.Format(_T("%d"), BagBuff.m_IsFengYin);
    m_ListCtrl.SetItemText(i, 7, strLast);

    strLast.Format(_T("%d"), BagBuff.m_DangQianJingYanZhi);
    m_ListCtrl.SetItemText(i, 8, strLast);

    strLast.Format(_T("%d"), BagBuff.m_YanSe);
    m_ListCtrl.SetItemText(i, 9, strLast);

    strLast.Format(_T("%d"), BagBuff.m_DangQianJingYanZongZhi);
    m_ListCtrl.SetItemText(i, 10, strLast);

    strLast.Format(_T("%d"), BagBuff.m_PingJi);
    m_ListCtrl.SetItemText(i, 11, strLast);

    strLast.Format(_T("%d"), BagBuff.m_BaGuaGeZiShu);
    m_ListCtrl.SetItemText(i, 12, strLast);

}

//遍历角色装备
void CDataDlg::PrintfPlayerEquip()
{
    //获取游戏外挂功能
    GamecallEx& gcall = *GamecallEx::GetInstance();

    std::vector<_BAGSTU> GoodsItem;
    gcall.GetAllBodyEquipToVector(GoodsItem);

    for(DWORD i = 0; i < GoodsItem.size() ; i++)
    {
        InertBagItem(i, GoodsItem[i]);

    }
}


void CDataDlg::PrintfRangeTaskItem()
{
    //获取游戏外挂功能
    GamecallEx& gcall = *GamecallEx::GetInstance();


    std::vector<ObjectNode*> RangeObject;
    gcall.GetRangeTaskItemToVectr(RangeObject, m_nRange);

    std::sort(RangeObject.begin(), RangeObject.end(), GamecallEx::UDgreater);
    fPosition fmypos;
    gcall.GetPlayerPos(&fmypos);

    for(DWORD i = 0; i < RangeObject.size(); i++)
    {
        ObjectNode* pNode = RangeObject[i];



        //名字
        wchar_t* name = gcall.GetObjectName(pNode->ObjAddress);
        if(name != NULL)
        {
            m_ListCtrl.InsertItem(i, name);
        }


        //距离
        fPosition fpos;
        if(gcall.GetObjectPos(pNode, &fpos))
        {
            CString strTemp;
            strTemp.Format(_T("%d"), (DWORD)gcall.CalcC(fmypos, fpos));
            m_ListCtrl.SetItemText(i, 1, strTemp);


            strTemp.Format(_T("x:%d y:%d z:%d"), (int)fpos.x, (int)fpos.y, (int)fpos.z);
            m_ListCtrl.SetItemText(i, 2, strTemp);
        }

        CString strTemp;
        strTemp.Format(_T("%08x"), gcall.GetObjectType(pNode->ObjAddress));
        m_ListCtrl.SetItemText(i, 3, strTemp);
    }

}


//取得所有UI
void CDataDlg::PrintfAllUI()
{

    //获取游戏外挂功能
    GamecallEx& gcall = *GamecallEx::GetInstance();

    std::vector<Tree*> AllUI;
    gcall.sendcall(id_msg_vector_ui, &AllUI);

    CString strTemp;
    for(DWORD i = 0; i < AllUI.size(); i++)
    {
        wchar_t* name = gcall.GetUIName(AllUI[i]->Adress);
        if(name != NULL)
        {
            if(AllUI[i]->Adress != 0)
            {
                m_ListCtrl.InsertItem(i, name);

                strTemp.Format(_T("%08x"), (DWORD)AllUI[i]->Adress);
                m_ListCtrl.SetItemText(i, 1, strTemp);

                strTemp.Format(_T("%d"), (DWORD)AllUI[i]->ID);
                m_ListCtrl.SetItemText(i, 2, strTemp);
            }
        }
    }
}

//遍历任务
void CDataDlg::PrintfQuest()
{

    //获取游戏外挂功能
    GamecallEx& gcall = *GamecallEx::GetInstance();

    int TaskNum = 53;
    DWORD pStartAddr = gcall.GetTaskStartAddr();  //获取任务开始地址


    CString strTemp;
    for(int i = 0; i < TaskNum; i++)
    {
        //DWORD *pAddr        =     gcall.GetTaskPresentAddr(i, pStartAddr);  //获得当前任务地址
        DWORD ID = gcall.GetTaskID(i, pStartAddr);  //获得当前任务ID
        DWORD name_id = gcall.GetTaskNameID(i, pStartAddr);  //获得当前任务名字ID
        DWORD info = gcall.GetPresentTaskIndexes(i, pStartAddr);  //获得当前做到第几个小任务
        DWORD endflag = gcall.GetPresentTaskEndFlag(i, pStartAddr, info);  //获得当前小任务结束标志
        DWORD num = gcall.GetPresentTaskNum(i, pStartAddr, info);  //获得当前小任务已经打的怪数量

        wchar_t* name = (wchar_t*)gcall.sendcall(id_msg_GatTaskName, (LPVOID)name_id);
        if(name)
        {
            m_ListCtrl.InsertItem(i, name);
        }
        else
        {
            //遍历完成
            break;
        }

        strTemp.Format(_T("%d"), info);
        m_ListCtrl.SetItemText(i, 1, strTemp);

        strTemp.Format(_T("%d"), endflag);
        m_ListCtrl.SetItemText(i, 2, strTemp);

        strTemp.Format(_T("%d"), num);
        m_ListCtrl.SetItemText(i, 3, strTemp);

        strTemp.Format(_T("%d"), ID);
        m_ListCtrl.SetItemText(i, 4, strTemp);
    }

}

//遍历背包
void CDataDlg::PrintfBag()
{

    //获取游戏外挂功能
    GamecallEx& gcall = *GamecallEx::GetInstance();

    std::vector<_BAGSTU> RangeObject;
    gcall.GetAllGoodsToVector(RangeObject);

    CString strTemp;
    for(DWORD i = 0; i < RangeObject.size(); i++)
    {
        InertBagItem(i, RangeObject[i]);
    }
}

//遍历背包
void CDataDlg::PrintfRangeLoot()
{
    //获取游戏外挂功能
    GamecallEx& gcall = *GamecallEx::GetInstance();


    std::vector<ObjectNode*> RangeObject;
    gcall.GetRangeLootObjectToVector(m_nRange, RangeObject);

    CString strTemp;
    for(DWORD index = 0; index < RangeObject.size(); index++)
    {
        ObjectNode* pNode = RangeObject[index];

        //对象地址
        strTemp.Format(_T("%08x"), (DWORD)pNode->ObjAddress);
        m_ListCtrl.InsertItem(index, strTemp);


        //名称
        TCHAR* pText = (LPTSTR)gcall.GetObjectName(pNode->ObjAddress);
        m_ListCtrl.SetItemText(index, 1, pText);


        //距离
        fPosition mypos;
        gcall.GetPlayerPos(&mypos);

        fPosition tarpos;
        gcall.GetObjectPos(pNode, &tarpos);


        strTemp.Format(_T("%d"), (DWORD)gcall.CalcC(tarpos, mypos));
        m_ListCtrl.SetItemText(index, 2, strTemp);



        strTemp.Format(_T("x:%d y:%d z:%d"), (int)tarpos.x, (int)tarpos.y, (int)tarpos.z);
        m_ListCtrl.SetItemText(index, 3, strTemp);


        //索引
        strTemp.Format(_T("%08x"), gcall.GetIndexByType(pNode->ObjAddress));
        m_ListCtrl.SetItemText(index, 7, strTemp);


        m_ListCtrl.SetItemData(index, (DWORD)pNode);
    }
}


//遍历攻击技能
void CDataDlg::PrintfStrike()
{

    //获取游戏外挂功能
    GamecallEx& gcall = *GamecallEx::GetInstance();


    std::vector<STRIKEINFO> RangeObject;
    gcall.GetStrikeToVector(RangeObject);

    CString strTemp;
    for(DWORD i = 0; i < RangeObject.size(); i++)
    {
        int id1 = RangeObject[i].id1;
        int id2 = RangeObject[i].id2;

        wchar_t* name = RangeObject[i].stName.name;

        //地址
        m_ListCtrl.InsertItem(i, name);

        strTemp.Format(_T("%d"), RangeObject[i].cd);
        m_ListCtrl.SetItemText(i, 1, strTemp);



        if(RangeObject[i].isBlock == 0)
        {

            strTemp.Format(_T("不可用"));
            m_ListCtrl.SetItemText(i, 2, strTemp);
            strTemp.Format(_T("未解锁"));
        }
        else
        {
            if(RangeObject[i].canUse == 0)
            {
                strTemp.Format(_T("可使用"));
            }
            else
            {
                strTemp.Format(_T("不可用"));
            }
            //strTemp.Format(_T("%d"), RangeObject[i].canUse);
            m_ListCtrl.SetItemText(i, 2, strTemp);
            strTemp.Format(_T("已解锁"));
        }
        //strTemp.Format(_T("%d"), RangeObject[i].isBlock);
        m_ListCtrl.SetItemText(i, 3, strTemp);

        strTemp.Format(_T("%d"), id1);
        m_ListCtrl.SetItemText(i, 4, strTemp);

        strTemp.Format(_T("%d"), id2);
        m_ListCtrl.SetItemText(i, 5, strTemp);

    }

}

void CDataDlg::PrintfRangeMonster(BOOL bApplyConfig)
{
    UpdateData();

    //获取游戏外挂功能
    GamecallEx& gcall = *GamecallEx::GetInstance();

    std::vector<ObjectNode*> RangeObject;
    gcall.GetRangeMonsterToVector(m_nRange, RangeObject);

    if(bApplyConfig)
    {
        gcall.Kill_ApplyConfig(RangeObject);
    }
    //判续对象, 根据距离
    std::sort(RangeObject.begin(), RangeObject.end(), GamecallEx::UDgreater);

    CString strTemp;
    for(DWORD index = 0; index < RangeObject.size(); index++)
    {
        ObjectNode* pNode = RangeObject[index];

        //地址
        strTemp.Format(_T("%08x"), pNode->ObjAddress);
        m_ListCtrl.InsertItem(index, strTemp);

        //名称
        TCHAR* pText = (LPTSTR)gcall.GetObjectName(pNode->ObjAddress);
        m_ListCtrl.SetItemText(index, 1, pText);

        strTemp.Format(_T("%d"), pNode->id);
        m_ListCtrl.SetItemText(index, 2, strTemp);

        strTemp.Format(_T("%d"), pNode->id2);
        m_ListCtrl.SetItemText(index, 3, strTemp);

        UCHAR type = gcall.GetObjectType(pNode->ObjAddress);
        strTemp.Format(_T("%d"), type);
        m_ListCtrl.SetItemText(index, 4, strTemp);

        //hp
        if(type == 0x4)
        {
            strTemp.Format(_T("%d"), gcall.GetType4HP(pNode->ObjAddress));
            m_ListCtrl.SetItemText(index, 5, strTemp);
        }

        //坐标和距离
        fPosition pos;
        if(gcall.GetObjectPos(pNode, &pos))
        {
            fPosition mypos;
            gcall.GetPlayerPos(&mypos);

            strTemp.Format(_T("%d"), (DWORD)gcall.CalcC(pos, mypos));
            m_ListCtrl.SetItemText(index, 6, strTemp);
            strTemp.Format(_T("x:%d y:%d z:%d"), (int)pos.x, (int)pos.y, (int)pos.z);
            m_ListCtrl.SetItemText(index, 7, strTemp);
        }




        //是否是怪物
        m_ListCtrl.SetItemText(index, 8, L"是");

        //索引
        int suoyin = gcall.GetIndexByType(pNode->ObjAddress);
        if(suoyin != -1)
        {
            strTemp.Format(_T("%d"), suoyin);
            m_ListCtrl.SetItemText(index, 9, strTemp);
        }

        //怪物面向
        strTemp.Format(_T("%d"), gcall.GetObjectView(pNode->ObjAddress));
        m_ListCtrl.SetItemText(index, 10, strTemp);


        m_ListCtrl.SetItemData(index, (DWORD)pNode);
    }

}




//遍历范围内的对象
void CDataDlg::PrintfRangeObject()
{

    UpdateData();

    //获取游戏外挂功能
    GamecallEx& gcall = *GamecallEx::GetInstance();


    std::vector<ObjectNode*> RangeObject;
    gcall.GetRangeObjectToVector(gcall.GetObjectBinTreeBaseAddr(), m_nRange, RangeObject);

    fPosition mypos;
    gcall.GetPlayerPos(&mypos);

    CString strTemp;
    for(DWORD index = 0; index < RangeObject.size(); index++)
    {
        ObjectNode* pNode = RangeObject[index];

        //对象地址
        strTemp.Format(_T("%08x"), (DWORD)pNode->ObjAddress);
        m_ListCtrl.InsertItem(index, strTemp);


        UCHAR type = gcall.GetObjectType(pNode->ObjAddress);
        strTemp.Format(_T("%d"), type);



        //名称
        wchar_t* pText = gcall.GetObjectName(pNode->ObjAddress);
        m_ListCtrl.SetItemText(index, 1, pText);

        strTemp.Format(_T("%d"), pNode->id);
        m_ListCtrl.SetItemText(index, 2, strTemp);

        strTemp.Format(_T("%d"), pNode->id2);
        m_ListCtrl.SetItemText(index, 3, strTemp);

        strTemp.Format(_T("%d"), type);
        m_ListCtrl.SetItemText(index, 4, strTemp);


        if(type == 0x4)
        {
            strTemp.Format(_T("%d"), gcall.GetType4HP(pNode->ObjAddress));
            m_ListCtrl.SetItemText(index, 5, strTemp);
        }



        //距离
        //坐标

        fPosition pos;
        if(gcall.GetObjectPos(pNode, &pos))
        {
            strTemp.Format(_T("x:%d y:%d z:%d"), (int)pos.x, (int)pos.y, (int)pos.z);
            m_ListCtrl.SetItemText(index, 7, strTemp);

            strTemp.Format(_T("%d"), (DWORD)gcall.CalcC(pos, mypos));
            m_ListCtrl.SetItemText(index, 6, strTemp);
        }


        //是否是怪物
        if(gcall.isCanKill(pNode))
        {
            m_ListCtrl.SetItemText(index, 8, _T("是"));
        }
        else
        {
            m_ListCtrl.SetItemText(index, 8, _T("否"));
        }



        //索引
        int suoyin = gcall.GetIndexByType(pNode->ObjAddress);
        if(suoyin != -1)
        {
            strTemp.Format(_T("%d"), suoyin);
            m_ListCtrl.SetItemText(index, 9, strTemp);
        }



        m_ListCtrl.SetItemData(index, (DWORD)pNode);

    }

}

void CDataDlg::OnSpeedx()
{
    //获取游戏外挂功能
    GamecallEx& gcall = *GamecallEx::GetInstance();

    UpdateData(TRUE);
    if(m_nRange == 0)
    {
        AfxMessageBox(_T("不能输入0值"));
    }
    else if(m_nRange > 50)
    {
        AfxMessageBox(_T("太大了, 可能会崩溃游戏"));
    }
    else
    {
        gcall.NewSpend((float)m_nRange);
    }
}


void CDataDlg::InsertColumnHelper(TCHAR* column[], int count)
{

    for(int i = 0; i < count; i++)
    {
        m_ListCtrl.DeleteColumn(i);
        m_ListCtrl.InsertColumn(i, column[i]);
    }
}


void CDataDlg::OnSelchangeComboDatatype()
{
    // TODO: Add your control notification handler code here
    UpdateData(TRUE);


    CString strSel;
    m_ComBox.GetLBText(m_ComBox.GetCurSel(), strSel);

    m_ListCtrl.DeleteAllItems();
    for(;;)
    {
        if(m_ListCtrl.DeleteColumn(0) == FALSE) break;
    }

    if(strSel == _T("背包"))
    {
        InsertColumnHelper(cli_Bag, sizeof(cli_Bag) / sizeof(TCHAR*));
        PrintfBag();

    }
    else if(strSel == _T("所有对象"))
    {
        InsertColumnHelper(cli_AllObject, sizeof(cli_AllObject) / sizeof(TCHAR*));
        PrintfAllObject();

    }
    else if(strSel == _T("界面"))
    {
        InsertColumnHelper(cli_Bar, sizeof(cli_Bar) / sizeof(TCHAR*));
        PrintfAllUI();
    }
    else if(strSel == _T("范围对象"))
    {
        InsertColumnHelper(cli_RangeObject, sizeof(cli_RangeObject) / sizeof(TCHAR*));
        PrintfRangeObject();
    }
    else if(strSel == _T("任务物品"))
    {
        InsertColumnHelper(cli_TaskItem, sizeof(cli_TaskItem) / sizeof(TCHAR*));
        PrintfRangeTaskItem();
    }
    else if(strSel == _T("装备"))
    {
        InsertColumnHelper(cli_Bag, sizeof(cli_Bag) / sizeof(TCHAR*));
        PrintfPlayerEquip();
    }
    else if(strSel == _T("技能"))
    {
        InsertColumnHelper(cli_Strike, sizeof(cli_Strike) / sizeof(TCHAR*));
        PrintfStrike();
    }
    else if(strSel == _T("周围掉落"))
    {
        InsertColumnHelper(cli_Loots, sizeof(cli_Loots) / sizeof(TCHAR*));
        PrintfRangeLoot();
    }
    else if(strSel == _T("范围怪物"))
    {
        InsertColumnHelper(cli_RangeObject, sizeof(cli_RangeObject) / sizeof(TCHAR*));
        PrintfRangeMonster();
    }
    else if(strSel == _T("范围怪物(配置文件)"))
    {
        InsertColumnHelper(cli_RangeObject, sizeof(cli_RangeObject) / sizeof(TCHAR*));
        PrintfRangeMonster(TRUE);
    }
    else if(strSel == _T("任务"))
    {
        InsertColumnHelper(cli_Quest, sizeof(cli_Quest) / sizeof(TCHAR*));
        PrintfQuest();
    }


    int i = 0;
    for(;;)
    {
        if(m_ListCtrl.SetColumnWidth(i++, LVSCW_AUTOSIZE_USEHEADER) == FALSE)
        {
            break;
        }
    }

}

void CDataDlg::OnBtnConfig()
{
    ShowWindow(SW_HIDE);

    //配置对话框
    CPropertySheet sheet(_T("配置文件"));
    CConfigQhPage qhpage;
    CConfigObjPage objpage;
    CConfigItemPage itempage;
    CConfigPartyPage partypage;

    sheet.AddPage(&qhpage);
    sheet.AddPage(&objpage);
    sheet.AddPage(&itempage);
    sheet.AddPage(&partypage);


    if(sheet.DoModal() == IDOK)
    {
        GameConfig::GetInstance()->SaveConfig();
    }



    ShowWindow(SW_SHOW);
}

void CDataDlg::OnRefresh()
{
    OnSelchangeComboDatatype();
}


//走路钩子
void CDataDlg::OnHookSendstep()
{
    UpdateData(TRUE);

    if(m_bHook_step)
    {
        GameHook::GetInstance()->backupSendStep = GameHook::GetInstance()->stepHook.hook();
    }
    else
    {
        GameHook::GetInstance()->stepHook.unhook();
    }
}


void CDataDlg::OnHookYicijianwu()
{
    // TODO: Add your control notification handler code here
    UpdateData(TRUE);
    if(m_bHook_Pickup1)
        GameHook::GetInstance()->backupYiciJianWu = GameHook::GetInstance()->Yicjw.hook();

    else
        GameHook::GetInstance()->Yicjw.unhook();
}

//npc接任务
void CDataDlg::OnHookDequest()
{
    // TODO: Add your control notification handler code here
    UpdateData(TRUE);
    if(m_bHook_quest)
        GameHook::GetInstance()->backupQuest = GameHook::GetInstance()->deQuestHook.hook();

    else
        GameHook::GetInstance()->deQuestHook.unhook();
}

void CDataDlg::OnHookChuanzhuangbei()
{
    // TODO: Add your control notification handler code here
    UpdateData(TRUE);
    if(m_bHook_Weaquit)
        GameHook::GetInstance()->backupWearEquipment = GameHook::GetInstance()->WearHook.hook();

    else
        GameHook::GetInstance()->WearHook.unhook();

}

void CDataDlg::OnHookDundi()
{
    // TODO: Add your control notification handler code here
    UpdateData(TRUE);
    if(m_bHook_Dundi)
    {
        GameHook::GetInstance()->backupDunDi = GameHook::GetInstance()->DundiHook.hook();
    }
    else
    {
        GameHook::GetInstance()->DundiHook.unhook();
    }

}

BOOL CDataDlg::DestroyWindow()
{
    CheckHook();
    return CDialog::DestroyWindow();
}

void CDataDlg::OnClr()
{
    m_pDbgPage->m_strInfo = _T("");
    m_pDbgPage->UpdateData(FALSE);
}

void CDataDlg::OnTurnto()
{

    //获取游戏外挂功能
    GamecallEx& gcall = *GamecallEx::GetInstance();

    POSITION pos = m_ListCtrl.GetFirstSelectedItemPosition();
    if(pos == NULL)
    {
        TRACE0("No items were selected!\n");
    }
    else
    {
        while(pos)
        {
            int nItem = m_ListCtrl.GetNextSelectedItem(pos);
            TRACE1("Item %d was selected!\n", nItem);
            ObjectNode* pNode = (ObjectNode*)m_ListCtrl.GetItemData(nItem);

            gcall.TurnTo(pNode);
        }
    }

}

void CDataDlg::OnSteptoobjet()
{
    //获取游戏外挂功能
    GamecallEx& gcall = *GamecallEx::GetInstance();

    POSITION pos = m_ListCtrl.GetFirstSelectedItemPosition();
    if(pos == NULL)
    {
        TRACE0("No items were selected!\n");
    }
    else
    {
        while(pos)
        {
            int nItem = m_ListCtrl.GetNextSelectedItem(pos);
            TRACE1("Item %d was selected!\n", nItem);
            ObjectNode* pNode = (ObjectNode*)m_ListCtrl.GetItemData(nItem);

            gcall.Step(pNode);
        }
    }

}

void CDataDlg::OnRclickList(NMHDR* pNMHDR, LRESULT* pResult)
{

    if(m_ListCtrl.GetSelectedCount() != 0)
    {
        POINT point;
        GetCursorPos(&point);

        CMenu menu;
        menu.LoadMenu(IDR_OBJECT);
        menu.GetSubMenu(0)->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);
    }

    *pResult = 0;
}


void CDataDlg::OnFindthenkill()
{
    //获取游戏外挂功能
    GamecallEx& gcall = *GamecallEx::GetInstance();
    //gcall.FindThenKill(0, 1000, modeNormal);

	gcall.Attack(0x5dc1);
	gcall.Attack(0x5dc1);
	gcall.Attack(0x5dc1);
	gcall.Attack(0x5dc1);
}

void CDataDlg::OnHookAcceptquest()
{
    UpdateData(TRUE);
    if(m_bHook_Accquest)
        GameHook::GetInstance()->aeQuestHook.hook();
    else
        GameHook::GetInstance()->aeQuestHook.unhook();
}

void CDataDlg::OnHookstrike()
{
    POSITION pos = m_ListCtrl.GetFirstSelectedItemPosition();

    while(pos)
    {
        int nItem = m_ListCtrl.GetNextSelectedItem(pos);
        ObjectNode* pNode = (ObjectNode*)m_ListCtrl.GetItemData(nItem);

        GameHook::GetInstance()->m_ObjAddrVec.push_back(pNode->ObjAddress);
    }
}

void CDataDlg::OnHookCombat()
{

    UpdateData(TRUE);

    if(m_bHook_Combat)
    {
        GameHook::GetInstance()->m_ObjAddrVec.clear();
        GameHook::GetInstance()->backupCombat = GameHook::GetInstance()->CombatHook.hook();
    }
    else
    {
        GameHook::GetInstance()->CombatHook.unhook();
    }
}


void CDataDlg::ShowHook(TCHAR* pszFormat, ...)
{
    TCHAR buffer[BUFSIZ] = {0};

    va_list argptr;
    va_start(argptr, pszFormat);
    wvsprintf(buffer, pszFormat, argptr);
    va_end(argptr);

    _tcscat(buffer, _T("\r\n"));

    m_pDbgPage->m_strInfo += buffer;
    m_pDbgPage->UpdateData(FALSE);
}

void CDataDlg::OnBossBombat()
{
    theApp.m_pWgDlg->m_pWorkThread->PostThreadMessage(WM_WORKTHREAD_TESTCOMBATBOSS, (WPARAM)this, 0);
}


void CDataDlg::OnSelchangeTab1(NMHDR* pNMHDR, LRESULT* pResult)
{
    int inIndex = m_TabCtrl.GetCurSel();
    if(inIndex == 0)
    {
        m_pDbgPage->ShowWindow(SW_SHOW);
        m_pLuaPage->ShowWindow(SW_HIDE);
    }
    else if(inIndex == 1)
    {
        m_pDbgPage->ShowWindow(SW_HIDE);
        m_pLuaPage->ShowWindow(SW_SHOW);
    }
    *pResult = 0;
}

void CDataDlg::OnGotoback() 
{
    //获取游戏外挂功能
    GamecallEx& gcall = *GamecallEx::GetInstance();
    
    POSITION pos = m_ListCtrl.GetFirstSelectedItemPosition();
    if(pos == NULL)
    {
        TRACE0("No items were selected!\n");
    }
    else
    {
        while(pos)
        {
            int nItem = m_ListCtrl.GetNextSelectedItem(pos);
            TRACE1("Item %d was selected!\n", nItem);
            ObjectNode* pNode = (ObjectNode*)m_ListCtrl.GetItemData(nItem);
            
            gcall.SteptoBack(pNode);
        }
    }
}
