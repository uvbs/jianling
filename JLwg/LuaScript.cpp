// LuaScript.cpp: implementation of the LuaScript class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "jlwg.h"
#include "LuaScript.h"
#include "GamecallEx.h"



#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif



//方便注册自己的函数
#define REGLUAFUN(x) \
    _ASSERTE(L != NULL); \
    lua_register(L, #x, (lua_CFunction)&x);


#define REGLUADATA(x) \
    _ASSERTE(L != NULL); \
    lua_pushinteger(L, x); \
    lua_setglobal(L, #x);


static int Shunyi(lua_State* L);
static int CityConvey(lua_State* L);
static int DeliverQuests(lua_State* L);
static int FuHuo(lua_State* L);
static int FollowNpc(lua_State* L);
static int GetPresentTaskID(lua_State* L);
static int GetPresentTaskStep(lua_State* L);
static int KeyPress(lua_State* L);
static int STATUS(lua_State* L);
static int KillBoss(lua_State* L);
static int FindThenKill(lua_State* L);
static int Sleep(lua_State* L);
static int NewSpend(lua_State* L);
static int Stepto(lua_State* L);
static int AddToPary();
static int ChiYao(lua_State* L);
static int MsgBox(lua_State* L);

IMPLEMENT_SINGLETON(LuaScript)

LuaScript::LuaScript()
{
}

LuaScript::~LuaScript()
{
    if(m_pstate)
    {
        lua_close(m_pstate);
        m_pstate = NULL;
    }
}


BOOL LuaScript::Init()
{
    //创建一个lua状态
    m_pstate = luaL_newstate();
    _ASSERTE(m_pstate != NULL);
    if(m_pstate == NULL) return FALSE;


    //加载游戏库
    if(m_pstate)
    {
        GameLib(m_pstate);
        return TRUE;
    }

    return FALSE;
}


//注册lua的全局变量
void LuaScript::GameLib(lua_State* L)
{

    REGLUADATA(modeNormal);
    REGLUADATA(modeAoe);
    REGLUADATA(modeGoback);

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
    REGLUAFUN(L);
    REGLUAFUN(AddToPary);
    REGLUAFUN(FuHuo);
    REGLUAFUN(FollowNpc);
    REGLUAFUN(Shunyi);
    REGLUAFUN(CityConvey);
    REGLUAFUN(ChiYao);
    REGLUAFUN(MsgBox);
}




int utf8ToUnicode16(const char* utf8, wchar_t* unicode16, int length)
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

    return (i + 1);
}


static int AddToPary()
{
    GamecallEx::GetInstance()->AddToPary();
    return 0;
}

//utf8->utf-16的转换
static int L(lua_State* L)
{
    wchar_t a[256];
    wchar_t* unicode16 = a;

    int  length = 0;
    const char* utf8;

    utf8 = luaL_checkstring(L, 1);
    length = utf8ToUnicode16(utf8, unicode16, 256);
    if(length <= 256)
    {
        lua_pushlstring(L, (const char*) unicode16, length * 2);
    }
    else
    {
        unicode16 = (wchar_t*)malloc(length);
        utf8ToUnicode16(utf8, unicode16, length);
        lua_pushlstring(L, (const char*) unicode16, length * 2);
        free(unicode16);
    }

    return 1;
}

static int MsgBox(lua_State* L)
{
    const char* pszText = lua_tostring(L, 1);
    MessageBoxW(NULL, (wchar_t*)pszText, L"脚本", MB_OK);
    return 0;
}

//Stepto(x, y, z);
static int Stepto(lua_State* L)
{
    //从lua栈中取数据
    int y = lua_tointeger(L, 1);
    int x = lua_tointeger(L, 2);
    int z = lua_tointeger(L, 3);

    GamecallEx::GetInstance()->Stepto(y, x, z);
    return 0;
}

static int NewSpend(lua_State* L)
{
    float x = lua_tonumber(L, 1);
    GamecallEx::GetInstance()->NewSpend(x);
    return 0;
}

static int Sleep(lua_State* L)
{
    int x = lua_tonumber(L, 1);
    Sleep(x);
    return 0;
}

static int FindThenKill(lua_State* L)
{
    //获取参数个数, 因为lua不支持默认参数
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
    else
    {
        int pos = lua_tointeger(L, 1);
        DWORD range = lua_tointeger(L, 2);
        DWORD mode = lua_tointeger(L, 3);
        DWORD MyQuestStep = lua_tointeger(L, 41);
        DWORD MyQuestID = lua_tointeger(L, 5);
        DWORD canKillRange = lua_tointeger(L, 6);

        GamecallEx::GetInstance()->FindThenKill(pos, range, mode, MyQuestStep, MyQuestID, canKillRange);
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
