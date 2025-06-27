#define	D3D_OVERLOADS
#define DIRECT3D_VERSION 0x0700
#define DIRECTDRAW_VERSION 0x0700
#include	<ddraw.h>
#include	<d3d.h>
#include	<d3dx.h>
#include	"KGraphicD3D.h"
#include	"ximage.h"
#include	"matrices.h"
#include	"KMiscTools.h"
#include "KResource.h"
#include	"d3dxcore.h"
#include	"KBatchD3D.h"

using namespace std;

float		KGraphicD3D::_texelSX = 0 ;
float		KGraphicD3D::_texelSY = 0 ;
float		KGraphicD3D::_texelDX = -0.5 ;
float		KGraphicD3D::_texelDY = -0.5 ;

extern	D3DVECTOR operator * (const D3DVECTOR &p, const D3DMATRIX &M)  ;

//#define		LOGZEERRORS			1

#ifdef	LOGZEERRORS

void	logerror( char *text ) ;

void	logerror( char *text ) 
{
FILE		*fe ;

	fe = fopen("c:\\errors\\error.txt" , "a+" ) ;
	if( fe == 0 )	return ;
	
	fprintf( fe , "%s" , text ) ;
	fclose( fe ) ;
}
#endif

LPDIRECTDRAW7				KGraphicD3D::_directX = NULL ;
LPDIRECT3DDEVICE7		KGraphicD3D::_d3d	= NULL ;
LPDIRECTDRAWSURFACE7		KGraphicD3D::_backBuffer = NULL ;
LPDIRECTDRAWSURFACE7		KGraphicD3D::_oldBindedText = NULL ;

long									KGraphicD3D::_screenWidth = 0 ;
long									KGraphicD3D::_screenHeight = 0 ;
long									KGraphicD3D::_screenDepth = 0 ;

vector<KGraphicD3D*>		KGraphicD3D::surfaceList ;

void			KGraphicD3D::setTexelInfo( float sx , float sy , float dx , float dy ) 
{
	_texelSX = sx ;
	_texelSY = sy ;
	_texelDX = dx ;
	_texelDY = dy ;
	KBatchD3D::setTexelInfo( sx , sy , dx, dy ) ;
}

void	KGraphicD3D::setDirectX( LPDIRECTDRAW7	dd7 , LPDIRECT3DDEVICE7	d3dPtr ,LPDIRECTDRAWSURFACE7 backbuffer , long width,long	height , long depth)
{
	_directX = dd7 ;
	_d3d  = d3dPtr ;
	_backBuffer = backbuffer ;
	_oldBindedText = 0 ;
	_d3d->SetRenderState(D3DRENDERSTATE_LIGHTING, FALSE);
    _d3d->SetRenderState(D3DRENDERSTATE_ZENABLE, FALSE);
    _d3d->SetRenderState(D3DRENDERSTATE_CULLMODE, D3DCULL_NONE);
    _d3d->SetRenderState(D3DRENDERSTATE_COLORVERTEX, true);
 

	_d3d->SetTextureStageState( 0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE );
	_d3d->SetTextureStageState( 0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE );
	_d3d->SetTextureStageState( 0, D3DTSS_ALPHAOP, D3DTOP_MODULATE );

	
	_d3d->SetRenderState(D3DRENDERSTATE_SRCBLEND, D3DBLEND_SRCALPHA);
	_d3d->SetRenderState(D3DRENDERSTATE_DESTBLEND, D3DBLEND_INVSRCALPHA);
	 _d3d->SetTextureStageState(0,D3DTSS_ADDRESS ,     D3DTADDRESS_CLAMP      );	    	
	_d3d->SetTextureStageState(0,D3DTSS_ADDRESSU ,     D3DTADDRESS_CLAMP      );	    	
	_d3d->SetTextureStageState(0,D3DTSS_ADDRESSV ,     D3DTADDRESS_CLAMP      );	    	
  	_d3d->SetTextureStageState(0,D3DTSS_MAGFILTER,     D3DTFG_POINT      );
    	_d3d->SetTextureStageState(0,D3DTSS_MINFILTER,     D3DTFG_POINT      );	

	_d3d->SetRenderState( D3DRENDERSTATE_TEXTUREPERSPECTIVE  , false ) ;
	_d3d->SetRenderState( D3DRENDERSTATE_ALPHATESTENABLE , false ) ;
	_d3d->SetRenderState( D3DRENDERSTATE_DITHERENABLE , false ) ;
	_d3d->SetRenderState( D3DRENDERSTATE_CLIPPING , true ) ;
	_d3d->SetRenderState( D3DRENDERSTATE_ANTIALIAS  ,     D3DANTIALIAS_NONE   ) ;
	_d3d->SetRenderState( D3DRENDERSTATE_EDGEANTIALIAS , false ) ;

	_screenWidth 	= width ;
	_screenHeight 	= height ;
	_screenDepth 	= depth ;
}

KGraphicD3D::KGraphicD3D(  ) 
{
    _2dSurface = false ;
	_usedForTTF = 0 ;	
    _pixels = NULL ;
    fimageWidth = 0 ;
    _ftextureWIDTH = 0 ;
    _ftextureHEIGHT = 0 ;
    setAlphaMode( true  ) ;
    _ckActive = false ;
    _textureWrap = false ;
    allowTextureWrap( false ) ;
    _surface = NULL ;
    _ckr = 0 ;
    _ckg = 0 ;
    _ckb = 0 ;
	_userPixelPtr = NULL ;
	//used for setBlitColor ( replaces glColor4f )
	_blitRed = 1 ;
	_blitGreen = 1 ;
	_blitBlue = 1 ;
	_blitAlpha = 1 ;
	_blitColorChanged = false ;
	_blend = 1 ;
	_textureQuality	= false ;
	_textureQualityD3D = D3DTFG_POINT ;
	setBlitColor( 1,1,1,1 ) ;
	_oldTextureQualityD3D = D3DTFG_FLATCUBIC ;
	_oldTextureWrapD3D = D3DTADDRESS_MIRROR ;
	_oldsourceAlpha = D3DBLEND_ZERO ;
	_olddestAlpha = D3DBLEND_ZERO;
	 strcpy( imageFileName , "") ;
	 strcpy( imageMaskFileName , "" ) ;
    _zoomX = 1 ;
    _zoomY = 1 ;
 
	 addSurfaceToList( ) ;
	 
}


KGraphicD3D::~KGraphicD3D( ) 
{
	removeSurfaceFromList( ) ;
	freePicture( ) ;
}

void	KGraphicD3D::setZoom( float zx, float zy)
{
	_zoomX = zx ;
	_zoomY = zy ;
}

//	vector<KGraphicD3D*>		surfaceList ; //the list of surface  ( required to fix a non working managed surface in directx ) ->alt tab bug
void			KGraphicD3D::addSurfaceToList( void ) 
{

	surfaceList.push_back( this ) ;
}

void			KGraphicD3D::removeSurfaceFromList( void ) 
{
long i ;

	if ( surfaceList.size() <= 0 )		return ;
	
	for ( i = 0  ; i < surfaceList.size() ; i++ )
	{
		if ( this != surfaceList[i] )		continue ;
		
		surfaceList.erase( surfaceList.begin( ) + i ) ;
		break ;
	}
}

void			KGraphicD3D::forceReloadList( void ) 
{
long		i ;
KGraphicD3D		*kdptr ;

	if ( surfaceList.size() <= 0 )		return ;
	
	for ( i = 0  ; i < surfaceList.size() ; i++ )
	{	
		kdptr = surfaceList[i] ;
		kdptr->reloadSurface( ) ;
	}
}

void			KGraphicD3D::deleteList( void ) 
{
long		i ;


	if ( surfaceList.size() <= 0 )		return ;
	
	for ( i = 0  ; i < surfaceList.size() ; i++ )
	{	
		surfaceList[i]->deleteD3DSurface( ) ;
	}
}


void		KGraphicD3D::deleteD3DSurface( void )
{
		if ( _surface  != NULL )
		{
			_surface->DeleteAttachedSurface( 0 , NULL ) ;
			_surface->Release( ) ;
			_surface = NULL ;
		}
}

void		KGraphicD3D::setAlphaMode( long	alphamodeSource, long alphamodeDest ) 
{
  	_sourceAlpha 		= (_D3DBLEND) alphamodeSource  ;
	 _destAlpha			=(_D3DBLEND)alphamodeDest  ;
}

 void	 	KGraphicD3D::setAlphaMode( long	 alphaMode  ) 
{
/*	    D3DBLEND_ZERO              = 1,
    D3DBLEND_ONE               = 2,
    D3DBLEND_SRCCOLOR          = 3,
    D3DBLEND_INVSRCCOLOR       = 4,
    D3DBLEND_SRCALPHA          = 5,
    D3DBLEND_INVSRCALPHA       = 6,
    D3DBLEND_DESTALPHA         = 7,
    D3DBLEND_INVDESTALPHA      = 8,
    D3DBLEND_DESTCOLOR         = 9,
    D3DBLEND_INVDESTCOLOR      = 10,
    D3DBLEND_SRCALPHASAT       = 11,
    D3DBLEND_BOTHSRCALPHA      = 12,
    D3DBLEND_BOTHINVSRCALPHA   = 13,
 */   
 switch ( alphaMode )
 {
 	//additive
 	case	0:
    	   _sourceAlpha 		=  D3DBLEND_SRCALPHA  ;
	   _destAlpha			=	D3DBLEND_DESTALPHA  ;
 	break ;
 	//normal
	case	1:
 	       _sourceAlpha 	=  D3DBLEND_SRCALPHA ;
	        _destAlpha		=	D3DBLEND_INVSRCALPHA ;
 	break ;
 	case	2:
    	   _sourceAlpha 		=  D3DBLEND_ONE  ;
	  _destAlpha			=	D3DBLEND_INVSRCALPHA  ;
 	break ;
 	case	3:
    	   _sourceAlpha 		=  D3DBLEND_ZERO  ;
	  _destAlpha			=	D3DBLEND_INVSRCALPHA  ;
 	break ;
  	case	4:
  		 _sourceAlpha 	=  D3DBLEND_SRCALPHA ;
	        _destAlpha		=	D3DBLEND_ONE ; 	
	       break ;
 		case  5: // Copy Blender
			     _sourceAlpha  = D3DBLEND_ONE;
			     _destAlpha = D3DBLEND_ZERO;
		break ;	
	case  6:
		     _sourceAlpha 	= D3DBLEND_INVSRCALPHA;
			 _destAlpha 		= D3DBLEND_ONE;
  	break;
  
		
}
	
}


void	KGraphicD3D::freePicture( void ) 
{
	if ( _surface != NULL )
	{
		_surface->DeleteAttachedSurface( 0 , NULL ) ;
		_surface->Release( ) ;
		_surface = NULL ;
	}
}

float	KGraphicD3D::getWidth( void )
{
	return	fimageWidth;
}

float	KGraphicD3D::getHeight( void )
{
	return	fimageHeight ;
}

bool	KGraphicD3D::loadPicture32Ptr( const char	*filename , unsigned char	*dataPtr  , unsigned long size , bool hidef , bool hasAlpha )
{
    long						 x,y ;
    long						imageWidth , imageHeight ;
    tgaBitmap				tgaInfo ;
    CxImage				*cxImagePtr ;	
    hasAlpha = hasAlpha ; 
    hidef = hidef ;
//    #pragma unused( hasAlpha )
//    #pragma unused( hidef )
    
    
    
    if ( _directX == NULL ||  _d3d == NULL )		
    {
    		strcpy( imageFileName , "" ) ;
	    	//MessageBox( 0 , "directx not initialized",0,0 ) ;
	    	return false ;
	}

	if ( _directX->TestCooperativeLevel() != DD_OK)		return false ;
	
 
 
    strcpy( imageFileName , filename ) ;
	
    cxImagePtr = (CxImage*)LoadGenericFromPtr( (char*)filename , dataPtr , size ) ;
    if ( cxImagePtr == NULL  )	
    {
  	  	strcpy( imageFileName , "" ) ;
    		return false ;
    	}

    
    tgaInfo.bpp = cxImagePtr->GetBpp( ) ;
    tgaInfo.width = cxImagePtr->GetWidth( ) ;
    tgaInfo.height = cxImagePtr->GetHeight( ) ;

    long nMaxDim;
    int nPow;

    nMaxDim = tgaInfo.width;
    if (tgaInfo.height > nMaxDim)
       nMaxDim = tgaInfo.height;

    for ( nPow = 30; ((1 << nPow) >= nMaxDim) && (nPow >= 0); nPow--) {;}
       nPow++;

    _ftextureWIDTH		=		1 << nPow ;
    _ftextureHEIGHT	=		1 << nPow ;
    fimageWidth = tgaInfo.width;
    fimageHeight =tgaInfo.height ;

    long ct = cxImagePtr->GetColorType( ) ;
    
    if ( ct == 4) 
    {
        tgaInfo.bpp  = 32 ;
    }
    
	//describe the texture
	DDSURFACEDESC2		ddsd ;
	memset(&ddsd, 0, sizeof(DDSURFACEDESC2));
	ddsd.dwSize 					= sizeof(DDSURFACEDESC2);
	ddsd.dwFlags 				= DDSD_CAPS|DDSD_WIDTH|DDSD_HEIGHT|DDSD_PITCH|DDSD_TEXTURESTAGE|DDSD_PIXELFORMAT;
	ddsd.ddsCaps.dwCaps  	= DDSCAPS_TEXTURE   ;
	ddsd.ddsCaps.dwCaps2 	= DDSCAPS2_TEXTUREMANAGE;
	ddsd.dwWidth 				= _ftextureWIDTH;
	ddsd.dwHeight 				= _ftextureHEIGHT;
	ddsd.ddpfPixelFormat.dwSize 		= sizeof(DDPIXELFORMAT);
	ddsd.ddpfPixelFormat.dwFlags 	= DDPF_RGB | DDPF_ALPHAPIXELS ;
	ddsd.ddpfPixelFormat.dwRGBBitCount = 32;
	ddsd.ddpfPixelFormat.dwRBitMask = 0x00FF0000;
	ddsd.ddpfPixelFormat.dwGBitMask = 0x0000FF00;
	ddsd.ddpfPixelFormat.dwBBitMask = 0x000000FF;
	ddsd.ddpfPixelFormat.dwRGBAlphaBitMask = 0xFF000000 ;
    
    if(FAILED(  _directX->CreateSurface( &ddsd  ,  &_surface , NULL ) ) )
    {	
		    	return false ;
    }
		

    	ddsd.dwFlags 				= DDSD_PITCH ;
	_surface->GetSurfaceDesc(&ddsd);

	_surface->Lock( NULL , &ddsd, DDLOCK_SURFACEMEMORYPTR | DDLOCK_WAIT, NULL);
    unsigned char *ptr = (  unsigned char *)ddsd.lpSurface;
	long	surfacePitch		= ddsd.lPitch;
	unsigned	char r,g,b,a ;

	imageWidth 	= tgaInfo.width ;
	imageHeight 	= tgaInfo.height ;


	switch ( tgaInfo.bpp )
    {
    		case	32:
	    	     for ( x =0 ; x < imageWidth ; x++)
	  	      {
	            for ( y = 0 ; y < imageHeight ; y++ )
	            {
	                RGBQUAD color ;
	                color = cxImagePtr->GetPixelColor( x ,  imageHeight-(y+1)  , true ) ;
	                
	                r =   color.rgbRed  ;
	                g = color.rgbGreen  ;
	                b = color.rgbBlue ;
	                a = color.rgbReserved  ;
	                
	                if ( _ckActive == true && _ckr == r && _ckb == b && _ckg == g )
	                {
	                    a = 0 ;							
	                }
	                
	       	       ptr[4*x+y*(long)surfacePitch] 	 	= 	b ;				//r
	         	      ptr[4*x+y*(long)surfacePitch+1] 	=	g	 ;				//g
	          	     ptr[4*x+y*(long)surfacePitch+2] 	= r ;				//b
	                ptr[4*x+y*(long)surfacePitch+3] 	=	a  ;				//a							
	                
	            }	
			}//for x
    		break; //case 32
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
			                
			    	            ptr[4*x+y*(long)surfacePitch] 	 = 	b ;				//r
			    	            ptr[4*x+y*(long)surfacePitch+1]	 =	g	 ;				//g
			    	            ptr[4*x+y*(long)surfacePitch+2]	 = r ;				//b
			    	            ptr[4*x+y*(long)surfacePitch+3] =	a  ;				//a							
			                
			            }	
			        }
			break ;    		//default
 	   }

	_surface->Unlock( NULL );
	_d3d->PreLoad( _surface ) ;
     //free the memory where we loaded the tga
    delete cxImagePtr ;
    cxImagePtr = NULL ;

