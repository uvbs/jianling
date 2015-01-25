// ConfigSheet.cpp : implementation file
//

#include "stdafx.h"
#include "jlwg.h"
#include "ConfigItemPage.h"
#include "ConfigObjPage.h"
#include "ConfigQhPage.h"
#include "ConfigSheet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CConfigSheet

IMPLEMENT_DYNAMIC(CConfigSheet, CPropertySheet)


CConfigSheet::CConfigSheet(CWnd* pWndParent)
	:CPropertySheet(_T("≈‰÷√Œƒº˛"), pWndParent)
{
	AddPage(&itempage);
	AddPage(&objpage);
	AddPage(&qhpage);
}

CConfigSheet::~CConfigSheet()
{
}


BEGIN_MESSAGE_MAP(CConfigSheet, CPropertySheet)
	//{{AFX_MSG_MAP(CConfigSheet)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		ON_COMMAND(ID_APPLY_NOW, OnApplyNow)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CConfigSheet message handlers
void CConfigSheet::OnApplyNow()
{

	CString szSell;
	CString szCunCang;
	CString szJioayi;
	CString szFenjie;
	CString szQhWuqi;
	CString szQhShipin;
	int i;
	
	for(i = 0; i < itempage.m_FilterList.GetItemCount(); i++)
	{
		CString strText = itempage.m_FilterList.GetItemText(i, 0);
		CString strOperator= itempage.m_FilterList.GetItemText(i, 1);
		
		strText	+= _T(";");
		
		if(strOperator == strSell){
			szSell += strText;
		}
		else if(strOperator == strCunCang){
			szCunCang += strText;
		}
		else if(strOperator == strFenjie){
			szFenjie += strText;
		}
		else if(strOperator == strQhWuqi){
			szQhWuqi += strText;
		}
		else if(strOperator == strQhShipin){
			szQhShipin += strText;
		}
		else if(strOperator == strJiaoyi){
			szJioayi += strText;
		}
		
	}
				

	WritePrivateProfileString(strSell, strItemName, (LPCTSTR)szSell, gcall.GetConfigPath());
	WritePrivateProfileString(strJiaoyi, strItemName, (LPCTSTR)szJioayi, gcall.GetConfigPath());
	WritePrivateProfileString(strCunCang, strItemName, (LPCTSTR)szCunCang, gcall.GetConfigPath());
	WritePrivateProfileString(strQhShipin, strItemName, (LPCTSTR)szQhShipin, gcall.GetConfigPath());
	WritePrivateProfileString(strQhWuqi, strItemName, (LPCTSTR)szQhWuqi, gcall.GetConfigPath());
	WritePrivateProfileString(strFenjie, strItemName, (LPCTSTR)szFenjie, gcall.GetConfigPath());
				
				

	CString strObj_dongtKill;
	CString strObj_mustKill;
	CString strObj_first;
	for(i = 0; i < objpage.m_FilterList.GetItemCount(); i++)
	{
		CString strName = objpage.m_FilterList.GetItemText(i, 0);
		CString strOp = objpage.m_FilterList.GetItemText(i, 1);

		strName += _T(";");

		if(strOp == strFirst)
		{
			strObj_first += strName;
		}
		else if(strOp == strDontKill)
		{
			strObj_dongtKill += strName;
		}
		else if(strOp == strAlwaysKill)
		{
			strObj_mustKill += strName;
		}
		
	}


	WritePrivateProfileString(strCombat, strFirst, (LPCTSTR)strObj_first, gcall.GetConfigPath());
	WritePrivateProfileString(strCombat, strDontKill, (LPCTSTR)strObj_dongtKill, gcall.GetConfigPath());
	WritePrivateProfileString(strCombat, strAlwaysKill, (LPCTSTR)strObj_mustKill, gcall.GetConfigPath());


    CString strQhColor_temp;
    qhpage.GetDlgItemText(IDC_COMBO_ITEMCOLOR, strQhColor_temp);
	WritePrivateProfileString(strNormal, strQhColor, (LPCTSTR)strQhColor_temp, gcall.GetConfigPath());

	CString strHeYaoPercent_temp;
	qhpage.GetDlgItemText(IDC_CHIYAOPERCENT, strHeYaoPercent_temp);
	WritePrivateProfileString(strCombat, strYaoPecent, (LPCTSTR)strHeYaoPercent_temp, gcall.GetConfigPath());

	qhpage.SetModified(FALSE);
	objpage.SetModified(FALSE);
	objpage.SetModified(FALSE);
}