#if !defined(AFX_LAUNCHGAMETHREAD_H__8A027B09_D6EE_4356_BA08_E90381DB258C__INCLUDED_)
#define AFX_LAUNCHGAMETHREAD_H__8A027B09_D6EE_4356_BA08_E90381DB258C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LaunchGameThread.h : header file
//



/////////////////////////////////////////////////////////////////////////////
// CLaunchGameThread thread

class CJLkitView;
class CLaunchThread : public CWinThread
{
    DECLARE_DYNCREATE(CLaunchThread)
protected:
    CLaunchThread();           // protected constructor used by dynamic creation

// Attributes
public:

    CJLkitView* m_pView;
    void SetOwner(CJLkitView* pOwner)
    {
        m_pView = pOwner;
    };
    BOOL isWorking()
    {
        return m_bIsWorking;
    };
    BOOL m_bIsWorking;
// Operations
public:

// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CLaunchThread)
public:
    virtual int Run();
    virtual BOOL InitInstance();
    //}}AFX_VIRTUAL

// Implementation
protected:
    virtual ~CLaunchThread();

    // Generated message map functions
    //{{AFX_MSG(CLaunchThread)
    // NOTE - the ClassWizard will add and remove member functions here.
    //}}AFX_MSG

    DECLARE_MESSAGE_MAP()

};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LAUNCHGAMETHREAD_H__8A027B09_D6EE_4356_BA08_E90381DB258C__INCLUDED_)
