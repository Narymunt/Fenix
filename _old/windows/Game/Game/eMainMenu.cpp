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
	m_pProfileName = NULL;
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

}

//=== destruktor 

eMainMenu::~eMainMenu()
{
	Close();
	SafeDelete(_pMobileKeyboard);
	SafeDelete(m_pFont);
}

//=== aktualizuje i wczytuje dane

int eMainMenu::Open(CScreen *pScreen)
{		
	CProfile *pProfile;

	if (m_pProfileEdit==NULL)
	{
		m_pProfileEdit = new CSprite("data/profile_edit.png");
		m_pProfileDelete = new CSprite("data/profile_delete.png");
		m_pProfileName = new CSprite("data/edit_name.png");
		return 5;
	}

	if (m_pBackground==NULL)
	{
		m_pBackground = new CSprite(pScreen,"GFX_MMENU_SCREEN");
		m_pBlack = new CSprite(pScreen,"GFX_BLACK100_SCREEN");	// czarny fade
		m_pFont = new CSpriteFont(pScreen);
		return 10;
	}

	if (m_pWall_L==NULL)
	{
		m_pWall_L = new CSprite(pScreen,"WALL_L");
		m_pWall_R = new CSprite(pScreen,"WALL_R");
		return 15;
	}

	if (m_pButtonStart==NULL)
	{
		m_pButtonStart = new CButton(pScreen,"BUTTON_START");
		_pMobileKeyboard->Open(pScreen);

		return 20;
	}

	if (m_pButtonOptions==NULL)
	{
		m_pButtonOptions = new CButton(pScreen,"BUTTON_SETTINGS");
		return 25;
	}

	if (m_pButtonTrophy==NULL)
	{
		m_pButtonTrophy = new CButton(pScreen,"BUTTON_TROPHY");
		return 30;
	}

	if (m_pButtonHelp==NULL)
	{
		m_pButtonHelp = new CButton(pScreen,"BUTTON_HELP");
		return 35;
	}

	if (m_pButtonSupport==NULL)
	{
		m_pButtonSupport= new CButton(pScreen,"BUTTON_SUPPORT");
		return 40;
	}
	
	if (m_pButtonExit==NULL)
	{
		m_pButtonExit = new CButton(pScreen,"BUTTON_EXIT");
		return 45;
	}

	if (m_pButtonSwitch==NULL)
	{
		m_pButtonSwitch = new CButton(pScreen,"BUTTON_EDIT");
		return 50;
	}

	if (m_pButtonYes==NULL)
	{
		m_pButtonYes = new CButton( "data/yes.png","data/yes_over.png","data/yes_clicked.png");
		m_pButtonYes->SetPosition(512-64,500);
		m_pButtonYes->SetHotCoords(512-64,500,512+64,628);
		return 55;
	}

	if (m_pButtonNo==NULL)
	{
		m_pButtonNo = new CButton( "data/no.png", "data/no_over.png", "data/no_clicked.png");
		m_pButtonNo->SetPosition(768,500);
		m_pButtonNo->SetHotCoords(768,500,768+128,628);
		return 60;
	}
	
	if (m_pButtonEdit==NULL)
	{
		m_pButtonEdit = new CButton(pScreen,"BUTTON_EDIT");

		m_pParticleManager = new CParticle2DManager((char*)"data/particle.png", 50, 
                                               -100,-100,1024,768,
                                               0.01f,0.01f,0.3f,0.3f,
                                               0.5f, -.001f,.001f,
                                               0.5f, -5.0f,5.0f,
                                               1000,10000,pScreen);

		return 65;
	}

	if (_pTitle==NULL)
	{
		_pTitle = new CSprite(pScreen,"TITLE");
		return 70;
	}

	// wczytaj odpowiednia flage

	if (m_pFlag == NULL)
	{
		switch (m_ucLanguage)
		{
			case 10:
				m_pFlag = new CButton("data/l_en.png","data/l_en.png","data/l_en.png");
			break;

			case 20:
				m_pFlag = new CButton("data/l_ru.png","data/l_ru.png","data/l_ru.png");
			break;

			case 30:
				m_pFlag = new CButton("data/l_de.png","data/l_de.png","data/l_de.png");
			break;

			case 40:
				m_pFlag = new CButton("data/l_fr.png","data/l_fr.png","data/l_fr.png");
			break;

			case 50:
				m_pFlag = new CButton("data/l_it.png","data/l_it.png","data/l_it.png");
			break;

			case 60:
				m_pFlag = new CButton("data/l_es.png","data/l_es.png","data/l_es.png");
			break;

			case 70:
				m_pFlag = new CButton("data/l_pl.png","data/l_pl.png","data/l_pl.png");
			break;

			case 80:
				m_pFlag = new CButton("data/l_tu.png","data/l_tu.png","data/l_tu.png");
			break;

			case 90:
				m_pFlag = new CButton("data/l_jp.png","data/l_jp.png","data/l_jp.png");
			break;

			case 100:
				m_pFlag = new CButton("data/l_ko.png","data/l_ko.png","data/l_ko.png");
			break;

			case 110:
				m_pFlag = new CButton("data/l_ch.png","data/l_ch.png","data/l_ch.png");
			break;

			case 120:
				m_pFlag = new CButton("data/l_in.png","data/l_in.png","data/l_in.png");
			break;

			case 130:
				m_pFlag = new CButton("data/l_ar.png","data/l_ar.png","data/l_ar.png");
			break;
	
			case 140:
				m_pFlag = new CButton("data/l_is.png","data/l_is.png","data/l_is.png");
			break;

			case 150:
				m_pFlag = new CButton("data/l_br.png","data/l_br.png","data/l_br.png");
			break;

			case 160:
				m_pFlag = new CButton("data/l_id.png","data/l_id.png","data/l_id.png");
			break;

			case 170:
				m_pFlag = new CButton("data/l_po.png","data/l_po.png","data/l_po.png");
			break;

			case 180:
				m_pFlag = new CButton("data/l_se.png","data/l_se.png","data/l_se.png");
			break;

			case 190:
				m_pFlag = new CButton("data/l_no.png","data/l_no.png","data/l_no.png");
			break;

			case 200:
				m_pFlag = new CButton("l_dk.png","l_dk.png","l_dk.png");
			break;

			default:
				m_pFlag = new CButton("data/l_en.png","data/l_en.png","data/l_en.png");
			break;
		}

		m_pFlag->SetPosition(960,704);
		m_pFlag->SetHotCoords(960,704,1024,768);
		
		return 100;
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

	_isActive = true;	// dane wczytane
	return 101;
}

//=== deaktualizuje, ale trzyma znaczniki (zwalnia tylko textury)

void eMainMenu::Close(void)
{
	CProfile *pProfile;

	SafeDelete(m_pBackground);
	SafeDelete(m_pBlack);
	SafeDelete(_pTitle);
	
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

	SafeDelete(m_pFlag);

	SafeDelete(m_pProfileEdit);
	SafeDelete(m_pProfileDelete);
	SafeDelete(m_pProfileName);

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

	_pMobileKeyboard->Close();

	SafeDelete(m_pParticleManager);

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


	if (!m_bProfileView)	// nie jestesmy w trybie przegladania profili
	{
		m_pBackground->Render();

		if (m_pButtonStart->Render(pMouse)==ON_LEFT) iReturn = 1;
		if (m_pButtonOptions->Render(pMouse)==ON_LEFT) iReturn = 2;
		if (m_pButtonTrophy->Render(pMouse)==ON_LEFT) iReturn = 3; 
		if (m_pButtonHelp->Render(pMouse)==ON_LEFT) iReturn = 4; 
		if (m_pButtonSupport->Render(pMouse)==ON_LEFT) iReturn = 5;
		if (m_pButtonExit->Render(pMouse)==ON_LEFT) iReturn = 6;
		if (m_pButtonSwitch->Render(pMouse)==ON_LEFT) m_bProfileView = true;;

		m_pFont->Print(10,732,255,0.03f,0.03f,MAIN_VERSION);	// w rogu wersja gry
		m_pFont->Print(m_pFont->iSize(0.1f,m_pUserName[m_ucCurrentProfile]),500,255,0.1f,0.1f,m_pUserName[m_ucCurrentProfile]);
		
		if (m_pFlag->Render(pMouse)==ON_LEFT) iReturn = 10;		// przycisk zmiany jezyka 

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

			for (int i=0; i<8; i++)
			{
				m_pFont->Print(300,150+(i*32),255, 0.03f, 0.03f, m_pUserName[i]);

				if (m_ucCurrentProfile==i)
					m_pFont->Print(500,150+(i*32),255, 0.03f, 0.03f, "selected");

				if (pMouse->fMouseX()>300 && pMouse->fMouseX()<700 && pMouse->fMouseY()>(150+(i*32)) && pMouse->fMouseY()<(150+(i*32)+32))
				{
					m_pFont->Print(600,150+(i*32),255, 0.03f, 0.03f, "...");

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
			
			if (m_pButtonEdit->Render(pMouse)==ON_LEFT)	// kasujemy aktualna nazwe bedziemy wprowadzac nowa
			{
				for (int i=0;i<18;i++)
					m_cEditName[i]=0;
				m_cIndex=0;
				m_bProfileEdit = true;
			}


			m_pButtonYes->SetPosition(450,500);
			m_pButtonYes->SetHotCoords(450,500,550,600);
			
			if (m_pButtonYes->Render(pMouse)==ON_LEFT)
				m_bProfileView=false;
				
			m_pButtonNo->SetPosition(650,500);
			m_pButtonNo->SetHotCoords(650,500,750,600);
			
			if (m_pButtonNo->Render(pMouse)==ON_LEFT)
				m_bProfileDelete = true;;

		}
		
		if (m_bProfileDelete)		// kasowanie profilu
		{
			m_pProfileDelete->Render();

			m_pButtonYes->SetPosition(250,500);
			m_pButtonYes->SetHotCoords(250,500,350,600);

			if (m_pButtonYes->Render(pMouse)==ON_LEFT)
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
			
			if (m_pButtonNo->Render(pMouse)==ON_LEFT)
				m_bProfileDelete = false;				
		}
	}

	if (m_bProfileEdit)
	{
		m_pProfileName->Render();

		m_pButtonYes->SetPosition(600,200);
		m_pButtonYes->SetHotCoords(600,200,600+64,200+64);

		m_pFont->Print(300,300,255,0.03f,0.03f,m_cEditName);
		
		if ((ulTimer%100)>50)
			m_pFont->Print(300+(m_cIndex*16),300,255,0.03f,0.03f,".");

		if (m_pButtonYes->Render(pMouse)==ON_LEFT)
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
