// CRegistDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Jlkit.h"
#include "RegistDlg.h"

#include "..\common\protocol.h"
#include "..\common\Userinfo.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif



CRegistDlg::CRegistDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CRegistDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CRegistDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CRegistDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRegistDlg)
	DDX_Text(pDX, IDC_EDITPASSWORD, m_strPw);
	DDX_Text(pDX, IDC_EDITUSERNAME, m_strName);
	DDX_Text(pDX, IDC_IPADDRESS, m_strIp);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CRegistDlg, CDialog)
	//{{AFX_MSG_MAP(CRegistDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
	ON_WM_TIMER()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRegistDlg message handlers

void CRegistDlg::OnOK()
{
	// TODO: Add your specialized code here and/or call the base class
	UpdateData();
	
	if(m_strName.GetLength() > 10 || m_strPw.GetLength() > 10)
	{
		AfxMessageBox(_T("�10���ַ�"));
		UpdateData(0);
		return;
	}
	
// 	if(m_strIp == _T("0.0.0.0") || m_strName.IsEmpty() || m_strPw.IsEmpty())
// 	{
// 		AfxMessageBox(_T("����Ϊ��"));
// 	}
// 	else
// 	{
// 		//��ע�����ݴ��
// 		REGIST_BUF registbuf;
// 		registbuf.fun = fun_regist;
// 		
// 		
		
		
// 		CCUserInfo pcinfo;
// 		pcinfo.GetInfo(Pcinfo::mac);
// 		pcinfo.GetInfo(Pcinfo::cpuid);
		
	
// 		memcpy(registbuf.ip, (LPCTSTR)m_strIp, MAXLEN);
// 		memcpy(registbuf.name, (LPCTSTR)m_strName, MAXLEN);
//		memcpy(registbuf.password, (LPCTSTR)m_strPw, MAXLEN);
//		memcpy(&registbuf.pcdata, &pcinfo.stPcData, sizeof(PCDATA));
		
//		g_sock = socket(AF_INET, SOCK_STREAM, 0);
//		if(g_sock == INVALID_SOCKET)
		{
			AfxMessageBox(_T("���� Sockets ʧ��"));
			return;
		}

		/*����һ������*/
// 		int result = connect(g_sock, (sockaddr *)&g_serveraddr, sizeof(g_serveraddr));
// 		if(result == SOCKET_ERROR)
// 		{
// 			AfxMessageBox(_T("�޷����ӵ�������"));
// 			UpdateData(0);
// 			return;
// 		}
		
		/*
		���͵���������֤��¼
		*/
// 		result = pSend(g_sock, (char *)&registbuf, sizeof(registbuf), 0);
// 		if(result != SOCKET_ERROR)
// 		{
// 			RET_BUF retbuf;
// 			result = pRecv(g_sock, (char *)&retbuf, sizeof(retbuf), 0);
// 			if(result != SOCKET_ERROR)
// 			{
// 				if(retbuf.fun == fun_regist)
// 				{
// 					if(retbuf.result == result_ok)
// 					{
// 						AfxMessageBox(_T("����ɹ�"));
// 						CDialog::OnOK();
// 					}
// 					else
// 					{
// 						AfxMessageBox(_T("����ʧ��"));
// 					}
// 				}
// 			}
// 			else
// 			{
// 				if(result == WSAETIMEDOUT)
// 				{
// 					AfxMessageBox(_T("��¼��ʱ"));
// 				}
// 				else
// 					AfxMessageBox(_T("�������"));
// 			}
// 		}
// 		else
// 		{
// 			AfxMessageBox(_T("����ʧ��"));
// 		}
// 	}

// 	closesocket(g_sock);
// 	UpdateData(0);
	
}

BOOL CRegistDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CRegistDlg::OnTimer(UINT nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	OnOK();

	CDialog::OnTimer(nIDEvent);
}
