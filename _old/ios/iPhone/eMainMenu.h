#ifndef _igame_emainmenu_
#define _igame_emainmenu_

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
#include "Anim.h"


// stan w trakcie wczytywania zasobów

class eMainMenu
{

	
public: 
	
    eMainMenu();
    ~eMainMenu();            // destruktor automatycznie zamyka stan
    
    void Open(void);        // otwiera stan 
    void Close(void);       // zamyka stan

    int Render(CTouch *pTouch, unsigned long ulTimer);       // render zwraca info czy powinien być zamknięty i/lub przejść do innego stanu
    
    bool isActive(void);    // czy dane wczytane ? 

    template< class T > void SafeDelete( T*& pVal )
    {
        if (pVal!=NULL)
        {
                delete pVal;
                pVal = NULL;
        }
    }
    
    template< class T > void SafeDeleteArray( T*& pVal )
    {
        delete[] pVal;
        pVal = NULL;
    }
    
    
private:	

    KMusic      *m_pMusic;
       
    bool        m_bActive;
    
    CSprite     *m_pBackground;
	CSprite     *m_pForeground;
    
    CSprite     *m_pClouds[4];
    float       m_fCloudsX[4];
    float       m_fCloudsY[4];
    
    CSprite     *m_pWindmillBase;
    CSprite     *m_pWindmillWings;
    
    CTouchButton    *m_pButtonOptions;
    CTouchButton    *m_pButtonAbout;
    CTouchButton    *m_pButtonClose;
    CTouchButton    *m_pButtonPlay;
    CTouchButton    *m_pButtonTrophy;
    
    CTouchButton    *m_pButtonProfile;
    
    CAnim           *m_pGrass;
    CAnim           *m_pGrass2;
    CAnim           *m_pGrassEyes;
    
    CAnim           *m_pNietoperek;
    
    CAnim           *m_pSingleLine;
    
};

#endif
