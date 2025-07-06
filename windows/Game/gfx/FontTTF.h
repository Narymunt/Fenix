/**
   FontTTF.h

   Klasa do renderowania font�w TTF na teksturze 2D. 

   @author Jaros�aw Ro�y�ski
   
*/

#pragma once

#include <string>
#include <SDL.h>
#include <SDL_openGL.h>
#include <SDL_ttf.h>
#include "../Game.h"

class FontTTF
{
	
public: 
	
   FontTTF(char cFilenameTTF[], int iSize);   // plik z czcionk� np. arial.txt
   ~FontTTF();

   void print(const std::string &message, unsigned char r, unsigned char g, unsigned char b, int x, int y);

private:	
    
    unsigned int   _iTexture;
    TTF_Font       *_pFont;
    SDL_Surface    *_pSurface;
};

