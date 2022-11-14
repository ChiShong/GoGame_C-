; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CGoServer
LastTemplate=CSocket
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "Go.h"
LastPage=0

ClassCount=12
Class1=CGoApp
Class2=CGoDoc
Class3=CGoView
Class4=CMainFrame

ResourceCount=7
Resource1=IDD_DIALOGBAR (English (U.S.))
Resource2=IDD_ABOUTBOX
Class5=CChildFrame
Class6=CAboutDlg
Resource3=IDR_ReviewBoard
Class7=goDialog
Resource4=IDR_MAINFRAME
Class8=CBoardSizeDialog
Resource5=IDD_BoardSize
Class9=ReviewBoard
Resource6=IDR_GOTYPE
Class10=CPlayStatusDlg
Class11=CGoClient
Class12=CGoServer
Resource7=IDD_PlayStatus

[CLS:CGoApp]
Type=0
HeaderFile=Go.h
ImplementationFile=Go.cpp
Filter=N
LastObject=CGoApp

[CLS:CGoDoc]
Type=0
HeaderFile=GoDoc.h
ImplementationFile=GoDoc.cpp
Filter=N
BaseClass=CDocument
VirtualFilter=DC
LastObject=CGoDoc

[CLS:CGoView]
Type=0
HeaderFile=GoView.h
ImplementationFile=GoView.cpp
Filter=C
LastObject=CGoView
BaseClass=CView
VirtualFilter=VWC


[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
BaseClass=CMDIFrameWnd
VirtualFilter=fWC
LastObject=CMainFrame


[CLS:CChildFrame]
Type=0
HeaderFile=ChildFrm.h
ImplementationFile=ChildFrm.cpp
Filter=M
BaseClass=CMDIChildWnd
VirtualFilter=mfWC
LastObject=CChildFrame


[CLS:CAboutDlg]
Type=0
HeaderFile=Go.cpp
ImplementationFile=Go.cpp
Filter=D
LastObject=CAboutDlg

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
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_PRINT_SETUP
Command4=ID_FILE_MRU_FILE1
Command5=ID_APP_EXIT
Command6=ID_VIEW_TOOLBAR
Command7=ID_VIEW_STATUS_BAR
Command8=ID_APP_ABOUT
CommandCount=8

[TB:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_CUT
Command5=ID_EDIT_COPY
Command6=ID_EDIT_PASTE
Command7=ID_FILE_PRINT
Command8=ID_APP_ABOUT
CommandCount=8

[MNU:IDR_GOTYPE]
Type=1
Class=CGoView
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_CLOSE
Command4=ID_FILE_SAVE
Command5=ID_FILE_SAVE_AS
Command6=ID_FILE_PRINT
Command7=ID_FILE_PRINT_PREVIEW
Command8=ID_FILE_PRINT_SETUP
Command9=ID_FILE_SEND_MAIL
Command10=ID_FILE_MRU_FILE1
Command11=ID_APP_EXIT
Command12=ID_EDIT_UNDO
Command13=ID_EDIT_CUT
Command14=ID_EDIT_COPY
Command15=ID_EDIT_PASTE
Command16=ID_VIEW_TOOLBAR
Command17=ID_VIEW_STATUS_BAR
Command18=ID_WINDOW_NEW
Command19=ID_WINDOW_CASCADE
Command20=ID_WINDOW_TILE_HORZ
Command21=ID_WINDOW_ARRANGE
Command22=ID_APP_ABOUT
Command23=ID_board_size
Command24=ID_PlayStatus
CommandCount=24

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_PRINT
Command5=ID_EDIT_UNDO
Command6=ID_EDIT_CUT
Command7=ID_EDIT_COPY
Command8=ID_EDIT_PASTE
Command9=ID_EDIT_UNDO
Command10=ID_EDIT_CUT
Command11=ID_EDIT_COPY
Command12=ID_EDIT_PASTE
Command13=ID_NEXT_PANE
Command14=ID_PREV_PANE
CommandCount=14

[CLS:goDialog]
Type=0
HeaderFile=goDialog.h
ImplementationFile=goDialog.cpp
BaseClass=CDialog
Filter=D
LastObject=goDialog
VirtualFilter=dWC

[DLG:IDD_DIALOGBAR (English (U.S.))]
Type=1
Class=?
ControlCount=1
Control1=IDC_STATIC,static,1342308352

[CLS:CBoardSizeDialog]
Type=0
HeaderFile=BoardSizeDialog.h
ImplementationFile=BoardSizeDialog.cpp
BaseClass=CDialog
Filter=D
LastObject=CBoardSizeDialog
VirtualFilter=dWC

[DLG:IDD_BoardSize]
Type=1
Class=?
ControlCount=6
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_RADIO1,button,1342177289
Control4=IDC_RADIO2,button,1342177289
Control5=IDC_RADIO3,button,1342177289
Control6=IDC_STATIC,button,1342177287

[CLS:ReviewBoard]
Type=0
HeaderFile=ReviewBoard.h
ImplementationFile=ReviewBoard.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=ID_APP_ABOUT

[TB:IDR_ReviewBoard]
Type=1
Class=CGoView
Command1=ID_forward_1
Command2=ID_forward_5
Command3=ID_backward_1
Command4=ID_backward_5
Command5=ID_to_the_end
Command6=ID_to_the_begin
CommandCount=6

[DLG:IDD_PlayStatus]
Type=1
Class=CPlayStatusDlg
ControlCount=25
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_Board19,button,1342308361
Control4=IDC_Board13,button,1342177289
Control5=IDC_Board9,button,1342177289
Control6=IDC_BlackStone,button,1342308361
Control7=IDC_WhiteStone,button,1342177289
Control8=IDC_SystemDetermined,button,1342177289
Control9=IDC_Handicap,edit,1350631552
Control10=IDC_STATIC,button,1342308359
Control11=IDC_STATIC,button,1342177287
Control12=IDC_STATIC,button,1342177287
Control13=IDC_STATIC,button,1342177287
Control14=IDC_STATIC,button,1342177287
Control15=IDC_STATIC,button,1342177287
Control16=IDC_STATIC,button,1342177287
Control17=IDC_BasicTime,edit,1350770816
Control18=IDC_CountDownTime,edit,1350639744
Control19=IDC_NumCountDown,edit,1350639744
Control20=IDC_STATIC,button,1342177287
Control21=IDC_PSK,button,1342308361
Control22=IDC_SSK,button,1342177289
Control23=IDC_ChineseRule,button,1342177289
Control24=IDC_JapanRule,button,1342177289
Control25=IDC_IngRule,button,1342177289

[CLS:CPlayStatusDlg]
Type=0
HeaderFile=PlayStatusDlg.h
ImplementationFile=PlayStatusDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CPlayStatusDlg

[CLS:CGoClient]
Type=0
HeaderFile=GoClient.h
ImplementationFile=GoClient.cpp
BaseClass=CSocket
Filter=N

[CLS:CGoServer]
Type=0
HeaderFile=GoServer.h
ImplementationFile=GoServer.cpp
BaseClass=CSocket
Filter=N

