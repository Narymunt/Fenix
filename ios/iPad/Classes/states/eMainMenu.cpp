// main class

#include "eMainMenu.h"

// konstruktor, tutaj pakujemy najmniej jak tylko możliwe

eMainMenu::eMainMenu() :
_isFirstRun(true)
{
	CProfile *pProfile;
    CHighScore *pHighScore;
    
	// ustaw znacznik, ze dane nie sa jeszcze wczytane
	_isActive = false;
    
	_pTitle = NULL;
    
	_pBackground = NULL;
	_pWall_L = _pWall_R = NULL;
	_ulTimerStart = 0;
	
	_pBlack = NULL;
	_pWhite = NULL;
    
	_pArrowR = NULL;
    
	_pButtonStart = NULL;
	_pButtonOptions = NULL;
	_pButtonTrophy = NULL;
	_pButtonHelp = NULL;
	_pButtonSupport = NULL;
    
	_pButtonSwitch = NULL;
	_pButtonYes = NULL;
	_pButtonNo = NULL;
	_pButtonEdit = NULL;
    
	_pProfileEdit = NULL;
	_pProfileDelete = NULL;
    
	_bPrevBack = false;		// nie bylo backspace
    
	_pFont = NULL;
    
	pProfile = new CProfile();
    
    if (pProfile->bSetup())             // to jest pierwsze uruchomienie aplikacji
    {
        pHighScore = new CHighScore();
        pHighScore->Setup();
        delete pHighScore;
    }
        
	
    pProfile->bLoad();
    
	_ucCurrentProfile = pProfile->ucCurrentProfile();
    
	for (int i=0; i<8; i++)
	{
		pProfile->ucCurrentProfile(i);
		strcpy(_pUserName[i],pProfile->pGetName());
	}
    
	delete pProfile;
    
	_isProfileView = false;		// czy przegladamy profile? ustawione celowo, zeby pokazywal 100 wczytania
	_isProfileEdit = false;		// czy wpisujemy dane?
	_isProfileDelete = false;
    
	_ucLanguage = 0;
    
	for (int i=0; i<18; i++)
		_cEditName[i] = 0;
    
	_cIndex = 0;
    
	_pFlag = NULL;
    
	_pParticleManager = NULL;
    
	_pFXManager = NULL;
    
	_pMobileKeyboard = new CMobileKeyboard(0);
    
	_isMouseLock = true;
}

eMainMenu::~eMainMenu()
{
	Close();
    
	SafeDelete(_pFont);
    
	SafeDelete(_pBackground);
	SafeDelete(_pBlack);
	SafeDelete(_pWhite);
	SafeDelete(_pTitle);
	
	SafeDelete(_pArrowR);
    
	SafeDelete(_pWall_L);
	SafeDelete(_pWall_R);
    
	SafeDelete(_pButtonStart);
	SafeDelete(_pButtonOptions);
	SafeDelete(_pButtonTrophy);
	SafeDelete(_pButtonHelp);
	SafeDelete(_pButtonSupport);
    
	SafeDelete(_pButtonSwitch);
	SafeDelete(_pButtonYes);
	SafeDelete(_pButtonNo);
	SafeDelete(_pButtonEdit);
    
	SafeDelete(_pProfileEdit);
	SafeDelete(_pProfileDelete);
    
	SafeDelete(_pParticleManager);
    
	SafeDelete(_pMobileKeyboard);
    
}

