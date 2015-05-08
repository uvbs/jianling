#include "stdafx.h"
#include "JLwg.h"
#include "TaskScript.h"
#include "GamecallEx.h"
#include "GameConfig.h"
#include "JLDlg.h"
#include "GameSpend.h"
#include "LuaScript.h"



IMPLEMENT_SINGLETON(GameLog)



//����ʵ��Ψһ
CJLwgApp theApp;


CJLwgApp::CJLwgApp()
{
    m_hPipe = INVALID_HANDLE_VALUE;
    _tcscpy(m_stData.szAccount, _T("�޿���̨"));
    _tcscpy(m_stData.szConfig, _T("default.ini"));
    _tcscpy(m_stData.szScript, _T("default.lua"));
}

CJLwgApp::~CJLwgApp()
{
}


//����Ϸ����Ϣ����
LRESULT CALLBACK GameMsgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{

    if(!theApp.m_pWgDlg || !theApp.m_pWgDlg->GetSafeHwnd())
    {
        return CallWindowProc(theApp.wpOrigGameProc, hwnd, uMsg, wParam, lParam);
    }

    //�������
    switch(uMsg)
    {

    //��Ϊ���򱣻�������, ������Ϸ�����˳�ʱ, ���ģ�鲢���ᱻ֪ͨ��
    case WM_DESTROY:
        {
            theApp.m_pWgDlg->OnUnloadwg();
            break;
        }


    case WM_MOVE:
        {
            RECT rect;
            GetWindowRect(hwnd, &rect);
            theApp.m_pWgDlg->SetWindowPos(NULL, rect.right, rect.top, 0, 0, SWP_NOSIZE | SWP_NOACTIVATE);
            break;
        }

    case WM_KEYDOWN:
        {

            if(wParam == VK_INSERT)
            {
                int result = MessageBox(hwnd, _T("�㰴���� VK_INSERT ����.\nȷ��ִ������?"), NULL, MB_OKCANCEL);
                if(result == IDOK)
                {
                    theApp.m_pWgDlg->OnGotask();
                }
            }
            else if(wParam == VK_DELETE)
            {
                theApp.m_pWgDlg->OnStopTask();
            }
            else if(wParam == VK_END)
            {
                if(theApp.m_pWgDlg->IsWindowVisible())
                {
                    theApp.m_pWgDlg->ShowWindow(SW_HIDE);
                }
                else
                {
                    theApp.m_pWgDlg->ShowWindow(SW_SHOWNA);
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


    return CallWindowProc(theApp.wpOrigGameProc, hwnd, uMsg, wParam, lParam);
}


DWORD CALLBACK CJLwgApp::WgThread(LPVOID pParam)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState())

    //
    //DebugBreak();

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


    if(!GameSpend::GetInstance()->Init())
    {
        LOGER(_T("��ʼ������ʧ��"));
        ExitProcess(0);
        return FALSE;
    }


    if(!GameConfig::GetInstance()->LoadConfig())
    {
        LOGER(_T("���������ļ�ʧ��"));
        ExitProcess(0);
        return FALSE;
    }



    //����һ��lua״̬
    if(!LuaScript::GetInstance()->Init())
    {
        LOGER(_T("�ű���ʼ��ʧ��"));
        ExitProcess(0);
        return FALSE;
    }

    //��ʼ��call��
    if(!GamecallEx::GetInstance()->Init())
    {
        LOGER(_T("��ҹ��ܳ�ʼ��ʧ��"));
        ExitProcess(0);
        return 0;
    }

    LOGER(_T("�������"));



    //����Ϸ���ڴ���
    theApp.wpOrigGameProc = (WNDPROC)::SetWindowLong(theApp.m_hGameWnd, GWL_WNDPROC, (LONG)GameMsgProc);
    ::SetWindowText(theApp.m_hGameWnd, theApp.m_stData.szAccount);


    //������Ի���
    theApp.m_pWgDlg = new CJLDlg;
    theApp.m_pWgDlg->DoModal();



    GamecallEx::GetInstance()->UnLoad();


    if(theApp.m_hPipe != INVALID_HANDLE_VALUE)
    {
        CloseHandle(theApp.m_hPipe);
    }


    if(theApp.wpOrigGameProc)
    {
        ::SetWindowLong(theApp.m_hGameWnd, GWL_WNDPROC, (LONG)theApp.wpOrigGameProc);
    }

    LOGER(_T("ж��"));
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

BOOL CJLwgApp::InitPipe()
{
    //1, ��ȡͨ������
    TCHAR szPipe[MAX_PATH];
    wsprintf(szPipe, _T("\\\\.\\Pipe\\JLwg_%d"), GetCurrentProcessId());
    if(!::WaitNamedPipe(szPipe, NMPWAIT_USE_DEFAULT_WAIT))
    {
        TRACE(_T("can't find pipe!"));
        return TRUE;
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

    return TRUE;
}

BOOL CJLwgApp::InitLog()
{
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

    //��������
    setlocale(LC_ALL, "chs");


    if(!InitPipe())
    {
        return FALSE;
    }


    if(!InitLog())
    {
        return FALSE;
    }


    //��־����
    LOGER(_T("###�������"));

    //������߳�
    HANDLE hThread = ::CreateThread(NULL, 0, WgThread, this, 0, 0);
    if(hThread == NULL)
    {
        LOGER(_T("���̴߳���ʧ��"));
        ExitProcess(0);
        return FALSE;
    }

    CloseHandle(hThread);
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

int CJLwgApp::ExitInstance()
{
    TRACE(_T("ExitInstance()"));
    return CWinApp::ExitInstance();
}

