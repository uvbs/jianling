// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__428CBD86_0EF0_4A61_ACB2_0FA05787D810__INCLUDED_)
#define AFX_STDAFX_H__428CBD86_0EF0_4A61_ACB2_0FA05787D810__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#define _WIN32_WINNT 0x501



#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxsock.h>
#include <afxole.h>
#include <afxinet.h>
#define _WIN32_WINNT 0x501

#define DIRECT3D_VERSION         0x0900

#include <d3d9.h>

#include <IPHlpApi.h>
#include <Psapi.h>
#include <NtDDNdis.h>


#include <shlwapi.h>

#include <DbgHelp.h>

#pragma comment(lib, "Iphlpapi")
#pragma comment(lib, "shlwapi")
#pragma comment(lib, "Psapi")
#pragma comment(lib, "dbghelp")
#pragma warning(disable : 4786)



#include <atlconv.h>



//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__428CBD86_0EF0_4A61_ACB2_0FA05787D810__INCLUDED_)
