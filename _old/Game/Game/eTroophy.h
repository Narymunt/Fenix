// przydzielanie trofeum 

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

class eTroophy: public CGameObject
{
public:
	eTroophy();
	~eTroophy();

	void	Open(CScreen *pScreen);		// load data
	void	Close(void);				// unload 

	int		Render(unsigned long lTimer, CMouse *pMouse);		// render frame																					

private:

	CSprite				*m_pBackground;		// tlo

	unsigned long		m_ulTimerStart;	// poczatek

	bool				m_bMouseLock;		// blokada przycisku

	bool				m_bTroophyLocked[21];
	CSprite				*m_pTroophyLocked[21];
	CSprite				*m_pTroophyUnlocked[21];

	CScreen				*_pScreen;

	CSpriteFont			*_pFont;

	int					_iFontX, _iFontY;						// gdzie wypisujemy informacje o zaliczeniach

	float				_fFontScale;

};
