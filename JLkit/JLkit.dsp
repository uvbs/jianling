# Microsoft Developer Studio Project File - Name="JLkit" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=JLKIT - WIN32 RELEASE
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "JLkit.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "JLkit.mak" CFG="JLKIT - WIN32 RELEASE"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "JLkit - Win32 Release" (based on "Win32 (x86) Application")
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
# ADD CPP /nologo /MDd /W3 /GX /Zi /Od /Gf /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_AFXDLL" /FR /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /pdb:"..\bin\JLkit.pdb" /debug /machine:I386 /out:"..\bin\JLkit.exe"
# SUBTRACT LINK32 /profile /pdb:none /map
# Begin Target

# Name "JLkit - Win32 Release"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\BindKeyDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\BugRepDlg.cpp
# End Source File
# Begin Source File

SOURCE=..\common\CallTracer.cpp
# End Source File
# Begin Source File

SOURCE=.\ConfigMgr.cpp
# End Source File
# Begin Source File

SOURCE=.\CVPNFile.cpp
# End Source File
# Begin Source File

SOURCE=..\common\Inject.cpp
# End Source File
# Begin Source File

SOURCE=.\JLkit.cpp
# End Source File
# Begin Source File

SOURCE=.\JLkitDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\JLkitSocket.cpp
# End Source File
# Begin Source File

SOURCE=.\JLkitView.cpp
# End Source File
# Begin Source File

SOURCE=..\common\Job.cpp
# End Source File
# Begin Source File

SOURCE=.\Keyviewdlg.cpp
# End Source File
# Begin Source File

SOURCE=.\LaunchGameThread.cpp
# End Source File
# Begin Source File

SOURCE=..\common\logger.cpp
# End Source File
# Begin Source File

SOURCE=.\logindlg.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\Modifybind.cpp
# End Source File
# Begin Source File

SOURCE=.\registdlg.cpp
# End Source File
# Begin Source File

SOURCE=.\settingdlg.cpp
# End Source File
# Begin Source File

SOURCE=..\common\ShareMem.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=..\common\webpost.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\BindKeyDlg.h
# End Source File
# Begin Source File

SOURCE=.\BugRepDlg.h
# End Source File
# Begin Source File

SOURCE=..\common\CallTracer.h
# End Source File
# Begin Source File

SOURCE=.\ConfigMgr.h
# End Source File
# Begin Source File

SOURCE=.\CVPNFile.h
# End Source File
# Begin Source File

SOURCE=..\common\inject.h
# End Source File
# Begin Source File

SOURCE=.\JLkit.h
# End Source File
# Begin Source File

SOURCE=.\JLkitDoc.h
# End Source File
# Begin Source File

SOURCE=.\JLkitSocket.h
# End Source File
# Begin Source File

SOURCE=.\JLkitView.h
# End Source File
# Begin Source File

SOURCE=..\common\Job.h
# End Source File
# Begin Source File

SOURCE=.\Keyviewdlg.h
# End Source File
# Begin Source File

SOURCE=.\LaunchGameThread.h
# End Source File
# Begin Source File

SOURCE=..\common\Lock.h
# End Source File
# Begin Source File

SOURCE=..\common\logger.h
# End Source File
# Begin Source File

SOURCE=.\logindlg.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\Modifybind.h
# End Source File
# Begin Source File

SOURCE=.\registdlg.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\settingdlg.h
# End Source File
# Begin Source File

SOURCE=..\common\ShareMem.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=..\common\webpost.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\default1.bin
# End Source File
# Begin Source File

SOURCE=.\res\JLkit.ico
# End Source File
# Begin Source File

SOURCE=.\JLkit.rc
# End Source File
# Begin Source File

SOURCE=.\res\JLkit.rc2
# End Source File
# End Group
# Begin Source File

SOURCE=.\res\JLnp.dll
# End Source File
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
