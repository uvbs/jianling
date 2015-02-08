// JLSrvrDoc.cpp : implementation of the CJLSrvrDoc class
//

#include "stdafx.h"
#include "JLSrvr.h"

#include "ListenSocket.h"
#include "JLSrvrDoc.h"
#include "RequestSocket.h"
#include "Request.h"

#include "..\common\common.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CJLSrvrDoc

IMPLEMENT_DYNCREATE(CJLSrvrDoc, CDocument)

BEGIN_MESSAGE_MAP(CJLSrvrDoc, CDocument)
    //{{AFX_MSG_MAP(CJLSrvrDoc)
    ON_UPDATE_COMMAND_UI(ID_INDICATOR_UPTIME , OnUpdateCalcUpTime)
    ON_UPDATE_COMMAND_UI(ID_INDICATOR_CONNECTS, OnUpdateConnects)
    ON_COMMAND(ID_FILE_RESTART, OnFileRestart)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CJLSrvrDoc construction/destruction

CJLSrvrDoc::CJLSrvrDoc()
{
    // TODO: add one-time construction code here
    m_pListen = NULL;
    m_pDB = NULL;
}

CJLSrvrDoc::~CJLSrvrDoc()
{
}



void CJLSrvrDoc::OnUpdateCalcUpTime(CCmdUI* pCmdUI)
{

    CTime timeNow = CTime::GetCurrentTime();
    // calculate uptime and set the status bar....
    CTimeSpan upTime = timeNow - m_timeStarted;
    UINT uFmt = upTime.GetDays() > 0 ? IDS_UPTIME_DAYS : IDS_UPTIME_DAY;
    CString strUpTime = upTime.Format(uFmt);
    pCmdUI->SetText(strUpTime);

}


void CJLSrvrDoc::OnUpdateConnects(CCmdUI* pCmdUI)
{
    CString strText;
    strText.Format(ID_INDICATOR_CONNECTS, m_ClientList.GetCount());
    pCmdUI->SetText(strText);
}


void CJLSrvrDoc::OnFileRestart()
{
    // this will close the connection if it's already open
    // before starting again....
    StartListening();
}


BOOL CJLSrvrDoc::OnNewDocument()
{
    if(!CDocument::OnNewDocument())
    {
        return FALSE;
    }

    BOOL bRet = FALSE;

    if(!m_pDB)
    {
        m_pDB = new CDatabase;
    }


    TRY
    {
        bRet = m_pDB->OpenEx(NULL, CDatabase::openReadOnly);
        if(bRet)
        {
            bRet = StartListening();
            SetTitle(NULL);
        }

    }
    CATCH(CDBException, e)
    {
        if(AfxMessageBox(IDS_DB_OPENERROR, MB_YESNO) == IDNO)
        {
            delete m_pDB;
        }

    }
    END_CATCH


    return bRet;
}


void CJLSrvrDoc::StopListening()
{
    if(m_pListen != NULL)
    {
        m_pListen->Close();
        delete m_pListen;
        m_pListen = NULL;
    }
}

BOOL CJLSrvrDoc::isLogined(TCHAR* szUserName)
{
    POSITION pos = m_ClientList.GetHeadPosition();
    while(pos != NULL)
    {
        CRequestSocket* pSocket = (CRequestSocket*)m_ClientList.GetAt(pos);
        if(strcmp(szUserName, pSocket->m_szName) == 0)
        {
            return TRUE;
        }
        m_ClientList.GetNext(pos);
    }

    return FALSE;
}

void CJLSrvrDoc::SetTitle(LPCTSTR lpszTitle)
{
    CString strTitle;
    if(lpszTitle != NULL)
    {
        m_strTitleBase = lpszTitle;
    }

    if(m_strServer.IsEmpty())
    {
        strTitle = m_strTitleBase;
    }
    else if(m_pListen == NULL)
    {
        strTitle.Format(IDS_INVALID, m_strTitleBase);
    }
    else
    {
        strTitle.Format(IDS_DOCTITLE_NOPORT, m_strTitleBase, m_strServer);
    }

    CDocument::SetTitle(strTitle);
}


BOOL CJLSrvrDoc::StartListening()
{
    BOOL bOk = FALSE;
    StopListening();
    m_pListen = new CListenSocket(this);
    if(m_pListen)
    {
        if(m_pListen->Create(PORT_SRV, SOCK_STREAM, FD_ACCEPT))
        {
            bOk = m_pListen->Listen();
        }

        if(!bOk)
        {
            CString strMsg;
            int nErr = m_pListen->GetLastError();
            if(nErr == WSAEADDRINUSE)
            {
                strMsg.Format(IDS_LISTEN_INUSE, PORT_SRV);
            }
            else
            {
                strMsg.Format(IDS_LISTEN_ERROR, PORT_SRV);
            }

            AfxMessageBox(strMsg, MB_OK | MB_ICONSTOP);
            delete m_pListen;
            m_pListen = NULL;
        }
    }
    else
    {
        AfxMessageBox(IDS_CANT_LISTEN, MB_OK | MB_ICONSTOP);
    }

    m_timeStarted = CTime::GetCurrentTime();

    return bOk;
}

/////////////////////////////////////////////////////////////////////////////
// CJLSrvrDoc serialization

void CJLSrvrDoc::Serialize(CArchive& ar)
{
    if(ar.IsStoring())
    {
        // TODO: add storing code here
    }
    else
    {
        // TODO: add loading code here
    }
}

/////////////////////////////////////////////////////////////////////////////
// CJLSrvrDoc diagnostics

#ifdef _DEBUG
void CJLSrvrDoc::AssertValid() const
{
    CDocument::AssertValid();
}

void CJLSrvrDoc::Dump(CDumpContext& dc) const
{
    CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CJLSrvrDoc commands


//接受连接, 放到客户列表, 通知视图更新
void CJLSrvrDoc::ClientAccept()
{
    CRequestSocket* pClientSock = new CRequestSocket(this);

    SOCKADDR_IN soaddr;
    int len = sizeof(soaddr);
    if(m_pListen->Accept(*pClientSock, (SOCKADDR*)&soaddr, &len))
    {
        pClientSock->AsyncSelect(FD_READ | FD_CLOSE);
        pClientSock->InitAccept(soaddr);
        m_ClientList.AddTail(pClientSock);

    }
    else
    {
        delete pClientSock;

    }

}


//从客户列中删掉自己
void CJLSrvrDoc::ClientClose(CRequestSocket* pSock)
{

    POSITION pos = m_ClientList.GetHeadPosition();
    while(pos != NULL)
    {
        CRequestSocket* pSocket = (CRequestSocket*)m_ClientList.GetAt(pos);
        if(pSocket == pSock)
        {
            m_ClientList.RemoveAt(pos);
            DocHit(HINT_OFFLINE, pSocket->m_pRequest);
            delete pSocket;
            return;
        }
        m_ClientList.GetNext(pos);
    }

}

void CJLSrvrDoc::DocHit(LPARAM lHint, CRequest* m_pRequest)
{
    UpdateAllViews(NULL, lHint, m_pRequest);
}


void CJLSrvrDoc::OnCloseDocument()
{
    // TODO: Add your specialized code here and/or call the base class
    StopListening();
    if(m_pDB)
    {
        delete m_pDB;
    }

    CDocument::OnCloseDocument();
}
