// DataDlg1.cpp : implementation file
//

#include "stdafx.h"
#include "jlwg.h"
#include "DataDlg.h"


#include "ConfigItemPage.h"
#include "ConfigObjPage.h"
#include "ConfigQhPage.h"
#include "ConfigSheet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



static CDataDlg* g_pDataDlg = NULL;
/////////////////////////////////////////////////////////////////////////////
// CDataDlg dialog


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

	g_pDataDlg = this;
}


void CDataDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDataDlg)
	DDX_Control(pDX, IDC_LIST, m_ListCtrl);
	DDX_Control(pDX, IDC_EDITINFO, m_hEdit);
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
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()



static TCHAR* cli_AllObject[] =
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

static TCHAR* cli_RangeObject[] =
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
    {_T("����")}
};

//���� ��Ҫ�Ŀؼ���
static TCHAR* cli_Bar[] =
{
    {_T("����")},
    {_T("��ַ")},
    {_T("id")}
};

static TCHAR* cli_Strike[] =
{
    {_T("������")},
    {_T("��ȴ")},
    {_T("����")},
    {_T("����")},
    {_T("ID_1")},
    {_T("ID_2")}
};

static TCHAR* cli_Quest[] =
{
    {_T("��������")},
    {_T("����")},
    {_T("������־")},
    {_T("��������")},
    {_T("����ID")},
};



static TCHAR* cli_TaskItem[] =
{
    {_T("����")},
    {_T("����")},
    {_T("����")},
    {_T("����")}
};


static TCHAR* cli_Bag[] =
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

static TCHAR* cli_Loots[] =
{
    {_T("��ַ")},
    {_T("����")},
    {_T("����")},
    {_T("����")}
};



//��·�����Ľṹ
typedef struct _SENDSTEP
{
    DWORD unknow;
    float x;
    float y;
    float z;
}SENDSTEP, PSENDSTEP;



static void log2(TCHAR szFormat[], ...)
{
    TCHAR buffer[BUFSIZ] = {0};
    
    va_list argptr;
    va_start(argptr, szFormat);
    wvsprintf(buffer, szFormat, argptr);
    va_end(argptr);
    
    _tcscat(buffer, _T("\r\n"));
    
	int len = g_pDataDlg->m_hEdit.GetWindowTextLength();
	g_pDataDlg->m_hEdit.SetSel(len, -1);
	g_pDataDlg->m_hEdit.ReplaceSel(buffer);
}



static void *backupSendStep;
static void *backupWearEquipment;
static void *backupYiciJianWu;
static void *backupDunDi;
static void *backupQuest;
static void *backupCombat;
static DWORD g_RecordStepRange = 200;
static fPosition g_fmypos;
static void __stdcall mySendStep(SENDSTEP *ftarpos)
{

	static BOOL bFirst = TRUE;
	if(bFirst)
	{
		log2(_T("gcall.Stepto(%d,%d,%d);"), (int)ftarpos->y, (int)ftarpos->x, (int)ftarpos->z);
		bFirst = !bFirst;
	}


    fPosition tarpos = {ftarpos->x, ftarpos->y, ftarpos->z};
    
	BYTE* backup = (BYTE*)ftarpos;

    //�೤�������һ��
    if(gcall.CalcC(g_fmypos, tarpos) >= g_RecordStepRange)
    {
        log2(_T("gcall.Stepto(%d,%d,%d);"), (int)ftarpos->y, (int)ftarpos->x, (int)ftarpos->z);
        g_fmypos.x = ftarpos->x;
        g_fmypos.y = ftarpos->y;
        g_fmypos.z = ftarpos->z;
    }
    

	//׷��
	FILE* file = _tfopen(gcall.GetLujingTest(), _T("a+b"));
	if(file == NULL)
	{
		OutputDebugString(_T("���ļ�ʧ��"));
		goto exitf;
	}

    int i;
	for(i = 0; i < 34; i++)
	{

		BYTE buff[512];
		//�Ӳ����и���512�ֽڵ�������
		memcpy(buff, backup, 512);

		//����512�ֽ�д���ļ���
		size_t count = fwrite(buff, 512, 1, file);
		if(count == 0)
		{
			TRACE(_T("д��ʧ��"));
			break;
		}

		fflush(file);
		backup += 512;
	}

	fclose(file);


exitf:
   __asm
    {
        leave;
        jmp backupSendStep;
    }
}


