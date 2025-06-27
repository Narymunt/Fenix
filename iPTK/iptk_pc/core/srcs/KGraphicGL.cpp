#include		<windows.h>
#include		<stdio.h>
#include		"KGraphicGL.h"
#include		"KGlobals.h"
#include		"KMiscTools.h"
#include		"KWindowGL.h"
#include    "KResource.h"
#include 		"glati.h"

#include		"ximage.h"


#define	HIMETRIC_INCH	2540


short				KGraphicGL::screenWidth=0 , KGraphicGL::screenHeight=0 ,KGraphicGL::screenDepth=0  ;	
long				KGraphicGL::videoMemory = 0 ;
bool				KGraphicGL:: _graphicQuality = false ;
GLint 			KGraphicGL:: _oldBindedText =-1;
bool				KGraphicGL::_rectangleTexCap = true ;

void		getGLERR( GLenum g , char *t) ;

KGraphicGL::KGraphicGL( )
{
    if ( screenWidth == 0 )		KMiscTools::messageBox( "Screen Dimensions not specified, you will not see anything" , "KGraphicGL::SetScreenSize Not Called!" ) ;
    _pixels = NULL ;
    fimageWidth = 0 ;
    _ftextureWIDTH = 0 ;
    _ftextureHEIGHT = 0 ;
    setAlphaMode( true  ) ;
    _glEnum = GL_TEXTURE_2D ;
    _ckActive = false ;
    picX1 = 0 ;
    picY1 = 0 ;
    _userPixelPtr = NULL ;
    _userHiDef = false ;
    _textureWrap = false ;
    _blitColorChanged = false ;
    _rectangleTexCap = false ;
    _transPixX = -1 ;
    _transPixY = -1 ;
    _zoomX = 1 ;
    _zoomY = 1 ;
    
}

KGraphicGL::~KGraphicGL( )
{
    freePicture( ) ;
}

void		KGraphicGL::setColorKey( bool active , unsigned char r ,unsigned char g ,unsigned char b )
{
    _ckActive = active ;
    _ckr = r ;
    _ckg = g ;
    _ckb = b ;
}
/*
void		KGraphicGL::d3dTextureToTGA( char *sourcefilename , char *destFilename)
{
		MessageBox( 0 , "requires to be running in DirectX mode ( K_DIRECTX )" ,0,0 ) ;
}
*/
unsigned	char*		KGraphicGL::LoadGeneric( char	*filename )
{
    
    unsigned	char	*imageBits = NULL ;
    CxImage	*cxi = NULL ;
    KResource resImage;
    KResourceResult result;
    BYTE *buffer;
    int size = 0;
    
    strlwr( filename ) ;
    result = resImage.open (filename, K_RES_READ);
    if (result != K_RES_OK) 
    {
    		return NULL;
    }

    resImage.seek (K_RES_END, 0);
    result = resImage.tell (size);
    if ((result != K_RES_OK) || (!size))
    {
    	 return NULL;
    	}
    	
    resImage.seek (K_RES_BEGIN, 0);

    buffer = new BYTE [size];
    resImage.read (buffer, size);
    resImage.close ();

    if (		strstr( filename,".tga") != NULL )
    {
        cxi = new CxImage( buffer , (DWORD) size , CXIMAGE_FORMAT_TGA ) ;
    }
    
    if (		strstr( filename,".jpg") != NULL )
    {
        cxi = new CxImage( buffer , (DWORD) size , CXIMAGE_FORMAT_JPG ) ;
    }
    
    if (		strstr( filename,".bmp") != NULL )
    {
        cxi = new CxImage( buffer , (DWORD) size , CXIMAGE_FORMAT_BMP ) ;			
    }
    
    if (		strstr( filename,".png") != NULL )
    {
        cxi = new CxImage( buffer , (DWORD) size , CXIMAGE_FORMAT_PNG ) ;
    }


    if (		strstr( filename,".gif") != NULL )
    {
        cxi = new CxImage( buffer , (DWORD) size , CXIMAGE_FORMAT_GIF ) ;
    }


#if 0
    if (		strstr( filename,".pcx") != NULL )
    {
        cxi = new CxImage( buffer , (DWORD) size , CXIMAGE_FORMAT_PCX ) ;
    }
    
    if (		strstr( filename,".tif") != NULL )
    {
        cxi = new CxImage( buffer , (DWORD) size , CXIMAGE_FORMAT_TIF ) ;
    }
#endif
    
    delete	[]	buffer ;
    return	(unsigned char*)cxi ; 
    
}


unsigned	char*		KGraphicGL::LoadGenericFromPtr( char	*filename , unsigned char *buffer , unsigned long size )
{
    
    unsigned	char	*imageBits = NULL ;
    CxImage	*cxi = NULL ;

    
    if (buffer == NULL )		return NULL ;
    

    if (		strstr( filename,".tga") != NULL )
    {
        cxi = new CxImage( buffer , (DWORD) size , CXIMAGE_FORMAT_TGA ) ;
    }
    
    if (		strstr( filename,".jpg") != NULL )
    {
        cxi = new CxImage( buffer , (DWORD) size , CXIMAGE_FORMAT_JPG ) ;
    }
    
    if (		strstr( filename,".bmp") != NULL )
    {
        cxi = new CxImage( buffer , (DWORD) size , CXIMAGE_FORMAT_BMP ) ;			
    }
    
    if (		strstr( filename,".png") != NULL )
    {
        cxi = new CxImage( buffer , (DWORD) size , CXIMAGE_FORMAT_PNG ) ;
    }

#if 0
    if (		strstr( filename,".pcx") != NULL )
    {
        cxi = new CxImage( buffer , (DWORD) size , CXIMAGE_FORMAT_PCX ) ;
    }
    
    if (		strstr( filename,".tif") != NULL )
    {
        cxi = new CxImage( buffer , (DWORD) size , CXIMAGE_FORMAT_TIF ) ;
    }
#endif
    

    return	(unsigned char*)cxi ; 
    
}


//tries the ole loader ( pc ) or quicktime ( mac )
/*
unsigned	char*		KGraphicGL::LoadGeneric( char	*filename )
{
HRESULT 			hr;
unsigned long 	ulFileSize = 0  , ulBytesRead = 0 ;
HANDLE			hFile;
char					*dataPtr ;
HGLOBAL 			hGlobal = NULL ;
LPSTREAM 		pictureStreamPtr = NULL  ;
LPPICTURE 		picture = NULL;
short					catcherrorcode = 0 ;
unsigned	char	*imageBits = NULL ;

  // try the default loader
  try 
  {
		// open file
        hFile = CreateFile( filename , GENERIC_READ, 0, NULL, OPEN_EXISTING, 0, NULL);
        if ( hFile == INVALID_HANDLE_VALUE )				throw((const char*)"file not found" ) ;
        
          // get file size
          ulFileSize = GetFileSize(hFile, NULL);
          if ( ulFileSize == 0xFFFFFFFF || ulFileSize == 0) 		throw( (const char*)"file is corrupt" ) ;
          
            dataPtr  = NULL ;
            
              // alloc memory based on file size
              hGlobal = GlobalAlloc(GMEM_MOVEABLE, ulFileSize);
              if ( hGlobal == NULL )		throw((const char*)"out of memory" ) ;
              
                dataPtr = (char*) GlobalLock(hGlobal);	//our data points to the buffer prepared to receive the file
                if ( dataPtr == NULL )		throw( (const char*)"out of memory" ) ;
                
                  // read file and store in global memory
                  ReadFile(hFile, dataPtr, ulFileSize, &ulBytesRead, NULL);
                  if ( ulBytesRead != ulFileSize)	throw( (const char*)"File is corrupted" ) ;
                  
                    // create IStream* from global memory and FREE the memory of the HGLOBAL ( TRUE flag )
                    hr = CreateStreamOnHGlobal(hGlobal, TRUE, &pictureStreamPtr);
                    if ( hr != S_OK )		throw((const char*)"File is corrupted" ) ;
                    
                      hr = OleLoadPicture(pictureStreamPtr, ulFileSize, FALSE, IID_IPicture , (LPVOID *)&picture);
                      if (hr != S_OK )			throw( (const char*)"File is corrupted"  ) ;
                      
                        imageBits	=	RenderPicture( picture  ) ;
                        
                          picture->Release( ) ;
                          }
                          catch( const char *messageID )
                          {
                          KMiscTools::messageBox(  (char*)messageID , filename ) ;
                          
                            if ( pictureStreamPtr )		pictureStreamPtr->Release() ;
                            if( hGlobal )					
                            {	
                            GlobalUnlock( hGlobal );
                            GlobalFree( hGlobal ) ;
                            }
                            
                              CloseHandle(hFile);
                              return	NULL  ;
                              }
                              
                                
                                  
                                    //cool we could decompress our picture !	
                                    if ( pictureStreamPtr != NULL )	
                                    {
                                    pictureStreamPtr->Release() ;
                                    }
                                    
                                      if( hGlobal != NULL )					
                                      {	
                                      GlobalUnlock( hGlobal );
                                      GlobalFree( hGlobal ) ;
                                      }
                                      
                                        CloseHandle(hFile);
                                        
                                          return	imageBits ; 
                                          }
                                          
                                            unsigned char*		KGraphicGL::RenderPicture( LPPICTURE 		picture  ) 
                                            {
                                            long 						pictureWidth ,  pictureHeight ;
                                            RECT					r = {0,0,320,240 } ;
                                            int 						nWidth , nHeight , logpixelx ;
                                            HDC						screenDC , memDC ;
                                            
                                              HBITMAP				hbm, oldhbm  ;
                                              BITMAPINFO		bmi ;
                                              unsigned char		*bitmapBits ;
                                              unsigned char		*tmpBitmapBits ;
                                              
                                                //get the dpi of the screen
                                                screenDC		=	GetDC( GetDesktopWindow( ) ) ; 
                                                memDC			=	CreateCompatibleDC( screenDC ) ;
                                                
                                                  logpixelx		= 	GetDeviceCaps( screenDC , LOGPIXELSX ) ;
                                                  ReleaseDC( GetDesktopWindow( ) , screenDC ) ;
                                                  
                                                    picture->get_Width(	&pictureWidth	);
                                                    picture->get_Height(	&pictureHeight	);
                                                    
                                                      // convert himetric to pixels
                                                      nWidth	= MulDiv(	pictureWidth		, logpixelx	, HIMETRIC_INCH) ;
                                                      nHeight	= MulDiv(	pictureHeight		, logpixelx	, HIMETRIC_INCH) ;
                                                      
                                                        memset( &bmi , 0 , sizeof( BITMAPINFO ) ) ;
                                                        
                                                          bmi.bmiHeader.biSize 				=	sizeof( BITMAPINFOHEADER ) ;
                                                          bmi.bmiHeader.biWidth			=	nWidth ;
                                                          bmi.bmiHeader.biHeight 			=	nHeight ;
                                                          bmi.bmiHeader.biPlanes 			=	1 ;
                                                          bmi.bmiHeader.biBitCount 		=	24 ;		//32 bits
                                                          bmi.bmiHeader.biCompression = BI_RGB ;
                                                          bmi.bmiHeader.biSizeImage 	=	nWidth*nHeight*3	; 
                                                          bmi.bmiHeader.biXPelsPerMeter =0;
                                                          bmi.bmiHeader.biYPelsPerMeter =0 ;
                                                          
                                                            hbm = CreateDIBSection( memDC , &bmi , DIB_RGB_COLORS , (void**)&bitmapBits , NULL , 0 ) ;
                                                            
                                                              if ( bitmapBits == NULL )	
                                                              {
                                                              KMiscTools::messageBox( "error" , "could not create dib section"  ) ;
                                                              return	NULL ;
                                                              }
                                                              
                                                                //attache notre bitmap a notre DC de destination
                                                                oldhbm  = ( HBITMAP )SelectObject( 	memDC , hbm ) ;
                                                                
                                                                  //render la pic	
                                                                  picture->Render(	memDC,
                                                                  0,0,nWidth	,nHeight,						//destination
                                                                  0,pictureHeight,pictureWidth	,-pictureHeight,		//source  ( stored backwards )
                                                                  NULL  )	;
                                                                  
                                                                    //restitue ce qu'on a modifié
                                                                    SelectObject( 	memDC , oldhbm ) ;
                                                                    
                                                                      //libere le merdier	
                                                                      DeleteObject( memDC ) ;
                                                                      
                                                                        tmpBitmapBits = new	unsigned char[sizeof( tgaBitmap )+( nWidth * nHeight * 3) ] ;
                                                                        
                                                                          if ( tmpBitmapBits == NULL )
                                                                          {
                                                                          KMiscTools::messageBox( "out of memory (tmpBitmapBits)" , "error" ) ;
                                                                          }
                                                                          else
                                                                          {
                                                                          tgaBitmap		*tgaheader ;
                                                                          
                                                                            tgaheader =  (tgaBitmap*)tmpBitmapBits ;
                                                                            tgaheader->width		=	nWidth ; 
                                                                            tgaheader->height		=	nHeight ;
                                                                            tgaheader->bpp			=	24 ;
                                                                            
                                                                              memcpy(  tmpBitmapBits+sizeof(tgaBitmap) , bitmapBits , nWidth*nHeight*3 ) ;
                                                                              }
                                                                              
                                                                                //MessageBox( 0 ,"Erwer",0,0 ) ;
                                                                                //delete la bitmap en memoire
                                                                                DeleteObject( hbm ) ;
                                                                                
                                                                                  return	tmpBitmapBits ;
                                                                                  }
*/
/*
unsigned	char*		KGraphicGL::LoadTGA( char	*filename )
{
    FILE		*ftga ;
    long						filesize ,	 bytesread ;
    unsigned	long		header ;
    unsigned	char		*fileBuffer = NULL ;	
    
    
    //open the file and get its size		
    ftga = fopen( filename , "rb" ) ;
    if ( ftga == NULL )	
    {
        char msg[1024] ;
        strcpy( msg , "Could not open file " ) ;
        strcat( msg , filename ) ;
        KMiscTools::messageBox(  "Could not open file", filename ) ;
        return NULL ;
    }
    
    fseek(ftga , 0 , SEEK_END );	
    //check if the file is of a valid size
    filesize = ftell( ftga ) ;
    
    if ( filesize <= 0 )
    {
        KMiscTools::messageBox(  "file is 0 byte",filename  ) ;
        fclose( ftga ) ;
        return NULL ;
    }
    
    
    fseek( ftga , 0 , SEEK_SET ) ; 
    
    
    fread( &header , 1 , sizeof( unsigned long ) , ftga ) ;
    if (  header != 'ship' )
    {
        //fichier non compressé
        fseek( ftga , 0 , SEEK_SET ) ; 
    }
    else
    {
        filesize -= sizeof( unsigned long ) ;
    }
    
    fileBuffer =  new unsigned char[filesize]  ;	
    if ( fileBuffer == NULL )
    {
        KMiscTools::messageBox(  "Out of memory",filename  ) ;
        //probably out of memory
        fclose( ftga ) ;
        return NULL ;
    }
    
    
    //read the file
    bytesread =  (long)fread (  (void*)fileBuffer , (unsigned int)filesize ,  (unsigned int)1 , ftga ) ;
    fclose( ftga ) ;
    
    if ( bytesread != 1  )		//number of items
    {
        KMiscTools::messageBox(  "Out of data to read",filename  ) ;
        delete	[]	fileBuffer ;
        fileBuffer = NULL ;
    }
    
    return fileBuffer ;	
}
*/
//returns the width of a picture
float			KGraphicGL::getTextureWidth( void )
{
    return fimageWidth ;
}

