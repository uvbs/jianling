#include "stdafx.h"

#ifdef WIN32
#define RING3
#endif

#include "inlinehook.h"
#include "..\common\LDasm.h"

/*

这是这个 RING3 宏定义和不定义产生的区别

定义了 用 r3层的 VirtualAlloc 申请内存
没定义用  ExAllocataPool 申请内存

r0层是不能用 r3 层的 api.

这个函数是在 内核文件 ntoskrnl.exe 中导出的
驱动DKK 中可以查到

sdk software 是软件开发工具
ddk driver 是驱动开发工具

developer kit 就是开发工具的意思, 包括头文件, 库文件(lib文件).

*/



#ifdef RING3
#define __malloc(_s)	VirtualAlloc(NULL, _s, MEM_COMMIT, PAGE_EXECUTE_READWRITE)
#define __free(_p)		VirtualFree(_p, 0, MEM_RELEASE)
#define JMP_SIZE		5
#else
#define __malloc(_s)	ExAllocatePool(NonPagedPool, _s)
#define __free(_p)		ExFreePool(_p)
#define JMP_SIZE		7
#endif

#ifdef RING3



BOOL WriteReadOnlyMemory(LPBYTE	lpDest, LPBYTE	lpSource, ULONG	Length)
{
    BOOL bRet;
    DWORD dwOldProtect;
    bRet = FALSE;

    if(!VirtualProtect(lpDest, Length, PAGE_EXECUTE_READWRITE, &dwOldProtect))
    {
        return bRet;
    }

    memcpy(lpDest, lpSource, Length);

    bRet = VirtualProtect(lpDest, Length, dwOldProtect, &dwOldProtect);

    return	bRet;
}

#else

NTSTATUS
WriteReadOnlyMemory(
    LPBYTE	lpDest,
    LPBYTE	lpSource,
    ULONG	Length
)
{
    NTSTATUS status;
    KSPIN_LOCK spinLock;
    KIRQL oldIrql;
    PMDL pMdlMemory;
    LPBYTE lpWritableAddress;

    status = STATUS_UNSUCCESSFUL;

    pMdlMemory = IoAllocateMdl(lpDest, Length, FALSE, FALSE, NULL);

    if(NULL == pMdlMemory)
    {
        return status;
    }

    MmBuildMdlForNonPagedPool(pMdlMemory);
    MmProbeAndLockPages(pMdlMemory, KernelMode, IoWriteAccess);
    lpWritableAddress = MmMapLockedPages(pMdlMemory, KernelMode);
    if(NULL != lpWritableAddress)
    {
        oldIrql	= 0;
        KeInitializeSpinLock(&spinLock);
        KeAcquireSpinLock(&spinLock, &oldIrql);

        memcpy(lpWritableAddress, lpSource, Length);

        KeReleaseSpinLock(&spinLock, oldIrql);
        MmUnmapLockedPages(lpWritableAddress, pMdlMemory);

        status = STATUS_SUCCESS;
    }

    MmUnlockPages(pMdlMemory);
    IoFreeMdl(pMdlMemory);

    return status;
}

#endif

