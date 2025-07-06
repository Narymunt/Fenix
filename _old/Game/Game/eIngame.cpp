#include "eIngame.h"

#pragma warning(disable : 4996)	// sprintf unsafe

// class constructor

eIngame::eIngame() :
_pFXManager(NULL)
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

	_pScore100 = NULL;
	_pScore250 = NULL;
	_pScore500 = NULL;
	_pScore1000 = NULL;

	m_pPopup = NULL;

	// gems animations

	_pGemRock = NULL;
	_pGemDiamond = NULL;
	_pGemRainbow = NULL;
	_pGemBomb = NULL;

	// audio chunks

	_pMSuper = NULL;
	_pMRainbow = NULL;
	_pMDiamond = NULL;
	_pMLevelUp = NULL;
	_pMClick = NULL;
	_pMBomb = NULL;

	_pGameOverSFX = NULL;
	_pTikTakSFX = NULL;

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

	_iHintID = -1;
	m_bHint = false;

	m_ulScore = 0;			// iloœæ punktów
	m_ucScoreMulti = (unsigned char) iLevel -1;		// jaki mno¿nik

	m_ulTimer1000 = 0;		// czas 10 sek temu
	m_ulScore1000 = 0;		// punkty 10 sek temu
	m_ulTimerStart = 0;	// poczatek

	m_pTimeBar = new CSprite(pScreen,"BAR_RED");
	m_pExpBar =  new CSprite(pScreen,"BAR_GREEN");
	m_pGreyBar = new CSprite(pScreen,"BAR_GREY");

	m_pBoard = new CSprite(pScreen,"GFX_BOARD");

	m_pGameOver = new CSprite(pScreen,"GFX_GAMEOVER_SCREEN");
	
	m_pHint = new CSprite(pScreen,"GFX_HINT");
	m_lHintTime = 0;

	m_pBlack = new CSprite(pScreen,"GFX_BLACK100_SCREEN");

	_pFXManager = new CFXManager(pScreen);
	
	// ikony x1,x2 itd. 

	for (int i=0; i<=9; i++)
	{
		sprintf(cBuffer,"X%d",i+1);
		m_pScoreMulti[i] = new CSprite(pScreen,cBuffer);
	}

	switch(iLevel)
	{
		case 1:
			m_pBackground = new CSprite(pScreen,"LEVEL01_SCREEN");
			
			m_pParticleManager = new CParticle2DManager((char*)"k2.png", 150,
				-100, -100, pScreen->iSizeX()+100, pScreen->iSizeY()+100,
				0.01f, 0.01f, 0.3f, 0.3f,
				0.5f, -.001f, .001f,
				0.5f, -1.0f, 1.0f,
				1000, 10000, pScreen);

//			m_pParticleManager->Color(1, 0, 0, 1);

			break;

		case 2:
			m_pBackground = new CSprite(pScreen,"LEVEL02_SCREEN");
			
			m_pParticleManager = new CParticle2DManager((char*)"k6.png", 150,
				-100, -100, pScreen->iSizeX()+100, pScreen->iSizeY()+100,
				0.01f, 0.01f, 0.3f, 0.3f,
				0.5f, -.001f, .001f,
				0.5f, -1.0f, 1.0f,
				1000, 10000, pScreen);

//			m_pParticleManager->Color(0, 1, 0, 1);

			break;

		case 3:
			m_pBackground = new CSprite(pScreen,"LEVEL03_SCREEN");
			
			m_pParticleManager = new CParticle2DManager((char*)"k3.png", 150,
				-100, -100, pScreen->iSizeX()+100, pScreen->iSizeY()+100,
				0.01f, 0.01f, 0.3f, 0.3f,
				0.5f, -.001f, .001f,
				0.5f, -1.0f, 1.0f,
				1000, 10000, pScreen);

//			m_pParticleManager->Color(0, 0, 1, 1);

			break;

		case 4:
			m_pBackground = new CSprite(pScreen,"LEVEL04_SCREEN");
			
			m_pParticleManager = new CParticle2DManager((char*)"k5.png", 150,
				-100, -100, pScreen->iSizeX() + 100, pScreen->iSizeY() + 100,
				0.01f, 0.01f, 0.3f, 0.3f,
				0.5f, -.001f, .001f,
				0.5f, -1.0f, 1.0f,
				1000, 10000, pScreen);

//			m_pParticleManager->Color(1, 1, 0, 1);

			break;

		case 5:
			m_pBackground = new CSprite(pScreen,"LEVEL05_SCREEN");
			
			m_pParticleManager = new CParticle2DManager((char*)"k6.png", 150,
				-100, -100, pScreen->iSizeX() + 100, pScreen->iSizeY() + 100,
				0.01f, 0.01f, 0.3f, 0.3f,
				0.5f, -.001f, .001f,
				0.5f, -1.0f, 1.0f,
				1000, 10000, pScreen);

//			m_pParticleManager->Color(1, 0, 1, 1);

			break;
		
		case 6:
			m_pBackground = new CSprite(pScreen,"LEVEL06_SCREEN");
			
			m_pParticleManager = new CParticle2DManager((char*)"k3.png", 150,
				-100, -100, pScreen->iSizeX() + 100, pScreen->iSizeY() + 100,
				0.01f, 0.01f, 0.3f, 0.3f,
				0.5f, -.001f, .001f,
				0.5f, -1.0f, 1.0f,
				1000, 10000, pScreen);

//			m_pParticleManager->Color(0, 1, 1, 1);

			break;
		
		case 7:
			m_pBackground = new CSprite(pScreen,"LEVEL07_SCREEN");
			
			m_pParticleManager = new CParticle2DManager((char*)"m2.png", 150,
				-100, -100, pScreen->iSizeX() + 100, pScreen->iSizeY() + 100,
				0.01f, 0.01f, 0.3f, 0.3f,
				0.5f, -.001f, .001f,
				0.5f, -1.0f, 1.0f,
				1000, 10000, pScreen);

			m_pParticleManager->Color(1, 0, 1, 1);

			break;
	}
	
	// obrazki kamykow

	for (int i=0; i<=GEMS_COUNT-1; i++)
	{
		sprintf(cBuffer,"GEM%d",i+1);
		m_pGem[i] = new CSprite(pScreen, cBuffer);
	}

	_pGemRock = new CAnimation(pScreen,"GEM8");
	_pGemDiamond = new CAnimation(pScreen,"GEM9");
	_pGemRainbow = new CAnimation(pScreen,"GEM10");
	_pGemBomb = new CAnimation(pScreen,"GEM11");

	// przyciski podpowiedzi i wyjscia do menu

	m_pButtonHint = new CButton(pScreen, "BUTTON_HINT");
	m_pButtonMenu = new CButton(pScreen, "BUTTON_MENU_INGAME");

	// numer 

	for (int i=0; i<=9; i++)
	{
		sprintf(cBuffer,"GFX_%d",i);
		m_pNumber[i] = new CSprite(pScreen,cBuffer);
	}

	for (int i=0; i<64; i++)
	{
		m_cBoard[i]= 0;
		m_bBoard[i]= true;
		m_fBoardDeltaX[i] = 0.0f;
		m_fBoardDeltaY[i] = 0.0f;

		m_cScaleBoard[i]=-1;
		m_fScaleBoard[i]= 1.0f;
		m_ulScaleTimer[i]= 0;
	}

	// popup manager

	m_pPopup = new CPopup();
	m_pPopup->Open(pScreen);

	// punkty nad klockami

	_pScore100 = new CSprite(pScreen,"GFX_SCORE100");
	_pScore250 = new CSprite(pScreen,"GFX_SCORE250");
	_pScore500 = new CSprite(pScreen,"GFX_SCORE500");
	_pScore1000 = new CSprite(pScreen,"GFX_SCORE1000");

	for (int i=0; i<64; i++)
	{
		m_iCoin[i] = -1;
		_sCoin[i] = 0;
	}
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

	// init all audio chunks

	_pMSuper = Mix_LoadWAV("data/super.ogg");
	_pMRainbow = Mix_LoadWAV("data/rainbow.ogg");
	_pMDiamond = Mix_LoadWAV("data/diamond.ogg");
	_pMLevelUp = Mix_LoadWAV("data/level_up.ogg");
	_pMClick = Mix_LoadWAV("data/click.ogg");
	_pMBomb = Mix_LoadWAV("data/bomb.ogg");
	_pGameOverSFX = Mix_LoadWAV("data/gameover.ogg");
	_pTikTakSFX = Mix_LoadWAV("data/tiktak.ogg");

	// offset dla tablicy

	if (pScreen->iSizeX() == 1024 && pScreen->iSizeY() == 768)
	{
		_uiBoardOffsetY = 64;
	}
	else if (pScreen->iSizeX() == 1366)
	{
		_uiBoardOffsetY = 64;
	}
	else if (pScreen->iSizeX() == 1920)
	{
		_uiBoardOffsetY = 64;
	}
	else if (pScreen->iSizeX() == 2560)
	{
		_uiBoardOffsetY = 128;
	}

	_isGameOverSFX = false;	// jeszcze nie odtworzylismy dzwieku game over 
	_isTikTakSFX = false;	// nie odtwarzamy tiktak

	if (pScreen->iSizeX() < 1500)
	{
		M3_DELTA = 16.0f;
	}
	else
	{
		M3_DELTA = 16.0f;
	}

	if (_pScreen->iSizeX() < 1500)
	{
		_ucGemSize = 64;
		_ucGemSizeHalf = 32;
	}
	else if (_pScreen->iSizeX() == 1920)
	{
		_ucGemSize = 96;
		_ucGemSizeHalf = 48;
	}
	else if (_pScreen->iSizeX() == 2560)
	{
		_ucGemSize = 128;
		_ucGemSizeHalf = 64;
	}

	_isActive = true;	// data loaded

}

