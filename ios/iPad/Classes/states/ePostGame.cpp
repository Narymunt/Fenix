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
    _iOS = _pScreen->iOS();
    
	_isActive = true;	// dane wczytane

	m_pBackground = new CSprite((char*)"e_postlevel",pScreen->iOS());

    if (pScreen->iOS()!=IPAD_HD)
    {
        m_pScoreBar = new CSprite((char*)"bar_lvl.png");
        m_pLevelBar = new CSprite((char*)"bar_exp.png");
    }
    else
    {
        m_pScoreBar = new CSprite((char*)"bar_lvl64.png");
        m_pLevelBar = new CSprite((char*)"bar_exp64.png");
    }

	// numer
    
    if (_iOS != IPAD_HD)
    {
        for (int i=0; i<10; i++)
        {
            sprintf(cBuffer,"%d.png",i);
            m_pNumber[i] = new CSprite(cBuffer);
        }
    }
    else
    {
        for (int i=0; i<10; i++)
        {
            sprintf(cBuffer,"%db.png",i);
            m_pNumber[i] = new CSprite(cBuffer);
        }
    }

	// przyciski podpowiedzi i wyjscia do menu
    
    if (_iOS == IPAD_HD)
    {
        m_pButtonAgain = new CButton((char*)"pl_start256.png",(char*)"pl_starto256.png",(char*)"pl_start256.png",0,0,256,256);
        m_pButtonAgain->SetPosition(1600,1170);
        m_pButtonAgain->SetHotCoords(1600,1170,1600+256,1170+256);
        
        m_pButtonMenu = new CButton((char*)"menu_click256.png",(char*)"menu_over256.png",(char*)"menu_static256.png",0,0,256,256);
        m_pButtonMenu->SetPosition(170,1170);
        m_pButtonMenu->SetHotCoords(170,1170,170+256,1170+256);
        
    }
    else if (_iOS == IPAD)
    {
        m_pButtonAgain = new CButton((char*)"pl_start.png",(char*)"pl_starto.png",(char*)"pl_start.png",0,0,128,128);
        m_pButtonAgain->SetPosition(800,600);
        m_pButtonAgain->SetHotCoords(800,600,800+128,600+128);
        
        m_pButtonMenu = new CButton((char*)"menu_click.png",(char*)"menu_over.png",(char*)"menu_static.png",0,0,128,128);
        m_pButtonMenu->SetPosition(80,600);
        m_pButtonMenu->SetHotCoords(80,600,80+128,600+128);
        
    }
    else if (_iOS == IPHONE5)
    {
        m_pButtonAgain = new CButton((char*)"pl_start.png",(char*)"pl_starto.png",(char*)"pl_start.png",0,0,128,128);
        m_pButtonAgain->SetPosition(950,500);
        m_pButtonAgain->SetHotCoords(950,500,950+128,500+128);
        
        m_pButtonMenu = new CButton((char*)"menu_click.png",(char*)"menu_over.png",(char*)"menu_static.png",0,0,128,128);
        m_pButtonMenu->SetPosition(50,500);
        m_pButtonMenu->SetHotCoords(50,500,50+128,500+128);
    }
    else if (_iOS == IPHONE4)
    {
        m_pButtonAgain = new CButton((char*)"pl_start.png",(char*)"pl_starto.png",(char*)"pl_start.png",0,0,128,128);
        m_pButtonAgain->SetPosition(800,500);
        m_pButtonAgain->SetHotCoords(800,500,800+128,500+128);
        
        m_pButtonMenu = new CButton((char*)"menu_click.png",(char*)"menu_over.png",(char*)"menu_static.png",0,0,128,128);
        m_pButtonMenu->SetPosition(50,500);
        m_pButtonMenu->SetHotCoords(50,500,50+128,500+128);
    }


	m_pUserProfile = new CProfile();
	m_pUserProfile->bLoad();

	m_bAddedToHighscore = false;	// nie dodano jeszcze nowego wyniku

	m_pFont = new CSpriteFont();

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


