# Microsoft Developer Studio Project File - Name="LibPtkvc" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=LibPtkvc - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "LibPtkvc.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "LibPtkvc.mak" CFG="LibPtkvc - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "LibPtkvc - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "LibPtkvc - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "LibPtkvc - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /FR /FD /c
# SUBTRACT CPP /YX
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "LibPtkvc - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ENDIF 

# Begin Target

# Name "LibPtkvc - Win32 Release"
# Name "LibPtkvc - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "lua"

# PROP Default_Filter ""
# Begin Source File

SOURCE="..\srcs\lua-5.0\lua-5.0\src\lapi.c"
# End Source File
# Begin Source File

SOURCE="..\srcs\lua-5.0\lua-5.0\src\lapi.h"
# End Source File
# Begin Source File

SOURCE="..\srcs\lua-5.0\lua-5.0\src\lib\lauxlib.c"
# End Source File
# Begin Source File

SOURCE="..\srcs\lua-5.0\lua-5.0\src\lib\lbaselib.c"
# End Source File
# Begin Source File

SOURCE="..\srcs\lua-5.0\lua-5.0\src\lcode.c"
# End Source File
# Begin Source File

SOURCE="..\srcs\lua-5.0\lua-5.0\src\lcode.h"
# End Source File
# Begin Source File

SOURCE="..\srcs\lua-5.0\lua-5.0\src\lib\ldblib.c"
# End Source File
# Begin Source File

SOURCE="..\srcs\lua-5.0\lua-5.0\src\ldebug.c"
# End Source File
# Begin Source File

SOURCE="..\srcs\lua-5.0\lua-5.0\src\ldebug.h"
# End Source File
# Begin Source File

SOURCE="..\srcs\lua-5.0\lua-5.0\src\ldo.c"
# End Source File
# Begin Source File

SOURCE="..\srcs\lua-5.0\lua-5.0\src\ldo.h"
# End Source File
# Begin Source File

SOURCE="..\srcs\lua-5.0\lua-5.0\src\ldump.c"
# End Source File
# Begin Source File

SOURCE="..\srcs\lua-5.0\lua-5.0\src\lfunc.c"
# End Source File
# Begin Source File

SOURCE="..\srcs\lua-5.0\lua-5.0\src\lfunc.h"
# End Source File
# Begin Source File

SOURCE="..\srcs\lua-5.0\lua-5.0\src\lgc.c"
# End Source File
# Begin Source File

SOURCE="..\srcs\lua-5.0\lua-5.0\src\lgc.h"
# End Source File
# Begin Source File

SOURCE="..\srcs\lua-5.0\lua-5.0\src\lib\liolib.c"
# End Source File
# Begin Source File

SOURCE="..\srcs\lua-5.0\lua-5.0\src\llex.c"
# End Source File
# Begin Source File

SOURCE="..\srcs\lua-5.0\lua-5.0\src\llex.h"
# End Source File
# Begin Source File

SOURCE="..\srcs\lua-5.0\lua-5.0\src\llimits.h"
# End Source File
# Begin Source File

SOURCE="..\srcs\lua-5.0\lua-5.0\src\lib\lmathlib.c"
# End Source File
# Begin Source File

SOURCE="..\srcs\lua-5.0\lua-5.0\src\lmem.c"
# End Source File
# Begin Source File

SOURCE="..\srcs\lua-5.0\lua-5.0\src\lmem.h"
# End Source File
# Begin Source File

SOURCE="..\srcs\lua-5.0\lua-5.0\src\lib\loadlib.c"
# End Source File
# Begin Source File

SOURCE="..\srcs\lua-5.0\lua-5.0\src\lobject.c"
# End Source File
# Begin Source File

SOURCE="..\srcs\lua-5.0\lua-5.0\src\lobject.h"
# End Source File
# Begin Source File

SOURCE="..\srcs\lua-5.0\lua-5.0\src\lopcodes.c"
# End Source File
# Begin Source File

SOURCE="..\srcs\lua-5.0\lua-5.0\src\lopcodes.h"
# End Source File
# Begin Source File

SOURCE="..\srcs\lua-5.0\lua-5.0\src\lparser.c"
# End Source File
# Begin Source File

SOURCE="..\srcs\lua-5.0\lua-5.0\src\lparser.h"
# End Source File
# Begin Source File

SOURCE="..\srcs\lua-5.0\lua-5.0\src\lstate.c"
# End Source File
# Begin Source File

SOURCE="..\srcs\lua-5.0\lua-5.0\src\lstate.h"
# End Source File
# Begin Source File

SOURCE="..\srcs\lua-5.0\lua-5.0\src\lstring.c"
# End Source File
# Begin Source File

SOURCE="..\srcs\lua-5.0\lua-5.0\src\lstring.h"
# End Source File
# Begin Source File

SOURCE="..\srcs\lua-5.0\lua-5.0\src\lib\lstrlib.c"
# End Source File
# Begin Source File

