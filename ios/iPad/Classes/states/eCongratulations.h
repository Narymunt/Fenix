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
#include "SpriteFont.h"

// stan w trakcie wczytywania zasobów

class eCongratulations : public CGameObject
{
	
public: 
	
    eCongratulations(int iOS);
    ~eCongratulations();                                                   // destruktor automatycznie zamyka stan
    
    void Open(CScreen *pScreen);                                           // otwiera stan
    void Close(void);                                                       // zamyka stan

    int Render(CTouch *pTouch, unsigned long ulTimer);         // render zwraca info czy powinien być zamknięty i/lub przejść do innego stanu
    
private:
    
    CSprite                 *_pBackground;
    CSprite                 *_pBlack;
    
    CButton                 *_pExitButton;
    
    CSpriteFont             *_pFont;
    
    CScreen                 *_pScreen;
    
    unsigned long           _ulTimerStart;
    
};
