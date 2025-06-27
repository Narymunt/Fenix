
#include	"KwindowGDI.h"
#include	"KGlobals.h"
#include	<stdio.h>
#include	"KMiscTools.h"
#include	"KInput.h"
//#include	"KGraphicGL.h"
#include	"ptk.h"
//#include	<complex.h>
#include	<math.h>
#include	"glati.h"
#include	"trial.h"
#include	"ximage.h"

#ifndef	WM_MOUSEWHEEL
#define	WM_MOUSEWHEEL                   0x020A
#endif



KGraphicGDI*		KWindowGDI::_surf_colorHolder = NULL ;

KWindowGDI::KWindowGDI( ) 
{
	_fullscreen = false ;
	memset( &dv , 0 , sizeof( DEVMODE ) ) ;
	_quit = false ;
	KMiscTools::initMillisecond( ) ;
	_use3d = false ;
	_userCallback 	= NULL ;
	_ptkCallback 	= NULL ;
	_gamma = 1 ;
	_maxFrameRate = 0 ;
////////////////////////////////////////////////////////////////////
	_clearR = 0 ;
	_clearG = 0 ;
	_clearB = 0 ;
	_clearA = 0 ;
    _silent = false;
    _displayPTKMouse = false ;
	_windowDC = 0 ;
	_surf_backBuffer = NULL ;
	_surf_colorHolder = NULL ;
}

KWindowGDI::KWindowGDI( bool 	use3D) 
{
_surf_backBuffer = NULL ;
    _displayPTKMouse = false ;
	_fullscreen = false ;
	memset( &dv , 0 , sizeof( DEVMODE ) ) ;
	_quit = false ;
	KMiscTools::initMillisecond( ) ;
	_use3d = use3D ;
	_userCallback 	= NULL ;
	_ptkCallback 	= NULL ;
	_gamma = 1 ;
	_maxFrameRate = 0 ;
////////////////////////////////////////////////////////////////////
	_clearR = 0 ;
	_clearG = 0 ;
	_clearB = 0 ;
	_clearA = 0 ;
    _silent = false;
    _windowDC = 0 ;
    _surf_colorHolder = NULL ;
}

long		KWindowGDI::getWindowWidth( void ) 
{
	return _windowWidth ;
}

long		KWindowGDI::getWindowHeight( void ) 
{
	return _windowHeight ;

}


//the basic world
void		KWindowGDI::setDefaultWorldView( void ) 
{
    setWorldView( 0,0,0,1.0f , false )  ;
}


//permet de creer un etat global du jeu
void		KWindowGDI::setWorldView( float	translateX , float		translateY ,   float	rotation , float 	zoom, bool	clearworld  )
{
    
    if ( clearworld == true )	
    {
//      	glClearColor( _clearR ,_clearG ,_clearB ,_clearA  ) ;
    }
    
}


void		KWindowGDI::displayMouse( bool mousestate ) 
{
		_displayPTKMouse = mousestate ;

}


KWindowGDI::~KWindowGDI( ) 
{
	KInput::freeMouse( ) ;
	_userCallback 	= NULL ;
	_ptkCallback 	= NULL ;
	KInput::showPointer( ) ;

	ReleaseDC( _hwnd , _hDC ) ;
	ReleaseDC(  _hwnd , _windowDC )  ;

	if (IsWindow ( _hwnd  ))
	{
		DestroyWindow( _hwnd ) ;
		_hwnd = 0 ;
	}
	
	PTK_FREEPTR( _surf_colorHolder )
	PTK_FREEPTR( _surf_backBuffer  )
	
	RestoreResolution( ) ;
	_quit = true ;
}


void		KWindowGDI::setCallBack( ptkWindowCallBack  userProc ) 
{
	_userCallback = userProc ;
}

void		KWindowGDI::setPTKCallBack( ptkNativeCallBack  userProc ) 
{
	_ptkCallback = userProc ;
}



