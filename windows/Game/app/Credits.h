// prezentacja autorow gry
#pragma once

#include "../Game.h"
#include "../common/GameObject.h"
#include "../gfx/OGL.h"
#include "../ui/Mouse.h"
#include "../ui/Button.h"
#include "../gfx/Sprite.h"
#include "../gfx/Screen.h"

class CCredits: public CGameObject
{
public:
	CCredits();
	~CCredits();

	void	Open(CScreen *pScreen);		// load data
	void	Close(void);				// unload 

	int		Render(unsigned long lTimer, CMouse *pMouse);		// render frame																					

private:

	CSprite		*_background;	
	CButton		*_exitButton;

	unsigned long	_timerStart;	// start

};