//	_ftextureHEIGHTM1	= _ftextureHEIGHT -1 ;
//	_ftextureWIDTHM1	= _ftextureWIDTH -1 ;

	return true ;
}


bool	KGraphicD3D::loadPicture32( const char	*filename  , const char	*filenameMask , bool hidef , bool hasAlpha )
{
    long						 x,y ;
    long						imageWidth , imageHeight ;
    tgaBitmap				tgaInfo ;
    CxImage				*cxImagePtr ;	
    CxImage				*cxImageMaskPtr = NULL ;	
    hasAlpha = hasAlpha ; 
    hidef = hidef ;
//    #pragma unused( hasAlpha )
//    #pragma unused( hidef )
    
    _maskedUsed = false ;
    
    if ( _directX == NULL ||  _d3d == NULL )		
    {
    		strcpy( imageFileName , "" ) ;
	    	//MessageBox( 0 , "directx not initialized",0,0 ) ;
	    	return false ;
	}

    strcpy( imageFileName , filename ) ;
    if ( filenameMask != NULL )
    {
       strcpy( imageMaskFileName , filenameMask ) ;
	}
	else
	{
	    strcpy( imageMaskFileName , "" ) ;
	}

    cxImagePtr = (CxImage*)LoadGeneric( filename ) ;
    if ( cxImagePtr == NULL  )	
    {
  	  	strcpy( imageFileName , "" ) ;
    		return false ;
 	}


	if ( filenameMask != NULL )
	{
		if ( strcmp( filenameMask , "" ) != 0 )
		{
			cxImageMaskPtr =  (CxImage*)LoadGeneric( filenameMask ) ;
			_maskedUsed = true ;
		}
	}

    
    tgaInfo.bpp = cxImagePtr->GetBpp( ) ;
    tgaInfo.width = cxImagePtr->GetWidth( ) ;
    tgaInfo.height = cxImagePtr->GetHeight( ) ;

    long nMaxDim;
    int nPow;

    nMaxDim = tgaInfo.width;
    if (tgaInfo.height > nMaxDim)
       nMaxDim = tgaInfo.height;

    for ( nPow = 30; ((1 << nPow) >= nMaxDim) && (nPow >= 0); nPow--) {;}
       nPow++;

    _ftextureWIDTH		=		1 << nPow ;
    _ftextureHEIGHT	=		1 << nPow ;
    fimageWidth = tgaInfo.width;
    fimageHeight =tgaInfo.height ;

    long ct = cxImagePtr->GetColorType( ) ;
    
    if ( ct == 4) 
    {
        tgaInfo.bpp  = 32 ;
    }
    
	//describe the texture
	DDSURFACEDESC2		ddsd ;
	memset(&ddsd, 0, sizeof(DDSURFACEDESC2));
	ddsd.dwSize 					= sizeof(DDSURFACEDESC2);
	ddsd.dwFlags 				= DDSD_CAPS|DDSD_WIDTH|DDSD_HEIGHT|DDSD_PITCH|DDSD_TEXTURESTAGE|DDSD_PIXELFORMAT;
	ddsd.ddsCaps.dwCaps  	= DDSCAPS_TEXTURE   ;
	ddsd.ddsCaps.dwCaps2 	= DDSCAPS2_TEXTUREMANAGE;
	ddsd.dwWidth 				= _ftextureWIDTH;
	ddsd.dwHeight 				= _ftextureHEIGHT;
	ddsd.ddpfPixelFormat.dwSize 		= sizeof(DDPIXELFORMAT);
	ddsd.ddpfPixelFormat.dwFlags 	= DDPF_RGB | DDPF_ALPHAPIXELS ;
	ddsd.ddpfPixelFormat.dwRGBBitCount = 32;
	ddsd.ddpfPixelFormat.dwRBitMask = 0x00FF0000;
	ddsd.ddpfPixelFormat.dwGBitMask = 0x0000FF00;
	ddsd.ddpfPixelFormat.dwBBitMask = 0x000000FF;
	ddsd.ddpfPixelFormat.dwRGBAlphaBitMask = 0xFF000000 ;
    
    if(FAILED(  _directX->CreateSurface( &ddsd  ,  &_surface , NULL ) ) )
    {	
		    	return false ;
    }
		

    	ddsd.dwFlags 				= DDSD_PITCH ;
	_surface->GetSurfaceDesc(&ddsd);

	_surface->Lock( NULL , &ddsd, DDLOCK_SURFACEMEMORYPTR | DDLOCK_WAIT, NULL);
    unsigned char *ptr = (  unsigned char *)ddsd.lpSurface;
	long	surfacePitch		= ddsd.lPitch;
	unsigned	char r,g,b,a ;

	imageWidth 	= tgaInfo.width ;
	imageHeight 	= tgaInfo.height ;


	switch ( tgaInfo.bpp )
    {
    		case	32:
	    	     for ( x =0 ; x < imageWidth ; x++)
	  	      {
	            for ( y = 0 ; y < imageHeight ; y++ )
	            {
	                RGBQUAD color ;
	                color = cxImagePtr->GetPixelColor( x ,  imageHeight-(y+1)  , true ) ;
	                
	                r =   color.rgbRed  ;
	                g = color.rgbGreen  ;
	                b = color.rgbBlue ;
	                a = color.rgbReserved  ;
	                if  ( cxImageMaskPtr != NULL )
			       {
				     a =  cxImageMaskPtr->GetPixelColor( x , imageHeight-(y+1) , true  ).rgbBlue ;
			       }
	                if ( _ckActive == true && _ckr == r && _ckb == b && _ckg == g )
	                {
	                    a = 0 ;							
	                }
	                
	       	       ptr[4*x+y*(long)surfacePitch] 	 	= 	b ;				//r
	         	      ptr[4*x+y*(long)surfacePitch+1] 	=	g	 ;				//g
	          	     ptr[4*x+y*(long)surfacePitch+2] 	= r ;				//b
	                ptr[4*x+y*(long)surfacePitch+3] 	=	a  ;				//a							
	                
	            }	
			}//for x
    		break; //case 32
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
			                if  ( cxImageMaskPtr != NULL )
			                {
				               a =  cxImageMaskPtr->GetPixelColor( x , imageHeight-(y+1) , true  ).rgbBlue ;
			                }
			                
			                if ( _ckActive == true && _ckr == r && _ckb == b && _ckg == g )
			                {
			                    a = 0 ;							
			                }
			                
			    	            ptr[4*x+y*(long)surfacePitch] 	 = 	b ;				//r
			    	            ptr[4*x+y*(long)surfacePitch+1]	 =	g	 ;				//g
			    	            ptr[4*x+y*(long)surfacePitch+2]	 = r ;				//b
			    	            ptr[4*x+y*(long)surfacePitch+3] =	a  ;				//a							
			                
			            }	
			        }
			break ;    		//default
 	   }

	_surface->Unlock( NULL );
	_d3d->PreLoad( _surface ) ;
     //free the memory where we loaded the tga
    delete cxImagePtr ;
    cxImagePtr = NULL ;
	if ( cxImageMaskPtr != NULL )
	{
		delete	cxImageMaskPtr ;
		cxImageMaskPtr = NULL ;
	}

//	_ftextureHEIGHTM1	= _ftextureHEIGHT -1 ;
//	_ftextureWIDTHM1	= _ftextureWIDTH -1 ;

	return true ;
}

bool			KGraphicD3D::loadPictureWithMask( const	char	*filename , const	char	*filenameMask , bool hiDef ) 
{
	freePicture( ) ;

	
	if ( hiDef == true )
	{
		return	loadPicture32( filename , filenameMask , hiDef , true ) ;
	}
	else
	{
		return	loadPicture16( filename , filenameMask  , hiDef , true ) ;	
	}

}




bool			KGraphicD3D::loadPicture2dFromPtr( const char	*filename , unsigned char	*dataPtr , unsigned long datasize , long tx, long ty )  
{
//    long						 x,y ;
    long						imageWidth , imageHeight ;
    tgaBitmap				tgaInfo ;
    CxImage				*cxImagePtr ;	
    
    _2dSurface = true ;
    
     if ( _directX == NULL ||  _d3d == NULL )		
    {  
    		  strcpy( imageFileName , "" ) ;
	    	//MessageBox( 0 , "directx not initialized",0,0 ) ;
	    	return false ;
	}
	
	freePicture( ) ;
	
	 strcpy( imageFileName , filename ) ;
	
    strcpy( imageFileName , filename ) ;
	
    cxImagePtr = (CxImage*)LoadGenericFromPtr( (char*)filename , dataPtr , datasize ) ;
    if ( cxImagePtr == NULL  )	
    {
  	  	strcpy( imageFileName , "" ) ;
    		return false ;
    	}

    
    	
    tgaInfo.bpp = cxImagePtr->GetBpp( ) ;
    tgaInfo.width = cxImagePtr->GetWidth( ) ;
    tgaInfo.height = cxImagePtr->GetHeight( ) ;
	imageWidth			= 	tgaInfo.width ;
	imageHeight  			=	tgaInfo.height ;
	_ftextureWIDTH		=	imageWidth ;
	_ftextureHEIGHT	=	imageHeight ;

    long ct = cxImagePtr->GetColorType( ) ;
    
    if ( ct == 4) 
    {
        tgaInfo.bpp  = 32 ;
    }
    
	//describe the texture
	DDSURFACEDESC2		ddsd ;
	memset(&ddsd, 0, sizeof(DDSURFACEDESC2));
	ddsd.dwSize 					= sizeof(DDSURFACEDESC2);
	
	ddsd.dwFlags 				= DDSD_CAPS|DDSD_WIDTH|DDSD_HEIGHT | DDSD_PITCH  ;
	ddsd.ddsCaps.dwCaps  	= DDSCAPS_OFFSCREENPLAIN | DDSCAPS_VIDEOMEMORY    ;
	
	ddsd.lPitch		=	_screenDepth ;
	ddsd.dwWidth 				= _ftextureWIDTH;
	ddsd.dwHeight 				= _ftextureHEIGHT;
	


HRESULT hr ;
	
	hr = _directX->CreateSurface( &ddsd , &_surface , NULL ) ;
	if ( hr != DD_OK )	
	{
	

		//test in AGP
		ddsd.ddsCaps.dwCaps  	=	DDSCAPS_NONLOCALVIDMEM  | DDSCAPS_OFFSCREENPLAIN  ;
		hr	=	_directX->CreateSurface(&ddsd , &_surface , NULL ) ;
		if ( hr != DD_OK )	
		{
			//test in  RAM
			ddsd.ddsCaps.dwCaps  	=	DDSCAPS_SYSTEMMEMORY | DDSCAPS_OFFSCREENPLAIN  ;
			hr	=	_directX->CreateSurface(&ddsd , &_surface , NULL ) ;
			if ( hr != DD_OK )	
			{
	 			strcpy( imageFileName , "" ) ;
				return false ;
			}
		}
	}

    	ddsd.dwFlags 				= DDSD_PITCH ;
	_surface->GetSurfaceDesc(&ddsd);
//	_surface->Lock( NULL , &ddsd, DDLOCK_SURFACEMEMORYPTR | DDLOCK_WAIT, NULL);
	
	HDC		dcsurface ;

	hr =  _surface->GetDC( &dcsurface ) ;
		cxImagePtr->Draw( dcsurface );
	_surface->ReleaseDC( dcsurface ) ;

	delete		cxImagePtr ;

	if ( tx <0 || ty < 0 )			return true ;

    	ddsd.dwFlags 				= DDSD_PITCH ;
	_surface->GetSurfaceDesc(&ddsd);
	_surface->Lock( NULL , &ddsd, DDLOCK_SURFACEMEMORYPTR | DDLOCK_WAIT, NULL);

	
long		*color32Ptr ;
short		*color16Ptr ;
long		color32 ;
short		color16 ;

long		surfacePitch ;
DDCOLORKEY  colork ;

//    DWORD dwColorSpaceLowValue; 
 //   DWORD dwColorSpaceHighValue; 

	_ckPixelX = tx ;
	_ckPixelY = ty ;

 color32Ptr 		= (  long *)ddsd.lpSurface;
 surfacePitch		= ddsd.lPitch;
 color16Ptr 		= (   short *)ddsd.lpSurface;
	
	color32Ptr	+=(tx + ty*(surfacePitch/4)) ;
	color16Ptr	+=(tx + ty*(surfacePitch/2)) ;

	color32 = *color32Ptr ;
	color16 = *color16Ptr	 ;


	_surface->Unlock( NULL  ) ;
	
	if (  _screenDepth == 32 )
	{
		colork.dwColorSpaceLowValue = color32 ;
		colork.dwColorSpaceHighValue = color32 ;
	}
	else
	{
		colork.dwColorSpaceLowValue = color16 ;
		colork.dwColorSpaceHighValue = color16 ;
	}

	_surface->SetColorKey( DDCKEY_SRCBLT  , &colork ) ;

	return true ;
}






