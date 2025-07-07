// do trzymania fontow jako grafiki, gdzie kazda litera to osobny sprite
// tylko duze literki

#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include "../Game.h"

#ifdef _WIN32
	#include "../gfx/Sprite.h"
	#include "../gfx/Screen.h"
#endif

#ifdef __ANDROID__
#include "../android/Sprite.h"
#include "../android/Screen.h"
#endif

#ifdef __APPLE__
#include "TargetConditionals.h"
#if TARGET_IPHONE_SIMULATOR
// iOS Simulator
#include "../ios/Sprite.h"
#include "../ios/Screen.h"
#elif TARGET_OS_IPHONE
// iOS device
#include "../ios/Sprite.h"
#include "../ios/Screen.h"
#elif TARGET_OS_MAC
// Other kinds of Mac OS
#include "../osx/Sprite.h"
#include "../osx/Screen.h"
#else
#   error "Unknown Apple platform"
#endif
#endif

using namespace std;

class CSpriteFont
{

	public : 
	
		CSpriteFont(CScreen *screen);
		~CSpriteFont();
		
		void print(int iX, int iY, int iAlfa, float fSizeX, float fSizeY, char cText[]);		
		
		int	size(float fSizeX, char cText[]);	// zwraca ile szerokoœci bêdzie zajmowaæ dany napis

	private:
	
		CSprite		*_charTable[37];
	
};