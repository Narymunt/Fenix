#include "Congratulations.h"

Congratulations::Congratulations()
{
	_background = NULL;
	_black = NULL;	
	_exitButton = NULL;
	_timerStart = 0;
	_font = NULL;

	_isOpen = false;
}


Congratulations::~Congratulations()
{
	close();
}


void Congratulations::open(Screen *screen)
{	
	_timerStart = 0;
	_font = new SpriteFont(screen);
	_isMouseLock = true;
	_isOpen = true;
	_screen = screen;
}


void Congratulations::close(void)
{
	safeDelete(_background);
	safeDelete(_black);
	safeDelete(_exitButton);
	safeDelete(_font);

	_isOpen = false;
}

int Congratulations::render(unsigned long timer, Mouse *mouse)
{
	if (!mouse->_isL)
		_isMouseLock = false;

	if (_timerStart == 0)
		_timerStart = timer;

	_background->render();		

	if (timer - _timerStart < 1000)
	{
		_black->_a = (1-(timer - _timerStart)*0.001f);
		_black->render();
	}

	_font->print(250, 300, 1, 0.1f, 0.1f, (char*)"congratulations");

	return (_exitButton->render(mouse) == ON_LEFT && !_isMouseLock) ? 1 : 0;
}


//end
