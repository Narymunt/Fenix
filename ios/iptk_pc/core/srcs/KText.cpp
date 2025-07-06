#include	"KText.h"
#include	<stdio.h>
#include	"KPTK.h"

KText::KText( )
{
	_surf_Fonts = NULL ;
	_fontTable = NULL ;
	_r	 = 1 ;
	_g	 = 1 ;
	_b	 = 1 ;
	_ySpacing = 0 ;
	_spaceAdjustment = 0 ;
	_blendFactor = 1 ;
	_textBatcher = NULL ;
}


KText::KText( const char	 *font_Filename , KFont	*table )
{
	_fontTable 	= NULL ;
	_surf_Fonts 	= NULL ;
	
	_surf_Fonts 	= KPTK::createKGraphic( )  ;
	if ( _surf_Fonts != NULL )
	{
		_surf_Fonts->loadPicture( font_Filename , true, true ) ;
		_fontTable = table ;
	}
	_surf_Fonts->setTextureQuality( false ) ;
	setColor( 1,1,1,1 ) ;
	
	_textBatcher = KPTK::createKBatch() ;

	//allocate for 1024 quads
	_textBatcher->allocateBuffer( 1024 ) ;	
	
	_spaceAdjustment = 0 ;
	_ySpacing = 0 ;
		
	
}

KGraphic	*KText::getKGraphicPtr( void ) 
{
	return	_surf_Fonts ;
}

KText::~KText( )
{
	if ( _surf_Fonts != NULL )
	{
		delete	_surf_Fonts ;
		_surf_Fonts = NULL ;
	}

	if ( _textBatcher != NULL )
	{
		delete	_textBatcher ;
		_textBatcher = NULL ;
	}

	//	_fontTable = NULL ;
}

//set alpha blending for the font
void	KText::setColor( float		r,  float		g, float b ,   float		blendFactor )
{
	_r	 = r ;
	_g	 = g ;
	_b	 = b ;
	_blendFactor = blendFactor ;
}

//attache la table de fonte
void	KText::setFontTable( KFont	*table ) 
{
	_fontTable = table ;
}

//attach the picture
void	KText::setKGraphic( KGraphic	*picPtr ) 
{
	_surf_Fonts = picPtr ;
}

//attache la bitap de fonte
void	KText::loadFontBitmap( char	*font_Filename ) 
{
	if ( _surf_Fonts != NULL )		return ;

	_surf_Fonts 	=  KPTK::createKGraphic( )  ; ;
	if ( _surf_Fonts != NULL )
	{
		_surf_Fonts->loadPicture( font_Filename , true , true ) ;
	}
}


//affiche des numeros
void	KText::drawStringFromLeft( long 	value , long x , long y,float  kerning ) 
{
char	buffer[256] ;

	_snprintf( buffer , 255 , "%d" , value ) ;
	drawStringFromLeft( buffer , x, y, kerning ) ;
}	


//affiche des numeros
void	KText::drawStringFromRight( long 	value , long x , long y,float  kerning ) 
{
char	buffer[256] ;

	_snprintf( buffer , 255 , "%d" , value ) ;
	drawStringFromRight( buffer , x, y, kerning ) ;
}	

void	KText::drawStringCentered( long value , long x1,long x2 , long y , float kerning ) 
{
char	buffer[256] ;

	_snprintf( buffer , 255 , "%d" , value ) ;
	drawStringCentered( buffer , x1, x2,y, kerning ) ;
}
	
//affiche le texte en partant de la gauche
void	KText::drawStringFromLeft( const	char	*txt , long x , long y,float  kerning ) 
{

	if ( _surf_Fonts == NULL )		return ;

long	l , i  , letterindex;
float  realx ;
unsigned char  thechar ;
	
	l = strlen( txt ) ;
	
	//ze string is empty
	if ( l <= 0 )		return  ;
		
	_surf_Fonts->setBlitColor ( _r,_g,_b,_blendFactor ) ;

//	_textBatcher->beginBatch( _surf_Fonts ) ;

	realx = x ;


	for ( i = 0 ; i < l ; i++ )
	{
		thechar = txt[i] ;
	
		letterindex	= getCharIndex( thechar  ) ;
		if ( letterindex < 0 )	
		{
			continue ;
		}
	
	/*		_textBatcher->blitAlphaRect( 	_fontTable[letterindex]._x1 , _fontTable[letterindex]._y1 , 
														_fontTable[letterindex]._x2+1 , _fontTable[letterindex]._y2+1 ,
														realx ,y ) ;
		
	*/
	  _surf_Fonts->blitAlphaRect( 	_fontTable[letterindex]._x1 , _fontTable[letterindex]._y1 , 
														_fontTable[letterindex]._x2+1 , _fontTable[letterindex]._y2+1 ,
														realx ,y ) ;
													
														

		if ( thechar  == ' ' )
		{
			realx += _spaceAdjustment ; 
		}
		realx	+=	((float)_fontTable[letterindex]._w+kerning ) ;
	}

//	_textBatcher->endBatch(  ) ;

}

