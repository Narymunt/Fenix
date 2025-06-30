#include	"KGraphicD3D.h"
#include	"KBatchD3D.h"

LPDIRECT3D7							KBatchD3D::_direct3d7 = NULL ;
LPDIRECT3DDEVICE7				KBatchD3D::_d3dDevice = NULL ;

#ifndef	M_2PI
	#define  M_PI        3.14159265358979323846f
	#define  M_2PI       (2.0f * M_PI)
#endif

float		KBatchD3D::_texelSX = 0 ;
float		KBatchD3D::_texelSY = 0.1 ;
float		KBatchD3D::_texelDX = 0.5 ;
float		KBatchD3D::_texelDY = 0.5 ;


void			KBatchD3D::setTexelInfo( float sx , float sy , float dx , float dy ) 
{
	_texelSX = sx ;
	_texelSY = sy ;
	_texelDX = dx ;
	_texelDY = dy ;
}

void		KBatchD3D::setDirectX( LPDIRECT3D7 d3d7ptr , LPDIRECT3DDEVICE7 d3device ) 
{
	
	_direct3d7 = d3d7ptr ;
	_d3dDevice = d3device ;
	
} 


KBatchD3D::KBatchD3D( ) 
{
	_maxVertice 		= 0 ;
	_d3dlvertexBuffer = NULL ;
}

KBatchD3D::~KBatchD3D( ) 
{
	if ( _d3dlvertexBuffer != NULL )
	{
		_d3dlvertexBuffer->Release(  )  ;
		_d3dlvertexBuffer = NULL ;
	}

}

//allocate the vertex buffer
bool		KBatchD3D::allocateBuffer( long quadCount ) 
{
D3DVERTEXBUFFERDESC 		ddvbDesc ;
HRESULT		hr ;


	if ( _d3dlvertexBuffer != NULL )
	{
		_d3dlvertexBuffer->Release(  )  ;
		_d3dlvertexBuffer  = NULL ;	
	}

	//1 quad = 2 triangles = 6 vertices
	_maxVertice = quadCount*2*6 ;


	memset ( &ddvbDesc , 0 , sizeof(  D3DVERTEXBUFFERDESC ) ) ;
	ddvbDesc.dwSize 	= sizeof( D3DVERTEXBUFFERDESC ) ;
	ddvbDesc.dwCaps 	= 0 ;
	ddvbDesc.dwFVF 	=  D3DFVF_LVERTEX ;
	ddvbDesc.dwNumVertices 	=  _maxVertice  ;

	
	hr = _direct3d7->CreateVertexBuffer( &ddvbDesc , &_d3dlvertexBuffer ,  0 ) ;
	if ( hr != D3D_OK )
	{
		MessageBox( 0,"could not create batching buffer" ,0 ,0 ) ;
		return false ;
	}

//	_d3dlvertexBuffer = new D3DLVERTEX[_maxVertice+12] ;

	if ( _d3dlvertexBuffer == NULL )		return false;

	return true ;	
}

void		KBatchD3D::freeBatchBuffer( void )
{
	if ( _d3dlvertexBuffer != NULL )
	{
		_d3dlvertexBuffer->Release( ) ;
		_d3dlvertexBuffer  = NULL ;	
	}
}
//begin batch
void		KBatchD3D::beginBatch( KGraphic	*surface ) 
{
	

	if ( _d3dlvertexBuffer == NULL )
	{
		allocateBuffer( 512 ) ;
	}


	if ( surface == NULL )	
	{
		_texturePtr = NULL ;
	}
	else
	{
		_texturePtr = (KGraphicD3D	*)surface ;
	}
	
	_verticeCount = 0 ;

	

	_d3dDevice->GetTransform(D3DTRANSFORMSTATE_WORLD, &_mat3); // sauvegarde de la matrice

}


