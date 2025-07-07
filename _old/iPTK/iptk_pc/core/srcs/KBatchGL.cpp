#include	"KBatchGL.h"

#include	"KGraphicGL.h"




KBatchGL::KBatchGL( ) 
{
}

KBatchGL::~KBatchGL( ) 
{


}

//allocate the vertex buffer
bool		KBatchGL::allocateBuffer( long quadCount ) 
{
	quadCount = quadCount ;

	return true ;	
}

//begin batch
void		KBatchGL::beginBatch( KGraphic	*surface ) 
{

	if ( surface == NULL )	return ;

	_texturePtr = (KGraphic*)surface ;


}


//end batch
void		KBatchGL::endBatch( void ) 
{

}


void		KBatchGL::drawLine( float	x1, float y1 , float	x2 , float y2 , float r ,float g ,float b ,  float blend )
{
     KGraphicGL::_oldBindedText = -1 ;
    
    y2 =  KGraphicGL::screenHeight - y2 ;
    y1 =  KGraphicGL::screenHeight - y1 ;
    


    
    glDisable( GL_TEXTURE_2D) ;
   
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
    
    //	 glLineWidth( 1 );
    
    glBegin (GL_LINE_LOOP);
		  glVertex2f (x1,y1);
          glVertex2f (x2,y2);
          glEnd( ) ;
          
          glDisable( GL_BLEND ) ;
          glColor4f( 1.0f , 1.0f ,1.0f ,1.0f ) ;
}



void		KBatchGL::drawRect( float	x1, float y1 , float	x2 , float y2 , float r ,float g ,float b ,  float blend ) 
{
    y2 = KGraphicGL::screenHeight - y2 ;
    y1 = KGraphicGL::screenHeight - y1 ;
    
    KGraphicGL::_oldBindedText = -1 ;
    
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

void		KBatchGL::freeBatchBuffer( void )		//only call if you want to free the buffer ( not necessary for most users )
{
}

void		KBatchGL::blitAlphaRectFx( float	x1, float y1 , float	x2 , float y2 , float	destX , float	destY, float angle, float zoom, float blend ,   bool flipx  , bool flipy ,  float centerX , float centerY )  
{
	_texturePtr->blitAlphaRectFx( x1,y1,x2,y2, destX , destY , angle, zoom, blend , flipx, flipy , centerX, centerY ) ;	
}

//blit used for all the function
void KBatchGL::blitAlphaRect(long x1, long y1, long x2, long y2, float destX, float destY,   bool flipx  , bool flipy )  
{
	_texturePtr->blitAlphaRect( x1,y1,x2,y2, destX , destY  , flipx, flipy ) ;	
}

