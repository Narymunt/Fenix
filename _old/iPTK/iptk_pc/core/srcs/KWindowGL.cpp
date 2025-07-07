
#include	"KwindowGL.h"
#include	"KGlobals.h"
#include	<stdio.h>
#include	"KMiscTools.h"
#include	"KInput.h"
#include	"KGraphicGL.h"
//#include	"K3D.h"
//#include	<complex.h>
#include	<math.h>
#include	"glati.h"
#include	"trial.h"
#include	"ximage.h"

#ifndef	WM_MOUSEWHEEL
#define	WM_MOUSEWHEEL                   0x020A
#endif






void DrawLineMacro( float	x1, float y1 , float	x2 , float y2 , float r ,float g ,float b ,  float blend , float _windowHeight) ;

void DrawLineMacro( float	x1, float y1 , float	x2 , float y2 , float r ,float g ,float b ,  float blend , float _windowHeight)
{
    y2 = _windowHeight - y2 ;   
     y1 = _windowHeight - y1 ;
    glEnable( GL_BLEND ) ;    
    glBlendFunc(  GL_SRC_ALPHA , GL_ONE_MINUS_SRC_ALPHA  );	\
    glDisable( GL_TEXTURE_2D) ;
    glColor4f( r , g , b ,blend ) ;
	glBegin (GL_LINE_LOOP);
	glVertex2f (x1,y1);
    glVertex2f (x2,y2);
    glEnd( ) ;
    glDisable( GL_BLEND ) ;
    glColor4f( 1.0f , 1.0f ,1.0f ,1.0f ) ; 
}
struct		swaterMark
{
	float	x,y ;
};
//swaterMark	wateraP[10] = { -23,-3,-11,-3,-9,1,-8,1,-10,4,-12,6,-18,6,-18,12,-23,12 , -23,-3 } ;
//swaterMark	wateraT[9] = { -8,-3, 7,3,7,1, 2,1, 0,12, -5,12, -4,1,-8,0 , -8,-3 } ;
//swaterMark	wateraK[12] = { 7,13,14,-3,14,1,19,-3,25,-3,19,4,24,12,16,12,13,6,13,12,6,12 , 7,13 } ;

typedef		void			 (APIENTRY * PFNGLWAITVBLPROC ) ( GLint  frameCount );
PFNGLWAITVBLPROC		WaitVBL = NULL ;

//LRESULT CALLBACK	KWindowGL::GameWindowProc( HWND hWnd, UINT messg,	WPARAM wParam, LPARAM lParam ) 

/*
bool				KWindowGL::_isWaitVBLSupported = false ;
short				KWindowGL::_windowWidth , KWindowGL::_windowHeight , KWindowGL::_windowDepth  ;
HGLRC			KWindowGL::_openGLContext ;
DEVMODE	KWindowGL::dv ;
HDC				KWindowGL::_hDC ;
bool				KWindowGL::_quit ;
HWND			KWindowGL::_hwnd ;
unsigned	long		KWindowGL::_maxFrameRate = 14 ;
bool				KWindowGL::hasRectangleText = false ;
bool				KWindowGL::isAccelerated = false ;
bool				KWindowGL::_use3d = false ;
bool				KWindowGL::_fullscreen = false ;
float				KWindowGL::_gamma = 1 ;
bool				KWindowGL::_silent = false ;
bool				KWindowGL::_capsDetected = false ;
*/

//bool				KWindowGL::_gammaChanged = false ;
//short				KWindowGL::gammaTable[3*256] ;
//#define			 PATmax(a,b) (((a)>(b))?(a):(b))
//#define 			PATmin(a,b) (((a)<(b))?(a):(b))

KWindowGL::KWindowGL( ) 
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
    _hwndParent = 0 ;
}

KWindowGL::KWindowGL( bool 	use3D) 
{
    _hwndParent = 0 ;
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


}

void	 	KWindowGL::setParentWindow( HWND	hwndParent ) 
{
	_hwndParent = hwndParent ;
}

long		KWindowGL::getWindowWidth( void ) 
{
	return _windowWidth ;
}

long		KWindowGL::getWindowHeight( void ) 
{
	return _windowHeight ;

}


