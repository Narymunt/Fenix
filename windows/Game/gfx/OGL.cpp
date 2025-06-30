/**
   OGL.cpp

   Podstawowe funkcje do obs³ugi openGL

   @author Jaros³aw N. Ro¿yñski
   @version 2014-09-04
   
*/

#include "OGL.h"
#include <SDL_error.h>

#define OGL_MAX(a, b) (a) < (b) ? (b) : (a)	
#define OGL_MIN(a, b) (a) > (b) ? (b) : (a)	

#define OGL_UNKNOWN 0

// openGL texture
static SDL_Surface* SCREEN = NULL;

// Compares two SDL_PixelFormat structures, only works with RGBA or RGB surfaces and disregards everything but the color masks 

/**
   Porównanie dwóch formatów SDL_PixelFormat, dzia³a tylko na RGBA i RGB.

   @param a pierwszy surface
   @param b drugi surface

   @return -1 je¿eli ró¿ne surface, 1 je¿eli takie same, 0 je¿eli surface jest pusty
*/

int oglCompareFormat(SDL_PixelFormat* a, SDL_PixelFormat* b)
{
	if(a->BytesPerPixel == b->BytesPerPixel)
	{
		if(a->BytesPerPixel == 3)
		{
			if(a->Rmask == b->Rmask && a->Gmask == b->Gmask && a->Bmask == b->Bmask)
				return 1;			
		}
		else
		{
			if (a->Rmask == b->Rmask &&	a->Gmask == b->Gmask &&	a->Bmask == b->Bmask &&	a->Amask == b->Amask )
				return 1;		
		}
	}
	else
	{
		return -1; // BytesPerPixel differs
	}
	return 0;
}


/**
   Zwraca SDL_PixelFormat w³aœciwy dla tego komputera.

   @param glFormat zapytanie o format

   @return w³aœciwy format pixela
*/

SDL_PixelFormat oglGetPixelFormat(GLenum glFormat)
{
	SDL_PixelFormat format;
	if(glFormat == GL_RGBA)
	{
		format.BytesPerPixel = 4;
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
		format.Rmask = 0xff000000;
		format.Gmask = 0x00ff0000;
		format.Bmask = 0x0000ff00;
		format.Amask = 0x000000ff;
#else	
		format.Rmask = 0x000000ff; 
		format.Gmask = 0x0000ff00;
		format.Bmask = 0x00ff0000;
		format.Amask = 0xff000000;
#endif
	}
	else
	{
		format.BytesPerPixel = 3;

#if SDL_BYTEORDER == SDL_BIG_ENDIAN
		format.Rmask = 0xff0000;
		format.Gmask = 0x00ff00;
		format.Bmask = 0x0000ff;
#else
		format.Rmask = 0x0000ff;
		format.Gmask = 0x00ff00;
		format.Bmask = 0xff0000;
#endif
		format.Amask = 0;
	}
	
	return format;
}

/**
   Inicjalizacja opengl z podanymi flagami.

   @param iScreenX rozmiar X ekranu
   @param iScreenY rozmiar Y ekranu
   @param bpp format ekranu
   @param flags dodatkowe flagi do inicjalizacji

   @return true je¿eli uda³o siê utworzyæ ekran, false je¿eli nie
*/

bool oglInit(int iScreenX, int iScreenY, int bpp, Uint32 flags)
{

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	// aliasing
	
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4);

	// set video mode

	SCREEN = SDL_SetVideoMode(iScreenX, iScreenY, bpp, SDL_OPENGL | flags);

	if (SCREEN == NULL)
	{
		printf("ERROR: Unable to set up video mode %dx%dx%dbpp.\n", iScreenX, iScreenY, bpp);
		return 0;
	}
	
	if (SCREEN->flags & SDL_OPENGL)
	{
		printf("[openGL]: %s\n ", glGetString(GL_VERSION));
		printf("[vendor]: %s\n ", glGetString(GL_VENDOR));
		printf("[renderer]: %s\n ", glGetString(GL_RENDERER));
		printf("[shader]: %s\n\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
	}
	else
	{
		printf("ERROR: Unable to init OpenGL\n");
	}

	glEnable(GL_TEXTURE_2D);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glViewport(0, 0, iScreenX, iScreenY);

	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glOrtho(0.0f, iScreenX, iScreenY, 0.0f, -1.0f, 1.0f);

	glMatrixMode(GL_MODELVIEW);

	glEnable(GL_BLEND);
	glEnable(GL_TEXTURE_2D);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_ALPHA_TEST);
	glDisable(GL_DEPTH_TEST);

	glEnable(GL_MULTISAMPLE);

	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST );
	glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST );
 
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_POLYGON_SMOOTH);

	glLoadIdentity();

	return true;
}

