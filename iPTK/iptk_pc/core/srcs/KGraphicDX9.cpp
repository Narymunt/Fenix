#include	"KGraphicDX9.h"
#include	"KResource.h"
#include	<ximage.h>
#include <d3dx9tex.h>
// needed to draw pictures---------------------------
#define D3DFVF_PTKVERTEX (D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1 )


LPDIRECT3D9            KGraphicDX9::_d3d9Ptr	 = NULL ; //the D3DDevice
LPDIRECT3DDEVICE9      KGraphicDX9::_d3d9Device  = NULL ; //  rendering device
std::vector<KGraphicDX9*>   KGraphicDX9::currents;

KGraphicDX9::KGraphicDX9() 
{
	_texture = NULL ;
	_imageMaskFileName[0] = 0 ;
	_imageFileName[0] = 0 ;
	_maskedUsed = false ;
	_ftextureWIDTH = 0 ;
	_ftextureHEIGHT = 0 ;
	fimageWidth = 0 ;
	fimageHeight = 0 ;
	_quality  = false ;
	_imageHeight  = 0 ;
	_imageWidth = 0 ;
	_oldTexture = 0 ;
	_vertexBuffer = NULL ;
	_pTargetSurface=NULL;
	_pTargetTexture=NULL;
	_targetWidth = 0;
	_targetHeight = 0;

	_ckActive = false;
	_ckr = 0;
	_ckg = 0;
	_ckb = 0;
	setAlphaMode( 1 );
	allowTextureWrap( false );
	setTextureQuality( true );
	setBlitColor( 1, 1, 1, 1 );
	_blitColorChanged = false;
	_zoomX = 1;
	_zoomY = 1;

	createBuffer();
	currents.push_back(this);
}

void KGraphicDX9::releaseCurrents()
{
	for (int i = 0; i < KGraphicDX9::currents.size(); i++)
	{
		KGraphicDX9::currents[i]->releaseBuffer();
		KGraphicDX9::currents[i]->freePicture();
	}
}
void KGraphicDX9::initCurrents()
{
	for (int i = 0; i < KGraphicDX9::currents.size(); i++)
	{
		KGraphicDX9::currents[i]->createBuffer();
		KGraphicDX9::currents[i]->_usedForTTF = 2;
	}
}


KGraphicDX9::~KGraphicDX9() 
{
	freePicture( ) ;
	releaseBuffer();
	std::vector<KGraphicDX9*>::iterator it;
	for (it = currents.begin(); it != currents.end(); it++)
	{
		if (*it == this)
		{
			currents.erase(it);
			break;
		}
	}	
}

bool KGraphicDX9::createBuffer()
{
	if ( _d3d9Device  != NULL )
	{
		_d3d9Device->CreateVertexBuffer( 5*sizeof( PTKVERTEX ),
			D3DUSAGE_DYNAMIC,
			D3DFVF_PTKVERTEX,
			D3DPOOL_DEFAULT,
			&_vertexBuffer, NULL);
		if (_targetWidth != 0&& _targetHeight != 0)
		{
			CreateRenderTarget(_targetWidth, _targetHeight);
		}
		return true;
	}
	return false;
}
bool KGraphicDX9::releaseBuffer() 
{
	if ( _vertexBuffer != NULL )
	{
		_vertexBuffer->Release();
		_vertexBuffer = NULL;
	}
	if (_pTargetSurface != NULL)
	{
		_pTargetSurface->Release();
		_pTargetSurface = NULL;
	}
	if (_pTargetTexture != NULL)
	{
		_pTargetTexture->Release();
		_pTargetTexture = NULL;
	}
	return true;
}


void KGraphicDX9::setDirectX( LPDIRECT3D9 dx9Ptr, LPDIRECT3DDEVICE9 dx9Device ) 
{
	_d3d9Ptr = dx9Ptr;
	_d3d9Device = dx9Device;
}


bool KGraphicDX9::loadPicture2d( const char	*filename, long x, long y ) 
{
	return false;
}
bool KGraphicDX9::loadPicture2dFromPtr( const char *filename, unsigned char	*dataPtr, unsigned long datasize, long tx, long ty )   
{
	return false;
}
void KGraphicDX9::blitRect2d( float	x1, float y1, float x2, float y2, short destX, short destY )  
{
}
void KGraphicDX9::blitAlphaRect2d( float x1, float y1, float x2, float y2, short destX, short destY ) 
{
}
//3d stuff
bool KGraphicDX9::loadPictureFromPtr( const	char *filename, unsigned char *dataPtr, 
									 unsigned long datasize, bool hiDef, bool hasalpha )  
{
	freePicture();

	_hidef = hiDef;
	_hasAlpha =	hasalpha;

	CxImage	* cxImagePtr;
	tgaBitmap tgaInfo;

	if ( strstr( filename,".tga") != NULL )
	{
		cxImagePtr = new CxImage( dataPtr, (DWORD) datasize, CXIMAGE_FORMAT_TGA );
	}

	if ( strstr( filename,".jpg") != NULL )
	{
		cxImagePtr = new CxImage( dataPtr, (DWORD) datasize, CXIMAGE_FORMAT_JPG );
	}

	if ( strstr( filename,".bmp") != NULL )
	{
		cxImagePtr = new CxImage( dataPtr, (DWORD) datasize, CXIMAGE_FORMAT_BMP );			
	}

	if ( strstr( filename,".png") != NULL )
	{
		cxImagePtr = new CxImage( dataPtr, (DWORD) datasize, CXIMAGE_FORMAT_PNG );
	}

	tgaInfo.bpp = (unsigned char)cxImagePtr->GetBpp();
	tgaInfo.width = (unsigned short)cxImagePtr->GetWidth();
	tgaInfo.height = (unsigned short)cxImagePtr->GetHeight();

	_ftextureWIDTH = tgaInfo.width;
	_ftextureHEIGHT = tgaInfo.height;
	fimageWidth = tgaInfo.width;
	fimageHeight = tgaInfo.height;

	long ct = cxImagePtr->GetColorType();

	if ( ct == 4 ) 
	{
		tgaInfo.bpp = 32;
	}

	if ( createTexture( (long)fimageWidth, (long)fimageHeight,  tgaInfo.bpp ) == false )
	{
		delete cxImagePtr;
		return false;
	}


	HRESULT hr;
	D3DLOCKED_RECT lockedRect;

	hr = _texture->LockRect( 0, &lockedRect, NULL, 0 );

	unsigned char *ptr = (unsigned char *) lockedRect.pBits;
	long surfacePitch = lockedRect.Pitch;
	unsigned char r, g, b, a;

	long imageWidth = tgaInfo.width;
	long imageHeight = tgaInfo.height;


	switch ( tgaInfo.bpp )
	{
	case 32:
		{
			for ( long  x = 0 ; x < imageWidth ; x++ )
			{
				for ( long y = 0 ; y < imageHeight ; y++ )
				{
					RGBQUAD color;
					color = cxImagePtr->GetPixelColor( x,  imageHeight - ( y + 1 ), true );

					r = color.rgbRed;
					g = color.rgbGreen;
					b = color.rgbBlue;
					a = color.rgbReserved;
					if ( _ckActive == true && _ckr == r && _ckb == b && _ckg == g )
					{
						a = 0;							
					}
					ptr[ 4 * x + y * (long)surfacePitch] = b;					//r
					ptr[ 4 * x + y * (long)surfacePitch + 1] = g;				//g
					ptr[ 4 * x + y * (long)surfacePitch + 2] = r;				//b
					ptr[ 4 * x + y * (long)surfacePitch + 3] = a;				//a							
				}	
			}//for x
		}
		break; //case 32
	default:
		{
			//8 or 16 or 24 bits
			for ( long x = 0 ; x < imageWidth ; x++ )
			{
				for ( long y = 0 ; y < imageHeight ; y++ )
				{
					RGBQUAD color;
					color = cxImagePtr->GetPixelColor( x, imageHeight - ( y + 1 ), false );

					r = color.rgbRed;
					g = color.rgbGreen;
					b = color.rgbBlue;
					a = 255;

					if ( _ckActive == true && _ckr == r && _ckb == b && _ckg == g )
					{
						a = 0;							
					}

					ptr[ 4 * x + y * (long)surfacePitch] = b;			    	//r
					ptr[ 4 * x + y * (long)surfacePitch + 1] = g;				//g
					ptr[ 4 * x + y * (long)surfacePitch + 2] = r;				//b
					ptr[ 4 * x + y * (long)surfacePitch + 3] = a;				//a							

				}	
			}
		}
		break;    		//default
	}

	_texture->UnlockRect( 0 );

	//free the memory where we loaded the tga
	delete cxImagePtr;
	cxImagePtr = NULL;
	return true;
}

