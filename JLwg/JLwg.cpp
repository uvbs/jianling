//JLwg.cpp

#include "stdafx.h"
#include "JLwg.h"
#include "JLDlg.h"
#include "TaskScript.h"
#include "GamecallEx.h"

#include "..\common\CCHook.h"
#include "..\common\common.h"
#include "..\common\logger.h"
#include "..\common\inject.h"
#include "..\common\inlinehook.h"





CJLwgApp CWinApp;
GamecallEx gcall;            //游戏call



WNDPROC CJLwgApp::wpOrigGameProc = NULL;
CJLDlg* CJLwgApp::m_pWgDlg = NULL;


//此处钩游戏的消息窗口
//按键  和 一个自定义的消息
LRESULT CALLBACK CJLwgApp::GameMsgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    if(CJLwgApp::m_pWgDlg == NULL)
        return CallWindowProc(wpOrigGameProc, hwnd, uMsg, wParam, lParam);


    //调出外挂
    switch(uMsg)
    {

        case WM_KEYDOWN:
            {
                if(wParam == VK_INSERT)
                {
                    int result = MessageBox(hwnd, _T("你按下了 VK_INSERT 按键.\n确认执行任务?"), NULL, MB_OKCANCEL);
                    if(result == IDOK)
                        m_pWgDlg->OnGotask();

                }
                else if(wParam == VK_DELETE)
                    m_pWgDlg->OnStopTask();

                else if(wParam == VK_END)
                {
                    if(m_pWgDlg->IsWindowVisible())
                        m_pWgDlg->ShowWindow(SW_HIDE);
                    else
                        m_pWgDlg->ShowWindow(SW_SHOWNA);

                }

            }
            break;


        case WM_CUSTOM_GCALL:
            {
                //此处实现游戏call的调用
                return gcall.call((DWORD)wParam, (LPVOID*)lParam);
            }
        case WM_MOVE:
            {
                int xPos = (int)(short)LOWORD(lParam);   // horizontal position
                int yPos = (int)(short)HIWORD(lParam);   // vertical position

                RECT rect;
                GetWindowRect(hwnd, &rect);
                int width = rect.right - rect.left;
                m_pWgDlg->SetWindowPos(NULL, xPos + width, yPos, 0, 0, SWP_NOSIZE | SWP_NOACTIVATE);
            }
            break;
    }

    return CallWindowProc(wpOrigGameProc, hwnd, uMsg, wParam, lParam);
}


LONG CALLBACK TopLevelExceptionHander(EXCEPTION_POINTERS* ExceptionInfo)
{
    const int FRAME_MSG_SIZE = MAX_PATH * 2;
    const int MAX_SYM_SIZE = MAX_PATH * 4;

    TCHAR szText[BUFSIZ] = {0};
    FILE* file = _tfopen(_T("call stack.txt"), _T("a+"));


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

    while(nCount < 1000)
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
            strcpy(module.ModuleName, "Unknown");


        DWORD dwOffsetFromSmybol = 0;
        TCHAR szSym[MAX_SYM_SIZE];
        TCHAR szFrame[FRAME_MSG_SIZE];
        PIMAGEHLP_SYMBOL pSymbol = (PIMAGEHLP_SYMBOL)szSym;
        ZeroMemory(pSymbol, sizeof(IMAGEHLP_SYMBOL));


        pSymbol->MaxNameLength = MAX_SYM_SIZE - sizeof(IMAGEHLP_SYMBOL) / sizeof(TCHAR);
        pSymbol->Address = frame.AddrPC.Offset;
        if(SymGetSymFromAddr(GetCurrentProcess(), frame.AddrPC.Offset, &dwOffsetFromSmybol, pSymbol))
        {
            _stprintf(szFrame, _T("%s!%s\n"), module.ModuleName, pSymbol->Name);
            _tcscat(szText, szFrame);
        }
        else
        {
            _stprintf(szFrame, _T("%s!%08x\n"), module.ModuleName, pSymbol->Address);
            _tcscat(szText, szFrame);
        }
        if(frame.AddrFrame.Offset == 0 || frame.AddrReturn.Offset == 0)
        {
            // End of stack.
            break;
        }
    }
    _fputts(szText, file);
    fflush(file);
    return EXCEPTION_CONTINUE_SEARCH;
}


DWORD CALLBACK CJLwgApp::WgThread(LPVOID pParam)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());
    setlocale(LC_ALL, "chs");

    //安装一个全局的未处理异常
    //AddVectoredExceptionHandler(1, TopLevelExceptionHander);

    //先外挂的初始化
    if(gcall.Init() == FALSE)
    {
        ExitProcess(0);
        return 0;
    }


    wpOrigGameProc = (WNDPROC)::SetWindowLong(gcall.GetGamehWnd(), GWL_WNDPROC, (LONG)GameMsgProc);
    CString strTitle = gcall.GetAccountInfo()->szName;
    ::SetWindowText(gcall.GetGamehWnd(), (LPCTSTR)strTitle);

    m_pWgDlg = new CJLDlg;
    m_pWgDlg->Create(CJLDlg::IDD);
    m_pWgDlg->ShowWindow(SW_SHOW);
    m_pWgDlg->SetWindowText(strTitle);

    //创建消息循环
    BOOL bRet;
    MSG msg;
    while((bRet = GetMessage(&msg, NULL, 0, 0)) != 0)
    {
        if(bRet == -1)
        {
            // handle the error and possibly exit
        }
        else if(!IsWindow(m_pWgDlg->m_hWnd) || !IsDialogMessage(m_pWgDlg->m_hWnd, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }


    TRACE(_T("消息循环正常退出了"));
    if(wpOrigGameProc)
        ::SetWindowLong(gcall.GetGamehWnd(), GWL_WNDPROC, (LONG)wpOrigGameProc);

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
    //创建一个线程
    HANDLE hWgThread = ::CreateThread(NULL, 0, CJLwgApp::WgThread, 0, 0, 0);
    CloseHandle(hWgThread);
    return TRUE;
}


int CJLwgApp::ExitInstance()
{
    return CWinApp::ExitInstance();
}

