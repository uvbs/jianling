#pragma once


#define VC_EXTRALEAN        // 从 Windows 标头中排除不常使用的资料

#define _WIN32_WINNT 0x501

#define _CRT_SECURE_NO_WARNINGS

#pragma warning(disable: 4018)
#pragma warning(disable: 4996)
#pragma warning(disable: 4786)


#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>
#include <afxcview.h>       // MFC view
#include <afxinet.h>        // MFC internet
#include <afxtempl.h>
#include <afxmt.h>
#include <atlbase.h>
#include <afxsock.h>        // MFC socket
#ifndef _AFX_NO_AFXCMN_SUPPORT
    #include <afxcmn.h>         // MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT



#include <Tlhelp32.h>
#include <NB30.H>


#include <Shlwapi.h>
#pragma comment(lib, "shlwapi")



#include <string>
#include <sstream>
#include <vector>
#include <queue>


#include "..\common\protocol.h"
#include "..\common\common.h"
#include "..\common\webpost.h"
#include "..\common\Inject.h"
#include "..\common\Lock.h"
#include "..\common\WHService.h"

#include "..\第三方库\SimpleIni\SimpleIni.h"