//returns the height of a picture
float			KGraphicGL::getTextureHeight( void )
{
    return fimageHeight ;
}


//build a 32 bit picture from an array
bool		KGraphicGL::makePictureFromArray( unsigned long *userPixelPtr , long width , long height , bool hiDef )
{
    long						newSize , i  ;
    long						imageWidth , imageHeight ;
    unsigned	long		*ptr ;			
    unsigned	long		*tempbuffer ;			
    unsigned	long		colorkey , curColor ,r,g,b;
    long						x , y ;
    
    if ( userPixelPtr == NULL )			return K_ERROR ;
    if ( width <= 0 || height <= 0  )		return K_ERROR ;
    
    r = _ckr ;
    g = _ckg ;
    b = _ckb ;
    
    colorkey = r | (g <<8) | (b << 16) ;

    if ( _ckActive == true )
    {
        for ( x = 0 ; x < width ; x++ )
        {
            
            for ( y= 0 ;y < height ; y++ )
            {
                curColor = userPixelPtr[x+y*width] & 0x00ffffff ;
                if ( curColor == colorkey ) 
                {
                    userPixelPtr[x+y*width] = 0 ;
                }
            }
        }
    }
    
    ptr = userPixelPtr ;
    _userPixelPtr = userPixelPtr ;
    
    glLoadIdentity();
    glFlush( ) ;
    
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    
    imageWidth		=	width ; 
    imageHeight 		=	height ; 
    
    fimageWidth	=	(float)imageWidth ;
    fimageHeight 	=	(float)imageHeight ;
    

    newSize = imageWidth ;
    if ( imageHeight > imageWidth )			newSize 	=	imageHeight ;
    
    //calculate a multiple of 2 for the texture size
    i = 2 ;
    do
    {
        i *= 2 ;
    }while( i < newSize ) ;
    
    newSize = i ;

	tempbuffer = new unsigned long[newSize*newSize] ;
	memset( tempbuffer , 0 , newSize*newSize*sizeof( unsigned long) ) ;
	
      for ( x = 0 ; x < width ; x++ )
        {  
            for ( y= 0 ;y < height ; y++ )
            {
                tempbuffer[x+y*newSize] =     userPixelPtr[x+y*width]  ;
            }
        }			
   //does the card handle rectangular textures ?
 //   if (i ==width &&   width == height  )
  // {			
        //non        
        _glEnum = GL_TEXTURE_2D ;
        _ftextureWIDTH 		=	(float)newSize ;
        _ftextureHEIGHT		=	(float)newSize ;
  //  	}
   // else
  //  {

   //     _glEnum =  GL_TEXTURE_RECTANGLE_NV ;
    //    _ftextureWIDTH 		=	(float)fimageWidth ;
     //   _ftextureHEIGHT		=	(float)fimageHeight ;
   // }

/*    
    //square texture from the source, we force everything in gl_textire_2d !  ( less bugs! :)  )
    if ( newSize == _ftextureWIDTH && _ftextureWIDTH == _ftextureHEIGHT )
    {
        _glEnum = GL_TEXTURE_2D ;
        
        _ftextureWIDTH 		=	(float)newSize ;
        _ftextureHEIGHT		=	(float)newSize ;
    }
   */
    _glEnum = GL_TEXTURE_2D;

    glLoadIdentity ();

//    glDisable( GL_TEXTURE_RECTANGLE_NV ) ;

    //genere un nom de texture		
    glGenTextures( 1 , &texture ) ;

    glDisable( GL_TEXTURE_2D ) ;
    glEnable( _glEnum ) ;

    glBindTexture(_glEnum, texture ) ;
    _oldBindedText = texture ;
    
    _userHiDef = hiDef ;

    if ( true == _userHiDef )
    {
        glTexImage2D( _glEnum , 0 , GL_RGBA8       , (long)_ftextureWIDTH,(long)_ftextureHEIGHT ,0 , GL_RGBA     , GL_UNSIGNED_BYTE , tempbuffer ) ; 			
    }
    else
    {
        glTexImage2D( _glEnum , 0 , GL_RGBA       , (long)_ftextureWIDTH, (long)_ftextureHEIGHT ,0 , GL_RGBA     , GL_UNSIGNED_BYTE , tempbuffer ) ; 
    }
        
    setTextureQuality (false);
    
    glTexParameteri( _glEnum, GL_TEXTURE_WRAP_S,  GL_CLAMP);	
    glTexParameteri( _glEnum, GL_TEXTURE_WRAP_T,  GL_CLAMP );
  
  	 
    if (  tempbuffer != NULL )
    {
        delete	[]  tempbuffer ;
         tempbuffer = NULL ;
    }

    if ( _pixels != NULL )
    {
        delete	[] _pixels ;
        _pixels = NULL ;
    }

    //pollArray() ;
    
    return	K_OK ;
}

void			KGraphicGL::pollArray( void )
{
    if ( _userPixelPtr == NULL )		return ;
    
    glLoadIdentity( ) ;
    glDisable( GL_TEXTURE_2D ) ;
//    glDisable( GL_TEXTURE_RECTANGLE_NV ) ;
    glEnable( _glEnum ) ;
    ptk_glBindTexture( ) ;
    
    if ( true == _userHiDef )
    {
        glTexSubImage2D( _glEnum , 0 , 0,0       , (long)fimageWidth,(long)fimageHeight , GL_RGBA     , GL_UNSIGNED_BYTE , _userPixelPtr ) ; 			
    }
    else
    {
        glTexSubImage2D( _glEnum , 0 , 0,0       , (long)fimageWidth, (long)fimageHeight , GL_RGBA     , GL_UNSIGNED_BYTE , _userPixelPtr ) ; 
    }
}


bool			KGraphicGL::loadPictureFromPtr( const	char	*filename , unsigned char	*dataPtr , unsigned long datasize , bool hiDef , bool hasalpha ) 
{
    unsigned 	char	*pixelPtr ;		
    long						newSize , i ,x,y ;
    long						imageWidth , imageHeight ;
    tgaBitmap				tgaInfo ;
    CxImage				*cxImagePtr ;		
//    GLenum					 gerror ;
    
    
    freePicture( ) ;
    
    cxImagePtr = (CxImage*)LoadGenericFromPtr( (char*)filename , (unsigned char*)dataPtr , datasize )  ; 	
    
    if ( cxImagePtr	== NULL )	
    {
        char msg[1024] ;
        strcpy( msg , "Could not load picture " ) ;
        strcat( msg , filename ) ;
        //	KMiscTools::messageBox(  filename,"file not found or out of memory" ) ;
        return	K_ERROR ;
    }
    
    
    memset (&tgaInfo, 0, sizeof (tgaInfo));
    tgaInfo.bpp = cxImagePtr->GetBpp( ) ;
    tgaInfo.width = cxImagePtr->GetWidth( ) ;
    tgaInfo.height = cxImagePtr->GetHeight( ) ;
    long ct = cxImagePtr->GetColorType( ) ;
    if ( ct == 4) 
    {
        tgaInfo.bpp  = 32 ;
    }
    
    //not sure this is useful, but opengl crashes if not present ( sometimes )
    glLoadIdentity();
    glFlush( ) ;
    
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    
    imageWidth		=	tgaInfo.width ; 
    imageHeight 		=	tgaInfo.height ; 
    
    fimageWidth	=	(float)imageWidth ;
    fimageHeight 	=	(float)imageHeight ;
    picX1	=	tgaInfo.xstart ;
    picY1	=	tgaInfo.ystart ;
    
    newSize = imageWidth ;
    if ( imageHeight > imageWidth )			newSize 	=	imageHeight ;
    
    //calculate a multiple of 2 for the texture size
    i = 2 ;
    do
    {
        i *= 2 ;
    }while( i < newSize ) ;
    
    newSize = i ;	

	_rectangleTexCap	= false ;

   
    //does the card handle rectangular textures ?
    if ( _rectangleTexCap == false  )
    {			
        //non
        _glEnum = GL_TEXTURE_2D ;
        _ftextureWIDTH 		=	(float)newSize ;
        _ftextureHEIGHT		=	(float)newSize ;
    }
    else
    {

        _glEnum =  GL_TEXTURE_RECTANGLE_NV ;
        _ftextureWIDTH 		=	(float)fimageWidth ;
        _ftextureHEIGHT		=	(float)fimageHeight ;
   }
    

    //square texture from the source, we force everything in gl_textire_2d !  ( less bugs! :)  )
    if ( i == _ftextureWIDTH && _ftextureWIDTH == _ftextureHEIGHT )
    {
        _glEnum = GL_TEXTURE_2D ;
        
        _ftextureWIDTH 		=	(float)newSize ;
        _ftextureHEIGHT		=	(float)newSize ;
    }

    
    _pixels = new unsigned char[(long)(_ftextureWIDTH*_ftextureHEIGHT*4)] ;
    memset( _pixels , 0 , (long)(_ftextureWIDTH*_ftextureHEIGHT*4) ) ;
    
    pixelPtr = (unsigned char*)cxImagePtr->GetBits( ) ;
    
    unsigned char r,g,b ,a;
    
    switch ( tgaInfo.bpp )
    {
    /*
    //du joli 24 bits
    case	24:
				for ( x =0 ; x < imageWidth ; x++)
                {
                for ( y = 0 ; y < imageHeight ; y++ )
                {
                r = pixelPtr[3*x+(imageHeight-y-1)*imageWidth*3+2] ;
                g = pixelPtr[3*x+(imageHeight-y-1)*imageWidth*3+1] ;
                b = pixelPtr[3*x+(imageHeight-y-1)*imageWidth*3+0] ;
                a = 255 ;
                
                  if ( _ckActive == true && _ckr == r && _ckb == b && _ckg == g )
                  {
                  a = 0 ;							
                  }
                  
                    _pixels[4*x+y*(long)_ftextureWIDTH*4] 	 = 	r ;				//r
                    _pixels[4*x+y*(long)_ftextureWIDTH*4+1]	 =	g	 ;				//g
                    _pixels[4*x+y*(long)_ftextureWIDTH*4+2]	 = b ;				//b
                    _pixels[4*x+y*(long)_ftextureWIDTH*4+3] =	a  ;				//a							
                    
                      }	
                      }
                      break ;
        */
        //du 32 bits avec alpha			
    case	32:
        //32 bits
        for ( x =0 ; x < imageWidth ; x++)
        {
            for ( y = 0 ; y < imageHeight ; y++ )
            {
                RGBQUAD color ;
                color = cxImagePtr->GetPixelColor( x , imageHeight-(y+1) , true ) ;
                
                r =   color.rgbRed  ;
                g = color.rgbGreen  ;
                b = color.rgbBlue ;
                a = color.rgbReserved  ;
                
                if ( _ckActive == true && _ckr == r && _ckb == b && _ckg == g )
                {
                    a = 0 ;							
                }
                
                _pixels[4*x+y*(long)_ftextureWIDTH*4] 	 = 	r ;				//r
                _pixels[4*x+y*(long)_ftextureWIDTH*4+1]	 =	g	 ;				//g
                _pixels[4*x+y*(long)_ftextureWIDTH*4+2]	 = b ;				//b
                _pixels[4*x+y*(long)_ftextureWIDTH*4+3] =	a  ;				//a							
                
            }	
        }
        
        /*
        for ( x =0 ; x < imageWidth*4 ; x+=4)
        {
        for ( y = 0 ; y < imageHeight ; y++ )
        {
        r = pixelPtr[x+(imageHeight-y-1)*imageWidth*4+2] ;
        g = pixelPtr[x+(imageHeight-y-1)*imageWidth*4+1] ;
        b = pixelPtr[x+(imageHeight-y-1)*imageWidth*4+0] ;
        a = pixelPtr[x+(imageHeight-y-1)*imageWidth*4+3] ;
        
          if ( _ckActive == true && _ckr == r && _ckb == b && _ckg == g )
          {
          a = 0 ;							
          }
          
            _pixels[x+y*(long)_ftextureWIDTH*4] 		= 	r	 ;				//r
            _pixels[x+y*(long)_ftextureWIDTH*4+1] 	=	g	 ;				//g
            _pixels[x+y*(long)_ftextureWIDTH*4+2] 	=	b	 ;				//b
            _pixels[x+y*(long)_ftextureWIDTH*4+3] 	=	a	 ;				//a
            }	
            }
        */
        break ;
    default:
        
        //8 or 16 or 24 bits
        for ( x =0 ; x < imageWidth ; x++)
        {
            for ( y = 0 ; y < imageHeight ; y++ )
            {
                RGBQUAD color ;
                color = cxImagePtr->GetPixelColor( x , imageHeight-(y+1) , false ) ;
                
                r =   color.rgbRed  ;
                g = color.rgbGreen  ;
                b = color.rgbBlue ;
                a = 255 ;
                
                if ( _ckActive == true && _ckr == r && _ckb == b && _ckg == g )
                {
                    a = 0 ;							
                }
                
                _pixels[4*x+y*(long)_ftextureWIDTH*4] 	 = 	r ;				//r
                _pixels[4*x+y*(long)_ftextureWIDTH*4+1]	 =	g	 ;				//g
                _pixels[4*x+y*(long)_ftextureWIDTH*4+2]	 = b ;				//b
                _pixels[4*x+y*(long)_ftextureWIDTH*4+3] =	a  ;				//a							
                
            }	
        }
        
        break ;
        
        }
        
        //free the memory where we loaded the tga
        delete cxImagePtr ;
        cxImagePtr = NULL ;
        pixelPtr = NULL;
        
        glLoadIdentity( ) ;
        //genere un nom de texture		
        glGenTextures( 1 , &texture ) ;
        
        glDisable( GL_TEXTURE_2D ) ;
//        glDisable( GL_TEXTURE_RECTANGLE_NV ) ;
        glEnable( _glEnum ) ;
        
        glBindTexture(_glEnum, texture ) ;
        _oldBindedText = texture ;

        //getGLERR( 	glGetError( ) ,filename ) ;
        
        if ( hasalpha == K_ALPHA )
        {
            if ( true == hiDef )
            {
                glTexImage2D( _glEnum , 0 , GL_RGBA8       , (long)_ftextureWIDTH,(long)_ftextureHEIGHT ,0 , GL_RGBA     , GL_UNSIGNED_BYTE , _pixels ) ; 			
            }
            else
            {
                glTexImage2D( _glEnum , 0 , GL_RGBA       , (long)_ftextureWIDTH, (long)_ftextureHEIGHT ,0 , GL_RGBA     , GL_UNSIGNED_BYTE , _pixels ) ; 
            }
        }
        else
        {
            if ( true == hiDef )
            {
                glTexImage2D( _glEnum , 0 , GL_RGB8       , (long)_ftextureWIDTH, (long)_ftextureHEIGHT ,0 , GL_RGBA     , GL_UNSIGNED_BYTE , _pixels ) ; 
            }
            else
            {
                glTexImage2D( _glEnum , 0 , GL_RGB       , (long)_ftextureWIDTH, (long)_ftextureHEIGHT ,0 , GL_RGBA     , GL_UNSIGNED_BYTE , _pixels ) ; 
            }
        }
        
        
        setTextureQuality( _graphicQuality ) ;
        
        if ( _textureWrap == false )
        {
            glTexParameteri( _glEnum, GL_TEXTURE_WRAP_S,  GL_CLAMP);	
            glTexParameteri( _glEnum, GL_TEXTURE_WRAP_T,  GL_CLAMP );
        }
        else
        {
            glTexParameteri( _glEnum, GL_TEXTURE_WRAP_S,  GL_REPEAT);	
            glTexParameteri( _glEnum, GL_TEXTURE_WRAP_T,  GL_REPEAT );
        }
        
        //free the converted pixel buffer memory
        delete	[]	_pixels ;
        _pixels = NULL ;
        
        videoMemory += (long)_ftextureWIDTH*(long)_ftextureHEIGHT*( screenDepth / 8 ) ;
        
//        setCenterPoint( 0,0 ) ;
        
        return K_OK ;
}