// free graphics and music, but keep the required data

void eIngame::Close(void)
{
	SafeDelete(_pFXManager);

	SafeDelete(m_pBoard);
	SafeDelete(m_pBlack);
	SafeDelete(m_pBackground);
	
	SafeDelete(m_pTimeBar);
	SafeDelete(m_pExpBar);
	SafeDelete(m_pGreyBar);

	SafeDelete(m_pGameOver);

	for (int i=0; i<=GEMS_COUNT; i++)
		SafeDelete(m_pGem[i]);

	SafeDelete(_pGemRock);
	SafeDelete(_pGemDiamond);
	SafeDelete(_pGemRainbow);
	SafeDelete(_pGemBomb);

	for (int i=0; i<10; i++)
		SafeDelete(m_pNumber[i]);

	SafeDelete(m_pParticleManager);
	SafeDelete(m_pButtonMenu);
	SafeDelete(m_pButtonHint);

	for (int i=0; i<=9; i++)
		SafeDelete(m_pScoreMulti[i]);

	SafeDelete(m_pPopup);
	SafeDelete(m_pHint);

	SafeDelete(_pScore100);
	SafeDelete(_pScore250);
	SafeDelete(_pScore500);
	SafeDelete(_pScore1000);

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

	if (_pGameOverSFX != NULL)
	{
		Mix_FreeChunk(_pGameOverSFX);
		_pGameOverSFX = NULL;
	}

	if (_pTikTakSFX != NULL)
	{
		Mix_FreeChunk(_pTikTakSFX);
		_pTikTakSFX = NULL;
	}

	m_ulTimerStart = 0;	// poczatek

	m_bHint = false;

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
				Mix_PlayChannel(-1, _pMDiamond,0);

				m_iCoin[adres] = ulTimer;	// dodajemy monetê
				_sCoin[adres] = 500;		// dajemy +250
				Advance(0,50,500);

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
				Mix_PlayChannel(-1, _pMDiamond,0);

				m_iCoin[adres+2] = ulTimer;	// dodajemy monetê
				_sCoin[adres+2] = 500;		// dajemy +250
				Advance(0,50,500);

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
				Mix_PlayChannel(-1, _pMDiamond,0);

				m_iCoin[((h1+2)*8)+h2] = ulTimer;	// dodajemy monetê
				_sCoin[((h1+2)*8)+h2] = 500;		// dajemy +250
				Advance(0,50,500);

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
				Mix_PlayChannel(-1, _pMDiamond,0);

				m_iCoin[adres+2] = ulTimer;	// dodajemy monetê
				_sCoin[adres+2] = 500;		// dajemy +250
				Advance(0,50,500);

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
							m_iCoin[adres+2] = ulTimer;	// dodajemy monetê
							_sCoin[adres+2] = 1000;		// dajemy +250
							Advance(0,100,1000);

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

							Advance ((10/(m_ucScoreMulti+1)),(100/(m_ucScoreMulti+1)),((3*(m_ucScoreMulti+1))+(m_ulBonusTime/10)));
							Mix_PlayChannel(-1, _pMRainbow,0);	
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
								m_iCoin[adres+2] = ulTimer;	// dodajemy monetê
								_sCoin[adres+2] = 1000;		// dajemy +250
								Advance(0,100,1000);

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

								Advance ((10/(m_ucScoreMulti+1)),(100/(m_ucScoreMulti+1)),((3*(m_ucScoreMulti+1))+(m_ulBonusTime/10)));
								Mix_PlayChannel(-1, _pMRainbow,0);
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
						m_iCoin[((h1+2)*8)+h2] = ulTimer;	// dodajemy monetê
						_sCoin[((h1+2)*8)+h2] = 1000;		// dajemy +250
						Advance(0,100,1000);

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

						Advance ((10/(m_ucScoreMulti+1)),(100/(m_ucScoreMulti+1)),((3*(m_ucScoreMulti+1))+(m_ulBonusTime/10)));
						Mix_PlayChannel(-1, _pMRainbow,0);	
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

							m_iCoin[adres] = ulTimer;	// dodajemy monetê
							_sCoin[adres] = 100;		// dajemy +250
							m_iCoin[adres+1] = ulTimer;	// dodajemy monetê
							_sCoin[adres+1] = 100;		// dajemy +250
							m_iCoin[adres+2] = ulTimer;	// dodajemy monetê
							_sCoin[adres+2] = 100;		// dajemy +250
							m_iCoin[adres+3] = ulTimer;	// dodajemy monetê
							_sCoin[adres+3] = 100;		// dajemy +250

							Advance(0,40,400);

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
					else
					{
						if (!m_bBoard[((h1+1)*8)+h2] && !m_bBoard[((h1+1)*8)+h2+1] && !m_bBoard[((h1+1)*8)+h2+2] && !m_bBoard[((h1+1)*8)+h2+3])	// czy pod klockami jest spacja ?
						{
							if (m_cBoard[adres]<GEM_ROCK)		// tylko kamyki standardowe
							{
								m_bBoard[adres] = true;
								m_bBoard[adres+1] = true;
								m_bBoard[adres+2] = true;
								m_bBoard[adres+3] = true;

								m_iCoin[adres] = ulTimer;	// dodajemy monetê
								_sCoin[adres] = 100;		// dajemy +250
								m_iCoin[adres+1] = ulTimer;	// dodajemy monetê
								_sCoin[adres+1] = 100;		// dajemy +250
								m_iCoin[adres+2] = ulTimer;	// dodajemy monetê
								_sCoin[adres+2] = 100;		// dajemy +250
								m_iCoin[adres+3] = ulTimer;	// dodajemy monetê
								_sCoin[adres+3] = 100;		// dajemy +250

								Advance(0,40,400);

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

						m_iCoin[adres] = ulTimer;	// dodajemy monetê
						_sCoin[adres] = 100;		// dajemy +250
						m_iCoin[((h1+1)*8)+h2] = ulTimer;	// dodajemy monetê
						_sCoin[((h1+1)*8)+h2] = 100;		// dajemy +250
						m_iCoin[((h1+2)*8)+h2] = ulTimer;	// dodajemy monetê
						_sCoin[((h1+2)*8)+h2] = 100;		// dajemy +250
						m_iCoin[((h1+3)*8)+h2] = ulTimer;	// dodajemy monetê
						_sCoin[((h1+3)*8)+h2] = 100;		// dajemy +250

						Advance(0,40,400);

						m_cScaleBoard[adres] = m_cBoard[adres];
						m_cScaleBoard[((h1+1)*8)+h2] = m_cBoard[((h1+1)*8)+h2];
						m_cScaleBoard[((h1+2)*8)+h2] = m_cBoard[((h1+2)*8)+h2];						
						m_cScaleBoard[((h1+3)*8)+h2] = m_cBoard[((h1+3)*8)+h2];

						m_ulScaleTimer[adres] = (unsigned long)ulTimer;
						m_ulScaleTimer[((h1+1)*8)+h2] = (unsigned long)ulTimer;
						m_ulScaleTimer[((h1+2)*8)+h2] = (unsigned long)ulTimer;
						m_ulScaleTimer[((h1+3)*8)+h2] = (unsigned long)ulTimer;

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
							_sCoin[adres+1] = 100;
							Advance(0,10,100);

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
								_sCoin[adres+1] = 100;
								Advance(0,10,100);

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
						_sCoin[((h1+1)*8)+h2] = 100;
						Advance(0,10,100);

						Advance ((10/(m_ucScoreMulti+1)),(100/(m_ucScoreMulti+1)),((3*(m_ucScoreMulti+1))+(m_ulBonusTime/10)));
	
						bFound = true;
					}
				}
			}
		}

	if (bFound)
		Mix_PlayChannel(-1, _pMClick,0);

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
	float	fTimeBar, fCurrent;
	int		iTimeX1, iTimeY1, iTimeX2, iTimeY2;
	int		iExpX1, iExpY1, iExpX2, iExpY2;	// wspolrzedne progress barow

	// rysujemy progress bar

	fTimeBar = (float)((ulTimer-m_ulTimerStart)/10)-m_ulBonusTime;

	// jezeli czasu jest za duzo (czyli ponizej 0) to ustawiamy na 0

	if (fTimeBar<0)
		fTimeBar = 0;

	// sprawdzamy czy powinnismy puszczac dzwiek odliczania do konca czasu

	if (fTimeBar > 700)
	{
		if (!_isTikTakSFX)
		{
			_iTikTakChannel = Mix_PlayChannel(-1, _pTikTakSFX, -1);
			_isTikTakSFX = true;
		}
	}
	else
	{
		if (_isTikTakSFX)
		{
			Mix_HaltChannel(_iTikTakChannel);
			_isTikTakSFX = false;
		}
	}


	// jezeli czasu jest za malo, progress bar jest ponizej 0, to dajemy game over

	if (fTimeBar>1000)
	{
		fTimeBar = 0.0f;
		m_bGameOver = true;
		m_ulTimerStart = 0;
		m_ulPrevTimer = 0;
	}

	// ustawianie wspolrzednych

	if (_pScreen->iSizeX()==1024 && _pScreen->iSizeY()==768)
	{
		iTimeX1 = 334; iTimeY1 = 632;
		iTimeX2 = 700; iTimeY2 = 664;

		iExpX1 = 334; iExpY1 = 680;
		iExpX2 = 700; iExpY2 = 712;
	}
	else if (_pScreen->iSizeX()==1366 && _pScreen->iSizeY()==768)
	{
		iTimeX1 = 507; iTimeY1 = 635;
		iTimeX2 = 507+364; iTimeY2 = 635+24;

		iExpX1 = 507; iExpY1 = 674;
		iExpX2 = 507+364; iExpY2 = 674+24;
	}
	else if (_pScreen->iSizeX() == 1920)
	{
		iTimeX1 = 711; iTimeY1 = 895;
		iTimeX2 = 711 + 510; iTimeY2 = 895 + 30;

		iExpX1 = 711; iExpY1 = 951;
		iExpX2 = 711 + 510; iExpY2 = 951 + 30;
	}
	else if (_pScreen->iSizeX() == 2560)
	{
		iTimeX1 = 948; iTimeY1 = 1192;
		iTimeX2 = 945 + 685; iTimeY2 = 1192 + 48;

		iExpX1 = 948; iExpY1 = 1265;
		iExpX2 = 948 + 685; iExpY2 = 1265 + 48;
	}


	// szare progress bary jako podklad

	m_pGreyBar->Position(iTimeX1,iTimeY1);
	m_pGreyBar->Resize(iTimeX1,iTimeY1,iTimeX2,iTimeY2);
	m_pGreyBar->Render();

	m_pGreyBar->Position(iExpX1,iExpY1);
	m_pGreyBar->Resize(iExpX1,iExpY1,iExpX2,iExpY2);
	m_pGreyBar->Render();

	// rysujemy pasek czasu

	fCurrent = 1000 - fTimeBar;
	fCurrent =  fCurrent*0.001f;		// skala 1-100

	m_pTimeBar->Position(iTimeX1,iTimeY1);
	m_pTimeBar->Resize(iTimeX1,iTimeY1,(int)iTimeX1+((iTimeX2-iTimeX1)*fCurrent),(int)iTimeY1+(iTimeY2-iTimeY1));
	m_pTimeBar->Render();

	// rysujemy pasek doswiadczenia

	fCurrent = (float)(m_ulBonusExp/10);

	if (fCurrent>1000)	// czy awansujemy ?
	{
		m_ulBonusExp = 0;
		
		if (m_ucScoreMulti!=9)	// level up
		{
			m_ucScoreMulti++;
			m_pPopup->Add(POPUP_FLASH_WHITE,(unsigned long)ulTimer);
			Mix_PlayChannel(-1, _pMLevelUp,0);
		}
		m_ulBonusTime +=1000;	// dodajemy graczowi czas przy awansie
	}

	fCurrent = fCurrent*0.001f;

	m_pExpBar->Position(iExpX1,iExpY1);
	m_pExpBar->Resize(iExpX1,iExpY1,(int)iExpX1+((iExpX2-iExpX1)*fCurrent),(int)iExpY1+(iExpY2-iExpY1));
	m_pExpBar->Render();

}

