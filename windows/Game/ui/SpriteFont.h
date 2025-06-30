// do trzymania fontow jako grafiki, gdzie kazda litera to osobny sprite
// tylko duze literki

#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include "../Game.h"
#include "../gfx/Sprite.h"
#include "../gfx/Screen.h"

using namespace std;

class SpriteFont
{

public : 

	SpriteFont(Screen *screen);
	~SpriteFont();
	
	void print(int iX, int iY, int iAlfa, float fSizeX, float fSizeY, char cText[]);		
	int	size(float fSizeX, char cText[]);	// zwraca ile szeroko�ci b�dzie zajmowa� dany napis
	
	Sprite		*_charTable[37];
	
};