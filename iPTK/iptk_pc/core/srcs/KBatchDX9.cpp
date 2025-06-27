#include	"KGraphicDX9.h"
#include	"KBatchDX9.h"

LPDIRECT3D9							KBatchDX9::_d3d9Ptr = NULL ;
LPDIRECT3DDEVICE9				KBatchDX9::_d3d9Device = NULL ;

#ifndef	M_2PI
#define  M_PI        3.14159265358979323846f
#define  M_2PI       (2.0f * M_PI)
#endif

float KBatchDX9::_texelSX = 0 ;
float KBatchDX9::_texelSY = 0 ;
float KBatchDX9::_texelDX = -0.5 ;
float KBatchDX9::_texelDY = -0.5 ;

std::vector<KBatchDX9*>   KBatchDX9::currents;

void KBatchDX9::setTexelInfo( float sx, float sy, float dx, float dy ) 
{
	_texelSX = sx ;
	_texelSY = sy ;
	_texelDX = dx ;
	_texelDY = dy ;
}

void KBatchDX9::setDirectX( LPDIRECT3D9 d3d9Ptr, LPDIRECT3DDEVICE9 d3d9Device ) 
{
	_d3d9Ptr = d3d9Ptr;
	_d3d9Device = d3d9Device;
} 


void KBatchDX9::releaseCurrents()
{
	for (int i = 0; i < KBatchDX9::currents.size(); i++)
	{
		KBatchDX9::currents[i]->_allocated = KBatchDX9::currents[i]->releaseBuffer();
	}
}
void KBatchDX9::initCurrents()
{
	for (int i = 0; i < KBatchDX9::currents.size(); i++)
	{
		if (KBatchDX9::currents[i]->_allocated)
		{
			KBatchDX9::currents[i]->allocateBuffer(KBatchDX9::currents[i]->_quadCount);
		}
	}
}

KBatchDX9::KBatchDX9( ) 
{
	_quadCount = 0;
	_allocated = false;
	_maxVertice = 0;
	_vertexBuffer = NULL;
	setAlphaMode( 1 );
	setBlitColor( 1, 1, 1, 1 );
	currents.push_back(this);
}

KBatchDX9::~KBatchDX9( ) 
{
	releaseBuffer();
	std::vector<KBatchDX9*>::iterator it;
	for (it = currents.begin(); it != currents.end(); it++)
	{
		if (*it == this)
		{
			currents.erase(it);
			break;
		}
	}	
}

//allocate the vertex buffer
bool KBatchDX9::releaseBuffer() 
{
	if ( _vertexBuffer != NULL )
	{
		_vertexBuffer->Release();
		_vertexBuffer = NULL;
		return true;
	}
	return false;
}
//allocate the vertex buffer
bool KBatchDX9::allocateBuffer( long quadCount ) 
{
	_quadCount = quadCount;
	HRESULT hr = _d3d9Device->TestCooperativeLevel();

	if(!SUCCEEDED(hr))
	{
		return false;
	}

	releaseBuffer();

	// 1 quad = 2 triangles = 6 vertices
	//_maxVertice = quadCount*2*6 ;
	// 1 triangle fan de 4 vertices * nb de quads 
	_maxVertice = quadCount*4 ;
	if ( _d3d9Device  != NULL )
	{
		_d3d9Device->CreateVertexBuffer( _maxVertice*sizeof( PTKVERTEX ),
			D3DUSAGE_DYNAMIC,
			D3DFVF_PTKVERTEX,
			D3DPOOL_DEFAULT,
			&_vertexBuffer, NULL);
	}

	if ( _vertexBuffer == NULL )		
	{
		return false;
	}

	return true ;	
}

