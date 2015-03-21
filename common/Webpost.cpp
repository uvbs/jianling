// Webpost.cpp: implementation of the Webpost class.
//
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "webpost.h"


#if _MSC_VER <= 1200
#include <boost\regex.hpp>
using namespace boost;
#else
#include <regex>
using namespace std;
#endif

#import "ncllm3.dll" no_namespace


const TCHAR ten_obj[] = _T("/myshop/coupon/bns/used/list");
const TCHAR gift_ref[] = _T("http://bns.plaync.com/story/returnplay/comeback/index");
const TCHAR login_ref[] = _T("https://login.plaync.com/login/login");
const TCHAR login_server[] = _T("login.plaync.com");
const TCHAR login_objname[] = _T("/login/login");
const TCHAR auth_server[] = _T("login.plaync.co.kr");
const TCHAR auth_objname[] = _T("/auth/sso");
const TCHAR auth_query[] = _T("return_url=http://bns.plaync.com/story/returnplay/comeback/index&gpvlu=%s&is_mobile=&mgpsec=&mgpsecexpireat=");
const TCHAR login_query[] = _T("id=%s&pwd=%s&game_id=13&loginsite=&site_id=13&adult_yn=N&encoding_type=utf-8&ukey=%s&loginLevel=");
const TCHAR gift_server[] = _T("bns.plaync.com");
const TCHAR gift_get_obj[] = _T("/story/returnplay/comeback/support");
const TCHAR active_server[] = _T("nshop.plaync.com");
const TCHAR active_obj[] = _T("/myshop/coupon/bns/usable/list");
const TCHAR active_obj_get[] = _T("/myshop/coupon/useGoodsCoupon.json?userCouponId=%s&goodsId=%s&_=%ld");
const TCHAR active_ref[] = _T("http://nshop.plaync.com/myshop/coupon/popup/couponPopupUseForm");
const char ten[] = "\xeb\xac\xb4\xeb\xa3\x8c\x20\xec\x97\xac\xed\x96\x89\x20\xec\x84\xa0\xeb"
                   "\xac\xbc\x20\xed\x8c\xa8\xed\x82\xa4\xec\xa7\x80";		//韩文
const TCHAR start_server[] = _T("bnslauncher.plaync.com");
const TCHAR start_obj[] = _T("/api/launcher/launcher");
const TCHAR start_query[] = _T("serverType=live&callback=jQuery17109341772997286171_1412085994722&_=1412086012077");
const TCHAR start_ref[] = _T("http://bns.plaync.com/story/note/index");


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Webpost::Webpost(const CString& strName, const CString& strPw): log(_T("Webpost"))
{
    httpfile = NULL;
    httpconnect = NULL;
    ac_name = strName;
    ac_pw = strPw;

    InitSetting();
}

Webpost::Webpost(const TCHAR szName[], const TCHAR szPw[]): log(_T("Webpost"))
{
    httpfile = NULL;
    httpconnect = NULL;
    ac_name = szName;
    ac_pw = szPw;

    InitSetting();
}


Webpost::~Webpost()
{
    Close();
    sess.Close();
}

void Webpost::InitSetting()
{

}


