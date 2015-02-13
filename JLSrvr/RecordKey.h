#if !defined(AFX_RECORDKEY_H__39FCCCF7_E2BB_4E73_BEC6_CDE7F781EFF4__INCLUDED_)
#define AFX_RECORDKEY_H__39FCCCF7_E2BB_4E73_BEC6_CDE7F781EFF4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RecordKey.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRecordKey recordset

class CRecordKey : public CRecordset
{
public:
    CRecordKey(CDatabase* pDatabase = NULL);
    DECLARE_DYNAMIC(CRecordKey)

// Field/Param Data
    //{{AFX_FIELD(CRecordKey, CRecordset)
    CString m_strKey;   //卡号
    CString m_strTime;  //生成时间
    CString m_strUse;  //使用时间
    CString m_strLeft;  //剩余时间
    //}}AFX_FIELD

    CString m_strAcName;
    void SetAcName(CString& strAcName);


// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CRecordKey)
public:
    virtual CString GetDefaultConnect();    // Default connection string
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

#endif // !defined(AFX_RECORDKEY_H__39FCCCF7_E2BB_4E73_BEC6_CDE7F781EFF4__INCLUDED_)