void	KText::drawNCharFromLeft( char	*txt , long nchar , long x , long y,float  kerning ) 
{

	if ( _surf_Fonts == NULL )		return ;

long	l , i  , letterindex;
	
	l = strlen( txt ) ;
	
	//ze string is empty
	if ( l <= 0 )		return  ;
		
	_surf_Fonts->setBlitColor ( _r,_g,_b,_blendFactor ) ;

	_textBatcher->beginBatch( _surf_Fonts ) ;

	
	for ( i = 0 ; i < nchar ; i++ )
	{
		letterindex	= getCharIndex( txt[i] ) ;
		if ( letterindex < 0 )		
		{		
			continue ;
		}
		
		_textBatcher->blitAlphaRect( 	_fontTable[letterindex]._x1 , _fontTable[letterindex]._y1 , 
													_fontTable[letterindex]._x2 , _fontTable[letterindex]._y2 ,
													x ,y ) ;

		x	+=	(_fontTable[letterindex]._w+kerning ) ;
	}
	_textBatcher->endBatch(  ) ;

	
}

//affiche le texte en partant de la droite
void	KText::drawStringFromRight( const	char	*txt , long x , long y, float kerning   ) 
{
	if ( _surf_Fonts == NULL )		return ;

long	l , i  , letterindex;
	float  realx ;
	
	l = strlen( txt ) ;
	
	//ze string is empty
	if ( l <= 0 )		return  ;

	_surf_Fonts->setBlitColor ( _r,_g,_b,_blendFactor ) ;
	
	realx = x ;

	for ( i = (l-1) ; i >= 0 ; i-- )
	{
		letterindex	= getCharIndex( txt[i] ) ;
		if ( letterindex < 0 )		continue ;
		
		realx	-=	((float)_fontTable[letterindex]._w+kerning )  ;


		_surf_Fonts->blitAlphaRect( 	_fontTable[letterindex]._x1 , _fontTable[letterindex]._y1 , 
													_fontTable[letterindex]._x2+1 , _fontTable[letterindex]._y2+1 ,
													realx ,y ) ;

	}
	

}

//texte centré
void	KText::drawStringCentered( const	char	*txt , long x1,long x2 , long y , float kerning ) 
{
float		largeur ;
long		rx ;
	
	if ( _surf_Fonts == NULL )		return ;
	if ( txt == NULL )					return ;
	if ( _fontTable 	== NULL )		return ;
	
	largeur = getStringWidth( txt , kerning ) ;
	if ( largeur<= 0 )		return ;
	rx = x1+((( x2-x1)- largeur )/2 ) ;

	drawStringFromLeft( txt , rx , y , kerning ) ;
	
}


 void	KText::setSpaceAdjustment( float pixels ) 
 {
 	 _spaceAdjustment = pixels ;
 }


//largeur d'une string
float	KText::getStringWidth( const	char	*txt , float kerning ) 
{
	if ( _surf_Fonts == NULL )		return -1;
	if ( txt == NULL )					return -1;
	if ( _fontTable 	== NULL )		return -1;
	
long	l , i  , ci ;
float  largeur;
unsigned char  thechar ;
	
	l = strlen( txt ) ;
	
	if ( l <= 0 )		return -1 ;
	
	largeur = 0 ;
	
	for ( i = 0 ; i < l ; i++ )
	{
		thechar = txt[i] ;
	
		
		ci = getCharIndex(thechar ) ;
		if ( ci >= 0 )
		{
			largeur += ((float)_fontTable[ci]._w+kerning) ;
			
		}
	}
	
	return  largeur ;
}


