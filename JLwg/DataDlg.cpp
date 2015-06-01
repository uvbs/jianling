// DataDlg1.cpp : implementation file
//

#include "stdafx.h"
#include "Jlwg.h"
#include "JLDlg.h"
#include "DataDlg.h"
#include "GameHook.h"
#include "GameConfig.h"
#include "ConfigQhPage.h"
#include "LuaPage.h"
#include "ToolDlg.h"
#include "GamecallEx.h"

#include <winternl.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


TCHAR* cli_AllObject[] = {{_T("地址")},
    {_T("名字")},
    {_T("ID")},
    {_T("目标ID")},
    {_T("类型")},
    {_T("血量")},
    {_T("名字ID")},
    {_T("坐标")}
};

TCHAR* cli_RangeObject[] = {{_T("地址")},
    {_T("名字")},
    {_T("ID")},
    {_T("对象目标")},
    {_T("类型")},
    {_T("血量")},
    {_T("距离")},
    {_T("坐标")},
    {_T("怪物")},
    {_T("面向")}
};

//技能 需要的控件列
TCHAR* cli_Bar[] = {{_T("名称")},
    {_T("地址")},
    {_T("id")}
};

TCHAR* cli_Strike[] = {{_T("技能名")},
    {_T("冷却")},
    {_T("可用")},
    {_T("id")},
};

TCHAR* cli_Quest[] = {{_T("名称")},
    {_T("步骤")},
    {_T("描述")}
};

TCHAR* cli_Team[] = {{_T("名字")},
    {_T("指针")},
    {_T("当前血值")},
    {_T("最大血值")},
    {_T("Id")},
    {_T("Id2")},
    {_T("坐标")},
    {_T("面向")},
    {_T("距离")},
    {_T("等级")},
    {_T("线路")}
};

TCHAR* cli_TaskItem[] = {{_T("名称")},
    {_T("距离")},
    {_T("坐标")},
    {_T("类型")}
};


