// GameInit.cpp: implementation of the GameInit class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Jlwg.h"
#include "GameInit.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif


#include "..\common\common.h"
#include "..\common\ShareMem.h"


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


GameInit* GameInit::m_inst = NULL;
GameInit::GameInit()
{
    ZeroMemory(m_szLujingPath, MAX_PATH);
    ZeroMemory(m_szConfigPath, MAX_PATH);
    ZeroMemory(m_szLujingTest, MAX_PATH);
}

GameInit::~GameInit()
{
}


//�ȴ���Ϸ���ڴ���
//�ȴ�ʱ��25��
BOOL GameInit::WaitGameCreate()
{

    //�жϵ�ǰ��Ϸ�Ĵ����Ƿ񴴽�
    //25����û����Ϸ���ڲ�����ʹ��Ҳ�����
    for(int i = 0; i < 20; i++)
    {
        if(isGameWndCreated(GetCurrentProcessId()) != NULL)
        {
            TRACE(_T("��⵽��Ϸ���ڴ���"));
            return TRUE;
        }

        Sleep(2000);
    }

    return FALSE;
}


//�ж���Ϸ�����Ƿ񴴽�
HWND GameInit::isGameWndCreated(DWORD dwPid)
{
    HWND hGameWnd = FindWindowEx(NULL, NULL, _T("LaunchUnrealUWindowsClient"), NULL);

    if(hGameWnd == NULL)
    {
        //û���ҵ�
        return NULL;
    }

    //�ж���Ϸ���ڴ������
    for(;;)
    {
        DWORD dwWndOfPid;
        GetWindowThreadProcessId(hGameWnd, &dwWndOfPid);

        if(dwPid == dwWndOfPid)
        {
            //�ҵ���, ����
            m_hGameWnd = hGameWnd;
            return hGameWnd;
        }

        hGameWnd = FindWindowEx(NULL, hGameWnd, _T("LaunchUnrealUWindowsClient"), NULL);
        if(hGameWnd == NULL)
        {
            return NULL;
        }
    }
}


BOOL GameInit::Init()
{

    BOOL bGetShareMem = FALSE;
    if(JLShareMem::Instance()->Open(SHAREOBJNAME))
    {

        if(!JLShareMem::Instance()->Get(GetCurrentProcessId()))
        {
            TRACE(_T("û�ܳ�ʼ���������"));
            return FALSE;
        }
    }
    else
    {
        TRACE(_T("�򿪹����ڴ�ʧ��"));
        return FALSE;
    }


    //�����ļ�·��
    GetModuleFileName(GetModuleHandle(_T("JLwg")), m_szConfigPath, MAX_PATH);
    PathRemoveFileSpec(m_szConfigPath);


    //ģ���·��
    TCHAR szExePath[MAX_PATH] = {0};
    _tcscpy(szExePath, m_szConfigPath);


    //�����ļ�·��
    PathAppend(m_szConfigPath, _T("����"));
    if(PathFileExists(m_szConfigPath) == FALSE)
    {
        _wmkdir(m_szConfigPath);
    }


    //˲�Ƶ�·��
    _tcscpy(m_szLujingPath, szExePath);
    PathAppend(m_szLujingPath, _T("·��"));
    if(PathFileExists(m_szLujingPath) == FALSE)
    {
        _wmkdir(m_szLujingPath);
    }


    //¼��˲�Ƶ�Ĭ��·��
    _tcscpy(m_szLujingTest, m_szLujingPath);
    PathAppend(m_szLujingTest, _T("test.bin"));


    //Ĭ�������ļ���·��
    TCHAR szConfigTemp[MAX_PATH] = {0};
    CString strConfig = JLShareMem::Instance()->Get(GetCurrentProcessId())->szConfig;
    _tcscpy(szConfigTemp, (LPCTSTR)strConfig);
    _tcscat(szConfigTemp, _T(".ini"));
    PathAppend(m_szConfigPath, szConfigTemp);



    //��������ļ�������
    if(PathFileExists(m_szConfigPath) == FALSE)
    {
        FILE* configFile = _tfopen(_T("default.ini"), _T("w+"));
        if(configFile == NULL)
        {
            TRACE(_T("���������ļ�ʧ��"));
            return FALSE;
        }

        WORD hdr = 0xfeff;
        if(fwrite(&hdr, 1, sizeof(WORD), configFile) != sizeof(WORD))
        {
            return FALSE;
        }

        fclose(configFile);

    }


    TRACE1("%s", m_szConfigPath);
    TRACE1("%s", m_szLujingTest);


    //�ȴ���Ϸ���ڴ����ٽ��г�ʼ��
    WaitGameCreate();

    return TRUE;
}

void GameInit::SetIniPath(TCHAR* szPath)
{
    _tcscpy(m_szConfigPath, szPath);
}


GameInit* GameInit::Instance()
{
    if(m_inst == 0)
    {
        m_inst = new GameInit;
    }

    return m_inst;
}