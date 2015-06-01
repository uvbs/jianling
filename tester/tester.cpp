// Tester.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Test.h"

#include <windows.h>
#include <vector>
#include <fstream>
#include <map>

#include <winternl.h>



typedef enum _MEMORY_INFORMATION_CLASS
{
    MemoryBasicInformation,
    MemoryWorkingSetList,
    MemorySectionName
} MEMORY_INFORMATION_CLASS;

typedef
NTSTATUS
(WINAPI* ZWQUERYVIRTUALMEMORY)
(
    IN HANDLE ProcessHandle,
    IN PVOID BaseAddress,
    IN MEMORY_INFORMATION_CLASS MemoryInformationClass,
    OUT PVOID MemoryInformation,
    IN ULONG MemoryInformationLength,
    OUT PULONG ReturnLength OPTIONAL
);



CWinApp theApp;


typedef struct _PEB_LDR_DATA
{
    ULONG                   Length;
    BOOLEAN                 Initialized;
    PVOID                   SsHandle;
    LIST_ENTRY              InLoadOrderModuleList;
    LIST_ENTRY              InMemoryOrderModuleList;
    LIST_ENTRY              InInitializationOrderModuleList;

} PEB_LDR_DATA, *PPEB_LDR_DATA;


typedef struct _LDR_DATA_TABLE_ENTRY
{

    LIST_ENTRY InLoadOrderLinks;
    LIST_ENTRY InMemoryOrderLinks;
    LIST_ENTRY InInitializationOrderLinks;
    PVOID DllBase;
    PVOID EntryPoint;
    ULONG SizeOfImage;
    UNICODE_STRING FullDllName;
    UNICODE_STRING BaseDllName;
    ULONG Flags;
    USHORT LoadCount;
    USHORT TlsIndex;
    union
    {
        LIST_ENTRY HashLinks;
        struct
        {
            PVOID SectionPointer;
            ULONG CheckSum;
        };
    };
    ULONG TimeDateStamp;

} LDR_DATA_TABLE_ENTRY, *PLDR_DATA_TABLE_ENTRY;


typedef struct MEMORY_SECTION_NAME
{
    UNICODE_STRING SectionFileName;
    WCHAR       NameBuffer[ANYSIZE_ARRAY];
}* PMEMORY_SECTION_NAME;


VOID EnumProcessForModule()
{

    //����������ͷ������һЩ��Ҫ�ľֲ�����,��ȻC++�и��ŵ������ʱ��ش���,�����Ҳ�ϲ����ô��,Ϊ�˺��������廷���滮��ˬ,��Ȼ�³ǹ�����,

    ZWQUERYVIRTUALMEMORY QueryVirtualMemoryFunction = NULL;
    DWORD Index = 0;
    NTSTATUS NtStatus = 0;
    MEMORY_BASIC_INFORMATION InfoMation;
    BYTE Buffer[MAX_PATH * 2 + 4] = {0};
    PUNICODE_STRING SectionName = NULL;
    DWORD Counter;
    CString ModuleAddress;
    CString ModuleName;



    QueryVirtualMemoryFunction = (ZWQUERYVIRTUALMEMORY)::GetProcAddress(GetModuleHandle("ntdll.dll"), //ntdll.dll=�ظ�
                                 _T("ZwQueryVirtualMemory")); //ZwQueryVirtualMemory=�����


    //Ϊ�˾�����һ���Ͻ��ĳ���Ա,����Ҫ������ÿһ����������Ч�������ж�,���Ǻ��кô���
    if(QueryVirtualMemoryFunction == NULL)//�ж����Ƿ��������,
    {
        AfxMessageBox(_T("��ϹTM��������"));
        //���û��,��ɶ��������,һ�й�����Ҫ����������㲻����һ���������ɻ��
    }
    else //�Ǻ�,��������㻹û��,�Ǿͱ�Ъ����,���ֵܵ�æ�ɡ�����
    {
        for(Index; Index < 0x80000000; Index += 0x1000)
        {
            NtStatus = QueryVirtualMemoryFunction(
                           (HANDLE) - 1, //��Ϊ������ע���,����-1�ʹ���ǰ���̵ľ��,HOHO,i love dll
                           (PULONG)Index,  //������ַӴ,��һ�δ�0x00000000��ʼ,�ڶ��δ�0x00001000
                           MemoryBasicInformation, //�ǵò���ö������,�ղ���,Ҫ��Ŀ�ĵĲ�ѽ,���ʹ������ǵ�Ŀ��
                           &InfoMation, //���ĸ��ֲ�����,����������ƶ�Ӳ�̺���,�鵽�����ݷŵ�����,������������
                           sizeof(InfoMation),  //��Ҫ���߹��ˡ��������һ�������ƶ�Ӳ�̲���,HOHO
                           NULL); //���һ�����������ò���,������,

            if(NtStatus >= 0)
            {
                //Type�ͱ�ʾ��Щ�˵�������,����Ǳ���,�����Ǿ�Ҫ����Ĵ�����,MEM_IMAGE�����ľͱ�ʾ������,HOHO,������Ц,��ʵ����0x1000�����С��
                //һ���ڴ��������־,��������ڴ�ı�־��MEM_IMAGE�ľ�˵������һ������Ҫ��ģ����

                if(InfoMation.Type == MEM_IMAGE)
                {


                    if((DWORD)InfoMation.AllocationBase == Index)
                    {

                        NtStatus = QueryVirtualMemoryFunction(
                                       (HANDLE) - 1, //����
                                       (PULONG)Index, //ģ���ַ��,
                                       MemorySectionName, //��������,���ǻ���һ��������������ͬ�Ĺ���(�ڴ����ö��)
                                       Buffer,
                                       sizeof(Buffer),//���͹��ˡ�
                                       NULL);

                        if(NtStatus >= 0) 
                        {

                            SectionName = (PUNICODE_STRING)Buffer;
                            ModuleName = SectionName->Buffer;
                            ModuleAddress.Format(_T("%x"), Index);
                            AfxMessageBox(ModuleAddress);
                        }
                    }
                }
            }
        }
    }
}