//creates a window
bool		KWindowGDI::createGameWindow( short  width , short height , short depth , bool windowed , const char *windowTitle )
{
WNDCLASS				wndClass ;
RECT						r ;
int							screenWidth , screenHeight ;
unsigned long		windowStyle = WS_CAPTION | WS_SYSMENU | WS_VISIBLE | WS_MINIMIZEBOX ;

		depth = 32 ;

//			fadeGammaRamp( ) ;
		if ( _silent == true )
		{
			width = 256 ;
			height = 256 ;
			depth = -1 ;
			windowed = true ;
		}
			_windowWidth		=	width ;
			_windowHeight 	=	height ;
			_windowDepth 	=	depth ;
		
		KGraphicGDI::setScreenSize( width , height , depth ) ;
		if ( windowed == false )	
		{
			_fullscreen = true ;
			SwitchToResolution( width , height , depth ) ;
			windowStyle = WS_POPUP | WS_VISIBLE  ;
		}
		else
		{
			_fullscreen = false  ;
			//switch en depth  bits
			if ( depth != -1 )
			{
				SwitchToResolution( -1,-1,depth ) ;
			}
		}
		screenWidth 	= GetSystemMetrics( SM_CXSCREEN ) ;
		screenHeight = GetSystemMetrics( SM_CYSCREEN ) ;

		wndClass.lpszClassName 	= "PTK windowTitle" ;
		wndClass.hInstance 			= GetModuleHandle( NULL ) ;
		wndClass.lpfnWndProc		= GameWindowProc;
		wndClass.hCursor				= NULL ; /// LoadCursor( NULL , IDC_ARROW )  ;
		SetCursor( LoadCursor( NULL , IDC_ARROW )   ) ;

		wndClass.hIcon					= LoadIcon( GetModuleHandle( NULL ) , MAKEINTRESOURCE(160) );
		wndClass.lpszMenuName	= NULL;
		if ( _silent == true )
		{
				wndClass.hbrBackground	= (HBRUSH)GetStockObject( NULL_BRUSH );
		}
		else
		{
				wndClass.hbrBackground	= (HBRUSH)GetStockObject( BLACK_BRUSH );
		}
		wndClass.style					= CS_DBLCLKS;
		wndClass.cbClsExtra			= 0;
		wndClass.cbWndExtra			= 0;

		RegisterClass( &wndClass ) ;
		
	
		//we need a width*height window
		SetRect( &r , 0 , 0 , width , height ) ;

		//calculate the client rect
		AdjustWindowRect( &r , windowStyle  , false ) ;
	
		//go baby !		
		if ( _silent == false )
		{
				_hwnd		=	CreateWindow( 		"PTK windowTitle"  ,
														windowTitle,
														windowStyle ,
														(screenWidth-(r.right-r.left))/2 ,			//centers the window
														(screenHeight-(r.bottom-r.top))/2,
														r.right-r.left	,	
														r.bottom-r.top  ,
														NULL ,
														0 ,
														GetModuleHandle( NULL ) ,
														0 ) ;
		}
		else
		{
				_hwnd		=	CreateWindow( 		windowTitle ,
														windowTitle,
														WS_POPUP ,30,30 ,256,256	,		//centers the window
														NULL ,
														0 ,
														GetModuleHandle( NULL ) ,
														0 ) ;		
		}
		
		if ( _hwnd == NULL  )	return K_ERROR ;		
		SetWindowLong( _hwnd , GWL_USERDATA , (long)this );

		setTitle( windowTitle ) ;
		ShowWindow( _hwnd, SW_SHOW );
		UpdateWindow( _hwnd );
		_windowDC = GetDC( _hwnd )  ;
		KGraphicGDI::_mainDC = _windowDC ;
		
		KInput::initInput( _hwnd ) ;
	
		KGraphicGDI::setScreenSize( width , height ,  depth ) ;
		_surf_backBuffer = new KGraphicGDI ;
		_surf_backBuffer->createHBitmap( width , height ) ;
		KGraphicGDI::_backBufferDC = _surf_backBuffer->_surfaceHDC ;
		_surf_colorHolder = new KGraphicGDI ;
		_surf_colorHolder->createHBitmap( 64,64 ) ;
	
		KInput::initInput( _hwnd ) ;
		KMiscTools::initMiscTools() ;


	//	MessageBox( 0, gdiDetect , microsoftDetect ,0 ) ;
		_capsDetected = true ;
			
		isAccelerated = false ;
		
//		K3D::initK3D( width,height ) ;
		setDefaultWorldView( ) ;	

		return true ;
}

//gamma intensity
void		KWindowGDI::setGamma( float	gammai )
{
	_gamma = gammai ;
}

