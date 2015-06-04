// Webpost.cpp: implementation of the Webpost class.
//
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "webpost.h"
#include "ncllm3.tlh"


#if _MSC_VER <= 1500
    #include <boost\regex.hpp>
    using namespace boost;

	#ifdef _UNICODE
    typedef boost::wregex tregex;
    typedef boost::wsmatch tsmatch;
	#else
    typedef boost::regex tregex;
    typedef boost::smatch tsmatch;
	#endif

#else
    #include <regex>
    using namespace std;

	#ifdef _UNICODE
    typedef wregex tregex;
    typedef wsmatch tsmatch;
	#else
    typedef regex tregex;
    typedef smatch tsmatch;
	#endif
#endif


#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif



const TCHAR ten_obj[] = _T("/myshop/coupon/bns/used/list");
const TCHAR gift_ref[] = _T("http://bns.plaync.com/story/returnplay/comeback/index");

#ifdef JLTW
    const TCHAR login_server[] = _T("tw.ncsoft.com");
    const TCHAR login_obj[] = _T("/login/game/login");
    const TCHAR login_query[] = _T("login_name=%s&password=%s&persistent=0&return_url=");
    const TCHAR login_ref[] = _T("https://tw.ncsoft.com/login/game/login");

#else
    const TCHAR login_ref[] = _T("https://login.plaync.com/login/login");
    const TCHAR login_server[] = _T("login.plaync.com");
    const TCHAR login_obj[] = _T("/login/login");
    const TCHAR login_query[] = _T("id=%s&pwd=%s&game_id=13&loginsite=&site_id=13&adult_yn=N&encoding_type=utf-8&ukey=%s&loginLevel=");

    const TCHAR start_server[] = _T("bnslauncher.plaync.com");
    const TCHAR start_obj[] = _T("/api/launcher/launcher");
    const TCHAR start_query[] = _T("serverType=live&callback=jQuery17109341772997286171_1412085994722&_=1412086012077");
    const TCHAR start_ref[] = _T("http://bns.plaync.com/story/note/index");


#endif

const TCHAR auth_server[] = _T("login.plaync.co.kr");
const TCHAR auth_objname[] = _T("/auth/sso");
const TCHAR auth_query[] = _T("return_url=http://bns.plaync.com/story/returnplay/comeback/index&gpvlu=%s&is_mobile=&mgpsec=&mgpsecexpireat=");

const TCHAR gift_server[] = _T("bns.plaync.com");
const TCHAR gift_get_obj[] = _T("/story/returnplay/comeback/support");
const TCHAR active_server[] = _T("nshop.plaync.com");
const TCHAR active_obj[] = _T("/myshop/coupon/bns/usable/list");
const TCHAR active_obj_get[] = _T("/myshop/coupon/useGoodsCoupon.json?userCouponId=%s&goodsId=%s&_=%ld");
const TCHAR active_ref[] = _T("http://nshop.plaync.com/myshop/coupon/popup/couponPopupUseForm");
const char ten[] = "\xeb\xac\xb4\xeb\xa3\x8c\x20\xec\x97\xac\xed\x96\x89\x20\xec\x84\xa0\xeb"
                   "\xac\xbc\x20\xed\x8c\xa8\xed\x82\xa4\xec\xa7\x80";      //韩文


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Webpost::Webpost(const TCHAR szName[], const TCHAR szPw[])
{
    httpfile = NULL;
    httpconnect = NULL;
    m_strName = szName;
    m_strPw = szPw;

}


Webpost::~Webpost()
{
    Close();
    sess.Close();
}


void Webpost::Close()
{
    if(httpfile)
    {
        httpfile->Close();
        delete httpfile;
        httpfile = NULL;
    }

    if(httpconnect)
    {
        httpconnect->Close();
        delete httpconnect;
        httpconnect = NULL;
    }
}


