// TaskDispter.h: interface for the TaskDispter class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TASKDISPTER_H__5B264B95_2F2C_4A6F_8D92_9CAC7CF4EE3B__INCLUDED_)
#define AFX_TASKDISPTER_H__5B264B95_2F2C_4A6F_8D92_9CAC7CF4EE3B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000



#include "logic.h"
//任务分发
class TaskDispter
{
public:
    void AddLogic(Logic* logc);
    void AddWork(pfn_FUNC pfn)
    {
        std::list<Logic*>::iterator it;
        for(it = m_list.begin(); it != m_list.end(); it++)
        {
            Logic *pLog = *it;
            pLog->Updata(pfn);
        }
    }

private:
    std::list<Logic*> m_list;
};


#endif // !defined(AFX_TASKDISPTER_H__5B264B95_2F2C_4A6F_8D92_9CAC7CF4EE3B__INCLUDED_)
