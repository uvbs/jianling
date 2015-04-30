#include "stdafx.h"
#include "JLwg.h"
#include "TaskScript.h"
#include "GamecallEx.h"
#include "GameConfig.h"
#include "GameLog.h"
#include "JLDlg.h"


//程序实例唯一
CJLwgApp theApp;


//静态变量
WNDPROC CJLwgApp::wpOrigGameProc = NULL;
CJLDlg* CJLwgApp::m_pWgDlg = NULL;
HWND CJLwgApp::m_hGameWnd = NULL;




CJLwgApp::CJLwgApp()
{
    m_hPipe = INVALID_HANDLE_VALUE;
}

CJLwgApp::~CJLwgApp()
{
}


//钩游戏的消息窗口
LRESULT CALLBACK CJLwgApp::GameMsgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{

    if(!CJLwgApp::m_pWgDlg || !::IsWindow(CJLwgApp::m_pWgDlg->m_hWnd))
    {
        return CallWindowProc(wpOrigGameProc, hwnd, uMsg, wParam, lParam);
    }

    //调出外挂
    switch(uMsg)
    {

    //因为程序保护的问题, 好像游戏进程退出时, 外挂模块并不会被通知到
    case WM_DESTROY:
        {
            theApp.UnLoad();
            break;
        }


    case WM_MOVE:
        {
            RECT rect;


            GetWindowRect(hwnd, &rect);
            m_pWgDlg->SetWindowPos(NULL, rect.right, rect.top, 0, 0, SWP_NOSIZE | SWP_NOACTIVATE);
            break;
        }

    case WM_KEYDOWN:
        {

            if(wParam == VK_INSERT)
            {
                int result = MessageBox(hwnd, _T("你按下了 VK_INSERT 按键.\n确认执行任务?"), NULL, MB_OKCANCEL);
                if(result == IDOK)
                {
                    m_pWgDlg->OnGotask();
                }
            }
            else if(wParam == VK_DELETE)
            {
                m_pWgDlg->OnStopTask();
            }
            else if(wParam == VK_END)
            {
                if(m_pWgDlg->IsWindowVisible())
                {
                    m_pWgDlg->ShowWindow(SW_HIDE);
                }
                else
                {
                    m_pWgDlg->ShowWindow(SW_SHOWNA);
                }

            }
            break;
        }

    case WM_CUSTOM_GCALL:
        {
            //此处实现游戏call的调用
            return GamecallEx::GetInstance()->call((DWORD)wParam, (LPVOID*)lParam);
        }

    }


    return CallWindowProc(wpOrigGameProc, hwnd, uMsg, wParam, lParam);
}


DWORD CALLBACK CJLwgApp::WgThread(LPVOID pParam)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState())

    if(!AfxSocketInit())
    {
        LOGER(_T("套接字初始化失败"));
        ExitProcess(0);
        return FALSE;
    }

    if(!theApp.WaitGameCreate(30))
    {
        LOGER(_T("等待游戏窗口超时"));
        ExitProcess(0);
        return FALSE;
    }


    if(!GameSpend::GetInstance()->Init())
    {
        LOGER(_T("初始化加速失败"));
        ExitProcess(0);
        return FALSE;
    }


    if(!GameConfig::GetInstance()->LoadConfig())
    {
        LOGER(_T("加载配置文件失败"));
        ExitProcess(0);
        return FALSE;
    }



    if(!GamecallEx::GetInstance()->Init())
    {
        LOGER(_T("外挂功能初始化失败"));
        ExitProcess(0);
        return FALSE;
    }

    if(!LuaScript::GetInstance()->Init())
    {
        LOGER(_T("LUA初始化失败"));
        ExitProcess(0);
        return FALSE;
    }

    LOGER(_T("启动完成"));


    //钩游戏窗口处理
    wpOrigGameProc = (WNDPROC)::SetWindowLong(m_hGameWnd, GWL_WNDPROC, (LONG)GameMsgProc);
    ::SetWindowText(m_hGameWnd, theApp.m_stData.szAccount);


    //外挂主对话框
    m_pWgDlg = new CJLDlg;
    m_pWgDlg->DoModal();


    FreeLibraryAndExitThread(theApp.m_hInstance, 0);
    return 0;
}