//largeur d'une string  with n chars
float  KText::getNCharWidth (const char *txt, long charcount , float  kerning) 
{
	if ( _surf_Fonts == NULL )		return -1;
	if ( txt == NULL )					return -1;
	if ( _fontTable 	== NULL )		return -1;
	
long	l , i  , ci ;
float  largeur;
	
	l = strlen( txt ) ;
	
	if ( charcount <= 0 )		return -1 ;
	if ( charcount >= l )
	{
			charcount = l ;
	}

	largeur = 0 ;
	
	for ( i = 0 ; i < charcount ; i++ )
	{
		ci = getCharIndex( txt[i] ) ;
		if ( ci >= 0 )
		{
			largeur += ((float)_fontTable[ci]._w+kerning) ;
		}
	}
	
	return  largeur ;
}

//index de la lettre dans la table
long		KText::getCharIndex( char	c ) 
{
long	i ;	
char	cs ;

	if ( _surf_Fonts 	== NULL )		return -1;
	if ( _fontTable 	== NULL )		return -1;

	i = 0 ; 
	do
	{
		cs = _fontTable[i]._c ;

		if ( cs == '\0' 	)	return -1 ;		//end of table
		if ( cs == c	)	return i ;		//end of table
		
		i++ ;
	}while( true )  ;

	return -1 ;
}



void		KText::setYSpacing( float yspacing ) 
{
	_ySpacing = yspacing ;
}


long		KText::drawMultiline( const char *myText , long x1, long x2 , long y, long textstyle , float kerning  ) 
{
long		matchwidth ;

sStringInfo	strInfo ;
char		tmpBuffer[4096] ;
char		tmpString[512] ;
bool		result ;
long		charcount ;
float		fontheight ;


	if ( myText == NULL )		return  y ;
	if ( strcmp( myText , "" ) == 0 )		return y ;
	
	if ( _fontTable == NULL )	return y;

	fontheight = _fontTable[0]._h ;
	
	if ( textstyle == TEXTSTYLE_JUSTIFIED )
	{
		return drawJustifiedMultilineText( myText , x1, x2 , y ,  kerning ) ; 
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
		
			y+=(long)( fontheight+_ySpacing ) ;
		
		}
			strInfo.startpos = strInfo.endpos ;
			//in case the last break was on a space, move on to the next real character 
			if ( true == movePosToNextChar( tmpBuffer , &strInfo ) )
			{
				//we reached the end of the string
				break ;
			}
			
			
	}while( result == false  ) ;
	
	return y ;
}


long		KText::drawJustifiedMultilineText( const char *myText , long x1, long x2 , long y , float kerning ) 
{
long		matchwidth ;

sStringInfo	strInfo ;
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
	
	if ( _fontTable == NULL )	return y;
	if ( myText == NULL )		return y ;
	if ( strcmp( myText , "" ) == 0 )		return y ;

	memset( tmpBuffer, 0 , 4096 ) ;
	
	strcpy( tmpBuffer, myText ) ;
	
	matchwidth = x2-x1 ;
	
	
	strInfo.startpos = 0 ;
	fontheight = _fontTable[0]._h  ;

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
			if ( strInfo.leftAlign == false )
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

//returns the number of spaces in the string
long		KText::getSpaceCount( char *textPtr ) 
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

bool			KText::movePosToNextChar( char *tmpBuffer ,  sStringInfo  *strInfo ) 
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
 bool		KText::findStringMatchWidth(  char *buffer , long  matchwidth ,  sStringInfo  *strinfoptr , float kerning ) 
 {
 long		strw ;
 long		i , j , stringlen ;
 
 		i = strinfoptr->startpos ;
 		j = 1 ;
 
 		stringlen  = strlen( buffer+strinfoptr->startpos ) ;
 		if ( j >= stringlen )		return true ;
 		 
 		strinfoptr->leftAlign = false ;
 		 
 		do
 		{
 			if( buffer[strinfoptr->startpos+j] == '\n' )
 			{
 				//carriage return
 				buffer[strinfoptr->startpos+j] = ' ' ;
 				strw = matchwidth+1 ;
 				strinfoptr->leftAlign = true ;
 				j++;
 			}
 			else
 			{
 				j++;
 						
				strw = getNCharWidth( buffer+strinfoptr->startpos , j , kerning );
 			}
 			
 			
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
 