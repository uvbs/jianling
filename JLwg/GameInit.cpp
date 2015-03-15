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


//等待游戏窗口创建
//等待时间25秒
BOOL GameInit::WaitGameCreate()
{

    //判断当前游戏的窗口是否创建
    //25秒内没有游戏窗口产生就使外挂不加载
    for(int i = 0; i < 20; i++)
    {
        if(isGameWndCreated(GetCurrentProcessId()) != NULL)
        {
            TRACE(_T("检测到游戏窗口创建"));
            return TRUE;
        }

        Sleep(2000);
    }

    return FALSE;
}


//判断游戏窗口是否创建
HWND GameInit::isGameWndCreated(DWORD dwPid)
{
    HWND hGameWnd = FindWindowEx(NULL, NULL, _T("LaunchUnrealUWindowsClient"), NULL);

    if(hGameWnd == NULL)
    {
        //没有找到
        return NULL;
    }

    //判断游戏窗口创建完成
    for(;;)
    {
        DWORD dwWndOfPid;
        GetWindowThreadProcessId(hGameWnd, &dwWndOfPid);

        if(dwPid == dwWndOfPid)
        {
            //找到了, 保存
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
            TRACE(_T("没能初始化外挂数据"));
            return FALSE;
        }
    }
    else
    {
        TRACE(_T("打开共享内存失败"));
        return FALSE;
    }


    //配置文件路径
    GetModuleFileName(GetModuleHandle(_T("JLwg")), m_szConfigPath, MAX_PATH);
    PathRemoveFileSpec(m_szConfigPath);


    //模块的路径
    TCHAR szExePath[MAX_PATH] = {0};
    _tcscpy(szExePath, m_szConfigPath);


    //配置文件路径
    PathAppend(m_szConfigPath, _T("配置"));
    if(PathFileExists(m_szConfigPath) == FALSE)
    {
        _wmkdir(m_szConfigPath);
    }


    //瞬移的路径
    _tcscpy(m_szLujingPath, szExePath);
    PathAppend(m_szLujingPath, _T("路径"));
    if(PathFileExists(m_szLujingPath) == FALSE)
    {
        _wmkdir(m_szLujingPath);
    }


    //录制瞬移的默认路径
    _tcscpy(m_szLujingTest, m_szLujingPath);
    PathAppend(m_szLujingTest, _T("test.bin"));


    //默认配置文件的路径
    TCHAR szConfigTemp[MAX_PATH] = {0};
    CString strConfig = JLShareMem::Instance()->Get(GetCurrentProcessId())->szConfig;
    _tcscpy(szConfigTemp, (LPCTSTR)strConfig);
    _tcscat(szConfigTemp, _T(".ini"));
    PathAppend(m_szConfigPath, szConfigTemp);



    //如果配置文件不存在
    if(PathFileExists(m_szConfigPath) == FALSE)
    {
        FILE* configFile = _tfopen(_T("default.ini"), _T("w+"));
        if(configFile == NULL)
        {
            TRACE(_T("创建配置文件失败"));
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


    //等待游戏窗口创建再进行初始化
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