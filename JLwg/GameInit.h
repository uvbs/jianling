// GameInit.h: interface for the GameInit class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GAMEINIT_H__CFB0DEBA_3917_47FF_9B2E_C0228C627C8F__INCLUDED_)
#define AFX_GAMEINIT_H__CFB0DEBA_3917_47FF_9B2E_C0228C627C8F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include "..\common\ShareMem.h"

//负责一些初始化数据的工作
class GameInit
{
public:
    GameInit();
    virtual ~GameInit();



    BOOL Init();


    static TCHAR* GetLujingPath()
    {
        return m_szLujingPath;
    }
    static TCHAR* GetConfigPath()
    {
        return m_szConfigPath;
    }
    static TCHAR* GetLujingTest()
    {
        return m_szLujingTest;
    }


    void SetIniPath(TCHAR* szPath)
    {
        _tcscpy(m_szConfigPath, szPath);
    }


    HWND isGameWndCreated(DWORD dwPid);          //判断游戏窗口是否创建

    //游戏窗口
    static HWND GetGamehWnd()
    {
        return m_hGameWnd;   //获取游戏窗口
    }


    BOOL WaitGameCreate();


    SHAREINFO* GetAccountInfo()
    {
        return m_pShareMem;
    }

    void HookQietu(BOOL bEnable);   //hook 切图

protected:
    static void __stdcall ShunyiQietu();
    CCHook hookQietu;


    static HWND m_hGameWnd;

    //配置文件
    static TCHAR m_szLujingPath[MAX_PATH];
    static TCHAR m_szConfigPath[MAX_PATH];
    static TCHAR m_szLujingTest[MAX_PATH];

    ShareMem m_share;
    SHAREINFO* m_pShareMem;
};

#endif // !defined(AFX_GAMEINIT_H__CFB0DEBA_3917_47FF_9B2E_C0228C627C8F__INCLUDED_)
