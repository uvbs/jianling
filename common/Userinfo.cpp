#include "stdafx.h"
#include "Userinfo.h"



#pragma comment(lib, "Iphlpapi")



CCUserInfo::CCUserInfo()
{
	memset(&stPcData, 0, sizeof(stPcData));
}

CCUserInfo::~CCUserInfo()
{

}

//ȡ��pc��Ϣ
BOOL CCUserInfo::Get()
{
    
    char buf[20];
    
    
    __asm
    {
        
        //cpu ������Ϣ
        mov eax, 0;
        cpuid;
        mov dword ptr buf[0], eax;
        mov dword ptr buf[4], ebx;
        mov dword ptr buf[8], ecx;
        mov dword ptr buf[12], edx;
        
        
        //�汾��Ϣ ����, ����, ����
        mov eax, 1;
        cpuid;
        mov dword ptr buf[16], eax;
        
    }
    
    MoveMemory(stPcData.cpu, buf, sizeof(buf));
    
    system("wmic path win32_physicalmedia get SerialNumber");
    
    //mac
    IP_ADAPTER_INFO iai;
    ULONG uSize = 0;
    
    
    DWORD dwResult = GetAdaptersInfo(&iai, &uSize);
    if(dwResult == ERROR_BUFFER_OVERFLOW)
    {
        
        IP_ADAPTER_INFO *piai = (IP_ADAPTER_INFO *)new char[uSize];
        if(piai != NULL)
        {
            
            dwResult = GetAdaptersInfo(piai, &uSize);
            if(ERROR_SUCCESS == dwResult)
            {
                IP_ADAPTER_INFO *piai2 = piai;
                while(piai2 != NULL)
                {
                    /*�� mac ���ݿ������ṹ��*/
                    MoveMemory(stPcData.mac, (char *)piai2->Address, piai2->AddressLength);
                    break;
                }
            }
            
            delete []piai;
        }
        
        
        return true;
    }
}
