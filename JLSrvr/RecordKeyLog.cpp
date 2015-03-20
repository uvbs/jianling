// RecordKeyLog.cpp : implementation file
//

#include "stdafx.h"
#include "jlsrvr.h"
#include "RecordKeyLog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRecordKeyLog

IMPLEMENT_DYNAMIC(CRecordKeyLog, CRecordset)

CRecordKeyLog::CRecordKeyLog(CDatabase* pdb)
    : CRecordset(pdb)
{
    //{{AFX_FIELD_INIT(CRecordKeyLog)
    m_nFields = 3;
    m_strKey = _T("");
    m_strIp = _T("");
    m_strTime = _T("");
    //}}AFX_FIELD_INIT
    m_nDefaultType = snapshot;

}

void CRecordKeyLog::SetAcName(CString& strAcName)
{
    m_strAcName = strAcName;
}


CString CRecordKeyLog::GetDefaultSQL()
{
    CString strFormat =
        _T("select uk_log_key, uk_log_time, uk_log_ip from Rr_User_Key_log where uk_log_user = '%s'");


    CString strSql;
    strSql.Format(strFormat, m_strAcName);
    TRACE0(strSql);
    return strSql;
}


void CRecordKeyLog::DoFieldExchange(CFieldExchange* pFX)
{
    //{{AFX_FIELD_MAP(CRecordKeyLog)
    pFX->SetFieldType(CFieldExchange::outputColumn);
    RFX_Text(pFX, "uk_log_key", m_strKey);
    RFX_Text(pFX, "uk_log_time", m_strTime);
    RFX_Text(pFX, "uk_log_ip", m_strIp);
    //}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CRecordKeyLog diagnostics

#ifdef _DEBUG
void CRecordKeyLog::AssertValid() const
{
    CRecordset::AssertValid();
}

void CRecordKeyLog::Dump(CDumpContext& dc) const
{
    CRecordset::Dump(dc);
}
#endif //_DEBUG