bool			KGraphicGL::loadPictureWithMask( const	char	*filename , const	char	*filenameMask , bool hiDef ) 
{
	
    long					newSize , i ,x,y ;
    long					imageWidth , imageHeight ;
    tgaBitmap				tgaInfo ;
    CxImage				*cxImagePtrSource ;		
    CxImage				*cxImagePtrMask ;		

    
    
    freePicture( ) ;
    
      cxImagePtrMask = (CxImage*)LoadGeneric( (char*)filenameMask )  ; 	
 cxImagePtrSource = (CxImage*)LoadGeneric( (char*)filename )  ; 	
 
    
    memset (&tgaInfo, 0, sizeof (tgaInfo));
    tgaInfo.bpp = cxImagePtrSource->GetBpp( ) ;
    tgaInfo.width = cxImagePtrSource->GetWidth( ) ;
    tgaInfo.height = cxImagePtrSource->GetHeight( ) ;
    long ct = cxImagePtrSource->GetColorType( ) ;
    if ( ct == 4) 
    {
        tgaInfo.bpp  = 32 ;
    }
    
     
    //not sure this is useful, but opengl crashes if not present ( sometimes )
    glLoadIdentity();
    glFlush( ) ;
    
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    
    imageWidth		=	tgaInfo.width ; 
    imageHeight 		=	tgaInfo.height ; 
    
    fimageWidth	=	(float)imageWidth ;
    fimageHeight 	=	(float)imageHeight ;
    picX1	=	tgaInfo.xstart ;
    picY1	=	tgaInfo.ystart ;
    
    newSize = imageWidth ;
    if ( imageHeight > imageWidth )			newSize 	=	imageHeight ;
    
    //calculate a multiple of 2 for the texture size
    i = 2 ;
    do
    {
        i *= 2 ;
    }while( i < newSize ) ;
    
    newSize = i ;	

	_rectangleTexCap	= false ;

   
    //does the card handle rectangular textures ?
    if ( _rectangleTexCap == false  )
    {			
        //non
        _glEnum = GL_TEXTURE_2D ;
        _ftextureWIDTH 		=	(float)newSize ;
        _ftextureHEIGHT		=	(float)newSize ;
    }
    else
    {

        _glEnum =  GL_TEXTURE_RECTANGLE_NV ;
        _ftextureWIDTH 		=	(float)fimageWidth ;
        _ftextureHEIGHT		=	(float)fimageHeight ;
   }
    

    //square texture from the source, we force everything in gl_textire_2d !  ( less bugs! :)  )
    if ( i == _ftextureWIDTH && _ftextureWIDTH == _ftextureHEIGHT )
    {
        _glEnum = GL_TEXTURE_2D ;
        
        _ftextureWIDTH 		=	(float)newSize ;
        _ftextureHEIGHT		=	(float)newSize ;
    }

    
    _pixels = new unsigned char[(long)(_ftextureWIDTH*_ftextureHEIGHT*4)] ;
    memset( _pixels , 0 , (long)(_ftextureWIDTH*_ftextureHEIGHT*4) ) ;
    
   
    unsigned char r,g,b ,a;
    RGBQUAD	maskIntensity ;
    
    switch ( tgaInfo.bpp )
    {
          //du 32 bits with  alpha			
    case	32:
        //32 bits
        for ( x =0 ; x < imageWidth ; x++)
        {
            for ( y = 0 ; y < imageHeight ; y++ )
            {
                RGBQUAD color ;
                color = cxImagePtrSource->GetPixelColor( x , imageHeight-(y+1) , true ) ;
                maskIntensity = cxImagePtrMask->GetPixelColor( x , imageHeight-(y+1) , true  ) ;
       
                r =   color.rgbRed  ;
                g = color.rgbGreen  ;
                b = color.rgbBlue ;
                a = maskIntensity.rgbBlue  ;

                if ( _ckActive == true && _ckr == r && _ckb == b && _ckg == g )
                {
                    a = 0 ;							
                }                
                _pixels[4*x+y*(long)_ftextureWIDTH*4] 	 = 	r ;				//r
               _pixels[4*x+y*(long)_ftextureWIDTH*4+1]	 =	g	 ;				//g
                _pixels[4*x+y*(long)_ftextureWIDTH*4+2]	 = b ;				//b
                _pixels[4*x+y*(long)_ftextureWIDTH*4+3] =	a  ;				//a							                
            }	
        }

        break ;
    default:
        
        //8 or 16 or 24 bits
        for ( x =0 ; x < imageWidth ; x++)
        {
            for ( y = 0 ; y < imageHeight ; y++ )
            {
                RGBQUAD color ;
               color = cxImagePtrSource->GetPixelColor( x , imageHeight-(y+1) , true ) ;
                maskIntensity = cxImagePtrMask->GetPixelColor( x , imageHeight-(y+1) , true  ) ;
                     
                r =   color.rgbRed  ;
                g = color.rgbGreen  ;
                b = color.rgbBlue ;
               a = maskIntensity.rgbBlue  ;
                
                if ( _ckActive == true && _ckr == r && _ckb == b && _ckg == g )
                {
                                a = 0 ;							                 				
                }
        		
                //c bien ici
             	_pixels[4*x+y*(long)_ftextureWIDTH*4] 	 = 	r ;				//r
             	_pixels[4*x+y*(long)_ftextureWIDTH*4+1]	 =	g	 ;				//g
             	_pixels[4*x+y*(long)_ftextureWIDTH*4+2]	 =	 b ;				//b
            	_pixels[4*x+y*(long)_ftextureWIDTH*4+3] 	=	a  ;				//a							
                
            }	
        }
        
        break ;
        
        }
        
        //free the memory where we loaded the tga

        delete cxImagePtrSource ;
        cxImagePtrSource = NULL ;

        delete cxImagePtrMask ;
        cxImagePtrMask = NULL ;
        
        glLoadIdentity( ) ;
        //genere un nom de texture		
        glGenTextures( 1 , &texture ) ;
        
        glDisable( GL_TEXTURE_2D ) ;
//        glDisable( GL_TEXTURE_RECTANGLE_NV ) ;
        glEnable( _glEnum ) ;
        
        glBindTexture(_glEnum, texture ) ;
        _oldBindedText = texture ;

        //getGLERR( 	glGetError( ) ,filename ) ;
        
            if ( true == hiDef )
            {
                glTexImage2D( _glEnum , 0 , GL_RGBA8       , (long)_ftextureWIDTH,(long)_ftextureHEIGHT ,0 , GL_RGBA     , GL_UNSIGNED_BYTE , _pixels ) ; 			
            }
            else
            {
                glTexImage2D( _glEnum , 0 , GL_RGBA       , (long)_ftextureWIDTH, (long)_ftextureHEIGHT ,0 , GL_RGBA     , GL_UNSIGNED_BYTE , _pixels ) ; 
            }
     
        
        
        setTextureQuality( _graphicQuality ) ;
        
        if ( _textureWrap == false )
        {
            glTexParameteri( _glEnum, GL_TEXTURE_WRAP_S,  GL_CLAMP);	
            glTexParameteri( _glEnum, GL_TEXTURE_WRAP_T,  GL_CLAMP );
        }
        else
        {
            glTexParameteri( _glEnum, GL_TEXTURE_WRAP_S,  GL_REPEAT);	
            glTexParameteri( _glEnum, GL_TEXTURE_WRAP_T,  GL_REPEAT );
        }
        
        //free the converted pixel buffer memory
        delete	[]	_pixels ;
        _pixels = NULL ;
        
        videoMemory += (long)_ftextureWIDTH*(long)_ftextureHEIGHT*( screenDepth / 8 ) ;
        
//        setCenterPoint( 0,0 ) ;
        
        return K_OK ;
}


bool			KGraphicGL::loadPicture2d( const char	*filename , long x, long y )  
{
	_transPixX = x ;
	_transPixY = y ;
	return loadPicture( filename, true , true ) ;
}


bool			KGraphicGL::loadPicture2dFromPtr( const char	*filename , unsigned char	*dataPtr , unsigned long datasize , long x, long y )  
{
	_transPixX = x ;
	_transPixY = y ;
	return loadPictureFromPtr( filename, dataPtr , datasize , true, true  ) ;
	
	
}


void			KGraphicGL::blitRect2d( float	x1, float y1 , float	x2 , float y2 , short	destX , short	destY  )  
{	
	blitRect( x1,y1,x2,y2, destX, destY ) ;
}

void			KGraphicGL::blitAlphaRect2d( float	x1, float y1 , float	x2 , float y2 , short	destX , short	destY  )  
{
	blitAlphaRect( x1,y1,x2,y2, destX, destY ) ;
}
	


bool			KGraphicGL::loadPicture( const	char	*filename , bool hiDef , bool hasalpha ) 
{
    unsigned 	char	*pixelPtr ;		
    long						newSize , i ,x,y ;
    long						imageWidth , imageHeight ;
    tgaBitmap				tgaInfo ;
    CxImage				*cxImagePtr ;		
//    GLenum					 gerror ;
    
    
    freePicture( ) ;
    
    cxImagePtr = (CxImage*)LoadGeneric( (char*)filename )  ; 	
    
    if ( cxImagePtr	== NULL )	
    {
        char msg[1024] ;
        strcpy( msg , "Could not load picture " ) ;
        strcat( msg , filename ) ;
        //	KMiscTools::messageBox(  filename,"file not found or out of memory" ) ;
        return	K_ERROR ;
    }
    
    
    memset (&tgaInfo, 0, sizeof (tgaInfo));
    tgaInfo.bpp = cxImagePtr->GetBpp( ) ;
    tgaInfo.width = cxImagePtr->GetWidth( ) ;
    tgaInfo.height = cxImagePtr->GetHeight( ) ;
    long ct = cxImagePtr->GetColorType( ) ;
    if ( ct == 4) 
    {
        tgaInfo.bpp  = 32 ;
    }
    
    //not sure this is useful, but opengl crashes if not present ( sometimes )
    glLoadIdentity();
    glFlush( ) ;
    
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    
    imageWidth		=	tgaInfo.width ; 
    imageHeight 		=	tgaInfo.height ; 
    
    fimageWidth	=	(float)imageWidth ;
    fimageHeight 	=	(float)imageHeight ;
    picX1	=	tgaInfo.xstart ;
    picY1	=	tgaInfo.ystart ;
    
    newSize = imageWidth ;
    if ( imageHeight > imageWidth )			newSize 	=	imageHeight ;
    
    //calculate a multiple of 2 for the texture size
    i = 2 ;
    do
    {
        i *= 2 ;
    }while( i < newSize ) ;
    
    newSize = i ;	

	_rectangleTexCap	= false ;

   
    //does the card handle rectangular textures ?
    if ( _rectangleTexCap == false  )
    {			
        //non
        _glEnum = GL_TEXTURE_2D ;
        _ftextureWIDTH 		=	(float)newSize ;
        _ftextureHEIGHT		=	(float)newSize ;
    }
    else
    {

        _glEnum =  GL_TEXTURE_RECTANGLE_NV ;
        _ftextureWIDTH 		=	(float)fimageWidth ;
        _ftextureHEIGHT		=	(float)fimageHeight ;
   }
    

    //square texture from the source, we force everything in gl_textire_2d !  ( less bugs! :)  )
    if ( i == _ftextureWIDTH && _ftextureWIDTH == _ftextureHEIGHT )
    {
        _glEnum = GL_TEXTURE_2D ;
        
        _ftextureWIDTH 		=	(float)newSize ;
        _ftextureHEIGHT		=	(float)newSize ;
    }

    
    _pixels = new unsigned char[(long)(_ftextureWIDTH*_ftextureHEIGHT*4)] ;
    memset( _pixels , 0 , (long)(_ftextureWIDTH*_ftextureHEIGHT*4) ) ;
    
    pixelPtr = (unsigned char*)cxImagePtr->GetBits( ) ;

RGBQUAD color ;    
unsigned char r,g,b ,a;

    if ( _transPixX >= 0 && _transPixY >= 0 )
    {
   
                color = cxImagePtr->GetPixelColor( _transPixX , imageHeight-(_transPixY+1) , true ) ;
                
                r =   color.rgbRed  ;
                g = color.rgbGreen  ;
                b = color.rgbBlue ;
                a = color.rgbReserved  ;
                setColorKey( true , r, g, b  ) ;
    }
    
    

    
    switch ( tgaInfo.bpp )
    {
          //du 32 bits with  alpha			
    case	32:
        //32 bits
        for ( x =0 ; x < imageWidth ; x++)
        {
            for ( y = 0 ; y < imageHeight ; y++ )
            {
              
                color = cxImagePtr->GetPixelColor( x , imageHeight-(y+1) , true ) ;
                
                r =   color.rgbRed  ;
                g = color.rgbGreen  ;
                b = color.rgbBlue ;
                a = color.rgbReserved  ;
                
                if ( _ckActive == true && _ckr == r && _ckb == b && _ckg == g )
                {
                    if ( hasalpha != K_ALPHA )
				{
					a = 255 ;
				}
				else
				{
                    a = 0 ;							
                   }
                }
                
                _pixels[4*x+y*(long)_ftextureWIDTH*4] 	 = 	r ;				//r
                _pixels[4*x+y*(long)_ftextureWIDTH*4+1]	 =	g	 ;				//g
                _pixels[4*x+y*(long)_ftextureWIDTH*4+2]	 = b ;				//b
                _pixels[4*x+y*(long)_ftextureWIDTH*4+3] =	a  ;				//a							
                
            }	
        }
        

        break ;
    default:
        
        //8 or 16 or 24 bits
        for ( x =0 ; x < imageWidth ; x++)
        {
            for ( y = 0 ; y < imageHeight ; y++ )
            {
                RGBQUAD color ;
                color = cxImagePtr->GetPixelColor( x , imageHeight-(y+1) , false ) ;
                
                r =   color.rgbRed  ;
                g = color.rgbGreen  ;
                b = color.rgbBlue ;
                a = 255 ;
                
                if ( _ckActive == true && _ckr == r && _ckb == b && _ckg == g )
                {
                  if ( hasalpha != K_ALPHA )
				{
					a = 255 ;
				}
				else
				{
                    a = 0 ;							
                   }					
                }
                
                _pixels[4*x+y*(long)_ftextureWIDTH*4] 	 = 	r ;				//r
                _pixels[4*x+y*(long)_ftextureWIDTH*4+1]	 =	g	 ;				//g
                _pixels[4*x+y*(long)_ftextureWIDTH*4+2]	 = b ;				//b
                _pixels[4*x+y*(long)_ftextureWIDTH*4+3] =	a  ;				//a							
                
            }	
        }
        
        break ;
        
        }
        
        //free the memory where we loaded the tga
        delete cxImagePtr ;
        cxImagePtr = NULL ;
        pixelPtr = NULL;
        
        glLoadIdentity( ) ;
        //genere un nom de texture		
        glGenTextures( 1 , &texture ) ;
        
        glDisable( GL_TEXTURE_2D ) ;
//        glDisable( GL_TEXTURE_RECTANGLE_NV ) ;
        glEnable( _glEnum ) ;
        
        glBindTexture(_glEnum, texture ) ;
        _oldBindedText = texture ;

        //getGLERR( 	glGetError( ) ,filename ) ;
        
        if ( hasalpha == K_ALPHA )
        {
            if ( true == hiDef )
            {
                glTexImage2D( _glEnum , 0 , GL_RGBA8       , (long)_ftextureWIDTH,(long)_ftextureHEIGHT ,0 , GL_RGBA     , GL_UNSIGNED_BYTE , _pixels ) ; 			
            }
            else
            {
                glTexImage2D( _glEnum , 0 , GL_RGBA       , (long)_ftextureWIDTH, (long)_ftextureHEIGHT ,0 , GL_RGBA     , GL_UNSIGNED_BYTE , _pixels ) ; 
            }
        }
        else
        {
            if ( true == hiDef )
            {
                glTexImage2D( _glEnum , 0 , GL_RGB8       , (long)_ftextureWIDTH, (long)_ftextureHEIGHT ,0 , GL_RGBA     , GL_UNSIGNED_BYTE , _pixels ) ; 
            }
            else
            {
                glTexImage2D( _glEnum , 0 , GL_RGB       , (long)_ftextureWIDTH, (long)_ftextureHEIGHT ,0 , GL_RGBA     , GL_UNSIGNED_BYTE , _pixels ) ; 
            }
        }
        
        
        setTextureQuality( _graphicQuality ) ;
        
        if ( _textureWrap == false )
        {
            glTexParameteri( _glEnum, GL_TEXTURE_WRAP_S,  GL_CLAMP);	
            glTexParameteri( _glEnum, GL_TEXTURE_WRAP_T,  GL_CLAMP );
        }
        else
        {
            glTexParameteri( _glEnum, GL_TEXTURE_WRAP_S,  GL_REPEAT);	
            glTexParameteri( _glEnum, GL_TEXTURE_WRAP_T,  GL_REPEAT );
        }
        
        //free the converted pixel buffer memory
        delete	[]	_pixels ;
        _pixels = NULL ;
        
        videoMemory += (long)_ftextureWIDTH*(long)_ftextureHEIGHT*( screenDepth / 8 ) ;
        
//        setCenterPoint( 0,0 ) ;
        
        return K_OK ;
}


