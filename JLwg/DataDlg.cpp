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
    {_T("��ַ")},
    {_T("����")},
    {_T("ID")},
    {_T("ID2")},
    {_T("����")},
    {_T("Ѫ��")},
    {_T("����")},
    {_T("����")}
};

TCHAR* cli_RangeObject[] =
{
    {_T("��ַ")},
    {_T("����")},
    {_T("ID")},
    {_T("ID2")},
    {_T("����")},
    {_T("Ѫ��")},
    {_T("����")},
    {_T("����")},
    {_T("�Ƿ����")},
    {_T("����")},
    {_T("����")}
};

//���� ��Ҫ�Ŀؼ���
TCHAR* cli_Bar[] =
{
    {_T("����")},
    {_T("��ַ")},
    {_T("id")}
};

TCHAR* cli_Strike[] =
{
    {_T("������")},
    {_T("��ȴ")},
    {_T("����")},
    {_T("����")},
    {_T("ID_1")},
    {_T("ID_2")}
};

TCHAR* cli_Quest[] =
{
    {_T("��������")},
    {_T("����")},
    {_T("������־")},
    {_T("��������")},
    {_T("����ID")},
};



TCHAR* cli_TaskItem[] =
{
    {_T("����")},
    {_T("����")},
    {_T("����")},
    {_T("����")}
};


TCHAR* cli_Bag[] =
{
    {_T("����")},
    {_T("�;�")},
    {_T("�ȼ�")},
    {_T("����")},
    {_T("����")},
    {_T("λ��")},
    {_T("��ַ")},
    {_T("��ӡ")},
    {_T("����")},
    {_T("��ɫ")},
    {_T("�ܾ���")},
    {_T("����")},
    {_T("����")},
    {_T("����")}

};

TCHAR* cli_Loots[] =
{
    {_T("��ַ")},
    {_T("����")},
    {_T("����")},
    {_T("����")}
};


//���캯��
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


    m_ComBox.AddString(_T("���ж���"));
    m_ComBox.AddString(_T("δ������"));
    m_ComBox.AddString(_T("����"));
    m_ComBox.AddString(_T("��Χ����"));
    m_ComBox.AddString(_T("����"));
    m_ComBox.AddString(_T("����"));
    m_ComBox.AddString(_T("����"));
    m_ComBox.AddString(_T("��Χ����"));
    m_ComBox.AddString(_T("������Ʒ"));
    m_ComBox.AddString(_T("װ��"));
    m_ComBox.AddString(_T("��Χ����"));
    m_ComBox.AddString(_T("��Χ����(�����ļ�)"));

    m_ListCtrl.SetExtendedStyle(LVS_EX_FULLROWSELECT);

    //����lua�͵�����Ϣ����ҳ��
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

    m_TabCtrl.InsertItem(0, _T("����"));
    m_TabCtrl.InsertItem(1, _T("�ű�"));

    m_pLuaPage->Create(CLuaPage::IDD, this);
    m_pDbgPage->Create(CDbgPage::IDD, this);

    m_pLuaPage->SetWindowPos(NULL, rect.left + 5, rect.top + 20, 0, 0, SWP_NOSIZE);
    m_pDbgPage->SetWindowPos(NULL, rect.left + 5, rect.top + 20, 0, 0, SWP_NOSIZE);
    m_pDbgPage->ShowWindow(SW_SHOW);

    CheckHook();

    //��ʼ������
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
            //��ʾ��������ֵ��༭�ؼ����㸴��
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
    //��ȡ��Ϸ��ҹ���
    GamecallEx& gcall = *GamecallEx::GetInstance();

    fPosition PlayerPos;
    gcall.GetPlayerPos(&PlayerPos);

    sPosition PlayerPos2;
    gcall.GetPlayerPos2(&PlayerPos2);

    AddInfo(_T("��ɫ��: %s"), gcall.GetPlayerName());
    AddInfo(_T("��ɫ��ͼID: %d"), gcall.GetCityID());
    AddInfo(_T("��ɫħ��: %d"), gcall.GetPlayerMana());
    AddInfo(_T("��ɫ�ȼ�: %d"), gcall.GetPlayerLevel());
    AddInfo(_T("��ɫѪ��: %d"), gcall.GetPlayerHealth());
    AddInfo(_T("��ɫ���Ѫ��: %d"), gcall.GetPlayerMaxHealth());
    AddInfo(_T("��ɫ����: %d"), gcall.GetPlayerMana());
    AddInfo(_T("��ɫID: %d"), gcall.GetPlayerID());
    AddInfo(_T("��ɫ�������: %d"), (int)gcall.GetPlayerMaxVit());
    AddInfo(_T("��ɫ����: %d"), (int) gcall.GetPlayerVit());
    AddInfo(_T("��ɫ�ӽ�: %d"), (int)gcall.GetPlayerViewPoint());
    AddInfo(_T("����UI״̬: %d"), gcall.GetPlayerQuestUIStatus());
    AddInfo(_T("����UI״̬2: %d"), gcall.GetPlayerQuestUIStatusts());
    AddInfo(_T("LoadingMap: %d"), gcall.isLoadingMap());

    AddInfo(_T("��ɫ����: x:%d y:%d z:%d"), (int)PlayerPos.x, (int)PlayerPos.y, (int)PlayerPos.z);
    AddInfo(_T("��ɫ����2: x:%d y:%d z:%d"), (int)PlayerPos2.x, (int)PlayerPos2.y, (int)PlayerPos2.z);

}


