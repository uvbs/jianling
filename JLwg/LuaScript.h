// LuaScript.h: interface for the LuaScript class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LUASCRIPT_H__1AD247B2_ADAD_4E4D_ACE8_0AB161DCB430__INCLUDED_)
#define AFX_LUASCRIPT_H__1AD247B2_ADAD_4E4D_ACE8_0AB161DCB430__INCLUDED_



class LuaScript
{
public:
    LuaScript();
    virtual ~LuaScript();

    DECLARE_SINGLETON(LuaScript)

public:
    BOOL Init();

private:

};
#endif // !defined(AFX_LUASCRIPT_H__1AD247B2_ADAD_4E4D_ACE8_0AB161DCB430__INCLUDED_)
