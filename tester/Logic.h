// Logic.h: interface for the Logic class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LOGIC_H__2D455467_4B6D_4486_95EF_39474EDB0E8F__INCLUDED_)
#define AFX_LOGIC_H__2D455467_4B6D_4486_95EF_39474EDB0E8F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


typedef void (*pfn_FUNC)();
class Logic
{
public:
    Logic()
    {
        m_bExit = FALSE;
    }
    ~Logic()
    {
        UnInit();
    }

    static UINT CALLBACK Run(LPVOID pParam);

    virtual void Updata(pfn_FUNC pfn)
    {
         pfn();
    }


    virtual void Init();
    virtual void UnInit();

private:
    HANDLE m_hThread;
    BOOL m_bExit;
};



#endif // !defined(AFX_LOGIC_H__2D455467_4B6D_4486_95EF_39474EDB0E8F__INCLUDED_)
