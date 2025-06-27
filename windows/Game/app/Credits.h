// prezentacja autorow gry
#pragma once

#include "../Game.h"
#include "../common/GameObject.h"
#include "../gfx/OGL.h"
#include "../ui/Mouse.h"
#include "../ui/Button.h"
#include "../gfx/Sprite.h"
#include "../gfx/Screen.h"

class Credits: public GameObject
{
public:
	Credits();
	~Credits();

	void	open(Screen *pScreen);		// load data
	void	close(void);				// unload 

	int		render(unsigned long lTimer, Mouse *pMouse);		// render frame																					

private:

	Sprite		*_background;	
	Button		*_exitButton;

	unsigned long	_timerStart;	// start

};

