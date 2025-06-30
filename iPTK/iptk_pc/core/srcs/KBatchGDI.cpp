#include	"KBatchGDI.h"





KBatchGDI::KBatchGDI( ) 
{
}

KBatchGDI::~KBatchGDI( ) 
{


}

//allocate the vertex buffer
bool		KBatchGDI::allocateBuffer( long quadCount ) 
{
	quadCount = quadCount ;

	return true ;	
}

//begin batch
void		KBatchGDI::beginBatch( KGraphic	*surface ) 
{

	if ( surface == NULL )	return ;

	_texturePtr = (KGraphic*)surface ;


}


//end batch
void		KBatchGDI::endBatch( void ) 
{

}

void		KBatchGDI::blitAlphaRectFx( float	x1, float y1 , float	x2 , float y2 , float	destX , float	destY, float angle, float zoom, float blend , bool flipx,bool flipy ) 
{
	_texturePtr->blitAlphaRectFx( x1,y1,x2,y2, destX , destY , angle, zoom, blend ) ;	
}

//blit used for all the function
void KBatchGDI::blitAlphaRect(long x1, long y1, long x2, long y2, float destX, float destY , bool flipx,bool flipy )  
{
	_texturePtr->blitAlphaRect( x1,y1,x2,y2, destX , destY ) ;	
}

