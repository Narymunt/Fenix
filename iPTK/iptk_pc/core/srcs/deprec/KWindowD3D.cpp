#include	"KWindowD3D.h"
#include	"KMiscTools.h"
#include	"matrices.h"
#include	"KGraphicD3D.h"
#include "K3Dd3d.h"
#include	"ximage.h"
#include	"trial.h"
#include	"d3dxcore.h"
#include	"KBatchD3D.h"

#ifndef	WM_MOUSEWHEEL
#define	WM_MOUSEWHEEL                   0x020A
#endif


unsigned	long 	_internalScrFix ;
unsigned	long 	_internalScrFix2 ;

struct		swaterMarkx
{
	float	x,y ;
};

bool		KWindowD3D::isWindowActive = false ;


static bool g_bGotZFormat = false;

KWindowD3D::KWindowD3D( )
{

		

	_quit = false ;
	memset( &dv , 0 ,  sizeof(DEVMODE) )  ;
	
	_lpDD				= NULL;
	_lpD3D				= NULL;
	_lpD3DDevice	= NULL;
	_lpDDSPrimary	= NULL;
	_lpDDSBack		= NULL;
	_lpDDSZBuffer	= NULL;
	_fullscreen 		= false ;
	_clearColor		= 0 ;
	_hWndPTK			=	0 ;
	_ptkCallback = NULL ;
	_userCallback = NULL ;
	_maxFrameRate  = 0 ;
	_gamma	= 1 ;
   _use3d = false ;
   _displayPTKMouse = false ;
   _hwndParent = 0 ;
   	_visibleState = true ;

//   D3DXInitialize ( ) ;
}

KWindowD3D::KWindowD3D(bool use3d)
{

	
	   _hwndParent = 0 ;
	_quit = false ;
	memset( &dv , 0 ,  sizeof(DEVMODE) )  ;
	
	_lpDD				= NULL;
	_lpD3D				= NULL;
	_lpD3DDevice	= NULL;
	_lpDDSPrimary	= NULL;
	_lpDDSBack		= NULL;
	_lpDDSZBuffer	= NULL;
	_fullscreen 		= false ;
	_clearColor		= 0 ;
	_hWndPTK			=	0 ;
	_ptkCallback = NULL ;
	_userCallback = NULL ;
	_maxFrameRate  = 0 ;
	_gamma	= 1 ;
   _use3d = use3d ;
   _displayPTKMouse = false ;	
   _visibleState = true ;


 //     D3DXInitialize ( ) ;
}

KWindowD3D::~KWindowD3D( )
{
//   D3DXUninitialize() ;
	
	_displayPTKMouse = false ;
//	_quit = false ;
	releaseDirectContexts( ) ;
	
	_lpDD				= NULL;
	_lpD3D				= NULL;
	_lpD3DDevice	= NULL;
	_lpDDSPrimary	= NULL;
	_lpDDSBack		= NULL;
	_lpDDSZBuffer	= NULL;
	_fullscreen 		= false ;
	_clearColor		= 0 ;
	_ptkCallback = NULL ;
	_userCallback = NULL ;
	_maxFrameRate  = 0 ;
	_gamma	= 1 ;	
	
	if ( IsWindow( _hWndPTK )  )
	{
		DestroyWindow( _hWndPTK ) ;
	}

	_hWndPTK = 0 ;
	
}

void           KWindowD3D::displayMouse( bool mousestate )
{
               _displayPTKMouse = mousestate ;

}

//set clear color 
void			KWindowD3D::setClearColor(float r , float g , float b  , float alp ) 
{
	 _clearColor = D3DRGBA( r,g, b , alp );
}


//really creates the window
bool		KWindowD3D::createGameWindow( short  width , short height , short depth , bool windowed , const char *windowTitle  )  
{
	_internalFocus = true ;
	_monitorOn = true ;
	
HKEY   phKey ;
	strcpy( _screenSaverPath , "" ) ;
	
	if ( ERROR_SUCCESS ==  RegOpenKeyEx( HKEY_CURRENT_USER , "Control Panel\\Desktop" , 0 , KEY_READ , &phKey ) )
	{
		const char	keyname[512] = { "SCRNSAVE.EXE" } ;
		
		unsigned long scrBufferLen = 512 ;
//		RegQueryValueEx( phKey , "SCRNSAVE.EXE" ,NULL ,  NULL , scrBuffer , &scrBufferLen ) ;
		RegQueryValueEx( phKey , keyname ,NULL ,  NULL , (unsigned char*)_screenSaverPath , &scrBufferLen ) ;
		RegCloseKey( phKey ) ;
	
	}


	_internalScrFix = GetTickCount( ) ;
	_internalScrFix2 = _internalScrFix ;
	

	 SystemParametersInfo( 	SPI_GETPOWEROFFTIMEOUT , 0,&_screenTimeOut,0 ) ;
	 SystemParametersInfo( 	SPI_GETPOWEROFFACTIVE , 0,&_screenTimeOutActive,0 ) ;

	_screenTimeOut -=5 ;
	if ( _screenTimeOut < 0 ) _screenTimeOut = 1 ;

	 SystemParametersInfo( 	SPI_GETSCREENSAVEACTIVE , 0,&_scrActive,0 ) ;
	 SystemParametersInfo( 	SPI_GETSCREENSAVETIMEOUT , 0,&_startSCR,0 ) ;
	_scrTimer = 0 ;
	

	_windowWidth		=	width ;
	_windowHeight	=	height ;
	_windowDepth	=	depth ;
	_fullscreen			=	true ;
	if ( windowed == true )		{	_fullscreen = false ; }	
	
	
	return 	createRealWindow( width , height , depth ,  windowTitle ) ;
}


//create the d3d objects etc...
bool		KWindowD3D::attachD3DToWindow( void )
{
	if ( _fullscreen == false )
	{
		if ( 	createDirectContextsWindow( ) == false )	
		{	
//			MessageBox( 0 ,"can't create directX context, please reinstall direct X" ,0,0 ) ;
			return false ;
		}
	}
	else
	{
		// If fullscreen we change the display mode
		if ( 	createDirectContextsFullScreen( ) == false )	
		{	
//			MessageBox( 0 ,"can't create directX context for fullscreen, please reinstall direct X" ,0,0 ) ;
			return false ;
		}
	}

	regenerateD3DDevice( ) ;

	D3DVIEWPORT7 vp = { 0, 0, _windowWidth, _windowHeight, 0.0f, 1.0f };

	if( FAILED( _lpD3DDevice->SetViewport( &vp )) )		return false;
		
	KGraphicD3D::setDirectX(_lpDD , _lpD3DDevice , _lpDDSBack , _windowWidth , _windowHeight , _windowDepth ) ;

	K3Dd3d::initK3Dd3d( _windowWidth,_windowHeight, _lpD3DDevice ) ;

	KBatchD3D::setDirectX(_lpD3D , _lpD3DDevice  ) ;

	return true ;
	
}


//code provided by www.pokiemagic.com
void		KWindowD3D::setClipping( long x1, long y1, long x2 , long y2 ) 
{
 D3DRECT clipRect;
 clipRect.x1 = x1;
 clipRect.y1 = y1;
 clipRect.x2 = x2;
 clipRect.y2 = y2;
 
	if ( _lpD3DDevice == NULL )		return ;
	_lpD3DDevice->Clear(1, NULL, D3DCLEAR_ZBUFFER, 0, 0.0f, 0); 

	_lpD3DDevice->Clear(1, &clipRect, D3DCLEAR_ZBUFFER, 0, 1.0f, 0); //with the current fix this throws an exception
 
	_lpD3DDevice->SetRenderState( D3DRENDERSTATE_ZENABLE, TRUE); //with the current fix this throws an exception
	_lpD3DDevice->SetRenderState( D3DRENDERSTATE_ZWRITEENABLE, FALSE); //with the current fix this throws an exception
	_lpD3DDevice->SetRenderState( D3DRENDERSTATE_ZFUNC, D3DCMP_LESS); //with the current fix this throws an exception

}

