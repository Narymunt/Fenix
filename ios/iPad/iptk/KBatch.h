
#ifndef		DEF_KBATCHGL

#define		DEF_KBATCHGL

#include "KGraphicGL.h"
#include "GLTextureHelper.h"

#include	"KGraphic.h"




class	 KBatch
{
private:
	GLshort			*quadPtr ;
	GLfloat			*texuvPtr ;
	GLfloat			*texColor ;  //couleur des blits
	
	long			quadCount ;
	
	void							freeBuffer( void ) ;
	long							_currentQuad ;
	float							_textureSize ;
	float							_r,_g,_b,_a ;
	unsigned short 		_sourceAlpha   , _destAlpha ;
	long							_curColorIndex ;

	float							cosr_lup[360*8];
	float							sinr_lup[360*8];
	
public:

	KBatch( ) ;
	~KBatch( ) ;
	
	KGraphic						*_texturePtr ;
	
	bool		allocateBuffer( long polygoncount ) ;
	void		beginBatch( KGraphic	*surface ) ;

	void		endBatch( void ) ;
	
	
	//blit used for all the function , acts the same way as KGraphic::blitAlphaRect
	void		blitAlphaRect(long x1, long y1, long x2, long y2, float destX, float destY ) ;
	void		blitAlphaRectFx( float	x1, float y1 , float	x2 , float y2 , short	destX , short	destY, float angle, float zoom, float blend  ) ;

	void		drawRect( float	x1, float y1 , float	x2 , float y2 , float r ,float g ,float b ,  float blend ) ;
	void		setBlitColor( float r , float g , float b , float a ) ;
	void		setAlphaMode( long	alphamode ) ;

};

#endif