//begin batch
void KBatchDX9::beginBatch( KGraphic * surface ) 
{
	HRESULT hr = _d3d9Device->TestCooperativeLevel();

	if(!SUCCEEDED(hr))
	{
		return;
	}


	if ( _vertexBuffer == NULL )
	{
		allocateBuffer( 512 );
	}

	if ( surface == NULL )	
	{
		_texturePtr = NULL;
	}
	else
	{
		_texturePtr = (KGraphicDX9*)surface;
	}

	_verticeCount = 0;

	_d3d9Device->GetTransform(D3DTS_WORLD, &_matWorld); // sauvegarde de la matrice

	_vertexBuffer->Lock( 0, _maxVertice * sizeof( PTKVERTEX ), &vertexDataPtr, 0 );

}


//end batch
void KBatchDX9::endBatch( void ) 
{
	HRESULT hr = _d3d9Device->TestCooperativeLevel();

	if(!SUCCEEDED(hr))
	{
		return;
	}

	_vertexBuffer->Unlock();

	if ( _verticeCount > 0 ) 
	{

		if (_texturePtr != NULL)
		{
			_texturePtr->SetStates(_textureflag,true);
		}
		else
		{
			_d3d9Device->SetRenderState( D3DRS_SEPARATEALPHABLENDENABLE, FALSE );
			_d3d9Device->SetRenderState( D3DRS_ALPHABLENDENABLE, TRUE );
			_d3d9Device->SetRenderState( D3DRS_DESTBLEND, _destAlpha);
			_d3d9Device->SetRenderState( D3DRS_SRCBLEND, _sourceAlpha);

			_d3d9Device->SetRenderState( D3DRS_CULLMODE, D3DCULL_NONE );

			_d3d9Device->SetRenderState( D3DRS_LIGHTING, FALSE );

			_d3d9Device->SetTexture(0,NULL);
		}

		HRESULT hr = _d3d9Device->SetFVF( D3DFVF_PTKVERTEX );
		if ( hr != D3D_OK )		
		{
			return;
		}

		hr = _d3d9Device->SetStreamSource( 0, _vertexBuffer, 0, sizeof( PTKVERTEX ) );
		if ( hr != D3D_OK )		
		{
			return;
		}

		for (int i = 0; i < _verticeCount; i+=4)
		{
			_d3d9Device->DrawPrimitive (D3DPT_TRIANGLEFAN, i, 2);
		}

	}
	_d3d9Device->SetTransform(D3DTS_WORLD, &_matWorld); // restauration de la matrice

}


void KBatchDX9::drawRect( float	x1, float y1, float	x2, float y2, 
						 float r, float g, float b, float blend ) 
{
	HRESULT hr = _d3d9Device->TestCooperativeLevel();

	if(!SUCCEEDED(hr))
	{
		return;
	}

	//out of space in thebuffer ? let's flush
	if ( _verticeCount >=  _maxVertice )
	{
		endBatch( ) ;
		beginBatch( (KGraphicDX9*)_texturePtr) ; 
	}

	_textureflag = false;

	if (_texturePtr != NULL)
	{
		_blitAlpha = _texturePtr->_blitAlpha;
		_blitRed= _texturePtr->_blitRed;
		_blitGreen= _texturePtr->_blitGreen;
		_blitBlue= _texturePtr->_blitBlue;
	}
	
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

	memcpy( &((PTKVERTEX*)vertexDataPtr)[_verticeCount], _ptkVertex, sizeof( PTKVERTEX ) * 4 );

	_verticeCount += 4;
}