int eMainMenu::Open(int iOS)
{
    CProfile *pProfile;
    
    if (_pProfileEdit==NULL)
	{
		_pProfileEdit = new CSprite((char*)"profed",iOS);
		_pProfileDelete = new CSprite((char*)"prodel",iOS);
		return 10;
	}

	if (_pBackground==NULL)
	{
		_pBackground = new CSprite((char*)"e_mmenu",iOS);
		_pBlack = new CSprite((char*)"black100",iOS);	// czarny fade
		_pWhite = new CSprite((char*)"white100",iOS);
		_pFont = new CSpriteFont();
		return 20;
	}
    
	if (_pWall_L==NULL)
	{
		_pWall_L = new CSprite((char*)"walll",iOS);
		_pWall_R = new CSprite((char*)"wallr",iOS);
        
        if (iOS == IPHONE4 || iOS == IPHONE5 || iOS == IPAD)
        {
        	_pArrowR = new CSprite((char*)"arrow_right32.png");
        }
        else
        {
        	_pArrowR = new CSprite((char*)"arrow_right64.png");
        }
        
		return 30;
	}
    
	if (_pButtonStart==NULL)
	{
        if (iOS == IPHONE4)
        {
            _pButtonStart = new CTouchButton(0,0,128,128,(char*)"pl_start.png",(char*)"pl_starto.png",(char*)"pl_start.png");
            _pButtonStart->SetPosition(510,500);
        }
        else if (iOS == IPHONE5)
        {
            _pButtonStart = new CTouchButton(0,0,128,128,(char*)"pl_start.png",(char*)"pl_starto.png",(char*)"pl_start.png");
            _pButtonStart->SetPosition(630,500);
        }
        else if (iOS == IPAD)
        {
            _pButtonStart = new CTouchButton(0,0,128,128,(char*)"pl_start.png",(char*)"pl_starto.png",(char*)"pl_start.png");
            _pButtonStart->SetPosition(590,610);
        }
        else if (iOS == IPAD_HD)
        {
            _pButtonStart = new CTouchButton(0,0,256,256,(char*)"pl_start256.png",(char*)"pl_starto256.png",(char*)"pl_start256.png");
            _pButtonStart->SetPosition(1170,1220);
        }

        if (_pMobileKeyboard==NULL)
        _pMobileKeyboard = new CMobileKeyboard(0);

        _pMobileKeyboard->Open(iOS);
        
		return 40;
	}
    
	if (_pButtonOptions==NULL)
	{
        if (iOS == IPHONE4)
        {
            _pButtonOptions = new CTouchButton(0,0,128,128,(char*)"pl_settings.png",(char*)"pl_settingso.png",(char*)"pl_settings.png");
            _pButtonOptions->SetPosition(100,500);
        }
        else if (iOS == IPHONE5)
        {
            _pButtonOptions = new CTouchButton(0,0,128,128,(char*)"pl_settings.png",(char*)"pl_settingso.png",(char*)"pl_settings.png");
            _pButtonOptions->SetPosition(150,500);
        }
        else if (iOS == IPAD)
        {
            _pButtonOptions = new CTouchButton(0,0,128,128,(char*)"pl_settings.png",(char*)"pl_settingso.png",(char*)"pl_settings.png");
            _pButtonOptions->SetPosition(125,610);
        }
        else if (iOS == IPAD_HD)
        {
            _pButtonOptions = new CTouchButton(0,0,256,256,(char*)"pl_settings256.png",(char*)"pl_settingso256.png",(char*)"pl_settings256.png");
            _pButtonOptions->SetPosition(250,1220);
        }

		return 50;
	}
    
	if (_pButtonTrophy==NULL)
	{
        if (iOS == IPHONE4)
        {
            _pButtonTrophy = new CTouchButton(0,0,128,128,(char*)"pl_trophy.png",(char*)"pl_trophyo.png",(char*)"pl_trophy.png");
            _pButtonTrophy->SetPosition(240,450);
        }
        else if (iOS == IPHONE5)
        {
            _pButtonTrophy = new CTouchButton(0,0,128,128,(char*)"pl_trophy.png",(char*)"pl_trophyo.png",(char*)"pl_trophy.png");
            _pButtonTrophy->SetPosition(340,470);
        }
        else if (iOS == IPAD)
        {
            _pButtonTrophy = new CTouchButton(0,0,128,128,(char*)"pl_trophy.png",(char*)"pl_trophyo.png",(char*)"pl_trophy.png");
            _pButtonTrophy->SetPosition(260,600);
        }
        else if (iOS == IPAD_HD)
        {
            _pButtonTrophy = new CTouchButton(0,0,256,256,(char*)"pl_trophy256.png",(char*)"pl_trophyo256.png",(char*)"pl_trophy256.png");
            _pButtonTrophy->SetPosition(500,1200);
        }

		return 60;
	}

	if (_pButtonHelp==NULL)
	{
        if (iOS == IPHONE4)
        {
            _pButtonHelp = new CTouchButton(0,0,128,128,(char*)"pl_help.png",(char*)"pl_helpo.png",(char*)"pl_help.png");
            _pButtonHelp->SetPosition(800,500);
        }
        else if (iOS == IPHONE5)
        {
            _pButtonHelp = new CTouchButton(0,0,128,128,(char*)"pl_help.png",(char*)"pl_helpo.png",(char*)"pl_help.png");
            _pButtonHelp->SetPosition(900,500);
        }
        else if (iOS == IPAD)
        {
            _pButtonHelp = new CTouchButton(0,0,128,128,(char*)"pl_help.png",(char*)"pl_helpo.png",(char*)"pl_help.png");
            _pButtonHelp->SetPosition(820,610);
        }
        else if (iOS == IPAD_HD)
        {
            _pButtonHelp = new CTouchButton(0,0,256,256,(char*)"pl_help256.png",(char*)"pl_helpo256.png",(char*)"pl_help256.png");
            _pButtonHelp->SetPosition(1660,1220);
        }

		return 65;
	}
    
	if (_pButtonSupport==NULL)
	{
        if (iOS == IPHONE4)
        {
            _pButtonSupport = new CTouchButton(0,0,128,128,(char*)"pl_support.png",(char*)"pl_supporto.png",(char*)"pl_support.png");
            _pButtonSupport->SetPosition(-20,500);
        }
        else if (iOS == IPHONE5)
        {
            _pButtonSupport = new CTouchButton(0,0,128,128,(char*)"pl_support.png",(char*)"pl_supporto.png",(char*)"pl_support.png");
            _pButtonSupport->SetPosition(0,500);
        }
        else if (iOS == IPAD)
        {
            _pButtonSupport = new CTouchButton(0,0,128,128,(char*)"pl_support.png",(char*)"pl_supporto.png",(char*)"pl_support.png");
            _pButtonSupport->SetPosition(0,610);
        }
        else if (iOS == IPAD_HD)
        {
            _pButtonSupport = new CTouchButton(0,0,256,256,(char*)"pl_support256.png",(char*)"pl_supporto256.png",(char*)"pl_support256.png");
            _pButtonSupport->SetPosition(20,1220);
        }
        
        return 70;
	}
    
	if (_pButtonSwitch==NULL)
	{
        if (iOS == IPHONE4)
        {
            _pButtonSwitch = new CTouchButton(0,0,128,128,(char*)"edit.png",(char*)"edito.png",(char*)"edit.png");
            _pButtonSwitch->SetPosition(650,500);
        }
        else if (iOS == IPHONE5)
        {
            _pButtonSwitch = new CTouchButton(0,0,128,128,(char*)"edit.png",(char*)"edito.png",(char*)"edit.png");
            _pButtonSwitch->SetPosition(770,500);
        }
        else if (iOS == IPAD)
        {
            _pButtonSwitch = new CTouchButton(0,0,128,128,(char*)"edit.png",(char*)"edito.png",(char*)"edit.png");
            _pButtonSwitch->SetPosition(700,610);
        }
        else if (iOS == IPAD_HD)
        {
            _pButtonSwitch = new CTouchButton(0,0,256,256,(char*)"edit256.png",(char*)"edito256.png",(char*)"edit256.png");
            _pButtonSwitch->SetPosition(1400,1220);
        }
		
		return 80;
	}
    
	if (_pButtonYes==NULL)
	{
        if (iOS == IPHONE4)
        {
            _pButtonYes = new CTouchButton(0,0,128,128,(char*)"ok_static_128px.png",(char*)"ok_over_128px.png",(char*)"ok_click_128px.png");
        }
        else if (iOS == IPHONE5)
        {
            _pButtonYes = new CTouchButton(0,0,128,128,(char*)"ok_static_128px.png",(char*)"ok_over_128px.png",(char*)"ok_click_128px.png");
        }
        else if (iOS == IPAD)
        {
            _pButtonYes = new CTouchButton(0,0,128,128,(char*)"ok_static_128px.png",(char*)"ok_over_128px.png",(char*)"ok_click_128px.png");
        }
        else if (iOS == IPAD_HD)
        {
            _pButtonYes = new CTouchButton(0,0,256,256,(char*)"ok_static_256px.png",(char*)"ok_over_256px.png",(char*)"ok_click_256px.png");
        }
        
		return 85;
	}
    
	if (_pButtonNo==NULL)
	{
        if (iOS == IPHONE4)
        {
            _pButtonNo = new CTouchButton(0,0,128,128,(char*)"cancel_static128.png",(char*)"cancel_over128.png",(char*)"cancel_clicked128.png");
        }
        else if (iOS == IPHONE5)
        {
            _pButtonNo = new CTouchButton(0,0,128,128,(char*)"cancel_static128.png",(char*)"cancel_over128.png",(char*)"cancel_clicked128.png");
        }
        else if (iOS == IPAD)
        {
            _pButtonNo = new CTouchButton(0,0,128,128,(char*)"cancel_static128.png",(char*)"cancel_over128.png",(char*)"cancel_clicked128.png");
        }
        else if (iOS == IPAD_HD)
        {
            _pButtonNo = new CTouchButton(0,0,256,256,(char*)"cancel_static256.png",(char*)"cancel_over256.png",(char*)"cancel_clicked256.png");
        }

		return 90;
	}
    
	if (_pButtonEdit==NULL)
	{
        if (iOS == IPHONE4)
        {
            _pButtonEdit = new CTouchButton(0,0,128,128,(char*)"edit.png",(char*)"edito.png",(char*)"edit.png");

            _pParticleManager = new CParticle2DManager((char*)"k6.png", 50,
                                                       -100,-100,IPHONE4_X+100,IPHONE4_Y+100,
                                                       0.01f,0.01f,1.3f,1.3f,
                                                       0.5f, -.001f,.001f,
                                                       0.5f, -.5f,.5f,
                                                       1000,10000);
        }
        else if (iOS == IPHONE5)
        {
            _pButtonEdit = new CTouchButton(0,0,128,128,(char*)"edit.png",(char*)"edito.png",(char*)"edit.png");

            _pParticleManager = new CParticle2DManager((char*)"k6.png", 50,
                                                       -100,-100,IPHONE5_X+100,IPHONE5_Y+100,
                                                       0.01f,0.01f,1.3f,1.3f,
                                                       0.5f, -.001f,.001f,
                                                       0.5f, -.5f,.5f,
                                                       1000,10000);
        }
        else if (iOS == IPAD)
        {
            _pButtonEdit = new CTouchButton(0,0,128,128,(char*)"edit.png",(char*)"edito.png",(char*)"edit.png");

            _pParticleManager = new CParticle2DManager((char*)"k6.png", 50,
                                                       -100,-100,IPAD_X+100,IPAD_Y+100,
                                                       0.01f,0.01f,1.3f,1.3f,
                                                       0.5f, -.001f,.001f,
                                                       0.5f, -.5f,.5f,
                                                       1000,10000);
            
        }
        else if (iOS == IPAD_HD)
        {
            _pButtonEdit = new CTouchButton(0,0,256,256,(char*)"edit256.png",(char*)"edito256.png",(char*)"edit256.png");

            _pParticleManager = new CParticle2DManager((char*)"k6.png", 50,
                                                       -100,-100,IPAD_HD_X+100,IPAD_HD_Y+100,
                                                       0.1f,0.1f,1.3f,1.3f,
                                                       0.5f, -.001f,.001f,
                                                       0.5f, -.5f,.5f,
                                                       1000,10000);
        
        }
        
        _pParticleManager->isLoop(true);
        
		return 95;
	}
    
	if (_pTitle==NULL)
	{

        if (iOS == IPAD_HD)
        {
        	_pTitle = new CSprite((char*)"title1024.png");
            _pTitle->SetPosition(512,64);
        }
        else if (iOS == IPAD)
        {
            _pTitle = new CSprite((char*)"title512.png");
            _pTitle->SetPosition(256,64);
        }
        else if (iOS == IPHONE5)
        {
            _pTitle = new CSprite((char*)"title512.png");
            _pTitle->SetPosition(312,0);
            
        }
        else if (iOS == IPHONE4)
        {
            _pTitle = new CSprite((char*)"title512.png");
            _pTitle->SetPosition(224,0);
        }
        
        return 100;
	}
    
	// wczytaj odpowiednia flage
    
	if (_pFlag == NULL)
	{
		switch (_ucLanguage)
		{
			case 10:
                _pFlag = new CButton((char*)"l_en_click64.png",(char*)"l_en_over64.png",(char*)"l_en64.png",0,0,64,64);

                break;
                
			case 20:
                _pFlag = new CButton((char*)"l_ru_click64.png",(char*)"l_ru_over64.png",(char*)"l_ru64.png",0,0,64,64);
                break;
                
			case 30:
                _pFlag = new CButton((char*)"l_de_click64.png",(char*)"l_de_over64.png",(char*)"l_de64.png",0,0,64,64);
                break;
                
			case 40:
                _pFlag = new CButton((char*)"l_fr_click64.png",(char*)"l_fr_over64.png",(char*)"l_fr64.png",0,0,64,64);
                break;
                
			case 50:
                _pFlag = new CButton((char*)"l_it_click64.png",(char*)"l_it_over64.png",(char*)"l_it64.png",0,0,64,64);
                break;
                
			case 60:
                _pFlag = new CButton((char*)"l_es_click64.png",(char*)"l_es_over64.png",(char*)"l_es64.png",0,0,64,64);
                break;
                
			case 70:
                _pFlag = new CButton((char*)"l_pl_click64.png",(char*)"l_pl_over64.png",(char*)"l_pl64.png",0,0,64,64);
                break;
                
			case 80:
                _pFlag = new CButton((char*)"l_tu_click64.png",(char*)"l_tu_over64.png",(char*)"l_tu64.png",0,0,64,64);
                break;
                
			case 90:
                _pFlag = new CButton((char*)"l_jp_click64.png",(char*)"l_jp_over64.png",(char*)"l_jp64.png",0,0,64,64);
                break;
                
			case 100:
                _pFlag = new CButton((char*)"l_ko_click64.png",(char*)"l_ko_over64.png",(char*)"l_ko64.png",0,0,64,64);
                break;
                
			case 110:
                _pFlag = new CButton((char*)"l_ch_click64.png",(char*)"l_ch_over64.png",(char*)"l_ch64.png",0,0,64,64);
                break;
                
			case 120:
                _pFlag = new CButton((char*)"l_in_click64.png",(char*)"l_in_over64.png",(char*)"l_in64.png",0,0,64,64);
                break;
                
			case 130:
                _pFlag = new CButton((char*)"l_ar_click64.png",(char*)"l_ar_over64.png",(char*)"l_ar64.png",0,0,64,64);
                break;
                
			case 140:
                _pFlag = new CButton((char*)"l_is_click64.png",(char*)"l_is_over64.png",(char*)"l_is64.png",0,0,64,64);
                break;
                
			case 150:
                _pFlag = new CButton((char*)"l_br_click64.png",(char*)"l_br_over64.png",(char*)"l_br64.png",0,0,64,64);
                break;
                
			case 160:
                _pFlag = new CButton((char*)"l_id_click64.png",(char*)"l_id_over64.png",(char*)"l_id64.png",0,0,64,64);
                break;
                
			case 170:
                _pFlag = new CButton((char*)"l_po_click64.png",(char*)"l_po_over64.png",(char*)"l_po64.png",0,0,64,64);
                break;
                
			case 180:
                _pFlag = new CButton((char*)"l_se_click64.png",(char*)"l_se_over64.png",(char*)"l_se64.png",0,0,64,64);
                break;
                
			case 190:
                _pFlag = new CButton((char*)"l_no_click64.png",(char*)"l_no_over64.png",(char*)"l_no64.png",0,0,64,64);
                break;
                
			case 200:
                _pFlag = new CButton((char*)"l_dk_click64.png",(char*)"l_dk_over64.png",(char*)"l_dk64.png",0,0,64,64);
                break;
                
			default:
                _pFlag = new CButton((char*)"l_en_click64.png",(char*)"l_en_over64.png",(char*)"l_en64.png",0,0,64,64);
                break;
		}

        if (iOS==IPHONE4)
        {
            _pFlag->SetPosition(IPHONE4_X-80,16);
            _pFlag->SetHotCoords(IPHONE4_X-80,16,IPHONE4_X-16,80);
        }
        else if (iOS==IPHONE5)
        {
            _pFlag->SetPosition(IPHONE5_X-80,IPHONE5_Y-80);
            _pFlag->SetHotCoords(IPHONE5_X-80,IPHONE5_Y-80,IPHONE5_X-16,IPHONE5_Y-16);
        }
        else if (iOS==IPAD)
        {
            _pFlag->SetPosition(IPAD_X-80,IPAD_Y-80);
            _pFlag->SetHotCoords(IPAD_X-80,IPAD_Y-80,IPAD_X-16,IPAD_Y-16);
        }
        else if (iOS==IPAD_HD)
        {
            _pFlag->SetPosition(IPAD_HD_X-80,IPAD_HD_Y-80);
            _pFlag->SetHotCoords(IPAD_HD_X-80,IPAD_HD_Y-80,IPAD_HD_X-16,IPAD_HD_Y-16);
        }

	}
  
	// zaktualizuj informacje o profilu
    
	pProfile = new CProfile();
    pProfile->bSetup();
	
    pProfile->bLoad();
    
	_ucCurrentProfile = pProfile->ucCurrentProfile();
    
	for (int i=0; i<8; i++)
	{
		pProfile->ucCurrentProfile(i);
		strcpy(_pUserName[i],pProfile->pGetName());
	}
	
	delete pProfile;
    
	_isProfileView = false;		// czy przegladamy profile?
	_isProfileEdit = false;		// czy wpisujemy dane?
	_isProfileDelete = false;
    
	_bMouseLock = true;
    
	_pFXManager = new CFXManager();
    
    _iOS = iOS;
    
    _ulTimerStart = 0;
    
	_isActive = true;	// dane wczytane
    
    return 101;
    
}

