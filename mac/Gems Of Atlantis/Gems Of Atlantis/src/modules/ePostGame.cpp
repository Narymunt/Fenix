#include "ePostGame.h"

#pragma warning(disable : 4996)	// sprintf unsafe

ePostGame::ePostGame()
{
	
	// ustaw znacznik, ze dane nie sa jeszcze wczytane
	_isActive = false;

	m_pBackground = NULL;
	m_pScoreBar = NULL;
	m_pLevelBar = NULL;

	for (int i=0; i<10; i++)
		m_pNumber[i] = NULL;

	m_pButtonAgain = NULL;
	m_pButtonMenu = NULL;

	m_pUserProfile = NULL;

	m_bAddedToHighscore = false;	// nie dodano jeszcze nowego wyniku

	m_pFont = NULL;

}


ePostGame::~ePostGame()
{
	Close();
}


void ePostGame::Open(CScreen *pScreen)
{	
	char cBuffer[64];

	_pScreen = pScreen;

	_isActive = true;	// dane wczytane

	m_pBackground = new CSprite(pScreen,"POSTLEVEL_SCREEN");

	m_pScoreBar = new CSprite(pScreen,"BAR_GREEN");
	m_pLevelBar =  new CSprite(pScreen,"BAR_BLUE");

	for (int i=0; i<=9; i++)
	{
		sprintf(cBuffer,"GFX_%d",i);
		m_pNumber[i] = new CSprite(pScreen,cBuffer);
	}

	m_pButtonMenu = new CButton(pScreen, "BUTTON_MENU_POSTGAME");
	m_pButtonAgain = new CButton(pScreen, "BUTTON_START_POSTGAME");

	m_pUserProfile = new CProfile("Game.cfg");
	m_pUserProfile->bLoad();

	m_bAddedToHighscore = false;	// nie dodano jeszcze nowego wyniku

	m_pFont = new CSpriteFont(pScreen);

	_pScreen = pScreen;
	_isMouseLock = true;
	_isActive = true;
}


void ePostGame::Close(void)
{
	SafeDelete(m_pBackground);
	
	SafeDelete(m_pScoreBar);
	SafeDelete(m_pLevelBar);

	for (int i=0; i<10; i++)
	  SafeDelete(m_pNumber[i]);

	SafeDelete(m_pButtonMenu);
	SafeDelete(m_pButtonAgain);

	if (m_pUserProfile!=NULL)
	{
		// sprawdzamy najpierw czy nie powinnismy odblokowac planszy

		if (m_pUserProfile->ulGetLevel()==20)
		{
			if (m_pUserProfile->ulMap()!=8)		// 8 oznacza odblokowanie konca gry
			{
				m_pUserProfile->ulMap(m_pUserProfile->ulMap()+1); // dodajemy nr mapy
			}

			m_pUserProfile->SetScore(0);	// kasujemy punkty
			m_pUserProfile->SetTotalScore(0);
		}
		m_pUserProfile->bSave();
	}

	SafeDelete(m_pUserProfile);
	SafeDelete(m_pFont);

	_isMouseLock = true;
	_isActive = false;
}


