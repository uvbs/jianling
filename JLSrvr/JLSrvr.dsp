# Microsoft Developer Studio Project File - Name="JLSrvr" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=JLSRVR - WIN32 RELEASE
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "JLSrvr.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "JLSrvr.mak" CFG="JLSRVR - WIN32 RELEASE"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "JLSrvr - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe
# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MDd /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_UNICODE" /FR /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /entry:"wWinMainCRTStartup" /subsystem:windows /debug /machine:I386 /out:"..\bin\JLSrvr.exe"
# SUBTRACT LINK32 /pdb:none
# Begin Target

# Name "JLSrvr - Win32 Release"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\common\CallTracer.cpp
# End Source File
# Begin Source File

SOURCE=.\DbMngr.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgAcInfo.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgAcKey.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgAcKeylog.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgKeyAdd.cpp
# End Source File
# Begin Source File

SOURCE=.\JLSrvr.cpp
# End Source File
# Begin Source File

SOURCE=.\JLSrvr.rc
# End Source File
# Begin Source File

SOURCE=.\JLSrvrDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\JLSrvrView.cpp
# End Source File
# Begin Source File

SOURCE=.\ListenSocket.cpp
# End Source File
# Begin Source File

SOURCE=..\common\logger.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\RecordAc.cpp
# End Source File
# Begin Source File

SOURCE=.\RecordKey.cpp
# End Source File
# Begin Source File

SOURCE=.\RecordKeyLog.cpp
# End Source File
# Begin Source File

SOURCE=.\Request.cpp
# End Source File
# Begin Source File

SOURCE=.\RequestSocket.cpp
# End Source File
# Begin Source File

SOURCE=.\RequestView.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\common\CallTracer.h
# End Source File
# Begin Source File

SOURCE=.\DbMngr.h
# End Source File
# Begin Source File

SOURCE=.\DlgAcInfo.h
# End Source File
# Begin Source File

SOURCE=.\DlgAcKey.h
# End Source File
# Begin Source File

SOURCE=.\DlgAcKeylog.h
# End Source File
# Begin Source File

SOURCE=.\DlgKeyAdd.h
# End Source File
# Begin Source File

SOURCE=.\JLSrvr.h
# End Source File
# Begin Source File

SOURCE=.\JLSrvrDoc.h
# End Source File
# Begin Source File

SOURCE=.\JLSrvrView.h
# End Source File
# Begin Source File

SOURCE=.\ListenSocket.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\RecordAc.h
# End Source File
# Begin Source File

SOURCE=.\RecordKey.h
# End Source File
# Begin Source File

SOURCE=.\RecordKeyLog.h
# End Source File
# Begin Source File

SOURCE=.\Request.h
# End Source File
# Begin Source File

SOURCE=.\RequestSocket.h
# End Source File
# Begin Source File

SOURCE=.\RequestView.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\sockinfo.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\default1.bin
# End Source File
# Begin Source File

SOURCE=.\res\JLSrvr.ico
# End Source File
# Begin Source File

SOURCE=.\res\JLSrvr.rc2
# End Source File
# Begin Source File

SOURCE=.\res\JLSrvrDoc.ico
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar.bmp
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
