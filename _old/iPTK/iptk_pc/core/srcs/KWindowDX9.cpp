#include	"KWindowDX9.h"
#include	"KMiscTools.h"
#include	"KGraphicDX9.h"
#include	"KBatchDX9.h"
#include "D3DX9math.h"
#include	<stdio.h>
#include	<stdlib.h>

extern	void 	ortho(D3DXMATRIX *mat, long width, long height, float znear, float zfar) ;

//#define		GAMECLASSNAME		"PTK DX9 RENDERER"

KWindowDX9::KWindowDX9( )
{
	_graphic = NULL;
	_backbufferTarget = 0 ;
	_hwndPTK = 0 ;
	_hwndParent = 0 ;
	_clearColor = 0 ;
	_d3d9Ptr	= NULL  ; //the D3DDevice
	_d3d9Device = NULL ; //  rendering device
	
	_maxFrameRate  = 0 ;
	_gamma	= 1 ;
	_ptkCallback = NULL ;
	_userCallback = NULL;
	_use3d = false ;
	_quit = false ;

	_translateX = 0;
	_translateY = 0;
	_rotation		=	0;
	_zoom				= 1;

}

bool		KWindowDX9::setQuit( bool quitstate ) 
{
	_quit = true ;
	
	return _quit ;
}


KWindowDX9::KWindowDX9( bool use3d )
{
	_graphic = NULL;
	_backbufferTarget = 0 ;
	_hwndPTK = 0 ;
	_hwndParent = 0 ;
	_clearColor = 0 ;
	_d3d9Ptr	= NULL  ; //the D3DDevice
	_d3d9Device = NULL ; //  rendering device
	
	_maxFrameRate  = 0 ;
	_gamma	= 1 ;
  
	_use3d = false ;
	_quit = false ;
	_ptkCallback = NULL ;
	_userCallback = NULL;

	_translateX = 0;
	_translateY = 0;
	_rotation		=	0;
	_zoom				= 1; 
}

KWindowDX9::~KWindowDX9( )
{
	_ptkCallback = NULL ;
	_userCallback = NULL;
	releaseD3D9( ) ;
}

//release our dx stuff
void		KWindowDX9::releaseD3D9( void )
{
	
	if ( _d3d9Device != NULL )
	{
		_d3d9Device->Release( ) ;
	}


	if ( _d3d9Ptr != NULL )
	{
		_d3d9Ptr->Release( ) ;
	}

	_d3d9Ptr	= NULL  ; //the D3DDevice
	_d3d9Device = NULL ; //  rendering device


}

//init dx9
bool			KWindowDX9::initDx9( void )
{
 HRESULT  hr ;
 D3DFORMAT d3dFormat[4] =  {D3DFMT_X8R8G8B8 , D3DFMT_R8G8B8 , D3DFMT_R5G6B5 , D3DFMT_X1R5G5B5 } ;
 D3DFORMAT selectedFormat  = D3DFMT_X8R8G8B8 ;
	long i ;

	_d3d9Ptr = Direct3DCreate9( D3D_SDK_VERSION ) ;

	if( _d3d9Ptr == NULL ) return false ;



//check colors supported for fullscreen
		for ( i = 0 ; i < 4 ; i++ )
		{
			hr = _d3d9Ptr->CheckDeviceType(  D3DADAPTER_DEFAULT ,D3DDEVTYPE_HAL ,d3dFormat[i]  , d3dFormat[i] , false ) ;
			if ( hr == D3D_OK )
			{
					selectedFormat = d3dFormat[i] ;
			}
		}





   memset( &d3dpp, 0 , sizeof(d3dpp) );
	KInput::_fullScreen = _fullscreen ;

	if (_fullscreen)
	{
		d3dpp.Windowed = FALSE;
	}
	else
	{
		d3dpp.Windowed = TRUE;
	}
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;

	
	d3dpp.hDeviceWindow = _hwndPTK ;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_ONE;
	d3dpp.BackBufferWidth = _windowWidth;
	d3dpp.BackBufferHeight = _windowHeight;

	if ( 	d3dpp.Windowed == false )
	{
		d3dpp.BackBufferFormat = selectedFormat; //for fullscreen
	}
	else
	{
		d3dpp.BackBufferFormat = D3DFMT_UNKNOWN; //for windowed
	}

	d3dpp.BackBufferCount = 1;
	d3dpp.MultiSampleType = D3DMULTISAMPLE_NONE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_FLIP;
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT; // 50


	 if( FAILED( _d3d9Ptr->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, _hwndPTK ,
                                      D3DCREATE_SOFTWARE_VERTEXPROCESSING,
                                      &d3dpp, &_d3d9Device ) ) )
    {
        return false;
    }

	hr = _d3d9Device->GetRenderTarget( 0, &_backbufferTarget );
	KGraphicDX9::setDirectX( _d3d9Ptr , _d3d9Device ) ;
	KBatchDX9::setDirectX( _d3d9Ptr , _d3d9Device ) ;

	return true ;
}

