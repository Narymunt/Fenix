#include		"KWeb.h"
#include		"KMiscTools.h"


KWeb::KWeb( ) 
{
	hInternet = 0 ;		//handle internet
	hIurl	= 0 ;
	_dataBuffer = NULL ;
	_dataBufferSize = 0 ;
}
	
KWeb::~KWeb( ) 
{
	freeInternetHandles( ) ;
	freeDataBuffer( ) ;
}


char	*		KWeb::callURL( char	*paramURL , bool 	asynchronous ) 
{
unsigned long ulconnect = 0 ;

		//are we connected ?
		if ( InternetAttemptConnect( 0 ) != ERROR_SUCCESS  )			return  	NULL;
		if (  InternetGetConnectedState(    &ulconnect , 0 ) == false )		return 	NULL ;
	
		
		//yes, so let's work!
		return openURL( 	paramURL , asynchronous ) ;
}

void		KWeb::freeDataBuffer( void ) 
{
	if ( _dataBuffer != NULL )
	{
		delete	[]	_dataBuffer ;
		_dataBuffer 		= NULL ;
		_dataBufferSize 	= 0 ;
	}
}


unsigned long		KWeb::getBufferSize( void ) 
{
	return	_dataBufferSize ;
}

//do the url dance	
char*		KWeb::openURL( char	*paramURL , bool 	asynchronous ) 
{
unsigned long		asyncState =	WININET_API_FLAG_SYNC  ;
unsigned long 	bytesToRead , bytesRead , writeHead , ctx = 0 , urllen ;
char		strURL[PTK_MAXPATH*2] ;

		freeInternetHandles( ) ;
		freeDataBuffer( ) ;
	
		if ( asynchronous == true )	{	asyncState =	WININET_API_FLAG_ASYNC ;	}
		
		hInternet =  InternetOpen( 	"PTK - http://www.phelios.com" , 
												INTERNET_OPEN_TYPE_PRECONFIG ,
												NULL ,	//lpszProxyName
												NULL ,	//lpszProxyBypass
												asyncState ) ;
	
		//could not connect
		if ( hInternet == NULL )	{	return NULL ;	}
		
		//transform the url in %20 style
		urllen = (PTK_MAXPATH *2) -1 ;
		memset( strURL , 0 , PTK_MAXPATH*2 ) ;
		
		if ( InternetCanonicalizeUrl( paramURL , strURL , &urllen ,ICU_BROWSER_MODE ) == false )
		{
			//failed to encode the url
			strcpy( strURL  , paramURL ) ;
		}

		hIurl =  InternetOpenUrl( 	hInternet , 
												(const char*)strURL , 
												0  ,
												0 ,
												INTERNET_FLAG_RELOAD  , ctx ) ;
												
		if ( hIurl	== NULL )			return NULL ;							

		
char	 *dataBuffer2 = NULL ;;	
unsigned long	bufferSize = 16384		 ;

		//buffer de 16ko
		_dataBuffer = new		char[bufferSize] ;
		memset( _dataBuffer , 0 , bufferSize ) ;
		
		writeHead = 0 ;
		
		do
		{
			bytesToRead	= 256 ;
			if ( InternetReadFile( hIurl , _dataBuffer+writeHead , bytesToRead , &bytesRead ) == false )
			{
				//and error occured
				break ;
			}

			if ( bytesRead ==  0 )		break ;		//transfer is finished
			//move the seeking head
			writeHead += bytesRead ;

			//check for possible memory overwrite
			if ( (writeHead+256) >= bufferSize )
			{
				//not enough space in buffer, realloc it.
				dataBuffer2 = new char[bufferSize*2] ;
				memset( dataBuffer2 , 0 , bufferSize*2 ) ;
				memcpy( dataBuffer2 , _dataBuffer , bufferSize ) ;

				bufferSize *= 2 ;

				delete [] _dataBuffer ;				
				_dataBuffer = new char[bufferSize] ;
				memcpy( _dataBuffer , dataBuffer2 , bufferSize ) ;
				delete [] dataBuffer2 ;
				dataBuffer2 = NULL ;

			}	
		  
		}while( true ) ;
		
		_dataBufferSize = writeHead ;
		_dataBuffer[_dataBufferSize] = '\0' ;
		
		freeInternetHandles( ) ;

		return _dataBuffer ;
}

void	KWeb::freeInternetHandles( void ) 
{
		if ( hIurl != NULL )
	{
		 InternetCloseHandle( hIurl ) ;
		 hIurl = 0 ; 
	}
	
	if ( hInternet != NULL )
	{
		 InternetCloseHandle( hInternet ) ;
		 hInternet = 0 ; 
	}
}