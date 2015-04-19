#if !defined _PROTOCOL_H_
#define _PROTOCOL_H_

#if _MSC_VER > 1000
    #pragma once
#endif // _MSC_VER > 1000


//����
#define     MAXLEN          16      //�û�����󳤶�
#define     KEYLEN          16     //������󳤶�
#define     DESLEN          64     //������Ϣ��󳤶�
#define     LEN_MACHINE_ID  33      //����ID��󳤶�
#define     LEN_NETWORK_ID  13      //��������


//���ȶ���
#define SOCKET_TCP_BUFFER           16384                               //���绺��
#define SOCKET_TCP_PACKET           (SOCKET_TCP_BUFFER-sizeof(Tcp_Head))//���绺��

struct PlayerPos
{
    float x;
    float y;
    float z;
};

//��ӽṹ
struct PartyPlayer
{
    DWORD flag;     //
    DWORD taskid;
    DWORD pid;  //���id
    DWORD mid;  //��ͼid;
    struct PlayerPos pos;//�������
};


enum PartyFlag
{
    ONLY_MAP,      
    ONLY_RANGE,    
    SAME_TASKID
};


//��ӻظ�
struct PartyRequest
{
    DWORD pid1;
    DWORD pid2;
    DWORD pid3;
    DWORD pid4;
    DWORD pid5;
    DWORD pid6;
};

//�����ͷ
struct Tcp_Head
{
    WORD wVersion;      //�汾
    WORD wPacketSize;    //���ݴ�С
    WORD wMainCmdID;    //��������
    WORD wSubCmdID;      //��������, Ҳ���ؽ��
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

//������
enum CMD_MAIN
{
    M_LOGIN,    //��½
    M_KEY,      //KEY
    M_HELP
};

enum CMD_SUB_LOGIN
{
    fun_login,   //��¼
    fun_login_fail,
    fun_login_ok,

    fun_regist,   //ע��
    fun_regist_fail,
    fun_regist_ok,

    fun_mbind,     //�޸İ�
    fun_mbind_fail,
    fun_mbind_ok
};

enum CMD_SUB_KEY
{
    fun_querykey,       //��ѯȡ���ʺ��µ�����key
    fun_querykey_ok,
    fun_querykey_fail,

    fun_bindkey,        //��key
    fun_bindkey_ok,
    fun_bindkey_fail,

    fun_unbindkey,      //���key
    fun_unbindkey_ok,
    fun_unbindkey_fail,
};

enum CMD_SUB_HELP
{
    fun_bugrep,          //����bug
    fun_bugrep_ok,
    fun_bugrep_fail
};


//��½
struct LOGIN_BUF
{
    TCHAR name[MAXLEN];
    TCHAR pw[MAXLEN];
    TCHAR szMachineID[LEN_MACHINE_ID];
};

//ע��
struct REGIST_BUF
{
    DWORD ip;
    TCHAR name[MAXLEN];
    TCHAR pw[MAXLEN];
};

//�޸İ�
struct MODIFYBIND_BUF
{
    TCHAR old_bind[MAXLEN];
    TCHAR new_bind[MAXLEN];
};

//��key, ���key
struct BINDKEY_BUF
{
    TCHAR key[KEYLEN];
};


//����bug
struct BUG_BUF
{
    TCHAR szBug[BUFSIZ];
};


//��½ʧ��
struct PROCESS_DESCRIBE
{
    TCHAR szDescribe[DESLEN]; //������Ϣ
};

//��ѯKEY���
struct QUERYKEY_SUCCESS
{
    TCHAR key[KEYLEN];
    TCHAR type[DESLEN];
    DWORD buildtime;  //����ʱ��
    DWORD remaintime;  //ʣ��ʱ��
};




#endif