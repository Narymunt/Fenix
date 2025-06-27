/******************************************************************************
 * PTK truetype text rendering class implementation
 ******************************************************************************
 * Rock And Roll (c) 2005 FunPause and Phelios Inc.
 ******************************************************************************
 * $Id: KTrueText.cpp,v 1.6 2005/06/02 16:01:41 emarty Exp $
 ******************************************************************************
 */

#define _BUILDING_KTRUETYPE

#define		TEXTSTYLE_LEFT			0
#define		TEXTSTYLE_RIGHT		1
#define		TEXTSTYLE_CENTER	2
#define		TEXTSTYLE_JUSTIFIED	3

#define		PADDINGFONT		2

#include "KTrueText.h"

/**** PUBLIC ****/

/**
 * Constructor
 *
 * \param font_Filename name of truetype font to load
 */

KTrueText::KTrueText (const char *font_Filename) :
	_spaceAdjustment( 0 ) ,
      _lpFtStream (NULL),
      _lpFreeTypeFace (NULL),
      _lpFontGraphics (NULL),
      _nTextR (1),
      _nTextG (1),
      _nTextB (1),
      _ySpacing( 0 ) ,
      _fBlendFactor (1.0) {
   if (!_lpFreeTypeLib) {
      FT_Error error;

      /* Initialize FreeType */
      error = FT_Init_FreeType (&_lpFreeTypeLib);
   }

   /* Allocate memory for FreeType stream */
   _lpFtStream = (FT_Stream) malloc (sizeof (*_lpFtStream));

   /* Load specified font */
   loadFontFile ((char*)font_Filename);
   setHeightPix( 14 ) ;
}

/** Destructor */

KTrueText::~KTrueText () {
   if (_lpFontGraphics) {
      /* Free font texture */
      delete _lpFontGraphics;
      _lpFontGraphics = NULL;
   }

   if (_lpFreeTypeFace) {
      /* Free font face data */
      FT_Done_Face (_lpFreeTypeFace);
      _lpFreeTypeFace = NULL;
   }

   if (_lpFtStream) {
      /* Free stream */
      free (_lpFtStream);
      _lpFtStream = NULL;
   }
}

/**
 * Load a font file
 *
 * \param font_Filename name of file to be loaded
 */

void KTrueText::loadFontFile (char *font_Filename) {
   FT_Error error;

   /* Check that a font isn't already loaded */
   if (_lpFreeTypeFace) {
      FT_Done_Face (_lpFreeTypeFace);
      _lpFreeTypeFace = NULL;
   }

   /* Open font face */
   error = FT_New_Face (_lpFreeTypeLib, font_Filename, 0,
                        &_lpFreeTypeFace);
   if (error != FT_Err_Ok) {
      if (_lpFreeTypeFace) {
         FT_Done_Face (_lpFreeTypeFace);
         _lpFreeTypeFace = NULL;
      }
   }
}

/**
 * Draw a string from coordinates of top, left
 *
 * \param txt text to be drawn
 * \param x X coordinate of top, left of text
 * \param y Y coordinate of top, left of text
 * \param kering horizontal space between chars, in pixels
 */

void KTrueText::drawStringFromLeft ( const char *txt, long x, long y,   float  kerning)
 {
    float	realx ;
   size_t i, nLen = strlen (txt);

	realx = x ;

   /* Don't do anything if no font is loaded */
   if (!_lpFreeTypeFace) return;

   if (_lpFontGraphics == NULL ) {
      /* No texture for font yet; render one */
      render ();
   }
   if ( _lpFontGraphics->_usedForTTF == 2 ) {
      /* No texture for font yet; render one */
      render ();
   }
   for (i = 0; i < nLen; i++) {
      unsigned int c = (unsigned int) ((unsigned char) txt[i]);

      if (c >= 32) {
         struct KTrueTextChar *lpChar = &_char[c-32];

         _lpFontGraphics->blitAlphaRectFx (lpChar->fX, lpChar->fY,    lpChar->fX + lpChar->fWidth, lpChar->fY + lpChar->fHeight,
         												             realx + lpChar->nXOffset, 
         												             (short) y + lpChar->nYOffset,
             0, 1.0, _fBlendFactor,
             false, false);
             if ( c == 32 )
             {
        		 realx += (lpChar->nXAdvance + kerning)+_spaceAdjustment;
      		}
      		else
      		{
       		 realx += (lpChar->nXAdvance + kerning);
      		}
      }
   }
}

