#include "MainMenu.h"

//=== onstruktor

CMainMenu::CMainMenu(CScreen *pScreen) :
_pBackground(0), _pTitle(0),
_pBlack(0), _pWhite(0),
_pWall_L(0), _pWall_R(0),
_pProfileDelete(0), _pProfileEdit(0),
_pButtonStart(0), _pButtonOptions(0),
_pButtonHelp(0), _pButtonSupport(0),
_pButtonSwitch(0), _pButtonTroophy(0),
_pButtonYes(0), _pButtonNo(0),
_pFont(0), _pParticleManager(0),
_pFlag(0), _pFXManager(0),
_pMobileKeyboard(0), _pButtonEdit(0),
_isFirstRun(true)
{
	CProfile *pProfile;

	_pScreen = pScreen;
	_isActive = false;
	_isMouseLock = true;
	_ulTimerStart = 0;

	m_bPrevBack = false;		// nie bylo backspace

	// wczytanie odpowiedniego profilu

	pProfile = new CProfile(USERS_FILE);
	pProfile->bLoad();

	m_ucCurrentProfile = pProfile->ucCurrentProfile();

	for (int i=0; i<8; i++)
	{
		pProfile->ucCurrentProfile(i);
		strcpy(m_pUserName[i],pProfile->pGetName());
	}

	delete pProfile;

	_bProfileView = false;		// czy przegladamy profile? ustawione celowo, zeby pokazywal 100 wczytania
	_bProfileEdit = false;		// czy wpisujemy dane?
	_bProfileDelete = false;

	_ucLanguage = 0;

	for (int i=0; i<18; i++)
		_cEditName[i] = 0;

	_cIndex = 0;

	_pMobileKeyboard = new CMobileKeyboard(0);

}

//=== destructor 

CMainMenu::~CMainMenu()
{
	Close();
}

//=== load and prepare data