bool		KWindowGDI::getRectangleTexCap( void ) 		//returns true if rectangle is possible
{
	return true ;
}

void		KWindowGDI::setRectangleTexCap( bool	forceRectangleCap ) 		//returns true if rectangle is possible
{
	 hasRectangleText = forceRectangleCap ;
	
	 
}


bool		KWindowGDI::getAccelerationCap( void )		//returns true if accelerated
{
	return false ;
}
	
HWND	KWindowGDI::getWindowHandle(void ) 
{
	return	_hwnd ;
}

//sets the title of the window
void		KWindowGDI::setTitle( const char *title )
{

	SetWindowText( _hwnd , title ) ;
}

void		KWindowGDI::setClearColor( float r , float g , float b , float a )
{
	_clearR = r ;
	_clearG = g ;
	_clearB = b ;
	_clearA =a ;
	
}


bool		KWindowGDI::hasFocus()
{
	return GetForegroundWindow( ) == _hwnd ;
}


void		KWindowGDI::setMaxFrameRate( long	desiredFrameRate )
{
	if ( desiredFrameRate > 0 )
	{
		_maxFrameRate = 1000 / desiredFrameRate ;
	}

	if ( desiredFrameRate == 0 ) 	
	{
		_maxFrameRate = 0 ;
	}
	
	if ( desiredFrameRate < 0 ) 	
	{
		_maxFrameRate = 0 ;
//			if ( _isWaitVBLSupported == true )			WaitVBL( 0 ) ;	

	}

}



bool			KWindowGDI::saveBackBuffer( const char * cpcFileName , long	imageFormat , long resizeW , long resizeH )
{
/*
    unsigned char * header = (unsigned char *)"012345678901234567" ;
    unsigned char		*pixelsBack ;		//pixels in the backbuffer
    unsigned	long	 pixelsize ; 
    KGraphicGL	*backBufGrab ;
    
    //	FILE *f ;
    backBufGrab = new KGraphicGL ;
    backBufGrab->grabBackBuffer( NULL) ;
    if ( resizeW > 0 && resizeH > 0 )
    {
        backBufGrab->stretchAlphaRect( 0,0,_windowWidth , _windowHeight  , 0,_windowHeight-resizeH,resizeW , _windowHeight ) ;
    }
    else
    {
        resizeW = _windowWidth ;
        resizeH 	= _windowHeight ;
    }
    
    
    
    //force tout en 32 bits
    pixelsize = 4 ;
    
    pixelsBack = new unsigned char[resizeW*resizeH*pixelsize] ;
    if ( pixelsBack == NULL )	return	K_ERROR ;
    
    glReadBuffer( GL_BACK ) ;
    
    glReadPixels( 0 , 0 , resizeW , resizeH , GL_RGBA , GL_UNSIGNED_BYTE , pixelsBack ) ;
    
    for( int i=0 ; i < resizeW*resizeH*pixelsize ; i+=4 )
    {
        char	c = pixelsBack[ i ] ;
        pixelsBack[ i ] = pixelsBack[ i + 2 ] ;
        pixelsBack[ i  + 2 ] = c ;
    }
    
    CxImage		*cix ;
    
    
    cix = new  CxImage ;
    cix->CreateFromArray( pixelsBack , resizeW , resizeH , 32 , resizeW*4 , false ) ;
    
    
    switch( imageFormat )
    {
    case K_IMAGE_BMP:
        cix->Save( cpcFileName , CXIMAGE_FORMAT_BMP ) ;
        break ;
    case K_IMAGE_JPG:
        cix->Save( cpcFileName , CXIMAGE_FORMAT_JPG ) ;
        break ;
    case K_IMAGE_TGA:
        cix->Save( cpcFileName , CXIMAGE_FORMAT_TGA ) ;
        break ;
    case K_IMAGE_PNG:
        cix->Save( cpcFileName , CXIMAGE_FORMAT_PNG ) ;
        break ;
    }
    
    delete	cix ;
    
    
    delete	[]	pixelsBack ;
    
    backBufGrab->blitRect( 0,0,_windowWidth , _windowHeight ,10 ,10 ) ;
    delete	backBufGrab ;
    */
    return K_OK ;
}

