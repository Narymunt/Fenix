// 

#pragma once

#include "Game.h"
#include "GameObject.h"
#include "OGL.h"
#include "Mouse.h"
#include "Button.h"
#include "Sprite.h"
#include "Screen.h"

class eIntro: public CGameObject
{
public:
	eIntro();
	~eIntro();

	void	Open(CScreen *pScreen);		// load data
	void	Close(void);				// unload 

	int		Render(unsigned long lTimer, CMouse *pMouse);		// render frame																					

private:

	CSprite		*_pBackground;	
	CSprite		*_pBlack;

	unsigned long	_ulTimerStart;	// start

	bool	m_bMouseLock;		// avoid transfering click from previous state

};

