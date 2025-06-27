#include	"KWebCam.h"
#include	<Vfw.h>
#include	<string.h>
#include	<stdio.h>
#include	<stdlib.h>

#define	snprintf	_snprintf

KWebCam::KWebCam( ) 
{
	_screenshotData 		=	NULL ;
	_cameraInitialised 		=	false ;
	_hwndCamera			=	NULL ;
	_cameraIndex			=	-1 ;
}
KWebCam::~KWebCam( )
{
	stopCapture( ) ;
	detachGrabber( ) ;
	disconnectCamera( ) ;
	
	if ( _screenshotData != NULL )
	{
		delete	[]	_screenshotData ;
		_screenshotData = NULL ;
	}
}

//enumeration des cameras
char*		KWebCam::getCameraInfo( long	index )
{
char	cameraName[256] ;
char	deviceName[256] ;
static	char	buffer[256] ;

	//index de 0 a 9
	if ( index < 0 || index > 9 )		return NULL ;
	
	memset(  buffer , 0 , 256 ) ;		    		
	
    if ((bool)capGetDriverDescription (index, cameraName, 256, deviceName,  256 ) == true )
    {
				snprintf( buffer , 256,  "%s" ,cameraName ) ;		    		
    }
		
		return buffer ;
}


bool		KWebCam::setCamera( HWND	parentWindow , long		cameraIndex )
{
	_hwndCamera =  capCreateCaptureWindow(	"KWebCamera" , 
																	 WS_CHILD     , 
																	320,
																	0,
																	320,
																	240,
																	parentWindow ,
																	1725); //window identifier ) ;
																	
	if ( _hwndCamera == NULL )	return false ;
	_cameraIndex = cameraIndex ; 
	

 	capPreview(	_hwndCamera , false );       
 	
	SetWindowLong( _hwndCamera , GWL_USERDATA , (long)this ) ;
	
	 _screenshotData = new unsigned short[320*240] ;
	memset( _screenshotData , 0 , 320*240 ) ;
	
	if ( connectCamera( ) == false )	return false ;
	
	return startCamera( ) ;
}


//demarre la camera
bool	KWebCam::startCamera( void )
{
BITMAPINFO	bmi ;

	if ( _hwndCamera == NULL )		return false ;
	if ( _cameraIndex < 0 || _cameraIndex > 9 )		return false;
		
	//se mets en 320*240*16 bits RGB pour la webcam

	memset( &bmi , 0 , sizeof( BITMAPINFO ) ) ;
	
	bmi.bmiHeader.biSize		=	sizeof( BITMAPINFO ) ;
	bmi.bmiHeader.biWidth	=	320 ;
	bmi.bmiHeader.biHeight	=	240 ;
	bmi.bmiHeader.biPlanes	=	1 ; 
	bmi.bmiHeader.biBitCount	=	16 ;
	bmi.bmiHeader.biSizeImage 	=		bmi.bmiHeader.biWidth*	bmi.bmiHeader.biHeight*2 ;

	if (  capSetVideoFormat( _hwndCamera , &bmi , sizeof( BITMAPINFO ) ) == false )
	{
		MessageBox( 0 ,"Your webcam does allow 320*240*16 bpp RGB" ,"Try to update your drivers" , 0 ) ;
		return false;
	}


	if ( attachGrabber( ) == false )
	{
		return false ;
	}
	
CAPTUREPARMS	cparms ;

	capCaptureGetSetup(	_hwndCamera , &cparms , sizeof( CAPTUREPARMS ) ) ;
	cparms.dwRequestMicroSecPerFrame = 1000000 ;
	cparms.fMakeUserHitOKToCapture  = false ;
	cparms.wPercentDropForError = 80 ;
	cparms.fCaptureAudio  = false ;
	cparms.fLimitEnabled  = false ;
	cparms.fAbortLeftMouse  = false ;
	cparms.fAbortRightMouse  = false ;
	cparms.fYield = true ;
	
	if ( capCaptureSetSetup(	_hwndCamera , &cparms , sizeof( CAPTUREPARMS ) ) == false )
	{
		MessageBox( 0 , "impossible capCaptureSetSetup",0,0 ) ;
		return false ;
	}

	capFileSetCaptureFile( _hwndCamera , "c:\\pheliosvideo.avi" ) ;

	return true ;
}

