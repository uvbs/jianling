#if !defined _USERINFO_H_
#define _USERINFO_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <IPTypes.h>

typedef struct _PCDATA
{
	BYTE cpu[20];
	BYTE mac[MAX_ADAPTER_ADDRESS_LENGTH];
	BYTE hid[12];
	BYTE mbid[12];
	BYTE bios[20];
}PCDATA, *PPCDATA;



class CCUserInfo
{
public:
	CCUserInfo();
	~CCUserInfo();

    BOOL Get();

	CString m_strUser;
	CString m_strPw;
	CString m_strIp;
	PCDATA stPcData;
};


#endif