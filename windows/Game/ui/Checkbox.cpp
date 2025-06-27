#include "Checkbox.h"

Checkbox::Checkbox(char onStatic[], char onOver[], char offStatic[], char offOver[]) : _isMouseLock(true)
{init(onStatic, onOver, offStatic, offOver, 0, 0, 0, 0, 0, 0, false);}

Checkbox::Checkbox(char onStatic[], char onOver[], char offStatic[], char offOver[], bool b) : _isMouseLock(true)
{init(onStatic, onOver, offStatic, offOver, 0, 0, 0, 0, 0, 0, b);}

Checkbox::Checkbox(char onStatic[], char onOver[], char offStatic[], char offOver[], int x, int y) : _isMouseLock(true)
{init(onStatic, onOver, offStatic, offOver, x, y, 0, 0, 0, 0, false);}

Checkbox::Checkbox(char onStatic[], char onOver[], char offStatic[], char offOver[], int x, int y, bool b) : _isMouseLock(true)
{init(onStatic, onOver, offStatic, offOver, x, y, 0, 0, 0, 0, b);}

Checkbox::Checkbox(char onStatic[], char onOver[], char offStatic[], char offOver[], int x1, int y1, int x2, int y2) : _isMouseLock(true)
{init(onStatic, onOver, offStatic, offOver, x1, y1, x1, y1, x2, y2, false);}

Checkbox::Checkbox(char onStatic[], char onOver[], char offStatic[], char offOver[], int x1, int y1, int x2, int y2, bool b) : _isMouseLock(true)
{init(onStatic, onOver, offStatic, offOver, x1, y1, x1, y1, x2, y2, b);}

Checkbox::Checkbox(char onStatic[], char onOver[], char offStatic[], char offOver[], int x, int y, int x1, int y1, int x2, int y2) : _isMouseLock(true)
{init(onStatic, onOver, offStatic, offOver, x, y, x1, y1, x2, y2, false);}

Checkbox::Checkbox(char onStatic[], char onOver[], char offStatic[], char offOver[], int x, int y, int x1, int y1, int x2, int y2, bool b) : _isMouseLock(true)
{init(onStatic, onOver, offStatic, offOver, x, y, x1, y1, x2, y2, b);}

Checkbox::~Checkbox()
{
	safeDelete(_onStatic);
	safeDelete(_onOver);
	safeDelete(_offStatic);
	safeDelete(_offOver);
}

void Checkbox::init(char onStatic[], char onOver[], char offStatic[], char offOver[], int x, int y, int x1, int y1, int x2, int y2, bool b)
{
	_onStatic = new Sprite(onStatic);
	_onOver = new Sprite(onOver);
	_offStatic = new Sprite(offStatic);
	_offOver = new Sprite(offOver);

	if (x == y && x== 0 && x==x2)	// brak podanych x1,y1,x2,y2
	{
		_onStatic->position((float)x, (float)y);
		_onOver->position((float)x, (float)y);
	}
}

int Checkbox::render(unsigned long ulTimer,Mouse *mouse)	// 0 - mysz poza, 1 - clicked, 2 on over
{
	// renderuj przycisk

	if (_onOver!=NULL)	// czy kursor podswietla
	{
		if (_state)
		{
			if ((mouse->_x>_x1)&&(mouse->_x<_x2)&&(mouse->_y>_y1)&&(mouse->_y<_y2))	// mysz nad obiektem - rysuj podswietlone
			{
				_onOver->position((float)_x,(float)_x);
				_onOver->render();
			}
			else
			{
				_onStatic->position((float)_x,(float)_y);	// jesli nie, rysuj normalne
				_onStatic->render();
			}
		}
		else
		{
			if ((mouse->_x > _x1) && (mouse->_x < _x2) && (mouse->_y > _y1) && (mouse->_y < _y2))	// mysz nad obiektem - rysuj podswietlone
			{
				_offOver->position((float)_x,(float)_y);
				_offOver->render();
			}
			else
			{
				_offStatic->position((float)_x,(float)_y);	// jesli nie, rysuj normalne
				_offStatic->render();
			}
		}
	}
	else	// bez podswietlania
	{
		if (_state)
		{
			_onStatic->position((float)_x,(float)_y);
			_onStatic->render();
		}
		else
		{
			_offStatic->position((float)_x,(float)_y);
			_offStatic->render();
		}
	}
	
	// zmiana stanu przycisku

	if (!_isMouseLock)
	{
		if ((mouse->_x > _x1) && (mouse->_x < _x2) && (mouse->_y > _y1) && (mouse->_y < _y2) && mouse->_isL)	// mysz nad obiektem - rysuj podswietlone
			_state |= _state;
	}

	// zmiana stanu blokady myszy

	_isMouseLock = mouse->_isL ? true : false;

	return 0; 
}

int Checkbox::render(int iX, int iY, unsigned long ulTimer,Mouse *pMouse)
{
   int deltaX,deltaY;

   _x = iX;_y = iY;

   _onStatic->position((float)iX,(float)iY);
   _offStatic->position((float)iX,(float)iY);
   _onOver->position((float)iX,(float)iY);
   _offOver->position((float)iX,(float)iY);

   deltaX = _x2 - _x1;
   deltaY = _y2 - _y1;

   setHotCoords(iX,iY, iX+deltaX,iY+deltaY);

   return render(ulTimer,pMouse); 
}	

void Checkbox::set(bool state, int x, int y)
{
	_state = state; _x = x; _y = y; 
}

void Checkbox::set(bool state, int x, int y, int x1, int y1, int x2, int y2)
{
	_state = state;
	_x = x; _y = y; 
	_x1 = x1; _y1 = y1; 
	_x2 = x2; _y2 = y2; 
}

void Checkbox::setHotCoords(int x1, int y1, int x2, int y2)
{
	_x1 = x1; _y1 = y1; 
	_x2 = x2; _y2 = y2; 
}

void Checkbox::position(int x, int y)
{
	_x = x; _y = y; 
}

void Checkbox::position(int x, int y, int x1, int y1, int x2, int y2)
{
	position(x, y);
	setHotCoords(x1, y1, x2, y2);
}