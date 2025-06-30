#ifndef _igame_particle2Dmanager_
#define _igame_particle2Dmanager_

#include "config.h"

#include <time.h>
#include <vector.h>

#include "KPTK.h"
#include "KMiscTools.h"
#include "KGraphic.h"
#include "KSound.h"
#include "KMusic.h"
#include "KInput.h"

#include "Particle2D.h"
#include "Sprite.h"

// particle to tylko informacja nt aktualnego elementu
// jego 

using namespace std;

class CParticle2DManager
{

	
public: 
	
    CParticle2DManager(char cSpriteFilename[], unsigned long ulCount, 
                     float fX1, float fY1, float fX2, float fY2, 
                     float fMinIncX, float fMinIncY, float fMaxIncX, float fMaxIncY,
                     float fAlpha, float fMinIncAlpha, float fMaxIncAlpha,
                     float fAngle, float fMinIncAngle, float fMaxIncAngle,
                     unsigned long ulMinLifeTime, unsigned long ulMaxLifeTime);
    ~CParticle2DManager();            // destruktor automatycznie zamyka stan
    
    void Open(void);        // otwiera stan 
    void Close(void);       // zamyka stan

    int Render(unsigned long ulTimer);       // render zwraca info czy powinien być zamknięty i/lub przejść do innego stanu
    
    void Regenerate(unsigned long ulIndex);  // wygenerowanie parametrow dla indeksu 
    
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
    
    unsigned long   m_ulCount;  // ile particli ? 
    
    unsigned long   m_ulTimer;  // aktualny timer renderingu
    unsigned long   m_ulStart;  // czas startu renderingu
    
    float           m_fX1, m_fY1, m_fX2, m_fY2;
    float           m_fMinIncX, m_fMinIncY, m_fMaxIncX, m_fMaxIncY;
    float           m_fAlpha, m_fMinIncAlpha, m_fMaxIncAlpha;
    float           m_fAngle, m_fMinIncAngle, m_fMaxIncAngle;
    
    unsigned long   m_ulMinLifeTime, m_ulMaxLifeTime;
    
    bool            m_bActive;        

    vector <CParticle2D*>   m_pParticles;
    CSprite                 *m_pImage;  // obraz naszego particle
	
};

#endif
