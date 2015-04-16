#include "stdafx.h"
#include "JLwg.h"
#include "TaskScript.h"
#include "GamecallEx.h"
#include "GameConfig.h"
#include "GameLog.h"

//����ʵ��Ψһ
CJLwgApp CWinApp;


//��̬����
WNDPROC CJLwgApp::wpOrigGameProc = NULL;
CJLDlg* CJLwgApp::m_pWgDlg = NULL;
HWND CJLwgApp::m_hGameWnd = NULL;

//����Ϸ����Ϣ����
LRESULT CALLBACK CJLwgApp::GameMsgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    if(CJLwgApp::m_pWgDlg == NULL)
    {
        return CallWindowProc(wpOrigGameProc, hwnd, uMsg, wParam, lParam);
    }


    //�������
    switch(uMsg)
    {

        case WM_KEYDOWN:
        {
            if(wParam == VK_INSERT)
            {
                int result = MessageBox(
                                 hwnd,
                                 _T("�㰴���� VK_INSERT ����.\nȷ��ִ������?"),
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
            //��ȡ��Ϸ��ҹ���
            GamecallEx *pcall = GamecallEx::GetInstance();

            //�˴�ʵ����Ϸcall�ĵ���
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

    MessageBox(NULL, szText, _T("��Ϸ����"), MB_OK);
    return EXCEPTION_CONTINUE_SEARCH;
}


DWORD CALLBACK CJLwgApp::WgThread(LPVOID pParam)
{

    //��ȡ���ö���
    GameConfig* pConfig = GameConfig::GetInstance();

#ifndef TEST_CONFIG
<<<<<<< Updated upstream
    GamecallEx *pCall = GamecallEx::GetInstance();
=======
    GamecallEx *pcall = GamecallEx::GetInstance();
>>>>>>> Stashed changes
    GameSpend* pGameSpender = GameSpend::GetInstance();
#endif


    //��ʼ��
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

    //��������
    pConfig->LoadConfig();


    //����Ϸ���ڴ������
#ifndef TEST_CONFIG
    wpOrigGameProc = (WNDPROC)::SetWindowLong(m_hGameWnd, GWL_WNDPROC, (LONG)GameMsgProc);


    //����Ϸ���ڱ���
    ::SetWindowText(m_hGameWnd, pMyData->szName);

#endif

    //������ҶԻ���
    m_pWgDlg = new CJLDlg;
    m_pWgDlg->Create(CJLDlg::IDD);
    m_pWgDlg->ShowWindow(SW_SHOW);

    //�ı���
#ifndef TEST_CONFIG
    m_pWgDlg->SetWindowText(pMyData->szName);
#endif

    //������Ϣѭ��
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


    //ж����Ϸ����
#ifndef TEST_CONFIG
    pCall->UnInit();
#endif //TEST_CONFIG

    //��������
    pConfig->SaveConfig();

#ifndef TEST_CONFIG
    TRACE(_T("��Ϣѭ�������˳���"));
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

//�ж���Ϸ�����Ƿ񴴽�
HWND CJLwgApp::isGameWndCreated(DWORD dwPid)
{
    HWND hGameWnd = FindWindowEx(NULL, NULL, _T("LaunchUnrealUWindowsClient"), NULL);

    if(hGameWnd == NULL) return NULL;

    //�ж���Ϸ���ڴ������
    for(;;)
    {
        DWORD dwWndOfPid;
        GetWindowThreadProcessId(hGameWnd, &dwWndOfPid);

        //�ҵ�
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


//�ȴ���Ϸ���ڴ���
//�ȴ�ʱ��25��
BOOL CJLwgApp::WaitGameCreate()
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

BOOL CJLwgApp::InitInstance()
{

    //��װһ��ȫ�ֵ�δ�����쳣
    //AddVectoredExceptionHandler(1, TopLevelExceptionHander);
    SetUnhandledExceptionFilter(TopLevelExceptionHander);

    //��������
    setlocale(LC_ALL, "chs");


    try
    {
        log.open(_T("test.cppp"));
        log.info(_T("Hello WOrlf"));

        //��ʼ���׽���
        if(!AfxSocketInit())
        {
            log.info(_T("�׽��ֳ�ʼ��ʧ��"));
            return FALSE;
        }


        //����߳�
        HANDLE hThread = ::CreateThread(NULL, 0, WgThread, 0, 0, 0);
        CloseHandle(hThread);

        log.info(_T("������Ϸ�߳�"));
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

