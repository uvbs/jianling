#pragma once


#define VC_EXTRALEAN		// 从 Windows 标头中排除不常使用的资料


#define	_WIN32_WINNT    0x501
#define WINVER          0x501
#define _CRT_SECURE_NO_WARNINGS


#include <afxwin.h>         // MFC core and standard components
#include <afxcview.h>       // MFC view
#include <afxext.h>         // MFC extensions
#include <afxdb.h>          // MFC db
#include <afxinet.h>        // MFC internet
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