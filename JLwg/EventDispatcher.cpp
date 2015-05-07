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


//���캯��
EventDispatcher::EventDispatcher()
{

}

//��������
EventDispatcher::~EventDispatcher()
{

}

//����¼�
void EventDispatcher::AddEvent(EventArg* pNew)
{
    //����ֱ�ӽ�����ŵ������ߵ����������
    if(_listeners.size() == 0)
    {
        //���������Ӧ����
        _ASSERTE(FALSE);
        return;
    }


    //����������
    for(GroupListener::iterator it = _listeners.begin(); it != _listeners.end(); it++)
    {
        (*it)->AddEvent(pNew);
    }



}

//����¼�����
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

    //����ǰ�¼�֪ͨ��������
    for(std::vector<Listener*>::iterator it = _listeners.begin(); it != _listeners.end(); it++)
    {
        //std::list<EventArg>::iterator ita = _events.begin();

        //�����¼����͸���ͬ�ļ�����, ����һ���¼�֪ͨ�����м�����
        //����֪ͨ��ɵĽ�������������¼���ͬ����, �¼�û�д�����,
        //���Notify�ǲ��᷵�ص�.
        //      (*it)->Notify();

        //��һ�ַ�ʽ��, Notifyֻ���¼���ӵ������ߵ��¼��б���.
        //ͨ��һ���̵߳�Notify���������ߴ����¼�. ��Ȼ���������
        //��ͬ����, �����ᵼ�����ﱻ����ס.

        //��һ��ֱ�ӷŵ�����¼���, ����¼�ʱ, ֱ�ӷŵ���Ӧ�����ߵ�
        //�����б�
        TRACE(_T("�������м�����, ֪ͨ����"));

    }
}