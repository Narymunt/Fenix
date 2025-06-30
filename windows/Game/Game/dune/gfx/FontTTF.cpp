/**
   FontTTF.cpp

   @author Jaros³aw N. Ro¿yñski
   
*/

#pragma warning (disable:4244)

#include "FontTTF.h"

CFontTTF::CFontTTF(char cFilenameTTF[], int iSize)
{  
   _pFont = TTF_OpenFont("c:\\projects\\arial.ttf", iSize);
}

CFontTTF::~CFontTTF()
{
  TTF_CloseFont(_pFont);  
}

void CFontTTF::Print(const std::string &message, unsigned char r, unsigned char g, unsigned char b, int x, int y)
{
   SDL_Color color;

   color.r = r; color.b = b; color.g = g;

   _pSurface = TTF_RenderText_Blended(_pFont, message.c_str(), color);

   glGenTextures(1, &_iTexture);
   glBindTexture(GL_TEXTURE_2D, _iTexture);

   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, _pSurface->w, _pSurface->h, 0, GL_BGRA, GL_UNSIGNED_BYTE, _pSurface->pixels);

   glBegin(GL_QUADS);
   {
    glTexCoord2f(0,0); glVertex2f(x, y);
    glTexCoord2f(1,0); glVertex2f(x + _pSurface->w, y);
    glTexCoord2f(1,1); glVertex2f(x + _pSurface->w, y + _pSurface->h);
    glTexCoord2f(0,1); glVertex2f(x, y + _pSurface->h);
   }
  
   glEnd();

  glDeleteTextures(1, &_iTexture);
  SDL_FreeSurface(_pSurface);

}