bool			KGraphicGL::loadPicture3D( const	char	*filename , bool hiDef , bool hasalpha ) 
{
    unsigned 	char	*pixelPtr ;		
    long						newSize , i ,x,y ;
    long						imageWidth , imageHeight ;
    tgaBitmap				tgaInfo ;
    CxImage				*cxImagePtr ;		
    
    freePicture( ) ;
    
    cxImagePtr = (CxImage*)LoadGeneric( (char*)filename )  ; 	
    
    if ( cxImagePtr	== NULL )	
    {
        char msg[1024] ;
        strcpy( msg , "Could not load picture " ) ;
        strcat( msg , filename ) ;
        //	KMiscTools::messageBox(  filename,"file not found or out of memory" ) ;
        return	K_ERROR ;
    }
    
    
    tgaInfo.bpp = cxImagePtr->GetBpp( ) ;
    tgaInfo.width = cxImagePtr->GetWidth( ) ;
    tgaInfo.height = cxImagePtr->GetHeight( ) ;
    long ct = cxImagePtr->GetColorType( ) ;
    if ( ct == 4) 
    {
        tgaInfo.bpp  = 32 ;
    }
    
    //not sure this is useful, but opengl crashes if not present ( sometimes )
    glLoadIdentity();
    glFlush( ) ;
    
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    
    imageWidth		=	tgaInfo.width ; 
    imageHeight 		=	tgaInfo.height ; 
    
    fimageWidth	=	(float)imageWidth ;
    fimageHeight 	=	(float)imageHeight ;
//    picX1	=	tgaInfo.xstart ;
 //   picY1	=	tgaInfo.ystart ;
    
    newSize = imageWidth ;
    if ( imageHeight > imageWidth )			newSize 	=	imageHeight ;
    
    //calculate a multiple of 2 for the texture size
    i = 2 ;
    do
    {
        i *= 2 ;
    }while( i < newSize ) ;
    
    newSize = i ;	
    
    //does the card handle rectangular textures ?
    if (_rectangleTexCap == false  )
    {			
        //non
        _glEnum = GL_TEXTURE_2D ;
        _ftextureWIDTH 		=	(float)newSize ;
        _ftextureHEIGHT		=	(float)newSize ;
    }
    else
    {
        _glEnum =  GL_TEXTURE_RECTANGLE_NV ;
        _ftextureWIDTH 		=	(float)fimageWidth ;
        _ftextureHEIGHT		=	(float)fimageHeight ;
    }
    
    
    //square texture from the source, we force everything in gl_textire_2d !  ( less bugs! :)  )
    if ( i == _ftextureWIDTH && _ftextureWIDTH == _ftextureHEIGHT )
    {
        _glEnum = GL_TEXTURE_2D ;
        
        _ftextureWIDTH 		=	(float)newSize ;
        _ftextureHEIGHT		=	(float)newSize ;
    }
    
    _pixels = new unsigned char[(long)(_ftextureWIDTH*_ftextureHEIGHT*4)] ;
    memset( _pixels , 0 , (long)(_ftextureWIDTH*_ftextureHEIGHT*4) ) ;
    
    pixelPtr = (unsigned char*)cxImagePtr->GetBits( ) ;
    
    unsigned char r,g,b ,a;
    
    switch ( tgaInfo.bpp )
    {
    /*
    //du joli 24 bits
    case	24:
				for ( x =0 ; x < imageWidth ; x++)
                {
                for ( y = 0 ; y < imageHeight ; y++ )
                {
                r = pixelPtr[3*x+(imageHeight-y-1)*imageWidth*3+2] ;
                g = pixelPtr[3*x+(imageHeight-y-1)*imageWidth*3+1] ;
                b = pixelPtr[3*x+(imageHeight-y-1)*imageWidth*3+0] ;
                a = 255 ;
                
                  if ( _ckActive == true && _ckr == r && _ckb == b && _ckg == g )
                  {
                  a = 0 ;							
                  }
                  
                    _pixels[4*x+y*(long)_ftextureWIDTH*4] 	 = 	r ;				//r
                    _pixels[4*x+y*(long)_ftextureWIDTH*4+1]	 =	g	 ;				//g
                    _pixels[4*x+y*(long)_ftextureWIDTH*4+2]	 = b ;				//b
                    _pixels[4*x+y*(long)_ftextureWIDTH*4+3] =	a  ;				//a							
                    
                      }	
                      }
                      break ;
        */
        //du 32 bits avec alpha			
    case	32:
        //32 bits
        for ( x =0 ; x < imageWidth ; x++)
        {
            for ( y = 0 ; y < imageHeight ; y++ )
            {
                RGBQUAD color ;
                color = cxImagePtr->GetPixelColor( x , y , true ) ;
                
                r =   color.rgbRed  ;
                g = color.rgbGreen  ;
                b = color.rgbBlue ;
                a = color.rgbReserved  ;
                
                if ( _ckActive == true && _ckr == r && _ckb == b && _ckg == g )
                {
                    a = 0 ;							
                }
                
                _pixels[4*x+y*(long)_ftextureWIDTH*4] 	 = 	r ;				//r
                _pixels[4*x+y*(long)_ftextureWIDTH*4+1]	 =	g	 ;				//g
                _pixels[4*x+y*(long)_ftextureWIDTH*4+2]	 = b ;				//b
                _pixels[4*x+y*(long)_ftextureWIDTH*4+3] =	a  ;				//a							
                
            }	
        }
        
        /*
        for ( x =0 ; x < imageWidth*4 ; x+=4)
        {
        for ( y = 0 ; y < imageHeight ; y++ )
        {
        r = pixelPtr[x+(imageHeight-y-1)*imageWidth*4+2] ;
        g = pixelPtr[x+(imageHeight-y-1)*imageWidth*4+1] ;
        b = pixelPtr[x+(imageHeight-y-1)*imageWidth*4+0] ;
        a = pixelPtr[x+(imageHeight-y-1)*imageWidth*4+3] ;
        
          if ( _ckActive == true && _ckr == r && _ckb == b && _ckg == g )
          {
          a = 0 ;							
          }
          
            _pixels[x+y*(long)_ftextureWIDTH*4] 		= 	r	 ;				//r
            _pixels[x+y*(long)_ftextureWIDTH*4+1] 	=	g	 ;				//g
            _pixels[x+y*(long)_ftextureWIDTH*4+2] 	=	b	 ;				//b
            _pixels[x+y*(long)_ftextureWIDTH*4+3] 	=	a	 ;				//a
            }	
            }
        */
        break ;
    default:
        
        //8 or 16 or 24 bits
        for ( x =0 ; x < imageWidth ; x++)
        {
            for ( y = 0 ; y < imageHeight ; y++ )
            {
                RGBQUAD color ;
                color = cxImagePtr->GetPixelColor( x , y , false ) ;
                
                r =   color.rgbRed  ;
                g = color.rgbGreen  ;
                b = color.rgbBlue ;
                a = 255 ;
                
                if ( _ckActive == true && _ckr == r && _ckb == b && _ckg == g )
                {
                    a = 0 ;							
                }
                
                _pixels[4*x+y*(long)_ftextureWIDTH*4] 	 = 	r ;				//r
                _pixels[4*x+y*(long)_ftextureWIDTH*4+1]	 =	g	 ;				//g
                _pixels[4*x+y*(long)_ftextureWIDTH*4+2]	 = b ;				//b
                _pixels[4*x+y*(long)_ftextureWIDTH*4+3] =	a  ;				//a							
                
            }	
        }
        
        break ;
        
        }
        
        //free the memory where we loaded the tga
        delete cxImagePtr ;
        cxImagePtr = NULL ;
        pixelPtr = NULL;
        
        glLoadIdentity( ) ;
        //genere un nom de texture		
        glGenTextures( 1 , &texture ) ;
        
        glDisable( GL_TEXTURE_2D ) ;
//        glDisable( GL_TEXTURE_RECTANGLE_NV ) ;
        glEnable( _glEnum ) ;
        
        glBindTexture(_glEnum, texture ) ;
        _oldBindedText = texture ;
        
        //getGLERR( 	glGetError( ) ,filename ) ;
        
        if ( hasalpha == K_ALPHA )
        {
            if ( true == hiDef )
            {
                glTexImage2D( _glEnum , 0 , GL_RGBA8       , (long)_ftextureWIDTH,(long)_ftextureHEIGHT ,0 , GL_RGBA     , GL_UNSIGNED_BYTE , _pixels ) ; 			
            }
            else
            {
                glTexImage2D( _glEnum , 0 , GL_RGBA       , (long)_ftextureWIDTH, (long)_ftextureHEIGHT ,0 , GL_RGBA     , GL_UNSIGNED_BYTE , _pixels ) ; 
            }
        }
        else
        {
            if ( true == hiDef )
            {
                glTexImage2D( _glEnum , 0 , GL_RGB8       , (long)_ftextureWIDTH, (long)_ftextureHEIGHT ,0 , GL_RGBA     , GL_UNSIGNED_BYTE , _pixels ) ; 
            }
            else
            {
                glTexImage2D( _glEnum , 0 , GL_RGB       , (long)_ftextureWIDTH, (long)_ftextureHEIGHT ,0 , GL_RGBA     , GL_UNSIGNED_BYTE , _pixels ) ; 
            }
        }
        
        
       
        if ( _textureWrap == false )
        {
            glTexParameteri( _glEnum, GL_TEXTURE_WRAP_S,  GL_CLAMP);	
            glTexParameteri( _glEnum, GL_TEXTURE_WRAP_T,  GL_CLAMP );
        }
        else
        {
            glTexParameteri( _glEnum, GL_TEXTURE_WRAP_S,  GL_REPEAT);	
            glTexParameteri( _glEnum, GL_TEXTURE_WRAP_T,  GL_REPEAT );
        }
        
        //free the converted pixel buffer memory
        delete	[]	_pixels ;
        _pixels = NULL ;
        
        videoMemory += (long)_ftextureWIDTH*(long)_ftextureHEIGHT*( screenDepth / 8 ) ;
        
        //setCenterPoint( 0,0 ) ;
        
        return K_OK ;
}

void		getGLERR( GLenum g , char *t)
{
				if ( g != GL_NO_ERROR  )
                {
                    switch( g ) 
                    {
                    case	GL_INVALID_ENUM:
                        KMiscTools::messageBox( "GL_INVALID_ENUM" ,t ) ;
                        break ;
                    case	GL_INVALID_VALUE: 
                        KMiscTools::messageBox( "GL_INVALID_VALUE" , t) ;
                        break ;
                    case	GL_INVALID_OPERATION: 
                        KMiscTools::messageBox( "GL_INVALID_OPERATION" ,t ) ;
                        break ;
                    case	GL_STACK_OVERFLOW: 
                        KMiscTools::messageBox( "GL_STACK_OVERFLOW" ,t ) ;
                        break ;
                    case	GL_STACK_UNDERFLOW: 
                        KMiscTools::messageBox( "GL_STACK_UNDERFLOW" ,t ) ;
                        break ;
                    case	GL_OUT_OF_MEMORY: 
                        KMiscTools::messageBox( "GL_OUT_OF_MEMORY" ,t ) ;
                        break ;
                    }
                }
}



//Free texture
void		KGraphicGL::freePicture( void )
{
    _transPixX = -1 ;
    _transPixY = -1 ;


    if ( NULL != _pixels )
    {
        delete _pixels ;
        _pixels = NULL ;
    }
    
    //s'assure que la texture existe
    if ( fimageWidth > 0 )
    {
        videoMemory -= (long)_ftextureWIDTH*(long)_ftextureHEIGHT*( screenDepth / 8 ) ;
        glDeleteTextures( 1, &texture ) ;
        fimageWidth		= 0 ;
        fimageHeight		= 0 ;
    }
}
/*
void		KGraphicGL::draw16BitMatrix(	long	dx, long dy , unsigned short* PixelsMap ,long width,long height , float alpha) 
{
register long	px,py ;
register	float	r,g,b ;
register	long	rowbytes ;
register	unsigned short	pixelColor ;

  
    glEnable( GL_BLEND ) ;
    glDisable( GL_TEXTURE_2D ) ;
    glDisable( GL_TEXTURE_RECTANGLE_NV ) ;
    
      glBegin (GL_POINTS);
      //103 93
      for ( py = 0 ; py < height; py++ )
      {	
      rowbytes = py*width ;
      for ( px = 0 ; px < width ; px++ )
      {	  			
      pixelColor = PixelsMap[px+rowbytes] ;
      b = ((float)(pixelColor & 0x1f) )/31.0f  ;
      g = ((float)((pixelColor>>5) & 0x1f) )/31.0f ;
      r = ((float)((pixelColor>>10) & 0x1f ))/31.0f  ;
      
        glColor4f( r , g , b , alpha ) ;
        glVertex2f ((float)px+dx,(float)((screenHeight-dy)-py));					
        }
        }
        
          glEnd( ) ;
          
            glColor4f( 1 , 1 , 1 ,1 ) ;
            glDisable( GL_BLEND ) ;
            glEnable( GL_TEXTURE_2D) ;
            }
*/
//stocke la taille ecran, necessaire pour le blit ( pour le systeme de coordonnees )
void		KGraphicGL::setScreenSize( short		swidth , short	sheight  , short sdepth ) 
{
    screenWidth 	= swidth ;
    screenHeight = sheight ;
    screenDepth = sdepth ;
    
    glEnable( GL_TEXTURE_2D ) ;
    glShadeModel(GL_FLAT );
}



/*
//sets the center point of the sprite ( for rotations )
void		KGraphicGL::setCenterPoint( float	 cx,float cy )
{
    _centerX = cx ;
    _centerY = cy ;
}
*/

