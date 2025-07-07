
#include		<windows.h>
#include		<stdio.h>
#include		"KGraphicGDI.h"
#include		"KGlobals.h"
#include		"KMiscTools.h"
#include		"KWindowGDI.h"
#include    "KResource.h"


#include		"ximage.h"


#define	HIMETRIC_INCH	2540


short				KGraphicGDI::screenWidth=0 , KGraphicGDI::screenHeight=0 ,KGraphicGDI::screenDepth=0  ;	
long				KGraphicGDI::videoMemory = 0 ;
bool				KGraphicGDI:: _graphicQuality = false ;
HDC				KGraphicGDI::_mainDC = 0 ;
HDC				KGraphicGDI::_backBufferDC = 0 ;

KGraphicGDI::KGraphicGDI( )
{
//    if ( screenWidth == 0 )		KMiscTools::messageBox( "Screen Dimensions not specified, you will not see anything" , "KGraphicGDI::SetScreenSize Not Called!" ) ;

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
    _blitColorChanged = false ;
    _surfaceHBitmap = 0 ;
    _surfaceHDC = 0 ;
    _oldBitmap  = 0 ;
	_blitAlpha = 1 ;
	_picBits = NULL ;

}

KGraphicGDI::~KGraphicGDI( )
{
    freePicture( ) ;
}

void		KGraphicGDI::setColorKey( bool active , unsigned char r ,unsigned char g ,unsigned char b )
{
    _ckActive = active ;
    _ckr = r ;
    _ckg = g ;
    _ckb = b ;
}
/*
void		KGraphicGDI::d3dTextureToTGA( char *sourcefilename , char *destFilename)
{
		MessageBox( 0 , "requires to be running in DirectX mode ( K_DIRECTX )" ,0,0 ) ;
}
*/
unsigned	char*		KGraphicGDI::LoadGeneric( char	*filename )
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


unsigned	char*		KGraphicGDI::LoadGenericFromPtr( char	*filename , unsigned char *buffer , unsigned long size )
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
unsigned	char*		KGraphicGDI::LoadGeneric( char	*filename )
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
                                          
                                            unsigned char*		KGraphicGDI::RenderPicture( LPPICTURE 		picture  ) 
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
unsigned	char*		KGraphicGDI::LoadTGA( char	*filename )
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
float			KGraphicGDI::getWidth( void )
{
    return fimageWidth ;
}

//returns the height of a picture
float			KGraphicGDI::getHeight( void )
{
    return fimageHeight ;
}

void			KGraphicGDI::selectTexture( void ) 
{

}
//build a 32 bit picture from an array
bool		KGraphicGDI::makePictureFromArray( unsigned long *userPixelPtr , long width , long height , bool hiDef )
{
  HDC hScreen = GetDC(NULL);
   
    
    fimageWidth	=	(float)width ;
    fimageHeight 	=	(float)height ;

    
  _ftextureWIDTH = width ;
  _ftextureHEIGHT = height ;

    
    	//old bitmaps ( for transfer )
  //  	HDC tmpdc = CreateCompatibleDC( hScreen ) ;
  //  HBITMAP tmpbitmap  = CreateBitmap( width ,  height , 1 , 32 , userPixelPtr ) ;
//	HBITMAP tmpoldBitmap  = (HBITMAP)SelectObject( tmpdc , tmpbitmap ) ;
    
    //the real bitmap
    	_surfaceHDC = CreateCompatibleDC( hScreen ) ;
    _surfaceHBitmap =  CreateBitmap( width ,  height , 1 , 32 , userPixelPtr ) ;
	_oldBitmap  = (HBITMAP)SelectObject( _surfaceHDC , _surfaceHBitmap ) ;

   // BitBlt(  _surfaceHDC, 0,0,width, height, tmpdc , 0 , 0, SRCCOPY ) ;
    
    //clean up our tmp bitmaps/dc
//	SelectObject( tmpdc ,  tmpoldBitmap ) ;
//	DeleteDC( tmpdc ) ;
//	DeleteObject( tmpbitmap ) ;

    
    return	K_OK ;
}