bool		KWindowDX9::getFullScreenState( void ) 
{
return _fullscreen ;
}
//create game window
bool		KWindowDX9::createGameWindow( short width, short height , short bpp, bool windowed, const char* title ) 
{
WNDCLASS			wndClass ;
RECT				r ;
int					screenWidth , screenHeight ;
unsigned long		windowStyle = WS_CAPTION | WS_SYSMENU | WS_VISIBLE | WS_MINIMIZEBOX ;


	_windowWidth		=	width ;
	_windowHeight	=	height ;
	_windowDepth	=	bpp ;
	_fullscreen			=	!windowed ;

	KInput::_fullScreen = _fullscreen ;


	windowStyle = WS_CAPTION | WS_SYSMENU | WS_VISIBLE | WS_MINIMIZEBOX ;
	
	if ( bpp != -1 )
	{
//		SwitchToResolution( -1,-1,depth ) ;
	}
	
	strcpy ( _windowTitle , title ) ;

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

	RegisterClass( &wndClass ) ;

	SetRect( &r , 0 , 0 , width , height ) ;

	if ( _hwndParent != 0  )		windowStyle = WS_CHILD | WS_POPUP |	WS_VISIBLE ;


	//calculate the client rect
	AdjustWindowRect( &r , windowStyle  , false ) ;

		_hwndPTK		=	CreateWindowEx( 	0,	GAMECLASSNAME ,
														_windowTitle,
														windowStyle ,
														(screenWidth-(r.right-r.left))/2 ,			//centers the window
														(screenHeight-(r.bottom-r.top))/2,
														(r.right-r.left)	,	
														(r.bottom-r.top)  ,
														_hwndParent ,
														0 ,
														GetModuleHandle( NULL ) ,
														0 ) ;


	SetWindowLong( _hwndPTK , GWL_USERDATA , (long)this );
	ShowWindow( _hwndPTK, SW_SHOW );
	UpdateWindow( _hwndPTK );
	KInput::initInputEx( _hwndPTK, screenWidth, screenHeight ) ;

	initDx9( ); 

	return true ;

}

void KWindowDX9::setDefaultWorldView( void )
{
	setWorldView( 0, 0, 0, 1, false );
}

void KWindowDX9::setWorldView(float	translateX, float translateY, float rotation, float zoom, bool clearworld)
{
	if(	_d3d9Device == NULL )		
	{
		return;
	}

	//will be used for kbatch
	_translateX = translateX ;
	_translateY = translateY;
	_rotation	= rotation ;
	_zoom		= zoom ;
	
	D3DSURFACE_DESC desc;

	if (_graphic != NULL && _graphic->_pTargetSurface != NULL)
	{
		_graphic->_pTargetSurface->GetDesc(&desc);
		//_d3d9Device->SetRenderTarget(0, _graphic->_pTargetSurface);
		_graphic->startRenderToTexture();
	}
	else 
	{
		_backbufferTarget->GetDesc(&desc);
		_d3d9Device->SetRenderTarget(0, _backbufferTarget);
	}

	if ( clearworld == true )
	{
		_d3d9Device->Clear(0, NULL, D3DCLEAR_TARGET, _clearColor, 1.0f, 0);
	}

	D3DXMATRIX projectionMatrix;
	ortho( &projectionMatrix, desc.Width, desc.Height, -0, 1 );
	_d3d9Device->SetTransform( D3DTS_PROJECTION, &projectionMatrix );

	D3DXMATRIX Identity;
	D3DXMatrixIdentity( &Identity );
	_d3d9Device->SetTransform( D3DTS_VIEW, &Identity );

	D3DXMATRIX worldMatrix;
	D3DXMatrixIdentity( &worldMatrix );

	D3DXMATRIX translateMatrix;
	D3DXMATRIX rotateMatrix;
	D3DXMATRIX scaleMatrix;
	
	D3DXMatrixTranslation( &translateMatrix, -(int)desc.Width/2 -0.5f, -(int)desc.Height/2 -0.5f, 0 );	// 28/05/2008, TZ - 0.5f offset for clear 2D rendering
	D3DXMatrixMultiply( &worldMatrix, &worldMatrix, &translateMatrix );

	D3DXMatrixRotationZ( &rotateMatrix, rotation / 180 * 3.14159265358979323846f);
	D3DXMatrixMultiply( &worldMatrix, &worldMatrix, &rotateMatrix );

	D3DXMatrixScaling( &scaleMatrix, -zoom, zoom, 1 );
	D3DXMatrixMultiply( &worldMatrix, &worldMatrix, &scaleMatrix );
	
	D3DXMatrixTranslation( &translateMatrix, translateX, translateY, 0 );
	D3DXMatrixMultiply( &worldMatrix, &worldMatrix, &translateMatrix);

	D3DXMatrixScaling( &scaleMatrix, -1, -1, 1 );
	D3DXMatrixMultiply( &worldMatrix, &worldMatrix, &scaleMatrix );

	_d3d9Device->SetTransform( D3DTS_WORLD, &worldMatrix );

}


