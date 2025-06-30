#ifndef _igame_particle_
#define _igame_particle_

#include "config.h"

#include <time.h>

#include "KPTK.h"
#include "KMiscTools.h"
#include "KGraphic.h"
#include "KSound.h"
#include "KMusic.h"
#include "KInput.h"

#include "Sprite.h"

// particle to tylko informacja nt aktualnego elementu
// jego 

class CParticle
{

	
public: 
	
    CParticle();
    ~CParticle();            // destruktor automatycznie zamyka stan
    
    void Open(void);        // otwiera stan 
    void Close(void);       // zamyka stan

    int Render(unsigned long ulTimer);       // render zwraca info czy powinien być zamknięty i/lub przejść do innego stanu
    
private:	
    
    unsigned long   m_ulTimer;  // aktualny timer renderingu
    unsigned long   m_ulStart;  // czas startu renderingu
    
    bool        m_bActive;        
    
    CSprite     *m_pImage;  // obraz naszego particle
	
};

#endif
