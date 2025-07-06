
#include	<string.h>
#include	<stdio.h>
#include	"KLog.h"
#include	"KMiscTools.h"
#include    <process.h>
#include	<stdio.h>
#include	<stdlib.h>
#include	<time.h>
#include	<process.h>
#include <sys/types.h>
#include <sys/stat.h>



#include	<shlobj.h>


#ifdef __MWERKS__
using namespace std ;
#endif

char	KMiscTools::currentFilePath[PTK_MAXPATH] = "" ;
LARGE_INTEGER	KMiscTools::_unitsPerSecond  ;
LARGE_INTEGER	KMiscTools::tstart;
LARGE_INTEGER	KMiscTools::tticks;
LARGE_INTEGER	KMiscTools::tnow;


unsigned long	KMiscTools::_millisecondCounter = 0 ;
unsigned long	KMiscTools::_starterMSTimer = 0 ;

void launchURL(void* parms) ;

KLog  KMiscTools::_kLog ;
int		KMiscTools::_HighFreq ;

KMiscTools::KMiscTools( ) 
{

}

KMiscTools::~KMiscTools( ) 
{

}



void		KMiscTools::initMiscTools( const char *appName ) 
{
long	i ;
		//recupere le path de l'exe
		GetModuleFileName( NULL , currentFilePath , PTK_MAXPATH ) ;
		
		i = strlen( currentFilePath ) ;
		while( i>0 )
		{
			if ( currentFilePath[i] == '\\' )	
			{	
				currentFilePath[i] = '\0' ;
				break ;
			}			
			i-- ;
		}
		
		initMillisecond( ) ;
		getYear( ) ;
}

char		*				KMiscTools::getCurrentPath( void ) 
{
static		char		builtPath[PTK_MAXPATH] ;

		if ( strcmp( currentFilePath , "" ) == 0 )			initMiscTools( NULL ) ;

		strcpy( builtPath ,  currentFilePath ) ;
		return builtPath ;
}

//make file path
char		*KMiscTools::makeFilePath( const	char	*filename ) 
{
static		char		builtPath[PTK_MAXPATH] ;
long			i =0 ;

	memset( builtPath , 0 , PTK_MAXPATH ) ;

	//check if it has been initialized before
	if ( strcmp( currentFilePath , "" ) == 0 )			initMiscTools( NULL ) ;
	
	//suprime le \ de debut si l'utilisateur en a mis un
	if ( filename[0] == '\\' || filename[0] == ':'  || filename[0] == '/' )	filename++ ;
		
	//ok we have a local path
	if ( filename[1] != ':' )
	{
		_snprintf( builtPath , PTK_MAXPATH , "%s\\%s" , 	currentFilePath , filename ) ;
	}
	else
	{
		_snprintf( builtPath , PTK_MAXPATH , "%s" , filename ) ;	
	}

		//pour mac, conversion de fichier en :
		i = strlen(builtPath ) ;
		if ( i > 0 ) 
		{
			for ( long index = 0 ; index <  i ; index++ ) 
			{
			//	if ( builtPath[index] == ':' )		builtPath[index] = '\\' ;
				if ( builtPath[index] == '/' )		builtPath[index] = '\\' ;
			}
		} 
	
	return	builtPath ;
}


char*	KMiscTools::getPreferencesFolder( void )
{
static	char	   szPath[PTK_MAXPATH];

 //   if (SHGetFolderPath(NULL, CSIDL_APPDATA|CSIDL_FLAG_CREATE , NULL , SHGFP_TYPE_CURRENT , szPath) == S_OK )
    if (SHGetSpecialFolderPath(NULL, szPath, CSIDL_APPDATA, TRUE) == true )
    {
	    	return szPath ;
    }
    
    return KMiscTools::makeFilePath( "" ) ;
}

char*	KMiscTools::getUserFolder( void )
{
static	char	   szPath[PTK_MAXPATH];

    if (SHGetSpecialFolderPath(NULL, szPath, CSIDL_PERSONAL , TRUE) == true )
    {
	    	return szPath ;
    }
    
    return KMiscTools::makeFilePath( "" ) ; 
}

void		KMiscTools::messageBox(const char *title, const char *text ) 
{
		//le getWindowHandle est requis pour que la boite soit devant la fenetre
//		MessageBox( KWindow::getWindowHandle() , text   , title ,  0 ) ;
		MessageBox( GetForegroundWindow() , text   , title ,  0 ) ;
}

