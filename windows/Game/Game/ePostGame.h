// ePostGame - zliczanie punktow po zakonczeniu gry
// 

#pragma once

#include "Game.h"
#include "GameObject.h"
#include "OGL.h"
#include "Mouse.h"
#include "Button.h"
#include "Sprite.h"
#include "Screen.h"
#include "Profile.h"
#include "SpriteFont.h"
#include "HighScore.h"

class ePostGame: public CGameObject
{
public:
	ePostGame();
	~ePostGame();

	void	Open(CScreen *pScreen);		// load data
	void	Close(void);				// unload 

	int		Render(unsigned long lTimer, CMouse *pMouse);		// render frame																					

	char	cToDigit(char cDigit);

private:

	CSprite	*m_pBackground;		// tlo

	CButton	*m_pButtonMenu;		// powrot do glownego menu
	CButton	*m_pButtonAgain;	// ponowna gra

	CSprite	*m_pScoreBar;		// ile punktow mamy
	CSprite	*m_pLevelBar;		// nasz poziom doswiadczenia

	CSprite	*m_pNumber[10];		// cyferki

	CProfile	*m_pUserProfile;

	unsigned long	m_ulScoreTable[11];
	char			m_cNameTable[11][100];
	bool			m_bAddedToHighscore;	// czy dodano juz do tablicy ? 

	CSpriteFont	*m_pFont;		// czcionka do wypisywania punktow na highscore

	CScreen			*_pScreen;	// potrzebne do progress barow itd
};

