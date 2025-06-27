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

	if (pScreen->iSizeX()==1024 && pScreen->iSizeY()==600)
	{
		m_pCheckboxMSX = new CCheckbox(pScreen,false,300,100,300,100,300+128,100+128,"CHECK_ON","CHECK_OVER_ON","CHECK_OFF","CHECK_OVER_OFF");
		m_pCheckboxSFX = new CCheckbox(pScreen,false,300,250,300,250,300+128,250+128,"CHECK_ON","CHECK_OVER_ON","CHECK_OFF","CHECK_OVER_OFF");
		_iMSXFontX = 450; _iMSXFontY = 150;
		_iSFXFontX = 450; _iSFXFontY = 300;
	}
/*
	if (pScreen->iSizeX()<1500)
	{
		m_pCheckboxMSX = new CCheckbox(pScreen,false,100,100,100,100,228,228,"CHECK_ON","CHECK_OVER_ON","CHECK_OFF","CHECK_OVER_OFF");
		m_pCheckboxSFX = new CCheckbox(pScreen,false,100,400,100,400,228,528,"CHECK_ON","CHECK_OVER_ON","CHECK_OFF","CHECK_OVER_OFF");
	}
	else
	{
		m_pCheckboxMSX = new CCheckbox(pScreen,false,100,100,100,100,356,356,"CHECK_ON","CHECK_OVER_ON","CHECK_OFF","CHECK_OVER_OFF");
		m_pCheckboxSFX = new CCheckbox(pScreen,false,100,800,100,800,356,800+256,"CHECK_ON","CHECK_OVER_ON","CHECK_OFF","CHECK_OVER_OFF");
	}
*/
	pSetup = new CGameSettings();
	pSetup->bLoad();

	m_pCheckboxMSX->Set(pSetup->isMSX());
	m_pCheckboxSFX->Set(pSetup->isSFX());

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
	if (!pMouse->isLeft())
		m_bMouseLock = false;

	m_pBackground->Render();

	if (m_pCheckboxMSX->isSet())
	{
		_pFont->Print(_iMSXFontX,_iMSXFontY,1,0.05,0.05,"music on");
	}
	else
	{
		_pFont->Print(_iMSXFontX,_iMSXFontY,1,0.05,0.05,"music off");
	}

	if (m_pCheckboxSFX->isSet())
	{
		_pFont->Print(_iSFXFontX,_iSFXFontY,1,0.05,0.05,"effects on");
	}
	else
	{
		_pFont->Print(_iSFXFontX,_iSFXFontY,1,0.05,0.05,"effects off");
	}

	m_pCheckboxMSX->Render(ulTimer,pMouse);
	m_pCheckboxSFX->Render(ulTimer,pMouse);

	if (m_pExitButton->Render(pMouse)==ON_LEFT && !m_bMouseLock)		
		return 1;

	return 0;
}


//end