void			KWindowD3D::enumerateDisplays( ptkEnumDisplayCallBack  functionPtr )
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


//regnerate device
bool		KWindowD3D::regenerateD3DDevice( void )
{


	if ( _lpD3DDevice != NULL )		
	{
		_lpD3DDevice->EndScene( ) ;
		_lpD3DDevice->Release( ) ;
		_lpD3DDevice = NULL ;
	}

	// Try to set TnL device
	if( FAILED( _lpD3D->CreateDevice(IID_IDirect3DTnLHalDevice, _lpDDSBack, &_lpD3DDevice)))
	{

		// If failed, try the HAL device
		if( FAILED( _lpD3D->CreateDevice(IID_IDirect3DHALDevice, _lpDDSBack, &_lpD3DDevice)))
		{
	
			// So, if no 3D card is detected, set the RGB device
			if( FAILED( _lpD3D->CreateDevice(IID_IDirect3DRGBDevice, _lpDDSBack, &_lpD3DDevice)))
			{
				return false;
			}
		}
	}

	
	D3DVIEWPORT7 vp = { 0, 0, _windowWidth, _windowHeight, 0.0f, 1.0f };

	if( FAILED( _lpD3DDevice->SetViewport( &vp )) )		return false;
		
	KGraphicD3D::setDirectX(_lpDD , _lpD3DDevice , _lpDDSBack , _windowWidth , _windowHeight , _windowDepth ) ;
	KBatchD3D::setDirectX(_lpD3D , _lpD3DDevice  ) ;

	if ( _lpDD->TestCooperativeLevel () != DD_OK )		return  true;

	_lpD3DDevice->BeginScene( ) ;

	return true ;
}

static HRESULT WINAPI EnumZBufferFormatsCallback( DDPIXELFORMAT* pddpf,
                                                  VOID* pddpfDesired ) {
	if( NULL==pddpf || NULL==pddpfDesired )
        return D3DENUMRET_CANCEL;

    if( pddpf->dwFlags == ((DDPIXELFORMAT*)pddpfDesired)->dwFlags ) {
        memcpy( pddpfDesired, pddpf, sizeof(DDPIXELFORMAT) );
		
		g_bGotZFormat=TRUE;
        return D3DENUMRET_CANCEL;
    }

    return D3DENUMRET_OK;
}

bool KWindowD3D::createZBuffer (void) {
   DDSURFACEDESC2 ddsd;

   bool bSoftZBuffer = false;
	DDPIXELFORMAT ddpfZBuffer;

   g_bGotZFormat = false;

	ZeroMemory(&ddpfZBuffer,sizeof(ddpfZBuffer));
	ddpfZBuffer.dwSize=sizeof(ddpfZBuffer);
	ddpfZBuffer.dwFlags = DDPF_ZBUFFER ;
	_lpD3D->EnumZBufferFormats( IID_IDirect3DTnLHalDevice, 
							   EnumZBufferFormatsCallback,
							   (VOID*)&ddpfZBuffer);
   if (g_bGotZFormat) {
		bSoftZBuffer = false;
	}
   else {
		_lpD3D->EnumZBufferFormats( IID_IDirect3DHALDevice, EnumZBufferFormatsCallback,
		                            (VOID*)&ddpfZBuffer );
		if (g_bGotZFormat) {
			bSoftZBuffer = false;
		}
      else {
			_lpD3D->EnumZBufferFormats( IID_IDirect3DMMXDevice, EnumZBufferFormatsCallback,
			                            (VOID*)&ddpfZBuffer );
			if (g_bGotZFormat) {
				bSoftZBuffer = true;
			}
         else {
				_lpD3D->EnumZBufferFormats( IID_IDirect3DRGBDevice, EnumZBufferFormatsCallback,
				                            (VOID*)&ddpfZBuffer );
				if (g_bGotZFormat) 
					bSoftZBuffer = true;
			}
		}
	}


   // Create the Z buffer
	memset( &ddsd, 0,sizeof(DDSURFACEDESC2) );
	ddsd.dwSize = sizeof(DDSURFACEDESC2);

   ddsd.dwFlags = DDSD_CAPS|DDSD_WIDTH|DDSD_HEIGHT|DDSD_PIXELFORMAT;
   if (!bSoftZBuffer)
      ddsd.ddsCaps.dwCaps = DDSCAPS_ZBUFFER|DDSCAPS_VIDEOMEMORY;
   else
      ddsd.ddsCaps.dwCaps = DDSCAPS_ZBUFFER|DDSCAPS_SYSTEMMEMORY;
	ddsd.dwWidth  	= _windowWidth;
	ddsd.dwHeight 	= _windowHeight ;
	ddsd.ddpfPixelFormat.dwSize = sizeof(DDPIXELFORMAT);
	ddsd.ddpfPixelFormat.dwFlags = DDPF_ZBUFFER;
   ddsd.ddpfPixelFormat.dwRGBBitCount = 16;
   memcpy(&ddsd.ddpfPixelFormat,&ddpfZBuffer,sizeof(DDPIXELFORMAT));

	if( FAILED (_lpDD->CreateSurface( &ddsd, &_lpDDSZBuffer, NULL )) )		
	{
//		MessageBox( 0 , "can't create Z buffer",0,0 ) ;
		return false;
	}

   // Attach to back buffer
   if ( _lpDDSBack->AddAttachedSurface(_lpDDSZBuffer) != DD_OK ) {
//		MessageBox( 0 , "can't attach Z buffer" ,0,0 ) ;
      return false;
   }

   // Done
   return true;
}

