// do trzymania fontow jako grafiki, gdzie kazda litera to osobny sprite
// tylko duze literki

#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include "../../Game.h"
#include "../gfx/Sprite.h"
#include "../gfx/Screen.h"

using namespace std;

class CSpriteFont
{

	public : 
	
		CSpriteFont(CScreen *pScreen);
		~CSpriteFont();
		
		void Print(int iX, int iY, int iAlfa, float fSizeX, float fSizeY, char cText[]);		
		
		int	iSize(float fSizeX, char cText[]);	// zwraca ile szerokoœci bêdzie zajmowaæ dany napis

	private:
	
		CSprite		*m_pCharTable[37];
	
};