void		KWindowGDI::flipBackBuffer( bool	waitForBackWindow , bool restoreView  ) 
{
MSG		Msg ;
static	long	t1 = 0 ;
unsigned 	long		t2 , frameRenderTime ;


	if ( _displayPTKMouse == true )
	{	
		setDefaultWorldView( ) ;
		KInput::displayMouse( ) ;
	}

	t2 =	KMiscTools::getMilliseconds( ) ;

	if ( _maxFrameRate >= 0 )
	{
//		if ( _isWaitVBLSupported == true )			WaitVBL( 1 ) ;
	}
	

	//gamma
	if ( _gamma < 1 )
	{
		doGammaAdjustment( ) ;
	}

//	SwapBuffers( _hDC ) ;
//to do

	if ( restoreView == true )
	{
		setDefaultWorldView( ) ;
	}
	processEvents( ) ;


	if ( _surf_backBuffer != 0 )
	{
		BitBlt ( _windowDC , 0,0,_windowWidth,_windowHeight , _surf_backBuffer->_surfaceHDC , 0,0 , SRCCOPY ) ;
	}

	//adjust the tempo so we don't get faster than the requested frame rate
	if ( _maxFrameRate > 0 )
	{
		frameRenderTime	= t2-t1 ;
		if ( frameRenderTime < 0 )
		{
			frameRenderTime = 0 ;
		}
		
		if ( frameRenderTime <= _maxFrameRate && frameRenderTime >= 0 )		//+de 100 fps !!! la folie! ?
		{
			//pause
			do
			{
				t2 =	KMiscTools::getMilliseconds( ) ;
				
				frameRenderTime	= t2-t1 ;

			//	snprintf( buffer , 255 , "t2=%d  frametime=%d" , t2 , frameRenderTime ) ;
			//	KWindowGDI::setTitle( buffer)  ;
			}while( frameRenderTime <_maxFrameRate ) ;
		}
	}
	
	t1 =	KMiscTools::getMilliseconds( ) ;

	
	if ( waitForBackWindow == false )		return ;
	//test si le jeu est en arriere plan
	if ( GetForegroundWindow( ) == _hwnd )		return ;

	//oui il y est ! donc on pause pour ne pas bouffer du temps cpu
	do
	{
		if ( GetMessage( &Msg, NULL, 0, 0  ) )
		{
				TranslateMessage( &Msg );
				DispatchMessage( &Msg ); 
		}
	}while((GetForegroundWindow( ) != _hwnd ) && IsWindow( _hwnd ) ) ;

	KMiscTools::freezeTimer( ) ;


}

void		KWindowGDI::doGammaAdjustment( void )
{
/*
float	realgamma ;
float	x1,y1,x2,y2 ;

	setDefaultWorldView( ) ;
	
	realgamma = 1-_gamma ;
	if ( realgamma < 0 )		realgamma = 0 ;
//	KGraphic::drawRect( 0,0, _windowWidth , _windowHeight  , 0,0,0,realgamma );
	x1 = 0 ;
	y1 = 0 ;
	x2 = _windowWidth ;
	y2 = _windowHeight ;
	
   y2 = _windowHeight - y2 ;
    y1 =_windowHeight - y1 ;
    
    
    glDisable( GL_TEXTURE_2D) ;
    glDisable( GL_TEXTURE_RECTANGLE_NV ) ;
    glEnable( GL_BLEND ) ;
    
        glBlendFunc(  GL_SRC_ALPHA , GL_ONE_MINUS_SRC_ALPHA  );
           glColor4f(0,0,0 ,realgamma ) ;
    //	destY	 = screenHeight -destY ;
    
    glBegin(GL_QUADS);
    glVertex3i( x1 ,y1, 0);  
	  	glVertex3i( x2 , y1, 0);
        glVertex3i( x2 , y2 , 0);
        glVertex3i( x1, y2, 0 );	    	    		
        glEnd();
        
        glDisable( GL_BLEND ) ;
        glColor4f( 1.0f , 1.0f ,1.0f ,1.0f ) ;
        
        
        KGraphicGL::_oldBindedText = -1 ;
*/        
}

//retourne le quit
bool		KWindowGDI::isQuit( void )
{
	return _quit ;
}


