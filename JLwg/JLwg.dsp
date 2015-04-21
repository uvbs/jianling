# Microsoft Developer Studio Project File - Name="JLwg" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=JLWG - WIN32 RELEASE
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "JLwg.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "JLwg.mak" CFG="JLWG - WIN32 RELEASE"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "JLwg - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "JLwg - Win32 JLTW" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "JLwg - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 1
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "JLWG_EXPORTS" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MDd /W3 /GX /Zi /Od /Gf /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_UNICODE" /D "UNICODE" /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /FA /Yu"stdafx.h" /FD /c
# SUBTRACT CPP /Fr
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "NDEBUG"
# ADD RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386
# ADD LINK32 comctl32.lib /nologo /dll /debug /machine:I386 /out:"..\bin\JLwg.dll"
# SUBTRACT LINK32 /profile /pdb:none /map

!ELSEIF  "$(CFG)" == "JLwg - Win32 JLTW"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "JLwg___Win32_JLTW"
# PROP BASE Intermediate_Dir "JLwg___Win32_JLTW"
# PROP BASE Ignore_Export_Lib 1
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "JLTW"
# PROP Intermediate_Dir "JLTW"
# PROP Ignore_Export_Lib 1
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /GX /Zi /Od /Gf /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_UNICODE" /D "UNICODE" /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /D "JLTW" /FA /Yu"stdafx.h" /FD /c
# SUBTRACT BASE CPP /Fr
# ADD CPP /nologo /MDd /W3 /GX /Zi /Od /Gf /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_UNICODE" /D "UNICODE" /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /D "JLTW" /FA /Yu"stdafx.h" /FD /c
# SUBTRACT CPP /Fr
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 comctl32.lib /nologo /dll /debug /machine:I386 /out:"..\bin\JLwg.dll"
# SUBTRACT BASE LINK32 /profile /pdb:none /map
# ADD LINK32 /nologo /dll /pdb:"../bin/JLwg_tw.pdb" /debug /machine:I386 /out:"..\bin\JLwg_tw.dll"
# SUBTRACT LINK32 /pdb:none

!ENDIF 

# Begin Target

# Name "JLwg - Win32 Release"
# Name "JLwg - Win32 JLTW"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\common\CHook.cpp
# End Source File
# Begin Source File

SOURCE=.\ConfigItemPage.cpp
# End Source File
# Begin Source File

SOURCE=.\ConfigObjPage.cpp
# End Source File
# Begin Source File

SOURCE=.\ConfigPartyPage.cpp
# End Source File
# Begin Source File

SOURCE=.\ConfigQhPage.cpp
# End Source File
# Begin Source File

SOURCE=.\DataDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\gamecall.cpp
# End Source File
# Begin Source File

SOURCE=.\GamecallEx.cpp
# End Source File
# Begin Source File

SOURCE=.\GameConfig.cpp
# End Source File
# Begin Source File

SOURCE=.\GameHook.cpp
# End Source File
# Begin Source File

SOURCE=.\GameLog.cpp
# End Source File
# Begin Source File

SOURCE=.\GameSpend.cpp
# End Source File
# Begin Source File

SOURCE=.\JLDlg.cpp
# End Source File
# Begin Source File

SOURCE=..\JLkit\JLkitSocket.cpp
# End Source File
# Begin Source File

SOURCE=.\JLwg.cpp
# End Source File
# Begin Source File

SOURCE=..\common\LDasm.cpp
# End Source File
# Begin Source File

SOURCE=..\common\logger.cpp
# End Source File
# Begin Source File

SOURCE=..\common\MSJEXHND.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\TaskScript.cpp
# End Source File
# Begin Source File

SOURCE=.\TaskScript1.cpp
# End Source File
# Begin Source File

SOURCE=.\TaskScript2.cpp
# End Source File
# Begin Source File

SOURCE=.\TranScript.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\common\CHook.h
# End Source File
# Begin Source File

SOURCE=..\common\common.h
# End Source File
# Begin Source File

SOURCE=.\ConfigItemPage.h
# End Source File
# Begin Source File

SOURCE=.\ConfigObjPage.h
# End Source File
# Begin Source File

SOURCE=.\ConfigPartyPage.h
# End Source File
# Begin Source File

SOURCE=.\ConfigQhPage.h
# End Source File
# Begin Source File

SOURCE=.\DataDlg.h
# End Source File
# Begin Source File

SOURCE=.\gamecall.h
# End Source File
# Begin Source File

SOURCE=.\GamecallEx.h
# End Source File
# Begin Source File

SOURCE=.\GameConfig.h
# End Source File
# Begin Source File

SOURCE=.\gamedef.h
# End Source File
# Begin Source File

SOURCE=.\GameHook.h
# End Source File
# Begin Source File

SOURCE=.\GameLog.h
# End Source File
# Begin Source File

SOURCE=.\GameSpend.h
# End Source File
# Begin Source File

SOURCE=.\gamestruct.h
# End Source File
# Begin Source File

SOURCE=.\JLDlg.h
# End Source File
# Begin Source File

SOURCE=.\JLkitDoc.h
# End Source File
# Begin Source File

SOURCE=..\JLkit\JLkitSocket.h
# End Source File
# Begin Source File

SOURCE=.\JLwg.h
# End Source File
# Begin Source File

SOURCE=..\common\LDasm.h
# End Source File
# Begin Source File

SOURCE=..\common\logger.h
# End Source File
# Begin Source File

SOURCE=..\common\MSJEXHND.h
# End Source File
# Begin Source File

SOURCE=.\resource.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\TaskScript.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\default1.bin
# End Source File
# Begin Source File

SOURCE=.\res\default1.bin
# End Source File
# Begin Source File

SOURCE=.\JLwg.rc
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
