#include "eIngame.h"

#pragma warning(disable : 4996)	// sprintf unsafe

// class constructor

eIngame::eIngame()
{
	m_pBlack = NULL;
	m_pBackground = NULL;
	m_pBoard = NULL;

	for (int i=0; i<GEMS_COUNT; i++)
		m_pGem[i]=NULL;

	for (int i=0; i<10; i++)
		m_pNumber[i]=NULL;

	m_pTimeBar = NULL; 
	m_pExpBar = NULL;
	m_pGreyBar = NULL;

	m_ulTimerStart = 0;	// poczatek
	m_ulPrevTimer = 0;

	// ustaw znacznik, ze dane nie sa jeszcze wczytane
	_isActive = false;

	m_cClickedA = -1;	// zadne nie klikniete
	m_cClickedB = -1;
	m_iClickedAx = m_iClickedAy = m_iClickedBx = m_iClickedBy = -1; 

	m_ulBonusTime = 0;	// dodatek do czasu
	m_ulBonusExp = 0;

	m_bMouseLock = false;
	m_bFallLock = false;

	m_pGameOver = NULL;
	m_bGameOver = false;
	m_lInGameOver = 0;

	m_pParticleManager = NULL;

	m_pHint = NULL;
	m_lHintTime = 0;

	m_iHintX = 0; m_iHintY = 0;

	m_ulScore = 0;

	m_pButtonMenu = NULL;
	m_pButtonHint = NULL;

	m_ucScoreMulti = 0;
	
	for (int i=0; i<=9; i++)
		m_pScoreMulti[i] = NULL;

	m_bHint = false;

	m_pCoin = NULL;
	m_pPopup = NULL;

	// audio chunks

	_pMSuper = NULL;
	_pMRainbow = NULL;
	_pMDiamond = NULL;
	_pMLevelUp = NULL;
	_pMClick = NULL;
	_pMBomb = NULL;

}

// class destructor

eIngame::~eIngame()
{
	Close();
}

// load data

void eIngame::Open(int iLevel, CScreen *pScreen)
{	
	char cBuffer[16];

	m_ulScore = 0;			// iloœæ punktów
	m_ucScoreMulti = (unsigned char) iLevel -1;		// jaki mno¿nik

	m_ulTimer1000 = 0;		// czas 10 sek temu
	m_ulScore1000 = 0;		// punkty 10 sek temu

	m_pParticleManager = new CParticle2DManager((char*)"data/particle.png", 250, 
                                               -100,-100,1024,768,
                                               0.01f,0.01f,0.3f,0.3f,
                                               0.5f, -.001f,.001f,
                                               0.5f, -5.0f,5.0f,
                                               1000,10000,pScreen);

	m_pTimeBar = new CSprite(pScreen,"BAR_RED");
	m_pExpBar =  new CSprite(pScreen,"BAR_GREEN");
	m_pGreyBar = new CSprite(pScreen,"BAR_GREY");

	m_pBoard = new CSprite("data/board512.png");

	m_pGameOver = new CSprite(pScreen,"GFX_GAMEOVER_SCREEN");
	
	m_pHint = new CSprite(pScreen,"GFX_HINT");
	m_lHintTime = 0;

	m_pBlack = new CSprite(pScreen,"GFX_BLACK100_SCREEN");

	// ikony x1,x2 itd. 

	for (int i=0; i<=9; i++)
	{
		sprintf(cBuffer,"data/x%d.png",i+1);
		m_pScoreMulti[i] = new CSprite(cBuffer);
	}

	switch(iLevel)
	{
		case 1:
			m_pBackground = new CSprite(pScreen,"LEVEL01_SCREEN");
		break;

		case 2:
			m_pBackground = new CSprite(pScreen,"LEVEL02_SCREEN");
		break;

		case 3:
			m_pBackground = new CSprite(pScreen,"LEVEL03_SCREEN");
		break;

		case 4:
			m_pBackground = new CSprite(pScreen,"LEVEL04_SCREEN");
		break;

		case 5:
			m_pBackground = new CSprite(pScreen,"LEVEL05_SCREEN");
		break;
		
		case 6:
			m_pBackground = new CSprite(pScreen,"LEVEL06_SCREEN");
		break;
		
		case 7:
			m_pBackground = new CSprite(pScreen,"LEVEL07_SCREEN");
		break;
	}
	
	// obrazki kamykow

	for (int i=0; i<=GEMS_COUNT-1; i++)
	{
		sprintf(cBuffer,"data/gem%d.png",i+1);
		m_pGem[i] = new CSprite(cBuffer);
	}

	// przyciski podpowiedzi i wyjscia do menu

	m_pButtonHint = new CButton("data/button_hint.png","data/button_hint.png","data/button_hint.png");
	m_pButtonHint->SetPosition(320,400);
	m_pButtonHint->SetHotCoords(320,400,320+64,400+64);

	m_pButtonMenu = new CButton("data/button_menu.png","data/button_menu.png","data/button_menu.png");
	m_pButtonMenu->SetPosition(160,400);
	m_pButtonMenu->SetHotCoords(160,400,160+64,400+64);

	// numer

	for (int i=0; i<=9; i++)
	{
		sprintf(cBuffer,"data/%d.png",i);
		m_pNumber[i] = new CSprite(cBuffer);
	}

	for (int i=0; i<64; i++)
	{
		m_cBoard[i]= rand()%7;
		m_bBoard[i]= false;
		m_fBoardDeltaX[i] = 0.0f;
		m_fBoardDeltaY[i] = 0.0f;

		m_cScaleBoard[i]=-1;
		m_fScaleBoard[i]= 1.0f;
		m_ulScaleTimer[i]= 0;
	}

	// popup manager

	m_pPopup = new CPopup();
	m_pPopup->Open(pScreen);

	// animacja monety

	m_pCoin = new CAnimation("coin_",24,"png");
	m_pCoin->Open(pScreen);

	for (int i=0; i<64; i++)
		m_iCoin[i] = -1;

	// liczniki, timery i inne bajery

	m_ulTimerStart = 0;	// poczatek
	m_ulPrevTimer = 0;

	m_cClickedA = -1;	// zadne nie klikniete
	m_cClickedB = -1;
	m_iClickedAx = m_iClickedAy = m_iClickedBx = m_iClickedBy = -1; 

	m_ulBonusTime = 0;	// dodatek do czasu
	m_ulBonusExp = 0;

	m_bMouseLock = false;
	m_bFallLock = false;

	m_bGameOver = false;
	m_lInGameOver = 0;

	m_iHintX = 0;
	m_iHintY = 0;

	for (int i=0; i<20; i++)		/// zerujemy tablice nowych osiagniec
		_ucNewTroophy[i] = 0;

	_uiMatchCount = 0;

	m_bHint = false;
	
	_pScreen = pScreen;

	_isActive = true;	// dane wczytane

	// init all audio chunks

	_pMSuper = Mix_LoadWAV("data/super.ogg");
	_pMRainbow = Mix_LoadWAV("data/rainbow.ogg");
	_pMDiamond = Mix_LoadWAV("data/diamond.ogg");
	_pMLevelUp = Mix_LoadWAV("data/level_up.ogg");
	_pMClick = Mix_LoadWAV("data/click.ogg");
	_pMBomb = Mix_LoadWAV("data/bomb.ogg");

	_isActive = true;	// data loaded

}

// free graphics and music, but keep the required data

void eIngame::Close(void)
{
	SafeDelete(m_pBoard);
	SafeDelete(m_pBlack);
	SafeDelete(m_pBackground);
	
	SafeDelete(m_pTimeBar);
	SafeDelete(m_pExpBar);
	SafeDelete(m_pGreyBar);

	SafeDelete(m_pGameOver);

	for (int i=0; i<=GEMS_COUNT; i++)
		SafeDelete(m_pGem[i]);

	for (int i=0; i<10; i++)
		SafeDelete(m_pNumber[i]);

	SafeDelete(m_pParticleManager);
	SafeDelete(m_pButtonMenu);
	SafeDelete(m_pButtonHint);

	for (int i=0; i<=9; i++)
		SafeDelete(m_pScoreMulti[i]);

	SafeDelete(m_pPopup);
	SafeDelete(m_pHint);
	SafeDelete(m_pCoin);
	
	// release audio chunks

	if (_pMSuper!=NULL)
	{
		Mix_FreeChunk(_pMSuper);
		_pMSuper = NULL;
	}

	if (_pMRainbow!=NULL)
	{
		Mix_FreeChunk(_pMRainbow);
		_pMRainbow = NULL;
	}

	if (_pMDiamond!=NULL)
	{
		Mix_FreeChunk(_pMDiamond);
		_pMDiamond = NULL;
	}

	if (_pMLevelUp!=NULL)
	{
		Mix_FreeChunk(_pMLevelUp);
		_pMLevelUp = NULL;
	}

	if (_pMClick!=NULL)
	{
		Mix_FreeChunk(_pMClick);
		_pMClick = NULL;
	}
	
	if (_pMBomb!=NULL)
	{
		Mix_FreeChunk(_pMBomb);
		_pMBomb = NULL;
	}

	_isActive = false;
}

// add points

void eIngame::Advance(unsigned long ulBonusTime, unsigned long ulBonusExp, unsigned long ulScore)
{
	m_ulBonusTime += ulBonusTime;
	m_ulBonusExp += ulBonusExp;
	m_ulScore += ulScore;
	
	_uiMatchCount++;	// licznik ulozonych kombinacji, zeby mozna bylo sprawdzic czy mozemy dodac archievement
}

// update board when correct combination found

