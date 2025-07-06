#include "Mouse.h"

CMouse::CMouse(bool isVisible) :
_deltaX(0), _deltaY(0), _isVisible(isVisible)
{
	_isL = false;
	_isR = false;
	_isC = false;

	_hotX = 0; _hotY = 0; 

	_state = MOUSE_ARROW;

	// objects loaded 
	
	_cursorArrow = new CSprite((char*)"mouse_arrow64.png");
	_cursorHand = new CSprite((char*)"mouse_hand64.png");
	_cursorWait = new CSprite((char*)"mouse_wait64.png");
}

// class destructor

CMouse::~CMouse()
{
	safeDelete(_cursorArrow);
	safeDelete(_cursorHand);
	safeDelete(_cursorWait);
}

void CMouse::render(void) // render pointer 
{
   if (!_isVisible)
      return;

	switch (_state)
	{
		case MOUSE_NONE:

		break;

		case MOUSE_ARROW:
			_cursorArrow->position(_x, _y);
			_cursorArrow->render();
		break;

		case MOUSE_HAND:
			_cursorHand->position(_x, _y);
			_cursorHand->render();
		break;

		case MOUSE_WAIT:
			_cursorWait->position(_x, _y);
			_cursorWait->render();
		break;

	}
}

void CMouse::set(float x, float y)
{
	_x = x; _y = y;
}

void CMouse::click(float x, float y, bool L, bool C, bool R)
{
	_x = x; _y = y;
	_isL = L; _isC = C; _isR = R;
}

