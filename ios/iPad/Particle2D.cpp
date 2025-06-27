// main class

#include "Particle2D.h"

// konstruktor, tutaj pakujemy najmniej jak tylko możliwe

CParticle2D::CParticle2D(float fX, float fY, float fAlpha, float fAngle, float fIncX, float fIncY, float fIncAlpha, float fIncAngle, unsigned long ulLifeTime)
{
    m_fX = fX; 
    m_fY = fY;
    
    m_fAlpha = fAlpha; 
    m_fAngle = fAngle;
    
    m_fIncX = fIncX; 
    m_fIncY = fIncY; 

    m_fIncAngle = fIncAngle;
    m_fIncAlpha = fIncAlpha;
    
    m_ulStartTime =0; 
    
    m_ulLifeTime = ulLifeTime;
    
    m_bActive = false;
    
}

// regenerowanie particli, ktorych czas zycia juz minal

void CParticle2D::Regenerate(float fX, float fY, float fAlpha, float fAngle, float fIncX, float fIncY, float fIncAlpha, float fIncAngle, unsigned long ulLifeTime)
{
    m_fX = fX; 
    m_fY = fY;
    
    m_fAlpha = fAlpha; 
    m_fAngle = fAngle;
    
    m_fIncX = fIncX; 
    m_fIncY = fIncY; 
    
    m_fIncAngle = fIncAngle;
    m_fIncAlpha = fIncAlpha;
    
    m_ulStartTime =0; 
    
    m_ulLifeTime = ulLifeTime;
    
    m_bActive = false;    
    
}

void CParticle2D::Open(void)
{
    
    
}

void CParticle2D::Close(void)
{
    
    
}

int CParticle2D::Update(unsigned long ulTimer)
{
    if (m_ulStartTime == 0)
    {
        m_ulStartTime = ulTimer;
        m_bActive = true;
    }
    
    m_ulTimer = ulTimer - m_ulStartTime;
    
    if (m_ulTimer > m_ulLifeTime) return 0;
    
    if (m_bActive)
    {
        m_fX += m_fIncX; 
        m_fY += m_fIncY; 
        
        m_fAlpha += m_fIncAlpha; 
        
        if (m_fAlpha>1.0f) m_fAlpha=1.0f;
        if (m_fAlpha<0.0f) m_fAlpha=0.0f;
        
        m_fAngle += m_fIncAngle;
        
    }    
    
    return 1;   // nie rob nic
}

float CParticle2D::fGetX(void)
{
    return m_fX;
}

float CParticle2D::fGetY(void)
{
    return m_fY;
}

float CParticle2D::fGetAlpha(void)
{
    return m_fAlpha;
}

float CParticle2D::fGetIncAlpha(void)
{
    return m_fIncAlpha;
}

float CParticle2D::fGetAngle(void)
{
    return m_fAngle;
}

float CParticle2D::fGetIncAngle(void)
{
    return m_fIncAngle;
}


bool CParticle2D::isActive(void)
{
    return m_bActive;
}