BOOL GetPatchSize(void* Proc, DWORD dwNeedSize, LPDWORD lpPatchSize)
{
    DWORD Length;
    PUCHAR pOpcode;
    DWORD PatchSize = 0;

    /*前置的参数检查*/
    if(!Proc || !lpPatchSize)
    {
        return FALSE;
    }


    do
    {
        Length = SizeOfCode(Proc, &pOpcode);
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


/*

内联钩子

*/
BOOL InlineHook(void* OrgProc, void* NewProc, void** RealProc)
{
    DWORD dwPatchSize;    //得到需要patch的字节大小
    LPVOID lpHookFunc;    //分配的Hook函数的内存
    DWORD dwBytesNeed;    //分配的Hook函数的大小
    LPBYTE lpPatchBuffer; //jmp 指令的临时缓冲区


    //前置的参数检查, 参数不正确就返回了
    if(!OrgProc || !NewProc || !RealProc)
    {
        return FALSE;
    }


    //得到需要需要hook的函数开头的某些大小
    //这个函数掉进去涉及到 Opcode, 意思就是取得函数头到某条指令的大小,
    //毕竟汇编指令本身的长度不一样, 需要确定边界, 这个函数是这么个意思
    //返回的 dwPatchSize 包含了长度

    if(!GetPatchSize(OrgProc, JMP_SIZE, &dwPatchSize))
    {
        return FALSE;
    }

    /*
    0x00000800					0x00000800		sizeof(DWORD)	// dwPatchSize
    JMP	/ FAR 0xAABBCCDD		E9 DDCCBBAA		JMP_SIZE
    ...							...				dwPatchSize		// Backup instruction
    JMP	/ FAR 0xAABBCCDD		E9 DDCCBBAA		JMP_SIZE
    */

    //获得总共需要的字节长度
    dwBytesNeed = sizeof(DWORD) + JMP_SIZE + dwPatchSize + JMP_SIZE;


    //申请一片此长度的内存, 返回值指向这片内存
    lpHookFunc = __malloc(dwBytesNeed);

    //这片内存第一个双字是 dwPathchSize 大小
    //备份dwPatchSize到lpHookFunc
    *(DWORD*)lpHookFunc = dwPatchSize;

    //跳过开头的4个字节
    lpHookFunc = (LPVOID)((DWORD)lpHookFunc + sizeof(DWORD));

    //开始backup函数开头的字
    memcpy((BYTE*)lpHookFunc + JMP_SIZE, OrgProc, dwPatchSize);



    lpPatchBuffer = (LPBYTE)__malloc(dwPatchSize);

    //NOP填充
    memset(lpPatchBuffer, 0x90, dwPatchSize);


#ifdef RING3
    //jmp到Hook
    *(BYTE*)lpHookFunc = 0xE9;


    //这个 NewProc 是此函数参数, 传进来的是目标指针, 就是要跳转到我们的代码的地址
    *(DWORD*)((DWORD)lpHookFunc + 1) = (DWORD)NewProc - (DWORD)lpHookFunc - JMP_SIZE;

    //跳回原始
    *(BYTE*)((DWORD)lpHookFunc + 5 + dwPatchSize) = 0xE9;
    *(DWORD*)((DWORD)lpHookFunc + 5 + dwPatchSize + 1) = ((DWORD)OrgProc + dwPatchSize) - ((DWORD)lpHookFunc + JMP_SIZE + dwPatchSize) - JMP_SIZE;


    //jmp
    *(BYTE*)lpPatchBuffer = 0xE9;
    //注意计算长度的时候得用OrgProc
    *(DWORD*)(lpPatchBuffer + 1) = (DWORD)lpHookFunc - (DWORD)OrgProc - JMP_SIZE;

#else

    //jmp到Hook
    *(BYTE*)lpHookFunc = 0xEA;
    *(DWORD*)((DWORD)lpHookFunc + 1) = (DWORD)NewProc;
    *(WORD*)((DWORD)lpHookFunc + 5) = 0x08;

    //跳回原始
    *(BYTE*)((DWORD)lpHookFunc + JMP_SIZE + dwPatchSize) = 0xEA;
    *(DWORD*)((DWORD)lpHookFunc + JMP_SIZE + dwPatchSize + 1) = ((DWORD)OrgProc + dwPatchSize);
    *(WORD*)((DWORD)lpHookFunc + JMP_SIZE + dwPatchSize + 5) = 0x08;

    //jmp far
    *(BYTE*)lpPatchBuffer = 0xEA;

    //跳到lpHookFunc函数
    *(DWORD*)(lpPatchBuffer + 1) = (DWORD)lpHookFunc;
    *(WORD*)(lpPatchBuffer + 5) = 0x08;
#endif


    WriteReadOnlyMemory((LPBYTE)OrgProc, lpPatchBuffer, dwPatchSize);

    __free(lpPatchBuffer);

    *RealProc = (void*)((DWORD)lpHookFunc + JMP_SIZE);

    return TRUE;
}

void UnInlineHook(void* OrgProc, void* RealProc)
{
    DWORD dwPatchSize;
    //DWORD dwOldProtect;
    LPBYTE lpBuffer;

    //找到分配的空间
    lpBuffer = (LPBYTE)((DWORD)RealProc - (sizeof(DWORD) + JMP_SIZE));
    //得到dwPatchSize
    dwPatchSize = *(DWORD*)lpBuffer;

    WriteReadOnlyMemory((LPBYTE)OrgProc, (LPBYTE)RealProc, dwPatchSize);

    //释放分配的跳转函数的空间
    __free(lpBuffer);

    return;
}