//the basic world
void		KWindowGL::setDefaultWorldView( void ) 
{
    setWorldView( 0,0,0,1.0f , false )  ;
}


//permet de creer un etat global du jeu
void		KWindowGL::setWorldView( float	translateX , float		translateY ,   float	rotation , float 	zoom, bool	clearworld  )
{
//    _oldBindedText = -1 ;
    
    glMatrixMode(GL_PROJECTION);      
    
    glLoadIdentity();
    glOrtho(0, _windowWidth ,0, _windowHeight , -100 , 100 );
    glMatrixMode(GL_MODELVIEW);
    
    if ( clearworld == true )	
    {
      	glClearColor( _clearR ,_clearG ,_clearB ,_clearA  ) ;
      	glClear(GL_COLOR_BUFFER_BIT );
    }
    
    glLoadIdentity();
    /*
    glTranslatef( (float)(_windowWidth / 2) , (float)(_windowHeight/2) ,0 ) ;
    glRotatef( rotation , 0.0f , 0.0f ,1.0f ) ; 		
    glScalef( zoom ,zoom , 0 ) ;
    glTranslatef( (float)(_windowWidth / -2) , (float)(_windowHeight/-2) ,0 ) ;
    
    glTranslatef( translateX , translateY  ,0 ) ;
    */
    
       glTranslatef( (float)(_windowWidth / 2) , (float)(_windowHeight/2) ,0 ) ;
//    glTranslatef( translateX  , translateY  ,0 ) ;
    glRotatef( rotation , 0.0f , 0.0f ,1.0f ) ;
    glScalef( zoom ,zoom , 0 ) ;
    glTranslatef( (float)(_windowWidth / -2) , (float)(_windowHeight/-2) ,0 ) ;
	if ( zoom != 0 )
	{
    		glTranslatef( translateX / zoom, translateY / zoom ,0 ) ;
    }
    
    glDisable(GL_DEPTH_TEST);							// Enables Depth Testing
    glViewport( 0 , 0 , _windowWidth,_windowHeight ) ;
	glEnable (GL_DITHER);
    
}

/*
void KWindowGL::saveGammaRamp( void )
{
HDC	desktopWindowDC ;

	desktopWindowDC = GetDC( GetDesktopWindow() ) ;
	
	_gammaChanged = GetDeviceGammaRamp(desktopWindowDC , gammaTable );
   	ReleaseDC( GetDesktopWindow() , desktopWindowDC  ) ;
  
}
/*
void 	KWindowGL::restoreGammaRamp( void ) 
{
HDC	desktopWindowDC ;

	if ( _gammaChanged == false )		return ;

	desktopWindowDC = GetDC( GetDesktopWindow() ) ;
	
	_gammaChanged = SetDeviceGammaRamp(desktopWindowDC , gammaTable );
   	ReleaseDC( GetDesktopWindow() , desktopWindowDC  ) ;
   
}

	
void w32_setGamma(double gamma , HDC hDC )
{
   int        i;
   double    div;
   unsigned short    gammaramp[3*256];
   int        value;
	 bool    res;

//   if(!hDC)       return;

   res = GetDeviceGammaRamp(hDC,gammaramp);
   //m_ConsPrint("GammaGet : %d\n",(int)res);

   //gamma = 2.0f;
   div = 1/256.0f;

   for(i=0 ; i<256 ; i++)
   {
       value = (int)PATmin(65535.0,PATmax(0,pow((double)i*div,gamma)*65535.0));
       //m_ConsPrint("%d\n",value);
       gammaramp[i+512] = gammaramp[i+256] = gammaramp[i] = value;
   }

   res = SetDeviceGammaRamp(hDC,gammaramp);

}
/*
void KWindowGL::fadeGammaRamp( void )
{
   double	gamma ;
	HDC		desktopWindowDC ;

	saveGammaRamp( ) ;
	if ( _gammaChanged == false )		return ;
	


	desktopWindowDC = GetDC( GetDesktopWindow() ) ;

	for ( gamma = 1 ; gamma >= 0 ; gamma -= 0.005f ) 
	{
		w32_setGamma( gamma , desktopWindowDC) ;
		Sleep( 16 ) ;
	}


  	ReleaseDC( GetDesktopWindow() , desktopWindowDC ) ;
	
	restoreGammaRamp( ) ;
}
*/