//����ȫ������
void CDataDlg::PrintfAllObject()
{
    //��ȡ��Ϸ��ҹ���
    GamecallEx& gcall = *GamecallEx::GetInstance();


    ObjectVector RangeObject;
    gcall.GetAllObjectToVector(gcall.GetObjectBinTreeBaseAddr(), RangeObject);

    m_ListCtrl.SetRedraw(FALSE);
    for(DWORD i = 0; i < RangeObject.size(); i++)
    {

        ObjectNode* pNode = RangeObject[i];


        //��ַ
        CString strAddr;
        strAddr.Format(_T("%08x"), pNode->ObjAddress);
        m_ListCtrl.InsertItem(i, strAddr);



        DWORD type = gcall.GetObjectType(pNode->ObjAddress);


        //����
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


        //��ʾ���������
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
    //��Ʒ����
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

//������ɫװ��
void CDataDlg::PrintfPlayerEquip()
{
    //��ȡ��Ϸ��ҹ���
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
    //��ȡ��Ϸ��ҹ���
    GamecallEx& gcall = *GamecallEx::GetInstance();


    std::vector<ObjectNode*> RangeObject;
    gcall.GetRangeTaskItemToVectr(RangeObject, m_nRange);

    std::sort(RangeObject.begin(), RangeObject.end(), GamecallEx::UDgreater);
    fPosition fmypos;
    gcall.GetPlayerPos(&fmypos);

    for(DWORD i = 0; i < RangeObject.size(); i++)
    {
        ObjectNode* pNode = RangeObject[i];



        //����
        wchar_t* name = gcall.GetObjectName(pNode->ObjAddress);
        if(name != NULL)
        {
            m_ListCtrl.InsertItem(i, name);
        }


        //����
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


//ȡ������UI
void CDataDlg::PrintfAllUI()
{

    //��ȡ��Ϸ��ҹ���
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

//��������
void CDataDlg::PrintfQuest()
{

    //��ȡ��Ϸ��ҹ���
    GamecallEx& gcall = *GamecallEx::GetInstance();

    int TaskNum = 53;
    DWORD pStartAddr = gcall.GetTaskStartAddr();  //��ȡ����ʼ��ַ


    CString strTemp;
    for(int i = 0; i < TaskNum; i++)
    {
        //DWORD *pAddr        =     gcall.GetTaskPresentAddr(i, pStartAddr);  //��õ�ǰ�����ַ
        DWORD ID = gcall.GetTaskID(i, pStartAddr);  //��õ�ǰ����ID
        DWORD name_id = gcall.GetTaskNameID(i, pStartAddr);  //��õ�ǰ��������ID
        DWORD info = gcall.GetPresentTaskIndexes(i, pStartAddr);  //��õ�ǰ�����ڼ���С����
        DWORD endflag = gcall.GetPresentTaskEndFlag(i, pStartAddr, info);  //��õ�ǰС���������־
        DWORD num = gcall.GetPresentTaskNum(i, pStartAddr, info);  //��õ�ǰС�����Ѿ���Ĺ�����

        wchar_t* name = (wchar_t*)gcall.sendcall(id_msg_GatTaskName, (LPVOID)name_id);
        if(name)
        {
            m_ListCtrl.InsertItem(i, name);
        }
        else
        {
            //�������
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

//��������
void CDataDlg::PrintfBag()
{

    //��ȡ��Ϸ��ҹ���
    GamecallEx& gcall = *GamecallEx::GetInstance();

    std::vector<_BAGSTU> RangeObject;
    gcall.GetAllGoodsToVector(RangeObject);

    CString strTemp;
    for(DWORD i = 0; i < RangeObject.size(); i++)
    {
        InertBagItem(i, RangeObject[i]);
    }
}

//��������
void CDataDlg::PrintfRangeLoot()
{
    //��ȡ��Ϸ��ҹ���
    GamecallEx& gcall = *GamecallEx::GetInstance();


    std::vector<ObjectNode*> RangeObject;
    gcall.GetRangeLootObjectToVector(m_nRange, RangeObject);

    CString strTemp;
    for(DWORD index = 0; index < RangeObject.size(); index++)
    {
        ObjectNode* pNode = RangeObject[index];

        //�����ַ
        strTemp.Format(_T("%08x"), (DWORD)pNode->ObjAddress);
        m_ListCtrl.InsertItem(index, strTemp);


        //����
        TCHAR* pText = (LPTSTR)gcall.GetObjectName(pNode->ObjAddress);
        m_ListCtrl.SetItemText(index, 1, pText);


        //����
        fPosition mypos;
        gcall.GetPlayerPos(&mypos);

        fPosition tarpos;
        gcall.GetObjectPos(pNode, &tarpos);


        strTemp.Format(_T("%d"), (DWORD)gcall.CalcC(tarpos, mypos));
        m_ListCtrl.SetItemText(index, 2, strTemp);



        strTemp.Format(_T("x:%d y:%d z:%d"), (int)tarpos.x, (int)tarpos.y, (int)tarpos.z);
        m_ListCtrl.SetItemText(index, 3, strTemp);


        //����
        strTemp.Format(_T("%08x"), gcall.GetIndexByType(pNode->ObjAddress));
        m_ListCtrl.SetItemText(index, 7, strTemp);


        m_ListCtrl.SetItemData(index, (DWORD)pNode);
    }
}


//������������
void CDataDlg::PrintfStrike()
{

    //��ȡ��Ϸ��ҹ���
    GamecallEx& gcall = *GamecallEx::GetInstance();


    std::vector<STRIKEINFO> RangeObject;
    gcall.GetStrikeToVector(RangeObject);

    CString strTemp;
    for(DWORD i = 0; i < RangeObject.size(); i++)
    {
        int id1 = RangeObject[i].id1;
        int id2 = RangeObject[i].id2;

        wchar_t* name = RangeObject[i].stName.name;

        //��ַ
        m_ListCtrl.InsertItem(i, name);

        strTemp.Format(_T("%d"), RangeObject[i].cd);
        m_ListCtrl.SetItemText(i, 1, strTemp);



        if(RangeObject[i].isBlock == 0)
        {

            strTemp.Format(_T("������"));
            m_ListCtrl.SetItemText(i, 2, strTemp);
            strTemp.Format(_T("δ����"));
        }
        else
        {
            if(RangeObject[i].canUse == 0)
            {
                strTemp.Format(_T("��ʹ��"));
            }
            else
            {
                strTemp.Format(_T("������"));
            }
            //strTemp.Format(_T("%d"), RangeObject[i].canUse);
            m_ListCtrl.SetItemText(i, 2, strTemp);
            strTemp.Format(_T("�ѽ���"));
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

    //��ȡ��Ϸ��ҹ���
    GamecallEx& gcall = *GamecallEx::GetInstance();

    std::vector<ObjectNode*> RangeObject;
    gcall.GetRangeMonsterToVector(m_nRange, RangeObject);

    if(bApplyConfig)
    {
        gcall.Kill_ApplyConfig(RangeObject);
    }
    //��������, ���ݾ���
    std::sort(RangeObject.begin(), RangeObject.end(), GamecallEx::UDgreater);

    CString strTemp;
    for(DWORD index = 0; index < RangeObject.size(); index++)
    {
        ObjectNode* pNode = RangeObject[index];

        //��ַ
        strTemp.Format(_T("%08x"), pNode->ObjAddress);
        m_ListCtrl.InsertItem(index, strTemp);

        //����
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

        //����;���
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




        //�Ƿ��ǹ���
        m_ListCtrl.SetItemText(index, 8, L"��");

        //����
        int suoyin = gcall.GetIndexByType(pNode->ObjAddress);
        if(suoyin != -1)
        {
            strTemp.Format(_T("%d"), suoyin);
            m_ListCtrl.SetItemText(index, 9, strTemp);
        }

        //��������
        strTemp.Format(_T("%d"), gcall.GetObjectView(pNode->ObjAddress));
        m_ListCtrl.SetItemText(index, 10, strTemp);


        m_ListCtrl.SetItemData(index, (DWORD)pNode);
    }

}




//������Χ�ڵĶ���
void CDataDlg::PrintfRangeObject()
{

    UpdateData();

    //��ȡ��Ϸ��ҹ���
    GamecallEx& gcall = *GamecallEx::GetInstance();


    std::vector<ObjectNode*> RangeObject;
    gcall.GetRangeObjectToVector(gcall.GetObjectBinTreeBaseAddr(), m_nRange, RangeObject);

    fPosition mypos;
    gcall.GetPlayerPos(&mypos);

    CString strTemp;
    for(DWORD index = 0; index < RangeObject.size(); index++)
    {
        ObjectNode* pNode = RangeObject[index];

        //�����ַ
        strTemp.Format(_T("%08x"), (DWORD)pNode->ObjAddress);
        m_ListCtrl.InsertItem(index, strTemp);


        UCHAR type = gcall.GetObjectType(pNode->ObjAddress);
        strTemp.Format(_T("%d"), type);



        //����
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



        //����
        //����

        fPosition pos;
        if(gcall.GetObjectPos(pNode, &pos))
        {
            strTemp.Format(_T("x:%d y:%d z:%d"), (int)pos.x, (int)pos.y, (int)pos.z);
            m_ListCtrl.SetItemText(index, 7, strTemp);

            strTemp.Format(_T("%d"), (DWORD)gcall.CalcC(pos, mypos));
            m_ListCtrl.SetItemText(index, 6, strTemp);
        }


        //�Ƿ��ǹ���
        if(gcall.isCanKill(pNode))
        {
            m_ListCtrl.SetItemText(index, 8, _T("��"));
        }
        else
        {
            m_ListCtrl.SetItemText(index, 8, _T("��"));
        }



        //����
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
    //��ȡ��Ϸ��ҹ���
    GamecallEx& gcall = *GamecallEx::GetInstance();

    UpdateData(TRUE);
    if(m_nRange == 0)
    {
        AfxMessageBox(_T("��������0ֵ"));
    }
    else if(m_nRange > 50)
    {
        AfxMessageBox(_T("̫����, ���ܻ������Ϸ"));
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

    if(strSel == _T("����"))
    {
        InsertColumnHelper(cli_Bag, sizeof(cli_Bag) / sizeof(TCHAR*));
        PrintfBag();

    }
    else if(strSel == _T("���ж���"))
    {
        InsertColumnHelper(cli_AllObject, sizeof(cli_AllObject) / sizeof(TCHAR*));
        PrintfAllObject();

    }
    else if(strSel == _T("����"))
    {
        InsertColumnHelper(cli_Bar, sizeof(cli_Bar) / sizeof(TCHAR*));
        PrintfAllUI();
    }
    else if(strSel == _T("��Χ����"))
    {
        InsertColumnHelper(cli_RangeObject, sizeof(cli_RangeObject) / sizeof(TCHAR*));
        PrintfRangeObject();
    }
    else if(strSel == _T("������Ʒ"))
    {
        InsertColumnHelper(cli_TaskItem, sizeof(cli_TaskItem) / sizeof(TCHAR*));
        PrintfRangeTaskItem();
    }
    else if(strSel == _T("װ��"))
    {
        InsertColumnHelper(cli_Bag, sizeof(cli_Bag) / sizeof(TCHAR*));
        PrintfPlayerEquip();
    }
    else if(strSel == _T("����"))
    {
        InsertColumnHelper(cli_Strike, sizeof(cli_Strike) / sizeof(TCHAR*));
        PrintfStrike();
    }
    else if(strSel == _T("��Χ����"))
    {
        InsertColumnHelper(cli_Loots, sizeof(cli_Loots) / sizeof(TCHAR*));
        PrintfRangeLoot();
    }
    else if(strSel == _T("��Χ����"))
    {
        InsertColumnHelper(cli_RangeObject, sizeof(cli_RangeObject) / sizeof(TCHAR*));
        PrintfRangeMonster();
    }
    else if(strSel == _T("��Χ����(�����ļ�)"))
    {
        InsertColumnHelper(cli_RangeObject, sizeof(cli_RangeObject) / sizeof(TCHAR*));
        PrintfRangeMonster(TRUE);
    }
    else if(strSel == _T("����"))
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

    //���öԻ���
    CPropertySheet sheet(_T("�����ļ�"));
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


//��·����
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

//npc������
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

    //��ȡ��Ϸ��ҹ���
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
    //��ȡ��Ϸ��ҹ���
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
    //��ȡ��Ϸ��ҹ���
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
    //��ȡ��Ϸ��ҹ���
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
