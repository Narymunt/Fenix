// main class

#include "Jelly.h"

// konstruktor, tutaj pakujemy najmniej jak tylko możliwe

CJelly::CJelly(char cType, float fX, float fY)
{
    
    m_pSndJump = new CSound((char*)"sfx/cartoon008.wav");
    m_pSndLanding = new CSound((char*)"sfx/cartoon035.wav");
    
    switch (cType)
    {
        case JELLY_BLUE:
            m_pBody = new CSprite((char*)"jelly/blue/body_blue.png",0,0,65,65);
            m_pEyes = new CAnim((char*)"jelly/blue/jelly_eyes_blue_",9, 64, 64);
            
            m_pStretch = new CAnim((char*)"jelly/blue/jelly_rozciaganie_blue_",10, 128, 128);

            m_pLanding[0] = new CAnim((char*)"jelly/blue/jelly_ladowanie_blue_1_",9,128,128);
            m_pLanding[1] = new CAnim((char*)"jelly/blue/jelly_ladowanie_blue_2_",14,128,128);
            m_pLanding[2] = new CAnim((char*)"jelly/blue/jelly_ladowanie_blue_3_",19,128,128);

            m_pLandingEyes[0] = new CAnim((char*)"jelly/blue/jelly_ladowanie_eyes_1_",9,128,128);
            m_pLandingEyes[1] = new CAnim((char*)"jelly/blue/jelly_ladowanie_eyes_2_",14,128,128);
            m_pLandingEyes[2] = new CAnim((char*)"jelly/blue/jelly_ladowanie_eyes_3_",19,128,128);            
            
            m_pCollision[0] = new CAnim((char*)"jelly/blue/jelly_collision_1_blue_",5,64,64);
            m_pCollision[1] = new CAnim((char*)"jelly/blue/jelly_collision_2_blue_",5,64,64);
            m_pCollision[2] = new CAnim((char*)"jelly/blue/jelly_collision_3_blue_",5,64,64);
            m_pCollision[3] = new CAnim((char*)"jelly/blue/jelly_collision_4_blue_",5,64,64);
            m_pCollision[4] = new CAnim((char*)"jelly/blue/jelly_collision_5_blue_",5,64,64);
            m_pCollision[5] = new CAnim((char*)"jelly/blue/jelly_collision_6_blue_",5,64,64);
            m_pCollision[6] = new CAnim((char*)"jelly/blue/jelly_collision_7_blue_",5,64,64);
            m_pCollision[7] = new CAnim((char*)"jelly/blue/jelly_collision_8_blue_",5,64,64);
            
            m_pIdle = new CAnim((char*)"jelly/blue/jelly_jump_blue_",15,128,128);
            
        break;
            
        case JELLY_RED:
            m_pBody = new CSprite((char*)"jelly/red/body_red.png",0,0,65,65);
            m_pEyes = new CAnim((char*)"jelly/red/jelly_eyes_red_",9, 64, 64);
            
            m_pStretch = new CAnim((char*)"jelly/red/jelly_rozciaganie_red_",10, 128, 128);

            m_pLanding[0] = new CAnim((char*)"jelly/red/jelly_ladowanie_red_1_",9,128,128);
            m_pLanding[1] = new CAnim((char*)"jelly/red/jelly_ladowanie_red_2_",14,128,128);
            m_pLanding[2] = new CAnim((char*)"jelly/red/jelly_ladowanie_red_3_",19,128,128);
            
            m_pLandingEyes[0] = new CAnim((char*)"jelly/blue/jelly_ladowanie_eyes_1_",9,128,128);
            m_pLandingEyes[1] = new CAnim((char*)"jelly/blue/jelly_ladowanie_eyes_2_",14,128,128);
            m_pLandingEyes[2] = new CAnim((char*)"jelly/blue/jelly_ladowanie_eyes_3_",19,128,128);                        
            
            m_pCollision[0] = new CAnim((char*)"jelly/red/jelly_collision_1_red_",5,64,64);
            m_pCollision[1] = new CAnim((char*)"jelly/red/jelly_collision_2_red_",5,64,64);
            m_pCollision[2] = new CAnim((char*)"jelly/red/jelly_collision_3_red_",5,64,64);
            m_pCollision[3] = new CAnim((char*)"jelly/red/jelly_collision_4_red_",5,64,64);
            m_pCollision[4] = new CAnim((char*)"jelly/red/jelly_collision_5_red_",5,64,64);
            m_pCollision[5] = new CAnim((char*)"jelly/red/jelly_collision_6_red_",5,64,64);
            m_pCollision[6] = new CAnim((char*)"jelly/red/jelly_collision_7_red_",5,64,64);
            m_pCollision[7] = new CAnim((char*)"jelly/red/jelly_collision_8_red_",5,64,64);

            m_pIdle = new CAnim((char*)"jelly/red/jelly_jump_red_",15,128,128);
            
        break;
    }
    
    m_ulZValue = 1;     // na starcie wszystkie maja Z=1
    
    m_fX = fX; 
    m_fY = fY;
    
    m_fIncX = 0.0f;
    m_fIncY = 0.0f;
    
    m_fGravity = 0.5f;
    m_fGroundX = 0.2f;

    m_bPress = false; m_bRelease = false;
    
    m_iStartX = m_iStartY = m_iPressX = m_iPressY = m_iReleaseX = m_iReleaseY = 0;
    
    m_fScale = 1.0f;
        
    m_pBoundBox = new CBox(m_fX, m_fY, m_fX+64, m_fY+64);

    m_ucCollisionAnim = 255;    // brak kolizji
    
    m_ucIdleSpeed = 40 + (unsigned char)rand()%10;
    
    m_bActive = true;
    m_bLanding = false;
}

