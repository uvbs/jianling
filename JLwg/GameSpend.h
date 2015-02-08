// GameSpend.h: interface for the GameSpend class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GAMESPEND_H__C21DB428_5D98_4535_817B_E6E7A67D8713__INCLUDED_)
#define AFX_GAMESPEND_H__C21DB428_5D98_4535_817B_E6E7A67D8713__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include "..\common\CCHook.h"



//��ʼ������
class GameSpend  
{
public:
	GameSpend();
	virtual ~GameSpend();


    void Init();



    typedef int (*_InitializeSpeedhack)(float);
    _InitializeSpeedhack m_pfnInitSpeed;

private:
    HMODULE	m_hack;	//����ģ����
    CCHook ce_hookGetTickCount;
    CCHook ce_hookQueryPerformanceCounter;
    CCHook ce_hooktimeGetTime;
};

#endif // !defined(AFX_GAMESPEND_H__C21DB428_5D98_4535_817B_E6E7A67D8713__INCLUDED_)
