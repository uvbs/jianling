// JLDlg.cpp : implementation file
//

#include "stdafx.h"
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
	m_strInfo = _T("");
	//}}AFX_DATA_INIT
	
}


void CJLDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CJLDlg)
	DDX_Text(pDX, IDC_STATIC_WGINFO, m_strInfo);
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





CWinThread* g_pTaskThread = NULL;
CWinThread* g_pCloseThread = NULL;
static UINT AutoCloseThread(LPVOID pParam)
{
	
	while(1)
	{
		gcall.CloseXiaoDongHua();
		Sleep(1000);
	}

}

static UINT TaskThread(LPVOID pParam)
{

	g_pCloseThread = AfxBeginThread(AutoCloseThread, 0);

	TaskScript task;
	task.BeginTask();

	return 0;
}

/////////////////////////////////////////////////////////////////////////////
// CJLDlg message handlers

void CJLDlg::OnGotask() 
{

	//读取配置文件
	//创建任务线程
	if(g_pTaskThread == NULL)
	{
		g_pTaskThread = AfxBeginThread(TaskThread, 0);
		SetDlgItemText(IDC_GOTASK, _T("终止任务"));
	}
	else
	{
		OnStopTask();
		SetDlgItemText(IDC_GOTASK, _T("开始任务"));
	}

}

BOOL CJLDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	SHAREINFO* pShareInfo = gcall.m_pShareMem;
	CString strConfig = pShareInfo->szConfig;
	CString strScript = pShareInfo->szSript;
	m_strInfo.Format(
		_T("配置: %s\n脚本: %s\n"), strConfig, strScript);

	UpdateData(FALSE);	

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
	if(g_pTaskThread != NULL)
	{
		::TerminateThread(g_pTaskThread->m_hThread, 0);
		g_pTaskThread->Delete();
		g_pTaskThread = NULL;
	}

	if(g_pCloseThread != NULL)
	{
		::TerminateThread(g_pCloseThread->m_hThread, 0);
		g_pCloseThread->Delete();
		g_pCloseThread = NULL;
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
