// 

#pragma once

#include "Game.h"
#include "dune/GameObject.h"
#include "dune/gfx/OGL.h"
#include "dune/ui/Mouse.h"
#include "dune/ui/Button.h"
#include "dune/gfx/Sprite.h"
#include "dune/gfx/Screen.h"
#include "dune/ui/SpriteFont.h"

class CCongratulations: public CGameObject
{
public:
	CCongratulations();
	~CCongratulations();

	void	Open(CScreen *pScreen);		// load data
	void	Close(void);				// unload 

	int		Render(unsigned long lTimer, CMouse *pMouse);		// render frame																					

private:

	CSprite					*_pBackground;	
	CSprite					*_pBlack;

	CButton					*_pExitButton;

	CSpriteFont				*_pFont;

	unsigned long	_ulTimerStart;	// start

	bool	m_bMouseLock;		// avoid transfering click from previous state

};

