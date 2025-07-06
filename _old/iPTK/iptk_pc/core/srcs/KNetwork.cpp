#include <stdio.h>
#include <stdlib.h>

#include <winsock.h>
//#define	_snprintf		snprintf

#include "KNetwork.h"

static const char *kIPConfigAddressTag = "IPaddr";  // KLUDGE:  Tags stolen from NetModuleIP.h, 
static const char *kIPConfigPortTag    = "IPport";  // module_config.c, etc. -  See comments in 
static const char *kTypeTag            = "type";    // Open_Connection() below. Tags used to 
static const char *kVersionTag         = "version"; // manually build config string when necessary.
static const char *kGameIDTag          = "gameID";
static const char *kGameNameTag        = "gameName";
static const char *kModeTag            = "mode";


void OpenPlay_Callback( PEndpointRef inEndpoint, void* callbackData, NMCallbackCode inCode, NMErr inError, void* inCookie )
{
	KNetwork *pkNetwork = (KNetwork *)callbackData ;
	
//	#pragma unused( inEndpoint )
//	#pragma unused( inError )

	if ( pkNetwork == NULL )
	{
		MessageBox ( 0 , "Problem, pkNetwork == NULL !" , "OpenPlay_Callback" ,0 ) ;
		return ;
	}


	switch( inCode ) 
	{
		case kNMConnectRequest:
			pkNetwork -> accept( inCookie );
			break;

		case kNMDatagramData:
			pkNetwork -> recvDatagramMessage( ) ;
			break;
			
		case kNMStreamData:
			pkNetwork -> recvStreamMessage( ) ;
			break;

		case kNMFlowClear:
			printf("OpenPlay Callback : kNMFlowClear\n");
			break;

		case kNMAcceptComplete:
			pkNetwork -> setClientEndPoint( inEndpoint ) ;
			break;

		case kNMHandoffComplete:
			printf("OpenPlay Callback : kNMHandoffComplete\n");
			break;

		case kNMEndpointDied:
			printf("OpenPlay Callback : kNMEndpointDied\n");
			pkNetwork -> endPointDied( inEndpoint );
			break;

		case kNMCloseComplete:
			printf("OpenPlay Callback : kNMCloseComplete\n");
			break;

		default:
			break;
	}
	
	return;
}

//--- publics
KNetwork::KNetwork( KProtocolType kProtocolType, int gameId, const char *pcGameName,const char *hostName,int port,bool bServerMode, long packetSize, int stackSize )
{
	char       infoStr[ 1024 ];
	short      configStrLen = 0;
	NMBoolean  result = false;
	NMErr      err = 0;
	char       configStr[ 1024 ];
 
	_pkDataExchange = new KDataExchange( stackSize ) ;
	memset( configStr, 0, sizeof( configStr ) );
	memset( _hosts , 0 , sizeof( _hosts ) ) ;
	_hostsCount = 0 ;
	_status[ 0 ] = '\0' ;
	
	_packetSize = packetSize ;
	
	_pClient = NULL ;
	_pSocket = NULL ;
	
	_kProtocolType = kProtocolType ;

	_bServerMode = bServerMode ;
	
	if ( kProtocolType == K_TCP ) 
	{
		sprintf( configStr, "%s=%u\t%s=%u\t%s=%u\t%s=%s\t%s=%u\t%s=%s\t%s=%u", 
		              kTypeTag, kTCP_ProtoTag,
		              kVersionTag, 0x00000100,
		              kGameIDTag, gameId,
		              kGameNameTag, pcGameName,
		              kModeTag, 3,
		              kIPConfigAddressTag, hostName,
		              kIPConfigPortTag, port );
	}

	// OpenPlay API
	err = ProtocolCreateConfig(   kTCP_ProtoTag,    // Which protocol to use (TCP/IP, Appletalk, etc.)
	                              gameId,           // 'Key' to find same game type on network.
	                              pcGameName,       // 'Key' to a particular game of that type.
	                              NULL, 
	                              0, 
	                              configStr, 
	                            & _configuration    // Retrieve your config info with this critter.
	                          );
	printf("KNetwork::KNetwork --> ProtocolCreateConfig : %d\n" , err ) ;
	// OpenPlay API
	ProtocolGetConfigStringLen( _configuration, &configStrLen );
	
	// OpenPlay API
	ProtocolGetConfigString( _configuration, infoStr, sizeof(infoStr) );
	
	printf( "\nConfig Info:  %s\n", infoStr );
	fflush(stdout);

	if (  err >= 0 ) 
	{
		if ( true == bServerMode )
		{
			err = ProtocolOpenEndpoint(   _configuration, 
			                            	OpenPlay_Callback, 
			                            	this, 
			                            &	_pSocket, 
			                            	(NMOpenFlags)false );
			printf("KNetwork::KNetwork (ServerMode) --> ProtocolOpenEndpoint : %d\n" , err ) ;
		}
		else
		{
			err = ProtocolOpenEndpoint(   _configuration, 
			                            	OpenPlay_Callback, 
			                            	this, 
			                            &	_pSocket, 
			                            	(NMOpenFlags)true );
			printf("KNetwork::KNetwork (ClientMode) --> ProtocolOpenEndpoint : %d\n" , err ) ;
		}
	}
	
	if (  err >= 0 ) 
	{
		_bInitOk = true ;
	}
	else 
	{
		_bInitOk = false ;
	}

}