void			KGraphicGDI::pollArray( void )
{
    if ( _userPixelPtr == NULL )		return ;
 
}


bool			KGraphicGDI::loadPictureFromPtr( const	char	*filename , unsigned char	*dataPtr , unsigned long datasize , bool hiDef , bool hasalpha ) 
{
//        setCenterPoint( 0,0 ) ;
        
        return K_OK ;
}

bool			KGraphicGDI::loadPictureWithMask( const	char	*filename , const	char	*filenameMask , bool hiDef ) 
{

        
        return K_OK ;
}

HBITMAP	KGraphicGDI::createHBitmap( long width , long height )
{
	
	_surfaceHDC = CreateCompatibleDC( NULL ) ;

    _surfaceHBitmap = CreateCompatibleBitmap( GetDC( NULL ) ,  width , height ) ;
	_oldBitmap  = (HBITMAP)SelectObject( _surfaceHDC , _surfaceHBitmap ) ;

	return _surfaceHBitmap ;
}
			
bool			KGraphicGDI::loadPicture( const	char	*filename , bool hiDef , bool hasalpha ) 
{
    unsigned 	char	*pixelPtr ;		
    long						x,y ;
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
    
 
    imageWidth		=	tgaInfo.width ; 
    imageHeight 		=	tgaInfo.height ; 
    
    fimageWidth	=	(float)imageWidth ;
    fimageHeight 	=	(float)imageHeight ;
    picX1	=	tgaInfo.xstart ;
    picY1	=	tgaInfo.ystart ;
    
  _ftextureWIDTH = fimageWidth ;
  _ftextureHEIGHT = imageHeight ;
    

    
    pixelPtr = (unsigned char*)cxImagePtr->GetBits( ) ;
    
    unsigned char r,g,b ,a;
	
	_picBits = new unsigned char[imageWidth*imageHeight*4] ;
	
//	createHBitmap( imageWidth , imageHeight  ) ;
long		tr,tg,tb, ta ;
    
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
                color = cxImagePtr->GetPixelColor( x , imageHeight-(y+1) , true ) ;
                
               tr =   color.rgbRed  ;
               tg = color.rgbGreen  ;
               tb = color.rgbBlue ;
               ta = color.rgbReserved  ;
               a = ta ;
                
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

			tr =  (tr * ta ) / 255 ;
			tg =  (tg * ta ) / 255 ;
			tb =  (tb * ta ) / 255 ;
			r = tr ;
			g = tg ;
			b = tb ;
			
			
            /*    if ( a == 0 )
                {
                	r = 0 ;
                	g = 0 ;
                	b = 0 ;
                }
               */
    
                _picBits[4*x+y*(long)_ftextureWIDTH*4] 	 = 	b ;				//r
                _picBits[4*x+y*(long)_ftextureWIDTH*4+1]	 =	g	 ;				//g
                _picBits[4*x+y*(long)_ftextureWIDTH*4+2]	 = r ;				//b
                _picBits[4*x+y*(long)_ftextureWIDTH*4+3] =	a  ;				//a							
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
                
                _picBits[4*x+y*(long)_ftextureWIDTH*4] 	 =b ;				//r
                _picBits[4*x+y*(long)_ftextureWIDTH*4+1]	 =	g	 ;				//g
                _picBits[4*x+y*(long)_ftextureWIDTH*4+2]	 = r ;				//b
                _picBits[4*x+y*(long)_ftextureWIDTH*4+3] =	a  ;				//a							
                
            }	
        }
        
        break ;
        
        }
  HDC hScreen = GetDC(NULL);

    	
    	
	//old bitmaps ( for transfer )
    	HDC tmpdc = CreateCompatibleDC( hScreen ) ;
    HBITMAP tmpbitmap  = CreateBitmap( imageWidth ,  imageHeight , 1 , 32 , _picBits ) ;
	HBITMAP tmpoldBitmap  = (HBITMAP)SelectObject( tmpdc , tmpbitmap ) ;
    
    //the real bitmap
    	_surfaceHDC = CreateCompatibleDC( hScreen ) ;
    _surfaceHBitmap =  CreateCompatibleBitmap ( hScreen,  imageWidth ,  imageHeight ) ;
	_oldBitmap  = (HBITMAP)SelectObject( _surfaceHDC , _surfaceHBitmap ) ;

    BitBlt(  _surfaceHDC, 0,0,imageWidth, imageHeight, tmpdc , 0 , 0, SRCCOPY ) ;
    
    //clean up our tmp bitmaps/dc
	SelectObject( tmpdc ,  tmpoldBitmap ) ;
	DeleteDC( tmpdc ) ;
	DeleteObject( tmpbitmap ) ;
    

	delete [] _picBits ;
	_picBits = NULL ;

        //free the memory where we loaded the tga
        delete cxImagePtr ;
        cxImagePtr = NULL ;
        pixelPtr = NULL;
       
               
        
        videoMemory += (long)_ftextureWIDTH*(long)_ftextureHEIGHT*( screenDepth / 8 ) ;
        
