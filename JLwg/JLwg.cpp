#include "stdafx.h"
#include "JLwg.h"
#include "TaskScript.h"
#include "GamecallEx.h"
#include "GameConfig.h"
#include "GameLog.h"



//����ʵ��Ψһ
CJLwgApp theApp;


//��̬����
WNDPROC CJLwgApp::wpOrigGameProc = NULL;
CJLDlg* CJLwgApp::m_pWgDlg = NULL;
HWND CJLwgApp::m_hGameWnd = NULL;




CJLwgApp::CJLwgApp()
{
}

CJLwgApp::~CJLwgApp()
{
}


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
                int result = MessageBox(hwnd, _T("�㰴���� VK_INSERT ����.\nȷ��ִ������?"), NULL, MB_OKCANCEL);
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
            GamecallEx* pcall = GamecallEx::GetInstance();

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
    LOGER(_T("�쳣����"));
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
    AFX_MANAGE_STATE(AfxGetStaticModuleState())

    if(!AfxSocketInit())
    {
        LOGER(_T("�׽��ֳ�ʼ��ʧ��"));
        ExitProcess(0);
        return FALSE;
    }


    //ȫ���쳣����
    SetUnhandledExceptionFilter(TopLevelExceptionHander);


    if(!theApp.WaitGameCreate(20))
    {
        LOGER(_T("�ȴ���Ϸ���ڳ�ʱ"));
        ExitProcess(0);
        return FALSE;
    }
    else
    {
        LOGER(_T("��Ϸ���ڴ���"));
    }


    LOGER(_T("��ʼ������"));
    GameSpend* pGameSpender = GameSpend::GetInstance();
    if(!pGameSpender->Init())
    {
        ExitProcess(0);
        return FALSE;
    }


    LOGER(_T("��������"));
    GameConfig* pConfig = GameConfig::GetInstance();
    pConfig->LoadConfig();


    //��ʼ��
    GamecallEx* pCall = GamecallEx::GetInstance();

//     LOGER(_T("��ʼ����ҹ���"));
//     if(!pCall->Init())
//     {
//         ExitProcess(0);
//         return FALSE;
//     }


    //����Ϸ���ڴ������
    wpOrigGameProc = (WNDPROC)::SetWindowLong(m_hGameWnd, GWL_WNDPROC, (LONG)GameMsgProc);

    //ͨ������
    PIPEDATA& data = theApp.m_stData;
    ::SetWindowText(m_hGameWnd, data.szAccount);


    SENDLOG(_T("�Ի���������"));

    //������ҶԻ���
    m_pWgDlg = new CJLDlg;
    m_pWgDlg->DoModal();



    LOGER(_T("��ұ��ֶ�ж�ص���"));
    
    
    //��������
    pConfig->SaveConfig();
    
    
    if(wpOrigGameProc) 
    {
        ::SetWindowLong(m_hGameWnd, GWL_WNDPROC, (LONG)wpOrigGameProc);
    }
    
    FreeLibraryAndExitThread(theApp.m_hInstance, 0);
    return 0;
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
        if(hGameWnd == NULL) return NULL;
    }
}



BOOL CJLwgApp::WaitGameCreate(int inMaxTime)
{

    //�жϵ�ǰ��Ϸ�Ĵ����Ƿ񴴽�
    for(int i = 0; i < inMaxTime; i++)
    {
        if(isGameWndCreated(GetCurrentProcessId()) != NULL) return TRUE;
        Sleep(1000);
    }

    return FALSE;
}

BOOL CJLwgApp::InitInstance()
{

    //��������
    setlocale(LC_ALL, "chs");

    //1, ��ȡͨ������
    TCHAR szPipe[MAX_PATH];
    wsprintf(szPipe, _T("\\\\.\\Pipe\\JLwg_%d"), GetCurrentProcessId());
    if(!::WaitNamedPipe(szPipe, NMPWAIT_USE_DEFAULT_WAIT))
    {
        TRACE(_T("can't find pipe!"));
        return FALSE;
    }

    // �򿪹ܵ�
    m_hPipe = CreateFile(szPipe, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL) ;
    if(m_hPipe == INVALID_HANDLE_VALUE)
    {
        TRACE(_T("can't open console pipe!")) ;
        ExitProcess(0);
        return FALSE;
    }

    //��ȡ����
    DWORD dwBytesReaded = 0;
    if(!ReadFile(m_hPipe, &m_stData, sizeof(PIPEDATA), &dwBytesReaded, NULL))
    {
        TRACE(_T("can't read pipe data!"));
        ExitProcess(0);
        return FALSE;
    }

    //���óɲ��ȴ�ģʽ
    DWORD dwMode = PIPE_NOWAIT | PIPE_READMODE_MESSAGE;
    SetNamedPipeHandleState(m_hPipe, &dwMode, NULL, NULL);


    //2, ��ʼ����־
    TCHAR szLogPath[MAX_PATH];
    GetModuleFileName(AfxGetInstanceHandle(), szLogPath, MAX_PATH);
    PathRemoveFileSpec(szLogPath);
    PathAppend(szLogPath, _T("��־"));
    if(!PathFileExists(szLogPath))
    {
        //������־Ŀ¼
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

    //������־��
    LOGER(_T("#�������"));

    //����߳�
    HANDLE hThread = ::CreateThread(NULL, 0, WgThread, this, 0, 0);
    if(hThread == NULL)
    {
        LOGER(_T("���̴߳���ʧ��"));
        ExitProcess(0);
        return FALSE;
    }

    _ASSERTE(hThread != NULL);
    CloseHandle(hThread);

    return TRUE;
}


void CJLwgApp::SendStatus(TCHAR szText[])
{
    PIPESTATUS status;
    status.dwPid = m_stData.dwPid;
    status.dwItem = m_stData.dwItem;
    _tcsncpy(status.szStatus, szText, _tcslen(szText) + 1);

    DWORD dwWriten;
    WriteFile(m_hPipe, &status, sizeof(PIPESTATUS), &dwWriten, NULL);
}


int CJLwgApp::ExitInstance()
{
    LOGER(_T("�������Ϸ�����˳���"));
 
    
    m_pWgDlg->EndDialog(IDOK);
    
    
    //��������
    GameConfig* pConfig = GameConfig::GetInstance();
    pConfig->SaveConfig();
    
    
    if(wpOrigGameProc)
    {
        ::SetWindowLong(m_hGameWnd, GWL_WNDPROC, (LONG)wpOrigGameProc);
    }
    

    return CWinApp::ExitInstance();
}
