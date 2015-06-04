// LuaPage.cpp : implementation file
//

#include "stdafx.h"
#include "jlwg.h"
#include "LuaPage.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLuaPage dialog


CLuaPage::CLuaPage(CWnd* pParent /*=NULL*/)
    : CPropertyPage(CLuaPage::IDD)
{
    //{{AFX_DATA_INIT(CLuaPage)
    // NOTE: the ClassWizard will add member initialization here
    //}}AFX_DATA_INIT
}


void CLuaPage::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CLuaPage)
    // NOTE: the ClassWizard will add DDX and DDV calls here
    //}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CLuaPage, CDialog)
    //{{AFX_MSG_MAP(CLuaPage)
    ON_BN_CLICKED(IDC_TESTLUA, OnTestLua)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLuaPage message handlers

void CLuaPage::OnTestLua()
{

    lua_State* pL = theApp.m_pstate;


    CString strLua;
	GetDlgItem(IDC_EDIT1)->GetWindowText(strLua);



	int utf8_size = WideCharToMultiByte(CP_UTF8, 0, strLua.GetBuffer(0), -1, NULL, 0, NULL, NULL) + 1;
	strLua.ReleaseBuffer();

	char* utf8_str = new char[utf8_size];
	WideCharToMultiByte(CP_UTF8, 0, strLua.GetBuffer(0), -1, utf8_str, utf8_size, NULL, NULL);
	strLua.ReleaseBuffer();


    int error = luaL_loadbuffer(pL, utf8_str, utf8_size-1, "line") || lua_pcall(pL, 0, 0, 0);

    if(error)
    {
        MessageBoxA(NULL, lua_tostring(pL, -1), "脚本", MB_ICONINFORMATION);
        lua_pop(pL, 1);
    }
}



//调试信息对话框
CDbgPage::CDbgPage(CWnd* pParent /*=NULL*/)
: CPropertyPage(CDbgPage::IDD)
{
    //{{AFX_DATA_INIT(CDbgPage)
    //}}AFX_DATA_INIT
}


void CDbgPage::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CDbgPage)
    //}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDbgPage, CDialog)
//{{AFX_MSG_MAP(CDbgPage)
// NOTE: the ClassWizard will add message map macros here
//}}AFX_MSG_MAP
END_MESSAGE_MAP()


BOOL CDbgPage::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo)
{
	//拦截对回车和ESC
	if(nID == IDOK || nID == IDCANCEL) return TRUE;

	return CPropertyPage::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}


BOOL CLuaPage::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo)
{
	//	
	if(nID == IDOK || nID == IDCANCEL) return TRUE;

	return CPropertyPage::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}