//ddraw loading
bool			KGraphicD3D::loadPicture2d( const char	*filename ,  long tx, long ty ) 
{
//    long						 x,y ;
    long						imageWidth , imageHeight ;
    tgaBitmap				tgaInfo ;
    CxImage				*cxImagePtr ;	
    
    _2dSurface = true ;
    
     if ( _directX == NULL ||  _d3d == NULL )		
    {  
    		  strcpy( imageFileName , "" ) ;
	    	//MessageBox( 0 , "directx not initialized",0,0 ) ;
	    	return false ;
	}
	
	freePicture( ) ;
	
	 strcpy( imageFileName , filename ) ;
	
    cxImagePtr =   (CxImage*)LoadGeneric( filename ) ;
    if ( cxImagePtr == NULL  )	
    {
    	    strcpy( imageFileName , "" ) ;
    		return false ;
    	}
    	
    tgaInfo.bpp = cxImagePtr->GetBpp( ) ;
    tgaInfo.width = cxImagePtr->GetWidth( ) ;
    tgaInfo.height = cxImagePtr->GetHeight( ) ;
	imageWidth			= 	tgaInfo.width ;
	imageHeight  			=	tgaInfo.height ;
	_ftextureWIDTH		=	imageWidth ;
	_ftextureHEIGHT	=	imageHeight ;

    long ct = cxImagePtr->GetColorType( ) ;
    
    if ( ct == 4) 
    {
        tgaInfo.bpp  = 32 ;
    }
    
	//describe the texture
	DDSURFACEDESC2		ddsd ;
	memset(&ddsd, 0, sizeof(DDSURFACEDESC2));
	ddsd.dwSize 					= sizeof(DDSURFACEDESC2);
	
	ddsd.dwFlags 				= DDSD_CAPS|DDSD_WIDTH|DDSD_HEIGHT | DDSD_PITCH  ;
	ddsd.ddsCaps.dwCaps  	= DDSCAPS_OFFSCREENPLAIN | DDSCAPS_VIDEOMEMORY    ;
	
	ddsd.lPitch		=	_screenDepth ;
	ddsd.dwWidth 				= _ftextureWIDTH;
	ddsd.dwHeight 				= _ftextureHEIGHT;
	


HRESULT hr ;
	
	hr = _directX->CreateSurface( &ddsd , &_surface , NULL ) ;
	if ( hr != DD_OK )	
	{
	

		//test in AGP
		ddsd.ddsCaps.dwCaps  	=	DDSCAPS_NONLOCALVIDMEM  | DDSCAPS_OFFSCREENPLAIN  ;
		hr	=	_directX->CreateSurface(&ddsd , &_surface , NULL ) ;
		if ( hr != DD_OK )	
		{
			//test in  RAM
			ddsd.ddsCaps.dwCaps  	=	DDSCAPS_SYSTEMMEMORY | DDSCAPS_OFFSCREENPLAIN  ;
			hr	=	_directX->CreateSurface(&ddsd , &_surface , NULL ) ;
			if ( hr != DD_OK )	
			{
	 			strcpy( imageFileName , "" ) ;
				return false ;
			}
		}
	}

    	ddsd.dwFlags 				= DDSD_PITCH ;
	_surface->GetSurfaceDesc(&ddsd);
//	_surface->Lock( NULL , &ddsd, DDLOCK_SURFACEMEMORYPTR | DDLOCK_WAIT, NULL);
	
	HDC		dcsurface ;

	hr =  _surface->GetDC( &dcsurface ) ;
		cxImagePtr->Draw( dcsurface );
	_surface->ReleaseDC( dcsurface ) ;

	delete		cxImagePtr ;

	if ( tx <0 || ty < 0 )			return true ;

    	ddsd.dwFlags 				= DDSD_PITCH ;
	_surface->GetSurfaceDesc(&ddsd);
	_surface->Lock( NULL , &ddsd, DDLOCK_SURFACEMEMORYPTR | DDLOCK_WAIT, NULL);

	
long		*color32Ptr ;
short		*color16Ptr ;
long		color32 ;
short		color16 ;

long		surfacePitch ;
DDCOLORKEY  colork ;

//    DWORD dwColorSpaceLowValue; 
 //   DWORD dwColorSpaceHighValue; 

	_ckPixelX = tx ;
	_ckPixelY = ty ;

 color32Ptr 		= (  long *)ddsd.lpSurface;
 surfacePitch		= ddsd.lPitch;
 color16Ptr 		= (   short *)ddsd.lpSurface;
	
	color32Ptr	+=(tx + ty*(surfacePitch/4)) ;
	color16Ptr	+=(tx + ty*(surfacePitch/2)) ;

	color32 = *color32Ptr ;
	color16 = *color16Ptr	 ;


	_surface->Unlock( NULL  ) ;
	
	if (  _screenDepth == 32 )
	{
		colork.dwColorSpaceLowValue = color32 ;
		colork.dwColorSpaceHighValue = color32 ;
	}
	else
	{
		colork.dwColorSpaceLowValue = color16 ;
		colork.dwColorSpaceHighValue = color16 ;
	}

	_surface->SetColorKey( DDCKEY_SRCBLT  , &colork ) ;

	return true ;
}


void			KGraphicD3D::blitRect2d( float	x1, float y1 , float	x2 , float y2 , short	destX , short	destY  ) 
{
RECT		r ;
//HRESULT 		errorCooperative ;
long			dx1,dy1,dx2,dy2 ;
long			sx1,sy1,sx2,sy2 ;

	if ( _surface == NULL )		return ;
	if ( _backBuffer == NULL )		return ;

//	errorCooperative = _directX->TestCooperativeLevel() ;
 // 	if ( errorCooperative  != DD_OK ) 		return ;

	if( _surface->IsLost( ) == DDERR_SURFACELOST  )
	{
		reloadSurface( ) ;
		return ;
	}

	sx1 = x1 ;
	sy1 = y1 ;
	sx2 = x2 ;
	sy2 = y2 ;

	dx1 = destX ;
	dy1 = destY ;
	dx2 = destX+(x2-x1) ;
	dy2 = destY+(y2-y1) ;
	
	//traite le cas de clipping numero 1
	if ( dx1 < 0 )
	{
		x1 += (-dx1) ;
		dx1 = 0 ;
	}

	if ( dy1 < 0 )
	{
		y1 += (-dy1) ;
		dy1 = 0 ;
	}

	if ( dx2 >=_screenWidth )
	{
		sx2 = sx2-(dx2-_screenWidth) ;
	}
	
	if ( dy2 >= _screenHeight )
	{
		sy2 = sy2-(dy2-_screenHeight) ;
	}
	
	x1 = sx1 ;
	x2 = sx2 ;
	y1 = sy1 ;
	y2 = sy2 ;
	destX = dx1 ;
	destY = dy1 ;
	
	SetRect( &r , x1 , y1 ,  x2 , y2 ) ;
	
	_backBuffer->BltFast( destX , destY , _surface , &r , DDBLTFAST_NOCOLORKEY  ) ;

}



void			KGraphicD3D::blitAlphaRect2d( float	x1, float y1 , float	x2 , float y2 , short	destX , short	destY  ) 
{
RECT		r ;
//HRESULT 		errorCooperative ;
long			dx1,dy1,dx2,dy2 ;
long			sx1,sy1,sx2,sy2 ;

	if ( _surface == NULL )		return ;
	if ( _backBuffer == NULL )		return ;

//	errorCooperative = _directX->TestCooperativeLevel() ;
 // 	if ( errorCooperative  != DD_OK ) 		return ;

	if( _surface->IsLost( ) == DDERR_SURFACELOST  )
	{
		reloadSurface( ) ;
		return ;
	}

	sx1 = x1 ;
	sy1 = y1 ;
	sx2 = x2 ;
	sy2 = y2 ;

	dx1 = destX ;
	dy1 = destY ;
	dx2 = destX+(x2-x1) ;
	dy2 = destY+(y2-y1) ;
	
	//traite le cas de clipping numero 1
	if ( dx1 < 0 )
	{
		x1 += (-dx1) ;
		dx1 = 0 ;
	}

	if ( dy1 < 0 )
	{
		y1 += (-dy1) ;
		dy1 = 0 ;
	}

	if ( dx2 >=_screenWidth )
	{
		sx2 = sx2-(dx2-_screenWidth) ;
	}
	
	if ( dy2 >= _screenHeight )
	{
		sy2 = sy2-(dy2-_screenHeight) ;
	}
	
	x1 = sx1 ;
	x2 = sx2 ;
	y1 = sy1 ;
	y2 = sy2 ;
	destX = dx1 ;
	destY = dy1 ;
	
	SetRect( &r , x1 , y1 ,  x2 , y2 ) ;
	
	_backBuffer->BltFast( destX , destY , _surface , &r , DDBLTFAST_SRCCOLORKEY  ) ;

}


bool	KGraphicD3D::loadPicture( const char	*filename , bool hidef , bool hasAlpha )
{
	freePicture( ) ;
	_hidef 			= 	hidef ;
	_hasAlpha		=	hasAlpha ;

    _2dSurface = false ;


	if ( hidef == true )
	{
		return	loadPicture32( filename , NULL , hidef , hasAlpha ) ;
	}

	return	loadPicture16( filename , NULL  , hidef , hasAlpha ) ;	
}

bool	KGraphicD3D::loadPictureFromPtr( const char	*filename ,unsigned char *dataPtr , unsigned long size ,  bool hidef , bool hasAlpha )
{
	freePicture( ) ;
	_hidef 			= 	hidef ;
	_hasAlpha		=	hasAlpha ;
    _2dSurface = false ;


	if ( hidef == true )
	{
		return	loadPicture32Ptr( filename , dataPtr , size , hidef , hasAlpha ) ;
	}

	return	loadPicture16Ptr( filename , dataPtr , size , hidef , hasAlpha ) ;	
}

