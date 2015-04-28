// EventDispatcher.h: interface for the EventDispatcher class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_EVENTDISPATCHER_H__72FE6A91_6E0C_4B3E_94F0_121C2BF0FB98__INCLUDED_)
#define AFX_EVENTDISPATCHER_H__72FE6A91_6E0C_4B3E_94F0_121C2BF0FB98__INCLUDED_



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


    //添加一个事件
    void AddEvent(EventArg* pNew);

    //删除一个事件
    void DelAllEvent(EventArg* pEvent);




    //添加解除监听者
    void AddListener(Listener* pNew);
    void DelListener(Listener* pName);


    void Notify();

private:
    std::list<EventArg> _events;

    typedef std::vector<Listener*> GroupListener;
    GroupListener _listeners;
};

#endif // !defined(AFX_EVENTDISPATCHER_H__72FE6A91_6E0C_4B3E_94F0_121C2BF0FB98__INCLUDED_)