void Webpost::Close()
{

    if(httpfile != NULL)
    {
        httpfile->Close();
        delete httpfile;
        httpfile = NULL;
    }
    if(httpconnect != NULL)
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
    try
    {
        Close();
        httpconnect = sess.GetHttpConnection(login_server,
                                             (INTERNET_PORT)INTERNET_DEFAULT_HTTPS_PORT);
        httpfile = httpconnect->OpenRequest(CHttpConnection::HTTP_VERB_POST, login_objname,
                                            login_ref, 1, NULL, NULL,
                                            INTERNET_FLAG_NO_AUTO_REDIRECT | INTERNET_FLAG_SECURE | INTERNET_FLAG_RELOAD);

        AddOtherHeader();
        CString strUkey = GetUniqueKey();
        if(strUkey == _T(""))
        {
            return bRet;
        }

        CString strQuery;
        strQuery.Format(login_query, ac_name, ac_pw, strUkey);

#ifdef _UNICODE
        USES_CONVERSION;
        LPCSTR lpTemp = W2A((LPCTSTR)strQuery);
#else
        LPCSTR lpTemp = (LPCTSTR)strQuery;
#endif
        httpfile->SendRequest(NULL, 0, (LPVOID)lpTemp, strlen(lpTemp));


        //直接对行匹配正则
        regex gpvlu("[a-zA-Z0-9]{20,}");
        cmatch matches;

        CString strLine;
        while(httpfile->ReadString(strLine))
        {
            //判断是否返回 gpvlu
            if(regex_search((char*)(LPCTSTR)strLine, matches, gpvlu))
            {
                //保存到成员变量中
                m_gpvlu = matches.str().c_str();
                bRet = RESULT_SUCCESS;
                break;
            }

            regex blocking("LoginBlocking");
            if(regex_search((char*)(LPCTSTR)strLine, matches, blocking))
            {
                bRet = RESULT_FAIL_IPBLOCK;
                break;
            }

            regex captcha("captcha.jpg");
            if(regex_search((char*)(LPCTSTR)strLine, matches, captcha))
            {
                bRet = RESULT_FAIL_CAPTCHA;
                break;
            }

            regex pwerror("h1_type2");
            if(regex_search((char*)(LPCTSTR)strLine, matches, pwerror))
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

    return bRet;
}

int Webpost::Get() //领取
{

    BOOL bRet = RESULT_GET_ERROR;
    try
    {
        Close();
        httpconnect = sess.GetHttpConnection(gift_server,
                                             (INTERNET_PORT)INTERNET_DEFAULT_HTTP_PORT);
        httpfile = httpconnect->OpenRequest(CHttpConnection::HTTP_VERB_POST,
                                            gift_get_obj, gift_ref, 1, NULL, NULL,
                                            INTERNET_FLAG_NO_AUTO_REDIRECT | INTERNET_FLAG_RELOAD);

        AddOtherHeader();
        httpfile->AddRequestHeaders(_T("X-Requested-With: XMLHttpRequest"));


        CString strQuery;
        strQuery.Format(auth_query, m_gpvlu);


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

    return bRet;
}

int Webpost::Active() //激活
{
    BOOL bRet = RESULT_FAIL_NOACTIVEITEMS;//没有激活条目
    try
    {
        CString goodsid;
        CString couponid;

        Close();
        httpconnect = sess.GetHttpConnection(active_server,
                                             (INTERNET_PORT)INTERNET_DEFAULT_HTTP_PORT);

        httpfile = httpconnect->OpenRequest(CHttpConnection::HTTP_VERB_GET,
                                            active_obj, NULL, 1, NULL, NULL,
                                            INTERNET_FLAG_NO_AUTO_REDIRECT | INTERNET_FLAG_RELOAD);

        AddOtherHeader();
        httpfile->SendRequest();

        regex goods("\\[(\\d+)\\],\\s*\'(\\d+)\'");
        cmatch matches;

        CString strLine;
        while(httpfile->ReadString(strLine))
        {
            if(regex_search((LPCTSTR)strLine, matches, goods))
            {
                //匹配到, 把值取出来
                goodsid = matches.str(1).c_str();
                couponid = matches.str(2).c_str();

                log.logdv(_T("匹配到: %s - %s"), (LPCTSTR)goodsid, (LPCTSTR)couponid);
                //匹配到一个就将默认错误改成激活错误
                bRet = RESULT_FAIL_ACTIVEITEMSERR;


                time_t ltime;
                time(&ltime);
                // ltime += GetTickCount();
                CString query;
                query.Format(active_obj_get, couponid, goodsid, ltime);

                sess.GetHttpConnection(active_server,
                                       (INTERNET_PORT)INTERNET_DEFAULT_HTTP_PORT);

                CHttpFile* httpfile_temp = httpconnect->OpenRequest(_T("POST"), query,
                                           active_ref, 1, NULL, NULL,
                                           INTERNET_FLAG_NO_AUTO_REDIRECT | INTERNET_FLAG_RELOAD);

                AddOtherHeader();
                httpfile_temp->SendRequest();

                BOOL bActiveOK = FALSE;
                while(httpfile_temp->ReadString(strLine))
                {
                    if(strstr((LPCTSTR)strLine, "resultCode\":0") != NULL)
                    {
                        bActiveOK = TRUE;
                    }
                }

                httpfile_temp->Close();
                delete httpfile_temp;

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
        TRACE(_T("%d"), pEx->m_dwError);
        if(pEx->m_dwError == ERROR_INTERNET_TIMEOUT)
        {
            bRet = RESULT_FAIL_TIMEOUT;
        }
        pEx->Delete();
    }

    return bRet;
}

int Webpost::Ten()//返回 -1 激活失败, 返回 1 成功, 返回 0 没有需要激活的
{
    return -1;
}

void Webpost::AddOtherHeader()  //组织http头
{
    httpfile->AddRequestHeaders(
        _T("User-Agent: Mozilla/5.0 (Windows NT 6.1; WOW64) AppleWebKit/537.36 ")
        _T("(KHTML, like Gecko) Chrome/39.0.2171.71 Safari/537.36"));
    httpfile->AddRequestHeaders(_T("Pragma: no-cache"));
    httpfile->AddRequestHeaders(_T("Connection: keep-alive"));
    httpfile->AddRequestHeaders(_T("Accept: */*"));
    httpfile->AddRequestHeaders(_T("Content-Type: application/x-www-form-urlencoded"));
}

CString Webpost::GetUniqueKey()
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

BOOL Webpost::Auth(const CString& gpvlu)
{
    BOOL bRet = FALSE;
    try
    {
        Close();
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
        regex isLoginFlag("isLoginFlag = \"Y\"");
        cmatch matches;

        CString strLine;
        while(httpfile->ReadString(strLine))
        {
            if(regex_search((char*)(LPCTSTR)strLine, matches, isLoginFlag))
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

    return bRet;
}

CString Webpost::GetGameStartKey()
{
    //取得网页返回的sesskey数据
    //登录需要
    try
    {
        Close();
        httpconnect = sess.GetHttpConnection(start_server,
                                             (INTERNET_PORT)INTERNET_DEFAULT_HTTPS_PORT);

        httpfile = httpconnect->OpenRequest(CHttpConnection::HTTP_VERB_GET, start_obj,
                                            start_ref, 1, NULL, NULL,
                                            INTERNET_FLAG_NO_AUTO_REDIRECT | INTERNET_FLAG_SECURE | INTERNET_FLAG_RELOAD);

        AddOtherHeader();
        httpfile->SendRequest(NULL, 0, (void*)start_query, sizeof(start_query));

        regex skey("\\w{20,}==");
        cmatch matches;

        CString strLine;
        while(httpfile->ReadString(strLine))
        {
            if(regex_search((LPCTSTR)strLine, matches, skey))
            {
                CString strRet = matches.str(0).c_str();
                return strRet;
            }
        }

    }
    catch(CInternetException* pEx)
    {
        TRACE1(_T("%d"), pEx->m_dwError);
        pEx->Delete();
    }
    return _T("");
}


//从一行中取出来用户名和密码
BOOL Webpost::GetPwName(CString& strLine, CString& name, CString& pw)
{

    regex line("([^, ]*)([, ]*)?([^, ]*)");
    cmatch matches;

#ifdef _UNICODE
    USES_CONVERSION;
    LPCSTR lpTemp = T2A(strLine);
#else
    LPCSTR lpTemp = (LPCTSTR)strLine;
#endif

    if(regex_search(lpTemp, matches, line))
    {
        name = matches.str(1).c_str();
        pw = matches.str(3).c_str();
        return TRUE;
    }

    return FALSE;
}

void Webpost::InitCom()
{
    CoInitialize(NULL);
}

void Webpost::UnInitCom()
{
    CoUninitialize();
}