//=== sprawdzamy czy na planszy jest wlasciwa kombinacja, jesli tak to przestawiamy klocki

bool eIngame::isMatch3(unsigned long ulTimer)
{
	bool bFound;
	int h1,h2, adres;

	bFound = false;

	// szukamy L, 3 kamykow w pionie i poziomie aby utworzyc diament

	// +-	szukamy lewego gornego rogu
	// |

	for (h1=0; h1<=5; h1++)
	{
		for (h2=0; h2<=5; h2++)
		{
			adres = (h1*8)+h2;

			if (m_cBoard[adres] == m_cBoard[adres+1] && m_cBoard[adres] == m_cBoard[adres+2] && 
				m_cBoard[adres] == m_cBoard[((h1+1)*8)+h2] && m_cBoard[adres] == m_cBoard[((h1+1)*8)+h2] &&
				m_fBoardDeltaX[adres] == 0 && m_fBoardDeltaY[adres] == 0 &&
				m_fBoardDeltaX[adres+1] == 0 && m_fBoardDeltaY[adres+1] == 0 &&
				m_fBoardDeltaX[adres+2] == 0 && m_fBoardDeltaY[adres+2] == 0 &&
				m_fBoardDeltaX[((h1+1)*8)+h2] == 0 && m_fBoardDeltaY[((h1+1)*8)+h2] == 0 &&
				m_fBoardDeltaX[((h1+2)*8)+h2] == 0 && m_fBoardDeltaY[((h1+2)*8)+h2] == 0 &&
				!m_bBoard[((h1+1)*8)+h2+1] &&		// sprawdzamy czy pod spodem nie ma wolnych miejsc
				!m_bBoard[((h1+1)*8)+h2+2] &&
				!m_bBoard[adres] &&				// czy my nie sprawdzamy pustych miejsc
				m_cBoard[adres]<GEM_ROCK)
			{

				m_cBoard[adres] = GEM_DIAMOND;
				m_iCoin[adres] = ulTimer;	// dodajemy monetê

				m_cScaleBoard[adres] = m_cBoard[adres];
				m_cScaleBoard[adres+1] = m_cBoard[adres+1];
				m_cScaleBoard[adres+2] = m_cBoard[adres+2];						
				m_cScaleBoard[((h1+1)*8)+h2] = m_cBoard[((h1+1)*8)+h2];
				m_cScaleBoard[((h1+2)*8)+h2] = m_cBoard[((h1+2)*8)+h2];

				m_ulScaleTimer[adres] = (unsigned long)ulTimer;
				m_ulScaleTimer[adres+1] = (unsigned long)ulTimer;
				m_ulScaleTimer[adres+2] = (unsigned long)ulTimer;
				m_ulScaleTimer[((h1+1)*8)+h2] = (unsigned long)ulTimer;
				m_ulScaleTimer[((h1+2)*8)+h2] = (unsigned long)ulTimer;

				m_cBoard[adres+1] = -1;
				m_bBoard[adres+1] = true;

				m_cBoard[adres+2] = -1;
				m_bBoard[adres+2] = true;

				m_cBoard[((h1+1)*8)+h2] = -1;
				m_bBoard[((h1+1)*8)+h2] = true;

				m_cBoard[((h1+2)*8)+h2] = -1;
				m_bBoard[((h1+2)*8)+h2] = true;

				// dodajemy czas, doœwiadczenie, punkty
				Advance ((10/(m_ucScoreMulti+1))*3,(100/(m_ucScoreMulti+1))*3,((3*(m_ucScoreMulti+1))+(m_ulBonusTime/10))*3);

				bFound = true;
			}
		}
	}

	// -+	szukamy prawego gornego rogu
	//  |

	for (h1=0; h1<=5; h1++)
	{
		for (h2=0; h2<=5; h2++)
		{
			adres = (h1*8)+h2;

			if (m_cBoard[adres] == m_cBoard[adres+1] && m_cBoard[adres] == m_cBoard[adres+2] && 
				m_cBoard[adres] == m_cBoard[((h1+1)*8)+h2+2] && m_cBoard[adres] == m_cBoard[((h1+2)*8)+h2+2] &&
				m_fBoardDeltaX[adres] == 0 && m_fBoardDeltaY[adres] == 0 &&
				m_fBoardDeltaX[adres+1] == 0 && m_fBoardDeltaY[adres+1] == 0 &&
				m_fBoardDeltaX[adres+2] == 0 && m_fBoardDeltaY[adres+2] == 0 &&
				m_fBoardDeltaX[((h1+1)*8)+h2+2] == 0 && m_fBoardDeltaY[((h1+1)*8)+h2+2] == 0 &&
				m_fBoardDeltaX[((h1+2)*8)+h2+2] == 0 && m_fBoardDeltaY[((h1+2)*8)+h2+2] == 0 &&
				!m_bBoard[((h1+1)*8)+h2-1] &&		// sprawdzamy czy pod spodem nie ma wolnych miejsc
				!m_bBoard[((h1+1)*8)+h2-2] &&
				!m_bBoard[adres] &&				// czy my nie sprawdzamy pustych miejsc
				m_cBoard[adres]<GEM_ROCK)
			{

				m_cBoard[adres+2] = GEM_DIAMOND;
				m_iCoin[adres+2] = ulTimer;	// dodajemy monetê

				m_cScaleBoard[adres] = m_cBoard[adres];
				m_cScaleBoard[adres+1] = m_cBoard[adres+1];
				m_cScaleBoard[adres+2] = m_cBoard[adres+2];						
				m_cScaleBoard[((h1+1)*8)+h2+2] = m_cBoard[((h1+1)*8)+h2+2];
				m_cScaleBoard[((h1+2)*8)+h2+2] = m_cBoard[((h1+2)*8)+h2+2];

				m_ulScaleTimer[adres] = (unsigned long)ulTimer;
				m_ulScaleTimer[adres+1] = (unsigned long)ulTimer;
				m_ulScaleTimer[adres+2] = (unsigned long)ulTimer;
				m_ulScaleTimer[((h1+1)*8)+h2+2] = (unsigned long)ulTimer;
				m_ulScaleTimer[((h1+2)*8)+h2+2] = (unsigned long)ulTimer;

				m_cBoard[adres] = -1;
				m_bBoard[adres] = true;

				m_cBoard[adres+1] = -1;
				m_bBoard[adres+1] = true;

				m_cBoard[((h1+1)*8)+h2+2] = -1;
				m_bBoard[((h1+1)*8)+h2+2] = true;

				m_cBoard[((h1+2)*8)+h2+2] = -1;
				m_bBoard[((h1+2)*8)+h2+2] = true;

				Advance ((10/(m_ucScoreMulti+1))*3,(100/(m_ucScoreMulti+1))*3,((3*(m_ucScoreMulti+1))+(m_ulBonusTime/10))*3);
						
				bFound = true;
			}
		}
	}

	// |	szukamy lewego dolnego rogu
	// +- 

	for (h1=0; h1<=5; h1++)
	{
		for (h2=0; h2<=5; h2++)
		{
			adres = (h1*8)+h2;

			if (m_cBoard[adres] == m_cBoard[((h1+1)*8)+h2] && m_cBoard[adres] == m_cBoard[((h1+2)*8)+h2] && 
				m_cBoard[adres] == m_cBoard[((h1+2)*8)+h2+1] && m_cBoard[adres] == m_cBoard[((h1+2)*8)+h2+2] &&
				m_fBoardDeltaX[adres] == 0 && m_fBoardDeltaY[adres] == 0 &&
				m_fBoardDeltaX[((h1+1)*8)+h2] == 0 && m_fBoardDeltaY[((h1+1)*8)+h2] == 0 &&
				m_fBoardDeltaX[((h1+2)*8)+h2] == 0 && m_fBoardDeltaY[((h1+2)*8)+h2] == 0 &&
				m_fBoardDeltaX[((h1+2)*8)+h2+1] == 0 && m_fBoardDeltaY[((h1+2)*8)+h2+1] == 0 &&
				m_fBoardDeltaX[((h1+2)*8)+h2+2] == 0 && m_fBoardDeltaY[((h1+2)*8)+h2+2] == 0 &&
				!m_bBoard[adres] &&				// czy my nie sprawdzamy pustych miejsc
				m_cBoard[adres]<GEM_ROCK)
			{

				m_cBoard[((h1+2)*8)+h2] = GEM_DIAMOND;
				m_iCoin[((h1+2)*8)+h2] = ulTimer;	// dodajemy monetê

				m_cScaleBoard[((h1+2)*8)+h2] = m_cBoard[((h1+2)*8)+h2];
				m_cScaleBoard[adres] = m_cBoard[adres];
				m_cScaleBoard[((h1+1)*8)+h2] = m_cBoard[((h1+1)*8)+h2];						
				m_cScaleBoard[((h1+2)*8)+h2+1] = m_cBoard[((h1+2)*8)+h2+1];
				m_cScaleBoard[((h1+2)*8)+h2+2] = m_cBoard[((h1+2)*8)+h2+2];

				m_ulScaleTimer[((h1+2)*8)+h2] = (unsigned long)ulTimer;
				m_ulScaleTimer[adres] = (unsigned long)ulTimer;
				m_ulScaleTimer[((h1+1)*8)+h2] = (unsigned long)ulTimer;
				m_ulScaleTimer[((h1+2)*8)+h2+1] = (unsigned long)ulTimer;
				m_ulScaleTimer[((h1+2)*8)+h2+2] = (unsigned long)ulTimer;

				m_cBoard[adres] = -1;
				m_bBoard[adres] = true;

				m_cBoard[((h1+1)*8)+h2] = -1;
				m_bBoard[((h1+1)*8)+h2] = true;

				m_cBoard[((h1+2)*8)+h2+1] = -1;
				m_bBoard[((h1+2)*8)+h2+1] = true;

				m_cBoard[((h1+2)*8)+h2+2] = -1;
				m_bBoard[((h1+2)*8)+h2+2] = true;

				Advance ((10/(m_ucScoreMulti+1))*3,(100/(m_ucScoreMulti+1))*3,((3*(m_ucScoreMulti+1))+(m_ulBonusTime/10))*3);
						
				bFound = true;
			}
		}
	}

	//  |	szukamy prawego dolnego rogu
	// -+

	for (h1=2; h1<=7; h1++)
	{
		for (h2=0; h2<=5; h2++)
		{
			adres = (h1*8)+h2;

			if (m_cBoard[adres] == m_cBoard[adres+1] && m_cBoard[adres] == m_cBoard[adres+2] && 
				m_cBoard[adres] == m_cBoard[((h1-1)*8)+h2+2] && m_cBoard[adres] == m_cBoard[((h1-2)*8)+h2+2] &&
				m_fBoardDeltaX[adres] == 0 && m_fBoardDeltaY[adres] == 0 &&
				m_fBoardDeltaX[adres+1] == 0 && m_fBoardDeltaY[adres+1] == 0 &&
				m_fBoardDeltaX[adres+2] == 0 && m_fBoardDeltaY[adres+2] == 0 &&
				m_fBoardDeltaX[((h1-1)*8)+h2+2] == 0 && m_fBoardDeltaY[((h1-1)*8)+h2+2] == 0 &&
				m_fBoardDeltaX[((h1-2)*8)+h2+2] == 0 && m_fBoardDeltaY[((h1-2)*8)+h2+2] == 0 &&
				!m_bBoard[adres] &&				// czy my nie sprawdzamy pustych miejsc
				m_cBoard[adres]<GEM_ROCK)
			{

				m_cBoard[adres+2] = GEM_DIAMOND;
				m_iCoin[adres+2] = ulTimer;	// dodajemy monetê

				m_cScaleBoard[adres+2] = m_cBoard[adres+2];
				m_cScaleBoard[adres] = m_cBoard[adres];
				m_cScaleBoard[adres+1] = m_cBoard[adres+1];						
				m_cScaleBoard[((h1-1)*8)+h2+2] = m_cBoard[((h1-1)*8)+h2+2];
				m_cScaleBoard[((h1-2)*8)+h2+2] = m_cBoard[((h1-2)*8)+h2+2];

				m_ulScaleTimer[adres+2] = (unsigned long)ulTimer;
				m_ulScaleTimer[adres] = (unsigned long)ulTimer;
				m_ulScaleTimer[adres+1] = (unsigned long)ulTimer;
				m_ulScaleTimer[((h1-1)*8)+h2+2] = (unsigned long)ulTimer;
				m_ulScaleTimer[((h1-2)*8)+h2+2] = (unsigned long)ulTimer;

				m_cBoard[adres+1] = -1;
				m_bBoard[adres+1] = true;

				m_cBoard[adres] = -1;
				m_bBoard[adres] = true;

				m_cBoard[((h1-1)*8)+h2+2] = -1;
				m_bBoard[((h1-1)*8)+h2+2] = true;

				m_cBoard[((h1-2)*8)+h2+2] = -1;
				m_bBoard[((h1-2)*8)+h2+2] = true;

				Advance ((10/(m_ucScoreMulti+1))*3,(100/(m_ucScoreMulti+1))*3,((3*(m_ucScoreMulti+1))+(m_ulBonusTime/10))*3);
						
				bFound = true;
			}
		}
	}

	//=== szukamy 5 kamykow w jednej linii poziomo

		for (h1=0; h1<=7; h1++)	// sprawdzamy poziomo
		{
			for (h2=0; h2<=3; h2++)
			{
			adres = (h1*8)+h2;

				if (m_cBoard[adres] == m_cBoard[adres+1] && m_cBoard[adres] == m_cBoard[adres+2] && m_cBoard[adres] == m_cBoard[adres+3] && m_cBoard[adres] == m_cBoard[adres+4] &&
					!m_bBoard[adres] &&				// czy my nie sprawdzamy pustych miejsc
					m_fBoardDeltaX[adres]==0 && m_fBoardDeltaY[adres]==0 &&	
					m_fBoardDeltaX[adres+1]==0 && m_fBoardDeltaY[adres+1]==0 &&
					m_fBoardDeltaX[adres+2]==0 && m_fBoardDeltaY[adres+2]==0 &&
					m_fBoardDeltaX[adres+3]==0 && m_fBoardDeltaY[adres+3]==0 &&
					m_fBoardDeltaX[adres+4]==0 && m_fBoardDeltaY[adres+3]==0 ) 	// sprawdzamy tylko klocki ktore juz nie sa w ruchu

				{
					if (h1==7)	// w ostatniej lini nie sprawdzamy czy pod klockami jest spacja
					{	
						if (m_cBoard[adres]<GEM_ROCK)		// tylko kamyki standardowe
						{
							m_bBoard[adres] = true;
							m_bBoard[adres+1] = true;
					
							m_cBoard[adres+2] = GEM_RAINBOW;
							m_bBoard[adres+2] = false;
							
							m_bBoard[adres+3] = true;
							m_bBoard[adres+4] = true;

							m_cScaleBoard[adres] = m_cBoard[adres];
							m_cScaleBoard[adres+1] = m_cBoard[adres+1];
							m_cScaleBoard[adres+2] = m_cBoard[adres+2];						
							m_cScaleBoard[adres+3] = m_cBoard[adres+3];
							m_cScaleBoard[adres+4] = m_cBoard[adres+4];

							m_ulScaleTimer[adres] = (unsigned long)ulTimer;
							m_ulScaleTimer[adres+1] = (unsigned long)ulTimer;
							m_ulScaleTimer[adres+2] = (unsigned long)ulTimer;
							m_ulScaleTimer[adres+3] = (unsigned long)ulTimer;
							m_ulScaleTimer[adres+4] = (unsigned long)ulTimer;

							m_iCoin[adres] = ulTimer;	// uruchom animacje tutaj 
							m_iCoin[adres+1] = ulTimer;	
							m_iCoin[adres+2] = ulTimer;	
							m_iCoin[adres+3] = ulTimer;	
							m_iCoin[adres+4] = ulTimer;	

							Advance ((10/(m_ucScoreMulti+1)),(100/(m_ucScoreMulti+1)),((3*(m_ucScoreMulti+1))+(m_ulBonusTime/10)));
						
							bFound = true;
						}
					}
					else
					{
						if (!m_bBoard[((h1+1)*8)+h2] && !m_bBoard[((h1+1)*8)+h2+1] && !m_bBoard[((h1+1)*8)+h2+2] && !m_bBoard[((h1+1)*8)+h2+3] && !m_bBoard[((h1+1)*8)+h2+4])	// czy pod klockami jest spacja ?
						{
							if (m_cBoard[adres]<GEM_ROCK)		// tylko kamyki standardowe
							{
								m_bBoard[adres] = true;
								m_bBoard[adres+1] = true;

								m_cBoard[adres+2] = GEM_RAINBOW;
								m_bBoard[adres+2] = false;

								m_bBoard[adres+3] = true;
								m_bBoard[adres+4] = true;

								m_cScaleBoard[adres] = m_cBoard[adres];
								m_cScaleBoard[adres+1] = m_cBoard[adres+1];
								m_cScaleBoard[adres+2] = m_cBoard[adres+2];						
								m_cScaleBoard[adres+3] = m_cBoard[adres+3];
								m_cScaleBoard[adres+4] = m_cBoard[adres+4];

								m_ulScaleTimer[adres] = (unsigned long)ulTimer;
								m_ulScaleTimer[adres+1] = (unsigned long)ulTimer;
								m_ulScaleTimer[adres+2] = (unsigned long)ulTimer;
								m_ulScaleTimer[adres+3] = (unsigned long)ulTimer;
								m_ulScaleTimer[adres+4] = (unsigned long)ulTimer;

								m_iCoin[adres] = ulTimer;	// uruchom animacje tutaj 
								m_iCoin[adres+1] = ulTimer;	
								m_iCoin[adres+2] = ulTimer;	
								m_iCoin[adres+3] = ulTimer;	
								m_iCoin[adres+4] = ulTimer;	

								Advance ((10/(m_ucScoreMulti+1)),(100/(m_ucScoreMulti+1)),((3*(m_ucScoreMulti+1))+(m_ulBonusTime/10)));

								bFound = true;
							}
						}
					}
				}
			}
		}

		for (h1=0; h1<=3; h1++)	// sprawdzamy pionowo
		{
			for (h2=0; h2<=7; h2++)
			{
				adres = (h1*8)+h2;

				if (m_cBoard[adres] == m_cBoard[((h1+1)*8)+h2] && m_cBoard[adres] == m_cBoard[((h1+2)*8)+h2] && m_cBoard[adres] == m_cBoard[((h1+2)*8)+h2] && m_cBoard[adres] == m_cBoard[((h1+3)*8)+h2] && m_cBoard[adres] == m_cBoard[((h1+4)*8)+h2] &&
					!m_bBoard[adres] &&				// czy my nie sprawdzamy pustych miejsc
					m_fBoardDeltaX[adres] == 0 && m_fBoardDeltaY[adres] == 0 &&
					m_fBoardDeltaX[((h1+1)*8)+h2] == 0 && m_fBoardDeltaY[((h1+1)*8)+h2] == 0 &&
					m_fBoardDeltaX[((h1+2)*8)+h2] == 0 && m_fBoardDeltaY[((h1+2)*8)+h2] == 0 &&
					m_fBoardDeltaX[((h1+3)*8)+h2] == 0 && m_fBoardDeltaY[((h1+3)*8)+h2] == 0 &&
					m_fBoardDeltaX[((h1+4)*8)+h2] == 0 && m_fBoardDeltaY[((h1+4)*8)+h2] == 0 )
				{
					if (m_cBoard[adres]<GEM_ROCK)		// tylko kamyki standardowe
					{
						m_bBoard[adres] = true;
						m_bBoard[((h1+1)*8)+h2] = true;
						
						m_cBoard[((h1+2)*8)+h2] = GEM_RAINBOW;
						m_bBoard[((h1+2)*8)+h2] = false;

						m_bBoard[((h1+3)*8)+h2] = true;
						m_bBoard[((h1+4)*8)+h2] = true;

						m_cScaleBoard[adres] = m_cBoard[adres];
						m_cScaleBoard[((h1+1)*8)+h2] = m_cBoard[((h1+1)*8)+h2];
						m_cScaleBoard[((h1+2)*8)+h2] = m_cBoard[((h1+2)*8)+h2];						
						m_cScaleBoard[((h1+3)*8)+h2] = m_cBoard[((h1+3)*8)+h2];
						m_cScaleBoard[((h1+4)*8)+h2] = m_cBoard[((h1+4)*8)+h2];

						m_ulScaleTimer[adres] = (unsigned long)ulTimer;
						m_ulScaleTimer[((h1+1)*8)+h2] = (unsigned long)ulTimer;
						m_ulScaleTimer[((h1+2)*8)+h2] = (unsigned long)ulTimer;
						m_ulScaleTimer[((h1+3)*8)+h2] = (unsigned long)ulTimer;
						m_ulScaleTimer[((h1+4)*8)+h2] = (unsigned long)ulTimer;

						m_iCoin[adres] = ulTimer;	// uruchom animacje tutaj 
						m_iCoin[((h1+1)*8)+h2] = ulTimer;	
						m_iCoin[((h1+2)*8)+h2] = ulTimer;	
						m_iCoin[((h1+3)*8)+h2] = ulTimer;	
						m_iCoin[((h1+4)*8)+h2] = ulTimer;	

						Advance ((10/(m_ucScoreMulti+1)),(100/(m_ucScoreMulti+1)),((3*(m_ucScoreMulti+1))+(m_ulBonusTime/10)));
	
						bFound = true;
					}
				}
			}
		}

	// szukamy 4 kamyczków w jednej linii

		for (h1=0; h1<=7; h1++)	// sprawdzamy poziomo
		{
			for (h2=0; h2<=4; h2++)
			{
				adres = (h1*8)+h2;

				if (m_cBoard[adres] == m_cBoard[adres+1] && m_cBoard[adres] == m_cBoard[adres+2] && m_cBoard[adres] == m_cBoard[adres+3] &&
					!m_bBoard[adres] &&				// czy my nie sprawdzamy pustych miejsc
					m_fBoardDeltaX[adres]==0 && m_fBoardDeltaY[adres]==0 &&	
					m_fBoardDeltaX[adres+1]==0 && m_fBoardDeltaY[adres+1]==0 &&
					m_fBoardDeltaX[adres+2]==0 && m_fBoardDeltaY[adres+2]==0 &&
					m_fBoardDeltaX[adres+3]==0 && m_fBoardDeltaY[adres+3]==0)	// sprawdzamy tylko klocki ktore juz nie sa w ruchu

				{
					if (h1==7)	// w ostatniej lini nie sprawdzamy czy pod klockami jest spacja
					{	
						if (m_cBoard[adres]<GEM_ROCK)		// tylko kamyki standardowe
						{
							m_bBoard[adres] = true;
							m_bBoard[adres+1] = true;
							m_bBoard[adres+2] = true;
							m_bBoard[adres+3] = true;

							m_cScaleBoard[adres] = m_cBoard[adres];
							m_cScaleBoard[adres+1] = m_cBoard[adres+1];
							m_cScaleBoard[adres+2] = m_cBoard[adres+2];						
							m_cScaleBoard[adres+3] = m_cBoard[adres+3];

							m_ulScaleTimer[adres] = (unsigned long)ulTimer;
							m_ulScaleTimer[adres+1] = (unsigned long)ulTimer;
							m_ulScaleTimer[adres+2] = (unsigned long)ulTimer;
							m_ulScaleTimer[adres+3] = (unsigned long)ulTimer;

							m_iCoin[adres] = ulTimer;
							m_iCoin[adres+1] = ulTimer;	// uruchom animacje tutaj 
							m_iCoin[adres+2] = ulTimer;
							m_iCoin[adres+3] = ulTimer;
							
							Advance ((10/(m_ucScoreMulti+1)),(100/(m_ucScoreMulti+1)),((3*(m_ucScoreMulti+1))+(m_ulBonusTime/10)));
							Advance ((10/(m_ucScoreMulti+1)),(100/(m_ucScoreMulti+1)),((3*(m_ucScoreMulti+1))+(m_ulBonusTime/10)));
						
							bFound = true;
						}
					}
					else
					{
						if (!m_bBoard[((h1+1)*8)+h2] && !m_bBoard[((h1+1)*8)+h2+1] && !m_bBoard[((h1+1)*8)+h2+2] && !m_bBoard[((h1+1)*8)+h2+3])	// czy pod klockami jest spacja ?
						{
							if (m_cBoard[adres]<GEM_ROCK)		// tylko kamyki standardowe
							{
								m_bBoard[adres] = true;
								m_bBoard[adres+1] = true;
								m_bBoard[adres+2] = true;
								m_bBoard[adres+2] = true;

								m_iCoin[adres] = ulTimer;	// uruchom animacje tutaj 
								m_iCoin[adres+1] = ulTimer;	// uruchom animacje tutaj 
								m_iCoin[adres+2] = ulTimer;	// uruchom animacje tutaj 
								m_iCoin[adres+3] = ulTimer;	// uruchom animacje tutaj 

								m_cScaleBoard[adres] = m_cBoard[adres];
								m_cScaleBoard[adres+1] = m_cBoard[adres+1];
								m_cScaleBoard[adres+2] = m_cBoard[adres+2];						
								m_cScaleBoard[adres+3] = m_cBoard[adres+3];

								m_ulScaleTimer[adres] = (unsigned long)ulTimer;
								m_ulScaleTimer[adres+1] = (unsigned long)ulTimer;
								m_ulScaleTimer[adres+2] = (unsigned long)ulTimer;
								m_ulScaleTimer[adres+3] = (unsigned long)ulTimer;

								Advance ((10/(m_ucScoreMulti+1)),(100/(m_ucScoreMulti+1)),((3*(m_ucScoreMulti+1))+(m_ulBonusTime/10)));
								Advance ((10/(m_ucScoreMulti+1)),(100/(m_ucScoreMulti+1)),((3*(m_ucScoreMulti+1))+(m_ulBonusTime/10)));

								bFound = true;
							}
						}
					}
				}
			}
		}

		for (h1=0; h1<=4; h1++)	// sprawdzamy pionowo
		{
			for (h2=0; h2<=7; h2++)
			{
				adres = (h1*8)+h2;

				if (m_cBoard[adres] == m_cBoard[((h1+1)*8)+h2] && m_cBoard[adres] == m_cBoard[((h1+2)*8)+h2] && m_cBoard[adres] == m_cBoard[((h1+3)*8)+h2] &&
					!m_bBoard[adres] &&				// czy my nie sprawdzamy pustych miejsc	
					m_fBoardDeltaX[adres] == 0 && m_fBoardDeltaY[adres] == 0 &&
					m_fBoardDeltaX[((h1+1)*8)+h2] == 0 && m_fBoardDeltaY[((h1+1)*8)+h2] == 0 &&
					m_fBoardDeltaX[((h1+2)*8)+h2] == 0 && m_fBoardDeltaY[((h1+2)*8)+h2] == 0 &&
					m_fBoardDeltaX[((h1+3)*8)+h2] == 0 && m_fBoardDeltaY[((h1+3)*8)+h2] == 0)
				{
					if (m_cBoard[adres]<GEM_ROCK)		// tylko kamyki standardowe
					{
						m_bBoard[adres] = true;
						m_bBoard[((h1+1)*8)+h2] = true;
						m_bBoard[((h1+2)*8)+h2] = true;
						m_bBoard[((h1+3)*8)+h2] = true;

						m_cScaleBoard[adres] = m_cBoard[adres];
						m_cScaleBoard[((h1+1)*8)+h2] = m_cBoard[((h1+1)*8)+h2];
						m_cScaleBoard[((h1+2)*8)+h2] = m_cBoard[((h1+2)*8)+h2];						
						m_cScaleBoard[((h1+3)*8)+h2] = m_cBoard[((h1+3)*8)+h2];

						m_ulScaleTimer[adres] = (unsigned long)ulTimer;
						m_ulScaleTimer[((h1+1)*8)+h2] = (unsigned long)ulTimer;
						m_ulScaleTimer[((h1+2)*8)+h2] = (unsigned long)ulTimer;
						m_ulScaleTimer[((h1+3)*8)+h2] = (unsigned long)ulTimer;

						m_iCoin[adres] = ulTimer;	// uruchom animacje tutaj 
						m_iCoin[((h1+1)*8)+h2] = ulTimer;	// uruchom animacje tutaj 
						m_iCoin[((h1+2)*8)+h2] = ulTimer;	// uruchom animacje tutaj 
						m_iCoin[((h1+3)*8)+h2] = ulTimer;	// uruchom animacje tutaj 

						Advance ((10/(m_ucScoreMulti+1)),(100/(m_ucScoreMulti+1)),((3*(m_ucScoreMulti+1))+(m_ulBonusTime/10)));
						Advance ((10/(m_ucScoreMulti+1)),(100/(m_ucScoreMulti+1)),((3*(m_ucScoreMulti+1))+(m_ulBonusTime/10)));
	
						bFound = true;
					}
				}
			}
		}


	//=== standardowe sprawdzenie, szukamy 3-jek

		for (h1=0; h1<=7; h1++)	// sprawdzamy poziomo
		{
			for (h2=0; h2<=5; h2++)
			{
				adres = (h1*8)+h2;

				if (m_cBoard[adres] == m_cBoard[adres+1] && m_cBoard[adres] == m_cBoard[adres+2] &&
					!m_bBoard[adres] &&				// czy my nie sprawdzamy pustych miejsc
					m_fBoardDeltaX[adres]==0 && m_fBoardDeltaY[adres]==0 &&	
					m_fBoardDeltaX[adres+1]==0 && m_fBoardDeltaY[adres+1]==0 &&
					m_fBoardDeltaX[adres+2]==0 && m_fBoardDeltaY[adres+2]==0 )	// sprawdzamy tylko klocki ktore juz nie sa w ruchu

				{
					if (h1==7)	// w ostatniej lini nie sprawdzamy czy pod klockami jest spacja
					{	
						if (m_cBoard[adres]<GEM_ROCK)		// tylko kamyki standardowe
						{
							m_bBoard[adres] = true;
							m_bBoard[adres+1] = true;
							m_bBoard[adres+2] = true;

							m_cScaleBoard[adres] = m_cBoard[adres];
							m_cScaleBoard[adres+1] = m_cBoard[adres+1];
							m_cScaleBoard[adres+2] = m_cBoard[adres+2];						

							m_ulScaleTimer[adres] = (unsigned long)ulTimer;
							m_ulScaleTimer[adres+1] = (unsigned long)ulTimer;
							m_ulScaleTimer[adres+2] = (unsigned long)ulTimer;

							m_iCoin[adres+1] = ulTimer;	// uruchom animacje tutaj 
							
							Advance ((10/(m_ucScoreMulti+1)),(100/(m_ucScoreMulti+1)),((3*(m_ucScoreMulti+1))+(m_ulBonusTime/10)));
						
							bFound = true;
						}
					}
					else
					{
						if (!m_bBoard[((h1+1)*8)+h2] && !m_bBoard[((h1+1)*8)+h2+1] && !m_bBoard[((h1+1)*8)+h2+2])	// czy pod klockami jest spacja ?
						{
							if (m_cBoard[adres]<GEM_ROCK)		// tylko kamyki standardowe
							{
								m_bBoard[adres] = true;
								m_bBoard[adres+1] = true;
								m_bBoard[adres+2] = true;

								m_cScaleBoard[adres] = m_cBoard[adres];
								m_cScaleBoard[adres+1] = m_cBoard[adres+1];
								m_cScaleBoard[adres+2] = m_cBoard[adres+2];						

								m_ulScaleTimer[adres] = (unsigned long)ulTimer;
								m_ulScaleTimer[adres+1] = (unsigned long)ulTimer;
								m_ulScaleTimer[adres+2] = (unsigned long)ulTimer;

								m_iCoin[adres+1] = ulTimer;	// uruchom animacje tutaj 

								Advance ((10/(m_ucScoreMulti+1)),(100/(m_ucScoreMulti+1)),((3*(m_ucScoreMulti+1))+(m_ulBonusTime/10)));

								bFound = true;
							}
						}
					}
				}
			}
		}

		for (h1=0; h1<=5; h1++)	// sprawdzamy pionowo
		{
			for (h2=0; h2<=7; h2++)
			{

				adres = (h1*8)+h2;
				
				if (m_cBoard[adres] == m_cBoard[((h1+1)*8)+h2] && m_cBoard[adres] == m_cBoard[((h1+2)*8)+h2] &&
					!m_bBoard[adres] &&				// czy my nie sprawdzamy pustych miejsc	
					m_fBoardDeltaX[adres] == 0 && m_fBoardDeltaY[adres] == 0 &&
					m_fBoardDeltaX[((h1+1)*8)+h2] == 0 && m_fBoardDeltaY[((h1+1)*8)+h2] == 0 &&
					m_fBoardDeltaX[((h1+2)*8)+h2] == 0 && m_fBoardDeltaY[((h1+2)*8)+h2] == 0)
				{
					if (m_cBoard[adres]<GEM_ROCK)		// tylko kamyki standardowe
					{
						m_bBoard[adres] = true;
						m_bBoard[((h1+1)*8)+h2] = true;
						m_bBoard[((h1+2)*8)+h2] = true;

						m_cScaleBoard[adres] = m_cBoard[adres];
						m_cScaleBoard[((h1+1)*8)+h2] = m_cBoard[((h1+1)*8)+h2];
						m_cScaleBoard[((h1+2)*8)+h2] = m_cBoard[((h1+1)*8)+h2];						

						m_ulScaleTimer[adres] = (unsigned long)ulTimer;
						m_ulScaleTimer[((h1+1)*8)+h2] = (unsigned long)ulTimer;
						m_ulScaleTimer[((h1+2)*8)+h2] = (unsigned long)ulTimer;

						m_iCoin[((h1+1)*8)+h2] = ulTimer;	// uruchom animacje tutaj 

						Advance ((10/(m_ucScoreMulti+1)),(100/(m_ucScoreMulti+1)),((3*(m_ucScoreMulti+1))+(m_ulBonusTime/10)));
	
						bFound = true;
					}
				}
			}
		}

	return bFound; //false;
}

