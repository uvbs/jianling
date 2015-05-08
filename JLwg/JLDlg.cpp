// JLDlg.cpp : implementation file
//

#include "stdafx.h"
#include "JLwg.h"
#include "JLDlg.h"
#include "DataDlg.h"
#include "LuaScript.h"

#include <afxpriv.h>

#ifdef JLTW
#include "TaskScript_tw.h"
#else
#include "TaskScript.h"
#endif



#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


//���캯��
CJLDlg::CJLDlg(CWnd* pParent /*=NULL*/)
    : CDialog(CJLDlg::IDD, pParent)
{
    //{{AFX_DATA_INIT(CJLDlg)
    //}}AFX_DATA_INIT
    m_bWorking = true;
}

//��������
CJLDlg::~CJLDlg()
{
    //�ͷ��߳�
    if(m_pWorkThread)
    {
        m_bWorking = false;
        m_pWorkThread->PostThreadMessage(WM_QUIT, 0, 0);
        WaitForSingleObject(m_pWorkThread->m_hThread, INFINITE);
    }
}


BEGIN_MESSAGE_MAP(CJLDlg, CDialog)
    //{{AFX_MSG_MAP(CJLDlg)
    ON_BN_CLICKED(IDC_GOTASK, OnGotask)
    ON_BN_CLICKED(IDC_WGDATA, OnWgdata)
    ON_BN_CLICKED(IDC_UNLOADWG, OnUnloadwg)
    ON_BN_CLICKED(IDC_GOTASK2, OnGotask2)
    ON_WM_CLOSE()
    ON_WM_SHOWWINDOW()
    ON_WM_PAINT()
    ON_MESSAGE(WM_KICKIDLE, OnKickIdle)
    ON_UPDATE_COMMAND_UI(IDC_GOTASK, OnUpdateGoTask)
    ON_UPDATE_COMMAND_UI(IDC_GOTASK2, OnUpdateGoTask)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()


void CJLDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CJLDlg)
    //}}AFX_DATA_MAP
}

void CJLDlg::OnGotask()
{
    m_pWorkThread->PostThreadMessage(WM_WORKTHREAD_EXCUTASK, 0, 0);
}

BOOL CJLDlg::OnInitDialog()
{
    if(!CDialog::OnInitDialog())
        return FALSE;

    SetWindowText(theApp.m_stData.szAccount);

    //��ʼ�������߳�
    m_pWorkThread = AfxBeginThread(WorkThread, this);
    if(!m_pWorkThread) return FALSE;

    return TRUE;
}

void CJLDlg::OnWgdata()
{
    ShowWindow(SW_HIDE);

    CDataDlg dlg;
    dlg.DoModal();

    ShowWindow(SW_SHOW);
}

void CJLDlg::OnStopTask()
{
}


void CJLDlg::OnClose()
{
    ShowWindow(SW_HIDE);
}

void CJLDlg::OnUnloadwg()
{
    OnStopTask();
    EndDialog(IDCANCEL);
}

void CJLDlg::PostNcDestroy()
{
    TRACE(_T("PostNcDestroy"));
    delete this;
}

//ִ�нű�
void CJLDlg::OnGotask2()
{
    m_pWorkThread->PostThreadMessage(WM_WORKTHREAD_EXCULUA, 0, 0);
}


void CJLDlg::OnUpdateGoTask(CCmdUI* pCmdUI)
{
    if(m_bWorking)
    {
        pCmdUI->Enable(FALSE);
    }
    else
    {
        pCmdUI->Enable();
    }
}

LRESULT CJLDlg::OnKickIdle(WPARAM wParam, LPARAM lParam)
{
    UpdateDialogControls(this, FALSE);
    return 0;
}




//�����߳�
UINT CJLDlg::WorkThread(LPVOID pParam)
{

    CJLDlg* pDlg = (CJLDlg*)pParam;


    //��ȡlua״̬
    lua_State* pL = theApp.m_pstate;


    //�����߳���Ϣ����
    MSG msg;
    PeekMessage(&msg, NULL, WM_USER, WM_USER, PM_NOREMOVE);

    while(1)
    {
        //״̬
        pDlg->m_bWorking = false;

        GetMessage(&msg, NULL, 0, 0);
        pDlg->m_bWorking = true;

        switch(msg.message)
        {
        case WM_QUIT:
            {
                return 1;
            }

        case WM_WORKTHREAD_TESTCOMBATBOSS:
            {
                CDataDlg* pDlg = (CDataDlg*)msg.wParam;

                if(pDlg->m_ListCtrl.GetSelectedCount() == 0)
                {
                    AfxMessageBox(_T("ѡ���������"));
                    return 0;
                }

                POSITION rpos = pDlg->m_ListCtrl.GetFirstSelectedItemPosition();
                if(rpos)
                {
                    int inItem  = pDlg->m_ListCtrl.GetNextSelectedItem(rpos);
                    TCHAR szName[MAX_PATH] = {0};
                    pDlg->m_ListCtrl.GetItemText(inItem, 1, szName, sizeof(szName));
                    GamecallEx::GetInstance()->KillBoss(szName);
                }

                break;
            }


        case WM_WORKTHREAD_EXCULUA:
            {

                //���ģ�鵱ǰ·��
                TCHAR szExe[MAX_PATH] = {0};
                GetModuleFileName(theApp.m_hInstance, szExe, MAX_PATH);
                PathRemoveFileSpec(szExe);
                PathAppend(szExe, _T("�ű�"));
                PathAppend(szExe, theApp.m_stData.szScript);

                if(!PathFileExists(szExe))
                {
                    AfxMessageBox(_T("�ű�������"));
                    break;
                }

                LPCSTR pszPath;
#ifdef _UNICODE
                USES_CONVERSION;
                pszPath = T2A(szExe);
#else
                pszPath = szExe;
#endif

                //����lua�ű�
                if(luaL_dofile(pL, pszPath) != LUA_OK)
                {
                    MessageBoxA(NULL, lua_tostring(pL, -1), "����", MB_OK);
                }


                break;
            }

        case WM_WORKTHREAD_EXCUTASK:
            {
                //TaskScript task;
                //task.BeginTask();
                break;
            }

        default:
            break;
        }
    }

    return 0;
}
