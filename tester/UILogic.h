// UILogic.h: interface for the UILogic class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_UILOGIC_H__FF594DF0_86C7_4313_B3B4_2F3D53870A2F__INCLUDED_)
#define AFX_UILOGIC_H__FF594DF0_86C7_4313_B3B4_2F3D53870A2F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Logic.h"
class UILogic: public Logic
{

public:
    virtual void Update(pfn_FUNC pfn);
};



#endif // !defined(AFX_UILOGIC_H__FF594DF0_86C7_4313_B3B4_2F3D53870A2F__INCLUDED_)