void	 	KWindowDX9::setParentWindow( HWND	hwndParent ) 
{
			_hwndParent  = hwndParent ;
}

//flip back buffer
void KWindowDX9::flipBackBuffer(bool waitForBackWindow, bool restoreview) 
{
	MSG		Msg ;
	static	long	t1 = 0 ;
	unsigned 	long		t2 , frameRenderTime ;

	if (_d3d9Device == NULL)		
	{
		return;
	}

	_d3d9Device->EndScene( );

	t2 =	KMiscTools::getMilliseconds( ) ;


    //flips the backbuffer
    if (_graphic == NULL)
	{
		_d3d9Device->Present( NULL, NULL, NULL, NULL );
	}
	else
	{
		_graphic->endRenderToTexture();
	}
	//_d3d9Device->BeginScene( ) ;

	HRESULT hr = _d3d9Device->TestCooperativeLevel();

	if (hr == D3DERR_DEVICELOST) 
	{ //Device is lost and cannot be reset yet
		Sleep(100); 
		hr = _d3d9Device->TestCooperativeLevel();
	}
	
	if (hr == D3DERR_DEVICENOTRESET )//&& _fullscreen)  /* _fullscreen commented out: 7/06/2008 by Tomasz Zielinski*/
	{ //Lost but we can reset it now
		_backbufferTarget->Release();
		KGraphicDX9::releaseCurrents();
		KBatchDX9::releaseCurrents();
		
		hr=_d3d9Device->Reset(&d3dpp);
		
		hr = _d3d9Device->GetRenderTarget( 0, &_backbufferTarget );
		KGraphicDX9::initCurrents();
		KBatchDX9::initCurrents();

	}

	processEvents( ) ;

	_d3d9Device->BeginScene( ) ;

	
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
	if ( GetForegroundWindow( ) == _hwndPTK )		return ;

	//the app is in the background, just idle
	do
	{
		if ( GetMessage( &Msg, NULL, 0, 0  ) )
		{
				TranslateMessage( &Msg );
				DispatchMessage( &Msg ); 
		}
	}while((GetForegroundWindow( ) != _hwndPTK ) && IsWindow( _hwndPTK ) ) ;

		KMiscTools::freezeTimer( ) ;


}

void KWindowDX9::Resize(int width, int height)
{
	if (width != 0 && height != 0)
	{
		_windowWidth = width;
		_windowHeight = height;
		d3dpp.BackBufferWidth = width;
		d3dpp.BackBufferHeight = height;

		_backbufferTarget->Release();
		KGraphicDX9::releaseCurrents();
		KBatchDX9::releaseCurrents();
		
		HRESULT hr=_d3d9Device->Reset(&d3dpp);
		
		KGraphicDX9::initCurrents();
		KBatchDX9::initCurrents();
		hr = _d3d9Device->GetRenderTarget( 0, &_backbufferTarget );
	}	
}

LRESULT CALLBACK	KWindowDX9::GameWindowProc( HWND hWnd, UINT messg,	WPARAM wParam, LPARAM lParam ) 
{
	KWindowDX9	*thisWindow ;
	KEvent	kEvent ;
	
	thisWindow  = (KWindowDX9*)GetWindowLong( hWnd , GWL_USERDATA ) ;

	if ( thisWindow != NULL && thisWindow->_userCallback != NULL )
	{
		if ( thisWindow->_userCallback( hWnd , messg , wParam , lParam ) == false )	
		{
			return 0;
		}
	}
	if ( thisWindow != NULL && thisWindow->_ptkCallback != NULL )
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
			//case	WM_MOUSEWHEEL:
			//	kEvent.type = K_EVENT_WHEEL ;
			//	kEvent.wheel =  HIWORD(wParam) ;
			//	KInput::setLastWheelValue( kEvent.wheel ) ;
			//break;
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
		
		if ( thisWindow->_ptkCallback( &kEvent ) == false )	
		{
			return 0;
		}
	}

	switch(messg)
	{	
		


		case	WM_CLOSE:
			thisWindow->_quit = true ;
			PostQuitMessage( 0 );
		break;
		case WM_DESTROY:
			thisWindow->_quit = true ;
			PostQuitMessage( 0 );
		break;
		case WM_SIZE:
			if (thisWindow && !thisWindow->_fullscreen)
			{
				thisWindow->Resize(LOWORD(lParam), HIWORD(lParam));
			}
			break;
	
		default:
			return( DefWindowProc( hWnd, messg, wParam, lParam ) );
	}
	
	return	0 ;
	
}