VOID GetPebModule()
{
    PBYTE pPeb;
    PPEB_LDR_DATA pLdr;
    PLDR_DATA_TABLE_ENTRY pLdrData;

    __asm
    {
        MOV EAX, FS:[0x18]
        MOV EAX, [EAX + 0x30]

        MOV pPeb, EAX
    }

    pLdr = (PPEB_LDR_DATA)(*(DWORD*)(pPeb + 0x0C));
    pLdrData = (PLDR_DATA_TABLE_ENTRY)pLdr->InLoadOrderModuleList.Flink;

    for(; (pLdr->InLoadOrderModuleList.Flink) != (pLdrData->InLoadOrderLinks.Flink);)
    {
        wprintf(L"%s\r\n", (pLdrData->FullDllName.Buffer));
        pLdrData = (PLDR_DATA_TABLE_ENTRY)(pLdrData->InLoadOrderLinks.Flink);
    }

    return ;
}


/**
* ������ǰ����Ȩ�޺���("SeDebugPrivilege"����д����Ȩ��)
* @param void
* @return TRUE-�ɹ���FALSE-ʧ��
*/
BOOL EnableDebugPriv()
{
    HANDLE hToken;
    TOKEN_PRIVILEGES tkp;
    LUID Luid;

    if(!OpenProcessToken(GetCurrentProcess(),
                         TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken))
    {
        return FALSE;
    }

    if(!LookupPrivilegeValue(NULL, SE_DEBUG_NAME, &Luid))
    {
        CloseHandle(hToken);
        return FALSE;
    }

    tkp.PrivilegeCount = 1;
    tkp.Privileges[0].Luid = Luid;
    tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

    if(!AdjustTokenPrivileges(hToken, FALSE, &tkp, sizeof(tkp), NULL, NULL))
    {
        CloseHandle(hToken);
        return FALSE;
    }

    return TRUE;
}




int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{

    // initialize MFC and print and error on failure
    if(!AfxWinInit(::GetModuleHandle(NULL), NULL, ::GetCommandLine(), 0))
    {
        // TODO: change error code to suit your needs
        std::cerr << _T("Fatal Error: MFC initialization failed") << std::endl;
        return 1;
    }



    // ������ʾȨ��
    if(EnableDebugPriv())
    {

        EnumProcessForModule();

    }



    getchar();
    return 0;
}