#if !defined _WEBPOST_H_
#define _WEBPOST_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Logger.h"


enum POSTRET
{
    RESULT_FAIL_EXCEPTION,
    RESULT_FAIL_CAPTCHA		,
    RESULT_FAIL_IPBLOCK	,
    RESULT_FAIL_PWERROR	,
    RESULT_FAIL_AUTH		,
    RESULT_FAIL_NOACTIVEITEMS,
    RESULT_FAIL_ACTIVEITEMSERR	,
    RESULT_FAIL_TIMEOUT	,
    RESULT_SUCCESS,
    RESULT_GET_ALEADY	,
    RESULT_GET_ERROR,
    RESULT_LOGIN_NOUKEY,
    RESULT_FAIL_GETUKEY
};

class Logger;
class Webpost
{
public:
    static void InitCom();
    static void UnInitCom();

    Webpost(const TCHAR szName[], const TCHAR szPw[]);
    Webpost(const CString& strName, const CString& strPw);
    ~Webpost();

    void Close();
    void InitSetting();

    //������ҳ�Ĳ���
    int Login();	//��¼
    int Get();		//��ȡ
    int Active();	//����
    BOOL Auth(const CString& str);	//��֤
    BOOL Ten();

    CString GetGameStartKey();
    CString GetUniqueKey();

    //����
    static BOOL GetPwName(CString& strLine, CString& name, CString& pw);

private:
    //ͨ�õļ���ͷ��Ϣ
    void AddOtherHeader();

    CString ac_name;
    CString ac_pw;
    CString m_gpvlu;

    CHttpFile* httpfile;
    CHttpConnection* httpconnect;
    CInternetSession sess;

    //��־
    Logger log;
};

#endif