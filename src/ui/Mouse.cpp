#include "Mouse.h"

// constructor

CMouse::CMouse(bool isVisible) :
_deltaX(0), _deltaY(0),
_isVisible(isVisible)
{

	// set flags

	_isLeft = false;
	_isRight = false;
	_isCenter = false;

	// hot X,Y = 0

	_hotX = 0; 
	_hotY = 0; 

	_state = MOUSE_ARROW;

	// objects loaded 
	
	_cursorArrow = new CSprite("mouse_arrow64.png");
	_cursorHand = new CSprite("mouse_hand64.png");
	_cursorWait = new CSprite("mouse_wait64.png");
}

// class destructor

CMouse::~CMouse()
{
	SafeDelete(_cursorArrow);
	SafeDelete(_cursorHand);
	SafeDelete(_cursorWait);
}


// render pointer 

void CMouse::render(void)
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

// end