/**
   Aktualizacja ekranu.

   @param none

   @return none
*/

void oglFlip()
{
	SDL_GL_SwapBuffers();
}

/**
   Czyszczenie ekranu.

   @param none

   @return none
*/

void oglClear()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}


/**
   Zwolnienie pamiêci u¿ywanej przez texturê.

   @param texture wskaznik do uwalnianej textury

   @return none
*/

void oglFreeTexture(oglTexture *texture)
{
	glDeleteTextures(1, &texture->name);
	free(texture);
}

/**
   Render textury na ekran.

   @param texture renderowana textura
   @param clipping prostok¹t obcinaj¹cy
   @param x wspó³rzêdna x na ekranie
   @param y wspó³rzêdna y na ekranie
   @param cr modyfikacja koloru R textury
   @param cg modyfikacja koloru G textury
   @param cb modyfikacja koloru B textury
   @param ca modyfikacja przezroczystoœci textury
   @param hZoom skala X
   @param vZoom skala Y
   @param rotation k¹t obrotu textury

   @return none
*/

void oglBlit(oglTexture *texture, SDL_Rect* clipping, int x, int y, float cr, float cg, float cb, float ca, GLfloat hZoom, GLfloat vZoom, GLfloat rotation)
{
	GLfloat l, r, t, b;
	GLuint ch, cw;
	GLfloat hch, hcw;

	glBindTexture( GL_TEXTURE_2D, texture->name );

	glPushMatrix();

	if(clipping)
	{
		l = (GLfloat)clipping->x / texture->wTex;
		t = (GLfloat)clipping->y / texture->hTex;

		r = (GLfloat)(clipping->x + clipping->w) / texture->wTex;
		b = (GLfloat)(clipping->y + clipping->h) / texture->hTex;

		cw = clipping->w;
		ch = clipping->h;
	}
	else
	{
		cw = texture->w;
		ch = texture->h;	

		l = t = 0;
		r = b = 1;
	}

	hcw = ((GLfloat)cw ) * hZoom;
	hch = ((GLfloat)ch ) * vZoom;

	glTranslatef((GLfloat)x, (GLfloat)y, 0);
	glRotatef(rotation, 0, 0, 1.0f);

	glBegin( GL_QUADS );

	// Top-left 
	glTexCoord2f(l, t);
	glColor4f(cr,cg,cb,ca);	
	glVertex3f(0, 0, 0);

	// Top-right 
	glTexCoord2f(r, t);
	glColor4f(cr,cg,cb,ca);	
	glVertex3f(hcw, 0, 0 );
	
	// Bottom-right 
	glTexCoord2f(r, b);
	glColor4f(cr,cg,cb,ca);	
	glVertex3f(hcw, hch, 0);

	// Bottom-left 
	glTexCoord2f(l, b);
	glColor4f(cr,cg,cb,ca);	
	glVertex3f(0, hch, 0);
	
	glEnd();

	glPopMatrix();	
}

// blit texture giving center x & y

/**
   Render textury na ekran, gdzie podajemy wspó³rzêdne œrodka textury.
   Przydatne przy elementach obracaj¹cych siê wokó³ w³asnej osi.

   @param texture renderowana textura
   @param clipping prostok¹t obcinaj¹cy
   @param x wspó³rzêdna x na ekranie
   @param y wspó³rzêdna y na ekranie
   @param cr modyfikacja koloru R textury
   @param cg modyfikacja koloru G textury
   @param cb modyfikacja koloru B textury
   @param ca modyfikacja przezroczystoœci textury
   @param hZoom skala X
   @param vZoom skala Y
   @param rotation k¹t obrotu textury

   @return none
*/

