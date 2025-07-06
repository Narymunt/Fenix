#include <stdio.h>
#include <io.h>

#include "KLog.h"

KLog::KLog(KLogFileType kLogFileType)
{
	_logFileType = kLogFileType;

	_logInfo  = false ;
	_logError = true  ;
	_logFatal = true  ;
	_logDebug = true  ;
	
	if ( _logFileType == kLogKeepFilesOpen )
	{
		_info  = fopen( "infos.log" , "wt");
		_error = fopen( "errors.log" , "wt" ) ;
		_fatal = fopen( "fatals.log" , "wt" ) ;
		_debug = fopen( "debug.log" , "wt" ) ;
	}
	else
	{
		_info  = NULL;
		_error = NULL;
		_fatal = NULL;
		_debug = NULL;
	}
}

KLog::~KLog()
{
	if ( _logFileType == kLogKeepFilesOpen )
	{
		fclose( _info ) ;
		fclose( _error ) ;
		fclose( _fatal ) ;
		fclose( _debug ) ;
	}
}

void  KLog::reset()
{
	unlink( "infos.log" ) ;
	unlink( "errors.log" ) ;
	unlink( "fatals.log" ) ;
	unlink( "debug.log" ) ;
}

void	KLog::logInfo( bool b )
{
	_logInfo = b ;
}

void	KLog::logError( bool b )
{
	_logError = b ;
}

void	KLog::logFatal( bool b )
{
	_logFatal = b ;
}

void	KLog::logDebug( bool b )
{
	_logDebug = b ;
}

void	KLog::logMessage( KLogType kLogType , const char *msg )
{
	if ( _logFileType == kLogKeepFilesOpen )
	{
		switch ( kLogType )
		{
			case kInfo  : 
				if ( true == _logInfo )
				{
					fprintf( _info , msg ) ; 
					fprintf( _info , "\n" ) ; 
				}
				break;
			case kError : 
				if ( true == _logError )
				{
					fprintf( _error , msg ) ; 
					fprintf( _error , "\n" ) ; 
				}
				break;
			case kFatal : 
				if ( true == _logFatal )
				{
					fprintf( _fatal , msg ) ; 
					fprintf( _fatal , "\n" ) ; 
				}
				break;
			case kDebug : 
				if ( true == _logDebug )
				{
					fprintf( _debug , msg ) ; 
					fprintf( _debug , "\n" ) ; 
				}
				break;
		}
	}
	else
	{
		switch ( kLogType )
		{
			case kInfo  : 
				if ( true == _logInfo )
				{
					_info  = fopen( "infos.log" , "a+");
					fprintf( _info , msg ) ;
					fprintf( _info , "\n" ) ; 
					fclose( _info ) ;
				}
				break;
				
			case kError : 
				if ( true == _logError )
				{
					_error = fopen( "errors.log" , "a+" ) ;
					fprintf( _error , msg ) ;
					fprintf( _error , "\n" ) ; 
					fclose( _error ) ;
				}
				break;
				
			case kFatal : 
				if ( true == _logFatal )
				{
					_fatal = fopen( "fatals.log" , "a+" ) ;
					fprintf( _fatal , msg ) ;
					fprintf( _debug , "\n" ) ; 
					fclose( _fatal ) ;
				}
				break;
				
			case kDebug : 
				if ( true == _logDebug )
				{
					_debug = fopen( "debug.log" , "a+" ) ;
					fprintf( _debug , msg ) ;
					fprintf( _debug , "\n" ) ; 
					fclose( _debug ) ;
				}
				break;
				
		}
	}
}