// EventDispatcher.h: interface for the EventDispatcher class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_EVENTDISPATCHER_H__72FE6A91_6E0C_4B3E_94F0_121C2BF0FB98__INCLUDED_)
#define AFX_EVENTDISPATCHER_H__72FE6A91_6E0C_4B3E_94F0_121C2BF0FB98__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


struct EventArg
{
    EventArg()
    {
        priority = 0;
    }


    int priority;

};


class Listener
{
public:
    void Notify()
    {

    }

    void AddEvent(EventArg* pEvent)
    {

        //还有最大优先级的事件存在
        if(_task.size() > 0)
        {
            TaskGroup::iterator it = _task.begin();
            if((*it).priority == 2)
            {
                return;
            }
        }

        //根据优先级置于队列前还是队列后
        if(pEvent->priority == 0)
        {
            _task.push_back(*pEvent);
        }
        else if(pEvent->priority == 1)
        {
            _task.push_front(*pEvent);
        }
        else if(pEvent->priority == 2)
        {
            _task.clear();
            _task.push_back(*pEvent);
        }


    }

private:
    typedef std::list<EventArg> TaskGroup;
    TaskGroup _task;
};



class EventDispatcher
{
protected:
    EventDispatcher();
    virtual ~EventDispatcher();

    DECLARE_SINGLETON(EventDispatcher)

public:

    void AddEvent(EventArg* pNew);
    void DelAllEvent(EventArg* pEvent);

    void AddListener(Listener* pNew);
    void DelListener(Listener* pName);


    void Notify();

private:
    std::list<EventArg> _events;

    typedef std::vector<Listener*> GroupListener;
    GroupListener _listeners;
};

#endif // !defined(AFX_EVENTDISPATCHER_H__72FE6A91_6E0C_4B3E_94F0_121C2BF0FB98__INCLUDED_)
