#include "stdafx.h"
#include "JLwg.h"
#include "TaskScript.h"
#include "GamecallEx.h"
#include "GameConfig.h"
#include "GameLog.h"



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
    if(!CJLwgApp::m_pWgDlg)
    {
        return CallWindowProc(wpOrigGameProc, hwnd, uMsg, wParam, lParam);
    }


    //调出外挂
    switch(uMsg)
    {

    case WM_DESTROY:
        {
            OutputDebugString(_T("game destroy msg"));
            theApp.UnLoad();
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

                if(::IsWindow(m_pWgDlg->m_hWnd) == FALSE)
                {
                    break;
                }

                int style = GetWindowLong(hwnd, GWL_STYLE);
                ::SetWindowLong(hwnd, GWL_STYLE, style | WS_CLIPCHILDREN);


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
    else
    {
        LOGER(_T("游戏窗口创建"));
    }

    LOGER(_T("初始化加速"));
    if(!GameSpend::GetInstance()->Init())
    {
        LOGER(_T("初始化加速失败"));
        ExitProcess(0);
        return FALSE;
    }


    LOGER(_T("加载配置"));
    if(!GameConfig::GetInstance()->LoadConfig())
    {
        LOGER(_T("加载配置文件失败"));
        ExitProcess(0);
        return FALSE;
    }


    LOGER(_T("初始化外挂功能"));
//     if(!GamecallEx::GetInstance()->Init())
//     {
//         LOGER(_T("外挂功能初始化失败"));
//         ExitProcess(0);
//         return FALSE;
//     }


    LOGER(_T("外挂启动完成"));
    SENDLOG(_T("外挂启动完成"));
    
    //钩游戏窗口处理
    wpOrigGameProc = (WNDPROC)::SetWindowLong(m_hGameWnd, GWL_WNDPROC, (LONG)GameMsgProc);
    ::SetWindowText(m_hGameWnd, theApp.m_stData.szAccount);
    
    
    //外挂主对话框
    m_pWgDlg = new CJLDlg;
    m_pWgDlg->DoModal();

    TRACE(_T("CJLDlg DoModal ret"));
    theApp.UnLoad();
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

BOOL CJLwgApp::InitInstance()
{

    //设置区域
    setlocale(LC_ALL, "chs");

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


    GameLog* pLog = GameLog::GetInstance();
    if(!pLog->open(szLogPath))
    {
        TRACE(_T("can't open log file!"));
        ExitProcess(0);
        return FALSE;
    }

    //至此日志能
    LOGER(_T("#外挂启动"));

    //外挂线程
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
    PIPESTATUS status;
    status.dwPid = m_stData.dwPid;
    status.dwItem = m_stData.dwItem;
    _tcsncpy(status.szStatus, szText, _tcslen(szText) + 1);

    DWORD dwWriten;
    WriteFile(m_hPipe, &status, sizeof(PIPESTATUS), &dwWriten, NULL);
}

void CJLwgApp::UnLoad()
{
    LOGER(_T("外挂正常退出"));
    SENDLOG(_T("外挂被卸载了"));

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
            m_pWgDlg->EndDialog(IDOK);
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
