// main menu

#pragma once

#include "Game.h"
#include "GameObject.h"
#include "OGL.h"
#include "Mouse.h"
#include "Button.h"
#include "Sprite.h"
#include "Screen.h"
#include "Particle2DManager.h"
#include "MobileKeyboard.h"
#include "SpriteFont.h"
#include "Profile.h"
#include "FXManager.h"

class eMainMenu : public CGameObject
{
public:
	eMainMenu();
	~eMainMenu();

	int		Open(CScreen *pScreen);		// load data
	void	Close(void);				// unload 

	int		Render(unsigned long lTimer, CMouse *pMouse, unsigned char KEYPRESSED);		// render frame																					

	// rysuje pojedyncza klatke i zwraca sygnal co dalej 

	// klawiatura w formie klawiszy dostepna jest tylko w komputerach
	// generalnie powinno to byc wyrzucone do osobnej klasy, tak jak myszka
	// static KEYPRESSED zadeklarowany w main.h nie przenosi wartosci jak powinien

	void	ucLanguage(unsigned char _lang);


private:

	bool					m_bProfileView;		// czy przegladamy profile?
	bool					m_bProfileEdit;		// czy wpisujemy dane?
	bool					m_bProfileDelete;	// czy kasujemy profil ? 

	char					m_cEditName[18];	// nowa nazwa gracza
	char					m_cIndex;			// ktory znak teraz piszemy ?
	bool					m_bPrevBack;		// backspace na ostatniej literze dziala inaczej, potrzebujemy flage do sprawdzania

	CSprite					*m_pBackground;	

	CSprite					*m_pBlack;
	CSprite					*m_pWhite;		// bialy 100%

	CSprite					*_pArrowR;		// strzalka pokazujaca w prawo

	CSprite					*_pTitle;

	CSprite					*m_pProfileEdit;
	CSprite					*m_pProfileDelete;

	CSprite					*m_pWall_L;	// rozsuwane sciany
	CSprite					*m_pWall_R;

	CButton					*m_pButtonStart;
	CButton					*m_pButtonOptions;
	CButton					*m_pButtonTrophy;
	CButton					*m_pButtonHelp;
	CButton					*m_pButtonExit;
	CButton					*m_pButtonSupport;

	CButton					*m_pButtonSwitch;
	CButton					*m_pButtonYes;				// przycisk akceptacji
	CButton					*m_pButtonNo;				// przycisk odmowy
	CButton					*m_pButtonEdit;				// przycisk edycji - maszyna do pisania

	CSpriteFont				*m_pFont;

	unsigned long			m_ulTimerStart;	// poczatek

	char					m_pUserName[8][20];
	unsigned char			m_ucCurrentProfile;

	bool					m_bMouseLock;
	bool					m_bKeyLock;		// blokada klawiatury

	unsigned char			m_ucLanguage;		// w prawym dolnym rogu wyswietlana jest odpowiednia flaga
	CButton					*m_pFlag;				// klikniecie w ten przycisk cofa do menu wyboru jezyka

	CMobileKeyboard			*_pMobileKeyboard;	// nasza klawiaturka

	CParticle2DManager		*m_pParticleManager;

	CScreen					*_pScreen;			// do zapamietania referencja

	CFXManager				*_pFXManager;

};

