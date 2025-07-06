#ifndef _igame_eads_
#define _igame_eads_

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

class eAds
{

	
public: 
	
    eAds();
    ~eAds();            // destruktor automatycznie zamyka stan
    
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
    
    unsigned long m_ulTimer;
    unsigned long m_ulStart;
    
    bool        m_bActive;
    
    KMusic      *m_pMusic;
    
    CSprite     *m_pBackground;
	
};

#endif
