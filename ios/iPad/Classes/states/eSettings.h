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

// stan w trakcie wczytywania zasobów

class eSettings : public CGameObject
{
	
public: 
	
    eSettings(int iOS);
    ~eSettings();                       // destruktor automatycznie zamyka stan
    
    void Open(void);                    // otwiera stan
    void Close(void);                   // zamyka stan

    int Render(CTouch *pTouch, unsigned long ulTimer);         // render zwraca info czy powinien być zamknięty i/lub przejść do innego stanu
    
private:
    
    CSprite                 *_pBackground;
    
    CButton                 *_pExitButton;
    
    CSpriteFont             *_pFont;

	CCheckbox				*m_pCheckboxMSX;
	CCheckbox				*m_pCheckboxSFX;
    
    
    int                     _iMSXFontX, _iMSXFontY;
    int                     _iSFXFontX, _iSFXFontY;
    
    char                    _cLanguage;
    
};