SOURCE="..\srcs\lua-5.0\lua-5.0\src\ltable.c"
# End Source File
# Begin Source File

SOURCE="..\srcs\lua-5.0\lua-5.0\src\ltable.h"
# End Source File
# Begin Source File

SOURCE="..\srcs\lua-5.0\lua-5.0\src\lib\ltablib.c"
# End Source File
# Begin Source File

SOURCE="..\srcs\lua-5.0\lua-5.0\src\ltests.c"
# End Source File
# Begin Source File

SOURCE="..\srcs\lua-5.0\lua-5.0\src\ltm.c"
# End Source File
# Begin Source File

SOURCE="..\srcs\lua-5.0\lua-5.0\src\ltm.h"
# End Source File
# Begin Source File

SOURCE="..\srcs\lua-5.0\lua-5.0\src\lundump.c"
# End Source File
# Begin Source File

SOURCE="..\srcs\lua-5.0\lua-5.0\src\lundump.h"
# End Source File
# Begin Source File

SOURCE="..\srcs\lua-5.0\lua-5.0\src\lvm.c"
# End Source File
# Begin Source File

SOURCE="..\srcs\lua-5.0\lua-5.0\src\lvm.h"
# End Source File
# Begin Source File

SOURCE="..\srcs\lua-5.0\lua-5.0\src\lzio.c"
# End Source File
# Begin Source File

SOURCE="..\srcs\lua-5.0\lua-5.0\src\lzio.h"
# End Source File
# Begin Source File

SOURCE="..\srcs\lua-5.0\lua-5.0\src\luac\print.c"
# End Source File
# End Group
# Begin Group "truetype"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\freetypelib\freetype\freetype\autohint.c
# End Source File
# Begin Source File

SOURCE=..\..\..\freetypelib\freetype\freetype\bdf.c
# End Source File
# Begin Source File

SOURCE=..\..\..\freetypelib\freetype\freetype\ftbase.c
# End Source File
# Begin Source File

SOURCE=..\..\..\freetypelib\freetype\freetype\ftdebug.c
# End Source File
# Begin Source File

SOURCE=..\..\..\freetypelib\freetype\freetype\ftglyph.c
# End Source File
# Begin Source File

SOURCE=..\..\..\freetypelib\freetype\freetype\ftinit.c
# End Source File
# Begin Source File

SOURCE=..\..\..\freetypelib\freetype\freetype\ftlzw.c
# End Source File
# Begin Source File

SOURCE=..\..\..\freetypelib\freetype\freetype\ftmm.c
# End Source File
# Begin Source File

SOURCE=..\..\..\freetypelib\freetype\freetype\ftsystem.c
# End Source File
# Begin Source File

SOURCE=..\..\..\freetypelib\freetype\freetype\raster.c
# End Source File
# Begin Source File

SOURCE=..\..\..\freetypelib\freetype\freetype\sfnt.c
# End Source File
# Begin Source File

SOURCE=..\..\..\freetypelib\freetype\freetype\smooth.c
# End Source File
# Begin Source File

SOURCE=..\..\..\freetypelib\freetype\freetype\truetype.c
# End Source File
# Begin Source File

SOURCE=..\..\..\freetypelib\freetype\freetype\winfnt.c
# End Source File
# End Group
# Begin Source File

SOURCE=..\srcs\K3D.cpp
# End Source File
# Begin Source File

SOURCE=..\srcs\K3Dd3d.cpp
# End Source File
# Begin Source File

SOURCE=..\srcs\KBatchD3D.cpp
# End Source File
# Begin Source File

SOURCE=..\srcs\KBatchGL.cpp
# End Source File
# Begin Source File

SOURCE=..\srcs\KGraphicD3D.cpp
# End Source File
# Begin Source File

SOURCE=..\srcs\KGraphicGL.cpp
# End Source File
# Begin Source File

SOURCE=..\srcs\KIniReader.cpp
# End Source File
# Begin Source File

SOURCE=..\srcs\KInput_Win.cpp

!IF  "$(CFG)" == "LibPtkvc - Win32 Release"

# ADD CPP /MT

!ELSEIF  "$(CFG)" == "LibPtkvc - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\srcs\KKeyTablePC.cpp
# End Source File
# Begin Source File

SOURCE=..\srcs\KLog.cpp
# End Source File
# Begin Source File

SOURCE=..\srcs\KMiscTools.cpp
# End Source File
# Begin Source File

SOURCE=..\srcs\KObjectBase.cpp
# End Source File
# Begin Source File

SOURCE=..\srcs\KObjectListable.cpp
# End Source File
# Begin Source File

SOURCE=..\srcs\KPTK.cpp
# End Source File
# Begin Source File

SOURCE=..\srcs\KResource.cpp
# End Source File
# Begin Source File

SOURCE=..\srcs\KResourceArchive.cpp
# End Source File
# Begin Source File

SOURCE=..\srcs\KSpline.cpp
# End Source File
# Begin Source File

