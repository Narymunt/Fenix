#include	"KIniReader.h"
#include "KResource.h"
#include	<stdlib.h>
#include	<string.h>
#include	<stdio.h>

//

#define		snprintf	_snprintf	

KIniReader::KIniReader( ) 
{
	memIni 			= 	NULL ;
	memIniLen	=	0 ;
}

KIniReader::~KIniReader( ) 
{
	if ( memIni )
	{
		delete	[] memIni ;
		memIni 			= 	NULL ;
		memIniLen	=	0 ;
	}
}


//creates an ini from memory
bool	KIniReader::setIni( char	*iniFile , long datalength) 
{

	strncpy( iniFilename ,  iniFile ,260 ) ;



	if ( memIni )
	{
		delete	[] memIni ;
		memIni 			= 	NULL ;
		memIniLen	=	0 ;
	}
			
	memIniLen =datalength ;

	
	
	memIni = new char[memIniLen + 1] ;
	if ( memIni == NULL )
	{	
		return false ;
	}
	
	memcpy(  memIni , iniFile , datalength ) ;
   memIni[memIniLen] = 0;
	
	
	return true ;
}


//returns true if the file exists, false if it does not
bool	KIniReader::setIni( char	*iniFile ) 
{
   KResource resIni;
   KResourceResult result;
   int integLen = 0;

	strcpy( iniFilename ,  iniFile ) ;



	if ( memIni )
	{
		delete	[] memIni ;
		memIni 			= 	NULL ;
		memIniLen	=	0 ;
	}
	
   result = resIni.open (iniFile, K_RES_READ);
   if (result != K_RES_OK)    return false ;
		
	resIni.seek(K_RES_END, 0) ;
	result = resIni.tell (integLen);
	if (( result != K_RES_OK) || ( integLen <= 0 ))
	{
		return false ;
	}
   memIniLen = integLen;
	
	resIni.seek(K_RES_BEGIN, 0) ;


	
	memIni = new char[memIniLen + 1] ;
	if ( memIni == NULL )
	{	
		return false ;
	}
	
	resIni.read (memIni, memIniLen );
   memIni[memIniLen] = 0;
	
	return true ;
}

long	KIniReader::getValue( char	*section , char 	*variable , long defaultValue) 
{
char		values[256] ;

	if ( memIni == NULL )		return 0 ;

	if ( getString( section , variable , values , 256 ) == false )		return defaultValue ;
	
	return	atol( values ) ;
	
}
	
//reads an ini like file.
bool	KIniReader::getString( char	*section , char 	*variable, char	*buffer,long	bufferlen ) 
{
char		*sectionPosition  ;
char		*variablePosition  ;

char		sectionName[256] ;
char		variableName[256] ;
long		endofline ;

char		*posstart, *posend ;

	if ( bufferlen<= 1 )		
	{
//		MessageBox( 0,"empty buffer",0,0 ) ;
		return false ;
	}
	
	memset( buffer , 0 , bufferlen ) ; 
	if ( memIni == NULL )		return false ;

	//first find the section
	snprintf( sectionName ,255, "[%s]" , section ) ;
    sectionName[255] = 0;

	sectionPosition = strstr( memIni , sectionName );
	posstart = sectionPosition ;

	if ( sectionPosition == NULL )	
	{
		return false ;
	}

	//try to locate the variable
	snprintf( variableName , 255 , "%s=" , variable ) ;
   variableName[255] = 0;
	variablePosition =  strstr( sectionPosition , variableName );	
	if ( variablePosition == NULL )		return false ;
	posend = variablePosition ;
	
	//check if there wasn't a new section between the variable and the section
	sectionPosition+=strlen(sectionName ) ;
	do
	{
		if  ( *posstart == 0x0d )
		{
			posstart++ ;
			if  ( *posstart == '[' )
			{
				return false ;
			}
		}

		if  ( *posstart == 0x0a )
		{
			posstart++ ;
			if  ( *posstart == '[' )
			{
				return false ;
			}
		}
		posstart++ ; 
			
	}while( posstart < posend ) ;
	
	
	variablePosition += strlen( variableName ) ;
	
	//find the end of the line
	endofline = 0 ;
	do
	{
		endofline++ ;
	}while( ( variablePosition[endofline] != 0x0d ) &&          ( variablePosition[endofline] ));

	if (  (bufferlen - 1) <= endofline ) 
	{
		endofline = bufferlen - 1 ;
	}
	
	memcpy( buffer , variablePosition  ,endofline ) ;
	buffer[endofline] = '\0' ;

	return true ;
}