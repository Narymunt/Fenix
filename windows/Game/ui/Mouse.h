#pragma once

#include <Windows.h>
#include "../Game.h"
#include "../common/GameObject.h"
#include "../gfx/Sprite.h"

#define MOUSE_NONE		0
#define MOUSE_ARROW		10
#define MOUSE_HAND		20
#define MOUSE_WAIT		30

class Mouse : public GameObject
{

public:
	Mouse(bool isVisible);      
	~Mouse();

	void render(void);		
	void render(int iState);

	//=== delta dla wspolrzednych

	float clickDeltaX(void) {};
	float clickDeltaY(void) {};

	void set(float x, float y);
	void click(float x, float y, bool L, bool C, bool R);

	int		_state;

	bool	_isL;		// left mouse button 
	bool	_isR;		
	bool	_isC;	

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

	Sprite		*_cursorArrow;		// bitmap
	Sprite		*_cursorHand;
	Sprite		*_cursorWait;
};