bool	KGraphicD3D::loadPicture16Ptr( const char	*filename , unsigned char* dataPtr , unsigned long size , bool hidef , bool hasAlpha )
{
    long						 x,y ;
    long						imageWidth , imageHeight ;
    tgaBitmap				tgaInfo ;
    CxImage				*cxImagePtr ;	
    
   // #pragma unused( hasAlpha )
  //  #pragma unused( hidef )
    hidef  = hidef ;

    
    if ( _directX == NULL ||  _d3d == NULL )		
    {  
    		  strcpy( imageFileName , "" ) ;
	    	//MessageBox( 0 , "directx not initialized",0,0 ) ;
	    	return false ;
	}

    strcpy( imageFileName , filename ) ;
	
    cxImagePtr = (CxImage*)LoadGenericFromPtr( ( char*)filename , dataPtr, size) ;
    if ( cxImagePtr == NULL  )	
    {
    	    strcpy( imageFileName , "" ) ;
    		return false ;
    	}
    
   
    
    
    tgaInfo.bpp = cxImagePtr->GetBpp( ) ;
    tgaInfo.width = cxImagePtr->GetWidth( ) ;
    tgaInfo.height = cxImagePtr->GetHeight( ) ;

    long nMaxDim;
    int nPow;

    nMaxDim = tgaInfo.width;
    if (tgaInfo.height > nMaxDim)
       nMaxDim = tgaInfo.height;

    for ( nPow = 30; ((1 << nPow) >= nMaxDim) && (nPow >= 0); nPow--) {;}
       nPow++;

    _ftextureWIDTH		=		1 << nPow ;
    _ftextureHEIGHT	=		1 << nPow ;
    fimageWidth = tgaInfo.width;
    fimageHeight =tgaInfo.height ;

    long ct = cxImagePtr->GetColorType( ) ;
    
    if ( ct == 4) 
    {
        tgaInfo.bpp  = 32 ;
    }
    
	//describe the texture
	DDSURFACEDESC2		ddsd ;
	memset(&ddsd, 0, sizeof(DDSURFACEDESC2));
	ddsd.dwSize 					= sizeof(DDSURFACEDESC2);
	ddsd.dwFlags 				= DDSD_CAPS|DDSD_WIDTH|DDSD_HEIGHT|DDSD_PITCH|DDSD_TEXTURESTAGE|DDSD_PIXELFORMAT;
	ddsd.ddsCaps.dwCaps  	= DDSCAPS_TEXTURE   ;
	ddsd.ddsCaps.dwCaps2 	= DDSCAPS2_TEXTUREMANAGE;
	ddsd.dwWidth 				= _ftextureWIDTH;
	ddsd.dwHeight 				= _ftextureHEIGHT;
	ddsd.ddpfPixelFormat.dwSize 		= sizeof(DDPIXELFORMAT);

	if ( hasAlpha == false ||  tgaInfo.bpp  < 32)
	{
		ddsd.ddpfPixelFormat.dwFlags 	= DDPF_RGB   ;
		ddsd.ddpfPixelFormat.dwRBitMask = 0x001F << 10;
		ddsd.ddpfPixelFormat.dwGBitMask = 0x001F << 5 ;
		ddsd.ddpfPixelFormat.dwBBitMask = 0x001F;
		//ddsd.ddpfPixelFormat.dwRGBAlphaBitMask = 1 << 15 ;
		hasAlpha = false ;
	}
	else
	{
	
		ddsd.ddpfPixelFormat.dwFlags 	= DDPF_RGB | DDPF_ALPHAPIXELS ;
		ddsd.ddpfPixelFormat.dwRBitMask = 0x0f00;
		ddsd.ddpfPixelFormat.dwGBitMask = 0x000f0;
		ddsd.ddpfPixelFormat.dwBBitMask = 0x000f;
		ddsd.ddpfPixelFormat.dwRGBAlphaBitMask = 0xf000 ;
	}

	ddsd.ddpfPixelFormat.dwRGBBitCount = 16 ;
	
    
    if(FAILED(  _directX->CreateSurface( &ddsd  ,  &_surface , NULL ) ) )
    {
		    	return false ;
    }

    	ddsd.dwFlags 				= DDSD_PITCH ;
	_surface->GetSurfaceDesc(&ddsd);

	_surface->Lock( NULL , &ddsd, DDLOCK_SURFACEMEMORYPTR | DDLOCK_WAIT, NULL);
   unsigned short *ptr = (  unsigned short *)ddsd.lpSurface;
	long	surfacePitch		= ddsd.lPitch;
	unsigned	char r,g,b,a ;

	imageWidth 	= tgaInfo.width ;
	imageHeight 	= tgaInfo.height ;

	unsigned short	scolor , tr,tb,tg ,ta  ;
	
	switch ( tgaInfo.bpp )
    {
 		case	32:
	    	     for ( x =0 ; x < imageWidth ; x++)
	  	      {
	            for ( y = 0 ; y < imageHeight ; y++ )
	            {
	                RGBQUAD color ;
	                color = cxImagePtr->GetPixelColor( x ,  imageHeight-(y+1)  , true ) ;
	                
	                r =   color.rgbRed  ;
	                g = color.rgbGreen  ;
	                b = color.rgbBlue ;
	                a = color.rgbReserved  ;
	                
	                if ( _ckActive == true && _ckr == r && _ckb == b && _ckg == g )
	                {
	                    a = 0 ;							
	                }
	               if ( hasAlpha == true )
	                {
	                	tr = r >> 4 ; 
	                	tg = g >> 4 ; 
	                	tb = b >> 4 ; 
	                	ta = a >> 4 ; 
		                scolor = ( tr << 8 )  | ( tg << 4 )  | tb| (ta << 12 ) ;
	                }
	   		       else
	                {  
	                	 tr = r / 8 ; 
	        	  		 tg = g / 8 ; 
			          tb = b / 8 ; 
	                    scolor = ( tr << 10 )  | ( tg << 5 )  | tb ;					
				  }                
	                
	       	       ptr[x+y*(long)surfacePitch/2] 	 	= 	scolor ;				//r
	                
	            }	
			}//for x
    		break; //case 32

    		 default:
			        
			        //8 or 16 or 24 bits
			        for ( x =0 ; x < imageWidth ; x++)
			        {
			            for ( y = 0 ; y < imageHeight ; y++ )
			            {
			                RGBQUAD color ;
			                color = cxImagePtr->GetPixelColor( x ,  imageHeight-(y+1)  , false ) ;
			                
			                r =   color.rgbRed  ;
			                g = color.rgbGreen  ;
			                b = color.rgbBlue ;
			                a = 255 ;
			                
			                if ( _ckActive == true && _ckr == r && _ckb == b && _ckg == g )
			                {
			                    a = 0 ;							
			                }
			  
			                 tr = r / 8 ; 
	        	  			   tg = g / 8 ; 
			        	        tb = b / 8 ; 
	                
			             	   scolor = ( tr << 10 )  | ( tg << 5 )  | tb ;
				    	       ptr[x+y*(long)surfacePitch/2] 	 	= 	scolor ;								                
			            }	
			        }
			break ;    		//default
 	   }

	_surface->Unlock( NULL );
	
	_d3d->PreLoad( _surface ) ;

     //free the memory where we loaded the tga
    delete cxImagePtr ;
    cxImagePtr = NULL ;

//	_ftextureHEIGHT	= _ftextureHEIGHT -1 ;
//	_ftextureWIDTH	= _ftextureWIDTH -1 ;

	return true ;
}



bool	KGraphicD3D::loadPicture16( const char	*filename , const char	*filenamemask ,bool hidef , bool hasAlpha )
{
    long						 x,y ;
    long						imageWidth , imageHeight ;
    tgaBitmap				tgaInfo ;
    CxImage				*cxImagePtr ;	
    CxImage				*cxImageMaskPtr = NULL ;	
    
   // #pragma unused( hasAlpha )
  //  #pragma unused( hidef )
    hidef  = hidef ;

    _maskedUsed = false ;
    if ( _directX == NULL ||  _d3d == NULL )		
    {  
    		  strcpy( imageFileName , "" ) ;
	    	//MessageBox( 0 , "directx not initialized",0,0 ) ;
	    	return false ;
	}

    strcpy( imageFileName , filename ) ;
   
    if ( filenamemask != NULL )
    {
       strcpy( imageMaskFileName , filenamemask ) ;
	}
	else
	{
	    strcpy( imageMaskFileName , "" ) ;
	}
	
    cxImagePtr = (CxImage*)LoadGeneric( filename ) ;
    if ( cxImagePtr == NULL  )	
    {
    	    strcpy( imageFileName , "" ) ;
    		return false ;
    	}

	if ( filenamemask != NULL )
	{
		if ( strcmp( filenamemask , "" ) != 0 )
		{
			cxImageMaskPtr =  (CxImage*)LoadGeneric( filenamemask ) ;
			_maskedUsed = true ;
		}
	}

    
    
    tgaInfo.bpp = cxImagePtr->GetBpp( ) ;
    tgaInfo.width = cxImagePtr->GetWidth( ) ;
    tgaInfo.height = cxImagePtr->GetHeight( ) ;

    long nMaxDim;
    int nPow;

    nMaxDim = tgaInfo.width;
    if (tgaInfo.height > nMaxDim)
       nMaxDim = tgaInfo.height;

    for ( nPow = 30; ((1 << nPow) >= nMaxDim) && (nPow >= 0); nPow--) {;}
       nPow++;

    _ftextureWIDTH		=		1 << nPow ;
    _ftextureHEIGHT	=		1 << nPow ;
    fimageWidth = tgaInfo.width;
    fimageHeight =tgaInfo.height ;

    long ct = cxImagePtr->GetColorType( ) ;
    
    if ( ct == 4) 
    {
        tgaInfo.bpp  = 32 ;
    }
    
	//describe the texture
	DDSURFACEDESC2		ddsd ;
	memset(&ddsd, 0, sizeof(DDSURFACEDESC2));
	ddsd.dwSize 					= sizeof(DDSURFACEDESC2);
	ddsd.dwFlags 				= DDSD_CAPS|DDSD_WIDTH|DDSD_HEIGHT|DDSD_PITCH|DDSD_TEXTURESTAGE|DDSD_PIXELFORMAT;
	ddsd.ddsCaps.dwCaps  	= DDSCAPS_TEXTURE   ;
	ddsd.ddsCaps.dwCaps2 	= DDSCAPS2_TEXTUREMANAGE;
	ddsd.dwWidth 				= _ftextureWIDTH;
	ddsd.dwHeight 				= _ftextureHEIGHT;
	ddsd.ddpfPixelFormat.dwSize 		= sizeof(DDPIXELFORMAT);

	if ( hasAlpha == true ||  tgaInfo.bpp  >= 32)
	{
		ddsd.ddpfPixelFormat.dwFlags 	= DDPF_RGB | DDPF_ALPHAPIXELS ;
		ddsd.ddpfPixelFormat.dwRBitMask = 0x0f00;
		ddsd.ddpfPixelFormat.dwGBitMask = 0x000f0;
		ddsd.ddpfPixelFormat.dwBBitMask = 0x000f;
		ddsd.ddpfPixelFormat.dwRGBAlphaBitMask = 0xf000 ;
	}
	else
	{
		ddsd.ddpfPixelFormat.dwFlags 	= DDPF_RGB   ;
		ddsd.ddpfPixelFormat.dwRBitMask = 0x001F << 10;
		ddsd.ddpfPixelFormat.dwGBitMask = 0x001F << 5 ;
		ddsd.ddpfPixelFormat.dwBBitMask = 0x001F;
		//ddsd.ddpfPixelFormat.dwRGBAlphaBitMask = 1 << 15 ;
		hasAlpha = false ;
	
	}

	ddsd.ddpfPixelFormat.dwRGBBitCount = 16 ;
	
    
    if(FAILED(  _directX->CreateSurface( &ddsd  ,  &_surface , NULL ) ) )
    {
		    	return false ;
    }

    	ddsd.dwFlags 				= DDSD_PITCH ;
	_surface->GetSurfaceDesc(&ddsd);

	_surface->Lock( NULL , &ddsd, DDLOCK_SURFACEMEMORYPTR | DDLOCK_WAIT, NULL);
   unsigned short *ptr = (  unsigned short *)ddsd.lpSurface;
	long	surfacePitch		= ddsd.lPitch;
	unsigned	char r,g,b,a ;

	imageWidth 	= tgaInfo.width ;
	imageHeight 	= tgaInfo.height ;

	unsigned short	scolor , tr,tb,tg ,ta  ;
	
	switch ( tgaInfo.bpp )
    {
 		case	32:
	    	     for ( x =0 ; x < imageWidth ; x++)
	  	      {
	            for ( y = 0 ; y < imageHeight ; y++ )
	            {
	                RGBQUAD color ;
	                color = cxImagePtr->GetPixelColor( x ,  imageHeight-(y+1)  , true ) ;
	                
	                r =   color.rgbRed  ;
	                g = color.rgbGreen  ;
	                b = color.rgbBlue ;
	                a = color.rgbReserved  ;
	                 if  ( cxImageMaskPtr != NULL )
			       {
				     a =  cxImageMaskPtr->GetPixelColor( x , imageHeight-(y+1) , true  ).rgbBlue ;
			       }
			       
	                if ( _ckActive == true && _ckr == r && _ckb == b && _ckg == g )
	                {
	                    a = 0 ;							
	                }
	               if ( hasAlpha == true )
	                {
	                	tr = r >> 4 ; 
	                	tg = g >> 4 ; 
	                	tb = b >> 4 ; 
	                	ta = a >> 4 ; 
		                scolor = ( tr << 8 )  | ( tg << 4 )  | tb| (ta << 12 ) ;
	                }
	   		       else
	                {  
	                	 tr = r / 8 ; 
	        	  		 tg = g / 8 ; 
			          tb = b / 8 ; 
	                    scolor = ( tr << 10 )  | ( tg << 5 )  | tb ;					
				  }                
	                
	       	       ptr[x+y*(long)surfacePitch/2] 	 	= 	scolor ;				//r
	                
	            }	
			}//for x
    		break; //case 32

    		 default:
			        
			        //8 or 16 or 24 bits
			        for ( x =0 ; x < imageWidth ; x++)
			        {
			            for ( y = 0 ; y < imageHeight ; y++ )
			            {
			                RGBQUAD color ;
			                color = cxImagePtr->GetPixelColor( x ,  imageHeight-(y+1)  , false ) ;
			                
			                r =   color.rgbRed  ;
			                g = color.rgbGreen  ;
			                b = color.rgbBlue ;
			                a = 255 ;
		                     if  ( cxImageMaskPtr != NULL )
					       {
						     a =  cxImageMaskPtr->GetPixelColor( x , imageHeight-(y+1) , true  ).rgbBlue ;
			       		}
			                if ( _ckActive == true && _ckr == r && _ckb == b && _ckg == g )
			                {
			                    a = 0 ;							
			                }
			
						//alpha or not alpha
			              if ( hasAlpha == true )
	         		       {
		                	tr = r >> 4 ; 
	        		       	tg = g >> 4 ; 
		         	       	tb = b >> 4 ; 
	         		       	ta = a >> 4 ; 
		        	        scolor = ( tr << 8 )  | ( tg << 4 )  | tb| (ta << 12 ) ;
	    		            }
	   			       else
		   		       {
				                 tr = r / 8 ; 
		        	  			   tg = g / 8 ; 
				        	        tb = b / 8 ; 
	                
				            	   scolor = ( tr << 10 )  | ( tg << 5 )  | tb ;
		            	   }
			            	   
			            	//store the pixel value	   
				    	       ptr[x+y*(long)surfacePitch/2] 	 	= 	scolor ;								                
			            }	
			            
			        }
			break ;    		//default
 	   }

	_surface->Unlock( NULL );
	
	_d3d->PreLoad( _surface ) ;

     //free the memory where we loaded the tga
    delete cxImagePtr ;
    cxImagePtr = NULL ;
    if  ( cxImageMaskPtr != NULL )
    {
	   delete cxImageMaskPtr ;
    }
      
//	_ftextureHEIGHT	= _ftextureHEIGHT -1 ;
//	_ftextureWIDTH	= _ftextureWIDTH -1 ;

	return true ;
}


