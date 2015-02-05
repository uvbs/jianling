// Request.cpp: implementation of the CRequest class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "JLSrvr.h"
#include "Request.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CRequest::CRequest()
{

    m_reqNums = 0;
}

CRequest::~CRequest()
{
}

int CRequest::AddRef()
{
    return ++m_reqNums;
}

int CRequest::Release()
{
    int nRefs = --m_reqNums;
    if(nRefs == 0)
    {
        delete this;
    }
    return nRefs;
}
