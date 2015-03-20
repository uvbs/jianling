// AttackLogic.h: interface for the AttackLogic class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ATTACKLOGIC_H__CDE366A2_A953_46A3_A942_B1D627032D52__INCLUDED_)
#define AFX_ATTACKLOGIC_H__CDE366A2_A953_46A3_A942_B1D627032D52__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Logic.h"
class AttackLogic: public Logic
{
public:


    virtual void Update(pfn_FUNC pfn);
};


#endif // !defined(AFX_ATTACKLOGIC_H__CDE366A2_A953_46A3_A942_B1D627032D52__INCLUDED_)