//=== sprawdzamy czy istnieje kombinacja, ale nie przestawiamy klockow
//=== u¿ywane do podpowiedzi i sprawdzenia czy musimy wylosowaæ na nowo klocki

bool eIngame::isMatch3Check(void)
{
	bool bFound;
	int h1,h2;

	bFound = false;

		for (h1=0; h1<=7; h1++)	// sprawdzamy poziomo
		{
			for (h2=0; h2<=5; h2++)
			{
				if (m_cBoard[(h1*8)+h2] == m_cBoard[(h1*8)+h2+1] && m_cBoard[(h1*8)+h2] == m_cBoard[(h1*8)+h2+2])
				{
					if (h1==7)	// w ostatniej lini nie sprawdzamy czy pod klockami jest spacja
					{	
						if (m_cBoard[(h1*8)+h2]<GEM_ROCK)		// tylko kamyki standardowe
							bFound = true;
					}
					else
					{
						if (!m_bBoard[((h1+1)*8)+h2] && !m_bBoard[((h1+1)*8)+h2+1] && !m_bBoard[((h1+1)*8)+h2+2])	// czy pod klockami jest spacja ?
						{
							if (m_cBoard[(h1*8)+h2]<GEM_ROCK)		// tylko kamyki standardowe
								bFound = true;
						}
					}
				}
			}
		}

		for (h1=0; h1<=5; h1++)	// sprawdzamy pionowo
		{
			for (h2=0; h2<=7; h2++)
			{
				if (m_cBoard[(h1*8)+h2] == m_cBoard[((h1+1)*8)+h2] && m_cBoard[(h1*8)+h2] == m_cBoard[((h1+2)*8)+h2])
				{
					if (m_cBoard[(h1*8)+h2]<GEM_ROCK)		// tylko kamyki standardowe
						bFound = true;
				}
			}
		}

	return bFound;//false;
}

