// RecordAc.cpp : implementation file
//

#include "stdafx.h"
#include "jlsrvr.h"
#include "RecordAc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRecordAc

IMPLEMENT_DYNAMIC(CRecordAc, CRecordset)

CRecordAc::CRecordAc(CDatabase* pdb)
    : CRecordset(pdb)
{
    //{{AFX_FIELD_INIT(CRecordAc)
    m_strName = _T("");
    m_strAc = _T("");
    m_strCpuip = _T("");
    m_strHid = _T("");
    m_strBios = _T("");
    m_strMB = _T("");
    m_strRegTime = _T(""); //×¢²áÊ±¼ä
    m_nFields = 7;
    //}}AFX_FIELD_INIT
    m_nDefaultType = snapshot;
}


CString CRecordAc::GetDefaultConnect()
{
    return _T("");
}

void CRecordAc::SetAcName(CString& strAcName)
{
    m_strAcName = strAcName;
}

CString CRecordAc::GetDefaultSQL()
{
    CString strFormat =
        _T("select u_user, u_ac, u_cpuip, u_hd_id, u_bios, u_motherboard, u_time from Rr_User where u_user = '%s'");
    CString strSQL;
    strSQL.Format(strFormat, m_strAcName);
    return strSQL;
}

void CRecordAc::DoFieldExchange(CFieldExchange* pFX)
{
    //{{AFX_FIELD_MAP(CRecordAc)
    pFX->SetFieldType(CFieldExchange::outputColumn);
    RFX_Text(pFX, _T("u_user"), m_strName);
    RFX_Text(pFX, _T("u_ac"), m_strAc);
    RFX_Text(pFX, _T("u_cpuip"), m_strCpuip);
    RFX_Text(pFX, _T("u_hd_id"),m_strHid);
    RFX_Text(pFX, _T("u_bios"), m_strBios);
    RFX_Text(pFX, _T("u_motherboard"),m_strMB);
    RFX_Text(pFX, _T("u_time"), m_strRegTime);

    //}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CRecordAc diagnostics

#ifdef _DEBUG
void CRecordAc::AssertValid() const
{
    CRecordset::AssertValid();
}

void CRecordAc::Dump(CDumpContext& dc) const
{
    CRecordset::Dump(dc);
}
#endif //_DEBUG
