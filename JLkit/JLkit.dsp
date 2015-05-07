# Microsoft Developer Studio Project File - Name="JLkit" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=JLKIT - WIN32 JLTW
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "JLkit.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "JLkit.mak" CFG="JLKIT - WIN32 JLTW"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "JLkit - Win32 JLTW" (based on "Win32 (x86) Application")
!MESSAGE "JLkit - Win32 JLHF" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "JLkit - Win32 JLTW"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "JLkit___Win32_JLTW"
# PROP BASE Intermediate_Dir "JLkit___Win32_JLTW"
# PROP BASE Ignore_Export_Lib 1
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "JLTW"
# PROP Intermediate_Dir "JLTW"
# PROP Ignore_Export_Lib 1
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_UNICODE" /D "UNICODE" /D "_AFXDLL" /D "JLTW" /FAs /Yu"stdafx.h" /FD /c
# SUBTRACT BASE CPP /Gf /Fr
# ADD CPP /nologo /MDd /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_UNICODE" /D "UNICODE" /D "_AFXDLL" /D "JLTW" /FAs /Yu"stdafx.h" /FD /c
# SUBTRACT CPP /Gf /Fr
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /entry:"wWinMainCRTStartup" /subsystem:windows /debug /machine:I386 /out:"..\bin\JLkit.exe"
# SUBTRACT BASE LINK32 /profile /map
# ADD LINK32 /nologo /entry:"wWinMainCRTStartup" /subsystem:windows /pdb:"../bin/JLkit_tw.pdb" /debug /machine:I386 /out:"..\bin\JLkit_tw.exe"
# SUBTRACT LINK32 /profile /pdb:none /map

!ELSEIF  "$(CFG)" == "JLkit - Win32 JLHF"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "JLkit___Win32_JLHF"
# PROP BASE Intermediate_Dir "JLkit___Win32_JLHF"
# PROP BASE Ignore_Export_Lib 1
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "JLHF"
# PROP Intermediate_Dir "JLHF"
# PROP Ignore_Export_Lib 1
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_UNICODE" /D "UNICODE" /D "_AFXDLL" /D "JLTW" /FAs /Yu"stdafx.h" /FD /c
# SUBTRACT BASE CPP /Gf /Fr
# ADD CPP /nologo /MDd /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_UNICODE" /D "UNICODE" /D "_AFXDLL" /D "JLTW" /FAs /Yu"stdafx.h" /FD /c
# SUBTRACT CPP /Gf /Fr
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /entry:"wWinMainCRTStartup" /subsystem:windows /pdb:"../bin/JLkit_tw.pdb" /debug /machine:I386 /out:"..\bin\JLkit_tw.exe"
# SUBTRACT BASE LINK32 /profile /pdb:none /map
# ADD LINK32 /nologo /entry:"wWinMainCRTStartup" /subsystem:windows /pdb:"../bin/JLkit_tw.pdb" /debug /machine:I386 /out:"..\bin\JLkit_tw.exe"
# SUBTRACT LINK32 /profile /pdb:none /map

!ENDIF 

# Begin Target

# Name "JLkit - Win32 JLTW"
# Name "JLkit - Win32 JLHF"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\BindKeyDlg.cpp
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

SOURCE=.\logindlg.cpp
# End Source File
# Begin Source File

SOURCE=.\LoginSheet.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\MsgBox.cpp
# End Source File
# Begin Source File

SOURCE=..\common\MSJEXHND.cpp
# End Source File
# Begin Source File

SOURCE=.\registdlg.cpp
# End Source File
# Begin Source File

SOURCE=.\settingdlg.cpp
# End Source File
# Begin Source File

SOURCE=.\StatusBox.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=..\common\webpost.cpp
# End Source File
# Begin Source File

SOURCE=..\common\WHService.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\BindKeyDlg.h
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

SOURCE=.\Keyviewdlg.h
# End Source File
# Begin Source File

SOURCE=.\logindlg.h
# End Source File
# Begin Source File

SOURCE=.\LoginSheet.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\MsgBox.h
# End Source File
# Begin Source File

SOURCE=..\common\MSJEXHND.h
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

SOURCE=.\StatusBox.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=..\common\webpost.h
# End Source File
# Begin Source File

SOURCE=..\common\WHService.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\BnSClient.ico
# End Source File
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
# Begin Source File

SOURCE=.\res\title.bmp
# End Source File
# Begin Source File

SOURCE=.\res\toolbar1.bmp
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
