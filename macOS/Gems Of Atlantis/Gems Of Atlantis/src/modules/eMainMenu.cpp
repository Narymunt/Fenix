#include "eMainMenu.h"

#pragma warning(disable:4996)

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

//=== konstruktor

eMainMenu::eMainMenu()
{
	
	CProfile *pProfile;

	// ustaw znacznik, ze dane nie sa jeszcze wczytane
	_isActive = false;

	_pTitle = NULL;

	m_pBackground = NULL;
	m_pWall_L = m_pWall_R = NULL;
	m_ulTimerStart = 0;
	
	m_pBlack = NULL;
	m_pWhite = NULL;

	_pArrowR = NULL;

	m_pButtonStart = NULL;
	m_pButtonOptions = NULL;
	m_pButtonTrophy = NULL;
	m_pButtonHelp = NULL;
	m_pButtonExit = NULL;
	m_pButtonSupport = NULL;

	m_pButtonSwitch = NULL;
	m_pButtonYes = NULL;
	m_pButtonNo = NULL;
	m_pButtonEdit = NULL;

	m_pProfileEdit = NULL;
	m_pProfileDelete = NULL;

	m_bPrevBack = false;		// nie bylo backspace

	m_pFont = NULL;

	pProfile = new CProfile(USERS_FILE);
	pProfile->bLoad();

	m_ucCurrentProfile = pProfile->ucCurrentProfile();

	for (int i=0; i<8; i++)
	{
		pProfile->ucCurrentProfile(i);
		strcpy(m_pUserName[i],pProfile->pGetName());
	}

	delete pProfile;

	m_bProfileView = false;		// czy przegladamy profile? ustawione celowo, zeby pokazywal 100 wczytania
	m_bProfileEdit = false;		// czy wpisujemy dane?
	m_bProfileDelete = false;	

	m_ucLanguage = 0;

	for (int i=0; i<18; i++)
		m_cEditName[i] = 0;

	m_cIndex = 0;

	m_bKeyLock = true;			// blokada klawiatury na starcie

	m_pFlag = NULL;

	m_pParticleManager = NULL;	

	_pMobileKeyboard = new CMobileKeyboard(0);

	m_bMouseLock = true;
}

//=== destruktor 

eMainMenu::~eMainMenu()
{
	Close();

	SafeDelete(m_pFont);

	SafeDelete(m_pBackground);
	SafeDelete(m_pBlack);
	SafeDelete(m_pWhite);
	SafeDelete(_pTitle);
	
	SafeDelete(_pArrowR);

	SafeDelete(m_pWall_L);
	SafeDelete(m_pWall_R);

	SafeDelete(m_pButtonStart);
	SafeDelete(m_pButtonOptions);
	SafeDelete(m_pButtonTrophy);
	SafeDelete(m_pButtonHelp);
	SafeDelete(m_pButtonSupport);
	SafeDelete(m_pButtonExit);

	SafeDelete(m_pButtonSwitch);
	SafeDelete(m_pButtonYes);
	SafeDelete(m_pButtonNo);
	SafeDelete(m_pButtonEdit);

	SafeDelete(m_pProfileEdit);
	SafeDelete(m_pProfileDelete);

	SafeDelete(m_pParticleManager);

	SafeDelete(_pMobileKeyboard);
}

//=== aktualizuje i wczytuje dane