int ePostGame::Render(unsigned long ulTimer, CTouch *pTouch)
{
	char cScore[9];
	int	iReturn;
	float	fDest, fSize;
	CHighScore *pHighScore;
	CProfile *pProfile;	// musimy pobrac nazwe uzytkownika
	char cUserName[30];
	int	x,y,xx,yy;
	int iBarY;
	int iKerning, iKerningPTS;

	iReturn = 0;

	if (!pTouch->isPressed())
		isMouseLock(false);

	m_pBackground->Render();

	if (_pScreen->iSizeX()==1024 && _pScreen->iSizeY()==768)
	{
		x = 140; xx = 650; y=16; 
		yy = 650;					// poziom 
		iBarY = 100;
        iKerningPTS = 32;
		iKerning = 48;
		fSize = 0.07f;
	}
	else if (_pScreen->iSizeX() == 960)
	{
		x = 100; xx = 650;	// wspolrzedne dla punktow
		y = 16;
		yy = 550;					// poziom
		iBarY = 100;
        iKerningPTS = 32;
		iKerning = 48;
		fSize = 0.07f;
	}
	else if (_pScreen->iSizeX() == 1136)
	{
		x = 100; xx = 800;	// wspolrzedne dla punktow
		y = 16;
		yy = 550;					// poziom
		iBarY = 100;
        iKerningPTS = 32;
		iKerning = 48;
		fSize = 0.07f;
	}
	else if (_pScreen->iSizeX() == 2048)
	{
		x = 220; xx = 1300;	// wspolrzedne dla punktow
		y = 64;

		yy = 1200;					// poziom 
		
		iBarY = 200;
		iKerningPTS = 64;
		iKerning = 80;
		
		fSize = 0.125f;
	}


	// rysujemy licznik punktow zdobytych w levelu

	sprintf(cScore,"%.8d",m_pUserProfile->ulGetScore());

	for (int i=0; i<8; i++)
	{
		m_pNumber[cToDigit(cScore[i])]->Position(x+(iKerningPTS*i), y);
		m_pNumber[cToDigit(cScore[i])]->Render();
	}

	// rysujemy licznik punktow calkowitych

	sprintf(cScore,"%.8d",m_pUserProfile->ulGetTotalScore());	

	for (int i=0; i<8; i++)
	{
		m_pNumber[cToDigit(cScore[i])]->Position(xx+(iKerningPTS*i), y);
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
		pProfile = new CProfile();		// najpierw wczytujemy imie aktualnego gracza
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

    if (_pScreen->iOS()==IPAD_HD)
    {
        for (int i=0; i<10; i++)
        {
            m_pFont->Print(100,iKerning+iKerning+(i*(iKerning*0.75f)),255, fSize, fSize, m_cNameTable[i]);
            sprintf(cUserName,"%d",m_ulScoreTable[i]);	// wykorzystujemy nie uzywana juz zmienna do konwersji liczby na ciag znakow
            m_pFont->Print(1200, iKerning+iKerning + (i*(iKerning*0.75f)), 255, fSize, fSize, cUserName);
        }
    }
    else
    {
        for (int i=0; i<10; i++)
        {
            m_pFont->Print(-100,iKerning+iKerning+(i*(iKerning*0.75f))-200,255, fSize, fSize, m_cNameTable[i]);
            sprintf(cUserName,"%d",m_ulScoreTable[i]);	// wykorzystujemy nie uzywana juz zmienna do konwersji liczby na ciag znakow
            m_pFont->Print(400, iKerning+iKerning + (i*(iKerning*0.75f))-200, 255, fSize, fSize, cUserName);
        }
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

	if (m_pButtonMenu->Render(pTouch) == ON_LEFT && !isMouseLock())
	{
		if (m_pUserProfile->ulGetLevel() == 20 && m_pUserProfile->ulMap() == 8)		// 8 oznacza odblokowanie konca gry
		{
			iReturn = 100;
		}
		else
		{
			iReturn = 1;
		}
	}

	if (m_pButtonAgain->Render(pTouch) == ON_LEFT && !isMouseLock())
	{
		if (m_pUserProfile->ulGetLevel() == 20 && m_pUserProfile->ulMap() == 8)		// 8 oznacza odblokowanie konca gry
		{
			iReturn = 100;
		}
		else
		{
			iReturn = 2;
		}
	}

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
