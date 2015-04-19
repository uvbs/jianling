#if !defined _PROTOCOL_H_
#define _PROTOCOL_H_

#if _MSC_VER > 1000
    #pragma once
#endif // _MSC_VER > 1000


//常量
#define     MAXLEN          16      //用户名最大长度
#define     KEYLEN          16     //卡号最大长度
#define     DESLEN          64     //描述信息最大长度
#define     LEN_MACHINE_ID  33      //机器ID最大长度
#define     LEN_NETWORK_ID  13      //网卡长度


//长度定义
#define SOCKET_TCP_BUFFER           16384                               //网络缓冲
#define SOCKET_TCP_PACKET           (SOCKET_TCP_BUFFER-sizeof(Tcp_Head))//网络缓冲

struct PlayerPos
{
    float x;
    float y;
    float z;
};

//组队结构
struct PartyPlayer
{
    DWORD flag;     //
    DWORD taskid;
    DWORD pid;  //玩家id
    DWORD mid;  //地图id;
    struct PlayerPos pos;//玩家坐标
};


enum PartyFlag
{
    ONLY_MAP,      
    ONLY_RANGE,    
    SAME_TASKID
};


//组队回复
struct PartyRequest
{
    DWORD pid1;
    DWORD pid2;
    DWORD pid3;
    DWORD pid4;
    DWORD pid5;
    DWORD pid6;
};

//网络包头
struct Tcp_Head
{
    WORD wVersion;      //版本
    WORD wPacketSize;    //数据大小
    WORD wMainCmdID;    //主命令码
    WORD wSubCmdID;      //子命令码, 也返回结果
};


enum CMD_PARTY_MAIN
{
    M_ADDPARTY 
};

enum CMD_PARTY_SUB
{
    fun_group_find,
    fun_group_member,
    fun_group_caption,
    fun_group_fail
};

//主命令
enum CMD_MAIN
{
    M_LOGIN,    //登陆
    M_KEY,      //KEY
    M_HELP
};

enum CMD_SUB_LOGIN
{
    fun_login,   //登录
    fun_login_fail,
    fun_login_ok,

    fun_regist,   //注册
    fun_regist_fail,
    fun_regist_ok,

    fun_mbind,     //修改绑定
    fun_mbind_fail,
    fun_mbind_ok
};

enum CMD_SUB_KEY
{
    fun_querykey,       //查询取得帐号下的所有key
    fun_querykey_ok,
    fun_querykey_fail,

    fun_bindkey,        //绑定key
    fun_bindkey_ok,
    fun_bindkey_fail,

    fun_unbindkey,      //解绑key
    fun_unbindkey_ok,
    fun_unbindkey_fail,
};

enum CMD_SUB_HELP
{
    fun_bugrep,          //报告bug
    fun_bugrep_ok,
    fun_bugrep_fail
};


//登陆
struct LOGIN_BUF
{
    TCHAR name[MAXLEN];
    TCHAR pw[MAXLEN];
    TCHAR szMachineID[LEN_MACHINE_ID];
};

//注册
struct REGIST_BUF
{
    DWORD ip;
    TCHAR name[MAXLEN];
    TCHAR pw[MAXLEN];
};

//修改绑定
struct MODIFYBIND_BUF
{
    TCHAR old_bind[MAXLEN];
    TCHAR new_bind[MAXLEN];
};

//绑定key, 解绑key
struct BINDKEY_BUF
{
    TCHAR key[KEYLEN];
};


//报告bug
struct BUG_BUF
{
    TCHAR szBug[BUFSIZ];
};


//登陆失败
struct PROCESS_DESCRIBE
{
    TCHAR szDescribe[DESLEN]; //描述信息
};

//查询KEY结果
struct QUERYKEY_SUCCESS
{
    TCHAR key[KEYLEN];
    TCHAR type[DESLEN];
    DWORD buildtime;  //生成时间
    DWORD remaintime;  //剩余时间
};




#endif