void		KWindowGL::displayMouse( bool mousestate ) 
{
		_displayPTKMouse = mousestate ;

}


KWindowGL::~KWindowGL( ) 
{
	KInput::freeMouse( ) ;
	_userCallback 	= NULL ;
	_ptkCallback 	= NULL ;
	KInput::showPointer( ) ;
	wglMakeCurrent (NULL, NULL) ; 
	wglDeleteContext ( _openGLContext ); 
	ReleaseDC( _hwnd , _hDC ) ;
	if (IsWindow ( _hwnd  ))
	{
		DestroyWindow( _hwnd ) ;
		_hwnd = 0 ;
	}
	RestoreResolution( ) ;
	_quit = true ;
}


void		KWindowGL::setCallBack( ptkWindowCallBack  userProc ) 
{
	_userCallback = userProc ;
}

void		KWindowGL::setPTKCallBack( ptkNativeCallBack  userProc ) 
{
	_ptkCallback = userProc ;
}



//creates a window
bool		KWindowGL::createGameWindow( short  width , short height , short depth , bool windowed , const char *windowTitle )
{
WNDCLASS				wndClass ;
RECT						r ;
int							screenWidth , screenHeight ;
unsigned long		windowStyle = WS_CAPTION | WS_SYSMENU | WS_VISIBLE | WS_MINIMIZEBOX ;
bool						result ;
char						*glstrings ;


		_quit = false ;
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
		
		KGraphicGL::setScreenSize( width , height , depth ) ;
		if ( windowed == false )	
		{
			_fullscreen = true ;
				KInput::_fullScreen = _fullscreen ;

			SwitchToResolution( width , height , depth ) ;
			windowStyle = WS_POPUP | WS_VISIBLE  ;
		}
		else
		{
			_fullscreen = false  ;
				KInput::_fullScreen = _fullscreen ;

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
		wndClass.lpszMenuName	= NULL ;
		
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

	
		if ( _hwndParent != 0  )		windowStyle = WS_CHILD | WS_POPUP |	WS_VISIBLE ;

		//go baby !		
		if ( _silent == false )
		{
				if ( _hwndParent == 0  )	
				{
					_hwnd		=	CreateWindow( 		"PTK windowTitle"  ,
															windowTitle,
															windowStyle ,
															(screenWidth-(r.right-r.left))/2 ,			//centers the window
															(screenHeight-(r.bottom-r.top))/2,
															r.right-r.left	,	
															r.bottom-r.top  ,
															_hwndParent ,
															0 ,
															GetModuleHandle( NULL ) ,
															0 ) ;
					}
					else
					{
							GetClientRect( _hwndParent , &r ) ;
										_hwnd		=	CreateWindow( 		"PTK windowTitle"  ,
															windowTitle,
															windowStyle ,
															0 ,			
															0,
															r.right-r.left	,	
															r.bottom-r.top  ,
															_hwndParent ,
															0 ,
															GetModuleHandle( NULL ) ,
															0 ) ;
					}
		}
		else
		{
				_hwnd		=	CreateWindow( 		windowTitle ,
														windowTitle,
														WS_POPUP ,30,30 ,256,256	,		//centers the window
														0 ,
														0 ,
														GetModuleHandle( NULL ) ,
														0 ) ;		
		}
		
		if ( _hwnd == NULL  )	return K_ERROR ;		
		SetWindowLong( _hwnd , GWL_USERDATA , (long)this );

		if ( _silent == false )
		{
			setTitle( windowTitle ) ;
	//		ShowWindow( _hwnd, SW_SHOW );
			UpdateWindow( _hwnd );
		}
		KInput::initInputEx( _hwnd, width, height ) ;
	
		result = AttachOpenGLToWindow(  depth ) ;
	
		//on recherche la VBL si possible
		glstrings =  (char*)glGetString(GL_EXTENSIONS) ;
		
		
		if ( glstrings )
		{
			if ( strstr( glstrings , "GL_EXT_swap_control" ) != NULL )
			{
				_isWaitVBLSupported = true ;
			}
			
			//test des textures rectangulaires
			if ( strstr( glstrings , "GL_EXT_texture_rectangle" ) != NULL ||  strstr( glstrings , "GL_NV_texture_rectangle" ) != 0 )
			{
					hasRectangleText = true ;
			}
		}

		getRectangleTexCap( ) ;
		
		if ( _isWaitVBLSupported == true )
		{
			/* initialize function pointers for GL_EXT_Swap_control */
			WaitVBL = (PFNGLWAITVBLPROC)		wglGetProcAddress("wglSwapIntervalEXT");		
			//remplacer par un log
//			if ( WaitVBL == NULL 	)		KMiscTools::messageBox( "Problem receiving vbl information","ProcAddress pb" ) ;	
		}
		KGraphicGL::setScreenSize( width , height ,  depth ) ;
		KInput::initInputEx( _hwnd, width , height ) ;
		KMiscTools::initMiscTools(NULL) ;
		if ( _silent == false )
		{
			//cls de l'ecran
			glClearColor( 0,0,0,1.0f );
			glClear(GL_COLOR_BUFFER_BIT );
			glDisable(GL_LIGHTING) ;
			flipBackBuffer ( ) ;
		}
		glstrings =  (char*)glGetString(GL_VENDOR) ;
		char	microsoftDetect[2048] , gdiDetect[2048] ;
		
		memset( microsoftDetect ,0 , 2048 ) ;
		_snprintf( microsoftDetect , 2048 , "%s" , glstrings ) ;		
		strlwr( microsoftDetect ) ;
		
		glstrings =  (char*)glGetString(GL_RENDERER) ;
		memset( gdiDetect ,0 , 2048 ) ;
		strcpy( gdiDetect , glstrings ) ;
		strlwr( gdiDetect ) ;
		
	//	MessageBox( 0, gdiDetect , microsoftDetect ,0 ) ;
		_capsDetected = true ;
			
	//	isAccelerated = true ;
		if ( strstr( microsoftDetect ,"microsoft corporation" ) != 0 || strstr( gdiDetect ,"gdi generic" ) != 0)
		{
			isAccelerated = false ;
		}
		
//		K3D::initK3D( width,height ) ;
		setDefaultWorldView( ) ;	
		glViewport( 0 , 0 , width,height ) ;
		return result ;
}

//gamma intensity
void		KWindowGL::setGamma( float	gammai )
{
	_gamma = gammai ;
}

bool		KWindowGL::getRectangleTexCap( void ) 		//returns true if rectangle is possible
{
	 KGraphicGL::setRectangleTexSupport(hasRectangleText ) ;
	return hasRectangleText ;
}

void		KWindowGL::setRectangleTexCap( bool	forceRectangleCap ) 		//returns true if rectangle is possible
{
	 hasRectangleText = forceRectangleCap ;
	
	 
}


bool		KWindowGL::getAccelerationCap( void )		//returns true if accelerated
{
KWindowGL	*kw ;

	if ( _capsDetected == false )
	{
		kw = new KWindowGL ;
		_silent = true ;
		kw->createGameWindow( 640,480,16 , true ) ;
		_silent = false ;
		delete	kw ;
	}

	_quit = false ;
	return isAccelerated ;
}

bool		KWindowGL::setQuit( bool quitstate ) 
{
	_quit = quitstate ;
	return _quit ;
}

HWND	KWindowGL::getWindowHandle(void ) 
{
	return	_hwnd ;
}

//sets the title of the window
void		KWindowGL::setTitle( const char *title )
{
	#ifdef	TRIALVERSION
		SetWindowText( _hwnd , "Evaluation version - http://www.phelios.net" ) ;
		return ;	
	#endif
	
	SetWindowText( _hwnd , title ) ;
}

void		KWindowGL::setClearColor( float r , float g , float b , float a )
{
	_clearR = r ;
	_clearG = g ;
	_clearB = b ;
	_clearA =a ;
	
}


bool		KWindowGL::hasFocus()
{
	if ( IsIconic( _hwnd ) == true )		return false ;
	if ( GetForegroundWindow( ) == _hwnd ) return true ;
	
	return false ;
}



void		KWindowGL::setMaxFrameRate( long	desiredFrameRate )
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
			if ( _isWaitVBLSupported == true )			WaitVBL( 0 ) ;	

	}

}



