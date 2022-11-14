# Microsoft Developer Studio Project File - Name="Go" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=Go - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Go.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Go.mak" CFG="Go - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Go - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "Go - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Go - Win32 Release"

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
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x404 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x404 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 winmm.lib /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "Go - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x404 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x404 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 winmm.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "Go - Win32 Release"
# Name "Go - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\board.cpp
# End Source File
# Begin Source File

SOURCE=.\BoardSizeDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\ChildFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\Go.cpp
# End Source File
# Begin Source File

SOURCE=.\Go.rc
# End Source File
# Begin Source File

SOURCE=.\GoDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\GoServer.cpp
# End Source File
# Begin Source File

SOURCE=.\GoView.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\Move1.cpp
# End Source File
# Begin Source File

SOURCE=.\PlayStatusDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\Rules.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\board.h
# End Source File
# Begin Source File

SOURCE=.\BoardSizeDialog.h
# End Source File
# Begin Source File

SOURCE=.\ChildFrm.h
# End Source File
# Begin Source File

SOURCE=.\Go.h
# End Source File
# Begin Source File

SOURCE=.\GoDoc.h
# End Source File
# Begin Source File

SOURCE=.\GoServer.h
# End Source File
# Begin Source File

SOURCE=.\GoView.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\Move1.h
# End Source File
# Begin Source File

SOURCE=.\PlayStatusDlg.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\Rules.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\0.bmp
# End Source File
# Begin Source File

SOURCE=.\res\1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\1leftarrow.bmp
# End Source File
# Begin Source File

SOURCE=.\res\1rightarrow.bmp
# End Source File
# Begin Source File

SOURCE=.\res\2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\2leftarrow.bmp
# End Source File
# Begin Source File

SOURCE=.\res\2rightarrow.bmp
# End Source File
# Begin Source File

SOURCE=.\res\3.bmp
# End Source File
# Begin Source File

SOURCE=.\res\32.bmp
# End Source File
# Begin Source File

SOURCE=.\res\4.bmp
# End Source File
# Begin Source File

SOURCE=.\res\5.bmp
# End Source File
# Begin Source File

SOURCE=.\res\6.bmp
# End Source File
# Begin Source File

SOURCE=.\res\7.bmp
# End Source File
# Begin Source File

SOURCE=.\res\8.bmp
# End Source File
# Begin Source File

SOURCE=.\res\9.bmp
# End Source File
# Begin Source File

SOURCE=.\res\birch.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap3.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap4.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bitmap_103.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bitmap_124.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bitmap_127.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bitmap_130.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bitmap_132.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bitmap_134.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bitmap_153.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bitmap_24.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bitmap_27.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bitmap_30.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bitmap_32.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bitmap_34.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bitmap_53.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bitmap_74.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bitmap_77.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bitmap_80.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bitmap_82.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bitmap_84.bmp
# End Source File
# Begin Source File

SOURCE=.\res\black.bmp
# End Source File
# Begin Source File

SOURCE=.\res\board0.bmp
# End Source File
# Begin Source File

SOURCE=.\res\cursor11.cur
# End Source File
# Begin Source File

SOURCE=.\res\Cursor_1.cur
# End Source File
# Begin Source File

SOURCE=.\res\Cursor_10.cur
# End Source File
# Begin Source File

SOURCE=.\res\Cursor_2.cur
# End Source File
# Begin Source File

SOURCE=.\res\Cursor_3.cur
# End Source File
# Begin Source File

SOURCE=.\res\Cursor_4.cur
# End Source File
# Begin Source File

SOURCE=.\res\Cursor_5.cur
# End Source File
# Begin Source File

SOURCE=.\res\Cursor_6.cur
# End Source File
# Begin Source File

SOURCE=.\res\Cursor_7.cur
# End Source File
# Begin Source File

SOURCE=.\res\Cursor_8.cur
# End Source File
# Begin Source File

SOURCE=.\res\Cursor_9.cur
# End Source File
# Begin Source File

SOURCE=.\res\Go.ico
# End Source File
# Begin Source File

SOURCE=.\res\Go.rc2
# End Source File
# Begin Source File

SOURCE=.\res\GoDoc.ico
# End Source File
# Begin Source File

SOURCE=.\res\node_black.bmp
# End Source File
# Begin Source File

SOURCE=.\res\node_white.bmp
# End Source File
# Begin Source File

SOURCE=.\res\stones2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\stones3.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar.bmp
# End Source File
# Begin Source File

SOURCE=.\res\toolbar1.bmp
# End Source File
# Begin Source File

SOURCE=".\res\¤ý±Ò¶¯.bmp"
# End Source File
# End Group
# Begin Source File

SOURCE=.\res\Data_10.wav
# End Source File
# Begin Source File

SOURCE=.\res\Data_16.wav
# End Source File
# Begin Source File

SOURCE=.\res\Data_2.wav
# End Source File
# Begin Source File

SOURCE=.\res\Data_3.wav
# End Source File
# Begin Source File

SOURCE=.\res\Data_4.wav
# End Source File
# Begin Source File

SOURCE=.\res\Data_5.wav
# End Source File
# Begin Source File

SOURCE=.\res\Data_6.wav
# End Source File
# Begin Source File

SOURCE=.\res\Data_7.wav
# End Source File
# Begin Source File

SOURCE=.\res\Data_8.wav
# End Source File
# Begin Source File

SOURCE=.\res\Data_9.wav
# End Source File
# Begin Source File

SOURCE=.\res\Data_CountDown1.wav
# End Source File
# Begin Source File

SOURCE=.\res\FinalCountDown.wav
# End Source File
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# Begin Source File

SOURCE=.\res\RemainThreeCountDown.wav
# End Source File
# Begin Source File

SOURCE=.\res\RemainTwoCountDown.wav
# End Source File
# Begin Source File

SOURCE=.\res\StartCountDown.wav
# End Source File
# Begin Source File

SOURCE=.\res\StartTheGame.wav
# End Source File
# End Target
# End Project
