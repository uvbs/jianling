// RequestSocket.cpp : implementation file
//

#include "stdafx.h"
#include "JLSrvr.h"
#include "RequestSocket.h"
#include "Request.h"
#include "JLSrvrDoc.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRequestSocket

CRequestSocket::CRequestSocket(CJLSrvrDoc* pDoc)
{
    m_pDoc = pDoc;
	m_pRequest = NULL;
}

CRequestSocket::~CRequestSocket()
{
	if ( m_pRequest )
	{
		// release our hold on the request object....
		delete m_pRequest;
	}
}


// Do not edit the following lines, which are needed by ClassWizard.
#if 0
BEGIN_MESSAGE_MAP(CRequestSocket, CAsyncSocket)
	//{{AFX_MSG_MAP(CRequestSocket)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif	// 0

/////////////////////////////////////////////////////////////////////////////
// CRequestSocket member functions

// void CRequestSocket::OnSend(int nErrorCode) 
// {
// 
// 	int nBytes = Send(m_buf.GetData(), m_buf.GetSize());
// 	if (nBytes == SOCKET_ERROR)
// 	{
// 		if(GetLastError() != WSAEWOULDBLOCK )
// 		{
// 			ShutDown(both);
// 		}
// 		else
// 			AsyncSelect(FD_WRITE | FD_CLOSE);
// 	}
// 	else if(nBytes < m_buf.GetSize())
// 	{
// 		// still got some left....
// 		m_buf.RemoveAt(0, nBytes);
// 		
// 		// set up for next write....
// 		AsyncSelect( FD_WRITE | FD_CLOSE );
// 	}
// 	
// }



//查询充值卡是否可用
//返回值 0 = 可以使用  
//1=已使用 jk_key_type=1代表该充值卡只能充值韩服剑灵
BOOL CRequestSocket::Bindkey(KEY_BUF *pKeyBuf)
{
	
	CString strSql;
	
	strSql.Format(_T("{call Bind_key('%s','%s','%s','%s','%s','%s','%s','%s','%s')}"),
		pKeyBuf->name, pKeyBuf->key, inet_ntoa(m_soaddr.sin_addr), _T("ac"), 
		pKeyBuf->pcdata.cpu, pKeyBuf->pcdata.mac, pKeyBuf->pcdata.hid, pKeyBuf->pcdata.bios, pKeyBuf->pcdata.mbid);

	TRY
	{
		
		
		CRecordset record(m_pDoc->m_pDB);
		if(record.Open(AFX_DB_USE_DEFAULT_TYPE, (LPCTSTR)strSql) == FALSE)
		{
			return result_bind_fail;
		}
		
		CString strRet;
		record.GetFieldValue(_T("返回值"), strRet);
		
		return _ttoi((LPCTSTR)strRet);
		
	}
	CATCH(CDBException, e)
	{
		TRACE1("异常: %s", (LPCTSTR)e->m_strError);
	}
	END_CATCH
	
	return false;
	
	
}


