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
    char name[MAXLEN];
    char pw[MAXLEN];
};


struct REGIST_BUF: LOGIN_BUF
{
    char ip[MAXLEN];
    char id[MAXLEN];
};


struct RET_BUF
{
    char fun;
    char result;
};

struct MODIFYBIND_BUF: LOGIN_BUF
{
    char old_bind[MAXLEN];
    char new_bind[MAXLEN];
};

struct KEY_BUF: LOGIN_BUF
{
    char key[128];
};

struct BUG_BUF: LOGIN_BUF
{
    char szBug[BUFSIZ];
};

struct QUERYKEY_RET_BUF: RET_BUF
{
    UCHAR count;
    char key[128];
    char buildtime[30];  /*����ʱ��*/
    char type[30];
    int remaintime;  /*ʣ��ʱ��*/
};

#endif