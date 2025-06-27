#include	<windows.h>
#include 	<stdio.h>
#include	"KInput.h"
#include	"dinput.h"
#include		"KPTK.h"
#include		"ptk.h"


 
KGraphic*	KInput::surf_mouse = NULL  ;


HWND		KInput::_hwnd ;
HKL			KInput::hKL ;
bool			KInput::joystick[2] = {false , false } ;
bool			KInput::_is9x = false ;
bool			KInput::_fullScreen = false;

int		KInput::_screen_width = 0;
int		KInput::_screen_height = 0;

 unsigned  long			mousePattern[] = 
{
//first too entries Widh , height
16,16,
//pixel data
 0xffffffff ,0xffffffff,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0xffffffff,0xff000000,0xffffffff,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0xffffffff,0xff000000,0xff000000,0xffffffff,0,0,0,0,
0,0,0,0,0,0,0,0,
0xffffffff,0xff000000,0xff000000,0xff000000,0xffffffff,0,0,0,0,
0,0,0,0,0,0,0,0xffffffff,
0xff000000,0xff000000,0xff000000,0xff000000,0xffffffff,0,0,0,0,0,0,0,0,0,0,0xffffffff,0xff000000,0xff000000,
0xff000000,0xff000000,0xff000000,0xffffffff,0,0,0,0,
0,0,0,0,0,0xffffffff,0xff000000,0xff000000,0xff000000,
0xff000000,0xff000000,0xff000000,0xffffffff,0,0,0,0,
0,0,0,0,0xffffffff,0xff000000,0xff000000,0xff000000,0xff000000,0xff000000,
0xff000000,0xff000000,0xffffffff,0,0,0,0,0,0,
0,0xffffffff,0xff000000,0xff000000,0xff000000,0xff000000,0xff000000,0xff000000,0xff000000,0xff000000,0xffffffff,
0,0,0,0,0,0,0xffffffff,0xff000000,
0xff000000,0xff000000,0xff000000,0xff000000,0xff000000,0xff000000,0xffffffff,0,0,0,0,0,0,0,0xffffffff,
0xff000000,0xff000000,0xff000000,0xff000000,0xff000000,0xffffffff,0xffffffff,0,0,0,0,0,0,0,0,0xffffffff,
0xff000000,0xff000000,0xff000000,0xff000000,0xff000000,0xffffffff,0,0,0,0,0,
0,0,0,0,0xffffffff,0xff000000,0xff000000,0xffffffff,
0xff000000,0xffffffff,0,0,0,0,0,0,0,0,0,0,0xffffffff,
0xff000000,0xffffffff,0,0xffffffff,0,0,0,0,
0,0,0,0,0,0,0,0xffffffff,
0xffffffff,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,
0,0,0,0,
0,0,0,0,
0,0,0
 };

 unsigned	long*		KInput::_mousePointerBuffer = mousePattern ;

#define		JOYTOLERANCE		65500
//	joyID 0 = joystick numero 1
//	joyID 1 = joystick numero 2

/*
#define		BUTTON_A		JOY_BUTTON1
#define		BUTTON_B		JOY_BUTTON2
#define		ISDOWN			true
#define		ISUP					false
*/

BOOL CALLBACK   inputEnumeratorProc(   const DIDEVICEINSTANCE *lpddi,    void* pvRef   )  ;

unsigned	char				KInput::keystatetable[256] ;
short								KInput::_lastWheelValue ;



//constructeur
KInput::KInput( )
{
	joystick[0] = false ;
	joystick[1] = false ;
	_lastWheelValue = 0 ;
}


//destructeur
KInput::~KInput( )
{
	_lastWheelValue = 0 ;
}






//inits the input, joystick structures etc...
void		KInput::initInput( KWindow * kwindow) // , int screen_width, int screen_height  ) 
{
	_hwnd	=	kwindow->getWindowHandle(); // NULL;// hwnd ;
	_screen_width = (int)kwindow->getWindowWidth(); // screen_width;
	_screen_height = (int)kwindow->getWindowHeight(); //screen_height;
	initInputEx(_hwnd, _screen_width, _screen_height);
}

