// DbMngr.cpp: implementation of the CDbMngr class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "jlsrvr.h"
#include "DbMngr.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
    #define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDbMngr* CDbMngr::_Instance = NULL;
CDbMngr* CDbMngr::GetInstance()
{
    if(_Instance == NULL) {
        _Instance = new CDbMngr;
    }

    return _Instance;
}


CDbMngr::CDbMngr()
{
}

CDbMngr::~CDbMngr()
{

}


BOOL CDbMngr::ModifyBind(TCHAR szUserName[], TCHAR szPassword[], TCHAR szOldBind[], TCHAR szNewBind[])
{

    CString strSql;
    strSql.Format(_T("select top 1 br_bind_result as �ɰ� from Rr_Bind_Rs where br_user = '%s' order by br_bind_result desc"),
                  szUserName);

    try {
        CRecordset record(this);
        record.Open(AFX_DB_USE_DEFAULT_TYPE, strSql);
        CString strOldbind;


        record.GetFieldValue(_T("�ɰ�"), strOldbind);
        if(strOldbind == szOldBind) {
            //�ɰ󶨺��û��ύ��һ��"
            //��ʼ�ж��ϴθ�������

            CString strlastTime;
            strlastTime.Format(
                _T("select br_id as �û�ID from Rr_Bind_Rs where br_user = '%s' ")
                _T("and br_bind_result = '%s' and datediff(mi,br_bind_time,CONVERT(CHAR(19), ")
                _T("Sysdatetime(), 20))>1440 order by br_bind_time desc"),
                szUserName, szOldBind);

            record.Close();
            record.Open(AFX_DB_USE_DEFAULT_TYPE, strlastTime);

            //CString strValue;
            //record.GetFieldValue("br_id", strValue);
            //if(strValue == "")
            if(record.IsBOF()) {
                //�յ�
                return FALSE;
            }
            else {
                //���Ը���
                CString strModify;
                strModify.Format(
                    _T("insert into Rr_Bind_Rs(br_user,br_bind_result,br_bind_time)")
                    _T("values('%s','%s',CONVERT(CHAR(19), Sysdatetime(), 20))"),
                    szUserName, szNewBind);

                ExecuteSQL(strModify);

            }

            record.Close();
            return TRUE;
        }
        else {
            return FALSE;
        }

    }
    catch
        (CDBException* pEx) {
        pEx->Delete();
    }


    return false;
}


//0 ʧ��
//1 �ɹ�
//2 û�����ʱ��
int CDbMngr::Unbindkey(KEY_BUF* pKeyBuf,  sockaddr_in* pSocketAddr)
{
    TCHAR szSql[BUFSIZ] = {0};


    CString strSql;
    strSql.Format(
        _T("{call UnBind('%s','%s','%s','%s','%s','%s','%s','%s','%s')}"),
        pKeyBuf->name, pKeyBuf->key, inet_ntoa(pSocketAddr->sin_addr), _T("0"),
        _T("0"), _T("0"), _T("0"), _T("0"), _T("0"));


    try {
        CRecordset record(this);
        if(record.Open(AFX_DB_USE_DEFAULT_TYPE, strSql) == FALSE) {
            return 0;
        }

        CString strRet;
        record.GetFieldValue(_T("����ֵ"), strRet);

        return _ttoi((LPCTSTR)strRet);
    }
    catch
        (CDBException* pEx) {
        pEx->Delete();
    }

    return 0;
}
BOOL CDbMngr::NewRegist(TCHAR szUserName[], TCHAR szPassword[], TCHAR szBindIP[], TCHAR szMac[], TCHAR szClientIp[])
{

    CString strSql;
    strSql.Format(
        _T("insert into Rr_User(u_user,u_psw,u_ip,u_ac,u_cpuip,u_mac,u_hd_id,")
        _T("u_bios,u_motherboard,u_time,u_game_id,u_bind_type)values('%s','%s',")
        _T("'%s','������','CPUID','%s','Ӳ��ID','BIOS��Ϣ','������Ϣ',CONVERT(CHAR(19),")
        _T("Sysdatetime(), 20),1,'band_ip')"),
        szUserName, szPassword, szClientIp, szMac);

    CString strBind;
    strBind.Format(
        _T("insert into Rr_Bind_Rs(br_user,br_bind_result,br_bind_time)values('%s',")
        _T("'%s',CONVERT(CHAR(19), Sysdatetime(), 20))"),
        szUserName, szBindIP);

    try {

        ExecuteSQL(strSql);
        ExecuteSQL(strBind);
        return TRUE;

    }
    catch
        (CDBException* pEx) {
        pEx->Delete();
    }

    return FALSE;

}


//��ѯ��ֵ���Ƿ����
//����ֵ 0 = ����ʹ��
//1=��ʹ�� jk_key_type=1����ó�ֵ��ֻ�ܳ�ֵ��������
int CDbMngr::Bindkey(KEY_BUF* pKeyBuf, TCHAR szIp[])
{

    CString strSql;

    strSql.Format(_T("{call Bind_key('%s','%s','%s','%s','%s','%s','%s','%s','%s')}"),
                  pKeyBuf->name, pKeyBuf->key, szIp, _T("ac"),
                  _T("0"), _T("0"), _T("0"), _T("0"), _T("0"));

    TRY {
        CRecordset record(this);
        if(record.Open(AFX_DB_USE_DEFAULT_TYPE, (LPCTSTR)strSql) == FALSE)
        {
            return result_bind_fail;
        }

        CString strRet;
        record.GetFieldValue(_T("����ֵ"), strRet);

        return _ttoi((LPCTSTR)strRet);

    }
    CATCH(CDBException, e) {

    }
    END_CATCH

    return FALSE;
}


