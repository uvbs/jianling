// MyWork.cpp: implementation of the CMyWork class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Jlkit.h"
#include "CVPNFile.h"
#include "JLkitView.h"
#include "MyWork.h"

#include "..\common\Lock.h"
#include "..\common\webpost.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

MyCWork::MyCWork(int item, CJLkitView *pFrame)
{
    m_lpLock = new CLock();
	nItem = item;
	m_pFrame = pFrame;
}

MyCWork::~MyCWork()
{

}

void MyCWork::DoWork()
{
    Webpost::InitCom();

    CListCtrl &m_ListCtrl = m_pFrame->GetListCtrl();
 

    CString strName = m_ListCtrl.GetItemText(nItem, 0);
    CString strPw = m_ListCtrl.GetItemText(nItem, 1);
    
    CString strLine = strName + _T(", ") + strPw + _T("\n");
    Webpost poster(strName, strPw);
    
    int LoginTimes = 0;
    BOOL bWriteOnce = TRUE;
    while(1){
        m_ListCtrl.SetItemText(nItem, COLUMN_TEXT_STATUS, _T("���ڵ�¼"));
        int nResult = poster.Login();
        if(nResult == RESULT_SUCCESS){
            m_ListCtrl.SetItemText(nItem, COLUMN_TEXT_STATUS, _T("������ȡ����"));
            nResult = poster.Get();
            if(nResult == RESULT_GET_ERROR){
                m_ListCtrl.SetItemText(nItem, COLUMN_TEXT_STATUS, _T("��ȡʧ��"));
                
                if(bWriteOnce){
//                    m_pFrame->LogToErrorFile(strLine);
                    bWriteOnce = FALSE;
                }
                
            }
            else if(nResult == RESULT_GET_ALEADY){
                m_ListCtrl.SetItemText(nItem, COLUMN_TEXT_STATUS, _T("�Ѿ���ȡ"));
            }
            else if(nResult == RESULT_SUCCESS){
                m_ListCtrl.SetItemText(nItem, COLUMN_TEXT_STATUS, _T("��ȡ���"));
            }
            
            
            nResult = poster.Active();
            if(nResult == RESULT_SUCCESS){
                m_ListCtrl.SetItemText(nItem, COLUMN_TEXT_STATUS, _T("�������"));
            }
            else if(nResult == RESULT_FAIL_TIMEOUT){
                m_ListCtrl.SetItemText(nItem, COLUMN_TEXT_STATUS, _T("���ʱ"));
                if(bWriteOnce){
                //    m_pFrame->LogToErrorFile(strLine);
                    bWriteOnce = FALSE;
                }
            }
            else if(nResult == RESULT_FAIL_NOACTIVEITEMS){
                m_ListCtrl.SetItemText(nItem, COLUMN_TEXT_STATUS, _T("���輤��"));
            }
            else if(nResult == RESULT_FAIL_ACTIVEITEMSERR){
                m_ListCtrl.SetItemText(nItem, COLUMN_TEXT_STATUS, _T("����ʧ��"));
                if(bWriteOnce){
                 //   m_pFrame->LogToErrorFile(strLine);
                    bWriteOnce = FALSE; 
                }
            }
            
            
            break;
        }
        else{
            //��ʱ���β���
            if(nResult == RESULT_FAIL_TIMEOUT){
                m_ListCtrl.SetItemText(nItem, COLUMN_TEXT_STATUS, _T("��ʱ"));	
                
                LoginTimes++;
                TRACE(_T("ʧ��һ��"));
                if(LoginTimes == 2){
//                    m_pFrame->ChangeVPN();
                    LoginTimes = 0;
                }
            }
            else if(nResult == RESULT_FAIL_CAPTCHA){
                m_ListCtrl.SetItemText(nItem, COLUMN_TEXT_STATUS, _T("��Ҫ��֤��"));
      //          m_pFrame->ChangeVPN();
                LoginTimes = 0;
            }
            else if(nResult == RESULT_FAIL_IPBLOCK){
                m_ListCtrl.SetItemText(nItem, COLUMN_TEXT_STATUS, _T("IP BLOCK"));
          //      m_pFrame->ChangeVPN();
                LoginTimes = 0;
            }
            else if(nResult == RESULT_FAIL_PWERROR){
                m_ListCtrl.SetItemText(nItem, COLUMN_TEXT_STATUS, _T("�������"));
                if(bWriteOnce){
                    strLine.Remove(_T('\n'));
                    strLine += _T(" : �������");
                    strLine += _T("\n");
               //     m_pFrame->LogToErrorFile(strLine);
                    bWriteOnce = FALSE;
                }
                break;
            }
            else{
                m_ListCtrl.SetItemText(nItem, COLUMN_TEXT_STATUS, _T("��¼ʧ��"));
                TRACE(_T("ʧ��%d��"), LoginTimes++);
                if(LoginTimes == 2){
       //             m_pFrame->ChangeVPN();
                    LoginTimes = 0;
                }
            }
        }
    }

    Webpost::UnInitCom();
	delete this;
}