SOURCE=..\srcs\KSystem.cpp
# End Source File
# Begin Source File

SOURCE=..\srcs\KText.cpp
# End Source File
# Begin Source File

SOURCE=..\srcs\KTrueText.cpp
# End Source File
# Begin Source File

SOURCE=..\srcs\KWeb.cpp
# End Source File
# Begin Source File

SOURCE=..\srcs\KWindowD3D.cpp
# End Source File
# Begin Source File

SOURCE=..\srcs\KWindowGL.cpp
# End Source File
# Begin Source File

SOURCE=..\srcs\matrices.cpp
# End Source File
# Begin Source File

SOURCE=.\vccximage.lib
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE="..\..\..\..\Documents and Settings\patriceXP\Desktop\LaPTK\ptk\libptk\pc\headers\K3D.h"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\Documents and Settings\patriceXP\Desktop\LaPTK\ptk\libptk\pc\headers\K3Dd3d.h"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\Documents and Settings\patriceXP\Desktop\LaPTK\ptk\libptk\pc\headers\K3DGL.h"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\Documents and Settings\patriceXP\Desktop\LaPTK\ptk\libptk\pc\headers\K7Z.h"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\Documents and Settings\patriceXP\Desktop\LaPTK\ptk\libptk\pc\headers\KDataExchange.h"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\Documents and Settings\patriceXP\Desktop\LaPTK\ptk\libptk\pc\headers\KDataItem.h"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\Documents and Settings\patriceXP\Desktop\LaPTK\ptk\libptk\pc\headers\KGlobals.h"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\Documents and Settings\patriceXP\Desktop\LaPTK\ptk\libptk\pc\headers\KGraphic.h"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\Documents and Settings\patriceXP\Desktop\LaPTK\ptk\libptk\pc\headers\KGraphicD3D.h"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\Documents and Settings\patriceXP\Desktop\LaPTK\ptk\libptk\pc\headers\KGraphicGL.h"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\Documents and Settings\patriceXP\Desktop\LaPTK\ptk\libptk\pc\headers\KIniReader.h"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\Documents and Settings\patriceXP\Desktop\LaPTK\ptk\libptk\pc\headers\KInput.h"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\Documents and Settings\patriceXP\Desktop\LaPTK\ptk\libptk\pc\headers\KKeyTable.h"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\Documents and Settings\patriceXP\Desktop\LaPTK\ptk\libptk\pc\headers\KList.h"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\Documents and Settings\patriceXP\Desktop\LaPTK\ptk\libptk\pc\headers\KLog.h"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\Documents and Settings\patriceXP\Desktop\LaPTK\ptk\libptk\pc\headers\KMessage.h"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\Documents and Settings\patriceXP\Desktop\LaPTK\ptk\libptk\pc\headers\KMiscTools.h"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\Documents and Settings\patriceXP\Desktop\LaPTK\ptk\libptk\pc\headers\KObjectBase.h"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\Documents and Settings\patriceXP\Desktop\LaPTK\ptk\libptk\pc\headers\KObjectListable.h"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\Documents and Settings\patriceXP\Desktop\LaPTK\ptk\libptk\pc\headers\KPTK.h"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\Documents and Settings\patriceXP\Desktop\LaPTK\ptk\libptk\pc\headers\KResource.h"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\Documents and Settings\patriceXP\Desktop\LaPTK\ptk\libptk\pc\headers\KResourceArchive.h"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\Documents and Settings\patriceXP\Desktop\LaPTK\ptk\libptk\pc\headers\KSpline.h"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\Documents and Settings\patriceXP\Desktop\LaPTK\ptk\libptk\pc\headers\KSystem.h"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\Documents and Settings\patriceXP\Desktop\LaPTK\ptk\libptk\pc\headers\KText.h"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\Documents and Settings\patriceXP\Desktop\LaPTK\ptk\libptk\pc\headers\KTrueText.h"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\Documents and Settings\patriceXP\Desktop\LaPTK\ptk\libptk\pc\headers\KTypes.h"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\Documents and Settings\patriceXP\Desktop\LaPTK\ptk\libptk\pc\headers\KWeb.h"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\Documents and Settings\patriceXP\Desktop\LaPTK\ptk\libptk\pc\headers\KWindow.h"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\Documents and Settings\patriceXP\Desktop\LaPTK\ptk\libptk\pc\headers\KWindowD3D.h"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\Documents and Settings\patriceXP\Desktop\LaPTK\ptk\libptk\pc\headers\KWindowGL.h"
# End Source File
# Begin Source File

SOURCE=..\srcs\matrices.h
# End Source File
# Begin Source File

SOURCE="..\..\..\..\Documents and Settings\patriceXP\Desktop\LaPTK\ptk\libptk\pc\headers\ptk.h"
# End Source File
# Begin Source File

SOURCE=..\srcs\trial.h
# End Source File
# End Group
# End Target
# End Project