KNetwork::~KNetwork( ) 
{
	disconnect();
	
	delete _pkDataExchange ;
}

bool KNetwork::isServer()
{
	return _bServerMode ;
}

bool KNetwork::isClientConnected()
{
	if ( true == _bServerMode )
	{
		if ( _pClient != NULL )
		{
			return true ;
		}
	}
	return false ;
}

bool KNetwork::isServerConnected()
{
	if ( false == _bServerMode )
	{
		if ( _pSocket != NULL )
		{
			return true ;
		}
	}
	return false ;
}
void KNetwork::disconnect()
{

	if ( NULL != _pClient )
	{
		printf("Disconnect Client\n");
		ProtocolCloseEndpoint( _pClient , true ) ;
		_pClient = NULL ;
	}
	
	if ( NULL != _pSocket )
	{
		printf("Disconnect Server\n");
		ProtocolCloseEndpoint( _pSocket , true ) ;
		_pSocket = NULL ;
	}
	
}

bool				KNetwork::sendDatagramMessage( short messageLen, const char * bytes , char *errorMsg ) 
{
	NMErr      err = 0;
	bool       bRet = true ;
	unsigned long ulToSend = messageLen ;

	if ( ((true  == _bServerMode) && (NULL == _pClient)) ||
	     ((false == _bServerMode) && (NULL == _pSocket)) )
	{
		strcpy( errorMsg , "You are not connected, you can not send any bytes" );
		return false;
	}

	if ( K_TCP == _kProtocolType )
	{
		if ( messageLen > 1500 )
		{
			bRet = false ;
			if ( NULL != errorMsg )
			{
				strcpy( errorMsg , "For TCP datagram max length is 1500 bytes" );
			}
		}
	}
	else if ( K_APL == _kProtocolType )
	{
		if ( messageLen > 576 )
		{
			bRet = false ;
			if ( NULL != errorMsg )
			{
				strcpy( errorMsg , "For AppleTalk datagram max length is 576 bytes" );
			}
		}
	}

	if ( true == bRet )
	{
		if ( NULL != _pClient )
		{
			err = ProtocolSendPacket( _pClient , (void*) bytes , (long)messageLen , 0 ) ;
		}
		else
		{
			err = ProtocolSendPacket( _pSocket , (void*) bytes , (long)messageLen , 0 ) ;
		}
		if ( err < 0 )
		{
			bRet = false ;
			if ( NULL != errorMsg )
			{
				sprintf( errorMsg , "OpenPlay ProtocolSendPacket Error : %d" , err ) ;
			}
		}
	}
	
	return bRet ;
}

bool				KNetwork::recvDatagramMessage( char *errorMsg ) 
{
	unsigned long ulToRead = 1500 ;
	unsigned long ulNbRead = ulToRead ;
	unsigned long ul = sizeof(ulToRead);
	NMErr      		err = 0;
	bool       		bRet = true ;
	NMFlags 			flags;
	char					bytes[ 1500 ] ;

	if ( K_TCP == _kProtocolType )
	{
		if ( ulToRead > 1500 )
		{
			bRet = false ;
			if ( NULL != errorMsg )
			{
				strcpy( errorMsg , "For TCP datagram max length is 1500 bytes" );
			}
		}
	}
	else if ( K_APL == _kProtocolType )
	{
		if ( ulToRead > 576 )
		{
			bRet = false ;
			if ( NULL != errorMsg )
			{
				strcpy( errorMsg , "For AppleTalk datagram max length is 576 bytes" );
			}
		}
	}

	if ( true == bRet )
	{
		if ( NULL != _pClient )
		{
			err = ProtocolReceivePacket( _pClient , (void*)bytes , & ulNbRead , & flags ) ;
		}
		else
		{
			err = ProtocolReceivePacket( _pSocket , (void*)bytes , & ulNbRead , & flags ) ;
		}
		if ( err < 0 )
		{
			bRet = false ;
			if ( NULL != errorMsg )
			{
				sprintf( errorMsg , "OpenPlay ProtocolReceivePacket Error : %d" , err ) ;
			}
		}
		else
		{
			KDataItem * kDataItem = new KDataItem( kCopyData );
			kDataItem -> set( kUdp , bytes , ulNbRead ) ;
			_pkDataExchange -> push( kDataItem ) ;
		}
	}
	
	return bRet ;
}