bool KGraphicDX9::loadPictureWithMask( const char *filename, const char	*filenameMask, bool hiDef ) 
{
	freePicture();

	_hidef = hiDef;
	_hasAlpha =	true;

	return loadPicture32( filename, filenameMask, _hidef, true );
}

bool KGraphicDX9::loadPicture( const char *filename, bool hiDef, bool hasalpha )  
{
	freePicture();

	_hidef = hiDef;
	_hasAlpha =	hasalpha;

	return loadPicture32( filename, NULL, _hidef, _hasAlpha );
}


bool KGraphicDX9::createTexture( long width, long height, long bpp )
{
	HRESULT	hr;
	D3DFORMAT d3dFormat;

	if ( _d3d9Device == NULL )		
	{
		return false;
	}

	d3dFormat = D3DFMT_A8R8G8B8;

	hr = _d3d9Device->CreateTexture( width, height, 
		1, //only one level of mipmapping
		D3DUSAGE_DYNAMIC, //usage  -D3DUSAGE_RENDERTARGET  for a rendering target
		d3dFormat ,
		D3DPOOL_DEFAULT,
		&_texture,
		NULL);

	_imageWidth = width;
	_imageHeight = height;

	if ( hr != D3D_OK )
	{
		return false;
	}
	return true;  
}


bool KGraphicDX9::loadPicture32( const char	*filename, const char *filenameMask, bool hidef, bool hasAlpha )
{
/*
	unsigned char * imageBits = NULL;
	CxImage	* cxi = NULL;
	KResource resImage;
	KResourceResult result;
	BYTE * buffer;
	int size = 0;

	//    strlwr( filename ) ;
	result = resImage.open ( filename, K_RES_READ );
	if ( result != K_RES_OK ) 
	{
		return NULL;
	}

	resImage.seek( K_RES_END, 0 );
	result = resImage.tell( size );
	if ((result != K_RES_OK) || (!size)) 
	{
		return NULL;
	}
	resImage.seek( K_RES_BEGIN, 0);

	buffer = new BYTE [size];
	resImage.read (buffer, size);
	resImage.close ();

	loadPictureFromPtr(filename,buffer,size,hidef,hasAlpha);
*/

	long x, y;
	tgaBitmap tgaInfo;
	CxImage *cxImagePtr;	
	CxImage *cxImageMaskPtr = NULL;	

	_maskedUsed = false;

	if ( _d3d9Ptr == NULL || _d3d9Device == NULL )		
	{
		strcpy ( _imageFileName, "" );
		//MessageBox( 0, "directx not initialized", 0, 0 );
		return false;
	}

	strcpy( _imageFileName, filename );
	if ( filenameMask != NULL )
	{
		strcpy( _imageMaskFileName, filenameMask );
	}
	else
	{
		strcpy( _imageMaskFileName, "" );
	}

	cxImagePtr = (CxImage*)LoadGeneric( filename );
	if ( cxImagePtr == NULL )	
	{
		strcpy( _imageFileName, "" );
		return false;
	}

	if ( filenameMask != NULL  && strcmp( filenameMask, "" ) != 0 )
	{
		cxImageMaskPtr = (CxImage*)LoadGeneric( filenameMask );
		_maskedUsed = true;
	}


	tgaInfo.bpp = (unsigned char)cxImagePtr->GetBpp();
	tgaInfo.width = (unsigned short)cxImagePtr->GetWidth();
	tgaInfo.height = (unsigned short)cxImagePtr->GetHeight();

	_ftextureWIDTH = tgaInfo.width;
	_ftextureHEIGHT = tgaInfo.height;
	fimageWidth = tgaInfo.width;
	fimageHeight = tgaInfo.height;

	long ct = cxImagePtr->GetColorType();

	if ( ct == 4 ) 
	{
		tgaInfo.bpp = 32;
	}

	if ( createTexture( (long)fimageWidth, (long)fimageHeight,  tgaInfo.bpp ) == false )
	{
		delete cxImagePtr;
		return false;
	}


	HRESULT hr;
	D3DLOCKED_RECT lockedRect;

	hr = _texture->LockRect( 0, &lockedRect, NULL, 0 );

	unsigned char *ptr = (unsigned char *) lockedRect.pBits;
	long surfacePitch = lockedRect.Pitch;
	unsigned char r, g, b, a;

	long imageWidth = tgaInfo.width;
	long imageHeight = tgaInfo.height;


	switch ( tgaInfo.bpp )
	{
	case 32:
		{
			for ( x = 0 ; x < imageWidth ; x++ )
			{
				for ( y = 0 ; y < imageHeight ; y++ )
				{
					RGBQUAD color;
					color = cxImagePtr->GetPixelColor( x,  imageHeight - ( y + 1 ), true );

					r = color.rgbRed;
					g = color.rgbGreen;
					b = color.rgbBlue;
					a = color.rgbReserved;
					if  ( cxImageMaskPtr != NULL )
					{
						a = cxImageMaskPtr->GetPixelColor( x, imageHeight - ( y + 1 ), true).rgbBlue;
					}
					if ( _ckActive == true && _ckr == r && _ckb == b && _ckg == g )
					{
						a = 0;							
					}
					ptr[ 4 * x + y * (long)surfacePitch] = b;					//r
					ptr[ 4 * x + y * (long)surfacePitch + 1] = g;				//g
					ptr[ 4 * x + y * (long)surfacePitch + 2] = r;				//b
					ptr[ 4 * x + y * (long)surfacePitch + 3] = a;				//a							
				}	
			}//for x
		}
		break; //case 32
	default:
		{
			//8 or 16 or 24 bits
			for ( x = 0 ; x < imageWidth ; x++ )
			{
				for ( y = 0 ; y < imageHeight ; y++ )
				{
					RGBQUAD color;
					color = cxImagePtr->GetPixelColor( x, imageHeight - ( y + 1 ), false );

					r = color.rgbRed;
					g = color.rgbGreen;
					b = color.rgbBlue;
					a = 255;
					if ( cxImageMaskPtr != NULL )
					{
						a = cxImageMaskPtr->GetPixelColor( x, imageHeight - ( y + 1 ), true ).rgbBlue;
					}

					if ( _ckActive == true && _ckr == r && _ckb == b && _ckg == g )
					{
						a = 0;							
					}

					ptr[ 4 * x + y * (long)surfacePitch] = b;			    	//r
					ptr[ 4 * x + y * (long)surfacePitch + 1] = g;				//g
					ptr[ 4 * x + y * (long)surfacePitch + 2] = r;				//b
					ptr[ 4 * x + y * (long)surfacePitch + 3] = a;				//a							

				}	
			}
		}
		break;    		//default
	}

	_texture->UnlockRect( 0 );

	//free the memory where we loaded the tga
	delete cxImagePtr;
	cxImagePtr = NULL;
	if ( cxImageMaskPtr != NULL )
	{
		delete cxImageMaskPtr;
		cxImageMaskPtr = NULL;
	}
	return true;
}


