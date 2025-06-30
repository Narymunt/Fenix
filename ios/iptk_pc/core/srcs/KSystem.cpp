#include	<windows.h>
#include	"KSystem.h"
#include	<stdlib.h>
#include	<stdio.h>

#ifndef SM_CMONITORS
       typedef HANDLE HMONITOR;
 #endif


 struct 	MYDISPLAY_DEVICE {
        DWORD  cb;
        TCHAR  DeviceName[32];
        TCHAR  DeviceString[128];
        DWORD  StateFlags;
       } ;
       
       #define DISPLAY_DEVICE_ATTACHED_TO_DESKTOP 0x00000001
       #define DISPLAY_DEVICE_MULTI_DRIVER        0x00000002
       #define DISPLAY_DEVICE_PRIMARY_DEVICE      0x00000004
       #define DISPLAY_DEVICE_VGA             0x00000010

	 bool myEnumDisplayDevices(  long Unused,  unsigned long  iDevNum, MYDISPLAY_DEVICE* lpDisplayDevice, unsigned long  dwFlags );


typedef    bool (WINAPI* pEnumDisplayDevices)(void*,unsigned long,MYDISPLAY_DEVICE*,unsigned long);

KSystem::KSystem( ) 
{
MYDISPLAY_DEVICE			ddevice ;
DEVMODE				devmode ;
MEMORYSTATUS 			cpumem ;   // memory status structure

	ddevice.cb =sizeof( DISPLAY_DEVICE ) ;
	memset( &devmode , 0 , sizeof( DEVMODE ) ) ;
	if ( myEnumDisplayDevices( 0 , 0 , &ddevice , 0 ) == false )
	{
		//ATI2VG
		devmode.dmSize = sizeof( DEVMODE ) ;
		EnumDisplaySettings( 0 , 0 , &devmode ) ;
		strcpy(	videoCardName , (char*)devmode.dmDeviceName  ) ;
	}
	else
	{
		strcpy(	videoCardName , (char*)ddevice.DeviceString  ) ;	
	}




	cpumem.dwLength = sizeof( MEMORYSTATUS ) ;

	GlobalMemoryStatus( &cpumem ) ;
	memory = (unsigned long)cpumem.dwTotalPhys ;


}

	
	
KSystem::~KSystem( ) 
{
}


void		KSystem::getTime( KTime	*ktime ) 
{
SYSTEMTIME	st ;

	if ( ktime == NULL )	return ;
	GetLocalTime( &st ) ;

	ktime->year 	= st.wYear ;
	ktime->month 	= st.wMonth ;
	ktime->day	= st.wDay ;

	ktime->hour 	= st.wHour ;
	ktime->minute 	= st.wMinute ;
	ktime->second	= st.wSecond ;
	ktime->milliseconds	= st.wMilliseconds ;
}


unsigned long		KSystem::getMemory( void ) 
{
	return	memory ;
}

//returns the video card name
char*	KSystem::getVideoCardName( void )
{
	return	videoCardName ;
}


void		KSystem::getOSVersion( KOSVersion	*kos)
{
OSVERSIONINFO		osvi ;

//HKEY_LOCAL_MACHINE\HARDWARE\DESCRIPTION\SYSTEM\CentralProcessor 

	if ( kos == NULL )		return ;
	
	osvi.dwOSVersionInfoSize  = sizeof( OSVERSIONINFO ) ;
	GetVersionEx( &osvi ) ;
	kos->computerType	=	CPUTYPE_PC ;
	kos->majorVersion	=	osvi.dwMajorVersion  ;
	kos->minorVersion	=	osvi.dwMinorVersion  ;
	kos->buildNumber	=	osvi.dwBuildNumber  ;
	kos->platformId		=	osvi.dwPlatformId  ;

	#ifndef __MWERKS__
		_snprintf( kos->miscInfo ,256 , "%s",osvi.szCSDVersion )  ;
	#else
		snprintf( kos->miscInfo ,256 , "%s",osvi.szCSDVersion )  ;
	#endif

	strcpy( kos->ptkVersion , "2.1" ) ;

}


bool myEnumDisplayDevices(  long Unused,  unsigned long  iDevNum, MYDISPLAY_DEVICE* lpDisplayDevice, unsigned long  dwFlags )
{
	#pragma unused( Unused )
	#pragma unused( iDevNum )
	#pragma unused( dwFlags )
    //BOOL (WINAPI* pEnumDisplayDevices)(PVOID,DWORD,PVOID,DWORD);

	pEnumDisplayDevices  pendisplay ;

   /* (FARPROC)*/
	pendisplay = (pEnumDisplayDevices)GetProcAddress( LoadLibrary("USER32"), "EnumDisplayDevicesA");

    if (pendisplay == NULL )		return false ;

    ZeroMemory(	lpDisplayDevice, sizeof(MYDISPLAY_DEVICE));
    lpDisplayDevice->cb = sizeof(MYDISPLAY_DEVICE);

    (*pendisplay)(NULL, 0, lpDisplayDevice, 0) ;

   return true ;
 }

//audio
char*	KSystem::getAudioDriverName( void )
{
static	WAVEINCAPS 	ac ;

	memset( &ac , 0 , sizeof( WAVEINCAPS  ) ) ;
	waveInGetDevCaps( 0 ,    &ac , sizeof( WAVEINCAPS  ) ) ;
	
	return ac.szPname  ;
}

	