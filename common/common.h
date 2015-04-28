#ifndef _COMMON_H_
#define _COMMON_H_

//�������˿�
#define     PORT_SRV    5678


//�����ڴ�����
#define SHAREOBJNAME _T("Bns_Mem_Share")

//����̨������
#define JLKITCLASSNAME _T("JLKitWnd")



#define SafeDelete(x) {try{if(x != NULL){delete x;}}catch(...){_ASSERTE(FALSE);}x = NULL;}

//������, ��Ƕ�������Զ�delete����
#define DECLARE_SINGLETON(x)\
private:\
static x* _inst;\
class Nested\
{\
public: \
    Nested() {}\
    ~Nested() \
    { \
        if(x::_inst != NULL)\
            delete x::_inst;\
    }\
}; \
        friend class Nested; \
        static Nested m_nest; \
    public:\
static x* GetInstance()\
{   \
    if(_inst == 0)\
        _inst = new x; \
    return _inst; \
}



#define IMPLEMENT_SINGLETON(x)\
x* x::_inst = 0;\
x::Nested x::m_nest;



typedef struct _PIPEDATA
{
    DWORD dwPid;
    DWORD dwItem;
    TCHAR szAccount[MAX_PATH];
    TCHAR szConfig[MAX_PATH];
    TCHAR szScript[MAX_PATH];
}PIPEDATA, *PPIPEDATA;


typedef struct _PIPESTATUS
{
    DWORD dwPid;
    DWORD dwItem;
    TCHAR szStatus[MAX_PATH];
}PIPESTATUS, *PPIPESTATUS;


#endif
