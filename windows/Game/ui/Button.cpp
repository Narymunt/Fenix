#include "Button.h"

#pragma warning(disable:4996)

CButton::CButton(char image[], char onClick[]) :
	_x1(0), _y1(0), _x2(0), _y2(0)
{
	_onStatic = new CSprite(image);
	_onOver = NULL;
	_onClick = new CSprite(onClick);
}

CButton::CButton(char clicked_name[], char m_pImage_name[], int x1, int y1, int x2, int y2) :
	_x1(x1), _y1(y1), _x2(x2), _y2(y2)
{
	_onClick = new CSprite(clicked_name);
	_onClick->resize(x1, y1, x2, y2);

	_onOver = NULL;

	_onStatic = new CSprite(m_pImage_name);
	_onStatic->resize(x1, y1, x2, y2);
}

// create 3 bitmap based button

CButton::CButton(char image[], char onOver[], char onClick[]) :
_x1(0),_y1(0),_x2(0),_y2(0)
{
	_onStatic = new CSprite(image);
	_onOver = new CSprite(onOver);
	_onClick = new CSprite(onClick);
}

// create and rescale

CButton::CButton(char clicked_name[], char onButton_name[], char m_pImage_name[], int x1, int y1, int x2, int y2) :
_x1(x1), _y1(y1), _x2(x2), _y2(y2)
{
	_onClick = new CSprite(clicked_name);
	_onClick->resize(x1, y1, x2, y2);
	
	_onOver = new CSprite(onButton_name);
	_onOver->resize(x1, y1, x2, y2);
	
	_onStatic = new CSprite(m_pImage_name);
	_onStatic->resize(x1, y1, x2, y2);
}

// destructor, release graphics 

CButton::~CButton()
{
	safeDelete(_onClick);
	safeDelete(_onStatic);
	safeDelete(_onOver);
}

// check mouse state and draw 

int CButton::render(CMouse *mouse)
{
	// check hot coords 

	if ((mouse->_x>_x1) && (mouse->_x<_x2) && (mouse->_y>_y1) && (mouse->_y<_y2))
	{
		if (mouse->_isR)
		{
			_onClick->render();	
			return ON_RIGHT;
		}

		if (mouse->_isL)
		{
			_onClick->render();
			return ON_LEFT;
		}
		
		if (mouse->_isC)
		{
			_onClick->render();
			return ON_CENTER;
		}

		_onOver->render();
		return ON_OVER;
	}

	_onStatic->render();
	return 0;
}

// setup button position 

void CButton::position(long lX, long lY)
{
	_onClick->position((float)lX,(float)lY);
	_onStatic->position((float)lX,(float)lY);
	_onOver->position((float)lX,(float)lY);
}

// set hot coords for button

void CButton::setHotCoords(long lXStart, long lYStart, long lXEnd, long lYEnd)
{
	_x1 = lXStart; _y1 = lYStart;
	_x2 = lXEnd; _y2 = lYEnd;
}

void CButton::set(long x1, long y1, long x2, long y2)
{
	_x1 = x1; _y1= y1;
	_x2 = x2; _y2 = y2;

	_onClick->position((float)x1,(float)y1);
	_onStatic->position((float)x1,(float)y1);
	_onOver->position((float)x1,(float)y1);
}
