#if !defined(AFX_DLGACINFO_H__24942F7B_6B47_46AB_B1A4_847A775250D3__INCLUDED_)
#define AFX_DLGACINFO_H__24942F7B_6B47_46AB_B1A4_847A775250D3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgAcInfo.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgAcInfo dialog

class CDlgAcInfo : public CPropertyPage
{
// Construction
public:
    CDlgAcInfo(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
    //{{AFX_DATA(CDlgAcInfo)
    enum { IDD = IDD_DIALOG2base };
    CString m_strName;
    CString m_strAc;
    CString m_strCpuip ;
    CString m_strHid ;
    CString m_strBios;
    CString m_strMB ;
    CString m_strRegTime; //◊¢≤· ±º‰
    //}}AFX_DATA

    // Ù–‘
    CString m_strAcName;

// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CDlgAcInfo)
protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL

// Implementation
protected:

    // Generated message map functions
    //{{AFX_MSG(CDlgAcInfo)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGACINFO_H__24942F7B_6B47_46AB_B1A4_847A775250D3__INCLUDED_)
