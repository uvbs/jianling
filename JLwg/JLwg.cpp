#include "stdafx.h"
#include "JLwg.h"
#include "GamecallEx.h"
#include "GameConfig.h"
#include "JLDlg.h"
#include "GameSpend.h"



//����ע���Լ��ĺ���
#define REGLUAFUN(x) \
    lua_register(L, #x, (lua_CFunction)x);


#define REGLUADATA(x) \
    lua_pushinteger(L, x); \
    lua_setglobal(L, #x);



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
    if(m_pstate)
    {
        lua_close(m_pstate);
        m_pstate = NULL;
    }

}


//����Ϸ����Ϣ����
LRESULT CALLBACK CJLwgApp::GameWndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{

    if(!theApp.m_pWgDlg || !theApp.m_pWgDlg->GetSafeHwnd())
    {
        return CallWindowProc(theApp.wpOrigGameProc, hwnd, uMsg, wParam, lParam);
    }

    //�������
    switch(uMsg)
    {

    //��Ϊ���򱣻�������, ������Ϸ�����˳�ʱ, ���ģ�鲢���ᱻ֪ͨ��
    case WM_CLOSE:
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


DWORD CALLBACK CJLwgApp::WorkThread(LPVOID pParam)
{

    try
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
        if(!theApp.InitLua())
        {
            LOGER(_T("�ű���ʼ��ʧ��"));
            ExitProcess(0);
            return FALSE;
        }

        //��ʼ��call�� �����Ϸ���ܵĳ�ʼ�����Էŵ��ű��߳̿�ʼִ��
        //��������������ҽ����߳�, ��������߳�
        //ʹ��ҽ����ܾ������, ���Ƿ��ڽű��̻߳ᵼ��
        if(!GamecallEx::GetInstance()->Init())
        {
            LOGER(_T("��ҹ��ܳ�ʼ��ʧ��"));
            ExitProcess(0);
            return 0;
        }

        LOGER(_T("�������"));



        //����Ϸ���ڴ���
        theApp.wpOrigGameProc = (WNDPROC)::SetWindowLong(theApp.m_hGameWnd, GWL_WNDPROC, (LONG)theApp.GameWndProc);
        ::SetWindowText(theApp.m_hGameWnd, theApp.m_stData.szAccount);

        //static CFrameWnd a;   //����һ����ܴ��ڶ���
        //a.Create(NULL, _T("HideTaskBar")); //���ɴ���,����ws_visible

        //���Ի���
        theApp.m_pWgDlg = new CJLDlg();
        theApp.m_pWgDlg->DoModal();

    }
    catch(...)
    {
        AfxMessageBox(_T("�쳣! ����ע��"));
    }


    GamecallEx::GetInstance()->UnLoad();


    if(theApp.m_hPipe != INVALID_HANDLE_VALUE)
    {
        CloseHandle(theApp.m_hPipe);
    }


    if(theApp.wpOrigGameProc)
    {
        ::SetWindowLong(theApp.m_hGameWnd, GWL_WNDPROC, (LONG)theApp.wpOrigGameProc);
    }

    LOGER(_T("����ж��"));
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



    if(!m_GameLog.open(szLogPath))
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
    HANDLE hThread = ::CreateThread(NULL, 0, WorkThread, this, 0, 0);
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
    if(WriteFile(m_hPipe, &status, sizeof(PIPESTATUS), &dwWriten, NULL) == 0)
    {
        //�޿���̨, dbgview
        TRACE(szText);
    }
}

int CJLwgApp::ExitInstance()
{
    return CWinApp::ExitInstance();
}



int utf8ToUnicode16(const   char* utf8, wchar_t* unicode16,  int  length)
{
    char  c;
    int  i = 0;
    --length;
    while(c = *utf8)
    {
        if(c & 0x80)
        {
            if(c & 0x20)
            {
                if(i < length)
                {
                    unicode16[i] = ((utf8[0] & 0xf) << 12) | ((utf8[1] & 0x3f) << 6) | ((utf8[2] & 0x3f));
                }
                ++i;
                utf8 += 3;
            }
            else
            {
                if(i < length)
                {
                    unicode16[i] = ((utf8[0] & 0x1f) << 6) | ((utf8[1] & 0x3f));
                }
                ++i;
                utf8 += 2;
            }
        }
        else
        {
            if(i < length)
            {
                unicode16[i] = c;
            }
            ++i;
            ++utf8;
        }
    }
    if(i <= length)
    {
        unicode16[i] = 0;
    }
    return  i + 1;
}


static int AddToPary()
{
    GamecallEx::GetInstance()->AddToPary();
    return 0;
}

//utf8->utf-16��ת��
static int w(lua_State* L)
{
    wchar_t a[256] = {0};
    wchar_t* unicode16 = a;
    int length = 0;
    const char* utf8;

    utf8 = luaL_checkstring(L, 1);
    length = utf8ToUnicode16(utf8, unicode16, 256);
    if(length <= 256)
    {
        lua_pushlstring(L, (const   char*) unicode16, length * 2);
    }
    else
    {
        unicode16 = (wchar_t*)malloc(length);
        utf8ToUnicode16(utf8, unicode16, length);
        lua_pushlstring(L, (const   char*) unicode16, length * 2);
        free(unicode16);
    }

    return 1;
}

static int MsgBox(lua_State* L)
{
    const char* pszText = lua_tostring(L, 1);
    MessageBoxW(NULL, (wchar_t*)pszText, L"�ű�", MB_OK);
    return 0;
}

//Stepto(x, y, z);
static int Stepto(lua_State* L)
{
    //��luaջ��ȡ����
    float y = (float)lua_tonumber(L, 1);
    float x = (float)lua_tonumber(L, 2);
    float z = (float)lua_tonumber(L, 3);

    GamecallEx::GetInstance()->Stepto(y, x, z);
    return 0;
}

static int NewSpend(lua_State* L)
{
    float x = (float)lua_tonumber(L, 1);
    GamecallEx::GetInstance()->NewSpend(x);
    return 0;
}

static int Sleep(lua_State* L)
{
    int x = lua_tointeger(L, 1);
    Sleep(x);
    return 0;
}

static int FindThenKill(lua_State* L)
{
    //��ȡ��������, ��Ϊlua��֧��Ĭ�ϲ���
    int nums = lua_gettop(L);
    if(nums == 3)
    {
        int pos = lua_tointeger(L, 1);
        DWORD range = lua_tointeger(L, 2);
        DWORD mode = lua_tointeger(L, 3);
        GamecallEx::GetInstance()->FindThenKill(pos, range, modeNormal);
    }
    else if(nums == 0)
    {
        GamecallEx::GetInstance()->FindThenKill(0, 1000, modeNormal);
    }
    else if(nums == 6)
    {
        int pos = lua_tointeger(L, 1);
        DWORD range = lua_tointeger(L, 2);
        DWORD mode = lua_tointeger(L, 3);
        DWORD MyQuestStep = lua_tointeger(L, 4);
        DWORD MyQuestID = lua_tointeger(L, 5);
        DWORD canKillRange = lua_tointeger(L, 6);

        GamecallEx::GetInstance()->FindThenKill(pos, range, mode, MyQuestStep, MyQuestID, canKillRange);
    }
    else if(nums == 5)
    {
        int pos = lua_tointeger(L, 1);
        DWORD range = lua_tointeger(L, 2);
        DWORD mode = lua_tointeger(L, 3);
        DWORD MyQuestStep = lua_tointeger(L, 4);
        DWORD MyQuestID = lua_tointeger(L, 5);

        GamecallEx::GetInstance()->FindThenKill(pos, range, mode, MyQuestStep, MyQuestID);
    }
    else if(nums == 4)
    {
        int pos = lua_tointeger(L, 1);
        DWORD range = lua_tointeger(L, 2);
        DWORD mode = lua_tointeger(L, 3);
        DWORD MyQuestStep = lua_tointeger(L, 4);

        GamecallEx::GetInstance()->FindThenKill(pos, range, mode, MyQuestStep);
    }
    else
    {

        //lua_error()
        _ASSERTE(FALSE);
    }

    return 0;
}


static int KillBoss(lua_State* L)
{
    const char* pszText = lua_tostring(L, 1);
    GamecallEx::GetInstance()->KillBoss((wchar_t*)pszText);
    return 0;
}

static int STATUS(lua_State* L)
{
    const char* pszText = lua_tostring(L, 1);
    theApp.SendStatus((wchar_t*)pszText);
    return 0;
}


static int KeyPress(lua_State* L)
{
    int vk = lua_tointeger(L, 1);
    GamecallEx::GetInstance()->KeyPress(vk);
    return 0;
}

static int GetPresentTaskStep(lua_State* L)
{
    int step = GamecallEx::GetInstance()->GetPresentTaskStep();
    lua_pushinteger(L, step);
    return 1;
}

static int GetPresentTaskID(lua_State* L)
{
    int id = GamecallEx::GetInstance()->GetPresentTaskID();
    lua_pushinteger(L, id);
    return 1;
}


static int FollowNpc(lua_State* L)
{
    const char* pszText = lua_tostring(L, 1);
    int range = lua_tointeger(L, 2);
    GamecallEx::GetInstance()->FollowNpc((wchar_t*)pszText, range);
    return 0;
}


static int FuHuo(lua_State* L)
{
    GamecallEx::GetInstance()->FuHuo();
    return 0;
}

static int WearEquipment(lua_State* L)
{
    const char* name = lua_tostring(L, 1);
    int pos = lua_tointeger(L, 2);
    GamecallEx::GetInstance()->WearEquipment((wchar_t*)name, pos);

    return 0;
}
static int PickupTask(lua_State* L)
{
    int nums = lua_gettop(L);
    switch(nums)
    {
    case 0:

        GamecallEx::GetInstance()->PickupTask();
        break;


    case 1:
        {

            int range = lua_tointeger(L, 1);
            GamecallEx::GetInstance()->PickupTask();
            break;
        }

    case 3:
        {
            int c1 = lua_tointeger(L, 1);
            int c2 = lua_tointeger(L, 1);
            int c3 = lua_tointeger(L, 1);
            GamecallEx::GetInstance()->PickupTask(c1, c2, c3);
            break;
        }

    default:
        _ASSERTE(FALSE); //��Ӧ���е���
        break;
    }

    return 0;
}

static int DeliverQuests(lua_State* L)
{
    int nums = lua_gettop(L);
    switch(nums)
    {
    case 3:
        {
            int a1 = lua_tointeger(L, 1);
            int a2 = lua_tointeger(L, 2);
            const char* a3 = lua_tostring(L, 3);

            GamecallEx::GetInstance()->DeliverQuests(a1, a2, (wchar_t*)a3);
            break;
        }

    case 6:
        {

            int a1 = lua_tointeger(L, 1);
            int a2 = lua_tointeger(L, 2);
            const char* a3 = lua_tostring(L, 3);
            int a4 = lua_tointeger(L, 4);
            int a5 = lua_tointeger(L, 5);
            int a6 = lua_tointeger(L, 6);
            GamecallEx::GetInstance()->DeliverQuests(a1, a2, (wchar_t*)a3, a4, a5, a6);
            break;
        }

    case 4:
        {
            int a1 = lua_tointeger(L, 1);
            int a2 = lua_tointeger(L, 2);
            const char* a3 = lua_tostring(L, 3);
            int a4 = lua_tointeger(L, 4);
            GamecallEx::GetInstance()->DeliverQuests(a1, a2, (wchar_t*)a3, a4);
            break;
        }


    default:
        {
            _ASSERTE(FALSE); //��Ӧ��
            break;
        }
    }

    return 0;
}

static int CityConvey(lua_State* L)
{
    int id = lua_tointeger(L, 1);
    GamecallEx::GetInstance()->CityConvey(id);
    return 0;
}

static int Shunyi(lua_State* L)
{
    const char* pszText = lua_tostring(L, 1);
    GamecallEx::GetInstance()->Shunyi((wchar_t*)pszText);
    return 0;
}

static int ChiYao(lua_State* L)
{
    const char* pszText = lua_tostring(L, 1);
    GamecallEx::GetInstance()->ChiYao((wchar_t*)pszText);
    return 0;
}

static int WaitPlans(lua_State* L)
{
    GamecallEx::GetInstance()->WaitPlans();
    return 0;
}

static int NewBag(lua_State* L)
{
    GamecallEx::GetInstance()->NewBag();
    return 0;
}

static int randXianlu(lua_State* L)
{
    int id = lua_tointeger(L, 1);
    GamecallEx::GetInstance()->randXianlu(id);
    return 0;
}

static int NPCJieRenWu(lua_State* L)
{
    int nums = lua_gettop(L);
    if(nums == 4)
    {
        const char* name = lua_tostring(L, 1);
        int canshu2 = lua_tointeger(L, 2);
        int canshu3 = lua_tointeger(L, 3);
        int canshu4 = lua_tointeger(L, 4);
        GamecallEx::GetInstance()->NPCJieRenWu((wchar_t*)name, canshu2, canshu3, canshu4);
    }
    else if(nums == 5)
    {
        int c1 = lua_tointeger(L, 1);
        int c2 = lua_tointeger(L, 2);
        int c3 = lua_tointeger(L, 3);
        int c4 = lua_tointeger(L, 4);
        int c5 = lua_tointeger(L, 5);
        GamecallEx::GetInstance()->NPCJieRenWu(c1, c2, c3, c4, c5);
    }
    else
    {
        _ASSERTE(FALSE);
    }

    return 0;
}

static int Pickup(lua_State* L)
{
    int iRange = lua_tointeger(L, 1);
    GamecallEx::GetInstance()->Pickup(iRange);
    return 0;
}


static int HeChengWuQiByHun(lua_State* L)
{
    int pos = lua_tointeger(L, 1);
    GamecallEx::GetInstance()->HeChengWuQiByHun((EQUITMENT_POS)pos);
    return 0;
}

bool CJLwgApp::InitLua()
{
    //����һ��lua״̬
    m_pstate = luaL_newstate();
    _ASSERTE(m_pstate != NULL);
    if(m_pstate == NULL) return false;


    //������Ϸ��
    if(m_pstate)
    {
        RegGameLib(m_pstate);
        return true;
    }

    return false;
}


//ע��lua��ȫ�ֱ���
void CJLwgApp::RegGameLib(lua_State* L)
{

    REGLUADATA(modeNormal);
    REGLUADATA(modeAoe);
    REGLUADATA(modeGoback);
    REGLUADATA(modePickupOnce);
    REGLUADATA(modeTask);
    REGLUADATA(modePickup);
    REGLUADATA(WUQI);
    REGLUADATA(YIFU);
    REGLUADATA(YAODAI);
    REGLUADATA(XIANGLIAN);
    REGLUADATA(JIEZHI);
    REGLUADATA(ERHUAN);

    REGLUAFUN(Stepto);
    REGLUAFUN(KillBoss);
    REGLUAFUN(STATUS);
    REGLUAFUN(KeyPress);
    REGLUAFUN(NewSpend);
    REGLUAFUN(GetPresentTaskStep);
    REGLUAFUN(GetPresentTaskID);
    REGLUAFUN(FindThenKill);
    REGLUAFUN(Sleep);
    REGLUAFUN(DeliverQuests);
    REGLUAFUN(w);
    REGLUAFUN(AddToPary);
    REGLUAFUN(FuHuo);
    REGLUAFUN(FollowNpc);
    REGLUAFUN(Shunyi);
    REGLUAFUN(CityConvey);
    REGLUAFUN(ChiYao);
    REGLUAFUN(MsgBox);
    REGLUAFUN(PickupTask);
    REGLUAFUN(Pickup);
    REGLUAFUN(WearEquipment);
    REGLUAFUN(WaitPlans);
    REGLUAFUN(randXianlu);
    REGLUAFUN(NewBag);
    REGLUAFUN(NPCJieRenWu);
    REGLUAFUN(HeChengWuQiByHun);
}




