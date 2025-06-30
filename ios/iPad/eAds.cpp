// ads, banners, etc. 

#include "eAds.h"

// konstruktor, tutaj pakujemy najmniej jak tylko możliwe

eAds::eAds()
{
    m_bActive = false;
    m_ulTimer = 0; 
    m_ulStart = 0;    
}

eAds::~eAds()
{
    if (m_bActive)
    {        
        Close();
        m_bActive = false;
    }    
}

void eAds::Open(void)
{
    m_pMusic = new KMusic();
    m_pMusic->setVolume(80);
    
    m_pBackground = new CSprite((char*)"city_logo.png",0,0,SCREEN_X, SCREEN_Y);

    m_bActive = true;
}

void eAds::Close(void)
{
   
    m_pMusic->stopMusic();
    SafeDelete(m_pMusic);
    
    SafeDelete(m_pBackground);   
    
    m_bActive = false;
}

int eAds::Render(CTouch *pTouch, unsigned long ulTimer)
{
    m_pBackground->Render();
    
    if (m_ulStart == 0) 
    {
        m_pMusic->playMusic(KMiscTools::makeFilePath("e_ads.mp3"));    
        m_ulStart = ulTimer;
    }
    
    m_ulTimer = ulTimer - m_ulStart; 
    
    if (m_ulTimer>6500) return 255;    
    return 0;   // nie rob nic
}

bool eAds::isActive(void)
{
    return m_bActive;
}