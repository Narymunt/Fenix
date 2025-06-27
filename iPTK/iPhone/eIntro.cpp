// main class

#include "eIntro.h"

// konstruktor, tutaj pakujemy najmniej jak tylko możliwe

eIntro::eIntro()
{
    m_bActive = false;
    m_ulTimer = 0;
    m_ulStart = 0;
}

eIntro::~eIntro()
{
    if (m_bActive)
    {        
        Close();
        m_bActive = false;
    }    
}

void eIntro::Open(void)
{
    m_pBackground = new CSprite((char*)"e_intro.png",0,0,SCREEN_X, SCREEN_Y);
    m_bActive = true;
}

void eIntro::Close(void)
{
    SafeDelete(m_pBackground);
    
    m_bActive = false;
    
}

int eIntro::Render(CTouch *pTouch, unsigned long ulTimer)
{
    m_pBackground->Render();
    
    if (m_ulStart == 0) m_ulStart = ulTimer;
    
    m_ulTimer = ulTimer - m_ulStart; 
    
    if (m_ulTimer>3000) return 255;
    
    
    return 0;   // nie rob nic
}

bool eIntro::isActive(void)
{
    return m_bActive;
}