/**
 * Draw a string from coordinates of top, right
 *
 * \param txt text to be drawn
 * \param x X coordinate of top, right of text
 * \param y Y coordinate of top, right of text
 * \param kerning extra horizontal space between chars, in pixels
 */

void KTrueText::drawStringFromRight (const char *txt, long x, long y,   float kerning)
 {
   size_t i, nLen = strlen (txt);
	float  realx ;
	
	realx = x ;
	
   /* Don't do anything if no font is loaded */
   if (!_lpFreeTypeFace) return;

   if (!_lpFontGraphics) {
      /* No texture for font yet; render one */
      render ();
   }

   for (i = nLen; i; i--) {
      unsigned int c = (unsigned int) ((unsigned char) txt[i-1]);

      if (c >= 32) {
         struct KTrueTextChar *lpChar = &_char[c-32];

         realx -= lpChar->nXAdvance;
         if (i < nLen) realx -= kerning;

         _lpFontGraphics->blitAlphaRectFx( lpChar->fX, lpChar->fY,   lpChar->fX + lpChar->fWidth, lpChar->fY + lpChar->fHeight,
             							     (short) realx + lpChar->nXOffset, 
             							     (short) y + lpChar->nYOffset,
             
             							0, 1.0, _fBlendFactor,
             false, false);
             
      }
   }
}

/**
 * Draw a centered string
 *
 * \param txt text to be drawn
 * \param x1 X coordinate of left of box to center text in
 * \param x2 X coordinate of right of box to center text in
 * \param y Y coordinate of top of text
 * \param kerning extra horizontal space between chars, in pixels
 */

void KTrueText::drawStringCentered (const char *txt, long x1, long x2, long y, float kerning) {
   float nWidth = getStringWidth (txt, kerning);
   long x = x1 + ((x2 - x1) - nWidth) / 2;

   drawStringFromLeft (txt, x, y, kerning);
}

/**
 * Get width of specified text in pixels, using loaded font
 *
 * \param txt text to get width of
 * \param kerning extra horizontal space between chars, in pixels
 *
 * \return width in pixels
 */    

float  KTrueText::getStringWidth (const char *txt, float  kerning) 
{

   /* No font face read */
   if (!_lpFreeTypeFace) return 0;

   FT_GlyphSlot lpSlot = _lpFreeTypeFace->glyph;
   float  nDrawXPos;
   size_t i;
      KTrueTextChar *lpChar ;
      
      if (!_lpFreeTypeFace) return 0 ;

   if (_lpFontGraphics == NULL ) {
      /* No texture for font yet; render one */
      render ();
   }
   long strsize ;
   
   if ( txt == NULL )		return 0;
   strsize = strlen ( txt ) ;
   if ( strsize <= 0 )		return 0;
   
   nDrawXPos = 0 ;
    unsigned char c ;
    
   for ( i = 0;  i < strsize; i++) 
        {
        		c = txt[i] ;
   			lpChar = &_char[c-32];
   
   			nDrawXPos += lpChar->nXAdvance ;
         		nDrawXPos += kerning;
   }

   return nDrawXPos;
}



 void	KTrueText::setSpaceAdjustment( float pixels ) 
 {
 	 _spaceAdjustment = pixels ;
 }

