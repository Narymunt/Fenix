
// mouse handle class 

#pragma once

#include "../Game.h"
#include "../common/GameObject.h"

#ifdef _WIN32
#include <Windows.h>
#include "../gfx/Sprite.h"
#endif

#ifdef __ANDROID__
#include "../android/Sprite.h"
#endif

#ifdef __APPLE__
#include "TargetConditionals.h"
#if TARGET_IPHONE_SIMULATOR
// iOS Simulator
#include "../ios/Sprite.h"
#elif TARGET_OS_IPHONE
// iOS device
#include "../ios/Sprite.h"
#elif TARGET_OS_MAC
// Other kinds of Mac OS
#include "../osx/Sprite.h"
#else
#   error "Unknown Apple platform"
#endif
#endif


#define MOUSE_NONE		0
#define MOUSE_ARROW		10
#define MOUSE_HAND		20
#define MOUSE_WAIT		30

class CMouse : public CGameObject
{

public:
	CMouse(bool isVisible);      
	~CMouse();

	void render(void);		
	void render(int iState);

	//=== delta dla wspolrzednych

	float fClickDeltaX(void);
	float fClickDeltaY(void);

	int		_state;

	bool	_isLeft;		// left mouse button 
	bool	_isRight;		
	bool	_isCenter;	

	bool	_isVisible;

	float	_x;		// cursor positions 
	float	_y;		

	float	_lastX;
	float	_lastY;

	float	_xClick;
	float	_yClick;

	float	_deltaX;		// roznica pomiedzy kliknieciem a aktualnymi wspolrzednymi
	float	_deltaY;

	char	_hotX;		// hot coords 
	char	_hotY;		

	CSprite		*_cursorArrow;		// bitmap
	CSprite		*_cursorHand;
	CSprite		*_cursorWait;
};


