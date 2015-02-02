// CDlgModifyBind.cpp : implementation file
//

#include "stdafx.h"
#include "JLkit.h"
#include "Modifybind.h"

#include "..\common\protocol.h"


// CDlgModifyBind dialog

IMPLEMENT_DYNAMIC(CDlgModifyBind, CDialog)
CDlgModifyBind::CDlgModifyBind(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgModifyBind::IDD, pParent)
{
}

CDlgModifyBind::~CDlgModifyBind()
{
}

void CDlgModifyBind::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Text(pDX, IDC_EDITPASSWORD, m_strPw);
	DDX_Text(pDX, IDC_EDITUSERNAME, m_strName);
	DDX_Text(pDX, IDC_OLDBIND, m_strOldbind);
	DDX_Text(pDX, IDC_NEWBIND, m_strNewbind);
}


BEGIN_MESSAGE_MAP(CDlgModifyBind, CDialog)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
END_MESSAGE_MAP()


// CDlgModifyBind message handlers

void CDlgModifyBind::OnBnClickedOk()
{
	/*处理修改绑定的数据发送*/
	
	UpdateData();

	if(m_strName.GetLength() > 10 || m_strPw.GetLength() > 10)
	{
		AfxMessageBox(_T("最长10个字符"));
		UpdateData(0);
		return;
	}

	if(m_strOldbind == _T("0.0.0.0") || m_strNewbind == _T("0.0.0.0") || m_strName.IsEmpty() || 
		m_strPw.IsEmpty())
	{
		AfxMessageBox(_T("不能为空"));
	}
	else
	{
		/*将注册数据打包*/
		MODIFYBIND_BUF modifybuf;

		modifybuf.fun = fun_mbind;

		memcpy(modifybuf.new_bind, (LPCTSTR)m_strNewbind, MAXLEN);
		memcpy(modifybuf.old_bind, (LPCTSTR)m_strOldbind, MAXLEN);
		memcpy(modifybuf.name, (LPCTSTR)m_strName, MAXLEN);
		memcpy(modifybuf.pw, (LPCTSTR)m_strPw, MAXLEN);


// 		g_sock = socket(AF_INET, SOCK_STREAM, 0);
// 		if(g_sock == INVALID_SOCKET)
// 		{
// 			AfxMessageBox(_T("创建 Sockets 失败"));
// 			return;
// 		}
		
		/*发起一个连接*/
// 		int result = connect(g_sock, (sockaddr *)&g_serveraddr, sizeof(g_serveraddr));
// 		if(result == SOCKET_ERROR)
// 		{
// 			AfxMessageBox(_T("无法连接到服务器"));
// 			UpdateData(0);
// 			return;
// 		}

		/*
		发送到服务器验证登录
		*/
// 		result = pSend(g_sock, (char *)&modifybuf, sizeof(modifybuf), 0);
// 		if(result != SOCKET_ERROR)
// 		{
// 			RET_BUF retbuf;
// 			result = pRecv(g_sock, (char *)&retbuf, sizeof(retbuf), 0);
// 			if(result != SOCKET_ERROR)
// 			{
// 				if(retbuf.fun == fun_mbind)
// 				{
// 					if(retbuf.result == result_ok)
// 					{
// 						AfxMessageBox(_T("修改成功"));
// 						CDialog::OnOK();
// 					}
// 					else
// 					{
// 						AfxMessageBox(_T("修改失败"));
// 					}
// 				}
// 			}
// 			else
// 			{
// 				if(result == WSAETIMEDOUT)
// 				{
// 					AfxMessageBox(_T("网络超时"));
// 				}
// 				else
// 					AfxMessageBox(_T("网络错误"));
// 			}
// 		}
// 		else
// 		{
// 			AfxMessageBox(_T("发送失败"));
// 		}
 	}
	

//	closesocket(g_sock);
	UpdateData(0);
}