CJelly::~CJelly()
{
    if (m_bActive)
    {        
        SafeDelete(m_pBody);
        SafeDelete(m_pEyes);
        SafeDelete(m_pBoundBox);
        SafeDelete(m_pStretch);
        SafeDelete(m_pIdle);
        
        for (int i=0; i<3; i++) SafeDelete(m_pLanding[i]);
        for (int i=0; i<8; i++) SafeDelete(m_pCollision[i]);
        
        SafeDelete(m_pSndJump);
        SafeDelete(m_pSndLanding);
        
        m_bActive = false;
    }    
}

// bActive -> czy na tym zelku mozna wykonywac akcje

int CJelly::Render(CTouch *pTouch, unsigned long ulTimer, bool bActive)
{

    float fDistanceX, fDistanceY;    
    int iFrame, iReturn;
    
    iReturn =0;

    m_fX += m_fIncX;
    m_fY += m_fIncY; 

    if (m_fIncY>15.0f) m_fIncY = 15.0f;
    if (m_fIncY<-15.0f) m_fIncY = -15.0f;
    
    if (m_fIncX>15.0f) m_fIncX = 15.0f;
    if (m_fIncX<-15.0f) m_fIncX = -15.0f;    

    
    if ((m_fY+m_fIncY+m_fGravity>600)&&(m_fIncY>m_fGravity) && !m_bLanding)
    {
        m_cLandingType = 0;

        if (m_iStartY < 512) m_cLandingType=1;        
        if (m_iStartY < 256) m_cLandingType=2;
        
        m_bLanding = true;

        m_pSndLanding->Play();

        m_ulTimerEvent = ulTimer;   // zapamietaj czas zdarzenia        
    }
    
    m_fIncY += m_fGravity;
    
    if (m_fY>600) // ziemia
    {        
        m_fY=600;
        m_fIncY = 0.0f;
        
        if (m_fIncX>2.0f) m_fIncX = m_fIncX * 0.75f;
        if (m_fIncX<-2.0f) m_fIncX = m_fIncX * 0.75f;                   
    }

    // animacja ladowania ludzika
    
    if (m_bLanding)
    {
        iFrame = (int)(ulTimer-m_ulTimerEvent)/18;

          if (iFrame>m_pLanding[m_cLandingType]->iGetFrameCount())
          {
              m_bLanding = false;            
          }
          else 
          {
              m_pLanding[m_cLandingType]->Render(m_fX-32, m_fY, iFrame % m_pLanding[m_cLandingType]->iGetFrameCount());
              m_pLandingEyes[m_cLandingType]->Render(m_fX-32,m_fY,(ulTimer/90)%m_pLandingEyes[m_cLandingType]->iGetFrameCount());            
          }                                
         m_ucCollisionAnim = 255;
    }    
    
    if (!m_bPress && !m_bLanding && m_ucCollisionAnim==255)
    {    
        if (m_fY<550.0f && m_fIncX!= 0.0f)
        {
            m_pIdle->Render(m_fX-32, m_fY, (ulTimer/m_ucIdleSpeed) % m_pIdle->iGetFrameCount());
        }
        else
        {
            m_pBody->Render(m_fX, m_fY);
        }
        m_pEyes->SetRotation(0.0f);
        m_pEyes->Render(m_fX,m_fY,(ulTimer/90)%m_pEyes->iGetFrameCount());
    }

    if (m_ucCollisionAnim<255 )
    {
        iFrame = (int)(ulTimer-m_ulTimerEvent)/100;
        
        if (iFrame>9)
        {
            m_ucCollisionAnim = 255;            
        }
        
        if (iFrame>5)
        {
            iFrame = 10-iFrame;
        }
        
        if (m_ucCollisionAnim!=255)
        {
            m_pCollision[m_ucCollisionAnim]->Render(m_fX, m_fY, iFrame );
            m_pEyes->Render(m_fX,m_fY,(ulTimer/90)%m_pEyes->iGetFrameCount());                        
        }
        else 
        {
            m_pIdle->Render(m_fX-32, m_fY, (ulTimer/m_ucIdleSpeed) % m_pIdle->iGetFrameCount());
            
            m_pEyes->SetRotation(0.0f);
            m_pEyes->Render(m_fX,m_fY,(ulTimer/90)%m_pEyes->iGetFrameCount());            
        }        
    }

    
    if (bActive)
    {
        
        // sprawdzanie interakcji na tej postaci
        
        if (!m_bPress && !m_bLanding &&pTouch->isPressed() && 
            pTouch->iGetX() > m_fX && pTouch->iGetX() < m_fX+64 &&
            pTouch->iGetY() > m_fY && pTouch->iGetY() < m_fY+64)   // pierwszy raz nacisniety
        {
            m_bPress = true;
            m_iStartX = pTouch->iGetX();
            m_iStartY = pTouch->iGetY();              
  
            m_pBody->Render(m_fX, m_fY);
            
            m_pEyes->SetRotation(0.0f);
            m_pEyes->Render(m_fX,m_fY,(ulTimer/90)%m_pEyes->iGetFrameCount());   
            
            m_ucCollisionAnim = 255;
            
            iReturn = 1;        
        }

        if (m_bPress && !m_bLanding && pTouch->isPressed())    // juz wcisniety
        {
            m_iPressX = pTouch->iGetX();
            m_iPressY = pTouch->iGetY();               
        
            fDistanceX = (m_iStartX - m_iPressX)*0.05f;        
            fDistanceY = (m_iStartY - m_iPressY)*0.05f;        
        
            m_pStretch->SetRotation( ((m_iStartX - m_iPressX) * (m_iStartY - m_iPressY))*0.00314f);

            if (fDistanceY<0) fDistanceY *= -1;                
            if (fDistanceX<0) fDistanceX *= -1;        
        
            m_fScale = 1.0f + fDistanceX + fDistanceY;               
        
            if (m_fScale >10) m_fScale = 10;
        
        
            m_pStretch->Render(m_fX-32, m_fY, (int) m_fScale);

            m_pEyes->SetRotation( ((m_iStartX - m_iPressX) * (m_iStartY - m_iPressY))*0.00314f);
            m_pEyes->Render(m_fX,m_fY,(ulTimer/90)%m_pEyes->iGetFrameCount());
   
            m_ucCollisionAnim = 255;
        
            iReturn = 1;        
        }
    
        if (m_bPress && !m_bLanding && pTouch->isReleased())
        {
            m_fIncX = (m_iStartX - m_iPressX)/7;
            m_fIncY = (m_iStartY - m_iPressY)/7;                       
        
            m_fScale = 1.0f; // powrot do normalnego rozmiaru

            m_pIdle->Render(m_fX-32, m_fY, (ulTimer/m_ucIdleSpeed) % m_pIdle->iGetFrameCount());
        
            m_pEyes->SetRotation(0.0f);
            m_pEyes->Render(m_fX,m_fY,(ulTimer/90)%m_pEyes->iGetFrameCount());             
        
            m_bPress = false;
            
            m_pSndJump->Play();
            
            iReturn = 1;
        }
    }   // bActive
        
    // tarcie po ziemi
    
    if (m_fY==600 && m_fIncX>0)  // hamowanie w prawo
    {
        m_fIncX -= m_fGroundX;
        
        if (m_fIncX<0) m_fIncX = 0.0f;  // zeby go nie przesunelo w druga strone                
    }
    
    if (m_fY==600 && m_fIncX<0)  // hamowanie w lewo
    {
        m_fIncX +=m_fGroundX;
        if (m_fIncX>0) m_fIncX = 0.0f;  // zeby go nie przesunelo w druga strone
    }
    
    
    // sprawdzanie krawedzi
    
    if (m_fX>(1024-64) && m_fIncX>0)
    {
        m_fIncX = m_fIncX * -0.75f;

        if (!m_bLanding)
        {
            m_ucCollisionAnim = 7;
            m_ulTimerEvent = ulTimer;   // zapamietaj czas zdarzenia        
        }
    }
    
    if (m_fX<0 && m_fIncX<0)
    {
        m_fIncX = m_fIncX * -0.75f;    
        
        if (!m_bLanding)
        {
            m_ucCollisionAnim = 6;
            m_ulTimerEvent = ulTimer;   // zapamietaj czas zdarzenia        
        }
    }

    m_pBoundBox->Update(m_fX, m_fY, m_fX+64, m_fY+64);
    
    return iReturn;   // nie rob nic
}

bool CJelly::isActive(void)
{
    return m_bActive;
}

float CJelly::fGetForceX(void)
{
    return m_fIncX;    
}

float CJelly::fGetForceY(void)
{
    return m_fIncY;
}

void CJelly::SetForce(float fX, float fY)
{
    m_fIncX = fX;
    m_fIncY = fY;
}

CBox *CJelly::eGetBBox(void)
{
    return m_pBoundBox;
}

float CJelly::fGetX(void)
{
    return m_fX;
}

float CJelly::fGetY(void)
{
    return m_fY;
}

void CJelly::SetPosition(float fX, float fY)
{
    m_fX = fX; 
    m_fY = fY;
}

void CJelly::SetLanding(bool bLanding, unsigned long ulTimer)
{
    m_bLanding = bLanding;
    m_ulTimerEvent = ulTimer;
}

bool CJelly::isLanding(void)
{
    return m_bLanding;
}

void CJelly::SetZValue(unsigned long ulZValue)
{
    m_ulZValue = ulZValue; 
}

unsigned long CJelly::ulGetZValue(void)
{
    return m_ulZValue;
}

void CJelly::PlaySndLanding(void)
{
    m_pSndLanding->Play();
}