int eMainMenu::Open(CScreen *pScreen)
{		
	CProfile *pProfile;

	if (m_pProfileEdit==NULL)
	{
		m_pProfileEdit = new CSprite(pScreen,"PROFILE_EDIT");
		m_pProfileDelete = new CSprite(pScreen,"PROFILE_DELETE");
		return 10;
	}

	if (m_pBackground==NULL)
	{
		m_pBackground = new CSprite(pScreen,"GFX_MMENU_SCREEN");
		m_pBlack = new CSprite(pScreen,"GFX_BLACK100_SCREEN");	// czarny fade
		m_pWhite = new CSprite(pScreen,"GFX_WHITE100_SCREEN");
		m_pFont = new CSpriteFont(pScreen);
		return 20;
	}

	if (m_pWall_L==NULL)
	{
		m_pWall_L = new CSprite(pScreen,"WALL_L");
		m_pWall_R = new CSprite(pScreen,"WALL_R");

		_pArrowR = new CSprite(pScreen,"ARROW_RIGHT");

		return 30;
	}

	if (m_pButtonStart==NULL)
	{
		m_pButtonStart = new CButton(pScreen,"BUTTON_START");
		_pMobileKeyboard->Open(pScreen);

		return 40;
	}

	if (m_pButtonOptions==NULL)
	{
		m_pButtonOptions = new CButton(pScreen,"BUTTON_SETTINGS");
		return 50;
	}

	if (m_pButtonTrophy==NULL)
	{
		m_pButtonTrophy = new CButton(pScreen,"BUTTON_TROPHY");
		return 60;
	}

	if (m_pButtonHelp==NULL)
	{
		m_pButtonHelp = new CButton(pScreen,"BUTTON_HELP");
		return 65;
	}

	if (m_pButtonSupport==NULL)
	{
		m_pButtonSupport= new CButton(pScreen,"BUTTON_SUPPORT");
		return 70;
	}
	
	if (m_pButtonExit==NULL)
	{
		m_pButtonExit = new CButton(pScreen,"BUTTON_EXIT");
		return 75;
	}

	if (m_pButtonSwitch==NULL)
	{
		m_pButtonSwitch = new CButton(pScreen,"BUTTON_EDIT");
		return 80;
	}

	if (m_pButtonYes==NULL)
	{
		m_pButtonYes = new CButton(pScreen, "BUTTON_OK_PROFILE");
		return 85;
	}

	if (m_pButtonNo==NULL)
	{
		m_pButtonNo = new CButton(pScreen, "BUTTON_CANCEL_PROFILE");
		return 90;
	}
	
	if (m_pButtonEdit==NULL)
	{
		m_pButtonEdit = new CButton(pScreen,"BUTTON_EDIT");

		m_pParticleManager = new CParticle2DManager((char*)"particle.png", 50, 
                                               -100,-100,1024,768,
                                               0.01f,0.01f,0.3f,0.3f,
                                               0.5f, -.001f,.001f,
                                               0.5f, -5.0f,5.0f,
                                               1000,10000,pScreen);

		return 95;
	}

	if (_pTitle==NULL)
	{
		_pTitle = new CSprite(pScreen,"TITLE");
		return 100;
	}

	// wczytaj odpowiednia flage

	if (m_pFlag == NULL)
	{
		switch (m_ucLanguage)
		{
			case 10:
				m_pFlag = new CButton(pScreen, "BUTTON_MENU64_ENGLISH");
			break;

			case 20:
				m_pFlag = new CButton(pScreen, "BUTTON_MENU64_RUSSIA");
			break;

			case 30:
				m_pFlag = new CButton(pScreen, "BUTTON_MENU64_GERMAN");
			break;

			case 40:
				m_pFlag = new CButton(pScreen, "BUTTON_MENU64_FRENCH");
			break;

			case 50:
				m_pFlag = new CButton(pScreen, "BUTTON_MENU64_ITALY");
			break;

			case 60:
				m_pFlag = new CButton(pScreen, "BUTTON_MENU64_ESPANA");
			break;

			case 70:
				m_pFlag = new CButton(pScreen, "BUTTON_MENU64_POLAND");
			break;

			case 80:
				m_pFlag = new CButton(pScreen, "BUTTON_MENU64_TURKEY");
			break;

			case 90:
				m_pFlag = new CButton(pScreen, "BUTTON_MENU64_JAPAN");
			break;

			case 100:
				m_pFlag = new CButton(pScreen, "BUTTON_MENU64_KOREA");
			break;

			case 110:
				m_pFlag = new CButton(pScreen, "BUTTON_MENU64_CHINA");
			break;

			case 120:
				m_pFlag = new CButton(pScreen, "BUTTON_MENU64_INDIA");
			break;

			case 130:
				m_pFlag = new CButton(pScreen, "BUTTON_MENU64_ARABIC");
			break;
	
			case 140:
				m_pFlag = new CButton(pScreen, "BUTTON_MENU64_ISRAEL");
			break;

			case 150:
				m_pFlag = new CButton(pScreen, "BUTTON_MENU64_BRAZILIAN");
			break;

			case 160:
				m_pFlag = new CButton(pScreen, "BUTTON_MENU64_INDONEZJA");
			break;

			case 170:
				m_pFlag = new CButton(pScreen, "BUTTON_MENU64_PORTUGAL");
			break;

			case 180:
				m_pFlag = new CButton(pScreen, "BUTTON_MENU64_SWEDEN");
			break;

			case 190:
				m_pFlag = new CButton(pScreen, "BUTTON_MENU64_NORWAY");
			break;

			case 200:
				m_pFlag = new CButton(pScreen, "BUTTON_MENU64_DENMARK");
			break;

			default:
				m_pFlag = new CButton(pScreen, "BUTTON_MENU64_ENGLISH");
			break;
		}

		m_pFlag->SetPosition(32,pScreen->iSizeY()-96);
		m_pFlag->SetHotCoords(32,pScreen->iSizeY()-96,96,pScreen->iSizeY()-32);		
	}

	// zaktualizuj informacje o profilu

	pProfile = new CProfile(USERS_FILE);
	pProfile->bLoad();

	m_ucCurrentProfile = pProfile->ucCurrentProfile();

	for (int i=0; i<8; i++)
	{
		pProfile->ucCurrentProfile(i);
		strcpy(m_pUserName[i],pProfile->pGetName());
	}
	
	delete pProfile;
			
	m_bProfileView = false;		// czy przegladamy profile?
	m_bProfileEdit = false;		// czy wpisujemy dane?
	m_bProfileDelete = false;	

	m_bMouseLock = true;

	_pScreen = pScreen;

	_isActive = true;	// dane wczytane
	return 101;
}