float  KTrueText::getNCharWidth (char *txt, long charcount , float  kerning) 
{
	long strsize ;

   /* No font face read */
   if (!_lpFreeTypeFace) return 0;

   FT_GlyphSlot lpSlot = _lpFreeTypeFace->glyph;
   float  nDrawXPos;
   size_t i;
   KTrueTextChar *lpChar ;
   unsigned char		c ;
   
   if (!_lpFreeTypeFace) return 0 ;

   if (_lpFontGraphics == NULL ) {
      /* No texture for font yet; render one */
      render ();
   }

/*    if (c >= 32) {
         struct KTrueTextChar *lpChar = &_char[c-32];

         _lpFontGraphics->blitAlphaRectFx
            (lpChar->fX, lpChar->fY,
             lpChar->fX + lpChar->fWidth, lpChar->fY + lpChar->fHeight,
             (short) x + lpChar->nXOffset, (short) y + lpChar->nYOffset,
             0, 1.0, _fBlendFactor,
             false, false);
         x += (lpChar->nXAdvance + kerning);
      }
   */
   strsize = strlen( txt ) ;
   
   if ( charcount >strsize )
   {
   		charcount = strsize ;
   }
    
   nDrawXPos = 0 ;
    
   for ( i = 0;  i < charcount; i++) 
        {
        		c = txt[i] ;
   			lpChar = &_char[c-32];
   
   			nDrawXPos += lpChar->nXAdvance ;
         		nDrawXPos += kerning;
   }

   return nDrawXPos;
}


/**
 * Get this font's height in pixels, independently of how
 * it was set (points or pixels)
 *
 * \return height in pixels
 */

long KTrueText::getHeightPix (void) {
   if (_lpFreeTypeFace) {
      return _lpFreeTypeFace->size->metrics.height >> 6;
   }
   else
      return 0;
}

/**
 * Set this font's height in pixels
 *
 * \param nPixHeight font height in pixels
 */

void KTrueText::setHeightPix (long nHeightPix) {
   if (_lpFreeTypeFace) {
      long nPrevHeightPix;
      FT_Error error;

      nPrevHeightPix = getHeightPix ();
      error = FT_Set_Pixel_Sizes (_lpFreeTypeFace, 0, nHeightPix);

      if ((getHeightPix() != nPrevHeightPix) && (_lpFontGraphics)) {
         /* Rerender next time we draw text */
         delete _lpFontGraphics;
         _lpFontGraphics = NULL;
      }
   }
}

/**
 * Set this font's height in points
 *
 * \param nPtHeight font size in points for 96 dpp
 */

void KTrueText::setHeightPt (long nHeightPt) 
{
   if (_lpFreeTypeFace) {
      long nPrevHeightPix;
      FT_Error error;

      nPrevHeightPix = getHeightPix ();
      error = FT_Set_Char_Size (_lpFreeTypeFace, 0, nHeightPt * 64,
                                96, 96);

      if ((getHeightPix() != nPrevHeightPix) && (_lpFontGraphics)) {
         /* Rerender next time we draw text */
         delete _lpFontGraphics;
         _lpFontGraphics = NULL;
      }
   }
}

/**
 * Set text color
 *
 * \param r red component (0-255)
 * \param g red component (0-255)
 * \param b red component (0-255)
 */

void KTrueText::setColor (float r, float g,float  b , float alpha ) 
{
      _nTextR = r;
      _nTextG = g;
      _nTextB = b;
      
         /* Don't do anything if no font is loaded */
   if (_lpFontGraphics == NULL) 
   {
   	   render ();
//	   if (!_lpFreeTypeFace) 	return ;
   }


      if (_lpFontGraphics) 
      {
	      _lpFontGraphics->setBlitColor( _nTextR ,_nTextG, _nTextB , alpha ) ;      
      }
   
}





/**** PRIVATE ****/

/**
 * Render current font and size to a texture
 */

