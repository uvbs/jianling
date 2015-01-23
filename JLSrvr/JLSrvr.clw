; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CRequestView
LastTemplate=CListView
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "JLSrvr.h"
LastPage=0

ClassCount=9
Class1=CJLSrvrApp
Class2=CJLSrvrDoc
Class3=CJLSrvrView
Class4=CMainFrame

ResourceCount=3
Resource1=IDR_MAINFRAME
Resource2=IDD_ABOUTBOX
Class5=CAboutDlg
Class6=CListenSocket
Class7=CRequestSocket
Class8=CDBLoginDlg
Class9=CRequestView
Resource3=IDD_DLG_LOGIN

[CLS:CJLSrvrApp]
Type=0
HeaderFile=JLSrvr.h
ImplementationFile=JLSrvr.cpp
Filter=N

[CLS:CJLSrvrDoc]
Type=0
HeaderFile=JLSrvrDoc.h
ImplementationFile=JLSrvrDoc.cpp
Filter=N
LastObject=ID_FILE_RESTART
BaseClass=CDocument
VirtualFilter=DC

[CLS:CJLSrvrView]
Type=0
HeaderFile=JLSrvrView.h
ImplementationFile=JLSrvrView.cpp
Filter=C
BaseClass=CListView
VirtualFilter=VWC


[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
LastObject=CMainFrame
BaseClass=CFrameWnd
VirtualFilter=fWC




[CLS:CAboutDlg]
Type=0
HeaderFile=JLSrvr.cpp
ImplementationFile=JLSrvr.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_OPEN
Command2=ID_FILE_SAVE
Command3=ID_FILE_SAVE_AS
Command4=ID_FILE_RESTART
Command5=ID_FILE_MRU_FILE1
Command6=ID_APP_EXIT
Command7=ID_VIEW_TOOLBAR
Command8=ID_VIEW_STATUS_BAR
Command9=ID_APP_ABOUT
CommandCount=9

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_UNDO
Command5=ID_EDIT_CUT
Command6=ID_EDIT_COPY
Command7=ID_EDIT_PASTE
Command8=ID_EDIT_UNDO
Command9=ID_EDIT_CUT
Command10=ID_EDIT_COPY
Command11=ID_EDIT_PASTE
Command12=ID_NEXT_PANE
Command13=ID_PREV_PANE
CommandCount=13

[TB:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_CUT
Command5=ID_EDIT_COPY
Command6=ID_EDIT_PASTE
Command7=ID_FILE_PRINT
Command8=ID_APP_ABOUT
CommandCount=8

[CLS:CListenSocket]
Type=0
HeaderFile=ListenSocket.h
ImplementationFile=ListenSocket.cpp
BaseClass=CSocket
Filter=N

[CLS:CRequestSocket]
Type=0
HeaderFile=RequestSocket.h
ImplementationFile=RequestSocket.cpp
BaseClass=CAsyncSocket
Filter=N
VirtualFilter=q
LastObject=IDC_EDIT1

[DLG:IDD_DLG_LOGIN]
Type=1
Class=CDBLoginDlg
ControlCount=10
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352
Control7=IDC_DBNAME,edit,1350631552
Control8=IDC_USERNAME,edit,1350631552
Control9=IDC_PASSW,edit,1350631552
Control10=IDC_COMBO1,combobox,1344340226

[CLS:CDBLoginDlg]
Type=0
HeaderFile=DBLoginDlg.h
ImplementationFile=DBLoginDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CDBLoginDlg

[CLS:CRequestView]
Type=0
HeaderFile=RequestView.h
ImplementationFile=RequestView.cpp
BaseClass=CListView
Filter=C
VirtualFilter=VWC