unsigned char* KGraphicDX9::LoadGeneric( const char *filename )
{
	unsigned char * imageBits = NULL;
	CxImage	* cxi = NULL;
	KResource resImage;
	KResourceResult result;
	BYTE * buffer;
	int size = 0;

	//    strlwr( filename ) ;
	result = resImage.open ( filename, K_RES_READ );
	if ( result != K_RES_OK ) 
	{
		return NULL;
	}

	resImage.seek( K_RES_END, 0 );
	result = resImage.tell( size );
	if ((result != K_RES_OK) || (!size)) 
	{
		return NULL;
	}
	resImage.seek( K_RES_BEGIN, 0);

	buffer = new BYTE [size];
	resImage.read (buffer, size);
	resImage.close ();

	if ( strstr( filename,".tga") != NULL )
	{
		cxi = new CxImage( buffer, (DWORD) size, CXIMAGE_FORMAT_TGA );
	}

	if ( strstr( filename,".jpg") != NULL )
	{
		cxi = new CxImage( buffer, (DWORD) size, CXIMAGE_FORMAT_JPG );
	}

	if ( strstr( filename,".bmp") != NULL )
	{
		cxi = new CxImage( buffer, (DWORD) size, CXIMAGE_FORMAT_BMP );			
	}

	if ( strstr( filename,".png") != NULL )
	{
		cxi = new CxImage( buffer, (DWORD) size, CXIMAGE_FORMAT_PNG );
	}

	delete[] buffer;
	return	(unsigned char*)cxi; 
}


//frees the picture
void KGraphicDX9::freePicture() 
{
	if ( _texture != NULL )
	{
		_texture->Release();
		_texture = NULL;
	}
}

float KGraphicDX9::getTextureWidth() 
{
	return (float)_imageWidth;
}

float KGraphicDX9::getTextureHeight()
{
	return (float)_imageHeight;
}

void KGraphicDX9::setTextureQuality( bool quality ) 
{
	_quality = quality ;

	if (quality == false )
	{
		_textureQualityD3D = D3DTEXF_POINT;
    }
    else
    {
    	_textureQualityD3D = D3DTEXF_LINEAR ;
    }
}

void KGraphicDX9::Project( int nbVertexs, int nbIndices, D3DPRIMITIVETYPE type ) 
{
	void * vertexDataPtr;

	HRESULT hr;

	hr = _vertexBuffer->Lock( 0, nbVertexs * sizeof( PTKVERTEX ), &vertexDataPtr, 0 );
	if ( hr != D3D_OK )
	{
		return;
	}

	memcpy( vertexDataPtr, _ptkVertex, sizeof( PTKVERTEX ) * nbVertexs );
	_vertexBuffer->Unlock();

	hr = _d3d9Device->SetFVF( D3DFVF_PTKVERTEX );
	if ( hr != D3D_OK )		
	{
		return;
	}

	hr = _d3d9Device->SetStreamSource( 0, _vertexBuffer, 0, sizeof( PTKVERTEX ) );
	if ( hr != D3D_OK )		
	{
		return;
	}

	hr = _d3d9Device->DrawPrimitive( type , 0, nbIndices );
	if ( hr != D3D_OK )		
	{
		return;
	}
}

void KGraphicDX9::drawRect( float x1, float y1, float x2, float y2, float r, float g, float b, float blend ) 
{
	HRESULT hr = _d3d9Device->TestCooperativeLevel();

	if(!SUCCEEDED(hr))
	{
		return;
	}

	SetStates( false, true );

	for (int i = 0; i < 4 ; i++)
	{
		_ptkVertex[i].z = 0.0f;
		_ptkVertex[i].u = 0;
		_ptkVertex[i].v = 0;
		_ptkVertex[i].color = D3DCOLOR_ARGB((int)(blend*255), (int)(r*255), (int)(g*255), (int)(b*255));
	}

	_ptkVertex[0].x = x1;
	_ptkVertex[0].y = y1;

	_ptkVertex[1].x = x2;
	_ptkVertex[1].y = y1;

	_ptkVertex[2].x = x2;
	_ptkVertex[2].y = y2;

	_ptkVertex[3].x = x1;
	_ptkVertex[3].y = y2;

	Project( 4, 2, D3DPT_TRIANGLEFAN );

}

void KGraphicDX9::setLineWidth( float lineWidth )
{
	_lineWidth = lineWidth;
}

void KGraphicDX9::drawLine( short x1, short y1 , short x2 , short y2 , float r , float g , float b, float asource, float adest )
{
	HRESULT hr = _d3d9Device->TestCooperativeLevel();
	if(!SUCCEEDED(hr))
	{
		return;
	}

	ID3DXLine *pLine = NULL;
	D3DXCreateLine(_d3d9Device, &pLine);
	pLine->SetWidth(_lineWidth);
	
	D3DXVECTOR2 v[2];
	v[0].x = x1;
	v[0].y = y1;
	v[1].x = x2;
	v[1].y = y2;

	D3DXMATRIX worldMatrix;
	_d3d9Device->GetTransform( D3DTS_WORLD, &worldMatrix );

	pLine->Begin();
	pLine->Draw( v, 2, /*0xffffffff*/D3DCOLOR_ARGB((int)(adest*255), (int)(r*255), (int)(g*255), (int)(b*255)) ); 
	//pLine->DrawTransform(v,2,&worldMatrix,D3DCOLOR_ARGB((int)(adest*255), (int)(r*255), (int)(g*255), (int)(b*255)) );
	pLine->End();


/*

	HRESULT hr = _d3d9Device->TestCooperativeLevel();
	if(!SUCCEEDED(hr))
	{
		return;
	}

	SetStates( false, true );

	for (int i = 0; i < 2 ; i++)
	{
		_ptkVertex[i].z = 0.0f;
		_ptkVertex[i].u = 0;
		_ptkVertex[i].v = 0;
		_ptkVertex[i].color = D3DCOLOR_ARGB((int)(adest*255), (int)(r*255), (int)(g*255), (int)(b*255));
	}

	_ptkVertex[0].x = x1;
	_ptkVertex[0].y = y1;

	_ptkVertex[1].x = x2;
	_ptkVertex[1].y = y2;

	Project( 2, 1, D3DPT_LINELIST );
	*/
}

