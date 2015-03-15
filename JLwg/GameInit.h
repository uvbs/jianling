// GameInit.h: interface for the GameInit class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GAMEINIT_H__CFB0DEBA_3917_47FF_9B2E_C0228C627C8F__INCLUDED_)
#define AFX_GAMEINIT_H__CFB0DEBA_3917_47FF_9B2E_C0228C627C8F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


//负责一些初始化数据的工作
class GameInit
{
public:
    GameInit();
    virtual ~GameInit();
    BOOL Init();
    static GameInit* Instance();

    TCHAR* GetLujingPath() {return m_szLujingPath;}
    TCHAR* GetConfigPath() {return m_szConfigPath;}
    TCHAR* GetLujingTest() {return m_szLujingTest;}
    HWND GetGamehWnd() {return m_hGameWnd;}

    void SetIniPath(TCHAR* szPath);
    HWND isGameWndCreated(DWORD dwPid);
    BOOL WaitGameCreate();
    
private:
    HWND m_hGameWnd;
    TCHAR m_szLujingPath[MAX_PATH];
    TCHAR m_szConfigPath[MAX_PATH];
    TCHAR m_szLujingTest[MAX_PATH];
    static GameInit* m_inst;
};

#endif // !defined(AFX_GAMEINIT_H__CFB0DEBA_3917_47FF_9B2E_C0228C627C8F__INCLUDED_)
