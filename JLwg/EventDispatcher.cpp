// EventDispatcher.cpp: implementation of the EventDispatcher class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "jlwg.h"
#include "EventDispatcher.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif



IMPLEMENT_SINGLETON(EventDispatcher)


//构造函数
EventDispatcher::EventDispatcher()
{

}

//析构函数
EventDispatcher::~EventDispatcher()
{

}

//添加事件
void EventDispatcher::AddEvent(EventArg* pNew)
{
    //这里直接将任务放到监听者的任务队列中
    if(_listeners.size() == 0)
    {
        //这种情况不应该有
        _ASSERTE(FALSE);
        return;
    }


    //遍历监听者
    for(GroupListener::iterator it = _listeners.begin(); it != _listeners.end(); it++)
    {
        (*it)->AddEvent(pNew);
    }



}

//清空事件队列
void EventDispatcher::DelAllEvent(EventArg* pEvent)
{
    _events.clear();
}

void EventDispatcher::AddListener(Listener* pNew)
{
    _listeners.push_back(pNew);
}

void EventDispatcher::DelListener(Listener* pName)
{
    TRACE(_T("no write"));
}

void EventDispatcher::Notify()
{

    if(_events.size() < 0) return;

    //将当前事件通知给监听者
    for(std::vector<Listener*>::iterator it = _listeners.begin(); it != _listeners.end(); it++)
    {
        //std::list<EventArg>::iterator ita = _events.begin();

        //根据事件类型给不同的监听者, 还是一个事件通知给所有监听者
        //这样通知造成的结果是整个处理事件是同步的, 事件没有处理完,
        //这个Notify是不会返回的.
        //      (*it)->Notify();

        //另一种方式是, Notify只讲事件添加到监听者的事件列表中.
        //通过一个线程的Notify驱动监听者处理事件. 当然这个过程又
        //是同步的, 但不会导致这里被阻塞住.

        //这一步直接放到添加事件中, 添加事件时, 直接放到对应监听者的
        //任务列表
        TRACE(_T("遍历所有监听者, 通知更新"));

    }
}