void		KMiscTools::cleanPath( char		*texturePath ) 
{
long		i ;
long		index ;

		i  = strlen(texturePath )   ;
	
		if ( i < 0 )  return ; 
	
		for ( index = 0 ; index <  i ; index++ ) 
		{
			if ( texturePath[index] == '/' )		texturePath[index] = '\\' ;
		}

}

//retrieves the ms elapsed
unsigned	long	KMiscTools::getTheTicks( void )
{
	return	KMiscTools::getMilliseconds( ) ;
}


void		KMiscTools::pause( long	milliseconds , bool pollevents )
{
long		t  , t2;
MSG		Msg ;
	
	t2 = getMilliseconds( ) ;
	
	do
	{
			t = ( getMilliseconds( ) - t2)  ;
			
			//if ( t >  getMilliseconds( )  )	break ;
			if ( t < 0 )	break ;
						
			if ( pollevents == true ) 
			{
				if ( PeekMessage( &Msg, NULL, 0, 0 , PM_REMOVE ) )
				{
					TranslateMessage( &Msg );
					DispatchMessage( &Msg ); 
				}
			}
	}while( t < milliseconds ) ;		//pause n secondes		

}

long		KMiscTools::getYear( void )
{
	tm 	*newtime ;
	time_t		 aclock;

char			datestr[256] ;
char			*yearPtr ;

	time( &aclock );                 /* Get time in seconds */
	newtime = localtime( &aclock );  /* Convert time to struct */
	strncpy( datestr , asctime( newtime ) , 256 ) ;


                                  
   /* Print local time as a string */

	yearPtr = datestr+(strlen( datestr ) -5) ;

    return atol( yearPtr ) ;
   
}
void		KMiscTools::initMillisecond( void )
{

	_HighFreq=  QueryPerformanceFrequency(	&_unitsPerSecond ) ;
	 
	 _starterMSTimer = getRawMilliseconds( ) ;
	 	
//	 unitsPerSecond = N unités par secondes
}


void	KMiscTools::freezeTimer( void )
{
	_starterMSTimer = getRawMilliseconds( ) ;
}

unsigned long		KMiscTools::getRawMilliseconds( void )
{
unsigned long		curms ;

	if( _HighFreq )
	{
		QueryPerformanceCounter( &tnow );
		curms =  (unsigned long	)(((tnow.QuadPart - tstart.QuadPart) * 1000) / _unitsPerSecond.QuadPart);
	}	
	else
	{
		tnow.LowPart = timeGetTime();
		if(tnow.LowPart < tstart.LowPart)
		{	//Oops, millisecond rollover.
			curms =  (unsigned long	)(((tnow.LowPart + (0xffffffff - tstart.LowPart)) * 1000) / 1000);
		}
		else
		{
			curms =  (unsigned long	)(((tnow.LowPart - tstart.LowPart) * 1000) / 1000);
		}
	}
	
	

	return curms ;
	
}

unsigned long		KMiscTools::getMilliseconds( void )
{
unsigned long		curms , _delta ;

	if( _HighFreq )
	{
		QueryPerformanceCounter( &tnow );
		curms =  (unsigned long	)(((tnow.QuadPart - tstart.QuadPart) * 1000) / _unitsPerSecond.QuadPart);
	}	
	else
	{
		tnow.LowPart = timeGetTime();
		if(tnow.LowPart < tstart.LowPart)
		{	//Oops, millisecond rollover.
			curms =  (unsigned long	)(((tnow.LowPart + (0xffffffff - tstart.LowPart)) * 1000) / 1000);
		}
		else
		{
			curms =  (unsigned long	)(((tnow.LowPart - tstart.LowPart) * 1000) / 1000);
		}
	}
	
	_delta = (curms-_starterMSTimer) ;
	_millisecondCounter += _delta ;
	_starterMSTimer = curms ;

	return _millisecondCounter ;
	
}

struct URLParms
{
    char url[2048];
    bool maximised;
};

void launchURL(void* parms)
{
    URLParms* url = (URLParms*)parms;
    
    if ( url->maximised == true )
    {	
        ShellExecute( 0 ,"open" ,url->url ,0,0,SW_SHOWMAXIMIZED ) ;
    }
    else
    {
        ShellExecute( 0 ,"open" ,url->url ,0,0,SW_SHOWNORMAL ) ;
    }
    delete url;    

}


void		KMiscTools::setFileSource( bool vall ) 
{
	vall = vall ;
}


