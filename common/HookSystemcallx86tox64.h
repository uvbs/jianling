#pragma once
#include "Common.h"

///////////////////////by:exediy  QQ:393234111

class HookSystemcallx86tox64
{
public:
    HookSystemcallx86tox64(void);
    virtual ~HookSystemcallx86tox64(void);

    // X64下X86模式进入内核函数地址
    DWORD dwX86SwitchTo64BitMode;

    //调用函数GetDllFuncAddr以便获得服务号
    int GetSysCallIndex(PCHAR FuncName);

    // 获取模式转换函数地址
    DWORD GetX86toX64BitModeFun(void);
    // 初始化
    BOOL Initialization(void);

    VOID UnInitialization(void);

    // 安装钩子
    BOOL InstallHook(PCHAR FunName,//NTAPI
                     DWORD pHookFunc,	//HOOK的函数
                     DWORD* pOrigFunc);	//返回的函数

    // Ex安装钩子
    BOOL InstallHookEx(DWORD dwIndex,		//NTAPI
                       WORD dwRetIndex,	//返回堆栈平衡
                       DWORD pHookFunc,		//HOOK的函数
                       DWORD* pOrigFunc);	//返回的函数

    // 改造起始地址
    int GetEditLength(PVOID CodeAdderss);
};
///////////////////////by:exediy  QQ:393234111