void KGraphicDX9::plotPixel( float x1, float y1, float r, float g, float b, float blend )
{
	HRESULT hr = _d3d9Device->TestCooperativeLevel();

	if(!SUCCEEDED(hr))
	{
		return;
	}

	SetStates( false, true );

	for (int i = 0; i < 1 ; i++)
	{
		_ptkVertex[i].z = 0.0f;
		_ptkVertex[i].u = 0;
		_ptkVertex[i].v = 0;
		_ptkVertex[i].color = D3DCOLOR_ARGB((int)(blend*255), (int)(r*255), (int)(g*255), (int)(b*255));
	}

	_ptkVertex[0].x = x1;
	_ptkVertex[0].y = y1;

	Project( 1, 1, D3DPT_POINTLIST );
}


void KGraphicDX9::PrepareRect( float x1, float y1, float x2, float y2, float destX, float destY, bool flipx, bool flipy )
{
	float sx1, sy1, sx2, sy2;
	float spriteWidth, spriteHeight;

	spriteWidth = x2 - x1;
	spriteHeight = y2 - y1;

	if (flipx)
	{
		sx1 = (float)x2 - 0.5f;
		sx2 = (float)x1 + 0.5f;
	}
	else
	{
		sx1 = (float)x1 + 0.5f;
		sx2 = (float)x2 - 0.5f;
	}

	if (flipy)
	{
		sy1 = (float)y2 - 0.5f;
		sy2 = (float)y1 + 0.5f;
	}
	else
	{
		sy1 = (float)y1 + 0.5f;
		sy2 = (float)y2 - 0.5f;
	}

	float u1 = sx1 / _ftextureWIDTH;
	float v1 = sy1 / _ftextureHEIGHT;
	float u2 = sx2 / _ftextureWIDTH;
	float v2 = sy2 / _ftextureHEIGHT;

/*
	float u1 = (sx1+0.5f) / _ftextureWIDTH;
	float v1 = (sy1+0.5f) / _ftextureHEIGHT;

	float u2 = (sx2-0.5f) / _ftextureWIDTH;
	float v2 = (sy2-0.5f) / _ftextureHEIGHT;
*/
	/*
	u_start = (fx1+0.5f) / _imageWidth;
	u_end = (fx2-0.5f) / _imageWidth;
	v_start = (fy1+0.5f) / _imageHeight;
	v_end = (fy2-0.5f) / _imageHeight;
	*/

	_ptkVertex[0].x = destX;
	_ptkVertex[0].y = destY;
	_ptkVertex[0].u = u1;
	_ptkVertex[0].v = v1;

	_ptkVertex[1].x = destX + spriteWidth;
	_ptkVertex[1].y = destY;
	_ptkVertex[1].u = u2;
	_ptkVertex[1].v = v1;

	_ptkVertex[2].x = destX + spriteWidth;
	_ptkVertex[2].y = destY + spriteHeight;
	_ptkVertex[2].u = u2;
	_ptkVertex[2].v = v2;

	_ptkVertex[3].x = destX;
	_ptkVertex[3].y = destY + spriteHeight;
	_ptkVertex[3].u = u1;
	_ptkVertex[3].v = v2;
}

void KGraphicDX9::SetStates(bool textured, bool alpha)
{
	_d3d9Device->SetRenderState( D3DRS_SEPARATEALPHABLENDENABLE, FALSE );
	
	if (alpha)
	{
		_d3d9Device->SetRenderState( D3DRS_ALPHABLENDENABLE, TRUE );
	}
	else
	{
		_d3d9Device->SetRenderState( D3DRS_ALPHABLENDENABLE, FALSE );
	}

	_d3d9Device->SetRenderState( D3DRS_SRCBLEND, _sourceAlpha);
	_d3d9Device->SetRenderState( D3DRS_DESTBLEND, _destAlpha);

	_d3d9Device->SetRenderState( D3DRS_CULLMODE, D3DCULL_NONE );

	_d3d9Device->SetRenderState( D3DRS_LIGHTING, FALSE );

	if (textured)
	{
		_d3d9Device->SetTextureStageState( 0, D3DTSS_COLOROP,   D3DTOP_MODULATE );
		_d3d9Device->SetTextureStageState( 0, D3DTSS_COLORARG1, D3DTA_TEXTURE );
		_d3d9Device->SetTextureStageState( 0, D3DTSS_COLORARG2, D3DTA_DIFFUSE );

		_d3d9Device->SetTextureStageState( 0, D3DTSS_ALPHAOP,   D3DTOP_MODULATE );
		_d3d9Device->SetTextureStageState( 0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE );
		_d3d9Device->SetTextureStageState( 0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE );

		_d3d9Device->SetSamplerState( 0, D3DSAMP_MAGFILTER, _textureQualityD3D);
		_d3d9Device->SetSamplerState( 0, D3DSAMP_MINFILTER, _textureQualityD3D);

		_d3d9Device->SetSamplerState( 0, D3DSAMP_ADDRESSU, _textureWrapD3D );
		_d3d9Device->SetSamplerState( 0, D3DSAMP_ADDRESSV, _textureWrapD3D );

		bindTexture();
	}
	else
	{
		_d3d9Device->SetTexture(0,NULL);
	}
}

void KGraphicDX9::PrepareFx( float x1, float y1, float x2, float y2, 
							float destX, float destY, float angle, float zoom, 
							float centerX, float centerY )
{
	D3DXMATRIX worldMatrix;
	_d3d9Device->GetTransform( D3DTS_WORLD, &worldMatrix );

	D3DXMATRIX translateMatrix;
	D3DXMATRIX rotateMatrix;
	D3DXMATRIX scaleMatrix;

	D3DXMATRIX worldMatrix2;
	D3DXMatrixIdentity( &worldMatrix2 );

	float x = (x2-x1) * 0.5f + centerX;
	float y = (y2-y1) * 0.5f + centerY;

	D3DXMatrixTranslation( &translateMatrix, -x, -y, 0 );
	D3DXMatrixMultiply( &worldMatrix2, &worldMatrix2, &translateMatrix );

	D3DXMatrixRotationZ( &rotateMatrix, -angle / 180 * 3.14159265358979323846f );
	D3DXMatrixMultiply( &worldMatrix2, &worldMatrix2, &rotateMatrix );

	D3DXMatrixScaling( &scaleMatrix, zoom, zoom, 0 );
	D3DXMatrixMultiply( &worldMatrix2, &worldMatrix2, &scaleMatrix );

	D3DXMatrixTranslation( &translateMatrix, x+destX, y+destY, 0 );
	D3DXMatrixMultiply( &worldMatrix2, &worldMatrix2, &translateMatrix );

//	D3DXMatrixScaling( &scaleMatrix, -1, 1, 1 );
//	D3DXMatrixMultiply( &worldMatrix2, &worldMatrix2, &scaleMatrix );

	D3DXMatrixMultiply( &worldMatrix2, &worldMatrix2, &worldMatrix );

	_d3d9Device->SetTransform( D3DTS_WORLD, &worldMatrix2 );
}

