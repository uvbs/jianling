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


    LPSTR pszLua;

#ifdef _UNICODE
    USES_CONVERSION;
    pszLua = T2A((LPCTSTR)strLua);
#else
    pszLua = (LPCTSTR)strLua;
#endif



    int error = luaL_loadbuffer(pL, pszLua, strlen(pszLua), "line") ||
                lua_pcall(pL, 0, 0, 0);
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
