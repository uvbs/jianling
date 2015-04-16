// InlineHook.cpp: implementation of the InlineHook class.
//
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "CHook.h"
#include "LDasm.h"



CHook::CHook(void* CallAddr, void* NewCall, BOOL bAutoDel)
{
    Init(CallAddr, NewCall, bAutoDel);
    m_BackupCall = NULL;
}


CHook::~CHook()
{
    unhook();
}

CHook::CHook()
{
    m_BackupCall = NULL;
    m_CallAddr = NULL;
    m_NewCall = NULL;
    m_bAutoDel = TRUE;
}

void CHook::Init(void* CallAddr, void* NewCall, BOOL bAutoDel)
{
    m_CallAddr = (BYTE*)CallAddr;
    m_NewCall = (BYTE*)NewCall;
    m_bAutoDel = bAutoDel;
}



//返回根据函数头分析需要修补的大小
BOOL CHook::GetPatchSize(void* Proc, DWORD dwNeedSize, LPDWORD lpPatchSize)
{
    DWORD Length;
    PUCHAR pOpcode;
    DWORD PatchSize = 0;
    //前置的参数检查
    if(!Proc || !lpPatchSize)
    {
        return FALSE;
    }
    do
    {
        Length = LDasm::SizeOfCode(Proc, &pOpcode);
        if((Length == 1) && (*pOpcode == 0xC3))
        {
            break;
        }
        if((Length == 3) && (*pOpcode == 0xC2))
        {
            break;
        }
        Proc = (PVOID)((DWORD)Proc + Length);
        PatchSize += Length;
        if(PatchSize >= dwNeedSize)
        {
            break;
        }
    }
    while(Length);
    *lpPatchSize = PatchSize;
    return TRUE;
}

//钩游戏call
//参数1: 目标函数地址
//参数2:  我们的处理函数
//返回入口点
DWORD* CHook::hook()
{
	//TRACE1("Hook addr:%08x", m_CallAddr);
    if(m_BackupCall != NULL)
	{
        return (DWORD*)m_BackupCall;
    }

    __try
    {

        BYTE sub[10];
        memset(sub, 0x90, 10);
        sub[0] = 0xe9;


        BYTE backjmp[5];
        memset(backjmp, 0x90, 5);
        backjmp[0] = 0xe9;


        DWORD pfunStart = (DWORD)sub;
        //改内存属性
        DWORD dwOldProtect;
        if(!VirtualProtect(m_CallAddr, 4, PAGE_EXECUTE_READWRITE, &dwOldProtect))
        {
            return 0;
        }


        if(!VirtualProtect((void*)pfunStart, 4, PAGE_EXECUTE_READWRITE, &dwOldProtect))
        {
            return 0;
        }


        //判断已经hook的情况
        if(*(BYTE*)m_CallAddr == 0xe9)
        {
            OutputDebugString(_T("地址已经被HOOK"));
            return 0;
        }



        //取得合适的大小
        DWORD dwPathSize;
        if(!GetPatchSize(m_CallAddr, 5, &dwPathSize))
        {
            return 0;
        }



        //申请一块内存
        //布局
        // 4  sub大小
        // 备份的出来的原始字节 (可能会改)
        // jmp 原本入口点
        // 原始的字节 ( 不会更改), 恢复call时应该从此处拷贝原始数据
        m_nLen = 4 + dwPathSize + 5 + dwPathSize;
        BYTE* backup = (BYTE*)VirtualAlloc(NULL, m_nLen, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
        memset(backup, 0x90, m_nLen);
        int nCall = (DWORD)m_NewCall - (DWORD)m_CallAddr - 5;
        memcpy((void*)(sub + 1), (void*)&nCall, 4);



        //填充跳回的地址
        nCall = (int)m_CallAddr + dwPathSize - ((int)backup + 4 + dwPathSize) - 5;
        memcpy((void*)((int)backjmp + 1), (void*)&nCall, 4);



        //前四个字节填充hook的大小
        *(DWORD*)backup = dwPathSize;
        //备份这几个字节数据到 + 4
        memcpy(backup + 4, m_CallAddr, dwPathSize);



        if(*(backup + 4) == 0xeb)
        {
            *(backup + 4) = 0xe9;
            int oplen = *(backup + 4 + 1);
            int nCall = (DWORD)m_CallAddr + oplen - (DWORD)m_CallAddr - 5;
            memcpy((void*)(backup + 4 + 1), (void*)&nCall, 4);
        }


        //后边跟上跳回的指令
        memcpy((backup + 4 + dwPathSize), backjmp, 5);
        memcpy((backup + 4 + dwPathSize + 5), m_CallAddr, dwPathSize);
       

        //装钩子
        memcpy(m_CallAddr, (void*)sub, dwPathSize);


        m_BackupCall = (backup + 4);
        return (DWORD*)m_BackupCall;
    }
    __except(1)
    {
        OutputDebugString(_T("安装钩子异常"));
    }


    return 0;
}


void CHook::unhook()
{
    if(m_BackupCall == NULL)
    {
        return;
    }


    __try
    {

        DWORD dwOldProtect;
        VirtualProtect(m_CallAddr, 4, PAGE_EXECUTE_READWRITE, &dwOldProtect);
        if(m_bAutoDel)
        {
            DWORD len = *(int*)(m_BackupCall - 4);
            memcpy(m_CallAddr, m_BackupCall + len + 5, len);

            //释放掉申请的内存
            VirtualFree(m_BackupCall - 4, m_nLen, MEM_DECOMMIT);
            m_BackupCall = NULL;
        }
    }
    __except(1)
    {
        OutputDebugString(_T("卸载钩子异常"));
    }
}