BOOL CDbMngr::Querykey(std::vector<QUERYKEY_RET_BUF>& vecKeyInfo, TCHAR szUserName[], TCHAR szPassWord[])
{

    CString strSql;
    strSql.Format(
        _T("select uk_key as ����, jk_recharge_time as ��ֵʱ�� ,bt_type_explanation as ��ֵ������ ,")
        _T(" datediff(ss,CONVERT(CHAR(19), Sysdatetime(), 120),dateadd(hh,b.jk_time_type,b.jk_recharge_time))/60/60 as ʣ��ʱ�� ")
        _T(" from Rr_User_Key a,Rr_Key b,Rr_Bind_type c where a.uk_key = b.jk_key and c.bt_id = b.jk_key_type and uk_user = ")
        _T("'%s' and bt_type_explanation = '��������'  order by uk_key"),
        szUserName);


    BOOL bRet = FALSE;
    try {

        CRecordset record(this);
        if(record.Open(AFX_DB_USE_DEFAULT_TYPE, (LPCTSTR)strSql) == FALSE) {
            THROW(_T("û�ܴ򿪼�¼��"));
        }

        CString strKey;
        CString strBuildTime;
        CString strKeyType;
        CString strRemainTime;

        int count = record.GetRecordCount();
        while(record.IsEOF() == FALSE) {
            QUERYKEY_RET_BUF QueryRetInfo;
            ZeroMemory(&QueryRetInfo, sizeof(QUERYKEY_RET_BUF));

            record.GetFieldValue(_T("����"), strKey);
            record.GetFieldValue(_T("��ֵʱ��"), strBuildTime);
            record.GetFieldValue(_T("��ֵ������"), strKeyType);
            record.GetFieldValue(_T("ʣ��ʱ��"), strRemainTime);

            QueryRetInfo.count = (UCHAR)--count;
            _tcsncpy(QueryRetInfo.type, (LPCTSTR)strKeyType, strKeyType.GetLength());
            QueryRetInfo.remaintime = _ttoi((LPCTSTR)strRemainTime);

            _tcsncpy(QueryRetInfo.buildtime, (LPCTSTR)strBuildTime, strBuildTime.GetLength());
            _tcsncpy(QueryRetInfo.key, (LPCTSTR)strKey, strKey.GetLength());

            vecKeyInfo.push_back(QueryRetInfo);

            record.MoveNext();
        }

        bRet = TRUE;
    }
    catch(CDBException* pEx) {
        pEx->Delete();
    }

    return bRet;
}

int CDbMngr::GetPwRight(TCHAR szUsername[], TCHAR szPassw[])
{
    CString strSql;
    strSql.Format(_T("select u_psw as �û����� from Rr_User where u_user = '%s' and u_game_id = 1"),
                  szUsername);


    try {
        CRecordset record(this);
        record.Open(AFX_DB_USE_DEFAULT_TYPE, (LPCTSTR)strSql);
        CString strPassword;


        //û������
        if(record.IsBOF()) {
            strPassword.Empty();
            return result_login_notuser;
        }
        else {
            record.GetFieldValue(_T("�û�����"), strPassword);
            if(strPassword == szPassw) {
                return result_login_ok;
            }
            else {
                return result_login_pwerror;
            }
        }

    }
    catch(CDBException* pEx) {
        pEx->Delete();
    }

    return result_login_pwerror;

}


TCHAR g_szAlpha[] = _T("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890");

//�����key, key��ʱ��(Сʱ), key������, 1 = ����
BOOL CDbMngr::AddKey(CString& strKey, UINT nTimes, int type)
{

    TCHAR szKey[9] = {0};

    /* Seed the random-number generator with current time so that
    * the numbers will be different every time we run.
    */

    //48~57
    //65 90
    //97~122
    /* Display 8 numbers. */
    while(1) {
        ZeroMemory(szKey, sizeof(szKey));
        for(int i = 0; i < 8; i++) {
            szKey[i] = g_szAlpha[rand() % 63];
        }

        if(_tcslen(szKey) == 8) {
            break;
        }
    }


    TCHAR szSql[] =
        _T("insert into Rr_Key(jk_key,jk_build_time,jk_sell_time,jk_recharge_time,jk_state,jk_time_type,jk_key_type)")
        _T("values('%s',CONVERT(CHAR(19), Sysdatetime(), 20),NULL,NULL,0,%d,%d)");

    CString strSql;
    strSql.Format(szSql, szKey, nTimes, type);


    TRY {
        ExecuteSQL(strSql);
        strKey = szKey;
    }
    CATCH(CDBException, e) {
        // The error code is in e->m_nRetCode
        return FALSE;
    }
    END_CATCH


    return TRUE;
}


BOOL CDbMngr::Init()
{
    BOOL bRet;

    TRY {
        if(!IsOpen())
        {
            bRet = OpenEx(NULL, CDatabase::openReadOnly);
        }
        else{
            bRet = TRUE;
        }
    }
    CATCH(CDBException, e) {
        if(AfxMessageBox(IDS_DB_OPENERROR, MB_YESNO) == IDNO) {
            delete this;
        }
    }
    END_CATCH;
    return bRet;
}