unsigned	char*		KGraphicD3D::LoadGenericFromPtr( char	*filename , unsigned char *buffer , unsigned long size )
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


unsigned	char*		KGraphicD3D::LoadGeneric( const char	*filename )
{
    
    unsigned	char	*imageBits = NULL ;
    CxImage	*cxi = NULL ;
    KResource resImage;
    KResourceResult result;
    BYTE *buffer;
    int size = 0;
    
//    strlwr( filename ) ;
    result = resImage.open (filename, K_RES_READ);
    if (result != K_RES_OK) return NULL;

    resImage.seek (K_RES_END, 0);
    result = resImage.tell (size);
    if ((result != K_RES_OK) || (!size)) return NULL;
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

	delete	[]    buffer ;
    return	(unsigned char*)cxi ; 
    
}


void			KGraphicD3D::blitAlphaRect( float	x1, float y1 , float	x2 , float y2 , short	destX , short	destY, bool flipx  , bool flipy  ) 
{

 	if ( _directX->TestCooperativeLevel() != DD_OK)		return ;
 	
 
	if ( _surface == NULL )
	{
			#ifdef LOGZEERRORS
				logerror( " KGraphicD3D::blitAlphaRect  _surface == NULL\r\n" ) ;
			#endif
			return ;
			
	}
		
	if ( D3D_OK != _d3d->SetRenderState(D3DRENDERSTATE_ALPHABLENDENABLE, true) )
	{
		#ifdef LOGZEERRORS
			logerror( " KGraphicD3D::blitAlphaRect  _d3d->SetRenderState(D3DRENDERSTATE_ALPHABLENDENABLE, true)\r\n" ) ;
		#endif
		return ;
	}

	GenericBlit(x1, y1, x2, y2, destX, destY, flipx, flipy) ;

}


#define  M_PI        3.14159265358979323846f
#define  M_2PI       (2.0f * M_PI)

void			KGraphicD3D::blitAlphaRectFx( float	x1, float y1 , float	x2 , float y2 , short	destX , short	destY, float angle, float zoom, float blend , bool flipx , bool flipy , float centerX , float centerY  ) 
{
float middlesizeX, middlesizeY;
long	vx,vy ;

	long iw ,ih ;

	iw = x2-x1 ;
	ih = y2-y1 ;
		
	if ( blend <= 0 )					return ;

	if ( _surface == NULL )		return ;

	if(zoom == 0)		return;

	vx = ( x2-x1)/2 + centerX ;
	vy = ( y2-y1)/2 + centerY ;
	
 	middlesizeX	=	vx;
	middlesizeY	=	vy ;
	
	D3DXMATRIX worldMatrix;
	_d3d->GetTransform(D3DTRANSFORMSTATE_WORLD, (LPD3DMATRIX)&worldMatrix); // sauvegarde de la matrice

	D3DXMATRIX translateMatrix;
	D3DXMATRIX rotateMatrix;
	D3DXMATRIX scaleMatrix;

	D3DXMATRIX worldMatrix2;
	D3DXMatrixIdentity( &worldMatrix2 );

	float x = (x2-x1) * 0.5f + centerX;
	float y = (y2-y1) * 0.5f + centerY;

	D3DXMatrixTranslation( &translateMatrix, -x, y, 0 );
	D3DXMatrixMultiply( &worldMatrix2, &worldMatrix2, &translateMatrix );

	D3DXMatrixRotationZ( &rotateMatrix, angle / 180 * 3.14159265358979323846f );
	D3DXMatrixMultiply( &worldMatrix2, &worldMatrix2, &rotateMatrix );

	D3DXMatrixScaling( &scaleMatrix, zoom, zoom, 0 );
	D3DXMatrixMultiply( &worldMatrix2, &worldMatrix2, &scaleMatrix );

	D3DXMatrixTranslation( &translateMatrix, x+destX, -y-destY, 0 );
	D3DXMatrixMultiply( &worldMatrix2, &worldMatrix2, &translateMatrix );

	D3DXMatrixMultiply( &worldMatrix2, &worldMatrix2, &worldMatrix );

	_d3d->SetTransform(D3DTRANSFORMSTATE_WORLD, (LPD3DMATRIX)&worldMatrix2);

	_blend = blend ;

	blitAlphaRect(x1, y1, x2, y2, 0, 0, flipx, flipy);
	_blend =1 ;
	_d3d->SetTransform(D3DTRANSFORMSTATE_WORLD, (LPD3DMATRIX)&worldMatrix);
}


void	KGraphicD3D::setTextureQuality(bool	highquality )
{
	_textureQuality = highquality ;
// of course we want some bilinear filtering
 //   D3Ddevice->SetTextureStageState(0,D3DTSS_MAGFILTER, D3DTEXF_LINEAR);
//    D3Ddevice->SetTextureStageState(0,D3DTSS_MINFILTER, D3DTEXF_LINEAR);
	if (highquality == false )
	{
    		_textureQualityD3D = D3DTFG_POINT ;
    }
    else
    {
    		_textureQualityD3D = D3DTFG_LINEAR ;
    }

}


void			KGraphicD3D::blitRectFx( float	x1, float y1 , float	x2 , float y2 , short	destX , short	destY, float angle, float zoom, bool flipx , bool flipy) 
{
float middlesizeX, middlesizeY;

	if ( _surface == NULL )		return ;

	if(zoom == 0)		return;

	middlesizeX	= (x2-x1)/2;
	middlesizeY	= (y2-y1)/2;

	D3DMATRIX m1, m2, m3;
	_d3d->GetTransform(D3DTRANSFORMSTATE_WORLD, &m3); // sauvegarde de la matrice

	translate(m1, -middlesizeX, middlesizeY, 0);
	rotatez(m2, angle);
	m1 = m1*m2;
	scale(m2, zoom, zoom, 0);
	m1 = m1*m2;
	_d3d->GetTransform(D3DTRANSFORMSTATE_WORLD, &m2);
	m1 = m1*m2;
	_d3d->SetTransform(D3DTRANSFORMSTATE_WORLD, &m1);

	_blend = 1 ;

	blitRect(x1, y1, x2, y2, destX+middlesizeX*zoom, destY+middlesizeY*zoom, flipx, flipy);
	_d3d->SetTransform(D3DTRANSFORMSTATE_WORLD, &m3); // restauration de la matrice

}
/*
void		KGraphicD3D::d3dTextureToTGA( char *sourcefilename , char *destFilename)
{
HRESULT		hr ;
unsigned long		mipmap = D3DX_TEXTURE_NOMIPMAP ;
unsigned long		flag = D3DX_TEXTURE_NOMIPMAP , width = D3DX_DEFAULT ,height = D3DX_DEFAULT ;
LPDIRECTDRAWSURFACE7 ppDDSurf  =NULL ;
D3DX_SURFACEFORMAT		pixelFormat = D3DX_SF_A8R8G8B8 ;
unsigned long					*pixelPtr	= NULL ,w,h ,x,y , *surfacePtr;
				 
	if ( _d3d == NULL )
	{
			MessageBox( 0 , "d3d not initialised" ,0,0 ) ;
			return ;
	}

		
hr =  D3DXCreateTextureFromFile( _d3d , 
									&flag ,  //flags
									NULL ,		//width
									NULL, 		//height
									 &pixelFormat  , 	//format
									NULL , ///no palette
									&ppDDSurf , //surface returned
									&mipmap ,	//mipmap generated ?
									sourcefilename,
									D3DX_FT_POINT  ) ;
																

	switch( hr )
	{
		case	D3DERR_TEXTURE_NO_SUPPORT:
			MessageBox( 0 , "D3DERR_TEXTURE_NO_SUPPORT",0,0 ) ;
		break ;
		case	D3DXERR_D3DXNOTSTARTEDYET:
			MessageBox( 0 , "D3DXERR_D3DXNOTSTARTEDYET",0,0 ) ;
		break ;
		case	D3DXERR_INVALIDFILEFORMAT:
			MessageBox( 0 , "D3DXERR_INVALIDFILEFORMAT",0,0 ) ;
		break ;
		case	D3DXERR_INVALIDPARAMETER:
			MessageBox( 0 , "D3DXERR_INVALIDPARAMETER",0,0 ) ;
		break ;
		case	D3DXERR_NOMATCHFOUND:
			MessageBox( 0 , "D3DXERR_NOMATCHFOUND",0,0 ) ;
		break ;
		case	D3DXERR_NOMEMORY:
			MessageBox( 0 , "D3DXERR_NOMEMORY",0,0 ) ;
		break ;
	}

	


	if ( ppDDSurf == NULL)
	{
		MessageBox( 0 ,"couldn't load " , sourcefilename , 0 ) ;
		return ;
	}

DDSURFACEDESC2	ddesc ;

	memset( &ddesc , 0 , sizeof( DDSURFACEDESC2 ) ) ;
	ddesc.dwSize = sizeof( DDSURFACEDESC2 ) ;
	ddesc.dwFlags  = DDSD_HEIGHT | DDSD_WIDTH | DDSD_LPSURFACE  | DDSD_PITCH  ;


	ppDDSurf->Lock( NULL , &ddesc , 0 , 0 ) ;
  
	w = ddesc.dwWidth ;
	h = ddesc.dwHeight ; 
	surfacePtr =   (unsigned long*)ddesc.lpSurface ;

	pixelPtr = new unsigned long[ w * h ] ;

	for ( x = 0 ; x < w ;x++ )
	{
		for ( y = 0 ; y < h ;y++ )
		{
			pixelPtr[x+(h-(y+1))*w] = surfacePtr[x+y*ddesc.lPitch/4] ;
		}
	}

	
    CxImage		*cix ;
    
    cix = new  CxImage ;
    cix->CreateFromArray( (unsigned char*)pixelPtr , w , h , 32 , w*4 , false ) ;
	cix->Save( destFilename , CXIMAGE_FORMAT_TGA ) ;
    
    delete	cix ;

	delete [] pixelPtr  ;

	ppDDSurf->Unlock( NULL ) ;		

	ppDDSurf->Release( ) ;
}

*/

//blitting in sub pixels
void			KGraphicD3D::blitRectF( float	x1, float y1 , float	x2 , float y2 , float	destX , float	destY , bool flipx  , bool flipy ) 
{
	if ( _surface == NULL )		return ;
	_d3d->SetRenderState(D3DRENDERSTATE_ALPHABLENDENABLE, false);
	GenericBlit(x1, y1, x2, y2, destX, destY, flipx, flipy) ;
}

//blitting in sub pixels
void			KGraphicD3D::blitRectFxF( float	x1, float y1 , float	x2 , float y2 , float destX , float	destY, float angle, float zoom, bool flipx, bool flipy) 
{
float middlesizeX, middlesizeY;

	if ( _surface == NULL )		return ;

	if(zoom == 0)		return;

	middlesizeX	= (x2-x1)/2;
	middlesizeY	= (y2-y1)/2;

	D3DMATRIX m1, m2, m3;
	_d3d->GetTransform(D3DTRANSFORMSTATE_WORLD, &m3); // sauvegarde de la matrice

	translate(m1, -middlesizeX, middlesizeY, 0);
	rotatez(m2, angle);
	m1 = m1*m2;
	scale(m2, zoom, zoom, 0);
	m1 = m1*m2;
	_d3d->GetTransform(D3DTRANSFORMSTATE_WORLD, &m2);
	m1 = m1*m2;
	_d3d->SetTransform(D3DTRANSFORMSTATE_WORLD, &m1);

	_blend = 1 ;

	blitRectF(x1, y1, x2, y2, destX+middlesizeX*zoom, destY+middlesizeY*zoom, flipx, flipy);
	_d3d->SetTransform(D3DTRANSFORMSTATE_WORLD, &m3); // restauration de la matrice
}

//blitting in sub pixels
void			KGraphicD3D::blitAlphaRectF( float	x1, float y1 , float	x2 , float y2 , float destX , float	destY, bool flipx , bool flipy  ) 
{
	if ( _surface == NULL )		return ;
	_d3d->SetRenderState(D3DRENDERSTATE_ALPHABLENDENABLE, true);

	GenericBlit(x1, y1, x2, y2, destX, destY, flipx, flipy) ;
}

//blitting in sub pixels
void			KGraphicD3D::blitAlphaRectFxF( float	x1, float y1 , float	x2 , float y2 , float 	destX , float	destY, float angle, float zoom, float blend , bool flipx , bool flipy , float centerX , float centerY  )  
{
float middlesizeX, middlesizeY;
	
	if ( blend <= 0 )					return ;

	if ( _surface == NULL )		return ;

	if(zoom == 0)		return;

    middlesizeX	=	(x2-x1)/2 + centerX ;
    middlesizeY	=	(y2-y1)/2 + centerY ;

	D3DXMATRIX worldMatrix;
	_d3d->GetTransform(D3DTRANSFORMSTATE_WORLD, (LPD3DMATRIX)&worldMatrix); // sauvegarde de la matrice

	D3DXMATRIX translateMatrix;
	D3DXMATRIX rotateMatrix;
	D3DXMATRIX scaleMatrix;

	D3DXMATRIX worldMatrix2;
	D3DXMatrixIdentity( &worldMatrix2 );

	float x = (x2-x1) * 0.5f + centerX;
	float y = (y2-y1) * 0.5f + centerY;

	D3DXMatrixTranslation( &translateMatrix, -x, y, 0 );
	D3DXMatrixMultiply( &worldMatrix2, &worldMatrix2, &translateMatrix );

	D3DXMatrixRotationZ( &rotateMatrix, angle / 180 * 3.14159265358979323846f );
	D3DXMatrixMultiply( &worldMatrix2, &worldMatrix2, &rotateMatrix );

	D3DXMatrixScaling( &scaleMatrix, zoom, zoom, 0 );
	D3DXMatrixMultiply( &worldMatrix2, &worldMatrix2, &scaleMatrix );

	D3DXMatrixTranslation( &translateMatrix, x+destX, -y-destY, 0 );
	D3DXMatrixMultiply( &worldMatrix2, &worldMatrix2, &translateMatrix );

	D3DXMatrixMultiply( &worldMatrix2, &worldMatrix2, &worldMatrix );

	_d3d->SetTransform(D3DTRANSFORMSTATE_WORLD, (LPD3DMATRIX)&worldMatrix2);

	_blend = blend ;

	blitAlphaRectF(x1, y1, x2, y2, 0, 0, flipx, flipy);
	_blend =1 ;
	_d3d->SetTransform(D3DTRANSFORMSTATE_WORLD, (LPD3DMATRIX)&worldMatrix);
}


