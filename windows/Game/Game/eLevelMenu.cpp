#include "eLevelMenu.h"

eLevelMenu::eLevelMenu()
{
	m_pBackground = NULL;

	m_ulTimerStart =0;

	for (int i=0; i<7; i++)
		m_pLevel[i] = NULL;

	m_pButtonBack = NULL;
	m_pButtonEndGame = NULL;

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

	m_pLevel[0] = new CButton("data/level01.png","data/level01.png","data/level01.png");
	m_pLevel[0]->SetPosition(128,64-32);
	m_pLevel[0]->SetHotCoords(128,32,128+128,32+128);

	m_pLevel[1] = new CButton("data/level02.png","data/level02.png","data/level02.png");
	m_pLevel[1]->SetPosition(256+64,64-32);
	m_pLevel[1]->SetHotCoords(256+64,64-32,256+64+128,64-32+128);

	m_pLevel[2] = new CButton("data/level03.png","data/level03.png","data/level03.png");
	m_pLevel[2]->SetPosition(448+64,64-32);
	m_pLevel[2]->SetHotCoords(448+64,64-32,448+64+128,64-32+128);

	m_pLevel[3] = new CButton("data/level04.png","data/level04.png","data/level04.png");
	m_pLevel[3]->SetPosition(640+64,64-32);
	m_pLevel[3]->SetHotCoords(640+64,64-32,640+64+128,64-32+128);

	m_pLevel[4] = new CButton("data/level05.png","data/level05.png","data/level05.png");
	m_pLevel[4]->SetPosition(128,256-32);
	m_pLevel[4]->SetHotCoords(128,256-32,128+128,256-32+128);

	m_pLevel[5] = new CButton("data/level06.png","data/level06.png","data/level06.png");
	m_pLevel[5]->SetPosition(256+64,256-32);
	m_pLevel[5]->SetHotCoords(256+64,256-32,256+64+128,256-32+128);

	m_pLevel[6] = new CButton("data/level07.png","data/level07.png","data/level07.png");
	m_pLevel[6]->SetPosition(448+64,256-32);
	m_pLevel[6]->SetHotCoords(448+64,256-32,448+64+128,256-32+128);

	m_pButtonBack = new CButton("data/no_clicked.png","data/no.png","data/no_over.png");
	m_pButtonBack->SetPosition(448,600);
	m_pButtonBack->SetHotCoords(448,600,448+64,600+64);

	m_pButtonEndGame = new CButton("data/a00_l.png","data/a00_u.png","data/a00_l.png");
	m_pButtonEndGame->SetPosition(448,460);
	m_pButtonEndGame->SetHotCoords(448,460,448+64,460+64);

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
	SafeDelete(m_pButtonEndGame);
	
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

	if (m_pButtonBack->Render(pMouse)==ON_LEFT)
		iReturn = -1;

	if (m_ulMap>=7)		// odblokowane wszysktie etapy
	{
		if (m_pButtonEndGame->Render(pMouse)==ON_LEFT)
			iReturn = 100;	// koniec gry
	}

	return iReturn;
}


int eLevelMenu::iGetCurrentLevel(void)
{
	return (int)m_ucCurrentLevel;
}
//end
