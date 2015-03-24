//JLwg.cpp
#include "stdafx.h"
#include "JLwg.h"
#include "JLDlg.h"
#include "TaskScript.h"
#include "GamecallEx.h"


#include "GameConfig.h"
#include "..\common\CHook.h"
#include "..\common\common.h"
#include "..\common\ShareMem.h"
#include "..\common\logger.h"
#include "..\common\inject.h"
#include "..\common\inlinehook.h"


#include "..\Optimizer\Optimizer.h"
#pragma comment(lib, "..\\Optimizer\\Release\\Optimizer")


//程序实例唯一
CJLwgApp CWinApp;


//静态变量
WNDPROC CJLwgApp::wpOrigGameProc = NULL;
CJLDlg* CJLwgApp::m_pWgDlg = NULL;


//钩游戏的消息窗口
LRESULT CALLBACK CJLwgApp::GameMsgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    if(CJLwgApp::m_pWgDlg == NULL) {
        return CallWindowProc(wpOrigGameProc, hwnd, uMsg, wParam, lParam);
    }


    //调出外挂
    switch(uMsg) {

        case WM_KEYDOWN: {
            if(wParam == VK_INSERT) {
                int result = MessageBox(
                                 hwnd,
                                 _T("你按下了 VK_INSERT 按键.\n确认执行任务?"),
                                 NULL,
                                 MB_OKCANCEL);
                if(result == IDOK) {
                    m_pWgDlg->OnGotask();
                }

            }
            else if(wParam == VK_DELETE) {
                m_pWgDlg->OnStopTask();
            }

            else if(wParam == VK_END) {
                if(m_pWgDlg->IsWindowVisible()) {
                    m_pWgDlg->ShowWindow(SW_HIDE);
                }
                else {
                    m_pWgDlg->ShowWindow(SW_SHOWNA);
                }

            }
            break;
        }



        case WM_CUSTOM_GCALL: {
            //获取游戏外挂功能
            GamecallEx& gcall = *GamecallEx::Instance();

            //此处实现游戏call的调用
            return gcall.call((DWORD)wParam, (LPVOID*)lParam);
        }


        case WM_MOVE: {
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

    while(nCount < 1000) {
        nCount++;
        if(!StackWalk(IMAGE_FILE_MACHINE_I386,
                      GetCurrentProcess(), GetCurrentThread(),
                      &frame, pContext,
                      NULL,
                      SymFunctionTableAccess,
                      SymGetModuleBase, NULL)) {
            // Error occured.
            break;
        }


        // get module name
        IMAGEHLP_MODULE module;
        memset(&module, 0, sizeof(IMAGEHLP_MODULE));
        module.SizeOfStruct = sizeof(IMAGEHLP_MODULE);

        if(!SymGetModuleInfo(GetCurrentProcess(),
                             frame.AddrPC.Offset, &module)) {
            strcpy(module.ModuleName, "Unknown");
        }


        DWORD dwOffsetFromSmybol = 0;
        TCHAR szSym[MAX_SYM_SIZE];
        TCHAR szFrame[FRAME_MSG_SIZE];
        PIMAGEHLP_SYMBOL pSymbol = (PIMAGEHLP_SYMBOL)szSym;
        ZeroMemory(pSymbol, sizeof(IMAGEHLP_SYMBOL));


        pSymbol->MaxNameLength = MAX_SYM_SIZE - sizeof(IMAGEHLP_SYMBOL) / sizeof(TCHAR);
        pSymbol->Address = frame.AddrPC.Offset;
        if(SymGetSymFromAddr(GetCurrentProcess(), frame.AddrPC.Offset, &dwOffsetFromSmybol, pSymbol)) {
            _stprintf(szFrame, _T("%S!%S\n"), module.ModuleName, pSymbol->Name);
            _tcscat(szText, szFrame);
        }
        else {
            _stprintf(szFrame, _T("%S!%08x\n"), module.ModuleName, pSymbol->Address);
            _tcscat(szText, szFrame);
        }
        if(frame.AddrFrame.Offset == 0 || frame.AddrReturn.Offset == 0) {
            // End of stack.
            break;
        }
    }

    MessageBox(NULL, szText, _T("游戏崩溃"), MB_OK);
    return EXCEPTION_CONTINUE_SEARCH;
}


DWORD CALLBACK CJLwgApp::WgThread(LPVOID pParam)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    //安装一个全局的未处理异常
    //AddVectoredExceptionHandler(1, TopLevelExceptionHander);
    SetUnhandledExceptionFilter(TopLevelExceptionHander);

    //设置区域
    setlocale(LC_ALL, "chs");

    //获取配置对象
    GameConfig* pConfig = GameConfig::Instance();
    GamecallEx& gcall = *GamecallEx::Instance();
    JLShareMem* pJLShareMem = JLShareMem::Instance();
    GameSpend* pGameSpender = GameSpend::Instance();

    //打开共享内存
    if(!pJLShareMem->Open(SHAREOBJNAME)) return 0;

    #ifdef _DEBUG
    pJLShareMem->Dump(GetCurrentProcessId());
    #endif

    //获取本DLL的共享数据
    SHAREINFO* pSMem = pJLShareMem->Get(GetCurrentProcessId());
    if(pSMem == NULL) return 0;

    //初始化
    if(!pConfig->Init()) return 0;
    if(!gcall.Init()) return 0;
    if(!pGameSpender->Init()) return 0;

    //加载配置
    pConfig->LoadConfig();

    //改游戏窗口处理过程
    wpOrigGameProc = (WNDPROC)::SetWindowLong(gcall.GetGameWnd(), GWL_WNDPROC, (LONG)GameMsgProc);

    //改游戏窗口标题
    ::SetWindowText(gcall.GetGameWnd(), pSMem->szName);


    //准备游戏线程
    gcall.InitThread();


    //创建外挂对话框
    m_pWgDlg = new CJLDlg;
    m_pWgDlg->Create(CJLDlg::IDD);
    m_pWgDlg->ShowWindow(SW_SHOW);

    //改外挂标题
    m_pWgDlg->SetWindowText(pSMem->szName);


    //创建消息循环
    MSG msg;
    BOOL bRet;
    while((bRet = GetMessage(&msg, NULL, 0, 0)) != 0) {
        if(bRet == -1) break;
        if(!IsWindow(m_pWgDlg->m_hWnd) || !IsDialogMessage(m_pWgDlg->m_hWnd, &msg)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    //卸载游戏功能
    gcall.UnInit();

    TRACE(_T("消息循环正常退出了"));
    if(wpOrigGameProc) {
        ::SetWindowLong(gcall.GetGameWnd(), GWL_WNDPROC, (LONG)wpOrigGameProc);
    }

    FreeLibraryAndExitThread(AfxGetInstanceHandle(), 0);
    return 0;
}


CJLwgApp::CJLwgApp()
{

}

CJLwgApp::~CJLwgApp()
{

}

BOOL CJLwgApp::InitInstance()
{
    //外挂线程
    HANDLE hWgThread = ::CreateThread(NULL, 0, WgThread, 0, 0, 0);
    CloseHandle(hWgThread);

    return TRUE;
}


int CJLwgApp::ExitInstance()
{
    return CWinApp::ExitInstance();
}

