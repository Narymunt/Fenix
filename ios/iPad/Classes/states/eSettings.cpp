// main class

#include "eSettings.h"

// konstruktor, tutaj pakujemy najmniej jak tylko możliwe

eSettings::eSettings(int iOS) :
_pBackground(NULL), _pExitButton(NULL), _pFont(NULL)
{
    _isActive = false;
    _iOS = iOS;
}

eSettings::~eSettings()
{
    if (_isActive)
        Close();
}

void eSettings::Open(void)
{
    CGameSettings *pSetup;
    
    _pBackground = new CSprite((char*)"e_settings",_iOS);

    if (_iOS == IPAD_HD)
    {
        _pExitButton = new CButton((char*)"menu_over256.png",(char*)"menu_click256.png",(char*)"menu_static256.png",0,0,256,256);
        _pExitButton->SetPosition(1600,1150);
        _pExitButton->SetHotCoords(1600,1150,1600+256,1150+256);
        
		m_pCheckboxMSX = new CCheckbox(false,600,300,600,300,600+256,300+256,(char*)"check_on_256.png",(char*)"check_over_on_256.png",(char*)"check_off_256.png",(char*)"check_over_off_256.png");
		m_pCheckboxSFX = new CCheckbox(false,600,600,600,600,600+256,600+256,(char*)"check_on_256.png",(char*)"check_over_on_256.png",(char*)"check_off_256.png",(char*)"check_over_off_256.png");
        
        _iMSXFontX = 700; _iMSXFontY = 200;
        _iSFXFontX = 700; _iSFXFontY = 500;
    }
    else if (_iOS == IPAD)
    {
        _pExitButton = new CButton((char*)"menu_over.png",(char*)"menu_click.png",(char*)"menu_static.png",0,0,128,128);
        _pExitButton->SetPosition(780,580);
        _pExitButton->SetHotCoords(780,580,780+128,580+128);
        
        _iMSXFontX = 250; _iMSXFontY = -50;
        _iSFXFontX = 250; _iSFXFontY = 100;
        
		m_pCheckboxMSX = new CCheckbox(false,300,150,300,150,300+128,150+128,(char*)"check_on_128.png",(char*)"check_over_on_128.png",(char*)"check_off_128.png",(char*)"check_over_off_128.png");
		m_pCheckboxSFX = new CCheckbox(false,300,300,300,300,300+128,300+128,(char*)"check_on_128.png",(char*)"check_over_on_128.png",(char*)"check_off_128.png",(char*)"check_over_off_128.png");
        
    }
    else if (_iOS == IPHONE4)
    {
        _pExitButton = new CButton((char*)"menu_over.png",(char*)"menu_click.png",(char*)"menu_static.png",0,0,128,128);
        _pExitButton->SetPosition(660,480);
        _pExitButton->SetHotCoords(660,480,660+128,480+128);

		m_pCheckboxMSX = new CCheckbox(false,300,130,300,130,300+128,130+128,(char*)"check_on_128.png",(char*)"check_over_on_128.png",(char*)"check_off_128.png",(char*)"check_over_off_128.png");
		m_pCheckboxSFX = new CCheckbox(false,300,270,300,270,300+128,270+128,(char*)"check_on_128.png",(char*)"check_over_on_128.png",(char*)"check_off_128.png",(char*)"check_over_off_128.png");
        
        _iMSXFontX = 200; _iMSXFontY = -50;
        _iSFXFontX = 200; _iSFXFontY = 70;
    }
    else if (_iOS == IPHONE5)
    {
        _pExitButton = new CButton((char*)"menu_over.png",(char*)"menu_click.png",(char*)"menu_static.png",0,0,128,128);
        _pExitButton->SetPosition(790,480);
        _pExitButton->SetHotCoords(790,480,790+128,480+128);

        m_pCheckboxMSX = new CCheckbox(false,400,130,400,130,400+128,130+128,(char*)"check_on_128.png",(char*)"check_over_on_128.png",(char*)"check_off_128.png",(char*)"check_over_off_128.png");
		m_pCheckboxSFX = new CCheckbox(false,400,270,400,270,400+128,270+128,(char*)"check_on_128.png",(char*)"check_over_on_128.png",(char*)"check_off_128.png",(char*)"check_over_off_128.png");

        _iMSXFontX = 300; _iMSXFontY = -50;
        _iSFXFontX = 300; _iSFXFontY = 70;
    }

    pSetup = new CGameSettings();
	pSetup->bLoad();
    
	m_pCheckboxMSX->Set(pSetup->isMSX());
	m_pCheckboxSFX->Set(pSetup->isSFX());
	_cLanguage = pSetup->cSelectedLanguage();
	delete pSetup;
    
    _pFont = new CSpriteFont();

    _isActive = true;
    _isMouseLock = true;
}

void eSettings::Close(void)
{
    
    if (_pBackground!=NULL)
	{
		CGameSettings *pSetup;
        
		pSetup = new CGameSettings();
		pSetup->isMSX(m_pCheckboxMSX->isSet());
		pSetup->isSFX(m_pCheckboxSFX->isSet());
		pSetup->cSelectedLanguage(_cLanguage);
		pSetup->bSave();
		delete pSetup;
	}
    
    SafeDelete(_pBackground);
    SafeDelete(_pExitButton);
    SafeDelete(_pFont);
    
    _isActive = false;
    _isMouseLock = true;
}

int eSettings::Render(CTouch *pTouch, unsigned long ulTimer)
{
    
    float fSize;
    
    if (!pTouch->isPressed())
        _isMouseLock = false;
    
    _pBackground->Render();
    
    _iOS == IPAD_HD ? fSize = 0.1f : fSize = 0.055f;
    
	if (m_pCheckboxMSX->isSet())
	{
		_pFont->Print(_iMSXFontX,_iMSXFontY,1,fSize,fSize,(char*)"music on");
	}
	else
	{
		_pFont->Print(_iMSXFontX,_iMSXFontY,1,fSize,fSize,(char*)"music off");
	}
    
	if (m_pCheckboxSFX->isSet())
	{
		_pFont->Print(_iSFXFontX,_iSFXFontY,1,fSize,fSize,(char*)"effects on");
	}
	else
	{
		_pFont->Print(_iSFXFontX,_iSFXFontY,1,fSize,fSize,(char*)"effects off");
	}
    
	m_pCheckboxMSX->Render(ulTimer,pTouch);
	m_pCheckboxSFX->Render(ulTimer,pTouch);

    if (_pExitButton->Render(pTouch)==ON_LEFT && !_isMouseLock)
        return 1;

    
    return 0;   // nie rob nic
}