//        setCenterPoint( 0,0 ) ;
        
        return K_OK ;
}


bool			KGraphicGDI::loadPicture3D( const	char	*filename , bool hiDef , bool hasalpha ) 
{
  
        
        return K_OK ;
}





//Free texture
void		KGraphicGDI::freePicture( void )
{
    
    //s'assure que la texture existe
    if ( fimageWidth > 0 )
    {
        videoMemory -= (long)_ftextureWIDTH*(long)_ftextureHEIGHT*( screenDepth / 8 ) ;
    
        fimageWidth		= 0 ;
        fimageHeight		= 0 ;
    }
    
	if ( _oldBitmap != 0 )
	{
		SelectObject( _surfaceHDC , _oldBitmap ) ;
		DeleteObject( _surfaceHBitmap );
		DeleteDC ( _surfaceHDC ) ;
	}
	
	_surfaceHDC = 0 ;
	_surfaceHBitmap = 0 ;
	_oldBitmap = 0 ;
	

}

//stocke la taille ecran, necessaire pour le blit ( pour le systeme de coordonnees )
void		KGraphicGDI::setScreenSize( short		swidth , short	sheight  , short sdepth ) 
{
    screenWidth 	= swidth ;
    screenHeight = sheight ;
    screenDepth = sdepth ;
    

}



/*
//sets the center point of the sprite ( for rotations )
void		KGraphicGDI::setCenterPoint( float	 cx,float cy )
{
    _centerX = cx ;
    _centerY = cy ;
}
*/

//sub pixel blitting
//**************
void			KGraphicGDI::blitRectF( float	x1, float y1 , float	x2 , float y2 , float	destX , float	destY , bool flipx  , bool flipy ) 
{

}

void			KGraphicGDI::blitRectFxF( float	x1, float y1 , float	x2 , float y2 , float destX , float	destY, float angle, float zoom, bool flipx , bool flipy) 
{

}

//alpha rect for sub  pixels
void			KGraphicGDI::blitAlphaRectF( float	x1, float y1 , float	x2 , float y2 , float destX , float	destY, bool flipx  , bool  flipy ) 
{


}

//alpha rectfx for sub  pixels
void			KGraphicGDI::blitAlphaRectFxF( float	x1, float y1 , float	x2 , float y2 , float 	destX , float	destY, float angle, float zoom, float blend , bool flipx  , bool flipy  , float centerX, float centerY )  
{

}


//**************

//no alpha stuff, the fastest we can get ?
void		KGraphicGDI::blitRect( float	x1, float y1 , float	x2 , float y2 , short	destX , short	destY , bool flipx , bool flipy )
{
  	BitBlt ( _backBufferDC , destX, destY , x2-x1  , y2-y1 , _surfaceHDC , x1 , y1 , SRCCOPY ) ;

}