void KTrueText::render (void) {
   FT_GlyphSlot lpSlot;
   float fX, fY, fMaxWidth;
   int i, nBaseline, nTexWidth, nTexHeight, nMaxRowHeight;
   unsigned char *lpTexBuf;
   bool bSuccess;

   /* Don't do anything if no font is loaded */
   if (!_lpFreeTypeFace) return;

   /* Free existing texture if any */
   if (_lpFontGraphics) {
      /* Free font texture */
      delete _lpFontGraphics;
      _lpFontGraphics = NULL;
   }

   if (!getHeightPix ()) {
      FT_Error error;

      /* Set default height of 12pt */
      error = FT_Set_Char_Size (_lpFreeTypeFace, 0, 12 * 64,   96, 96);
   }

   /* First pass: map characters to texture coordinates */

   lpSlot = _lpFreeTypeFace->glyph;
   fX = 0; 
   fY = 0; 
   nTexWidth = 0; 
   nMaxRowHeight = 0;
   nBaseline = _lpFreeTypeFace->size->metrics.ascender >> 6;

   if (getHeightPix () < 20)
   {
      fMaxWidth = 256.0;
   }
   else
   {
      fMaxWidth = 512.0;
	}
	
	//clear the coordinnate table
   memset (&_char, 0, sizeof (_char));

   for (i = 32; i < 256; i++) 
   {
      FT_Error error;
      struct KTrueTextChar *lpChar = &_char[i-32];

      /* Render char to get its size */
      error = FT_Load_Char (_lpFreeTypeFace, i, FT_LOAD_RENDER);
      
      if (!error) 
      {
         if ((fX + (float) lpSlot->bitmap.width) > fMaxWidth)
          {
	
	            if (((int) fX) > nTexWidth)
	            {
               		nTexWidth = (int) fX ;
                 }

            fX = 0.0;
            fY += (float) nMaxRowHeight+PADDINGFONT;
         }

         /* Store location */
         lpChar->fX = fX;
         lpChar->fY = fY;
         lpChar->fWidth = (float) lpSlot->bitmap.width ;
         lpChar->fHeight = (float) lpSlot->bitmap.rows ;
         lpChar->nXOffset = lpSlot->bitmap_left;
         lpChar->nYOffset = nBaseline - lpSlot->bitmap_top;
         lpChar->nXAdvance = lpSlot->advance.x >> 6;

         if (lpSlot->bitmap.rows > nMaxRowHeight)
         {
            nMaxRowHeight = lpSlot->bitmap.rows;
          }

         fX += (float) lpSlot->bitmap.width+PADDINGFONT;
      }
   }
   nTexHeight = (int) fY + nMaxRowHeight;

   /* Allocate buffer for rendering chars as 32-bit RGBA */
   lpTexBuf = new unsigned char [nTexWidth * nTexHeight * 4];
   memset (lpTexBuf, 0, nTexWidth * nTexHeight * 4);

   /* Second pass: render characters to pixel buffer */

   lpSlot = _lpFreeTypeFace->glyph;
   nBaseline = _lpFreeTypeFace->size->metrics.ascender >> 6;

   for (i = 32; i < 256; i++)  {
      FT_Error error;
      struct KTrueTextChar *lpChar = &_char[i-32];

      /* Render char to slot */
      error = FT_Load_Char (_lpFreeTypeFace, i, FT_LOAD_RENDER);
      if (!error) {
         unsigned char *lpDstBuf, *lpSrcBuf;
         int x, y, nDstStride;
         unsigned char nR = 255;
         unsigned char nG = 255;
         unsigned char nB = 255 ;

         /* Transfer char to texture buffer */

         nDstStride  = (4 * nTexWidth);
         lpDstBuf    = lpTexBuf + ((int) lpChar->fY) * nDstStride;
         lpDstBuf   += (4 * (int) lpChar->fX);
         nDstStride -= (4 * lpSlot->bitmap.width);
         lpSrcBuf    = lpSlot->bitmap.buffer;

  //     	if ( KPTK::_renderer == K_GDI )
  //     	{
	 //        for (y = 0; y < lpSlot->bitmap.rows; y++) 
	 //        {
	 //           for (x = 0; x < lpSlot->bitmap.width; x++) 
	 //           {
	 //             	 *lpDstBuf++ = *lpSrcBuf;
	 //             	 *lpDstBuf++ = *lpSrcBuf;
	 //             	 *lpDstBuf++ = *lpSrcBuf;
	 //             	 *lpDstBuf++ = *lpSrcBuf++;  	
  //          		}
  //          		  lpDstBuf += nDstStride;
		//	}
		//}
		//else
		{
		     for (y = 0; y < lpSlot->bitmap.rows; y++) 
	         {
	            for (x = 0; x < lpSlot->bitmap.width; x++) 
	            {
	              	 *lpDstBuf++ =nR;
	              	 *lpDstBuf++ = nG;
	              	 *lpDstBuf++ = nB;
	              	 *lpDstBuf++ = *lpSrcBuf++;  	
            		}
            		  lpDstBuf += nDstStride;
			}	
		}
						
          
         }
      }
      


   /* Create texture from buffer */
	if ( _lpFontGraphics != NULL ) 
	{
		delete _lpFontGraphics ;
		_lpFontGraphics = NULL 	;	
	}
	
   _lpFontGraphics = KPTK::createKGraphic ();
   _lpFontGraphics->setTextureQuality( true ) ;
   _lpFontGraphics->_usedForTTF = 1 ;
   bSuccess = _lpFontGraphics->makePictureFromArray ((unsigned long *) lpTexBuf,  nTexWidth, nTexHeight, true);
   _lpFontGraphics->setTextureQuality( true ) ;
   _lpFontGraphics->_usedForTTF = 1 ;

   /* The buffer is not required anymore */
   delete lpTexBuf;
}