//create direct contexts for windowed mode
bool		KWindowD3D::createDirectContextsWindow( void )
{

		
	if ( _lpDD == NULL )
	{
		// Create the DirectDraw Object
		if( FAILED( DirectDrawCreateEx( NULL, (VOID**)&_lpDD, IID_IDirectDraw7, NULL ) ) )		return false;
		// Create the Direct3D Object
		if( FAILED( _lpDD->QueryInterface( IID_IDirect3D7, (VOID**)&_lpD3D )) )		return false;
	}
		
	
	//release only in case of switch from one mode to another ( fullscreen<->windowed)
	if ( _lpDDSPrimary != NULL )	
	{
		_lpDDSPrimary->Release( ) ;
		_lpDDSPrimary = NULL ;
		_lpDDSBack = NULL ;			//the back is released with the primary if coming from a double buffer fullscreen
	}
	

	// Set the cooperative level
	if( FAILED ( _lpDD->SetCooperativeLevel( _hWndPTK, DDSCL_NORMAL ) ))	
	{
//		MessageBox( 0 , "could not change cooperative level" ,0,0 ) ;
		return false ;
	}

	while (_lpDD->TestCooperativeLevel () != DD_OK) 
	{
		 Sleep (100);
		 processEvents ();
		if ( _quit == true )		return false  ;
	};


	DDSURFACEDESC2 ddsd;
	memset( &ddsd, 0,sizeof(DDSURFACEDESC2) );
	ddsd.dwSize = sizeof(DDSURFACEDESC2);
	
	ddsd.dwFlags		   			= DDSD_CAPS ;
	ddsd.ddsCaps.dwCaps    = DDSCAPS_PRIMARYSURFACE | DDSCAPS_VIDEOMEMORY   ;
//		 DDSCAPS_PRIMARYSURFACE Or DDSCAPS_VIDEOMEMORY Or DDSCAPS_FLIP Or DDSCAPS_COMPLEX

	
	// Create the primary surface
	if( FAILED (_lpDD->CreateSurface( &ddsd, &_lpDDSPrimary, NULL )) )	
	{
//		MessageBox( 0 ,"can't create primary surface for window mode" ,0,0 ) ;
		return false;
	}
	
	memset( &ddsd, 0,sizeof(DDSURFACEDESC2) );
	ddsd.dwSize = sizeof(DDSURFACEDESC2);
	
	// Create the backbuffer surface
	ddsd.dwFlags					= DDSD_WIDTH | DDSD_HEIGHT | DDSD_CAPS;
	ddsd.ddsCaps.dwCaps 	= DDSCAPS_OFFSCREENPLAIN | DDSCAPS_3DDEVICE | DDSCAPS_VIDEOMEMORY ;

	ddsd.dwWidth  	= _windowWidth;
	ddsd.dwHeight 	= _windowHeight ;
		
	if( FAILED (_lpDD->CreateSurface( &ddsd, &_lpDDSBack, NULL )) )		
	{
//		MessageBox( 0 , "can't create backbuffer",0,0 ) ;
			return false;
	}

   if ( _use3d) 
   {
      if ( createZBuffer () == false )        return false;
   }

/*	if ( _lpDDSPrimary->AddAttachedSurface( _lpDDSBack )  != DD_OK )
	{
		MessageBox( 0 , "can't attach back buffer" ,0,0 ) ;
	}
*/
	LPDIRECTDRAWCLIPPER lpDDCClipper;

	if( FAILED (_lpDD->CreateClipper( 0, &lpDDCClipper, NULL )) )			return false;
		
	lpDDCClipper->SetHWnd( 0, _hWndPTK );
	_lpDDSPrimary->SetClipper( lpDDCClipper );		
	lpDDCClipper->Release();


	ClearSurface( _lpDDSPrimary ) ;
	ClearSurface( _lpDDSBack ) ;


	return true ;
}

//clear a surface to black
void 	KWindowD3D::ClearSurface(LPDIRECTDRAWSURFACE7  surfacePTR)
{
	if(surfacePTR == NULL)        return;

	DDBLTFX	ddblt;
							
	memset( &ddblt , 0 , sizeof (  DDBLTFX ) ) ;
	ddblt.dwSize = sizeof ( DDBLTFX ) ;
	ddblt.dwFillColor  = 0 ;
	surfacePTR->Blt( NULL , NULL , NULL , DDBLT_WAIT | DDBLT_COLORFILL  , &ddblt ) ;
}

//fullscreen
bool		KWindowD3D::createDirectContextsFullScreen( void )
{
char	buffer[1024] ;

	// Create the DirectDraw Object
	if ( _lpDD == NULL )
	{
		if( FAILED( DirectDrawCreateEx( NULL, (VOID**)&_lpDD, IID_IDirectDraw7, NULL ) ) )		return false;
		// Create the Direct3D Object
		if( FAILED( _lpDD->QueryInterface( IID_IDirect3D7, (VOID**)&_lpD3D )) )		return false;
	}



	//release only in case of switch from one mode to another ( fullscreen<->windowed)
	if ( _lpDDSPrimary != NULL )	
	{
		_lpDDSPrimary->Release( ) ;
		_lpDDSPrimary = NULL ;
	}
	if ( _lpDDSBack != NULL )		
	{
		_lpDDSBack->Release( ) ;
		_lpDDSBack = NULL ;
	}
	
		// Set the cooperative level
	if( FAILED ( _lpDD->SetCooperativeLevel( _hWndPTK, DDSCL_EXCLUSIVE |DDSCL_FULLSCREEN   ) ))		
	{
		//MessageBox( 0 , "could not change cooperative level" ,0,0 ) ;
		return false ;
	}

	//-1 is not possible in fullscreen, just default to 16
	if ( _windowDepth <= 0 )	{	_windowDepth = 16 ;	}



	if( FAILED (_lpDD->SetDisplayMode(_windowWidth, _windowHeight, _windowDepth, 0, 0)) )			
	{
	sprintf( buffer , "Could not switch screen to %dx%d %d bits" , _windowWidth, _windowHeight, _windowDepth ) ;
		return false;
	}
	
	while (_lpDD->TestCooperativeLevel () != DD_OK) 
	{
		 Sleep (100);
		 processEvents ();
		if ( _quit == true )		return false  ;
	};


	//creates the surfaces
	DDSURFACEDESC2 ddsd;
	memset( &ddsd, 0,sizeof(DDSURFACEDESC2) );
	ddsd.dwSize = sizeof(DDSURFACEDESC2);
	
	ddsd.dwFlags		   			= DDSD_CAPS | DDSD_BACKBUFFERCOUNT;
	ddsd.ddsCaps.dwCaps    = DDSCAPS_PRIMARYSURFACE | 
											DDSCAPS_FLIP |  
											DDSCAPS_COMPLEX | DDSCAPS_3DDEVICE | DDSCAPS_VIDEOMEMORY ;
											
	ddsd.dwBackBufferCount = 1;

	// Create the primary surface
	if( FAILED (_lpDD->CreateSurface( &ddsd, &_lpDDSPrimary, NULL )) )		return false;
	
	DDSCAPS2 ddscaps = { DDSCAPS_BACKBUFFER, 0, 0, 0 };

	ZeroMemory(&ddscaps, sizeof(DDSCAPS2));
	 ddscaps.dwCaps = DDSCAPS_BACKBUFFER;
	  
	if( FAILED (_lpDDSPrimary->GetAttachedSurface( &ddscaps, &_lpDDSBack )) )			return false;


   if ( _use3d) 
   {
//      if ( createZBuffer () == false )        return false;
   }

					
	_lpDDSPrimary->SetClipper( NULL );
	_lpDDSBack->SetClipper( NULL );
	

	ClearSurface( _lpDDSPrimary ) ;
	ClearSurface( _lpDDSBack ) ;
	
	return true ;
}

//release direct contexts
bool		KWindowD3D::releaseDirectContexts( void )
{	
	if ( _lpD3DDevice != NULL )	_lpD3DDevice->Release( ) ;
	if ( _lpD3D	!= NULL )				_lpD3D->Release( );

	if ( _lpDDSZBuffer !=	NULL )	
	{
		_lpDDSZBuffer->Release( ) ;
		_lpDDSZBuffer = NULL ;
	}

	if ( _fullscreen == false )
	{
		if ( _lpDDSBack !=	NULL )	
		{
			_lpDDSBack->Release( ) ;
			_lpDDSBack = NULL ;
		}
	}
	
	if ( _lpDDSPrimary !=	NULL )	
	{
		_lpDDSPrimary->Release( ) ;
		_lpDDSPrimary = NULL ;
	}


	
/*	if ( _lpDD != NULL  && _fullscreen==true)
	{	
		_lpDD->RestoreDisplayMode();
	}
	*/
	
	if ( _lpDD 	!= NULL )				_lpDD->Release( );

	_lpD3DDevice	=	NULL ;
	_lpDDSPrimary	=	NULL ;
	_lpDDSBack		=	NULL ;
	_lpD3D 	= NULL ;
	_lpDD 	= NULL ;

	return true ;
}


