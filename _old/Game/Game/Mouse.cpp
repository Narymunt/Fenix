
#include "Mouse.h"

// constructor

CMouse::CMouse() :
_fDeltaX(0), _fDeltaY(0)
{

	// set flags

	_isLeft = false;
	_isRight = false;
	_isCenter = false;

	// hot X,Y = 0

	_cHotX = 0; 
	_cHotY = 0; 

	_iState = MOUSE_ARROW;

	// objects loaded 
	
	_pCursorArrow = new CSprite("mouse_arrow64.png");
	_pCursorHand = new CSprite("mouse_hand64.png");
	_pCursorWait = new CSprite("mouse_wait64.png");
}

// class destructor

CMouse::~CMouse()
{
	SafeDelete(_pCursorArrow);
	SafeDelete(_pCursorHand);
	SafeDelete(_pCursorWait);
}

void CMouse::isLeft(bool b)
{
	_isLeft = b;
}

void CMouse::isRight(bool b)
{
	_isRight = b;
}

void CMouse::isCenter(bool b)
{
	_isCenter = b;
}

// left button state

bool CMouse::isLeft(void)
{
	return _isLeft;
}

// right button state

bool CMouse::isRight(void)
{
	return _isRight;
}

// center button state 

bool CMouse::isCenter(void)
{
	return _isCenter;
}

// set positions 

void CMouse::fMouseX(float fPosition)
{
	_fLastMouseX = _fMouseX;
	_fMouseX = fPosition;
}

void CMouse::fMouseY(float fPosition)
{
	_fLastMouseY = _fMouseY;
	_fMouseY = fPosition;
}

// return positions 

float CMouse::fMouseX(void)
{
	return _fMouseX;
}

float CMouse::fMouseY(void)
{
	return _fMouseY;
}

// set click positions 

void CMouse::fMouseXClick(float fPosition)
{
	_fMouseXClick = fPosition;
}

void CMouse::fMouseYClick(float fPosition)
{
	_fMouseYClick = fPosition;
}

// return click positions 

float CMouse::fMouseXClick(void)
{
	return _fMouseXClick;
}

float CMouse::fMouseYClick(void)
{
	return _fMouseYClick;
}

// return delta click 

float CMouse::fClickDeltaX(void)
{
	if (_fMouseXClick<0)
		return 0;

	return _fMouseXClick - _fMouseX;
}

float CMouse::fClickDeltaY(void)
{
	if (_fMouseYClick<0)
		return 0;

	return _fMouseYClick - _fMouseY;
}

// set last positions 

void CMouse::fLastMouseX(float fPosition)
{
	_fLastMouseX = fPosition;
}


void CMouse::fLastMouseY(float fPosition)
{
	_fLastMouseY = fPosition;
}

// return last positions 

float CMouse::fLastMouseX(void)
{
	return _fLastMouseX;
}

float CMouse::fLastMouseY(void)
{
	return _fLastMouseY;
}

// render pointer 

void CMouse::Render(void)
{
	switch (_iState)
	{
		case MOUSE_NONE:

		break;

		case MOUSE_ARROW:
			_pCursorArrow->Position(_fMouseX, _fMouseY);
			_pCursorArrow->Render();
		break;

		case MOUSE_HAND:
			_pCursorHand->Position(_fMouseX, _fMouseY);
			_pCursorHand->Render();
		break;

		case MOUSE_WAIT:
			_pCursorWait->Position(_fMouseX, _fMouseY);
			_pCursorWait->Render();
		break;

	}
}



// end
