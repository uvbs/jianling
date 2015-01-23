// Work.h: interface for the CWork class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_WORK_H__2DAF972A_D048_4E15_8864_0EDBA195C8F1__INCLUDED_)
#define AFX_WORK_H__2DAF972A_D048_4E15_8864_0EDBA195C8F1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000



class CWork  
{
public:
	virtual void DoWork() = 0;
	CWork(){};
	virtual ~CWork(){};
 
};


#endif // !defined(AFX_WORK_H__2DAF972A_D048_4E15_8864_0EDBA195C8F1__INCLUDED_)
