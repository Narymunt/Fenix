/*
 *  KGraphic.h
*  Copyright 2010 jmApp.com All rights reserved.
 *
 */

#ifndef API_KGRAPHIC__
#define API_KGRAPHIC__

#include <stdio.h>
#include <stdlib.h>



class KGraphic
{

public:
	
	KGraphic() {} ;
	virtual	~KGraphic()  {} ;
	

	virtual	bool	loadWatermark()=0;
	virtual	bool	loadPicture(char *filename , bool  unused=false , bool unused2=false) = 0;

	virtual	void	blitAlphaRectFx(int x1, int y1, int x2, int y2, int dx, int dy, float rotate, float zoom, float alpha , bool flipx=false , bool flipy=false)=0;	
	virtual	void	blitAlphaRect(int x1, int y1, int x2, int y2, int dx, int dy , bool flipx=false , bool flipy=false)=0;	
	virtual	void	drawRect( short x1,short y1 , short x2 , short y2 , float r , float g , float b, float a ) =0 ;

	virtual	void	setBlitColor( float r , float g , float b , float a ) =0;
	virtual	void	setAlphaMode( long	alphamode ) = 0 ;
	virtual	void	setTextureQuality( bool quality ) = 0;
	virtual	float	getTextureSize( void ) = 0 ;
	
	virtual	void	drawLine( short x1,short y1 , short x2 , short y2 , float r , float g , float b, float asource, float adest ) = 0 ;
	virtual	void	setLineWidth( short lineWidth ) = 0;
	virtual	void	ptk_glBindTexture( void ) = 0 ;
	
	virtual	void	grabToTexture(KGraphic *g) = 0;

	
};


#endif // API_KGRAPHIC__