//��װ��
static void __stdcall myWearEquipment(DWORD argv1, DWORD value, DWORD argv3, DWORD itemtype)
{
    
    BOOL bFind = FALSE;
    //����value�ĸ�16λ �Ǳ�����Ʒ��id;
    //ͨ����������ȡ����
    std::vector<_BAGSTU> GoodsVector;
    gcall.GetAllGoodsToVector(GoodsVector);
    
    wchar_t *name = NULL;
    DWORD GridPos = value >> 16;
    
    for(DWORD i = 0; i < GoodsVector.size(); i++)
    {
        if(GoodsVector[i].m_Info == GridPos)
        {
            bFind = TRUE;
            name = GoodsVector[i].name;
        }
    }
    
    if(bFind)
        log2(_T("gcall.WearEquipment(L%s, %d);"), name, itemtype);
    else
    {
        log2(_T("��װ��ʧ��"));
    }
    
    __asm
    {
        leave;
        jmp backupWearEquipment;
    }
}

std::vector<DWORD> g_ObjAddrVec;
static void __stdcall myCombatFilter()
{

	DWORD objAddr;
	DWORD id;
	__asm
	{
		mov objAddr, ebx;
	}
	__asm 
	{
		mov eax,[esi+0x10];
		mov id,eax;
	}
	
	for(int i = 0; i < g_ObjAddrVec.size(); i++){
		if(objAddr == g_ObjAddrVec[i]){
			log2(_T("%08x, ����: %d"), objAddr, id);
		}
	}

	__asm{
		leave;
		jmp backupCombat;
		}
		
}

//�������Ӻ���
static void __stdcall myYiCiJianWu(DWORD argv1, 
                            DWORD argv2, 
                            DWORD argv3, 
                            DWORD argv4, 
                            DWORD argv5)
{

    DWORD* pEsp = & argv1;
    log2(_T("dump stack"));
    
    for(int i = 0; i < 5; i++)
    {
        log2(_T("esp+%d %08x"), i, *(pEsp + i));
    }
    
    __asm
    {
        leave;
        jmp backupYiciJianWu;
    }
}



//�������Ӻ���
static void __stdcall myDunDi()
{
    DWORD eax_value;
    __asm
    {
        mov eax_value, eax;
    }
    
    log2(_T("eax = %08x"), eax_value);
    
 
    __asm
    {
        leave;
        jmp backupDunDi;
    }
}



//�������Ӻ���
static void __stdcall myDeliveQuest(DWORD unknow,
									DWORD questID, 
                             UCHAR questStep,
                             DWORD argv3,
                             DWORD argv4, 
                             DWORD npcid1,
                             DWORD npcid2)
{
    int edi_value;
    int i;


    __asm
    {
        __asm
        {
            mov edi_value, edi;
        }
        pushad;
    }
    
    //��������ֵ
    DWORD* pEsp = &questID;  
    pEsp += 1;
    
    
    log2(_T("dump stack"));
    for(i = 0; i < 8; i++)
    {
        log2(_T("esp+%d %08x"), i, *(pEsp + i));
    }
    
    log2(_T("mianban: %08x"), edi_value);
    BOOL bFined;
    bFined = FALSE;
    wchar_t* name = NULL;
    std::vector<ObjectNode *> RangeObject;
    
    gcall.GetAllObjectToVector(gcall.GetObjectBinTreeBaseAddr(), RangeObject);
    for(i = 0; i < RangeObject.size(); i++)
    {
        ObjectNode *pNode = RangeObject[i];
        
        if((pNode->id == npcid1) && (pNode->id2 == npcid2))
        {
            //ֻҪ�Աȵ�NPCID������ȥ
            name = gcall.GetObjectName(pNode->ObjAddress);
            bFined = TRUE;
            
            //�˴�break�߼�����
            break;
        }
    }
    
    if(bFined != TRUE)
    {
        log2(_T("û�б��������\nNPCID: %d, NPCID2: %d"), npcid1, npcid2);
    }
    
    //NPC��û������
    if(name == NULL)
    {
        name = L"NULL";
    }
    
    log2(_T("gcall.DeliverQuests(%d, %x, %s);"), questID, questStep, name);
    
    int result = MessageBox(NULL, _T("һ�ν�����CALLִ��\n\nȷ��: ������\nȡ��: ֹͣ��"),
        NULL, MB_OKCANCEL);
    
    if(result == IDOK)
    {
        __asm
        {
            popad;
            leave;
            jmp backupQuest;
        }
    }
    else
    {
        __asm
        {
            popad;
            leave;
            retn 32;
        }
    }
}


