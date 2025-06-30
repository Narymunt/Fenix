#pragma once

#include "config.h"

#include <time.h>
#include "KPTK.h"
#include "KMiscTools.h"
#include "KGraphic.h"
#include "KSound.h"
#include "KMusic.h"
#include "KInput.h"
#include "Screen.h"
#include "Touch.h"
#include "Sprite.h"
#include "TouchButton.h"
#include "FlatButton.h"
#include "GameObject.h"
#include "Button.h"
#include "Profile.h"

// stan w trakcie wczytywania zasobów

class eLevelMenu : public CGameObject
{
	
public: 
	
    eLevelMenu();
    ~eLevelMenu();            // destruktor automatycznie zamyka stan
    
    void Open(CScreen *pScreen);        // otwiera stan
    void Close(void);       // zamyka stan

    int Render(CTouch *pTouch, unsigned long ulTimer);       // render zwraca info czy powinien być zamknięty i/lub przejść do innego stanu
    
    inline unsigned char ucCurrentLevel(void) { return _ucCurrentLevel; }
    inline void ucCurrentLevel(unsigned char c) { _ucCurrentLevel = c; }
    
private:
    
    CSprite             *_pBackground;
    
    CButton             *_pExitButton;
    CButton             *_pLevel[7];
    
    unsigned long       _ulMap;                     // ktore etapy sa dostepne
    unsigned long       _ulTimerStart;              // start wyswietlania etapu        

    unsigned char       _ucCurrentLevel;            
};

