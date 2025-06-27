// main class

#include "eIngame.h"

// konstruktor, tutaj pakujemy najmniej jak tylko możliwe

eIngame::eIngame()
{
    m_bActive = false;
//    m_bCollision = false;
    m_uiCurrentLevel = 1;    
    m_iPressedID = 255; // 255 = zaden wcisniety
    m_ulMaxZValue = 1; 
}

eIngame::~eIngame()
{
    if (m_bActive)
    {        
        Close();
        m_bActive = false;
    }    
}

void eIngame::SetLevel(unsigned int uiLevel)
{
    m_uiCurrentLevel = uiLevel;
}

unsigned int eIngame::uiGetLevel(void)
{
    return m_uiCurrentLevel;
}

void eIngame::Open()
{
    m_pButtonClose = new CTouchButton(MMENU_CLOSE_X, MMENU_CLOSE_Y, MMENU_CLOSE_SIZE_X, MMENU_CLOSE_SIZE_Y,(char*) "button/mmenu_close_idle.png",(char*) "button/mmenu_close_onover.png",(char*) "button/mmenu_close_onclick.png");

/*    CParticle2DManager(char cSpriteFilename[], unsigned long ulCount, 
                       float fX1, float fY1, float fX2, float fY2, 
                       float fMinIncX, float fMinIncY, float fMaxIncX, float fMaxIncY,
                       float fAlpha, float fMinIncAlpha, float fMaxIncAlpha,
                       float fAngle, float fMinIncAngle, float fMaxIncAngle,
                       unsigned long ulMinLifeTime, unsigned long ulMaxLifeTime);
*/
    m_pParticleManager = new CParticle2DManager((char*)"particle/leaf.png", 50, 
                                                0,0,1024,768,
                                                0.01f,0.01f,0.3f,0.3f,
                                                0.0f, 0.001f,0.005f,
                                                0.5f, -5.0f,5.0f,
                                                1000,10000);

    m_pGarnek = new CSprite((char*)"garnek.png",0,0,256,256);    
  
    m_pBat = new CAnim((char*)"anim/bat_",7, 64, 64);
    m_iBatX = 1100;
    
    switch (m_uiCurrentLevel)
    {
            
        // level 1
            
        case 1:
            m_pBackground = new CSprite((char*)"level/001/background.png",0,0,SCREEN_X, SCREEN_Y);
            m_pForeground = new CSprite((char*)"level/001/foreground.png",0,0,SCREEN_X, SCREEN_Y);
            
            m_pDotYellow = new CSprite((char*)"dot_yellow.png",0,0,16,16);
            
            m_pJelly[0] = new CJelly(JELLY_BLUE,100,400);
            m_pJelly[1] = new CJelly(JELLY_BLUE,200,400);
            m_pJelly[2] = new CJelly(JELLY_RED,300,400);
            m_pJelly[3] = new CJelly(JELLY_RED,400,400);
            
            
            m_pPlatform[0] = new CPlatform((char*)"level/001/platform1.png",100,300,120,20);
            m_pPlatform[1] = new CPlatform((char*)"level/001/platform2.png",400,200,120,20);
            m_pPlatform[2] = new CPlatform((char*)"level/001/platform3.png",600,500,120,20);
            m_pPlatform[3] = new CPlatform((char*)"level/001/platform3.png",200,500,120,20);    
            
            m_pWindmillBase = new CSprite((char*) "mmenu_windmill_base.png",0,0,MMENU_WINDMILL_BASE_SIZE_X,MMENU_WINDMILL_BASE_SIZE_Y);
            m_pWindmillBase->SetPosition((float)MMENU_WINDMILL_BASE_X, (float)MMENU_WINDMILL_BASE_Y);
            
            m_pWindmillWings = new CSprite((char*) "mmenu_windmill_wings.png", 0, 0, MMENU_WINDMILL_WINGS_SIZE_X, MMENU_WINDMILL_WINGS_SIZE_Y);
            m_pWindmillWings->SetPosition((float)MMENU_WINDMILL_WINGS_X, (float)MMENU_WINDMILL_WINGS_Y);
            
            m_pClouds[0] = new CSprite((char*) "level/001/cloud_1.png",0,0,256,256); m_pClouds[0]->SetPosition(100, 100);
            m_pClouds[1] = new CSprite((char*) "level/001/cloud_2.png",0,0,64,64); m_pClouds[1]->SetPosition(200,200);
            m_pClouds[2] = new CSprite((char*) "level/001/cloud_3.png",0,0,128,128); m_pClouds[2]->SetPosition(300,300);
            m_pClouds[3] = new CSprite((char*) "level/001/cloud_4.png",0,0,64,64); m_pClouds[3]->SetPosition(400,400);

            m_pGrass = new CAnim((char*)"level/001/grass1_",19, 64, 64);
            m_pGrass2 = new CAnim((char*)"level/001/grass2_",19, 64, 64);
            m_pGrassEyes = new CAnim((char*)"level/001/grass3_",39, 64, 64);                
            
        break;
        
        // level 2
            
        case 2:
            m_pBackground = new CSprite((char*)"level/002/background.png",0,0,SCREEN_X, SCREEN_Y);
            m_pForeground = new CSprite((char*)"level/002/foreground.png",0,0,SCREEN_X, SCREEN_Y);
            
            m_pDotYellow = new CSprite((char*)"dot_yellow.png",0,0,16,16);
            
            m_pJelly[0] = new CJelly(JELLY_BLUE,100,100);
            m_pJelly[1] = new CJelly(JELLY_RED,200,200);
            m_pJelly[2] = new CJelly(JELLY_BLUE,300,300);
            m_pJelly[3] = new CJelly(JELLY_RED,400,400);
            
            
            m_pPlatform[0] = new CPlatform((char*)"level/002/platform1.png",300,300,120,20);
            m_pPlatform[1] = new CPlatform((char*)"level/002/platform2.png",200,200,120,20);
            m_pPlatform[2] = new CPlatform((char*)"level/002/platform3.png",400,500,120,20);
            m_pPlatform[3] = new CPlatform((char*)"level/002/platform3.png",100,500,120,20);            

            m_pWindmillBase = new CSprite((char*) "mmenu_windmill_base.png",0,0,MMENU_WINDMILL_BASE_SIZE_X,MMENU_WINDMILL_BASE_SIZE_Y);
            m_pWindmillBase->SetPosition((float)MMENU_WINDMILL_BASE_X, (float)MMENU_WINDMILL_BASE_Y);
            
            m_pWindmillWings = new CSprite((char*) "mmenu_windmill_wings.png", 0, 0, MMENU_WINDMILL_WINGS_SIZE_X, MMENU_WINDMILL_WINGS_SIZE_Y);
            m_pWindmillWings->SetPosition((float)MMENU_WINDMILL_WINGS_X, (float)MMENU_WINDMILL_WINGS_Y);
            
            m_pClouds[0] = new CSprite((char*) "level/002/cloud_1.png",0,0,256,256); m_pClouds[0]->SetPosition(100, 100);
            m_pClouds[1] = new CSprite((char*) "level/002/cloud_2.png",0,0,64,64); m_pClouds[1]->SetPosition(200,200);
            m_pClouds[2] = new CSprite((char*) "level/002/cloud_3.png",0,0,128,128); m_pClouds[2]->SetPosition(300,300);
            m_pClouds[3] = new CSprite((char*) "level/002/cloud_4.png",0,0,64,64); m_pClouds[3]->SetPosition(400,400);

            m_pGrass = new CAnim((char*)"level/002/grass1_",19, 64, 64);
            m_pGrass2 = new CAnim((char*)"level/002/grass2_",19, 64, 64);
            m_pGrassEyes = new CAnim((char*)"level/002/grass3_",39, 64, 64);                         
            
        break;

        case 3:
            m_pBackground = new CSprite((char*)"level/003/background.png",0,0,SCREEN_X, SCREEN_Y);
            m_pForeground = new CSprite((char*)"level/003/foreground.png",0,0,SCREEN_X, SCREEN_Y);
            
            m_pDotYellow = new CSprite((char*)"dot_yellow.png",0,0,16,16);
            
            m_pJelly[0] = new CJelly(JELLY_BLUE,100,400);
            m_pJelly[1] = new CJelly(JELLY_BLUE,200,300);
            m_pJelly[2] = new CJelly(JELLY_RED,300,200);
            m_pJelly[3] = new CJelly(JELLY_RED,400,100);
            
            
            m_pPlatform[0] = new CPlatform((char*)"level/003/platform1.png",800,400,120,20);
            m_pPlatform[1] = new CPlatform((char*)"level/003/platform2.png",200,200,120,20);
            m_pPlatform[2] = new CPlatform((char*)"level/003/platform3.png",400,500,120,20);
            m_pPlatform[3] = new CPlatform((char*)"level/003/platform3.png",100,500,120,20);            
            
            m_pWindmillBase = new CSprite((char*) "mmenu_windmill_base.png",0,0,MMENU_WINDMILL_BASE_SIZE_X,MMENU_WINDMILL_BASE_SIZE_Y);
            m_pWindmillBase->SetPosition((float)MMENU_WINDMILL_BASE_X, (float)MMENU_WINDMILL_BASE_Y);
            
            m_pWindmillWings = new CSprite((char*) "mmenu_windmill_wings.png", 0, 0, MMENU_WINDMILL_WINGS_SIZE_X, MMENU_WINDMILL_WINGS_SIZE_Y);
            m_pWindmillWings->SetPosition((float)MMENU_WINDMILL_WINGS_X, (float)MMENU_WINDMILL_WINGS_Y);
            
            m_pClouds[0] = new CSprite((char*) "level/003/cloud_1.png",0,0,256,256); m_pClouds[0]->SetPosition(100, 100);
            m_pClouds[1] = new CSprite((char*) "level/003/cloud_2.png",0,0,64,64); m_pClouds[1]->SetPosition(200,200);
            m_pClouds[2] = new CSprite((char*) "level/003/cloud_3.png",0,0,128,128); m_pClouds[2]->SetPosition(300,300);
            m_pClouds[3] = new CSprite((char*) "level/003/cloud_4.png",0,0,64,64); m_pClouds[3]->SetPosition(400,400);            

            m_pGrass = new CAnim((char*)"level/003/grass1_",19, 64, 64);
            m_pGrass2 = new CAnim((char*)"level/003/grass2_",19, 64, 64);
            m_pGrassEyes = new CAnim((char*)"level/003/grass3_",39, 64, 64);          // menu_grass3_      
            
            
            break;            
            
    }            
    
    m_pGarnek->SetPosition(600, 200);
    m_pGarnekL = new CBox(600,200,620,350); // lewa sciana        
    m_pGarnekP = new CBox(740,200,760,350); // prawa sciana    
    m_pGarnekD = new CBox(610,320,740,340); // dolna sciana
    
    m_pMusic = new KMusic();
    m_pMusic->setVolume(50);
	m_pMusic->playMusic(KMiscTools::makeFilePath("ingame.mp3"));

    m_bActive = true;

}