//launches a URL in the default browser
void		KMiscTools::launchURL( char	*url ,bool maximised  )
{
char		buffer[1024] ;

sprintf(buffer,"url.dll,FileProtocolHandler %s",url);

if ( maximised == true )
{
	ShellExecute(NULL, "open", "rundll32.exe", buffer,NULL,SW_MAXIMIZE);
}
else
{
	ShellExecute(NULL, "open", "rundll32.exe", buffer,NULL,SW_SHOWNORMAL);

}
/*   if ( maximised == true )
    {	
        ShellExecute( 0 ,"open" ,url ,0,0,SW_SHOWMAXIMIZED ) ;
    }
    else
    {
        ShellExecute( 0 ,"open" ,url ,0,0,SW_SHOWNORMAL ) ;
    }
   */ 
}

//launches a file
void		KMiscTools::launchFile( char	*url ,bool maximised  )
{
char		buffer[1024] ;

sprintf(buffer,"url.dll,FileProtocolHandler %s",url);

if ( maximised == true )
{
	ShellExecute(NULL, "open", "rundll32.exe", buffer,NULL,SW_MAXIMIZE);
}
else
{
	ShellExecute(NULL, "open", "rundll32.exe", buffer,NULL,SW_SHOWNORMAL);

}
/*
   if ( maximised == true )
    {	
        ShellExecute( 0 ,"open" ,url ,0,0,SW_SHOWMAXIMIZED ) ;
    }
    else
    {
        ShellExecute( 0 ,"open" ,url ,0,0,SW_SHOWNORMAL ) ;
    }
	*/
}


void    KMiscTools::logMessage( KLogType kLogType , const char* msg )
{
	_kLog.logMessage( kLogType , msg ) ;
}

long	KMiscTools::flipLong( long value )
{
	return value ;
}

short		KMiscTools::flipShort( short value )
{
	return value ;
}

char		*KMiscTools::getLocale( void )
{
static	char		localeLanguage[300] ;
static	char		localeCountry[300] ;

//	hKL =  GetKeyboardLayout( 0 ) ;
	 GetLocaleInfo(		LOCALE_USER_DEFAULT ,
	 							LOCALE_SISO639LANGNAME     , 
	 							localeLanguage ,
	 							300 ) ;

	strcpy(localeCountry ,  localeLanguage  ) ;
	strupr( localeCountry ) ;

	strcat( localeLanguage , "_" ) ;
	strcat( localeLanguage , localeCountry ) ;
	

	return	localeLanguage ;
}

float		KMiscTools::flipFloat( float value ) 
{
	return value ;
}

//enumerates a folder
void		KMiscTools::enumerateFolder( char 	*folderpath , enumProc		enumerationProcPtr , void *userData )
{
	if ( folderpath == NULL ) 					return ;
	if ( enumerationProcPtr == NULL ) 	return ;

HANDLE					hf ;
WIN32_FIND_DATA findFileData ;

	memset( &findFileData , 0 , sizeof( WIN32_FIND_DATA  ) ) ;

	hf =  FindFirstFile( folderpath , &findFileData ) ;

	if ( hf == INVALID_HANDLE_VALUE )		return ;

	if ( enumerationProcPtr( findFileData.cFileName , findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY , userData   ) == false )
	{
		FindClose( hf ) ;
		return ;
	}
	
	while	( FindNextFile( hf , &findFileData ) != false )
	{
		if ( enumerationProcPtr( findFileData.cFileName ,  findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY , userData  ) == false )
		{
			FindClose( hf ) ;
			return ;
		}
	}



	FindClose( hf ) ;

}

bool		KMiscTools::createDirectory( const char *folderpath ) 
{

	return	CreateDirectory( folderpath , NULL ) ;
}	

bool		KMiscTools::fileExists( const char *filepath )
{
struct	stat buf ;
int			result ;

		result = stat( filepath , &buf ) ;
		
		if ( result == 0 )	return true ;
		
		return false ;
	
}
	
/*
bool XDir::MatchesMask(const string& itemName) 
{ 
    if (m_mask != "" && m_mask != "*") 
    { 
        int maskStarPos = m_mask.find('*', 0); 
        string postStar = ""; 
        string preStar = ""; 
         
        if (maskStarPos < m_mask.length() - 1) 
        { 
            postStar = m_mask.substr(maskStarPos + 1, m_mask.length() - (maskStarPos + 1)); 
        } 
        if (maskStarPos > 0) 
        { 
            preStar = m_mask.substr(0, maskStarPos); 
        } 
        if (preStar != "") 
        { 
            if (itemName.find(preStar, 0) != 0) 
            { 
                return false; 
            } 
        } 
        if (postStar != "") 
        { 
            if (itemName.rfind(postStar,itemName.length()) != itemName.length() - postStar.length()) 
            { 
                return false; 
            } 
        } 
    } 
    return true; 
 
} 
#endif
*/
