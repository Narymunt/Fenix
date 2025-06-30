#ifndef _igame_eventgfx_
#define _igame_eventgfx_

#include <time.h>
#include "KPTK.h"
#include "KMiscTools.h"
#include "KGraphic.h"
#include "KSound.h"
#include "KMusic.h"
#include "KInput.h"

#include "Anim.h"
#include "Sprite.h"
#include "Touch.h"

// stan w trakcie wczytywania zasobów

class CEventGFX
{
	
public: 
	
    CEventGFX();
    ~CEventGFX();            // destruktor automatycznie zamyka stan
    
    void Open(void);        // otwiera stan 
    void Close(void);       // zamyka stan

    int Render(void);       // render zwraca info czy powinien być zamknięty i/lub przejść do innego stanu

    
    
private:	
    
    bool        m_bActive;    
    
    unsigned char m_ucType; // jaki to rodzaj zdarzenia
    
    CAnim           *m_pAnimation;
    
	
};

#endif
