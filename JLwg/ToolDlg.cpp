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

    //push �ַ���ƫ��
    //call Client+0x1420;
    //

    //push �ַ���
    //call retn
    //�����ebp

    _ebp += 2;

    static std::wstring strOld = (wchar_t*)*_ebp;

    if(strOld != (wchar_t*)*_ebp)
    {
        //�������ַ���. ���ַ�
        OutputDebugStringW((wchar_t*)*_ebp);

        strOld = (wchar_t*)*_ebp;
    }



    __asm
    {
        leave;
        jmp ori_gameprint;
    }


}


//�����Ǵ�������ģ��
//�����·���õ������
void __stdcall eGetInstance()
{

    int* _ebp;
    __asm mov _ebp , ebp;

    //push �ַ���ƫ��
    //call Client+0x1420;
    //

    //push �ַ���
    //call retn
    //�����ebp

    _ebp += 1;

    static old = (DWORD) * _ebp;

    if(old != (DWORD)*_ebp)
    {
        //���õ�ַ���
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

        //���ĵ�ַ
        HMODULE hClient = GetModuleHandle(_T("Client.exe"));
        if(hClient == NULL)
        {
            AfxMessageBox(_T("û���ҵ�Client"));
            return;
        }

        DWORD dwHookAddr = (DWORD)hClient + 0x1420;


        m_dbgprint.Init((void*)dwHookAddr, gameprint);

        if((ori_eGetInstance = (DWORD)m_dbgprint.hook()) == 0)
        {
            AfxMessageBox(_T("��װ����ʧ��"));
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

        //���ĵ�ַ
        HMODULE hbs = GetModuleHandle(_T("bsengine_Shipping.dll"));
        if(hbs == NULL)
        {
            AfxMessageBox(_T("û���ҵ�bsengine"));
            return;
        }



        DWORD dwHookAddr = (DWORD)hbs + 0xA30FB0;


        m_bsEGetInstance.Init((void*)dwHookAddr, eGetInstance);

        if((ori_eGetInstance = (DWORD)m_bsEGetInstance.hook()) == 0)
        {
            AfxMessageBox(_T("��װ����ʧ��"));
        }
    }
}