void eMainMenu::Close(void)
{
	SafeDelete(_pFont);
    SafeDelete(_pFlag);
	SafeDelete(_pBackground);
	SafeDelete(_pBlack);
	SafeDelete(_pWhite);
	SafeDelete(_pTitle);
	
	SafeDelete(_pArrowR);
    
	SafeDelete(_pWall_L);
	SafeDelete(_pWall_R);
    
	SafeDelete(_pButtonStart);
	SafeDelete(_pButtonOptions);
	SafeDelete(_pButtonTrophy);
	SafeDelete(_pButtonHelp);
	SafeDelete(_pButtonSupport);
    
	SafeDelete(_pButtonSwitch);
	SafeDelete(_pButtonYes);
	SafeDelete(_pButtonNo);
	SafeDelete(_pButtonEdit);
    
	SafeDelete(_pProfileEdit);
	SafeDelete(_pProfileDelete);
    
	SafeDelete(_pParticleManager);
    
	SafeDelete(_pMobileKeyboard);

    _bMouseLock = true;
    _isActive = false;
   
}

int eMainMenu::Render(CTouch *pTouch, unsigned long ulTimer)
{
    int iReturn = 0;
	static unsigned char cMobileKey=0;

    
	if (_ulTimerStart == 0)
	{
		_ulTimerStart = ulTimer;

		_pFXManager->Add(FX_MENU_BUTTON, _pButtonStart->x1() + (_pButtonStart->iSizeX() / 2), _pButtonStart->y1() + (_pButtonStart->iSizeY() / 2), 1, 1, 1, 0.25, ulTimer, 1000000);
		_pFXManager->Add(FX_MENU_BUTTON, _pButtonSwitch->x1() + (_pButtonSwitch->iSizeX() / 2), _pButtonSwitch->y1() + (_pButtonSwitch->iSizeY() / 2), 1, 1, 1, 0.25, ulTimer, 1000000);
		_pFXManager->Add(FX_MENU_BUTTON, _pButtonOptions->x1() + (_pButtonOptions->iSizeX() / 2), _pButtonOptions->y1() + (_pButtonOptions->iSizeY() / 2), 1, 1, 1, 0.5, ulTimer, 1000000);
		_pFXManager->Add(FX_MENU_BUTTON, _pButtonTrophy->x1() + (_pButtonTrophy->iSizeX() / 2), _pButtonTrophy->y1() + (_pButtonTrophy->iSizeY() / 2), 1, 1, 1, 0.5, ulTimer, 1000000);
		_pFXManager->Add(FX_MENU_BUTTON, _pButtonHelp->x1() + (_pButtonHelp->iSizeX() / 2), _pButtonHelp->y1() + (_pButtonHelp->iSizeY() / 2), 1, 1, 1, 0.5, ulTimer, 1000000);
		_pFXManager->Add(FX_MENU_BUTTON, _pButtonSupport->x1() + (_pButtonSupport->iSizeX() / 2), _pButtonSupport->y1() + (_pButtonSupport->iSizeY() / 2), 1, 1, 1, 0.5, ulTimer, 1000000);
        pTouch->Reset();
	}
    
    if (!pTouch->isPressed())
    {
        _bMouseLock = false;
    }
    
    
	if (!_isProfileView)	// nie jestesmy w trybie przegladania profili
	{
		_pBackground->Render();
        
		if (_pButtonStart->Render(pTouch)==ON_LEFT && !_bMouseLock) iReturn = 1;
		if (_pButtonOptions->Render(pTouch)==ON_LEFT && !_bMouseLock) iReturn = 2;
		if (_pButtonTrophy->Render(pTouch)==ON_LEFT && !_bMouseLock) iReturn = 3;
		if (_pButtonHelp->Render(pTouch)==ON_LEFT && !_bMouseLock) iReturn = 4;
		if (_pButtonSupport->Render(pTouch)==ON_LEFT && !_bMouseLock) iReturn = 5;
		
		if (_pButtonSwitch->Render(pTouch)==ON_LEFT && !_bMouseLock)
		{
			_isProfileView = true;
			_bMouseLock = true;	// blokujemy mysz ponownie zeby nie przenosic klikniecia
		}
        
		if (_pFlag->Render(pTouch)==ON_LEFT && !_bMouseLock)
			iReturn = 10;		// przycisk zmiany jezyka
        
		_pParticleManager->Render(ulTimer);
        
		_pFXManager->Render(ulTimer);
        
		_pTitle->Render();												// logo gry
        
		if (_iOS == IPAD)
		{
			_pFont->Print(25, 300, 1, 0.1f, 0.1f, _pUserName[_ucCurrentProfile]);		// imie gracza
		}
		else if (_iOS == IPHONE4)
		{
			_pFont->Print(-20, 180, 1, 0.1f, 0.1f, _pUserName[_ucCurrentProfile]);		// imie gracza
		}
		else if (_iOS == IPHONE5)
		{
			_pFont->Print(25, 180, 1, 0.1f, 0.1f, _pUserName[_ucCurrentProfile]);		// imie gracza
		}
		else if (_iOS == IPAD_HD)
		{
			_pFont->Print(250, 800, 1, 0.2f, 0.2f, _pUserName[_ucCurrentProfile]);		// imie gracza
		}
        
        // rozsuwane ściany

        if (ulTimer - _ulTimerStart<201)
        {
            _pWall_L->Position((float)-(_pWall_L->fSizeX()/2),0);
            _pWall_L->Render();
          
            _pWall_R->Position(_pWall_R->fSizeX()/2,0);
            _pWall_R->Render();
        }

        // fade
        
		if ((ulTimer - _ulTimerStart>200) && (ulTimer - _ulTimerStart<10000) )
		{
            
			if ((ulTimer - _ulTimerStart)<1000)	// czarny fade out tla
			{
				_pBlack->fAlfa(1.0f-((ulTimer-_ulTimerStart)*0.001));
				_pBlack->Render();
			}
            
			// rozsuwane sciany
            
			_pWall_L->Position((float)-(_pWall_L->fSizeX()/2)-((ulTimer - _ulTimerStart-200)/6),0);
			_pWall_L->Render();
            
			_pWall_R->Position((_pWall_R->fSizeX()/2)+((ulTimer - _ulTimerStart)-200)/6,0);
			_pWall_R->Render();
		}
        
	}
	else	// przegladamy profile
	{
		if (!_isProfileDelete && !_isProfileEdit)	// edycja nazw profilu
		{
			_pProfileEdit->Render();
            
			// wypisz duøymi literami nazwÍ g≥Ûwnego profilu
            
            if (_iOS == IPHONE4)
            {
				_pFont->Print(-200, -200, 1, 0.125f, 0.125f, _pUserName[_ucCurrentProfile]);
            }
            else if (_iOS == IPHONE5)
            {
				_pFont->Print(-200, -200, 1, 0.125f, 0.125f, _pUserName[_ucCurrentProfile]);
            }
            else if(_iOS == IPAD)
            {
				_pFont->Print(-200, -200, 1, 0.125f, 0.125f, _pUserName[_ucCurrentProfile]);
			}
            else if (_iOS == IPAD_HD)
            {
				_pFont->Print(-100, -100, 1, 0.25f, 0.25f, _pUserName[_ucCurrentProfile]);
            }
            
			// wypisujemy nazwy wszystkich profili
            
			for (int i=0; i<8; i++)
			{
				int x1, y1, iStep, xp1, yp1;            // xp1,yp1 - print, obszar fontów różny niż obszar kliknięcia
				float fSize;
                
				if (_iOS == IPAD)
				{
					x1 = 100; y1 = 148; fSize = 0.06f; iStep = 48;
                    xp1 = 100; yp1 = -100;
				}
				else if (_iOS == IPHONE4)
				{
					x1 = 100; y1 = 148; fSize = 0.06f; iStep = 48;
                    xp1 = 100; yp1=-100;
				}
				else if (_iOS == IPHONE5)
				{
					x1 = 100; y1 = 148; fSize = 0.06f; iStep = 48;
                    xp1 = 100; yp1=-100;
				}
				else if (_iOS == IPAD_HD)
				{
					x1 = 300; y1 = 340; fSize = 0.15f; iStep = 80;
                    xp1 = x1; yp1 = 100;
				}
                
				_pFont->Print(xp1,yp1+(i*iStep),255, fSize, fSize, _pUserName[i]);
                
				if (pTouch->iGetY()>(y1+(i*iStep)) && pTouch->iGetY()<(y1+(i*iStep)+iStep))
				{
					if (_iOS == IPAD)
					{
						_pArrowR->Position(260, 148 + (i * iStep));
					}
					else if (_iOS == IPHONE4)
					{
						_pArrowR->Position(260, 148 + (i * iStep));
					}
					else if (_iOS == IPHONE5)
					{
						_pArrowR->Position(260, 145 + (i * iStep));
					}
					else if (_iOS == IPAD_HD)
					{
						_pArrowR->Position(360, 320 + (i * iStep));
					}
                    
					_pArrowR->Render();
                    
					if (pTouch->isPressed())
					{
						CProfile	*pProfile;
                        
						_ucCurrentProfile=i;
                        
						pProfile = new CProfile();
						pProfile->bLoad();
						pProfile->ucCurrentProfile(_ucCurrentProfile);
						pProfile->bSave();
						delete pProfile;
					}
				}
                
			}
            
			if (_iOS == IPAD)
			{
				_pButtonEdit->SetPosition(250, 550);
			}
			else if(_iOS == IPHONE4)
			{
				_pButtonEdit->SetPosition(128, 500);
			}
			else if (_iOS == IPHONE5)
			{
				_pButtonEdit->SetPosition(128, 500);
			}
			else if (_iOS == IPAD_HD)
			{
				_pButtonEdit->SetPosition(400, 1000);
			}
            
            
			if (_pButtonEdit->Render(pTouch)==ON_LEFT && !_bMouseLock )	// kasujemy aktualna nazwe bedziemy wprowadzac nowa
			{
				for (int i=0;i<18;i++)
					_cEditName[i]=0;

				_cIndex=0;
				_isProfileEdit = true;
				_bMouseLock = true;	// zablokuj myszke zeby nie przenosic klikniecia
			}
            
			if (_iOS == IPAD)
			{
				_pButtonYes->SetPosition(450, 550);
				_pButtonNo->SetPosition(650, 550);
			}
			else if (_iOS == IPHONE4)
			{
				_pButtonYes->SetPosition(416, 500);
				_pButtonNo->SetPosition(768, 500);
			}
			else if (_iOS == IPHONE5)
			{
				_pButtonYes->SetPosition(550, 500);
				_pButtonNo->SetPosition(900, 500);
			}
			else if (_iOS == IPAD_HD)
			{
				_pButtonYes->SetPosition(1000, 1000);
				_pButtonNo->SetPosition(1600, 1000);
			}
            
			if (_pButtonYes->Render(pTouch)==ON_LEFT && !_bMouseLock)
            {
				_isProfileView=false;
                _bMouseLock = true;
            }
			
			if (_pButtonNo->Render(pTouch)==ON_LEFT && !_bMouseLock)
            {
				_isProfileDelete = true;;
                _bMouseLock = true;
            }
        }
        
		if (_isProfileDelete)		// kasowanie profilu
		{
			_pProfileDelete->Render();
            
			// wypisz duøymi literami nazwÍ g≥Ûwnego profilu
            
            if (_iOS == IPAD)
            {
				_pFont->Print(0, 100, 1, 0.125f, 0.125f, _pUserName[_ucCurrentProfile]);
				_pFont->Print(-200, -200, 1, 0.125f, 0.125f, (char*)"delete profile?");
                
				// przyciski kasowania
                
				_pButtonYes->SetPosition(128, 500);
				_pButtonYes->SetHotCoords(128, 500, 128+128, 500+128);
                
				_pButtonNo->SetPosition(1024-128-128, 500);
				_pButtonNo->SetHotCoords(1024-128-128, 500, 1024-128, 500+128);
            }
            else if (_iOS == IPAD_HD)
            {
				_pFont->Print(32, 300, 1, 0.25f, 0.25f, _pUserName[_ucCurrentProfile]);
				_pFont->Print(0, 0, 1, 0.25f, 0.25f, (char*)"delete profile?");
                
				// przyciski kasowania
                
				_pButtonYes->SetPosition(300, 1000);
				_pButtonNo->SetPosition(1300, 1000);
            }
            else if (_iOS == IPHONE4)
            {
				_pFont->Print(-100, -50, 1, 0.125f, 0.125f, _pUserName[_ucCurrentProfile]);
				_pFont->Print(-100, -150, 1, 0.125f, 0.125f, (char*)"delete profile?");
                
				// przyciski kasowania
                
				_pButtonYes->SetPosition(128, 300);
                
				_pButtonNo->SetPosition(1024-128-128, 300);

            }
            else if (_iOS == IPHONE5)
            {
				_pFont->Print(-100, 50, 1, 0.125f, 0.125f, _pUserName[_ucCurrentProfile]);
				_pFont->Print(-100, -150, 1, 0.125f, 0.125f, (char*)"delete profile?");
                
				// przyciski kasowania
                
				_pButtonYes->SetPosition(128, 300);
                
				_pButtonNo->SetPosition(1136-128-128, 300);
            }
            
            
			if (_pButtonYes->Render(pTouch)==ON_LEFT  && !_bMouseLock)
			{
				CProfile	*pProfile;
                
				pProfile = new CProfile();
				pProfile->bLoad();
                
				pProfile->ucCurrentProfile(_ucCurrentProfile);
				pProfile->SetName((char*)"EMPTY");
				pProfile->SetLevel(0);
				pProfile->SetScore(0);
				pProfile->SetTotalScore(0);
				pProfile->ulMap(0);
                
				for (int i=0; i<21; i++)
					pProfile->ucTroophy(i,0);
                
				pProfile->bSave();
                
				strcpy(_pUserName[_ucCurrentProfile],pProfile->pGetName());
                
				delete pProfile;
                
				_bMouseLock = true;
				_isProfileDelete = false;
			}
            
			
			if (_pButtonNo->Render(pTouch)==ON_LEFT  && !_bMouseLock)
				_isProfileDelete = false;
		}
	}
    
	if (_isProfileEdit)					// edycja nazwy profilu
	{
		_pProfileDelete->Render();		// uzywamy tego samego tla co dla profile
        
        if (_iOS == IPAD)
        {
			_pButtonYes->SetPosition(800, 200);
			_pButtonYes->SetHotCoords(800, 200, 800 + 128, 200 + 128);
			_pFont->Print(0, 0, 1, 0.1f, 0.1f, _cEditName);						// wypisz nazwe gracza
            
			if ((ulTimer % 100)>50)													// mrugajacy kursor, tu jestesmy
				_pFont->Print(0 + (_cIndex * 40), 0, 255, 0.1f, 0.1f, (char*)".");
        }
        else if (_iOS == IPAD_HD)
        {
			_pButtonYes->SetPosition(1700, 100);
			_pFont->Print(16, 256, 1, 0.25f, 0.25f, _cEditName);						// wypisz nazwe gracza
            
			if ((ulTimer % 100)>50)													// mrugajacy kursor, tu jestesmy
				_pFont->Print(16 + (_cIndex * 100), 256, 1, 0.25f, 0.25f, (char*)".");
        }
        else if (_iOS == IPHONE4)
        {
			_pButtonYes->SetPosition(800, 100);
			_pFont->Print(-100, -100, 1, 0.1f, 0.1f, _cEditName);						// wypisz nazwe gracza
            
			if ((ulTimer % 100)>50)													// mrugajacy kursor, tu jestesmy
				_pFont->Print(-100 + (_cIndex * 40), -100, 1, 0.1f, 0.1f, (char*)".");
        }
        else if (_iOS == IPHONE5)
        {
			_pButtonYes->SetPosition(950, 100);
			_pFont->Print(-100, -100, 1, 0.1f, 0.1f, _cEditName);						// wypisz nazwe gracza
            
			if ((ulTimer % 100)>50)													// mrugajacy kursor, tu jestesmy
				_pFont->Print(-100 + (_cIndex * 40), -100, 1, 0.1f, 0.1f, (char*)".");
        }
        
		if (_cEditName[0] != 0)										// przycisk akceptacji dostÍpny tylko gdy wprowadzona jest co najmniej jedna litera
		{
			if (_pButtonYes->Render(pTouch) == ON_LEFT  && !_bMouseLock)
			{
				_isProfileEdit = false;
                
				CProfile	*pProfile;
				pProfile = new CProfile();
				pProfile->bLoad();
				pProfile->ucCurrentProfile(_ucCurrentProfile);
				pProfile->SetName(_cEditName);
				pProfile->bSave();
				delete pProfile;
                
				strcpy(_pUserName[_ucCurrentProfile], _cEditName);	// zapamietaj tez w wyswietlanej obecnie tablicy nazw
			}
		}
        
		cMobileKey = _pMobileKeyboard->cRender(pTouch, ulTimer);
        
        if (cMobileKey!=KEY_NONE)
        {
            KEYPRESSED = cMobileKey;
        }
        else
        {
            KEYPRESSED = KEY_NONE;
            _bKeyLock = false;
        }
        
		if (KEYPRESSED!=KEY_NONE)	// sprawdzamy stan klawiatury
		{
			if (!_bKeyLock)
			{
				switch (KEYPRESSED)
				{
					case KEY_A: if (_bPrevBack && _cIndex<15 && _cIndex!=0) _cIndex++; _cEditName[_cIndex] = 'a'; if (_cIndex<15) _cIndex++; _bPrevBack = false; break;
					case KEY_B: if (_bPrevBack && _cIndex<15 && _cIndex!=0) _cIndex++; _cEditName[_cIndex] = 'b'; if (_cIndex<15) _cIndex++; _bPrevBack = false; break;
					case KEY_C: if (_bPrevBack && _cIndex<15 && _cIndex!=0) _cIndex++;	_cEditName[_cIndex] = 'c'; if (_cIndex<15) _cIndex++; _bPrevBack = false; break;
					case KEY_D: if (_bPrevBack && _cIndex<15 && _cIndex!=0) _cIndex++;	_cEditName[_cIndex] = 'd'; if (_cIndex<15) _cIndex++; _bPrevBack = false; break;
					case KEY_E: if (_bPrevBack && _cIndex<15 && _cIndex!=0) _cIndex++;	_cEditName[_cIndex] = 'e'; if (_cIndex<15) _cIndex++; _bPrevBack = false; break;
					case KEY_F: if (_bPrevBack && _cIndex<15 && _cIndex!=0) _cIndex++;	_cEditName[_cIndex] = 'f'; if (_cIndex<15) _cIndex++; _bPrevBack = false; break;
					case KEY_G: if (_bPrevBack && _cIndex<15 && _cIndex!=0) _cIndex++;	_cEditName[_cIndex] = 'g'; if (_cIndex<15) _cIndex++; _bPrevBack = false; break;
					case KEY_H: if (_bPrevBack && _cIndex<15 && _cIndex!=0) _cIndex++;	_cEditName[_cIndex] = 'h'; if (_cIndex<15) _cIndex++; _bPrevBack = false; break;
					case KEY_I: if (_bPrevBack && _cIndex<15 && _cIndex!=0) _cIndex++;	_cEditName[_cIndex] = 'i'; if (_cIndex<15) _cIndex++; _bPrevBack = false; break;
					case KEY_J: if (_bPrevBack && _cIndex<15 && _cIndex!=0) _cIndex++;	_cEditName[_cIndex] = 'j'; if (_cIndex<15) _cIndex++; _bPrevBack = false; break;
					case KEY_K: if (_bPrevBack && _cIndex<15 && _cIndex!=0) _cIndex++;	_cEditName[_cIndex] = 'k'; if (_cIndex<15) _cIndex++; _bPrevBack = false; break;
					case KEY_L: if (_bPrevBack && _cIndex<15 && _cIndex!=0) _cIndex++;	_cEditName[_cIndex] = 'l'; if (_cIndex<15) _cIndex++; _bPrevBack = false; break;
					case KEY_M: if (_bPrevBack && _cIndex<15 && _cIndex!=0) _cIndex++;	_cEditName[_cIndex] = 'm'; if (_cIndex<15) _cIndex++; _bPrevBack = false; break;
					case KEY_N: if (_bPrevBack && _cIndex<15 && _cIndex!=0) _cIndex++;	_cEditName[_cIndex] = 'n'; if (_cIndex<15) _cIndex++; _bPrevBack = false; break;
					case KEY_O: if (_bPrevBack && _cIndex<15 && _cIndex!=0) _cIndex++;	_cEditName[_cIndex] = 'o'; if (_cIndex<15) _cIndex++; _bPrevBack = false; break;
					case KEY_P: if (_bPrevBack && _cIndex<15 && _cIndex!=0) _cIndex++;	_cEditName[_cIndex] = 'p'; if (_cIndex<15) _cIndex++; _bPrevBack = false; break;
					case KEY_Q: if (_bPrevBack && _cIndex<15 && _cIndex!=0) _cIndex++;	_cEditName[_cIndex] = 'q'; if (_cIndex<15) _cIndex++; _bPrevBack = false; break;
					case KEY_R: if (_bPrevBack && _cIndex<15 && _cIndex!=0) _cIndex++;	_cEditName[_cIndex] = 'r'; if (_cIndex<15) _cIndex++; _bPrevBack = false; break;
					case KEY_S: if (_bPrevBack && _cIndex<15 && _cIndex!=0) _cIndex++;	_cEditName[_cIndex] = 's'; if (_cIndex<15) _cIndex++; _bPrevBack = false; break;
					case KEY_T: if (_bPrevBack && _cIndex<15 && _cIndex!=0) _cIndex++;	_cEditName[_cIndex] = 't'; if (_cIndex<15) _cIndex++; _bPrevBack = false; break;
					case KEY_U: if (_bPrevBack && _cIndex<15 && _cIndex!=0) _cIndex++;	_cEditName[_cIndex] = 'u'; if (_cIndex<15) _cIndex++; _bPrevBack = false; break;
					case KEY_V: if (_bPrevBack && _cIndex<15 && _cIndex!=0) _cIndex++;	_cEditName[_cIndex] = 'v'; if (_cIndex<15) _cIndex++; _bPrevBack = false; break;
					case KEY_W: if (_bPrevBack && _cIndex<15 && _cIndex!=0) _cIndex++;	_cEditName[_cIndex] = 'w'; if (_cIndex<15) _cIndex++; _bPrevBack = false; break;
					case KEY_X: if (_bPrevBack && _cIndex<15 && _cIndex!=0) _cIndex++;	_cEditName[_cIndex] = 'x'; if (_cIndex<15) _cIndex++; _bPrevBack = false; break;
					case KEY_Y: if (_bPrevBack && _cIndex<15 && _cIndex!=0) _cIndex++;	_cEditName[_cIndex] = 'y'; if (_cIndex<15) _cIndex++; _bPrevBack = false; break;
					case KEY_Z: if (_bPrevBack && _cIndex<15 && _cIndex!=0) _cIndex++;	_cEditName[_cIndex] = 'z'; if (_cIndex<15) _cIndex++; _bPrevBack = false; break;
					case KEY_0: if (_bPrevBack && _cIndex<15 && _cIndex!=0) _cIndex++;	_cEditName[_cIndex] = '0'; if (_cIndex<15) _cIndex++; _bPrevBack = false; break;
					case KEY_1: if (_bPrevBack && _cIndex<15 && _cIndex!=0) _cIndex++;	_cEditName[_cIndex] = '1'; if (_cIndex<15) _cIndex++; _bPrevBack = false; break;
					case KEY_2: if (_bPrevBack && _cIndex<15 && _cIndex!=0) _cIndex++;	_cEditName[_cIndex] = '2'; if (_cIndex<15) _cIndex++; _bPrevBack = false; break;
					case KEY_3: if (_bPrevBack && _cIndex<15 && _cIndex!=0) _cIndex++;	_cEditName[_cIndex] = '3'; if (_cIndex<15) _cIndex++; _bPrevBack = false; break;
					case KEY_4: if (_bPrevBack && _cIndex<15 && _cIndex!=0) _cIndex++;	_cEditName[_cIndex] = '4'; if (_cIndex<15) _cIndex++; _bPrevBack = false; break;
					case KEY_5: if (_bPrevBack && _cIndex<15 && _cIndex!=0) _cIndex++;	_cEditName[_cIndex] = '5'; if (_cIndex<15) _cIndex++; _bPrevBack = false; break;
					case KEY_6: if (_bPrevBack && _cIndex<15 && _cIndex!=0) _cIndex++;	_cEditName[_cIndex] = '6'; if (_cIndex<15) _cIndex++; _bPrevBack = false; break;
					case KEY_7: if (_bPrevBack && _cIndex<15 && _cIndex!=0) _cIndex++;	_cEditName[_cIndex] = '7'; if (_cIndex<15) _cIndex++; _bPrevBack = false; break;
					case KEY_8: if (_bPrevBack && _cIndex<15 && _cIndex!=0) _cIndex++;	_cEditName[_cIndex] = '8'; if (_cIndex<15) _cIndex++; _bPrevBack = false; break;
					case KEY_9: if (_bPrevBack && _cIndex<15 && _cIndex!=0) _cIndex++;	_cEditName[_cIndex] = '9'; if (_cIndex<15) _cIndex++; _bPrevBack = false; break;
                        
					case KEY_DELETE:
						_cEditName[_cIndex]=0;
                        
						if (_cIndex!=0 )
						{
							_cIndex--;
							_bPrevBack = true;
						}
                        
                        break;
                        
					case KEY_ENTER:
						_isProfileEdit = false;
						CProfile	*pProfile;
						pProfile = new CProfile();
						pProfile->bLoad();
						pProfile->ucCurrentProfile(_ucCurrentProfile);
						pProfile->SetName(_cEditName);
						pProfile->bSave();
						delete pProfile;
                        
						strcpy(_pUserName[_ucCurrentProfile],_cEditName);	// zapamietaj tez w wyswietlanej obecnie tablicy nazw
                        break;
                        
				}													
				_bKeyLock = true;
			}
		}
		else
		{
			_bKeyLock = false;
		}
        
	}

    pTouch->Reset();
    
    return iReturn;   // nie rob nic
}