void oglCBlit(oglTexture *texture, SDL_Rect* clipping, int x, int y, float cr, float cg, float cb, float ca, GLfloat hZoom, GLfloat vZoom, GLfloat rotation)
{
	GLfloat l, r, t, b;
	GLuint ch, cw;
	GLfloat hch, hcw;

	glBindTexture( GL_TEXTURE_2D, texture->name );

	glPushMatrix();

	if(clipping)
	{
		l = (GLfloat)clipping->x / texture->wTex;
		t = (GLfloat)clipping->y / texture->hTex;

		r = (GLfloat)(clipping->x + clipping->w) / texture->wTex;
		b = (GLfloat)(clipping->y + clipping->h) / texture->hTex;

		cw = clipping->w;
		ch = clipping->h;
	}
	else
	{
		cw = texture->w;
		ch = texture->h;	

		l = t = 0;
		r = b = 1;
	}

	hcw = ((GLfloat)cw / 2) * hZoom;
	hch = ((GLfloat)ch / 2) * vZoom;

	glTranslatef((GLfloat)x, (GLfloat)y, 0);
	glRotatef(rotation, 0, 0, 1.0f);

	glBegin( GL_QUADS );

	// Top-left 
	glTexCoord2f(l, t);
	glColor4f(cr,cg,cb,ca);	
	glVertex3f(-hcw, -hch, 0);

	// Top-right 
	glTexCoord2f(r, t);
	glColor4f(cr,cg,cb,ca);	
	glVertex3f(hcw, -hch, 0 );
	
	// Bottom-right 
	glTexCoord2f(r, b);
	glColor4f(cr,cg,cb,ca);	
	glVertex3f(hcw, hch, 0);

	// Bottom-left 
	glTexCoord2f(l, b);
	glColor4f(cr,cg,cb,ca);	
	glVertex3f(-hcw, hch, 0);
	
	glEnd();

	glPopMatrix();	
}

/**
   Zwraca najbli¿sz¹ liczbê, która jest potêg¹ liczby 2, ale poni¿ej wartoœci max.

   @param val liczba aktualna
   @param max wartoœæ maksymalna przeszukiwanego zakresu

   @return zwraca najbli¿sz¹ liczbê bêd¹c¹ potêg¹ liczby 2
*/

GLint oglGetPT(GLint val, GLint max)
{
	GLint i, count, high;

	count = 0;

	for (i = 0; i < sizeof(val) * 8; i++)
	{
		if((val >> i) & 1)
		{
			high = i;
			count++;
		}
	}

	if(count != 1)
		val = 1 << (high + 1);

	return OGL_MIN(val, max);
}

/**
   Sprawdzamy jaki format textury jest obs³ugiwany na karcie graficznej.

   @param w wysokoœæ tekstury
   @param h szerokoœæ tekstury
   @format format tekstury

   @return -1 je¿eli format i rozmiar jest niepoprawny
*/

int oglProbeTexture(GLint w, GLint h, GLenum format)
{
	GLint bpp;
	GLint width;

	if(format == GL_RGB || format == GL_BGR)
	{
		bpp = 3;
	}
	else
	{
		bpp = 4;
	}

	glTexImage2D(GL_PROXY_TEXTURE_2D, 0, format, w, h, 0, format, GL_UNSIGNED_BYTE, NULL);  
	glGetTexLevelParameteriv(GL_PROXY_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &width);

	if(!width)
		return -1;	// Texture probing failed 
	
	return !!width;
}

/**
   Sprawdzamy czy format tekstury i wymiary powinny byæ skonwertowane zanim obraz zostanie textur¹ openGL. 
   
   @param size prostok¹t z wymiarami testowanej textury
   @format format tekstury

   @return 1 je¿eli parametry s¹ poprawne
*/


int oglGetTexSize(SDL_Rect* size, GLenum format)
{
	GLint maxSize;
	int ret;

	ret = 1;

	glGetIntegerv(GL_MAX_TEXTURE_SIZE, &maxSize);

	if(size->x > maxSize || size->y > maxSize)
	{
		size->x = OGL_MIN(size->x, maxSize);
		size->y = OGL_MIN(size->y, maxSize);
		ret = 0;
	}

	if(!oglProbeTexture(size->x, size->y, format))
	{
		size->x = oglGetPT(size->x, maxSize);
		size->y = oglGetPT(size->y, maxSize);
	
		if(!oglProbeTexture(size->x, size->y, format))
			size->x = size->y = 0;
		
		ret = 0;
	}

	return ret;
}

/**
   Sprawdzamy jaki jest w³aœciwy format textury openGL dla danego SDL_Surface. 

   @format surface textura na podstawie której odpytujemy

   @return OGL_UNKNOWN je¿eli nie ma znanego formatu, lub format openGL
*/

GLenum oglGetFormat(SDL_Surface* surface)
{
	if(surface->format->BytesPerPixel == 4)
	{
		SDL_PixelFormat rgba = oglGetPixelFormat(GL_RGBA);
		
		if(oglCompareFormat(&rgba, surface->format))
			return GL_RGBA;
	}
	else if(surface->format->BytesPerPixel == 3)
	{
		SDL_PixelFormat rgb = oglGetPixelFormat(GL_RGB);
		
		if(oglCompareFormat(&rgb, surface->format))	
			return GL_RGB;	
	}

	return OGL_UNKNOWN;	
}