/** Global instance of FreeType library */
FT_Library KTrueText::_lpFreeTypeLib;








KGraphic	*KTrueText::getKGraphicPtr( void ) 
{
	if ( _lpFontGraphics == NULL )		render( ) ;
	return _lpFontGraphics ;

}

long		KTrueText::getMultilineHeight( const char *myText , long x1, long x2 , long textstyle , float kerning  ) 
{

long		matchwidth ;

sStringInfoKtt	strInfo ;
char		tmpBuffer[4096] ;
char		tmpString[512] ;
bool		result ;
long		charcount ;
float		fontheight ;

long	 y ;
	y = 0 ;
	if ( myText == NULL )		return y ;
	if ( strcmp( myText , "" ) == 0 )		return y ;
	
	fontheight = getHeightPix( ) ;
	
	if ( textstyle == TEXTSTYLE_JUSTIFIED )
	{
		return getJustifiedMultilineTextHeight( myText , x1, x2 , y ,  kerning ) ; 
	}
	
	memset( tmpBuffer, 0 , 4096 ) ;
	
	strcpy( tmpBuffer, myText ) ;
	
	matchwidth = x2-x1 ;
	
	
	strInfo.startpos = 0 ;
	setSpaceAdjustment( 0 ) ;

	do
	{
	
		result = 	findStringMatchWidth( (char*)tmpBuffer  , matchwidth , &strInfo , kerning ) ;
		
		memset( tmpString, 0 , 512 ) ;
		charcount = strInfo.endpos-strInfo.startpos ;
		
		if ( charcount > 0 )
		{
		
			strncpy( tmpString , tmpBuffer+strInfo.startpos ,charcount) ;

			y+=( fontheight+_ySpacing ) ;
		
		}
			strInfo.startpos = strInfo.endpos ;
			//in case the last break was on a space, move on to the next real character 
			if ( true == movePosToNextChar( tmpBuffer , &strInfo ) )
			{
				//we reached the end of the string
				break ;
			}
			
			
	}while( result == false  ) ;
	
	return y;
}



long		KTrueText::drawMultiline( const char *myText , long x1, long x2 , long y, long textstyle , float kerning  ) 
{
long		matchwidth ;

sStringInfoKtt	strInfo ;
char		tmpBuffer[4096] ;
char		tmpString[512] ;
bool		result ;
long		charcount ;
float		fontheight ;


	if ( myText == NULL )		return y ;
	if ( strcmp( myText , "" ) == 0 )		return y ;
	
	fontheight = getHeightPix( ) ;
	
	if ( textstyle == TEXTSTYLE_JUSTIFIED )
	{
		return  drawJustifiedMultilineText( myText , x1, x2 , y ,  kerning ) ; 
	}
	
	memset( tmpBuffer, 0 , 4096 ) ;
	
	strcpy( tmpBuffer, myText ) ;
	
	matchwidth = x2-x1 ;
	
	
	strInfo.startpos = 0 ;
	setSpaceAdjustment( 0 ) ;

	do
	{
	
		result = 	findStringMatchWidth( (char*)tmpBuffer  , matchwidth , &strInfo , kerning ) ;
		
		memset( tmpString, 0 , 512 ) ;
		charcount = strInfo.endpos-strInfo.startpos ;
		
		if ( charcount > 0 )
		{
		
			strncpy( tmpString , tmpBuffer+strInfo.startpos ,charcount) ;

			switch( textstyle )
			{
				case TEXTSTYLE_LEFT:
					drawStringFromLeft( tmpString , x1 , y , kerning  ) ;
				break ;
				case TEXTSTYLE_RIGHT:
					drawStringFromRight( tmpString , x2 , y , kerning  ) ;
				break ;
				case TEXTSTYLE_CENTER:
					drawStringCentered( tmpString ,x1, x2 , y , kerning  ) ;
				break ;
			}
		
			y+=( fontheight+_ySpacing ) ;
		
		}
			strInfo.startpos = strInfo.endpos ;
			//in case the last break was on a space, move on to the next real character 
			if ( true == movePosToNextChar( tmpBuffer , &strInfo ) )
			{
				//we reached the end of the string
				break ;
			}
			
			
	}while( result == false  ) ;
	
	return y;
	
}