void		KWindowDX9::terminate( void )  
{
	_quit = true ;
}

//process the events
void		KWindowDX9::processEvents( void )
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
			
				saveBackBuffer( KMiscTools::makeFilePath( ssfilename ) , D3DXIFF_TGA , 0 , 0 ) ;
				KInput::waitForKeyRelease( K_VK_SNAPSHOT ) ;
				KInput::waitForKeyRelease( K_VK_L_SHIFT ) ;			
			}
		}
		
			if ( PeekMessage( &Msg, NULL, 0, 0 , PM_REMOVE ) )
			{
				TranslateMessage( &Msg );
				DispatchMessage( &Msg ); 
			}
			
}

//bool		KWindowDX9::getFullScreenState( void )  
///{
//	return _fullscreen ;
//}


void			KWindowDX9::minimize( void )
{
	ShowWindow( _hwndPTK , SW_MINIMIZE ) ;
}

void			KWindowDX9::restore( void )
{
	ShowWindow( _hwndPTK , SW_SHOWNORMAL ) ;
}


bool		KWindowDX9::hasFocus(void) 
{
		return GetForegroundWindow( ) == _hwndPTK ;
}

void		KWindowDX9::setTitle( const char * title ) 
{
	SetWindowText( _hwndPTK , title ) ;
}

void			KWindowDX9::showWindow( bool show ) 
{

	if ( show == true )
	{
		ShowWindow( _hwndPTK , SW_SHOW ) ;
	}
	else
	{
		ShowWindow( _hwndPTK , SW_HIDE) ;	

	}
}

bool		KWindowDX9::toggleFullScreen( bool 	fullscreen ) 
{
long		windowStyle = WS_CAPTION | WS_SYSMENU | WS_VISIBLE | WS_MINIMIZEBOX ;


	if (d3dpp.Windowed == fullscreen)
	{
		d3dpp.Windowed = !fullscreen;
		d3dpp.hDeviceWindow = _hwndPTK ;
	
	d3dpp.hDeviceWindow = _hwndPTK ;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_ONE;
	d3dpp.BackBufferWidth = _windowWidth;
	d3dpp.BackBufferHeight = _windowHeight;
	d3dpp.BackBufferCount = 1;
	d3dpp.MultiSampleType = D3DMULTISAMPLE_NONE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_FLIP;
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT; // 50

		_fullscreen = fullscreen;

		_backbufferTarget->Release();
		KGraphicDX9::releaseCurrents();
		KBatchDX9::releaseCurrents();
		
		HRESULT hr=_d3d9Device->Reset(&d3dpp);
		
		KGraphicDX9::initCurrents();
		KBatchDX9::initCurrents();
		hr = _d3d9Device->GetRenderTarget( 0, &_backbufferTarget );

		if ( fullscreen == false )
		{
			SetWindowLong( _hwndPTK , GWL_STYLE , windowStyle ) ;
			RECT	r ;
			SetRect( &r , 0,0 , _windowWidth, _windowHeight ) ;	
			AdjustWindowRect( &r , windowStyle  , false ) ;
			MoveWindow( _hwndPTK , 100,100,r.right-r.left, r.bottom-r.top, true ) ;
			UpdateWindow( _hwndPTK ) ;
			SetFocus( _hwndPTK ) ;
		}
		else
		{
			SetFocus( _hwndPTK ) ;
		}



	}
	KInput::_fullScreen = _fullscreen ;

	return _fullscreen ;
}


