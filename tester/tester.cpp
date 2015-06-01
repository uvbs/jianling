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

    //按惯例函数头部创建一些需要的局部变量,虽然C++有个优点可以随时随地创建,但是我不喜欢那么做,为了函数的整体环境规划清爽,不然怕城管来砸,

    ZWQUERYVIRTUALMEMORY QueryVirtualMemoryFunction = NULL;
    DWORD Index = 0;
    NTSTATUS NtStatus = 0;
    MEMORY_BASIC_INFORMATION InfoMation;
    BYTE Buffer[MAX_PATH * 2 + 4] = {0};
    PUNICODE_STRING SectionName = NULL;
    DWORD Counter;
    CString ModuleAddress;
    CString ModuleName;



    QueryVirtualMemoryFunction = (ZWQUERYVIRTUALMEMORY)::GetProcAddress(GetModuleHandle("ntdll.dll"), //ntdll.dll=地府
                                 _T("ZwQueryVirtualMemory")); //ZwQueryVirtualMemory=鬼魂名


    //为了尽量做一个严谨的程序员,我们要尽量对每一步工作的有效性作下判断,这是很有好处的
    if(QueryVirtualMemoryFunction == NULL)//判断它是否有了灵魂,
    {
        AfxMessageBox(_T("别瞎TM扯淡啦！"));
        //如果没有,那啥都别想啦,一切工作都要靠它来完成你不能让一个死人来干活吧
    }
    else //呵呵,哥们如果你还没死,那就别歇着啦,帮兄弟点忙吧。。。
    {
        for(Index; Index < 0x80000000; Index += 0x1000)
        {
            NtStatus = QueryVirtualMemoryFunction(
                           (HANDLE) - 1, //因为我们是注入的,所以-1就代表当前进程的句柄,HOHO,i love dll
                           (PULONG)Index,  //工作地址哟,第一次从0x00000000开始,第二次从0x00001000
                           MemoryBasicInformation, //记得不？枚举类型,普查嘛,要有目的的查呀,他就代表我们的目的
                           &InfoMation, //第四个局部变量,你把它理解成移动硬盘好啦,查到的数据放到里面,回来交给我们
                           sizeof(InfoMation),  //你要告诉工人。你给了他一个多大的移动硬盘才行,HOHO
                           NULL); //最后一个参数我们用不到,无视它,

            if(NtStatus >= 0)
            {
                //Type就表示这些人的类型啦,如果是暴民,那我们就要严肃的处理啦,MEM_IMAGE这样的就表示暴民啦,HOHO,开个玩笑,其实它是0x1000这个大小的
                //一块内存的描述标志,比如这块内存的标志是MEM_IMAGE哪就说明他是一个我们要的模块啦

                if(InfoMation.Type == MEM_IMAGE)
                {


                    if((DWORD)InfoMation.AllocationBase == Index)
                    {

                        NtStatus = QueryVirtualMemoryFunction(
                                       (HANDLE) - 1, //不变
                                       (PULONG)Index, //模块地址啦,
                                       MemorySectionName, //看见了吗,我们换了一个命令让他做不同的工作(内存节名枚举)
                                       Buffer,
                                       sizeof(Buffer),//解释过了。
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
* 提升当前进程权限函数("SeDebugPrivilege"读、写控制权限)
* @param void
* @return TRUE-成功；FALSE-失败
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



    // 首先提示权限
    if(EnableDebugPriv())
    {

        EnumProcessForModule();

    }



    getchar();
    return 0;
}