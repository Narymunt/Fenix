// 

#pragma once

#include "Game.h"
#include "GameObject.h"
#include "OGL.h"
#include "Mouse.h"
#include "Button.h"
#include "Sprite.h"
#include "Screen.h"

class ePreload: public CGameObject
{
public:
	ePreload();
	~ePreload();

	void	Open(CScreen *pScreen);		// load data
	void	Close(void);				// unload 

	int		Render(unsigned long lTimer, CMouse *pMouse);		// render frame																					

private:

	CSprite	*m_pBlack;			// czarne tlo
	CSprite	*m_pLogoBF;			// bigfish
	CSprite	*m_pLogoShodan9;	// shodan

	unsigned long	m_ulTimerStart;	// start

	bool	m_bMouseLock;		// avoid transfering click from previous state

};

