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

class eLevelMenu: public CGameObject
{
public:
	eLevelMenu();
	~eLevelMenu();

	void	Open(CScreen *pScreen);		// load data
	void	Close(void);				// unload 

	int		Render(unsigned long lTimer, CMouse *pMouse);		// render frame																					

	int		iGetCurrentLevel(void);


private:

	CSprite	*m_pBackground;		// tlo

	CButton	*m_pLevel[7];		// przyciski z jezykiem do wyboru

	unsigned long	m_ulMap;		// ktore etapy dostepne

	unsigned long	m_ulTimerStart;	// poczatek

	unsigned char	m_ucCurrentLevel;

	CButton	*m_pButtonEndGame;	// koniec gry, tutaj jest wejscie do eCongratulations

	CButton	*m_pButtonBack;		// powrot z menu etapow do menu glownego

	bool		m_bMouseLock;		// blokada przycisku
};