void eIngame::Close(void)
{
    SafeDelete(m_pButtonClose);
    
    SafeDelete(m_pBackground);
    SafeDelete(m_pForeground);
    
    SafeDelete(m_pDotYellow);
    
    SafeDelete(m_pGarnek);
    
    for (int i=0; i<4; i++) SafeDelete(m_pJelly[i]);
    
    m_pMusic->stopMusic();
    SafeDelete(m_pMusic);
    

    SafeDelete(m_pWindmillBase);
    SafeDelete(m_pWindmillWings);  
    
    SafeDelete(m_pGrass);
    SafeDelete(m_pGrass2);
    SafeDelete(m_pGrassEyes);    
    
    for (int i=0; i<4; i++) 
    {
        SafeDelete(m_pClouds[i]);    
        SafeDelete(m_pPlatform[i]);
    }
    
    SafeDelete(m_pParticleManager);
    
    SafeDelete(m_pGarnekL);
    SafeDelete(m_pGarnekP);
    SafeDelete(m_pGarnekD);
    
    SafeDelete(m_pBat);
    
    m_bActive = false;
    
}


int eIngame::Render(CTouch *pTouch, unsigned long ulTimer)
{
    bool bPressed;
    
    m_ulTimer = ulTimer;
    
    m_pBackground->Render();

    m_pBat->SetPosition((float)m_iBatX, 200.0f);
    m_pBat->Render((ulTimer/50)%m_pBat->iGetFrameCount());    
    
    if (m_iBatX-- < -100) m_iBatX=1100;        

    
    // chmurki
    
    for (int i=0; i<4; i++)
    {
        int j= (ulTimer/(10+(10*i)));
        int k= SCREEN_X*1.5f;
        j%=k;
        
        m_pClouds[i]->SetPositionX(0-(SCREEN_X/4) + j);
        m_pClouds[i]->Render();
    }   

    // 2-gi plan
    
    m_pForeground->Render();

    m_pWindmillBase->Render();
    
    m_pWindmillWings->SetRotation((float)((ulTimer/10)%360));
    m_pWindmillWings->Render();
        
    m_pGrass->Render(240,588,(ulTimer/50)%19);
    m_pGrass2->Render(550,588,(ulTimer/50)%19);
    m_pGrassEyes->Render(920,580,(ulTimer/100)%39);    

    // particle
    
    m_pParticleManager->Render(ulTimer);             
    
    // platformy itp
    
    for (long lZValue=0; lZValue<=m_ulMaxZValue; lZValue++)
    {
        for (int iJelly=0; iJelly<4; iJelly++)
        {
            if (m_pJelly[iJelly]->ulGetZValue()==lZValue)
            {
                for (int i=0; i<4; i++)
                {
                    m_pPlatform[i]->Render(pTouch,ulTimer);
                    CheckCollision(m_pJelly[iJelly], m_pPlatform[i]);
                }
    
                CheckCollisionH(m_pJelly[iJelly],m_pGarnekL);
                CheckCollisionH(m_pJelly[iJelly],m_pGarnekP);
                CheckCollisionV(m_pJelly[iJelly],m_pGarnekD);
        
                if (m_iPressedID == iJelly)
                {
                    if (!m_pJelly[iJelly]->Render(pTouch, ulTimer, true))
                    {
                        bPressed = false;
                        m_iPressedID = 255;                 
                    }            
                }
        
                if (m_iPressedID != 255 && m_iPressedID!=iJelly)
                {
                    m_pJelly[iJelly]->Render(pTouch, ulTimer, false);
                }
        
                if (m_iPressedID == 255)
                {
                    if (m_pJelly[iJelly]->Render(pTouch,ulTimer,true))
                    {
                        bPressed = true; 
                        m_iPressedID = iJelly;  // zapamietaj ID
                        UpdateZValue(iJelly);   // wyciagnij go na wierzch
                    }
                }
            } 
        } // iJelly
    } // lZValue
    
    m_pGarnek->Render();   
    
    if (m_pButtonClose->Render(pTouch)==2) 
    {
        return 255;
    }           
    
    return 0;   // nie rob nic
}

