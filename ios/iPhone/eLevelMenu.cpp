// main class

#include "eLevelMenu.h"

// konstruktor, tutaj pakujemy najmniej jak tylko możliwe

eLevelMenu::eLevelMenu()
{
    m_bActive = false;
}

eLevelMenu::~eLevelMenu()
{
    if (m_bActive)
    {        
        Close();
        m_bActive = false;
    }    
}

void eLevelMenu::Open(void)
{
    char cFilename[20];
    
    m_pBackground = new CSprite((char*)"levelmenu_layer0.png",0,0,SCREEN_X, SCREEN_Y);
    m_pForeground = new CSprite((char*)"levelmenu_layer5.png",0,0,SCREEN_X, SCREEN_Y);
    
    m_pButtonClose = new CTouchButton(MMENU_CLOSE_X, MMENU_CLOSE_Y, MMENU_CLOSE_SIZE_X, MMENU_CLOSE_SIZE_Y,(char*) "button/mmenu_close_idle.png",(char*) "button/mmenu_close_onover.png",(char*) "button/mmenu_close_onclick.png");
    
    m_pStars[0] = new CSprite((char*)"button/stars0.png",0,0,128,128);
    m_pStars[1] = new CSprite((char*)"button/stars1.png",0,0,128,128);
    m_pStars[2] = new CSprite((char*)"button/stars2.png",0,0,128,128);
    m_pStars[3] = new CSprite((char*)"button/stars3.png",0,0,128,128);
        
    m_pLock = new CSprite((char*)"lock.png",0,0,128,128);
    
    m_pKafel = new CFlatButton( 0, 0, 128, 128, (char*)"levelmenu_kafelek.png");
    
    for (int i=0; i<10;i++)
    {
        sprintf(cFilename,"font/%d.png",i+1);
        m_pNumber[i] = new CSprite(cFilename,0,0,128,128);
    }
    
    m_bActive = true;
}

void eLevelMenu::Close(void)
{
    SafeDelete(m_pBackground);
    SafeDelete(m_pForeground);
    
    for (int i=0; i<4; i++) SafeDelete(m_pStars[i]);
         
    SafeDelete(m_pLock);
    
    SafeDelete(m_pButtonClose);
    SafeDelete(m_pKafel);
    
    for (int i=0; i<10; i++)
        SafeDelete(m_pNumber[i]);
    
    m_bActive = false;
    
}

int eLevelMenu::Render(CTouch *pTouch, unsigned long ulTimer)
{
    int iReturn=0;
    
    m_pBackground->Render();
    m_pForeground->Render();

    for (int j=0; j<2; j++)
    {
        for (int i=0; i<5; i++)
        {
            if (m_pKafel->Render(pTouch,64+(i*192),192+(j*192)))
            {
                iReturn = (1+i)+(j*5);  // zapamietaj stan, ale renderuj pozostale klocki
            }            
            
            if (((1+i)+(j*5))<4)
            {
                m_pStars[1]->Render(64+(i*192),192+(j*192));
                m_pNumber[(i)+(j*5)]->Render(64+(i*192),192+(j*192));
            }
            else
            {
                m_pLock->Render(64+(i*192),192+(j*192));                
            }
        
            
        }
    }
    
    if (iReturn!=0) return iReturn; // zwraca numer wybranego levelu
    
    if (m_pButtonClose->Render(pTouch)==2) 
    {
        return 255;
    }   
    
    return 0;   // nie rob nic
}

bool eLevelMenu::isActive(void)
{
    return m_bActive;
}