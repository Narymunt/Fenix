#include "eSettings.h"

eSettings::eSettings()
{
	m_pBackground = NULL;
	m_ulTimerStart =0;
	m_pExitButton = NULL;

	m_pCheckboxMSX = NULL;
	m_pCheckboxSFX = NULL;

	_pFont = NULL;

	// ustaw znacznik, ze dane nie sa jeszcze wczytane
	_isActive = false;
	m_bMouseLock = true;
}


eSettings::~eSettings()
{
	Close();
}


void eSettings::Open(CScreen *pScreen)
{	
	CGameSettings	*pSetup;

	m_pBackground = new CSprite(pScreen,"SETTINGS_SCREEN");

	m_pExitButton = new CButton(pScreen,"BUTTON_MENU_SETTINGS");

	// przyciski z opcjami

	if (pScreen->iSizeX()==1024 && pScreen->iSizeY()==768)
	{
		m_pCheckboxMSX = new CCheckbox(pScreen,false,300,150,300,150,300+128,150+128,"CHECK_ON","CHECK_OVER_ON","CHECK_OFF","CHECK_OVER_OFF");
		m_pCheckboxSFX = new CCheckbox(pScreen,false,300,300,300,300,300+128,300+128,"CHECK_ON","CHECK_OVER_ON","CHECK_OFF","CHECK_OVER_OFF");
		_iMSXFontX = 450; _iMSXFontY = 200;
		_iSFXFontX = 450; _iSFXFontY = 350;
	}
	else if (pScreen->iSizeX() == 1366 && pScreen->iSizeY() == 768)
	{
		m_pCheckboxMSX = new CCheckbox(pScreen, false, 500, 150, 500, 150, 500 + 128, 450 + 128, "CHECK_ON", "CHECK_OVER_ON", "CHECK_OFF", "CHECK_OVER_OFF");
		m_pCheckboxSFX = new CCheckbox(pScreen, false, 500, 300, 500, 300, 500 + 128, 400 + 128, "CHECK_ON", "CHECK_OVER_ON", "CHECK_OFF", "CHECK_OVER_OFF");
		_iMSXFontX = 650; _iMSXFontY = 200;
		_iSFXFontX = 650; _iSFXFontY = 350;
	}
	else if (pScreen->iSizeX() == 1920)
	{
		m_pCheckboxMSX = new CCheckbox(pScreen, false, 600, 150, 600, 150, 600 + 256, 150 + 256, "CHECK_ON", "CHECK_OVER_ON", "CHECK_OFF", "CHECK_OVER_OFF");
		m_pCheckboxSFX = new CCheckbox(pScreen, false, 600, 450, 600, 450, 600 + 256, 450 + 256, "CHECK_ON", "CHECK_OVER_ON", "CHECK_OFF", "CHECK_OVER_OFF");
		_iMSXFontX = 950; _iMSXFontY = 250;
		_iSFXFontX = 950; _iSFXFontY = 550;
	}
	else if (pScreen->iSizeX() == 2560)
	{
		m_pCheckboxMSX = new CCheckbox(pScreen, false, 950, 250, 950, 150, 950 + 256, 250 + 256, "CHECK_ON", "CHECK_OVER_ON", "CHECK_OFF", "CHECK_OVER_OFF");
		m_pCheckboxSFX = new CCheckbox(pScreen, false, 950, 550, 950, 450, 950 + 256, 550 + 256, "CHECK_ON", "CHECK_OVER_ON", "CHECK_OFF", "CHECK_OVER_OFF");
		_iMSXFontX = 1300; _iMSXFontY = 350;
		_iSFXFontX = 1300; _iSFXFontY = 650;
	}



	pSetup = new CGameSettings();
	pSetup->bLoad();

	m_pCheckboxMSX->Set(pSetup->isMSX());
	m_pCheckboxSFX->Set(pSetup->isSFX());
	_cLanguage = pSetup->cSelectedLanguage();
	delete pSetup;

	m_bMouseLock = true;	// blokada myszki, zeby nie przenosic klikniecia z poprzedniej planszy na obecna

	_pFont = new CSpriteFont(pScreen);
	
	_pScreen = pScreen;

	_isActive = true;	// dane wczytane
}


void eSettings::Close(void)
{

	if (m_pBackground!=NULL)
	{
		CGameSettings *pSetup;

		pSetup = new CGameSettings();
		pSetup->isMSX(m_pCheckboxMSX->isSet());
		pSetup->isSFX(m_pCheckboxSFX->isSet());
		pSetup->cSelectedLanguage(_cLanguage);
		pSetup->bSave();
		delete pSetup;
	}

	SafeDelete(m_pBackground);
	SafeDelete(m_pExitButton);
	SafeDelete(m_pCheckboxMSX);
	SafeDelete(m_pCheckboxSFX);

	SafeDelete(_pFont);

	_isActive = false;
}


int eSettings::Render(unsigned long ulTimer, CMouse *pMouse)
{
	float fSize;

	if (!pMouse->isLeft())
		m_bMouseLock = false;

	m_pBackground->Render();

	_pScreen->iSizeX() < 1500 ? fSize = 0.05f : fSize = 0.1f;
	
	if (m_pCheckboxMSX->isSet())
	{
		_pFont->Print(_iMSXFontX,_iMSXFontY,1,fSize,fSize,"music on");
	}
	else
	{
		_pFont->Print(_iMSXFontX,_iMSXFontY,1,fSize,fSize,"music off");
	}

	if (m_pCheckboxSFX->isSet())
	{
		_pFont->Print(_iSFXFontX,_iSFXFontY,1,fSize,fSize,"effects on");
	}
	else
	{
		_pFont->Print(_iSFXFontX,_iSFXFontY,1,fSize,fSize,"effects off");
	}

	m_pCheckboxMSX->Render(ulTimer,pMouse);
	m_pCheckboxSFX->Render(ulTimer,pMouse);

	if (m_pExitButton->Render(pMouse)==ON_LEFT && !m_bMouseLock)		
		return 1;

	return 0;
}


//end