// sprawdz czy modul jest aktywny

bool eIngame::isActive(void)
{
    return m_bActive;
}

// sprawdzanie kolizji zelkow z platformami

void eIngame::CheckCollision(CJelly *pJelly, CPlatform *pPlatform)
{

    // kolizja gora jelek dol platforma
    
    if (pJelly->eGetBBox()->m_fy1 < pPlatform->eGetBBox()->m_fy2 &&
        pJelly->eGetBBox()->m_fy1 > pPlatform->eGetBBox()->m_fy1 &&
        pJelly->eGetBBox()->m_fx1 < pPlatform->eGetBBox()->m_fx2 &&
        pJelly->eGetBBox()->m_fx2 > pPlatform->eGetBBox()->m_fx1 && 
        pJelly->fGetForceY() < 0.0f )
    {
        pJelly->SetForce(pJelly->fGetForceX(), pJelly->fGetForceY()* - 0.75f);
        pJelly->SetPosition(pJelly->fGetX(), pPlatform->eGetBBox()->m_fy2);
        return;
    }
    
    // kolizja dol jelek gora platforma
    
    if (pJelly->eGetBBox()->m_fy2 >= pPlatform->eGetBBox()->m_fy1 &&
        pJelly->eGetBBox()->m_fy2 <= pPlatform->eGetBBox()->m_fy2 &&
        pJelly->eGetBBox()->m_fx1 <= pPlatform->eGetBBox()->m_fx2 &&
        pJelly->eGetBBox()->m_fx2 >= pPlatform->eGetBBox()->m_fx1 && 
        pJelly->fGetForceY() > 0.0f )
    {
        pJelly->SetForce(pJelly->fGetForceX(), 0.0f);        
        pJelly->SetPosition(pJelly->fGetX(), pPlatform->eGetBBox()->m_fy1 - (pJelly->eGetBBox()->m_fy2 - pJelly->eGetBBox()->m_fy1));        

        if (pJelly->fGetForceX()>2.0f) pJelly->SetForce(pJelly->fGetForceX()*0.25f,pJelly->fGetForceY());
        if (pJelly->fGetForceX()<-2.0f) pJelly->SetForce(pJelly->fGetForceX()*0.25f,pJelly->fGetForceY());
        
        return;
    }
    
    // kolizja prawa jelek lewa platforma
    
    if (pJelly->eGetBBox()->m_fx2 > pPlatform->eGetBBox()->m_fx1 &&
        pJelly->eGetBBox()->m_fx2 < pPlatform->eGetBBox()->m_fx2 &&
        pJelly->eGetBBox()->m_fy1 < pPlatform->eGetBBox()->m_fy1 &&
        pJelly->eGetBBox()->m_fy2 > pPlatform->eGetBBox()->m_fy2 &&
        pJelly->fGetForceX() > 0.0f )
    {
        pJelly->SetForce(pJelly->fGetForceX() * -0.75f, pJelly->fGetForceY());
        return;
    }
        
    if (pJelly->eGetBBox()->m_fx2 > pPlatform->eGetBBox()->m_fx1 &&
        pJelly->eGetBBox()->m_fx2 < pPlatform->eGetBBox()->m_fx2 &&
        pJelly->eGetBBox()->m_fy1 > pPlatform->eGetBBox()->m_fy1 &&
        pJelly->eGetBBox()->m_fy1 < pPlatform->eGetBBox()->m_fy2 &&
        pJelly->fGetForceX() > 0.0f )
    {
        pJelly->SetForce(pJelly->fGetForceX() * -0.75f, pJelly->fGetForceY());
        return;
    }
    
    if (pJelly->eGetBBox()->m_fx2 > pPlatform->eGetBBox()->m_fx1 &&
        pJelly->eGetBBox()->m_fx2 < pPlatform->eGetBBox()->m_fx2 &&
        pJelly->eGetBBox()->m_fy2 > pPlatform->eGetBBox()->m_fy1 &&
        pJelly->eGetBBox()->m_fy2 < pPlatform->eGetBBox()->m_fy2 &&
        pJelly->fGetForceX() > 0.0f )
    {
        pJelly->SetForce(pJelly->fGetForceX() * -0.75f, pJelly->fGetForceY());
        return;
    }
    
    // kolizja lewa jelek prawa platforma 
    
    if (pJelly->eGetBBox()->m_fx1 < pPlatform->eGetBBox()->m_fx2 &&
        pJelly->eGetBBox()->m_fx1 > pPlatform->eGetBBox()->m_fx1 &&
        pJelly->eGetBBox()->m_fy1 < pPlatform->eGetBBox()->m_fy1 &&
        pJelly->eGetBBox()->m_fy2 > pPlatform->eGetBBox()->m_fy2 &&
        pJelly->fGetForceX() < 0.0f )
    {
        pJelly->SetForce(pJelly->fGetForceX() * -0.75f, pJelly->fGetForceY());
        return;
    }
    
    if (pJelly->eGetBBox()->m_fx1 < pPlatform->eGetBBox()->m_fx2 &&
        pJelly->eGetBBox()->m_fx1 > pPlatform->eGetBBox()->m_fx1 &&
        pJelly->eGetBBox()->m_fy1 > pPlatform->eGetBBox()->m_fy1 &&
        pJelly->eGetBBox()->m_fy1 < pPlatform->eGetBBox()->m_fy2 &&
        pJelly->fGetForceX() < 0.0f )
    {
        pJelly->SetForce(pJelly->fGetForceX() * -0.75f, pJelly->fGetForceY());
        return;
    }
    
    if (pJelly->eGetBBox()->m_fx1 < pPlatform->eGetBBox()->m_fx2 &&
        pJelly->eGetBBox()->m_fx1 > pPlatform->eGetBBox()->m_fx1 &&
        pJelly->eGetBBox()->m_fy2 > pPlatform->eGetBBox()->m_fy1 &&
        pJelly->eGetBBox()->m_fy2 < pPlatform->eGetBBox()->m_fy2 &&
        pJelly->fGetForceX() < 0.0f )
    {
        pJelly->SetForce(pJelly->fGetForceX() * -0.75f, pJelly->fGetForceY());
        return;
    }              
}

