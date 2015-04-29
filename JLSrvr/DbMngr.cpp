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

//0 ʧ��
//1 �ɹ�
//2 û�����ʱ��
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
        record.GetFieldValue(_T("����ֵ"), strRet);

        return _ttoi((LPCTSTR)strRet);
    }
    catch(CDBException* pEx)
    {
        pEx->Delete();
    }

    return 0;
}


BOOL CDbMngr::NewRegist(TCHAR szName[], TCHAR szPw[])
{

    CString strSql;
    strSql.Format(db_sql_register, szName, szPw, _T(""), _T(""), _T(""), _T(""), _T(""), _T(""), _T(""));

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


//��ѯ��ֵ���Ƿ����
//����ֵ 0 = ����ʹ��
//1=��ʹ�� jk_key_type=1����ó�ֵ��ֻ�ܳ�ֵ��������
int CDbMngr::Bindkey(TCHAR* pszName, TCHAR* pszKey, const TCHAR szIp[])
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
        record.GetFieldValue(_T("����ֵ"), ret);

    }
    catch(CDBException* pEx)
    {
        AfxMessageBox(pEx->m_strError);
        pEx->Delete();
    }

    return ret.m_iVal;
}


BOOL CDbMngr::Querykey(std::vector<QUERYKEY_SUCCESS>& vecKeyInfo, TCHAR szUserName[], TCHAR szPassWord[])
{

    CString strSql;
    strSql.Format(db_sql_querykey, szUserName);


    BOOL bRet = FALSE;
    try
    {

        CRecordset record(this);
        if(!record.Open(AFX_DB_USE_DEFAULT_TYPE, (LPCTSTR)strSql))
        {
            TRACE(_T("û�ܴ򿪼�¼��"));
            return FALSE;
        }

        CString strKey;
        CDBVariant leftt;



        if(record.IsBOF())
        {
            TRACE(_T("�޿��ÿ���"));
            return FALSE;
        }


        while(!record.IsEOF())
        {

            QUERYKEY_SUCCESS QueryRetInfo;
            ZeroMemory(&QueryRetInfo, sizeof(QUERYKEY_SUCCESS));

            record.GetFieldValue(_T("����"), strKey);
            record.GetFieldValue(_T("ʣ��ʱ��"), leftt);

            QueryRetInfo.remaintime = leftt.m_lVal;

            _tcscpy(QueryRetInfo.key, (LPCTSTR)strKey);

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

void CDbMngr::UserExit(TCHAR szName[])
{
    CString strSql;
    strSql.Format(db_sql_userexit, szName);
    try
    {
        ExecuteSQL((LPCTSTR)strSql);
    }
    catch(CDBException* pEx)
    {
        pEx->Delete();
    }
}

int CDbMngr::CheckUser(TCHAR szUsername[], TCHAR szPassw[])
{
    CString strSql;
    strSql.Format(
        db_sql_checkuser, szUsername, szPassw,
        _T("1"), _T("1"), _T("1"), _T("1"),
        _T("1"), _T("1"), _T("1"), _T("��������"), _T("1"));


    CDBVariant varValue;
    
    try
    {
        CRecordset record(this);
        if(!record.Open(AFX_DB_USE_DEFAULT_TYPE, (LPCTSTR)strSql))
        {
            return 0;
        }
        else
        {
            record.GetFieldValue(_T("����ֵ"), varValue);
        }

    }
    catch(CDBException* pEx)
    {
        pEx->Delete();
        TRACE(_T("CDBException: %s"), (LPCTSTR)pEx->m_strError);
    }

    return varValue.m_lVal;
}



//�����key, key��ʱ��(Сʱ), key������, 1 = ����
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


    try
    {
        ExecuteSQL(strSql);
        strKey = szKey;
    }
    catch(CDBException* pEx)
    {
        pEx->Delete();
        return FALSE;
    }

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

