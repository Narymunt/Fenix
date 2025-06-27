#include "Mouse.h"

Mouse::Mouse(bool isVisible) :
_deltaX(0), _deltaY(0), _isVisible(isVisible)
{
	_isL = false;
	_isR = false;
	_isC = false;

	_hotX = 0; _hotY = 0; 

	_state = MOUSE_ARROW;

	// objects loaded 
	
	_cursorArrow = new Sprite((char*)"mouse_arrow64.png");
	_cursorHand = new Sprite((char*)"mouse_hand64.png");
	_cursorWait = new Sprite((char*)"mouse_wait64.png");
}

// class destructor

Mouse::~Mouse()
{
	safeDelete(_cursorArrow);
	safeDelete(_cursorHand);
	safeDelete(_cursorWait);
}

void Mouse::render(void) // render pointer 
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

void Mouse::set(float x, float y)
{
	_x = x; _y = y;
}

void Mouse::click(float x, float y, bool L, bool C, bool R)
{
	_x = x; _y = y;
	_isL = L; _isC = C; _isR = R;
}

