#include "eHelp.h"

// konstruktor, tutaj pakujemy najmniej jak tylko możliwe

eHelp::eHelp(int iOS) :
_pBackground(NULL), _pExitButton(NULL)
{
    _isActive = false;
    _iOS = iOS;
}

eHelp::~eHelp()
{
    if (_isActive)
        Close();
}

void eHelp::Open(void)
{
    
    _pBackground = new CSprite((char*)"e_help",_iOS);

    if (_iOS == IPAD_HD)
    {
        _pExitButton = new CButton((char*)"menu_over256.png",(char*)"menu_click256.png",(char*)"menu_static256.png",0,0,256,256);
        _pExitButton->SetPosition(1024-128,1150);
        _pExitButton->SetHotCoords(1024-128,1150,1024+128,1150+256);
    }
    else if (_iOS == IPAD)
    {
        _pExitButton = new CButton((char*)"menu_over.png",(char*)"menu_click.png",(char*)"menu_static.png",0,0,128,128);
        _pExitButton->SetPosition(512-64,580);
        _pExitButton->SetHotCoords(512-64,580,512+64,580+128);
    }
    else if (_iOS == IPHONE4)
    {
        _pExitButton = new CButton((char*)"menu_over.png",(char*)"menu_click.png",(char*)"menu_static.png",0,0,128,128);
        _pExitButton->SetPosition(480-64,480);
        _pExitButton->SetHotCoords(480-64,480,480+64,480+128);
    }
    else if (_iOS == IPHONE5)
    {
        _pExitButton = new CButton((char*)"menu_over.png",(char*)"menu_click.png",(char*)"menu_static.png",0,0,128,128);
        _pExitButton->SetPosition(568-64,480);
        _pExitButton->SetHotCoords(568-64,480,568+64,480+128);
    }

    _isActive = true;
    _isMouseLock = true;
}

void eHelp::Close(void)
{
    SafeDelete(_pBackground);
    SafeDelete(_pExitButton);
    
    _isActive = false;
    _isMouseLock = true;
}

int eHelp::Render(CTouch *pTouch, unsigned long ulTimer)
{
    
    if (!pTouch->isPressed())
        _isMouseLock = false;
    
    _pBackground->Render();

    if (_pExitButton->Render(pTouch)==ON_LEFT && !_isMouseLock)
        return 1;

    
    return 0;   // nie rob nic
}

