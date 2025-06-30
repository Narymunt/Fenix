// main class

#include "ePreload.h"

// konstruktor, tutaj pakujemy najmniej jak tylko możliwe

ePreload::ePreload()
{
    m_bActive = false;
    m_iCount = 0;
}

ePreload::~ePreload()
{
    if (m_bActive)
    {        
        Close();
        m_bActive = false;
    }    
}

void ePreload::Open(void)
{
    m_pBackground = new CSprite((char*)"e_preload.png",0,0,SCREEN_X,SCREEN_Y);
    m_bActive = true;
}

void ePreload::Close(void)
{
    SafeDelete(m_pBackground);
    m_bActive = false;
    
}

int ePreload::Render(CTouch *pTouch)
{
    m_pBackground->Render();
    
    m_iCount++;
    
    if (m_iCount==30) return 255;  // wyjscie do innego modulu
    
    return 0;   // nie rob nic
}

bool ePreload::isActive(void)
{
    return m_bActive;
}