//�������Ӻ���
static void __stdcall myAcceptQuest(DWORD questID, 
                             UCHAR questStep, 
                             DWORD argv3, 
                             DWORD argv4, 
                             DWORD npcid1,
                             DWORD npcid2, 
                             DWORD argv7)
{
    DWORD* pEsp = &questID;
   
    log2(_T("dump stack"));
    for(int i = 0; i < 7; i++)
    {
        log2(_T("esp+%d %08x"), i, *(pEsp + i));
    }
    
    __asm
    {
        leave;
        retn 28;
    }
}



static CCHook stepHook((void *)shunyi_call, mySendStep);
static CCHook deQuestHook((void *)deliver_quest_call, myDeliveQuest);
static CCHook aeQuestHook((void *)npc_quest_call, myAcceptQuest);
static CCHook WearHook((void *)chuanzhuangbei_call, myWearEquipment);
static CCHook DundiHook((void *)dundi_call, myDunDi);
static CCHook Yicjw((void *)pickup1_call, myYiCiJianWu);
static CCHook CombatHook((void *)0x0047B948, myCombatFilter);


/////////////////////////////////////////////////////////////////////////////
// CDataDlg message handlers

void CDataDlg::CheckHook()
{
	if(m_bHook_Combat)
	{

	}
	if(m_bHook_Accquest)
	{
		aeQuestHook.unhook();
	}

	if(m_bHook_Dundi)
	{
		DundiHook.unhook();
	}

	if(m_bHook_Pickup1)
	{
		Yicjw.unhook();
	}

	if(m_bHook_quest)
	{
		deQuestHook.unhook();
	}

	if(m_bHook_Weaquit)
	{
		WearHook.unhook();
	}

	if(m_bHook_step)
	{
		stepHook.unhook();
	}


		
}


BOOL CDataDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
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
	CheckHook();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CDataDlg::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	NMHDR* pNMHdr = (NMHDR *)lParam;
	switch(pNMHdr->code)
	{
	case NM_CLICK:
		{
			//��ʾ��������ֵ��༭�ؼ����㸴��
			NMLISTVIEW *pItem = (NMLISTVIEW*)pNMHdr;
			CString strClick = m_ListCtrl.GetItemText(pItem->iItem, pItem->iSubItem);
			if(strClick.IsEmpty() == FALSE)
			{
				log2(_T("%s"), (LPCTSTR)strClick);
			}
		}
		break;
		
	}

	return CDialog::OnNotify(wParam, lParam, pResult);
}

