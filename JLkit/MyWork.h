// MyWork.h: interface for the CMyWork class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYWORK_H__A5FB9599_55DE_45DA_A302_EB2E79321C7B__INCLUDED_)
#define AFX_MYWORK_H__A5FB9599_55DE_45DA_A302_EB2E79321C7B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\common\Work.h"


class CLock;
class CJLkitView;
class MyCWork: public CWork
{
public:
 	MyCWork(int item, CJLkitView *pParam);
	~MyCWork();
	void DoWork();
    
private:
    CJLkitView* m_pFrame;
    int nItem;				//当前处理的下标
    CLock *m_lpLock;
};


#endif // !defined(AFX_MYWORK_H__A5FB9599_55DE_45DA_A302_EB2E79321C7B__INCLUDED_)
