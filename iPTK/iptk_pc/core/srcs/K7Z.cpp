#include	"K7Z.h"
#include	"LzmaDecode.h"
#include	<string.h>
#include	<stdio.h>
#include	<stdlib.h>




K7Z::K7Z( ) 
{
	dataPtr = NULL ;
	_dataSize = 0 ;
	inStream = NULL ;
	lzmaInternalData = NULL  ;
	strcpy( _k7zError , "" ) ;
}

K7Z::~K7Z( ) 
{
	release( ) ;
}


char		*K7Z::getLastError( void ) 
{
	return _k7zError ;
}	

//depack a file to disk
bool		K7Z::depack( char *sourceFileName , char *destFileName ) 
{
	if ( depackFile( sourceFileName ) == false )		return false ;

	if ( _dataSize <= 0 || dataPtr == NULL )	
	{
		sprintf( _k7zError , "No data to write" ) ;
		return false ;
	}

FILE	*f ;

	f = fopen( destFileName , "wb" ) ;
	if ( f == NULL )		
	{
		sprintf( _k7zError , "can't open destination file" ) ;
		return false ;
	}	
	
	fwrite( dataPtr , 1 , _dataSize ,f ) ;
	fclose( f ) ;
	
	return true ;

}


//returns NULL if failed
unsigned	char*	K7Z::load(  char *fileName , unsigned long *buffersize ) 
{
	if ( buffersize != NULL )	{	*buffersize = _dataSize ; 	}

	if ( depackFile( fileName ) == false )		return NULL ;
		
	return dataPtr ;
}

void		K7Z::release( void )
{
	freeInternalMemory( ) ;
	if ( dataPtr != NULL )
	{
		delete	[] dataPtr ;
		dataPtr = NULL ;
	}
	_dataSize = 0 ;
}



 // LZMA Decoder 4.01 Copyright (c) 2001-2003 Igor Pavlov  2004-02-15\n");

//this is the LZMA decoder SDK example, fixed for codewarrior.

