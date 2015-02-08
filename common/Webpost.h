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

    //几个网页的操作
    int Login();	//登录
    int Get();		//领取
    int Active();	//激活
    BOOL Auth(const CString& str);	//验证
    BOOL Ten();

    CString GetGameStartKey();
    CString GetUniqueKey();

    //工具
    static BOOL GetPwName(CString& strLine, CString& name, CString& pw);

private:
    //通用的几个头信息
    void AddOtherHeader();

    CString ac_name;
    CString ac_pw;
    CString m_gpvlu;

    CHttpFile* httpfile;
    CHttpConnection* httpconnect;
    CInternetSession sess;

    //日志
    Logger log;
};

#endif