#if !defined _PROTOCOL_H_
#define _PROTOCOL_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include "..\common\Userinfo.h"


//外挂与验证服务器和控制台的通讯协议
#define		MAXLEN			16
#define		KEYLEN			128


enum FUNCODE{
		fun_login		,	//登录
		fun_regist		,	//注册
		fun_log			,	//日志
		fun_mbind		,	//修改绑定
		fun_querykey	,   //取得帐号下的所有key
		fun_bindkey		,	//绑定key
		fun_unbindkey	,	//解绑key
		fun_addkey		,	//添加key
		fun_bugrep	//报告bug..
};


#define result_fail     0
#define	result_ok		1
   		


#define	result_login_pwerror	0
#define	result_login_ok			1
#define	result_login_notuser	2
#define result_login_logined    3


#define	result_bind_fail	0
#define	result_bind_ok		1
#define	result_bind_used	2   //这个卡不属于账户
#define	result_bind_errkey	3   //卡号错误



#define	result_unbind_fail		0
#define	result_unbind_ok		1
#define	result_unbind_errtime	2
#define	result_unbind_notuser	3	//不属于账户


struct LOGIN_BUF
{
	//功能号
	char fun;
	char name[MAXLEN];
	char password[MAXLEN];
};


struct REGIST_BUF: LOGIN_BUF
{
	char ip[MAXLEN];
	PCDATA pcdata;
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
	PCDATA pcdata;
};

struct BUG_BUF: LOGIN_BUF
{
	char szBug[BUFSIZ];
};

struct QUERYKEY_RET_BUF: RET_BUF
{
	UCHAR count;
	char key[128];
	char buildtime[30];  /*生成时间*/
	char type[30];
	int remaintime;  /*剩余时间*/
};

#endif