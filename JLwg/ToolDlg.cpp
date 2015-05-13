// ToolDlg.cpp : implementation file
//

#include "stdafx.h"
#include "jlwg.h"
#include "ToolDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CToolDlg dialog


CToolDlg::CToolDlg(CWnd* pParent /*=NULL*/)
    : CDialog(CToolDlg::IDD, pParent)
{
    //{{AFX_DATA_INIT(CToolDlg)
    // NOTE: the ClassWizard will add member initialization here
    //}}AFX_DATA_INIT
}


void CToolDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CToolDlg)
    // NOTE: the ClassWizard will add DDX and DDV calls here
    //}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CToolDlg, CDialog)
    //{{AFX_MSG_MAP(CToolDlg)
    ON_BN_CLICKED(IDC_CHECK1, OnCheck1)
    ON_BN_CLICKED(IDC_CHECK2, OnCheck2)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CToolDlg message handlers



DWORD ori_gameprint = 0;
DWORD ori_eGetInstance = 0;
void __stdcall gameprint()
{
    int* _ebp;
    __asm mov _ebp , ebp;

    //push 字符串偏移
    //call Client+0x1420;
    //

    //push 字符串
    //call retn
    //保存的ebp

    _ebp += 2;

    static std::wstring strOld = (wchar_t*)*_ebp;

    if(strOld != (wchar_t*)*_ebp)
    {
        //输出这个字符串. 宽字符
        OutputDebugStringW((wchar_t*)*_ebp);

        strOld = (wchar_t*)*_ebp;
    }



    __asm
    {
        leave;
        jmp ori_gameprint;
    }


}


//可能是处理动作的模块
//徐哥走路就用到了这个
void __stdcall eGetInstance()
{

    int* _ebp;
    __asm mov _ebp , ebp;

    //push 字符串偏移
    //call Client+0x1420;
    //

    //push 字符串
    //call retn
    //保存的ebp

    _ebp += 1;

    static old = (DWORD) * _ebp;

    if(old != (DWORD)*_ebp)
    {
        //调用地址输出
        char buf[30];
        wsprintfA(buf, "%08x", (DWORD)*_ebp);
        OutputDebugStringA(buf);

        old = (DWORD) * _ebp;
    }


    __asm
    {
        leave;
        jmp ori_eGetInstance;
    }
}

void CToolDlg::OnCheck1()
{
    // TODO: Add your control notification handler code here

    if(((CButton*)GetDlgItem(IDC_CHECK1))->GetState()  == BST_UNCHECKED)
    {
        AfxMessageBox(_T(""));
        m_dbgprint.unhook();
    }
    else
    {

        //钩的地址
        HMODULE hClient = GetModuleHandle(_T("Client.exe"));
        if(hClient == NULL)
        {
            AfxMessageBox(_T("没有找到Client"));
            return;
        }

        DWORD dwHookAddr = (DWORD)hClient + 0x1420;


        m_dbgprint.Init((void*)dwHookAddr, gameprint);

        if((ori_eGetInstance = (DWORD)m_dbgprint.hook()) == 0)
        {
            AfxMessageBox(_T("安装钩子失败"));
        }
    }
}


//EInterfaceGetInstanc>  A1 E031CB05     mov     eax, [0x5CB31E0]
void CToolDlg::OnCheck2()
{
    // TODO: Add your control notification handler code here

    if(((CButton*)GetDlgItem(IDC_CHECK2))->GetState()  == BST_UNCHECKED)
    {
        AfxMessageBox(_T("EInterfaceGetInstanc unhook"));
        m_dbgprint.unhook();
    }
    else
    {

        //钩的地址
        HMODULE hbs = GetModuleHandle(_T("bsengine_Shipping.dll"));
        if(hbs == NULL)
        {
            AfxMessageBox(_T("没有找到bsengine"));
            return;
        }



        DWORD dwHookAddr = (DWORD)hbs + 0xA30FB0;


        m_bsEGetInstance.Init((void*)dwHookAddr, eGetInstance);

        if((ori_eGetInstance = (DWORD)m_bsEGetInstance.hook()) == 0)
        {
            AfxMessageBox(_T("安装钩子失败"));
        }
    }
}
