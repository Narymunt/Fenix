#ifndef _igame_epreload_
#define _igame_epreload_

#include <time.h>
#include "KPTK.h"
#include "KMiscTools.h"
#include "KGraphic.h"
#include "KSound.h"
#include "KMusic.h"
#include "KInput.h"

#include "Sprite.h"

// stan w trakcie wczytywania zasobów

class ePreload
{

	
public: 
	
    ePreload();
    ~ePreload();            // destruktor automatycznie zamyka stan
    
    void Open(void);        // otwiera stan 
    void Close(void);       // zamyka stan

    int Render(void);       // render zwraca info czy powinien być zamknięty i/lub przejść do innego stanu
    
private:	
    
    bool        m_bActive;
    
    CSprite     *m_pBackground;
	
};

#endif
