// Request.h: interface for the CRequest class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_REQUEST_H__8DB4623A_D730_4D3D_9647_34D893564383__INCLUDED_)
#define AFX_REQUEST_H__8DB4623A_D730_4D3D_9647_34D893564383__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CRequest: public CObject
{
public:
    CRequest();
    virtual ~CRequest();

    CString strType;
    CString strTime;
    CString strUserName;
    CString strOther;
    CString strIp;
    CString strResult;
    DWORD m_reqNums;    //ÇëÇó´ÎÊý
    CTime m_time;

    int AddRef();
    int Release();
};

#endif // !defined(AFX_REQUEST_H__8DB4623A_D730_4D3D_9647_34D893564383__INCLUDED_)