void		KGraphicGDI::stretchAlphaRect( float	sx1, float sy1 , float	sx2 , float sy2 , float	dx1, float dy1 , float	dx2 , float dy2, float blend, float angle , bool flipx, bool flipy , float centerX, float centerY)
{
	

}


// blit no alpha but with effects
void		KGraphicGDI::blitRectFx( float	x1, float y1 , float	x2 , float y2 , short	destX , short	destY, float angle, float zoom, bool flipx , bool flipy)
{

}


//blit used for all the function
inline		void		KGraphicGDI::genericStretchBlit( float	sx1 , float	sy1 , float	sx2 , float	sy2 , float	dx1 ,float	dy1 , float	dx2 , float	dy2  , bool flipx,bool flipy) 
{

    
}

void		KGraphicGDI::genericArbitraryBlit( 	float	sx1 , float	sy1 , float	sx2 , float	sy2 , float	sx3 ,float	sy3 , float	sx4 , float	sy4 , 
                                           float	dx1 , float	dy1 , float	dx2 , float	dy2 , float	dx3 ,float	dy3 , float	dx4 , float	dy4 )													
{

    
}



//blit used for all the function
inline		void		KGraphicGDI::GenericBlit(  float	x1, float y1 , float	x2 , float y2 , short	destX , short	destY , bool flipx , bool flipy ) 
{


        
 
            
}





//blit tiling the texture
void		KGraphicGDI::blitTiledRect(short	destX , short	destY , short		width , short	height ,  float tileFactor ,float angle )
{

    
}

//blit taking care of the alpha channel
void		KGraphicGDI::blitAlphaRect( float	x1, float y1 , float	x2 , float y2 , short	destX , short	destY , bool flipx , bool flipy )
{
	long		w,h ;
	BLENDFUNCTION  blendFunction ;
	
	blendFunction.BlendOp 						= AC_SRC_OVER ;
	blendFunction.BlendFlags					= 0 ;

	blendFunction.SourceConstantAlpha 	= 255 ;
	blendFunction.AlphaFormat 				=  0x01 ; //AC_SRC_ALPHA  ;
	
	w = x2-x1 ;
	h = y2-y1 ;
	
	AlphaBlend ( _backBufferDC , destX, destY , w , h , _surfaceHDC , x1,y1  , w , h , blendFunction ) ;
    
}

//blit for tga with coordinates
void		KGraphicGDI::blitAlphaRect( void )
{
    

}



//regular == true pour TGA  false pour additif
void		KGraphicGDI::setAlphaMode( long	alphamode )
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
    }
    
    
    
}


//blit from backbuffer to backbuffer
void		KGraphicGDI::blitBackToBack( float	x1, float y1 , float	x2 , float y2 , float dx,float dy )
{

}

//draw a rect
void		KGraphicGDI::drawRect( float	x1, float y1 , float	x2 , float y2 , float r ,float g ,float b ,  float blend )
{
RECT	rec ;
HBRUSH hbr ;
COLORREF  mycolor ;
long				lr,lg,lb,la ;
HDC		colordc ;

	lr = r * 255.0f ;
	lg = g * 255.0f ;
	lb = b * 255.0f ;
	la = blend * 255.0f ;
	
	BLENDFUNCTION  blendFunction ;
	
	blendFunction.BlendOp 						= AC_SRC_OVER ;
	blendFunction.BlendFlags					= 0 ;

	blendFunction.SourceConstantAlpha 	= la ;
	blendFunction.AlphaFormat 				=  0x01; 
	
		
	colordc =  KWindowGDI::_surf_colorHolder->_surfaceHDC ;
	
		
	mycolor = ( lb << 16 ) | (lg<< 8 ) | lr ;
	hbr = CreateSolidBrush( mycolor ) ;
	HGDIOBJ oldobj = SelectObject( colordc ,  hbr ) ;

	SetRect( &rec ,  0,0,64,64) ;
    FillRect( colordc , &rec , hbr ) ;
	
  
    AlphaBlend ( _backBufferDC , x1,y1,x2-x1,y2-y1 , colordc , 0,0,32,32 , blendFunction ) ;
    
    
	SelectObject(  KWindowGDI::_surf_colorHolder->_surfaceHDC ,  oldobj ) ;
     DeleteObject( hbr ) ;

}