//envoie un stream
bool				KNetwork::sendStreamMessage( const char * bytes , char *errorMsg ) 
{
//	#pragma unused( errorMsg )
	long	sentBytes = 0 ;
	
	if ( ((true  == _bServerMode) && (NULL == _pClient)) ||
	     ((false == _bServerMode) && (NULL == _pSocket)) )
	{
		strcpy( errorMsg , "You are not connected, you can not send any bytes" );
		return false;
	}
	
	if ( NULL != _pClient )
	{
		if (bytes != NULL && _packetSize>0 )
		{
			sentBytes = ProtocolSend( _pClient, (void*)bytes, _packetSize, 0 ) ;
		}
	}
	else
	{
		if ( _pSocket != NULL && bytes != NULL && _packetSize>0 )
		{
			sentBytes = ProtocolSend( _pSocket, (void*)bytes, _packetSize, 0 ) ;
		}
	}
	
	if ( sentBytes <= 0 )		return false ;
	return true ;
}

//recois un stream
bool				KNetwork::recvStreamMessage( char *errorMsg ) 
{
	NMFlags 			flags;
	NMErr      			err = 0;
	unsigned long 	l = sizeof(l);
	unsigned long 	ulNbRead = _packetSize ;
	char			*		bytes = NULL ;
	
	unsigned long		ulTotalRead = 0L ;
	unsigned long		indexRead = 0 ;
	
	if ( NULL != _pClient )
	{
		if ( _pClient != NULL )
		{
			bytes = new char[ _packetSize ] ;
				
			indexRead = 0 ;
			ulNbRead = _packetSize ;
			do
			{
				ulNbRead = ( _packetSize-indexRead ) ;
				if ( ulNbRead <= 0 )					break ;
				if ( indexRead >= _packetSize )	break ;
				
				err = ProtocolReceive( _pClient , (void*) (bytes+ indexRead) , & ulNbRead , & flags ) ;
				indexRead += ulNbRead ;
				
				if ( indexRead >= _packetSize )		{			break ; 		}
				if ( err != 0 )	 {			 	break ;	 }
				
			}while( true ) ;

		}
	}
	else
	{
		if ( _pSocket != NULL )
		{
			bytes = new char[ _packetSize ] ;
				
			indexRead = 0 ;
			ulNbRead = _packetSize ;
			do
			{
				ulNbRead = ( _packetSize-indexRead ) ;
				if ( ulNbRead <= 0 )					break ;
				if ( indexRead >= _packetSize )	break ;
				
				err = ProtocolReceive( _pSocket , (void*) (bytes+ indexRead) , & ulNbRead , & flags ) ;
				indexRead += ulNbRead ;
				
				if ( indexRead >= _packetSize )		{			break ; 		}
				if ( err != 0 )	 {			 	break ;	 }
				
			}while( true ) ;
			
		//	bytes = new char[ _packetSize ] ;
		//	err = ProtocolReceive( _pSocket , (void*) bytes, & ulNbRead , & flags ) ;
		}
	}



	//erreur de reception ?
	if ( err < 0 )
	{
		if ( bytes != NULL )
		{
			delete[] bytes ;
			bytes = NULL ;
		}
		
		if ( NULL != errorMsg )
		{
			sprintf( errorMsg , "OpenPlay ProtocolReceive Error : %d" , err ) ;
		}
		return false ;
	}



	//le buffer de reception n'a pu etre alloué
	if ( bytes == NULL )		{ return false; }

	KDataItem * kDataItem = new KDataItem( kCopyData );

	if ( kDataItem == NULL )
	{
		delete[] bytes ;
		bytes = NULL ;
		return false ;
	}
	
	kDataItem -> set( kTcp , bytes , ulNbRead ) ;
	_pkDataExchange -> push( kDataItem ) ;

	
	delete[] bytes ;
	bytes = NULL ;
	
	return true ;
}

void				KNetwork::setTimetout( long timeout ) 
{
	_timeout = timeout ;
}

long				KNetwork::getTimeout() 
{
	return _timeout ;
}

bool				KNetwork::isInitOk() 
{
	return _bInitOk ;
}

const char* KNetwork::getErrorMessage()
{
	return _error ;
}

void				KNetwork::displayStatus()
{
	printf( "%s\n" , _status ) ;
}