//create a window for windowed mode
bool	 	KWindowD3D::createRealWindow( short	width , short	height , short	depth ,  const char	*windowTitle ) 
{
WNDCLASS			wndClass ;
RECT					r ;
int							screenWidth , screenHeight ;
unsigned long			windowStyle = WS_CAPTION | WS_SYSMENU | WS_VISIBLE | WS_MINIMIZEBOX ;

		if ( 	_visibleState == true )
		{
			windowStyle = WS_CAPTION | WS_SYSMENU | WS_VISIBLE | WS_MINIMIZEBOX ;
		}
		else
		{
			windowStyle = WS_CAPTION | WS_SYSMENU  | WS_MINIMIZEBOX ;		
		}

		if ( depth != -1 )
		{
			SwitchToResolution( -1,-1,depth ) ;
		}
	strcpy ( _windowTitle , windowTitle ) ;

	screenWidth 	= GetSystemMetrics( SM_CXSCREEN ) ;
	screenHeight = GetSystemMetrics( SM_CYSCREEN ) ;

	memset( &wndClass , 0 , sizeof( WNDCLASS ) ) ;
 

	wndClass.lpszClassName 	= GAMECLASSNAME;
	wndClass.hInstance 			= GetModuleHandle( NULL );
	wndClass.lpfnWndProc		= GameWindowProc;
	wndClass.hCursor				= NULL ; // LoadCursor( NULL , IDC_ARROW )  ;
	SetCursor( LoadCursor( NULL , IDC_ARROW )   ) ;
	wndClass.hIcon					= LoadIcon( GetModuleHandle( NULL ) , MAKEINTRESOURCE(160) );
	wndClass.lpszMenuName	= NULL;
	wndClass.style					=  CS_DBLCLKS;
	wndClass.cbClsExtra			= 0;
	wndClass.cbWndExtra			= 0;
	wndClass.hbrBackground	= (HBRUSH)GetStockObject( BLACK_BRUSH );

	if ( _fullscreen == true  )	
	{
		if ( _visibleState == true )
		{
			windowStyle = WS_POPUP |	WS_VISIBLE ;
		}
		else
		{
			windowStyle = WS_POPUP ;
		}
	}
	
	
	if ( _hwndParent != 0  )		windowStyle = WS_CHILD | WS_POPUP |	WS_VISIBLE ;

	RegisterClass( &wndClass ) ;

	//we need a width*height window
	SetRect( &r , 0 , 0 , width , height ) ;

	//calculate the client rect
	AdjustWindowRect( &r , windowStyle  , false ) ;
//	SetRect( &r , 0 , 0 , 320,240 ) ;

	if ( _hwndParent == 0  )
	{
	_hWndPTK		=	CreateWindowEx( 	0,	GAMECLASSNAME ,
														windowTitle,
														windowStyle ,
														(screenWidth-(r.right-r.left))/2 ,			//centers the window
														(screenHeight-(r.bottom-r.top))/2,
														(r.right-r.left)	,	
														(r.bottom-r.top)  ,
														_hwndParent ,
														0 ,
														GetModuleHandle( NULL ) ,
														0 ) ;
		}
		else
		{
			GetClientRect( _hwndParent , &r ) ;
			_hWndPTK		=	CreateWindow( 		"PTK windowTitle"  ,
															windowTitle,
															windowStyle ,
															0 ,			
															0,
															width,	
															height  ,
															_hwndParent ,
															0 ,
															GetModuleHandle( NULL ) ,
															0 ) ;
		}
		
		
		if ( _hWndPTK == 0 )		
		{
			return false ;
		}
		
		SetWindowLong( _hWndPTK , GWL_USERDATA , (long)this );
		ShowWindow( _hWndPTK, SW_SHOW );
		UpdateWindow( _hWndPTK );

	
		KInput::initInput( _hWndPTK ) ;
	
		bool	result = attachD3DToWindow(   ) ;
		
		return true ;
}

bool	 	KWindowD3D::createGameWindowSpecial( short	width , short	height , short	depth ,  const char	*windowTitle ) 
{
WNDCLASS			wndClass ;
RECT					r ;
int							screenWidth , screenHeight ;
unsigned long			windowStyle = WS_CAPTION | WS_SYSMENU | WS_VISIBLE | WS_MINIMIZEBOX ;

		if ( depth != -1 )
		{
			SwitchToResolution( -1,-1,depth ) ;
		}

	screenWidth 	= GetSystemMetrics( SM_CXSCREEN ) ;
	screenHeight = GetSystemMetrics( SM_CYSCREEN ) ;

	memset( &wndClass , 0 , sizeof( WNDCLASS ) ) ;

	wndClass.lpszClassName 	= GAMECLASSNAME;
	wndClass.hInstance 			= GetModuleHandle( NULL ) ;
	wndClass.lpfnWndProc		= GameWindowProc;
	wndClass.hCursor				= NULL ; // LoadCursor( NULL , IDC_ARROW )  ;
	SetCursor( LoadCursor( NULL , IDC_ARROW )   ) ;
	wndClass.hIcon					= LoadIcon( GetModuleHandle( NULL ) , MAKEINTRESOURCE(160) );
	wndClass.lpszMenuName	= NULL;
	wndClass.style					= CS_DBLCLKS;
	wndClass.cbClsExtra			= 0;
	wndClass.cbWndExtra			= 0;
	wndClass.hbrBackground	= (HBRUSH)GetStockObject( BLACK_BRUSH );

	if ( _fullscreen == true  )		windowStyle = WS_POPUP |	WS_VISIBLE ;
	if ( _hwndParent != 0  )		windowStyle = WS_CHILD | WS_POPUP |	WS_VISIBLE ;

	RegisterClass( &wndClass ) ;

	//we need a width*height window
	SetRect( &r , 0 , 0 , width , height ) ;


	//calculate the client rect
	AdjustWindowRect( &r , windowStyle  , false ) ;

	if ( _hwndParent == 0  )
	{
	_hWndPTK		=	CreateWindowEx( 	0,	GAMECLASSNAME ,
														windowTitle,
														windowStyle ,
														(screenWidth-(r.right-r.left))/2 ,			//centers the window
														(screenHeight-(r.bottom-r.top))/2,
														(r.right-r.left)	,	
														(r.bottom-r.top)  ,
														_hwndParent ,
														0 ,
														GetModuleHandle( NULL ) ,
														0 ) ;
		}
		else
		{
			GetClientRect( _hwndParent , &r ) ;
			_hWndPTK		=	CreateWindow( 		"PTK windowTitle"  ,
															windowTitle,
															windowStyle ,
															0 ,			
															0,
															width,	
															height  ,
															_hwndParent ,
															0 ,
															GetModuleHandle( NULL ) ,
															0 ) ;
		}
		
		
		if ( _hWndPTK == 0 )		
		{
			return false ;
		}
		
		SetWindowLong( _hWndPTK , GWL_USERDATA , (long)this );
		ShowWindow( _hWndPTK, SW_SHOW );
		UpdateWindow( _hWndPTK );

		KInput::initInput( _hWndPTK ) ;
	
		bool	result = attachD3DToWindow(   ) ;
		
		return result ;
}



//sets a parent for activeX power
void	 	KWindowD3D::setParentWindow( HWND	hwndParent ) 
{
	_hwndParent = hwndParent ;
}


//terminates the app
void		KWindowD3D::terminate( void )  
{
	_quit = true ;
}
long		KWindowD3D::getWindowWidth( void ) 
{
	return _windowWidth ;
}

long		KWindowD3D::getWindowHeight( void ) 
{
	return _windowHeight ;

}

