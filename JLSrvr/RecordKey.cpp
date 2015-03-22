// RecordKey.cpp : implementation file
//

#include "stdafx.h"
#include "jlsrvr.h"
#include "RecordKey.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRecordKey

IMPLEMENT_DYNAMIC(CRecordKey, CRecordset)

CRecordKey::CRecordKey(CDatabase* pdb)
    : CRecordset(pdb)
{
    //{{AFX_FIELD_INIT(CRecordKey)
    m_strKey = _T("");   //卡号
    m_strTime = _T(""); //购买时间
    m_strUse = _T(""); //使用时间
    m_strLeft = _T(""); //剩余时间
    m_nFields = 4;
    //}}AFX_FIELD_INIT
    m_nDefaultType = snapshot;
}


CString CRecordKey::GetDefaultConnect()
{
    return _T("");
}


void CRecordKey::SetAcName(CString& strAcName)
{
    m_strAcName = strAcName;
}


CString CRecordKey::GetDefaultSQL()
{


    CString strFormat =
        _T("select uk_key, jk_build_time, jk_recharge_time,")
        _T(" datediff(ss,CONVERT(CHAR(19), Sysdatetime(), 120),dateadd(hh,b.jk_time_type,b.jk_recharge_time))/60/60 as 剩余时间 ")
        _T(" from Rr_User_Key a,Rr_Key b,Rr_Bind_type c where a.uk_key = b.jk_key and c.bt_id = b.jk_key_type and uk_user = ")
        _T("'%s' order by uk_key");


    CString strSql;
    strSql.Format(strFormat, m_strAcName);
    return strSql;
}

void CRecordKey::DoFieldExchange(CFieldExchange* pFX)
{
    //{{AFX_FIELD_MAP(CRecordKey)
    pFX->SetFieldType(CFieldExchange::outputColumn);
    RFX_Text(pFX, _T("uk_key"), m_strKey);
    RFX_Text(pFX, _T("jk_build_time"), m_strTime);
    RFX_Text(pFX, _T("jk_recharge_time"), m_strUse);
    RFX_Text(pFX, _T("剩余时间"), m_strLeft);
    //}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CRecordKey diagnostics

#ifdef _DEBUG
void CRecordKey::AssertValid() const
{
    CRecordset::AssertValid();
}

void CRecordKey::Dump(CDumpContext& dc) const
{
    CRecordset::Dump(dc);
}
#endif //_DEBUG