void				KNetwork::accept( void* inCookie )
{
	NMErr err;

	err = ProtocolAcceptConnection( _pSocket, inCookie, OpenPlay_Callback, this );

	printf("KNetwork::accept --> ProtocolAcceptConnection : %d\n" , err ) ;
	if ( err >= 0 ) 
	{
		printf( "Accepting connection...\n" );
		fflush(stdout);
	} 
	else 
	{
		printf( "ERROR: %d Failed connection request!\n", err );
		fflush(stdout);
	}
}

bool				KNetwork::getLastNetworkMessageType( KPacketType *pkPacketType )
{
	KDataItem * pkDataItem = (KDataItem *)_pkDataExchange -> peek() ;
	bool   bRet = false ;
	
	if ( NULL != pkDataItem )
	{
		(*pkPacketType) = pkDataItem -> getPacketType() ;
		bRet = true ;
	}
	return bRet ;
}

void	KNetwork::getLastNetworkMessage( KDataItem & rDataItem )
{
	KDataItem * pkDataItem = (KDataItem *)_pkDataExchange -> pop() ;
	
	rDataItem = (*pkDataItem) ; // operator =
	delete pkDataItem ; // delete pushed datas
}

//--- protected
void				KNetwork::setClientEndPoint( PEndpointRef pEndPoint )
{
	_pClient = pEndPoint ;
}

void				KNetwork::endPointDied( PEndpointRef deadEndPoint )
{
	printf("_pClient(%X), _pSocket(%X), deadEndPoint(%X)\n",_pClient, _pSocket, deadEndPoint ) ;
	if ( deadEndPoint == _pClient )
	{
		ProtocolCloseEndpoint( _pClient , true ) ;		
		_pClient = NULL ;
	}
	else if ( deadEndPoint == _pSocket )
	{
		ProtocolCloseEndpoint( _pSocket , true ) ;		
		_pSocket = NULL ;
	}
}

//PATRICE K implementation pour les Nuls
bool				KNetwork::getTCPData( void*	buffer )
{
	KDataItem			kDataItem( kCopyData ) ;
	char					*dataPtr ;
	
	//taille de paquet a 0 
	if ( _packetSize <= 0  )	return false ;
	
	getLastNetworkMessage( kDataItem ) ;

	dataPtr = (char*)kDataItem . get() ;
	if ( dataPtr == NULL )	return false ;
	
	memcpy( buffer , dataPtr , _packetSize ) ;

	return true ;
}

unsigned	long				KNetwork::getUDPDataSize( void )
{
	KDataItem * pkDataItem = (KDataItem *)_pkDataExchange -> peek() ;
	
	return ( pkDataItem -> getSize() + 1 ) ;
}

//lit des donnees udp
bool				KNetwork::getUDPData( char*	buffer , unsigned long	buffersize)
{
	KDataItem			kDataItem( kCopyData ) ;
	char		*dataPtr ;

	if ( buffer == NULL )		return false ;

	getLastNetworkMessage( kDataItem ) ;
	
	dataPtr = 	(char*)(kDataItem . get( ) ) ;
	memcpy( 	buffer , dataPtr , 	( buffersize-1 ) ) ;
	buffer[buffersize] = '\0' ;
	
	return true ;
}

bool				KNetwork::getIpAddress( char *ipAddress )
{
	WORD 			wVersionRequested;
	WSADATA 	wsaData;
	int err;

	wVersionRequested = MAKEWORD( 1, 1 );

	err = WSAStartup( wVersionRequested, &wsaData );
	if ( err != 0 )
	{
		return false;
	}

	if ( LOBYTE( wsaData.wVersion ) != 1 ||  HIBYTE( wsaData.wVersion ) != 1 )
	{
		WSACleanup( );
		return false ;
	}

	char hostName[256];
	memset( hostName , 0 , 256 ) ;
	if (gethostname( hostName, sizeof(hostName) ) == SOCKET_ERROR)
	{
		WSACleanup( );
		return false ;
	}

//	MessageBox( 0,hostName,0,0 ) ;

	//gethostbyname function retrieves host information corresponding to a host name from a host database.
	hostent *phe = gethostbyname( hostName );

	if (phe == NULL )
	{
		WSACleanup( );
		return false ;
	}

	for (int i = 0; phe->h_addr_list[i] != 0; ++i)
	{
		struct in_addr addr;
		memcpy(&addr, phe->h_addr_list[i], sizeof(struct in_addr));
		_snprintf( ipAddress , 256,"%s",  inet_ntoa(addr) ) ;
	}
//	MessageBox( 0,ipAddress,0,0 ) ;

	WSACleanup( );

	return true;
}
