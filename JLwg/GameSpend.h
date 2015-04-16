// GameSpend.h: interface for the GameSpend class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GAMESPEND_H__C21DB428_5D98_4535_817B_E6E7A67D8713__INCLUDED_)
#define AFX_GAMESPEND_H__C21DB428_5D98_4535_817B_E6E7A67D8713__INCLUDED_

#if _MSC_VER > 1000
    #pragma once
#endif // _MSC_VER > 1000



//初始化加速
class GameSpend
{
protected:
    GameSpend();
    virtual ~GameSpend();
    DECLARE_SINGLETON(GameSpend)


    BOOL Init();

    typedef int (*_InitializeSpeedhack)(float);
    _InitializeSpeedhack m_pfnInitSpeed;

private:
    HMODULE m_hack; //加速模块句柄
    CHook ce_hookGetTickCount;
    CHook ce_hookQueryPerformanceCounter;
    CHook ce_hooktimeGetTime;
};

#endif // !defined(AFX_GAMESPEND_H__C21DB428_5D98_4535_817B_E6E7A67D8713__INCLUDED_)