//=== deaktualizuje, ale trzyma znaczniki (zwalnia tylko textury)

void eMainMenu::Close(void)
{
	CProfile *pProfile;

	pProfile = new CProfile(USERS_FILE);
	pProfile->bLoad();

	for (int i=0; i<8; i++)
	{
		pProfile->ucCurrentProfile(i);
		pProfile->SetName(m_pUserName[i]);
	}

	pProfile->ucCurrentProfile(m_ucCurrentProfile);

	pProfile->bSave();

	delete pProfile;

	SafeDelete(m_pFlag);	// flaga jest prze³adowywana za ka¿dym razem

	_isActive = false;

}

//=== rysuje pojedyncza klatke

int eMainMenu::Render(unsigned long ulTimer, CMouse *pMouse, unsigned char KEYPRESSED)
{
	int iReturn;
	unsigned char cMobileKey;

	iReturn = 0;
	
	if (m_ulTimerStart == 0)
		m_ulTimerStart = ulTimer;

	if (m_bMouseLock && !pMouse->isLeft())
		m_bMouseLock = false;

	if (!m_bProfileView)	// nie jestesmy w trybie przegladania profili
	{
		m_pBackground->Render();

		if (m_pButtonStart->Render(pMouse)==ON_LEFT && !m_bMouseLock) iReturn = 1;
		if (m_pButtonOptions->Render(pMouse)==ON_LEFT && !m_bMouseLock) iReturn = 2;
		if (m_pButtonTrophy->Render(pMouse)==ON_LEFT && !m_bMouseLock) iReturn = 3; 
		if (m_pButtonHelp->Render(pMouse)==ON_LEFT && !m_bMouseLock) iReturn = 4; 
		if (m_pButtonSupport->Render(pMouse)==ON_LEFT && !m_bMouseLock) iReturn = 5;
		if (m_pButtonExit->Render(pMouse)==ON_LEFT && !m_bMouseLock) iReturn = 6;
		
		if (m_pButtonSwitch->Render(pMouse)==ON_LEFT && !m_bMouseLock)
		{	
			m_bProfileView = true;
			m_bMouseLock = true;	// blokujemy mysz ponownie zeby nie przenosic klikniecia
		}

		m_pFont->Print(32,_pScreen->iSizeY()-32,255,0.03f,0.03f,MAIN_VERSION);	// w rogu wersja gry
		
		if (_pScreen->iSizeX()==1024 && _pScreen->iSizeY()==600)
			m_pFont->Print(m_pFont->iSize(0.1f,m_pUserName[m_ucCurrentProfile]),400,1,0.1f,0.1f,m_pUserName[m_ucCurrentProfile]);		// imie gracza
		
		if (_pScreen->iSizeX()==1024 && _pScreen->iSizeY()==768)
			m_pFont->Print(m_pFont->iSize(0.1f,m_pUserName[m_ucCurrentProfile]),500,1,0.1f,0.1f,m_pUserName[m_ucCurrentProfile]);		// imie gracza


		if (m_pFlag->Render(pMouse)==ON_LEFT && !m_bMouseLock) iReturn = 10;		// przycisk zmiany jezyka 

		m_pParticleManager->Render(ulTimer);

		_pTitle->Render(ulTimer);

		if (ulTimer - m_ulTimerStart<101)
		{
			m_pWall_L->Position((float)-(m_pWall_L->fSizeX()/2),0);
			m_pWall_L->Render();

			m_pWall_R->Position(m_pWall_R->fSizeX()/2,0);
			m_pWall_R->Render();
		}

		if ((ulTimer - m_ulTimerStart>100) && (ulTimer - m_ulTimerStart<10000))
		{

			if ((ulTimer - m_ulTimerStart)<1000)	// czarny fade out tla
			{
				m_pBlack->fAlfa(1.0f-((ulTimer-m_ulTimerStart)*0.001));
				m_pBlack->Render();
			}

			// rozsuwane sciany

			m_pWall_L->Position((float)-(m_pWall_L->fSizeX()/2)-((ulTimer - m_ulTimerStart-100)/6),0);
			m_pWall_L->Render();
	
			m_pWall_R->Position((m_pWall_R->fSizeX()/2)+((ulTimer - m_ulTimerStart)-100)/6,0);
			m_pWall_R->Render();
		}
	}
	else	// przegladamy profile
	{
		if (!m_bProfileDelete && !m_bProfileEdit)	// edycja nazw profilu
		{
			m_pProfileEdit->Render();

			// wypisz du¿ymi literami nazwê g³ównego profilu

			if (_pScreen->iSizeX()==1024 && _pScreen->iSizeY()==600)
				m_pFont->Print(32,64, 1, 0.125f, 0.125f, m_pUserName[m_ucCurrentProfile]);
			
			// wypisujemy nazwy wszystkich profili

			for (int i=0; i<8; i++)
			{
				m_pFont->Print(300,150+(i*32),255, 0.03f, 0.03f, m_pUserName[i]);

				if (pMouse->fMouseX()>300 && pMouse->fMouseX()<700 && pMouse->fMouseY()>(150+(i*32)) && pMouse->fMouseY()<(150+(i*32)+32))
				{

					// 1024x600 1280x600
					
					if (_pScreen->iSizeY()==600) 
						_pArrowR->Position(260,145+(i*32));


					_pArrowR->Render();

					if (pMouse->isLeft())
					{
						CProfile	*pProfile;
		
						m_ucCurrentProfile=i;

						pProfile = new CProfile(USERS_FILE);
						pProfile->bLoad();
						pProfile->ucCurrentProfile(m_ucCurrentProfile);
						pProfile->bSave();
						delete pProfile;
					}
				}

			}

			m_pButtonEdit->SetPosition(250,500);
			m_pButtonEdit->SetHotCoords(250,500,350,600);
			
			if (m_pButtonEdit->Render(pMouse)==ON_LEFT && !m_bMouseLock )	// kasujemy aktualna nazwe bedziemy wprowadzac nowa
			{
				for (int i=0;i<18;i++)
					m_cEditName[i]=0;
				m_cIndex=0;
				m_bProfileEdit = true;
				m_bMouseLock = true;	// zablokuj myszke zeby nie przenosic klikniecia
			}


			m_pButtonYes->SetPosition(450,500);
			m_pButtonYes->SetHotCoords(450,500,550,600);
			
			if (m_pButtonYes->Render(pMouse)==ON_LEFT && !m_bMouseLock)
				m_bProfileView=false;
				
			m_pButtonNo->SetPosition(650,500);
			m_pButtonNo->SetHotCoords(650,500,750,600);
			
			if (m_pButtonNo->Render(pMouse)==ON_LEFT && !m_bMouseLock)
				m_bProfileDelete = true;;

		}
		
		if (m_bProfileDelete)		// kasowanie profilu
		{
			m_pProfileDelete->Render();

			m_pButtonYes->SetPosition(250,500);
			m_pButtonYes->SetHotCoords(250,500,350,600);

			if (m_pButtonYes->Render(pMouse)==ON_LEFT  && !m_bMouseLock)
			{
				CProfile	*pProfile;

				pProfile = new CProfile(USERS_FILE);
				pProfile->bLoad();

				pProfile->ucCurrentProfile(m_ucCurrentProfile);
				pProfile->SetName("EMPTY");
				pProfile->SetLevel(0);
				pProfile->SetScore(0);
				pProfile->SetTotalScore(0);
				pProfile->ulMap(0);

				for (int i=0; i<21; i++)
					pProfile->ucTroophy(i,0);

				pProfile->bSave();

				strcpy(m_pUserName[m_ucCurrentProfile],pProfile->pGetName());

				delete pProfile;


				m_bProfileDelete = false;
			}

			m_pButtonNo->SetPosition(750,500);
			m_pButtonNo->SetHotCoords(750,500,850,600);
			
			if (m_pButtonNo->Render(pMouse)==ON_LEFT  && !m_bMouseLock)
				m_bProfileDelete = false;				
		}
	}

	if (m_bProfileEdit)
	{
		m_pProfileDelete->Render();		// uzywamy tego samego tla co dla profile 

		m_pButtonYes->SetPosition(600,200);
		m_pButtonYes->SetHotCoords(600,200,600+64,200+64);

		m_pFont->Print(300,300,255,0.03f,0.03f,m_cEditName);
		
		if ((ulTimer%100)>50)
			m_pFont->Print(300+(m_cIndex*16),300,255,0.03f,0.03f,".");

		if (m_pButtonYes->Render(pMouse)==ON_LEFT  && !m_bMouseLock)
		{
			m_bProfileEdit = false;

			CProfile	*pProfile;
			pProfile = new CProfile(USERS_FILE);
			pProfile->bLoad();
			pProfile->ucCurrentProfile(m_ucCurrentProfile);
			pProfile->SetName(m_cEditName);
			pProfile->bSave();
			delete pProfile;

			strcpy(m_pUserName[m_ucCurrentProfile],m_cEditName);	// zapamietaj tez w wyswietlanej obecnie tablicy nazw
		}

		cMobileKey = _pMobileKeyboard->cRender(ulTimer,pMouse);
			
		if (cMobileKey!=KEY_NONE) 
			KEYPRESSED = cMobileKey;


		if (KEYPRESSED!=KEY_NONE)	// sprawdzamy stan klawiatury
		{
			if (!m_bKeyLock)
			{
				switch (KEYPRESSED)
				{
					case KEY_A: if (m_bPrevBack && m_cIndex<15 && m_cIndex!=0) m_cIndex++; m_cEditName[m_cIndex] = 'a'; if (m_cIndex<15) m_cIndex++; m_bPrevBack = false; break;
					case KEY_B: if (m_bPrevBack && m_cIndex<15 && m_cIndex!=0) m_cIndex++; m_cEditName[m_cIndex] = 'b'; if (m_cIndex<15) m_cIndex++; m_bPrevBack = false; break;
					case KEY_C: if (m_bPrevBack && m_cIndex<15 && m_cIndex!=0) m_cIndex++;	m_cEditName[m_cIndex] = 'c'; if (m_cIndex<15) m_cIndex++; m_bPrevBack = false; break;
					case KEY_D: if (m_bPrevBack && m_cIndex<15 && m_cIndex!=0) m_cIndex++;	m_cEditName[m_cIndex] = 'd'; if (m_cIndex<15) m_cIndex++; m_bPrevBack = false; break;
					case KEY_E: if (m_bPrevBack && m_cIndex<15 && m_cIndex!=0) m_cIndex++;	m_cEditName[m_cIndex] = 'e'; if (m_cIndex<15) m_cIndex++; m_bPrevBack = false; break;
					case KEY_F: if (m_bPrevBack && m_cIndex<15 && m_cIndex!=0) m_cIndex++;	m_cEditName[m_cIndex] = 'f'; if (m_cIndex<15) m_cIndex++; m_bPrevBack = false; break;
					case KEY_G: if (m_bPrevBack && m_cIndex<15 && m_cIndex!=0) m_cIndex++;	m_cEditName[m_cIndex] = 'g'; if (m_cIndex<15) m_cIndex++; m_bPrevBack = false; break;
					case KEY_H: if (m_bPrevBack && m_cIndex<15 && m_cIndex!=0) m_cIndex++;	m_cEditName[m_cIndex] = 'h'; if (m_cIndex<15) m_cIndex++; m_bPrevBack = false; break;
					case KEY_I: if (m_bPrevBack && m_cIndex<15 && m_cIndex!=0) m_cIndex++;	m_cEditName[m_cIndex] = 'i'; if (m_cIndex<15) m_cIndex++; m_bPrevBack = false; break;
					case KEY_J: if (m_bPrevBack && m_cIndex<15 && m_cIndex!=0) m_cIndex++;	m_cEditName[m_cIndex] = 'j'; if (m_cIndex<15) m_cIndex++; m_bPrevBack = false; break;
					case KEY_K: if (m_bPrevBack && m_cIndex<15 && m_cIndex!=0) m_cIndex++;	m_cEditName[m_cIndex] = 'k'; if (m_cIndex<15) m_cIndex++; m_bPrevBack = false; break;
					case KEY_L: if (m_bPrevBack && m_cIndex<15 && m_cIndex!=0) m_cIndex++;	m_cEditName[m_cIndex] = 'l'; if (m_cIndex<15) m_cIndex++; m_bPrevBack = false; break;
					case KEY_M: if (m_bPrevBack && m_cIndex<15 && m_cIndex!=0) m_cIndex++;	m_cEditName[m_cIndex] = 'm'; if (m_cIndex<15) m_cIndex++; m_bPrevBack = false; break;
					case KEY_N: if (m_bPrevBack && m_cIndex<15 && m_cIndex!=0) m_cIndex++;	m_cEditName[m_cIndex] = 'n'; if (m_cIndex<15) m_cIndex++; m_bPrevBack = false; break;
					case KEY_O: if (m_bPrevBack && m_cIndex<15 && m_cIndex!=0) m_cIndex++;	m_cEditName[m_cIndex] = 'o'; if (m_cIndex<15) m_cIndex++; m_bPrevBack = false; break;
					case KEY_P: if (m_bPrevBack && m_cIndex<15 && m_cIndex!=0) m_cIndex++;	m_cEditName[m_cIndex] = 'p'; if (m_cIndex<15) m_cIndex++; m_bPrevBack = false; break;
					case KEY_Q: if (m_bPrevBack && m_cIndex<15 && m_cIndex!=0) m_cIndex++;	m_cEditName[m_cIndex] = 'q'; if (m_cIndex<15) m_cIndex++; m_bPrevBack = false; break;
					case KEY_R: if (m_bPrevBack && m_cIndex<15 && m_cIndex!=0) m_cIndex++;	m_cEditName[m_cIndex] = 'r'; if (m_cIndex<15) m_cIndex++; m_bPrevBack = false; break;
					case KEY_S: if (m_bPrevBack && m_cIndex<15 && m_cIndex!=0) m_cIndex++;	m_cEditName[m_cIndex] = 's'; if (m_cIndex<15) m_cIndex++; m_bPrevBack = false; break;
					case KEY_T: if (m_bPrevBack && m_cIndex<15 && m_cIndex!=0) m_cIndex++;	m_cEditName[m_cIndex] = 't'; if (m_cIndex<15) m_cIndex++; m_bPrevBack = false; break;
					case KEY_U: if (m_bPrevBack && m_cIndex<15 && m_cIndex!=0) m_cIndex++;	m_cEditName[m_cIndex] = 'u'; if (m_cIndex<15) m_cIndex++; m_bPrevBack = false; break;
					case KEY_V: if (m_bPrevBack && m_cIndex<15 && m_cIndex!=0) m_cIndex++;	m_cEditName[m_cIndex] = 'v'; if (m_cIndex<15) m_cIndex++; m_bPrevBack = false; break;
					case KEY_W: if (m_bPrevBack && m_cIndex<15 && m_cIndex!=0) m_cIndex++;	m_cEditName[m_cIndex] = 'w'; if (m_cIndex<15) m_cIndex++; m_bPrevBack = false; break;
					case KEY_X: if (m_bPrevBack && m_cIndex<15 && m_cIndex!=0) m_cIndex++;	m_cEditName[m_cIndex] = 'x'; if (m_cIndex<15) m_cIndex++; m_bPrevBack = false; break;
					case KEY_Y: if (m_bPrevBack && m_cIndex<15 && m_cIndex!=0) m_cIndex++;	m_cEditName[m_cIndex] = 'y'; if (m_cIndex<15) m_cIndex++; m_bPrevBack = false; break;
					case KEY_Z: if (m_bPrevBack && m_cIndex<15 && m_cIndex!=0) m_cIndex++;	m_cEditName[m_cIndex] = 'z'; if (m_cIndex<15) m_cIndex++; m_bPrevBack = false; break;
					case KEY_0: if (m_bPrevBack && m_cIndex<15 && m_cIndex!=0) m_cIndex++;	m_cEditName[m_cIndex] = '0'; if (m_cIndex<15) m_cIndex++; m_bPrevBack = false; break;
					case KEY_1: if (m_bPrevBack && m_cIndex<15 && m_cIndex!=0) m_cIndex++;	m_cEditName[m_cIndex] = '1'; if (m_cIndex<15) m_cIndex++; m_bPrevBack = false; break;
					case KEY_2: if (m_bPrevBack && m_cIndex<15 && m_cIndex!=0) m_cIndex++;	m_cEditName[m_cIndex] = '2'; if (m_cIndex<15) m_cIndex++; m_bPrevBack = false; break;
					case KEY_3: if (m_bPrevBack && m_cIndex<15 && m_cIndex!=0) m_cIndex++;	m_cEditName[m_cIndex] = '3'; if (m_cIndex<15) m_cIndex++; m_bPrevBack = false; break;
					case KEY_4: if (m_bPrevBack && m_cIndex<15 && m_cIndex!=0) m_cIndex++;	m_cEditName[m_cIndex] = '4'; if (m_cIndex<15) m_cIndex++; m_bPrevBack = false; break;
					case KEY_5: if (m_bPrevBack && m_cIndex<15 && m_cIndex!=0) m_cIndex++;	m_cEditName[m_cIndex] = '5'; if (m_cIndex<15) m_cIndex++; m_bPrevBack = false; break;
					case KEY_6: if (m_bPrevBack && m_cIndex<15 && m_cIndex!=0) m_cIndex++;	m_cEditName[m_cIndex] = '6'; if (m_cIndex<15) m_cIndex++; m_bPrevBack = false; break;
					case KEY_7: if (m_bPrevBack && m_cIndex<15 && m_cIndex!=0) m_cIndex++;	m_cEditName[m_cIndex] = '7'; if (m_cIndex<15) m_cIndex++; m_bPrevBack = false; break;
					case KEY_8: if (m_bPrevBack && m_cIndex<15 && m_cIndex!=0) m_cIndex++;	m_cEditName[m_cIndex] = '8'; if (m_cIndex<15) m_cIndex++; m_bPrevBack = false; break;
					case KEY_9: if (m_bPrevBack && m_cIndex<15 && m_cIndex!=0) m_cIndex++;	m_cEditName[m_cIndex] = '9'; if (m_cIndex<15) m_cIndex++; m_bPrevBack = false; break;
//					case KEY_SPACE:  if (m_bPrevBack && m_cIndex<15  && m_cIndex!=0) m_cIndex++; m_cEditName[m_cIndex] = ' '; if (m_cIndex<15) m_cIndex++;  m_bPrevBack = false; break;
					
					case KEY_DELETE: 
						m_cEditName[m_cIndex]=' '; 

						if (m_cIndex!=0 )
						{
							m_cIndex--;
							m_bPrevBack = true;
						}

					break;

					case KEY_ENTER:
						m_bProfileEdit = false;
						CProfile	*pProfile;
						pProfile = new CProfile(USERS_FILE);
						pProfile->bLoad();		
						pProfile->ucCurrentProfile(m_ucCurrentProfile);
						pProfile->SetName(m_cEditName);
						pProfile->bSave();
						delete pProfile;

						strcpy(m_pUserName[m_ucCurrentProfile],m_cEditName);	// zapamietaj tez w wyswietlanej obecnie tablicy nazw
					break;

				}													
				m_bKeyLock = true;
			}
		}
		else
		{
			m_bKeyLock = false;
		}

	}


	return iReturn;
}

void eMainMenu::ucLanguage(unsigned char _lang)
{
	m_ucLanguage = _lang;
}

//end