// blitting in integer
void KGraphicDX9::blitRect( float x1, float y1, float x2, float y2, short destX, short destY, bool flipx, bool flipy )
{
	HRESULT hr = _d3d9Device->TestCooperativeLevel();

	if(!SUCCEEDED(hr))
	{
		return;
	}

	SetStates( true, false );

	for (int i = 0; i < 4; i++)
	{
		_ptkVertex[i].z = 0.0f;
		_ptkVertex[i].color = D3DCOLOR_ARGB( (int)(_blitAlpha*255), (int)(_blitRed*255), (int)(_blitGreen*255), (int)(_blitBlue*255) );
	}

	PrepareRect( x1, y1, x2, y2, destX, destY, flipx, flipy );

	Project( 4, 2, D3DPT_TRIANGLEFAN );
}

void KGraphicDX9::blitRectFx( float	x1, float y1, float x2, float y2, 
							 short	destX, short destY, float angle, float zoom, 
							 bool flipx, bool flipy) 
{
	HRESULT hr = _d3d9Device->TestCooperativeLevel();

	if(!SUCCEEDED(hr))
	{
		return;
	}

	D3DXMATRIX worldMatrix;
	_d3d9Device->GetTransform( D3DTS_WORLD , &worldMatrix );

	PrepareFx( x1, y1, x2, y2, destX, destY, angle, zoom );

	SetStates( true, false );

	for (int i = 0; i < 4; i++)
	{
		_ptkVertex[i].z = 0.0f;
		_ptkVertex[i].color = D3DCOLOR_ARGB( (int)(_blitAlpha*255), (int)(_blitRed*255), (int)(_blitGreen*255), (int)(_blitBlue*255) );
	}

	PrepareRect( x1, y1, x2, y2, 0, 0, flipx, flipy );

	Project( 4, 2, D3DPT_TRIANGLEFAN );

	_d3d9Device->SetTransform( D3DTS_WORLD, &worldMatrix );
}

void KGraphicDX9::blitAlphaRect( float x1, float y1, float x2, float y2, short destX, short	destY, bool flipx, bool flipy ) 
{
	HRESULT hr = _d3d9Device->TestCooperativeLevel();

	if(!SUCCEEDED(hr))
	{
		return;
	}

//	D3DXMATRIX worldMatrix;
//	_d3d9Device->GetTransform( D3DTS_WORLD , &worldMatrix) ;

//	PrepareFx( x1, y1, x2, y2, destX, destY, 0, 1, 0, 0 );

	SetStates( true, true );

	for (int i = 0; i < 4 ; i++)
	{
		_ptkVertex[i].z = 0.0f;
		_ptkVertex[i].color = D3DCOLOR_ARGB( (int)(_blitAlpha*255), (int)(_blitRed*255), (int)(_blitGreen*255), (int)(_blitBlue*255) );
	}

	PrepareRect( x1, y1, x2, y2, destX, destY, flipx, flipy );

	Project( 4, 2, D3DPT_TRIANGLEFAN );

//	_d3d9Device->SetTransform( D3DTS_WORLD , &worldMatrix) ;
}

void KGraphicDX9::blitAlphaRectFx( float x1, float y1, float x2, float y2, 
								  short destX, short destY, float angle, float zoom, 
								  float blend, bool flipx, bool flipy, 
								  float centerX, float centerY )  
{
	HRESULT hr = _d3d9Device->TestCooperativeLevel();

	if(!SUCCEEDED(hr))
	{
		return;
	}

	D3DXMATRIX worldMatrix;
	_d3d9Device->GetTransform( D3DTS_WORLD , &worldMatrix) ;

	PrepareFx( x1, y1, x2, y2, destX, destY, angle, zoom, centerX, centerY );

	SetStates( true, true );

	for (int i = 0; i < 4; i++)
	{
		_ptkVertex[i].z = 0.0f;
		_ptkVertex[i].color = D3DCOLOR_ARGB( (int)(blend*_blitAlpha*255), (int)(_blitRed*255), (int)(_blitGreen*255), (int)(_blitBlue*255) );
	}

	PrepareRect( x1, y1, x2, y2, 0, 0, flipx, flipy );

	Project( 4, 2, D3DPT_TRIANGLEFAN );

	_d3d9Device->SetTransform( D3DTS_WORLD , &worldMatrix) ;
}



//blitting in sub pixels
void KGraphicDX9::blitRectF( float x1, float y1, float x2, float y2, float destX, float destY , bool flipx, bool flipy ) 
{
	HRESULT hr = _d3d9Device->TestCooperativeLevel();

	if(!SUCCEEDED(hr))
	{
		return;
	}

	SetStates( true, false );

	for (int i = 0; i < 4; i++)
	{
		_ptkVertex[i].z = 0.0f;
		_ptkVertex[i].color = D3DCOLOR_ARGB( (int)(_blitAlpha*255), (int)(_blitRed*255), (int)(_blitGreen*255), (int)(_blitBlue*255) );
	}

	PrepareRect( x1, y1, x2, y2, destX, destY, flipx, flipy );

	Project( 4, 2, D3DPT_TRIANGLEFAN );
}

void KGraphicDX9::blitRectFxF( float x1, float y1, float x2, float y2, 
							  float destX, float destY, float angle, float zoom, 
							  bool flipx, bool flipy ) 
{
	HRESULT hr = _d3d9Device->TestCooperativeLevel();

	if(!SUCCEEDED(hr))
	{
		return;
	}

	D3DXMATRIX worldMatrix;
	_d3d9Device->GetTransform( D3DTS_WORLD , &worldMatrix );

	PrepareFx( x1, y1, x2, y2, destX, destY, angle, zoom );

	SetStates( true, false );

	for (int i = 0; i < 4; i++)
	{
		_ptkVertex[i].z = 0.0f;
		_ptkVertex[i].color = D3DCOLOR_ARGB( (int)(_blitAlpha*255), (int)(_blitRed*255), (int)(_blitGreen*255), (int)(_blitBlue*255) );
	}

	PrepareRect( x1, y1, x2, y2, 0, 0, flipx, flipy );

	Project( 4, 2, D3DPT_TRIANGLEFAN );

	_d3d9Device->SetTransform( D3DTS_WORLD, &worldMatrix );
}

void KGraphicDX9::blitAlphaRectF( float x1, float y1, float x2, float y2, float destX, float destY, bool flipx, bool flipy ) 
{
	HRESULT hr = _d3d9Device->TestCooperativeLevel();

	if(!SUCCEEDED(hr))
	{
		return;
	}

	SetStates( true, true );

	for (int i = 0; i < 4 ; i++)
	{
		_ptkVertex[i].z = 0.0f;
		_ptkVertex[i].color = D3DCOLOR_ARGB( (int)(_blitAlpha*255), (int)(_blitRed*255), (int)(_blitGreen*255), (int)(_blitBlue*255) );
	}

	PrepareRect( x1, y1, x2, y2, destX, destY, flipx, flipy );

	Project( 4, 2, D3DPT_TRIANGLEFAN );
}