TCHAR* cli_Bag[] = {{_T("名称")},
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

TCHAR* cli_Loots[] = {{_T("地址")},
    {_T("名称")},
    {_T("坐标")},
    {_T("距离")}
};



typedef enum _MEMORY_INFORMATION_CLASS
{
    MemoryBasicInformation,
    MemoryWorkingSetList,
    MemorySectionName
} MEMORY_INFORMATION_CLASS;

typedef NTSTATUS(WINAPI* ZWQUERYVIRTUALMEMORY)(
    IN HANDLE ProcessHandle,
    IN PVOID BaseAddress,
    IN MEMORY_INFORMATION_CLASS MemoryInformationClass,
    OUT PVOID MemoryInformation,
    IN ULONG MemoryInformationLength,
    OUT PULONG ReturnLength OPTIONAL);

typedef struct MEMORY_SECTION_NAME
{
    UNICODE_STRING SectionFileName;
    WCHAR       NameBuffer[ANYSIZE_ARRAY];
}* PMEMORY_SECTION_NAME;


VOID EnumProcessForModule()
{

    //按惯例函数头部创建一些需要的局部变量,虽然C++有个优点可以随时随地创建,但是我不喜欢那么做,为了函数的整体环境规划清爽,不然怕城管来砸,

    ZWQUERYVIRTUALMEMORY QueryVirtualMemoryFunction = NULL;
    DWORD Index = 0;
    NTSTATUS NtStatus = 0;
    MEMORY_BASIC_INFORMATION InfoMation;
    BYTE Buffer[MAX_PATH * 2 + 4] = {0};
    PUNICODE_STRING SectionName = NULL;
    CString ModuleAddress;
    CString ModuleName;



    QueryVirtualMemoryFunction = (ZWQUERYVIRTUALMEMORY)::GetProcAddress(GetModuleHandle(_T("ntdll.dll")), //ntdll.dll=地府
                                 "ZwQueryVirtualMemory"); //ZwQueryVirtualMemory=鬼魂名


    //为了尽量做一个严谨的程序员,我们要尽量对每一步工作的有效性作下判断,这是很有好处的
    if(QueryVirtualMemoryFunction == NULL)//判断它是否有了灵魂,
    {
        AfxMessageBox(_T("别瞎TM扯淡啦！"));
        //如果没有,那啥都别想啦,一切工作都要靠它来完成你不能让一个死人来干活吧
    }
    else //呵呵,哥们如果你还没死,那就别歇着啦,帮兄弟点忙吧。。。
    {
        for(Index; Index < 0x80000000; Index += 0x1000)
        {
            NtStatus = QueryVirtualMemoryFunction(
                           (HANDLE) - 1, //因为我们是注入的,所以-1就代表当前进程的句柄,HOHO,i love dll
                           (PULONG)Index,  //工作地址哟,第一次从0x00000000开始,第二次从0x00001000
                           MemoryBasicInformation, //记得不？枚举类型,普查嘛,要有目的的查呀,他就代表我们的目的
                           &InfoMation, //第四个局部变量,你把它理解成移动硬盘好啦,查到的数据放到里面,回来交给我们
                           sizeof(InfoMation),  //你要告诉工人。你给了他一个多大的移动硬盘才行,HOHO
                           NULL); //最后一个参数我们用不到,无视它,

            if(NtStatus >= 0)
            {
                //Type就表示这些人的类型啦,如果是暴民,那我们就要严肃的处理啦,MEM_IMAGE这样的就表示暴民啦,HOHO,开个玩笑,其实它是0x1000这个大小的
                //一块内存的描述标志,比如这块内存的标志是MEM_IMAGE哪就说明他是一个我们要的模块啦

                if(InfoMation.Type == MEM_IMAGE)
                {


                    if((DWORD)InfoMation.AllocationBase == Index)
                    {

                        NtStatus = QueryVirtualMemoryFunction(
                                       (HANDLE) - 1, //不变
                                       (PULONG)Index, //模块地址啦,
                                       MemorySectionName, //看见了吗,我们换了一个命令让他做不同的工作(内存节名枚举)
                                       Buffer,
                                       sizeof(Buffer),//解释过了。
                                       NULL);

                        if(NtStatus >= 0)
                        {

                            SectionName = (PUNICODE_STRING)Buffer;
                            ModuleName = SectionName->Buffer;
                            ModuleAddress.Format(_T("%x"), Index);

                            TRACE(_T("%08x: %s"), Index, ModuleName);

                            if(ModuleName.Find(_T("wow64cpu")) != -1)
                            {
                                BYTE ori[] = "\xea\x1e\x27\x80\x74";

                                DWORD dwOld;
                                VirtualProtect((LPVOID)(Index + 0x2320), 5, PAGE_EXECUTE_READWRITE, &dwOld);

                                //memcpy((void *)(Index + 0x2320), ori, sizeof(ori));
                                AfxMessageBox(_T("done!"));
                            }

                        }
                    }
                }
            }
        }
    }
}



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
    //hand = INVALID_HANDLE_VALUE;
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


BEGIN_MESSAGE_MAP(CDataDlg, CDialog
                     )
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
    ON_UPDATE_COMMAND_UI(ID_HOOKSTRIKE, OnUpdateHookstrike)
    ON_BN_CLICKED(IDC_CALLTOOL, OnCalltool)
    ON_BN_CLICKED(ID_FINDTHENKILLaa, OnBnClickedFindthenkillaa)
    ON_BN_CLICKED(IDC_BUTTON1, OnBnClickedButton1)
    ON_BN_CLICKED(IDC_BUTTON2, OnBnClickedButton2)
    ON_WM_TIMER()
//}}AFX_MSG_MAP
    ON_BN_CLICKED(IDC_BUTTON3, &CDataDlg::OnBnClickedButton3)
    ON_BN_CLICKED(IDC_BUTTON4, &CDataDlg::OnBnClickedButton4)
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CDataDlg message handlers

void CDataDlg::CheckHook()
{

    if(m_bHook_Combat)
    {
        GameHook::GetInstance()->CombatHook.unhook();
    }

    if(m_bHook_Accquest)
    {
        GameHook::GetInstance()->aeQuestHook.unhook();
    }

    if(m_bHook_Dundi)
    {
        GameHook::GetInstance()->DundiHook.unhook();
    }

    if(m_bHook_Pickup1)
    {
        GameHook::GetInstance()->Yicjw.unhook();
    }

    if(m_bHook_quest)
    {
        GameHook::GetInstance()->deQuestHook.unhook();
    }

    if(m_bHook_Weaquit)
    {
        GameHook::GetInstance()->WearHook.unhook();
    }

    if(m_bHook_step)
    {
        GameHook::GetInstance()->stepHook.unhook();
    }

}

void CDataDlg::AddInfo(const TCHAR szFormat[], ...)
{
    TCHAR buffer[BUFSIZ] = {0};

    va_list argptr;
    va_start(argptr, szFormat);
    wvsprintf(buffer, szFormat, argptr);
    va_end(argptr);

    _tcscat(buffer, _T("\r\n"));

    CEdit* pEdit = (CEdit*)m_pDbgPage->GetDlgItem(IDC_EDITINFO);
    int inLen = pEdit->GetWindowTextLength();
    pEdit->SetSel(inLen, inLen);
    pEdit->ReplaceSel(buffer);

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
    m_ComBox.AddString(_T("遍历队伍信息"));

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

    m_pLuaPage->SetWindowPos(NULL, rect.left, rect.top + 20, 0, 0, SWP_NOSIZE);
    m_pDbgPage->SetWindowPos(NULL, rect.left, rect.top + 20, 0, 0, SWP_NOSIZE);
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

    AddInfo(_T("角色地址: %x"), gcall.GetPlayerDataAddr());
    AddInfo(_T("角色名: %s"), gcall.GetPlayerName());
    AddInfo(_T("角色ID: %d"), gcall.GetPlayerID());
    AddInfo(_T("角色地图ID: %d"), gcall.GetCityID());
    AddInfo(_T("角色魔法: %d"), gcall.GetPlayerMana());
    AddInfo(_T("角色等级: %d"), gcall.GetPlayerLevel());
    AddInfo(_T("角色血量: %d"), gcall.GetPlayerHealth());
    AddInfo(_T("角色最大血量: %d"), gcall.GetPlayerMaxHealth());
    AddInfo(_T("角色内力: %d"), gcall.GetPlayerMana());
    AddInfo(_T("角色红心数量: %d"), gcall.GetPlarerRedHeart());
    AddInfo(_T("角色最大体力: %d"), (int)gcall.GetPlayerMaxVit());
    AddInfo(_T("角色体力: %d"), (int)gcall.GetPlayerVit());
    AddInfo(_T("角色视角: %d"), (int)gcall.GetPlayerViewPoint());
    AddInfo(_T("角色战斗状态: %d"), (int)gcall.GetPlayerFightingStatus());
    AddInfo(_T("角色释放技能状态: %d"), gcall.GetPlayerSkillStatus());
    AddInfo(_T("角色是否忙碌: %d"), gcall.GetPlayerBusy());
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


    for(DWORD i = 0; i < RangeObject.size(); i++)
    {

        ObjectNode* pNode = RangeObject[i];


        //地址
        CString strAddr;
        strAddr.Format(_T("%08x"), pNode);
        m_ListCtrl.InsertItem(i, strAddr);


        DWORD type = gcall.GetObjectType(pNode->ObjAddress);


        //名称
        wchar_t* pText = gcall.GetObjectName(pNode->ObjAddress);
        m_ListCtrl.SetItemText(i, 1, pText);

        CString strTemp;
        strTemp.Format(_T("%d"), pNode->id);
        m_ListCtrl.SetItemText(i, 2, strTemp);

        if(type == 0x4 || type == 1 || type == 2)
        {
            DWORD TargetId = gcall.GetObjectTargetId(pNode->ObjAddress);
            strTemp.Format(_T("%d"), TargetId);
            m_ListCtrl.SetItemText(i, 3, strTemp);
        }

        strTemp.Format(_T("%d"), type);
        m_ListCtrl.SetItemText(i, 4, strTemp);

        if(type == 0x4 || type == 1 || type == 2)
        {
            strTemp.Format(_T("%d"), gcall.GetObjectHP(pNode->ObjAddress));
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
}

void CDataDlg::InertBagItem(DWORD i, _BAGSTU& BagBuff)
{
    //物品名称
    m_ListCtrl.InsertItem(i, BagBuff.name);

    CString strLast;
    strLast.Format(_T("%d"), BagBuff.CurDur);
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

    BagVector BagVec;
    gcall.GetAllBodyEquipToVector(BagVec);

    for(DWORD i = 0; i < BagVec.size(); i++)
    {
        InertBagItem(i, BagVec[i]);

    }
}


void CDataDlg::PrintfRangeTaskItem()
{
    //获取游戏外挂功能
    GamecallEx& gcall = *GamecallEx::GetInstance();


    std::vector < ObjectNode* > RangeObject;
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

    std::vector < Tree* > AllUI;
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

    TaskVector task;
    gcall.GetAcceptedQuestToVector(task);


    CString strTemp;
    for(int i = 0; i < task.size(); i++)
    {

        m_ListCtrl.InsertItem(i, task[i].nName);

        strTemp.Format(_T("%d"), task[i].Step);
        m_ListCtrl.SetItemText(i, 1, strTemp);

        strTemp.Format(_T("%s"), task[i].StepName);
        m_ListCtrl.SetItemText(i, 2, strTemp);

    }

}

//遍历背包
void CDataDlg::PrintfBag()
{

    //获取游戏外挂功能
    GamecallEx& gcall = *GamecallEx::GetInstance();

    std::vector <_BAGSTU> RangeObject;
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


    ObjectVector RangeObject;
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


    StrikeVector JnVec;
    gcall.GetStrikeToVector(JnVec);

    CString strTemp;
    for(int i = 0; i < JnVec.size(); i++)
    {

        m_ListCtrl.InsertItem(i, JnVec[i].name);

        strTemp = JnVec[i].bCD == TRUE ? _T("冷却完毕") : _T("冷却中");
        m_ListCtrl.SetItemText(i, 1, strTemp);

        strTemp = JnVec[i].bAviable == TRUE ? _T("可用") : _T("不可用");
        m_ListCtrl.SetItemText(i, 2, strTemp);

        strTemp.Format(_T("%d"), JnVec[i].id);
        m_ListCtrl.SetItemText(i, 3, strTemp);

    }

}

void CDataDlg::PrintfRangeMonster(BOOL bApplyConfig)
{
    UpdateData();

    //获取游戏外挂功能
    GamecallEx& gcall = *GamecallEx::GetInstance();

    ObjectVector RangeObject;
    gcall.GetRangeMonsterToVector(gcall.GetObjectBinTreeBaseAddr(), m_nRange, RangeObject);
    if(RangeObject.size() < 1)
    {
        return;
    }

    if(bApplyConfig)
    {
        gcall.Kill_ApplyConfig(RangeObject);
    }


    //判续对象, 根据距离
    std::sort(RangeObject.begin(), RangeObject.end(), GamecallEx::UDgreater);

    CString strTemp;
    for(int i = 0; i < RangeObject.size(); i++)
    {
        ObjectNode* pNode = RangeObject[i];

        //地址
        strTemp.Format(_T("%08x"), pNode->ObjAddress);
        m_ListCtrl.InsertItem(i, strTemp);

        //名称
        TCHAR* pText = (LPTSTR)gcall.GetObjectName(pNode->ObjAddress);
        m_ListCtrl.SetItemText(i, 1, pText);

        strTemp.Format(_T("%d"), pNode->id);
        m_ListCtrl.SetItemText(i, 2, strTemp);

        strTemp.Format(_T("%d"), pNode->id2);
        m_ListCtrl.SetItemText(i, 3, strTemp);

        UCHAR type = gcall.GetObjectType(pNode->ObjAddress);
        strTemp.Format(_T("%d"), type);
        m_ListCtrl.SetItemText(i, 4, strTemp);

        strTemp.Format(_T("%x"), gcall.GetObjectTargetId(pNode->ObjAddress));
        m_ListCtrl.SetItemText(i, 5, strTemp);

        if(type == 0x4 || type == 1 || type == 2)
        {
            strTemp.Format(_T("%d"), gcall.GetObjectHP(pNode->ObjAddress));
            m_ListCtrl.SetItemText(i, 6, strTemp);
        }

        //坐标和距离
        fPosition pos;
        if(gcall.GetObjectPos(pNode, &pos))
        {
            fPosition mypos;
            gcall.GetPlayerPos(&mypos);

            strTemp.Format(_T("%d"), (DWORD)gcall.CalcC(pos, mypos));
            m_ListCtrl.SetItemText(i, 7, strTemp);


            strTemp.Format(_T("x:%d y:%d z:%d"), (int)pos.x, (int)pos.y, (int)pos.z);
            m_ListCtrl.SetItemText(i, 8, strTemp);
        }



        //索引
        int suoyin = gcall.GetIndexByType(pNode->ObjAddress);
        strTemp.Format(_T("%d"), suoyin == -1 ? -1 : suoyin);
        m_ListCtrl.SetItemText(i, 9, strTemp);

        if(type == 0x4 || type == 1 || type == 2)
        {
            //怪物面向
            strTemp.Format(_T("%d"), gcall.GetObjectView(pNode->ObjAddress));
            m_ListCtrl.SetItemText(i, 10, strTemp);
        }

        m_ListCtrl.SetItemData(i, (DWORD)pNode);
    }

}


//遍历范围内的对象
void CDataDlg::PrintfRangeObject()
{

    UpdateData();

    //获取游戏外挂功能
    GamecallEx& gcall = *GamecallEx::GetInstance();


    ObjectVector RangeObject;
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

        strTemp.Format(_T("%x"), pNode->id);
        m_ListCtrl.SetItemText(index, 2, strTemp);

        strTemp.Format(_T("%d"), gcall.GetObjectTargetId(pNode->ObjAddress));
        m_ListCtrl.SetItemText(index, 3, strTemp);

        strTemp.Format(_T("%d"), type);
        m_ListCtrl.SetItemText(index, 4, strTemp);

        if(type == 0x4 || type == 1 || type == 2)
        {
            strTemp.Format(_T("%d"), gcall.GetObjectHP(pNode->ObjAddress));
            m_ListCtrl.SetItemText(index, 5, strTemp);
        }



        //距离
        //坐标

        fPosition pos;
        if(gcall.GetObjectPos(pNode, &pos))
        {
            strTemp.Format(_T("x:%d y:%d z:%d"), (int)pos.x, (int)pos.y, (int)pos.z);
            m_ListCtrl.SetItemText(index, 6, strTemp);

            strTemp.Format(_T("%d"), (DWORD)gcall.CalcC(pos, mypos));
            m_ListCtrl.SetItemText(index, 7, strTemp);
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

        strTemp.Format(_T("%d"), gcall.GetObjectView(pNode->ObjAddress));
        m_ListCtrl.SetItemText(index, 9, strTemp);


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


void CDataDlg::InsertColumnHelper(TCHAR* column[], int
                                  count)
{

    for(
        int i = 0;
        i < count;
        i++)
    {
        m_ListCtrl.
        DeleteColumn(i);
        m_ListCtrl.
        InsertColumn(i, column[i]
                    );
    }
}


void CDataDlg::OnSelchangeComboDatatype()
{
    UpdateData(TRUE);


    CString strSel;
    m_ComBox.GetLBText(m_ComBox.GetCurSel(), strSel);

    m_ListCtrl.DeleteAllItems();
    for(; ;)
    {
        if(m_ListCtrl.DeleteColumn(0) == FALSE)
        {
            break;
        }
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
    else if(strSel == _T("遍历队伍信息"))
    {
        InsertColumnHelper(cli_Team, sizeof(cli_Team) / sizeof(TCHAR*));
        PrintfTeaminfo();
    }


    int i = 0;
    for(; ;)
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

    GameConfig* pConfig = GameConfig::GetInstance();

    //配置对话框
    CPropertySheet sheet(_T("配置文件"), this);
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
        pConfig->SaveConfig();
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
    UpdateData(TRUE);
    if(m_bHook_Pickup1)
    {
        GameHook::GetInstance()->backupYiciJianWu = GameHook::GetInstance()->Yicjw.hook();

    }
    else
    {
        GameHook::GetInstance()->Yicjw.unhook();
    }
}

//npc接任务
void CDataDlg::OnHookDequest()
{
    UpdateData(TRUE);
    if(m_bHook_quest)
    {
        GameHook::GetInstance()->backupQuest = GameHook::GetInstance()->deQuestHook.hook();

    }
    else
    {
        GameHook::GetInstance()->deQuestHook.unhook();
    }
}

void CDataDlg::OnHookChuanzhuangbei()
{
    UpdateData(TRUE);
    if(m_bHook_Weaquit)
    {
        GameHook::GetInstance()->backupWearEquipment = GameHook::GetInstance()->WearHook.hook();

    }
    else
    {
        GameHook::GetInstance()->WearHook.unhook();
    }

}

void CDataDlg::OnHookDundi()
{
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
    CEdit* pEdit = (CEdit*)m_pDbgPage->GetDlgItem(IDC_EDITINFO);
    pEdit->SetSel(0, -1);
    pEdit->Clear();
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
    DWORD Kill_Result = 0;


    while(gcall.GetObjectByName(L"咒術師", 3000) != NULL)
    {
        gcall.NewSpend(2.5);
        gcall.Stepto(-4057, -51895, 4653, 10, 10, 3000); //啊胶
        gcall.Stepto(6609, -42911, 5433, 10, 10, 3000); //赤胶
        gcall.Stepto(15200, -55500, 5620, 10, 10, 3000); //太尚
        gcall.NewSpend(1);


        //如果范围内找到幻魔先打
        if(gcall.GetObjectByName(L"幻魔", 1400))
        {
            gcall.ClearCustom();
            gcall.AddCustomKill(L"幻魔", KILLFIRST);
            gcall.AddCustomKill(L"飛魔", DONTKILL);
            gcall.AddCustomKill(L"戮魔", DONTKILL);
            gcall.AddCustomKill(L"骨魔", DONTKILL);
            gcall.AddCustomKill(L"悍魔", DONTKILL);
            gcall.AddCustomKill(L"咒術師", DONTKILL);
            gcall.AddCustomKill(L"封魔核", DONTKILL);
            gcall.AddCustomKill(L"邵俊喜", DONTKILL);
            gcall.AddCustomKill(L"邵俊方", DONTKILL);
            gcall.AddCustomKill(L"方玉蘭", DONTKILL);
            gcall.AddCustomKill(L"克克爆", DONTKILL);
            gcall.AddCustomKill(L"熱風", DONTKILL);
            gcall.AddCustomKill(L"戰無懼", DONTKILL);
            gcall.AddCustomKill(L"西風", DONTKILL);
            gcall.AddCustomKill(L"克克爆", DONTKILL);
            gcall.AddCustomKill(L"克克擊", DONTKILL);
            gcall.AddCustomKill(L"克克焰", DONTKILL);
            gcall.AddCustomKill(L"鱷鮫天王", DONTKILL);
            gcall.AddCustomKill(L"馬塔", DONTKILL);
            gcall.AddCustomKill(L"馬杜", DONTKILL);
            gcall.AddCustomKill(L"克克焰", DONTKILL);
            Kill_Result = gcall.FindThenKill_S(1400, modeAoe | modeNormal);
            if(Kill_Result == RESULT_KILL_PLAYDEAD)
            {
                TRACE(_T("人物死亡"));
                return;
            }
        }
        else if(gcall.GetObjectByName(L"飛魔", 1500))
        {
            gcall.ClearCustom();
            gcall.AddCustomKill(L"幻魔", KILLFIRST);
            gcall.AddCustomKill(L"飛魔", KILLFIRST);
            gcall.AddCustomKill(L"戮魔", DONTKILL);
            gcall.AddCustomKill(L"骨魔", DONTKILL);
            gcall.AddCustomKill(L"悍魔", DONTKILL);
            gcall.AddCustomKill(L"咒術師", DONTKILL);
            gcall.AddCustomKill(L"封魔核", DONTKILL);
            gcall.AddCustomKill(L"邵俊喜", DONTKILL);
            gcall.AddCustomKill(L"邵俊方", DONTKILL);
            gcall.AddCustomKill(L"方玉蘭", DONTKILL);
            gcall.AddCustomKill(L"克克爆", DONTKILL);
            gcall.AddCustomKill(L"熱風", DONTKILL);
            gcall.AddCustomKill(L"戰無懼", DONTKILL);
            gcall.AddCustomKill(L"西風", DONTKILL);
            gcall.AddCustomKill(L"克克爆", DONTKILL);
            gcall.AddCustomKill(L"克克擊", DONTKILL);
            gcall.AddCustomKill(L"克克焰", DONTKILL);
            gcall.AddCustomKill(L"鱷鮫天王", DONTKILL);
            gcall.AddCustomKill(L"馬塔", DONTKILL);
            gcall.AddCustomKill(L"馬杜", DONTKILL);
            gcall.AddCustomKill(L"克克焰", DONTKILL);
            Kill_Result = gcall.FindThenKill_S(1000, modeNormal);
            if(Kill_Result == RESULT_KILL_PLAYDEAD)
            {
                TRACE(_T("人物死亡"));
                return;
            }
        }
        else if(gcall.GetObjectByName(L"血魔犬", 1500))
        {
            gcall.ClearCustom();
            gcall.AddCustomKill(L"幻魔", KILLFIRST);
            gcall.AddCustomKill(L"飛魔", KILLFIRST);
            gcall.AddCustomKill(L"血魔犬", KILLFIRST);
            gcall.AddCustomKill(L"戮魔", DONTKILL);
            gcall.AddCustomKill(L"骨魔", DONTKILL);
            gcall.AddCustomKill(L"悍魔", DONTKILL);
            gcall.AddCustomKill(L"咒術師", DONTKILL);
            gcall.AddCustomKill(L"封魔核", DONTKILL);
            gcall.AddCustomKill(L"邵俊喜", DONTKILL);
            gcall.AddCustomKill(L"邵俊方", DONTKILL);
            gcall.AddCustomKill(L"方玉蘭", DONTKILL);
            gcall.AddCustomKill(L"克克爆", DONTKILL);
            gcall.AddCustomKill(L"熱風", DONTKILL);
            gcall.AddCustomKill(L"戰無懼", DONTKILL);
            gcall.AddCustomKill(L"西風", DONTKILL);
            gcall.AddCustomKill(L"克克爆", DONTKILL);
            gcall.AddCustomKill(L"克克擊", DONTKILL);
            gcall.AddCustomKill(L"克克焰", DONTKILL);
            gcall.AddCustomKill(L"鱷鮫天王", DONTKILL);
            gcall.AddCustomKill(L"馬塔", DONTKILL);
            gcall.AddCustomKill(L"馬杜", DONTKILL);
            gcall.AddCustomKill(L"克克焰", DONTKILL);
            Kill_Result = gcall.FindThenKill_S(1000, modeNormal);
            if(Kill_Result == RESULT_KILL_PLAYDEAD)
            {
                TRACE(_T("人物死亡"));
                return;
            }
        }

        else if(gcall.GetObjectByName(L"戮魔", 400))
        {
            gcall.ClearCustom();
            gcall.AddCustomKill(L"幻魔", KILLFIRST);
            gcall.AddCustomKill(L"飛魔", KILLFIRST);
            gcall.AddCustomKill(L"血魔犬", KILLFIRST);
            //gcall.AddCustomKill(L"戮魔", DONTKILL);
            gcall.AddCustomKill(L"骨魔", DONTKILL);
            gcall.AddCustomKill(L"悍魔", DONTKILL);
            gcall.AddCustomKill(L"咒術師", DONTKILL);
            gcall.AddCustomKill(L"封魔核", DONTKILL);
            gcall.AddCustomKill(L"邵俊喜", DONTKILL);
            gcall.AddCustomKill(L"邵俊方", DONTKILL);
            gcall.AddCustomKill(L"方玉蘭", DONTKILL);
            gcall.AddCustomKill(L"克克爆", DONTKILL);
            gcall.AddCustomKill(L"熱風", DONTKILL);
            gcall.AddCustomKill(L"戰無懼", DONTKILL);
            gcall.AddCustomKill(L"西風", DONTKILL);
            gcall.AddCustomKill(L"克克爆", DONTKILL);
            gcall.AddCustomKill(L"克克擊", DONTKILL);
            gcall.AddCustomKill(L"克克焰", DONTKILL);
            gcall.AddCustomKill(L"鱷鮫天王", DONTKILL);
            gcall.AddCustomKill(L"馬塔", DONTKILL);
            gcall.AddCustomKill(L"馬杜", DONTKILL);
            gcall.AddCustomKill(L"克克焰", DONTKILL);
            Kill_Result = gcall.FindThenKill_S(500,  modeNormal, 155, FALSE, TRUE);
            if(Kill_Result == RESULT_KILL_PLAYDEAD)
            {
                TRACE(_T("人物死亡"));
                return;
            }
        }
        else
        {
            //if(gcall.GetPlayerFightingStatus() == FALSE)
            //{

            //}
            gcall.ClearCustom();
            gcall.AddCustomKill(L"幻魔", KILLFIRST);
            gcall.AddCustomKill(L"飛魔", KILLFIRST);
            gcall.AddCustomKill(L"血魔犬", KILLFIRST);
            //gcall.AddCustomKill(L"戮魔", DONTKILL);
            //gcall.AddCustomKill(L"骨魔", DONTKILL);
            gcall.AddCustomKill(L"悍魔", DONTKILL);
            gcall.AddCustomKill(L"咒術師", DONTKILL);
            gcall.AddCustomKill(L"封魔核", DONTKILL);
            gcall.AddCustomKill(L"邵俊喜", DONTKILL);
            gcall.AddCustomKill(L"邵俊方", DONTKILL);
            gcall.AddCustomKill(L"方玉蘭", DONTKILL);
            gcall.AddCustomKill(L"克克爆", DONTKILL);
            gcall.AddCustomKill(L"熱風", DONTKILL);
            gcall.AddCustomKill(L"戰無懼", DONTKILL);
            gcall.AddCustomKill(L"西風", DONTKILL);
            gcall.AddCustomKill(L"克克爆", DONTKILL);
            gcall.AddCustomKill(L"克克擊", DONTKILL);
            gcall.AddCustomKill(L"克克焰", DONTKILL);
            gcall.AddCustomKill(L"鱷鮫天王", DONTKILL);
            gcall.AddCustomKill(L"馬塔", DONTKILL);
            gcall.AddCustomKill(L"馬杜", DONTKILL);
            gcall.AddCustomKill(L"克克焰", DONTKILL);
            Kill_Result = gcall.FindThenKill_S(600, modeNormal, 155, FALSE, TRUE);
            if(Kill_Result == RESULT_KILL_PLAYDEAD)
            {
                TRACE(_T("人物死亡"));
                return;
            }
        }
    }

    TRACE(_T("遍历不到咒術師"));

    return;


    //彩虹湖
    while(1)
    {
        gcall.Stepto(47820, -27420, -4818, 10, 10, 3000);
        gcall.FindThenKill(0, 300, modeNormal | modePickup);
        gcall.Stepto(47832, -26837, -4818, 10, 10, 3000);
        gcall.FindThenKill(0, 300, modeNormal | modePickup);
        gcall.Stepto(48224, -26502, -4818, 10, 10, 3000);
        gcall.FindThenKill(0, 300, modeNormal | modePickup);
        gcall.Stepto(48733, -26449, -4818, 10, 10, 3000);
        gcall.FindThenKill(0, 300, modeNormal | modePickup);
        gcall.Stepto(49140, -26806, -4818, 10, 10, 3000);
        gcall.FindThenKill(0, 300, modeNormal | modePickup);
        gcall.Stepto(49167, -27362, -4818, 10, 10, 3000);
        gcall.FindThenKill(0, 300, modeNormal | modePickup);
        gcall.Stepto(48815, -27746, -4818, 10, 10, 3000);
        gcall.FindThenKill(0, 300, modeNormal | modePickup);
    }


}

void CDataDlg::OnHookAcceptquest()
{
    UpdateData(TRUE);
    if(m_bHook_Accquest)
    {
        GameHook::GetInstance()->aeQuestHook.hook();
    }
    else
    {
        GameHook::GetInstance()->aeQuestHook.unhook();
    }
}


//钩选中的怪的技能释放
void CDataDlg::OnHookstrike()
{
    POSITION pos = m_ListCtrl.GetFirstSelectedItemPosition();
    if(pos)
    {
        ObjectVector& HookVec = GameHook::GetInstance()->m_ObjAddrVec;
        int nItem = m_ListCtrl.GetNextSelectedItem(pos);
        ObjectNode* pNode = (ObjectNode*)m_ListCtrl.GetItemData(nItem);

        CMenu menu;
        menu.LoadMenu(IDR_OBJECT);
        if(menu.GetMenuState(ID_HOOKSTRIKE, MF_BYCOMMAND) == MF_CHECKED)
        {

            //从钩子vec中删掉
            for(std::vector<ObjectNode*>::iterator it = HookVec.begin(); it != HookVec.end(); it++)
            {
                if(*it == pNode)
                {
                    HookVec.erase(it);
                    break;
                }
            }
        }
        GameHook::GetInstance()->m_ObjAddrVec.push_back(pNode);
    }
    else
    {
        AfxMessageBox(_T("选个要钩的怪"));
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

    CEdit* pEdit = (CEdit*)m_pDbgPage->GetDlgItem(IDC_EDITINFO);
    TCHAR buffer[BUFSIZ] = {0};

    va_list argptr;
    va_start(argptr, pszFormat);
    wvsprintf(buffer, pszFormat, argptr);
    va_end(argptr);

    _tcscat(buffer, _T("\r\n"));

    int inLen = pEdit->GetWindowTextLength();
    pEdit->SetSel(inLen, -1);
    pEdit->ReplaceSel(buffer);
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

void CDataDlg::OnUpdateHookstrike(CCmdUI* pCmdUI)
{
    pCmdUI->SetCheck(0);

    //获取游戏外挂功能
    GamecallEx& gcall = *GamecallEx::GetInstance();

    POSITION pos = m_ListCtrl.GetFirstSelectedItemPosition();
    if(pos)
    {
        int nItem = m_ListCtrl.GetNextSelectedItem(pos);
        ObjectNode* pNode = (ObjectNode*)m_ListCtrl.GetItemData(nItem);

        for(int i = 0; i < GameHook::GetInstance()->m_ObjAddrVec.size(); i++)
        {
            if(GameHook::GetInstance()->m_ObjAddrVec[i] == pNode)
            {
                pCmdUI->SetCheck();
                break;
            }
        }
    }

}

void CDataDlg::PrintfTeaminfo()
{
    //获取游戏外挂功能
    GamecallEx& gcall = *GamecallEx::GetInstance();
    TeamVector tv;
    BOOL flag = gcall.GetPartyInfo(tv);
    if(flag)
    {
        int size = tv.size();
        CString strTemp;
        for(int i = 0; i < size; i++)
        {
            m_ListCtrl.InsertItem(i, tv[i].name);

            strTemp.Format(_T("%x"), tv[i].PAddress);
            m_ListCtrl.SetItemText(i, 1, strTemp);

            strTemp.Format(_T("%d"), tv[i].CurrLife);
            m_ListCtrl.SetItemText(i, 2, strTemp);

            strTemp.Format(_T("%d"), tv[i].MaxLife);
            m_ListCtrl.SetItemText(i, 3, strTemp);

            strTemp.Format(_T("%x"), tv[i].ID);
            m_ListCtrl.SetItemText(i, 4, strTemp);

            strTemp.Format(_T("%x"), tv[i].ID2);
            m_ListCtrl.SetItemText(i, 5, strTemp);

            strTemp.Format(_T("%d,%d,%d"), (int)tv[i].Pos.y, (int)tv[i].Pos.x, (int)tv[i].Pos.z);
            m_ListCtrl.SetItemText(i, 6, strTemp);

            strTemp.Format(_T("%d"), tv[i].Angle);
            m_ListCtrl.SetItemText(i, 7, strTemp);

            strTemp.Format(_T("%d"), tv[i].Range);
            m_ListCtrl.SetItemText(i, 8, strTemp);

            strTemp.Format(_T("%d"), tv[i].LV);
            m_ListCtrl.SetItemText(i, 9, strTemp);

            strTemp.Format(_T("%d"), tv[i].Channel);
            m_ListCtrl.SetItemText(i, 10, strTemp);
        }
    }
}

void CDataDlg::OnBnClickedFindthenkillaa()
{

}

void CDataDlg::OnBnClickedFindthenkill2()
{

}

HANDLE hand = INVALID_HANDLE_VALUE;


UINT testThread(LPVOID ll)
{
    //CDataDlg* dlg = (CDataDlg*)ll;
    GamecallEx& gcall = *GamecallEx::GetInstance();
    gcall.Party_KillObject();
    //dlg->hand = INVALID_HANDLE_VALUE;
    hand = INVALID_HANDLE_VALUE;
    return 0;
}
void CDataDlg::OnBnClickedButton1()
{
    if(hand == INVALID_HANDLE_VALUE)
    {
        hand = AfxBeginThread(testThread, this)->m_hThread;
    }
}


void CDataDlg::OnBnClickedButton2()
{
    if(hand != INVALID_HANDLE_VALUE)
    {
        TerminateThread(hand, 0);
        hand = INVALID_HANDLE_VALUE;
    }
}

void CDataDlg::OnCalltool()
{
    ShowWindow(SW_HIDE);

    CToolDlg dlg;
    dlg.DoModal();

    ShowWindow(SW_SHOW);
}

void CDataDlg::OnTimer(UINT nIDEvent)
{
    CDialog::OnTimer(nIDEvent);
}

void CDataDlg::OnBnClickedButton3()
{
    GamecallEx& gcall = *GamecallEx::GetInstance();
    gcall.ChangeZ_Status(TRUE);
    gcall.ChangeHeight(0);
    MessageBox(L"摇奖完", L"装八卦", MB_OK);
    gcall.ChangeZ_Status(FALSE);
    gcall.ChangeHeight(-1071);
    //MessageBox(L"摇奖完", L"装八卦", MB_OK);
}

void CDataDlg::OnBnClickedButton4()
{
    //TRACE(_T("策划"));
    // TODO: 在此添加控件通知处理程序代码
    GamecallEx& gcall = *GamecallEx::GetInstance();
    DWORD cs = 0;
    int Kill_result = -1;
    fPosition Mpos;
    Mpos.y = 24908;
    Mpos.x = -68282;
    Mpos.z = 6548;//门口的怪

    fPosition Mpos1;
    Mpos1.y = 25720;
    Mpos1.x = -67972;
    Mpos1.z = 6540;//里面的怪

    fPosition Mpos2;
    Mpos2.y = 25160;
    Mpos2.x = -69108;
    Mpos2.z = 6548;//心里的怪


    fPosition NothingPos;
    NothingPos.y = 24720;
    NothingPos.x = -68168;
    NothingPos.z = 6553;//外面的怪
    fPosition NothingPos1;
    NothingPos1.y = 25532;
    NothingPos1.x = -69350;
    NothingPos1.z = 6556;//里面的怪
    fPosition NothingPos2;
    NothingPos2.y = 24435;
    NothingPos2.x = -68114;
    NothingPos2.z = 6549;//心里的怪




	//TRACE(_T("NothingPos:%d"),gcall.GetObjectCountByName(L"濁魔血殭屍", NothingPos, 450));
	//TRACE(_T("NothingPos1:%d"),gcall.GetObjectCountByName(L"濁魔血殭屍", NothingPos1, 450));
	//TRACE(_T("NothingPos2:%d"),gcall.GetObjectCountByName(L"濁魔血殭屍", NothingPos2, 450));
	//return;

    while(true)
    {
        //1
        if(gcall.GetObjectCountByName(L"鬼門萬年殭屍", Mpos, 200) >= 1)
        {
            gcall.NewSpend(2.5);
            gcall.Stepto(26814, -67554, 6612, 10, 10, 3000);
            gcall.Stepto(25847, -67613, 6535, 10, 10, 3000);
            gcall.NewSpend(1);
            Kill_result = gcall.FindThenKill(0, 450, modeAoe | modeNormal);
            TRACE(_T("Mpos,Kill_result:%d"), Kill_result);
            if(Kill_result == RESULT_KILL_PLAYDEAD)
            {
                goto PlayDead;
            }
            gcall.NewSpend(2.5);
            gcall.Stepto(25847, -67613, 6535, 10, 10, 3000);
            gcall.Stepto(27317, -67795, 6859, 10, 10, 3000);
            gcall.NewSpend(1);
        }
        else if(gcall.GetObjectCountByName(L"鬼門萬年殭屍", Mpos1, 200) >= 1)
        {
            gcall.NewSpend(2.5);
            gcall.Stepto(26582, -68265, 6586, 10, 10, 3000);
            gcall.Stepto(26466, -68565, 6593, 10, 10, 3000);
            gcall.Stepto(26135, -69033, 6575, 10, 10, 3000);
            gcall.Stepto(25532, -69350, 6556, 10, 10, 3000);
            gcall.NewSpend(1);
            Kill_result = gcall.FindThenKill(0, 450, modeAoe | modeNormal);
            TRACE(_T("Mpos1,Kill_result:%d"), Kill_result);
            if(Kill_result == RESULT_KILL_PLAYDEAD)
            {
                goto PlayDead;
            }
            gcall.NewSpend(2.5);
            gcall.Stepto(26135, -69033, 6575, 10, 10, 3000);
            gcall.Stepto(26466, -68565, 6593, 10, 10, 3000);
            gcall.Stepto(26582, -68265, 6586, 10, 10, 3000);
            gcall.Stepto(27317, -67795, 6859, 10, 10, 3000);
            gcall.NewSpend(1);
        }
        else  if(gcall.GetObjectCountByName(L"鬼門萬年殭屍", Mpos2, 200) >= 1)
        {
            gcall.NewSpend(2.5);
            gcall.Stepto(26887, -67459, 6627, 10, 10, 3000);
            gcall.Stepto(26485, -66968, 6544, 10, 10, 3000);
            gcall.Stepto(25737, -66641, 6438, 10, 10, 3000);
            gcall.Stepto(24993, -66721, 6449, 10, 10, 3000);
            gcall.Stepto(24550, -66912, 6514, 10, 10, 3000);
            gcall.Stepto(24435, -68114, 6549, 10, 10, 3000);
            gcall.NewSpend(1);
            Kill_result = gcall.FindThenKill(0, 450, modeAoe | modeNormal);
            TRACE(_T("Mpos2,Kill_result:%d"), Kill_result);
            if(Kill_result == RESULT_KILL_PLAYDEAD)
            {
                goto PlayDead;
            }

            gcall.NewSpend(2.5);
            gcall.Stepto(24435, -68114, 6549, 10, 10, 3000);
            gcall.Stepto(24550, -66912, 6514, 10, 10, 3000);
            gcall.Stepto(24993, -66721, 6449, 10, 10, 3000);
            gcall.Stepto(25737, -66641, 6438, 10, 10, 3000);
            gcall.Stepto(26485, -66968, 6544, 10, 10, 3000);
            gcall.Stepto(27317, -67795, 6859, 10, 10, 3000);
            gcall.NewSpend(1);
        }

        if(gcall.GetObjectCountByName(L"濁魔血殭屍", NothingPos, 500) < 1)
        {
            if(gcall.GetObjectCountByName(L"濁魔血殭屍", NothingPos1, 500) < 1)
            {
                if(gcall.GetObjectCountByName(L"濁魔血殭屍", NothingPos2, 500) < 1)
                {
                    TRACE(_T("打完收工"));
                    break;
                }
            }
        }

PlayDead:
        if(Kill_result == RESULT_KILL_PLAYDEAD)
        {
            Sleep(2000);
            gcall.FuHuo();

            //执行死亡走路
        }
        Sleep(100);
    }


}
