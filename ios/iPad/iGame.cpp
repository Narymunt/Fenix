// main class

#include "iGame.h"

// konstruktor, tutaj pakujemy najmniej jak tylko możliwe

iGame::iGame() :
_iOS(0),_ulTimerPrev(0),_pScreen(0), _pBlack(0),_bSettingsMSX(true),_pMusic(0)
{
    m_pTouch = new CTouch();    // inicjalizacja ekranu dotykowego
    
}

// start programu

void iGame::init()
{    
	srand(time(0));
	KMiscTools::initMiscTools();

    reloadSettings();
    
	// Create our window	
  
	m_pWindow = KPTK::createKWindow(IPAD_2048x1536);

    if (m_pWindow->iX()==480 || m_pWindow->iX()==960)
    {
        SafeDelete(m_pWindow);
        m_pWindow = KPTK::createKWindow(IPHONE_960x640);
        m_pWindow->createGameWindow(960,640,32,false,(char*)"iGame");
        _iOS = IPHONE4;
        printf("PLATFORM: IPHONE4\n");
    }

    if (m_pWindow->iX()==568 || m_pWindow->iX()==1136)
    {
        SafeDelete(m_pWindow);
        m_pWindow = KPTK::createKWindow(IPHONE_1136x640);
        m_pWindow->createGameWindow(1136,640,32,false,(char*)"iGame");
        _iOS = IPHONE5;
        printf("PLATFORM: IPHONE4\n");
    }
    
    if (m_pWindow->iX()==1024 && m_pWindow->fScale()==1.0f)
    {
        SafeDelete(m_pWindow);
        m_pWindow = KPTK::createKWindow(IPAD_1024x768);
        m_pWindow->createGameWindow(1024,768,32,false,(char*)"iGame");
        _iOS = IPAD;
        printf("PLATFORM: IPAD\n");
    }

    if (m_pWindow->iX()==1024 && m_pWindow->fScale()==2.0f)
    {
        SafeDelete(m_pWindow);
        m_pWindow = KPTK::createKWindow(IPAD_2048x1536);
        m_pWindow->createGameWindow(2048,1536,32,false,(char*)"iGame");
        _iOS = IPAD_HD;
        printf("PLATFORM: IPAD_HD\n");
    }
    
    _pScreen = new CScreen(_iOS);
    
	KInput::initInput(m_pWindow->getWindowHandle());  // inicjalizacja io (touch)
    
    // inicjalizacja modułów
    
    _pPreload = new ePreload(_iOS);
    m_pAds = new eAds();
    _pIntro = new eIntro(_iOS);
    _pMainMenu = new eMainMenu();
    _pIngame = new eIngame();          // główna gra
    _pLevelMenu = new eLevelMenu();    // wybor etapu

    _pLanguage = new eLanguage(_iOS);
    _pSettings = new eSettings(_iOS);
    _pHelp = new eHelp(_iOS);
    _pCredits = new eCredits(_iOS);
    _pTroophy = new eTroophy(_pScreen);
    _pCongratulations = new eCongratulations(_pScreen->iOS());
    
    _pPostGame = new ePostGame();
    _pPostTroophy = new ePostTroophy();
    
    _pLoadScreen = new CSprite((char*)"load",_iOS);

    if (_iOS==IPAD_HD)
    {
        _pGreyBar = new CSprite((char*)"bar_grey64.png",0,0,64,64);
        _pGreenBar = new CSprite((char*)"bar_exp64.png",0,0,64,64);
    }
    else
    {
        _pGreyBar = new CSprite((char*)"bar_grey.png",0,0,64,64);
        _pGreenBar = new CSprite((char*)"bar_exp.png",0,0,64,64);
    }

    _pBlack = new CSprite((char*)"black100",_iOS);
    
    _pMusic = new KMusic();
    
    _iAppState = E_INTRO;
    _iPrevAppState = E_LANGUAGE;
}


