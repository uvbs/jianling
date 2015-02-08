#if !defined _LOCK_H_
#define _LOCK_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//日志
class CLock
{
public:
    CLock()
    {
        __try
        {
            InitializeCriticalSection(&m_critical);
        }
        __except(EXCEPTION_EXECUTE_HANDLER)
        {
        }
    }
    ~CLock()
    {
        DeleteCriticalSection(&m_critical);
    }

    inline void lock()
    {
        EnterCriticalSection(&m_critical);
    }
    inline void unlock()
    {
        LeaveCriticalSection(&m_critical);
    }

private:
    CRITICAL_SECTION    m_critical; // 系统临界区
};

#endif