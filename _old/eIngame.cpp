#include "eIngame.h"

// class constructor

eIngame::eIngame()
{
	_pBlack = NULL;
	_pBackground = NULL;
	_pBoard = NULL;

	for (int i=0; i<GEMS_COUNT; i++)
		_pGem[i]=NULL;

	for (int i=0; i<10; i++)
		_pNumber[i]=NULL;

	_pTimeBar = NULL; 
	_pExpBar = NULL;
	_pGreyBar = NULL;

	_ulTimerStart = 0;	// start
	_ulPrevTimer = 0;

	_isActive = false;

	_cClickedA = -1;	// none clicked
	_cClickedB = -1;
	_iClickedAx = _iClickedAy = _iClickedBx = _iClickedBy = -1; 

	_ulBonusTime = 0;	// bonus time
	_ulBonusExp = 0;

	_bMouseLock = false;
	_bFallLock = false;

	_pGameOver = NULL;
	_bGameOver = false;
	_lInGameOver = 0;

	_pParticleManager = NULL;

	_pHint = NULL;
	_lHintTime = 0;

	_iHintX = 0;
	_iHintY = 0;

	_ulScore = 0;

	_pButtonMenu = NULL;
	_pButtonHint = NULL;

	_ucScoreMulti = 0;

	_fM3Delta = 8.0f;

	for (int i=0; i<=9; i++)
		_pScoreMulti[i] = NULL;

	_bHint = false;

	_pPopup = NULL;

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

void eIngame::Open(CScreen *pScreen)
{	
	char cBuffer[16];

	_pScreen = pScreen;

	_ulScore = 0;			
	_ucScoreMulti = 0;		

	_ulTimer1000 = 0;		
	_ulScore1000 = 0;		

	_pParticleManager = new CParticle2DManager((char*)"data/particle.png", 100, 
                                               -100,-100,1024,768,
                                               0.01f,0.01f,0.3f,0.3f,
                                               0.0f, 1.0f,5.0f,
                                               0.5f, -5.0f,5.0f,
                                               1000,10000,pScreen);

	_pTimeBar = new CSprite("data/bar_time.png");
	_pTimeBar->Resize(0,0,_pScreen->toX(64),_pScreen->toY(64));

	_pExpBar =  new CSprite("data/bar_exp.png");
	_pExpBar->Resize(0,0,_pScreen->toX(64),_pScreen->toY(64));
	
	_pGreyBar = new CSprite("data/bar_grey.png");
	_pGreyBar->Resize(0,0,_pScreen->toX(64),_pScreen->toY(64));

	_pBoard = new CSprite("data/board.png");
	_pBoard->Resize(pScreen->toX(BOARD_X1),pScreen->toY(BOARD_Y1),pScreen->toX(BOARD_X2),pScreen->toY(BOARD_Y2));

	_pGameOver = new CSprite("data/game_over.jpg");
	_pGameOver->Resize(0,0,pScreen->toX(DEFAULT_SCREENX), pScreen->toY(DEFAULT_SCREENY));

	_pHint = new CSprite("data/hint.png");
	_pHint->Resize(0,0,pScreen->toX(ITEM_SIZE),pScreen->toY(ITEM_SIZE));
	_lHintTime = 0;

	_pBlack = new CSprite("data/fc1.png");

	// icons x1,x2 itd. 

	for (int i=0; i<=9; i++)
	{
		sprintf(cBuffer,"data/x%d.png",i+1);
		_pScoreMulti[i] = new CSprite(cBuffer);
	}

	_pBackground = new CSprite("data/Background.jpg");
	_pBackground->Resize(0,0,pScreen->toX(DEFAULT_SCREENX), pScreen->toY(DEFAULT_SCREENY));
	
	// gems

	for (int i=0; i<=GEMS_COUNT-1; i++)
	{
		sprintf(cBuffer,"data/gem%d.png",i+1);
		_pGem[i] = new CSprite(cBuffer);
	}

	// buttons

	_pButtonHint = new CButton("data/button_hint.png","data/button_hint.png","data/button_hint.png");
	_pButtonHint->SetPosition(320,400);
	_pButtonHint->SetHotCoords(320,400,320+64,400+64);

	_pButtonMenu = new CButton("data/button_menu.png","data/button_menu.png","data/button_menu.png");
	_pButtonMenu->SetPosition(160,400);
	_pButtonMenu->SetHotCoords(160,400,160+64,400+64);

	// numer

	for (int i=0; i<=9; i++)
	{
		sprintf(cBuffer,"data/%d.png",i);
		_pNumber[i] = new CSprite(cBuffer);
	}

	for (int i=0; i<64; i++)
	{
		_cBoard[i]= rand()%7;
		_bBoard[i]= false;
		_fBoardDeltaX[i] = 0.0f;
		_fBoardDeltaY[i] = 0.0f;

		_cScaleBoard[i]=-1;
		_fScaleBoard[i]= 1.0f;
		_ulScaleTimer[i]= 0;
	}

	// popup manager

	_pPopup = new CPopup();
	_pPopup->Open(pScreen);

	// counters and timers

	_ulTimerStart = 0;	
	_ulPrevTimer = 0;

	_cClickedA = -1;	
	_cClickedB = -1;
	_iClickedAx = _iClickedAy = _iClickedBx = _iClickedBy = -1; 

	_ulBonusTime = 0;	
	_ulBonusExp = 0;

	_bMouseLock = false;
	_bFallLock = false;

	_bGameOver = false;
	_lInGameOver = 0;

	_iHintX = 0;
	_iHintY = 0;

	_bHint = false;

	_cReplacedA = _cReplacedB = -1;

	_idA_lastDeltaX = _idA_lastDeltaY = 0.0f;
	_idB_lastDeltaX = _idB_lastDeltaY = 0.0f;

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
	SafeDelete(_pBoard);
	SafeDelete(_pBlack);
	SafeDelete(_pBackground);
	
	SafeDelete(_pTimeBar);
	SafeDelete(_pExpBar);
	SafeDelete(_pGreyBar);

	SafeDelete(_pGameOver);

	for (int i=0; i<=GEMS_COUNT; i++)
		SafeDelete(_pGem[i]);

	for (int i=0; i<10; i++)
		SafeDelete(_pNumber[i]);

	SafeDelete(_pParticleManager);
	SafeDelete(_pButtonMenu);
	SafeDelete(_pButtonHint);

	for (int i=0; i<=9; i++)
		SafeDelete(_pScoreMulti[i]);

	SafeDelete(_pPopup);
	SafeDelete(_pHint);
	
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
	_ulBonusTime += ulBonusTime;
	_ulBonusExp += ulBonusExp;
	_ulScore += ulScore;
}

// update board when correct combination found

bool eIngame::isMatch3(unsigned long ulTimer)
{
	bool bFound;
	int h1,h2,adres;

	bFound = false;

	// looking for L - 3 gems in H/V - create a diamond

	// +---	
	// |
	// |

	for (h1=0; h1<=5; h1++)
	{
		for (h2=0; h2<=5; h2++)
		{
			adres = (h1*8)+h2;

			if (_cBoard[adres] == _cBoard[adres+1] && _cBoard[adres] == _cBoard[adres+2] && 
				_cBoard[adres] == _cBoard[((h1+1)*8)+h2] && _cBoard[adres] == _cBoard[((h1+1)*8)+h2] &&
				_fBoardDeltaX[adres] == 0 && _fBoardDeltaY[adres] == 0 &&
				_fBoardDeltaX[adres+1] == 0 && _fBoardDeltaY[adres+1] == 0 &&
				_fBoardDeltaX[adres+2] == 0 && _fBoardDeltaY[adres+2] == 0 &&
				_fBoardDeltaX[((h1+1)*8)+h2] == 0 && _fBoardDeltaY[((h1+1)*8)+h2] == 0 &&
				_fBoardDeltaX[((h1+2)*8)+h2] == 0 && _fBoardDeltaY[((h1+2)*8)+h2] == 0 &&
				!_bBoard[((h1+1)*8)+h2+1] &&		// check for empty spaces
				!_bBoard[((h1+1)*8)+h2+2] &&
				!_bBoard[adres] &&				
				_cBoard[adres]<GEM_ROCK)
			{

				_cBoard[adres] = GEM_DIAMOND;
				Mix_PlayChannel(-1,_pMDiamond,0);

				_cScaleBoard[adres] = _cBoard[adres];
				_cScaleBoard[adres+1] = _cBoard[adres+1];
				_cScaleBoard[adres+2] = _cBoard[adres+2];						
				_cScaleBoard[((h1+1)*8)+h2] = _cBoard[((h1+1)*8)+h2];
				_cScaleBoard[((h1+2)*8)+h2] = _cBoard[((h1+2)*8)+h2];

				_ulScaleTimer[adres] = ulTimer;
				_ulScaleTimer[adres+1] = ulTimer;
				_ulScaleTimer[adres+2] = ulTimer;
				_ulScaleTimer[((h1+1)*8)+h2] = ulTimer;
				_ulScaleTimer[((h1+2)*8)+h2] = ulTimer;

				_cBoard[adres+1] = -1;
				_bBoard[adres+1] = true;

				_cBoard[adres+2] = -1;
				_bBoard[adres+2] = true;

				_cBoard[((h1+1)*8)+h2] = -1;
				_bBoard[((h1+1)*8)+h2] = true;

				_cBoard[((h1+2)*8)+h2] = -1;
				_bBoard[((h1+2)*8)+h2] = true;

				// add time, exp, points

				Advance ((10/(_ucScoreMulti+1))*3,(100/(_ucScoreMulti+1))*3,((3*(_ucScoreMulti+1))+(_ulBonusTime/10))*3);

				bFound = true;
			}
		}
	}

	// ---+	
	//    |
	//	  |

	for (h1=0; h1<=5; h1++)
	{
		for (h2=0; h2<=5; h2++)
		{
			adres = (h1*8)+h2;

			if (_cBoard[adres] == _cBoard[adres+1] && _cBoard[adres] == _cBoard[adres+2] && 
				_cBoard[adres] == _cBoard[((h1+1)*8)+h2+2] && _cBoard[adres] == _cBoard[((h1+2)*8)+h2+2] &&
				_fBoardDeltaX[adres] == 0 && _fBoardDeltaY[adres] == 0 &&
				_fBoardDeltaX[adres+1] == 0 && _fBoardDeltaY[adres+1] == 0 &&
				_fBoardDeltaX[adres+2] == 0 && _fBoardDeltaY[adres+2] == 0 &&
				_fBoardDeltaX[((h1+1)*8)+h2+2] == 0 && _fBoardDeltaY[((h1+1)*8)+h2+2] == 0 &&
				_fBoardDeltaX[((h1+2)*8)+h2+2] == 0 && _fBoardDeltaY[((h1+2)*8)+h2+2] == 0 &&
				!_bBoard[((h1+1)*8)+h2-1] &&		
				!_bBoard[((h1+1)*8)+h2-2] &&
				!_bBoard[adres] &&				
				_cBoard[adres]<GEM_ROCK)
			{

				_cBoard[adres+2] = GEM_DIAMOND;
				Mix_PlayChannel(-1,_pMDiamond,0);

				_cScaleBoard[adres] = _cBoard[adres];
				_cScaleBoard[adres+1] = _cBoard[adres+1];
				_cScaleBoard[adres+2] = _cBoard[adres+2];						
				_cScaleBoard[((h1+1)*8)+h2+2] = _cBoard[((h1+1)*8)+h2+2];
				_cScaleBoard[((h1+2)*8)+h2+2] = _cBoard[((h1+2)*8)+h2+2];

				_ulScaleTimer[adres] = ulTimer;
				_ulScaleTimer[adres+1] = ulTimer;
				_ulScaleTimer[adres+2] = ulTimer;
				_ulScaleTimer[((h1+1)*8)+h2+2] = ulTimer;
				_ulScaleTimer[((h1+2)*8)+h2+2] = ulTimer;

				_cBoard[adres] = -1;
				_bBoard[adres] = true;

				_cBoard[adres+1] = -1;
				_bBoard[adres+1] = true;

				_cBoard[((h1+1)*8)+h2+2] = -1;
				_bBoard[((h1+1)*8)+h2+2] = true;

				_cBoard[((h1+2)*8)+h2+2] = -1;
				_bBoard[((h1+2)*8)+h2+2] = true;

				Advance ((10/(_ucScoreMulti+1))*3,(100/(_ucScoreMulti+1))*3,((3*(_ucScoreMulti+1))+(_ulBonusTime/10))*3);
						
				bFound = true;
			}
		}
	}

	// |
	// |	
	// +--- 

	for (h1=0; h1<=5; h1++)
	{
		for (h2=0; h2<=5; h2++)
		{
			adres = (h1*8)+h2;

			if (_cBoard[adres] == _cBoard[((h1+1)*8)+h2] && _cBoard[adres] == _cBoard[((h1+2)*8)+h2] && 
				_cBoard[adres] == _cBoard[((h1+2)*8)+h2+1] && _cBoard[adres] == _cBoard[((h1+2)*8)+h2+2] &&
				_fBoardDeltaX[adres] == 0 && _fBoardDeltaY[adres] == 0 &&
				_fBoardDeltaX[((h1+1)*8)+h2] == 0 && _fBoardDeltaY[((h1+1)*8)+h2] == 0 &&
				_fBoardDeltaX[((h1+2)*8)+h2] == 0 && _fBoardDeltaY[((h1+2)*8)+h2] == 0 &&
				_fBoardDeltaX[((h1+2)*8)+h2+1] == 0 && _fBoardDeltaY[((h1+2)*8)+h2+1] == 0 &&
				_fBoardDeltaX[((h1+2)*8)+h2+2] == 0 && _fBoardDeltaY[((h1+2)*8)+h2+2] == 0 &&
				!_bBoard[adres] &&				
				_cBoard[adres]<GEM_ROCK)
			{

				_cBoard[((h1+2)*8)+h2] = GEM_DIAMOND;
				Mix_PlayChannel(-1,_pMDiamond,0);

				_cScaleBoard[((h1+2)*8)+h2] = _cBoard[((h1+2)*8)+h2];
				_cScaleBoard[adres] = _cBoard[adres];
				_cScaleBoard[((h1+1)*8)+h2] = _cBoard[((h1+1)*8)+h2];						
				_cScaleBoard[((h1+2)*8)+h2+1] = _cBoard[((h1+2)*8)+h2+1];
				_cScaleBoard[((h1+2)*8)+h2+2] = _cBoard[((h1+2)*8)+h2+2];

				_ulScaleTimer[((h1+2)*8)+h2] = ulTimer;
				_ulScaleTimer[adres] = ulTimer;
				_ulScaleTimer[((h1+1)*8)+h2] = ulTimer;
				_ulScaleTimer[((h1+2)*8)+h2+1] = ulTimer;
				_ulScaleTimer[((h1+2)*8)+h2+2] = ulTimer;

				_cBoard[adres] = -1;
				_bBoard[adres] = true;

				_cBoard[((h1+1)*8)+h2] = -1;
				_bBoard[((h1+1)*8)+h2] = true;

				_cBoard[((h1+2)*8)+h2+1] = -1;
				_bBoard[((h1+2)*8)+h2+1] = true;

				_cBoard[((h1+2)*8)+h2+2] = -1;
				_bBoard[((h1+2)*8)+h2+2] = true;

				Advance ((10/(_ucScoreMulti+1))*3,(100/(_ucScoreMulti+1))*3,((3*(_ucScoreMulti+1))+(_ulBonusTime/10))*3);
						
				bFound = true;
			}
		}
	}

	//    |
	//    |	
	// ---+

	for (h1=2; h1<=7; h1++)
	{
		for (h2=0; h2<=5; h2++)
		{
			adres = (h1*8)+h2;

			if (_cBoard[adres] == _cBoard[adres+1] && _cBoard[adres] == _cBoard[adres+2] && 
				_cBoard[adres] == _cBoard[((h1-1)*8)+h2+2] && _cBoard[adres] == _cBoard[((h1-2)*8)+h2+2] &&
				_fBoardDeltaX[adres] == 0 && _fBoardDeltaY[adres] == 0 &&
				_fBoardDeltaX[adres+1] == 0 && _fBoardDeltaY[adres+1] == 0 &&
				_fBoardDeltaX[adres+2] == 0 && _fBoardDeltaY[adres+2] == 0 &&
				_fBoardDeltaX[((h1-1)*8)+h2+2] == 0 && _fBoardDeltaY[((h1-1)*8)+h2+2] == 0 &&
				_fBoardDeltaX[((h1-2)*8)+h2+2] == 0 && _fBoardDeltaY[((h1-2)*8)+h2+2] == 0 &&
				!_bBoard[adres] &&				
				_cBoard[adres]<GEM_ROCK)
			{

				_cBoard[adres+2] = GEM_DIAMOND;
				Mix_PlayChannel(-1,_pMDiamond,0);

				_cScaleBoard[adres+2] = _cBoard[adres+2];
				_cScaleBoard[adres] = _cBoard[adres];
				_cScaleBoard[adres+1] = _cBoard[adres+1];						
				_cScaleBoard[((h1-1)*8)+h2+2] = _cBoard[((h1-1)*8)+h2+2];
				_cScaleBoard[((h1-2)*8)+h2+2] = _cBoard[((h1-2)*8)+h2+2];

				_ulScaleTimer[adres+2] = ulTimer;
				_ulScaleTimer[adres] = ulTimer;
				_ulScaleTimer[adres+1] = ulTimer;
				_ulScaleTimer[((h1-1)*8)+h2+2] = ulTimer;
				_ulScaleTimer[((h1-2)*8)+h2+2] = ulTimer;

				_cBoard[adres+1] = -1;
				_bBoard[adres+1] = true;

				_cBoard[adres] = -1;
				_bBoard[adres] = true;

				_cBoard[((h1-1)*8)+h2+2] = -1;
				_bBoard[((h1-1)*8)+h2+2] = true;

				_cBoard[((h1-2)*8)+h2+2] = -1;
				_bBoard[((h1-2)*8)+h2+2] = true;

				Advance ((10/(_ucScoreMulti+1))*3,(100/(_ucScoreMulti+1))*3,((3*(_ucScoreMulti+1))+(_ulBonusTime/10))*3);
						
				bFound = true;
			}
		}
	}

	// check for 5 gems in same line

		for (h1=0; h1<=7; h1++)	// horizontal check
		{
			for (h2=0; h2<=3; h2++)
			{

				adres = (h1*8)+h2;

				if (_cBoard[adres] == _cBoard[adres+1] && _cBoard[adres] == _cBoard[adres+2] && _cBoard[adres] == _cBoard[adres+3] && _cBoard[adres] == _cBoard[adres+4] &&
					!_bBoard[adres] &&			
					_fBoardDeltaX[adres]==0 && _fBoardDeltaY[adres]==0 &&	
					_fBoardDeltaX[adres+1]==0 && _fBoardDeltaY[adres+1]==0 &&
					_fBoardDeltaX[adres+2]==0 && _fBoardDeltaY[adres+2]==0 &&
					_fBoardDeltaX[adres+3]==0 && _fBoardDeltaY[adres+3]==0 &&
					_fBoardDeltaX[adres+4]==0 && _fBoardDeltaY[adres+3]==0 ) 	// check only gems that are not in move

				{
					if (h1==7)	// no need to check in last line 
					{	
						if (_cBoard[adres]<GEM_ROCK)		// only standard gems
						{
							_bBoard[adres] = true;
							_bBoard[adres+1] = true;
					
							_cBoard[adres+2] = GEM_RAINBOW;
							_bBoard[adres+2] = false;
							
							_bBoard[adres+3] = true;
							_bBoard[adres+4] = true;

							_cScaleBoard[adres] = _cBoard[adres];
							_cScaleBoard[adres+1] = _cBoard[adres+1];
							_cScaleBoard[adres+2] = _cBoard[adres+2];						
							_cScaleBoard[adres+3] = _cBoard[adres+3];
							_cScaleBoard[adres+4] = _cBoard[adres+4];

							_ulScaleTimer[adres] = ulTimer;
							_ulScaleTimer[adres+1] = ulTimer;
							_ulScaleTimer[adres+2] = ulTimer;
							_ulScaleTimer[adres+3] = ulTimer;
							_ulScaleTimer[adres+4] = ulTimer;

							Advance ((10/(_ucScoreMulti+1)),(100/(_ucScoreMulti+1)),((3*(_ucScoreMulti+1))+(_ulBonusTime/10)));
							Mix_PlayChannel(-1,_pMRainbow,0);
							bFound = true;
						}
					}
					else
					{
						if (!_bBoard[((h1+1)*8)+h2] && !_bBoard[((h1+1)*8)+h2+1] && !_bBoard[((h1+1)*8)+h2+2] && !_bBoard[((h1+1)*8)+h2+3] && !_bBoard[((h1+1)*8)+h2+4])	// empty space ?
						{
							if (_cBoard[adres]<GEM_ROCK)		// only standard gems
							{
								_bBoard[adres] = true;
								_bBoard[adres+1] = true;

								_cBoard[adres+2] = GEM_RAINBOW;
								_bBoard[adres+2] = false;

								_bBoard[adres+3] = true;
								_bBoard[adres+4] = true;

								_cScaleBoard[adres] = _cBoard[adres];
								_cScaleBoard[adres+1] = _cBoard[adres+1];
								_cScaleBoard[adres+2] = _cBoard[adres+2];						
								_cScaleBoard[adres+3] = _cBoard[adres+3];
								_cScaleBoard[adres+4] = _cBoard[adres+4];

								_ulScaleTimer[adres] = ulTimer;
								_ulScaleTimer[adres+1] = ulTimer;
								_ulScaleTimer[adres+2] = ulTimer;
								_ulScaleTimer[adres+3] = ulTimer;
								_ulScaleTimer[adres+4] = ulTimer;

								Advance ((10/(_ucScoreMulti+1)),(100/(_ucScoreMulti+1)),((3*(_ucScoreMulti+1))+(_ulBonusTime/10)));
								Mix_PlayChannel(-1,_pMRainbow,0);
								bFound = true;
							}
						}
					}
				}
			}
		}

		for (h1=0; h1<=3; h1++)	// vertical check
		{
			for (h2=0; h2<=7; h2++)
			{
				adres = (h1*8)+h2;

				if (_cBoard[adres] == _cBoard[((h1+1)*8)+h2] && _cBoard[adres] == _cBoard[((h1+2)*8)+h2] && _cBoard[adres] == _cBoard[((h1+2)*8)+h2] && _cBoard[adres] == _cBoard[((h1+3)*8)+h2] && _cBoard[adres] == _cBoard[((h1+4)*8)+h2] &&
					!_bBoard[adres] &&				// empty spaces
					_fBoardDeltaX[adres] == 0 && _fBoardDeltaY[adres] == 0 &&
					_fBoardDeltaX[((h1+1)*8)+h2] == 0 && _fBoardDeltaY[((h1+1)*8)+h2] == 0 &&
					_fBoardDeltaX[((h1+2)*8)+h2] == 0 && _fBoardDeltaY[((h1+2)*8)+h2] == 0 &&
					_fBoardDeltaX[((h1+3)*8)+h2] == 0 && _fBoardDeltaY[((h1+3)*8)+h2] == 0 &&
					_fBoardDeltaX[((h1+4)*8)+h2] == 0 && _fBoardDeltaY[((h1+4)*8)+h2] == 0 )
				{
					if (_cBoard[adres]<GEM_ROCK)		// only standard gems
					{
						_bBoard[adres] = true;
						_bBoard[((h1+1)*8)+h2] = true;
						
						_cBoard[((h1+2)*8)+h2] = GEM_RAINBOW;
						_bBoard[((h1+2)*8)+h2] = false;

						_bBoard[((h1+3)*8)+h2] = true;
						_bBoard[((h1+4)*8)+h2] = true;

						_cScaleBoard[adres] = _cBoard[adres];
						_cScaleBoard[((h1+1)*8)+h2] = _cBoard[((h1+1)*8)+h2];
						_cScaleBoard[((h1+2)*8)+h2] = _cBoard[((h1+2)*8)+h2];						
						_cScaleBoard[((h1+3)*8)+h2] = _cBoard[((h1+3)*8)+h2];
						_cScaleBoard[((h1+4)*8)+h2] = _cBoard[((h1+4)*8)+h2];

						_ulScaleTimer[adres] = ulTimer;
						_ulScaleTimer[((h1+1)*8)+h2] = ulTimer;
						_ulScaleTimer[((h1+2)*8)+h2] = ulTimer;
						_ulScaleTimer[((h1+3)*8)+h2] = ulTimer;
						_ulScaleTimer[((h1+4)*8)+h2] = ulTimer;

						Advance ((10/(_ucScoreMulti+1)),(100/(_ucScoreMulti+1)),((3*(_ucScoreMulti+1))+(_ulBonusTime/10)));
						Mix_PlayChannel(-1,_pMRainbow,0);	
						bFound = true;
					}
				}
			}
		}

	// check for 4 gems in line

		for (h1=0; h1<=7; h1++)	// horizontal check
		{
			for (h2=0; h2<=4; h2++)
			{
				adres = (h1*8)+h2;

				if (_cBoard[adres] == _cBoard[adres+1] && _cBoard[adres] == _cBoard[adres+2] && _cBoard[adres] == _cBoard[adres+3] &&
					!_bBoard[adres] &&				// empty spaces ? 
					_fBoardDeltaX[adres]==0 && _fBoardDeltaY[adres]==0 &&	
					_fBoardDeltaX[adres+1]==0 && _fBoardDeltaY[adres+1]==0 &&
					_fBoardDeltaX[adres+2]==0 && _fBoardDeltaY[adres+2]==0 &&
					_fBoardDeltaX[adres+3]==0 && _fBoardDeltaY[adres+3]==0)	// only gems that are not in move

				{
					if (h1==7)	// no check for last line
					{	
						if (_cBoard[adres]<GEM_ROCK)		// only standard gems
						{
							_bBoard[adres] = true;
							_bBoard[adres+1] = true;
							_bBoard[adres+2] = true;
							_bBoard[adres+3] = true;

							_cScaleBoard[adres] = _cBoard[adres];
							_cScaleBoard[adres+1] = _cBoard[adres+1];
							_cScaleBoard[adres+2] = _cBoard[adres+2];						
							_cScaleBoard[adres+3] = _cBoard[adres+3];

							_ulScaleTimer[adres] = ulTimer;
							_ulScaleTimer[adres+1] = ulTimer;
							_ulScaleTimer[adres+2] = ulTimer;
							_ulScaleTimer[adres+3] = ulTimer;
							
							Advance ((10/(_ucScoreMulti+1)),(100/(_ucScoreMulti+1)),((3*(_ucScoreMulti+1))+(_ulBonusTime/10)));
							Advance ((10/(_ucScoreMulti+1)),(100/(_ucScoreMulti+1)),((3*(_ucScoreMulti+1))+(_ulBonusTime/10)));
						
							bFound = true;
						}
					}
					else
					{
						if (!_bBoard[((h1+1)*8)+h2] && !_bBoard[((h1+1)*8)+h2+1] && !_bBoard[((h1+1)*8)+h2+2] && !_bBoard[((h1+1)*8)+h2+3])	// any empty spaces ? 
						{
							if (_cBoard[adres]<GEM_ROCK)		// only standard gems
							{
								_bBoard[adres] = true;
								_bBoard[adres+1] = true;
								_bBoard[adres+2] = true;
								_bBoard[adres+2] = true;

								_cScaleBoard[adres] = _cBoard[adres];
								_cScaleBoard[adres+1] = _cBoard[adres+1];
								_cScaleBoard[adres+2] = _cBoard[adres+2];						
								_cScaleBoard[adres+3] = _cBoard[adres+3];

								_ulScaleTimer[adres] = ulTimer;
								_ulScaleTimer[adres+1] = ulTimer;
								_ulScaleTimer[adres+2] = ulTimer;
								_ulScaleTimer[adres+3] = ulTimer;

								Advance ((10/(_ucScoreMulti+1)),(100/(_ucScoreMulti+1)),((3*(_ucScoreMulti+1))+(_ulBonusTime/10)));
								Advance ((10/(_ucScoreMulti+1)),(100/(_ucScoreMulti+1)),((3*(_ucScoreMulti+1))+(_ulBonusTime/10)));

								bFound = true;
							}
						}
					}
				}
			}
		}

		for (h1=0; h1<=4; h1++)	// vertical check
		{
			for (h2=0; h2<=7; h2++)
			{
				adres = (h1*8)+h2;

				if (_cBoard[adres] == _cBoard[((h1+1)*8)+h2] && _cBoard[adres] == _cBoard[((h1+2)*8)+h2] && _cBoard[adres] == _cBoard[((h1+3)*8)+h2] &&
					!_bBoard[adres] &&				// empty spaces ? 
					_fBoardDeltaX[adres] == 0 && _fBoardDeltaY[adres] == 0 &&
					_fBoardDeltaX[((h1+1)*8)+h2] == 0 && _fBoardDeltaY[((h1+1)*8)+h2] == 0 &&
					_fBoardDeltaX[((h1+2)*8)+h2] == 0 && _fBoardDeltaY[((h1+2)*8)+h2] == 0 &&
					_fBoardDeltaX[((h1+3)*8)+h2] == 0 && _fBoardDeltaY[((h1+3)*8)+h2] == 0)
				{
					if (_cBoard[adres]<GEM_ROCK)		// only standard gems
					{
						_bBoard[adres] = true;
						_bBoard[((h1+1)*8)+h2] = true;
						_bBoard[((h1+2)*8)+h2] = true;
						_bBoard[((h1+3)*8)+h2] = true;

						_cScaleBoard[adres] = _cBoard[adres];
						_cScaleBoard[((h1+1)*8)+h2] = _cBoard[((h1+1)*8)+h2];
						_cScaleBoard[((h1+2)*8)+h2] = _cBoard[((h1+2)*8)+h2];						
						_cScaleBoard[((h1+3)*8)+h2] = _cBoard[((h1+3)*8)+h2];

						_ulScaleTimer[adres] = ulTimer;
						_ulScaleTimer[((h1+1)*8)+h2] = ulTimer;
						_ulScaleTimer[((h1+2)*8)+h2] = ulTimer;
						_ulScaleTimer[((h1+3)*8)+h2] = ulTimer;

						Advance ((10/(_ucScoreMulti+1)),(100/(_ucScoreMulti+1)),((3*(_ucScoreMulti+1))+(_ulBonusTime/10)));
						Advance ((10/(_ucScoreMulti+1)),(100/(_ucScoreMulti+1)),((3*(_ucScoreMulti+1))+(_ulBonusTime/10)));
	
						bFound = true;
					}
				}
			}
		}


	// look for 3 gems in line 

		for (h1=0; h1<=7; h1++)	// horizontal check
		{
			for (h2=0; h2<=5; h2++)
			{
				adres = (h1*8)+h2;

				if (_cBoard[adres] == _cBoard[adres+1] && _cBoard[adres] == _cBoard[adres+2] &&
					!_bBoard[adres] &&				// empty spaces ? 
					_fBoardDeltaX[adres]==0 && _fBoardDeltaY[adres]==0 &&	
					_fBoardDeltaX[adres+1]==0 && _fBoardDeltaY[adres+1]==0 &&
					_fBoardDeltaX[adres+2]==0 && _fBoardDeltaY[adres+2]==0 )	// only gems that are not in move

				{
					if (h1==7)	// last line
					{	
						if (_cBoard[adres]<GEM_ROCK)		// only standard gems
						{
							_bBoard[adres] = true;
							_bBoard[adres+1] = true;
							_bBoard[adres+2] = true;

							_cScaleBoard[adres] = _cBoard[adres];
							_cScaleBoard[adres+1] = _cBoard[adres+1];
							_cScaleBoard[adres+2] = _cBoard[adres+2];						

							_ulScaleTimer[adres] = ulTimer;
							_ulScaleTimer[adres+1] = ulTimer;
							_ulScaleTimer[adres+2] = ulTimer;
							
							Advance ((10/(_ucScoreMulti+1)),(100/(_ucScoreMulti+1)),((3*(_ucScoreMulti+1))+(_ulBonusTime/10)));
						
							bFound = true;
						}
					}
					else
					{
						if (!_bBoard[((h1+1)*8)+h2] && !_bBoard[((h1+1)*8)+h2+1] && !_bBoard[((h1+1)*8)+h2+2])	// empty spaces ?
						{
							if (_cBoard[adres]<GEM_ROCK)		// only standard gems
							{
								_bBoard[adres] = true;
								_bBoard[adres+1] = true;
								_bBoard[adres+2] = true;

								_cScaleBoard[adres] = _cBoard[adres];
								_cScaleBoard[adres+1] = _cBoard[adres+1];
								_cScaleBoard[adres+2] = _cBoard[adres+2];						

								_ulScaleTimer[adres] = ulTimer;
								_ulScaleTimer[adres+1] = ulTimer;
								_ulScaleTimer[adres+2] = ulTimer;

								Advance ((10/(_ucScoreMulti+1)),(100/(_ucScoreMulti+1)),((3*(_ucScoreMulti+1))+(_ulBonusTime/10)));

								bFound = true;
							}
						}
					}
				}
			}
		}

		for (h1=0; h1<=5; h1++)	// vertical check
		{
			for (h2=0; h2<=7; h2++)
			{
				adres = (h1*8)+h2;

				if (_cBoard[adres] == _cBoard[((h1+1)*8)+h2] && _cBoard[adres] == _cBoard[((h1+2)*8)+h2] &&
					!_bBoard[adres] &&				// empty spaces ? 
					_fBoardDeltaX[adres] == 0 && _fBoardDeltaY[adres] == 0 &&
					_fBoardDeltaX[((h1+1)*8)+h2] == 0 && _fBoardDeltaY[((h1+1)*8)+h2] == 0 &&
					_fBoardDeltaX[((h1+2)*8)+h2] == 0 && _fBoardDeltaY[((h1+2)*8)+h2] == 0)
				{
					if (_cBoard[adres]<GEM_ROCK)		// only standard gems
					{
						_bBoard[adres] = true;
						_bBoard[((h1+1)*8)+h2] = true;
						_bBoard[((h1+2)*8)+h2] = true;

						_cScaleBoard[adres] = _cBoard[adres];
						_cScaleBoard[((h1+1)*8)+h2] = _cBoard[((h1+1)*8)+h2];
						_cScaleBoard[((h1+2)*8)+h2] = _cBoard[((h1+1)*8)+h2];						

						_ulScaleTimer[adres] = ulTimer;
						_ulScaleTimer[((h1+1)*8)+h2] = ulTimer;
						_ulScaleTimer[((h1+2)*8)+h2] = ulTimer;

						Advance ((10/(_ucScoreMulti+1)),(100/(_ucScoreMulti+1)),((3*(_ucScoreMulti+1))+(_ulBonusTime/10)));
	
						bFound = true;
					}
				}
			}
		}

	if (bFound)
		 Mix_PlayChannel(-1,_pMClick,0); 

	return bFound; //false;
}

// check if combination of 3 gems exist but do not modify and do not generate new gems

bool eIngame::isMatch3Check(void)
{
	bool bFound;
	int h1,h2;

	bFound = false;

		for (h1=0; h1<=7; h1++)	// horizontal check
		{
			for (h2=0; h2<=5; h2++)
			{
				if (_cBoard[(h1*8)+h2] == _cBoard[(h1*8)+h2+1] && _cBoard[(h1*8)+h2] == _cBoard[(h1*8)+h2+2])
				{
					if (h1==7)	// last line, skip empty space check
					{	
						if (_cBoard[(h1*8)+h2]<GEM_ROCK)		// only standard gems
							bFound = true;
					}
					else
					{
						if (!_bBoard[((h1+1)*8)+h2] && !_bBoard[((h1+1)*8)+h2+1] && !_bBoard[((h1+1)*8)+h2+2])	// check for empty spaces
						{
							if (_cBoard[(h1*8)+h2]<GEM_ROCK)		// only standard gems
								bFound = true;
						}
					}
				}
			}
		}

		for (h1=0; h1<=5; h1++)	// vertical check
		{
			for (h2=0; h2<=7; h2++)
			{
				if (_cBoard[(h1*8)+h2] == _cBoard[((h1+1)*8)+h2] && _cBoard[(h1*8)+h2] == _cBoard[((h1+2)*8)+h2])
				{
					if (_cBoard[(h1*8)+h2]<GEM_ROCK)		// only standard gems
						bFound = true;
				}
			}
		}

	return bFound;
}

// update gems that are moving

bool eIngame::isMoveGems(unsigned long ulTimer)
{
	bool bFallLock = false;

	for (int i=0; i<64;i++)
	{
		if (_fBoardDeltaX[i]<0)
		{
			if (_ulPrevTimer != ulTimer)
				_fBoardDeltaX[i]+=_fM3Delta;
			
			bFallLock = true;
		}

		if (_fBoardDeltaX[i]>0)
		{
			if (_ulPrevTimer != ulTimer)
				_fBoardDeltaX[i]-=_fM3Delta;
			
			bFallLock = true;
		}

		if (_fBoardDeltaY[i]<0)
		{
			if (_ulPrevTimer != ulTimer)
				_fBoardDeltaY[i]+=_fM3Delta;
			
			bFallLock = true;
		}

		if (_fBoardDeltaY[i]>0)
		{
			if (_ulPrevTimer != ulTimer)
				_fBoardDeltaY[i]-=_fM3Delta;
			
			bFallLock = true;
		}
	}

	return bFallLock;

}


// convert char digit to int and return as char :)

char eIngame::cToDigit(char cDigit)
{
	return char((int)cDigit-'0');
}

// draw progress bar and time bar

void eIngame::DrawProgressBar(unsigned long lTimer)
{
	float	fTimeBar;
	
	//  timer	

	fTimeBar = (float)((lTimer-_ulTimerStart)/10);
	fTimeBar = _pScreen->toX(BAR_SIZEX - fTimeBar + _ulBonusTime);

	if (fTimeBar > _pScreen->toX(BAR_SIZEX))
		fTimeBar = _pScreen->toX(BAR_SIZEX);

	// draw grey bars

	for (int i=_pScreen->toX(BAR_X); i<_pScreen->toX(BAR_SIZEX); i+=_pScreen->toX(BAR_X))	// granica 64+896
	{
		_pGreyBar->Position((float)i,_pScreen->toY(BAR_Y1));
		_pGreyBar->Render();

		_pGreyBar->Position((float)i,_pScreen->toY(BAR_Y2));
		_pGreyBar->Render();
	}

	fTimeBar = fTimeBar / 32;

	if (fTimeBar<=0.0f)	// game over check
	{
		fTimeBar = 0.0f;
		_bGameOver = true;
	}

	_pTimeBar->fScaleX(fTimeBar);
	_pTimeBar->Position(_pScreen->toX(BAR_X),_pScreen->toY(BAR_Y1));
	_pTimeBar->Render();

	// draw experience

	fTimeBar = (float)(_ulBonusExp/30);

	if (fTimeBar > _pScreen->toX(BAR_SIZEX))
	{
		_ulBonusExp = 0;
		
		if (_ucScoreMulti!=9)	// level up
		{
			_ucScoreMulti++;
			_pPopup->Add(POPUP_FLASH_WHITE,(unsigned long)lTimer);
			Mix_PlayChannel(-1,_pMLevelUp,0);
		}
		_ulBonusTime +=1000;	// add time when level up

		fTimeBar = BAR_SIZEX;
	}

	fTimeBar = fTimeBar / 32;

	_pExpBar->fScaleX(fTimeBar);
	_pExpBar->Position(_pScreen->toX(BAR_X),_pScreen->toY(BAR_Y2));
	_pExpBar->Render();
}

// render frame, check for mouse click

int eIngame::Render(unsigned long lTimer, CMouse *pMouse)
{
	int 	iReturn,h1,h2;
	char 	c1,c2;
	char	cScore[8];	//	conversion

	iReturn = 0;

	if (_ulTimerStart == 0)		// first frame ? 
	{
		_ulTimerStart = lTimer;
		
		if (pMouse->isLeft())	// do not catch click from main menu
			_bMouseLock = true;

		_pPopup->Add(POPUP_INGAME_START,lTimer);
	}

	_pBackground->Render();
	_pParticleManager->Render(lTimer);

	_pBoard->Render();

	DrawProgressBar(lTimer);

	// delta gems to be updated

	if (!_bGameOver)
		_bFallLock = isMoveGems(lTimer);

	if (_bFallLock)			// remember last move time, if no new move within 5secs - give a hint
		_lHintTime = lTimer;

	// should mouse button be unlocked

	if (_bMouseLock && !pMouse->isLeft())
		_bMouseLock=false;

	// check for match3, note - all other combinations - 5,4, L, -  include match3 check

	if (!_bFallLock) 
		isMatch3(lTimer);

	// delete matched gems

	for (h1=0; h1<64; h1++)
	{
		if (_bBoard[h1])
			_cBoard[h1]=-1;		
	}

	// scroll down from up

	if (!_bFallLock)
	{
		for (h1=7; h1>=1; h1--)	// vertical check from down to up
		{
			if (!_bFallLock)
			{
				for (h2=0; h2<=7; h2++)
				{
					if (_bBoard[(h1*8)+h2] == true && _bBoard[((h1-1)*8)+h2]==false)
					{
						_bBoard[(h1*8)+h2] = false; 
						_bBoard[((h1-1)*8)+h2] = true;			
						_cBoard[(h1*8)+h2] = _cBoard[((h1-1)*8)+h2];
						_cBoard[((h1-1)*8)+h2]=-1;	
						_fBoardDeltaY[(h1*8)+h2]= -64.0f;
					}
				}
			}
		}

		// fill top line with new gems

		for (h1=0; h1<=7; h1++)
		{
			if (_bBoard[h1])
			{
				_bBoard[h1]=false;
				
				if (_ucScoreMulti<1)		// if level 2 or more - add extra gems 
				{
					_cBoard[h1]=rand()%7;
				}
				else
				{
					_cBoard[h1]=rand()%9;		// 8 = stone 
					if (_cBoard[h1]==8)			// bomb is rare 
					{
						if (rand()%5==3)
						{
							_cBoard[h1]=GEM_BOMB;
						}
						else
						{
							_cBoard[h1]=rand()%7;
						}
					}
				}
				_fBoardDeltaY[h1] = -64.0f;
			}
		}
	}

	// bottom layer effect - scaled matched gems 

	for (h1=0; h1<8; h1++)
	{
		for (h2=0; h2<8; h2++)
		{
			if (_cScaleBoard[(h1*8)+h2]!=-1)
			{
				if ((lTimer-_ulScaleTimer[(h1*8)+h2])<100.0f)
				{
					
					float scale = (1+(((float)(lTimer-_ulScaleTimer[(h1*8)+h2])/100.0f)));

					_pGem[_cScaleBoard[(h1*8)+h2]]->Resize((BOARD_X1+(ITEM_SIZE*h2)+(ITEM_SIZE/2)-((ITEM_SIZE/2)*scale)) * _pScreen->fPixelX(), 
														   (BOARD_Y1+(ITEM_SIZE*h1)+(ITEM_SIZE/2)-((ITEM_SIZE/2)*scale)) * _pScreen->fPixelY(),
														   (BOARD_X1+(ITEM_SIZE*h2)+(ITEM_SIZE/2)+((ITEM_SIZE/2)*scale)) * _pScreen->fPixelX(), 
														   (BOARD_Y1+(ITEM_SIZE*h1)+(ITEM_SIZE/2)+((ITEM_SIZE/2)*scale)) * _pScreen->fPixelY());
					
					scale = scale - 1.0f;

					_pGem[_cScaleBoard[(h1*8)+h2]]->fAlfa (1-(1*scale)); 
					_pGem[_cScaleBoard[(h1*8)+h2]]->Render();
				}
				else
				{
					_cScaleBoard[(h1*8)+h2]=-1;
				}
			}
		}
	}

	// draw gems on board

	for (h1=0; h1<8; h1++)
	{
		for (h2=0; h2<8; h2++)
		{
			if (_cBoard[(h1*8)+h2]>-1)
			{
				_pGem[_cBoard[(h1*8)+h2]]->Resize((BOARD_X1+(ITEM_SIZE*h2)+_fBoardDeltaX[(h1*8)+h2]) *_pScreen->fPixelX(),(BOARD_Y1+(ITEM_SIZE*h1)+_fBoardDeltaY[(h1*8)+h2]) *_pScreen->fPixelY(), 
												(BOARD_X1+(ITEM_SIZE*h2)+_fBoardDeltaX[(h1*8)+h2]+ITEM_SIZE) *_pScreen->fPixelX(),(BOARD_Y1+(ITEM_SIZE*h1)+_fBoardDeltaY[(h1*8)+h2]+ITEM_SIZE) *_pScreen->fPixelY());					
				_pGem[_cBoard[(h1*8)+h2]]->fAlfa(1.0f);
				_pGem[_cBoard[(h1*8)+h2]]->Render();
			}
		}
	}

	// clicked ? 

	if (pMouse->fMouseX()>_pScreen->toX(BOARD_X1) && pMouse->fMouseX()<_pScreen->toX(BOARD_X2) && pMouse->fMouseY()>_pScreen->toY(BOARD_Y1) && pMouse->fMouseY()<_pScreen->toY(BOARD_Y2) && pMouse->isLeft() && !_bMouseLock && !_bGameOver && !_bFallLock)
	{
		h1 = (int)((pMouse->fMouseX()-_pScreen->toX(BOARD_X1))/_pScreen->toX(ITEM_SIZE));	// X on board
		h2 = (int)((pMouse->fMouseY()-_pScreen->toY(BOARD_Y1))/_pScreen->toY(ITEM_SIZE));	// Y on board

		if (_cClickedA==-1)
		{
			_cClickedA=(h2*8)+h1;
			_iClickedAx = _pScreen->toX(BOARD_X1 + (h1*ITEM_SIZE));
			_iClickedAy = _pScreen->toY(BOARD_Y1 + (h2*ITEM_SIZE));
		}
		else if (_cClickedB==-1)
		{
			if (_cClickedA!=(h2*8)+h1)			// double click on the same gem ? 
			{
				if ( (((_cClickedA-1 == (h2*8)+h1) || (_cClickedA+1 == (h2*8)+h1)) && _iClickedAy == _pScreen->toY(BOARD_Y1 + (h2*ITEM_SIZE))) || (_cClickedA+8 == (h2*8)+h1) || (_cClickedA-8 == (h2*8)+h1) ) // close enough ?
				{					
					_cClickedB=(h2*8)+h1;									// index of clicked B 
					_iClickedBx = _pScreen->toX(BOARD_X1 + (h1*ITEM_SIZE));	// offset X for gem B
					_iClickedBy = _pScreen->toY(BOARD_Y1 + (h2*ITEM_SIZE));	// offset Y for gem B
				}
				else	// gem B is not close enough to gem A, there for gem B is now gem A, gem B does not exist 
				{
					_cClickedA=(h2*8)+h1;
					_iClickedAx = _pScreen->toX(BOARD_X1 + (h1*ITEM_SIZE));
					_iClickedAy = _pScreen->toY(BOARD_Y1 + (h2*ITEM_SIZE));
				}
			}
			else	// if A=B then cancel selection
			{
				_cClickedA = -1;
				_cClickedB = -1;
				_iClickedAx = _iClickedAy = _iClickedBx = _iClickedBy = -1; 		
			}
		}	

		// if ROCK is clicked - cancel selection 

		if (_cBoard[_cClickedA]==GEM_ROCK || _cBoard[_cClickedB]==GEM_ROCK)
		{
			_cClickedA = -1;
			_cClickedB = -1;
			_iClickedAx = _iClickedAy = _iClickedBx = _iClickedBy = -1; 				
		}

		// if clicked gem is the bomb - explode 

		if (_cBoard[_cClickedA]==GEM_BOMB || _cBoard[_cClickedB]==GEM_BOMB)
		{
				Mix_PlayChannel(-1,_pMBomb,0);

				_cBoard[(h2*8)+h1] = -1;
				_bBoard[(h2*8)+h1] = true;
				
				if (h1>0)	// left
				{
					_cBoard[(h2*8)+h1-1] = -1;
					_bBoard[(h2*8)+h1-1] = true;
				}					

				if (h1<7)	// right
				{
					_cBoard[(h2*8)+h1+1] = -1;
					_bBoard[(h2*8)+h1+1] = true;
				}			

				if (h2>0)	// up
				{
					_cBoard[((h2-1)*8)+h1] = -1;
					_bBoard[((h2-1)*8)+h1] = true;
				}

				if (h2<7) // down
				{
					_cBoard[((h2+1)*8)+h1] = -1;
					_bBoard[((h2+1)*8)+h1] = true;
				}

				if (h1>0 && h2>0)	// up left
				{
					_cBoard[((h2-1)*8)+h1-1] = -1;
					_bBoard[((h2-1)*8)+h1-1] = true;
				}

				if (h2>0 && h1<7)	// up right
				{
					_cBoard[((h2-1)*8)+h1+1] = -1;
					_bBoard[((h2-1)*8)+h1+1] = true;
				}

				if (h2<7 && h1>0)	// down left
				{
					_cBoard[((h2+1)*8)+h1-1] = -1;
					_bBoard[((h2+1)*8)+h1-1] = true;
				}

				if (h1<7 && h2<7)	// down right
				{
					_cBoard[((h2+1)*8)+h1+1] = -1;
					_bBoard[((h2+1)*8)+h1+1] = true;
				}			

			_cClickedA = -1;
			_cClickedB = -1;
			_iClickedAx = _iClickedAy = _iClickedBx = _iClickedBy = -1; 						
		}

		// if DIAMOND clicked then we clean top and horizontal line 

		if (_cBoard[_cClickedA]==GEM_DIAMOND || _cBoard[_cClickedB]==GEM_DIAMOND)
		{
			Mix_PlayChannel(-1,_pMDiamond,0);

			// update vertical and horizontal line

			for (int i=0; i<8; i++)
			{
				_cScaleBoard[(h2*8)+i] = _cBoard[(h2*8)+i];
				_ulScaleTimer[(h2*8)+i] = (unsigned long)lTimer;

				_cScaleBoard[(i*8)+h1] = _cBoard[(i*8)+h1];
				_ulScaleTimer[(i*8)+h1] = (unsigned long)lTimer;

				_cBoard[(h2*8)+i] = -1;
				_bBoard[(h2*8)+i] = true;

				_cBoard[(i*8)+h1] = -1;
				_bBoard[(i*8)+h1] = true;
			}

			_cClickedA = -1;
			_cClickedB = -1;
			_iClickedAx = _iClickedAy = _iClickedBx = _iClickedBy = -1; 						
		}

		_bMouseLock = true;	// lock the mouse button

	}

	// right button cancel the selection 

	if (pMouse->isRight())
	{
		_cClickedA = -1;
		_cClickedB = -1;
		_iClickedAx = _iClickedAy = _iClickedBx = _iClickedBy = -1; 
	}

	// draw frame on selected gems

	if (_iClickedAx!=-1)
	{
		_pNumber[0]->Position((float)_iClickedAx, (float)_iClickedAy);
		_pNumber[0]->Render();
	}

	if (_iClickedBx!=-1)
	{
		_pNumber[1]->Position((float)_iClickedBx,(float)_iClickedBy);
		_pNumber[1]->Render();
	}

	// remove gems matched with RAINBOW GEM
	// 2 rainbow gems remove 3,4,5 and other 

	if (_cClickedA!=-1 && _cClickedB!=-1)	
	{
		// check for matched rainbow gems

		if (_cBoard[_cClickedA] == GEM_RAINBOW || _cBoard[_cClickedB] == GEM_RAINBOW)
		{
			Mix_PlayChannel(-1,_pMRainbow,0);
			
			if (_cBoard[_cClickedA] == GEM_RAINBOW)
			{
				h2 = _cBoard[_cClickedB]; // keep it to delete

				for (h1=0; h1<64; h1++)
				{
					if (_cBoard[h1]== h2)
					{
						_cScaleBoard[h1] = _cBoard[h1];
						_ulScaleTimer[h1] = (unsigned long)lTimer;

						_cBoard[h1]=-1;
						_bBoard[h1]=true;
					}
				}

				_cBoard[_cClickedA] = -1;
				_bBoard[_cClickedA] = true;
			}
			else
			{
				h2 = _cBoard[_cClickedA];
				
				for (int i=0; i<64; i++)
				{
					if (_cBoard[i]==h2)
					{
						_cBoard[i]=-1;
						_bBoard[i]=true;
					}
				}

				_cBoard[_cClickedB] = -1;
				_bBoard[_cClickedB] = true;

			}

			_cClickedA = -1;
			_cClickedB = -1;
			_iClickedAx = _iClickedAy = _iClickedBx = _iClickedBy = -1; 
			_bMouseLock = true;
		}
	}	// GEM_RAINBOW end

	if (_cClickedA!=-1 && _cClickedB!=-1)	// swap
	{
		
		h1=_cBoard[_cClickedA];
		_cBoard[_cClickedA] = _cBoard[_cClickedB];
		_cBoard[_cClickedB] = h1;	


		if (!isMatch3Check()) // no match ? keep id's to switch them back
		{
			_cReplacedA = _cClickedA;
			_cReplacedB = _cClickedB;

			_idA_lastDeltaX = _idA_lastDeltaY = 0.0f;
			_idB_lastDeltaX = _idB_lastDeltaY = 0.0f;
		}

			if (abs(_cClickedA-_cClickedB)==1)	// horizontal check
			{
				if (_cClickedA>_cClickedB)
				{
					_fBoardDeltaX[_cClickedA] = -64.0f;
					_idA_lastDeltaX = -64.0f;
					
					_fBoardDeltaX[_cClickedB] = 64.0f;
					_idB_lastDeltaX = 64.0f;
				}
				else
				{
					_fBoardDeltaX[_cClickedA] = 64.0f;
					_idA_lastDeltaX = 64.0f;

					_fBoardDeltaX[_cClickedB] = -64.0f;
					_idB_lastDeltaX = -64.0f;
				}
			}
			else	// vertical check
			{
				if (_cClickedA>_cClickedB)
				{
					_fBoardDeltaY[_cClickedA] = -64.0f;
					_idA_lastDeltaY = -64.0f;

					_fBoardDeltaY[_cClickedB] = 64.0f;
					_idB_lastDeltaY = 64.0f;
				}
				else
				{
					_fBoardDeltaY[_cClickedA] = 64.0f;
					_idA_lastDeltaY = 64.0f;

					_fBoardDeltaY[_cClickedB] = -64.0f;
					_idB_lastDeltaY = -64.0f;
				}
			}
		
		_bHint = false;		// cancel hint 

		_cClickedA = -1;
		_cClickedB = -1;
		_iClickedAx = _iClickedAy = _iClickedBx = _iClickedBy = -1; 
		_bMouseLock = true;
	}

	// switch back unmatched gems

	if (_cReplacedA != -1 && _cReplacedB != -1 )
	{
		if (_fBoardDeltaX[_cReplacedA]==0.0f && _fBoardDeltaY[_cReplacedA]==0.0f &&
			_fBoardDeltaX[_cReplacedA]==0.0f && _fBoardDeltaY[_cReplacedA]==0.0f)
		{		
			_fBoardDeltaX[_cReplacedA] = -_idB_lastDeltaX;
			_fBoardDeltaY[_cReplacedA] = -_idB_lastDeltaY;

			_fBoardDeltaX[_cReplacedB] = -_idA_lastDeltaX;
			_fBoardDeltaY[_cReplacedB] = -_idA_lastDeltaY;

			h1=_cBoard[_cReplacedA];
			_cBoard[_cReplacedA] = _cBoard[_cReplacedB];
			_cBoard[_cReplacedB] = h1;	


			_cReplacedA = -1;
			_cReplacedB = -1;

			_idA_lastDeltaX = _idA_lastDeltaY = 0.0f;
			_idB_lastDeltaX = _idB_lastDeltaY = 0.0f;
		}
	}

	// any moves possible ? 
	
	c2=0;

	for (h1=0; h1<=7; h1++) // horizontal check 
	{
		for (h2=0; h2<=6; h2++)
		{
			if (_cBoard[(h1*8)+h2]!=-1 && _cBoard[(h1*8)+h2+1]!=-1 && 
				_cBoard[(h1*8)+h2]<GEM_ROCK && _cBoard[(h1*8)+h2+1]<GEM_ROCK)	// only standard gems
			{
				c1 = _cBoard[(h1*8)+h2];
				_cBoard[(h1*8)+h2] = _cBoard[(h1*8)+h2+1];
				_cBoard[(h1*8)+h2+1] = c1;

			    if (isMatch3Check())
				{
					c2=1;
					_iHintX = _pScreen->toX(BOARD_X1 + (h2*ITEM_SIZE));
					_iHintY = _pScreen->toY(BOARD_Y1 + (h1*ITEM_SIZE));
				}

				c1 = _cBoard[(h1*8)+h2];
				_cBoard[(h1*8)+h2] = _cBoard[(h1*8)+h2+1];
				_cBoard[(h1*8)+h2+1] = c1;
			}
		}
	}

	for (h1=0; h1<=6; h1++) // vertical check 
	{
		for (h2=0; h2<=7; h2++)
		{
			if (_cBoard[(h1*8)+h2]!=-1 && _cBoard[((h1+1)*8)+h2]!=-1 &&
				_cBoard[(h1*8)+h2]<GEM_ROCK && _cBoard[((h1+1)*8)+h2]<GEM_ROCK)	// only standard gems
			{
				c1 = _cBoard[(h1*8)+h2];
				_cBoard[(h1*8)+h2] = _cBoard[((h1+1)*8)+h2];
				_cBoard[((h1+1)*8)+h2] = c1;

			    if (isMatch3Check())
				{
					c2=1;
					_iHintX = _pScreen->toX(BOARD_X1 + (h2*ITEM_SIZE));
					_iHintY = _pScreen->toY(BOARD_Y1 + (h1*ITEM_SIZE));
				}
				c1 = _cBoard[(h1*8)+h2];
				_cBoard[(h1*8)+h2] = _cBoard[((h1+1)*8)+h2];
				_cBoard[((h1+1)*8)+h2] = c1;
			}
		}
	}

	if (c2)	// check for hints, show if available  
	{
		if ((lTimer - _lHintTime)>1000 || _bHint)
		{
			_pHint->Position((float)_iHintX, (float)_iHintY);
			_pHint->Render();
		}
	}
	else
	{
		if (!_bFallLock) // no moves available - add RAINBOW GEM 
		{		
			bool bSpecial=false;

			for (int i=0; i<64; i++)
			{
				if (_cBoard[i] == GEM_RAINBOW || _cBoard[i] == GEM_DIAMOND || _cBoard[i] == GEM_BOMB)
					bSpecial = true;
			}

			// no special gems found on board - generate RAINBOW GEM

			if (!bSpecial)
			{
				_cBoard[lTimer%63] = GEM_RAINBOW;
				Mix_PlayChannel(-1,_pMRainbow,0);
				bSpecial = false;		
			}

		}
	}

	// points 

	sprintf(cScore,"%.7d",_ulScore);

	_pNumber[cToDigit(cScore[0])]->Position(32,500);
	_pNumber[cToDigit(cScore[0])]->Render();

	_pNumber[cToDigit(cScore[1])]->Position(32+32,500);
	_pNumber[cToDigit(cScore[1])]->Render();

	_pNumber[cToDigit(cScore[2])]->Position(32+64,500);
	_pNumber[cToDigit(cScore[2])]->Render();

	_pNumber[cToDigit(cScore[3])]->Position(32+96,500);
	_pNumber[cToDigit(cScore[3])]->Render();

	_pNumber[cToDigit(cScore[4])]->Position(32+128,500);
	_pNumber[cToDigit(cScore[4])]->Render();

	_pNumber[cToDigit(cScore[5])]->Position(32+160,500);
	_pNumber[cToDigit(cScore[5])]->Render();

	_pNumber[cToDigit(cScore[6])]->Position(32+192,500);
	_pNumber[cToDigit(cScore[6])]->Render();

	// if game over - overlay 

	if (_bGameOver)
	{
		if (_lInGameOver==0)
			_lInGameOver=lTimer;

		_pGameOver->Render();

		if (lTimer-_lInGameOver>500)	// exit from ingame
			iReturn = -1;		

	}

	// if no game over - draw buttons etc. 

	if (!_bGameOver)
	{
		if (_pButtonMenu->Render(pMouse)==ON_LEFT)
			iReturn = -1; 

		if (_pButtonHint->Render(pMouse)==ON_LEFT && !_bMouseLock)
		{
			_bHint = true;	
			_ulScore = (unsigned long)(_ulScore * 0.9);	// hints take 10% of points
			_bMouseLock = true;
		}	

		_pScoreMulti[_ucScoreMulti]->Position(200,300);
		_pScoreMulti[_ucScoreMulti]->Render();

	}

	_ulPrevTimer = lTimer;		// remember time of this frame

	_bPrevFallLock = _bFallLock;

	// check for sum of points during last 10 secs - if high enough - add popup with applause

	if (_ulScore != _ulScore1000 && _ulScore > _ulScore1000)		// avoid check after pressing hint 
	{
		if ((lTimer-_ulTimer1000)>1000)	// 10 seconds passed, restart
		{
			_ulTimer1000 = lTimer;
			_ulScore1000 = _ulScore;
		}
		else
		{
			if ((_ulScore-_ulScore1000) > (1000+(1000 * _ucScoreMulti)))	// check within 10 seconds
			{
				switch(lTimer%5)
				{
					case 0:
						_pPopup->Add(POPUP_INGAME_GOOD1,(unsigned long)lTimer);
					break;

					case 1:
						_pPopup->Add(POPUP_INGAME_GOOD2,(unsigned long)lTimer);
					break;

					case 2:
						_pPopup->Add(POPUP_INGAME_GOOD3,(unsigned long)lTimer);
					break;

					case 3:
						_pPopup->Add(POPUP_INGAME_GOOD4,(unsigned long)lTimer);
					break;

					case 4:
						_pPopup->Add(POPUP_INGAME_GOOD5,(unsigned long)lTimer);
					break;
				}
				Mix_PlayChannel(-1,_pMSuper,0);
				_ulTimer1000 = lTimer;
				_ulScore1000 = _ulScore;
			}
		}
	}

	// in there's no game over - render popup as requested

	if (!_bGameOver)
	{
		_pPopup->Render(lTimer);
	}

	return iReturn;	
}

unsigned long eIngame::ulGetScore(void)		// return points from this session 
{
	return _ulScore;
}

void eIngame::AddScore(unsigned long lScore)		// add points 
{
	_ulScore += lScore;
}

//end
