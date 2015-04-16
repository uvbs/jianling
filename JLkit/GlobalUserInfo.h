// GlobalUserInfo.h: interface for the CGlobalUserInfo class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GLOBALUSERINFO_H__1B9E3163_A17F_491B_BE28_C5867DAA6FEE__INCLUDED_)
#define AFX_GLOBALUSERINFO_H__1B9E3163_A17F_491B_BE28_C5867DAA6FEE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//KEY
typedef std::vector<QUERYKEY_SUCCESS> KeyVec;


class CGlobalUserInfo
{
protected:
	CGlobalUserInfo();
	virtual ~CGlobalUserInfo();

public:
    DWORD dwKeyNums; //key数量


    //当前卡号
    KeyVec m_KeyVec;


    DECLARE_SINGLETON(CGlobalUserInfo)
};

#endif // !defined(AFX_GLOBALUSERINFO_H__1B9E3163_A17F_491B_BE28_C5867DAA6FEE__INCLUDED_)
