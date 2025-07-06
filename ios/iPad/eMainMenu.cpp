// main class

#include "eMainMenu.h"

// konstruktor, tutaj pakujemy najmniej jak tylko możliwe

eMainMenu::eMainMenu()
{
    m_bActive = false;
}

eMainMenu::~eMainMenu()
{
    if (m_bActive)
    {        
        Close();
        m_bActive = false;
    }    
}

void eMainMenu::Open(void)
{
    m_pBackground = new CSprite((char*)"mmenu_layer0.png",0,0,SCREEN_X,SCREEN_Y);
    m_pForeground = new CSprite((char*)"mmenu_layer5.png",0,0,SCREEN_X,SCREEN_Y);
    
    m_pButtonOptions = new CTouchButton(MMENU_OPTIONS_X, MMENU_OPTIONS_Y, MMENU_OPTIONS_SIZE_X, MMENU_OPTIONS_SIZE_Y, (char*)"button/mmenu_options_idle.png", (char*)"button/mmenu_options_onover.png", (char*)"button/mmenu_options_onclick.png");
    m_pButtonAbout = new CTouchButton(MMENU_ABOUT_X, MMENU_ABOUT_Y, MMENU_ABOUT_SIZE_X, MMENU_ABOUT_SIZE_Y,(char*) "button/mmenu_about_idle.png",(char*) "button/mmenu_about_onover.png",(char*) "button/mmenu_about_onclick.png");
    m_pButtonClose = new CTouchButton(MMENU_CLOSE_X, MMENU_CLOSE_Y, MMENU_CLOSE_SIZE_X, MMENU_CLOSE_SIZE_Y,(char*) "button/mmenu_close_idle.png",(char*) "button/mmenu_close_onover.png",(char*) "button/mmenu_close_onclick.png");
    m_pButtonPlay = new CTouchButton(MMENU_PLAY_X, MMENU_PLAY_Y, MMENU_PLAY_SIZE_X, MMENU_PLAY_SIZE_Y,(char*) "button/mmenu_play_idle.png",(char*) "button/mmenu_play_onover.png",(char*) "button/mmenu_play_onclick.png");
    
    m_pButtonTrophy = new CTouchButton(MMENU_TROPHY_X, MMENU_TROPHY_Y, MMENU_TROPHY_SIZE_X, MMENU_TROPHY_SIZE_Y,(char*) "button/mmenu_trophy_idle.png",(char*) "button/mmenu_trophy_onover.png",(char*) "button/mmenu_trophy_onclick.png");
    
    m_pButtonProfile = new CTouchButton(MMENU_PROFILE_X, MMENU_PROFILE_Y, MMENU_PROFILE_SIZE_X, MMENU_PROFILE_SIZE_Y, 
                                        0, 0, MMENU_PROFILE_SIZE_X, MMENU_PROFILE_SIZE_Y,
                                        0, MMENU_PROFILE_INC_Y, MMENU_PROFILE_SIZE_X, MMENU_PROFILE_SIZE_Y+MMENU_PROFILE_INC_Y,
                                        0, MMENU_PROFILE_INC_Y+MMENU_PROFILE_INC_Y, MMENU_PROFILE_SIZE_X, MMENU_PROFILE_INC_Y+MMENU_PROFILE_INC_Y+MMENU_PROFILE_SIZE_Y,
                                        (char*) "button/mmenu_profile.png");
    
    m_pWindmillBase = new CSprite((char*) "mmenu_windmill_base.png",0,0,MMENU_WINDMILL_BASE_SIZE_X,MMENU_WINDMILL_BASE_SIZE_Y);
    m_pWindmillBase->SetPosition((float)MMENU_WINDMILL_BASE_X, (float)MMENU_WINDMILL_BASE_Y);
    
    m_pWindmillWings = new CSprite((char*) "mmenu_windmill_wings.png", 0, 0, MMENU_WINDMILL_WINGS_SIZE_X, MMENU_WINDMILL_WINGS_SIZE_Y);
    m_pWindmillWings->SetPosition((float)MMENU_WINDMILL_WINGS_X, (float)MMENU_WINDMILL_WINGS_Y);
    
    m_pClouds[0] = new CSprite((char*) "mmenu_cloud1.png",0,0,256,256); m_pClouds[0]->SetPosition(100, 100);
    m_pClouds[1] = new CSprite((char*) "mmenu_cloud2.png",0,0,64,64); m_pClouds[1]->SetPosition(200,200);
    m_pClouds[2] = new CSprite((char*) "mmenu_cloud3.png",0,0,128,128); m_pClouds[2]->SetPosition(300,300);
    m_pClouds[3] = new CSprite((char*) "mmenu_cloud4.png",0,0,64,64); m_pClouds[3]->SetPosition(400,400);
    
    m_pGrass = new CAnim((char*)"menu_grass1_",19, 64, 64);
    m_pGrass2 = new CAnim((char*)"menu_grass2_",19, 64, 64);
    m_pGrassEyes = new CAnim((char*)"menu_grass3_",39, 64, 64);
    
    m_pNietoperek = new CAnim((char*)"nietoperek",19, 64, 64);
    
    m_pSingleLine = new CAnim((char*)"single_line_up_",19, 64, 64);
    
    m_pMusic = new KMusic();
    m_pMusic->setVolume(50);
	m_pMusic->playMusic(KMiscTools::makeFilePath("mmenu.mp3"));
    
    m_bActive = true;
}