bool			KWindowGL::saveBackBuffer( const char * cpcFileName , long	imageFormat , long resizeW , long resizeH )
{
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
    
    /*
    f = fopen( cpcFileName , "wb" ) ;
    if ( NULL != f )
    {
    memset( header , 0 ,  18 ) ;
    header[ 2 ] = 2 ;
    header[ 12 ] = (unsigned char)width & 0x00FF ;
    width = width >> 8 ;
    header[ 13 ] = (unsigned char)width & 0x00FF ;
    header[ 14 ] = (unsigned char)height & 0x00FF ;
    height = height >> 8 ;
    header[ 15 ] = (unsigned char)height & 0x00FF ;
    header[ 16 ] = 0x20 ;
    header[ 17 ] = 0x08 ;
    fwrite( header , 1 , 18 , f ) ;
    fwrite( pixelsBack , 1 , screenWidth*screenHeight*pixelsize , f ) ;
    fclose( f ) ;
    }
    */
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
    
    return K_OK ;
}

void		KWindowGL::flipBackBuffer( bool	waitForBackWindow , bool restoreView  ) 
{
MSG		Msg ;
static	long	t1 = 0 ;
unsigned 	long		t2 , frameRenderTime ;

#ifdef			TRIALVERSION
swaterMark	waterP[10] = { -23,-3,-11,-2,-9,1,-8,1,-10,4,-12,6,-18,6,-18,12,-23,12 , -23,-3 } ;
swaterMark	waterT[9] = { -8,-3,   7,-3   ,  7,1   ,   2,1,   2,12, -5,12, -5,1,-8,0 , -8,-3 } ;
swaterMark	waterK[12] = { 8,-3,  15,-3  ,15,1, 20,-3, 27,-3,20,4,26,12,17,12,14,6,14,12,7,12 , 8,-3 } ;
#endif
/*

//char	buffer[256] ;
static	bool gravvideo = false  ;
HDC		wdc ;

	if ( gravvideo == true )
	{
		wdc = GetDC( _hwnd ) ;
		BitBlt( qt_Bitmap.gworldDC , 0,0,800,600,wdc ,0,0,SRCCOPY ) ;
		ourMovie.addFrame( &qt_Bitmap , 16 ) ;
		ReleaseDC( _hwnd ,  wdc ) ;
	}
	
	if ( KInput::isPressed( K_VK_W ) )	gravvideo = true ;
	if ( KInput::isPressed( K_VK_E ) )	gravvideo = false ;
*/
	if ( _displayPTKMouse == true )
	{	
		setDefaultWorldView( ) ;
		KInput::displayMouse( ) ;
	}

	t2 =	KMiscTools::getMilliseconds( ) ;

/*
char buf[50];
	sprintf( buf , "%d" , _maxFrameRate ) ;
	KWindowGL::setTitle( buf ) ;
	*/
	
	if ( _maxFrameRate >= 0 )
	{
		if ( _isWaitVBLSupported == true )			WaitVBL( 1 ) ;
	}
	
	



	//gamma
	if ( _gamma < 1 )
	{
		doGammaAdjustment( ) ;
	}

	SwapBuffers( _hDC ) ;
	if ( restoreView == true )
	{
		setDefaultWorldView( ) ;
	}
	processEvents( ) ;


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
			//	KWindowGL::setTitle( buffer)  ;
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

void		KWindowGL::doGammaAdjustment( void )
{
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
        
}

//retourne le quit
bool		KWindowGL::isQuit( void )
{
	return _quit ;
}

//select a pixel format etc...
bool		KWindowGL::AttachOpenGLToWindow( short depth )
{
PIXELFORMATDESCRIPTOR		 pixelFormatDesc ;
int												result ;


		_hDC	=	GetDC( _hwnd ) ;

		result = FillAndSelectPixelFormat( _hDC , &pixelFormatDesc , depth ) ;
		if ( result == 0 )		
		{
//			KMiscTools::messageBox( "Could not select fixel format" , "OpenGl error : video drivers probably missing." ) ;
			return K_ERROR ;
		}
 
 	
		_openGLContext	=	 wglCreateContext( _hDC ) ;
		if ( _openGLContext	 == NULL )		
		{
//			KMiscTools::messageBox( "Could not create openGL Context" , "OpenGl error" ) ;
			return K_ERROR ;
		}
		
		 result	=	wglMakeCurrent( _hDC , _openGLContext ) ;
 		if ( result == false )	
 		{
//	 		KMiscTools::messageBox( "Could not make  openGL Context" , "OpenGl error" ) ;
			return K_ERROR ;
 		}
 				
 		return K_OK ;
}

//true for fullscreen, false for windowed
bool	KWindowGL::toggleFullScreen( bool 	fullscreen )
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
				KInput::_fullScreen = _fullscreen ;

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
				KInput::_fullScreen = _fullscreen ;

			return _fullscreen ;
	}
		KInput::_fullScreen = _fullscreen ;

	return _fullscreen ;
}