/**
   Konwersja SDL_Surface na format w³aœciwy dla openGL.

   @param surface obraz do konwersji
   @param format format openGL do konwersji
   @format origSize prostok¹t opisuj¹cy oryginalny rozmiar obrazu

   @return zwraca wskaŸnik do skonwertowanej textury openGL
*/

oglTexture *oglFromSurfaceConvert(SDL_Surface* surface, GLenum format, SDL_Rect origSize)
{
	oglTexture *texture = NULL;
	
	if(surface)
	{
		texture = (oglTexture*)malloc(sizeof(oglTexture));
		
		if(texture)
		{
			texture->w = origSize.x;
			texture->h = origSize.y;
			texture->hTex = surface->h;
			texture->wTex = surface->w;

			texture->format = format;

			glGenTextures(1, &texture->name);
			glBindTexture(GL_TEXTURE_2D, texture->name);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

			if(SDL_MUSTLOCK(surface))
				SDL_LockSurface(surface);			

			glTexImage2D(GL_TEXTURE_2D, 0, surface->format->BytesPerPixel, surface->w, surface->h, 0, texture->format, GL_UNSIGNED_BYTE, surface->pixels );

			if(SDL_MUSTLOCK(surface))
				SDL_UnlockSurface(surface);		
		}
	}
	return texture;
}

/**
   Tworzy kopiê surface na nowy w formacie RGBA w rozmiarze size.

   @param from surface Ÿród³owy textury
   @param size szeœcian z wymiarami nowej textury

   @return zwraca nowy, przekonwertowany surface
*/

SDL_Surface *oglCopySurface(SDL_Surface* from, SDL_Rect size)
{
	SDL_Surface* ret;
	SDL_PixelFormat fmt;

	fmt = oglGetPixelFormat(GL_RGBA);

	ret = SDL_CreateRGBSurface(SDL_SRCALPHA | SDL_SWSURFACE, size.x, size.y, 32, fmt.Rmask, fmt.Gmask, fmt.Bmask, fmt.Amask);

	if(ret)
		SDL_BlitSurface(from, NULL, ret, NULL);

	return ret;
}

/**
   Tworzy texturê openGL i zwalnia surface, który nie jest ju¿ potrzebny.

   @param surface obraz textury

   @return wskaŸnik do nowej textury w formacie openGL
*/

oglTexture *oglFromSurfaceFree(SDL_Surface* surface)
{
	oglTexture* ret;
	
	ret = oglFromSurface(surface);
	
	if(ret)
		SDL_FreeSurface(surface);	

	return ret;	
}

/**
   Tworzy texturê openGL na podstawie surface SDL.

   @param surface obraz Ÿród³owy textury

   @return zwraca wskaŸnik do textury openGL
*/

oglTexture *oglFromSurface(SDL_Surface* surface)
{
	GLenum format;
	SDL_Rect size, origSize;
	int reBlit, error;
	oglTexture* ret;

	error = reBlit = 0;
	ret = NULL;

	if(!surface)
		return ret;

	/* Get the color format of the surface */
	format = oglGetFormat(surface);

	origSize.x = size.x = surface->w;
	origSize.y = size.y = surface->h;

	if(format == OGL_UNKNOWN)
	{
		// Unsupported color format for direct conversion, see if the size is ok 
		oglGetTexSize(&size, GL_RGBA);
		reBlit = 1;
	}
	else
	{
		// Supported color format, see if the size is ok 
		reBlit = !oglGetTexSize(&size, format);
	}

	// If a OGL_GetTexSize didn't fail to find a texture size 
	if(size.x != 0 && size.y != 0)
	{
		if(!reBlit)
		{
			// The original surface size and color format was ok for direct conversion 
			ret = oglFromSurfaceConvert(surface, format, origSize);
		}
		else
		{
			// The original surface size and/or color format wasn't ok for direct conversion.
 			//   Do an RGBA-copy of it with the suggested size and then convert it.
			SDL_Surface* tmp;
			tmp = oglCopySurface(surface, size);
	
			if(tmp)
			{
				if(! (ret = oglFromSurfaceConvert(tmp, GL_RGBA, origSize)) )
					error = 1;
				
				SDL_FreeSurface(tmp);
			}
			else
			{
				// SDL_oglblit: Couldn't copy an unsupported surface to an RGBA surface
				error = 1;
			}
		}
	}
	else
	{
		// SDL_oglblit: Couldn't find a suitable texture size for the given surface.
		error = 1;
	}

	if(!ret && !error)
	{
		// Unknown error while converting surface to texture.
	}
	return ret;
}