void CDataDlg::OnGetpalyerinfo() 
{
	// TODO: Add your control notification handler code here
	fPosition PlayerPos;
	gcall.GetPlayerPos(&PlayerPos);
	
	sPosition PlayerPos2;
	gcall.GetPlayerPos2(&PlayerPos2);
	
	log2(_T("��ɫ��: %s"), gcall.GetPlayerName());
	log2(_T("��ɫ��ͼID: %d"), gcall.GetCityID());
	log2(_T("��ɫħ��: %d"), gcall.GetPlayerMana());
	log2(_T("��ɫ�ȼ�: %d"), gcall.GetPlayerLevel());
	log2(_T("��ɫѪ��: %d"), gcall.GetPlayerHealth());
	log2(_T("��ɫ���Ѫ��: %d"), gcall.GetPlayerMaxHealth());
	log2(_T("��ɫ����: %d"), gcall.GetPlayerMana());
	log2(_T("��ɫID: %d"), gcall.GetPlayerID());
	log2(_T("��ɫ�������: %d"),(int)gcall.GetPlayerMaxVit());
	log2(_T("��ɫ����: %d"),(int) gcall.GetPlayerVit());
	log2(_T("��ɫ�ӽ�: %d"), (int)gcall.GetPlayerViewPoint());
	log2(_T("����UI״̬: %d"), gcall.GetPlayerQuestUIStatus());
	log2(_T("����UI״̬2: %d"), gcall.GetPlayerQuestUIStatusts());
	log2(_T("��ɫ����: x:%d y:%d z:%d"), (int)PlayerPos.x, (int)PlayerPos.y, (int)PlayerPos.z);
	log2(_T("��ɫ����2: x:%d y:%d z:%d"), (int)PlayerPos2.x, (int)PlayerPos2.y, (int)PlayerPos2.z);
	
}

extern DWORD stdaa;
//����ȫ������
void CDataDlg::PrintfAllObject()
{
    std::vector<ObjectNode *> RangeObject;
    gcall.GetAllObjectToVector(gcall.GetObjectBinTreeBaseAddr(), RangeObject);
 
	m_ListCtrl.SetRedraw(FALSE); 
    for(DWORD i = 0; i < RangeObject.size(); i++)
    {
        
        ObjectNode *pNode = RangeObject[i];
        
        
        //��ַ
		CString strAddr;
		strAddr.Format(_T("%08x"), pNode->ObjAddress);
        m_ListCtrl.InsertItem(i, strAddr);
        


        DWORD type = gcall.GetObjectType(pNode->ObjAddress);


        //����
        wchar_t *pText = gcall.GetObjectName(pNode->ObjAddress);
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
		if(suoyin != -1){
			strTemp.Format(_T("%d"), suoyin);
			m_ListCtrl.SetItemText(i, 6, strTemp);
		}
        

        //��ʾ���������
        fPosition fpos;
		if(gcall.GetObjectPos(pNode, &fpos)){
			strTemp.Format(_T("x:%d y:%d z:%d"), (int)fpos.x, (int)fpos.y, (int)fpos.z);
			m_ListCtrl.SetItemText(i, 7, strTemp);
		}

		
		m_ListCtrl.SetItemData(i, (DWORD)pNode);
    }
	m_ListCtrl.SetRedraw(TRUE); 
}

void CDataDlg::InertBagItem(DWORD i, _BAGSTU &BagBuff)
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
    
    std::vector<_BAGSTU> GoodsItem;
    gcall.GetAllBodyEquipToVector(GoodsItem);

    for(DWORD i = 0; i < GoodsItem.size() ;i++)
    {
		InertBagItem(i, GoodsItem[i]);

    }
}