//sub pixel blitting
//**************
void			KGraphicGL::blitRectF( float	x1, float y1 , float	x2 , float y2 , float	destX , float	destY , bool flipx  , bool flipy ) 
{
    ptk_glBindTexture();
    glDisable( GL_BLEND ) ;
    
    destY	 = (float)screenHeight -destY ;
    
  
    glPushMatrix();
    GenericBlitF( x1 , y1 , x2 , y2 , destX , destY , flipx , flipy ) ;
    glPopMatrix();
}

void			KGraphicGL::blitRectFxF( float	x1, float y1 , float	x2 , float y2 , float destX , float	destY, float angle, float zoom, bool flipx , bool flipy) 
{
   float		middlesizeX , middlesizeY ;
    
    if ( zoom == 0 )	return ;
    
    middlesizeX	=	(x2-x1)/2 ;
    middlesizeY	=	(y2-y1)/2 ;
    
    glMatrixMode( GL_MODELVIEW) ;
    glPushMatrix();		//sauvegarde la matrice en cours
    
    destY	 = (float)screenHeight -destY ;
    glTranslatef( (float)destX+middlesizeX ,(float)(destY)-middlesizeY  , 0  ) ;
    glRotatef( angle , 0.0f , 0.0f ,1.0f ) ; 	
    
    glScalef( zoom ,zoom , 0 ) ;
    
    ptk_glBindTexture();
    glDisable( GL_BLEND ) ;
    
    
    glPushMatrix( ) ;
    GenericBlitF( x1 , y1 , x2 , y2 , (float)-middlesizeX , (float)middlesizeY , flipx , flipy ) ;
    glPopMatrix( ) ;
    
    
    glMatrixMode( GL_MODELVIEW ) ;
    glPopMatrix();		//sauvegarde la matrice e
}

//alpha rect for sub  pixels
void			KGraphicGL::blitAlphaRectF( float	x1, float y1 , float	x2 , float y2 , float destX , float	destY, bool flipx  , bool  flipy ) 
{
    ptk_glBindTexture();
    glEnable( GL_BLEND ) ;
    glBlendFunc(  _sourceAlpha , _destAlpha  );	
    
    destY	 = (float)screenHeight -destY ;
    
    	if ( _blitColorChanged == true )
	{
		glColor4f( _blitRed ,_blitGreen , _blitBlue , _blitAlpha  ) ;
	}
	else
	{
		glColor4f( 1.0f,1.0f,1.0f,1.0f) ;
	}
	
    glPushMatrix( ) ;
    GenericBlitF( x1 , y1 , x2 , y2 , destX , destY , flipx , flipy ) ;
    glPopMatrix( ) ;

}

//alpha rectfx for sub  pixels
void			KGraphicGL::blitAlphaRectFxF( float	x1, float y1 , float	x2 , float y2 , float 	destX , float	destY, float angle, float zoom,
						 float blend , bool flipx  , bool flipy  , float centerX, float centerY )  
{
bool translated ;

    float		middlesizeX , middlesizeY ;
    
    
    if ( zoom == 0  )		return ;
    if ( blend <= 0 )	 	return ;
    

    
    middlesizeX	=	(x2-x1)/2 + centerX ;
    middlesizeY	=	(y2-y1)/2 + centerY ;
    
   
    
    destY	 = (float)screenHeight -destY ;
    //	glMatrixMode( GL_MODELVIEW) ;
    glPushMatrix();		//sauvegarde la matrice en cours
    
    translated = false ;
    
     if ( zoom == 1 )
   {
   	 	if ( _zoomX != 1 || _zoomY != 1 )
   	 	{     
   	 		translated =true;
      	 	 glTranslatef( (float)destX+middlesizeX ,(float)(destY)-middlesizeY  , 0  ) ;  	 		
   	 		glScalef(_zoomX ,_zoomY , 0 ) ;
   	 	}
   }
  
    if ( angle != 0 || zoom != 1 )
    {
		if ( translated == false )
		{
		      glTranslatef( (float)destX+middlesizeX ,(float)(destY)-middlesizeY  , 0  ) ;
      	}  
       
        if ( angle != 0 )
        {
            glRotatef( angle , 0.0f , 0.0f ,1.0f ) ; 	
        }
        
        if ( zoom != 1 )
        {
            glScalef( zoom  * _zoomX ,zoom* _zoomY , 0 ) ;
        }
    }
    
   
    	if ( _blitColorChanged == true )
	{
		glColor4f( _blitRed ,_blitGreen , _blitBlue , _blitAlpha * blend ) ;
	}
	else
	{
		 if ( blend >= 0 )	 glColor4f( 1.0f,1.0f,1.0f,blend) ;
	}
    
    ptk_glBindTexture();
    glEnable( GL_BLEND ) ;
    glBlendFunc(  _sourceAlpha , _destAlpha  );	
    
    glPushMatrix( ) ;
    if ( angle != 0 || zoom != 1 || _zoomX != 1 ||  _zoomY != 1 )
    {
        GenericBlitF( x1 , y1 , x2 , y2 , -middlesizeX , middlesizeY , flipx , flipy ) ;
    }
    else
    {
        GenericBlitF( x1 , y1 , x2 , y2 , destX , destY , flipx , flipy ) ;
    }
    glPopMatrix( ) ;
				
    glColor4f( 1.0f,1.0f,1.0f,1.0f) ;
    
    //	glMatrixMode( GL_MODELVIEW ) ;
    glPopMatrix();		//sauvegarde la matrice en cours
    
}


//**************

//no alpha stuff, the fastest we can get ?
void		KGraphicGL::blitRect( float	x1, float y1 , float	x2 , float y2 , short	destX , short	destY , bool flipx , bool flipy )
{
    ptk_glBindTexture();
    glDisable( GL_BLEND ) ;
    
    destY	 = screenHeight -destY ;
    
  
    glPushMatrix();
    GenericBlit( x1 , y1 , x2 , y2 , destX , destY , flipx , flipy ) ;
    glPopMatrix();
}


void		KGraphicGL::stretchAlphaRect( float	sx1, float sy1 , float	sx2 , float sy2 , float	dx1, float dy1 , float	dx2 , float dy2, float blend, float angle , bool flipx, bool flipy , float centerX, float centerY)
{
	
    if ( blend >= 0 && blend != 1 )	 glColor4f( 1.0f,1.0f,1.0f,blend) ;
    ptk_glBindTexture();
    glEnable( GL_BLEND ) ;
    glBlendFunc(  _sourceAlpha , _destAlpha );
    
    float middlesizeX	=	(dx2-dx1)/2 +centerX;
    float middlesizeY	=	(dy2-dy1)/2 +centerY;

    dy1	 = screenHeight -dy1 ;
    dy2	 = screenHeight -dy2 ;
    
    
  if ( _blitColorChanged == true ) 
     { 
          glColor4f( _blitRed ,_blitGreen , _blitBlue , _blitAlpha * blend ) ; 
     } 
     else 
     { 
	        if ( blend >= 0 && blend != 1 ) 
	        { 
	            glColor4f( 1.0f,1.0f,1.0f,blend) ; 
	        } 
	        else 
	        { 
	              glColor4f( 1.0f,1.0f,1.0f,1.0f) ; 
	        } 
     }
     
     
    glPushMatrix();
    if ( angle != 0)
    {
        glTranslatef( (float)dx1+middlesizeX ,(float)(dy1)-middlesizeY  , 0  ) ;
        
        
        if ( angle != 0 )
        {
            glRotatef( angle , 0.0f , 0.0f ,1.0f ) ; 	
        }
    }
    if (angle != 0)
    {
        genericStretchBlit( sx1 , sy1 , sx2 , sy2 , -middlesizeX ,middlesizeY, -middlesizeX + (dx2 - dx1) , middlesizeY + (dy2 - dy1) , flipx,flipy) ;	
    }
    else
    {
        genericStretchBlit( sx1 , sy1 , sx2 , sy2 , dx1 ,dy1 , dx2 , dy2 ,  flipx,flipy  ) ;	
    }  
    
     glColor4f( 1.0f,1.0f,1.0f,1.0f) ;
    glPopMatrix();
}


// blit no alpha but with effects
void		KGraphicGL::blitRectFx( float	x1, float y1 , float	x2 , float y2 , short	destX , short	destY, float angle, float zoom, bool flipx , bool flipy)
{
    float		middlesizeX , middlesizeY ;
    
    if ( zoom == 0 )	return ;
    
    middlesizeX	=	(x2-x1)/2 ;
    middlesizeY	=	(y2-y1)/2 ;
    
    glMatrixMode( GL_MODELVIEW) ;
    glPushMatrix();		//sauvegarde la matrice en cours
    
    destY	 = screenHeight -destY ;
    glTranslatef( (float)destX+middlesizeX ,(float)(destY)-middlesizeY  , 0  ) ;
    glRotatef( angle , 0.0f , 0.0f ,1.0f ) ; 	
    
    glScalef( zoom ,zoom , 0 ) ;
    
    ptk_glBindTexture();
    glDisable( GL_BLEND ) ;
    
    
    glPushMatrix( ) ;
    GenericBlit( x1 , y1 , x2 , y2 , (float)-middlesizeX , (float)middlesizeY , flipx , flipy ) ;
    glPopMatrix( ) ;
    
    
    glMatrixMode( GL_MODELVIEW ) ;
    glPopMatrix();		//sauvegarde la matrice e
}


//blit used for all the function
inline		void		KGraphicGL::genericStretchBlit( float	sx1 , float	sy1 , float	sx2 , float	sy2 , float	dx1 ,float	dy1 , float	dx2 , float	dy2  , bool flipx,bool flipy) 
{
    glPushMatrix( ) ;
    
    
    if ( _glEnum == GL_TEXTURE_2D)
    {
        //glDisable(GL_TEXTURE_RECTANGLE_NV ) ;
        //glEnable(GL_TEXTURE_2D ) ;
        
        
        glBegin(GL_QUADS);
        
       	if ( flipx == false && flipy == false )
        	{
        		glTexCoord2f( sx1/_ftextureWIDTH ,sy1/_ftextureHEIGHT ); 		glVertex3i( dx1,dy1, 0);  
        		glTexCoord2f( sx1/_ftextureWIDTH ,sy2/_ftextureHEIGHT );  		glVertex3i( dx1, dy2, 0);
       		glTexCoord2f( sx2/_ftextureWIDTH ,sy2/_ftextureHEIGHT );  		glVertex3i( dx2, dy2,0);
	   		glTexCoord2f( sx2/_ftextureWIDTH ,sy1/_ftextureHEIGHT  );		glVertex3i( dx2, dy1, 0);	    	    		
	   	}


       	if ( flipx == false && flipy == true )
       	{
		    	glTexCoord2f( sx1/_ftextureWIDTH ,sy2/_ftextureHEIGHT ); 		glVertex3i( dx1,dy1, 0);  
    			glTexCoord2f( sx1/_ftextureWIDTH ,sy1/_ftextureHEIGHT );  		glVertex3i( dx1, dy2, 0);
    			glTexCoord2f( sx2/_ftextureWIDTH ,sy1/_ftextureHEIGHT );  		glVertex3i( dx2, dy2,0);
    			glTexCoord2f( sx2/_ftextureWIDTH ,sy2/_ftextureHEIGHT  );		glVertex3i( dx2, dy1, 0);	    	 
    		}

	   	if ( flipx == true && flipy == false )
	   	{
	   	
    			glTexCoord2f( sx2/_ftextureWIDTH ,sy1/_ftextureHEIGHT ); 		glVertex3i( dx1,dy1, 0);  
    			glTexCoord2f( sx2/_ftextureWIDTH ,sy2/_ftextureHEIGHT );  		glVertex3i( dx1, dy2, 0);
    			glTexCoord2f( sx1/_ftextureWIDTH ,sy2/_ftextureHEIGHT );  		glVertex3i( dx2, dy2,0);
    			glTexCoord2f( sx1/_ftextureWIDTH ,sy1/_ftextureHEIGHT  );		glVertex3i( dx2, dy1, 0);	    	    		
    		}
	    	
	   	if ( flipx == true && flipy == true )
	   	{
    			glTexCoord2f( sx2/_ftextureWIDTH ,sy2/_ftextureHEIGHT ); 		glVertex3i( dx1,dy1, 0);  
    			glTexCoord2f( sx2/_ftextureWIDTH ,sy1/_ftextureHEIGHT );  		glVertex3i( dx1, dy2, 0);
    			glTexCoord2f( sx1/_ftextureWIDTH ,sy1/_ftextureHEIGHT );  		glVertex3i( dx2, dy2,0);
    			glTexCoord2f( sx1/_ftextureWIDTH ,sy2/_ftextureHEIGHT  );		glVertex3i( dx2, dy1, 0);	    	    		
		}
    			
        glEnd();
    }
    else
    {
      	  glBegin(GL_QUADS);
        
       	if ( flipx == false && flipy == false )
        	{
        		glTexCoord2f( sx1 ,sy1 ); 		glVertex3i( dx1,dy1, 0);  
        		glTexCoord2f( sx1 ,sy2 );  		glVertex3i( dx1, dy2, 0);
       		glTexCoord2f( sx2 ,sy2 );  		glVertex3i( dx2, dy2,0);
	   		glTexCoord2f( sx2 ,sy1  );		glVertex3i( dx2, dy1, 0);	    	    		
	   	}


       	if ( flipx == false && flipy == true )
       	{
		    	glTexCoord2f( sx1 ,sy2 ); 		glVertex3i( dx1,dy1, 0);  
    			glTexCoord2f( sx1 ,sy1 );  		glVertex3i( dx1, dy2, 0);
    			glTexCoord2f( sx2 ,sy1 );  		glVertex3i( dx2, dy2,0);
    			glTexCoord2f( sx2 ,sy2  );		glVertex3i( dx2, dy1, 0);	    	 
    		}

	   	if ( flipx == true && flipy == false )
	   	{
	   	
    			glTexCoord2f( sx2 ,sy1 ); 		glVertex3i( dx1,dy1, 0);  
    			glTexCoord2f( sx2 ,sy2 );  		glVertex3i( dx1, dy2, 0);
    			glTexCoord2f( sx1 ,sy2 );  		glVertex3i( dx2, dy2,0);
    			glTexCoord2f( sx1 ,sy1  );		glVertex3i( dx2, dy1, 0);	    	    		
    		}
	    	
	   	if ( flipx == true && flipy == true )
	   	{
    			glTexCoord2f( sx2 ,sy2 ); 		glVertex3i( dx1,dy1, 0);  
    			glTexCoord2f( sx2 ,sy1 );  		glVertex3i( dx1, dy2, 0);
    			glTexCoord2f( sx1 ,sy1 );  		glVertex3i( dx2, dy2,0);
    			glTexCoord2f( sx1 ,sy2  );		glVertex3i( dx2, dy1, 0);	    	    		
		}
    			
        glEnd();	


    }
    glPopMatrix();
    
}

