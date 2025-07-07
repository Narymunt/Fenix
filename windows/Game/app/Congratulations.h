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

class Congratulations: public GameObject
{
public:
	Congratulations();
	~Congratulations();

	void	open(Screen *screen);		// load data
	void	close(void);				// unload 

	int		render(unsigned long timer, Mouse *mouse);		// render frame																					

private:

	Sprite					*_background;	
	Sprite					*_black;

	Button					*_exitButton;

	SpriteFont				*_font;

	unsigned long			_timerStart;	// start

};