void KGraphicDX9::blitAlphaRectFxF( float x1, float y1, float x2, float y2, 
								   float destX, float destY, float angle, float zoom, 
								   float blend, bool flipx, bool flipy, 
								   float centerX, float centerY ) 
{
	HRESULT hr = _d3d9Device->TestCooperativeLevel();

	if(!SUCCEEDED(hr))
	{
		return;
	}

	D3DXMATRIX worldMatrix;
	_d3d9Device->GetTransform( D3DTS_WORLD , &worldMatrix) ;

	PrepareFx( x1, y1, x2, y2, destX, destY, angle, zoom, centerX, centerY );

	SetStates( true, true );

	for (int i = 0; i < 4 ; i++)
	{
		_ptkVertex[i].z = 0.0f;
		_ptkVertex[i].color = D3DCOLOR_ARGB( (int)(blend*_blitAlpha*255), (int)(_blitRed*255), (int)(_blitGreen*255), (int)(_blitBlue*255) );
	}
	PrepareRect( x1, y1, x2, y2, 0, 0, flipx, flipy );

	Project( 4, 2, D3DPT_TRIANGLEFAN );

	_d3d9Device->SetTransform( D3DTS_WORLD , &worldMatrix) ;
}

void KGraphicDX9::blitTiledRect(short destX, short destY, short width, short height, 
								float tileFactor, float angle ) 
{
	HRESULT hr = _d3d9Device->TestCooperativeLevel();

	if(!SUCCEEDED(hr))
	{
		return;
	}

	D3DXMATRIX worldMatrix;
	_d3d9Device->GetTransform( D3DTS_WORLD , &worldMatrix );

	SetStates( true, false );

	for (int i = 0; i < 4; i++)
	{
		_ptkVertex[i].z = 0.0f;
		_ptkVertex[i].color = D3DCOLOR_ARGB( (int)(_blitAlpha*255), (int)(_blitRed*255), (int)(_blitGreen*255), (int)(_blitBlue*255) );
	}

	_d3d9Device->SetSamplerState( 0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP );
	_d3d9Device->SetSamplerState( 0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP );

	D3DXMATRIX translateMatrix;
	D3DXMATRIX rotateMatrix;

	D3DXMATRIX worldMatrix2;
	D3DXMatrixIdentity( &worldMatrix2 );

	float x = width * 0.5f;
	float y = height * 0.5f;

	D3DXMatrixTranslation( &translateMatrix, -x, -y, 0 );
	D3DXMatrixMultiply( &worldMatrix2, &worldMatrix2, &translateMatrix );

	D3DXMatrixRotationZ( &rotateMatrix, angle / 180 * 3.14159265358979323846f );
	D3DXMatrixMultiply( &worldMatrix2, &worldMatrix2, &rotateMatrix );

	D3DXMatrixTranslation( &translateMatrix, x + destX, y + destY, 0 );
	D3DXMatrixMultiply( &worldMatrix2, &worldMatrix2, &translateMatrix );

	D3DXMatrixMultiply( &worldMatrix2, &worldMatrix2, &worldMatrix );

	_d3d9Device->SetTransform( D3DTS_WORLD, &worldMatrix2 );

	_ptkVertex[0].x = 0;
	_ptkVertex[0].y = 0;
	_ptkVertex[0].u = 0;
	_ptkVertex[0].v = 0;

	_ptkVertex[1].x = width;
	_ptkVertex[1].y = 0;
	_ptkVertex[1].u = tileFactor;
	_ptkVertex[1].v = 0;

	_ptkVertex[2].x = width;
	_ptkVertex[2].y = height;
	_ptkVertex[2].u = tileFactor;
	_ptkVertex[2].v = tileFactor;

	_ptkVertex[3].x = 0;
	_ptkVertex[3].y = height;
	_ptkVertex[3].u = 0;
	_ptkVertex[3].v = tileFactor;

	Project( 4, 2, D3DPT_TRIANGLEFAN );

	_d3d9Device->SetTransform( D3DTS_WORLD, &worldMatrix );
}
//arbitraty blits
void KGraphicDX9::blitArbitraryQuad( float sx1, float sy1, float sx2, float sy2, 
									float sx3, float sy3, float sx4, float sy4, 
									float dx1, float dy1, float dx2, float dy2, 
									float dx3, float dy3, float dx4, float dy4 ) 
{
	HRESULT hr = _d3d9Device->TestCooperativeLevel();

	if(!SUCCEEDED(hr))
	{
		return;
	}

	SetStates( true, true );

	for (int i = 0; i < 4 ; i++)
	{
		_ptkVertex[i].z = 0.0f;
		_ptkVertex[i].color = D3DCOLOR_ARGB( (int)(_blitAlpha*255), (int)(_blitRed*255), (int)(_blitGreen*255), (int)(_blitBlue*255) );
	}

	float su1 = sx1/_ftextureWIDTH;
	float su2 = sx2/_ftextureWIDTH;

	float sv1 = sy1/_ftextureHEIGHT;
	float sv2 = sy2/_ftextureHEIGHT;

	float su3 = sx3/_ftextureWIDTH;
	float su4 = sx4/_ftextureWIDTH;

	float sv3 = sy3/_ftextureHEIGHT;
	float sv4 = sy4/_ftextureHEIGHT;

	_ptkVertex[0].x = dx1;
	_ptkVertex[0].y = dy1;
	_ptkVertex[0].u = su1;
	_ptkVertex[0].v = sv1;

	_ptkVertex[1].x = dx2;
	_ptkVertex[1].y = dy2;
	_ptkVertex[1].u = su2;
	_ptkVertex[1].v = sv2;

	_ptkVertex[2].x = dx3;
	_ptkVertex[2].y = dy3;
	_ptkVertex[2].u = su3;
	_ptkVertex[2].v = sv3;

	_ptkVertex[3].x = dx4;
	_ptkVertex[3].y = dy4;
	_ptkVertex[3].u = su4;
	_ptkVertex[3].v = sv4;

	Project( 4, 2, D3DPT_TRIANGLESTRIP );
}

//alpha additif ou normal ? ( false = noir transparent + ajout des couleurs )
void KGraphicDX9::setAlphaMode( long alphamode ) 
{
	switch ( alphamode )
	{
		//additive
	case 0:
		_sourceAlpha = D3DBLEND_SRCALPHA;
		_destAlpha = D3DBLEND_DESTALPHA;
		break ;

		//normal
	case 1:
		_sourceAlpha = D3DBLEND_SRCALPHA;
		_destAlpha = D3DBLEND_INVSRCALPHA;
		break ;

	case 2:
		_sourceAlpha = D3DBLEND_ONE;
		_destAlpha = D3DBLEND_INVSRCALPHA;
		break ;

	case 3:
		_sourceAlpha = D3DBLEND_ZERO;
		_destAlpha = D3DBLEND_INVSRCALPHA;
		break ;

	case 4:
		_sourceAlpha = D3DBLEND_SRCALPHA;
		_destAlpha = D3DBLEND_ONE; 	
		break ;

		// Copy Blender
	case 5: 
		_sourceAlpha = D3DBLEND_ONE;
		_destAlpha = D3DBLEND_ZERO;
		break ;	

	case 6:
		_sourceAlpha = D3DBLEND_INVSRCALPHA;
		_destAlpha = D3DBLEND_ONE;
		break;

	case 7:
		_sourceAlpha = D3DBLEND_SRCALPHA;
		_destAlpha = D3DBLEND_ZERO;
		break;
	case 8:
		_sourceAlpha = D3DBLEND_SRCCOLOR;
		_destAlpha = D3DBLEND_ONE;
		break;
	}
}

