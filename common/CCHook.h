// InlineHook.h: interface for the InlineHook class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_INLINEHOOK_H__C46FFB69_056F_4680_9BF3_A98586E9AD31__INCLUDED_)
#define AFX_INLINEHOOK_H__C46FFB69_056F_4680_9BF3_A98586E9AD31__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000




class CCHook
{
public:
	CCHook();
	CCHook(void* CallAddr, void* NewCall, BOOL bAutoDel = TRUE);
	~CCHook();
	void Init(void* CallAddr, void* NewCall, BOOL bAutoDel = TRUE);


	void unhook();
	void* hook();


private:
	BOOL GetPatchSize(void *Proc, DWORD dwNeedSize, LPDWORD lpPatchSize);


	BYTE *m_CallAddr;	//call地址
	BYTE *m_NewCall;	//新call地址
	BYTE *m_BackupCall; //备份的入口点
	BOOL m_bAutoDel;
	int m_nLen;
};


#endif // !defined(AFX_INLINEHOOK_H__C46FFB69_056F_4680_9BF3_A98586E9AD31__INCLUDED_)