//登录时的返回值
//0表示失败
//1表示被封
//2表示需要验证码
int Webpost::Login()
{


    int bRet = RESULT_LOGIN_NOUKEY;

#ifdef JLTW

    bRet = RESULT_SUCCESS;
    _RPTF0(_CRT_ERROR, "不要调用此函数, 直接调用GetStartKey");

#else

    try
    {

        httpconnect = sess.GetHttpConnection(login_server, (INTERNET_PORT)INTERNET_DEFAULT_HTTPS_PORT);

        httpfile = httpconnect->OpenRequest(CHttpConnection::HTTP_VERB_POST, login_obj,
                                            login_ref, 1, NULL, NULL,
                                            INTERNET_FLAG_NO_AUTO_REDIRECT | INTERNET_FLAG_SECURE | INTERNET_FLAG_RELOAD);


        //通用HTTP头
        AddOtherHeader();

        CString strUkey = GetUniqueKey();
        if(strUkey == _T("")) return bRet;

        CString strQuery;
        strQuery.Format(login_query, ac_name, ac_pw, strUkey);


#ifdef _UNICODE
        USES_CONVERSION;
        LPCSTR lpTemp = W2A((LPCTSTR)strQuery);
#else
        LPCSTR lpTemp = (LPCTSTR)strQuery;
#endif

        //发送HTTP请求
        httpfile->SendRequest(NULL, 0, (LPVOID)lpTemp, strlen(lpTemp));


        //直接对行匹配正则
        tregex gpvlu(_T("[a-zA-Z0-9]{20,}"));
        tsmatch matches;

        std::basic_string<TCHAR> strLine;
        while(ReadLine(strLine))
        {
            //判断是否返回 gpvlu
            if(regex_search(strLine, matches, gpvlu))
            {
                //保存到成员变量中
                m_gpvlu = matches.str().c_str();
                bRet = RESULT_SUCCESS;
                break;
            }

            tregex blocking(_T("LoginBlocking"));
            if(regex_search(strLine, matches, blocking))
            {
                bRet = RESULT_FAIL_IPBLOCK;
                break;
            }

            tregex captcha(_T("captcha.jpg"));
            if(regex_search(strLine, matches, captcha))
            {
                bRet = RESULT_FAIL_CAPTCHA;
                break;
            }

            tregex pwerror(_T("h1_type2"));
            if(regex_search(strLine, matches, pwerror))
            {
                bRet = RESULT_FAIL_PWERROR;
                break;
            }

        }


        if(bRet == RESULT_SUCCESS)
        {
            if(Auth(m_gpvlu))
            {
                bRet = RESULT_SUCCESS;
            }
            else
            {
                bRet = RESULT_FAIL_AUTH;
            }
        }

    }
    catch(CInternetException* pEx)
    {
        bRet = RESULT_FAIL_EXCEPTION;
        if(pEx->m_dwError == ERROR_INTERNET_TIMEOUT)
        {
            bRet = RESULT_FAIL_TIMEOUT;
        }

        pEx->Delete();
    }


    //删掉连接
    Close();


#endif //JLTW


    return bRet;
}


//领取
int Webpost::Get()
{

    BOOL bRet = RESULT_GET_ERROR;
    try
    {

        httpconnect = sess.GetHttpConnection(gift_server,
                                             (INTERNET_PORT)INTERNET_DEFAULT_HTTP_PORT);
        httpfile = httpconnect->OpenRequest(CHttpConnection::HTTP_VERB_POST,
                                            gift_get_obj, gift_ref, 1, NULL, NULL,
                                            INTERNET_FLAG_NO_AUTO_REDIRECT | INTERNET_FLAG_RELOAD);

        AddOtherHeader();
        httpfile->AddRequestHeaders(_T("X-Requested-With: XMLHttpRequest"));


        CString strQuery;
        strQuery.Format(auth_query, m_strGpvlu.c_str());


#ifdef _UNICODE
        USES_CONVERSION;
        LPCSTR lpTemp = W2A((LPCTSTR)strQuery);
#else
        LPCSTR lpTemp = (LPCTSTR)strQuery;
#endif
        httpfile->SendRequest(NULL, 0, (LPVOID)lpTemp, strlen(lpTemp));


        char szBuf[BUFSIZ] = {0};
        while(httpfile->Read(szBuf, BUFSIZ - 1))
        {
            if(strstr((char*)szBuf, "SUCCESS") != NULL)
            {
                bRet = RESULT_SUCCESS;
                break;
            }

            if(strstr((char*)szBuf, "ALEADY_SUPPORTED") != NULL)
            {
                bRet = RESULT_GET_ALEADY;
                break;
            }

            ZeroMemory(szBuf, BUFSIZ);
        }

    }
    catch(CInternetException* pEx)
    {
        TRACE1("%d", pEx->m_dwError);
        if(pEx->m_dwError == ERROR_INTERNET_TIMEOUT)
        {
            bRet = RESULT_FAIL_TIMEOUT;
        }
        pEx->Delete();
    }

    Close();

    return bRet;
}