void		KInput::initInputEx( HWND		hwnd, int screen_width, int screen_height )
{
	_hwnd = hwnd;
	_screen_width = screen_width;
	_screen_height = screen_height;

	memset( keystatetable , 0 , 256 ) ;
	SetKeyboardState( (unsigned char*)&keystatetable ) ;
	hKL =  GetKeyboardLayout( 0 ) ;


OSVERSIONINFO versionInfo ;

	memset( &versionInfo , 0 , sizeof( OSVERSIONINFO ) ) ;
	
	versionInfo.dwOSVersionInfoSize =  sizeof( OSVERSIONINFO ) ;
	
 	if ( GetVersionEx( &versionInfo ) == false )
 	{
 		//couldn't get info, just assume it's false
	 	_is9x = true ;
	 	return ;
 	}
 	
 //POSVERSIONINFO lpVersionInfo // version information

	if ( versionInfo.dwPlatformId == VER_PLATFORM_WIN32_NT )
	{
		
		_is9x = false ;
	}
	else
	{
		_is9x = true ;
	
			long	i ;
			
			for ( i = 0 ; i < 20 ; i++ )
			{
				if ( KeyboardLayout[i].toucheID ==K_VK_L_SHIFT || KeyboardLayout[i].toucheID ==K_VK_R_SHIFT ) 
				{
					 KeyboardLayout[i].KeyCode = VK_SHIFT ;
				}

				if ( KeyboardLayout[i].toucheID ==K_VK_L_CONTROL || KeyboardLayout[i].toucheID ==K_VK_R_CONTROL ) 
				{
					 KeyboardLayout[i].KeyCode = VK_CONTROL ;
				}

			}
	}

}


//on attends que le joueur relache la touche en question
void		KInput::waitForKeyRelease( EKeyboardLayout keyCode )
{
	do
	{
	
	}while( isPressed( keyCode)  ) ;
}

//screen coordinates
void		KInput::mousePointerTo( long x , long y ) 
{
POINT		pt ;
	pt.x = x ;
	pt.y = y ;
	
	ClientToScreen(_hwnd ,  &pt );
	SetCursorPos( pt.x , pt.y ) ;
}

//touche du clavier ( creer une table de touches virtuelles pour le mac VK_XXXX -> equivalent pc )
bool		KInput::isPressed( EKeyboardLayout	keyCode ) 
{
short		k ;
long		realkeyCode  ;

 	realkeyCode = KeyboardLayout[keyCode].KeyCode ;

	//translation in  local  keyboard

//	answer  = MapVirtualKeyEx(  realkeyCode , 0 , hKL  ) ;
//	answer  = MapVirtualKeyEx(  answer , 1 , hKL  ) ;
//	k = GetAsyncKeyState( answer  ) ;

	k = GetAsyncKeyState( realkeyCode  ) ;
	
	k = k & 0x8000 ;
	
	if (  k != 0	)	return ISDOWN ;

	return ISUP ;
}

//returns a key given a wparam
EKeyboardLayout KInput::getPTKKey( long wparam ) 
{
long i ;
EKeyboardLayout ek ;
long		windowskey ;
		
		i = 0 ;
		do
		{
			ek = KeyboardLayout[i].toucheID ;
			windowskey = KeyboardLayout[i].KeyCode ;
			if ( wparam == windowskey )	return ek ;
			i++ ;
			
		}while( ek != K_VK_ERROR ) ;
		 
		return K_VK_ERROR ;
}

//souris , position et boutons
short		KInput::getMouseX( void ) 
{
POINT		pt	;


	GetCursorPos( &pt ) ;
	if ( _fullScreen == false )
	{
		ScreenToClient(  _hwnd , &pt  ) ;
	}
	return	(short)pt.x ;
}

// mouseY position
short		KInput::getMouseY( void ) 
{
POINT		pt	;

	GetCursorPos( &pt ) ;
	if ( _fullScreen == false )
	{
		ScreenToClient(  _hwnd , &pt  ) ;
	}
	
	return	(short)pt.y ;
}


