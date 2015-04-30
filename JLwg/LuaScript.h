// LuaScript.h: interface for the LuaScript class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LUASCRIPT_H__1AD247B2_ADAD_4E4D_ACE8_0AB161DCB430__INCLUDED_)
#define AFX_LUASCRIPT_H__1AD247B2_ADAD_4E4D_ACE8_0AB161DCB430__INCLUDED_


extern "C"
{
    #include "..\第三方库\lua52\lua.h"
    #include "..\第三方库\lua52\lauxlib.h"
}




class LuaScript
{
public:
    LuaScript();
    virtual ~LuaScript();

    static LuaScript* GetInstance()
    {
        return _inst;
    }


    BOOL Init();

private:
    static LuaScript* _inst;
    lua_State* m_pstate;
};

#endif // !defined(AFX_LUASCRIPT_H__1AD247B2_ADAD_4E4D_ACE8_0AB161DCB430__INCLUDED_)
