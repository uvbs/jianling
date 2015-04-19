// DbMngr.cpp: implementation of the CDbMngr class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "JLSrvr.h"
#include "DbMngr.h"
#include "db_sql.h"


#ifdef _DEBUG
    #define new DEBUG_NEW
#endif


CDbMngr::CDbMngr()
{
}

CDbMngr::~CDbMngr()
{

}

//0 失败
//1 成功
//2 没到解绑时间
int CDbMngr::Unbindkey(TCHAR* pszName, TCHAR* pszKey, sockaddr_in* pSocketAddr)
{
    TCHAR szSql[BUFSIZ] = {0};


    CString strSql;
    strSql.Format(db_sql_unbind, pszName, pszKey, _T("0"), _T("0"), _T("0"), _T("0"), _T("0"), _T("0"), _T("0"));


    try
    {
        CRecordset record(this);
        if(record.Open(AFX_DB_USE_DEFAULT_TYPE, strSql) == FALSE)
        {
            return 0;
        }

        CString strRet;
        record.GetFieldValue(_T("返回值"), strRet);

        return _ttoi((LPCTSTR)strRet);
    }
    catch(CDBException* pEx)
    {
        pEx->Delete();
    }

    return 0;
}


BOOL CDbMngr::NewRegist(TCHAR szUserName[], TCHAR szPassword[], TCHAR szBindIP[], TCHAR szMac[], TCHAR szClientIp[])
{

    CString strSql;
    strSql.Format(db_sql_register, szUserName, szPassword, szClientIp, szMac);

    try
    {
        ExecuteSQL(strSql);
        return TRUE;
    }
    catch(CDBException* pEx)
    {
        pEx->Delete();
    }

    return FALSE;

}


//查询充值卡是否可用
//返回值 0 = 可以使用
//1=已使用 jk_key_type=1代表该充值卡只能充值韩服剑灵
int CDbMngr::Bindkey(TCHAR *pszName, TCHAR *pszKey, const TCHAR szIp[])
{

    CDBVariant ret;
    CString strSql;
    strSql.Format(db_sql_bindkey, pszName, pszKey, szIp, _T("ac"), _T("0"), _T("0"), _T("0"), _T("0"), _T("0"));

    try
    {
        CRecordset record(this);
        if(record.Open(AFX_DB_USE_DEFAULT_TYPE, (LPCTSTR)strSql) == FALSE)
        {
            return false;
        }

        CString strRet;
        record.GetFieldValue(_T("返回值"), ret);

        return ret.m_iVal;

    }
    catch(CDBException* pEx)
    {
        pEx->Delete();
    }

    return 0;
}


BOOL CDbMngr::Querykey(std::vector<QUERYKEY_SUCCESS>& vecKeyInfo, TCHAR szUserName[], TCHAR szPassWord[])
{

    CString strSql;
    strSql.Format(db_sql_querykey, szUserName);


    BOOL bRet = FALSE;
    try
    {

        CRecordset record(this);
        if(record.Open(AFX_DB_USE_DEFAULT_TYPE, (LPCTSTR)strSql) == FALSE)
        {
            THROW(_T("没能打开记录集"));
        }

        CString strKey;
        CString strBuildTime;
        CString strKeyType;
        CString strRemainTime;


        while(record.IsEOF() == FALSE)
        {
            QUERYKEY_SUCCESS QueryRetInfo;
            ZeroMemory(&QueryRetInfo, sizeof(QUERYKEY_SUCCESS));

            record.GetFieldValue(_T("卡号"), strKey);
            record.GetFieldValue(_T("充值时间"), strBuildTime);
            record.GetFieldValue(_T("充值卡类型"), strKeyType);
            record.GetFieldValue(_T("剩余时间"), strRemainTime);

            _tcsncpy(QueryRetInfo.type, (LPCTSTR)strKeyType, strKeyType.GetLength());
            QueryRetInfo.remaintime = _ttoi((LPCTSTR)strRemainTime);

            QueryRetInfo.buildtime = 22;
            _tcsncpy(QueryRetInfo.key, (LPCTSTR)strKey, strKey.GetLength());

            vecKeyInfo.push_back(QueryRetInfo);

            record.MoveNext();
        }

        bRet = TRUE;
    }
    catch(CDBException* pEx)
    {
        pEx->Delete();
    }

    return bRet;
}

int CDbMngr::CheckUser(TCHAR szUsername[], TCHAR szPassw[])
{
    CString strSql;
    strSql.Format(db_sql_checkuser, szUsername,
                  _T(""), _T(""), _T(""), _T(""), _T(""), _T(""), _T(""), _T(""), _T(""), _T(""));


    CDBVariant varValue;
    try
    {
        CRecordset record(this);
        if(record.Open(AFX_DB_USE_DEFAULT_TYPE, (LPCTSTR)strSql) == false)
        {
            return 0;
        }
        else
        {
            record.GetFieldValue(_T("返回值"), varValue);
        }

    }
    catch(CDBException* pEx)
    {
        pEx->Delete();
    }

    return varValue.m_lVal;
}



//插入的key, key的时间(小时), key的类型, 1 = 剑灵
BOOL CDbMngr::AddKey(CString& strKey, UINT nTimes, int type)
{

    TCHAR szKey[9] = {0};
    static TCHAR g_szAlpha[] = _T("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890");

    /* Seed the random-number generator with current time so that
    * the numbers will be different every time we run.
    */

    //48~57
    //65 90
    //97~122
    /* Display 8 numbers. */
    while(1)
    {
        ZeroMemory(szKey, sizeof(szKey));
        for(int i = 0; i < 8; i++)
        {
            szKey[i] = g_szAlpha[rand() % 63];
        }

        if(_tcslen(szKey) == 8)
        {
            break;
        }
    }


    CString strSql;
    strSql.Format(db_sql_addkey, szKey, nTimes, type);


    TRY
    {
        ExecuteSQL(strSql);
        strKey = szKey;
    }
    CATCH(CDBException, e)
    {
        // The error code is in e->m_nRetCode
        return FALSE;
    }
    END_CATCH


    return TRUE;
}


BOOL CDbMngr::Init()
{
    BOOL bRet;

    try
    {
        if(!IsOpen())
        {
            bRet = OpenEx(NULL, CDatabase::openReadOnly);
        }
        else
        {
            bRet = TRUE;
        }
    }
    catch(CDBException* pEx)
    {
        AfxMessageBox(pEx->m_strError);
        pEx->Delete();
    }
    return bRet;
}