void		KGraphicD3D::stretchAlphaRect( float	sx1, float sy1 , float	sx2 , float sy2 , float	dx1, float dy1 , float	dx2 , float dy2, float blend ,float angle , bool flipx , bool flipy  , float centerX , float centerY  )
{
float		middlesizeX , middlesizeY ;
float	tmp ;

	if ( _surface == NULL )	{	return ;	}

	middlesizeX	= (dx2-dx1)/2 + centerX;
	middlesizeY	= (dy2-dy1)/2+ centerY;;

    if ( flipx == true ) 
    {
    		tmp = sx1 ;
    		sx1 =  sx2;
    		sx2 = tmp ;
    }

    if ( flipy == true ) 
    {
    		tmp = sy1 ;
    		sy1 =  sy2;
    		sy2 = tmp ;
    }


	D3DMATRIX m1, m2, m3;
	_d3d->GetTransform(D3DTRANSFORMSTATE_WORLD, &m3); // sauvegarde de la matrice

	translate(m1, -middlesizeX, middlesizeY, 0);
	rotatez(m2, angle);
	m1 = m1*m2;
//	scale(m2, 1,1, 0);

	m1 = m1*m2;
	_d3d->GetTransform(D3DTRANSFORMSTATE_WORLD, &m2);
	m1 = m1*m2;
	_d3d->SetTransform(D3DTRANSFORMSTATE_WORLD, &m1);


//  dy1	 =  -dy1 ;
 // dy2	 =  -dy2 ;
    	_blend = blend ;

	_d3d->SetRenderState(D3DRENDERSTATE_ALPHABLENDENABLE, true);
    genericStretchBlit( sx1 , sy1 , sx2 , sy2 , dx1+middlesizeX ,dy1+middlesizeY , dx2+middlesizeX , dy2 +middlesizeY ) ;	
	_blend = 1 ;

	_d3d->SetTransform(D3DTRANSFORMSTATE_WORLD, &m3); // restore matrix

}

void			KGraphicD3D::setLineWidth( short	linewidth )
{
	_lineWidth = linewidth ;
}
/*
bool			KGraphicD3D::saveBackBuffer( const char * cpcFileName , long	imageFormat , long resizeW , long resizeH )
{
unsigned	long		*pixelsBack ;

	_d3d->EndScene( ) ;

    KGraphicD3D	*backBufGrab ;
    
    //	FILE *f ;
    backBufGrab = new KGraphicD3D ;
    backBufGrab->grabBackBuffer( NULL) ;
    if ( resizeW > 0 && resizeH > 0 )
    {
        backBufGrab->stretchAlphaRect( 0,0,_screenWidth , _screenHeight , 0,0,resizeW , resizeH ) ;
    }
    else
    {
        resizeW = _screenWidth ;
        resizeH 	= _screenHeight ;
    }
    	delete	backBufGrab ;
	pixelsBack = new unsigned long[resizeW*resizeH] ;

	 HDC		dcBackBuffer  ;
	_backBuffer->GetDC( &dcBackBuffer ) ;


	COLORREF	colorR ;
	long	x , y ;
	
	for ( y = 0 ; y< resizeH ; y++ )
	{
		for ( x = 0 ; x< resizeW ; x++ )
		{
				colorR = GetPixel(dcBackBuffer , x , y ) ;
				pixelsBack[x+((resizeH-1)-y)*resizeW] = 0xff000000 | colorR ;
		}
	}
	

	
	_backBuffer->ReleaseDC( dcBackBuffer ) ;

	
    CxImage		*cix ;
    
    cix = new  CxImage ;
    cix->CreateFromArray( (unsigned char*)pixelsBack , resizeW , resizeH , 32 , resizeW*4 , false ) ;
    
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

	_d3d->BeginScene( ) ;

	return true ;    
}
*/

bool            KGraphicD3D::grabBackBuffer(  pixelCallBackPtr	pixelTransformationPtr ) 
{
	if (_surface != NULL )		_surface->Release( ) ;
	
	_d3d->EndScene( ) ;
		//describe the texture
	DDSURFACEDESC2		ddsd ;
	memset(&ddsd, 0, sizeof(DDSURFACEDESC2));
	ddsd.dwSize 					= sizeof(DDSURFACEDESC2);
	ddsd.dwFlags 				= DDSD_CAPS|DDSD_WIDTH|DDSD_HEIGHT|DDSD_PITCH|DDSD_TEXTURESTAGE|DDSD_PIXELFORMAT;
	ddsd.ddsCaps.dwCaps  	= DDSCAPS_TEXTURE   ;
	ddsd.ddsCaps.dwCaps2 	= DDSCAPS2_TEXTUREMANAGE;
	ddsd.dwWidth 				= _screenWidth;
	ddsd.dwHeight 				= _screenHeight;
	ddsd.ddpfPixelFormat.dwSize 		= sizeof(DDPIXELFORMAT);
	ddsd.ddpfPixelFormat.dwFlags 	= DDPF_RGB | DDPF_ALPHAPIXELS ;
	ddsd.ddpfPixelFormat.dwRGBBitCount = 32;
	ddsd.ddpfPixelFormat.dwRBitMask = 0x00FF0000;
	ddsd.ddpfPixelFormat.dwGBitMask = 0x0000FF00;
	ddsd.ddpfPixelFormat.dwBBitMask = 0x000000FF;
	ddsd.ddpfPixelFormat.dwRGBAlphaBitMask = 0xFF000000 ;
    
    if(FAILED(  _directX->CreateSurface( &ddsd  ,  &_surface , NULL ) ) )
    {
	//MessageBox( 0 ,"can't create surface",0,0 ) ;
	    	return false ;
    }
    
	 _ftextureWIDTH		=		_screenWidth ;
	 _ftextureHEIGHT		=		_screenHeight ;
//	 _ftextureWIDTHM1		=		_screenWidth -1 ;
//	 _ftextureHEIGHTM1		=		_screenHeight-1 ;
	 
    fimageHeight =_ftextureHEIGHT ;
    fimageWidth = _ftextureWIDTH ;

//	 HDC		dcBackBuffer  ;
//	_backBuffer->GetDC( &dcBackBuffer ) ;


    	ddsd.dwFlags 				= DDSD_PITCH ;
	_surface->GetSurfaceDesc(&ddsd);
	long	surfacePitch		= ddsd.lPitch;




	_surface->Lock( NULL , &ddsd, DDLOCK_SURFACEMEMORYPTR | DDLOCK_WAIT, NULL);
    unsigned char *ptr = (  unsigned char *)ddsd.lpSurface;
 
	ddsd.ddpfPixelFormat.dwSize = sizeof( DDPIXELFORMAT ) ;
 	//lock the back buffer
  	ddsd.dwFlags 				= DDSD_PITCH  | DDSD_PIXELFORMAT  ;
	_backBuffer->GetSurfaceDesc(&ddsd);
	long	backPitch		= ddsd.lPitch/4;
	long	backPitchs		= ddsd.lPitch/2;
	_backBuffer->Lock( NULL , &ddsd, DDLOCK_SURFACEMEMORYPTR | DDLOCK_WAIT, NULL);
    unsigned long 	*backptr = (  unsigned long *)ddsd.lpSurface;
    unsigned short 	*backptrs = ( unsigned short*)backptr ;
    
	COLORREF	colorR ;
	unsigned short	colorShort ;
	long	x , y ;
	long		r,g,b ;
	
	
	//for 5 6 5 mode
	long	decalo = 10 ;
	long	decaloCoef = 8 ;
	if ( ddsd.ddpfPixelFormat.dwGBitMask == 2016 )
	{
		decalo = 11 ;
		decaloCoef = 4 ;
	}

	if ( ddsd.ddpfPixelFormat.dwRGBBitCount  == 32 )
	{	
		for ( y = 0 ; y< _screenHeight ; y++ )
		{
			for ( x = 0 ; x< _screenWidth ; x++ )
			{
				
					colorR = backptr[x+y*backPitch] ;
				
                          r         =(colorR) & 0x000000ff ;
                          g       = (colorR >> 8 ) & 0x000000ff ;
                          b       = (colorR >> 16 ) & 0x000000ff ;                                       

						if ( pixelTransformationPtr != NULL ) 
						{
							pixelTransformationPtr( x , y , &r,&g,&b ) ;
						}
							
					ptr[4*x+(y*surfacePitch)+0] = r;
					ptr[4*x+(y*surfacePitch)+1] = g;
					ptr[4*x+(y*surfacePitch)+2] = b ;
					ptr[4*x+(y*surfacePitch)+3] =0xff ;		//alpha
			}
		}
	}
	else	if ( ddsd.ddpfPixelFormat.dwRGBBitCount  == 16 )
	{	
		for ( y = 0 ; y< _screenHeight ; y++ )
		{
			for ( x = 0 ; x< _screenWidth ; x++ )
			{
				//	colorR = GetPixel(dcBackBuffer , x , y ) ;
					colorShort = backptrs[x+y*backPitchs] ;
					r = (colorShort &  ddsd.ddpfPixelFormat.dwRBitMask) >>decalo;
					g =( colorShort &  ddsd.ddpfPixelFormat.dwGBitMask) >>5 ;
					b =( colorShort &  ddsd.ddpfPixelFormat.dwBBitMask) ;
					r*=8 ;
					g*=decaloCoef ;
					b*=8 ;
					
						if ( pixelTransformationPtr != NULL ) 
						{
							pixelTransformationPtr( x , y , &r,&g,&b ) ;
						}
						
					ptr[4*x+(y*surfacePitch)+2] =r ;
					ptr[4*x+(y*surfacePitch)+1] =g ;
					ptr[4*x+(y*surfacePitch)+0] =b ;
					ptr[4*x+(y*surfacePitch)+3] =0xff ;		//alpha
			}
		}
		
	
	}

	_backBuffer->Unlock( NULL ) ;
	_surface->Unlock( NULL );

    	_d3d->BeginScene( ) ;

	return true ;
}

bool             KGraphicD3D::grabFrontBuffer( void ) 
{
	return grabBackBuffer( NULL ) ;
}

//if you want to make pictures from buffers  HIDEF == true will use 32 bits textures in memory, else it'll use the current depth
bool			KGraphicD3D::makePictureFromArray( unsigned long *userPixelPtr , long width , long height , bool hiDef  ) 
{
	long		dxWidth , dxHeight , newSize, i ;
	
	long	x , y ;
	hiDef = hiDef;
	
	dxWidth		=	width ;
	dxHeight	=	height ;
	
    newSize = dxWidth ;
    if ( dxHeight > dxWidth )			newSize 	=	dxHeight ;
    
    //calculate a multiple of 2 for the texture size
    i = 2 ;
    do
    {
        i *= 2 ;
    }while( i < newSize ) ;
    
    newSize = i ;	




	//describe the texture
	DDSURFACEDESC2		ddsd ;
	memset(&ddsd, 0, sizeof(DDSURFACEDESC2));
	ddsd.dwSize 					= sizeof(DDSURFACEDESC2);
	ddsd.dwFlags 				= DDSD_CAPS|DDSD_WIDTH|DDSD_HEIGHT|DDSD_PITCH/*|DDSD_TEXTURESTAGE*/|DDSD_PIXELFORMAT;
	ddsd.ddsCaps.dwCaps  	= DDSCAPS_TEXTURE   ;
	ddsd.ddsCaps.dwCaps2 	= DDSCAPS2_TEXTUREMANAGE;
	ddsd.dwWidth 				= newSize;
	ddsd.dwHeight 				= newSize;
	ddsd.ddpfPixelFormat.dwSize 		= sizeof(DDPIXELFORMAT);
	ddsd.ddpfPixelFormat.dwFlags 	= DDPF_RGB | DDPF_ALPHAPIXELS ;
	ddsd.ddpfPixelFormat.dwRGBBitCount = 32;
	ddsd.ddpfPixelFormat.dwRBitMask = 0x00FF0000;
	ddsd.ddpfPixelFormat.dwGBitMask = 0x0000FF00;
	ddsd.ddpfPixelFormat.dwBBitMask = 0x000000FF;
	ddsd.ddpfPixelFormat.dwRGBAlphaBitMask = 0xFF000000 ;
    
    if(FAILED(  _directX->CreateSurface( &ddsd  ,  &_surface , NULL ) ) )
    {	
		    	return false ;
    }
		

    	ddsd.dwFlags 				= DDSD_PITCH ;
	_surface->GetSurfaceDesc(&ddsd);
	long	surfacePitch		= ddsd.lPitch;

	_surface->Lock( NULL , &ddsd, DDLOCK_SURFACEMEMORYPTR | DDLOCK_WAIT, NULL);
    unsigned long *ptr = (  unsigned long *)ddsd.lpSurface;
	unsigned long color , r, g, b, a ;	
	for ( x = 0 ; x < width ; x++ )
	{
		for ( y = 0 ; y < height ; y++ )
		{
			color = userPixelPtr[x+y*width] ; 
			 r         =(color) & 0x000000ff ;
               g       = (color >> 8 ) & 0x000000ff ;
               b       = (color >> 16 ) & 0x000000ff ;         
               a		=(color >> 24 ) & 0x000000ff ;         
			ptr[x+y*surfacePitch/4] = r <<16|g<<8|b|a<<24 ;
		}
	}
	
	_surface->Unlock( NULL );

 	_ftextureWIDTH		=		newSize ;
    _ftextureHEIGHT	=		newSize ;
    fimageHeight =width ;
    fimageWidth = height ;
    
	return true ;
}