void eMainMenu::Close(void)
{

    m_pMusic->stopMusic();
    SafeDelete(m_pMusic);
    
    SafeDelete(m_pBackground);
    SafeDelete(m_pForeground);
    SafeDelete(m_pButtonOptions);
    SafeDelete(m_pButtonAbout);
    SafeDelete(m_pButtonClose);
    SafeDelete(m_pButtonPlay);   
    SafeDelete(m_pButtonTrophy);
    
    SafeDelete(m_pWindmillBase);
    SafeDelete(m_pWindmillWings);
    
    SafeDelete(m_pButtonProfile);
    
    SafeDelete(m_pGrass);
    SafeDelete(m_pGrass2);
    SafeDelete(m_pGrassEyes);
    
    SafeDelete(m_pNietoperek);
    
    SafeDelete(m_pSingleLine);
    
    for (int i=0; i<4; i++) SafeDelete(m_pClouds[i]);
    
    m_bActive = false;
    
}

int eMainMenu::Render(CTouch *pTouch, unsigned long ulTimer)
{
    int iReturn;

    iReturn = 0;    
    
    m_pBackground->Render();

    for (int i=0; i<4; i++)
    {
        int j= (ulTimer/(10+(10*i)));
        int k= SCREEN_X*1.5f;
        j%=k;

        m_pClouds[i]->SetPositionX(0-(SCREEN_X/4) + j);
        m_pClouds[i]->Render();
    }   
    
    m_pForeground->Render();

    m_pWindmillBase->Render();

    m_pWindmillWings->SetRotation((float)((ulTimer/10)%360));
    m_pWindmillWings->Render();
    
    m_pGrass->Render(240,588,(ulTimer/50)%19);
    m_pGrass2->Render(550,578,(ulTimer/50)%19);
    m_pGrassEyes->Render(920,570,(ulTimer/25)%39);
    
    m_pNietoperek->Render(110,90,(ulTimer/30)%19);
    
    m_pSingleLine->Render(800,0,(ulTimer/60)%19);
    
    m_pButtonOptions->Render(pTouch);
    m_pButtonAbout->Render(pTouch);
    m_pButtonClose->Render(pTouch);
    
    if (m_pButtonPlay->Render(pTouch)==2) 
    {
       iReturn = 10;
    }
    
    m_pButtonTrophy->Render(pTouch);
    
    m_pButtonProfile->Render(pTouch);
    
    
    return iReturn;   // nie rob nic
}

bool eMainMenu::isActive(void)
{
    return m_bActive;
}