void eIngame::CheckCollisionH(CJelly *pJelly, CBox *BBox)
{
          
    // kolizja prawa jelek lewa platforma
    
    if (pJelly->eGetBBox()->m_fx2 > BBox->m_fx1 &&
        pJelly->eGetBBox()->m_fx1 < BBox->m_fx2 &&     
        pJelly->eGetBBox()->m_fy1 <= BBox->m_fy1 &&
        pJelly->eGetBBox()->m_fy2 >= BBox->m_fy2 &&
        pJelly->fGetForceX() > 0.0f )
    {
        pJelly->SetForce(pJelly->fGetForceX() * -0.75f, pJelly->fGetForceY());
        return;
    }
    
    if (pJelly->eGetBBox()->m_fx2 > BBox->m_fx1 &&
        pJelly->eGetBBox()->m_fx1 < BBox->m_fx2 &&         
        pJelly->eGetBBox()->m_fy1 >= BBox->m_fy1 &&
        pJelly->eGetBBox()->m_fy1 <= BBox->m_fy2 &&
        pJelly->fGetForceX() > 0.0f )
    {
        pJelly->SetForce(pJelly->fGetForceX() * -0.75f, pJelly->fGetForceY());
        return;
    }
    
    if (pJelly->eGetBBox()->m_fx2 > BBox->m_fx1 &&
        pJelly->eGetBBox()->m_fx1 < BBox->m_fx2 &&          
        pJelly->eGetBBox()->m_fy2 >= BBox->m_fy1 &&
        pJelly->eGetBBox()->m_fy2 <= BBox->m_fy2 &&
        pJelly->fGetForceX() > 0.0f )
    {
        pJelly->SetForce(pJelly->fGetForceX() * -0.75f, pJelly->fGetForceY());
        return;
    }

    if (pJelly->eGetBBox()->m_fx2 > BBox->m_fx1 &&
        pJelly->eGetBBox()->m_fx1 < BBox->m_fx2 &&     
        pJelly->eGetBBox()->m_fy1 >= BBox->m_fy1 &&
        pJelly->eGetBBox()->m_fy2 <= BBox->m_fy2 &&
        pJelly->fGetForceX() > 0.0f )
    {
        pJelly->SetForce(pJelly->fGetForceX() * -0.75f, pJelly->fGetForceY());
        return;
    }    
    
    // kolizja lewa jelek prawa platforma 
    
    if (pJelly->eGetBBox()->m_fx1 < BBox->m_fx2 &&
        pJelly->eGetBBox()->m_fx1 > BBox->m_fx1 &&
        pJelly->eGetBBox()->m_fy1 <= BBox->m_fy1 &&
        pJelly->eGetBBox()->m_fy2 >= BBox->m_fy2 &&
        pJelly->fGetForceX() < 0.0f )
    {
        pJelly->SetForce(pJelly->fGetForceX() * -0.75f, pJelly->fGetForceY());
        return;
    }
    
    if (pJelly->eGetBBox()->m_fx1 < BBox->m_fx2 &&
        pJelly->eGetBBox()->m_fx1 > BBox->m_fx1 &&
        pJelly->eGetBBox()->m_fy1 >= BBox->m_fy1 &&
        pJelly->eGetBBox()->m_fy1 <= BBox->m_fy2 &&
        pJelly->fGetForceX() < 0.0f )
    {
        pJelly->SetForce(pJelly->fGetForceX() * -0.75f, pJelly->fGetForceY());
        return;
    }
    
    if (pJelly->eGetBBox()->m_fx1 < BBox->m_fx2 &&
        pJelly->eGetBBox()->m_fx1 > BBox->m_fx1 &&
        pJelly->eGetBBox()->m_fy2 >= BBox->m_fy1 &&
        pJelly->eGetBBox()->m_fy2 <= BBox->m_fy2 &&
        pJelly->fGetForceX() < 0.0f )
    {
        pJelly->SetForce(pJelly->fGetForceX() * -0.75f, pJelly->fGetForceY());
        return;
    }              

    if (pJelly->eGetBBox()->m_fx1 < BBox->m_fx2 &&
        pJelly->eGetBBox()->m_fx1 > BBox->m_fx1 &&
        pJelly->eGetBBox()->m_fy1 >= BBox->m_fy1 &&
        pJelly->eGetBBox()->m_fy2 <= BBox->m_fy2 &&
        pJelly->fGetForceX() < 0.0f )
    {
        pJelly->SetForce(pJelly->fGetForceX() * -0.75f, pJelly->fGetForceY());
        return;
    }              

}

