#pragma once

#include "config.h"

#include <time.h>
#include <sys/time.h>
#include "KPTK.h"
#include "KMiscTools.h"
#include "KGraphic.h"
#include "KSound.h"
#include "KMusic.h"
#include "KInput.h"

#include "Touch.h"
#include "Sprite.h"     // element graficzny

// moduły aplikacji

#include "ePreload.h"                       // pre load danych
#include "eAds.h"                           // banery, reklamy itp
#include "eIntro.h"                         // intro, animacja itp.
#include "eMainMenu.h"                      // menu główne gry
#include "eIngame.h"                        // gra
#include "eLevelMenu.h"                     // menu z levelami
#include "eLanguage.h"                      // wybor jezyka
#include "eSettings.h"                      // ustawienia gry
#include "eHelp.h"                          // pomoc
#include "eCredits.h"                       // scroll z autorami gry
#include "Screen.h"
#include "EventGFX.h"                       // event graficzny
#include "eTroophy.h"                       // zdobyte nagrody
#include "eCongratulations.h"
#include "ePostTroophy.h"                   // trofea zdobyte w grze
#include "ePostGame.h"                      // tablica hi-score

// główna klasa programu

class iGame
{
	
public: 
	
    iGame();
	
    // klasy predefiniowane w obj-c 
    
	void			init();
	bool			render();
	void			cleanup();	
	void			UpdateSprite();	

    void            LoadScreen(int iProgress);
    
    void            reloadSettings();
    
    template< class T > void SafeDelete( T*& pVal )
    {
        delete pVal;
        pVal = NULL;
    }
    
    template< class T > void SafeDeleteArray( T*& pVal )
    {
        delete[] pVal;
        pVal = NULL;
    }
   
    
private:
	
    bool                    _bSettingsMSX;
    
    CScreen                 *_pScreen;
    
    unsigned char           _ucLanguage;
    
    int                     _iOS;
    
    timeval                 Time;

    unsigned long           m_ulTimer;
    unsigned long           _ulTimerPrev;
    int                     _iFPS;
    
    
    int                     _iAppState;         // aktualny stan
    int                     _iPrevAppState;     // poprzedni stan
    
    int                     _iLoad;             // potrzebne dla progress bar
    
    CTouch                  *m_pTouch;
    
	KWindow                 *m_pWindow;         // Our window buffer

    KSound                  *m_pSound;			// Short sound effect in CAF format
	KMusic                  *_pMusic;			// Long MP3 audio track playing in background
	
    ePreload                *_pPreload;        // moduł przeładowania danych
    eAds                    *m_pAds;           // reklamy
	eIntro                  *_pIntro;         // intro
    eMainMenu               *_pMainMenu;       // menu główne
    eIngame                 *_pIngame;         // ingame
    eLevelMenu              *_pLevelMenu;      // level menu
    eLanguage               *_pLanguage;
    eSettings               *_pSettings;        // ustawienia gry
    eHelp                   *_pHelp;
    eCredits                *_pCredits;         // autorzy gry
    eTroophy                *_pTroophy;
    eCongratulations        *_pCongratulations; 
    ePostGame               *_pPostGame;        // tablica hi-score
    ePostTroophy            *_pPostTroophy;     // zaliczone osiagnieca w grze
    
    // grafiki do preload screen
    
    CSprite                 *_pLoadScreen;
    CSprite                 *_pGreyBar;
    CSprite                 *_pGreenBar;
    
    CSprite                 *_pBlack;           // czarna nakładka na ekran
    
};

