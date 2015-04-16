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
            GamecallEx *pcall = GamecallEx::GetInstance();

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

    //获取配置对象
    GameConfig* pConfig = GameConfig::GetInstance();

#ifndef TEST_CONFIG
<<<<<<< Updated upstream
    GamecallEx *pCall = GamecallEx::GetInstance();
=======
    GamecallEx *pcall = GamecallEx::GetInstance();
>>>>>>> Stashed changes
    GameSpend* pGameSpender = GameSpend::GetInstance();
#endif


    //初始化
    if(!pConfig->Init()) return 0;
#ifndef TEST_CONFIG
<<<<<<< Updated upstream
    if(!pCall->Init()) return 0;
=======
    if(!pcall->Init()) return 0;
>>>>>>> Stashed changes
    if(!pGameSpender->Init()) return 0;
#endif


    SHAREINFO* pMyData = pConfig->m_pMyData;

    //加载配置
    pConfig->LoadConfig();


    //改游戏窗口处理过程
#ifndef TEST_CONFIG
    wpOrigGameProc = (WNDPROC)::SetWindowLong(m_hGameWnd, GWL_WNDPROC, (LONG)GameMsgProc);


    //改游戏窗口标题
    ::SetWindowText(m_hGameWnd, pMyData->szName);

#endif

    //创建外挂对话框
    m_pWgDlg = new CJLDlg;
    m_pWgDlg->Create(CJLDlg::IDD);
    m_pWgDlg->ShowWindow(SW_SHOW);

    //改标题
#ifndef TEST_CONFIG
    m_pWgDlg->SetWindowText(pMyData->szName);
#endif

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
#ifndef TEST_CONFIG
    pCall->UnInit();
#endif //TEST_CONFIG

    //保存配置
    pConfig->SaveConfig();

#ifndef TEST_CONFIG
    TRACE(_T("消息循环正常退出了"));
    if(wpOrigGameProc)
    {
        ::SetWindowLong(m_hGameWnd, GWL_WNDPROC, (LONG)wpOrigGameProc);
    }
#endif //TEST_CONFIG

    FreeLibraryAndExitThread(AfxGetInstanceHandle(), 0);
    return 0;
}


CJLwgApp::CJLwgApp()
{
    OutputDebugString(_T("CJLwgApp()"));
}

CJLwgApp::~CJLwgApp()
{
    OutputDebugString(_T("~CJLwgApp()"));
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


//等待游戏窗口创建
//等待时间25秒
BOOL CJLwgApp::WaitGameCreate()
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

BOOL CJLwgApp::InitInstance()
{

    //安装一个全局的未处理异常
    //AddVectoredExceptionHandler(1, TopLevelExceptionHander);
    SetUnhandledExceptionFilter(TopLevelExceptionHander);

    //设置区域
    setlocale(LC_ALL, "chs");


    try
    {
        log.open(_T("test.cppp"));
        log.info(_T("Hello WOrlf"));

        //初始化套接字
        if(!AfxSocketInit())
        {
            log.info(_T("套接字初始化失败"));
            return FALSE;
        }


        //外挂线程
        HANDLE hThread = ::CreateThread(NULL, 0, WgThread, 0, 0, 0);
        CloseHandle(hThread);

        log.info(_T("创建游戏线程"));
    }
    catch(runtime_error err)
    {
    }

    return TRUE;
}


int CJLwgApp::ExitInstance()
{
    return CWinApp::ExitInstance();
}

