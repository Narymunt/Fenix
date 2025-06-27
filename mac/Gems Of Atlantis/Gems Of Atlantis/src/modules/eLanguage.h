// 

#pragma once

#include "Game.h"
#include "GameObject.h"
#include "OGL.h"
#include "Mouse.h"
#include "Button.h"
#include "Sprite.h"
#include "Screen.h"

class eLanguage: public CGameObject
{
public:
	eLanguage();
	~eLanguage();

	void	Open(CScreen *pScreen);		// load data
	void	Close(void);				// unload 

	int		Render(unsigned long lTimer, CMouse *pMouse);		// render frame																					

	void	ucLanguage(unsigned char ucLang);
	unsigned char ucLanguage(void);


private:

	CSprite	*m_pBackground;		// tlo

	CButton	*m_pFlag[20];		// przyciski z jezykiem do wyboru

	unsigned long	m_ulTimerStart;	// start
	unsigned char	m_ucLanguage;


	bool	m_bMouseLock;		// avoid transfering click from previous state

};