BOOL CRequestSocket::Querykey(std::vector<QUERYKEY_RET_BUF> &vecKeyInfo, TCHAR szUserName[], TCHAR szPassWord[])
{
	
	CString strSql;
	strSql.Format(
		_T("select uk_key as 卡号, jk_recharge_time as 充值时间 ,bt_type_explanation as 充值卡类型 ,")
		_T(" datediff(ss,CONVERT(CHAR(19), Sysdatetime(), 120),dateadd(hh,b.jk_time_type,b.jk_recharge_time))/60/60 as 剩余时间 ")
		_T(" from Rr_User_Key a,Rr_Key b,Rr_Bind_type c where a.uk_key = b.jk_key and c.bt_id = b.jk_key_type and uk_user = ")
		_T("'%s' and bt_type_explanation = '韩服剑灵'  order by uk_key"),
		szUserName);
	
	
	BOOL bRet = FALSE;
	try
	{
		
		CRecordset record(m_pDoc->m_pDB);
		if(record.Open(AFX_DB_USE_DEFAULT_TYPE, (LPCTSTR)strSql) == FALSE){
			THROW(_T("没能打开记录集"));
		}
		
		CString strKey;
		CString strBuildTime;
		CString strKeyType;
		CString strRemainTime;
		
		DWORD count = 0;
		while(record.IsEOF() == FALSE){
			record.MoveNext();
			count++;
		}
		
		
		record.MoveFirst();
		while(record.IsEOF() == FALSE){
			QUERYKEY_RET_BUF QueryRetInfo;
			ZeroMemory(&QueryRetInfo, sizeof(QUERYKEY_RET_BUF));

			record.GetFieldValue(_T("卡号"), strKey);
			record.GetFieldValue(_T("充值时间"), strBuildTime);
			record.GetFieldValue(_T("充值卡类型"), strKeyType);
			record.GetFieldValue(_T("剩余时间"), strRemainTime);
	
			QueryRetInfo.count = (UCHAR)--count;
			_tcsncpy(QueryRetInfo.type, (LPCTSTR)strKeyType, strKeyType.GetLength());
			QueryRetInfo.remaintime = _ttoi((LPCTSTR)strRemainTime);
			QueryRetInfo.fun = fun_querykey;
			QueryRetInfo.result = result_ok;
			
			_tcsncpy(QueryRetInfo.buildtime, (LPCTSTR)strBuildTime, strBuildTime.GetLength());
			_tcsncpy(QueryRetInfo.key, (LPCTSTR)strKey, strKey.GetLength());
			
			vecKeyInfo.push_back(QueryRetInfo);
			
			record.MoveNext();
		}
		
		bRet = TRUE;
	}
	catch(CDBException *pEx){
		TRACE1("查询key异常: %s", (LPCTSTR)pEx->m_strError);
	}
	catch(TCHAR *pText){
		TRACE1("查询key异常: %s", pText);
	}
	catch(...){
		TRACE(_T("查询key异常: unknow"));
	}

	
	return bRet;
}

int CRequestSocket::GetPwRight(TCHAR szUsername[], TCHAR szPassw[])
{
	CString strSql;
	strSql.Format(_T("select u_psw as 用户密码 from Rr_User where u_user = '%s' and u_game_id = 1"),
		szUsername);

	
	try
	{
		CRecordset record(m_pDoc->m_pDB);
		record.Open(AFX_DB_USE_DEFAULT_TYPE, (LPCTSTR)strSql);
		CString strPassword;

		
		//没有数据
		if(record.IsBOF()){
			strPassword.Empty();
			return result_login_notuser;
		}
		else{
			record.GetFieldValue(_T("用户密码"), strPassword);
			if(strPassword == szPassw){
				return result_login_ok;
			}
            else{
                return result_login_pwerror;
            }
		}

	}
	catch(CDBException *pEx){
		TRACE1("异常: %s", (LPCTSTR)pEx->m_strError);
	}

	return result_login_pwerror;

}

