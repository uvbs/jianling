; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CJLkitView
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "jlkit.h"
LastPage=0

ClassCount=13
Class1=CBindKeyDlg
Class2=CBugRepDlg
Class3=CCFileDialog
Class4=CJLkitApp
Class5=CJLkitDoc
Class6=CJLkitView
Class7=KeyViewDlg
Class8=CLaunchGameThread
Class9=CLoginDlg
Class10=CMainFrame
Class11=RegistDlg
Class12=SettingDlg
Class13=CWaitDlg

ResourceCount=10
Resource1=IDD_INFO
Resource2=IDD_REPORTBUG
Resource3=IDD_MODIFYBIND
Resource4=IDD_KEY
Resource5=IDD_BINDKEY
Resource6=IDD_SETTING
Resource7=IDD_REGISTER
Resource8=IDR_KEY
Resource9=IDD_LOGIN
Resource10=IDR_MAINFRAME

[CLS:CBindKeyDlg]
Type=0
BaseClass=CDialog
HeaderFile=BindKeyDlg.h
ImplementationFile=BindKeyDlg.cpp
LastObject=CBindKeyDlg

[CLS:CBugRepDlg]
Type=0
BaseClass=CDialog
HeaderFile=BugRepDlg.h
ImplementationFile=BugRepDlg.cpp
Filter=D
VirtualFilter=dWC

[CLS:CCFileDialog]
Type=0
BaseClass=CFileDialog
HeaderFile=CFileDialog.h
ImplementationFile=CFileDialog.cpp

[CLS:CJLkitApp]
Type=0
BaseClass=CWinApp
HeaderFile=JLkit.h
ImplementationFile=JLkit.cpp
Filter=N
VirtualFilter=AC

[CLS:CJLkitDoc]
Type=0
BaseClass=CDocument
HeaderFile=JLkitDoc.h
ImplementationFile=JLkitDoc.cpp
LastObject=CJLkitDoc
Filter=N
VirtualFilter=DC

[CLS:CJLkitView]
Type=0
BaseClass=CListView
HeaderFile=JLkitView.h
ImplementationFile=JLkitView.cpp
Filter=C
VirtualFilter=VWC
LastObject=ID_START

[CLS:KeyViewDlg]
Type=0
BaseClass=CDialog
HeaderFile=Keyviewdlg.h
ImplementationFile=Keyviewdlg.cpp
LastObject=ID_ACTIVE

[CLS:CLaunchGameThread]
Type=0
BaseClass=CWinThread
HeaderFile=LaunchGameThread.h
ImplementationFile=LaunchGameThread.cpp
Filter=N
VirtualFilter=TC

[CLS:CLoginDlg]
Type=0
BaseClass=CDialog
HeaderFile=Logindlg.h
ImplementationFile=Logindlg.cpp
Filter=D
VirtualFilter=dWC

[CLS:CMainFrame]
Type=0
BaseClass=CFrameWnd
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=W
VirtualFilter=fWC

[CLS:RegistDlg]
Type=0
BaseClass=CDialog
HeaderFile=Registdlg.h
ImplementationFile=Registdlg.cpp

[CLS:SettingDlg]
Type=0
BaseClass=CDialog
HeaderFile=Settingdlg.h
ImplementationFile=Settingdlg.cpp

[CLS:CWaitDlg]
Type=0
BaseClass=CDialog
HeaderFile=Waitdlg.h
ImplementationFile=Waitdlg.cpp

[DLG:IDD_BINDKEY]
Type=1
Class=CBindKeyDlg
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDC_BINDKEY,edit,1342242820
Control3=IDCANCEL,button,1342242816

[DLG:IDD_KEY]
Type=1
Class=KeyViewDlg
ControlCount=1
Control1=IDC_LISTKEY,SysListView32,1350633473

[DLG:IDD_LOGIN]
Type=1
Class=CLoginDlg
ControlCount=9
Control1=IDC_EDITNAME,edit,1350631552
Control2=IDC_EDITPASSWORD,edit,1350631584
Control3=IDOK,button,1342242817
Control4=IDCANCEL,button,1342242816
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352
Control7=IDC_BUTTONREGISTER,button,1342242816
Control8=IDC_BTNMODIFYBIND,button,1342242816
Control9=IDC_REMPASSWORD,button,1342242819

[DLG:IDD_REGISTER]
Type=1
Class=RegistDlg
ControlCount=8
Control1=IDC_IPADDRESS,SysIPAddress32,1342242816
Control2=IDC_EDITUSERNAME,edit,1350631552
Control3=IDC_EDITPASSWORD,edit,1350631552
Control4=IDOK,button,1342242817
Control5=IDC_STATIC,static,1342308352
Control6=IDCANCEL,button,1342242816
Control7=IDC_STATIC,static,1342308352
Control8=IDC_STATIC,static,1342308352

[DLG:IDD_SETTING]
Type=1
Class=SettingDlg
ControlCount=5
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_GAMEPATH,edit,1350631552
Control4=IDC_STATIC,static,1342308352
Control5=IDC_SETTING_BROWSE,button,1342242816

[DLG:IDD_INFO]
Type=1
Class=CWaitDlg
ControlCount=2
Control1=IDC_INFO,static,1342308865
Control2=IDOK,button,1342242817

[MNU:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_FILE_OPEN
Command2=ID_FILE_MRU_FILE1
Command3=ID_FILE_NEW
Command4=ID_APP_EXIT
Command5=ID_SELECTALL
Command6=ID_LOOKKEY
Command7=ID_GET
Command8=ID_ACTIVE
Command9=ID_GETANDACTIVE
Command10=ID_START
Command11=ID_PROFILE
Command12=ID_SETTING
Command13=ID_LOOKSHAREMEM
Command14=ID_REPORTBUG
Command15=ID_UPDATACLIENT
CommandCount=15

[MNU:IDR_KEY]
Type=1
Class=?
Command1=ID_QUERY
Command2=ID_UNBIND
Command3=ID_BINDKEY
CommandCount=3

[DLG:IDD_MODIFYBIND]
Type=1
Class=?
ControlCount=10
Control1=IDC_OLDBIND,SysIPAddress32,1342242816
Control2=IDC_EDITUSERNAME,edit,1350631552
Control3=IDC_EDITPASSWORD,edit,1350631552
Control4=IDC_NEWBIND,SysIPAddress32,1342242816
Control5=IDOK,button,1342242817
Control6=IDCANCEL,button,1342242816
Control7=IDC_STATIC,static,1342308352
Control8=IDC_STATIC,static,1342308352
Control9=IDC_STATIC,static,1342308352
Control10=IDC_STATIC,static,1342308352

[ACL:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_STARTGAME
CommandCount=1

[DLG:IDD_REPORTBUG]
Type=1
Class=CBugRepDlg
ControlCount=3
Control1=IDC_EDIT1,edit,1350631552
Control2=IDOK,button,1342242817
Control3=IDCANCEL,button,1342242816

