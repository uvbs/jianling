#pragma once

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN		// �� Windows ��ͷ���ų�����ʹ�õ�����
#endif

#ifndef WINVER
#define WINVER 0x0501
#endif

#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0501	
#endif

// Insert your headers here
#define	_CRT_SECURE_NO_WARNINGS	//�ص���ȫ��ľ���

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
#pragma comment(lib, "dbghelp")


#pragma warning(once:4127)
#pragma warning(once:4100)
#pragma warning(once:4701)
#pragma warning(once:4703)
#pragma warning(once:4702)

#pragma warning(disable: 4018)
#pragma warning(disable: 4996)


