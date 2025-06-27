#include "eCredits.h"

eCredits::eCredits()
{
	_pBackground = NULL;
	_pExitButton = NULL;
	_pImage = NULL;
	
	_ulTimerStart = 0;

	m_bMouseLock = true;

	_isActive = false;

}


eCredits::~eCredits()
{
	Close();
}


void eCredits::Open(CScreen *pScreen)
{	
	m_bMouseLock = true;

	_pBackground = new CSprite(pScreen,"CREDITS_SCREEN");
	_pImage = new CSprite(pScreen,"CREDITS");

	_pExitButton = new CButton(pScreen,"BUTTON_MENU_SETTINGS");

	_ulTimerStart = 0;

	_pScreen = pScreen;
	_isActive = true;
}


void eCredits::Close(void)
{
	SafeDelete(_pBackground);
	SafeDelete(_pImage);

	SafeDelete(_pExitButton);
	
	_isActive = false;
}


int eCredits::Render(unsigned long ulTimer, CMouse *pMouse)
{
	int iReturn=0;

	if (!pMouse->isLeft())
		m_bMouseLock = false;

	if ( (_ulTimerStart == 0) || (((ulTimer-_ulTimerStart)*0.1f)>2048) )
		_ulTimerStart = ulTimer;

	_pBackground->Render();		

	_pImage->Position( (_pScreen->iSizeX()/2)-(_pImage->fSizeX()/2), (_pScreen->iSizeY()*1.25f)-((ulTimer-_ulTimerStart)*0.1f));	// scroll do góry
	_pImage->Render();



	if (_pExitButton->Render(pMouse)==ON_LEFT && !m_bMouseLock)		
		return 1;

	return 0;
}


//end
