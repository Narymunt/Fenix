#include "eLevelMenu.h"

eLevelMenu::eLevelMenu()
{
	m_pBackground = NULL;

	m_ulTimerStart =0;

	for (int i=0; i<7; i++)
		m_pLevel[i] = NULL;

	m_pButtonBack = NULL;

	// ustaw znacznik, ze dane nie sa jeszcze wczytane
	_isActive = false;
	m_ucCurrentLevel = 1;

}


eLevelMenu::~eLevelMenu()
{
	Close();
}


void eLevelMenu::Open(CScreen *pScreen)
{	
	CProfile	*pUserProfile;	// odczytujemy info, ktore etapy sa dostepne

	m_pBackground = new CSprite(pScreen,"GFX_LEVEL_SCREEN");

	m_pLevel[0] = new CButton(pScreen,"BUTTON_LEVEL01");
	m_pLevel[1] = new CButton(pScreen,"BUTTON_LEVEL02");
	m_pLevel[2] = new CButton(pScreen,"BUTTON_LEVEL03");
	m_pLevel[3] = new CButton(pScreen,"BUTTON_LEVEL04");
	m_pLevel[4] = new CButton(pScreen,"BUTTON_LEVEL05");
	m_pLevel[5] = new CButton(pScreen,"BUTTON_LEVEL06");
	m_pLevel[6] = new CButton(pScreen,"BUTTON_LEVEL07");

	m_pButtonBack = new CButton(pScreen, "BUTTON_MENU_SETTINGS");

	if (pScreen->iSizeX() < 1500)
	{
		m_pButtonBack->SetHotCoords((pScreen->iSizeX() / 2) - 64 + 16, pScreen->iSizeY() - 128 - 50, (pScreen->iSizeX() / 2) + 64 + 16, pScreen->iSizeY() - 50);
	}
	else if (pScreen->iSizeX() == 2560)
	{
		m_pButtonBack->SetHotCoords((pScreen->iSizeX() / 2) - 128 + 16, pScreen->iSizeY() - 256 - 80, (pScreen->iSizeX() / 2) + 128 + 16, pScreen->iSizeY() - 80);
	}
	else
	{
		m_pButtonBack->SetHotCoords((pScreen->iSizeX() / 2) -128 + 16, pScreen->iSizeY() - 256 - 50, (pScreen->iSizeX() / 2) + 128 + 16, pScreen->iSizeY() - 50);
	}

	pUserProfile = new CProfile("Game.cfg");
	pUserProfile->bLoad();

	m_ulMap = pUserProfile->ulMap();

	delete pUserProfile;

	m_bMouseLock = true;	// blokada myszki, zeby nie przenosic klikniecia z poprzedniej planszy na obecna
	_isActive = true;
}

void eLevelMenu::Close(void)
{
	SafeDelete(m_pBackground);

	for (int i=0; i<7; i++)
		SafeDelete(m_pLevel[i]);

	SafeDelete(m_pButtonBack);
	
	_isActive = false;
}


int eLevelMenu::Render(unsigned long ulTimer, CMouse *pMouse)
{
	int iReturn;

	iReturn = 0;
	
	if (!pMouse->isLeft())
		m_bMouseLock = false;

	if (m_ulTimerStart == 0)
		m_ulTimerStart = ulTimer;

	m_pBackground->Render();

	for (int i=0; i<7; i++)
	{
		if (i<=m_ulMap)	// czy ten etap jest dostepny
		{
			if (m_pLevel[i]->Render(pMouse)==ON_LEFT)
			{
				m_ucCurrentLevel = i+1;
		
				if (!m_bMouseLock) 
					iReturn = i+1; 
			}			
		}
	}

	if (m_pButtonBack->Render(pMouse)==ON_LEFT && !m_bMouseLock)
		iReturn = -1;

	return iReturn;
}


int eLevelMenu::iGetCurrentLevel(void)
{
	return (int)m_ucCurrentLevel;
}
//end
