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
    m_hPipe = INVALID_HANDLE_VALUE;
}

CJLwgApp::~CJLwgApp()
{
}


//����Ϸ����Ϣ����
LRESULT CALLBACK CJLwgApp::GameMsgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    if(!CJLwgApp::m_pWgDlg)
    {
        return CallWindowProc(wpOrigGameProc, hwnd, uMsg, wParam, lParam);
    }


    //�������
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
            //�˴�ʵ����Ϸcall�ĵ���
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
        LOGER(_T("�׽��ֳ�ʼ��ʧ��"));
        ExitProcess(0);
        return FALSE;
    }

    if(!theApp.WaitGameCreate(30))
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
    if(!GameSpend::GetInstance()->Init())
    {
        LOGER(_T("��ʼ������ʧ��"));
        ExitProcess(0);
        return FALSE;
    }


    LOGER(_T("��������"));
    if(!GameConfig::GetInstance()->LoadConfig())
    {
        LOGER(_T("���������ļ�ʧ��"));
        ExitProcess(0);
        return FALSE;
    }


    LOGER(_T("��ʼ����ҹ���"));
//     if(!GamecallEx::GetInstance()->Init())
//     {
//         LOGER(_T("��ҹ��ܳ�ʼ��ʧ��"));
//         ExitProcess(0);
//         return FALSE;
//     }


    LOGER(_T("����������"));
    SENDLOG(_T("����������"));
    
    //����Ϸ���ڴ���
    wpOrigGameProc = (WNDPROC)::SetWindowLong(m_hGameWnd, GWL_WNDPROC, (LONG)GameMsgProc);
    ::SetWindowText(m_hGameWnd, theApp.m_stData.szAccount);
    
    
    //������Ի���
    m_pWgDlg = new CJLDlg;
    m_pWgDlg->DoModal();

    TRACE(_T("CJLDlg DoModal ret"));
    theApp.UnLoad();
    FreeLibraryAndExitThread(theApp.m_hInstance, 0);
    return 0;
}



//�ȴ���Ϸ���ڴ���
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

            //�ҵ�
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
    HANDLE hwgThread = ::CreateThread(NULL, 0, WgThread, this, 0, 0);
    if(hwgThread == NULL)
    {
        LOGER(_T("���̴߳���ʧ��"));
        ExitProcess(0);
        return FALSE;
    }

    CloseHandle(hwgThread);
    return TRUE;
}

//�����̨ͨ��
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
    LOGER(_T("��������˳�"));
    SENDLOG(_T("��ұ�ж����"));

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
