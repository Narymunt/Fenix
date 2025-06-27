#include "ButtonTTF.h"

#pragma warning(disable:4996)

ButtonTTF::ButtonTTF(char image[], char onClick[], char text[]) :
	_x1(0), _y1(0), _x2(0), _y2(0)
{
	_onStatic = new Sprite(image);
	_onOver = NULL;
	_onClick = new Sprite(onClick);

	_text = std::string(text);
	_font = new FontTTF((char*)"data/consola.ttf", 20);
}

ButtonTTF::ButtonTTF(char clicked_name[], char m_pImage_name[], char text[], int x1, int y1, int x2, int y2) :
	_x1(x1), _y1(y1), _x2(x2), _y2(y2)
{
	_onClick = new Sprite(clicked_name);
	_onClick->resize(x1, y1, x2, y2);

	_onOver = NULL;

	_onStatic = new Sprite(m_pImage_name);
	_onStatic->resize(x1, y1, x2, y2);

	_text = std::string(text);
	_font = new FontTTF((char*)"data/consola.ttf", 20);
}

// create 3 bitmap based button

ButtonTTF::ButtonTTF(char image[], char onOver[], char onClick[], char text[]) :
_x1(0),_y1(0),_x2(0),_y2(0)
{
	_onStatic = new Sprite(image);
	_onOver = new Sprite(onOver);
	_onClick = new Sprite(onClick);

	_text = std::string(text);
	_font = new FontTTF((char*)"data/consola.ttf", 20);
}

// create and rescale

ButtonTTF::ButtonTTF(char clicked_name[], char onButton_name[], char m_pImage_name[], char text[], int x1, int y1, int x2, int y2) :
_x1(x1), _y1(y1), _x2(x2), _y2(y2)
{
	_onClick = new Sprite(clicked_name);
	_onClick->resize(x1, y1, x2, y2);
	
	_onOver = new Sprite(onButton_name);
	_onOver->resize(x1, y1, x2, y2);
	
	_onStatic = new Sprite(m_pImage_name);
	_onStatic->resize(x1, y1, x2, y2);

	_text = std::string(text);
	_font = new FontTTF((char*)"data/consola.ttf", 20);
}

// destructor, release graphics 

ButtonTTF::~ButtonTTF()
{
	safeDelete(_onClick);
	safeDelete(_onStatic);
	safeDelete(_onOver);
}

// check mouse state and draw 

int ButtonTTF::render(Mouse *mouse)
{
	int ret = 0;

	// check hot coords 

	if ((mouse->_x>_x1) && (mouse->_x<_x2) && (mouse->_y>_y1) && (mouse->_y<_y2))
	{
		if (mouse->_isR)
		{
			_onClick->render();	
			ret = ON_RIGHT;
		}
		else 
		if (mouse->_isL)
		{
			_onClick->render();
			ret = ON_LEFT;
		}
		else
		if (mouse->_isC)
		{
			_onClick->render();
			ret = ON_CENTER;
		}
		else
		{
			_onOver->render();
			ret = ON_OVER;
		}
	}
	else
	{ 
		_onStatic->render();
		ret = 0;
	}
	
	_font->print(_text, 255, 255, 255, _x1+10, _y1+10);

	return ret;
}

// setup button position 

void ButtonTTF::position(long lX, long lY)
{
	_onClick->position((float)lX,(float)lY);
	_onStatic->position((float)lX,(float)lY);
	_onOver->position((float)lX,(float)lY);
}

// set hot coords for button

void ButtonTTF::setHotCoords(long lXStart, long lYStart, long lXEnd, long lYEnd)
{
	_x1 = lXStart; _y1 = lYStart;
	_x2 = lXEnd; _y2 = lYEnd;
}

void ButtonTTF::set(long x1, long y1, long x2, long y2)
{
	_x1 = x1; _y1= y1;
	_x2 = x2; _y2 = y2;

	_onClick->position((float)x1,(float)y1);
	_onClick->scale((x2 - x1) / _onClick->_sizeX, (y2 - y1) / _onClick->_sizeY);

	_onStatic->position((float)x1,(float)y1);
	_onStatic->scale((x2 - x1) / _onStatic->_sizeX, (y2 - y1) / _onStatic->_sizeY);

	_onOver->position((float)x1,(float)y1);
	_onOver->scale((x2 - x1) / _onOver->_sizeX, (y2 - y1) / _onOver->_sizeY);
}

void ButtonTTF::alfa(float a)
{
	_onClick->_a = a;
	_onStatic->_a = a;
	_onOver->_a = a;
}