bool		KWindowD3D::toggleFullScreen( bool 	fullscreen ) 
{
	testCooperative( ) ;
	

	ptkWindowCallBack	_userCallbackBuffer ;
	ptkNativeCallBack		_ptkCallbackBuffer  ;

	_userCallbackBuffer = _userCallback ;
	_ptkCallbackBuffer = _ptkCallback ;



	//are we already in fullscreen ?
	if ( _fullscreen == true && fullscreen == true	)		return _fullscreen ;
	//are we already in windowed ?
	if ( _fullscreen == false && fullscreen == false	)		return _fullscreen ;
	
	releaseDirectContexts( ) ;
	
	_lpDD				= NULL;
	_lpD3D				= NULL;
	_lpD3DDevice	= NULL;
	_lpDDSPrimary	= NULL;
	_lpDDSBack		= NULL;
	_lpDDSZBuffer	= NULL;
	_gamma	= 1 ;	
	
	if ( IsWindow( _hWndPTK )  )
	{
		DestroyWindow( _hWndPTK ) ;
	}

	_hWndPTK = 0 ;
	_fullscreen = fullscreen ;
	memset( &dv , 0 ,  sizeof(DEVMODE) )  ;
	createGameWindowSpecial( _windowWidth , _windowHeight , _windowDepth  , (const char*)_windowTitle );
	testCooperative( ) ;

	if ( _lpDD->TestCooperativeLevel() == DD_OK)	
	{
		KGraphicD3D::forceReloadList( ) ;
	}
	_quit = false ;
	
	_userCallback = _userCallbackBuffer ;
	_ptkCallback = _ptkCallbackBuffer  ;

	return true ;
	
	/*
//	KGraphicD3D::deleteList( ) ;

	_fullscreen = fullscreen ;

	//switch to windowed
	if ( fullscreen == false && IsWindow( _hWndPTK )  && _lpDD != NULL)
	{
			_lpDD->RestoreDisplayMode( ) ;

			long  i ;
			for ( i = 0 ; i  < 1000 ; i++ )
			{
				processEvents() ;
			}
			
			//we need a width*height window
			SetRect( &r , 0 , 0 , _windowWidth , _windowHeight ) ;
			//calculate the client rect
			AdjustWindowRect( &r , WS_CAPTION | WS_SYSMENU | WS_VISIBLE | WS_MINIMIZEBOX  , false ) ;
			long	screenWidth 	= GetSystemMetrics( SM_CXSCREEN ) ;
			long	screenHeight = GetSystemMetrics( SM_CYSCREEN ) ;
		
			SetWindowLong( _hWndPTK ,GWL_STYLE , WS_CAPTION | WS_SYSMENU | WS_VISIBLE | WS_MINIMIZEBOX ) ;
			MoveWindow(  _hWndPTK , (screenWidth-(r.right-r.left))/2,(screenHeight-(r.bottom-r.top))/2, (r.right-r.left),(r.bottom-r.top)  ,true ) ;
			UpdateWindow( _hWndPTK  ) ;

			_fullscreen = false ;
			createDirectContextsWindow() ;
			regenerateD3DDevice( ) ;

			
			//KGraphicD3D::forceReloadList( ) ;
			return _fullscreen ;
	}


		//switch to fullscreen
		if ( fullscreen == true && IsWindow( _hWndPTK )  )
		{				
				SetWindowLong( _hWndPTK ,GWL_STYLE , WS_POPUP | WS_VISIBLE  ) ;
				MoveWindow(  _hWndPTK , 0,0,_windowWidth,_windowHeight,true ) ;
				UpdateWindow( _hWndPTK ) ;
				
				createDirectContextsFullScreen( ) ;
				_fullscreen = true ;
				regenerateD3DDevice( ) ;
				
				return _fullscreen ;
		}
		
		
		return	_fullscreen ;
		*/
}

bool		KWindowD3D::hasFocus()
{
	if ( IsIconic( _hWndPTK ) == true )		return false ;
	if ( GetForegroundWindow( ) == _hWndPTK ) return true ;
	
	return false ;

}

void		KWindowD3D::setTitle( const char * title ) 
{
	if ( _hWndPTK == 0 )		return ;
	
	SetWindowText( _hWndPTK , title ) ;
}


void		KWindowD3D::doGammaAdjustment( void )
{
float	realgamma ;
	if ( _lpD3DDevice == NULL )		return ;

	setDefaultWorldView( ) ;
	
	realgamma = 1-_gamma ;
	if ( realgamma < 0 )		realgamma = 0 ;

	_lpD3DDevice->SetRenderState(D3DRENDERSTATE_ALPHABLENDENABLE, TRUE);

	D3DCOLOR col = D3DRGBA( 0,0,0, realgamma);

	D3DLVERTEX v[6];
	v[0] = D3DLVERTEX(D3DVECTOR(0,0,0), col, 0, 0, 0);
	v[1] = D3DLVERTEX(D3DVECTOR(_windowWidth,0,0), col, 0, 0, 0);
	v[2] = D3DLVERTEX(D3DVECTOR(_windowWidth,-_windowHeight,0), col, 0, 0, 0);
	v[3] = D3DLVERTEX(D3DVECTOR(_windowWidth,-_windowHeight,0), col, 0, 0, 0);
	v[4] = D3DLVERTEX(D3DVECTOR(0,-_windowHeight,0), col, 0, 0, 0);
	v[5] = D3DLVERTEX(D3DVECTOR(0,0,0), col, 0, 0, 0);

	_lpD3DDevice->SetTexture(0, NULL);

//	_lpD3DDevice->BeginScene();
	_lpD3DDevice->DrawPrimitive(D3DPT_TRIANGLELIST, D3DFVF_LVERTEX, &v[0], 6, D3DDP_WAIT);
//	_lpD3DDevice->EndScene();

	KGraphicD3D::_oldBindedText = NULL  ;


}