//if you want to "refresh" the texture created by makePictureFromArray you can just call poll 
void			KGraphicD3D::pollArray( void ) 
{

}

//replaces glColor4f
void			KGraphicD3D::setBlitColor ( float	r , float	g , float	b , float a )
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



//arbitrary quad  BROKEN
void			KGraphicD3D::blitArbitraryQuad( 	float sx1 , float sy1 , float sx2 , float sy2 , float sx3 , float sy3 , float sx4 , float sy4 , 
														float dx1 , float dy1 , float dx2 , float dy2 , float dx3 , float dy3 , float dx4 , float dy4  ) 
{

	if ( _surface == NULL )		return ;
	
	_d3d->SetRenderState(D3DRENDERSTATE_ALPHABLENDENABLE, true);
	
	dy1 = -dy1 ;
	dy2 = -dy2 ;
	dy3 = -dy3 ;
	dy4 = -dy4 ;
	    	
	 _d3d->SetTextureStageState(0,D3DTSS_ADDRESS ,     _textureWrapD3D      );	    	
	_d3d->SetTextureStageState(0,D3DTSS_ADDRESSU ,     _textureWrapD3D      );	    	
	_d3d->SetTextureStageState(0,D3DTSS_ADDRESSV ,     _textureWrapD3D      );	    	
  	_d3d->SetTextureStageState(0,D3DTSS_MAGFILTER,     _textureQualityD3D      );
    	_d3d->SetTextureStageState(0,D3DTSS_MINFILTER,     _textureQualityD3D      );	
	_d3d->SetRenderState(D3DRENDERSTATE_SRCBLEND, _sourceAlpha);
	_d3d->SetRenderState(D3DRENDERSTATE_DESTBLEND, _destAlpha);
	

	//place a select texture here with a "memory" no to rebind the texture over and over again ( faster )
	//_d3d->SetTexture(0, _surface);
    	if ( ptk_bindTexture( )  == false )		return ;

            
	D3DMATRIX mat, mat2, mat3;

	_d3d->GetTransform(D3DTRANSFORMSTATE_WORLD, &mat3); // sauvegarde de la matrice

	D3DLVERTEX v[8];
	D3DCOLOR col ;
	
	if ( _blitColorChanged == false )
	{
		col = D3DRGBA(  1, 1, 1 , _blend );			//vector color  - like glColor4f
	}
	else
	{	
		 col = D3DRGBA( _blitRed, _blitGreen, _blitBlue , _blitAlpha);			//vector color  - like glColor4f
	}

	float su1 = sx1/_ftextureWIDTH;
	float su2 = sx2/_ftextureWIDTH;
	
	float sv1 = sy1/_ftextureHEIGHT;
	float sv2 = sy2/_ftextureHEIGHT;
	
	float su3 = sx3/_ftextureWIDTH;
	float su4 = sx4/_ftextureWIDTH;
	
	float sv3 = sy3/_ftextureHEIGHT;
	float sv4 = sy4/_ftextureHEIGHT;
/*
	v[0] = D3DLVERTEX(D3DVECTOR(dx1,dy1,0), col, 0, su1, sv1);
	v[1] = D3DLVERTEX(D3DVECTOR(dx2,dy2,0), col, 0, su2, sv2);
	v[2] = D3DLVERTEX(D3DVECTOR(dx3,dy3,0), col, 0, su3, sv3);

	v[3] = D3DLVERTEX(D3DVECTOR(dx1,dy1,0), col, 0, su1, sv1);
	v[4] = D3DLVERTEX(D3DVECTOR(dx3,dy3,0), col, 0, su3, sv3);
	v[5] = D3DLVERTEX(D3DVECTOR(dx4,dy4,0), col, 0, su4, sv4);
*/
	v[0] = D3DLVERTEX(D3DVECTOR(dx1,dy1,0), col, 0, su1, sv1);
	v[1] = D3DLVERTEX(D3DVECTOR(dx2,dy2,0), col, 0, su2, sv2);
	v[2] = D3DLVERTEX(D3DVECTOR(dx3,dy3,0), col, 0, su3, sv3);

	v[3] = D3DLVERTEX(D3DVECTOR(dx1,dy1,0), col, 0, su1, sv1);
	v[4] = D3DLVERTEX(D3DVECTOR(dx3,dy3,0), col, 0, su3, sv3);
	v[5] = D3DLVERTEX(D3DVECTOR(dx4,dy4,0), col, 0, su4, sv4);


  	if ( _directX->TestCooperativeLevel() == DD_OK)
  	{
	  	_d3d->DrawPrimitive(D3DPT_TRIANGLESTRIP, D3DFVF_LVERTEX, &v[0], 6, 0);
		_d3d->SetTransform(D3DTRANSFORMSTATE_WORLD, &mat3); // restauration de la matrice
	}

}														

//blit tiling the texture
void		KGraphicD3D::blitTiledRect(short	destX , short	destY , short		width , short	height ,  float tileFactor ,float angle )
{
    float		middlesizeX , middlesizeY ;

    	if ( _surface == NULL )		return ;
	_d3d->SetRenderState(D3DRENDERSTATE_ALPHABLENDENABLE, false);

    

	
//	destY = -(destY-1);
//	destX-- ;
    

    	//wrapping
    if ( _textureWrap == true )
    {
	    _d3d->SetTextureStageState(0,D3DTSS_ADDRESS ,	 D3DTADDRESS_WRAP      );
	    _d3d->SetTextureStageState(0,D3DTSS_ADDRESSU ,	 D3DTADDRESS_WRAP      );
	    _d3d->SetTextureStageState(0,D3DTSS_ADDRESSV ,	 D3DTADDRESS_WRAP      );
    	}
    	else
    	{
	    _d3d->SetTextureStageState(0,D3DTSS_ADDRESS ,     D3DTADDRESS_CLAMP      );	    	
	    _d3d->SetTextureStageState(0,D3DTSS_ADDRESSU ,     D3DTADDRESS_CLAMP      );	    	
	    _d3d->SetTextureStageState(0,D3DTSS_ADDRESSV ,     D3DTADDRESS_CLAMP      );	    	
    	}
    	    	
	if ( _textureQuality == true )	//high quality!
	{
	  	_d3d->SetTextureStageState(0,D3DTSS_MAGFILTER,     D3DTFG_LINEAR      );
	    	_d3d->SetTextureStageState(0,D3DTSS_MINFILTER,     D3DTFG_LINEAR      );
	}
	else
	{
	  	_d3d->SetTextureStageState(0,D3DTSS_MAGFILTER	,     	D3DTFG_POINT      );
	    	_d3d->SetTextureStageState(0,D3DTSS_MINFILTER	, 		D3DTFG_POINT	);	
	}




	middlesizeX	= (float)(width/2);
	middlesizeY	= (float)(height/2);


	D3DMATRIX m1, m2, m3;

	_d3d->GetTransform(D3DTRANSFORMSTATE_WORLD, &m3); // sauvegarde de la matrice

	 
	_d3d->SetRenderState(D3DRENDERSTATE_ALPHABLENDENABLE, FALSE);
//	_d3d->BeginScene();
	if ( ptk_bindTexture( )  == false )		return ;

//	_d3d->SetTexture(0, _surface);
/*	
	//on supprime le clamping
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,  GL_REPEAT );	//GL_CLAMP_TO_EDGE  sur mac peut etre
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,  GL_REPEAT );
*/

	destY = -destY;

	translate(m1, -middlesizeX, middlesizeY, 0);
	rotatez(m2, angle);
	m1 = m1*m2;
	translate(m2, destX+middlesizeX, destY-middlesizeY, 0);
	m1 = m1*m2;
	_d3d->GetTransform(D3DTRANSFORMSTATE_WORLD, &m2);
	m1 = m1*m2;
	_d3d->SetTransform(D3DTRANSFORMSTATE_WORLD, &m1);

	D3DCOLOR col = D3DRGBA( 1, 1, 1 , _blend );

	D3DLVERTEX v[4];
	v[0] = D3DLVERTEX(D3DVECTOR(0,0,0), col, 0, 0, 0);
	v[1] = D3DLVERTEX(D3DVECTOR((float)width,0,0), col, 0, tileFactor, 0);
	v[2] = D3DLVERTEX(D3DVECTOR(0,-(float)height,0), col, 0, 0, tileFactor);
	v[3] = D3DLVERTEX(D3DVECTOR((float)width,-(float)height,0), col, 0, tileFactor, tileFactor);

  	if ( _directX->TestCooperativeLevel() == DD_OK)
  	{
		_d3d->DrawPrimitive(D3DPT_TRIANGLESTRIP, D3DFVF_LVERTEX, &v[0], 4, 0);
		_d3d->SetTransform(D3DTRANSFORMSTATE_WORLD, &m3);
	}    
}

//no alpha stuff, the fastest we can get ?
void		KGraphicD3D::blitRect( float	x1, float y1 , float	x2 , float y2 , short	destX , short	destY , bool flipx , bool flipy )
{
	if ( _surface == NULL )		return ;
	_d3d->SetRenderState(D3DRENDERSTATE_ALPHABLENDENABLE, false);
	GenericBlit(x1, y1, x2, y2, destX, destY, flipx, flipy) ;

}

void			KGraphicD3D::allowTextureWrap( bool texwRap)
{


    _textureWrap = texwRap ;

	if ( _textureWrap == true )
	{
		_textureWrapD3D = D3DTADDRESS_WRAP ;
	}
	else
	{
		_textureWrapD3D = D3DTADDRESS_CLAMP ;
	}
    
}

//set color key
void			KGraphicD3D::setColorKey( bool active,unsigned char r , unsigned char g ,  unsigned char b ) 
{
    _ckActive = active ;
    _ckr = r ;
    _ckg = g ;
    _ckb = b ;
}


//plot a pixel
void	KGraphicD3D::plotPixel( float	x1, float y1, float r ,float g ,float b ,  float blend ) 
{
	x1+=_texelDX ;
	y1+=_texelDY ;

	
	y1 = -y1;

	_d3d->SetRenderState(D3DRENDERSTATE_ALPHABLENDENABLE, TRUE);

	D3DCOLOR col = D3DRGBA( r,g, b , blend);

	D3DLVERTEX v[2];
	v[0] = D3DLVERTEX(D3DVECTOR(x1,y1,0), col, 0, 0, 0);

	_d3d->SetTexture(0, NULL);

//	_d3d->BeginScene();
  	if ( _directX->TestCooperativeLevel() == DD_OK)
  	{
		_d3d->DrawPrimitive(D3DPT_POINTLIST, D3DFVF_LVERTEX, &v[0], 1, 0);
	}
//	_d3d->EndScene();
	_oldBindedText	= 0 ;


}

   //draw a line
void KGraphicD3D::drawLine(float x1, float y1, float x2, float y2, float r, float g, float b, float blend)
{
	x1+=_texelDX ;
	y1+=_texelDY ;
	x2+=_texelDX ;
	y2+=_texelDY ;
	
	y2 = -y2;
	y1 = -y1;


	_d3d->SetRenderState(D3DRENDERSTATE_ALPHABLENDENABLE, TRUE);
	_d3d->SetRenderState(D3DRENDERSTATE_SRCBLEND, _sourceAlpha);
	_d3d->SetRenderState(D3DRENDERSTATE_DESTBLEND, _destAlpha);
		
		
		
	D3DCOLOR col = D3DRGBA(	r, g, b , blend );

	D3DLVERTEX v[2];
	v[0] = D3DLVERTEX(D3DVECTOR(x1,y1,0), col, 0, 0, 0);
	v[1] = D3DLVERTEX(D3DVECTOR(x2,y2,0), col, 0, 0, 0);

  	if ( _directX->TestCooperativeLevel() == DD_OK)
  	{
		_d3d->SetTexture(0, NULL);
		_d3d->DrawPrimitive(D3DPT_LINELIST, D3DFVF_LVERTEX, &v[0], 2, 0);
	}
		_oldBindedText	= 0 ;
	

}

void		KGraphicD3D::drawRect( float	x1, float y1 , float	x2 , float y2 , float r ,float g ,float b ,  float blend ) 
{

	x1+=_texelDX ;
	y1+=_texelDY ;
	x2+=_texelDX ;
	y2+=_texelDY ;
	
	y2 = -y2;
	y1 = -y1;
  	if ( _directX->TestCooperativeLevel() != DD_OK)		return ;

//	x1++;	x2++ ;
	
	_d3d->SetRenderState(D3DRENDERSTATE_ALPHABLENDENABLE, TRUE);
	_d3d->SetRenderState(D3DRENDERSTATE_SRCBLEND, _sourceAlpha);
	_d3d->SetRenderState(D3DRENDERSTATE_DESTBLEND, _destAlpha);
	
	D3DCOLOR col = D3DRGBA(  r, g, b , blend);

	D3DLVERTEX v[4];
	v[0] = D3DLVERTEX(D3DVECTOR(x1,y2,0), col, 0, 0, 0);
	v[1] = D3DLVERTEX(D3DVECTOR(x1,y1,0), col, 0, 0, 0);
	v[2] = D3DLVERTEX(D3DVECTOR(x2,y2,0), col, 0, 0, 0);
	v[3] = D3DLVERTEX(D3DVECTOR(x2,y1,0), col, 0, 0, 0);

	_d3d->SetTexture(0, NULL);

//	_d3d->BeginScene();
	_d3d->DrawPrimitive(D3DPT_TRIANGLESTRIP, D3DFVF_LVERTEX, &v[0], 4, 0);
//	_d3d->EndScene();
	_oldBindedText	= 0 ;


}

