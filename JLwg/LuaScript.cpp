// LuaScript.cpp: implementation of the LuaScript class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "jlwg.h"
#include "LuaScript.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

#ifdef _DEBUG
#pragma comment(lib, "..\\第三方库\\lua52\\lib\\lua52d.lib")
#else
#pragma comment(lib, "..\\第三方库\\lua52\\lib\\lua52.lib")
#endif



LuaScript* LuaScript::_inst = NULL;

LuaScript::LuaScript()
{

    _ASSERTE(_inst == NULL);

    if(_inst == 0)
    {
        _inst = this;
    }


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

    return (m_pstate != NULL);
}