//blit used for all the function
void KBatchDX9::blitAlphaRect(long x1, long y1, long x2, long y2, 
							  float destX, float destY, bool flipx, bool flipy ) 
{
	HRESULT hr = _d3d9Device->TestCooperativeLevel();

	if(!SUCCEEDED(hr))
	{
		return;
	}

	//out of space in thebuffer ? let's flush
	if ( _verticeCount >=  _maxVertice )
	{
		endBatch( ) ;
		beginBatch( (KGraphicDX9*)_texturePtr) ; 
	}

	_textureflag = true;
	
	if (_texturePtr != NULL)
	{
		_blitAlpha = _texturePtr->_blitAlpha;
		_blitRed= _texturePtr->_blitRed;
		_blitGreen= _texturePtr->_blitGreen;
		_blitBlue= _texturePtr->_blitBlue;
	}
	
	for (int i = 0; i < 4 ; i++)
	{
		_ptkVertex[i].z = 0.0f;
		_ptkVertex[i].color = D3DCOLOR_ARGB( (int)(_blitAlpha*255), (int)(_blitRed*255), (int)(_blitGreen*255), (int)(_blitBlue*255) );
	}

	float sx1, sy1, sx2, sy2;
	float spriteWidth, spriteHeight;

	spriteWidth = x2 - x1;
	spriteHeight = y2 - y1;

	if (flipx)
	{
		sx1 = (float)x2;
		sx2 = (float)x1 - 0.1f;
	}
	else
	{
		sx1 = (float)x1;
		sx2 = (float)x2 + 0.1f;
	}

	if (flipy)
	{
		sy1 = (float)y2;
		sy2 = (float)y1 - 0.1f;
	}
	else
	{
		sy1 = (float)y1;
		sy2 = (float)y2 + 0.1f;
	}

	float u1 = sx1 / (_texturePtr != NULL ? _texturePtr->getTextureWidth() : 1);
	float v1 = sy1 / (_texturePtr != NULL ? _texturePtr->getTextureHeight() : 1);

	float u2 = sx2 / (_texturePtr != NULL ? _texturePtr->getTextureWidth() : 1);
	float v2 = sy2 / (_texturePtr != NULL ? _texturePtr->getTextureHeight() : 1);

	_ptkVertex[0].x = destX+_texelDX;
	_ptkVertex[0].y = destY+_texelDY;
	_ptkVertex[0].u = u1;
	_ptkVertex[0].v = v1;

	_ptkVertex[1].x = destX + spriteWidth+_texelDX;
	_ptkVertex[1].y = destY+_texelDY;
	_ptkVertex[1].u = u2;
	_ptkVertex[1].v = v1;

	_ptkVertex[2].x = destX + spriteWidth+_texelDX;
	_ptkVertex[2].y = destY + spriteHeight+_texelDY;
	_ptkVertex[2].u = u2;
	_ptkVertex[2].v = v2;

	_ptkVertex[3].x = destX+_texelDX;
	_ptkVertex[3].y = destY + spriteHeight+_texelDY;
	_ptkVertex[3].u = u1;
	_ptkVertex[3].v = v2;

	memcpy( &((PTKVERTEX*)vertexDataPtr)[_verticeCount], _ptkVertex, sizeof( PTKVERTEX ) * 4 );

	_verticeCount += 4;
}