void eIngame::CheckCollisionV(CJelly *pJelly, CBox *BBox)
{
    
    // kolizja gora jelek dol platforma
    
    if (pJelly->eGetBBox()->m_fy1 < BBox->m_fy2 &&
        pJelly->eGetBBox()->m_fy1 > BBox->m_fy1 &&
        pJelly->eGetBBox()->m_fx1 < BBox->m_fx2 &&
        pJelly->eGetBBox()->m_fx2 > BBox->m_fx1 && 
        pJelly->fGetForceY() < 0.0f )
    {
        pJelly->SetForce(pJelly->fGetForceX(), pJelly->fGetForceY()* - 0.75f);
        pJelly->SetPosition(pJelly->fGetX(), BBox->m_fy2+0.1f);
        return;
    }
    
    // kolizja dol jelek gora platforma
    
    if (pJelly->eGetBBox()->m_fy2 > BBox->m_fy1 &&
        pJelly->eGetBBox()->m_fy2 < BBox->m_fy2 &&
        pJelly->eGetBBox()->m_fx1 < BBox->m_fx2 &&
        pJelly->eGetBBox()->m_fx2 > BBox->m_fx1 && 
        pJelly->fGetForceY() > 0.0f )
    {
        pJelly->SetForce(0.0f,0.0f);      
        return;
    }

}

// jelek z identyfikatorem iJellyID ma miec max Z

void eIngame::UpdateZValue(unsigned int iJellyID)
{
    unsigned long ulMaxZ; 
    
    ulMaxZ = 0; 
    
    for (int i=0; i<4; i++)
    {
        if (m_pJelly[i]->ulGetZValue() > ulMaxZ) ulMaxZ = m_pJelly[i]->ulGetZValue();            
    }
    
    m_ulMaxZValue = ulMaxZ+1;
    
    m_pJelly[iJellyID]->SetZValue(m_ulMaxZValue);
    
}

