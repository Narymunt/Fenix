#include "Credits.h"

Credits::Credits()
{
	_background = NULL;
	_exitButton = NULL;
	_timerStart = 0;
	_isOpen = false;
}


Credits::~Credits()
{
	close();
}


void Credits::open(Screen *pScreen)
{	
//	_pBackground = new CSprite(pScreen,"CREDITS_SCREEN");
//	_pExitButton = new CButton("data/x1.png","data/x2.png","data/x3.png");
//	_pExitButton->SetPosition(128,64-32);
//	_pExitButton->SetHotCoords(128,32,128+128,32+128);

	_isOpen = true;
}

void Credits::close(void)
{
	safeDelete(_background);
	safeDelete(_exitButton);
	_isOpen = false;
}

int Credits::render(unsigned long timer, Mouse *mouse)
{
	if (!mouse->_isL)
		_isMouseLock = false;

	if (_timerStart == 0)
		_timerStart = timer;

	_background->render();		

	return (_exitButton->render(mouse) == ON_LEFT && !_isMouseLock) ? 1 : 0;
}