//=== rysuje pojedyncza klatke
//=== TODO: extra klocki dostepne proporcjonalnie do levelu

int eIngame::Render(unsigned long ulTimer, CMouse *pMouse)
{
	int 	iReturn,h1,h2,h3,h4;
	char 	c1,c2;
	char	cScore[8];	//	do konwersji na digits

	iReturn = 0;

	if (m_ulTimerStart == 0)		// czy to pierwsza renderowana klatka ?
	{
		m_ulTimerStart = ulTimer;
		m_lHintTime = ulTimer;

		if (pMouse->isLeft() || pMouse->isRight())	// nie przechwytujmy clicku z menu
			m_bMouseLock = true;


		m_pPopup->Add(POPUP_INGAME_START,ulTimer);

		if (_pScreen->iSizeX() == 1024)
		{
			_pFXManager->Add(FX_SMALL_LOOP, 850, 640, 1.0f, 0.75f, 0.5f, 1, ulTimer, 100000);	// particle pod latarni¹
			_pFXManager->Add(FX_SMALL_LOOP, 140, 640, 1.0f, 0.75f, 0.5f, 1, ulTimer, 100000);	// particle pod przyciskiem menu	
			_pFXManager->Add(FX_SMALL_LOOP, 885, 420, 0.0f, 0.0f, 0.0f, 1.0f, ulTimer, 100000);	// particle pod levelem
		}
		else if (_pScreen->iSizeX() == 1366)
		{
			_pFXManager->Add(FX_SMALL_LOOP, 1015, 640, 1.0f, 0.75f, 0.5f, 1, ulTimer, 100000);	// particle pod latarni¹
			_pFXManager->Add(FX_SMALL_LOOP, 315, 640, 1.0f, 0.75f, 0.5f, 1, ulTimer, 100000);	// particle pod przyciskiem menu	
			_pFXManager->Add(FX_SMALL_LOOP, 1080, 400, 0.0f, 0.0f, 0.0f, 1.0f, ulTimer, 100000);	// particle pod levelem
		}
		else if (_pScreen->iSizeX() == 1920)
		{
			_pFXManager->Add(FX_SMALL_LOOP, 1420, 888, 1.0f, 0.75f, 0.5f, 1, ulTimer, 100000);	// particle pod latarni¹
			_pFXManager->Add(FX_SMALL_LOOP, 440, 888, 1.0f, 0.75f, 0.5f, 1, ulTimer, 100000);	// particle pod przyciskiem menu	
			_pFXManager->Add(FX_SMALL_LOOP, 1500, 600, 0.0f, 0.0f, 0.0f, 1.0f, ulTimer, 100000);	// particle pod levelem
		}
		else if (_pScreen->iSizeX() == 2560)
		{
			_pFXManager->Add(FX_SMALL_LOOP, 1900, 1200, 1.0f, 0.75f, 0.5f, 1, ulTimer, 100000);	// particle pod latarni¹
			_pFXManager->Add(FX_SMALL_LOOP, 600, 1150, 1.0f, 0.75f, 0.5f, 1, ulTimer, 100000);	// particle pod przyciskiem menu	
			_pFXManager->Add(FX_SMALL_LOOP, 2050, 600, 0.0f, 0.0f, 0.0f, 1.0f, ulTimer, 100000);	// particle pod levelem
		}
	}

	m_pBackground->Render();
	m_pParticleManager->Render(ulTimer);

	m_pBoard->Render(ulTimer);

	DrawProgressBar(ulTimer);

	_pFXManager->Render(ulTimer, FX_LAYER_0);

	// sprawdzamy czy trzeba zmienic delte klockow

	if (!m_bGameOver)
		m_bFallLock = isMoveGems(ulTimer);

	if (m_bFallLock)			// zapamietaj czas ostatniego ruchu, jezeli brak ruchu przez 5 sekund to daj podpowiedz
		m_lHintTime = ulTimer;

	// sprawdzamy czy przycisk mozemy odblokowac

	if (m_bMouseLock && !pMouse->isLeft() && !pMouse->isRight())
		m_bMouseLock=false;

	// sprawdz czy sa trojki

	if (!m_bFallLock) 
		isMatch3(ulTimer);

	// jezeli cala dolna linia to same kamienie, to kasujemy t¹ linie

	if (m_cBoard[63] == m_cBoard[62] == m_cBoard[61] == m_cBoard[60] == m_cBoard[59] == m_cBoard[58] == m_cBoard[57] == m_cBoard[58] == GEM_ROCK)
		m_bBoard[63] = m_bBoard[62] = m_bBoard[61] = m_bBoard[60] = m_bBoard[59] = m_bBoard[58] = m_bBoard[57] = m_bBoard[58] = true;

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
						m_fBoardDeltaY[(h1 * 8) + h2] = -_ucGemSize;
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
				m_fBoardDeltaY[h1] = -_ucGemSize;
			}
		}
	}

	// narysuj przeskalowane poprzednie klocki

	h3 = _ucGemSize;
	h4 = h3/2;

	for (h1=0; h1<8; h1++)
	{
		for (h2=0; h2<8; h2++)
		{
			if (m_cScaleBoard[(h1*8)+h2]!=-1)
			{
				if ((ulTimer-m_ulScaleTimer[(h1*8)+h2])<100.0f)
				{
					float scale = (1+(((float)(ulTimer-m_ulScaleTimer[(h1*8)+h2])/100.0f)));
					m_pGem[m_cScaleBoard[(h1*8)+h2]]->Position((float)(((_pScreen->iSizeX()/2)-(m_pBoard->fSizeX()/2))+(h2*h3)+h4-(h4*scale)),(float)(_uiBoardOffsetY+(h3*h1)+h4-(h4*scale)));
					m_pGem[m_cScaleBoard[(h1*8)+h2]]->Scale(scale,scale);
					
					scale = scale - 1.0f;

					m_pGem[m_cScaleBoard[(h1*8)+h2]]->fAlfa(1.0f-(1.0f*scale));
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
				if (m_cBoard[(h1*8)+h2]<GEM_ROCK)
				{
					m_pGem[m_cBoard[(h1*8)+h2]]->Position((float)(((_pScreen->iSizeX()/2)-(m_pBoard->fSizeX()/2))+(h2*h3)+m_fBoardDeltaX[(h1*8)+h2]),(float)(_uiBoardOffsetY+(h3*h1)+m_fBoardDeltaY[(h1*8)+h2]));
					m_pGem[m_cBoard[(h1*8)+h2]]->Scale(1.0f,1.0f);
					m_pGem[m_cBoard[(h1*8)+h2]]->fAlfa(1.0f);
					m_pGem[m_cBoard[(h1*8)+h2]]->Render();
				}

				if (m_cBoard[(h1*8)+h2]==GEM_RAINBOW)
				{
					_pGemRainbow->Render(((ulTimer+(100*h1*h2))/10)%_pGemRainbow->iFrameCount(),(float)(((_pScreen->iSizeX()/2)-(m_pBoard->fSizeX()/2))+(h2*h3)+m_fBoardDeltaX[(h1*8)+h2]),(float)(_uiBoardOffsetY+(h3*h1)+m_fBoardDeltaY[(h1*8)+h2]));
				}

				if (m_cBoard[(h1*8)+h2]==GEM_DIAMOND)
				{
					_pGemDiamond->Render(((ulTimer+(100*h1*h2))/10)%_pGemDiamond->iFrameCount(),(float)(((_pScreen->iSizeX()/2)-(m_pBoard->fSizeX()/2))+(h2*h3)+m_fBoardDeltaX[(h1*8)+h2]),(float)(_uiBoardOffsetY+(h3*h1)+m_fBoardDeltaY[(h1*8)+h2]));
				}

				if (m_cBoard[(h1*8)+h2]==GEM_ROCK)
				{
					_pGemRock->Render(((ulTimer+(100*h1*h2))/10)%_pGemRock->iFrameCount(),(float)(((_pScreen->iSizeX()/2)-(m_pBoard->fSizeX()/2))+(h2*h3)+m_fBoardDeltaX[(h1*8)+h2]),(float)(_uiBoardOffsetY+(h3*h1)+m_fBoardDeltaY[(h1*8)+h2]));
				}

				if (m_cBoard[(h1*8)+h2]==GEM_BOMB)
				{
					_pGemBomb->Render(((ulTimer+(100*h1*h2))/10)%_pGemBomb->iFrameCount(),(float)(((_pScreen->iSizeX()/2)-(m_pBoard->fSizeX()/2))+(h2*h3)+m_fBoardDeltaX[(h1*8)+h2]),(float)(_uiBoardOffsetY+(h3*h1)+m_fBoardDeltaY[(h1*8)+h2]));
				}
			}

			// czy rysujemy monety nad klockami

			if (m_iCoin[(h1*8)+h2]!=-1)
			{
				if ((ulTimer - m_iCoin[(h1*8)+h2])>100.0f) // czy minal czas 255 ? 
				{
					m_iCoin[(h1*8)+h2]=-1;	// zerujemy 
				}
				else
				{
					float fAlfa = ((((float)(ulTimer-m_iCoin[(h1*8)+h2])/100.0f)));

					if (_sCoin[(h1*8)+h2]==100)
					_pScore100->Render(((_pScreen->iSizeX()/2)-(m_pBoard->fSizeX()/2))+(h2*h3),_uiBoardOffsetY+(h3*h1)- (ulTimer - m_iCoin[(h1*8)+h2]), 1.0f-(1.0f*fAlfa));

					if (_sCoin[(h1*8)+h2]==250)
					_pScore250->Render(((_pScreen->iSizeX()/2)-(m_pBoard->fSizeX()/2))+(h2*h3),_uiBoardOffsetY+(h3*h1)- (ulTimer - m_iCoin[(h1*8)+h2]), 1.0f-(1.0f*fAlfa));

					if (_sCoin[(h1*8)+h2]==500)
					_pScore500->Render(((_pScreen->iSizeX()/2)-(m_pBoard->fSizeX()/2))+(h2*h3),_uiBoardOffsetY+(h3*h1)- (ulTimer - m_iCoin[(h1*8)+h2]), 1.0f-(1.0f*fAlfa));

					if (_sCoin[(h1*8)+h2]==1000)
					_pScore1000->Render(((_pScreen->iSizeX()/2)-(m_pBoard->fSizeX()/2))+(h2*h3),_uiBoardOffsetY+(h3*h1)- (ulTimer - m_iCoin[(h1*8)+h2]), 1.0f-(1.0f*fAlfa));

				}
			}
		}
	}
	

	// jezeli przesuniecie jest wieksze od +/- 64 to zdejmujemy blokade myszy

	if (pMouse->fClickDeltaX()>_ucGemSize || pMouse->fClickDeltaY()>_ucGemSize || pMouse->fClickDeltaX()<-_ucGemSize || pMouse->fClickDeltaY()<-_ucGemSize)
	{
		m_bMouseLock = false;
		pMouse->fMouseXClick(pMouse->fMouseX());
		pMouse->fMouseYClick(pMouse->fMouseY());
	}

	// jezeli mysz znajduje sie nad tablica z kamykami to zamieniamy kursor na raczke

	if (pMouse->fMouseX()>((_pScreen->iSizeX() / 2) - (m_pBoard->fSizeX() / 2)) && pMouse->fMouseX()<((_pScreen->iSizeX() / 2) + (m_pBoard->fSizeX() / 2)) &&
		pMouse->fMouseY()>_uiBoardOffsetY && pMouse->fMouseY() < (m_pBoard->fSizeX() + _uiBoardOffsetY) && !m_bGameOver)
	{
		pMouse->iState(MOUSE_HAND);
	}
	else
	{
		pMouse->iState(MOUSE_ARROW);
	}

	// czy kliknieto

	h3 = _ucGemSize;

	if (pMouse->fMouseX()>((_pScreen->iSizeX()/2)-(m_pBoard->fSizeX()/2)) && pMouse->fMouseX()<((_pScreen->iSizeX()/2)+(m_pBoard->fSizeX()/2)) && 
		pMouse->fMouseY()>_uiBoardOffsetY && pMouse->fMouseY()<(m_pBoard->fSizeX()+_uiBoardOffsetY) && pMouse->isLeft() && !m_bMouseLock && !m_bGameOver && !m_bFallLock)
	{
		h1 = (int)((pMouse->fMouseX()-((_pScreen->iSizeX()/2)-(m_pBoard->fSizeX()/2)))/h3);	// X na tablicy
		h2 = (int)((pMouse->fMouseY()-_uiBoardOffsetY)/h3);	// Y na tablicy

		if (m_cClickedA==-1)
		{
			m_cClickedA=(h2*8)+h1;
			m_iClickedAx = ((_pScreen->iSizeX()/2)-(m_pBoard->fSizeX()/2)) +(h1*h3);
			m_iClickedAy = _uiBoardOffsetY + (h2*h3);
		}
		else if (m_cClickedB==-1)
		{
			if (m_cClickedA!=(h2*8)+h1)			// czy to nie ten sam co #1 ? 
			{
				if ( (((m_cClickedA-1 == (h2*8)+h1) || (m_cClickedA+1 == (h2*8)+h1)) && m_iClickedAy == _uiBoardOffsetY + (h2*h3)) || (m_cClickedA+8 == (h2*8)+h1) || (m_cClickedA-8 == (h2*8)+h1) ) // czy to klik obok ?
				{					
					m_cClickedB=(h2*8)+h1;			// numer kliknietego klocka B na tablicy
					m_iClickedBx = ((_pScreen->iSizeX()/2)-(m_pBoard->fSizeX()/2)) +(h1*h3);	// wspolrzedne X klocka B
					m_iClickedBy = _uiBoardOffsetY + (h2*h3);	// wspolrzedne Y klocka B
				}
				else	// to nie jest click obok wiêc to bêdzie teraz nasz klocek #1
				{
					m_cClickedA=(h2*8)+h1;
					m_iClickedAx = ((_pScreen->iSizeX()/2)-(m_pBoard->fSizeX()/2)) +(h1*h3);
					m_iClickedAy = _uiBoardOffsetY + (h2*h3);
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
				Mix_PlayChannel(-1, _pMBomb,0);

				if (m_cBoard[m_cClickedA] == GEM_BOMB)
				{
					_pFXManager->Add(FX_BIG_EXPLOSION, m_iClickedAx + (h3 / 2), m_iClickedAy + (h3 / 2), (25+ ((ulTimer * m_iClickedAx) % 75)) * 0.01f, (25 + ((ulTimer * m_iClickedAy) % 75)) * 0.01f, (25 + ((ulTimer * m_ulScore) % 75)) * 0.01f, 1, ulTimer, 1000, FX_LAYER_5);	// particle wybuch bomby
				}
				else
				{
					_pFXManager->Add(FX_BIG_EXPLOSION, m_iClickedBx + (h3 / 2), m_iClickedBy + (h3 / 2), (25 + ((ulTimer * m_iClickedBx) % 75)) * 0.01f, (25 + ((ulTimer * m_iClickedBy) % 75)) * 0.01f, (25 + ((ulTimer * m_ulScore) % 75)) * 0.01f, 1, ulTimer, 1000, FX_LAYER_5);	// particle wybuch bomby
				}

				m_cBoard[(h2*8)+h1] = -1;
				m_bBoard[(h2*8)+h1] = true;
				m_iCoin[(h2*8)+h1] = ulTimer;
				_sCoin[(h2*8)+h1] = 500;
				Advance(0,50,500);
				
				if (h1>0)	// po lewej
				{
					m_cBoard[(h2*8)+h1-1] = -1;
					m_bBoard[(h2*8)+h1-1] = true;
					m_iCoin[(h2*8)+h1-1] = ulTimer;
					_sCoin[(h2*8)+h1-1] = 100;
				}					

				if (h1<7)	// po prawej
				{
					m_cBoard[(h2*8)+h1+1] = -1;
					m_bBoard[(h2*8)+h1+1] = true;
					m_iCoin[(h2*8)+h1+1] = ulTimer;
					_sCoin[(h2*8)+h1+1] = 100;
				}			

				if (h2>0)	// na gorze
				{
					m_cBoard[((h2-1)*8)+h1] = -1;
					m_bBoard[((h2-1)*8)+h1] = true;
					m_iCoin[((h2-1)*8)+h1] = ulTimer;			
					_sCoin[((h2-1)*8)+h1] = 100;
				}

				if (h2<7) // na dole
				{
					m_cBoard[((h2+1)*8)+h1] = -1;
					m_bBoard[((h2+1)*8)+h1] = true;
					m_iCoin[((h2+1)*8)+h1] = ulTimer;
					_sCoin[((h2+1)*8)+h1] = 100;			
				}

				if (h1>0 && h2>0)	// na gorze po lewej
				{
					m_cBoard[((h2-1)*8)+h1-1] = -1;
					m_bBoard[((h2-1)*8)+h1-1] = true;
					m_iCoin[((h2-1)*8)+h1-1] = ulTimer;					
					_sCoin[((h2-1)*8)+h1-1] = 100;					
				}

				if (h2>0 && h1<7)	// na gorze po prawej
				{
					m_cBoard[((h2-1)*8)+h1+1] = -1;
					m_bBoard[((h2-1)*8)+h1+1] = true;
					m_iCoin[((h2-1)*8)+h1+1] = ulTimer;
					_sCoin[((h2-1)*8)+h1+1] = 100;					
				}

				if (h2<7 && h1>0)	// na dole po lewej
				{
					m_cBoard[((h2+1)*8)+h1-1] = -1;
					m_bBoard[((h2+1)*8)+h1-1] = true;
					m_iCoin[((h2+1)*8)+h1-1] = ulTimer;
					_sCoin[((h2+1)*8)+h1-1] = 100;
				}

				if (h1<7 && h2<7)	// na dole po prawej
				{
					m_cBoard[((h2+1)*8)+h1+1] = -1;
					m_bBoard[((h2+1)*8)+h1+1] = true;
					m_iCoin[((h2+1)*8)+h1+1] = ulTimer;
					_sCoin[((h2+1)*8)+h1+1] = 100;
				}			

			m_cClickedA = -1;
			m_cClickedB = -1;
			m_iClickedAx = m_iClickedAy = m_iClickedBx = m_iClickedBy = -1; 						
		}

		// jezeli ktorys z kamykow to diament to kasujemy linie w pionie i w poziomie

		if (m_cBoard[m_cClickedA]==GEM_DIAMOND || m_cBoard[m_cClickedB]==GEM_DIAMOND)
		{
			Mix_PlayChannel(-1, _pMDiamond,0);

			// dodajemy monete tylko tam gdzie jest diament

			if (m_cBoard[m_cClickedA]==GEM_DIAMOND)
			{
				m_iCoin[m_cClickedA] = ulTimer;
				_sCoin[m_cClickedA] = 500;
				Advance(0,50,500);
			}
			else
			{
				m_iCoin[m_cClickedB] = ulTimer;
				_sCoin[m_cClickedB] = 100;
				Advance(0,50,500);
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

				_pFXManager->Add(FX_DIAMOND_EXPLOSION, ((_pScreen->iSizeX() / 2) - (m_pBoard->fSizeX() / 2)) + (h1*h3) + (h3 / 2), _uiBoardOffsetY + (i*h3) + (h3/ 2), 1, 1, 1, 1, ulTimer, 2000, FX_LAYER_5);
				_pFXManager->Add(FX_DIAMOND_EXPLOSION, ((_pScreen->iSizeX() / 2) - (m_pBoard->fSizeX() / 2)) + (i*h3) + (h3 / 2), _uiBoardOffsetY + (h2*h3) + (h3/ 2), 1, 1, 1, 1, ulTimer, 2000, FX_LAYER_5);

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
		m_bMouseLock = true;
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
			Mix_PlayChannel(-1, _pMRainbow,0);

			if (m_cBoard[m_cClickedA] == GEM_RAINBOW)
			{
				h2 = m_cBoard[m_cClickedB]; // zapamietaj do kasowania

				for (h1 = 0; h1 < 8; h1++)
				{
					for (h3 = 0; h3 < 8; h3++)
					{
						if (m_cBoard[(h1*8)+h3] == h2)
						{
							m_cBoard[(h1 * 8) + h3] = -1;
							m_bBoard[(h1 * 8) + h3] = true;
							m_iCoin[(h1 * 8) + h3] = ulTimer;	// dodajemy monete
							_sCoin[(h1 * 8) + h3] = 100;
							Advance(0, 10, 100);

							_pFXManager->Add(FX_RAINBOW_EXPLOSION, ((_pScreen->iSizeX() / 2) - (m_pBoard->fSizeX() / 2)) + (h3*_ucGemSize) + _ucGemSizeHalf, _uiBoardOffsetY + (h1*_ucGemSize) + _ucGemSizeHalf, 1, 1, 1, 1, ulTimer, 1000, FX_LAYER_5);	// particle wybuch bomby
						}
					}
				}
				m_cBoard[m_cClickedA] = -1;
				m_bBoard[m_cClickedA] = true;
				m_iCoin[m_cClickedA] = ulTimer;
				_sCoin[m_cClickedA] = 1000;
				Advance(0,100,1000);
			}
			else
			{
				h2 = m_cBoard[m_cClickedA];

				for (h1 = 0; h1 < 8; h1++)
				{
					for (h3 = 0; h3 < 8; h3++)
					{
						if (m_cBoard[(h1 * 8) + h3] == h2)
						{
							if (m_cBoard[(h1 * 8) + h3] == h2)
							{
								m_cBoard[(h1 * 8) + h3] = -1;
								m_bBoard[(h1 * 8) + h3] = true;
								m_iCoin[(h1 * 8) + h3] = ulTimer;
								_sCoin[(h1 * 8) + h3] = 100;
								Advance(0, 10, 100);

								_pFXManager->Add(FX_RAINBOW_EXPLOSION, ((_pScreen->iSizeX() / 2) - (m_pBoard->fSizeX() / 2)) + (h3*_ucGemSize) + _ucGemSizeHalf, _uiBoardOffsetY + (h1*_ucGemSize) + _ucGemSizeHalf, 1, 1, 1, 1, ulTimer, 1000, FX_LAYER_5);	// particle wybuch bomby
							}
						}
					}
				}

				m_cBoard[m_cClickedB] = -1;
				m_bBoard[m_cClickedB] = true;
				m_iCoin[m_cClickedB] = ulTimer;
				_sCoin[m_cClickedB] = 1000;
				Advance(0,100,1000);
			}

			m_cClickedA = -1;
			m_cClickedB = -1;
			m_iClickedAx = m_iClickedAy = m_iClickedBx = m_iClickedBy = -1; 
			m_bMouseLock = true;
		}
	}

	if (m_cClickedA!=-1 && m_cClickedB!=-1)	// swap
	{
		m_bHint = false;		// znikamy pomoc
		
		if (_iHintID != -1)
		{
			_pFXManager->Remove(_iHintID);
			_iHintID = -1;
		}
		
		m_lHintTime = ulTimer;

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
					m_fBoardDeltaX[m_cClickedA] = -_ucGemSize; // -64.0f;
					m_fBoardDeltaX[m_cClickedB] = _ucGemSize; // 64.0f;
				}
				else
				{
					m_fBoardDeltaX[m_cClickedA] = _ucGemSize;// 64.0f;
					m_fBoardDeltaX[m_cClickedB] = -_ucGemSize;// 64.0f;
				}
			}
			else	// klocki sa obok siebie w pionie			
			{
				if (m_cClickedA>m_cClickedB)
				{
					m_fBoardDeltaY[m_cClickedA] = -_ucGemSize;// 64.0f;
					m_fBoardDeltaY[m_cClickedB] = _ucGemSize;// 64.0f;
				}
				else
				{
					m_fBoardDeltaY[m_cClickedA] = _ucGemSize;// 64.0f;
					m_fBoardDeltaY[m_cClickedB] = -_ucGemSize;// 64.0f;
				}
			}
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
					m_iHintX = ((_pScreen->iSizeX()/2)-(m_pBoard->fSizeX()/2)) + (h2*_ucGemSize);
					m_iHintY = _uiBoardOffsetY + (h1*_ucGemSize);
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
					m_iHintX = ((_pScreen->iSizeX()/2)-(m_pBoard->fSizeX()/2)) + (h2*_ucGemSize);
					m_iHintY = _uiBoardOffsetY + (h1*_ucGemSize);
				}

				c1 = m_cBoard[(h1*8)+h2];
				m_cBoard[(h1*8)+h2] = m_cBoard[((h1+1)*8)+h2];
				m_cBoard[((h1+1)*8)+h2] = c1;
			}
		}
	}

	if (c2)	// sprawdzamy czy mozemy dac podpowiedz
	{
		if ( ((ulTimer - m_lHintTime)>1000) || m_bHint)
		{
			m_bHint = true;

			if (_iHintID==-1)
				_iHintID = _pFXManager->Add(FX_HINT, (float)m_iHintX + _ucGemSizeHalf, (float)m_iHintY + _ucGemSizeHalf, 1.0f, 1.0f, 1.0f, 1, ulTimer, 1000000,FX_LAYER_5);	// particle wybuch bomby
		}
	}
	else
	{
		if (!m_bFallLock) // nie ma ruchow mozliwych
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
			{
				int i = ulTimer % 7;
				m_cBoard[(i<<3)+i] = GEM_BOMB;

				_pFXManager->Add(FX_SHOW_BOMB, (_pScreen->iSizeX() / 2) - (m_pBoard->fSizeX()/2 ) + (i*_ucGemSize) + _ucGemSizeHalf, _uiBoardOffsetY + (i*_ucGemSize) + _ucGemSizeHalf, 1, 1, 1, 1, ulTimer, 2000, FX_LAYER_5);
				Mix_PlayChannel(-1, _pMRainbow,0);
				bSpecial = false;
			}
		}
	}

	// rysujemy licznik punktow

	h3=0;

	// odstep po lewej

	if (_pScreen->iSizeX() == 1024 )
	{
		h3 = 16;
		h4 = 32;	// odstep pomiedzy cyferkami
		h2 = _pScreen->iSizeY() / 2;
	}
	else if (_pScreen->iSizeX() == 1366)
	{
		h3 = 64;
		h4 = 32;
		h2 = _pScreen->iSizeY() / 2;
	}
	else if (_pScreen->iSizeX() == 1920)
	{
		h3 = 64;
		h4 = 64;
		h2 = _pScreen->iSizeY() / 2 - 100;
	}
	else if (_pScreen->iSizeX() == 2560)
	{
		h3 = 128;
		h4 = 64;
		h2 = _pScreen->iSizeY() / 2 - 200;
	}
	

	sprintf(cScore,"%.7d",m_ulScore);

	for (int i=0; i<7; i++)
	{
		m_pNumber[cToDigit(cScore[i])]->Position(h3+(i*h4),h2);
		m_pNumber[cToDigit(cScore[i])]->Render();
	}

	// dodatkowe particle - hint

	_pFXManager->Render(ulTimer, FX_LAYER_5);

	// rysujemy game over

	if (m_bGameOver)
	{
		if (m_lInGameOver==0)
			m_lInGameOver=ulTimer;

		m_pGameOver->Render();

		if (ulTimer-m_lInGameOver>500)	// wychodzimy z gry
			iReturn = -1;		

		if (!_isGameOverSFX)			// pierwszy render game over -> odtworz dzwiek
		{
			_isGameOverSFX = true;
			Mix_HaltMusic();
			Mix_PlayChannel(-1, _pGameOverSFX, 0);
		}

	}

	// przyciski menu i hint, score multi info, jezeli nie ma gameover

	if (!m_bGameOver)
	{
		if (m_pButtonMenu->Render(pMouse)==ON_LEFT)
			iReturn = -1; 

		if (m_pButtonHint->Render(pMouse)==ON_LEFT && !m_bMouseLock)
		{
			if (!m_bHint)
			{
				m_bHint = true;
				m_ulScore = (unsigned long)(m_ulScore * 0.9);	// zabieramy 10% punktow
				m_bMouseLock = true;

				if (_iHintID != -1)
					_pFXManager->Remove(_iHintID);

			}
		}	

		// renderowanie mnoznika dla punktow

		if (_pScreen->isSDS())
		{
			m_pScoreMulti[m_ucScoreMulti]->Position(850, _pScreen->iSizeY() / 2);
		}
		else if (_pScreen->iSizeX() == 1366)
		{
			m_pScoreMulti[m_ucScoreMulti]->Position(1050, _pScreen->iSizeY() / 2);
		}
		else if (_pScreen->iSizeX() == 1920)
		{
			m_pScoreMulti[m_ucScoreMulti]->Position(1450, _pScreen->iSizeY() / 2);
		}
		else if (_pScreen->iSizeX() == 2560)
		{
			m_pScoreMulti[m_ucScoreMulti]->Position(2000, _pScreen->iSizeY() / 2 - 200);
		}

		
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
				Mix_PlayChannel(-1,_pMSuper,0);
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
