// ontrolLogic.h: interface for the ControlLogic class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ONTROLLOGIC_H__76931224_80C1_43EC_9C3C_8CE8BE8A06E9__INCLUDED_)
#define AFX_ONTROLLOGIC_H__76931224_80C1_43EC_9C3C_8CE8BE8A06E9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Logic.h"
class ControLogic: public Logic
{
public:
    virtual void Update(pfn_FUNC pfn);

};


#endif // !defined(AFX_ONTROLLOGIC_H__76931224_80C1_43EC_9C3C_8CE8BE8A06E9__INCLUDED_)
