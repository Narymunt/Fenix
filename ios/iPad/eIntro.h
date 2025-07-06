#ifndef _igame_eintro_
#define _igame_eintro_

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

// stan w trakcie wczytywania zasobów

class eIntro
{
	
public: 
	
    eIntro();
    ~eIntro();            // destruktor automatycznie zamyka stan
    
    void Open(void);        // otwiera stan 
    void Close(void);       // zamyka stan

    int Render(CTouch *pTouch, unsigned long ulTimer);       // render zwraca info czy powinien być zamknięty i/lub przejść do innego stanu
        
    bool isActive(void);    // czy dane wczytane ? 

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
    
    unsigned long         m_ulTimer;    // lokalny timer
    unsigned long         m_ulStart;    // czas startu modułu
    
    bool        m_bActive;
    
    CSprite     *m_pBackground;
	
};

#endif