void		KGraphicGL::genericArbitraryBlit( 	float	sx1 , float	sy1 , float	sx2 , float	sy2 , float	sx3 ,float	sy3 , float	sx4 , float	sy4 , 
                                           float	dx1 , float	dy1 , float	dx2 , float	dy2 , float	dx3 ,float	dy3 , float	dx4 , float	dy4 )													
{
    glPushMatrix( ) ;
    
    
    if ( _glEnum == GL_TEXTURE_2D)
    {
        //	glDisable(GL_TEXTURE_RECTANGLE_NV ) ;
        //	glEnable(GL_TEXTURE_2D ) ;
        
        
        glBegin(GL_QUADS);
        glTexCoord2f( sx1/_ftextureWIDTH ,sy1/_ftextureHEIGHT ); 		glVertex3i( dx1,dy1, 0);  
        glTexCoord2f( sx2/_ftextureWIDTH ,sy2/_ftextureHEIGHT ); 		glVertex3i( dx2,dy2, 0);  
        glTexCoord2f( sx3/_ftextureWIDTH ,sy3/_ftextureHEIGHT ); 		glVertex3i( dx3,dy3, 0);  
        glTexCoord2f( sx4/_ftextureWIDTH ,sy4/_ftextureHEIGHT ); 		glVertex3i( dx4,dy4, 0);  
        glEnd();
    }
    else
    {
//        glEnable(GL_TEXTURE_RECTANGLE_NV ) ;
//        glDisable(GL_TEXTURE_2D ) ;
        
        glBegin(GL_QUADS);
        glTexCoord2f( sx1 ,sy1 ); 		glVertex3i( dx1,dy1, 0);  
        glTexCoord2f( sx2 ,sy2 );  		glVertex3i( dx2, dy2, 0);
        glTexCoord2f( sx3 ,sy3 );  		glVertex3i( dx3, dy3,0);
			     glTexCoord2f( sx4 ,sy4  );		glVertex3i( dx4, dy4, 0);	    	    		
                 glEnd();		
    }
    glPopMatrix();
    
}

void					KGraphicGL::setRectangleTexSupport( bool rsupport )
{
rsupport = rsupport ;  //patch
	_rectangleTexCap = false ;
}

//does a bind
void					KGraphicGL::selectTexture( void )
{
//    glDisable( GL_TEXTURE_RECTANGLE_NV ) ;
    glEnable( GL_TEXTURE_2D ) ;
    
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,  GL_REPEAT);	
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,  GL_REPEAT );
    
    
    ptk_glBindTexture();
}

//blit used for all the function
inline		void		KGraphicGL::GenericBlit(  float	x1, float y1 , float	x2 , float y2 , short	destX , short	destY , bool flipx , bool flipy ) 
{

    //textures rectangulaires
    if ( _glEnum == GL_TEXTURE_RECTANGLE_NV ) 
    {
        //	glDisable( GL_TEXTURE_2D ) ;
        
        if ( flipx == false && flipy == false )
        {
            glBegin(GL_QUADS);
            
            glTexCoord2f( x1 ,y1 ); 		glVertex3i( destX,destY, 0);  
            glTexCoord2f( x1 ,y2 );  		glVertex3i( destX, destY-(short)(y2-y1), 0);
            glTexCoord2f( x2 ,y2 );  		glVertex3i( destX+(short)(x2-x1), destY-(short)(y2-y1),0);
            glTexCoord2f( x2 ,y1  );		glVertex3i( destX+(short)(x2-x1), destY, 0);	    	    		
            
            glEnd();
            return ;
        }
        
        if ( flipx == true && flipy == true )
        {
            glBegin(GL_QUADS);
            glTexCoord2f( x2 ,y2 ); 		glVertex3i( destX,destY, 0);  
            glTexCoord2f( x2 ,y1 );  		glVertex3i( destX, destY-(short)(y2-y1), 0);
            glTexCoord2f( x1 ,y1 );  		glVertex3i( destX+(short)(x2-x1), destY-(short)(y2-y1),0);
            glTexCoord2f( x1 ,y2  );		glVertex3i( destX+(short)(x2-x1), destY, 0);	    	    	
            glEnd();
            return ;
        } 
        
        if ( flipx == true && flipy == false )
        {
            glBegin(GL_QUADS);
            glTexCoord2f( x2 ,y1 ); 		glVertex3i( destX,destY, 0);  
            glTexCoord2f( x2 ,y2 );  		glVertex3i( destX, destY-(short)(y2-y1), 0);
            glTexCoord2f( x1 ,y2 );  		glVertex3i( destX+(short)(x2-x1), destY-(short)(y2-y1),0);
            glTexCoord2f( x1 ,y1  );		glVertex3i( destX+(short)(x2-x1), destY, 0);	    	    	
            glEnd();
            return ;
        } 
        
        
        //		if ( flipx == false  && flipy == true )
        glBegin(GL_QUADS);
        glTexCoord2f( x1 ,y2 ); 		glVertex3i( destX,destY, 0);  
        glTexCoord2f( x1 ,y1 ); 	 	glVertex3i( destX, destY-(short)(y2-y1), 0);
        glTexCoord2f( x2 ,y1 ); 	 	glVertex3i( destX+(short)(x2-x1), destY-(short)(y2-y1),0);
        glTexCoord2f( x2 ,y2  );		glVertex3i( destX+(short)(x2-x1), destY, 0);	    	    	
        
        glEnd();
        
        return ;
    }
    
    //texture carrées
    //		glDisable( GL_TEXTURE_RECTANGLE_NV ) ;
    
    //		ptk_glBindTexture();
    
    if ( flipx == false && flipy == false )
    {
        glBegin(GL_QUADS);
        
        glTexCoord2f( x1/_ftextureWIDTH ,y1/_ftextureHEIGHT ); 		glVertex3i( destX,destY, 0);  
        glTexCoord2f( x1/_ftextureWIDTH ,y2/_ftextureHEIGHT );  	glVertex3i( destX, destY-(short)(y2-y1), 0);
        glTexCoord2f( x2/_ftextureWIDTH ,y2/_ftextureHEIGHT );  	glVertex3i( destX+(short)(x2-x1), destY-(short)(y2-y1),0);
        glTexCoord2f( x2/_ftextureWIDTH ,y1/_ftextureHEIGHT  );		glVertex3i( destX+(short)(x2-x1), destY, 0);	    	    		
        
        glEnd();
        return ;
    }
    
    if ( flipx == true && flipy == true )
    {
        glBegin(GL_QUADS);
        glTexCoord2f( x2/_ftextureWIDTH ,y2/_ftextureHEIGHT ); 		glVertex3i( destX,destY, 0);  
        glTexCoord2f( x2/_ftextureWIDTH ,y1/_ftextureHEIGHT );  	glVertex3i( destX, destY-(short)(y2-y1), 0);
        glTexCoord2f( x1/_ftextureWIDTH ,y1/_ftextureHEIGHT );  	glVertex3i( destX+(short)(x2-x1), destY-(short)(y2-y1),0);
        glTexCoord2f( x1/_ftextureWIDTH ,y2/_ftextureHEIGHT  );		glVertex3i( destX+(short)(x2-x1), destY, 0);	    	    	
        glEnd();
        return ;
    } 
    
    if ( flipx == true && flipy == false )
    {
        glBegin(GL_QUADS);
        glTexCoord2f( x2/_ftextureWIDTH ,y1/_ftextureHEIGHT ); 		glVertex3i( destX,destY, 0);  
        glTexCoord2f( x2/_ftextureWIDTH ,y2/_ftextureHEIGHT );  	glVertex3i( destX, destY-(short)(y2-y1), 0);
        glTexCoord2f( x1/_ftextureWIDTH ,y2/_ftextureHEIGHT );  	glVertex3i( destX+(short)(x2-x1), destY-(short)(y2-y1),0);
        glTexCoord2f( x1/_ftextureWIDTH ,y1/_ftextureHEIGHT  );		glVertex3i( destX+(short)(x2-x1), destY, 0);	    	    	
        glEnd();
        return ;
    } 
    
    
    //		if ( flipx == false  && flipy == true )
    glBegin(GL_QUADS);
    glTexCoord2f( x1/_ftextureWIDTH ,y2/_ftextureHEIGHT ); 		glVertex3i( destX,destY, 0);  
    glTexCoord2f( x1/_ftextureWIDTH ,y1/_ftextureHEIGHT );  	glVertex3i( destX, destY-(short)(y2-y1), 0);
	 		glTexCoord2f( x2/_ftextureWIDTH ,y1/_ftextureHEIGHT );  	glVertex3i( destX+(short)(x2-x1), destY-(short)(y2-y1),0);
            glTexCoord2f( x2/_ftextureWIDTH ,y2/_ftextureHEIGHT  );		glVertex3i( destX+(short)(x2-x1), destY, 0);	    	    	
            
            glEnd();
            
}



//blit used for all the function
inline		void		KGraphicGL::GenericBlitF(  float	x1, float y1 , float	x2 , float y2 , float	destX , float	destY , bool flipx , bool flipy ) 
{

    //textures rectangulaires
    if ( _glEnum == GL_TEXTURE_RECTANGLE_NV ) 
    {
        //	glDisable( GL_TEXTURE_2D ) ;
        
        if ( flipx == false && flipy == false )
        {
            glBegin(GL_QUADS);
            
            glTexCoord2f( x1 ,y1 ); 		glVertex3f( destX,destY, 0);  
            glTexCoord2f( x1 ,y2 );  		glVertex3f( destX, destY-(y2-y1), 0);
            glTexCoord2f( x2 ,y2 );  		glVertex3f( destX+(x2-x1), destY-(y2-y1),0);
            glTexCoord2f( x2 ,y1  );		glVertex3f( destX+(x2-x1), destY, 0);	    	    		
            
            glEnd();
            return ;
        }
        
        if ( flipx == true && flipy == true )
        {
            glBegin(GL_QUADS);
            glTexCoord2f( x2 ,y2 ); 		glVertex3f( destX,destY, 0);  
            glTexCoord2f( x2 ,y1 );  		glVertex3f( destX, destY-(y2-y1), 0);
            glTexCoord2f( x1 ,y1 );  		glVertex3f( destX+(x2-x1), destY-(y2-y1),0);
            glTexCoord2f( x1 ,y2  );		glVertex3f( destX+(x2-x1), destY, 0);	    	    	
            glEnd();
            return ;
        } 
        
        if ( flipx == true && flipy == false )
        {
            glBegin(GL_QUADS);
            glTexCoord2f( x2 ,y1 ); 		glVertex3f( destX,destY, 0);  
            glTexCoord2f( x2 ,y2 );  		glVertex3f( destX, destY-(y2-y1), 0);
            glTexCoord2f( x1 ,y2 );  		glVertex3f( destX+(x2-x1), destY-(y2-y1),0);
            glTexCoord2f( x1 ,y1  );		glVertex3f( destX+(x2-x1), destY, 0);	    	    	
            glEnd();
            return ;
        } 
        
        
        //		if ( flipx == false  && flipy == true )
        glBegin(GL_QUADS);
        glTexCoord2f( x1 ,y2 ); 		glVertex3f( destX,destY, 0);  
        glTexCoord2f( x1 ,y1 ); 	 	glVertex3f( destX, destY-(y2-y1), 0);
        glTexCoord2f( x2 ,y1 ); 	 	glVertex3f( destX+(x2-x1), destY-(y2-y1),0);
        glTexCoord2f( x2 ,y2  );		glVertex3f( destX+(x2-x1), destY, 0);	    	    	
        
        glEnd();
        
        return ;
    }
    
    //texture carrées
    //		glDisable( GL_TEXTURE_RECTANGLE_NV ) ;
    
    //		ptk_glBindTexture();
    
    if ( flipx == false && flipy == false )
    {
        glBegin(GL_QUADS);
        
        glTexCoord2f( x1/_ftextureWIDTH ,y1/_ftextureHEIGHT ); 		glVertex3f( destX,destY, 0);  
        glTexCoord2f( x1/_ftextureWIDTH ,y2/_ftextureHEIGHT );  	glVertex3f( destX, destY-(y2-y1), 0);
        glTexCoord2f( x2/_ftextureWIDTH ,y2/_ftextureHEIGHT );  	glVertex3f( destX+(x2-x1), destY-(y2-y1),0);
        glTexCoord2f( x2/_ftextureWIDTH ,y1/_ftextureHEIGHT  );		glVertex3f( destX+(x2-x1), destY, 0);	    	    		
        
        glEnd();
        return ;
    }
    
    if ( flipx == true && flipy == true )
    {
        glBegin(GL_QUADS);
        glTexCoord2f( x2/_ftextureWIDTH ,y2/_ftextureHEIGHT ); 		glVertex3f( destX,destY, 0);  
        glTexCoord2f( x2/_ftextureWIDTH ,y1/_ftextureHEIGHT );  	glVertex3f( destX, destY-(y2-y1), 0);
        glTexCoord2f( x1/_ftextureWIDTH ,y1/_ftextureHEIGHT );  	glVertex3f( destX+(x2-x1), destY-(y2-y1),0);
        glTexCoord2f( x1/_ftextureWIDTH ,y2/_ftextureHEIGHT  );		glVertex3f( destX+(x2-x1), destY, 0);	    	    	
        glEnd();
        return ;
    } 
    
    if ( flipx == true && flipy == false )
    {
        glBegin(GL_QUADS);
        glTexCoord2f( x2/_ftextureWIDTH ,y1/_ftextureHEIGHT ); 		glVertex3f( destX,destY, 0);  
        glTexCoord2f( x2/_ftextureWIDTH ,y2/_ftextureHEIGHT );  	glVertex3f( destX, destY-(y2-y1), 0);
        glTexCoord2f( x1/_ftextureWIDTH ,y2/_ftextureHEIGHT );  	glVertex3f( destX+(x2-x1), destY-(y2-y1),0);
        glTexCoord2f( x1/_ftextureWIDTH ,y1/_ftextureHEIGHT  );		glVertex3f( destX+(x2-x1), destY, 0);	    	    	
        glEnd();
        return ;
    } 
    
    
    //		if ( flipx == false  && flipy == true )
    glBegin(GL_QUADS);
    glTexCoord2f( x1/_ftextureWIDTH ,y2/_ftextureHEIGHT ); 		glVertex3f( destX,destY, 0);  
    glTexCoord2f( x1/_ftextureWIDTH ,y1/_ftextureHEIGHT );  	glVertex3f( destX, destY-(y2-y1), 0);
	 		glTexCoord2f( x2/_ftextureWIDTH ,y1/_ftextureHEIGHT );  	glVertex3f( destX+(x2-x1), destY-(y2-y1),0);
            glTexCoord2f( x2/_ftextureWIDTH ,y2/_ftextureHEIGHT  );		glVertex3f( destX+(x2-x1), destY, 0);	    	    	
            
            glEnd();
            
}


//blit tiling the texture
void		KGraphicGL::blitTiledRect(short	destX , short	destY , short		width , short	height ,  float tileFactor ,float angle )
{
    float		middlesizeX , middlesizeY ;
    
    
    middlesizeX	=	(float)(width/2) ;
    middlesizeY	=	(float)(height/2) ;
    
    glDisable( GL_BLEND ) ;
    
    //on supprime le clamping
    //	glTexParameteri( _glEnum, GL_TEXTURE_WRAP_S,  GL_REPEAT );	//GL_CLAMP_TO_EDGE  sur mac peut etre
    //	glTexParameteri( _glEnum, GL_TEXTURE_WRAP_T,  GL_REPEAT );
    
    
    destY	 = screenHeight -destY ;
    
    ptk_glBindTexture();
    
    glMatrixMode( GL_MODELVIEW) ;
    glPushMatrix();		//sauvegarde la matrice en cours
    
    glTranslatef( (float)destX+middlesizeX ,(float)(destY)-middlesizeY  , 0  ) ;
    glRotatef( angle , 0.0f , 0.0f ,1.0f ) ; 	
    
    if (	_glEnum ==  GL_TEXTURE_RECTANGLE_NV )
    {
        glBegin(GL_QUADS);
        glTexCoord2f( _ftextureWIDTH , _ftextureHEIGHT ); 					glVertex3i( -middlesizeX,middlesizeY, 0);  
        glTexCoord2f( _ftextureWIDTH , 0 );  							glVertex3i( -middlesizeX, -middlesizeY, 0);
        glTexCoord2f(0 , 0 );  										glVertex3i( middlesizeX, -middlesizeY,0);
			     glTexCoord2f( 0 , _ftextureHEIGHT  );							glVertex3i( middlesizeX , middlesizeY, 0);	    	    		
                 glEnd( );
    }
    else
    {
        glBegin(GL_QUADS);
        glTexCoord2f( (float)tileFactor , (float)tileFactor ); 					glVertex3i( -middlesizeX,middlesizeY, 0);  
        glTexCoord2f( (float)tileFactor , 0 );  							glVertex3i( -middlesizeX, -middlesizeY, 0);
        glTexCoord2f(0 , 0 );  										glVertex3i( middlesizeX, -middlesizeY,0);
			     glTexCoord2f( 0 , (float)tileFactor  );							glVertex3i( middlesizeX , middlesizeY, 0);	    	    		
                 glEnd( );
    }
    
    glMatrixMode( GL_MODELVIEW ) ;
    glPopMatrix();		//sauvegarde la matrice en cours
    
    //on restore le clamping
    //	glTexParameteri( _glEnum, GL_TEXTURE_WRAP_S,  GL_CLAMP );	//GL_CLAMP_TO_EDGE  sur mac peut etre
    //	glTexParameteri( _glEnum, GL_TEXTURE_WRAP_T,  GL_CLAMP );
    
    
}

