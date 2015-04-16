// GlobalUserInfo.cpp: implementation of the CGlobalUserInfo class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "jlkit.h"
#include "GlobalUserInfo.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
    #define new DEBUG_NEW
#endif



IMPLEMENT_SINGLETON(CGlobalUserInfo)

//¹¹Ôìº¯Êý
CGlobalUserInfo::CGlobalUserInfo()
{

}

CGlobalUserInfo::~CGlobalUserInfo()
{
    m_KeyVec.clear();
}
