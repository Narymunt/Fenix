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
#include "GameSettings.h"
#include "SpriteFont.h"
#include "Button.h"
#include "Checkbox.h"
#include "Screen.h"
#include "Profile.h"

// stan w trakcie wczytywania zasobów

class eTroophy : public CGameObject
{
	
public: 
	
    eTroophy(CScreen *pScreen);
    ~eTroophy();                                                   // destruktor automatycznie zamyka stan
    
    void Open(void);                                            // otwiera stan
    void Close(void);                                           // zamyka stan

    int Render(CTouch *pTouch, unsigned long ulTimer);         // render zwraca info czy powinien być zamknięty i/lub przejść do innego stanu
    
private:
    
    CSprite                 *_pBackground;

	unsigned long           m_ulTimerStart;	// poczatek
    
	bool                    m_bTroophyLocked[21];

	CSprite                 *m_pTroophyLocked[21];
	CSprite                 *m_pTroophyUnlocked[21];
    
	CScreen                 *_pScreen;
    
};