//end batch
void		KBatchD3D::endBatch( void ) 
{
	//_vertexBuffer->Unlock( ) ;
	
	 if ( _verticeCount > 0  ) 
	 {
	 	if ( _texturePtr != NULL )
	 	{
			_texturePtr->selectTexture( ) ;
			_d3dDevice->SetRenderState(D3DRENDERSTATE_ALPHABLENDENABLE, true);
		  	_d3dDevice->SetTextureStageState(0,D3DTSS_MAGFILTER,    _texturePtr-> _textureQualityD3D      );
		    	_d3dDevice->SetTextureStageState(0,D3DTSS_MINFILTER,     _texturePtr->_textureQualityD3D      );	
	_d3dDevice->SetTextureStageState(0,D3DTSS_ADDRESS ,     _texturePtr-> _textureWrapD3D      );	    	
		_d3dDevice->SetTextureStageState(0,D3DTSS_ADDRESSU ,      _texturePtr->_textureWrapD3D      );	    	
		_d3dDevice->SetTextureStageState(0,D3DTSS_ADDRESSV ,      _texturePtr->_textureWrapD3D      );	 
	  	_d3dDevice->SetTextureStageState(0,D3DTSS_MAGFILTER,      _texturePtr->_textureQualityD3D      );
	    	_d3dDevice->SetTextureStageState(0,D3DTSS_MINFILTER,      _texturePtr->_textureQualityD3D      );	
		_d3dDevice->SetRenderState(D3DRENDERSTATE_SRCBLEND,  _texturePtr->_sourceAlpha);
		_d3dDevice->SetRenderState(D3DRENDERSTATE_DESTBLEND,  _texturePtr->_destAlpha);


			_texturePtr->setStates( ) ;
		}
		else
		{
				_d3dDevice->SetTexture(0, NULL);
				_d3dDevice->SetRenderState(D3DRENDERSTATE_ALPHABLENDENABLE, true);
		}

	

		 _d3dDevice->DrawPrimitiveVB (D3DPT_TRIANGLELIST, _d3dlvertexBuffer, 0, _verticeCount , 0 );
  	
  	}
	_d3dDevice->SetTransform(D3DTRANSFORMSTATE_WORLD, &_mat3); // restauration de la matrice

}
/*
void		KBatchD3D::drawLine( float	x1, float y1 , float	x2 , float y2 , float r ,float g ,float b ,  float blend ) 
{
/*
D3DLVERTEX v[4];
D3DCOLOR 		col ;
float					destX1 ,destY1 ,destX2 ,destY2  ;

x1 = x1 ;
x2 = x2 ;
y1 = y1 ;
y2 = y2 ;
r=r;
g=g;
b=b;
blend = blend ;


	x1+=_texelDX ;
	y1+=_texelDY ;
	x2+=_texelDX ;
	y2+=_texelDY ;
	
	
	destX1 	= x1 ;
	destY1 	= y1 ;
	destX2 	= x2 ;
	destY2 	= y2;
   
  

//	x1++;	x2++ ;

	_d3dDevice->SetRenderState(D3DRENDERSTATE_ALPHABLENDENABLE, TRUE);
	_d3dDevice->SetRenderState(D3DRENDERSTATE_SRCBLEND, D3DBLEND_SRCALPHA);
	_d3dDevice->SetRenderState(D3DRENDERSTATE_DESTBLEND, D3DBLEND_INVSRCALPHA);
	
	col = D3DRGBA(  1,0,0 , 1);

	v[0] = D3DLVERTEX(D3DVECTOR(destX1+_texelDX,destY1+_texelDY,0), 0,col, 0, 0, 0);
	v[1] = D3DLVERTEX(D3DVECTOR(destX2+_texelDX,destY1+_texelDY,0), 0,col, 0, 0, 0);
	v[2] = D3DLVERTEX(D3DVECTOR(destX1+_texelDX,destY2+_texelDY,0), 0,col, 0, 0, 0);
	v[3] = D3DLVERTEX(D3DVECTOR(destX2+_texelDX,destY2+_texelDY,0), 0,col, 0, 0, 0);



   D3DLVERTEX	 *vertexPtr = &_d3dlvertexBuffer[_verticeCount] ;
		   
		  memcpy( &vertexPtr[0] , &v[0] , sizeof(D3DLVERTEX)*3 ) ;		//we can use only 1 memcpy instead  of 3 since data is aligned
		  memcpy( &vertexPtr[3] , &v[1], sizeof(D3DLVERTEX) *3) ;		//we can use only 1 memcpy instead  of 3 since data is aligned
		   
		//a quad == 2 triangles  ( 6 points )
		_verticeCount += 6 ;

		//out of space in the buffer ? let's flush
		if ( _verticeCount >=  _maxVertice )
		{
			endBatch( ) ;
			beginBatch( (KGraphicD3D*)_texturePtr) ; 
		}
		
*/
		