void		KWindowD3D::flipBackBuffer(  bool	waitForBackWindow  , bool restoreView ) 
{
MSG		Msg ;
static	long	t1 = 0 ;
unsigned 	long		t2 , frameRenderTime ;
bool			iamready ;

	processEvents( ) ;

	testCooperative( ) ;
	
	if ( _lpD3DDevice == NULL )		return ;
	if ( _lpDDSPrimary == NULL )		return ;


	iamready = true ;


	if ( _lpDD != NULL )
	{
		if ( _lpDD->TestCooperativeLevel () != DD_OK )		
		{
			iamready = false ;
		}
	}


	if ( iamready == true )
	{
	   if ( _displayPTKMouse == true )
	   {
	           setDefaultWorldView( ) ;
	           KInput::displayMouse( ) ;
	   }

		//gamma
		if ( _gamma < 1 )
		{
			doGammaAdjustment( ) ;
		}

		_lpD3DDevice->EndScene( ) ;
	}
	
	
	if (  _fullscreen == true  && iamready == true )
	{
		_internalScrFix = GetTickCount( ) - _internalScrFix2 ; 
		if ( _internalScrFix >= 1000 )
		{
			_internalScrFix = GetTickCount( ) ;
			_internalScrFix2 = _internalScrFix ;
			_scrTimer++ ;		//add one second to our timer
		
			if ( _scrTimer > _startSCR  && _scrActive == true  )
			{
			//	minimize( ) ;
				 keybd_event(VK_MENU, 0, 0, 0);
  				keybd_event(VK_TAB, 0, 0, 0);
				_scrTimer = 0 ;
				Sleep(100 ) ;
				keybd_event(VK_MENU, 0, KEYEVENTF_KEYUP, 0);
				  keybd_event(VK_TAB, 0, KEYEVENTF_KEYUP, 0);

				
				if ( strcmp( _screenSaverPath , "" ) != 0 )
				{
					KMiscTools::launchFile(_screenSaverPath , true )  ;
				}
			}//if ( _scrTimer > _startSCR  && _scrActive == true  )

			if ( _scrTimer > _screenTimeOut  && _screenTimeOutActive == true    )
			{
				_scrTimer = 0 ;
				minimize(  ) ;
				

				Sleep( 100 ) ;
//				 SystemParametersInfo( 	SPI_SETPOWEROFFTIMEOUT , 800,0,0 ) ;

				SendMessage(HWND_BROADCAST, WM_SYSCOMMAND, SC_MONITORPOWER, (LPARAM) 2);
				//SendMessage( getWindowHandle() , WM_SYSCOMMAND , SC_MONITORPOWER , 2 ) ;
			}//if ( _scrTimer > _startSCR  && _screenTimeOutActive == true  )

		}
	}

	
	isWindowActive = true ;

	t2 =	KMiscTools::getMilliseconds( ) ;





	if ( iamready == true )
	{

	if ( _lpDDSPrimary != NULL )
	{
		if( _fullscreen == false )
		{	

			RECT	r , rw;
			POINT		pt = {0,0 } ;
			
			SetRect( &r ,0,0,_windowWidth , _windowHeight ) ;
			ClientToScreen( _hWndPTK , &pt ) ;
			SetRect( &rw , pt.x , pt.y , pt.x+_windowWidth , pt.y+_windowHeight  ) ;
			
			//en fenetré
			if ( _maxFrameRate >= 0 )
			{
				testCooperative( ) ;
				_lpDD->WaitForVerticalBlank( DDWAITVB_BLOCKBEGIN , 0 ) ;
			}
		
			
			_lpDDSPrimary->Blt( &rw , _lpDDSBack, &r, DDBLT_WAIT, NULL ) ;
//			_lpDDSPrimary->BltFast( pt.x , pt.y , _lpDDSBack, &r, DDBLTFAST_WAIT , NULL ) ;
			
		}
		else
		{
				if ( _maxFrameRate < 0 )
				{
					
	
						testCooperative( ) ;
						if ( _lpDDSPrimary->IsLost() != DDERR_SURFACELOST  )
						{
							_lpDDSPrimary->Flip(NULL, 0) ;
						}
				}
				else
				{
						testCooperative( ) ;
						if ( _lpDDSPrimary->IsLost() != DDERR_SURFACELOST  )
						{
							_lpDDSPrimary->Flip(NULL, DDFLIP_WAIT) ;
						}
				}
		}
	}	

	}	

	if ( restoreView == true )
	{
		testCooperative( ) ;
		setDefaultWorldView( ) ;
	}
	
if ( _lpDD->TestCooperativeLevel () == DD_OK )		
{	
	_lpD3DDevice->BeginScene( ) ;
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
			//	KWindow::setTitle( buffer)  ;
			}while( frameRenderTime <_maxFrameRate ) ;
		}
	}
	
	t1 =	KMiscTools::getMilliseconds( ) ;
	
	if ( waitForBackWindow == false )		return ;
	//test si le jeu est en arriere plan
	if ( GetForegroundWindow( ) == _hWndPTK )		return ;

	//the app is in the background, just idle
	do
	{
		if ( GetMessage( &Msg, NULL, 0, 0  ) )
		{
				TranslateMessage( &Msg );
				DispatchMessage( &Msg ); 
		}
	}while((GetForegroundWindow( ) != _hWndPTK ) && IsWindow( _hWndPTK ) ) ;

		KMiscTools::freezeTimer( ) ;

}

//process the events
void		KWindowD3D::processEvents( void ) 
{
MSG		Msg ;
static	long	screnshot = 0 ;
static	char	ssfilename[260] ;




		if ( KInput::isPressed( K_VK_L_SHIFT ) )
		{
			if ( KInput::isPressed( K_VK_SNAPSHOT ) )
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


	//if the window is minimized then just wait, not important to do anything
	if ( IsIconic( _hWndPTK  ) == (bool)true )
	{
		
		isWindowActive = false ;
		//the app is in the background, just idle
		do
		{
			
		
			if ( GetMessage( &Msg, NULL, 0, 0  ) )
			{
					TranslateMessage( &Msg );
					DispatchMessage( &Msg ); 
			}
		}while( IsIconic( _hWndPTK  )  && IsWindow( _hWndPTK ) ) ;
		
		KMiscTools::freezeTimer( ) ;
		isWindowActive = true ;
	
	}

//	if ( _lpDD == NULL )		return ;

//	if ( _lpDD->TestCooperativeLevel() == DD_OK)		
		while ( isQuit( ) == false && _lpDD->TestCooperativeLevel() != DD_OK)		
		{
			if ( GetMessage( &Msg, NULL, 0, 0  ) )
			{
					TranslateMessage( &Msg );
					DispatchMessage( &Msg ); 
			}



		}
		
	
	//did we lose the buffers ( a minimzation etc... ? )
	if ( _lpDDSPrimary->IsLost() == DDERR_SURFACELOST  )
	{
		if ( isQuit() == false )
		{
		
										    if ( _lpD3DDevice != NULL )		
										      {
											      _lpD3DDevice->EndScene( ) ;
											      _lpD3DDevice->Release( ) ;
											      _lpD3DDevice = NULL ;
										      }

										      if ( _lpDDSPrimary != NULL )	
										      {
											      _lpDDSPrimary->Release( ) ;
											      _lpDDSPrimary = NULL ;
											      _lpDDSBack = NULL ;			//the back is released with the primary if coming from a double buffer fullscreen
										      }

						attachD3DToWindow( ) ;
						KGraphicD3D::forceReloadList( ) ;
		
		}
	}


		isWindowActive = true ;

		//	Sleep( 1 ) ;
}


bool		KWindowD3D::isQuit( void ) 
{
	return _quit ;
}

HWND	KWindowD3D::getWindowHandle(void ) 
{
	return _hWndPTK ;
}



void		KWindowD3D::setMaxFrameRate( long	desiredFrameRate  ) 
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
		_maxFrameRate = -1 ;
		//	if ( _isWaitVBLSupported == true )			WaitVBL( 0 ) ;	

	}
}


bool		KWindowD3D::getRectangleTexCap( void ) 
{
	return true ;
}

bool		KWindowD3D::getAccelerationCap( void )
{
	return true ;
}


void		KWindowD3D::setRectangleTexCap( bool	forceRectangleCap ) 	
{
	forceRectangleCap =forceRectangleCap  ;
}

void		KWindowD3D::setGamma( float	gammai ) 
{
	_gamma = gammai ;
	if ( _gamma < 0 ) _gamma = 0 ;
}

void		KWindowD3D::restore( void )
{
	ShowWindow( _hWndPTK , SW_SHOWNORMAL ) ;
}
bool			KWindowD3D::saveBackBuffer( const char * cpcFileName , long	imageFormat , long resizeW , long resizeH )
{
unsigned	long		*pixelsBack ;

	_lpD3DDevice->EndScene( ) ;

    KGraphicD3D	*backBufGrab ;
    
    //	FILE *f ;
    backBufGrab = new KGraphicD3D ;
    backBufGrab->grabBackBuffer( NULL) ;
    if ( resizeW > 0 && resizeH > 0 )
    {
        backBufGrab->stretchAlphaRect( 0,0,_windowWidth , _windowHeight , 0,0,resizeW , resizeH ) ;
    }
    else
    {
        resizeW = _windowWidth ;
        resizeH 	= _windowHeight ;
    }
    	delete	backBufGrab ;
	pixelsBack = new unsigned long[resizeW*resizeH] ;

	 HDC		dcBackBuffer  ;
	_lpDDSBack->GetDC( &dcBackBuffer ) ;


	COLORREF	colorR ;
	long	x , y ;
	long r,g,b ;
	
	for ( y = 0 ; y< resizeH ; y++ )
	{
		for ( x = 0 ; x< resizeW ; x++ )
		{
				colorR = GetPixel(dcBackBuffer , x , y ) ;
				r = colorR & 0x000000ff ;
				g = (colorR & 0x0000ff00) >> 8 ;
				b = (colorR & 0x00ff0000) >> 16 ;
				
				
				pixelsBack[x+((resizeH-1)-y)*resizeW] = r<<16 | g << 8| b ;
		}
	}
	

	
	_lpDDSBack->ReleaseDC( dcBackBuffer ) ;

	
    CxImage		*cix ;
    
    cix = new  CxImage ;
    cix->CreateFromArray( (unsigned char*)pixelsBack , resizeW , resizeH , 32 , resizeW*4 , false ) ;
    
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



	_lpD3DDevice->BeginScene( ) ;

	return true ;    
}

