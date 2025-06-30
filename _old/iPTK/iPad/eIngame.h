#ifndef _igame_eingame_
#define _igame_eingame_

#include "config.h"

#include <time.h>
#include "KPTK.h"
#include "KMiscTools.h"
#include "KGraphic.h"
#include "KSound.h"
#include "KMusic.h"
#include "KInput.h"

#include "Box.h"
#include "Touch.h"
#include "Sprite.h"
#include "Anim.h"
#include "TouchButton.h"

#include "Jelly.h"  // jelek
#include "Platform.h"   // platformy

#include "Particle2DManager.h"  // manager particli

// stan w trakcie wczytywania zasobów

class eIngame
{
	
public: 
	
    eIngame();
    ~eIngame();            // destruktor automatycznie zamyka stan
    
    void Open(void);        // otwiera stan 
    void Close(void);       // zamyka stan

    void SetLevel(unsigned int uiLevel);
    unsigned int uiGetLevel(void);
    
    int Render(CTouch *pTouch,  unsigned long ulTimer);       // render zwraca info czy powinien być zamknięty i/lub przejść do innego stanu

    void CheckCollision(CJelly *pJelly, CPlatform *pPlatform);
    void CheckCollisionH(CJelly *pJelly, CBox *BBox);
    void CheckCollisionV(CJelly *pJelly, CBox *BBox);
    
    bool isActive(void);    // czy dane wczytane ? 

    void UpdateZValue(unsigned int iJellyID);   // jelek z tym ID dostaje max Z
    
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
    
    bool        m_bActive;

    unsigned int m_iPressedID;  // ktory jelek jest wcisniety
    
    unsigned int m_uiCurrentLevel;
    
    unsigned long m_ulMaxZValue;    // ostatnio dotkniety jelek dostaje max Z
    
    KMusic      *m_pMusic;    
    
    CSprite     *m_pBackground;
    CSprite     *m_pForeground;

    CSprite     *m_pClouds[4];
    float       m_fCloudsX[4];
    float       m_fCloudsY[4];
    
    CSprite     *m_pWindmillBase;
    CSprite     *m_pWindmillWings;

    CAnim       *m_pGrass;
    CAnim       *m_pGrass2;
    CAnim       *m_pGrassEyes;
    CAnim       *m_pBat;
    
    int         m_iBatX;    
    
    CTouchButton    *m_pButtonClose;		
    
    CSprite     *m_pDotYellow;      // pokazuje trase   
    
    CSprite     *m_pGarnek;
    CBox        *m_pGarnekL, *m_pGarnekP, *m_pGarnekD;  // sciany garnka 
    
    CJelly      *m_pJelly[4];
    
    CPlatform   *m_pPlatform[4];    // nasze platformy
    
    CParticle2DManager *m_pParticleManager;
    
};

#endif
