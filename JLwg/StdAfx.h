#pragma once

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN		// 从 Windows 标头中排除不常使用的资料
#endif

// 如果您必须使用下列所指定的平台之前的平台，则修改下面的定义。
// 有关不同平台的相应值的最新信息，请参考 MSDN。
#ifndef WINVER				// 允许使用 Windows 95 和 Windows NT 4 或更高版本的特定功能。
#define WINVER 0x0501		//为 Windows98 和 Windows 2000 及更新版本改变为适当的值。
#endif

#ifndef _WIN32_WINNT		// 允许使用 Windows NT 4 或更高版本的特定功能。
#define _WIN32_WINNT 0x0501		//为 Windows98 和 Windows 2000 及更新版本改变为适当的值。
#endif

// Insert your headers here
#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers
#define	_CRT_SECURE_NO_WARNINGS	//关掉安全类的警告




#include <afxwin.h>
#include <afxcmn.h>
#include <afxdlgs.h>
#include <assert.h>
#include <DbgHelp.h>
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

#pragma warning(once:4127)
#pragma warning(once:4100)
#pragma warning(once:4701)
#pragma warning(once:4703)
#pragma warning(once:4702)

#pragma warning(disable: 4018)
#pragma warning(disable: 4996)


