#pragma once

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN        // 从 Windows 标头中排除不常使用的资料
#endif

#define _WIN32_WINNT 0x501

// Insert your headers here
#define _CRT_SECURE_NO_WARNINGS //关掉安全类的警告

#pragma warning(disable: 4786)
#pragma warning(disable: 4503)
#pragma warning(once:4127)
#pragma warning(once:4100)
#pragma warning(once:4701)
#pragma warning(once:4703)
#pragma warning(once:4702)
#pragma warning(disable:4099)
#pragma warning(disable:4018)
#pragma warning(disable:4996)



#include <afxwin.h>
#include <afxcmn.h>
#include <afxdlgs.h>

#include <afxsock.h>
#include <afxmt.h>

#include <atlbase.h>
#include <atlconv.h>

#include <stdarg.h>
#include <string>
#include <sstream>


#include <locale.h>
#include <process.h>
#include <tchar.h>
#include <cmath>
#include <vector>
#include <algorithm>
#include <functional>
#include <TlHelp32.h>
#include <Shlwapi.h>

#pragma comment(lib, "shlwapi")



#include "..\common\protocol.h"
#include "..\common\common.h"
#include "..\common\CHook.h"
#include "..\common\logger.h"
#include "..\common\inject.h"
#include "..\common\inlinehook.h"

#include "..\第三方库\SimpleIni\SimpleIni.h"

extern "C"
{
#include "..\第三方库\lua52\lua.h"
#include "..\第三方库\lua52\lauxlib.h"
}

#ifdef _DEBUG
#pragma comment(lib, "..\\第三方库\\lua52\\lib\\lua52d")
#else
#pragma comment(lib, "..\\第三方库\\lua52\\lib\\lua52")
#endif