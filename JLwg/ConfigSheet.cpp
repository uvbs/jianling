// ConfigSheet.cpp : implementation file
//

#include "stdafx.h"
#include "JLwg.h"
#include "ConfigSheet.h"
#include "GameConfig.h"
#include "gamedef.h"

#include "..\common\common.h"


#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif



/////////////////////////////////////////////////////////////////////////////
// CConfigSheet

IMPLEMENT_DYNAMIC(CConfigSheet, CPropertySheet)


CConfigSheet::CConfigSheet(CWnd* pWndParent)
    : CPropertySheet(_T("配置文件"), pWndParent)
{
    AddPage(&itempage);
    AddPage(&objpage);
    AddPage(&qhpage);
    AddPage(&partypage);
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

    Default();

    //获取配置
    GameConfig* pConfig = GameConfig::Instance();


    CString szSell;
    CString szCunCang;
    CString szJioayi;
    CString szFenjie;
    CString szQhWuqi;
    CString szQhShipin;
    int i;


    for(i = 0; i < itempage.m_FilterList.GetItemCount(); i++) {
        CString strText = itempage.m_FilterList.GetItemText(i, 0);
        CString strOperator = itempage.m_FilterList.GetItemText(i, 1);

        strText += _T(";");

        if(strOperator == strSell) {
            szSell += strText;
        }
        else if(strOperator == strCunCang) {
            szCunCang += strText;
        }
        else if(strOperator == strFenjie) {
            szFenjie += strText;
        }
        else if(strOperator == strQhWuqi) {
            szQhWuqi += strText;
        }
        else if(strOperator == strQhShipin) {
            szQhShipin += strText;
        }
        else if(strOperator == strJiaoyi) {
            szJioayi += strText;
        }

    }


    pConfig->WriteString(strSell, strItemName, (LPCTSTR)szSell);
    pConfig->WriteString(strJiaoyi, strItemName, (LPCTSTR)szJioayi);
    pConfig->WriteString(strCunCang, strItemName, (LPCTSTR)szCunCang);
    pConfig->WriteString(strQhShipin, strItemName, (LPCTSTR)szQhShipin);
    pConfig->WriteString(strQhWuqi, strItemName, (LPCTSTR)szQhWuqi);
    pConfig->WriteString(strFenjie, strItemName, (LPCTSTR)szFenjie);


    CString strObj_dongtKill;
    CString strObj_mustKill;
    CString strObj_first;
    for(i = 0; i < objpage.m_FilterList.GetItemCount(); i++) {
        CString strName = objpage.m_FilterList.GetItemText(i, 0);
        CString strOp = objpage.m_FilterList.GetItemText(i, 1);

        strName += _T(";");

        if(strOp == strFirstKill) {
            strObj_first += strName;
        }
        else if(strOp == strDontKill) {
            strObj_dongtKill += strName;
        }
        else if(strOp == strAlwaysKill) {
            strObj_mustKill += strName;
        }

    }



    pConfig->WriteString(strCombat, strFirstKill, (LPCTSTR)strObj_first);
    pConfig->WriteString(strCombat, strDontKill, (LPCTSTR)strObj_dongtKill);
    pConfig->WriteString(strCombat, strAlwaysKill, (LPCTSTR)strObj_mustKill);


    CString strQhColor_temp;
    qhpage.GetDlgItemText(IDC_COMBO_ITEMCOLOR, strQhColor_temp);
    pConfig->WriteString(strNormal, strQhColor, (LPCTSTR)strQhColor_temp);

    CString strHeYaoPercent_temp;
    qhpage.GetDlgItemText(IDC_CHIYAOPERCENT, strHeYaoPercent_temp);
    pConfig->WriteString(strCombat, strYaoPecent, (LPCTSTR)strHeYaoPercent_temp);


    qhpage.SetModified(FALSE);
    objpage.SetModified(FALSE);
    objpage.SetModified(FALSE);
}