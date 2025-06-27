// main class

#include "iGame.h"

// konstruktor, tutaj pakujemy najmniej jak tylko możliwe

iGame::iGame()
{
    m_pTouch = new CTouch();    // inicjalizacja ekranu dotykowego
}

// start programu

void iGame::init()
{    
	srand(time(0));
	KMiscTools::initMiscTools();

	// Create our window	

	m_pWindow = KPTK::createKWindow(K_1024x768);
	m_pWindow->createGameWindow(1024,768,32,false,(char*)"iGame");
    
	KInput::initInput(m_pWindow->getWindowHandle());  // inicjalizacja io (touch)
    
    // inicjalizacja modułów
    
    m_pPreload = new ePreload();
    m_pAds = new eAds();
    m_pIntro = new eIntro();
    m_pMainMenu = new eMainMenu();
    m_pIngame = new eIngame();          // główna gra
    m_pLevelMenu = new eLevelMenu();    // wybor etapu
    
    m_iGameState = E_MAINMENU;
}


// Called everytime in an infinite loop
bool iGame::render()
{
    int iMode;
    
	// Begin of rendering process
	m_pWindow->setDefaultWorldView();

    switch (m_iGameState)
    {
        case E_PRELOAD:
            if (!m_pPreload->isActive()) m_pPreload->Open();
            
            iMode=m_pPreload->Render(m_pTouch);
            
            if (iMode==255)
            {
                delete m_pPreload;
                m_pPreload = NULL;
                m_iGameState = E_ADS;
            }            
        break;

        //=== ADS ===
            
        case E_ADS:
            if (!m_pAds->isActive()) m_pAds->Open();
            
            iMode=m_pAds->Render(m_pTouch, m_ulTimer);
            
            if (iMode==255)
            {
                delete m_pAds;
                m_pAds = NULL;
                m_iGameState = E_INTRO;
            }                        
        break;
        
        //=== INTRO ===        
            
        case E_INTRO:
            if (!m_pIntro->isActive()) m_pIntro->Open();
            
            iMode = m_pIntro->Render(m_pTouch, m_ulTimer);
            
            if (iMode==255)
            {
                delete m_pIntro;
                m_pIntro = NULL;
                m_iGameState = E_MAINMENU;
            }
            
        break;
            
        //=== MAIN MENU ===
            
        case E_MAINMENU:
            
            if (!m_pMainMenu->isActive()) m_pMainMenu->Open();
            
            iMode = m_pMainMenu->Render(m_pTouch,m_ulTimer);
            
            switch (iMode)
            {            
                case 10:    
                    m_iGameState = E_LEVELMENU;                                       
                break;
                    
            }
            
        break;  

        //=== LEVEL MENU === 
        
        case E_LEVELMENU:

            if (!m_pLevelMenu->isActive()) m_pLevelMenu->Open();
            
            iMode = m_pLevelMenu->Render(m_pTouch,m_ulTimer);
            
            // 0 - nic nie wybrano
            // 1-254 - numer levelu
            // 255 - powrot do menu
            
            if (iMode >0 && iMode< 255 && iMode<4)
            {
                m_pLevelMenu->Close();      // wejscie do wybranego levelu
                m_pMainMenu->Close();
                m_pIngame->SetLevel(iMode);
                m_iGameState = E_INGAME;                
            }
            
            if (iMode == 255)            
            {
                m_pLevelMenu->Close();      // powrot do glownego menu
                m_iGameState = E_MAINMENU;            
            }
                        
        break;

        //=== IN GAME ===
            
        case E_INGAME:

            if (!m_pIngame->isActive()) 
            {
                m_pMainMenu->Close();
                m_pLevelMenu->Close();
                m_pIngame->Open();
            }
            
            iMode = m_pIngame->Render(m_pTouch,m_ulTimer);
            
            switch (iMode)
            {
                case 255:   // powrot do menu
                    m_pIngame->Close();
                    m_pMainMenu->Open();
                    m_iGameState = E_MAINMENU;
                break;
            }
            
        break;
            
            
    }
    
	UpdateSprite(); // aktualizacja logiki
    
	m_pWindow->flipBackBuffer();  // przerzuc na ekran

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
    
}

// czyszczenie zasobów przed wywołaniem destruktora

void iGame::cleanup()
{
	// Delete our window
    
	SafeDelete(m_pWindow);    
    SafeDelete(m_pTouch);

    // kasowanie modułów
 
    SafeDelete(m_pPreload);
    SafeDelete(m_pAds);
    SafeDelete(m_pIntro);
    SafeDelete(m_pMainMenu);    
    
    SafeDelete(m_pIngame);      // modul glowny gry

}
