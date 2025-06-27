#pragma once

#include "config.h"

#include <time.h>
#include "KPTK.h"
#include "KMiscTools.h"
#include "KGraphic.h"
#include "KSound.h"
#include "KMusic.h"
#include "KInput.h"

#include "Touch.h"
#include "Sprite.h"
#include "GameObject.h"
#include "Button.h"
#include "GameSettings.h"

// stan w trakcie wczytywania zasobów

class eLanguage : public CGameObject
{
	
public: 
	
    eLanguage(int iOS);
    ~eLanguage();                        // destruktor automatycznie zamyka stan
    
    void Open(void);                    // otwiera stan
    void Close(void);                   // zamyka stan

    int Render(CTouch *pTouch, unsigned long ulTimer);         // render zwraca info czy powinien być zamknięty i/lub przejść do innego stanu
    
    inline void ucLanguage(unsigned char uc) { _ucLanguage = uc; }
    inline unsigned char ucLanguage(void) { return _ucLanguage; }
    
private:	
    
    int             _iOS;
    
    CSprite         *_pBackground;
    CButton         *_pFlag[20];
    
    unsigned long   _ulTimerStart;
    unsigned char   _ucLanguage;
    
};

