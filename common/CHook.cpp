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



//���ظ��ݺ���ͷ������Ҫ�޲��Ĵ�С
BOOL CHook::GetPatchSize(void* Proc, DWORD dwNeedSize, LPDWORD lpPatchSize)
{
    DWORD Length;
    PUCHAR pOpcode;
    DWORD PatchSize = 0;
    //ǰ�õĲ������
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

//����Ϸcall
//����1: Ŀ�꺯����ַ
//����2:  ���ǵĴ�����
//������ڵ�
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
        //���ڴ�����
        DWORD dwOldProtect;
        if(!VirtualProtect(m_CallAddr, 4, PAGE_EXECUTE_READWRITE, &dwOldProtect))
        {
            return 0;
        }


        if(!VirtualProtect((void*)pfunStart, 4, PAGE_EXECUTE_READWRITE, &dwOldProtect))
        {
            return 0;
        }


        //�ж��Ѿ�hook�����
        if(*(BYTE*)m_CallAddr == 0xe9)
        {
            OutputDebugString(_T("��ַ�Ѿ���HOOK"));
            return 0;
        }



        //ȡ�ú��ʵĴ�С
        DWORD dwPathSize;
        if(!GetPatchSize(m_CallAddr, 5, &dwPathSize))
        {
            return 0;
        }



        //����һ���ڴ�
        //����
        // 4  sub��С
        // ���ݵĳ�����ԭʼ�ֽ� (���ܻ��)
        // jmp ԭ����ڵ�
        // ԭʼ���ֽ� ( �������), �ָ�callʱӦ�ôӴ˴�����ԭʼ����
        m_nLen = 4 + dwPathSize + 5 + dwPathSize;
        BYTE* backup = (BYTE*)VirtualAlloc(NULL, m_nLen, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
        memset(backup, 0x90, m_nLen);
        int nCall = (DWORD)m_NewCall - (DWORD)m_CallAddr - 5;
        memcpy((void*)(sub + 1), (void*)&nCall, 4);



        //������صĵ�ַ
        nCall = (int)m_CallAddr + dwPathSize - ((int)backup + 4 + dwPathSize) - 5;
        memcpy((void*)((int)backjmp + 1), (void*)&nCall, 4);



        //ǰ�ĸ��ֽ����hook�Ĵ�С
        *(DWORD*)backup = dwPathSize;
        //�����⼸���ֽ����ݵ� + 4
        memcpy(backup + 4, m_CallAddr, dwPathSize);



        if(*(backup + 4) == 0xeb)
        {
            *(backup + 4) = 0xe9;
            int oplen = *(backup + 4 + 1);
            int nCall = (DWORD)m_CallAddr + oplen - (DWORD)m_CallAddr - 5;
            memcpy((void*)(backup + 4 + 1), (void*)&nCall, 4);
        }


        //��߸������ص�ָ��
        memcpy((backup + 4 + dwPathSize), backjmp, 5);
        memcpy((backup + 4 + dwPathSize + 5), m_CallAddr, dwPathSize);
       

        //װ����
        memcpy(m_CallAddr, (void*)sub, dwPathSize);


        m_BackupCall = (backup + 4);
        return (DWORD*)m_BackupCall;
    }
    __except(1)
    {
        OutputDebugString(_T("��װ�����쳣"));
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

            //�ͷŵ�������ڴ�
            VirtualFree(m_BackupCall - 4, m_nLen, MEM_DECOMMIT);
            m_BackupCall = NULL;
        }
    }
    __except(1)
    {
        OutputDebugString(_T("ж�ع����쳣"));
    }
}

