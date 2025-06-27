#include "eCongratulations.h"

// konstruktor, tutaj pakujemy najmniej jak tylko możliwe

eCongratulations::eCongratulations(int iOS) :
_pBackground(NULL), _pExitButton(NULL), _pBlack(NULL), _pFont(NULL)
{
    _isActive = false;
    _iOS = iOS;
}

eCongratulations::~eCongratulations()
{
    if (_isActive)
        Close();
}

void eCongratulations::Open(CScreen *pScreen)
{
    
    _pBackground = new CSprite((char*)"e_end",_iOS);
    _pBlack = new CSprite((char*)"black_100",pScreen->iOS());
    
    if (_iOS == IPAD_HD)
    {
        _pExitButton = new CButton((char*)"menu_over256.png",(char*)"menu_click256.png",(char*)"menu_static256.png",0,0,256,256);
        _pExitButton->SetPosition(1600,1150);
        _pExitButton->SetHotCoords(1600,1150,1600+256,1150+256);
    }
    else if (_iOS == IPAD)
    {
        _pExitButton = new CButton((char*)"menu_over.png",(char*)"menu_click.png",(char*)"menu_static.png",0,0,128,128);
        _pExitButton->SetPosition(780,580);
        _pExitButton->SetHotCoords(780,580,780+128,580+128);
    }
    else if (_iOS == IPHONE4)
    {
        _pExitButton = new CButton((char*)"menu_over.png",(char*)"menu_click.png",(char*)"menu_static.png",0,0,128,128);
        _pExitButton->SetPosition(660,480);
        _pExitButton->SetHotCoords(660,480,660+128,480+128);
    }
    else if (_iOS == IPHONE5)
    {
        _pExitButton = new CButton((char*)"menu_over.png",(char*)"menu_click.png",(char*)"menu_static.png",0,0,128,128);
        _pExitButton->SetPosition(790,480);
        _pExitButton->SetHotCoords(790,480,790+128,480+128);
    }

    _pFont = new CSpriteFont();
    
    _pScreen = pScreen;
    _ulTimerStart = 0;
    _isActive = true;
    _isMouseLock = true;
}

void eCongratulations::Close(void)
{
    SafeDelete(_pBackground);
    SafeDelete(_pExitButton);
    SafeDelete(_pBlack);
    SafeDelete(_pFont);
    
    _isActive = false;
    _isMouseLock = true;
}

int eCongratulations::Render(CTouch *pTouch, unsigned long ulTimer)
{
    
    if (!pTouch->isPressed())
        _isMouseLock = false;

	if (_ulTimerStart == 0)
		_ulTimerStart = ulTimer;
    
    _pBackground->Render();
    
	if (ulTimer - _ulTimerStart < 1000)
	{
		_pBlack->fAlfa(1-(ulTimer - _ulTimerStart)*0.001f);
		_pBlack->Render();
	}
    
    if (_pScreen->iOS() == IPAD)
	{
		if ((ulTimer % 20000) < 5000)
		{
			_pFont->Print(-150, 0, 1, 0.1f, 0.1f,(char*)"congratulations");
			_pFont->Print(-150, 100, 1, 0.1f, 0.1f,(char*) "you have found atlantis");
		}
		else if ((ulTimer % 20000) < 10000)
		{
			_pFont->Print(-150, 0, 1, 0.1f, 0.1f,(char*) "get all troophys");
			_pFont->Print(-150, 100, 1, 0.1f, 0.1f,(char*) "to unlock new game modes");
		}
		else if ((ulTimer % 20000) < 15000)
		{
			_pFont->Print(-150, 0, 1, 0.1f, 0.1f,(char*) "get all highscores");
			_pFont->Print(-150, 100, 1, 0.1f, 0.1f,(char*) "to unlock new areas");
		}
		else
		{
			_pFont->Print(-150, 0, 1, 0.1f, 0.1f,(char*) "and go for a walk");
			_pFont->Print(-150, 100, 1, 0.1f, 0.1f,(char*) "it is good for health");
		}
	}
	else if (_pScreen->iOS() == IPHONE4)
	{
		if ((ulTimer % 20000) < 5000)
		{
			_pFont->Print(-175, 0, 1, 0.1f, 0.1f,(char*) "congratulations");
			_pFont->Print(-175, 100, 1, 0.1f, 0.1f,(char*) "you have found atlantis");
		}
		else if ((ulTimer % 20000) < 10000)
		{
			_pFont->Print(-175, 0, 1, 0.1f, 0.1f,(char*) "get all troophys");
			_pFont->Print(-175, 100, 1, 0.1f, 0.1f,(char*) "to unlock new game modes");
		}
		else if ((ulTimer % 20000) < 15000)
		{
			_pFont->Print(-175, 0, 1, 0.1f, 0.1f,(char*) "get all highscores");
			_pFont->Print(-175, 100, 1, 0.1f, 0.1f,(char*) "to unlock new areas");
		}
		else
		{
			_pFont->Print(-150, 0, 1, 0.1f, 0.1f,(char*) "and go for a walk");
			_pFont->Print(-150, 100, 1, 0.1f, 0.1f,(char*) "it is good for health");
		}
	}
	else if (_pScreen->iOS() == IPHONE5)
	{
		if ((ulTimer % 20000) < 5000)
		{
			_pFont->Print(-175, 0, 1, 0.1f, 0.1f,(char*) "congratulations");
			_pFont->Print(-175, 100, 1, 0.1f, 0.1f,(char*) "you have found atlantis");
		}
		else if ((ulTimer % 20000) < 10000)
		{
			_pFont->Print(-175, 0, 1, 0.1f, 0.1f,(char*) "get all troophys");
			_pFont->Print(-175, 100, 1, 0.1f, 0.1f,(char*) "to unlock new game modes");
		}
		else if ((ulTimer % 20000) < 15000)
		{
			_pFont->Print(-175, 0, 1, 0.1f, 0.1f,(char*) "get all highscores");
			_pFont->Print(-175, 100, 1, 0.1f, 0.1f,(char*) "to unlock new areas");
		}
		else
		{
			_pFont->Print(-150, 0, 1, 0.1f, 0.1f,(char*) "and go for a walk");
			_pFont->Print(-150, 100, 1, 0.1f, 0.1f,(char*) "it is good for health");
		}
	}
	else if (_pScreen->iOS() == IPAD_HD)
	{
		if ((ulTimer % 20000) < 5000)
		{
			_pFont->Print(-175, 300, 1, 0.2f, 0.2f,(char*) "congratulations");
			_pFont->Print(-175, 500, 1, 0.2f, 0.2f,(char*) "you have found atlantis");
		}
		else if ((ulTimer % 20000) < 10000)
		{
			_pFont->Print(-175, 300, 1, 0.2f, 0.2f,(char*) "get all troophys");
			_pFont->Print(-175, 500, 1, 0.2f, 0.2f,(char*) "to unlock new game modes");
		}
		else if ((ulTimer % 20000) < 15000)
		{
			_pFont->Print(-175, 300, 1, 0.2f, 0.2f,(char*) "get all highscores");
			_pFont->Print(-175, 500, 1, 0.2f, 0.2f,(char*) "to unlock new areas");
		}
		else
		{
			_pFont->Print(-150, 300, 1, 0.2f, 0.2f,(char*) "and go for a walk");
			_pFont->Print(-150, 500, 1, 0.2f, 0.2f,(char*) "it is good for health");
		}
	}

    
    if (_pExitButton->Render(pTouch)==ON_LEFT && !_isMouseLock)
        return 1;

    
    return 0;   // nie rob nic
}