//blit taking care of the alpha channel
void		KGraphicGL::blitAlphaRect( float	x1, float y1 , float	x2 , float y2 , short	destX , short	destY , bool flipx , bool flipy )
{
    ptk_glBindTexture();
    glEnable( GL_BLEND ) ;
    glBlendFunc(  _sourceAlpha , _destAlpha  );	
    
    destY	 = screenHeight -destY ;
    
    	if ( _blitColorChanged == true )
	{
		glColor4f( _blitRed ,_blitGreen , _blitBlue , _blitAlpha  ) ;
	}
	else
	{
		glColor4f( 1.0f,1.0f,1.0f,1.0f) ;
	}
	
    glPushMatrix( ) ;
    GenericBlit( x1 , y1 , x2 , y2 , destX , destY , flipx , flipy ) ;
    glPopMatrix( ) ;
    
}

//blit for tga with coordinates
void		KGraphicGL::blitAlphaRect( void )
{
    
    ptk_glBindTexture();
    glEnable( GL_BLEND ) ;
    glBlendFunc(  _sourceAlpha , _destAlpha  );	
    
    float	destY	 = screenHeight -picY1 ;
    
    glPushMatrix( ) ;
    GenericBlit( 0,0,fimageWidth , fimageHeight , picX1 ,destY, false,false ) ;
    glPopMatrix( ) ;
    
}

void		KGraphicGL::setAlphaMode( long	alphamodeSource, long alphamodeDest )
{
	        _sourceAlpha 	=  alphamodeSource ;
	        _destAlpha		=	alphamodeDest ;
}

//regular == true pour TGA  false pour additif
void		KGraphicGL::setAlphaMode( long	alphamode )
{
	switch( alphamode) 
	{
    		//additive
    		case	0:
	        _sourceAlpha 	=  GL_SRC_ALPHA ;
	        _destAlpha		=	GL_DST_ALPHA ;
    		break;
    		//normal
		case	1:
	        _sourceAlpha 	=  GL_SRC_ALPHA ;
	        _destAlpha		=	GL_ONE_MINUS_SRC_ALPHA ;
    		break ;
	 	case	2:
	    	   _sourceAlpha 		=  GL_ONE  ;
		   _destAlpha			=	GL_ONE_MINUS_SRC_ALPHA  ;
	 	break ;
	 	case	3:
	    	   _sourceAlpha 		=  GL_ZERO  ;
		   _destAlpha			=	GL_ONE_MINUS_SRC_ALPHA  ;
	 	break ;
		case	4:
	        _sourceAlpha 	=  GL_SRC_ALPHA ;
	        _destAlpha		=	GL_ONE ;
    		break ;
		case  5: // Copy Blender
			     _sourceAlpha  = GL_ONE;
			     _destAlpha = GL_ZERO;
		break ;	     
		case  6:
		     _sourceAlpha 	= GL_ONE_MINUS_SRC_ALPHA;
			 _destAlpha 		= GL_ONE;
  		break;
  	
    }
    
    
    
}


//blit from backbuffer to backbuffer
void		KGraphicGL::blitBackToBack( float	x1, float y1 , float	x2 , float y2 , float dx,float dy )
{
    glReadBuffer( GL_BACK ) ;
    glRasterPos2i( dx , dy ); 
    glCopyPixels( x1, y1 , x2-x1 , y2-y1 ,GL_COLOR  ) ;
    
}

//draw a rect
void		KGraphicGL::drawRect( float	x1, float y1 , float	x2 , float y2 , float r ,float g ,float b ,  float blend )
{
    
    y2 = screenHeight - y2 ;
    y1 = screenHeight - y1 ;
    
    _oldBindedText = -1 ;
    
    glDisable( GL_TEXTURE_2D) ;
//    glDisable( GL_TEXTURE_RECTANGLE_NV ) ;
    
    
    
    if (  blend != 1 )
    {
        glEnable( GL_BLEND ) ;
        glColor4f( r , g , b ,blend ) ;
        glBlendFunc(  GL_SRC_ALPHA , GL_ONE_MINUS_SRC_ALPHA  );
    }
    else
    {
        glDisable( GL_BLEND ) ;
        glColor3f( r , g , b ) ;	
    }
    //	destY	 = screenHeight -destY ;
    
    glBegin(GL_QUADS);
    glVertex3i( x1 ,y1, 0);  
	  	glVertex3i( x2 , y1, 0);
        glVertex3i( x2 , y2 , 0);
        glVertex3i( x1, y2, 0 );	    	    		
        glEnd();
        
        glDisable( GL_BLEND ) ;
        glColor4f( 1.0f , 1.0f ,1.0f ,1.0f ) ;
}


//non static version ( setAlphaMode compliant )
void		KGraphicGL::drawAlphaRect( float	x1, float y1 , float	x2 , float y2 , float r ,float g ,float b ,  float  blend )
{
    
    y2 = screenHeight - y2 ;
    y1 = screenHeight - y1 ;
    
    _oldBindedText = -1 ;
    
    glDisable( GL_TEXTURE_2D) ;
//    glDisable( GL_TEXTURE_RECTANGLE_NV ) ;
    
    
    
    if (  blend != 1 )
    {
        glEnable( GL_BLEND ) ;
        glColor4f( r , g , b ,blend ) ;
        glBlendFunc(  _sourceAlpha , _destAlpha  );	
        
    }
    else
    {
        glDisable( GL_BLEND ) ;
        glColor3f( r , g , b ) ;	
    }
    //	destY	 = screenHeight -destY ;
    
    glBegin(GL_QUADS);
    glVertex3i( x1 ,y1, 0);  
	  	glVertex3i( x2 , y1, 0);
        glVertex3i( x2 , y2 , 0);
        glVertex3i( x1, y2, 0 );	    	    		
        glEnd();
        
        glDisable( GL_BLEND ) ;
        glColor4f( 1.0f , 1.0f ,1.0f ,1.0f ) ;
        
}

void KGraphicGL::setLineWidth( float lineWidth )
{
	glLineWidth( lineWidth ) ;
}

//draw a rect
void		KGraphicGL::drawLine( short x1,short y1 , short x2 , short y2 , float r , float g , float b, float asource, float adest )
{
    _oldBindedText = -1 ;
    
    x1--;
    y1-- ;
    y2 = screenHeight - y2 ;
    y1 = screenHeight - y1 ;
    
    
    glDisable( GL_TEXTURE_2D) ;
//    glDisable( GL_TEXTURE_RECTANGLE_NV ) ;
    glEnable( GL_BLEND ) ;
    glBlendFunc(  _sourceAlpha , _destAlpha  );	
    
    glColor4f( r , g , b ,adest ) ;
    
    //	destY	 = screenHeight -destY ;
    
    //	 glLineWidth( 1 );
    
    glBegin (GL_LINE_LOOP);
		  glVertex2f (x1,y1);
          glVertex2f (x2,y2);
          glEnd( ) ;
          
          glDisable( GL_BLEND ) ;
          glColor4f( 1.0f , 1.0f ,1.0f ,1.0f ) ;
}

//plot pixels
void		KGraphicGL::plotPixel( float	x1, float y1 , float r ,float g ,float b ,  float blend )
{
    _oldBindedText = -1 ;
    
    y1 = screenHeight - y1 ;
    
    glEnable( GL_BLEND ) ;
    glBlendFunc(  _sourceAlpha , _destAlpha  );	
    
    glDisable( GL_TEXTURE_2D) ;
 //   glDisable( GL_TEXTURE_RECTANGLE_NV ) ;
    
    glColor4f( r , g , b ,blend ) ;
    
    glBegin( GL_POINTS ) ;
    glVertex2d( x1,y1 ) ;
    glEnd( ) ;
    
    glDisable( GL_BLEND ) ;
    glColor4f( 1.0f , 1.0f ,1.0f ,1.0f ) ;
    
}

void		KGraphicGL::blitArbitraryQuad( 	float sx1 , float sy1 , float sx2 , float sy2 , float sx3 , float sy3 , float sx4 , float sy4 , 
                                        float dx1 , float dy1 , float dx2 , float dy2 , float dx3 , float dy3 , float dx4 , float dy4  )
{
    
    ptk_glBindTexture();
    glEnable( GL_BLEND ) ;
    glBlendFunc(  _sourceAlpha , _destAlpha  );	
    
    	if ( _blitColorChanged == true )
	{
		glColor4f( _blitRed ,_blitGreen , _blitBlue , _blitAlpha  ) ;
	}
	else
	{
		glColor4f( 1.0f,1.0f,1.0f,1.0f) ;
	}
	
    glPushMatrix( ) ;
    genericArbitraryBlit( 	sx1,sy1,sx2,sy2,sx3,sy3,sx4,sy4 ,dx1,screenHeight-dy1,dx2,screenHeight-dy2,dx3,screenHeight-dy3,dx4,screenHeight-dy4 ) ;
    glPopMatrix( ) ;
}			

//blit un sprite alpha channel avec effet de rotation ou de zoom
void		KGraphicGL::blitAlphaRectFx( float	x1, float y1 , float	x2 , float y2 , short	destX , short	destY, float angle, float zoom, float blend , 
														bool flipx , bool flipy , float centerX , float centerY ) 
	{
    float		middlesizeX , middlesizeY ;
    bool		translated = false ;
    
    if ( zoom == 0  )		return ;
    if ( blend <= 0 )	 	return ;
    

    
    middlesizeX	=	(x2-x1)/2 + centerX ;
    middlesizeY	=	(y2-y1)/2 + centerY ;
    
   
    
    destY	 = screenHeight -destY ;
    //	glMatrixMode( GL_MODELVIEW) ;
    glPushMatrix();		//sauvegarde la matrice en cours
    
      if ( zoom == 1 )
   {
   	 	if ( _zoomX != 1 || _zoomY != 1 )
   	 	{     
   	 		translated =true;
      	 	 glTranslatef( (float)destX+middlesizeX ,(float)(destY)-middlesizeY  , 0  ) ;  	 		
   	 		glScalef(_zoomX ,_zoomY , 0 ) ;
   	 	}
   }
  
    if ( angle != 0 || zoom != 1 )
    {
		if ( translated == false )
		{
		      glTranslatef( (float)destX+middlesizeX ,(float)(destY)-middlesizeY  , 0  ) ;
      	}  
       
        if ( angle != 0 )
        {
            glRotatef( angle , 0.0f , 0.0f ,1.0f ) ; 	
        }
        
        if ( zoom != 1 )
        {
            glScalef( zoom  * _zoomX ,zoom* _zoomY , 0 ) ;
        }
    }
    

    
    
    	if ( _blitColorChanged == true )
	{
		glColor4f( _blitRed ,_blitGreen , _blitBlue , _blitAlpha * blend ) ;
	}
	else
	{
		 if ( blend >= 0 )	 glColor4f( 1.0f,1.0f,1.0f,blend) ;
	}
    
    ptk_glBindTexture();
    glEnable( GL_BLEND ) ;
    glBlendFunc(  _sourceAlpha , _destAlpha  );	
    
    glPushMatrix( ) ;
    if ( angle != 0 || zoom != 1 || _zoomX != 1 ||  _zoomY != 1  )
    {
        GenericBlit( x1 , y1 , x2 , y2 , -middlesizeX , middlesizeY , flipx , flipy ) ;
    }
    else
    {
        GenericBlit( x1 , y1 , x2 , y2 , destX , destY , flipx , flipy ) ;
    }
    glPopMatrix( ) ;
				
    glColor4f( 1.0f,1.0f,1.0f,1.0f) ;
    
    //	glMatrixMode( GL_MODELVIEW ) ;
    glPopMatrix();		//sauvegarde la matrice en cours
    
    
}