//returns the number of spaces in the string
long		KTrueText::getSpaceCount( char *textPtr ) 
{
long i , c, l ;

	l = strlen( textPtr ) ;
	
	if ( l <= 0 )	return 0 ;
	
	c = 0 ;
	for ( i = 0 ; i < l ; i++ )
	{
		if ( textPtr[i] == ' ' )		c++ ;
	}

	return c ;
}

void		KTrueText::setYSpacing( float yspacing ) 
{
	_ySpacing = yspacing ;
}


long		KTrueText::getJustifiedMultilineTextHeight( const char *myText , long x1, long x2 , long y , float kerning ) 
{

long		matchwidth ;

sStringInfoKtt	strInfo ;
char		tmpBuffer[4096] ;
char		tmpString[512] ;
bool		result ;
long		charcount ;
float		strwidth ;
float		spaceCount ;		//the number of spaces in the string
float		spaceadjust ;
float		requiredWidth ;
float		fontheight ;




	requiredWidth = x2 - x1 ;
	

	if ( myText == NULL )		return y  ;
	if ( strcmp( myText , "" ) == 0 )		return y ;

	memset( tmpBuffer, 0 , 4096 ) ;
	
	strcpy( tmpBuffer, myText ) ;
	
	matchwidth = x2-x1 ;
	
	
	strInfo.startpos = 0 ;
	fontheight = getHeightPix( ) ;

	do
	{

		result = 	findStringMatchWidth( (char*)tmpBuffer  , matchwidth , &strInfo , kerning ) ;
		
		memset( tmpString, 0 , 512 ) ;
		charcount = strInfo.endpos-strInfo.startpos ;
		
		if ( charcount > 0 )
		{
			strncpy( tmpString , tmpBuffer+strInfo.startpos ,charcount) ;
			spaceCount = getSpaceCount( tmpString ) ;
			strwidth = 	getStringWidth ( tmpString , kerning) ;
			if ( spaceCount >= 0  )
			{
				spaceadjust = (requiredWidth-strwidth) / spaceCount ;
			}
			if ( result == true )
			{
				//we reached the last line, no justification.
				spaceadjust = 0 ;
			} 
			
			if ( strInfo.leftalign == false )
			{
				setSpaceAdjustment( spaceadjust ) ;
			}
			else
			{
				setSpaceAdjustment( 0 ) ;
			}	

		//	drawStringFromLeft( tmpString , x1 , y , kerning  ) ;
			y+= (fontheight +  _ySpacing ) ;
		
		}
			strInfo.startpos = strInfo.endpos ;
			//in case the last break was on a space, move on to the next real character 
			if ( true 	== movePosToNextChar( tmpBuffer , &strInfo ) )
			{
				//we reached the end of the string
				break ;
			}
			
			
	}while( result == false  ) ;
	
	return y ;

}

