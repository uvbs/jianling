#if !defined(AFX_RECORDKEYLOG_H__44A6BD3F_CBBD_4C05_897F_7278B3D07FAC__INCLUDED_)
#define AFX_RECORDKEYLOG_H__44A6BD3F_CBBD_4C05_897F_7278B3D07FAC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RecordKeyLog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRecordKeyLog recordset

class CRecordKeyLog : public CRecordset
{
public:
    CRecordKeyLog(CDatabase* pDatabase = NULL);
    DECLARE_DYNAMIC(CRecordKeyLog)

// Field/Param Data
    //{{AFX_FIELD(CRecordKeyLog, CRecordset)
    CString m_strKey;
    CString m_strTime;
    CString m_strIp;
    //}}AFX_FIELD


    // Ù–‘
    CString m_strAcName;
    void SetAcName(CString& strAcName);


// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CRecordKeyLog)
public:
    virtual CString GetDefaultSQL();    // Default SQL for Recordset
    virtual void DoFieldExchange(CFieldExchange* pFX);  // RFX support
    //}}AFX_VIRTUAL

// Implementation
#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump(CDumpContext& dc) const;
#endif
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RECORDKEYLOG_H__44A6BD3F_CBBD_4C05_897F_7278B3D07FAC__INCLUDED_)