// Called everytime in an infinite loop
bool iGame::render()
{
    int iMode;

	UpdateSprite(); // dotyk ekranu
    
	// Begin of rendering process
	m_pWindow->setDefaultWorldView();

    switch (_iAppState)
    {
        case E_PRELOAD:
            if (!_pPreload->isActive()) _pPreload->Open();
            
            iMode = _pPreload->Render(m_pTouch);
            
            if (_bSettingsMSX)
            {
                if (!_pMusic) _pMusic->stopMusic();
                
                SafeDelete(_pMusic);
                _pMusic = new KMusic();
                _pMusic->playMusic(KMiscTools::makeFilePath("music_mainmenu.mp3"));
            }
            
            if (iMode==255)
            {
                delete _pPreload;
                _pPreload = NULL;
                _iAppState = E_MAINMENU;
                _iPrevAppState = E_PRELOAD;
            }            
        break;

            
        case E_LANGUAGE:
            
            if (!_pLanguage->isActive())
                _pLanguage->Open();
            
            iMode = _pLanguage->Render(m_pTouch, m_ulTimer);

            if (iMode!=0)
            {
                if (_ucLanguage==0)
                {
                    _iAppState = E_PRELOAD;	// pierwsze uruchomienie aplikacji
                }
                else
                {
                    _iAppState = E_MAINMENU;	// kolejna zmiana jezyka
                    _iPrevAppState = E_PRELOAD;	// przeskakujemy preload przy zmianie jezyka z menu glownego
                }
                
                _ucLanguage = _pLanguage->ucLanguage();
                _pLanguage->Close();
            }
            
            
        break;
            
        //=== ADS ===
            
        case E_ADS:
            if (!m_pAds->isActive())
                m_pAds->Open();
            
            iMode=m_pAds->Render(m_pTouch, m_ulTimer);
            
            if (iMode==255)
            {
                delete m_pAds;
                m_pAds = NULL;
                _iAppState = E_INTRO;
            }                        
        break;
        
        //=== INTRO ===        
            
        case E_INTRO:
            if (!_pIntro->isActive()) _pIntro->Open();
            
            iMode = _pIntro->Render(m_pTouch, m_ulTimer);
            
            if (iMode==255)
            {
                delete _pIntro;
                _pIntro = NULL;
                _iAppState = E_LANGUAGE;
            }
            
        break;
            
            
        //=== SETTINGS ===
            
        case E_SETTINGS:
            
            if (!_pSettings->isActive())
                _pSettings->Open();
            
            if (_pSettings->Render(m_pTouch, m_ulTimer))
            {
                _iAppState = E_MAINMENU;
                _iPrevAppState = E_SETTINGS;
                _pSettings->Close();
                reloadSettings();
            }
            
        break;
            
        //=== HELP ===
            
        case E_HELP:

            if (!_pHelp->isActive())
                _pHelp->Open();
            
            if (_pHelp->Render(m_pTouch, m_ulTimer))
            {
                _iAppState = E_MAINMENU;
                _iPrevAppState = E_HELP;
                
                _pHelp->Close();
            }
            
        break;

        //=== CREDITS ===
            
        case E_CREDITS:
            
            if (!_pCredits->isActive())
                _pCredits->Open();
            
            if (_pCredits->Render(m_pTouch, m_ulTimer))
            {
                _iAppState = E_MAINMENU;
                _iPrevAppState = E_CREDITS;
                
                _pCredits->Close();
            }
            
        break;

        //=== TROOPHY ===
            
        case E_TROOPHY:

            if (!_pTroophy->isActive())
                _pTroophy->Open();
            
            if (_pTroophy->Render(m_pTouch, m_ulTimer))
            {
                _iAppState = E_MAINMENU;
                _iPrevAppState = E_TROOPHY;
                
                _pTroophy->Close();
            }
            
        break;
            
        //=== MAIN MENU ===
            
        case E_MAINMENU:
        
            if (!_pMainMenu->isActive())
            {
                _pMainMenu->ucLanguage(_ucLanguage);	// ustawiamy jezyk zanim zainicjalizujemy assety
                _iLoad = _pMainMenu->Open(_iOS);
                
                if (_iLoad==101)
                {
                    if (_iPrevAppState == E_SETTINGS)	// zaktualizuj ustawienia
                    {
                        reloadSettings();
                    }
                    
                    if (_iPrevAppState == E_INGAME || _iPrevAppState == E_POSTGAME ||
                        _iPrevAppState == E_SETTINGS || _iPrevAppState == E_CONGRATULATIONS)
                    {
                        if (_bSettingsMSX)
                        {
                            if (!_pMusic) _pMusic->stopMusic();
                            
                            SafeDelete(_pMusic);
                            _pMusic = new KMusic();
                            _pMusic->playMusic(KMiscTools::makeFilePath("music_mainmenu.mp3"));
                        }

                    }
                    LoadScreen(100);
                }
                else
                {
                    LoadScreen(_iLoad);
                }
            }
            else	// assety zaladowane - renderowanie
            {
                iMode = _pMainMenu->Render(m_pTouch,m_ulTimer);

                switch (iMode)
                {
						// START - wybor etapu
                        
                    case 1:
                        _pMainMenu->Close();
                        _iAppState = E_LEVELMENU;
                        _iPrevAppState = E_MAINMENU;
						break;
                        
						// SETTINGS - ustawienia
                        
                    case 2:
                        _pMainMenu->Close();
                        _iAppState = E_SETTINGS;
                        _iPrevAppState = E_MAINMENU;
						break;
                        
						// TROPHY ROOM
                        
                    case 3:
                        _pMainMenu->Close();
                        _iAppState = E_TROOPHY;
                        _iPrevAppState = E_MAINMENU;
						break;
                        
						// HELP
                        
                    case 4:
                        _pMainMenu->Close();
                        _iAppState = E_HELP;
                        _iPrevAppState = E_MAINMENU;
						break;
                        
						// SUPPORT / CREDITS
                        
                    case 5:
                        _pMainMenu->Close();
                        _iAppState = E_CREDITS;
                        _iPrevAppState = E_MAINMENU;
						break;
                        
						// ZMIANA JEZYKA
                        
                    case 10:
                        _pMainMenu->Close();
                        _iAppState = E_LANGUAGE;
                        _iPrevAppState = E_MAINMENU;
						break;
                }
                
            }
            
        break;  

        //=== IN GAME ===
            
        case E_INGAME:

            if (!_pIngame->isActive())
            {
                _pIngame->Open(_pLevelMenu->ucCurrentLevel(),_pScreen);
                
                if (_iPrevAppState == E_LEVELMENU)
                {
                    if (_bSettingsMSX)
                    {
                        if (_pMusic!=NULL)
                            _pMusic->stopMusic();
                        
                        SafeDelete(_pMusic);
                        _pMusic = new KMusic();

                        switch (_pLevelMenu->ucCurrentLevel())
                        {
                            case 1:
                                _pMusic->playMusic(KMiscTools::makeFilePath("music_ingame01.mp3"));
                            break;

                            case 2:
                                _pMusic->playMusic(KMiscTools::makeFilePath("music_ingame02.mp3"));
                                break;

                            case 3:
                                _pMusic->playMusic(KMiscTools::makeFilePath("music_ingame03.mp3"));
                                break;

                            case 4:
                                _pMusic->playMusic(KMiscTools::makeFilePath("music_ingame04.mp3"));
                                break;

                            case 5:
                                _pMusic->playMusic(KMiscTools::makeFilePath("music_ingame05.mp3"));
                                break;

                            case 6:
                                _pMusic->playMusic(KMiscTools::makeFilePath("music_ingame06.mp3"));
                                break;

                            case 7:
                                _pMusic->playMusic(KMiscTools::makeFilePath("music_ingame07.mp3"));
                                break;
                        }
                    }
                }
            }
            
            if (_pIngame->Render(m_ulTimer/10,m_pTouch)<0)
            {
                _pIngame->Close();
                _iAppState = E_POST_TROOPHY;
                _iPrevAppState = E_INGAME;
                _pMusic->stopMusic();
                SafeDelete(_pMusic);
            }
        break;

        //=== POST TROOPHY ===
            
        case	E_POST_TROOPHY:
            
            if (!_pPostTroophy->isActive())
            {
                _pPostTroophy->Open(_pScreen);

                if (_bSettingsMSX)  // wylaczamy muzyke
                {
                    if (!_pMusic) _pMusic->stopMusic();
                    SafeDelete(_pMusic);
                }
                
                for (int i=0; i<20; i++)									// dane graficzne juz rozladowane, ale tablica trzyma ustawienia z ostatniej gry
                    _pPostTroophy->ucNewTroophy(i,_pIngame->ucNewTroophy(i));
//                    _pPostTroophy->ucNewTroophy(i,1);                       // obejrzymy nadanie wszystkich nagród

                if (!_pPostTroophy->reOpen())
                {
                    _pPostTroophy->Close();
                    _iAppState = E_POSTGAME;
                }

               _pBlack->Render();
            }
            else
            {
                if (_pPostTroophy->Render(m_ulTimer,m_pTouch))
                {
                    _pPostTroophy->Close();
                    _iAppState = E_POSTGAME;
                }
            }
            
			break;
            
        //=== POST GAME ===
            
        case	E_POSTGAME:
            
            if (!_pPostGame->isActive())
            {
                _pPostGame->Open(_pScreen);
				
                if (_bSettingsMSX)
                {
                    if (!_pMusic) _pMusic->stopMusic();
                    SafeDelete(_pMusic);
                    _pMusic = new KMusic();
                    _pMusic->playMusic(KMiscTools::makeFilePath("music_postgame.mp3"));
                    
                }
                else
                {
                    if (!_pMusic) _pMusic->stopMusic();
                    SafeDelete(_pMusic);
                }
            }
            
        switch (_pPostGame->Render(m_ulTimer,m_pTouch))
        {
            case 1:
                if (_pMusic!=NULL) _pMusic->stopMusic();
                SafeDelete(_pMusic);
                _iAppState = E_MAINMENU;
                _iPrevAppState = E_POSTGAME;
                _pPostGame->Close();
                break;
                
            case 2:
                if (_pMusic!=NULL) _pMusic->stopMusic();
                SafeDelete(_pMusic);
                _iAppState = E_INGAME;
                _iPrevAppState = E_LEVELMENU;
                _pPostGame->Close();
                break;
                
            case 100:
                if (_pMusic!=NULL) _pMusic->stopMusic();
                SafeDelete(_pMusic);
                _iAppState = E_CONGRATULATIONS;
                _iPrevAppState = E_POSTGAME;
                _pPostGame->Close();
                break;
        }
            
			break;
            
            
        //=== LEVEL MENU ===
            
		case	E_LEVELMENU:
            
            if (!_pLevelMenu->isActive())
            {
                _pLevelMenu->Open(_pScreen);
                
                if (_iPrevAppState != E_PRELOAD && _iPrevAppState!=E_MAINMENU)
                {
                    if (_bSettingsMSX)
                    {
                        if (!_pMusic)
                            _pMusic->stopMusic();
                        
                        SafeDelete(_pMusic);
                        _pMusic->playMusic(KMiscTools::makeFilePath("music_mainmenu.mp3"));
                    }
                    else
                    {
                        _pMusic->stopMusic();
                    }
                }
            }
            
            iMode = _pLevelMenu->Render(m_pTouch, m_ulTimer);
            
            if (iMode>0 && iMode <100)
            {
                _pLevelMenu->Close();
                _iAppState = E_INGAME;
                _iPrevAppState = E_LEVELMENU;
            }
            
            if (iMode<0)
            {
                _pLevelMenu->Close();
                _iAppState = E_MAINMENU;
                _iPrevAppState = E_LEVELMENU;
            }
            
			break;

        //=== CONGRATULATIONS
            
        case	E_CONGRATULATIONS:
            
            if (!_pCongratulations->isActive())
            {
                _pCongratulations->Open(_pScreen);
                
                if (_bSettingsMSX)
                {
                    if (!_pMusic) _pMusic->stopMusic();
                    SafeDelete(_pMusic);
                    _pMusic = new KMusic();
                    _pMusic->playMusic(KMiscTools::makeFilePath("music_victory.mp3"));
                }
                else
                {
                    if (!_pMusic) _pMusic->stopMusic();
                    SafeDelete(_pMusic);
                }
            }
            
            if (_pCongratulations->Render(m_pTouch,m_ulTimer))
            {
                _iAppState = E_MAINMENU;
                _iPrevAppState = E_CONGRATULATIONS;
                _pCongratulations->Close();
            }
            
			break;
            
    }

//    if (_iAppState!=E_INTRO)
	m_pWindow->flipBackBuffer();  // przerzuc na ekran

    _iFPS++;
    
    if ((m_ulTimer-_ulTimerPrev)>1000)
    {
        printf("FPS: %d\n",_iFPS);
        _iFPS=0;
        _ulTimerPrev = m_ulTimer;
    }

    
    
	return true; // return false if you want to nicely quit
}