int ePostGame::Render(unsigned long ulTimer, CMouse *pMouse)
{
	char cScore[9];
	int	iReturn;
	float	fDest;
	CHighScore *pHighScore;
	CProfile *pProfile;	// musimy pobrac nazwe uzytkownika
	char cUserName[30];
	int	x,y,xx,yy;
	int iBarY;

	iReturn = 0;

	if (!pMouse->isLeft())
		isMouseLock(false);

	m_pBackground->Render();

	if (_pScreen->iSizeX()==1024 && _pScreen->iSizeY()==600)
	{
		x = 140; xx = 650; y=16; yy = 500; iBarY = 100;
	}

	// rysujemy licznik punktow zdobytych w levelu

	sprintf(cScore,"%.8d",m_pUserProfile->ulGetScore());

	for (int i=0; i<8; i++)
	{
		m_pNumber[cToDigit(cScore[i])]->Position(x+(32*i), y);
		m_pNumber[cToDigit(cScore[i])]->Render();
	}

	// rysujemy licznik punktow calkowitych

	sprintf(cScore,"%.8d",m_pUserProfile->ulGetTotalScore());	

	for (int i=0; i<8; i++)
	{
		m_pNumber[cToDigit(cScore[i])]->Position(xx+(32*i), y);
		m_pNumber[cToDigit(cScore[i])]->Render();
	}

	// rysujemy poziom

	sprintf(cScore,"%.2d",m_pUserProfile->ulGetLevel());

	m_pNumber[cToDigit(cScore[0])]->Position((_pScreen->iSizeX()/2)-32,yy);
	m_pNumber[cToDigit(cScore[0])]->Render();

	m_pNumber[cToDigit(cScore[1])]->Position((_pScreen->iSizeX()/2)+32,yy);
	m_pNumber[cToDigit(cScore[1])]->Render();

	// rysujemy progress bar

	for (int i=(_pScreen->iSizeX()/8); i<_pScreen->iSizeX()-(_pScreen->iSizeX()/8); i++)
	{
		m_pLevelBar->Position((float)i,iBarY);
		m_pLevelBar->Render();
	}

	fDest = (_pScreen->iSizeX()-(_pScreen->iSizeX()/8) - (_pScreen->iSizeX()/8) ) * (m_pUserProfile->fGetProgress()*0.01f);

	for (int i=0; i<(int)fDest; i++)
	{
		m_pScoreBar->Position((_pScreen->iSizeX()/8)+i,iBarY);
		m_pScoreBar->Render();
	}

	// rysujemy tablice highscore

	if (!m_bAddedToHighscore)
	{
		pProfile = new CProfile(USERS_FILE);		// najpierw wczytujemy imie aktualnego gracza
		pProfile->bLoad();
		strcpy(cUserName,pProfile->pGetName());
		delete pProfile;

		pHighScore = new CHighScore();		// wczytujemy tablice highscore
		pHighScore->bLoad();
		pHighScore->AddScore(cUserName,m_pUserProfile->ulGetScore());	// dodajemy zdobyte w tej grze punkty
		pHighScore->bSave();				// zapisujemy 

		// przepisz punkty do tablicy
		// przepisz nazwy do tablicy

		for (int i=0; i<10; i++)
		{
			m_ulScoreTable[i] = pHighScore->ulGetScore(i);
			strcpy(m_cNameTable[i],pHighScore->cGetName(i));
		}

		delete pHighScore;

		m_bAddedToHighscore = true;
	}

	for (int i=0; i<10; i++)
	{
		m_pFont->Print(300,150+(i*32),255, 0.03f, 0.03f, m_cNameTable[i]);
		sprintf(cUserName,"%d",m_ulScoreTable[i]);	// wykorzystujemy nie uzywana juz zmienna do konwersji liczby na ciag znakow
		m_pFont->Print(700,150+(i*32),255, 0.03f, 0.03f, cUserName);
	}

	// aktualizacja statusu

	if (m_pUserProfile->ulGetScore()>100000)
	{
		m_pUserProfile->AddScore(-10000);
		m_pUserProfile->AddTotalScore(10000);
	}

	if (m_pUserProfile->ulGetScore()>10000)
	{
		m_pUserProfile->AddScore(-1000);
		m_pUserProfile->AddTotalScore(1000);
	}

	if (m_pUserProfile->ulGetScore()>1000)
	{
		m_pUserProfile->AddScore(-100);
		m_pUserProfile->AddTotalScore(100);
	}

	if (m_pUserProfile->ulGetScore()>100)
	{
		m_pUserProfile->AddScore(-10);
		m_pUserProfile->AddTotalScore(10);
	}

	if (m_pUserProfile->ulGetScore()>0)
	{
		m_pUserProfile->AddScore(-1);
		m_pUserProfile->AddTotalScore(1);
	}

	// przyciski

	if (m_pButtonMenu->Render(pMouse)==ON_LEFT && !isMouseLock() )
		iReturn = 1; 
	
	if (m_pButtonAgain->Render(pMouse)==ON_LEFT && !isMouseLock() )
		iReturn = 2;

	if (iReturn>0)
	{
		// dodaj wszystkie pozostale punkty
		m_pUserProfile->AddTotalScore(m_pUserProfile->ulGetScore());
		m_pUserProfile->SetScore(0);

		m_pUserProfile->bSave();
	}

	return iReturn;
}

char ePostGame::cToDigit(char cDigit)
{
	if (cDigit=='1') return 1;
	if (cDigit=='2') return 2;
	if (cDigit=='3') return 3;
	if (cDigit=='4') return 4;
	if (cDigit=='5') return 5;
	if (cDigit=='6') return 6;
	if (cDigit=='7') return 7;
	if (cDigit=='8') return 8;
	if (cDigit=='9') return 9;

	return 0;
}


//end