int		KWindowGL::FillAndSelectPixelFormat( HDC		hdc , PIXELFORMATDESCRIPTOR		*pixelFormatDesc , short depth )
{
int		pfmIndex ;


	pixelFormatDesc->nSize			=	sizeof( PIXELFORMATDESCRIPTOR ) ;
	pixelFormatDesc->nVersion	=	1 ; 
	pixelFormatDesc->dwFlags		=	 PFD_DOUBLEBUFFER | PFD_GENERIC_ACCELERATED | PFD_GENERIC_FORMAT | PFD_SUPPORT_OPENGL   ; 
	pixelFormatDesc->dwFlags		=	 PFD_DOUBLEBUFFER ; 
//	pixelFormatDesc->dwFlags		=	 PFD_SWAP_LAYER_BUFFERS | PFD_SUPPORT_GDI | PFD_GENERIC_FORMAT   ; 
	pixelFormatDesc->iPixelType 	=	PFD_TYPE_RGBA  ;
	pixelFormatDesc->cColorBits 	=	(char)depth ;
	pixelFormatDesc->cRedBits	=	0 ;
	pixelFormatDesc->cRedShift	=	0 ;
	pixelFormatDesc->cGreenBits				= 	0 ;
	pixelFormatDesc->cGreenShift			= 	0 ;
	pixelFormatDesc->cBlueBits				= 	0 ;
	pixelFormatDesc->cBlueShift				= 	0 ;
	pixelFormatDesc->cAlphaBits				= 	8 ;
	pixelFormatDesc->cAlphaBits				= 	0 ;
	pixelFormatDesc->cAlphaShift			=	0 ;
	pixelFormatDesc->cAccumBits			=	0 ;
	pixelFormatDesc->cAccumRedBits		=	0 ;
	pixelFormatDesc->cAccumGreenBits	=	0 ;
	pixelFormatDesc->cAccumBlueBits		=	0 ;
	pixelFormatDesc->cAccumAlphaBits	=	0; 
	pixelFormatDesc->cDepthBits				=	0; 
	pixelFormatDesc->cStencilBits			=	0	; 
	
	if ( _use3d == true )
	{
		pixelFormatDesc->cDepthBits			=	16; 
	//	pixelFormatDesc->cStencilBits		=	1	; 
	}

	pixelFormatDesc->cAuxBuffers			=	0	; 
	pixelFormatDesc->iLayerType				=	PFD_MAIN_PLANE ; 
	pixelFormatDesc->bReserved				=	0	; 
	pixelFormatDesc->dwLayerMask			=	0	; 
	pixelFormatDesc->dwVisibleMask		=	0; 
	pixelFormatDesc->dwDamageMask		=	0	; 
	
	pfmIndex	=	 ChoosePixelFormat( hdc , pixelFormatDesc ) ;
	if ( pfmIndex != 0 )	
	{
		SetPixelFormat(hdc, pfmIndex, pixelFormatDesc); 
		isAccelerated = true ;
		return	pfmIndex ;
	}
	else
	{		
		//hardware mode could not be set, let's try a software rendering	
		isAccelerated = true ;
	}

pixelFormatDesc->nSize			=	sizeof( PIXELFORMATDESCRIPTOR ) ;
	pixelFormatDesc->nVersion	=	1 ; 
	pixelFormatDesc->dwFlags		=	 PFD_DOUBLEBUFFER     ; 
//	pixelFormatDesc->dwFlags		=	 PFD_SWAP_LAYER_BUFFERS | PFD_SUPPORT_GDI | PFD_GENERIC_FORMAT   ; 
	pixelFormatDesc->iPixelType 	=	PFD_TYPE_RGBA  ;
	pixelFormatDesc->cColorBits 	=	(char)depth ;
	pixelFormatDesc->cRedBits	=	0 ;
	pixelFormatDesc->cRedShift	=	0 ;
	pixelFormatDesc->cGreenBits				= 	0 ;
	pixelFormatDesc->cGreenShift			= 	0 ;
	pixelFormatDesc->cBlueBits				= 	0 ;
	pixelFormatDesc->cBlueShift				= 	0 ;
	pixelFormatDesc->cAlphaBits				= 	0 ;
	pixelFormatDesc->cAlphaShift			=	0 ;
	pixelFormatDesc->cAccumBits			=	0 ;
	pixelFormatDesc->cAccumRedBits		=	0 ;
	pixelFormatDesc->cAccumGreenBits	=	0 ;
	pixelFormatDesc->cAccumBlueBits		=	0 ;
	pixelFormatDesc->cAccumAlphaBits	=	0; 
	pixelFormatDesc->cDepthBits				=	0; 
	pixelFormatDesc->cStencilBits			=	0	; 
	pixelFormatDesc->cAuxBuffers			=	0	; 
	pixelFormatDesc->iLayerType				=	PFD_MAIN_PLANE ; 
	pixelFormatDesc->bReserved				=	0	; 
	pixelFormatDesc->dwLayerMask			=	0	; 
	pixelFormatDesc->dwVisibleMask		=	0; 
	pixelFormatDesc->dwDamageMask		=	0	; 
	
	pfmIndex	=	 ChoosePixelFormat( hdc , pixelFormatDesc ) ;
	if ( pfmIndex != 0 )	
	{
		SetPixelFormat(hdc, pfmIndex, pixelFormatDesc); 		
		return	pfmIndex ;
	}
	else
	{
		//hardware mode could not be set, let's try a software rendering	
//		KMiscTools::messageBox( "Could not initialize openGL" , "Please install your video drivers" ) ;
		return NULL ;
	}

	return	pfmIndex ;
	
}

