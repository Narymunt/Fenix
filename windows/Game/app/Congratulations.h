// ekran z gratulacjami ?
#pragma once

#include "../Game.h"
#include "../common/GameObject.h"
#include "../gfx/OGL.h"
#include "../ui/Mouse.h"
#include "../ui/Button.h"
#include "../gfx/Sprite.h"
#include "../gfx/Screen.h"
#include "../ui/SpriteFont.h"

class CCongratulations: public CGameObject
{
public:
	CCongratulations();
	~CCongratulations();

	void	Open(CScreen *pScreen);		// load data
	void	Close(void);				// unload 

	int		Render(unsigned long lTimer, CMouse *pMouse);		// render frame																					

private:

	CSprite					*_background;	
	CSprite					*_black;

	CButton					*_exitButton;

	CSpriteFont				*_font;

	unsigned long			_timerStart;	// start

};

