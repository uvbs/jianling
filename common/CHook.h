// InlineHook.h: interface for the InlineHook class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_INLINEHOOK_H__C46FFB69_056F_4680_9BF3_A98586E9AD31__INCLUDED_)
#define AFX_INLINEHOOK_H__C46FFB69_056F_4680_9BF3_A98586E9AD31__INCLUDED_



class CHook
{
public:
    CHook();
    CHook(void* CallAddr, void* NewCall, BOOL bAutoDel = TRUE);
    ~CHook();

    //��ʼ��
    void Init(void* CallAddr, void* NewCall, BOOL bAutoDel = TRUE);

    //ж�ع���
    void unhook();

    //��װ����
    DWORD* hook();

    //��ȡָ��߽��С
protected:
    BOOL GetPatchSize(void* Proc, DWORD dwNeedSize, LPDWORD lpPatchSize);

private:
    BYTE* m_CallAddr;   //call��ַ
    BYTE* m_NewCall;    //��call��ַ
    BYTE* m_BackupCall; //���ݵ���ڵ�
    BOOL m_bAutoDel;    //�Զ�ɾ��
    int m_nLen;
};


#endif // !defined(AFX_INLINEHOOK_H__C46FFB69_056F_4680_9BF3_A98586E9AD31__INCLUDED_)