void			KWindowGL::showWindow( bool show ) 
{

	if ( show == true )
	{
		ShowWindow( _hwnd , SW_SHOW ) ;
	}
	else
	{
		ShowWindow( _hwnd , SW_HIDE) ;	

	}
}

bool		KWindowGL::isWindowVisible( void )  
{
	return IsWindowVisible( _hwnd )  ;
}


void			KWindowGL::setClipping( long x1, long y1, long x2 , long y2 )
{
long		 w, h ;
	
	w = x2-x1 ;
	h = y2-y1 ;
	
	y1 = _windowHeight-y1 ;
	y2 = _windowHeight-y2 ;
	
	glScissor(  x1 , y2  , w,  h) ;
	glEnable( GL_SCISSOR_TEST ) ;

 
}
void			KWindowGL::enumerateDisplays( ptkEnumDisplayCallBack  functionPtr )
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
bool			KWindowGL::SwitchToResolution( short	width , short	height , short depth ) 
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
void		KWindowGL::RestoreResolution( void ) 
{
	//on ne restitue que si ca avait switché
//	if ( dv.dmPelsHeight == 0 )	return ;
	
	ChangeDisplaySettings( &dv ,   CDS_FULLSCREEN ) ;
//Passing NULL for the lpDevMode parameter and 0 for the dwFlags parameter is the 
//easiest way to return to the default mode after a dynamic mode change. 
//	ChangeDisplaySettings( 0,0) ;
}