bool		KInput::getLeftButtonState( void ) 
{
short		k ;

	
	k = GetAsyncKeyState( VK_LBUTTON  ) ;
	k = k & 0x8000 ;
	
	if (  k != 0	)	return ISDOWN ;
	
	return ISUP ;
}


bool		KInput::getRightButtonState( void ) 
{
short		k ;

	
	k = GetAsyncKeyState( VK_RBUTTON  ) ;
	k = k & 0x8000 ;
	
	if (  k != 0	)	return ISDOWN ;
	
	return ISUP ;
}

bool		KInput::getMiddleButtonState( void ) 
{
short		k ;

	
	k = GetAsyncKeyState( VK_MBUTTON  ) ;
	k = k & 0x8000 ;
	
	if (  k != 0	)	return ISDOWN ;
	
	return ISUP ;
}

//sets the last wheel value
void		KInput::setLastWheelValue( short	value )
{
	_lastWheelValue = value ;	
}

//reads the last wheel value
short		KInput::getWheelValue( void )
{
short	v ;

	v =  _lastWheelValue ;
	_lastWheelValue = 0 ;
	return v ;
	
}

//shot the cursor
void		KInput::showPointer( void ) 
{
	while ( ShowCursor( true ) < 0 ) { } 
}

//hide the cursor
void		KInput::hidePointer( void ) 
{
	while ( ShowCursor( false  ) >= 0 ) { }
}

//maintains the pointer inside the window
void		KInput::clipPointer( bool clipToWindow ) 
{
/*
POINT		p1,p2 ;
RECT		wr ;
*/
	if ( clipToWindow == false   )	
	{
		//on ne clip pas
		ClipCursor( NULL ) ;
		return ;
	}
	/*
	GetClientRect( gameWindow , &wr ) ;
	p1.x = 0 ;
	p1.y = 0 ;
	p2.x = wr.right ;
	p2.y = wr.bottom ;
	
	ClientToScreen( gameWindow , &p2 ) ;
	ClientToScreen( gameWindow , &p1 ) ;
	SetRect( &wr , p1.x , p1.y , p2.x,p2.y ) ;
	ClipCursor( &wr ) ;
*/
}
	



//function speciales joystick  //joyID = numero du joystick ( 0,1,2,3 )
//active le joystick
bool		KInput::joyEnable( char	joyID )
{
MMRESULT 		mmr ;

	joyDisable( joyID ) ;
	mmr = joySetCapture( _hwnd , joyID, NULL, FALSE) ;

	if ( mmr == JOYERR_NOERROR  )		joystick[joyID] = true ;

	return 	joystick[joyID]  ;		//return true si le joystick est present et a eté correctement acquis
}	

//desactive un joystick
void		KInput::joyDisable( char	joyID ) 
{
	//desactive le joy si il a ete activé auparavant
	if ( joystick[joyID] == true  )		joyReleaseCapture(  joyID ) ;

	joystick[joyID] = false ;

}
	
//detection de mouvement, retourne ISDOWN si le joy est dans la position indiquee
bool		KInput::joyLeft( char		joyID ) 
{
JOYINFO		ji ;

	//uniquement si le joy est actif !
	if ( joystick[joyID] == false )		return ISUP ;
	
	 joyGetPos(joyID , &ji ) ;
	 
	 if ( ji.wXpos  <= 10 )	return ISDOWN ;
	 
	 return ISUP ;
}
	
bool		KInput::joyRight( char		joyID ) 
{
JOYINFO		ji ;

	//uniquement si le joy est actif !
	if ( joystick[joyID] == false )		return ISUP ;
	
	 joyGetPos(joyID , &ji ) ;

	if ( ji.wXpos >JOYTOLERANCE )	return ISDOWN ;
	 
	 return ISUP ;
}

bool		KInput::joyUp( char		joyID ) 
{
JOYINFO		ji ;

	//uniquement si le joy est actif !
	if ( joystick[joyID] == false )		return ISUP ;

	 joyGetPos(joyID , &ji ) ;
	 
	 if ( ji.wYpos <=	10 )	return ISDOWN ;
	  return ISUP ;
}