//true for fullscreen, false for windowed
bool	KWindowGDI::toggleFullScreen( bool 	fullscreen )
{
RECT	r ;

	//are we already in fullscreen ?
	if ( _fullscreen == true && fullscreen == true	)		return _fullscreen;
	//are we already in windowed ?
	if ( _fullscreen == false && fullscreen == false	)		return _fullscreen;


	//switch to windowed
	if ( fullscreen == false && IsWindow( _hwnd )  )
	{

			//restore the desktop
			RestoreResolution( ) ;
			//we need a width*height window
			SetRect( &r , 0 , 0 , _windowWidth , _windowHeight ) ;
			//calculate the client rect
			AdjustWindowRect( &r , WS_CAPTION | WS_SYSMENU | WS_VISIBLE | WS_MINIMIZEBOX  , false ) ;
			long	screenWidth 	= GetSystemMetrics( SM_CXSCREEN ) ;
			long	screenHeight = GetSystemMetrics( SM_CYSCREEN ) ;
		
			SetWindowLong( _hwnd ,GWL_STYLE , WS_CAPTION | WS_SYSMENU | WS_VISIBLE | WS_MINIMIZEBOX ) ;
			MoveWindow(  _hwnd , (screenWidth-(r.right-r.left))/2,(screenHeight-(r.bottom-r.top))/2, r.right-r.left,r.bottom-r.top  ,true ) ;
			UpdateWindow( _hwnd  ) ;
			SetWindowLong( _hwnd ,GWL_STYLE , WS_CAPTION | WS_SYSMENU | WS_VISIBLE | WS_MINIMIZEBOX ) ;
			MoveWindow(  _hwnd , (screenWidth-(r.right-r.left))/2,(screenHeight-(r.bottom-r.top))/2, r.right-r.left,r.bottom-r.top  ,true ) ;
			UpdateWindow( _hwnd  ) ;
			_fullscreen = false ;
			return _fullscreen ;
	}

	//switch to fullscreen
	if ( fullscreen == true && IsWindow( _hwnd )  )
	{
			SwitchToResolution( _windowWidth , _windowHeight , _windowDepth) ;
			SetWindowLong( _hwnd ,GWL_STYLE , WS_POPUP | WS_VISIBLE  ) ;
			//calculate the client rect
			MoveWindow(  _hwnd , 0,0,_windowWidth,_windowHeight,true ) ;
			UpdateWindow( _hwnd ) ;
			_fullscreen = true ;
			return _fullscreen ;
	}
	
	return _fullscreen ;
}



void			KWindowGDI::setClipping( long x1, long y1, long x2 , long y2 )
{
long		 w, h ;
	
	w = x2-x1 ;
	h = y2-y1 ;
	
	y1 = _windowHeight-y1 ;
	y2 = _windowHeight-y2 ;
	

 
}
void			KWindowGDI::enumerateDisplays( ptkEnumDisplayCallBack  functionPtr )
{

DEVMODE		dv ;
long 					 i ;
static	KDisplay			dp ;

	if ( functionPtr == NULL )		return ;

	i = 0 ;	

	while( EnumDisplaySettings( NULL , i , &dv ) > 0 )
	{
		dp.width 		= 	dv.dmPelsWidth ;
		dp.height 		=	dv.dmPelsHeight ;
		dp.depth 		= 	dv.dmBitsPerPel ;
		dp.frequency  = 	dv.dmDisplayFrequency ;
		
		if ( false == functionPtr( &dp )  )		return ;		
		i++ ;	
	}
}


//change la resolution de l'ecran
bool			KWindowGDI::SwitchToResolution( short	width , short	height , short depth ) 
{
DEVMODE		dv2 ;
	
	if ( depth<= 0 )		depth = 16 ;
	
	dv2.dmSize  = sizeof( DEVMODE ) ;
	dv.dmSize  = sizeof( DEVMODE ) ;

	if ( width > 0 && height > 0 )
	{
		//get the current resolution
		dv.dmFields 	=  DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT   ;
		dv2.dmFields =  DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT  ;
		dv2.dmDisplayFrequency = 75 ;
		EnumDisplaySettings( NULL , ENUM_CURRENT_SETTINGS , &dv ) ;
	}
	else
	{
		//get the current depth and frequency
		dv.dmFields 	=  DM_BITSPERPEL | DM_DISPLAYFREQUENCY ;
		dv2.dmFields =  DM_BITSPERPEL |DM_DISPLAYFREQUENCY  ;
		EnumDisplaySettings( NULL , ENUM_CURRENT_SETTINGS , &dv ) ;
		dv2.dmDisplayFrequency = dv.dmDisplayFrequency ;
	}


	dv2.dmBitsPerPel = depth ;
	dv2.dmPelsWidth	 = width ;
	dv2.dmPelsHeight = height ;
	
	if ( DISP_CHANGE_SUCCESSFUL == ChangeDisplaySettings(  &dv2,   CDS_FULLSCREEN ) )	
	{
		return K_OK ;
	}
	else
	{
		dv.dmFields 	=  DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT | DM_DISPLAYFREQUENCY  ;
		dv2.dmFields =  DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT   ;
		dv.dmDisplayFrequency = 0 ;
		EnumDisplaySettings( NULL , ENUM_CURRENT_SETTINGS , &dv ) ;
		if ( DISP_CHANGE_SUCCESSFUL == ChangeDisplaySettings(  &dv2,   CDS_FULLSCREEN ) )	
		{
			return K_OK ;
		}
	}
	
	return K_ERROR ;
 }

