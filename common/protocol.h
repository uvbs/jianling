#if !defined _PROTOCOL_H_
#define _PROTOCOL_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000




//�������֤�������Ϳ���̨��ͨѶЭ��
#define     MAXLEN          16
#define     KEYLEN          128


enum FUNCODE
{
    fun_login       ,   //��¼
    fun_regist      ,   //ע��
    fun_log         ,   //��־
    fun_mbind       ,   //�޸İ�
    fun_querykey    ,   //ȡ���ʺ��µ�����key
    fun_bindkey     ,   //��key
    fun_unbindkey   ,   //���key
    fun_addkey      ,   //���key
    fun_bugrep  //����bug..
};


#define result_fail     0
#define result_ok       1



#define result_login_pwerror    0
#define result_login_ok         1
#define result_login_notuser    2
#define result_login_logined    3


#define result_bind_fail    0
#define result_bind_ok      1
#define result_bind_used    2   //������������˻�
#define result_bind_errkey  3   //���Ŵ���



#define result_unbind_fail      0
#define result_unbind_ok        1
#define result_unbind_errtime   2
#define result_unbind_notuser   3   //�������˻�


struct LOGIN_BUF
{
    //���ܺ�
    char fun;
    TCHAR name[MAXLEN];
    TCHAR pw[MAXLEN];
};


struct REGIST_BUF: LOGIN_BUF
{
    TCHAR ip[MAXLEN];
    TCHAR id[MAXLEN];

};


struct RET_BUF
{
    char fun;
    char result;
};

struct MODIFYBIND_BUF: LOGIN_BUF
{
    TCHAR old_bind[MAXLEN];
    TCHAR new_bind[MAXLEN];
};

struct KEY_BUF: LOGIN_BUF
{
    TCHAR key[128];
};

struct BUG_BUF: LOGIN_BUF
{
    TCHAR szBug[BUFSIZ];
};

struct QUERYKEY_RET_BUF: RET_BUF
{
    UCHAR count;
    TCHAR key[128];
    TCHAR buildtime[30];  //����ʱ��
    TCHAR type[30];
    int remaintime;  //ʣ��ʱ��
};

typedef std::vector<QUERYKEY_RET_BUF> KeyVec;

#endif