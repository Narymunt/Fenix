#include "eCongratulations.h"


eCongratulations::eCongratulations()
{
	_pBackground = NULL;
	_pBlack = NULL;	

	_ulTimerStart = 0;

	_isActive = false;

}


eCongratulations::~eCongratulations()
{
	Close();
}


void eCongratulations::Open(CScreen *pScreen)
{	
	_pBackground = new CSprite("data/e_mmenu.jpg");

	_pBlack = new CSprite("data/fc1.png");

	_isActive = true;
}


void eCongratulations::Close(void)
{
	SafeDelete(_pBackground);
	SafeDelete(_pBlack);
	
	_isActive = false;
}


int eCongratulations::Render(unsigned long ulTimer, CMouse *pMouse)
{
	int iReturn=0;

	if (_ulTimerStart == 0)
		_ulTimerStart = ulTimer;

	_pBackground->Render();		

	return iReturn;
}


//end
