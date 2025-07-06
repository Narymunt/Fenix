#include "Help.h"

CHelp::CHelp()
{
	_background = NULL;
	_exitButton = NULL;
	_timerStart = 0;
	_isOpen = false;
}

CHelp::~CHelp()
{
	close();
}


void CHelp::open(CScreen *pScreen)
{	
	_background = new CSprite((char*)"level04.jpg");

	_exitButton = new CButton((char*)"x1.png", (char*)"x2.png", (char*)"x3.png");
	_exitButton->position(128,64-32);
	_exitButton->setHotCoords(128,32,128+128,32+128);

	_isOpen = true;
}

void CHelp::close(void)
{
	safeDelete(_background);
	safeDelete(_exitButton);
	_isOpen = false;
}


int CHelp::render(unsigned long timer, CMouse *mouse)
{
	if (!mouse->_isL)
		_isMouseLock = false;

	if (_timerStart == 0)
		_timerStart = timer;

	_background->render();		

	return (_exitButton->render(mouse) == ON_LEFT && !_isMouseLock) ? 1 : 0;
}