int Webpost::Active()   //激活
{
    BOOL bRet = RESULT_FAIL_NOACTIVEITEMS;//没有激活条目
    try
    {
        CString goodsid;
        CString couponid;

        httpconnect = sess.GetHttpConnection(active_server,
                                             (INTERNET_PORT)INTERNET_DEFAULT_HTTP_PORT);

        httpfile = httpconnect->OpenRequest(CHttpConnection::HTTP_VERB_GET,
                                            active_obj, NULL, 1, NULL, NULL,
                                            INTERNET_FLAG_NO_AUTO_REDIRECT | INTERNET_FLAG_RELOAD);

        AddOtherHeader();
        httpfile->SendRequest();

        tregex goods(_T("\\[(\\d+)\\],\\s*\'(\\d+)\'"));
        tsmatch matches;

        std::basic_string<TCHAR> strLine;
        while(ReadLine(strLine))
        {

            if(regex_search(strLine, matches, goods))
            {
                //匹配到, 把值取出来
                goodsid = matches.str(1).c_str();
                couponid = matches.str(2).c_str();

                TRACE(_T("匹配到: %s - %s"), (LPCTSTR)goodsid, (LPCTSTR)couponid);


                //匹配到一个就将默认错误改成激活错误
                bRet = RESULT_FAIL_ACTIVEITEMSERR;


                time_t ltime;
                time(&ltime);
                // ltime += GetTickCount();
                CString query;
                query.Format(active_obj_get, couponid, goodsid, ltime);

                sess.GetHttpConnection(active_server,
                                       (INTERNET_PORT)INTERNET_DEFAULT_HTTP_PORT);

                CHttpFile* httpfile_temp =
                    httpconnect->OpenRequest(
                        _T("POST"),
                        query,
                        active_ref,
                        1,
                        NULL,
                        NULL,
                        INTERNET_FLAG_NO_AUTO_REDIRECT | INTERNET_FLAG_RELOAD);

                httpfile_temp->SendRequest();


                BOOL bActiveOK = FALSE;
                CHAR szBuf[BUFSIZ] = {0};
                while(httpfile_temp->Read(szBuf, BUFSIZ))
                {
                    if(strstr(szBuf, "resultCode\":0") != NULL)
                    {
                        bActiveOK = TRUE;
                    }
                }

                //关闭连接
                Close();

                if(bActiveOK == FALSE)
                {
                    bRet = RESULT_FAIL_ACTIVEITEMSERR;
                    break;  //直接跳出把， 算是激活失败
                }
                else
                {
                    bRet = RESULT_SUCCESS;
                }
            }
        }


    }
    catch(CInternetException* pEx)
    {
        if(pEx->m_dwError == ERROR_INTERNET_TIMEOUT)
        {
            bRet = RESULT_FAIL_TIMEOUT;
        }
        pEx->Delete();
    }

    //关闭连接
    Close();


    return bRet;
}


//返回 -1 激活失败, 返回 1 成功, 返回 0 没有需要激活的
int Webpost::Ten()
{
    return -1;
}


//组织http头
void Webpost::AddOtherHeader()
{
    httpfile->AddRequestHeaders(_T("User-Agent: Mozilla/5.0 (Windows NT 6.1; WOW64; Trident/7.0; rv:11.0) like Gecko"));
    httpfile->AddRequestHeaders(_T("Accept: text/html, application/xhtml+xml, */*"));
    httpfile->AddRequestHeaders(_T("Content-Type: application/x-www-form-urlencoded"));
}

std::basic_string<TCHAR> Webpost::GetUniqueKey()
{
    CLSID clsid;
    if(CLSIDFromProgID(OLESTR("ncllm.ncllmCtrl"), &clsid) != S_OK)
    {
        return _T("");
    }

    CComPtr<IncllmCtrl> pCtrl;
    pCtrl.CoCreateInstance(clsid);

    _bstr_t str = pCtrl->GetUniqueKey();

    pCtrl.Release();
    return (LPTSTR)str;

}

bool Webpost::ReadLine(std::basic_string<TCHAR>& strLine)
{
    char cbChar = 0;
    strLine = _T("");
    try
    {

        for(;;)
        {
            if(httpfile->Read(&cbChar, sizeof(cbChar)) == 0) return false;

            strLine += cbChar;

            if(cbChar == 0x0d || cbChar == 0x0a)
            {
                if(cbChar == 0x0a)
                {
                    break;
                }

                continue;
            }


        }

        return true;

    }
    catch(CFileException* pEx)
    {
        pEx->Delete();
    }

    return false;
}


