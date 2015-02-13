#if !defined(AFX_RECORDAC_H__12BC8C51_521C_43B1_87D4_2C571705FEB3__INCLUDED_)
#define AFX_RECORDAC_H__12BC8C51_521C_43B1_87D4_2C571705FEB3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RecordAc.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRecordAc recordset

class CRecordAc : public CRecordset
{
public:
	CRecordAc(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CRecordAc)

// Field/Param Data
	//{{AFX_FIELD(CRecordAc, CRecordset)
    CString m_strName;
    CString m_strAc;
    CString m_strCpuip ;
    CString m_strHid ;
    CString m_strBios;
    CString m_strMB ;
    CString m_strRegTime; //×¢²áÊ±¼ä
	//}}AFX_FIELD




    CString m_strAcName;
    void SetAcName(CString& strAcName);


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRecordAc)
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

#endif // !defined(AFX_RECORDAC_H__12BC8C51_521C_43B1_87D4_2C571705FEB3__INCLUDED_)
