#pragma once


#define VC_EXTRALEAN		// �� Windows ��ͷ���ų�����ʹ�õ�����


#define	_WIN32_WINNT    0x501
#define WINVER          0x501
#define _CRT_SECURE_NO_WARNINGS

#pragma comment(linker, "/OPT:NOWIN98")

#include <afxwin.h>         // MFC core and standard components
#include <afxcview.h>       // MFC view
#include <afxinet.h>        // MFC internet
#include <afxmt.h>
#include <atlbase.h>
#include <afxsock.h>        // MFC socket
#ifndef _AFX_NO_AFXCMN_SUPPORT
    #include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT
#include <afxdao.h>


#include <assert.h>
#include <direct.h>
#include <Iphlpapi.h>
#include <vector>
#include <queue>
#include <Tlhelp32.h>
#include <Shlwapi.h>
#pragma comment(lib, "shlwapi")


#pragma warning(disable: 4018)
#pragma warning(disable: 4996)