bool		KInput::joyDown( char		joyID ) 
{
JOYINFO		ji ;

	//uniquement si le joy est actif !
	if ( joystick[joyID] == false )		return ISUP ;

	 joyGetPos(joyID , &ji ) ;
	 
	 if ( ji.wYpos  > JOYTOLERANCE )	return ISDOWN ;
	 return ISUP ;
}


long		KInput::joyY( char		joyID , char	hatID	 ) 
{
JOYINFOEX		ji ;

	//uniquement si le joy est actif !
	if ( joystick[joyID] == false )		return 32767 ;

	memset( &ji , 0 , sizeof( JOYINFOEX ) ) ;
	ji.dwSize 	= sizeof(	JOYINFOEX ) ;
	ji.dwFlags 	= JOY_RETURNALL ;
	
	 joyGetPosEx(joyID , &ji ) ;
	 
	 if ( hatID == 0 ) 	return ji.dwYpos ;
	 
	return ji.dwRpos  ;

}

long		KInput::joyX( char		joyID , char	hatID	 ) 
{
JOYINFOEX		ji ;

	//uniquement si le joy est actif !
	if ( joystick[joyID] == false )		return 32767 ;

	memset( &ji , 0 , sizeof( JOYINFOEX ) ) ;
	ji.dwSize 	= sizeof(	JOYINFOEX ) ;
	ji.dwFlags 	= JOY_RETURNALL ;
	
	 joyGetPosEx(joyID , &ji ) ;
	 
	 if ( hatID == 0 ) 	return ji.dwXpos ;
	 
	return ji.dwZpos  ;
}

long		KInput::joyPOV( char		joyID 	 ) 
{
JOYINFOEX		ji ;

	//uniquement si le joy est actif !
	if ( joystick[joyID] == false )		return 32767 ;

	memset( &ji , 0 , sizeof( JOYINFOEX ) ) ;
	ji.dwSize 	= sizeof(	JOYINFOEX ) ;
	ji.dwFlags 	= JOY_RETURNALL ;
	
	 joyGetPosEx(joyID , &ji ) ;
	 
	return ji.dwPOV  ;
}


void		KInput::joyWaitForJoyButtonUp( char		joyID , long		buttonID ) 
{
MSG		Msg ;

	do
	{
			if ( PeekMessage( &Msg, NULL, 0, 0 , PM_REMOVE ) )
				{
					TranslateMessage( &Msg );
					DispatchMessage( &Msg ); 
				}
	}while( joyButtonN( joyID , buttonID ) == ISDOWN ) ;

}

void		KInput::generateMouse( void )
{

	surf_mouse = KPTK::createKGraphic( ) ;
	surf_mouse->makePictureFromArray( _mousePointerBuffer+2 ,_mousePointerBuffer[0],_mousePointerBuffer[1] , false ) ;

}

void		KInput::setMousePointerBuffer( unsigned long *dataPtr )
{
	_mousePointerBuffer = dataPtr ;
}

void		KInput::freeMouse( void ) 
{
	PTK_FREEPTR( surf_mouse ) ;
}

void		KInput::displayMouse( void )
{
	if ( surf_mouse == NULL )		generateMouse( ) ;

	surf_mouse->blitAlphaRect( 0,0,16,16,KInput::getMouseX() ,KInput::getMouseY() ) ;
	
}

bool		KInput::joyButtonN( char		joyID , long		buttonID )
{
JOYINFOEX		ji ;

	if ( joystick[joyID] == false )		return ISUP ;

	memset( &ji , 0 , sizeof( JOYINFOEX ) );

	ji.dwSize  = sizeof( JOYINFOEX ) ;
	ji.dwFlags = JOY_RETURNBUTTONS ;

	//uniquement si le joy est actif !
	if ( joystick[joyID] == false )		return ISUP ;

	 joyGetPosEx(joyID , &ji ) ;
	 
	 if ( ji.dwButtons   & buttonID )	return ISDOWN ;
	 return ISUP ;
}