; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=
LastTemplate=CDocument
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "jlwg.h"
LastPage=0

ClassCount=7
Class1=CConfigDlg
Class2=CDataDlg
Class3=CJLDlg

ResourceCount=8
Resource1=IDD_WGDATA
Resource2=IDD_SETINI_QIANGHUA
Resource3=IDR_MENU2
Resource4=IDD_SETINI_OBJFILTER
Resource5=IDD_SETINI_ITEMFILTER
Resource6=IDR_OBJECT
Class4=CConfigItemPage
Class5=CConfigObjPage
Class6=CConfigQhPage
Class7=CConfigSheet
Resource7=IDR_FILTER
Resource8=IDD_WGDLG

[CLS:CConfigDlg]
Type=0
BaseClass=CDialog
HeaderFile=ConfigDlg.h
ImplementationFile=ConfigDlg.cpp
LastObject=CConfigDlg
Filter=D
VirtualFilter=dWC

[CLS:CDataDlg]
Type=0
HeaderFile=datadlg.h
ImplementationFile=datadlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDC_HOOK_ACCEPTQUEST

[CLS:CJLDlg]
Type=0
BaseClass=CDialog
HeaderFile=JLDlg.h
ImplementationFile=JLDlg.cpp
Filter=D
VirtualFilter=dWC
LastObject=CJLDlg

[DLG:IDD_WGDATA]
Type=1
Class=CDataDlg
ControlCount=17
Control1=IDC_EDITMEMINPUT,edit,1350631552
Control2=IDC_EDITINFO,edit,1352732740
Control3=IDC_COMBO_DATATYPE,combobox,1344340227
Control4=IDC_LIST,SysListView32,1350631425
Control5=IDC_REFRESH,button,1342242816
Control6=IDC_HOOK_DEQUEST,button,1342242819
Control7=IDC_HOOK_SENDSTEP,button,1342242819
Control8=IDC_HOOK_CHUANZHUANGBEI,button,1342242819
Control9=ID_CLR,button,1342242816
Control10=ID_GETPALYERINFO,button,1342242816
Control11=IDC_SPEEDX,button,1342242816
Control12=IDC_HOOK_ACCEPTQUEST,button,1342242819
Control13=IDC_HOOK_DUNDI,button,1342242819
Control14=IDC_HOOK_YICIJIANWU,button,1342242819
Control15=ID_FINDTHENKILL,button,1342246915
Control16=IDC_BTNCONFIG,button,1342242816
Control17=IDC_HOOK_COMBAT,button,1342242819

[DLG:IDD_WGDLG]
Type=1
Class=CJLDlg
ControlCount=4
Control1=IDC_WGDATA,button,1342242816
Control2=IDC_GOTASK,button,1342242816
Control3=IDC_UNLOADWG,button,1342242816
Control4=IDC_STATIC_WGINFO,static,1342308352

[DLG:IDD_SETINI_QIANGHUA]
Type=1
Class=CConfigQhPage
ControlCount=4
Control1=65535,static,1342308352
Control2=IDC_COMBO_ITEMCOLOR,combobox,1342242819
Control3=65535,static,1342308352
Control4=IDC_CHIYAOPERCENT,edit,1350631552

[DLG:IDD_SETINI_ITEMFILTER]
Type=1
Class=CConfigItemPage
ControlCount=2
Control1=IDC_LIST_BAGS,SysListView32,1350633473
Control2=IDC_LIST_BAGSFILTER,SysListView32,1350633473

[DLG:IDD_SETINI_OBJFILTER]
Type=1
Class=CConfigObjPage
ControlCount=2
Control1=IDC_LIST_OBJECTS,SysListView32,1350633473
Control2=IDC_LIST_OBJECTFILTER,SysListView32,1350633473

[MNU:IDR_MENU2]
Type=1
Class=?
Command1=IDC_TURNTO
Command2=ID_STEPTOOBJET
CommandCount=2

[CLS:CConfigItemPage]
Type=0
HeaderFile=ConfigItemPage.h
ImplementationFile=ConfigItemPage.cpp
BaseClass=CDialog
Filter=D
LastObject=ID_CONFIG_REFRESH
VirtualFilter=dWC

[CLS:CConfigObjPage]
Type=0
HeaderFile=ConfigObjPage.h
ImplementationFile=ConfigObjPage.cpp
BaseClass=CDialog
Filter=D
LastObject=ID_CONFIG_ALWAYSKILL
VirtualFilter=dWC

[CLS:CConfigQhPage]
Type=0
HeaderFile=ConfigQhPage.h
ImplementationFile=ConfigQhPage.cpp
BaseClass=CDialog
Filter=D
LastObject=65535
VirtualFilter=dWC

[MNU:IDR_OBJECT]
Type=1
Class=?
Command1=IDC_TURNTO
Command2=ID_STEPTOOBJET
Command3=ID_HOOKSTRIKE
CommandCount=3

[CLS:CConfigSheet]
Type=0
HeaderFile=ConfigSheet.h
ImplementationFile=ConfigSheet.cpp
BaseClass=CPropertySheet
Filter=W
LastObject=CConfigSheet

[MNU:IDR_FILTER]
Type=1
Class=?
Command1=ID_CONFIG_SELL
Command2=ID_CONFIG_CUNCANG
Command3=ID_CONFIG_FENJIE
Command4=ID_CONFIG_JIAOYI
Command5=ID_CONFIG_QHSP
Command6=ID_CONFIG_QHWQ
Command7=ID_CONFIG_FIRST
Command8=ID_CONFIG_DONTKILL
Command9=ID_CONFIG_ALWAYSKILL
Command10=ID_CONFIG_REFRESH
CommandCount=10

