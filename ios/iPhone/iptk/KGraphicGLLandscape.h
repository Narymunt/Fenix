#ifndef PTK_KGRAPHICGLLAND__
#define PTK_KGRAPHICGLLAND__

#include <string.h>
#include <OpenGLES/ES1/gl.h>
#include <OpenGLES/ES1/glext.h>

#include "KGraphic.h"



// opengl 1.2 ( standart is ms' opengl 1.1 !!! )
#ifndef GL_CLAMP_TO_EDGE  
#define GL_CLAMP_TO_EDGE					0x812F 
#endif

#ifndef GL_CLAMP_TO_BORDER
#define GL_CLAMP_TO_BORDER                0x812D
#endif




class KGraphicGLLAND : public KGraphic
{
	private:
	GLuint      textureID;
	static GLuint		_oldBindedText ;
		
	int		_screenX, _screenY;

	float	_imageWidth  ;
	float	_imageHeight  ;
	float	_textureSize ;
	bool	_textureQuality ;
	
	void	GenericBlit( short x1 , short y1 , short x2 , short y2 , short destX , short destY , bool flipx , bool flipy )  ;
	
	float	_blitRed ,_blitGreen,_blitBlue 		 ;
	float	_blitAlpha 		 ;
	bool	_blitColorChanged ;
	unsigned short 		_sourceAlpha   , _destAlpha ;
	

	public:

	//	long	RendererState;


		KGraphicGLLAND(int _sx, int _sy);
		~KGraphicGLLAND();

		bool	loadWatermark();
		bool	loadPicture(char *filename,bool u1,bool u2);
		void	blitAlphaRectFx(int x1, int y1, int x2, int y2, int destX, int destY, float angle, float zoom, float blend , bool flipx=false , bool flipy=false ) ;
		void	blitAlphaRect(int x1, int y1, int x2, int y2, int destX, int destY , bool flipx=false , bool flipy=false ) ;
	void	drawRect( short x1,short y1 , short x2 , short y2 , float r , float g , float b, float a ) ;

	
		void	freePicture( void ) ;
		void	setTextureQuality( bool quality ) ;
		void	setBlitColor( float r , float g , float b , float a ) ;
		void	setAlphaMode( long	alphamode ) ;
	
		float	getTextureSize( void ) ;

	
	void	drawLine( short x1,short y1 , short x2 , short y2 , float r , float g , float b, float asource, float adest ) ;

	void	setLineWidth( short lineWith ) ;
	void	ptk_glBindTexture( void  ) ;
	
	void	grabToTexture(KGraphic *g);

};

#endif // PTK_KGRAPHICGL

