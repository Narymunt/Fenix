#include "eHelp.h"

eHelp::eHelp()
{
	_pBackground = NULL;
	_pExitButton = NULL;

	_ulTimerStart = 0;

	m_bMouseLock = true;

	_isActive = false;
}


eHelp::~eHelp()
{
	Close();
}


void eHelp::Open(CScreen *pScreen)
{	
	m_bMouseLock = true;
	_pBackground = new CSprite(pScreen,"HELP_SCREEN");

	_pExitButton = new CButton(pScreen,"BUTTON_MENU_SETTINGS");

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