//start capture
bool	KWebCam::startCapture( long		FrameEveryMicroseconds )
{
	if ( _hwndCamera == NULL )		return false ;
	
	stopCapture( ) ;
	
CAPTUREPARMS	cparms ;

	capCaptureGetSetup(	_hwndCamera , &cparms , sizeof( CAPTUREPARMS ) ) ;
	cparms.dwRequestMicroSecPerFrame = FrameEveryMicroseconds ;
	cparms.fMakeUserHitOKToCapture  = false ;
	cparms.wPercentDropForError = 0 ;
	cparms.fCaptureAudio  = false ;
	cparms.fLimitEnabled  = false ;
	cparms.fAbortLeftMouse  = false ;
	cparms.fAbortRightMouse  = false ;
	cparms.fYield = true ;
	
	if ( capCaptureSetSetup(	_hwndCamera , &cparms , sizeof( CAPTUREPARMS ) ) == false )
	{		
		return false ;
	}

	return	capCaptureSequenceNoFile( _hwndCamera ) ;

	
}

//stop capture
void	KWebCam::stopCapture( void )
{
	if ( _hwndCamera == NULL )		return  ;	
	capCaptureStop( _hwndCamera ) ;
}


//connecte la camera
bool	KWebCam::connectCamera( void ) 
{
	//la camera ne peu pas exister ?
	if ( _cameraIndex < 0 || _cameraIndex > 9 )		return false;
	
	return (bool)capDriverConnect( _hwndCamera , _cameraIndex ) ;
}

//deconnecte  la camera
bool	KWebCam::disconnectCamera( void ) 
{
	//la camera ne peu pas exister ?
	if ( _cameraIndex < 0 || _cameraIndex > 9 )		return false ;
	if ( _hwndCamera == NULL )		return false ;

 	capPreview(	_hwndCamera , false );       

	return 	capDriverDisconnect( _hwndCamera  ) ;
}


//attache le frame grabber
bool	KWebCam::attachGrabber( void )
{
	if ( _hwndCamera == NULL )		return false ;

	return	 capSetCallbackOnVideoStream( _hwndCamera , grabFrameProc ) ;
}

bool	KWebCam::detachGrabber( void )
{
	if ( _hwndCamera == NULL )		return false ;
	return	 capSetCallbackOnVideoStream( _hwndCamera , NULL ) ;
}


//retourne le pointeur sur les pixels
unsigned	short	*		KWebCam::getPixels( void ) 
{
	return _screenshotData ;
}


LRESULT CALLBACK		KWebCam::grabFrameProc( HWND hwnd , LPVIDEOHDR  videoHDR ) 
{

	
static	long	frameCount = 0 ;
//HWND	hwndParent ;
unsigned	short		*pixelsPtr ;
unsigned	short		*pixelsSourcePtr ;
	
KWebCam	*kwPtr ;
static			unsigned long		dropFrame = 0 ;
//char		buffer[256] ;

	dropFrame++ ;
	if ( dropFrame < 25 )		return true ;
	dropFrame = 0 ;
	
	if ( (videoHDR->dwFlags & VHDR_DONE ) == 0 )	
	{
		return false ;
	}
		
	if ( videoHDR == NULL )		return 0 ;
	pixelsPtr = (unsigned short*)videoHDR->lpData  ;


	kwPtr = (KWebCam*)GetWindowLong( hwnd , GWL_USERDATA ) ;
	if ( kwPtr == NULL )		return 0 ;
	
	pixelsPtr = kwPtr->getPixels( ) ;
    if ( pixelsPtr == NULL )	return 0 ;


//ne pas utiliser memcpy car l'image est a l'envers
long	x,y, rows,rowd ;

	pixelsSourcePtr = (unsigned short*)videoHDR->lpData ;

	for ( y = 0 ; y< 240 ; y++ )
	{
		rows = y*320 ;
		rowd = (239-y) *320 ;
		
		for ( x = 0 ; x < 320 ; x++ )
		{
			pixelsPtr[x+rows] =  pixelsSourcePtr[x+rowd] ;
		}
	}

	return true ;
}