//=== w tej metodzie aktualizujemy tylko logike, bez funkcji rysujacych

void iGame::UpdateSprite()
{
	static int hitx=0, hity=0;  
    int iTap;
    
    gettimeofday(&Time,NULL);
    m_ulTimer = (Time.tv_sec * 1000) + (Time.tv_usec / 1000);
    
    
	if (KInput::getScreenTap() == 2) 
    {
        iTap = 2;
	}
    else
    {
        iTap = 0;
    }

    switch (_iOS)
    {
        case IPHONE4 :
            if (KInput::isScreenPressed(&hitx, &hity) == true)
            {
                m_pTouch->Update(true,false,(hitx-480)<<1,hity<<1,iTap);
                return;
            }
            
            if (KInput::isScreenReleased(&hitx,&hity)==true)
            {
                m_pTouch->Update(false,true,(hitx-480)<<1,hity<<1,iTap);
                return;
            }
            
            m_pTouch->Update(false,false,(hitx-480)<<1,hity<<1,iTap);
        break;
            

        case IPHONE5:
            if (KInput::isScreenPressed(&hitx, &hity) == true)
            {
                m_pTouch->Update(true,false,(hitx-568)<<1,hity<<1,iTap);
                return;
            }
            
            if (KInput::isScreenReleased(&hitx,&hity)==true)
            {
                m_pTouch->Update(false,true,(hitx-568)<<1,hity<<1,iTap);
                return;
            }
            
            m_pTouch->Update(false,false,(hitx-568)<<1,hity<<1,iTap);
        break;
        
        case IPAD:
            if (KInput::isScreenPressed(&hitx, &hity) == true)
            {
                m_pTouch->Update(true,false,hitx,hity,iTap);
                return;
            }
            
            if (KInput::isScreenReleased(&hitx,&hity)==true)
            {
                m_pTouch->Update(false,true,hitx,hity,iTap);
                return;
            }
            
            m_pTouch->Update(false,false,hitx,hity,iTap);
        break;

        case IPAD_HD:
            if (KInput::isScreenPressed(&hitx, &hity) == true)
            {
                m_pTouch->Update(true,false,(hitx-1024)<<1,hity<<1,iTap);
                return;
            }
            
            if (KInput::isScreenReleased(&hitx,&hity)==true)
            {
                m_pTouch->Update(false,true,(hitx-1024)<<1,hity<<1,iTap);
                return;
            }
            
            m_pTouch->Update(false,false,(hitx-1024)<<1,hity<<1,iTap);
        break;
    }
    
    
}