//restore la resolution
void		KWindowGDI::RestoreResolution( void ) 
{
	//on ne restitue que si ca avait switché
//	if ( dv.dmPelsHeight == 0 )	return ;
	
	ChangeDisplaySettings( &dv ,   CDS_FULLSCREEN ) ;
//Passing NULL for the lpDevMode parameter and 0 for the dwFlags parameter is the 
//easiest way to return to the default mode after a dynamic mode change. 
//	ChangeDisplaySettings( 0,0) ;
}


//destroys the window
void		KWindowGDI::terminate( void ) 
{
	_quit = true ;
	PostQuitMessage( 0 ) ;
}




//process the events
void		KWindowGDI::processEvents( void )
{
MSG		Msg ;
static	long	screnshot = 0 ;
static	char	ssfilename[260] ;

		if ( KInput::isPressed( K_VK_L_SHIFT ) )
		{
			if ( KInput::isPressed( K_VK_SNAPSHOT ) || KInput::isPressed( K_VK_F12 ) )
			{
				screnshot++ ;
				sprintf( ssfilename , "screenshot%d.tga" , screnshot  ) ;
			
				saveBackBuffer( KMiscTools::makeFilePath( ssfilename ) , K_IMAGE_TGA , 0 , 0 ) ;
				KInput::waitForKeyRelease( K_VK_SNAPSHOT ) ;
				KInput::waitForKeyRelease( K_VK_L_SHIFT ) ;			
			}
		}
		
			if ( PeekMessage( &Msg, NULL, 0, 0 , PM_REMOVE ) )
			{
				TranslateMessage( &Msg );
				DispatchMessage( &Msg ); 
			}
			
		//	Sleep( 1 ) ;
}

void			KWindowGDI::minimize( void )
{
	ShowWindow( _hwnd , SW_MINIMIZE ) ;
}

void			KWindowGDI::restore( void )
{
	ShowWindow( _hwnd , SW_SHOWNORMAL ) ;
}