/*
void		KGraphicD3D::plotPixel( float	x1, float y1, float r ,float g ,float b ,  float blend ) 
{
}
*/
bool		KGraphicD3D::reloadSurface( void )
{
char		filenameStorage[260] ;
bool		result ;

		if ( _directX->TestCooperativeLevel() != DD_OK)		return false ;

		result = false ;
		
		if ( _surface  != NULL )
		{
			_surface->Release( ) ;
			_surface = NULL ;
		}
		
		if ( _usedForTTF > 0 )
		{		
			if ( _usedForTTF  == 1 ) {	_usedForTTF	= 2 ; }
			return result ;
		}
	
		//prevents overlapping of filenames ( crash in loadpicture )
		strcpy( filenameStorage , imageFileName ) ;
		if ( strcmp( imageFileName , "")  == 0 )		return false ;	 	
		
		if (  _2dSurface ==  true )
		{
			result = loadPicture2d( filenameStorage , _ckPixelX, _ckPixelY ) ;	
	
			_oldBindedText = 0 ;
			return result ;
		
		}
		
		

		if ( _usedForTTF == false )
		{
				//MessageBox( 0 , filenameStorage ,0,0  ) ;
			if ( _maskedUsed == false )
			{			
				result = loadPicture( filenameStorage , _hidef , _hasAlpha ) ;
			}
			else
			{
				result = loadPictureWithMask( filenameStorage , imageMaskFileName , true ) ;		
			}
			
			_oldBindedText = 0 ;
		}

		return		result ;
}


bool		KGraphicD3D::ptk_bindTexture( void ) 
{
    if ( _oldBindedText != _surface )
    {
	    _oldBindedText = _surface ;
		if ( D3D_OK == _d3d->SetTexture(0, _surface) )
		{
			if( _surface->IsLost( ) == DDERR_SURFACELOST  )
			{
				reloadSurface( ) ;
			}
	
			return true ;
		}
		return false ;
    }
    
	return true ;    
}

void		KGraphicD3D::selectTexture( void ) 
{
 //   if ( _oldBindedText != _surface )
  //  {
        _oldBindedText = _surface ;
		_d3d->SetTexture(0, _surface) ;
   // }
    
}

void			KGraphicD3D::setStates( void ) 
{
		_d3d->SetTextureStageState(0,D3DTSS_ADDRESS ,     _textureWrapD3D      );	    	
		_d3d->SetTextureStageState(0,D3DTSS_ADDRESSU ,     _textureWrapD3D      );	    	
		_d3d->SetTextureStageState(0,D3DTSS_ADDRESSV ,     _textureWrapD3D      );	 
	  	_d3d->SetTextureStageState(0,D3DTSS_MAGFILTER,     _textureQualityD3D      );
	    	_d3d->SetTextureStageState(0,D3DTSS_MINFILTER,     _textureQualityD3D      );	
		_d3d->SetRenderState(D3DRENDERSTATE_SRCBLEND, _sourceAlpha);
		_d3d->SetRenderState(D3DRENDERSTATE_DESTBLEND, _destAlpha);
		
		//_d3d->SetRenderState( D3DRENDERSTATE_CLIPPING , true ) ;
		
}





//blit used for all the function
void KGraphicD3D::GenericBlit(long x1, long y1, long x2, long y2, float destX, float destY, bool flipx, bool flipy) 
{
long	ih ;
float sx1,sy1 , sx2,sy2 ;
//HRESULT 		errorCooperative ;




	sx1 = (float)x1 ;
	sx2 = (float)x2 ;
	sy1 = (float)y1 ;
	sy2 = (float)y2 ;


	ih = (y2-y1) ;
	
	if( _surface->IsLost( ) == DDERR_SURFACELOST  )
	{
//		_currentState  = KGraphicD3D::getFullscreenState()  ;
		reloadSurface( ) ;
		#ifdef LOGZEERRORS
			logerror( "KGraphicD3D::GenericBlit surface was lost\r\n" ) ;
		#endif
		return ;
	}

	
	 destY = -(destY-1);

		_d3d->SetTextureStageState(0,D3DTSS_ADDRESS ,     _textureWrapD3D      );	    	
		_d3d->SetTextureStageState(0,D3DTSS_ADDRESSU ,     _textureWrapD3D      );	    	
		_d3d->SetTextureStageState(0,D3DTSS_ADDRESSV ,     _textureWrapD3D      );	 
	  	_d3d->SetTextureStageState(0,D3DTSS_MAGFILTER,     _textureQualityD3D      );
	    	_d3d->SetTextureStageState(0,D3DTSS_MINFILTER,     _textureQualityD3D      );	
		_d3d->SetRenderState(D3DRENDERSTATE_SRCBLEND, _sourceAlpha);
		_d3d->SetRenderState(D3DRENDERSTATE_DESTBLEND, _destAlpha);


	//place a select texture here with a "memory" no to rebind the texture over and over again ( faster )
	if ( ptk_bindTexture( )  == false )		
	{	
		#ifdef LOGZEERRORS
			logerror( "KGraphicD3D::GenericBlit can't bind texture\r\n") ;
		#endif
		return ;		
	}

            
	D3DXMATRIX worldMatrix;
	_d3d->GetTransform(D3DTRANSFORMSTATE_WORLD, (LPD3DMATRIX)&worldMatrix); // sauvegarde de la matrice

	D3DXMATRIX translateMatrix;
	D3DXMATRIX rotateMatrix;
	D3DXMATRIX scaleMatrix;

	D3DXMATRIX worldMatrix2;
	D3DXMatrixIdentity( &worldMatrix2 );

	D3DXMatrixTranslation( &translateMatrix, destX, destY, 0 );
	D3DXMatrixMultiply( &worldMatrix2, &worldMatrix2, &translateMatrix );

	D3DXMatrixMultiply( &worldMatrix2, &worldMatrix2, &worldMatrix );

long dxcoop ;
	dxcoop = _directX->TestCooperativeLevel() ;

  	if ( dxcoop == DD_OK)
	{
		_d3d->SetTransform(D3DTRANSFORMSTATE_WORLD, (LPD3DMATRIX)&worldMatrix2);
	}

	D3DLVERTEX v[4];
	D3DCOLOR col ;
	
	if ( _blitColorChanged == false )
	{
		col = D3DRGBA( 1, 1,1 , _blend);			//vector color  - like glColor4f
	}
	else
	{
		float		a = ((float)_blend*_blitAlpha);
		 col = D3DRGBA(  _blitRed, _blitGreen, _blitBlue , a );			//vector color  - like glColor4f
	}
	
	float w = (sx2-sx1);				//-1 cuts
	float h = (sy1-sy2);
	


	
		w = (sx2-sx1);
		h = (sy1-sy2);

	float u1 = (sx1/(_ftextureWIDTH)) + _texelSX ;
	float v1 = (sy1/(_ftextureHEIGHT))+ _texelSY;
	
	float u2 = (sx2/(_ftextureWIDTH))+ _texelSX ;
	float v2 = (sy2/(_ftextureHEIGHT))+ _texelSY ;


	if(flipx == false && flipy == false)
	{
		v[0] = D3DLVERTEX(D3DVECTOR(_texelDX,_texelDY,0), col, 0, u1, v1);
		v[1] = D3DLVERTEX(D3DVECTOR(w+_texelDX,_texelDY,0), col, 0, u2, v1);
		v[2] = D3DLVERTEX(D3DVECTOR(_texelDX,h+_texelDY,0), col, 0, u1, v2);
		v[3] = D3DLVERTEX(D3DVECTOR(w+_texelDX,h+_texelDY,0), col, 0, u2, v2);
	}
	else
	if(flipx == true && flipy == true)
	{
		v[0] = D3DLVERTEX(D3DVECTOR(_texelDX,_texelDY,0), col, 0, u2, v2);
		v[1] = D3DLVERTEX(D3DVECTOR(w+_texelDX,_texelDY,0), col, 0, u1, v2);
		v[2] = D3DLVERTEX(D3DVECTOR(_texelDX,h+_texelDY,0), col, 0, u2, v1);
		v[3] = D3DLVERTEX(D3DVECTOR(w+_texelDX,h+_texelDY,0), col, 0, u1, v1);
	}
	else
	if(flipx == true && flipy == false)
	{
			float u1 = (sx2)/(_ftextureWIDTH);
		float v1 = sy1/(_ftextureHEIGHT);
	
		float u2 = (sx1)/(_ftextureWIDTH);
		float v2 = sy2/(_ftextureHEIGHT);

		v[0] = D3DLVERTEX(D3DVECTOR(_texelDX,_texelDY,0), col, 0, u1, v1);
		v[1] = D3DLVERTEX(D3DVECTOR(w+_texelDX,_texelDY,0), col, 0, u2, v1);
		v[2] = D3DLVERTEX(D3DVECTOR(_texelDX,h+_texelDY,0), col, 0, u1, v2);
		v[3] = D3DLVERTEX(D3DVECTOR(w+_texelDX,h+_texelDY,0), col, 0, u2, v2);
		

	}
	else
	if(flipx == false && flipy == true)
	{
		v[0] = D3DLVERTEX(D3DVECTOR(_texelDX,_texelDY,0), col, 0, u1, v2);
		v[1] = D3DLVERTEX(D3DVECTOR(w+_texelDX,_texelDY,0), col, 0, u2, v2);
		v[2] = D3DLVERTEX(D3DVECTOR(_texelDX,h+_texelDY,0), col, 0, u1, v1);
		v[3] = D3DLVERTEX(D3DVECTOR(w+_texelDX,h+_texelDY,0), col, 0, u2, v1);
	}


	dxcoop = _directX->TestCooperativeLevel() ;

  	if ( dxcoop == DD_OK)
  	{
		_d3d->DrawPrimitive(D3DPT_TRIANGLESTRIP, D3DFVF_LVERTEX, &v[0], 4, 0);
		_d3d->SetTransform(D3DTRANSFORMSTATE_WORLD, (LPD3DMATRIX)&worldMatrix);
	}

}








//blit used for all the function
void KGraphicD3D::genericStretchBlit( float	sx1 , float	sy1 , float	sx2 , float	sy2 , float	dx1 ,float	dy1 , float	dx2 , float	dy2  ) 
{

	if( _surface->IsLost( ) == DDERR_SURFACELOST )
	{
		reloadSurface( ) ;
	}

	 _d3d->SetTextureStageState(0,D3DTSS_ADDRESS ,     _textureWrapD3D      );	    	
	_d3d->SetTextureStageState(0,D3DTSS_ADDRESSU ,     _textureWrapD3D      );	    	
	_d3d->SetTextureStageState(0,D3DTSS_ADDRESSV ,     _textureWrapD3D      );	    	
  	_d3d->SetTextureStageState(0,D3DTSS_MAGFILTER,     _textureQualityD3D      );
    	_d3d->SetTextureStageState(0,D3DTSS_MINFILTER,     _textureQualityD3D      );	
	_d3d->SetRenderState(D3DRENDERSTATE_SRCBLEND, _sourceAlpha);
	_d3d->SetRenderState(D3DRENDERSTATE_DESTBLEND, _destAlpha);
	

	//place a select texture here with a "memory" no to rebind the texture over and over again ( faster )
	if ( ptk_bindTexture( )  == false )		return ;

            
	D3DMATRIX mat, mat2, mat3;
	_d3d->GetTransform(D3DTRANSFORMSTATE_WORLD, &mat);
	translate(mat2, dx1+0.5f, -(dy1+0.5f), 0);
	mat = mat*mat2;
	_d3d->SetTransform(D3DTRANSFORMSTATE_WORLD, &mat);

	D3DLVERTEX v[4];
	D3DCOLOR col ;
	
	if ( _blitColorChanged == false )
	{
		col = D3DRGBA( 1, 1,1 , _blend);			//vector color  - like glColor4f
	}
	else
	{
		float		a = ((float)_blend*_blitAlpha);
		 col = D3DRGBA(  _blitRed, _blitGreen, _blitBlue , a );			//vector color  - like glColor4f
	}


	float w = (dx2-dx1);
	float h = (dy1-dy2) ; 
	
	float u1 = (sx1/(_ftextureWIDTH)) + _texelSX ;
	float v1 = (sy1/(_ftextureHEIGHT))+ _texelSY;
	
	float u2 = (sx2/(_ftextureWIDTH))+ _texelSX ;
	float v2 = (sy2/(_ftextureHEIGHT))+ _texelSY ;


		v[0] = D3DLVERTEX(D3DVECTOR(_texelDX,_texelDY,0), col, 0, u1, v1);
		v[1] = D3DLVERTEX(D3DVECTOR(w+_texelDX,_texelDY,0), col, 0, u2, v1);
		v[2] = D3DLVERTEX(D3DVECTOR(_texelDX,h+_texelDY,0), col, 0, u1, v2);
		v[3] = D3DLVERTEX(D3DVECTOR(w+_texelDX,h+_texelDY,0), col, 0, u2, v2);


 	if ( _directX->TestCooperativeLevel() == DD_OK)
  	{
		_d3d->DrawPrimitive(D3DPT_TRIANGLESTRIP, D3DFVF_LVERTEX, &v[0], 4, 0);
	}

}


bool            KGraphicD3D::grabBackBufferFast(  long x, long y, long w, long h ) 
{
	_d3d->EndScene( ) ;
	
	RECT rc; 
	rc.left = x;	rc.top = y;
	rc.right = x + (w - 1);
	rc.bottom = y + (h - 1);

	if ( _surface->Blt(&rc, _backBuffer, &rc, DDBLT_WAIT, NULL) != DD_OK )
	{
		_d3d->BeginScene();
		return false;
	}

	_d3d->BeginScene();

	return true;
}

void 		KGraphicD3D::gpuFinish( void )
{
 DDSURFACEDESC2		ddsd ;
 
 _backBuffer->GetSurfaceDesc(&ddsd);
 _backBuffer->Lock( NULL , &ddsd, DDLOCK_WAIT, NULL);
 _backBuffer->Unlock( NULL );
}


bool             KGraphicD3D::grabFrontBufferFast( void ) 
{
	return grabBackBufferFast( 0, 0, 256, 256 ) ;
}

