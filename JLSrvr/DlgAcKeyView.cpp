// DlgAcKeyView.cpp : implementation file
//

#include "stdafx.h"
#include "JLsrvr.h"
#include "DlgAcKeyView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgAcKeyView

IMPLEMENT_DYNCREATE(CDlgAcKeyView, CRecordView)

CDlgAcKeyView::CDlgAcKeyView()
	: CRecordView(CDlgAcKeyView::IDD)
{
	//{{AFX_DATA_INIT(CDlgAcKeyView)
	m_pSet = NULL;
	//}}AFX_DATA_INIT
}

CDlgAcKeyView::~CDlgAcKeyView()
{
	if (m_pSet)
		delete m_pSet;
}

void CDlgAcKeyView::DoDataExchange(CDataExchange* pDX)
{
	CRecordView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgAcKeyView)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgAcKeyView, CRecordView)
	//{{AFX_MSG_MAP(CDlgAcKeyView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgAcKeyView diagnostics

#ifdef _DEBUG
void CDlgAcKeyView::AssertValid() const
{
	CRecordView::AssertValid();
}

void CDlgAcKeyView::Dump(CDumpContext& dc) const
{
	CRecordView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDlgAcKeyView message handlers

CRecordset* CDlgAcKeyView::OnGetRecordset()
{
	if (m_pSet != NULL)
		return m_pSet;

	m_pSet = new CRecordKeyLog(NULL);
	m_pSet->Open();

	return m_pSet;
}

CRecordKeyLog* CDlgAcKeyView::GetRecordset()
{
	CRecordKeyLog* pData = (CRecordKeyLog*) OnGetRecordset();
	ASSERT(pData == NULL || pData->IsKindOf(RUNTIME_CLASS(CRecordKeyLog)));
	return pData;
}

void CDlgAcKeyView::OnInitialUpdate()
{
	BeginWaitCursor();
	GetRecordset();
	CRecordView::OnInitialUpdate();
	if (m_pSet->IsOpen())
	{
		CString strTitle = m_pSet->m_pDatabase->GetDatabaseName();
		CString strTable = m_pSet->GetTableName();
		if (!strTable.IsEmpty())
			strTitle += _T(":") + strTable;
		GetDocument()->SetTitle(strTitle);
	}
	EndWaitCursor();
}
