#ifndef _igame_
#define _igame_

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

#include "ePreload.h"   // pre load danych
#include "eAds.h"       // banery, reklamy itp
#include "eIntro.h"     // intro, animacja itp. 
#include "eMainMenu.h"  // menu główne gry
#include "eIngame.h"    // gra
#include "eLevelMenu.h" // menu z levelami

#include "EventGFX.h"   // event graficzny

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
	
    timeval         Time;
    unsigned long   m_ulTimer;
    
    int         m_iGameState;
    
    CTouch      *m_pTouch;
    
	// Simpe iPTK objects for handling everything needed in a game
	
	KWindow		*m_pWindow;		// Our window buffer  

    KSound		*m_pSound;			// Short sound effect in CAF format
	KMusic		*m_pMusic;			// Long MP3 audio track playing in background    
    
	// Sprite position direction angle infos
	
	//float			xpos, ypos, xdir, ydir;
	//int				rotation;
	//float			zoom;
	
    ePreload    *m_pPreload;    // moduł przeładowania danych
    eAds        *m_pAds;        // reklamy
	eIntro      *m_pIntro;      // intro
    eMainMenu   *m_pMainMenu;   // menu główne
    eIngame     *m_pIngame;     // ingame
    eLevelMenu  *m_pLevelMenu;  // level menu
    
};

#endif