void KGraphicDX9::setAlphaMode( long alphamodeSource, long alphamodeDest ) 
{
	_sourceAlpha = (D3DBLEND) alphamodeSource;
	_destAlpha = (D3DBLEND) alphamodeDest;
}

//stretching
void KGraphicDX9::stretchAlphaRect( float sx1, float sy1, float sx2, float sy2, 
								   float dx1, float dy1, float dx2, float dy2, 
								   float blend, float angle, bool flipx, bool flipy, 
								   float centerX, float centerY ) 
{
	HRESULT hr = _d3d9Device->TestCooperativeLevel();

	if(!SUCCEEDED(hr))
	{
		return;
	}

	D3DXMATRIX worldMatrix;
	_d3d9Device->GetTransform( D3DTS_WORLD , &worldMatrix) ;

	PrepareFx( dx1, dy1, dx2, dy2, dx1, dy1, angle, 1, centerX, centerY );

	SetStates( true, true );

	for (int i = 0; i < 4 ; i++)
	{
		_ptkVertex[i].z = 0.0f;
		_ptkVertex[i].color = D3DCOLOR_ARGB( (int)(blend*_blitAlpha*255), (int)(_blitRed*255), (int)(_blitGreen*255), (int)(_blitBlue*255) );
	}

	float x1, y1, x2, y2;
	float spriteWidth, spriteHeight;

	spriteWidth = dx2 - dx1;
	spriteHeight = dy2 - dy1;

	if (flipx)
	{
		x1 = (float)sx2;
		x2 = (float)sx1 - 0.1f;
	}
	else
	{
		x1 = (float)sx1;
		x2 = (float)sx2 + 0.1f;
	}

	if (flipy)
	{
		y1 = (float)sy2;
		y2 = (float)sy1 - 0.1f;
	}
	else
	{
		y1 = (float)sy1;
		y2 = (float)sy2 + 0.1f;
	}

	float u1 = x1 / _ftextureWIDTH;
	float v1 = y1 / _ftextureHEIGHT;

	float u2 = x2 / _ftextureWIDTH;
	float v2 = y2 / _ftextureHEIGHT;

	_ptkVertex[0].x = 0;
	_ptkVertex[0].y = 0;
	_ptkVertex[0].u = u1;
	_ptkVertex[0].v = v1;

	_ptkVertex[1].x = spriteWidth;
	_ptkVertex[1].y = 0;
	_ptkVertex[1].u = u2;
	_ptkVertex[1].v = v1;

	_ptkVertex[2].x = spriteWidth;
	_ptkVertex[2].y = spriteHeight;
	_ptkVertex[2].u = u2;
	_ptkVertex[2].v = v2;

	_ptkVertex[3].x = 0;
	_ptkVertex[3].y = spriteHeight;
	_ptkVertex[3].u = u1;
	_ptkVertex[3].v = v2;

	Project( 4, 2, D3DPT_TRIANGLEFAN );

	_d3d9Device->SetTransform( D3DTS_WORLD , &worldMatrix) ;
}

//recupere le buffer et le mets dans une texture	
bool KGraphicDX9::grabBackBuffer( pixelCallBackPtr pixelFunc ) 
{
	HRESULT hr = _d3d9Device->TestCooperativeLevel();

	if(!SUCCEEDED(hr))
	{
		return false;
	}

	IDirect3DSurface9* pTargetSurface=NULL;
	_d3d9Device->GetRenderTarget(0,&pTargetSurface);
	
	D3DSURFACE_DESC desc;
	pTargetSurface->GetDesc(&desc);
	
	IDirect3DTexture9* pTempTexture=NULL;
	_d3d9Device->CreateTexture(desc.Width,desc.Height,
		1,D3DUSAGE_DYNAMIC,desc.Format,D3DPOOL_SYSTEMMEM,&pTempTexture,NULL);
		
	IDirect3DSurface9* pTempSurface=NULL;
	pTempTexture->GetSurfaceLevel(0,&pTempSurface);
	_d3d9Device->GetRenderTargetData(pTargetSurface,pTempSurface);
	
	freePicture();

	_d3d9Device->CreateTexture( desc.Width, desc.Height, 
		1, //only one level of mipmapping
		D3DUSAGE_DYNAMIC, //usage  -D3DUSAGE_RENDERTARGET  for a rendering target
		desc.Format ,
		D3DPOOL_DEFAULT,
		&_texture,
		NULL);

	_imageWidth = desc.Width;
	_imageHeight = desc.Height;
	_ftextureWIDTH = (float)desc.Width;
	_ftextureHEIGHT = (float)desc.Height;
	
	hr = _d3d9Device->UpdateTexture(pTempTexture, _texture);

	pTargetSurface->Release();
	pTempSurface->Release();
	pTempTexture->Release();

	if (hr != D3D_OK)
	{
		return false;
	}

	return true;
}

bool KGraphicDX9::grabFrontBuffer( void ) 
{
	return grabBackBuffer();
}

//color key ( generates an alpha channel from a color key, must be called before loading the bitmap
void KGraphicDX9::setColorKey( bool active, unsigned char r, unsigned char g, unsigned char b ) 
{
	_ckActive = active ;
	_ckr = r ;
	_ckg = g ;
	_ckb = b ;
}

void KGraphicDX9::allowTextureWrap( bool textureWrap ) //allow texture wrapping ( only works with square textures )
{
	_textureWrap = textureWrap ;

	if ( _textureWrap == true )
	{
		_textureWrapD3D = D3DTADDRESS_WRAP ;
	}
	else
	{
		_textureWrapD3D = D3DTADDRESS_CLAMP ;
	}
}
//regle la couleur de blit
void KGraphicDX9::setBlitColor( float r, float g, float b, float a ) 
{
	_blitRed = (r > 1 ? 1 : ( r < 0 ? 0 : r ) );
	_blitGreen = (g > 1 ? 1 : ( g < 0 ? 0 : g ) );
	_blitBlue = (b > 1 ? 1 : ( b < 0 ? 0 : b ) );
	_blitAlpha = (a > 1 ? 1 : ( a < 0 ? 0 : a ) );
	_blitColorChanged = true ;
}


