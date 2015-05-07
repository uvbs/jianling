// LuaPage.cpp : implementation file
//

#include "stdafx.h"
#include "jlwg.h"
#include "LuaPage.h"
#include "LuaScript.h"



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

    lua_State* pL = LuaScript::GetInstance()->m_pstate;


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
        CEdit* pEdit = (CEdit*)GetDlgItem(IDC_EDIT1);
        int len = pEdit->GetWindowTextLength();
        pEdit->SetSel(len, -1);
        pEdit->ReplaceSel(A2T(lua_tostring(pL, -1)));

        lua_pop(pL, 1);
    }
}
