#ifndef _igame_elevelmenu_
#define _igame_elevelmenu_

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
#include "TouchButton.h"
#include "FlatButton.h"

// stan w trakcie wczytywania zasobów

class eLevelMenu
{
	
public: 
	
    eLevelMenu();
    ~eLevelMenu();            // destruktor automatycznie zamyka stan
    
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
        
    bool            m_bActive;
    
    CSprite         *m_pBackground;
    CSprite         *m_pForeground;
    
    CSprite         *m_pStars[4];       // gwiazdki pod ikonami leveli
    CSprite         *m_pLock;           // ikona klodki
    
    CSprite         *m_pNumber[10];     // numer levelu
    
    CTouchButton    *m_pButtonClose;	
    CFlatButton     *m_pKafel;
};

#endif
