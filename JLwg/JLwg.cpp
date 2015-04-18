#include "stdafx.h"
#include "JLwg.h"
#include "TaskScript.h"
#include "GamecallEx.h"
#include "GameConfig.h"
#include "GameLog.h"

//程序实例唯一
CJLwgApp CWinApp;


//静态变量
WNDPROC CJLwgApp::wpOrigGameProc = NULL;
CJLDlg* CJLwgApp::m_pWgDlg = NULL;
HWND CJLwgApp::m_hGameWnd = NULL;

//钩游戏的消息窗口
LRESULT CALLBACK CJLwgApp::GameMsgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    if(CJLwgApp::m_pWgDlg == NULL)
    {
        return CallWindowProc(wpOrigGameProc, hwnd, uMsg, wParam, lParam);
    }


    //调出外挂
    switch(uMsg)
    {

        case WM_KEYDOWN:
        {
            if(wParam == VK_INSERT)
            {
                int result = MessageBox(
                                 hwnd,
                                 _T("你按下了 VK_INSERT 按键.\n确认执行任务?"),
                                 NULL,
                                 MB_OKCANCEL);
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
            //获取游戏外挂功能
            GamecallEx* pcall = GamecallEx::GetInstance();

            //此处实现游戏call的调用
            return pcall->call((DWORD)wParam, (LPVOID*)lParam);
        }


        case WM_MOVE:
        {
            int xPos = (int)(short)LOWORD(lParam);   // horizontal position
            int yPos = (int)(short)HIWORD(lParam);   // vertical position

            RECT rect;
            GetWindowRect(hwnd, &rect);
            int width = rect.right - rect.left;
            m_pWgDlg->SetWindowPos(NULL, xPos + width, yPos, 0, 0, SWP_NOSIZE | SWP_NOACTIVATE);
            break;
        }

    }

    return CallWindowProc(wpOrigGameProc, hwnd, uMsg, wParam, lParam);
}


LONG CALLBACK TopLevelExceptionHander(EXCEPTION_POINTERS* ExceptionInfo)
{
    LOGER(_T("异常处理"));
    const int FRAME_MSG_SIZE = MAX_PATH * 2;
    const int MAX_SYM_SIZE = MAX_PATH * 4;

    TCHAR szText[BUFSIZ] = {0};

    STACKFRAME frame;
    int nCount = 0;
    DWORD dwTimeMS;

    CONTEXT* pContext = ExceptionInfo->ContextRecord;
    dwTimeMS = GetTickCount();


    memset(&frame, 0, sizeof(frame));

    frame.AddrPC.Offset = pContext->Eip;
    frame.AddrPC.Mode = AddrModeFlat;
    frame.AddrFrame.Offset = pContext->Ebp;
    frame.AddrFrame.Mode = AddrModeFlat;
    frame.AddrStack.Offset = pContext->Esp;
    frame.AddrStack.Mode = AddrModeFlat;

    while(nCount < 20)
    {
        nCount++;
        if(!StackWalk(IMAGE_FILE_MACHINE_I386,
                      GetCurrentProcess(), GetCurrentThread(),
                      &frame, pContext,
                      NULL,
                      SymFunctionTableAccess,
                      SymGetModuleBase, NULL))
        {
            // Error occured.
            break;
        }


        // get module name
        IMAGEHLP_MODULE module;
        memset(&module, 0, sizeof(IMAGEHLP_MODULE));
        module.SizeOfStruct = sizeof(IMAGEHLP_MODULE);

        if(!SymGetModuleInfo(GetCurrentProcess(),
                             frame.AddrPC.Offset, &module))
        {
            strcpy(module.ModuleName, "Unknown");
        }


        DWORD dwOffsetFromSmybol = 0;
        TCHAR szSym[MAX_SYM_SIZE];
        TCHAR szFrame[FRAME_MSG_SIZE];
        PIMAGEHLP_SYMBOL pSymbol = (PIMAGEHLP_SYMBOL)szSym;
        ZeroMemory(pSymbol, sizeof(IMAGEHLP_SYMBOL));


        pSymbol->MaxNameLength = MAX_SYM_SIZE - sizeof(IMAGEHLP_SYMBOL) / sizeof(TCHAR);
        pSymbol->Address = frame.AddrPC.Offset;
        if(SymGetSymFromAddr(GetCurrentProcess(), frame.AddrPC.Offset, &dwOffsetFromSmybol, pSymbol))
        {
            _stprintf(szFrame, _T("%S!%S\n"), module.ModuleName, pSymbol->Name);
            _tcscat(szText, szFrame);
        }
        else
        {
            _stprintf(szFrame, _T("%S!%08x\n"), module.ModuleName, pSymbol->Address);
            _tcscat(szText, szFrame);
        }
        if(frame.AddrFrame.Offset == 0 || frame.AddrReturn.Offset == 0)
        {
            // End of stack.
            break;
        }
    }

    MessageBox(NULL, szText, _T("游戏崩溃"), MB_OK);
    return EXCEPTION_CONTINUE_SEARCH;
}



