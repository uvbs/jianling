// JLDlg.cpp : implementation file
//

#include "stdafx.h"
#include "JLwg.h"
#include "JLDlg.h"
#include "TaskScript.h"
#include "DataDlg.h"

#include "..\common\common.h"
#include "..\common\sharemem.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CJLDlg dialog


CJLDlg::CJLDlg(CWnd* pParent /*=NULL*/)
    : CDialog(CJLDlg::IDD, pParent)
{
    //{{AFX_DATA_INIT(CJLDlg)

    //}}AFX_DATA_INIT

    m_pTaskThread = NULL;
}


void CJLDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CJLDlg)
    //}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CJLDlg, CDialog)
    //{{AFX_MSG_MAP(CJLDlg)
    ON_BN_CLICKED(IDC_GOTASK, OnGotask)
    ON_BN_CLICKED(IDC_WGDATA, OnWgdata)
    ON_BN_CLICKED(IDC_STOPTASk, OnStopTask)
    ON_WM_CLOSE()
    ON_WM_SHOWWINDOW()
    ON_BN_CLICKED(IDC_UNLOADWG, OnUnloadwg)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()


static UINT TaskThread(LPVOID pParam)
{

    TaskScript task;
    task.BeginTask();

    return 0;
}

/////////////////////////////////////////////////////////////////////////////
// CJLDlg message handlers

void CJLDlg::OnGotask()
{
    //创建任务线程
    if(m_pTaskThread == NULL)
    {
        m_pTaskThread = AfxBeginThread(TaskThread, 0);
        SetDlgItemText(IDC_GOTASK, _T("终止任务"));
    }
    else
    {
        OnStopTask();
        m_pTaskThread = NULL;
        SetDlgItemText(IDC_GOTASK, _T("开始任务"));
    }
}

BOOL CJLDlg::OnInitDialog()
{
    CDialog::OnInitDialog();
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
    if(m_pTaskThread != NULL)
    {
        ::TerminateThread(m_pTaskThread->m_hThread, 0);
        m_pTaskThread->Delete();
        m_pTaskThread = NULL;
    }
}


void CJLDlg::OnClose()
{
    ShowWindow(SW_HIDE);
}

void CJLDlg::OnShowWindow(BOOL bShow, UINT nStatus)
{
    CDialog::OnShowWindow(bShow, nStatus);

}

void CJLDlg::OnUnloadwg()
{
    OnStopTask();
    DestroyWindow();
}


void CJLDlg::PostNcDestroy()
{
    PostQuitMessage(0);
    delete this;
}
