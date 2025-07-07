// main menu

#pragma once

#include "_fenix.h"
#include "GameObject.h"
#include "Mouse.h"
#include "Button.h"
#include "Sprite.h"
#include "Screen.h"
#include "Particle2DManager.h"

class eMainMenu : public CGameObject
{
public:
	eMainMenu();
	~eMainMenu();

	void	Open(CScreen *pScreen);		// load data
	void	Close(void);				// unload 

	int		Render(unsigned long lTimer, CMouse *pMouse);		// render frame																					

private:

	CSprite		*_pBackground;	
	CSprite		*_pBlack;

	CButton		*_pButtonStart;
	CButton		*_pButtonQuit;

	unsigned long	_ulTimerStart;	// start

	CParticle2DManager	*_pParticleManager;

	bool	m_bMouseLock;		// avoid transfering click from previous state


};

