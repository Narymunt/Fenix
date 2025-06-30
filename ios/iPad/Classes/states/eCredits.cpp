#include "eCredits.h"

// konstruktor, tutaj pakujemy najmniej jak tylko możliwe

eCredits::eCredits(int iOS) :
_pBackground(NULL), _pExitButton(NULL), _pImage(NULL)
{
    _isActive = false;
    _iOS = iOS;
}

eCredits::~eCredits()
{
    if (_isActive)
        Close();
}

void eCredits::Open(void)
{
    
    _pBackground = new CSprite((char*)"e_credits",_iOS);
    _pImage = new CSprite((char*)"credits.png");
    
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

    _ulTimerStart = 0;
    _isActive = true;
    _isMouseLock = true;
}

void eCredits::Close(void)
{
    SafeDelete(_pBackground);
    SafeDelete(_pExitButton);
    SafeDelete(_pImage);
    
    _isActive = false;
    _isMouseLock = true;
}

int eCredits::Render(CTouch *pTouch, unsigned long ulTimer)
{
    int iSizeX, iSizeY;
    
    if (!pTouch->isPressed())
        _isMouseLock = false;

	if ( (_ulTimerStart == 0) || (((ulTimer-_ulTimerStart)*0.1f)>4096) )
		_ulTimerStart = ulTimer;
    
    _pBackground->Render();

    if (_iOS == IPHONE4)
    {
        iSizeX = 960; iSizeY = 640;
    }
    else if (_iOS == IPHONE5)
    {
        iSizeX = 1136; iSizeY = 640;
    }
    else if (_iOS == IPAD)
    {
        iSizeX = 1024; iSizeY = 768;
    }
    else if (_iOS == IPAD_HD)
    {
        iSizeX = 2048; iSizeY = 1536;
    }
    
	_pImage->Position( (iSizeX/2)-(_pImage->fSizeX()/2), (iSizeY*1.25f)-((ulTimer-_ulTimerStart)*0.1f));	// scroll do gÛry
	_pImage->Render();
    
    
    if (_pExitButton->Render(pTouch)==ON_LEFT && !_isMouseLock)
        return 1;

    
    return 0;   // nie rob nic
}