void		KWindowD3D::minimize( void )
{
	ShowWindow( _hWndPTK , SW_MINIMIZE ) ;
}

	
//callback  for the window  ( differs on  mac )
void		KWindowD3D::setCallBack( ptkWindowCallBack  userProc ) 
{
	_userCallback = userProc ;
}



//PTK callback
void		KWindowD3D::setPTKCallBack( ptkNativeCallBack  userProc ) 
{
	_ptkCallback = userProc ;
}

//change la resolution de l'ecran
bool			KWindowD3D::SwitchToResolution( short	width , short	height , short depth ) 
{
DEVMODE		dv2 ;
	
	if ( depth<= 0 )		depth = 16 ;
	
	dv2.dmSize  = sizeof( DEVMODE ) ;
	dv.dmSize  = sizeof( DEVMODE ) ;

	if ( width > 0 && height > 0 )
	{
		//get the current resolution
		dv.dmFields 	=  DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT | DM_DISPLAYFREQUENCY  ;
		dv2.dmFields =  DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT | DM_DISPLAYFREQUENCY ;
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
		return true ;
	}
	else
	{
		dv.dmFields 	=  DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT | DM_DISPLAYFREQUENCY  ;
		dv2.dmFields =  DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT   ;
		dv.dmDisplayFrequency = 0 ;
		EnumDisplaySettings( NULL , ENUM_CURRENT_SETTINGS , &dv ) ;
		if ( DISP_CHANGE_SUCCESSFUL == ChangeDisplaySettings(  &dv2,   CDS_FULLSCREEN ) )	
		{
			return true ;
		}
	}
	
	return false ;
 }

//restore la resolution
void		KWindowD3D::RestoreResolution( void ) 
{
	//on ne restitue que si ca avait switché
//	if ( dv.dmPelsHeight == 0 )	return ;
	
	ChangeDisplaySettings( &dv ,   CDS_FULLSCREEN ) ;
//Passing NULL for the lpDevMode parameter and 0 for the dwFlags parameter is the 
//easiest way to return to the default mode after a dynamic mode change. 
//	ChangeDisplaySettings( 0,0) ;
}

LRESULT CALLBACK	KWindowD3D::GameWindowProc( HWND hWnd, UINT messg,	WPARAM wParam, LPARAM lParam ) 
{
KEvent	kEvent ;
KWindowD3D		*kwD3D = NULL ;
bool					soundstatus  = true ;


	kwD3D =(KWindowD3D*)GetWindowLong( hWnd , GWL_USERDATA ) ;

	if ( messg == 	WM_SYSCOMMAND  &&  wParam == SC_MONITORPOWER  )
	{
			  kEvent.type 	= K_EVENT_MONITORPOWEROFF ;
			if ( kwD3D )
			{
				if ( kwD3D->_ptkCallback != NULL )
				{
					if ( kwD3D->_ptkCallback( &kEvent ) == false)  return  0 ;
				}
			}
	}
	
	if ( kwD3D != NULL )
	{
		if ( kwD3D->_userCallback != NULL )
		{
			if ( kwD3D->_userCallback( hWnd , messg , wParam , lParam ) == false )	return 0 ;
		}
	
		//native PTK event system ( multiplatform )
		if ( kwD3D->_ptkCallback != NULL )
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
				
	
				case	WM_LBUTTONDBLCLK:
					kEvent.type = K_EVENT_DBLCLICK ;
					kEvent.buttonIndex = K_LBUTTON ;
				break;
				case	WM_RBUTTONDBLCLK:
					kEvent.type = K_EVENT_DBLCLICK ;
					kEvent.buttonIndex = K_RBUTTON ;
				break;
			
				case	WM_MOUSEMOVE:
					kEvent.type = K_EVENT_MOUSEMOVE ;
				break;
				case	WM_LBUTTONDOWN:
					kEvent.type = K_EVENT_MOUSEDOWN ;
					kEvent.buttonIndex = K_LBUTTON ;
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
					 	soundstatus = false ; 
					}
					if ( wParam == WA_CLICKACTIVE )
					{ 
						kEvent.type 	= K_EVENT_ACTIVATED ;
					}
					
					if ( wParam == WA_ACTIVE )
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
			if ( kwD3D->_ptkCallback( &kEvent ) == false )	return 0 ;
		
	}	//if ( kwD3D != NULL )
	}


			
	switch(messg)
	{
		
		case	WM_KEYDOWN:
		case	WM_LBUTTONDOWN:
		case	WM_MOUSEMOVE:
		case	WM_CHAR:
			if ( kwD3D != NULL )
			{
				kwD3D->_monitorOn = true ;
				 kwD3D->_scrTimer = 0 ;
			}
		break ;
		
		
		case	WM_MOUSEWHEEL:
			if ( kwD3D != NULL )
			{
				kwD3D->_monitorOn = true ;
				 kwD3D->_scrTimer = 0 ;
			}
			
			KInput::setLastWheelValue(  HIWORD(wParam) );
		break;
		case	WM_CLOSE:
			if ( kwD3D != NULL )
			{
				 kwD3D->_quit = true ;
			}
			PostQuitMessage( 0 );
		break;
		case WM_DESTROY:
			if ( kwD3D != NULL )
			{
				 kwD3D->_quit = true ;
			}			
			PostQuitMessage( 0 );
		break;


		default:
			return( DefWindowProc( hWnd, messg, wParam, lParam ) );
	}
	

	return	0 ;
	
}

bool		KWindowD3D::setQuit( bool quitstate ) 
{
	_quit = quitstate ;
	return _quit ;
}


//set default world view
void	KWindowD3D::setDefaultWorldView( void ) 
{
	setWorldView( 0,0,0,1,false ) ;
}


void			KWindowD3D::showWindow( bool show ) 
{
	if ( _hWndPTK == 0 )
	{
		_visibleState = show ;
		return ;
	}
	
	if ( show == true )
	{
		ShowWindow( _hWndPTK , SW_SHOW ) ;

	}
	else
	{
		ShowWindow( _hWndPTK , SW_HIDE) ;	

	}
}

bool		KWindowD3D::isWindowVisible( void )  
{
	return IsWindowVisible( _hWndPTK )  ;
}


void		KWindowD3D::testCooperative(void )
{
MSG		Msg ;

	if (  _lpDD == NULL )		return ;
	
		while ( isQuit( ) == false && _lpDD->TestCooperativeLevel() != DD_OK)		
		{
			if ( GetMessage( &Msg, NULL, 0, 0  ) )
			{
					TranslateMessage( &Msg );
					DispatchMessage( &Msg ); 
			}
		}


}
	
//setworldview old ( non affecting kbatch )

