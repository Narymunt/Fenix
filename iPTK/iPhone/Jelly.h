#ifndef _igame_jelly_
#define _igame_jelly_

#include "config.h"

#include <time.h>
#include "KPTK.h"
#include "KMiscTools.h"
#include "KGraphic.h"
#include "KSound.h"
#include "KMusic.h"
#include "KInput.h"

#include "Box.h"        // bounding box
#include "Touch.h"
#include "Sprite.h"
#include "Anim.h"
#include "Sound.h"

// stan w trakcie wczytywania zasobów

class CJelly
{
	
public: 
	
    CJelly(char cType, float fX, float fY);
    ~CJelly();            // destruktor automatycznie zamyka stan
    
    void SetPosition(float fX, float fY);

    inline void SetPosition (int fX, int fY) { SetPosition((float)fX,(float)fY); }    
    
    void SetForce(float fX, float fY);
    void IncForce(float fX, float fY);
    
    float fGetForceX(void);
    float fGetForceY(void);     
    
    float fGetX(void);
    float fGetY(void);
    
    int Render(CTouch *pTouch, unsigned long ulTimer, bool bActive);       // render zwraca info czy powinien być zamknięty i/lub przejść do innego stanu
    
    bool isActive(void);    // czy dane wczytane ? 

    void SetLanding(bool bLanding, unsigned long ulTimer);
    bool isLanding(void);
    
    CBox *eGetBBox(void);    // zwraca bounding box
    
    void    SetZValue(unsigned long ulZValue);
    unsigned long ulGetZValue(void);
    
    void PlaySndLanding(void);
    
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
   
    bool        m_bActive;

    bool        m_bLanding;
    char        m_cLandingType;         // jakiego rodzaju animacja przy spadaniu
    
    unsigned char m_ucCollisionAnim;    // która animacje kolizji teraz odtwarzamy
    
    unsigned long m_ulTimerEvent;     // osobny timer dla aktualnie odtwarzanego eventu
    
    unsigned long m_ulZValue;       // kolejnosc rysowania jelkow ma byc zalezna od ostatniego ruchu a nie listy w kolejce
    
    float       m_fX, m_fY, m_fIncX, m_fIncY;
    
    float       m_fGravity;
    float       m_fGroundX;      // tarcie po ziemi

    bool        m_bPress, m_bRelease;
    int         m_iStartX, m_iStartY, m_iPressX, m_iPressY, m_iReleaseX, m_iReleaseY;   
    
    float       m_fScale;
    
    unsigned char   m_ucIdleSpeed;      // 40 + 0-10 jak szybko ma sie odtwarzac idle
    
    CSprite     *m_pBody;

    CAnim     *m_pIdle;
    
    CAnim       *m_pEyes;
    CAnim       *m_pStretch;
    
    CAnim       *m_pLandingEyes[3];
    CAnim       *m_pLanding[3];
    
    CAnim       *m_pCollision[8];       // animacje przy uderzeniach
    
	CBox        *m_pBoundBox;
    
    CSound      *m_pSndLanding;
    CSound      *m_pSndJump;
    
};

#endif