//处理请求同时填充请求相关信息
BOOL CRequestSocket::ProcessRequest(BYTE* pRequestBuf)
{
	int fun = ((LOGIN_BUF *)pRequestBuf)->fun;

	//记录这个请求的相关信息
	CString strPort;
	strPort.Format(_T("%s:%d"), m_pRequest->strIp, m_soaddr.sin_port);

    m_pRequest->m_reqNums += 1;
	m_pRequest->strTime = CTime::GetCurrentTime().Format(_T("%y/%m/%d %H:%M:%S"));
	m_pRequest->strIp = strPort;

	//取请求类型分别处理
	switch(fun)
	{

	case fun_bugrep:
		{
			BUG_BUF* LoginBuf = (BUG_BUF *)pRequestBuf;
		    m_pRequest->strType = _T("bug报告");
			m_pRequest->strOther = LoginBuf->szBug;
			m_buf.RemoveAll();		//不发送回复
		}
		break;

	case fun_login:
		{
			LOGIN_BUF* pLoginBuf = (LOGIN_BUF *)pRequestBuf;
			int nResult = GetPwRight(pLoginBuf->name, pLoginBuf->pw);

			m_pRequest->strUserName = pLoginBuf->name;
			m_pRequest->strType = _T("登录");
			m_pRequest->strOther = pLoginBuf->pw;

			if(nResult == result_login_ok){
				
                //检测是否已经登录
                if(m_pDoc->isLogined(pLoginBuf->name)){
                    m_pRequest->strResult = _T("已经登陆");
                    nResult = result_login_logined;
                }
                else{
                    m_pRequest->strResult = _T("验证完成");
                    memcpy(m_szName, pLoginBuf->name, MAXLEN*sizeof(TCHAR));
                    memcpy(m_szPw, pLoginBuf->pw, MAXLEN*sizeof(TCHAR));
                }
			}
			else if(nResult == result_login_pwerror){
				m_pRequest->strResult = _T("密码错误");
			}
            else if(nResult == result_login_notuser){
                m_pRequest->strResult = _T("用户不存在");
            }


            RET_BUF retbuf;
            retbuf.fun = fun;
            retbuf.result = nResult;
			m_buf.SetSize(sizeof(RET_BUF));
			memcpy(m_buf.GetData(), &retbuf, m_buf.GetSize());
			
		}
		break;

	case fun_querykey:
		{

			LOGIN_BUF* pLoginBuf = (LOGIN_BUF *)pRequestBuf;
			std::vector<QUERYKEY_RET_BUF> querybuf;
			m_pRequest->strType = _T("查询卡号");
            m_pRequest->strOther = _T("");
			if(Querykey(querybuf, pLoginBuf->name, pLoginBuf->pw)){
				m_pRequest->strResult = _T("完成");

				m_buf.SetSize(sizeof(QUERYKEY_RET_BUF) * querybuf.size());
				for(int i = 0; i < querybuf.size(); i++){
					memcpy((m_buf.GetData() + sizeof(QUERYKEY_RET_BUF) * i), &querybuf[i], sizeof(QUERYKEY_RET_BUF));
				}

				
			}
			else{
				m_pRequest->strResult = _T("失败");

				RET_BUF retbuf;
				retbuf.fun = fun_querykey;
				retbuf.result = result_fail;
				m_buf.SetSize(sizeof(RET_BUF));
				
			}
		}
		break;

	case fun_unbindkey:
        {
			KEY_BUF* keybuf = (KEY_BUF *)pRequestBuf;

			m_pRequest->strType = _T("解绑");
			m_pRequest->strOther = keybuf->key;

			int nResult = Unbindkey(keybuf, &m_soaddr);

			RET_BUF retbuf;
			retbuf.fun = fun_unbindkey;
			retbuf.result = nResult;

			switch(nResult)
			{
			case result_unbind_ok:
				m_pRequest->strResult = _T("完成");
				break;
			case result_unbind_fail:
				m_pRequest->strResult = _T("失败");
				break;
			case result_unbind_errtime:
				m_pRequest->strResult = _T("24限制");
				break;
			case result_unbind_notuser:
				m_pRequest->strResult = _T("不存在帐号");
				break;
			default:
				m_pRequest->strResult = _T("未知错误");
			}
		}
		break;

		
	case fun_bindkey:
		{
			KEY_BUF* keybuf = (KEY_BUF *)pRequestBuf;
			
			m_pRequest->strType = _T("绑卡");
			m_pRequest->strOther = keybuf->key;
			

			int nResult = Bindkey(keybuf);
			
			RET_BUF retbuf;
			retbuf.fun = fun_bindkey;
			retbuf.result = nResult;
			
			switch(nResult)
			{
			case result_bind_ok:
				m_pRequest->strResult = _T("完成");
				break;
			case result_bind_fail:
				m_pRequest->strResult = _T("失败");
				break;
			case result_bind_errkey:
				m_pRequest->strResult = _T("卡号错误");
				break;
			case result_bind_used:
				m_pRequest->strResult = _T("已使用");
				break;
			default:
				m_pRequest->strResult = _T("未知错误");
			}

			m_buf.SetSize(sizeof(RET_BUF));
			memcpy(m_buf.GetData(), &retbuf, m_buf.GetSize());
		}
		break;


	default:
		{
			m_pRequest->strType = _T("其他");
		}
		break;
		
	}


	return TRUE;
}

