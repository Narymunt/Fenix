
#include "Mouse.h"

// constructor

CMouse::CMouse()
{

	// set flags

	_isLeft = false;
	_isRight = false;
	_isCenter = false;

	// hot X,Y = 0

	_cHotX = 0; 
	_cHotY = 0; 

	// objects loaded 
	
	_pNormalPoint = NULL;	// null point

	_pNormalPoint = new CSprite("data/mouse.png");

}

// class destructor

CMouse::~CMouse()
{
	SafeDelete(_pNormalPoint);
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

float CMouse::fGetClickDeltaX(void)
{
	if (_fMouseXClick<0)
		return 0;

	return _fMouseXClick - _fMouseX;
}

float CMouse::fGetClickDeltaY(void)
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
		_pNormalPoint->Position(_fMouseX, _fMouseY);
		_pNormalPoint->Render();
}



// end