BOOL Webpost::Auth(const CString& gpvlu)
{
    BOOL bRet = FALSE;
    try
    {

        httpconnect = sess.GetHttpConnection(auth_server,
                                             (INTERNET_PORT)INTERNET_DEFAULT_HTTPS_PORT);
        httpfile = httpconnect->OpenRequest(CHttpConnection::HTTP_VERB_POST, auth_objname,
                                            login_ref, 1, NULL, NULL,
                                            INTERNET_FLAG_SECURE | INTERNET_FLAG_NO_AUTO_REDIRECT | INTERNET_FLAG_RELOAD);

        AddOtherHeader();

        CString strQuery;
        strQuery.Format(auth_query, gpvlu);

#ifdef _UNICODE
        USES_CONVERSION;
        LPCSTR lpTemp = W2A((LPCTSTR)strQuery);
#else
        LPCSTR lpTemp = (LPCTSTR)strQuery;
#endif

        httpfile->SendRequest(NULL, 0, (LPVOID)lpTemp, strlen(lpTemp));
        Close();

        httpconnect = sess.GetHttpConnection(gift_server, (INTERNET_PORT)INTERNET_DEFAULT_HTTP_PORT);
        httpfile = httpconnect->OpenRequest(CHttpConnection::HTTP_VERB_GET,
                                            _T("/"), NULL, 1, NULL, NULL,
                                            INTERNET_FLAG_NO_AUTO_REDIRECT | INTERNET_FLAG_RELOAD);
        AddOtherHeader();
        httpfile->SendRequest();

        //直接对行匹配正则
        tregex isLoginFlag(_T("isLoginFlag = \"Y\""));
        tsmatch matches;

        std::basic_string<TCHAR> strLine;
        while(ReadLine(strLine))
        {
            if(regex_search(strLine, matches, isLoginFlag))
            {
                bRet = TRUE;
                break;
            }
        }
    }
    catch(CInternetException* pEx)
    {
        pEx->Delete();
    }

    Close();
    return bRet;
}


//取得网页返回的sesskey数据
bool Webpost::GetStartKey(std::basic_string<TCHAR>& strkey)
{

    try
    {

#ifdef JLTW

        httpconnect = sess.GetHttpConnection(login_server, (INTERNET_PORT)INTERNET_DEFAULT_HTTPS_PORT);

        httpfile = httpconnect->OpenRequest(
                       CHttpConnection::HTTP_VERB_POST, login_obj,
                       login_ref, 1, NULL, NULL,
                       INTERNET_FLAG_NO_AUTO_REDIRECT | INTERNET_FLAG_SECURE | INTERNET_FLAG_RELOAD);

#else
        httpconnect = sess.GetHttpConnection(start_server, (INTERNET_PORT)INTERNET_DEFAULT_HTTPS_PORT);

        httpfile = httpconnect->OpenRequest(
                       CHttpConnection::HTTP_VERB_GET, start_obj,
                       NULL, 1, NULL, NULL,
                       INTERNET_FLAG_NO_AUTO_REDIRECT | INTERNET_FLAG_SECURE | INTERNET_FLAG_RELOAD);


#endif


        AddOtherHeader();


#ifdef JLTW

        CString strQuery;
        strQuery.Format(login_query, m_strName.c_str(), m_strPw.c_str());
        strQuery.Replace(_T("+"), _T("%2B"));

#ifdef _UNICODE
        USES_CONVERSION;
        LPCSTR lpTemp = W2A((LPCTSTR)strQuery);
#else
        LPCSTR lpTemp = (LPCTSTR)strQuery;
#endif

        httpfile->SendRequest(NULL, 0, (LPVOID)lpTemp, strlen(lpTemp));

#else

        httpfile->SendRequest(NULL, 0, (LPVOID)start_query, sizeof(start_query));

#endif

        tregex skey(_T("\\w{20,}=="));
        tsmatch matches;

        std::basic_string<TCHAR> strLine;
        while(ReadLine(strLine))
        {
            if(regex_search(strLine, matches, skey))
            {
                strkey = matches.str(0);
                return true;
            }
        }

    }
    catch(CInternetException* pEx)
    {
        pEx->Delete();
    }

    Close();
    return false;
}

void Webpost::InitCom()
{
    CoInitialize(NULL);
}

void Webpost::UnInitCom()
{
    CoUninitialize();
}