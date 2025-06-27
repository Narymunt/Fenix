#pragma once

#include "config.h"

#include <time.h>
#include "KPTK.h"
#include "KMiscTools.h"
#include "KGraphic.h"
#include "KSound.h"
#include "KMusic.h"
#include "KInput.h"

#include "GameObject.h"
#include "TouchButton.h"
#include "SpriteFont.h"
#include "Touch.h"
#include "Sprite.h"
#include "Anim.h"
#include "MobileKeyboard.h"
#include "Particle2DManager.h"
#include "FXManager.h"
#include "Profile.h"
#include "HighScore.h"

// stan w trakcie wczytywania zasobów

class eMainMenu : public CGameObject
{
	
public: 
	
    eMainMenu();
    ~eMainMenu();            // destruktor automatycznie zamyka stan
    
    int Open(int _iOS);                                        // otwiera stan
    void Close(void);                                           // zamyka stan

    int Render(CTouch *pTouch, unsigned long ulTimer);       // render zwraca info czy powinien być zamknięty i/lub przejść do innego stanu
    
    inline void ucLanguage(unsigned char c) { _ucLanguage = c; }
    inline unsigned char ucLanguage(void) { return _ucLanguage; }  
    
private:	

	bool                            _isProfileView;                     // czy przegladamy profile?
	bool                            _isProfileEdit;                     // czy wpisujemy dane?
	bool                            _isProfileDelete;                   // czy kasujemy profil ?

    bool                            _bPrevBack;                         // backspace na ostatniej literze dziala inaczej, potrzebujemy flage do sprawdzania
    bool                            _isFirstRun;                        // czy pierwszy raz pojawia się menu ? jeżeli tak to rozsuwamy ściany
    
	char                            _cEditName[18];                     // nowa nazwa gracza
	char                            _cIndex;                            // ktory znak teraz piszemy ?
	
    
    
	CSprite                         *_pBackground;
    
	CSprite                         *_pBlack;
	CSprite                         *_pWhite;		// bialy 100%
    
	CSprite                         *_pArrowR;		// strzalka pokazujaca w prawo
    
	CSprite                         *_pTitle;
    
	CSprite                         *_pProfileEdit;
	CSprite                         *_pProfileDelete;
    
	CSprite                         *_pWall_L;	// rozsuwane sciany
	CSprite                         *_pWall_R;
    
	CTouchButton					*_pButtonStart;
	CTouchButton					*_pButtonOptions;
	CTouchButton					*_pButtonTrophy;
	CTouchButton					*_pButtonHelp;
	CTouchButton					*_pButtonSupport;
    
	CTouchButton					*_pButtonSwitch;
	CTouchButton					*_pButtonYes;				// przycisk akceptacji
	CTouchButton					*_pButtonNo;				// przycisk odmowy
	CTouchButton					*_pButtonEdit;				// przycisk edycji - maszyna do pisania
    
	CSpriteFont                     *_pFont;
    
	unsigned long                   _ulTimerStart;	// poczatek
    
	char                            _pUserName[8][20];
	unsigned char                   _ucCurrentProfile;
    
	bool                            _bMouseLock;
	bool                            _bKeyLock;		// blokada klawiatury
    
	unsigned char                   _ucLanguage;		// w prawym dolnym rogu wyswietlana jest odpowiednia flaga
	CButton                         *_pFlag;				// klikniecie w ten przycisk cofa do menu wyboru jezyka
    
	CMobileKeyboard                 *_pMobileKeyboard;	// nasza klawiaturka
    
	CParticle2DManager              *_pParticleManager;
    
	CFXManager                      *_pFXManager;

    
};

