// ustawienia gry

#pragma once

#include "Game.h"
#include "GameObject.h"
#include "OGL.h"
#include "Mouse.h"
#include "Button.h"
#include "Sprite.h"
#include "Screen.h"
#include "Checkbox.h"
#include "GameSettings.h"

class eSettings: public CGameObject
{
public:
	eSettings();
	~eSettings();

	void	Open(CScreen *pScreen);		// load data
	void	Close(void);				// unload 

	int		Render(unsigned long lTimer, CMouse *pMouse);		// render frame																					

private:

	CSprite	*m_pBackground;		// tlo
	CButton	*m_pExitButton;		// wyjscie z helpa

	unsigned long	m_ulTimerStart;	// poczatek

	bool		m_bMouseLock;		// blokada przycisku

	CCheckbox	*m_pCheckboxMSX;
	CCheckbox	*m_pCheckboxSFX;

};