void KBatchDX9::blitAlphaRectFx( float x1, float y1, float x2, float y2, 
								float destX, float destY, float angle, float zoom, float blend, 
								bool flipx, bool flipy, float centerX, float centerY )   
{
	HRESULT hr = _d3d9Device->TestCooperativeLevel();
long i ;
	if(!SUCCEEDED(hr))
	{
		return;
	}

	//out of space in thebuffer ? let's flush
	if ( _verticeCount >=  _maxVertice )
	{
		endBatch( ) ;
		beginBatch( (KGraphicDX9*)_texturePtr) ; 
	}

	//PrepareFx( x1, y1, x2, y2, destX, destY, angle, zoom, centerX, centerY );
	_textureflag = true;

	if (_texturePtr != NULL)
	{
		_blitAlpha = _texturePtr->_blitAlpha;
		_blitRed= _texturePtr->_blitRed;
		_blitGreen= _texturePtr->_blitGreen;
		_blitBlue= _texturePtr->_blitBlue;
	}
	
	for ( i = 0; i < 4 ; i++)
	{
		_ptkVertex[i].z = 0.0f;
		_ptkVertex[i].color = D3DCOLOR_ARGB( (int)(blend*_blitAlpha*255), (int)(_blitRed*255), (int)(_blitGreen*255), (int)(_blitBlue*255) );
	}

	float sx1, sy1, sx2, sy2;
	float spriteWidth, spriteHeight;

	spriteWidth = (x2 - x1) / 2;
	spriteHeight = (y2 - y1) /2 ;

	float X[4], Y[4];
	X[0] = -centerX-spriteWidth;
	Y[0] = -centerY-spriteHeight;
	X[1] = -centerX+spriteWidth; 
	Y[1] = -centerY-spriteHeight;
	X[2] = -centerX+spriteWidth;
	Y[2] = -centerY+spriteHeight;
	X[3] = -centerX-spriteWidth;
	Y[3] = -centerY+spriteHeight;

	float angle_rad 	= 	(M_2PI*angle) /360.0f ;
	float cos_angle 	= 	cos(angle_rad) ;
	float sin_angle 	= 	sin(angle_rad) ;
	float xf, yf;
	for ( i = 0; i < 4; i++)
	{
		xf = X[i] * cos_angle + Y[i] * sin_angle;
		yf = Y[i] * cos_angle - X[i] * sin_angle;
		X[i] = xf * zoom + destX + (spriteWidth + centerX) * zoom;
		Y[i] = yf * zoom + destY + (spriteHeight + centerY) * zoom;
	}

	if (flipx)
	{
		sx1 = (float)x2;
		sx2 = (float)x1 - 0.1f;
	}
	else
	{
		sx1 = (float)x1;
		sx2 = (float)x2 + 0.1f;
	}

	if (flipy)
	{
		sy1 = (float)y2;
		sy2 = (float)y1 - 0.1f;
	}
	else
	{
		sy1 = (float)y1;
		sy2 = (float)y2 + 0.1f;
	}

	float u1 = sx1 / (_texturePtr != NULL ? _texturePtr->getTextureWidth() : 1);
	float v1 = sy1 / (_texturePtr != NULL ? _texturePtr->getTextureHeight() : 1);

	float u2 = sx2 / (_texturePtr != NULL ? _texturePtr->getTextureWidth() : 1);
	float v2 = sy2 / (_texturePtr != NULL ? _texturePtr->getTextureHeight() : 1);

	_ptkVertex[0].x = X[0]+_texelDX;
	_ptkVertex[0].y = Y[0]+_texelDY;
	_ptkVertex[0].u = u1;
	_ptkVertex[0].v = v1;

	_ptkVertex[1].x = X[1]+_texelDX;
	_ptkVertex[1].y = Y[1]+_texelDY;
	_ptkVertex[1].u = u2;
	_ptkVertex[1].v = v1;

	_ptkVertex[2].x = X[2]+_texelDX;
	_ptkVertex[2].y = Y[2]+_texelDY;
	_ptkVertex[2].u = u2;
	_ptkVertex[2].v = v2;

	_ptkVertex[3].x = X[3]+_texelDX;
	_ptkVertex[3].y = Y[3]+_texelDY;
	_ptkVertex[3].u = u1;
	_ptkVertex[3].v = v2;

	memcpy( &((PTKVERTEX*)vertexDataPtr)[_verticeCount], _ptkVertex, sizeof( PTKVERTEX ) * 4 );

	_verticeCount+=4;
}






//regle la couleur de blit
void KBatchDX9::setBlitColor( float r, float g, float b, float a ) 
{
	_blitRed = (r > 1 ? 1 : ( r < 0 ? 0 : r ) );
	_blitGreen = (g > 1 ? 1 : ( g < 0 ? 0 : g ) );
	_blitBlue = (b > 1 ? 1 : ( b < 0 ? 0 : b ) );
	_blitAlpha = (a > 1 ? 1 : ( a < 0 ? 0 : a ) );
	_blitColorChanged = true ;
}
//alpha additif ou normal ? ( false = noir transparent + ajout des couleurs )
void KBatchDX9::setAlphaMode( long alphamode ) 
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
	}
}

void KBatchDX9::setAlphaMode( long alphamodeSource, long alphamodeDest ) 
{
	_sourceAlpha = (D3DBLEND) alphamodeSource;
	_destAlpha = (D3DBLEND) alphamodeDest;
}