void CDataDlg::PrintfRangeTaskItem()
{
    std::vector<ObjectNode *> RangeObject;
    gcall.GetRangeTaskItemToVectr(RangeObject, m_nRange);
    
    std::sort(RangeObject.begin(), RangeObject.end(), GamecallEx::UDgreater);
    fPosition fmypos;
	gcall.GetPlayerPos(&fmypos);
    
    for(DWORD i = 0; i < RangeObject.size(); i++)
    {
        ObjectNode *pNode = RangeObject[i];
        
        
        
        //����
        wchar_t *name = gcall.GetObjectName(pNode->ObjAddress);
        if(name != NULL)
        {
            m_ListCtrl.InsertItem(i, name);
        }
        
        
        //����
        fPosition fpos;
		if(gcall.GetObjectPos(pNode, &fpos)){
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
	std::vector<Tree *> AllUI;
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
        
        wchar_t *name = (wchar_t *)gcall.sendcall(id_msg_GatTaskName, (LPVOID)name_id);
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
    std::vector<ObjectNode *> RangeObject;
    gcall.GetRangeLootObjectToVector(m_nRange, RangeObject);
    
	CString strTemp;
    for(DWORD index = 0; index < RangeObject.size(); index++)
    {
        ObjectNode *pNode = RangeObject[index];
        
        //�����ַ
		strTemp.Format(_T("%08x"), (DWORD)pNode->ObjAddress);
        m_ListCtrl.InsertItem(index, strTemp);
        
    
        //����
        TCHAR *pText = (LPTSTR)gcall.GetObjectName(pNode->ObjAddress);
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
    std::vector<STRIKEINFO> RangeObject;
    gcall.GetStrikeToVector(RangeObject);

    CString strTemp;
    for(DWORD i = 0; i < RangeObject.size(); i++)
    {
        int id1 = RangeObject[i].id1;
        int id2 = RangeObject[i].id2;
        
        wchar_t *name = RangeObject[i].stName.name;
        
        //��ַ
        m_ListCtrl.InsertItem(i, name);

		strTemp.Format(_T("%d"), RangeObject[i].cd);
        m_ListCtrl.SetItemText(i, 1, strTemp);

		

		if (RangeObject[i].isBlock == 0)
		{
			
			strTemp.Format(_T("������"));
			m_ListCtrl.SetItemText(i, 2, strTemp);
			strTemp.Format(_T("δ����"));
		}else
		{
			if (RangeObject[i].canUse == 0)
			{
				strTemp.Format(_T("��ʹ��"));
			}else
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

    std::vector<ObjectNode *> RangeObject;
    gcall.GetRangeMonsterToVector(m_nRange, RangeObject);

    if(bApplyConfig){
        gcall.Kill_ApplyConfig(RangeObject);
    }
	//��������, ���ݾ���
    std::sort(RangeObject.begin(), RangeObject.end(), GamecallEx::UDgreater);

	CString strTemp;
    for(DWORD index = 0; index < RangeObject.size(); index++)
    {
        ObjectNode *pNode = RangeObject[index];
        
        //��ַ
		strTemp.Format(_T("%08x"), pNode->ObjAddress);
        m_ListCtrl.InsertItem(index, strTemp);
        
        //����
        TCHAR *pText = (LPTSTR)gcall.GetObjectName(pNode->ObjAddress);
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
		if(gcall.GetObjectPos(pNode, &pos)){
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
		if(suoyin != -1){
			strTemp.Format(_T("%d"), suoyin);
			m_ListCtrl.SetItemText(index, 9, strTemp);
		}


		m_ListCtrl.SetItemData(index, (DWORD)pNode);
    }
   
}




//������Χ�ڵĶ���
void CDataDlg::PrintfRangeObject()
{
    
	UpdateData();

    std::vector<ObjectNode *> RangeObject;
    gcall.GetRangeObjectToVector(gcall.GetObjectBinTreeBaseAddr(), m_nRange, RangeObject);
    
	fPosition mypos;
	gcall.GetPlayerPos(&mypos);

	CString strTemp;
    for(DWORD index = 0; index < RangeObject.size(); index++)
    {
        ObjectNode *pNode = RangeObject[index];
        
        //�����ַ
		strTemp.Format(_T("%08x"), (DWORD)pNode->ObjAddress);
        m_ListCtrl.InsertItem(index, strTemp);
        
	
        UCHAR type = gcall.GetObjectType(pNode->ObjAddress);
        strTemp.Format(_T("%d"), type);



        //����
        wchar_t *pText = gcall.GetObjectName(pNode->ObjAddress);
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
		if(gcall.GetObjectPos(pNode, &pos)){
			strTemp.Format(_T("x:%d y:%d z:%d"), (int)pos.x, (int)pos.y, (int)pos.z);
			m_ListCtrl.SetItemText(index, 7, strTemp);

			strTemp.Format(_T("%d"), (DWORD)gcall.CalcC(pos, mypos));
			m_ListCtrl.SetItemText(index, 6, strTemp);
		}


		

        //�Ƿ��ǹ���
		if(gcall.isCanKill(pNode))
			m_ListCtrl.SetItemText(index, 8, L"��");
		else
			m_ListCtrl.SetItemText(index, 8, L"��");
        


        //����
		int suoyin = gcall.GetIndexByType(pNode->ObjAddress);
		if(suoyin != -1){
			strTemp.Format(_T("%d"), suoyin);
			m_ListCtrl.SetItemText(index, 9, strTemp);
		}
        


		m_ListCtrl.SetItemData(index, (DWORD)pNode);
	
    }
    
}

void CDataDlg::OnSpeedx() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	gcall.NewSpend((float)m_nRange);
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
	for(;;){
		if(m_ListCtrl.DeleteColumn(0) == FALSE)
			break;
	}

	if(strSel == _T("����"))
	{
		InsertColumnHelper(cli_Bag, sizeof(cli_Bag)/sizeof(TCHAR *));
		PrintfBag();

	}
	else if(strSel == _T("���ж���"))
	{
		InsertColumnHelper(cli_AllObject, sizeof(cli_AllObject)/sizeof(TCHAR *));
		PrintfAllObject();

	}
	else if(strSel == _T("����"))
	{
		InsertColumnHelper(cli_Bar, sizeof(cli_Bar)/sizeof(TCHAR *));
		PrintfAllUI();
	}
	else if(strSel == _T("��Χ����"))
	{
		InsertColumnHelper(cli_RangeObject, sizeof(cli_RangeObject)/sizeof(TCHAR *));
		PrintfRangeObject();
	}
	else if(strSel == _T("������Ʒ"))
	{
		InsertColumnHelper(cli_TaskItem, sizeof(cli_TaskItem)/sizeof(TCHAR *));
		PrintfRangeTaskItem();
	}
	else if(strSel == _T("װ��"))
	{
		InsertColumnHelper(cli_Bag, sizeof(cli_Bag)/sizeof(TCHAR *));
		PrintfPlayerEquip();
	}
	else if(strSel == _T("����"))
	{
		InsertColumnHelper(cli_Strike, sizeof(cli_Strike)/sizeof(TCHAR *));
		PrintfStrike();
	}
	else if(strSel == _T("��Χ����"))
	{
		InsertColumnHelper(cli_Loots, sizeof(cli_Loots)/sizeof(TCHAR *));
		PrintfRangeLoot();
	}
	else if(strSel == _T("��Χ����"))
	{
		InsertColumnHelper(cli_RangeObject, sizeof(cli_RangeObject)/sizeof(TCHAR *));
		PrintfRangeMonster();
	}
    else if(strSel == _T("��Χ����(�����ļ�)")){
        InsertColumnHelper(cli_RangeObject, sizeof(cli_RangeObject)/sizeof(TCHAR *));
        PrintfRangeMonster(TRUE);
    }
	else if(strSel == _T("����"))
	{
		InsertColumnHelper(cli_Quest, sizeof(cli_Quest)/sizeof(TCHAR *));
		PrintfQuest();
	}


	int i = 0;
	for(;;)
	{
		if(m_ListCtrl.SetColumnWidth(i++, LVSCW_AUTOSIZE_USEHEADER) == FALSE)
			break;
	}
		
}

void CDataDlg::OnBtnConfig() 
{
	// TODO: Add your control notification handler code here
	ShowWindow(SW_HIDE);
	CConfigSheet ConfigSheet;
	ConfigSheet.DoModal();
	ShowWindow(SW_SHOW);
}

void CDataDlg::OnRefresh() 
{
	// TODO: Add your control notification handler code here
	OnSelchangeComboDatatype();
}

void CDataDlg::OnHookSendstep() 
{
	
	UpdateData(TRUE);
	if(m_bHook_step)
	{
		backupSendStep = stepHook.hook();
	}
	else 
	{
		stepHook.unhook();
	}
	
}


void CDataDlg::OnHookYicijianwu() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if(m_bHook_Pickup1)
	{
		backupYiciJianWu = Yicjw.hook();
		
	}
	else
	{
		Yicjw.unhook();
	}
}

//npc������
void CDataDlg::OnHookDequest() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if(m_bHook_quest)
	{
		backupQuest = deQuestHook.hook();
		
	}
	else
	{
		deQuestHook.unhook();
	}
}

void CDataDlg::OnHookChuanzhuangbei() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if(m_bHook_Weaquit)
	{
		backupWearEquipment = WearHook.hook();
		
	}
	else
	{
		WearHook.unhook();
	}
	
}

void CDataDlg::OnHookDundi() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if(m_bHook_Dundi)
	{
		backupDunDi = DundiHook.hook();
		
	}
	else
	{
		DundiHook.unhook();
	}
	
}

BOOL CDataDlg::DestroyWindow() 
{
	// TODO: Add your specialized code here and/or call the base class

	CheckHook();
	return CDialog::DestroyWindow();
}

void CDataDlg::OnClr() 
{
	// TODO: Add your control notification handler code here
	m_hEdit.SetSel(0, -1);
	m_hEdit.Clear();
}

void CDataDlg::OnTurnto() 
{
	// TODO: Add your command handler code here
	
	POSITION pos = m_ListCtrl.GetFirstSelectedItemPosition();
	if (pos == NULL)
		TRACE0("No items were selected!\n");
	else
	{
		while (pos)
		{
			int nItem = m_ListCtrl.GetNextSelectedItem(pos);
			TRACE1("Item %d was selected!\n", nItem);
			ObjectNode* pNode = (ObjectNode *)m_ListCtrl.GetItemData(nItem);

			gcall.TurnTo(pNode);
		}
	}

}

void CDataDlg::OnSteptoobjet() 
{
	// TODO: Add your command handler code here
	
	POSITION pos = m_ListCtrl.GetFirstSelectedItemPosition();
	if (pos == NULL)
		TRACE0("No items were selected!\n");
	else
	{
		while (pos)
		{
			int nItem = m_ListCtrl.GetNextSelectedItem(pos);
			TRACE1("Item %d was selected!\n", nItem);
			ObjectNode* pNode = (ObjectNode *)m_ListCtrl.GetItemData(nItem);
	
			gcall.Step(pNode);
		}
	}
	
}

void CDataDlg::OnRclickList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	
	POINT point;
	GetCursorPos(&point);
	
	CMenu menu;
	menu.LoadMenu(IDR_OBJECT);
	menu.GetSubMenu(0)->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);
	


	*pResult = 0;
}

void CDataDlg::OnScriptwriter() 
{
	// TODO: Add your control notification handler code here
	
}

void CDataDlg::OnFindthenkill() 
{
	// TODO: Add your control notification handler code here
	gcall.FindThenKill(0, 1000, modeNormal | modePickup | modeAoe);
}

void CDataDlg::OnHookAcceptquest() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if(m_bHook_Accquest)
	{
		aeQuestHook.hook();
	}
	else
	{
		aeQuestHook.unhook();
	}
}

void CDataDlg::OnHookstrike() 
{
	// TODO: Add your command handler code here
	POSITION pos = m_ListCtrl.GetFirstSelectedItemPosition();

	while(pos)
	{
		int nItem = m_ListCtrl.GetNextSelectedItem(pos);
		ObjectNode* pNode = (ObjectNode *)m_ListCtrl.GetItemData(nItem);

		g_ObjAddrVec.push_back(pNode->ObjAddress);
	}
}

void CDataDlg::OnHookCombat() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if(m_bHook_Combat)
	{
		g_ObjAddrVec.clear();
		backupCombat = CombatHook.hook();
	}
	else{
		CombatHook.unhook();
	}
}
