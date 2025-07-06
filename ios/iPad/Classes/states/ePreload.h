#ifndef _igame_epreload_
#define _igame_epreload_

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

class ePreload
{
	
public: 
	
    ePreload(int iOS);
    ~ePreload();                        // destruktor automatycznie zamyka stan
    
    void Open(void);                    // otwiera stan
    void Close(void);                   // zamyka stan

    int Render(CTouch *pTouch);         // render zwraca info czy powinien być zamknięty i/lub przejść do innego stanu
    
    bool isActive(void);                // czy dane wczytane ?

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
    
    int         _iOS;
    
    int         m_iCount;
    
    bool        m_bActive;
    
    CSprite     *m_pBackground;
    CSprite     *_pShodan9Logo;
	
};

#endif