//=== aktualizacja wspolrzednych klockow
//=== TODO: delta przesuniêcia klocków powinna byæ liczona z timera

bool eIngame::isMoveGems(unsigned long ulTimer)
{
	bool bFallLock = false;

	for (int i=0; i<64;i++)
	{
		if (m_fBoardDeltaX[i]<0)
		{
			if (m_ulPrevTimer != ulTimer)
				m_fBoardDeltaX[i]+=M3_DELTA;
			
			bFallLock = true;
		}

		if (m_fBoardDeltaX[i]>0)
		{
			if (m_ulPrevTimer != ulTimer)
				m_fBoardDeltaX[i]-=M3_DELTA;
			
			bFallLock = true;
		}

		if (m_fBoardDeltaY[i]<0)
		{
			if (m_ulPrevTimer != ulTimer)
				m_fBoardDeltaY[i]+=M3_DELTA;
			
			bFallLock = true;
		}

		if (m_fBoardDeltaY[i]>0)
		{
			if (m_ulPrevTimer != ulTimer)
				m_fBoardDeltaY[i]-=M3_DELTA;
			
			bFallLock = true;
		}
	}

	return bFallLock;

}


// zwraca liczbe przy konwersji znaku z tablicy
// convert char digit to int and return as char :)

char eIngame::cToDigit(char cDigit)
{
	return char((int)cDigit-'0');
}



