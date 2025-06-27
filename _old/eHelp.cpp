#include "eHelp.h"

eHelp::eHelp()
{
	_pBackground = NULL;
	_pExitButton = NULL;

	_ulTimerStart = 0;

	_isActive = false;
}


eHelp::~eHelp()
{
	Close();
}


void eHelp::Open(CScreen *pScreen)
{	
	_pBackground = new CSprite(pScreen,"HELP_SCREEN");

	_pExitButton = new CButton("data/x1.png","data/x2.png","data/x3.png");
	_pExitButton->SetPosition(128,64-32);
	_pExitButton->SetHotCoords(128,32,128+128,32+128);

	_isActive = true;
}


void eHelp::Close(void)
{
	SafeDelete(_pBackground);
	SafeDelete(_pExitButton);
	
	_isActive = false;
}


int eHelp::Render(unsigned long ulTimer, CMouse *pMouse)
{
	int iReturn=0;

	if (!pMouse->isLeft())
		m_bMouseLock = false;

	if (_ulTimerStart == 0)
		_ulTimerStart = ulTimer;

	_pBackground->Render();		

	if (_pExitButton->Render(pMouse)==ON_LEFT && !m_bMouseLock)		
		return 1;

	return 0;
}


//end