long		KTrueText::drawJustifiedMultilineText( const char *myText , long x1, long x2 , long y , float kerning ) 
{
long		matchwidth ;

sStringInfoKtt	strInfo ;
char		tmpBuffer[4096] ;
char		tmpString[512] ;
bool		result ;
long		charcount ;
float		strwidth ;
float		spaceCount ;		//the number of spaces in the string
float		spaceadjust ;
float		requiredWidth ;
float		fontheight ;




	requiredWidth = x2 - x1 ;
	

	if ( myText == NULL )		return y  ;
	if ( strcmp( myText , "" ) == 0 )		return y ;

	memset( tmpBuffer, 0 , 4096 ) ;
	
	strcpy( tmpBuffer, myText ) ;
	
	matchwidth = x2-x1 ;
	
	
	strInfo.startpos = 0 ;
	fontheight = getHeightPix( ) ;

	do
	{

		result = 	findStringMatchWidth( (char*)tmpBuffer  , matchwidth , &strInfo , kerning ) ;
		
		memset( tmpString, 0 , 512 ) ;
		charcount = strInfo.endpos-strInfo.startpos ;
		
		if ( charcount > 0 )
		{
			strncpy( tmpString , tmpBuffer+strInfo.startpos ,charcount) ;
			spaceCount = getSpaceCount( tmpString ) ;
			strwidth = 	getStringWidth ( tmpString , kerning) ;
			if ( spaceCount >= 0  )
			{
				spaceadjust = (requiredWidth-strwidth) / spaceCount ;
			}
			if ( result == true )
			{
				//we reached the last line, no justification.
				spaceadjust = 0 ;
			} 
			
			if ( strInfo.leftalign == false )
			{
				setSpaceAdjustment( spaceadjust ) ;
			}
			else
			{
				setSpaceAdjustment( 0 ) ;
			}	

			drawStringFromLeft( tmpString , x1 , y , kerning  ) ;
			y+= (fontheight +  _ySpacing ) ;
		
		}
			strInfo.startpos = strInfo.endpos ;
			//in case the last break was on a space, move on to the next real character 
			if ( true 	== movePosToNextChar( tmpBuffer , &strInfo ) )
			{
				//we reached the end of the string
				break ;
			}
			
			
	}while( result == false  ) ;
	
	return y ;
}


bool			KTrueText::movePosToNextChar( char *tmpBuffer ,  sStringInfoKtt  *strInfo ) 
{
long lenstring, x ;

		lenstring = strlen( tmpBuffer ) ;
		
		x = strInfo->startpos ;
		if ( x >= lenstring ) return true;
		
		while( tmpBuffer[strInfo->startpos] == ' ' )
		{
			strInfo->startpos++ ;
		}
		

		return false ;
}



//returns true if the text ended
 bool		KTrueText::findStringMatchWidth(  char *buffer , long  matchwidth ,  sStringInfoKtt  *strinfoptr , float kerning ) 
 {
 long		strw ;
 long		i , j , stringlen ;
 
 		i = strinfoptr->startpos ;
 		j = 1 ;
 
 		stringlen  = strlen( buffer+strinfoptr->startpos ) ;
 		if ( j >= stringlen )		return true ;
 		 
 		strinfoptr->leftalign = false ;
 		
 		do
 		{
			if( buffer[strinfoptr->startpos+j] == '\n' )
 			{
 				//carriage return
 				buffer[strinfoptr->startpos+j] = ' ' ;
 				strw = matchwidth+1 ;
 				strinfoptr->leftalign = true ;
 				j++;
 			}
 			else
 			{
 				j++;
 						
				strw = getNCharWidth( buffer+strinfoptr->startpos , j , kerning );
 			}
 			
 				
			strw = getNCharWidth( buffer+strinfoptr->startpos , j , kerning );
 			
			//reached end of string
			if ( j >= stringlen )		
			{
				j = stringlen ;
				strinfoptr->endpos = strinfoptr->startpos+j ;
				//true == end of text
				return true ;		
				
			}
			
			//we have a matching width
			if ( strw >= matchwidth )		
			{	
				j-- ;
				break ;
			}
			
 		}while( true ) ;
 
 		strinfoptr->endpos = strinfoptr->startpos+j ;
 		
 	//startpos and endpos are the maximum width allowed, we need to go back in the string to find a space or character
 	long  poxs ;
	poxs = strinfoptr->endpos  ;
 	
 	do
 	{
 			switch( buffer[poxs] )
 			{
 				case ' ':
 					//we found a space, break the string here
 					strinfoptr->endpos = poxs ;
 				 	return false ;
 				break ;
 			}
 			poxs-- ;
 	}while( poxs > strinfoptr->startpos ) ;
 	
 	return false ;
 }
 
 
 