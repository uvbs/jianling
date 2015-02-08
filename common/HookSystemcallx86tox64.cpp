#include "stdafx.h"
#include "Common.h"
#include "HookSystemcallx86tox64.h"
///////////////////////by:exediy  QQ:393234111
DWORD dwX86to64Index;

//HOOK后跳入的函数地址
DWORD dwHookX86SwitchTo64[0x4048];

//返回的函数地址
DWORD* dwOrigX86SwitchTo64[0x4048];

DWORD dwX86SwitchTo64BitMode;

//原始进入内核函数地址
DWORD* dwX86SwitchTo64BitModeEx;

HookSystemcallx86tox64::HookSystemcallx86tox64(void)
    : dwX86SwitchTo64BitMode(0)
{
}

HookSystemcallx86tox64::~HookSystemcallx86tox64(void)
{
}

//75072320  EA 1E 27 07 75 33 00  jmp         0033:7507271E


__declspec(naked) void  X86SwitchTo64BitMode()
{
    __asm
    {
        pushad
        pushfd

        cmp         dword ptr [eax*4+dwHookX86SwitchTo64], 0

        jz          Label
        popfd
        popad
        add         esp, 4
        jmp         dword ptr [dwHookX86SwitchTo64+eax*4]

        Label:
        popfd
        popad
        jmp         dword ptr [dwX86SwitchTo64BitModeEx]

    }

}

// 改造起始地址
int HookSystemcallx86tox64::GetEditLength(PVOID CodeAdderss)
{
    unsigned char szCode[7] = {0x64, 0xFF , 0x15 , 0xC0 , 0x00 , 0x00 , 0x00};
    for(int i = 0; i < 0x20; i++)
    {
        if(memcmp((PVOID)((DWORD)CodeAdderss + i), szCode, 7) == 0)
        {
            return i;
        }
    }
    return 0;
}
/*
	.text:7DC66B9D B8 6E 10 00 00                                      mov     eax, 106Eh
	.text:7DC66BA2 B9 00 00 00 00                                      mov     ecx, 0
	.text:7DC66BA7 8D 54 24 04                                         lea     edx, [esp+arg_0]
	.text:7DC66BAB 64 FF 15 C0 00 00 00                                call    large dword ptr fs:0C0h
	.text:7DC66BB2 83 C4 04                                            add     esp, 4
	.text:7DC66BB5 C2 14 00                                            retn    14h
*/