/*
//blit un sprite alpha channel avec effet de rotation ou de zoom
void		KGraphicGL::blitAlphaRectFxCenterAdjust( float	x1, float y1 , float	x2 , float y2 , short	destX , short	destY, float angle, float zoom, float blend  )
{
    float		middlesizeX , middlesizeY ;
    
    if ( zoom == 0  )		return ;
    if ( blend <= 0 )	 	return ;
    
    
    if ( _centerX	 == 0 )
    {
        middlesizeX	=	(x2-x1)/2 ;
    }
    else
    {
        middlesizeX = _centerX ;
    }
    
    if ( _centerY == 0 )
    {
        middlesizeY	=	(y2-y1)/2 ;
    }
    else
    {
        middlesizeY = _centerY ;
    }
    middlesizeY = _centerY ;
    //	middlesizeY =  y2-y1 ;
    
    destY	 = screenHeight -destY ;
    //	glMatrixMode( GL_MODELVIEW) ;
    glPushMatrix();		//sauvegarde la matrice en cours
    
    
    
    if ( angle != 0 || zoom != 1 )
    {
        
        glTranslatef( (float)destX+middlesizeX ,(float)(destY)-middlesizeY  , 0  ) ;
        
        
        if ( angle != 0 )
        {
            glRotatef( angle , 0.0f , 0.0f ,1.0f ) ; 	
        }
        
        if ( zoom != 1 )
        {
            glScalef( zoom ,zoom , 0 ) ;
        }
    }
    
    if ( blend >= 0 )	 glColor4f( 1.0f,1.0f,1.0f,blend) ;
    
    ptk_glBindTexture();
    glEnable( GL_BLEND ) ;
    glBlendFunc(  _sourceAlpha , _destAlpha  );	
    
    glPushMatrix( ) ;
    if ( angle != 0 || zoom != 1 )
    {
        GenericBlit( x1 , y1 , x2 , y2 , -middlesizeX , middlesizeY , true , false ) ;
    }
    else
    {
        GenericBlit( x1 , y1 , x2 , y2 , destX , destY , true , false ) ;
    }
    glPopMatrix( ) ;
				
    glColor4f( 1.0f,1.0f,1.0f,1.0f) ;
    
    //	glMatrixMode( GL_MODELVIEW ) ;
    glPopMatrix();		//sauvegarde la matrice en cours
    
    
}
*/
//grab le backbuffer
bool                    KGraphicGL::grabBackBuffer( pixelCallBackPtr	pixelTransformationPtr )
{

unsigned char           *pixels ;
unsigned char           *pixelsBack ;           //pixels in the backbuffer
unsigned        long            size ;
unsigned        long            i ;
unsigned        long            pixelsize ;
unsigned        long            x , y  ;
unsigned        long            rowBytes ;
unsigned        long            *pixelsBackL ,*destPixelsL;
unsigned        long            colorkey , curColor ,r,g,b;
long pr,pg,pb ;
                
        r = _ckr ;
        g = _ckg ;
        b = _ckb ;
                
        colorkey = r | (g <<8) | (b << 16) ;
                                
        //force tout en 32 bits
        pixelsize = 4 ;
        
        x = screenWidth ;
        if ( screenHeight > screenWidth ) {  x = screenHeight ; }
        
        //calculate a multiple of 2 for the texture size
        i = 2 ;
        do
        {
                i *= 2 ;
        }while( i < x ) ;

        size = i ;


        if ( _rectangleTexCap == false )
        {
                _glEnum = GL_TEXTURE_2D ;
                _ftextureWIDTH  = size ;
                _ftextureHEIGHT = size ;
        }
        else
        {
                _glEnum =  GL_TEXTURE_RECTANGLE_NV ;
                _ftextureWIDTH  = screenWidth ;
                _ftextureHEIGHT = screenHeight ;        
        }
        
        pixelsBack = new unsigned char[screenWidth*(screenHeight)*pixelsize] ;
        if ( pixelsBack == NULL )       return  K_ERROR ;

         pixels = new unsigned char[(long)(_ftextureWIDTH*_ftextureHEIGHT*4)] ;
         if ( pixels == NULL )  
         {
                delete  []      pixelsBack ;
                return  K_ERROR ;
         }      


        glReadBuffer( GL_BACK ) ;
        glReadPixels( 0 , 0 , screenWidth , screenHeight , GL_RGBA , GL_UNSIGNED_BYTE , pixelsBack ) ;

        rowBytes = _ftextureWIDTH*4 ;
        pixelsBackL = (unsigned long*)pixelsBack ;
        destPixelsL = (unsigned long*)pixels ;
        
        for ( y = 0 ; y < screenHeight ; y++ )
        {
                for ( x =0 ; x < screenWidth*pixelsize ; x+=pixelsize  )
                {
//                              pixels[x+y*rowBytes]            = pixelsBack[x+(screenHeight-(y+1))*screenWidth*pixelsize] ;
//                              pixels[x+y*rowBytes+1]          = pixelsBack[x+(screenHeight-(y+1))*screenWidth*pixelsize+1] ;
//                              pixels[x+y*rowBytes+2]          = pixelsBack[x+(screenHeight-(y+1))*screenWidth*pixelsize+2] ;

                                pr         = pixelsBack[x+y*screenWidth*pixelsize] ;
                                pg       = pixelsBack[x+y*screenWidth*pixelsize+1] ;
                                pb       = pixelsBack[x+y*screenWidth*pixelsize+2] ;                                       

							if ( pixelTransformationPtr != NULL ) 
							{
								pixelTransformationPtr( x/pixelsize , y , &pr,&pg,&pb ) ;
							}

                                pixels[x+(screenHeight-(y+1))*rowBytes]        =	pr ;
                                pixels[x+(screenHeight-(y+1))*rowBytes+1]   = 	pg ;
                                pixels[x+(screenHeight-(y+1))*rowBytes+2]   = 	pb ;                                       
                                  pixels[x+(screenHeight-(y+1))*rowBytes+3]  = 255 ;
                }
        }
        
        //alpha
        if ( _ckActive==true )
        {
                for ( y = 0 ; y < screenHeight ; y++ )
                {
                        for ( x =0 ; x < screenWidth ; x++  )
                        {
                                //      if ( x < 400 )          destPixelsL[x+y*screenWidth] = 0x880000ff ; //ABGR
                        
                                        curColor = destPixelsL[x+y*screenWidth] & 0x00ffffff ;
                                        if ( curColor ==  colorkey  )
                                        {
                                                destPixelsL[x+y*screenWidth] = 0 ;
                                        }
                                        else
                                        {
                                                destPixelsL[x+y*screenWidth] = curColor | 0xff000000 ;
                                        }
                                        
                        }                               
                }
        }

        glEnable( _glEnum ) ;
        glLoadIdentity( ) ;
        glGenTextures( 1 , &texture ) ;

        ptk_glBindTexture() ;
        glBindTexture(_glEnum, texture ) ;
        glEnable( GL_BLEND ) ;
        glBlendFunc(  _sourceAlpha , _destAlpha );
        
        glTexImage2D( _glEnum , 0 , GL_RGBA8     , _ftextureWIDTH,_ftextureHEIGHT ,0 , GL_RGBA , GL_UNSIGNED_BYTE , pixels ) ;

        
        glTexParameterf(_glEnum, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameterf(_glEnum, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri( _glEnum, GL_TEXTURE_WRAP_S,  GL_CLAMP );
        glTexParameteri( _glEnum, GL_TEXTURE_WRAP_T, GL_CLAMP );


        fimageWidth             =       (float)screenWidth ;
        fimageHeight            =       (float)screenHeight ;
        videoMemory             += (long)_ftextureWIDTH*(long)_ftextureHEIGHT*( screenDepth / 8 ) ;

        delete  []      pixels ;
        delete  []      pixelsBack ;

        return K_OK ;
}

/*
bool			KGraphicGL::saveBackBuffer( const char * cpcFileName , long	imageFormat , long resizeW , long resizeH )
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
        backBufGrab->stretchAlphaRect( 0,0,screenWidth , screenHeight , 0,screenHeight-resizeH,resizeW , screenHeight ) ;
    }
    else
    {
        resizeW = screenWidth ;
        resizeH 	= screenHeight ;
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
    
    backBufGrab->blitRect( 0,0,screenWidth , screenHeight ,0 ,0 ) ;
    delete	backBufGrab ;
    
    return K_OK ;
}
*/

/*
void			KGraphicGL::setGraphicQuality( bool quality )
{
    _graphicQuality = quality ;
    
    if ( quality == true )
    {
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameterf(GL_TEXTURE_RECTANGLE_NV, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameterf(GL_TEXTURE_RECTANGLE_NV, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    }
    else
    {
        glTexParameterf(GL_TEXTURE_RECTANGLE_NV, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameterf(GL_TEXTURE_RECTANGLE_NV, GL_TEXTURE_MIN_FILTER, GL_NEAREST);		
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);		
    }
}
*/


void			KGraphicGL::setTextureQuality( bool quality )
{
    
    ptk_glBindTexture();
    
    if ( quality == true )
    {
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//        glTexParameterf(GL_TEXTURE_RECTANGLE_NV, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//        glTexParameterf(GL_TEXTURE_RECTANGLE_NV, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    }
    else
    {
//        glTexParameterf(GL_TEXTURE_RECTANGLE_NV, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
//        glTexParameterf(GL_TEXTURE_RECTANGLE_NV, GL_TEXTURE_MIN_FILTER, GL_NEAREST);		
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);		
    }
}


void			KGraphicGL::allowTextureWrap( bool texwRap)
{
    _textureWrap = texwRap ;
    
    ptk_glBindTexture();
    
    if ( _textureWrap == false )
    {
        glTexParameteri( _glEnum, GL_TEXTURE_WRAP_S,  GL_CLAMP);	
        glTexParameteri( _glEnum, GL_TEXTURE_WRAP_T,  GL_CLAMP );
    }
    else
    {
        glTexParameteri( _glEnum, GL_TEXTURE_WRAP_S,  GL_REPEAT);	
        glTexParameteri( _glEnum, GL_TEXTURE_WRAP_T,  GL_REPEAT );
    }
	  	
}

void		KGraphicGL::ptk_glBindTexture(void  ) 
{
    
    if ( _oldBindedText != texture )
    {
        if ( _glEnum == GL_TEXTURE_RECTANGLE_NV )
        {
            glEnable(GL_TEXTURE_RECTANGLE_NV ) ;
            glDisable(GL_TEXTURE_2D ) ;
        }
        else
        {
//            glDisable(GL_TEXTURE_RECTANGLE_NV ) ;
            glEnable(GL_TEXTURE_2D ) ;
        }
        
        glBindTexture(_glEnum, texture ) ;
        _oldBindedText = texture ;
    }
    
}

void			KGraphicGL::setBlitColor( float r , float g , float b , float a )
{
	if ( r == 1 && g == 1 && b == 1 &&a == 1 )
	{
		_blitColorChanged = false ;
		return ;
	}
	
	if ( r > 1 )		r = 1 ;
	if ( g > 1 )		g = 1 ;
	if ( b > 1 )		b = 1 ;
	if ( a > 1 )		a = 1 ;
	if ( r < 0 )		r = 0 ;
	if ( g < 0 )		g = 0 ;
	if ( b < 0 )		b = 0 ;
	if ( a < 0 )		a = 0 ;
	
	_blitRed 		=  r ;
	_blitGreen	 	= g ;
	_blitBlue 		= b ;
	_blitAlpha 		= a ;
	_blitColorChanged = true ;
}

//grab le front buffer dans une texture
bool			KGraphicGL::grabFrontBuffer( void )
{
    
    unsigned char		*pixels ;
    unsigned char		*pixelsBack ;		//pixels in the backbuffer
    unsigned	long		size ;
    unsigned	long		i ;
    unsigned	long		pixelsize ; 
    unsigned	long  		x , y  ;
    unsigned	long		rowBytes ;
    
    //force tout en 32 bits
    pixelsize = 4 ;
    
    x = screenWidth ;
    if ( screenHeight > screenWidth ) {  x = screenHeight ; } 
    
    //calculate a multiple of 2 for the texture size
    i = 2 ;
    do
    {
        i *= 2 ;
    }while( i < x ) ;
    
    size = i ;
    if ( _rectangleTexCap == false )
    {
        _glEnum =  GL_TEXTURE_2D ;
        _ftextureWIDTH	= size ;
        _ftextureHEIGHT = size ;
    }
    else
    {
        _glEnum =  GL_TEXTURE_RECTANGLE_NV ;
        _ftextureWIDTH	= screenWidth ;
        _ftextureHEIGHT = screenHeight ;	
    }
    
    pixelsBack = new unsigned char[screenWidth*(screenHeight)*pixelsize] ;
    if ( pixelsBack == NULL )	return	K_ERROR ;
    
    pixels = new unsigned char[(long)(_ftextureWIDTH*_ftextureHEIGHT*4)] ;
    if ( pixels == NULL )	
    {
        delete	[]	pixelsBack ;
        return	K_ERROR ;
    } 	 
    
    
    glReadBuffer( GL_FRONT ) ;
    glReadPixels( 0 , 0 , screenWidth , screenHeight , GL_RGBA , GL_UNSIGNED_BYTE , pixelsBack ) ;
    
    rowBytes = _ftextureWIDTH*4 ;
    
    for ( y = 0 ; y < screenHeight ; y++ )
    {
        for ( x =0 ; x < screenWidth*pixelsize ; x+=pixelsize  )
        {
            //				pixels[x+y*rowBytes]  		=	pixelsBack[x+(screenHeight-(y+1))*screenWidth*pixelsize] ;
            //				pixels[x+y*rowBytes+1]		=	pixelsBack[x+(screenHeight-(y+1))*screenWidth*pixelsize+1] ;
            //				pixels[x+y*rowBytes+2]		=	pixelsBack[x+(screenHeight-(y+1))*screenWidth*pixelsize+2] ;
            
            pixels[x+(screenHeight-(y+1))*rowBytes]  		=	pixelsBack[x+y*screenWidth*pixelsize] ;
            pixels[x+(screenHeight-(y+1))*rowBytes+1]	=	pixelsBack[x+y*screenWidth*pixelsize+1] ;
            pixels[x+(screenHeight-(y+1))*rowBytes+2]	=	pixelsBack[x+y*screenWidth*pixelsize+2] ;
        }
    }
    
    
    glEnable( _glEnum ) ;
    glLoadIdentity( ) ;
    glGenTextures( 1 , &texture ) ;
    
    ptk_glBindTexture() ;
    
    glTexImage2D( _glEnum , 0 , GL_RGB     , _ftextureWIDTH, _ftextureHEIGHT ,0 , GL_RGBA , GL_UNSIGNED_BYTE , pixels ) ; 
    
    glTexParameterf(_glEnum, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameterf(_glEnum, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri( _glEnum, GL_TEXTURE_WRAP_S,  GL_CLAMP );
    glTexParameteri( _glEnum, GL_TEXTURE_WRAP_T, GL_CLAMP );
    
    fimageWidth		=	(float)screenWidth ; 
    fimageHeight 		=	(float)screenHeight ; 
    videoMemory		+= (long)_ftextureWIDTH*(long)_ftextureHEIGHT*( screenDepth / 8 ) ;
    
    delete	[]	pixels ;
    delete	[]	pixelsBack ;
    
	return K_OK ;
}

//grab le backbuffer
bool                    KGraphicGL::grabBackBufferFast(  long x, long y, long  w, long h ) 
{
	GLint buffer = 0;
	
	glGetIntegerv( GL_READ_BUFFER, &buffer );
	glReadBuffer( GL_BACK );
	
	selectTexture();
	glCopyTexSubImage2D( GL_TEXTURE_2D, 0, x, y, x, y, w, h );
	
    glReadBuffer( buffer );

	return K_OK;
}

void			KGraphicGL::setZoom( float zx, float zy )
{
	_zoomX = zx ;
	_zoomY = zy ;	
}

void KGraphicGL::gpuFinish( void )
{
	glFinish();
}


bool			KGraphicGL::grabFrontBufferFast( void )
{
	return grabBackBufferFast(0, 0, 256, 256);
}



bool KGraphicGL::CreateRenderTarget(int width, int height) 
{
	freePicture();

	fimageWidth		= (float)width;
	fimageHeight	= (float)height;
	_ftextureWIDTH	= (float)width;
	_ftextureHEIGHT = (float)height;

	glGenTextures( 1 , &texture );
	glGenTextures( 1 , &textureRttBuf );
	
	_glEnum = GL_TEXTURE_2D;

	GLenum gerr = glGetError();

    glBindTexture( _glEnum, texture);

	gerr = glGetError();

		glCopyTexSubImage2D( _glEnum, 0,     0, 0,  0, 0,   width, height );
	
		gerr = glGetError();

	glBindTexture( _glEnum, textureRttBuf);

	gerr = glGetError();

		glCopyTexSubImage2D( _glEnum, 0,     0, 0,  0, 0,   width, height );

		gerr = glGetError();

	_oldBindedText = textureRttBuf;

	return true;
}

bool KGraphicGL::startRenderToTexture() 
{
	glBindTexture( _glEnum, textureRttBuf);

	GLenum gerr = glGetError();

		glCopyTexSubImage2D( _glEnum, 0,     0, 0,  0, 0,  (GLsizei)_ftextureWIDTH, (GLsizei)_ftextureHEIGHT );

		gerr = glGetError();

	_oldBindedText = textureRttBuf;

	return true;
}

bool KGraphicGL::endRenderToTexture() 
{
    glBindTexture( _glEnum, texture);

	GLenum gerr = glGetError();

		glCopyTexSubImage2D( _glEnum, 0,     0, 0,  0, 0,   (GLsizei)_ftextureWIDTH, (GLsizei)_ftextureHEIGHT );
	
		gerr = glGetError();

	_oldBindedText = texture;

	GLenum temp = texture;
		texture = textureRttBuf;
		textureRttBuf = temp;

	blitRect( 0, 0, (GLsizei)_ftextureWIDTH, (GLsizei)_ftextureHEIGHT, 0, 0 );

	temp = texture;
		texture = textureRttBuf;
		textureRttBuf = temp;

	return true;
}