bool		  K7Z::depackFile( char *filename )
{
  FILE 				*inputHandle ;
  unsigned int 	length;
  unsigned int 	compressedSize, outSizeProcessed, lzmaInternalSize;
  long					outSize ;
  unsigned char 	properties[5];
  unsigned char 	prop0;
  int 					ii;
  int 					lc, lp, pb;
  int 					res;


  release( ) ;


  inputHandle = fopen( filename , "rb");
  if (inputHandle == 0)
  {
	strcpy(_k7zError , "Impossible to open File" ) ;
    return false ;
  }

  //gets the filesize of the file to depack
  fseek(inputHandle, 0, SEEK_END);
  length = ftell(inputHandle);
  fseek(inputHandle, 0, SEEK_SET);

	//properties of an lzma = 5 char	// unsigned char properties[5];
  if ( fread (  properties, 1 , sizeof(  properties)  , inputHandle ) == NULL )
  {
	 fclose( inputHandle ) ;
     return false ;
  }
  
  outSize = 0 ;
  for (ii = 0; ii < 4; ii++)
  {
    unsigned char b;

    //read 1 char  4 times ( 1 long without endianness issues )
    if ( fread( &b, 1 , sizeof( unsigned char) , inputHandle ) == NULL )
    {
  	   fclose( inputHandle ) ;
       return false ;
    }
    
    outSize += ((unsigned int)(b) << (ii * 8));
  }
  
   if (outSize == 0xFFFFFFFF)
  {
    strcpy(_k7zError, "stream version is not supported");
    return false;
  }
  

//display the size
//sprintf( buffer , "Size of depacked file is :  %d" , outSize ) ;
//	MessageBox( 0 , buffer ,0 , 0 ) ;

  //error on the size ?	
  if (outSize == 0xFFFFFFFF)
  {
    sprintf(_k7zError, "stream version is not supported");
	fclose(  inputHandle ) ;
    return false;
  }

  for (ii = 0; ii < 4; ii++)
  {
    unsigned char b;

    //read 4 chars again  ( this is now the compressed size of the data that we are trying to find  )
    if ( fread( &b, 1 ,  sizeof(b) , inputHandle ) == NULL )
    {
		fclose(  inputHandle ) ;
	  	return false;
    }
     
    if (b != 0)
    {
	     sprintf( _k7zError , "file too long ");
		fclose(  inputHandle ) ;
	  	return false;	  	
    }
    
  }

  compressedSize = length - 13;
  
  //display the compressed size of the file ( data part only )
//  sprintf( buffer , "Size of depacked file is :  %d" , outSize ) ;
//MessageBox( 0 , buffer ,0 , 0 ) ;
      
  //allocate the memory in order to read the file
  inStream = malloc(compressedSize);
  if (inStream == 0)
  {
    sprintf(_k7zError , "can't allocate memory for depacking");
	fclose(  inputHandle ) ;
	return false;	  	
  }

          //fread(data, 1, size, file)
	//k7zReadFile(FILE *file, void *data, size_t size)
    //fread(data, 1, size, file)
	//k7zReadFile(FILE *file, void *data, size_t size)

	//read the data
  if ( fread( inStream , 1 , compressedSize , inputHandle ) == NULL )
  {
    sprintf(_k7zError , "can't read file");
	fclose(  inputHandle ) ;
	return false;	  	
  }

  fclose(inputHandle);
  inputHandle = 0 ;

  prop0 = properties[0];
  if (prop0 >= (9*5*5))
  {
	 sprintf(_k7zError , "properties error");
	return false;	  	
  }
  
  //decode the properties ( i have no clue what that does )
for (pb = 0; prop0 >= (9 * 5); pb++, prop0 -= (9 * 5)) 
{}
    
for (lp = 0; prop0 >= 9; lp++, prop0 -= 9 ) 
{}

 lc = prop0;

  lzmaInternalSize =  (LZMA_BASE_SIZE + (LZMA_LIT_SIZE << (lc + lp)))* sizeof(CProb);

  #ifdef _LZMA_OUT_READ
  lzmaInternalSize += 100;
  #endif

	//prepare to spit the generated data.
  
	if ( outSize <= 0 )
	{
	   sprintf(_k7zError, "ouput file size is 0 byte.");
	   return false;
	}
	
  _dataSize = outSize ;
  dataPtr = new unsigned char[outSize];
  
  lzmaInternalData = malloc(lzmaInternalSize);
  if (dataPtr == 0 || lzmaInternalData == 0)
  {
    sprintf(_k7zError, "can't allocate memory for depacked data");
    return false;
  }

  #ifdef _LZMA_IN_CB
  bo.InCallback.Read = LzmaReadCompressed;
  bo.Buffer = (unsigned char *)inStream;
  bo.Size = compressedSize;
  #endif

   //_LZMA_OUT_READ == Decompression with buffering
  #ifdef _LZMA_OUT_READ
  {
   //_LZMA_OUT_READ == Decompression with buffering
    UInt32 nowPos;
    unsigned char *dictionary;
    UInt32 dictionarySize = 0;
    int i;
    
    //calculate the dictionnary size
    for (i = 0; i < 4; i++)
    {
      dictionarySize += (UInt32)(properties[1 + i]) << (i * 8);
    }

	//allocate memory for the dictionnary    
    dictionary = malloc( dictionarySize ) ;

    if (dictionary == 0)
    {
      sprintf( _k7zError, "can't allocate dictionnary memory");
      return false ;
    }
    
    //inits the lzma decoder
    LzmaDecoderInit((unsigned char *)lzmaInternalData, lzmaInternalSize,
        lc, lp, pb,
        dictionary, dictionarySize,
       // _LZMA_IN_CB    - Use callback for input data
        #ifdef _LZMA_IN_CB
        &bo.InCallback
        #else
        (unsigned char *)inStream, compressedSize
        #endif
        );
        
       //start depacking 
    for (nowPos = 0; nowPos < outSize;)
    {
      UInt32 blockSize = outSize - nowPos;
      UInt32 kBlockSize = 0x10000;
      
      if (blockSize > kBlockSize)
      {
        blockSize = kBlockSize;
      }

      //outstream got a malloc to contain the data.
      res = LzmaDecode((unsigned char *)lzmaInternalData, ((unsigned char *)outStream) + nowPos, blockSize, &outSizeProcessed);
			      if (res != 0)
			      {
			        sprintf(_k7zError, " LZMA decoder : error during decoding %d", res);
			        return false;
			      }
			      
			      if (outSizeProcessed == 0)
			      {
			        outSize = nowPos;
			        break;
			      }
			      nowPos += outSizeProcessed;
    }

    //free the memory used by the dictionnary
    free(dictionary);
  }

  #else					  //  Decompression without buffering

					  res = LzmaDecode((unsigned char *)lzmaInternalData, lzmaInternalSize,   lc, lp, pb,
				
				      #ifdef _LZMA_IN_CB
					 	     &bo.InCallback,
					      #else
					 	     (unsigned char *)inStream, compressedSize,
					      #endif
					    	  (unsigned char *)dataPtr, outSize, &outSizeProcessed);
					  outSize = outSizeProcessed;
  #endif

  if (res != 0)
  {
    sprintf(_k7zError , "lzma error = %d\n", res);
    return false ;
  }
  
/*
  if (numargs > 2)
  {
    outputHandle = fopen(args[2], "wb+");
    if (outputHandle == 0)
    {
      sprintf(rs + strlen(rs), "\n Open output file error");
      return 1;
    }
    processedSize = fwrite(outStream, 1, outSize, outputHandle);
    if (processedSize != outSize)
    {
      sprintf(_k7zError, "\n can't write");
      	if ( lzmaInternalData != NULL )
		{
			 free( lzmaInternalData );
		 	 lzmaInternalData = NULL ;
		}
		if ( inStream != NULL )
		{
		  	free( inStream );
		  	inStream  = NULL ;
		}
      return false;
    }
    fclose(outputHandle);
  }
  */

	freeInternalMemory( ) ;
	 
//  free(outStream);
  
  //0 == no error
  return true;
}

void	K7Z::freeInternalMemory( void )
{
	if ( lzmaInternalData != NULL )
	{
		 free( lzmaInternalData );
	 	 lzmaInternalData = NULL ;
	}
	if ( inStream != NULL )
	{
	  	free( inStream );
	  	inStream  = NULL ;
	}
}