void		KBatchD3D::drawRect( float	x1, float y1 , float	x2 , float y2 , float r ,float g ,float b ,  float blend ) 
{

D3DLVERTEX v[4];
D3DCOLOR 		col ;
float					destX1 ,destY1 ,destX2 ,destY2  ;


	x1+=_texelDX ;
	y1+=_texelDY ;
	x2+=_texelDX ;
	y2+=_texelDY ;
	
	
	destX1 	= x1 ;
	destY1 	= y1 ;
	destX2 	= x2 ;
	destY2 	= y2;
   
  

//	x1++;	x2++ ;

	_d3dDevice->SetRenderState(D3DRENDERSTATE_ALPHABLENDENABLE, TRUE);
	_d3dDevice->SetRenderState(D3DRENDERSTATE_SRCBLEND, D3DBLEND_SRCALPHA);
	_d3dDevice->SetRenderState(D3DRENDERSTATE_DESTBLEND, D3DBLEND_INVSRCALPHA);
	
	col = D3DRGBA(  r, g, b , blend);

	v[0] = D3DLVERTEX(D3DVECTOR(destX1,-destY1,0), col, 0, 0, 0);
	v[1] = D3DLVERTEX(D3DVECTOR(destX2,-destY1,0), col, 0, 0, 0);
	v[2] = D3DLVERTEX(D3DVECTOR(destX1,-destY2,0), col, 0, 0, 0);
	v[3] = D3DLVERTEX(D3DVECTOR(destX2,-destY2,0), col, 0, 0, 0);



//   D3DLVERTEX	 *vertexPtr = &_d3dlvertexBuffer[_verticeCount] ;
   D3DLVERTEX	 *vertexPtr = NULL ;
		 
 _d3dlvertexBuffer->Lock( DDLOCK_WRITEONLY  , (void**)&vertexPtr , NULL ) ;
		 
		  memcpy( &vertexPtr[_verticeCount] , &v[0] , sizeof(D3DLVERTEX)*3 ) ;		//we can use only 1 memcpy instead  of 3 since data is aligned
		  memcpy( &vertexPtr[_verticeCount+3] , &v[1], sizeof(D3DLVERTEX) *3) ;		//we can use only 1 memcpy instead  of 3 since data is aligned

 _d3dlvertexBuffer->Unlock(  ) ;
		 
		   
		//a quad == 2 triangles  ( 6 points )
		_verticeCount += 6 ;

		//out of space in the buffer ? let's flush
		if ( _verticeCount >=  _maxVertice )
		{
			endBatch( ) ;
			beginBatch( (KGraphicD3D*)_texturePtr) ; 
		}
		


}



//blit used for all the function
void KBatchD3D::blitAlphaRect(long x1, long y1, long x2, long y2, float destX, float destY , bool flipx , bool flipy) 
{
float 					sx1,sy1	, sx2,sy2 ;
D3DLVERTEX v[4];
D3DCOLOR 		col ;
float					destX1 ,destY1 ,destX2 ,destY2 ,w,h , tmpval ;

	
	destX1 	= destX ;
	destY1 	= destY ;
	destX2 	= destX + (x2 - x1) ;
	destY2 	= destY + (y2 - y1) ;
   
   	if ( flipx == true )
	{
		tmpval = destX1 ;
		destX1 = destX2 ;
		destX2 = tmpval ;
	}

	if ( flipy == true )
	{
		tmpval = destY1 ;
		destY1 = destY2 ;
		destY2 = tmpval ;
	}
	
	sx1 = (float)x1 ;
	sx2 = (float)x2 ;
	sy1 = (float)y1 ;
	sy2 = (float)y2 ;

	sx1+=_texelSX ;
	sy1+=_texelSY ;
	sx2+=_texelSX ;
	sy2+=_texelSY ;
	
	if ( _texturePtr->_blitColorChanged == false )
	{
		col = D3DRGBA( 1, 1,1 ,  1 );			//vector color  - like glColor4f
	}
	else
	{
		float		a = ((float)_texturePtr->_blitAlpha);
		 col = D3DRGBA(  _texturePtr->_blitRed, _texturePtr->_blitGreen, _texturePtr->_blitBlue , a );			//vector color  - like glColor4f
	}
	
	
	w = (sx2-sx1);				//-1 cuts
	h = (sy1-sy2);


	float u1 = (sx1/(_texturePtr->_ftextureWIDTH))+ _texelSX ;
	float v1 = (sy1/(_texturePtr->_ftextureHEIGHT))+ _texelSY;
	
	float u2 = (sx2/(_texturePtr->_ftextureWIDTH))+ _texelSX ;
	float v2 = (sy2/(_texturePtr->_ftextureHEIGHT))+ _texelSY;


	
	v[0] = D3DLVERTEX(D3DVECTOR(destX1+_texelDX,-(destY1+_texelDY),0),col, 0, u1, v1);
	v[1] = D3DLVERTEX(D3DVECTOR(destX2+_texelDX,-(destY1+_texelDY),0),col, 0, u2, v1);
	v[2] = D3DLVERTEX(D3DVECTOR(destX1+_texelDX,-(destY2+_texelDY),0),col, 0, u1, v2);
	v[3] = D3DLVERTEX(D3DVECTOR(destX2+_texelDX,-(destY2+_texelDY),0),col, 0, u2, v2);

				
   D3DLVERTEX	 *vertexPtr ; // = &_d3dlvertexBuffer[_verticeCount] ;

 	HRESULT hr = _d3dlvertexBuffer->Lock( 0  , (void**)&vertexPtr , NULL ) ;
	if ( vertexPtr == NULL )
	{
		return  ;
	}
	if ( hr != D3D_OK )
	{
		return  ;
	}
		   
		  memcpy( &vertexPtr[_verticeCount] , &v[0] , sizeof(D3DLVERTEX)*3 ) ;		//we can use only 1 memcpy instead  of 3 since data is aligned
		  memcpy( &vertexPtr[_verticeCount+3] , &v[1], sizeof(D3DLVERTEX) *3) ;		//we can use only 1 memcpy instead  of 3 since data is aligned

 _d3dlvertexBuffer->Unlock(  ) ;

		   
		//a quad == 2 triangles  ( 6 points )
		_verticeCount += 6 ;

		//out of space in the buffer ? let's flush
		if ( _verticeCount >=  _maxVertice )
		{
			endBatch( ) ;
			beginBatch( (KGraphicD3D*)_texturePtr) ; 
		}
}




