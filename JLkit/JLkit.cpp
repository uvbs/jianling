// JLkit.cpp : Defines the class behaviors for the application.
//
#include "stdafx.h"
#include "JLkit.h"
#include "MainFrm.h"
#include "JLkitView.h"
#include "JLkitDoc.h"
#include "JLkitSocket.h"
#include "configmgr.h"

#ifdef _DEBUG
    #define new DEBUG_NEW
#endif

using namespace Gdiplus;


//Ψһʵ��
CJLkitApp   theApp;



//��Ϣӳ��
BEGIN_MESSAGE_MAP(CJLkitApp, CWinApp)
//{{AFX_MSG_MAP(CJLkitApp)
    ON_COMMAND(ID_APP_EXIT, OnAppExit)
    ON_COMMAND(ID_FILE_OPEN, OnFileOpen)
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////

CJLkitApp::CJLkitApp()
{
}


CJLkitApp::~CJLkitApp()
{
}


BOOL CJLkitApp::InitInstance()
{


#ifdef JLTW
    if(!LoadLibrary(_T("JLnp_tw.dll")))
#else
    if(!LoadLibrary(_T("JLnp.dll")))
#endif
    {
        AfxMessageBox(_T("����NPʧ��"));
        return FALSE;
    }


    //��ʼ���׽���
    if(!AfxSocketInit())
    {
        AfxMessageBox(IDP_SOCKETS_INIT_FAIL);
        return FALSE;
    }


    //���������ļ�
    TCHAR szIni[MAX_PATH];
    GetModuleFileName(NULL, szIni, MAX_PATH);
    PathRemoveExtension(szIni);
    _tcscat(szIni, _T(".ini"));
    if(!PathFileExists(szIni))
    {
        FILE* fp = _tfopen(szIni, _T("w+"));
        if(fp == NULL)
        {
            AfxMessageBox(_T("�޷����������ļ�"));
            return FALSE;
        }

        fclose(fp);
    }

    //��������
    if(!CConfigMgr::GetInstance()->LoadConfig(szIni))
    {
        AfxMessageBox(_T("���������ļ�ʧ��"));
        return FALSE;
    }



    //�������ڿ��
    CSingleDocTemplate* pDocTemplate;
    pDocTemplate = new CSingleDocTemplate(
        IDR_MAINFRAME, 
        RUNTIME_CLASS(CJLkitDoc),
        RUNTIME_CLASS(CMainFrame), 
        RUNTIME_CLASS(CJLkitView));
    AddDocTemplate(pDocTemplate);

    m_nCmdShow = SW_HIDE;
    OnFileNew();

    return TRUE;
}

int CJLkitApp::ExitInstance()
{
    return CWinApp::ExitInstance();
}
