// LaunchGameThread.cpp : implementation file
//

#include "stdafx.h"
#include "jlkit.h"
#include "LaunchGameThread.h"
#include "JLkitView.h"
#include "JLkitDoc.h"


#include "..\common\webpost.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLaunchGameThread

IMPLEMENT_DYNCREATE(CLaunchGameThread, CWinThread)

CLaunchGameThread::CLaunchGameThread()
{
}

CLaunchGameThread::~CLaunchGameThread()
{
}


BEGIN_MESSAGE_MAP(CLaunchGameThread, CWinThread)
	//{{AFX_MSG_MAP(CLaunchGameThread)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()



/////////////////////////////////////////////////////////////////////////////
// CLaunchGameThread message handlers

int CLaunchGameThread::Run() 
{
    // TODO: Add your specialized code here and/or call the base class
    if(m_pView == NULL)
        return -1;
    
    Webpost::InitCom();
    CJLkitDoc* pDoc = m_pView->GetDocument();
    CListCtrl &list = m_pView->GetListCtrl();
    //当前选中的条目
    for(int i = 0; i < list.GetItemCount(); i++){
        
        if(list.GetCheck(i)){
            CString strName = list.GetItemText(i, COLUMN_TEXT_ACCOUNT);
            CString strPw = list.GetItemText(i, COLUMN_TEXT_PASSWORD);
            CString strConfig = list.GetItemText(i, COLUMN_TEXT_CONFIG);
            CString strScript = list.GetItemText(i, COLUMN_TEXT_SCRIPT);
            
            list.SetItemText(i, COLUMN_TEXT_STATUS, _T("开始运行.."));
            int nReslt = pDoc->LaunchGame(strName, strPw, strConfig, strScript);
            m_pView->SetResult(nReslt, i);	
        }
    
    }
    Webpost::UnInitCom();
    return 0;
}

BOOL CLaunchGameThread::InitInstance() 
{
	// TODO: Add your specialized code here and/or call the base class
	
	CWinThread::InitInstance();
    return TRUE;
}
