#ifndef _igame_particle2D_
#define _igame_particle2D_

#include "config.h"

#include <time.h>

#include "KPTK.h"
#include "KMiscTools.h"
#include "KGraphic.h"
#include "KSound.h"
#include "KMusic.h"
#include "KInput.h"

#include "Sprite.h"

// Particle2D to tylko informacja nt aktualnego elementu
// jego 

class CParticle2D
{

	
public: 
	
    CParticle2D(float fX, float fY, float fAlpha, float fAngle, float fIncX, float fIncY, float fIncAlpha, float fIncAngle, unsigned long ulLifeTime);
    ~CParticle2D();            // destruktor automatycznie zamyka stan
    
    void Regenerate(float fX, float fY, float fAlpha, float fAngle, float fIncX, float fIncY, float fIncAlpha, float fIncAngle, unsigned long ulLifeTime);
    
    void Open(void);        // otwiera stan 
    void Close(void);       // zamyka stan

    int Update(unsigned long ulTimer);       // render zwraca info czy powinien być zamknięty i/lub przejść do innego stanu
    
    float fGetX(void);
    float fGetY(void);
    
    float fGetAlpha(void);
    float fGetIncAlpha(void);
    
    float fGetAngle(void);
    float fGetIncAngle(void);
    
    bool isActive(void);
    
private:	
    
    float           m_fX, m_fY;
    float           m_fAlpha, m_fAngle;
    
    float           m_fIncAlpha, m_fIncAngle;    

    float           m_fIncX, m_fIncY;
    
    
    unsigned long   m_ulTimer;  // aktualny timer renderingu

    unsigned long   m_ulStartTime;  // czas startu renderingu    
    unsigned long   m_ulLifeTime;   
    
    bool        m_bActive;        
    
    CSprite     *m_pImage;  // obraz naszego Particle2D
	
};

#endif