/*
void 	KWindowD3D::setWorldView(float translateX, float translateY, float rotation, float zoom, bool clearworld)
{    
D3DRECT D3DRect = { 0, 0, _windowWidth, _windowHeight};
MSG	Msg ;


	if ( _lpD3DDevice == NULL )		return ;
	if (  _lpDD == NULL )					return ;
	
	if ( _lpDD->TestCooperativeLevel () != DD_OK )		
	{
			while ( isQuit( ) == false && _lpDD->TestCooperativeLevel() != DD_OK)		
		{
			if ( GetMessage( &Msg, NULL, 0, 0  ) )
			{
					TranslateMessage( &Msg );
					DispatchMessage( &Msg ); 
			}
		}
	//	flipBackBuffer( ) ;
		return ;
	}

	if ( _lpDD->TestCooperativeLevel () != DD_OK )		return ;
	

	 _lpD3DDevice->SetRenderTarget(_lpDDSBack , 0 ) ;
 	 _lpD3DDevice->SetRenderState(D3DRENDERSTATE_SHADEMODE, D3DSHADE_FLAT);
//	 _lpD3DDevice->SetLightState(D3DLIGHTSTATE_MATERIAL,NULL);

	D3DVIEWPORT7 vp = { 0, 0, _windowWidth, _windowHeight , 0.0f, 1.0f };
	_lpD3DDevice->SetViewport( &vp ) ;

	_lpD3DDevice->SetRenderState(D3DRENDERSTATE_LIGHTING, false);
    _lpD3DDevice->SetRenderState(D3DRENDERSTATE_ZENABLE, false);
    _lpD3DDevice->SetRenderState(D3DRENDERSTATE_CULLMODE, D3DCULL_NONE);
    _lpD3DDevice->SetRenderState(D3DRENDERSTATE_COLORVERTEX, true);
 
	translateY = -translateY;

	if(clearworld == true)
	{

	      if (_use3d == true )
	       {
		      D3DMATRIX  mat ;

		  	identity500( &mat ) ;
			mat._31 *=-1 ;
			mat._32 *=-1 ;
			mat._33 *=-1 ;
			mat._34 *=-1 ;
		
		   _lpD3DDevice->SetTransform(D3DTRANSFORMSTATE_VIEW, &mat);
		   _lpD3DDevice->SetTransform(D3DTRANSFORMSTATE_PROJECTION, &mat);
		   _lpD3DDevice->SetTransform(D3DTRANSFORMSTATE_WORLD, &mat);

			_lpD3DDevice->Clear(1UL, &D3DRect, D3DCLEAR_TARGET, 0xff000000, 1, 0L );
			_lpD3DDevice->Clear(1UL, &D3DRect, D3DCLEAR_ZBUFFER, 0xff000000, 1, 0L );
	      }
	      
	      	_lpD3DDevice->Clear(1UL, &D3DRect, D3DCLEAR_TARGET, _clearColor, 1, 0L );

	}

	// Construit une matrice orthographique
	D3DMATRIX mat, mat2;
//for cabinet
//	ortho(&mat, -_windowWidth, -_windowHeight, -100, 100);
	
	//loadIdentity
	ortho(&mat, _windowWidth, _windowHeight, -100, 100);
	_lpD3DDevice->SetTransform(D3DTRANSFORMSTATE_PROJECTION, &mat);

	// Applique les transformations a l'ensemble des sprites
	translate(mat, -(float)(_windowWidth / 2), (float)(_windowHeight/2), 0);

	rotatez(mat2, rotation);
	mat = mat*mat2;
	scale(mat2, zoom, zoom, 0);
	mat = mat*mat2;
	translate(mat2, translateX, -translateY, 0);
	mat = mat*mat2;
	_lpD3DDevice->SetTransform(D3DTRANSFORMSTATE_VIEW, &mat);

}
*/

	
//setworldview
void 	KWindowD3D::setWorldView(float translateX, float translateY, float rotation, float zoom, bool clearworld)
{    
D3DRECT D3DRect = { 0, 0, _windowWidth, _windowHeight};


	if ( _lpD3DDevice == NULL )		return ;

	 _lpD3DDevice->SetRenderTarget(_lpDDSBack , 0 ) ;
 	 _lpD3DDevice->SetRenderState(D3DRENDERSTATE_SHADEMODE, D3DSHADE_FLAT);
//	 _lpD3DDevice->SetLightState(D3DLIGHTSTATE_MATERIAL,NULL);

	D3DVIEWPORT7 vp = { 0, 0, _windowWidth, _windowHeight , 0.0f, 1.0f };
	_lpD3DDevice->SetViewport( &vp ) ;

	_lpD3DDevice->SetRenderState(D3DRENDERSTATE_LIGHTING, false);
    _lpD3DDevice->SetRenderState(D3DRENDERSTATE_ZENABLE, false);
    _lpD3DDevice->SetRenderState(D3DRENDERSTATE_CULLMODE, D3DCULL_NONE);
    _lpD3DDevice->SetRenderState(D3DRENDERSTATE_COLORVERTEX, true);
 
	translateY = -translateY;

	if(clearworld == true)
	{

	      if (_use3d == true )
	       {
		      D3DMATRIX  mat ;

		  	identity500( &mat ) ;
			mat._31 *=-1 ;
			mat._32 *=-1 ;
			mat._33 *=-1 ;
			mat._34 *=-1 ;
		
		   _lpD3DDevice->SetTransform(D3DTRANSFORMSTATE_VIEW, &mat);
		   _lpD3DDevice->SetTransform(D3DTRANSFORMSTATE_PROJECTION, &mat);
		   _lpD3DDevice->SetTransform(D3DTRANSFORMSTATE_WORLD, &mat);

			_lpD3DDevice->Clear(1UL, &D3DRect, D3DCLEAR_TARGET, 0xff000000, 1, 0L );
			_lpD3DDevice->Clear(1UL, &D3DRect, D3DCLEAR_ZBUFFER, 0xff000000, 1, 0L );
	      }
	      
	      	_lpD3DDevice->Clear(1UL, &D3DRect, D3DCLEAR_TARGET, _clearColor, 1, 0L );

	}


	D3DXMATRIX projectionMatrix;
	ortho( (D3DMATRIX*)&projectionMatrix, _windowWidth, _windowHeight, -100, 100 );
	_lpD3DDevice->SetTransform( D3DTRANSFORMSTATE_PROJECTION, (LPD3DMATRIX)&projectionMatrix );

	D3DXMATRIX Identity;
	D3DXMatrixIdentity( &Identity );
	_lpD3DDevice->SetTransform( D3DTRANSFORMSTATE_VIEW, (LPD3DMATRIX)&Identity );

	D3DXMATRIX worldMatrix;
	D3DXMatrixIdentity( &worldMatrix );

	D3DXMATRIX translateMatrix;
	D3DXMATRIX rotateMatrix;
	D3DXMATRIX scaleMatrix;
	
	D3DXMatrixTranslation( &translateMatrix, -_windowWidth/2, _windowHeight/2, 0 );	
	D3DXMatrixMultiply( &worldMatrix, &worldMatrix, &translateMatrix );

	D3DXMatrixRotationZ( &rotateMatrix, rotation / 180 * 3.14159265358979323846f);
	D3DXMatrixMultiply( &worldMatrix, &worldMatrix, &rotateMatrix );

	D3DXMatrixScaling( &scaleMatrix, zoom, zoom, 1 );
	D3DXMatrixMultiply( &worldMatrix, &worldMatrix, &scaleMatrix );
	
	D3DXMatrixTranslation( &translateMatrix, translateX, translateY, 0 );
	D3DXMatrixMultiply( &worldMatrix, &worldMatrix, &translateMatrix);

//	D3DXMatrixScaling( &scaleMatrix, 1, -1, 1 );
//	D3DXMatrixMultiply( &worldMatrix, &worldMatrix, &scaleMatrix );

	_lpD3DDevice->SetTransform( D3DTRANSFORMSTATE_WORLD, (LPD3DMATRIX)&worldMatrix );

}
bool		KWindowD3D::getFullScreenState( void )
{
	return _fullscreen ;
}