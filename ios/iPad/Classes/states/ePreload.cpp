// main class

#include "ePreload.h"

// konstruktor, tutaj pakujemy najmniej jak tylko możliwe

ePreload::ePreload(int iOS) :
_iOS(iOS), m_bActive(false), m_iCount(0), m_pBackground(NULL),_pShodan9Logo(NULL)
{

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
    
    m_pBackground = new CSprite((char*)"start",_iOS);
    _pShodan9Logo = new CSprite((char*)"e_ads2",_iOS);
    
    m_bActive = true;
}

void ePreload::Close(void)
{
    SafeDelete(m_pBackground);
    SafeDelete(_pShodan9Logo);
    m_bActive = false;
    
}

int ePreload::Render(CTouch *pTouch)
{
    
    m_iCount++;
    
    if (m_iCount<200)
    {
        _pShodan9Logo->Render();
    }
    else
    {
        m_pBackground->Render();
    }
    
    if (m_iCount>400) return 255;  // wyjscie do innego modulu
    
    return 0;   // nie rob nic
}

bool ePreload::isActive(void)
{
    return m_bActive;
}