BOOL CRequestSocket::ModifyBind(TCHAR szUserName[], TCHAR szPassword[], TCHAR szOldBind[], TCHAR szNewBind[])
{
	
	CString strSql;
	strSql.Format(_T("select top 1 br_bind_result as 旧绑定 from Rr_Bind_Rs where br_user = '%s' order by br_bind_result desc"),
		szUserName);	
	
	try
	{
		CRecordset record(m_pDoc->m_pDB);
		record.Open(AFX_DB_USE_DEFAULT_TYPE, strSql);
		CString strOldbind;
		
		
		record.GetFieldValue(_T("旧绑定"), strOldbind);
		if(strOldbind == szOldBind){
			//旧绑定和用户提交的一致"
			//开始判断上次更改日期
			
			CString strlastTime;
			strlastTime.Format(
                _T( "select br_id as 用户ID from Rr_Bind_Rs where br_user = '%s' ")
				_T( "and br_bind_result = '%s' and datediff(mi,br_bind_time,CONVERT(CHAR(19), ")
				_T( "Sysdatetime(), 20))>1440 order by br_bind_time desc"),
				szUserName, szOldBind);
			
			record.Close();
			record.Open(AFX_DB_USE_DEFAULT_TYPE, strlastTime);
			
			//CString strValue;
			//record.GetFieldValue("br_id", strValue);
			//if(strValue == "")
			if(record.IsBOF())
			{
				//空的
				return FALSE;
			}
			else
			{
				//可以更改
				CString strModify;
				strModify.Format(
                    _T("insert into Rr_Bind_Rs(br_user,br_bind_result,br_bind_time)")
					_T("values('%s','%s',CONVERT(CHAR(19), Sysdatetime(), 20))"),
					szUserName, szNewBind);
				
				m_pDoc->m_pDB->ExecuteSQL(strModify);
				
			}
			
			record.Close();
			return TRUE;
		}
		else
		{
			return FALSE;
		}
		
	}
	catch(CDBException *pEx)
	{
		TRACE1("异常: %s", (LPCTSTR)pEx->m_strError);
	}
	
	
	return false;
}
//0 失败
//1 成功
//2 没到解绑时间
int CRequestSocket::Unbindkey(KEY_BUF *pKeyBuf,  sockaddr_in *pSocketAddr)
{
	TCHAR szSql[BUFSIZ] = {0};
	
	
	CString strSql;
	strSql.Format(_T(
		"{call UnBind('%s','%s','%s','%s','%s','%s','%s','%s','%s')}"),
		pKeyBuf->name, pKeyBuf->key, inet_ntoa(pSocketAddr->sin_addr), _T("ac"), 
		pKeyBuf->pcdata.cpu, pKeyBuf->pcdata.mac, pKeyBuf->pcdata.hid, pKeyBuf->pcdata.bios, pKeyBuf->pcdata.mbid);
	
	
	try{
		CRecordset record(m_pDoc->m_pDB);
		if(record.Open(AFX_DB_USE_DEFAULT_TYPE, strSql) == FALSE)
		{
			return 0;
		}
		
		CString strRet;
		record.GetFieldValue(_T("返回值"), strRet);
		
		return _ttoi((LPCTSTR)strRet);
	}
	catch(CDBException *pEx)
	{
		TRACE1("异常, %s", (LPCTSTR)pEx->m_strError);	
	}
	
	return 0;
}
BOOL CRequestSocket::NewRegist(TCHAR szUserName[], TCHAR szPassword[], TCHAR szBindIP[], TCHAR szMac[], TCHAR szClientIp[])
{
	
	TCHAR szSql[BUFSIZ] = {0};
	TCHAR szSql_bind[BUFSIZ] = {0};
	
	CString strSql;
	strSql.Format(
		_T("insert into Rr_User(u_user,u_psw,u_ip,u_ac,u_cpuip,u_mac,u_hd_id,")
		_T("u_bios,u_motherboard,u_time,u_game_id,u_bind_type)values('%s','%s',")
		_T("'%s','特征码','CPUID','%s','硬盘ID','BIOS信息','主板信息',CONVERT(CHAR(19),")
		_T("Sysdatetime(), 20),1,'band_ip')"),
		szUserName, szPassword, szClientIp, szMac);
	
	CString strBind;
	strBind.Format(
		_T("insert into Rr_Bind_Rs(br_user,br_bind_result,br_bind_time)values('%s',")
		_T("'%s',CONVERT(CHAR(19), Sysdatetime(), 20))"),
		szUserName, szBindIP);
	
	try
	{
		
		m_pDoc->m_pDB->ExecuteSQL(szSql);
		m_pDoc->m_pDB->ExecuteSQL(szSql_bind);
		return TRUE;
		
	}
	catch(CDBException *pEx)
	{
		TRACE1("异常: %s", (LPCTSTR)pEx->m_strError);
	}
	
	return FALSE;
	
}