//=== rysowanie pasków postêpu i pasku czasu

void eIngame::DrawProgressBar(unsigned long ulTimer)
{
	float	fTimeBar;

	// rysujemy progress bar

	fTimeBar = (float)((ulTimer-m_ulTimerStart)/10);
	fTimeBar = _pScreen->iSizeX()-_pScreen->iSizeX()/8-_pScreen->iSizeX()/8- fTimeBar + m_ulBonusTime;

	if (fTimeBar > _pScreen->iSizeX()-_pScreen->iSizeX()/8)
		fTimeBar = _pScreen->iSizeX()-_pScreen->iSizeX()/8;

	for (int i=(_pScreen->iSizeX()/8); i<_pScreen->iSizeX()-(_pScreen->iSizeX()/8); i+=16)
	{
		m_pGreyBar->Position((float)i,(float)_pScreen->iSizeY()-_pScreen->iSizeY()/8-m_pGreyBar->fSizeY()-m_pGreyBar->fSizeY());
		m_pGreyBar->Render();

		m_pGreyBar->Position((float)i,(float)_pScreen->iSizeY()-_pScreen->iSizeY()/8);
		m_pGreyBar->Render();
	}

	// narysuj timer	
	
	fTimeBar = (fTimeBar-_pScreen->iSizeX()/10) / 32;
	
	if (fTimeBar<=0.0f)	// jezeli skonczyl sie czas to koniec gry
	{
		fTimeBar = 0.0f;
		m_bGameOver = true;
	}

	m_pTimeBar->fScaleX(fTimeBar);
	m_pTimeBar->Position(_pScreen->iSizeX()/8,_pScreen->iSizeY()-_pScreen->iSizeY()/8-m_pGreyBar->fSizeY()-m_pGreyBar->fSizeY());
	m_pTimeBar->Render();

	// narysuj doswiadczenie

	fTimeBar = (float)(m_ulBonusExp/100);

	if (fTimeBar > 100.0f)
	{
		m_ulBonusExp = 0;
		
		if (m_ucScoreMulti!=9)	// level up
		{
			m_ucScoreMulti++;
			m_pPopup->Add(POPUP_FLASH_WHITE,(unsigned long)ulTimer);
		}
		m_ulBonusTime +=1000;	// dodajemy graczowi czas przy awansie

		fTimeBar = 100.0f;
	}

	fTimeBar = (fTimeBar/100) * (_pScreen->iSizeX()-(_pScreen->iSizeX()/8)-(_pScreen->iSizeX()/8));

//	m_pExpBar->fScaleX(fTimeBar);
	m_pExpBar->Resize((float)_pScreen->iSizeX()/8,(float)_pScreen->iSizeY()-_pScreen->iSizeY()/8,
		(float)_pScreen->iSizeX()/8+fTimeBar, (float)_pScreen->iSizeY()-_pScreen->iSizeY()/8+m_pExpBar->fSizeY());
//	m_pExpBar->Position(_pScreen->iSizeX()/8,_pScreen->iSizeY()-_pScreen->iSizeY()/8);
	m_pExpBar->Render();

}

