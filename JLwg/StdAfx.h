#pragma once

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN		// �� Windows ��ͷ���ų�����ʹ�õ�����
#endif

// ���������ʹ��������ָ����ƽ̨֮ǰ��ƽ̨�����޸�����Ķ��塣
// �йز�ͬƽ̨����Ӧֵ��������Ϣ����ο� MSDN��
#ifndef WINVER				// ����ʹ�� Windows 95 �� Windows NT 4 ����߰汾���ض����ܡ�
#define WINVER 0x0501		//Ϊ Windows98 �� Windows 2000 �����°汾�ı�Ϊ�ʵ���ֵ��
#endif

#ifndef _WIN32_WINNT		// ����ʹ�� Windows NT 4 ����߰汾���ض����ܡ�
#define _WIN32_WINNT 0x0501		//Ϊ Windows98 �� Windows 2000 �����°汾�ı�Ϊ�ʵ���ֵ��
#endif

// Insert your headers here
#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers
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

#pragma warning(once:4127)
#pragma warning(once:4100)
#pragma warning(once:4701)
#pragma warning(once:4703)
#pragma warning(once:4702)

#pragma warning(disable: 4018)
#pragma warning(disable: 4996)