// czyszczenie zasobów przed wywołaniem destruktora

void iGame::cleanup()
{
	// Delete our window
    
	SafeDelete(m_pWindow);    
    SafeDelete(m_pTouch);

    // kasowanie modułów
 
    SafeDelete(_pPreload);
    SafeDelete(m_pAds);
    SafeDelete(_pIntro);
    SafeDelete(_pMainMenu);    
    SafeDelete(_pSettings);
    SafeDelete(_pIngame);      // modul glowny gry
    SafeDelete(_pHelp);
    SafeDelete(_pCredits);
    SafeDelete(_pScreen);
    SafeDelete(_pLanguage);
    SafeDelete(_pTroophy);
    SafeDelete(_pCongratulations);
    SafeDelete(_pBlack);

}

void iGame::LoadScreen(int iProgress)
{
	int x1,x2,y1,y2, dx, dy;
	float fx;
    
	_pLoadScreen->Render();

    switch (_iOS)
    {
        case IPHONE4 :
            x1 = 272; y1 = 408;
            x2 = 272+417; y2 = 408+28;
        break;

        case IPHONE5 :
            x1 = 320; y1 = 408;
            x2 = 320+500; y2 = 408+28;
            break;
            
        case IPAD :
            x1 = 207; y1 = 480;
            x2 = 820; y2 = 511;
        break;

        case IPAD_HD :
            x1 = 417; y1 = 958;
            x2 = 417+1217; y2 = 958+76;
        break;
            
    }
    
	dx = x2-x1;
    dy = y2-y1;

    fx = (float) (dx * (iProgress *0.01f));

    
    for (int i=x1; i<x2-_pGreyBar->fOriginalSizeX(); i++)
    {
        _pGreyBar->Position(i, y1);
        _pGreyBar->Render();
    }
        
    for (int i=0; i<fx-_pGreenBar->fOriginalSizeX(); i++)
    {
        _pGreenBar->Position(x1+i,y1);
        _pGreenBar->Render();
    }
    
}

void iGame::reloadSettings(void)
{
	// wczytaj config
    
	CGameSettings *pSetup;
    
	pSetup = new CGameSettings();
	pSetup->bLoad();
    
	_bSettingsMSX = pSetup->isMSX();
	_bSettingsMSX = pSetup->isSFX();
    
	delete pSetup;
}