int CMainMenu::Open(void)
{
	CProfile *pProfile;

	if (_pProfileEdit == NULL)
	{
		_pProfileEdit = new CSprite(_pScreen,"profiled");
		_pProfileEdit->FullScreen(_pScreen);

		_pProfileDelete = new CSprite(_pScreen,"profidel");
		_PProfileDelete->FullScreen(_pScreen);

		return 10;
	}

	if (_pBackground == NULL)
	{
		_pBackground = new CSprite(_pScreen,"e_mainmenu");
		_pBackground->Fullscreen(_pScreen);

		_pBlack = new CSprite("black.png");
		_pBlack->Resize(0, 0, _pScreen->iSizeX(), _pScreen->iSizeY());

		_pWhite = new CSprite("white.png");
		_pWhite->Fullscreen(_pScreen);

		_pFont = new CSpriteFont(_pScreen);

		return 20;
	}

	if (_pWall_L == NULL)
	{
		_pWall_L = new CSprite(_pScreen,"walll");
		_pWall_L->Fullscreen(_pScreen);

		_pWall_R = new CSprite(_pScreen,"wallr");
		_pWall_R->Fullscreen(_pScreen);

		return 30;
	}

	if (_pButtonStart == NULL)
	{
		_pButtonStart = new CButton(_pScreen, "button_start", "button_start_over", "button_start_click");
		_pMobileKeyboard->Open(_pScreen);

		return 40;
	}

	if (_pButtonOptions == NULL)
	{
		_pButtonOptions = new CButton(_pScreen, "button_settings");

		return 50;
	}

	if (_pButtonTroophy == NULL)
	{
		_pButtonTroophy = new CButton(_pScreen, "button_troophy");

		return 60;
	}

	if (_pButtonHelp == NULL)
	{
		_pButtonHelp = new CButton(_pScreen, "button_help");
		return 65;
	}

	if (_pButtonSupport == NULL)
	{
		_pButtonSupport = new CButton(_pScreen, "button_support");
		return 70;
	}

	if (_pButtonSwitch == NULL)
	{
		_pButtonSwitch = new CButton(_pScreen, "button_edit");
		return 80;
	}

	if (_pButtonYes == NULL)
	{
		_pButtonYes = new CButton(_pScreen,"yes");
		return 85;
	}

	if (_pButtonNo == NULL)
	{
		_pButtonNo = new CButton(_pScreen,"no");
		return 90;
	}

	if (_pButtonEdit == NULL)
	{
		_pButtonEdit = new CButton(_pScreen,"button_edit")

		_pParticleManager = new CParticle2DManager((char*)"k6.png", 50,
                                               -100,-100,pScreen->iSizeX()+100,pScreen->iSizeY()+100,
                                               0.01f,0.01f,0.3f,0.3f,
                                               0.5f, -.001f,.001f,
                                               0.5f, -.5f,.5f,
                                               1000,10000,pScreen);

		_pParticleManager->Color(0.95f, 0.82f, 0.0f, 1.0f);

		return 95;
	}

	if (_pTitle == NULL)
	{
		_pTitle = new CSprite(_pScreen, "title");
		return 100;
	}

	// wczytaj odpowiednia flage

	if (_pFlag == NULL)
	{
		switch (_ucLanguage)
		{
			case 10:
				m_pFlag = new CButton(pScreen, "button_en64");
			break;

			case 20:
				m_pFlag = new CButton(pScreen, "button_ru64");
			break;

			case 30:
				m_pFlag = new CButton(pScreen, "button_de64");
			break;

			case 40:
				m_pFlag = new CButton(pScreen, "button_fr64");
			break;

			case 50:
				m_pFlag = new CButton(pScreen, "button_it64");
			break;

			case 60:
				m_pFlag = new CButton(pScreen, "button_es64");
			break;

			case 70:
				m_pFlag = new CButton(pScreen, "button_pl64");
			break;

			case 80:
				m_pFlag = new CButton(pScreen, "button_tu64");
			break;

			case 90:
				m_pFlag = new CButton(pScreen, "button_jp64");
			break;

			case 100:
				m_pFlag = new CButton(pScreen, "button_ko64");
			break;

			case 110:
				m_pFlag = new CButton(pScreen, "button_cn64");
			break;

			case 120:
				m_pFlag = new CButton(pScreen, "button_in64");
			break;

			case 130:
				m_pFlag = new CButton(pScreen, "button_ar64");
			break;

			case 140:
				m_pFlag = new CButton(pScreen, "button_is64");
			break;

			case 150:
				m_pFlag = new CButton(pScreen, "button_br64");
			break;

			case 160:
				m_pFlag = new CButton(pScreen, "button_id64");
			break;

			case 170:
				m_pFlag = new CButton(pScreen, "button_po64");
			break;

			case 180:
				m_pFlag = new CButton(pScreen, "button_se64");
			break;

			case 190:
				m_pFlag = new CButton(pScreen, "button_no64");
			break;

			case 200:
				m_pFlag = new CButton(pScreen, "button_dk64");
			break;

			default:
				m_pFlag = new CButton(pScreen, "button_en64");
			break;
		}

		m_pFlag->SetPosition(32,pScreen->iSizeY()-96);
		m_pFlag->SetHotCoords(32,pScreen->iSizeY()-96,96,pScreen->iSizeY()-32);
	}

	// zaktualizuj informacje o profilu

	pProfile = new CProfile(USERS_FILE);
	pProfile->bLoad();

	_ucCurrentProfile = pProfile->ucCurrentProfile();

	for (int i=0; i<8; i++)
	{
		pProfile->ucCurrentProfile(i);
		strcpy(_pUserName[i],pProfile->pGetName());
	}

	delete pProfile;

	_bProfileView = false;		// czy przegladamy profile?
	_bProfileEdit = false;		// czy wpisujemy dane?
	_bProfileDelete = false;

	_pFXManager = new CFXManager(pScreen);

	_pScreen = pScreen;

	_isActive = true;
	_isMouseLock = true;
	_ulTimerStart = 0;

	return 101;
}

//=== release data

void CMainMenu::Close(void)
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

	SafeDelete(m_pFlag);	// flaga jest prze≥adowywana za kaødym razem

	SafeDelete(_pFXManager);

	SafeDelete(_pBackground);
	SafeDelete(_pTitle);

	SafeDelete(_pBlack);
	SafeDelete(_pWhite);

	SafeDelete(_pWall_L);
	SafeDelete(_pWall_R);

	SafeDelete(_pButtonStart);
	SafeDelete(_pButtonOptions);
	SafeDelete(_pButtonTroophy);
	SafeDelete(_pButtonHelp);
	SafeDelete(_pButtonSupport);

	SafeDelete(_pButtonSwitch);
	SafeDelete(_pButtonYes);
	SafeDelete(_pButtonNo);
	SafeDelete(_pButtonEdit);

	SafeDelete(_pProfileEdit);
	SafeDelete(_pProfileDelete);

	SafeDelete(_pFont);
	SafeDelete(_pParticleManager);

	SafeDelete(_pMobileKeyboard);

	_isActive = false;
	_isMouseLock = true;
}

// rysuj ekran

int CMainMenu::iRender(unsigned long ulTimer, CTouch *pTouch)
{
	int iReturn = 0;
	int iDelta;

	if (!_isActive)
		Open();

	if (!pTouch->isTouch())
		_isMouseLock = false;

	if (_ulTimerStart == 0)
		_ulTimerStart = ulTimer;

	iDelta = ulTimer - _ulTimerStart;

	if (!_isProfileView)			// nie jestesmy w trybie przegladania profili
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

		_pFont->Print(25,300,1, 0.1f, 0.1f, _pUserName[_ucCurrentProfile]);

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

	} // if (!_isProfileView)

	return iReturn;
}