//non static version ( setAlphaMode compliant )
void		KGraphicGDI::drawAlphaRect( float	x1, float y1 , float	x2 , float y2 , float r ,float g ,float b ,  float  blend )
{
    

        
}


//draw a rect
void		KGraphicGDI::drawLine( float	x1, float y1 , float	x2 , float y2 , float r ,float g ,float b ,  float blend )
{
   

}

//plot pixels
void		KGraphicGDI::plotPixel( float	x1, float y1 , float r ,float g ,float b ,  float blend )
{

   

    
}

void		KGraphicGDI::blitArbitraryQuad( 	float sx1 , float sy1 , float sx2 , float sy2 , float sx3 , float sy3 , float sx4 , float sy4 , 
                                        float dx1 , float dy1 , float dx2 , float dy2 , float dx3 , float dy3 , float dx4 , float dy4  )
{
    
    
    	if ( _blitColorChanged == true )
	{
//		glColor4f( _blitRed ,_blitGreen , _blitBlue , _blitAlpha  ) ;
	}
	else
	{
//		glColor4f( 1.0f,1.0f,1.0f,1.0f) ;
	}

}			

//blit un sprite alpha channel avec effet de rotation ou de zoom
void		KGraphicGDI::blitAlphaRectFx( float	x1, float y1 , float	x2 , float y2 , short	destX , short	destY, float angle, float zoom, float blend , 
														bool flipx , bool flipy , float centerX , float centerY ) 
	{
    float		middlesizeX , middlesizeY ;
    
    
    if ( zoom == 0  )		return ;
    if ( blend <= 0 )	 	return ;
    

    
    middlesizeX	=	(x2-x1)/2 + centerX ;
    middlesizeY	=	(y2-y1)/2 + centerY ;
    
	float		w,h , wdest, hdest;
	float		offsetx, offsety ;
	BLENDFUNCTION  blendFunction ;
	
	blendFunction.BlendOp 						= 0 ; //AC_SRC_OVER ;
	blendFunction.BlendFlags					= 0 ;

	blendFunction.SourceConstantAlpha 	= 255*blend ;
	blendFunction.AlphaFormat 				= 0x01 ;
	if ( blendFunction.SourceConstantAlpha < 0 )		{blendFunction.SourceConstantAlpha = 0 ; } 
	if ( blendFunction.SourceConstantAlpha > 255 )	{blendFunction.SourceConstantAlpha = 255; }

	w = x2-x1 ;
	h = y2-y1 ;
	wdest 	=w*zoom ;
	hdest	=h*zoom ;
	offsetx	= (wdest-w ) /2 ;
	offsety	=(hdest-h ) /2 ;
	
 //StretchBlt(_backBufferDC , destX-offsetx, destY-offsety ,wdest , hdest , _surfaceHDC , x1,y1  , w , h , SRCCOPY ) ;



	AlphaBlend ( _backBufferDC , destX-offsetx, destY-offsety ,wdest , hdest , _surfaceHDC , x1,y1  , w , h , blendFunction ) ;
	//AC_SRC_ALPHA = &H1
/*BLENDFUNCTION  bldf = { AC_SRC_OVER , 0 , 255 ,0x1  }   ;

	bldf.SourceConstantAlpha  = alphaFactor  ;
   */
    
}

//grab le backbuffer
bool                    KGraphicGDI::grabBackBuffer( pixelCallBackPtr	pixelTransformationPtr )
{

        return K_OK ;
}




void			KGraphicGDI::setTextureQuality( bool quality )
{
  //no filtering for stretchblt sorry.
}


void			KGraphicGDI::allowTextureWrap( bool texwRap)
{

	  	
}



void			KGraphicGDI::setBlitColor( float r , float g , float b , float a )
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
bool			KGraphicGDI::grabFrontBuffer( void )
{
 
	return K_OK ;
}