LRESULT CALLBACK	KWindowGDI::GameWindowProc( HWND hWnd, UINT messg,	WPARAM wParam, LPARAM lParam ) 
{
KEvent	kEvent ;

KWindowGDI		*kwGDI= NULL ;

	kwGDI =(KWindowGDI*)GetWindowLong( hWnd , GWL_USERDATA ) ;

	if ( kwGDI != NULL )
	{
		if ( kwGDI->_userCallback != NULL )
		{
			if ( kwGDI->_userCallback( hWnd , messg , wParam , lParam ) == false )	return 0 ;
		}
		
		//native PTK event system ( multiplatform )
		if ( kwGDI->_ptkCallback != NULL )
		{		
		kEvent.type 		= K_EVENT_NULL ;
		kEvent.buttonIndex =  0 ;
		kEvent.nativeMessage 	= messg ;
		kEvent.mouseX = KInput::getMouseX( ) ;
		kEvent.mouseY = KInput::getMouseY( ) ;
		kEvent.nativeData = lParam ;
		kEvent.ptkKey = K_VK_ERROR ;
		
		switch( messg )
		{
			case	WM_CONTEXTMENU:
				kEvent.type = K_EVENT_CONTEXTMENU ;					
			break ;
				
			case	WM_MOUSEMOVE:
				kEvent.type = K_EVENT_MOUSEMOVE ;
			break;
			case	WM_LBUTTONDOWN:
				kEvent.type = K_EVENT_MOUSEDOWN ;
				kEvent.buttonIndex = K_LBUTTON ;
			break;
			case	WM_LBUTTONDBLCLK:
				kEvent.type = K_EVENT_DBLCLICK ;
				kEvent.buttonIndex = K_LBUTTON ;
			break;
			case	WM_RBUTTONDBLCLK:
				kEvent.type = K_EVENT_DBLCLICK ;
				kEvent.buttonIndex = K_RBUTTON ;
			break;
			
			case	WM_LBUTTONUP:
				kEvent.type = K_EVENT_MOUSEUP ;
				kEvent.buttonIndex = K_LBUTTON ;
			break;
			case	WM_RBUTTONDOWN:
				kEvent.type = K_EVENT_MOUSEDOWN ;				
				kEvent.buttonIndex = K_RBUTTON ;
			break;
			case	WM_RBUTTONUP:
				kEvent.type = K_EVENT_MOUSEUP ;
				kEvent.buttonIndex = K_RBUTTON ;
			break;
			case	WM_MBUTTONDOWN:
				kEvent.type = K_EVENT_MOUSEDOWN ;
				kEvent.buttonIndex = K_MBUTTON ;
			break;
			case	WM_MBUTTONUP:
				kEvent.type = K_EVENT_MOUSEUP ;
				kEvent.buttonIndex = K_MBUTTON ;
			break;
			case	WM_MOUSEWHEEL:
				kEvent.type = K_EVENT_WHEEL ;
				kEvent.wheel =  HIWORD(wParam) ;
				KInput::setLastWheelValue( kEvent.wheel ) ;
			break;
			case	WM_CHAR:
				kEvent.type = K_EVENT_CHAR ;
				kEvent.character =  wParam ;
			break;
			case	WM_KEYDOWN:
				kEvent.type = K_EVENT_KEYDOWN ;
				kEvent.virtualKey 	=	wParam  ;
				kEvent.ptkKey =  KInput::getPTKKey( wParam ) ;
				kEvent.character 	= 	( lParam >> 16 ) & 0x000000ff ;
			break;
			case	WM_KEYUP:
				kEvent.type 	= K_EVENT_KEYUP ;
				kEvent.ptkKey =  KInput::getPTKKey( wParam ) ;
				kEvent.virtualKey 	=	wParam  ;
				kEvent.character 	= 	wParam  ;
			break;
		}
		

		if ( kwGDI->_ptkCallback( &kEvent ) == false )	return 0 ;
	}
	
	}
		
	switch(messg)
	{	
	/*	case	WM_PAINT:
			if ( kwGL != NULL)	
			{
				if (kwGL->hasFocus(  ) == false )
				{
					PAINTSTRUCT	ps ;
					HDC	hdc = BeginPaint( hWnd , &ps ) ;
						kwGDI->flipBackBuffer( ) ;
					EndPaint( hWnd , &ps ) ;	
				}
			}
		break ;
		*/
		

		case	WM_ACTIVATEAPP:
			if ( kwGDI == NULL )		break ;

				if ( wParam == false )
				{
						if ( kwGDI->_fullscreen == true && IsWindow( kwGDI->_hwnd )  )
						{
							if ( kwGDI )	kwGDI->RestoreResolution( ) ;
							ShowWindow( kwGDI->_hwnd , SW_MINIMIZE ) ;
						}
				}
				else
				{
						if ( kwGDI->_fullscreen == true && IsWindow( kwGDI->_hwnd ) )
						{
							if ( kwGDI )	kwGDI->SwitchToResolution( kwGDI->_windowWidth ,kwGDI-> _windowHeight , kwGDI->_windowDepth) ;
						}
				
				}
						
		break ;
		case	WM_MOUSEWHEEL:
			KInput::setLastWheelValue(  HIWORD(wParam) );
		break;
		case	WM_CLOSE:
			
			if (kwGDI ) 	{kwGDI->_quit = true ; }
			
		break;
		case WM_DESTROY:
				if (kwGDI ) 	{kwGDI->_quit = true ; }
		//PostQuitMessage( 0 );
		break;
	
		default:
			return( DefWindowProc( hWnd, messg, wParam, lParam ) );
	}
	
	return	0 ;
	
}
