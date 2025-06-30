#include "Congratulations.h"

CCongratulations::CCongratulations()
{
	_background = NULL;
	_black = NULL;	
	_exitButton = NULL;
	_timerStart = 0;
	_font = NULL;

	_isOpen = false;
}


CCongratulations::~CCongratulations()
{
	Close();
}


void CCongratulations::Open(CScreen *pScreen)
{	
	_timerStart = 0;
	_font = new CSpriteFont(pScreen);
	_isMouseLock = true;
	_isOpen = true;
	_screen = pScreen;
}


void CCongratulations::Close(void)
{
	safeDelete(_background);
	safeDelete(_black);
	safeDelete(_exitButton);
	safeDelete(_font);

	_isOpen = false;
}


int CCongratulations::Render(unsigned long ulTimer, CMouse *pMouse)
{
	if (!pMouse->_isL)
		_isMouseLock = false;

	if (_timerStart == 0)
		_timerStart = ulTimer;

	_background->render();		

	if (ulTimer - _timerStart < 1000)
	{
		_black->_a = (1-(ulTimer - _timerStart)*0.001f);
		_black->render();
	}

	_font->print(250, 300, 1, 0.1f, 0.1f, (char*)"congratulations");

	return (_exitButton->render(pMouse) == ON_LEFT && !_isMouseLock) ? 1 : 0;
}


//end
