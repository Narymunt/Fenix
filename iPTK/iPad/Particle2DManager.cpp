// main class

#include "Particle2DManager.h"
#include "debug.h"

float RandomFloat(float a, float b)
{
    return ((b-a)*((float)rand()/RAND_MAX))+a;
}

// konstruktor, tutaj pakujemy najmniej jak tylko możliwe

CParticle2DManager::CParticle2DManager(char cSpriteFilename[], unsigned long ulCount, 
                                   float fX1, float fY1, float fX2, float fY2, 
                                   float fMinIncX, float fMinIncY, float fMaxIncX, float fMaxIncY,
                                   float fAlpha, float fMinIncAlpha, float fMaxIncAlpha,
                                   float fAngle, float fMinIncAngle, float fMaxIncAngle,
                                   unsigned long ulMinLifeTime, unsigned long ulMaxLifeTime)
{
    float fX, fY, fIncX, fIncY, fIncAlpha, fIncAngle;
    unsigned long ulLifeTime;
      
    m_ulCount = ulCount;

    m_fX1 = fX1; m_fY1 = fY1; m_fX2 = fX2; m_fY2 = fY2; 
    
    m_fMinIncX = fMinIncX; m_fMinIncY = fMinIncY;
    m_fMaxIncX = fMaxIncX; m_fMaxIncY = fMaxIncY;
    
    m_fAlpha = fAlpha; m_fMinIncAlpha = fMinIncAlpha; m_fMaxIncAlpha = fMaxIncAlpha;
    m_fAngle = fAngle; m_fMinIncAngle = fMinIncAngle; m_fMaxIncAngle = fMaxIncAngle;
    
    m_ulMinLifeTime = ulMinLifeTime; m_ulMaxLifeTime = ulMaxLifeTime;
    
    for (unsigned long i=0; i<ulCount; i++)
    {    
  
        fX = RandomFloat(m_fX1, m_fX2);
        fY = RandomFloat(m_fY1, m_fY2);

        fIncX = RandomFloat(m_fMinIncX, m_fMaxIncX);
        fIncY = RandomFloat(m_fMinIncY, m_fMaxIncY);
    
        fIncAlpha = RandomFloat(m_fMinIncAlpha, m_fMaxIncAlpha);
        fIncAngle = RandomFloat(m_fMinIncAngle, m_fMaxIncAngle);
    
        ulLifeTime = m_ulMinLifeTime + ((unsigned long)rand()%(m_ulMaxLifeTime-m_ulMinLifeTime));
    
        m_pParticles.push_back(new CParticle2D(fX, fY, fAlpha, fAngle, fIncX, fIncY, fIncAlpha, fIncAngle, ulLifeTime));
    }        
    
    m_pImage = new CSprite(cSpriteFilename,0,0,64,64);
    
}

CParticle2DManager::~CParticle2DManager()
{
    SafeDelete(m_pImage);
}

void CParticle2DManager::Regenerate(unsigned long ulIndex)
{
    float fX, fY, fIncX, fIncY, fIncAlpha, fIncAngle;
    unsigned long ulLifeTime;

    fX = RandomFloat(m_fX1, m_fX2);
    fY = RandomFloat(m_fY1, m_fY2);
    
    fIncX = RandomFloat(m_fMinIncX, m_fMaxIncX);
    fIncY = RandomFloat(m_fMinIncY, m_fMaxIncY);
    
    fIncAlpha = RandomFloat(m_fMinIncAlpha, m_fMaxIncAlpha);
    fIncAngle = RandomFloat(m_fMinIncAngle, m_fMaxIncAngle);
    
    ulLifeTime = m_ulMinLifeTime + ((unsigned long)rand()%(m_ulMaxLifeTime-m_ulMinLifeTime));
    
    m_pParticles[ulIndex]->Regenerate(fX, fY, m_fAlpha, m_fAngle, fIncX, fIncY, fIncAlpha, fIncAngle, ulLifeTime);
    
    
}

void CParticle2DManager::Open(void)
{
    
    
}

void CParticle2DManager::Close(void)
{
    
    
}

int CParticle2DManager::Render(unsigned long ulTimer)
{
      
    for (unsigned long i=0; i<m_pParticles.size(); i++)
    {
        if (m_pParticles[i]->Update(ulTimer))
        {            
            m_pImage->Render( m_pParticles[i]->fGetX(), m_pParticles[i]->fGetY(), 
                             m_pParticles[i]->fGetAlpha(), m_pParticles[i]->fGetAngle());                             
        }
        else 
        {
            Regenerate(i);        // wygeneruj nowe parametry
        }
    }
    
    
        
    return 0;   // nie rob nic
}