void			KBatchD3D::blitAlphaRectFx( float	x1, float y1 , float	x2 , float y2 , float	destX , float	destY, float angle, float zoom, float blend   , bool flipx , bool flipy , float centerX , float centerY )   
{
float middlesizeX, middlesizeY;
long	vx,vy ;
float	destX1 , destY1 ,  destX2 , destY2 ;
float	destX3 , destY3 ,  destX4 , destY4 ;
float		tmpval ;

float	 xf, yf  ;
long iw ,ih ;
float cos_angle, sin_angle , angle_rad  ;
float	sx1,sy1,sx2,sy2    ;
float	rdx, rdy ;
D3DCOLOR 		col ;
 D3DLVERTEX v[4];
 

	
	sx1 = (float)x1 ;
	sx2 = (float)x2 ;
	sy1 = (float)y1 ;
	sy2 = (float)y2 ;
	
	sx1+=_texelSX ;
	sy1+=_texelSY ;
	sx2+=_texelSX ;
	sy2+=_texelSY ;

		
	iw = x2-x1 ;
	ih = y2-y1 ;
		
	if 	( blend <= 0 )			return ;
	if	(zoom == 0)			return;

	vx = ( x2-x1)/2  ;
	vy = ( y2-y1)/2 ;

 	middlesizeX	=	(( x2-x1 )) / 2 	;
	middlesizeY	=	(( y2-y1 )) / 2	;
	
/*
yf = y * cos(rad) - z * sin(rad);
zf = y* sin(rad) + z * cos(rad);
y=yf;
z=zf;
*/
	
// 	middlesizeX	=	(( x2-x1 )) / 2 	;
//	middlesizeY	=	(( y2-y1 )) / 2	;

//	middlesizeX*= zoom ;
//	middlesizeY *= zoom ;

	rdx = ((float)destX )+	vx ;
	rdy=	 ((float)destY)+	vy ;


	
	destX1 	= -middlesizeX;
	destY1 	= -middlesizeY ;
	destX2 	= middlesizeX ;
	destY2 	= -middlesizeY ;	
	destX3 	= -middlesizeX ;
	destY3 	= middlesizeY ;	
	destX4 	= middlesizeX ;
	destY4 	= middlesizeY ;
	
	destX1 -= centerX ;
	destX2 -= centerX ;
	destX3 -= centerX ;
	destX4 -= centerX ;

	destY1 -= centerY ;
	destY2 -= centerY ;
	destY3 -= centerY ;
	destY4 -= centerY ;
	
	if ( flipx == true )
	{
		tmpval = destX1 ;
		destX1 = destX2 ;
		destX2 = tmpval ;
		
		tmpval = destX3 ;
		destX3 = destX4 ;
		destX4 = tmpval ;				
	}

	if ( flipy == true )
	{
		tmpval = destY1 ;
		destY1 = destY2 ;
		destY2 = tmpval ;
		
		tmpval = destY3 ;
		destY3 = destY4 ;
		destY4 = tmpval ;				
	}


	if ( angle != 0 )
	{ 
		angle_rad 	= 	(M_2PI*angle) /360.0f ;
		cos_angle 	= 	cos(angle_rad) ;
		sin_angle 	= 	sin(angle_rad) ;
		
		//rotate our object
		xf = destX1*cos_angle +destY1*sin_angle 	;
		yf = destY1*cos_angle-destX1*sin_angle	 ;
		destX1 = xf ;
		destY1 = yf ;

		xf = destX2*cos_angle +destY2*sin_angle ;
		yf = destY2*cos_angle-destX2*sin_angle ;
		destX2 = xf ;
		destY2 = yf ;


		xf = destX3*cos_angle +destY3*sin_angle ;
		yf = destY3*cos_angle-destX3*sin_angle ;
		destX3 = xf ;
		destY3 = yf ;


		xf = destX4*cos_angle +destY4*sin_angle ;
		yf = destY4*cos_angle-destX4*sin_angle ;
		destX4 = xf ;
		destY4 = yf ;
	}

		destX1 	*= zoom;
		destY1 	*= zoom ;
		destX2 	*= zoom ;
		destY2 *= zoom ;	
		destX3 	*= zoom ;
		destY3 	*= zoom ;	
		destX4 	*= zoom ;
		destY4 	*= zoom ;



	//offset it back where it's supposed to be
	destX1 += rdx ;
	destY1 += rdy ;
	destX2 += rdx ;
	destY2 += rdy ;
	destX3 += rdx ;
	destY3 += rdy ;
	destX4 += rdx ;
	destY4 += rdy ;				
	
	if ( _texturePtr->_blitColorChanged == false )
	{
		col = D3DRGBA( 1, 1,1 ,  blend);			//vector color  - like glColor4f
	}
	else
	{
		float		a = ((float)blend*_texturePtr->_blitAlpha);
		 col = D3DRGBA(  _texturePtr->_blitRed, _texturePtr->_blitGreen, _texturePtr->_blitBlue , a );			//vector color  - like glColor4f
	}
	




	float u1 = (sx1/(_texturePtr->_ftextureWIDTH)) ;
	float v1 = (sy1/(_texturePtr->_ftextureHEIGHT));
	
	float u2 = (sx2/(_texturePtr->_ftextureWIDTH)) ;
	float v2 = (sy2/(_texturePtr->_ftextureHEIGHT));



	v[0] = D3DLVERTEX(D3DVECTOR(destX1+_texelDX,-(destY1+_texelDY),0),col, 0, u1, v1);
	v[1] = D3DLVERTEX(D3DVECTOR(destX2+_texelDX,-(destY2+_texelDY),0),col, 0, u2, v1);
	v[2] = D3DLVERTEX(D3DVECTOR(destX3+_texelDX,-(destY3+_texelDY),0),col, 0, u1, v2);
	v[3] = D3DLVERTEX(D3DVECTOR(destX4+_texelDX,-(destY4+_texelDY),0),col, 0, u2, v2);

				
   	D3DLVERTEX	 *vertexPtr ;// = &_d3dlvertexBuffer[_verticeCount] ;
		   
_d3dlvertexBuffer->Lock( DDLOCK_WAIT  , (void**)&vertexPtr , NULL ) ;


	 memcpy( &vertexPtr[_verticeCount] , &v[0] , sizeof(D3DLVERTEX)*3 ) ;		//we can use only 1 memcpy instead  of 3 since data is aligned  
	 memcpy( &vertexPtr[_verticeCount+3] , &v[1], sizeof(D3DLVERTEX) *3) ;		//we can use only 1 memcpy instead  of 3 since data is aligned
		    _d3dlvertexBuffer->Unlock(  ) ;
		   
	//a quad == 2 triangles  ( 6 points , we must use  a triangle list else if we blit more than 1 quad 1 gets attached  to 2 if you use a trianglestrip)
	_verticeCount += 6 ;

	//out of space in the buffer ? let's flush
	if ( _verticeCount >=  _maxVertice )
	{
		endBatch( ) ;
		beginBatch( (KGraphicD3D*)_texturePtr) ; 
	}


}