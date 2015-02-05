#include "stdafx.h"

#ifdef WIN32
#define RING3
#endif

#include "inlinehook.h"
#include "..\common\LDasm.h"

/*

������� RING3 �궨��Ͳ��������������

������ �� r3��� VirtualAlloc �����ڴ�
û������  ExAllocataPool �����ڴ�

r0���ǲ����� r3 ��� api.

����������� �ں��ļ� ntoskrnl.exe �е�����
����DKK �п��Բ鵽

sdk software �������������
ddk driver ��������������

developer kit ���ǿ������ߵ���˼, ����ͷ�ļ�, ���ļ�(lib�ļ�).

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

    /*ǰ�õĲ������*/
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

��������

*/
BOOL InlineHook(void* OrgProc, void* NewProc, void** RealProc)
{
    DWORD dwPatchSize;    //�õ���Ҫpatch���ֽڴ�С
    LPVOID lpHookFunc;    //�����Hook�������ڴ�
    DWORD dwBytesNeed;    //�����Hook�����Ĵ�С
    LPBYTE lpPatchBuffer; //jmp ָ�����ʱ������


    //ǰ�õĲ������, ��������ȷ�ͷ�����
    if(!OrgProc || !NewProc || !RealProc)
    {
        return FALSE;
    }


    //�õ���Ҫ��Ҫhook�ĺ�����ͷ��ĳЩ��С
    //�����������ȥ�漰�� Opcode, ��˼����ȡ�ú���ͷ��ĳ��ָ��Ĵ�С,
    //�Ͼ����ָ���ĳ��Ȳ�һ��, ��Ҫȷ���߽�, �����������ô����˼
    //���ص� dwPatchSize �����˳���

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

    //����ܹ���Ҫ���ֽڳ���
    dwBytesNeed = sizeof(DWORD) + JMP_SIZE + dwPatchSize + JMP_SIZE;


    //����һƬ�˳��ȵ��ڴ�, ����ֵָ����Ƭ�ڴ�
    lpHookFunc = __malloc(dwBytesNeed);

    //��Ƭ�ڴ��һ��˫���� dwPathchSize ��С
    //����dwPatchSize��lpHookFunc
    *(DWORD*)lpHookFunc = dwPatchSize;

    //������ͷ��4���ֽ�
    lpHookFunc = (LPVOID)((DWORD)lpHookFunc + sizeof(DWORD));

    //��ʼbackup������ͷ����
    memcpy((BYTE*)lpHookFunc + JMP_SIZE, OrgProc, dwPatchSize);



    lpPatchBuffer = (LPBYTE)__malloc(dwPatchSize);

    //NOP���
    memset(lpPatchBuffer, 0x90, dwPatchSize);


#ifdef RING3
    //jmp��Hook
    *(BYTE*)lpHookFunc = 0xE9;


    //��� NewProc �Ǵ˺�������, ����������Ŀ��ָ��, ����Ҫ��ת�����ǵĴ���ĵ�ַ
    *(DWORD*)((DWORD)lpHookFunc + 1) = (DWORD)NewProc - (DWORD)lpHookFunc - JMP_SIZE;

    //����ԭʼ
    *(BYTE*)((DWORD)lpHookFunc + 5 + dwPatchSize) = 0xE9;
    *(DWORD*)((DWORD)lpHookFunc + 5 + dwPatchSize + 1) = ((DWORD)OrgProc + dwPatchSize) - ((DWORD)lpHookFunc + JMP_SIZE + dwPatchSize) - JMP_SIZE;


    //jmp
    *(BYTE*)lpPatchBuffer = 0xE9;
    //ע����㳤�ȵ�ʱ�����OrgProc
    *(DWORD*)(lpPatchBuffer + 1) = (DWORD)lpHookFunc - (DWORD)OrgProc - JMP_SIZE;

#else

    //jmp��Hook
    *(BYTE*)lpHookFunc = 0xEA;
    *(DWORD*)((DWORD)lpHookFunc + 1) = (DWORD)NewProc;
    *(WORD*)((DWORD)lpHookFunc + 5) = 0x08;

    //����ԭʼ
    *(BYTE*)((DWORD)lpHookFunc + JMP_SIZE + dwPatchSize) = 0xEA;
    *(DWORD*)((DWORD)lpHookFunc + JMP_SIZE + dwPatchSize + 1) = ((DWORD)OrgProc + dwPatchSize);
    *(WORD*)((DWORD)lpHookFunc + JMP_SIZE + dwPatchSize + 5) = 0x08;

    //jmp far
    *(BYTE*)lpPatchBuffer = 0xEA;

    //����lpHookFunc����
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

    //�ҵ�����Ŀռ�
    lpBuffer = (LPBYTE)((DWORD)RealProc - (sizeof(DWORD) + JMP_SIZE));
    //�õ�dwPatchSize
    dwPatchSize = *(DWORD*)lpBuffer;

    WriteReadOnlyMemory((LPBYTE)OrgProc, (LPBYTE)RealProc, dwPatchSize);

    //�ͷŷ������ת�����Ŀռ�
    __free(lpBuffer);

    return;
}