// MainMenu - glowne menu gry

#pragma once

#include "Main.h"
#include "State.h"
#include "../gfx/Screen.h"
#include "../gfx/Button.h"
#include "../gfx/Sprite.h"
#include "../control/Touch.h"
#include "Profile.h"

class CMainMenu : public CState
{

public:

	CMainMenu(CScreen *pScreen);
	~CMainMenu();

	int 		Open(void);			// load
	void		Close(void);		// unload

	int			iRender(unsigned long ulTimer, CTouch *pTouch);

    inline void ucLanguage(unsigned char c) { _ucLanguage = c; }
    inline unsigned char ucLanguage(void) { return _ucLanguage; }

protected:

	bool 				_bProfileView;				// czy przegladamy profile ?
	bool				_bProfileEdit;				// czy wpisujemy dane ?
	bool				_bProfileDelete;			// czy kasujemy profil ?

	char				_cEditName[18];				// nowa nazwa gracza
	char				_cIndex;					// ktory znak teraz piszemy ?
	bool				_bPrevBack;					// backspace na ostatniej literze dzia¸a inaczej

	bool				_isFirstRun;				// czy to pierwsze uruchomienie ?

	CSprite				*_pBackground;				// tlo z logiem gry
	CSprite				*_pTitle;					// tytu¸ gry

	CSprite				*_pBlack;					// czarny ekran
	CSprite				*_pWhite;					// bialy ekran

	CSprite				*_pWall_L;					// rozsuwane æciany
	CSprite				*_pWall_R;

	CSprite				*_pProfileEdit;				// tlo do edycji profilu
	CSprite				*_pProfileDelete;			// tlo do kasowania profilu

	CButton				*_pButtonStart;
	CButton				*_pButtonOptions;
	CButton				*_pButtonHelp;
	CButton				*_pButtonSupport;
	CButton				*_pButtonTroophy;

	CButton				*_pButtonSwitch;
	CButton				*_pButtonYes;
	CButton				*_pButtonNo;
	CButton				*_pButtonEdit;

	CSpriteFont			*_pFont;

	char				_cUserName[8][20];
	unsigned char		_ucCurrentProfile;

	unsigned char		_ucLanguage;

	CButton				*_pFlag;

	CMobileKeyboard		*_pMobileKeyboard;

	CParticle2DManager	*_pParticleManager;

	CFXManager			*_pFXManager;

};