// 安装钩子
BOOL HookSystemcallx86tox64::InstallHook(PCHAR FunName,		//NTAPI
        DWORD pHookFunc,	//HOOK的函数
        DWORD* pOrigFunc)	//返回的函数
{
    DWORD dwOldProtect;
    DWORD dwIndex = GetSysCallIndex(FunName);

    DWORD	dwFunadd = PtrToUlong(GetProcAddress(GetModuleHandleA("NTDLL.dll"), FunName));

    //保存各种信息
    dwOrigX86SwitchTo64[dwIndex] = (PDWORD)malloc(0x20);

    //将原本的ZW函数保存进去
    memcpy(dwOrigX86SwitchTo64[dwIndex], (PVOID)dwFunadd, 0x20);

    //获取改造起始偏移
    int nlen = GetEditLength(dwOrigX86SwitchTo64[dwIndex]);

    //DbgPrint("输出 index[%08x]%08x,%d %s\r\n",dwIndex,dwOrigX86SwitchTo64[dwIndex],nlen,FunName);
    //野猪改造开始
    VirtualProtect(ULongToPtr(dwOrigX86SwitchTo64[dwIndex]), 0x20, PAGE_EXECUTE_READWRITE, &dwOldProtect);

    *(PBYTE)((DWORD)dwOrigX86SwitchTo64[dwIndex]	+ nlen)		=	 0xE8;
    *(PDWORD)((DWORD)dwOrigX86SwitchTo64[dwIndex]	+ nlen + 1)	= (DWORD)dwX86SwitchTo64BitModeEx - (DWORD)dwOrigX86SwitchTo64[dwIndex] - nlen - 5;
    *(PWORD)((DWORD)dwOrigX86SwitchTo64[dwIndex]	+ nlen + 5)	=	 0x9090;


    * pOrigFunc = (DWORD)dwOrigX86SwitchTo64[dwIndex];

    //开始HOOK
    dwHookX86SwitchTo64[dwIndex] = pHookFunc;

    return 0;
}
//EX SystemCall
__declspec(naked) void SystemCallX64()
{
    __asm
    {
        __emit 0x90
        mov eax, 0x11B2
        mov     ecx, 0
        lea     edx, [esp+0x4]
        //64 FF 15 C0 00 00 00
        __emit 0x64
        __emit 0xFF
        __emit 0x15
        __emit 0xC0
        __emit 0x00
        __emit 0x00
        __emit 0x00
        add esp, 0x4
        retn 0xFF
        __emit 0x90
    }
}
// Ex安装钩子
BOOL HookSystemcallx86tox64::InstallHookEx(DWORD dwIndex,		//NTAPI
        WORD dwRetIndex,	//返回堆栈平衡
        DWORD pHookFunc,		//HOOK的函数
        DWORD* pOrigFunc)	//返回的函数
{
    DWORD dwOldProtect;


    //保存各种信息
    dwOrigX86SwitchTo64[dwIndex] = (PDWORD)malloc(0x20);

    //将原本的ZW函数保存进去
    memcpy(dwOrigX86SwitchTo64[dwIndex], (PVOID)SystemCallX64, 0x20);

    //获取改造起始偏移
    int nlen = GetEditLength(dwOrigX86SwitchTo64[dwIndex]);

    //DbgPrint("输出 index[%08x]%08x,%d\r\n",dwIndex,dwOrigX86SwitchTo64[dwIndex],nlen);
    //野猪改造开始
    VirtualProtect(ULongToPtr(dwOrigX86SwitchTo64[dwIndex]), 0x20, PAGE_EXECUTE_READWRITE, &dwOldProtect);

    *(PDWORD)((DWORD)dwOrigX86SwitchTo64[dwIndex]	+ 2)		=	 dwIndex;
    *(PBYTE)((DWORD)dwOrigX86SwitchTo64[dwIndex]	+ nlen)		=	 0xE8;
    *(PDWORD)((DWORD)dwOrigX86SwitchTo64[dwIndex]	+ nlen + 1)	= (DWORD)dwX86SwitchTo64BitModeEx - (DWORD)dwOrigX86SwitchTo64[dwIndex] - nlen - 5;
    *(PWORD)((DWORD)dwOrigX86SwitchTo64[dwIndex]	+ nlen + 5)	=	 0x9090;
    *(PWORD)((DWORD)dwOrigX86SwitchTo64[dwIndex]	+ nlen + 7 + 3 + 1) = dwRetIndex;

    * pOrigFunc = (DWORD)dwOrigX86SwitchTo64[dwIndex];

    //开始HOOK
    dwHookX86SwitchTo64[dwIndex] = pHookFunc;

    return 0;
}
//调用函数GetDllFuncAddr以便获得服务号
int HookSystemcallx86tox64::GetSysCallIndex(PCHAR FuncName)
{
    DWORD          FuncAddr;    //函数地址
    int            SysCallIndex;//服务号

    FuncAddr =  PtrToUlong(GetProcAddress(GetModuleHandleA("NTDLL.dll"), FuncName));
    SysCallIndex = *((WORD*)(FuncAddr + 1));
    return SysCallIndex;
}


// 获取模式转换函数地址
DWORD HookSystemcallx86tox64::GetX86toX64BitModeFun(void)
{
    DWORD dwFsAdd;
    __asm
    {
        push eax
        mov eax, dword ptr fs:[0x000000C0]
        mov dwFsAdd, eax
        pop eax
    }
    return dwFsAdd;
}

// 初始化
BOOL HookSystemcallx86tox64::Initialization(void)
{
    DWORD dwOldProtect;
    memset(dwHookX86SwitchTo64, 0, sizeof(DWORD) * 0x4048);

    dwX86SwitchTo64BitMode = GetX86toX64BitModeFun();
    dwX86SwitchTo64BitModeEx = (PDWORD)malloc(0xA);

    VirtualProtect(ULongToPtr(dwX86SwitchTo64BitModeEx), 10, PAGE_EXECUTE_READWRITE, &dwOldProtect);
    RtlCopyMemory(dwX86SwitchTo64BitModeEx, (PVOID)dwX86SwitchTo64BitMode, 7);
    VirtualProtect(ULongToPtr(dwX86SwitchTo64BitMode), 10, PAGE_EXECUTE_READWRITE, &dwOldProtect);

    *(PBYTE)ULongToPtr(dwX86SwitchTo64BitMode) = 0xE9;
    *(PDWORD)ULongToPtr(dwX86SwitchTo64BitMode + 1) = PtrToUlong(X86SwitchTo64BitMode) - dwX86SwitchTo64BitMode - 5;

    //VirtualProtect(ULongToPtr(dwX86SwitchTo64BitMode), 10, dwOldProtect, &dwOldProtect);

    return 0;
}

VOID HookSystemcallx86tox64::UnInitialization(void)
{
    RtlCopyMemory((PVOID)dwX86SwitchTo64BitMode, dwX86SwitchTo64BitModeEx, 7);
}

///////////////////////by:exediy  QQ:393234111