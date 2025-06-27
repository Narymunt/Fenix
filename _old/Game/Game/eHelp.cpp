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
	
	if (pScreen->iSizeX() < 1500)
	{
		_pExitButton->SetHotCoords(pScreen->iSizeX() / 2 - 64, pScreen->iSizeY() - 128 - 64, pScreen->iSizeX() / 2 + 64, pScreen->iSizeY() - 64 - 64);
	}
	else if (pScreen->iSizeX() == 2560)
	{
		_pExitButton->SetHotCoords(pScreen->iSizeX() / 2 - 128, pScreen->iSizeY() - 256 - 80, pScreen->iSizeX() / 2 + 128, pScreen->iSizeY() - 80);
	}
	else 
	{
		_pExitButton->SetHotCoords(pScreen->iSizeX() / 2 - 128, pScreen->iSizeY() - 256 - 32, pScreen->iSizeX() / 2 + 128, pScreen->iSizeY() - 32 );
	}
	
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
