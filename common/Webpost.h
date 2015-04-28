#if !defined _WEBPOST_H_
#define _WEBPOST_H_


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

    //几个网页的操作
    int Login();    //登录
    int Get();      //领取
    int Active();   //激活
    BOOL Auth(const CString& str);  //验证
    BOOL Ten();

    bool GetStartKey(std::basic_string<TCHAR>& strkey);


private:
    //通用的几个头信息
    void AddOtherHeader();

    std::basic_string<TCHAR> GetUniqueKey();

    //读取一行
    bool ReadLine(std::basic_string<TCHAR>& strLine);

    std::basic_string<TCHAR> m_strName;
    std::basic_string<TCHAR> m_strPw;
    std::basic_string<TCHAR> m_strGpvlu;


    CHttpFile* httpfile;
    CHttpConnection* httpconnect;
    CInternetSession sess;
};

#endif