DWORD CALLBACK CJLwgApp::WgThread(LPVOID pParam)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState())


    //全局异常处理
    SetUnhandledExceptionFilter(TopLevelExceptionHander);


    //获取配置对象
    CJLwgApp* pApp = (CJLwgApp*)pParam;
    GameConfig* pConfig = GameConfig::GetInstance();
    GamecallEx* pCall = GamecallEx::GetInstance();
    GameSpend* pGameSpender = GameSpend::GetInstance();


    if(!pApp->WaitGameCreate(20))
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
    if(!pGameSpender->Init())
    {
        ExitProcess(0);
        return FALSE;
    }


    LOGER(_T("加载配置"));
    pConfig->LoadConfig();


    //初始化
//     LOGER(_T("初始化外挂功能"));
//     if(!pCall->Init())
//     {
//         ExitProcess(0);
//         return FALSE;
//     }


    //改游戏窗口处理过程
    wpOrigGameProc = (WNDPROC)::SetWindowLong(m_hGameWnd, GWL_WNDPROC, (LONG)GameMsgProc);


    //改游戏窗口标题
    ::SetWindowText(m_hGameWnd, _T(""));

    //创建外挂对话框
    m_pWgDlg = new CJLDlg;
    m_pWgDlg->Create(CJLDlg::IDD);
    m_pWgDlg->ShowWindow(SW_SHOW);

    //改标题
    m_pWgDlg->SetWindowText(_T(""));


    //创建消息循环
    MSG msg;
    BOOL bRet;
    while((bRet = GetMessage(&msg, NULL, 0, 0)) != 0)
    {
        if(bRet == -1) break;
        if(!IsWindow(m_pWgDlg->m_hWnd) || !IsDialogMessage(m_pWgDlg->m_hWnd, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }


    //卸载游戏功能
    pCall->UnInit();

    //保存配置
    pConfig->SaveConfig();

    if(wpOrigGameProc)
    {
        ::SetWindowLong(m_hGameWnd, GWL_WNDPROC, (LONG)wpOrigGameProc);
    }


    FreeLibraryAndExitThread(AfxGetApp()->m_hInstance, 0);
    return 0;
}


CJLwgApp::CJLwgApp()
{
}

CJLwgApp::~CJLwgApp()
{
}

//判断游戏窗口是否创建
HWND CJLwgApp::isGameWndCreated(DWORD dwPid)
{
    HWND hGameWnd = FindWindowEx(NULL, NULL, _T("LaunchUnrealUWindowsClient"), NULL);

    if(hGameWnd == NULL) return NULL;

    //判断游戏窗口创建完成
    for(;;)
    {
        DWORD dwWndOfPid;
        GetWindowThreadProcessId(hGameWnd, &dwWndOfPid);

        //找到
        if(dwPid == dwWndOfPid)
        {
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



BOOL CJLwgApp::WaitGameCreate(int inMaxTime)
{

    //判断当前游戏的窗口是否创建
    for(int i = 0; i < inMaxTime; i++)
    {
        if(isGameWndCreated(GetCurrentProcessId()) != NULL)
        {
            return TRUE;
        }

        Sleep(1000);
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
    if(!::WaitNamedPipe(szPipe, NMPWAIT_WAIT_FOREVER))
    {
        TRACE(_T("can't find pipe!"));
        return FALSE;
    }

    // 打开管道
    HANDLE hPipe = CreateFile(szPipe, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL) ;
    if(hPipe == INVALID_HANDLE_VALUE)
    {
        TRACE(_T("can't open console pipe!")) ;
        ExitProcess(0);
        return FALSE;
    }

    //读取数据
    DWORD dwBytesReaded = 0;
    if(!ReadFile(hPipe, &m_stData, sizeof(PIPEDATA), &dwBytesReaded, NULL))
    {
        TRACE(_T("can't read pipe data!"));
        ExitProcess(0);
        return FALSE;
    }


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

    //至此日志能用了
    LOGER(_T("外挂启动"));


    if(!AfxSocketInit())
    {
        LOGER(_T("套接字初始化失败"));
        ExitProcess(0);
        return FALSE;
    }


    //外挂线程
    HANDLE hThread = ::CreateThread(NULL, 0, WgThread, 0, 0, 0);
    if(hThread == NULL)
    {
        LOGER(_T("主线程创建失败"));
        ExitProcess(0);
        return FALSE;
    }

    _ASSERTE(hThread != NULL);
    CloseHandle(hThread);

    return TRUE;
}


int CJLwgApp::ExitInstance()
{
    OutputDebugString(_T("外挂退出"));
    return CWinApp::ExitInstance();
}

