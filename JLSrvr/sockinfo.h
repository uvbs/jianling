#ifndef _SOCKINFO_H_
#define _SOCKINFO_H_



#include <ws2tcpip.h>


enum /* 选项的类型 */
{
    VBOOL,
    VCHAR,
    VINTG,
    VLGER
};

union opt_val /* 选项值 */
{
    BOOL b_value;
    char c_value;
    int i_value;
    struct linger linger;
};

struct sock_opt /* 选项信息 */
{
    char* name;     /* 字符串名 */
    int level;      /* 选项等级 */
    int option;     /* 选项名字 */
    int type;       /* 类型     */
    int protocol;   /* 适用协议: 0 - UDP, 1 - TCP */
};

/* 选项信息全局变量 */
struct sock_opt sock_opt_g[] =
{
    /* level = SOL_SOCKET */
    {"SO_ACCEPTCONN",  SOL_SOCKET, SO_ACCEPTCONN,  VBOOL, 1},
    {"SO_BROADCAST",   SOL_SOCKET, SO_BROADCAST,   VBOOL, 0},
    {"SO_DEBUG",       SOL_SOCKET, SO_DEBUG,       VBOOL, 0},
    {"SO_DONTLINGER",  SOL_SOCKET, SO_DONTLINGER,  VBOOL, 1},
    {"SO_DONTROUTE",   SOL_SOCKET, SO_DONTROUTE,   VCHAR, 0},
    {"SO_ERROR",       SOL_SOCKET, SO_ERROR,       VINTG, 0},
    {"SO_KEEPALIVE",   SOL_SOCKET, SO_KEEPALIVE,   VCHAR, 1},
    {"SO_LINGER",      SOL_SOCKET, SO_LINGER,      VLGER, 1},
    {"SO_MAX_MSG_SIZE", SOL_SOCKET, SO_MAX_MSG_SIZE, VINTG, 0},
    {"SO_OOBINLINE",   SOL_SOCKET, SO_OOBINLINE,   VBOOL, 1},
    {"SO_RCVBUF",      SOL_SOCKET, SO_RCVBUF,      VINTG, 1},
    {"SO_RCVTIMEO",    SOL_SOCKET, SO_RCVTIMEO,    VINTG, 1},
    {"SO_REUSEADDR",   SOL_SOCKET, SO_REUSEADDR,   VBOOL, 1},
    {"SO_SNDBUF",      SOL_SOCKET, SO_SNDBUF,      VINTG, 1},
    {"SO_SNDTIMEO",    SOL_SOCKET, SO_SNDTIMEO,    VINTG, 1},
    {"SO_TYPE",        SOL_SOCKET, SO_TYPE,        VINTG, 1},

    /* level = IPPROTO_IP */
    {"IP_DONTFRAGMENT", IPPROTO_IP, IP_DONTFRAGMENT, VBOOL, 0},
    {"IP_HDRINCL",     IPPROTO_IP, IP_HDRINCL,     VBOOL, 0},
    {"IP_TOS",         IPPROTO_IP, IP_TOS,         VINTG, 0},
    {"IP_TTL",         IPPROTO_IP, IP_TTL,         VINTG, 0},

    /* level = IPPROTO_UDP */
    {"UDP_NOCHECKSUM", IPPROTO_UDP, UDP_NOCHECKSUM, VCHAR, 0},

    /* level = IPPROTO_TCP */
    {"TCP_NODELAY",    IPPROTO_TCP, TCP_NODELAY,    VCHAR, 1},
    {"TCP_EXPEDITED_1122", IPPROTO_TCP, TCP_EXPEDITED_1122, VCHAR, 1}
};

#endif