void CRequestSocket::OnReceive(int nErrorCode) 
{
    
    m_buf.SetSize(1024);
    int nBytes = Receive(m_buf.GetData(), m_buf.GetSize());
    if(nBytes != SOCKET_ERROR)
    {
        if(nBytes == 0)
            m_pDoc->ClientClose(this);


        ProcessRequest(m_buf.GetData());
        m_pDoc->DocHit(HINT_REQUEST, m_pRequest);
        
        //AsyncSelect(FD_WRITE | FD_CLOSE);
        if(m_buf.GetSize() != 0){
            Send(m_buf.GetData(), m_buf.GetSize());
        }
        
    }
    else{
        nBytes = GetLastError();
    }
    
}

int CRequestSocket::Send(const void* lpBuf, int nBufLen, int nFlags) 
{
	//备份这片数据
    BYTE *pBack = new BYTE[nBufLen];
    memcpy(pBack, lpBuf, nBufLen);
    
    //对数据加密
    for(int i = 0; i < nBufLen; i++){
        BYTE q = (BYTE)i%3;
        pBack[i] ^= 0x93;
        pBack[i] += q;
    }
    
    int nBytes = CAsyncSocket::Send(pBack, nBufLen, nFlags);


    delete []pBack;
    return nBytes;
}

int CRequestSocket::Receive(void* lpBuf, int nBufLen, int nFlags) 
{

    int result = CAsyncSocket::Receive(lpBuf, nBufLen, nFlags);
    if(result == SOCKET_ERROR)
        return result;
    
    
    //对数据解密
    BYTE* temp = (BYTE *)lpBuf;
    for(int i = 0; i < nBufLen; i++)
    {
        BYTE q = (BYTE)i%3;
        temp[i] -= q;
        temp[i] ^= 0x93;
    }
    
    return result;
    
}

void CRequestSocket::OnClose(int nErrorCode) 
{
    if(nErrorCode != 0)
        return;

    m_pRequest->strType = _T("离线");
	m_pRequest->strTime = CTime::GetCurrentTime().Format(_T("%y/%m/%d %H:%M:%S"));
    m_pRequest->strOther = _T("");
    m_pRequest->strResult = _T("完成");
    m_pDoc->ClientClose(this);
}

void CRequestSocket::InitAccept(SOCKADDR_IN &cltsock)
{
    
    if(m_pRequest == NULL)
        m_pRequest = new CRequest;
    

    if(m_pRequest)
    {
        m_soaddr = cltsock;
        m_pRequest->m_reqNums = 0;
        m_pRequest->strUserName = _T("");
        m_pRequest->strType = _T("连接");
        m_pRequest->strTime = CTime::GetCurrentTime().Format(_T("%y/%m/%d %H:%M:%S"));
        m_pRequest->strOther = _T("");
        m_pRequest->strResult = _T("完成");
        m_pRequest->strIp = inet_ntoa(m_soaddr.sin_addr);
        m_pDoc->DocHit(HINT_ACEEPT, m_pRequest);
    }
    else
        ShutDown(both);
    
}