//等待游戏窗口创建
BOOL CJLwgApp::WaitGameCreate(int inMaxTime)
{

    DWORD dwWndOfPid;
    DWORD dwMyid = GetCurrentProcessId();

    for(int i = 0; i < inMaxTime; i++)
    {
        Sleep(1000);

        HWND hGameWnd = FindWindowEx(NULL, NULL, _T("LaunchUnrealUWindowsClient"), NULL);
        if(hGameWnd == NULL) continue;
        for(;;)
        {

            GetWindowThreadProcessId(hGameWnd, &dwWndOfPid);

            //找到
            if(dwMyid == dwWndOfPid)
            {
                m_hGameWnd = hGameWnd;
                return TRUE;
            }

            hGameWnd = FindWindowEx(NULL, hGameWnd, _T("LaunchUnrealUWindowsClient"), NULL);
            if(hGameWnd == NULL) break;
        }

    }

    return FALSE;
}

BOOL CJLwgApp::InitPipe()
{
    //1, 获取通信数据
    TCHAR szPipe[MAX_PATH];
    wsprintf(szPipe, _T("\\\\.\\Pipe\\JLwg_%d"), GetCurrentProcessId());
    if(!::WaitNamedPipe(szPipe, NMPWAIT_USE_DEFAULT_WAIT))
    {
        TRACE(_T("can't find pipe!"));
        return FALSE;
    }

    // 打开管道
    m_hPipe = CreateFile(szPipe, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL) ;
    if(m_hPipe == INVALID_HANDLE_VALUE)
    {
        TRACE(_T("can't open console pipe!")) ;
        ExitProcess(0);
        return FALSE;
    }

    //读取数据
    DWORD dwBytesReaded = 0;
    if(!ReadFile(m_hPipe, &m_stData, sizeof(PIPEDATA), &dwBytesReaded, NULL))
    {
        TRACE(_T("can't read pipe data!"));
        ExitProcess(0);
        return FALSE;
    }

    //设置成不等待模式
    DWORD dwMode = PIPE_NOWAIT | PIPE_READMODE_MESSAGE;
    SetNamedPipeHandleState(m_hPipe, &dwMode, NULL, NULL);

    return TRUE;
}

BOOL CJLwgApp::InitLog()
{
    //2, 初始化日志
    TCHAR szLogPath[MAX_PATH];
    GetModuleFileName(AfxGetInstanceHandle(), szLogPath, MAX_PATH);
    PathRemoveFileSpec(szLogPath);
    PathAppend(szLogPath, _T("日志"));
    if(!PathFileExists(szLogPath))
    {
        //创建日志目录
        _tmkdir(szLogPath);
    }

    PathAppend(szLogPath, m_stData.szAccount);
    _tcscat(szLogPath, _T(".txt"));



    if(!GameLog::GetInstance()->open(szLogPath))
    {
        TRACE(_T("can't open log file!"));
        ExitProcess(0);
        return FALSE;
    }

    return TRUE;
}


BOOL CJLwgApp::InitInstance()
{

    //设置区域
    setlocale(LC_ALL, "chs");


    if(!InitPipe())
    {
        return FALSE;
    }


    if(!InitLog())
    {
        return FALSE;
    }



    //至此日志能使用
    LOGER(_T("###外挂启动"));

    //外挂主线程
    HANDLE hwgThread = ::CreateThread(NULL, 0, WgThread, this, 0, 0);
    if(hwgThread == NULL)
    {

        LOGER(_T("主线程创建失败"));
        ExitProcess(0);
        return FALSE;
    }


    CloseHandle(hwgThread);
    return TRUE;
}

//向控制台通信
void CJLwgApp::SendStatus(TCHAR szText[])
{
    _ASSERTE(_tcslen(szText) <= MAX_PATH);


    PIPESTATUS status;
    status.dwPid = m_stData.dwPid;
    status.dwItem = m_stData.dwItem;
    _tcsncpy(status.szStatus, szText, _tcslen(szText) + 1);

    DWORD dwWriten;
    WriteFile(m_hPipe, &status, sizeof(PIPESTATUS), &dwWriten, NULL);
}

void CJLwgApp::UnLoad()
{
    LOGER(_T("已卸载"));

    GamecallEx::GetInstance()->UnLoad();


    if(m_hPipe != INVALID_HANDLE_VALUE)
    {
        CloseHandle(m_hPipe);
        m_hPipe = INVALID_HANDLE_VALUE;
    }


    if(wpOrigGameProc)
    {
        ::SetWindowLong(m_hGameWnd, GWL_WNDPROC, (LONG)wpOrigGameProc);
        wpOrigGameProc = NULL;
    }

    if(m_pWgDlg)
    {
        if(::IsWindow(m_pWgDlg->m_hWnd))
        {
            m_pWgDlg->EndDialog(IDCANCEL);
        }

        SafeDelete(m_pWgDlg);
    }

}

int CJLwgApp::ExitInstance()
{
    TRACE(_T("ExitInstance"));
    UnLoad();

    return CWinApp::ExitInstance();
}

