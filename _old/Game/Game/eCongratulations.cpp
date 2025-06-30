#include "eCongratulations.h"


eCongratulations::eCongratulations()
{
	_pBackground = NULL;
	_pBlack = NULL;	

	_pExitButton = NULL;

	_ulTimerStart = 0;
	
	_pFont = NULL;

	_isActive = false;

}


eCongratulations::~eCongratulations()
{
	Close();
}


void eCongratulations::Open(CScreen *pScreen)
{	
	_pBackground = new CSprite(pScreen,"END_SCREEN");

	_pBlack = new CSprite(pScreen,"GFX_BLACK100_SCREEN");

	_pExitButton = new CButton(pScreen, "BUTTON_OK_PROFILE");
	
	if (pScreen->iSizeX() < 1500)
	{
		_pExitButton->SetHotCoords((pScreen->iSizeX() / 2) - 64, pScreen->iSizeY() - 128, (pScreen->iSizeX() / 2) + 64, pScreen->iSizeY());
	}
	else
	{
		_pExitButton->SetHotCoords((pScreen->iSizeX() / 2) - 128, pScreen->iSizeY() - 256, (pScreen->iSizeX() / 2) + 128, pScreen->iSizeY());
	}

	_ulTimerStart = 0;

	_pFont = new CSpriteFont(pScreen);

	_isMouseLock = true;
	_pScreen = pScreen;
	_isActive = true;
}


void eCongratulations::Close(void)
{
	SafeDelete(_pBackground);
	SafeDelete(_pBlack);
	SafeDelete(_pExitButton);
	SafeDelete(_pFont);

	_isActive = false;
}


int eCongratulations::Render(unsigned long ulTimer, CMouse *pMouse)
{
	int iReturn=0;

	if (!pMouse->isLeft())
		_isMouseLock = false;

	if (_ulTimerStart == 0)
		_ulTimerStart = ulTimer;

	_pBackground->Render();		

	if (ulTimer - _ulTimerStart < 1000)
	{
		_pBlack->fAlfa(1-(ulTimer - _ulTimerStart)*0.001f);
		_pBlack->Render();
	}

	if (_pScreen->iSizeX() == 1024)
	{
		if ((ulTimer % 20000) < 5000)
		{
			_pFont->Print(250, 300, 1, 0.1f, 0.1f, "congratulations");
			_pFont->Print(64, 400, 1, 0.1f, 0.1f, "you have found atlantis");
		}
		else if ((ulTimer % 20000) < 10000)
		{
			_pFont->Print(64, 300, 1, 0.1f, 0.1f, "get all troophys");
			_pFont->Print(64, 400, 1, 0.1f, 0.1f, "to unlock new game modes");
		}
		else if ((ulTimer % 20000) < 15000)
		{
			_pFont->Print(64, 300, 1, 0.1f, 0.1f, "get all highscores");
			_pFont->Print(64, 400, 1, 0.1f, 0.1f, "to unlock new areas");
		}
		else
		{
			_pFont->Print(64, 300, 1, 0.1f, 0.1f, "and go for a walk");
			_pFont->Print(64, 400, 1, 0.1f, 0.1f, "it is good for health");
		}
	} 
	else if (_pScreen->iSizeX() == 1366)
	{
		if ((ulTimer % 20000) < 5000)
		{
			_pFont->Print(400, 300, 1, 0.1f, 0.1f, "congratulations");
			_pFont->Print(200, 400, 1, 0.1f, 0.1f, "you have found atlantis");
		}
		else if ((ulTimer % 20000) < 10000)
		{
			_pFont->Print(264, 300, 1, 0.1f, 0.1f, "get all troophys");
			_pFont->Print(164, 400, 1, 0.1f, 0.1f, "to unlock new game modes");
		}
		else if ((ulTimer % 20000) < 15000)
		{
			_pFont->Print(300, 300, 1, 0.1f, 0.1f, "get all highscores");
			_pFont->Print(300, 400, 1, 0.1f, 0.1f, "to unlock new areas");
		}
		else
		{
			_pFont->Print(350, 300, 1, 0.1f, 0.1f, "and go for a walk");
			_pFont->Print(300, 400, 1, 0.1f, 0.1f, "it is good for health");
		}
	}
	else if (_pScreen->iSizeX() == 1920)
	{
		if ((ulTimer % 20000) < 5000)
		{
			_pFont->Print(400, 300, 1, 0.15f, 0.15f, "congratulations");
			_pFont->Print(200, 400, 1, 0.15f, 0.15f, "you have found atlantis");
		}
		else if ((ulTimer % 20000) < 10000)
		{
			_pFont->Print(264, 300, 1, 0.15f, 0.15f, "get all troophys");
			_pFont->Print(164, 400, 1, 0.15f, 0.15f, "to unlock new game modes");
		}
		else if ((ulTimer % 20000) < 15000)
		{
			_pFont->Print(300, 300, 1, 0.15f, 0.15f, "get all highscores");
			_pFont->Print(300, 400, 1, 0.15f, 0.15f, "to unlock new areas");
		}
		else
		{
			_pFont->Print(350, 300, 1, 0.15f, 0.15f, "and go for a walk");
			_pFont->Print(300, 400, 1, 0.15f, 0.15f, "it is good for health");
		}
	}
	else if (_pScreen->iSizeX() == 2560)
	{
		if ((ulTimer % 20000) < 5000)
		{
			_pFont->Print(400, 300, 1, 0.25f, 0.25f, "congratulations");
			_pFont->Print(200, 400, 1, 0.25f, 0.25f, "you have found atlantis");
		}
		else if ((ulTimer % 20000) < 10000)
		{
			_pFont->Print(264, 300, 1, 0.25f, 0.25f, "get all troophys");
			_pFont->Print(164, 400, 1, 0.25f, 0.25f, "to unlock new game modes");
		}
		else if ((ulTimer % 20000) < 15000)
		{
			_pFont->Print(300, 300, 1, 0.25f, 0.25f, "get all highscores");
			_pFont->Print(300, 400, 1, 0.25f, 0.25f, "to unlock new areas");
		}
		else
		{
			_pFont->Print(350, 300, 1, 0.25f, 0.25f, "and go for a walk");
			_pFont->Print(300, 400, 1, 0.25f, 0.25f, "it is good for health");
		}
	}



	if (_pExitButton->Render(pMouse) == ON_LEFT && !_isMouseLock)
		iReturn = 1;

	return iReturn;
}


//end