//=== rysuje pojedyncza klatke
//=== TODO: extra klocki dostepne proporcjonalnie do levelu

int eIngame::Render(unsigned long ulTimer, CMouse *pMouse)
{
	int 	iReturn,h1,h2;
	char 	c1,c2;
	char	cScore[8];	//	do konwersji na digits

	iReturn = 0;

	if (m_ulTimerStart == 0)		// czy to pierwsza renderowana klatka ?
	{
		m_ulTimerStart = ulTimer;
		
		if (pMouse->isLeft())	// nie przechwytujmy clicku z menu
			m_bMouseLock = true;

		m_pPopup->Add(POPUP_INGAME_START,ulTimer);
	}

	m_pBackground->Render();
	m_pParticleManager->Render(ulTimer);

	m_pBoard->Position(448,64);		// podkladka, szachownica pod klocki
	m_pBoard->Render();

	DrawProgressBar(ulTimer);

	// sprawdzamy czy trzeba zmienic delte klockow

	if (!m_bGameOver)
		m_bFallLock = isMoveGems(ulTimer);

	if (m_bFallLock)			// zapamietaj czas ostatniego ruchu, jezeli brak ruchu przez 5 sekund to daj podpowiedz
		m_lHintTime = ulTimer;

	// sprawdzamy czy przycisk mozemy odblokowac

	if (m_bMouseLock && !pMouse->isLeft())
		m_bMouseLock=false;

	// sprawdz czy sa trojki

	if (!m_bFallLock) 
		isMatch3(ulTimer);

	// kasujemy dopasowane klocki, true = puste pole

	for (h1=0; h1<64; h1++)
	{
		if (m_bBoard[h1])
			m_cBoard[h1]=-1;		
	}

	// scroll z gory na dol - klocki opadaja

	if (!m_bFallLock)
	{
		for (h1=7; h1>=1; h1--)	// sprawdzamy pionowo od do³u do góry
		{
			if (!m_bFallLock)
			{
				for (h2=0; h2<=7; h2++)
				{
					if (m_bBoard[(h1*8)+h2] == true && m_bBoard[((h1-1)*8)+h2]==false)
					{
						m_bBoard[(h1*8)+h2] = false; 
						m_bBoard[((h1-1)*8)+h2] = true;			
						m_cBoard[(h1*8)+h2] = m_cBoard[((h1-1)*8)+h2];
						m_cBoard[((h1-1)*8)+h2]=-1;	
						m_fBoardDeltaY[(h1*8)+h2]= -64.0f;
					}
				}
			}
		}

		// uzupelniamy gorna linie

		for (h1=0; h1<=7; h1++)
		{
			if (m_bBoard[h1])
			{
				m_bBoard[h1]=false;
				
				if (m_ucScoreMulti<5)		// jezeli etap mniejszy od 5 to dodajemy tylko podstawowe klocki
				{
					m_cBoard[h1]=rand()%7;
				}
				else
				{
					m_cBoard[h1]=rand()%9;		// 8 to kamyk
					if (m_cBoard[h1]==8)		// 9 trzeba zamienic na 11 - bomba i zmniejszyc szanse jej pojawienia sie na 1/5
					{
						if (rand()%5==3)
						{
							m_cBoard[h1]=GEM_BOMB;
						}
						else
						{
							m_cBoard[h1]=rand()%7;
						}
					}
				}
				m_fBoardDeltaY[h1] = -64.0f;
			}
		}
	}

	// narysuj przeskalowane poprzednie klocki

	for (h1=0; h1<8; h1++)
	{
		for (h2=0; h2<8; h2++)
		{
			if (m_cScaleBoard[(h1*8)+h2]!=-1)
			{
				if ((ulTimer-m_ulScaleTimer[(h1*8)+h2])<100.0f)
				{
					float scale = (1+(((float)(ulTimer-m_ulScaleTimer[(h1*8)+h2])/100.0f)));
					m_pGem[m_cScaleBoard[(h1*8)+h2]]->Position((float)(448+(h2*64)+32-(32*scale)),(float)(64+(64*h1)+32-(32*scale)));
					m_pGem[m_cScaleBoard[(h1*8)+h2]]->Scale(scale,scale);
					
					scale = scale - 1.0f;

//todo					m_pGem[m_cScaleBoard[(h1*8)+h2]]->fAlfa((unsigned char)(255-(255*scale)),(unsigned char)(255-(255*scale)),(unsigned char)(255-(255*scale)),(unsigned char)(255-(255*scale)));
					m_pGem[m_cScaleBoard[(h1*8)+h2]]->Render();
				}
				else
				{
					m_cScaleBoard[(h1*8)+h2]=-1;
				}
			}
		}
	}

	// narysuj tablice oraz monety

	for (h1=0; h1<8; h1++)
	{
		for (h2=0; h2<8; h2++)
		{
			if (m_cBoard[(h1*8)+h2]>-1)
			{
				m_pGem[m_cBoard[(h1*8)+h2]]->Position((float)(448+(h2*64)+m_fBoardDeltaX[(h1*8)+h2]),(float)(64+(64*h1)+m_fBoardDeltaY[(h1*8)+h2]));
				m_pGem[m_cBoard[(h1*8)+h2]]->Scale(1.0f,1.0f);
				m_pGem[m_cBoard[(h1*8)+h2]]->fAlfa(1.0f);
				m_pGem[m_cBoard[(h1*8)+h2]]->Render();
			}

			// czy rysujemy monety nad klockami

			if (m_iCoin[(h1*8)+h2]!=-1)
			{
				if ((ulTimer - m_iCoin[(h1*8)+h2])>255) // czy minal czas 255 ? 
				{
					m_iCoin[(h1*8)+h2]=-1;	// zerujemy 
				}
				else
				{
					m_pCoin->Render((ulTimer>>2)%m_pCoin->iFrameCount(),448+(h2*64),64+(64*h1)- (ulTimer - m_iCoin[(h1*8)+h2]), (unsigned char)255-(ulTimer - m_iCoin[(h1*8)+h2]));
				}
			}
		}
	}

	// jezeli przesuniecie jest wieksze od +/- 64 to zdejmujemy blokade myszy

	if (pMouse->fGetClickDeltaX()>64.0f || pMouse->fGetClickDeltaY()>64.0f || pMouse->fGetClickDeltaX()<-64.0f || pMouse->fGetClickDeltaY()<-64.0f)
	{
		m_bMouseLock = false;
		pMouse->fMouseXClick(pMouse->fMouseX());
		pMouse->fMouseYClick(pMouse->fMouseY());
	}

	// czy kliknieto

	if (pMouse->fMouseX()>448 && pMouse->fMouseX()<960 && pMouse->fMouseY()>64 && pMouse->fMouseY()<576 && pMouse->isLeft() && !m_bMouseLock && !m_bGameOver && !m_bFallLock)
	{
		h1 = (int)((pMouse->fMouseX()-448)/64);	// X na tablicy
		h2 = (int)((pMouse->fMouseY()-64)/64);	// Y na tablicy

		if (m_cClickedA==-1)
		{
			m_cClickedA=(h2*8)+h1;
			m_iClickedAx = 448 +(h1*64);
			m_iClickedAy = 64 + (h2*64);
		}
		else if (m_cClickedB==-1)
		{
			if (m_cClickedA!=(h2*8)+h1)			// czy to nie ten sam co #1 ? 
			{
				if ( (((m_cClickedA-1 == (h2*8)+h1) || (m_cClickedA+1 == (h2*8)+h1)) && m_iClickedAy == 64 + (h2*64)) || (m_cClickedA+8 == (h2*8)+h1) || (m_cClickedA-8 == (h2*8)+h1) ) // czy to klik obok ?
				{					
					m_cClickedB=(h2*8)+h1;			// numer kliknietego klocka B na tablicy
					m_iClickedBx = 448 +(h1*64);	// wspolrzedne X klocka B
					m_iClickedBy = 64 + (h2*64);	// wspolrzedne Y klocka B
				}
				else	// to nie jest click obok wiêc to bêdzie teraz nasz klocek #1
				{
					m_cClickedA=(h2*8)+h1;
					m_iClickedAx = 448 +(h1*64);
					m_iClickedAy = 64 + (h2*64);
				}
			}
			else	// jesli to samo to kasujemy zaznaczenie
			{
				m_cClickedA = -1;
				m_cClickedB = -1;
				m_iClickedAx = m_iClickedAy = m_iClickedBx = m_iClickedBy = -1; 		
			}
		}	

		// jezeli ktorys z kliknietych kamykow to skala to kasujemy zaznaczenia

		if (m_cBoard[m_cClickedA]==GEM_ROCK || m_cBoard[m_cClickedB]==GEM_ROCK)
		{
			m_cClickedA = -1;
			m_cClickedB = -1;
			m_iClickedAx = m_iClickedAy = m_iClickedBx = m_iClickedBy = -1; 				
		}

		// jezeli ktorys z klikniety kamykow to bomba, to wybuchamy klocki 

		if (m_cBoard[m_cClickedA]==GEM_BOMB || m_cBoard[m_cClickedB]==GEM_BOMB)
		{
				m_cBoard[(h2*8)+h1] = -1;
				m_bBoard[(h2*8)+h1] = true;
				m_iCoin[(h2*8)+h1] = ulTimer;
				
				if (h1>0)	// po lewej
				{
					m_cBoard[(h2*8)+h1-1] = -1;
					m_bBoard[(h2*8)+h1-1] = true;
					m_iCoin[(h2*8)+h1-1] = ulTimer;
				}					

				if (h1<7)	// po prawej
				{
					m_cBoard[(h2*8)+h1+1] = -1;
					m_bBoard[(h2*8)+h1+1] = true;
					m_iCoin[(h2*8)+h1+1] = ulTimer;
				}			

				if (h2>0)	// na gorze
				{
					m_cBoard[((h2-1)*8)+h1] = -1;
					m_bBoard[((h2-1)*8)+h1] = true;
					m_iCoin[((h2-1)*8)+h1] = ulTimer;			
				}

				if (h2<7) // na dole
				{
					m_cBoard[((h2+1)*8)+h1] = -1;
					m_bBoard[((h2+1)*8)+h1] = true;
					m_iCoin[((h2+1)*8)+h1] = ulTimer;
				}

				if (h1>0 && h2>0)	// na gorze po lewej
				{
					m_cBoard[((h2-1)*8)+h1-1] = -1;
					m_bBoard[((h2-1)*8)+h1-1] = true;
					m_iCoin[((h2-1)*8)+h1-1] = ulTimer;					
				}

				if (h2>0 && h1<7)	// na gorze po prawej
				{
					m_cBoard[((h2-1)*8)+h1+1] = -1;
					m_bBoard[((h2-1)*8)+h1+1] = true;
					m_iCoin[((h2-1)*8)+h1+1] = ulTimer;
				}

				if (h2<7 && h1>0)	// na dole po lewej
				{
					m_cBoard[((h2+1)*8)+h1-1] = -1;
					m_bBoard[((h2+1)*8)+h1-1] = true;
					m_iCoin[((h2+1)*8)+h1-1] = ulTimer;
				}

				if (h1<7 && h2<7)	// na dole po prawej
				{
					m_cBoard[((h2+1)*8)+h1+1] = -1;
					m_bBoard[((h2+1)*8)+h1+1] = true;
					m_iCoin[((h2+1)*8)+h1+1] = ulTimer;
				}			

			m_cClickedA = -1;
			m_cClickedB = -1;
			m_iClickedAx = m_iClickedAy = m_iClickedBx = m_iClickedBy = -1; 						
		}

		// jezeli ktorys z kamykow to diament to kasujemy linie w pionie i w poziomie

		if (m_cBoard[m_cClickedA]==GEM_DIAMOND || m_cBoard[m_cClickedB]==GEM_DIAMOND)
		{

			// dodajemy monete tylko tam gdzie jest diament

			if (m_cBoard[m_cClickedA]==GEM_DIAMOND)
			{
				m_iCoin[m_cClickedA] = ulTimer;
			}
			else
			{
				m_iCoin[m_cClickedB] = ulTimer;
			}

			// kasujemy w poziomie i w pionie

			for (int i=0; i<8; i++)
			{
				m_cScaleBoard[(h2*8)+i] = m_cBoard[(h2*8)+i];
				m_ulScaleTimer[(h2*8)+i] = (unsigned long)ulTimer;

				m_cScaleBoard[(i*8)+h1] = m_cBoard[(i*8)+h1];
				m_ulScaleTimer[(i*8)+h1] = (unsigned long)ulTimer;

				m_cBoard[(h2*8)+i] = -1;
				m_bBoard[(h2*8)+i] = true;

				m_cBoard[(i*8)+h1] = -1;
				m_bBoard[(i*8)+h1] = true;
			}

			m_cClickedA = -1;
			m_cClickedB = -1;
			m_iClickedAx = m_iClickedAy = m_iClickedBx = m_iClickedBy = -1; 						
		}

		m_bMouseLock = true;	// zablokuj myszke zeby w nastepnej klatce nie chwycil tego samego 

	}

	// prawy przycisk myszy kasuje zaznaczony kamyk

	if (pMouse->isRight())
	{
		m_cClickedA = -1;
		m_cClickedB = -1;
		m_iClickedAx = m_iClickedAy = m_iClickedBx = m_iClickedBy = -1; 
	}

	// rysowanie oznaczenia na kamykach

	if (m_iClickedAx!=-1)
	{
		m_pHint->Position((float)m_iClickedAx, (float)m_iClickedAy);
		m_pHint->fRotation(0.f);
		m_pHint->Render();
	}

	if (m_iClickedBx!=-1)
	{
		m_pHint->Position((float)m_iClickedBx,(float)m_iClickedBy);
		m_pHint->fRotation(0.f);
		m_pHint->Render();
	}

	// zamiana kamykow kolejnoscia

	if (m_cClickedA!=-1 && m_cClickedB!=-1)	
	{
		// jezeli jeden z zaznaczonych kamykow to teczowy to usuwamy wszystkie tego typu kamyki z planszy jak drugi typ

		if (m_cBoard[m_cClickedA] == GEM_RAINBOW || m_cBoard[m_cClickedB] == GEM_RAINBOW)
		{

			if (m_cBoard[m_cClickedA] == GEM_RAINBOW)
			{
				h2 = m_cBoard[m_cClickedB]; // zapamietaj do kasowania

				for (h1=0; h1<64; h1++)
				{
					if (m_cBoard[h1]== h2)
					{
						m_cScaleBoard[h1] = m_cBoard[h1];
						m_ulScaleTimer[h1] = (unsigned long)ulTimer;

						m_cBoard[h1]=-1;
						m_bBoard[h1]=true;
						m_iCoin[h1] = ulTimer;	// dodajemy monete
					}
				}

				m_cBoard[m_cClickedA] = -1;
				m_bBoard[m_cClickedA] = true;
				m_iCoin[m_cClickedA] = ulTimer;
			}
			else
			{
				h2 = m_cBoard[m_cClickedA];
				
				for (int i=0; i<64; i++)
				{
					if (m_cBoard[i]==h2)
					{
						m_cBoard[i]=-1;
						m_bBoard[i]=true;
						m_iCoin[i] = ulTimer;
					}
				}

				m_cBoard[m_cClickedB] = -1;
				m_bBoard[m_cClickedB] = true;
				m_iCoin[m_cClickedB] = ulTimer;

			}

			m_cClickedA = -1;
			m_cClickedB = -1;
			m_iClickedAx = m_iClickedAy = m_iClickedBx = m_iClickedBy = -1; 
			m_bMouseLock = true;
		}
	}

	if (m_cClickedA!=-1 && m_cClickedB!=-1)	// swap
	{
		// zamiana kolejnoscia
		
		h1=m_cBoard[m_cClickedA];
		m_cBoard[m_cClickedA] = m_cBoard[m_cClickedB];
		m_cBoard[m_cClickedB] = h1;	

		if (!isMatch3Check()) // jak nie ma dopasowania po ruchu to cofamy
		{
			h1=m_cBoard[m_cClickedA];
			m_cBoard[m_cClickedA] = m_cBoard[m_cClickedB];
			m_cBoard[m_cClickedB] = h1;	

			// tutaj jakis event dzwiekowy

		}
		else
		{
			if (abs(m_cClickedA-m_cClickedB)==1)	// czy klocki sa obok siebie w poziomie?
			{
				if (m_cClickedA>m_cClickedB)
				{
					m_fBoardDeltaX[m_cClickedA] = -64.0f;
					m_fBoardDeltaX[m_cClickedB] = 64.0f;
				}
				else
				{
					m_fBoardDeltaX[m_cClickedA] = 64.0f;
					m_fBoardDeltaX[m_cClickedB] = -64.0f;
				}
			}
			else	// klocki sa obok siebie w pionie			
			{
				if (m_cClickedA>m_cClickedB)
				{
					m_fBoardDeltaY[m_cClickedA] = -64.0f;
					m_fBoardDeltaY[m_cClickedB] = 64.0f;
				}
				else
				{
					m_fBoardDeltaY[m_cClickedA] = 64.0f;
					m_fBoardDeltaY[m_cClickedB] = -64.0f;
				}
			}
			m_bHint = false;		// znikamy pomoc
		}

		m_cClickedA = -1;
		m_cClickedB = -1;
		m_iClickedAx = m_iClickedAy = m_iClickedBx = m_iClickedBy = -1; 
		m_bMouseLock = true;
	}

	// sprawdzamy czy sa jeszcze mozliwe ruchy
	
	c2=0;

	for (h1=0; h1<=7; h1++) // czy mozliwe ruchy w poziomie
	{
		for (h2=0; h2<=6; h2++)
		{
			if (m_cBoard[(h1*8)+h2]!=-1 && m_cBoard[(h1*8)+h2+1]!=-1 && 
				m_cBoard[(h1*8)+h2]<GEM_ROCK && m_cBoard[(h1*8)+h2+1]<GEM_ROCK)	// sprawdzamy tylko kamyki standardowe
			{
				c1 = m_cBoard[(h1*8)+h2];
				m_cBoard[(h1*8)+h2] = m_cBoard[(h1*8)+h2+1];
				m_cBoard[(h1*8)+h2+1] = c1;

			    if (isMatch3Check())
				{
					c2=1;
					m_iHintX = 448 + (h2*64);
					m_iHintY = 64 + (h1*64);
				}

				c1 = m_cBoard[(h1*8)+h2];
				m_cBoard[(h1*8)+h2] = m_cBoard[(h1*8)+h2+1];
				m_cBoard[(h1*8)+h2+1] = c1;
			}
		}
	}

	for (h1=0; h1<=6; h1++) // czy mozliwe ruchy w pionie
	{
		for (h2=0; h2<=7; h2++)
		{
			if (m_cBoard[(h1*8)+h2]!=-1 && m_cBoard[((h1+1)*8)+h2]!=-1 &&
				m_cBoard[(h1*8)+h2]<GEM_ROCK && m_cBoard[((h1+1)*8)+h2]<GEM_ROCK)	// sprawdzamy tylko kamyki standardowe
			{
				c1 = m_cBoard[(h1*8)+h2];
				m_cBoard[(h1*8)+h2] = m_cBoard[((h1+1)*8)+h2];
				m_cBoard[((h1+1)*8)+h2] = c1;

			    if (isMatch3Check())
				{
					c2=1;
					m_iHintX = 448 + (h2*64);
					m_iHintY = 64 + (h1*64);
				}
				c1 = m_cBoard[(h1*8)+h2];
				m_cBoard[(h1*8)+h2] = m_cBoard[((h1+1)*8)+h2];
				m_cBoard[((h1+1)*8)+h2] = c1;
			}
		}
	}

	if (c2)	// sprawdzamy czy mozemy dac podpowiedz
	{
		if ((ulTimer - m_lHintTime)>1000 || m_bHint)
		{
			m_pHint->Position((float)m_iHintX+(m_pHint->fSizeX()/2), (float)m_iHintY+(m_pHint->fSizeY()/2));
			m_pHint->fRotation(ulTimer/5);
			m_pHint->RenderC();
		}
	}
	else
	{
		if (!m_bFallLock) // kasujemy ostatnia linie poniewaz nie ma ruchow mozliwych
		{
			// zamieniamy to na postawienie krysztalowego klocka w losowym miejscu na planszy
			bool bSpecial=false;

			for (int i=0; i<64; i++)
			{
				if (m_cBoard[i] == GEM_RAINBOW || m_cBoard[i] == GEM_DIAMOND || m_cBoard[i] == GEM_BOMB)
					bSpecial = true;
			}

			// jezeli na planszy nie ma zadnego klocka specjalnego to zamieniamy jeden na teczowy

			if (!bSpecial)
				m_cBoard[ulTimer%63] = GEM_RAINBOW;

		}
	}

	// rysujemy licznik punktow

	sprintf(cScore,"%.7d",m_ulScore);

	m_pNumber[cToDigit(cScore[0])]->Position(32,500);
	m_pNumber[cToDigit(cScore[0])]->Render();

	m_pNumber[cToDigit(cScore[1])]->Position(32+32,500);
	m_pNumber[cToDigit(cScore[1])]->Render();

	m_pNumber[cToDigit(cScore[2])]->Position(32+64,500);
	m_pNumber[cToDigit(cScore[2])]->Render();

	m_pNumber[cToDigit(cScore[3])]->Position(32+96,500);
	m_pNumber[cToDigit(cScore[3])]->Render();

	m_pNumber[cToDigit(cScore[4])]->Position(32+128,500);
	m_pNumber[cToDigit(cScore[4])]->Render();

	m_pNumber[cToDigit(cScore[5])]->Position(32+160,500);
	m_pNumber[cToDigit(cScore[5])]->Render();

	m_pNumber[cToDigit(cScore[6])]->Position(32+192,500);
	m_pNumber[cToDigit(cScore[6])]->Render();

	// rysujemy game over

	if (m_bGameOver)
	{
		if (m_lInGameOver==0)
			m_lInGameOver=ulTimer;

		m_pGameOver->Render();

		if (ulTimer-m_lInGameOver>500)	// wychodzimy z gry
			iReturn = -1;		

	}

	// przyciski menu i hint, score multi info, jezeli nie ma gameover

	if (!m_bGameOver)
	{
		if (m_pButtonMenu->Render(pMouse)==ON_LEFT)
			iReturn = -1; 

		if (m_pButtonHint->Render(pMouse)==ON_LEFT && !m_bMouseLock)
		{
			m_bHint = true;	
			m_ulScore = (unsigned long)(m_ulScore * 0.9);	// zabieramy 10% punktow
			m_bMouseLock = true;
		}	

		m_pScoreMulti[m_ucScoreMulti]->Position(200,300);
		m_pScoreMulti[m_ucScoreMulti]->Render();

	}

	m_ulPrevTimer = ulTimer;		// zapamietaj czas ostatniej klatki

	m_bPrevFallLock = m_bFallLock;

	if (iReturn<0)	// zapisujemy punkty do dodania do profilu
	{
		CProfile *pProfile;

		pProfile = new CProfile(USERS_FILE);
		pProfile->bLoad();
		pProfile->AddScore(m_ulScore);		
		pProfile->bSave();
		delete pProfile;

		if (_uiMatchCount>100)
			_ucNewTroophy[TROOPHY_MATCH_100] = 1;

		if (_uiMatchCount>1000)
			_ucNewTroophy[TROOPHY_MATCH_1000] = 1;

	}

	// sprawdzamy roznice punktow w ciagu ostatnich 10 sekund, jezeli jest wystarzcajaco duza to dajemy popup

	if (m_ulScore != m_ulScore1000 && m_ulScore > m_ulScore1000)		// zmienily sie punkty, wiec sprawdzamy czy w ciagu 10 sekund nabilismy 100, pomijamy przypadek gdy gracz ma mniej punktow niz poprzednio bo nacisnal hint
	{
		if ((ulTimer-m_ulTimer1000)>1000)	// minelo 10 sekund, przepisujemy timer i punkty do nowego
		{
			m_ulTimer1000 = ulTimer;
			m_ulScore1000 = m_ulScore;
		}
		else
		{
			if ((m_ulScore-m_ulScore1000) > (1000+(1000 * m_ucScoreMulti)))	// nie minelo 10 sekund, jezeli roznica punktow > 100 to dajemy popup
			{
				switch(ulTimer%5)
				{
					case 0:
						m_pPopup->Add(POPUP_INGAME_GOOD1,(unsigned long)ulTimer);
					break;

					case 1:
						m_pPopup->Add(POPUP_INGAME_GOOD2,(unsigned long)ulTimer);
					break;

					case 2:
						m_pPopup->Add(POPUP_INGAME_GOOD3,(unsigned long)ulTimer);
					break;

					case 3:
						m_pPopup->Add(POPUP_INGAME_GOOD4,(unsigned long)ulTimer);
					break;

					case 4:
						m_pPopup->Add(POPUP_INGAME_GOOD5,(unsigned long)ulTimer);
					break;
				}

				m_ulTimer1000 = ulTimer;
				m_ulScore1000 = m_ulScore;
			}
		}
	}


	// renderujemy popup jezeli jakis jest

	if (!m_bGameOver)
	{
		m_pPopup->Render(ulTimer);
	}

	return iReturn;
}

unsigned long eIngame::ulGetScore(void)		// zwraca liczbe punktow z tej serii
{
	return m_ulScore;
}

void eIngame::AddScore(long lScore)		// dodaje liczbe punktow
{
	m_ulScore += lScore;
}

unsigned char eIngame::ucNewTroophy(int i)
{
	return _ucNewTroophy[i];
}

//end
