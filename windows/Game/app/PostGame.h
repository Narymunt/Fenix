// ePostGame - zliczanie punktow po zakonczeniu gry (levelu)

#pragma once

#include "../Game.h"
#include "../common/GameObject.h"
#include "../gfx/OGL.h"
#include "../ui/Mouse.h"
#include "../ui/Button.h"
#include "../gfx/Sprite.h"
#include "../gfx/Screen.h"

class CPostGame : public CGameObject
{
public:
	CPostGame();
	~CPostGame();

	void	open(CScreen* pScreen);		// load data
	void	close(void);				// unload 

	int		render(unsigned long lTimer, CMouse* pMouse);		// render frame																					

private:

	CSprite* _background;
	CButton* _exitButton;

	unsigned long	_timerStart;	// start

};