//if you want to make pictures from buffers  HIDEF == true will use 32 bits textures in memory, else it'll use the current depth
bool KGraphicDX9::makePictureFromArray( unsigned long *userPixelPtr, 
									   long width, long height, bool hiDef  ) 
{
	HRESULT hr = _d3d9Device->TestCooperativeLevel();

	if(!SUCCEEDED(hr))
	{
		return false;
	}


	freePicture();

	if  ( createTexture( width, height, 0 ) == false )
	{
		return false;
	}	

	D3DLOCKED_RECT lockedRect;

	hr = _texture->LockRect( 0, &lockedRect, NULL, 0 );

	unsigned char *ptr = (unsigned char *) lockedRect.pBits;
	long surfacePitch = lockedRect.Pitch;
	unsigned char r, g, b, a;

	long imageWidth = width;
	long imageHeight = height;
	_imageWidth = width;
	_imageHeight = height;
	_ftextureWIDTH = (float)width;
	_ftextureHEIGHT = (float)height;

	for ( long  x = 0 ; x < imageWidth ; x++ )
	{
		for ( long y = 0 ; y < imageHeight ; y++ )
		{
			unsigned long color = userPixelPtr[x+y*imageWidth] ;
			r = (color & 0xFF);
			g = (color >> 8) & 0xFF;
			b = (color >> 16) & 0xFF;
			a = (color >> 24) & 0xFF;
			if ( _ckActive == true && _ckr == r && _ckb == b && _ckg == g )
			{
				a = 0;							
			}
			ptr[ 4 * x + y * (long)surfacePitch] = b;					//r
			ptr[ 4 * x + y * (long)surfacePitch + 1] = g;				//g
			ptr[ 4 * x + y * (long)surfacePitch + 2] = r;				//b
			ptr[ 4 * x + y * (long)surfacePitch + 3] = a;				//a							
		}	
	}

	_texture->UnlockRect( 0 );

	return true;
}
//if you want to "refresh" the texture created by makePictureFromArray you can just call poll 
void KGraphicDX9::pollArray( void )
{
}

void KGraphicDX9::gpuFinish( void ) 
{
}

bool KGraphicDX9::grabBackBufferFast(  long  x, long  y, long  w, long  h )   
{
	return grabBackBuffer();
}

bool KGraphicDX9::grabFrontBufferFast( void ) 
{
	return grabBackBuffer();
}

//used by K3D ( does a glBind )
void KGraphicDX9::selectTexture( void ) 
{
	bindTexture();
}

void KGraphicDX9::setZoom( float zx, float zy )  
{
	_zoomX = zx ;
	_zoomY = zy ;
}

//binds the texture before a blit
void KGraphicDX9::bindTexture()
{
	if ( _d3d9Device == NULL )
	{
		_oldTexture  = 0 ;
		return ;
	}
	_oldTexture = _texture ;
	if (_texture == NULL && strcmp(_imageFileName,"") != 0)
	{
		loadPictureWithMask(_imageFileName, _imageMaskFileName, true);
	}
	_d3d9Device->SetTexture( 0 ,_texture ) ;
}

bool KGraphicDX9::CreateRenderTarget(int width, int height)
{
	//HRESULT hr = _d3d9Device->TestCooperativeLevel();

	//if(!SUCCEEDED(hr))
	//{
	//	return false;
	//}

	////_d3d9Device->GetRenderTarget(0,&_pSavedTargetSurface);
	//
	//if (_pTargetTexture != NULL)
	//{
	//	_pTargetTexture->Release();
	//	_pTargetSurface->Release();
	//}
	//// on cree une texture qui servira de render target provisoire
 //   // Usage.RenderTarget
	//_d3d9Device->CreateTexture( width, height, 
	//	1, 
	//	D3DUSAGE_RENDERTARGET,
	//	D3DFMT_A8R8G8B8,
	//	D3DPOOL_DEFAULT,
	//	&_pTargetTexture,
	//	NULL);
	//_pTargetTexture->GetSurfaceLevel(0,&_pTargetSurface);

	//_targetWidth = width;
	//_targetHeight = height;
	//return true ;

	
	HRESULT hr = _d3d9Device->TestCooperativeLevel();

	if(!SUCCEEDED(hr))
	{
		return false;
	}

	_d3d9Device->GetRenderTarget(0,&_pSavedTargetSurface);

	if( _pTargetSurface )
	{
		_pTargetSurface->Release();
		_pTargetSurface = NULL;
	}

	freePicture();

	_d3d9Device->CreateTexture( width, height, 
		1, 
		D3DUSAGE_RENDERTARGET,
		D3DFMT_A8R8G8B8,
		D3DPOOL_DEFAULT,
		&_texture,
		NULL);
	_texture->GetSurfaceLevel(0,&_pTargetSurface);

	_targetWidth = _imageWidth		= width;
	_targetHeight = _imageHeight	= height;

	_ftextureWIDTH = (float)width;
	_ftextureHEIGHT = (float)height;

	return true;
}

bool KGraphicDX9::startRenderToTexture()
{
	//HRESULT hr = _d3d9Device->TestCooperativeLevel();

	//if(!SUCCEEDED(hr))
	//{
	//	return false;
	//}

	//if (_pTargetSurface == NULL)
	//{
	//	return false;
	//}
	//_d3d9Device->SetRenderTarget(0, _pTargetSurface);


	//return true;

	HRESULT hr = _d3d9Device->TestCooperativeLevel();

	if(!SUCCEEDED(hr))
	{
		return false;
	}

	if (_pTargetSurface == NULL)
	{
		return false;
	}
	_d3d9Device->SetRenderTarget(0, _pTargetSurface);


	return true;
}

bool KGraphicDX9::endRenderToTexture()
{
	//HRESULT hr = _d3d9Device->TestCooperativeLevel();

	//if(!SUCCEEDED(hr))
	//{
	//	return false;
	//}

	//if (_pTargetSurface == NULL)
	//{
	//	return false;
	//}

	//D3DSURFACE_DESC desc;
	//_pTargetSurface->GetDesc(&desc);
	//
	//IDirect3DTexture9* pTempTexture=NULL;
	//_d3d9Device->CreateTexture(desc.Width,desc.Height,
	//	1,D3DUSAGE_DYNAMIC,desc.Format,D3DPOOL_SYSTEMMEM,&pTempTexture,NULL);
	//	
	//IDirect3DSurface9* pTempSurface=NULL;
	//pTempTexture->GetSurfaceLevel(0,&pTempSurface);
	//_d3d9Device->GetRenderTargetData(_pTargetSurface,pTempSurface);
	//
	//freePicture();

	//_d3d9Device->CreateTexture( desc.Width, desc.Height, 
	//	1, //only one level of mipmapping
	//	D3DUSAGE_DYNAMIC, //usage  -D3DUSAGE_RENDERTARGET  for a rendering target
	//	desc.Format ,
	//	D3DPOOL_DEFAULT,
	//	&_texture,
	//	NULL);

	//_imageWidth = desc.Width;
	//_imageHeight = desc.Height;
	//_ftextureWIDTH = (float)desc.Width;
	//_ftextureHEIGHT = (float)desc.Height;
	//
	//hr = _d3d9Device->UpdateTexture(pTempTexture, _texture);

	//pTempSurface->Release();
	//pTempTexture->Release();
	
	HRESULT hr = _d3d9Device->TestCooperativeLevel();

	if(!SUCCEEDED(hr))
	{
		return false;
	}

	if (_pTargetSurface == NULL)
	{
		return false;
	}

	_d3d9Device->SetRenderTarget(0, _pSavedTargetSurface);

	return true;
}
