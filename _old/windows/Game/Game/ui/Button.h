#pragma once

#include "../Game.h"
#include "Mouse.h"

#ifdef _WIN32
#include <windows.h>
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

#define ON_NONE		0
#define ON_LEFT		10
#define ON_RIGHT	20
#define ON_CENTER	30
#define ON_OVER		40

class CButton  
{
public:
	
	CButton(CScreen *screen, char name[]); 

	CButton(char onStatic[], char onOver[], char onClick[]);
	CButton(CScreen *screen, char onStatic[], char onOver[], char onClick[]);

	CButton(char onStatic[], char onOver[], char onClick[], int x1, int y1, int x2, int y2);
	CButton(CScreen *screen, char onStatic[], char onOver[], char onClick[], int x1, int y1, int x2, int y2);

	~CButton();

	int render(CMouse *pMouse);								// render button 

	void position(long x, long y);							// ustawia wspó³rzêdne do rysowania	
	void setHotCoords(long x1, long y1, long x2, long y2);  // ustawia wspó³rzêdne aktywnego obszaru
   
	void set(long x1, long y1, long x2, long y2);			// ustawia wspó³rzêdne do rysowania oraz aktywnego obszaru

	inline int sizeX(void) { return _x2 - _x1; }
	inline int sizeY(void) { return _y2 - _y1; }
	
	long		_x1, _y1, _x2, _y2;

private:

	void init(CScreen *screen, char image[], char onOver[], char onClick[], int x1, int y1, int x2, int y2);

	CSprite		*_onClick;		
	CSprite		*_onOver;	
	CSprite		*_onStatic;		

};