bool		KWindowDX9::saveBackBuffer( const char * cpcFileName , long	imageFormat  , long resizeW , long resizeH )
{
	HRESULT hr = _d3d9Device->TestCooperativeLevel();

	if(!SUCCEEDED(hr))
	{
		return false;
	}

	IDirect3DSurface9* pTargetSurface=NULL;
	_d3d9Device->GetRenderTarget(0,&pTargetSurface);
	
	D3DSURFACE_DESC desc;
	pTargetSurface->GetDesc(&desc);
	
	IDirect3DTexture9* pTempTexture=NULL;
	_d3d9Device->CreateTexture(desc.Width,desc.Height,
		1,D3DUSAGE_DYNAMIC,desc.Format,D3DPOOL_SYSTEMMEM,&pTempTexture,NULL);
		
	IDirect3DSurface9* pTempSurface=NULL;
	pTempTexture->GetSurfaceLevel(0,&pTempSurface);
	_d3d9Device->GetRenderTargetData(pTargetSurface,pTempSurface);
	
	IDirect3DTexture9* _texture;
	_d3d9Device->CreateTexture( desc.Width, desc.Height, 
		1, //only one level of mipmapping
		D3DUSAGE_DYNAMIC, //usage  -D3DUSAGE_RENDERTARGET  for a rendering target
		desc.Format ,
		D3DPOOL_DEFAULT,
		&_texture,
		NULL);

	_d3d9Device->UpdateTexture(pTempTexture, _texture);

	pTargetSurface->Release();
	pTempSurface->Release();
	pTempTexture->Release();

	hr = D3DXSaveTextureToFile(cpcFileName,(D3DXIMAGE_FILEFORMAT)imageFormat,_texture,NULL);

	_texture->Release();

	if (hr != D3D_OK)
	{
		return false;
	}

	return true;
}

bool		KWindowDX9::isWindowVisible( void )  
{
	return (bool)IsWindowVisible( _hwndPTK )  ;
}


void		KWindowDX9::setClearColor ( float r , float g , float b , float a ) 
{
	 _clearColor =  D3DCOLOR_COLORVALUE( r,g, b , a);
}


void		KWindowDX9::setCallBack( ptkWindowCallBack  userProc ) 
{
	_userCallback = userProc ;
}

void		KWindowDX9::setPTKCallBack( ptkNativeCallBack  userProc ) 
{
	_ptkCallback = userProc ;
}



bool		KWindowDX9::isQuit( void ) 
{
	return _quit ;
}

HWND	KWindowDX9::getWindowHandle(void ) 
{
	return _hwndPTK ;
}

long		KWindowDX9::getWindowWidth( void ) 
{
	return _windowWidth ;
}

long		KWindowDX9::getWindowHeight( void ) 
{
	return _windowHeight ;

}


void		KWindowDX9::setMaxFrameRate( long	desiredFrameRate  ) 
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


bool		KWindowDX9::getRectangleTexCap( void ) 
{
	return true ;
}

bool		KWindowDX9::getAccelerationCap( void )
{
	return true ;
}


void		KWindowDX9::setRectangleTexCap( bool	forceRectangleCap ) 	
{
	forceRectangleCap =forceRectangleCap  ;
}

void		KWindowDX9::setGamma( float	gammai ) 
{
	_gamma = gammai ;
	if ( _gamma < 0 ) _gamma = 0 ;
}


void	KWindowDX9::setClipping( long x1 , long y1, long x2, long y2 )
{
	RECT	r; 
	
	if ( _d3d9Device == NULL )	return ;

	SetRect( &r, x1, y1, x2, y2 ) ;
//	HRESULT hr = _d3d9Device->SetScissorRect(  &r  ) ;

	D3DVIEWPORT9 vp;
	vp.X		= x1;
	vp.Y		= y1;
	vp.Width	= x2 - x1;
	vp.Height	= y2 - y1;
	vp.MinZ		= -0.0f;
	vp.MaxZ		= 1.0f;
	_d3d9Device->SetViewport( &vp );

	// -------

	D3DSURFACE_DESC desc;

	if (_graphic != NULL && _graphic->_pTargetSurface != NULL)
	{
		_graphic->_pTargetSurface->GetDesc(&desc);
	}
	else 
	{
		_backbufferTarget->GetDesc(&desc);
	}

	D3DXMATRIX proj;

	D3DXMatrixOrthoOffCenterLH( &proj,	(float)x1 - desc.Width/2.0f, 
										(float)x2 - desc.Width/2.0f, 

										desc.Height - (float)y2 - desc.Height/2.0f, 
										desc.Height - (float)y1 - desc.Height/2.0f, 

										-0, 1 
								);

	_d3d9Device->SetTransform( D3DTS_PROJECTION, &proj );


//	hr = hr;
}

void KWindowDX9::SetRenderTarget(KGraphic* graphic)
{
	if (_graphic != NULL)
	{
		flipBackBuffer();
	}
	_graphic = (KGraphicDX9*)graphic;
}