//destroys the window
void		KWindowGL::terminate( void ) 
{
	_quit = true ;
	PostQuitMessage( 0 ) ;
}




//process the events
void		KWindowGL::processEvents( void )
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

void			KWindowGL::minimize( void )
{
	ShowWindow( _hwnd , SW_MINIMIZE ) ;
}

void			KWindowGL::restore( void )
{
	ShowWindow( _hwnd , SW_SHOWNORMAL ) ;
}




LRESULT CALLBACK	KWindowGL::GameWindowProc( HWND hWnd, UINT messg,	WPARAM wParam, LPARAM lParam ) 
{
KEvent	kEvent ;

KWindowGL		*kwGL = NULL ;

	kwGL =(KWindowGL*)GetWindowLong( hWnd , GWL_USERDATA ) ;

	if ( kwGL != NULL )
	{
		if ( kwGL->_userCallback != NULL )
		{
			if ( kwGL->_userCallback( hWnd , messg , wParam , lParam ) == false )	return 0 ;
		}
		
		//native PTK event system ( multiplatform )
		if ( kwGL->_ptkCallback != NULL )
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
			case	WM_ACTIVATE:
					if( wParam == WA_INACTIVE )
					{
						kEvent.type 	= K_EVENT_DEACTIVATED ;
					}
					else
					{ 
						kEvent.type 	= K_EVENT_ACTIVATED ;
					}
				break ;
				//a window from another app is brought in front
				case	WM_ACTIVATEAPP:
					if( (bool)wParam != true )
					{
						kEvent.type 	= K_EVENT_DEACTIVATED ;
					}
					else
					{ 
						kEvent.type 	= K_EVENT_ACTIVATED ;
					}
				break ;

		}
		

		if ( kwGL->_ptkCallback( &kEvent ) == false )	return 0 ;
	}
	
	}
		
	switch(messg)
	{	
	/*	case WM_SYSCOMMAND:	// Intercept System Commands
			switch (wParam)	// Check System Calls
			{
				// Screensaver Trying To Start?
				case SC_SCREENSAVE:	
					if ( kwGL != NULL )
					{
						kwGL->minimize( ) ;
					}
				break ;
				
				// Monitor Trying To Enter Powersave?
				case SC_MONITORPOWER:
				return 0;	// Prevent From Happening
			}
		break;			// Exit
	*/
	
		case	WM_PAINT:
			if ( kwGL != NULL)	
			{
				if (kwGL->hasFocus(  ) == false )
				{
					PAINTSTRUCT	ps ;
					HDC	hdc = BeginPaint( hWnd , &ps ) ;
						kwGL->flipBackBuffer( false ) ;
					EndPaint( hWnd , &ps ) ;	
				}
			}
		break ;
		
	/*
		case	WM_SYSKEYDOWN:
				if ( wParam  == VK_MENU )	return 0;
				return( DefWindowProc( hWnd, messg, wParam, lParam ) );
				
		case WM_SYSKEYUP:
				if ( wParam  == VK_MENU )	return 0;
				return( DefWindowProc( hWnd, messg, wParam, lParam ) );
*/
		case	WM_ACTIVATEAPP:
			if ( kwGL == NULL )		break ;

			if ( kwGL->_silent == false )
			{
				if ( wParam == false )
				{
						if ( kwGL->_fullscreen == true && IsWindow( kwGL->_hwnd )  )
						{
							if ( kwGL )	kwGL->RestoreResolution( ) ;
							ShowWindow( kwGL->_hwnd , SW_MINIMIZE ) ;
						}
				}
				else
				{
						if ( kwGL->_fullscreen == true && IsWindow( kwGL->_hwnd ) )
						{
							if ( kwGL )	kwGL->SwitchToResolution( kwGL->_windowWidth ,kwGL-> _windowHeight , kwGL->_windowDepth) ;
						}
				
				}
			}
						
		break ;
		case	WM_MOUSEWHEEL:
			KInput::setLastWheelValue(  HIWORD(wParam) );
		break;
		case	WM_CLOSE:
			
			if (kwGL ) 	{kwGL->_quit = true ; }
			
		break;
		case WM_DESTROY:
				if (kwGL ) 	{kwGL->_quit = true ; }
		//PostQuitMessage( 0 );
		break;
	
		default:
			return( DefWindowProc( hWnd, messg, wParam, lParam ) );
	}
	
	return	0 ;
	
}



bool		KWindowGL::getFullScreenState( void )  
{
	return _fullscreen ;
}


// ----------------------------------------------------------

//bool KWindowGL::SetRenderTarget(KGraphic* graphic) 
//{
//	if (m_rttGL != NULL)
//	{
//		flipBackBuffer();
//	}
//	m_rttGL = (KGraphicGL*)graphic;	
//}
