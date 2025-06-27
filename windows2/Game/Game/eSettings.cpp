#include "eSettings.h"

eSettings::eSettings()
{
	m_pBackground = NULL;
	m_ulTimerStart =0;
	m_pExitButton = NULL;

	m_pCheckboxMSX = NULL;
	m_pCheckboxSFX = NULL;

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

	m_pExitButton = new CButton("data/x1.png","data/x2.png","data/x3.png");
	m_pExitButton->SetPosition(128,64-32);
	m_pExitButton->SetHotCoords(128,32,128+128,32+128);

	m_pCheckboxMSX = new CCheckbox(false,100,100,100,100,200,200,"data/check_on.png","data/check_off.png");
	m_pCheckboxSFX = new CCheckbox(false,100,400,100,400,200,500,"data/check_on.png","data/check_off.png");

	pSetup = new CGameSettings();
	pSetup->bLoad();

	m_pCheckboxMSX->Set(pSetup->isMSX());
	m_pCheckboxSFX->Set(pSetup->isSFX());

	delete pSetup;

	m_bMouseLock = true;	// blokada myszki, zeby nie przenosic klikniecia z poprzedniej planszy na obecna

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

	_isActive = false;
}


int eSettings::Render(unsigned long ulTimer, CMouse *pMouse)
{
	if (!pMouse->isLeft())
		m_bMouseLock = false;

	m_pBackground->Render();

	m_pCheckboxMSX->Render(ulTimer,pMouse);
	m_pCheckboxSFX->Render(ulTimer,pMouse);

	if (m_pExitButton->Render(pMouse)==ON_LEFT && !m_bMouseLock)		
		return 1;

	return 0;
}


//end
