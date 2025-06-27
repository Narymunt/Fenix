#pragma once

#include "../Game.h"
#include "Mouse.h"

#include <windows.h>
#include <string>
#include "../gfx/Sprite.h"
#include "../gfx/Screen.h"
#include "../gfx/FontTTF.h"

#define ON_NONE		0
#define ON_LEFT		10
#define ON_RIGHT	20
#define ON_CENTER	30
#define ON_OVER		40

class CButtonTTF
{
	
public:
	
	CButtonTTF(char onStatic[], char onClick[], char text[]);
	CButtonTTF(char onStatic[], char onClick[], char text[], int x1, int y1, int x2, int y2);

	CButtonTTF(char onStatic[], char onOver[], char onClick[], char text[]);
	CButtonTTF(char onStatic[], char onOver[], char onClick[], char text[], int x1, int y1, int x2, int y2);

	~CButtonTTF();

	int render(CMouse *mouse);								// render button 

	void position(long x, long y);							// ustawia wspó³rzêdne do rysowania	
	void setHotCoords(long x1, long y1, long x2, long y2);  // ustawia wspó³rzêdne aktywnego obszaru
   
	void set(long x1, long y1, long x2, long y2);			// ustawia wspó³rzêdne do rysowania oraz aktywnego obszaru

	inline int sizeX(void) { return _x2 - _x1; }
	inline int sizeY(void) { return _y2 - _y1; }
	
	void alfa(float a);

	long		_x1, _y1, _x2, _y2;

	std::string _text;

	CSprite		*_onClick;		
	CSprite		*_onOver;	
	CSprite		*_onStatic;		

	CFontTTF* _font;

};