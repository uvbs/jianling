#if !defined _WEBPOST_H_
#define _WEBPOST_H_

#if _MSC_VER > 1000
    #pragma once
#endif // _MSC_VER > 1000

#include <string>


enum POSTRET
{
    RESULT_FAIL_EXCEPTION,
    RESULT_FAIL_CAPTCHA     ,
    RESULT_FAIL_IPBLOCK ,
    RESULT_FAIL_PWERROR ,
    RESULT_FAIL_AUTH        ,
    RESULT_FAIL_NOACTIVEITEMS,
    RESULT_FAIL_ACTIVEITEMSERR  ,
    RESULT_FAIL_TIMEOUT ,
    RESULT_SUCCESS,
    RESULT_GET_ALEADY   ,
    RESULT_GET_ERROR,
    RESULT_LOGIN_NOUKEY,
    RESULT_FAIL_GETUKEY
};



class Webpost
{
public:
    static void InitCom();
    static void UnInitCom();

    Webpost(const TCHAR szName[], const TCHAR szPw[]);
    ~Webpost();

    void Close();

    //������ҳ�Ĳ���
    int Login();    //��¼
    int Get();      //��ȡ
    int Active();   //����
    BOOL Auth(const CString& str);  //��֤
    BOOL Ten();

    bool GetStartKey(std::basic_string<TCHAR>& strkey);


private:
    //ͨ�õļ���ͷ��Ϣ
    void AddOtherHeader();

    CString GetUniqueKey();

    //��ȡһ��
    bool ReadLine(std::basic_string<TCHAR>& strLine);

    CString ac_name;
    CString ac_pw;
    CString m_gpvlu;

    CString m_Cookie;

    CHttpFile* httpfile;
    CHttpConnection* httpconnect;
    CInternetSession sess;
};

#endif